multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skaddr.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.23 $&n; * Date:&t;$Date: 2000/08/10 11:27:50 $&n; * Purpose:&t;Header file for Address Management (MC, UC, Prom).&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2000 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skaddr.h,v $&n; *&t;Revision 1.23  2000/08/10 11:27:50  rassmann&n; *&t;Editorial changes.&n; *&t;Preserving 32-bit alignment in structs for the adapter context.&n; *&t;&n; *&t;Revision 1.22  2000/08/07 11:10:40  rassmann&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.21  2000/05/04 09:39:59  rassmann&n; *&t;Editorial changes.&n; *&t;Corrected multicast address hashing.&n; *&t;&n; *&t;Revision 1.20  1999/11/22 13:46:14  cgoos&n; *&t;Changed license header to GPL.&n; *&t;Allowing overwrite for SK_ADDR_EQUAL.&n; *&t;&n; *&t;Revision 1.19  1999/05/28 10:56:07  rassmann&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.18  1999/04/06 17:22:04  rassmann&n; *&t;Added private &quot;ActivePort&quot;.&n; *&t;&n; *&t;Revision 1.17  1999/01/14 16:18:19  rassmann&n; *&t;Corrected multicast initialization.&n; *&t;&n; *&t;Revision 1.16  1999/01/04 10:30:36  rassmann&n; *&t;SkAddrOverride only possible after SK_INIT_IO phase.&n; *&t;&n; *&t;Revision 1.15  1998/12/29 13:13:11  rassmann&n; *&t;An address override is now preserved in the SK_INIT_IO phase.&n; *&t;All functions return an int now.&n; *&t;Extended parameter checking.&n; *&t;&n; *&t;Revision 1.14  1998/11/24 12:39:45  rassmann&n; *&t;Reserved multicast entry for BPDU address.&n; *&t;13 multicast entries left for protocol.&n; *&t;&n; *&t;Revision 1.13  1998/11/13 17:24:32  rassmann&n; *&t;Changed return value of SkAddrOverride to int.&n; *&t;&n; *&t;Revision 1.12  1998/11/13 16:56:19  rassmann&n; *&t;Added macro SK_ADDR_COMPARE.&n; *&t;Changed return type of SkAddrOverride to SK_BOOL.&n; *&t;&n; *&t;Revision 1.11  1998/10/28 18:16:35  rassmann&n; *&t;Avoiding I/Os before SK_INIT_RUN level.&n; *&t;Aligning InexactFilter.&n; *&t;&n; *&t;Revision 1.10  1998/10/22 11:39:10  rassmann&n; *&t;Corrected signed/unsigned mismatches.&n; *&t;&n; *&t;Revision 1.9  1998/10/15 15:15:49  rassmann&n; *&t;Changed Flags Parameters from SK_U8 to int.&n; *&t;Checked with lint.&n; *&t;&n; *&t;Revision 1.8  1998/09/24 19:15:12  rassmann&n; *&t;Code cleanup.&n; *&t;&n; *&t;Revision 1.7  1998/09/18 20:22:13  rassmann&n; *&t;Added HW access.&n; *&t;&n; *&t;Revision 1.6  1998/09/04 19:40:20  rassmann&n; *&t;Interface enhancements.&n; *&t;&n; *&t;Revision 1.5  1998/09/04 12:40:57  rassmann&n; *&t;Interface cleanup.&n; *&t;&n; *&t;Revision 1.4  1998/09/04 12:14:13  rassmann&n; *&t;Interface cleanup.&n; *&t;&n; *&t;Revision 1.3  1998/09/02 16:56:40  rassmann&n; *&t;Updated interface.&n; *&t;&n; *&t;Revision 1.2  1998/08/27 14:26:09  rassmann&n; *&t;Updated interface.&n; *&t;&n; *&t;Revision 1.1  1998/08/21 08:31:08  rassmann&n; *&t;First public version.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * This module is intended to manage multicast addresses and promiscuous mode&n; * on GEnesis adapters.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;&quot;skdrv1st.h&quot;&n; *&t;...&n; *&t;&quot;sktypes.h&quot;&n; *&t;&quot;skqueue.h&quot;&n; *&t;&quot;skaddr.h&quot;&n; *&t;...&n; *&t;&quot;skdrv2nd.h&quot;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKADDR_H
DECL|macro|__INC_SKADDR_H
mdefine_line|#define __INC_SKADDR_H
macro_line|#ifdef __cplusplus
macro_line|#error C++ is not yet supported.
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* cplusplus */
multiline_comment|/* defines ********************************************************************/
DECL|macro|SK_MAC_ADDR_LEN
mdefine_line|#define SK_MAC_ADDR_LEN&t;&t;&t;&t;6&t;/* Length of MAC address. */
DECL|macro|SK_MAX_ADDRS
mdefine_line|#define&t;SK_MAX_ADDRS&t;&t;&t;&t;14&t;/* #Addrs for exact match. */
multiline_comment|/* ----- Common return values ----- */
DECL|macro|SK_ADDR_SUCCESS
mdefine_line|#define SK_ADDR_SUCCESS&t;&t;&t;&t;0&t;/* Function returned successfully. */
DECL|macro|SK_ADDR_ILLEGAL_PORT
mdefine_line|#define SK_ADDR_ILLEGAL_PORT&t;&t;100&t;/* Port number too high. */
DECL|macro|SK_ADDR_TOO_EARLY
mdefine_line|#define SK_ADDR_TOO_EARLY&t;&t;&t;101&t;/* Function called too early. */
multiline_comment|/* ----- Clear/Add flag bits ----- */
DECL|macro|SK_ADDR_PERMANENT
mdefine_line|#define SK_ADDR_PERMANENT&t;&t;&t;1&t;/* RLMT Address */
multiline_comment|/* ----- Additional Clear flag bits ----- */
DECL|macro|SK_MC_SW_ONLY
mdefine_line|#define SK_MC_SW_ONLY&t;&t;&t;&t;2&t;/* Do not update HW when clearing. */
multiline_comment|/* ----- Override flag bits ----- */
DECL|macro|SK_ADDR_LOGICAL_ADDRESS
mdefine_line|#define SK_ADDR_LOGICAL_ADDRESS&t;&t;0
DECL|macro|SK_ADDR_VIRTUAL_ADDRESS
mdefine_line|#define SK_ADDR_VIRTUAL_ADDRESS&t;&t;(SK_ADDR_LOGICAL_ADDRESS)&t;/* old */
DECL|macro|SK_ADDR_PHYSICAL_ADDRESS
mdefine_line|#define SK_ADDR_PHYSICAL_ADDRESS&t;1
multiline_comment|/* ----- Override return values ----- */
DECL|macro|SK_ADDR_OVERRIDE_SUCCESS
mdefine_line|#define SK_ADDR_OVERRIDE_SUCCESS&t;(SK_ADDR_SUCCESS)
DECL|macro|SK_ADDR_DUPLICATE_ADDRESS
mdefine_line|#define SK_ADDR_DUPLICATE_ADDRESS&t;1
DECL|macro|SK_ADDR_MULTICAST_ADDRESS
mdefine_line|#define SK_ADDR_MULTICAST_ADDRESS&t;2
multiline_comment|/* ----- Partitioning of excact match table ----- */
DECL|macro|SK_ADDR_EXACT_MATCHES
mdefine_line|#define SK_ADDR_EXACT_MATCHES&t;&t;16&t;/* #Exact match entries. */
DECL|macro|SK_ADDR_FIRST_MATCH_RLMT
mdefine_line|#define SK_ADDR_FIRST_MATCH_RLMT&t;1
DECL|macro|SK_ADDR_LAST_MATCH_RLMT
mdefine_line|#define SK_ADDR_LAST_MATCH_RLMT&t;&t;2
DECL|macro|SK_ADDR_FIRST_MATCH_DRV
mdefine_line|#define SK_ADDR_FIRST_MATCH_DRV&t;&t;3
DECL|macro|SK_ADDR_LAST_MATCH_DRV
mdefine_line|#define SK_ADDR_LAST_MATCH_DRV&t;&t;(SK_ADDR_EXACT_MATCHES - 1)
multiline_comment|/* ----- SkAddrMcAdd/SkAddrMcUpdate return values ----- */
DECL|macro|SK_MC_FILTERING_EXACT
mdefine_line|#define SK_MC_FILTERING_EXACT&t;&t;0&t;/* Exact filtering. */
DECL|macro|SK_MC_FILTERING_INEXACT
mdefine_line|#define SK_MC_FILTERING_INEXACT&t;&t;1&t;/* Inexact filtering. */
multiline_comment|/* ----- Additional SkAddrMcAdd return values ----- */
DECL|macro|SK_MC_ILLEGAL_ADDRESS
mdefine_line|#define SK_MC_ILLEGAL_ADDRESS&t;&t;2&t;/* Illegal address. */
DECL|macro|SK_MC_ILLEGAL_PORT
mdefine_line|#define SK_MC_ILLEGAL_PORT&t;&t;&t;3&t;/* Illegal port (not the active one). */
DECL|macro|SK_MC_RLMT_OVERFLOW
mdefine_line|#define SK_MC_RLMT_OVERFLOW&t;&t;&t;4&t;/* Too many RLMT mc addresses. */
multiline_comment|/* Promiscuous mode bits ----- */
DECL|macro|SK_PROM_MODE_NONE
mdefine_line|#define SK_PROM_MODE_NONE&t;&t;&t;0&t;/* Normal receive. */
DECL|macro|SK_PROM_MODE_LLC
mdefine_line|#define SK_PROM_MODE_LLC&t;&t;&t;1&t;/* Receive all LLC frames. */
DECL|macro|SK_PROM_MODE_ALL_MC
mdefine_line|#define SK_PROM_MODE_ALL_MC&t;&t;&t;2&t;/* Receive all multicast frames. */
multiline_comment|/* #define SK_PROM_MODE_NON_LLC&t;&t;4 */
multiline_comment|/* Receive all non-LLC frames. */
multiline_comment|/* Macros */
macro_line|#ifndef SK_ADDR_EQUAL
macro_line|#ifndef SK_ADDR_DWORD_COMPARE
DECL|macro|SK_ADDR_EQUAL
mdefine_line|#define SK_ADDR_EQUAL(A1,A2)&t;( &bslash;&n;&t;((SK_U8 *)(A1))[5] == ((SK_U8 *)(A2))[5] &amp;&amp; &bslash;&n;&t;((SK_U8 *)(A1))[4] == ((SK_U8 *)(A2))[4] &amp;&amp; &bslash;&n;&t;((SK_U8 *)(A1))[3] == ((SK_U8 *)(A2))[3] &amp;&amp; &bslash;&n;&t;((SK_U8 *)(A1))[2] == ((SK_U8 *)(A2))[2] &amp;&amp; &bslash;&n;&t;((SK_U8 *)(A1))[1] == ((SK_U8 *)(A2))[1] &amp;&amp; &bslash;&n;&t;((SK_U8 *)(A1))[0] == ((SK_U8 *)(A2))[0])
macro_line|#else&t;/* SK_ADDR_DWORD_COMPARE */
DECL|macro|SK_ADDR_EQUAL
mdefine_line|#define SK_ADDR_EQUAL(A1,A2)&t;( &bslash;&n;&t;*(SK_U32 *)&amp;(((SK_U8 *)(A1))[2]) == *(SK_U32 *)&amp;(((SK_U8 *)(A2))[2]) &amp;&amp; &bslash;&n;&t;*(SK_U32 *)&amp;(((SK_U8 *)(A1))[0]) == *(SK_U32 *)&amp;(((SK_U8 *)(A2))[0]))
macro_line|#endif&t;/* SK_ADDR_DWORD_COMPARE */
macro_line|#endif&t;/* SK_ADDR_EQUAL */
multiline_comment|/* typedefs *******************************************************************/
DECL|struct|s_MacAddr
r_typedef
r_struct
id|s_MacAddr
(brace
DECL|member|a
id|SK_U8
id|a
(braket
id|SK_MAC_ADDR_LEN
)braket
suffix:semicolon
DECL|typedef|SK_MAC_ADDR
)brace
id|SK_MAC_ADDR
suffix:semicolon
multiline_comment|/* SK_FILTER is used to ensure alignment of the filter. */
DECL|union|s_InexactFilter
r_typedef
r_union
id|s_InexactFilter
(brace
DECL|member|Bytes
id|SK_U8
id|Bytes
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|Val
id|SK_U64
id|Val
suffix:semicolon
multiline_comment|/* Dummy entry for alignment only. */
DECL|typedef|SK_FILTER64
)brace
id|SK_FILTER64
suffix:semicolon
DECL|struct|s_AddrPort
r_typedef
r_struct
id|s_AddrPort
(brace
multiline_comment|/* ----- Public part (read-only) ----- */
DECL|member|CurrentMacAddress
id|SK_MAC_ADDR
id|CurrentMacAddress
suffix:semicolon
multiline_comment|/* Current physical MAC Address. */
DECL|member|PermanentMacAddress
id|SK_MAC_ADDR
id|PermanentMacAddress
suffix:semicolon
multiline_comment|/* Permanent physical MAC Address. */
DECL|member|PromMode
r_int
id|PromMode
suffix:semicolon
multiline_comment|/* Promiscuous Mode. */
multiline_comment|/* ----- Private part ----- */
DECL|member|PreviousMacAddress
id|SK_MAC_ADDR
id|PreviousMacAddress
suffix:semicolon
multiline_comment|/* Prev. phys. MAC Address. */
DECL|member|CurrentMacAddressSet
id|SK_BOOL
id|CurrentMacAddressSet
suffix:semicolon
multiline_comment|/* CurrentMacAddress is set. */
DECL|member|Align01
id|SK_U8
id|Align01
suffix:semicolon
DECL|member|FirstExactMatchRlmt
id|SK_U32
id|FirstExactMatchRlmt
suffix:semicolon
DECL|member|NextExactMatchRlmt
id|SK_U32
id|NextExactMatchRlmt
suffix:semicolon
DECL|member|FirstExactMatchDrv
id|SK_U32
id|FirstExactMatchDrv
suffix:semicolon
DECL|member|NextExactMatchDrv
id|SK_U32
id|NextExactMatchDrv
suffix:semicolon
DECL|member|Exact
id|SK_MAC_ADDR
id|Exact
(braket
id|SK_ADDR_EXACT_MATCHES
)braket
suffix:semicolon
DECL|member|InexactFilter
id|SK_FILTER64
id|InexactFilter
suffix:semicolon
multiline_comment|/* For 64-bit hash register. */
DECL|typedef|SK_ADDR_PORT
)brace
id|SK_ADDR_PORT
suffix:semicolon
DECL|struct|s_Addr
r_typedef
r_struct
id|s_Addr
(brace
multiline_comment|/* ----- Public part (read-only) ----- */
DECL|member|Port
id|SK_ADDR_PORT
id|Port
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
DECL|member|PermanentMacAddress
id|SK_MAC_ADDR
id|PermanentMacAddress
suffix:semicolon
multiline_comment|/* Logical MAC Address. */
DECL|member|CurrentMacAddress
id|SK_MAC_ADDR
id|CurrentMacAddress
suffix:semicolon
multiline_comment|/* Logical MAC Address. */
multiline_comment|/* ----- Private part ----- */
DECL|member|ActivePort
id|SK_U32
id|ActivePort
suffix:semicolon
multiline_comment|/* View of module ADDR. */
DECL|member|CurrentMacAddressSet
id|SK_BOOL
id|CurrentMacAddressSet
suffix:semicolon
multiline_comment|/* CurrentMacAddress is set. */
DECL|member|Align01
id|SK_U8
id|Align01
suffix:semicolon
DECL|member|Align02
id|SK_U16
id|Align02
suffix:semicolon
DECL|typedef|SK_ADDR
)brace
id|SK_ADDR
suffix:semicolon
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifndef SK_KR_PROTO
multiline_comment|/* Functions provided by SkAddr */
multiline_comment|/* ANSI/C++ compliant function prototypes */
r_extern
r_int
id|SkAddrInit
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
id|SkAddrMcClear
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
id|PortIdx
comma
r_int
id|Flags
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrMcAdd
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
id|PortIdx
comma
id|SK_MAC_ADDR
op_star
id|pMc
comma
r_int
id|Flags
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrMcUpdate
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
id|PortIdx
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrOverride
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
id|PortIdx
comma
id|SK_MAC_ADDR
op_star
id|pNewAddr
comma
r_int
id|Flags
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrPromiscuousChange
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
id|PortIdx
comma
r_int
id|NewPromMode
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrSwap
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
id|FromPortIdx
comma
id|SK_U32
id|ToPortIdx
)paren
suffix:semicolon
macro_line|#else&t;/* defined(SK_KR_PROTO)) */
multiline_comment|/* Non-ANSI/C++ compliant function prototypes */
macro_line|#error KR-style prototypes are not yet provided.
macro_line|#endif&t;/* defined(SK_KR_PROTO)) */
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_SKADDR_H */
eof
