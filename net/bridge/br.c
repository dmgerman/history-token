multiline_comment|/*&n; *&t;Generic parts&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br.c,v 1.47 2001/12/24 00:56:41 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
macro_line|#include &quot;../atm/lec.h&quot;
macro_line|#endif
DECL|variable|br_should_route_hook
r_int
(paren
op_star
id|br_should_route_hook
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|function|br_init
r_static
r_int
id|__init
id|br_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NET4: Ethernet Bridge 008 for NET4.0&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_INET) &amp;&amp; defined(CONFIG_NETFILTER)
r_if
c_cond
(paren
id|br_netfilter_init
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
id|brioctl_set
c_func
(paren
id|br_ioctl_deviceless_stub
)paren
suffix:semicolon
id|br_handle_frame_hook
op_assign
id|br_handle_frame
suffix:semicolon
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
id|br_fdb_get_hook
op_assign
id|br_fdb_get
suffix:semicolon
id|br_fdb_put_hook
op_assign
id|br_fdb_put
suffix:semicolon
macro_line|#endif
id|register_netdevice_notifier
c_func
(paren
op_amp
id|br_device_notifier
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_deinit
r_static
r_void
id|__exit
id|br_deinit
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_INET) &amp;&amp; defined(CONFIG_NETFILTER)
id|br_netfilter_fini
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|br_device_notifier
)paren
suffix:semicolon
id|brioctl_set
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|br_handle_frame_hook
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
id|br_fdb_get_hook
op_assign
l_int|NULL
suffix:semicolon
id|br_fdb_put_hook
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|br_cleanup_bridges
c_func
(paren
)paren
suffix:semicolon
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|br_should_route_hook
id|EXPORT_SYMBOL
c_func
(paren
id|br_should_route_hook
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|br_init
)paren
id|module_exit
c_func
(paren
id|br_deinit
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
