multiline_comment|/* net_init.c: Initialization for network devices. */
multiline_comment|/*&n;&t;Written 1993,1994,1995 by Donald Becker.&n;&n;&t;The author may be reached as becker@scyld.com, or C/O&n;&t;Scyld Computing Corporation&n;&t;410 Severn Ave., Suite 210&n;&t;Annapolis MD 21403&n;&n;&t;This file contains the initialization for the &quot;pl14+&quot; style ethernet&n;&t;drivers.  It should eventually replace most of drivers/net/Space.c.&n;&t;It&squot;s primary advantage is that it&squot;s able to allocate low-memory buffers.&n;&t;A secondary advantage is that the dangerous NE*000 netcards can reserve&n;&t;their I/O port region before the SCSI probes start.&n;&n;&t;Modifications/additions by Bjorn Ekwall &lt;bj0rn@blox.se&gt;:&n;&t;&t;ethdev_index[MAX_ETH_CARDS]&n;&t;&t;register_netdev() / unregister_netdev()&n;&t;&t;&n;&t;Modifications by Wolfgang Walter&n;&t;&t;Use dev_close cleanly so we always shut things down tidily.&n;&t;&t;&n;&t;Changed 29/10/95, Alan Cox to pass sockaddr&squot;s around for mac addresses.&n;&t;&n;&t;14/06/96 - Paul Gortmaker:&t;Add generic eth_change_mtu() function. &n;&t;24/09/96 - Paul Norton: Add token-ring variants of the netdev functions. &n;&t;&n;&t;08/11/99 - Alan Cox: Got fed up of the mess in this file and cleaned it&n;&t;&t;&t;up. We now share common code and have regularised name&n;&t;&t;&t;allocation setups. Abolished the 16 card limits.&n;&t;03/19/2000 - jgarzik and Urban Widmark: init_etherdev 32-byte align&n;&t;03/21/2001 - jgarzik: alloc_etherdev and friends&n;&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/fddidevice.h&gt;
macro_line|#include &lt;linux/hippidevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/fcdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_ltalk.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/neighbour.h&gt;
multiline_comment|/* The network devices currently exist only in the socket namespace, so these&n;   entries are unused.  The only ones that make sense are&n;    open&t;start the ethercard&n;    close&t;stop  the ethercard&n;    ioctl&t;To get statistics, perhaps set the interface port (AUI, BNC, etc.)&n;   One can also imagine getting raw packets using&n;    read &amp; write&n;   but this is probably better handled by a raw packet socket.&n;&n;   Given that almost all of these functions are handled in the current&n;   socket-based scheme, putting ethercard devices in /dev/ seems pointless.&n;   &n;   [Removed all support for /dev network devices. When someone adds&n;    streams then by magic we get them, but otherwise they are un-needed&n;&t;and a space waste]&n;*/
DECL|function|alloc_netdev
r_struct
id|net_device
op_star
id|alloc_netdev
c_func
(paren
r_int
id|sizeof_priv
comma
r_const
r_char
op_star
id|mask
comma
r_void
(paren
op_star
id|setup
)paren
(paren
r_struct
id|net_device
op_star
)paren
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|alloc_size
suffix:semicolon
multiline_comment|/* ensure 32-byte alignment of the private area */
id|alloc_size
op_assign
r_sizeof
(paren
op_star
id|dev
)paren
op_plus
id|sizeof_priv
op_plus
l_int|31
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|kmalloc
(paren
id|alloc_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;alloc_dev: Unable to allocate device memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
id|alloc_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sizeof_priv
)paren
id|dev-&gt;priv
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|dev
op_plus
l_int|1
)paren
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
suffix:semicolon
id|setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
id|mask
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
DECL|variable|alloc_netdev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_netdev
)paren
suffix:semicolon
DECL|function|init_alloc_dev
r_static
r_struct
id|net_device
op_star
id|init_alloc_dev
c_func
(paren
r_int
id|sizeof_priv
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|alloc_size
suffix:semicolon
multiline_comment|/* ensure 32-byte alignment of the private area */
id|alloc_size
op_assign
r_sizeof
(paren
op_star
id|dev
)paren
op_plus
id|sizeof_priv
op_plus
l_int|31
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|kmalloc
(paren
id|alloc_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;alloc_dev: Unable to allocate device memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
id|alloc_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sizeof_priv
)paren
id|dev-&gt;priv
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|dev
op_plus
l_int|1
)paren
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Create and name a device from a prototype, then perform any needed&n; *&t;setup.&n; */
DECL|function|init_netdev
r_static
r_struct
id|net_device
op_star
id|init_netdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|sizeof_priv
comma
r_char
op_star
id|mask
comma
r_void
(paren
op_star
id|setup
)paren
(paren
r_struct
id|net_device
op_star
)paren
)paren
(brace
r_int
id|new_device
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Allocate a device if one is not provided.&n;&t; */
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|dev
op_assign
id|init_alloc_dev
c_func
(paren
id|sizeof_priv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|new_device
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Allocate a name&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;name
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
id|dev-&gt;name
(braket
l_int|0
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_alloc_name
c_func
(paren
id|dev
comma
id|mask
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|new_device
)paren
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
id|netdev_boot_setup_check
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Configure via the caller provided setup function then&n;&t; *&t;register if needed.&n;&t; */
id|setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_device
)paren
(brace
r_int
id|err
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|register_netdevice
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * init_etherdev - Register ethernet device&n; * @dev: An ethernet device structure to be filled in, or %NULL if a new&n; *&t;struct should be allocated.&n; * @sizeof_priv: Size of additional driver-private structure to be allocated&n; *&t;for this ethernet device&n; *&n; * Fill in the fields of the device structure with ethernet-generic values.&n; *&n; * If no device structure is passed, a new one is constructed, complete with&n; * a private data area of size @sizeof_priv.  A 32-byte (not bit)&n; * alignment is enforced for this private data area.&n; *&n; * If an empty string area is passed as dev-&gt;name, or a new structure is made,&n; * a new name string is constructed.&n; */
DECL|function|init_etherdev
r_struct
id|net_device
op_star
id|init_etherdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|sizeof_priv
)paren
(brace
r_return
id|init_netdev
c_func
(paren
id|dev
comma
id|sizeof_priv
comma
l_string|&quot;eth%d&quot;
comma
id|ether_setup
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * alloc_etherdev - Allocates and sets up an ethernet device&n; * @sizeof_priv: Size of additional driver-private structure to be allocated&n; *&t;for this ethernet device&n; *&n; * Fill in the fields of the device structure with ethernet-generic&n; * values. Basically does everything except registering the device.&n; *&n; * Constructs a new net device, complete with a private data area of&n; * size @sizeof_priv.  A 32-byte (not bit) alignment is enforced for&n; * this private data area.&n; */
DECL|function|alloc_etherdev
r_struct
id|net_device
op_star
id|alloc_etherdev
c_func
(paren
r_int
id|sizeof_priv
)paren
(brace
r_return
id|alloc_netdev
c_func
(paren
id|sizeof_priv
comma
l_string|&quot;eth%d&quot;
comma
id|ether_setup
)paren
suffix:semicolon
)brace
DECL|variable|init_etherdev
id|EXPORT_SYMBOL
c_func
(paren
id|init_etherdev
)paren
suffix:semicolon
DECL|variable|alloc_etherdev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_etherdev
)paren
suffix:semicolon
DECL|function|eth_mac_addr
r_static
r_int
id|eth_mac_addr
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
id|addr
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|addr-&gt;sa_data
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|eth_change_mtu
r_static
r_int
id|eth_change_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
(brace
r_if
c_cond
(paren
(paren
id|new_mtu
OL
l_int|68
)paren
op_logical_or
(paren
id|new_mtu
OG
l_int|1500
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|new_mtu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_FDDI
multiline_comment|/**&n; * alloc_fddidev - Register FDDI device&n; * @sizeof_priv: Size of additional driver-private structure to be allocated&n; *&t;for this FDDI device&n; *&n; * Fill in the fields of the device structure with FDDI-generic values.&n; *&n; * Constructs a new net device, complete with a private data area of&n; * size @sizeof_priv.  A 32-byte (not bit) alignment is enforced for&n; * this private data area.&n; */
DECL|function|alloc_fddidev
r_struct
id|net_device
op_star
id|alloc_fddidev
c_func
(paren
r_int
id|sizeof_priv
)paren
(brace
r_return
id|alloc_netdev
c_func
(paren
id|sizeof_priv
comma
l_string|&quot;fddi%d&quot;
comma
id|fddi_setup
)paren
suffix:semicolon
)brace
DECL|variable|alloc_fddidev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_fddidev
)paren
suffix:semicolon
DECL|function|fddi_change_mtu
r_static
r_int
id|fddi_change_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
(brace
r_if
c_cond
(paren
(paren
id|new_mtu
OL
id|FDDI_K_SNAP_HLEN
)paren
op_logical_or
(paren
id|new_mtu
OG
id|FDDI_K_SNAP_DLEN
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|new_mtu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FDDI */
macro_line|#ifdef CONFIG_HIPPI
DECL|function|hippi_change_mtu
r_static
r_int
id|hippi_change_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
(brace
multiline_comment|/*&n;&t; * HIPPI&squot;s got these nice large MTUs.&n;&t; */
r_if
c_cond
(paren
(paren
id|new_mtu
OL
l_int|68
)paren
op_logical_or
(paren
id|new_mtu
OG
l_int|65280
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|new_mtu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * For HIPPI we will actually use the lower 4 bytes of the hardware&n; * address as the I-FIELD rather than the actual hardware address.&n; */
DECL|function|hippi_mac_addr
r_static
r_int
id|hippi_mac_addr
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
id|addr
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|addr-&gt;sa_data
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hippi_neigh_setup_dev
r_static
r_int
id|hippi_neigh_setup_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|neigh_parms
op_star
id|p
)paren
(brace
multiline_comment|/* Never send broadcast/multicast ARP messages */
id|p-&gt;mcast_probes
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* In IPv6 unicast probes are valid even on NBMA,&n;&t;* because they are encapsulated in normal IPv6 protocol.&n;&t;* Should be a generic flag. &n;&t;*/
r_if
c_cond
(paren
id|p-&gt;tbl-&gt;family
op_ne
id|AF_INET6
)paren
id|p-&gt;ucast_probes
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hippi_setup
r_static
r_void
id|hippi_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev-&gt;set_multicast_list
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;change_mtu
op_assign
id|hippi_change_mtu
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|hippi_header
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|hippi_rebuild_header
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|hippi_mac_addr
suffix:semicolon
id|dev-&gt;hard_header_parse
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;header_cache_update
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;neigh_setup
op_assign
id|hippi_neigh_setup_dev
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t support HIPPI `ARP&squot; for the time being, and probably&n;&t; * never will unless someone else implements it. However we&n;&t; * still need a fake ARPHRD to make ifconfig and friends play ball.&n;&t; */
id|dev-&gt;type
op_assign
id|ARPHRD_HIPPI
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|HIPPI_HLEN
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|65280
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|HIPPI_ALEN
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|25
multiline_comment|/* 5 */
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xFF
comma
id|HIPPI_ALEN
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * HIPPI doesn&squot;t support broadcast+multicast and we only use&n;&t; * static ARP tables. ARP is disabled by hippi_neigh_setup_dev. &n;&t; */
id|dev-&gt;flags
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * alloc_hippi_dev - Register HIPPI device&n; * @sizeof_priv: Size of additional driver-private structure to be allocated&n; *&t;for this HIPPI device&n; *&n; * Fill in the fields of the device structure with HIPPI-generic values.&n; *&n; * Constructs a new net device, complete with a private data area of&n; * size @sizeof_priv.  A 32-byte (not bit) alignment is enforced for&n; * this private data area.&n; */
DECL|function|alloc_hippi_dev
r_struct
id|net_device
op_star
id|alloc_hippi_dev
c_func
(paren
r_int
id|sizeof_priv
)paren
(brace
r_return
id|alloc_netdev
c_func
(paren
id|sizeof_priv
comma
l_string|&quot;hip%d&quot;
comma
id|hippi_setup
)paren
suffix:semicolon
)brace
DECL|variable|alloc_hippi_dev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_hippi_dev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HIPPI */
DECL|function|ether_setup
r_void
id|ether_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Fill in the fields of the device structure with ethernet-generic values.&n;&t;   This should be in a common file instead of per-driver.  */
id|dev-&gt;change_mtu
op_assign
id|eth_change_mtu
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|eth_header
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|eth_rebuild_header
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|eth_mac_addr
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
id|eth_header_cache
suffix:semicolon
id|dev-&gt;header_cache_update
op_assign
id|eth_header_cache_update
suffix:semicolon
id|dev-&gt;hard_header_parse
op_assign
id|eth_header_parse
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_ETHER
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|ETH_HLEN
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|1500
suffix:semicolon
multiline_comment|/* eth_mtu */
id|dev-&gt;addr_len
op_assign
id|ETH_ALEN
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* Ethernet wants good queues */
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xFF
comma
id|ETH_ALEN
)paren
suffix:semicolon
multiline_comment|/* New-style flags. */
id|dev-&gt;flags
op_assign
id|IFF_BROADCAST
op_or
id|IFF_MULTICAST
suffix:semicolon
)brace
DECL|variable|ether_setup
id|EXPORT_SYMBOL
c_func
(paren
id|ether_setup
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FDDI
DECL|function|fddi_setup
r_void
id|fddi_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; * Fill in the fields of the device structure with FDDI-generic values.&n;&t; * This should be in a common file instead of per-driver.&n;&t; */
id|dev-&gt;change_mtu
op_assign
id|fddi_change_mtu
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|fddi_header
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|fddi_rebuild_header
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_FDDI
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|FDDI_K_SNAP_HLEN
op_plus
l_int|3
suffix:semicolon
multiline_comment|/* Assume 802.2 SNAP hdr len + 3 pad bytes */
id|dev-&gt;mtu
op_assign
id|FDDI_K_SNAP_DLEN
suffix:semicolon
multiline_comment|/* Assume max payload of 802.2 SNAP frame */
id|dev-&gt;addr_len
op_assign
id|FDDI_K_ALEN
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* Long queues on FDDI */
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xFF
comma
id|FDDI_K_ALEN
)paren
suffix:semicolon
multiline_comment|/* New-style flags */
id|dev-&gt;flags
op_assign
id|IFF_BROADCAST
op_or
id|IFF_MULTICAST
suffix:semicolon
)brace
DECL|variable|fddi_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fddi_setup
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FDDI */
macro_line|#if defined(CONFIG_ATALK) || defined(CONFIG_ATALK_MODULE)
DECL|function|ltalk_change_mtu
r_static
r_int
id|ltalk_change_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mtu
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ltalk_mac_addr
r_static
r_int
id|ltalk_mac_addr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ltalk_setup
r_void
id|ltalk_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Fill in the fields of the device structure with localtalk-generic values. */
id|dev-&gt;change_mtu
op_assign
id|ltalk_change_mtu
suffix:semicolon
id|dev-&gt;hard_header
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|ltalk_mac_addr
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;header_cache_update
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_LOCALTLK
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|LTALK_HLEN
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|LTALK_MTU
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|LTALK_ALEN
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|10
suffix:semicolon
id|dev-&gt;broadcast
(braket
l_int|0
)braket
op_assign
l_int|0xFF
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_BROADCAST
op_or
id|IFF_MULTICAST
op_or
id|IFF_NOARP
suffix:semicolon
)brace
DECL|variable|ltalk_setup
id|EXPORT_SYMBOL
c_func
(paren
id|ltalk_setup
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ATALK || CONFIG_ATALK_MODULE */
DECL|function|register_netdev
r_int
id|register_netdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;If the name is a format string the caller wants us to&n;&t; *&t;do a name allocation&n;&t; */
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|dev-&gt;name
comma
l_char|&squot;%&squot;
)paren
)paren
(brace
id|err
op_assign
id|dev_alloc_name
c_func
(paren
id|dev
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Back compatibility hook. Kill this one in 2.5&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;name
(braket
l_int|0
)braket
op_eq
l_int|0
op_logical_or
id|dev-&gt;name
(braket
l_int|0
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|err
op_assign
id|dev_alloc_name
c_func
(paren
id|dev
comma
l_string|&quot;eth%d&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|register_netdevice
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|unregister_netdev
r_void
id|unregister_netdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|register_netdev
id|EXPORT_SYMBOL
c_func
(paren
id|register_netdev
)paren
suffix:semicolon
DECL|variable|unregister_netdev
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_netdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TR
DECL|function|tr_setup
r_void
id|tr_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; *&t;Configure and register&n;&t; */
id|dev-&gt;hard_header
op_assign
id|tr_header
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|tr_rebuild_header
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_IEEE802_TR
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|TR_HLEN
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|2000
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|TR_ALEN
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* Long queues on tr */
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xFF
comma
id|TR_ALEN
)paren
suffix:semicolon
multiline_comment|/* New-style flags. */
id|dev-&gt;flags
op_assign
id|IFF_BROADCAST
op_or
id|IFF_MULTICAST
suffix:semicolon
)brace
multiline_comment|/**&n; * alloc_trdev - Register token ring device&n; * @sizeof_priv: Size of additional driver-private structure to be allocated&n; *&t;for this token ring device&n; *&n; * Fill in the fields of the device structure with token ring-generic values.&n; *&n; * Constructs a new net device, complete with a private data area of&n; * size @sizeof_priv.  A 32-byte (not bit) alignment is enforced for&n; * this private data area.&n; */
DECL|function|alloc_trdev
r_struct
id|net_device
op_star
id|alloc_trdev
c_func
(paren
r_int
id|sizeof_priv
)paren
(brace
r_return
id|alloc_netdev
c_func
(paren
id|sizeof_priv
comma
l_string|&quot;tr%d&quot;
comma
id|tr_setup
)paren
suffix:semicolon
)brace
DECL|variable|tr_setup
id|EXPORT_SYMBOL
c_func
(paren
id|tr_setup
)paren
suffix:semicolon
DECL|variable|alloc_trdev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_trdev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_TR */
macro_line|#ifdef CONFIG_NET_FC
DECL|function|fc_setup
r_void
id|fc_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev-&gt;hard_header
op_assign
id|fc_header
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|fc_rebuild_header
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_IEEE802
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|FC_HLEN
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|2024
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|FC_ALEN
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* Long queues on fc */
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xFF
comma
id|FC_ALEN
)paren
suffix:semicolon
multiline_comment|/* New-style flags. */
id|dev-&gt;flags
op_assign
id|IFF_BROADCAST
suffix:semicolon
)brace
multiline_comment|/**&n; * alloc_fcdev - Register fibre channel device&n; * @sizeof_priv: Size of additional driver-private structure to be allocated&n; *&t;for this fibre channel device&n; *&n; * Fill in the fields of the device structure with fibre channel-generic values.&n; *&n; * Constructs a new net device, complete with a private data area of&n; * size @sizeof_priv.  A 32-byte (not bit) alignment is enforced for&n; * this private data area.&n; */
DECL|function|alloc_fcdev
r_struct
id|net_device
op_star
id|alloc_fcdev
c_func
(paren
r_int
id|sizeof_priv
)paren
(brace
r_return
id|alloc_netdev
c_func
(paren
id|sizeof_priv
comma
l_string|&quot;fc%d&quot;
comma
id|fc_setup
)paren
suffix:semicolon
)brace
DECL|variable|fc_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fc_setup
)paren
suffix:semicolon
DECL|variable|alloc_fcdev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_fcdev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_FC */
eof
