multiline_comment|/*                                              -*- linux-c -*-&n; * dtlk.c - DoubleTalk PC driver for Linux&n; *&n; * Original author: Chris Pallotta &lt;chris@allmedia.com&gt;&n; * Current maintainer: Jim Van Zandt &lt;jrv@vanzandt.mv.com&gt;&n; * &n; * 2000-03-18 Jim Van Zandt: Fix polling.&n; *  Eliminate dtlk_timer_active flag and separate dtlk_stop_timer&n; *  function.  Don&squot;t restart timer in dtlk_timer_tick.  Restart timer&n; *  in dtlk_poll after every poll.  dtlk_poll returns mask (duh).&n; *  Eliminate unused function dtlk_write_byte.  Misc. code cleanups.&n; */
multiline_comment|/* This driver is for the DoubleTalk PC, a speech synthesizer&n;   manufactured by RC Systems (http://www.rcsys.com/).  It was written&n;   based on documentation in their User&squot;s Manual file and Developer&squot;s&n;   Tools disk.&n;&n;   The DoubleTalk PC contains four voice synthesizers: text-to-speech&n;   (TTS), linear predictive coding (LPC), PCM/ADPCM, and CVSD.  It&n;   also has a tone generator.  Output data for LPC are written to the&n;   LPC port, and output data for the other modes are written to the&n;   TTS port.&n;&n;   Two kinds of data can be read from the DoubleTalk: status&n;   information (in response to the &quot;&bslash;001?&quot; interrogation command) is&n;   read from the TTS port, and index markers (which mark the progress&n;   of the speech) are read from the LPC port.  Not all models of the&n;   DoubleTalk PC implement index markers.  Both the TTS and LPC ports&n;   can also display status flags.&n;&n;   The DoubleTalk PC generates no interrupts.&n;&n;   These characteristics are mapped into the Unix stream I/O model as&n;   follows:&n;&n;   &quot;write&quot; sends bytes to the TTS port.  It is the responsibility of&n;   the user program to switch modes among TTS, PCM/ADPCM, and CVSD.&n;   This driver was written for use with the text-to-speech&n;   synthesizer.  If LPC output is needed some day, other minor device&n;   numbers can be used to select among output modes.&n;&n;   &quot;read&quot; gets index markers from the LPC port.  If the device does&n;   not implement index markers, the read will fail with error EINVAL.&n;&n;   Status information is available using the DTLK_INTERROGATE ioctl.&n;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|KERNEL
mdefine_line|#define KERNEL
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* for verify_area */
macro_line|#include &lt;linux/errno.h&gt;&t;/* for -EBUSY */
macro_line|#include &lt;linux/ioport.h&gt;&t;/* for request_region */
macro_line|#include &lt;linux/delay.h&gt;&t;/* for loops_per_jiffy */
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* for inb_p, outb_p, inb, outb, etc. */
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* for get_user, etc. */
macro_line|#include &lt;linux/wait.h&gt;&t;&t;/* for wait_queue */
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* for __init, module_{init,exit} */
macro_line|#include &lt;linux/poll.h&gt;&t;&t;/* for POLLIN, etc. */
macro_line|#include &lt;linux/dtlk.h&gt;&t;&t;/* local header file for DoubleTalk values */
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#ifdef TRACING
DECL|macro|TRACE_TEXT
mdefine_line|#define TRACE_TEXT(str) printk(str);
DECL|macro|TRACE_RET
mdefine_line|#define TRACE_RET printk(&quot;)&quot;)
macro_line|#else&t;&t;&t;&t;/* !TRACING */
DECL|macro|TRACE_TEXT
mdefine_line|#define TRACE_TEXT(str) ((void) 0)
DECL|macro|TRACE_RET
mdefine_line|#define TRACE_RET ((void) 0)
macro_line|#endif&t;&t;&t;&t;/* TRACING */
DECL|variable|dtlk_major
r_static
r_int
id|dtlk_major
suffix:semicolon
DECL|variable|dtlk_port_lpc
r_static
r_int
id|dtlk_port_lpc
suffix:semicolon
DECL|variable|dtlk_port_tts
r_static
r_int
id|dtlk_port_tts
suffix:semicolon
DECL|variable|dtlk_busy
r_static
r_int
id|dtlk_busy
suffix:semicolon
DECL|variable|dtlk_has_indexing
r_static
r_int
id|dtlk_has_indexing
suffix:semicolon
DECL|variable|dtlk_portlist
r_static
r_int
r_int
id|dtlk_portlist
(braket
)braket
op_assign
(brace
l_int|0x25e
comma
l_int|0x29e
comma
l_int|0x2de
comma
l_int|0x31e
comma
l_int|0x35e
comma
l_int|0x39e
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|dtlk_process_list
r_static
id|wait_queue_head_t
id|dtlk_process_list
suffix:semicolon
DECL|variable|dtlk_timer
r_static
r_struct
id|timer_list
id|dtlk_timer
suffix:semicolon
multiline_comment|/* prototypes for file_operations struct */
r_static
id|ssize_t
id|dtlk_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
id|ssize_t
id|dtlk_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
r_int
r_int
id|dtlk_poll
c_func
(paren
r_struct
id|file
op_star
comma
id|poll_table
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtlk_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtlk_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtlk_ioctl
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
suffix:semicolon
DECL|variable|dtlk_fops
r_static
r_struct
id|file_operations
id|dtlk_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|dtlk_read
comma
dot
id|write
op_assign
id|dtlk_write
comma
dot
id|poll
op_assign
id|dtlk_poll
comma
dot
id|ioctl
op_assign
id|dtlk_ioctl
comma
dot
id|open
op_assign
id|dtlk_open
comma
dot
id|release
op_assign
id|dtlk_release
comma
)brace
suffix:semicolon
multiline_comment|/* local prototypes */
r_static
r_void
id|dtlk_delay
c_func
(paren
r_int
id|ms
)paren
suffix:semicolon
r_static
r_int
id|dtlk_dev_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_struct
id|dtlk_settings
op_star
id|dtlk_interrogate
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|dtlk_readable
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_char
id|dtlk_read_lpc
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_char
id|dtlk_read_tts
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|dtlk_writeable
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_char
id|dtlk_write_bytes
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
id|n
)paren
suffix:semicolon
r_static
r_char
id|dtlk_write_tts
c_func
(paren
r_char
)paren
suffix:semicolon
multiline_comment|/*&n;   static void dtlk_handle_error(char, char, unsigned int);&n; */
r_static
r_void
id|dtlk_timer_tick
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|function|dtlk_read
r_static
id|ssize_t
id|dtlk_read
c_func
(paren
r_struct
id|file
op_star
id|file
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
r_int
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_char
id|ch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|retries
suffix:semicolon
multiline_comment|/* Can&squot;t seek (pread) on the DoubleTalk.  */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_read&quot;
)paren
suffix:semicolon
multiline_comment|/*  printk(&quot;DoubleTalk PC - dtlk_read()&bslash;n&quot;); */
r_if
c_cond
(paren
id|minor
op_ne
id|DTLK_MINOR
op_logical_or
op_logical_neg
id|dtlk_has_indexing
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|retries
op_assign
l_int|0
suffix:semicolon
id|retries
OL
id|loops_per_jiffy
suffix:semicolon
id|retries
op_increment
)paren
(brace
r_while
c_loop
(paren
id|i
OL
id|count
op_logical_and
id|dtlk_readable
c_func
(paren
)paren
)paren
(brace
id|ch
op_assign
id|dtlk_read_lpc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*        printk(&quot;dtlk_read() reads 0x%02x&bslash;n&quot;, ch); */
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|ch
comma
id|buf
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_break
suffix:semicolon
id|dtlk_delay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retries
op_eq
id|loops_per_jiffy
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dtlk_read times out&bslash;n&quot;
)paren
suffix:semicolon
id|TRACE_RET
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|function|dtlk_write
r_static
id|ssize_t
id|dtlk_write
c_func
(paren
r_struct
id|file
op_star
id|file
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
r_int
id|i
op_assign
l_int|0
comma
id|retries
op_assign
l_int|0
comma
id|ch
suffix:semicolon
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_write&quot;
)paren
suffix:semicolon
macro_line|#ifdef TRACING
id|printk
c_func
(paren
l_string|&quot; &bslash;&quot;&quot;
)paren
suffix:semicolon
(brace
r_int
id|i
comma
id|ch
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ch
comma
id|buf
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
l_char|&squot; &squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;~&squot;
)paren
id|printk
c_func
(paren
l_string|&quot;%c&quot;
comma
id|ch
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;&bslash;%03o&quot;
comma
id|ch
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;&quot;&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Can&squot;t seek (pwrite) on the DoubleTalk.  */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_if
c_cond
(paren
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
op_ne
id|DTLK_MINOR
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
id|i
OL
id|count
op_logical_and
op_logical_neg
id|get_user
c_func
(paren
id|ch
comma
id|buf
)paren
op_logical_and
(paren
id|ch
op_eq
id|DTLK_CLEAR
op_logical_or
id|dtlk_writeable
c_func
(paren
)paren
)paren
)paren
(brace
id|dtlk_write_tts
c_func
(paren
id|ch
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_mod
l_int|5
op_eq
l_int|0
)paren
multiline_comment|/* We yield our time until scheduled&n;&t;&t;&t;&t;   again.  This reduces the transfer&n;&t;&t;&t;&t;   rate to 500 bytes/sec, but that&squot;s&n;&t;&t;&t;&t;   still enough to keep up with the&n;&t;&t;&t;&t;   speech synthesizer. */
id|dtlk_delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* the RDY bit goes zero 2-3 usec&n;&t;&t;&t;&t;   after writing, and goes 1 again&n;&t;&t;&t;&t;   180-190 usec later.  Here, we wait&n;&t;&t;&t;&t;   up to 250 usec for the RDY bit to&n;&t;&t;&t;&t;   go nonzero. */
r_for
c_loop
(paren
id|retries
op_assign
l_int|0
suffix:semicolon
id|retries
OL
id|loops_per_jiffy
op_div
(paren
l_int|4000
op_div
id|HZ
)paren
suffix:semicolon
id|retries
op_increment
)paren
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
op_amp
id|TTS_WRITABLE
)paren
r_break
suffix:semicolon
)brace
id|retries
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|count
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_break
suffix:semicolon
id|dtlk_delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|retries
OG
l_int|10
op_star
id|HZ
)paren
(brace
multiline_comment|/* wait no more than 10 sec&n;&t;&t;&t;&t;&t;      from last write */
id|printk
c_func
(paren
l_string|&quot;dtlk: write timeout.  &quot;
l_string|&quot;inb_p(dtlk_port_tts) = 0x%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
)paren
suffix:semicolon
id|TRACE_RET
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|TRACE_RET
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|function|dtlk_poll
r_static
r_int
r_int
id|dtlk_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|expires
suffix:semicolon
id|TRACE_TEXT
c_func
(paren
l_string|&quot; dtlk_poll&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   static long int j;&n;&t;   printk(&quot;.&quot;);&n;&t;   printk(&quot;&lt;%ld&gt;&quot;, jiffies-j);&n;&t;   j=jiffies;&n;&t; */
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|dtlk_process_list
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dtlk_has_indexing
op_logical_and
id|dtlk_readable
c_func
(paren
)paren
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|dtlk_timer
)paren
suffix:semicolon
id|mask
op_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dtlk_writeable
c_func
(paren
)paren
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|dtlk_timer
)paren
suffix:semicolon
id|mask
op_or_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
)brace
multiline_comment|/* there are no exception conditions */
multiline_comment|/* There won&squot;t be any interrupts, so we set a timer instead. */
id|expires
op_assign
id|jiffies
op_plus
l_int|3
op_star
id|HZ
op_div
l_int|100
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|dtlk_timer
comma
id|expires
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|dtlk_timer_tick
r_static
r_void
id|dtlk_timer_tick
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|TRACE_TEXT
c_func
(paren
l_string|&quot; dtlk_timer_tick&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dtlk_process_list
)paren
suffix:semicolon
)brace
DECL|function|dtlk_ioctl
r_static
r_int
id|dtlk_ioctl
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
r_struct
id|dtlk_settings
op_star
id|sp
suffix:semicolon
r_char
id|portval
suffix:semicolon
id|TRACE_TEXT
c_func
(paren
l_string|&quot; dtlk_ioctl&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|DTLK_INTERROGATE
suffix:colon
id|sp
op_assign
id|dtlk_interrogate
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
(paren
r_char
op_star
)paren
id|sp
comma
r_sizeof
(paren
r_struct
id|dtlk_settings
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|DTLK_STATUS
suffix:colon
id|portval
op_assign
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|portval
comma
(paren
r_char
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
DECL|function|dtlk_open
r_static
r_int
id|dtlk_open
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
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_open&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|DTLK_MINOR
suffix:colon
r_if
c_cond
(paren
id|dtlk_busy
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
DECL|function|dtlk_release
r_static
r_int
id|dtlk_release
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
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_release&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|DTLK_MINOR
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|TRACE_RET
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|dtlk_timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtlk_init
r_static
r_int
id|__init
id|dtlk_init
c_func
(paren
r_void
)paren
(brace
id|dtlk_port_lpc
op_assign
l_int|0
suffix:semicolon
id|dtlk_port_tts
op_assign
l_int|0
suffix:semicolon
id|dtlk_busy
op_assign
l_int|0
suffix:semicolon
id|dtlk_major
op_assign
id|register_chrdev
c_func
(paren
l_int|0
comma
l_string|&quot;dtlk&quot;
comma
op_amp
id|dtlk_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dtlk_major
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DoubleTalk PC - cannot register device&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dtlk_dev_probe
c_func
(paren
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;, MAJOR %d&bslash;n&quot;
comma
id|dtlk_major
)paren
suffix:semicolon
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|dtlk_major
comma
id|DTLK_MINOR
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_string|&quot;dtlk&quot;
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dtlk_timer
)paren
suffix:semicolon
id|dtlk_timer.function
op_assign
id|dtlk_timer_tick
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dtlk_process_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtlk_cleanup
r_static
r_void
id|__exit
id|dtlk_cleanup
(paren
r_void
)paren
(brace
id|dtlk_write_bytes
c_func
(paren
l_string|&quot;goodbye&quot;
comma
l_int|8
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|5
op_star
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
multiline_comment|/* nap 0.50 sec but&n;&t;&t;&t;&t;&t;&t;   could be awakened&n;&t;&t;&t;&t;&t;&t;   earlier by&n;&t;&t;&t;&t;&t;&t;   signals... */
id|dtlk_write_tts
c_func
(paren
id|DTLK_CLEAR
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|dtlk_major
comma
l_string|&quot;dtlk&quot;
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;dtlk&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dtlk_port_lpc
comma
id|DTLK_IO_EXTENT
)paren
suffix:semicolon
)brace
DECL|variable|dtlk_init
id|module_init
c_func
(paren
id|dtlk_init
)paren
suffix:semicolon
DECL|variable|dtlk_cleanup
id|module_exit
c_func
(paren
id|dtlk_cleanup
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------ */
multiline_comment|/* sleep for ms milliseconds */
DECL|function|dtlk_delay
r_static
r_void
id|dtlk_delay
c_func
(paren
r_int
id|ms
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
id|ms
op_star
id|HZ
op_plus
l_int|1000
op_minus
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
DECL|function|dtlk_readable
r_static
r_int
id|dtlk_readable
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef TRACING
id|printk
c_func
(paren
l_string|&quot; dtlk_readable=%u@%u&quot;
comma
id|inb_p
c_func
(paren
id|dtlk_port_lpc
)paren
op_ne
l_int|0x7f
comma
id|jiffies
)paren
suffix:semicolon
macro_line|#endif
r_return
id|inb_p
c_func
(paren
id|dtlk_port_lpc
)paren
op_ne
l_int|0x7f
suffix:semicolon
)brace
DECL|function|dtlk_writeable
r_static
r_int
id|dtlk_writeable
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* TRACE_TEXT(&quot; dtlk_writeable&quot;); */
macro_line|#ifdef TRACINGMORE
id|printk
c_func
(paren
l_string|&quot; dtlk_writeable=%u&quot;
comma
(paren
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
op_amp
id|TTS_WRITABLE
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_return
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
op_amp
id|TTS_WRITABLE
suffix:semicolon
)brace
DECL|function|dtlk_dev_probe
r_static
r_int
id|__init
id|dtlk_dev_probe
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|testval
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|dtlk_settings
op_star
id|sp
suffix:semicolon
r_if
c_cond
(paren
id|dtlk_port_lpc
op_or
id|dtlk_port_tts
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|dtlk_portlist
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;DoubleTalk PC - Port %03x = %04x&bslash;n&quot;
comma
id|dtlk_portlist
(braket
id|i
)braket
comma
(paren
id|testval
op_assign
id|inw_p
c_func
(paren
id|dtlk_portlist
(braket
id|i
)braket
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|dtlk_portlist
(braket
id|i
)braket
comma
id|DTLK_IO_EXTENT
comma
l_string|&quot;dtlk&quot;
)paren
)paren
r_continue
suffix:semicolon
id|testval
op_assign
id|inw_p
c_func
(paren
id|dtlk_portlist
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|testval
op_and_assign
l_int|0xfbff
)paren
op_eq
l_int|0x107f
)paren
(brace
id|dtlk_port_lpc
op_assign
id|dtlk_portlist
(braket
id|i
)braket
suffix:semicolon
id|dtlk_port_tts
op_assign
id|dtlk_port_lpc
op_plus
l_int|1
suffix:semicolon
id|sp
op_assign
id|dtlk_interrogate
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;DoubleTalk PC at %03x-%03x, &quot;
l_string|&quot;ROM version %s, serial number %u&quot;
comma
id|dtlk_portlist
(braket
id|i
)braket
comma
id|dtlk_portlist
(braket
id|i
)braket
op_plus
id|DTLK_IO_EXTENT
op_minus
l_int|1
comma
id|sp-&gt;rom_version
comma
id|sp-&gt;serial_number
)paren
suffix:semicolon
multiline_comment|/* put LPC port into known state, so&n;&t;&t;&t;   dtlk_readable() gives valid result */
id|outb_p
c_func
(paren
l_int|0xff
comma
id|dtlk_port_lpc
)paren
suffix:semicolon
multiline_comment|/* INIT string and index marker */
id|dtlk_write_bytes
c_func
(paren
l_string|&quot;&bslash;036&bslash;1@&bslash;0&bslash;0012I&bslash;r&quot;
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* posting an index takes 18 msec.  Here, we&n;&t;&t;&t;   wait up to 100 msec to see whether it&n;&t;&t;&t;   appears. */
id|dtlk_delay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|dtlk_has_indexing
op_assign
id|dtlk_readable
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef TRACING
id|printk
c_func
(paren
l_string|&quot;, indexing %d&bslash;n&quot;
comma
id|dtlk_has_indexing
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef INSCOPE
(brace
multiline_comment|/* This macro records ten samples read from the LPC port, for later display */
DECL|macro|LOOK
mdefine_line|#define LOOK&t;&t;&t;&t;&t;&bslash;&n;for (i = 0; i &lt; 10; i++)&t;&t;&t;&bslash;&n;  {&t;&t;&t;&t;&t;&t;&bslash;&n;    buffer[b++] = inb_p(dtlk_port_lpc);&t;&t;&bslash;&n;    __delay(loops_per_jiffy/(1000000/HZ));             &bslash;&n;  }
r_char
id|buffer
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|b
op_assign
l_int|0
comma
id|i
comma
id|j
suffix:semicolon
id|LOOK
id|outb_p
c_func
(paren
l_int|0xff
comma
id|dtlk_port_lpc
)paren
suffix:semicolon
id|buffer
(braket
id|b
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|LOOK
id|dtlk_write_bytes
c_func
(paren
l_string|&quot;&bslash;0012I&bslash;r&quot;
comma
l_int|4
)paren
suffix:semicolon
id|buffer
(braket
id|b
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|__delay
c_func
(paren
l_int|50
op_star
id|loops_per_jiffy
op_div
(paren
l_int|1000
op_div
id|HZ
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xff
comma
id|dtlk_port_lpc
)paren
suffix:semicolon
id|buffer
(braket
id|b
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|LOOK
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
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
id|b
suffix:semicolon
id|j
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|buffer
(braket
id|j
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* INSCOPE */
macro_line|#ifdef OUTSCOPE
(brace
multiline_comment|/* This macro records ten samples read from the TTS port, for later display */
DECL|macro|LOOK
mdefine_line|#define LOOK&t;&t;&t;&t;&t;&bslash;&n;for (i = 0; i &lt; 10; i++)&t;&t;&t;&bslash;&n;  {&t;&t;&t;&t;&t;&t;&bslash;&n;    buffer[b++] = inb_p(dtlk_port_tts);&t;&t;&bslash;&n;    __delay(loops_per_jiffy/(1000000/HZ));  /* 1 us */ &bslash;&n;  }
r_char
id|buffer
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|b
op_assign
l_int|0
comma
id|i
comma
id|j
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* 10 ms */
id|LOOK
id|outb_p
c_func
(paren
l_int|0x03
comma
id|dtlk_port_tts
)paren
suffix:semicolon
id|buffer
(braket
id|b
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|LOOK
id|LOOK
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
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
id|b
suffix:semicolon
id|j
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|buffer
(braket
id|j
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* OUTSCOPE */
id|dtlk_write_bytes
c_func
(paren
l_string|&quot;Double Talk found&quot;
comma
l_int|18
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|dtlk_portlist
(braket
id|i
)braket
comma
id|DTLK_IO_EXTENT
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;nDoubleTalk PC - not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;   static void dtlk_handle_error(char op, char rc, unsigned int minor)&n;   {&n;   printk(KERN_INFO&quot;&bslash;nDoubleTalk PC - MINOR: %d, OPCODE: %d, ERROR: %d&bslash;n&quot;, &n;   minor, op, rc);&n;   return;&n;   }&n; */
multiline_comment|/* interrogate the DoubleTalk PC and return its settings */
DECL|function|dtlk_interrogate
r_static
r_struct
id|dtlk_settings
op_star
id|dtlk_interrogate
c_func
(paren
r_void
)paren
(brace
r_int
r_char
op_star
id|t
suffix:semicolon
r_static
r_char
id|buf
(braket
r_sizeof
(paren
r_struct
id|dtlk_settings
)paren
op_plus
l_int|1
)braket
suffix:semicolon
r_int
id|total
comma
id|i
suffix:semicolon
r_static
r_struct
id|dtlk_settings
id|status
suffix:semicolon
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_interrogate&quot;
)paren
suffix:semicolon
id|dtlk_write_bytes
c_func
(paren
l_string|&quot;&bslash;030&bslash;001?&quot;
comma
l_int|3
)paren
suffix:semicolon
r_for
c_loop
(paren
id|total
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|50
suffix:semicolon
id|i
op_increment
)paren
(brace
id|buf
(braket
id|total
)braket
op_assign
id|dtlk_read_tts
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|total
OG
l_int|2
op_logical_and
id|buf
(braket
id|total
)braket
op_eq
l_int|0x7f
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|total
OL
r_sizeof
(paren
r_struct
id|dtlk_settings
)paren
)paren
id|total
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   if (i==50) printk(&quot;interrogate() read overrun&bslash;n&quot;);&n;&t;   for (i=0; i&lt;sizeof(buf); i++)&n;&t;   printk(&quot; %02x&quot;, buf[i]);&n;&t;   printk(&quot;&bslash;n&quot;);&n;&t; */
id|t
op_assign
id|buf
suffix:semicolon
id|status.serial_number
op_assign
id|t
(braket
l_int|0
)braket
op_plus
id|t
(braket
l_int|1
)braket
op_star
l_int|256
suffix:semicolon
multiline_comment|/* serial number is&n;&t;&t;&t;&t;&t;&t;     little endian */
id|t
op_add_assign
l_int|2
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|t
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|status.rom_version
(braket
id|i
)braket
op_assign
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
r_sizeof
(paren
id|status.rom_version
)paren
op_minus
l_int|1
)paren
id|i
op_increment
suffix:semicolon
id|t
op_increment
suffix:semicolon
)brace
id|status.rom_version
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|t
op_increment
suffix:semicolon
id|status.mode
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.punc_level
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.formant_freq
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.pitch
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.speed
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.volume
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.tone
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.expression
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.ext_dict_loaded
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.ext_dict_status
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.free_ram
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.articulation
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.reverb
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.eob
op_assign
op_star
id|t
op_increment
suffix:semicolon
id|status.has_indexing
op_assign
id|dtlk_has_indexing
suffix:semicolon
id|TRACE_RET
suffix:semicolon
r_return
op_amp
id|status
suffix:semicolon
)brace
DECL|function|dtlk_read_tts
r_static
r_char
id|dtlk_read_tts
c_func
(paren
r_void
)paren
(brace
r_int
id|portval
comma
id|retries
op_assign
l_int|0
suffix:semicolon
r_char
id|ch
suffix:semicolon
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_read_tts&quot;
)paren
suffix:semicolon
multiline_comment|/* verify DT is ready, read char, wait for ACK */
r_do
(brace
id|portval
op_assign
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|portval
op_amp
id|TTS_READABLE
)paren
op_eq
l_int|0
op_logical_and
id|retries
op_increment
OL
id|DTLK_MAX_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_eq
id|DTLK_MAX_RETRIES
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dtlk_read_tts() timeout&bslash;n&quot;
)paren
suffix:semicolon
id|ch
op_assign
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
suffix:semicolon
multiline_comment|/* input from TTS port */
id|ch
op_and_assign
l_int|0x7f
suffix:semicolon
id|outb_p
c_func
(paren
id|ch
comma
id|dtlk_port_tts
)paren
suffix:semicolon
id|retries
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|portval
op_assign
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|portval
op_amp
id|TTS_READABLE
)paren
op_ne
l_int|0
op_logical_and
id|retries
op_increment
OL
id|DTLK_MAX_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_eq
id|DTLK_MAX_RETRIES
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dtlk_read_tts() timeout&bslash;n&quot;
)paren
suffix:semicolon
id|TRACE_RET
suffix:semicolon
r_return
id|ch
suffix:semicolon
)brace
DECL|function|dtlk_read_lpc
r_static
r_char
id|dtlk_read_lpc
c_func
(paren
r_void
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
r_char
id|ch
suffix:semicolon
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_read_lpc&quot;
)paren
suffix:semicolon
multiline_comment|/* no need to test -- this is only called when the port is readable */
id|ch
op_assign
id|inb_p
c_func
(paren
id|dtlk_port_lpc
)paren
suffix:semicolon
multiline_comment|/* input from LPC port */
id|outb_p
c_func
(paren
l_int|0xff
comma
id|dtlk_port_lpc
)paren
suffix:semicolon
multiline_comment|/* acknowledging a read takes 3-4&n;&t;   usec.  Here, we wait up to 20 usec&n;&t;   for the acknowledgement */
id|retries
op_assign
(paren
id|loops_per_jiffy
op_star
l_int|20
)paren
op_div
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
r_while
c_loop
(paren
id|inb_p
c_func
(paren
id|dtlk_port_lpc
)paren
op_ne
l_int|0x7f
op_logical_and
op_decrement
id|retries
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dtlk_read_lpc() timeout&bslash;n&quot;
)paren
suffix:semicolon
id|TRACE_RET
suffix:semicolon
r_return
id|ch
suffix:semicolon
)brace
multiline_comment|/* write n bytes to tts port */
DECL|function|dtlk_write_bytes
r_static
r_char
id|dtlk_write_bytes
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
id|n
)paren
(brace
r_char
id|val
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*  printk(&quot;dtlk_write_bytes(&bslash;&quot;%-*s&bslash;&quot;, %d)&bslash;n&quot;, n, buf, n); */
id|TRACE_TEXT
c_func
(paren
l_string|&quot;(dtlk_write_bytes&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
OG
l_int|0
)paren
id|val
op_assign
id|dtlk_write_tts
c_func
(paren
op_star
id|buf
op_increment
)paren
suffix:semicolon
id|TRACE_RET
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|dtlk_write_tts
r_static
r_char
id|dtlk_write_tts
c_func
(paren
r_char
id|ch
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef TRACINGMORE
id|printk
c_func
(paren
l_string|&quot;  dtlk_write_tts(&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_char|&squot; &squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;~&squot;
)paren
id|printk
c_func
(paren
l_string|&quot;&squot;%c&squot;&quot;
comma
id|ch
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;0x%02x&quot;
comma
id|ch
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ch
op_ne
id|DTLK_CLEAR
)paren
multiline_comment|/* no flow control for CLEAR command */
r_while
c_loop
(paren
(paren
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
op_amp
id|TTS_WRITABLE
)paren
op_eq
l_int|0
op_logical_and
id|retries
op_increment
OL
id|DTLK_MAX_RETRIES
)paren
multiline_comment|/* DT ready? */
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_eq
id|DTLK_MAX_RETRIES
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dtlk_write_tts() timeout&bslash;n&quot;
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ch
comma
id|dtlk_port_tts
)paren
suffix:semicolon
multiline_comment|/* output to TTS port */
multiline_comment|/* the RDY bit goes zero 2-3 usec after writing, and goes&n;&t;   1 again 180-190 usec later.  Here, we wait up to 10&n;&t;   usec for the RDY bit to go zero. */
r_for
c_loop
(paren
id|retries
op_assign
l_int|0
suffix:semicolon
id|retries
OL
id|loops_per_jiffy
op_div
(paren
l_int|100000
op_div
id|HZ
)paren
suffix:semicolon
id|retries
op_increment
)paren
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
id|dtlk_port_tts
)paren
op_amp
id|TTS_WRITABLE
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
macro_line|#ifdef TRACINGMORE
id|printk
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
