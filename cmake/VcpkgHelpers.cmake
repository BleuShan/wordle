include_guard()

include(WorkspaceUtilities)

function(declare_vpckg_packages)
  list(APPEND declared_vcpkg_packages $CACHE{VCPKG_DECLARED_PACKAGES} ${ARGV})
  list(REMOVE_DUPLICATES declared_vcpkg_packages)
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
  make_cmake_variable_name(
    OUTPUT_VARIABLE varname
    VCPKG
    ${package_name}
    features)
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

      make_cmake_variable_name(
        OUTPUT_VARIABLE varname
        VCPKG
        ${package_name}
        features)

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
        list_contains(features ${feature} has_feature)
        if(NOT has_feature)
          list(APPEND install_list "${package_name}[${feature}]")
        endif()
      endforeach()

      if(default_install)
        list(APPEND install_list "${package_name}")
      endif()
    endforeach()

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

function(setup_vcpkg)
  if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT
      $ENV{VCPKG_ROOT}
      CACHE STRING "Vcpkg root directory")
  elseif(NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT
      ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
      CACHE STRING "Vcpkg root directory")
  endif()

  if(VCPKG_ROOT STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    set(LOCAL_VCPKG_ROOT ON)
  endif()


  set(VCPKG_EXECUTABLE
    ${VCPKG_ROOT}/vcpkg
    CACHE STRING "Vcpkg executable")

  set(VCPKG_BOOTSTRAP_SCRIPT
    ${VCPKG_ROOT}/bootstrap-vcpkg.sh
    CACHE STRING "Vcpkg bootstrap script"
  )

  if(CMAKE_HOST_WIN32)
    set(VCPKG_EXECUTABLE
      ${VCPKG_EXECUTABLE}.exe
      CACHE STRING "Vcpkg executable")

    set(VCPKG_BOOTSTRAP_SCRIPT
      ${VCPKG_ROOT}/bootstrap-vcpkg.bat
      CACHE STRING "Vcpkg bootstrap script"
    )
  endif()

  if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET $ENV{VCPKG_DEFAULT_TRIPLET} CACHE STRING "")
  endif()

  set(CMAKE_TOOLCHAIN_FILE
    ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")

  if(LOCAL_VCPKG_ROOT)
    execute_process(
          COMMAND git
          submodule
          update
          "--init"
          "--recursive"
        )
  endif()

  if(NOT EXISTS ${VCPKG_EXECUTABLE})
    execute_process(COMMAND ${VCPKG_BOOTSTRAP_SCRIPT})
  endif()

  if(NOT DEFINED VCPKG_TARGET_TRIPLET)
      message(FATAL "")
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

  set(VCPKG_COMMAND_ARGS
      "--x-json;--triplet=${VCPKG_TARGET_TRIPLET}"
      CACHE
      STRING
      "Common vcpkg command arguments"
      FORCE
  )

  mark_as_advanced(FORCE
    CMAKE_TOOLCHAIN_FILE
    VCPKG_EXECUTABLE
    VCPKG_BOOTSTRAP_SCRIPT
    VCPKG_COMMAND_ARGS
  )
endfunction()
