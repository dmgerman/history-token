macro_line|#ifndef _LINUX_BINFMTS_H
DECL|macro|_LINUX_BINFMTS_H
mdefine_line|#define _LINUX_BINFMTS_H
macro_line|#include &lt;linux/capability.h&gt;
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/*&n; * MAX_ARG_PAGES defines the number of pages allocated for arguments&n; * and envelope for the new program. 32 should suffice, this gives&n; * a maximum env+arg of 128kB w/4KB pages!&n; */
DECL|macro|MAX_ARG_PAGES
mdefine_line|#define MAX_ARG_PAGES 32
multiline_comment|/* sizeof(linux_binprm-&gt;buf) */
DECL|macro|BINPRM_BUF_SIZE
mdefine_line|#define BINPRM_BUF_SIZE 128
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This structure is used to hold the arguments that are used when loading binaries.&n; */
DECL|struct|linux_binprm
r_struct
id|linux_binprm
(brace
DECL|member|buf
r_char
id|buf
(braket
id|BINPRM_BUF_SIZE
)braket
suffix:semicolon
DECL|member|page
r_struct
id|page
op_star
id|page
(braket
id|MAX_ARG_PAGES
)braket
suffix:semicolon
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
DECL|member|p
r_int
r_int
id|p
suffix:semicolon
multiline_comment|/* current top of mem */
DECL|member|sh_bang
r_int
id|sh_bang
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|e_uid
DECL|member|e_gid
r_int
id|e_uid
comma
id|e_gid
suffix:semicolon
DECL|member|cap_inheritable
DECL|member|cap_permitted
DECL|member|cap_effective
id|kernel_cap_t
id|cap_inheritable
comma
id|cap_permitted
comma
id|cap_effective
suffix:semicolon
DECL|member|security
r_void
op_star
id|security
suffix:semicolon
DECL|member|argc
DECL|member|envc
r_int
id|argc
comma
id|envc
suffix:semicolon
DECL|member|filename
r_char
op_star
id|filename
suffix:semicolon
multiline_comment|/* Name of binary as seen by procps */
DECL|member|interp
r_char
op_star
id|interp
suffix:semicolon
multiline_comment|/* Name of the binary really executed. Most&n;&t;&t;&t;&t;   of the time same as filename, but could be&n;&t;&t;&t;&t;   different for binfmt_{misc,script} */
DECL|member|interp_flags
r_int
id|interp_flags
suffix:semicolon
DECL|member|interp_data
r_int
id|interp_data
suffix:semicolon
DECL|member|loader
DECL|member|exec
r_int
r_int
id|loader
comma
id|exec
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BINPRM_FLAGS_ENFORCE_NONDUMP_BIT
mdefine_line|#define BINPRM_FLAGS_ENFORCE_NONDUMP_BIT 0
DECL|macro|BINPRM_FLAGS_ENFORCE_NONDUMP
mdefine_line|#define BINPRM_FLAGS_ENFORCE_NONDUMP (1 &lt;&lt; BINPRM_FLAGS_ENFORCE_NONDUMP_BIT)
multiline_comment|/* fd of the binary should be passed to the interpreter */
DECL|macro|BINPRM_FLAGS_EXECFD_BIT
mdefine_line|#define BINPRM_FLAGS_EXECFD_BIT 1
DECL|macro|BINPRM_FLAGS_EXECFD
mdefine_line|#define BINPRM_FLAGS_EXECFD (1 &lt;&lt; BINPRM_FLAGS_EXECFD_BIT)
multiline_comment|/*&n; * This structure defines the functions that are used to load the binary formats that&n; * linux accepts.&n; */
DECL|struct|linux_binfmt
r_struct
id|linux_binfmt
(brace
DECL|member|next
r_struct
id|linux_binfmt
op_star
id|next
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|load_binary
r_int
(paren
op_star
id|load_binary
)paren
(paren
r_struct
id|linux_binprm
op_star
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|load_shlib
r_int
(paren
op_star
id|load_shlib
)paren
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|member|core_dump
r_int
(paren
op_star
id|core_dump
)paren
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|member|min_coredump
r_int
r_int
id|min_coredump
suffix:semicolon
multiline_comment|/* minimal dump size */
)brace
suffix:semicolon
r_extern
r_int
id|register_binfmt
c_func
(paren
r_struct
id|linux_binfmt
op_star
)paren
suffix:semicolon
r_extern
r_int
id|unregister_binfmt
c_func
(paren
r_struct
id|linux_binfmt
op_star
)paren
suffix:semicolon
r_extern
r_int
id|prepare_binprm
c_func
(paren
r_struct
id|linux_binprm
op_star
)paren
suffix:semicolon
r_extern
r_void
id|remove_arg_zero
c_func
(paren
r_struct
id|linux_binprm
op_star
)paren
suffix:semicolon
r_extern
r_int
id|search_binary_handler
c_func
(paren
r_struct
id|linux_binprm
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|flush_old_exec
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
suffix:semicolon
multiline_comment|/* Stack area protections */
DECL|macro|EXSTACK_DEFAULT
mdefine_line|#define EXSTACK_DEFAULT   0&t;/* Whatever the arch defaults to */
DECL|macro|EXSTACK_DISABLE_X
mdefine_line|#define EXSTACK_DISABLE_X 1&t;/* Disable executable stacks */
DECL|macro|EXSTACK_ENABLE_X
mdefine_line|#define EXSTACK_ENABLE_X  2&t;/* Enable executable stacks */
r_extern
r_int
id|setup_arg_pages
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_int
r_int
id|stack_top
comma
r_int
id|executable_stack
)paren
suffix:semicolon
r_extern
r_int
id|copy_strings
c_func
(paren
r_int
id|argc
comma
r_char
id|__user
op_star
id|__user
op_star
id|argv
comma
r_struct
id|linux_binprm
op_star
id|bprm
)paren
suffix:semicolon
r_extern
r_int
id|copy_strings_kernel
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_struct
id|linux_binprm
op_star
id|bprm
)paren
suffix:semicolon
r_extern
r_void
id|compute_creds
c_func
(paren
r_struct
id|linux_binprm
op_star
id|binprm
)paren
suffix:semicolon
r_extern
r_int
id|do_coredump
c_func
(paren
r_int
id|signr
comma
r_int
id|exit_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|set_binfmt
c_func
(paren
r_struct
id|linux_binfmt
op_star
r_new
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_BINFMTS_H */
eof
