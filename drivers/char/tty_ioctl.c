multiline_comment|/*&n; *  linux/drivers/char/tty_ioctl.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; * Modified by Fred N. van Kempen, 01/29/93, to add line disciplines&n; * which can be dynamically activated and de-activated by the line&n; * discipline handling modules (like SLIP).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|TTY_DEBUG_WAIT_UNTIL_SENT
macro_line|#undef TTY_DEBUG_WAIT_UNTIL_SENT
DECL|macro|DEBUG
macro_line|#undef&t;DEBUG
multiline_comment|/*&n; * Internal flag options for termios setting behavior&n; */
DECL|macro|TERMIOS_FLUSH
mdefine_line|#define TERMIOS_FLUSH&t;1
DECL|macro|TERMIOS_WAIT
mdefine_line|#define TERMIOS_WAIT&t;2
DECL|macro|TERMIOS_TERMIO
mdefine_line|#define TERMIOS_TERMIO&t;4
DECL|function|tty_wait_until_sent
r_void
id|tty_wait_until_sent
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|timeout
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
macro_line|#ifdef TTY_DEBUG_WAIT_UNTIL_SENT
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s wait until sent...&bslash;n&quot;
comma
id|tty_name
c_func
(paren
id|tty
comma
id|buf
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;driver-&gt;chars_in_buffer
)paren
r_return
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|tty-&gt;write_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
r_do
(brace
macro_line|#ifdef TTY_DEBUG_WAIT_UNTIL_SENT
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;waiting %s...(%d)&bslash;n&quot;
comma
id|tty_name
c_func
(paren
id|tty
comma
id|buf
)paren
comma
id|tty-&gt;driver
op_member_access_from_pointer
id|chars_in_buffer
c_func
(paren
id|tty
)paren
)paren
suffix:semicolon
macro_line|#endif
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
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
r_goto
id|stop_waiting
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;driver
op_member_access_from_pointer
id|chars_in_buffer
c_func
(paren
id|tty
)paren
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
r_while
c_loop
(paren
id|timeout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;wait_until_sent
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|wait_until_sent
c_func
(paren
id|tty
comma
id|timeout
)paren
suffix:semicolon
id|stop_waiting
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|tty-&gt;write_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
DECL|variable|tty_wait_until_sent
id|EXPORT_SYMBOL
c_func
(paren
id|tty_wait_until_sent
)paren
suffix:semicolon
DECL|function|unset_locked_termios
r_static
r_void
id|unset_locked_termios
c_func
(paren
r_struct
id|termios
op_star
id|termios
comma
r_struct
id|termios
op_star
id|old
comma
r_struct
id|termios
op_star
id|locked
)paren
(brace
r_int
id|i
suffix:semicolon
DECL|macro|NOSET_MASK
mdefine_line|#define NOSET_MASK(x,y,z) (x = ((x) &amp; ~(z)) | ((y) &amp; (z)))
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning?!? termios_locked is NULL.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_iflag
comma
id|old-&gt;c_iflag
comma
id|locked-&gt;c_iflag
)paren
suffix:semicolon
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_oflag
comma
id|old-&gt;c_oflag
comma
id|locked-&gt;c_oflag
)paren
suffix:semicolon
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_cflag
comma
id|old-&gt;c_cflag
comma
id|locked-&gt;c_cflag
)paren
suffix:semicolon
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_lflag
comma
id|old-&gt;c_lflag
comma
id|locked-&gt;c_lflag
)paren
suffix:semicolon
id|termios-&gt;c_line
op_assign
id|locked-&gt;c_line
ques
c_cond
id|old-&gt;c_line
suffix:colon
id|termios-&gt;c_line
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
id|NCCS
suffix:semicolon
id|i
op_increment
)paren
id|termios-&gt;c_cc
(braket
id|i
)braket
op_assign
id|locked-&gt;c_cc
(braket
id|i
)braket
ques
c_cond
id|old-&gt;c_cc
(braket
id|i
)braket
suffix:colon
id|termios-&gt;c_cc
(braket
id|i
)braket
suffix:semicolon
)brace
DECL|function|change_termios
r_static
r_void
id|change_termios
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
id|new_termios
)paren
(brace
r_int
id|canon_change
suffix:semicolon
r_struct
id|termios
id|old_termios
op_assign
op_star
id|tty-&gt;termios
suffix:semicolon
r_struct
id|tty_ldisc
op_star
id|ld
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Perform the actual termios internal changes under lock.&n;&t; */
multiline_comment|/* FIXME: we need to decide on some locking/ordering semantics&n;&t;   for the set_termios notification eventually */
id|down
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
op_star
id|tty-&gt;termios
op_assign
op_star
id|new_termios
suffix:semicolon
id|unset_locked_termios
c_func
(paren
id|tty-&gt;termios
comma
op_amp
id|old_termios
comma
id|tty-&gt;termios_locked
)paren
suffix:semicolon
id|canon_change
op_assign
(paren
id|old_termios.c_lflag
op_xor
id|tty-&gt;termios-&gt;c_lflag
)paren
op_amp
id|ICANON
suffix:semicolon
r_if
c_cond
(paren
id|canon_change
)paren
(brace
id|memset
c_func
(paren
op_amp
id|tty-&gt;read_flags
comma
l_int|0
comma
r_sizeof
id|tty-&gt;read_flags
)paren
suffix:semicolon
id|tty-&gt;canon_head
op_assign
id|tty-&gt;read_tail
suffix:semicolon
id|tty-&gt;canon_data
op_assign
l_int|0
suffix:semicolon
id|tty-&gt;erasing
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|canon_change
op_logical_and
op_logical_neg
id|L_ICANON
c_func
(paren
id|tty
)paren
op_logical_and
id|tty-&gt;read_cnt
)paren
multiline_comment|/* Get characters left over from canonical mode. */
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;read_wait
)paren
suffix:semicolon
multiline_comment|/* See if packet mode change of state. */
r_if
c_cond
(paren
id|tty-&gt;link
op_logical_and
id|tty-&gt;link-&gt;packet
)paren
(brace
r_int
id|old_flow
op_assign
(paren
(paren
id|old_termios.c_iflag
op_amp
id|IXON
)paren
op_logical_and
(paren
id|old_termios.c_cc
(braket
id|VSTOP
)braket
op_eq
l_char|&squot;&bslash;023&squot;
)paren
op_logical_and
(paren
id|old_termios.c_cc
(braket
id|VSTART
)braket
op_eq
l_char|&squot;&bslash;021&squot;
)paren
)paren
suffix:semicolon
r_int
id|new_flow
op_assign
(paren
id|I_IXON
c_func
(paren
id|tty
)paren
op_logical_and
id|STOP_CHAR
c_func
(paren
id|tty
)paren
op_eq
l_char|&squot;&bslash;023&squot;
op_logical_and
id|START_CHAR
c_func
(paren
id|tty
)paren
op_eq
l_char|&squot;&bslash;021&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_flow
op_ne
id|new_flow
)paren
(brace
id|tty-&gt;ctrl_status
op_and_assign
op_complement
(paren
id|TIOCPKT_DOSTOP
op_or
id|TIOCPKT_NOSTOP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_flow
)paren
id|tty-&gt;ctrl_status
op_or_assign
id|TIOCPKT_DOSTOP
suffix:semicolon
r_else
id|tty-&gt;ctrl_status
op_or_assign
id|TIOCPKT_NOSTOP
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;read_wait
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;set_termios
)paren
(paren
op_star
id|tty-&gt;driver-&gt;set_termios
)paren
(paren
id|tty
comma
op_amp
id|old_termios
)paren
suffix:semicolon
id|ld
op_assign
id|tty_ldisc_ref
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ld
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ld-&gt;set_termios
)paren
(paren
id|ld-&gt;set_termios
)paren
(paren
id|tty
comma
op_amp
id|old_termios
)paren
suffix:semicolon
id|tty_ldisc_deref
c_func
(paren
id|ld
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
)brace
DECL|function|set_termios
r_static
r_int
id|set_termios
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_void
id|__user
op_star
id|arg
comma
r_int
id|opt
)paren
(brace
r_struct
id|termios
id|tmp_termios
suffix:semicolon
r_struct
id|tty_ldisc
op_star
id|ld
suffix:semicolon
r_int
id|retval
op_assign
id|tty_check_change
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_amp
id|TERMIOS_TERMIO
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|tmp_termios
comma
id|tty-&gt;termios
comma
r_sizeof
(paren
r_struct
id|termios
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_termio_to_kernel_termios
c_func
(paren
op_amp
id|tmp_termios
comma
(paren
r_struct
id|termio
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|user_termios_to_kernel_termios
c_func
(paren
op_amp
id|tmp_termios
comma
(paren
r_struct
id|termios
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|ld
op_assign
id|tty_ldisc_ref
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ld
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|opt
op_amp
id|TERMIOS_FLUSH
)paren
op_logical_and
id|ld-&gt;flush_buffer
)paren
id|ld
op_member_access_from_pointer
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
id|tty_ldisc_deref
c_func
(paren
id|ld
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt
op_amp
id|TERMIOS_WAIT
)paren
(brace
id|tty_wait_until_sent
c_func
(paren
id|tty
comma
l_int|0
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
)brace
id|change_termios
c_func
(paren
id|tty
comma
op_amp
id|tmp_termios
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_termio
r_static
r_int
id|get_termio
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termio
id|__user
op_star
id|termio
)paren
(brace
r_if
c_cond
(paren
id|kernel_termios_to_user_termio
c_func
(paren
id|termio
comma
id|tty-&gt;termios
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inq_canon
r_static
r_int
r_int
id|inq_canon
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_int
id|nr
comma
id|head
comma
id|tail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;canon_data
op_logical_or
op_logical_neg
id|tty-&gt;read_buf
)paren
r_return
l_int|0
suffix:semicolon
id|head
op_assign
id|tty-&gt;canon_head
suffix:semicolon
id|tail
op_assign
id|tty-&gt;read_tail
suffix:semicolon
id|nr
op_assign
(paren
id|head
op_minus
id|tail
)paren
op_amp
(paren
id|N_TTY_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Skip EOF-chars.. */
r_while
c_loop
(paren
id|head
op_ne
id|tail
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|tail
comma
id|tty-&gt;read_flags
)paren
op_logical_and
id|tty-&gt;read_buf
(braket
id|tail
)braket
op_eq
id|__DISABLED_CHAR
)paren
id|nr
op_decrement
suffix:semicolon
id|tail
op_assign
(paren
id|tail
op_plus
l_int|1
)paren
op_amp
(paren
id|N_TTY_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|nr
suffix:semicolon
)brace
macro_line|#ifdef TIOCGETP
multiline_comment|/*&n; * These are deprecated, but there is limited support..&n; *&n; * The &quot;sg_flags&quot; translation is a joke..&n; */
DECL|function|get_sgflags
r_static
r_int
id|get_sgflags
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tty-&gt;termios-&gt;c_lflag
op_amp
id|ICANON
)paren
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;termios-&gt;c_lflag
op_amp
id|ISIG
)paren
id|flags
op_or_assign
l_int|0x02
suffix:semicolon
multiline_comment|/* cbreak */
r_else
id|flags
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* raw */
)brace
r_if
c_cond
(paren
id|tty-&gt;termios-&gt;c_lflag
op_amp
id|ECHO
)paren
id|flags
op_or_assign
l_int|0x08
suffix:semicolon
multiline_comment|/* echo */
r_if
c_cond
(paren
id|tty-&gt;termios-&gt;c_oflag
op_amp
id|OPOST
)paren
r_if
c_cond
(paren
id|tty-&gt;termios-&gt;c_oflag
op_amp
id|ONLCR
)paren
id|flags
op_or_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* crmod */
r_return
id|flags
suffix:semicolon
)brace
DECL|function|get_sgttyb
r_static
r_int
id|get_sgttyb
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|sgttyb
id|__user
op_star
id|sgttyb
)paren
(brace
r_struct
id|sgttyb
id|tmp
suffix:semicolon
id|down
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
id|tmp.sg_ispeed
op_assign
l_int|0
suffix:semicolon
id|tmp.sg_ospeed
op_assign
l_int|0
suffix:semicolon
id|tmp.sg_erase
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VERASE
)braket
suffix:semicolon
id|tmp.sg_kill
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VKILL
)braket
suffix:semicolon
id|tmp.sg_flags
op_assign
id|get_sgflags
c_func
(paren
id|tty
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|sgttyb
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|set_sgflags
r_static
r_void
id|set_sgflags
c_func
(paren
r_struct
id|termios
op_star
id|termios
comma
r_int
id|flags
)paren
(brace
id|termios-&gt;c_iflag
op_assign
id|ICRNL
op_or
id|IXON
suffix:semicolon
id|termios-&gt;c_oflag
op_assign
l_int|0
suffix:semicolon
id|termios-&gt;c_lflag
op_assign
id|ISIG
op_or
id|ICANON
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
l_int|0x02
)paren
(brace
multiline_comment|/* cbreak */
id|termios-&gt;c_iflag
op_assign
l_int|0
suffix:semicolon
id|termios-&gt;c_lflag
op_and_assign
op_complement
id|ICANON
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
l_int|0x08
)paren
(brace
multiline_comment|/* echo */
id|termios-&gt;c_lflag
op_or_assign
id|ECHO
op_or
id|ECHOE
op_or
id|ECHOK
op_or
id|ECHOCTL
op_or
id|ECHOKE
op_or
id|IEXTEN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
l_int|0x10
)paren
(brace
multiline_comment|/* crmod */
id|termios-&gt;c_oflag
op_or_assign
id|OPOST
op_or
id|ONLCR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
l_int|0x20
)paren
(brace
multiline_comment|/* raw */
id|termios-&gt;c_iflag
op_assign
l_int|0
suffix:semicolon
id|termios-&gt;c_lflag
op_and_assign
op_complement
(paren
id|ISIG
op_or
id|ICANON
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|termios-&gt;c_lflag
op_amp
id|ICANON
)paren
)paren
(brace
id|termios-&gt;c_cc
(braket
id|VMIN
)braket
op_assign
l_int|1
suffix:semicolon
id|termios-&gt;c_cc
(braket
id|VTIME
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|set_sgttyb
r_static
r_int
id|set_sgttyb
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|sgttyb
id|__user
op_star
id|sgttyb
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|sgttyb
id|tmp
suffix:semicolon
r_struct
id|termios
id|termios
suffix:semicolon
id|retval
op_assign
id|tty_check_change
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
id|sgttyb
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
id|termios
op_assign
op_star
id|tty-&gt;termios
suffix:semicolon
id|termios.c_cc
(braket
id|VERASE
)braket
op_assign
id|tmp.sg_erase
suffix:semicolon
id|termios.c_cc
(braket
id|VKILL
)braket
op_assign
id|tmp.sg_kill
suffix:semicolon
id|set_sgflags
c_func
(paren
op_amp
id|termios
comma
id|tmp.sg_flags
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
id|change_termios
c_func
(paren
id|tty
comma
op_amp
id|termios
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef TIOCGETC
DECL|function|get_tchars
r_static
r_int
id|get_tchars
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|tchars
id|__user
op_star
id|tchars
)paren
(brace
r_struct
id|tchars
id|tmp
suffix:semicolon
id|tmp.t_intrc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VINTR
)braket
suffix:semicolon
id|tmp.t_quitc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VQUIT
)braket
suffix:semicolon
id|tmp.t_startc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VSTART
)braket
suffix:semicolon
id|tmp.t_stopc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VSTOP
)braket
suffix:semicolon
id|tmp.t_eofc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VEOF
)braket
suffix:semicolon
id|tmp.t_brkc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VEOL2
)braket
suffix:semicolon
multiline_comment|/* what is brkc anyway? */
r_return
id|copy_to_user
c_func
(paren
id|tchars
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|set_tchars
r_static
r_int
id|set_tchars
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|tchars
id|__user
op_star
id|tchars
)paren
(brace
r_struct
id|tchars
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
id|tchars
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VINTR
)braket
op_assign
id|tmp.t_intrc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VQUIT
)braket
op_assign
id|tmp.t_quitc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VSTART
)braket
op_assign
id|tmp.t_startc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VSTOP
)braket
op_assign
id|tmp.t_stopc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VEOF
)braket
op_assign
id|tmp.t_eofc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VEOL2
)braket
op_assign
id|tmp.t_brkc
suffix:semicolon
multiline_comment|/* what is brkc anyway? */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef TIOCGLTC
DECL|function|get_ltchars
r_static
r_int
id|get_ltchars
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|ltchars
id|__user
op_star
id|ltchars
)paren
(brace
r_struct
id|ltchars
id|tmp
suffix:semicolon
id|tmp.t_suspc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VSUSP
)braket
suffix:semicolon
id|tmp.t_dsuspc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VSUSP
)braket
suffix:semicolon
multiline_comment|/* what is dsuspc anyway? */
id|tmp.t_rprntc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VREPRINT
)braket
suffix:semicolon
id|tmp.t_flushc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VEOL2
)braket
suffix:semicolon
multiline_comment|/* what is flushc anyway? */
id|tmp.t_werasc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VWERASE
)braket
suffix:semicolon
id|tmp.t_lnextc
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|VLNEXT
)braket
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|ltchars
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|set_ltchars
r_static
r_int
id|set_ltchars
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|ltchars
id|__user
op_star
id|ltchars
)paren
(brace
r_struct
id|ltchars
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
id|ltchars
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VSUSP
)braket
op_assign
id|tmp.t_suspc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VEOL2
)braket
op_assign
id|tmp.t_dsuspc
suffix:semicolon
multiline_comment|/* what is dsuspc anyway? */
id|tty-&gt;termios-&gt;c_cc
(braket
id|VREPRINT
)braket
op_assign
id|tmp.t_rprntc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VEOL2
)braket
op_assign
id|tmp.t_flushc
suffix:semicolon
multiline_comment|/* what is flushc anyway? */
id|tty-&gt;termios-&gt;c_cc
(braket
id|VWERASE
)braket
op_assign
id|tmp.t_werasc
suffix:semicolon
id|tty-&gt;termios-&gt;c_cc
(braket
id|VLNEXT
)braket
op_assign
id|tmp.t_lnextc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Send a high priority character to the tty.&n; */
DECL|function|send_prio_char
r_void
id|send_prio_char
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_char
id|ch
)paren
(brace
r_int
id|was_stopped
op_assign
id|tty-&gt;stopped
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;send_xchar
)paren
(brace
id|tty-&gt;driver
op_member_access_from_pointer
id|send_xchar
c_func
(paren
id|tty
comma
id|ch
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|was_stopped
)paren
id|start_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
id|tty-&gt;driver
op_member_access_from_pointer
id|write
c_func
(paren
id|tty
comma
l_int|0
comma
op_amp
id|ch
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|was_stopped
)paren
id|stop_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
DECL|function|n_tty_ioctl
r_int
id|n_tty_ioctl
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
r_struct
id|tty_struct
op_star
id|real_tty
suffix:semicolon
r_void
id|__user
op_star
id|p
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_struct
id|tty_ldisc
op_star
id|ld
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;type
op_eq
id|TTY_DRIVER_TYPE_PTY
op_logical_and
id|tty-&gt;driver-&gt;subtype
op_eq
id|PTY_TYPE_MASTER
)paren
id|real_tty
op_assign
id|tty-&gt;link
suffix:semicolon
r_else
id|real_tty
op_assign
id|tty
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
macro_line|#ifdef TIOCGETP
r_case
id|TIOCGETP
suffix:colon
r_return
id|get_sgttyb
c_func
(paren
id|real_tty
comma
(paren
r_struct
id|sgttyb
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|TIOCSETP
suffix:colon
r_case
id|TIOCSETN
suffix:colon
r_return
id|set_sgttyb
c_func
(paren
id|real_tty
comma
(paren
r_struct
id|sgttyb
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef TIOCGETC
r_case
id|TIOCGETC
suffix:colon
r_return
id|get_tchars
c_func
(paren
id|real_tty
comma
id|p
)paren
suffix:semicolon
r_case
id|TIOCSETC
suffix:colon
r_return
id|set_tchars
c_func
(paren
id|real_tty
comma
id|p
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef TIOCGLTC
r_case
id|TIOCGLTC
suffix:colon
r_return
id|get_ltchars
c_func
(paren
id|real_tty
comma
id|p
)paren
suffix:semicolon
r_case
id|TIOCSLTC
suffix:colon
r_return
id|set_ltchars
c_func
(paren
id|real_tty
comma
id|p
)paren
suffix:semicolon
macro_line|#endif
r_case
id|TCGETS
suffix:colon
r_if
c_cond
(paren
id|kernel_termios_to_user_termios
c_func
(paren
(paren
r_struct
id|termios
id|__user
op_star
)paren
id|arg
comma
id|real_tty-&gt;termios
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TCSETSF
suffix:colon
r_return
id|set_termios
c_func
(paren
id|real_tty
comma
id|p
comma
id|TERMIOS_FLUSH
op_or
id|TERMIOS_WAIT
)paren
suffix:semicolon
r_case
id|TCSETSW
suffix:colon
r_return
id|set_termios
c_func
(paren
id|real_tty
comma
id|p
comma
id|TERMIOS_WAIT
)paren
suffix:semicolon
r_case
id|TCSETS
suffix:colon
r_return
id|set_termios
c_func
(paren
id|real_tty
comma
id|p
comma
l_int|0
)paren
suffix:semicolon
r_case
id|TCGETA
suffix:colon
r_return
id|get_termio
c_func
(paren
id|real_tty
comma
id|p
)paren
suffix:semicolon
r_case
id|TCSETAF
suffix:colon
r_return
id|set_termios
c_func
(paren
id|real_tty
comma
id|p
comma
id|TERMIOS_FLUSH
op_or
id|TERMIOS_WAIT
op_or
id|TERMIOS_TERMIO
)paren
suffix:semicolon
r_case
id|TCSETAW
suffix:colon
r_return
id|set_termios
c_func
(paren
id|real_tty
comma
id|p
comma
id|TERMIOS_WAIT
op_or
id|TERMIOS_TERMIO
)paren
suffix:semicolon
r_case
id|TCSETA
suffix:colon
r_return
id|set_termios
c_func
(paren
id|real_tty
comma
id|p
comma
id|TERMIOS_TERMIO
)paren
suffix:semicolon
r_case
id|TCXONC
suffix:colon
id|retval
op_assign
id|tty_check_change
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_switch
c_cond
(paren
id|arg
)paren
(brace
r_case
id|TCOOFF
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;flow_stopped
)paren
(brace
id|tty-&gt;flow_stopped
op_assign
l_int|1
suffix:semicolon
id|stop_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|TCOON
suffix:colon
r_if
c_cond
(paren
id|tty-&gt;flow_stopped
)paren
(brace
id|tty-&gt;flow_stopped
op_assign
l_int|0
suffix:semicolon
id|start_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|TCIOFF
suffix:colon
r_if
c_cond
(paren
id|STOP_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
id|send_prio_char
c_func
(paren
id|tty
comma
id|STOP_CHAR
c_func
(paren
id|tty
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCION
suffix:colon
r_if
c_cond
(paren
id|START_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
id|send_prio_char
c_func
(paren
id|tty
comma
id|START_CHAR
c_func
(paren
id|tty
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|TCFLSH
suffix:colon
id|retval
op_assign
id|tty_check_change
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|ld
op_assign
id|tty_ldisc_ref
c_func
(paren
id|tty
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|arg
)paren
(brace
r_case
id|TCIFLUSH
suffix:colon
r_if
c_cond
(paren
id|ld-&gt;flush_buffer
)paren
id|ld
op_member_access_from_pointer
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCIOFLUSH
suffix:colon
r_if
c_cond
(paren
id|ld-&gt;flush_buffer
)paren
id|ld
op_member_access_from_pointer
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|TCOFLUSH
suffix:colon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;flush_buffer
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|tty_ldisc_deref
c_func
(paren
id|ld
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|tty_ldisc_deref
c_func
(paren
id|ld
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCOUTQ
suffix:colon
r_return
id|put_user
c_func
(paren
id|tty-&gt;driver-&gt;chars_in_buffer
ques
c_cond
id|tty-&gt;driver
op_member_access_from_pointer
id|chars_in_buffer
c_func
(paren
id|tty
)paren
suffix:colon
l_int|0
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
id|TIOCINQ
suffix:colon
id|retval
op_assign
id|tty-&gt;read_cnt
suffix:semicolon
r_if
c_cond
(paren
id|L_ICANON
c_func
(paren
id|tty
)paren
)paren
id|retval
op_assign
id|inq_canon
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|retval
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
r_case
id|TIOCGLCKTRMIOS
suffix:colon
r_if
c_cond
(paren
id|kernel_termios_to_user_termios
c_func
(paren
(paren
r_struct
id|termios
id|__user
op_star
)paren
id|arg
comma
id|real_tty-&gt;termios_locked
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCSLCKTRMIOS
suffix:colon
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
id|user_termios_to_kernel_termios
c_func
(paren
id|real_tty-&gt;termios_locked
comma
(paren
r_struct
id|termios
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCPKT
suffix:colon
(brace
r_int
id|pktmode
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;type
op_ne
id|TTY_DRIVER_TYPE_PTY
op_logical_or
id|tty-&gt;driver-&gt;subtype
op_ne
id|PTY_TYPE_MASTER
)paren
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|pktmode
comma
(paren
r_int
id|__user
op_star
)paren
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
id|pktmode
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;packet
)paren
(brace
id|tty-&gt;packet
op_assign
l_int|1
suffix:semicolon
id|tty-&gt;link-&gt;ctrl_status
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
id|tty-&gt;packet
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|TIOCGSOFTCAR
suffix:colon
r_return
id|put_user
c_func
(paren
id|C_CLOCAL
c_func
(paren
id|tty
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
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
id|TIOCSSOFTCAR
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|arg
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
id|tty-&gt;termios-&gt;c_cflag
op_assign
(paren
(paren
id|tty-&gt;termios-&gt;c_cflag
op_amp
op_complement
id|CLOCAL
)paren
op_or
(paren
id|arg
ques
c_cond
id|CLOCAL
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|tty-&gt;termios_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|variable|n_tty_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|n_tty_ioctl
)paren
suffix:semicolon
eof
