multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SKAS_H
DECL|macro|__SKAS_H
mdefine_line|#define __SKAS_H
macro_line|#include &quot;sysdep/ptrace.h&quot;
r_extern
r_int
id|userspace_pid
suffix:semicolon
r_extern
r_void
id|switch_threads
c_func
(paren
r_void
op_star
id|me
comma
r_void
op_star
id|next
)paren
suffix:semicolon
r_extern
r_void
id|thread_wait
c_func
(paren
r_void
op_star
id|sw
comma
r_void
op_star
id|fb
)paren
suffix:semicolon
r_extern
r_void
id|new_thread
c_func
(paren
r_void
op_star
id|stack
comma
r_void
op_star
op_star
id|switch_buf_ptr
comma
r_void
op_star
op_star
id|fork_buf_ptr
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
)paren
)paren
suffix:semicolon
r_extern
r_int
id|start_idle_thread
c_func
(paren
r_void
op_star
id|stack
comma
r_void
op_star
id|switch_buf_ptr
comma
r_void
op_star
op_star
id|fork_buf_ptr
)paren
suffix:semicolon
r_extern
r_int
id|user_thread
c_func
(paren
r_int
r_int
id|stack
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|userspace
c_func
(paren
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|new_thread_proc
c_func
(paren
r_void
op_star
id|stack
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
id|sig
)paren
)paren
suffix:semicolon
r_extern
r_void
id|remove_sigstack
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|new_thread_handler
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_void
id|handle_syscall
c_func
(paren
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|map
c_func
(paren
r_int
id|fd
comma
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
)paren
suffix:semicolon
r_extern
r_int
id|unmap
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|protect
c_func
(paren
r_int
id|fd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
comma
r_int
id|must_succeed
)paren
suffix:semicolon
r_extern
r_void
id|user_signal
c_func
(paren
r_int
id|sig
comma
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|singlestepping_skas
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|new_mm
c_func
(paren
r_int
id|from
)paren
suffix:semicolon
r_extern
r_void
id|save_registers
c_func
(paren
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|restore_registers
c_func
(paren
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|start_userspace
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_registers
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
