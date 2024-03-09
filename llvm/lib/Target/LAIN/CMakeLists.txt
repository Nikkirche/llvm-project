add_llvm_component_group(LAIN)

add_llvm_target(LAINCodeGen
        LAINTargetMachine.cpp

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