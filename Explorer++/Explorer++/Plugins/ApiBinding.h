// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "PluginInterface.h"
#include <sol/forward.hpp>

namespace Plugins
{
void BindAllApiMethods(int pluginId, sol::state &state, PluginInterface *pluginInterface);
}
