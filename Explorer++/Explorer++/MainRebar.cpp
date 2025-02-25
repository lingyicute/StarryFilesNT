// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "Explorer++.h"
#include "AddressBar.h"
#include "App.h"
#include "ApplicationToolbar.h"
#include "ApplicationToolbarView.h"
#include "Bookmarks/UI/BookmarksToolbar.h"
#include "Bookmarks/UI/Views/BookmarksToolbarView.h"
#include "Config.h"
#include "DriveEnumeratorImpl.h"
#include "DriveModel.h"
#include "DriveWatcherImpl.h"
#include "DrivesToolbar.h"
#include "DrivesToolbarView.h"
#include "Explorer++_internal.h"
#include "MainRebarStorage.h"
#include "MainRebarView.h"
#include "MainResource.h"
#include "MainToolbar.h"
#include "ShellBrowser/ShellBrowserImpl.h"
#include "ShellBrowser/ShellNavigationController.h"
#include "TabContainer.h"
#include "../Helper/MenuHelper.h"
#include "../Helper/WindowHelper.h"

void Explorerplusplus::CreateMainRebarAndChildren(const WindowStorageData *storageData)
{
	m_mainRebarView = MainRebarView::Create(m_hContainer);

	m_windowSubclasses.push_back(std::make_unique<WindowSubclass>(m_mainRebarView->GetHWND(),
		std::bind_front(&Explorerplusplus::RebarSubclass, this)));

	auto bands = InitializeMainRebarBands(storageData);
	m_mainRebarView->AddBands(bands);

	m_mainRebarView->LockBands(m_config->lockToolbars.get());
	m_rebarConnections.push_back(m_config->lockToolbars.addObserver(
		std::bind_front(&RebarView::LockBands, m_mainRebarView)));
}

std::vector<RebarView::Band> Explorerplusplus::InitializeMainRebarBands(
	const WindowStorageData *storageData)
{
	std::vector<RebarView::Band> mainRebarBands;

	CreateMainToolbar(storageData ? storageData->mainToolbarButtons : std::nullopt);
	auto band = InitializeToolbarBand(REBAR_BAND_ID_MAIN_TOOLBAR, m_mainToolbar->GetHWND(),
		m_config->showMainToolbar.get());
	mainRebarBands.push_back(band);

	m_rebarConnections.push_back(m_config->showMainToolbar.addObserver(
		std::bind_front(&RebarView::ShowBand, m_mainRebarView, m_mainToolbar->GetHWND())));

	CreateAddressBar();
	band = InitializeNonToolbarBand(REBAR_BAND_ID_ADDRESS_BAR, m_addressBar->GetHWND(),
		m_config->showAddressBar.get());
	mainRebarBands.push_back(band);

	m_rebarConnections.push_back(m_config->showAddressBar.addObserver(
		std::bind_front(&RebarView::ShowBand, m_mainRebarView, m_addressBar->GetHWND())));

	CreateBookmarksToolbar();
	band = InitializeToolbarBand(REBAR_BAND_ID_BOOKMARKS_TOOLBAR,
		m_bookmarksToolbar->GetView()->GetHWND(), m_config->showBookmarksToolbar.get());
	mainRebarBands.push_back(band);

	m_rebarConnections.push_back(m_config->showBookmarksToolbar.addObserver(std::bind_front(
		&RebarView::ShowBand, m_mainRebarView, m_bookmarksToolbar->GetView()->GetHWND())));

	CreateDrivesToolbar();
	band = InitializeToolbarBand(REBAR_BAND_ID_DRIVES_TOOLBAR,
		m_drivesToolbar->GetView()->GetHWND(), m_config->showDrivesToolbar.get());
	mainRebarBands.push_back(band);

	m_rebarConnections.push_back(m_config->showDrivesToolbar.addObserver(std::bind_front(
		&RebarView::ShowBand, m_mainRebarView, m_drivesToolbar->GetView()->GetHWND())));

	CreateApplicationToolbar();
	band = InitializeToolbarBand(REBAR_BAND_ID_APPLICATIONS_TOOLBAR,
		m_applicationToolbar->GetView()->GetHWND(), m_config->showApplicationToolbar.get());
	mainRebarBands.push_back(band);

	m_rebarConnections.push_back(m_config->showApplicationToolbar.addObserver(std::bind_front(
		&RebarView::ShowBand, m_mainRebarView, m_applicationToolbar->GetView()->GetHWND())));

	if (storageData)
	{
		UpdateMainRebarBandsFromLoadedInfo(mainRebarBands, storageData->mainRebarInfo);
	}

	return mainRebarBands;
}

