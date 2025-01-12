// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_WIN32_TIP_TIP_DLL_MODULE_H_
#define MOZC_WIN32_TIP_TIP_DLL_MODULE_H_

#include <windows.h>

#include <atomic>

#include "absl/base/call_once.h"

namespace mozc {
namespace win32 {
namespace tsf {

class TipDllModule {
 public:
  TipDllModule() = delete;
  TipDllModule(const TipDllModule&) = delete;
  TipDllModule& operator=(const TipDllModule&) = delete;

  // Increases and decreases the reference count to this module.
  // This reference count is used for preventing Windows from unloading
  // this module.
  static LONG AddRef() noexcept { return ::InterlockedIncrement(&ref_count_); }
  static LONG Release() noexcept;

  static bool IsUnloaded() { return unloaded_; }
  static bool CanUnload() { return ref_count_ <= 0; }
  static void Unload() { unloaded_ = true; }

  static void set_module_handle(HMODULE handle) { module_handle_ = handle; }
  static HMODULE module_handle() { return module_handle_; }

  static void InitForUnitTest();

 private:
  static volatile LONG ref_count_;
  static HMODULE module_handle_;
  static bool unloaded_;
  static absl::once_flag uninitialize_once_;
};

}  // namespace tsf
}  // namespace win32
}  // namespace mozc

#endif  // MOZC_WIN32_TIP_TIP_DLL_MODULE_H_
