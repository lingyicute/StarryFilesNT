// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "ApplicationExecutor.h"
#include <string>

class CoreInterface;

namespace Applications
{

class Application;

class ApplicationExecutorImpl : public ApplicationExecutor
{
public:
	// Without this, the overloaded version of ApplicationExecutor::Execute() that only takes a
	// single parameter would be hidden by the declaration of Execute() below. This statement
	// ensures that the overload is directly visible to users of this class.
	using ApplicationExecutor::Execute;

	ApplicationExecutorImpl(CoreInterface *coreInterface);

	void Execute(const Application *application, std::wstring extraParameters) override;

private:
	CoreInterface *m_coreInterface = nullptr;
};

}
