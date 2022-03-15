set(workspace_helpers_parse_arguments_flags
    SHARED
    WIN32
    MACOSX_BUNDLE
)
set(workspace_helpers_parse_arguments_args
    VERSION
)
set(workspace_helpers_parse_arguments_list_args
    PROPERTIES
    SOURCES
)

macro(workspace_helpers_parse_arguments prefix)
    workspace_helpers_parse_arguments_variable_name(
        normalized_prefix_ ${prefix} "")
    cmake_parse_arguments(
        ${normalized_prefix_}
        "${workspace_helpers_parse_arguments_flags}"
        "${workspace_helpers_parse_arguments_args}"
        "${workspace_helpers_parse_arguments_list_args}"
        ${ARGN}
    )
endmacro()

macro(workspace_helpers_parse_arguments_variable_name var prefix suffix)
    if(prefix STREQUAL "")
        set(prefix current_target)
    endif()

    string(JOIN "_" ${var} ${prefix} ${suffix})
    string(TOUPPER ${${var}} ${var})
endmacro()

macro(workspace_helpers_parse_arguments_value var prefix suffix)
    workspace_helpers_parse_arguments_variable_name(source ${prefix} ${suffix})
    set(${var} ${${source}} ${ARGN})
endmacro()

function(workspace_helpers_set_target_property name)
    set_target_properties(
        ${name}
        PROPERTIES
        C_STANDARD 23
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    workspace_helpers_parse_arguments_value(props ${name} PROPERTIES)
    if(DEFINED props)
        set_target_properties(${name} PROPERTIES ${props})
    endif()
endfunction()

macro(workspace_helpers_define_project name)
    workspace_helpers_parse_arguments(${name} ${ARGN})
    workspace_helpers_parse_arguments_value(version ${name} VERSION)
    if(NOT DEFINED version)
        set(version "${WORKSPACE_PACKAGE_VERSION}")
    endif()

    project(
        ${name}
        VERSION ${version}
        LANGUAGES C CXX
    )
endmacro()

function(workspace_helpers_target_type name var)
    foreach(flag ${workspace_helpers_parse_arguments_flags})
        workspace_helpers_parse_arguments_value(present ${name} ${flag})
        if(present)
            set(${var} ${flag} PARENT_SCOPE)
            return()
        endif()

    endforeach()
endfunction()



macro(library_project name)
    workspace_helpers_define_project(${name} ${ARGN})

    workspace_helpers_target_type(${name} type)
    workspace_helpers_parse_arguments_value(sources ${name} SOURCES)
    add_library(${name} ${type} ${sources})
    add_library(${WORKSPACE_PACKAGE_NAME}::${name} ALIAS ${name})
    if(BUILD_SHARED_LIBS OR type STREQUAL "SHARED")
        string(TOUPPER "${name}_exports" define_symbol)
        set_target_properties(
            ${name}
            PROPERTIES
            DEFINE_SYMBOL define_symbol
        )
    endif()

    workspace_helpers_set_target_property(${name})

    target_include_directories(${name}
        SYSTEM
        PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${CMAKE_INSTALL_INCLUDEDIR}>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
    )
endmacro()

macro(executable_project name)
    workspace_helpers_define_project(${name})

    workspace_helpers_parse_arguments_value(sources ${name} SOURCES)
    add_executable(${name})
    workspace_helpers_set_target_property(${name})
endmacro()


function(current_project_sources)
    target_sources(${PROJECT_NAME} ${ARGV})
endfunction()
