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
 * @file ZumoDriverStateMachine.cpp
 * @author Luis Moser
 * @brief ZumoDriverStateMachine class
 * @date 08/23/2021
 *
 * @{
 */

#include <ZumoDriverStateMachine.h>

ZumoDriverStateMachine::ZumoDriverStateMachine() :
    m_currentState(CLOSED)
{
}

ZumoDriverStateMachine::~ZumoDriverStateMachine()
{
}

bool ZumoDriverStateMachine::setState(ZumoStates state)
{
    bool retCode = false;

    switch (m_currentState)
    {
    case CLOSED:
    {
        if ((OPENED == state)
            || (FLASHING == state)
            || (CLOSED == state))
        {
            m_currentState = state;
            retCode = true;
        }
        break;
    }
    case OPENED: /* Intentional fall through */
    case WRITING_SERIAL: /* Intentional fall through */
    case READING_SERIAL: /* Intentional fall through */
    {
        if ((WRITING_SERIAL == state)
            || (READING_SERIAL == state)
            || (CLOSED == state)
            || (FLASHING == state))
        {
            m_currentState = state;
            retCode = true;
        }
        break;
    }
    case FLASHING:
    {
        if ((FLASHING == state)
            || (CLOSED == state))
        {
            m_currentState = state;
            retCode = true;
        }
        break;
    }
    default:
    {
        retCode = false;
        break;
    }
    }
    return retCode;
}

ZumoStates ZumoDriverStateMachine::getState()
{
    return m_currentState;
}
