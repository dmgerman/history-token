multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;net_user.h&quot;
DECL|struct|ethertap_data
r_struct
id|ethertap_data
(brace
DECL|member|dev_name
r_char
op_star
id|dev_name
suffix:semicolon
DECL|member|gate_addr
r_char
op_star
id|gate_addr
suffix:semicolon
DECL|member|data_fd
r_int
id|data_fd
suffix:semicolon
DECL|member|control_fd
r_int
id|control_fd
suffix:semicolon
DECL|member|dev
r_void
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|net_user_info
id|ethertap_user_info
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
