multiline_comment|/*&n; *  Fast Userspace Mutexes (which I call &quot;Futexes!&quot;).&n; *  (C) Rusty Russell, IBM 2002&n; *&n; *  Thanks to Ben LaHaise for yelling &quot;hashed waitqueues&quot; loudly&n; *  enough at me, Linus for the original (flawed) idea, Matthew&n; *  Kirkwood for proof-of-concept implementation.&n; *&n; *  &quot;The futexes are also cursed.&quot;&n; *  &quot;But they come in a choice of three flavours!&quot;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hash.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/futex.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* Simple &quot;sleep if unchanged&quot; interface. */
multiline_comment|/* FIXME: This may be way too small. --RR */
DECL|macro|FUTEX_HASHBITS
mdefine_line|#define FUTEX_HASHBITS 6
multiline_comment|/* We use this instead of a normal wait_queue_t, so we can wake only&n;   the relevent ones (hashed queues may be shared) */
DECL|struct|futex_q
r_struct
id|futex_q
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|waiters
id|wait_queue_head_t
id|waiters
suffix:semicolon
multiline_comment|/* Page struct and offset within it. */
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The key for the hash is the address + index + offset within page */
DECL|variable|futex_queues
r_static
r_struct
id|list_head
id|futex_queues
(braket
l_int|1
op_lshift
id|FUTEX_HASHBITS
)braket
suffix:semicolon
DECL|variable|futex_lock
r_static
id|spinlock_t
id|futex_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|hash_futex
r_static
r_inline
r_struct
id|list_head
op_star
id|hash_futex
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
id|h
suffix:semicolon
multiline_comment|/* struct page is shared, so we can hash on its address */
id|h
op_assign
(paren
r_int
r_int
)paren
id|page
op_plus
id|offset
suffix:semicolon
r_return
op_amp
id|futex_queues
(braket
id|hash_long
c_func
(paren
id|h
comma
id|FUTEX_HASHBITS
)paren
)braket
suffix:semicolon
)brace
DECL|function|tell_waiter
r_static
r_inline
r_void
id|tell_waiter
c_func
(paren
r_struct
id|futex_q
op_star
id|q
)paren
(brace
id|wake_up_all
c_func
(paren
op_amp
id|q-&gt;waiters
)paren
suffix:semicolon
)brace
DECL|function|futex_wake
r_static
r_int
id|futex_wake
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
id|num
)paren
(brace
r_struct
id|list_head
op_star
id|i
comma
op_star
id|next
suffix:semicolon
r_int
id|num_woken
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|futex_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|i
comma
id|next
comma
id|head
)paren
(brace
r_struct
id|futex_q
op_star
id|this
op_assign
id|list_entry
c_func
(paren
id|i
comma
r_struct
id|futex_q
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|this-&gt;page
op_eq
id|page
op_logical_and
id|this-&gt;offset
op_eq
id|offset
)paren
(brace
id|list_del_init
c_func
(paren
id|i
)paren
suffix:semicolon
id|tell_waiter
c_func
(paren
id|this
)paren
suffix:semicolon
id|num_woken
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|num_woken
op_ge
id|num
)paren
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|futex_lock
)paren
suffix:semicolon
r_return
id|num_woken
suffix:semicolon
)brace
multiline_comment|/* Add at end to avoid starvation */
DECL|function|queue_me
r_static
r_inline
r_void
id|queue_me
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
id|wait_queue_t
op_star
id|wait
comma
r_struct
id|futex_q
op_star
id|q
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|q-&gt;waiters
comma
id|wait
)paren
suffix:semicolon
id|q-&gt;page
op_assign
id|page
suffix:semicolon
id|q-&gt;offset
op_assign
id|offset
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|futex_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|q-&gt;list
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|futex_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Return 1 if we were still queued (ie. 0 means we were woken) */
DECL|function|unqueue_me
r_static
r_inline
r_int
id|unqueue_me
c_func
(paren
r_struct
id|futex_q
op_star
id|q
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|futex_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;list
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|q-&gt;list
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|futex_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Get kernel address of the user page and pin it. */
DECL|function|pin_page
r_static
r_struct
id|page
op_star
id|pin_page
c_func
(paren
r_int
r_int
id|page_start
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|err
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|err
op_assign
id|get_user_pages
c_func
(paren
id|current
comma
id|current-&gt;mm
comma
id|page_start
comma
l_int|1
multiline_comment|/* one page */
comma
l_int|1
multiline_comment|/* writable */
comma
l_int|0
multiline_comment|/* don&squot;t force */
comma
op_amp
id|page
comma
l_int|NULL
multiline_comment|/* don&squot;t return vmas */
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|futex_wait
r_static
r_int
id|futex_wait
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|val
comma
r_int
op_star
id|uaddr
comma
r_int
r_int
id|time
)paren
(brace
r_int
id|curval
suffix:semicolon
r_struct
id|futex_q
id|q
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|queue_me
c_func
(paren
id|head
comma
op_amp
id|wait
comma
op_amp
id|q
comma
id|page
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* Page is pinned, but may no longer be in this address space. */
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|curval
comma
id|uaddr
)paren
op_ne
l_int|0
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|curval
op_ne
id|val
)paren
(brace
id|ret
op_assign
op_minus
id|EWOULDBLOCK
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|time
op_assign
id|schedule_timeout
c_func
(paren
id|time
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
multiline_comment|/* Were we woken up anyway? */
r_if
c_cond
(paren
op_logical_neg
id|unqueue_me
c_func
(paren
op_amp
id|q
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_futex
id|asmlinkage
r_int
id|sys_futex
c_func
(paren
r_void
op_star
id|uaddr
comma
r_int
id|op
comma
r_int
id|val
comma
r_struct
id|timespec
op_star
id|utime
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|pos_in_page
suffix:semicolon
r_struct
id|list_head
op_star
id|head
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|time
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
r_if
c_cond
(paren
id|utime
)paren
(brace
r_struct
id|timespec
id|t
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|t
comma
id|utime
comma
r_sizeof
(paren
id|t
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|time
op_assign
id|timespec_to_jiffies
c_func
(paren
op_amp
id|t
)paren
op_plus
l_int|1
suffix:semicolon
)brace
id|pos_in_page
op_assign
(paren
(paren
r_int
r_int
)paren
id|uaddr
)paren
op_mod
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* Must be &quot;naturally&quot; aligned, and not on page boundary. */
r_if
c_cond
(paren
(paren
id|pos_in_page
op_mod
id|__alignof__
c_func
(paren
r_int
)paren
)paren
op_ne
l_int|0
op_logical_or
id|pos_in_page
op_plus
r_sizeof
(paren
r_int
)paren
OG
id|PAGE_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Simpler if it doesn&squot;t vanish underneath us. */
id|page
op_assign
id|pin_page
c_func
(paren
(paren
r_int
r_int
)paren
id|uaddr
op_minus
id|pos_in_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|page
)paren
suffix:semicolon
id|head
op_assign
id|hash_futex
c_func
(paren
id|page
comma
id|pos_in_page
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|op
)paren
(brace
r_case
id|FUTEX_WAIT
suffix:colon
id|ret
op_assign
id|futex_wait
c_func
(paren
id|head
comma
id|page
comma
id|pos_in_page
comma
id|val
comma
id|uaddr
comma
id|time
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FUTEX_WAKE
suffix:colon
id|ret
op_assign
id|futex_wake
c_func
(paren
id|head
comma
id|page
comma
id|pos_in_page
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|futex_queues
)paren
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|futex_queues
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init
id|__initcall
c_func
(paren
id|init
)paren
suffix:semicolon
eof
