multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skdrv1st.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.9.2.1 $&n; * Date:&t;$Date: 2001/03/12 16:50:59 $&n; * Purpose:&t;First header file for driver and all other modules&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2001 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skdrv1st.h,v $&n; *&t;Revision 1.9.2.1  2001/03/12 16:50:59  mlindner&n; *&t;chg: kernel 2.4 adaption&n; *&t;&n; *&t;Revision 1.9  2001/01/22 14:16:04  mlindner&n; *&t;added ProcFs functionality&n; *&t;Dual Net functionality integrated&n; *&t;Rlmt networks added&n; *&t;&n; *&t;Revision 1.8  2000/02/21 12:19:18  cgoos&n; *&t;Added default for SK_DEBUG_CHKMOD/_CHKCAT&n; *&t;&n; *&t;Revision 1.7  1999/11/22 13:50:00  cgoos&n; *&t;Changed license header to GPL.&n; *&t;Added overwrite for several functions.&n; *&t;Removed linux 2.0.x definitions.&n; *&t;Removed PCI vendor ID definition (now in kernel).&n; *&t;&n; *&t;Revision 1.6  1999/07/27 08:03:33  cgoos&n; *&t;Changed SK_IN/OUT macros to readX/writeX instead of memory&n; *&t;accesses (necessary for ALPHA).&n; *&t;&n; *&t;Revision 1.5  1999/07/23 12:10:21  cgoos&n; *&t;Removed SK_RLMT_SLOW_LOOKAHEAD define.&n; *&t;&n; *&t;Revision 1.4  1999/07/14 12:31:13  cgoos&n; *&t;Added SK_RLMT_SLOW_LOOKAHEAD define.&n; *&t;&n; *&t;Revision 1.3  1999/04/07 10:12:54  cgoos&n; *&t;Added check for KERNEL and OPTIMIZATION defines.&n; *&t;&n; *&t;Revision 1.2  1999/03/01 08:51:47  cgoos&n; *&t;Fixed pcibios_read/write definitions.&n; *&t;&n; *&t;Revision 1.1  1999/02/16 07:40:49  cgoos&n; *&t;First version.&n; *&t;&n; *&t;&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * This is the first include file of the driver, which includes all&n; * neccessary system header files and some of the GEnesis header files.&n; * It also defines some basic items.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;see skge.c&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKDRV1ST_H
DECL|macro|__INC_SKDRV1ST_H
mdefine_line|#define __INC_SKDRV1ST_H
DECL|typedef|SK_AC
r_typedef
r_struct
id|s_AC
id|SK_AC
suffix:semicolon
multiline_comment|/* override some default functions with optimized linux functions */
DECL|macro|SK_PNMI_STORE_U16
mdefine_line|#define SK_PNMI_STORE_U16(p,v)&t;&t;memcpy((char*)(p),(char*)&amp;(v),2)
DECL|macro|SK_PNMI_STORE_U32
mdefine_line|#define SK_PNMI_STORE_U32(p,v)&t;&t;memcpy((char*)(p),(char*)&amp;(v),4)
DECL|macro|SK_PNMI_STORE_U64
mdefine_line|#define SK_PNMI_STORE_U64(p,v)&t;&t;memcpy((char*)(p),(char*)&amp;(v),8)
DECL|macro|SK_PNMI_READ_U16
mdefine_line|#define SK_PNMI_READ_U16(p,v)&t;&t;memcpy((char*)&amp;(v),(char*)(p),2)
DECL|macro|SK_PNMI_READ_U32
mdefine_line|#define SK_PNMI_READ_U32(p,v)&t;&t;memcpy((char*)&amp;(v),(char*)(p),2)
DECL|macro|SK_PNMI_READ_U64
mdefine_line|#define SK_PNMI_READ_U64(p,v)&t;&t;memcpy((char*)&amp;(v),(char*)(p),2)
DECL|macro|SkCsCalculateChecksum
mdefine_line|#define SkCsCalculateChecksum(p,l)&t;((~ip_compute_csum(p, l)) &amp; 0xffff)
DECL|macro|SK_ADDR_EQUAL
mdefine_line|#define SK_ADDR_EQUAL(a1,a2)&t;&t;(!memcmp(a1,a2,6))
macro_line|#if !defined(__OPTIMIZE__)  ||  !defined(__KERNEL__)
macro_line|#warning  You must compile this file with the correct options!
macro_line|#warning  See the last lines of the source file.
macro_line|#error You must compile this driver with &quot;-O&quot;.
macro_line|#endif
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include&t;&quot;h/sktypes.h&quot;
macro_line|#include&t;&quot;h/skerror.h&quot;
macro_line|#include&t;&quot;h/skdebug.h&quot;
macro_line|#include&t;&quot;h/lm80.h&quot;
macro_line|#include&t;&quot;h/xmac_ii.h&quot;
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|SK_LITTLE_ENDIAN
mdefine_line|#define SK_LITTLE_ENDIAN
macro_line|#else
DECL|macro|SK_BIG_ENDIAN
mdefine_line|#define SK_BIG_ENDIAN
macro_line|#endif
multiline_comment|/* we use gethrtime(), return unit: nanoseconds */
DECL|macro|SK_TICKS_PER_SEC
mdefine_line|#define SK_TICKS_PER_SEC&t;HZ
DECL|macro|SK_MEM_MAPPED_IO
mdefine_line|#define&t;SK_MEM_MAPPED_IO
singleline_comment|// #define SK_RLMT_SLOW_LOOKAHEAD
DECL|macro|SK_MAX_MACS
mdefine_line|#define SK_MAX_MACS&t;&t;2
DECL|macro|SK_MAX_NETS
mdefine_line|#define SK_MAX_NETS&t;&t;2
DECL|macro|SK_IOC
mdefine_line|#define SK_IOC&t;&t;&t;char*
DECL|typedef|SK_MBUF
r_typedef
r_struct
id|s_DrvRlmtMbuf
id|SK_MBUF
suffix:semicolon
DECL|macro|SK_CONST64
mdefine_line|#define&t;SK_CONST64&t;INT64_C
DECL|macro|SK_CONSTU64
mdefine_line|#define&t;SK_CONSTU64&t;UINT64_C
DECL|macro|SK_MEMCPY
mdefine_line|#define SK_MEMCPY(dest,src,size)&t;memcpy(dest,src,size)
DECL|macro|SK_MEMCMP
mdefine_line|#define SK_MEMCMP(s1,s2,size)&t;&t;memcmp(s1,s2,size)
DECL|macro|SK_MEMSET
mdefine_line|#define SK_MEMSET(dest,val,size)&t;memset(dest,val,size)
DECL|macro|SK_STRLEN
mdefine_line|#define SK_STRLEN(pStr)&t;&t;&t;strlen((char*)pStr)
DECL|macro|SK_STRNCPY
mdefine_line|#define SK_STRNCPY(pDest,pSrc,size)&t;strncpy((char*)pDest,(char*)pSrc,size)
DECL|macro|SK_STRCMP
mdefine_line|#define SK_STRCMP(pStr1,pStr2)&t;&t;strcmp((char*)pStr1,(char*)pStr2)
multiline_comment|/* macros to access the adapter */
DECL|macro|SK_OUT8
mdefine_line|#define SK_OUT8(b,a,v)&t;&t;writeb(v, (b+a))&t;
DECL|macro|SK_OUT16
mdefine_line|#define SK_OUT16(b,a,v)&t;&t;writew(v, (b+a))&t;
DECL|macro|SK_OUT32
mdefine_line|#define SK_OUT32(b,a,v)&t;&t;writel(v, (b+a))&t;
DECL|macro|SK_IN8
mdefine_line|#define SK_IN8(b,a,pv)&t;&t;(*(pv) = readb(b+a))
DECL|macro|SK_IN16
mdefine_line|#define SK_IN16(b,a,pv)&t;&t;(*(pv) = readw(b+a))
DECL|macro|SK_IN32
mdefine_line|#define SK_IN32(b,a,pv)&t;&t;(*(pv) = readl(b+a))
DECL|macro|int8_t
mdefine_line|#define int8_t&t;&t;char
DECL|macro|int16_t
mdefine_line|#define int16_t&t;&t;short
DECL|macro|int32_t
mdefine_line|#define int32_t&t;&t;long
DECL|macro|int64_t
mdefine_line|#define int64_t&t;&t;long long
DECL|macro|uint8_t
mdefine_line|#define uint8_t&t;&t;u_char
DECL|macro|uint16_t
mdefine_line|#define uint16_t&t;u_short
DECL|macro|uint32_t
mdefine_line|#define uint32_t&t;u_long
DECL|macro|uint64_t
mdefine_line|#define uint64_t&t;unsigned long long
DECL|macro|t_scalar_t
mdefine_line|#define t_scalar_t&t;int
DECL|macro|t_uscalar_t
mdefine_line|#define t_uscalar_t&t;unsigned int
DECL|macro|uintptr_t
mdefine_line|#define uintptr_t&t;unsigned long
DECL|macro|__CONCAT__
mdefine_line|#define __CONCAT__(A,B) A##B
DECL|macro|INT32_C
mdefine_line|#define INT32_C(a)&t;&t;__CONCAT__(a,L)
DECL|macro|INT64_C
mdefine_line|#define INT64_C(a)&t;&t;__CONCAT__(a,LL)
DECL|macro|UINT32_C
mdefine_line|#define UINT32_C(a)&t;&t;__CONCAT__(a,UL)
DECL|macro|UINT64_C
mdefine_line|#define UINT64_C(a)&t;&t;__CONCAT__(a,ULL)
macro_line|#ifdef DEBUG
DECL|macro|SK_DBG_PRINTF
mdefine_line|#define SK_DBG_PRINTF&t;&t;printk
macro_line|#ifndef SK_DEBUG_CHKMOD
DECL|macro|SK_DEBUG_CHKMOD
mdefine_line|#define SK_DEBUG_CHKMOD&t;&t;0
macro_line|#endif
macro_line|#ifndef SK_DEBUG_CHKCAT
DECL|macro|SK_DEBUG_CHKCAT
mdefine_line|#define SK_DEBUG_CHKCAT&t;&t;0
macro_line|#endif
multiline_comment|/* those come from the makefile */
DECL|macro|SK_DBG_CHKMOD
mdefine_line|#define SK_DBG_CHKMOD(pAC)&t;(SK_DEBUG_CHKMOD)
DECL|macro|SK_DBG_CHKCAT
mdefine_line|#define SK_DBG_CHKCAT(pAC)&t;(SK_DEBUG_CHKCAT)
r_extern
r_void
id|SkDbgPrintf
c_func
(paren
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|SK_DBGMOD_DRV
mdefine_line|#define SK_DBGMOD_DRV&t;&t;&t;0x00010000
multiline_comment|/**** possible driver debug categories ********************************/
DECL|macro|SK_DBGCAT_DRV_ENTRY
mdefine_line|#define SK_DBGCAT_DRV_ENTRY&t;&t;0x00010000
DECL|macro|SK_DBGCAT_DRV_SAP
mdefine_line|#define SK_DBGCAT_DRV_SAP&t;&t;0x00020000
DECL|macro|SK_DBGCAT_DRV_MCA
mdefine_line|#define SK_DBGCAT_DRV_MCA&t;&t;0x00040000
DECL|macro|SK_DBGCAT_DRV_TX_PROGRESS
mdefine_line|#define SK_DBGCAT_DRV_TX_PROGRESS&t;0x00080000
DECL|macro|SK_DBGCAT_DRV_RX_PROGRESS
mdefine_line|#define SK_DBGCAT_DRV_RX_PROGRESS&t;0x00100000
DECL|macro|SK_DBGCAT_DRV_PROGRESS
mdefine_line|#define SK_DBGCAT_DRV_PROGRESS&t;&t;0x00200000
DECL|macro|SK_DBGCAT_DRV_MSG
mdefine_line|#define SK_DBGCAT_DRV_MSG&t;&t;0x00400000
DECL|macro|SK_DBGCAT_DRV_PROM
mdefine_line|#define SK_DBGCAT_DRV_PROM&t;&t;0x00800000
DECL|macro|SK_DBGCAT_DRV_TX_FRAME
mdefine_line|#define SK_DBGCAT_DRV_TX_FRAME&t;&t;0x01000000
DECL|macro|SK_DBGCAT_DRV_ERROR
mdefine_line|#define SK_DBGCAT_DRV_ERROR&t;&t;0x02000000
DECL|macro|SK_DBGCAT_DRV_INT_SRC
mdefine_line|#define SK_DBGCAT_DRV_INT_SRC&t;&t;0x04000000
DECL|macro|SK_DBGCAT_DRV_EVENT
mdefine_line|#define SK_DBGCAT_DRV_EVENT&t;&t;0x08000000
macro_line|#endif /* DEBUG */
DECL|macro|SK_ERR_LOG
mdefine_line|#define SK_ERR_LOG&t;&t;SkErrorLog
r_extern
r_void
id|SkErrorLog
c_func
(paren
id|SK_AC
op_star
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* __INC_SKDRV1ST_H */
eof
