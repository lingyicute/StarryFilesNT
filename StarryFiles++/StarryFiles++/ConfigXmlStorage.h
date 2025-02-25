// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <msxml.h>

struct Config;

namespace ConfigXmlStorage
{

void Load(IXMLDOMNode *rootNode, Config &config);
void Save(IXMLDOMDocument *xmlDocument, IXMLDOMNode *rootNode, const Config &config);

}
