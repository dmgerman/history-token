multiline_comment|/*&n; *  include/linux/eventpoll.h ( Efficent event polling implementation )&n; *  Copyright (C) 2001,...,2003&t; Davide Libenzi&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#ifndef _LINUX_EVENTPOLL_H
DECL|macro|_LINUX_EVENTPOLL_H
mdefine_line|#define _LINUX_EVENTPOLL_H
macro_line|#include &lt;linux/types.h&gt;
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
multiline_comment|/* Used to release the epoll bits inside the &quot;struct file&quot; */
r_void
id|eventpoll_release_file
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
multiline_comment|/*&n; * This is called from inside fs/file_table.c:__fput() to unlink files&n; * from the eventpoll interface. We need to have this facility to cleanup&n; * correctly files that are closed without being removed from the eventpoll&n; * interface.&n; */
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
multiline_comment|/*&n;&t; * Fast check to avoid the get/release of the semaphore. Since&n;&t; * we&squot;re doing this outside the semaphore lock, it might return&n;&t; * false negatives, but we don&squot;t care. It&squot;ll help in 99.99% of cases&n;&t; * to avoid the semaphore lock. False positives simply cannot happen&n;&t; * because the file in on the way to be removed and nobody ( but&n;&t; * eventpoll ) has still a reference to this file.&n;&t; */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|list_empty
c_func
(paren
op_amp
id|file-&gt;f_ep_links
)paren
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * The file is being closed while it is still linked to an epoll&n;&t; * descriptor. We need to handle this by correctly unlinking it&n;&t; * from its containers.&n;&t; */
id|eventpoll_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
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
