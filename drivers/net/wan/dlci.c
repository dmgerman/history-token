multiline_comment|/*&n; * DLCI&t;&t;Implementation of Frame Relay protocol for Linux, according to&n; *&t;&t;RFC 1490.  This generic device provides en/decapsulation for an&n; *&t;&t;underlying hardware driver.  Routes &amp; IPs are assigned to these&n; *&t;&t;interfaces.  Requires &squot;dlcicfg&squot; program to create usable &n; *&t;&t;interfaces, the initial one, &squot;dlci&squot; is for IOCTL use only.&n; *&n; * Version:&t;@(#)dlci.c&t;0.35&t;4 Jan 1997&n; *&n; * Author:&t;Mike McLagan &lt;mike.mclagan@linux.org&gt;&n; *&n; * Changes:&n; *&n; *&t;&t;0.15&t;Mike Mclagan&t;Packet freeing, bug in kmalloc call&n; *&t;&t;&t;&t;&t;DLCI_RET handling&n; *&t;&t;0.20&t;Mike McLagan&t;More conservative on which packets&n; *&t;&t;&t;&t;&t;are returned for retry and whic are&n; *&t;&t;&t;&t;&t;are dropped.  If DLCI_RET_DROP is&n; *&t;&t;&t;&t;&t;returned from the FRAD, the packet is&n; *&t;&t;&t;&t; &t;sent back to Linux for re-transmission&n; *&t;&t;0.25&t;Mike McLagan&t;Converted to use SIOC IOCTL calls&n; *&t;&t;0.30&t;Jim Freeman&t;Fixed to allow IPX traffic&n; *&t;&t;0.35&t;Michael Elizabeth&t;Fixed incorrect memcpy_fromfs&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_DLCI_COUNT */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
DECL|variable|devname
r_static
r_const
r_char
id|devname
(braket
)braket
op_assign
l_string|&quot;dlci&quot;
suffix:semicolon
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
DECL|variable|open_dev
r_static
r_struct
id|net_device
op_star
id|open_dev
(braket
id|CONFIG_DLCI_COUNT
)braket
suffix:semicolon
DECL|variable|basename
r_static
r_char
op_star
id|basename
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|dlci_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* allow FRAD&squot;s to register their name as a valid FRAD */
DECL|function|register_frad
r_int
id|register_frad
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EINVAL
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
r_sizeof
(paren
id|basename
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|basename
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
multiline_comment|/* take care of multiple registrations */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|basename
(braket
id|i
)braket
comma
id|name
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
r_sizeof
(paren
id|basename
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
)paren
r_return
op_minus
id|EMLINK
suffix:semicolon
id|basename
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|basename
(braket
id|i
)braket
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|strcpy
c_func
(paren
id|basename
(braket
id|i
)braket
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|register_frad
id|EXPORT_SYMBOL
c_func
(paren
id|register_frad
)paren
suffix:semicolon
DECL|function|unregister_frad
r_int
id|unregister_frad
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EINVAL
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
r_sizeof
(paren
id|basename
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|basename
(braket
id|i
)braket
op_logical_and
(paren
id|strcmp
c_func
(paren
id|basename
(braket
id|i
)braket
comma
id|name
)paren
op_eq
l_int|0
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
r_sizeof
(paren
id|basename
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|kfree
c_func
(paren
id|basename
(braket
id|i
)braket
)paren
suffix:semicolon
id|basename
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
comma
id|i
suffix:semicolon
r_char
id|buf
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* validate slave device */
id|slave
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
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* check for registration */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|basename
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|basename
(braket
id|i
)braket
)paren
op_logical_and
(paren
id|strncmp
c_func
(paren
id|dlci-&gt;devname
comma
id|basename
(braket
id|i
)braket
comma
id|strlen
c_func
(paren
id|basename
(braket
id|i
)braket
)paren
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|strlen
c_func
(paren
id|dlci-&gt;devname
)paren
OG
id|strlen
c_func
(paren
id|basename
(braket
id|i
)braket
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
r_sizeof
(paren
id|basename
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* check for too many open devices : should this be dynamic ? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CONFIG_DLCI_COUNT
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|open_dev
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|CONFIG_DLCI_COUNT
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
multiline_comment|/*  #### Alan: Comments on this?? */
multiline_comment|/* create device name */
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s%02i&quot;
comma
id|devname
comma
id|i
)paren
suffix:semicolon
id|master
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|master
)paren
comma
id|GFP_KERNEL
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
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|master
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|master
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|master-&gt;name
comma
id|buf
)paren
suffix:semicolon
id|master-&gt;init
op_assign
id|dlci_init
suffix:semicolon
id|master-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|register_netdev
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
(brace
id|kfree
c_func
(paren
id|master
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
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
id|flp
op_assign
id|slave-&gt;priv
suffix:semicolon
id|err
op_assign
id|flp
ques
c_cond
(paren
op_star
id|flp-&gt;assoc
)paren
(paren
id|slave
comma
id|master
)paren
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|unregister_netdev
c_func
(paren
id|master
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|master-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|master
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|dlci-&gt;devname
comma
id|buf
)paren
suffix:semicolon
id|open_dev
(braket
id|i
)braket
op_assign
id|master
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_del
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
id|i
comma
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
r_return
op_minus
id|EBUSY
suffix:semicolon
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
id|err
)paren
r_return
id|err
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|master
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
id|CONFIG_DLCI_COUNT
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|master
op_eq
id|open_dev
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|CONFIG_DLCI_COUNT
)paren
id|open_dev
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|master-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|master
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_ioctl
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
DECL|function|dlci_init
r_int
id|dlci_init
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
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dlci_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dlci_local
)paren
)paren
suffix:semicolon
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
id|memset
c_func
(paren
id|dev-&gt;dev_addr
comma
l_int|0
comma
r_sizeof
(paren
id|dev-&gt;dev_addr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlci_setup
r_int
id|__init
id|dlci_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s.&bslash;n&quot;
comma
id|version
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
id|CONFIG_DLCI_COUNT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|open_dev
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|basename
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|basename
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
r_extern
r_int
(paren
op_star
id|dlci_ioctl_hook
)paren
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|dlci_ioctl_hook
op_assign
id|dlci_ioctl
suffix:semicolon
r_return
id|dlci_setup
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|dlci_ioctl_hook
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
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
