// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "DefaultSettingsOptionsPage.h"
#include "Config.h"
#include "MainResource.h"
#include "SetDefaultColumnsDialog.h"
#include "ViewModeHelper.h"
#include "../Helper/Controls.h"
#include "../Helper/ResizableDialogHelper.h"

DefaultSettingsOptionsPage::DefaultSettingsOptionsPage(HWND parent, HINSTANCE resourceInstance,
	Config *config, CoreInterface *coreInterface, SettingChangedCallback settingChangedCallback,
	HWND tooltipWindow, ThemeManager *themeManager) :
	OptionsPage(IDD_OPTIONS_DEFAULT, IDS_OPTIONS_DEFAULT_TITLE, parent, resourceInstance, config,
		coreInterface, settingChangedCallback, tooltipWindow),
	m_themeManager(themeManager)
{
}

std::unique_ptr<ResizableDialogHelper> DefaultSettingsOptionsPage::InitializeResizeDialogHelper()
{
	std::vector<ResizableDialogControl> controls;
	controls.emplace_back(GetDlgItem(GetDialog(), IDC_STATIC_DEFAULT_SETTINGS_NOTICE),
		MovingType::None, SizingType::Horizontal);
	controls.emplace_back(GetDlgItem(GetDialog(), IDC_SHOWHIDDENGLOBAL), MovingType::None,
		SizingType::Horizontal);
	controls.emplace_back(GetDlgItem(GetDialog(), IDC_AUTOARRANGEGLOBAL), MovingType::None,
		SizingType::Horizontal);
	controls.emplace_back(GetDlgItem(GetDialog(), IDC_SHOWINGROUPSGLOBAL), MovingType::None,
		SizingType::Horizontal);
	controls.emplace_back(GetDlgItem(GetDialog(), IDC_SORTASCENDINGGLOBAL), MovingType::None,
		SizingType::Horizontal);
	controls.emplace_back(GetDlgItem(GetDialog(), IDC_GROUP_SORT_ASCENDING_GLOBAL),
		MovingType::None, SizingType::Horizontal);
	return std::make_unique<ResizableDialogHelper>(GetDialog(), controls);
}

void DefaultSettingsOptionsPage::InitializeControls()
{
	if (m_config->defaultFolderSettings.showHidden)
	{
		CheckDlgButton(GetDialog(), IDC_SHOWHIDDENGLOBAL, BST_CHECKED);
	}

	if (m_config->defaultFolderSettings.autoArrange)
	{
		CheckDlgButton(GetDialog(), IDC_AUTOARRANGEGLOBAL, BST_CHECKED);
	}

	if (m_config->defaultFolderSettings.sortDirection == +SortDirection::Ascending)
	{
		CheckDlgButton(GetDialog(), IDC_SORTASCENDINGGLOBAL, BST_CHECKED);
	}

	if (m_config->defaultFolderSettings.showInGroups)
	{
		CheckDlgButton(GetDialog(), IDC_SHOWINGROUPSGLOBAL, BST_CHECKED);
	}

	if (m_config->defaultFolderSettings.groupSortDirection == +SortDirection::Ascending)
	{
		CheckDlgButton(GetDialog(), IDC_GROUP_SORT_ASCENDING_GLOBAL, BST_CHECKED);
	}

	std::vector<ComboBoxItem> viewModeItems;

	for (auto viewMode : VIEW_MODES)
	{
		viewModeItems.emplace_back(viewMode, GetViewModeMenuText(viewMode, m_resourceInstance));
	}

	AddItemsToComboBox(GetDlgItem(GetDialog(), IDC_OPTIONS_DEFAULT_VIEW), viewModeItems,
		m_config->defaultFolderSettings.viewMode);
}

void DefaultSettingsOptionsPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	if (HIWORD(wParam) != 0)
	{
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
			m_settingChangedCallback();
			break;
		}
	}
	else
	{
		switch (LOWORD(wParam))
		{
		case IDC_SHOWHIDDENGLOBAL:
		case IDC_AUTOARRANGEGLOBAL:
		case IDC_SORTASCENDINGGLOBAL:
		case IDC_SHOWINGROUPSGLOBAL:
		case IDC_GROUP_SORT_ASCENDING_GLOBAL:
			m_settingChangedCallback();
			break;

		case IDC_BUTTON_DEFAULTCOLUMNS:
		{
			SetDefaultColumnsDialog setDefaultColumnsDialog(m_resourceInstance, GetDialog(),
				m_themeManager, m_config->globalFolderSettings.folderColumns);
			setDefaultColumnsDialog.ShowModalDialog();
		}
		break;
		}
	}
}

void DefaultSettingsOptionsPage::SaveSettings()
{
	m_config->defaultFolderSettings.showHidden =
		(IsDlgButtonChecked(GetDialog(), IDC_SHOWHIDDENGLOBAL) == BST_CHECKED);

	m_config->defaultFolderSettings.autoArrange =
		(IsDlgButtonChecked(GetDialog(), IDC_AUTOARRANGEGLOBAL) == BST_CHECKED);

	bool sortAscending = (IsDlgButtonChecked(GetDialog(), IDC_SORTASCENDINGGLOBAL) == BST_CHECKED);
	m_config->defaultFolderSettings.sortDirection =
		sortAscending ? SortDirection::Ascending : SortDirection::Descending;

	m_config->defaultFolderSettings.showInGroups =
		(IsDlgButtonChecked(GetDialog(), IDC_SHOWINGROUPSGLOBAL) == BST_CHECKED);

	bool groupSortAscending =
		(IsDlgButtonChecked(GetDialog(), IDC_GROUP_SORT_ASCENDING_GLOBAL) == BST_CHECKED);
	m_config->defaultFolderSettings.groupSortDirection =
		groupSortAscending ? SortDirection::Ascending : SortDirection::Descending;

	HWND hComboBox = GetDlgItem(GetDialog(), IDC_OPTIONS_DEFAULT_VIEW);
	int selectedIndex = static_cast<int>(SendMessage(hComboBox, CB_GETCURSEL, 0, 0));
	m_config->defaultFolderSettings.viewMode = ViewMode::_from_integral(
		static_cast<int>(SendMessage(hComboBox, CB_GETITEMDATA, selectedIndex, 0)));
}
