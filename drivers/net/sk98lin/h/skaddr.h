multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skaddr.h&n; * Project:&t;Gigabit Ethernet Adapters, ADDR-Modul&n; * Version:&t;$Revision: 1.29 $&n; * Date:&t;$Date: 2003/05/13 16:57:24 $&n; * Purpose:&t;Header file for Address Management (MC, UC, Prom).&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * This module is intended to manage multicast addresses and promiscuous mode&n; * on GEnesis adapters.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;&quot;skdrv1st.h&quot;&n; *&t;...&n; *&t;&quot;sktypes.h&quot;&n; *&t;&quot;skqueue.h&quot;&n; *&t;&quot;skaddr.h&quot;&n; *&t;...&n; *&t;&quot;skdrv2nd.h&quot;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKADDR_H
DECL|macro|__INC_SKADDR_H
mdefine_line|#define __INC_SKADDR_H
macro_line|#ifdef __cplusplus
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
mdefine_line|#define SK_ADDR_ILLEGAL_PORT&t;&t;&t;100&t;/* Port number too high. */
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
DECL|macro|SK_ADDR_CLEAR_LOGICAL
mdefine_line|#define SK_ADDR_CLEAR_LOGICAL&t;&t;2
DECL|macro|SK_ADDR_SET_LOGICAL
mdefine_line|#define SK_ADDR_SET_LOGICAL&t;&t;&t;4
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
macro_line|#ifdef OLD_STUFF
macro_line|#ifndef SK_ADDR_EQUAL
multiline_comment|/*&n; * &quot;&amp;&quot; instead of &quot;&amp;&amp;&quot; allows better optimization on IA-64.&n; * The replacement is safe here, as all bytes exist.&n; */
macro_line|#ifndef SK_ADDR_DWORD_COMPARE
DECL|macro|SK_ADDR_EQUAL
mdefine_line|#define SK_ADDR_EQUAL(A1,A2)&t;( &bslash;&n;&t;(((SK_U8 *)(A1))[5] == ((SK_U8 *)(A2))[5]) &amp; &bslash;&n;&t;(((SK_U8 *)(A1))[4] == ((SK_U8 *)(A2))[4]) &amp; &bslash;&n;&t;(((SK_U8 *)(A1))[3] == ((SK_U8 *)(A2))[3]) &amp; &bslash;&n;&t;(((SK_U8 *)(A1))[2] == ((SK_U8 *)(A2))[2]) &amp; &bslash;&n;&t;(((SK_U8 *)(A1))[1] == ((SK_U8 *)(A2))[1]) &amp; &bslash;&n;&t;(((SK_U8 *)(A1))[0] == ((SK_U8 *)(A2))[0]))
macro_line|#else&t;/* SK_ADDR_DWORD_COMPARE */
DECL|macro|SK_ADDR_EQUAL
mdefine_line|#define SK_ADDR_EQUAL(A1,A2)&t;( &bslash;&n;&t;(*(SK_U32 *)&amp;(((SK_U8 *)(A1))[2]) == *(SK_U32 *)&amp;(((SK_U8 *)(A2))[2])) &amp; &bslash;&n;&t;(*(SK_U32 *)&amp;(((SK_U8 *)(A1))[0]) == *(SK_U32 *)&amp;(((SK_U8 *)(A2))[0])))
macro_line|#endif&t;/* SK_ADDR_DWORD_COMPARE */
macro_line|#endif&t;/* SK_ADDR_EQUAL */
macro_line|#endif /* 0 */
macro_line|#ifndef SK_ADDR_EQUAL
macro_line|#ifndef SK_ADDR_DWORD_COMPARE
DECL|macro|SK_ADDR_EQUAL
mdefine_line|#define SK_ADDR_EQUAL(A1,A2)&t;( &bslash;&n;&t;(((SK_U8 SK_FAR *)(A1))[5] == ((SK_U8 SK_FAR *)(A2))[5]) &amp; &bslash;&n;&t;(((SK_U8 SK_FAR *)(A1))[4] == ((SK_U8 SK_FAR *)(A2))[4]) &amp; &bslash;&n;&t;(((SK_U8 SK_FAR *)(A1))[3] == ((SK_U8 SK_FAR *)(A2))[3]) &amp; &bslash;&n;&t;(((SK_U8 SK_FAR *)(A1))[2] == ((SK_U8 SK_FAR *)(A2))[2]) &amp; &bslash;&n;&t;(((SK_U8 SK_FAR *)(A1))[1] == ((SK_U8 SK_FAR *)(A2))[1]) &amp; &bslash;&n;&t;(((SK_U8 SK_FAR *)(A1))[0] == ((SK_U8 SK_FAR *)(A2))[0]))
macro_line|#else&t;/* SK_ADDR_DWORD_COMPARE */
DECL|macro|SK_ADDR_EQUAL
mdefine_line|#define SK_ADDR_EQUAL(A1,A2)&t;( &bslash;&n;&t;(*(SK_U16 SK_FAR *)&amp;(((SK_U8 SK_FAR *)(A1))[4]) == &bslash;&n;&t;*(SK_U16 SK_FAR *)&amp;(((SK_U8 SK_FAR *)(A2))[4])) &amp;&amp; &bslash;&n;&t;(*(SK_U32 SK_FAR *)&amp;(((SK_U8 SK_FAR *)(A1))[0]) == &bslash;&n;&t;*(SK_U32 SK_FAR *)&amp;(((SK_U8 SK_FAR *)(A2))[0])))
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
DECL|typedef|SK_ADDR_NET
r_typedef
r_struct
id|s_AddrNet
id|SK_ADDR_NET
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
DECL|member|InexactRlmtFilter
id|SK_FILTER64
id|InexactRlmtFilter
suffix:semicolon
multiline_comment|/* For 64-bit hash register. */
DECL|member|InexactDrvFilter
id|SK_FILTER64
id|InexactDrvFilter
suffix:semicolon
multiline_comment|/* For 64-bit hash register. */
DECL|typedef|SK_ADDR_PORT
)brace
id|SK_ADDR_PORT
suffix:semicolon
DECL|struct|s_AddrNet
r_struct
id|s_AddrNet
(brace
multiline_comment|/* ----- Public part (read-only) ----- */
DECL|member|CurrentMacAddress
id|SK_MAC_ADDR
id|CurrentMacAddress
suffix:semicolon
multiline_comment|/* Logical MAC Address. */
DECL|member|PermanentMacAddress
id|SK_MAC_ADDR
id|PermanentMacAddress
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
)brace
suffix:semicolon
DECL|struct|s_Addr
r_typedef
r_struct
id|s_Addr
(brace
multiline_comment|/* ----- Public part (read-only) ----- */
DECL|member|Net
id|SK_ADDR_NET
id|Net
(braket
id|SK_MAX_NETS
)braket
suffix:semicolon
DECL|member|Port
id|SK_ADDR_PORT
id|Port
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
multiline_comment|/* ----- Private part ----- */
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
id|PortNumber
comma
r_int
id|Flags
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrXmacMcClear
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
id|PortNumber
comma
r_int
id|Flags
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrGmacMcClear
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
id|PortNumber
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
id|PortNumber
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
id|SkAddrXmacMcAdd
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
id|PortNumber
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
id|SkAddrGmacMcAdd
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
id|PortNumber
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
id|PortNumber
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrXmacMcUpdate
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
id|PortNumber
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrGmacMcUpdate
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
id|PortNumber
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
id|PortNumber
comma
id|SK_MAC_ADDR
id|SK_FAR
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
id|PortNumber
comma
r_int
id|NewPromMode
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrXmacPromiscuousChange
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
id|PortNumber
comma
r_int
id|NewPromMode
)paren
suffix:semicolon
r_extern
r_int
id|SkAddrGmacPromiscuousChange
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
id|PortNumber
comma
r_int
id|NewPromMode
)paren
suffix:semicolon
macro_line|#ifndef SK_SLIM
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
id|FromPortNumber
comma
id|SK_U32
id|ToPortNumber
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else&t;/* defined(SK_KR_PROTO)) */
multiline_comment|/* Non-ANSI/C++ compliant function prototypes */
macro_line|#error KR-style prototypes are not yet provided.
macro_line|#endif&t;/* defined(SK_KR_PROTO)) */
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_SKADDR_H */
eof
