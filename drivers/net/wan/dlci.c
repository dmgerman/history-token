multiline_comment|/*&n; * DLCI&t;&t;Implementation of Frame Relay protocol for Linux, according to&n; *&t;&t;RFC 1490.  This generic device provides en/decapsulation for an&n; *&t;&t;underlying hardware driver.  Routes &amp; IPs are assigned to these&n; *&t;&t;interfaces.  Requires &squot;dlcicfg&squot; program to create usable &n; *&t;&t;interfaces, the initial one, &squot;dlci&squot; is for IOCTL use only.&n; *&n; * Version:&t;@(#)dlci.c&t;0.35&t;4 Jan 1997&n; *&n; * Author:&t;Mike McLagan &lt;mike.mclagan@linux.org&gt;&n; *&n; * Changes:&n; *&n; *&t;&t;0.15&t;Mike Mclagan&t;Packet freeing, bug in kmalloc call&n; *&t;&t;&t;&t;&t;DLCI_RET handling&n; *&t;&t;0.20&t;Mike McLagan&t;More conservative on which packets&n; *&t;&t;&t;&t;&t;are returned for retry and which are&n; *&t;&t;&t;&t;&t;are dropped.  If DLCI_RET_DROP is&n; *&t;&t;&t;&t;&t;returned from the FRAD, the packet is&n; *&t;&t;&t;&t; &t;sent back to Linux for re-transmission&n; *&t;&t;0.25&t;Mike McLagan&t;Converted to use SIOC IOCTL calls&n; *&t;&t;0.30&t;Jim Freeman&t;Fixed to allow IPX traffic&n; *&t;&t;0.35&t;Michael Elizabeth&t;Fixed incorrect memcpy_fromfs&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_DLCI_COUNT */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_frad.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;DLCI driver v0.35, 4 Jan 1997, mike.mclagan@linux.org&quot;
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|dlci_devs
)paren
suffix:semicolon
r_static
r_void
id|dlci_setup
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
multiline_comment|/* &n; * these encapsulate the RFC 1490 requirements as well as &n; * deal with packet transmission and reception, working with&n; * the upper network layers &n; */
DECL|function|dlci_header
r_static
r_int
id|dlci_header
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
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
(brace
r_struct
id|frhdr
id|hdr
suffix:semicolon
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_int
r_int
id|hlen
suffix:semicolon
r_char
op_star
id|dest
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|hdr.control
op_assign
id|FRAD_I_UI
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ETH_P_IP
suffix:colon
id|hdr.IP_NLPID
op_assign
id|FRAD_P_IP
suffix:semicolon
id|hlen
op_assign
r_sizeof
(paren
id|hdr.control
)paren
op_plus
r_sizeof
(paren
id|hdr.IP_NLPID
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* feel free to add other types, if necessary */
r_default
suffix:colon
id|hdr.pad
op_assign
id|FRAD_P_PADDING
suffix:semicolon
id|hdr.NLPID
op_assign
id|FRAD_P_SNAP
suffix:semicolon
id|memset
c_func
(paren
id|hdr.OUI
comma
l_int|0
comma
r_sizeof
(paren
id|hdr.OUI
)paren
)paren
suffix:semicolon
id|hdr.PID
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
id|hlen
op_assign
r_sizeof
(paren
id|hdr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dest
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|hlen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
comma
op_amp
id|hdr
comma
id|hlen
)paren
suffix:semicolon
r_return
id|hlen
suffix:semicolon
)brace
DECL|function|dlci_receive
r_static
r_void
id|dlci_receive
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
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_struct
id|frhdr
op_star
id|hdr
suffix:semicolon
r_int
id|process
comma
id|header
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|hdr
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: invalid data no header&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_errors
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|hdr
op_assign
(paren
r_struct
id|frhdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|process
op_assign
l_int|0
suffix:semicolon
id|header
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;control
op_ne
id|FRAD_I_UI
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: Invalid header flag 0x%02X.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|hdr-&gt;control
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_errors
op_increment
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|hdr-&gt;IP_NLPID
)paren
(brace
r_case
id|FRAD_P_PADDING
suffix:colon
r_if
c_cond
(paren
id|hdr-&gt;NLPID
op_ne
id|FRAD_P_SNAP
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: Unsupported NLPID 0x%02X.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|hdr-&gt;NLPID
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr-&gt;OUI
(braket
l_int|0
)braket
op_plus
id|hdr-&gt;OUI
(braket
l_int|1
)braket
op_plus
id|hdr-&gt;OUI
(braket
l_int|2
)braket
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: Unsupported organizationally unique identifier 0x%02X-%02X-%02X.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|hdr-&gt;OUI
(braket
l_int|0
)braket
comma
id|hdr-&gt;OUI
(braket
l_int|1
)braket
comma
id|hdr-&gt;OUI
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* at this point, it&squot;s an EtherType frame */
id|header
op_assign
r_sizeof
(paren
r_struct
id|frhdr
)paren
suffix:semicolon
multiline_comment|/* Already in network order ! */
id|skb-&gt;protocol
op_assign
id|hdr-&gt;PID
suffix:semicolon
id|process
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FRAD_P_IP
suffix:colon
id|header
op_assign
r_sizeof
(paren
id|hdr-&gt;control
)paren
op_plus
r_sizeof
(paren
id|hdr-&gt;IP_NLPID
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
id|process
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FRAD_P_SNAP
suffix:colon
r_case
id|FRAD_P_Q933
suffix:colon
r_case
id|FRAD_P_CLNP
suffix:colon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: Unsupported NLPID 0x%02X.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|hdr-&gt;pad
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: Invalid pad byte 0x%02X.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|hdr-&gt;pad
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|process
)paren
(brace
multiline_comment|/* we&squot;ve set up the protocol, so discard the header */
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|header
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|dlp-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
)brace
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dlci_transmit
r_static
r_int
id|dlci_transmit
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
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
op_logical_or
op_logical_neg
id|dev
)paren
r_return
l_int|0
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
id|dlp-&gt;slave
op_member_access_from_pointer
id|hard_start_xmit
c_func
(paren
id|skb
comma
id|dlp-&gt;slave
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
id|DLCI_RET_OK
suffix:colon
id|dlp-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DLCI_RET_ERR
suffix:colon
id|dlp-&gt;stats.tx_errors
op_increment
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DLCI_RET_DROP
suffix:colon
id|dlp-&gt;stats.tx_dropped
op_increment
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Alan Cox recommends always returning 0, and always freeing the packet */
multiline_comment|/* experience suggest a slightly more conservative approach */
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dlci_config
r_static
r_int
id|dlci_config
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|dlci_conf
op_star
id|conf
comma
r_int
id|get
)paren
(brace
r_struct
id|dlci_conf
id|config
suffix:semicolon
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_struct
id|frad_local
op_star
id|flp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|flp
op_assign
id|dlp-&gt;slave-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|config
comma
id|conf
comma
r_sizeof
(paren
r_struct
id|dlci_conf
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|config.flags
op_amp
op_complement
id|DLCI_VALID_FLAGS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dlp-&gt;config
comma
op_amp
id|config
comma
r_sizeof
(paren
r_struct
id|dlci_conf
)paren
)paren
suffix:semicolon
id|dlp-&gt;configured
op_assign
l_int|1
suffix:semicolon
)brace
id|err
op_assign
(paren
op_star
id|flp-&gt;dlci_conf
)paren
(paren
id|dlp-&gt;slave
comma
id|dev
comma
id|get
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|conf
comma
op_amp
id|dlp-&gt;config
comma
r_sizeof
(paren
r_struct
id|dlci_conf
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_dev_ioctl
r_static
r_int
id|dlci_dev_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|DLCI_GET_SLAVE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
op_star
(paren
r_int
op_star
)paren
(paren
id|dev-&gt;dev_addr
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|strncpy
c_func
(paren
id|ifr-&gt;ifr_slave
comma
id|dlp-&gt;slave-&gt;name
comma
r_sizeof
(paren
id|ifr-&gt;ifr_slave
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DLCI_GET_CONF
suffix:colon
r_case
id|DLCI_SET_CONF
suffix:colon
r_if
c_cond
(paren
op_logical_neg
op_star
(paren
r_int
op_star
)paren
(paren
id|dev-&gt;dev_addr
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|dlci_config
c_func
(paren
id|dev
comma
(paren
r_struct
id|dlci_conf
op_star
)paren
id|ifr-&gt;ifr_data
comma
id|cmd
op_eq
id|DLCI_GET_CONF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_change_mtu
r_static
r_int
id|dlci_change_mtu
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
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
r_return
(paren
op_star
id|dlp-&gt;slave-&gt;change_mtu
)paren
(paren
id|dlp-&gt;slave
comma
id|new_mtu
)paren
suffix:semicolon
)brace
DECL|function|dlci_open
r_static
r_int
id|dlci_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_struct
id|frad_local
op_star
id|flp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
(paren
r_int
op_star
)paren
(paren
id|dev-&gt;dev_addr
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|netif_running
c_func
(paren
id|dlp-&gt;slave
)paren
)paren
r_return
op_minus
id|ENOTCONN
suffix:semicolon
id|flp
op_assign
id|dlp-&gt;slave-&gt;priv
suffix:semicolon
id|err
op_assign
(paren
op_star
id|flp-&gt;activate
)paren
(paren
id|dlp-&gt;slave
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_close
r_static
r_int
id|dlci_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_struct
id|frad_local
op_star
id|flp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|flp
op_assign
id|dlp-&gt;slave-&gt;priv
suffix:semicolon
id|err
op_assign
(paren
op_star
id|flp-&gt;deactivate
)paren
(paren
id|dlp-&gt;slave
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|dlci_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|dlp-&gt;stats
suffix:semicolon
)brace
DECL|function|dlci_add
r_static
r_int
id|dlci_add
c_func
(paren
r_struct
id|dlci_add
op_star
id|dlci
)paren
(brace
r_struct
id|net_device
op_star
id|master
comma
op_star
id|slave
suffix:semicolon
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_struct
id|frad_local
op_star
id|flp
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* validate slave device */
id|slave
op_assign
id|dev_get_by_name
c_func
(paren
id|dlci-&gt;devname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slave
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|slave-&gt;type
op_ne
id|ARPHRD_FRAD
op_logical_or
id|slave-&gt;priv
op_eq
l_int|NULL
)paren
r_goto
id|err1
suffix:semicolon
multiline_comment|/* create device name */
id|master
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
r_struct
id|dlci_local
)paren
comma
l_string|&quot;dlci%d&quot;
comma
id|dlci_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|master
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
multiline_comment|/* make sure same slave not already registered */
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dlp
comma
op_amp
id|dlci_devs
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|dlp-&gt;slave
op_eq
id|slave
)paren
(brace
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
)brace
id|err
op_assign
id|dev_alloc_name
c_func
(paren
id|master
comma
id|master-&gt;name
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
id|err2
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
(paren
id|master-&gt;dev_addr
)paren
op_assign
id|dlci-&gt;dlci
suffix:semicolon
id|dlp
op_assign
(paren
r_struct
id|dlci_local
op_star
)paren
id|master-&gt;priv
suffix:semicolon
id|dlp-&gt;slave
op_assign
id|slave
suffix:semicolon
id|dlp-&gt;master
op_assign
id|master
suffix:semicolon
id|flp
op_assign
id|slave-&gt;priv
suffix:semicolon
id|err
op_assign
(paren
op_star
id|flp-&gt;assoc
)paren
(paren
id|slave
comma
id|master
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
id|err2
suffix:semicolon
id|err
op_assign
id|register_netdevice
c_func
(paren
id|master
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
id|err2
suffix:semicolon
id|strcpy
c_func
(paren
id|dlci-&gt;devname
comma
id|master-&gt;name
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|dlp-&gt;list
comma
op_amp
id|dlci_devs
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err2
suffix:colon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|master
)paren
suffix:semicolon
id|err1
suffix:colon
id|dev_put
c_func
(paren
id|slave
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|dlci_del
r_static
r_int
id|dlci_del
c_func
(paren
r_struct
id|dlci_add
op_star
id|dlci
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
r_struct
id|frad_local
op_star
id|flp
suffix:semicolon
r_struct
id|net_device
op_star
id|master
comma
op_star
id|slave
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* validate slave device */
id|master
op_assign
id|__dev_get_by_name
c_func
(paren
id|dlci-&gt;devname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|master
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|master
)paren
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|dlp
op_assign
id|master-&gt;priv
suffix:semicolon
id|slave
op_assign
id|dlp-&gt;slave
suffix:semicolon
id|flp
op_assign
id|slave-&gt;priv
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
(paren
op_star
id|flp-&gt;deassoc
)paren
(paren
id|slave
comma
id|master
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|dlp-&gt;list
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|master
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|slave
)paren
suffix:semicolon
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|dlci_ioctl
r_static
r_int
id|dlci_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|dlci_add
id|add
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|add
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|dlci_add
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCADDDLCI
suffix:colon
id|err
op_assign
id|dlci_add
c_func
(paren
op_amp
id|add
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|add
comma
r_sizeof
(paren
r_struct
id|dlci_add
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIOCDELDLCI
suffix:colon
id|err
op_assign
id|dlci_del
c_func
(paren
op_amp
id|add
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|dlci_setup
r_static
r_void
id|dlci_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|dev-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;open
op_assign
id|dlci_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|dlci_close
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|dlci_dev_ioctl
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|dlci_transmit
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|dlci_header
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|dlci_get_stats
suffix:semicolon
id|dev-&gt;change_mtu
op_assign
id|dlci_change_mtu
suffix:semicolon
id|dev-&gt;destructor
op_assign
id|free_netdev
suffix:semicolon
id|dlp-&gt;receive
op_assign
id|dlci_receive
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_DLCI
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
r_sizeof
(paren
r_struct
id|frhdr
)paren
suffix:semicolon
id|dev-&gt;addr_len
op_assign
r_sizeof
(paren
r_int
)paren
suffix:semicolon
)brace
multiline_comment|/* if slave is unregistering, then cleanup master */
DECL|function|dlci_dev_event
r_static
r_int
id|dlci_dev_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|unused
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_UNREGISTER
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dlp
comma
op_amp
id|dlci_devs
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|dlp-&gt;slave
op_eq
id|dev
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|dlp-&gt;list
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|dlp-&gt;master
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dlp-&gt;slave
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|dlci_notifier
r_static
r_struct
id|notifier_block
id|dlci_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|dlci_dev_event
comma
)brace
suffix:semicolon
DECL|function|init_dlci
r_static
r_int
id|__init
id|init_dlci
c_func
(paren
r_void
)paren
(brace
id|dlci_ioctl_set
c_func
(paren
id|dlci_ioctl
)paren
suffix:semicolon
id|register_netdevice_notifier
c_func
(paren
op_amp
id|dlci_notifier
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s.&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_exit
r_static
r_void
id|__exit
id|dlci_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|dlci_local
op_star
id|dlp
comma
op_star
id|nxt
suffix:semicolon
id|dlci_ioctl_set
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|dlci_notifier
)paren
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|dlp
comma
id|nxt
comma
op_amp
id|dlci_devs
comma
id|list
)paren
(brace
id|unregister_netdevice
c_func
(paren
id|dlp-&gt;master
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dlp-&gt;slave
)paren
suffix:semicolon
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|init_dlci
id|module_init
c_func
(paren
id|init_dlci
)paren
suffix:semicolon
DECL|variable|dlci_exit
id|module_exit
c_func
(paren
id|dlci_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mike McLagan&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Frame Relay DLCI layer&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
