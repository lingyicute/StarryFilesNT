// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

struct FolderInfo
{
	std::uintmax_t size;
	int numFolders;
	int numFiles;
};

FolderInfo GetFolderInfo(const std::wstring &path);

typedef struct
{
	TCHAR szPath[MAX_PATH];
	LPVOID pData;
	void (*pfnCallback)(int nFolders, int nFiles, PULARGE_INTEGER lTotalFolderSize, LPVOID pData);
} FolderSize_t;

DWORD WINAPI Thread_CalculateFolderSize(LPVOID lpParameter);
