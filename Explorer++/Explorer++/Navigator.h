// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "NavigationHelper.h"
#include <shtypes.h>
#include <string>

class Navigator
{
public:
	virtual ~Navigator() = default;

	virtual void OpenDefaultItem(OpenFolderDisposition openFolderDisposition) = 0;

	void OpenDefaultItem()
	{
		OpenDefaultItem(OpenFolderDisposition::CurrentTab);
	}

	virtual void OpenItem(const std::wstring &itemPath,
		OpenFolderDisposition openFolderDisposition) = 0;

	void OpenItem(const std::wstring &itemPath)
	{
		OpenItem(itemPath, OpenFolderDisposition::CurrentTab);
	}

	virtual void OpenItem(PCIDLIST_ABSOLUTE pidlItem,
		OpenFolderDisposition openFolderDisposition) = 0;

	void OpenItem(PCIDLIST_ABSOLUTE pidlItem)
	{
		OpenItem(pidlItem, OpenFolderDisposition::CurrentTab);
	}
};
