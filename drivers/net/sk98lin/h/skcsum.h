multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skcsum.h&n; * Project:&t;GEnesis - SysKonnect SK-NET Gigabit Ethernet (SK-98xx)&n; * Version:&t;$Revision: 1.9 $&n; * Date:&t;$Date: 2001/02/06 11:21:39 $&n; * Purpose:&t;Store/verify Internet checksum in send/receive packets.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2001 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skcsum.h,v $&n; *&t;Revision 1.9  2001/02/06 11:21:39  rassmann&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.8  2001/02/06 11:15:36  rassmann&n; *&t;Supporting two nets on dual-port adapters.&n; *&t;&n; *&t;Revision 1.7  2000/06/29 13:17:05  rassmann&n; *&t;Corrected reception of a packet with UDP checksum == 0 (which means there&n; *&t;is no UDP checksum).&n; *&t;&n; *&t;Revision 1.6  2000/02/28 12:33:44  cgoos&n; *&t;Changed C++ style comments to C style.&n; *&t;&n; *&t;Revision 1.5  2000/02/21 12:10:05  cgoos&n; *&t;Fixed license comment.&n; *&t;&n; *&t;Revision 1.4  2000/02/21 11:08:37  cgoos&n; *&t;Merged changes back into common source.&n; *&t;&n; *&t;Revision 1.1  1999/07/26 14:47:49  mkarl&n; *&t;changed from common source to windows specific source&n; *&t;added return SKCS_STATUS_IP_CSUM_ERROR_UDP and&n; *&t;SKCS_STATUS_IP_CSUM_ERROR_TCP to pass the NidsTester&n; *&t;changes for Tx csum offload&n; *&t;&n; *&t;Revision 1.2  1998/09/04 12:16:34  mhaveman&n; *&t;Checked in for Stephan to allow compilation.&n; *&t;-Added definition SK_CSUM_EVENT_CLEAR_PROTO_STATS to clear statistic&n; *&t;-Added prototype for SkCsEvent()&n; *&t;&n; *&t;Revision 1.1  1998/09/01 15:36:53  swolf&n; *&t;initial revision&n; *&n; *&t;01-Sep-1998 sw&t;Created.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * Public header file for the &quot;GEnesis&quot; common module &quot;CSUM&quot;.&n; *&n; * &quot;GEnesis&quot; is an abbreviation of &quot;Gigabit Ethernet Network System in Silicon&quot;&n; * and is the code name of this SysKonnect project.&n; *&n; * Compilation Options:&n; *&n; *&t;SK_USE_CSUM - Define if CSUM is to be used. Otherwise, CSUM will be an&n; *&t;empty module.&n; *&n; *&t;SKCS_OVERWRITE_PROTO - Define to overwrite the default protocol id&n; *&t;definitions. In this case, all SKCS_PROTO_xxx definitions must be made&n; *&t;external.&n; *&n; *&t;SKCS_OVERWRITE_STATUS - Define to overwrite the default return status&n; *&t;definitions. In this case, all SKCS_STATUS_xxx definitions must be made&n; *&t;external.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;&quot;h/skcsum.h&quot;&n; *&t; &quot;h/sktypes.h&quot;&n; *&t; &quot;h/skqueue.h&quot;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKCSUM_H
DECL|macro|__INC_SKCSUM_H
mdefine_line|#define __INC_SKCSUM_H
macro_line|#include &quot;h/sktypes.h&quot;
macro_line|#include &quot;h/skqueue.h&quot;
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * Define the default bit flags for &squot;SKCS_PACKET_INFO.ProtocolFlags&squot;  if no user&n; * overwrite.&n; */
macro_line|#ifndef SKCS_OVERWRITE_PROTO&t;/* User overwrite? */
DECL|macro|SKCS_PROTO_IP
mdefine_line|#define SKCS_PROTO_IP&t;0x1&t;/* IP (Internet Protocol version 4) */
DECL|macro|SKCS_PROTO_TCP
mdefine_line|#define SKCS_PROTO_TCP&t;0x2&t;/* TCP (Transmission Control Protocol) */
DECL|macro|SKCS_PROTO_UDP
mdefine_line|#define SKCS_PROTO_UDP&t;0x4&t;/* UDP (User Datagram Protocol) */
multiline_comment|/* Indices for protocol statistics. */
DECL|macro|SKCS_PROTO_STATS_IP
mdefine_line|#define SKCS_PROTO_STATS_IP&t;0
DECL|macro|SKCS_PROTO_STATS_UDP
mdefine_line|#define SKCS_PROTO_STATS_UDP&t;1
DECL|macro|SKCS_PROTO_STATS_TCP
mdefine_line|#define SKCS_PROTO_STATS_TCP&t;2
DECL|macro|SKCS_NUM_PROTOCOLS
mdefine_line|#define SKCS_NUM_PROTOCOLS&t;3&t;/* Number of supported protocols. */
macro_line|#endif&t;/* !SKCS_OVERWRITE_PROTO */
multiline_comment|/*&n; * Define the default SKCS_STATUS type and values if no user overwrite.&n; *&n; *&t;SKCS_STATUS_UNKNOWN_IP_VERSION - Not an IP v4 frame.&n; *&t;SKCS_STATUS_IP_CSUM_ERROR - IP checksum error.&n; *&t;SKCS_STATUS_IP_CSUM_ERROR_TCP - IP checksum error in TCP frame.&n; *&t;SKCS_STATUS_IP_CSUM_ERROR_UDP - IP checksum error in UDP frame&n; *&t;SKCS_STATUS_IP_FRAGMENT - IP fragment (IP checksum ok).&n; *&t;SKCS_STATUS_IP_CSUM_OK - IP checksum ok (not a TCP or UDP frame).&n; *&t;SKCS_STATUS_TCP_CSUM_ERROR - TCP checksum error (IP checksum ok).&n; *&t;SKCS_STATUS_UDP_CSUM_ERROR - UDP checksum error (IP checksum ok).&n; *&t;SKCS_STATUS_TCP_CSUM_OK - IP and TCP checksum ok.&n; *&t;SKCS_STATUS_UDP_CSUM_OK - IP and UDP checksum ok.&n; *&t;SKCS_STATUS_IP_CSUM_OK_NO_UDP - IP checksum OK and no UDP checksum. &n; */
macro_line|#ifndef SKCS_OVERWRITE_STATUS&t;/* User overwrite? */
DECL|macro|SKCS_STATUS
mdefine_line|#define SKCS_STATUS&t;int&t;/* Define status type. */
DECL|macro|SKCS_STATUS_UNKNOWN_IP_VERSION
mdefine_line|#define SKCS_STATUS_UNKNOWN_IP_VERSION&t;1
DECL|macro|SKCS_STATUS_IP_CSUM_ERROR
mdefine_line|#define SKCS_STATUS_IP_CSUM_ERROR&t;&t;2
DECL|macro|SKCS_STATUS_IP_FRAGMENT
mdefine_line|#define SKCS_STATUS_IP_FRAGMENT&t;&t;&t;3
DECL|macro|SKCS_STATUS_IP_CSUM_OK
mdefine_line|#define SKCS_STATUS_IP_CSUM_OK&t;&t;&t;4
DECL|macro|SKCS_STATUS_TCP_CSUM_ERROR
mdefine_line|#define SKCS_STATUS_TCP_CSUM_ERROR&t;&t;5
DECL|macro|SKCS_STATUS_UDP_CSUM_ERROR
mdefine_line|#define SKCS_STATUS_UDP_CSUM_ERROR&t;&t;6
DECL|macro|SKCS_STATUS_TCP_CSUM_OK
mdefine_line|#define SKCS_STATUS_TCP_CSUM_OK&t;&t;&t;7
DECL|macro|SKCS_STATUS_UDP_CSUM_OK
mdefine_line|#define SKCS_STATUS_UDP_CSUM_OK&t;&t;&t;8
multiline_comment|/* needed for Microsoft */
DECL|macro|SKCS_STATUS_IP_CSUM_ERROR_UDP
mdefine_line|#define SKCS_STATUS_IP_CSUM_ERROR_UDP&t;9
DECL|macro|SKCS_STATUS_IP_CSUM_ERROR_TCP
mdefine_line|#define SKCS_STATUS_IP_CSUM_ERROR_TCP&t;10
multiline_comment|/* UDP checksum may be omitted */
DECL|macro|SKCS_STATUS_IP_CSUM_OK_NO_UDP
mdefine_line|#define SKCS_STATUS_IP_CSUM_OK_NO_UDP&t;11
macro_line|#endif&t;/* !SKCS_OVERWRITE_STATUS */
multiline_comment|/* Clear protocol statistics event. */
DECL|macro|SK_CSUM_EVENT_CLEAR_PROTO_STATS
mdefine_line|#define SK_CSUM_EVENT_CLEAR_PROTO_STATS&t;1
multiline_comment|/*&n; * Add two values in one&squot;s complement.&n; *&n; * Note: One of the two input values may be &quot;longer&quot; than 16-bit, but then the&n; * resulting sum may be 17 bits long. In this case, add zero to the result using&n; * SKCS_OC_ADD() again.&n; *&n; *&t;Result = Value1 + Value2&n; */
DECL|macro|SKCS_OC_ADD
mdefine_line|#define SKCS_OC_ADD(Result, Value1, Value2) {&t;&t;&t;&t;&bslash;&n;&t;unsigned long Sum;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Sum = (unsigned long) (Value1) + (unsigned long) (Value2);&t;&bslash;&n;&t;/* Add-in any carry. */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(Result) = (Sum &amp; 0xffff) + (Sum &gt;&gt; 16);&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Subtract two values in one&squot;s complement.&n; *&n; *&t;Result = Value1 - Value2&n; */
DECL|macro|SKCS_OC_SUB
mdefine_line|#define SKCS_OC_SUB(Result, Value1, Value2)&t;&bslash;&n;&t;SKCS_OC_ADD((Result), (Value1), ~(Value2) &amp; 0xffff)
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/*&n; * SKCS_PROTO_STATS - The CSUM protocol statistics structure.&n; *&n; * There is one instance of this structure for each protocol supported.&n; */
DECL|struct|s_CsProtocolStatistics
r_typedef
r_struct
id|s_CsProtocolStatistics
(brace
DECL|member|RxOkCts
id|SK_U64
id|RxOkCts
suffix:semicolon
multiline_comment|/* Receive checksum ok. */
DECL|member|RxUnableCts
id|SK_U64
id|RxUnableCts
suffix:semicolon
multiline_comment|/* Unable to verify receive checksum. */
DECL|member|RxErrCts
id|SK_U64
id|RxErrCts
suffix:semicolon
multiline_comment|/* Receive checksum error. */
DECL|member|TxOkCts
id|SK_U64
id|TxOkCts
suffix:semicolon
multiline_comment|/* Transmit checksum ok. */
DECL|member|TxUnableCts
id|SK_U64
id|TxUnableCts
suffix:semicolon
multiline_comment|/* Unable to calculate checksum in hw. */
DECL|typedef|SKCS_PROTO_STATS
)brace
id|SKCS_PROTO_STATS
suffix:semicolon
multiline_comment|/*&n; * s_Csum - The CSUM module context structure.&n; */
DECL|struct|s_Csum
r_typedef
r_struct
id|s_Csum
(brace
multiline_comment|/* Enabled receive SK_PROTO_XXX bit flags. */
DECL|member|ReceiveFlags
r_int
id|ReceiveFlags
(braket
id|SK_MAX_NETS
)braket
suffix:semicolon
macro_line|#ifdef TX_CSUM
DECL|member|TransmitFlags
r_int
id|TransmitFlags
(braket
id|SK_MAX_NETS
)braket
suffix:semicolon
macro_line|#endif /* TX_CSUM */
multiline_comment|/* The protocol statistics structure; one per supported protocol. */
DECL|member|ProtoStats
id|SKCS_PROTO_STATS
id|ProtoStats
(braket
id|SK_MAX_NETS
)braket
(braket
id|SKCS_NUM_PROTOCOLS
)braket
suffix:semicolon
DECL|typedef|SK_CSUM
)brace
id|SK_CSUM
suffix:semicolon
multiline_comment|/*&n; * SKCS_PACKET_INFO - The packet information structure.&n; */
DECL|struct|s_CsPacketInfo
r_typedef
r_struct
id|s_CsPacketInfo
(brace
multiline_comment|/* Bit field specifiying the desired/found protocols. */
DECL|member|ProtocolFlags
r_int
id|ProtocolFlags
suffix:semicolon
multiline_comment|/* Length of complete IP header, including any option fields. */
DECL|member|IpHeaderLength
r_int
id|IpHeaderLength
suffix:semicolon
multiline_comment|/* IP header checksum. */
DECL|member|IpHeaderChecksum
r_int
id|IpHeaderChecksum
suffix:semicolon
multiline_comment|/* TCP/UDP pseudo header checksum. */
DECL|member|PseudoHeaderChecksum
r_int
id|PseudoHeaderChecksum
suffix:semicolon
DECL|typedef|SKCS_PACKET_INFO
)brace
id|SKCS_PACKET_INFO
suffix:semicolon
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifndef SkCsCalculateChecksum
r_extern
r_int
id|SkCsCalculateChecksum
c_func
(paren
r_void
op_star
id|pData
comma
r_int
id|Length
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|SkCsEvent
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
id|SK_IOC
id|Ioc
comma
id|SK_U32
id|Event
comma
id|SK_EVPARA
id|Param
)paren
suffix:semicolon
r_extern
id|SKCS_STATUS
id|SkCsGetReceiveInfo
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
r_void
op_star
id|pIpHeader
comma
r_int
id|Checksum1
comma
r_int
id|Checksum2
comma
r_int
id|NetNumber
)paren
suffix:semicolon
r_extern
r_void
id|SkCsGetSendInfo
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
r_void
op_star
id|pIpHeader
comma
id|SKCS_PACKET_INFO
op_star
id|pPacketInfo
comma
r_int
id|NetNumber
)paren
suffix:semicolon
r_extern
r_void
id|SkCsSetReceiveFlags
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
r_int
id|ReceiveFlags
comma
r_int
op_star
id|pChecksum1Offset
comma
r_int
op_star
id|pChecksum2Offset
comma
r_int
id|NetNumber
)paren
suffix:semicolon
macro_line|#endif&t;/* __INC_SKCSUM_H */
eof
