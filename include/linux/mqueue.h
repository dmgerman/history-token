multiline_comment|/* Copyright (C) 2003 Krzysztof Benedyczak &amp; Michal Wronski&n;&n;   This program is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Lesser General Public&n;   License as published by the Free Software Foundation; either&n;   version 2.1 of the License, or (at your option) any later version.&n;&n;   It is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Lesser General Public License for more details.&n;&n;   You should have received a copy of the GNU Lesser General Public&n;   License along with this software; if not, write to the Free&n;   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA&n;   02111-1307 USA.  */
macro_line|#ifndef _LINUX_MQUEUE_H
DECL|macro|_LINUX_MQUEUE_H
mdefine_line|#define _LINUX_MQUEUE_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|MQ_PRIO_MAX
mdefine_line|#define MQ_PRIO_MAX &t;32768
DECL|struct|mq_attr
r_struct
id|mq_attr
(brace
DECL|member|mq_flags
r_int
id|mq_flags
suffix:semicolon
multiline_comment|/* message queue flags&t;&t;&t;*/
DECL|member|mq_maxmsg
r_int
id|mq_maxmsg
suffix:semicolon
multiline_comment|/* maximum number of messages&t;&t;*/
DECL|member|mq_msgsize
r_int
id|mq_msgsize
suffix:semicolon
multiline_comment|/* maximum message size&t;&t;&t;*/
DECL|member|mq_curmsgs
r_int
id|mq_curmsgs
suffix:semicolon
multiline_comment|/* number of messages currently queued&t;*/
DECL|member|__reserved
r_int
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ignored for input, zeroed for output */
)brace
suffix:semicolon
multiline_comment|/*&n; * SIGEV_THREAD implementation:&n; * SIGEV_THREAD must be implemented in user space. If SIGEV_THREAD is passed&n; * to mq_notify, then&n; * - sigev_signo must be the file descriptor of an AF_NETLINK socket. It&squot;s not&n; *   necessary that the socket is bound.&n; * - sigev_value.sival_ptr must point to a cookie that is NOTIFY_COOKIE_LEN&n; *   bytes long.&n; * If the notification is triggered, then the cookie is sent to the netlink&n; * socket. The last byte of the cookie is replaced with the NOTIFY_?? codes:&n; * NOTIFY_WOKENUP if the notification got triggered, NOTIFY_REMOVED if it was&n; * removed, either due to a close() on the message queue fd or due to a&n; * mq_notify() that removed the notification.&n; */
DECL|macro|NOTIFY_NONE
mdefine_line|#define NOTIFY_NONE&t;0
DECL|macro|NOTIFY_WOKENUP
mdefine_line|#define NOTIFY_WOKENUP&t;1
DECL|macro|NOTIFY_REMOVED
mdefine_line|#define NOTIFY_REMOVED&t;2
DECL|macro|NOTIFY_COOKIE_LEN
mdefine_line|#define NOTIFY_COOKIE_LEN&t;32
macro_line|#endif
eof
