multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __FRAME_KERN_I386_H
DECL|macro|__FRAME_KERN_I386_H
mdefine_line|#define __FRAME_KERN_I386_H
multiline_comment|/* This is called from sys_sigreturn.  It takes the sp at the point of the&n; * sigreturn system call and returns the address of the sigcontext struct&n; * on the stack.&n; */
DECL|function|sp_to_sc
r_static
r_inline
r_void
op_star
id|sp_to_sc
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|sp
suffix:semicolon
)brace
DECL|function|sp_to_rt_sc
r_static
r_inline
r_void
op_star
id|sp_to_rt_sc
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_int
r_int
id|sc
suffix:semicolon
id|sc
op_assign
id|sp
op_minus
id|signal_frame_si.common.sp_index
op_plus
id|signal_frame_si.common.len
op_minus
l_int|4
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|sc
suffix:semicolon
)brace
DECL|function|sp_to_mask
r_static
r_inline
r_void
op_star
id|sp_to_mask
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
id|sp
op_minus
id|signal_frame_sc.common.sp_index
op_plus
id|signal_frame_sc.common.len
op_minus
l_int|8
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|mask
suffix:semicolon
)brace
r_extern
r_int
id|sc_size
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|function|sp_to_rt_mask
r_static
r_inline
r_void
op_star
id|sp_to_rt_mask
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
id|sp
op_minus
id|signal_frame_si.common.sp_index
op_plus
id|signal_frame_si.common.len
op_plus
id|sc_size
c_func
(paren
op_amp
id|signal_frame_sc.arch
)paren
op_minus
l_int|4
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|mask
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
