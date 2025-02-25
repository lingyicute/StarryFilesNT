// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ShellBrowser/SortModes.h"
#include <wil/resource.h>

class Tab;

class SortMenuBuilder
{
public:
	struct SortMenus
	{
		wil::unique_hmenu sortByMenu;
		wil::unique_hmenu groupByMenu;
	};

	SortMenuBuilder(HINSTANCE resourceInstance);

	SortMenus BuildMenus(const Tab &tab);

private:
	wil::unique_hmenu CreateDefaultMenu(UINT ascendingMenuItemId, UINT descendingMenuItemId);
	void SetMenuItemStates(HMENU sortByMenu, HMENU groupByMenu, const Tab &tab);

	UINT GetSortMenuItemStringIndex(UINT uItemId);
	int DetermineSortModeMenuId(SortMode sortMode);
	int DetermineGroupModeMenuId(SortMode sortMode);

	HINSTANCE m_resourceInstance;
};
