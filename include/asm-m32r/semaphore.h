macro_line|#ifndef _ASM_M32R_SEMAPHORE_H
DECL|macro|_ASM_M32R_SEMAPHORE_H
mdefine_line|#define _ASM_M32R_SEMAPHORE_H
multiline_comment|/* $Id$ */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * Modified 1996-12-23 by Dave Grothe &lt;dave@gcom.com&gt; to fix bugs in&n; *                     the original code and to make semaphore waits&n; *                     interruptible so that processes waiting on&n; *                     semaphores can be killed.&n; * Modified 1999-02-14 by Andrea Arcangeli, split the sched.c helper&n; *&t;&t;       functions in asm/sempahore-helper.h while fixing a&n; *&t;&t;       potential and subtle race discovered by Ulrich Schmid&n; *&t;&t;       in down_interruptible(). Since I started to play here I&n; *&t;&t;       also implemented the `trylock&squot; semaphore operation.&n; *          1999-07-02 Artur Skawina &lt;skawina@geocities.com&gt;&n; *                     Optimized &quot;0(ecx)&quot; -&gt; &quot;(ecx)&quot; (the assembler does not&n; *                     do this). Changed calling sequences from push/jmp to&n; *                     traditional call/ret.&n; * Modified 2001-01-01 Andreas Franck &lt;afranck@gmx.de&gt;&n; *&t;&t;       Some hacks to ensure compatibility with recent&n; *&t;&t;       GCC snapshots, to avoid stack corruption when compiling&n; *&t;&t;       with -fomit-frame-pointer. It&squot;s not sure if this will&n; *&t;&t;       be fixed in GCC, as our previous implementation was a&n; *&t;&t;       bit dubious.&n; *&n; * If you would like to see an analysis of this implementation, please&n; * ftp to gcom.com and download the file&n; * /pub/linux/src/semaphore/semaphore-2.0.24.tar.gz.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
DECL|macro|LOAD
macro_line|#undef LOAD
DECL|macro|STORE
macro_line|#undef STORE
macro_line|#ifdef CONFIG_SMP
DECL|macro|LOAD
mdefine_line|#define LOAD&t;&quot;lock&quot;
DECL|macro|STORE
mdefine_line|#define STORE&t;&quot;unlock&quot;
macro_line|#else
DECL|macro|LOAD
mdefine_line|#define LOAD&t;&quot;ld&quot;
DECL|macro|STORE
mdefine_line|#define STORE&t;&quot;st&quot;
macro_line|#endif
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|sleepers
r_int
id|sleepers
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name) &bslash;&n;&t;&t;, (int)&amp;(name).__magic
macro_line|#else
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name)
macro_line|#endif
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ ATOMIC_INIT(count), 0, __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name) &bslash;&n;&t;__SEMAPHORE_INITIALIZER(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count) &bslash;&n;&t;struct semaphore name = __SEMAPHORE_INITIALIZER(name,count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name) __DECLARE_SEMAPHORE_GENERIC(name,1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name) __DECLARE_SEMAPHORE_GENERIC(name,0)
DECL|function|sema_init
r_static
id|__inline__
r_void
id|sema_init
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_int
id|val
)paren
(brace
multiline_comment|/*&n; *&t;*sem = (struct semaphore)__SEMAPHORE_INITIALIZER((*sem),val);&n; *&n; * i&squot;d rather use the more flexible initialization above, but sadly&n; * GCC 2.7.2.3 emits a bogus warning. EGCS doesnt. Oh well.&n; */
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|val
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|sem-&gt;__magic
op_assign
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
suffix:semicolon
macro_line|#endif
)brace
DECL|function|init_MUTEX
r_static
id|__inline__
r_void
id|init_MUTEX
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|sema_init
c_func
(paren
id|sem
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|init_MUTEX_LOCKED
r_static
id|__inline__
r_void
id|init_MUTEX_LOCKED
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|sema_init
c_func
(paren
id|sem
comma
l_int|0
)paren
suffix:semicolon
)brace
id|asmlinkage
r_void
id|__down_failed
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_failed_interruptible
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_failed_trylock
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up_wakeup
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
multiline_comment|/*&n; * This is ugly, but we want the default case to fall through.&n; * &quot;__down_failed&quot; is a special asm handler that calls the C&n; * routine that actually waits. See arch/i386/kernel/semaphore.c&n; */
DECL|function|down
r_static
id|__inline__
r_void
id|down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# down&t;&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
OL
l_int|0
)paren
id|__down
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Interruptible try to acquire a semaphore.  If we obtained&n; * it, return zero.  If we were interrupted, returns -EINTR&n; */
DECL|function|down_interruptible
r_static
id|__inline__
r_int
id|down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# down_interruptible&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
OL
l_int|0
)paren
id|result
op_assign
id|__down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Non-blockingly attempt to down() a semaphore.&n; * Returns zero if we acquired it&n; */
DECL|function|down_trylock
r_static
id|__inline__
r_int
id|down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# down_trylock&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
OL
l_int|0
)paren
id|result
op_assign
id|__down_trylock
c_func
(paren
id|sem
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; * The default case (no contention) will result in NO&n; * jumps for both down() and up().&n; */
DECL|function|up
r_static
id|__inline__
r_void
id|up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# up&t;&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #1;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_le
l_int|0
)paren
id|__up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif  /* _ASM_M32R_SEMAPHORE_H */
eof
