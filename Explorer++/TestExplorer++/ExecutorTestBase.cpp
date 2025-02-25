// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "ExecutorTestBase.h"

ExecutorTestBase::ExecutorTestBase(std::shared_ptr<concurrencpp::executor> executor) :
	m_executor(executor)
{
}

ExecutorTestBase::~ExecutorTestBase()
{
	// A test may call this method, but that's not an issue, since it's explicitly safe to call the
	// method multiple times.
	m_executor->shutdown();
}
