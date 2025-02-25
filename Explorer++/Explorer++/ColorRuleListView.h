// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "SignalWrapper.h"
#include <boost/signals2.hpp>

class ColorRule;
class ColorRuleModel;
class ThemeManager;
class WindowSubclass;

class ColorRuleListView
{
public:
	ColorRuleListView(HWND listView, HINSTANCE resourceInstance, ThemeManager *themeManager,
		ColorRuleModel *model);

	ColorRule *MaybeGetSelectedColorRule();

	SignalWrapper<ColorRuleListView, void()> colorRuleSelectedSignal;
	SignalWrapper<ColorRuleListView, void()> colorRuleDeselectedSignal;

private:
	LRESULT CALLBACK ParentWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnDoubleClick(const NMITEMACTIVATE *itemActivate);

	void InsertColumns();
	void InsertColorRules();
	void InsertColorRule(const ColorRule *colorRule, size_t index);
	void UpdateColumnsForItem(const ColorRule *colorRule, size_t index);

	void OnColorRuleAdded(ColorRule *colorRule, size_t index);
	void OnColorRuleUpdated(ColorRule *colorRule);
	void OnColorRuleMoved(ColorRule *colorRule, size_t oldIndex, size_t newIndex);
	void OnColorRuleRemoved(const ColorRule *colorRule, size_t oldIndex);
	void OnAllColorRulesRemoved();

	HWND m_listView;
	HINSTANCE m_resourceInstance;
	ThemeManager *const m_themeManager;
	ColorRuleModel *m_model;

	std::vector<std::unique_ptr<WindowSubclass>> m_windowSubclasses;
	std::vector<boost::signals2::scoped_connection> m_connections;
};
