multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the INET interface module.&n; *&n; * Version:&t;@(#)if.h&t;1.0.2&t;04/18/93&n; *&n; * Authors:&t;Original taken from Berkeley UNIX 4.3, (c) UCB 1982-1988&n; *&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_H
DECL|macro|_LINUX_IF_H
mdefine_line|#define _LINUX_IF_H
macro_line|#include &lt;linux/types.h&gt;&t;&t;/* for &quot;__kernel_caddr_t&quot; et al&t;*/
macro_line|#include &lt;linux/socket.h&gt;&t;&t;/* for &quot;struct sockaddr&quot; et al&t;*/
DECL|macro|IFNAMSIZ
mdefine_line|#define&t;IFNAMSIZ&t;16
macro_line|#include &lt;linux/hdlc/ioctl.h&gt;
multiline_comment|/* Standard interface flags (netdevice-&gt;flags). */
DECL|macro|IFF_UP
mdefine_line|#define&t;IFF_UP&t;&t;0x1&t;&t;/* interface is up&t;&t;*/
DECL|macro|IFF_BROADCAST
mdefine_line|#define&t;IFF_BROADCAST&t;0x2&t;&t;/* broadcast address valid&t;*/
DECL|macro|IFF_DEBUG
mdefine_line|#define&t;IFF_DEBUG&t;0x4&t;&t;/* turn on debugging&t;&t;*/
DECL|macro|IFF_LOOPBACK
mdefine_line|#define&t;IFF_LOOPBACK&t;0x8&t;&t;/* is a loopback net&t;&t;*/
DECL|macro|IFF_POINTOPOINT
mdefine_line|#define&t;IFF_POINTOPOINT&t;0x10&t;&t;/* interface is has p-p link&t;*/
DECL|macro|IFF_NOTRAILERS
mdefine_line|#define&t;IFF_NOTRAILERS&t;0x20&t;&t;/* avoid use of trailers&t;*/
DECL|macro|IFF_RUNNING
mdefine_line|#define&t;IFF_RUNNING&t;0x40&t;&t;/* resources allocated&t;&t;*/
DECL|macro|IFF_NOARP
mdefine_line|#define&t;IFF_NOARP&t;0x80&t;&t;/* no ARP protocol&t;&t;*/
DECL|macro|IFF_PROMISC
mdefine_line|#define&t;IFF_PROMISC&t;0x100&t;&t;/* receive all packets&t;&t;*/
DECL|macro|IFF_ALLMULTI
mdefine_line|#define&t;IFF_ALLMULTI&t;0x200&t;&t;/* receive all multicast packets*/
DECL|macro|IFF_MASTER
mdefine_line|#define IFF_MASTER&t;0x400&t;&t;/* master of a load balancer &t;*/
DECL|macro|IFF_SLAVE
mdefine_line|#define IFF_SLAVE&t;0x800&t;&t;/* slave of a load balancer&t;*/
DECL|macro|IFF_MULTICAST
mdefine_line|#define IFF_MULTICAST&t;0x1000&t;&t;/* Supports multicast&t;&t;*/
DECL|macro|IFF_VOLATILE
mdefine_line|#define IFF_VOLATILE&t;(IFF_LOOPBACK|IFF_POINTOPOINT|IFF_BROADCAST|IFF_MASTER|IFF_SLAVE|IFF_RUNNING)
DECL|macro|IFF_PORTSEL
mdefine_line|#define IFF_PORTSEL&t;0x2000          /* can set media type&t;&t;*/
DECL|macro|IFF_AUTOMEDIA
mdefine_line|#define IFF_AUTOMEDIA&t;0x4000&t;&t;/* auto media select active&t;*/
DECL|macro|IFF_DYNAMIC
mdefine_line|#define IFF_DYNAMIC&t;0x8000&t;&t;/* dialup device with changing addresses*/
multiline_comment|/* Private (from user) interface flags (netdevice-&gt;priv_flags). */
DECL|macro|IFF_802_1Q_VLAN
mdefine_line|#define IFF_802_1Q_VLAN 0x1             /* 802.1Q VLAN device.          */
DECL|macro|IFF_EBRIDGE
mdefine_line|#define IFF_EBRIDGE&t;0x2&t;&t;/* Ethernet bridging device.&t;*/
DECL|macro|IF_GET_IFACE
mdefine_line|#define IF_GET_IFACE&t;0x0001&t;&t;/* for querying only */
DECL|macro|IF_GET_PROTO
mdefine_line|#define IF_GET_PROTO&t;0x0002
multiline_comment|/* For definitions see hdlc.h */
DECL|macro|IF_IFACE_V35
mdefine_line|#define IF_IFACE_V35&t;0x1000&t;&t;/* V.35 serial interface&t;*/
DECL|macro|IF_IFACE_V24
mdefine_line|#define IF_IFACE_V24&t;0x1001&t;&t;/* V.24 serial interface&t;*/
DECL|macro|IF_IFACE_X21
mdefine_line|#define IF_IFACE_X21&t;0x1002&t;&t;/* X.21 serial interface&t;*/
DECL|macro|IF_IFACE_T1
mdefine_line|#define IF_IFACE_T1&t;0x1003&t;&t;/* T1 telco serial interface&t;*/
DECL|macro|IF_IFACE_E1
mdefine_line|#define IF_IFACE_E1&t;0x1004&t;&t;/* E1 telco serial interface&t;*/
DECL|macro|IF_IFACE_SYNC_SERIAL
mdefine_line|#define IF_IFACE_SYNC_SERIAL 0x1005&t;/* can&squot;t be set by software&t;*/
multiline_comment|/* For definitions see hdlc.h */
DECL|macro|IF_PROTO_HDLC
mdefine_line|#define IF_PROTO_HDLC&t;0x2000&t;&t;/* raw HDLC protocol&t;&t;*/
DECL|macro|IF_PROTO_PPP
mdefine_line|#define IF_PROTO_PPP&t;0x2001&t;&t;/* PPP protocol&t;&t;&t;*/
DECL|macro|IF_PROTO_CISCO
mdefine_line|#define IF_PROTO_CISCO&t;0x2002&t;&t;/* Cisco HDLC protocol&t;&t;*/
DECL|macro|IF_PROTO_FR
mdefine_line|#define IF_PROTO_FR&t;0x2003&t;&t;/* Frame Relay protocol&t;&t;*/
DECL|macro|IF_PROTO_FR_ADD_PVC
mdefine_line|#define IF_PROTO_FR_ADD_PVC 0x2004&t;/*    Create FR PVC&t;&t;*/
DECL|macro|IF_PROTO_FR_DEL_PVC
mdefine_line|#define IF_PROTO_FR_DEL_PVC 0x2005&t;/*    Delete FR PVC&t;&t;*/
DECL|macro|IF_PROTO_X25
mdefine_line|#define IF_PROTO_X25&t;0x2006&t;&t;/* X.25&t;&t;&t;&t;*/
DECL|macro|IF_PROTO_HDLC_ETH
mdefine_line|#define IF_PROTO_HDLC_ETH 0x2007&t;/* raw HDLC, Ethernet emulation&t;*/
DECL|macro|IF_PROTO_FR_ADD_ETH_PVC
mdefine_line|#define IF_PROTO_FR_ADD_ETH_PVC 0x2008&t;/*  Create FR Ethernet-bridged PVC */
DECL|macro|IF_PROTO_FR_DEL_ETH_PVC
mdefine_line|#define IF_PROTO_FR_DEL_ETH_PVC 0x2009&t;/*  Delete FR Ethernet-bridged PVC */
DECL|macro|IF_PROTO_FR_PVC
mdefine_line|#define IF_PROTO_FR_PVC&t;0x200A&t;&t;/* for reading PVC status&t;*/
DECL|macro|IF_PROTO_FR_ETH_PVC
mdefine_line|#define IF_PROTO_FR_ETH_PVC 0x200B
multiline_comment|/*&n; *&t;Device mapping structure. I&squot;d just gone off and designed a &n; *&t;beautiful scheme using only loadable modules with arguments&n; *&t;for driver options and along come the PCMCIA people 8)&n; *&n; *&t;Ah well. The get() side of this is good for WDSETUP, and it&squot;ll&n; *&t;be handy for debugging things. The set side is fine for now and&n; *&t;being very small might be worth keeping for clean configuration.&n; */
DECL|struct|ifmap
r_struct
id|ifmap
(brace
DECL|member|mem_start
r_int
r_int
id|mem_start
suffix:semicolon
DECL|member|mem_end
r_int
r_int
id|mem_end
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|dma
r_int
r_char
id|dma
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
multiline_comment|/* 3 bytes spare */
)brace
suffix:semicolon
DECL|struct|if_settings
r_struct
id|if_settings
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* Type of physical device or protocol */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* Size of the data allocated by the caller */
r_union
(brace
multiline_comment|/* {atm/eth/dsl}_settings anyone ? */
DECL|member|raw_hdlc
id|raw_hdlc_proto
op_star
id|raw_hdlc
suffix:semicolon
DECL|member|cisco
id|cisco_proto
op_star
id|cisco
suffix:semicolon
DECL|member|fr
id|fr_proto
op_star
id|fr
suffix:semicolon
DECL|member|fr_pvc
id|fr_proto_pvc
op_star
id|fr_pvc
suffix:semicolon
DECL|member|fr_pvc_info
id|fr_proto_pvc_info
op_star
id|fr_pvc_info
suffix:semicolon
multiline_comment|/* interface settings */
DECL|member|sync
id|sync_serial_settings
op_star
id|sync
suffix:semicolon
DECL|member|te1
id|te1_settings
op_star
id|te1
suffix:semicolon
DECL|member|ifs_ifsu
)brace
id|ifs_ifsu
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Interface request structure used for socket&n; * ioctl&squot;s.  All interface ioctl&squot;s must have parameter&n; * definitions which begin with ifr_name.  The&n; * remainder may be interface specific.&n; */
DECL|struct|ifreq
r_struct
id|ifreq
(brace
DECL|macro|IFHWADDRLEN
mdefine_line|#define IFHWADDRLEN&t;6
r_union
(brace
DECL|member|ifrn_name
r_char
id|ifrn_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* if name, e.g. &quot;en0&quot; */
DECL|member|ifr_ifrn
)brace
id|ifr_ifrn
suffix:semicolon
r_union
(brace
DECL|member|ifru_addr
r_struct
id|sockaddr
id|ifru_addr
suffix:semicolon
DECL|member|ifru_dstaddr
r_struct
id|sockaddr
id|ifru_dstaddr
suffix:semicolon
DECL|member|ifru_broadaddr
r_struct
id|sockaddr
id|ifru_broadaddr
suffix:semicolon
DECL|member|ifru_netmask
r_struct
id|sockaddr
id|ifru_netmask
suffix:semicolon
DECL|member|ifru_hwaddr
r_struct
id|sockaddr
id|ifru_hwaddr
suffix:semicolon
DECL|member|ifru_flags
r_int
id|ifru_flags
suffix:semicolon
DECL|member|ifru_ivalue
r_int
id|ifru_ivalue
suffix:semicolon
DECL|member|ifru_mtu
r_int
id|ifru_mtu
suffix:semicolon
DECL|member|ifru_map
r_struct
id|ifmap
id|ifru_map
suffix:semicolon
DECL|member|ifru_slave
r_char
id|ifru_slave
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Just fits the size */
DECL|member|ifru_newname
r_char
id|ifru_newname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|ifru_data
r_char
id|__user
op_star
id|ifru_data
suffix:semicolon
DECL|member|ifru_settings
r_struct
id|if_settings
id|ifru_settings
suffix:semicolon
DECL|member|ifr_ifru
)brace
id|ifr_ifru
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ifr_name
mdefine_line|#define ifr_name&t;ifr_ifrn.ifrn_name&t;/* interface name &t;*/
DECL|macro|ifr_hwaddr
mdefine_line|#define ifr_hwaddr&t;ifr_ifru.ifru_hwaddr&t;/* MAC address &t;&t;*/
DECL|macro|ifr_addr
mdefine_line|#define&t;ifr_addr&t;ifr_ifru.ifru_addr&t;/* address&t;&t;*/
DECL|macro|ifr_dstaddr
mdefine_line|#define&t;ifr_dstaddr&t;ifr_ifru.ifru_dstaddr&t;/* other end of p-p lnk&t;*/
DECL|macro|ifr_broadaddr
mdefine_line|#define&t;ifr_broadaddr&t;ifr_ifru.ifru_broadaddr&t;/* broadcast address&t;*/
DECL|macro|ifr_netmask
mdefine_line|#define&t;ifr_netmask&t;ifr_ifru.ifru_netmask&t;/* interface net mask&t;*/
DECL|macro|ifr_flags
mdefine_line|#define&t;ifr_flags&t;ifr_ifru.ifru_flags&t;/* flags&t;&t;*/
DECL|macro|ifr_metric
mdefine_line|#define&t;ifr_metric&t;ifr_ifru.ifru_ivalue&t;/* metric&t;&t;*/
DECL|macro|ifr_mtu
mdefine_line|#define&t;ifr_mtu&t;&t;ifr_ifru.ifru_mtu&t;/* mtu&t;&t;&t;*/
DECL|macro|ifr_map
mdefine_line|#define ifr_map&t;&t;ifr_ifru.ifru_map&t;/* device map&t;&t;*/
DECL|macro|ifr_slave
mdefine_line|#define ifr_slave&t;ifr_ifru.ifru_slave&t;/* slave device&t;&t;*/
DECL|macro|ifr_data
mdefine_line|#define&t;ifr_data&t;ifr_ifru.ifru_data&t;/* for use by interface&t;*/
DECL|macro|ifr_ifindex
mdefine_line|#define ifr_ifindex&t;ifr_ifru.ifru_ivalue&t;/* interface index&t;*/
DECL|macro|ifr_bandwidth
mdefine_line|#define ifr_bandwidth&t;ifr_ifru.ifru_ivalue    /* link bandwidth&t;*/
DECL|macro|ifr_qlen
mdefine_line|#define ifr_qlen&t;ifr_ifru.ifru_ivalue&t;/* Queue length &t;*/
DECL|macro|ifr_newname
mdefine_line|#define ifr_newname&t;ifr_ifru.ifru_newname&t;/* New name&t;&t;*/
DECL|macro|ifr_settings
mdefine_line|#define ifr_settings&t;ifr_ifru.ifru_settings&t;/* Device/proto settings*/
multiline_comment|/*&n; * Structure used in SIOCGIFCONF request.&n; * Used to retrieve interface configuration&n; * for machine (useful for programs which&n; * must know all networks accessible).&n; */
DECL|struct|ifconf
r_struct
id|ifconf
(brace
DECL|member|ifc_len
r_int
id|ifc_len
suffix:semicolon
multiline_comment|/* size of buffer&t;*/
r_union
(brace
DECL|member|ifcu_buf
r_char
op_star
id|ifcu_buf
suffix:semicolon
DECL|member|ifcu_req
r_struct
id|ifreq
op_star
id|ifcu_req
suffix:semicolon
DECL|member|ifc_ifcu
)brace
id|ifc_ifcu
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ifc_buf
mdefine_line|#define&t;ifc_buf&t;ifc_ifcu.ifcu_buf&t;&t;/* buffer address&t;*/
DECL|macro|ifc_req
mdefine_line|#define&t;ifc_req&t;ifc_ifcu.ifcu_req&t;&t;/* array of structures&t;*/
macro_line|#endif /* _LINUX_IF_H */
eof
