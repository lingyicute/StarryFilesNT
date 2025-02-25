// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "Storage.h"
#include "../Helper/ProcessHelper.h"
#include <filesystem>

namespace Storage
{

std::wstring GetConfigFilePath()
{
	wchar_t currentProcessPath[MAX_PATH];
	GetProcessImageName(GetCurrentProcessId(), currentProcessPath, std::size(currentProcessPath));

	std::filesystem::path configFilePath(currentProcessPath);
	configFilePath.replace_filename(CONFIG_FILE_FILENAME);

	return configFilePath.c_str();
}

}
