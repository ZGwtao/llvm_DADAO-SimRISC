//===-- DADAOTargetMachine.h - Define TargetMachine for DADAO -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===------------------------------------------------------------------------===//
//
// This file declares the DADAO specific subclass of TargetMachine.
//
//===------------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_DADAO_DADAOTARGETMACHINE_H
#define LLVM_LIB_TARGET_DADAO_DADAOTARGETMACHINE_H

#include "DADAOSubtarget.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>

namespace llvm {

class DADAOTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  /* FIXME
   * DADAOSubtarget class is neither defined nor implemented yet.
   */
  mutable StringMap<std::unique_ptr<DADAOSubtarget>> SubtargetMap;
public:
  DADAOTargetMachine(const Target &T,
		       const Triple &TT, /* Target Triple: e.g. dadao-unknwon-linux-elf */
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
  const DADAOSubtarget *getSubtargetImpl(std::string CPU, std::string FS) const;
  const DADAOSubtarget *getSubtargetImpl(const Function &F) const override;
  const DADAOSubtarget *getSubtargetImpl() const;

  /* Create a pass configuration object to be used by addPassToEmitX methods for
   * generating a pipeline of CodeGen passes => "benefits passes scheduler?"
   */
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

class DADAOPassConfig : public TargetPassConfig {
public:
  DADAOPassConfig(LLVMTargetMachine &TM, PassManagerBase &PM);
  //!
  //! ScheduleDAG <-- ScheduleDAGInstrs = Instruction Selection ? related
  //!
  /* Create an instance of "ScheduleDAGInstrs" to be run within the standard
   * "MachineScheduler" pass for this function and target at the current opt
   * level, return NULL to select the default (generic) machine scheduler.
   */
  ScheduleDAGInstrs *
  createMachineScheduler(MachineSchedContext *C) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DADAO_DADAOTARGETMACHINE_H

