if(NOT TARGET pdf)
  find_package(compat QUIET PATHS "${CMAKE_CURRENT_LIST_DIR}/../compat")
  find_library(pdf_debug pdf PATHS ${CMAKE_CURRENT_LIST_DIR}/lib/debug NO_DEFAULT_PATH)
  find_library(pdf_release pdf PATHS ${CMAKE_CURRENT_LIST_DIR}/lib/release NO_DEFAULT_PATH)
  if(NOT pdf_debug OR NOT pdf_release)
    message(FATAL_ERROR "Could not find library: pdf")
  endif()
  add_library(pdf STATIC IMPORTED)
  set_target_properties(pdf PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
    INTERFACE_LINK_LIBRARIES "compat"
    IMPORTED_LOCATION_DEBUG "${pdf_debug}"
    IMPORTED_LOCATION_RELEASE "${pdf_release}"
    IMPORTED_CONFIGURATIONS "DEBUG;RELEASE"
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX")
  if(MSVC)
    install(FILES "${CMAKE_CURRENT_LIST_DIR}/lib/$<LOWER_CASE:$<CONFIG>>/pdf.dll" DESTINATION bin)
    file(COPY "${CMAKE_CURRENT_LIST_DIR}/lib/debug/pdf.dll" DESTINATION "${CMAKE_BINARY_DIR}/Debug")
    file(COPY "${CMAKE_CURRENT_LIST_DIR}/lib/release/pdf.dll" DESTINATION "${CMAKE_BINARY_DIR}/Release")
  else()
    if (CMAKE_BUILD_TYPE EQUAL "Debug")
      install(FILES "${CMAKE_CURRENT_LIST_DIR}/lib/debug/libpdf.so" DESTINATION bin)
      file(COPY "${CMAKE_CURRENT_LIST_DIR}/lib/debug/libpdf.so" DESTINATION "${CMAKE_BINARY_DIR}")
    else()
      install(FILES "${CMAKE_CURRENT_LIST_DIR}/lib/release/libpdf.so" DESTINATION bin)
      file(COPY "${CMAKE_CURRENT_LIST_DIR}/lib/release/libpdf.so" DESTINATION "${CMAKE_BINARY_DIR}")
    endif()
  endif()
endif()
