multiline_comment|/*****************************************************************************&n; *&n; * Name:&t;skgepnm2.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.30 $&n; * Date:&t;$Date: 2001/02/06 10:03:41 $&n; * Purpose:&t;Defines for Private Network Management Interface&n; *&n; ****************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2001 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*****************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgepnm2.h,v $&n; *&t;Revision 1.30  2001/02/06 10:03:41  mkunz&n; *&t;- Pnmi V4 dual net support added. Interface functions and macros extended&n; *&t;- Vpd bug fixed&n; *&t;- OID_SKGE_MTU added&n; *&t;&n; *&t;Revision 1.29  2001/01/22 13:41:37  rassmann&n; *&t;Supporting two nets on dual-port adapters.&n; *&t;&n; *&t;Revision 1.28  2000/08/03 15:12:48  rwahl&n; *&t;- Additional comment for MAC statistic data structure.&n; *&t;&n; *&t;Revision 1.27  2000/08/01 16:10:18  rwahl&n; *&t;- Added mac statistic data structure for StatRxLongFrame counter.&n; *&t;&n; *&t;Revision 1.26  2000/03/31 13:51:34  rwahl&n; *&t;Added SK_UPTR cast to offset calculation for PNMI struct fields;&n; *&t;missing cast caused compiler warnings by Win64 compiler.&n; *&t;&n; *&t;Revision 1.25  1999/11/22 13:57:41  cgoos&n; *&t;Changed license header to GPL.&n; *&t;Allowing overwrite for SK_PNMI_STORE/_READ defines.&n; *&t;&n; *&t;Revision 1.24  1999/04/13 15:11:11  mhaveman&n; *&t;Changed copyright.&n; *&t;&n; *&t;Revision 1.23  1999/01/28 15:07:12  mhaveman&n; *&t;Changed default threshold for port switches per hour from 10&n; *&t;to 240 which means 4 switches per minute. This fits better&n; *&t;the granularity of 32 for the port switch estimate&n; *&t;counter.&n; *&t;&n; *&t;Revision 1.22  1999/01/05 12:52:30  mhaveman&n; *&t;Removed macro SK_PNMI_MICRO_SEC.&n; *&t;&n; *&t;Revision 1.21  1999/01/05 12:50:34  mhaveman&n; *&t;Enlarged macro definition SK_PNMI_HUNDREDS_SEC() so that no 64-bit&n; *&t;arithmetic is necessary if SK_TICKS_PER_SEC is 100.&n; *&t;&n; *&t;Revision 1.20  1998/12/09 14:02:53  mhaveman&n; *&t;Defined macro SK_PNMI_DEF_RLMT_CHG_THRES for default port switch&n; *&t;threshold.&n; *&t;&n; *&t;Revision 1.19  1998/12/03 11:28:41  mhaveman&n; *&t;Removed SK_PNMI_CHECKPTR macro.&n; *&t;&n; *&t;Revision 1.18  1998/12/03 11:21:00  mhaveman&n; *&t;-Added pointer check macro SK_PNMI_CHECKPTR&n; *&t;-Added macros SK_PNMI_VPD_ARR_SIZE and SK_PNMI_VPD_STR_SIZE for&n; *&t; VPD key evaluation.&n; *&t;&n; *&t;Revision 1.17  1998/11/20 13:20:33  mhaveman&n; *&t;Fixed bug in SK_PNMI_SET_STAT macro. ErrorStatus was not correctly set.&n; *&t;&n; *&t;Revision 1.16  1998/11/20 08:08:49  mhaveman&n; *&t;Macro SK_PNMI_CHECKFLAGS has got a if clause.&n; *&t;&n; *&t;Revision 1.15  1998/11/03 13:53:40  mhaveman&n; *&t;Fixed alignment problem in macor SK_PNMI_SET_STAT macro.&n; *&t;&n; *&t;Revision 1.14  1998/10/30 15:50:13  mhaveman&n; *&t;Added macro SK_PNMI_MICRO_SEC()&n; *&t;&n; *&t;Revision 1.13  1998/10/30 12:32:20  mhaveman&n; *&t;Added forgotten cast in SK_PNMI_READ_U32 macro.&n; *&n; *&t;Revision 1.12  1998/10/29 15:40:26  mhaveman&n; *&t;-Changed SK_PNMI_TRAP_SENSOR_LEN because SensorDescr has now&n; *&t; variable string length.&n; *&t;-Defined SK_PNMI_CHECKFLAGS macro&n; *&t;&n; *&t;Revision 1.11  1998/10/29 08:53:34  mhaveman&n; *&t;Removed SK_PNMI_RLM_XXX table indexed because these counters need&n; *&t;not been saved over XMAC resets.&n; *&t;&n; *&t;Revision 1.10  1998/10/28 08:48:20  mhaveman&n; *&t;-Added macros for storage according to alignment&n; *&t;-Changed type of Instance to SK_U32 because of VPD&n; *&t;-Removed trap structures. Not needed because of alignment problem&n; *&t;-Changed type of Action form SK_U8 to int&n; *&t;&n; *&t;Revision 1.9  1998/10/21 13:34:45  mhaveman&n; *&t;Shit, mismatched calculation of SK_PNMI_HUNDREDS_SEC. Corrected.&n; *&t;&n; *&t;Revision 1.8  1998/10/21 13:24:58  mhaveman&n; *&t;Changed calculation of hundreds of seconds.&n; *&t;&n; *&t;Revision 1.7  1998/10/20 07:31:41  mhaveman&n; *&t;Made type changes to unsigned int where possible.&n; *&t;&n; *&t;Revision 1.6  1998/09/04 17:04:05  mhaveman&n; *&t;Added Sync counters to offset storage to provided settled values on&n; *&t;port switch.&n; *&t;&n; *&t;Revision 1.5  1998/09/04 12:45:35  mhaveman&n; *&t;Removed dummies for SK_DRIVER_ macros. They should be added by driver&n; *&t;writer in skdrv2nd.h.&n; *&t;&n; *&t;Revision 1.4  1998/09/04 11:59:50  mhaveman&n; *&t;Everything compiles now. Driver Macros for counting still missing.&n; *&t;&n; *&t;Revision 1.3  1998/08/24 12:01:35  mhaveman&n; *&t;Intermediate state.&n; *&t;&n; *&t;Revision 1.2  1998/08/17 07:51:40  mhaveman&n; *&t;Intermediate state.&n; *&t;&n; *&t;Revision 1.1  1998/08/11 09:08:40  mhaveman&n; *&t;Intermediate state.&n; *&t;&n; ****************************************************************************/
macro_line|#ifndef _SKGEPNM2_H_
DECL|macro|_SKGEPNM2_H_
mdefine_line|#define _SKGEPNM2_H_
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE&t;&t;&t;0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define&t;TRUE&t;&t;&t;!(FALSE)
macro_line|#endif
multiline_comment|/*&n; * General definitions&n; */
DECL|macro|SK_PNMI_CHIPSET
mdefine_line|#define SK_PNMI_CHIPSET&t;&t;1&t;/* XMAC11800FP */
DECL|macro|SK_PNMI_BUS_PCI
mdefine_line|#define&t;SK_PNMI_BUS_PCI&t;&t;1&t;/* PCI bus*/
multiline_comment|/*&n; * Actions&n; */
DECL|macro|SK_PNMI_ACT_IDLE
mdefine_line|#define SK_PNMI_ACT_IDLE&t;1
DECL|macro|SK_PNMI_ACT_RESET
mdefine_line|#define SK_PNMI_ACT_RESET&t;2
DECL|macro|SK_PNMI_ACT_SELFTEST
mdefine_line|#define SK_PNMI_ACT_SELFTEST&t;3
DECL|macro|SK_PNMI_ACT_RESETCNT
mdefine_line|#define SK_PNMI_ACT_RESETCNT&t;4
multiline_comment|/*&n; * VPD releated defines&n; */
DECL|macro|SK_PNMI_VPD_RW
mdefine_line|#define SK_PNMI_VPD_RW&t;&t;1
DECL|macro|SK_PNMI_VPD_RO
mdefine_line|#define SK_PNMI_VPD_RO&t;&t;2
DECL|macro|SK_PNMI_VPD_OK
mdefine_line|#define SK_PNMI_VPD_OK&t;&t;0
DECL|macro|SK_PNMI_VPD_NOTFOUND
mdefine_line|#define SK_PNMI_VPD_NOTFOUND&t;1
DECL|macro|SK_PNMI_VPD_CUT
mdefine_line|#define SK_PNMI_VPD_CUT&t;&t;2
DECL|macro|SK_PNMI_VPD_TIMEOUT
mdefine_line|#define SK_PNMI_VPD_TIMEOUT&t;3
DECL|macro|SK_PNMI_VPD_FULL
mdefine_line|#define SK_PNMI_VPD_FULL&t;4
DECL|macro|SK_PNMI_VPD_NOWRITE
mdefine_line|#define SK_PNMI_VPD_NOWRITE&t;5
DECL|macro|SK_PNMI_VPD_FATAL
mdefine_line|#define SK_PNMI_VPD_FATAL&t;6
DECL|macro|SK_PNMI_VPD_IGNORE
mdefine_line|#define SK_PNMI_VPD_IGNORE&t;0
DECL|macro|SK_PNMI_VPD_CREATE
mdefine_line|#define SK_PNMI_VPD_CREATE&t;1
DECL|macro|SK_PNMI_VPD_DELETE
mdefine_line|#define SK_PNMI_VPD_DELETE&t;2
multiline_comment|/*&n; * RLMT related defines&n; */
DECL|macro|SK_PNMI_DEF_RLMT_CHG_THRES
mdefine_line|#define SK_PNMI_DEF_RLMT_CHG_THRES&t;240&t;/* 4 changes per minute */
multiline_comment|/*&n; * Internal table definitions&n; */
DECL|macro|SK_PNMI_GET
mdefine_line|#define SK_PNMI_GET&t;&t;0
DECL|macro|SK_PNMI_PRESET
mdefine_line|#define SK_PNMI_PRESET&t;&t;1
DECL|macro|SK_PNMI_SET
mdefine_line|#define SK_PNMI_SET&t;&t;2
DECL|macro|SK_PNMI_RO
mdefine_line|#define SK_PNMI_RO&t;&t;0
DECL|macro|SK_PNMI_RW
mdefine_line|#define SK_PNMI_RW&t;&t;1
DECL|struct|s_OidTabEntry
r_typedef
r_struct
id|s_OidTabEntry
(brace
DECL|member|Id
id|SK_U32
id|Id
suffix:semicolon
DECL|member|InstanceNo
id|SK_U32
id|InstanceNo
suffix:semicolon
DECL|member|StructSize
r_int
r_int
id|StructSize
suffix:semicolon
DECL|member|Offset
r_int
r_int
id|Offset
suffix:semicolon
DECL|member|Access
r_int
id|Access
suffix:semicolon
DECL|member|Func
r_int
(paren
op_star
id|Func
)paren
(paren
id|SK_AC
op_star
id|pAc
comma
id|SK_IOC
id|pIo
comma
r_int
id|action
comma
id|SK_U32
id|Id
comma
r_char
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
r_int
r_int
id|TableIndex
comma
id|SK_U32
id|NetNumber
)paren
suffix:semicolon
DECL|member|Param
id|SK_U16
id|Param
suffix:semicolon
DECL|typedef|SK_PNMI_TAB_ENTRY
)brace
id|SK_PNMI_TAB_ENTRY
suffix:semicolon
multiline_comment|/*&n; * Trap lengths&n; */
DECL|macro|SK_PNMI_TRAP_SIMPLE_LEN
mdefine_line|#define SK_PNMI_TRAP_SIMPLE_LEN&t;&t;17
DECL|macro|SK_PNMI_TRAP_SENSOR_LEN_BASE
mdefine_line|#define SK_PNMI_TRAP_SENSOR_LEN_BASE&t;46
DECL|macro|SK_PNMI_TRAP_RLMT_CHANGE_LEN
mdefine_line|#define SK_PNMI_TRAP_RLMT_CHANGE_LEN&t;23
DECL|macro|SK_PNMI_TRAP_RLMT_PORT_LEN
mdefine_line|#define SK_PNMI_TRAP_RLMT_PORT_LEN&t;23
multiline_comment|/*&n; * MAC statistic data structures&n; * Only for the first 64 counters: the number relates to the bit in the&n; * XMAC overflow status register&n; */
DECL|macro|SK_PNMI_HTX
mdefine_line|#define SK_PNMI_HTX&t;&t;&t;0
DECL|macro|SK_PNMI_HTX_OCTET
mdefine_line|#define SK_PNMI_HTX_OCTET&t;&t;1
DECL|macro|SK_PNMI_HTX_OCTETHIGH
mdefine_line|#define SK_PNMI_HTX_OCTETHIGH&t;&t;1
DECL|macro|SK_PNMI_HTX_OCTETLOW
mdefine_line|#define SK_PNMI_HTX_OCTETLOW&t;&t;2
DECL|macro|SK_PNMI_HTX_BROADCAST
mdefine_line|#define SK_PNMI_HTX_BROADCAST&t;&t;3
DECL|macro|SK_PNMI_HTX_MULTICAST
mdefine_line|#define SK_PNMI_HTX_MULTICAST&t;&t;4
DECL|macro|SK_PNMI_HTX_UNICAST
mdefine_line|#define SK_PNMI_HTX_UNICAST&t;&t;5
DECL|macro|SK_PNMI_HTX_LONGFRAMES
mdefine_line|#define SK_PNMI_HTX_LONGFRAMES&t;&t;6
DECL|macro|SK_PNMI_HTX_BURST
mdefine_line|#define SK_PNMI_HTX_BURST&t;&t;7
DECL|macro|SK_PNMI_HTX_PMACC
mdefine_line|#define SK_PNMI_HTX_PMACC&t;&t;8
DECL|macro|SK_PNMI_HTX_MACC
mdefine_line|#define SK_PNMI_HTX_MACC&t;&t;9
DECL|macro|SK_PNMI_HTX_SINGLE_COL
mdefine_line|#define SK_PNMI_HTX_SINGLE_COL&t;&t;10
DECL|macro|SK_PNMI_HTX_MULTI_COL
mdefine_line|#define SK_PNMI_HTX_MULTI_COL&t;&t;11
DECL|macro|SK_PNMI_HTX_EXCESS_COL
mdefine_line|#define SK_PNMI_HTX_EXCESS_COL&t;&t;12
DECL|macro|SK_PNMI_HTX_LATE_COL
mdefine_line|#define SK_PNMI_HTX_LATE_COL&t;&t;13
DECL|macro|SK_PNMI_HTX_DEFFERAL
mdefine_line|#define SK_PNMI_HTX_DEFFERAL&t;&t;14
DECL|macro|SK_PNMI_HTX_EXCESS_DEF
mdefine_line|#define SK_PNMI_HTX_EXCESS_DEF&t;&t;15
DECL|macro|SK_PNMI_HTX_UNDERRUN
mdefine_line|#define SK_PNMI_HTX_UNDERRUN&t;&t;16
DECL|macro|SK_PNMI_HTX_CARRIER
mdefine_line|#define SK_PNMI_HTX_CARRIER&t;&t;17
DECL|macro|SK_PNMI_HTX_UTILUNDER
mdefine_line|#define SK_PNMI_HTX_UTILUNDER&t;&t;18
DECL|macro|SK_PNMI_HTX_UTILOVER
mdefine_line|#define SK_PNMI_HTX_UTILOVER&t;&t;19
DECL|macro|SK_PNMI_HTX_64
mdefine_line|#define SK_PNMI_HTX_64&t;&t;&t;20
DECL|macro|SK_PNMI_HTX_127
mdefine_line|#define SK_PNMI_HTX_127&t;&t;&t;21
DECL|macro|SK_PNMI_HTX_255
mdefine_line|#define SK_PNMI_HTX_255&t;&t;&t;22
DECL|macro|SK_PNMI_HTX_511
mdefine_line|#define SK_PNMI_HTX_511&t;&t;&t;23
DECL|macro|SK_PNMI_HTX_1023
mdefine_line|#define SK_PNMI_HTX_1023&t;&t;24
DECL|macro|SK_PNMI_HTX_MAX
mdefine_line|#define SK_PNMI_HTX_MAX&t;&t;&t;25
DECL|macro|SK_PNMI_HTX_RESERVED26
mdefine_line|#define SK_PNMI_HTX_RESERVED26&t;&t;26
DECL|macro|SK_PNMI_HTX_RESERVED27
mdefine_line|#define SK_PNMI_HTX_RESERVED27&t;&t;27
DECL|macro|SK_PNMI_HTX_RESERVED28
mdefine_line|#define SK_PNMI_HTX_RESERVED28&t;&t;28
DECL|macro|SK_PNMI_HTX_RESERVED29
mdefine_line|#define SK_PNMI_HTX_RESERVED29&t;&t;29
DECL|macro|SK_PNMI_HTX_RESERVED30
mdefine_line|#define SK_PNMI_HTX_RESERVED30&t;&t;30
DECL|macro|SK_PNMI_HTX_RESERVED31
mdefine_line|#define SK_PNMI_HTX_RESERVED31&t;&t;31
DECL|macro|SK_PNMI_HRX
mdefine_line|#define SK_PNMI_HRX&t;&t;&t;(32 + 0)
DECL|macro|SK_PNMI_HRX_OCTET
mdefine_line|#define SK_PNMI_HRX_OCTET&t;&t;(32 + 1)
DECL|macro|SK_PNMI_HRX_OCTETHIGH
mdefine_line|#define SK_PNMI_HRX_OCTETHIGH&t;&t;(32 + 1)
DECL|macro|SK_PNMI_HRX_OCTETLOW
mdefine_line|#define SK_PNMI_HRX_OCTETLOW&t;&t;(32 + 2)
DECL|macro|SK_PNMI_HRX_BROADCAST
mdefine_line|#define SK_PNMI_HRX_BROADCAST&t;&t;(32 + 3)
DECL|macro|SK_PNMI_HRX_MULTICAST
mdefine_line|#define SK_PNMI_HRX_MULTICAST&t;&t;(32 + 4)
DECL|macro|SK_PNMI_HRX_UNICAST
mdefine_line|#define SK_PNMI_HRX_UNICAST&t;&t;(32 + 5)
DECL|macro|SK_PNMI_HRX_PMACC
mdefine_line|#define SK_PNMI_HRX_PMACC&t;&t;(32 + 6)
DECL|macro|SK_PNMI_HRX_MACC
mdefine_line|#define SK_PNMI_HRX_MACC&t;&t;(32 + 7)
DECL|macro|SK_PNMI_HRX_PMACC_ERR
mdefine_line|#define SK_PNMI_HRX_PMACC_ERR&t;&t;(32 + 8)
DECL|macro|SK_PNMI_HRX_MACC_UNKWN
mdefine_line|#define SK_PNMI_HRX_MACC_UNKWN&t;&t;(32 + 9)
DECL|macro|SK_PNMI_HRX_BURST
mdefine_line|#define SK_PNMI_HRX_BURST&t;&t;(32 + 10)
DECL|macro|SK_PNMI_HRX_MISSED
mdefine_line|#define SK_PNMI_HRX_MISSED&t;&t;(32 + 11)
DECL|macro|SK_PNMI_HRX_FRAMING
mdefine_line|#define SK_PNMI_HRX_FRAMING&t;&t;(32 + 12)
DECL|macro|SK_PNMI_HRX_OVERFLOW
mdefine_line|#define SK_PNMI_HRX_OVERFLOW&t;&t;(32 + 13)
DECL|macro|SK_PNMI_HRX_JABBER
mdefine_line|#define SK_PNMI_HRX_JABBER&t;&t;(32 + 14)
DECL|macro|SK_PNMI_HRX_CARRIER
mdefine_line|#define SK_PNMI_HRX_CARRIER&t;&t;(32 + 15)
DECL|macro|SK_PNMI_HRX_IRLENGTH
mdefine_line|#define SK_PNMI_HRX_IRLENGTH&t;&t;(32 + 16)
DECL|macro|SK_PNMI_HRX_SYMBOL
mdefine_line|#define SK_PNMI_HRX_SYMBOL&t;&t;(32 + 17)
DECL|macro|SK_PNMI_HRX_SHORTS
mdefine_line|#define SK_PNMI_HRX_SHORTS&t;&t;(32 + 18)
DECL|macro|SK_PNMI_HRX_RUNT
mdefine_line|#define SK_PNMI_HRX_RUNT&t;&t;(32 + 19)
DECL|macro|SK_PNMI_HRX_TOO_LONG
mdefine_line|#define SK_PNMI_HRX_TOO_LONG&t;&t;(32 + 20)
DECL|macro|SK_PNMI_HRX_FCS
mdefine_line|#define SK_PNMI_HRX_FCS&t;&t;&t;(32 + 21)
DECL|macro|SK_PNMI_HRX_RESERVED22
mdefine_line|#define SK_PNMI_HRX_RESERVED22&t;&t;(32 + 22)
DECL|macro|SK_PNMI_HRX_CEXT
mdefine_line|#define SK_PNMI_HRX_CEXT&t;&t;(32 + 23)
DECL|macro|SK_PNMI_HRX_UTILUNDER
mdefine_line|#define SK_PNMI_HRX_UTILUNDER&t;&t;(32 + 24)
DECL|macro|SK_PNMI_HRX_UTILOVER
mdefine_line|#define SK_PNMI_HRX_UTILOVER&t;&t;(32 + 25)
DECL|macro|SK_PNMI_HRX_64
mdefine_line|#define SK_PNMI_HRX_64&t;&t;&t;(32 + 26)
DECL|macro|SK_PNMI_HRX_127
mdefine_line|#define SK_PNMI_HRX_127&t;&t;&t;(32 + 27)
DECL|macro|SK_PNMI_HRX_255
mdefine_line|#define SK_PNMI_HRX_255&t;&t;&t;(32 + 28)
DECL|macro|SK_PNMI_HRX_511
mdefine_line|#define SK_PNMI_HRX_511&t;&t;&t;(32 + 29)
DECL|macro|SK_PNMI_HRX_1023
mdefine_line|#define SK_PNMI_HRX_1023&t;&t;(32 + 30)
DECL|macro|SK_PNMI_HRX_MAX
mdefine_line|#define SK_PNMI_HRX_MAX&t;&t;&t;(32 + 31)
DECL|macro|SK_PNMI_HTX_SYNC
mdefine_line|#define SK_PNMI_HTX_SYNC&t;&t;64
DECL|macro|SK_PNMI_HTX_SYNC_OCTET
mdefine_line|#define SK_PNMI_HTX_SYNC_OCTET&t;&t;65
DECL|macro|SK_PNMI_HRX_LONGFRAMES
mdefine_line|#define SK_PNMI_HRX_LONGFRAMES&t;&t;66
DECL|macro|SK_PNMI_MAX_IDX
mdefine_line|#define SK_PNMI_MAX_IDX&t;&t;&t;(SK_PNMI_CNT_NO)
multiline_comment|/*&n; * MAC specific data&n; */
DECL|struct|s_PnmiStatAddr
r_typedef
r_struct
id|s_PnmiStatAddr
(brace
DECL|member|GetOffset
id|SK_BOOL
id|GetOffset
suffix:semicolon
multiline_comment|/* TRUE: Call GetStatVal function */
DECL|member|Param
id|SK_U16
id|Param
suffix:semicolon
multiline_comment|/* XMAC register containing value */
DECL|typedef|SK_PNMI_STATADDR
)brace
id|SK_PNMI_STATADDR
suffix:semicolon
multiline_comment|/*&n; * SK_PNMI_STRUCT_DATA copy offset evaluation macros&n; */
DECL|macro|SK_PNMI_OFF
mdefine_line|#define SK_PNMI_OFF(e)&t;&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_STRUCT_DATA *)0)-&gt;e))
DECL|macro|SK_PNMI_MAI_OFF
mdefine_line|#define SK_PNMI_MAI_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_STRUCT_DATA *)0)-&gt;e))
DECL|macro|SK_PNMI_VPD_OFF
mdefine_line|#define SK_PNMI_VPD_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_VPD *)0)-&gt;e))
DECL|macro|SK_PNMI_SEN_OFF
mdefine_line|#define SK_PNMI_SEN_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_SENSOR *)0)-&gt;e))
DECL|macro|SK_PNMI_CHK_OFF
mdefine_line|#define SK_PNMI_CHK_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_CHECKSUM *)0)-&gt;e))
DECL|macro|SK_PNMI_STA_OFF
mdefine_line|#define SK_PNMI_STA_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_STAT *)0)-&gt;e))
DECL|macro|SK_PNMI_CNF_OFF
mdefine_line|#define SK_PNMI_CNF_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_CONF *)0)-&gt;e))
DECL|macro|SK_PNMI_RLM_OFF
mdefine_line|#define SK_PNMI_RLM_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_RLMT *)0)-&gt;e))
DECL|macro|SK_PNMI_MON_OFF
mdefine_line|#define SK_PNMI_MON_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_RLMT_MONITOR *)0)-&gt;e))
DECL|macro|SK_PNMI_TRP_OFF
mdefine_line|#define SK_PNMI_TRP_OFF(e)&t;((SK_U32)(SK_UPTR)&amp;(((SK_PNMI_TRAP *)0)-&gt;e))
DECL|macro|SK_PNMI_SET_STAT
mdefine_line|#define SK_PNMI_SET_STAT(b,s,o)&t;{SK_U32&t;Val32; char *pVal; &bslash;&n;&t;&t;&t;&t;&t;Val32 = (s); &bslash;&n;&t;&t;&t;&t;&t;pVal = (char *)(b) + ((SK_U32)(SK_UPTR) &bslash;&n;&t;&t;&t;&t;&t;&t;&amp;(((SK_PNMI_STRUCT_DATA *)0)-&gt; &bslash;&n;&t;&t;&t;&t;&t;&t;ReturnStatus.ErrorStatus)); &bslash;&n;&t;&t;&t;&t;&t;SK_PNMI_STORE_U32(pVal, Val32); &bslash;&n;&t;&t;&t;&t;&t;Val32 = (o); &bslash;&n;&t;&t;&t;&t;&t;pVal = (char *)(b) + ((SK_U32)(SK_UPTR) &bslash;&n;&t;&t;&t;&t;&t;&t;&amp;(((SK_PNMI_STRUCT_DATA *)0)-&gt; &bslash;&n;&t;&t;&t;&t;&t;&t;ReturnStatus.ErrorOffset)); &bslash;&n;&t;&t;&t;&t;&t;SK_PNMI_STORE_U32(pVal, Val32);}
multiline_comment|/*&n; * Time macros&n; */
macro_line|#if SK_TICKS_PER_SEC == 100
DECL|macro|SK_PNMI_HUNDREDS_SEC
mdefine_line|#define SK_PNMI_HUNDREDS_SEC(t)&t;(t)
macro_line|#else
DECL|macro|SK_PNMI_HUNDREDS_SEC
mdefine_line|#define SK_PNMI_HUNDREDS_SEC(t)&t;(((t) * 100) / (SK_TICKS_PER_SEC))
macro_line|#endif
multiline_comment|/*&n; * Macros to work around alignment problems&n; */
macro_line|#ifndef SK_PNMI_STORE_U16
DECL|macro|SK_PNMI_STORE_U16
mdefine_line|#define SK_PNMI_STORE_U16(p,v)&t;{*(char *)(p) = *((char *)&amp;(v)); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 1) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 1);}
macro_line|#endif
macro_line|#ifndef SK_PNMI_STORE_U32
DECL|macro|SK_PNMI_STORE_U32
mdefine_line|#define SK_PNMI_STORE_U32(p,v)&t;{*(char *)(p) = *((char *)&amp;(v)); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 1) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 1); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 2) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 2); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 3) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 3);}
macro_line|#endif
macro_line|#ifndef SK_PNMI_STORE_U64
DECL|macro|SK_PNMI_STORE_U64
mdefine_line|#define SK_PNMI_STORE_U64(p,v)&t;{*(char *)(p) = *((char *)&amp;(v)); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 1) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 1); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 2) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 2); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 3) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 3); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 4) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 4); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 5) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 5); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 6) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 6); &bslash;&n;&t;&t;&t;&t;&t;*((char *)(p) + 7) = &bslash;&n;&t;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 7);}
macro_line|#endif
macro_line|#ifndef SK_PNMI_READ_U16
DECL|macro|SK_PNMI_READ_U16
mdefine_line|#define SK_PNMI_READ_U16(p,v)&t;{*((char *)&amp;(v)) = *(char *)(p); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 1) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 1);}
macro_line|#endif
macro_line|#ifndef SK_PNMI_READ_U32
DECL|macro|SK_PNMI_READ_U32
mdefine_line|#define SK_PNMI_READ_U32(p,v)&t;{*((char *)&amp;(v)) = *(char *)(p); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 1) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 1); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 2) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 2); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 3) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 3);}
macro_line|#endif
macro_line|#ifndef SK_PNMI_READ_U64
DECL|macro|SK_PNMI_READ_U64
mdefine_line|#define SK_PNMI_READ_U64(p,v)&t;{*((char *)&amp;(v)) = *(char *)(p); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 1) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 1); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 2) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 2); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 3) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 3); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 4) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 4); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 5) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 5); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 6) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 6); &bslash;&n;&t;&t;&t;&t;&t;*(((char *)&amp;(v)) + 7) = &bslash;&n;&t;&t;&t;&t;&t;&t;*((char *)(p) + 7);}
macro_line|#endif
multiline_comment|/*&n; * Macros for Debug&n; */
macro_line|#ifdef DEBUG
DECL|macro|SK_PNMI_CHECKFLAGS
mdefine_line|#define SK_PNMI_CHECKFLAGS(vSt)&t;{if (pAC-&gt;Pnmi.MacUpdatedFlag &gt; 0 || &bslash;&n;&t;&t;&t;&t;&t;pAC-&gt;Pnmi.RlmtUpdatedFlag &gt; 0 || &bslash;&n;&t;&t;&t;&t;&t;pAC-&gt;Pnmi.SirqUpdatedFlag &gt; 0) { &bslash;&n;&t;&t;&t;&t;&t;&t;SK_DBG_MSG(pAC, &bslash;&n;&t;&t;&t;&t;&t;&t;SK_DBGMOD_PNMI, &bslash;&n;&t;&t;&t;&t;&t;&t;SK_DBGCAT_CTRL,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;(&quot;PNMI: ERR: %s MacUFlag=%d, RlmtUFlag=%d, SirqUFlag=%d&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;&t;vSt, &bslash;&n;&t;&t;&t;&t;&t;&t;pAC-&gt;Pnmi.MacUpdatedFlag, &bslash;&n;&t;&t;&t;&t;&t;&t;pAC-&gt;Pnmi.RlmtUpdatedFlag, &bslash;&n;&t;&t;&t;&t;&t;&t;pAC-&gt;Pnmi.SirqUpdatedFlag))}}
macro_line|#else&t;/* !DEBUG */
DECL|macro|SK_PNMI_CHECKFLAGS
mdefine_line|#define SK_PNMI_CHECKFLAGS(vSt)&t;/* Nothing */
macro_line|#endif&t;/* !DEBUG */
macro_line|#endif&t;/* _SKGEPNM2_H_ */
eof
