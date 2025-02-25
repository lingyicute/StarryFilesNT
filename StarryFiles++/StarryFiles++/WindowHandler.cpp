// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "StarryFiles++.h"
#include "Config.h"
#include "HolderWindow.h"
#include "../Helper/WindowHelper.h"

void Starryfilesplusplus::ToggleFolders()
{
	m_config->showFolders = !m_config->showFolders.get();
	lShowWindow(m_treeViewHolder->GetHWND(), m_config->showFolders.get());
	UpdateLayout();
}

void Starryfilesplusplus::ToggleDualPane()
{
	m_config->dualPane = !m_config->dualPane;
}
