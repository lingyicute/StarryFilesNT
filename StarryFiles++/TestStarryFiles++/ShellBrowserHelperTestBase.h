// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ShellBrowserFake.h"
#include "TabNavigationMock.h"
#include <gtest/gtest.h>

template <class T>
concept DerivedShellBrowserHelper = std::is_base_of_v<ShellBrowserHelperBase, T>;

template <DerivedShellBrowserHelper Helper>
class ShellBrowserHelperTestBase : public testing::Test
{
protected:
	template <typename... Args>
	std::unique_ptr<ShellBrowserFake> CreateTab(Args &&...args)
	{
		auto shellBrowser = std::make_unique<ShellBrowserFake>(&m_tabNavigation);
		Helper::CreateAndAttachToShellBrowser(shellBrowser.get(), std::forward<Args>(args)...);
		return shellBrowser;
	}

	TabNavigationMock m_tabNavigation;
};
