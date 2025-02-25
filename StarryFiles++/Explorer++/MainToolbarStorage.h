// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "MainToolbarButtons.h"
#include <msxml.h>
#include <optional>
#include <string>
#include <vector>

namespace MainToolbarStorage
{

// Represents a set of toolbar buttons. The advantage this has over a raw vector is that it will
// only allow non-separator buttons to be added a single time.
class MainToolbarButtons
{
public:
	MainToolbarButtons() = default;
	MainToolbarButtons(const std::vector<MainToolbarButton> &buttons);

	void AddButton(MainToolbarButton button);
	const std::vector<MainToolbarButton> &GetButtons() const;

	// This is only used in tests.
	bool operator==(const MainToolbarButtons &) const = default;

private:
	std::vector<MainToolbarButton> m_buttons;
};

std::optional<MainToolbarButtons> LoadFromRegistry(HKEY parentKey, const std::wstring &valueName);
void SaveToRegistry(HKEY parentKey, const std::wstring &valueName,
	const MainToolbarButtons &buttons);
std::optional<MainToolbarButtons> LoadFromXml(IXMLDOMNode *toolbarNode);
void SaveToXml(IXMLDOMDocument *xmlDocument, IXMLDOMElement *toolbarNode,
	const MainToolbarButtons &buttons);

}
