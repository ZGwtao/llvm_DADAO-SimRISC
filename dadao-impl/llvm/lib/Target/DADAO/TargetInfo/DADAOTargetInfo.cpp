//===-- DADAOTargetInfo.cpp - DADAO Target Implementation -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/DADAOTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheDADAOTarget() {
  static Target TheDADAOTarget;
  return TheDADAOTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDADAOTargetInfo() {
  RegisterTarget<Triple::dadao, /*HasJIT=*/false> X(getTheDADAOTarget(),
                                                    "dadao", "DADAO", "DADAO");
}
