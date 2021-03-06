/**
 * \file
 * \brief SignalsCatcherControlBlock class header
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-05-17
 */

#ifndef INCLUDE_DISTORTOS_SYNCHRONIZATION_SIGNALSCATCHERCONTROLBLOCK_HPP_
#define INCLUDE_DISTORTOS_SYNCHRONIZATION_SIGNALSCATCHERCONTROLBLOCK_HPP_

#include "distortos/SignalAction.hpp"

namespace distortos
{

namespace scheduler
{

class ThreadControlBlock;

}	// namespace scheduler

namespace synchronization
{

class SignalsReceiverControlBlock;

/// SignalsCatcherControlBlock class is a structure required by threads for "catching" and "handling" of signals
class SignalsCatcherControlBlock
{
public:

	/// association of signal numbers (as SignalSet) with SignalAction
	using Association = std::pair<SignalSet, SignalAction>;

	/// type of uninitialized storage for Association objects
	using Storage = std::aligned_storage<sizeof(Association), alignof(Association)>::type;

	/**
	 * \brief SignalsCatcherControlBlock's constructor
	 *
	 * \param [in] storageBegin is a pointer to first element of storage for Association objects
	 * \param [in] storageEnd is a pointer to "one past the last" element of storage for Association objects
	 */

	constexpr SignalsCatcherControlBlock(Storage* const storageBegin, Storage* const storageEnd) :
			signalMask_{SignalSet::empty},
			associationsBegin_{reinterpret_cast<decltype(associationsBegin_)>(storageBegin)},
			storageBegin_{storageBegin},
			storageEnd_{storageEnd},
			deliveryIsPending_{}
	{

	}

	/**
	 * \brief Hook function executed when delivery of signals is started.
	 *
	 * Clears "delivery pending" flag.
	 *
	 * \attention This function should be called only by SignalsReceiverControlBlock::deliveryOfSignalsFinishedHook().
	 */

	void deliveryOfSignalsStartedHook()
	{
		deliveryIsPending_ = false;
	}

	/**
	 * \brief Gets SignalAction associated with given signal number.
	 *
	 * \param [in] signalNumber is the signal for which the association is requested, [0; 31]
	 *
	 * \return pair with return code (0 on success, error code otherwise) and SignalAction that is associated with
	 * \a signalNumber, default-constructed object if no association was found;
	 * error codes:
	 * - EINVAL - \a signalNumber value is invalid;
	 */

	std::pair<int, SignalAction> getAssociation(uint8_t signalNumber) const;

	/**
	 * \return SignalSet with signal mask for associated thread
	 */

	SignalSet getSignalMask() const
	{
		return signalMask_;
	}

	/**
	 * \brief Part of SignalsReceiverControlBlock::postGenerate() specific to catching unmasked signals.
	 *
	 * Requests delivery of signals to associated thread if there is some non-default signal handler for the signal.
	 *
	 * \param [in] signalNumber is the unmasked signal that was generated, [0; 31]
	 * \param [in] threadControlBlock is a reference to associated ThreadControlBlock
	 *
	 * \return 0 on success, error code otherwise:
	 * - EINVAL - \a signalNumber value is invalid;
	 */

	int postGenerate(uint8_t signalNumber, const scheduler::ThreadControlBlock& threadControlBlock);

	/**
	 * \brief Sets association for given signal number.
	 *
	 * \param [in] signalNumber is the signal for which the association will be set, [0; 31]
	 * \param [in] signalAction is a reference to SignalAction that will be associated with given signal number, object
	 * in internal storage is copy-constructed
	 *
	 * \return pair with return code (0 on success, error code otherwise) and SignalAction that was associated with
	 * \a signalNumber, default-constructed object if no association was found;
	 * error codes:
	 * - EAGAIN - no resources are available to associate \a signalNumber with \a signalAction;
	 * - EINVAL - \a signalNumber value is invalid;
	 */

	std::pair<int, SignalAction> setAssociation(uint8_t signalNumber, const SignalAction& signalAction);

	/**
	 * \brief Sets signal mask for associated thread.
	 *
	 * If any pending signal is unblocked and \a owner doesn't equal nullptr, then delivery of signals to associated
	 * thread will be requested.
	 *
	 * \param [in] signalMask is the SignalSet with new signal mask for associated thread
	 * \param [in] owner selects whether delivery of signals will be requested if any pending signal is unblocked
	 * (pointer to owner SignalsReceiverControlBlock object) or not (nullptr)
	 */

	void setSignalMask(SignalSet signalMask, const SignalsReceiverControlBlock* owner);

private:

	/**
	 * \brief Clears association for given signal number.
	 *
	 * \param [in] signalNumber is the signal for which the association will be cleared, [0; 31]
	 *
	 * \return SignalAction that was associated with \a signalNumber, default-constructed object if no association was
	 * found
	 */

	SignalAction clearAssociation(uint8_t signalNumber);

	/**
	 * \brief Clears given association for given signal number.
	 *
	 * \param [in] signalNumber is the signal for which the association will be cleared, [0; 31]
	 * \param [in] association is a reference to Association object from <em>[associationsBegin_; associationsEnd_)</em>
	 * range that will be removed
	 *
	 * \return SignalAction from \a association
	 */

	SignalAction clearAssociation(uint8_t signalNumber, Association& association);

	/**
	 * \brief Requests delivery of signals to associated thread.
	 *
	 * \param [in] threadControlBlock is a reference to associated ThreadControlBlock
	 */

	void requestDeliveryOfSignals(const scheduler::ThreadControlBlock& threadControlBlock);

	/// SignalSet with signal mask for associated thread
	SignalSet signalMask_;

	/// pointer to first element of range of Association objects
	Association* associationsBegin_;

	/// union binds \a associationsEnd_ and \a storageBegin_ - these point to the same address
	union
	{
		/// pointer to "one past the last" element of range of Association objects
		Association* associationsEnd_;

		/// pointer to first element of range of Storage objects
		Storage* storageBegin_;
	};

	/// pointer to "one past the last" element of range of Storage objects
	Storage* storageEnd_;

	/// true if signal delivery is pending, false otherwise
	bool deliveryIsPending_;
};

}	// namespace synchronization

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_SYNCHRONIZATION_SIGNALSCATCHERCONTROLBLOCK_HPP_
