// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "../Helper/Helper.h"
#include <gtest/gtest.h>

TEST(BuildFileAttributesString, Empty)
{
	auto attributesString = BuildFileAttributesString(0);
	EXPECT_EQ(attributesString, L"---------");
}

TEST(BuildFileAttributesString, Simple)
{
	auto attributesString =
		BuildFileAttributesString(FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN);
	EXPECT_EQ(attributesString, L"AH-------");

	attributesString =
		BuildFileAttributesString(FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_COMPRESSED);
	EXPECT_EQ(attributesString, L"----DC---");
}

TEST(BuildFileAttributesString, All)
{
	auto attributesString = BuildFileAttributesString(FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_DIRECTORY
		| FILE_ATTRIBUTE_COMPRESSED | FILE_ATTRIBUTE_SPARSE_FILE | FILE_ATTRIBUTE_ENCRYPTED
		| FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
	EXPECT_EQ(attributesString, L"AHRSDCPEI");
}

TEST(IsProcessRTL, CheckValue)
{
	// The layout will be LTR by default.
	EXPECT_EQ(IsProcessRTL(), false);

	SetProcessDefaultLayout(LAYOUT_RTL);
	EXPECT_EQ(IsProcessRTL(), true);
}
