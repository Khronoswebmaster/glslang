//
// Copyright (C) 2020 Google, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include "hlslParseHelper.h"
#include "hlslParseables.h"
#include "hlslScanContext.h"

#include "../glslang/MachineIndependent/Language.h"

namespace glslang {
namespace {

class HlslLanguage : public Language {
public:
    static HlslLanguage instance;

    void Initialize() {
        HlslScanContext::fillInKeywordMap();
    }

    void Terminate() {
        HlslScanContext::deleteKeywordMap();
    }

    EShSource Source() const {
        return EShSourceHlsl;
    }

    TBuiltInParseables* CreateBuiltInParseables(TInfoSink&) {
        return new TBuiltInParseablesHlsl();
    }

    TParseContextBase* CreateParseContext(TSymbolTable& symbolTable, TIntermediate& intermediate,
            int version, EProfile profile,
            EShLanguage language, TInfoSink& infoSink,
            SpvVersion spvVersion, bool forwardCompatible, EShMessages messages,
            bool parsingBuiltIns, std::string sourceEntryPointName) {
        return new HlslParseContext(symbolTable, intermediate, parsingBuiltIns, version, profile, spvVersion,
                                    language, infoSink, sourceEntryPointName.c_str(), forwardCompatible, messages);
    }
};

HlslLanguage HlslLanguage::instance;

} // end anonymous namespace

#ifdef ENABLE_HLSL
void RegisterHlslLanguage()
{
    Language::Register(&HlslLanguage::instance);
}
#endif

} // end namespace glslang
