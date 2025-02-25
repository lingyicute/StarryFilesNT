// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "../Helper/WeakPtr.h"
#include "../Helper/WinRTBaseWrapper.h"

class ShellBrowserImpl;
class TabNavigationInterface;

// This isn't a complete implementation. There's only enough functionality to support the "New
// Folder" item shown on the background context menu in a phone's virtual folder (when that phone is
// connected via USB).
class ShellView : public winrt::implements<ShellView, IShellView, winrt::non_agile>
{
public:
	ShellView(WeakPtr<ShellBrowserImpl> shellBrowserWeak, TabNavigationInterface *tabNavigation,
		bool switchToTabOnSelect);

	// IShellView
	IFACEMETHODIMP TranslateAccelerator(MSG *msg);
	IFACEMETHODIMP EnableModeless(BOOL enable);
	IFACEMETHODIMP UIActivate(UINT state);
	IFACEMETHODIMP Refresh();
	IFACEMETHODIMP CreateViewWindow(IShellView *previous, LPCFOLDERSETTINGS folderSettings,
		IShellBrowser *shellBrowser, RECT *view, HWND *hwnd);
	IFACEMETHODIMP DestroyViewWindow();
	IFACEMETHODIMP GetCurrentInfo(LPFOLDERSETTINGS folderSettings);
	IFACEMETHODIMP AddPropertySheetPages(DWORD reserved, LPFNSVADDPROPSHEETPAGE callback,
		LPARAM lParam);
	IFACEMETHODIMP SaveViewState();
	IFACEMETHODIMP SelectItem(PCUITEMID_CHILD pidlItem, SVSIF flags);
	IFACEMETHODIMP GetItemObject(UINT item, REFIID riid, void **ppv);

	// IOleWindow
	IFACEMETHODIMP GetWindow(HWND *hwnd);
	IFACEMETHODIMP ContextSensitiveHelp(BOOL enterMode);

private:
	const WeakPtr<ShellBrowserImpl> m_shellBrowserWeak;
	TabNavigationInterface *const m_tabNavigation;
	const bool m_switchToTabOnSelect;
};

namespace winrt
{
template <>
bool is_guid_of<IShellView>(guid const &id) noexcept;
}
