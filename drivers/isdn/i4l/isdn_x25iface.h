multiline_comment|/* Linux ISDN subsystem, x.25 related functions&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef _LINUX_ISDN_X25IFACE_H
DECL|macro|_LINUX_ISDN_X25IFACE_H
mdefine_line|#define _LINUX_ISDN_X25IFACE_H
DECL|macro|ISDN_X25IFACE_MAGIC
mdefine_line|#define ISDN_X25IFACE_MAGIC 0x1e75a2b9
DECL|macro|DEBUG_ISDN_X25
macro_line|#undef DEBUG_ISDN_X25
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
