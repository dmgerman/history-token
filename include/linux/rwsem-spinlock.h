multiline_comment|/* rwsem-spinlock.h: fallback C implementation&n; *&n; * Copyright (c) 2001   David Howells (dhowells@redhat.com).&n; * - Derived partially from ideas by Andrea Arcangeli &lt;andrea@suse.de&gt;&n; * - Derived also from comments by Linus&n; */
macro_line|#ifndef _LINUX_RWSEM_SPINLOCK_H
DECL|macro|_LINUX_RWSEM_SPINLOCK_H
mdefine_line|#define _LINUX_RWSEM_SPINLOCK_H
macro_line|#ifndef _LINUX_RWSEM_H
macro_line|#error please dont include linux/rwsem-spinlock.h directly, use linux/rwsem.h instead
macro_line|#endif
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
r_struct
id|rwsem_waiter
suffix:semicolon
multiline_comment|/*&n; * the rw-semaphore definition&n; * - if activity is 0 then there are no active readers or writers&n; * - if activity is +ve then that is the number of active readers&n; * - if activity is -1 then there is one active writer&n; * - if wait_list is not empty, then there are processes waiting for the semaphore&n; */
DECL|struct|rw_semaphore
r_struct
id|rw_semaphore
(brace
DECL|member|activity
id|__s32
id|activity
suffix:semicolon
DECL|member|wait_lock
id|spinlock_t
id|wait_lock
suffix:semicolon
DECL|member|wait_list
r_struct
id|list_head
id|wait_list
suffix:semicolon
macro_line|#if RWSEM_DEBUG
DECL|member|debug
r_int
id|debug
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * initialisation&n; */
macro_line|#if RWSEM_DEBUG
DECL|macro|__RWSEM_DEBUG_INIT
mdefine_line|#define __RWSEM_DEBUG_INIT      , 0
macro_line|#else
DECL|macro|__RWSEM_DEBUG_INIT
mdefine_line|#define __RWSEM_DEBUG_INIT&t;/* */
macro_line|#endif
DECL|macro|__RWSEM_INITIALIZER
mdefine_line|#define __RWSEM_INITIALIZER(name) &bslash;&n;{ 0, SPIN_LOCK_UNLOCKED, LIST_HEAD_INIT((name).wait_list) __RWSEM_DEBUG_INIT }
DECL|macro|DECLARE_RWSEM
mdefine_line|#define DECLARE_RWSEM(name) &bslash;&n;&t;struct rw_semaphore name = __RWSEM_INITIALIZER(name)
r_extern
r_void
id|FASTCALL
c_func
(paren
id|init_rwsem
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_RWSEM_SPINLOCK_H */
eof
