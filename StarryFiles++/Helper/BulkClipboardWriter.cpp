// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "BulkClipboardWriter.h"

BulkClipboardWriter::BulkClipboardWriter()
{
	m_clipboard.Clear();
}

bool BulkClipboardWriter::WriteText(const std::wstring &str)
{
	return m_clipboard.WriteText(str);
}

bool BulkClipboardWriter::WriteCustomData(UINT format, const std::string &data)
{
	return m_clipboard.WriteCustomData(format, data);
}