RebarView::Band Explorerplusplus::InitializeToolbarBand(UINT id, HWND toolbar, bool showBand)
{
	auto toolbarSize = static_cast<DWORD>(SendMessage(toolbar, TB_GETBUTTONSIZE, 0, 0));

	SIZE size;
	auto res = SendMessage(toolbar, TB_GETMAXSIZE, 0, reinterpret_cast<LPARAM>(&size));
	DCHECK(res);

	RebarView::Band band = {};
	band.id = id;
	band.child = toolbar;
	band.height = HIWORD(toolbarSize);
	band.newLine = true;
	band.useChevron = true;
	band.show = showBand;
	band.idealLength = size.cx;
	return band;
}

RebarView::Band Explorerplusplus::InitializeNonToolbarBand(UINT id, HWND child, bool showBand)
{
	RECT rect;
	auto res = GetWindowRect(child, &rect);
	DCHECK(res);

	RebarView::Band band = {};
	band.id = id;
	band.child = child;
	band.height = GetRectHeight(&rect);
	band.newLine = true;
	band.useChevron = false;
	band.show = showBand;
	return band;
}

void Explorerplusplus::UpdateMainRebarBandsFromLoadedInfo(
	std::vector<RebarView::Band> &mainRebarBands,
	const std::vector<RebarBandStorageInfo> &rebarStorageInfo)
{
	auto getSortedBandIndex = [this, &mainRebarBands, &rebarStorageInfo](UINT bandId) -> size_t
	{
		auto itr = std::find_if(rebarStorageInfo.begin(), rebarStorageInfo.end(),
			[bandId](const auto &loadedBandInfo) { return loadedBandInfo.id == bandId; });

		if (itr == rebarStorageInfo.end())
		{
			// Any band that doesn't appear in the loaded data will be placed at the end.
			return mainRebarBands.size() - 1;
		}

		return itr - rebarStorageInfo.begin();
	};

	std::stable_sort(mainRebarBands.begin(), mainRebarBands.end(),
		[getSortedBandIndex](const auto &band1, const auto &band2)
		{ return getSortedBandIndex(band1.id) < getSortedBandIndex(band2.id); });

	for (auto &band : mainRebarBands)
	{
		UpdateMainRebarBandFromLoadedInfo(band, rebarStorageInfo);
	}
}

void Explorerplusplus::UpdateMainRebarBandFromLoadedInfo(RebarView::Band &band,
	const std::vector<RebarBandStorageInfo> &rebarStorageInfo)
{
	auto itr = std::find_if(rebarStorageInfo.begin(), rebarStorageInfo.end(),
		[&band](const auto &loadedBandInfo) { return loadedBandInfo.id == band.id; });

	if (itr == rebarStorageInfo.end())
	{
		return;
	}

	band.newLine = WI_IsFlagSet(itr->style, RBBS_BREAK);
	band.length = itr->length;
}

LRESULT Explorerplusplus::RebarSubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITMENU:
		SendMessage(m_hContainer, WM_INITMENU, wParam, lParam);
		break;

	case WM_MENUSELECT:
		SendMessage(m_hContainer, WM_MENUSELECT, wParam, lParam);
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR) lParam)->code)
		{
		case NM_RCLICK:
		{
			auto pnmm = reinterpret_cast<LPNMMOUSE>(lParam);
			OnToolbarRClick(pnmm->hdr.hwndFrom);
		}
			return TRUE;
		}
		break;

	case WM_DESTROY:
		m_rebarConnections.clear();
		break;
	}

	return DefSubclassProc(hwnd, msg, wParam, lParam);
}

