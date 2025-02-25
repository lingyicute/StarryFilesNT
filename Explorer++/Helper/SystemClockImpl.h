// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "SystemClock.h"

class SystemClockImpl : public SystemClock
{
public:
	TimePoint Now() override;
};
