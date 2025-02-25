// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

/*
 * Switches events based on the currently selected window
 * (principally the listview and treeview).
 */

#include "stdafx.h"
#include "StarryFiles++.h"
#include "ShellBrowser/ShellBrowserImpl.h"
#include "ShellTreeView/ShellTreeView.h"
#include "TabContainer.h"

void Starryfilesplusplus::OnCopyItemPath() const
{
	HWND hFocus;

	hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		OnListViewCopyItemPath();
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		OnTreeViewCopyItemPath();
	}
}

void Starryfilesplusplus::OnCopyUniversalPaths() const
{
	HWND hFocus;

	hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		OnListViewCopyUniversalPaths();
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		OnTreeViewCopyUniversalPaths();
	}
}

void Starryfilesplusplus::OnCopy(BOOL bCopy)
{
	HWND hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		Tab &selectedTab = GetActivePane()->GetTabContainer()->GetSelectedTab();
		selectedTab.GetShellBrowserImpl()->CopySelectedItemsToClipboard(bCopy);
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		m_shellTreeView->CopySelectedItemToClipboard(bCopy);
	}
}

void Starryfilesplusplus::OnFileRename()
{
	HWND hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		Tab &selectedTab = GetActivePane()->GetTabContainer()->GetSelectedTab();
		selectedTab.GetShellBrowserImpl()->StartRenamingSelectedItems();
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		m_shellTreeView->StartRenamingSelectedItem();
	}
}

void Starryfilesplusplus::OnFileDelete(bool permanent)
{
	HWND hFocus;

	hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		Tab &tab = GetActivePane()->GetTabContainer()->GetSelectedTab();
		tab.GetShellBrowserImpl()->DeleteSelectedItems(permanent);
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		m_shellTreeView->DeleteSelectedItem(permanent);
	}
}

void Starryfilesplusplus::OnSetFileAttributes() const
{
	HWND hFocus;

	hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		OnListViewSetFileAttributes();
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		OnTreeViewSetFileAttributes();
	}
}

void Starryfilesplusplus::OnShowFileProperties() const
{
	HWND hFocus;

	hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		const Tab &selectedTab = GetActivePane()->GetTabContainer()->GetSelectedTab();
		selectedTab.GetShellBrowserImpl()->ShowPropertiesForSelectedFiles();
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		m_shellTreeView->ShowPropertiesOfSelectedItem();
	}
}

void Starryfilesplusplus::OnPaste()
{
	HWND focus = GetFocus();

	if (focus == m_hActiveListView)
	{
		OnListViewPaste();
	}
	else if (focus == m_shellTreeView->GetHWND())
	{
		m_shellTreeView->Paste();
	}
}

void Starryfilesplusplus::OnPasteShortcut()
{
	HWND focus = GetFocus();

	if (focus == m_hActiveListView)
	{
		GetActiveShellBrowserImpl()->PasteShortcut();
	}
	else if (focus == m_shellTreeView->GetHWND())
	{
		m_shellTreeView->PasteShortcut();
	}
}