void Explorerplusplus::OnToolbarRClick(HWND sourceWindow)
{
	auto parentMenu = wil::unique_hmenu(
		LoadMenu(m_app->GetResourceInstance(), MAKEINTRESOURCE(IDR_TOOLBAR_MENU)));

	if (!parentMenu)
	{
		return;
	}

	HMENU menu = GetSubMenu(parentMenu.get(), 0);

	MenuHelper::CheckItem(menu, IDM_TOOLBARS_ADDRESSBAR, m_config->showAddressBar.get());
	MenuHelper::CheckItem(menu, IDM_TOOLBARS_MAINTOOLBAR, m_config->showMainToolbar.get());
	MenuHelper::CheckItem(menu, IDM_TOOLBARS_BOOKMARKSTOOLBAR,
		m_config->showBookmarksToolbar.get());
	MenuHelper::CheckItem(menu, IDM_TOOLBARS_DRIVES, m_config->showDrivesToolbar.get());
	MenuHelper::CheckItem(menu, IDM_TOOLBARS_APPLICATIONTOOLBAR,
		m_config->showApplicationToolbar.get());
	MenuHelper::CheckItem(menu, IDM_TOOLBARS_LOCKTOOLBARS, m_config->lockToolbars.get());

	DWORD dwPos = GetMessagePos();

	POINT ptCursor;
	ptCursor.x = GET_X_LPARAM(dwPos);
	ptCursor.y = GET_Y_LPARAM(dwPos);

	// Give any observers a chance to modify the menu.
	m_toolbarContextMenuSignal(menu, sourceWindow, ptCursor);

	int menuItemId = TrackPopupMenu(menu, TPM_LEFTALIGN | TPM_RETURNCMD, ptCursor.x, ptCursor.y, 0,
		m_mainRebarView->GetHWND(), nullptr);

	if (menuItemId == 0)
	{
		return;
	}

	OnToolbarMenuItemSelected(sourceWindow, menuItemId);
}

void Explorerplusplus::OnToolbarMenuItemSelected(HWND sourceWindow, int menuItemId)
{
	switch (menuItemId)
	{
	case IDM_TOOLBARS_ADDRESSBAR:
		OnToggleAddressBar();
		break;

	case IDM_TOOLBARS_MAINTOOLBAR:
		OnToggleMainToolbar();
		break;

	case IDM_TOOLBARS_BOOKMARKSTOOLBAR:
		OnToggleBookmarksToolbar();
		break;

	case IDM_TOOLBARS_DRIVES:
		OnToggleDrivesToolbar();
		break;

	case IDM_TOOLBARS_APPLICATIONTOOLBAR:
		OnToggleApplicationToolbar();
		break;

	case IDM_TOOLBARS_LOCKTOOLBARS:
		OnToggleLockToolbars();
		break;

	case IDM_TOOLBARS_CUSTOMIZE:
		OnCustomizeMainToolbar();
		break;

	default:
		m_toolbarContextMenuSelectedSignal(sourceWindow, menuItemId);
		break;
	}
}

void Explorerplusplus::OnToggleAddressBar()
{
	m_config->showAddressBar = !m_config->showAddressBar.get();
}

void Explorerplusplus::OnToggleMainToolbar()
{
	m_config->showMainToolbar = !m_config->showMainToolbar.get();
}

void Explorerplusplus::OnToggleBookmarksToolbar()
{
	m_config->showBookmarksToolbar = !m_config->showBookmarksToolbar.get();
}

void Explorerplusplus::OnToggleDrivesToolbar()
{
	m_config->showDrivesToolbar = !m_config->showDrivesToolbar.get();
}

void Explorerplusplus::OnToggleApplicationToolbar()
{
	m_config->showApplicationToolbar = !m_config->showApplicationToolbar.get();
}

void Explorerplusplus::OnToggleLockToolbars()
{
	m_config->lockToolbars = !m_config->lockToolbars.get();
}

void Explorerplusplus::OnCustomizeMainToolbar()
{
	m_mainToolbar->StartCustomization();
}

boost::signals2::connection Explorerplusplus::AddToolbarContextMenuObserver(
	const ToolbarContextMenuSignal::slot_type &observer)
{
	return m_toolbarContextMenuSignal.connect(observer);
}

boost::signals2::connection Explorerplusplus::AddToolbarContextMenuSelectedObserver(
	const ToolbarContextMenuSelectedSignal::slot_type &observer)
{
	return m_toolbarContextMenuSelectedSignal.connect(observer);
}

void Explorerplusplus::CreateAddressBar()
{
	m_addressBar = AddressBar::Create(m_mainRebarView->GetHWND(), m_app, this, this);
	m_addressBar->sizeUpdatedSignal.AddObserver(
		std::bind_front(&Explorerplusplus::OnAddressBarSizeUpdated, this));
}

void Explorerplusplus::OnAddressBarSizeUpdated()
{
	RECT rect;
	GetWindowRect(m_addressBar->GetHWND(), &rect);
	m_mainRebarView->UpdateBandSize(m_addressBar->GetHWND(), 0, GetRectHeight(&rect));
}

