multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_TUNTAP_H
DECL|macro|__UM_TUNTAP_H
mdefine_line|#define __UM_TUNTAP_H
macro_line|#include &quot;net_user.h&quot;
DECL|struct|tuntap_data
r_struct
id|tuntap_data
(brace
DECL|member|dev_name
r_char
op_star
id|dev_name
suffix:semicolon
DECL|member|fixed_config
r_int
id|fixed_config
suffix:semicolon
DECL|member|gate_addr
r_char
op_star
id|gate_addr
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|dev
r_void
op_star
id|dev
suffix:semicolon
DECL|member|hw_addr
r_int
r_char
id|hw_addr
(braket
id|ETH_ADDR_LEN
)braket
suffix:semicolon
DECL|member|hw_setup
r_int
id|hw_setup
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|net_user_info
id|tuntap_user_info
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
