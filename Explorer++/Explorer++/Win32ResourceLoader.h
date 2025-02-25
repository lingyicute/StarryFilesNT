// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ResourceLoader.h"

// Loads a resource, using the Windows API resource functions.
class Win32ResourceLoader : public ResourceLoader
{
public:
	Win32ResourceLoader(HINSTANCE resourceInstance);

	std::wstring LoadString(UINT stringId) const override;

private:
	const HINSTANCE m_resourceInstance;
};
