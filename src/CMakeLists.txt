add_library(SimpleLib)
add_library(${PROJECT_NAME}::SimpleLib ALIAS SimpleLib)

set(EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/simplelib_export.h)
include(GenerateExportHeader)
generate_export_header(SimpleLib
  EXPORT_FILE_NAME ${EXPORT_HEADER}
  EXPORT_MACRO_NAME SIMPLELIB_EXPORT
)

set(PUBLIC_HEADERS ${EXPORT_HEADER}

  # TODO: Add public headers here
  ../include/simplelib/simplelib.h
)
target_sources(SimpleLib PRIVATE ${PUBLIC_HEADERS}

  # TODO: Add private headers and sources here
  simplelib.cpp
)
set_target_properties(SimpleLib PROPERTIES
  PUBLIC_HEADER "${PUBLIC_HEADERS}"
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_include_directories(SimpleLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GNUInstallDirs)
install(TARGETS SimpleLib EXPORT ${PROJECT_NAME}Config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/$<CONFIG>
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/simplelib
)

# Install PDB files for MSVC debug builds
if(MSVC)
  if(BUILD_SHARED_LIBS)
    install(FILES $<TARGET_PDB_FILE:SimpleLib>
      DESTINATION ${CMAKE_INSTALL_BINDIR}/$<CONFIG> OPTIONAL
    )
  else()
    install(DIRECTORY $<TARGET_FILE_DIR:SimpleLib>/
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG> FILES_MATCHING PATTERN "*.pdb"
    )
  endif()
endif()
