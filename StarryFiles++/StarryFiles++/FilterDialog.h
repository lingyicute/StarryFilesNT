// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ThemedDialog.h"
#include "../Helper/DialogSettings.h"
#include "../Helper/ResizableDialogHelper.h"
#include <MsXml2.h>
#include <objbase.h>

class CoreInterface;
class FilterDialog;
class IconResourceLoader;

class FilterDialogPersistentSettings : public DialogSettings
{
public:
	static FilterDialogPersistentSettings &GetInstance();

private:
	friend FilterDialog;

	static const TCHAR SETTINGS_KEY[];

	static const TCHAR SETTING_FILTER_LIST[];

	FilterDialogPersistentSettings();

	FilterDialogPersistentSettings(const FilterDialogPersistentSettings &);
	FilterDialogPersistentSettings &operator=(const FilterDialogPersistentSettings &);

	void SaveExtraRegistrySettings(HKEY hKey) override;
	void LoadExtraRegistrySettings(HKEY hKey) override;

	void SaveExtraXMLSettings(IXMLDOMDocument *pXMLDom, IXMLDOMElement *pParentNode) override;
	void LoadExtraXMLSettings(BSTR bstrName, BSTR bstrValue) override;

	std::list<std::wstring> m_FilterList;
};

class FilterDialog : public ThemedDialog
{
public:
	FilterDialog(HINSTANCE resourceInstance, HWND hParent, ThemeManager *themeManager,
		CoreInterface *coreInterface, const IconResourceLoader *iconResourceLoader);

protected:
	INT_PTR OnInitDialog() override;
	INT_PTR OnCommand(WPARAM wParam, LPARAM lParam) override;
	INT_PTR OnClose() override;

	virtual wil::unique_hicon GetDialogIcon(int iconWidth, int iconHeight) const override;

private:
	std::vector<ResizableDialogControl> GetResizableControls() override;
	void SaveState() override;

	void OnOk();
	void OnCancel();

	CoreInterface *m_coreInterface;
	const IconResourceLoader *const m_iconResourceLoader;

	FilterDialogPersistentSettings *m_persistentSettings;
};
