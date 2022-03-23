include_guard()

macro(workspace_helpers_parse_arguments prefix)
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
       LINK_LIBRARIES
    )

    workspace_helpers_parse_arguments_variable_name(
        normalized_prefix ${prefix} "")
    cmake_parse_arguments(
        ${normalized_prefix}
        "${flags}"
        "${args}"
        "${list_args}"
        ${ARGN}
    )
endmacro()

function(workspace_helpers_parse_arguments_variable_name var prefix suffix)
    string(JOIN "_" value ${prefix} ${suffix})
    string(TOUPPER ${value} value)
    set(${var} ${value} PARENT_SCOPE)
endfunction()

function(workspace_helpers_get_parse_arguments_value var prefix suffix)
    workspace_helpers_parse_arguments_variable_name(source ${prefix} ${suffix})
    list(FIND ARGN CACHE index)
    if(index EQUAL -1)
      list(APPEND ARGN PARENT_SCOPE)
    endif()
    set(${var} ${${source}} ${ARGN})
endfunction()

function(workspace_helpers_set_parse_arguments_value prefix suffix)
    workspace_helpers_parse_arguments_variable_name(var ${prefix} ${suffix})
    list(FIND ARGN CACHE index)
    if(index EQUAL -1)
      list(APPEND ARGN PARENT_SCOPE)
    endif()
    set(${var} ${ARGN})
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
        CXX_STANDARD 23
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
        string(JOIN ";" test_suffixes
            "-tests"
            "_tests"
            "-test"
            "_test"
            "Test"
            "Tests"
        )

        foreach(suffix ${test_suffixes})
            string(CONCAT allowed_filename ${name} ${suffix})
            list(APPEND allowed_filenames ${allowed_filename})
        endforeach()
    endif()

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

    foreach(allowed_filename ${allowed_filenames})
        foreach(directory ${allowed_directories})
            cmake_path(
                APPEND directory
                ${allowed_filename}
                OUTPUT_VARIABLE filename)

            foreach(file_extension ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS})
                cmake_path(
                    REPLACE_EXTENSION filename ${file_extension}
                    OUTPUT_VARIABLE filename)

                if(EXISTS ${filename})
                    list(APPEND filenames ${filename})
                    break()
                endif()
            endforeach()
        endforeach()
    endforeach()

    workspace_helpers_get_parse_arguments_value(
        disallowed_filename_patterns
        ${prefix}
        DISALLOWED_FILENAME_PATTERNS)

    workspace_helpers_get_parse_arguments_value(
        disallowed_filenames
        ${prefix}
        DISALLOWED_FILENAMES)

    foreach(filename ${disallowed_filenames})
        string(JOIN "|" extension_pattern ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS})
        string(REGEX REPLACE "[+]" "[+]" extension_pattern "${extension_pattern}")
        set(file_pattern "${filename}[.](${extension_pattern})$")
        list(APPEND disallowed_filename_patterns "${file_pattern}")
    endforeach()

    foreach(pattern ${disallowed_filename_patterns})
        list(FILTER filenames EXCLUDE REGEX ${pattern})
    endforeach()

    if(DEFINED ${output_variable})
        list(APPEND filenames ${${output_variable}})
    endif()

    set(${output_variable} ${filenames} PARENT_SCOPE)
endfunction()

