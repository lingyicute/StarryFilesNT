// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "../Helper/BaseDialog.h"

class ThemeManager;
class ThemeWindowTracker;

class ThemedDialog : public BaseDialog
{
public:
	ThemedDialog(HINSTANCE resourceInstance, int dialogResourceId, HWND parent,
		DialogSizingType dialogSizingType, ThemeManager *themeManager);
	~ThemedDialog();

protected:
	ThemeManager *GetThemeManager() const;

private:
	void OnInitDialogBase() override final;

	ThemeManager *const m_themeManager;
	std::unique_ptr<ThemeWindowTracker> m_themeWindowTracker;
};
