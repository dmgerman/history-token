multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skrlmt.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.32 $&n; * Date:&t;$Date: 2001/02/14 14:06:31 $&n; * Purpose:&t;Header file for Redundant Link ManagemenT.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2001 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skrlmt.h,v $&n; *&t;Revision 1.32  2001/02/14 14:06:31  rassmann&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.31  2001/02/05 14:25:26  rassmann&n; *&t;Prepared RLMT for transparent operation.&n; *&t;&n; *&t;Revision 1.30  2001/01/22 13:41:39  rassmann&n; *&t;Supporting two nets on dual-port adapters.&n; *&t;&n; *&t;Revision 1.29  2000/11/17 08:58:00  rassmann&n; *&t;Moved CheckSwitch from SK_RLMT_PACKET_RECEIVED to SK_RLMT_TIM event.&n; *&t;&n; *&t;Revision 1.28  2000/11/09 12:24:34  rassmann&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.27  1999/11/22 13:59:56  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.26  1999/10/04 14:01:19  rassmann&n; *&t;Corrected reaction to reception of BPDU frames (#10441).&n; *&t;&n; *&t;Revision 1.25  1999/07/20 12:53:39  rassmann&n; *&t;Fixed documentation errors for lookahead macros.&n; *&t;&n; *&t;Revision 1.24  1999/05/28 11:15:56  rassmann&n; *&t;Changed behaviour to reflect Design Spec v1.2.&n; *&t;Controlling Link LED(s).&n; *&t;Introduced RLMT Packet Version field in RLMT Packet.&n; *&t;Newstyle lookahead macros (checking meta-information before looking at&n; *&t;  the packet).&n; *&t;&n; *&t;Revision 1.23  1999/01/28 12:50:42  rassmann&n; *&t;Not using broadcast time stamps in CheckLinkState mode.&n; *&t;&n; *&t;Revision 1.22  1999/01/27 14:13:04  rassmann&n; *&t;Monitoring broadcast traffic.&n; *&t;Switching more reliably and not too early if switch is&n; *&t; configured for spanning tree.&n; *&t;&n; *&t;Revision 1.21  1998/12/08 13:11:25  rassmann&n; *&t;Stopping SegTimer at RlmtStop.&n; *&t;&n; *&t;Revision 1.20  1998/11/24 12:37:33  rassmann&n; *&t;Implemented segmentation check.&n; *&t;&n; *&t;Revision 1.19  1998/11/17 13:43:06  rassmann&n; *&t;Handling (logical) tx failure.&n; *&t;Sending packet on logical address after PORT_SWITCH.&n; *&t;&n; *&t;Revision 1.18  1998/11/13 16:56:56  rassmann&n; *&t;Added macro version of SkRlmtLookaheadPacket.&n; *&t;&n; *&t;Revision 1.17  1998/11/06 18:06:05  rassmann&n; *&t;Corrected timing when RLMT checks fail.&n; *&t;Clearing tx counter earlier in periodical checks.&n; *&t;&n; *&t;Revision 1.16  1998/11/03 13:53:50  rassmann&n; *&t;RLMT should switch now (at least in mode 3).&n; *&t;&n; *&t;Revision 1.15  1998/10/22 11:39:52  rassmann&n; *&t;Corrected signed/unsigned mismatches.&n; *&t;Corrected receive list handling and address recognition.&n; *&t;&n; *&t;Revision 1.14  1998/10/15 15:16:36  rassmann&n; *&t;Finished Spanning Tree checking.&n; *&t;Checked with lint.&n; *&t;&n; *&t;Revision 1.13  1998/09/24 19:16:08  rassmann&n; *&t;Code cleanup.&n; *&t;Introduced Timer for PORT_DOWN due to no RX.&n; *&t;&n; *&t;Revision 1.12  1998/09/16 11:09:52  rassmann&n; *&t;Syntax corrections.&n; *&t;&n; *&t;Revision 1.11  1998/09/15 11:28:50  rassmann&n; *&t;Syntax corrections.&n; *&t;&n; *&t;Revision 1.10  1998/09/14 17:07:38  rassmann&n; *&t;Added code for port checking via LAN.&n; *&t;Changed Mbuf definition.&n; *&t;&n; *&t;Revision 1.9  1998/09/07 11:14:15  rassmann&n; *&t;Syntax corrections.&n; *&t;&n; *&t;Revision 1.8  1998/09/07 09:06:08  rassmann&n; *&t;Syntax corrections.&n; *&t;&n; *&t;Revision 1.7  1998/09/04 19:41:34  rassmann&n; *&t;Syntax corrections.&n; *&t;Started entering code for checking local links.&n; *&t;&n; *&t;Revision 1.6  1998/09/04 12:14:28  rassmann&n; *&t;Interface cleanup.&n; *&t;&n; *&t;Revision 1.5  1998/09/02 16:55:29  rassmann&n; *&t;Updated to reflect new DRV/HWAC/RLMT interface.&n; *&t;&n; *&t;Revision 1.4  1998/09/02 07:26:02  afischer&n; *&t;typedef for SK_RLMT_PORT&n; *&n; *&t;Revision 1.3  1998/08/27 14:29:03  rassmann&n; *&t;Code cleanup.&n; *&t;&n; *&t;Revision 1.2  1998/08/27 14:26:25  rassmann&n; *&t;Updated interface.&n; *&t;&n; *&t;Revision 1.1  1998/08/21 08:29:10  rassmann&n; *&t;First public version.&n; *&t;&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * This is the header file for Redundant Link ManagemenT.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;&quot;skdrv1st.h&quot;&n; *&t;...&n; *&t;&quot;sktypes.h&quot;&n; *&t;&quot;skqueue.h&quot;&n; *&t;&quot;skaddr.h&quot;&n; *&t;&quot;skrlmt.h&quot;&n; *&t;...&n; *&t;&quot;skdrv2nd.h&quot;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKRLMT_H
DECL|macro|__INC_SKRLMT_H
mdefine_line|#define __INC_SKRLMT_H
macro_line|#ifdef __cplusplus
macro_line|#error C++ is not yet supported.
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* cplusplus */
multiline_comment|/* defines ********************************************************************/
DECL|macro|SK_RLMT_NET_DOWN_TEMP
mdefine_line|#define&t;SK_RLMT_NET_DOWN_TEMP&t;1&t;/* NET_DOWN due to last port down. */
DECL|macro|SK_RLMT_NET_DOWN_FINAL
mdefine_line|#define&t;SK_RLMT_NET_DOWN_FINAL&t;2&t;/* NET_DOWN due to RLMT_STOP. */
multiline_comment|/* ----- Default queue sizes - must be multiples of 8 KB ----- */
multiline_comment|/* Less than 8 KB free in RX queue =&gt; pause frames. */
DECL|macro|SK_RLMT_STANDBY_QRXSIZE
mdefine_line|#define SK_RLMT_STANDBY_QRXSIZE&t;128&t;/* Size of rx standby queue in KB. */
DECL|macro|SK_RLMT_STANDBY_QXASIZE
mdefine_line|#define SK_RLMT_STANDBY_QXASIZE&t;32&t;/* Size of async standby queue in KB. */
DECL|macro|SK_RLMT_STANDBY_QXSSIZE
mdefine_line|#define SK_RLMT_STANDBY_QXSSIZE&t;0&t;/* Size of sync standby queue in KB. */
DECL|macro|SK_RLMT_MAX_TX_BUF_SIZE
mdefine_line|#define SK_RLMT_MAX_TX_BUF_SIZE&t;60&t;/* Maximum RLMT transmit size. */
multiline_comment|/* ----- PORT states ----- */
DECL|macro|SK_RLMT_PS_INIT
mdefine_line|#define SK_RLMT_PS_INIT&t;&t;&t;0&t;/* Port state: Init. */
DECL|macro|SK_RLMT_PS_LINK_DOWN
mdefine_line|#define SK_RLMT_PS_LINK_DOWN&t;1&t;/* Port state: Link down. */
DECL|macro|SK_RLMT_PS_DOWN
mdefine_line|#define SK_RLMT_PS_DOWN&t;&t;&t;2&t;/* Port state: Port down. */
DECL|macro|SK_RLMT_PS_GOING_UP
mdefine_line|#define SK_RLMT_PS_GOING_UP&t;&t;3&t;/* Port state: Going up. */
DECL|macro|SK_RLMT_PS_UP
mdefine_line|#define SK_RLMT_PS_UP&t;&t;&t;4&t;/* Port state: Up. */
multiline_comment|/* ----- RLMT states ----- */
DECL|macro|SK_RLMT_RS_INIT
mdefine_line|#define SK_RLMT_RS_INIT&t;&t;&t;0&t;/* RLMT state: Init. */
DECL|macro|SK_RLMT_RS_NET_DOWN
mdefine_line|#define SK_RLMT_RS_NET_DOWN&t;&t;1&t;/* RLMT state: Net down. */
DECL|macro|SK_RLMT_RS_NET_UP
mdefine_line|#define SK_RLMT_RS_NET_UP&t;&t;2&t;/* RLMT state: Net up. */
multiline_comment|/* ----- PORT events ----- */
DECL|macro|SK_RLMT_LINK_UP
mdefine_line|#define SK_RLMT_LINK_UP&t;&t;&t;1001&t;/* Link came up. */
DECL|macro|SK_RLMT_LINK_DOWN
mdefine_line|#define SK_RLMT_LINK_DOWN&t;&t;1002&t;/* Link went down. */
DECL|macro|SK_RLMT_PORT_ADDR
mdefine_line|#define SK_RLMT_PORT_ADDR&t;&t;1003&t;/* Port address changed. */
multiline_comment|/* ----- RLMT events ----- */
DECL|macro|SK_RLMT_START
mdefine_line|#define SK_RLMT_START&t;&t;&t;2001&t;/* Start RLMT. */
DECL|macro|SK_RLMT_STOP
mdefine_line|#define SK_RLMT_STOP&t;&t;&t;2002&t;/* Stop RLMT. */
DECL|macro|SK_RLMT_PACKET_RECEIVED
mdefine_line|#define SK_RLMT_PACKET_RECEIVED&t;2003&t;/* Packet was received for RLMT. */
DECL|macro|SK_RLMT_STATS_CLEAR
mdefine_line|#define SK_RLMT_STATS_CLEAR&t;&t;2004&t;/* Clear statistics. */
DECL|macro|SK_RLMT_STATS_UPDATE
mdefine_line|#define SK_RLMT_STATS_UPDATE&t;2005&t;/* Update statistics. */
DECL|macro|SK_RLMT_PREFPORT_CHANGE
mdefine_line|#define SK_RLMT_PREFPORT_CHANGE&t;2006&t;/* Change preferred port. */
DECL|macro|SK_RLMT_MODE_CHANGE
mdefine_line|#define SK_RLMT_MODE_CHANGE&t;&t;2007&t;/* New RlmtMode. */
DECL|macro|SK_RLMT_SET_NETS
mdefine_line|#define SK_RLMT_SET_NETS&t;&t;2008&t;/* Number of Nets (1 or 2). */
multiline_comment|/* ----- RLMT mode bits ----- */
multiline_comment|/*&n; * CAUTION:&t;These defines are private to RLMT.&n; *&t;&t;&t;Please use the RLMT mode defines below.&n; */
DECL|macro|SK_RLMT_CHECK_LINK
mdefine_line|#define SK_RLMT_CHECK_LINK&t;&t;  1&t;&t;/* Check Link. */
DECL|macro|SK_RLMT_CHECK_LOC_LINK
mdefine_line|#define SK_RLMT_CHECK_LOC_LINK&t;  2&t;&t;/* Check other link on same adapter. */
DECL|macro|SK_RLMT_CHECK_SEG
mdefine_line|#define SK_RLMT_CHECK_SEG&t;&t;  4&t;&t;/* Check segmentation. */
macro_line|#ifndef RLMT_CHECK_REMOTE
DECL|macro|SK_RLMT_CHECK_OTHERS
mdefine_line|#define SK_RLMT_CHECK_OTHERS&t;SK_RLMT_CHECK_LOC_LINK
macro_line|#else&t;/* RLMT_CHECK_REMOTE */
DECL|macro|SK_RLMT_CHECK_REM_LINK
mdefine_line|#define SK_RLMT_CHECK_REM_LINK&t;  8&t;&t;/* Check link(s) on other adapter(s). */
DECL|macro|SK_RLMT_MAX_REMOTE_PORTS_CHECKED
mdefine_line|#define SK_RLMT_MAX_REMOTE_PORTS_CHECKED&t;3
DECL|macro|SK_RLMT_CHECK_OTHERS
mdefine_line|#define SK_RLMT_CHECK_OTHERS&t;&bslash;&n;&t;&t;(SK_RLMT_CHECK_LOC_LINK | SK_RLMT_CHECK_REM_LINK)
macro_line|#endif&t;/* RLMT_CHECK_REMOTE */
macro_line|#ifndef SK_RLMT_ENABLE_TRANSPARENT
DECL|macro|SK_RLMT_TRANSPARENT
mdefine_line|#define SK_RLMT_TRANSPARENT&t;&t;  0&t;&t;/* RLMT transparent - inactive. */
macro_line|#else&t;/* SK_RLMT_ENABLE_TRANSPARENT */
DECL|macro|SK_RLMT_TRANSPARENT
mdefine_line|#define SK_RLMT_TRANSPARENT&t;&t;128&t;&t;/* RLMT transparent. */
macro_line|#endif&t;/* SK_RLMT_ENABLE_TRANSPARENT */
multiline_comment|/* ----- RLMT modes ----- */
multiline_comment|/* Check Link State. */
DECL|macro|SK_RLMT_MODE_CLS
mdefine_line|#define SK_RLMT_MODE_CLS&t;(SK_RLMT_CHECK_LINK)
multiline_comment|/* Check Local Ports: check other links on the same adapter. */
DECL|macro|SK_RLMT_MODE_CLP
mdefine_line|#define SK_RLMT_MODE_CLP&t;(SK_RLMT_CHECK_LINK | SK_RLMT_CHECK_LOC_LINK)
multiline_comment|/* Check Local Ports and Segmentation Status. */
DECL|macro|SK_RLMT_MODE_CLPSS
mdefine_line|#define SK_RLMT_MODE_CLPSS&t;&bslash;&n;&t;&t;(SK_RLMT_CHECK_LINK | SK_RLMT_CHECK_LOC_LINK | SK_RLMT_CHECK_SEG)
macro_line|#ifdef RLMT_CHECK_REMOTE
multiline_comment|/* Check Local and Remote Ports: check links (local or remote). */
id|Name
id|of
id|define
id|TBD
op_logical_neg
DECL|macro|SK_RLMT_MODE_CRP
mdefine_line|#define SK_RLMT_MODE_CRP&t;&bslash;&n;&t;&t;(SK_RLMT_CHECK_LINK | SK_RLMT_CHECK_LOC_LINK | SK_RLMT_CHECK_REM_LINK)
multiline_comment|/* Check Local and Remote Ports and Segmentation Status. */
id|Name
id|of
id|define
id|TBD
op_logical_neg
DECL|macro|SK_RLMT_MODE_CRPSS
mdefine_line|#define SK_RLMT_MODE_CRPSS&t;&bslash;&n;&t;&t;(SK_RLMT_CHECK_LINK | SK_RLMT_CHECK_LOC_LINK | &bslash;&n;&t;&t;SK_RLMT_CHECK_REM_LINK | SK_RLMT_CHECK_SEG)
macro_line|#endif&t;/* RLMT_CHECK_REMOTE */
multiline_comment|/* ----- RLMT lookahead result bits ----- */
DECL|macro|SK_RLMT_RX_RLMT
mdefine_line|#define SK_RLMT_RX_RLMT&t;&t;&t;1&t;/* Give packet to RLMT. */
DECL|macro|SK_RLMT_RX_PROTOCOL
mdefine_line|#define SK_RLMT_RX_PROTOCOL&t;&t;2&t;/* Give packet to protocol. */
multiline_comment|/* Macros */
macro_line|#if 0
id|SK_AC
op_star
id|pAC
multiline_comment|/* adapter context */
id|SK_U32
id|PortNum
multiline_comment|/* receiving port */
r_int
id|PktLen
multiline_comment|/* received packet&squot;s length */
id|SK_BOOL
id|IsBc
multiline_comment|/* Flag: packet is broadcast */
r_int
op_star
id|pOffset
multiline_comment|/* offs. of bytes to present to SK_RLMT_LOOKAHEAD */
r_int
op_star
id|pNumBytes
multiline_comment|/* #Bytes to present to SK_RLMT_LOOKAHEAD */
macro_line|#endif&t;/* 0 */
DECL|macro|SK_RLMT_PRE_LOOKAHEAD
mdefine_line|#define SK_RLMT_PRE_LOOKAHEAD(pAC,PortNum,PktLen,IsBc,pOffset,pNumBytes) { &bslash;&n;&t;SK_AC&t;*_pAC; &bslash;&n;&t;SK_U32&t;_PortNum; &bslash;&n;&t;_pAC = (pAC); &bslash;&n;&t;_PortNum = (SK_U32)(PortNum); &bslash;&n;&t;/* _pAC-&gt;Rlmt.Port[_PortNum].PacketsRx++; */ &bslash;&n;&t;_pAC-&gt;Rlmt.Port[_PortNum].PacketsPerTimeSlot++; &bslash;&n;&t;if ((_pAC-&gt;Rlmt.Port[_PortNum].Net-&gt;RlmtMode &amp; SK_RLMT_TRANSPARENT) != 0) { &bslash;&n;&t;&t;*(pNumBytes) = 0; &bslash;&n;&t;} &bslash;&n;&t;else if (IsBc) { &bslash;&n;&t;&t;if (_pAC-&gt;Rlmt.Port[_PortNum].Net-&gt;RlmtMode != SK_RLMT_MODE_CLS) { &bslash;&n;&t;&t;&t;*(pNumBytes) = 6; &bslash;&n;&t;&t;&t;*(pOffset) = 6; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;else { &bslash;&n;&t;&t;&t;*(pNumBytes) = 0; &bslash;&n;&t;&t;} &bslash;&n;&t;} &bslash;&n;&t;else { &bslash;&n;&t;&t;if ((PktLen) &gt; SK_RLMT_MAX_TX_BUF_SIZE) { &bslash;&n;&t;&t;&t;/* _pAC-&gt;Rlmt.Port[_PortNum].DataPacketsPerTimeSlot++; */ &bslash;&n;&t;&t;&t;*(pNumBytes) = 0; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;else { &bslash;&n;&t;&t;&t;*(pNumBytes) = 6; &bslash;&n;&t;&t;&t;*(pOffset) = 0; &bslash;&n;&t;&t;} &bslash;&n;&t;} &bslash;&n;}
macro_line|#if 0
id|SK_AC
op_star
id|pAC
multiline_comment|/* adapter context */
id|SK_U32
id|PortNum
multiline_comment|/* receiving port */
id|SK_U8
op_star
id|pLaPacket
comma
multiline_comment|/* received packet&squot;s data (points to pOffset) */
id|SK_BOOL
id|IsBc
multiline_comment|/* Flag: packet is broadcast */
id|SK_BOOL
id|IsMc
multiline_comment|/* Flag: packet is multicast */
r_int
op_star
id|pForRlmt
multiline_comment|/* Result: bits SK_RLMT_RX_RLMT, SK_RLMT_RX_PROTOCOL */
id|SK_RLMT_LOOKAHEAD
c_func
(paren
)paren
id|expects
op_star
id|pNumBytes
id|from
id|packet
id|offset
op_star
id|pOffset
(paren
id|s.a
dot
)paren
id|at
op_star
id|pLaPacket
dot
id|If
id|you
id|use
id|SK_RLMT_LOOKAHEAD
id|in
id|a
id|path
id|where
id|you
id|already
id|know
r_if
c_cond
id|the
id|packet
id|is
id|BC
comma
id|MC
comma
op_logical_or
id|UC
comma
id|you
id|should
id|use
id|constants
r_for
c_loop
id|IsBc
op_logical_and
id|IsMc
comma
id|so
id|that
id|your
id|compiler
id|can
id|trash
id|unneeded
id|parts
id|of
id|the
r_if
c_cond
id|construction
dot
macro_line|#endif&t;/* 0 */
DECL|macro|SK_RLMT_LOOKAHEAD
mdefine_line|#define SK_RLMT_LOOKAHEAD(pAC,PortNum,pLaPacket,IsBc,IsMc,pForRlmt) { &bslash;&n;&t;SK_AC&t;*_pAC; &bslash;&n;&t;SK_U32&t;_PortNum; &bslash;&n;&t;SK_U8&t;*_pLaPacket; &bslash;&n;&t;_pAC = (pAC); &bslash;&n;&t;_PortNum = (SK_U32)(PortNum); &bslash;&n;&t;_pLaPacket = (SK_U8 *)(pLaPacket); &bslash;&n;&t;if (IsBc) {&bslash;&n;&t;&t;if (!SK_ADDR_EQUAL(_pLaPacket, _pAC-&gt;Addr.Net[_pAC-&gt;Rlmt.Port[ &bslash;&n;&t;&t;&t;_PortNum].Net-&gt;NetNumber].CurrentMacAddress.a)) { &bslash;&n;&t;&t;&t;_pAC-&gt;Rlmt.Port[_PortNum].BcTimeStamp = SkOsGetTime(_pAC); &bslash;&n;&t;&t;&t;_pAC-&gt;Rlmt.CheckSwitch = SK_TRUE; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;/* _pAC-&gt;Rlmt.Port[_PortNum].DataPacketsPerTimeSlot++; */ &bslash;&n;&t;&t;*(pForRlmt) = SK_RLMT_RX_PROTOCOL; &bslash;&n;&t;} &bslash;&n;&t;else if (IsMc) { &bslash;&n;&t;&t;if (SK_ADDR_EQUAL(_pLaPacket, BridgeMcAddr.a)) { &bslash;&n;&t;&t;&t;_pAC-&gt;Rlmt.Port[_PortNum].BpduPacketsPerTimeSlot++; &bslash;&n;&t;&t;&t;if (_pAC-&gt;Rlmt.Port[_PortNum].Net-&gt;RlmtMode &amp; SK_RLMT_CHECK_SEG) { &bslash;&n;&t;&t;&t;&t;*(pForRlmt) = SK_RLMT_RX_RLMT | SK_RLMT_RX_PROTOCOL; &bslash;&n;&t;&t;&t;} &bslash;&n;&t;&t;&t;else { &bslash;&n;&t;&t;&t;&t;*(pForRlmt) = SK_RLMT_RX_PROTOCOL; &bslash;&n;&t;&t;&t;} &bslash;&n;&t;&t;} &bslash;&n;&t;&t;else if (SK_ADDR_EQUAL(_pLaPacket, SkRlmtMcAddr.a)) { &bslash;&n;&t;&t;&t;*(pForRlmt) = SK_RLMT_RX_RLMT; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;else { &bslash;&n;&t;&t;&t;/* _pAC-&gt;Rlmt.Port[_PortNum].DataPacketsPerTimeSlot++; */ &bslash;&n;&t;&t;&t;*(pForRlmt) = SK_RLMT_RX_PROTOCOL; &bslash;&n;&t;&t;} &bslash;&n;&t;} &bslash;&n;&t;else { &bslash;&n;&t;&t;if (SK_ADDR_EQUAL( &bslash;&n;&t;&t;&t;_pLaPacket, &bslash;&n;&t;&t;&t;_pAC-&gt;Addr.Port[_PortNum].CurrentMacAddress.a)) { &bslash;&n;&t;&t;&t;*(pForRlmt) = SK_RLMT_RX_RLMT; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;else { &bslash;&n;&t;&t;&t;/* _pAC-&gt;Rlmt.Port[_PortNum].DataPacketsPerTimeSlot++; */ &bslash;&n;&t;&t;&t;*(pForRlmt) = SK_RLMT_RX_PROTOCOL; &bslash;&n;&t;&t;} &bslash;&n;&t;} &bslash;&n;}
macro_line|#ifdef SK_RLMT_FAST_LOOKAHEAD
id|Error
suffix:colon
id|SK_RLMT_FAST_LOOKAHEAD
id|no
id|longer
id|used
dot
id|Use
r_new
id|macros
r_for
c_loop
id|lookahead
dot
macro_line|#endif&t;/* SK_RLMT_FAST_LOOKAHEAD */
macro_line|#ifdef SK_RLMT_SLOW_LOOKAHEAD
id|Error
suffix:colon
id|SK_RLMT_SLOW_LOOKAHEAD
id|no
id|longer
id|used
dot
id|Use
r_new
id|macros
r_for
c_loop
id|lookahead
dot
macro_line|#endif&t;/* SK_RLMT_SLOW_LOOKAHEAD */
multiline_comment|/* typedefs *******************************************************************/
macro_line|#ifdef SK_RLMT_MBUF_PRIVATE
DECL|struct|s_RlmtMbuf
r_typedef
r_struct
id|s_RlmtMbuf
(brace
id|some
id|content
DECL|typedef|SK_RLMT_MBUF
)brace
id|SK_RLMT_MBUF
suffix:semicolon
macro_line|#endif&t;/* SK_RLMT_MBUF_PRIVATE */
macro_line|#ifdef SK_LA_INFO
DECL|struct|s_Rlmt_PacketInfo
r_typedef
r_struct
id|s_Rlmt_PacketInfo
(brace
DECL|member|PacketLength
r_int
id|PacketLength
suffix:semicolon
multiline_comment|/* Length of packet. */
DECL|member|PacketType
r_int
id|PacketType
suffix:semicolon
multiline_comment|/* Directed/Multicast/Broadcast. */
DECL|typedef|SK_RLMT_PINFO
)brace
id|SK_RLMT_PINFO
suffix:semicolon
macro_line|#endif&t;/* SK_LA_INFO */
DECL|struct|s_RootId
r_typedef
r_struct
id|s_RootId
(brace
DECL|member|Id
id|SK_U8
id|Id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Root Bridge Id. */
DECL|typedef|SK_RLMT_ROOT_ID
)brace
id|SK_RLMT_ROOT_ID
suffix:semicolon
DECL|struct|s_port
r_typedef
r_struct
id|s_port
(brace
DECL|member|CheckAddr
id|SK_MAC_ADDR
id|CheckAddr
suffix:semicolon
DECL|member|SuspectTx
id|SK_BOOL
id|SuspectTx
suffix:semicolon
DECL|typedef|SK_PORT_CHECK
)brace
id|SK_PORT_CHECK
suffix:semicolon
DECL|typedef|SK_RLMT_NET
r_typedef
r_struct
id|s_RlmtNet
id|SK_RLMT_NET
suffix:semicolon
DECL|struct|s_RlmtPort
r_typedef
r_struct
id|s_RlmtPort
(brace
multiline_comment|/* ----- Public part (read-only) ----- */
DECL|member|PortState
id|SK_U8
id|PortState
suffix:semicolon
multiline_comment|/* Current state of this port. */
multiline_comment|/* For PNMI */
DECL|member|LinkDown
id|SK_BOOL
id|LinkDown
suffix:semicolon
DECL|member|PortDown
id|SK_BOOL
id|PortDown
suffix:semicolon
DECL|member|Align01
id|SK_U8
id|Align01
suffix:semicolon
DECL|member|PortNumber
id|SK_U32
id|PortNumber
suffix:semicolon
multiline_comment|/* Number of port on adapter. */
DECL|member|Net
id|SK_RLMT_NET
op_star
id|Net
suffix:semicolon
multiline_comment|/* Net port belongs to. */
DECL|member|TxHelloCts
id|SK_U64
id|TxHelloCts
suffix:semicolon
DECL|member|RxHelloCts
id|SK_U64
id|RxHelloCts
suffix:semicolon
DECL|member|TxSpHelloReqCts
id|SK_U64
id|TxSpHelloReqCts
suffix:semicolon
DECL|member|RxSpHelloCts
id|SK_U64
id|RxSpHelloCts
suffix:semicolon
multiline_comment|/* ----- Private part ----- */
multiline_comment|/*&t;SK_U64&t;&t;&t;PacketsRx; */
multiline_comment|/* Total packets received. */
DECL|member|PacketsPerTimeSlot
id|SK_U32
id|PacketsPerTimeSlot
suffix:semicolon
multiline_comment|/* Packets rxed between TOs. */
multiline_comment|/*&t;SK_U32&t;&t;&t;DataPacketsPerTimeSlot; */
multiline_comment|/* Data packets ... */
DECL|member|BpduPacketsPerTimeSlot
id|SK_U32
id|BpduPacketsPerTimeSlot
suffix:semicolon
multiline_comment|/* BPDU packets rxed in TS. */
DECL|member|BcTimeStamp
id|SK_U64
id|BcTimeStamp
suffix:semicolon
multiline_comment|/* Time of last BC receive. */
DECL|member|GuTimeStamp
id|SK_U64
id|GuTimeStamp
suffix:semicolon
multiline_comment|/* Time of entering GOING_UP. */
DECL|member|UpTimer
id|SK_TIMER
id|UpTimer
suffix:semicolon
multiline_comment|/* Timer struct Link/Port up. */
DECL|member|DownRxTimer
id|SK_TIMER
id|DownRxTimer
suffix:semicolon
multiline_comment|/* Timer struct down rx. */
DECL|member|DownTxTimer
id|SK_TIMER
id|DownTxTimer
suffix:semicolon
multiline_comment|/* Timer struct down tx. */
DECL|member|CheckingState
id|SK_U32
id|CheckingState
suffix:semicolon
multiline_comment|/* Checking State. */
DECL|member|AddrPort
id|SK_ADDR_PORT
op_star
id|AddrPort
suffix:semicolon
DECL|member|Random
id|SK_U8
id|Random
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Random value. */
DECL|member|PortsChecked
r_int
id|PortsChecked
suffix:semicolon
multiline_comment|/* #ports checked. */
DECL|member|PortsSuspect
r_int
id|PortsSuspect
suffix:semicolon
multiline_comment|/* #ports checked that are s. */
DECL|member|PortCheck
id|SK_PORT_CHECK
id|PortCheck
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&t;SK_PORT_CHECK&t;PortCheck[SK_MAX_MACS - 1]; */
DECL|member|PortStarted
id|SK_BOOL
id|PortStarted
suffix:semicolon
multiline_comment|/* Port is started. */
DECL|member|PortNoRx
id|SK_BOOL
id|PortNoRx
suffix:semicolon
multiline_comment|/* NoRx for &gt;= 1 time slot. */
DECL|member|RootIdSet
id|SK_BOOL
id|RootIdSet
suffix:semicolon
DECL|member|Root
id|SK_RLMT_ROOT_ID
id|Root
suffix:semicolon
multiline_comment|/* Root Bridge Id. */
DECL|typedef|SK_RLMT_PORT
)brace
id|SK_RLMT_PORT
suffix:semicolon
DECL|struct|s_RlmtNet
r_struct
id|s_RlmtNet
(brace
multiline_comment|/* ----- Public part (read-only) ----- */
DECL|member|NetNumber
id|SK_U32
id|NetNumber
suffix:semicolon
multiline_comment|/* Number of net. */
DECL|member|Port
id|SK_RLMT_PORT
op_star
id|Port
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
multiline_comment|/* Ports that belong to this net. */
DECL|member|NumPorts
id|SK_U32
id|NumPorts
suffix:semicolon
multiline_comment|/* Number of ports. */
DECL|member|PrefPort
id|SK_U32
id|PrefPort
suffix:semicolon
multiline_comment|/* Preferred port. */
multiline_comment|/* For PNMI */
DECL|member|RlmtMode
id|SK_U32
id|RlmtMode
suffix:semicolon
multiline_comment|/* Check ... */
DECL|member|ActivePort
id|SK_U32
id|ActivePort
suffix:semicolon
multiline_comment|/* Active port. */
DECL|member|Preference
id|SK_U32
id|Preference
suffix:semicolon
multiline_comment|/* 0xFFFFFFFF: Automatic. */
DECL|member|RlmtState
id|SK_U8
id|RlmtState
suffix:semicolon
multiline_comment|/* Current RLMT state. */
multiline_comment|/* ----- Private part ----- */
DECL|member|RootIdSet
id|SK_BOOL
id|RootIdSet
suffix:semicolon
DECL|member|Align01
id|SK_U16
id|Align01
suffix:semicolon
DECL|member|LinksUp
r_int
id|LinksUp
suffix:semicolon
multiline_comment|/* #Links up. */
DECL|member|PortsUp
r_int
id|PortsUp
suffix:semicolon
multiline_comment|/* #Ports up. */
DECL|member|TimeoutValue
id|SK_U32
id|TimeoutValue
suffix:semicolon
multiline_comment|/* RLMT timeout value. */
DECL|member|CheckingState
id|SK_U32
id|CheckingState
suffix:semicolon
multiline_comment|/* Checking State. */
DECL|member|Root
id|SK_RLMT_ROOT_ID
id|Root
suffix:semicolon
multiline_comment|/* Root Bridge Id. */
DECL|member|LocTimer
id|SK_TIMER
id|LocTimer
suffix:semicolon
multiline_comment|/* Timer struct. */
DECL|member|SegTimer
id|SK_TIMER
id|SegTimer
suffix:semicolon
multiline_comment|/* Timer struct. */
)brace
suffix:semicolon
DECL|struct|s_Rlmt
r_typedef
r_struct
id|s_Rlmt
(brace
multiline_comment|/* ----- Public part (read-only) ----- */
DECL|member|NumNets
id|SK_U32
id|NumNets
suffix:semicolon
multiline_comment|/* Number of nets. */
DECL|member|NetsStarted
id|SK_U32
id|NetsStarted
suffix:semicolon
multiline_comment|/* Number of nets started. */
DECL|member|Net
id|SK_RLMT_NET
id|Net
(braket
id|SK_MAX_NETS
)braket
suffix:semicolon
multiline_comment|/* Array of available nets. */
DECL|member|Port
id|SK_RLMT_PORT
id|Port
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
multiline_comment|/* Array of available ports. */
multiline_comment|/* ----- Private part ----- */
DECL|member|CheckSwitch
id|SK_BOOL
id|CheckSwitch
suffix:semicolon
DECL|member|Align01
id|SK_U8
id|Align01
suffix:semicolon
DECL|member|Align02
id|SK_U16
id|Align02
suffix:semicolon
DECL|typedef|SK_RLMT
)brace
id|SK_RLMT
suffix:semicolon
r_extern
id|SK_MAC_ADDR
id|BridgeMcAddr
suffix:semicolon
r_extern
id|SK_MAC_ADDR
id|SkRlmtMcAddr
suffix:semicolon
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifndef SK_KR_PROTO
multiline_comment|/* Functions provided by SkRlmt */
multiline_comment|/* ANSI/C++ compliant function prototypes */
r_extern
r_void
id|SkRlmtInit
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
id|SkRlmtEvent
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
id|Para
)paren
suffix:semicolon
macro_line|#else&t;/* defined(SK_KR_PROTO) */
multiline_comment|/* Non-ANSI/C++ compliant function prototypes */
macro_line|#error KR-style function prototypes are not yet provided.
macro_line|#endif&t;/* defined(SK_KR_PROTO)) */
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_SKRLMT_H */
eof
