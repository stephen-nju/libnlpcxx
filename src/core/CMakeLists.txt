cmake_minimum_required(VERSION 3.6)
project(core)

set(CORE
    msgqueue.c
    thrdpool.c
)

add_library(${PROJECT_NAME} OBJECT ${CORE})