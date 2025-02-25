// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <Windows.h>

BOOL GetClusterSize(const TCHAR *drive, DWORD *pdwClusterSize);
TCHAR GetDriveLetterFromMask(ULONG unitmask);
