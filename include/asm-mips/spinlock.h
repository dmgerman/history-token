multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SPINLOCK_H
DECL|macro|_ASM_SPINLOCK_H
mdefine_line|#define _ASM_SPINLOCK_H
multiline_comment|/*&n; * Your basic SMP spinlocks, allowing only a single CPU anywhere&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { (x)-&gt;lock = 0; } while(0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while ((x)-&gt;lock)
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions.  They have a cost.&n; */
DECL|function|spin_lock
r_static
r_inline
r_void
id|spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# spin_lock&bslash;n&quot;
l_string|&quot;1:&bslash;tll&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; li&bslash;t%1, 1&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; sync&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=o&quot;
(paren
id|lock-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|spin_unlock
r_static
r_inline
r_void
id|spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# spin_unlock&bslash;n&bslash;t&quot;
l_string|&quot;sync&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t$0, %0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=o&quot;
(paren
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock) (!test_and_set_bit(0,(lock)))
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts but no interrupt&n; * writers. For those circumstances we can &quot;mix&quot; irq-safe locks - any writer&n; * needs to get a irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0 }
DECL|function|read_lock
r_static
r_inline
r_void
id|read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# read_lock&bslash;n&quot;
l_string|&quot;1:&bslash;tll&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;bltz&bslash;t%1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; addu&bslash;t%1, 1&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; sync&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=o&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Note the use of sub, not subu which will make the kernel die with an&n;   overflow exception if we ever try to unlock an rwlock that is already&n;   unlocked or is being held by a writer.  */
DECL|function|read_unlock
r_static
r_inline
r_void
id|read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# read_unlock&bslash;n&quot;
l_string|&quot;1:&bslash;tll&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;sub&bslash;t%1, 1&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%1, 1b&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=o&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|write_lock
r_static
r_inline
r_void
id|write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# write_lock&bslash;n&quot;
l_string|&quot;1:&bslash;tll&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; lui&bslash;t%1, 0x8000&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; sync&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=o&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|write_unlock
r_static
r_inline
r_void
id|write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# write_unlock&bslash;n&bslash;t&quot;
l_string|&quot;sync&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t$0, %0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=o&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SPINLOCK_H */
eof
