multiline_comment|/******************************************************************************&n; *&n; * Name:        skethtool.c&n; * Project:     GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:     $Revision: 1.7 $&n; * Date:        $Date: 2004/09/29 13:32:07 $&n; * Purpose:     All functions regarding ethtool handling&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2004 Marvell.&n; *&n; *&t;Driver for Marvell Yukon/2 chipset and SysKonnect Gigabit Ethernet &n; *      Server Adapters.&n; *&n; *&t;Author: Ralph Roesler (rroesler@syskonnect.de)&n; *&t;        Mirko Lindner (mlindner@syskonnect.de)&n; *&n; *&t;Address all question to: linux@syskonnect.de&n; *&n; *&t;The technical manual for the adapters is available from SysKonnect&squot;s&n; *&t;web pages: www.syskonnect.com&n; *&t;&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; *****************************************************************************/
macro_line|#include &quot;h/skdrv1st.h&quot;
macro_line|#include &quot;h/skdrv2nd.h&quot;
macro_line|#include &quot;h/skversion.h&quot;
macro_line|#include &lt;linux/ethtool.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
multiline_comment|/******************************************************************************&n; *&n; * Defines&n; *&n; *****************************************************************************/
DECL|macro|SUPP_COPPER_ALL
mdefine_line|#define SUPP_COPPER_ALL (SUPPORTED_10baseT_Half  | SUPPORTED_10baseT_Full  | &bslash;&n;                         SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full | &bslash;&n;                         SUPPORTED_1000baseT_Half| SUPPORTED_1000baseT_Full| &bslash;&n;                         SUPPORTED_TP)
DECL|macro|ADV_COPPER_ALL
mdefine_line|#define ADV_COPPER_ALL  (ADVERTISED_10baseT_Half  | ADVERTISED_10baseT_Full  | &bslash;&n;                         ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full | &bslash;&n;                         ADVERTISED_1000baseT_Half| ADVERTISED_1000baseT_Full| &bslash;&n;                         ADVERTISED_TP)
DECL|macro|SUPP_FIBRE_ALL
mdefine_line|#define SUPP_FIBRE_ALL  (SUPPORTED_1000baseT_Full | &bslash;&n;                         SUPPORTED_FIBRE          | &bslash;&n;                         SUPPORTED_Autoneg)
DECL|macro|ADV_FIBRE_ALL
mdefine_line|#define ADV_FIBRE_ALL   (ADVERTISED_1000baseT_Full | &bslash;&n;                         ADVERTISED_FIBRE          | &bslash;&n;                         ADVERTISED_Autoneg)
multiline_comment|/******************************************************************************&n; *&n; * Local Functions&n; *&n; *****************************************************************************/
multiline_comment|/*****************************************************************************&n; *&n; * &t;getSettings - retrieves the current settings of the selected adapter&n; *&n; * Description:&n; *&t;The current configuration of the selected adapter is returned.&n; *&t;This configuration involves a)speed, b)duplex and c)autoneg plus&n; *&t;a number of other variables.&n; *&n; * Returns:    always 0&n; *&n; */
DECL|function|getSettings
r_static
r_int
id|getSettings
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ethtool_cmd
op_star
id|ecmd
)paren
(brace
r_const
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|port
op_assign
id|pNet-&gt;PortNr
suffix:semicolon
r_const
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
r_const
id|SK_GEPORT
op_star
id|pPort
op_assign
op_amp
id|pAC-&gt;GIni.GP
(braket
id|port
)braket
suffix:semicolon
r_static
r_int
id|DuplexAutoNegConfMap
(braket
l_int|9
)braket
(braket
l_int|3
)braket
op_assign
(brace
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|0
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
(brace
id|SK_LMODE_HALF
comma
id|DUPLEX_HALF
comma
id|AUTONEG_DISABLE
)brace
comma
(brace
id|SK_LMODE_FULL
comma
id|DUPLEX_FULL
comma
id|AUTONEG_DISABLE
)brace
comma
(brace
id|SK_LMODE_AUTOHALF
comma
id|DUPLEX_HALF
comma
id|AUTONEG_ENABLE
)brace
comma
(brace
id|SK_LMODE_AUTOFULL
comma
id|DUPLEX_FULL
comma
id|AUTONEG_ENABLE
)brace
comma
(brace
id|SK_LMODE_AUTOBOTH
comma
id|DUPLEX_FULL
comma
id|AUTONEG_ENABLE
)brace
comma
(brace
id|SK_LMODE_AUTOSENSE
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
(brace
id|SK_LMODE_INDETERMINATED
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
r_static
r_int
id|SpeedConfMap
(braket
l_int|6
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|SK_LSPEED_AUTO
comma
op_minus
l_int|1
)brace
comma
(brace
id|SK_LSPEED_10MBPS
comma
id|SPEED_10
)brace
comma
(brace
id|SK_LSPEED_100MBPS
comma
id|SPEED_100
)brace
comma
(brace
id|SK_LSPEED_1000MBPS
comma
id|SPEED_1000
)brace
comma
(brace
id|SK_LSPEED_INDETERMINATED
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
r_static
r_int
id|AdvSpeedMap
(braket
l_int|6
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|SK_LSPEED_AUTO
comma
op_minus
l_int|1
)brace
comma
(brace
id|SK_LSPEED_10MBPS
comma
id|ADVERTISED_10baseT_Half
op_or
id|ADVERTISED_10baseT_Full
)brace
comma
(brace
id|SK_LSPEED_100MBPS
comma
id|ADVERTISED_100baseT_Half
op_or
id|ADVERTISED_100baseT_Full
)brace
comma
(brace
id|SK_LSPEED_1000MBPS
comma
id|ADVERTISED_1000baseT_Half
op_or
id|ADVERTISED_1000baseT_Full
)brace
comma
(brace
id|SK_LSPEED_INDETERMINATED
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
id|ecmd-&gt;phy_address
op_assign
id|port
suffix:semicolon
id|ecmd-&gt;speed
op_assign
id|SpeedConfMap
(braket
id|pPort-&gt;PLinkSpeedUsed
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|ecmd-&gt;duplex
op_assign
id|DuplexAutoNegConfMap
(braket
id|pPort-&gt;PLinkModeStatus
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|ecmd-&gt;autoneg
op_assign
id|DuplexAutoNegConfMap
(braket
id|pPort-&gt;PLinkModeStatus
)braket
(braket
l_int|2
)braket
suffix:semicolon
id|ecmd-&gt;transceiver
op_assign
id|XCVR_INTERNAL
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GICopperType
)paren
(brace
id|ecmd-&gt;port
op_assign
id|PORT_TP
suffix:semicolon
id|ecmd-&gt;supported
op_assign
(paren
id|SUPP_COPPER_ALL
op_or
id|SUPPORTED_Autoneg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIGenesis
)paren
(brace
id|ecmd-&gt;supported
op_and_assign
op_complement
(paren
id|SUPPORTED_10baseT_Half
)paren
suffix:semicolon
id|ecmd-&gt;supported
op_and_assign
op_complement
(paren
id|SUPPORTED_10baseT_Full
)paren
suffix:semicolon
id|ecmd-&gt;supported
op_and_assign
op_complement
(paren
id|SUPPORTED_100baseT_Half
)paren
suffix:semicolon
id|ecmd-&gt;supported
op_and_assign
op_complement
(paren
id|SUPPORTED_100baseT_Full
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIChipId
op_eq
id|CHIP_ID_YUKON
)paren
(brace
id|ecmd-&gt;supported
op_and_assign
op_complement
(paren
id|SUPPORTED_1000baseT_Half
)paren
suffix:semicolon
)brace
macro_line|#ifdef CHIP_ID_YUKON_FE
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIChipId
op_eq
id|CHIP_ID_YUKON_FE
)paren
(brace
id|ecmd-&gt;supported
op_and_assign
op_complement
(paren
id|SUPPORTED_1000baseT_Half
)paren
suffix:semicolon
id|ecmd-&gt;supported
op_and_assign
op_complement
(paren
id|SUPPORTED_1000baseT_Full
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_if
c_cond
(paren
id|pAC-&gt;GIni.GP
(braket
l_int|0
)braket
dot
id|PLinkSpeed
op_ne
id|SK_LSPEED_AUTO
)paren
(brace
id|ecmd-&gt;advertising
op_assign
id|AdvSpeedMap
(braket
id|pPort-&gt;PLinkSpeed
)braket
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIChipId
op_eq
id|CHIP_ID_YUKON
)paren
(brace
id|ecmd-&gt;advertising
op_and_assign
op_complement
(paren
id|SUPPORTED_1000baseT_Half
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ecmd-&gt;advertising
op_assign
id|ecmd-&gt;supported
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ecmd-&gt;autoneg
op_eq
id|AUTONEG_ENABLE
)paren
id|ecmd-&gt;advertising
op_or_assign
id|ADVERTISED_Autoneg
suffix:semicolon
)brace
r_else
(brace
id|ecmd-&gt;port
op_assign
id|PORT_FIBRE
suffix:semicolon
id|ecmd-&gt;supported
op_assign
id|SUPP_FIBRE_ALL
suffix:semicolon
id|ecmd-&gt;advertising
op_assign
id|ADV_FIBRE_ALL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * MIB infrastructure uses instance value starting at 1&n; * based on board and port.&n; */
DECL|function|pnmiInstance
r_static
r_inline
id|u32
id|pnmiInstance
c_func
(paren
r_const
id|DEV_NET
op_star
id|pNet
)paren
(brace
r_return
l_int|1
op_plus
(paren
id|pNet-&gt;pAC-&gt;RlmtNets
op_eq
l_int|2
)paren
op_plus
id|pNet-&gt;PortNr
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; *&t;setSettings - configures the settings of a selected adapter&n; *&n; * Description:&n; *&t;Possible settings that may be altered are a)speed, b)duplex or &n; *&t;c)autonegotiation.&n; *&n; * Returns:&n; *&t;0:&t;everything fine, no error&n; *&t;&lt;0:&t;the return value is the error code of the failure &n; */
DECL|function|setSettings
r_static
r_int
id|setSettings
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ethtool_cmd
op_star
id|ecmd
)paren
(brace
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
id|u32
id|instance
suffix:semicolon
r_char
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|len
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;speed
op_ne
id|SPEED_10
op_logical_and
id|ecmd-&gt;speed
op_ne
id|SPEED_100
op_logical_and
id|ecmd-&gt;speed
op_ne
id|SPEED_1000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;duplex
op_ne
id|DUPLEX_HALF
op_logical_and
id|ecmd-&gt;duplex
op_ne
id|DUPLEX_FULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;autoneg
op_ne
id|AUTONEG_DISABLE
op_logical_and
id|ecmd-&gt;autoneg
op_ne
id|AUTONEG_ENABLE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;autoneg
op_eq
id|AUTONEG_DISABLE
)paren
op_star
id|buf
op_assign
(paren
id|ecmd-&gt;duplex
op_eq
id|DUPLEX_FULL
)paren
ques
c_cond
id|SK_LMODE_FULL
suffix:colon
id|SK_LMODE_HALF
suffix:semicolon
r_else
op_star
id|buf
op_assign
(paren
id|ecmd-&gt;duplex
op_eq
id|DUPLEX_FULL
)paren
ques
c_cond
id|SK_LMODE_AUTOFULL
suffix:colon
id|SK_LMODE_AUTOHALF
suffix:semicolon
id|instance
op_assign
id|pnmiInstance
c_func
(paren
id|pNet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SkPnmiSetVar
c_func
(paren
id|pAC
comma
id|pAC-&gt;IoBase
comma
id|OID_SKGE_LINK_MODE
comma
op_amp
id|buf
comma
op_amp
id|len
comma
id|instance
comma
id|pNet-&gt;NetNr
)paren
op_ne
id|SK_PNMI_ERR_OK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|ecmd-&gt;speed
)paren
(brace
r_case
id|SPEED_1000
suffix:colon
op_star
id|buf
op_assign
id|SK_LSPEED_1000MBPS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_100
suffix:colon
op_star
id|buf
op_assign
id|SK_LSPEED_100MBPS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_10
suffix:colon
op_star
id|buf
op_assign
id|SK_LSPEED_10MBPS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SkPnmiSetVar
c_func
(paren
id|pAC
comma
id|pAC-&gt;IoBase
comma
id|OID_SKGE_SPEED_MODE
comma
op_amp
id|buf
comma
op_amp
id|len
comma
id|instance
comma
id|pNet-&gt;NetNr
)paren
op_ne
id|SK_PNMI_ERR_OK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * &t;getDriverInfo - returns generic driver and adapter information&n; *&n; * Description:&n; *&t;Generic driver information is returned via this function, such as&n; *&t;the name of the driver, its version and and firmware version.&n; *&t;In addition to this, the location of the selected adapter is &n; *&t;returned as a bus info string (e.g. &squot;01:05.0&squot;).&n; *&t;&n; * Returns:&t;N/A&n; *&n; */
DECL|function|getDriverInfo
r_static
r_void
id|getDriverInfo
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ethtool_drvinfo
op_star
id|info
)paren
(brace
r_const
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_const
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
r_char
id|vers
(braket
l_int|32
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|vers
comma
r_sizeof
(paren
id|vers
)paren
op_minus
l_int|1
comma
id|VER_STRING
l_string|&quot;(v%d.%d)&quot;
comma
(paren
id|pAC-&gt;GIni.GIPciHwRev
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|pAC-&gt;GIni.GIPciHwRev
op_amp
l_int|0xf
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|info-&gt;driver
comma
id|DRIVER_FILE_NAME
comma
r_sizeof
(paren
id|info-&gt;driver
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;version
comma
id|vers
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;fw_version
comma
l_string|&quot;N/A&quot;
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|info-&gt;bus_info
comma
id|pAC-&gt;PciDev-&gt;slot_name
comma
id|ETHTOOL_BUSINFO_LEN
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ethtool statistics support.&n; */
DECL|variable|StringsStats
r_static
r_const
r_char
id|StringsStats
(braket
)braket
(braket
id|ETH_GSTRING_LEN
)braket
op_assign
(brace
l_string|&quot;rx_packets&quot;
comma
l_string|&quot;tx_packets&quot;
comma
l_string|&quot;rx_bytes&quot;
comma
l_string|&quot;tx_bytes&quot;
comma
l_string|&quot;rx_errors&quot;
comma
l_string|&quot;tx_errors&quot;
comma
l_string|&quot;rx_dropped&quot;
comma
l_string|&quot;tx_dropped&quot;
comma
l_string|&quot;multicasts&quot;
comma
l_string|&quot;collisions&quot;
comma
l_string|&quot;rx_length_errors&quot;
comma
l_string|&quot;rx_buffer_overflow_errors&quot;
comma
l_string|&quot;rx_crc_errors&quot;
comma
l_string|&quot;rx_frame_errors&quot;
comma
l_string|&quot;rx_too_short_errors&quot;
comma
l_string|&quot;rx_too_long_errors&quot;
comma
l_string|&quot;rx_carrier_extension_errors&quot;
comma
l_string|&quot;rx_symbol_errors&quot;
comma
l_string|&quot;rx_llc_mac_size_errors&quot;
comma
l_string|&quot;rx_carrier_errors&quot;
comma
l_string|&quot;rx_jabber_errors&quot;
comma
l_string|&quot;rx_missed_errors&quot;
comma
l_string|&quot;tx_abort_collision_errors&quot;
comma
l_string|&quot;tx_carrier_errors&quot;
comma
l_string|&quot;tx_buffer_underrun_errors&quot;
comma
l_string|&quot;tx_heartbeat_errors&quot;
comma
l_string|&quot;tx_window_errors&quot;
comma
)brace
suffix:semicolon
DECL|function|getStatsCount
r_static
r_int
id|getStatsCount
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|ARRAY_SIZE
c_func
(paren
id|StringsStats
)paren
suffix:semicolon
)brace
DECL|function|getStrings
r_static
r_void
id|getStrings
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|stringset
comma
id|u8
op_star
id|data
)paren
(brace
r_switch
c_cond
(paren
id|stringset
)paren
(brace
r_case
id|ETH_SS_STATS
suffix:colon
id|memcpy
c_func
(paren
id|data
comma
op_star
id|StringsStats
comma
r_sizeof
(paren
id|StringsStats
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|getEthtoolStats
r_static
r_void
id|getEthtoolStats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ethtool_stats
op_star
id|stats
comma
id|u64
op_star
id|data
)paren
(brace
r_const
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_const
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
r_const
id|SK_PNMI_STRUCT_DATA
op_star
id|pPnmiStruct
op_assign
op_amp
id|pAC-&gt;PnmiStruct
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxOkCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatTxOkCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxOctetsOkCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatTxOctetsOkCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;InErrorsCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatTxSingleCollisionCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;RxNoBufCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;TxNoBufCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxMulticastOkCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatTxSingleCollisionCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxRuntCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxFifoOverflowCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxFcsCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxFramingCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxShortsCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxTooLongCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxCextCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxSymbolCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxIRLengthCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxCarrierCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxJabberCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatRxMissedCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pAC-&gt;stats.tx_aborted_errors
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatTxCarrierCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatTxFifoUnderrunCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
dot
id|StatTxCarrierCts
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|pAC-&gt;stats.tx_window_errors
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * &t;toggleLeds - Changes the LED state of an adapter&n; *&n; * Description:&n; *&t;This function changes the current state of all LEDs of an adapter so&n; *&t;that it can be located by a user. &n; *&n; * Returns:&t;N/A&n; *&n; */
DECL|function|toggleLeds
r_static
r_void
id|toggleLeds
c_func
(paren
id|DEV_NET
op_star
id|pNet
comma
r_int
id|on
)paren
(brace
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
r_int
id|port
op_assign
id|pNet-&gt;PortNr
suffix:semicolon
r_void
id|__iomem
op_star
id|io
op_assign
id|pAC-&gt;IoBase
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIGenesis
)paren
(brace
id|SK_OUT8
c_func
(paren
id|io
comma
id|MR_ADDR
c_func
(paren
id|port
comma
id|LNK_LED_REG
)paren
comma
id|on
ques
c_cond
id|SK_LNK_ON
suffix:colon
id|SK_LNK_OFF
)paren
suffix:semicolon
id|SkGeYellowLED
c_func
(paren
id|pAC
comma
id|io
comma
id|on
ques
c_cond
(paren
id|LED_ON
op_rshift
l_int|1
)paren
suffix:colon
(paren
id|LED_OFF
op_rshift
l_int|1
)paren
)paren
suffix:semicolon
id|SkGeXmitLED
c_func
(paren
id|pAC
comma
id|io
comma
id|MR_ADDR
c_func
(paren
id|port
comma
id|RX_LED_INI
)paren
comma
id|on
ques
c_cond
id|SK_LED_TST
suffix:colon
id|SK_LED_DIS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GP
(braket
id|port
)braket
dot
id|PhyType
op_eq
id|SK_PHY_BCOM
)paren
id|SkXmPhyWrite
c_func
(paren
id|pAC
comma
id|io
comma
id|port
comma
id|PHY_BCOM_P_EXT_CTRL
comma
id|on
ques
c_cond
id|PHY_B_PEC_LED_ON
suffix:colon
id|PHY_B_PEC_LED_OFF
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pAC-&gt;GIni.GP
(braket
id|port
)braket
dot
id|PhyType
op_eq
id|SK_PHY_LONE
)paren
id|SkXmPhyWrite
c_func
(paren
id|pAC
comma
id|io
comma
id|port
comma
id|PHY_LONE_LED_CFG
comma
id|on
ques
c_cond
l_int|0x0800
suffix:colon
id|PHY_L_LC_LEDT
)paren
suffix:semicolon
r_else
id|SkGeXmitLED
c_func
(paren
id|pAC
comma
id|io
comma
id|MR_ADDR
c_func
(paren
id|port
comma
id|TX_LED_INI
)paren
comma
id|on
ques
c_cond
id|SK_LED_TST
suffix:colon
id|SK_LED_DIS
)paren
suffix:semicolon
)brace
r_else
(brace
r_const
id|u16
id|YukLedOn
op_assign
(paren
id|PHY_M_LED_MO_DUP
c_func
(paren
id|MO_LED_ON
)paren
op_or
id|PHY_M_LED_MO_10
c_func
(paren
id|MO_LED_ON
)paren
op_or
id|PHY_M_LED_MO_100
c_func
(paren
id|MO_LED_ON
)paren
op_or
id|PHY_M_LED_MO_1000
c_func
(paren
id|MO_LED_ON
)paren
op_or
id|PHY_M_LED_MO_RX
c_func
(paren
id|MO_LED_ON
)paren
)paren
suffix:semicolon
r_const
id|u16
id|YukLedOff
op_assign
(paren
id|PHY_M_LED_MO_DUP
c_func
(paren
id|MO_LED_OFF
)paren
op_or
id|PHY_M_LED_MO_10
c_func
(paren
id|MO_LED_OFF
)paren
op_or
id|PHY_M_LED_MO_100
c_func
(paren
id|MO_LED_OFF
)paren
op_or
id|PHY_M_LED_MO_1000
c_func
(paren
id|MO_LED_OFF
)paren
op_or
id|PHY_M_LED_MO_RX
c_func
(paren
id|MO_LED_OFF
)paren
)paren
suffix:semicolon
id|SkGmPhyWrite
c_func
(paren
id|pAC
comma
id|io
comma
id|port
comma
id|PHY_MARV_LED_CTRL
comma
l_int|0
)paren
suffix:semicolon
id|SkGmPhyWrite
c_func
(paren
id|pAC
comma
id|io
comma
id|port
comma
id|PHY_MARV_LED_OVER
comma
id|on
ques
c_cond
id|YukLedOn
suffix:colon
id|YukLedOff
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*****************************************************************************&n; *&n; * &t;skGeBlinkTimer - Changes the LED state of an adapter&n; *&n; * Description:&n; *&t;This function changes the current state of all LEDs of an adapter so&n; *&t;that it can be located by a user. If the requested time interval for&n; *&t;this test has elapsed, this function cleans up everything that was &n; *&t;temporarily setup during the locate NIC test. This involves of course&n; *&t;also closing or opening any adapter so that the initial board state &n; *&t;is recovered.&n; *&n; * Returns:&t;N/A&n; *&n; */
DECL|function|SkGeBlinkTimer
r_void
id|SkGeBlinkTimer
c_func
(paren
r_int
r_int
id|data
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
id|data
suffix:semicolon
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
id|toggleLeds
c_func
(paren
id|pNet
comma
id|pAC-&gt;LedsOn
)paren
suffix:semicolon
id|pAC-&gt;LedsOn
op_assign
op_logical_neg
id|pAC-&gt;LedsOn
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|pAC-&gt;BlinkTimer
comma
id|jiffies
op_plus
id|HZ
op_div
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * &t;locateDevice - start the locate NIC feature of the elected adapter &n; *&n; * Description:&n; *&t;This function is used if the user want to locate a particular NIC.&n; *&t;All LEDs are regularly switched on and off, so the NIC can easily&n; *&t;be identified.&n; *&n; * Returns:&t;&n; *&t;==0:&t;everything fine, no error, locateNIC test was started&n; *&t;!=0:&t;one locateNIC test runs already&n; *&n; */
DECL|function|locateDevice
r_static
r_int
id|locateDevice
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|data
)paren
(brace
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
op_logical_or
id|data
OG
(paren
id|u32
)paren
(paren
id|MAX_SCHEDULE_TIMEOUT
op_div
id|HZ
)paren
)paren
(brace
id|data
op_assign
(paren
id|u32
)paren
(paren
id|MAX_SCHEDULE_TIMEOUT
op_div
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/* start blinking */
id|pAC-&gt;LedsOn
op_assign
l_int|0
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|pAC-&gt;BlinkTimer
comma
id|jiffies
)paren
suffix:semicolon
id|msleep_interruptible
c_func
(paren
id|data
op_star
l_int|1000
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|data
op_star
id|HZ
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|pAC-&gt;BlinkTimer
)paren
suffix:semicolon
id|toggleLeds
c_func
(paren
id|pNet
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * &t;getPauseParams - retrieves the pause parameters&n; *&n; * Description:&n; *&t;All current pause parameters of a selected adapter are placed &n; *&t;in the passed ethtool_pauseparam structure and are returned.&n; *&n; * Returns:&t;N/A&n; *&n; */
DECL|function|getPauseParams
r_static
r_void
id|getPauseParams
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ethtool_pauseparam
op_star
id|epause
)paren
(brace
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
id|SK_GEPORT
op_star
id|pPort
op_assign
op_amp
id|pAC-&gt;GIni.GP
(braket
id|pNet-&gt;PortNr
)braket
suffix:semicolon
id|epause-&gt;rx_pause
op_assign
(paren
id|pPort-&gt;PFlowCtrlMode
op_eq
id|SK_FLOW_MODE_SYMMETRIC
)paren
op_logical_or
(paren
id|pPort-&gt;PFlowCtrlMode
op_eq
id|SK_FLOW_MODE_SYM_OR_REM
)paren
suffix:semicolon
id|epause-&gt;tx_pause
op_assign
id|epause-&gt;rx_pause
op_logical_or
(paren
id|pPort-&gt;PFlowCtrlMode
op_eq
id|SK_FLOW_MODE_LOC_SEND
)paren
suffix:semicolon
id|epause-&gt;autoneg
op_assign
id|epause-&gt;rx_pause
op_logical_or
id|epause-&gt;tx_pause
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; *&t;setPauseParams - configures the pause parameters of an adapter&n; *&n; * Description:&n; *&t;This function sets the Rx or Tx pause parameters &n; *&n; * Returns:&n; *&t;==0:&t;everything fine, no error&n; *&t;!=0:&t;the return value is the error code of the failure &n; */
DECL|function|setPauseParams
r_static
r_int
id|setPauseParams
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ethtool_pauseparam
op_star
id|epause
)paren
(brace
id|DEV_NET
op_star
id|pNet
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SK_AC
op_star
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
id|SK_GEPORT
op_star
id|pPort
op_assign
op_amp
id|pAC-&gt;GIni.GP
(braket
id|pNet-&gt;PortNr
)braket
suffix:semicolon
id|u32
id|instance
op_assign
id|pnmiInstance
c_func
(paren
id|pNet
)paren
suffix:semicolon
r_struct
id|ethtool_pauseparam
id|old
suffix:semicolon
id|u8
id|oldspeed
op_assign
id|pPort-&gt;PLinkSpeedUsed
suffix:semicolon
r_char
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|len
op_assign
l_int|1
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t;** we have to determine the current settings to see if &n;&t;** the operator requested any modification of the flow &n;&t;** control parameters...&n;&t;*/
id|getPauseParams
c_func
(paren
id|dev
comma
op_amp
id|old
)paren
suffix:semicolon
multiline_comment|/*&n;&t;** perform modifications regarding the changes &n;&t;** requested by the operator&n;&t;*/
r_if
c_cond
(paren
id|epause-&gt;autoneg
op_ne
id|old.autoneg
)paren
op_star
id|buf
op_assign
id|epause-&gt;autoneg
ques
c_cond
id|SK_FLOW_MODE_NONE
suffix:colon
id|SK_FLOW_MODE_SYMMETRIC
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|epause-&gt;rx_pause
op_logical_and
id|epause-&gt;tx_pause
)paren
op_star
id|buf
op_assign
id|SK_FLOW_MODE_SYMMETRIC
suffix:semicolon
r_else
r_if
c_cond
(paren
id|epause-&gt;rx_pause
op_logical_and
op_logical_neg
id|epause-&gt;tx_pause
)paren
op_star
id|buf
op_assign
id|SK_FLOW_MODE_SYM_OR_REM
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|epause-&gt;rx_pause
op_logical_and
id|epause-&gt;tx_pause
)paren
op_star
id|buf
op_assign
id|SK_FLOW_MODE_LOC_SEND
suffix:semicolon
r_else
op_star
id|buf
op_assign
id|SK_FLOW_MODE_NONE
suffix:semicolon
)brace
id|ret
op_assign
id|SkPnmiSetVar
c_func
(paren
id|pAC
comma
id|pAC-&gt;IoBase
comma
id|OID_SKGE_FLOWCTRL_MODE
comma
op_amp
id|buf
comma
op_amp
id|len
comma
id|instance
comma
id|pNet-&gt;NetNr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|SK_PNMI_ERR_OK
)paren
(brace
id|SK_DBG_MSG
c_func
(paren
l_int|NULL
comma
id|SK_DBGMOD_DRV
comma
id|SK_DBGCAT_CTRL
comma
(paren
l_string|&quot;ethtool (sk98lin): error changing rx/tx pause (%i)&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;&t;** It may be that autoneg has been disabled! Therefore&n;&t;** set the speed to the previously used value...&n;&t;*/
r_if
c_cond
(paren
op_logical_neg
id|epause-&gt;autoneg
)paren
(brace
id|len
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|SkPnmiSetVar
c_func
(paren
id|pAC
comma
id|pAC-&gt;IoBase
comma
id|OID_SKGE_SPEED_MODE
comma
op_amp
id|oldspeed
comma
op_amp
id|len
comma
id|instance
comma
id|pNet-&gt;NetNr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|SK_PNMI_ERR_OK
)paren
id|SK_DBG_MSG
c_func
(paren
l_int|NULL
comma
id|SK_DBGMOD_DRV
comma
id|SK_DBGCAT_CTRL
comma
(paren
l_string|&quot;ethtool (sk98lin): error setting speed (%i)&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
id|err
suffix:colon
r_return
id|ret
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|variable|SkGeEthtoolOps
r_struct
id|ethtool_ops
id|SkGeEthtoolOps
op_assign
(brace
dot
id|get_settings
op_assign
id|getSettings
comma
dot
id|set_settings
op_assign
id|setSettings
comma
dot
id|get_drvinfo
op_assign
id|getDriverInfo
comma
dot
id|get_strings
op_assign
id|getStrings
comma
dot
id|get_stats_count
op_assign
id|getStatsCount
comma
dot
id|get_ethtool_stats
op_assign
id|getEthtoolStats
comma
dot
id|phys_id
op_assign
id|locateDevice
comma
dot
id|get_pauseparam
op_assign
id|getPauseParams
comma
dot
id|set_pauseparam
op_assign
id|setPauseParams
comma
)brace
suffix:semicolon
eof
