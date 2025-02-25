// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "StarryFiles++.h"
#include "ClipboardOperations.h"
#include "DirectoryOperationsHelper.h"
#include "ShellBrowser/ShellBrowserImpl.h"
#include "ShellTreeView/ShellTreeView.h"
#include "TabContainer.h"
#include "../Helper/ClipboardHelper.h"

BOOL Starryfilesplusplus::AnyItemsSelected() const
{
	HWND hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		const Tab &selectedTab = GetActivePane()->GetTabContainer()->GetSelectedTab();

		if (ListView_GetSelectedCount(selectedTab.GetShellBrowserImpl()->GetListView()) > 0)
		{
			return TRUE;
		}
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		if (TreeView_GetSelection(m_shellTreeView->GetHWND()) != nullptr)
		{
			return TRUE;
		}
	}

	return FALSE;
}

bool Starryfilesplusplus::CanCreate() const
{
	const Tab &selectedTab = GetActivePane()->GetTabContainer()->GetSelectedTab();
	auto pidlDirectory = selectedTab.GetShellBrowserImpl()->GetDirectoryIdl();
	return CanCreateInDirectory(pidlDirectory.get());
}

BOOL Starryfilesplusplus::CanCut() const
{
	return TestItemAttributes(SFGAO_CANMOVE);
}

BOOL Starryfilesplusplus::CanCopy() const
{
	return TestItemAttributes(SFGAO_CANCOPY);
}

BOOL Starryfilesplusplus::CanRename() const
{
	return TestItemAttributes(SFGAO_CANRENAME);
}

BOOL Starryfilesplusplus::CanDelete() const
{
	return TestItemAttributes(SFGAO_CANDELETE);
}

BOOL Starryfilesplusplus::CanShowFileProperties() const
{
	return TestItemAttributes(SFGAO_HASPROPSHEET);
}

/* Returns TRUE if all the specified attributes are set on the selected items. */
BOOL Starryfilesplusplus::TestItemAttributes(SFGAOF attributes) const
{
	SFGAOF commonAttributes = attributes;
	HRESULT hr = GetSelectionAttributes(&commonAttributes);

	if (SUCCEEDED(hr))
	{
		return (commonAttributes & attributes) == attributes;
	}

	return FALSE;
}

HRESULT Starryfilesplusplus::GetSelectionAttributes(SFGAOF *pItemAttributes) const
{
	HWND hFocus;
	HRESULT hr = E_FAIL;

	hFocus = GetFocus();

	if (hFocus == m_hActiveListView)
	{
		const Tab &selectedTab = GetActivePane()->GetTabContainer()->GetSelectedTab();
		hr = selectedTab.GetShellBrowserImpl()->GetListViewSelectionAttributes(pItemAttributes);
	}
	else if (hFocus == m_shellTreeView->GetHWND())
	{
		hr = GetTreeViewSelectionAttributes(pItemAttributes);
	}

	return hr;
}

HRESULT Starryfilesplusplus::GetTreeViewSelectionAttributes(SFGAOF *pItemAttributes) const
{
	auto pidl = m_shellTreeView->GetSelectedNodePidl();
	return GetItemAttributes(pidl.get(), pItemAttributes);
}

BOOL Starryfilesplusplus::CanPaste(PasteType pasteType) const
{
	auto directory = MaybeGetFocusedDirectory();

	if (!directory.HasValue())
	{
		return false;
	}

	return CanPasteInDirectory(directory.Raw(), pasteType);
}

// Tests whether a hard link or symlink can be pasted.
bool Starryfilesplusplus::CanPasteLink() const
{
	const auto *activeShellBrowser = GetActiveShellBrowserImpl();
	return ClipboardOperations::CanPasteLinkInDirectory(
		activeShellBrowser->GetDirectoryIdl().get());
}

PidlAbsolute Starryfilesplusplus::MaybeGetFocusedDirectory() const
{
	HWND focus = GetFocus();

	if (!focus)
	{
		return nullptr;
	}

	unique_pidl_absolute directory;

	const auto *activeShellBrowser = GetActiveShellBrowserImpl();

	if (focus == activeShellBrowser->GetListView())
	{
		directory = activeShellBrowser->GetDirectoryIdl();
	}
	else if (focus == m_shellTreeView->GetHWND())
	{
		directory = m_shellTreeView->GetSelectedNodePidl();
	}

	return directory.get();
}
