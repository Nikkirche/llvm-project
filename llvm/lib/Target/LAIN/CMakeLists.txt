add_llvm_component_group(LAIN)

set(LLVM_TARGET_DEFINITIONS LAIN.td)

tablegen(LLVM LAINGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM LAINGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM LAINGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(LAINCommonTableGen)

add_llvm_target(LAINCodeGen
        LAINTargetMachine.cpp
        LAINRegisterInfo.cpp
        LAINInstrInfo.cpp
        LAINSubtarget.cpp

        LINK_COMPONENTS
        CodeGen
        Core
        Support
        Target
        LAINInfo

        ADD_TO_COMPONENT
        LAIN
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
