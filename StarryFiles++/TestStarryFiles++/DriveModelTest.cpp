// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "DriveModel.h"
#include "DriveEnumerator.h"
#include "DriveWatcher.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <set>
#include <string>

using namespace testing;

class DriveEnumeratorFake : public DriveEnumerator
{
public:
	DriveEnumeratorFake(const std::set<std::wstring> &drives) : m_drives(drives)
	{
	}

	outcome::std_result<std::set<std::wstring>> GetDrives() override
	{
		return m_drives;
	}

private:
	std::set<std::wstring> m_drives;
};

class DriveWatcherFake : public DriveWatcher
{
public:
	boost::signals2::connection AddDriveAddedObserver(
		const DriveAddedSignal::slot_type &observer) override
	{
		return m_driveAddedSignal.connect(observer);
	}

	boost::signals2::connection AddDriveUpdatedObserver(
		const DriveUpdatedSignal::slot_type &observer) override
	{
		return m_driveUpdatedSignal.connect(observer);
	}

	boost::signals2::connection AddDriveRemovedObserver(
		const DriveRemovedSignal::slot_type &observer) override
	{
		return m_driveRemovedSignal.connect(observer);
	}

	void AddDrive(const std::wstring &path)
	{
		m_driveAddedSignal(path);
	}

	void UpdateDrive(const std::wstring &path)
	{
		m_driveUpdatedSignal(path);
	}

	void RemoveDrive(const std::wstring &path)
	{
		m_driveRemovedSignal(path);
	}

private:
	DriveAddedSignal m_driveAddedSignal;
	DriveUpdatedSignal m_driveUpdatedSignal;
	DriveRemovedSignal m_driveRemovedSignal;
};

class DriveModelObserverMock
{
public:
	DriveModelObserverMock(DriveModel *driveModel)
	{
		driveModel->AddDriveAddedObserver(
			std::bind_front(&DriveModelObserverMock::OnDriveAdded, this));
		driveModel->AddDriveUpdatedObserver(
			std::bind_front(&DriveModelObserverMock::OnDriveUpdated, this));
		driveModel->AddDriveRemovedObserver(
			std::bind_front(&DriveModelObserverMock::OnDriveRemoved, this));
	}

	MOCK_METHOD(void, OnDriveAdded, (const std::wstring &path, size_t index));
	MOCK_METHOD(void, OnDriveUpdated, (const std::wstring &path));
	MOCK_METHOD(void, OnDriveRemoved, (const std::wstring &path, size_t oldIndex));
};

class DriveModelTest : public Test
{
protected:
	DriveModelTest()
	{
		m_drives = { L"C:\\", L"D:\\", L"E:\\" };
		auto driveEnumerator = std::make_unique<DriveEnumeratorFake>(m_drives);

		auto driveWatcher = std::make_unique<DriveWatcherFake>();
		m_rawDriveWatcher = driveWatcher.get();

		m_driveModel =
			std::make_unique<DriveModel>(std::move(driveEnumerator), std::move(driveWatcher));

		m_observerMock = std::make_unique<DriveModelObserverMock>(m_driveModel.get());
	}

	std::set<std::wstring> m_drives;
	DriveWatcherFake *m_rawDriveWatcher;
	std::unique_ptr<DriveModel> m_driveModel;
	std::unique_ptr<DriveModelObserverMock> m_observerMock;
};

TEST_F(DriveModelTest, AddDrive)
{
	std::wstring pathToAdd = L"F:\\";

	EXPECT_CALL(*m_observerMock, OnDriveAdded(pathToAdd, 3));

	m_rawDriveWatcher->AddDrive(pathToAdd);

	m_drives.emplace(pathToAdd);
	EXPECT_EQ(m_driveModel->GetDrives(), m_drives);
}

TEST_F(DriveModelTest, RemoveDrive)
{
	std::wstring pathToRemove = L"D:\\";

	EXPECT_CALL(*m_observerMock, OnDriveRemoved(pathToRemove, 1));

	m_rawDriveWatcher->RemoveDrive(pathToRemove);

	m_drives.erase(pathToRemove);
	EXPECT_EQ(m_driveModel->GetDrives(), m_drives);
}

TEST_F(DriveModelTest, AddDuplicateDrive)
{
	std::wstring pathToAdd = L"D:\\";

	EXPECT_CALL(*m_observerMock, OnDriveAdded(_, _)).Times(0);

	m_rawDriveWatcher->AddDrive(pathToAdd);

	EXPECT_EQ(m_driveModel->GetDrives(), m_drives);
}

TEST_F(DriveModelTest, RemoveNonExistentDrive)
{
	std::wstring pathToRemove = L"F:\\";

	EXPECT_CALL(*m_observerMock, OnDriveRemoved(_, _)).Times(0);

	m_rawDriveWatcher->RemoveDrive(pathToRemove);

	EXPECT_EQ(m_driveModel->GetDrives(), m_drives);
}
