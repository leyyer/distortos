/**
 * \file
 * \brief Stack class header
 *
 * \author Copyright (C) 2014-2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-04-28
 */

#ifndef INCLUDE_DISTORTOS_ARCHITECTURE_STACK_HPP_
#define INCLUDE_DISTORTOS_ARCHITECTURE_STACK_HPP_

#include <cstddef>

namespace distortos
{

class ThreadBase;

namespace architecture
{

/// Stack class is an abstraction of architecture's stack
class Stack
{
public:

	/**
	 * \brief Stack's constructor
	 *
	 * This function initializes valid architecture-specific stack in provided buffer. This requires following steps:
	 * - adjustment of buffer's address to suit architecture's alignment requirements,
	 * - adjustment of buffer's size to suit architecture's divisibility requirements,
	 * - creating hardware and software stack frame in suitable place in the stack,
	 * - calculation of stack pointer register value.
	 *
	 * After this constructor completes, stack is ready for context switching.
	 *
	 * \param [in] buffer is a pointer to stack's buffer
	 * \param [in] size is the size of stack's buffer, bytes
	 * \param [in] function is a reference to thread's function, this function must not return
	 * \param [in] threadBase is a reference to ThreadBase object passed to function
	 */

	Stack(void* buffer, size_t size, void (& function)(ThreadBase&), ThreadBase& threadBase);

	/**
	 * \brief Stack's constructor
	 *
	 * This function adopts existing valid architecture-specific stack in provided buffer. No adjustments are done,
	 * no stack frame is created and stack pointer register's value is not calculated.
	 *
	 * This is meant to adopt main()'s stack.
	 *
	 * \param [in] buffer is a pointer to stack's buffer
	 * \param [in] size is the size of stack's buffer, bytes
	 */

	Stack(void* buffer, size_t size);

	/**
	 * \brief Gets current value of stack pointer.
	 *
	 * \return current value of stack pointer
	 */

	void* getStackPointer() const { return stackPointer_; }

	/**
	 * \brief Sets value of stack pointer.
	 *
	 * \param [in] stackPointer is the new value of stack pointer
	 */

	void setStackPointer(void* const stackPointer) { stackPointer_ = stackPointer; }

	Stack(const Stack&) = delete;
	Stack(Stack&&) = default;
	const Stack& operator=(const Stack&) = delete;
	Stack& operator=(Stack&&) = delete;

private:

	/// adjusted address of stack's buffer
	void* const adjustedBuffer_;

	/// adjusted size of stack's buffer
	const size_t adjustedSize_;

	/// current value of stack pointer register
	void* stackPointer_;
};

}	// namespace architecture

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_ARCHITECTURE_STACK_HPP_
