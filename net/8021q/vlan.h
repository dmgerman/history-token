macro_line|#ifndef __BEN_VLAN_802_1Q_INC__
DECL|macro|__BEN_VLAN_802_1Q_INC__
mdefine_line|#define __BEN_VLAN_802_1Q_INC__
macro_line|#include &lt;linux/if_vlan.h&gt;
multiline_comment|/*  Uncomment this if you want debug traces to be shown. */
multiline_comment|/* #define VLAN_DEBUG */
DECL|macro|VLAN_ERR
mdefine_line|#define VLAN_ERR KERN_ERR
DECL|macro|VLAN_INF
mdefine_line|#define VLAN_INF KERN_ALERT
DECL|macro|VLAN_DBG
mdefine_line|#define VLAN_DBG KERN_ALERT /* change these... to debug, having a hard time&n;                             * changing the log level at run-time..for some reason.&n;                             */
multiline_comment|/*&n;&n;These I use for memory debugging.  I feared a leak at one time, but&n;I never found it..and the problem seems to have dissappeared.  Still,&n;I&squot;ll bet they might prove useful again... --Ben&n;&n;&n;#define VLAN_MEM_DBG(x, y, z) printk(VLAN_DBG __FUNCTION__ &quot;:  &quot;  x, y, z);&n;#define VLAN_FMEM_DBG(x, y) printk(VLAN_DBG __FUNCTION__  &quot;:  &quot; x, y);&n;*/
multiline_comment|/* This way they don&squot;t do anything! */
DECL|macro|VLAN_MEM_DBG
mdefine_line|#define VLAN_MEM_DBG(x, y, z) 
DECL|macro|VLAN_FMEM_DBG
mdefine_line|#define VLAN_FMEM_DBG(x, y)
r_extern
r_int
r_int
id|vlan_name_type
suffix:semicolon
multiline_comment|/* Counter for how many NON-VLAN protos we&squot;ve received on a VLAN. */
r_extern
r_int
r_int
id|vlan_bad_proto_recvd
suffix:semicolon
r_int
id|vlan_ioctl_handler
c_func
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* Add some headers for the public VLAN methods. */
r_int
id|unregister_802_1Q_vlan_device
c_func
(paren
r_const
r_char
op_star
id|vlan_IF_name
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|register_802_1Q_vlan_device
c_func
(paren
r_const
r_char
op_star
id|eth_IF_name
comma
r_int
r_int
id|VID
)paren
suffix:semicolon
macro_line|#endif /* !(__BEN_VLAN_802_1Q_INC__) */
eof
