// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "Plugins/TabsApi/Events/TabCreated.h"
#include "Plugins/TabsApi/TabsApi.h"
#include "TabContainer.h"
#include <sol/sol.hpp>

Plugins::TabCreated::TabCreated(TabContainer *tabContainer) : m_tabContainer(tabContainer)
{
}

boost::signals2::connection Plugins::TabCreated::connectObserver(sol::protected_function observer,
	sol::this_state state)
{
	UNREFERENCED_PARAMETER(state);

	return m_tabContainer->tabCreatedSignal.AddObserver(
		[this, observer](int tabId, BOOL switchToNewTab)
		{
			UNREFERENCED_PARAMETER(switchToNewTab);

			onTabCreated(tabId, observer);
		});
}

void Plugins::TabCreated::onTabCreated(int tabId, sol::protected_function observer)
{
	const Tab &tabInternal = m_tabContainer->GetTab(tabId);

	TabsApi::Tab tab(tabInternal);
	observer(tab);
}
