add_llvm_component_library(LLVMLAINDesc
        LAINMCTargetDesc.cpp

        LINK_COMPONENTS
        MC
        Support
        LAINInfo

        ADD_TO_COMPONENT
        LAIN
)