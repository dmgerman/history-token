multiline_comment|/*&n; *  linux/drivers/char/pty.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Added support for a Unix98-style ptmx device.&n; *    -- C. Scott Ananian &lt;cananian@alumni.princeton.edu&gt;, 14-Jan-1998&n; *  Added TTY_DO_WRITE_WAKEUP to enable n_tty to send POLL_OUT to&n; *      waiting writers -- Sapan Bhatia &lt;sapan@corewars.org&gt;&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;&t;/* For EXPORT_SYMBOL */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/devpts_fs.h&gt;
multiline_comment|/* These are global because they are accessed in tty_io.c */
macro_line|#ifdef CONFIG_UNIX98_PTYS
DECL|variable|ptm_driver
r_struct
id|tty_driver
op_star
id|ptm_driver
suffix:semicolon
DECL|variable|pts_driver
r_static
r_struct
id|tty_driver
op_star
id|pts_driver
suffix:semicolon
macro_line|#endif
DECL|function|pty_close
r_static
r_void
id|pty_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tty
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;subtype
op_eq
id|PTY_TYPE_MASTER
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;count
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;master pty_close: count = %d!!&bslash;n&quot;
comma
id|tty-&gt;count
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|tty-&gt;count
OG
l_int|2
)paren
r_return
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;read_wait
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;write_wait
)paren
suffix:semicolon
id|tty-&gt;packet
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;link
)paren
r_return
suffix:semicolon
id|tty-&gt;link-&gt;packet
op_assign
l_int|0
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_OTHER_CLOSED
comma
op_amp
id|tty-&gt;link-&gt;flags
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;read_wait
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;write_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;subtype
op_eq
id|PTY_TYPE_MASTER
)paren
(brace
id|set_bit
c_func
(paren
id|TTY_OTHER_CLOSED
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_UNIX98_PTYS
r_if
c_cond
(paren
id|tty-&gt;driver
op_eq
id|ptm_driver
)paren
id|devpts_pty_kill
c_func
(paren
id|tty-&gt;index
)paren
suffix:semicolon
macro_line|#endif
id|tty_vhangup
c_func
(paren
id|tty-&gt;link
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The unthrottle routine is called by the line discipline to signal&n; * that it can receive more characters.  For PTY&squot;s, the TTY_THROTTLED&n; * flag is always set, to force the line discipline to always call the&n; * unthrottle routine when there are fewer than TTY_THRESHOLD_UNTHROTTLE &n; * characters in the queue.  This is necessary since each time this&n; * happens, we need to wake up any sleeping processes that could be&n; * (1) trying to send data to the pty, or (2) waiting in wait_until_sent()&n; * for the pty buffer to be drained.&n; */
DECL|function|pty_unthrottle
r_static
r_void
id|pty_unthrottle
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|o_tty
op_assign
id|tty-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o_tty
)paren
r_return
suffix:semicolon
id|tty_wakeup
c_func
(paren
id|o_tty
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_THROTTLED
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * WSH 05/24/97: modified to &n; *   (1) use space in tty-&gt;flip instead of a shared temp buffer&n; *&t; The flip buffers aren&squot;t being used for a pty, so there&squot;s lots&n; *&t; of space available.  The buffer is protected by a per-pty&n; *&t; semaphore that should almost never come under contention.&n; *   (2) avoid redundant copying for cases where count &gt;&gt; receive_room&n; * N.B. Calls from user space may now return an error code instead of&n; * a count.&n; *&n; * FIXME: Our pty_write method is called with our ldisc lock held but&n; * not our partners. We can&squot;t just take the other one blindly without&n; * risking deadlocks.  There is also the small matter of TTY_DONT_FLIP&n; */
DECL|function|pty_write
r_static
r_int
id|pty_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_int
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
op_logical_or
id|tty-&gt;stopped
)paren
r_return
l_int|0
suffix:semicolon
id|c
op_assign
id|to-&gt;ldisc
dot
id|receive_room
c_func
(paren
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
id|count
)paren
id|c
op_assign
id|count
suffix:semicolon
id|to-&gt;ldisc
dot
id|receive_buf
c_func
(paren
id|to
comma
id|buf
comma
l_int|NULL
comma
id|c
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|function|pty_write_room
r_static
r_int
id|pty_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
op_logical_or
id|tty-&gt;stopped
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|to-&gt;ldisc
dot
id|receive_room
c_func
(paren
id|to
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;WSH 05/24/97:  Modified for asymmetric MASTER/SLAVE behavior&n; *&t;The chars_in_buffer() value is used by the ldisc select() function &n; *&t;to hold off writing when chars_in_buffer &gt; WAKEUP_CHARS (== 256).&n; *&t;The pty driver chars_in_buffer() Master/Slave must behave differently:&n; *&n; *      The Master side needs to allow typed-ahead commands to accumulate&n; *      while being canonicalized, so we report &quot;our buffer&quot; as empty until&n; *&t;some threshold is reached, and then report the count. (Any count &gt;&n; *&t;WAKEUP_CHARS is regarded by select() as &quot;full&quot;.)  To avoid deadlock &n; *&t;the count returned must be 0 if no canonical data is available to be &n; *&t;read. (The N_TTY ldisc.chars_in_buffer now knows this.)&n; *  &n; *&t;The Slave side passes all characters in raw mode to the Master side&squot;s&n; *&t;buffer where they can be read immediately, so in this case we can&n; *&t;return the true count in the buffer.&n; */
DECL|function|pty_chars_in_buffer
r_static
r_int
id|pty_chars_in_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
op_logical_or
op_logical_neg
id|to-&gt;ldisc.chars_in_buffer
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* The ldisc must report 0 if no characters available to be read */
id|count
op_assign
id|to-&gt;ldisc
dot
id|chars_in_buffer
c_func
(paren
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;subtype
op_eq
id|PTY_TYPE_SLAVE
)paren
r_return
id|count
suffix:semicolon
multiline_comment|/* Master side driver ... if the other side&squot;s read buffer is less than &n;&t; * half full, return 0 to allow writers to proceed; otherwise return&n;&t; * the count.  This leaves a comfortable margin to avoid overflow, &n;&t; * and still allows half a buffer&squot;s worth of typed-ahead commands.&n;&t; */
r_return
(paren
(paren
id|count
OL
id|N_TTY_BUF_SIZE
op_div
l_int|2
)paren
ques
c_cond
l_int|0
suffix:colon
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the lock flag on a pty */
DECL|function|pty_set_lock
r_static
r_int
id|pty_set_lock
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|__user
op_star
id|arg
)paren
(brace
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|set_bit
c_func
(paren
id|TTY_PTY_LOCK
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
r_else
id|clear_bit
c_func
(paren
id|TTY_PTY_LOCK
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pty_flush_buffer
r_static
r_void
id|pty_flush_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|to-&gt;ldisc.flush_buffer
)paren
id|to-&gt;ldisc
dot
id|flush_buffer
c_func
(paren
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|to-&gt;packet
)paren
(brace
id|tty-&gt;ctrl_status
op_or_assign
id|TIOCPKT_FLUSHWRITE
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|to-&gt;read_wait
)paren
suffix:semicolon
)brace
)brace
DECL|function|pty_open
r_static
r_int
id|pty_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty
op_logical_or
op_logical_neg
id|tty-&gt;link
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|TTY_OTHER_CLOSED
comma
op_amp
id|tty-&gt;flags
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|TTY_PTY_LOCK
comma
op_amp
id|tty-&gt;link-&gt;flags
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;link-&gt;count
op_ne
l_int|1
)paren
r_goto
id|out
suffix:semicolon
id|clear_bit
c_func
(paren
id|TTY_OTHER_CLOSED
comma
op_amp
id|tty-&gt;link-&gt;flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_THROTTLED
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_DO_WRITE_WAKEUP
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|pty_set_termios
r_static
r_void
id|pty_set_termios
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|old_termios
)paren
(brace
id|tty-&gt;termios-&gt;c_cflag
op_and_assign
op_complement
(paren
id|CSIZE
op_or
id|PARENB
)paren
suffix:semicolon
id|tty-&gt;termios-&gt;c_cflag
op_or_assign
(paren
id|CS8
op_or
id|CREAD
)paren
suffix:semicolon
)brace
DECL|variable|pty_ops
r_static
r_struct
id|tty_operations
id|pty_ops
op_assign
(brace
dot
id|open
op_assign
id|pty_open
comma
dot
id|close
op_assign
id|pty_close
comma
dot
id|write
op_assign
id|pty_write
comma
dot
id|write_room
op_assign
id|pty_write_room
comma
dot
id|flush_buffer
op_assign
id|pty_flush_buffer
comma
dot
id|chars_in_buffer
op_assign
id|pty_chars_in_buffer
comma
dot
id|unthrottle
op_assign
id|pty_unthrottle
comma
dot
id|set_termios
op_assign
id|pty_set_termios
comma
)brace
suffix:semicolon
multiline_comment|/* Traditional BSD devices */
macro_line|#ifdef CONFIG_LEGACY_PTYS
DECL|variable|pty_driver
DECL|variable|pty_slave_driver
r_static
r_struct
id|tty_driver
op_star
id|pty_driver
comma
op_star
id|pty_slave_driver
suffix:semicolon
DECL|function|pty_bsd_ioctl
r_static
r_int
id|pty_bsd_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
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
id|TIOCSPTLCK
suffix:colon
multiline_comment|/* Set PT Lock (disallow slave open) */
r_return
id|pty_set_lock
c_func
(paren
id|tty
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
DECL|function|legacy_pty_init
r_static
r_void
id|__init
id|legacy_pty_init
c_func
(paren
r_void
)paren
(brace
id|pty_driver
op_assign
id|alloc_tty_driver
c_func
(paren
id|NR_PTYS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pty_driver
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t allocate pty driver&quot;
)paren
suffix:semicolon
id|pty_slave_driver
op_assign
id|alloc_tty_driver
c_func
(paren
id|NR_PTYS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pty_slave_driver
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t allocate pty slave driver&quot;
)paren
suffix:semicolon
id|pty_driver-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|pty_driver-&gt;driver_name
op_assign
l_string|&quot;pty_master&quot;
suffix:semicolon
id|pty_driver-&gt;name
op_assign
l_string|&quot;pty&quot;
suffix:semicolon
id|pty_driver-&gt;devfs_name
op_assign
l_string|&quot;pty/m&quot;
suffix:semicolon
id|pty_driver-&gt;major
op_assign
id|PTY_MASTER_MAJOR
suffix:semicolon
id|pty_driver-&gt;minor_start
op_assign
l_int|0
suffix:semicolon
id|pty_driver-&gt;type
op_assign
id|TTY_DRIVER_TYPE_PTY
suffix:semicolon
id|pty_driver-&gt;subtype
op_assign
id|PTY_TYPE_MASTER
suffix:semicolon
id|pty_driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|pty_driver-&gt;init_termios.c_iflag
op_assign
l_int|0
suffix:semicolon
id|pty_driver-&gt;init_termios.c_oflag
op_assign
l_int|0
suffix:semicolon
id|pty_driver-&gt;init_termios.c_cflag
op_assign
id|B38400
op_or
id|CS8
op_or
id|CREAD
suffix:semicolon
id|pty_driver-&gt;init_termios.c_lflag
op_assign
l_int|0
suffix:semicolon
id|pty_driver-&gt;flags
op_assign
id|TTY_DRIVER_RESET_TERMIOS
op_or
id|TTY_DRIVER_REAL_RAW
suffix:semicolon
id|pty_driver-&gt;other
op_assign
id|pty_slave_driver
suffix:semicolon
id|tty_set_operations
c_func
(paren
id|pty_driver
comma
op_amp
id|pty_ops
)paren
suffix:semicolon
id|pty_driver-&gt;ioctl
op_assign
id|pty_bsd_ioctl
suffix:semicolon
id|pty_slave_driver-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|pty_slave_driver-&gt;driver_name
op_assign
l_string|&quot;pty_slave&quot;
suffix:semicolon
id|pty_slave_driver-&gt;name
op_assign
l_string|&quot;ttyp&quot;
suffix:semicolon
id|pty_slave_driver-&gt;devfs_name
op_assign
l_string|&quot;pty/s&quot;
suffix:semicolon
id|pty_slave_driver-&gt;major
op_assign
id|PTY_SLAVE_MAJOR
suffix:semicolon
id|pty_slave_driver-&gt;minor_start
op_assign
l_int|0
suffix:semicolon
id|pty_slave_driver-&gt;type
op_assign
id|TTY_DRIVER_TYPE_PTY
suffix:semicolon
id|pty_slave_driver-&gt;subtype
op_assign
id|PTY_TYPE_SLAVE
suffix:semicolon
id|pty_slave_driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|pty_slave_driver-&gt;init_termios.c_cflag
op_assign
id|B38400
op_or
id|CS8
op_or
id|CREAD
suffix:semicolon
id|pty_slave_driver-&gt;flags
op_assign
id|TTY_DRIVER_RESET_TERMIOS
op_or
id|TTY_DRIVER_REAL_RAW
suffix:semicolon
id|pty_slave_driver-&gt;other
op_assign
id|pty_driver
suffix:semicolon
id|tty_set_operations
c_func
(paren
id|pty_slave_driver
comma
op_amp
id|pty_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
id|pty_driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register pty driver&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
id|pty_slave_driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register pty slave driver&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|legacy_pty_init
r_static
r_inline
r_void
id|legacy_pty_init
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/* Unix98 devices */
macro_line|#ifdef CONFIG_UNIX98_PTYS
multiline_comment|/*&n; * sysctl support for setting limits on the number of Unix98 ptys allocated.&n; * Otherwise one can eat up all kernel memory by opening /dev/ptmx repeatedly.&n; */
DECL|variable|pty_limit
r_int
id|pty_limit
op_assign
id|NR_UNIX98_PTY_DEFAULT
suffix:semicolon
DECL|variable|pty_limit_min
r_static
r_int
id|pty_limit_min
op_assign
l_int|0
suffix:semicolon
DECL|variable|pty_limit_max
r_static
r_int
id|pty_limit_max
op_assign
id|NR_UNIX98_PTY_MAX
suffix:semicolon
DECL|variable|pty_table
id|ctl_table
id|pty_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|PTY_MAX
comma
dot
id|procname
op_assign
l_string|&quot;max&quot;
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|data
op_assign
op_amp
id|pty_limit
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|pty_limit_min
comma
dot
id|extra2
op_assign
op_amp
id|pty_limit_max
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|PTY_NR
comma
dot
id|procname
op_assign
l_string|&quot;nr&quot;
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0444
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|pty_unix98_ioctl
r_static
r_int
id|pty_unix98_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
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
id|TIOCSPTLCK
suffix:colon
multiline_comment|/* Set PT Lock (disallow slave open) */
r_return
id|pty_set_lock
c_func
(paren
id|tty
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|TIOCGPTN
suffix:colon
multiline_comment|/* Get PT Number */
r_return
id|put_user
c_func
(paren
id|tty-&gt;index
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
DECL|function|unix98_pty_init
r_static
r_void
id|__init
id|unix98_pty_init
c_func
(paren
r_void
)paren
(brace
id|devfs_mk_dir
c_func
(paren
l_string|&quot;pts&quot;
)paren
suffix:semicolon
id|ptm_driver
op_assign
id|alloc_tty_driver
c_func
(paren
id|NR_UNIX98_PTY_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptm_driver
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t allocate Unix98 ptm driver&quot;
)paren
suffix:semicolon
id|pts_driver
op_assign
id|alloc_tty_driver
c_func
(paren
id|NR_UNIX98_PTY_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pts_driver
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t allocate Unix98 pts driver&quot;
)paren
suffix:semicolon
id|ptm_driver-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|ptm_driver-&gt;driver_name
op_assign
l_string|&quot;pty_master&quot;
suffix:semicolon
id|ptm_driver-&gt;name
op_assign
l_string|&quot;ptm&quot;
suffix:semicolon
id|ptm_driver-&gt;major
op_assign
id|UNIX98_PTY_MASTER_MAJOR
suffix:semicolon
id|ptm_driver-&gt;minor_start
op_assign
l_int|0
suffix:semicolon
id|ptm_driver-&gt;type
op_assign
id|TTY_DRIVER_TYPE_PTY
suffix:semicolon
id|ptm_driver-&gt;subtype
op_assign
id|PTY_TYPE_MASTER
suffix:semicolon
id|ptm_driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|ptm_driver-&gt;init_termios.c_iflag
op_assign
l_int|0
suffix:semicolon
id|ptm_driver-&gt;init_termios.c_oflag
op_assign
l_int|0
suffix:semicolon
id|ptm_driver-&gt;init_termios.c_cflag
op_assign
id|B38400
op_or
id|CS8
op_or
id|CREAD
suffix:semicolon
id|ptm_driver-&gt;init_termios.c_lflag
op_assign
l_int|0
suffix:semicolon
id|ptm_driver-&gt;flags
op_assign
id|TTY_DRIVER_RESET_TERMIOS
op_or
id|TTY_DRIVER_REAL_RAW
op_or
id|TTY_DRIVER_NO_DEVFS
op_or
id|TTY_DRIVER_DEVPTS_MEM
suffix:semicolon
id|ptm_driver-&gt;other
op_assign
id|pts_driver
suffix:semicolon
id|tty_set_operations
c_func
(paren
id|ptm_driver
comma
op_amp
id|pty_ops
)paren
suffix:semicolon
id|ptm_driver-&gt;ioctl
op_assign
id|pty_unix98_ioctl
suffix:semicolon
id|pts_driver-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|pts_driver-&gt;driver_name
op_assign
l_string|&quot;pty_slave&quot;
suffix:semicolon
id|pts_driver-&gt;name
op_assign
l_string|&quot;pts&quot;
suffix:semicolon
id|pts_driver-&gt;major
op_assign
id|UNIX98_PTY_SLAVE_MAJOR
suffix:semicolon
id|pts_driver-&gt;minor_start
op_assign
l_int|0
suffix:semicolon
id|pts_driver-&gt;type
op_assign
id|TTY_DRIVER_TYPE_PTY
suffix:semicolon
id|pts_driver-&gt;subtype
op_assign
id|PTY_TYPE_SLAVE
suffix:semicolon
id|pts_driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|pts_driver-&gt;init_termios.c_cflag
op_assign
id|B38400
op_or
id|CS8
op_or
id|CREAD
suffix:semicolon
id|pts_driver-&gt;flags
op_assign
id|TTY_DRIVER_RESET_TERMIOS
op_or
id|TTY_DRIVER_REAL_RAW
op_or
id|TTY_DRIVER_NO_DEVFS
op_or
id|TTY_DRIVER_DEVPTS_MEM
suffix:semicolon
id|pts_driver-&gt;other
op_assign
id|ptm_driver
suffix:semicolon
id|tty_set_operations
c_func
(paren
id|pts_driver
comma
op_amp
id|pty_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
id|ptm_driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register Unix98 ptm driver&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
id|pts_driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register Unix98 pts driver&quot;
)paren
suffix:semicolon
id|pty_table
(braket
l_int|1
)braket
dot
id|data
op_assign
op_amp
id|ptm_driver-&gt;refcount
suffix:semicolon
)brace
macro_line|#else
DECL|function|unix98_pty_init
r_static
r_inline
r_void
id|unix98_pty_init
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
DECL|function|pty_init
r_static
r_int
id|__init
id|pty_init
c_func
(paren
r_void
)paren
(brace
id|legacy_pty_init
c_func
(paren
)paren
suffix:semicolon
id|unix98_pty_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pty_init
id|module_init
c_func
(paren
id|pty_init
)paren
suffix:semicolon
eof
