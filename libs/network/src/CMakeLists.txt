# Copyright (c) Glyn Matthews 2011.
# Copyright 2011 Dean Michael Berris (dberris@google.com)
# Copyright 2011 Google, Inc.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


include_directories(${CPP-NETLIB_SOURCE_DIR})

file(GLOB_RECURSE CPP-NETLIB_HEADERS
    "${CPP-NETLIB_SOURCE_DIR}/boost/" "*.hpp")

set(CPP-NETLIB_HTTP_SERVER_SRCS server_request_parsers_impl.cpp)
add_library(cppnetlib-server-parsers ${CPP-NETLIB_HTTP_SERVER_SRCS})
set_target_properties(cppnetlib-server-parsers
    PROPERTIES VERSION ${CPPNETLIB_VERSION_STRING}
    SOVERSION ${CPPNETLIB_VERSION_MAJOR}
    PUBLIC_HEADER "${CPP-NETLIB_HEADERS}")
install(TARGETS cppnetlib-server-parsers
    EXPORT cppnetlibTargets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})

set(CPP-NETLIB_HTTP_CLIENT_SRCS client.cpp)
add_library(cppnetlib-client-connections ${CPP-NETLIB_HTTP_CLIENT_SRCS})
set_target_properties(cppnetlib-client-connections
    PROPERTIES VERSION ${CPPNETLIB_VERSION_STRING}
    SOVERSION ${CPPNETLIB_VERSION_MAJOR}
    PUBLIC_HEADER "${CPP-NETLIB_HEADERS}")
target_link_libraries(cppnetlib-client-connections ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
if (OPENSSL_FOUND)
    target_link_libraries(cppnetlib-client-connections ${OPENSSL_LIBRARIES})
    if (CPP-NETLIB_STATIC_OPENSSL)
      if (NOT MSVC AND NOT MINGW AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD") # dynlinker functions are built into libc on FreeBSD
        target_link_libraries(cppnetlib-client-connections "-ldl")
      endif()
    endif()
endif ()
install(TARGETS cppnetlib-client-connections
    EXPORT cppnetlibTargets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
