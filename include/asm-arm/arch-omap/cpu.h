multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/cpu.h&n; *&n; * OMAP cpu type detection&n; *&n; * Copyright (C) 2004 Nokia Corporation&n; *&n; * Written by Tony Lindgren &lt;tony.lindgren@nokia.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_CPU_H
DECL|macro|__ASM_ARCH_OMAP_CPU_H
mdefine_line|#define __ASM_ARCH_OMAP_CPU_H
r_extern
r_int
r_int
id|system_rev
suffix:semicolon
DECL|macro|OMAP_DIE_ID_0
mdefine_line|#define OMAP_DIE_ID_0&t;&t;0xfffe1800
DECL|macro|OMAP_DIE_ID_1
mdefine_line|#define OMAP_DIE_ID_1&t;&t;0xfffe1804
DECL|macro|OMAP_PRODUCTION_ID_0
mdefine_line|#define OMAP_PRODUCTION_ID_0&t;0xfffe2000
DECL|macro|OMAP_PRODUCTION_ID_1
mdefine_line|#define OMAP_PRODUCTION_ID_1&t;0xfffe2004
DECL|macro|OMAP32_ID_0
mdefine_line|#define OMAP32_ID_0&t;&t;0xfffed400
DECL|macro|OMAP32_ID_1
mdefine_line|#define OMAP32_ID_1&t;&t;0xfffed404
multiline_comment|/*&n; * Test if multicore OMAP support is needed&n; */
DECL|macro|MULTI_OMAP
macro_line|#undef MULTI_OMAP
DECL|macro|OMAP_NAME
macro_line|#undef OMAP_NAME
macro_line|#ifdef CONFIG_ARCH_OMAP730
macro_line|# ifdef OMAP_NAME
DECL|macro|MULTI_OMAP
macro_line|#  undef  MULTI_OMAP
DECL|macro|MULTI_OMAP
macro_line|#  define MULTI_OMAP
macro_line|# else
DECL|macro|OMAP_NAME
macro_line|#  define OMAP_NAME omap730
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1510
macro_line|# ifdef OMAP_NAME
DECL|macro|MULTI_OMAP
macro_line|#  undef  MULTI_OMAP
DECL|macro|MULTI_OMAP
macro_line|#  define MULTI_OMAP
macro_line|# else
DECL|macro|OMAP_NAME
macro_line|#  define OMAP_NAME omap1510
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP16XX
macro_line|# ifdef OMAP_NAME
DECL|macro|MULTI_OMAP
macro_line|#  undef  MULTI_OMAP
DECL|macro|MULTI_OMAP
macro_line|#  define MULTI_OMAP
macro_line|# else
DECL|macro|OMAP_NAME
macro_line|#  define OMAP_NAME omap1610
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP16XX
macro_line|# ifdef OMAP_NAME
DECL|macro|MULTI_OMAP
macro_line|#  undef  MULTI_OMAP
DECL|macro|MULTI_OMAP
macro_line|#  define MULTI_OMAP
macro_line|# else
DECL|macro|OMAP_NAME
macro_line|#  define OMAP_NAME omap1710
macro_line|# endif
macro_line|#endif
multiline_comment|/*&n; * Generate various OMAP cpu specific macros, and cpu class&n; * specific macros&n; */
DECL|macro|GET_OMAP_TYPE
mdefine_line|#define GET_OMAP_TYPE&t;((system_rev &gt;&gt; 24) &amp; 0xff)
DECL|macro|GET_OMAP_CLASS
mdefine_line|#define GET_OMAP_CLASS&t;(system_rev &amp; 0xff)
DECL|macro|IS_OMAP_TYPE
mdefine_line|#define IS_OMAP_TYPE(type, id)&t;&t;&t;&t;&bslash;&n;static inline int is_omap ##type (void)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (GET_OMAP_TYPE == (id)) ? 1 : 0;&t;&t;&bslash;&n;}
DECL|macro|IS_OMAP_CLASS
mdefine_line|#define IS_OMAP_CLASS(class, id)&t;&t;&t;&bslash;&n;static inline int is_omap ##class (void)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (GET_OMAP_CLASS == (id)) ? 1 : 0;&t;&bslash;&n;}
id|IS_OMAP_TYPE
c_func
(paren
l_int|730
comma
l_int|0x07
)paren
id|IS_OMAP_TYPE
c_func
(paren
l_int|1510
comma
l_int|0x15
)paren
id|IS_OMAP_TYPE
c_func
(paren
l_int|1610
comma
l_int|0x16
)paren
id|IS_OMAP_TYPE
c_func
(paren
l_int|5912
comma
l_int|0x16
)paren
id|IS_OMAP_TYPE
c_func
(paren
l_int|1710
comma
l_int|0x17
)paren
id|IS_OMAP_TYPE
c_func
(paren
l_int|2420
comma
l_int|0x24
)paren
id|IS_OMAP_CLASS
c_func
(paren
l_int|7
id|xx
comma
l_int|0x07
)paren
id|IS_OMAP_CLASS
c_func
(paren
l_int|15
id|xx
comma
l_int|0x15
)paren
id|IS_OMAP_CLASS
c_func
(paren
l_int|16
id|xx
comma
l_int|0x16
)paren
id|IS_OMAP_CLASS
c_func
(paren
l_int|24
id|xx
comma
l_int|0x24
)paren
multiline_comment|/*&n; * Macros to group OMAP types into cpu classes.&n; * These can be used in most places.&n; * cpu_is_omap15xx():&t;True for 1510 and 5910&n; * cpu_is_omap16xx():&t;True for 1610, 5912 and 1710&n; */
macro_line|#if defined(MULTI_OMAP)
DECL|macro|cpu_is_omap7xx
macro_line|# define cpu_is_omap7xx()&t;&t;is_omap7xx()
DECL|macro|cpu_is_omap15xx
macro_line|# define cpu_is_omap15xx()&t;&t;is_omap15xx()
macro_line|# if !(defined(CONFIG_ARCH_OMAP1510) || defined(CONFIG_ARCH_OMAP730))
DECL|macro|cpu_is_omap16xx
macro_line|#  define cpu_is_omap16xx()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap16xx()&t;&t;is_omap16xx()
macro_line|# endif
macro_line|#else
macro_line|# if defined(CONFIG_ARCH_OMAP730)
macro_line|#  define cpu_is_omap7xx()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap7xx()&t;&t;0
macro_line|# endif
macro_line|# if defined(CONFIG_ARCH_OMAP1510)
macro_line|#  define cpu_is_omap15xx()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap15xx()&t;&t;0
macro_line|# endif
macro_line|# if defined(CONFIG_ARCH_OMAP16XX)
macro_line|#  define cpu_is_omap16xx()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap16xx()&t;&t;0
macro_line|# endif
macro_line|#endif
macro_line|#if defined(MULTI_OMAP)
DECL|macro|cpu_is_omap730
macro_line|# define cpu_is_omap730()&t;&t;is_omap730()
DECL|macro|cpu_is_omap1510
macro_line|# define cpu_is_omap1510()&t;&t;is_omap1510()
DECL|macro|cpu_is_omap1610
macro_line|# define cpu_is_omap1610()&t;&t;is_omap1610()
DECL|macro|cpu_is_omap5912
macro_line|# define cpu_is_omap5912()&t;&t;is_omap5912()
DECL|macro|cpu_is_omap1710
macro_line|# define cpu_is_omap1710()&t;&t;is_omap1710()
macro_line|#else
macro_line|# if defined(CONFIG_ARCH_OMAP730)
macro_line|#  define cpu_is_omap730()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap730()&t;&t;0
macro_line|# endif
macro_line|# if defined(CONFIG_ARCH_OMAP1510)
macro_line|#  define cpu_is_omap1510()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap1510()&t;&t;0
macro_line|# endif
macro_line|# if defined(CONFIG_ARCH_OMAP16XX)
macro_line|#  define cpu_is_omap1610()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap1610()&t;&t;0
macro_line|# endif
macro_line|# if defined(CONFIG_ARCH_OMAP16XX)
macro_line|#  define cpu_is_omap5912()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap5912()&t;&t;0
macro_line|# endif
macro_line|# if defined(CONFIG_ARCH_OMAP16XX)
macro_line|# define cpu_is_omap1610()&t;&t;is_omap1610()
macro_line|# define cpu_is_omap5912()&t;&t;is_omap5912()
macro_line|# define cpu_is_omap1710()&t;&t;is_omap1710()
macro_line|# else
macro_line|# define cpu_is_omap1610()&t;&t;0
macro_line|# define cpu_is_omap5912()&t;&t;0
macro_line|# define cpu_is_omap1710()&t;&t;0
macro_line|# endif
macro_line|# if defined(CONFIG_ARCH_OMAP2420)
macro_line|#  define cpu_is_omap2420()&t;&t;1
macro_line|# else
macro_line|#  define cpu_is_omap2420()&t;&t;0
macro_line|# endif
macro_line|#endif
macro_line|#endif
eof
