multiline_comment|/*&n; *&t;$Id: maple_keyb.c,v 1.1 2001/11/02 17:27:32 jsimmons Exp $&n; * &t;SEGA Dreamcast keyboard driver&n; *&t;Based on drivers/usb/usbkbd.c&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/maple.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;YAEGASHI Takeshi &lt;t@keshi.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SEGA Dreamcast keyboard driver&quot;
)paren
suffix:semicolon
DECL|variable|dc_kbd_keycode
r_static
r_int
r_char
id|dc_kbd_keycode
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|30
comma
l_int|48
comma
l_int|46
comma
l_int|32
comma
l_int|18
comma
l_int|33
comma
l_int|34
comma
l_int|35
comma
l_int|23
comma
l_int|36
comma
l_int|37
comma
l_int|38
comma
l_int|50
comma
l_int|49
comma
l_int|24
comma
l_int|25
comma
l_int|16
comma
l_int|19
comma
l_int|31
comma
l_int|20
comma
l_int|22
comma
l_int|47
comma
l_int|17
comma
l_int|45
comma
l_int|21
comma
l_int|44
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|28
comma
l_int|1
comma
l_int|14
comma
l_int|15
comma
l_int|57
comma
l_int|12
comma
l_int|13
comma
l_int|26
comma
l_int|27
comma
l_int|43
comma
l_int|84
comma
l_int|39
comma
l_int|40
comma
l_int|41
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|58
comma
l_int|59
comma
l_int|60
comma
l_int|61
comma
l_int|62
comma
l_int|63
comma
l_int|64
comma
l_int|65
comma
l_int|66
comma
l_int|67
comma
l_int|68
comma
l_int|87
comma
l_int|88
comma
l_int|99
comma
l_int|70
comma
l_int|119
comma
l_int|110
comma
l_int|102
comma
l_int|104
comma
l_int|111
comma
l_int|107
comma
l_int|109
comma
l_int|106
comma
l_int|105
comma
l_int|108
comma
l_int|103
comma
l_int|69
comma
l_int|98
comma
l_int|55
comma
l_int|74
comma
l_int|78
comma
l_int|96
comma
l_int|79
comma
l_int|80
comma
l_int|81
comma
l_int|75
comma
l_int|76
comma
l_int|77
comma
l_int|71
comma
l_int|72
comma
l_int|73
comma
l_int|82
comma
l_int|83
comma
l_int|86
comma
l_int|127
comma
l_int|116
comma
l_int|117
comma
l_int|85
comma
l_int|89
comma
l_int|90
comma
l_int|91
comma
l_int|92
comma
l_int|93
comma
l_int|94
comma
l_int|95
comma
l_int|120
comma
l_int|121
comma
l_int|122
comma
l_int|123
comma
l_int|134
comma
l_int|138
comma
l_int|130
comma
l_int|132
comma
l_int|128
comma
l_int|129
comma
l_int|131
comma
l_int|137
comma
l_int|133
comma
l_int|135
comma
l_int|136
comma
l_int|113
comma
l_int|115
comma
l_int|114
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|124
comma
l_int|0
comma
l_int|181
comma
l_int|182
comma
l_int|183
comma
l_int|184
comma
l_int|185
comma
l_int|186
comma
l_int|187
comma
l_int|188
comma
l_int|189
comma
l_int|190
comma
l_int|191
comma
l_int|192
comma
l_int|193
comma
l_int|194
comma
l_int|195
comma
l_int|196
comma
l_int|197
comma
l_int|198
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
l_int|29
comma
l_int|42
comma
l_int|56
comma
l_int|125
comma
l_int|97
comma
l_int|54
comma
l_int|100
comma
l_int|126
comma
l_int|164
comma
l_int|166
comma
l_int|165
comma
l_int|163
comma
l_int|161
comma
l_int|115
comma
l_int|114
comma
l_int|113
comma
l_int|150
comma
l_int|158
comma
l_int|159
comma
l_int|128
comma
l_int|136
comma
l_int|177
comma
l_int|178
comma
l_int|176
comma
l_int|142
comma
l_int|152
comma
l_int|173
comma
l_int|140
)brace
suffix:semicolon
DECL|struct|dc_kbd
r_struct
id|dc_kbd
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|new
r_int
r_char
r_new
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|old
r_int
r_char
id|old
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
)brace
suffix:semicolon
DECL|function|dc_scan_kbd
r_static
r_void
id|dc_scan_kbd
c_func
(paren
r_struct
id|dc_kbd
op_star
id|kbd
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|kbd-&gt;dev
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
id|input_report_key
c_func
(paren
id|dev
comma
id|dc_kbd_keycode
(braket
id|i
op_plus
l_int|224
)braket
comma
(paren
id|kbd
op_member_access_from_pointer
r_new
(braket
l_int|0
)braket
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kbd-&gt;old
(braket
id|i
)braket
OG
l_int|3
op_logical_and
id|memscan
c_func
(paren
id|kbd
op_member_access_from_pointer
r_new
op_plus
l_int|2
comma
id|kbd-&gt;old
(braket
id|i
)braket
comma
l_int|6
)paren
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dc_kbd_keycode
(braket
id|kbd-&gt;old
(braket
id|i
)braket
)braket
)paren
(brace
id|input_report_key
c_func
(paren
id|dev
comma
id|dc_kbd_keycode
(braket
id|kbd-&gt;old
(braket
id|i
)braket
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Unknown key (scancode %#x) released.&quot;
comma
id|kbd-&gt;old
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
OG
l_int|3
op_logical_and
id|memscan
c_func
(paren
id|kbd-&gt;old
op_plus
l_int|2
comma
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
comma
l_int|6
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dc_kbd_keycode
(braket
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
)braket
)paren
(brace
id|input_report_key
c_func
(paren
id|dev
comma
id|dc_kbd_keycode
(braket
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Unknown key (scancode %#x) pressed.&quot;
comma
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|memcpy
c_func
(paren
id|kbd-&gt;old
comma
id|kbd
op_member_access_from_pointer
r_new
comma
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|dc_kbd_callback
r_static
r_void
id|dc_kbd_callback
c_func
(paren
r_struct
id|mapleq
op_star
id|mq
)paren
(brace
r_struct
id|maple_device
op_star
id|mapledev
op_assign
id|mq-&gt;dev
suffix:semicolon
r_struct
id|dc_kbd
op_star
id|kbd
op_assign
id|mapledev-&gt;private_data
suffix:semicolon
r_int
r_int
op_star
id|buf
op_assign
id|mq-&gt;recvbuf
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|1
)braket
op_eq
id|mapledev-&gt;function
)paren
(brace
id|memcpy
c_func
(paren
id|kbd
op_member_access_from_pointer
r_new
comma
id|buf
op_plus
l_int|2
comma
l_int|8
)paren
suffix:semicolon
id|dc_scan_kbd
c_func
(paren
id|kbd
)paren
suffix:semicolon
)brace
)brace
DECL|function|dc_kbd_open
r_static
r_int
id|dc_kbd_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|dc_kbd
op_star
id|kbd
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|kbd-&gt;open
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dc_kbd_close
r_static
r_void
id|dc_kbd_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|dc_kbd
op_star
id|kbd
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|kbd-&gt;open
op_decrement
suffix:semicolon
)brace
DECL|function|dc_kbd_connect
r_static
r_int
id|dc_kbd_connect
c_func
(paren
r_struct
id|maple_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|data
op_assign
id|be32_to_cpu
c_func
(paren
id|dev-&gt;devinfo.function_data
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_struct
id|dc_kbd
op_star
id|kbd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|kbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dc_kbd
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|kbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dc_kbd
)paren
)paren
suffix:semicolon
id|dev-&gt;private_data
op_assign
id|kbd
suffix:semicolon
id|kbd-&gt;dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_REP
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
l_int|255
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|dc_kbd_keycode
(braket
id|i
)braket
comma
id|kbd-&gt;dev.keybit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
id|kbd-&gt;dev.keybit
)paren
suffix:semicolon
id|kbd-&gt;dev
dot
r_private
op_assign
id|kbd
suffix:semicolon
id|kbd-&gt;dev.open
op_assign
id|dc_kbd_open
suffix:semicolon
id|kbd-&gt;dev.close
op_assign
id|dc_kbd_close
suffix:semicolon
id|kbd-&gt;dev.event
op_assign
l_int|NULL
suffix:semicolon
id|kbd-&gt;dev.name
op_assign
id|dev-&gt;product_name
suffix:semicolon
id|kbd-&gt;dev.id.bustype
op_assign
id|BUS_MAPLE
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|kbd-&gt;dev
)paren
suffix:semicolon
id|maple_getcond_callback
c_func
(paren
id|dev
comma
id|dc_kbd_callback
comma
l_int|1
comma
id|MAPLE_FUNC_KEYBOARD
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input%d: keyboard(0x%lx): %s&bslash;n&quot;
comma
id|kbd-&gt;dev.number
comma
id|data
comma
id|kbd-&gt;dev.name
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dc_kbd_disconnect
r_static
r_void
id|dc_kbd_disconnect
c_func
(paren
r_struct
id|maple_device
op_star
id|dev
)paren
(brace
r_struct
id|dc_kbd
op_star
id|kbd
op_assign
id|dev-&gt;private_data
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|kbd-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|dc_kbd_driver
r_static
r_struct
id|maple_driver
id|dc_kbd_driver
op_assign
(brace
dot
id|function
op_assign
id|MAPLE_FUNC_KEYBOARD
comma
dot
id|name
op_assign
l_string|&quot;Dreamcast keyboard&quot;
comma
dot
id|connect
op_assign
id|dc_kbd_connect
comma
dot
id|disconnect
op_assign
id|dc_kbd_disconnect
comma
)brace
suffix:semicolon
DECL|function|dc_kbd_init
r_static
r_int
id|__init
id|dc_kbd_init
c_func
(paren
r_void
)paren
(brace
id|maple_register_driver
c_func
(paren
op_amp
id|dc_kbd_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dc_kbd_exit
r_static
r_void
id|__exit
id|dc_kbd_exit
c_func
(paren
r_void
)paren
(brace
id|maple_unregister_driver
c_func
(paren
op_amp
id|dc_kbd_driver
)paren
suffix:semicolon
)brace
DECL|variable|dc_kbd_init
id|module_init
c_func
(paren
id|dc_kbd_init
)paren
suffix:semicolon
DECL|variable|dc_kbd_exit
id|module_exit
c_func
(paren
id|dc_kbd_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
