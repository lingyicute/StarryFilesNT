// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "Plugins/Event.h"
#include "Plugins/PluginCommandManager.h"

namespace Plugins
{
class CommandInvoked : public Event
{
public:
	CommandInvoked(PluginCommandManager *pluginCommandManager, int pluginId);

protected:
	boost::signals2::connection connectObserver(sol::protected_function observer,
		sol::this_state state) override;

private:
	void onCommandInvoked(int pluginId, const std::wstring &name, sol::protected_function observer);

	PluginCommandManager *m_pluginCommandManager;
	int m_pluginId;
};
}
