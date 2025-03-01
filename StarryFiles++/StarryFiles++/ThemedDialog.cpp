// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "ThemedDialog.h"
#include "ThemeManager.h"
#include "ThemeWindowTracker.h"
#include "NoTranslationResource.h"

ThemedDialog::ThemedDialog(HINSTANCE resourceInstance, int dialogResourceId, HWND parent,
	DialogSizingType dialogSizingType, ThemeManager *themeManager) :
	BaseDialog(resourceInstance, dialogResourceId, parent, dialogSizingType),
	m_themeManager(themeManager)
{
}

ThemedDialog::~ThemedDialog() = default;

void ThemedDialog::OnInitDialogBase()
{
	m_themeWindowTracker = std::make_unique<ThemeWindowTracker>(m_hDlg, m_themeManager);
}

ThemeManager *ThemedDialog::GetThemeManager() const
{
	return m_themeManager;
}

wil::unique_hicon ThemedDialog::GetDialogIcon(int iconWidth, int iconHeight) const
{
	UNREFERENCED_PARAMETER(iconWidth);
	UNREFERENCED_PARAMETER(iconHeight);

	return wil::unique_hicon(LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_MAIN)));
}
