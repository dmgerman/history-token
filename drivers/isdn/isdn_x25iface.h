multiline_comment|/* $Id: isdn_x25iface.h,v 1.3 2000/05/11 22:29:21 kai Exp $&n;&n; * header for Linux ISDN subsystem, x.25 related functions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef _LINUX_ISDN_X25IFACE_H
DECL|macro|_LINUX_ISDN_X25IFACE_H
mdefine_line|#define _LINUX_ISDN_X25IFACE_H
DECL|macro|ISDN_X25IFACE_MAGIC
mdefine_line|#define ISDN_X25IFACE_MAGIC 0x1e75a2b9
multiline_comment|/* #define DEBUG_ISDN_X25 if you want isdn_x25 debugging messages */
macro_line|#ifdef DEBUG_ISDN_X25
DECL|macro|IX25DEBUG
macro_line|#   define IX25DEBUG(fmt,args...) printk(KERN_DEBUG fmt , ## args)
macro_line|#else
DECL|macro|IX25DEBUG
macro_line|#   define IX25DEBUG(fmt,args...)
macro_line|#endif
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/wanrouter.h&gt;
macro_line|#include &lt;linux/isdn.h&gt;
macro_line|#include &lt;linux/concap.h&gt;
r_extern
r_struct
id|concap_proto_ops
op_star
id|isdn_x25iface_concap_proto_ops_pt
suffix:semicolon
r_extern
r_struct
id|concap_proto
op_star
id|isdn_x25iface_proto_new
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
