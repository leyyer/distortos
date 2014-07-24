/**
 * \file
 * \brief schedulerInstance object definition
 *
 * \author Copyright (C) 2014 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2014-07-24
 */

#include "distortos/scheduler/schedulerInstance.hpp"

#include "distortos/scheduler/Scheduler.hpp"

namespace distortos
{

namespace scheduler
{

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

Scheduler schedulerInstance;

}	// namespace scheduler

}	// namespace distortos