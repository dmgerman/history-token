multiline_comment|/*&n; *&t;Linux driver for the PC110 pad&n; */
multiline_comment|/**&n; * &t;DOC: PC110 Digitizer Hardware&n; *&n; *&t;The pad provides triples of data. The first byte has&n; *&t;0x80=bit 8 X, 0x01=bit 7 X, 0x08=bit 8 Y, 0x01=still down&n; *&t;The second byte is bits 0-6 X&n; *&t;The third is bits 0-6 Y&n; *&n; *&t;This is read internally and used to synthesize a stream of&n; *&t;triples in the form expected from a PS/2 device. Specialist&n; *&t;applications can choose to obtain the pad data in other formats&n; *&t;including a debugging mode.&n; *&n; *&t;It would be good to add a joystick driver mode to this pad so&n; *&t;that doom and other game playing are better. One possible approach&n; *&t;would be to deactive the mouse mode while the joystick port is opened.&n; */
multiline_comment|/*&n; *&t;History&n; *&n; *&t;0.0 1997-05-16 Alan Cox &lt;alan@redhat.com&gt; - Pad reader&n; *&t;0.1 1997-05-19 Robin O&squot;Leary &lt;robin@acm.org&gt; - PS/2 emulation&n; *&t;0.2 1997-06-03 Robin O&squot;Leary &lt;robin@acm.org&gt; - tap gesture&n; *&t;0.3 1997-06-27 Alan Cox &lt;alan@redhat.com&gt; - 2.1 commit&n; *&t;0.4 1997-11-09 Alan Cox &lt;alan@redhat.com&gt; - Single Unix VFS API changes&n; *&t;0.5 2000-02-10 Alan Cox &lt;alan@redhat.com&gt; - 2.3.x cleanup, documentation&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;pc110pad.h&quot;
DECL|variable|default_params
r_static
r_struct
id|pc110pad_params
id|default_params
op_assign
(brace
id|mode
suffix:colon
id|PC110PAD_PS2
comma
id|bounce_interval
suffix:colon
l_int|50
id|MS
comma
id|tap_interval
suffix:colon
l_int|200
id|MS
comma
id|irq
suffix:colon
l_int|10
comma
id|io
suffix:colon
l_int|0x15E0
comma
)brace
suffix:semicolon
DECL|variable|current_params
r_static
r_struct
id|pc110pad_params
id|current_params
suffix:semicolon
multiline_comment|/* driver/filesystem interface management */
DECL|variable|queue
r_static
id|wait_queue_head_t
id|queue
suffix:semicolon
DECL|variable|asyncptr
r_static
r_struct
id|fasync_struct
op_star
id|asyncptr
suffix:semicolon
DECL|variable|active_count
r_static
id|active_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* number of concurrent open()s */
DECL|variable|active_lock
r_static
id|spinlock_t
id|active_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* this lock should be held when referencing active_count */
DECL|variable|reader_lock
r_static
r_struct
id|semaphore
id|reader_lock
suffix:semicolon
multiline_comment|/**&n; *&t;wake_readers:&n; *&n; *&t;Take care of letting any waiting processes know that&n; *&t;now would be a good time to do a read().  Called&n; *&t;whenever a state transition occurs, real or synthetic. Also&n; *&t;issue any SIGIO&squot;s to programs that use SIGIO on mice (eg&n; *&t;Executor)&n; */
DECL|function|wake_readers
r_static
r_void
id|wake_readers
c_func
(paren
r_void
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|queue
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
op_amp
id|asyncptr
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Deal with the messy business of synthesizing button tap and drag&n; * events.&n; *&n; * Exports:&n; *&t;notify_pad_up_down()&n; *&t;&t;Must be called whenever debounced pad up/down state changes.&n; *&t;button_pending&n; *&t;&t;Flag is set whenever read_button() has new values&n; *&t;&t;to return.&n; *&t;read_button()&n; *&t;&t;Obtains the current synthetic mouse button state.&n; */
multiline_comment|/*&n; * These keep track of up/down transitions needed to generate the&n; * synthetic mouse button events.  While recent_transition is set,&n; * up/down events cause transition_count to increment.  tap_timer&n; * turns off the recent_transition flag and may cause some synthetic&n; * up/down mouse events to be created by incrementing synthesize_tap.&n; */
DECL|variable|button_pending
r_static
r_int
id|button_pending
suffix:semicolon
DECL|variable|recent_transition
r_static
r_int
id|recent_transition
suffix:semicolon
DECL|variable|transition_count
r_static
r_int
id|transition_count
suffix:semicolon
DECL|variable|synthesize_tap
r_static
r_int
id|synthesize_tap
suffix:semicolon
r_static
r_void
id|tap_timeout
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|variable|tap_timer
r_static
r_struct
id|timer_list
id|tap_timer
op_assign
(brace
id|function
suffix:colon
id|tap_timeout
)brace
suffix:semicolon
multiline_comment|/**&n; * tap_timeout:&n; * @data: Unused&n; *&n; * This callback goes off a short time after an up/down transition;&n; * before it goes off, transitions will be considered part of a&n; * single PS/2 event and counted in transition_count.  Once the&n; * timeout occurs the recent_transition flag is cleared and&n; * any synthetic mouse up/down events are generated.&n; */
DECL|function|tap_timeout
r_static
r_void
id|tap_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|recent_transition
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pc110pad: tap_timeout but no recent transition!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|transition_count
op_eq
l_int|2
op_logical_or
id|transition_count
op_eq
l_int|4
op_logical_or
id|transition_count
op_eq
l_int|6
)paren
(brace
id|synthesize_tap
op_add_assign
id|transition_count
suffix:semicolon
id|button_pending
op_assign
l_int|1
suffix:semicolon
id|wake_readers
c_func
(paren
)paren
suffix:semicolon
)brace
id|recent_transition
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * notify_pad_up_down:&n; *&n; * Called by the raw pad read routines when a (debounced) up/down&n; * transition is detected.&n; */
DECL|function|notify_pad_up_down
r_void
id|notify_pad_up_down
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|recent_transition
)paren
(brace
id|transition_count
op_increment
suffix:semicolon
)brace
r_else
(brace
id|transition_count
op_assign
l_int|1
suffix:semicolon
id|recent_transition
op_assign
l_int|1
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|tap_timer
comma
id|jiffies
op_plus
id|current_params.tap_interval
)paren
suffix:semicolon
multiline_comment|/* changes to transition_count can cause reported button to change */
id|button_pending
op_assign
l_int|1
suffix:semicolon
id|wake_readers
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;read_button:&n; *&t;@b: pointer to the button status.&n; *&n; *&t;The actual button state depends on what we are seeing. We have to check&n; *&t;for the tap gesture and also for dragging.&n; */
DECL|function|read_button
r_static
r_void
id|read_button
c_func
(paren
r_int
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|synthesize_tap
)paren
(brace
op_star
id|b
op_assign
op_decrement
id|synthesize_tap
op_amp
l_int|1
suffix:semicolon
)brace
r_else
(brace
op_star
id|b
op_assign
(paren
op_logical_neg
id|recent_transition
op_logical_and
id|transition_count
op_eq
l_int|3
)paren
suffix:semicolon
multiline_comment|/* drag */
)brace
id|button_pending
op_assign
(paren
id|synthesize_tap
OG
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Read pad absolute co-ordinates and debounced up/down state.&n; *&n; * Exports:&n; *&t;pad_irq()&n; *&t;&t;Function to be called whenever the pad signals&n; *&t;&t;that it has new data available.&n; *&t;read_raw_pad()&n; *&t;&t;Returns the most current pad state.&n; *&t;xy_pending&n; *&t;&t;Flag is set whenever read_raw_pad() has new values&n; *&t;&t;to return.&n; * Imports:&n; *&t;wake_readers()&n; *&t;&t;Called when movement occurs.&n; *&t;notify_pad_up_down()&n; *&t;&t;Called when debounced up/down status changes.&n; */
multiline_comment|/*&n; * These are up/down state and absolute co-ords read directly from pad &n; */
DECL|variable|raw_data
r_static
r_int
id|raw_data
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|raw_data_count
r_static
r_int
id|raw_data_count
suffix:semicolon
DECL|variable|raw_x
DECL|variable|raw_y
r_static
r_int
id|raw_x
comma
id|raw_y
suffix:semicolon
multiline_comment|/* most recent absolute co-ords read */
DECL|variable|raw_down
r_static
r_int
id|raw_down
suffix:semicolon
multiline_comment|/* raw up/down state */
DECL|variable|debounced_down
r_static
r_int
id|debounced_down
suffix:semicolon
multiline_comment|/* up/down state after debounce processing */
DECL|enumerator|NO_BOUNCE
DECL|enumerator|JUST_GONE_UP
DECL|enumerator|JUST_GONE_DOWN
DECL|variable|bounce
r_static
r_enum
(brace
id|NO_BOUNCE
comma
id|JUST_GONE_UP
comma
id|JUST_GONE_DOWN
)brace
id|bounce
op_assign
id|NO_BOUNCE
suffix:semicolon
multiline_comment|/* set just after an up/down transition */
DECL|variable|xy_pending
r_static
r_int
id|xy_pending
suffix:semicolon
multiline_comment|/* set if new data have not yet been read */
multiline_comment|/* &n; * Timer goes off a short while after an up/down transition and copies&n; * the value of raw_down to debounced_down.&n; */
r_static
r_void
id|bounce_timeout
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|variable|bounce_timer
r_static
r_struct
id|timer_list
id|bounce_timer
op_assign
(brace
id|function
suffix:colon
id|bounce_timeout
)brace
suffix:semicolon
multiline_comment|/**&n; * bounce_timeout:&n; * @data: Unused&n; *&n; * No further up/down transitions happened within the&n; * bounce period, so treat this as a genuine transition.&n; */
DECL|function|bounce_timeout
r_static
r_void
id|bounce_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_switch
c_cond
(paren
id|bounce
)paren
(brace
r_case
id|NO_BOUNCE
suffix:colon
(brace
multiline_comment|/*&n;&t;&t;&t; * Strange; the timer callback should only go off if&n;&t;&t;&t; * we were expecting to do bounce processing!&n;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;pc110pad, bounce_timeout: bounce flag not set!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|JUST_GONE_UP
suffix:colon
(brace
multiline_comment|/*&n;&t;&t;&t; * The last up we spotted really was an up, so set&n;&t;&t;&t; * debounced state the same as raw state.&n;&t;&t;&t; */
id|bounce
op_assign
id|NO_BOUNCE
suffix:semicolon
r_if
c_cond
(paren
id|debounced_down
op_eq
id|raw_down
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;pc110pad, bounce_timeout: raw already debounced!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|debounced_down
op_assign
id|raw_down
suffix:semicolon
id|notify_pad_up_down
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|JUST_GONE_DOWN
suffix:colon
(brace
multiline_comment|/*&n;&t;&t;&t; * We don&squot;t debounce down events, but we still time&n;&t;&t;&t; * out soon after one occurs so we can avoid the (x,y)&n;&t;&t;&t; * skittering that sometimes happens.&n;&t;&t;&t; */
id|bounce
op_assign
id|NO_BOUNCE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * pad_irq:&n; * @irq: Interrupt number&n; * @ptr: Unused&n; * @regs: Unused&n; *&n; * Callback when pad&squot;s irq goes off; copies values in to raw_* globals;&n; * initiates debounce processing. This isn&squot;t SMP safe however there are&n; * no SMP machines with a PC110 touchpad on them.&n; */
DECL|function|pad_irq
r_static
r_void
id|pad_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* Obtain byte from pad and prime for next byte */
(brace
r_int
id|value
op_assign
id|inb_p
c_func
(paren
id|current_params.io
)paren
suffix:semicolon
r_int
id|handshake
op_assign
id|inb_p
c_func
(paren
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|handshake
op_or
l_int|1
comma
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|handshake
op_amp
op_complement
l_int|1
comma
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
id|inb_p
c_func
(paren
l_int|0x64
)paren
suffix:semicolon
id|raw_data
(braket
id|raw_data_count
op_increment
)braket
op_assign
id|value
suffix:semicolon
)brace
r_if
c_cond
(paren
id|raw_data_count
op_eq
l_int|3
)paren
(brace
r_int
id|new_down
op_assign
id|raw_data
(braket
l_int|0
)braket
op_amp
l_int|0x01
suffix:semicolon
r_int
id|new_x
op_assign
id|raw_data
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|new_y
op_assign
id|raw_data
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|raw_data
(braket
l_int|0
)braket
op_amp
l_int|0x10
)paren
(brace
id|new_x
op_add_assign
l_int|128
suffix:semicolon
)brace
r_if
c_cond
(paren
id|raw_data
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
(brace
id|new_x
op_add_assign
l_int|256
suffix:semicolon
)brace
r_if
c_cond
(paren
id|raw_data
(braket
l_int|0
)braket
op_amp
l_int|0x08
)paren
(brace
id|new_y
op_add_assign
l_int|128
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|raw_x
op_ne
id|new_x
)paren
op_logical_or
(paren
id|raw_y
op_ne
id|new_y
)paren
)paren
(brace
id|raw_x
op_assign
id|new_x
suffix:semicolon
id|raw_y
op_assign
id|new_y
suffix:semicolon
id|xy_pending
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_down
op_ne
id|raw_down
)paren
(brace
multiline_comment|/* Down state has changed.  raw_down always holds&n;&t;&t;&t; * the most recently observed state.&n;&t;&t;&t; */
id|raw_down
op_assign
id|new_down
suffix:semicolon
multiline_comment|/* Forget any earlier bounce processing */
r_if
c_cond
(paren
id|bounce
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|bounce_timer
)paren
suffix:semicolon
id|bounce
op_assign
id|NO_BOUNCE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_down
)paren
(brace
r_if
c_cond
(paren
id|debounced_down
)paren
(brace
multiline_comment|/* pad gone down, but we were reporting&n;&t;&t;&t;&t;&t; * it down anyway because we suspected&n;&t;&t;&t;&t;&t; * (correctly) that the last up was just&n;&t;&t;&t;&t;&t; * a bounce&n;&t;&t;&t;&t;&t; */
)brace
r_else
(brace
id|bounce
op_assign
id|JUST_GONE_DOWN
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|bounce_timer
comma
id|jiffies
op_plus
id|current_params.bounce_interval
)paren
suffix:semicolon
multiline_comment|/* start new stroke/tap */
id|debounced_down
op_assign
id|new_down
suffix:semicolon
id|notify_pad_up_down
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
multiline_comment|/* just gone up */
(brace
r_if
c_cond
(paren
id|recent_transition
)paren
(brace
multiline_comment|/* early bounces are probably part of&n;&t;&t;&t;&t;&t; * a multi-tap gesture, so process&n;&t;&t;&t;&t;&t; * immediately&n;&t;&t;&t;&t;&t; */
id|debounced_down
op_assign
id|new_down
suffix:semicolon
id|notify_pad_up_down
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* don&squot;t trust it yet */
id|bounce
op_assign
id|JUST_GONE_UP
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|bounce_timer
comma
id|jiffies
op_plus
id|current_params.bounce_interval
)paren
suffix:semicolon
)brace
)brace
)brace
id|wake_readers
c_func
(paren
)paren
suffix:semicolon
id|raw_data_count
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;read_raw_pad:&n; *&t;@down: set if the pen is down&n; *&t;@debounced: set if the debounced pen position is down&n; *&t;@x: X position&n; *&t;@y: Y position&n; *&n; *&t;Retrieve the data saved by the interrupt handler and indicate we&n; *&t;have no more pending XY to do. &n; *&n; *&t;FIXME: We should switch to a spinlock for this.&n; */
DECL|function|read_raw_pad
r_static
r_void
id|read_raw_pad
c_func
(paren
r_int
op_star
id|down
comma
r_int
op_star
id|debounced
comma
r_int
op_star
id|x
comma
r_int
op_star
id|y
)paren
(brace
id|disable_irq
c_func
(paren
id|current_params.irq
)paren
suffix:semicolon
(brace
op_star
id|down
op_assign
id|raw_down
suffix:semicolon
op_star
id|debounced
op_assign
id|debounced_down
suffix:semicolon
op_star
id|x
op_assign
id|raw_x
suffix:semicolon
op_star
id|y
op_assign
id|raw_y
suffix:semicolon
id|xy_pending
op_assign
l_int|0
suffix:semicolon
)brace
id|enable_irq
c_func
(paren
id|current_params.irq
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Filesystem interface&n; */
multiline_comment|/* &n; * Read returns byte triples, so we need to keep track of&n; * how much of a triple has been read.  This is shared across&n; * all processes which have this device open---not that anything&n; * will make much sense in that case.&n; */
DECL|variable|read_bytes
r_static
r_int
id|read_bytes
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|read_byte_count
r_static
r_int
id|read_byte_count
suffix:semicolon
multiline_comment|/**&n; *&t;sample_raw:&n; *&t;@d: sample buffer&n; *&n; *&t;Retrieve a triple of sample data. &n; */
DECL|function|sample_raw
r_static
r_void
id|sample_raw
c_func
(paren
r_int
id|d
(braket
l_int|3
)braket
)paren
(brace
id|d
(braket
l_int|0
)braket
op_assign
id|raw_data
(braket
l_int|0
)braket
suffix:semicolon
id|d
(braket
l_int|1
)braket
op_assign
id|raw_data
(braket
l_int|1
)braket
suffix:semicolon
id|d
(braket
l_int|2
)braket
op_assign
id|raw_data
(braket
l_int|2
)braket
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sample_rare:&n; *&t;@d: sample buffer&n; *&n; *&t;Retrieve a triple of sample data and sanitize it. We do the needed&n; *&t;scaling and masking to get the current status.&n; */
DECL|function|sample_rare
r_static
r_void
id|sample_rare
c_func
(paren
r_int
id|d
(braket
l_int|3
)braket
)paren
(brace
r_int
id|thisd
comma
id|thisdd
comma
id|thisx
comma
id|thisy
suffix:semicolon
id|read_raw_pad
c_func
(paren
op_amp
id|thisd
comma
op_amp
id|thisdd
comma
op_amp
id|thisx
comma
op_amp
id|thisy
)paren
suffix:semicolon
id|d
(braket
l_int|0
)braket
op_assign
(paren
id|thisd
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
op_or
(paren
id|thisx
op_div
l_int|256
)paren
op_lshift
l_int|4
op_or
(paren
id|thisdd
ques
c_cond
l_int|0x08
suffix:colon
l_int|0
)paren
op_or
(paren
id|thisy
op_div
l_int|256
)paren
suffix:semicolon
id|d
(braket
l_int|1
)braket
op_assign
id|thisx
op_mod
l_int|256
suffix:semicolon
id|d
(braket
l_int|2
)braket
op_assign
id|thisy
op_mod
l_int|256
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sample_debug:&n; *&t;@d: sample buffer&n; *&n; *&t;Retrieve a triple of sample data and mix it up with the state &n; *&t;information in the gesture parser. Not useful for normal users but&n; *&t;handy when debugging&n; */
DECL|function|sample_debug
r_static
r_void
id|sample_debug
c_func
(paren
r_int
id|d
(braket
l_int|3
)braket
)paren
(brace
r_int
id|thisd
comma
id|thisdd
comma
id|thisx
comma
id|thisy
suffix:semicolon
r_int
id|b
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|read_raw_pad
c_func
(paren
op_amp
id|thisd
comma
op_amp
id|thisdd
comma
op_amp
id|thisx
comma
op_amp
id|thisy
)paren
suffix:semicolon
id|d
(braket
l_int|0
)braket
op_assign
(paren
id|thisd
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
op_or
(paren
id|thisdd
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
op_or
id|bounce
suffix:semicolon
id|d
(braket
l_int|1
)braket
op_assign
(paren
id|recent_transition
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
op_plus
id|transition_count
suffix:semicolon
id|read_button
c_func
(paren
op_amp
id|b
)paren
suffix:semicolon
id|d
(braket
l_int|2
)braket
op_assign
(paren
id|synthesize_tap
op_lshift
l_int|4
)paren
op_or
(paren
id|b
ques
c_cond
l_int|0x01
suffix:colon
l_int|0
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sample_ps2:&n; *&t;@d: sample buffer&n; *&n; *&t;Retrieve a triple of sample data and turn the debounced tap and&n; *&t;stroke information into what appears to be a PS/2 mouse. This means&n; *&t;the PC110 pad needs no funny application side support.&n; */
DECL|function|sample_ps2
r_static
r_void
id|sample_ps2
c_func
(paren
r_int
id|d
(braket
l_int|3
)braket
)paren
(brace
r_static
r_int
id|lastx
comma
id|lasty
comma
id|lastd
suffix:semicolon
r_int
id|thisd
comma
id|thisdd
comma
id|thisx
comma
id|thisy
suffix:semicolon
r_int
id|dx
comma
id|dy
comma
id|b
suffix:semicolon
multiline_comment|/*&n;&t; * Obtain the current mouse parameters and limit as appropriate for&n;&t; * the return data format.  Interrupts are only disabled while &n;&t; * obtaining the parameters, NOT during the puts_fs_byte() calls,&n;&t; * so paging in put_user() does not affect mouse tracking.&n;&t; */
id|read_raw_pad
c_func
(paren
op_amp
id|thisd
comma
op_amp
id|thisdd
comma
op_amp
id|thisx
comma
op_amp
id|thisy
)paren
suffix:semicolon
id|read_button
c_func
(paren
op_amp
id|b
)paren
suffix:semicolon
multiline_comment|/* Now compare with previous readings.  Note that we use the&n;&t; * raw down flag rather than the debounced one.&n;&t; */
r_if
c_cond
(paren
(paren
id|thisd
op_logical_and
op_logical_neg
id|lastd
)paren
multiline_comment|/* new stroke */
op_logical_or
(paren
id|bounce
op_ne
id|NO_BOUNCE
)paren
)paren
(brace
id|dx
op_assign
l_int|0
suffix:semicolon
id|dy
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dx
op_assign
(paren
id|thisx
op_minus
id|lastx
)paren
suffix:semicolon
id|dy
op_assign
op_minus
(paren
id|thisy
op_minus
id|lasty
)paren
suffix:semicolon
)brace
id|lastx
op_assign
id|thisx
suffix:semicolon
id|lasty
op_assign
id|thisy
suffix:semicolon
id|lastd
op_assign
id|thisd
suffix:semicolon
multiline_comment|/*&n;&t;d[0]= ((dy&lt;0)?0x20:0)&n;&t;    | ((dx&lt;0)?0x10:0)&n;&t;    | 0x08&n;&t;    | (b? 0x01:0x00)&n;&t;;&n;*/
id|d
(braket
l_int|0
)braket
op_assign
(paren
(paren
id|dy
OL
l_int|0
)paren
ques
c_cond
l_int|0x20
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|dx
OL
l_int|0
)paren
ques
c_cond
l_int|0x10
suffix:colon
l_int|0
)paren
op_or
(paren
id|b
ques
c_cond
l_int|0x00
suffix:colon
l_int|0x08
)paren
suffix:semicolon
id|d
(braket
l_int|1
)braket
op_assign
id|dx
suffix:semicolon
id|d
(braket
l_int|2
)braket
op_assign
id|dy
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fasync_pad:&n; *&t;@fd:&t;file number for the file &n; *&t;@filp:&t;file handle&n; *&t;@on:&t;1 to add, 0 to remove a notifier&n; *&n; *&t;Update the queue of asynchronous event notifiers. We can use the&n; *&t;same helper the mice do and that does almost everything we need.&n; */
DECL|function|fasync_pad
r_static
r_int
id|fasync_pad
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
r_int
id|retval
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
op_amp
id|asyncptr
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
multiline_comment|/**&n; *&t;close_pad:&n; *&t;@inode: inode of pad&n; *&t;@file: file handle to pad&n; *&n; *&t;Close access to the pad. We turn the pad power off if this is the&n; *&t;last user of the pad. I&squot;ve not actually measured the power draw but&n; *&t;the DOS driver is careful to do this so we follow suit.&n; */
DECL|function|close_pad
r_static
r_int
id|close_pad
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
id|fasync_pad
c_func
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|active_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|active_count
)paren
id|outb
c_func
(paren
l_int|0x30
comma
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* switch off digitiser */
id|spin_unlock
c_func
(paren
op_amp
id|active_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;open_pad:&n; *&t;@inode: inode of pad&n; *&t;@file: file handle to pad&n; *&n; *&t;Open access to the pad. We turn the pad off first (we turned it off&n; *&t;on close but if this is the first open after a crash the state is&n; *&t;indeterminate). The device has a small fifo so we empty that before&n; *&t;we kick it back into action.&n; */
DECL|function|open_pad
r_static
r_int
id|open_pad
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
id|flags
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|active_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_count
op_increment
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|active_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|active_lock
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x30
comma
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* switch off digitiser */
id|pad_irq
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* read to flush any pending bytes */
id|pad_irq
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* read to flush any pending bytes */
id|pad_irq
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* read to flush any pending bytes */
id|outb
c_func
(paren
l_int|0x38
comma
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* switch on digitiser */
id|current_params
op_assign
id|default_params
suffix:semicolon
id|raw_data_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* re-sync input byte counter */
id|read_byte_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* re-sync output byte counter */
id|button_pending
op_assign
l_int|0
suffix:semicolon
id|recent_transition
op_assign
l_int|0
suffix:semicolon
id|transition_count
op_assign
l_int|0
suffix:semicolon
id|synthesize_tap
op_assign
l_int|0
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|bounce_timer
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|tap_timer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;write_pad:&n; *&t;@file: File handle to the pad&n; *&t;@buffer: Unused&n; *&t;@count: Unused&n; *&t;@ppos: Unused&n; *&n; *&t;Writes are disallowed. A true PS/2 mouse lets you write stuff. Everyone&n; *&t;seems happy with this and not faking the write modes.&n; */
DECL|function|write_pad
r_static
id|ssize_t
id|write_pad
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
id|buffer
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
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;new_sample:&n; *&t;@d: sample buffer&n; *&n; *&t;Fetch a new sample according the current mouse mode the pad is &n; *&t;using.&n; */
DECL|function|new_sample
r_void
id|new_sample
c_func
(paren
r_int
id|d
(braket
l_int|3
)braket
)paren
(brace
r_switch
c_cond
(paren
id|current_params.mode
)paren
(brace
r_case
id|PC110PAD_RAW
suffix:colon
id|sample_raw
c_func
(paren
id|d
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PC110PAD_RARE
suffix:colon
id|sample_rare
c_func
(paren
id|d
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PC110PAD_DEBUG
suffix:colon
id|sample_debug
c_func
(paren
id|d
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PC110PAD_PS2
suffix:colon
id|sample_ps2
c_func
(paren
id|d
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * read_pad:&n; * @file: File handle to pad&n; * @buffer: Target for the mouse data&n; * @count: Buffer length&n; * @ppos: Offset (unused)&n; *&n; * Read data from the pad. We use the reader_lock to avoid mess when there are&n; * two readers. This shouldnt be happening anyway but we play safe.&n; */
DECL|function|read_pad
r_static
id|ssize_t
id|read_pad
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
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
id|r
suffix:semicolon
id|down
c_func
(paren
op_amp
id|reader_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|r
OL
id|count
suffix:semicolon
id|r
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|read_byte_count
)paren
(brace
id|new_sample
c_func
(paren
id|read_bytes
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|read_bytes
(braket
id|read_byte_count
)braket
comma
id|buffer
op_plus
id|r
)paren
)paren
(brace
id|r
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|read_byte_count
op_assign
(paren
id|read_byte_count
op_plus
l_int|1
)paren
op_mod
l_int|3
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|reader_lock
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/**&n; * pad_poll:&n; * @file: File of the pad device&n; * @wait: Poll table&n; *&n; * The pad is ready to read if there is a button or any position change&n; * pending in the queue. The reading and interrupt routines maintain the&n; * required state for us and do needed wakeups.&n; */
DECL|function|pad_poll
r_static
r_int
r_int
id|pad_poll
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
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|queue
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|button_pending
op_logical_or
id|xy_pending
)paren
(brace
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pad_ioctl;&n; *&t;@inode: Inode of the pad&n; *&t;@file: File handle to the pad&n; *&t;@cmd: Ioctl command&n; *&t;@arg: Argument pointer&n; *&n; *&t;The PC110 pad supports two ioctls both of which use the pc110pad_params&n; *&t;structure. GETP queries the current pad status. SETP changes the pad&n; *&t;configuration. Changing configuration during normal mouse operations&n; *&t;may give momentarily odd results as things like tap gesture state&n; *&t;may be lost.&n; */
DECL|function|pad_ioctl
r_static
r_int
id|pad_ioctl
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
id|pc110pad_params
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|PC110PADIOCGETP
suffix:colon
r_new
op_assign
id|current_params
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
r_new
comma
r_sizeof
(paren
r_new
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|PC110PADIOCSETP
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
r_new
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_new
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_new
dot
id|mode
OL
id|PC110PAD_RAW
)paren
op_logical_or
(paren
r_new
dot
id|mode
OG
id|PC110PAD_PS2
)paren
op_logical_or
(paren
r_new
dot
id|bounce_interval
OL
l_int|0
)paren
op_logical_or
(paren
r_new
dot
id|tap_interval
OL
l_int|0
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|current_params.mode
op_assign
r_new
dot
id|mode
suffix:semicolon
id|current_params.bounce_interval
op_assign
r_new
dot
id|bounce_interval
suffix:semicolon
id|current_params.tap_interval
op_assign
r_new
dot
id|tap_interval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
DECL|variable|pad_fops
r_static
r_struct
id|file_operations
id|pad_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|read_pad
comma
id|write
suffix:colon
id|write_pad
comma
id|poll
suffix:colon
id|pad_poll
comma
id|ioctl
suffix:colon
id|pad_ioctl
comma
id|open
suffix:colon
id|open_pad
comma
id|release
suffix:colon
id|close_pad
comma
id|fasync
suffix:colon
id|fasync_pad
comma
)brace
suffix:semicolon
DECL|variable|pc110_pad
r_static
r_struct
id|miscdevice
id|pc110_pad
op_assign
(brace
id|minor
suffix:colon
id|PC110PAD_MINOR
comma
id|name
suffix:colon
l_string|&quot;pc110 pad&quot;
comma
id|fops
suffix:colon
op_amp
id|pad_fops
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;pc110pad_init_driver:&n; *&n; *&t;We configure the pad with the default parameters (that is PS/2 &n; *&t;emulation mode. We then claim the needed I/O and interrupt resources.&n; *&t;Finally as a matter of paranoia we turn the pad off until we are&n; *&t;asked to open it by an application.&n; */
DECL|variable|__initdata
r_static
r_char
id|banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
l_string|&quot;PC110 digitizer pad at 0x%X, irq %d.&bslash;n&quot;
suffix:semicolon
DECL|function|pc110pad_init_driver
r_static
r_int
id|__init
id|pc110pad_init_driver
c_func
(paren
r_void
)paren
(brace
id|init_MUTEX
c_func
(paren
op_amp
id|reader_lock
)paren
suffix:semicolon
id|current_params
op_assign
id|default_params
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|current_params.irq
comma
id|pad_irq
comma
l_int|0
comma
l_string|&quot;pc110pad&quot;
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pc110pad: Unable to get IRQ.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|current_params.io
comma
l_int|4
comma
l_string|&quot;pc110pad&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pc110pad: I/O area in use.&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|current_params.irq
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|queue
)paren
suffix:semicolon
id|printk
c_func
(paren
id|banner
comma
id|current_params.io
comma
id|current_params.irq
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|pc110_pad
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x30
comma
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* switch off digitiser */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;pc110pad_exit_driver:&n; *&n; *&t;Free the resources we acquired when the module was loaded. We also&n; *&t;turn the pad off to be sure we don&squot;t leave it using power.&n; */
DECL|function|pc110pad_exit_driver
r_static
r_void
id|__exit
id|pc110pad_exit_driver
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0x30
comma
id|current_params.io
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* switch off digitiser */
r_if
c_cond
(paren
id|current_params.irq
)paren
id|free_irq
c_func
(paren
id|current_params.irq
comma
l_int|0
)paren
suffix:semicolon
id|current_params.irq
op_assign
l_int|0
suffix:semicolon
id|release_region
c_func
(paren
id|current_params.io
comma
l_int|4
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|pc110_pad
)paren
suffix:semicolon
)brace
DECL|variable|pc110pad_init_driver
id|module_init
c_func
(paren
id|pc110pad_init_driver
)paren
suffix:semicolon
DECL|variable|pc110pad_exit_driver
id|module_exit
c_func
(paren
id|pc110pad_exit_driver
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alan Cox, Robin O&squot;Leary&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for the touchpad on the IBM PC110 palmtop&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
eof
