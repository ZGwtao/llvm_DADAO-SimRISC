add_llvm_component_library(LLVMDADAOInfo
  DADAOTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  DADAO
  )
