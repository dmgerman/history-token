multiline_comment|/*&n; *  linux/fs/pipe.c&n; *&n; *  Copyright (C) 1991, 1992, 1999  Linus Torvalds&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/pipe_fs_i.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
multiline_comment|/*&n; * We use a start+len construction, which provides full use of the &n; * allocated memory.&n; * -- Florian Coosmann (FGC)&n; * &n; * Reads with count = 0 should always return 0.&n; * -- Julian Bradfield 1999-06-07.&n; *&n; * FIFOs and Pipes now generate SIGIO for both readers and writers.&n; * -- Jeremy Elson &lt;jelson@circlemud.org&gt; 2001-08-16&n; *&n; * pipe_read &amp; write cleanup&n; * -- Manfred Spraul &lt;manfred@colorfullife.com&gt; 2002-05-09&n; */
multiline_comment|/* Drop the inode semaphore and wait for a pipe event, atomically */
DECL|function|pipe_wait
r_void
id|pipe_wait
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|finish_wait
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
op_amp
id|wait
)paren
suffix:semicolon
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pipe_read
id|pipe_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|do_wakeup
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
multiline_comment|/* pread is not allowed on pipes. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ppos
op_ne
op_amp
id|filp-&gt;f_pos
)paren
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
multiline_comment|/* Null read succeeds. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|count
op_eq
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|do_wakeup
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|size
op_assign
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
r_char
op_star
id|pipebuf
op_assign
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_plus
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
id|ssize_t
id|chars
op_assign
id|PIPE_MAX_RCHUNK
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|count
)paren
id|chars
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|size
)paren
id|chars
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|pipebuf
comma
id|chars
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_add_assign
id|chars
suffix:semicolon
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_add_assign
id|chars
suffix:semicolon
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_and_assign
(paren
id|PIPE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
op_sub_assign
id|chars
suffix:semicolon
id|count
op_sub_assign
id|chars
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
id|do_wakeup
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_break
suffix:semicolon
multiline_comment|/* common path: read succeeded */
r_if
c_cond
(paren
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
)paren
multiline_comment|/* test for cyclic buffers */
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
multiline_comment|/* syscall merging: Usually we must not sleep&n;&t;&t;&t; * if O_NONBLOCK is set, or if we got some data.&n;&t;&t;&t; * But if a writer sleeps in kernel space, then&n;&t;&t;&t; * we can wait for that data without violating POSIX.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_wakeup
)paren
(brace
id|wake_up_interruptible_sync
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
id|PIPE_FASYNC_WRITERS
c_func
(paren
op_star
id|inode
)paren
comma
id|SIGIO
comma
id|POLL_OUT
)paren
suffix:semicolon
)brace
id|pipe_wait
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
multiline_comment|/* Signal writers asynchronously that there is more room.  */
r_if
c_cond
(paren
id|do_wakeup
)paren
(brace
id|wake_up_interruptible
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
id|PIPE_FASYNC_WRITERS
c_func
(paren
op_star
id|inode
)paren
comma
id|SIGIO
comma
id|POLL_OUT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
id|update_atime
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pipe_write
id|pipe_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_int
id|min
suffix:semicolon
r_int
id|do_wakeup
suffix:semicolon
multiline_comment|/* pwrite is not allowed on pipes. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ppos
op_ne
op_amp
id|filp-&gt;f_pos
)paren
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
multiline_comment|/* Null write succeeds. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|count
op_eq
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|do_wakeup
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|min
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|min
OG
id|PIPE_BUF
)paren
id|min
op_assign
l_int|1
suffix:semicolon
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|free
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
id|send_sig
c_func
(paren
id|SIGPIPE
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|EPIPE
suffix:semicolon
r_break
suffix:semicolon
)brace
id|free
op_assign
id|PIPE_FREE
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free
op_ge
id|min
)paren
(brace
multiline_comment|/* transfer data */
id|ssize_t
id|chars
op_assign
id|PIPE_MAX_WCHUNK
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
r_char
op_star
id|pipebuf
op_assign
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_plus
id|PIPE_END
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* Always wakeup, even if the copy fails. Otherwise&n;&t;&t;&t; * we lock up (O_NONBLOCK-)readers that sleep due to&n;&t;&t;&t; * syscall merging.&n;&t;&t;&t; */
id|do_wakeup
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|count
)paren
id|chars
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|free
)paren
id|chars
op_assign
id|free
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|pipebuf
comma
id|buf
comma
id|chars
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_add_assign
id|chars
suffix:semicolon
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
op_add_assign
id|chars
suffix:semicolon
id|count
op_sub_assign
id|chars
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|PIPE_FREE
c_func
(paren
op_star
id|inode
)paren
op_logical_and
id|ret
)paren
(brace
multiline_comment|/* handle cyclic data buffers */
id|min
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
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
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_wakeup
)paren
(brace
id|wake_up_interruptible_sync
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
id|PIPE_FASYNC_READERS
c_func
(paren
op_star
id|inode
)paren
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|do_wakeup
op_assign
l_int|0
suffix:semicolon
)brace
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|pipe_wait
c_func
(paren
id|inode
)paren
suffix:semicolon
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
)brace
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_wakeup
)paren
(brace
id|wake_up_interruptible
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
id|PIPE_FASYNC_READERS
c_func
(paren
op_star
id|inode
)paren
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|bad_pipe_r
id|bad_pipe_r
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|bad_pipe_w
id|bad_pipe_w
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_ioctl
id|pipe_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|pino
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FIONREAD
suffix:colon
r_return
id|put_user
c_func
(paren
id|PIPE_LEN
c_func
(paren
op_star
id|pino
)paren
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/* No kernel lock held - fine */
r_static
r_int
r_int
DECL|function|pipe_poll
id|pipe_poll
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|poll_wait
c_func
(paren
id|filp
comma
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
id|wait
)paren
suffix:semicolon
multiline_comment|/* Reading only -- no need for acquiring the semaphore.  */
id|mask
op_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_if
c_cond
(paren
id|PIPE_EMPTY
c_func
(paren
op_star
id|inode
)paren
)paren
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_logical_and
id|filp-&gt;f_version
op_ne
id|PIPE_WCOUNTER
c_func
(paren
op_star
id|inode
)paren
)paren
id|mask
op_or_assign
id|POLLHUP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
id|mask
op_or_assign
id|POLLERR
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
multiline_comment|/* FIXME: most Unices do not set POLLERR for fifos */
DECL|macro|fifo_poll
mdefine_line|#define fifo_poll pipe_poll
r_static
r_int
DECL|function|pipe_release
id|pipe_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|decr
comma
r_int
id|decw
)paren
(brace
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_sub_assign
id|decr
suffix:semicolon
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_sub_assign
id|decw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_logical_and
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
r_struct
id|pipe_inode_info
op_star
id|info
op_assign
id|inode-&gt;i_pipe
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
l_int|NULL
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|info-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
r_else
(brace
id|wake_up_interruptible
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
id|PIPE_FASYNC_READERS
c_func
(paren
op_star
id|inode
)paren
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
id|PIPE_FASYNC_WRITERS
c_func
(paren
op_star
id|inode
)paren
comma
id|SIGIO
comma
id|POLL_OUT
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_read_fasync
id|pipe_read_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
id|PIPE_FASYNC_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_write_fasync
id|pipe_write_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
id|PIPE_FASYNC_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_rdwr_fasync
id|pipe_rdwr_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
id|PIPE_FASYNC_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
id|PIPE_FASYNC_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_read_release
id|pipe_read_release
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
id|filp
)paren
(brace
id|pipe_read_fasync
c_func
(paren
op_minus
l_int|1
comma
id|filp
comma
l_int|0
)paren
suffix:semicolon
r_return
id|pipe_release
c_func
(paren
id|inode
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_write_release
id|pipe_write_release
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
id|filp
)paren
(brace
id|pipe_write_fasync
c_func
(paren
op_minus
l_int|1
comma
id|filp
comma
l_int|0
)paren
suffix:semicolon
r_return
id|pipe_release
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_rdwr_release
id|pipe_rdwr_release
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
id|filp
)paren
(brace
r_int
id|decr
comma
id|decw
suffix:semicolon
id|pipe_rdwr_fasync
c_func
(paren
op_minus
l_int|1
comma
id|filp
comma
l_int|0
)paren
suffix:semicolon
id|decr
op_assign
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_ne
l_int|0
suffix:semicolon
id|decw
op_assign
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
op_ne
l_int|0
suffix:semicolon
r_return
id|pipe_release
c_func
(paren
id|inode
comma
id|decr
comma
id|decw
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_read_open
id|pipe_read_open
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
id|filp
)paren
(brace
multiline_comment|/* We could have perhaps used atomic_t, but this and friends&n;&t;   below are the only places.  So it doesn&squot;t seem worthwhile.  */
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_write_open
id|pipe_write_open
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
id|filp
)paren
(brace
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_rdwr_open
id|pipe_rdwr_open
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
id|filp
)paren
(brace
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_READ
)paren
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The file_operations structs are not static because they&n; * are also used in linux/fs/fifo.c to do operations on FIFOs.&n; */
DECL|variable|read_fifo_fops
r_struct
id|file_operations
id|read_fifo_fops
op_assign
(brace
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|pipe_read
comma
dot
id|write
op_assign
id|bad_pipe_w
comma
dot
id|poll
op_assign
id|fifo_poll
comma
dot
id|ioctl
op_assign
id|pipe_ioctl
comma
dot
id|open
op_assign
id|pipe_read_open
comma
dot
id|release
op_assign
id|pipe_read_release
comma
dot
id|fasync
op_assign
id|pipe_read_fasync
comma
)brace
suffix:semicolon
DECL|variable|write_fifo_fops
r_struct
id|file_operations
id|write_fifo_fops
op_assign
(brace
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|bad_pipe_r
comma
dot
id|write
op_assign
id|pipe_write
comma
dot
id|poll
op_assign
id|fifo_poll
comma
dot
id|ioctl
op_assign
id|pipe_ioctl
comma
dot
id|open
op_assign
id|pipe_write_open
comma
dot
id|release
op_assign
id|pipe_write_release
comma
dot
id|fasync
op_assign
id|pipe_write_fasync
comma
)brace
suffix:semicolon
DECL|variable|rdwr_fifo_fops
r_struct
id|file_operations
id|rdwr_fifo_fops
op_assign
(brace
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|pipe_read
comma
dot
id|write
op_assign
id|pipe_write
comma
dot
id|poll
op_assign
id|fifo_poll
comma
dot
id|ioctl
op_assign
id|pipe_ioctl
comma
dot
id|open
op_assign
id|pipe_rdwr_open
comma
dot
id|release
op_assign
id|pipe_rdwr_release
comma
dot
id|fasync
op_assign
id|pipe_rdwr_fasync
comma
)brace
suffix:semicolon
DECL|variable|read_pipe_fops
r_struct
id|file_operations
id|read_pipe_fops
op_assign
(brace
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|pipe_read
comma
dot
id|write
op_assign
id|bad_pipe_w
comma
dot
id|poll
op_assign
id|pipe_poll
comma
dot
id|ioctl
op_assign
id|pipe_ioctl
comma
dot
id|open
op_assign
id|pipe_read_open
comma
dot
id|release
op_assign
id|pipe_read_release
comma
dot
id|fasync
op_assign
id|pipe_read_fasync
comma
)brace
suffix:semicolon
DECL|variable|write_pipe_fops
r_struct
id|file_operations
id|write_pipe_fops
op_assign
(brace
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|bad_pipe_r
comma
dot
id|write
op_assign
id|pipe_write
comma
dot
id|poll
op_assign
id|pipe_poll
comma
dot
id|ioctl
op_assign
id|pipe_ioctl
comma
dot
id|open
op_assign
id|pipe_write_open
comma
dot
id|release
op_assign
id|pipe_write_release
comma
dot
id|fasync
op_assign
id|pipe_write_fasync
comma
)brace
suffix:semicolon
DECL|variable|rdwr_pipe_fops
r_struct
id|file_operations
id|rdwr_pipe_fops
op_assign
(brace
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|pipe_read
comma
dot
id|write
op_assign
id|pipe_write
comma
dot
id|poll
op_assign
id|pipe_poll
comma
dot
id|ioctl
op_assign
id|pipe_ioctl
comma
dot
id|open
op_assign
id|pipe_rdwr_open
comma
dot
id|release
op_assign
id|pipe_rdwr_release
comma
dot
id|fasync
op_assign
id|pipe_rdwr_fasync
comma
)brace
suffix:semicolon
DECL|function|pipe_new
r_struct
id|inode
op_star
id|pipe_new
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
id|page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|NULL
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pipe_inode_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_pipe
)paren
r_goto
id|fail_page
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_assign
(paren
r_char
op_star
)paren
id|page
suffix:semicolon
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_RCOUNTER
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WCOUNTER
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|1
suffix:semicolon
op_star
id|PIPE_FASYNC_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
op_star
id|PIPE_FASYNC_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|NULL
suffix:semicolon
r_return
id|inode
suffix:semicolon
id|fail_page
suffix:colon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|pipe_mnt
r_static
r_struct
id|vfsmount
op_star
id|pipe_mnt
suffix:semicolon
DECL|function|pipefs_delete_dentry
r_static
r_int
id|pipefs_delete_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pipefs_dentry_operations
r_static
r_struct
id|dentry_operations
id|pipefs_dentry_operations
op_assign
(brace
dot
id|d_delete
op_assign
id|pipefs_delete_dentry
comma
)brace
suffix:semicolon
DECL|function|get_pipe_inode
r_static
r_struct
id|inode
op_star
id|get_pipe_inode
c_func
(paren
r_void
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|pipe_mnt-&gt;mnt_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|fail_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pipe_new
c_func
(paren
id|inode
)paren
)paren
(brace
r_goto
id|fail_iput
suffix:semicolon
)brace
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|rdwr_pipe_fops
suffix:semicolon
multiline_comment|/*&n;&t; * Mark the inode dirty from the very beginning,&n;&t; * that way it will never be moved to the dirty&n;&t; * list because &quot;mark_inode_dirty()&quot; will think&n;&t; * that it already _is_ on the dirty list.&n;&t; */
id|inode-&gt;i_state
op_assign
id|I_DIRTY
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFIFO
op_or
id|S_IRUSR
op_or
id|S_IWUSR
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
r_return
id|inode
suffix:semicolon
id|fail_iput
suffix:colon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|fail_inode
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|do_pipe
r_int
id|do_pipe
c_func
(paren
r_int
op_star
id|fd
)paren
(brace
r_struct
id|qstr
id|this
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file
op_star
id|f1
comma
op_star
id|f2
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|error
op_assign
op_minus
id|ENFILE
suffix:semicolon
id|f1
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f1
)paren
r_goto
id|no_files
suffix:semicolon
id|f2
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f2
)paren
r_goto
id|close_f1
suffix:semicolon
id|inode
op_assign
id|get_pipe_inode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|close_f12
suffix:semicolon
id|error
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|close_f12_inode
suffix:semicolon
id|i
op_assign
id|error
suffix:semicolon
id|error
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|close_f12_inode_i
suffix:semicolon
id|j
op_assign
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;[%lu]&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|this.name
op_assign
id|name
suffix:semicolon
id|this.len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|this.hash
op_assign
id|inode-&gt;i_ino
suffix:semicolon
multiline_comment|/* will go */
id|dentry
op_assign
id|d_alloc
c_func
(paren
id|pipe_mnt-&gt;mnt_sb-&gt;s_root
comma
op_amp
id|this
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_goto
id|close_f12_inode_i_j
suffix:semicolon
id|dentry-&gt;d_op
op_assign
op_amp
id|pipefs_dentry_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|f1-&gt;f_vfsmnt
op_assign
id|f2-&gt;f_vfsmnt
op_assign
id|mntget
c_func
(paren
id|mntget
c_func
(paren
id|pipe_mnt
)paren
)paren
suffix:semicolon
id|f1-&gt;f_dentry
op_assign
id|f2-&gt;f_dentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* read file */
id|f1-&gt;f_pos
op_assign
id|f2-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
id|f1-&gt;f_flags
op_assign
id|O_RDONLY
suffix:semicolon
id|f1-&gt;f_op
op_assign
op_amp
id|read_pipe_fops
suffix:semicolon
id|f1-&gt;f_mode
op_assign
l_int|1
suffix:semicolon
id|f1-&gt;f_version
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* write file */
id|f2-&gt;f_flags
op_assign
id|O_WRONLY
suffix:semicolon
id|f2-&gt;f_op
op_assign
op_amp
id|write_pipe_fops
suffix:semicolon
id|f2-&gt;f_mode
op_assign
l_int|2
suffix:semicolon
id|f2-&gt;f_version
op_assign
l_int|0
suffix:semicolon
id|fd_install
c_func
(paren
id|i
comma
id|f1
)paren
suffix:semicolon
id|fd_install
c_func
(paren
id|j
comma
id|f2
)paren
suffix:semicolon
id|fd
(braket
l_int|0
)braket
op_assign
id|i
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
id|j
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|close_f12_inode_i_j
suffix:colon
id|put_unused_fd
c_func
(paren
id|j
)paren
suffix:semicolon
id|close_f12_inode_i
suffix:colon
id|put_unused_fd
c_func
(paren
id|i
)paren
suffix:semicolon
id|close_f12_inode
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|inode-&gt;i_pipe
)paren
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
l_int|NULL
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|close_f12
suffix:colon
id|put_filp
c_func
(paren
id|f2
)paren
suffix:semicolon
id|close_f1
suffix:colon
id|put_filp
c_func
(paren
id|f1
)paren
suffix:semicolon
id|no_files
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * pipefs should _never_ be mounted by userland - too much of security hassle,&n; * no real gain from having the whole whorehouse mounted. So we don&squot;t need&n; * any operations on the root directory. However, we need a non-trivial&n; * d_name - pipe: will go nicely and kill the special-casing in procfs.&n; */
DECL|function|pipefs_get_sb
r_static
r_struct
id|super_block
op_star
id|pipefs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_pseudo
c_func
(paren
id|fs_type
comma
l_string|&quot;pipe:&quot;
comma
l_int|NULL
comma
id|PIPEFS_MAGIC
)paren
suffix:semicolon
)brace
DECL|variable|pipe_fs_type
r_static
r_struct
id|file_system_type
id|pipe_fs_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pipefs&quot;
comma
dot
id|get_sb
op_assign
id|pipefs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_anon_super
comma
)brace
suffix:semicolon
DECL|function|init_pipe_fs
r_static
r_int
id|__init
id|init_pipe_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|pipe_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|pipe_mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|pipe_fs_type
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|pipe_mnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|pipe_mnt
)paren
)paren
id|unregister_filesystem
c_func
(paren
op_amp
id|pipe_fs_type
)paren
suffix:semicolon
r_else
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_pipe_fs
r_static
r_void
id|__exit
id|exit_pipe_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|pipe_fs_type
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|pipe_mnt
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_pipe_fs
)paren
id|module_exit
c_func
(paren
id|exit_pipe_fs
)paren
eof
