//===-- SIMRISCTargetMachine.h - Define TargetMachine for SIMRISC -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===------------------------------------------------------------------------===//
//
// This file declares the SIMRISC specific subclass of TargetMachine.
//
//===------------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SIMRISC_SIMRISCTARGETMACHINE_H
#define LLVM_LIB_TARGET_SIMRISC_SIMRISCTARGETMACHINE_H

#include "SIMRISCSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>

namespace llvm {

class SIMRISCTargetMachine : public LLVMTargetMachine {
  
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  /* FIXME
   * SIMRISCSubtarget class is neither defined nor implemented yet.
   */
  mutable StringMap<std::unique_ptr<SIMRISCSubtarget>> SubtargetMap;

public:
  SIMRISCTargetMachine(const Target &T,
		       const Triple &TT, /* Target Triple: e.g. simrisc-unknwon-linux-elf */
		       StringRef CPU,
		       StringRef FS,
		       const TargetOptions &Options,
		       std::optional<Reloc::Model> RM, /* static, pic, ... */
		       std::optional<CodeModel::Model> CM, /* size of the addr space */
		       CodeGenOpt::Level OptLevel,
		       bool JIT
		  ); /* Constructor of this class */

  /* Symbol "override" means the virtual method, which is defined by base class,
   * will be replaced by the method declared below.
   */
  const SIMRISCSubtarget *getSubtargetImpl(std::string CPU, std::string FS) const;
  const SIMRISCSubtarget *getSubtargetImpl(const Function &F) const override;
  const SIMRISCSubtarget *getSubtargetImpl() const;

  /* Create a pass configuration object to be used by addPassToEmitX methods for
   * generating a pipeline of CodeGen passes => "benefits passes scheduler?"
   */
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
}
