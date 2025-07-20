/*
** Lua bindings for primesieve
** Copyright (c) 2025 Kenny Phelps-McKeown
*/

#include "lua-primesieve.h"

luaL_Reg primes_mt[] = {
    {"__len", primes_len},
    {"__index", primes_index},
    {"__gc", primes_gc},
    {NULL, NULL}
};

int primes_len(lua_State *L) {
    primesieve_array *p = lua_touserdata(L, 1);
    lua_pushinteger(L, p->size);
    return 1;
}

int primes_index(lua_State *L) {
    primesieve_array *p = lua_touserdata(L, 1);
    lua_Integer i = luaL_checkinteger(L, 2);
    if((i > 0) && (i <= p->size))
        lua_pushinteger(L, p->primes[i-1]);
    else if((i < 0) && (i >= -(p->size)))
        lua_pushinteger(L, p->primes[ p->size + i ]);
    else lua_pushnil(L);
    return 1;
}

int primes_gc(lua_State *L) {
    primesieve_array *p = lua_touserdata(L, 1);
    primesieve_free(p->primes);
    return 0;
}
