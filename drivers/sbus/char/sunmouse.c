multiline_comment|/* sunmouse.c: Sun mouse driver for the Sparc&n; *&n; * Copyright (C) 1995, 1996, 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; *&n; * Parts based on the psaux.c driver written by:&n; * Johan Myreen.&n; *&n; * Dec/19/95 Added SunOS mouse ioctls - miguel.&n; * Jan/5/96  Added VUID support, sigio support - miguel.&n; * Mar/5/96  Added proper mouse stream support - miguel.&n; * Sep/96    Allow more than one reader -miguel.&n; * Aug/97    Added PCI 8042 controller support -DaveM&n; */
multiline_comment|/* The mouse is run off of one of the Zilog serial ports.  On&n; * that port is the mouse and the keyboard, each gets a zs channel.&n; * The mouse itself is mouse-systems in nature.  So the protocol is:&n; *&n; * Byte 1) Button state which is bit-encoded as&n; *            0x4 == left-button down, else up&n; *            0x2 == middle-button down, else up&n; *            0x1 == right-button down, else up&n; *&n; * Byte 2) Delta-x&n; * Byte 3) Delta-y&n; * Byte 4) Delta-x again&n; * Byte 5) Delta-y again&n; *&n; * One day this driver will have to support more than one mouse in the system.&n; *&n; * This driver has two modes of operation: the default VUID_NATIVE is&n; * set when the device is opened and allows the application to see the&n; * mouse character stream as we get it from the serial (for gpm for&n; * example).  The second method, VUID_FIRM_EVENT will provide cooked&n; * events in Firm_event records as expected by SunOS/Solaris applications.&n; *&n; * FIXME: We need to support more than one mouse.&n; * */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/vuid_event.h&gt;
macro_line|#include &lt;linux/random.h&gt;
multiline_comment|/* The following keeps track of software state for the Sun&n; * mouse.&n; */
DECL|macro|STREAM_SIZE
mdefine_line|#define STREAM_SIZE   2048
DECL|macro|EV_SIZE
mdefine_line|#define EV_SIZE       (STREAM_SIZE/sizeof (Firm_event))
DECL|macro|BUTTON_LEFT
mdefine_line|#define BUTTON_LEFT   4
DECL|macro|BUTTON_MIDDLE
mdefine_line|#define BUTTON_MIDDLE 2
DECL|macro|BUTTON_RIGHT
mdefine_line|#define BUTTON_RIGHT  1
DECL|struct|sun_mouse
r_struct
id|sun_mouse
(brace
DECL|member|transaction
r_int
r_char
id|transaction
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Each protocol transaction */
DECL|member|byte
r_int
r_char
id|byte
suffix:semicolon
multiline_comment|/* Counter, starts at 0 */
DECL|member|button_state
r_int
r_char
id|button_state
suffix:semicolon
multiline_comment|/* Current button state */
DECL|member|prev_state
r_int
r_char
id|prev_state
suffix:semicolon
multiline_comment|/* Previous button state */
DECL|member|delta_x
r_int
id|delta_x
suffix:semicolon
multiline_comment|/* Current delta-x */
DECL|member|delta_y
r_int
id|delta_y
suffix:semicolon
multiline_comment|/* Current delta-y */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* set if device is open */
DECL|member|vuid_mode
r_int
id|vuid_mode
suffix:semicolon
multiline_comment|/* VUID_NATIVE or VUID_FIRM_EVENT */
DECL|member|proc_list
id|wait_queue_head_t
id|proc_list
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
multiline_comment|/* The event/stream queue */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
r_union
(brace
DECL|member|stream
r_char
id|stream
(braket
id|STREAM_SIZE
)braket
suffix:semicolon
DECL|member|ev
id|Firm_event
id|ev
(braket
id|EV_SIZE
)braket
suffix:semicolon
DECL|member|queue
)brace
id|queue
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sunmouse
r_static
r_struct
id|sun_mouse
id|sunmouse
suffix:semicolon
DECL|macro|gen_events
mdefine_line|#define gen_events (sunmouse.vuid_mode != VUID_NATIVE)
DECL|macro|bstate
mdefine_line|#define bstate sunmouse.button_state
DECL|macro|pstate
mdefine_line|#define pstate sunmouse.prev_state
r_extern
r_void
id|mouse_put_char
c_func
(paren
r_char
id|ch
)paren
suffix:semicolon
DECL|macro|SMOUSE_DEBUG
macro_line|#undef SMOUSE_DEBUG
r_static
r_int
DECL|function|push_event
id|push_event
(paren
id|Firm_event
op_star
id|ev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|next
comma
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
id|next
op_assign
(paren
id|sunmouse.head
op_plus
l_int|1
)paren
op_mod
id|EV_SIZE
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ne
id|sunmouse.tail
)paren
(brace
id|sunmouse.queue.ev
(braket
id|sunmouse.head
)braket
op_assign
op_star
id|ev
suffix:semicolon
id|sunmouse.head
op_assign
id|next
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|queue_empty
id|queue_empty
(paren
r_void
)paren
(brace
r_return
id|sunmouse.head
op_eq
id|sunmouse.tail
suffix:semicolon
)brace
multiline_comment|/* Must be invoked under the sunmouse.lock */
DECL|function|get_from_queue
r_static
r_void
id|get_from_queue
(paren
id|Firm_event
op_star
id|p
)paren
(brace
op_star
id|p
op_assign
id|sunmouse.queue.ev
(braket
id|sunmouse.tail
)braket
suffix:semicolon
id|sunmouse.tail
op_assign
(paren
id|sunmouse.tail
op_plus
l_int|1
)paren
op_mod
id|EV_SIZE
suffix:semicolon
)brace
r_static
r_void
DECL|function|push_char
id|push_char
(paren
r_char
id|c
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|next
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
id|next
op_assign
(paren
id|sunmouse.head
op_plus
l_int|1
)paren
op_mod
id|STREAM_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ne
id|sunmouse.tail
)paren
(brace
macro_line|#ifdef SMOUSE_DEBUG
id|printk
c_func
(paren
l_string|&quot;P&lt;%02x&gt;&bslash;n&quot;
comma
(paren
r_int
r_char
)paren
id|c
)paren
suffix:semicolon
macro_line|#endif
id|sunmouse.queue.stream
(braket
id|sunmouse.head
)braket
op_assign
id|c
suffix:semicolon
id|sunmouse.head
op_assign
id|next
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
id|kill_fasync
(paren
op_amp
id|sunmouse.fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
(paren
op_amp
id|sunmouse.proc_list
)paren
suffix:semicolon
)brace
multiline_comment|/* Auto baud rate &quot;detection&quot;.  ;-) */
DECL|variable|mouse_baud
r_static
r_int
id|mouse_baud
op_assign
l_int|4800
suffix:semicolon
multiline_comment|/* Initial rate set by zilog driver. */
multiline_comment|/* Change the baud rate after receiving too many &quot;bogon bytes&quot;. */
DECL|function|sun_mouse_change_baud
r_void
id|sun_mouse_change_baud
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|rs_change_mouse_baud
c_func
(paren
r_int
id|newbaud
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mouse_baud
op_eq
l_int|1200
)paren
(brace
id|mouse_baud
op_assign
l_int|2400
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mouse_baud
op_eq
l_int|2400
)paren
(brace
id|mouse_baud
op_assign
l_int|4800
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mouse_baud
op_eq
l_int|4800
)paren
(brace
id|mouse_baud
op_assign
l_int|9600
suffix:semicolon
)brace
r_else
id|mouse_baud
op_assign
l_int|1200
suffix:semicolon
id|rs_change_mouse_baud
c_func
(paren
id|mouse_baud
)paren
suffix:semicolon
)brace
multiline_comment|/* This tries to monitor the mouse state so that it&n; * can automatically adjust to the correct baud rate.&n; * The mouse spits out BRKs when the baud rate is&n; * incorrect.&n; *&n; * It returns non-zero if we should ignore this byte.&n; */
DECL|function|mouse_baud_detection
r_int
id|mouse_baud_detection
c_func
(paren
r_int
r_char
id|c
comma
r_int
id|is_break
)paren
(brace
r_static
r_int
id|mouse_got_break
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|ctr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_break
)paren
(brace
multiline_comment|/* Let a few normal bytes go by before&n;&t;&t; * we jump the gun and say we need to&n;&t;&t; * try another baud rate.&n;&t;&t; */
r_if
c_cond
(paren
id|mouse_got_break
op_logical_and
id|ctr
OL
l_int|8
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* OK, we need to try another baud rate. */
id|sun_mouse_change_baud
c_func
(paren
)paren
suffix:semicolon
id|ctr
op_assign
l_int|0
suffix:semicolon
id|mouse_got_break
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mouse_got_break
)paren
(brace
id|ctr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_int|0x87
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sunmouse: Successfully &quot;
l_string|&quot;adjusted to %d baud.&bslash;n&quot;
comma
id|mouse_baud
)paren
suffix:semicolon
id|mouse_got_break
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* You ask me, why does this cap the lower bound at -127 and not&n; * -128?  Because the xf86 mouse code is crap and treats -128&n; * as an illegal value and resets it&squot;s protocol state machine&n; * when it sees this value.&n; */
DECL|macro|CLIP
mdefine_line|#define CLIP(__X)&t;(((__X) &gt; 127) ? 127 : (((__X) &lt; -127) ? -127 : (__X)))
multiline_comment|/* The following is called from the serial driver when bytes/breaks&n; * are received on the Mouse line.&n; */
r_void
DECL|function|sun_mouse_inbyte
id|sun_mouse_inbyte
c_func
(paren
r_int
r_char
id|byte
comma
r_int
id|is_break
)paren
(brace
r_int
r_char
id|mvalue
suffix:semicolon
r_int
id|d
comma
id|pushed
op_assign
l_int|0
suffix:semicolon
id|Firm_event
id|ev
suffix:semicolon
id|add_mouse_randomness
(paren
id|byte
)paren
suffix:semicolon
macro_line|#if 0
(brace
r_static
r_int
id|xxx
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mouse(%02x:%d) &quot;
comma
id|byte
comma
id|is_break
)paren
suffix:semicolon
r_if
c_cond
(paren
id|byte
op_eq
l_int|0x87
)paren
(brace
id|xxx
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|mouse_baud_detection
c_func
(paren
id|byte
comma
id|is_break
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sunmouse.active
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Ignore this if it is garbage. */
r_if
c_cond
(paren
id|sunmouse.byte
op_eq
l_int|69
)paren
(brace
r_if
c_cond
(paren
id|byte
op_ne
l_int|0x87
)paren
r_return
suffix:semicolon
multiline_comment|/* Ok, we&squot;ve begun the state machine. */
id|sunmouse.byte
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* If the mouse sends us a byte from 0x80 to 0x87&n;&t; * we are starting at byte zero in the transaction&n;&t; * protocol.&n;&t; */
r_if
c_cond
(paren
(paren
id|byte
op_amp
op_complement
l_int|0x0f
)paren
op_eq
l_int|0x80
)paren
(brace
id|sunmouse.byte
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|mvalue
op_assign
(paren
r_int
r_char
)paren
id|byte
suffix:semicolon
r_switch
c_cond
(paren
id|sunmouse.byte
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* If we get a bogus button byte, just skip it.&n;&t;&t; * When we get here the baud detection code has&n;&t;&t; * passed, so the only other things which can&n;&t;&t; * cause this are dropped serial characters and&n;&t;&t; * confused mouse.  We check this because otherwise&n;&t;&t; * begin posting erroneous mouse events.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|byte
op_amp
l_int|0xf0
)paren
op_ne
l_int|0x80
)paren
r_return
suffix:semicolon
multiline_comment|/* Button state */
id|sunmouse.button_state
op_assign
(paren
op_complement
id|byte
)paren
op_amp
l_int|0x7
suffix:semicolon
macro_line|#ifdef SMOUSE_DEBUG
id|printk
c_func
(paren
l_string|&quot;B&lt;Left %s, Middle %s, Right %s&gt;&quot;
comma
(paren
(paren
id|sunmouse.button_state
op_amp
l_int|0x4
)paren
ques
c_cond
l_string|&quot;DOWN&quot;
suffix:colon
l_string|&quot;UP&quot;
)paren
comma
(paren
(paren
id|sunmouse.button_state
op_amp
l_int|0x2
)paren
ques
c_cond
l_string|&quot;DOWN&quot;
suffix:colon
l_string|&quot;UP&quot;
)paren
comma
(paren
(paren
id|sunmouse.button_state
op_amp
l_int|0x1
)paren
ques
c_cond
l_string|&quot;DOWN&quot;
suffix:colon
l_string|&quot;UP&quot;
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* To deal with the Sparcbook 3 */
r_if
c_cond
(paren
id|byte
op_amp
l_int|0x8
)paren
(brace
id|sunmouse.byte
op_add_assign
l_int|2
suffix:semicolon
id|sunmouse.delta_y
op_assign
l_int|0
suffix:semicolon
id|sunmouse.delta_x
op_assign
l_int|0
suffix:semicolon
)brace
id|sunmouse.byte
op_increment
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Delta-x 1 */
macro_line|#ifdef SMOUSE_DEBUG
id|printk
c_func
(paren
l_string|&quot;DX1&lt;%d&gt;&quot;
comma
id|mvalue
)paren
suffix:semicolon
macro_line|#endif
id|sunmouse.delta_x
op_assign
id|mvalue
suffix:semicolon
id|sunmouse.byte
op_increment
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* Delta-y 1 */
macro_line|#ifdef SMOUSE_DEBUG
id|printk
c_func
(paren
l_string|&quot;DY1&lt;%d&gt;&quot;
comma
id|mvalue
)paren
suffix:semicolon
macro_line|#endif
id|sunmouse.delta_y
op_assign
id|mvalue
suffix:semicolon
id|sunmouse.byte
op_increment
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* Delta-x 2 */
macro_line|#ifdef SMOUSE_DEBUG
id|printk
c_func
(paren
l_string|&quot;DX2&lt;%d&gt;&quot;
comma
id|mvalue
)paren
suffix:semicolon
macro_line|#endif
id|sunmouse.delta_x
op_add_assign
id|mvalue
suffix:semicolon
id|sunmouse.delta_x
op_assign
id|CLIP
c_func
(paren
id|sunmouse.delta_x
)paren
suffix:semicolon
id|sunmouse.byte
op_increment
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* Last byte, Delta-y 2 */
macro_line|#ifdef SMOUSE_DEBUG
id|printk
c_func
(paren
l_string|&quot;DY2&lt;%d&gt;&quot;
comma
id|mvalue
)paren
suffix:semicolon
macro_line|#endif
id|sunmouse.delta_y
op_add_assign
id|mvalue
suffix:semicolon
id|sunmouse.delta_y
op_assign
id|CLIP
c_func
(paren
id|sunmouse.delta_y
)paren
suffix:semicolon
id|sunmouse.byte
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Back to button state */
r_break
suffix:semicolon
r_case
l_int|69
suffix:colon
multiline_comment|/* Until we get the (0x80 -&gt; 0x87) value we aren&squot;t&n;&t;&t; * in the middle of a real transaction, so just&n;&t;&t; * return.&n;&t;&t; */
r_return
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;sunmouse: bogon transaction state&bslash;n&quot;
)paren
suffix:semicolon
id|sunmouse.byte
op_assign
l_int|69
suffix:semicolon
multiline_comment|/* What could cause this? */
r_return
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gen_events
)paren
(brace
id|push_char
(paren
op_complement
id|sunmouse.button_state
op_amp
l_int|0x87
)paren
suffix:semicolon
id|push_char
(paren
id|sunmouse.delta_x
)paren
suffix:semicolon
id|push_char
(paren
id|sunmouse.delta_y
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|d
op_assign
id|bstate
op_xor
id|pstate
suffix:semicolon
id|pstate
op_assign
id|bstate
suffix:semicolon
r_if
c_cond
(paren
id|d
)paren
(brace
r_if
c_cond
(paren
id|d
op_amp
id|BUTTON_LEFT
)paren
(brace
id|ev.id
op_assign
id|MS_LEFT
suffix:semicolon
id|ev.value
op_assign
id|bstate
op_amp
id|BUTTON_LEFT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
op_amp
id|BUTTON_RIGHT
)paren
(brace
id|ev.id
op_assign
id|MS_RIGHT
suffix:semicolon
id|ev.value
op_assign
id|bstate
op_amp
id|BUTTON_RIGHT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
op_amp
id|BUTTON_MIDDLE
)paren
(brace
id|ev.id
op_assign
id|MS_MIDDLE
suffix:semicolon
id|ev.value
op_assign
id|bstate
op_amp
id|BUTTON_MIDDLE
suffix:semicolon
)brace
id|ev.time
op_assign
id|xtime
suffix:semicolon
id|ev.value
op_assign
id|ev.value
ques
c_cond
id|VKEY_DOWN
suffix:colon
id|VKEY_UP
suffix:semicolon
id|pushed
op_add_assign
id|push_event
(paren
op_amp
id|ev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sunmouse.delta_x
)paren
(brace
id|ev.id
op_assign
id|LOC_X_DELTA
suffix:semicolon
id|ev.time
op_assign
id|xtime
suffix:semicolon
id|ev.value
op_assign
id|sunmouse.delta_x
suffix:semicolon
id|pushed
op_add_assign
id|push_event
(paren
op_amp
id|ev
)paren
suffix:semicolon
id|sunmouse.delta_x
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sunmouse.delta_y
)paren
(brace
id|ev.id
op_assign
id|LOC_Y_DELTA
suffix:semicolon
id|ev.time
op_assign
id|xtime
suffix:semicolon
id|ev.value
op_assign
id|sunmouse.delta_y
suffix:semicolon
id|pushed
op_add_assign
id|push_event
(paren
op_amp
id|ev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pushed
op_ne
l_int|0
)paren
(brace
multiline_comment|/* We just completed a transaction, wake up whoever is awaiting&n;&t;&t; * this event.&n;&t;&t; */
id|kill_fasync
(paren
op_amp
id|sunmouse.fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|sunmouse.proc_list
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_static
r_int
DECL|function|sun_mouse_open
id|sun_mouse_open
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
id|spin_lock_irq
c_func
(paren
op_amp
id|sunmouse.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sunmouse.active
op_increment
)paren
r_goto
id|out
suffix:semicolon
id|sunmouse.delta_x
op_assign
id|sunmouse.delta_y
op_assign
l_int|0
suffix:semicolon
id|sunmouse.button_state
op_assign
l_int|0x80
suffix:semicolon
id|sunmouse.vuid_mode
op_assign
id|VUID_NATIVE
suffix:semicolon
id|out
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sunmouse.lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sun_mouse_fasync
r_static
r_int
id|sun_mouse_fasync
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
(paren
id|fd
comma
id|filp
comma
id|on
comma
op_amp
id|sunmouse.fasync
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
DECL|function|sun_mouse_close
id|sun_mouse_close
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
id|sun_mouse_fasync
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sunmouse.lock
)paren
suffix:semicolon
id|sunmouse.active
op_decrement
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sunmouse.lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|sun_mouse_write
id|sun_mouse_write
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
multiline_comment|/* foo on you */
)brace
r_static
id|ssize_t
DECL|function|sun_mouse_read
id|sun_mouse_read
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
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
(paren
)paren
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
id|add_wait_queue
(paren
op_amp
id|sunmouse.proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
(paren
op_amp
id|sunmouse.proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gen_events
)paren
(brace
r_char
op_star
id|p
op_assign
id|buffer
comma
op_star
id|end
op_assign
id|buffer
op_plus
id|count
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
op_logical_and
op_logical_neg
id|queue_empty
(paren
)paren
)paren
(brace
id|Firm_event
id|this_event
suffix:semicolon
id|get_from_queue
c_func
(paren
op_amp
id|this_event
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SPARC32_COMPAT
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|end
op_minus
id|p
)paren
OL
(paren
(paren
r_sizeof
(paren
id|Firm_event
)paren
op_minus
r_sizeof
(paren
r_struct
id|timeval
)paren
op_plus
(paren
r_sizeof
(paren
id|u32
)paren
op_star
l_int|2
)paren
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|Firm_event
op_star
)paren
id|p
comma
op_amp
id|this_event
comma
r_sizeof
(paren
id|Firm_event
)paren
op_minus
r_sizeof
(paren
r_struct
id|timeval
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|p
op_add_assign
r_sizeof
(paren
id|Firm_event
)paren
op_minus
r_sizeof
(paren
r_struct
id|timeval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|this_event.time.tv_sec
comma
(paren
id|u32
op_star
)paren
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|p
op_add_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|this_event.time.tv_usec
comma
(paren
id|u32
op_star
)paren
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|p
op_add_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif&t;
(brace
r_if
c_cond
(paren
(paren
id|end
op_minus
id|p
)paren
OL
r_sizeof
(paren
id|Firm_event
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|Firm_event
op_star
)paren
id|p
comma
op_amp
id|this_event
comma
r_sizeof
(paren
id|Firm_event
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|p
op_add_assign
r_sizeof
(paren
id|Firm_event
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|p
op_minus
id|buffer
suffix:semicolon
)brace
r_else
(brace
r_int
id|c
comma
id|limit
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|limit
)paren
id|limit
op_assign
id|count
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
l_int|0
suffix:semicolon
id|c
OL
id|limit
suffix:semicolon
id|c
op_increment
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
r_int
id|empty
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
)paren
(brace
id|empty
op_assign
l_int|1
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|val
op_assign
id|sunmouse.queue.stream
(braket
id|sunmouse.tail
)braket
suffix:semicolon
id|sunmouse.tail
op_assign
(paren
id|sunmouse.tail
op_plus
l_int|1
)paren
op_mod
id|STREAM_SIZE
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sunmouse.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|empty
)paren
r_break
suffix:semicolon
id|put_user
c_func
(paren
id|val
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
OL
id|count
)paren
(brace
r_if
c_cond
(paren
id|c
op_ge
l_int|5
)paren
r_break
suffix:semicolon
id|put_user
c_func
(paren
l_int|0
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_increment
suffix:semicolon
id|c
op_increment
suffix:semicolon
)brace
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/* Only called if nothing was sent */
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
id|ERESTARTSYS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sun_mouse_poll
r_static
r_int
r_int
id|sun_mouse_poll
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
id|sunmouse.proc_list
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue_empty
c_func
(paren
)paren
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
r_int
DECL|function|sun_mouse_ioctl
id|sun_mouse_ioctl
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
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* VUIDGFORMAT - Get input device byte stream format */
r_case
id|_IOR
c_func
(paren
l_char|&squot;v&squot;
comma
l_int|2
comma
r_int
)paren
suffix:colon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|sunmouse.vuid_mode
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* VUIDSFORMAT - Set input device byte stream format*/
r_case
id|_IOW
c_func
(paren
l_char|&squot;v&squot;
comma
l_int|1
comma
r_int
)paren
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|i
comma
(paren
r_int
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
id|i
op_eq
id|VUID_NATIVE
op_logical_or
id|i
op_eq
id|VUID_FIRM_EVENT
)paren
(brace
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|value
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sunmouse.lock
)paren
suffix:semicolon
id|sunmouse.vuid_mode
op_assign
id|value
suffix:semicolon
id|sunmouse.head
op_assign
id|sunmouse.tail
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sunmouse.lock
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8024540b
suffix:colon
r_case
l_int|0x40245408
suffix:colon
multiline_comment|/* This is a buggy application doing termios on the mouse driver */
multiline_comment|/* we ignore it.  I keep this check here so that we will notice   */
multiline_comment|/* future mouse vuid ioctls */
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[MOUSE-ioctl: %8.8x]&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sun_mouse_fops
r_struct
id|file_operations
id|sun_mouse_fops
op_assign
(brace
id|read
suffix:colon
id|sun_mouse_read
comma
id|write
suffix:colon
id|sun_mouse_write
comma
id|poll
suffix:colon
id|sun_mouse_poll
comma
id|ioctl
suffix:colon
id|sun_mouse_ioctl
comma
id|open
suffix:colon
id|sun_mouse_open
comma
id|release
suffix:colon
id|sun_mouse_close
comma
id|fasync
suffix:colon
id|sun_mouse_fasync
comma
)brace
suffix:semicolon
DECL|variable|sun_mouse_mouse
r_static
r_struct
id|miscdevice
id|sun_mouse_mouse
op_assign
(brace
id|SUN_MOUSE_MINOR
comma
l_string|&quot;sunmouse&quot;
comma
op_amp
id|sun_mouse_fops
)brace
suffix:semicolon
DECL|function|sun_mouse_zsinit
r_void
id|sun_mouse_zsinit
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Sun Mouse-Systems mouse driver version 1.00&bslash;n&quot;
)paren
suffix:semicolon
id|sunmouse.active
op_assign
l_int|0
suffix:semicolon
id|misc_register
(paren
op_amp
id|sun_mouse_mouse
)paren
suffix:semicolon
id|sunmouse.delta_x
op_assign
id|sunmouse.delta_y
op_assign
l_int|0
suffix:semicolon
id|sunmouse.button_state
op_assign
l_int|0x80
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sunmouse.proc_list
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|sunmouse.lock
)paren
suffix:semicolon
id|sunmouse.byte
op_assign
l_int|69
suffix:semicolon
)brace
eof
