multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_NET_KERN_H
DECL|macro|__UM_NET_KERN_H
mdefine_line|#define __UM_NET_KERN_H
macro_line|#include &quot;linux/netdevice.h&quot;
macro_line|#include &quot;linux/skbuff.h&quot;
macro_line|#include &quot;linux/socket.h&quot;
macro_line|#include &quot;linux/list.h&quot;
DECL|struct|uml_net
r_struct
id|uml_net
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|pdev
r_struct
id|platform_device
id|pdev
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|mac
r_int
r_char
id|mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|have_mac
r_int
id|have_mac
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|uml_net_private
r_struct
id|uml_net_private
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|tl
r_struct
id|timer_list
id|tl
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|mac
r_int
r_char
id|mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|have_mac
r_int
id|have_mac
suffix:semicolon
DECL|member|protocol
r_int
r_int
(paren
op_star
id|protocol
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_int
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_int
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
)paren
suffix:semicolon
DECL|member|add_address
r_void
(paren
op_star
id|add_address
)paren
(paren
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|delete_address
r_void
(paren
op_star
id|delete_address
)paren
(paren
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|set_mtu
r_int
(paren
op_star
id|set_mtu
)paren
(paren
r_int
id|mtu
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|user
r_int
id|user
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|net_kern_info
r_struct
id|net_kern_info
(brace
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_struct
id|net_device
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|protocol
r_int
r_int
(paren
op_star
id|protocol
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_int
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_int
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|transport
r_struct
id|transport
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|user
r_struct
id|net_user_info
op_star
id|user
suffix:semicolon
DECL|member|kern
r_struct
id|net_kern_info
op_star
id|kern
suffix:semicolon
DECL|member|private_size
r_int
id|private_size
suffix:semicolon
DECL|member|setup_size
r_int
id|setup_size
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|ether_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ether_protocol
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|setup_etheraddr
c_func
(paren
r_char
op_star
id|str
comma
r_int
r_char
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|ether_adjust_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|extra
)paren
suffix:semicolon
r_extern
r_int
id|tap_setup_common
c_func
(paren
r_char
op_star
id|str
comma
r_char
op_star
id|type
comma
r_char
op_star
op_star
id|dev_name
comma
r_char
op_star
op_star
id|mac_out
comma
r_char
op_star
op_star
id|gate_addr
)paren
suffix:semicolon
r_extern
r_void
id|register_transport
c_func
(paren
r_struct
id|transport
op_star
r_new
)paren
suffix:semicolon
r_extern
r_int
r_int
id|eth_protocol
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
