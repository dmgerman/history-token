multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSDEP_X86_64_SYSCALLS_H__
DECL|macro|__SYSDEP_X86_64_SYSCALLS_H__
mdefine_line|#define __SYSDEP_X86_64_SYSCALLS_H__
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
DECL|typedef|syscall_handler_t
r_typedef
r_int
id|syscall_handler_t
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|syscall_handler_t
op_star
id|ia32_sys_call_table
(braket
)braket
suffix:semicolon
DECL|macro|EXECUTE_SYSCALL
mdefine_line|#define EXECUTE_SYSCALL(syscall, regs) &bslash;&n;&t;(((long (*)(long, long, long, long, long, long)) &bslash;&n;&t;  (*sys_call_table[syscall]))(UPT_SYSCALL_ARG1(&amp;regs-&gt;regs), &bslash;&n;&t;&t; &t;&t;      UPT_SYSCALL_ARG2(&amp;regs-&gt;regs), &bslash;&n;&t;&t;&t;&t;      UPT_SYSCALL_ARG3(&amp;regs-&gt;regs), &bslash;&n;&t;&t;&t;&t;      UPT_SYSCALL_ARG4(&amp;regs-&gt;regs), &bslash;&n;&t;&t;&t;&t;      UPT_SYSCALL_ARG5(&amp;regs-&gt;regs), &bslash;&n;&t;&t;&t;&t;      UPT_SYSCALL_ARG6(&amp;regs-&gt;regs)))
r_extern
r_int
id|old_mmap
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
r_extern
id|syscall_handler_t
id|wrap_sys_shmat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_modify_ldt
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_arch_prctl
suffix:semicolon
DECL|macro|ARCH_SYSCALLS
mdefine_line|#define ARCH_SYSCALLS &bslash;&n;&t;[ __NR_mmap ] = (syscall_handler_t *) old_mmap, &bslash;&n;&t;[ __NR_select ] = (syscall_handler_t *) sys_select, &bslash;&n;&t;[ __NR_mincore ] = (syscall_handler_t *) sys_mincore, &bslash;&n;&t;[ __NR_madvise ] = (syscall_handler_t *) sys_madvise, &bslash;&n;&t;[ __NR_shmget ] = (syscall_handler_t *) sys_shmget, &bslash;&n;&t;[ __NR_shmat ] = (syscall_handler_t *) wrap_sys_shmat, &bslash;&n;&t;[ __NR_shmctl ] = (syscall_handler_t *) sys_shmctl, &bslash;&n;&t;[ __NR_semop ] = (syscall_handler_t *) sys_semop, &bslash;&n;&t;[ __NR_semget ] = (syscall_handler_t *) sys_semget, &bslash;&n;&t;[ __NR_semctl ] = (syscall_handler_t *) sys_semctl, &bslash;&n;&t;[ __NR_shmdt ] = (syscall_handler_t *) sys_shmdt, &bslash;&n;&t;[ __NR_msgget ] = (syscall_handler_t *) sys_msgget, &bslash;&n;&t;[ __NR_msgsnd ] = (syscall_handler_t *) sys_msgsnd, &bslash;&n;&t;[ __NR_msgrcv ] = (syscall_handler_t *) sys_msgrcv, &bslash;&n;&t;[ __NR_msgctl ] = (syscall_handler_t *) sys_msgctl, &bslash;&n;&t;[ __NR_pivot_root ] = (syscall_handler_t *) sys_pivot_root, &bslash;&n;&t;[ __NR_tuxcall ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_security ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_epoll_ctl_old ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_epoll_wait_old ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_modify_ldt ] = (syscall_handler_t *) sys_modify_ldt, &bslash;&n;&t;[ __NR_arch_prctl ] = (syscall_handler_t *) sys_arch_prctl, &bslash;&n;&t;[ __NR_socket ] = (syscall_handler_t *) sys_socket, &bslash;&n;&t;[ __NR_connect ] = (syscall_handler_t *) sys_connect, &bslash;&n;&t;[ __NR_accept ] = (syscall_handler_t *) sys_accept, &bslash;&n;&t;[ __NR_recvfrom ] = (syscall_handler_t *) sys_recvfrom, &bslash;&n;&t;[ __NR_recvmsg ] = (syscall_handler_t *) sys_recvmsg, &bslash;&n;&t;[ __NR_sendmsg ] = (syscall_handler_t *) sys_sendmsg, &bslash;&n;&t;[ __NR_bind ] = (syscall_handler_t *) sys_bind, &bslash;&n;&t;[ __NR_listen ] = (syscall_handler_t *) sys_listen, &bslash;&n;&t;[ __NR_getsockname ] = (syscall_handler_t *) sys_getsockname, &bslash;&n;&t;[ __NR_getpeername ] = (syscall_handler_t *) sys_getpeername, &bslash;&n;&t;[ __NR_socketpair ] = (syscall_handler_t *) sys_socketpair, &bslash;&n;&t;[ __NR_sendto ] = (syscall_handler_t *) sys_sendto, &bslash;&n;&t;[ __NR_shutdown ] = (syscall_handler_t *) sys_shutdown, &bslash;&n;&t;[ __NR_setsockopt ] = (syscall_handler_t *) sys_setsockopt, &bslash;&n;&t;[ __NR_getsockopt ] = (syscall_handler_t *) sys_getsockopt, &bslash;&n;&t;[ __NR_iopl ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_set_thread_area ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_get_thread_area ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;        [ __NR_remap_file_pages ] = (syscall_handler_t *) sys_remap_file_pages, &bslash;&n;&t;[ __NR_semtimedop ] = (syscall_handler_t *) sys_semtimedop, &bslash;&n;&t;[ __NR_fadvise64 ] = (syscall_handler_t *) sys_fadvise64, &bslash;&n;&t;[ 223 ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ __NR_utimes ] = (syscall_handler_t *) sys_utimes, &bslash;&n;&t;[ __NR_vserver ] = (syscall_handler_t *) sys_ni_syscall, &bslash;&n;&t;[ 251 ] = (syscall_handler_t *) sys_ni_syscall,
DECL|macro|LAST_ARCH_SYSCALL
mdefine_line|#define LAST_ARCH_SYSCALL 251
DECL|macro|NR_syscalls
mdefine_line|#define NR_syscalls 1024
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
