multiline_comment|/******************************************************************************&n; *&n; * Name:&t;version.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.5 $&n; * Date:&t;$Date: 2003/10/07 08:16:51 $&n; * Purpose:&t;SK specific Error log support&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifdef&t;lint
DECL|variable|SysKonnectFileId
r_static
r_const
r_char
id|SysKonnectFileId
(braket
)braket
op_assign
l_string|&quot;@(#) (C) SysKonnect GmbH.&quot;
suffix:semicolon
DECL|variable|SysKonnectBuildNumber
r_static
r_const
r_char
id|SysKonnectBuildNumber
(braket
)braket
op_assign
l_string|&quot;@(#)SK-BUILD: 6.23 PL: 01&quot;
suffix:semicolon
macro_line|#endif&t;/* !defined(lint) */
DECL|macro|BOOT_STRING
mdefine_line|#define BOOT_STRING&t;&quot;sk98lin: Network Device Driver v6.23&bslash;n&quot; &bslash;&n;&t;&t;&t;&quot;(C)Copyright 1999-2004 Marvell(R).&quot;
DECL|macro|VER_STRING
mdefine_line|#define VER_STRING&t;&quot;6.23&quot;
DECL|macro|DRIVER_FILE_NAME
mdefine_line|#define DRIVER_FILE_NAME&t;&quot;sk98lin&quot;
DECL|macro|DRIVER_REL_DATE
mdefine_line|#define DRIVER_REL_DATE&t;&t;&quot;Feb-13-2004&quot;
eof
