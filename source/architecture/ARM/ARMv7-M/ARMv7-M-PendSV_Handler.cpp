/**
 * \file
 * \brief PendSV_Handler() for ARMv7-M (Cortex-M3 / Cortex-M4)
 *
 * \author Copyright (C) 2014 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2014-07-28
 */

#include "distortos/scheduler/schedulerInstance.hpp"
#include "distortos/scheduler/Scheduler.hpp"

#include "distortos/distortosConfiguration.h"

#include "distortos/chip/CMSIS-proxy.h"


/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Wrapper for void * distortos::scheduler::schedulerInstance.switchContext(void *)
 *
 * \param [in] stack_pointer is the current value of current thread's stack pointer
 *
 * \return new thread's stack pointer
 */

extern "C" void * schedulerSwitchContextWrapper(void * const stack_pointer)
{
	return distortos::scheduler::schedulerInstance.switchContext(stack_pointer);
}

/**
 * \brief PendSV_Handler() for ARMv7-M (Cortex-M3 / Cortex-M4)
 *
 * Performs the context switch.
 */

extern "C" __attribute__ ((naked)) void PendSV_Handler()
{
	asm volatile
	(
			"	mrs		r0, PSP								\n"	// save context of current thread
			"	stmdb	r0!, {r4-r11}						\n"
			"												\n"
			"	mov		r1, %[basepri]						\n"	// disable interrupts below configured priority
			"	msr		BASEPRI, r1							\n"
			"												\n"
			"	mov		r4, lr								\n"
			"	bl		schedulerSwitchContextWrapper		\n"	// switch context
			"	mov		lr, r4								\n"
			"												\n"
			"	mov		r1, #0								\n"	// enable all interrupts
			"	msr		BASEPRI, r1							\n"
			"												\n"
			"	ldmia	r0!, {r4-r11}						\n"	// load context of new thread
			"	msr		PSP, r0								\n"
			"												\n"
			"	bx		lr									\n"	// return to new thread

			:: [basepri] "i" (CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI << __NVIC_PRIO_BITS)
	);

	__builtin_unreachable();
}