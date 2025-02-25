// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <windows.h>
#include <vector>

// Mimics the ACCEL structure, but doesn't contain a cmd value. Used for
// times when an accelerator key combination is required by itself
// (without any associated command ID).
struct Accelerator
{
	BYTE modifiers;
	WORD key;
};

struct ShortcutKey
{
	int command;
	std::vector<Accelerator> accelerators;
};
