cmake_minimum_required(VERSION 3.12)

# Uncomment this and rebuild artifacts to enable debugging
set(CMAKE_BUILD_TYPE Debug)

project(bmi_extensions_c VERSION 1.0.0 DESCRIPTION "BMI Extension Library")
include(CTest)
set(LIB_NAME_CMAKE extendedbmi)

FILE( GLOB SOURCES src/*.c )

# if(WIN32)
#     add_library(extendedbmi src/bmi_extensions.c)
# else()
#     add_library(extendedbmi SHARED src/bmi_extensions.c)
# endif()
# Need a static lib to link module implementations of extension functions

add_library(extendedbmi src/bmi_extensions.c)
target_include_directories( extendedbmi PUBLIC include)

FOREACH( extension ${SOURCES} )
   GET_FILENAME_COMPONENT( extension_lib ${extension} NAME_WE )
   add_library(${extension_lib} ${extension})
   target_include_directories(${extension_lib} PUBLIC include)
   #Needed to link extension to main lib
   target_link_libraries(extendedbmi ${extension_lib})
ENDFOREACH()

add_subdirectory(test)

set_target_properties(extendedbmi PROPERTIES VERSION ${PROJECT_VERSION})

# TODO would need to put all extension headers into public headers...
set_target_properties(extendedbmi PROPERTIES PUBLIC_HEADER include/bmi_extensions.h)

include(GNUInstallDirs)

install(TARGETS extendedbmi
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(extendedbmi.pc.in extendedbmi.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/extendedbmi.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)