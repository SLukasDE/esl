include(FetchContent)

function(find_package_esa)
    # Default, try 'find_package'. VCPKG or Conan may be used, if enabled
    if(NOT esa_FOUND)
        message(STATUS "Try to find esa by find_package")
        find_package(esa QUIET)
        if(esa_FOUND)
            message(STATUS "esa has been found by using find_package")
        endif()
    endif()

    if(NOT esa_FOUND)
        message(STATUS "Try to find esa by FetchContent")
        FetchContent_Declare(
            esa
            GIT_REPOSITORY https://github.com/SLukasDE/esa
            #GIT_TAG master
            GIT_SHALLOW TRUE
            OVERRIDE_FIND_PACKAGE # 'find_package(...)' will call 'FetchContent_MakeAvailable(...)'
        )
        find_package(esa QUIET)
        if(esa_FOUND)
            message(STATUS "esa has been found by using FetchContent")
        endif()
    endif()

    if(NOT esa_FOUND)
        message(FATAL_ERROR "esa NOT found")
    endif()
endfunction()
