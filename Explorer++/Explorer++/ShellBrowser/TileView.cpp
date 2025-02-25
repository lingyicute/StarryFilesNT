// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "ShellBrowserImpl.h"
#include "Config.h"

void ShellBrowserImpl::InsertTileViewColumns()
{
	LVCOLUMN lvColumn;
	lvColumn.mask = 0;

	/* Name. */
	ListView_InsertColumn(m_hListView, 1, &lvColumn);

	/* Type. */
	ListView_InsertColumn(m_hListView, 2, &lvColumn);

	/* File size. */
	ListView_InsertColumn(m_hListView, 3, &lvColumn);

	LVTILEVIEWINFO lvtvi;
	lvtvi.cbSize = sizeof(lvtvi);
	lvtvi.dwMask = LVTVIM_COLUMNS;
	lvtvi.dwFlags = LVTVIF_AUTOSIZE;
	lvtvi.cLines = 2;
	ListView_SetTileViewInfo(m_hListView, &lvtvi);
}

void ShellBrowserImpl::SetTileViewInfo()
{
	LVITEM lvItem;
	BOOL bRes;
	int nItems;
	int i = 0;

	nItems = ListView_GetItemCount(m_hListView);

	for (i = 0; i < nItems; i++)
	{
		lvItem.mask = LVIF_PARAM;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		bRes = ListView_GetItem(m_hListView, &lvItem);

		if (bRes)
		{
			SetTileViewItemInfo(i, (int) lvItem.lParam);
		}
	}
}

/* TODO: Make this function configurable. */
void ShellBrowserImpl::SetTileViewItemInfo(int iItem, int iItemInternal)
{
	SHFILEINFO shfi;
	LVTILEINFO lvti;
	UINT uColumns[2] = { 1, 2 };
	int columnFormats[2] = { LVCFMT_LEFT, LVCFMT_LEFT };

	lvti.cbSize = sizeof(lvti);
	lvti.iItem = iItem;
	lvti.cColumns = 2;
	lvti.puColumns = uColumns;
	lvti.piColFmt = columnFormats;
	ListView_SetTileInfo(m_hListView, &lvti);

	std::wstring fullFileName = GetItemFullName(iItem);

	SHGetFileInfo(fullFileName.c_str(), 0, &shfi, sizeof(SHFILEINFO), SHGFI_TYPENAME);

	ListView_SetItemText(m_hListView, iItem, 1, shfi.szTypeName);

	if ((m_itemInfoMap.at(iItemInternal).wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		!= FILE_ATTRIBUTE_DIRECTORY)
	{
		ULARGE_INTEGER fileSize = { m_itemInfoMap.at(iItemInternal).wfd.nFileSizeLow,
			m_itemInfoMap.at(iItemInternal).wfd.nFileSizeHigh };

		auto displayFormat = m_config->globalFolderSettings.forceSize
			? m_config->globalFolderSettings.sizeDisplayFormat
			: +SizeDisplayFormat::None;
		std::wstring fileSizeText = FormatSizeString(fileSize.QuadPart, displayFormat);
		ListView_SetItemText(m_hListView, iItem, 2, fileSizeText.data());
	}
}