void Explorerplusplus::CreateMainToolbar(
	const std::optional<MainToolbarStorage::MainToolbarButtons> &initialButtons)
{
	m_mainToolbar = MainToolbar::Create(m_mainRebarView->GetHWND(), m_app->GetResourceInstance(),
		this, this, m_app->GetIconResourceLoader(), &m_shellIconLoader, m_config, initialButtons);
	m_mainToolbar->sizeUpdatedSignal.AddObserver(
		std::bind(&Explorerplusplus::OnRebarToolbarSizeUpdated, this, m_mainToolbar->GetHWND()));
}

void Explorerplusplus::CreateBookmarksToolbar()
{
	auto bookmarksToolbarView = new BookmarksToolbarView(m_mainRebarView->GetHWND(), m_config);

	m_bookmarksToolbar =
		BookmarksToolbar::Create(bookmarksToolbarView, this, this, m_app->GetIconResourceLoader(),
			&m_iconFetcher, m_app->GetBookmarkTree(), m_app->GetThemeManager());
	m_bookmarksToolbar->GetView()->AddToolbarSizeUpdatedObserver(
		std::bind(&Explorerplusplus::OnRebarToolbarSizeUpdated, this,
			m_bookmarksToolbar->GetView()->GetHWND()));
}

void Explorerplusplus::CreateDrivesToolbar()
{
	auto drivesToolbarView = DrivesToolbarView::Create(m_mainRebarView->GetHWND(), m_config);

	auto driveEnumerator = std::make_unique<DriveEnumeratorImpl>();
	auto driveWatcher = std::make_unique<DriveWatcherImpl>(m_hContainer);
	auto driveModel =
		std::make_unique<DriveModel>(std::move(driveEnumerator), std::move(driveWatcher));

	m_drivesToolbar = DrivesToolbar::Create(drivesToolbarView, std::move(driveModel), this, this);
	m_drivesToolbar->GetView()->AddToolbarSizeUpdatedObserver(std::bind(
		&Explorerplusplus::OnRebarToolbarSizeUpdated, this, m_drivesToolbar->GetView()->GetHWND()));
}

void Explorerplusplus::CreateApplicationToolbar()
{
	auto applicationToolbarView =
		Applications::ApplicationToolbarView::Create(m_mainRebarView->GetHWND(), m_config);

	m_applicationToolbar = Applications::ApplicationToolbar::Create(applicationToolbarView,
		m_app->GetApplicationModel(), this, m_app->GetThemeManager());
	m_applicationToolbar->GetView()->AddToolbarSizeUpdatedObserver(
		std::bind(&Explorerplusplus::OnRebarToolbarSizeUpdated, this,
			m_applicationToolbar->GetView()->GetHWND()));
}

void Explorerplusplus::OnRebarToolbarSizeUpdated(HWND toolbar)
{
	SIZE size;
	[[maybe_unused]] auto res =
		SendMessage(toolbar, TB_GETMAXSIZE, 0, reinterpret_cast<LPARAM>(&size));
	assert(res);

	m_mainRebarView->UpdateBandSize(toolbar, size.cx, size.cy);
}

HMENU Explorerplusplus::CreateRebarHistoryMenu(BOOL bBack)
{
	HMENU hSubMenu = nullptr;
	std::vector<HistoryEntry *> history;
	int iBase;

	const Tab &tab = GetActivePane()->GetTabContainer()->GetSelectedTab();

	if (bBack)
	{
		iBase = ID_REBAR_MENU_BACK_START;
		history = tab.GetShellBrowserImpl()->GetNavigationController()->GetBackHistory();
	}
	else
	{
		iBase = ID_REBAR_MENU_FORWARD_START;
		history = tab.GetShellBrowserImpl()->GetNavigationController()->GetForwardHistory();
	}

	if (!history.empty())
	{
		int i = 0;

		hSubMenu = CreateMenu();

		for (auto *entry : history)
		{
			std::wstring displayName =
				GetDisplayNameWithFallback(entry->GetPidl().Raw(), SHGDN_INFOLDER);

			MENUITEMINFO mii;
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_ID | MIIM_STRING;
			mii.wID = iBase + i + 1;
			mii.dwTypeData = displayName.data();
			InsertMenuItem(hSubMenu, i, TRUE, &mii);

			i++;
		}
	}

	return hSubMenu;
}
