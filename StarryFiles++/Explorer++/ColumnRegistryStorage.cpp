// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "ColumnRegistryStorage.h"
#include "ShellBrowser/FolderSettings.h"
#include "../Helper/RegistrySettings.h"

namespace ColumnRegistryStorage
{

namespace
{

const wchar_t REAL_FOLDER_COLUMNS_KEY_NAME[] = L"RealFolderColumns";
const wchar_t REAL_FOLDER_COLUMN_WIDTHS_KEY_NAME[] = L"RealFolderColumnWidths";
const wchar_t MY_COMPUTER_COLUMNS_KEY_NAME[] = L"MyComputerColumns";
const wchar_t MY_COMPUTER_COLUMN_WIDTHS_KEY_NAME[] = L"MyComputerColumnWidths";
const wchar_t CONTROL_PANEL_COLUMNS_KEY_NAME[] = L"ControlPanelColumns";
const wchar_t CONTROL_PANEL_COLUMN_WIDTHS_KEY_NAME[] = L"ControlPanelColumnWidths";
const wchar_t RECYCLE_BIN_COLUMNS_KEY_NAME[] = L"RecycleBinColumns";
const wchar_t RECYCLE_BIN_COLUMN_WIDTHS_KEY_NAME[] = L"RecycleBinColumnWidths";
const wchar_t PRINTERS_COLUMNS_KEY_NAME[] = L"PrinterColumns";
const wchar_t PRINTERS_COLUMN_WIDTHS_KEY_NAME[] = L"PrinterColumnWidths";
const wchar_t NETWORK_COLUMNS_KEY_NAME[] = L"NetworkColumns";
const wchar_t NETWORK_COLUMN_WIDTHS_KEY_NAME[] = L"NetworkColumnWidths";
const wchar_t NETWORK_PLACES_COLUMNS_KEY_NAME[] = L"NetworkPlacesColumns";
const wchar_t NETWORK_PLACES_COLUMN_WIDTHS_KEY_NAME[] = L"NetworkPlacesColumnWidths";

// For compatibility with past versions, columns and their widths are saved independently. That's
// the reason for this struct and the one below. They represent column data, as it's stored in the
// registry.
struct SavedColumn
{
	unsigned int type;
	BOOL checked;

	SavedColumn() = default;

	SavedColumn(const Column_t &column) : type(column.type._to_integral()), checked(column.checked)
	{
	}
};

static_assert(std::is_trivially_copyable_v<SavedColumn>);
static_assert(std::is_trivially_constructible_v<SavedColumn>);

struct SavedColumnWidth
{
	unsigned int type;
	int width;

	SavedColumnWidth() = default;

	SavedColumnWidth(const Column_t &column) : type(column.type._to_integral()), width(column.width)
	{
	}
};

static_assert(std::is_trivially_copyable_v<SavedColumnWidth>);
static_assert(std::is_trivially_constructible_v<SavedColumnWidth>);

void LoadColumnSet(HKEY parentKey, const std::wstring &columnsKeyName,
	const std::wstring &columnWidthsKeyName, std::vector<Column_t> &outputColumnSet)
{
	std::vector<SavedColumn> savedColumns;
	auto res = RegistrySettings::ReadVectorFromBinaryValue(parentKey, columnsKeyName, savedColumns);

	if (res != ERROR_SUCCESS)
	{
		return;
	}

	std::vector<SavedColumnWidth> savedColumnWidths;
	res = RegistrySettings::ReadVectorFromBinaryValue(parentKey, columnWidthsKeyName,
		savedColumnWidths);

	if (res != ERROR_SUCCESS)
	{
		return;
	}

	std::vector<Column_t> columns;

	for (const auto &savedColumn : savedColumns)
	{
		auto columnType = ColumnType::_from_integral_nothrow(savedColumn.type);

		if (!columnType)
		{
			continue;
		}

		Column_t column;
		column.type = *columnType;
		column.checked = savedColumn.checked;
		column.width = DEFAULT_COLUMN_WIDTH;

		auto itr = std::find_if(savedColumnWidths.begin(), savedColumnWidths.end(),
			[&savedColumn](const SavedColumnWidth &savedColumnWidth)
			{ return savedColumnWidth.type == savedColumn.type; });

		if (itr != savedColumnWidths.end())
		{
			column.width = itr->width;
		}

		columns.push_back(column);
	}

	if (columns.empty())
	{
		return;
	}

	outputColumnSet = columns;
}

void SaveColumnSet(HKEY parentKey, const std::wstring &columnsKeyName,
	const std::wstring &columnWidthsKeyName, const std::vector<Column_t> &columnSet)
{
	std::vector<SavedColumn> savedColumns(columnSet.begin(), columnSet.end());
	RegistrySettings::SaveVectorToBinaryValue(parentKey, columnsKeyName, savedColumns);

	std::vector<SavedColumnWidth> savedColumnWidths(columnSet.begin(), columnSet.end());
	RegistrySettings::SaveVectorToBinaryValue(parentKey, columnWidthsKeyName, savedColumnWidths);
}

}

void LoadAllColumnSets(HKEY parentKey, FolderColumns &folderColumns)
{
	LoadColumnSet(parentKey, REAL_FOLDER_COLUMNS_KEY_NAME, REAL_FOLDER_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.realFolderColumns);
	LoadColumnSet(parentKey, MY_COMPUTER_COLUMNS_KEY_NAME, MY_COMPUTER_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.myComputerColumns);
	LoadColumnSet(parentKey, CONTROL_PANEL_COLUMNS_KEY_NAME, CONTROL_PANEL_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.controlPanelColumns);
	LoadColumnSet(parentKey, RECYCLE_BIN_COLUMNS_KEY_NAME, RECYCLE_BIN_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.recycleBinColumns);
	LoadColumnSet(parentKey, PRINTERS_COLUMNS_KEY_NAME, PRINTERS_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.printersColumns);
	LoadColumnSet(parentKey, NETWORK_COLUMNS_KEY_NAME, NETWORK_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.networkConnectionsColumns);
	LoadColumnSet(parentKey, NETWORK_PLACES_COLUMNS_KEY_NAME, NETWORK_PLACES_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.myNetworkPlacesColumns);
}

void SaveAllColumnSets(HKEY parentKey, const FolderColumns &folderColumns)
{
	SaveColumnSet(parentKey, REAL_FOLDER_COLUMNS_KEY_NAME, REAL_FOLDER_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.realFolderColumns);
	SaveColumnSet(parentKey, MY_COMPUTER_COLUMNS_KEY_NAME, MY_COMPUTER_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.myComputerColumns);
	SaveColumnSet(parentKey, CONTROL_PANEL_COLUMNS_KEY_NAME, CONTROL_PANEL_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.controlPanelColumns);
	SaveColumnSet(parentKey, RECYCLE_BIN_COLUMNS_KEY_NAME, RECYCLE_BIN_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.recycleBinColumns);
	SaveColumnSet(parentKey, PRINTERS_COLUMNS_KEY_NAME, PRINTERS_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.printersColumns);
	SaveColumnSet(parentKey, NETWORK_COLUMNS_KEY_NAME, NETWORK_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.networkConnectionsColumns);
	SaveColumnSet(parentKey, NETWORK_PLACES_COLUMNS_KEY_NAME, NETWORK_PLACES_COLUMN_WIDTHS_KEY_NAME,
		folderColumns.myNetworkPlacesColumns);
}

}
