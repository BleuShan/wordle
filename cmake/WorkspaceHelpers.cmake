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
    LINK_LIBRARIES
)

set(workspace_helpers_get_target_version_property_keys
    VERSION
    SOVERSION
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

function(workspace_helpers_get_target_version_properties name out_var)
    set(result)
    foreach(key ${workspace_helpers_get_target_version_property_keys})
        string(TOLOWER ${key} value_key)
        get_target_property(${value_key} ${name} ${key})

        if (${${value_key}} STREQUAL "${value_key}-NOTFOUND")
            unset(${value_key})
        endif()

        if(NOT DEFINED ${value_key})
          workspace_helpers_parse_arguments_value(${value_key} ${name} ${key})
        endif()

        if(NOT DEFINED ${value_key} AND value_key STREQUAL "version")
            set(${value_key} ${PROJECT_VERSION})
        endif()

        if(NOT DEFINED ${value_key} AND value_key STREQUAL "version")
            set(${value_key} ${WORKSPACE_PACKAGE_VERSION})
        endif()


        if(DEFINED version AND
            NOT DEFINED ${value_key} AND
            value_key STREQUAL "soversion")
            string(REPLACE "." ";" version_values ${version})

            foreach(value ${version_values})
                string(JOIN "." ${value_key} ${${value_key}} ${value})
                if(NOT value STREQUAL "0")
                    break()
                endif()
            endforeach()
        endif()

        if(DEFINED ${value_key})
           list(APPEND result ${key} ${${value_key}})
        endif()
   endforeach()
   set(${out_var} ${result} PARENT_SCOPE)
endfunction()


function(workspace_helpers_set_target_properties name)
    workspace_helpers_get_target_version_properties(${name} versions)

    set_target_properties(
        ${name}
        PROPERTIES
        ${versions}
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
    workspace_helpers_parse_arguments_value(version_ ${name} VERSION)
    if(NOT DEFINED version_)
        set(version_ "${WORKSPACE_PACKAGE_VERSION}")
    endif()

    project(
        ${name}
        VERSION ${version_}
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
            DEFINE_SYMBOL ${define_symbol}
            C_VISIBILITY_PRESET hidden
            CXX_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN ON
        )
    endif()

    workspace_helpers_set_target_properties(${name})

    target_include_directories(${name}
        SYSTEM
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}/${name}>
    )
endmacro()

macro(executable_project name)
    workspace_helpers_define_project(${name} ${ARGN})
    executable_target(${name})
endmacro()

macro(executable_target name)
    workspace_helpers_parse_arguments_value(sources ${name} SOURCES)
    workspace_helpers_target_type(${name} type)
    add_executable(${name} ${type} ${sources})
    workspace_helpers_set_target_properties(${name})
    workspace_helpers_parse_arguments_value(libs ${name} LINK_LIBRARIES)
    foreach(lib ${libs})
        target_link_libraries(${name} ${lib})
    endforeach()
endmacro()

function(test_target name)
    if(NOT BUILD_TESTING)
        return()
    endif()
    workspace_helpers_parse_arguments(${name} ${ARGN})
    executable_target(${name})
    set_target_properties(
        ${name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
        PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    )
    target_link_libraries(${name} gmock_main)
    gtest_discover_tests(${name})
endfunction()


function(current_project_sources)
    target_sources(${PROJECT_NAME} ${ARGV})
endfunction()
