// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <functional>

LONG DetourTransaction(std::function<LONG()> callback);
