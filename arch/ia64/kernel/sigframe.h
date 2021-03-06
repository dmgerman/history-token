DECL|struct|sigscratch
r_struct
id|sigscratch
(brace
DECL|member|scratch_unat
r_int
r_int
id|scratch_unat
suffix:semicolon
multiline_comment|/* ar.unat for the general registers saved in pt */
DECL|member|ar_pfs
r_int
r_int
id|ar_pfs
suffix:semicolon
multiline_comment|/* for syscalls, the user-level function-state  */
DECL|member|pt
r_struct
id|pt_regs
id|pt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sigframe
r_struct
id|sigframe
(brace
multiline_comment|/*&n;&t; * Place signal handler args where user-level unwinder can find them easily.&n;&t; * DO NOT MOVE THESE.  They are part of the IA-64 Linux ABI and there is&n;&t; * user-level code that depends on their presence!&n;&t; */
DECL|member|arg0
r_int
r_int
id|arg0
suffix:semicolon
multiline_comment|/* signum */
DECL|member|arg1
r_int
r_int
id|arg1
suffix:semicolon
multiline_comment|/* siginfo pointer */
DECL|member|arg2
r_int
r_int
id|arg2
suffix:semicolon
multiline_comment|/* sigcontext pointer */
multiline_comment|/*&n;&t; * End of architected state.&n;&t; */
DECL|member|handler
r_void
id|__user
op_star
id|handler
suffix:semicolon
multiline_comment|/* pointer to the plabel of the signal handler */
DECL|member|info
r_struct
id|siginfo
id|info
suffix:semicolon
DECL|member|sc
r_struct
id|sigcontext
id|sc
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ia64_do_signal
(paren
id|sigset_t
op_star
comma
r_struct
id|sigscratch
op_star
comma
r_int
)paren
suffix:semicolon
eof
