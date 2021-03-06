multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  NET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the Fibre Channel handlers.&n; *&n; * Version:&t;@(#)fcdevice.h&t;1.0.0&t;09/26/98&n; *&n; * Authors:&t;Vineet Abraham &lt;vma@iol.unh.edu&gt;&n; *&n; *&t;&t;Relocated to include/linux where it belongs by Alan Cox &n; *&t;&t;&t;&t;&t;&t;&t;&lt;gw4pts@gw4pts.ampr.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;WARNING: This move may well be temporary. This file will get merged with others RSN.&n; *&n; */
macro_line|#ifndef _LINUX_FCDEVICE_H
DECL|macro|_LINUX_FCDEVICE_H
mdefine_line|#define _LINUX_FCDEVICE_H
macro_line|#include &lt;linux/if_fc.h&gt;
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|net_device
op_star
id|alloc_fcdev
c_func
(paren
r_int
id|sizeof_priv
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _LINUX_FCDEVICE_H */
eof
