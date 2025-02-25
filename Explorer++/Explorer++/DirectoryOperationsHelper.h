// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "../Helper/ClipboardHelper.h"

bool CanPasteInDirectory(PCIDLIST_ABSOLUTE pidl, PasteType pasteType);
bool CanCreateInDirectory(PCIDLIST_ABSOLUTE pidl);
bool CanCustomizeDirectory(PCIDLIST_ABSOLUTE pidl);
bool IsFilesystemFolder(PCIDLIST_ABSOLUTE pidl);
