macro_line|#ifndef _ASM_M32R_SPINLOCK_H
DECL|macro|_ASM_M32R_SPINLOCK_H
mdefine_line|#define _ASM_M32R_SPINLOCK_H
multiline_comment|/*&n; *  linux/include/asm-m32r/spinlock.h&n; *&n; *  M32R version:&n; *    Copyright (C) 2001, 2002  Hitoshi Yamamoto&n; *    Copyright (C) 2004  Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_DEBUG_SPINLOCK, CONFIG_SMP */
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
r_extern
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
DECL|macro|RW_LOCK_BIAS
mdefine_line|#define RW_LOCK_BIAS&t;&t; 0x01000000
DECL|macro|RW_LOCK_BIAS_STR
mdefine_line|#define RW_LOCK_BIAS_STR&t;&quot;0x01000000&quot;
multiline_comment|/* It seems that people are forgetting to&n; * initialize their spinlocks properly, tsk tsk.&n; * Remember to turn this off in 2.4. -ben&n; */
macro_line|#if defined(CONFIG_DEBUG_SPINLOCK)
DECL|macro|SPINLOCK_DEBUG
mdefine_line|#define SPINLOCK_DEBUG&t;1
macro_line|#else
DECL|macro|SPINLOCK_DEBUG
mdefine_line|#define SPINLOCK_DEBUG&t;0
macro_line|#endif
multiline_comment|/*&n; * Your basic SMP spinlocks, allowing only a single CPU anywhere&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
id|lock
suffix:semicolon
macro_line|#if SPINLOCK_DEBUG
DECL|member|magic
r_int
id|magic
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPINLOCK_MAGIC
mdefine_line|#define SPINLOCK_MAGIC&t;0xdead4ead
macro_line|#if SPINLOCK_DEBUG
DECL|macro|SPINLOCK_MAGIC_INIT
mdefine_line|#define SPINLOCK_MAGIC_INIT&t;, SPINLOCK_MAGIC
macro_line|#else
DECL|macro|SPINLOCK_MAGIC_INIT
mdefine_line|#define SPINLOCK_MAGIC_INIT&t;/* */
macro_line|#endif
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 1 SPINLOCK_MAGIC_INIT }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { *(x) = SPIN_LOCK_UNLOCKED; } while(0)
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;(*(volatile int *)(&amp;(x)-&gt;lock) &lt;= 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while(spin_is_locked(x))
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
multiline_comment|/**&n; * _raw_spin_trylock - Try spin lock and return a result&n; * @lock: Pointer to the lock variable&n; *&n; * _raw_spin_trylock() tries to get the lock and returns a result.&n; * On the m32r, the result value is 1 (= Success) or 0 (= Failure).&n; */
DECL|function|_raw_spin_trylock
r_static
r_inline
r_int
id|_raw_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
id|oldval
suffix:semicolon
r_int
r_int
id|tmp1
comma
id|tmp2
suffix:semicolon
multiline_comment|/*&n;&t; * lock-&gt;lock :  =1 : unlock&n;&t; *            : &lt;=0 : lock&n;&t; * {&n;&t; *   oldval = lock-&gt;lock; &lt;--+ need atomic operation&n;&t; *   lock-&gt;lock = 0;      &lt;--+&n;&t; * }&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;# spin_trylock&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ldi&t;%1, #0;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvfc&t;%2, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r6&quot;
comma
l_string|&quot;%3&quot;
)paren
l_string|&quot;lock&t;%0, @%3;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%1, @%3;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%2, psw;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|oldval
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r6&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
r_return
(paren
id|oldval
OG
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|_raw_spin_lock
r_static
r_inline
r_void
id|_raw_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|tmp0
comma
id|tmp1
suffix:semicolon
macro_line|#if SPINLOCK_DEBUG
id|__label__
id|here
suffix:semicolon
id|here
suffix:colon
r_if
c_cond
(paren
id|lock-&gt;magic
op_ne
id|SPINLOCK_MAGIC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;eip: %p&bslash;n&quot;
comma
op_logical_and
id|here
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * lock-&gt;lock :  =1 : unlock&n;&t; *            : &lt;=0 : lock&n;&t; *&n;&t; * for ( ; ; ) {&n;&t; *   lock-&gt;lock -= 1;  &lt;-- need atomic operation&n;&t; *   if (lock-&gt;lock == 0) break;&n;&t; *   for ( ; lock-&gt;lock &lt;= 0 ; );&n;&t; * }&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;# spin_lock&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvfc&t;%1, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r6&quot;
comma
l_string|&quot;%2&quot;
)paren
l_string|&quot;lock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%1, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bltz&t;%0, 2f;&t;&t;&t;&bslash;n&bslash;t&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;.balign 4 &bslash;n&bslash;t&quot;
)paren
l_string|&quot;.fillinsn&t;&t;&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bgtz&t;%0, 1b;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bra&t;2b;&t;&t;&t;&bslash;n&bslash;t&quot;
id|LOCK_SECTION_END
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r6&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
)brace
DECL|function|_raw_spin_unlock
r_static
r_inline
r_void
id|_raw_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
macro_line|#if SPINLOCK_DEBUG
id|BUG_ON
c_func
(paren
id|lock-&gt;magic
op_ne
id|SPINLOCK_MAGIC
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|spin_is_locked
c_func
(paren
id|lock
)paren
)paren
suffix:semicolon
macro_line|#endif
id|mb
c_func
(paren
)paren
suffix:semicolon
id|lock-&gt;lock
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
id|lock
suffix:semicolon
macro_line|#if SPINLOCK_DEBUG
DECL|member|magic
r_int
id|magic
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RWLOCK_MAGIC
mdefine_line|#define RWLOCK_MAGIC&t;0xdeaf1eed
macro_line|#if SPINLOCK_DEBUG
DECL|macro|RWLOCK_MAGIC_INIT
mdefine_line|#define RWLOCK_MAGIC_INIT&t;, RWLOCK_MAGIC
macro_line|#else
DECL|macro|RWLOCK_MAGIC_INIT
mdefine_line|#define RWLOCK_MAGIC_INIT&t;/* */
macro_line|#endif
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { RW_LOCK_BIAS RWLOCK_MAGIC_INIT }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)&t;do { *(x) = RW_LOCK_UNLOCKED; } while(0)
multiline_comment|/*&n; * On x86, we implement read-write locks as a 32-bit counter&n; * with the high bit (sign) being the &quot;contended&quot; bit.&n; *&n; * The inline assembly is non-obvious. Think about it.&n; *&n; * Changed to use the same technique as rw semaphores.  See&n; * semaphore.h for details.  -ben&n; */
multiline_comment|/* the spinlock helpers are in arch/i386/kernel/semaphore.c */
DECL|function|_raw_read_lock
r_static
r_inline
r_void
id|_raw_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp0
comma
id|tmp1
suffix:semicolon
macro_line|#if SPINLOCK_DEBUG
id|BUG_ON
c_func
(paren
id|rw-&gt;magic
op_ne
id|RWLOCK_MAGIC
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * rw-&gt;lock :  &gt;0 : unlock&n;&t; *          : &lt;=0 : lock&n;&t; *&n;&t; * for ( ; ; ) {&n;&t; *   rw-&gt;lock -= 1;  &lt;-- need atomic operation&n;&t; *   if (rw-&gt;lock &gt;= 0) break;&n;&t; *   rw-&gt;lock += 1;  &lt;-- need atomic operation&n;&t; *   for ( ; rw-&gt;lock &lt;= 0 ; );&n;&t; * }&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;# read_lock&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvfc&t;%1, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r6&quot;
comma
l_string|&quot;%2&quot;
)paren
l_string|&quot;lock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%1, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bltz&t;%0, 2f;&t;&t;&t;&bslash;n&bslash;t&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;.balign 4 &bslash;n&bslash;t&quot;
)paren
l_string|&quot;.fillinsn&t;&t;&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r6&quot;
comma
l_string|&quot;%2&quot;
)paren
l_string|&quot;lock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #1;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%1, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&t;&bslash;n&quot;
l_string|&quot;3:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bgtz&t;%0, 1b;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bra&t;3b;&t;&t;&t;&bslash;n&bslash;t&quot;
id|LOCK_SECTION_END
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r6&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
)brace
DECL|function|_raw_write_lock
r_static
r_inline
r_void
id|_raw_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp0
comma
id|tmp1
comma
id|tmp2
suffix:semicolon
macro_line|#if SPINLOCK_DEBUG
id|BUG_ON
c_func
(paren
id|rw-&gt;magic
op_ne
id|RWLOCK_MAGIC
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * rw-&gt;lock :  =RW_LOCK_BIAS_STR : unlock&n;&t; *          : !=RW_LOCK_BIAS_STR : lock&n;&t; *&n;&t; * for ( ; ; ) {&n;&t; *   rw-&gt;lock -= RW_LOCK_BIAS_STR;  &lt;-- need atomic operation&n;&t; *   if (rw-&gt;lock == 0) break;&n;&t; *   rw-&gt;lock += RW_LOCK_BIAS_STR;  &lt;-- need atomic operation&n;&t; *   for ( ; rw-&gt;lock != RW_LOCK_BIAS_STR ; ) ;&n;&t; * }&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;# write_lock&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;seth&t;%1, #high(&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;);&t;&bslash;n&bslash;t&quot;
l_string|&quot;or3&t;%1, %1, #low(&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;);&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvfc&t;%2, psw;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r7&quot;
comma
l_string|&quot;%3&quot;
)paren
l_string|&quot;lock&t;%0, @%3;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;%0, %1;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%0, @%3;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%2, psw;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bnez&t;%0, 2f;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;.balign 4 &bslash;n&bslash;t&quot;
)paren
l_string|&quot;.fillinsn&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r7&quot;
comma
l_string|&quot;%3&quot;
)paren
l_string|&quot;lock&t;%0, @%3;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%0, %1;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%0, @%3;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%2, psw;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;3:&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%0, @%3;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;beq&t;%0, %1, 1b;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bra&t;3b;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
id|LOCK_SECTION_END
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r7&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
)brace
DECL|function|_raw_read_unlock
r_static
r_inline
r_void
id|_raw_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp0
comma
id|tmp1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# read_unlock&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvfc&t;%1, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r6&quot;
comma
l_string|&quot;%2&quot;
)paren
l_string|&quot;lock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #1;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%0, @%2;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%1, psw;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r6&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
)brace
DECL|function|_raw_write_unlock
r_static
r_inline
r_void
id|_raw_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp0
comma
id|tmp1
comma
id|tmp2
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# write_unlock&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;seth&t;%1, #high(&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;);&t;&bslash;n&bslash;t&quot;
l_string|&quot;or3&t;%1, %1, #low(&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;);&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvfc&t;%2, psw;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r7&quot;
comma
l_string|&quot;%3&quot;
)paren
l_string|&quot;lock&t;%0, @%3;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%0, %1;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%0, @%3;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%2, psw;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r7&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
)brace
DECL|macro|_raw_read_trylock
mdefine_line|#define _raw_read_trylock(lock) generic_raw_read_trylock(lock)
DECL|function|_raw_write_trylock
r_static
r_inline
r_int
id|_raw_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|atomic_t
op_star
id|count
op_assign
(paren
id|atomic_t
op_star
)paren
id|lock
suffix:semicolon
r_if
c_cond
(paren
id|atomic_sub_and_test
c_func
(paren
id|RW_LOCK_BIAS
comma
id|count
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|atomic_add
c_func
(paren
id|RW_LOCK_BIAS
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* _ASM_M32R_SPINLOCK_H */
eof
