// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <string>

class BookmarkTree;

namespace BookmarkRegistryStorage
{

void Load(HKEY applicationKey, BookmarkTree *bookmarkTree);
void Save(HKEY applicationKey, const BookmarkTree *bookmarkTree);

}
