/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009-2014 by Appcelerator, Inc.
 */

/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef VirtualRegister_h
#define VirtualRegister_h

#include "CallFrame.h"

#include <wtf/Platform.h>
#include <wtf/PrintStream.h>

namespace TI {

inline bool operandIsLocal(int operand)
{
    return operand < 0;
}

inline bool operandIsArgument(int operand)
{
    return operand >= 0;
}


class VirtualRegister {
public:
    friend VirtualRegister virtualRegisterForLocal(int);
    friend VirtualRegister virtualRegisterForArgument(int, int);

    VirtualRegister()
        : m_virtualRegister(s_invalidVirtualRegister)
    { }

    explicit VirtualRegister(int virtualRegister)
        : m_virtualRegister(virtualRegister)
    { }

    bool isValid() const { return (m_virtualRegister != s_invalidVirtualRegister); }
    bool isLocal() const { return operandIsLocal(m_virtualRegister); }
    bool isArgument() const { return operandIsArgument(m_virtualRegister); }
    bool isConstant() const { return m_virtualRegister >= s_firstConstantRegisterIndex; }
    int toLocal() const { ASSERT(isLocal()); return operandToLocal(m_virtualRegister); }
    int toArgument() const { ASSERT(isArgument()); return operandToArgument(m_virtualRegister); }
    int toConstantIndex() const { ASSERT(isConstant()); return m_virtualRegister - s_firstConstantRegisterIndex; }
    int offset() const { return m_virtualRegister; }

    bool operator==(const VirtualRegister other) const { return m_virtualRegister == other.m_virtualRegister; }
    bool operator!=(const VirtualRegister other) const { return m_virtualRegister != other.m_virtualRegister; }

private:
    static const int s_invalidVirtualRegister = 0x3fffffff;
    static const int s_firstConstantRegisterIndex = 0x40000000;

    static int localToOperand(int local) { return -1 - local; }
    static int operandToLocal(int operand) { return -1 - operand; }
    static int operandToArgument(int operand) { return operand - CallFrame::thisArgumentOffset(); }
    static int argumentToOperand(int argument) { return argument + CallFrame::thisArgumentOffset(); }

    int m_virtualRegister;
};

COMPILE_ASSERT(sizeof(VirtualRegister) == sizeof(int), VirtualRegister_is_32bit);

inline VirtualRegister virtualRegisterForLocal(int local)
{
    return VirtualRegister(VirtualRegister::localToOperand(local));
}

inline VirtualRegister virtualRegisterForArgument(int argument, int offset = 0)
{
    return VirtualRegister(VirtualRegister::argumentToOperand(argument) + offset);
}

} // namespace TI

namespace WTI {

inline void printInternal(PrintStream& out, TI::VirtualRegister value)
{
    out.print(value.offset());
}

} // namespace WTI

#endif // VirtualRegister_h
