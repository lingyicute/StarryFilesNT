// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <boost/signals2.hpp>
#include <string>

class DriveWatcher
{
public:
	using DriveAddedSignal = boost::signals2::signal<void(const std::wstring &path)>;
	using DriveUpdatedSignal = boost::signals2::signal<void(const std::wstring &path)>;
	using DriveRemovedSignal = boost::signals2::signal<void(const std::wstring &path)>;

	virtual ~DriveWatcher() = default;

	virtual boost::signals2::connection AddDriveAddedObserver(
		const DriveAddedSignal::slot_type &observer) = 0;
	virtual boost::signals2::connection AddDriveUpdatedObserver(
		const DriveUpdatedSignal::slot_type &observer) = 0;
	virtual boost::signals2::connection AddDriveRemovedObserver(
		const DriveRemovedSignal::slot_type &observer) = 0;
};
