// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "WeakState.h"
#include <boost/core/noncopyable.hpp>
#include <memory>

template <class T>
class WeakPtr;

// This has a similar function to weak_ptr_factory in the Chromium codebase. The class is intended
// to be used by an object on a single thread. For example, an object created on the main thread
// could schedule some work on a background thread. When returning to the main thread, the object
// could use a WeakPtr generated by this class to check whether or not the object instance is still
// live.
// A key advantage to this class is that it makes it possible to deterministically check whether an
// object is live before invoking methods on it.
template <class T>
class WeakPtrFactory : private boost::noncopyable
{
public:
	WeakPtrFactory(T *ptr) : m_state(std::make_shared<WeakState<T>>(ptr))
	{
		DCHECK_NOTNULL(ptr);
	}

	~WeakPtrFactory()
	{
		m_state->Invalidate();
	}

	WeakPtr<T> GetWeakPtr() const
	{
		return WeakPtr<T>(m_state);
	}

private:
	const std::shared_ptr<WeakState<T>> m_state;
};
