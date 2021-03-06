/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009-2012 by Appcelerator, Inc.
 */

/*
 * Copyright (C) 2008, 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "config.h"
#include "JSNotAnObject.h"

#include <wtf/UnusedParam.h>

namespace TI {

ASSERT_CLASS_FITS_IN_CELL(JSNotAnObject);

// TiValue methods
TiValue JSNotAnObject::toPrimitive(TiExcState* exec, PreferredPrimitiveType) const
{
    ASSERT_UNUSED(exec, exec->hadException());
    return jsNumber(0);
}

bool JSNotAnObject::getPrimitiveNumber(TiExcState* exec, double&, TiValue&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

bool JSNotAnObject::toBoolean(TiExcState* exec) const
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

double JSNotAnObject::toNumber(TiExcState* exec) const
{
    ASSERT_UNUSED(exec, exec->hadException());
    return NaN;
}

UString JSNotAnObject::toString(TiExcState* exec) const
{
    ASSERT_UNUSED(exec, exec->hadException());
    return "";
}

TiObject* JSNotAnObject::toObject(TiExcState* exec, TiGlobalObject*) const
{
    ASSERT_UNUSED(exec, exec->hadException());
    return const_cast<JSNotAnObject*>(this);
}

// TiObject methods
bool JSNotAnObject::getOwnPropertySlot(TiExcState* exec, const Identifier&, PropertySlot&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

bool JSNotAnObject::getOwnPropertySlot(TiExcState* exec, unsigned, PropertySlot&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

bool JSNotAnObject::getOwnPropertyDescriptor(TiExcState* exec, const Identifier&, PropertyDescriptor&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

void JSNotAnObject::put(TiExcState* exec, const Identifier& , TiValue, PutPropertySlot&)
{
    ASSERT_UNUSED(exec, exec->hadException());
}

void JSNotAnObject::put(TiExcState* exec, unsigned, TiValue)
{
    ASSERT_UNUSED(exec, exec->hadException());
}

bool JSNotAnObject::deleteProperty(TiExcState* exec, const Identifier&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

bool JSNotAnObject::deleteProperty(TiExcState* exec, unsigned)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

void JSNotAnObject::getOwnPropertyNames(TiExcState* exec, PropertyNameArray&, EnumerationMode)
{
    ASSERT_UNUSED(exec, exec->hadException());
}

} // namespace TI
