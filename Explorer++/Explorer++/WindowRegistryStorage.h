// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <vector>

struct WindowStorageData;

namespace WindowRegistryStorage
{

std::vector<WindowStorageData> Load(HKEY applicationKey);
void Save(HKEY applicationKey, const std::vector<WindowStorageData> &windows);

}
