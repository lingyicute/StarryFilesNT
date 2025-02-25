// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "MainMenuSubMenuView.h"
#include "../Helper/MenuHelper.h"

MainMenuSubMenuView::MainMenuSubMenuView(HMENU mainMenu, UINT subMenuItemId)
{
	// This menu will be added as a submenu of the main menu. The main menu will therefore assume
	// ownership of the submenu and will be responsible for deleting it. So, only a non-owning
	// handle to the menu is stored.
	wil::unique_hmenu menu(CreatePopupMenu());
	m_menu = menu.get();

	MenuHelper::AttachSubMenu(mainMenu, std::move(menu), subMenuItemId, false);
}

HMENU MainMenuSubMenuView::GetMenu() const
{
	return m_menu;
}
