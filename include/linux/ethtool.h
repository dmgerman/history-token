multiline_comment|/*&n; * ethtool.h: Defines for Linux ethtool.&n; *&n; * Copyright (C) 1998 David S. Miller (davem@redhat.com)&n; * Copyright 2001 Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;&n; * Portions Copyright 2001 Sun Microsystems (thockin@sun.com)&n; */
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
DECL|macro|ETHTOOL_BUSINFO_LEN
mdefine_line|#define ETHTOOL_BUSINFO_LEN&t;32
multiline_comment|/* these strings are set to whatever the driver author decides... */
DECL|struct|ethtool_drvinfo
r_struct
id|ethtool_drvinfo
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|driver
r_char
id|driver
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* driver short name, &quot;tulip&quot;, &quot;eepro100&quot; */
DECL|member|version
r_char
id|version
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* driver version string */
DECL|member|fw_version
r_char
id|fw_version
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* firmware version string, if applicable */
DECL|member|bus_info
r_char
id|bus_info
(braket
id|ETHTOOL_BUSINFO_LEN
)braket
suffix:semicolon
multiline_comment|/* Bus info for this IF. */
multiline_comment|/* For PCI devices, use pci_dev-&gt;slot_name. */
DECL|member|reserved1
r_char
id|reserved1
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|reserved2
r_char
id|reserved2
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|eedump_len
id|u32
id|eedump_len
suffix:semicolon
multiline_comment|/* Size of data from ETHTOOL_GEEPROM (bytes) */
DECL|member|regdump_len
id|u32
id|regdump_len
suffix:semicolon
multiline_comment|/* Size of data from ETHTOOL_GREGS (bytes) */
)brace
suffix:semicolon
DECL|macro|SOPASS_MAX
mdefine_line|#define SOPASS_MAX&t;6
multiline_comment|/* wake-on-lan settings */
DECL|struct|ethtool_wolinfo
r_struct
id|ethtool_wolinfo
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|supported
id|u32
id|supported
suffix:semicolon
DECL|member|wolopts
id|u32
id|wolopts
suffix:semicolon
DECL|member|sopass
id|u8
id|sopass
(braket
id|SOPASS_MAX
)braket
suffix:semicolon
multiline_comment|/* SecureOn(tm) password */
)brace
suffix:semicolon
multiline_comment|/* for passing single values */
DECL|struct|ethtool_value
r_struct
id|ethtool_value
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|data
id|u32
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for passing big chunks of data */
DECL|struct|ethtool_regs
r_struct
id|ethtool_regs
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:semicolon
multiline_comment|/* driver-specific, indicates different chips/revs */
DECL|member|len
id|u32
id|len
suffix:semicolon
multiline_comment|/* bytes */
DECL|member|data
id|u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for passing EEPROM chunks */
DECL|struct|ethtool_eeprom
r_struct
id|ethtool_eeprom
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|len
id|u32
id|len
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|data
id|u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CMDs currently supported */
DECL|macro|ETHTOOL_GSET
mdefine_line|#define ETHTOOL_GSET&t;&t;0x00000001 /* Get settings. */
DECL|macro|ETHTOOL_SSET
mdefine_line|#define ETHTOOL_SSET&t;&t;0x00000002 /* Set settings, privileged. */
DECL|macro|ETHTOOL_GDRVINFO
mdefine_line|#define ETHTOOL_GDRVINFO&t;0x00000003 /* Get driver info. */
DECL|macro|ETHTOOL_GREGS
mdefine_line|#define ETHTOOL_GREGS&t;&t;0x00000004 /* Get NIC registers, privileged. */
DECL|macro|ETHTOOL_GWOL
mdefine_line|#define ETHTOOL_GWOL&t;&t;0x00000005 /* Get wake-on-lan options. */
DECL|macro|ETHTOOL_SWOL
mdefine_line|#define ETHTOOL_SWOL&t;&t;0x00000006 /* Set wake-on-lan options, priv. */
DECL|macro|ETHTOOL_GMSGLVL
mdefine_line|#define ETHTOOL_GMSGLVL&t;&t;0x00000007 /* Get driver message level */
DECL|macro|ETHTOOL_SMSGLVL
mdefine_line|#define ETHTOOL_SMSGLVL&t;&t;0x00000008 /* Set driver msg level, priv. */
DECL|macro|ETHTOOL_NWAY_RST
mdefine_line|#define ETHTOOL_NWAY_RST&t;0x00000009 /* Restart autonegotiation, priv. */
DECL|macro|ETHTOOL_GLINK
mdefine_line|#define ETHTOOL_GLINK&t;&t;0x0000000a /* Get link status */
DECL|macro|ETHTOOL_GEEPROM
mdefine_line|#define ETHTOOL_GEEPROM&t;&t;0x0000000b /* Get EEPROM data */
DECL|macro|ETHTOOL_SEEPROM
mdefine_line|#define ETHTOOL_SEEPROM&t;&t;0x0000000c /* Set EEPROM data */
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
DECL|macro|SUPPORTED_BNC
mdefine_line|#define SUPPORTED_BNC&t;&t;&t;(1 &lt;&lt; 11)
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
DECL|macro|ADVERTISED_BNC
mdefine_line|#define ADVERTISED_BNC&t;&t;&t;(1 &lt;&lt; 11)
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
multiline_comment|/* Wake-On-Lan options. */
DECL|macro|WAKE_PHY
mdefine_line|#define WAKE_PHY&t;&t;(1 &lt;&lt; 0)
DECL|macro|WAKE_UCAST
mdefine_line|#define WAKE_UCAST&t;&t;(1 &lt;&lt; 1)
DECL|macro|WAKE_MCAST
mdefine_line|#define WAKE_MCAST&t;&t;(1 &lt;&lt; 2)
DECL|macro|WAKE_BCAST
mdefine_line|#define WAKE_BCAST&t;&t;(1 &lt;&lt; 3)
DECL|macro|WAKE_ARP
mdefine_line|#define WAKE_ARP&t;&t;(1 &lt;&lt; 4)
DECL|macro|WAKE_MAGIC
mdefine_line|#define WAKE_MAGIC&t;&t;(1 &lt;&lt; 5)
DECL|macro|WAKE_MAGICSECURE
mdefine_line|#define WAKE_MAGICSECURE&t;(1 &lt;&lt; 6) /* only meaningful if WAKE_MAGIC */
macro_line|#endif /* _LINUX_ETHTOOL_H */
eof
