// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "WinRTBaseWrapper.h"
#include <oleidl.h>

class DropSourceImpl : public winrt::implements<DropSourceImpl, IDropSource, winrt::non_agile>
{
public:
	IFACEMETHODIMP QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState);
	IFACEMETHODIMP GiveFeedback(DWORD dwEffect);
};
