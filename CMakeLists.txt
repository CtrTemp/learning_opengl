cmake_minimum_required(VERSION 3.5)#Cmake最低版本

project(test_opengl)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE DEBUG)

aux_source_directory(. SRC_LIST)#添加src目录下的所有源文件
aux_source_directory(./src SRC_LIST)#添加src目录下的所有源文件
aux_source_directory(./shaders SRC_LIST)#添加 shaders 目录下的所有源文件
aux_source_directory(./textures SRC_LIST)#添加 textures 目录下的所有源文件
aux_source_directory(./models SRC_LIST)#添加 models 目录下的所有源文件

include_directories(./ ./include)



#编译列表
add_executable(${PROJECT_NAME} ${SRC_LIST})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} libglfw.so GL libassimp.so)
