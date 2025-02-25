// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

struct Config;

namespace ConfigRegistryStorage
{

void Load(HKEY applicationKey, Config &config);
void Save(HKEY applicationKey, const Config &config);

}
