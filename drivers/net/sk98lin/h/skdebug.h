multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skdebug.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.10 $&n; * Date:&t;$Date: 1999/11/22 13:47:40 $&n; * Purpose:&t;SK specific DEBUG support&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&t;$Log: skdebug.h,v $&n; *&t;Revision 1.10  1999/11/22 13:47:40  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.9  1999/09/14 14:02:43  rwahl&n; *&t;Added SK_DBGMOD_PECP.&n; *&t;&n; *&t;Revision 1.8  1998/11/25 08:31:54  gklug&n; *&t;fix: no C++ comments allowed in common sources&n; *&t;&n; *&t;Revision 1.7  1998/11/24 16:47:24  swolf&n; *&t;Driver may now define its own SK_DBG_MSG() (eg. in &quot;h/skdrv1st.h&quot;).&n; *&t;&n; *&t;Revision 1.6  1998/10/28 10:23:55  rassmann&n; *&t;ADDED SK_DBGMOD_ADDR.&n; *&t;&n; *&t;Revision 1.5  1998/10/22 09:43:55  gklug&n; *&t;add: CSUM module&n; *&t;&n; *&t;Revision 1.4  1998/10/01 07:54:44  gklug&n; *&t;add: PNMI debug module&n; *&t;&n; *&t;Revision 1.3  1998/09/18 08:32:34  afischer&n; *&t;Macros changed according ssr-spec.:&n; *&t;&t;SK_DBG_MODCHK -&gt; SK_DBG_CHKMOD&n; *&t;&t;SK_DBG_CATCHK -&gt; SK_DBG_CHKCAT&n; *&t;&n; *&t;Revision 1.2  1998/07/03 14:38:25  malthoff&n; *&t;Add category SK_DBGCAT_FATAL.&n; *&t;&n; *&t;Revision 1.1  1998/06/19 13:39:01  malthoff&n; *&t;created.&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKDEBUG_H
DECL|macro|__INC_SKDEBUG_H
mdefine_line|#define __INC_SKDEBUG_H
macro_line|#ifdef&t;DEBUG
macro_line|#ifndef SK_DBG_MSG
DECL|macro|SK_DBG_MSG
mdefine_line|#define SK_DBG_MSG(pAC,comp,cat,arg) &bslash;&n;&t;&t;if ( ((comp) &amp; SK_DBG_CHKMOD(pAC)) &amp;&amp; &t;&bslash;&n;&t;&t;      ((cat) &amp; SK_DBG_CHKCAT(pAC)) ) { &t;&bslash;&n;&t;&t;&t;SK_DBG_PRINTF arg ;&t;&t;&bslash;&n;&t;&t;}
macro_line|#endif
macro_line|#else
DECL|macro|SK_DBG_MSG
mdefine_line|#define SK_DBG_MSG(pAC,comp,lev,arg)
macro_line|#endif
multiline_comment|/* PLS NOTE:&n; * =========&n; * Due to any restrictions of kernel printf routines do not use other&n; * format identifiers as: %x %d %c %s .&n; * Never use any combined format identifiers such as: %lx %ld in your&n; * printf - argument (arg) because some OS specific kernel printfs may&n; * only support some basic identifiers.&n; */
multiline_comment|/* Debug modules */
DECL|macro|SK_DBGMOD_MERR
mdefine_line|#define SK_DBGMOD_MERR&t;0x00000001L&t;/* general module error indication */
DECL|macro|SK_DBGMOD_HWM
mdefine_line|#define SK_DBGMOD_HWM&t;0x00000002L&t;/* Hardware init module */
DECL|macro|SK_DBGMOD_RLMT
mdefine_line|#define&t;SK_DBGMOD_RLMT&t;0x00000004L&t;/* RLMT module */
DECL|macro|SK_DBGMOD_VPD
mdefine_line|#define&t;SK_DBGMOD_VPD&t;0x00000008L&t;/* VPD module */
DECL|macro|SK_DBGMOD_I2C
mdefine_line|#define&t;SK_DBGMOD_I2C&t;0x00000010L&t;/* I2C module */
DECL|macro|SK_DBGMOD_PNMI
mdefine_line|#define&t;SK_DBGMOD_PNMI&t;0x00000020L&t;/* PNMI module */
DECL|macro|SK_DBGMOD_CSUM
mdefine_line|#define&t;SK_DBGMOD_CSUM&t;0x00000040L&t;/* CSUM module */
DECL|macro|SK_DBGMOD_ADDR
mdefine_line|#define&t;SK_DBGMOD_ADDR&t;0x00000080L&t;/* ADDR module */
DECL|macro|SK_DBGMOD_PECP
mdefine_line|#define SK_DBGMOD_PECP&t;0x00000100L&t;/* PECP module */
multiline_comment|/* Debug events */
DECL|macro|SK_DBGCAT_INIT
mdefine_line|#define&t;SK_DBGCAT_INIT&t;0x00000001L&t;/* module/driver initialization */
DECL|macro|SK_DBGCAT_CTRL
mdefine_line|#define&t;SK_DBGCAT_CTRL&t;0x00000002L&t;/* controlling: add/rmv MCA/MAC&n;&t;&t;&t;&t;&t; * and other controls (IOCTL)&n;&t;&t;&t;&t;&t; */
DECL|macro|SK_DBGCAT_ERR
mdefine_line|#define&t;SK_DBGCAT_ERR&t;0x00000004L&t;/* error handling paths */
DECL|macro|SK_DBGCAT_TX
mdefine_line|#define&t;SK_DBGCAT_TX&t;0x00000008L&t;/* transmit path */
DECL|macro|SK_DBGCAT_RX
mdefine_line|#define&t;SK_DBGCAT_RX&t;0x00000010L&t;/* receive path */
DECL|macro|SK_DBGCAT_IRQ
mdefine_line|#define&t;SK_DBGCAT_IRQ&t;0x00000020L&t;/* general IRQ handling */
DECL|macro|SK_DBGCAT_QUEUE
mdefine_line|#define&t;SK_DBGCAT_QUEUE&t;0x00000040L&t;/* any queue management */
DECL|macro|SK_DBGCAT_DUMP
mdefine_line|#define&t;SK_DBGCAT_DUMP&t;0x00000080L&t;/* large data output e.g. hex dump */
DECL|macro|SK_DBGCAT_FATAL
mdefine_line|#define&t;SK_DBGCAT_FATAL&t;0x00000100L&t;/* large data output e.g. hex dump */
macro_line|#endif&t;/* __INC_SKDEBUG_H */
eof
