macro_line|#ifndef _ALPHA_SPINLOCK_H
DECL|macro|_ALPHA_SPINLOCK_H
mdefine_line|#define _ALPHA_SPINLOCK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/current.h&gt;
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
multiline_comment|/*__attribute__((aligned(32))) */
suffix:semicolon
macro_line|#if CONFIG_DEBUG_SPINLOCK
DECL|member|on_cpu
r_int
id|on_cpu
suffix:semicolon
DECL|member|line_no
r_int
id|line_no
suffix:semicolon
DECL|member|previous
r_void
op_star
id|previous
suffix:semicolon
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|base_file
r_const
r_char
op_star
id|base_file
suffix:semicolon
macro_line|#endif
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
macro_line|#if CONFIG_DEBUG_SPINLOCK
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) {0, -1, 0, 0, 0, 0}
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((x)-&gt;lock = 0, (x)-&gt;on_cpu = -1, (x)-&gt;previous = 0, (x)-&gt;task = 0)
macro_line|#else
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;(spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;((x)-&gt;lock = 0)
macro_line|#endif
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;({ do { barrier(); } while ((x)-&gt;lock); })
macro_line|#if CONFIG_DEBUG_SPINLOCK
r_extern
r_void
id|_raw_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|debug_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|debug_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(LOCK) debug_spin_lock(LOCK, __BASE_FILE__, __LINE__)
DECL|macro|_raw_spin_trylock
mdefine_line|#define _raw_spin_trylock(LOCK) debug_spin_trylock(LOCK, __BASE_FILE__, __LINE__)
DECL|macro|spin_lock_own
mdefine_line|#define spin_lock_own(LOCK, LOCATION)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!((LOCK)-&gt;lock &amp;&amp; (LOCK)-&gt;on_cpu == smp_processor_id()))&t;&bslash;&n;&t;&t;printk(&quot;%s: called on %d from %p but lock %s on %d&bslash;n&quot;,&t;&bslash;&n;&t;&t;       LOCATION, smp_processor_id(),&t;&t;&t;&bslash;&n;&t;&t;       __builtin_return_address(0),&t;&t;&t;&bslash;&n;&t;&t;       (LOCK)-&gt;lock ? &quot;taken&quot; : &quot;freed&quot;, (LOCK)-&gt;on_cpu); &bslash;&n;} while (0)
macro_line|#else
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
id|mb
c_func
(paren
)paren
suffix:semicolon
id|lock-&gt;lock
op_assign
l_int|0
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
id|tmp
suffix:semicolon
multiline_comment|/* Use sub-sections to put the actual loop at the end&n;&t;   of this object file&squot;s text section so as to perfect&n;&t;   branch prediction.  */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;blbs&t;%0,2f&bslash;n&quot;
l_string|&quot;&t;or&t;%0,1,%0&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;beq&t;%0,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;ldl&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;blbs&t;%0,2b&bslash;n&quot;
l_string|&quot;&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
r_return
op_logical_neg
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|lock-&gt;lock
)paren
suffix:semicolon
)brace
DECL|macro|spin_lock_own
mdefine_line|#define spin_lock_own(LOCK, LOCATION)&t;((void)0)
macro_line|#endif /* CONFIG_DEBUG_SPINLOCK */
multiline_comment|/***********************************************************/
r_typedef
r_struct
(brace
DECL|member|write_lock
DECL|member|read_counter
r_volatile
r_int
id|write_lock
suffix:colon
l_int|1
comma
id|read_counter
suffix:colon
l_int|31
suffix:semicolon
DECL|typedef|rwlock_t
)brace
multiline_comment|/*__attribute__((aligned(32)))*/
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)&t;do { *(x) = RW_LOCK_UNLOCKED; } while(0)
macro_line|#if CONFIG_DEBUG_RWLOCK
r_extern
r_void
id|_raw_write_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_raw_read_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
macro_line|#else
DECL|function|_raw_write_lock
r_static
r_inline
r_void
id|_raw_write_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
r_int
id|regx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;bne&t;%1,6f&bslash;n&quot;
l_string|&quot;&t;or&t;$31,1,%1&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,6f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;6:&t;ldl&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;bne&t;%1,6b&bslash;n&quot;
l_string|&quot;&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|regx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_read_lock
r_static
r_inline
r_void
id|_raw_read_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
r_int
id|regx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;blbs&t;%1,6f&bslash;n&quot;
l_string|&quot;&t;subl&t;%1,2,%1&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,6f&bslash;n&quot;
l_string|&quot;4:&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;6:&t;ldl&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;blbs&t;%1,6b&bslash;n&quot;
l_string|&quot;&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|regx
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DEBUG_RWLOCK */
DECL|function|_raw_write_unlock
r_static
r_inline
r_void
id|_raw_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
op_assign
l_int|0
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
id|lock
)paren
(brace
r_int
id|regx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;1:&t;ldl_l&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;addl&t;%1,2,%1&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,6f&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;6:&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|regx
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ALPHA_SPINLOCK_H */
eof
