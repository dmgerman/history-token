multiline_comment|/*&n; *  include/linux/eventpoll.h ( Efficent event polling implementation )&n; *  Copyright (C) 2001,...,2003&t; Davide Libenzi&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#ifndef _LINUX_EVENTPOLL_H
DECL|macro|_LINUX_EVENTPOLL_H
mdefine_line|#define _LINUX_EVENTPOLL_H
multiline_comment|/* Valid opcodes to issue to sys_epoll_ctl() */
DECL|macro|EPOLL_CTL_ADD
mdefine_line|#define EPOLL_CTL_ADD 1
DECL|macro|EPOLL_CTL_DEL
mdefine_line|#define EPOLL_CTL_DEL 2
DECL|macro|EPOLL_CTL_MOD
mdefine_line|#define EPOLL_CTL_MOD 3
multiline_comment|/* Set the Edge Triggered behaviour for the target file descriptor */
DECL|macro|EPOLLET
mdefine_line|#define EPOLLET (1 &lt;&lt; 31)
multiline_comment|/* &n; * On x86-64 make the 64bit structure have the same alignment as the&n; * 32bit structure. This makes 32bit emulation easier.&n; */
macro_line|#ifdef __x86_64__
DECL|macro|EPOLL_PACKED
mdefine_line|#define EPOLL_PACKED __attribute__((packed))
macro_line|#else
DECL|macro|EPOLL_PACKED
mdefine_line|#define EPOLL_PACKED
macro_line|#endif
DECL|struct|epoll_event
r_struct
id|epoll_event
(brace
DECL|member|events
id|__u32
id|events
suffix:semicolon
DECL|member|data
id|__u64
id|data
suffix:semicolon
DECL|variable|EPOLL_PACKED
)brace
id|EPOLL_PACKED
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Forward declarations to avoid compiler errors */
r_struct
id|file
suffix:semicolon
multiline_comment|/* Kernel space functions implementing the user space &quot;epoll&quot; API */
id|asmlinkage
r_int
id|sys_epoll_create
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_epoll_ctl
c_func
(paren
r_int
id|epfd
comma
r_int
id|op
comma
r_int
id|fd
comma
r_struct
id|epoll_event
op_star
id|event
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_epoll_wait
c_func
(paren
r_int
id|epfd
comma
r_struct
id|epoll_event
op_star
id|events
comma
r_int
id|maxevents
comma
r_int
id|timeout
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_EPOLL
multiline_comment|/* Used to initialize the epoll bits inside the &quot;struct file&quot; */
r_void
id|eventpoll_init_file
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
multiline_comment|/* Used in fs/file_table.c:__fput() to unlink files from the eventpoll interface */
r_void
id|eventpoll_release
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
macro_line|#else
DECL|function|eventpoll_init_file
r_static
r_inline
r_void
id|eventpoll_init_file
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
)brace
DECL|function|eventpoll_release
r_static
r_inline
r_void
id|eventpoll_release
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif /* #ifdef __KERNEL__ */
macro_line|#endif /* #ifndef _LINUX_EVENTPOLL_H */
eof
