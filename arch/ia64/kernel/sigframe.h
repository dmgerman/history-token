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
DECL|member|rbs_base
r_int
r_int
id|rbs_base
suffix:semicolon
multiline_comment|/* base of new register backing store (or NULL) */
DECL|member|handler
r_void
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
eof
