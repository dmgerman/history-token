multiline_comment|/*&n; * Macintosh ADB Mouse driver for Linux&n; *&n; * 27 Oct 1997 Michael Schmitz&n; * logitech fixes by anthony tong&n; * further hacking by Paul Mackerras&n; *&n; * Apple mouse protocol according to:&n; *&n; * Device code shamelessly stolen from:&n; */
multiline_comment|/*&n; * Atari Mouse Driver for Linux&n; * by Robert de Vries (robert@and.nl) 19Jul93&n; *&n; * 16 Nov 1994 Andreas Schwab&n; * Compatibility with busmouse&n; * Support for three button mouse (shamelessly stolen from MiNT)&n; * third button wired to one of the joystick directions on joystick 1&n; *&n; * 1996/02/11 Andreas Schwab&n; * Module support&n; * Allow multiple open&squot;s&n; *&n; * Converted to use new generic busmouse code.  11 July 1998&n; *   Russell King &lt;rmk@arm.uk.linux.org&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/adb_mouse.h&gt;
macro_line|#ifdef __powerpc__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#endif
macro_line|#if defined(__mc68000__) || defined(MODULE)
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#endif
macro_line|#include &quot;busmouse.h&quot;
DECL|variable|msedev
r_static
r_int
id|msedev
suffix:semicolon
DECL|variable|adb_mouse_buttons
r_static
r_int
r_char
id|adb_mouse_buttons
(braket
l_int|16
)braket
suffix:semicolon
r_extern
r_void
(paren
op_star
id|adb_mouse_interrupt_hook
)paren
(paren
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|adb_emulate_buttons
suffix:semicolon
r_extern
r_int
id|adb_button2_keycode
suffix:semicolon
r_extern
r_int
id|adb_button3_keycode
suffix:semicolon
multiline_comment|/*&n; *    XXX: need to figure out what ADB mouse packets mean ... &n; *      This is the stuff stolen from the Atari driver ...&n; */
DECL|function|adb_mouse_interrupt
r_static
r_void
id|adb_mouse_interrupt
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
id|nb
)paren
(brace
r_int
id|buttons
comma
id|id
suffix:semicolon
r_char
id|dx
comma
id|dy
suffix:semicolon
multiline_comment|/*&n;&t;   Handler 1 -- 100cpi original Apple mouse protocol.&n;&t;   Handler 2 -- 200cpi original Apple mouse protocol.&n;&n;&t;   For Apple&squot;s standard one-button mouse protocol the data array will&n;&t;   contain the following values:&n;&n;&t;&t;       BITS    COMMENTS&n;&t;   data[0] = dddd 1100 ADB command: Talk, register 0, for device dddd.&n;&t;   data[1] = bxxx xxxx First button and x-axis motion.&n;&t;   data[2] = byyy yyyy Second button and y-axis motion.&n;&n;&t;   Handler 4 -- Apple Extended mouse protocol.&n;&n;&t;   For Apple&squot;s 3-button mouse protocol the data array will contain the&n;&t;   following values:&n;&n;&t;&t;       BITS    COMMENTS&n;&t;   data[0] = dddd 1100 ADB command: Talk, register 0, for device dddd.&n;&t;   data[1] = bxxx xxxx Left button and x-axis motion.&n;&t;   data[2] = byyy yyyy Second button and y-axis motion.&n;&t;   data[3] = byyy bxxx Third button and fourth button.  &n;&t;&t;   Y is additiona. high bits of y-axis motion.  &n;&t;&t;   X is additional high bits of x-axis motion.&n;&n;&t;   &squot;buttons&squot; here means &squot;button down&squot; states!&n;&t;   Button 1 (left)  : bit 2, busmouse button 3&n;&t;   Button 2 (right) : bit 0, busmouse button 1&n;&t;   Button 3 (middle): bit 1, busmouse button 2&n;&t; */
multiline_comment|/* x/y and buttons swapped */
id|id
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
suffix:semicolon
id|buttons
op_assign
id|adb_mouse_buttons
(braket
id|id
)braket
suffix:semicolon
multiline_comment|/* button 1 (left, bit 2) */
id|buttons
op_assign
(paren
id|buttons
op_amp
l_int|3
)paren
op_or
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 1+2 unchanged */
multiline_comment|/* button 2 (middle) */
id|buttons
op_assign
(paren
id|buttons
op_amp
l_int|5
)paren
op_or
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 2+3 unchanged */
multiline_comment|/* button 3 (right) present?&n;&t; *  on a logitech mouseman, the right and mid buttons sometimes behave&n;&t; *  strangely until they both have been pressed after booting. */
multiline_comment|/* data valid only if extended mouse format ! */
r_if
c_cond
(paren
id|nb
op_ge
l_int|4
)paren
id|buttons
op_assign
(paren
id|buttons
op_amp
l_int|6
)paren
op_or
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 1+3 unchanged */
id|adb_mouse_buttons
(braket
id|id
)braket
op_assign
id|buttons
suffix:semicolon
multiline_comment|/* a button is down if it is down on any mouse */
r_for
c_loop
(paren
id|id
op_assign
l_int|0
suffix:semicolon
id|id
OL
l_int|16
suffix:semicolon
op_increment
id|id
)paren
id|buttons
op_and_assign
id|adb_mouse_buttons
(braket
id|id
)braket
suffix:semicolon
id|dx
op_assign
(paren
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
OL
l_int|64
ques
c_cond
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
suffix:colon
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
op_minus
l_int|128
)paren
suffix:semicolon
id|dy
op_assign
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
OL
l_int|64
ques
c_cond
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
suffix:colon
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
op_minus
l_int|128
)paren
suffix:semicolon
id|busmouse_add_movementbuttons
c_func
(paren
id|msedev
comma
id|dx
comma
op_minus
id|dy
comma
id|buttons
)paren
suffix:semicolon
r_if
c_cond
(paren
id|console_loglevel
op_ge
l_int|8
)paren
id|printk
c_func
(paren
l_string|&quot; %X %X %X dx %d dy %d &bslash;n&quot;
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
comma
id|dx
comma
id|dy
)paren
suffix:semicolon
)brace
DECL|function|release_mouse
r_static
r_int
id|release_mouse
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
id|adb_mouse_interrupt_hook
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;FIXME?: adb_mouse_interrupt_hook may still be executing&n;&t; *&t;on another CPU.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|open_mouse
r_static
r_int
id|open_mouse
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
id|adb_mouse_interrupt_hook
op_assign
id|adb_mouse_interrupt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|adb_mouse
r_static
r_struct
id|busmouse
id|adb_mouse
op_assign
(brace
id|ADB_MOUSE_MINOR
comma
l_string|&quot;adbmouse&quot;
comma
id|THIS_MODULE
comma
id|open_mouse
comma
id|release_mouse
comma
l_int|7
)brace
suffix:semicolon
DECL|function|adb_mouse_init
r_static
r_int
id|__init
id|adb_mouse_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef __powerpc__
r_if
c_cond
(paren
(paren
id|_machine
op_ne
id|_MACH_chrp
)paren
op_logical_and
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __mc68000__
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
multiline_comment|/* all buttons up */
id|memset
c_func
(paren
id|adb_mouse_buttons
comma
l_int|7
comma
r_sizeof
(paren
id|adb_mouse_buttons
)paren
)paren
suffix:semicolon
id|msedev
op_assign
id|register_busmouse
c_func
(paren
op_amp
id|adb_mouse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msedev
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Unable to register ADB mouse driver.&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Macintosh ADB mouse driver installed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|msedev
OL
l_int|0
ques
c_cond
id|msedev
suffix:colon
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef MODULE
multiline_comment|/*&n; * XXX this function is misnamed.&n; * It is called if the kernel is booted with the adb_buttons=xxx&n; * option, which is about using ADB keyboard buttons to emulate&n; * mouse buttons. -- paulus&n; */
DECL|function|adb_mouse_setup
r_static
r_int
id|__init
id|adb_mouse_setup
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
l_int|4
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
op_ge
l_int|1
)paren
(brace
id|adb_emulate_buttons
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ge
l_int|2
)paren
id|adb_button2_keycode
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ge
l_int|3
)paren
id|adb_button3_keycode
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;adb_buttons=&quot;
comma
id|adb_mouse_setup
)paren
suffix:semicolon
macro_line|#endif /* !MODULE */
DECL|function|adb_mouse_cleanup
r_static
r_void
id|__exit
id|adb_mouse_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_busmouse
c_func
(paren
id|msedev
)paren
suffix:semicolon
)brace
DECL|variable|adb_mouse_init
id|module_init
c_func
(paren
id|adb_mouse_init
)paren
suffix:semicolon
DECL|variable|adb_mouse_cleanup
id|module_exit
c_func
(paren
id|adb_mouse_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
