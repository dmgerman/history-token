multiline_comment|/*****************************************************************************&n; *&n; * Name:&t;skgepnmi.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.62 $&n; * Date:&t;$Date: 2003/08/15 12:31:52 $&n; * Purpose:&t;Defines for Private Network Management Interface&n; *&n; ****************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef _SKGEPNMI_H_
DECL|macro|_SKGEPNMI_H_
mdefine_line|#define _SKGEPNMI_H_
multiline_comment|/*&n; * Include dependencies&n; */
macro_line|#include &quot;h/sktypes.h&quot;
macro_line|#include &quot;h/skerror.h&quot;
macro_line|#include &quot;h/sktimer.h&quot;
macro_line|#include &quot;h/ski2c.h&quot;
macro_line|#include &quot;h/skaddr.h&quot;
macro_line|#include &quot;h/skrlmt.h&quot;
macro_line|#include &quot;h/skvpd.h&quot;
multiline_comment|/*&n; * Management Database Version&n; */
DECL|macro|SK_PNMI_MDB_VERSION
mdefine_line|#define SK_PNMI_MDB_VERSION&t;&t;0x00030001&t;/* 3.1 */
multiline_comment|/*&n; * Event definitions&n; */
DECL|macro|SK_PNMI_EVT_SIRQ_OVERFLOW
mdefine_line|#define SK_PNMI_EVT_SIRQ_OVERFLOW&t;&t;1&t;/* Counter overflow */
DECL|macro|SK_PNMI_EVT_SEN_WAR_LOW
mdefine_line|#define SK_PNMI_EVT_SEN_WAR_LOW&t;&t;&t;2&t;/* Lower war thres exceeded */
DECL|macro|SK_PNMI_EVT_SEN_WAR_UPP
mdefine_line|#define SK_PNMI_EVT_SEN_WAR_UPP&t;&t;&t;3&t;/* Upper war thres exceeded */
DECL|macro|SK_PNMI_EVT_SEN_ERR_LOW
mdefine_line|#define SK_PNMI_EVT_SEN_ERR_LOW&t;&t;&t;4&t;/* Lower err thres exceeded */
DECL|macro|SK_PNMI_EVT_SEN_ERR_UPP
mdefine_line|#define SK_PNMI_EVT_SEN_ERR_UPP&t;&t;&t;5&t;/* Upper err thres exceeded */
DECL|macro|SK_PNMI_EVT_CHG_EST_TIMER
mdefine_line|#define SK_PNMI_EVT_CHG_EST_TIMER&t;&t;6&t;/* Timer event for RLMT Chg */
DECL|macro|SK_PNMI_EVT_UTILIZATION_TIMER
mdefine_line|#define SK_PNMI_EVT_UTILIZATION_TIMER&t;7&t;/* Timer event for Utiliza. */
DECL|macro|SK_PNMI_EVT_CLEAR_COUNTER
mdefine_line|#define SK_PNMI_EVT_CLEAR_COUNTER&t;&t;8&t;/* Clear statistic counters */
DECL|macro|SK_PNMI_EVT_XMAC_RESET
mdefine_line|#define SK_PNMI_EVT_XMAC_RESET&t;&t;&t;9&t;/* XMAC will be reset */
DECL|macro|SK_PNMI_EVT_RLMT_PORT_UP
mdefine_line|#define SK_PNMI_EVT_RLMT_PORT_UP&t;&t;10&t;/* Port came logically up */
DECL|macro|SK_PNMI_EVT_RLMT_PORT_DOWN
mdefine_line|#define SK_PNMI_EVT_RLMT_PORT_DOWN&t;&t;11&t;/* Port went logically down */
DECL|macro|SK_PNMI_EVT_RLMT_SEGMENTATION
mdefine_line|#define SK_PNMI_EVT_RLMT_SEGMENTATION&t;13&t;/* Two SP root bridges found */
DECL|macro|SK_PNMI_EVT_RLMT_ACTIVE_DOWN
mdefine_line|#define SK_PNMI_EVT_RLMT_ACTIVE_DOWN&t;14&t;/* Port went logically down */
DECL|macro|SK_PNMI_EVT_RLMT_ACTIVE_UP
mdefine_line|#define SK_PNMI_EVT_RLMT_ACTIVE_UP&t;&t;15&t;/* Port came logically up */
DECL|macro|SK_PNMI_EVT_RLMT_SET_NETS
mdefine_line|#define SK_PNMI_EVT_RLMT_SET_NETS&t;&t;16&t;/* 1. Parameter is number of nets&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;1 = single net; 2 = dual net */
DECL|macro|SK_PNMI_EVT_VCT_RESET
mdefine_line|#define SK_PNMI_EVT_VCT_RESET&t;&t;17&t;/* VCT port reset timer event started with SET. */
multiline_comment|/*&n; * Return values&n; */
DECL|macro|SK_PNMI_ERR_OK
mdefine_line|#define SK_PNMI_ERR_OK&t;&t;&t;&t;0
DECL|macro|SK_PNMI_ERR_GENERAL
mdefine_line|#define SK_PNMI_ERR_GENERAL&t;&t;&t;1
DECL|macro|SK_PNMI_ERR_TOO_SHORT
mdefine_line|#define SK_PNMI_ERR_TOO_SHORT&t;&t;2
DECL|macro|SK_PNMI_ERR_BAD_VALUE
mdefine_line|#define SK_PNMI_ERR_BAD_VALUE&t;&t;3
DECL|macro|SK_PNMI_ERR_READ_ONLY
mdefine_line|#define SK_PNMI_ERR_READ_ONLY&t;&t;4
DECL|macro|SK_PNMI_ERR_UNKNOWN_OID
mdefine_line|#define SK_PNMI_ERR_UNKNOWN_OID&t;&t;5
DECL|macro|SK_PNMI_ERR_UNKNOWN_INST
mdefine_line|#define SK_PNMI_ERR_UNKNOWN_INST&t;6
DECL|macro|SK_PNMI_ERR_UNKNOWN_NET
mdefine_line|#define SK_PNMI_ERR_UNKNOWN_NET &t;7
DECL|macro|SK_PNMI_ERR_NOT_SUPPORTED
mdefine_line|#define SK_PNMI_ERR_NOT_SUPPORTED&t;10
multiline_comment|/*&n; * Return values of driver reset function SK_DRIVER_RESET() and&n; * driver event function SK_DRIVER_EVENT()&n; */
DECL|macro|SK_PNMI_ERR_OK
mdefine_line|#define SK_PNMI_ERR_OK&t;&t;&t;0
DECL|macro|SK_PNMI_ERR_FAIL
mdefine_line|#define SK_PNMI_ERR_FAIL&t;&t;1
multiline_comment|/*&n; * Return values of driver test function SK_DRIVER_SELFTEST()&n; */
DECL|macro|SK_PNMI_TST_UNKNOWN
mdefine_line|#define SK_PNMI_TST_UNKNOWN&t;&t;(1 &lt;&lt; 0)
DECL|macro|SK_PNMI_TST_TRANCEIVER
mdefine_line|#define SK_PNMI_TST_TRANCEIVER&t;&t;(1 &lt;&lt; 1)
DECL|macro|SK_PNMI_TST_ASIC
mdefine_line|#define SK_PNMI_TST_ASIC&t;&t;(1 &lt;&lt; 2)
DECL|macro|SK_PNMI_TST_SENSOR
mdefine_line|#define SK_PNMI_TST_SENSOR&t;&t;(1 &lt;&lt; 3)
DECL|macro|SK_PNMI_TST_POWERMGMT
mdefine_line|#define SK_PNMI_TST_POWERMGMT&t;&t;(1 &lt;&lt; 4)
DECL|macro|SK_PNMI_TST_PCI
mdefine_line|#define SK_PNMI_TST_PCI&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|SK_PNMI_TST_MAC
mdefine_line|#define SK_PNMI_TST_MAC&t;&t;&t;(1 &lt;&lt; 6)
multiline_comment|/*&n; * RLMT specific definitions&n; */
DECL|macro|SK_PNMI_RLMT_STATUS_STANDBY
mdefine_line|#define SK_PNMI_RLMT_STATUS_STANDBY&t;1
DECL|macro|SK_PNMI_RLMT_STATUS_ACTIVE
mdefine_line|#define SK_PNMI_RLMT_STATUS_ACTIVE&t;2
DECL|macro|SK_PNMI_RLMT_STATUS_ERROR
mdefine_line|#define SK_PNMI_RLMT_STATUS_ERROR&t;3
DECL|macro|SK_PNMI_RLMT_LSTAT_PHY_DOWN
mdefine_line|#define SK_PNMI_RLMT_LSTAT_PHY_DOWN&t;1
DECL|macro|SK_PNMI_RLMT_LSTAT_AUTONEG
mdefine_line|#define SK_PNMI_RLMT_LSTAT_AUTONEG&t;2
DECL|macro|SK_PNMI_RLMT_LSTAT_LOG_DOWN
mdefine_line|#define SK_PNMI_RLMT_LSTAT_LOG_DOWN&t;3
DECL|macro|SK_PNMI_RLMT_LSTAT_LOG_UP
mdefine_line|#define SK_PNMI_RLMT_LSTAT_LOG_UP&t;4
DECL|macro|SK_PNMI_RLMT_LSTAT_INDETERMINATED
mdefine_line|#define SK_PNMI_RLMT_LSTAT_INDETERMINATED 5
DECL|macro|SK_PNMI_RLMT_MODE_CHK_LINK
mdefine_line|#define SK_PNMI_RLMT_MODE_CHK_LINK&t;(SK_RLMT_CHECK_LINK)
DECL|macro|SK_PNMI_RLMT_MODE_CHK_RX
mdefine_line|#define SK_PNMI_RLMT_MODE_CHK_RX&t;(SK_RLMT_CHECK_LOC_LINK)
DECL|macro|SK_PNMI_RLMT_MODE_CHK_SPT
mdefine_line|#define SK_PNMI_RLMT_MODE_CHK_SPT&t;(SK_RLMT_CHECK_SEG)
multiline_comment|/* #define SK_PNMI_RLMT_MODE_CHK_EX */
multiline_comment|/*&n; * OID definition&n; */
macro_line|#ifndef _NDIS_&t;/* Check, whether NDIS already included OIDs */
DECL|macro|OID_GEN_XMIT_OK
mdefine_line|#define OID_GEN_XMIT_OK&t;&t;&t;&t;&t;0x00020101
DECL|macro|OID_GEN_RCV_OK
mdefine_line|#define OID_GEN_RCV_OK&t;&t;&t;&t;&t;0x00020102
DECL|macro|OID_GEN_XMIT_ERROR
mdefine_line|#define OID_GEN_XMIT_ERROR&t;&t;&t;&t;0x00020103
DECL|macro|OID_GEN_RCV_ERROR
mdefine_line|#define OID_GEN_RCV_ERROR&t;&t;&t;&t;0x00020104
DECL|macro|OID_GEN_RCV_NO_BUFFER
mdefine_line|#define OID_GEN_RCV_NO_BUFFER&t;&t;&t;0x00020105
multiline_comment|/* #define OID_GEN_DIRECTED_BYTES_XMIT&t;0x00020201 */
DECL|macro|OID_GEN_DIRECTED_FRAMES_XMIT
mdefine_line|#define OID_GEN_DIRECTED_FRAMES_XMIT&t;0x00020202
multiline_comment|/* #define OID_GEN_MULTICAST_BYTES_XMIT&t;0x00020203 */
DECL|macro|OID_GEN_MULTICAST_FRAMES_XMIT
mdefine_line|#define OID_GEN_MULTICAST_FRAMES_XMIT&t;0x00020204
multiline_comment|/* #define OID_GEN_BROADCAST_BYTES_XMIT&t;0x00020205 */
DECL|macro|OID_GEN_BROADCAST_FRAMES_XMIT
mdefine_line|#define OID_GEN_BROADCAST_FRAMES_XMIT&t;0x00020206
multiline_comment|/* #define OID_GEN_DIRECTED_BYTES_RCV&t;0x00020207 */
DECL|macro|OID_GEN_DIRECTED_FRAMES_RCV
mdefine_line|#define OID_GEN_DIRECTED_FRAMES_RCV&t;&t;0x00020208
multiline_comment|/* #define OID_GEN_MULTICAST_BYTES_RCV&t;0x00020209 */
DECL|macro|OID_GEN_MULTICAST_FRAMES_RCV
mdefine_line|#define OID_GEN_MULTICAST_FRAMES_RCV&t;0x0002020A
multiline_comment|/* #define OID_GEN_BROADCAST_BYTES_RCV&t;0x0002020B */
DECL|macro|OID_GEN_BROADCAST_FRAMES_RCV
mdefine_line|#define OID_GEN_BROADCAST_FRAMES_RCV&t;0x0002020C
DECL|macro|OID_GEN_RCV_CRC_ERROR
mdefine_line|#define OID_GEN_RCV_CRC_ERROR&t;&t;&t;0x0002020D
DECL|macro|OID_GEN_TRANSMIT_QUEUE_LENGTH
mdefine_line|#define OID_GEN_TRANSMIT_QUEUE_LENGTH&t;0x0002020E
DECL|macro|OID_802_3_PERMANENT_ADDRESS
mdefine_line|#define OID_802_3_PERMANENT_ADDRESS&t;&t;0x01010101
DECL|macro|OID_802_3_CURRENT_ADDRESS
mdefine_line|#define OID_802_3_CURRENT_ADDRESS&t;&t;0x01010102
multiline_comment|/* #define OID_802_3_MULTICAST_LIST&t;&t;0x01010103 */
multiline_comment|/* #define OID_802_3_MAXIMUM_LIST_SIZE&t;0x01010104 */
multiline_comment|/* #define OID_802_3_MAC_OPTIONS&t;&t;0x01010105 */
DECL|macro|OID_802_3_RCV_ERROR_ALIGNMENT
mdefine_line|#define OID_802_3_RCV_ERROR_ALIGNMENT&t;0x01020101
DECL|macro|OID_802_3_XMIT_ONE_COLLISION
mdefine_line|#define OID_802_3_XMIT_ONE_COLLISION&t;0x01020102
DECL|macro|OID_802_3_XMIT_MORE_COLLISIONS
mdefine_line|#define OID_802_3_XMIT_MORE_COLLISIONS&t;0x01020103
DECL|macro|OID_802_3_XMIT_DEFERRED
mdefine_line|#define OID_802_3_XMIT_DEFERRED&t;&t;&t;0x01020201
DECL|macro|OID_802_3_XMIT_MAX_COLLISIONS
mdefine_line|#define OID_802_3_XMIT_MAX_COLLISIONS&t;0x01020202
DECL|macro|OID_802_3_RCV_OVERRUN
mdefine_line|#define OID_802_3_RCV_OVERRUN&t;&t;&t;0x01020203
DECL|macro|OID_802_3_XMIT_UNDERRUN
mdefine_line|#define OID_802_3_XMIT_UNDERRUN&t;&t;&t;0x01020204
DECL|macro|OID_802_3_XMIT_TIMES_CRS_LOST
mdefine_line|#define OID_802_3_XMIT_TIMES_CRS_LOST&t;0x01020206
DECL|macro|OID_802_3_XMIT_LATE_COLLISIONS
mdefine_line|#define OID_802_3_XMIT_LATE_COLLISIONS&t;0x01020207
multiline_comment|/*&n; * PnP and PM OIDs&n; */
macro_line|#ifdef SK_POWER_MGMT
DECL|macro|OID_PNP_CAPABILITIES
mdefine_line|#define OID_PNP_CAPABILITIES&t;&t;&t;0xFD010100
DECL|macro|OID_PNP_SET_POWER
mdefine_line|#define OID_PNP_SET_POWER&t;&t;&t;&t;0xFD010101
DECL|macro|OID_PNP_QUERY_POWER
mdefine_line|#define OID_PNP_QUERY_POWER&t;&t;&t;&t;0xFD010102
DECL|macro|OID_PNP_ADD_WAKE_UP_PATTERN
mdefine_line|#define OID_PNP_ADD_WAKE_UP_PATTERN&t;&t;0xFD010103
DECL|macro|OID_PNP_REMOVE_WAKE_UP_PATTERN
mdefine_line|#define OID_PNP_REMOVE_WAKE_UP_PATTERN&t;0xFD010104
DECL|macro|OID_PNP_ENABLE_WAKE_UP
mdefine_line|#define OID_PNP_ENABLE_WAKE_UP&t;&t;&t;0xFD010106
macro_line|#endif /* SK_POWER_MGMT */
macro_line|#endif /* _NDIS_ */
DECL|macro|OID_SKGE_MDB_VERSION
mdefine_line|#define OID_SKGE_MDB_VERSION&t;&t;&t;0xFF010100
DECL|macro|OID_SKGE_SUPPORTED_LIST
mdefine_line|#define OID_SKGE_SUPPORTED_LIST&t;&t;&t;0xFF010101
DECL|macro|OID_SKGE_VPD_FREE_BYTES
mdefine_line|#define OID_SKGE_VPD_FREE_BYTES&t;&t;&t;0xFF010102
DECL|macro|OID_SKGE_VPD_ENTRIES_LIST
mdefine_line|#define OID_SKGE_VPD_ENTRIES_LIST&t;&t;0xFF010103
DECL|macro|OID_SKGE_VPD_ENTRIES_NUMBER
mdefine_line|#define OID_SKGE_VPD_ENTRIES_NUMBER&t;&t;0xFF010104
DECL|macro|OID_SKGE_VPD_KEY
mdefine_line|#define OID_SKGE_VPD_KEY&t;&t;&t;&t;0xFF010105
DECL|macro|OID_SKGE_VPD_VALUE
mdefine_line|#define OID_SKGE_VPD_VALUE&t;&t;&t;&t;0xFF010106
DECL|macro|OID_SKGE_VPD_ACCESS
mdefine_line|#define OID_SKGE_VPD_ACCESS&t;&t;&t;&t;0xFF010107
DECL|macro|OID_SKGE_VPD_ACTION
mdefine_line|#define OID_SKGE_VPD_ACTION&t;&t;&t;&t;0xFF010108
DECL|macro|OID_SKGE_PORT_NUMBER
mdefine_line|#define OID_SKGE_PORT_NUMBER&t;&t;&t;0xFF010110
DECL|macro|OID_SKGE_DEVICE_TYPE
mdefine_line|#define OID_SKGE_DEVICE_TYPE&t;&t;&t;0xFF010111
DECL|macro|OID_SKGE_DRIVER_DESCR
mdefine_line|#define OID_SKGE_DRIVER_DESCR&t;&t;&t;0xFF010112
DECL|macro|OID_SKGE_DRIVER_VERSION
mdefine_line|#define OID_SKGE_DRIVER_VERSION&t;&t;&t;0xFF010113
DECL|macro|OID_SKGE_HW_DESCR
mdefine_line|#define OID_SKGE_HW_DESCR&t;&t;&t;&t;0xFF010114
DECL|macro|OID_SKGE_HW_VERSION
mdefine_line|#define OID_SKGE_HW_VERSION&t;&t;&t;&t;0xFF010115
DECL|macro|OID_SKGE_CHIPSET
mdefine_line|#define OID_SKGE_CHIPSET&t;&t;&t;&t;0xFF010116
DECL|macro|OID_SKGE_ACTION
mdefine_line|#define OID_SKGE_ACTION&t;&t;&t;&t;&t;0xFF010117
DECL|macro|OID_SKGE_RESULT
mdefine_line|#define OID_SKGE_RESULT&t;&t;&t;&t;&t;0xFF010118
DECL|macro|OID_SKGE_BUS_TYPE
mdefine_line|#define OID_SKGE_BUS_TYPE&t;&t;&t;&t;0xFF010119
DECL|macro|OID_SKGE_BUS_SPEED
mdefine_line|#define OID_SKGE_BUS_SPEED&t;&t;&t;&t;0xFF01011A
DECL|macro|OID_SKGE_BUS_WIDTH
mdefine_line|#define OID_SKGE_BUS_WIDTH&t;&t;&t;&t;0xFF01011B
multiline_comment|/* 0xFF01011C unused */
DECL|macro|OID_SKGE_DIAG_ACTION
mdefine_line|#define OID_SKGE_DIAG_ACTION&t;&t;&t;0xFF01011D
DECL|macro|OID_SKGE_DIAG_RESULT
mdefine_line|#define OID_SKGE_DIAG_RESULT&t;&t;&t;0xFF01011E
DECL|macro|OID_SKGE_MTU
mdefine_line|#define OID_SKGE_MTU&t;&t;&t;&t;&t;0xFF01011F
DECL|macro|OID_SKGE_PHYS_CUR_ADDR
mdefine_line|#define OID_SKGE_PHYS_CUR_ADDR&t;&t;&t;0xFF010120
DECL|macro|OID_SKGE_PHYS_FAC_ADDR
mdefine_line|#define OID_SKGE_PHYS_FAC_ADDR&t;&t;&t;0xFF010121
DECL|macro|OID_SKGE_PMD
mdefine_line|#define OID_SKGE_PMD&t;&t;&t;&t;&t;0xFF010122
DECL|macro|OID_SKGE_CONNECTOR
mdefine_line|#define OID_SKGE_CONNECTOR&t;&t;&t;&t;0xFF010123
DECL|macro|OID_SKGE_LINK_CAP
mdefine_line|#define OID_SKGE_LINK_CAP&t;&t;&t;&t;0xFF010124
DECL|macro|OID_SKGE_LINK_MODE
mdefine_line|#define OID_SKGE_LINK_MODE&t;&t;&t;&t;0xFF010125
DECL|macro|OID_SKGE_LINK_MODE_STATUS
mdefine_line|#define OID_SKGE_LINK_MODE_STATUS&t;&t;0xFF010126
DECL|macro|OID_SKGE_LINK_STATUS
mdefine_line|#define OID_SKGE_LINK_STATUS&t;&t;&t;0xFF010127
DECL|macro|OID_SKGE_FLOWCTRL_CAP
mdefine_line|#define OID_SKGE_FLOWCTRL_CAP&t;&t;&t;0xFF010128
DECL|macro|OID_SKGE_FLOWCTRL_MODE
mdefine_line|#define OID_SKGE_FLOWCTRL_MODE&t;&t;&t;0xFF010129
DECL|macro|OID_SKGE_FLOWCTRL_STATUS
mdefine_line|#define OID_SKGE_FLOWCTRL_STATUS&t;&t;0xFF01012A
DECL|macro|OID_SKGE_PHY_OPERATION_CAP
mdefine_line|#define OID_SKGE_PHY_OPERATION_CAP&t;&t;0xFF01012B
DECL|macro|OID_SKGE_PHY_OPERATION_MODE
mdefine_line|#define OID_SKGE_PHY_OPERATION_MODE&t;&t;0xFF01012C
DECL|macro|OID_SKGE_PHY_OPERATION_STATUS
mdefine_line|#define OID_SKGE_PHY_OPERATION_STATUS&t;0xFF01012D
DECL|macro|OID_SKGE_MULTICAST_LIST
mdefine_line|#define OID_SKGE_MULTICAST_LIST&t;&t;&t;0xFF01012E
DECL|macro|OID_SKGE_CURRENT_PACKET_FILTER
mdefine_line|#define OID_SKGE_CURRENT_PACKET_FILTER&t;0xFF01012F
DECL|macro|OID_SKGE_TRAP
mdefine_line|#define OID_SKGE_TRAP&t;&t;&t;&t;&t;0xFF010130
DECL|macro|OID_SKGE_TRAP_NUMBER
mdefine_line|#define OID_SKGE_TRAP_NUMBER&t;&t;&t;0xFF010131
DECL|macro|OID_SKGE_RLMT_MODE
mdefine_line|#define OID_SKGE_RLMT_MODE&t;&t;&t;&t;0xFF010140
DECL|macro|OID_SKGE_RLMT_PORT_NUMBER
mdefine_line|#define OID_SKGE_RLMT_PORT_NUMBER&t;&t;0xFF010141
DECL|macro|OID_SKGE_RLMT_PORT_ACTIVE
mdefine_line|#define OID_SKGE_RLMT_PORT_ACTIVE&t;&t;0xFF010142
DECL|macro|OID_SKGE_RLMT_PORT_PREFERRED
mdefine_line|#define OID_SKGE_RLMT_PORT_PREFERRED&t;0xFF010143
DECL|macro|OID_SKGE_INTERMEDIATE_SUPPORT
mdefine_line|#define OID_SKGE_INTERMEDIATE_SUPPORT&t;0xFF010160
DECL|macro|OID_SKGE_SPEED_CAP
mdefine_line|#define OID_SKGE_SPEED_CAP&t;&t;&t;&t;0xFF010170
DECL|macro|OID_SKGE_SPEED_MODE
mdefine_line|#define OID_SKGE_SPEED_MODE&t;&t;&t;&t;0xFF010171
DECL|macro|OID_SKGE_SPEED_STATUS
mdefine_line|#define OID_SKGE_SPEED_STATUS&t;&t;&t;0xFF010172
DECL|macro|OID_SKGE_BOARDLEVEL
mdefine_line|#define OID_SKGE_BOARDLEVEL&t;&t;&t;&t;0xFF010180
DECL|macro|OID_SKGE_SENSOR_NUMBER
mdefine_line|#define OID_SKGE_SENSOR_NUMBER&t;&t;&t;0xFF020100&t;&t;&t;
DECL|macro|OID_SKGE_SENSOR_INDEX
mdefine_line|#define OID_SKGE_SENSOR_INDEX&t;&t;&t;0xFF020101
DECL|macro|OID_SKGE_SENSOR_DESCR
mdefine_line|#define OID_SKGE_SENSOR_DESCR&t;&t;&t;0xFF020102
DECL|macro|OID_SKGE_SENSOR_TYPE
mdefine_line|#define OID_SKGE_SENSOR_TYPE&t;&t;&t;0xFF020103
DECL|macro|OID_SKGE_SENSOR_VALUE
mdefine_line|#define OID_SKGE_SENSOR_VALUE&t;&t;&t;0xFF020104
DECL|macro|OID_SKGE_SENSOR_WAR_THRES_LOW
mdefine_line|#define OID_SKGE_SENSOR_WAR_THRES_LOW&t;0xFF020105
DECL|macro|OID_SKGE_SENSOR_WAR_THRES_UPP
mdefine_line|#define OID_SKGE_SENSOR_WAR_THRES_UPP&t;0xFF020106
DECL|macro|OID_SKGE_SENSOR_ERR_THRES_LOW
mdefine_line|#define OID_SKGE_SENSOR_ERR_THRES_LOW&t;0xFF020107
DECL|macro|OID_SKGE_SENSOR_ERR_THRES_UPP
mdefine_line|#define OID_SKGE_SENSOR_ERR_THRES_UPP&t;0xFF020108
DECL|macro|OID_SKGE_SENSOR_STATUS
mdefine_line|#define OID_SKGE_SENSOR_STATUS&t;&t;&t;0xFF020109
DECL|macro|OID_SKGE_SENSOR_WAR_CTS
mdefine_line|#define OID_SKGE_SENSOR_WAR_CTS&t;&t;&t;0xFF02010A
DECL|macro|OID_SKGE_SENSOR_ERR_CTS
mdefine_line|#define OID_SKGE_SENSOR_ERR_CTS&t;&t;&t;0xFF02010B
DECL|macro|OID_SKGE_SENSOR_WAR_TIME
mdefine_line|#define OID_SKGE_SENSOR_WAR_TIME&t;&t;0xFF02010C
DECL|macro|OID_SKGE_SENSOR_ERR_TIME
mdefine_line|#define OID_SKGE_SENSOR_ERR_TIME&t;&t;0xFF02010D
DECL|macro|OID_SKGE_CHKSM_NUMBER
mdefine_line|#define OID_SKGE_CHKSM_NUMBER&t;&t;&t;0xFF020110
DECL|macro|OID_SKGE_CHKSM_RX_OK_CTS
mdefine_line|#define OID_SKGE_CHKSM_RX_OK_CTS&t;&t;0xFF020111
DECL|macro|OID_SKGE_CHKSM_RX_UNABLE_CTS
mdefine_line|#define OID_SKGE_CHKSM_RX_UNABLE_CTS&t;0xFF020112
DECL|macro|OID_SKGE_CHKSM_RX_ERR_CTS
mdefine_line|#define OID_SKGE_CHKSM_RX_ERR_CTS&t;&t;0xFF020113
DECL|macro|OID_SKGE_CHKSM_TX_OK_CTS
mdefine_line|#define OID_SKGE_CHKSM_TX_OK_CTS&t;&t;0xFF020114
DECL|macro|OID_SKGE_CHKSM_TX_UNABLE_CTS
mdefine_line|#define OID_SKGE_CHKSM_TX_UNABLE_CTS&t;0xFF020115
DECL|macro|OID_SKGE_STAT_TX
mdefine_line|#define OID_SKGE_STAT_TX&t;&t;&t;&t;0xFF020120
DECL|macro|OID_SKGE_STAT_TX_OCTETS
mdefine_line|#define OID_SKGE_STAT_TX_OCTETS&t;&t;&t;0xFF020121
DECL|macro|OID_SKGE_STAT_TX_BROADCAST
mdefine_line|#define OID_SKGE_STAT_TX_BROADCAST&t;&t;0xFF020122
DECL|macro|OID_SKGE_STAT_TX_MULTICAST
mdefine_line|#define OID_SKGE_STAT_TX_MULTICAST&t;&t;0xFF020123
DECL|macro|OID_SKGE_STAT_TX_UNICAST
mdefine_line|#define OID_SKGE_STAT_TX_UNICAST&t;&t;0xFF020124
DECL|macro|OID_SKGE_STAT_TX_LONGFRAMES
mdefine_line|#define OID_SKGE_STAT_TX_LONGFRAMES&t;&t;0xFF020125
DECL|macro|OID_SKGE_STAT_TX_BURST
mdefine_line|#define OID_SKGE_STAT_TX_BURST&t;&t;&t;0xFF020126
DECL|macro|OID_SKGE_STAT_TX_PFLOWC
mdefine_line|#define OID_SKGE_STAT_TX_PFLOWC&t;&t;&t;0xFF020127
DECL|macro|OID_SKGE_STAT_TX_FLOWC
mdefine_line|#define OID_SKGE_STAT_TX_FLOWC&t;&t;&t;0xFF020128
DECL|macro|OID_SKGE_STAT_TX_SINGLE_COL
mdefine_line|#define OID_SKGE_STAT_TX_SINGLE_COL&t;&t;0xFF020129
DECL|macro|OID_SKGE_STAT_TX_MULTI_COL
mdefine_line|#define OID_SKGE_STAT_TX_MULTI_COL&t;&t;0xFF02012A
DECL|macro|OID_SKGE_STAT_TX_EXCESS_COL
mdefine_line|#define OID_SKGE_STAT_TX_EXCESS_COL&t;&t;0xFF02012B
DECL|macro|OID_SKGE_STAT_TX_LATE_COL
mdefine_line|#define OID_SKGE_STAT_TX_LATE_COL&t;&t;0xFF02012C
DECL|macro|OID_SKGE_STAT_TX_DEFFERAL
mdefine_line|#define OID_SKGE_STAT_TX_DEFFERAL&t;&t;0xFF02012D
DECL|macro|OID_SKGE_STAT_TX_EXCESS_DEF
mdefine_line|#define OID_SKGE_STAT_TX_EXCESS_DEF&t;&t;0xFF02012E
DECL|macro|OID_SKGE_STAT_TX_UNDERRUN
mdefine_line|#define OID_SKGE_STAT_TX_UNDERRUN&t;&t;0xFF02012F
DECL|macro|OID_SKGE_STAT_TX_CARRIER
mdefine_line|#define OID_SKGE_STAT_TX_CARRIER&t;&t;0xFF020130
multiline_comment|/* #define OID_SKGE_STAT_TX_UTIL&t;&t;0xFF020131 */
DECL|macro|OID_SKGE_STAT_TX_64
mdefine_line|#define OID_SKGE_STAT_TX_64&t;&t;&t;&t;0xFF020132
DECL|macro|OID_SKGE_STAT_TX_127
mdefine_line|#define OID_SKGE_STAT_TX_127&t;&t;&t;0xFF020133
DECL|macro|OID_SKGE_STAT_TX_255
mdefine_line|#define OID_SKGE_STAT_TX_255&t;&t;&t;0xFF020134
DECL|macro|OID_SKGE_STAT_TX_511
mdefine_line|#define OID_SKGE_STAT_TX_511&t;&t;&t;0xFF020135
DECL|macro|OID_SKGE_STAT_TX_1023
mdefine_line|#define OID_SKGE_STAT_TX_1023&t;&t;&t;0xFF020136
DECL|macro|OID_SKGE_STAT_TX_MAX
mdefine_line|#define OID_SKGE_STAT_TX_MAX&t;&t;&t;0xFF020137
DECL|macro|OID_SKGE_STAT_TX_SYNC
mdefine_line|#define OID_SKGE_STAT_TX_SYNC&t;&t;&t;0xFF020138
DECL|macro|OID_SKGE_STAT_TX_SYNC_OCTETS
mdefine_line|#define OID_SKGE_STAT_TX_SYNC_OCTETS&t;0xFF020139
DECL|macro|OID_SKGE_STAT_RX
mdefine_line|#define OID_SKGE_STAT_RX&t;&t;&t;&t;0xFF02013A
DECL|macro|OID_SKGE_STAT_RX_OCTETS
mdefine_line|#define OID_SKGE_STAT_RX_OCTETS&t;&t;&t;0xFF02013B
DECL|macro|OID_SKGE_STAT_RX_BROADCAST
mdefine_line|#define OID_SKGE_STAT_RX_BROADCAST&t;&t;0xFF02013C
DECL|macro|OID_SKGE_STAT_RX_MULTICAST
mdefine_line|#define OID_SKGE_STAT_RX_MULTICAST&t;&t;0xFF02013D
DECL|macro|OID_SKGE_STAT_RX_UNICAST
mdefine_line|#define OID_SKGE_STAT_RX_UNICAST&t;&t;0xFF02013E
DECL|macro|OID_SKGE_STAT_RX_PFLOWC
mdefine_line|#define OID_SKGE_STAT_RX_PFLOWC&t;&t;&t;0xFF02013F
DECL|macro|OID_SKGE_STAT_RX_FLOWC
mdefine_line|#define OID_SKGE_STAT_RX_FLOWC&t;&t;&t;0xFF020140
DECL|macro|OID_SKGE_STAT_RX_PFLOWC_ERR
mdefine_line|#define OID_SKGE_STAT_RX_PFLOWC_ERR&t;&t;0xFF020141
DECL|macro|OID_SKGE_STAT_RX_FLOWC_UNKWN
mdefine_line|#define OID_SKGE_STAT_RX_FLOWC_UNKWN&t;0xFF020142
DECL|macro|OID_SKGE_STAT_RX_BURST
mdefine_line|#define OID_SKGE_STAT_RX_BURST&t;&t;&t;0xFF020143
DECL|macro|OID_SKGE_STAT_RX_MISSED
mdefine_line|#define OID_SKGE_STAT_RX_MISSED&t;&t;&t;0xFF020144
DECL|macro|OID_SKGE_STAT_RX_FRAMING
mdefine_line|#define OID_SKGE_STAT_RX_FRAMING&t;&t;0xFF020145
DECL|macro|OID_SKGE_STAT_RX_OVERFLOW
mdefine_line|#define OID_SKGE_STAT_RX_OVERFLOW&t;&t;0xFF020146
DECL|macro|OID_SKGE_STAT_RX_JABBER
mdefine_line|#define OID_SKGE_STAT_RX_JABBER&t;&t;&t;0xFF020147
DECL|macro|OID_SKGE_STAT_RX_CARRIER
mdefine_line|#define OID_SKGE_STAT_RX_CARRIER&t;&t;0xFF020148
DECL|macro|OID_SKGE_STAT_RX_IR_LENGTH
mdefine_line|#define OID_SKGE_STAT_RX_IR_LENGTH&t;&t;0xFF020149
DECL|macro|OID_SKGE_STAT_RX_SYMBOL
mdefine_line|#define OID_SKGE_STAT_RX_SYMBOL&t;&t;&t;0xFF02014A
DECL|macro|OID_SKGE_STAT_RX_SHORTS
mdefine_line|#define OID_SKGE_STAT_RX_SHORTS&t;&t;&t;0xFF02014B
DECL|macro|OID_SKGE_STAT_RX_RUNT
mdefine_line|#define OID_SKGE_STAT_RX_RUNT&t;&t;&t;0xFF02014C
DECL|macro|OID_SKGE_STAT_RX_CEXT
mdefine_line|#define OID_SKGE_STAT_RX_CEXT&t;&t;&t;0xFF02014D
DECL|macro|OID_SKGE_STAT_RX_TOO_LONG
mdefine_line|#define OID_SKGE_STAT_RX_TOO_LONG&t;&t;0xFF02014E
DECL|macro|OID_SKGE_STAT_RX_FCS
mdefine_line|#define OID_SKGE_STAT_RX_FCS&t;&t;&t;0xFF02014F
multiline_comment|/* #define OID_SKGE_STAT_RX_UTIL&t;&t;0xFF020150 */
DECL|macro|OID_SKGE_STAT_RX_64
mdefine_line|#define OID_SKGE_STAT_RX_64&t;&t;&t;&t;0xFF020151
DECL|macro|OID_SKGE_STAT_RX_127
mdefine_line|#define OID_SKGE_STAT_RX_127&t;&t;&t;0xFF020152
DECL|macro|OID_SKGE_STAT_RX_255
mdefine_line|#define OID_SKGE_STAT_RX_255&t;&t;&t;0xFF020153
DECL|macro|OID_SKGE_STAT_RX_511
mdefine_line|#define OID_SKGE_STAT_RX_511&t;&t;&t;0xFF020154
DECL|macro|OID_SKGE_STAT_RX_1023
mdefine_line|#define OID_SKGE_STAT_RX_1023&t;&t;&t;0xFF020155
DECL|macro|OID_SKGE_STAT_RX_MAX
mdefine_line|#define OID_SKGE_STAT_RX_MAX&t;&t;&t;0xFF020156
DECL|macro|OID_SKGE_STAT_RX_LONGFRAMES
mdefine_line|#define OID_SKGE_STAT_RX_LONGFRAMES&t;&t;0xFF020157
DECL|macro|OID_SKGE_RLMT_CHANGE_CTS
mdefine_line|#define OID_SKGE_RLMT_CHANGE_CTS&t;&t;0xFF020160
DECL|macro|OID_SKGE_RLMT_CHANGE_TIME
mdefine_line|#define OID_SKGE_RLMT_CHANGE_TIME&t;&t;0xFF020161
DECL|macro|OID_SKGE_RLMT_CHANGE_ESTIM
mdefine_line|#define OID_SKGE_RLMT_CHANGE_ESTIM&t;&t;0xFF020162
DECL|macro|OID_SKGE_RLMT_CHANGE_THRES
mdefine_line|#define OID_SKGE_RLMT_CHANGE_THRES&t;&t;0xFF020163
DECL|macro|OID_SKGE_RLMT_PORT_INDEX
mdefine_line|#define OID_SKGE_RLMT_PORT_INDEX&t;&t;0xFF020164
DECL|macro|OID_SKGE_RLMT_STATUS
mdefine_line|#define OID_SKGE_RLMT_STATUS&t;&t;&t;0xFF020165
DECL|macro|OID_SKGE_RLMT_TX_HELLO_CTS
mdefine_line|#define OID_SKGE_RLMT_TX_HELLO_CTS&t;&t;0xFF020166
DECL|macro|OID_SKGE_RLMT_RX_HELLO_CTS
mdefine_line|#define OID_SKGE_RLMT_RX_HELLO_CTS&t;&t;0xFF020167
DECL|macro|OID_SKGE_RLMT_TX_SP_REQ_CTS
mdefine_line|#define OID_SKGE_RLMT_TX_SP_REQ_CTS&t;&t;0xFF020168
DECL|macro|OID_SKGE_RLMT_RX_SP_CTS
mdefine_line|#define OID_SKGE_RLMT_RX_SP_CTS&t;&t;&t;0xFF020169
DECL|macro|OID_SKGE_RLMT_MONITOR_NUMBER
mdefine_line|#define OID_SKGE_RLMT_MONITOR_NUMBER&t;0xFF010150
DECL|macro|OID_SKGE_RLMT_MONITOR_INDEX
mdefine_line|#define OID_SKGE_RLMT_MONITOR_INDEX&t;&t;0xFF010151
DECL|macro|OID_SKGE_RLMT_MONITOR_ADDR
mdefine_line|#define OID_SKGE_RLMT_MONITOR_ADDR&t;&t;0xFF010152
DECL|macro|OID_SKGE_RLMT_MONITOR_ERRS
mdefine_line|#define OID_SKGE_RLMT_MONITOR_ERRS&t;&t;0xFF010153
DECL|macro|OID_SKGE_RLMT_MONITOR_TIMESTAMP
mdefine_line|#define OID_SKGE_RLMT_MONITOR_TIMESTAMP&t;0xFF010154
DECL|macro|OID_SKGE_RLMT_MONITOR_ADMIN
mdefine_line|#define OID_SKGE_RLMT_MONITOR_ADMIN&t;&t;0xFF010155
DECL|macro|OID_SKGE_TX_SW_QUEUE_LEN
mdefine_line|#define OID_SKGE_TX_SW_QUEUE_LEN&t;&t;0xFF020170
DECL|macro|OID_SKGE_TX_SW_QUEUE_MAX
mdefine_line|#define OID_SKGE_TX_SW_QUEUE_MAX&t;&t;0xFF020171
DECL|macro|OID_SKGE_TX_RETRY
mdefine_line|#define OID_SKGE_TX_RETRY&t;&t;&t;&t;0xFF020172
DECL|macro|OID_SKGE_RX_INTR_CTS
mdefine_line|#define OID_SKGE_RX_INTR_CTS&t;&t;&t;0xFF020173
DECL|macro|OID_SKGE_TX_INTR_CTS
mdefine_line|#define OID_SKGE_TX_INTR_CTS&t;&t;&t;0xFF020174
DECL|macro|OID_SKGE_RX_NO_BUF_CTS
mdefine_line|#define OID_SKGE_RX_NO_BUF_CTS&t;&t;&t;0xFF020175
DECL|macro|OID_SKGE_TX_NO_BUF_CTS
mdefine_line|#define OID_SKGE_TX_NO_BUF_CTS&t;&t;&t;0xFF020176
DECL|macro|OID_SKGE_TX_USED_DESCR_NO
mdefine_line|#define OID_SKGE_TX_USED_DESCR_NO&t;&t;0xFF020177
DECL|macro|OID_SKGE_RX_DELIVERED_CTS
mdefine_line|#define OID_SKGE_RX_DELIVERED_CTS&t;&t;0xFF020178
DECL|macro|OID_SKGE_RX_OCTETS_DELIV_CTS
mdefine_line|#define OID_SKGE_RX_OCTETS_DELIV_CTS&t;0xFF020179
DECL|macro|OID_SKGE_RX_HW_ERROR_CTS
mdefine_line|#define OID_SKGE_RX_HW_ERROR_CTS&t;&t;0xFF02017A
DECL|macro|OID_SKGE_TX_HW_ERROR_CTS
mdefine_line|#define OID_SKGE_TX_HW_ERROR_CTS&t;&t;0xFF02017B
DECL|macro|OID_SKGE_IN_ERRORS_CTS
mdefine_line|#define OID_SKGE_IN_ERRORS_CTS&t;&t;&t;0xFF02017C
DECL|macro|OID_SKGE_OUT_ERROR_CTS
mdefine_line|#define OID_SKGE_OUT_ERROR_CTS&t;&t;&t;0xFF02017D
DECL|macro|OID_SKGE_ERR_RECOVERY_CTS
mdefine_line|#define OID_SKGE_ERR_RECOVERY_CTS&t;&t;0xFF02017E
DECL|macro|OID_SKGE_SYSUPTIME
mdefine_line|#define OID_SKGE_SYSUPTIME&t;&t;&t;&t;0xFF02017F
DECL|macro|OID_SKGE_ALL_DATA
mdefine_line|#define OID_SKGE_ALL_DATA&t;&t;&t;&t;0xFF020190
multiline_comment|/* Defines for VCT. */
DECL|macro|OID_SKGE_VCT_GET
mdefine_line|#define OID_SKGE_VCT_GET&t;&t;&t;&t;0xFF020200
DECL|macro|OID_SKGE_VCT_SET
mdefine_line|#define OID_SKGE_VCT_SET&t;&t;&t;&t;0xFF020201
DECL|macro|OID_SKGE_VCT_STATUS
mdefine_line|#define OID_SKGE_VCT_STATUS&t;&t;&t;&t;0xFF020202
macro_line|#ifdef SK_DIAG_SUPPORT
multiline_comment|/* Defines for driver DIAG mode. */
DECL|macro|OID_SKGE_DIAG_MODE
mdefine_line|#define OID_SKGE_DIAG_MODE&t;&t;&t;&t;0xFF020204
macro_line|#endif /* SK_DIAG_SUPPORT */
multiline_comment|/* New OIDs */
DECL|macro|OID_SKGE_DRIVER_RELDATE
mdefine_line|#define OID_SKGE_DRIVER_RELDATE&t;&t;&t;0xFF020210
DECL|macro|OID_SKGE_DRIVER_FILENAME
mdefine_line|#define OID_SKGE_DRIVER_FILENAME&t;&t;0xFF020211
DECL|macro|OID_SKGE_CHIPID
mdefine_line|#define OID_SKGE_CHIPID&t;&t;&t;&t;&t;0xFF020212
DECL|macro|OID_SKGE_RAMSIZE
mdefine_line|#define OID_SKGE_RAMSIZE&t;&t;&t;&t;0xFF020213
DECL|macro|OID_SKGE_VAUXAVAIL
mdefine_line|#define OID_SKGE_VAUXAVAIL&t;&t;&t;&t;0xFF020214
DECL|macro|OID_SKGE_PHY_TYPE
mdefine_line|#define OID_SKGE_PHY_TYPE&t;&t;&t;&t;0xFF020215
DECL|macro|OID_SKGE_PHY_LP_MODE
mdefine_line|#define OID_SKGE_PHY_LP_MODE&t;&t;&t;0xFF020216
multiline_comment|/* VCT struct to store a backup copy of VCT data after a port reset. */
DECL|struct|s_PnmiVct
r_typedef
r_struct
id|s_PnmiVct
(brace
DECL|member|VctStatus
id|SK_U8
id|VctStatus
suffix:semicolon
DECL|member|PCableLen
id|SK_U8
id|PCableLen
suffix:semicolon
DECL|member|PMdiPairLen
id|SK_U32
id|PMdiPairLen
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|PMdiPairSts
id|SK_U8
id|PMdiPairSts
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|SK_PNMI_VCT
)brace
id|SK_PNMI_VCT
suffix:semicolon
multiline_comment|/* VCT status values (to be given to CPA via OID_SKGE_VCT_STATUS). */
DECL|macro|SK_PNMI_VCT_NONE
mdefine_line|#define SK_PNMI_VCT_NONE&t;&t;0
DECL|macro|SK_PNMI_VCT_OLD_VCT_DATA
mdefine_line|#define SK_PNMI_VCT_OLD_VCT_DATA&t;1
DECL|macro|SK_PNMI_VCT_NEW_VCT_DATA
mdefine_line|#define SK_PNMI_VCT_NEW_VCT_DATA&t;2
DECL|macro|SK_PNMI_VCT_OLD_DSP_DATA
mdefine_line|#define SK_PNMI_VCT_OLD_DSP_DATA&t;4
DECL|macro|SK_PNMI_VCT_NEW_DSP_DATA
mdefine_line|#define SK_PNMI_VCT_NEW_DSP_DATA&t;8
DECL|macro|SK_PNMI_VCT_RUNNING
mdefine_line|#define SK_PNMI_VCT_RUNNING&t;&t;16
multiline_comment|/* VCT cable test status. */
DECL|macro|SK_PNMI_VCT_NORMAL_CABLE
mdefine_line|#define SK_PNMI_VCT_NORMAL_CABLE&t;&t;0
DECL|macro|SK_PNMI_VCT_SHORT_CABLE
mdefine_line|#define SK_PNMI_VCT_SHORT_CABLE&t;&t;&t;1
DECL|macro|SK_PNMI_VCT_OPEN_CABLE
mdefine_line|#define SK_PNMI_VCT_OPEN_CABLE&t;&t;&t;2
DECL|macro|SK_PNMI_VCT_TEST_FAIL
mdefine_line|#define SK_PNMI_VCT_TEST_FAIL&t;&t;&t;3
DECL|macro|SK_PNMI_VCT_IMPEDANCE_MISMATCH
mdefine_line|#define SK_PNMI_VCT_IMPEDANCE_MISMATCH&t;&t;4
DECL|macro|OID_SKGE_TRAP_SEN_WAR_LOW
mdefine_line|#define&t;OID_SKGE_TRAP_SEN_WAR_LOW&t;&t;500
DECL|macro|OID_SKGE_TRAP_SEN_WAR_UPP
mdefine_line|#define OID_SKGE_TRAP_SEN_WAR_UPP&t;&t;501
DECL|macro|OID_SKGE_TRAP_SEN_ERR_LOW
mdefine_line|#define&t;OID_SKGE_TRAP_SEN_ERR_LOW&t;&t;502
DECL|macro|OID_SKGE_TRAP_SEN_ERR_UPP
mdefine_line|#define OID_SKGE_TRAP_SEN_ERR_UPP&t;&t;503
DECL|macro|OID_SKGE_TRAP_RLMT_CHANGE_THRES
mdefine_line|#define OID_SKGE_TRAP_RLMT_CHANGE_THRES&t;520
DECL|macro|OID_SKGE_TRAP_RLMT_CHANGE_PORT
mdefine_line|#define OID_SKGE_TRAP_RLMT_CHANGE_PORT&t;521
DECL|macro|OID_SKGE_TRAP_RLMT_PORT_DOWN
mdefine_line|#define OID_SKGE_TRAP_RLMT_PORT_DOWN&t;522
DECL|macro|OID_SKGE_TRAP_RLMT_PORT_UP
mdefine_line|#define OID_SKGE_TRAP_RLMT_PORT_UP&t;&t;523
DECL|macro|OID_SKGE_TRAP_RLMT_SEGMENTATION
mdefine_line|#define OID_SKGE_TRAP_RLMT_SEGMENTATION&t;524
macro_line|#ifdef SK_DIAG_SUPPORT
multiline_comment|/* Defines for driver DIAG mode. */
DECL|macro|SK_DIAG_ATTACHED
mdefine_line|#define SK_DIAG_ATTACHED&t;2
DECL|macro|SK_DIAG_RUNNING
mdefine_line|#define SK_DIAG_RUNNING&t;&t;1
DECL|macro|SK_DIAG_IDLE
mdefine_line|#define SK_DIAG_IDLE&t;&t;0
macro_line|#endif /* SK_DIAG_SUPPORT */
multiline_comment|/*&n; * Generic PNMI IOCTL subcommand definitions.&n; */
DECL|macro|SK_GET_SINGLE_VAR
mdefine_line|#define&t;SK_GET_SINGLE_VAR&t;&t;1
DECL|macro|SK_SET_SINGLE_VAR
mdefine_line|#define&t;SK_SET_SINGLE_VAR&t;&t;2
DECL|macro|SK_PRESET_SINGLE_VAR
mdefine_line|#define&t;SK_PRESET_SINGLE_VAR&t;3
DECL|macro|SK_GET_FULL_MIB
mdefine_line|#define&t;SK_GET_FULL_MIB&t;&t;&t;4
DECL|macro|SK_SET_FULL_MIB
mdefine_line|#define&t;SK_SET_FULL_MIB&t;&t;&t;5
DECL|macro|SK_PRESET_FULL_MIB
mdefine_line|#define&t;SK_PRESET_FULL_MIB&t;&t;6
multiline_comment|/*&n; * Define error numbers and messages for syslog&n; */
DECL|macro|SK_PNMI_ERR001
mdefine_line|#define SK_PNMI_ERR001&t;&t;(SK_ERRBASE_PNMI + 1)
DECL|macro|SK_PNMI_ERR001MSG
mdefine_line|#define SK_PNMI_ERR001MSG&t;&quot;SkPnmiGetStruct: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR002
mdefine_line|#define SK_PNMI_ERR002&t;&t;(SK_ERRBASE_PNMI + 2)
DECL|macro|SK_PNMI_ERR002MSG
mdefine_line|#define SK_PNMI_ERR002MSG&t;&quot;SkPnmiGetStruct: Cannot read VPD keys&quot;
DECL|macro|SK_PNMI_ERR003
mdefine_line|#define SK_PNMI_ERR003&t;&t;(SK_ERRBASE_PNMI + 3)
DECL|macro|SK_PNMI_ERR003MSG
mdefine_line|#define SK_PNMI_ERR003MSG&t;&quot;OidStruct: Called with wrong OID&quot;
DECL|macro|SK_PNMI_ERR004
mdefine_line|#define SK_PNMI_ERR004&t;&t;(SK_ERRBASE_PNMI + 4)
DECL|macro|SK_PNMI_ERR004MSG
mdefine_line|#define SK_PNMI_ERR004MSG&t;&quot;OidStruct: Called with wrong action&quot;
DECL|macro|SK_PNMI_ERR005
mdefine_line|#define SK_PNMI_ERR005&t;&t;(SK_ERRBASE_PNMI + 5)
DECL|macro|SK_PNMI_ERR005MSG
mdefine_line|#define SK_PNMI_ERR005MSG&t;&quot;Perform: Cannot reset driver&quot;
DECL|macro|SK_PNMI_ERR006
mdefine_line|#define SK_PNMI_ERR006&t;&t;(SK_ERRBASE_PNMI + 6)
DECL|macro|SK_PNMI_ERR006MSG
mdefine_line|#define SK_PNMI_ERR006MSG&t;&quot;Perform: Unknown OID action command&quot;
DECL|macro|SK_PNMI_ERR007
mdefine_line|#define SK_PNMI_ERR007&t;&t;(SK_ERRBASE_PNMI + 7)
DECL|macro|SK_PNMI_ERR007MSG
mdefine_line|#define SK_PNMI_ERR007MSG&t;&quot;General: Driver description not initialized&quot;
DECL|macro|SK_PNMI_ERR008
mdefine_line|#define SK_PNMI_ERR008&t;&t;(SK_ERRBASE_PNMI + 8)
DECL|macro|SK_PNMI_ERR008MSG
mdefine_line|#define SK_PNMI_ERR008MSG&t;&quot;Addr: Tried to get unknown OID&quot;
DECL|macro|SK_PNMI_ERR009
mdefine_line|#define SK_PNMI_ERR009&t;&t;(SK_ERRBASE_PNMI + 9)
DECL|macro|SK_PNMI_ERR009MSG
mdefine_line|#define SK_PNMI_ERR009MSG&t;&quot;Addr: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR010
mdefine_line|#define SK_PNMI_ERR010&t;&t;(SK_ERRBASE_PNMI + 10)
DECL|macro|SK_PNMI_ERR010MSG
mdefine_line|#define SK_PNMI_ERR010MSG&t;&quot;CsumStat: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR011
mdefine_line|#define SK_PNMI_ERR011&t;&t;(SK_ERRBASE_PNMI + 11)
DECL|macro|SK_PNMI_ERR011MSG
mdefine_line|#define SK_PNMI_ERR011MSG&t;&quot;SensorStat: Sensor descr string too long&quot;
DECL|macro|SK_PNMI_ERR012
mdefine_line|#define SK_PNMI_ERR012&t;&t;(SK_ERRBASE_PNMI + 12)
DECL|macro|SK_PNMI_ERR012MSG
mdefine_line|#define SK_PNMI_ERR012MSG&t;&quot;SensorStat: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR013
mdefine_line|#define SK_PNMI_ERR013&t;&t;(SK_ERRBASE_PNMI + 13)
DECL|macro|SK_PNMI_ERR013MSG
mdefine_line|#define SK_PNMI_ERR013MSG&t;&quot;&quot;
DECL|macro|SK_PNMI_ERR014
mdefine_line|#define SK_PNMI_ERR014&t;&t;(SK_ERRBASE_PNMI + 14)
DECL|macro|SK_PNMI_ERR014MSG
mdefine_line|#define SK_PNMI_ERR014MSG&t;&quot;Vpd: Cannot read VPD keys&quot;
DECL|macro|SK_PNMI_ERR015
mdefine_line|#define SK_PNMI_ERR015&t;&t;(SK_ERRBASE_PNMI + 15)
DECL|macro|SK_PNMI_ERR015MSG
mdefine_line|#define SK_PNMI_ERR015MSG&t;&quot;Vpd: Internal array for VPD keys to small&quot;
DECL|macro|SK_PNMI_ERR016
mdefine_line|#define SK_PNMI_ERR016&t;&t;(SK_ERRBASE_PNMI + 16)
DECL|macro|SK_PNMI_ERR016MSG
mdefine_line|#define SK_PNMI_ERR016MSG&t;&quot;Vpd: Key string too long&quot;
DECL|macro|SK_PNMI_ERR017
mdefine_line|#define SK_PNMI_ERR017&t;&t;(SK_ERRBASE_PNMI + 17)
DECL|macro|SK_PNMI_ERR017MSG
mdefine_line|#define SK_PNMI_ERR017MSG&t;&quot;Vpd: Invalid VPD status pointer&quot;
DECL|macro|SK_PNMI_ERR018
mdefine_line|#define SK_PNMI_ERR018&t;&t;(SK_ERRBASE_PNMI + 18)
DECL|macro|SK_PNMI_ERR018MSG
mdefine_line|#define SK_PNMI_ERR018MSG&t;&quot;Vpd: VPD data not valid&quot;
DECL|macro|SK_PNMI_ERR019
mdefine_line|#define SK_PNMI_ERR019&t;&t;(SK_ERRBASE_PNMI + 19)
DECL|macro|SK_PNMI_ERR019MSG
mdefine_line|#define SK_PNMI_ERR019MSG&t;&quot;Vpd: VPD entries list string too long&quot;
DECL|macro|SK_PNMI_ERR021
mdefine_line|#define SK_PNMI_ERR021&t;&t;(SK_ERRBASE_PNMI + 21)
DECL|macro|SK_PNMI_ERR021MSG
mdefine_line|#define SK_PNMI_ERR021MSG&t;&quot;Vpd: VPD data string too long&quot;
DECL|macro|SK_PNMI_ERR022
mdefine_line|#define SK_PNMI_ERR022&t;&t;(SK_ERRBASE_PNMI + 22)
DECL|macro|SK_PNMI_ERR022MSG
mdefine_line|#define SK_PNMI_ERR022MSG&t;&quot;Vpd: VPD data string too long should be errored before&quot;
DECL|macro|SK_PNMI_ERR023
mdefine_line|#define SK_PNMI_ERR023&t;&t;(SK_ERRBASE_PNMI + 23)
DECL|macro|SK_PNMI_ERR023MSG
mdefine_line|#define SK_PNMI_ERR023MSG&t;&quot;Vpd: Unknown OID in get action&quot;
DECL|macro|SK_PNMI_ERR024
mdefine_line|#define SK_PNMI_ERR024&t;&t;(SK_ERRBASE_PNMI + 24)
DECL|macro|SK_PNMI_ERR024MSG
mdefine_line|#define SK_PNMI_ERR024MSG&t;&quot;Vpd: Unknown OID in preset/set action&quot;
DECL|macro|SK_PNMI_ERR025
mdefine_line|#define SK_PNMI_ERR025&t;&t;(SK_ERRBASE_PNMI + 25)
DECL|macro|SK_PNMI_ERR025MSG
mdefine_line|#define SK_PNMI_ERR025MSG&t;&quot;Vpd: Cannot write VPD after modify entry&quot;
DECL|macro|SK_PNMI_ERR026
mdefine_line|#define SK_PNMI_ERR026&t;&t;(SK_ERRBASE_PNMI + 26)
DECL|macro|SK_PNMI_ERR026MSG
mdefine_line|#define SK_PNMI_ERR026MSG&t;&quot;Vpd: Cannot update VPD&quot;
DECL|macro|SK_PNMI_ERR027
mdefine_line|#define SK_PNMI_ERR027&t;&t;(SK_ERRBASE_PNMI + 27)
DECL|macro|SK_PNMI_ERR027MSG
mdefine_line|#define SK_PNMI_ERR027MSG&t;&quot;Vpd: Cannot delete VPD entry&quot;
DECL|macro|SK_PNMI_ERR028
mdefine_line|#define SK_PNMI_ERR028&t;&t;(SK_ERRBASE_PNMI + 28)
DECL|macro|SK_PNMI_ERR028MSG
mdefine_line|#define SK_PNMI_ERR028MSG&t;&quot;Vpd: Cannot update VPD after delete entry&quot;
DECL|macro|SK_PNMI_ERR029
mdefine_line|#define SK_PNMI_ERR029&t;&t;(SK_ERRBASE_PNMI + 29)
DECL|macro|SK_PNMI_ERR029MSG
mdefine_line|#define SK_PNMI_ERR029MSG&t;&quot;General: Driver description string too long&quot;
DECL|macro|SK_PNMI_ERR030
mdefine_line|#define SK_PNMI_ERR030&t;&t;(SK_ERRBASE_PNMI + 30)
DECL|macro|SK_PNMI_ERR030MSG
mdefine_line|#define SK_PNMI_ERR030MSG&t;&quot;General: Driver version not initialized&quot;
DECL|macro|SK_PNMI_ERR031
mdefine_line|#define SK_PNMI_ERR031&t;&t;(SK_ERRBASE_PNMI + 31)
DECL|macro|SK_PNMI_ERR031MSG
mdefine_line|#define SK_PNMI_ERR031MSG&t;&quot;General: Driver version string too long&quot;
DECL|macro|SK_PNMI_ERR032
mdefine_line|#define SK_PNMI_ERR032&t;&t;(SK_ERRBASE_PNMI + 32)
DECL|macro|SK_PNMI_ERR032MSG
mdefine_line|#define SK_PNMI_ERR032MSG&t;&quot;General: Cannot read VPD Name for HW descr&quot;
DECL|macro|SK_PNMI_ERR033
mdefine_line|#define SK_PNMI_ERR033&t;&t;(SK_ERRBASE_PNMI + 33)
DECL|macro|SK_PNMI_ERR033MSG
mdefine_line|#define SK_PNMI_ERR033MSG&t;&quot;General: HW description string too long&quot;
DECL|macro|SK_PNMI_ERR034
mdefine_line|#define SK_PNMI_ERR034&t;&t;(SK_ERRBASE_PNMI + 34)
DECL|macro|SK_PNMI_ERR034MSG
mdefine_line|#define SK_PNMI_ERR034MSG&t;&quot;General: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR035
mdefine_line|#define SK_PNMI_ERR035&t;&t;(SK_ERRBASE_PNMI + 35)
DECL|macro|SK_PNMI_ERR035MSG
mdefine_line|#define SK_PNMI_ERR035MSG&t;&quot;Rlmt: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR036
mdefine_line|#define SK_PNMI_ERR036&t;&t;(SK_ERRBASE_PNMI + 36)
DECL|macro|SK_PNMI_ERR036MSG
mdefine_line|#define SK_PNMI_ERR036MSG&t;&quot;&quot;
DECL|macro|SK_PNMI_ERR037
mdefine_line|#define SK_PNMI_ERR037&t;&t;(SK_ERRBASE_PNMI + 37)
DECL|macro|SK_PNMI_ERR037MSG
mdefine_line|#define SK_PNMI_ERR037MSG&t;&quot;Rlmt: SK_RLMT_MODE_CHANGE event return not 0&quot;
DECL|macro|SK_PNMI_ERR038
mdefine_line|#define SK_PNMI_ERR038&t;&t;(SK_ERRBASE_PNMI + 38)
DECL|macro|SK_PNMI_ERR038MSG
mdefine_line|#define SK_PNMI_ERR038MSG&t;&quot;Rlmt: SK_RLMT_PREFPORT_CHANGE event return not 0&quot;
DECL|macro|SK_PNMI_ERR039
mdefine_line|#define SK_PNMI_ERR039&t;&t;(SK_ERRBASE_PNMI + 39)
DECL|macro|SK_PNMI_ERR039MSG
mdefine_line|#define SK_PNMI_ERR039MSG&t;&quot;RlmtStat: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR040
mdefine_line|#define SK_PNMI_ERR040&t;&t;(SK_ERRBASE_PNMI + 40)
DECL|macro|SK_PNMI_ERR040MSG
mdefine_line|#define SK_PNMI_ERR040MSG&t;&quot;PowerManagement: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR041
mdefine_line|#define SK_PNMI_ERR041&t;&t;(SK_ERRBASE_PNMI + 41)
DECL|macro|SK_PNMI_ERR041MSG
mdefine_line|#define SK_PNMI_ERR041MSG&t;&quot;MacPrivateConf: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR042
mdefine_line|#define SK_PNMI_ERR042&t;&t;(SK_ERRBASE_PNMI + 42)
DECL|macro|SK_PNMI_ERR042MSG
mdefine_line|#define SK_PNMI_ERR042MSG&t;&quot;MacPrivateConf: SK_HWEV_SET_ROLE returned not 0&quot;
DECL|macro|SK_PNMI_ERR043
mdefine_line|#define SK_PNMI_ERR043&t;&t;(SK_ERRBASE_PNMI + 43)
DECL|macro|SK_PNMI_ERR043MSG
mdefine_line|#define SK_PNMI_ERR043MSG&t;&quot;MacPrivateConf: SK_HWEV_SET_LMODE returned not 0&quot;
DECL|macro|SK_PNMI_ERR044
mdefine_line|#define SK_PNMI_ERR044&t;&t;(SK_ERRBASE_PNMI + 44)
DECL|macro|SK_PNMI_ERR044MSG
mdefine_line|#define SK_PNMI_ERR044MSG&t;&quot;MacPrivateConf: SK_HWEV_SET_FLOWMODE returned not 0&quot;
DECL|macro|SK_PNMI_ERR045
mdefine_line|#define SK_PNMI_ERR045&t;&t;(SK_ERRBASE_PNMI + 45)
DECL|macro|SK_PNMI_ERR045MSG
mdefine_line|#define SK_PNMI_ERR045MSG&t;&quot;MacPrivateConf: SK_HWEV_SET_SPEED returned not 0&quot;
DECL|macro|SK_PNMI_ERR046
mdefine_line|#define SK_PNMI_ERR046&t;&t;(SK_ERRBASE_PNMI + 46)
DECL|macro|SK_PNMI_ERR046MSG
mdefine_line|#define SK_PNMI_ERR046MSG&t;&quot;Monitor: Unknown OID&quot;
DECL|macro|SK_PNMI_ERR047
mdefine_line|#define SK_PNMI_ERR047&t;&t;(SK_ERRBASE_PNMI + 47)
DECL|macro|SK_PNMI_ERR047MSG
mdefine_line|#define SK_PNMI_ERR047MSG&t;&quot;SirqUpdate: Event function returns not 0&quot;
DECL|macro|SK_PNMI_ERR048
mdefine_line|#define SK_PNMI_ERR048&t;&t;(SK_ERRBASE_PNMI + 48)
DECL|macro|SK_PNMI_ERR048MSG
mdefine_line|#define SK_PNMI_ERR048MSG&t;&quot;RlmtUpdate: Event function returns not 0&quot;
DECL|macro|SK_PNMI_ERR049
mdefine_line|#define SK_PNMI_ERR049&t;&t;(SK_ERRBASE_PNMI + 49)
DECL|macro|SK_PNMI_ERR049MSG
mdefine_line|#define SK_PNMI_ERR049MSG&t;&quot;SkPnmiInit: Invalid size of &squot;CounterOffset&squot; struct!!&quot;
DECL|macro|SK_PNMI_ERR050
mdefine_line|#define SK_PNMI_ERR050&t;&t;(SK_ERRBASE_PNMI + 50)
DECL|macro|SK_PNMI_ERR050MSG
mdefine_line|#define SK_PNMI_ERR050MSG&t;&quot;SkPnmiInit: Invalid size of &squot;StatAddr&squot; table!!&quot;
DECL|macro|SK_PNMI_ERR051
mdefine_line|#define SK_PNMI_ERR051&t;&t;(SK_ERRBASE_PNMI + 51)
DECL|macro|SK_PNMI_ERR051MSG
mdefine_line|#define SK_PNMI_ERR051MSG&t;&quot;SkPnmiEvent: Port switch suspicious&quot;
DECL|macro|SK_PNMI_ERR052
mdefine_line|#define SK_PNMI_ERR052&t;&t;(SK_ERRBASE_PNMI + 52)
DECL|macro|SK_PNMI_ERR052MSG
mdefine_line|#define SK_PNMI_ERR052MSG&t;&quot;&quot;
DECL|macro|SK_PNMI_ERR053
mdefine_line|#define SK_PNMI_ERR053&t;&t;(SK_ERRBASE_PNMI + 53)
DECL|macro|SK_PNMI_ERR053MSG
mdefine_line|#define SK_PNMI_ERR053MSG&t;&quot;General: Driver release date not initialized&quot;
DECL|macro|SK_PNMI_ERR054
mdefine_line|#define SK_PNMI_ERR054&t;&t;(SK_ERRBASE_PNMI + 54)
DECL|macro|SK_PNMI_ERR054MSG
mdefine_line|#define SK_PNMI_ERR054MSG&t;&quot;General: Driver release date string too long&quot;
DECL|macro|SK_PNMI_ERR055
mdefine_line|#define SK_PNMI_ERR055&t;&t;(SK_ERRBASE_PNMI + 55)
DECL|macro|SK_PNMI_ERR055MSG
mdefine_line|#define SK_PNMI_ERR055MSG&t;&quot;General: Driver file name not initialized&quot;
DECL|macro|SK_PNMI_ERR056
mdefine_line|#define SK_PNMI_ERR056&t;&t;(SK_ERRBASE_PNMI + 56)
DECL|macro|SK_PNMI_ERR056MSG
mdefine_line|#define SK_PNMI_ERR056MSG&t;&quot;General: Driver file name string too long&quot;
multiline_comment|/*&n; * Management counter macros called by the driver&n; */
DECL|macro|SK_PNMI_SET_DRIVER_DESCR
mdefine_line|#define SK_PNMI_SET_DRIVER_DESCR(pAC,v)&t;((pAC)-&gt;Pnmi.pDriverDescription = &bslash;&n;&t;(char *)(v))
DECL|macro|SK_PNMI_SET_DRIVER_VER
mdefine_line|#define SK_PNMI_SET_DRIVER_VER(pAC,v)&t;((pAC)-&gt;Pnmi.pDriverVersion = &bslash;&n;&t;(char *)(v))
DECL|macro|SK_PNMI_SET_DRIVER_RELDATE
mdefine_line|#define SK_PNMI_SET_DRIVER_RELDATE(pAC,v)&t;((pAC)-&gt;Pnmi.pDriverReleaseDate = &bslash;&n;&t;(char *)(v))
DECL|macro|SK_PNMI_SET_DRIVER_FILENAME
mdefine_line|#define SK_PNMI_SET_DRIVER_FILENAME(pAC,v)&t;((pAC)-&gt;Pnmi.pDriverFileName = &bslash;&n;&t;(char *)(v))
DECL|macro|SK_PNMI_CNT_TX_QUEUE_LEN
mdefine_line|#define SK_PNMI_CNT_TX_QUEUE_LEN(pAC,v,p) &bslash;&n;&t;{ &bslash;&n;&t;&t;(pAC)-&gt;Pnmi.Port[p].TxSwQueueLen = (SK_U64)(v); &bslash;&n;&t;&t;if ((pAC)-&gt;Pnmi.Port[p].TxSwQueueLen &gt; (pAC)-&gt;Pnmi.Port[p].TxSwQueueMax) { &bslash;&n;&t;&t;&t;(pAC)-&gt;Pnmi.Port[p].TxSwQueueMax = (pAC)-&gt;Pnmi.Port[p].TxSwQueueLen; &bslash;&n;&t;&t;} &bslash;&n;&t;}
DECL|macro|SK_PNMI_CNT_TX_RETRY
mdefine_line|#define SK_PNMI_CNT_TX_RETRY(pAC,p)&t;(((pAC)-&gt;Pnmi.Port[p].TxRetryCts)++)
DECL|macro|SK_PNMI_CNT_RX_INTR
mdefine_line|#define SK_PNMI_CNT_RX_INTR(pAC,p)&t;(((pAC)-&gt;Pnmi.Port[p].RxIntrCts)++)
DECL|macro|SK_PNMI_CNT_TX_INTR
mdefine_line|#define SK_PNMI_CNT_TX_INTR(pAC,p)&t;(((pAC)-&gt;Pnmi.Port[p].TxIntrCts)++)
DECL|macro|SK_PNMI_CNT_NO_RX_BUF
mdefine_line|#define SK_PNMI_CNT_NO_RX_BUF(pAC,p)&t;(((pAC)-&gt;Pnmi.Port[p].RxNoBufCts)++)
DECL|macro|SK_PNMI_CNT_NO_TX_BUF
mdefine_line|#define SK_PNMI_CNT_NO_TX_BUF(pAC,p)&t;(((pAC)-&gt;Pnmi.Port[p].TxNoBufCts)++)
DECL|macro|SK_PNMI_CNT_USED_TX_DESCR
mdefine_line|#define SK_PNMI_CNT_USED_TX_DESCR(pAC,v,p) &bslash;&n;&t;((pAC)-&gt;Pnmi.Port[p].TxUsedDescrNo=(SK_U64)(v));
DECL|macro|SK_PNMI_CNT_RX_OCTETS_DELIVERED
mdefine_line|#define SK_PNMI_CNT_RX_OCTETS_DELIVERED(pAC,v,p) &bslash;&n;&t;{ &bslash;&n;&t;&t;((pAC)-&gt;Pnmi.Port[p].RxDeliveredCts)++; &bslash;&n;&t;&t;(pAC)-&gt;Pnmi.Port[p].RxOctetsDeliveredCts += (SK_U64)(v); &bslash;&n;&t;}
DECL|macro|SK_PNMI_CNT_ERR_RECOVERY
mdefine_line|#define SK_PNMI_CNT_ERR_RECOVERY(pAC,p)&t;(((pAC)-&gt;Pnmi.Port[p].ErrRecoveryCts)++);
DECL|macro|SK_PNMI_CNT_SYNC_OCTETS
mdefine_line|#define SK_PNMI_CNT_SYNC_OCTETS(pAC,p,v) &bslash;&n;&t;{ &bslash;&n;&t;&t;if ((p) &lt; SK_MAX_MACS) { &bslash;&n;&t;&t;&t;((pAC)-&gt;Pnmi.Port[p].StatSyncCts)++; &bslash;&n;&t;&t;&t;(pAC)-&gt;Pnmi.Port[p].StatSyncOctetsCts += (SK_U64)(v); &bslash;&n;&t;&t;} &bslash;&n;&t;}
DECL|macro|SK_PNMI_CNT_RX_LONGFRAMES
mdefine_line|#define SK_PNMI_CNT_RX_LONGFRAMES(pAC,p) &bslash;&n;&t;{ &bslash;&n;&t;&t;if ((p) &lt; SK_MAX_MACS) { &bslash;&n;&t;&t;&t;((pAC)-&gt;Pnmi.Port[p].StatRxLongFrameCts++); &bslash;&n;&t;&t;} &bslash;&n;&t;}
DECL|macro|SK_PNMI_CNT_RX_FRAMETOOLONG
mdefine_line|#define SK_PNMI_CNT_RX_FRAMETOOLONG(pAC,p) &bslash;&n;&t;{ &bslash;&n;&t;&t;if ((p) &lt; SK_MAX_MACS) { &bslash;&n;&t;&t;&t;((pAC)-&gt;Pnmi.Port[p].StatRxFrameTooLongCts++); &bslash;&n;&t;&t;} &bslash;&n;&t;}
DECL|macro|SK_PNMI_CNT_RX_PMACC_ERR
mdefine_line|#define SK_PNMI_CNT_RX_PMACC_ERR(pAC,p) &bslash;&n;&t;{ &bslash;&n;&t;&t;if ((p) &lt; SK_MAX_MACS) { &bslash;&n;&t;&t;&t;((pAC)-&gt;Pnmi.Port[p].StatRxPMaccErr++); &bslash;&n;&t;&t;} &bslash;&n;&t;}
multiline_comment|/*&n; * Conversion Macros&n; */
DECL|macro|SK_PNMI_PORT_INST2LOG
mdefine_line|#define SK_PNMI_PORT_INST2LOG(i)&t;((unsigned int)(i) - 1)
DECL|macro|SK_PNMI_PORT_LOG2INST
mdefine_line|#define SK_PNMI_PORT_LOG2INST(l)&t;((unsigned int)(l) + 1)
DECL|macro|SK_PNMI_PORT_PHYS2LOG
mdefine_line|#define SK_PNMI_PORT_PHYS2LOG(p)&t;((unsigned int)(p) + 1)
DECL|macro|SK_PNMI_PORT_LOG2PHYS
mdefine_line|#define SK_PNMI_PORT_LOG2PHYS(pAC,l)&t;((unsigned int)(l) - 1)
DECL|macro|SK_PNMI_PORT_PHYS2INST
mdefine_line|#define SK_PNMI_PORT_PHYS2INST(pAC,p)&t;&bslash;&n;&t;(pAC-&gt;Pnmi.DualNetActiveFlag ? 2 : ((unsigned int)(p) + 2))
DECL|macro|SK_PNMI_PORT_INST2PHYS
mdefine_line|#define SK_PNMI_PORT_INST2PHYS(pAC,i)&t;((unsigned int)(i) - 2)
multiline_comment|/*&n; * Structure definition for SkPnmiGetStruct and SkPnmiSetStruct&n; */
DECL|macro|SK_PNMI_VPD_KEY_SIZE
mdefine_line|#define SK_PNMI_VPD_KEY_SIZE&t;5
DECL|macro|SK_PNMI_VPD_BUFSIZE
mdefine_line|#define SK_PNMI_VPD_BUFSIZE&t;&t;(VPD_SIZE)
DECL|macro|SK_PNMI_VPD_ENTRIES
mdefine_line|#define SK_PNMI_VPD_ENTRIES&t;&t;(VPD_SIZE / 4)
DECL|macro|SK_PNMI_VPD_DATALEN
mdefine_line|#define SK_PNMI_VPD_DATALEN&t;&t;128 /*  Number of data bytes */
DECL|macro|SK_PNMI_MULTICAST_LISTLEN
mdefine_line|#define SK_PNMI_MULTICAST_LISTLEN&t;64
DECL|macro|SK_PNMI_SENSOR_ENTRIES
mdefine_line|#define SK_PNMI_SENSOR_ENTRIES&t;&t;(SK_MAX_SENSORS)
DECL|macro|SK_PNMI_CHECKSUM_ENTRIES
mdefine_line|#define SK_PNMI_CHECKSUM_ENTRIES&t;3
DECL|macro|SK_PNMI_MAC_ENTRIES
mdefine_line|#define SK_PNMI_MAC_ENTRIES&t;&t;&t;(SK_MAX_MACS + 1)
DECL|macro|SK_PNMI_MONITOR_ENTRIES
mdefine_line|#define SK_PNMI_MONITOR_ENTRIES&t;&t;20
DECL|macro|SK_PNMI_TRAP_ENTRIES
mdefine_line|#define SK_PNMI_TRAP_ENTRIES&t;&t;10
DECL|macro|SK_PNMI_TRAPLEN
mdefine_line|#define SK_PNMI_TRAPLEN&t;&t;&t;&t;128
DECL|macro|SK_PNMI_STRINGLEN1
mdefine_line|#define SK_PNMI_STRINGLEN1&t;&t;&t;80
DECL|macro|SK_PNMI_STRINGLEN2
mdefine_line|#define SK_PNMI_STRINGLEN2&t;&t;&t;25
DECL|macro|SK_PNMI_TRAP_QUEUE_LEN
mdefine_line|#define SK_PNMI_TRAP_QUEUE_LEN&t;&t;512
DECL|struct|s_PnmiVpd
r_typedef
r_struct
id|s_PnmiVpd
(brace
DECL|member|VpdKey
r_char
id|VpdKey
(braket
id|SK_PNMI_VPD_KEY_SIZE
)braket
suffix:semicolon
DECL|member|VpdValue
r_char
id|VpdValue
(braket
id|SK_PNMI_VPD_DATALEN
)braket
suffix:semicolon
DECL|member|VpdAccess
id|SK_U8
id|VpdAccess
suffix:semicolon
DECL|member|VpdAction
id|SK_U8
id|VpdAction
suffix:semicolon
DECL|typedef|SK_PNMI_VPD
)brace
id|SK_PNMI_VPD
suffix:semicolon
DECL|struct|s_PnmiSensor
r_typedef
r_struct
id|s_PnmiSensor
(brace
DECL|member|SensorIndex
id|SK_U8
id|SensorIndex
suffix:semicolon
DECL|member|SensorDescr
r_char
id|SensorDescr
(braket
id|SK_PNMI_STRINGLEN2
)braket
suffix:semicolon
DECL|member|SensorType
id|SK_U8
id|SensorType
suffix:semicolon
DECL|member|SensorValue
id|SK_U32
id|SensorValue
suffix:semicolon
DECL|member|SensorWarningThresholdLow
id|SK_U32
id|SensorWarningThresholdLow
suffix:semicolon
DECL|member|SensorWarningThresholdHigh
id|SK_U32
id|SensorWarningThresholdHigh
suffix:semicolon
DECL|member|SensorErrorThresholdLow
id|SK_U32
id|SensorErrorThresholdLow
suffix:semicolon
DECL|member|SensorErrorThresholdHigh
id|SK_U32
id|SensorErrorThresholdHigh
suffix:semicolon
DECL|member|SensorStatus
id|SK_U8
id|SensorStatus
suffix:semicolon
DECL|member|SensorWarningCts
id|SK_U64
id|SensorWarningCts
suffix:semicolon
DECL|member|SensorErrorCts
id|SK_U64
id|SensorErrorCts
suffix:semicolon
DECL|member|SensorWarningTimestamp
id|SK_U64
id|SensorWarningTimestamp
suffix:semicolon
DECL|member|SensorErrorTimestamp
id|SK_U64
id|SensorErrorTimestamp
suffix:semicolon
DECL|typedef|SK_PNMI_SENSOR
)brace
id|SK_PNMI_SENSOR
suffix:semicolon
DECL|struct|s_PnmiChecksum
r_typedef
r_struct
id|s_PnmiChecksum
(brace
DECL|member|ChecksumRxOkCts
id|SK_U64
id|ChecksumRxOkCts
suffix:semicolon
DECL|member|ChecksumRxUnableCts
id|SK_U64
id|ChecksumRxUnableCts
suffix:semicolon
DECL|member|ChecksumRxErrCts
id|SK_U64
id|ChecksumRxErrCts
suffix:semicolon
DECL|member|ChecksumTxOkCts
id|SK_U64
id|ChecksumTxOkCts
suffix:semicolon
DECL|member|ChecksumTxUnableCts
id|SK_U64
id|ChecksumTxUnableCts
suffix:semicolon
DECL|typedef|SK_PNMI_CHECKSUM
)brace
id|SK_PNMI_CHECKSUM
suffix:semicolon
DECL|struct|s_PnmiStat
r_typedef
r_struct
id|s_PnmiStat
(brace
DECL|member|StatTxOkCts
id|SK_U64
id|StatTxOkCts
suffix:semicolon
DECL|member|StatTxOctetsOkCts
id|SK_U64
id|StatTxOctetsOkCts
suffix:semicolon
DECL|member|StatTxBroadcastOkCts
id|SK_U64
id|StatTxBroadcastOkCts
suffix:semicolon
DECL|member|StatTxMulticastOkCts
id|SK_U64
id|StatTxMulticastOkCts
suffix:semicolon
DECL|member|StatTxUnicastOkCts
id|SK_U64
id|StatTxUnicastOkCts
suffix:semicolon
DECL|member|StatTxLongFramesCts
id|SK_U64
id|StatTxLongFramesCts
suffix:semicolon
DECL|member|StatTxBurstCts
id|SK_U64
id|StatTxBurstCts
suffix:semicolon
DECL|member|StatTxPauseMacCtrlCts
id|SK_U64
id|StatTxPauseMacCtrlCts
suffix:semicolon
DECL|member|StatTxMacCtrlCts
id|SK_U64
id|StatTxMacCtrlCts
suffix:semicolon
DECL|member|StatTxSingleCollisionCts
id|SK_U64
id|StatTxSingleCollisionCts
suffix:semicolon
DECL|member|StatTxMultipleCollisionCts
id|SK_U64
id|StatTxMultipleCollisionCts
suffix:semicolon
DECL|member|StatTxExcessiveCollisionCts
id|SK_U64
id|StatTxExcessiveCollisionCts
suffix:semicolon
DECL|member|StatTxLateCollisionCts
id|SK_U64
id|StatTxLateCollisionCts
suffix:semicolon
DECL|member|StatTxDeferralCts
id|SK_U64
id|StatTxDeferralCts
suffix:semicolon
DECL|member|StatTxExcessiveDeferralCts
id|SK_U64
id|StatTxExcessiveDeferralCts
suffix:semicolon
DECL|member|StatTxFifoUnderrunCts
id|SK_U64
id|StatTxFifoUnderrunCts
suffix:semicolon
DECL|member|StatTxCarrierCts
id|SK_U64
id|StatTxCarrierCts
suffix:semicolon
DECL|member|Dummy1
id|SK_U64
id|Dummy1
suffix:semicolon
multiline_comment|/* StatTxUtilization */
DECL|member|StatTx64Cts
id|SK_U64
id|StatTx64Cts
suffix:semicolon
DECL|member|StatTx127Cts
id|SK_U64
id|StatTx127Cts
suffix:semicolon
DECL|member|StatTx255Cts
id|SK_U64
id|StatTx255Cts
suffix:semicolon
DECL|member|StatTx511Cts
id|SK_U64
id|StatTx511Cts
suffix:semicolon
DECL|member|StatTx1023Cts
id|SK_U64
id|StatTx1023Cts
suffix:semicolon
DECL|member|StatTxMaxCts
id|SK_U64
id|StatTxMaxCts
suffix:semicolon
DECL|member|StatTxSyncCts
id|SK_U64
id|StatTxSyncCts
suffix:semicolon
DECL|member|StatTxSyncOctetsCts
id|SK_U64
id|StatTxSyncOctetsCts
suffix:semicolon
DECL|member|StatRxOkCts
id|SK_U64
id|StatRxOkCts
suffix:semicolon
DECL|member|StatRxOctetsOkCts
id|SK_U64
id|StatRxOctetsOkCts
suffix:semicolon
DECL|member|StatRxBroadcastOkCts
id|SK_U64
id|StatRxBroadcastOkCts
suffix:semicolon
DECL|member|StatRxMulticastOkCts
id|SK_U64
id|StatRxMulticastOkCts
suffix:semicolon
DECL|member|StatRxUnicastOkCts
id|SK_U64
id|StatRxUnicastOkCts
suffix:semicolon
DECL|member|StatRxLongFramesCts
id|SK_U64
id|StatRxLongFramesCts
suffix:semicolon
DECL|member|StatRxPauseMacCtrlCts
id|SK_U64
id|StatRxPauseMacCtrlCts
suffix:semicolon
DECL|member|StatRxMacCtrlCts
id|SK_U64
id|StatRxMacCtrlCts
suffix:semicolon
DECL|member|StatRxPauseMacCtrlErrorCts
id|SK_U64
id|StatRxPauseMacCtrlErrorCts
suffix:semicolon
DECL|member|StatRxMacCtrlUnknownCts
id|SK_U64
id|StatRxMacCtrlUnknownCts
suffix:semicolon
DECL|member|StatRxBurstCts
id|SK_U64
id|StatRxBurstCts
suffix:semicolon
DECL|member|StatRxMissedCts
id|SK_U64
id|StatRxMissedCts
suffix:semicolon
DECL|member|StatRxFramingCts
id|SK_U64
id|StatRxFramingCts
suffix:semicolon
DECL|member|StatRxFifoOverflowCts
id|SK_U64
id|StatRxFifoOverflowCts
suffix:semicolon
DECL|member|StatRxJabberCts
id|SK_U64
id|StatRxJabberCts
suffix:semicolon
DECL|member|StatRxCarrierCts
id|SK_U64
id|StatRxCarrierCts
suffix:semicolon
DECL|member|StatRxIRLengthCts
id|SK_U64
id|StatRxIRLengthCts
suffix:semicolon
DECL|member|StatRxSymbolCts
id|SK_U64
id|StatRxSymbolCts
suffix:semicolon
DECL|member|StatRxShortsCts
id|SK_U64
id|StatRxShortsCts
suffix:semicolon
DECL|member|StatRxRuntCts
id|SK_U64
id|StatRxRuntCts
suffix:semicolon
DECL|member|StatRxCextCts
id|SK_U64
id|StatRxCextCts
suffix:semicolon
DECL|member|StatRxTooLongCts
id|SK_U64
id|StatRxTooLongCts
suffix:semicolon
DECL|member|StatRxFcsCts
id|SK_U64
id|StatRxFcsCts
suffix:semicolon
DECL|member|Dummy2
id|SK_U64
id|Dummy2
suffix:semicolon
multiline_comment|/* StatRxUtilization */
DECL|member|StatRx64Cts
id|SK_U64
id|StatRx64Cts
suffix:semicolon
DECL|member|StatRx127Cts
id|SK_U64
id|StatRx127Cts
suffix:semicolon
DECL|member|StatRx255Cts
id|SK_U64
id|StatRx255Cts
suffix:semicolon
DECL|member|StatRx511Cts
id|SK_U64
id|StatRx511Cts
suffix:semicolon
DECL|member|StatRx1023Cts
id|SK_U64
id|StatRx1023Cts
suffix:semicolon
DECL|member|StatRxMaxCts
id|SK_U64
id|StatRxMaxCts
suffix:semicolon
DECL|typedef|SK_PNMI_STAT
)brace
id|SK_PNMI_STAT
suffix:semicolon
DECL|struct|s_PnmiConf
r_typedef
r_struct
id|s_PnmiConf
(brace
DECL|member|ConfMacCurrentAddr
r_char
id|ConfMacCurrentAddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|ConfMacFactoryAddr
r_char
id|ConfMacFactoryAddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|ConfPMD
id|SK_U8
id|ConfPMD
suffix:semicolon
DECL|member|ConfConnector
id|SK_U8
id|ConfConnector
suffix:semicolon
DECL|member|ConfPhyType
id|SK_U32
id|ConfPhyType
suffix:semicolon
DECL|member|ConfPhyMode
id|SK_U32
id|ConfPhyMode
suffix:semicolon
DECL|member|ConfLinkCapability
id|SK_U8
id|ConfLinkCapability
suffix:semicolon
DECL|member|ConfLinkMode
id|SK_U8
id|ConfLinkMode
suffix:semicolon
DECL|member|ConfLinkModeStatus
id|SK_U8
id|ConfLinkModeStatus
suffix:semicolon
DECL|member|ConfLinkStatus
id|SK_U8
id|ConfLinkStatus
suffix:semicolon
DECL|member|ConfFlowCtrlCapability
id|SK_U8
id|ConfFlowCtrlCapability
suffix:semicolon
DECL|member|ConfFlowCtrlMode
id|SK_U8
id|ConfFlowCtrlMode
suffix:semicolon
DECL|member|ConfFlowCtrlStatus
id|SK_U8
id|ConfFlowCtrlStatus
suffix:semicolon
DECL|member|ConfPhyOperationCapability
id|SK_U8
id|ConfPhyOperationCapability
suffix:semicolon
DECL|member|ConfPhyOperationMode
id|SK_U8
id|ConfPhyOperationMode
suffix:semicolon
DECL|member|ConfPhyOperationStatus
id|SK_U8
id|ConfPhyOperationStatus
suffix:semicolon
DECL|member|ConfSpeedCapability
id|SK_U8
id|ConfSpeedCapability
suffix:semicolon
DECL|member|ConfSpeedMode
id|SK_U8
id|ConfSpeedMode
suffix:semicolon
DECL|member|ConfSpeedStatus
id|SK_U8
id|ConfSpeedStatus
suffix:semicolon
DECL|typedef|SK_PNMI_CONF
)brace
id|SK_PNMI_CONF
suffix:semicolon
DECL|struct|s_PnmiRlmt
r_typedef
r_struct
id|s_PnmiRlmt
(brace
DECL|member|RlmtIndex
id|SK_U32
id|RlmtIndex
suffix:semicolon
DECL|member|RlmtStatus
id|SK_U32
id|RlmtStatus
suffix:semicolon
DECL|member|RlmtTxHelloCts
id|SK_U64
id|RlmtTxHelloCts
suffix:semicolon
DECL|member|RlmtRxHelloCts
id|SK_U64
id|RlmtRxHelloCts
suffix:semicolon
DECL|member|RlmtTxSpHelloReqCts
id|SK_U64
id|RlmtTxSpHelloReqCts
suffix:semicolon
DECL|member|RlmtRxSpHelloCts
id|SK_U64
id|RlmtRxSpHelloCts
suffix:semicolon
DECL|typedef|SK_PNMI_RLMT
)brace
id|SK_PNMI_RLMT
suffix:semicolon
DECL|struct|s_PnmiRlmtMonitor
r_typedef
r_struct
id|s_PnmiRlmtMonitor
(brace
DECL|member|RlmtMonitorIndex
id|SK_U32
id|RlmtMonitorIndex
suffix:semicolon
DECL|member|RlmtMonitorAddr
r_char
id|RlmtMonitorAddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|RlmtMonitorErrorCts
id|SK_U64
id|RlmtMonitorErrorCts
suffix:semicolon
DECL|member|RlmtMonitorTimestamp
id|SK_U64
id|RlmtMonitorTimestamp
suffix:semicolon
DECL|member|RlmtMonitorAdmin
id|SK_U8
id|RlmtMonitorAdmin
suffix:semicolon
DECL|typedef|SK_PNMI_RLMT_MONITOR
)brace
id|SK_PNMI_RLMT_MONITOR
suffix:semicolon
DECL|struct|s_PnmiRequestStatus
r_typedef
r_struct
id|s_PnmiRequestStatus
(brace
DECL|member|ErrorStatus
id|SK_U32
id|ErrorStatus
suffix:semicolon
DECL|member|ErrorOffset
id|SK_U32
id|ErrorOffset
suffix:semicolon
DECL|typedef|SK_PNMI_REQUEST_STATUS
)brace
id|SK_PNMI_REQUEST_STATUS
suffix:semicolon
DECL|struct|s_PnmiStrucData
r_typedef
r_struct
id|s_PnmiStrucData
(brace
DECL|member|MgmtDBVersion
id|SK_U32
id|MgmtDBVersion
suffix:semicolon
DECL|member|ReturnStatus
id|SK_PNMI_REQUEST_STATUS
id|ReturnStatus
suffix:semicolon
DECL|member|VpdFreeBytes
id|SK_U32
id|VpdFreeBytes
suffix:semicolon
DECL|member|VpdEntriesList
r_char
id|VpdEntriesList
(braket
id|SK_PNMI_VPD_ENTRIES
op_star
id|SK_PNMI_VPD_KEY_SIZE
)braket
suffix:semicolon
DECL|member|VpdEntriesNumber
id|SK_U32
id|VpdEntriesNumber
suffix:semicolon
DECL|member|Vpd
id|SK_PNMI_VPD
id|Vpd
(braket
id|SK_PNMI_VPD_ENTRIES
)braket
suffix:semicolon
DECL|member|PortNumber
id|SK_U32
id|PortNumber
suffix:semicolon
DECL|member|DeviceType
id|SK_U32
id|DeviceType
suffix:semicolon
DECL|member|DriverDescr
r_char
id|DriverDescr
(braket
id|SK_PNMI_STRINGLEN1
)braket
suffix:semicolon
DECL|member|DriverVersion
r_char
id|DriverVersion
(braket
id|SK_PNMI_STRINGLEN2
)braket
suffix:semicolon
DECL|member|DriverReleaseDate
r_char
id|DriverReleaseDate
(braket
id|SK_PNMI_STRINGLEN1
)braket
suffix:semicolon
DECL|member|DriverFileName
r_char
id|DriverFileName
(braket
id|SK_PNMI_STRINGLEN1
)braket
suffix:semicolon
DECL|member|HwDescr
r_char
id|HwDescr
(braket
id|SK_PNMI_STRINGLEN1
)braket
suffix:semicolon
DECL|member|HwVersion
r_char
id|HwVersion
(braket
id|SK_PNMI_STRINGLEN2
)braket
suffix:semicolon
DECL|member|Chipset
id|SK_U16
id|Chipset
suffix:semicolon
DECL|member|ChipId
id|SK_U32
id|ChipId
suffix:semicolon
DECL|member|VauxAvail
id|SK_U8
id|VauxAvail
suffix:semicolon
DECL|member|RamSize
id|SK_U32
id|RamSize
suffix:semicolon
DECL|member|MtuSize
id|SK_U32
id|MtuSize
suffix:semicolon
DECL|member|Action
id|SK_U32
id|Action
suffix:semicolon
DECL|member|TestResult
id|SK_U32
id|TestResult
suffix:semicolon
DECL|member|BusType
id|SK_U8
id|BusType
suffix:semicolon
DECL|member|BusSpeed
id|SK_U8
id|BusSpeed
suffix:semicolon
DECL|member|BusWidth
id|SK_U8
id|BusWidth
suffix:semicolon
DECL|member|SensorNumber
id|SK_U8
id|SensorNumber
suffix:semicolon
DECL|member|Sensor
id|SK_PNMI_SENSOR
id|Sensor
(braket
id|SK_PNMI_SENSOR_ENTRIES
)braket
suffix:semicolon
DECL|member|ChecksumNumber
id|SK_U8
id|ChecksumNumber
suffix:semicolon
DECL|member|Checksum
id|SK_PNMI_CHECKSUM
id|Checksum
(braket
id|SK_PNMI_CHECKSUM_ENTRIES
)braket
suffix:semicolon
DECL|member|Stat
id|SK_PNMI_STAT
id|Stat
(braket
id|SK_PNMI_MAC_ENTRIES
)braket
suffix:semicolon
DECL|member|Conf
id|SK_PNMI_CONF
id|Conf
(braket
id|SK_PNMI_MAC_ENTRIES
)braket
suffix:semicolon
DECL|member|RlmtMode
id|SK_U8
id|RlmtMode
suffix:semicolon
DECL|member|RlmtPortNumber
id|SK_U32
id|RlmtPortNumber
suffix:semicolon
DECL|member|RlmtPortActive
id|SK_U8
id|RlmtPortActive
suffix:semicolon
DECL|member|RlmtPortPreferred
id|SK_U8
id|RlmtPortPreferred
suffix:semicolon
DECL|member|RlmtChangeCts
id|SK_U64
id|RlmtChangeCts
suffix:semicolon
DECL|member|RlmtChangeTime
id|SK_U64
id|RlmtChangeTime
suffix:semicolon
DECL|member|RlmtChangeEstimate
id|SK_U64
id|RlmtChangeEstimate
suffix:semicolon
DECL|member|RlmtChangeThreshold
id|SK_U64
id|RlmtChangeThreshold
suffix:semicolon
DECL|member|Rlmt
id|SK_PNMI_RLMT
id|Rlmt
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
DECL|member|RlmtMonitorNumber
id|SK_U32
id|RlmtMonitorNumber
suffix:semicolon
DECL|member|RlmtMonitor
id|SK_PNMI_RLMT_MONITOR
id|RlmtMonitor
(braket
id|SK_PNMI_MONITOR_ENTRIES
)braket
suffix:semicolon
DECL|member|TrapNumber
id|SK_U32
id|TrapNumber
suffix:semicolon
DECL|member|Trap
id|SK_U8
id|Trap
(braket
id|SK_PNMI_TRAP_QUEUE_LEN
)braket
suffix:semicolon
DECL|member|TxSwQueueLen
id|SK_U64
id|TxSwQueueLen
suffix:semicolon
DECL|member|TxSwQueueMax
id|SK_U64
id|TxSwQueueMax
suffix:semicolon
DECL|member|TxRetryCts
id|SK_U64
id|TxRetryCts
suffix:semicolon
DECL|member|RxIntrCts
id|SK_U64
id|RxIntrCts
suffix:semicolon
DECL|member|TxIntrCts
id|SK_U64
id|TxIntrCts
suffix:semicolon
DECL|member|RxNoBufCts
id|SK_U64
id|RxNoBufCts
suffix:semicolon
DECL|member|TxNoBufCts
id|SK_U64
id|TxNoBufCts
suffix:semicolon
DECL|member|TxUsedDescrNo
id|SK_U64
id|TxUsedDescrNo
suffix:semicolon
DECL|member|RxDeliveredCts
id|SK_U64
id|RxDeliveredCts
suffix:semicolon
DECL|member|RxOctetsDeliveredCts
id|SK_U64
id|RxOctetsDeliveredCts
suffix:semicolon
DECL|member|RxHwErrorsCts
id|SK_U64
id|RxHwErrorsCts
suffix:semicolon
DECL|member|TxHwErrorsCts
id|SK_U64
id|TxHwErrorsCts
suffix:semicolon
DECL|member|InErrorsCts
id|SK_U64
id|InErrorsCts
suffix:semicolon
DECL|member|OutErrorsCts
id|SK_U64
id|OutErrorsCts
suffix:semicolon
DECL|member|ErrRecoveryCts
id|SK_U64
id|ErrRecoveryCts
suffix:semicolon
DECL|member|SysUpTime
id|SK_U64
id|SysUpTime
suffix:semicolon
DECL|typedef|SK_PNMI_STRUCT_DATA
)brace
id|SK_PNMI_STRUCT_DATA
suffix:semicolon
DECL|macro|SK_PNMI_STRUCT_SIZE
mdefine_line|#define SK_PNMI_STRUCT_SIZE&t;(sizeof(SK_PNMI_STRUCT_DATA))
DECL|macro|SK_PNMI_MIN_STRUCT_SIZE
mdefine_line|#define SK_PNMI_MIN_STRUCT_SIZE&t;((unsigned int)(SK_UPTR)&bslash;&n;&t;&t;&t;&t; &amp;(((SK_PNMI_STRUCT_DATA *)0)-&gt;VpdFreeBytes))
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; * ReturnStatus field&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; * must be located&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; * before VpdFreeBytes&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Various definitions&n; */
DECL|macro|SK_PNMI_MAX_PROTOS
mdefine_line|#define SK_PNMI_MAX_PROTOS&t;&t;3
DECL|macro|SK_PNMI_CNT_NO
mdefine_line|#define SK_PNMI_CNT_NO&t;&t;&t;66&t;/* Must have the value of the enum&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * SK_PNMI_MAX_IDX. Define SK_PNMI_CHECK&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * for check while init phase 1&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Estimate data structure&n; */
DECL|struct|s_PnmiEstimate
r_typedef
r_struct
id|s_PnmiEstimate
(brace
DECL|member|EstValueIndex
r_int
r_int
id|EstValueIndex
suffix:semicolon
DECL|member|EstValue
id|SK_U64
id|EstValue
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|Estimate
id|SK_U64
id|Estimate
suffix:semicolon
DECL|member|EstTimer
id|SK_TIMER
id|EstTimer
suffix:semicolon
DECL|typedef|SK_PNMI_ESTIMATE
)brace
id|SK_PNMI_ESTIMATE
suffix:semicolon
multiline_comment|/*&n; * VCT timer data structure&n; */
DECL|struct|s_VctTimer
r_typedef
r_struct
id|s_VctTimer
(brace
DECL|member|VctTimer
id|SK_TIMER
id|VctTimer
suffix:semicolon
DECL|typedef|SK_PNMI_VCT_TIMER
)brace
id|SK_PNMI_VCT_TIMER
suffix:semicolon
multiline_comment|/*&n; * PNMI specific adapter context structure&n; */
DECL|struct|s_PnmiPort
r_typedef
r_struct
id|s_PnmiPort
(brace
DECL|member|StatSyncCts
id|SK_U64
id|StatSyncCts
suffix:semicolon
DECL|member|StatSyncOctetsCts
id|SK_U64
id|StatSyncOctetsCts
suffix:semicolon
DECL|member|StatRxLongFrameCts
id|SK_U64
id|StatRxLongFrameCts
suffix:semicolon
DECL|member|StatRxFrameTooLongCts
id|SK_U64
id|StatRxFrameTooLongCts
suffix:semicolon
DECL|member|StatRxPMaccErr
id|SK_U64
id|StatRxPMaccErr
suffix:semicolon
DECL|member|TxSwQueueLen
id|SK_U64
id|TxSwQueueLen
suffix:semicolon
DECL|member|TxSwQueueMax
id|SK_U64
id|TxSwQueueMax
suffix:semicolon
DECL|member|TxRetryCts
id|SK_U64
id|TxRetryCts
suffix:semicolon
DECL|member|RxIntrCts
id|SK_U64
id|RxIntrCts
suffix:semicolon
DECL|member|TxIntrCts
id|SK_U64
id|TxIntrCts
suffix:semicolon
DECL|member|RxNoBufCts
id|SK_U64
id|RxNoBufCts
suffix:semicolon
DECL|member|TxNoBufCts
id|SK_U64
id|TxNoBufCts
suffix:semicolon
DECL|member|TxUsedDescrNo
id|SK_U64
id|TxUsedDescrNo
suffix:semicolon
DECL|member|RxDeliveredCts
id|SK_U64
id|RxDeliveredCts
suffix:semicolon
DECL|member|RxOctetsDeliveredCts
id|SK_U64
id|RxOctetsDeliveredCts
suffix:semicolon
DECL|member|RxHwErrorsCts
id|SK_U64
id|RxHwErrorsCts
suffix:semicolon
DECL|member|TxHwErrorsCts
id|SK_U64
id|TxHwErrorsCts
suffix:semicolon
DECL|member|InErrorsCts
id|SK_U64
id|InErrorsCts
suffix:semicolon
DECL|member|OutErrorsCts
id|SK_U64
id|OutErrorsCts
suffix:semicolon
DECL|member|ErrRecoveryCts
id|SK_U64
id|ErrRecoveryCts
suffix:semicolon
DECL|member|RxShortZeroMark
id|SK_U64
id|RxShortZeroMark
suffix:semicolon
DECL|member|CounterOffset
id|SK_U64
id|CounterOffset
(braket
id|SK_PNMI_CNT_NO
)braket
suffix:semicolon
DECL|member|CounterHigh
id|SK_U32
id|CounterHigh
(braket
id|SK_PNMI_CNT_NO
)braket
suffix:semicolon
DECL|member|ActiveFlag
id|SK_BOOL
id|ActiveFlag
suffix:semicolon
DECL|member|Align
id|SK_U8
id|Align
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|SK_PNMI_PORT
)brace
id|SK_PNMI_PORT
suffix:semicolon
DECL|struct|s_PnmiData
r_typedef
r_struct
id|s_PnmiData
(brace
DECL|member|Port
id|SK_PNMI_PORT
id|Port
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
DECL|member|BufPort
id|SK_PNMI_PORT
id|BufPort
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
multiline_comment|/* 2002-09-13 pweber  */
DECL|member|VirtualCounterOffset
id|SK_U64
id|VirtualCounterOffset
(braket
id|SK_PNMI_CNT_NO
)braket
suffix:semicolon
DECL|member|TestResult
id|SK_U32
id|TestResult
suffix:semicolon
DECL|member|HwVersion
r_char
id|HwVersion
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|Align01
id|SK_U16
id|Align01
suffix:semicolon
DECL|member|pDriverDescription
r_char
op_star
id|pDriverDescription
suffix:semicolon
DECL|member|pDriverVersion
r_char
op_star
id|pDriverVersion
suffix:semicolon
DECL|member|pDriverReleaseDate
r_char
op_star
id|pDriverReleaseDate
suffix:semicolon
DECL|member|pDriverFileName
r_char
op_star
id|pDriverFileName
suffix:semicolon
DECL|member|MacUpdatedFlag
r_int
id|MacUpdatedFlag
suffix:semicolon
DECL|member|RlmtUpdatedFlag
r_int
id|RlmtUpdatedFlag
suffix:semicolon
DECL|member|SirqUpdatedFlag
r_int
id|SirqUpdatedFlag
suffix:semicolon
DECL|member|RlmtChangeCts
id|SK_U64
id|RlmtChangeCts
suffix:semicolon
DECL|member|RlmtChangeTime
id|SK_U64
id|RlmtChangeTime
suffix:semicolon
DECL|member|RlmtChangeEstimate
id|SK_PNMI_ESTIMATE
id|RlmtChangeEstimate
suffix:semicolon
DECL|member|RlmtChangeThreshold
id|SK_U64
id|RlmtChangeThreshold
suffix:semicolon
DECL|member|StartUpTime
id|SK_U64
id|StartUpTime
suffix:semicolon
DECL|member|DeviceType
id|SK_U32
id|DeviceType
suffix:semicolon
DECL|member|PciBusSpeed
r_char
id|PciBusSpeed
suffix:semicolon
DECL|member|PciBusWidth
r_char
id|PciBusWidth
suffix:semicolon
DECL|member|Chipset
r_char
id|Chipset
suffix:semicolon
DECL|member|PMD
r_char
id|PMD
suffix:semicolon
DECL|member|Connector
r_char
id|Connector
suffix:semicolon
DECL|member|DualNetActiveFlag
id|SK_BOOL
id|DualNetActiveFlag
suffix:semicolon
DECL|member|Align02
id|SK_U16
id|Align02
suffix:semicolon
DECL|member|TrapBuf
r_char
id|TrapBuf
(braket
id|SK_PNMI_TRAP_QUEUE_LEN
)braket
suffix:semicolon
DECL|member|TrapBufFree
r_int
r_int
id|TrapBufFree
suffix:semicolon
DECL|member|TrapQueueBeg
r_int
r_int
id|TrapQueueBeg
suffix:semicolon
DECL|member|TrapQueueEnd
r_int
r_int
id|TrapQueueEnd
suffix:semicolon
DECL|member|TrapBufPad
r_int
r_int
id|TrapBufPad
suffix:semicolon
DECL|member|TrapUnique
r_int
r_int
id|TrapUnique
suffix:semicolon
DECL|member|VctStatus
id|SK_U8
id|VctStatus
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
DECL|member|VctBackup
id|SK_PNMI_VCT
id|VctBackup
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
DECL|member|VctTimeout
id|SK_PNMI_VCT_TIMER
id|VctTimeout
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
macro_line|#ifdef SK_DIAG_SUPPORT
DECL|member|DiagAttached
id|SK_U32
id|DiagAttached
suffix:semicolon
macro_line|#endif /* SK_DIAG_SUPPORT */
DECL|typedef|SK_PNMI
)brace
id|SK_PNMI
suffix:semicolon
multiline_comment|/*&n; * Function prototypes&n; */
r_extern
r_int
id|SkPnmiInit
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Level
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiGetVar
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
id|Id
comma
r_void
op_star
id|pBuf
comma
r_int
r_int
op_star
id|pLen
comma
id|SK_U32
id|Instance
comma
id|SK_U32
id|NetIndex
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiPreSetVar
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
id|Id
comma
r_void
op_star
id|pBuf
comma
r_int
r_int
op_star
id|pLen
comma
id|SK_U32
id|Instance
comma
id|SK_U32
id|NetIndex
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiSetVar
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
id|Id
comma
r_void
op_star
id|pBuf
comma
r_int
r_int
op_star
id|pLen
comma
id|SK_U32
id|Instance
comma
id|SK_U32
id|NetIndex
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiGetStruct
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_void
op_star
id|pBuf
comma
r_int
r_int
op_star
id|pLen
comma
id|SK_U32
id|NetIndex
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiPreSetStruct
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_void
op_star
id|pBuf
comma
r_int
r_int
op_star
id|pLen
comma
id|SK_U32
id|NetIndex
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiSetStruct
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_void
op_star
id|pBuf
comma
r_int
r_int
op_star
id|pLen
comma
id|SK_U32
id|NetIndex
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiEvent
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
id|Event
comma
id|SK_EVPARA
id|Param
)paren
suffix:semicolon
r_extern
r_int
id|SkPnmiGenIoctl
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_void
op_star
id|pBuf
comma
r_int
r_int
op_star
id|pLen
comma
id|SK_U32
id|NetIndex
)paren
suffix:semicolon
macro_line|#endif
eof
