multiline_comment|/* dummy.c: a dummy net driver&n;&n;&t;The purpose of this driver is to provide a device to point a&n;&t;route through, but not to actually transmit packets.&n;&n;&t;Why?  If you have a machine whose only connection is an occasional&n;&t;PPP/SLIP/PLIP link, you can only connect to your own hostname&n;&t;when the link is up.  Otherwise you have to use localhost.&n;&t;This isn&squot;t very consistent.&n;&n;&t;One solution is to set up a dummy link using PPP/SLIP/PLIP,&n;&t;but this seems (to me) too much overhead for too little gain.&n;&t;This driver provides a small alternative. Thus you can do&n;&t;&n;&t;[when not running slip]&n;&t;&t;ifconfig dummy slip.addr.ess.here up&n;&t;[to go to slip]&n;&t;&t;ifconfig dummy down&n;&t;&t;dip whatever&n;&n;&t;This was written by looking at Donald Becker&squot;s skeleton driver&n;&t;and the loopback driver.  I then threw away anything that didn&squot;t&n;&t;apply!&t;Thanks to Alan Cox for the key clue on what to do with&n;&t;misguided packets.&n;&n;&t;&t;&t;Nick Holloway, 27th May 1994&n;&t;[I tweaked this explanation a little but that&squot;s all]&n;&t;&t;&t;Alan Cox, 30th May 1994&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
DECL|variable|numdummies
r_static
r_int
id|numdummies
op_assign
l_int|1
suffix:semicolon
r_static
r_int
id|dummy_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|dummy_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|dummy_set_address
r_static
r_int
id|dummy_set_address
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|p
)paren
(brace
r_struct
id|sockaddr
op_star
id|sa
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_valid_ether_addr
c_func
(paren
id|sa-&gt;sa_data
)paren
)paren
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|sa-&gt;sa_data
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* fake multicast ability */
DECL|function|set_multicast_list
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
)brace
macro_line|#ifdef CONFIG_NET_FASTROUTE
DECL|function|dummy_accept_fastpath
r_static
r_int
id|dummy_accept_fastpath
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|dummy_setup
r_static
r_void
id|__init
id|dummy_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Initialize the device structure. */
id|dev-&gt;get_stats
op_assign
id|dummy_get_stats
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|dummy_xmit
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
id|set_multicast_list
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|dummy_set_address
suffix:semicolon
macro_line|#ifdef CONFIG_NET_FASTROUTE
id|dev-&gt;accept_fastpath
op_assign
id|dummy_accept_fastpath
suffix:semicolon
macro_line|#endif
multiline_comment|/* Fill in device structure with ethernet-generic values. */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;change_mtu
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;flags
op_or_assign
id|IFF_NOARP
suffix:semicolon
id|dev-&gt;flags
op_and_assign
op_complement
id|IFF_MULTICAST
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|random_ether_addr
c_func
(paren
id|dev-&gt;dev_addr
)paren
suffix:semicolon
)brace
DECL|function|dummy_xmit
r_static
r_int
id|dummy_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_device_stats
op_star
id|stats
op_assign
id|dev-&gt;priv
suffix:semicolon
id|stats-&gt;tx_packets
op_increment
suffix:semicolon
id|stats-&gt;tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|dummy_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;priv
suffix:semicolon
)brace
DECL|variable|dummies
r_static
r_struct
id|net_device
op_star
op_star
id|dummies
suffix:semicolon
multiline_comment|/* Number of dummy devices to be set up by this module. */
id|module_param
c_func
(paren
id|numdummies
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|numdummies
comma
l_string|&quot;Number of dummy pseudo devices&quot;
)paren
suffix:semicolon
DECL|function|dummy_init_one
r_static
r_int
id|__init
id|dummy_init_one
c_func
(paren
r_int
id|index
)paren
(brace
r_struct
id|net_device
op_star
id|dev_dummy
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dev_dummy
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
comma
l_string|&quot;dummy%d&quot;
comma
id|dummy_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_dummy
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev_dummy
)paren
)paren
)paren
(brace
id|free_netdev
c_func
(paren
id|dev_dummy
)paren
suffix:semicolon
id|dev_dummy
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|dummies
(braket
id|index
)braket
op_assign
id|dev_dummy
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|dummy_free_one
r_static
r_void
id|dummy_free_one
c_func
(paren
r_int
id|index
)paren
(brace
id|unregister_netdev
c_func
(paren
id|dummies
(braket
id|index
)braket
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dummies
(braket
id|index
)braket
)paren
suffix:semicolon
)brace
DECL|function|dummy_init_module
r_static
r_int
id|__init
id|dummy_init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|dummies
op_assign
id|kmalloc
c_func
(paren
id|numdummies
op_star
r_sizeof
(paren
r_void
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dummies
)paren
r_return
op_minus
id|ENOMEM
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
id|numdummies
op_logical_and
op_logical_neg
id|err
suffix:semicolon
id|i
op_increment
)paren
id|err
op_assign
id|dummy_init_one
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
id|dummy_free_one
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|dummy_cleanup_module
r_static
r_void
id|__exit
id|dummy_cleanup_module
c_func
(paren
r_void
)paren
(brace
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
id|numdummies
suffix:semicolon
id|i
op_increment
)paren
id|dummy_free_one
c_func
(paren
id|i
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dummies
)paren
suffix:semicolon
)brace
DECL|variable|dummy_init_module
id|module_init
c_func
(paren
id|dummy_init_module
)paren
suffix:semicolon
DECL|variable|dummy_cleanup_module
id|module_exit
c_func
(paren
id|dummy_cleanup_module
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
