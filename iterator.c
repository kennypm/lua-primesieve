/*
** Lua bindings for primesieve
** Copyright (c) 2025 Kenny Phelps-McKeown
*/

#include "lua-primesieve.h"

luaL_Reg iterator_methods[] = {
    {"jump_to", iterator_jump},
    {"clear", iterator_clear},
    {"next", iterator_next},
    {"prev", iterator_prev},
    {NULL, NULL}
};

int iterator_jump(lua_State *L) {
    primesieve_iterator *it = luaL_checkudata(L, 1, "primesieve_iterator");
    lua_Integer start, stop_hint;
    int top = lua_gettop(L);
    if ( !(1 < top && top < 4) )
        return luaL_error(L, "%s(): expects 1 or 2 arguments", __func__);
    start = luaL_checkinteger(L, 2);
    if (top == 2) stop_hint = it->stop_hint;
    else          stop_hint = luaL_checkinteger(L, 3);
    primesieve_jump_to(it, start, stop_hint);
    return 0;
}

int iterator_clear(lua_State *L) {
    primesieve_iterator *it = luaL_checkudata(L, 1, "primesieve_iterator");
    primesieve_clear(it);
    return 0;
}

int iterator_next(lua_State *L) {
    primesieve_iterator *it = luaL_checkudata(L, 1, "primesieve_iterator");
    lua_pushinteger(L, primesieve_next_prime(it));
    return 1;
}

int iterator_prev(lua_State *L) {
    primesieve_iterator *it = luaL_checkudata(L, 1, "primesieve_iterator");
    lua_pushinteger(L, primesieve_prev_prime(it));
    return 1;
}

luaL_Reg iterator_mt[] = {
    {"__add", iterator_add}, // shorthand for primesieve_next_prime
    {"__sub", iterator_sub}, // shorthand for primesieve_prev_prime
    {"__tostring", iterator_tostring}, // returns it->primes[it->i] string, or "nil"
    {"__gc", iterator_gc},
    {NULL, NULL}
};

int iterator_add(lua_State *L) {
    primesieve_iterator *it = lua_touserdata(L, 1);
    lua_Integer n = luaL_checkinteger(L, 2);
    lua_Integer p;
    if(n<0) for(int i=0; i>n; i--) p = primesieve_prev_prime(it);
    if(n==0) {
        if(it->primes) p = it->primes[it->i];
        else { lua_pushnil(L); return 1; }
    }
    if(n>0) for(int i=0; i<n; i++) p = primesieve_next_prime(it);
    lua_pushinteger(L, p);
    return 1;
}

int iterator_sub(lua_State *L) {
    primesieve_iterator *it = lua_touserdata(L, 1);
    lua_Integer n = luaL_checkinteger(L, 2);
    lua_Integer p;
    if(n<0) for(int i=0; i>n; i--) p = primesieve_next_prime(it);
    if(n==0) {
        if(it->primes) p = it->primes[it->i];
        else { lua_pushnil(L); return 1; }
    }
    if(n>0) for(int i=0; i<n; i++) p = primesieve_prev_prime(it);
    lua_pushinteger(L, p);
    return 1;
}

int iterator_tostring(lua_State *L) {
    primesieve_iterator *it = lua_touserdata(L, 1);
    if(it->primes) {
        lua_pushinteger(L, it->primes[it->i]);
        lua_tostring(L, -1);
    } else lua_pushliteral(L, "nil");
    return 1;
}

int iterator_gc(lua_State *L) {
    primesieve_iterator *it = lua_touserdata(L, 1);
    primesieve_free_iterator(it);
    return 0;
}

int iterator_new(lua_State *L) {
    primesieve_iterator *it = lua_newuserdatauv(L, sizeof(primesieve_iterator), 0);
    luaL_newmetatable(L, "primesieve_iterator");
    luaL_setfuncs(L, iterator_mt, 0);
    luaL_newlib(L, iterator_methods);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);
    primesieve_init(it);

    switch(lua_gettop(L)) {
        case 3:
            it->stop_hint = luaL_checkinteger(L, 2);
        case 2:
            it->start = luaL_checkinteger(L, 1);
        case 1:
            break;
        default:
            return luaL_error(L, "%s(): too many arguments", __func__);
    }

    return 1;
}
