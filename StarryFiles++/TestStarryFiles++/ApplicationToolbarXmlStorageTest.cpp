// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "ApplicationToolbarXmlStorage.h"
#include "Application.h"
#include "ApplicationModel.h"
#include "ApplicationToolbarStorageTestHelper.h"
#include "MovableModelHelper.h"
#include "ResourceTestHelper.h"
#include "XmlStorageTestHelper.h"
#include <gtest/gtest.h>

using namespace Applications;
using namespace testing;

class ApplicationToolbarXmlStorageTest : public XmlStorageTest
{
};

TEST_F(ApplicationToolbarXmlStorageTest, Load)
{
	ApplicationModel referenceModel;
	BuildLoadSaveReferenceModel(&referenceModel);

	std::wstring xmlFilePath = GetResourcePath(L"application-toolbar-config.xml");
	auto xmlDocumentData = LoadXmlDocument(xmlFilePath);

	ApplicationModel loadedModel;
	ApplicationToolbarXmlStorage::Load(xmlDocumentData.rootNode.get(), &loadedModel);

	EXPECT_EQ(loadedModel, referenceModel);
}

TEST_F(ApplicationToolbarXmlStorageTest, Save)
{
	ApplicationModel referenceModel;
	BuildLoadSaveReferenceModel(&referenceModel);

	auto xmlDocumentData = CreateXmlDocument();

	ApplicationToolbarXmlStorage::Save(xmlDocumentData.xmlDocument.get(),
		xmlDocumentData.rootNode.get(), &referenceModel);

	ApplicationModel loadedModel;
	ApplicationToolbarXmlStorage::Load(xmlDocumentData.rootNode.get(), &loadedModel);

	EXPECT_EQ(loadedModel, referenceModel);
}
