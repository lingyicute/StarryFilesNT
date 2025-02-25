// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

enum ExitCode : int
{
	EXIT_CODE_NORMAL,
	EXIT_CODE_NORMAL_EXISTING_PROCESS,
	EXIT_CODE_NORMAL_CRASH_HANDLER,
	EXIT_CODE_ERROR
};
