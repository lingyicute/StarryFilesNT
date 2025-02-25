// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "StarryFiles++.h"

TabContainer *Explorerplusplus::GetTabContainer()
{
	return GetActivePane()->GetTabContainer();
}

Plugins::PluginMenuManager *Explorerplusplus::GetPluginMenuManager()
{
	return &m_pluginMenuManager;
}

UiTheming *Explorerplusplus::GetUiTheming()
{
	return m_uiTheming.get();
}

AcceleratorUpdater *Explorerplusplus::GetAccleratorUpdater()
{
	return &m_acceleratorUpdater;
}

Plugins::PluginCommandManager *Explorerplusplus::GetPluginCommandManager()
{
	return &m_pluginCommandManager;
}
