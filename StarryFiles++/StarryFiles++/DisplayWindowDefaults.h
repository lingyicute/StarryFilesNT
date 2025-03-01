// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <windows.h>

namespace DisplayWindowDefaults
{

inline constexpr COLORREF CENTRE_COLOR = RGB(255, 255, 255);
inline constexpr COLORREF SURROUND_COLOR = RGB(0, 94, 138);
inline constexpr COLORREF TEXT_COLOR = RGB(0, 0, 0);
inline const LOGFONT FONT = { -13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
	OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"" };

}
