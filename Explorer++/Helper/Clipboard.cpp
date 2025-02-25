// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "Clipboard.h"
#include "DataExchangeHelper.h"

Clipboard::Clipboard() : m_clipboardOpened(false)
{
	if (OpenClipboard(nullptr))
	{
		m_clipboardOpened = true;
	}
}

Clipboard::~Clipboard()
{
	if (m_clipboardOpened)
	{
		CloseClipboard();
	}
}

std::optional<std::wstring> Clipboard::ReadText()
{
	HANDLE clipboardData = GetClipboardData(CF_UNICODETEXT);

	if (!clipboardData)
	{
		return std::nullopt;
	}

	return ReadStringFromGlobal(clipboardData);
}

std::optional<std::vector<std::wstring>> Clipboard::ReadHDropData()
{
	HANDLE clipboardData = GetClipboardData(CF_HDROP);

	if (!clipboardData)
	{
		return std::nullopt;
	}

	return ReadHDropDataFromGlobal(clipboardData);
}

std::unique_ptr<Gdiplus::Bitmap> Clipboard::ReadPng()
{
	HANDLE clipboardData = GetClipboardData(GetPngClipboardFormat());

	if (!clipboardData)
	{
		return nullptr;
	}

	return ReadPngDataFromGlobal(clipboardData);
}

std::unique_ptr<Gdiplus::Bitmap> Clipboard::ReadDIB()
{
	HANDLE clipboardData = GetClipboardData(CF_DIB);

	if (!clipboardData)
	{
		return nullptr;
	}

	return ReadDIBDataFromGlobal(clipboardData);
}

std::optional<std::string> Clipboard::ReadCustomData(UINT format)
{
	HANDLE clipboardData = GetClipboardData(format);

	if (!clipboardData)
	{
		return std::nullopt;
	}

	return ReadBinaryDataFromGlobal(clipboardData);
}

bool Clipboard::WriteText(const std::wstring &str)
{
	auto global = WriteStringToGlobal(str);

	if (!global)
	{
		return false;
	}

	return WriteDataToClipboard(CF_UNICODETEXT, std::move(global));
}

bool Clipboard::WriteHDropData(const std::vector<std::wstring> &paths)
{
	auto global = WriteHDropDataToGlobal(paths);

	if (!global)
	{
		return false;
	}

	return WriteDataToClipboard(CF_HDROP, std::move(global));
}

bool Clipboard::WritePng(Gdiplus::Bitmap *bitmap)
{
	auto global = WritePngDataToGlobal(bitmap);

	if (!global)
	{
		return false;
	}

	return WriteDataToClipboard(GetPngClipboardFormat(), std::move(global));
}

bool Clipboard::WriteDIB(Gdiplus::Bitmap *bitmap)
{
	auto global = WriteDIBDataToGlobal(bitmap);

	if (!global)
	{
		return false;
	}

	return WriteDataToClipboard(CF_DIB, std::move(global));
}

bool Clipboard::WriteCustomData(UINT format, const std::string &data)
{
	auto global = WriteBinaryDataToGlobal(data);

	if (!global)
	{
		return false;
	}

	return WriteDataToClipboard(format, std::move(global));
}

bool Clipboard::WriteDataToClipboard(UINT format, wil::unique_hglobal global)
{
	HANDLE clipboardData = SetClipboardData(format, global.get());

	if (!clipboardData)
	{
		return false;
	}

	// SetClipboardData() takes ownership of the data passed to it. Therefore,
	// it's important that the ownership of the data is relinquished here if the
	// call to SetClipboardData() succeeded.
	global.release();

	return true;
}

bool Clipboard::Clear()
{
	return EmptyClipboard();
}
