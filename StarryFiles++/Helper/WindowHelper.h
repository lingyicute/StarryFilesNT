// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <wil/resource.h>

BOOL CenterWindow(HWND hParent, HWND hChild);
std::wstring GetDlgItemString(HWND dlg, int controlId);
std::wstring GetWindowString(HWND hwnd);
BOOL lShowWindow(HWND hwnd, BOOL bShowWindow);
void AddWindowStyles(HWND hwnd, LONG_PTR styles, bool add);
int GetRectHeight(const RECT *rc);
int GetRectWidth(const RECT *rc);
bool BringWindowToForeground(HWND wnd);
bool IsRectVisible(const RECT *rect);

// This is only used in tests.
bool operator==(const RECT &first, const RECT &second);
