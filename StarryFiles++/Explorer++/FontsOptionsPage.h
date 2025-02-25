// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "OptionsPage.h"
#include <wil/resource.h>
#include <memory>
#include <set>
#include <string>

class FontsOptionsPage : public OptionsPage
{
public:
	FontsOptionsPage(HWND parent, HINSTANCE resourceInstance, Config *config,
		CoreInterface *coreInterface, SettingChangedCallback settingChangedCallback,
		HWND tooltipWindow);

	void SaveSettings() override;

private:
	std::unique_ptr<ResizableDialogHelper> InitializeResizeDialogHelper() override;

	void InitializeControls() override;
	void InitializeFontsControl();
	std::set<std::wstring> EnumerateUniqueFonts();
	static int CALLBACK EnumFontFamiliesExCallback(const LOGFONT *logFont,
		const TEXTMETRIC *textMetric, DWORD fontType, LPARAM lParam);
	void InitializeSizeControl();
	void InitializeSampleControl();
	void UpdateSampleWindow();

	INT_PTR DialogProcExtra(HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam) override;
	void OnDpiChanged();

	void OnCommand(WPARAM wParam, LPARAM lParam) override;
	void OnFontSelectionChanged();
	void OnResetToDefault();

	wil::unique_hfont m_sampleFont;
	LOGFONT m_systemLogFont;
	int m_defaultItemIndex;
};
