// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "HistoryShellBrowserHelper.h"
#include "HistoryModel.h"

HistoryShellBrowserHelper::HistoryShellBrowserHelper(ShellBrowser *shellBrowser,
	HistoryModel *historyModel) :
	ShellBrowserHelper(shellBrowser),
	m_historyModel(historyModel)
{
	// There's no need to explicitly remove this observer, since this object is tied to the
	// lifetime of the shellBrowser instance.
	shellBrowser->AddNavigationCommittedObserver(
		std::bind_front(&HistoryShellBrowserHelper::OnNavigationCommitted, this));
}

void HistoryShellBrowserHelper::OnNavigationCommitted(const NavigateParams &navigateParams)
{
	m_historyModel->AddHistoryItem(navigateParams.pidl);
}
