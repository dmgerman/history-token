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
multiline_comment|/*&n; * Hardware Graph routines that are currently stubbed!&n; */
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
DECL|macro|DELAY
mdefine_line|#define DELAY(a)
DECL|macro|cpuid
mdefine_line|#define cpuid() 0
multiline_comment|/************************************************&n; * Routines redefined to use linux equivalents. *&n; ************************************************/
DECL|macro|FIXME
mdefine_line|#define FIXME(s) printk(&quot;FIXME: [ %s ] in %s at %s:%d&bslash;n&quot;, s, __FUNCTION__, __FILE__, __LINE__)
DECL|macro|sv_init
mdefine_line|#define sv_init(a,b,c)          FIXME(&quot;Fixme: sv_init : no-op&quot;)
DECL|macro|sv_wait
mdefine_line|#define sv_wait(a,b,c,d)        FIXME(&quot;Fixme: sv_wait : no-op&quot;)
DECL|macro|sv_broadcast
mdefine_line|#define sv_broadcast(a)  &t;FIXME(&quot;Fixme: sv_broadcast : no-op&quot;)
DECL|macro|sv_destroy
mdefine_line|#define sv_destroy(a)&t;&t;FIXME(&quot;Fixme: sv_destroy : no-op&quot;)
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
DECL|function|sv_signal
r_static
r_inline
r_int
id|sv_signal
c_func
(paren
id|sv_t
op_star
id|a
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;sv_signal : return 0&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|cmn_err
mdefine_line|#define cmn_err(x,y...)         { FIXME(&quot;cmn_err : use printk&quot;); printk(x y); }
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
r_extern
r_int
id|badaddr_val
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
comma
r_volatile
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cap_able_cred
c_func
(paren
r_uint64
id|a
comma
r_uint64
id|b
)paren
suffix:semicolon
DECL|macro|_CAP_CRABLE
mdefine_line|#define _CAP_CRABLE(cr,c)&t;(cap_able_cred(cr,c))
DECL|macro|CAP_MEMORY_MGT
mdefine_line|#define CAP_MEMORY_MGT          (0x01LL &lt;&lt; 25)
DECL|macro|CAP_DEVICE_MGT
mdefine_line|#define CAP_DEVICE_MGT          (0x01LL &lt;&lt; 37)
DECL|macro|io_splock
mdefine_line|#define io_splock(l) l
DECL|macro|io_spunlock
mdefine_line|#define io_spunlock(l,s)
multiline_comment|/* move to stubs.c yet */
DECL|macro|spinlock_destroy
mdefine_line|#define spinlock_destroy(a)     /* needed by pcibr_detach() */
DECL|macro|mutex_spinlock
mdefine_line|#define mutex_spinlock(a) 0
DECL|macro|mutex_spinunlock
mdefine_line|#define mutex_spinunlock(a,b)
DECL|macro|mutex_spinlock_spl
mdefine_line|#define mutex_spinlock_spl(x,y) y
DECL|macro|mutex_init
mdefine_line|#define mutex_init(a,b,c)               ;
DECL|macro|mutex_lock
mdefine_line|#define mutex_lock(a,b)                 ;
DECL|macro|mutex_unlock
mdefine_line|#define mutex_unlock(a)                 ;
DECL|macro|dev_to_vhdl
mdefine_line|#define dev_to_vhdl(dev) 0
DECL|macro|get_timestamp
mdefine_line|#define get_timestamp() 0
DECL|macro|us_delay
mdefine_line|#define us_delay(a)
DECL|macro|v_mapphys
mdefine_line|#define v_mapphys(a,b,c) printk(&quot;Fixme: v_mapphys - soft-&gt;base 0x%p&bslash;n&quot;, b);
DECL|macro|splhi
mdefine_line|#define splhi()  0
DECL|macro|spl7
mdefine_line|#define spl7&t;splhi()
DECL|macro|splx
mdefine_line|#define splx(s)
DECL|macro|spinlock_init
mdefine_line|#define spinlock_init(x,name) mutex_init(x, MUTEX_DEFAULT, name);
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
