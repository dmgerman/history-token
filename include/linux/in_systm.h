multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Miscellaneous internetwork definitions for kernel.&n; *&n; * Version:&t;@(#)in_systm.h  1.0.0   12/17/93&n; *&n; * Authors:&t;Original taken from Berkeley BSD UNIX 4.3-RENO.&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IN_SYSTM_H
DECL|macro|_LINUX_IN_SYSTM_H
mdefine_line|#define _LINUX_IN_SYSTM_H
multiline_comment|/*&n; * Network types.&n; * The n_ types are network-order variants of their natural&n; * equivalents.  The Linux kernel NET-2 code does not use&n; * them (yet), but it might in the future.  This is mostly&n; * there for compatibility with BSD user-level programs.&n; */
DECL|typedef|n_short
r_typedef
id|u_short
id|n_short
suffix:semicolon
multiline_comment|/* short as received from the net&t;*/
DECL|typedef|n_long
r_typedef
id|u_long
id|n_long
suffix:semicolon
multiline_comment|/* long as received from the net&t;*/
DECL|typedef|n_time
r_typedef
id|u_long
id|n_time
suffix:semicolon
multiline_comment|/* ms since 00:00 GMT, byte rev&t;&t;*/
macro_line|#endif /* _LINUX_IN_SYSTM_H */
eof
