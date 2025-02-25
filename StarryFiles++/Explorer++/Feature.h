// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "../Helper/BetterEnumsWrapper.h"

// clang-format off
BETTER_ENUM(Feature, int,
	DualPane,
	Plugins,

	// When enabled, the quick access folder in the treeview will be automatically updated.
	AutomaticQuickAccessUpdates,

	// When enabled, the application will allow multiple windows to be created and restored in each
	// session, rather than just a single window.
	MultipleWindowsPerSession
)
// clang-format on
