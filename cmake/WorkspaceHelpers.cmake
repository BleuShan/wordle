include_guard()

include(WorkspaceEnvironment)

function(workspace_helpers_parse_arguments prefix)
    set(flags
        SHARED
        WIN32
        MACOSX_BUNDLE
    )
    set(args
        VERSION
    )
    set(list_args
       PROPERTIES
       SOURCES
    )

    workspace_helpers_parse_arguments_variable_name(
        normalized_prefix ${prefix} "")
    cmake_parse_arguments(
        PARSE_ARGV
        1
        ${normalized_prefix}
        "${flags}"
        "${args}"
        "${list_args}"
    )
endfunction()

function(workspace_helpers_parse_arguments_variable_name var prefix suffix)
    string(JOIN "_" value ${prefix} ${suffix})
    string(TOUPPER ${value} value)
    set(${var} ${value} PARENT_SCOPE)
endfunction()

function(workspace_helpers_get_parse_arguments_value var prefix suffix)
    workspace_helpers_parse_arguments_variable_name(source ${prefix} ${suffix})
    set(${var} ${${source}} ${ARGN} PARENT_SCOPE)
endfunction()

function(workspace_helpers_set_parse_arguments_value value prefix suffix)
    workspace_helpers_parse_arguments_variable_name(var ${prefix} ${suffix})
    set(${var} ${value} ${ARGN} PARENT_SCOPE)
endfunction()

function(workspace_helpers_set_target_version_properties name)
    set(keys
        VERSION
        SOVERSION)

    foreach(key ${keys})
        string(TOLOWER ${key} value_key)
        get_target_property(${value_key} ${name} ${key})

        if (${${value_key}} STREQUAL "${value_key}-NOTFOUND")
            unset(${value_key})
        endif()

        if(NOT DEFINED ${value_key})
          workspace_helpers_get_parse_arguments_value(${value_key} ${name} ${key})
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
           list(APPEND versions ${key} ${${value_key}})
        endif()
   endforeach()
   set_target_properties(${name} PROPERTIES ${versions})
endfunction()


