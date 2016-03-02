macro_line|#ifndef _I386_SEMAPHORE_H
DECL|macro|_I386_SEMAPHORE_H
mdefine_line|#define _I386_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * Modified 1996-12-23 by Dave Grothe &lt;dave@gcom.com&gt; to fix bugs in&n; *                     the original code and to make semaphore waits&n; *                     interruptible so that processes waiting on&n; *                     semaphores can be killed.&n; * Modified 1999-02-14 by Andrea Arcangeli, split the sched.c helper&n; *&t;&t;       functions in asm/sempahore-helper.h while fixing a&n; *&t;&t;       potential and subtle race discovered by Ulrich Schmid&n; *&t;&t;       in down_interruptible(). Since I started to play here I&n; *&t;&t;       also implemented the `trylock&squot; semaphore operation.&n; *          1999-07-02 Artur Skawina &lt;skawina@geocities.com&gt;&n; *                     Optimized &quot;0(ecx)&quot; -&gt; &quot;(ecx)&quot; (the assembler does not&n; *                     do this). Changed calling sequences from push/jmp to&n; *                     traditional call/ret.&n; * Modified 2001-01-01 Andreas Franck &lt;afranck@gmx.de&gt;&n; *&t;&t;       Some hacks to ensure compatibility with recent&n; *&t;&t;       GCC snapshots, to avoid stack corruption when compiling&n; *&t;&t;       with -fomit-frame-pointer. It&squot;s not sure if this will&n; *&t;&t;       be fixed in GCC, as our previous implementation was a&n; *&t;&t;       bit dubious.&n; *&n; * If you would like to see an analysis of this implementation, please&n; * ftp to gcom.com and download the file&n; * /pub/linux/src/semaphore/semaphore-2.0.24.tar.gz.&n; *&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
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
)brace
suffix:semicolon
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name, n)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.count&t;&t;= ATOMIC_INIT(n),&t;&t;&t;&t;&bslash;&n;&t;.sleepers&t;= 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.wait&t;&t;= __WAIT_QUEUE_HEAD_INITIALIZER((name).wait)&t;&bslash;&n;}
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
r_inline
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
multiline_comment|/*&n; *&t;*sem = (struct semaphore)__SEMAPHORE_INITIALIZER((*sem),val);&n; *&n; * i&squot;d rather use the more flexible initialization above, but sadly&n; * GCC 2.7.2.3 emits a bogus warning. EGCS doesn&squot;t. Oh well.&n; */
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
)brace
DECL|function|init_MUTEX
r_static
r_inline
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
r_inline
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
id|fastcall
r_void
id|__down_failed
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|fastcall
r_int
id|__down_failed_interruptible
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|fastcall
r_int
id|__down_failed_trylock
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|fastcall
r_void
id|__up_wakeup
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|fastcall
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
id|fastcall
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
id|fastcall
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
id|fastcall
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
r_inline
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic down operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;decl %0&bslash;n&bslash;t&quot;
multiline_comment|/* --sem-&gt;count */
l_string|&quot;js 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;&quot;
)paren
l_string|&quot;2:&bslash;tlea %0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;call __down_failed&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
id|LOCK_SECTION_END
suffix:colon
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;ax&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Interruptible try to acquire a semaphore.  If we obtained&n; * it, return zero.  If we were interrupted, returns -EINTR&n; */
DECL|function|down_interruptible
r_static
r_inline
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
id|result
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic interruptible down operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
multiline_comment|/* --sem-&gt;count */
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;&quot;
)paren
l_string|&quot;2:&bslash;tlea %1,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;call __down_failed_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
id|LOCK_SECTION_END
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Non-blockingly attempt to down() a semaphore.&n; * Returns zero if we acquired it&n; */
DECL|function|down_trylock
r_static
r_inline
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
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic interruptible down operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
multiline_comment|/* --sem-&gt;count */
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;&quot;
)paren
l_string|&quot;2:&bslash;tlea %1,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;call __down_failed_trylock&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
id|LOCK_SECTION_END
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; * The default case (no contention) will result in NO&n; * jumps for both down() and up().&n; */
DECL|function|up
r_static
r_inline
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic up operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;incl %0&bslash;n&bslash;t&quot;
multiline_comment|/* ++sem-&gt;count */
l_string|&quot;jle 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;&quot;
)paren
l_string|&quot;2:&bslash;tlea %0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;call __up_wakeup&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
id|LOCK_SECTION_END
l_string|&quot;.subsection 0&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;ax&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
