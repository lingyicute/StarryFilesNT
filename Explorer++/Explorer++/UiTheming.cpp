// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "UiTheming.h"
#include "CoreInterface.h"
#include "ShellBrowser/ShellBrowserImpl.h"
#include "Tab.h"
#include "TabContainer.h"

UiTheming::UiTheming(CoreInterface *coreInterface, TabContainer *tabContainer) :
	m_coreInterface(coreInterface),
	m_tabContainer(tabContainer),
	m_customListViewColorsApplied(false)
{
	m_connections.emplace_back(m_tabContainer->tabCreatedSignal.AddObserver(
		std::bind_front(&UiTheming::OnTabCreated, this)));
}

void UiTheming::OnTabCreated(int tabId, BOOL switchToNewTab)
{
	UNREFERENCED_PARAMETER(switchToNewTab);

	const Tab &tab = m_tabContainer->GetTab(tabId);

	if (m_customListViewColorsApplied)
	{
		ApplyListViewColorsForTab(tab, m_listViewBackgroundColor, m_listViewTextColor);
	}
}

bool UiTheming::SetListViewColors(COLORREF backgroundColor, COLORREF textColor)
{
	m_customListViewColorsApplied = true;
	m_listViewBackgroundColor = backgroundColor;
	m_listViewTextColor = textColor;

	bool res = ApplyListViewColorsForAllTabs(backgroundColor, textColor);

	return res;
}

bool UiTheming::ApplyListViewColorsForAllTabs(COLORREF backgroundColor, COLORREF textColor)
{
	bool overallResult = true;

	for (const auto &item : m_tabContainer->GetAllTabs())
	{
		bool res = ApplyListViewColorsForTab(*item.second, backgroundColor, textColor);

		if (!res)
		{
			overallResult = false;
		}
	}

	return overallResult;
}

bool UiTheming::ApplyListViewColorsForTab(const Tab &tab, COLORREF backgroundColor,
	COLORREF textColor)
{
	BOOL bkRes = ListView_SetBkColor(tab.GetShellBrowserImpl()->GetListView(), backgroundColor);
	BOOL textBkRes =
		ListView_SetTextBkColor(tab.GetShellBrowserImpl()->GetListView(), backgroundColor);
	BOOL textRes = ListView_SetTextColor(tab.GetShellBrowserImpl()->GetListView(), textColor);

	InvalidateRect(tab.GetShellBrowserImpl()->GetListView(), nullptr, TRUE);

	if (!bkRes || !textBkRes || !textRes)
	{
		return false;
	}

	return true;
}

void UiTheming::SetTreeViewColors(COLORREF backgroundColor, COLORREF textColor)
{
	TreeView_SetBkColor(m_coreInterface->GetTreeView(), backgroundColor);
	TreeView_SetTextColor(m_coreInterface->GetTreeView(), textColor);

	InvalidateRect(m_coreInterface->GetTreeView(), nullptr, TRUE);
}
