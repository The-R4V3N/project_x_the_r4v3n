add_custom_target(
    #name
    generate_sources_from_json
    # Command cmd arg1 arg2 arg ...
    COMMAND "python3" "signals.py"
    # Working directory -> our folder with CMakeList.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CAN_MessagesINCLUDE_DIR
            "${CMAKE_CURRENT_SOURCE_DIR}/Output/include/signals.h"
            PARENT_SCOPE)
            
set(CAN_MessagesSOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/Output/src/signals.cpp
            PARENT_SCOPE)
