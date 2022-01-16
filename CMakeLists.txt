CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(PA1 CXX)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

ADD_SUBDIRECTORY(deps/vecmath)

SET(PA1_SOURCES
        src/image.cpp
        src/main.cpp
        # src/mesh.cpp
        # src/scene_parser.cpp
        )

SET(PA1_INCLUDES
        include/image.hpp
        include/ray.hpp
        # include/scene_parser.hpp
        include/hittable.hpp
        include/ncamera.hpp
        include/ncolor.hpp
        include/nmaterial.hpp
        include/nsphere.hpp
        include/hittable_list.hpp
        include/utils.hpp
        include/scenes.hpp
        include/ntriangle.hpp
        include/moving_sphere.hpp
        include/aabb.hpp
        include/texture.hpp
        include/perlin.hpp
        include/stb_image.h
        include/constant_medium.hpp
        include/translate.hpp
        include/mesh.hpp
        )

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

ADD_EXECUTABLE(${PROJECT_NAME} ${PA1_SOURCES} ${PA1_INCLUDES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} vecmath)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE include)
