multiline_comment|/*&n; * linux/drivers/net/am79c961.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _LINUX_am79c961a_H
DECL|macro|_LINUX_am79c961a_H
mdefine_line|#define _LINUX_am79c961a_H
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug. debug flags: */
DECL|macro|DEBUG_TX
mdefine_line|#define DEBUG_TX&t; 2
DECL|macro|DEBUG_RX
mdefine_line|#define DEBUG_RX&t; 4
DECL|macro|DEBUG_INT
mdefine_line|#define DEBUG_INT&t; 8
DECL|macro|DEBUG_IC
mdefine_line|#define DEBUG_IC&t;16
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG &t;0
macro_line|#endif
DECL|macro|NET_UID
mdefine_line|#define NET_UID&t;&t;0
DECL|macro|NET_RDP
mdefine_line|#define NET_RDP&t;&t;0x10
DECL|macro|NET_RAP
mdefine_line|#define NET_RAP&t;&t;0x12
DECL|macro|NET_RESET
mdefine_line|#define NET_RESET&t;0x14
DECL|macro|NET_IDP
mdefine_line|#define NET_IDP&t;&t;0x16
multiline_comment|/*&n; * RAP registers&n; */
DECL|macro|CSR0
mdefine_line|#define CSR0&t;&t;0
DECL|macro|CSR0_INIT
mdefine_line|#define CSR0_INIT&t;0x0001
DECL|macro|CSR0_STRT
mdefine_line|#define CSR0_STRT&t;0x0002
DECL|macro|CSR0_STOP
mdefine_line|#define CSR0_STOP&t;0x0004
DECL|macro|CSR0_TDMD
mdefine_line|#define CSR0_TDMD&t;0x0008
DECL|macro|CSR0_TXON
mdefine_line|#define CSR0_TXON&t;0x0010
DECL|macro|CSR0_RXON
mdefine_line|#define CSR0_RXON&t;0x0020
DECL|macro|CSR0_IENA
mdefine_line|#define CSR0_IENA&t;0x0040
DECL|macro|CSR0_INTR
mdefine_line|#define CSR0_INTR&t;0x0080
DECL|macro|CSR0_IDON
mdefine_line|#define CSR0_IDON&t;0x0100
DECL|macro|CSR0_TINT
mdefine_line|#define CSR0_TINT&t;0x0200
DECL|macro|CSR0_RINT
mdefine_line|#define CSR0_RINT&t;0x0400
DECL|macro|CSR0_MERR
mdefine_line|#define CSR0_MERR&t;0x0800
DECL|macro|CSR0_MISS
mdefine_line|#define CSR0_MISS&t;0x1000
DECL|macro|CSR0_CERR
mdefine_line|#define CSR0_CERR&t;0x2000
DECL|macro|CSR0_BABL
mdefine_line|#define CSR0_BABL&t;0x4000
DECL|macro|CSR0_ERR
mdefine_line|#define CSR0_ERR&t;0x8000
DECL|macro|CSR3
mdefine_line|#define CSR3&t;&t;3
DECL|macro|CSR3_EMBA
mdefine_line|#define CSR3_EMBA&t;0x0008
DECL|macro|CSR3_DXMT2PD
mdefine_line|#define CSR3_DXMT2PD&t;0x0010
DECL|macro|CSR3_LAPPEN
mdefine_line|#define CSR3_LAPPEN&t;0x0020
DECL|macro|CSR3_DXSUFLO
mdefine_line|#define CSR3_DXSUFLO&t;0x0040
DECL|macro|CSR3_IDONM
mdefine_line|#define CSR3_IDONM&t;0x0100
DECL|macro|CSR3_TINTM
mdefine_line|#define CSR3_TINTM&t;0x0200
DECL|macro|CSR3_RINTM
mdefine_line|#define CSR3_RINTM&t;0x0400
DECL|macro|CSR3_MERRM
mdefine_line|#define CSR3_MERRM&t;0x0800
DECL|macro|CSR3_MISSM
mdefine_line|#define CSR3_MISSM&t;0x1000
DECL|macro|CSR3_BABLM
mdefine_line|#define CSR3_BABLM&t;0x4000
DECL|macro|CSR3_MASKALL
mdefine_line|#define CSR3_MASKALL&t;0x5F00
DECL|macro|CTRL1
mdefine_line|#define CTRL1&t;&t;5
DECL|macro|CTRL1_SPND
mdefine_line|#define CTRL1_SPND&t;0x0001
DECL|macro|LADRL
mdefine_line|#define LADRL&t;&t;8
DECL|macro|LADRM1
mdefine_line|#define LADRM1&t;&t;9
DECL|macro|LADRM2
mdefine_line|#define LADRM2&t;&t;10
DECL|macro|LADRH
mdefine_line|#define LADRH&t;&t;11
DECL|macro|PADRL
mdefine_line|#define PADRL&t;&t;12
DECL|macro|PADRM
mdefine_line|#define PADRM&t;&t;13
DECL|macro|PADRH
mdefine_line|#define PADRH&t;&t;14
DECL|macro|MODE
mdefine_line|#define MODE&t;&t;15
DECL|macro|MODE_DISRX
mdefine_line|#define MODE_DISRX&t;0x0001
DECL|macro|MODE_DISTX
mdefine_line|#define MODE_DISTX&t;0x0002
DECL|macro|MODE_LOOP
mdefine_line|#define MODE_LOOP&t;0x0004
DECL|macro|MODE_DTCRC
mdefine_line|#define MODE_DTCRC&t;0x0008
DECL|macro|MODE_COLL
mdefine_line|#define MODE_COLL&t;0x0010
DECL|macro|MODE_DRETRY
mdefine_line|#define MODE_DRETRY&t;0x0020
DECL|macro|MODE_INTLOOP
mdefine_line|#define MODE_INTLOOP&t;0x0040
DECL|macro|MODE_PORT_AUI
mdefine_line|#define MODE_PORT_AUI&t;0x0000
DECL|macro|MODE_PORT_10BT
mdefine_line|#define MODE_PORT_10BT&t;0x0080
DECL|macro|MODE_DRXPA
mdefine_line|#define MODE_DRXPA&t;0x2000
DECL|macro|MODE_DRXBA
mdefine_line|#define MODE_DRXBA&t;0x4000
DECL|macro|MODE_PROMISC
mdefine_line|#define MODE_PROMISC&t;0x8000
DECL|macro|BASERXL
mdefine_line|#define BASERXL&t;&t;24
DECL|macro|BASERXH
mdefine_line|#define BASERXH&t;&t;25
DECL|macro|BASETXL
mdefine_line|#define BASETXL&t;&t;30
DECL|macro|BASETXH
mdefine_line|#define BASETXH&t;&t;31
DECL|macro|POLLINT
mdefine_line|#define POLLINT&t;&t;47
DECL|macro|SIZERXR
mdefine_line|#define SIZERXR&t;&t;76
DECL|macro|SIZETXR
mdefine_line|#define SIZETXR&t;&t;78
DECL|macro|RMD_ENP
mdefine_line|#define RMD_ENP&t;&t;0x0100
DECL|macro|RMD_STP
mdefine_line|#define RMD_STP&t;&t;0x0200
DECL|macro|RMD_CRC
mdefine_line|#define RMD_CRC&t;&t;0x0800
DECL|macro|RMD_FRAM
mdefine_line|#define RMD_FRAM&t;0x2000
DECL|macro|RMD_ERR
mdefine_line|#define RMD_ERR&t;&t;0x4000
DECL|macro|RMD_OWN
mdefine_line|#define RMD_OWN&t;&t;0x8000
DECL|macro|TMD_ENP
mdefine_line|#define TMD_ENP&t;&t;0x0100
DECL|macro|TMD_STP
mdefine_line|#define TMD_STP&t;&t;0x0200
DECL|macro|TMD_MORE
mdefine_line|#define TMD_MORE&t;0x1000
DECL|macro|TMD_ERR
mdefine_line|#define TMD_ERR&t;&t;0x4000
DECL|macro|TMD_OWN
mdefine_line|#define TMD_OWN&t;&t;0x8000
DECL|macro|TST_RTRY
mdefine_line|#define TST_RTRY&t;0x0400
DECL|macro|TST_LCAR
mdefine_line|#define TST_LCAR&t;0x0800
DECL|macro|TST_LCOL
mdefine_line|#define TST_LCOL&t;0x1000
DECL|macro|TST_UFLO
mdefine_line|#define TST_UFLO&t;0x4000
DECL|macro|TST_BUFF
mdefine_line|#define TST_BUFF&t;0x8000
DECL|struct|dev_priv
r_struct
id|dev_priv
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|rxbuffer
r_int
r_int
id|rxbuffer
(braket
id|RX_BUFFERS
)braket
suffix:semicolon
DECL|member|txbuffer
r_int
r_int
id|txbuffer
(braket
id|TX_BUFFERS
)braket
suffix:semicolon
DECL|member|txhead
r_int
r_char
id|txhead
suffix:semicolon
DECL|member|txtail
r_int
r_char
id|txtail
suffix:semicolon
DECL|member|rxhead
r_int
r_char
id|rxhead
suffix:semicolon
DECL|member|rxtail
r_int
r_char
id|rxtail
suffix:semicolon
DECL|member|rxhdr
r_int
r_int
id|rxhdr
suffix:semicolon
DECL|member|txhdr
r_int
r_int
id|txhdr
suffix:semicolon
DECL|member|chip_lock
id|spinlock_t
id|chip_lock
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|am79c961_probe
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
eof
