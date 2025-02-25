// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <msxml.h>

struct FolderColumns;

namespace DefaultColumnXmlStorage
{

void Load(IXMLDOMNode *rootNode, FolderColumns &defaultColumns);
void Save(IXMLDOMDocument *xmlDocument, IXMLDOMNode *rootNode, const FolderColumns &defaultColumns);

}
