add_llvm_component_library(LLVMLAINDesc
        LAINMCTargetDesc.cpp
        LAINMCAsmInfo.cpp
        LAINInstPrinter.cpp

        LINK_COMPONENTS
        MC
        Support
        LAINInfo

        ADD_TO_COMPONENT
        LAIN
)