multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __FRAME_H_
DECL|macro|__FRAME_H_
mdefine_line|#define __FRAME_H_
macro_line|#include &quot;sysdep/frame.h&quot;
DECL|struct|sc_frame
r_struct
id|sc_frame
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|sig_index
r_int
id|sig_index
suffix:semicolon
DECL|member|sc_index
r_int
id|sc_index
suffix:semicolon
DECL|member|sr_index
r_int
id|sr_index
suffix:semicolon
DECL|member|sr_relative
r_int
id|sr_relative
suffix:semicolon
DECL|member|sp_index
r_int
id|sp_index
suffix:semicolon
DECL|member|arch
r_struct
id|arch_frame_data
id|arch
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sc_frame
id|signal_frame_sc
suffix:semicolon
DECL|struct|si_frame
r_struct
id|si_frame
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|sig_index
r_int
id|sig_index
suffix:semicolon
DECL|member|sip_index
r_int
id|sip_index
suffix:semicolon
DECL|member|si_index
r_int
id|si_index
suffix:semicolon
DECL|member|sr_index
r_int
id|sr_index
suffix:semicolon
DECL|member|sr_relative
r_int
id|sr_relative
suffix:semicolon
DECL|member|sp_index
r_int
id|sp_index
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|si_frame
id|signal_frame_si
suffix:semicolon
r_extern
r_void
id|capture_signal_stack
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_sc_ip_sp
c_func
(paren
r_void
op_star
id|sc_ptr
comma
r_int
r_int
id|ip
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof