multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SPINLOCK_H
DECL|macro|_ASM_SPINLOCK_H
mdefine_line|#define _ASM_SPINLOCK_H
macro_line|#include &lt;asm/war.h&gt;
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
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions.  They have a cost.&n; */
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
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|R10000_LLSC_WAR
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_spin_lock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bnez&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; li&t;%1, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; nop&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|lock-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
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
r_else
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_spin_lock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bnez&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; li&t;%1, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|lock-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_spin_unlock&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$0, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&bslash;treorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
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
r_int
id|temp
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|R10000_LLSC_WAR
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_spin_trylock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%0, %3&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;ori&t;%2, %0, 1&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%2, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%2, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; nop&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;andi&t;%2, %0, 1&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lock-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|res
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
r_else
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_spin_trylock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%0, %3&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;ori&t;%2, %0, 1&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%2, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%2, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; andi&t;%2, %0, 1&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lock-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|res
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
r_return
id|res
op_eq
l_int|0
suffix:semicolon
)brace
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
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)  do { *(x) = RW_LOCK_UNLOCKED; } while(0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(x) ((x)-&gt;lock)
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
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|R10000_LLSC_WAR
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_read_lock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bltz&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; addu&t;%1, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; nop&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_read_lock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bltz&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; addu&t;%1, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Note the use of sub, not subu which will make the kernel die with an&n;   overflow exception if we ever try to unlock an rwlock that is already&n;   unlocked or is being held by a writer.  */
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
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|R10000_LLSC_WAR
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;# _raw_read_unlock&t;&bslash;n&quot;
l_string|&quot;&t;sub&t;%1, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_read_unlock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sub&t;%1, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|R10000_LLSC_WAR
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_write_lock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bnez&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; lui&t;%1, 0x8000&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; nop&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_write_lock&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bnez&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; lui&t;%1, 0x8000&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; nop&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;sync&t;&t;&t;# _raw_write_unlock&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$0, %0&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_write_trylock
r_static
r_inline
r_int
id|_raw_write_trylock
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
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|R10000_LLSC_WAR
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_write_trylock&t;&bslash;n&quot;
l_string|&quot;&t;li&t;%2, 0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %3&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bnez&t;%1, 2f&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; lui&t;%1, 0x8000&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; nop&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;li&t;%2, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noreorder&t;# _raw_write_trylock&t;&bslash;n&quot;
l_string|&quot;&t;li&t;%2, 0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%1, %3&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;bnez&t;%1, 2f&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;lui&t;%1, 0x8000&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%1, %0&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t; sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;li&t;%2, 1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;reorder&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SPINLOCK_H */
eof
