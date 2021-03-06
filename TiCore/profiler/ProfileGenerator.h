/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009-2012 by Appcelerator, Inc.
 */

/*
 * Copyright (C) 2008 Apple Inc. All Rights Reserved.
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
 
#ifndef ProfileGenerator_h
#define ProfileGenerator_h

#include "Profile.h"
#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>

namespace TI {

    class TiExcState;
    class TiGlobalObject;
    class Profile;
    class ProfileNode;
    class UString;
    struct CallIdentifier;    

    class ProfileGenerator : public RefCounted<ProfileGenerator>  {
    public:
        static PassRefPtr<ProfileGenerator> create(TiExcState*, const UString& title, unsigned uid);

        // Members
        const UString& title() const;
        PassRefPtr<Profile> profile() const { return m_profile; }
        TiGlobalObject* origin() const { return m_origin; }
        unsigned profileGroup() const { return m_profileGroup; }

        // Collecting
        void willExecute(TiExcState* callerCallFrame, const CallIdentifier&);
        void didExecute(TiExcState* callerCallFrame, const CallIdentifier&);

        void exceptionUnwind(TiExcState* handlerCallFrame, const CallIdentifier&);

        // Stopping Profiling
        void stopProfiling();

        typedef void (ProfileGenerator::*ProfileFunction)(TiExcState* callerOrHandlerCallFrame, const CallIdentifier& callIdentifier);

    private:
        ProfileGenerator(TiExcState*, const UString& title, unsigned uid);
        void addParentForConsoleStart(TiExcState*);

        void removeProfileStart();
        void removeProfileEnd();

        RefPtr<Profile> m_profile;
        TiGlobalObject* m_origin;
        unsigned m_profileGroup;
        RefPtr<ProfileNode> m_head;
        RefPtr<ProfileNode> m_currentNode;
    };

} // namespace TI

#endif // ProfileGenerator_h
