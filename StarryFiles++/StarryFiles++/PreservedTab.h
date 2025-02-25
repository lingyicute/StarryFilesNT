// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ShellBrowser/PreservedFolderState.h"
#include "Tab.h"
#include <boost/core/noncopyable.hpp>

class PreservedHistoryEntry;

struct PreservedTab : private boost::noncopyable
{
	PreservedTab(const Tab &tab, int index);
	~PreservedTab();

	int id;
	int browserId;
	int index;

	std::vector<std::unique_ptr<PreservedHistoryEntry>> history;
	int currentEntry;

	bool useCustomName;
	std::wstring customName;
	Tab::LockState lockState;

	PreservedFolderState preservedFolderState;

private:
	static std::vector<std::unique_ptr<PreservedHistoryEntry>> CopyHistoryEntries(const Tab &tab);
};
