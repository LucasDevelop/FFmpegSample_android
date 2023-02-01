cmake_minimum_required(VERSION 3.18.1)
# Declares and names the project.
project("av_cpp_sample")
#设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#设置ffmpeg路径
set(ffmpeg_dir ${CMAKE_SOURCE_DIR}/ffmpeg)
set(ffmpeg_lib ${CMAKE_SOURCE_DIR}/ffmpeg/lib/${ANDROID_ABI})
include_directories(${ffmpeg_dir}/include)
link_directories(${ffmpeg_lib})
add_library(avutil SHARED IMPORTED)
add_library(avcodec SHARED IMPORTED)
add_library(avdevice SHARED IMPORTED)
add_library(avformat SHARED IMPORTED)
add_library(swresample SHARED IMPORTED)
add_library(swscale SHARED IMPORTED)
add_library(avfilter SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib}/libavutil.so)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib}/libavcodec.so)
set_target_properties(avdevice PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib}/libavdevice.so)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib}/libavformat.so)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib}/libswresample.so)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib}/libswscale.so)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib}/libavfilter.so)

#将写的cpp代码单独打包动态库av_cpp.so
set(av_cpp_lib_name "av_cpp")
include_directories(${CMAKE_SOURCE_DIR}/src/include)
# 从环境中找库
find_library(
        log-lib
        log)
add_library(
        ${PROJECT_NAME}
        SHARED
        av_cpp_sample.cpp
        ${CMAKE_SOURCE_DIR}/src/log.cpp
        ${CMAKE_SOURCE_DIR}/src/Jni_util.cpp
        ${CMAKE_SOURCE_DIR}/src/audio_record.cpp
        ${CMAKE_SOURCE_DIR}/src/audio_resample.cpp
        ${CMAKE_SOURCE_DIR}/src/audio_encode.cpp
        ${CMAKE_SOURCE_DIR}/src/video_record.cpp
        ${CMAKE_SOURCE_DIR}/src/socket_server.cpp
        ${CMAKE_SOURCE_DIR}/src/socket_client.cpp
)

# 连接库文件
target_link_libraries(
        ${PROJECT_NAME}
        ${log-lib}
        avcodec
        avdevice
        avformat
        swresample
        avutil
        avfilter
        swscale
        )