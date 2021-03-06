/**
 * \file
 * \brief TestCaseGroup class header
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-05-16
 */

#ifndef TEST_TESTCASEGROUP_HPP_
#define TEST_TESTCASEGROUP_HPP_

#include "TestCaseCommon.hpp"

#include "distortos/estd/ContiguousRange.hpp"
#include "distortos/estd/ReferenceHolder.hpp"

namespace distortos
{

namespace test
{

/// TestCaseGroup class is a group of TestCase objects
class TestCaseGroup : public TestCaseCommon
{
public:

	/// range of references to TestCase objects
	using Range = estd::ContiguousRange<const estd::ReferenceHolder<const TestCase>>;

	/**
	 * \brief TestCaseGroup's constructor
	 *
	 * \param [in] range is a range of references to TestCase objects
	 */

	constexpr explicit TestCaseGroup(const Range range) :
			range_{range}
	{

	}

private:

	/**
	 * \brief Runs the test case.
	 *
	 * Runs each test case from \a range_.
	 *
	 * \return true if the test case succeeded, false otherwise
	 */

	virtual bool run_() const override;

	/// range of references to TestCase objects
	Range range_;
};

}	// namespace test

}	// namespace distortos

#endif	// TEST_TESTCASEGROUP_HPP_
