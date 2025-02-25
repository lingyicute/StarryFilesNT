// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ShellItemsMenu.h"
#include <boost/signals2.hpp>
#include <vector>

class FrequentLocationsModel;

class FrequentLocationsMenu : public ShellItemsMenu
{
public:
	FrequentLocationsMenu(MenuView *menuView, const AcceleratorManager *acceleratorManager,
		FrequentLocationsModel *frequentLocationsModel, BrowserWindow *browserWindow,
		ShellIconLoader *shellIconLoader, UINT startId = DEFAULT_START_ID,
		UINT endId = DEFAULT_END_ID);

private:
	static constexpr int MAX_MENU_ITEMS = 10;

	void OnLocationsChanged();
	static std::vector<PidlAbsolute> GetLocations(
		const FrequentLocationsModel *frequentLocationsModel);

	FrequentLocationsModel *const m_frequentLocationsModel;
	std::vector<boost::signals2::scoped_connection> m_connections;
};
