#cmake 最低版本号要求
cmake_minimum_required (VERSION 2.6)

#项目名
project (TETRIS)

#添加编译选项
add_compile_options(-std=c++11)

#子目录
add_subdirectory (basicfuncs)
add_subdirectory (games)


#子目录头文件
include_directories (basicfuncs)
include_directories (games)

#把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST
aux_source_directory (. SRC_LIST)

#指定生成目标
add_executable (tetris ${SRC_LIST})

#添加链接库
target_link_libraries (tetris games basicfuncs)