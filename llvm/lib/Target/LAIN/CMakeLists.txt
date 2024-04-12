add_llvm_component_group(LAIN)

set(LLVM_TARGET_DEFINITIONS LAIN.td)

tablegen(LLVM LAINGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM LAINGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM LAINGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM LAINGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM LAINGenCallingConv.inc -gen-callingconv)
tablegen(LLVM LAINGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM LAINGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM LAINGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM LAINGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(LAINCommonTableGen)

add_llvm_target(LAINCodeGen
        LAINTargetMachine.cpp
        LAINRegisterInfo.cpp
        LAINInstrInfo.cpp
        LAINSubtarget.cpp
        LAINAsmPrinter.cpp
        LAINFrameLowering.cpp
        LAINISelDagToDag.cpp
        LAINISelLowering.cpp
        LAINMCInstLower.cpp

        LINK_COMPONENTS
        CodeGen
        Core
        Support
        Target
        LAINInfo
        MC
        LAINDesc
        AsmPrinter
        SelectionDAG

        ADD_TO_COMPONENT
        LAIN
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
