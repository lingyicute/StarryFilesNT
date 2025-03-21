// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ThemedDialog.h"
#include <wil/resource.h>

class AboutDialog : public ThemedDialog
{
public:
	AboutDialog(HINSTANCE resourceInstance, HWND hParent, ThemeManager *themeManager);

protected:
	INT_PTR OnInitDialog() override;
	INT_PTR OnCommand(WPARAM wParam, LPARAM lParam) override;
	INT_PTR OnNotify(NMHDR *pnmhdr) override;
	INT_PTR OnClose() override;

private:
	wil::unique_hicon m_icon;
	wil::unique_hicon m_mainIcon;
};
