multiline_comment|/******************************************************************************&n; *&n; * Name:&t;version.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.4 $&n; * Date:&t;$Date: 2003/02/25 14:16:40 $&n; * Purpose:&t;SK specific Error log support&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2003 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&t;$Log: skversion.h,v $&n; *&t;Revision 1.4  2003/02/25 14:16:40  mlindner&n; *&t;Fix: Copyright statement&n; *&t;&n; *&t;Revision 1.3  2003/02/25 13:30:18  mlindner&n; *&t;Add: Support for various vendors&n; *&t;&n; *&t;Revision 1.1.2.1  2001/09/05 13:38:30  mlindner&n; *&t;Removed FILE description&n; *&t;&n; *&t;Revision 1.1  2001/03/06 09:25:00  mlindner&n; *&t;first version&n; *&t;&n; *&t;&n; *&n; ******************************************************************************/
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
l_string|&quot;@(#)SK-BUILD: 6.14 PL: 01&quot;
suffix:semicolon
DECL|macro|BOOT_STRING
mdefine_line|#define BOOT_STRING&t;&quot;sk98lin: Network Device Driver v6.14&bslash;n&quot; &bslash;&n;&t;&t;&t;&quot;(C)Copyright 1999-2003 Marvell(R).&quot;
DECL|macro|VER_STRING
mdefine_line|#define VER_STRING&t;&quot;6.14&quot;
eof
