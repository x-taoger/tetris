#包含头文件
include_directories (../basicfuncs)

#把当前目录(.)下所有源代码文件和头文件加入变量 DIR_GAMES_SRCS
aux_source_directory (. DIR_GAMES_SRCS)

#指定链接库:games
add_library (games ${DIR_GAMES_SRCS})

#添加链接库
#target_link_libraries (games basicfuncs)



