multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skhwt.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.5 $&n; * Date:&t;$Date: 1999/11/22 13:54:24 $&n; * Purpose:&t;Defines for the hardware timer functions&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgehwt.h,v $&n; *&t;Revision 1.5  1999/11/22 13:54:24  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.4  1998/08/19 09:50:58  gklug&n; *&t;fix: remove struct keyword from c-code (see CCC) add typedefs&n; *&t;&n; *&t;Revision 1.3  1998/08/14 07:09:29  gklug&n; *&t;fix: chg pAc -&gt; pAC&n; *&t;&n; *&t;Revision 1.2  1998/08/07 12:54:21  gklug&n; *&t;fix: first compiled version&n; *&t;&n; *&t;Revision 1.1  1998/08/07 09:32:58  gklug&n; *&t;first version&n; *&t;&n; *&t;&n; *&t;&n; *&t;&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * SKGEHWT.H&t;contains all defines and types for the timer functions&n; */
macro_line|#ifndef&t;_SKGEHWT_H_
DECL|macro|_SKGEHWT_H_
mdefine_line|#define _SKGEHWT_H_
multiline_comment|/*&n; * SK Hardware Timer&n; * - needed wherever the HWT module is used&n; * - use in Adapters context name pAC-&gt;Hwt&n; */
DECL|struct|s_Hwt
r_typedef
r_struct
id|s_Hwt
(brace
DECL|member|TStart
id|SK_U32
id|TStart
suffix:semicolon
multiline_comment|/* HWT start */
DECL|member|TStop
id|SK_U32
id|TStop
suffix:semicolon
multiline_comment|/* HWT stop */
DECL|member|TActive
r_int
id|TActive
suffix:semicolon
multiline_comment|/* HWT: flag : active/inactive */
DECL|typedef|SK_HWT
)brace
id|SK_HWT
suffix:semicolon
r_extern
r_void
id|SkHwtInit
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
)paren
suffix:semicolon
r_extern
r_void
id|SkHwtStart
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
comma
id|SK_U32
id|Time
)paren
suffix:semicolon
r_extern
r_void
id|SkHwtStop
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
)paren
suffix:semicolon
r_extern
id|SK_U32
id|SkHwtRead
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
)paren
suffix:semicolon
r_extern
r_void
id|SkHwtIsr
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
)paren
suffix:semicolon
macro_line|#endif&t;/* _SKGEHWT_H_ */
eof
