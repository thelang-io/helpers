#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

include(ExternalProject)
include(ProcessorCount)

ProcessorCount(N)

set(OpenSSL_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/openssl-src")
set(OpenSSL_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/openssl")
set(OpenSSL_INCLUDE_DIR "${OpenSSL_INSTALL_DIR}/include")

if (WIN32)
  set(OpenSSL_MAKE_PROGRAM nmake)
else ()
  set(OpenSSL_MAKE_PROGRAM make -j${N})
endif ()

ExternalProject_Add(
  OpenSSL
  SOURCE_DIR "${OpenSSL_SOURCE_DIR}"
  INSTALL_DIR "${OpenSSL_INSTALL_DIR}"
  GIT_REPOSITORY https://github.com/openssl/openssl.git
  GIT_TAG openssl-3.2.1
  BUILD_BYPRODUCTS
    "${OpenSSL_INSTALL_DIR}/lib/libcrypto${CMAKE_SHARED_LIBRARY_SUFFIX}"
    "${OpenSSL_INSTALL_DIR}/lib/libssl${CMAKE_SHARED_LIBRARY_SUFFIX}"
    "${OpenSSL_INSTALL_DIR}/lib/libcrypto${CMAKE_STATIC_LIBRARY_SUFFIX}"
    "${OpenSSL_INSTALL_DIR}/lib/libssl${CMAKE_STATIC_LIBRARY_SUFFIX}"
  CONFIGURE_COMMAND perl "${OpenSSL_SOURCE_DIR}/Configure" no-docs no-tests --libdir=lib "--prefix=${OpenSSL_INSTALL_DIR}" "--openssldir=${OpenSSL_INSTALL_DIR}"
  BUILD_COMMAND ${OpenSSL_MAKE_PROGRAM}
  INSTALL_COMMAND ${OpenSSL_MAKE_PROGRAM} install_sw
  TEST_COMMAND ""
  UPDATE_COMMAND ""
)

file(MAKE_DIRECTORY "${OpenSSL_INCLUDE_DIR}")

add_library(OpenSSL::Crypto SHARED IMPORTED GLOBAL)
set_property(TARGET OpenSSL::Crypto PROPERTY IMPORTED_LOCATION "${OpenSSL_INSTALL_DIR}/lib/libcrypto${CMAKE_SHARED_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::Crypto PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL_INCLUDE_DIR}")
add_dependencies(OpenSSL::Crypto OpenSSL)

add_library(OpenSSL::Crypto_a STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::Crypto_a PROPERTY IMPORTED_LOCATION "${OpenSSL_INSTALL_DIR}/lib/libcrypto${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::Crypto_a PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL_INCLUDE_DIR}")
add_dependencies(OpenSSL::Crypto_a OpenSSL)

add_library(OpenSSL::SSL SHARED IMPORTED GLOBAL)
set_property(TARGET OpenSSL::SSL PROPERTY IMPORTED_LOCATION "${OpenSSL_INSTALL_DIR}/lib/libssl${CMAKE_SHARED_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::SSL PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL_INCLUDE_DIR}")
add_dependencies(OpenSSL::SSL OpenSSL)

add_library(OpenSSL::SSL_a STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::SSL_a PROPERTY IMPORTED_LOCATION "${OpenSSL_INSTALL_DIR}/lib/libssl${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::SSL_a PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL_INCLUDE_DIR}")
add_dependencies(OpenSSL::SSL_a OpenSSL)
