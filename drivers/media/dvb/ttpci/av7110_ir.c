macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;av7110.h&quot;
DECL|macro|UP_TIMEOUT
mdefine_line|#define UP_TIMEOUT (HZ/4)
multiline_comment|/* enable ir debugging by or&squot;ing av7110_debug with 16 */
DECL|variable|input_dev
r_static
r_struct
id|input_dev
id|input_dev
suffix:semicolon
DECL|variable|ir_config
r_static
id|u32
id|ir_config
suffix:semicolon
DECL|variable|key_map
r_static
id|u16
id|key_map
(braket
l_int|256
)braket
op_assign
(brace
id|KEY_0
comma
id|KEY_1
comma
id|KEY_2
comma
id|KEY_3
comma
id|KEY_4
comma
id|KEY_5
comma
id|KEY_6
comma
id|KEY_7
comma
id|KEY_8
comma
id|KEY_9
comma
id|KEY_BACK
comma
l_int|0
comma
id|KEY_POWER
comma
id|KEY_MUTE
comma
l_int|0
comma
id|KEY_INFO
comma
id|KEY_VOLUMEUP
comma
id|KEY_VOLUMEDOWN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_CHANNELUP
comma
id|KEY_CHANNELDOWN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_TEXT
comma
l_int|0
comma
l_int|0
comma
id|KEY_TV
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_SETUP
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_SUBTITLE
comma
l_int|0
comma
l_int|0
comma
id|KEY_LANGUAGE
comma
l_int|0
comma
id|KEY_RADIO
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_EXIT
comma
l_int|0
comma
l_int|0
comma
id|KEY_UP
comma
id|KEY_DOWN
comma
id|KEY_LEFT
comma
id|KEY_RIGHT
comma
id|KEY_OK
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_RED
comma
id|KEY_GREEN
comma
id|KEY_YELLOW
comma
id|KEY_BLUE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_MENU
comma
id|KEY_LIST
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_UP
comma
id|KEY_UP
comma
id|KEY_DOWN
comma
id|KEY_DOWN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_EPG
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_VCR
)brace
suffix:semicolon
DECL|function|av7110_emit_keyup
r_static
r_void
id|av7110_emit_keyup
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
id|data
op_logical_or
op_logical_neg
id|test_bit
(paren
id|data
comma
id|input_dev.key
)paren
)paren
r_return
suffix:semicolon
id|input_event
(paren
op_amp
id|input_dev
comma
id|EV_KEY
comma
id|data
comma
op_logical_neg
op_logical_neg
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|keyup_timer
r_static
r_struct
id|timer_list
id|keyup_timer
op_assign
(brace
dot
id|function
op_assign
id|av7110_emit_keyup
)brace
suffix:semicolon
DECL|function|av7110_emit_key
r_static
r_void
id|av7110_emit_key
(paren
id|u32
id|ircom
)paren
(brace
id|u8
id|data
suffix:semicolon
id|u8
id|addr
suffix:semicolon
r_static
id|u16
id|old_toggle
op_assign
l_int|0
suffix:semicolon
id|u16
id|new_toggle
suffix:semicolon
id|u16
id|keycode
suffix:semicolon
multiline_comment|/* extract device address and data */
r_if
c_cond
(paren
id|ir_config
op_amp
l_int|0x0001
)paren
(brace
multiline_comment|/* TODO RCMM: ? bits device address, 8 bits data */
id|data
op_assign
id|ircom
op_amp
l_int|0xff
suffix:semicolon
id|addr
op_assign
(paren
id|ircom
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* RC5: 5 bits device address, 6 bits data */
id|data
op_assign
id|ircom
op_amp
l_int|0x3f
suffix:semicolon
id|addr
op_assign
(paren
id|ircom
op_rshift
l_int|6
)paren
op_amp
l_int|0x1f
suffix:semicolon
)brace
id|keycode
op_assign
id|key_map
(braket
id|data
)braket
suffix:semicolon
id|dprintk
c_func
(paren
l_int|16
comma
l_string|&quot;#########%08x######### addr %i data 0x%02x (keycode %i)&bslash;n&quot;
comma
id|ircom
comma
id|addr
comma
id|data
comma
id|keycode
)paren
suffix:semicolon
multiline_comment|/* check device address (if selected) */
r_if
c_cond
(paren
id|ir_config
op_amp
l_int|0x4000
)paren
r_if
c_cond
(paren
id|addr
op_ne
(paren
(paren
id|ir_config
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|keycode
)paren
(brace
id|printk
(paren
l_string|&quot;%s: unknown key 0x%02x!!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ir_config
op_amp
l_int|0x0001
)paren
id|new_toggle
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* RCMM */
r_else
id|new_toggle
op_assign
(paren
id|ircom
op_amp
l_int|0x800
)paren
suffix:semicolon
multiline_comment|/* RC5 */
r_if
c_cond
(paren
id|timer_pending
(paren
op_amp
id|keyup_timer
)paren
)paren
(brace
id|del_timer
(paren
op_amp
id|keyup_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|keyup_timer.data
op_ne
id|keycode
op_logical_or
id|new_toggle
op_ne
id|old_toggle
)paren
(brace
id|input_event
(paren
op_amp
id|input_dev
comma
id|EV_KEY
comma
id|keyup_timer.data
comma
op_logical_neg
op_logical_neg
l_int|0
)paren
suffix:semicolon
id|input_event
(paren
op_amp
id|input_dev
comma
id|EV_KEY
comma
id|keycode
comma
op_logical_neg
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|input_event
(paren
op_amp
id|input_dev
comma
id|EV_KEY
comma
id|keycode
comma
l_int|2
)paren
suffix:semicolon
)brace
r_else
id|input_event
(paren
op_amp
id|input_dev
comma
id|EV_KEY
comma
id|keycode
comma
op_logical_neg
l_int|0
)paren
suffix:semicolon
id|keyup_timer.expires
op_assign
id|jiffies
op_plus
id|UP_TIMEOUT
suffix:semicolon
id|keyup_timer.data
op_assign
id|keycode
suffix:semicolon
id|add_timer
(paren
op_amp
id|keyup_timer
)paren
suffix:semicolon
id|old_toggle
op_assign
id|new_toggle
suffix:semicolon
)brace
DECL|function|input_register_keys
r_static
r_void
id|input_register_keys
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|memset
(paren
id|input_dev.keybit
comma
l_int|0
comma
r_sizeof
(paren
id|input_dev.keybit
)paren
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
r_sizeof
(paren
id|key_map
)paren
op_div
r_sizeof
(paren
id|key_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|key_map
(braket
id|i
)braket
OG
id|KEY_MAX
)paren
id|key_map
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|key_map
(braket
id|i
)braket
OG
id|KEY_RESERVED
)paren
id|set_bit
(paren
id|key_map
(braket
id|i
)braket
comma
id|input_dev.keybit
)paren
suffix:semicolon
)brace
)brace
DECL|function|input_repeat_key
r_static
r_void
id|input_repeat_key
c_func
(paren
r_int
r_int
id|data
)paren
(brace
multiline_comment|/* dummy routine to disable autorepeat in the input driver */
)brace
DECL|function|av7110_ir_write_proc
r_static
r_int
id|av7110_ir_write_proc
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
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|page
suffix:semicolon
r_int
id|size
op_assign
l_int|4
op_plus
l_int|256
op_star
r_sizeof
(paren
id|u16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|page
comma
id|buffer
comma
id|size
)paren
)paren
(brace
id|vfree
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|memcpy
(paren
op_amp
id|ir_config
comma
id|page
comma
l_int|4
)paren
suffix:semicolon
id|memcpy
(paren
op_amp
id|key_map
comma
id|page
op_plus
l_int|4
comma
l_int|256
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|page
)paren
suffix:semicolon
id|av7110_setup_irc_config
(paren
l_int|NULL
comma
id|ir_config
)paren
suffix:semicolon
id|input_register_keys
(paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|av7110_ir_init
r_int
id|__init
id|av7110_ir_init
(paren
r_void
)paren
(brace
r_static
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
id|init_timer
(paren
op_amp
id|keyup_timer
)paren
suffix:semicolon
id|keyup_timer.data
op_assign
l_int|0
suffix:semicolon
id|input_dev.name
op_assign
l_string|&quot;DVB on-card IR receiver&quot;
suffix:semicolon
multiline_comment|/**&n;         *  enable keys&n;         */
id|set_bit
(paren
id|EV_KEY
comma
id|input_dev.evbit
)paren
suffix:semicolon
id|set_bit
(paren
id|EV_REP
comma
id|input_dev.evbit
)paren
suffix:semicolon
id|input_register_keys
(paren
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|input_dev
)paren
suffix:semicolon
id|input_dev.timer.function
op_assign
id|input_repeat_key
suffix:semicolon
id|av7110_setup_irc_config
(paren
l_int|NULL
comma
l_int|0x0001
)paren
suffix:semicolon
id|av7110_register_irc_handler
(paren
id|av7110_emit_key
)paren
suffix:semicolon
id|e
op_assign
id|create_proc_entry
(paren
l_string|&quot;av7110_ir&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
)paren
(brace
id|e-&gt;write_proc
op_assign
id|av7110_ir_write_proc
suffix:semicolon
id|e-&gt;size
op_assign
l_int|4
op_plus
l_int|256
op_star
r_sizeof
(paren
id|u16
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|av7110_ir_exit
r_void
id|__exit
id|av7110_ir_exit
(paren
r_void
)paren
(brace
id|del_timer_sync
c_func
(paren
op_amp
id|keyup_timer
)paren
suffix:semicolon
id|remove_proc_entry
(paren
l_string|&quot;av7110_ir&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|av7110_unregister_irc_handler
(paren
id|av7110_emit_key
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|input_dev
)paren
suffix:semicolon
)brace
singleline_comment|//MODULE_AUTHOR(&quot;Holger Waechtler &lt;holger@convergence.de&gt;&quot;);
singleline_comment|//MODULE_LICENSE(&quot;GPL&quot;);
eof