function(workspace_helpers_set_target_link_librairies name)
    set(list_types INTERFACE PUBLIC PRIVATE)
    set(list_type PRIVATE)
    workspace_helpers_get_parse_arguments_value(items ${name} LINK_LIBRARIES)
    foreach(item ${items})
      list(FIND list_types ${item} index)
      if(index GREATER -1 AND NOT item STREQUAL ${list_type})
        set(list_type ${item})
        continue()
      endif()
      target_link_libraries(${name} ${list_type} ${item})
    endforeach()
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
    workspace_helpers_get_parse_arguments_value(sources ${name} SOURCES)
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
    add_library(${name} ${type} ${sources})
    add_library(${WORKSPACE_PACKAGE_NAME}::${name} ALIAS ${name})

    if(BUILD_SHARED_LIBS OR type STREQUAL "SHARED")
        string(TOUPPER "${name}_exports" define_symbol)
        set_target_properties(
            ${name}
            PROPERTIES
            DEFINE_SYMBOL ${define_symbol}
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

   
    workspace_helpers_set_target_link_librairies(${name})
endfunction()


function(executable_target name)
    workspace_helpers_parse_arguments(${ARGV})
    workspace_helpers_get_parse_arguments_value(sources ${name} SOURCES)
    workspace_helpers_target_type(${name} type)

    workspace_helpers_resolve_target_sources(
        ${name}
        ALLOWED_SUBDIRECTORIES
            src
        ALLOWED_FILENAMES
            main
        OUTPUT_VARIABLE sources
    )

    add_executable(${name} ${type} ${sources})

    workspace_helpers_set_target_properties(${name})
    workspace_helpers_set_target_link_librairies(${name})
endfunction()


function(add_test_suite name)
    if(NOT BUILD_TESTING)
        return()
    endif()

    string(REGEX MATCH ${WORKSPACE_TEST_SUFFIX_REGEX} test_suffix ${name})
    set(target_name ${name})
    if(NOT test_suffix)
        set(target_name ${name}Tests)
    endif()

    workspace_helpers_parse_arguments(${target_name} ${ARGN})

    workspace_helpers_target_type(${target_name} type)
    workspace_helpers_get_parse_arguments_value(sources ${target_name} SOURCES)
    if(DEFINED PROJECT_EXPORT_TARGET)
        list(APPEND disallowed_filenames ${name})
    endif()

    workspace_helpers_resolve_target_sources(
        ${name}
        ALLOWED_SUBDIRECTORIES
            test
            tests
        DISALLOWED_FILENAMES
            ${disallowed_filenames}
        OUTPUT_VARIABLE sources
    )

    add_executable(${target_name} ${type} ${sources})

    workspace_helpers_set_target_cxx_properties(${target_name})
    workspace_helpers_set_target_output_directory_properties(${target_name})
    workspace_helpers_set_target_pdb_properties(${target_name})

    workspace_helpers_get_parse_arguments_value(props ${target_name} PROPERTIES)
    if(DEFINED props)
        set_target_properties(${target_name} PROPERTIES ${props})
    endif()

    workspace_helpers_set_target_link_librairies(${target_name})

    target_link_libraries(
        ${target_name}
        PRIVATE
        GTest::gmock_main
    )

    if(DEFINED PROJECT_EXPORT_TARGET)
        target_link_libraries(${target_name} PRIVATE ${PROJECT_EXPORT_TARGET})
    endif()

    gtest_discover_tests(${target_name})
endfunction()


function(add_sources)
    set(flags)
    set(args TARGET SUBDIRECTORY)
    set(file_list_types INTERFACE PUBLIC PRIVATE)
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

function(declare_vpckg_packages)
  list(APPEND declared_vcpkg_packages $CACHE{VCPKG_DECLARED_PACKAGES} ${ARGV})
  list(REMOVE_DUPLICATES declared_packages)
  set(VCPKG_DECLARED_PACKAGES ${declared_vcpkg_packages} CACHE INTERNAL "List of declared packages" FORCE)
endfunction()

function(set_vcpkg_package_features package_name)
  if(package_name STREQUAL "" OR ARGC LESS 2)
    if(package_name STREQUAL "")
      set(package_name "<package_name>")
    endif()
    message(FATAL "Invalid arguments expected set_vcpkg_package_feature(${package_name} <features>...)")
  endif()
  list(FIND VCPKG_DECLARED_PACKAGES ${package_name} index)
  if(index EQUAL -1)
    message(FATAL "vcpkg package \"${package_name}\" is not declared.")
  endif()
  workspace_helpers_parse_arguments_variable_name(varname "VCPKG_${package_name}" features)
  unset(${varname} CACHE)
  if(ARGV1 STREQUAL "DEFAULT")
    return()
  endif()
  list(REMOVE_DUPLICATES ARGN)
  list(TRANSFORM ARGN STRIP)
  set(${varname} ${ARGN} CACHE STRING "Separated list of ${package_name} features" FORCE)
endfunction()

function(install_declared_vpckg_packages)
    list_vckpg_installed_packages(installed_packages)
    foreach(package_name ${VCPKG_DECLARED_PACKAGES})
      string(JOIN ":" key ${package_name} ${VCPKG_TARGET_TRIPLET})
      string(JSON package_def ERROR_VARIABLE error GET ${installed_packages} ${key})
      
      workspace_helpers_parse_arguments_variable_name(varname "VCPKG_${package_name}" features)
      
      set(default_install OFF)
      if(error STREQUAL NOTFOUND)
        string(JSON features ERROR_VARIABLE error GET ${package_def} features)
        if(error STREQUAL "NOTFOUND")
          string(REGEX REPLACE "^\\[(.+)\\]$" "\\1" features ${features})
          string(REGEX REPLACE "[\" ]" "" features ${features})
          string(REPLACE "," ";" features "${features}")
          string(REPLACE "[]" "" features "${features}")
        else()
          unset(features)
        endif()

        if(NOT DEFINED features)
          unset(${varname} CACHE)
        elseif(NOT DEFINED ${varname})
          set(${varname} ${features} CACHE STRING "Separated list of ${package_name} features")
        endif()
      elseif()
        set(default_install ON)
      endif()
      
      set(declared_features ${${varname}})
     
      foreach(feature ${declared_features})
        set(default_install OFF)
        list(FIND features ${feature} index)
        if(index EQUAL -1)
          list(APPEND install_list "${package_name}[${feature}]")
        endif()
      endforeach()

      if(default_install)
        list(APPEND install_list "${package_name}")
      endif()
    endforeach()

    message("${install_list}")
    
    if(NOT DEFINED install_list)
      execute_process(
         COMMAND ${VCPKG_EXECUTABLE}
         upgrade
         ${ARGV}
      )
    else()
      list(APPEND ARGV "--recurse" "--clean-after-build" ${VCPKG_COMMAND_ARGS})
      list(REMOVE_DUPLICATES ARGV)
      execute_process(
          COMMAND ${VCPKG_EXECUTABLE}
          install
         ${ARGV}
         ${install_list}
      )
    endif()
    
    foreach(package_name ${VCPKG_DECLARED_PACKAGES})
      find_package(${package_name} CONFIG REQUIRED)
    endforeach()
endfunction()

function(list_vckpg_installed_packages outvar)
    list(APPEND ARGN "--x-json" ${VCPKG_COMMAND_ARGS})
    list(REMOVE_DUPLICATES ARGN)
    execute_process(
        COMMAND ${VCPKG_EXECUTABLE}
        list
        ${ARGN}
        OUTPUT_VARIABLE result
    )
    set(${outvar} ${result} PARENT_SCOPE)
endfunction()

function(workspace_normalize_vcpkg_target_triplet)
    if(NOT DEFINED VCPKG_TARGET_TRIPLET)
        return()
    endif()
    string(REGEX MATCH  "^([A-Za-z0-9]+-windows)(-[A-Za-z0-9]+-?)?$"
        is_windows_triplet
        ${VCPKG_TARGET_TRIPLET})
    if(is_windows_triplet)
        return()
    endif()

    if(BUILD_SHARED_LIBS)
       set(linkage dynamic)
    else()
        set(linkage static)
    endif()
    string(
        REGEX
        REPLACE
        "^([A-Za-z0-9]+-[A-Za-z0-9]+)(-static|dynamic)?$"
        "\\1-${linkage}"
        target_triplet
        ${VCPKG_TARGET_TRIPLET}
    )

    set(VCPKG_TARGET_TRIPLET
        "${target_triplet}"
        CACHE
        INTERNAL
        "Vcpkg target triplet (ex x64-windows)")
endfunction()
