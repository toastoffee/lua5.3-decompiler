cmake_minimum_required(VERSION 3.27)
project(lua5_3_decompiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(lua5_3_decompiler
        main.cpp
        src/state/api_stack.cpp
        src/state/api_push.cpp
        src/state/api_access.cpp
        src/number/math.cpp
        src/number/math.h
        src/number/parser.cpp
        src/number/parser.h
        src/state/api_arith.cpp
        src/state/api_compare.cpp
        src/state/api_misc.cpp
        src/state/api_vm.cpp
        src/state/lua_impl.cpp
        src/state/api_get.cpp
        src/state/api_call.cpp
        src/state/api_closure.cpp
        src/api/lua_state.hpp
)
