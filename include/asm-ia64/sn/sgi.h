multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SGI_H
DECL|macro|_ASM_IA64_SN_SGI_H
mdefine_line|#define _ASM_IA64_SN_SGI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;&t;&t;/* for copy_??_user */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#ifdef CONFIG_HWGFS_FS
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/sn/hwgfs.h&gt;
DECL|typedef|vertex_hdl_t
r_typedef
id|hwgfs_handle_t
id|vertex_hdl_t
suffix:semicolon
macro_line|#else
DECL|typedef|vertex_hdl_t
r_typedef
id|devfs_handle_t
id|vertex_hdl_t
suffix:semicolon
macro_line|#endif
DECL|typedef|__psint_t
r_typedef
r_int64
id|__psint_t
suffix:semicolon
multiline_comment|/* needed by klgraph.c */
DECL|enumerator|B_FALSE
DECL|enumerator|B_TRUE
DECL|typedef|boolean_t
r_typedef
r_enum
(brace
id|B_FALSE
comma
id|B_TRUE
)brace
id|boolean_t
suffix:semicolon
DECL|macro|ctob
mdefine_line|#define ctob(x)&t;&t;&t;((uint64_t)(x)*NBPC)
DECL|macro|btoc
mdefine_line|#define btoc(x)&t;&t;&t;(((uint64_t)(x)+(NBPC-1))/NBPC)
multiline_comment|/*&n;** Possible return values from graph routines.&n;*/
DECL|enum|graph_error_e
r_typedef
r_enum
id|graph_error_e
(brace
DECL|enumerator|GRAPH_SUCCESS
id|GRAPH_SUCCESS
comma
multiline_comment|/* 0 */
DECL|enumerator|GRAPH_DUP
id|GRAPH_DUP
comma
multiline_comment|/* 1 */
DECL|enumerator|GRAPH_NOT_FOUND
id|GRAPH_NOT_FOUND
comma
multiline_comment|/* 2 */
DECL|enumerator|GRAPH_BAD_PARAM
id|GRAPH_BAD_PARAM
comma
multiline_comment|/* 3 */
DECL|enumerator|GRAPH_HIT_LIMIT
id|GRAPH_HIT_LIMIT
comma
multiline_comment|/* 4 */
DECL|enumerator|GRAPH_CANNOT_ALLOC
id|GRAPH_CANNOT_ALLOC
comma
multiline_comment|/* 5 */
DECL|enumerator|GRAPH_ILLEGAL_REQUEST
id|GRAPH_ILLEGAL_REQUEST
comma
multiline_comment|/* 6 */
DECL|enumerator|GRAPH_IN_USE
id|GRAPH_IN_USE
multiline_comment|/* 7 */
DECL|typedef|graph_error_t
)brace
id|graph_error_t
suffix:semicolon
DECL|macro|KM_SLEEP
mdefine_line|#define KM_SLEEP   0x0000
DECL|macro|KM_NOSLEEP
mdefine_line|#define KM_NOSLEEP 0x0001&t;&t;/* needed by kmem_alloc_node(), kmem_zalloc()&n;&t;&t;&t;&t;&t; * calls */
DECL|macro|VM_NOSLEEP
mdefine_line|#define VM_NOSLEEP 0x0001&t;&t;/* needed kmem_alloc_node(), kmem_zalloc_node&n;&t;&t;&t;&t;&t; * calls */
DECL|macro|XG_WIDGET_PART_NUM
mdefine_line|#define XG_WIDGET_PART_NUM      0xC102          /* KONA/xt_regs.h     XG_XT_PART_NUM_VALUE */
DECL|typedef|vhandl_t
r_typedef
r_uint64
id|vhandl_t
suffix:semicolon
DECL|macro|NBPP
mdefine_line|#define NBPP PAGE_SIZE
DECL|macro|_PAGESZ
mdefine_line|#define _PAGESZ PAGE_SIZE
macro_line|#ifndef D_MP
DECL|macro|D_MP
mdefine_line|#define D_MP 1
macro_line|#endif
macro_line|#ifndef MAXDEVNAME
DECL|macro|MAXDEVNAME
mdefine_line|#define MAXDEVNAME 256
macro_line|#endif
macro_line|#ifndef NBPC
DECL|macro|NBPC
mdefine_line|#define NBPC 0
macro_line|#endif
DECL|typedef|mrlock_t
r_typedef
r_uint64
id|mrlock_t
suffix:semicolon
multiline_comment|/* needed by devsupport.c */
DECL|macro|HUB_PIO_CONVEYOR
mdefine_line|#define HUB_PIO_CONVEYOR 0x1
DECL|macro|CNODEID_NONE
mdefine_line|#define CNODEID_NONE ((cnodeid_t)-1)
DECL|macro|XTALK_PCI_PART_NUM
mdefine_line|#define XTALK_PCI_PART_NUM &quot;030-1275-&quot;
DECL|macro|kdebug
mdefine_line|#define kdebug 0
DECL|macro|COPYIN
mdefine_line|#define COPYIN(a, b, c)&t;&t;copy_from_user(b,a,c)
DECL|macro|COPYOUT
mdefine_line|#define COPYOUT(a, b, c)&t;copy_to_user(b,a,c)
DECL|macro|kvtophys
mdefine_line|#define kvtophys(x)&t;&t;(alenaddr_t) (x)
DECL|macro|POFFMASK
mdefine_line|#define POFFMASK&t;&t;(NBPP - 1)
DECL|macro|poff
mdefine_line|#define poff(X)&t;&t;&t;((__psunsigned_t)(X) &amp; POFFMASK)
DECL|macro|BZERO
mdefine_line|#define BZERO(a,b)&t;&t;memset(a, 0, b)
DECL|macro|kern_malloc
mdefine_line|#define kern_malloc(x)&t;&t;kmalloc(x, GFP_KERNEL)
DECL|macro|kern_free
mdefine_line|#define kern_free(x)&t;&t;kfree(x)
DECL|typedef|cpu_cookie_t
r_typedef
id|cpuid_t
id|cpu_cookie_t
suffix:semicolon
DECL|macro|CPU_NONE
mdefine_line|#define CPU_NONE&t;&t;(-1)
multiline_comment|/*&n; * mutext support mapping&n; */
DECL|macro|mutex_spinlock_init
mdefine_line|#define mutex_spinlock_init(s)&t;spin_lock_init(s)
r_inline
r_static
r_int
r_int
DECL|function|mutex_spinlock
id|mutex_spinlock
c_func
(paren
id|spinlock_t
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|//&t;spin_lock_irqsave(sem, flags);
id|spin_lock
c_func
(paren
id|sem
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
singleline_comment|// #define mutex_spinunlock(s,t)&t;spin_unlock_irqrestore(s,t)
DECL|macro|mutex_spinunlock
mdefine_line|#define mutex_spinunlock(s,t)&t;spin_unlock(s)
DECL|macro|mutex_t
mdefine_line|#define mutex_t&t;&t;&t;struct semaphore
DECL|macro|mutex_init
mdefine_line|#define mutex_init(s)&t;&t;init_MUTEX(s)
DECL|macro|mutex_init_locked
mdefine_line|#define mutex_init_locked(s)&t;init_MUTEX_LOCKED(s)
DECL|macro|mutex_lock
mdefine_line|#define mutex_lock(s)&t;&t;down(s)
DECL|macro|mutex_unlock
mdefine_line|#define mutex_unlock(s)&t;&t;up(s)
DECL|macro|io_splock
mdefine_line|#define io_splock(s)&t;&t;mutex_spinlock(s)
DECL|macro|io_spunlock
mdefine_line|#define io_spunlock(s,t)&t;spin_unlock(s)
DECL|macro|spin_lock_destroy
mdefine_line|#define spin_lock_destroy(s)
macro_line|#if defined(DISABLE_ASSERT)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr)
DECL|macro|ASSERT_ALWAYS
mdefine_line|#define ASSERT_ALWAYS(expr)
macro_line|#else
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr)  do {&t;&bslash;&n;        if(!(expr)) { &bslash;&n;&t;&t;printk( &quot;Assertion [%s] failed! %s:%s(line=%d)&bslash;n&quot;,&bslash;&n;&t;&t;&t;#expr,__FILE__,__FUNCTION__,__LINE__); &bslash;&n;&t;&t;panic(&quot;Assertion panic&bslash;n&quot;); &t;&bslash;&n;        } } while(0)
DECL|macro|ASSERT_ALWAYS
mdefine_line|#define ASSERT_ALWAYS(expr)&t;do {&bslash;&n;        if(!(expr)) { &bslash;&n;&t;&t;printk( &quot;Assertion [%s] failed! %s:%s(line=%d)&bslash;n&quot;,&bslash;&n;&t;&t;&t;#expr,__FILE__,__FUNCTION__,__LINE__); &bslash;&n;&t;&t;panic(&quot;Assertion always panic&bslash;n&quot;); &t;&bslash;&n;        } } while(0)
macro_line|#endif&t;/* DISABLE_ASSERT */
DECL|macro|PRINT_PANIC
mdefine_line|#define PRINT_PANIC&t;&t;panic
multiline_comment|/* print_register() defs */
multiline_comment|/*&n; * register values&n; * map between numeric values and symbolic values&n; */
DECL|struct|reg_values
r_struct
id|reg_values
(brace
DECL|member|rv_value
r_int
r_int
r_int
id|rv_value
suffix:semicolon
DECL|member|rv_name
r_char
op_star
id|rv_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * register descriptors are used for formatted prints of register values&n; * rd_mask and rd_shift must be defined, other entries may be null&n; */
DECL|struct|reg_desc
r_struct
id|reg_desc
(brace
DECL|member|rd_mask
r_int
r_int
r_int
id|rd_mask
suffix:semicolon
multiline_comment|/* mask to extract field */
DECL|member|rd_shift
r_int
id|rd_shift
suffix:semicolon
multiline_comment|/* shift for extracted value, - &gt;&gt;, + &lt;&lt; */
DECL|member|rd_name
r_char
op_star
id|rd_name
suffix:semicolon
multiline_comment|/* field name */
DECL|member|rd_format
r_char
op_star
id|rd_format
suffix:semicolon
multiline_comment|/* format to print field */
DECL|member|rd_values
r_struct
id|reg_values
op_star
id|rd_values
suffix:semicolon
multiline_comment|/* symbolic names of values */
)brace
suffix:semicolon
r_extern
r_void
id|print_register
c_func
(paren
r_int
r_int
r_int
comma
r_struct
id|reg_desc
op_star
)paren
suffix:semicolon
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
DECL|macro|DELAY
mdefine_line|#define DELAY(a)
multiline_comment|/************************************************&n; * Routines redefined to use linux equivalents. *&n; ************************************************/
multiline_comment|/* #define FIXME(s) printk(&quot;FIXME: [ %s ] in %s at %s:%d&bslash;n&quot;, s, __FUNCTION__, __FILE__, __LINE__) */
DECL|macro|FIXME
mdefine_line|#define FIXME(s)
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
DECL|macro|splx
mdefine_line|#define splx(s)
r_extern
r_void
op_star
id|snia_kmem_alloc_node
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
id|snia_kmem_zalloc
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
id|snia_kmem_zalloc_node
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
r_int
id|is_specified
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_SGI_H */
eof
