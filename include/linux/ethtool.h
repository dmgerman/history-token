multiline_comment|/* $Id: ethtool.h,v 1.2 2000/11/12 10:05:57 davem Exp $&n; * ethtool.h: Defines for Linux ethtool.&n; *&n; * Copyright (C) 1998 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _LINUX_ETHTOOL_H
DECL|macro|_LINUX_ETHTOOL_H
mdefine_line|#define _LINUX_ETHTOOL_H
multiline_comment|/* This should work for both 32 and 64 bit userland. */
DECL|struct|ethtool_cmd
r_struct
id|ethtool_cmd
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|supported
id|u32
id|supported
suffix:semicolon
multiline_comment|/* Features this interface supports */
DECL|member|advertising
id|u32
id|advertising
suffix:semicolon
multiline_comment|/* Features this interface advertises */
DECL|member|speed
id|u16
id|speed
suffix:semicolon
multiline_comment|/* The forced speed, 10Mb, 100Mb, gigabit */
DECL|member|duplex
id|u8
id|duplex
suffix:semicolon
multiline_comment|/* Duplex, half or full */
DECL|member|port
id|u8
id|port
suffix:semicolon
multiline_comment|/* Which connector port */
DECL|member|phy_address
id|u8
id|phy_address
suffix:semicolon
DECL|member|transceiver
id|u8
id|transceiver
suffix:semicolon
multiline_comment|/* Which tranceiver to use */
DECL|member|autoneg
id|u8
id|autoneg
suffix:semicolon
multiline_comment|/* Enable or disable autonegotiation */
DECL|member|maxtxpkt
id|u32
id|maxtxpkt
suffix:semicolon
multiline_comment|/* Tx pkts before generating tx int */
DECL|member|maxrxpkt
id|u32
id|maxrxpkt
suffix:semicolon
multiline_comment|/* Rx pkts before generating rx int */
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CMDs currently supported */
DECL|macro|ETHTOOL_GSET
mdefine_line|#define ETHTOOL_GSET&t;&t;0x00000001 /* Get settings, non-privileged. */
DECL|macro|ETHTOOL_SSET
mdefine_line|#define ETHTOOL_SSET&t;&t;0x00000002 /* Set settings, privileged. */
multiline_comment|/* compatibility with older code */
DECL|macro|SPARC_ETH_GSET
mdefine_line|#define SPARC_ETH_GSET&t;&t;ETHTOOL_GSET
DECL|macro|SPARC_ETH_SSET
mdefine_line|#define SPARC_ETH_SSET&t;&t;ETHTOOL_SSET
multiline_comment|/* Indicates what features are supported by the interface. */
DECL|macro|SUPPORTED_10baseT_Half
mdefine_line|#define SUPPORTED_10baseT_Half&t;&t;(1 &lt;&lt; 0)
DECL|macro|SUPPORTED_10baseT_Full
mdefine_line|#define SUPPORTED_10baseT_Full&t;&t;(1 &lt;&lt; 1)
DECL|macro|SUPPORTED_100baseT_Half
mdefine_line|#define SUPPORTED_100baseT_Half&t;&t;(1 &lt;&lt; 2)
DECL|macro|SUPPORTED_100baseT_Full
mdefine_line|#define SUPPORTED_100baseT_Full&t;&t;(1 &lt;&lt; 3)
DECL|macro|SUPPORTED_1000baseT_Half
mdefine_line|#define SUPPORTED_1000baseT_Half&t;(1 &lt;&lt; 4)
DECL|macro|SUPPORTED_1000baseT_Full
mdefine_line|#define SUPPORTED_1000baseT_Full&t;(1 &lt;&lt; 5)
DECL|macro|SUPPORTED_Autoneg
mdefine_line|#define SUPPORTED_Autoneg&t;&t;(1 &lt;&lt; 6)
DECL|macro|SUPPORTED_TP
mdefine_line|#define SUPPORTED_TP&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|SUPPORTED_AUI
mdefine_line|#define SUPPORTED_AUI&t;&t;&t;(1 &lt;&lt; 8)
DECL|macro|SUPPORTED_MII
mdefine_line|#define SUPPORTED_MII&t;&t;&t;(1 &lt;&lt; 9)
DECL|macro|SUPPORTED_FIBRE
mdefine_line|#define SUPPORTED_FIBRE&t;&t;&t;(1 &lt;&lt; 10)
multiline_comment|/* Indicates what features are advertised by the interface. */
DECL|macro|ADVERTISED_10baseT_Half
mdefine_line|#define ADVERTISED_10baseT_Half&t;&t;(1 &lt;&lt; 0)
DECL|macro|ADVERTISED_10baseT_Full
mdefine_line|#define ADVERTISED_10baseT_Full&t;&t;(1 &lt;&lt; 1)
DECL|macro|ADVERTISED_100baseT_Half
mdefine_line|#define ADVERTISED_100baseT_Half&t;(1 &lt;&lt; 2)
DECL|macro|ADVERTISED_100baseT_Full
mdefine_line|#define ADVERTISED_100baseT_Full&t;(1 &lt;&lt; 3)
DECL|macro|ADVERTISED_1000baseT_Half
mdefine_line|#define ADVERTISED_1000baseT_Half&t;(1 &lt;&lt; 4)
DECL|macro|ADVERTISED_1000baseT_Full
mdefine_line|#define ADVERTISED_1000baseT_Full&t;(1 &lt;&lt; 5)
DECL|macro|ADVERTISED_Autoneg
mdefine_line|#define ADVERTISED_Autoneg&t;&t;(1 &lt;&lt; 6)
DECL|macro|ADVERTISED_TP
mdefine_line|#define ADVERTISED_TP&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|ADVERTISED_AUI
mdefine_line|#define ADVERTISED_AUI&t;&t;&t;(1 &lt;&lt; 8)
DECL|macro|ADVERTISED_MII
mdefine_line|#define ADVERTISED_MII&t;&t;&t;(1 &lt;&lt; 9)
DECL|macro|ADVERTISED_FIBRE
mdefine_line|#define ADVERTISED_FIBRE&t;&t;(1 &lt;&lt; 10)
multiline_comment|/* The following are all involved in forcing a particular link&n; * mode for the device for setting things.  When getting the&n; * devices settings, these indicate the current mode and whether&n; * it was foced up into this mode or autonegotiated.&n; */
multiline_comment|/* The forced speed, 10Mb, 100Mb, gigabit. */
DECL|macro|SPEED_10
mdefine_line|#define SPEED_10&t;&t;10
DECL|macro|SPEED_100
mdefine_line|#define SPEED_100&t;&t;100
DECL|macro|SPEED_1000
mdefine_line|#define SPEED_1000&t;&t;1000
multiline_comment|/* Duplex, half or full. */
DECL|macro|DUPLEX_HALF
mdefine_line|#define DUPLEX_HALF&t;&t;0x00
DECL|macro|DUPLEX_FULL
mdefine_line|#define DUPLEX_FULL&t;&t;0x01
multiline_comment|/* Which connector port. */
DECL|macro|PORT_TP
mdefine_line|#define PORT_TP&t;&t;&t;0x00
DECL|macro|PORT_AUI
mdefine_line|#define PORT_AUI&t;&t;0x01
DECL|macro|PORT_MII
mdefine_line|#define PORT_MII&t;&t;0x02
DECL|macro|PORT_FIBRE
mdefine_line|#define PORT_FIBRE&t;&t;0x03
DECL|macro|PORT_BNC
mdefine_line|#define PORT_BNC&t;&t;0x04
multiline_comment|/* Which tranceiver to use. */
DECL|macro|XCVR_INTERNAL
mdefine_line|#define XCVR_INTERNAL&t;&t;0x00
DECL|macro|XCVR_EXTERNAL
mdefine_line|#define XCVR_EXTERNAL&t;&t;0x01
DECL|macro|XCVR_DUMMY1
mdefine_line|#define XCVR_DUMMY1&t;&t;0x02
DECL|macro|XCVR_DUMMY2
mdefine_line|#define XCVR_DUMMY2&t;&t;0x03
DECL|macro|XCVR_DUMMY3
mdefine_line|#define XCVR_DUMMY3&t;&t;0x04
multiline_comment|/* Enable or disable autonegotiation.  If this is set to enable,&n; * the forced link modes above are completely ignored.&n; */
DECL|macro|AUTONEG_DISABLE
mdefine_line|#define AUTONEG_DISABLE&t;&t;0x00
DECL|macro|AUTONEG_ENABLE
mdefine_line|#define AUTONEG_ENABLE&t;&t;0x01
macro_line|#endif /* _LINUX_ETHTOOL_H */
eof