function(workspace_helpers_set_target_cxx_properties name)
    set_target_properties(
        ${name}
        PROPERTIES
        C_STANDARD 23
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
endfunction()

function(workspace_helpers_set_target_pdb_properties name)
  get_target_property(pdb_debug_postfix ${name} DEBUG_POSTFIX)
  
  if(${pdb_debug_postfix} STREQUAL "pdb_debug_postfix-NOTFOUND")
    unset(pdb_debug_postfix)
  endif()

  set_target_properties(${name}
    PROPERTIES
    PDB_NAME "${name}"
    PDB_NAME_DEBUG "${name}${pdb_debug_postfix}"
    COMPILE_PDB_NAME "${name}"
    COMPILE_PDB_NAME_DEBUG "${name}${pdb_debug_postfix}")
endfunction()

function(workspace_helpers_set_target_output_directory_properties name)
       set_target_properties(
        ${name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endfunction()

function(workspace_helpers_set_target_properties name)
    workspace_helpers_set_target_version_properties(${name})
    workspace_helpers_set_target_cxx_properties(${name})
    workspace_helpers_set_target_output_directory_properties(${name})
    workspace_helpers_set_target_pdb_properties(${name})

    workspace_helpers_get_parse_arguments_value(props ${name} PROPERTIES)
    if(DEFINED props)
        set_target_properties(${name} PROPERTIES ${props})
    endif()
endfunction()

macro(workspace_helpers_project name)
    workspace_helpers_parse_arguments(${ARGV})
    workspace_helpers_get_parse_arguments_value(
    workspace_helpers_project_version ${name} VERSION)
    set(PROJECT_TARGET ${name})
    set(PROJECT_EXPORT_TARGET ${WORKSPACE_PACKAGE_NAME}::${name})
    if(NOT DEFINED workspace_helpers_project_version)
        set(workspace_helpers_project_version ${WORKSPACE_PACKAGE_VERSION})
    endif()

    project(
        ${name}
        VERSION ${workspace_helpers_project_version}
        LANGUAGES C CXX
    )
endmacro()

function(workspace_helpers_target_type name var)
    foreach(flag ${workspace_helpers_parse_arguments_flags})
        workspace_helpers_get_parse_arguments_value(present ${name} ${flag})
        if(present)
            set(${var} ${flag} PARENT_SCOPE)
            return()
        endif()

    endforeach()
endfunction()

function(workspace_helpers_resolve_target_sources name)
    set(flags)
    set(args OUTPUT_VARIABLE)
    set(list_args
        ALLOWED_SUBDIRECTORIES
        ALLOWED_FILENAMES
        DISALLOWED_FILENAMES
        DISALLOWED_FILENAME_PATTERNS)

    workspace_helpers_parse_arguments_variable_name(
        prefix
        workspace_helpers_resolve_target_sources
        "")
    cmake_parse_arguments(
        PARSE_ARGV
        1
        ${prefix}
        "${flags}"
        "${args}"
        "${list_args}"
    )

    workspace_helpers_get_parse_arguments_value(
        output_variable
        ${prefix}
        OUTPUT_VARIABLE)

    if(NOT DEFINED output_variable)
        message(FATAL_ERROR "missing OUTPUT_VARIABLE <output_variable>")
    endif()

    workspace_helpers_get_parse_arguments_value(
        allowed_filenames
        ${prefix}
        ALLOWED_FILENAMES)


    string(REGEX REPLACE ${WORKSPACE_TEST_SUFFIX_REGEX} "" name ${name})
    list(APPEND allowed_filenames ${name})
    if(BUILD_TESTING)
        list(APPEND test_suffixes
            "-tests"
            "_tests"
            "-test"
            "_test"
            "Test"
            "Tests"
        )

        foreach(suffix ${test_suffixes})
            list(APPEND allowed_filenames ${name}${suffix})
        endforeach()
    endif()

    workspace_helpers_get_parse_arguments_value(
        disallowed_filenames
        ${prefix}
        DISALLOWED_FILENAMES)

    foreach(filename ${disallowed_filenames})
        list(FIND allowed_filenames ${filename} index)
        while(index GREATER_EQUAL 0)
            list(FIND allowed_filenames ${filename} index)
            list(REMOVE_AT allowed_filenames ${index})
        endwhile()
    endforeach()

    workspace_helpers_get_parse_arguments_value(
        disallowed_filename_patterns
        ${prefix}
        DISALLOWED_FILENAME_PATTERNS)

    foreach(pattern ${disallowed_filename_patterns})
        list(FILTER allowed_filenames EXCLUDE REGEX ${pattern})
    endforeach()

    workspace_helpers_get_parse_arguments_value(
        allowed_subdirectories
        ${prefix}
        ALLOWED_SUBDIRECTORIES)
    list(APPEND allowed_directories ${CMAKE_CURRENT_SOURCE_DIR})

    foreach(item ${allowed_subdirectories})
         cmake_path(
                APPEND CMAKE_CURRENT_SOURCE_DIR
                ${item}
                OUTPUT_VARIABLE directory)
        list(APPEND allowed_directories ${directory})
    endforeach()

    foreach(filename ${allowed_filenames})
        foreach(extension ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS})
            foreach(directory ${allowed_directories})
                cmake_path(
                    APPEND directory
                    ${filename}
                    OUTPUT_VARIABLE filepath)
                cmake_path(
                    REPLACE_EXTENSION filepath ${extension}
                    OUTPUT_VARIABLE filepath)

                if (EXISTS ${filepath})
                    cmake_path(
                        RELATIVE_PATH filepath
                        BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        OUTPUT_VARIABLE filepath)
                    list(APPEND filenames ${filepath})
                    break()
                endif()
            endforeach()
        endforeach()
    endforeach()

    set(${output_variable} ${filenames} PARENT_SCOPE)
endfunction()


macro(library_project name)
    workspace_helpers_project(${name} ${ARGN})
    library_target(${ARGV})
endmacro()

macro(executable_project name)
    workspace_helpers_project(${ARGV})
    unset(PROJECT_EXPORT_TARGET)
    executable_target(${ARGV})
endmacro()

function(library_target name)
    workspace_helpers_parse_arguments(${ARGV})
    workspace_helpers_target_type(${name} type)
    if(NOT DEFINED sources)
       workspace_helpers_resolve_target_sources(
            ${name}
            ALLOWED_SUBDIRECTORIES
                src
            ALLOWED_FILENAMES
                DllMain
            DISALLOWED_FILENAME_PATTERNS
                "${name}${WORKSPACE_TEST_SUFFIX_REGEX}"
            OUTPUT_VARIABLE sources
       )
    endif()
    workspace_helpers_get_parse_arguments_value(sources ${name} SOURCES)
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
        string(TOUPPER "${name}_BUILD_SHARED_LIBRARY" build_shared)
        target_compile_definitions(
            ${name}
            PUBLIC
            ${build_shared}
        )
    endif()

    workspace_helpers_set_target_properties(${name})

    target_include_directories(${name}
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    )
endfunction()


function(executable_target name)
    workspace_helpers_parse_arguments(${ARGV})
    workspace_helpers_get_parse_arguments_value(sources ${name} SOURCES)
    workspace_helpers_target_type(${name} type)

    if(NOT DEFINED sources)
       workspace_helpers_resolve_target_sources(
           ${name}
           ALLOWED_SUBDIRECTORIES
                src
           ALLOWED_FILENAMES
                main
           OUTPUT_VARIABLE sources
       )
    endif()

    add_executable(${name} ${type} ${sources})

    workspace_helpers_set_target_properties(${name})
endfunction()


function(add_test_suite name)
    if(NOT BUILD_TESTING)
        return()
    endif()

    string(REGEX MATCH ${WORKSPACE_TEST_SUFFIX_REGEX} test_suffix ${name})
    set(target_name ${name})
    if(NOT test_suffix)
        set(target_name ${name}_tests)
    endif()

    workspace_helpers_parse_arguments(${target_name} ${ARGN})

    workspace_helpers_target_type(${target_name} type)
    workspace_helpers_get_parse_arguments_value(sources ${target_name} SOURCES)
    if(NOT DEFINED sources)
        if(DEFINED PROJECT_EXPORT_TARGET)
            list(APPEND disallowed_filenames ${name})
        endif()

       workspace_helpers_resolve_target_sources(
           ${name}
           ALLOWED_SUBDIRECTORIES
                src
                test
                tests
           DISALLOWED_FILENAMES
                ${disallowed_filenames}
           OUTPUT_VARIABLE sources
       )
    endif()
    add_executable(${target_name} ${type} ${sources})

    workspace_helpers_set_target_cxx_properties(${target_name})
    workspace_helpers_set_target_output_directory_properties(${target_name})
    workspace_helpers_set_target_pdb_properties(${target_name})

    workspace_helpers_get_parse_arguments_value(props ${target_name} PROPERTIES)
    if(DEFINED props)
        set_target_properties(${target_name} PROPERTIES ${props})
    endif()

    target_link_libraries(${target_name} GTest::gmock_main)

    if(DEFINED PROJECT_EXPORT_TARGET)
        target_link_libraries(${target_name} ${PROJECT_EXPORT_TARGET})
    endif()

    gtest_discover_tests(${target_name})
endfunction()


function(add_sources)
    set(flags)
    set(args TARGET SUBDIRECTORY)
    set(file_list_types INTERFACE PUBLIC  PRIVATE)
    set(list_args ${file_list_types})

    workspace_helpers_parse_arguments_variable_name(
        prefix
        add_sources
        "")
    cmake_parse_arguments(
        PARSE_ARGV
        0
        ${prefix}
        "${flags}"
        "${args}"
        "${list_args}"
    )
    workspace_helpers_get_parse_arguments_value(target ${prefix} TARGET)
    workspace_helpers_get_parse_arguments_value(subdir ${prefix} SUBDIRECTORY)
    if(NOT DEFINED target)
        set(target ${PROJECT_TARGET})
    endif()

    foreach(list_type ${file_list_types})
        workspace_helpers_get_parse_arguments_value(items ${prefix} ${list_type})
        if(DEFINED subdir)
            foreach(item ${items})
                cmake_path(
                    APPEND subdir
                    ${item}
                    OUTPUT_VARIABLE prefixed_item)
                list(APPEND prefixed_items ${prefixed_item})
            endforeach()
            set(items ${prefixed_items})
        endif()

        set(sources ${list_type} ${items})
    endforeach()

    if(NOT DEFINED sources)
        foreach(arg ${ARGV})
            list(FIND args ${arg} index)
            if(index GREATER_EQUAL 0)
                continue()
            endif()

            list(FIND args ${prev} index)
            if(index GREATER_EQUAL 0)
                continue()
            endif()
            set(item ${arg})
            if(DEFINED subdir)
                 cmake_path(
                    APPEND subdir
                    ${item}
                    OUTPUT_VARIABLE item)
            endif()
            set(prev ${arg})
            list(APPEND sources ${item})
        endforeach()
    endif()

    target_sources(${target} ${sources})
endfunction()
