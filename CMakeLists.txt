cmake_minimum_required (VERSION 2.6)
project (OXYGINE_FACEBOOK)

set(OXYGINE_FACEBOOK_INCLUDE_DIRS 
	${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${OXYGINE_FACEBOOK_INCLUDE_DIRS})
add_library(oxygine-facebook STATIC 
	src/facebook.cpp 
	src/facebook.h
	src/sim/FacebookSimulator.cpp 
	src/sim/FacebookSimulator.h
)

#target_link_libraries(oxyginemagicparticles)

set(OXYGINE_FACEBOOK_INCLUDE_DIRS ${OXYGINE_FACEBOOK_INCLUDE_DIRS} PARENT_SCOPE)
set(OXYGINE_FACEBOOK_LIBS ${OXYGINE_FACEBOOK_LIBS} PARENT_SCOPE)