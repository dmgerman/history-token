multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skcsum.c&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.7 $&n; * Date:&t;$Date: 2000/06/29 13:17:05 $&n; * Purpose:&t;Store/verify Internet checksum in send/receive packets.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2000 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skcsum.c,v $&n; *&t;Revision 1.7  2000/06/29 13:17:05  rassmann&n; *&t;Corrected reception of a packet with UDP checksum == 0 (which means there&n; *&t;is no UDP checksum).&n; *&t;&n; *&t;Revision 1.6  2000/02/21 12:35:10  cgoos&n; *&t;Fixed license header comment.&n; *&t;&n; *&t;Revision 1.5  2000/02/21 11:05:19  cgoos&n; *&t;Merged changes back to common source.&n; *&t;Fixed rx path for BIG ENDIAN architecture.&n; *&t;&n; *&t;Revision 1.1  1999/07/26 15:28:12  mkarl&n; *&t;added return SKCS_STATUS_IP_CSUM_ERROR_UDP and&n; *&t;SKCS_STATUS_IP_CSUM_ERROR_TCP to pass the NidsTester&n; *&t;changed from common source to windows specific source&n; *&t;therefore restarting with v1.0&n; *&t;&n; *&t;Revision 1.3  1999/05/10 08:39:33  mkarl&n; *&t;prevent overflows in SKCS_HTON16&n; *&t;fixed a bug in pseudo header checksum calculation&n; *&t;added some comments&n; *&t;&n; *&t;Revision 1.2  1998/10/22 11:53:28  swolf&n; *&t;Now using SK_DBG_MSG.&n; *&t;&n; *&t;Revision 1.1  1998/09/01 15:35:41  swolf&n; *&t;initial revision&n; *&n; *&t;13-May-1998 sw&t;Created.&n; *&n; ******************************************************************************/
macro_line|#ifdef SK_USE_CSUM&t;/* Check if CSUM is to be used. */
macro_line|#ifndef lint
DECL|variable|SysKonnectFileId
r_static
r_const
r_char
id|SysKonnectFileId
(braket
)braket
op_assign
l_string|&quot;@(#)&quot;
l_string|&quot;$Id: skcsum.c,v 1.7 2000/06/29 13:17:05 rassmann Exp $&quot;
l_string|&quot; (C) SysKonnect.&quot;
suffix:semicolon
macro_line|#endif&t;/* !lint */
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * This is the &quot;GEnesis&quot; common module &quot;CSUM&quot;.&n; *&n; * This module contains the code necessary to calculate, store, and verify the&n; * Internet Checksum of IP, TCP, and UDP frames.&n; *&n; * &quot;GEnesis&quot; is an abbreviation of &quot;Gigabit Ethernet Network System in Silicon&quot;&n; * and is the code name of this SysKonnect project.&n; *&n; * Compilation Options:&n; *&n; *&t;SK_USE_CSUM - Define if CSUM is to be used. Otherwise, CSUM will be an&n; *&t;empty module.&n; *&n; *&t;SKCS_OVERWRITE_PROTO - Define to overwrite the default protocol id&n; *&t;definitions. In this case, all SKCS_PROTO_xxx definitions must be made&n; *&t;external.&n; *&n; *&t;SKCS_OVERWRITE_STATUS - Define to overwrite the default return status&n; *&t;definitions. In this case, all SKCS_STATUS_xxx definitions must be made&n; *&t;external.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;&quot;h/skdrv1st.h&quot;&n; *&t;&quot;h/skcsum.h&quot;&n; *&t; &quot;h/sktypes.h&quot;&n; *&t; &quot;h/skqueue.h&quot;&n; *&t;&quot;h/skdrv2nd.h&quot;&n; *&n; ******************************************************************************/
macro_line|#include &quot;h/skdrv1st.h&quot;
macro_line|#include &quot;h/skcsum.h&quot;
macro_line|#include &quot;h/skdrv2nd.h&quot;
multiline_comment|/* defines ********************************************************************/
multiline_comment|/* The size of an Ethernet MAC header. */
DECL|macro|SKCS_ETHERNET_MAC_HEADER_SIZE
mdefine_line|#define SKCS_ETHERNET_MAC_HEADER_SIZE&t;&t;&t;(6+6+2)
multiline_comment|/* The size of the used topology&squot;s MAC header. */
DECL|macro|SKCS_MAC_HEADER_SIZE
mdefine_line|#define&t;SKCS_MAC_HEADER_SIZE&t;SKCS_ETHERNET_MAC_HEADER_SIZE
multiline_comment|/* The size of the IP header without any option fields. */
DECL|macro|SKCS_IP_HEADER_SIZE
mdefine_line|#define SKCS_IP_HEADER_SIZE&t;&t;&t;&t;&t;&t;20
multiline_comment|/*&n; * Field offsets within the IP header.&n; */
multiline_comment|/* &quot;Internet Header Version&quot; and &quot;Length&quot;. */
DECL|macro|SKCS_OFS_IP_HEADER_VERSION_AND_LENGTH
mdefine_line|#define SKCS_OFS_IP_HEADER_VERSION_AND_LENGTH&t;0
multiline_comment|/* &quot;Total Length&quot;. */
DECL|macro|SKCS_OFS_IP_TOTAL_LENGTH
mdefine_line|#define SKCS_OFS_IP_TOTAL_LENGTH&t;&t;&t;&t;2
multiline_comment|/* &quot;Flags&quot; &quot;Fragment Offset&quot;. */
DECL|macro|SKCS_OFS_IP_FLAGS_AND_FRAGMENT_OFFSET
mdefine_line|#define SKCS_OFS_IP_FLAGS_AND_FRAGMENT_OFFSET&t;6
multiline_comment|/* &quot;Next Level Protocol&quot; identifier. */
DECL|macro|SKCS_OFS_IP_NEXT_LEVEL_PROTOCOL
mdefine_line|#define SKCS_OFS_IP_NEXT_LEVEL_PROTOCOL&t;&t;&t;9
multiline_comment|/* Source IP address. */
DECL|macro|SKCS_OFS_IP_SOURCE_ADDRESS
mdefine_line|#define SKCS_OFS_IP_SOURCE_ADDRESS&t;&t;&t;&t;12
multiline_comment|/* Destination IP address. */
DECL|macro|SKCS_OFS_IP_DESTINATION_ADDRESS
mdefine_line|#define SKCS_OFS_IP_DESTINATION_ADDRESS&t;&t;&t;16
multiline_comment|/*&n; * Field offsets within the UDP header.&n; */
multiline_comment|/* UDP checksum. */
DECL|macro|SKCS_OFS_UDP_CHECKSUM
mdefine_line|#define SKCS_OFS_UDP_CHECKSUM&t;&t;&t;&t;&t;6
multiline_comment|/* IP &quot;Next Level Protocol&quot; identifiers (see RFC 790). */
DECL|macro|SKCS_PROTO_ID_TCP
mdefine_line|#define SKCS_PROTO_ID_TCP&t;&t;6&t;/* Transport Control Protocol */
DECL|macro|SKCS_PROTO_ID_UDP
mdefine_line|#define SKCS_PROTO_ID_UDP&t;&t;17&t;/* User Datagram Protocol */
multiline_comment|/* IP &quot;Don&squot;t Fragment&quot; bit. */
DECL|macro|SKCS_IP_DONT_FRAGMENT
mdefine_line|#define SKCS_IP_DONT_FRAGMENT&t;SKCS_HTON16(0x4000)
multiline_comment|/* Add a byte offset to a pointer. */
DECL|macro|SKCS_IDX
mdefine_line|#define SKCS_IDX(pPtr, Ofs)&t;((void *) ((char *) (pPtr) + (Ofs)))
multiline_comment|/*&n; * Macros that convert host to network representation and vice versa, i.e.&n; * little/big endian conversion on little endian machines only.&n; */
macro_line|#ifdef SK_LITTLE_ENDIAN
DECL|macro|SKCS_HTON16
mdefine_line|#define SKCS_HTON16(Val16)&t;(((unsigned) (Val16) &gt;&gt; 8) | (((Val16) &amp; 0xFF) &lt;&lt; 8))
macro_line|#endif&t;/* SK_LITTLE_ENDIAN */
macro_line|#ifdef SK_BIG_ENDIAN
DECL|macro|SKCS_HTON16
mdefine_line|#define SKCS_HTON16(Val16)&t;(Val16)
macro_line|#endif&t;/* SK_BIG_ENDIAN */
DECL|macro|SKCS_NTOH16
mdefine_line|#define SKCS_NTOH16(Val16)&t;SKCS_HTON16(Val16)
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/* function prototypes ********************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;SkCsGetSendInfo - get checksum information for a send packet&n; *&n; * Description:&n; *&t;Get all checksum information necessary to send a TCP or UDP packet. The&n; *&t;function checks the IP header passed to it. If the high-level protocol&n; *&t;is either TCP or UDP the pseudo header checksum is calculated and&n; *&t;returned.&n; *&n; *&t;The function returns the total length of the IP header (including any&n; *&t;IP option fields), which is the same as the start offset of the IP data&n; *&t;which in turn is the start offset of the TCP or UDP header.&n; *&n; *&t;The function also returns the TCP or UDP pseudo header checksum, which&n; *&t;should be used as the start value for the hardware checksum calculation.&n; *&t;(Note that any actual pseudo header checksum can never calculate to&n; *&t;zero.)&n; *&n; * Note:&n; *&t;There is a bug in the ASIC whic may lead to wrong checksums.&n; *&n; * Arguments:&n; *&t;pAc - A pointer to the adapter context struct.&n; *&n; *&t;pIpHeader - Pointer to IP header. Must be at least the IP header *not*&n; *&t;including any option fields, i.e. at least 20 bytes.&n; *&n; *&t;Note: This pointer will be used to address 8-, 16-, and 32-bit&n; *&t;variables with the respective alignment offsets relative to the pointer.&n; *&t;Thus, the pointer should point to a 32-bit aligned address. If the&n; *&t;target system cannot address 32-bit variables on non 32-bit aligned&n; *&t;addresses, then the pointer *must* point to a 32-bit aligned address.&n; *&n; *&t;pPacketInfo - A pointer to the packet information structure for this&n; *&t;packet. Before calling this SkCsGetSendInfo(), the following field must&n; *&t;be initialized:&n; *&n; *&t;&t;ProtocolFlags - Initialize with any combination of&n; *&t;&t;SKCS_PROTO_XXX bit flags. SkCsGetSendInfo() will only work on&n; *&t;&t;the protocols specified here. Any protocol(s) not specified&n; *&t;&t;here will be ignored.&n; *&n; *&t;&t;Note: Only one checksum can be calculated in hardware. Thus, if&n; *&t;&t;SKCS_PROTO_IP is specified in the &squot;ProtocolFlags&squot;,&n; *&t;&t;SkCsGetSendInfo() must calculate the IP header checksum in&n; *&t;&t;software. It might be a better idea to have the calling&n; *&t;&t;protocol stack calculate the IP header checksum.&n; *&n; * Returns: N/A&n; *&t;On return, the following fields in &squot;pPacketInfo&squot; may or may not have&n; *&t;been filled with information, depending on the protocol(s) found in the&n; *&t;packet:&n; *&n; *&t;ProtocolFlags - Returns the SKCS_PROTO_XXX bit flags of the protocol(s)&n; *&t;that were both requested by the caller and actually found in the packet.&n; *&t;Protocol(s) not specified by the caller and/or not found in the packet&n; *&t;will have their respective SKCS_PROTO_XXX bit flags reset.&n; *&n; *&t;Note: For IP fragments, TCP and UDP packet information is ignored.&n; *&n; *&t;IpHeaderLength - The total length in bytes of the complete IP header&n; *&t;including any option fields is returned here. This is the start offset&n; *&t;of the IP data, i.e. the TCP or UDP header if present.&n; *&n; *&t;IpHeaderChecksum - If IP has been specified in the &squot;ProtocolFlags&squot;, the&n; *&t;16-bit Internet Checksum of the IP header is returned here. This value&n; *&t;is to be stored into the packet&squot;s &squot;IP Header Checksum&squot; field.&n; *&n; *&t;PseudoHeaderChecksum - If this is a TCP or UDP packet and if TCP or UDP&n; *&t;has been specified in the &squot;ProtocolFlags&squot;, the 16-bit Internet Checksum&n; *&t;of the TCP or UDP pseudo header is returned here.&n; */
DECL|function|SkCsGetSendInfo
r_void
id|SkCsGetSendInfo
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
multiline_comment|/* Adapter context struct. */
r_void
op_star
id|pIpHeader
comma
multiline_comment|/* IP header. */
id|SKCS_PACKET_INFO
op_star
id|pPacketInfo
)paren
multiline_comment|/* Packet information struct. */
(brace
multiline_comment|/* Internet Header Version found in IP header. */
r_int
id|InternetHeaderVersion
suffix:semicolon
multiline_comment|/* Length of the IP header as found in IP header. */
r_int
id|IpHeaderLength
suffix:semicolon
multiline_comment|/* Bit field specifiying the desired/found protocols. */
r_int
id|ProtocolFlags
suffix:semicolon
multiline_comment|/* Next level protocol identifier found in IP header. */
r_int
id|NextLevelProtocol
suffix:semicolon
multiline_comment|/* Length of IP data portion. */
r_int
id|IpDataLength
suffix:semicolon
multiline_comment|/* TCP/UDP pseudo header checksum. */
r_int
r_int
id|PseudoHeaderChecksum
suffix:semicolon
multiline_comment|/* Pointer to next level protocol statistics structure. */
id|SKCS_PROTO_STATS
op_star
id|NextLevelProtoStats
suffix:semicolon
multiline_comment|/* Temporary variable. */
r_int
id|Tmp
suffix:semicolon
id|Tmp
op_assign
op_star
(paren
id|SK_U8
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_HEADER_VERSION_AND_LENGTH
)paren
suffix:semicolon
multiline_comment|/* Get the Internet Header Version (IHV). */
multiline_comment|/* Note: The IHV is stored in the upper four bits. */
id|InternetHeaderVersion
op_assign
id|Tmp
op_rshift
l_int|4
suffix:semicolon
multiline_comment|/* Check the Internet Header Version. */
multiline_comment|/* Note: We currently only support IP version 4. */
r_if
c_cond
(paren
id|InternetHeaderVersion
op_ne
l_int|4
)paren
(brace
multiline_comment|/* IPv4? */
id|SK_DBG_MSG
c_func
(paren
id|pAc
comma
id|SK_DBGMOD_CSUM
comma
id|SK_DBGCAT_ERR
op_or
id|SK_DBGCAT_TX
comma
(paren
l_string|&quot;Tx: Unknown Internet Header Version %u.&bslash;n&quot;
comma
id|InternetHeaderVersion
)paren
)paren
suffix:semicolon
id|pPacketInfo-&gt;ProtocolFlags
op_assign
l_int|0
suffix:semicolon
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_IP
)braket
dot
id|TxUnableCts
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Get the IP header length (IHL). */
multiline_comment|/*&n;&t; * Note: The IHL is stored in the lower four bits as the number of&n;&t; * 4-byte words.&n;&t; */
id|IpHeaderLength
op_assign
(paren
id|Tmp
op_amp
l_int|0xf
)paren
op_star
l_int|4
suffix:semicolon
id|pPacketInfo-&gt;IpHeaderLength
op_assign
id|IpHeaderLength
suffix:semicolon
multiline_comment|/* Check the IP header length. */
multiline_comment|/* 04-Aug-1998 sw - Really check the IHL? Necessary? */
r_if
c_cond
(paren
id|IpHeaderLength
OL
l_int|5
op_star
l_int|4
)paren
(brace
id|SK_DBG_MSG
c_func
(paren
id|pAc
comma
id|SK_DBGMOD_CSUM
comma
id|SK_DBGCAT_ERR
op_or
id|SK_DBGCAT_TX
comma
(paren
l_string|&quot;Tx: Invalid IP Header Length %u.&bslash;n&quot;
comma
id|IpHeaderLength
)paren
)paren
suffix:semicolon
id|pPacketInfo-&gt;ProtocolFlags
op_assign
l_int|0
suffix:semicolon
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_IP
)braket
dot
id|TxUnableCts
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* This is an IPv4 frame with a header of valid length. */
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_IP
)braket
dot
id|TxOkCts
op_increment
suffix:semicolon
multiline_comment|/* Check if we should calculate the IP header checksum. */
id|ProtocolFlags
op_assign
id|pPacketInfo-&gt;ProtocolFlags
suffix:semicolon
r_if
c_cond
(paren
id|ProtocolFlags
op_amp
id|SKCS_PROTO_IP
)paren
(brace
id|pPacketInfo-&gt;IpHeaderChecksum
op_assign
id|SkCsCalculateChecksum
c_func
(paren
id|pIpHeader
comma
id|IpHeaderLength
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the next level protocol identifier. */
id|NextLevelProtocol
op_assign
op_star
(paren
id|SK_U8
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_NEXT_LEVEL_PROTOCOL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if this is a TCP or UDP frame and if we should calculate the&n;&t; * TCP/UDP pseudo header checksum.&n;&t; *&n;&t; * Also clear all protocol bit flags of protocols not present in the&n;&t; * frame.&n;&t; */
r_if
c_cond
(paren
(paren
id|ProtocolFlags
op_amp
id|SKCS_PROTO_TCP
)paren
op_ne
l_int|0
op_logical_and
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_TCP
)paren
(brace
multiline_comment|/* TCP/IP frame. */
id|ProtocolFlags
op_and_assign
id|SKCS_PROTO_TCP
op_or
id|SKCS_PROTO_IP
suffix:semicolon
id|NextLevelProtoStats
op_assign
op_amp
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_TCP
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|ProtocolFlags
op_amp
id|SKCS_PROTO_UDP
)paren
op_ne
l_int|0
op_logical_and
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_UDP
)paren
(brace
multiline_comment|/* UDP/IP frame. */
id|ProtocolFlags
op_and_assign
id|SKCS_PROTO_UDP
op_or
id|SKCS_PROTO_IP
suffix:semicolon
id|NextLevelProtoStats
op_assign
op_amp
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_UDP
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Either not a TCP or UDP frame and/or TCP/UDP processing not&n;&t;&t; * specified.&n;&t;&t; */
id|pPacketInfo-&gt;ProtocolFlags
op_assign
id|ProtocolFlags
op_amp
id|SKCS_PROTO_IP
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Check if this is an IP fragment. */
multiline_comment|/*&n;&t; * Note: An IP fragment has a non-zero &quot;Fragment Offset&quot; field and/or&n;&t; * the &quot;More Fragments&quot; bit set. Thus, if both the &quot;Fragment Offset&quot;&n;&t; * and the &quot;More Fragments&quot; are zero, it is *not* a fragment. We can&n;&t; * easily check both at the same time since they are in the same 16-bit&n;&t; * word.&n;&t; */
r_if
c_cond
(paren
(paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_FLAGS_AND_FRAGMENT_OFFSET
)paren
op_amp
op_complement
id|SKCS_IP_DONT_FRAGMENT
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* IP fragment; ignore all other protocols. */
id|pPacketInfo-&gt;ProtocolFlags
op_assign
id|ProtocolFlags
op_amp
id|SKCS_PROTO_IP
suffix:semicolon
id|NextLevelProtoStats-&gt;TxUnableCts
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Calculate the TCP/UDP pseudo header checksum.&n;&t; */
multiline_comment|/* Get total length of IP header and data. */
id|IpDataLength
op_assign
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_TOTAL_LENGTH
)paren
suffix:semicolon
multiline_comment|/* Get length of IP data portion. */
id|IpDataLength
op_assign
id|SKCS_NTOH16
c_func
(paren
id|IpDataLength
)paren
op_minus
id|IpHeaderLength
suffix:semicolon
multiline_comment|/* Calculate the sum of all pseudo header fields (16-bit). */
id|PseudoHeaderChecksum
op_assign
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_SOURCE_ADDRESS
op_plus
l_int|0
)paren
op_plus
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_SOURCE_ADDRESS
op_plus
l_int|2
)paren
op_plus
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_DESTINATION_ADDRESS
op_plus
l_int|0
)paren
op_plus
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_DESTINATION_ADDRESS
op_plus
l_int|2
)paren
op_plus
(paren
r_int
r_int
)paren
(paren
id|NextLevelProtocol
op_lshift
l_int|8
)paren
op_plus
(paren
r_int
r_int
)paren
id|SKCS_HTON16
c_func
(paren
id|IpDataLength
)paren
suffix:semicolon
multiline_comment|/* Add-in any carries. */
id|SKCS_OC_ADD
c_func
(paren
id|PseudoHeaderChecksum
comma
id|PseudoHeaderChecksum
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Add-in any new carry. */
id|SKCS_OC_ADD
c_func
(paren
id|pPacketInfo-&gt;PseudoHeaderChecksum
comma
id|PseudoHeaderChecksum
comma
l_int|0
)paren
suffix:semicolon
id|NextLevelProtoStats-&gt;TxOkCts
op_increment
suffix:semicolon
multiline_comment|/* Success. */
)brace
multiline_comment|/* SkCsGetSendInfo */
multiline_comment|/******************************************************************************&n; *&n; *&t;SkCsGetReceiveInfo - verify checksum information for a received packet&n; *&n; * Description:&n; *&t;Verify a received frame&squot;s checksum. The function returns a status code&n; *&t;reflecting the result of the verification.&n; *&n; * Note:&n; *&t;Before calling this function you have to verify that the frame is&n; *&t;not padded and Checksum1 and Checksum2 are bigger than 1.&n; *&n; * Arguments:&n; *&t;pAc - Pointer to adapter context struct.&n; *&n; *&t;pIpHeader - Pointer to IP header. Must be at least the length in bytes&n; *&t;of the received IP header including any option fields. For UDP packets,&n; *&t;8 additional bytes are needed to access the UDP checksum.&n; *&n; *&t;Note: The actual length of the IP header is stored in the lower four&n; *&t;bits of the first octet of the IP header as the number of 4-byte words,&n; *&t;so it must be multiplied by four to get the length in bytes. Thus, the&n; *&t;maximum IP header length is 15 * 4 = 60 bytes.&n; *&n; *&t;Checksum1 - The first 16-bit Internet Checksum calculated by the&n; *&t;hardware starting at the offset returned by SkCsSetReceiveFlags().&n; *&n; *&t;Checksum2 - The second 16-bit Internet Checksum calculated by the&n; *&t;hardware starting at the offset returned by SkCsSetReceiveFlags().&n; *&n; * Returns:&n; *&t;SKCS_STATUS_UNKNOWN_IP_VERSION - Not an IP v4 frame.&n; *&t;SKCS_STATUS_IP_CSUM_ERROR - IP checksum error.&n; *&t;SKCS_STATUS_IP_CSUM_ERROR_TCP - IP checksum error in TCP frame.&n; *&t;SKCS_STATUS_IP_CSUM_ERROR_UDP - IP checksum error in UDP frame&n; *&t;SKCS_STATUS_IP_FRAGMENT - IP fragment (IP checksum ok).&n; *&t;SKCS_STATUS_IP_CSUM_OK - IP checksum ok (not a TCP or UDP frame).&n; *&t;SKCS_STATUS_TCP_CSUM_ERROR - TCP checksum error (IP checksum ok).&n; *&t;SKCS_STATUS_UDP_CSUM_ERROR - UDP checksum error (IP checksum ok).&n; *&t;SKCS_STATUS_TCP_CSUM_OK - IP and TCP checksum ok.&n; *&t;SKCS_STATUS_UDP_CSUM_OK - IP and UDP checksum ok.&n; *&t;SKCS_STATUS_IP_CSUM_OK_NO_UDP - IP checksum OK and no UDP checksum.&n; *&n; *&t;Note: If SKCS_OVERWRITE_STATUS is defined, the SKCS_STATUS_XXX values&n; *&t;returned here can be defined in some header file by the module using CSUM.&n; *&t;In this way, the calling module can assign return values for its own needs,&n; *&t;e.g. by assigning bit flags to the individual protocols.&n; */
DECL|function|SkCsGetReceiveInfo
id|SKCS_STATUS
id|SkCsGetReceiveInfo
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
multiline_comment|/* Adapter context struct. */
r_void
op_star
id|pIpHeader
comma
multiline_comment|/* IP header. */
r_int
id|Checksum1
comma
multiline_comment|/* Hardware checksum 1. */
r_int
id|Checksum2
)paren
multiline_comment|/* Hardware checksum 2. */
(brace
multiline_comment|/* Internet Header Version found in IP header. */
r_int
id|InternetHeaderVersion
suffix:semicolon
multiline_comment|/* Length of the IP header as found in IP header. */
r_int
id|IpHeaderLength
suffix:semicolon
multiline_comment|/* Length of IP data portion. */
r_int
id|IpDataLength
suffix:semicolon
multiline_comment|/* IP header checksum. */
r_int
id|IpHeaderChecksum
suffix:semicolon
multiline_comment|/* IP header options checksum, if any. */
r_int
id|IpOptionsChecksum
suffix:semicolon
multiline_comment|/* IP data checksum, i.e. TCP/UDP checksum. */
r_int
id|IpDataChecksum
suffix:semicolon
multiline_comment|/* Next level protocol identifier found in IP header. */
r_int
id|NextLevelProtocol
suffix:semicolon
multiline_comment|/* The checksum of the &quot;next level protocol&quot;, i.e. TCP or UDP. */
r_int
r_int
id|NextLevelProtocolChecksum
suffix:semicolon
multiline_comment|/* Pointer to next level protocol statistics structure. */
id|SKCS_PROTO_STATS
op_star
id|NextLevelProtoStats
suffix:semicolon
multiline_comment|/* Temporary variable. */
r_int
id|Tmp
suffix:semicolon
id|Tmp
op_assign
op_star
(paren
id|SK_U8
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_HEADER_VERSION_AND_LENGTH
)paren
suffix:semicolon
multiline_comment|/* Get the Internet Header Version (IHV). */
multiline_comment|/* Note: The IHV is stored in the upper four bits. */
id|InternetHeaderVersion
op_assign
id|Tmp
op_rshift
l_int|4
suffix:semicolon
multiline_comment|/* Check the Internet Header Version. */
multiline_comment|/* Note: We currently only support IP version 4. */
r_if
c_cond
(paren
id|InternetHeaderVersion
op_ne
l_int|4
)paren
(brace
multiline_comment|/* IPv4? */
id|SK_DBG_MSG
c_func
(paren
id|pAc
comma
id|SK_DBGMOD_CSUM
comma
id|SK_DBGCAT_ERR
op_or
id|SK_DBGCAT_RX
comma
(paren
l_string|&quot;Rx: Unknown Internet Header Version %u.&bslash;n&quot;
comma
id|InternetHeaderVersion
)paren
)paren
suffix:semicolon
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_IP
)braket
dot
id|RxUnableCts
op_increment
suffix:semicolon
r_return
(paren
id|SKCS_STATUS_UNKNOWN_IP_VERSION
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the IP header length (IHL). */
multiline_comment|/*&n;&t; * Note: The IHL is stored in the lower four bits as the number of&n;&t; * 4-byte words.&n;&t; */
id|IpHeaderLength
op_assign
(paren
id|Tmp
op_amp
l_int|0xf
)paren
op_star
l_int|4
suffix:semicolon
multiline_comment|/* Check the IP header length. */
multiline_comment|/* 04-Aug-1998 sw - Really check the IHL? Necessary? */
r_if
c_cond
(paren
id|IpHeaderLength
OL
l_int|5
op_star
l_int|4
)paren
(brace
id|SK_DBG_MSG
c_func
(paren
id|pAc
comma
id|SK_DBGMOD_CSUM
comma
id|SK_DBGCAT_ERR
op_or
id|SK_DBGCAT_RX
comma
(paren
l_string|&quot;Rx: Invalid IP Header Length %u.&bslash;n&quot;
comma
id|IpHeaderLength
)paren
)paren
suffix:semicolon
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_IP
)braket
dot
id|RxErrCts
op_increment
suffix:semicolon
r_return
(paren
id|SKCS_STATUS_IP_CSUM_ERROR
)paren
suffix:semicolon
)brace
multiline_comment|/* This is an IPv4 frame with a header of valid length. */
multiline_comment|/* Get the IP header and data checksum. */
id|IpDataChecksum
op_assign
id|Checksum2
suffix:semicolon
multiline_comment|/*&n;&t; * The IP header checksum is calculated as follows:&n;&t; *&n;&t; *&t;IpHeaderChecksum = Checksum1 - Checksum2&n;&t; */
id|SKCS_OC_SUB
c_func
(paren
id|IpHeaderChecksum
comma
id|Checksum1
comma
id|Checksum2
)paren
suffix:semicolon
multiline_comment|/* Check if any IP header options. */
r_if
c_cond
(paren
id|IpHeaderLength
OG
id|SKCS_IP_HEADER_SIZE
)paren
(brace
multiline_comment|/* Get the IP options checksum. */
id|IpOptionsChecksum
op_assign
id|SkCsCalculateChecksum
c_func
(paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_IP_HEADER_SIZE
)paren
comma
id|IpHeaderLength
op_minus
id|SKCS_IP_HEADER_SIZE
)paren
suffix:semicolon
multiline_comment|/* Adjust the IP header and IP data checksums. */
id|SKCS_OC_ADD
c_func
(paren
id|IpHeaderChecksum
comma
id|IpHeaderChecksum
comma
id|IpOptionsChecksum
)paren
suffix:semicolon
id|SKCS_OC_SUB
c_func
(paren
id|IpDataChecksum
comma
id|IpDataChecksum
comma
id|IpOptionsChecksum
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check if the IP header checksum is ok.&n;&t; *&n;&t; * NOTE: We must check the IP header checksum even if the caller just wants&n;&t; * us to check upper-layer checksums, because we cannot do any further&n;&t; * processing of the packet without a valid IP checksum.&n;&t; */
multiline_comment|/* Get the next level protocol identifier. */
id|NextLevelProtocol
op_assign
op_star
(paren
id|SK_U8
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_NEXT_LEVEL_PROTOCOL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IpHeaderChecksum
op_ne
l_int|0xFFFF
)paren
(brace
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_IP
)braket
dot
id|RxErrCts
op_increment
suffix:semicolon
multiline_comment|/* the NDIS tester wants to know the upper level protocol too */
r_if
c_cond
(paren
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_TCP
)paren
(brace
r_return
id|SKCS_STATUS_IP_CSUM_ERROR_TCP
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_UDP
)paren
(brace
r_return
id|SKCS_STATUS_IP_CSUM_ERROR_UDP
suffix:semicolon
)brace
r_return
(paren
id|SKCS_STATUS_IP_CSUM_ERROR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check if this is a TCP or UDP frame and if we should calculate the&n;&t; * TCP/UDP pseudo header checksum.&n;&t; *&n;&t; * Also clear all protocol bit flags of protocols not present in the&n;&t; * frame.&n;&t; */
r_if
c_cond
(paren
(paren
id|pAc-&gt;Csum.ReceiveFlags
op_amp
id|SKCS_PROTO_TCP
)paren
op_ne
l_int|0
op_logical_and
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_TCP
)paren
(brace
multiline_comment|/* TCP/IP frame. */
id|NextLevelProtoStats
op_assign
op_amp
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_TCP
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|pAc-&gt;Csum.ReceiveFlags
op_amp
id|SKCS_PROTO_UDP
)paren
op_ne
l_int|0
op_logical_and
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_UDP
)paren
(brace
multiline_comment|/* UDP/IP frame. */
id|NextLevelProtoStats
op_assign
op_amp
id|pAc-&gt;Csum.ProtoStats
(braket
id|SKCS_PROTO_STATS_UDP
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Either not a TCP or UDP frame and/or TCP/UDP processing not&n;&t;&t; * specified.&n;&t;&t; */
r_return
(paren
id|SKCS_STATUS_IP_CSUM_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if this is an IP fragment. */
multiline_comment|/*&n;&t; * Note: An IP fragment has a non-zero &quot;Fragment Offset&quot; field and/or&n;&t; * the &quot;More Fragments&quot; bit set. Thus, if both the &quot;Fragment Offset&quot;&n;&t; * and the &quot;More Fragments&quot; are zero, it is *not* a fragment. We can&n;&t; * easily check both at the same time since they are in the same 16-bit&n;&t; * word.&n;&t; */
r_if
c_cond
(paren
(paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_FLAGS_AND_FRAGMENT_OFFSET
)paren
op_amp
op_complement
id|SKCS_IP_DONT_FRAGMENT
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* IP fragment; ignore all other protocols. */
id|NextLevelProtoStats-&gt;RxUnableCts
op_increment
suffix:semicolon
r_return
(paren
id|SKCS_STATUS_IP_FRAGMENT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * 08-May-2000 ra&n;&t; *&n;&t; * From RFC 768 (UDP)&n;&t; * If the computed checksum is zero, it is transmitted as all ones (the&n;&t; * equivalent in one&squot;s complement arithmetic).  An all zero transmitted&n;&t; * checksum value means that the transmitter generated no checksum (for&n;&t; * debugging or for higher level protocols that don&squot;t care).&n;&t; */
r_if
c_cond
(paren
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_UDP
op_logical_and
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|IpHeaderLength
op_plus
l_int|6
)paren
op_eq
l_int|0x0000
)paren
(brace
id|NextLevelProtoStats-&gt;RxOkCts
op_increment
suffix:semicolon
r_return
(paren
id|SKCS_STATUS_IP_CSUM_OK_NO_UDP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Calculate the TCP/UDP checksum.&n;&t; */
multiline_comment|/* Get total length of IP header and data. */
id|IpDataLength
op_assign
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_TOTAL_LENGTH
)paren
suffix:semicolon
multiline_comment|/* Get length of IP data portion. */
id|IpDataLength
op_assign
id|SKCS_NTOH16
c_func
(paren
id|IpDataLength
)paren
op_minus
id|IpHeaderLength
suffix:semicolon
id|NextLevelProtocolChecksum
op_assign
multiline_comment|/* Calculate the pseudo header checksum. */
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_SOURCE_ADDRESS
op_plus
l_int|0
)paren
op_plus
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_SOURCE_ADDRESS
op_plus
l_int|2
)paren
op_plus
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_DESTINATION_ADDRESS
op_plus
l_int|0
)paren
op_plus
(paren
r_int
r_int
)paren
op_star
(paren
id|SK_U16
op_star
)paren
id|SKCS_IDX
c_func
(paren
id|pIpHeader
comma
id|SKCS_OFS_IP_DESTINATION_ADDRESS
op_plus
l_int|2
)paren
op_plus
(paren
r_int
r_int
)paren
id|SKCS_HTON16
c_func
(paren
id|NextLevelProtocol
)paren
op_plus
(paren
r_int
r_int
)paren
id|SKCS_HTON16
c_func
(paren
id|IpDataLength
)paren
op_plus
multiline_comment|/* Add the TCP/UDP header checksum. */
(paren
r_int
r_int
)paren
id|IpDataChecksum
suffix:semicolon
multiline_comment|/* Add-in any carries. */
id|SKCS_OC_ADD
c_func
(paren
id|NextLevelProtocolChecksum
comma
id|NextLevelProtocolChecksum
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Add-in any new carry. */
id|SKCS_OC_ADD
c_func
(paren
id|NextLevelProtocolChecksum
comma
id|NextLevelProtocolChecksum
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Check if the TCP/UDP checksum is ok. */
r_if
c_cond
(paren
(paren
r_int
)paren
id|NextLevelProtocolChecksum
op_eq
l_int|0xFFFF
)paren
(brace
multiline_comment|/* TCP/UDP checksum ok. */
id|NextLevelProtoStats-&gt;RxOkCts
op_increment
suffix:semicolon
r_return
(paren
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_TCP
ques
c_cond
id|SKCS_STATUS_TCP_CSUM_OK
suffix:colon
id|SKCS_STATUS_UDP_CSUM_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* TCP/UDP checksum error. */
id|NextLevelProtoStats-&gt;RxErrCts
op_increment
suffix:semicolon
r_return
(paren
id|NextLevelProtocol
op_eq
id|SKCS_PROTO_ID_TCP
ques
c_cond
id|SKCS_STATUS_TCP_CSUM_ERROR
suffix:colon
id|SKCS_STATUS_UDP_CSUM_ERROR
)paren
suffix:semicolon
)brace
multiline_comment|/* SkCsGetReceiveInfo */
multiline_comment|/******************************************************************************&n; *&n; *&t;SkCsSetReceiveFlags - set checksum receive flags&n; *&n; * Description:&n; *&t;Use this function to set the various receive flags. According to the&n; *&t;protocol flags set by the caller, the start offsets within received&n; *&t;packets of the two hardware checksums are returned. These offsets must&n; *&t;be stored in all receive descriptors.&n; *&n; * Arguments:&n; *&t;pAc - Pointer to adapter context struct.&n; *&n; *&t;ReceiveFlags - Any combination of SK_PROTO_XXX flags of the protocols&n; *&t;for which the caller wants checksum information on received frames.&n; *&n; *&t;pChecksum1Offset - The start offset of the first receive descriptor&n; *&t;hardware checksum to be calculated for received frames is returned&n; *&t;here.&n; *&n; *&t;pChecksum2Offset - The start offset of the second receive descriptor&n; *&t;hardware checksum to be calculated for received frames is returned&n; *&t;here.&n; *&n; * Returns: N/A&n; *&t;Returns the two hardware checksum start offsets.&n; */
DECL|function|SkCsSetReceiveFlags
r_void
id|SkCsSetReceiveFlags
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
multiline_comment|/* Adapter context struct. */
r_int
id|ReceiveFlags
comma
multiline_comment|/* New receive flags. */
r_int
op_star
id|pChecksum1Offset
comma
multiline_comment|/* Offset for hardware checksum 1. */
r_int
op_star
id|pChecksum2Offset
)paren
multiline_comment|/* Offset for hardware checksum 2. */
(brace
multiline_comment|/* Save the receive flags. */
id|pAc-&gt;Csum.ReceiveFlags
op_assign
id|ReceiveFlags
suffix:semicolon
multiline_comment|/* First checksum start offset is the IP header. */
op_star
id|pChecksum1Offset
op_assign
id|SKCS_MAC_HEADER_SIZE
suffix:semicolon
multiline_comment|/*&n;&t; * Second checksum start offset is the IP data. Note that this may vary&n;&t; * if there are any IP header options in the actual packet.&n;&t; */
op_star
id|pChecksum2Offset
op_assign
id|SKCS_MAC_HEADER_SIZE
op_plus
id|SKCS_IP_HEADER_SIZE
suffix:semicolon
)brace
multiline_comment|/* SkCsSetReceiveFlags */
macro_line|#ifndef SkCsCalculateChecksum
multiline_comment|/******************************************************************************&n; *&n; *&t;SkCsCalculateChecksum - calculate checksum for specified data&n; *&n; * Description:&n; *&t;Calculate and return the 16-bit Internet Checksum for the specified&n; *&t;data.&n; *&n; * Arguments:&n; *&t;pData - Pointer to data for which the checksum shall be calculated.&n; *&t;Note: The pointer should be aligned on a 16-bit boundary.&n; *&n; *&t;Length - Length in bytes of data to checksum.&n; *&n; * Returns:&n; *&t;The 16-bit Internet Checksum for the specified data.&n; *&n; *&t;Note: The checksum is calculated in the machine&squot;s natural byte order,&n; *&t;i.e. little vs. big endian. Thus, the resulting checksum is different&n; *&t;for the same input data on little and big endian machines.&n; *&n; *&t;However, when written back to the network packet, the byte order is&n; *&t;always in correct network order.&n; */
DECL|function|SkCsCalculateChecksum
r_int
id|SkCsCalculateChecksum
c_func
(paren
r_void
op_star
id|pData
comma
multiline_comment|/* Data to checksum. */
r_int
id|Length
)paren
multiline_comment|/* Length of data. */
(brace
id|SK_U16
op_star
id|pU16
suffix:semicolon
multiline_comment|/* Pointer to the data as 16-bit words. */
r_int
r_int
id|Checksum
suffix:semicolon
multiline_comment|/* Checksum; must be at least 32 bits. */
multiline_comment|/* Sum up all 16-bit words. */
id|pU16
op_assign
(paren
id|SK_U16
op_star
)paren
id|pData
suffix:semicolon
r_for
c_loop
(paren
id|Checksum
op_assign
l_int|0
suffix:semicolon
id|Length
OG
l_int|1
suffix:semicolon
id|Length
op_sub_assign
l_int|2
)paren
(brace
id|Checksum
op_add_assign
op_star
id|pU16
op_increment
suffix:semicolon
)brace
multiline_comment|/* If this is an odd number of bytes, add-in the last byte. */
r_if
c_cond
(paren
id|Length
OG
l_int|0
)paren
(brace
macro_line|#ifdef SK_BIG_ENDIAN
multiline_comment|/* Add the last byte as the high byte. */
id|Checksum
op_add_assign
(paren
(paren
r_int
)paren
op_star
(paren
id|SK_U8
op_star
)paren
id|pU16
)paren
op_lshift
l_int|8
suffix:semicolon
macro_line|#else&t;/* !SK_BIG_ENDIAN */
multiline_comment|/* Add the last byte as the low byte. */
id|Checksum
op_add_assign
op_star
(paren
id|SK_U8
op_star
)paren
id|pU16
suffix:semicolon
macro_line|#endif&t;/* !SK_BIG_ENDIAN */
)brace
multiline_comment|/* Add-in any carries. */
id|SKCS_OC_ADD
c_func
(paren
id|Checksum
comma
id|Checksum
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Add-in any new carry. */
id|SKCS_OC_ADD
c_func
(paren
id|Checksum
comma
id|Checksum
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Note: All bits beyond the 16-bit limit are now zero. */
r_return
(paren
(paren
r_int
)paren
id|Checksum
)paren
suffix:semicolon
)brace
multiline_comment|/* SkCsCalculateChecksum */
macro_line|#endif /* SkCsCalculateChecksum */
multiline_comment|/******************************************************************************&n; *&n; *&t;SkCsEvent - the CSUM event dispatcher&n; *&n; * Description:&n; *&t;This is the event handler for the CSUM module.&n; *&n; * Arguments:&n; *&t;pAc - Pointer to adapter context.&n; *&n; *&t;Ioc - I/O context.&n; *&n; *&t;Event -&t; Event id.&n; *&n; *&t;Param - Event dependent parameter.&n; *&n; * Returns:&n; *&t;The 16-bit Internet Checksum for the specified data.&n; *&n; *&t;Note: The checksum is calculated in the machine&squot;s natural byte order,&n; *&t;i.e. little vs. big endian. Thus, the resulting checksum is different&n; *&t;for the same input data on little and big endian machines.&n; *&n; *&t;However, when written back to the network packet, the byte order is&n; *&t;always in correct network order.&n; */
DECL|function|SkCsEvent
r_int
id|SkCsEvent
c_func
(paren
id|SK_AC
op_star
id|pAc
comma
multiline_comment|/* Pointer to adapter context. */
id|SK_IOC
id|Ioc
comma
multiline_comment|/* I/O context. */
id|SK_U32
id|Event
comma
multiline_comment|/* Event id. */
id|SK_EVPARA
id|Param
)paren
multiline_comment|/* Event dependent parameter. */
(brace
r_int
id|ProtoIndex
suffix:semicolon
r_switch
c_cond
(paren
id|Event
)paren
(brace
multiline_comment|/*&n;&t; * Clear protocol statistics.&n;&t; *&n;&t; * Param - Protocol index, or -1 for all protocols.&n;&t; */
r_case
id|SK_CSUM_EVENT_CLEAR_PROTO_STATS
suffix:colon
id|ProtoIndex
op_assign
(paren
r_int
)paren
id|Param.Para32
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ProtoIndex
OL
l_int|0
)paren
(brace
multiline_comment|/* Clear for all protocols. */
id|memset
c_func
(paren
op_amp
id|pAc-&gt;Csum.ProtoStats
(braket
l_int|0
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|pAc-&gt;Csum.ProtoStats
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Clear for individual protocol. */
id|memset
c_func
(paren
op_amp
id|pAc-&gt;Csum.ProtoStats
(braket
id|ProtoIndex
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|pAc-&gt;Csum.ProtoStats
(braket
id|ProtoIndex
)braket
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Success. */
)brace
multiline_comment|/* SkCsEvent */
macro_line|#endif&t;/* SK_USE_CSUM */
eof
