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
multiline_comment|/* Not declared on x86, incompatible declarations on x86_64, so these have&n; * to go here rather than in sys_call_table.c&n; */
r_extern
id|syscall_handler_t
id|sys_ptrace
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigaction
suffix:semicolon
r_extern
id|syscall_handler_t
id|old_mmap_i386
suffix:semicolon
DECL|macro|EXECUTE_SYSCALL
mdefine_line|#define EXECUTE_SYSCALL(syscall, regs) &bslash;&n;&t;((long (*)(struct syscall_args)) (*sys_call_table[syscall]))(SYSCALL_ARGS(&amp;regs-&gt;regs))
r_extern
r_int
id|sys_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
suffix:semicolon
DECL|macro|ARCH_SYSCALLS
mdefine_line|#define ARCH_SYSCALLS &bslash;&n;&t;[ __NR_waitpid ] = (syscall_handler_t *) sys_waitpid, &bslash;&n;&t;[ __NR_break ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_oldstat ] = (syscall_handler_t *) sys_stat, &bslash;&n;&t;[ __NR_umount ] = (syscall_handler_t *) sys_oldumount, &bslash;&n;&t;[ __NR_stime ] = um_stime, &bslash;&n;&t;[ __NR_oldfstat ] = (syscall_handler_t *) sys_fstat, &bslash;&n;&t;[ __NR_stty ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_gtty ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_nice ] = (syscall_handler_t *) sys_nice, &bslash;&n;&t;[ __NR_ftime ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_prof ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_signal ] = (syscall_handler_t *) sys_signal, &bslash;&n;&t;[ __NR_lock ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_mpx ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_ulimit ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_oldolduname ] = (syscall_handler_t *) sys_olduname, &bslash;&n;&t;[ __NR_sigaction ] = (syscall_handler_t *) sys_sigaction, &bslash;&n;&t;[ __NR_sgetmask ] = (syscall_handler_t *) sys_sgetmask, &bslash;&n;&t;[ __NR_ssetmask ] = (syscall_handler_t *) sys_ssetmask, &bslash;&n;&t;[ __NR_sigsuspend ] = (syscall_handler_t *) sys_sigsuspend, &bslash;&n;&t;[ __NR_sigpending ] = (syscall_handler_t *) sys_sigpending, &bslash;&n;&t;[ __NR_oldlstat ] = (syscall_handler_t *) sys_lstat, &bslash;&n;&t;[ __NR_readdir ] = old_readdir, &bslash;&n;&t;[ __NR_profil ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_socketcall ] = (syscall_handler_t *) sys_socketcall, &bslash;&n;&t;[ __NR_olduname ] = (syscall_handler_t *) sys_uname, &bslash;&n;&t;[ __NR_iopl ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_idle ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_ipc ] = (syscall_handler_t *) sys_ipc, &bslash;&n;&t;[ __NR_sigreturn ] = (syscall_handler_t *) sys_sigreturn, &bslash;&n;&t;[ __NR_sigprocmask ] = (syscall_handler_t *) sys_sigprocmask, &bslash;&n;&t;[ __NR_bdflush ] = (syscall_handler_t *) sys_bdflush, &bslash;&n;&t;[ __NR__llseek ] = (syscall_handler_t *) sys_llseek, &bslash;&n;&t;[ __NR__newselect ] = (syscall_handler_t *) sys_select, &bslash;&n;&t;[ __NR_vm86 ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_mmap ] = (syscall_handler_t *) old_mmap_i386, &bslash;&n;&t;[ __NR_ugetrlimit ] = (syscall_handler_t *) sys_getrlimit, &bslash;&n;&t;[ __NR_mmap2 ] = (syscall_handler_t *) sys_mmap2, &bslash;&n;&t;[ __NR_truncate64 ] = (syscall_handler_t *) sys_truncate64, &bslash;&n;&t;[ __NR_ftruncate64 ] = (syscall_handler_t *) sys_ftruncate64, &bslash;&n;&t;[ __NR_stat64 ] = (syscall_handler_t *) sys_stat64, &bslash;&n;&t;[ __NR_lstat64 ] = (syscall_handler_t *) sys_lstat64, &bslash;&n;&t;[ __NR_fstat64 ] = (syscall_handler_t *) sys_fstat64, &bslash;&n;&t;[ __NR_fcntl64 ] = (syscall_handler_t *) sys_fcntl64, &bslash;&n;&t;[ __NR_sendfile64 ] = (syscall_handler_t *) sys_sendfile64, &bslash;&n;&t;[ __NR_statfs64 ] = (syscall_handler_t *) sys_statfs64, &bslash;&n;&t;[ __NR_fstatfs64 ] = (syscall_handler_t *) sys_fstatfs64, &bslash;&n;&t;[ __NR_fadvise64_64 ] = (syscall_handler_t *) sys_fadvise64_64, &bslash;&n;&t;[ __NR_select ] = (syscall_handler_t *) old_select, &bslash;&n;&t;[ __NR_vm86old ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;        [ __NR_modify_ldt ] = (syscall_handler_t *) sys_modify_ldt, &bslash;&n;&t;[ __NR_lchown32 ] = (syscall_handler_t *) sys_lchown, &bslash;&n;&t;[ __NR_getuid32 ] = (syscall_handler_t *) sys_getuid, &bslash;&n;&t;[ __NR_getgid32 ] = (syscall_handler_t *) sys_getgid, &bslash;&n;&t;[ __NR_geteuid32 ] = (syscall_handler_t *) sys_geteuid, &bslash;&n;&t;[ __NR_getegid32 ] = (syscall_handler_t *) sys_getegid, &bslash;&n;&t;[ __NR_setreuid32 ] = (syscall_handler_t *) sys_setreuid, &bslash;&n;&t;[ __NR_setregid32 ] = (syscall_handler_t *) sys_setregid, &bslash;&n;&t;[ __NR_getgroups32 ] = (syscall_handler_t *) sys_getgroups, &bslash;&n;&t;[ __NR_setgroups32 ] = (syscall_handler_t *) sys_setgroups, &bslash;&n;&t;[ __NR_fchown32 ] = (syscall_handler_t *) sys_fchown, &bslash;&n;&t;[ __NR_setresuid32 ] = (syscall_handler_t *) sys_setresuid, &bslash;&n;&t;[ __NR_getresuid32 ] = (syscall_handler_t *) sys_getresuid, &bslash;&n;&t;[ __NR_setresgid32 ] = (syscall_handler_t *) sys_setresgid, &bslash;&n;&t;[ __NR_getresgid32 ] = (syscall_handler_t *) sys_getresgid, &bslash;&n;&t;[ __NR_chown32 ] = (syscall_handler_t *) sys_chown, &bslash;&n;&t;[ __NR_setuid32 ] = (syscall_handler_t *) sys_setuid, &bslash;&n;&t;[ __NR_setgid32 ] = (syscall_handler_t *) sys_setgid, &bslash;&n;&t;[ __NR_setfsuid32 ] = (syscall_handler_t *) sys_setfsuid, &bslash;&n;&t;[ __NR_setfsgid32 ] = (syscall_handler_t *) sys_setfsgid, &bslash;&n;&t;[ __NR_pivot_root ] = (syscall_handler_t *) sys_pivot_root, &bslash;&n;&t;[ __NR_mincore ] = (syscall_handler_t *) sys_mincore, &bslash;&n;&t;[ __NR_madvise ] = (syscall_handler_t *) sys_madvise, &bslash;&n;        [ 222 ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ 223 ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_set_thread_area ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_get_thread_area ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_fadvise64 ] = (syscall_handler_t *) sys_fadvise64, &bslash;&n;&t;[ 251 ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;        [ __NR_remap_file_pages ] = (syscall_handler_t *) sys_remap_file_pages, &bslash;&n;&t;[ __NR_utimes ] = (syscall_handler_t *) sys_utimes, &bslash;&n;&t;[ __NR_vserver ] = (syscall_handler_t *) sys_ni_syscall,
multiline_comment|/* 222 doesn&squot;t yet have a name in include/asm-i386/unistd.h */
DECL|macro|LAST_ARCH_SYSCALL
mdefine_line|#define LAST_ARCH_SYSCALL __NR_vserver
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
