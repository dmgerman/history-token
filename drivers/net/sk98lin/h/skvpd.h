multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skvpd.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.10 $&n; * Date:&t;$Date: 2000/08/10 11:29:07 $&n; * Purpose:&t;Defines and Macros for VPD handling&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2000 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skvpd.h,v $&n; *&t;Revision 1.10  2000/08/10 11:29:07  rassmann&n; *&t;Editorial changes.&n; *&t;Preserving 32-bit alignment in structs for the adapter context.&n; *&t;Removed unused function VpdWriteDword() (#if 0).&n; *&t;Made VpdReadKeyword() available for SKDIAG only.&n; *&t;&n; *&t;Revision 1.9  1999/11/22 14:02:27  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.8  1999/03/11 14:26:40  malthoff&n; *&t;Replace __STDC__ with SK_KR_PROTO.&n; *&t;&n; *&t;Revision 1.7  1998/10/28 07:27:17  gklug&n; *&t;rmv: SWAP macros&n; *&t;add: VPD_IN/OUT8 macros&n; *&t;chg: interface definition&n; *&t;&n; *&t;Revision 1.6  1998/10/22 10:03:44  gklug&n; *&t;fix: use SK_OUT16 instead of SK_OUTW&n; *&t;&n; *&t;Revision 1.5  1998/10/14 07:05:31  cgoos&n; *&t;Changed constants in SK_SWAP_32 to UL.&n; *&t;&n; *&t;Revision 1.4  1998/08/19 08:14:09  gklug&n; *&t;fix: remove struct keyword as much as possible from the c-code (see CCC)&n; *&t;&n; *&t;Revision 1.3  1998/08/18 08:18:56  malthoff&n; *&t;Modify VPD in and out macros for SK_DIAG&n; *&t;&n; *&t;Revision 1.2  1998/07/03 14:49:08  malthoff&n; *&t;Add VPD_INxx() and VPD_OUTxx() macros for the Diagnostics tool.&n; *&t;&n; *&t;Revision 1.1  1998/06/19 14:08:03  malthoff&n; *&t;Created.&n; *&t;&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * skvpd.h&t;contains Diagnostic specific defines for VPD handling&n; */
macro_line|#ifndef __INC_SKVPD_H_
DECL|macro|__INC_SKVPD_H_
mdefine_line|#define __INC_SKVPD_H_
multiline_comment|/*&n; * Define Resource Type Identifiers and VPD keywords&n; */
DECL|macro|RES_ID
mdefine_line|#define&t;RES_ID&t;&t;0x82&t;/* Resource Type ID String (Product Name) */
DECL|macro|RES_VPD_R
mdefine_line|#define RES_VPD_R&t;0x90&t;/* start of VPD read only area */
DECL|macro|RES_VPD_W
mdefine_line|#define RES_VPD_W&t;0x91&t;/* start of VPD read/write area */
DECL|macro|RES_END
mdefine_line|#define RES_END&t;&t;0x78&t;/* Resource Type End Tag */
macro_line|#ifndef VPD_NAME
DECL|macro|VPD_NAME
mdefine_line|#define VPD_NAME&t;&quot;Name&quot;&t;/* Product Name, VPD name of RES_ID */
macro_line|#endif&t;/* VPD_NAME */
DECL|macro|VPD_PN
mdefine_line|#define VPD_PN&t;&t;&quot;PN&quot;&t;/* Adapter Part Number */
DECL|macro|VPD_EC
mdefine_line|#define&t;VPD_EC&t;&t;&quot;EC&quot;&t;/* Adapter Engineering Level */
DECL|macro|VPD_MN
mdefine_line|#define VPD_MN&t;&t;&quot;MN&quot;&t;/* Manufacture ID */
DECL|macro|VPD_SN
mdefine_line|#define VPD_SN&t;&t;&quot;SN&quot;&t;/* Serial Number */
DECL|macro|VPD_CP
mdefine_line|#define VPD_CP&t;&t;&quot;CP&quot;&t;/* Extended Capability */
DECL|macro|VPD_RV
mdefine_line|#define VPD_RV&t;&t;&quot;RV&quot;&t;/* Checksum and Reserved */
DECL|macro|VPD_YA
mdefine_line|#define&t;VPD_YA&t;&t;&quot;YA&quot;&t;/* Asset Tag Identifier */
DECL|macro|VPD_VL
mdefine_line|#define VPD_VL&t;&t;&quot;VL&quot;&t;/* First Error Log Message (SK specific) */
DECL|macro|VPD_VF
mdefine_line|#define VPD_VF&t;&t;&quot;VF&quot;&t;/* Second Error Log Message (SK specific) */
DECL|macro|VPD_RW
mdefine_line|#define VPD_RW&t;&t;&quot;RW&quot;&t;/* Remaining Read / Write Area */
multiline_comment|/* &squot;type&squot; values for vpd_setup_para() */
DECL|macro|VPD_RO_KEY
mdefine_line|#define VPD_RO_KEY&t;1&t;/* RO keys are &quot;PN&quot;, &quot;EC&quot;, &quot;MN&quot;, &quot;SN&quot;, &quot;RV&quot; */
DECL|macro|VPD_RW_KEY
mdefine_line|#define VPD_RW_KEY&t;2&t;/* RW keys are &quot;Yx&quot;, &quot;Vx&quot;, and &quot;RW&quot; */
multiline_comment|/* &squot;op&squot; values for vpd_setup_para() */
DECL|macro|ADD_KEY
mdefine_line|#define&t;ADD_KEY&t;&t;1&t;/* add the key at the pos &quot;RV&quot; or &quot;RW&quot; */
DECL|macro|OWR_KEY
mdefine_line|#define OWR_KEY&t;&t;2&t;/* overwrite key if already exists */
multiline_comment|/*&n; * Define READ and WRITE Constants.&n; */
DECL|macro|VPD_SIZE
mdefine_line|#define&t;VPD_SIZE&t;512
DECL|macro|VPD_READ
mdefine_line|#define VPD_READ&t;0x0000
DECL|macro|VPD_WRITE
mdefine_line|#define VPD_WRITE&t;0x8000
DECL|macro|VPD_STOP
mdefine_line|#define VPD_STOP(pAC,IoC)&t;VPD_OUT16(pAC,IoC,PCI_VPD_ADR_REG,VPD_WRITE)
DECL|macro|VPD_GET_RES_LEN
mdefine_line|#define VPD_GET_RES_LEN(p)&t;((unsigned int) &bslash;&n;&t;&t;&t;&t;&t;(* (SK_U8 *)&amp;(p)[1]) |&bslash;&n;&t;&t;&t;&t;&t;((* (SK_U8 *)&amp;(p)[2]) &lt;&lt; 8))
DECL|macro|VPD_GET_VPD_LEN
mdefine_line|#define VPD_GET_VPD_LEN(p)&t;((unsigned int)(* (SK_U8 *)&amp;(p)[2]))
DECL|macro|VPD_GET_VAL
mdefine_line|#define VPD_GET_VAL(p)&t;&t;((char *)&amp;(p)[3])
DECL|macro|VPD_MAX_LEN
mdefine_line|#define VPD_MAX_LEN&t;50
multiline_comment|/* VPD status */
multiline_comment|/* bit 7..1 reserved */
DECL|macro|VPD_VALID
mdefine_line|#define VPD_VALID&t;(1&lt;&lt;0)&t;/* VPD data buffer, vpd_free_ro, */
multiline_comment|/* and vpd_free_rw valid&t; */
multiline_comment|/*&n; * VPD structs&n; */
DECL|struct|s_vpd_status
r_typedef
r_struct
id|s_vpd_status
(brace
DECL|member|Align01
r_int
r_int
id|Align01
suffix:semicolon
multiline_comment|/* Alignment */
DECL|member|vpd_status
r_int
r_int
id|vpd_status
suffix:semicolon
multiline_comment|/* VPD status, description see above */
DECL|member|vpd_free_ro
r_int
id|vpd_free_ro
suffix:semicolon
multiline_comment|/* unused bytes in read only area */
DECL|member|vpd_free_rw
r_int
id|vpd_free_rw
suffix:semicolon
multiline_comment|/* bytes available in read/write area */
DECL|typedef|SK_VPD_STATUS
)brace
id|SK_VPD_STATUS
suffix:semicolon
DECL|struct|s_vpd
r_typedef
r_struct
id|s_vpd
(brace
DECL|member|v
id|SK_VPD_STATUS
id|v
suffix:semicolon
multiline_comment|/* VPD status structure */
DECL|member|vpd_buf
r_char
id|vpd_buf
(braket
id|VPD_SIZE
)braket
suffix:semicolon
multiline_comment|/* VPD buffer */
DECL|typedef|SK_VPD
)brace
id|SK_VPD
suffix:semicolon
DECL|struct|s_vpd_para
r_typedef
r_struct
id|s_vpd_para
(brace
DECL|member|p_len
r_int
r_int
id|p_len
suffix:semicolon
multiline_comment|/* parameter length */
DECL|member|p_val
r_char
op_star
id|p_val
suffix:semicolon
multiline_comment|/* points to the value */
DECL|typedef|SK_VPD_PARA
)brace
id|SK_VPD_PARA
suffix:semicolon
multiline_comment|/*&n; * structure of Large Resource Type Identifiers&n; */
multiline_comment|/* was removed because of alignment problems */
multiline_comment|/*&n; * sturcture of VPD keywords&n; */
DECL|struct|s_vpd_key
r_typedef
r_struct
id|s_vpd_key
(brace
DECL|member|p_key
r_char
id|p_key
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 2 bytes ID string */
DECL|member|p_len
r_int
r_char
id|p_len
suffix:semicolon
multiline_comment|/* 1 byte length */
DECL|member|p_val
r_char
id|p_val
suffix:semicolon
multiline_comment|/* start of the value string */
DECL|typedef|SK_VPD_KEY
)brace
id|SK_VPD_KEY
suffix:semicolon
multiline_comment|/*&n; * System specific VPD macros&n; */
macro_line|#ifndef SKDIAG
macro_line|#ifndef VPD_DO_IO
DECL|macro|VPD_OUT8
mdefine_line|#define VPD_OUT8(pAC,IoC,Addr,Val)&t;(void)SkPciWriteCfgByte(pAC,Addr,Val)
DECL|macro|VPD_OUT16
mdefine_line|#define VPD_OUT16(pAC,IoC,Addr,Val)&t;(void)SkPciWriteCfgWord(pAC,Addr,Val)
DECL|macro|VPD_OUT32
mdefine_line|#define VPD_OUT32(pAC,IoC,Addr,Val)&t;(void)SkPciWriteCfgDWord(pAC,Addr,Val)
DECL|macro|VPD_IN8
mdefine_line|#define VPD_IN8(pAC,IoC,Addr,pVal)&t;(void)SkPciReadCfgByte(pAC,Addr,pVal)
DECL|macro|VPD_IN16
mdefine_line|#define VPD_IN16(pAC,IoC,Addr,pVal)&t;(void)SkPciReadCfgWord(pAC,Addr,pVal)
DECL|macro|VPD_IN32
mdefine_line|#define VPD_IN32(pAC,IoC,Addr,pVal)&t;(void)SkPciReadCfgDWord(pAC,Addr,pVal)
macro_line|#else&t;/* VPD_DO_IO */
DECL|macro|VPD_OUT8
mdefine_line|#define VPD_OUT8(pAC,IoC,Addr,Val)&t;SK_OUT8(IoC,PCI_C(Addr),Val)
DECL|macro|VPD_OUT16
mdefine_line|#define VPD_OUT16(pAC,IoC,Addr,Val)&t;SK_OUT16(IoC,PCI_C(Addr),Val)
DECL|macro|VPD_OUT32
mdefine_line|#define VPD_OUT32(pAC,IoC,Addr,Val)&t;SK_OUT32(IoC,PCI_C(Addr),Val)
DECL|macro|VPD_IN8
mdefine_line|#define VPD_IN8(pAC,IoC,Addr,pVal)&t;SK_IN8(IoC,PCI_C(Addr),pVal)
DECL|macro|VPD_IN16
mdefine_line|#define VPD_IN16(pAC,IoC,Addr,pVal)&t;SK_IN16(IoC,PCI_C(Addr),pVal)
DECL|macro|VPD_IN32
mdefine_line|#define VPD_IN32(pAC,IoC,Addr,pVal)&t;SK_IN32(IoC,PCI_C(Addr),pVal)
macro_line|#endif&t;/* VPD_DO_IO */
macro_line|#else&t;/* SKDIAG */
DECL|macro|VPD_OUT8
mdefine_line|#define VPD_OUT8(pAC,Ioc,Addr,Val) {&t;&t;&t;&bslash;&n;&t;&t;if ((pAC)-&gt;DgT.DgUseCfgCycle)&t;&t;&t;&bslash;&n;&t;&t;&t;SkPciWriteCfgByte(pAC,Addr,Val);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SK_OUT8(pAC,PCI_C(Addr),Val);&t;&t;&bslash;&n;&t;&t;}
DECL|macro|VPD_OUT16
mdefine_line|#define VPD_OUT16(pAC,Ioc,Addr,Val) {&t;&t;&t;&bslash;&n;&t;&t;if ((pAC)-&gt;DgT.DgUseCfgCycle)&t;&t;&t;&bslash;&n;&t;&t;&t;SkPciWriteCfgWord(pAC,Addr,Val);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SK_OUT16(pAC,PCI_C(Addr),Val);&t;&t;&bslash;&n;&t;&t;}
DECL|macro|VPD_OUT32
mdefine_line|#define VPD_OUT32(pAC,Ioc,Addr,Val) {&t;&t;&t;&bslash;&n;&t;&t;if ((pAC)-&gt;DgT.DgUseCfgCycle)&t;&t;&t;&bslash;&n;&t;&t;&t;SkPciWriteCfgDWord(pAC,Addr,Val);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SK_OUT32(pAC,PCI_C(Addr),Val); &t;&t;&bslash;&n;&t;&t;}
DECL|macro|VPD_IN8
mdefine_line|#define VPD_IN8(pAC,Ioc,Addr,pVal) {&t;&t;&t;&bslash;&n;&t;&t;if ((pAC)-&gt;DgT.DgUseCfgCycle) &t;&t;&t;&bslash;&n;&t;&t;&t;SkPciReadCfgByte(pAC,Addr,pVal);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SK_IN8(pAC,PCI_C(Addr),pVal); &t;&t;&bslash;&n;&t;&t;}
DECL|macro|VPD_IN16
mdefine_line|#define VPD_IN16(pAC,Ioc,Addr,pVal) {&t;&t;&t;&bslash;&n;&t;&t;if ((pAC)-&gt;DgT.DgUseCfgCycle) &t;&t;&t;&bslash;&n;&t;&t;&t;SkPciReadCfgWord(pAC,Addr,pVal);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SK_IN16(pAC,PCI_C(Addr),pVal); &t;&t;&bslash;&n;&t;&t;}
DECL|macro|VPD_IN32
mdefine_line|#define VPD_IN32(pAC,Ioc,Addr,pVal) {&t;&t;&t;&bslash;&n;&t;&t;if ((pAC)-&gt;DgT.DgUseCfgCycle)&t;&t;&t;&bslash;&n;&t;&t;&t;SkPciReadCfgDWord(pAC,Addr,pVal);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SK_IN32(pAC,PCI_C(Addr),pVal);&t;&t;&bslash;&n;&t;&t;}
macro_line|#endif&t;/* nSKDIAG */
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifndef&t;SK_KR_PROTO
macro_line|#ifdef SKDIAG
r_extern
id|SK_U32
id|VpdReadDWord
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
id|addr
)paren
suffix:semicolon
macro_line|#endif&t;/* SKDIAG */
r_extern
r_int
id|VpdSetupPara
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
r_char
op_star
id|key
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|type
comma
r_int
id|op
)paren
suffix:semicolon
r_extern
id|SK_VPD_STATUS
op_star
id|VpdStat
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
)paren
suffix:semicolon
r_extern
r_int
id|VpdKeys
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_char
op_star
id|buf
comma
r_int
op_star
id|len
comma
r_int
op_star
id|elements
)paren
suffix:semicolon
r_extern
r_int
id|VpdRead
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_char
op_star
id|key
comma
r_char
op_star
id|buf
comma
r_int
op_star
id|len
)paren
suffix:semicolon
r_extern
id|SK_BOOL
id|VpdMayWrite
c_func
(paren
r_char
op_star
id|key
)paren
suffix:semicolon
r_extern
r_int
id|VpdWrite
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_char
op_star
id|key
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_int
id|VpdDelete
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_char
op_star
id|key
)paren
suffix:semicolon
r_extern
r_int
id|VpdUpdate
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
)paren
suffix:semicolon
r_extern
r_void
id|VpdErrLog
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_char
op_star
id|msg
)paren
suffix:semicolon
macro_line|#ifdef&t;SKDIAG
r_extern
r_int
id|VpdReadBlock
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_char
op_star
id|buf
comma
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|VpdWriteBlock
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_char
op_star
id|buf
comma
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif&t;/* SKDIAG */
macro_line|#else&t;/* SK_KR_PROTO */
r_extern
id|SK_U32
id|VpdReadDWord
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|VpdSetupPara
c_func
(paren
)paren
suffix:semicolon
r_extern
id|SK_VPD_STATUS
op_star
id|VpdStat
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|VpdKeys
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|VpdRead
c_func
(paren
)paren
suffix:semicolon
r_extern
id|SK_BOOL
id|VpdMayWrite
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|VpdWrite
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|VpdDelete
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|VpdUpdate
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|VpdErrLog
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;/* SK_KR_PROTO */
macro_line|#endif&t;/* __INC_SKVPD_H_ */
eof
