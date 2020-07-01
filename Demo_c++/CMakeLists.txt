#cmake_minimum_required(VERSION 3.2)
cmake_minimum_required(VERSION 3.4.1)

#2.project name，指定项目的名称，一般和项目的文件夹名称对应
project(printInfo)

#3.head file path，头文件目录
#INCLUDE_DIRECTORIES(include)

aux_source_directory(./src cur_srcs_path)

set(cursrc_include_path ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(cur_include_path ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(lib_ffmpeg_path ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${cur_include_path})
include_directories(${cursrc_include_path})
include_directories(${lib_ffmpeg_oath})
#include_directories(${cur_http_path1})
#include_directories(${cur_http_path1})

set(DIR_SRCS ${cur_srcs_path})
message(STATUS "DIR_SRCS = ${DIR_SRCS}")

#6.add executable file，添加要编译的可执行文件
add_executable(${PROJECT_NAME} ${DIR_SRCS})
#ADD_EXECUTABLE(${PROJECT_NAME} ${TEST_MATH})

#7.add link library，添加可执行文件所需要的库，比如我们用到了libm.so（命名规则：lib+name+.so），就添加该库的名称
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)

