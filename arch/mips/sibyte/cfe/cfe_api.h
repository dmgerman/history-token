multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*  *********************************************************************&n;    *&n;    *  Broadcom Common Firmware Environment (CFE)&n;    *&n;    *  Device function prototypes&t;&t;File: cfe_api.h&n;    *&n;    *  This file contains declarations for doing callbacks to&n;    *  cfe from an application.  It should be the only header&n;    *  needed by the application to use this library&n;    *&n;    *  Authors:  Mitch Lichtenberg, Chris Demetriou&n;    *&n;    ********************************************************************* */
macro_line|#ifndef CFE_API_H
DECL|macro|CFE_API_H
mdefine_line|#define CFE_API_H
multiline_comment|/*&n; * Apply customizations here for different OSes.  These need to:&n; *&t;* typedef uint64_t, int64_t, intptr_t, uintptr_t.&n; *&t;* define cfe_strlen() if use of an existing function is desired.&n; *&t;* define CFE_API_IMPL_NAMESPACE if API functions are to use&n; *&t;  names in the implementation namespace.&n; * Also, optionally, if the build environment does not do so automatically,&n; * CFE_API_* can be defined here as desired.&n; */
multiline_comment|/* Begin customization. */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|typedef|intptr_t
r_typedef
r_int
r_intptr
suffix:semicolon
DECL|macro|cfe_strlen
mdefine_line|#define cfe_strlen strlen
DECL|macro|CFE_API_ALL
mdefine_line|#define CFE_API_ALL
DECL|macro|CFE_API_STRLEN_CUSTOM
mdefine_line|#define CFE_API_STRLEN_CUSTOM
multiline_comment|/* End customization. */
multiline_comment|/*  *********************************************************************&n;    *  Constants&n;    ********************************************************************* */
multiline_comment|/* Seal indicating CFE&squot;s presence, passed to user program. */
DECL|macro|CFE_EPTSEAL
mdefine_line|#define CFE_EPTSEAL 0x43464531
DECL|macro|CFE_MI_RESERVED
mdefine_line|#define CFE_MI_RESERVED&t;0&t;/* memory is reserved, do not use */
DECL|macro|CFE_MI_AVAILABLE
mdefine_line|#define CFE_MI_AVAILABLE 1&t;/* memory is available */
DECL|macro|CFE_FLG_WARMSTART
mdefine_line|#define CFE_FLG_WARMSTART     0x00000001
DECL|macro|CFE_FLG_FULL_ARENA
mdefine_line|#define CFE_FLG_FULL_ARENA    0x00000001
DECL|macro|CFE_FLG_ENV_PERMANENT
mdefine_line|#define CFE_FLG_ENV_PERMANENT 0x00000001
DECL|macro|CFE_CPU_CMD_START
mdefine_line|#define CFE_CPU_CMD_START 1
DECL|macro|CFE_CPU_CMD_STOP
mdefine_line|#define CFE_CPU_CMD_STOP 0
DECL|macro|CFE_STDHANDLE_CONSOLE
mdefine_line|#define CFE_STDHANDLE_CONSOLE&t;0
DECL|macro|CFE_DEV_NETWORK
mdefine_line|#define CFE_DEV_NETWORK &t;1
DECL|macro|CFE_DEV_DISK
mdefine_line|#define CFE_DEV_DISK&t;&t;2
DECL|macro|CFE_DEV_FLASH
mdefine_line|#define CFE_DEV_FLASH&t;&t;3
DECL|macro|CFE_DEV_SERIAL
mdefine_line|#define CFE_DEV_SERIAL&t;&t;4
DECL|macro|CFE_DEV_CPU
mdefine_line|#define CFE_DEV_CPU&t;&t;5
DECL|macro|CFE_DEV_NVRAM
mdefine_line|#define CFE_DEV_NVRAM&t;&t;6
DECL|macro|CFE_DEV_CLOCK
mdefine_line|#define CFE_DEV_CLOCK           7
DECL|macro|CFE_DEV_OTHER
mdefine_line|#define CFE_DEV_OTHER&t;&t;8
DECL|macro|CFE_DEV_MASK
mdefine_line|#define CFE_DEV_MASK&t;&t;0x0F
DECL|macro|CFE_CACHE_FLUSH_D
mdefine_line|#define CFE_CACHE_FLUSH_D&t;1
DECL|macro|CFE_CACHE_INVAL_I
mdefine_line|#define CFE_CACHE_INVAL_I&t;2
DECL|macro|CFE_CACHE_INVAL_D
mdefine_line|#define CFE_CACHE_INVAL_D&t;4
DECL|macro|CFE_CACHE_INVAL_L2
mdefine_line|#define CFE_CACHE_INVAL_L2&t;8
DECL|macro|CFE_FWI_64BIT
mdefine_line|#define CFE_FWI_64BIT&t;&t;0x00000001
DECL|macro|CFE_FWI_32BIT
mdefine_line|#define CFE_FWI_32BIT&t;&t;0x00000002
DECL|macro|CFE_FWI_RELOC
mdefine_line|#define CFE_FWI_RELOC&t;&t;0x00000004
DECL|macro|CFE_FWI_UNCACHED
mdefine_line|#define CFE_FWI_UNCACHED&t;0x00000008
DECL|macro|CFE_FWI_MULTICPU
mdefine_line|#define CFE_FWI_MULTICPU&t;0x00000010
DECL|macro|CFE_FWI_FUNCSIM
mdefine_line|#define CFE_FWI_FUNCSIM&t;&t;0x00000020
DECL|macro|CFE_FWI_RTLSIM
mdefine_line|#define CFE_FWI_RTLSIM&t;&t;0x00000040
r_typedef
r_struct
(brace
DECL|member|fwi_version
r_int64
id|fwi_version
suffix:semicolon
multiline_comment|/* major, minor, eco version */
DECL|member|fwi_totalmem
r_int64
id|fwi_totalmem
suffix:semicolon
multiline_comment|/* total installed mem */
DECL|member|fwi_flags
r_int64
id|fwi_flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|fwi_boardid
r_int64
id|fwi_boardid
suffix:semicolon
multiline_comment|/* board ID */
DECL|member|fwi_bootarea_va
r_int64
id|fwi_bootarea_va
suffix:semicolon
multiline_comment|/* VA of boot area */
DECL|member|fwi_bootarea_pa
r_int64
id|fwi_bootarea_pa
suffix:semicolon
multiline_comment|/* PA of boot area */
DECL|member|fwi_bootarea_size
r_int64
id|fwi_bootarea_size
suffix:semicolon
multiline_comment|/* size of boot area */
DECL|typedef|cfe_fwinfo_t
)brace
id|cfe_fwinfo_t
suffix:semicolon
multiline_comment|/*&n; * cfe_strlen is handled specially: If already defined, it has been&n; * overridden in this environment with a standard strlen-like function.&n; */
macro_line|#ifdef cfe_strlen
DECL|macro|CFE_API_STRLEN_CUSTOM
macro_line|# define CFE_API_STRLEN_CUSTOM
macro_line|#else
macro_line|# ifdef CFE_API_IMPL_NAMESPACE
DECL|macro|cfe_strlen
macro_line|#  define cfe_strlen(a)&t;&t;&t;__cfe_strlen(a)
macro_line|# endif
r_int
id|cfe_strlen
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Defines and prototypes for functions which take no arguments.&n; */
macro_line|#ifdef CFE_API_IMPL_NAMESPACE
r_int64
id|__cfe_getticks
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|cfe_getticks
mdefine_line|#define cfe_getticks()&t;&t;&t;__cfe_getticks()
macro_line|#else
r_int64
id|cfe_getticks
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Defines and prototypes for the rest of the functions.&n; */
macro_line|#ifdef CFE_API_IMPL_NAMESPACE
DECL|macro|cfe_close
mdefine_line|#define cfe_close(a)&t;&t;&t;__cfe_close(a)
DECL|macro|cfe_cpu_start
mdefine_line|#define cfe_cpu_start(a,b,c,d,e)&t;__cfe_cpu_start(a,b,c,d,e)
DECL|macro|cfe_cpu_stop
mdefine_line|#define cfe_cpu_stop(a)&t;&t;&t;__cfe_cpu_stop(a)
DECL|macro|cfe_enumenv
mdefine_line|#define cfe_enumenv(a,b,d,e,f)&t;&t;__cfe_enumenv(a,b,d,e,f)
DECL|macro|cfe_enummem
mdefine_line|#define cfe_enummem(a,b,c,d,e)&t;&t;__cfe_enummem(a,b,c,d,e)
DECL|macro|cfe_exit
mdefine_line|#define cfe_exit(a,b)&t;&t;&t;__cfe_exit(a,b)
DECL|macro|cfe_flushcache
mdefine_line|#define cfe_flushcache(a)&t;&t;__cfe_cacheflush(a)
DECL|macro|cfe_getdevinfo
mdefine_line|#define cfe_getdevinfo(a)&t;&t;__cfe_getdevinfo(a)
DECL|macro|cfe_getenv
mdefine_line|#define cfe_getenv(a,b,c)&t;&t;__cfe_getenv(a,b,c)
DECL|macro|cfe_getfwinfo
mdefine_line|#define cfe_getfwinfo(a)&t;&t;__cfe_getfwinfo(a)
DECL|macro|cfe_getstdhandle
mdefine_line|#define cfe_getstdhandle(a)&t;&t;__cfe_getstdhandle(a)
DECL|macro|cfe_init
mdefine_line|#define cfe_init(a,b)&t;&t;&t;__cfe_init(a,b)
DECL|macro|cfe_inpstat
mdefine_line|#define cfe_inpstat(a)&t;&t;&t;__cfe_inpstat(a)
DECL|macro|cfe_ioctl
mdefine_line|#define cfe_ioctl(a,b,c,d,e,f)&t;&t;__cfe_ioctl(a,b,c,d,e,f)
DECL|macro|cfe_open
mdefine_line|#define cfe_open(a)&t;&t;&t;__cfe_open(a)
DECL|macro|cfe_read
mdefine_line|#define cfe_read(a,b,c)&t;&t;&t;__cfe_read(a,b,c)
DECL|macro|cfe_readblk
mdefine_line|#define cfe_readblk(a,b,c,d)&t;&t;__cfe_readblk(a,b,c,d)
DECL|macro|cfe_setenv
mdefine_line|#define cfe_setenv(a,b)&t;&t;&t;__cfe_setenv(a,b)
DECL|macro|cfe_write
mdefine_line|#define cfe_write(a,b,c)&t;&t;__cfe_write(a,b,c)
DECL|macro|cfe_writeblk
mdefine_line|#define cfe_writeblk(a,b,c,d)&t;&t;__cfe_writeblk(a,b,c,d)
macro_line|#endif&t;&t;&t;&t;/* CFE_API_IMPL_NAMESPACE */
r_int
id|cfe_close
c_func
(paren
r_int
id|handle
)paren
suffix:semicolon
r_int
id|cfe_cpu_start
c_func
(paren
r_int
id|cpu
comma
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
comma
r_int
id|sp
comma
r_int
id|gp
comma
r_int
id|a1
)paren
suffix:semicolon
r_int
id|cfe_cpu_stop
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_int
id|cfe_enumenv
c_func
(paren
r_int
id|idx
comma
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_char
op_star
id|val
comma
r_int
id|vallen
)paren
suffix:semicolon
r_int
id|cfe_enummem
c_func
(paren
r_int
id|idx
comma
r_int
id|flags
comma
r_uint64
op_star
id|start
comma
r_uint64
op_star
id|length
comma
r_uint64
op_star
id|type
)paren
suffix:semicolon
r_int
id|cfe_exit
c_func
(paren
r_int
id|warm
comma
r_int
id|status
)paren
suffix:semicolon
r_int
id|cfe_flushcache
c_func
(paren
r_int
id|flg
)paren
suffix:semicolon
r_int
id|cfe_getdevinfo
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|cfe_getenv
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|dest
comma
r_int
id|destlen
)paren
suffix:semicolon
r_int
id|cfe_getfwinfo
c_func
(paren
id|cfe_fwinfo_t
op_star
id|info
)paren
suffix:semicolon
r_int
id|cfe_getstdhandle
c_func
(paren
r_int
id|flg
)paren
suffix:semicolon
r_int
id|cfe_init
c_func
(paren
r_uint64
id|handle
comma
r_uint64
id|ept
)paren
suffix:semicolon
r_int
id|cfe_inpstat
c_func
(paren
r_int
id|handle
)paren
suffix:semicolon
r_int
id|cfe_ioctl
c_func
(paren
r_int
id|handle
comma
r_int
r_int
id|ioctlnum
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
op_star
id|retlen
comma
r_uint64
id|offset
)paren
suffix:semicolon
r_int
id|cfe_open
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|cfe_read
c_func
(paren
r_int
id|handle
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|cfe_readblk
c_func
(paren
r_int
id|handle
comma
r_int64
id|offset
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|cfe_setenv
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|val
)paren
suffix:semicolon
r_int
id|cfe_write
c_func
(paren
r_int
id|handle
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|cfe_writeblk
c_func
(paren
r_int
id|handle
comma
r_int64
id|offset
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CFE_API_H */
eof
