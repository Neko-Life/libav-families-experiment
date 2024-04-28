add_custom_target(clean-all
  COMMAND ${CMAKE_COMMAND} --build . --target clean # --config $<CONFIG>
  )

# ================================================================================

set(LIBOPUS_TARGET "libopus" CACHE INTERNAL "")

set(LIBOPUS_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opus/build" CACHE INTERNAL "")
set(LIBOPUS_INCLUDE_DIR "${LIBOPUS_BUILD_DIR}/include" CACHE INTERNAL "")
set(LIBOPUS_LIBDIR "${LIBOPUS_BUILD_DIR}/lib" CACHE INTERNAL "")
set(LIBOPUS_SO "${LIBOPUS_LIBDIR}/libopus.so" CACHE INTERNAL "")

file(GLOB_RECURSE LIBOPUS_SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opus/src/*.c")
file(GLOB_RECURSE LIBOPUS_HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opus/src/*.h")

set(LIBOPUS_OBJECT_FILES ${LIBOPUS_SOURCE_FILES})
list(TRANSFORM LIBOPUS_OBJECT_FILES REPLACE "\.c$" ".o")

add_dependencies(${MAIN_OUT} ${LIBOPUS_TARGET})
add_custom_target(${LIBOPUS_TARGET} DEPENDS ${LIBOPUS_SO})

add_custom_command(
  OUTPUT ${LIBOPUS_SO}
  COMMAND make install
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opus
  DEPENDS ${LIBOPUS_OBJECT_FILES})

add_custom_command(
  OUTPUT ${LIBOPUS_OBJECT_FILES}
  COMMAND ./autogen.sh && ./configure --prefix="${LIBOPUS_BUILD_DIR}"
          --exec-prefix="${LIBOPUS_BUILD_DIR}" && make && make check
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opus
  DEPENDS ${LIBOPUS_SOURCE_FILES} ${LIBOPUS_HEADER_FILES})

add_dependencies(clean-all ${LIBOPUS_TARGET}-clean)

add_custom_target(${LIBOPUS_TARGET}-clean
  COMMAND rm -rf build
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opus)

# ================================================================================

set(LIBOGG_TARGET "libogg" CACHE INTERNAL "")

set(LIBOGG_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ogg/build/build" CACHE INTERNAL "")
set(LIBOGG_INCLUDE_DIR "${LIBOGG_BUILD_DIR}/include" CACHE INTERNAL "")
set(LIBOGG_LIBDIR "${LIBOGG_BUILD_DIR}/lib" CACHE INTERNAL "")
set(LIBOGG_SO "${LIBOGG_LIBDIR}/libogg.so" CACHE INTERNAL "")

file(GLOB_RECURSE LIBOGG_SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/ogg/src/*.c")
   file(GLOB_RECURSE LIBOGG_HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/ogg/src/*.h")

   add_dependencies(${MAIN_OUT} ${LIBOGG_TARGET})
   add_custom_target(${LIBOGG_TARGET} DEPENDS ${LIBOGG_SO})

add_custom_command(
  OUTPUT ${LIBOGG_SO}
  COMMAND mkdir -p build && cd build && cmake .. -DBUILD_SHARED_LIBS=1 --install-prefix="${CMAKE_CURRENT_SOURCE_DIR}/ogg/build/build" && make && make test && make install
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ogg
  DEPENDS ${LIBOGG_SOURCE_FILES} ${LIBOGG_HEADER_FILES})

add_dependencies(clean-all ${LIBOGG_TARGET}-clean)

add_custom_target(${LIBOGG_TARGET}-clean
  COMMAND rm -rf build
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ogg)

# ================================================================================

set(OPUSFILE_TARGET "libopusfile" CACHE INTERNAL "")

set(OPUSFILE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opusfile/build/build" CACHE INTERNAL "")
set(OPUSFILE_INCLUDE_DIR "${OPUSFILE_BUILD_DIR}/include" CACHE INTERNAL "")
set(OPUSFILE_LIBDIR "${OPUSFILE_BUILD_DIR}/lib" CACHE INTERNAL "")
set(OPUSFILE_SO "${OPUSFILE_LIBDIR}/libopusfile.so" CACHE INTERNAL "")

file(GLOB_RECURSE OPUSFILE_SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opusfile/src/*.c")
   file(GLOB_RECURSE OPUSFILE_HEADER_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/opusfile/src/*.h")

   add_dependencies(${MAIN_OUT} ${OPUSFILE_TARGET})
   add_custom_target(${OPUSFILE_TARGET} DEPENDS ${OPUSFILE_SO})

add_custom_command(
  OUTPUT ${OPUSFILE_SO}
  COMMAND mkdir -p build && cd build && cmake .. -DBUILD_SHARED_LIBS=1 --install-prefix="${CMAKE_CURRENT_SOURCE_DIR}/opusfile/build/build" && make && make test && make install
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opusfile
  DEPENDS ${OPUSFILE_SOURCE_FILES} ${OPUSFILE_HEADER_FILES})

add_dependencies(clean-all ${OPUSFILE_TARGET}-clean)

add_custom_target(${OPUSFILE_TARGET}-clean
  COMMAND rm -rf build
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/opusfile)
