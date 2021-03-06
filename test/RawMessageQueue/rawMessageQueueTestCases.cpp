/**
 * \file
 * \brief rawMessageQueueTestCases object definition
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-05-16
 */

#include "rawMessageQueueTestCases.hpp"

#include "RawMessageQueuePriorityTestCase.hpp"
#include "RawMessageQueueOperationsTestCase.hpp"

#include "TestCaseGroup.hpp"

namespace distortos
{

namespace test
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// RawMessageQueuePriorityTestCase instance
const RawMessageQueuePriorityTestCase priorityTestCase;

/// RawMessageQueueOperationsTestCase instance
const RawMessageQueueOperationsTestCase operationsTestCase;

/// array with references to TestCase objects related to raw message queue
const TestCaseGroup::Range::value_type messageQueueTestCases_[]
{
		TestCaseGroup::Range::value_type{priorityTestCase},
		TestCaseGroup::Range::value_type{operationsTestCase},
};

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

const TestCaseGroup rawMessageQueueTestCases {TestCaseGroup::Range{messageQueueTestCases_}};

}	// namespace test

}	// namespace distortos
