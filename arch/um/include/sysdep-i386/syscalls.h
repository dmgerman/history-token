multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
DECL|typedef|syscall_handler_t
r_typedef
r_int
id|syscall_handler_t
c_func
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
DECL|macro|EXECUTE_SYSCALL
mdefine_line|#define EXECUTE_SYSCALL(syscall, regs) &bslash;&n;&t;((long (*)(struct syscall_args)) (*sys_call_table[syscall]))(SYSCALL_ARGS(&amp;regs-&gt;regs))
r_extern
id|syscall_handler_t
id|sys_modify_ldt
suffix:semicolon
r_extern
id|syscall_handler_t
id|old_mmap_i386
suffix:semicolon
r_extern
id|syscall_handler_t
id|old_select
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
DECL|macro|ARCH_SYSCALLS
mdefine_line|#define ARCH_SYSCALLS &bslash;&n;&t;[ __NR_mmap ] = old_mmap_i386, &bslash;&n;&t;[ __NR_select ] = old_select, &bslash;&n;&t;[ __NR_vm86old ] = sys_ni_syscall, &bslash;&n;        [ __NR_modify_ldt ] = sys_modify_ldt, &bslash;&n;&t;[ __NR_lchown32 ] = sys_lchown, &bslash;&n;&t;[ __NR_getuid32 ] = sys_getuid, &bslash;&n;&t;[ __NR_getgid32 ] = sys_getgid, &bslash;&n;&t;[ __NR_geteuid32 ] = sys_geteuid, &bslash;&n;&t;[ __NR_getegid32 ] = sys_getegid, &bslash;&n;&t;[ __NR_setreuid32 ] = sys_setreuid, &bslash;&n;&t;[ __NR_setregid32 ] = sys_setregid, &bslash;&n;&t;[ __NR_getgroups32 ] = sys_getgroups, &bslash;&n;&t;[ __NR_setgroups32 ] = sys_setgroups, &bslash;&n;&t;[ __NR_fchown32 ] = sys_fchown, &bslash;&n;&t;[ __NR_setresuid32 ] = sys_setresuid, &bslash;&n;&t;[ __NR_getresuid32 ] = sys_getresuid, &bslash;&n;&t;[ __NR_setresgid32 ] = sys_setresgid, &bslash;&n;&t;[ __NR_getresgid32 ] = sys_getresgid, &bslash;&n;&t;[ __NR_chown32 ] = sys_chown, &bslash;&n;&t;[ __NR_setuid32 ] = sys_setuid, &bslash;&n;&t;[ __NR_setgid32 ] = sys_setgid, &bslash;&n;&t;[ __NR_setfsuid32 ] = sys_setfsuid, &bslash;&n;&t;[ __NR_setfsgid32 ] = sys_setfsgid, &bslash;&n;&t;[ __NR_pivot_root ] = sys_pivot_root, &bslash;&n;&t;[ __NR_mincore ] = sys_mincore, &bslash;&n;&t;[ __NR_madvise ] = sys_madvise, &bslash;&n;        [ 222 ] = sys_ni_syscall, 
multiline_comment|/* 222 doesn&squot;t yet have a name in include/asm-i386/unistd.h */
DECL|macro|LAST_ARCH_SYSCALL
mdefine_line|#define LAST_ARCH_SYSCALL 222
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
