multiline_comment|/*&n; *  linux/kernel/printk.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; * Modified to make sys_syslog() more flexible: added commands to&n; * return the last 4k of kernel messages, regardless of whether&n; * they&squot;ve been read or not.  Added option to suppress kernel printk&squot;s&n; * to the console.  Added hook for sending the console messages&n; * elsewhere, in preparation for a serial line console (someday).&n; * Ted Ts&squot;o, 2/11/93.&n; * Modified for sysctl support, 1/8/97, Chris Horn.&n; * Fixed SMP synchronization, 08/08/99, Manfred Spraul &n; *     manfreds@colorfullife.com&n; * Rewrote bits to get rid of console_lock&n; *&t;01Mar01 Andrew Morton &lt;andrewm@uow.edu.au&gt;&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;&t;&t;&t;/* For in_interrupt() */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_MULTIQUAD
DECL|macro|LOG_BUF_LEN
mdefine_line|#define LOG_BUF_LEN&t;(65536)
macro_line|#elif defined(CONFIG_SMP)
DECL|macro|LOG_BUF_LEN
mdefine_line|#define LOG_BUF_LEN&t;(32768)
macro_line|#else&t;
DECL|macro|LOG_BUF_LEN
mdefine_line|#define LOG_BUF_LEN&t;(16384)&t;&t;&t;/* This must be a power of two */
macro_line|#endif
DECL|macro|LOG_BUF_MASK
mdefine_line|#define LOG_BUF_MASK&t;(LOG_BUF_LEN-1)
multiline_comment|/* printk&squot;s without a loglevel use this.. */
DECL|macro|DEFAULT_MESSAGE_LOGLEVEL
mdefine_line|#define DEFAULT_MESSAGE_LOGLEVEL 4 /* KERN_WARNING */
multiline_comment|/* We show everything that is MORE important than this.. */
DECL|macro|MINIMUM_CONSOLE_LOGLEVEL
mdefine_line|#define MINIMUM_CONSOLE_LOGLEVEL 1 /* Minimum loglevel we let people use */
DECL|macro|DEFAULT_CONSOLE_LOGLEVEL
mdefine_line|#define DEFAULT_CONSOLE_LOGLEVEL 7 /* anything MORE serious than KERN_DEBUG */
DECL|variable|log_wait
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|log_wait
)paren
suffix:semicolon
multiline_comment|/* Keep together for sysctl support */
DECL|variable|console_loglevel
r_int
id|console_loglevel
op_assign
id|DEFAULT_CONSOLE_LOGLEVEL
suffix:semicolon
DECL|variable|default_message_loglevel
r_int
id|default_message_loglevel
op_assign
id|DEFAULT_MESSAGE_LOGLEVEL
suffix:semicolon
DECL|variable|minimum_console_loglevel
r_int
id|minimum_console_loglevel
op_assign
id|MINIMUM_CONSOLE_LOGLEVEL
suffix:semicolon
DECL|variable|default_console_loglevel
r_int
id|default_console_loglevel
op_assign
id|DEFAULT_CONSOLE_LOGLEVEL
suffix:semicolon
DECL|variable|oops_in_progress
r_int
id|oops_in_progress
suffix:semicolon
multiline_comment|/*&n; * console_sem protects the console_drivers list, and also&n; * provides serialisation for access to the entire console&n; * driver system.&n; */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|console_sem
)paren
suffix:semicolon
DECL|variable|console_drivers
r_struct
id|console
op_star
id|console_drivers
suffix:semicolon
multiline_comment|/*&n; * logbuf_lock protects log_buf, log_start, log_end, con_start and logged_chars&n; * It is also used in interesting ways to provide interlocking in&n; * release_console_sem().&n; */
DECL|variable|logbuf_lock
r_static
id|spinlock_t
id|logbuf_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|log_buf
r_static
r_char
id|log_buf
(braket
id|LOG_BUF_LEN
)braket
suffix:semicolon
DECL|macro|LOG_BUF
mdefine_line|#define LOG_BUF(idx) (log_buf[(idx) &amp; LOG_BUF_MASK])
multiline_comment|/*&n; * The indices into log_buf are not constrained to LOG_BUF_LEN - they&n; * must be masked before subscripting&n; */
DECL|variable|log_start
r_static
r_int
r_int
id|log_start
suffix:semicolon
multiline_comment|/* Index into log_buf: next char to be read by syslog() */
DECL|variable|con_start
r_static
r_int
r_int
id|con_start
suffix:semicolon
multiline_comment|/* Index into log_buf: next char to be sent to consoles */
DECL|variable|log_end
r_static
r_int
r_int
id|log_end
suffix:semicolon
multiline_comment|/* Index into log_buf: most-recently-written-char + 1 */
DECL|variable|logged_chars
r_static
r_int
r_int
id|logged_chars
suffix:semicolon
multiline_comment|/* Number of chars produced since last read+clear operation */
DECL|variable|console_cmdline
r_struct
id|console_cmdline
id|console_cmdline
(braket
id|MAX_CMDLINECONSOLES
)braket
suffix:semicolon
DECL|variable|preferred_console
r_static
r_int
id|preferred_console
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Flag: console code may call schedule() */
DECL|variable|console_may_schedule
r_static
r_int
id|console_may_schedule
suffix:semicolon
multiline_comment|/*&n; *&t;Setup a list of consoles. Called from init/main.c&n; */
DECL|function|console_setup
r_static
r_int
id|__init
id|console_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_struct
id|console_cmdline
op_star
id|c
suffix:semicolon
r_char
id|name
(braket
r_sizeof
(paren
id|c-&gt;name
)paren
)braket
suffix:semicolon
r_char
op_star
id|s
comma
op_star
id|options
suffix:semicolon
r_int
id|i
comma
id|idx
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Decode str into name, index, options.&n;&t; */
r_if
c_cond
(paren
id|str
(braket
l_int|0
)braket
op_ge
l_char|&squot;0&squot;
op_logical_and
id|str
(braket
l_int|0
)braket
op_le
l_char|&squot;9&squot;
)paren
(brace
id|strcpy
c_func
(paren
id|name
comma
l_string|&quot;ttyS&quot;
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|name
op_plus
l_int|4
comma
id|str
comma
r_sizeof
(paren
id|name
)paren
op_minus
l_int|5
)paren
suffix:semicolon
)brace
r_else
id|strncpy
c_func
(paren
id|name
comma
id|str
comma
r_sizeof
(paren
id|name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|name
(braket
r_sizeof
(paren
id|name
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|options
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
op_star
(paren
id|options
op_increment
)paren
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;ttya&quot;
)paren
)paren
id|strcpy
c_func
(paren
id|name
comma
l_string|&quot;ttyS0&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;ttyb&quot;
)paren
)paren
id|strcpy
c_func
(paren
id|name
comma
l_string|&quot;ttyS1&quot;
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|s
op_assign
id|name
suffix:semicolon
op_star
id|s
suffix:semicolon
id|s
op_increment
)paren
r_if
c_cond
(paren
op_star
id|s
op_ge
l_char|&squot;0&squot;
op_logical_and
op_star
id|s
op_le
l_char|&squot;9&squot;
)paren
r_break
suffix:semicolon
id|idx
op_assign
id|simple_strtoul
c_func
(paren
id|s
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
op_star
id|s
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;See if this tty is not yet registered, and&n;&t; *&t;if we have a slot free.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CMDLINECONSOLES
op_logical_and
id|console_cmdline
(braket
id|i
)braket
dot
id|name
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|console_cmdline
(braket
id|i
)braket
dot
id|name
comma
id|name
)paren
op_eq
l_int|0
op_logical_and
id|console_cmdline
(braket
id|i
)braket
dot
id|index
op_eq
id|idx
)paren
(brace
id|preferred_console
op_assign
id|i
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|MAX_CMDLINECONSOLES
)paren
r_return
l_int|1
suffix:semicolon
id|preferred_console
op_assign
id|i
suffix:semicolon
id|c
op_assign
op_amp
id|console_cmdline
(braket
id|i
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|c-&gt;name
comma
id|name
comma
r_sizeof
(paren
id|c-&gt;name
)paren
)paren
suffix:semicolon
id|c-&gt;options
op_assign
id|options
suffix:semicolon
id|c-&gt;index
op_assign
id|idx
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;console=&quot;
comma
id|console_setup
)paren
suffix:semicolon
multiline_comment|/*&n; * Commands to do_syslog:&n; *&n; * &t;0 -- Close the log.  Currently a NOP.&n; * &t;1 -- Open the log. Currently a NOP.&n; * &t;2 -- Read from the log.&n; * &t;3 -- Read all messages remaining in the ring buffer.&n; * &t;4 -- Read and clear all messages remaining in the ring buffer&n; * &t;5 -- Clear ring buffer.&n; * &t;6 -- Disable printk&squot;s to console&n; * &t;7 -- Enable printk&squot;s to console&n; *&t;8 -- Set level of messages printed to console&n; *&t;9 -- Return number of unread characters in the log buffer&n; */
DECL|function|do_syslog
r_int
id|do_syslog
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|i
comma
id|j
comma
id|limit
comma
id|count
suffix:semicolon
r_int
id|do_clear
op_assign
l_int|0
suffix:semicolon
r_char
id|c
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Close log */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Open log */
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* Read from log */
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|len
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|wait_event_interruptible
c_func
(paren
id|log_wait
comma
(paren
id|log_start
op_minus
id|log_end
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|log_start
op_ne
id|log_end
)paren
op_logical_and
id|i
OL
id|len
)paren
(brace
id|c
op_assign
id|LOG_BUF
c_func
(paren
id|log_start
)paren
suffix:semicolon
id|log_start
op_increment
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|c
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|error
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* Read/clear last kernel messages */
id|do_clear
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* FALL THRU */
r_case
l_int|3
suffix:colon
multiline_comment|/* Read last kernel messages */
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|len
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|count
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|LOG_BUF_LEN
)paren
id|count
op_assign
id|LOG_BUF_LEN
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|logged_chars
)paren
id|count
op_assign
id|logged_chars
suffix:semicolon
r_if
c_cond
(paren
id|do_clear
)paren
id|logged_chars
op_assign
l_int|0
suffix:semicolon
id|limit
op_assign
id|log_end
suffix:semicolon
multiline_comment|/*&n;&t;&t; * __put_user() could sleep, and while we sleep&n;&t;&t; * printk() could overwrite the messages &n;&t;&t; * we try to copy to user space. Therefore&n;&t;&t; * the messages are copied in reverse. &lt;manfreds&gt;&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|limit
op_minus
l_int|1
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|j
op_plus
id|LOG_BUF_LEN
OL
id|log_end
)paren
r_break
suffix:semicolon
id|c
op_assign
id|LOG_BUF
c_func
(paren
id|j
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|c
comma
op_amp
id|buf
(braket
id|count
op_minus
l_int|1
op_minus
id|i
)braket
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|error
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|count
)paren
(brace
r_int
id|offset
op_assign
id|count
op_minus
id|error
suffix:semicolon
multiline_comment|/* buffer overflow during copy, correct user buffer. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|error
suffix:semicolon
id|i
op_increment
)paren
(brace
id|__get_user
c_func
(paren
id|c
comma
op_amp
id|buf
(braket
id|i
op_plus
id|offset
)braket
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|c
comma
op_amp
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* Clear ring buffer */
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|logged_chars
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* Disable logging to console */
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|minimum_console_loglevel
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* Enable logging to console */
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|default_console_loglevel
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/* Set level of messages printed to console */
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
template_param
l_int|8
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|minimum_console_loglevel
)paren
id|len
op_assign
id|minimum_console_loglevel
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|len
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
multiline_comment|/* Number of chars in the log buffer */
id|spin_lock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
id|error
op_assign
id|log_end
op_minus
id|log_start
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_syslog
id|asmlinkage
r_int
id|sys_syslog
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
(paren
id|type
op_ne
l_int|3
)paren
op_logical_and
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
r_return
id|do_syslog
c_func
(paren
id|type
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Call the console drivers on a range of log_buf&n; */
DECL|function|__call_console_drivers
r_static
r_void
id|__call_console_drivers
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|console
op_star
id|con
suffix:semicolon
r_for
c_loop
(paren
id|con
op_assign
id|console_drivers
suffix:semicolon
id|con
suffix:semicolon
id|con
op_assign
id|con-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
id|con-&gt;flags
op_amp
id|CON_ENABLED
)paren
op_logical_and
id|con-&gt;write
)paren
id|con
op_member_access_from_pointer
id|write
c_func
(paren
id|con
comma
op_amp
id|LOG_BUF
c_func
(paren
id|start
)paren
comma
id|end
op_minus
id|start
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write out chars from start to end - 1 inclusive&n; */
DECL|function|_call_console_drivers
r_static
r_void
id|_call_console_drivers
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|msg_log_level
)paren
(brace
r_if
c_cond
(paren
id|msg_log_level
OL
id|console_loglevel
op_logical_and
id|console_drivers
op_logical_and
id|start
op_ne
id|end
)paren
(brace
r_if
c_cond
(paren
(paren
id|start
op_amp
id|LOG_BUF_MASK
)paren
OG
(paren
id|end
op_amp
id|LOG_BUF_MASK
)paren
)paren
(brace
multiline_comment|/* wrapped write */
id|__call_console_drivers
c_func
(paren
id|start
op_amp
id|LOG_BUF_MASK
comma
id|LOG_BUF_LEN
)paren
suffix:semicolon
id|__call_console_drivers
c_func
(paren
l_int|0
comma
id|end
op_amp
id|LOG_BUF_MASK
)paren
suffix:semicolon
)brace
r_else
(brace
id|__call_console_drivers
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Call the console drivers, asking them to write out&n; * log_buf[start] to log_buf[end - 1].&n; * The console_sem must be held.&n; */
DECL|function|call_console_drivers
r_static
r_void
id|call_console_drivers
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
r_int
id|cur_index
comma
id|start_print
suffix:semicolon
r_static
r_int
id|msg_level
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
(paren
id|start
op_minus
id|end
)paren
)paren
OG
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|cur_index
op_assign
id|start
suffix:semicolon
id|start_print
op_assign
id|start
suffix:semicolon
r_while
c_loop
(paren
id|cur_index
op_ne
id|end
)paren
(brace
r_if
c_cond
(paren
id|msg_level
OL
l_int|0
op_logical_and
(paren
(paren
id|end
op_minus
id|cur_index
)paren
OG
l_int|2
)paren
op_logical_and
id|LOG_BUF
c_func
(paren
id|cur_index
op_plus
l_int|0
)paren
op_eq
l_char|&squot;&lt;&squot;
op_logical_and
id|LOG_BUF
c_func
(paren
id|cur_index
op_plus
l_int|1
)paren
op_ge
l_char|&squot;0&squot;
op_logical_and
id|LOG_BUF
c_func
(paren
id|cur_index
op_plus
l_int|1
)paren
op_le
l_char|&squot;7&squot;
op_logical_and
id|LOG_BUF
c_func
(paren
id|cur_index
op_plus
l_int|2
)paren
op_eq
l_char|&squot;&gt;&squot;
)paren
(brace
id|msg_level
op_assign
id|LOG_BUF
c_func
(paren
id|cur_index
op_plus
l_int|1
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|cur_index
op_add_assign
l_int|3
suffix:semicolon
id|start_print
op_assign
id|cur_index
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cur_index
op_ne
id|end
)paren
(brace
r_char
id|c
op_assign
id|LOG_BUF
c_func
(paren
id|cur_index
)paren
suffix:semicolon
id|cur_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_if
c_cond
(paren
id|msg_level
OL
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * printk() has already given us loglevel tags in&n;&t;&t;&t;&t;&t; * the buffer.  This code is here in case the&n;&t;&t;&t;&t;&t; * log buffer has wrapped right round and scribbled&n;&t;&t;&t;&t;&t; * on those tags&n;&t;&t;&t;&t;&t; */
id|msg_level
op_assign
id|default_message_loglevel
suffix:semicolon
)brace
id|_call_console_drivers
c_func
(paren
id|start_print
comma
id|cur_index
comma
id|msg_level
)paren
suffix:semicolon
id|msg_level
op_assign
op_minus
l_int|1
suffix:semicolon
id|start_print
op_assign
id|cur_index
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|_call_console_drivers
c_func
(paren
id|start_print
comma
id|end
comma
id|msg_level
)paren
suffix:semicolon
)brace
DECL|function|emit_log_char
r_static
r_void
id|emit_log_char
c_func
(paren
r_char
id|c
)paren
(brace
id|LOG_BUF
c_func
(paren
id|log_end
)paren
op_assign
id|c
suffix:semicolon
id|log_end
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|log_end
op_minus
id|log_start
OG
id|LOG_BUF_LEN
)paren
id|log_start
op_assign
id|log_end
op_minus
id|LOG_BUF_LEN
suffix:semicolon
r_if
c_cond
(paren
id|log_end
op_minus
id|con_start
OG
id|LOG_BUF_LEN
)paren
id|con_start
op_assign
id|log_end
op_minus
id|LOG_BUF_LEN
suffix:semicolon
r_if
c_cond
(paren
id|logged_chars
OL
id|LOG_BUF_LEN
)paren
id|logged_chars
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * This is printk.  It can be called from any context.  We want it to work.&n; * &n; * We try to grab the console_sem.  If we succeed, it&squot;s easy - we log the output and&n; * call the console drivers.  If we fail to get the semaphore we place the output&n; * into the log buffer and return.  The current holder of the console_sem will&n; * notice the new output in release_console_sem() and will send it to the&n; * consoles before releasing the semaphore.&n; *&n; * One effect of this deferred printing is that code which calls printk() and&n; * then changes console_loglevel may break. This is because console_loglevel&n; * is inspected when the actual printing occurs.&n; */
DECL|function|printk
id|asmlinkage
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
(brace
id|va_list
id|args
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|printed_len
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_static
r_char
id|printk_buf
(braket
l_int|1024
)braket
suffix:semicolon
r_static
r_int
id|log_level_unknown
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|oops_in_progress
)paren
(brace
multiline_comment|/* If a crash is occurring, make sure we can&squot;t deadlock */
id|spin_lock_init
c_func
(paren
op_amp
id|logbuf_lock
)paren
suffix:semicolon
multiline_comment|/* And make sure that we print immediately */
id|init_MUTEX
c_func
(paren
op_amp
id|console_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* This stops the holder of console_sem just where we want him */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Emit the output into the temporary buffer */
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|printed_len
op_assign
id|vsnprintf
c_func
(paren
id|printk_buf
comma
r_sizeof
(paren
id|printk_buf
)paren
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Copy the output into log_buf.  If the caller didn&squot;t provide&n;&t; * appropriate log level tags, we insert them here&n;&t; */
r_for
c_loop
(paren
id|p
op_assign
id|printk_buf
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|log_level_unknown
)paren
(brace
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_ne
l_char|&squot;&lt;&squot;
op_logical_or
id|p
(braket
l_int|1
)braket
template_param
l_char|&squot;7&squot;
op_logical_or
id|p
(braket
l_int|2
)braket
op_ne
l_char|&squot;&gt;&squot;
)paren
(brace
id|emit_log_char
c_func
(paren
l_char|&squot;&lt;&squot;
)paren
suffix:semicolon
id|emit_log_char
c_func
(paren
id|default_message_loglevel
op_plus
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|emit_log_char
c_func
(paren
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
)brace
id|log_level_unknown
op_assign
l_int|0
suffix:semicolon
)brace
id|emit_log_char
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|log_level_unknown
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|down_trylock
c_func
(paren
op_amp
id|console_sem
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We own the drivers.  We can drop the spinlock and let&n;&t;&t; * release_console_sem() print the text&n;&t;&t; */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
id|console_may_schedule
op_assign
l_int|0
suffix:semicolon
id|release_console_sem
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Someone else owns the drivers.  We drop the spinlock, which&n;&t;&t; * allows the semaphore holder to proceed and to call the&n;&t;&t; * console drivers with the output which we just produced.&n;&t;&t; */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
id|printed_len
suffix:semicolon
)brace
DECL|variable|printk
id|EXPORT_SYMBOL
c_func
(paren
id|printk
)paren
suffix:semicolon
multiline_comment|/**&n; * acquire_console_sem - lock the console system for exclusive use.&n; *&n; * Acquires a semaphore which guarantees that the caller has&n; * exclusive access to the console system and the console_drivers list.&n; *&n; * Can sleep, returns nothing.&n; */
DECL|function|acquire_console_sem
r_void
id|acquire_console_sem
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|console_sem
)paren
suffix:semicolon
id|console_may_schedule
op_assign
l_int|1
suffix:semicolon
)brace
DECL|variable|acquire_console_sem
id|EXPORT_SYMBOL
c_func
(paren
id|acquire_console_sem
)paren
suffix:semicolon
multiline_comment|/**&n; * release_console_sem - unlock the console system&n; *&n; * Releases the semaphore which the caller holds on the console system&n; * and the console driver list.&n; *&n; * While the semaphore was held, console output may have been buffered&n; * by printk().  If this is the case, release_console_sem() emits&n; * the output prior to releasing the semaphore.&n; *&n; * If there is output waiting for klogd, we wake it up.&n; *&n; * release_console_sem() may be called from any context.&n; */
DECL|function|release_console_sem
r_void
id|release_console_sem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|_con_start
comma
id|_log_end
suffix:semicolon
r_int
r_int
id|must_wake_klogd
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
id|must_wake_klogd
op_or_assign
id|log_start
op_minus
id|log_end
suffix:semicolon
r_if
c_cond
(paren
id|con_start
op_eq
id|log_end
)paren
r_break
suffix:semicolon
multiline_comment|/* Nothing to print */
id|_con_start
op_assign
id|con_start
suffix:semicolon
id|_log_end
op_assign
id|log_end
suffix:semicolon
id|con_start
op_assign
id|log_end
suffix:semicolon
multiline_comment|/* Flush */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
id|call_console_drivers
c_func
(paren
id|_con_start
comma
id|_log_end
)paren
suffix:semicolon
)brace
id|console_may_schedule
op_assign
l_int|0
suffix:semicolon
id|up
c_func
(paren
op_amp
id|console_sem
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|must_wake_klogd
op_logical_and
op_logical_neg
id|oops_in_progress
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|log_wait
)paren
suffix:semicolon
)brace
multiline_comment|/** console_conditional_schedule - yield the CPU if required&n; *&n; * If the console code is currently allowed to sleep, and&n; * if this CPU should yield the CPU to another task, do&n; * so here.&n; *&n; * Must be called within acquire_console_sem().&n; */
DECL|function|console_conditional_schedule
r_void
id|console_conditional_schedule
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|console_may_schedule
op_logical_and
id|current-&gt;need_resched
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|console_print
r_void
id|console_print
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;%s&quot;
comma
id|s
)paren
suffix:semicolon
)brace
DECL|variable|console_print
id|EXPORT_SYMBOL
c_func
(paren
id|console_print
)paren
suffix:semicolon
DECL|function|console_unblank
r_void
id|console_unblank
c_func
(paren
r_void
)paren
(brace
r_struct
id|console
op_star
id|c
suffix:semicolon
id|acquire_console_sem
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
id|console_drivers
suffix:semicolon
id|c
op_ne
l_int|NULL
suffix:semicolon
id|c
op_assign
id|c-&gt;next
)paren
r_if
c_cond
(paren
(paren
id|c-&gt;flags
op_amp
id|CON_ENABLED
)paren
op_logical_and
id|c-&gt;unblank
)paren
id|c
op_member_access_from_pointer
id|unblank
c_func
(paren
)paren
suffix:semicolon
id|release_console_sem
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|console_unblank
id|EXPORT_SYMBOL
c_func
(paren
id|console_unblank
)paren
suffix:semicolon
multiline_comment|/*&n; * The console driver calls this routine during kernel initialization&n; * to register the console printing procedure with printk() and to&n; * print any messages that were printed by the kernel before the&n; * console driver was initialized.&n; */
DECL|function|register_console
r_void
id|register_console
c_func
(paren
r_struct
id|console
op_star
id|console
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; *&t;See if we want to use this console driver. If we&n;&t; *&t;didn&squot;t select a console we take the first one&n;&t; *&t;that registers here.&n;&t; */
r_if
c_cond
(paren
id|preferred_console
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|console-&gt;index
OL
l_int|0
)paren
id|console-&gt;index
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|console-&gt;setup
op_eq
l_int|NULL
op_logical_or
id|console
op_member_access_from_pointer
id|setup
c_func
(paren
id|console
comma
l_int|NULL
)paren
op_eq
l_int|0
)paren
(brace
id|console-&gt;flags
op_or_assign
id|CON_ENABLED
op_or
id|CON_CONSDEV
suffix:semicolon
id|preferred_console
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;See if this console matches one we selected on&n;&t; *&t;the command line.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CMDLINECONSOLES
op_logical_and
id|console_cmdline
(braket
id|i
)braket
dot
id|name
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|console_cmdline
(braket
id|i
)braket
dot
id|name
comma
id|console-&gt;name
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|console-&gt;index
op_ge
l_int|0
op_logical_and
id|console-&gt;index
op_ne
id|console_cmdline
(braket
id|i
)braket
dot
id|index
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|console-&gt;index
OL
l_int|0
)paren
id|console-&gt;index
op_assign
id|console_cmdline
(braket
id|i
)braket
dot
id|index
suffix:semicolon
r_if
c_cond
(paren
id|console-&gt;setup
op_logical_and
id|console
op_member_access_from_pointer
id|setup
c_func
(paren
id|console
comma
id|console_cmdline
(braket
id|i
)braket
dot
id|options
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|console-&gt;flags
op_or_assign
id|CON_ENABLED
suffix:semicolon
id|console-&gt;index
op_assign
id|console_cmdline
(braket
id|i
)braket
dot
id|index
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|preferred_console
)paren
id|console-&gt;flags
op_or_assign
id|CON_CONSDEV
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|console-&gt;flags
op_amp
id|CON_ENABLED
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Put this console in the list - keep the&n;&t; *&t;preferred driver at the head of the list.&n;&t; */
id|acquire_console_sem
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|console-&gt;flags
op_amp
id|CON_CONSDEV
)paren
op_logical_or
id|console_drivers
op_eq
l_int|NULL
)paren
(brace
id|console-&gt;next
op_assign
id|console_drivers
suffix:semicolon
id|console_drivers
op_assign
id|console
suffix:semicolon
)brace
r_else
(brace
id|console-&gt;next
op_assign
id|console_drivers-&gt;next
suffix:semicolon
id|console_drivers-&gt;next
op_assign
id|console
suffix:semicolon
)brace
r_if
c_cond
(paren
id|console-&gt;flags
op_amp
id|CON_PRINTBUFFER
)paren
(brace
multiline_comment|/*&n;&t;&t; * release_cosole_sem() will print out the buffered messages for us.&n;&t;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
id|con_start
op_assign
id|log_start
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|logbuf_lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|release_console_sem
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|register_console
id|EXPORT_SYMBOL
c_func
(paren
id|register_console
)paren
suffix:semicolon
DECL|function|unregister_console
r_int
id|unregister_console
c_func
(paren
r_struct
id|console
op_star
id|console
)paren
(brace
r_struct
id|console
op_star
id|a
comma
op_star
id|b
suffix:semicolon
r_int
id|res
op_assign
l_int|1
suffix:semicolon
id|acquire_console_sem
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|console_drivers
op_eq
id|console
)paren
(brace
id|console_drivers
op_assign
id|console-&gt;next
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|a
op_assign
id|console_drivers-&gt;next
comma
id|b
op_assign
id|console_drivers
suffix:semicolon
id|a
suffix:semicolon
id|b
op_assign
id|a
comma
id|a
op_assign
id|b-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|a
op_eq
id|console
)paren
(brace
id|b-&gt;next
op_assign
id|a-&gt;next
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* If last console is removed, we re-enable picking the first&n;&t; * one that gets registered. Without that, pmac early boot console&n;&t; * would prevent fbcon from taking over.&n;&t; */
r_if
c_cond
(paren
id|console_drivers
op_eq
l_int|NULL
)paren
id|preferred_console
op_assign
op_minus
l_int|1
suffix:semicolon
id|release_console_sem
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|unregister_console
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_console
)paren
suffix:semicolon
multiline_comment|/**&n; * tty_write_message - write a message to a certain tty, not just the console.&n; *&n; * This is used for messages that need to be redirected to a specific tty.&n; * We don&squot;t put it into the syslog queue right now maybe in the future if&n; * really needed.&n; */
DECL|function|tty_write_message
r_void
id|tty_write_message
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_char
op_star
id|msg
)paren
(brace
r_if
c_cond
(paren
id|tty
op_logical_and
id|tty-&gt;driver.write
)paren
id|tty-&gt;driver
dot
id|write
c_func
(paren
id|tty
comma
l_int|0
comma
id|msg
comma
id|strlen
c_func
(paren
id|msg
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
