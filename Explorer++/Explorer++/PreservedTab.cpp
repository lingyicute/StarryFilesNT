// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "PreservedTab.h"
#include "BrowserWindow.h"
#include "ShellBrowser/PreservedHistoryEntry.h"
#include "ShellBrowser/ShellBrowser.h"
#include "ShellBrowser/ShellNavigationController.h"

PreservedTab::PreservedTab(const Tab &tab, int index) :
	id(tab.GetId()),
	browserId(tab.GetBrowser()->GetId()),
	index(index),
	history(CopyHistoryEntries(tab)),
	currentEntry(tab.GetShellBrowser()->GetNavigationController()->GetCurrentIndex()),
	useCustomName(tab.GetUseCustomName()),
	customName(tab.GetUseCustomName() ? tab.GetName() : std::wstring()),
	lockState(tab.GetLockState()),
	preservedFolderState(tab.GetShellBrowser())
{
}

PreservedTab::~PreservedTab() = default;

std::vector<std::unique_ptr<PreservedHistoryEntry>> PreservedTab::CopyHistoryEntries(const Tab &tab)
{
	std::vector<std::unique_ptr<PreservedHistoryEntry>> history;

	for (int i = 0; i < tab.GetShellBrowser()->GetNavigationController()->GetNumHistoryEntries();
		 i++)
	{
		auto entry = std::make_unique<PreservedHistoryEntry>(
			tab.GetShellBrowser()->GetNavigationController()->GetEntryAtIndex(i)->GetPidl());
		history.push_back(std::move(entry));
	}

	return history;
}
