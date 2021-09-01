/*
BSD 3-Clause License

Copyright (c) 2021, NewTec GmbH
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file ZumoDriverStateMachine.h
 * @author Luis Moser
 * @brief ZumoDriverStateMachine header
 * @date 08/23/2021
 *
 * @{
 */

#ifndef __ZUMODRIVERSTATEMACHINE_H__
#define __ZUMODRIVERSTATEMACHINE_H__

 /** Enum describing the Zumo32U4 driver states. Used by ZumoDriverStateMachine class */
enum ZumoStates
{
    CLOSED,
    OPENED,
    FLASHING,
    READING_SERIAL,
    WRITING_SERIAL
};

/** Simple state machine for blocking/releasing member functions of Zumo32U4 driver */
class ZumoDriverStateMachine
{
public:
    /**
     * Default Constructor
     */
    ZumoDriverStateMachine();

    /**
     * Destructor
     */
    ~ZumoDriverStateMachine();

    /**
     * Sets the next new state of this state machine if it is an allowed transition.
     *
     * @param[in] state The next state to be in
     * @return Returns true if state has been set successfully, else false
     */
    bool setState(ZumoStates state);

    /**
     * Returns the current state of this state machine
     *
     * @return The current ZumoStates state
     */
    ZumoStates getState();

private:
    /** Specifies the current state of the state machine */
    ZumoStates m_currentState;
};
#endif /** __ZUMODRIVERSTATEMACHINE_H__ */
