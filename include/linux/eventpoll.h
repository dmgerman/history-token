multiline_comment|/*&n; *  include/linux/eventpoll.h ( Efficent event polling implementation )&n; *  Copyright (C) 2001,...,2002&t; Davide Libenzi&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#ifndef _LINUX_EVENTPOLL_H
DECL|macro|_LINUX_EVENTPOLL_H
mdefine_line|#define _LINUX_EVENTPOLL_H
multiline_comment|/* Forward declarations to avoid compiler errors */
r_struct
id|file
suffix:semicolon
r_struct
id|pollfd
suffix:semicolon
multiline_comment|/* Valid opcodes to issue to sys_epoll_ctl() */
DECL|macro|EP_CTL_ADD
mdefine_line|#define EP_CTL_ADD 1
DECL|macro|EP_CTL_DEL
mdefine_line|#define EP_CTL_DEL 2
DECL|macro|EP_CTL_MOD
mdefine_line|#define EP_CTL_MOD 3
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
r_int
r_int
id|events
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
id|pollfd
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
multiline_comment|/* Used in fs/file_table.c:__fput() to unlink files from the eventpoll interface */
r_void
id|ep_notify_file_close
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
macro_line|#endif
eof
