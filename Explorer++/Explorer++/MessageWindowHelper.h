// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <wil/resource.h>

namespace MessageWindowHelper
{

inline constexpr wchar_t MESSAGE_CLASS_NAME[] = L"Explorer++MessageClass";

wil::unique_hwnd CreateMessageOnlyWindow(const std::wstring &windowName = L"");

}
