multiline_comment|/* rwsem.h: R/W semaphores based on spinlocks&n; *&n; * Written by David Howells (dhowells@redhat.com).&n; *&n; * Derived from asm-i386/semaphore.h and asm-i386/spinlock.h&n; */
macro_line|#ifndef _I386_RWSEM_SPIN_H
DECL|macro|_I386_RWSEM_SPIN_H
mdefine_line|#define _I386_RWSEM_SPIN_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _LINUX_RWSEM_H
macro_line|#error please dont include asm/rwsem-spin.h directly, use linux/rwsem.h instead
macro_line|#endif
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * the semaphore definition&n; */
DECL|struct|rw_semaphore
r_struct
id|rw_semaphore
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|macro|RWSEM_UNLOCKED_VALUE
mdefine_line|#define RWSEM_UNLOCKED_VALUE&t;&t;0x00000000
DECL|macro|RWSEM_ACTIVE_BIAS
mdefine_line|#define RWSEM_ACTIVE_BIAS&t;&t;0x00000001
DECL|macro|RWSEM_ACTIVE_MASK
mdefine_line|#define RWSEM_ACTIVE_MASK&t;&t;0x0000ffff
DECL|macro|RWSEM_WAITING_BIAS
mdefine_line|#define RWSEM_WAITING_BIAS&t;&t;(-0x00010000)
DECL|macro|RWSEM_ACTIVE_READ_BIAS
mdefine_line|#define RWSEM_ACTIVE_READ_BIAS&t;&t;RWSEM_ACTIVE_BIAS
DECL|macro|RWSEM_ACTIVE_WRITE_BIAS
mdefine_line|#define RWSEM_ACTIVE_WRITE_BIAS&t;&t;(RWSEM_WAITING_BIAS + RWSEM_ACTIVE_BIAS)
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|macro|RWSEM_SPINLOCK_OFFSET_STR
mdefine_line|#define RWSEM_SPINLOCK_OFFSET_STR&t;&quot;4&quot; /* byte offset of spinlock */
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|macro|RWSEM_WAITING_FOR_READ
mdefine_line|#define RWSEM_WAITING_FOR_READ&t;WQ_FLAG_CONTEXT_0&t;/* bits to use in wait_queue_t.flags */
DECL|macro|RWSEM_WAITING_FOR_WRITE
mdefine_line|#define RWSEM_WAITING_FOR_WRITE&t;WQ_FLAG_CONTEXT_1
macro_line|#if RWSEM_DEBUG
DECL|member|debug
r_int
id|debug
suffix:semicolon
macro_line|#endif
macro_line|#if RWSEM_DEBUG_MAGIC
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
DECL|member|readers
id|atomic_t
id|readers
suffix:semicolon
DECL|member|writers
id|atomic_t
id|writers
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
macro_line|#if RWSEM_DEBUG_MAGIC
DECL|macro|__RWSEM_DEBUG_MINIT
mdefine_line|#define __RWSEM_DEBUG_MINIT(name)&t;, (int)&amp;(name).__magic, ATOMIC_INIT(0), ATOMIC_INIT(0)
macro_line|#else
DECL|macro|__RWSEM_DEBUG_MINIT
mdefine_line|#define __RWSEM_DEBUG_MINIT(name)&t;/* */
macro_line|#endif
DECL|macro|__RWSEM_INITIALIZER
mdefine_line|#define __RWSEM_INITIALIZER(name) &bslash;&n;{ RWSEM_UNLOCKED_VALUE, SPIN_LOCK_UNLOCKED, &bslash;&n;&t;__WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__RWSEM_DEBUG_INIT __RWSEM_DEBUG_MINIT(name) }
DECL|macro|DECLARE_RWSEM
mdefine_line|#define DECLARE_RWSEM(name) &bslash;&n;&t;struct rw_semaphore name = __RWSEM_INITIALIZER(name)
DECL|function|init_rwsem
r_static
r_inline
r_void
id|init_rwsem
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|sem-&gt;count
op_assign
id|RWSEM_UNLOCKED_VALUE
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|sem-&gt;lock
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
macro_line|#if RWSEM_DEBUG
id|sem-&gt;debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if RWSEM_DEBUG_MAGIC
id|sem-&gt;__magic
op_assign
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;readers
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;writers
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * lock for reading&n; */
DECL|function|__down_read
r_static
r_inline
r_void
id|__down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# beginning down_read&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
id|LOCK_PREFIX
l_string|&quot;  decb      &quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* try to grab the spinlock */
l_string|&quot;  js        3f&bslash;n&quot;
multiline_comment|/* jump if failed */
l_string|&quot;1:&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;  incl      (%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* adds 0x00000001, returns the old value */
macro_line|#ifdef CONFIG_SMP
l_string|&quot;  movb      $1,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* release the spinlock */
macro_line|#endif
l_string|&quot;  js        4f&bslash;n&bslash;t&quot;
multiline_comment|/* jump if we weren&squot;t granted the lock */
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;3:&bslash;n&bslash;t&quot;
multiline_comment|/* spin on the spinlock till we get it */
l_string|&quot;  cmpb      $0,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
l_string|&quot;  rep;nop   &bslash;n&bslash;t&quot;
l_string|&quot;  jle       3b&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       1b&bslash;n&quot;
macro_line|#endif
l_string|&quot;4:&bslash;n&bslash;t&quot;
l_string|&quot;  call      __rwsem_down_read_failed&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       2b&bslash;n&quot;
l_string|&quot;.previous&quot;
l_string|&quot;# ending __down_read&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lock for writing&n; */
DECL|function|__down_write
r_static
r_inline
r_void
id|__down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|RWSEM_ACTIVE_WRITE_BIAS
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# beginning down_write&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
id|LOCK_PREFIX
l_string|&quot;  decb      &quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* try to grab the spinlock */
l_string|&quot;  js        3f&bslash;n&quot;
multiline_comment|/* jump if failed */
l_string|&quot;1:&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;  xchg      %0,(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* retrieve the old value */
l_string|&quot;  add       %0,(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* add 0xffff0001, result in memory */
macro_line|#ifdef CONFIG_SMP
l_string|&quot;  movb      $1,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* release the spinlock */
macro_line|#endif
l_string|&quot;  testl     %0,%0&bslash;n&bslash;t&quot;
multiline_comment|/* was the count 0 before? */
l_string|&quot;  jnz       4f&bslash;n&bslash;t&quot;
multiline_comment|/* jump if we weren&squot;t granted the lock */
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;3:&bslash;n&bslash;t&quot;
multiline_comment|/* spin on the spinlock till we get it */
l_string|&quot;  cmpb      $0,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
l_string|&quot;  rep;nop   &bslash;n&bslash;t&quot;
l_string|&quot;  jle       3b&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       1b&bslash;n&quot;
macro_line|#endif
l_string|&quot;4:&bslash;n&bslash;t&quot;
l_string|&quot;  call     __rwsem_down_write_failed&bslash;n&bslash;t&quot;
l_string|&quot;  jmp      2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;# ending down_write&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * unlock after reading&n; */
DECL|function|__up_read
r_static
r_inline
r_void
id|__up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
op_minus
id|RWSEM_ACTIVE_READ_BIAS
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# beginning __up_read&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
id|LOCK_PREFIX
l_string|&quot;  decb      &quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* try to grab the spinlock */
l_string|&quot;  js        3f&bslash;n&quot;
multiline_comment|/* jump if failed */
l_string|&quot;1:&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;  xchg      %0,(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* retrieve the old value */
l_string|&quot;  addl      %0,(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* subtract 1, result in memory */
macro_line|#ifdef CONFIG_SMP
l_string|&quot;  movb      $1,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* release the spinlock */
macro_line|#endif
l_string|&quot;  js        4f&bslash;n&bslash;t&quot;
multiline_comment|/* jump if the lock is being waited upon */
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;3:&bslash;n&bslash;t&quot;
multiline_comment|/* spin on the spinlock till we get it */
l_string|&quot;  cmpb      $0,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
l_string|&quot;  rep;nop   &bslash;n&bslash;t&quot;
l_string|&quot;  jle       3b&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       1b&bslash;n&quot;
macro_line|#endif
l_string|&quot;4:&bslash;n&bslash;t&quot;
l_string|&quot;  decl      %0&bslash;n&bslash;t&quot;
multiline_comment|/* xchg gave us the old count */
l_string|&quot;  testl     %4,%0&bslash;n&bslash;t&quot;
multiline_comment|/* do nothing if still outstanding active readers */
l_string|&quot;  jnz       2b&bslash;n&bslash;t&quot;
l_string|&quot;  call      __rwsem_wake&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;# ending __up_read&bslash;n&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|RWSEM_ACTIVE_MASK
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * unlock after writing&n; */
DECL|function|__up_write
r_static
r_inline
r_void
id|__up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# beginning __up_write&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
id|LOCK_PREFIX
l_string|&quot;  decb      &quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* try to grab the spinlock */
l_string|&quot;  js        3f&bslash;n&quot;
multiline_comment|/* jump if failed */
l_string|&quot;1:&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;  addl      %3,(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* adds 0x00010001 */
macro_line|#ifdef CONFIG_SMP
l_string|&quot;  movb      $1,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
multiline_comment|/* release the spinlock */
macro_line|#endif
l_string|&quot;  js        4f&bslash;n&bslash;t&quot;
multiline_comment|/* jump if the lock is being waited upon */
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;3:&bslash;n&bslash;t&quot;
multiline_comment|/* spin on the spinlock till we get it */
l_string|&quot;  cmpb      $0,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%%eax)&bslash;n&bslash;t&quot;
l_string|&quot;  rep;nop   &bslash;n&bslash;t&quot;
l_string|&quot;  jle       3b&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       1b&bslash;n&quot;
macro_line|#endif
l_string|&quot;4:&bslash;n&bslash;t&quot;
l_string|&quot;  call     __rwsem_wake&bslash;n&bslash;t&quot;
l_string|&quot;  jmp      2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;# ending __up_write&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|RWSEM_ACTIVE_WRITE_BIAS
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * implement exchange and add functionality&n; */
DECL|function|rwsem_atomic_update
r_static
r_inline
r_int
id|rwsem_atomic_update
c_func
(paren
r_int
id|delta
comma
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|tmp
op_assign
id|delta
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# beginning rwsem_atomic_update&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
id|LOCK_PREFIX
l_string|&quot;  decb      &quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%1)&bslash;n&bslash;t&quot;
multiline_comment|/* try to grab the spinlock */
l_string|&quot;  js        3f&bslash;n&quot;
multiline_comment|/* jump if failed */
l_string|&quot;1:&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;  xchgl     %0,(%1)&bslash;n&bslash;t&quot;
multiline_comment|/* retrieve the old value */
l_string|&quot;  addl      %0,(%1)&bslash;n&bslash;t&quot;
multiline_comment|/* add 0xffff0001, result in memory */
macro_line|#ifdef CONFIG_SMP
l_string|&quot;  movb      $1,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%1)&bslash;n&bslash;t&quot;
multiline_comment|/* release the spinlock */
macro_line|#endif
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;3:&bslash;n&bslash;t&quot;
multiline_comment|/* spin on the spinlock till we get it */
l_string|&quot;  cmpb      $0,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%1)&bslash;n&bslash;t&quot;
l_string|&quot;  rep;nop   &bslash;n&bslash;t&quot;
l_string|&quot;  jle       3b&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       1b&bslash;n&quot;
macro_line|#endif
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;# ending rwsem_atomic_update&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|tmp
op_plus
id|delta
suffix:semicolon
)brace
multiline_comment|/*&n; * implement compare and exchange functionality on the rw-semaphore count LSW&n; */
DECL|function|rwsem_cmpxchgw
r_static
r_inline
id|__u16
id|rwsem_cmpxchgw
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
id|__u16
id|old
comma
id|__u16
r_new
)paren
(brace
id|__u16
id|prev
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# beginning rwsem_cmpxchgw&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
id|LOCK_PREFIX
l_string|&quot;  decb      &quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%3)&bslash;n&bslash;t&quot;
multiline_comment|/* try to grab the spinlock */
l_string|&quot;  js        3f&bslash;n&quot;
multiline_comment|/* jump if failed */
l_string|&quot;1:&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;  cmpw      %w1,(%3)&bslash;n&bslash;t&quot;
l_string|&quot;  jne       4f&bslash;n&bslash;t&quot;
multiline_comment|/* jump if old doesn&squot;t match sem-&gt;count LSW */
l_string|&quot;  movw      %w2,(%3)&bslash;n&bslash;t&quot;
multiline_comment|/* replace sem-&gt;count LSW with the new value */
l_string|&quot;2:&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;  movb      $1,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%3)&bslash;n&bslash;t&quot;
multiline_comment|/* release the spinlock */
macro_line|#endif
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;3:&bslash;n&bslash;t&quot;
multiline_comment|/* spin on the spinlock till we get it */
l_string|&quot;  cmpb      $0,&quot;
id|RWSEM_SPINLOCK_OFFSET_STR
l_string|&quot;(%3)&bslash;n&bslash;t&quot;
l_string|&quot;  rep;nop   &bslash;n&bslash;t&quot;
l_string|&quot;  jle       3b&bslash;n&bslash;t&quot;
l_string|&quot;  jmp       1b&bslash;n&quot;
macro_line|#endif
l_string|&quot;4:&bslash;n&bslash;t&quot;
l_string|&quot;  movw      (%3),%w0&bslash;n&quot;
multiline_comment|/* we&squot;ll want to return the current value */
l_string|&quot;  jmp       2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;# ending rwsem_cmpxchgw&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;r0&quot;
(paren
id|old
)paren
comma
l_string|&quot;r&quot;
(paren
r_new
)paren
comma
l_string|&quot;r&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _I386_RWSEM_SPIN_H */
eof
