multiline_comment|/*****************************************************************************&n;* wanrouter.h&t;Definitions for the WAN Multiprotocol Router Module.&n;*&t;&t;This module provides API and common services for WAN Link&n;*&t;&t;Drivers and is completely hardware-independent.&n;*&n;* Author: &t;Nenad Corbic &lt;ncorbic@sangoma.com&gt;&n;*&t;&t;Gideon Hack &t;&n;*&n;* Copyright:&t;(c) 1995-2000 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jul 21, 2000  Nenad Corbic&t;Added WAN_FT1_READY State&n;* Feb 24, 2000  Nenad Corbic    Added support for socket based x25api&n;* Jan 28, 2000  Nenad Corbic    Added support for the ASYNC protocol.&n;* Oct 04, 1999  Nenad Corbic &t;Updated for 2.1.0 release&n;* Jun 02, 1999  Gideon Hack&t;Added support for the S514 adapter.&n;* Jul 20, 1998&t;David Fong&t;Added Inverse ARP options to &squot;wanif_conf_t&squot;&n;* Jun 12, 1998&t;David Fong&t;Added Cisco HDLC support.&n;* Dec 16, 1997&t;Jaspreet Singh&t;Moved &squot;enable_IPX&squot; and &squot;network_number&squot; to&n;*&t;&t;&t;&t;&squot;wanif_conf_t&squot;&n;* Dec 05, 1997&t;Jaspreet Singh&t;Added &squot;pap&squot;, &squot;chap&squot; to &squot;wanif_conf_t&squot;&n;*&t;&t;&t;&t;Added &squot;authenticator&squot; to &squot;wan_ppp_conf_t&squot;&n;* Nov 06, 1997&t;Jaspreet Singh&t;Changed Router Driver version to 1.1 from 1.0&n;* Oct 20, 1997&t;Jaspreet Singh&t;Added &squot;cir&squot;,&squot;bc&squot;,&squot;be&squot; and &squot;mc&squot; to &squot;wanif_conf_t&squot;&n;*&t;&t;&t;&t;Added &squot;enable_IPX&squot; and &squot;network_number&squot; to &n;*&t;&t;&t;&t;&squot;wan_device_t&squot;.  Also added defines for&n;*&t;&t;&t;&t;UDP PACKET TYPE, Interrupt test, critical values&n;*&t;&t;&t;&t;for RACE conditions.&n;* Oct 05, 1997&t;Jaspreet Singh&t;Added &squot;dlci_num&squot; and &squot;dlci[100]&squot; to &n;*&t;&t;&t;&t;&squot;wan_fr_conf_t&squot; to configure a list of dlci(s)&n;*&t;&t;&t;&t;for a NODE &n;* Jul 07, 1997&t;Jaspreet Singh&t;Added &squot;ttl&squot; to &squot;wandev_conf_t&squot; &amp; &squot;wan_device_t&squot;&n;* May 29, 1997 &t;Jaspreet Singh&t;Added &squot;tx_int_enabled&squot; to &squot;wan_device_t&squot;&n;* May 21, 1997&t;Jaspreet Singh&t;Added &squot;udp_port&squot; to &squot;wan_device_t&squot;&n;* Apr 25, 1997  Farhan Thawar   Added &squot;udp_port&squot; to &squot;wandev_conf_t&squot;&n;* Jan 16, 1997&t;Gene Kozin&t;router_devlist made public&n;* Jan 02, 1997&t;Gene Kozin&t;Initial version (based on wanpipe.h).&n;*****************************************************************************/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(a,b,c) (((a) &lt;&lt; 16) + ((b) &lt;&lt; 8) + (c))
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
DECL|macro|LINUX_2_4
mdefine_line|#define LINUX_2_4
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct net_device
macro_line|#include &lt;linux/spinlock.h&gt;       /* Support for SMP Locking */
macro_line|#elif LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
DECL|macro|LINUX_2_1
mdefine_line|#define LINUX_2_1
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct device
macro_line|#include &lt;asm/spinlock.h&gt;       /* Support for SMP Locking */
macro_line|#else
DECL|macro|LINUX_2_0
mdefine_line|#define LINUX_2_0
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct device
DECL|macro|spinlock_t
mdefine_line|#define spinlock_t int
macro_line|#endif
macro_line|#ifndef&t;_ROUTER_H
DECL|macro|_ROUTER_H
mdefine_line|#define&t;_ROUTER_H
DECL|macro|ROUTER_NAME
mdefine_line|#define&t;ROUTER_NAME&t;&quot;wanrouter&quot;&t;/* in case we ever change it */
DECL|macro|ROUTER_VERSION
mdefine_line|#define&t;ROUTER_VERSION&t;1&t;&t;/* version number */
DECL|macro|ROUTER_RELEASE
mdefine_line|#define&t;ROUTER_RELEASE&t;1&t;&t;/* release (minor version) number */
DECL|macro|ROUTER_IOCTL
mdefine_line|#define&t;ROUTER_IOCTL&t;&squot;W&squot;&t;&t;/* for IOCTL calls */
DECL|macro|ROUTER_MAGIC
mdefine_line|#define&t;ROUTER_MAGIC&t;0x524D4157L&t;/* signature: &squot;WANR&squot; reversed */
multiline_comment|/* IOCTL codes for /proc/router/&lt;device&gt; entries (up to 255) */
DECL|enum|router_ioctls
r_enum
id|router_ioctls
(brace
DECL|enumerator|ROUTER_SETUP
id|ROUTER_SETUP
op_assign
id|ROUTER_IOCTL
op_lshift
l_int|8
comma
multiline_comment|/* configure device */
DECL|enumerator|ROUTER_DOWN
id|ROUTER_DOWN
comma
multiline_comment|/* shut down device */
DECL|enumerator|ROUTER_STAT
id|ROUTER_STAT
comma
multiline_comment|/* get device status */
DECL|enumerator|ROUTER_IFNEW
id|ROUTER_IFNEW
comma
multiline_comment|/* add interface */
DECL|enumerator|ROUTER_IFDEL
id|ROUTER_IFDEL
comma
multiline_comment|/* delete interface */
DECL|enumerator|ROUTER_IFSTAT
id|ROUTER_IFSTAT
comma
multiline_comment|/* get interface status */
DECL|enumerator|ROUTER_USER
id|ROUTER_USER
op_assign
(paren
id|ROUTER_IOCTL
op_lshift
l_int|8
)paren
op_plus
l_int|16
comma
multiline_comment|/* driver-specific calls */
DECL|enumerator|ROUTER_USER_MAX
id|ROUTER_USER_MAX
op_assign
(paren
id|ROUTER_IOCTL
op_lshift
l_int|8
)paren
op_plus
l_int|31
)brace
suffix:semicolon
multiline_comment|/* identifiers for displaying proc file data for dual port adapters */
DECL|macro|PROC_DATA_PORT_0
mdefine_line|#define PROC_DATA_PORT_0 0x8000&t;/* the data is for port 0 */
DECL|macro|PROC_DATA_PORT_1
mdefine_line|#define PROC_DATA_PORT_1 0x8001&t;/* the data is for port 1 */
multiline_comment|/* NLPID for packet encapsulation (ISO/IEC TR 9577) */
DECL|macro|NLPID_IP
mdefine_line|#define&t;NLPID_IP&t;0xCC&t;/* Internet Protocol Datagram */
DECL|macro|NLPID_SNAP
mdefine_line|#define&t;NLPID_SNAP&t;0x80&t;/* IEEE Subnetwork Access Protocol */
DECL|macro|NLPID_CLNP
mdefine_line|#define&t;NLPID_CLNP&t;0x81&t;/* ISO/IEC 8473 */
DECL|macro|NLPID_ESIS
mdefine_line|#define&t;NLPID_ESIS&t;0x82&t;/* ISO/IEC 9542 */
DECL|macro|NLPID_ISIS
mdefine_line|#define&t;NLPID_ISIS&t;0x83&t;/* ISO/IEC ISIS */
DECL|macro|NLPID_Q933
mdefine_line|#define&t;NLPID_Q933&t;0x08&t;/* CCITT Q.933 */
multiline_comment|/* Miscellaneous */
DECL|macro|WAN_IFNAME_SZ
mdefine_line|#define&t;WAN_IFNAME_SZ&t;15&t;/* max length of the interface name */
DECL|macro|WAN_DRVNAME_SZ
mdefine_line|#define&t;WAN_DRVNAME_SZ&t;15&t;/* max length of the link driver name */
DECL|macro|WAN_ADDRESS_SZ
mdefine_line|#define&t;WAN_ADDRESS_SZ&t;31&t;/* max length of the WAN media address */
DECL|macro|USED_BY_FIELD
mdefine_line|#define USED_BY_FIELD&t;8&t;/* max length of the used by field */
multiline_comment|/* Defines for UDP PACKET TYPE */
DECL|macro|UDP_PTPIPE_TYPE
mdefine_line|#define UDP_PTPIPE_TYPE &t;0x01
DECL|macro|UDP_FPIPE_TYPE
mdefine_line|#define UDP_FPIPE_TYPE&t;&t;0x02
DECL|macro|UDP_CPIPE_TYPE
mdefine_line|#define UDP_CPIPE_TYPE&t;&t;0x03
DECL|macro|UDP_DRVSTATS_TYPE
mdefine_line|#define UDP_DRVSTATS_TYPE &t;0x04
DECL|macro|UDP_INVALID_TYPE
mdefine_line|#define UDP_INVALID_TYPE  &t;0x05
multiline_comment|/* Command return code */
DECL|macro|CMD_OK
mdefine_line|#define CMD_OK&t;&t;0&t;&t;/* normal firmware return code */
DECL|macro|CMD_TIMEOUT
mdefine_line|#define CMD_TIMEOUT&t;0xFF&t;&t;/* firmware command timed out */
multiline_comment|/* UDP Packet Management */
DECL|macro|UDP_PKT_FRM_STACK
mdefine_line|#define UDP_PKT_FRM_STACK&t;0x00
DECL|macro|UDP_PKT_FRM_NETWORK
mdefine_line|#define UDP_PKT_FRM_NETWORK&t;0x01
multiline_comment|/* Maximum interrupt test counter */
DECL|macro|MAX_INTR_TEST_COUNTER
mdefine_line|#define MAX_INTR_TEST_COUNTER&t;100
multiline_comment|/* Critical Values for RACE conditions*/
DECL|macro|CRITICAL_IN_ISR
mdefine_line|#define CRITICAL_IN_ISR&t;&t;0xA1
DECL|macro|CRITICAL_INTR_HANDLED
mdefine_line|#define CRITICAL_INTR_HANDLED&t;0xB1
multiline_comment|/****** Data Types **********************************************************/
multiline_comment|/*----------------------------------------------------------------------------&n; * X.25-specific link-level configuration.&n; */
DECL|struct|wan_x25_conf
r_typedef
r_struct
id|wan_x25_conf
(brace
DECL|member|lo_pvc
r_int
id|lo_pvc
suffix:semicolon
multiline_comment|/* lowest permanent circuit number */
DECL|member|hi_pvc
r_int
id|hi_pvc
suffix:semicolon
multiline_comment|/* highest permanent circuit number */
DECL|member|lo_svc
r_int
id|lo_svc
suffix:semicolon
multiline_comment|/* lowest switched circuit number */
DECL|member|hi_svc
r_int
id|hi_svc
suffix:semicolon
multiline_comment|/* highest switched circuit number */
DECL|member|hdlc_window
r_int
id|hdlc_window
suffix:semicolon
multiline_comment|/* HDLC window size (1..7) */
DECL|member|pkt_window
r_int
id|pkt_window
suffix:semicolon
multiline_comment|/* X.25 packet window size (1..7) */
DECL|member|t1
r_int
id|t1
suffix:semicolon
multiline_comment|/* HDLC timer T1, sec (1..30) */
DECL|member|t2
r_int
id|t2
suffix:semicolon
multiline_comment|/* HDLC timer T2, sec (0..29) */
DECL|member|t4
r_int
id|t4
suffix:semicolon
multiline_comment|/* HDLC supervisory frame timer = T4 * T1 */
DECL|member|n2
r_int
id|n2
suffix:semicolon
multiline_comment|/* HDLC retransmission limit (1..30) */
DECL|member|t10_t20
r_int
id|t10_t20
suffix:semicolon
multiline_comment|/* X.25 RESTART timeout, sec (1..255) */
DECL|member|t11_t21
r_int
id|t11_t21
suffix:semicolon
multiline_comment|/* X.25 CALL timeout, sec (1..255) */
DECL|member|t12_t22
r_int
id|t12_t22
suffix:semicolon
multiline_comment|/* X.25 RESET timeout, sec (1..255) */
DECL|member|t13_t23
r_int
id|t13_t23
suffix:semicolon
multiline_comment|/* X.25 CLEAR timeout, sec (1..255) */
DECL|member|t16_t26
r_int
id|t16_t26
suffix:semicolon
multiline_comment|/* X.25 INTERRUPT timeout, sec (1..255) */
DECL|member|t28
r_int
id|t28
suffix:semicolon
multiline_comment|/* X.25 REGISTRATION timeout, sec (1..255) */
DECL|member|r10_r20
r_int
id|r10_r20
suffix:semicolon
multiline_comment|/* RESTART retransmission limit (0..250) */
DECL|member|r12_r22
r_int
id|r12_r22
suffix:semicolon
multiline_comment|/* RESET retransmission limit (0..250) */
DECL|member|r13_r23
r_int
id|r13_r23
suffix:semicolon
multiline_comment|/* CLEAR retransmission limit (0..250) */
DECL|member|ccitt_compat
r_int
id|ccitt_compat
suffix:semicolon
multiline_comment|/* compatibility mode: 1988/1984/1980 */
DECL|member|x25_conf_opt
r_int
id|x25_conf_opt
suffix:semicolon
multiline_comment|/* User defined x25 config optoins */
DECL|member|LAPB_hdlc_only
r_int
r_char
id|LAPB_hdlc_only
suffix:semicolon
multiline_comment|/* Run in HDLC only mode */
DECL|member|logging
r_int
r_char
id|logging
suffix:semicolon
multiline_comment|/* Control connection logging */
DECL|member|oob_on_modem
r_int
r_char
id|oob_on_modem
suffix:semicolon
multiline_comment|/* Whether to send modem status to the user app */
DECL|typedef|wan_x25_conf_t
)brace
id|wan_x25_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Frame relay specific link-level configuration.&n; */
DECL|struct|wan_fr_conf
r_typedef
r_struct
id|wan_fr_conf
(brace
DECL|member|signalling
r_int
id|signalling
suffix:semicolon
multiline_comment|/* local in-channel signalling type */
DECL|member|t391
r_int
id|t391
suffix:semicolon
multiline_comment|/* link integrity verification timer */
DECL|member|t392
r_int
id|t392
suffix:semicolon
multiline_comment|/* polling verification timer */
DECL|member|n391
r_int
id|n391
suffix:semicolon
multiline_comment|/* full status polling cycle counter */
DECL|member|n392
r_int
id|n392
suffix:semicolon
multiline_comment|/* error threshold counter */
DECL|member|n393
r_int
id|n393
suffix:semicolon
multiline_comment|/* monitored events counter */
DECL|member|dlci_num
r_int
id|dlci_num
suffix:semicolon
multiline_comment|/* number of DLCs (access node) */
DECL|member|dlci
r_int
id|dlci
(braket
l_int|100
)braket
suffix:semicolon
multiline_comment|/* List of all DLCIs */
DECL|typedef|wan_fr_conf_t
)brace
id|wan_fr_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * PPP-specific link-level configuration.&n; */
DECL|struct|wan_ppp_conf
r_typedef
r_struct
id|wan_ppp_conf
(brace
DECL|member|restart_tmr
r_int
id|restart_tmr
suffix:semicolon
multiline_comment|/* restart timer */
DECL|member|auth_rsrt_tmr
r_int
id|auth_rsrt_tmr
suffix:semicolon
multiline_comment|/* authentication timer */
DECL|member|auth_wait_tmr
r_int
id|auth_wait_tmr
suffix:semicolon
multiline_comment|/* authentication timer */
DECL|member|mdm_fail_tmr
r_int
id|mdm_fail_tmr
suffix:semicolon
multiline_comment|/* modem failure timer */
DECL|member|dtr_drop_tmr
r_int
id|dtr_drop_tmr
suffix:semicolon
multiline_comment|/* DTR drop timer */
DECL|member|connect_tmout
r_int
id|connect_tmout
suffix:semicolon
multiline_comment|/* connection timeout */
DECL|member|conf_retry
r_int
id|conf_retry
suffix:semicolon
multiline_comment|/* max. retry */
DECL|member|term_retry
r_int
id|term_retry
suffix:semicolon
multiline_comment|/* max. retry */
DECL|member|fail_retry
r_int
id|fail_retry
suffix:semicolon
multiline_comment|/* max. retry */
DECL|member|auth_retry
r_int
id|auth_retry
suffix:semicolon
multiline_comment|/* max. retry */
DECL|member|auth_options
r_int
id|auth_options
suffix:semicolon
multiline_comment|/* authentication opt. */
DECL|member|ip_options
r_int
id|ip_options
suffix:semicolon
multiline_comment|/* IP options */
DECL|member|authenticator
r_char
id|authenticator
suffix:semicolon
multiline_comment|/* AUTHENTICATOR or not */
DECL|member|ip_mode
r_char
id|ip_mode
suffix:semicolon
multiline_comment|/* Static/Host/Peer */
DECL|typedef|wan_ppp_conf_t
)brace
id|wan_ppp_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * CHDLC-specific link-level configuration.&n; */
DECL|struct|wan_chdlc_conf
r_typedef
r_struct
id|wan_chdlc_conf
(brace
DECL|member|ignore_dcd
r_int
r_char
id|ignore_dcd
suffix:semicolon
multiline_comment|/* Protocol options:&t;&t;*/
DECL|member|ignore_cts
r_int
r_char
id|ignore_cts
suffix:semicolon
multiline_comment|/*  Ignore these to determine&t;*/
DECL|member|ignore_keepalive
r_int
r_char
id|ignore_keepalive
suffix:semicolon
multiline_comment|/*  link status (Yes or No)&t;*/
DECL|member|hdlc_streaming
r_int
r_char
id|hdlc_streaming
suffix:semicolon
multiline_comment|/*  hdlc_streaming mode (Y/N) */
DECL|member|receive_only
r_int
r_char
id|receive_only
suffix:semicolon
multiline_comment|/*  no transmit buffering (Y/N) */
DECL|member|keepalive_tx_tmr
r_int
id|keepalive_tx_tmr
suffix:semicolon
multiline_comment|/* transmit keepalive timer */
DECL|member|keepalive_rx_tmr
r_int
id|keepalive_rx_tmr
suffix:semicolon
multiline_comment|/* receive  keepalive timer */
DECL|member|keepalive_err_margin
r_int
id|keepalive_err_margin
suffix:semicolon
multiline_comment|/* keepalive_error_tolerance */
DECL|member|slarp_timer
r_int
id|slarp_timer
suffix:semicolon
multiline_comment|/* SLARP request timer */
DECL|typedef|wan_chdlc_conf_t
)brace
id|wan_chdlc_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * WAN device configuration. Passed to ROUTER_SETUP IOCTL.&n; */
DECL|struct|wandev_conf
r_typedef
r_struct
id|wandev_conf
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number (for verification) */
DECL|member|config_id
r_int
id|config_id
suffix:semicolon
multiline_comment|/* configuration structure identifier */
multiline_comment|/****** hardware configuration ******/
DECL|member|ioport
r_int
id|ioport
suffix:semicolon
multiline_comment|/* adapter I/O port base */
DECL|member|maddr
r_int
r_int
id|maddr
suffix:semicolon
multiline_comment|/* dual-port memory address */
DECL|member|msize
r_int
id|msize
suffix:semicolon
multiline_comment|/* dual-port memory size */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt request level */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* DMA request level */
DECL|member|S514_CPU_no
r_char
id|S514_CPU_no
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* S514 PCI adapter CPU number (&squot;A&squot; or &squot;B&squot;) */
DECL|member|PCI_slot_no
r_int
id|PCI_slot_no
suffix:semicolon
multiline_comment|/* S514 PCI adapter slot number */
DECL|member|auto_pci_cfg
r_char
id|auto_pci_cfg
suffix:semicolon
multiline_comment|/* S515 PCI automatic slot detection */
DECL|member|comm_port
r_char
id|comm_port
suffix:semicolon
multiline_comment|/* Communication Port (PRI=0, SEC=1) */
DECL|member|bps
r_int
id|bps
suffix:semicolon
multiline_comment|/* data transfer rate */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* maximum transmit unit size */
DECL|member|udp_port
r_int
id|udp_port
suffix:semicolon
multiline_comment|/* UDP port for management */
DECL|member|ttl
r_int
r_char
id|ttl
suffix:semicolon
multiline_comment|/* Time To Live for UDP security */
DECL|member|ft1
r_int
r_char
id|ft1
suffix:semicolon
multiline_comment|/* FT1 Configurator Option */
DECL|member|interface
r_char
id|interface
suffix:semicolon
multiline_comment|/* RS-232/V.35, etc. */
DECL|member|clocking
r_char
id|clocking
suffix:semicolon
multiline_comment|/* external/internal */
DECL|member|line_coding
r_char
id|line_coding
suffix:semicolon
multiline_comment|/* NRZ/NRZI/FM0/FM1, etc. */
DECL|member|station
r_char
id|station
suffix:semicolon
multiline_comment|/* DTE/DCE, primary/secondary, etc. */
DECL|member|connection
r_char
id|connection
suffix:semicolon
multiline_comment|/* permanent/switched/on-demand */
DECL|member|read_mode
r_char
id|read_mode
suffix:semicolon
multiline_comment|/* read mode: Polling or interrupt */
DECL|member|receive_only
r_char
id|receive_only
suffix:semicolon
multiline_comment|/* disable tx buffers */
DECL|member|tty
r_char
id|tty
suffix:semicolon
multiline_comment|/* Create a fake tty device */
DECL|member|tty_major
r_int
id|tty_major
suffix:semicolon
multiline_comment|/* Major number for wanpipe tty device */
DECL|member|tty_minor
r_int
id|tty_minor
suffix:semicolon
multiline_comment|/* Minor number for wanpipe tty device */
DECL|member|tty_mode
r_int
id|tty_mode
suffix:semicolon
multiline_comment|/* TTY operation mode SYNC or ASYNC */
DECL|member|backup
r_char
id|backup
suffix:semicolon
multiline_comment|/* Backup Mode */
DECL|member|hw_opt
r_int
id|hw_opt
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* other hardware options */
DECL|member|reserved
r_int
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/****** arbitrary data ***************/
DECL|member|data_size
r_int
id|data_size
suffix:semicolon
multiline_comment|/* data buffer size */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* data buffer, e.g. firmware */
r_union
multiline_comment|/****** protocol-specific ************/
(brace
DECL|member|x25
id|wan_x25_conf_t
id|x25
suffix:semicolon
multiline_comment|/* X.25 configuration */
DECL|member|ppp
id|wan_ppp_conf_t
id|ppp
suffix:semicolon
multiline_comment|/* PPP configuration */
DECL|member|fr
id|wan_fr_conf_t
id|fr
suffix:semicolon
multiline_comment|/* frame relay configuration */
DECL|member|chdlc
id|wan_chdlc_conf_t
id|chdlc
suffix:semicolon
multiline_comment|/* Cisco HDLC configuration */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|wandev_conf_t
)brace
id|wandev_conf_t
suffix:semicolon
multiline_comment|/* &squot;config_id&squot; definitions */
DECL|macro|WANCONFIG_X25
mdefine_line|#define&t;WANCONFIG_X25&t;101&t;/* X.25 link */
DECL|macro|WANCONFIG_FR
mdefine_line|#define&t;WANCONFIG_FR&t;102&t;/* frame relay link */
DECL|macro|WANCONFIG_PPP
mdefine_line|#define&t;WANCONFIG_PPP&t;103&t;/* synchronous PPP link */
DECL|macro|WANCONFIG_CHDLC
mdefine_line|#define WANCONFIG_CHDLC&t;104&t;/* Cisco HDLC Link */
DECL|macro|WANCONFIG_BSC
mdefine_line|#define WANCONFIG_BSC&t;105&t;/* BiSync Streaming */
DECL|macro|WANCONFIG_HDLC
mdefine_line|#define WANCONFIG_HDLC&t;106&t;/* HDLC Support */
DECL|macro|WANCONFIG_MPPP
mdefine_line|#define WANCONFIG_MPPP  107&t;/* Multi Port PPP over RAW CHDLC */
multiline_comment|/*&n; * Configuration options defines.&n; */
multiline_comment|/* general options */
DECL|macro|WANOPT_OFF
mdefine_line|#define&t;WANOPT_OFF&t;0
DECL|macro|WANOPT_ON
mdefine_line|#define&t;WANOPT_ON&t;1
DECL|macro|WANOPT_NO
mdefine_line|#define&t;WANOPT_NO&t;0
DECL|macro|WANOPT_YES
mdefine_line|#define&t;WANOPT_YES&t;1
multiline_comment|/* intercace options */
DECL|macro|WANOPT_RS232
mdefine_line|#define&t;WANOPT_RS232&t;0
DECL|macro|WANOPT_V35
mdefine_line|#define&t;WANOPT_V35&t;1
multiline_comment|/* data encoding options */
DECL|macro|WANOPT_NRZ
mdefine_line|#define&t;WANOPT_NRZ&t;0
DECL|macro|WANOPT_NRZI
mdefine_line|#define&t;WANOPT_NRZI&t;1
DECL|macro|WANOPT_FM0
mdefine_line|#define&t;WANOPT_FM0&t;2
DECL|macro|WANOPT_FM1
mdefine_line|#define&t;WANOPT_FM1&t;3
multiline_comment|/* link type options */
DECL|macro|WANOPT_POINTTOPOINT
mdefine_line|#define&t;WANOPT_POINTTOPOINT&t;0&t;/* RTS always active */
DECL|macro|WANOPT_MULTIDROP
mdefine_line|#define&t;WANOPT_MULTIDROP&t;1&t;/* RTS is active when transmitting */
multiline_comment|/* clocking options */
DECL|macro|WANOPT_EXTERNAL
mdefine_line|#define&t;WANOPT_EXTERNAL&t;0
DECL|macro|WANOPT_INTERNAL
mdefine_line|#define&t;WANOPT_INTERNAL&t;1
multiline_comment|/* station options */
DECL|macro|WANOPT_DTE
mdefine_line|#define&t;WANOPT_DTE&t;&t;0
DECL|macro|WANOPT_DCE
mdefine_line|#define&t;WANOPT_DCE&t;&t;1
DECL|macro|WANOPT_CPE
mdefine_line|#define&t;WANOPT_CPE&t;&t;0
DECL|macro|WANOPT_NODE
mdefine_line|#define&t;WANOPT_NODE&t;&t;1
DECL|macro|WANOPT_SECONDARY
mdefine_line|#define&t;WANOPT_SECONDARY&t;0
DECL|macro|WANOPT_PRIMARY
mdefine_line|#define&t;WANOPT_PRIMARY&t;&t;1
multiline_comment|/* connection options */
DECL|macro|WANOPT_PERMANENT
mdefine_line|#define&t;WANOPT_PERMANENT&t;0&t;/* DTR always active */
DECL|macro|WANOPT_SWITCHED
mdefine_line|#define&t;WANOPT_SWITCHED&t;&t;1&t;/* use DTR to setup link (dial-up) */
DECL|macro|WANOPT_ONDEMAND
mdefine_line|#define&t;WANOPT_ONDEMAND&t;&t;2&t;/* activate DTR only before sending */
multiline_comment|/* frame relay in-channel signalling */
DECL|macro|WANOPT_FR_ANSI
mdefine_line|#define&t;WANOPT_FR_ANSI&t;&t;1&t;/* ANSI T1.617 Annex D */
DECL|macro|WANOPT_FR_Q933
mdefine_line|#define&t;WANOPT_FR_Q933&t;&t;2&t;/* ITU Q.933A */
DECL|macro|WANOPT_FR_LMI
mdefine_line|#define&t;WANOPT_FR_LMI&t;&t;3&t;/* LMI */
multiline_comment|/* PPP IP Mode Options */
DECL|macro|WANOPT_PPP_STATIC
mdefine_line|#define&t;WANOPT_PPP_STATIC&t;0
DECL|macro|WANOPT_PPP_HOST
mdefine_line|#define&t;WANOPT_PPP_HOST&t;&t;1
DECL|macro|WANOPT_PPP_PEER
mdefine_line|#define&t;WANOPT_PPP_PEER&t;&t;2
multiline_comment|/* ASY Mode Options */
DECL|macro|WANOPT_ONE
mdefine_line|#define WANOPT_ONE &t;&t;1
DECL|macro|WANOPT_TWO
mdefine_line|#define WANOPT_TWO&t;&t;2
DECL|macro|WANOPT_ONE_AND_HALF
mdefine_line|#define WANOPT_ONE_AND_HALF&t;3
DECL|macro|WANOPT_NONE
mdefine_line|#define WANOPT_NONE&t;0
DECL|macro|WANOPT_ODD
mdefine_line|#define WANOPT_ODD      1
DECL|macro|WANOPT_EVEN
mdefine_line|#define WANOPT_EVEN&t;2
multiline_comment|/* CHDLC Protocol Options */
multiline_comment|/* DF Commmented out for now.&n;&n;#define WANOPT_CHDLC_NO_DCD&t;&t;IGNORE_DCD_FOR_LINK_STAT&n;#define WANOPT_CHDLC_NO_CTS&t;&t;IGNORE_CTS_FOR_LINK_STAT&n;#define WANOPT_CHDLC_NO_KEEPALIVE&t;IGNORE_KPALV_FOR_LINK_STAT&n;*/
multiline_comment|/* Port options */
DECL|macro|WANOPT_PRI
mdefine_line|#define WANOPT_PRI 0
DECL|macro|WANOPT_SEC
mdefine_line|#define WANOPT_SEC 1
multiline_comment|/* read mode */
DECL|macro|WANOPT_INTR
mdefine_line|#define&t;WANOPT_INTR&t;0
DECL|macro|WANOPT_POLL
mdefine_line|#define WANOPT_POLL&t;1
DECL|macro|WANOPT_TTY_SYNC
mdefine_line|#define WANOPT_TTY_SYNC  0
DECL|macro|WANOPT_TTY_ASYNC
mdefine_line|#define WANOPT_TTY_ASYNC 1
multiline_comment|/*----------------------------------------------------------------------------&n; * WAN Link Status Info (for ROUTER_STAT IOCTL).&n; */
DECL|struct|wandev_stat
r_typedef
r_struct
id|wandev_stat
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* link state */
DECL|member|ndev
r_int
id|ndev
suffix:semicolon
multiline_comment|/* number of configured interfaces */
multiline_comment|/* link/interface configuration */
DECL|member|connection
r_int
id|connection
suffix:semicolon
multiline_comment|/* permanent/switched/on-demand */
DECL|member|media_type
r_int
id|media_type
suffix:semicolon
multiline_comment|/* Frame relay/PPP/X.25/SDLC, etc. */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* max. transmit unit for this device */
multiline_comment|/* physical level statistics */
DECL|member|modem_status
r_int
id|modem_status
suffix:semicolon
multiline_comment|/* modem status */
DECL|member|rx_frames
r_int
id|rx_frames
suffix:semicolon
multiline_comment|/* received frames count */
DECL|member|rx_overruns
r_int
id|rx_overruns
suffix:semicolon
multiline_comment|/* receiver overrun error count */
DECL|member|rx_crc_err
r_int
id|rx_crc_err
suffix:semicolon
multiline_comment|/* receive CRC error count */
DECL|member|rx_aborts
r_int
id|rx_aborts
suffix:semicolon
multiline_comment|/* received aborted frames count */
DECL|member|rx_bad_length
r_int
id|rx_bad_length
suffix:semicolon
multiline_comment|/* unexpetedly long/short frames count */
DECL|member|rx_dropped
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* frames discarded at device level */
DECL|member|tx_frames
r_int
id|tx_frames
suffix:semicolon
multiline_comment|/* transmitted frames count */
DECL|member|tx_underruns
r_int
id|tx_underruns
suffix:semicolon
multiline_comment|/* aborted transmissions (underruns) count */
DECL|member|tx_timeouts
r_int
id|tx_timeouts
suffix:semicolon
multiline_comment|/* transmission timeouts */
DECL|member|tx_rejects
r_int
id|tx_rejects
suffix:semicolon
multiline_comment|/* other transmit errors */
multiline_comment|/* media level statistics */
DECL|member|rx_bad_format
r_int
id|rx_bad_format
suffix:semicolon
multiline_comment|/* frames with invalid format */
DECL|member|rx_bad_addr
r_int
id|rx_bad_addr
suffix:semicolon
multiline_comment|/* frames with invalid media address */
DECL|member|tx_retries
r_int
id|tx_retries
suffix:semicolon
multiline_comment|/* frames re-transmitted */
DECL|member|reserved
r_int
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|typedef|wandev_stat_t
)brace
id|wandev_stat_t
suffix:semicolon
multiline_comment|/* &squot;state&squot; defines */
DECL|enum|wan_states
r_enum
id|wan_states
(brace
DECL|enumerator|WAN_UNCONFIGURED
id|WAN_UNCONFIGURED
comma
multiline_comment|/* link/channel is not configured */
DECL|enumerator|WAN_DISCONNECTED
id|WAN_DISCONNECTED
comma
multiline_comment|/* link/channel is disconnected */
DECL|enumerator|WAN_CONNECTING
id|WAN_CONNECTING
comma
multiline_comment|/* connection is in progress */
DECL|enumerator|WAN_CONNECTED
id|WAN_CONNECTED
comma
multiline_comment|/* link/channel is operational */
DECL|enumerator|WAN_LIMIT
id|WAN_LIMIT
comma
multiline_comment|/* for verification only */
DECL|enumerator|WAN_DUALPORT
id|WAN_DUALPORT
comma
multiline_comment|/* for Dual Port cards */
DECL|enumerator|WAN_DISCONNECTING
id|WAN_DISCONNECTING
comma
DECL|enumerator|WAN_FT1_READY
id|WAN_FT1_READY
multiline_comment|/* FT1 Configurator Ready */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|WAN_LOCAL_IP
id|WAN_LOCAL_IP
comma
DECL|enumerator|WAN_POINTOPOINT_IP
id|WAN_POINTOPOINT_IP
comma
DECL|enumerator|WAN_NETMASK_IP
id|WAN_NETMASK_IP
comma
DECL|enumerator|WAN_BROADCAST_IP
id|WAN_BROADCAST_IP
)brace
suffix:semicolon
multiline_comment|/* &squot;modem_status&squot; masks */
DECL|macro|WAN_MODEM_CTS
mdefine_line|#define&t;WAN_MODEM_CTS&t;0x0001&t;/* CTS line active */
DECL|macro|WAN_MODEM_DCD
mdefine_line|#define&t;WAN_MODEM_DCD&t;0x0002&t;/* DCD line active */
DECL|macro|WAN_MODEM_DTR
mdefine_line|#define&t;WAN_MODEM_DTR&t;0x0010&t;/* DTR line active */
DECL|macro|WAN_MODEM_RTS
mdefine_line|#define&t;WAN_MODEM_RTS&t;0x0020&t;/* RTS line active */
multiline_comment|/*----------------------------------------------------------------------------&n; * WAN interface (logical channel) configuration (for ROUTER_IFNEW IOCTL).&n; */
DECL|struct|wanif_conf
r_typedef
r_struct
id|wanif_conf
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|config_id
r_int
id|config_id
suffix:semicolon
multiline_comment|/* configuration identifier */
DECL|member|name
r_char
id|name
(braket
id|WAN_IFNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* interface name, ASCIIZ */
DECL|member|addr
r_char
id|addr
(braket
id|WAN_ADDRESS_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* media address, ASCIIZ */
DECL|member|usedby
r_char
id|usedby
(braket
id|USED_BY_FIELD
)braket
suffix:semicolon
multiline_comment|/* used by API or WANPIPE */
DECL|member|idle_timeout
r_int
id|idle_timeout
suffix:semicolon
multiline_comment|/* sec, before disconnecting */
DECL|member|hold_timeout
r_int
id|hold_timeout
suffix:semicolon
multiline_comment|/* sec, before re-connecting */
DECL|member|cir
r_int
id|cir
suffix:semicolon
multiline_comment|/* Committed Information Rate fwd,bwd*/
DECL|member|bc
r_int
id|bc
suffix:semicolon
multiline_comment|/* Committed Burst Size fwd, bwd */
DECL|member|be
r_int
id|be
suffix:semicolon
multiline_comment|/* Excess Burst Size fwd, bwd */
DECL|member|enable_IPX
r_int
r_char
id|enable_IPX
suffix:semicolon
multiline_comment|/* Enable or Disable IPX */
DECL|member|inarp
r_int
r_char
id|inarp
suffix:semicolon
multiline_comment|/* Send Inverse ARP requests Y/N */
DECL|member|inarp_interval
r_int
id|inarp_interval
suffix:semicolon
multiline_comment|/* sec, between InARP requests */
DECL|member|network_number
r_int
r_int
id|network_number
suffix:semicolon
multiline_comment|/* Network Number for IPX */
DECL|member|mc
r_char
id|mc
suffix:semicolon
multiline_comment|/* Multicast on or off */
DECL|member|pap
r_char
id|pap
suffix:semicolon
multiline_comment|/* PAP enabled or disabled */
DECL|member|chap
r_char
id|chap
suffix:semicolon
multiline_comment|/* CHAP enabled or disabled */
DECL|member|userid
r_int
r_char
id|userid
(braket
l_int|511
)braket
suffix:semicolon
multiline_comment|/* List of User Id */
DECL|member|passwd
r_int
r_char
id|passwd
(braket
l_int|511
)braket
suffix:semicolon
multiline_comment|/* List of passwords */
DECL|member|sysname
r_int
r_char
id|sysname
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* Name of the system */
DECL|member|ignore_dcd
r_int
r_char
id|ignore_dcd
suffix:semicolon
multiline_comment|/* Protocol options: */
DECL|member|ignore_cts
r_int
r_char
id|ignore_cts
suffix:semicolon
multiline_comment|/*  Ignore these to determine */
DECL|member|ignore_keepalive
r_int
r_char
id|ignore_keepalive
suffix:semicolon
multiline_comment|/*  link status (Yes or No) */
DECL|member|hdlc_streaming
r_int
r_char
id|hdlc_streaming
suffix:semicolon
multiline_comment|/*  Hdlc streaming mode (Y/N) */
DECL|member|receive_only
r_int
r_char
id|receive_only
suffix:semicolon
multiline_comment|/*  no transmit buffering (Y/N) */
DECL|member|keepalive_tx_tmr
r_int
id|keepalive_tx_tmr
suffix:semicolon
multiline_comment|/* transmit keepalive timer */
DECL|member|keepalive_rx_tmr
r_int
id|keepalive_rx_tmr
suffix:semicolon
multiline_comment|/* receive  keepalive timer */
DECL|member|keepalive_err_margin
r_int
id|keepalive_err_margin
suffix:semicolon
multiline_comment|/* keepalive_error_tolerance */
DECL|member|slarp_timer
r_int
id|slarp_timer
suffix:semicolon
multiline_comment|/* SLARP request timer */
DECL|member|ttl
r_int
r_char
id|ttl
suffix:semicolon
multiline_comment|/* Time To Live for UDP security */
DECL|member|interface
r_char
id|interface
suffix:semicolon
multiline_comment|/* RS-232/V.35, etc. */
DECL|member|clocking
r_char
id|clocking
suffix:semicolon
multiline_comment|/* external/internal */
DECL|member|bps
r_int
id|bps
suffix:semicolon
multiline_comment|/* data transfer rate */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* maximum transmit unit size */
DECL|member|if_down
r_int
r_char
id|if_down
suffix:semicolon
multiline_comment|/* brind down interface when disconnected */
DECL|member|gateway
r_int
r_char
id|gateway
suffix:semicolon
multiline_comment|/* Is this interface a gateway */
DECL|member|true_if_encoding
r_int
r_char
id|true_if_encoding
suffix:semicolon
multiline_comment|/* Set the dev-&gt;type to true board protocol */
DECL|member|asy_data_trans
r_int
r_char
id|asy_data_trans
suffix:semicolon
multiline_comment|/* async API options */
DECL|member|rts_hs_for_receive
r_int
r_char
id|rts_hs_for_receive
suffix:semicolon
multiline_comment|/* async Protocol options */
DECL|member|xon_xoff_hs_for_receive
r_int
r_char
id|xon_xoff_hs_for_receive
suffix:semicolon
DECL|member|xon_xoff_hs_for_transmit
r_int
r_char
id|xon_xoff_hs_for_transmit
suffix:semicolon
DECL|member|dcd_hs_for_transmit
r_int
r_char
id|dcd_hs_for_transmit
suffix:semicolon
DECL|member|cts_hs_for_transmit
r_int
r_char
id|cts_hs_for_transmit
suffix:semicolon
DECL|member|async_mode
r_int
r_char
id|async_mode
suffix:semicolon
DECL|member|tx_bits_per_char
r_int
id|tx_bits_per_char
suffix:semicolon
DECL|member|rx_bits_per_char
r_int
id|rx_bits_per_char
suffix:semicolon
DECL|member|stop_bits
r_int
id|stop_bits
suffix:semicolon
DECL|member|parity
r_int
r_char
id|parity
suffix:semicolon
DECL|member|break_timer
r_int
id|break_timer
suffix:semicolon
DECL|member|inter_char_timer
r_int
id|inter_char_timer
suffix:semicolon
DECL|member|rx_complete_length
r_int
id|rx_complete_length
suffix:semicolon
DECL|member|xon_char
r_int
id|xon_char
suffix:semicolon
DECL|member|xoff_char
r_int
id|xoff_char
suffix:semicolon
DECL|typedef|wanif_conf_t
)brace
id|wanif_conf_t
suffix:semicolon
macro_line|#ifdef&t;__KERNEL__
multiline_comment|/****** Kernel Interface ****************************************************/
macro_line|#include &lt;linux/fs.h&gt;&t;&t;/* support for device drivers */
macro_line|#include &lt;linux/proc_fs.h&gt;&t;/* proc filesystem pragmatics */
macro_line|#include &lt;linux/inet.h&gt;&t;&t;/* in_aton(), in_ntoa() prototypes */
macro_line|#include &lt;linux/netdevice.h&gt;&t;/* support for network drivers */
multiline_comment|/*----------------------------------------------------------------------------&n; * WAN device data space.&n; */
DECL|struct|wan_device
r_typedef
r_struct
id|wan_device
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* -&gt; WAN device name (ASCIIZ) */
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* -&gt; driver private data */
DECL|member|config_id
r_int
id|config_id
suffix:semicolon
multiline_comment|/* Configuration ID */
multiline_comment|/****** hardware configuration ******/
DECL|member|ioport
r_int
id|ioport
suffix:semicolon
multiline_comment|/* adapter I/O port base #1 */
DECL|member|S514_cpu_no
r_char
id|S514_cpu_no
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* PCI CPU Number */
DECL|member|S514_slot_no
r_int
r_char
id|S514_slot_no
suffix:semicolon
multiline_comment|/* PCI Slot Number */
DECL|member|maddr
r_int
r_int
id|maddr
suffix:semicolon
multiline_comment|/* dual-port memory address */
DECL|member|msize
r_int
id|msize
suffix:semicolon
multiline_comment|/* dual-port memory size */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt request level */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* DMA request level */
DECL|member|bps
r_int
id|bps
suffix:semicolon
multiline_comment|/* data transfer rate */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* max physical transmit unit size */
DECL|member|udp_port
r_int
id|udp_port
suffix:semicolon
multiline_comment|/* UDP port for management */
DECL|member|ttl
r_int
r_char
id|ttl
suffix:semicolon
multiline_comment|/* Time To Live for UDP security */
DECL|member|enable_tx_int
r_int
id|enable_tx_int
suffix:semicolon
multiline_comment|/* Transmit Interrupt enabled or not */
DECL|member|interface
r_char
id|interface
suffix:semicolon
multiline_comment|/* RS-232/V.35, etc. */
DECL|member|clocking
r_char
id|clocking
suffix:semicolon
multiline_comment|/* external/internal */
DECL|member|line_coding
r_char
id|line_coding
suffix:semicolon
multiline_comment|/* NRZ/NRZI/FM0/FM1, etc. */
DECL|member|station
r_char
id|station
suffix:semicolon
multiline_comment|/* DTE/DCE, primary/secondary, etc. */
DECL|member|connection
r_char
id|connection
suffix:semicolon
multiline_comment|/* permanent/switched/on-demand */
DECL|member|signalling
r_char
id|signalling
suffix:semicolon
multiline_comment|/* Signalling RS232 or V35 */
DECL|member|read_mode
r_char
id|read_mode
suffix:semicolon
multiline_comment|/* read mode: Polling or interrupt */
DECL|member|new_if_cnt
r_char
id|new_if_cnt
suffix:semicolon
multiline_comment|/* Number of interfaces per wanpipe */
DECL|member|del_if_cnt
r_char
id|del_if_cnt
suffix:semicolon
multiline_comment|/* Number of times del_if() gets called */
DECL|member|piggyback
r_int
r_char
id|piggyback
suffix:semicolon
multiline_comment|/* Piggibacking a port */
DECL|member|hw_opt
r_int
id|hw_opt
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* other hardware options */
multiline_comment|/****** status and statistics *******/
DECL|member|state
r_char
id|state
suffix:semicolon
multiline_comment|/* device state */
DECL|member|api_status
r_char
id|api_status
suffix:semicolon
multiline_comment|/* device api status */
macro_line|#if defined(LINUX_2_1) || defined(LINUX_2_4)
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* interface statistics */
macro_line|#else
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
multiline_comment|/* interface statistics */
macro_line|#endif
DECL|member|reserved
r_int
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|member|critical
r_int
r_int
id|critical
suffix:semicolon
multiline_comment|/* critical section flag */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Support for SMP Locking */
multiline_comment|/****** device management methods ***/
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_struct
id|wan_device
op_star
id|wandev
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
DECL|member|shutdown
r_int
(paren
op_star
id|shutdown
)paren
(paren
r_struct
id|wan_device
op_star
id|wandev
)paren
suffix:semicolon
DECL|member|update
r_int
(paren
op_star
id|update
)paren
(paren
r_struct
id|wan_device
op_star
id|wandev
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|wan_device
op_star
id|wandev
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|new_if
r_int
(paren
op_star
id|new_if
)paren
(paren
r_struct
id|wan_device
op_star
id|wandev
comma
id|netdevice_t
op_star
id|dev
comma
id|wanif_conf_t
op_star
id|conf
)paren
suffix:semicolon
DECL|member|del_if
r_int
(paren
op_star
id|del_if
)paren
(paren
r_struct
id|wan_device
op_star
id|wandev
comma
id|netdevice_t
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/****** maintained by the router ****/
DECL|member|next
r_struct
id|wan_device
op_star
id|next
suffix:semicolon
multiline_comment|/* -&gt; next device */
DECL|member|dev
id|netdevice_t
op_star
id|dev
suffix:semicolon
multiline_comment|/* list of network interfaces */
DECL|member|ndev
r_int
id|ndev
suffix:semicolon
multiline_comment|/* number of interfaces */
macro_line|#ifdef LINUX_2_4
DECL|member|dent
r_struct
id|proc_dir_entry
op_star
id|dent
suffix:semicolon
multiline_comment|/* proc filesystem entry */
macro_line|#else
DECL|member|dent
r_struct
id|proc_dir_entry
id|dent
suffix:semicolon
multiline_comment|/* proc filesystem entry */
macro_line|#endif
DECL|typedef|wan_device_t
)brace
id|wan_device_t
suffix:semicolon
multiline_comment|/* Public functions available for device drivers */
r_extern
r_int
id|register_wan_device
c_func
(paren
id|wan_device_t
op_star
id|wandev
)paren
suffix:semicolon
r_extern
r_int
id|unregister_wan_device
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
r_int
id|wanrouter_type_trans
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|netdevice_t
op_star
id|dev
)paren
suffix:semicolon
r_int
id|wanrouter_encapsulate
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|netdevice_t
op_star
id|dev
comma
r_int
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* Proc interface functions. These must not be called by the drivers! */
r_extern
r_int
id|wanrouter_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wanrouter_proc_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|wanrouter_proc_add
c_func
(paren
id|wan_device_t
op_star
id|wandev
)paren
suffix:semicolon
r_extern
r_int
id|wanrouter_proc_delete
c_func
(paren
id|wan_device_t
op_star
id|wandev
)paren
suffix:semicolon
r_extern
r_int
id|wanrouter_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|lock_adapter_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_int
r_int
op_star
id|smp_flags
)paren
suffix:semicolon
r_extern
r_void
id|unlock_adapter_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_int
r_int
op_star
id|smp_flags
)paren
suffix:semicolon
multiline_comment|/* Public Data */
r_extern
id|wan_device_t
op_star
id|router_devlist
suffix:semicolon
multiline_comment|/* list of registered devices */
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _ROUTER_H */
eof
