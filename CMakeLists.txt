project(SkyLaunch)
cmake_minimum_required(VERSION 2.8)

add_executable(EXE WIN32 WinMain.cpp)
set_target_properties(EXE PROPERTIES OUTPUT_NAME "SkyLaunch")
target_link_libraries(EXE Shlwapi)

add_library(DLL SHARED DLLMain.cpp)
set_target_properties(DLL PROPERTIES OUTPUT_NAME "SkyLaunchHook")
