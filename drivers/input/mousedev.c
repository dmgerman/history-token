multiline_comment|/*&n; * Input driver to ExplorerPS/2 device driver module.&n; *&n; * Copyright (c) 1999-2002 Vojtech Pavlik&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
DECL|macro|MOUSEDEV_MINOR_BASE
mdefine_line|#define MOUSEDEV_MINOR_BASE &t;32
DECL|macro|MOUSEDEV_MINORS
mdefine_line|#define MOUSEDEV_MINORS&t;&t;32
DECL|macro|MOUSEDEV_MIX
mdefine_line|#define MOUSEDEV_MIX&t;&t;31
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Mouse (ExplorerPS/2) device interfaces&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_INPUT_MOUSEDEV_SCREEN_X
DECL|macro|CONFIG_INPUT_MOUSEDEV_SCREEN_X
mdefine_line|#define CONFIG_INPUT_MOUSEDEV_SCREEN_X&t;1024
macro_line|#endif
macro_line|#ifndef CONFIG_INPUT_MOUSEDEV_SCREEN_Y
DECL|macro|CONFIG_INPUT_MOUSEDEV_SCREEN_Y
mdefine_line|#define CONFIG_INPUT_MOUSEDEV_SCREEN_Y&t;768
macro_line|#endif
DECL|struct|mousedev
r_struct
id|mousedev
(brace
DECL|member|exist
r_int
id|exist
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|misc
r_int
id|misc
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|handle
r_struct
id|input_handle
id|handle
suffix:semicolon
DECL|member|devfs
id|devfs_handle_t
id|devfs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mousedev_list
r_struct
id|mousedev_list
(brace
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|mousedev
r_struct
id|mousedev
op_star
id|mousedev
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|dx
DECL|member|dy
DECL|member|dz
DECL|member|oldx
DECL|member|oldy
r_int
id|dx
comma
id|dy
comma
id|dz
comma
id|oldx
comma
id|oldy
suffix:semicolon
DECL|member|ps2
r_int
r_char
id|ps2
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|buttons
r_int
r_int
id|buttons
suffix:semicolon
DECL|member|ready
DECL|member|buffer
DECL|member|bufsiz
r_int
r_char
id|ready
comma
id|buffer
comma
id|bufsiz
suffix:semicolon
DECL|member|mode
DECL|member|imexseq
DECL|member|impsseq
r_int
r_char
id|mode
comma
id|imexseq
comma
id|impsseq
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MOUSEDEV_SEQ_LEN
mdefine_line|#define MOUSEDEV_SEQ_LEN&t;6
DECL|variable|mousedev_imps_seq
r_static
r_int
r_char
id|mousedev_imps_seq
(braket
)braket
op_assign
(brace
l_int|0xf3
comma
l_int|200
comma
l_int|0xf3
comma
l_int|100
comma
l_int|0xf3
comma
l_int|80
)brace
suffix:semicolon
DECL|variable|mousedev_imex_seq
r_static
r_int
r_char
id|mousedev_imex_seq
(braket
)braket
op_assign
(brace
l_int|0xf3
comma
l_int|200
comma
l_int|0xf3
comma
l_int|200
comma
l_int|0xf3
comma
l_int|80
)brace
suffix:semicolon
DECL|variable|mousedev_handler
r_static
r_struct
id|input_handler
id|mousedev_handler
suffix:semicolon
DECL|variable|mousedev_table
r_static
r_struct
id|mousedev
op_star
id|mousedev_table
(braket
id|MOUSEDEV_MINORS
)braket
suffix:semicolon
DECL|variable|mousedev_mix
r_static
r_struct
id|mousedev
id|mousedev_mix
suffix:semicolon
DECL|variable|xres
r_static
r_int
id|xres
op_assign
id|CONFIG_INPUT_MOUSEDEV_SCREEN_X
suffix:semicolon
DECL|variable|yres
r_static
r_int
id|yres
op_assign
id|CONFIG_INPUT_MOUSEDEV_SCREEN_Y
suffix:semicolon
DECL|function|mousedev_event
r_static
r_void
id|mousedev_event
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedevs
(braket
l_int|3
)braket
op_assign
(brace
id|handle
op_member_access_from_pointer
r_private
comma
op_amp
id|mousedev_mix
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|mousedev
op_star
op_star
id|mousedev
op_assign
id|mousedevs
suffix:semicolon
r_struct
id|mousedev_list
op_star
id|list
suffix:semicolon
r_int
id|index
comma
id|size
comma
id|wake
suffix:semicolon
r_while
c_loop
(paren
op_star
id|mousedev
)paren
(brace
id|wake
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|list
comma
op_amp
(paren
op_star
id|mousedev
)paren
op_member_access_from_pointer
id|list
comma
id|node
)paren
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_ABS
suffix:colon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|BTN_TRIGGER
comma
id|handle-&gt;dev-&gt;keybit
)paren
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ABS_X
suffix:colon
id|size
op_assign
id|handle-&gt;dev-&gt;absmax
(braket
id|ABS_X
)braket
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_X
)braket
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
l_int|0
)paren
(brace
id|list-&gt;dx
op_add_assign
(paren
id|value
op_star
id|xres
op_minus
id|list-&gt;oldx
)paren
op_div
id|size
suffix:semicolon
id|list-&gt;oldx
op_add_assign
id|list-&gt;dx
op_star
id|size
suffix:semicolon
)brace
r_else
(brace
id|list-&gt;dx
op_add_assign
id|value
op_minus
id|list-&gt;oldx
suffix:semicolon
id|list-&gt;oldx
op_add_assign
id|list-&gt;dx
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ABS_Y
suffix:colon
id|size
op_assign
id|handle-&gt;dev-&gt;absmax
(braket
id|ABS_Y
)braket
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_Y
)braket
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
l_int|0
)paren
(brace
id|list-&gt;dy
op_sub_assign
(paren
id|value
op_star
id|yres
op_minus
id|list-&gt;oldy
)paren
op_div
id|size
suffix:semicolon
id|list-&gt;oldy
op_sub_assign
id|list-&gt;dy
op_star
id|size
suffix:semicolon
)brace
r_else
(brace
id|list-&gt;dy
op_sub_assign
id|value
op_minus
id|list-&gt;oldy
suffix:semicolon
id|list-&gt;oldy
op_sub_assign
id|list-&gt;dy
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_REL
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|REL_X
suffix:colon
id|list-&gt;dx
op_add_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REL_Y
suffix:colon
id|list-&gt;dy
op_sub_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REL_WHEEL
suffix:colon
r_if
c_cond
(paren
id|list-&gt;mode
)paren
id|list-&gt;dz
op_sub_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_KEY
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|BTN_0
suffix:colon
r_case
id|BTN_TOUCH
suffix:colon
r_case
id|BTN_LEFT
suffix:colon
id|index
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BTN_4
suffix:colon
r_case
id|BTN_EXTRA
suffix:colon
r_if
c_cond
(paren
id|list-&gt;mode
op_eq
l_int|2
)paren
(brace
id|index
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|BTN_STYLUS
suffix:colon
r_case
id|BTN_1
suffix:colon
r_case
id|BTN_RIGHT
suffix:colon
id|index
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BTN_3
suffix:colon
r_case
id|BTN_SIDE
suffix:colon
r_if
c_cond
(paren
id|list-&gt;mode
op_eq
l_int|2
)paren
(brace
id|index
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|BTN_2
suffix:colon
r_case
id|BTN_STYLUS2
suffix:colon
r_case
id|BTN_MIDDLE
suffix:colon
id|index
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|value
)paren
(brace
r_case
l_int|0
suffix:colon
id|clear_bit
c_func
(paren
id|index
comma
op_amp
id|list-&gt;buttons
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|set_bit
c_func
(paren
id|index
comma
op_amp
id|list-&gt;buttons
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_SYN
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|SYN_REPORT
suffix:colon
id|list-&gt;ready
op_assign
l_int|1
suffix:semicolon
id|kill_fasync
c_func
(paren
op_amp
id|list-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|wake
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
(paren
(paren
op_star
id|mousedev
)paren
op_member_access_from_pointer
id|wait
)paren
)paren
suffix:semicolon
id|mousedev
op_increment
suffix:semicolon
)brace
)brace
DECL|function|mousedev_fasync
r_static
r_int
id|mousedev_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|on
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|file
comma
id|on
comma
op_amp
id|list-&gt;fasync
)paren
suffix:semicolon
r_return
id|retval
OL
l_int|0
ques
c_cond
id|retval
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_release
r_static
r_int
id|mousedev_release
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
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
r_struct
id|mousedev
op_star
id|mousedev
suffix:semicolon
id|mousedev_fasync
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
id|list_del
c_func
(paren
op_amp
id|list-&gt;node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|list-&gt;mousedev-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;mousedev-&gt;minor
op_eq
id|MOUSEDEV_MIX
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|handle
comma
op_amp
id|mousedev_handler.h_list
comma
id|h_node
)paren
(brace
id|mousedev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mousedev-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|mousedev-&gt;exist
)paren
(brace
id|input_close_device
c_func
(paren
op_amp
id|mousedev-&gt;handle
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|mousedev-&gt;devfs
)paren
suffix:semicolon
id|mousedev_table
(braket
id|mousedev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|mousedev
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|mousedev_mix.open
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;mousedev-&gt;exist
)paren
(brace
id|input_close_device
c_func
(paren
op_amp
id|list-&gt;mousedev-&gt;handle
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|list-&gt;mousedev-&gt;devfs
)paren
suffix:semicolon
id|mousedev_table
(braket
id|list-&gt;mousedev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|list-&gt;mousedev
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
id|kfree
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_open
r_static
r_int
id|mousedev_open
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
r_struct
id|mousedev_list
op_star
id|list
suffix:semicolon
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
r_struct
id|mousedev
op_star
id|mousedev
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
r_if
c_cond
(paren
id|major
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_eq
id|MISC_MAJOR
)paren
id|i
op_assign
id|MOUSEDEV_MIX
suffix:semicolon
r_else
macro_line|#endif
id|i
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_minus
id|MOUSEDEV_MINOR_BASE
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|MOUSEDEV_MINORS
op_logical_or
op_logical_neg
id|mousedev_table
(braket
id|i
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|list
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mousedev_list
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|list
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mousedev_list
)paren
)paren
suffix:semicolon
id|list-&gt;mousedev
op_assign
id|mousedev_table
(braket
id|i
)braket
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|list-&gt;node
comma
op_amp
id|mousedev_table
(braket
id|i
)braket
op_member_access_from_pointer
id|list
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
id|list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;mousedev-&gt;open
op_increment
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;mousedev-&gt;minor
op_eq
id|MOUSEDEV_MIX
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|handle
comma
op_amp
id|mousedev_handler.h_list
comma
id|h_node
)paren
(brace
id|mousedev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mousedev-&gt;open
op_logical_and
id|mousedev-&gt;exist
)paren
id|input_open_device
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|mousedev_mix.open
op_logical_and
id|list-&gt;mousedev-&gt;exist
)paren
id|input_open_device
c_func
(paren
op_amp
id|list-&gt;mousedev-&gt;handle
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_packet
r_static
r_void
id|mousedev_packet
c_func
(paren
r_struct
id|mousedev_list
op_star
id|list
comma
r_int
r_char
id|off
)paren
(brace
id|list-&gt;ps2
(braket
id|off
)braket
op_assign
l_int|0x08
op_or
(paren
(paren
id|list-&gt;dx
OL
l_int|0
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|list-&gt;dy
OL
l_int|0
)paren
op_lshift
l_int|5
)paren
op_or
(paren
id|list-&gt;buttons
op_amp
l_int|0x07
)paren
suffix:semicolon
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|1
)braket
op_assign
(paren
id|list-&gt;dx
OG
l_int|127
ques
c_cond
l_int|127
suffix:colon
(paren
id|list-&gt;dx
OL
op_minus
l_int|127
ques
c_cond
op_minus
l_int|127
suffix:colon
id|list-&gt;dx
)paren
)paren
suffix:semicolon
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|2
)braket
op_assign
(paren
id|list-&gt;dy
OG
l_int|127
ques
c_cond
l_int|127
suffix:colon
(paren
id|list-&gt;dy
OL
op_minus
l_int|127
ques
c_cond
op_minus
l_int|127
suffix:colon
id|list-&gt;dy
)paren
)paren
suffix:semicolon
id|list-&gt;dx
op_sub_assign
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|1
)braket
suffix:semicolon
id|list-&gt;dy
op_sub_assign
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|2
)braket
suffix:semicolon
id|list-&gt;bufsiz
op_assign
id|off
op_plus
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;mode
op_eq
l_int|2
)paren
(brace
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
op_assign
(paren
id|list-&gt;dz
OG
l_int|7
ques
c_cond
l_int|7
suffix:colon
(paren
id|list-&gt;dz
OL
op_minus
l_int|7
ques
c_cond
op_minus
l_int|7
suffix:colon
id|list-&gt;dz
)paren
)paren
suffix:semicolon
id|list-&gt;dz
op_sub_assign
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
suffix:semicolon
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
op_assign
(paren
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
op_amp
l_int|0x0f
)paren
op_or
(paren
(paren
id|list-&gt;buttons
op_amp
l_int|0x18
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|list-&gt;bufsiz
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list-&gt;mode
op_eq
l_int|1
)paren
(brace
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
op_assign
(paren
id|list-&gt;dz
OG
l_int|127
ques
c_cond
l_int|127
suffix:colon
(paren
id|list-&gt;dz
OL
op_minus
l_int|127
ques
c_cond
op_minus
l_int|127
suffix:colon
id|list-&gt;dz
)paren
)paren
suffix:semicolon
id|list-&gt;dz
op_sub_assign
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
suffix:semicolon
id|list-&gt;bufsiz
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;dx
op_logical_and
op_logical_neg
id|list-&gt;dy
op_logical_and
(paren
op_logical_neg
id|list-&gt;mode
op_logical_or
op_logical_neg
id|list-&gt;dz
)paren
)paren
id|list-&gt;ready
op_assign
l_int|0
suffix:semicolon
id|list-&gt;buffer
op_assign
id|list-&gt;bufsiz
suffix:semicolon
)brace
DECL|function|mousedev_write
r_static
id|ssize_t
id|mousedev_write
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
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
r_char
id|c
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
id|c
comma
id|buffer
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
id|c
op_eq
id|mousedev_imex_seq
(braket
id|list-&gt;imexseq
)braket
)paren
(brace
r_if
c_cond
(paren
op_increment
id|list-&gt;imexseq
op_eq
id|MOUSEDEV_SEQ_LEN
)paren
(brace
id|list-&gt;imexseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;mode
op_assign
l_int|2
suffix:semicolon
)brace
)brace
r_else
id|list-&gt;imexseq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|mousedev_imps_seq
(braket
id|list-&gt;impsseq
)braket
)paren
(brace
r_if
c_cond
(paren
op_increment
id|list-&gt;impsseq
op_eq
id|MOUSEDEV_SEQ_LEN
)paren
(brace
id|list-&gt;impsseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;mode
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|list-&gt;impsseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|0
)braket
op_assign
l_int|0xfa
suffix:semicolon
id|list-&gt;bufsiz
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_int|0xeb
suffix:colon
multiline_comment|/* Poll */
id|mousedev_packet
c_func
(paren
id|list
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf2
suffix:colon
multiline_comment|/* Get ID */
r_switch
c_cond
(paren
id|list-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list-&gt;bufsiz
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe9
suffix:colon
multiline_comment|/* Get info */
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
l_int|0x60
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|2
)braket
op_assign
l_int|3
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|3
)braket
op_assign
l_int|200
suffix:semicolon
id|list-&gt;bufsiz
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xff
suffix:colon
multiline_comment|/* Reset */
id|list-&gt;impsseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;imexseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|0
)braket
op_assign
l_int|0xaa
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|list-&gt;bufsiz
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list-&gt;buffer
op_assign
id|list-&gt;bufsiz
suffix:semicolon
)brace
id|kill_fasync
c_func
(paren
op_amp
id|list-&gt;fasync
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
id|list-&gt;mousedev-&gt;wait
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|mousedev_read
r_static
id|ssize_t
id|mousedev_read
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
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;ready
op_logical_and
op_logical_neg
id|list-&gt;buffer
op_logical_and
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|retval
op_assign
id|wait_event_interruptible
c_func
(paren
id|list-&gt;mousedev-&gt;wait
comma
id|list-&gt;ready
op_logical_or
id|list-&gt;buffer
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
op_logical_neg
id|list-&gt;buffer
op_logical_and
id|list-&gt;ready
)paren
id|mousedev_packet
c_func
(paren
id|list
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|list-&gt;buffer
)paren
id|count
op_assign
id|list-&gt;buffer
suffix:semicolon
id|list-&gt;buffer
op_sub_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|list-&gt;ps2
op_plus
id|list-&gt;bufsiz
op_minus
id|list-&gt;buffer
op_minus
id|count
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* No kernel lock - fine */
DECL|function|mousedev_poll
r_static
r_int
r_int
id|mousedev_poll
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
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|list-&gt;mousedev-&gt;wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;ready
op_logical_or
id|list-&gt;buffer
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mousedev_fops
r_struct
id|file_operations
id|mousedev_fops
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
id|mousedev_read
comma
dot
id|write
op_assign
id|mousedev_write
comma
dot
id|poll
op_assign
id|mousedev_poll
comma
dot
id|open
op_assign
id|mousedev_open
comma
dot
id|release
op_assign
id|mousedev_release
comma
dot
id|fasync
op_assign
id|mousedev_fasync
comma
)brace
suffix:semicolon
DECL|function|mousedev_connect
r_static
r_struct
id|input_handle
op_star
id|mousedev_connect
c_func
(paren
r_struct
id|input_handler
op_star
id|handler
comma
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|input_device_id
op_star
id|id
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedev
suffix:semicolon
r_int
id|minor
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|minor
op_assign
l_int|0
suffix:semicolon
id|minor
OL
id|MOUSEDEV_MINORS
op_logical_and
id|mousedev_table
(braket
id|minor
)braket
suffix:semicolon
id|minor
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_eq
id|MOUSEDEV_MINORS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mousedev: no more free mousedev devices&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mousedev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mousedev
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|mousedev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mousedev
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mousedev-&gt;list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|mousedev-&gt;wait
)paren
suffix:semicolon
id|mousedev-&gt;minor
op_assign
id|minor
suffix:semicolon
id|mousedev-&gt;exist
op_assign
l_int|1
suffix:semicolon
id|mousedev-&gt;handle.dev
op_assign
id|dev
suffix:semicolon
id|mousedev-&gt;handle.name
op_assign
id|mousedev-&gt;name
suffix:semicolon
id|mousedev-&gt;handle.handler
op_assign
id|handler
suffix:semicolon
id|mousedev-&gt;handle
dot
r_private
op_assign
id|mousedev
suffix:semicolon
id|sprintf
c_func
(paren
id|mousedev-&gt;name
comma
l_string|&quot;mouse%d&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mousedev_mix.open
)paren
id|input_open_device
c_func
(paren
op_amp
id|mousedev-&gt;handle
)paren
suffix:semicolon
id|mousedev_table
(braket
id|minor
)braket
op_assign
id|mousedev
suffix:semicolon
id|mousedev-&gt;devfs
op_assign
id|input_register_minor
c_func
(paren
l_string|&quot;input/mouse%d&quot;
comma
id|minor
comma
id|MOUSEDEV_MINOR_BASE
)paren
suffix:semicolon
r_return
op_amp
id|mousedev-&gt;handle
suffix:semicolon
)brace
DECL|function|mousedev_disconnect
r_static
r_void
id|mousedev_disconnect
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
id|mousedev-&gt;exist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mousedev-&gt;open
)paren
(brace
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mousedev_mix.open
)paren
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|input_unregister_minor
c_func
(paren
id|mousedev-&gt;devfs
)paren
suffix:semicolon
id|mousedev_table
(braket
id|mousedev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|mousedev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|mousedev_ids
r_static
r_struct
id|input_device_id
id|mousedev_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
op_or
id|INPUT_DEVICE_ID_MATCH_KEYBIT
op_or
id|INPUT_DEVICE_ID_MATCH_RELBIT
comma
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_REL
)paren
)brace
comma
dot
id|keybit
op_assign
(brace
(braket
id|LONG
c_func
(paren
id|BTN_LEFT
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
)brace
comma
dot
id|relbit
op_assign
(brace
id|BIT
c_func
(paren
id|REL_X
)paren
op_or
id|BIT
c_func
(paren
id|REL_Y
)paren
)brace
comma
)brace
comma
multiline_comment|/* A mouse like device, at least one button, two relative axes */
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
op_or
id|INPUT_DEVICE_ID_MATCH_RELBIT
comma
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_REL
)paren
)brace
comma
dot
id|relbit
op_assign
(brace
id|BIT
c_func
(paren
id|REL_WHEEL
)paren
)brace
comma
)brace
comma
multiline_comment|/* A separate scrollwheel */
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
op_or
id|INPUT_DEVICE_ID_MATCH_KEYBIT
op_or
id|INPUT_DEVICE_ID_MATCH_ABSBIT
comma
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
)brace
comma
dot
id|keybit
op_assign
(brace
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
)brace
comma
dot
id|absbit
op_assign
(brace
id|BIT
c_func
(paren
id|ABS_X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_Y
)paren
)brace
comma
)brace
comma
multiline_comment|/* A tablet like device, at least touch detection, two absolute axes */
(brace
)brace
comma
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|input
comma
id|mousedev_ids
)paren
suffix:semicolon
DECL|variable|mousedev_handler
r_static
r_struct
id|input_handler
id|mousedev_handler
op_assign
(brace
dot
id|event
op_assign
id|mousedev_event
comma
dot
id|connect
op_assign
id|mousedev_connect
comma
dot
id|disconnect
op_assign
id|mousedev_disconnect
comma
dot
id|fops
op_assign
op_amp
id|mousedev_fops
comma
dot
id|minor
op_assign
id|MOUSEDEV_MINOR_BASE
comma
dot
id|name
op_assign
l_string|&quot;mousedev&quot;
comma
dot
id|id_table
op_assign
id|mousedev_ids
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
DECL|variable|psaux_mouse
r_static
r_struct
id|miscdevice
id|psaux_mouse
op_assign
(brace
id|PSMOUSE_MINOR
comma
l_string|&quot;psaux&quot;
comma
op_amp
id|mousedev_fops
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|mousedev_intf
r_static
r_struct
id|device_interface
id|mousedev_intf
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mouse&quot;
comma
dot
id|devclass
op_assign
op_amp
id|input_devclass
comma
)brace
suffix:semicolon
DECL|function|mousedev_init
r_static
r_int
id|__init
id|mousedev_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|interface_register
c_func
(paren
op_amp
id|mousedev_intf
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|retval
suffix:semicolon
)brace
id|input_register_handler
c_func
(paren
op_amp
id|mousedev_handler
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mousedev_mix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mousedev
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mousedev_mix.list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|mousedev_mix.wait
)paren
suffix:semicolon
id|mousedev_table
(braket
id|MOUSEDEV_MIX
)braket
op_assign
op_amp
id|mousedev_mix
suffix:semicolon
id|mousedev_mix.exist
op_assign
l_int|1
suffix:semicolon
id|mousedev_mix.minor
op_assign
id|MOUSEDEV_MIX
suffix:semicolon
id|mousedev_mix.devfs
op_assign
id|input_register_minor
c_func
(paren
l_string|&quot;input/mice&quot;
comma
id|MOUSEDEV_MIX
comma
id|MOUSEDEV_MINOR_BASE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
r_if
c_cond
(paren
op_logical_neg
(paren
id|mousedev_mix.misc
op_assign
op_logical_neg
id|misc_register
c_func
(paren
op_amp
id|psaux_mouse
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mice: could not misc_register the device&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mice: PS/2 mouse device common for all mice&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_exit
r_static
r_void
id|__exit
id|mousedev_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
r_if
c_cond
(paren
id|mousedev_mix.misc
)paren
id|misc_deregister
c_func
(paren
op_amp
id|psaux_mouse
)paren
suffix:semicolon
macro_line|#endif
id|input_unregister_minor
c_func
(paren
id|mousedev_mix.devfs
)paren
suffix:semicolon
id|input_unregister_handler
c_func
(paren
op_amp
id|mousedev_handler
)paren
suffix:semicolon
id|interface_unregister
c_func
(paren
op_amp
id|mousedev_intf
)paren
suffix:semicolon
)brace
DECL|variable|mousedev_init
id|module_init
c_func
(paren
id|mousedev_init
)paren
suffix:semicolon
DECL|variable|mousedev_exit
id|module_exit
c_func
(paren
id|mousedev_exit
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|xres
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|xres
comma
l_string|&quot;Horizontal screen resolution&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|yres
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|yres
comma
l_string|&quot;Vertical screen resolution&quot;
)paren
suffix:semicolon
eof
