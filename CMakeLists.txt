# SPDX-License-Identifier: GPL-2.0-only
# Copyright © Interactive Echoes. All rights reserved.
# Author: mozahzah

cmake_minimum_required(VERSION 3.20)
project(IECore VERSION 1.0.0 LANGUAGES CXX)

set(IECORE_INCLUDE_EXAMPLES FALSE)

message("\n------------------------------------------------------------")
message("${PROJECT_NAME}\n")

message("Compiler Setup")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
message("Using Compiler: ${CMAKE_CXX_COMPILER_ID}")
message("version: ${CMAKE_CXX_COMPILER_VERSION}")
message("CXX standard: ${CMAKE_CXX_STANDARD}")
message("Working environment")
message("System name: ${CMAKE_SYSTEM_NAME}")
message("System version: ${CMAKE_SYSTEM_VERSION}")
message("System processor: ${CMAKE_SYSTEM_PROCESSOR}")
include(GNUInstallDirs)

message("Including Third Party Libraries")
find_package(Vulkan REQUIRED)
set(BUILD_SHARED_LIBS TRUE)
set(GLFW_BUILD_WAYLAND FALSE)
add_subdirectory(ThirdParty/glfw)
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ThirdParty/stb)

message("Gathering ${CMAKE_SYSTEM_NAME} specific files")
if (WIN32)
  set(IMPL_FILE "Implementation/IEWin32.cpp")
elseif(APPLE)
  set(CMAKE_OSX_SYSROOT /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk)
  set(IMPL_FILE "Implementation/IEApple.mm")
elseif(LINUX)
  set(IMPL_FILE "Implementation/IELinux.cpp")
endif()

message("Gathering imgui source files")
set(IMGUI_DIR "ThirdParty/imgui")
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)

set(IMGUI_SOURCE_FILES 
  ${IMGUI_DIR}/imconfig.h
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_internal.h
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui.h
  ${IMGUI_DIR}/imstb_rectpack.h
  ${IMGUI_DIR}/imstb_textedit.h
  ${IMGUI_DIR}/imstb_truetype.h
)
set(IMGUI_VULKAN_SOURCE_FILES 
  ${IMGUI_BACKENDS_DIR}/imgui_impl_vulkan.cpp
  ${IMGUI_BACKENDS_DIR}/imgui_impl_vulkan.h
)
set(IMGUI_GLFW_SOURCE_FILES 
  ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
  ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.h
)

message("Gathering source files")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(EXTENSION_FILES 
  "Extensions/ie.imgui.cpp"
  "Extensions/ie.imgui.h"
)
set(IECore_SOURCE_FILES 
  "Source/IECommon.cpp"
  "Source/IECommon.h"
  "Source/IERenderer.cpp"
  "Source/IERenderer.h"
  "Source/IERenderer.cpp"
  "Source/IEUtils.cpp"
  "Source/IEUtils.h"
)
list(APPEND IECore_SOURCE_FILES ${IMPL_FILE} ${EXTENSION_FILES})

message("Creating Library and setting compile time definitions")
add_library(${PROJECT_NAME} STATIC 
  ${IECore_SOURCE_FILES} 
  ${IMGUI_SOURCE_FILES} 
  ${IMGUI_VULKAN_SOURCE_FILES} 
  ${IMGUI_GLFW_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan glfw stb)
target_include_directories(${PROJECT_NAME} PUBLIC "." ${IMGUI_DIR})
set(IECore_HEADER_FILES "IECore.h")
set_property(TARGET ${PROJECT_NAME} PROPERTY PUBLIC_HEADER ${IECore_HEADER_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE IERESOURCES_DIR="${CMAKE_INSTALL_PREFIX}/IE/Resources" GLFW_INCLUDE_NONE)

message("Linking ${CMAKE_SYSTEM_NAME} specific libraries")
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PUBLIC dwmapi uxtheme)
elseif(APPLE)
  target_link_libraries(${PROJECT_NAME} PUBLIC "-framework Cocoa" "-framework UserNotifications")
elseif(LINUX)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GLIB REQUIRED glib-2.0)
  pkg_check_modules(LIBNOTIFY REQUIRED libnotify)

  target_include_directories(${PROJECT_NAME} PUBLIC 
    ${LIBNOTIFY_INCLUDE_DIRS} 
    ${GLIB_INCLUDE_DIRS})

  target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${LIBNOTIFY_LIBRARIES} 
    ${GLIB_LIBRARIES})
endif()

message("Setting up install")
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources" DESTINATION "IE")
include(InstallRequiredSystemLibraries)

message("Adding extra directories")
if(IECORE_INCLUDE_EXAMPLES)
  add_subdirectory(Examples)
endif()

message("------------------------------------------------------------\n")