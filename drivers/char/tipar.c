multiline_comment|/* Hey EMACS -*- linux-c -*-&n; *&n; * tipar - low level driver for handling a parallel link cable designed&n; * for Texas Instruments graphing calculators (http://lpg.ticalc.org).&n; * A part of the TiLP project.&n; *&n; * Copyright (C) 2000-2002, Romain Lievin &lt;roms@lpg.ticalc.org&gt;&n; * under the terms of the GNU General Public License.&n; *&n; * Various fixes &amp; clean-up from the Linux Kernel Mailing List&n; * (Alan Cox, Richard B. Johnson, Christoph Hellwig).&n; */
multiline_comment|/* This driver should, in theory, work with any parallel port that has an&n; * appropriate low-level driver; all I/O is done through the parport&n; * abstraction layer.&n; *&n; * If this driver is built into the kernel, you can configure it using the&n; * kernel command-line.  For example:&n; *&n; *      tipar=timeout,delay       (set timeout and delay)&n; *&n; * If the driver is loaded as a module, similar functionality is available&n; * using module parameters.  The equivalent of the above commands would be:&n; *&n; *      # insmod tipar timeout=15 delay=10&n; */
multiline_comment|/* COMPATIBILITY WITH OLD KERNELS&n; *&n; * Usually, parallel cables were bound to ports at&n; * particular I/O addresses, as follows:&n; *&n; *      tipar0             0x378&n; *      tipar1             0x278&n; *      tipar2             0x3bc&n; *&n; *&n; * This driver, by default, binds tipar devices according to parport and&n; * the minor number.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;&t;/* DevFs support */
macro_line|#include &lt;linux/parport.h&gt;&t;/* Our code depend on parport */
macro_line|#include &lt;linux/device.h&gt;
multiline_comment|/*&n; * TI definitions&n; */
macro_line|#include &lt;linux/ticable.h&gt;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;1.19&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR  &quot;Romain Lievin &lt;roms@lpg.ticalc.org&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC    &quot;Device driver for TI/PC parallel link cables&quot;
DECL|macro|DRIVER_LICENSE
mdefine_line|#define DRIVER_LICENSE &quot;GPL&quot;
DECL|macro|VERSION
mdefine_line|#define VERSION(ver,rel,seq) (((ver)&lt;&lt;16) | ((rel)&lt;&lt;8) | (seq))
macro_line|#if LINUX_VERSION_CODE &lt; VERSION(2,5,0)
DECL|macro|need_resched
macro_line|# define need_resched() (current-&gt;need_resched)
macro_line|#endif
multiline_comment|/* ----- global variables --------------------------------------------- */
DECL|struct|tipar_struct
r_struct
id|tipar_struct
(brace
DECL|member|dev
r_struct
id|pardevice
op_star
id|dev
suffix:semicolon
multiline_comment|/* Parport device entry */
)brace
suffix:semicolon
DECL|macro|PP_NO
mdefine_line|#define PP_NO 3
DECL|variable|table
r_static
r_struct
id|tipar_struct
id|table
(braket
id|PP_NO
)braket
suffix:semicolon
DECL|variable|delay
r_static
r_int
id|delay
op_assign
id|IO_DELAY
suffix:semicolon
multiline_comment|/* inter-bit delay in microseconds */
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
id|TIMAXTIME
suffix:semicolon
multiline_comment|/* timeout in tenth of seconds     */
DECL|variable|tp_count
r_static
r_int
r_int
id|tp_count
suffix:semicolon
multiline_comment|/* tipar count */
DECL|variable|opened
r_static
r_int
r_int
id|opened
suffix:semicolon
multiline_comment|/* opened devices */
DECL|variable|tipar_class
r_static
r_struct
id|class_simple
op_star
id|tipar_class
suffix:semicolon
multiline_comment|/* --- macros for parport access -------------------------------------- */
DECL|macro|r_dtr
mdefine_line|#define r_dtr(x)        (parport_read_data(table[(x)].dev-&gt;port))
DECL|macro|r_str
mdefine_line|#define r_str(x)        (parport_read_status(table[(x)].dev-&gt;port))
DECL|macro|w_ctr
mdefine_line|#define w_ctr(x,y)      (parport_write_control(table[(x)].dev-&gt;port, (y)))
DECL|macro|w_dtr
mdefine_line|#define w_dtr(x,y)      (parport_write_data(table[(x)].dev-&gt;port, (y)))
multiline_comment|/* --- setting states on the D-bus with the right timing: ------------- */
r_static
r_inline
r_void
DECL|function|outbyte
id|outbyte
c_func
(paren
r_int
id|value
comma
r_int
id|minor
)paren
(brace
id|w_dtr
c_func
(paren
id|minor
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|inbyte
id|inbyte
c_func
(paren
r_int
id|minor
)paren
(brace
r_return
(paren
id|r_str
c_func
(paren
id|minor
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|init_ti_parallel
id|init_ti_parallel
c_func
(paren
r_int
id|minor
)paren
(brace
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
)brace
multiline_comment|/* ----- global defines ----------------------------------------------- */
DECL|macro|START
mdefine_line|#define START(x) { x = jiffies + (HZ * timeout) / 10; }
DECL|macro|WAIT
mdefine_line|#define WAIT(x)  { &bslash;&n;  if (time_before((x), jiffies)) return -1; &bslash;&n;  if (need_resched()) schedule(); }
multiline_comment|/* ----- D-bus bit-banging functions ---------------------------------- */
multiline_comment|/* D-bus protocol (45kbit/s max):&n;                    1                 0                      0&n;       _______        ______|______    __________|________    __________&n;Red  :        ________      |      ____          |        ____&n;       _        ____________|________      ______|__________       _____&n;White:  ________            |        ______      |          _______&n;*/
multiline_comment|/* Try to transmit a byte on the specified port (-1 if error). */
r_static
r_int
DECL|function|put_ti_parallel
id|put_ti_parallel
c_func
(paren
r_int
id|minor
comma
r_int
r_char
id|data
)paren
(brace
r_int
id|bit
suffix:semicolon
r_int
r_int
id|max
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|0
suffix:semicolon
id|bit
OL
l_int|8
suffix:semicolon
id|bit
op_increment
)paren
(brace
r_if
c_cond
(paren
id|data
op_amp
l_int|1
)paren
(brace
id|outbyte
c_func
(paren
l_int|2
comma
id|minor
)paren
suffix:semicolon
id|START
c_func
(paren
id|max
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|max
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x10
)paren
suffix:semicolon
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
id|START
c_func
(paren
id|max
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|max
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x10
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|outbyte
c_func
(paren
l_int|1
comma
id|minor
)paren
suffix:semicolon
id|START
c_func
(paren
id|max
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|max
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x20
)paren
suffix:semicolon
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
id|START
c_func
(paren
id|max
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|max
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x20
)paren
)paren
suffix:semicolon
)brace
id|data
op_rshift_assign
l_int|1
suffix:semicolon
id|udelay
c_func
(paren
id|delay
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Receive a byte on the specified port or -1 if error. */
r_static
r_int
DECL|function|get_ti_parallel
id|get_ti_parallel
c_func
(paren
r_int
id|minor
)paren
(brace
r_int
id|bit
suffix:semicolon
r_int
r_char
id|v
comma
id|data
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|max
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|0
suffix:semicolon
id|bit
OL
l_int|8
suffix:semicolon
id|bit
op_increment
)paren
(brace
id|START
c_func
(paren
id|max
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|max
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|v
op_assign
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x30
)paren
op_eq
l_int|0x30
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
l_int|0x10
)paren
(brace
id|data
op_assign
(paren
id|data
op_rshift
l_int|1
)paren
op_or
l_int|0x80
suffix:semicolon
id|outbyte
c_func
(paren
l_int|1
comma
id|minor
)paren
suffix:semicolon
id|START
c_func
(paren
id|max
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|max
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x20
)paren
)paren
suffix:semicolon
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
)brace
r_else
(brace
id|data
op_assign
id|data
op_rshift
l_int|1
suffix:semicolon
id|outbyte
c_func
(paren
l_int|2
comma
id|minor
)paren
suffix:semicolon
id|START
c_func
(paren
id|max
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|max
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x10
)paren
)paren
suffix:semicolon
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
)brace
id|udelay
c_func
(paren
id|delay
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
(paren
r_int
)paren
id|data
suffix:semicolon
)brace
multiline_comment|/* Try to detect a parallel link cable on the specified port */
r_static
r_int
DECL|function|probe_ti_parallel
id|probe_ti_parallel
c_func
(paren
r_int
id|minor
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|seq
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x20
comma
l_int|0x10
comma
l_int|0x30
)brace
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
id|outbyte
c_func
(paren
id|i
comma
id|minor
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|delay
)paren
suffix:semicolon
multiline_comment|/*printk(KERN_DEBUG &quot;Probing -&gt; %i: 0x%02x 0x%02x&bslash;n&quot;, i, data &amp; 0x30, seq[i]); */
r_if
c_cond
(paren
(paren
id|inbyte
c_func
(paren
id|minor
)paren
op_amp
l_int|0x30
)paren
op_ne
id|seq
(braket
id|i
)braket
)paren
(brace
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|outbyte
c_func
(paren
l_int|3
comma
id|minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----- kernel module functions--------------------------------------- */
r_static
r_int
DECL|function|tipar_open
id|tipar_open
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
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
op_minus
id|TIPAR_MINOR
suffix:semicolon
r_if
c_cond
(paren
id|minor
OG
id|tp_count
op_minus
l_int|1
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|minor
comma
op_amp
id|opened
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|parport_claim_or_block
c_func
(paren
id|table
(braket
id|minor
)braket
dot
id|dev
)paren
suffix:semicolon
id|init_ti_parallel
c_func
(paren
id|minor
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|table
(braket
id|minor
)braket
dot
id|dev
)paren
suffix:semicolon
r_return
id|nonseekable_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tipar_close
id|tipar_close
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
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
op_minus
id|TIPAR_MINOR
suffix:semicolon
r_if
c_cond
(paren
id|minor
OG
id|tp_count
op_minus
l_int|1
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|clear_bit
c_func
(paren
id|minor
comma
op_amp
id|opened
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|tipar_write
id|tipar_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
id|ppos
)paren
(brace
r_int
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
op_minus
id|TIPAR_MINOR
suffix:semicolon
id|ssize_t
id|n
suffix:semicolon
id|parport_claim_or_block
c_func
(paren
id|table
(braket
id|minor
)braket
dot
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|count
suffix:semicolon
id|n
op_increment
)paren
(brace
r_int
r_char
id|b
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|b
comma
id|buf
op_plus
id|n
)paren
)paren
(brace
id|n
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
id|put_ti_parallel
c_func
(paren
id|minor
comma
id|b
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|init_ti_parallel
c_func
(paren
id|minor
)paren
suffix:semicolon
id|n
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|parport_release
c_func
(paren
id|table
(braket
id|minor
)braket
dot
id|dev
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|tipar_read
id|tipar_read
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
id|ppos
)paren
(brace
r_int
id|b
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
op_minus
id|TIPAR_MINOR
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|parport_claim_or_block
c_func
(paren
id|table
(braket
id|minor
)braket
dot
id|dev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|n
OL
id|count
)paren
(brace
id|b
op_assign
id|get_ti_parallel
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_eq
op_minus
l_int|1
)paren
(brace
id|init_ti_parallel
c_func
(paren
id|minor
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|b
comma
id|buf
op_plus
id|n
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
id|retval
op_assign
op_increment
id|n
suffix:semicolon
)brace
multiline_comment|/* Non-blocking mode : try again ! */
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Signal pending, try again ! */
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
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|parport_release
c_func
(paren
id|table
(braket
id|minor
)braket
dot
id|dev
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_int
DECL|function|tipar_ioctl
id|tipar_ioctl
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
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|IOCTL_TIPAR_DELAY
suffix:colon
id|delay
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
singleline_comment|//get_user(delay, &amp;arg);
r_break
suffix:semicolon
r_case
id|IOCTL_TIPAR_TIMEOUT
suffix:colon
r_if
c_cond
(paren
id|arg
op_ne
l_int|0
)paren
id|timeout
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
r_else
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|ENOTTY
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* ----- kernel module registering ------------------------------------ */
DECL|variable|tipar_fops
r_static
r_struct
id|file_operations
id|tipar_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|tipar_read
comma
dot
id|write
op_assign
id|tipar_write
comma
dot
id|ioctl
op_assign
id|tipar_ioctl
comma
dot
id|open
op_assign
id|tipar_open
comma
dot
id|release
op_assign
id|tipar_close
comma
)brace
suffix:semicolon
multiline_comment|/* --- initialisation code ------------------------------------- */
macro_line|#ifndef MODULE
multiline_comment|/*      You must set these - there is no sane way to probe for this cable.&n; *      You can use &squot;tipar=timeout,delay&squot; to set these now. */
r_static
r_int
id|__init
DECL|function|tipar_setup
id|tipar_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|ints
(braket
l_int|2
)braket
suffix:semicolon
id|str
op_assign
id|get_options
c_func
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|1
)braket
op_ne
l_int|0
)paren
id|timeout
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;tipar: wrong timeout value (0), using default value instead.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|1
)paren
(brace
id|delay
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Register our module into parport.&n; * Pass also 2 callbacks functions to parport: a pre-emptive function and an&n; * interrupt handler function (unused).&n; * Display a message such &quot;tipar0: using parport0 (polling)&quot;.&n; */
r_static
r_int
DECL|function|tipar_register
id|tipar_register
c_func
(paren
r_int
id|nr
comma
r_struct
id|parport
op_star
id|port
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Register our module into parport */
id|table
(braket
id|nr
)braket
dot
id|dev
op_assign
id|parport_register_device
c_func
(paren
id|port
comma
l_string|&quot;tipar&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|table
(braket
id|nr
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|table
(braket
id|nr
)braket
dot
id|dev
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|class_simple_device_add
c_func
(paren
id|tipar_class
comma
id|MKDEV
c_func
(paren
id|TIPAR_MAJOR
comma
id|TIPAR_MINOR
op_plus
id|nr
)paren
comma
l_int|NULL
comma
l_string|&quot;par%d&quot;
comma
id|nr
)paren
suffix:semicolon
multiline_comment|/* Use devfs, tree: /dev/ticables/par/[0..2] */
id|err
op_assign
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|TIPAR_MAJOR
comma
id|TIPAR_MINOR
op_plus
id|nr
)paren
comma
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
l_string|&quot;ticables/par/%d&quot;
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_class
suffix:semicolon
multiline_comment|/* Display informations */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;tipar%d: using %s (%s).&bslash;n&quot;
comma
id|nr
comma
id|port-&gt;name
comma
(paren
id|port-&gt;irq
op_eq
id|PARPORT_IRQ_NONE
)paren
ques
c_cond
l_string|&quot;polling&quot;
suffix:colon
l_string|&quot;interrupt-driven&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|probe_ti_parallel
c_func
(paren
id|nr
)paren
op_ne
op_minus
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;tipar%d: link cable found !&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;tipar%d: link cable not found.&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_class
suffix:colon
id|class_simple_device_remove
c_func
(paren
id|MKDEV
c_func
(paren
id|TIPAR_MAJOR
comma
id|TIPAR_MINOR
op_plus
id|nr
)paren
)paren
suffix:semicolon
id|class_simple_destroy
c_func
(paren
id|tipar_class
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
r_static
r_void
DECL|function|tipar_attach
id|tipar_attach
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|tp_count
op_eq
id|PP_NO
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tipar: ignoring parallel port (max. %d)&bslash;n&quot;
comma
id|PP_NO
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tipar_register
c_func
(paren
id|tp_count
comma
id|port
)paren
)paren
id|tp_count
op_increment
suffix:semicolon
)brace
r_static
r_void
DECL|function|tipar_detach
id|tipar_detach
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
multiline_comment|/* Nothing to do */
)brace
DECL|variable|tipar_driver
r_static
r_struct
id|parport_driver
id|tipar_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tipar&quot;
comma
dot
id|attach
op_assign
id|tipar_attach
comma
dot
id|detach
op_assign
id|tipar_detach
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|tipar_init_module
id|tipar_init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tipar: parallel link cable driver, version %s&bslash;n&quot;
comma
id|DRIVER_VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|TIPAR_MAJOR
comma
l_string|&quot;tipar&quot;
comma
op_amp
id|tipar_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tipar: unable to get major %d&bslash;n&quot;
comma
id|TIPAR_MAJOR
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Use devfs with tree: /dev/ticables/par/[0..2] */
id|devfs_mk_dir
c_func
(paren
l_string|&quot;ticables/par&quot;
)paren
suffix:semicolon
id|tipar_class
op_assign
id|class_simple_create
c_func
(paren
id|THIS_MODULE
comma
l_string|&quot;ticables&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|tipar_class
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|tipar_class
)paren
suffix:semicolon
r_goto
id|out_chrdev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parport_register_driver
c_func
(paren
op_amp
id|tipar_driver
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tipar: unable to register with parport&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_chrdev
suffix:colon
id|unregister_chrdev
c_func
(paren
id|TIPAR_MAJOR
comma
l_string|&quot;tipar&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
r_void
id|__exit
DECL|function|tipar_cleanup_module
id|tipar_cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Unregistering module */
id|parport_unregister_driver
c_func
(paren
op_amp
id|tipar_driver
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|TIPAR_MAJOR
comma
l_string|&quot;tipar&quot;
)paren
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
id|PP_NO
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|table
(braket
id|i
)braket
dot
id|dev
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|table
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
id|class_simple_device_remove
c_func
(paren
id|MKDEV
c_func
(paren
id|TIPAR_MAJOR
comma
id|i
)paren
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;ticables/par/%d&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|class_simple_destroy
c_func
(paren
id|tipar_class
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;ticables/par&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tipar: module unloaded !&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
id|__setup
c_func
(paren
l_string|&quot;tipar=&quot;
comma
id|tipar_setup
)paren
suffix:semicolon
DECL|variable|tipar_init_module
id|module_init
c_func
(paren
id|tipar_init_module
)paren
suffix:semicolon
DECL|variable|tipar_cleanup_module
id|module_exit
c_func
(paren
id|tipar_cleanup_module
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
DECL|variable|DRIVER_LICENSE
id|MODULE_LICENSE
c_func
(paren
id|DRIVER_LICENSE
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|timeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|timeout
comma
l_string|&quot;Timeout (default=1.5 seconds)&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|delay
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|delay
comma
l_string|&quot;Inter-bit delay (default=10 microseconds)&quot;
)paren
suffix:semicolon
eof
