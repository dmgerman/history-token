multiline_comment|/*&n; * $Id: power.c,v 1.10 2001/09/25 09:17:15 vojtech Exp $&n; *&n; *  Copyright (c) 2001 &quot;Crazy&quot; James Simmons  &n; *&n; *  Input driver Power Management.&n; *&n; *  Sponsored by Transvirtual Technology.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so by&n; * e-mail - mail your message to &lt;jsimmons@transvirtual.com&gt;.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
DECL|variable|power_handler
r_static
r_struct
id|input_handler
id|power_handler
suffix:semicolon
multiline_comment|/*&n; * Power management can&squot;t be done in a interrupt context. So we have to&n; * use keventd.&n; */
DECL|variable|suspend_button_pushed
r_static
r_int
id|suspend_button_pushed
op_assign
l_int|0
suffix:semicolon
DECL|function|suspend_button_task_handler
r_static
r_void
id|suspend_button_task_handler
c_func
(paren
r_void
op_star
id|data
)paren
(brace
singleline_comment|//extern void pm_do_suspend(void);
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* debounce */
singleline_comment|//pm_do_suspend();
id|suspend_button_pushed
op_assign
l_int|0
suffix:semicolon
)brace
r_static
id|DECLARE_WORK
c_func
(paren
id|suspend_button_task
comma
id|suspend_button_task_handler
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|power_event
r_static
r_void
id|power_event
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
id|down
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
id|handle-&gt;dev
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Entering power_event&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|EV_KEY
op_logical_or
id|type
op_ne
id|EV_PWR
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|EV_PWR
)paren
(brace
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|KEY_SUSPEND
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Powering down entire device&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|//pm_send_all(PM_SUSPEND, dev);
r_if
c_cond
(paren
op_logical_neg
id|suspend_button_pushed
)paren
(brace
id|suspend_button_pushed
op_assign
l_int|1
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|suspend_button_task
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|KEY_POWER
suffix:colon
multiline_comment|/* Hum power down the machine. */
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|KEY_SUSPEND
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Powering down input device&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* This is risky. See pm.h for details. */
r_if
c_cond
(paren
id|dev-&gt;state
op_ne
id|PM_RESUME
)paren
id|dev-&gt;state
op_assign
id|PM_RESUME
suffix:semicolon
r_else
id|dev-&gt;state
op_assign
id|PM_SUSPEND
suffix:semicolon
id|pm_send
c_func
(paren
id|dev-&gt;pm_dev
comma
id|dev-&gt;state
comma
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KEY_POWER
suffix:colon
multiline_comment|/* Turn the input device off completely ? */
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
DECL|function|power_connect
r_static
r_struct
id|input_handle
op_star
id|power_connect
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
id|input_handle
op_star
id|handle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|EV_KEY
comma
id|dev-&gt;evbit
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|EV_PWR
comma
id|dev-&gt;evbit
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|KEY_SUSPEND
comma
id|dev-&gt;keybit
)paren
op_logical_or
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|KEY_POWER
comma
id|dev-&gt;keybit
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|handle
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|input_handle
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
id|handle
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|input_handle
)paren
)paren
suffix:semicolon
id|handle-&gt;dev
op_assign
id|dev
suffix:semicolon
id|handle-&gt;handler
op_assign
id|handler
suffix:semicolon
id|input_open_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;power.c: Adding power management to input layer&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|handle
suffix:semicolon
)brace
DECL|function|power_disconnect
r_static
r_void
id|power_disconnect
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
DECL|variable|power_ids
r_static
r_struct
id|input_device_id
id|power_ids
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
id|KEY_SUSPEND
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|KEY_SUSPEND
)paren
)brace
)brace
comma
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
op_or
id|INPUT_DEVICE_ID_MATCH_KEYBIT
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
id|KEY_POWER
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|KEY_POWER
)paren
)brace
)brace
comma
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
comma
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_PWR
)paren
)brace
comma
)brace
comma
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
id|power_ids
)paren
suffix:semicolon
DECL|variable|power_handler
r_static
r_struct
id|input_handler
id|power_handler
op_assign
(brace
dot
id|event
op_assign
id|power_event
comma
dot
id|connect
op_assign
id|power_connect
comma
dot
id|disconnect
op_assign
id|power_disconnect
comma
dot
id|name
op_assign
l_string|&quot;power&quot;
comma
dot
id|id_table
op_assign
id|power_ids
comma
)brace
suffix:semicolon
DECL|function|power_init
r_static
r_int
id|__init
id|power_init
c_func
(paren
r_void
)paren
(brace
id|input_register_handler
c_func
(paren
op_amp
id|power_handler
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|power_exit
r_static
r_void
id|__exit
id|power_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_handler
c_func
(paren
op_amp
id|power_handler
)paren
suffix:semicolon
)brace
DECL|variable|power_init
id|module_init
c_func
(paren
id|power_init
)paren
suffix:semicolon
DECL|variable|power_exit
id|module_exit
c_func
(paren
id|power_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Simmons &lt;jsimmons@transvirtual.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Input Power Management driver&quot;
)paren
suffix:semicolon
eof
