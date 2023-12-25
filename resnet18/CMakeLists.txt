

cmake_minimum_required(VERSION 3.10)

project(resnet18)

add_library(${PROJECT_NAME}
    SHARED
    ${PROJECT_SOURCE_DIR}/src/resnet18.cpp
    ${PROJECT_SOURCE_DIR}/src/resnet18Impl.cpp
    ${CMAKE_SOURCE_DIR}/snpetask/SNPETask.cpp
)

target_link_libraries(${PROJECT_NAME}
    SNPE
    ${PTHREAD_DL_LIBS}
    fmt::fmt
    ${OpenCV_LIBS}
    ${spdlog_LIBRARIES}
)

install(
    TARGETS resnet18
    LIBRARY DESTINATION /home/tanja/work/SNPE_Tutorial/SNPE_Tutorial-main/algs/lib/
)
