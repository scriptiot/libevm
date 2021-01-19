/****************************************************************************
**
** Copyright (C) 2020 @武汉市字节码科技有限公司
**
** EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
** 支持多种脚本语言，纯Ｃ开发，零依赖，支持主流 ROM > 50KB, RAM > 2KB的MCU;
** 自带垃圾回收（GC），先进的内存管理，无内存碎片。
** EVM 版本	: 1.0
** Email	: scriptiot@aliyun.com
** Website	: https://github.com/scriptiot
**
** 源码简介：
** 本代码是通过EVM的API对LUA虚拟机的API层进行兼容。
**
** 修改记录：
** 2021-01-06       初代版本
****************************************************************************/
#ifndef EVM_LAUXLIB_h
#define EVM_LAUXLIB_h

#include <stddef.h>
#include <stdio.h>

#include "lua.h"

/* extra error code for 'luaL_loadfilex' */
#define LUA_ERRFILE     (LUA_ERRERR+1)

/* key, in the registry, for table of loaded modules */
#define LUA_LOADED_TABLE	"_LOADED"

/* key, in the registry, for table of preloaded loaders */
#define LUA_PRELOAD_TABLE	"_PRELOAD"

typedef struct luaL_Reg {
  const char *name;
  lua_CFunction func;
} luaL_Reg;

LUALIB_API lua_Number luaL_checknumber (lua_State *L, int arg);
LUALIB_API lua_Integer luaL_checkinteger (lua_State *L, int arg);
LUALIB_API const char *luaL_checklstring (lua_State *L, int arg, size_t *len);
LUALIB_API int lua_isnoneornil(lua_State *L, int arg);
LUALIB_API lua_Number luaL_optnumber (lua_State *L, int arg, lua_Number def);
LUALIB_API void luaL_unref (lua_State *L, int t, int ref);
LUALIB_API int luaL_ref (lua_State *L, int t);
LUALIB_API void *luaL_checkudata (lua_State *L, int ud, const char *tname);
LUALIB_API int luaL_argerror (lua_State *L, int arg, const char *extramsg);
LUALIB_API void luaL_pushresult (luaL_Buffer *B);
LUALIB_API void luaL_addlstring (luaL_Buffer *B, const char *s, size_t l);
LUALIB_API void luaL_addstring (luaL_Buffer *B, const char *s);
LUALIB_API void luaL_buffinit (lua_State *L, luaL_Buffer *B);
LUALIB_API void luaL_checkany (lua_State *L, int arg);
LUALIB_API void luaL_checktype (lua_State *L, int arg, int t);
LUALIB_API void luaL_where (lua_State *L, int level);
LUALIB_API int luaL_getmetafield (lua_State *L, int obj, const char *event);
LUALIB_API int luaL_error (lua_State *L, const char *fmt, ...);
LUALIB_API lua_Integer luaL_optinteger (lua_State *L, int arg, lua_Integer def);
LUALIB_API const char *luaL_tolstring (lua_State *L, int idx, size_t *len);
LUALIB_API char *luaL_buffinitsize (lua_State *L, luaL_Buffer *B, size_t sz);
LUALIB_API void luaL_pushresultsize (luaL_Buffer *B, size_t sz);
LUALIB_API const char *luaL_optlstring (lua_State *L, int arg,
                                        const char *def, size_t *len);
LUALIB_API void luaL_checkstack (lua_State *L, int space, const char *msg);

#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d)	(luaL_optlstring(L, (n), (d), NULL))
#define luaL_opt(L,f,n,d)	(lua_isnoneornil(L,(n)) ? (d) : f(L,(n)))
#define luaL_argcheck(L, cond,arg,extramsg)	\
                ((void)((cond) || luaL_argerror(L, (arg), (extramsg))))

#endif


