cmake_minimum_required(VERSION 3.4...3.19)
project(lua-primesieve C CXX)
find_package(primesieve REQUIRED)
find_package(Lua 5.4 REQUIRED)
add_library(lua-primesieve SHARED array.c iterator.c lua-primesieve.c)
target_include_directories(lua-primesieve PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(lua-primesieve primesieve::primesieve)
set_target_properties(lua-primesieve PROPERTIES
	PREFIX ""
	OUTPUT_NAME "primesieve"
)
