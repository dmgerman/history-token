multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SGI_H
DECL|macro|_ASM_IA64_SN_SGI_H
mdefine_line|#define _ASM_IA64_SN_SGI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;&t;&t;/* for copy_??_user */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
singleline_comment|// This devfs stuff needs a better home .....
DECL|struct|directory_type
r_struct
id|directory_type
(brace
DECL|member|first
r_struct
id|devfs_entry
op_star
id|first
suffix:semicolon
DECL|member|last
r_struct
id|devfs_entry
op_star
id|last
suffix:semicolon
DECL|member|num_removable
r_int
r_int
id|num_removable
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|file_type
r_struct
id|file_type
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|device_type
r_struct
id|device_type
(brace
DECL|member|major
r_int
r_int
id|major
suffix:semicolon
DECL|member|minor
r_int
r_int
id|minor
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fcb_type
r_struct
id|fcb_type
multiline_comment|/*  File, char, block type  */
(brace
DECL|member|default_uid
id|uid_t
id|default_uid
suffix:semicolon
DECL|member|default_gid
id|gid_t
id|default_gid
suffix:semicolon
DECL|member|ops
r_void
op_star
id|ops
suffix:semicolon
r_union
(brace
DECL|member|file
r_struct
id|file_type
id|file
suffix:semicolon
DECL|member|device
r_struct
id|device_type
id|device
suffix:semicolon
)brace
DECL|member|u
id|u
suffix:semicolon
DECL|member|auto_owner
r_int
r_char
id|auto_owner
suffix:colon
l_int|1
suffix:semicolon
DECL|member|aopen_notify
r_int
r_char
id|aopen_notify
suffix:colon
l_int|1
suffix:semicolon
DECL|member|removable
r_int
r_char
id|removable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*  Belongs in device_type, but save space   */
DECL|member|open
r_int
r_char
id|open
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*  Not entirely correct                     */
)brace
suffix:semicolon
DECL|struct|symlink_type
r_struct
id|symlink_type
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/*  Not including the NULL-termimator  */
DECL|member|linkname
r_char
op_star
id|linkname
suffix:semicolon
multiline_comment|/*  This is NULL-terminated            */
)brace
suffix:semicolon
DECL|struct|fifo_type
r_struct
id|fifo_type
(brace
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|devfs_entry
r_struct
id|devfs_entry
(brace
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
r_union
(brace
DECL|member|dir
r_struct
id|directory_type
id|dir
suffix:semicolon
DECL|member|fcb
r_struct
id|fcb_type
id|fcb
suffix:semicolon
DECL|member|symlink
r_struct
id|symlink_type
id|symlink
suffix:semicolon
DECL|member|fifo
r_struct
id|fifo_type
id|fifo
suffix:semicolon
)brace
DECL|member|u
id|u
suffix:semicolon
DECL|member|prev
r_struct
id|devfs_entry
op_star
id|prev
suffix:semicolon
multiline_comment|/*  Previous entry in the parent directory  */
DECL|member|next
r_struct
id|devfs_entry
op_star
id|next
suffix:semicolon
multiline_comment|/*  Next entry in the parent directory      */
DECL|member|parent
r_struct
id|devfs_entry
op_star
id|parent
suffix:semicolon
multiline_comment|/*  The parent directory                    */
DECL|member|slave
r_struct
id|devfs_entry
op_star
id|slave
suffix:semicolon
multiline_comment|/*  Another entry to unregister             */
DECL|member|first_inode
r_struct
id|devfs_inode
op_star
id|first_inode
suffix:semicolon
DECL|member|last_inode
r_struct
id|devfs_inode
op_star
id|last_inode
suffix:semicolon
DECL|member|mode
id|umode_t
id|mode
suffix:semicolon
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
multiline_comment|/*  I think 64k+ filenames are a way off...  */
DECL|member|registered
r_int
r_char
id|registered
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_unreg
r_int
r_char
id|show_unreg
suffix:colon
l_int|1
suffix:semicolon
DECL|member|hide
r_int
r_char
id|hide
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_persistence
r_int
r_char
id|no_persistence
multiline_comment|/*:1*/
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*  This is just a dummy: the allocated array is&n;&t;&t;&t;&t; bigger. This is NULL-terminated  */
)brace
suffix:semicolon
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
macro_line|#ifndef NBPP
DECL|macro|NBPP
mdefine_line|#define NBPP 4096
macro_line|#endif
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
macro_line|#ifndef _PAGESZ
DECL|macro|_PAGESZ
mdefine_line|#define _PAGESZ 4096
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
macro_line|#ifdef CONFIG_SMP
DECL|macro|cpu_enabled
mdefine_line|#define cpu_enabled(cpu)        (test_bit(cpu, &amp;cpu_online_map))
macro_line|#else
DECL|macro|cpu_enabled
mdefine_line|#define cpu_enabled(cpu)&t;(1)
macro_line|#endif
macro_line|#include &lt;asm/sn/hack.h&gt;&t;/* for now */
macro_line|#endif /* _ASM_IA64_SN_SGI_H */
eof
