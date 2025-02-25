// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ThemedDialog.h"
#include "../Helper/DialogSettings.h"
#include <list>

namespace NSetFileAttributesDialogExternal
{
struct SetFileAttributesInfo
{
	TCHAR szFullFileName[MAX_PATH];
	WIN32_FIND_DATA wfd;
};
}

class SetFileAttributesDialog;

class SetFileAttributesDialogPersistentSettings : public DialogSettings
{
public:
	static SetFileAttributesDialogPersistentSettings &GetInstance();

private:
	friend SetFileAttributesDialog;

	static const TCHAR SETTINGS_KEY[];

	SetFileAttributesDialogPersistentSettings();

	SetFileAttributesDialogPersistentSettings(
		const SetFileAttributesDialogPersistentSettings &) = delete;
	SetFileAttributesDialogPersistentSettings &operator=(
		const SetFileAttributesDialogPersistentSettings &) = delete;
};

class SetFileAttributesDialog : public ThemedDialog
{
public:
	SetFileAttributesDialog(HINSTANCE resourceInstance, HWND hParent, ThemeManager *themeManager,
		const std::list<NSetFileAttributesDialogExternal::SetFileAttributesInfo> &sfaiList);

protected:
	INT_PTR OnInitDialog() override;
	INT_PTR OnCommand(WPARAM wParam, LPARAM lParam) override;
	INT_PTR OnNotify(NMHDR *pnmhdr) override;
	INT_PTR OnClose() override;

	void SaveState() override;

private:
	typedef struct
	{
		DWORD Attribute;
		UINT uControlId;
		UINT uChecked;
	} Attribute_t;

	enum class DateTimeType
	{
		Modified,
		Created,
		Accessed
	};

	void InitializeAttributesStructure();

	void ResetButtonState(HWND hwnd, BOOL bReset);
	void SetAttributeCheckState(HWND hwnd, int nAttributes, int nSelected);

	void InitializeDateFields();
	void OnDateReset(DateTimeType dateTimeType);
	void OnOk();
	void OnCancel();

	std::list<NSetFileAttributesDialogExternal::SetFileAttributesInfo> m_FileList;
	std::list<Attribute_t> m_AttributeList;

	SetFileAttributesDialogPersistentSettings *m_psfadps;

	SYSTEMTIME m_LocalWrite;
	SYSTEMTIME m_LocalCreation;
	SYSTEMTIME m_LocalAccess;

	BOOL m_bModificationDateEnabled;
	BOOL m_bCreationDateEnabled;
	BOOL m_bAccessDateEnabled;
};
