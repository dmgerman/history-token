multiline_comment|/*&n; *  linux/drivers/net/netconsole.c&n; *&n; *  Copyright (C) 2001  Ingo Molnar &lt;mingo@redhat.com&gt;&n; *&n; *  This file contains the implementation of an IRQ-safe, crash-safe&n; *  kernel console implementation that outputs kernel messages to the&n; *  network.&n; *&n; * Modification history:&n; *&n; * 2001-09-17    started by Ingo Molnar.&n; * 2003-08-11    2.6 port by Matt Mackall&n; *               simplified options&n; *               generic card hooks&n; *               works non-modular&n; * 2003-09-07    rewritten with netpoll api&n; */
multiline_comment|/****************************************************************&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2, or (at your option)&n; *      any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; ****************************************************************/
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/netpoll.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Maintainer: Matt Mackall &lt;mpm@selenic.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Console driver for network interfaces&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|config
r_static
r_char
id|config
(braket
l_int|256
)braket
suffix:semicolon
id|module_param_string
c_func
(paren
id|netconsole
comma
id|config
comma
l_int|256
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|netconsole
comma
l_string|&quot; netconsole=[src-port]@[src-ip]/[dev],[tgt-port]@&lt;tgt-ip&gt;/[tgt-macaddr]&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|np
r_static
r_struct
id|netpoll
id|np
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;netconsole&quot;
comma
dot
id|dev_name
op_assign
l_string|&quot;eth0&quot;
comma
dot
id|local_port
op_assign
l_int|6665
comma
dot
id|remote_port
op_assign
l_int|6666
comma
dot
id|remote_mac
op_assign
(brace
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
)brace
comma
dot
id|drop
op_assign
id|netpoll_queue
comma
)brace
suffix:semicolon
DECL|variable|configured
r_static
r_int
id|configured
op_assign
l_int|0
suffix:semicolon
DECL|macro|MAX_PRINT_CHUNK
mdefine_line|#define MAX_PRINT_CHUNK 1000
DECL|function|write_msg
r_static
r_void
id|write_msg
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|msg
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|frag
comma
id|left
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np.dev
)paren
r_return
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|left
op_assign
id|len
suffix:semicolon
id|left
suffix:semicolon
)paren
(brace
id|frag
op_assign
id|min
c_func
(paren
id|left
comma
id|MAX_PRINT_CHUNK
)paren
suffix:semicolon
id|netpoll_send_udp
c_func
(paren
op_amp
id|np
comma
id|msg
comma
id|frag
)paren
suffix:semicolon
id|msg
op_add_assign
id|frag
suffix:semicolon
id|left
op_sub_assign
id|frag
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|netconsole
r_static
r_struct
id|console
id|netconsole
op_assign
(brace
dot
id|flags
op_assign
id|CON_ENABLED
op_or
id|CON_PRINTBUFFER
comma
dot
id|write
op_assign
id|write_msg
)brace
suffix:semicolon
DECL|function|option_setup
r_static
r_int
id|option_setup
c_func
(paren
r_char
op_star
id|opt
)paren
(brace
id|configured
op_assign
op_logical_neg
id|netpoll_parse_options
c_func
(paren
op_amp
id|np
comma
id|opt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;netconsole=&quot;
comma
id|option_setup
)paren
suffix:semicolon
DECL|function|init_netconsole
r_static
r_int
id|init_netconsole
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|config
)paren
)paren
(brace
id|option_setup
c_func
(paren
id|config
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|configured
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;netconsole: not configured, aborting&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|netpoll_setup
c_func
(paren
op_amp
id|np
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|register_console
c_func
(paren
op_amp
id|netconsole
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;netconsole: network logging started&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_netconsole
r_static
r_void
id|cleanup_netconsole
c_func
(paren
r_void
)paren
(brace
id|unregister_console
c_func
(paren
op_amp
id|netconsole
)paren
suffix:semicolon
id|netpoll_cleanup
c_func
(paren
op_amp
id|np
)paren
suffix:semicolon
)brace
DECL|variable|init_netconsole
id|module_init
c_func
(paren
id|init_netconsole
)paren
suffix:semicolon
DECL|variable|cleanup_netconsole
id|module_exit
c_func
(paren
id|cleanup_netconsole
)paren
suffix:semicolon
eof
