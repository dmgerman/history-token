multiline_comment|/******************************************************************************&n; *&n; * Name:&t;sktypes.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.2 $&n; * Date:&t;$Date: 1999/11/22 14:01:58 $&n; * Purpose:&t;Define data types for Linux&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*****************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: sktypes.h,v $&n; *&t;Revision 1.2  1999/11/22 14:01:58  cgoos&n; *&t;Changed license header to GPL.&n; *&t;Now using Linux&squot; fixed size types instead of standard types.&n; *&t;&n; *&t;Revision 1.1  1999/02/16 07:41:40  cgoos&n; *&t;First version.&n; *&t;&n; *&t;&n; *&n; *****************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * In this file, all data types that are needed by the common modules&n; * are mapped to Linux data types.&n; * &n; *&n; * Include File Hierarchy:&n; *&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKTYPES_H
DECL|macro|__INC_SKTYPES_H
mdefine_line|#define __INC_SKTYPES_H
multiline_comment|/* defines *******************************************************************/
multiline_comment|/*&n; * Data types with a specific size. &squot;I&squot; = signed, &squot;U&squot; = unsigned.&n; */
DECL|macro|SK_I8
mdefine_line|#define SK_I8&t;s8
DECL|macro|SK_U8
mdefine_line|#define SK_U8&t;u8
DECL|macro|SK_I16
mdefine_line|#define SK_I16&t;s16
DECL|macro|SK_U16
mdefine_line|#define SK_U16&t;u16
DECL|macro|SK_I32
mdefine_line|#define SK_I32&t;s32
DECL|macro|SK_U32
mdefine_line|#define SK_U32&t;u32
DECL|macro|SK_I64
mdefine_line|#define SK_I64&t;s64
DECL|macro|SK_U64
mdefine_line|#define SK_U64&t;u64
DECL|macro|SK_UPTR
mdefine_line|#define SK_UPTR&t;ulong&t;&t;/* casting pointer &lt;-&gt; integral */
multiline_comment|/*&n;* Boolean type.&n;*/
DECL|macro|SK_BOOL
mdefine_line|#define SK_BOOL&t;&t;SK_U8
DECL|macro|SK_FALSE
mdefine_line|#define SK_FALSE&t;0
DECL|macro|SK_TRUE
mdefine_line|#define SK_TRUE&t;&t;(!SK_FALSE)
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/* function prototypes ********************************************************/
macro_line|#endif&t;/* __INC_SKTYPES_H */
eof
