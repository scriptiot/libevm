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
#ifndef EVM_LUA_H
#define EVM_LUA_H

#include "evm.h"

#include <stdarg.h>

#define LUA_VERSION_MAJOR	"5"
#define LUA_VERSION_MINOR	"3"
#define LUA_VERSION_NUM		503
#define LUA_VERSION_RELEASE	"6"

#define LUA_VERSION	"Lua " LUA_VERSION_MAJOR "." LUA_VERSION_MINOR

#define LUAL_BUFFERSIZE 256

/* thread status */
#define LUA_OK		0
#define LUA_YIELD	1
#define LUA_ERRRUN	2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM	4
#define LUA_ERRGCMM	5
#define LUA_ERRERR	6

#define LUA_WEAK                     __attribute__((weak))
#define LUAMOD_API	extern
#define LUA_API		extern
#define LUALIB_API	LUA_API
/*
** basic types
*/
#define LUA_TNONE		TYPE_UNDEFINED

#define LUA_TNIL		TYPE_NULL
#define LUA_TBOOLEAN		TYPE_BOOLEAN
#define LUA_TNUMBER		TYPE_NUMBER
#define LUA_TSTRING		TYPE_HEAP_STRING
#define LUA_TFSTRING		TYPE_FOREIGN_STRING
#define LUA_TTABLE		TYPE_OBJECT
#define LUA_TFUNCTION		TYPE_FUNCTION
#define LUA_TUSERDATA		TYPE_FOREIGN
#define LUA_TLIGHTUSERDATA	TYPE_FOREIGN

/*
** garbage-collection function and options
*/

#define LUA_GCSTOP		0
#define LUA_GCRESTART		1
#define LUA_GCCOLLECT		2
#define LUA_GCCOUNT		3
#define LUA_GCCOUNTB		4
#define LUA_GCSTEP		5
#define LUA_GCSETPAUSE		6
#define LUA_GCSETSTEPMUL	7
#define LUA_GCISRUNNING		9

#define LUA_REGISTRYINDEX	100

/* predefined references */
#define LUA_NOREF       (-2)
#define LUA_REFNIL      (-1)

#define LUA_INTEGER		int
#define LUAI_UACINT		LUA_INTEGER
#define LUA_UNSIGNED	unsigned LUAI_UACINT
#define LUAI_UACNUMBER	double

typedef struct lua_State {
    evm_t *e;
    evm_val_t *p;
    int argc;
    evm_val_t *v;
    evm_val_t *registry;
    evm_val_t *global;
    evm_val_t *metatable;
} lua_State;

typedef float lua_Number;
typedef int lua_Integer;
typedef LUA_INTEGER lua_Integer;
typedef LUA_UNSIGNED lua_Unsigned;
typedef int (*lua_CFunction) (lua_State *L);

typedef struct luaL_Buffer {
    lua_State * L;
    evm_val_t v;
} luaL_Buffer;

LUA_API void evm_lua_print(char *s, size_t l);
LUA_API void        (lua_pushnil) (lua_State *L);
LUA_API void        (lua_pushnumber) (lua_State *L, lua_Number n);
LUA_API void        (lua_pushinteger) (lua_State *L, lua_Integer n);
LUA_API const char *(lua_pushlstring) (lua_State *L, const char *s, size_t len);
LUA_API const char *(lua_pushstring) (lua_State *L, const char *s);
LUA_API void  (lua_pushboolean) (lua_State *L, int b);
LUA_API void  (lua_pushlightuserdata) (lua_State *L, void *p);
LUA_API int   (lua_pushthread) (lua_State *L);
LUA_API const char *lua_tolstring (lua_State *L, int idx, size_t *len);
LUA_API int lua_istable (lua_State *L, int arg);
LUA_API int lua_gettable (lua_State *L, int idx);
LUA_API int lua_isstring (lua_State *L, int idx);
LUA_API int lua_isinteger(lua_State *L, int idx);
LUA_API int lua_isuserdata (lua_State *L, int idx);
LUA_API int lua_gc (lua_State *L, int what, int data);
LUA_API void lua_pushvalue (lua_State *L, int idx);
LUA_API void *lua_newuserdata (lua_State *L, size_t size);
LUA_API const void *lua_topointer (lua_State *L, int idx);
LUA_API int lua_isfunction(lua_State *L, int idx);
LUA_API int lua_isnone(lua_State *L, int idx);
LUA_API void lua_call(lua_State *L, int nargs, int nresults);
LUA_API void lua_copy (lua_State *L, int fromidx, int toidx); //copy value from fromidx to toidx
LUA_API int lua_gettop (lua_State *L); // number of arguments
LUA_API int lua_getglobal (lua_State *L, const char *name);// get global variable
LUA_API int lua_type (lua_State *L, int idx);// get type
LUA_API void lua_settop (lua_State *L, int idx);//set current stack to idx value
LUA_API size_t lua_stringtonumber (lua_State *L, const char *s);
LUA_API void lua_concat (lua_State *L, int n) ;
LUA_API int lua_error (lua_State *L);
LUA_API int lua_getmetatable (lua_State *L, int objindex);
LUA_API int lua_setmetatable (lua_State *L, int objindex);
LUA_API void lua_rotate (lua_State *L, int idx, int n);
LUA_API int lua_toboolean (lua_State *L, int idx);
LUA_API const char *lua_pushfstring (lua_State *L, const char *fmt, ...);
LUA_API lua_Integer lua_tointeger (lua_State *L, int idx);
LUA_API lua_Number lua_tonumber (lua_State *L, int idx);
LUA_API const char *lua_typename (lua_State *L, int t);
LUA_API int lua_checkstack (lua_State *L, int n);
LUA_API void *lua_touserdata (lua_State *L, int idx);
LUA_API void lua_insert(lua_State *L, int idx);
LUA_API void lua_remove(lua_State *L, int idx);
LUA_API int lua_rawgeti (lua_State *L, int idx, lua_Integer n);
LUA_API void lua_pop(lua_State *L, int idx);
LUA_API void lua_lock(lua_State *L);
LUA_API void lua_unlock(lua_State *L);

#define lua_tostring(L,i)	lua_tolstring(L, (i), NULL)
#define lua_islightuserdata(L,n)	(lua_type(L, (n)) == LUA_TLIGHTUSERDATA)
#define lua_assert EVM_ASSERT
#define lua_upvalueindex(i)	(LUA_REGISTRYINDEX - (i))
#define lua_pushliteral(L, s)	lua_pushstring(L, "" s)
#define lua_replace(L,idx)	(lua_copy(L, -1, (idx)), lua_pop(L, 1))
#define lua_writestring(s,l)    evm_lua_print(s, l)
#define lua_writeline()        (lua_writestring("\n", 1), fflush(stdout))

void evm_lua_init(evm_t * e, lua_State *L);
lua_State * evm_lua_get_state(void);
void evm_lua_native_init(lua_State *L, evm_t * e, evm_val_t * p, int argc, evm_val_t * v);
evm_val_t evm_lua_native_return(lua_State *L, int n);

/************* 非用户使用的API ****************/
static inline int _evm_lua_check_argc(lua_State *L, int offset){
    if( L->argc <= offset) {
        return 0;
    }
    return 1;
}

static inline evm_val_t * _evm_lua_arg_offset(lua_State *L, int idx) {
    if( idx > 0) {
        return L->v + idx - 1;
    }
    else {
        return L->e->sp + (idx + 1);
    }
}

static inline void _evm_lua_push(lua_State *L, evm_val_t v){
    ++L->e->sp;
    *L->e->sp = v;
}
#endif
