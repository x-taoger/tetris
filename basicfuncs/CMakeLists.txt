#把当前目录(.)下所有源代码文件和头文件加入变量 DIR_BASICFUNCS_SRCS
aux_source_directory (. DIR_BASICFUNCS_SRCS)

#指定链接库:basicfuncs
add_library (basicfuncs ${DIR_BASICFUNCS_SRCS})

#添加链接库
target_link_libraries (basicfuncs pthread)

