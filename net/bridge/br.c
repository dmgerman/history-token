multiline_comment|/*&n; *&t;Generic parts&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br.c,v 1.46 2001/10/02 02:22:36 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
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
DECL|function|br_dec_use_count
r_void
id|br_dec_use_count
c_func
(paren
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|br_inc_use_count
r_void
id|br_inc_use_count
c_func
(paren
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
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
id|br_handle_frame_hook
op_assign
id|br_handle_frame
suffix:semicolon
macro_line|#ifdef CONFIG_INET
id|br_ioctl_hook
op_assign
id|br_ioctl_deviceless_stub
suffix:semicolon
macro_line|#endif
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
DECL|function|__br_clear_frame_hook
r_static
r_void
id|__br_clear_frame_hook
c_func
(paren
r_void
)paren
(brace
id|br_handle_frame_hook
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|__br_clear_ioctl_hook
r_static
r_void
id|__br_clear_ioctl_hook
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_INET
id|br_ioctl_hook
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif&t;
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
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|br_device_notifier
)paren
suffix:semicolon
id|br_call_ioctl_atomic
c_func
(paren
id|__br_clear_ioctl_hook
)paren
suffix:semicolon
id|net_call_rx_atomic
c_func
(paren
id|__br_clear_frame_hook
)paren
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
)brace
id|EXPORT_NO_SYMBOLS
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
