multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Jack Steiner (steiner@sgi.com)&n; */
macro_line|#ifndef _ASM_SN_HACK_H
DECL|macro|_ASM_SN_HACK_H
mdefine_line|#define _ASM_SN_HACK_H
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;&t;&t;/* for copy_??_user */
multiline_comment|/******************************************&n; * Definitions that do not exist in linux *&n; ******************************************/
DECL|typedef|cred_t
r_typedef
r_int
id|cred_t
suffix:semicolon
multiline_comment|/* This is for compilation reasons */
DECL|struct|cred
DECL|member|x
r_struct
id|cred
(brace
r_int
id|x
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|mrlock
mdefine_line|#define mrlock(_s, _t, _u)
DECL|macro|mrunlock
mdefine_line|#define mrunlock(_s)
multiline_comment|/*&n; * Hardware Graph routines that are currently stubbed!&n; */
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
DECL|macro|DELAY
mdefine_line|#define DELAY(a)
DECL|macro|cpuid
mdefine_line|#define cpuid() 0
multiline_comment|/************************************************&n; * Routines redefined to use linux equivalents. *&n; ************************************************/
multiline_comment|/* #define FIXME(s) printk(&quot;FIXME: [ %s ] in %s at %s:%d&bslash;n&quot;, s, __FUNCTION__, __FILE__, __LINE__) */
DECL|macro|FIXME
mdefine_line|#define FIXME(s)
r_extern
id|devfs_handle_t
id|dummy_vrtx
suffix:semicolon
DECL|macro|cpuid_to_vertex
mdefine_line|#define cpuid_to_vertex(cpuid) dummy_vrtx /* (pdaindr[cpuid].pda-&gt;p_vertex) */
DECL|macro|PUTBUF_LOCK
mdefine_line|#define PUTBUF_LOCK(a) { FIXME(&quot;PUTBUF_LOCK&quot;); }
DECL|macro|PUTBUF_UNLOCK
mdefine_line|#define PUTBUF_UNLOCK(a) { FIXME(&quot;PUTBUF_UNLOCK&quot;); }
DECL|typedef|splfunc_t
r_typedef
r_int
(paren
op_star
id|splfunc_t
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* move to stubs.c yet */
DECL|macro|dev_to_vhdl
mdefine_line|#define dev_to_vhdl(dev) 0
DECL|macro|get_timestamp
mdefine_line|#define get_timestamp() 0
DECL|macro|us_delay
mdefine_line|#define us_delay(a)
DECL|macro|v_mapphys
mdefine_line|#define v_mapphys(a,b,c) 0    
singleline_comment|// printk(&quot;Fixme: v_mapphys - soft-&gt;base 0x%p&bslash;n&quot;, b);
DECL|macro|splhi
mdefine_line|#define splhi()  0
DECL|macro|spl7
mdefine_line|#define spl7&t;splhi()
DECL|macro|splx
mdefine_line|#define splx(s)
r_extern
r_void
op_star
id|kmem_alloc_node
c_func
(paren
r_register
r_int
comma
r_register
r_int
comma
id|cnodeid_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kmem_zalloc
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kmem_zalloc_node
c_func
(paren
r_register
r_int
comma
r_register
r_int
comma
id|cnodeid_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kmem_zone_alloc
c_func
(paren
r_register
id|zone_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|zone_t
op_star
id|kmem_zone_init
c_func
(paren
r_register
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kmem_zone_free
c_func
(paren
r_register
id|zone_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|is_specified
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cap_able
c_func
(paren
r_uint64
)paren
suffix:semicolon
r_extern
r_int
id|compare_and_swap_ptr
c_func
(paren
r_void
op_star
op_star
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* _ASM_SN_HACK_H */
eof
