// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include <boost/signals2.hpp>

// This saves a fair amount of boilerplate code from having to be
// written. It allows the stored value to be retrieved and updated
// (using getter and setter methods) and allows changes to be observed.
// Without something like this, getter/setter methods would need to be
// written manually. Even if they were generated by a tool, there would
// still be a lot of additional code and the observer code would also
// need to be set up on a per-variable basis.
template <typename T>
class ValueWrapper
{
public:
	using ValueUpdatedSignal = boost::signals2::signal<void(T newValue)>;

	ValueWrapper() : m_value()
	{
	}

	ValueWrapper(T value) : m_value(value)
	{
	}

	// This is designed to allow the parent Config struct to be copied
	// when necessary. None of the observers are copied, you only get a
	// copy of the data.
	ValueWrapper(const ValueWrapper &variableChange)
	{
		m_value = variableChange.get();
	}

	// There's no non-const version of this method, as the value should only be modified by calling
	// the setter methods on this object.
	const T &get() const
	{
		return m_value;
	}

	void set(const T &value)
	{
		if (value != m_value)
		{
			m_value = value;
			m_valueUpdatedSignal(value);
		}
	}

	ValueWrapper &operator=(const T &value)
	{
		set(value);
		return *this;
	}

	template <typename... Args>
	boost::signals2::connection addObserver(Args &&...args) const
	{
		return m_valueUpdatedSignal.connect(std::forward<Args>(args)...);
	}

	bool operator==(const ValueWrapper &other) const
	{
		return m_value == other.m_value;
	}

private:
	T m_value;
	mutable ValueUpdatedSignal m_valueUpdatedSignal;
};
