multiline_comment|/*&n; *&t;$Id: maplemouse.c,v 1.2 2004/03/22 01:18:15 lethal Exp $&n; * &t;SEGA Dreamcast mouse driver&n; *&t;Based on drivers/usb/usbmouse.c&n; */
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
l_string|&quot;SEGA Dreamcast mouse driver&quot;
)paren
suffix:semicolon
DECL|struct|dc_mouse
r_struct
id|dc_mouse
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
)brace
suffix:semicolon
DECL|function|dc_mouse_callback
r_static
r_void
id|dc_mouse_callback
c_func
(paren
r_struct
id|mapleq
op_star
id|mq
)paren
(brace
r_int
id|buttons
comma
id|relx
comma
id|rely
comma
id|relz
suffix:semicolon
r_struct
id|maple_device
op_star
id|mapledev
op_assign
id|mq-&gt;dev
suffix:semicolon
r_struct
id|dc_mouse
op_star
id|mouse
op_assign
id|mapledev-&gt;private_data
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|mouse-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|res
op_assign
id|mq-&gt;recvbuf
suffix:semicolon
id|buttons
op_assign
op_complement
id|res
(braket
l_int|8
)braket
suffix:semicolon
id|relx
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|res
op_plus
l_int|12
)paren
op_minus
l_int|512
suffix:semicolon
id|rely
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|res
op_plus
l_int|14
)paren
op_minus
l_int|512
suffix:semicolon
id|relz
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|res
op_plus
l_int|16
)paren
op_minus
l_int|512
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|buttons
op_amp
l_int|4
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|buttons
op_amp
l_int|9
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|buttons
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|relx
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
id|rely
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_WHEEL
comma
id|relz
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|dc_mouse_open
r_static
r_int
id|dc_mouse_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|dc_mouse
op_star
id|mouse
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|mouse-&gt;open
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dc_mouse_close
r_static
r_void
id|dc_mouse_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|dc_mouse
op_star
id|mouse
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|mouse-&gt;open
op_decrement
suffix:semicolon
)brace
DECL|function|dc_mouse_connect
r_static
r_int
id|dc_mouse_connect
c_func
(paren
r_struct
id|maple_device
op_star
id|dev
)paren
(brace
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
id|dc_mouse
op_star
id|mouse
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mouse
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dc_mouse
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
id|mouse
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dc_mouse
)paren
)paren
suffix:semicolon
id|dev-&gt;private_data
op_assign
id|mouse
suffix:semicolon
id|mouse-&gt;dev.evbit
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
id|EV_REL
)paren
suffix:semicolon
id|mouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_MOUSE
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_MIDDLE
)paren
suffix:semicolon
id|mouse-&gt;dev.relbit
(braket
l_int|0
)braket
op_assign
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
op_or
id|BIT
c_func
(paren
id|REL_WHEEL
)paren
suffix:semicolon
id|init_input_dev
c_func
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|mouse-&gt;dev
dot
r_private
op_assign
id|mouse
suffix:semicolon
id|mouse-&gt;dev.open
op_assign
id|dc_mouse_open
suffix:semicolon
id|mouse-&gt;dev.close
op_assign
id|dc_mouse_close
suffix:semicolon
id|mouse-&gt;dev.event
op_assign
l_int|NULL
suffix:semicolon
id|mouse-&gt;dev.name
op_assign
id|dev-&gt;product_name
suffix:semicolon
id|mouse-&gt;dev.id.bustype
op_assign
id|BUS_MAPLE
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|maple_getcond_callback
c_func
(paren
id|dev
comma
id|dc_mouse_callback
comma
l_int|1
comma
id|MAPLE_FUNC_MOUSE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: mouse(0x%lx): %s&bslash;n&quot;
comma
id|data
comma
id|mouse-&gt;dev.name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dc_mouse_disconnect
r_static
r_void
id|dc_mouse_disconnect
c_func
(paren
r_struct
id|maple_device
op_star
id|dev
)paren
(brace
r_struct
id|dc_mouse
op_star
id|mouse
op_assign
id|dev-&gt;private_data
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mouse
)paren
suffix:semicolon
)brace
DECL|variable|dc_mouse_driver
r_static
r_struct
id|maple_driver
id|dc_mouse_driver
op_assign
(brace
dot
id|function
op_assign
id|MAPLE_FUNC_MOUSE
comma
dot
id|name
op_assign
l_string|&quot;Dreamcast mouse&quot;
comma
dot
id|connect
op_assign
id|dc_mouse_connect
comma
dot
id|disconnect
op_assign
id|dc_mouse_disconnect
comma
)brace
suffix:semicolon
DECL|function|dc_mouse_init
r_static
r_int
id|__init
id|dc_mouse_init
c_func
(paren
r_void
)paren
(brace
id|maple_register_driver
c_func
(paren
op_amp
id|dc_mouse_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dc_mouse_exit
r_static
r_void
id|__exit
id|dc_mouse_exit
c_func
(paren
r_void
)paren
(brace
id|maple_unregister_driver
c_func
(paren
op_amp
id|dc_mouse_driver
)paren
suffix:semicolon
)brace
DECL|variable|dc_mouse_init
id|module_init
c_func
(paren
id|dc_mouse_init
)paren
suffix:semicolon
DECL|variable|dc_mouse_exit
id|module_exit
c_func
(paren
id|dc_mouse_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
