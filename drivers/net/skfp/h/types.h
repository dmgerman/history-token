multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#include&t;&lt;linux/types.h&gt;
multiline_comment|/*&n;&t;----------------------&n;&t;Basic SMT system types&n;&t;----------------------&n;*/
macro_line|#ifndef _TYPES_
DECL|macro|_TYPES_
mdefine_line|#define&t;_TYPES_
DECL|macro|_packed
mdefine_line|#define _packed
macro_line|#ifndef far
DECL|macro|far
mdefine_line|#define far
macro_line|#endif
macro_line|#ifndef _far
DECL|macro|_far
mdefine_line|#define _far
macro_line|#endif
DECL|macro|inp
mdefine_line|#define inp(p)  ioread8(p)
DECL|macro|inpw
mdefine_line|#define inpw(p)&t;ioread16(p)
DECL|macro|inpd
mdefine_line|#define inpd(p) ioread32(p)
DECL|macro|outp
mdefine_line|#define outp(p,c)  iowrite8(c,p)
DECL|macro|outpw
mdefine_line|#define outpw(p,s) iowrite16(s,p)
DECL|macro|outpd
mdefine_line|#define outpd(p,l) iowrite32(l,p)
macro_line|#endif&t;/* _TYPES_ */
eof
