/*
** Lua bindings for primesieve
** Copyright (c) 2025 Kenny Phelps-McKeown
*/

#include "lua.h"
#include "lauxlib.h"
#include <primesieve.h>

#if LUA_VERSION_NUM < 504
#define lua_newuserdatauv(L, size, nuvalue)     \
    lua_newuserdata(L, size)
#endif

typedef struct primesieve_array {
    size_t size;
    lua_Integer *primes;
} primesieve_array;

extern luaL_Reg primes_mt[];
int primes_len(lua_State *L);
int primes_index(lua_State *L);
int primes_gc(lua_State *L);

int primes(lua_State *L);
int n_primes(lua_State *L);
int nth_prime(lua_State *L);
int count_primes(lua_State *L);
int count_twins(lua_State *L);
int count_triplets(lua_State *L);
int count_quadruplets(lua_State *L);
int count_quintuplets(lua_State *L);
int count_sextuplets(lua_State *L);
int print_primes(lua_State *L);
int print_twins(lua_State *L);
int print_triplets(lua_State *L);
int print_quadruplets(lua_State *L);
int print_quintuplets(lua_State *L);
int print_sextuplets(lua_State *L);
int get_sieve_size(lua_State *L);
int get_num_threads(lua_State *L);
int set_sieve_size(lua_State *L);
int set_num_threads(lua_State *L);
int version(lua_State *L);

// methods
extern luaL_Reg iterator_methods[];
int iterator_jump(lua_State *L);
int iterator_clear(lua_State *L);
int iterator_next(lua_State *L);
int iterator_prev(lua_State *L);
// metamethods
extern luaL_Reg iterator_mt[];
int iterator_add(lua_State *L);
int iterator_sub(lua_State *L);
int iterator_tostring(lua_State *L);
int iterator_gc(lua_State *L);
// constructor
int iterator_new(lua_State *L);

int luaopen_primesieve(lua_State *L);
