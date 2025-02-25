// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "RebarView.h"

class MainRebarView : public RebarView
{
public:
	static MainRebarView *Create(HWND parent);

private:
	MainRebarView(HWND parent);
};
