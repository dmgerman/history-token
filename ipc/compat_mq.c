multiline_comment|/*&n; *  ipc/compat_mq.c&n; *    32 bit emulation for POSIX message queue system calls&n; *&n; *    Copyright (C) 2004 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author: Arnd Bergmann &lt;arnd@arndb.de&gt;&n; */
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mqueue.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|struct|compat_mq_attr
r_struct
id|compat_mq_attr
(brace
DECL|member|mq_flags
id|compat_long_t
id|mq_flags
suffix:semicolon
multiline_comment|/* message queue flags&t;&t;     */
DECL|member|mq_maxmsg
id|compat_long_t
id|mq_maxmsg
suffix:semicolon
multiline_comment|/* maximum number of messages&t;     */
DECL|member|mq_msgsize
id|compat_long_t
id|mq_msgsize
suffix:semicolon
multiline_comment|/* maximum message size&t;&t;     */
DECL|member|mq_curmsgs
id|compat_long_t
id|mq_curmsgs
suffix:semicolon
multiline_comment|/* number of messages currently queued  */
DECL|member|__reserved
id|compat_long_t
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ignored for input, zeroed for output */
)brace
suffix:semicolon
DECL|function|get_compat_mq_attr
r_static
r_inline
r_int
id|get_compat_mq_attr
c_func
(paren
r_struct
id|mq_attr
op_star
id|attr
comma
r_const
r_struct
id|compat_mq_attr
id|__user
op_star
id|uattr
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|uattr
comma
r_sizeof
op_star
id|uattr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|__get_user
c_func
(paren
id|attr-&gt;mq_flags
comma
op_amp
id|uattr-&gt;mq_flags
)paren
op_or
id|__get_user
c_func
(paren
id|attr-&gt;mq_maxmsg
comma
op_amp
id|uattr-&gt;mq_maxmsg
)paren
op_or
id|__get_user
c_func
(paren
id|attr-&gt;mq_msgsize
comma
op_amp
id|uattr-&gt;mq_msgsize
)paren
op_or
id|__get_user
c_func
(paren
id|attr-&gt;mq_curmsgs
comma
op_amp
id|uattr-&gt;mq_curmsgs
)paren
suffix:semicolon
)brace
DECL|function|put_compat_mq_attr
r_static
r_inline
r_int
id|put_compat_mq_attr
c_func
(paren
r_const
r_struct
id|mq_attr
op_star
id|attr
comma
r_struct
id|compat_mq_attr
id|__user
op_star
id|uattr
)paren
(brace
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|uattr
comma
r_sizeof
op_star
id|uattr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|__put_user
c_func
(paren
id|attr-&gt;mq_flags
comma
op_amp
id|uattr-&gt;mq_flags
)paren
op_or
id|__put_user
c_func
(paren
id|attr-&gt;mq_maxmsg
comma
op_amp
id|uattr-&gt;mq_maxmsg
)paren
op_or
id|__put_user
c_func
(paren
id|attr-&gt;mq_msgsize
comma
op_amp
id|uattr-&gt;mq_msgsize
)paren
op_or
id|__put_user
c_func
(paren
id|attr-&gt;mq_curmsgs
comma
op_amp
id|uattr-&gt;mq_curmsgs
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_mq_open
id|asmlinkage
r_int
id|compat_sys_mq_open
c_func
(paren
r_const
r_char
id|__user
op_star
id|u_name
comma
r_int
id|oflag
comma
id|compat_mode_t
id|mode
comma
r_struct
id|compat_mq_attr
id|__user
op_star
id|u_attr
)paren
(brace
r_struct
id|mq_attr
id|attr
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|oflag
op_amp
id|O_CREAT
)paren
op_eq
l_int|0
op_logical_or
op_logical_neg
id|u_attr
)paren
r_return
id|sys_mq_open
c_func
(paren
id|u_name
comma
id|oflag
comma
id|mode
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_mq_attr
c_func
(paren
op_amp
id|attr
comma
id|u_attr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|name
op_assign
id|getname
c_func
(paren
id|u_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|name
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|name
)paren
suffix:semicolon
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_mq_open
c_func
(paren
id|name
comma
id|oflag
comma
id|mode
comma
op_amp
id|attr
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
id|putname
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|compat_prepare_timeout
r_static
r_struct
id|timespec
id|__user
op_star
id|compat_prepare_timeout
c_func
(paren
r_const
r_struct
id|compat_timespec
id|__user
op_star
id|u_abs_timeout
)paren
(brace
r_struct
id|timespec
id|ts
suffix:semicolon
r_struct
id|timespec
id|__user
op_star
id|u_ts
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|u_abs_timeout
)paren
r_return
l_int|0
suffix:semicolon
id|u_ts
op_assign
id|compat_alloc_user_space
c_func
(paren
r_sizeof
(paren
op_star
id|u_ts
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_timespec
c_func
(paren
op_amp
id|ts
comma
id|u_abs_timeout
)paren
op_logical_or
id|copy_to_user
c_func
(paren
id|u_ts
comma
op_amp
id|ts
comma
r_sizeof
(paren
op_star
id|u_ts
)paren
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
r_return
id|u_ts
suffix:semicolon
)brace
DECL|function|compat_sys_mq_timedsend
id|asmlinkage
r_int
id|compat_sys_mq_timedsend
c_func
(paren
id|mqd_t
id|mqdes
comma
r_const
r_char
id|__user
op_star
id|u_msg_ptr
comma
r_int
id|msg_len
comma
r_int
r_int
id|msg_prio
comma
r_const
r_struct
id|compat_timespec
id|__user
op_star
id|u_abs_timeout
)paren
(brace
r_struct
id|timespec
id|__user
op_star
id|u_ts
suffix:semicolon
id|u_ts
op_assign
id|compat_prepare_timeout
c_func
(paren
id|u_abs_timeout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|u_ts
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_mq_timedsend
c_func
(paren
id|mqdes
comma
id|u_msg_ptr
comma
id|msg_len
comma
id|msg_prio
comma
id|u_ts
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_mq_timedreceive
id|asmlinkage
id|ssize_t
id|compat_sys_mq_timedreceive
c_func
(paren
id|mqd_t
id|mqdes
comma
r_char
id|__user
op_star
id|u_msg_ptr
comma
r_int
id|msg_len
comma
r_int
r_int
id|__user
op_star
id|u_msg_prio
comma
r_const
r_struct
id|compat_timespec
id|__user
op_star
id|u_abs_timeout
)paren
(brace
r_struct
id|timespec
id|__user
op_star
id|u_ts
suffix:semicolon
id|u_ts
op_assign
id|compat_prepare_timeout
c_func
(paren
id|u_abs_timeout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|u_ts
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_mq_timedreceive
c_func
(paren
id|mqdes
comma
id|u_msg_ptr
comma
id|msg_len
comma
id|u_msg_prio
comma
id|u_ts
)paren
suffix:semicolon
)brace
DECL|function|get_compat_sigevent
r_static
r_int
id|get_compat_sigevent
c_func
(paren
r_struct
id|sigevent
op_star
id|event
comma
r_const
r_struct
id|compat_sigevent
id|__user
op_star
id|u_event
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|u_event
comma
r_sizeof
(paren
op_star
id|u_event
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|__get_user
c_func
(paren
id|event-&gt;sigev_value.sival_int
comma
op_amp
id|u_event-&gt;sigev_value.sival_int
)paren
op_or
id|__get_user
c_func
(paren
id|event-&gt;sigev_signo
comma
op_amp
id|u_event-&gt;sigev_signo
)paren
op_or
id|__get_user
c_func
(paren
id|event-&gt;sigev_notify
comma
op_amp
id|u_event-&gt;sigev_notify
)paren
op_or
id|__get_user
c_func
(paren
id|event-&gt;sigev_notify_thread_id
comma
op_amp
id|u_event-&gt;sigev_notify_thread_id
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_mq_notify
id|asmlinkage
r_int
id|compat_sys_mq_notify
c_func
(paren
id|mqd_t
id|mqdes
comma
r_const
r_struct
id|compat_sigevent
id|__user
op_star
id|u_notification
)paren
(brace
id|mm_segment_t
id|oldfs
suffix:semicolon
r_struct
id|sigevent
id|notification
suffix:semicolon
r_char
id|cookie
(braket
id|NOTIFY_COOKIE_LEN
)braket
suffix:semicolon
id|compat_uptr_t
id|u_cookie
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|u_notification
)paren
r_return
id|sys_mq_notify
c_func
(paren
id|mqdes
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_sigevent
c_func
(paren
op_amp
id|notification
comma
id|u_notification
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|notification.sigev_notify
op_eq
id|SIGEV_THREAD
)paren
(brace
id|u_cookie
op_assign
(paren
id|compat_uptr_t
)paren
id|notification.sigev_value.sival_int
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|cookie
comma
id|compat_ptr
c_func
(paren
id|u_cookie
)paren
comma
id|NOTIFY_COOKIE_LEN
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|notification.sigev_value.sival_ptr
op_assign
id|cookie
suffix:semicolon
)brace
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_mq_notify
c_func
(paren
id|mqdes
comma
op_amp
id|notification
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|compat_sys_mq_getsetattr
id|asmlinkage
r_int
id|compat_sys_mq_getsetattr
c_func
(paren
id|mqd_t
id|mqdes
comma
r_const
r_struct
id|compat_mq_attr
id|__user
op_star
id|u_mqstat
comma
r_struct
id|compat_mq_attr
id|__user
op_star
id|u_omqstat
)paren
(brace
r_struct
id|mq_attr
id|mqstat
comma
id|omqstat
suffix:semicolon
r_struct
id|mq_attr
op_star
id|p_mqstat
op_assign
l_int|0
comma
op_star
id|p_omqstat
op_assign
l_int|0
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|u_mqstat
)paren
(brace
id|p_mqstat
op_assign
op_amp
id|mqstat
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_mq_attr
c_func
(paren
id|p_mqstat
comma
id|u_mqstat
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|u_omqstat
)paren
id|p_omqstat
op_assign
op_amp
id|omqstat
suffix:semicolon
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_mq_getsetattr
c_func
(paren
id|mqdes
comma
id|p_mqstat
comma
id|p_omqstat
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
(paren
id|u_omqstat
)paren
ques
c_cond
id|put_compat_mq_attr
c_func
(paren
op_amp
id|omqstat
comma
id|u_omqstat
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
