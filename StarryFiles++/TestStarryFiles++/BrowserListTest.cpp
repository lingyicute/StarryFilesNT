// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "BrowserList.h"
#include "BrowserWindowMock.h"
#include "GeneratorTestHelper.h"
#include <gtest/gtest.h>

using namespace testing;

class BrowserListTest : public Test
{
protected:
	BrowserList m_browserList;
};

TEST_F(BrowserListTest, IsEmpty)
{
	EXPECT_TRUE(m_browserList.IsEmpty());

	BrowserWindowMock browser;
	m_browserList.AddBrowser(&browser);
	EXPECT_FALSE(m_browserList.IsEmpty());

	m_browserList.RemoveBrowser(&browser);
	EXPECT_TRUE(m_browserList.IsEmpty());
}

TEST_F(BrowserListTest, AddRemoveBrowser)
{
	BrowserWindowMock browser1;
	m_browserList.AddBrowser(&browser1);
	EXPECT_THAT(GeneratorToVector(m_browserList.GetList()), UnorderedElementsAre(&browser1));

	BrowserWindowMock browser2;
	m_browserList.AddBrowser(&browser2);
	EXPECT_THAT(GeneratorToVector(m_browserList.GetList()),
		UnorderedElementsAre(&browser1, &browser2));

	m_browserList.RemoveBrowser(&browser1);
	EXPECT_THAT(GeneratorToVector(m_browserList.GetList()), UnorderedElementsAre(&browser2));

	m_browserList.RemoveBrowser(&browser2);
	EXPECT_THAT(GeneratorToVector(m_browserList.GetList()), IsEmpty());
}

TEST_F(BrowserListTest, AddedSignal)
{
	MockFunction<void(BrowserWindow *)> callback;
	m_browserList.browserAddedSignal.AddObserver(callback.AsStdFunction());

	BrowserWindowMock browser1;
	EXPECT_CALL(callback, Call(&browser1));
	m_browserList.AddBrowser(&browser1);

	BrowserWindowMock browser2;
	EXPECT_CALL(callback, Call(&browser2));
	m_browserList.AddBrowser(&browser2);
}

TEST_F(BrowserListTest, RemovedSignals)
{
	MockFunction<void(BrowserWindow *)> willRemoveCallback;
	m_browserList.willRemoveBrowserSignal.AddObserver(willRemoveCallback.AsStdFunction());

	MockFunction<void(BrowserWindow *)> removedCallback;
	m_browserList.browserRemovedSignal.AddObserver(removedCallback.AsStdFunction());

	BrowserWindowMock browser1;
	BrowserWindowMock browser2;
	m_browserList.AddBrowser(&browser1);
	m_browserList.AddBrowser(&browser2);

	{
		InSequence seq;

		EXPECT_CALL(willRemoveCallback, Call(&browser1));
		EXPECT_CALL(removedCallback, Call(&browser1));
	}
	m_browserList.RemoveBrowser(&browser1);

	{
		InSequence seq;

		EXPECT_CALL(willRemoveCallback, Call(&browser2));
		EXPECT_CALL(removedCallback, Call(&browser2));
	}
	m_browserList.RemoveBrowser(&browser2);
}

TEST_F(BrowserListTest, LastActive)
{
	EXPECT_THAT(m_browserList.GetLastActive(), IsNull());

	BrowserWindowMock browser1;
	BrowserWindowMock browser2;
	BrowserWindowMock browser3;
	m_browserList.AddBrowser(&browser1);
	m_browserList.AddBrowser(&browser2);
	m_browserList.AddBrowser(&browser3);

	m_browserList.SetLastActive(&browser1);
	EXPECT_EQ(m_browserList.GetLastActive(), &browser1);

	m_browserList.SetLastActive(&browser2);
	EXPECT_EQ(m_browserList.GetLastActive(), &browser2);

	m_browserList.RemoveBrowser(&browser2);
	EXPECT_EQ(m_browserList.GetLastActive(), &browser1);

	m_browserList.SetLastActive(&browser3);
	EXPECT_EQ(m_browserList.GetLastActive(), &browser3);

	m_browserList.RemoveBrowser(&browser1);
	EXPECT_EQ(m_browserList.GetLastActive(), &browser3);

	BrowserWindowMock browser4;
	EXPECT_CALL(browser4, IsActive()).WillOnce(Return(true));
	m_browserList.AddBrowser(&browser4);
	EXPECT_EQ(m_browserList.GetLastActive(), &browser4);
}

TEST_F(BrowserListTest, MaybeGetById)
{
	BrowserWindowMock browser1;
	BrowserWindowMock browser2;
	m_browserList.AddBrowser(&browser1);
	m_browserList.AddBrowser(&browser2);

	auto *retrievedBrowser = m_browserList.MaybeGetById(browser1.GetId());
	EXPECT_EQ(retrievedBrowser, &browser1);

	retrievedBrowser = m_browserList.MaybeGetById(browser2.GetId());
	EXPECT_EQ(retrievedBrowser, &browser2);

	retrievedBrowser = m_browserList.MaybeGetById(100);
	EXPECT_EQ(retrievedBrowser, nullptr);
}

TEST_F(BrowserListTest, GetSize)
{
	EXPECT_EQ(m_browserList.GetSize(), 0u);

	BrowserWindowMock browser1;
	m_browserList.AddBrowser(&browser1);
	EXPECT_EQ(m_browserList.GetSize(), 1u);

	BrowserWindowMock browser2;
	m_browserList.AddBrowser(&browser2);
	EXPECT_EQ(m_browserList.GetSize(), 2u);

	m_browserList.RemoveBrowser(&browser2);
	EXPECT_EQ(m_browserList.GetSize(), 1u);

	m_browserList.RemoveBrowser(&browser1);
	EXPECT_EQ(m_browserList.GetSize(), 0u);
}
