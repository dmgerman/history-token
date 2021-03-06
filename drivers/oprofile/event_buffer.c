multiline_comment|/**&n; * @file event_buffer.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; *&n; * This is the global event buffer that the user-space&n; * daemon reads from. The event buffer is an untyped array&n; * of unsigned longs. Entries are prefixed by the&n; * escape value ESCAPE_CODE followed by an identifying code.&n; */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/dcookies.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;oprof.h&quot;
macro_line|#include &quot;event_buffer.h&quot;
macro_line|#include &quot;oprofile_stats.h&quot;
DECL|variable|buffer_sem
id|DECLARE_MUTEX
c_func
(paren
id|buffer_sem
)paren
suffix:semicolon
DECL|variable|buffer_opened
r_static
r_int
r_int
id|buffer_opened
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|buffer_wait
)paren
suffix:semicolon
DECL|variable|event_buffer
r_static
r_int
r_int
op_star
id|event_buffer
suffix:semicolon
DECL|variable|buffer_size
r_static
r_int
r_int
id|buffer_size
suffix:semicolon
DECL|variable|buffer_watershed
r_static
r_int
r_int
id|buffer_watershed
suffix:semicolon
DECL|variable|buffer_pos
r_static
r_int
id|buffer_pos
suffix:semicolon
multiline_comment|/* atomic_t because wait_event checks it outside of buffer_sem */
DECL|variable|buffer_ready
r_static
id|atomic_t
id|buffer_ready
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Add an entry to the event buffer. When we&n; * get near to the end we wake up the process&n; * sleeping on the read() of the file.&n; */
DECL|function|add_event_entry
r_void
id|add_event_entry
c_func
(paren
r_int
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
id|buffer_pos
op_eq
id|buffer_size
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|oprofile_stats.event_lost_overflow
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|event_buffer
(braket
id|buffer_pos
)braket
op_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|buffer_pos
op_eq
id|buffer_size
op_minus
id|buffer_watershed
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|buffer_ready
comma
l_int|1
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|buffer_wait
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Wake up the waiting process if any. This happens&n; * on &quot;echo 0 &gt;/dev/oprofile/enable&quot; so the daemon&n; * processes the data remaining in the event buffer.&n; */
DECL|function|wake_up_buffer_waiter
r_void
id|wake_up_buffer_waiter
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|buffer_ready
comma
l_int|1
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|buffer_wait
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
)brace
DECL|function|alloc_event_buffer
r_int
id|alloc_event_buffer
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
id|buffer_size
op_assign
id|fs_buffer_size
suffix:semicolon
id|buffer_watershed
op_assign
id|fs_buffer_watershed
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_watershed
op_ge
id|buffer_size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|event_buffer
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
id|buffer_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event_buffer
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|free_event_buffer
r_void
id|free_event_buffer
c_func
(paren
r_void
)paren
(brace
id|vfree
c_func
(paren
id|event_buffer
)paren
suffix:semicolon
)brace
DECL|function|event_buffer_open
r_static
r_int
id|event_buffer_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|buffer_opened
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Register as a user of dcookies&n;&t; * to ensure they persist for the lifetime of&n;&t; * the open event file&n;&t; */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|file-&gt;private_data
op_assign
id|dcookie_register
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;private_data
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|oprofile_setup
c_func
(paren
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* NB: the actual start happens from userspace&n;&t; * echo 1 &gt;/dev/oprofile/enable&n;&t; */
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|dcookie_unregister
c_func
(paren
id|file-&gt;private_data
)paren
suffix:semicolon
id|out
suffix:colon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|buffer_opened
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|event_buffer_release
r_static
r_int
id|event_buffer_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|oprofile_stop
c_func
(paren
)paren
suffix:semicolon
id|oprofile_shutdown
c_func
(paren
)paren
suffix:semicolon
id|dcookie_unregister
c_func
(paren
id|file-&gt;private_data
)paren
suffix:semicolon
id|buffer_pos
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|buffer_ready
comma
l_int|0
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|buffer_opened
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|event_buffer_read
r_static
id|ssize_t
id|event_buffer_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
r_const
id|max
op_assign
id|buffer_size
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* handling partial reads is more trouble than it&squot;s worth */
r_if
c_cond
(paren
id|count
op_ne
id|max
op_logical_or
op_star
id|offset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|wait_event_interruptible
c_func
(paren
id|buffer_wait
comma
id|atomic_read
c_func
(paren
op_amp
id|buffer_ready
)paren
)paren
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
r_return
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* can&squot;t currently happen */
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|buffer_ready
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|down
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|buffer_ready
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|count
op_assign
id|buffer_pos
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|event_buffer
comma
id|count
)paren
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
id|count
suffix:semicolon
id|buffer_pos
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|event_buffer_fops
r_struct
id|file_operations
id|event_buffer_fops
op_assign
(brace
dot
id|open
op_assign
id|event_buffer_open
comma
dot
id|release
op_assign
id|event_buffer_release
comma
dot
id|read
op_assign
id|event_buffer_read
comma
)brace
suffix:semicolon
eof
