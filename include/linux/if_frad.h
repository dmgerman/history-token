multiline_comment|/*&n; * DLCI/FRAD&t;Definitions for Frame Relay Access Devices.  DLCI devices are&n; *&t;&t;created for each DLCI associated with a FRAD.  The FRAD driver&n; *&t;&t;is not truly a network device, but the lower level device&n; *&t;&t;handler.  This allows other FRAD manufacturers to use the DLCI&n; *&t;&t;code, including its RFC1490 encapsulation alongside the current&n; *&t;&t;implementation for the Sangoma cards.&n; *&n; * Version:&t;@(#)if_ifrad.h&t;0.15&t;31 Mar 96&n; *&n; * Author:&t;Mike McLagan &lt;mike.mclagan@linux.org&gt;&n; *&n; * Changes:&n; *&t;&t;0.15&t;Mike McLagan&t;changed structure defs (packed)&n; *&t;&t;&t;&t;&t;re-arranged flags&n; *&t;&t;&t;&t;&t;added DLCI_RET vars&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _FRAD_H_
DECL|macro|_FRAD_H_
mdefine_line|#define _FRAD_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#if defined(CONFIG_DLCI) || defined(CONFIG_DLCI_MODULE)
multiline_comment|/* Structures and constants associated with the DLCI device driver */
DECL|struct|dlci_add
r_struct
id|dlci_add
(brace
DECL|member|devname
r_char
id|devname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|dlci
r_int
id|dlci
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DLCI_GET_CONF
mdefine_line|#define DLCI_GET_CONF&t;(SIOCDEVPRIVATE + 2)
DECL|macro|DLCI_SET_CONF
mdefine_line|#define DLCI_SET_CONF&t;(SIOCDEVPRIVATE + 3)
multiline_comment|/* &n; * These are related to the Sangoma SDLA and should remain in order. &n; * Code within the SDLA module is based on the specifics of this &n; * structure.  Change at your own peril.&n; */
DECL|struct|dlci_conf
r_struct
id|dlci_conf
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|CIR_fwd
r_int
id|CIR_fwd
suffix:semicolon
DECL|member|Bc_fwd
r_int
id|Bc_fwd
suffix:semicolon
DECL|member|Be_fwd
r_int
id|Be_fwd
suffix:semicolon
DECL|member|CIR_bwd
r_int
id|CIR_bwd
suffix:semicolon
DECL|member|Bc_bwd
r_int
id|Bc_bwd
suffix:semicolon
DECL|member|Be_bwd
r_int
id|Be_bwd
suffix:semicolon
multiline_comment|/* these are part of the status read */
DECL|member|Tc_fwd
r_int
id|Tc_fwd
suffix:semicolon
DECL|member|Tc_bwd
r_int
id|Tc_bwd
suffix:semicolon
DECL|member|Tf_max
r_int
id|Tf_max
suffix:semicolon
DECL|member|Tb_max
r_int
id|Tb_max
suffix:semicolon
multiline_comment|/* add any new fields here above is a mirror of sdla_dlci_conf */
)brace
suffix:semicolon
DECL|macro|DLCI_GET_SLAVE
mdefine_line|#define DLCI_GET_SLAVE&t;(SIOCDEVPRIVATE + 4)
multiline_comment|/* configuration flags for DLCI */
DECL|macro|DLCI_IGNORE_CIR_OUT
mdefine_line|#define DLCI_IGNORE_CIR_OUT&t;0x0001
DECL|macro|DLCI_ACCOUNT_CIR_IN
mdefine_line|#define DLCI_ACCOUNT_CIR_IN&t;0x0002
DECL|macro|DLCI_BUFFER_IF
mdefine_line|#define DLCI_BUFFER_IF&t;&t;0x0008
DECL|macro|DLCI_VALID_FLAGS
mdefine_line|#define DLCI_VALID_FLAGS&t;0x000B
multiline_comment|/* FRAD driver uses these to indicate what it did with packet */
DECL|macro|DLCI_RET_OK
mdefine_line|#define DLCI_RET_OK&t;&t;0x00
DECL|macro|DLCI_RET_ERR
mdefine_line|#define DLCI_RET_ERR&t;&t;0x01
DECL|macro|DLCI_RET_DROP
mdefine_line|#define DLCI_RET_DROP&t;&t;0x02
multiline_comment|/* defines for the actual Frame Relay hardware */
DECL|macro|FRAD_GET_CONF
mdefine_line|#define FRAD_GET_CONF&t;(SIOCDEVPRIVATE)
DECL|macro|FRAD_SET_CONF
mdefine_line|#define FRAD_SET_CONF&t;(SIOCDEVPRIVATE + 1)
DECL|macro|FRAD_LAST_IOCTL
mdefine_line|#define FRAD_LAST_IOCTL&t;FRAD_SET_CONF
multiline_comment|/*&n; * Based on the setup for the Sangoma SDLA.  If changes are &n; * necessary to this structure, a routine will need to be &n; * added to that module to copy fields.&n; */
DECL|struct|frad_conf
r_struct
id|frad_conf
(brace
DECL|member|station
r_int
id|station
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|kbaud
r_int
id|kbaud
suffix:semicolon
DECL|member|clocking
r_int
id|clocking
suffix:semicolon
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
DECL|member|T391
r_int
id|T391
suffix:semicolon
DECL|member|T392
r_int
id|T392
suffix:semicolon
DECL|member|N391
r_int
id|N391
suffix:semicolon
DECL|member|N392
r_int
id|N392
suffix:semicolon
DECL|member|N393
r_int
id|N393
suffix:semicolon
DECL|member|CIR_fwd
r_int
id|CIR_fwd
suffix:semicolon
DECL|member|Bc_fwd
r_int
id|Bc_fwd
suffix:semicolon
DECL|member|Be_fwd
r_int
id|Be_fwd
suffix:semicolon
DECL|member|CIR_bwd
r_int
id|CIR_bwd
suffix:semicolon
DECL|member|Bc_bwd
r_int
id|Bc_bwd
suffix:semicolon
DECL|member|Be_bwd
r_int
id|Be_bwd
suffix:semicolon
multiline_comment|/* Add new fields here, above is a mirror of the sdla_conf */
)brace
suffix:semicolon
DECL|macro|FRAD_STATION_CPE
mdefine_line|#define FRAD_STATION_CPE&t;0x0000
DECL|macro|FRAD_STATION_NODE
mdefine_line|#define FRAD_STATION_NODE&t;0x0001
DECL|macro|FRAD_TX_IGNORE_CIR
mdefine_line|#define FRAD_TX_IGNORE_CIR&t;0x0001
DECL|macro|FRAD_RX_ACCOUNT_CIR
mdefine_line|#define FRAD_RX_ACCOUNT_CIR&t;0x0002
DECL|macro|FRAD_DROP_ABORTED
mdefine_line|#define FRAD_DROP_ABORTED&t;0x0004
DECL|macro|FRAD_BUFFERIF
mdefine_line|#define FRAD_BUFFERIF&t;&t;0x0008
DECL|macro|FRAD_STATS
mdefine_line|#define FRAD_STATS&t;&t;0x0010
DECL|macro|FRAD_MCI
mdefine_line|#define FRAD_MCI&t;&t;0x0100
DECL|macro|FRAD_AUTODLCI
mdefine_line|#define FRAD_AUTODLCI&t;&t;0x8000
DECL|macro|FRAD_VALID_FLAGS
mdefine_line|#define FRAD_VALID_FLAGS&t;0x811F
DECL|macro|FRAD_CLOCK_INT
mdefine_line|#define FRAD_CLOCK_INT&t;&t;0x0001
DECL|macro|FRAD_CLOCK_EXT
mdefine_line|#define FRAD_CLOCK_EXT&t;&t;0x0000
macro_line|#ifdef __KERNEL__
multiline_comment|/* these are the fields of an RFC 1490 header */
DECL|struct|frhdr
r_struct
id|frhdr
(brace
DECL|member|control
r_int
r_char
id|control
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* for IP packets, this can be the NLPID */
DECL|member|pad
r_int
r_char
id|pad
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|NLPID
r_int
r_char
id|NLPID
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|OUI
r_int
r_char
id|OUI
(braket
l_int|3
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|PID
r_int
r_int
id|PID
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|IP_NLPID
mdefine_line|#define IP_NLPID pad 
)brace
suffix:semicolon
multiline_comment|/* see RFC 1490 for the definition of the following */
DECL|macro|FRAD_I_UI
mdefine_line|#define FRAD_I_UI&t;&t;0x03
DECL|macro|FRAD_P_PADDING
mdefine_line|#define FRAD_P_PADDING&t;&t;0x00
DECL|macro|FRAD_P_Q933
mdefine_line|#define FRAD_P_Q933&t;&t;0x08
DECL|macro|FRAD_P_SNAP
mdefine_line|#define FRAD_P_SNAP&t;&t;0x80
DECL|macro|FRAD_P_CLNP
mdefine_line|#define FRAD_P_CLNP&t;&t;0x81
DECL|macro|FRAD_P_IP
mdefine_line|#define FRAD_P_IP&t;&t;0xCC
DECL|struct|dlci_local
r_struct
id|dlci_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|slave
r_struct
id|net_device
op_star
id|slave
suffix:semicolon
DECL|member|config
r_struct
id|dlci_conf
id|config
suffix:semicolon
DECL|member|configured
r_int
id|configured
suffix:semicolon
multiline_comment|/* callback function */
DECL|member|receive
r_void
(paren
op_star
id|receive
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|frad_local
r_struct
id|frad_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* devices which this FRAD is slaved to */
DECL|member|master
r_struct
id|net_device
op_star
id|master
(braket
id|CONFIG_DLCI_MAX
)braket
suffix:semicolon
DECL|member|dlci
r_int
id|dlci
(braket
id|CONFIG_DLCI_MAX
)braket
suffix:semicolon
DECL|member|config
r_struct
id|frad_conf
id|config
suffix:semicolon
DECL|member|configured
r_int
id|configured
suffix:semicolon
multiline_comment|/* has this device been configured */
DECL|member|initialized
r_int
id|initialized
suffix:semicolon
multiline_comment|/* mem_start, port, irq set ? */
multiline_comment|/* callback functions */
DECL|member|activate
r_int
(paren
op_star
id|activate
)paren
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|deactivate
r_int
(paren
op_star
id|deactivate
)paren
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|assoc
r_int
(paren
op_star
id|assoc
)paren
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|deassoc
r_int
(paren
op_star
id|deassoc
)paren
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|dlci_conf
r_int
(paren
op_star
id|dlci_conf
)paren
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
id|get
)paren
suffix:semicolon
multiline_comment|/* fields that are used by the Sangoma SDLA cards */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* adapter type */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* state of the S502/8 control latch */
DECL|member|buffer
r_int
id|buffer
suffix:semicolon
multiline_comment|/* current buffer for S508 firmware */
)brace
suffix:semicolon
r_int
id|register_frad
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|unregister_frad
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
DECL|variable|dlci_ioctl_hook
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
macro_line|#endif __KERNEL__
macro_line|#endif /* CONFIG_DLCI || CONFIG_DLCI_MODULE */
macro_line|#endif
eof
