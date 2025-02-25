// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "WindowStorageTestHelper.h"
#include "MainRebarStorage.h"
#include "ShellTestHelper.h"
#include "TabStorage.h"
#include "TabStorageTestHelper.h"
#include "WindowStorage.h"

namespace WindowStorageTestHelper
{

std::vector<WindowStorageData> BuildV2ReferenceWindows(TestStorageType storageType)
{
	// clang-format off
	return {
		{
			.bounds = { 618, 598, 1825, 1249 },
			.showState = WindowShowState::Normal,
			.tabs = {
				CreateTabStorageFromDirectory(L"c:\\fake1", storageType)
			},
			.selectedTab = 0,
			.mainRebarInfo = {
				{ 1, 769, 212 },
				{ 0, 768, 391 }
			},
			.mainToolbarButtons = MainToolbarStorage::MainToolbarButtons({
				MainToolbarButton::Back,
				MainToolbarButton::Forward,
				MainToolbarButton::Delete
			}),
			.treeViewWidth = 430,
			.displayWindowWidth = 610,
			.displayWindowHeight = 429
		},
		{
			.bounds = { 212, 40, 400, 1073 },
			.showState = WindowShowState::Minimized,
			.tabs = {
				CreateTabStorageFromDirectory(L"c:\\fake1", storageType),
				CreateTabStorageFromDirectory(L"c:\\fake2", storageType),
				CreateTabStorageFromDirectory(L"c:\\fake3", storageType)
			},
			.selectedTab = 2,
			.mainRebarInfo = {
				{ 0, 769, 110 }
			},
			.mainToolbarButtons = MainToolbarStorage::MainToolbarButtons({
				MainToolbarButton::Refresh,
				MainToolbarButton::Separator,
				MainToolbarButton::NewTab
			}),
			.treeViewWidth = 57,
			.displayWindowWidth = 176,
			.displayWindowHeight = 827
		},
		{
			.bounds = { 1165, 2, 2071, 643 },
			.showState = WindowShowState::Maximized,
			.tabs = {
				CreateTabStorageFromDirectory(L"c:\\fake1", storageType),
				CreateTabStorageFromDirectory(L"c:\\fake2", storageType)
			},
			.selectedTab = 1,
			.mainRebarInfo = {
				{ 0, 769, 1846 }
			},
			.mainToolbarButtons = MainToolbarStorage::MainToolbarButtons({
				MainToolbarButton::Search,
				MainToolbarButton::CloseTab
			}),
			.treeViewWidth = 844,
			.displayWindowWidth = 140,
			.displayWindowHeight = 211
		}
	};
	// clang-format on
}

WindowStorageData BuildV2FallbackReferenceWindow(TestStorageType storageType)
{
	// clang-format off
	return {
		.bounds = { 683, 790, 1073, 2280 },
		.showState = WindowShowState::Normal,
		.tabs = {
			CreateTabStorageFromDirectory(L"c:\\fake1", storageType),
			CreateTabStorageFromDirectory(L"c:\\fake2", storageType),
			CreateTabStorageFromDirectory(L"c:\\fake3", storageType)
		},
		.selectedTab = 2,
		.mainRebarInfo = {
			{ 2, 769, 88 },
			{ 0, 768, 712 },
			{ 1, 768, 1834 }
		},
		.mainToolbarButtons = MainToolbarStorage::MainToolbarButtons({
			MainToolbarButton::MergeFiles,
			MainToolbarButton::OpenCommandPrompt
		}),
		.treeViewWidth = 117,
		.displayWindowWidth = 66,
		.displayWindowHeight = 595
	};
	// clang-format on
}

WindowStorageData BuildV1ReferenceWindow(TestStorageType storageType)
{
	// clang-format off
	return {
		.bounds = { 98, 87, 1606, 798 },
		.showState = WindowShowState::Normal,
		.tabs = {
			CreateTabStorageFromDirectory(L"c:\\fake1", storageType),
			CreateTabStorageFromDirectory(L"c:\\fake2", storageType)
		},
		.selectedTab = 1,
		.mainRebarInfo = {
			{ 0, 768, 652 },
			{ 1, 769, 839 }
		},
		.mainToolbarButtons = MainToolbarStorage::MainToolbarButtons({
			MainToolbarButton::CopyTo,
			MainToolbarButton::MoveTo,
			MainToolbarButton::Up
		}),
		.treeViewWidth = 1014,
		.displayWindowWidth = 212,
		.displayWindowHeight = 340
	};
	// clang-format on
}

}
