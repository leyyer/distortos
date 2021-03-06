/**
 * \file
 * \brief Types used by ThreadControlBlockList
 *
 * \author Copyright (C) 2014-2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-03-01
 */

#ifndef INCLUDE_DISTORTOS_SCHEDULER_THREADCONTROLBLOCKLIST_TYPES_HPP_
#define INCLUDE_DISTORTOS_SCHEDULER_THREADCONTROLBLOCKLIST_TYPES_HPP_

#include "distortos/allocators/PoolAllocator.hpp"
#include "distortos/allocators/SimpleFeedablePool.hpp"

#include <list>
#include <functional>

namespace distortos
{

namespace scheduler
{

class ThreadControlBlock;

/// type held by ThreadControlBlockList
using ThreadControlBlockListValueType = std::reference_wrapper<ThreadControlBlock>;

/// type of allocator used by ThreadControlBlockList
using ThreadControlBlockListAllocator =
		allocators::PoolAllocator<ThreadControlBlockListValueType, allocators::SimpleFeedablePool>;

/// underlying unsorted container of ThreadControlBlockList
using ThreadControlBlockUnsortedList = std::list<ThreadControlBlockListValueType, ThreadControlBlockListAllocator>;

/// generic iterator for ThreadControlBlockList
using ThreadControlBlockListIterator = ThreadControlBlockUnsortedList::iterator;

}	// namespace scheduler

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_SCHEDULER_THREADCONTROLBLOCKLIST_TYPES_HPP_
