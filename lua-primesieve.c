/*
** Lua bindings for primesieve
** Copyright (c) 2025 Kenny Phelps-McKeown
*/

/*
** to-do:
** portability to Lua 5.3 (and 5.1?)
** primesieve_get_max_stop?? (UINT64_MAX > DBL_MAX)
*/

#include "lua-primesieve.h"

// for functions with uint64_t return type
#define ps_check_error(x)                                               \
    if ((x) == PRIMESIEVE_ERROR)                                        \
        return luaL_error(L, "%s(): PRIMESIEVE_ERROR", __func__)

int primes(lua_State *L) {
    lua_Integer start, stop;
    int top = lua_gettop(L);
    if( !(0 < top && top < 3) )
        return luaL_error(L, "%s(): expects 1 or 2 arguments", __func__);
    if( top == 1) {
        start = 0;
        stop = luaL_checkinteger(L, 1);
    } else {
        start = luaL_checkinteger(L, 1);
        stop = luaL_checkinteger(L, 2);
    }

    primesieve_array *p = lua_newuserdatauv(L, sizeof(primesieve_array), 0);
    luaL_newmetatable(L, "primesieve_array");
    luaL_setfuncs(L, primes_mt, 0);
    lua_setmetatable(L, -2);

    // portability issue with last arg
    p->primes = primesieve_generate_primes(start, stop, &(p->size), LONGLONG_PRIMES);
    return 1;
}

int n_primes(lua_State *L) {
    lua_Integer n, start;
    int top = lua_gettop(L);
    if( !(0 < top && top < 3) )
        return luaL_error(L, "%s(): expects 1 or 2 arguments", __func__);
    n = luaL_checkinteger(L, 1);
    if( top == 1 ) start = 0;
    else           start = luaL_checkinteger(L, 2);

    primesieve_array *p = lua_newuserdatauv(L, sizeof(primesieve_array), 0);
    luaL_newmetatable(L, "primesieve_array");
    luaL_setfuncs(L, primes_mt, 0);
    lua_setmetatable(L, -2);

    // portability issue with last arg
    p->primes = primesieve_generate_n_primes(n, start, LONGLONG_PRIMES);
    p->size = n;
    return 1;
}

int nth_prime(lua_State *L) {
    lua_Integer n, start;
    int top = lua_gettop(L);
    if( !(0 < top && top < 3) )
        return luaL_error(L, "%s(): expects 1 or 2 arguments", __func__);
    n = luaL_checkinteger(L, 1);
    if( top == 1 ) start = 0;
    else           start = luaL_checkinteger(L, 2);

    uint64_t p = primesieve_nth_prime(n, start);
    ps_check_error(p);
    lua_pushinteger(L, p);
    return 1;
}

int count_primes(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    uint64_t p = primesieve_count_primes(start, stop);
    ps_check_error(p);
    lua_pushinteger(L, p);
    return 1;
}

int count_twins(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    uint64_t p = primesieve_count_twins(start, stop);
    ps_check_error(p);
    lua_pushinteger(L, p);
    return 1;
}

int count_triplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    uint64_t p = primesieve_count_triplets(start, stop);
    ps_check_error(p);
    lua_pushinteger(L, p);
    return 1;
}

int count_quadruplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    uint64_t p = primesieve_count_quadruplets(start, stop);
    ps_check_error(p);
    lua_pushinteger(L, p);
    return 1;
}

int count_quintuplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    uint64_t p = primesieve_count_quintuplets(start, stop);
    ps_check_error(p);
    lua_pushinteger(L, p);
    return 1;
}

int count_sextuplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    uint64_t p = primesieve_count_sextuplets(start, stop);
    ps_check_error(p);
    lua_pushinteger(L, p);
    return 1;
}

int print_primes(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    primesieve_print_primes(start, stop);
    return 0;
}

int print_twins(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    primesieve_print_twins(start, stop);
    return 0;
}

int print_triplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    primesieve_print_triplets(start, stop);
    return 0;
}

int print_quadruplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    primesieve_print_quadruplets(start, stop);
    return 0;
}

int print_quintuplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    primesieve_print_quintuplets(start, stop);
    return 0;
}

int print_sextuplets(lua_State *L) {
    lua_Integer start = luaL_checkinteger(L, 1);
    lua_Integer stop = luaL_checkinteger(L, 2);
    primesieve_print_sextuplets(start, stop);
    return 0;
}

int get_sieve_size(lua_State *L) {
    lua_Integer n = primesieve_get_sieve_size();
    lua_pushinteger(L, n);
    return 1;
}

int get_num_threads(lua_State *L) {
    lua_Integer n = primesieve_get_num_threads();
    lua_pushinteger(L, n);
    return 1;
}

int set_sieve_size(lua_State *L) {
    lua_Integer n = luaL_checkinteger(L, 1);
    primesieve_set_sieve_size(n);
    return 0;
}

int set_num_threads(lua_State *L) {
    lua_Integer n = luaL_checkinteger(L, 1);
    primesieve_set_num_threads(n);
    return 0;
}

int version(lua_State *L) {
    const char *v = primesieve_version();
    lua_pushstring(L, v);
    return 1;
}

static luaL_Reg fns[] = {
    {"primes", primes},
    {"n_primes", n_primes},
    {"nth_prime", nth_prime},
    {"count_primes", count_primes},
    {"count_twins", count_twins},
    {"count_triplets", count_triplets},
    {"count_quadruplets", count_quadruplets},
    {"count_quintuplets", count_quintuplets},
    {"count_sextuplets", count_sextuplets},
    {"print_primes", print_primes},
    {"print_twins", print_twins},
    {"print_triplets", print_triplets},
    {"print_quadruplets", print_quadruplets},
    {"print_quintuplets", print_quintuplets},
    {"print_sextuplets", print_sextuplets},
    {"get_sieve_size", get_sieve_size},
    {"get_num_threads", get_num_threads},
    {"set_sieve_size", set_sieve_size},
    {"set_num_threads", set_num_threads},
    {"version", version},
    {"iterator", iterator_new},
    {NULL, NULL}
};

int luaopen_primesieve(lua_State *L) {
    luaL_newlib(L, fns);
    return 1;
}
