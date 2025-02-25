// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ToolbarView.h"

class DrivesToolbarView : public ToolbarView
{
public:
	static DrivesToolbarView *Create(HWND parent, const Config *config);

private:
	DrivesToolbarView(HWND parent, const Config *config);
};
