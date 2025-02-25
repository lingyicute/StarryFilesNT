// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "Plugins/Event.h"

class TabContainer;

namespace Plugins
{
class TabMoved : public Event
{
public:
	TabMoved(TabContainer *tabContainer);

protected:
	boost::signals2::connection connectObserver(sol::protected_function observer,
		sol::this_state state) override;

private:
	TabContainer *m_tabContainer;
};
}
