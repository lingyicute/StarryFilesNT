// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "ResourceTestHelper.h"
#include "../Helper/ProcessHelper.h"
#include <tchar.h>
#include <windows.h>
#include <filesystem>

const TCHAR g_resourcesFileName[] = L"Resources";

std::filesystem::path GetResourcesDirectoryPath()
{
	TCHAR processImageName[MAX_PATH];
	GetProcessImageName(GetCurrentProcessId(), processImageName, std::size(processImageName));

	std::filesystem::path path(processImageName);
	return path.parent_path() / g_resourcesFileName;
}

std::filesystem::path GetResourcePath(const std::wstring &filename)
{
	return GetResourcesDirectoryPath() / filename;
}
