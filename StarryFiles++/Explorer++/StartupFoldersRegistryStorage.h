// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <string>
#include <vector>

namespace StartupFoldersRegistryStorage
{

std::vector<std::wstring> Load(HKEY startupFoldersKey);
void Save(HKEY startupFoldersKey, const std::vector<std::wstring> &startupFolders);

}
