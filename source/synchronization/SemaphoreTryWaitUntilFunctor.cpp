/**
 * \file
 * \brief SemaphoreTryWaitUntilFunctor class implementation
 *
 * \author Copyright (C) 2014-2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-01-12
 */

#include "distortos/synchronization/SemaphoreTryWaitUntilFunctor.hpp"

#include "distortos/Semaphore.hpp"

namespace distortos
{

namespace synchronization
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

int SemaphoreTryWaitUntilFunctor::operator()(Semaphore& semaphore) const
{
	return semaphore.tryWaitUntil(timePoint_);
}

}	// namespace synchronization

}	// namespace distortos
