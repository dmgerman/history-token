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
multiline_comment|/* for configuring coalescing parameters of chip */
DECL|struct|ethtool_coalesce
r_struct
id|ethtool_coalesce
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
multiline_comment|/* ETHTOOL_{G,S}COALESCE */
multiline_comment|/* How many usecs to delay an RX interrupt after&n;&t; * a packet arrives.  If 0, only rx_max_coalesced_frames&n;&t; * is used.&n;&t; */
DECL|member|rx_coalesce_usecs
id|u32
id|rx_coalesce_usecs
suffix:semicolon
multiline_comment|/* How many packets to delay an RX interrupt after&n;&t; * a packet arrives.  If 0, only rx_coalesce_usecs is&n;&t; * used.  It is illegal to set both usecs and max frames&n;&t; * to zero as this would cause RX interrupts to never be&n;&t; * generated.&n;&t; */
DECL|member|rx_max_coalesced_frames
id|u32
id|rx_max_coalesced_frames
suffix:semicolon
multiline_comment|/* Same as above two parameters, except that these values&n;&t; * apply while an IRQ is being services by the host.  Not&n;&t; * all cards support this feature and the values are ignored&n;&t; * in that case.&n;&t; */
DECL|member|rx_coalesce_usecs_irq
id|u32
id|rx_coalesce_usecs_irq
suffix:semicolon
DECL|member|rx_max_coalesced_frames_irq
id|u32
id|rx_max_coalesced_frames_irq
suffix:semicolon
multiline_comment|/* How many usecs to delay a TX interrupt after&n;&t; * a packet is sent.  If 0, only tx_max_coalesced_frames&n;&t; * is used.&n;&t; */
DECL|member|tx_coalesce_usecs
id|u32
id|tx_coalesce_usecs
suffix:semicolon
multiline_comment|/* How many packets to delay a TX interrupt after&n;&t; * a packet is sent.  If 0, only tx_coalesce_usecs is&n;&t; * used.  It is illegal to set both usecs and max frames&n;&t; * to zero as this would cause TX interrupts to never be&n;&t; * generated.&n;&t; */
DECL|member|tx_max_coalesced_frames
id|u32
id|tx_max_coalesced_frames
suffix:semicolon
multiline_comment|/* Same as above two parameters, except that these values&n;&t; * apply while an IRQ is being services by the host.  Not&n;&t; * all cards support this feature and the values are ignored&n;&t; * in that case.&n;&t; */
DECL|member|tx_coalesce_usecs_irq
id|u32
id|tx_coalesce_usecs_irq
suffix:semicolon
DECL|member|tx_max_coalesced_frames_irq
id|u32
id|tx_max_coalesced_frames_irq
suffix:semicolon
multiline_comment|/* How many usecs to delay in-memory statistics&n;&t; * block updates.  Some drivers do not have an in-memory&n;&t; * statistic block, and in such cases this value is ignored.&n;&t; * This value must not be zero.&n;&t; */
DECL|member|stats_block_coalesce_usecs
id|u32
id|stats_block_coalesce_usecs
suffix:semicolon
multiline_comment|/* Adaptive RX/TX coalescing is an algorithm implemented by&n;&t; * some drivers to improve latency under low packet rates and&n;&t; * improve throughput under high packet rates.  Some drivers&n;&t; * only implement one of RX or TX adaptive coalescing.  Anything&n;&t; * not implemented by the driver causes these values to be&n;&t; * silently ignored.&n;&t; */
DECL|member|use_adaptive_rx_coalesce
id|u32
id|use_adaptive_rx_coalesce
suffix:semicolon
DECL|member|use_adaptive_tx_coalesce
id|u32
id|use_adaptive_tx_coalesce
suffix:semicolon
multiline_comment|/* When the packet rate (measured in packets per second)&n;&t; * is below pkt_rate_low, the {rx,tx}_*_low parameters are&n;&t; * used.&n;&t; */
DECL|member|pkt_rate_low
id|u32
id|pkt_rate_low
suffix:semicolon
DECL|member|rx_coalesce_usecs_low
id|u32
id|rx_coalesce_usecs_low
suffix:semicolon
DECL|member|rx_max_coalesced_frames_low
id|u32
id|rx_max_coalesced_frames_low
suffix:semicolon
DECL|member|tx_coalesce_usecs_low
id|u32
id|tx_coalesce_usecs_low
suffix:semicolon
DECL|member|tx_max_coalesced_frames_low
id|u32
id|tx_max_coalesced_frames_low
suffix:semicolon
multiline_comment|/* When the packet rate is below pkt_rate_high but above&n;&t; * pkt_rate_low (both measured in packets per second) the&n;&t; * normal {rx,tx}_* coalescing parameters are used.&n;&t; */
multiline_comment|/* When the packet rate is (measured in packets per second)&n;&t; * is above pkt_rate_high, the {rx,tx}_*_high parameters are&n;&t; * used.&n;&t; */
DECL|member|pkt_rate_high
id|u32
id|pkt_rate_high
suffix:semicolon
DECL|member|rx_coalesce_usecs_high
id|u32
id|rx_coalesce_usecs_high
suffix:semicolon
DECL|member|rx_max_coalesced_frames_high
id|u32
id|rx_max_coalesced_frames_high
suffix:semicolon
DECL|member|tx_coalesce_usecs_high
id|u32
id|tx_coalesce_usecs_high
suffix:semicolon
DECL|member|tx_max_coalesced_frames_high
id|u32
id|tx_max_coalesced_frames_high
suffix:semicolon
multiline_comment|/* How often to do adaptive coalescing packet rate sampling,&n;&t; * measured in seconds.  Must not be zero.&n;&t; */
DECL|member|rate_sample_interval
id|u32
id|rate_sample_interval
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for configuring RX/TX ring parameters */
DECL|struct|ethtool_ringparam
r_struct
id|ethtool_ringparam
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
multiline_comment|/* ETHTOOL_{G,S}RINGPARAM */
multiline_comment|/* Read only attributes.  These indicate the maximum number&n;&t; * of pending RX/TX ring entries the driver will allow the&n;&t; * user to set.&n;&t; */
DECL|member|rx_max_pending
id|u32
id|rx_max_pending
suffix:semicolon
DECL|member|rx_mini_max_pending
id|u32
id|rx_mini_max_pending
suffix:semicolon
DECL|member|rx_jumbo_max_pending
id|u32
id|rx_jumbo_max_pending
suffix:semicolon
DECL|member|tx_max_pending
id|u32
id|tx_max_pending
suffix:semicolon
multiline_comment|/* Values changeable by the user.  The valid values are&n;&t; * in the range 1 to the &quot;*_max_pending&quot; counterpart above.&n;&t; */
DECL|member|rx_pending
id|u32
id|rx_pending
suffix:semicolon
DECL|member|rx_mini_pending
id|u32
id|rx_mini_pending
suffix:semicolon
DECL|member|rx_jumbo_pending
id|u32
id|rx_jumbo_pending
suffix:semicolon
DECL|member|tx_pending
id|u32
id|tx_pending
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for configuring link flow control parameters */
DECL|struct|ethtool_pauseparam
r_struct
id|ethtool_pauseparam
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
multiline_comment|/* ETHTOOL_{G,S}PAUSEPARAM */
multiline_comment|/* If the link is being auto-negotiated (via ethtool_cmd.autoneg&n;&t; * being true) the user may set &squot;autonet&squot; here non-zero to have the&n;&t; * pause parameters be auto-negotiated too.  In such a case, the&n;&t; * {rx,tx}_pause values below determine what capabilities are&n;&t; * advertised.&n;&t; *&n;&t; * If &squot;autoneg&squot; is zero or the link is not being auto-negotiated,&n;&t; * then {rx,tx}_pause force the driver to use/not-use pause&n;&t; * flow control.&n;&t; */
DECL|member|autoneg
id|u32
id|autoneg
suffix:semicolon
DECL|member|rx_pause
id|u32
id|rx_pause
suffix:semicolon
DECL|member|tx_pause
id|u32
id|tx_pause
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
mdefine_line|#define ETHTOOL_GLINK&t;&t;0x0000000a /* Get link status (ethtool_value) */
DECL|macro|ETHTOOL_GEEPROM
mdefine_line|#define ETHTOOL_GEEPROM&t;&t;0x0000000b /* Get EEPROM data */
DECL|macro|ETHTOOL_SEEPROM
mdefine_line|#define ETHTOOL_SEEPROM&t;&t;0x0000000c /* Set EEPROM data */
DECL|macro|ETHTOOL_GCOALESCE
mdefine_line|#define ETHTOOL_GCOALESCE&t;0x0000000e /* Get coalesce config */
DECL|macro|ETHTOOL_SCOALESCE
mdefine_line|#define ETHTOOL_SCOALESCE&t;0x0000000f /* Set coalesce config */
DECL|macro|ETHTOOL_GRINGPARAM
mdefine_line|#define ETHTOOL_GRINGPARAM&t;0x00000010 /* Get ring parameters */
DECL|macro|ETHTOOL_SRINGPARAM
mdefine_line|#define ETHTOOL_SRINGPARAM&t;0x00000011 /* Set ring parameters */
DECL|macro|ETHTOOL_GPAUSEPARAM
mdefine_line|#define ETHTOOL_GPAUSEPARAM&t;0x00000012 /* Get pause parameters */
DECL|macro|ETHTOOL_SPAUSEPARAM
mdefine_line|#define ETHTOOL_SPAUSEPARAM&t;0x00000013 /* Set pause parameters */
DECL|macro|ETHTOOL_GRXCSUM
mdefine_line|#define ETHTOOL_GRXCSUM&t;&t;0x00000014 /* Get RX hw csum enable (ethtool_value) */
DECL|macro|ETHTOOL_SRXCSUM
mdefine_line|#define ETHTOOL_SRXCSUM&t;&t;0x00000015 /* Set RX hw csum enable (ethtool_value) */
DECL|macro|ETHTOOL_GTXCSUM
mdefine_line|#define ETHTOOL_GTXCSUM&t;&t;0x00000016 /* Get TX hw csum enable (ethtool_value) */
DECL|macro|ETHTOOL_STXCSUM
mdefine_line|#define ETHTOOL_STXCSUM&t;&t;0x00000017 /* Set TX hw csum enable (ethtool_value) */
DECL|macro|ETHTOOL_GSG
mdefine_line|#define ETHTOOL_GSG&t;&t;0x00000018 /* Get scatter-gather enable&n;&t;&t;&t;&t;&t;    * (ethtool_value) */
DECL|macro|ETHTOOL_SSG
mdefine_line|#define ETHTOOL_SSG&t;&t;0x00000019 /* Set scatter-gather enable&n;&t;&t;&t;&t;&t;    * (ethtool_value) */
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
