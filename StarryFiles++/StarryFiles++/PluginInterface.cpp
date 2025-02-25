// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "StarryFiles++.h"

TabContainer *Starryfilesplusplus::GetTabContainer()
{
	return GetActivePane()->GetTabContainer();
}

Plugins::PluginMenuManager *Starryfilesplusplus::GetPluginMenuManager()
{
	return &m_pluginMenuManager;
}

UiTheming *Starryfilesplusplus::GetUiTheming()
{
	return m_uiTheming.get();
}

AcceleratorUpdater *Starryfilesplusplus::GetAccleratorUpdater()
{
	return &m_acceleratorUpdater;
}

Plugins::PluginCommandManager *Starryfilesplusplus::GetPluginCommandManager()
{
	return &m_pluginCommandManager;
}
