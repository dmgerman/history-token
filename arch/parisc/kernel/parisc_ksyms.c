multiline_comment|/*&n; *    Architecture-specific kernel symbols&n; *&n; *    Copyright (C) 2000-2001 Richard Hirst &lt;rhirst with parisc-linux.org&gt;&n; *    Copyright (C) 2001 Dave Kennedy&n; *    Copyright (C) 2001 Paul Bame &lt;bame at parisc-linux.org&gt;&n; *    Copyright (C) 2001-2003 Grant Grundler &lt;grundler with parisc-linux.org&gt;&n; *    Copyright (C) 2002-2003 Matthew Wilcox &lt;willy at parisc-linux.org&gt;&n; *    Copyright (C) 2002 Randolph Chung &lt;tausq at parisc-linux.org&gt;&n; *    Copyright (C) 2002-2003 Helge Deller &lt;deller with parisc-linux.org&gt;&n; * &n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
macro_line|#include &lt;linux/pm.h&gt;
DECL|variable|pm_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|pm_power_off
)paren
suffix:semicolon
macro_line|#include &lt;asm/atomic.h&gt;
DECL|variable|__xchg8
id|EXPORT_SYMBOL
c_func
(paren
id|__xchg8
)paren
suffix:semicolon
DECL|variable|__xchg32
id|EXPORT_SYMBOL
c_func
(paren
id|__xchg32
)paren
suffix:semicolon
DECL|variable|__cmpxchg_u32
id|EXPORT_SYMBOL
c_func
(paren
id|__cmpxchg_u32
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|__atomic_hash
id|EXPORT_SYMBOL
c_func
(paren
id|__atomic_hash
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LP64__
DECL|variable|__xchg64
id|EXPORT_SYMBOL
c_func
(paren
id|__xchg64
)paren
suffix:semicolon
DECL|variable|__cmpxchg_u64
id|EXPORT_SYMBOL
c_func
(paren
id|__cmpxchg_u64
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|lcopy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|lcopy_to_user
)paren
suffix:semicolon
DECL|variable|lcopy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|lcopy_from_user
)paren
suffix:semicolon
DECL|variable|lcopy_in_user
id|EXPORT_SYMBOL
c_func
(paren
id|lcopy_in_user
)paren
suffix:semicolon
DECL|variable|lstrncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|lstrncpy_from_user
)paren
suffix:semicolon
DECL|variable|lclear_user
id|EXPORT_SYMBOL
c_func
(paren
id|lclear_user
)paren
suffix:semicolon
DECL|variable|lstrnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|lstrnlen_user
)paren
suffix:semicolon
macro_line|#ifndef __LP64__
multiline_comment|/* Needed so insmod can set dp value */
r_extern
r_int
"$"
id|global
"$"
suffix:semicolon
DECL|variable|$global$
id|EXPORT_SYMBOL
c_func
(paren
"$"
id|global
"$"
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|__ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|__ioremap
)paren
suffix:semicolon
DECL|variable|iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|iounmap
)paren
suffix:semicolon
DECL|variable|__memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy_toio
)paren
suffix:semicolon
DECL|variable|__memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy_fromio
)paren
suffix:semicolon
DECL|variable|__memset_io
id|EXPORT_SYMBOL
c_func
(paren
id|__memset_io
)paren
suffix:semicolon
macro_line|#include &lt;asm/unistd.h&gt;
DECL|variable|sys_open
id|EXPORT_SYMBOL
c_func
(paren
id|sys_open
)paren
suffix:semicolon
DECL|variable|sys_lseek
id|EXPORT_SYMBOL
c_func
(paren
id|sys_lseek
)paren
suffix:semicolon
DECL|variable|sys_read
id|EXPORT_SYMBOL
c_func
(paren
id|sys_read
)paren
suffix:semicolon
DECL|variable|sys_write
id|EXPORT_SYMBOL
c_func
(paren
id|sys_write
)paren
suffix:semicolon
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|variable|__up
id|EXPORT_SYMBOL
c_func
(paren
id|__up
)paren
suffix:semicolon
DECL|variable|__down_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|__down_interruptible
)paren
suffix:semicolon
DECL|variable|__down
id|EXPORT_SYMBOL
c_func
(paren
id|__down
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|remI
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|remU
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|mulI
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_5
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_6
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_9
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_10
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_12
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_7
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_14
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divU_15
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_5
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_6
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_7
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_9
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_10
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_12
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_14
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
"$$"
id|divI_15
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|$$divI
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI
)paren
suffix:semicolon
DECL|variable|$$divU
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU
)paren
suffix:semicolon
DECL|variable|$$remI
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|remI
)paren
suffix:semicolon
DECL|variable|$$remU
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|remU
)paren
suffix:semicolon
DECL|variable|$$mulI
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|mulI
)paren
suffix:semicolon
DECL|variable|$$divU_3
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_3
)paren
suffix:semicolon
DECL|variable|$$divU_5
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_5
)paren
suffix:semicolon
DECL|variable|$$divU_6
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_6
)paren
suffix:semicolon
DECL|variable|$$divU_9
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_9
)paren
suffix:semicolon
DECL|variable|$$divU_10
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_10
)paren
suffix:semicolon
DECL|variable|$$divU_12
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_12
)paren
suffix:semicolon
DECL|variable|$$divU_7
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_7
)paren
suffix:semicolon
DECL|variable|$$divU_14
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_14
)paren
suffix:semicolon
DECL|variable|$$divU_15
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divU_15
)paren
suffix:semicolon
DECL|variable|$$divI_3
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_3
)paren
suffix:semicolon
DECL|variable|$$divI_5
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_5
)paren
suffix:semicolon
DECL|variable|$$divI_6
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_6
)paren
suffix:semicolon
DECL|variable|$$divI_7
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_7
)paren
suffix:semicolon
DECL|variable|$$divI_9
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_9
)paren
suffix:semicolon
DECL|variable|$$divI_10
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_10
)paren
suffix:semicolon
DECL|variable|$$divI_12
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_12
)paren
suffix:semicolon
DECL|variable|$$divI_14
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_14
)paren
suffix:semicolon
DECL|variable|$$divI_15
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|divI_15
)paren
suffix:semicolon
r_extern
r_void
id|__ashrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashldi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__lshrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__muldi3
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__ashldi3
id|EXPORT_SYMBOL
c_func
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
DECL|variable|__muldi3
id|EXPORT_SYMBOL
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
id|asmlinkage
r_void
op_star
id|__canonicalize_funcptr_for_compare
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|variable|__canonicalize_funcptr_for_compare
id|EXPORT_SYMBOL
c_func
(paren
id|__canonicalize_funcptr_for_compare
)paren
suffix:semicolon
macro_line|#ifdef __LP64__
r_extern
r_void
id|__divdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__umoddi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__moddi3
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__divdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__divdi3
)paren
suffix:semicolon
DECL|variable|__udivdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__udivdi3
)paren
suffix:semicolon
DECL|variable|__umoddi3
id|EXPORT_SYMBOL
c_func
(paren
id|__umoddi3
)paren
suffix:semicolon
DECL|variable|__moddi3
id|EXPORT_SYMBOL
c_func
(paren
id|__moddi3
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __LP64__
r_extern
r_void
"$$"
id|dyncall
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|$$dyncall
id|EXPORT_SYMBOL
c_func
(paren
"$$"
id|dyncall
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#include &lt;asm/mmzone.h&gt;
DECL|variable|node_data
id|EXPORT_SYMBOL
c_func
(paren
id|node_data
)paren
suffix:semicolon
DECL|variable|pfnnid_map
id|EXPORT_SYMBOL
c_func
(paren
id|pfnnid_map
)paren
suffix:semicolon
macro_line|#endif
eof
