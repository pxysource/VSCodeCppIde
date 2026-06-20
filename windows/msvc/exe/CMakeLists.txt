cmake_minimum_required(VERSION 3.20)

project(DemoApp VERSION 0.1.0.0 LANGUAGES CXX DESCRIPTION "Demo application")

set(EXPORT_NAME "DemoApp")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("/EHsc")

# 设置安装目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "Installation path" FORCE)

# 编译库的类型，默认为动态库。
option(MY_PROJ_BUILD_STATIC_LIB "Build static library." OFF)

file(GLOB Origin src/*.h src/*.cpp)

set(PROJECT_SOURCES
        ${Origin}
)

if (MY_PROJ_BUILD_STATIC_LIB)
    set(LIB_TYPE "STATIC")
else ()
    set(LIB_TYPE "SHARED")
endif ()

# 设置文件版本信息
if (WIN32)
        # 让CMake处理.rc文件并替换变量
        configure_file(version.rc.in version.rc @ONLY)

        if (MSVC)
                # Find rc.exe.
                find_program(WINDRES rc)
                if (WINDRES)
                        set(RESOURCE_FILES version.rc)
                endif()
        else ()
                # 检测windres资源编译器（MinGW下使用），find windres.exe。
                find_program(WINDRES windres)
                if (WINDRES)
                        set(RESOURCE_FILES version.rc)
                endif()
        endif ()
else ()
endif ()

add_executable(${EXPORT_NAME}
        ${PROJECT_SOURCES}
        ${RESOURCE_FILES}
)

if (MSVC)
        # Ensure PDB symbols are generated for DLL debugging.
        target_compile_options(${EXPORT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:/Zi>"
                "$<$<CONFIG:RelWithDebInfo>:/Zi>"
        )
        target_link_options(${EXPORT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:/DEBUG:FULL>"
                "$<$<CONFIG:RelWithDebInfo>:/DEBUG:FULL>"
        )
endif()

# 安装lib文件
#install(TARGETS ${EXPORT_NAME}
#        EXPORT ${EXPORT_NAME}
#        ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#        RUNTIME DESTINATION bin
#)
# 安装lib文件到运行目录：debug配置
install(TARGETS ${EXPORT_NAME}
        CONFIGURATIONS Debug
        RUNTIME DESTINATION bin/debug
)
# 安装lib文件到运行目录：release配置
install(TARGETS ${EXPORT_NAME}
        CONFIGURATIONS Release
        RUNTIME DESTINATION bin/release
)