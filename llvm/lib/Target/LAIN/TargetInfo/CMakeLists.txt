add_llvm_component_library(LLVMLAINInfo
        LAINTargetInfo.cpp

        LINK_COMPONENTS
        MC
        Support

        ADD_TO_COMPONENT
        LAIN
)