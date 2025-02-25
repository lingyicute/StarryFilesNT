// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <memory>

class BrowserWindow;
class CoreInterface;
class FileActionHandler;
struct FolderColumns;
struct FolderSettings;
struct PreservedTab;
class ShellBrowser;
class ShellBrowserImpl;
class TabNavigationInterface;
struct TabStorageData;

class Tab : private boost::noncopyable
{
public:
	enum class PropertyType
	{
		Name,
		LockState
	};

	enum class LockState
	{
		// The tab isn't locked; it can be navigated freely and closed.
		NotLocked,

		// The tab is locked. It can be navigated freely, but not closed.
		Locked,

		// Both the tab and address are locked. The tab can't be navigated or closed. All
		// navigations will proceed in a new tab.
		AddressLocked
	};

	typedef boost::signals2::signal<void(const Tab &tab, PropertyType propertyType)>
		TabUpdatedSignal;

	Tab(std::unique_ptr<ShellBrowser> shellBrowser, BrowserWindow *browser);
	Tab(const PreservedTab &preservedTab, std::unique_ptr<ShellBrowser> shellBrowser,
		BrowserWindow *browser);

	int GetId() const;

	ShellBrowser *GetShellBrowser() const;
	ShellBrowserImpl *GetShellBrowserImpl() const;

	BrowserWindow *GetBrowser() const;

	std::wstring GetName() const;
	bool GetUseCustomName() const;
	void SetCustomName(const std::wstring &name);
	void ClearCustomName();

	LockState GetLockState() const;
	void SetLockState(LockState lockState);

	boost::signals2::connection AddTabUpdatedObserver(const TabUpdatedSignal::slot_type &observer);

	TabStorageData GetStorageData() const;

	/* Although each tab manages its
	own columns, it does not know
	about any column defaults.
	Therefore, it makes more sense
	for this setting to remain here. */
	// BOOL	bUsingDefaultColumns;

private:
	static inline int idCounter = 1;
	const int m_id;

	const std::unique_ptr<ShellBrowser> m_shellBrowser;
	ShellBrowserImpl *const m_shellBrowserImpl;

	BrowserWindow *const m_browser;

	bool m_useCustomName;
	std::wstring m_customName;
	LockState m_lockState;

	TabUpdatedSignal m_tabUpdatedSignal;
};
