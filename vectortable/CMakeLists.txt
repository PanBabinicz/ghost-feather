file(GLOB_RECURSE VECTORTABLE_SOURCES stm32f722xx/*.S)

set_property(
    GLOBAL
    PROPERTY VECTORTABLE_SOURCES
    ${VECTORTABLE_SOURCES}
    )

add_library(
    vectortable
    ${VECTORTABLE_SOURCES}
    )
