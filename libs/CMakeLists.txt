add_custom_target(clean-all
  COMMAND ${CMAKE_COMMAND} --build . --target clean # --config $<CONFIG>
  )

set(PKGCONF_PATH "$ENV{PKG_CONFIG_PATH}")

# ================================================================================

set(LIBOPUS_TARGET "libopus" CACHE INTERNAL "")

set(LIBOPUS_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opus/build" CACHE INTERNAL "")
set(LIBOPUS_INCLUDE_DIR "${LIBOPUS_BUILD_DIR}/include" CACHE INTERNAL "")
set(LIBOPUS_LIBDIR "${LIBOPUS_BUILD_DIR}/lib" CACHE INTERNAL "")
set(LIBOPUS_SO "${LIBOPUS_LIBDIR}/libopus.so" CACHE INTERNAL "")
list(APPEND LIBS_TARGETS ${LIBOPUS_SO})

set(LIBOPUS_OPUS_INCLUDE_DIR "${LIBOPUS_INCLUDE_DIR}/opus" CACHE INTERNAL "")

set(LIBS_INCLUDE_DIRS ${LIBOPUS_INCLUDE_DIR} ${LIBOPUS_OPUS_INCLUDE_DIR} ${LIBS_INCLUDE_DIRS} CACHE INTERNAL "")
set(LIBS_LIBDIRS ${LIBOPUS_LIBDIR} ${LIBS_LIBDIRS} CACHE INTERNAL "")

file(GLOB_RECURSE LIBOPUS_SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opus/src/*.c")

file(GLOB_RECURSE LIBOPUS_HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opus/src/*.h")

add_dependencies(${MAIN_OUT} ${LIBOPUS_TARGET})
add_custom_target(${LIBOPUS_TARGET} DEPENDS ${LIBOPUS_SO})

add_custom_command(
  OUTPUT ${LIBOPUS_SO}
  COMMAND ./autogen.sh && ./configure --prefix="${LIBOPUS_BUILD_DIR}"
          --exec-prefix="${LIBOPUS_BUILD_DIR}" && make && make check && make install
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opus
  DEPENDS ${LIBOPUS_SOURCE_FILES} ${LIBOPUS_HEADER_FILES})

set(PKGCONF_PATH "${LIBOPUS_LIBDIR}/pkgconfig:${PKGCONF_PATH}")

add_dependencies(clean-all ${LIBOPUS_TARGET}-clean)

add_custom_target(${LIBOPUS_TARGET}-clean
  COMMAND make uninstall && make clean
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opus)

# ================================================================================

set(LIBOGG_TARGET "libogg" CACHE INTERNAL "")

set(LIBOGG_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ogg/build/build" CACHE INTERNAL "")
set(LIBOGG_INCLUDE_DIR "${LIBOGG_BUILD_DIR}/include" CACHE INTERNAL "")
set(LIBOGG_LIBDIR "${LIBOGG_BUILD_DIR}/lib" CACHE INTERNAL "")
set(LIBOGG_SO "${LIBOGG_LIBDIR}/libogg.so" CACHE INTERNAL "")
list(APPEND LIBS_TARGETS ${LIBOGG_SO})

set(LIBOGG_OGG_INCLUDE_DIR "${LIBOGG_INCLUDE_DIR}/ogg" CACHE INTERNAL "")

set(LIBS_INCLUDE_DIRS ${LIBOGG_INCLUDE_DIR} ${LIBOGG_OGG_INCLUDE_DIR} ${LIBS_INCLUDE_DIRS} CACHE INTERNAL "")
set(LIBS_LIBDIRS ${LIBOGG_LIB_DIR} ${LIBS_LIBDIRS} CACHE INTERNAL "")

file(GLOB_RECURSE LIBOGG_SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/ogg/src/*.c")

file(GLOB_RECURSE LIBOGG_HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/ogg/src/*.h")

add_dependencies(${MAIN_OUT} ${LIBOGG_TARGET})
add_custom_target(${LIBOGG_TARGET} DEPENDS ${LIBOGG_SO})

add_custom_command(
  OUTPUT ${LIBOGG_SO}
  COMMAND PKG_CONFIG_PATH="${PKGCONF_PATH}" mkdir -p build && cd build && cmake .. -DBUILD_SHARED_LIBS=1 --install-prefix="${CMAKE_CURRENT_SOURCE_DIR}/ogg/build/build" && make && make test && make install
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ogg
  DEPENDS ${LIBOGG_SOURCE_FILES} ${LIBOGG_HEADER_FILES} ${LIBOPUS_TARGET})

set(PKGCONF_PATH "${LIBOGG_LIBDIR}/pkgconfig:${PKGCONF_PATH}")

add_dependencies(clean-all ${LIBOGG_TARGET}-clean)

add_custom_target(${LIBOGG_TARGET}-clean
  COMMAND rm -rf build
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ogg)

# ================================================================================

set(OPUSFILE_TARGET "libopusfile" CACHE INTERNAL "")

set(OPUSFILE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opusfile/build" CACHE INTERNAL "")
set(OPUSFILE_INCLUDE_DIR "${OPUSFILE_BUILD_DIR}/include" CACHE INTERNAL "")
set(OPUSFILE_LIBDIR "${OPUSFILE_BUILD_DIR}/lib" CACHE INTERNAL "")
set(OPUSFILE_SO "${OPUSFILE_LIBDIR}/libopusfile.so" CACHE INTERNAL "")
list(APPEND LIBS_TARGETS ${OPUSFILE_SO})

set(OPUSFILE_OPUS_INCLUDE_DIR "${OPUSFILE_INCLUDE_DIR}/opus" CACHE INTERNAL "")

set(LIBS_INCLUDE_DIRS ${OPUSFILE_INCLUDE_DIR} ${OPUSFILE_OPUS_INCLUDE_DIR} ${LIBS_INCLUDE_DIRS} CACHE INTERNAL "")
set(LIBS_LIBDIRS ${OPUSFILE_LIB_DIR} ${LIBS_LIBDIRS} CACHE INTERNAL "")

file(GLOB_RECURSE OPUSFILE_SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opusfile/src/*.c")

file(GLOB_RECURSE OPUSFILE_HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opusfile/src/*.h")

add_dependencies(${MAIN_OUT} ${OPUSFILE_TARGET})
add_custom_target(${OPUSFILE_TARGET} DEPENDS ${OPUSFILE_SO})

add_custom_command(
  OUTPUT ${OPUSFILE_SO}
  COMMAND PKG_CONFIG_PATH="${PKGCONF_PATH}" ./autogen.sh && ./configure --prefix="${OPUSFILE_BUILD_DIR}"
          --exec-prefix="${OPUSFILE_BUILD_DIR}" && make && make check && make install
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opusfile
  DEPENDS ${OPUSFILE_SOURCE_FILES} ${OPUSFILE_HEADER_FILES} ${LIBOPUS_TARGET} ${LIBOGG_TARGET})

add_dependencies(clean-all ${OPUSFILE_TARGET}-clean)

add_custom_target(${OPUSFILE_TARGET}-clean
  COMMAND make uninstall && make clean
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opusfile)

# ================================================================================

if (LIBS_TARGETS)
  add_custom_target(libs DEPENDS ${LIBS_TARGETS})
endif()
