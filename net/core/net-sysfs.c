multiline_comment|/*&n; * net-sysfs.c - network device class and attributes&n; *&n; * Copyright (c) 2003 Stephen Hemminger &lt;shemminger@osdl.org&gt;&n; * &n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
DECL|macro|to_class_dev
mdefine_line|#define to_class_dev(obj) container_of(obj,struct class_device,kobj)
DECL|macro|to_net_dev
mdefine_line|#define to_net_dev(class) container_of(class, struct net_device, class_dev)
DECL|variable|fmt_hex
r_static
r_const
r_char
op_star
id|fmt_hex
op_assign
l_string|&quot;%#x&bslash;n&quot;
suffix:semicolon
DECL|variable|fmt_dec
r_static
r_const
r_char
op_star
id|fmt_dec
op_assign
l_string|&quot;%d&bslash;n&quot;
suffix:semicolon
DECL|variable|fmt_ulong
r_static
r_const
r_char
op_star
id|fmt_ulong
op_assign
l_string|&quot;%lu&bslash;n&quot;
suffix:semicolon
DECL|function|dev_isalive
r_static
r_inline
r_int
id|dev_isalive
c_func
(paren
r_const
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;reg_state
op_eq
id|NETREG_REGISTERED
suffix:semicolon
)brace
multiline_comment|/* use same locking rules as GIF* ioctl&squot;s */
DECL|function|netdev_show
r_static
id|ssize_t
id|netdev_show
c_func
(paren
r_const
r_struct
id|class_device
op_star
id|cd
comma
r_char
op_star
id|buf
comma
id|ssize_t
(paren
op_star
id|format
)paren
(paren
r_const
r_struct
id|net_device
op_star
comma
r_char
op_star
)paren
)paren
(brace
r_struct
id|net_device
op_star
id|net
op_assign
id|to_net_dev
c_func
(paren
id|cd
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_isalive
c_func
(paren
id|net
)paren
)paren
id|ret
op_assign
(paren
op_star
id|format
)paren
(paren
id|net
comma
id|buf
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* generate a show function for simple field */
DECL|macro|NETDEVICE_SHOW
mdefine_line|#define NETDEVICE_SHOW(field, format_string)&t;&t;&t;&t;&bslash;&n;static ssize_t format_##field(const struct net_device *net, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf(buf, format_string, net-&gt;field);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t show_##field(struct class_device *cd, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return netdev_show(cd, buf, format_##field);&t;&t;&t;&bslash;&n;}
multiline_comment|/* use same locking and permission rules as SIF* ioctl&squot;s */
DECL|function|netdev_store
r_static
id|ssize_t
id|netdev_store
c_func
(paren
r_struct
id|class_device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
r_int
)paren
)paren
(brace
r_struct
id|net_device
op_star
id|net
op_assign
id|to_net_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_char
op_star
id|endp
suffix:semicolon
r_int
r_int
r_new
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EINVAL
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
r_new
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|endp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|endp
op_eq
id|buf
)paren
r_goto
id|err
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_isalive
c_func
(paren
id|net
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
op_star
id|set
)paren
(paren
id|net
comma
r_new
)paren
)paren
op_eq
l_int|0
)paren
id|ret
op_assign
id|len
suffix:semicolon
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
id|err
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* generate a read-only network device class attribute */
DECL|macro|NETDEVICE_ATTR
mdefine_line|#define NETDEVICE_ATTR(field, format_string)&t;&t;&t;&t;&bslash;&n;NETDEVICE_SHOW(field, format_string)&t;&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO, show_##field, NULL)&t;&t;&bslash;&n;
id|NETDEVICE_ATTR
c_func
(paren
id|addr_len
comma
id|fmt_dec
)paren
suffix:semicolon
id|NETDEVICE_ATTR
c_func
(paren
id|iflink
comma
id|fmt_dec
)paren
suffix:semicolon
id|NETDEVICE_ATTR
c_func
(paren
id|ifindex
comma
id|fmt_dec
)paren
suffix:semicolon
id|NETDEVICE_ATTR
c_func
(paren
id|features
comma
id|fmt_hex
)paren
suffix:semicolon
id|NETDEVICE_ATTR
c_func
(paren
id|type
comma
id|fmt_dec
)paren
suffix:semicolon
multiline_comment|/* use same locking rules as GIFHWADDR ioctl&squot;s */
DECL|function|format_addr
r_static
id|ssize_t
id|format_addr
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_int
r_char
op_star
id|addr
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|cp
op_assign
id|buf
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
id|len
suffix:semicolon
id|i
op_increment
)paren
id|cp
op_add_assign
id|sprintf
c_func
(paren
id|cp
comma
l_string|&quot;%02x%c&quot;
comma
id|addr
(braket
id|i
)braket
comma
id|i
op_eq
(paren
id|len
op_minus
l_int|1
)paren
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_return
id|cp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|show_address
r_static
id|ssize_t
id|show_address
c_func
(paren
r_struct
id|class_device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|net_device
op_star
id|net
op_assign
id|to_net_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_isalive
c_func
(paren
id|net
)paren
)paren
id|ret
op_assign
id|format_addr
c_func
(paren
id|buf
comma
id|net-&gt;dev_addr
comma
id|net-&gt;addr_len
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|show_broadcast
r_static
id|ssize_t
id|show_broadcast
c_func
(paren
r_struct
id|class_device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|net_device
op_star
id|net
op_assign
id|to_net_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_isalive
c_func
(paren
id|net
)paren
)paren
r_return
id|format_addr
c_func
(paren
id|buf
comma
id|net-&gt;broadcast
comma
id|net-&gt;addr_len
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|address
comma
id|S_IRUGO
comma
id|show_address
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|broadcast
comma
id|S_IRUGO
comma
id|show_broadcast
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* read-write attributes */
id|NETDEVICE_SHOW
c_func
(paren
id|mtu
comma
id|fmt_dec
)paren
suffix:semicolon
DECL|function|change_mtu
r_static
r_int
id|change_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|net
comma
r_int
r_int
id|new_mtu
)paren
(brace
r_return
id|dev_set_mtu
c_func
(paren
id|net
comma
(paren
r_int
)paren
id|new_mtu
)paren
suffix:semicolon
)brace
DECL|function|store_mtu
r_static
id|ssize_t
id|store_mtu
c_func
(paren
r_struct
id|class_device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_return
id|netdev_store
c_func
(paren
id|dev
comma
id|buf
comma
id|len
comma
id|change_mtu
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|mtu
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_mtu
comma
id|store_mtu
)paren
suffix:semicolon
id|NETDEVICE_SHOW
c_func
(paren
id|flags
comma
id|fmt_hex
)paren
suffix:semicolon
DECL|function|change_flags
r_static
r_int
id|change_flags
c_func
(paren
r_struct
id|net_device
op_star
id|net
comma
r_int
r_int
id|new_flags
)paren
(brace
r_return
id|dev_change_flags
c_func
(paren
id|net
comma
(paren
r_int
)paren
id|new_flags
)paren
suffix:semicolon
)brace
DECL|function|store_flags
r_static
id|ssize_t
id|store_flags
c_func
(paren
r_struct
id|class_device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_return
id|netdev_store
c_func
(paren
id|dev
comma
id|buf
comma
id|len
comma
id|change_flags
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|flags
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_flags
comma
id|store_flags
)paren
suffix:semicolon
id|NETDEVICE_SHOW
c_func
(paren
id|tx_queue_len
comma
id|fmt_ulong
)paren
suffix:semicolon
DECL|function|change_tx_queue_len
r_static
r_int
id|change_tx_queue_len
c_func
(paren
r_struct
id|net_device
op_star
id|net
comma
r_int
r_int
id|new_len
)paren
(brace
id|net-&gt;tx_queue_len
op_assign
id|new_len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|store_tx_queue_len
r_static
id|ssize_t
id|store_tx_queue_len
c_func
(paren
r_struct
id|class_device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_return
id|netdev_store
c_func
(paren
id|dev
comma
id|buf
comma
id|len
comma
id|change_tx_queue_len
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|tx_queue_len
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_tx_queue_len
comma
id|store_tx_queue_len
)paren
suffix:semicolon
DECL|variable|net_class_attributes
r_static
r_struct
id|class_device_attribute
op_star
id|net_class_attributes
(braket
)braket
op_assign
(brace
op_amp
id|class_device_attr_ifindex
comma
op_amp
id|class_device_attr_iflink
comma
op_amp
id|class_device_attr_addr_len
comma
op_amp
id|class_device_attr_tx_queue_len
comma
op_amp
id|class_device_attr_features
comma
op_amp
id|class_device_attr_mtu
comma
op_amp
id|class_device_attr_flags
comma
op_amp
id|class_device_attr_type
comma
op_amp
id|class_device_attr_address
comma
op_amp
id|class_device_attr_broadcast
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* Show a given an attribute in the statistics group */
DECL|function|netstat_show
r_static
id|ssize_t
id|netstat_show
c_func
(paren
r_const
r_struct
id|class_device
op_star
id|cd
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|offset
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|to_net_dev
c_func
(paren
id|cd
)paren
suffix:semicolon
r_struct
id|net_device_stats
op_star
id|stats
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
op_logical_or
id|offset
op_mod
r_sizeof
(paren
r_int
r_int
)paren
op_ne
l_int|0
)paren
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_isalive
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;get_stats
op_logical_and
(paren
id|stats
op_assign
(paren
op_star
id|dev-&gt;get_stats
)paren
(paren
id|dev
)paren
)paren
)paren
id|ret
op_assign
id|sprintf
c_func
(paren
id|buf
comma
id|fmt_ulong
comma
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
(paren
id|u8
op_star
)paren
id|stats
)paren
op_plus
id|offset
)paren
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* generate a read-only statistics attribute */
DECL|macro|NETSTAT_ENTRY
mdefine_line|#define NETSTAT_ENTRY(name)&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t show_##name(struct class_device *cd, char *buf) &t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return netstat_show(cd, buf, &t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    offsetof(struct net_device_stats, name));&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(name, S_IRUGO, show_##name, NULL)
DECL|variable|rx_packets
id|NETSTAT_ENTRY
c_func
(paren
id|rx_packets
)paren
suffix:semicolon
DECL|variable|tx_packets
id|NETSTAT_ENTRY
c_func
(paren
id|tx_packets
)paren
suffix:semicolon
DECL|variable|rx_bytes
id|NETSTAT_ENTRY
c_func
(paren
id|rx_bytes
)paren
suffix:semicolon
DECL|variable|tx_bytes
id|NETSTAT_ENTRY
c_func
(paren
id|tx_bytes
)paren
suffix:semicolon
DECL|variable|rx_errors
id|NETSTAT_ENTRY
c_func
(paren
id|rx_errors
)paren
suffix:semicolon
DECL|variable|tx_errors
id|NETSTAT_ENTRY
c_func
(paren
id|tx_errors
)paren
suffix:semicolon
DECL|variable|rx_dropped
id|NETSTAT_ENTRY
c_func
(paren
id|rx_dropped
)paren
suffix:semicolon
DECL|variable|tx_dropped
id|NETSTAT_ENTRY
c_func
(paren
id|tx_dropped
)paren
suffix:semicolon
DECL|variable|multicast
id|NETSTAT_ENTRY
c_func
(paren
id|multicast
)paren
suffix:semicolon
DECL|variable|collisions
id|NETSTAT_ENTRY
c_func
(paren
id|collisions
)paren
suffix:semicolon
DECL|variable|rx_length_errors
id|NETSTAT_ENTRY
c_func
(paren
id|rx_length_errors
)paren
suffix:semicolon
DECL|variable|rx_over_errors
id|NETSTAT_ENTRY
c_func
(paren
id|rx_over_errors
)paren
suffix:semicolon
DECL|variable|rx_crc_errors
id|NETSTAT_ENTRY
c_func
(paren
id|rx_crc_errors
)paren
suffix:semicolon
DECL|variable|rx_frame_errors
id|NETSTAT_ENTRY
c_func
(paren
id|rx_frame_errors
)paren
suffix:semicolon
DECL|variable|rx_fifo_errors
id|NETSTAT_ENTRY
c_func
(paren
id|rx_fifo_errors
)paren
suffix:semicolon
DECL|variable|rx_missed_errors
id|NETSTAT_ENTRY
c_func
(paren
id|rx_missed_errors
)paren
suffix:semicolon
DECL|variable|tx_aborted_errors
id|NETSTAT_ENTRY
c_func
(paren
id|tx_aborted_errors
)paren
suffix:semicolon
DECL|variable|tx_carrier_errors
id|NETSTAT_ENTRY
c_func
(paren
id|tx_carrier_errors
)paren
suffix:semicolon
DECL|variable|tx_fifo_errors
id|NETSTAT_ENTRY
c_func
(paren
id|tx_fifo_errors
)paren
suffix:semicolon
DECL|variable|tx_heartbeat_errors
id|NETSTAT_ENTRY
c_func
(paren
id|tx_heartbeat_errors
)paren
suffix:semicolon
DECL|variable|tx_window_errors
id|NETSTAT_ENTRY
c_func
(paren
id|tx_window_errors
)paren
suffix:semicolon
DECL|variable|rx_compressed
id|NETSTAT_ENTRY
c_func
(paren
id|rx_compressed
)paren
suffix:semicolon
DECL|variable|tx_compressed
id|NETSTAT_ENTRY
c_func
(paren
id|tx_compressed
)paren
suffix:semicolon
DECL|variable|netstat_attrs
r_static
r_struct
id|attribute
op_star
id|netstat_attrs
(braket
)braket
op_assign
(brace
op_amp
id|class_device_attr_rx_packets.attr
comma
op_amp
id|class_device_attr_tx_packets.attr
comma
op_amp
id|class_device_attr_rx_bytes.attr
comma
op_amp
id|class_device_attr_tx_bytes.attr
comma
op_amp
id|class_device_attr_rx_errors.attr
comma
op_amp
id|class_device_attr_tx_errors.attr
comma
op_amp
id|class_device_attr_rx_dropped.attr
comma
op_amp
id|class_device_attr_tx_dropped.attr
comma
op_amp
id|class_device_attr_multicast.attr
comma
op_amp
id|class_device_attr_collisions.attr
comma
op_amp
id|class_device_attr_rx_length_errors.attr
comma
op_amp
id|class_device_attr_rx_over_errors.attr
comma
op_amp
id|class_device_attr_rx_crc_errors.attr
comma
op_amp
id|class_device_attr_rx_frame_errors.attr
comma
op_amp
id|class_device_attr_rx_fifo_errors.attr
comma
op_amp
id|class_device_attr_rx_missed_errors.attr
comma
op_amp
id|class_device_attr_tx_aborted_errors.attr
comma
op_amp
id|class_device_attr_tx_carrier_errors.attr
comma
op_amp
id|class_device_attr_tx_fifo_errors.attr
comma
op_amp
id|class_device_attr_tx_heartbeat_errors.attr
comma
op_amp
id|class_device_attr_tx_window_errors.attr
comma
op_amp
id|class_device_attr_rx_compressed.attr
comma
op_amp
id|class_device_attr_tx_compressed.attr
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|netstat_group
r_static
r_struct
id|attribute_group
id|netstat_group
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;statistics&quot;
comma
dot
id|attrs
op_assign
id|netstat_attrs
comma
)brace
suffix:semicolon
macro_line|#ifdef WIRELESS_EXT
multiline_comment|/* helper function that does all the locking etc for wireless stats */
DECL|function|wireless_show
r_static
id|ssize_t
id|wireless_show
c_func
(paren
r_struct
id|class_device
op_star
id|cd
comma
r_char
op_star
id|buf
comma
id|ssize_t
(paren
op_star
id|format
)paren
(paren
r_const
r_struct
id|iw_statistics
op_star
comma
r_char
op_star
)paren
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|to_net_dev
c_func
(paren
id|cd
)paren
suffix:semicolon
r_const
r_struct
id|iw_statistics
op_star
id|iw
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_isalive
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;get_wireless_stats
op_logical_and
(paren
id|iw
op_assign
id|dev
op_member_access_from_pointer
id|get_wireless_stats
c_func
(paren
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
id|ret
op_assign
(paren
op_star
id|format
)paren
(paren
id|iw
comma
id|buf
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* show function template for wireless fields */
DECL|macro|WIRELESS_SHOW
mdefine_line|#define WIRELESS_SHOW(name, field, format_string)&t;&t;&t;&bslash;&n;static ssize_t format_iw_##name(const struct iw_statistics *iw, char *buf) &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf(buf, format_string, iw-&gt;field);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t show_iw_##name(struct class_device *cd, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return wireless_show(cd, buf, format_iw_##name);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(name, S_IRUGO, show_iw_##name, NULL)
id|WIRELESS_SHOW
c_func
(paren
id|status
comma
id|status
comma
id|fmt_hex
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|link
comma
id|qual.qual
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|level
comma
id|qual.level
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|noise
comma
id|qual.noise
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|nwid
comma
id|discard.nwid
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|crypt
comma
id|discard.code
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|fragment
comma
id|discard.fragment
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|misc
comma
id|discard.misc
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|retries
comma
id|discard.retries
comma
id|fmt_dec
)paren
suffix:semicolon
id|WIRELESS_SHOW
c_func
(paren
id|beacon
comma
id|miss.beacon
comma
id|fmt_dec
)paren
suffix:semicolon
DECL|variable|wireless_attrs
r_static
r_struct
id|attribute
op_star
id|wireless_attrs
(braket
)braket
op_assign
(brace
op_amp
id|class_device_attr_status.attr
comma
op_amp
id|class_device_attr_link.attr
comma
op_amp
id|class_device_attr_level.attr
comma
op_amp
id|class_device_attr_noise.attr
comma
op_amp
id|class_device_attr_nwid.attr
comma
op_amp
id|class_device_attr_crypt.attr
comma
op_amp
id|class_device_attr_fragment.attr
comma
op_amp
id|class_device_attr_retries.attr
comma
op_amp
id|class_device_attr_misc.attr
comma
op_amp
id|class_device_attr_beacon.attr
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|wireless_group
r_static
r_struct
id|attribute_group
id|wireless_group
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;wireless&quot;
comma
dot
id|attrs
op_assign
id|wireless_attrs
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HOTPLUG
DECL|function|netdev_hotplug
r_static
r_int
id|netdev_hotplug
c_func
(paren
r_struct
id|class_device
op_star
id|cd
comma
r_char
op_star
op_star
id|envp
comma
r_int
id|num_envp
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|to_net_dev
c_func
(paren
id|cd
)paren
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|n
suffix:semicolon
multiline_comment|/* pass interface in env to hotplug. */
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|buf
suffix:semicolon
id|n
op_assign
id|snprintf
c_func
(paren
id|buf
comma
id|size
comma
l_string|&quot;INTERFACE=%s&quot;
comma
id|dev-&gt;name
)paren
op_plus
l_int|1
suffix:semicolon
id|buf
op_add_assign
id|n
suffix:semicolon
id|size
op_sub_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|envp
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;netdev_release -- destroy and free a dead device. &n; *&t;Called when last reference to class_device kobject is gone.&n; */
DECL|function|netdev_release
r_static
r_void
id|netdev_release
c_func
(paren
r_struct
id|class_device
op_star
id|cd
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|cd
comma
r_struct
id|net_device
comma
id|class_dev
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|dev-&gt;reg_state
op_ne
id|NETREG_RELEASED
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|net_class
r_static
r_struct
r_class
id|net_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;net&quot;
comma
dot
id|release
op_assign
id|netdev_release
comma
macro_line|#ifdef CONFIG_HOTPLUG
dot
id|hotplug
op_assign
id|netdev_hotplug
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|netdev_unregister_sysfs
r_void
id|netdev_unregister_sysfs
c_func
(paren
r_struct
id|net_device
op_star
id|net
)paren
(brace
r_struct
id|class_device
op_star
id|class_dev
op_assign
op_amp
(paren
id|net-&gt;class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net-&gt;get_stats
)paren
id|sysfs_remove_group
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|netstat_group
)paren
suffix:semicolon
macro_line|#ifdef WIRELESS_EXT
r_if
c_cond
(paren
id|net-&gt;get_wireless_stats
)paren
id|sysfs_remove_group
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|wireless_group
)paren
suffix:semicolon
macro_line|#endif
id|class_device_del
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Create sysfs entries for network device. */
DECL|function|netdev_register_sysfs
r_int
id|netdev_register_sysfs
c_func
(paren
r_struct
id|net_device
op_star
id|net
)paren
(brace
r_struct
id|class_device
op_star
id|class_dev
op_assign
op_amp
(paren
id|net-&gt;class_dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|class_device_attribute
op_star
id|attr
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|class_dev
op_member_access_from_pointer
r_class
op_assign
op_amp
id|net_class
suffix:semicolon
id|class_dev-&gt;class_data
op_assign
id|net
suffix:semicolon
id|strlcpy
c_func
(paren
id|class_dev-&gt;class_id
comma
id|net-&gt;name
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|class_device_register
c_func
(paren
id|class_dev
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|attr
op_assign
id|net_class_attributes
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|class_device_create_file
c_func
(paren
id|class_dev
comma
id|attr
)paren
)paren
)paren
r_goto
id|out_unreg
suffix:semicolon
)brace
id|net-&gt;last_stats
op_assign
id|net-&gt;get_stats
suffix:semicolon
r_if
c_cond
(paren
id|net-&gt;get_stats
op_logical_and
(paren
id|ret
op_assign
id|sysfs_create_group
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|netstat_group
)paren
)paren
)paren
r_goto
id|out_unreg
suffix:semicolon
macro_line|#ifdef WIRELESS_EXT
r_if
c_cond
(paren
id|net-&gt;get_wireless_stats
op_logical_and
(paren
id|ret
op_assign
id|sysfs_create_group
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|wireless_group
)paren
)paren
)paren
r_goto
id|out_cleanup
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_cleanup
suffix:colon
r_if
c_cond
(paren
id|net-&gt;get_stats
)paren
id|sysfs_remove_group
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|netstat_group
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
id|out_unreg
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: sysfs attribute registration failed %d&bslash;n&quot;
comma
id|net-&gt;name
comma
id|ret
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|netdev_sysfs_init
r_int
id|netdev_sysfs_init
c_func
(paren
r_void
)paren
(brace
r_return
id|class_register
c_func
(paren
op_amp
id|net_class
)paren
suffix:semicolon
)brace
eof
