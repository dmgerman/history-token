macro_line|#ifndef _LINUX_IP_FW_COMPAT_H
DECL|macro|_LINUX_IP_FW_COMPAT_H
mdefine_line|#define _LINUX_IP_FW_COMPAT_H
multiline_comment|/* From ip_fw_compat_redir.c */
r_extern
r_int
r_int
id|do_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|dev
comma
id|u_int16_t
id|redirpt
)paren
suffix:semicolon
r_extern
r_void
id|check_for_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|check_for_unredirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* From ip_fw_compat_masq.c */
r_extern
r_int
r_int
id|do_masquerade
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_const
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|check_for_masq_error
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
r_extern
r_int
r_int
id|check_for_demasq
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
r_extern
r_int
id|__init
id|masq_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|masq_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_IP_FW_COMPAT_H */
eof
