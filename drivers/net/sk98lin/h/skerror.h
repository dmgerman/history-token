multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skerror.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.4 $&n; * Date:&t;$Date: 1999/11/22 13:51:59 $&n; * Purpose:&t;SK specific Error log support&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&t;$Log: skerror.h,v $&n; *&t;Revision 1.4  1999/11/22 13:51:59  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.3  1999/09/14 14:04:42  rwahl&n; *&t;Added error base SK_ERRBASE_PECP.&n; *&t;Changed error base for driver.&n; *&t;&n; *&t;Revision 1.2  1998/08/11 11:15:41  gklug&n; *&t;chg: comments&n; *&t;&n; *&t;Revision 1.1  1998/08/11 11:09:38  gklug&n; *&t;add: error bases&n; *&t;add: error Classes&n; *&t;first version&n; *&t;&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#ifndef _INC_SKERROR_H_
DECL|macro|_INC_SKERROR_H_
mdefine_line|#define _INC_SKERROR_H_
multiline_comment|/*&n; * Define the Error Classes&n; */
DECL|macro|SK_ERRCL_OTHER
mdefine_line|#define&t;SK_ERRCL_OTHER&t;&t;(0)&t;/* Other error */
DECL|macro|SK_ERRCL_CONFIG
mdefine_line|#define&t;SK_ERRCL_CONFIG&t;&t;(1L&lt;&lt;0)&t;/* Configuration error */
DECL|macro|SK_ERRCL_INIT
mdefine_line|#define&t;SK_ERRCL_INIT&t;&t;(1L&lt;&lt;1)&t;/* Initialization error */
DECL|macro|SK_ERRCL_NORES
mdefine_line|#define&t;SK_ERRCL_NORES&t;&t;(1L&lt;&lt;2)&t;/* Out of resources error */
DECL|macro|SK_ERRCL_SW
mdefine_line|#define&t;SK_ERRCL_SW&t;&t;(1L&lt;&lt;3)&t;/* internal Software error */
DECL|macro|SK_ERRCL_HW
mdefine_line|#define&t;SK_ERRCL_HW&t;&t;(1L&lt;&lt;4)&t;/* Hardware failure */
DECL|macro|SK_ERRCL_COMM
mdefine_line|#define&t;SK_ERRCL_COMM&t;&t;(1L&lt;&lt;5)&t;/* Communication error */
multiline_comment|/*&n; * Define Error code bases&n; */
DECL|macro|SK_ERRBASE_RLMT
mdefine_line|#define&t;SK_ERRBASE_RLMT&t;&t;100&t;/* Base Error number for RLMT */
DECL|macro|SK_ERRBASE_HWINIT
mdefine_line|#define&t;SK_ERRBASE_HWINIT&t;200&t;/* Base Error number for HWInit */
DECL|macro|SK_ERRBASE_VPD
mdefine_line|#define&t;SK_ERRBASE_VPD&t;&t;300&t;/* Base Error number for VPD */
DECL|macro|SK_ERRBASE_PNMI
mdefine_line|#define&t;SK_ERRBASE_PNMI&t;&t;400&t;/* Base Error number for PNMI */
DECL|macro|SK_ERRBASE_CSUM
mdefine_line|#define&t;SK_ERRBASE_CSUM&t;&t;500&t;/* Base Error number for Checksum */
DECL|macro|SK_ERRBASE_SIRQ
mdefine_line|#define&t;SK_ERRBASE_SIRQ&t;&t;600&t;/* Base Error number for Special IRQ */
DECL|macro|SK_ERRBASE_I2C
mdefine_line|#define&t;SK_ERRBASE_I2C&t;&t;700&t;/* Base Error number for i2C module */
DECL|macro|SK_ERRBASE_QUEUE
mdefine_line|#define&t;SK_ERRBASE_QUEUE&t;800&t;/* Base Error number for Scheduler */
DECL|macro|SK_ERRBASE_ADDR
mdefine_line|#define&t;SK_ERRBASE_ADDR&t;&t;900&t;/* Base Error number for Address mod. */
DECL|macro|SK_ERRBASE_PECP
mdefine_line|#define SK_ERRBASE_PECP&t;&t;1000    /* Base Error number for PECP */
DECL|macro|SK_ERRBASE_DRV
mdefine_line|#define&t;SK_ERRBASE_DRV&t;&t;1100&t;/* Base Error number for Driver */
macro_line|#endif&t;/* _INC_SKERROR_H_ */
eof
