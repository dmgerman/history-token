multiline_comment|/* radio-cadet.c - A video4linux driver for the ADS Cadet AM/FM Radio Card&n; *&n; * by Fred Gleason &lt;fredg@wava.com&gt;&n; * Version 0.3.3&n; *&n; * (Loosely) based on code for the Aztech radio card by&n; *&n; * Russell Kroll    (rkroll@exploits.org)&n; * Quay Ly&n; * Donald Song&n; * Jason Lewis      (jlewis@twilight.vtc.vsc.edu) &n; * Scott McGrath    (smcgrath@twilight.vtc.vsc.edu)&n; * William McGrath  (wmcgrath@twilight.vtc.vsc.edu)&n; *&n; * History:&n; * 2000-04-29&t;Russell Kroll &lt;rkroll@exploits.org&gt;&n; *&t;&t;Added ISAPnP detection for Linux 2.3/2.4&n; *&n; * 2001-01-10&t;Russell Kroll &lt;rkroll@exploits.org&gt;&n; *&t;&t;Removed dead CONFIG_RADIO_CADET_PORT code&n; *&t;&t;PnP detection on load is now default (no args necessary)&n; *&n; * 2002-01-17&t;Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&t;&t;Updated to latest pnp code&n; *&n; * 2003-01-31&t;Alan Cox &lt;alan@redhat.com&gt;&n; *&t;&t;Cleaned up locking, delay code, general odds and ends&n; */
macro_line|#include &lt;linux/module.h&gt;&t;/* Modules &t;&t;&t;*/
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* Initdata&t;&t;&t;*/
macro_line|#include &lt;linux/ioport.h&gt;&t;/* check_region, request_region&t;*/
macro_line|#include &lt;linux/delay.h&gt;&t;/* udelay&t;&t;&t;*/
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* outb, outb_p&t;&t;&t;*/
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy to/from user&t;&t;*/
macro_line|#include &lt;linux/videodev.h&gt;&t;/* kernel radio structs&t;&t;*/
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
DECL|macro|RDS_BUFFER
mdefine_line|#define RDS_BUFFER 256
DECL|variable|io
r_static
r_int
id|io
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* default to isapnp activation */
DECL|variable|radio_nr
r_static
r_int
id|radio_nr
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|users
r_static
r_int
id|users
op_assign
l_int|0
suffix:semicolon
DECL|variable|curtuner
r_static
r_int
id|curtuner
op_assign
l_int|0
suffix:semicolon
DECL|variable|tunestat
r_static
r_int
id|tunestat
op_assign
l_int|0
suffix:semicolon
DECL|variable|sigstrength
r_static
r_int
id|sigstrength
op_assign
l_int|0
suffix:semicolon
DECL|variable|read_queue
r_static
id|wait_queue_head_t
id|read_queue
suffix:semicolon
DECL|variable|tunertimer
DECL|variable|rdstimer
DECL|variable|readtimer
r_struct
id|timer_list
id|tunertimer
comma
id|rdstimer
comma
id|readtimer
suffix:semicolon
DECL|variable|rdsin
DECL|variable|rdsout
DECL|variable|rdsstat
r_static
id|__u8
id|rdsin
op_assign
l_int|0
comma
id|rdsout
op_assign
l_int|0
comma
id|rdsstat
op_assign
l_int|0
suffix:semicolon
DECL|variable|rdsbuf
r_static
r_int
r_char
id|rdsbuf
(braket
id|RDS_BUFFER
)braket
suffix:semicolon
DECL|variable|cadet_io_lock
r_static
id|spinlock_t
id|cadet_io_lock
suffix:semicolon
r_static
r_int
id|cadet_probe
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Signal Strength Threshold Values&n; * The V4L API spec does not define any particular unit for the signal &n; * strength value.  These values are in microvolts of RF at the tuner&squot;s input.&n; */
DECL|variable|sigtable
r_static
id|__u16
id|sigtable
(braket
l_int|2
)braket
(braket
l_int|4
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|cadet_getrds
r_static
r_int
id|cadet_getrds
c_func
(paren
r_void
)paren
(brace
r_int
id|rdsstat
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|3
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select Decoder Control/Status */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
op_amp
l_int|0x7f
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Reset RDS detection */
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|3
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select Decoder Control/Status */
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
op_amp
l_int|0x80
)paren
op_ne
l_int|0
)paren
(brace
id|rdsstat
op_or_assign
id|VIDEO_TUNER_RDS_ON
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
op_amp
l_int|0x10
)paren
op_ne
l_int|0
)paren
(brace
id|rdsstat
op_or_assign
id|VIDEO_TUNER_MBS_ON
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
r_return
id|rdsstat
suffix:semicolon
)brace
DECL|function|cadet_getstereo
r_static
r_int
id|cadet_getstereo
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|curtuner
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Only FM has stereo capability! */
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cadet_gettune
r_static
r_int
id|cadet_gettune
c_func
(paren
r_void
)paren
(brace
r_int
id|curvol
comma
id|i
suffix:semicolon
r_int
id|fifo
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;         * Prepare for read&n;         */
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
id|curvol
op_assign
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Save current volume/mute setting */
id|outb
c_func
(paren
l_int|0x00
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Ensure WRITE-ENABLE is LOW */
id|tunestat
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/*&n;         * Read the shift register&n;         */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|25
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fifo
op_assign
(paren
id|fifo
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
op_rshift
l_int|7
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|24
)paren
(brace
id|outb
c_func
(paren
l_int|0x01
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|tunestat
op_and_assign
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;         * Restore volume/mute setting&n;         */
id|outb
c_func
(paren
id|curvol
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
r_return
id|fifo
suffix:semicolon
)brace
DECL|function|cadet_getfreq
r_static
r_int
id|cadet_getfreq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|freq
op_assign
l_int|0
comma
id|test
comma
id|fifo
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Read current tuning&n;&t; */
id|fifo
op_assign
id|cadet_gettune
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * Convert to actual frequency&n;         */
r_if
c_cond
(paren
id|curtuner
op_eq
l_int|0
)paren
(brace
multiline_comment|/* FM */
id|test
op_assign
l_int|12500
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
l_int|14
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|fifo
op_amp
l_int|0x01
)paren
op_ne
l_int|0
)paren
(brace
id|freq
op_add_assign
id|test
suffix:semicolon
)brace
id|test
op_assign
id|test
op_lshift
l_int|1
suffix:semicolon
id|fifo
op_assign
id|fifo
op_rshift
l_int|1
suffix:semicolon
)brace
id|freq
op_sub_assign
l_int|10700000
suffix:semicolon
multiline_comment|/* IF frequency is 10.7 MHz */
id|freq
op_assign
(paren
id|freq
op_star
l_int|16
)paren
op_div
l_int|1000000
suffix:semicolon
multiline_comment|/* Make it 1/16 MHz */
)brace
r_if
c_cond
(paren
id|curtuner
op_eq
l_int|1
)paren
(brace
multiline_comment|/* AM */
id|freq
op_assign
(paren
(paren
id|fifo
op_amp
l_int|0x7fff
)paren
op_minus
l_int|2010
)paren
op_star
l_int|16
suffix:semicolon
)brace
r_return
id|freq
suffix:semicolon
)brace
DECL|function|cadet_settune
r_static
r_void
id|cadet_settune
c_func
(paren
r_int
id|fifo
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|test
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
multiline_comment|/*&n;&t; * Write the shift register&n;&t; */
id|test
op_assign
l_int|0
suffix:semicolon
id|test
op_assign
(paren
id|fifo
op_rshift
l_int|23
)paren
op_amp
l_int|0x02
suffix:semicolon
multiline_comment|/* Align data for SDO */
id|test
op_or_assign
l_int|0x1c
suffix:semicolon
multiline_comment|/* SDM=1, SWE=1, SEN=1, SCK=0 */
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
id|outb
c_func
(paren
id|test
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Initialize for write */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|25
suffix:semicolon
id|i
op_increment
)paren
(brace
id|test
op_or_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* Toggle SCK High */
id|outb
c_func
(paren
id|test
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|test
op_and_assign
l_int|0xfe
suffix:semicolon
multiline_comment|/* Toggle SCK Low */
id|outb
c_func
(paren
id|test
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|fifo
op_assign
id|fifo
op_lshift
l_int|1
suffix:semicolon
multiline_comment|/* Prepare the next bit */
id|test
op_assign
l_int|0x1c
op_or
(paren
(paren
id|fifo
op_rshift
l_int|23
)paren
op_amp
l_int|0x02
)paren
suffix:semicolon
id|outb
c_func
(paren
id|test
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
)brace
DECL|function|cadet_setfreq
r_static
r_void
id|cadet_setfreq
c_func
(paren
r_int
id|freq
)paren
(brace
r_int
id|fifo
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|test
suffix:semicolon
r_int
id|curvol
suffix:semicolon
multiline_comment|/* &n;         * Formulate a fifo command&n;         */
id|fifo
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|curtuner
op_eq
l_int|0
)paren
(brace
multiline_comment|/* FM */
id|test
op_assign
l_int|102400
suffix:semicolon
id|freq
op_assign
(paren
id|freq
op_star
l_int|1000
)paren
op_div
l_int|16
suffix:semicolon
multiline_comment|/* Make it kHz */
id|freq
op_add_assign
l_int|10700
suffix:semicolon
multiline_comment|/* IF is 10700 kHz */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|14
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fifo
op_assign
id|fifo
op_lshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|freq
op_ge
id|test
)paren
(brace
id|fifo
op_or_assign
l_int|0x01
suffix:semicolon
id|freq
op_sub_assign
id|test
suffix:semicolon
)brace
id|test
op_assign
id|test
op_rshift
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|curtuner
op_eq
l_int|1
)paren
(brace
multiline_comment|/* AM */
id|fifo
op_assign
(paren
id|freq
op_div
l_int|16
)paren
op_plus
l_int|2010
suffix:semicolon
multiline_comment|/* Make it kHz */
id|fifo
op_or_assign
l_int|0x100000
suffix:semicolon
multiline_comment|/* Select AM Band */
)brace
multiline_comment|/*&n;         * Save current volume/mute setting&n;         */
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
id|curvol
op_assign
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tune the card&n;&t; */
r_for
c_loop
(paren
id|j
op_assign
l_int|3
suffix:semicolon
id|j
OG
op_minus
l_int|1
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|cadet_settune
c_func
(paren
id|fifo
op_or
(paren
id|j
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
id|outb
c_func
(paren
id|curvol
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
id|cadet_gettune
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tunestat
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Tuned */
id|sigstrength
op_assign
id|sigtable
(braket
id|curtuner
)braket
(braket
id|j
)braket
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|sigstrength
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|cadet_getvol
r_static
r_int
id|cadet_getvol
c_func
(paren
r_void
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
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
op_amp
l_int|0x20
)paren
op_ne
l_int|0
)paren
(brace
id|ret
op_assign
l_int|0xffff
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cadet_setvol
r_static
r_void
id|cadet_setvol
c_func
(paren
r_int
id|vol
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select tuner control */
r_if
c_cond
(paren
id|vol
OG
l_int|0
)paren
(brace
id|outb
c_func
(paren
l_int|0x20
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|outb
c_func
(paren
l_int|0x00
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
)brace
DECL|function|cadet_handler
r_void
id|cadet_handler
c_func
(paren
r_int
r_int
id|data
)paren
(brace
multiline_comment|/*&n;&t; * Service the RDS fifo&n;&t; */
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
)paren
(brace
id|outb
c_func
(paren
l_int|0x3
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select RDS Decoder Control */
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
op_amp
l_int|0x20
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cadet: RDS fifo overflow&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0x80
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select RDS fifo */
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|io
)paren
op_amp
l_int|0x80
)paren
op_ne
l_int|0
)paren
(brace
id|rdsbuf
(braket
id|rdsin
)braket
op_assign
id|inb
c_func
(paren
id|io
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rdsin
op_eq
id|rdsout
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cadet: RDS buffer overflow&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|rdsin
op_increment
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Service pending read&n;&t; */
r_if
c_cond
(paren
id|rdsin
op_ne
id|rdsout
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|read_queue
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Clean up and exit&n;&t; */
id|init_timer
c_func
(paren
op_amp
id|readtimer
)paren
suffix:semicolon
id|readtimer.function
op_assign
id|cadet_handler
suffix:semicolon
id|readtimer.data
op_assign
(paren
r_int
r_int
)paren
l_int|0
suffix:semicolon
id|readtimer.expires
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|20
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|readtimer
)paren
suffix:semicolon
)brace
DECL|function|cadet_read
r_static
id|ssize_t
id|cadet_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|data
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
suffix:semicolon
r_int
r_char
id|readbuf
(braket
id|RDS_BUFFER
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rdsstat
op_eq
l_int|0
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|rdsstat
op_assign
l_int|1
suffix:semicolon
id|outb
c_func
(paren
l_int|0x80
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* Select RDS fifo */
id|spin_unlock
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|readtimer
)paren
suffix:semicolon
id|readtimer.function
op_assign
id|cadet_handler
suffix:semicolon
id|readtimer.data
op_assign
(paren
r_int
r_int
)paren
l_int|0
suffix:semicolon
id|readtimer.expires
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|20
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|readtimer
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rdsin
op_eq
id|rdsout
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EWOULDBLOCK
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|read_queue
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|count
op_logical_and
id|rdsin
op_ne
id|rdsout
)paren
(brace
id|readbuf
(braket
id|i
op_increment
)braket
op_assign
id|rdsbuf
(braket
id|rdsout
op_increment
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|data
comma
id|readbuf
comma
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|cadet_do_ioctl
r_static
r_int
id|cadet_do_ioctl
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
r_void
op_star
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
id|VIDIOCGCAP
suffix:colon
(brace
r_struct
id|video_capability
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
id|v
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
id|v-&gt;type
op_assign
id|VID_TYPE_TUNER
suffix:semicolon
id|v-&gt;channels
op_assign
l_int|2
suffix:semicolon
id|v-&gt;audios
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;ADS Cadet&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGTUNER
suffix:colon
(brace
r_struct
id|video_tuner
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
(paren
id|v-&gt;tuner
OL
l_int|0
)paren
op_logical_or
(paren
id|v-&gt;tuner
OG
l_int|1
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|v-&gt;tuner
)paren
(brace
r_case
l_int|0
suffix:colon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;FM&quot;
)paren
suffix:semicolon
id|v-&gt;rangelow
op_assign
l_int|1400
suffix:semicolon
multiline_comment|/* 87.5 MHz */
id|v-&gt;rangehigh
op_assign
l_int|1728
suffix:semicolon
multiline_comment|/* 108.0 MHz */
id|v-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|v-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|v-&gt;mode
op_or_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|v-&gt;signal
op_assign
id|sigstrength
suffix:semicolon
r_if
c_cond
(paren
id|cadet_getstereo
c_func
(paren
)paren
op_eq
l_int|1
)paren
(brace
id|v-&gt;flags
op_or_assign
id|VIDEO_TUNER_STEREO_ON
suffix:semicolon
)brace
id|v-&gt;flags
op_or_assign
id|cadet_getrds
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;AM&quot;
)paren
suffix:semicolon
id|v-&gt;rangelow
op_assign
l_int|8320
suffix:semicolon
multiline_comment|/* 520 kHz */
id|v-&gt;rangehigh
op_assign
l_int|26400
suffix:semicolon
multiline_comment|/* 1650 kHz */
id|v-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|v-&gt;flags
op_or_assign
id|VIDEO_TUNER_LOW
suffix:semicolon
id|v-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|v-&gt;mode
op_or_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|v-&gt;signal
op_assign
id|sigstrength
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSTUNER
suffix:colon
(brace
r_struct
id|video_tuner
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
(paren
id|v-&gt;tuner
OL
l_int|0
)paren
op_logical_or
(paren
id|v-&gt;tuner
OG
l_int|1
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|curtuner
op_assign
id|v-&gt;tuner
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGFREQ
suffix:colon
(brace
r_int
r_int
op_star
id|freq
op_assign
id|arg
suffix:semicolon
op_star
id|freq
op_assign
id|cadet_getfreq
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSFREQ
suffix:colon
(brace
r_int
r_int
op_star
id|freq
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
(paren
id|curtuner
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
op_star
id|freq
OL
l_int|1400
)paren
op_logical_or
(paren
op_star
id|freq
OG
l_int|1728
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|curtuner
op_eq
l_int|1
)paren
op_logical_and
(paren
(paren
op_star
id|freq
OL
l_int|8320
)paren
op_logical_or
(paren
op_star
id|freq
OG
l_int|26400
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cadet_setfreq
c_func
(paren
op_star
id|freq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
id|v
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
id|v-&gt;flags
op_assign
id|VIDEO_AUDIO_MUTABLE
op_or
id|VIDEO_AUDIO_VOLUME
suffix:semicolon
r_if
c_cond
(paren
id|cadet_getstereo
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
id|v-&gt;mode
op_assign
id|VIDEO_SOUND_MONO
suffix:semicolon
)brace
r_else
(brace
id|v-&gt;mode
op_assign
id|VIDEO_SOUND_STEREO
suffix:semicolon
)brace
id|v-&gt;volume
op_assign
id|cadet_getvol
c_func
(paren
)paren
suffix:semicolon
id|v-&gt;step
op_assign
l_int|0xffff
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Radio&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;audio
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cadet_setvol
c_func
(paren
id|v-&gt;volume
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
(brace
id|cadet_setvol
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|cadet_setvol
c_func
(paren
l_int|0xffff
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|function|cadet_ioctl
r_static
r_int
id|cadet_ioctl
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
r_return
id|video_usercopy
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|cadet_do_ioctl
)paren
suffix:semicolon
)brace
DECL|function|cadet_open
r_static
r_int
id|cadet_open
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
r_if
c_cond
(paren
id|users
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|users
op_increment
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|read_queue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cadet_release
r_static
r_int
id|cadet_release
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
id|del_timer_sync
c_func
(paren
op_amp
id|readtimer
)paren
suffix:semicolon
id|rdsstat
op_assign
l_int|0
suffix:semicolon
id|users
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cadet_fops
r_static
r_struct
id|file_operations
id|cadet_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|cadet_open
comma
dot
id|release
op_assign
id|cadet_release
comma
dot
id|read
op_assign
id|cadet_read
comma
dot
id|ioctl
op_assign
id|cadet_ioctl
comma
dot
id|llseek
op_assign
id|no_llseek
comma
)brace
suffix:semicolon
DECL|variable|cadet_radio
r_static
r_struct
id|video_device
id|cadet_radio
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;Cadet radio&quot;
comma
dot
id|type
op_assign
id|VID_TYPE_TUNER
comma
dot
id|hardware
op_assign
id|VID_HARDWARE_CADET
comma
dot
id|fops
op_assign
op_amp
id|cadet_fops
comma
)brace
suffix:semicolon
DECL|variable|cadet_pnp_devices
r_static
r_struct
id|pnp_device_id
id|cadet_pnp_devices
(braket
)braket
op_assign
(brace
multiline_comment|/* ADS Cadet AM/FM Radio Card */
(brace
dot
id|id
op_assign
l_string|&quot;MSM0c24&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pnp
comma
id|cadet_pnp_devices
)paren
suffix:semicolon
DECL|function|cadet_pnp_probe
r_static
r_int
id|cadet_pnp_probe
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|dev_id
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* only support one device */
r_if
c_cond
(paren
id|io
OG
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_port_valid
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|io
op_assign
id|pnp_port_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;radio-cadet: PnP reports device at %#x&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
id|io
suffix:semicolon
)brace
DECL|variable|cadet_pnp_driver
r_static
r_struct
id|pnp_driver
id|cadet_pnp_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;radio-cadet&quot;
comma
dot
id|id_table
op_assign
id|cadet_pnp_devices
comma
dot
id|probe
op_assign
id|cadet_pnp_probe
comma
dot
id|remove
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|cadet_probe
r_static
r_int
id|cadet_probe
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|iovals
(braket
l_int|8
)braket
op_assign
initialization_block
suffix:semicolon
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|io
op_assign
id|iovals
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|io
comma
l_int|2
comma
l_string|&quot;cadet-probe&quot;
)paren
op_ge
l_int|0
)paren
(brace
id|cadet_setfreq
c_func
(paren
l_int|1410
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cadet_getfreq
c_func
(paren
)paren
op_eq
l_int|1410
)paren
(brace
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
r_return
id|io
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n; * io should only be set if the user has used something like&n; * isapnp (the userspace program) to initialize this card for us&n; */
DECL|function|cadet_init
r_static
r_int
id|__init
id|cadet_init
c_func
(paren
r_void
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|cadet_io_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;If a probe was requested then probe ISAPnP first (safest)&n;&t; */
r_if
c_cond
(paren
id|io
OL
l_int|0
)paren
id|pnp_register_driver
c_func
(paren
op_amp
id|cadet_pnp_driver
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;If that fails then probe unsafely if probe is requested&n;&t; */
r_if
c_cond
(paren
id|io
OL
l_int|0
)paren
(brace
id|io
op_assign
id|cadet_probe
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Else we bail out&n;&t; */
r_if
c_cond
(paren
id|io
OL
l_int|0
)paren
(brace
macro_line|#ifdef MODULE        
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;You must set an I/O address with io=0x???&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
l_int|2
comma
l_string|&quot;cadet&quot;
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|cadet_radio
comma
id|VFL_TYPE_RADIO
comma
id|radio_nr
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ADS Cadet Radio Card at 0x%x&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|pnp_unregister_driver
c_func
(paren
op_amp
id|cadet_pnp_driver
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Fred Gleason, Russell Kroll, Quay Lu, Donald Song, Jason Lewis, Scott McGrath, William McGrath&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;A driver for the ADS Cadet AM/FM/RDS radio card.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O address of Cadet card (0x330,0x332,0x334,0x336,0x338,0x33a,0x33c,0x33e)&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|radio_nr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|cadet_cleanup_module
r_static
r_void
id|__exit
id|cadet_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|cadet_radio
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
id|pnp_unregister_driver
c_func
(paren
op_amp
id|cadet_pnp_driver
)paren
suffix:semicolon
)brace
DECL|variable|cadet_init
id|module_init
c_func
(paren
id|cadet_init
)paren
suffix:semicolon
DECL|variable|cadet_cleanup_module
id|module_exit
c_func
(paren
id|cadet_cleanup_module
)paren
suffix:semicolon
eof
