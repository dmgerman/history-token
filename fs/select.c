multiline_comment|/*&n; * This file contains the procedures for the handling of select and poll&n; *&n; * Created for Linux based loosely upon Mathius Lattner&squot;s minix&n; * patches by Peter MacDonald. Heavily edited by Linus.&n; *&n; *  4 February 1994&n; *     COFF/ELF binary emulation. If the process has the STICKY_TIMEOUTS&n; *     flag set in its personality we do *not* modify the given timeout&n; *     parameter to reflect time remaining.&n; *&n; *  24 January 2000&n; *     Changed sys_poll()/do_poll() to use PAGE_SIZE chunk-based allocation &n; *     of fds to overcome nfds &lt; 16390 descriptors limit (Tigran Aivazian).&n; */
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/personality.h&gt; /* for STICKY_TIMEOUTS */
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(x,y) (((x)+(y)-1)/(y))
DECL|macro|DEFAULT_POLLMASK
mdefine_line|#define DEFAULT_POLLMASK (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM)
DECL|struct|poll_table_entry
r_struct
id|poll_table_entry
(brace
DECL|member|filp
r_struct
id|file
op_star
id|filp
suffix:semicolon
DECL|member|wait
id|wait_queue_t
id|wait
suffix:semicolon
DECL|member|wait_address
id|wait_queue_head_t
op_star
id|wait_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|poll_table_page
r_struct
id|poll_table_page
(brace
DECL|member|next
r_struct
id|poll_table_page
op_star
id|next
suffix:semicolon
DECL|member|entry
r_struct
id|poll_table_entry
op_star
id|entry
suffix:semicolon
DECL|member|entries
r_struct
id|poll_table_entry
id|entries
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|POLL_TABLE_FULL
mdefine_line|#define POLL_TABLE_FULL(table) &bslash;&n;&t;((unsigned long)((table)-&gt;entry+1) &gt; PAGE_SIZE + (unsigned long)(table))
multiline_comment|/*&n; * Ok, Peter made a complicated, but straightforward multiple_wait() function.&n; * I have rewritten this, taking some shortcuts: This code may not be easy to&n; * follow, but it should be free of race-conditions, and it&squot;s practical. If you&n; * understand what I&squot;m doing here, then you understand how the linux&n; * sleep/wakeup mechanism works.&n; *&n; * Two very simple procedures, poll_wait() and poll_freewait() make all the&n; * work.  poll_wait() is an inline-function defined in &lt;linux/poll.h&gt;,&n; * as all select/poll functions have to call it to add an entry to the&n; * poll table.&n; */
r_void
id|__pollwait
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|wait_queue_head_t
op_star
id|wait_address
comma
id|poll_table
op_star
id|p
)paren
suffix:semicolon
DECL|function|poll_initwait
r_void
id|poll_initwait
c_func
(paren
r_struct
id|poll_wqueues
op_star
id|pwq
)paren
(brace
id|init_poll_funcptr
c_func
(paren
op_amp
id|pwq-&gt;pt
comma
id|__pollwait
)paren
suffix:semicolon
id|pwq-&gt;error
op_assign
l_int|0
suffix:semicolon
id|pwq-&gt;table
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|poll_initwait
id|EXPORT_SYMBOL
c_func
(paren
id|poll_initwait
)paren
suffix:semicolon
DECL|function|poll_freewait
r_void
id|poll_freewait
c_func
(paren
r_struct
id|poll_wqueues
op_star
id|pwq
)paren
(brace
r_struct
id|poll_table_page
op_star
id|p
op_assign
id|pwq-&gt;table
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_struct
id|poll_table_entry
op_star
id|entry
suffix:semicolon
r_struct
id|poll_table_page
op_star
id|old
suffix:semicolon
id|entry
op_assign
id|p-&gt;entry
suffix:semicolon
r_do
(brace
id|entry
op_decrement
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|entry-&gt;wait_address
comma
op_amp
id|entry-&gt;wait
)paren
suffix:semicolon
id|fput
c_func
(paren
id|entry-&gt;filp
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|entry
OG
id|p-&gt;entries
)paren
suffix:semicolon
id|old
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|old
)paren
suffix:semicolon
)brace
)brace
DECL|variable|poll_freewait
id|EXPORT_SYMBOL
c_func
(paren
id|poll_freewait
)paren
suffix:semicolon
DECL|function|__pollwait
r_void
id|__pollwait
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|wait_queue_head_t
op_star
id|wait_address
comma
id|poll_table
op_star
id|_p
)paren
(brace
r_struct
id|poll_wqueues
op_star
id|p
op_assign
id|container_of
c_func
(paren
id|_p
comma
r_struct
id|poll_wqueues
comma
id|pt
)paren
suffix:semicolon
r_struct
id|poll_table_page
op_star
id|table
op_assign
id|p-&gt;table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table
op_logical_or
id|POLL_TABLE_FULL
c_func
(paren
id|table
)paren
)paren
(brace
r_struct
id|poll_table_page
op_star
id|new_table
suffix:semicolon
id|new_table
op_assign
(paren
r_struct
id|poll_table_page
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_table
)paren
(brace
id|p-&gt;error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|new_table-&gt;entry
op_assign
id|new_table-&gt;entries
suffix:semicolon
id|new_table-&gt;next
op_assign
id|table
suffix:semicolon
id|p-&gt;table
op_assign
id|new_table
suffix:semicolon
id|table
op_assign
id|new_table
suffix:semicolon
)brace
multiline_comment|/* Add a new entry */
(brace
r_struct
id|poll_table_entry
op_star
id|entry
op_assign
id|table-&gt;entry
suffix:semicolon
id|table-&gt;entry
op_assign
id|entry
op_plus
l_int|1
suffix:semicolon
id|get_file
c_func
(paren
id|filp
)paren
suffix:semicolon
id|entry-&gt;filp
op_assign
id|filp
suffix:semicolon
id|entry-&gt;wait_address
op_assign
id|wait_address
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|entry-&gt;wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|wait_address
comma
op_amp
id|entry-&gt;wait
)paren
suffix:semicolon
)brace
)brace
DECL|macro|FDS_IN
mdefine_line|#define FDS_IN(fds, n)&t;&t;(fds-&gt;in + n)
DECL|macro|FDS_OUT
mdefine_line|#define FDS_OUT(fds, n)&t;&t;(fds-&gt;out + n)
DECL|macro|FDS_EX
mdefine_line|#define FDS_EX(fds, n)&t;&t;(fds-&gt;ex + n)
DECL|macro|BITS
mdefine_line|#define BITS(fds, n)&t;(*FDS_IN(fds, n)|*FDS_OUT(fds, n)|*FDS_EX(fds, n))
DECL|function|max_select_fd
r_static
r_int
id|max_select_fd
c_func
(paren
r_int
r_int
id|n
comma
id|fd_set_bits
op_star
id|fds
)paren
(brace
r_int
r_int
op_star
id|open_fds
suffix:semicolon
r_int
r_int
id|set
suffix:semicolon
r_int
id|max
suffix:semicolon
multiline_comment|/* handle last in-complete long-word first */
id|set
op_assign
op_complement
(paren
op_complement
l_int|0UL
op_lshift
(paren
id|n
op_amp
(paren
id|__NFDBITS
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|n
op_div_assign
id|__NFDBITS
suffix:semicolon
id|open_fds
op_assign
id|current-&gt;files-&gt;open_fds-&gt;fds_bits
op_plus
id|n
suffix:semicolon
id|max
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
id|set
op_and_assign
id|BITS
c_func
(paren
id|fds
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|set
op_amp
op_complement
op_star
id|open_fds
)paren
)paren
r_goto
id|get_max
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|n
)paren
(brace
id|open_fds
op_decrement
suffix:semicolon
id|n
op_decrement
suffix:semicolon
id|set
op_assign
id|BITS
c_func
(paren
id|fds
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|set
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|set
op_amp
op_complement
op_star
id|open_fds
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|max
)paren
r_continue
suffix:semicolon
id|get_max
suffix:colon
r_do
(brace
id|max
op_increment
suffix:semicolon
id|set
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|set
)paren
suffix:semicolon
id|max
op_add_assign
id|n
op_star
id|__NFDBITS
suffix:semicolon
)brace
r_return
id|max
suffix:semicolon
)brace
DECL|macro|BIT
mdefine_line|#define BIT(i)&t;&t;(1UL &lt;&lt; ((i)&amp;(__NFDBITS-1)))
DECL|macro|MEM
mdefine_line|#define MEM(i,m)&t;((m)+(unsigned)(i)/__NFDBITS)
DECL|macro|ISSET
mdefine_line|#define ISSET(i,m)&t;(((i)&amp;*(m)) != 0)
DECL|macro|SET
mdefine_line|#define SET(i,m)&t;(*(m) |= (i))
DECL|macro|POLLIN_SET
mdefine_line|#define POLLIN_SET (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
DECL|macro|POLLOUT_SET
mdefine_line|#define POLLOUT_SET (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
DECL|macro|POLLEX_SET
mdefine_line|#define POLLEX_SET (POLLPRI)
DECL|function|do_select
r_int
id|do_select
c_func
(paren
r_int
id|n
comma
id|fd_set_bits
op_star
id|fds
comma
r_int
op_star
id|timeout
)paren
(brace
r_struct
id|poll_wqueues
id|table
suffix:semicolon
id|poll_table
op_star
id|wait
suffix:semicolon
r_int
id|retval
comma
id|i
suffix:semicolon
r_int
id|__timeout
op_assign
op_star
id|timeout
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|current-&gt;files-&gt;file_lock
)paren
suffix:semicolon
id|retval
op_assign
id|max_select_fd
c_func
(paren
id|n
comma
id|fds
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|current-&gt;files-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|n
op_assign
id|retval
suffix:semicolon
id|poll_initwait
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
id|wait
op_assign
op_amp
id|table.pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|__timeout
)paren
id|wait
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
op_star
id|rinp
comma
op_star
id|routp
comma
op_star
id|rexp
comma
op_star
id|inp
comma
op_star
id|outp
comma
op_star
id|exp
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|inp
op_assign
id|fds-&gt;in
suffix:semicolon
id|outp
op_assign
id|fds-&gt;out
suffix:semicolon
id|exp
op_assign
id|fds-&gt;ex
suffix:semicolon
id|rinp
op_assign
id|fds-&gt;res_in
suffix:semicolon
id|routp
op_assign
id|fds-&gt;res_out
suffix:semicolon
id|rexp
op_assign
id|fds-&gt;res_ex
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
id|n
suffix:semicolon
op_increment
id|rinp
comma
op_increment
id|routp
comma
op_increment
id|rexp
)paren
(brace
r_int
r_int
id|in
comma
id|out
comma
id|ex
comma
id|all_bits
comma
id|bit
op_assign
l_int|1
comma
id|mask
comma
id|j
suffix:semicolon
r_int
r_int
id|res_in
op_assign
l_int|0
comma
id|res_out
op_assign
l_int|0
comma
id|res_ex
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_operations
op_star
id|f_op
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
id|in
op_assign
op_star
id|inp
op_increment
suffix:semicolon
id|out
op_assign
op_star
id|outp
op_increment
suffix:semicolon
id|ex
op_assign
op_star
id|exp
op_increment
suffix:semicolon
id|all_bits
op_assign
id|in
op_or
id|out
op_or
id|ex
suffix:semicolon
r_if
c_cond
(paren
id|all_bits
op_eq
l_int|0
)paren
(brace
id|i
op_add_assign
id|__NFDBITS
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|__NFDBITS
suffix:semicolon
op_increment
id|j
comma
op_increment
id|i
comma
id|bit
op_lshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|i
op_ge
id|n
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bit
op_amp
id|all_bits
)paren
)paren
r_continue
suffix:semicolon
id|file
op_assign
id|fget
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|f_op
op_assign
id|file-&gt;f_op
suffix:semicolon
id|mask
op_assign
id|DEFAULT_POLLMASK
suffix:semicolon
r_if
c_cond
(paren
id|f_op
op_logical_and
id|f_op-&gt;poll
)paren
id|mask
op_assign
(paren
op_star
id|f_op-&gt;poll
)paren
(paren
id|file
comma
id|retval
ques
c_cond
l_int|NULL
suffix:colon
id|wait
)paren
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mask
op_amp
id|POLLIN_SET
)paren
op_logical_and
(paren
id|in
op_amp
id|bit
)paren
)paren
(brace
id|res_in
op_or_assign
id|bit
suffix:semicolon
id|retval
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|mask
op_amp
id|POLLOUT_SET
)paren
op_logical_and
(paren
id|out
op_amp
id|bit
)paren
)paren
(brace
id|res_out
op_or_assign
id|bit
suffix:semicolon
id|retval
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|mask
op_amp
id|POLLEX_SET
)paren
op_logical_and
(paren
id|ex
op_amp
id|bit
)paren
)paren
(brace
id|res_ex
op_or_assign
id|bit
suffix:semicolon
id|retval
op_increment
suffix:semicolon
)brace
)brace
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res_in
)paren
op_star
id|rinp
op_assign
id|res_in
suffix:semicolon
r_if
c_cond
(paren
id|res_out
)paren
op_star
id|routp
op_assign
id|res_out
suffix:semicolon
r_if
c_cond
(paren
id|res_ex
)paren
op_star
id|rexp
op_assign
id|res_ex
suffix:semicolon
)brace
id|wait
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_logical_or
op_logical_neg
id|__timeout
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|table.error
)paren
(brace
id|retval
op_assign
id|table.error
suffix:semicolon
r_break
suffix:semicolon
)brace
id|__timeout
op_assign
id|schedule_timeout
c_func
(paren
id|__timeout
)paren
suffix:semicolon
)brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|poll_freewait
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Up-to-date the caller timeout.&n;&t; */
op_star
id|timeout
op_assign
id|__timeout
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|select_bits_alloc
r_static
r_void
op_star
id|select_bits_alloc
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|kmalloc
c_func
(paren
l_int|6
op_star
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|select_bits_free
r_static
r_void
id|select_bits_free
c_func
(paren
r_void
op_star
id|bits
comma
r_int
id|size
)paren
(brace
id|kfree
c_func
(paren
id|bits
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We can actually return ERESTARTSYS instead of EINTR, but I&squot;d&n; * like to be certain this leads to no problems. So I return&n; * EINTR just for safety.&n; *&n; * Update: ERESTARTSYS breaks at least the xview clock binary, so&n; * I&squot;m trying ERESTARTNOHAND which restart only when you want to.&n; */
DECL|macro|MAX_SELECT_SECONDS
mdefine_line|#define MAX_SELECT_SECONDS &bslash;&n;&t;((unsigned long) (MAX_SCHEDULE_TIMEOUT / HZ)-1)
id|asmlinkage
r_int
DECL|function|sys_select
id|sys_select
c_func
(paren
r_int
id|n
comma
id|fd_set
id|__user
op_star
id|inp
comma
id|fd_set
id|__user
op_star
id|outp
comma
id|fd_set
id|__user
op_star
id|exp
comma
r_struct
id|timeval
id|__user
op_star
id|tvp
)paren
(brace
id|fd_set_bits
id|fds
suffix:semicolon
r_char
op_star
id|bits
suffix:semicolon
r_int
id|timeout
suffix:semicolon
r_int
id|ret
comma
id|size
comma
id|max_fdset
suffix:semicolon
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
r_if
c_cond
(paren
id|tvp
)paren
(brace
id|time_t
id|sec
comma
id|usec
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|tvp
comma
r_sizeof
(paren
op_star
id|tvp
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|sec
comma
op_amp
id|tvp-&gt;tv_sec
)paren
op_logical_or
id|__get_user
c_func
(paren
id|usec
comma
op_amp
id|tvp-&gt;tv_usec
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out_nofds
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sec
OL
l_int|0
op_logical_or
id|usec
OL
l_int|0
)paren
r_goto
id|out_nofds
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|sec
OL
id|MAX_SELECT_SECONDS
)paren
(brace
id|timeout
op_assign
id|ROUND_UP
c_func
(paren
id|usec
comma
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|timeout
op_add_assign
id|sec
op_star
(paren
r_int
r_int
)paren
id|HZ
suffix:semicolon
)brace
)brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
r_goto
id|out_nofds
suffix:semicolon
multiline_comment|/* max_fdset can increase, so grab it once to avoid race */
id|max_fdset
op_assign
id|current-&gt;files-&gt;max_fdset
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|max_fdset
)paren
id|n
op_assign
id|max_fdset
suffix:semicolon
multiline_comment|/*&n;&t; * We need 6 bitmaps (in/out/ex for both incoming and outgoing),&n;&t; * since we used fdset we need to allocate memory in units of&n;&t; * long-words. &n;&t; */
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|size
op_assign
id|FDS_BYTES
c_func
(paren
id|n
)paren
suffix:semicolon
id|bits
op_assign
id|select_bits_alloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bits
)paren
r_goto
id|out_nofds
suffix:semicolon
id|fds.in
op_assign
(paren
r_int
r_int
op_star
)paren
id|bits
suffix:semicolon
id|fds.out
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|bits
op_plus
id|size
)paren
suffix:semicolon
id|fds.ex
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|bits
op_plus
l_int|2
op_star
id|size
)paren
suffix:semicolon
id|fds.res_in
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|bits
op_plus
l_int|3
op_star
id|size
)paren
suffix:semicolon
id|fds.res_out
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|bits
op_plus
l_int|4
op_star
id|size
)paren
suffix:semicolon
id|fds.res_ex
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|bits
op_plus
l_int|5
op_star
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|get_fd_set
c_func
(paren
id|n
comma
id|inp
comma
id|fds.in
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|get_fd_set
c_func
(paren
id|n
comma
id|outp
comma
id|fds.out
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|get_fd_set
c_func
(paren
id|n
comma
id|exp
comma
id|fds.ex
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|zero_fd_set
c_func
(paren
id|n
comma
id|fds.res_in
)paren
suffix:semicolon
id|zero_fd_set
c_func
(paren
id|n
comma
id|fds.res_out
)paren
suffix:semicolon
id|zero_fd_set
c_func
(paren
id|n
comma
id|fds.res_ex
)paren
suffix:semicolon
id|ret
op_assign
id|do_select
c_func
(paren
id|n
comma
op_amp
id|fds
comma
op_amp
id|timeout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tvp
op_logical_and
op_logical_neg
(paren
id|current-&gt;personality
op_amp
id|STICKY_TIMEOUTS
)paren
)paren
(brace
id|time_t
id|sec
op_assign
l_int|0
comma
id|usec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|timeout
)paren
(brace
id|sec
op_assign
id|timeout
op_div
id|HZ
suffix:semicolon
id|usec
op_assign
id|timeout
op_mod
id|HZ
suffix:semicolon
id|usec
op_mul_assign
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
)brace
id|put_user
c_func
(paren
id|sec
comma
op_amp
id|tvp-&gt;tv_sec
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|usec
comma
op_amp
id|tvp-&gt;tv_usec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
op_minus
id|ERESTARTNOHAND
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|set_fd_set
c_func
(paren
id|n
comma
id|inp
comma
id|fds.res_in
)paren
op_logical_or
id|set_fd_set
c_func
(paren
id|n
comma
id|outp
comma
id|fds.res_out
)paren
op_logical_or
id|set_fd_set
c_func
(paren
id|n
comma
id|exp
comma
id|fds.res_ex
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|out
suffix:colon
id|select_bits_free
c_func
(paren
id|bits
comma
id|size
)paren
suffix:semicolon
id|out_nofds
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|struct|poll_list
r_struct
id|poll_list
(brace
DECL|member|next
r_struct
id|poll_list
op_star
id|next
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|entries
r_struct
id|pollfd
id|entries
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|POLLFD_PER_PAGE
mdefine_line|#define POLLFD_PER_PAGE  ((PAGE_SIZE-sizeof(struct poll_list)) / sizeof(struct pollfd))
DECL|function|do_pollfd
r_static
r_void
id|do_pollfd
c_func
(paren
r_int
r_int
id|num
comma
r_struct
id|pollfd
op_star
id|fdpage
comma
id|poll_table
op_star
op_star
id|pwait
comma
r_int
op_star
id|count
)paren
(brace
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|fd
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_struct
id|pollfd
op_star
id|fdp
suffix:semicolon
id|mask
op_assign
l_int|0
suffix:semicolon
id|fdp
op_assign
id|fdpage
op_plus
id|i
suffix:semicolon
id|fd
op_assign
id|fdp-&gt;fd
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
id|mask
op_assign
id|POLLNVAL
suffix:semicolon
r_if
c_cond
(paren
id|file
op_ne
l_int|NULL
)paren
(brace
id|mask
op_assign
id|DEFAULT_POLLMASK
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;poll
)paren
id|mask
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|poll
c_func
(paren
id|file
comma
op_star
id|pwait
)paren
suffix:semicolon
id|mask
op_and_assign
id|fdp-&gt;events
op_or
id|POLLERR
op_or
id|POLLHUP
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mask
)paren
(brace
op_star
id|pwait
op_assign
l_int|NULL
suffix:semicolon
(paren
op_star
id|count
)paren
op_increment
suffix:semicolon
)brace
)brace
id|fdp-&gt;revents
op_assign
id|mask
suffix:semicolon
)brace
)brace
DECL|function|do_poll
r_static
r_int
id|do_poll
c_func
(paren
r_int
r_int
id|nfds
comma
r_struct
id|poll_list
op_star
id|list
comma
r_struct
id|poll_wqueues
op_star
id|wait
comma
r_int
id|timeout
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|poll_table
op_star
id|pt
op_assign
op_amp
id|wait-&gt;pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
id|pt
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|poll_list
op_star
id|walk
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|walk
op_assign
id|list
suffix:semicolon
r_while
c_loop
(paren
id|walk
op_ne
l_int|NULL
)paren
(brace
id|do_pollfd
c_func
(paren
id|walk-&gt;len
comma
id|walk-&gt;entries
comma
op_amp
id|pt
comma
op_amp
id|count
)paren
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
suffix:semicolon
)brace
id|pt
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|count
op_logical_or
op_logical_neg
id|timeout
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
id|count
op_assign
id|wait-&gt;error
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
r_break
suffix:semicolon
id|timeout
op_assign
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
)brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|sys_poll
id|asmlinkage
r_int
id|sys_poll
c_func
(paren
r_struct
id|pollfd
id|__user
op_star
id|ufds
comma
r_int
r_int
id|nfds
comma
r_int
id|timeout
)paren
(brace
r_struct
id|poll_wqueues
id|table
suffix:semicolon
r_int
id|fdcount
comma
id|err
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_struct
id|poll_list
op_star
id|head
suffix:semicolon
r_struct
id|poll_list
op_star
id|walk
suffix:semicolon
multiline_comment|/* Do a sanity check on nfds ... */
r_if
c_cond
(paren
id|nfds
OG
id|current-&gt;files-&gt;max_fdset
op_logical_and
id|nfds
OG
id|OPEN_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|timeout
)paren
(brace
multiline_comment|/* Careful about overflow in the intermediate values */
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|timeout
OL
id|MAX_SCHEDULE_TIMEOUT
op_div
id|HZ
)paren
id|timeout
op_assign
(paren
r_int
r_int
)paren
(paren
id|timeout
op_star
id|HZ
op_plus
l_int|999
)paren
op_div
l_int|1000
op_plus
l_int|1
suffix:semicolon
r_else
multiline_comment|/* Negative or overflow */
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
)brace
id|poll_initwait
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
id|head
op_assign
l_int|NULL
suffix:semicolon
id|walk
op_assign
l_int|NULL
suffix:semicolon
id|i
op_assign
id|nfds
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ne
l_int|0
)paren
(brace
r_struct
id|poll_list
op_star
id|pp
suffix:semicolon
id|pp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|poll_list
)paren
op_plus
r_sizeof
(paren
r_struct
id|pollfd
)paren
op_star
(paren
id|i
OG
id|POLLFD_PER_PAGE
ques
c_cond
id|POLLFD_PER_PAGE
suffix:colon
id|i
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
op_eq
l_int|NULL
)paren
(brace
r_goto
id|out_fds
suffix:semicolon
)brace
id|pp-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|pp-&gt;len
op_assign
(paren
id|i
OG
id|POLLFD_PER_PAGE
ques
c_cond
id|POLLFD_PER_PAGE
suffix:colon
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
id|head
op_assign
id|pp
suffix:semicolon
r_else
id|walk-&gt;next
op_assign
id|pp
suffix:semicolon
id|walk
op_assign
id|pp
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|pp-&gt;entries
comma
id|ufds
op_plus
id|nfds
op_minus
id|i
comma
r_sizeof
(paren
r_struct
id|pollfd
)paren
op_star
id|pp-&gt;len
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out_fds
suffix:semicolon
)brace
id|i
op_sub_assign
id|pp-&gt;len
suffix:semicolon
)brace
id|fdcount
op_assign
id|do_poll
c_func
(paren
id|nfds
comma
id|head
comma
op_amp
id|table
comma
id|timeout
)paren
suffix:semicolon
multiline_comment|/* OK, now copy the revents fields back to user space. */
id|walk
op_assign
id|head
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|walk
op_ne
l_int|NULL
)paren
(brace
r_struct
id|pollfd
op_star
id|fds
op_assign
id|walk-&gt;entries
suffix:semicolon
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|walk-&gt;len
suffix:semicolon
id|j
op_increment
comma
id|ufds
op_increment
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|fds
(braket
id|j
)braket
dot
id|revents
comma
op_amp
id|ufds-&gt;revents
)paren
)paren
(brace
r_goto
id|out_fds
suffix:semicolon
)brace
)brace
id|walk
op_assign
id|walk-&gt;next
suffix:semicolon
)brace
id|err
op_assign
id|fdcount
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fdcount
op_logical_and
id|signal_pending
c_func
(paren
id|current
)paren
)paren
id|err
op_assign
op_minus
id|EINTR
suffix:semicolon
id|out_fds
suffix:colon
id|walk
op_assign
id|head
suffix:semicolon
r_while
c_loop
(paren
id|walk
op_ne
l_int|NULL
)paren
(brace
r_struct
id|poll_list
op_star
id|pp
op_assign
id|walk-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|walk
)paren
suffix:semicolon
id|walk
op_assign
id|pp
suffix:semicolon
)brace
id|poll_freewait
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
