multiline_comment|/*&n; *  include/linux/eventpoll.h ( Efficent event polling implementation )&n; *  Copyright (C) 2001,...,2002  Davide Libenzi&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#ifndef _LINUX_EVENTPOLL_H
DECL|macro|_LINUX_EVENTPOLL_H
mdefine_line|#define _LINUX_EVENTPOLL_H
DECL|macro|EVENTPOLL_MINOR
mdefine_line|#define EVENTPOLL_MINOR&t;124
DECL|macro|POLLFD_X_PAGE
mdefine_line|#define POLLFD_X_PAGE (PAGE_SIZE / sizeof(struct pollfd))
DECL|macro|MAX_FDS_IN_EVENTPOLL
mdefine_line|#define MAX_FDS_IN_EVENTPOLL (1024 * 128)
DECL|macro|MAX_EVENTPOLL_PAGES
mdefine_line|#define MAX_EVENTPOLL_PAGES (MAX_FDS_IN_EVENTPOLL / POLLFD_X_PAGE)
DECL|macro|EVENT_PAGE_INDEX
mdefine_line|#define EVENT_PAGE_INDEX(n) ((n) / POLLFD_X_PAGE)
DECL|macro|EVENT_PAGE_REM
mdefine_line|#define EVENT_PAGE_REM(n) ((n) % POLLFD_X_PAGE)
DECL|macro|EVENT_PAGE_OFFSET
mdefine_line|#define EVENT_PAGE_OFFSET(n) (((n) % POLLFD_X_PAGE) * sizeof(struct pollfd))
DECL|macro|EP_FDS_PAGES
mdefine_line|#define EP_FDS_PAGES(n) (((n) + POLLFD_X_PAGE - 1) / POLLFD_X_PAGE)
DECL|macro|EP_MAP_SIZE
mdefine_line|#define EP_MAP_SIZE(n) (EP_FDS_PAGES(n) * PAGE_SIZE * 2)
DECL|struct|evpoll
r_struct
id|evpoll
(brace
DECL|member|ep_timeout
r_int
id|ep_timeout
suffix:semicolon
DECL|member|ep_resoff
r_int
r_int
id|ep_resoff
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EP_ALLOC
mdefine_line|#define EP_ALLOC _IOR(&squot;P&squot;, 1, int)
DECL|macro|EP_POLL
mdefine_line|#define EP_POLL _IOWR(&squot;P&squot;, 2, struct evpoll)
DECL|macro|EP_FREE
mdefine_line|#define EP_FREE _IO(&squot;P&squot;, 3)
DECL|macro|EP_ISPOLLED
mdefine_line|#define EP_ISPOLLED _IOWR(&squot;P&squot;, 4, struct pollfd)
DECL|macro|EP_CTL_ADD
mdefine_line|#define EP_CTL_ADD 1
DECL|macro|EP_CTL_DEL
mdefine_line|#define EP_CTL_DEL 2
DECL|macro|EP_CTL_MOD
mdefine_line|#define EP_CTL_MOD 3
id|asmlinkage
r_int
id|sys_epoll_create
c_func
(paren
r_int
id|maxfds
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
r_const
op_star
op_star
id|events
comma
r_int
id|timeout
)paren
suffix:semicolon
macro_line|#endif
eof
