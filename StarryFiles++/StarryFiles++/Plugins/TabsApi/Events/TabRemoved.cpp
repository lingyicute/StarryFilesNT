// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "Plugins/TabsApi/Events/TabRemoved.h"
#include "TabContainer.h"
#include <sol/sol.hpp>

Plugins::TabRemoved::TabRemoved(TabContainer *tabContainer) : m_tabContainer(tabContainer)
{
}

boost::signals2::connection Plugins::TabRemoved::connectObserver(sol::protected_function observer,
	sol::this_state state)
{
	UNREFERENCED_PARAMETER(state);

	return m_tabContainer->tabRemovedSignal.AddObserver(observer);
}
