multiline_comment|/* $Id: isdn_concap.h,v 1.3.6.1 2001/09/23 22:24:31 kai Exp $&n; *&n; * Linux ISDN subsystem, protocol encapsulation&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
r_extern
r_struct
id|concap_device_ops
id|isdn_concap_reliable_dl_dops
suffix:semicolon
r_extern
r_struct
id|concap_device_ops
id|isdn_concap_demand_dial_dops
suffix:semicolon
r_struct
id|concap_proto
op_star
id|isdn_concap_new
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_X25
r_int
id|isdn_x25_setup
c_func
(paren
id|isdn_net_dev
op_star
id|p
comma
r_int
id|encap
)paren
suffix:semicolon
r_void
id|isdn_x25_cleanup
c_func
(paren
id|isdn_net_dev
op_star
id|p
)paren
suffix:semicolon
r_void
id|isdn_x25_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|isdn_x25_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|isdn_x25_bhup
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
suffix:semicolon
r_void
id|isdn_x25_hangup
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
suffix:semicolon
r_int
id|isdn_x25_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|isdn_x25_realrm
c_func
(paren
id|isdn_net_dev
op_star
id|p
)paren
suffix:semicolon
macro_line|#else
r_static
r_inline
r_void
DECL|function|isdn_x25_cleanup
id|isdn_x25_cleanup
c_func
(paren
id|isdn_net_dev
op_star
id|p
)paren
(brace
)brace
r_static
r_inline
r_int
DECL|function|isdn_x25_setup
id|isdn_x25_setup
c_func
(paren
id|isdn_net_dev
op_star
id|p
comma
r_int
id|encap
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ISDN: X25 support not configured&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|isdn_x25_open
id|isdn_x25_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|isdn_x25_close
id|isdn_x25_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|isdn_x25_dhup
id|isdn_x25_dhup
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|isdn_x25_bhup
id|isdn_x25_bhup
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|isdn_x25_hangup
id|isdn_x25_hangup
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
)brace
r_static
r_inline
r_int
DECL|function|isdn_x25_start_xmit
id|isdn_x25_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|isdn_x25_realrm
id|isdn_x25_realrm
c_func
(paren
id|isdn_net_dev
op_star
id|p
)paren
(brace
)brace
macro_line|#endif
eof
