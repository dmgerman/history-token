multiline_comment|/* &n; * 32bit Socket syscall emulation. Based on arch/sparc64/kernel/sys_sparc32.c.&n; *&n; * Copyright (C) 2000&t;&t;VA Linux Co&n; * Copyright (C) 2000&t;&t;Don Dugger &lt;n0ano@valinux.com&gt;&n; * Copyright (C) 1999 &t;&t;Arun Sharma &lt;arun.sharma@intel.com&gt;&n; * Copyright (C) 1997,1998 &t;Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; * Copyright (C) 1997 &t;&t;David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 2000&t;&t;Hewlett-Packard Co.&n; * Copyright (C) 2000&t;&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 2000,2001&t;Andi Kleen, SuSE Labs &n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/filter.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;net/scm.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;net/compat.h&gt;
DECL|function|iov_from_user_compat_to_kern
r_static
r_inline
r_int
id|iov_from_user_compat_to_kern
c_func
(paren
r_struct
id|iovec
op_star
id|kiov
comma
r_struct
id|compat_iovec
op_star
id|uiov32
comma
r_int
id|niov
)paren
(brace
r_int
id|tot_len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|niov
OG
l_int|0
)paren
(brace
id|compat_uptr_t
id|buf
suffix:semicolon
id|compat_size_t
id|len
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
op_amp
id|uiov32-&gt;iov_len
)paren
op_logical_or
id|get_user
c_func
(paren
id|buf
comma
op_amp
id|uiov32-&gt;iov_base
)paren
)paren
(brace
id|tot_len
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tot_len
op_add_assign
id|len
suffix:semicolon
id|kiov-&gt;iov_base
op_assign
id|compat_ptr
c_func
(paren
id|buf
)paren
suffix:semicolon
id|kiov-&gt;iov_len
op_assign
(paren
id|__kernel_size_t
)paren
id|len
suffix:semicolon
id|uiov32
op_increment
suffix:semicolon
id|kiov
op_increment
suffix:semicolon
id|niov
op_decrement
suffix:semicolon
)brace
r_return
id|tot_len
suffix:semicolon
)brace
DECL|function|get_compat_msghdr
r_int
id|get_compat_msghdr
c_func
(paren
r_struct
id|msghdr
op_star
id|kmsg
comma
r_struct
id|compat_msghdr
op_star
id|umsg
)paren
(brace
id|compat_uptr_t
id|tmp1
comma
id|tmp2
comma
id|tmp3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|umsg
comma
r_sizeof
(paren
op_star
id|umsg
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tmp1
comma
op_amp
id|umsg-&gt;msg_name
)paren
op_logical_or
id|__get_user
c_func
(paren
id|kmsg-&gt;msg_namelen
comma
op_amp
id|umsg-&gt;msg_namelen
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tmp2
comma
op_amp
id|umsg-&gt;msg_iov
)paren
op_logical_or
id|__get_user
c_func
(paren
id|kmsg-&gt;msg_iovlen
comma
op_amp
id|umsg-&gt;msg_iovlen
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tmp3
comma
op_amp
id|umsg-&gt;msg_control
)paren
op_logical_or
id|__get_user
c_func
(paren
id|kmsg-&gt;msg_controllen
comma
op_amp
id|umsg-&gt;msg_controllen
)paren
op_logical_or
id|__get_user
c_func
(paren
id|kmsg-&gt;msg_flags
comma
op_amp
id|umsg-&gt;msg_flags
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|kmsg-&gt;msg_name
op_assign
id|compat_ptr
c_func
(paren
id|tmp1
)paren
suffix:semicolon
id|kmsg-&gt;msg_iov
op_assign
id|compat_ptr
c_func
(paren
id|tmp2
)paren
suffix:semicolon
id|kmsg-&gt;msg_control
op_assign
id|compat_ptr
c_func
(paren
id|tmp3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* I&squot;ve named the args so it is easy to tell whose space the pointers are in. */
DECL|function|verify_compat_iovec
r_int
id|verify_compat_iovec
c_func
(paren
r_struct
id|msghdr
op_star
id|kern_msg
comma
r_struct
id|iovec
op_star
id|kern_iov
comma
r_char
op_star
id|kern_address
comma
r_int
id|mode
)paren
(brace
r_int
id|tot_len
suffix:semicolon
r_if
c_cond
(paren
id|kern_msg-&gt;msg_namelen
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|VERIFY_READ
)paren
(brace
r_int
id|err
op_assign
id|move_addr_to_kernel
c_func
(paren
id|kern_msg-&gt;msg_name
comma
id|kern_msg-&gt;msg_namelen
comma
id|kern_address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
)brace
id|kern_msg-&gt;msg_name
op_assign
id|kern_address
suffix:semicolon
)brace
r_else
id|kern_msg-&gt;msg_name
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|kern_msg-&gt;msg_iovlen
OG
id|UIO_FASTIOV
)paren
(brace
id|kern_iov
op_assign
id|kmalloc
c_func
(paren
id|kern_msg-&gt;msg_iovlen
op_star
r_sizeof
(paren
r_struct
id|iovec
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kern_iov
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
id|tot_len
op_assign
id|iov_from_user_compat_to_kern
c_func
(paren
id|kern_iov
comma
(paren
r_struct
id|compat_iovec
op_star
)paren
id|kern_msg-&gt;msg_iov
comma
id|kern_msg-&gt;msg_iovlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tot_len
op_ge
l_int|0
)paren
(brace
id|kern_msg-&gt;msg_iov
op_assign
id|kern_iov
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kern_msg-&gt;msg_iovlen
OG
id|UIO_FASTIOV
)paren
(brace
id|kfree
c_func
(paren
id|kern_iov
)paren
suffix:semicolon
)brace
r_return
id|tot_len
suffix:semicolon
)brace
multiline_comment|/* Bleech... */
DECL|macro|CMSG_COMPAT_ALIGN
mdefine_line|#define CMSG_COMPAT_ALIGN(len)&t;ALIGN((len), sizeof(s32))
DECL|macro|CMSG_COMPAT_DATA
mdefine_line|#define CMSG_COMPAT_DATA(cmsg)&t;&t;&t;&t;&bslash;&n;&t;((void *)((char *)(cmsg) + CMSG_COMPAT_ALIGN(sizeof(struct compat_cmsghdr))))
DECL|macro|CMSG_COMPAT_SPACE
mdefine_line|#define CMSG_COMPAT_SPACE(len)&t;&t;&t;&t;&bslash;&n;&t;(CMSG_COMPAT_ALIGN(sizeof(struct compat_cmsghdr)) + CMSG_COMPAT_ALIGN(len))
DECL|macro|CMSG_COMPAT_LEN
mdefine_line|#define CMSG_COMPAT_LEN(len)&t;&t;&t;&t;&bslash;&n;&t;(CMSG_COMPAT_ALIGN(sizeof(struct compat_cmsghdr)) + (len))
DECL|macro|CMSG_COMPAT_FIRSTHDR
mdefine_line|#define CMSG_COMPAT_FIRSTHDR(msg)&t;&t;&t;&bslash;&n;&t;(((msg)-&gt;msg_controllen) &gt;= sizeof(struct compat_cmsghdr) ?&t;&bslash;&n;&t; (struct compat_cmsghdr *)((msg)-&gt;msg_control) :&t;&t;&bslash;&n;&t; (struct compat_cmsghdr *)NULL)
DECL|function|cmsg_compat_nxthdr
r_static
r_inline
r_struct
id|compat_cmsghdr
op_star
id|cmsg_compat_nxthdr
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|compat_cmsghdr
op_star
id|cmsg
comma
r_int
id|cmsg_len
)paren
(brace
r_struct
id|compat_cmsghdr
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
(paren
r_struct
id|compat_cmsghdr
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|cmsg
)paren
op_plus
id|CMSG_COMPAT_ALIGN
c_func
(paren
id|cmsg_len
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_char
op_star
)paren
(paren
id|ptr
op_plus
l_int|1
)paren
op_minus
(paren
r_char
op_star
)paren
id|msg-&gt;msg_control
)paren
OG
id|msg-&gt;msg_controllen
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
multiline_comment|/* There is a lot of hair here because the alignment rules (and&n; * thus placement) of cmsg headers and length are different for&n; * 32-bit apps.  -DaveM&n; */
DECL|function|cmsghdr_from_user_compat_to_kern
r_int
id|cmsghdr_from_user_compat_to_kern
c_func
(paren
r_struct
id|msghdr
op_star
id|kmsg
comma
r_int
r_char
op_star
id|stackbuf
comma
r_int
id|stackbuf_size
)paren
(brace
r_struct
id|compat_cmsghdr
op_star
id|ucmsg
suffix:semicolon
r_struct
id|cmsghdr
op_star
id|kcmsg
comma
op_star
id|kcmsg_base
suffix:semicolon
id|compat_size_t
id|ucmlen
suffix:semicolon
id|__kernel_size_t
id|kcmlen
comma
id|tmp
suffix:semicolon
id|kcmlen
op_assign
l_int|0
suffix:semicolon
id|kcmsg_base
op_assign
id|kcmsg
op_assign
(paren
r_struct
id|cmsghdr
op_star
)paren
id|stackbuf
suffix:semicolon
id|ucmsg
op_assign
id|CMSG_COMPAT_FIRSTHDR
c_func
(paren
id|kmsg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ucmsg
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ucmlen
comma
op_amp
id|ucmsg-&gt;cmsg_len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* Catch bogons. */
r_if
c_cond
(paren
id|CMSG_COMPAT_ALIGN
c_func
(paren
id|ucmlen
)paren
OL
id|CMSG_COMPAT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|compat_cmsghdr
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
(paren
(paren
(paren
r_char
op_star
)paren
id|ucmsg
op_minus
(paren
r_char
op_star
)paren
id|kmsg-&gt;msg_control
)paren
op_plus
id|ucmlen
)paren
OG
id|kmsg-&gt;msg_controllen
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|tmp
op_assign
(paren
(paren
id|ucmlen
op_minus
id|CMSG_COMPAT_ALIGN
c_func
(paren
r_sizeof
(paren
op_star
id|ucmsg
)paren
)paren
)paren
op_plus
id|CMSG_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
)paren
)paren
suffix:semicolon
id|kcmlen
op_add_assign
id|tmp
suffix:semicolon
id|ucmsg
op_assign
id|cmsg_compat_nxthdr
c_func
(paren
id|kmsg
comma
id|ucmsg
comma
id|ucmlen
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kcmlen
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* The kcmlen holds the 64-bit version of the control length.&n;&t; * It may not be modified as we do not stick it into the kmsg&n;&t; * until we have successfully copied over all of the data&n;&t; * from the user.&n;&t; */
r_if
c_cond
(paren
id|kcmlen
OG
id|stackbuf_size
)paren
(brace
id|kcmsg_base
op_assign
id|kcmsg
op_assign
id|kmalloc
c_func
(paren
id|kcmlen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kcmsg
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
multiline_comment|/* Now copy them over neatly. */
id|memset
c_func
(paren
id|kcmsg
comma
l_int|0
comma
id|kcmlen
)paren
suffix:semicolon
id|ucmsg
op_assign
id|CMSG_COMPAT_FIRSTHDR
c_func
(paren
id|kmsg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ucmsg
op_ne
l_int|NULL
)paren
(brace
id|__get_user
c_func
(paren
id|ucmlen
comma
op_amp
id|ucmsg-&gt;cmsg_len
)paren
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|ucmlen
op_minus
id|CMSG_COMPAT_ALIGN
c_func
(paren
r_sizeof
(paren
op_star
id|ucmsg
)paren
)paren
)paren
op_plus
id|CMSG_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
)paren
)paren
suffix:semicolon
id|kcmsg-&gt;cmsg_len
op_assign
id|tmp
suffix:semicolon
id|__get_user
c_func
(paren
id|kcmsg-&gt;cmsg_level
comma
op_amp
id|ucmsg-&gt;cmsg_level
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|kcmsg-&gt;cmsg_type
comma
op_amp
id|ucmsg-&gt;cmsg_type
)paren
suffix:semicolon
multiline_comment|/* Copy over the data. */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|CMSG_DATA
c_func
(paren
id|kcmsg
)paren
comma
id|CMSG_COMPAT_DATA
c_func
(paren
id|ucmsg
)paren
comma
(paren
id|ucmlen
op_minus
id|CMSG_COMPAT_ALIGN
c_func
(paren
r_sizeof
(paren
op_star
id|ucmsg
)paren
)paren
)paren
)paren
)paren
(brace
r_goto
id|out_free_efault
suffix:semicolon
)brace
multiline_comment|/* Advance. */
id|kcmsg
op_assign
(paren
r_struct
id|cmsghdr
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|kcmsg
op_plus
id|CMSG_ALIGN
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|ucmsg
op_assign
id|cmsg_compat_nxthdr
c_func
(paren
id|kmsg
comma
id|ucmsg
comma
id|ucmlen
)paren
suffix:semicolon
)brace
multiline_comment|/* Ok, looks like we made it.  Hook it up and return success. */
id|kmsg-&gt;msg_control
op_assign
id|kcmsg_base
suffix:semicolon
id|kmsg-&gt;msg_controllen
op_assign
id|kcmlen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_free_efault
suffix:colon
r_if
c_cond
(paren
id|kcmsg_base
op_ne
(paren
r_struct
id|cmsghdr
op_star
)paren
id|stackbuf
)paren
(brace
id|kfree
c_func
(paren
id|kcmsg_base
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
DECL|function|put_cmsg_compat
r_int
id|put_cmsg_compat
c_func
(paren
r_struct
id|msghdr
op_star
id|kmsg
comma
r_int
id|level
comma
r_int
id|type
comma
r_int
id|len
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|compat_timeval
id|ctv
suffix:semicolon
r_struct
id|compat_cmsghdr
op_star
id|cm
op_assign
(paren
r_struct
id|compat_cmsghdr
op_star
)paren
id|kmsg-&gt;msg_control
suffix:semicolon
r_struct
id|compat_cmsghdr
id|cmhdr
suffix:semicolon
r_int
id|cmlen
suffix:semicolon
r_if
c_cond
(paren
id|cm
op_eq
l_int|NULL
op_logical_or
id|kmsg-&gt;msg_controllen
OL
r_sizeof
(paren
op_star
id|cm
)paren
)paren
(brace
id|kmsg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* XXX: return error? check spec. */
)brace
r_if
c_cond
(paren
id|level
op_eq
id|SOL_SOCKET
op_logical_and
id|type
op_eq
id|SO_TIMESTAMP
)paren
(brace
r_struct
id|timeval
op_star
id|tv
op_assign
(paren
r_struct
id|timeval
op_star
)paren
id|data
suffix:semicolon
id|ctv.tv_sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|ctv.tv_usec
op_assign
id|tv-&gt;tv_usec
suffix:semicolon
id|data
op_assign
op_amp
id|ctv
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
r_struct
id|compat_timeval
)paren
suffix:semicolon
)brace
id|cmlen
op_assign
id|CMSG_COMPAT_LEN
c_func
(paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kmsg-&gt;msg_controllen
OL
id|cmlen
)paren
(brace
id|kmsg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
id|cmlen
op_assign
id|kmsg-&gt;msg_controllen
suffix:semicolon
)brace
id|cmhdr.cmsg_level
op_assign
id|level
suffix:semicolon
id|cmhdr.cmsg_type
op_assign
id|type
suffix:semicolon
id|cmhdr.cmsg_len
op_assign
id|cmlen
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|cm
comma
op_amp
id|cmhdr
comma
r_sizeof
id|cmhdr
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|CMSG_COMPAT_DATA
c_func
(paren
id|cm
)paren
comma
id|data
comma
id|cmlen
op_minus
r_sizeof
(paren
r_struct
id|compat_cmsghdr
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|cmlen
op_assign
id|CMSG_COMPAT_SPACE
c_func
(paren
id|len
)paren
suffix:semicolon
id|kmsg-&gt;msg_control
op_add_assign
id|cmlen
suffix:semicolon
id|kmsg-&gt;msg_controllen
op_sub_assign
id|cmlen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scm_detach_fds_compat
r_void
id|scm_detach_fds_compat
c_func
(paren
r_struct
id|msghdr
op_star
id|kmsg
comma
r_struct
id|scm_cookie
op_star
id|scm
)paren
(brace
r_struct
id|compat_cmsghdr
op_star
id|cm
op_assign
(paren
r_struct
id|compat_cmsghdr
op_star
)paren
id|kmsg-&gt;msg_control
suffix:semicolon
r_int
id|fdmax
op_assign
(paren
id|kmsg-&gt;msg_controllen
op_minus
r_sizeof
(paren
r_struct
id|compat_cmsghdr
)paren
)paren
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_int
id|fdnum
op_assign
id|scm-&gt;fp-&gt;count
suffix:semicolon
r_struct
id|file
op_star
op_star
id|fp
op_assign
id|scm-&gt;fp-&gt;fp
suffix:semicolon
r_int
op_star
id|cmfptr
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|fdnum
OL
id|fdmax
)paren
id|fdmax
op_assign
id|fdnum
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|cmfptr
op_assign
(paren
r_int
op_star
)paren
id|CMSG_COMPAT_DATA
c_func
(paren
id|cm
)paren
suffix:semicolon
id|i
OL
id|fdmax
suffix:semicolon
id|i
op_increment
comma
id|cmfptr
op_increment
)paren
(brace
r_int
id|new_fd
suffix:semicolon
id|err
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_break
suffix:semicolon
id|new_fd
op_assign
id|err
suffix:semicolon
id|err
op_assign
id|put_user
c_func
(paren
id|new_fd
comma
id|cmfptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|put_unused_fd
c_func
(paren
id|new_fd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Bump the usage count and install the file. */
id|get_file
c_func
(paren
id|fp
(braket
id|i
)braket
)paren
suffix:semicolon
id|fd_install
c_func
(paren
id|new_fd
comma
id|fp
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
r_int
id|cmlen
op_assign
id|CMSG_COMPAT_LEN
c_func
(paren
id|i
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|put_user
c_func
(paren
id|SOL_SOCKET
comma
op_amp
id|cm-&gt;cmsg_level
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|put_user
c_func
(paren
id|SCM_RIGHTS
comma
op_amp
id|cm-&gt;cmsg_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|put_user
c_func
(paren
id|cmlen
comma
op_amp
id|cm-&gt;cmsg_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|cmlen
op_assign
id|CMSG_COMPAT_SPACE
c_func
(paren
id|i
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|kmsg-&gt;msg_control
op_add_assign
id|cmlen
suffix:semicolon
id|kmsg-&gt;msg_controllen
op_sub_assign
id|cmlen
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
OL
id|fdnum
)paren
id|kmsg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
multiline_comment|/*&n;&t; * All of the files that fit in the message have had their&n;&t; * usage counts incremented, so we just free the list.&n;&t; */
id|__scm_destroy
c_func
(paren
id|scm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * For now, we assume that the compatibility and native version&n; * of struct ipt_entry are the same - sfr.  FIXME&n; */
DECL|struct|compat_ipt_replace
r_struct
id|compat_ipt_replace
(brace
DECL|member|name
r_char
id|name
(braket
id|IPT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|valid_hooks
id|u32
id|valid_hooks
suffix:semicolon
DECL|member|num_entries
id|u32
id|num_entries
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|hook_entry
id|u32
id|hook_entry
(braket
id|NF_IP_NUMHOOKS
)braket
suffix:semicolon
DECL|member|underflow
id|u32
id|underflow
(braket
id|NF_IP_NUMHOOKS
)braket
suffix:semicolon
DECL|member|num_counters
id|u32
id|num_counters
suffix:semicolon
DECL|member|counters
id|compat_uptr_t
id|counters
suffix:semicolon
multiline_comment|/* struct ipt_counters * */
DECL|member|entries
r_struct
id|ipt_entry
id|entries
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|do_netfilter_replace
r_static
r_int
id|do_netfilter_replace
c_func
(paren
r_int
id|fd
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_struct
id|compat_ipt_replace
op_star
id|urepl
op_assign
(paren
r_struct
id|compat_ipt_replace
op_star
)paren
id|optval
suffix:semicolon
r_struct
id|ipt_replace
op_star
id|repl_nat
suffix:semicolon
r_char
id|name
(braket
id|IPT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
id|u32
id|origsize
comma
id|tmp32
comma
id|num_counters
suffix:semicolon
r_int
r_int
id|repl_nat_size
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|i
suffix:semicolon
id|compat_uptr_t
id|ucntrs
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|origsize
comma
op_amp
id|urepl-&gt;size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Hack: Causes ipchains to give correct error msg --RR */
r_if
c_cond
(paren
id|optlen
op_ne
r_sizeof
(paren
op_star
id|urepl
)paren
op_plus
id|origsize
)paren
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
multiline_comment|/* XXX Assumes that size of ipt_entry is the same both in&n;&t; *     native and compat environments.&n;&t; */
id|repl_nat_size
op_assign
r_sizeof
(paren
op_star
id|repl_nat
)paren
op_plus
id|origsize
suffix:semicolon
id|repl_nat
op_assign
id|compat_alloc_user_space
c_func
(paren
id|repl_nat_size
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|origsize
comma
op_amp
id|repl_nat-&gt;size
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|urepl
comma
id|optlen
)paren
op_logical_or
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|repl_nat
comma
id|optlen
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|name
comma
id|urepl-&gt;name
comma
r_sizeof
(paren
id|urepl-&gt;name
)paren
)paren
op_logical_or
id|__copy_to_user
c_func
(paren
id|repl_nat-&gt;name
comma
id|name
comma
r_sizeof
(paren
id|repl_nat-&gt;name
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|tmp32
comma
op_amp
id|urepl-&gt;valid_hooks
)paren
op_logical_or
id|__put_user
c_func
(paren
id|tmp32
comma
op_amp
id|repl_nat-&gt;valid_hooks
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|tmp32
comma
op_amp
id|urepl-&gt;num_entries
)paren
op_logical_or
id|__put_user
c_func
(paren
id|tmp32
comma
op_amp
id|repl_nat-&gt;num_entries
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|num_counters
comma
op_amp
id|urepl-&gt;num_counters
)paren
op_logical_or
id|__put_user
c_func
(paren
id|num_counters
comma
op_amp
id|repl_nat-&gt;num_counters
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|ucntrs
comma
op_amp
id|urepl-&gt;counters
)paren
op_logical_or
id|__put_user
c_func
(paren
id|compat_ptr
c_func
(paren
id|ucntrs
)paren
comma
op_amp
id|repl_nat-&gt;counters
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|__copy_in_user
c_func
(paren
op_amp
id|repl_nat-&gt;entries
(braket
l_int|0
)braket
comma
op_amp
id|urepl-&gt;entries
(braket
l_int|0
)braket
comma
id|origsize
)paren
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NF_IP_NUMHOOKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|tmp32
comma
op_amp
id|urepl-&gt;hook_entry
(braket
id|i
)braket
)paren
op_logical_or
id|__put_user
c_func
(paren
id|tmp32
comma
op_amp
id|repl_nat-&gt;hook_entry
(braket
id|i
)braket
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tmp32
comma
op_amp
id|urepl-&gt;underflow
(braket
id|i
)braket
)paren
op_logical_or
id|__put_user
c_func
(paren
id|tmp32
comma
op_amp
id|repl_nat-&gt;underflow
(braket
id|i
)braket
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Since struct ipt_counters just contains two u_int64_t members&n;&t; * we can just do the access_ok check here and pass the (converted)&n;&t; * pointer into the standard syscall.  We hope that the pointer is&n;&t; * not misaligned ...&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|compat_ptr
c_func
(paren
id|ucntrs
)paren
comma
id|num_counters
op_star
r_sizeof
(paren
r_struct
id|ipt_counters
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|sys_setsockopt
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
(paren
r_char
op_star
)paren
id|repl_nat
comma
id|repl_nat_size
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * A struct sock_filter is architecture independent.&n; */
DECL|struct|compat_sock_fprog
r_struct
id|compat_sock_fprog
(brace
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|filter
id|compat_uptr_t
id|filter
suffix:semicolon
multiline_comment|/* struct sock_filter * */
)brace
suffix:semicolon
DECL|function|do_set_attach_filter
r_static
r_int
id|do_set_attach_filter
c_func
(paren
r_int
id|fd
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_struct
id|compat_sock_fprog
op_star
id|fprog32
op_assign
(paren
r_struct
id|compat_sock_fprog
op_star
)paren
id|optval
suffix:semicolon
r_struct
id|sock_fprog
op_star
id|kfprog
op_assign
id|compat_alloc_user_space
c_func
(paren
r_sizeof
(paren
r_struct
id|sock_fprog
)paren
)paren
suffix:semicolon
id|compat_uptr_t
id|ptr
suffix:semicolon
id|u16
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|fprog32
comma
r_sizeof
(paren
op_star
id|fprog32
)paren
)paren
op_logical_or
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|kfprog
comma
r_sizeof
(paren
r_struct
id|sock_fprog
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|len
comma
op_amp
id|fprog32-&gt;len
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ptr
comma
op_amp
id|fprog32-&gt;filter
)paren
op_logical_or
id|__put_user
c_func
(paren
id|len
comma
op_amp
id|kfprog-&gt;len
)paren
op_logical_or
id|__put_user
c_func
(paren
id|compat_ptr
c_func
(paren
id|ptr
)paren
comma
op_amp
id|kfprog-&gt;filter
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_setsockopt
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
(paren
r_char
op_star
)paren
id|kfprog
comma
r_sizeof
(paren
r_struct
id|sock_fprog
)paren
)paren
suffix:semicolon
)brace
DECL|function|do_set_sock_timeout
r_static
r_int
id|do_set_sock_timeout
c_func
(paren
r_int
id|fd
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_struct
id|compat_timeval
op_star
id|up
op_assign
(paren
r_struct
id|compat_timeval
op_star
)paren
id|optval
suffix:semicolon
r_struct
id|timeval
id|ktime
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OL
r_sizeof
(paren
op_star
id|up
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|up
comma
r_sizeof
(paren
op_star
id|up
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ktime.tv_sec
comma
op_amp
id|up-&gt;tv_sec
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ktime.tv_usec
comma
op_amp
id|up-&gt;tv_usec
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|old_fs
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
id|err
op_assign
id|sys_setsockopt
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
(paren
r_char
op_star
)paren
op_amp
id|ktime
comma
r_sizeof
(paren
id|ktime
)paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|compat_sys_setsockopt
id|asmlinkage
r_int
id|compat_sys_setsockopt
c_func
(paren
r_int
id|fd
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|optname
op_eq
id|IPT_SO_SET_REPLACE
)paren
r_return
id|do_netfilter_replace
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|SO_ATTACH_FILTER
)paren
r_return
id|do_set_attach_filter
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|SO_RCVTIMEO
op_logical_or
id|optname
op_eq
id|SO_SNDTIMEO
)paren
r_return
id|do_set_sock_timeout
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_return
id|sys_setsockopt
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
DECL|function|do_get_sock_timeout
r_static
r_int
id|do_get_sock_timeout
c_func
(paren
r_int
id|fd
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
(brace
r_struct
id|compat_timeval
op_star
id|up
op_assign
(paren
r_struct
id|compat_timeval
op_star
)paren
id|optval
suffix:semicolon
r_struct
id|timeval
id|ktime
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_int
id|len
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
op_star
id|up
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
id|ktime
)paren
suffix:semicolon
id|old_fs
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
id|err
op_assign
id|sys_getsockopt
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
(paren
r_char
op_star
)paren
op_amp
id|ktime
comma
op_amp
id|len
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
r_sizeof
(paren
op_star
id|up
)paren
comma
id|optlen
)paren
op_logical_or
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|up
comma
r_sizeof
(paren
op_star
id|up
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|ktime.tv_sec
comma
op_amp
id|up-&gt;tv_sec
)paren
op_logical_or
id|__put_user
c_func
(paren
id|ktime.tv_usec
comma
op_amp
id|up-&gt;tv_usec
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|compat_sys_getsockopt
id|asmlinkage
r_int
id|compat_sys_getsockopt
c_func
(paren
r_int
id|fd
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|optname
op_eq
id|SO_RCVTIMEO
op_logical_or
id|optname
op_eq
id|SO_SNDTIMEO
)paren
r_return
id|do_get_sock_timeout
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_return
id|sys_getsockopt
c_func
(paren
id|fd
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
multiline_comment|/* Argument list sizes for compat_sys_socketcall */
DECL|macro|AL
mdefine_line|#define AL(x) ((x) * sizeof(u32))
DECL|variable|nas
r_static
r_int
r_char
id|nas
(braket
l_int|18
)braket
op_assign
initialization_block
suffix:semicolon
DECL|macro|AL
macro_line|#undef AL
DECL|function|compat_sys_sendmsg
id|asmlinkage
r_int
id|compat_sys_sendmsg
c_func
(paren
r_int
id|fd
comma
r_struct
id|compat_msghdr
op_star
id|msg
comma
r_int
id|flags
)paren
(brace
r_return
id|sys_sendmsg
c_func
(paren
id|fd
comma
(paren
r_struct
id|msghdr
op_star
)paren
id|msg
comma
id|flags
op_or
id|MSG_CMSG_COMPAT
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_recvmsg
id|asmlinkage
r_int
id|compat_sys_recvmsg
c_func
(paren
r_int
id|fd
comma
r_struct
id|compat_msghdr
op_star
id|msg
comma
r_int
r_int
id|flags
)paren
(brace
r_return
id|sys_recvmsg
c_func
(paren
id|fd
comma
(paren
r_struct
id|msghdr
op_star
)paren
id|msg
comma
id|flags
op_or
id|MSG_CMSG_COMPAT
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_socketcall
id|asmlinkage
r_int
id|compat_sys_socketcall
c_func
(paren
r_int
id|call
comma
id|u32
op_star
id|args
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u32
id|a
(braket
l_int|6
)braket
suffix:semicolon
id|u32
id|a0
comma
id|a1
suffix:semicolon
r_if
c_cond
(paren
id|call
template_param
id|SYS_RECVMSG
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|a
comma
id|args
comma
id|nas
(braket
id|call
)braket
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|a0
op_assign
id|a
(braket
l_int|0
)braket
suffix:semicolon
id|a1
op_assign
id|a
(braket
l_int|1
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SYS_SOCKET
suffix:colon
id|ret
op_assign
id|sys_socket
c_func
(paren
id|a0
comma
id|a1
comma
id|a
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_BIND
suffix:colon
id|ret
op_assign
id|sys_bind
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_CONNECT
suffix:colon
id|ret
op_assign
id|sys_connect
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_LISTEN
suffix:colon
id|ret
op_assign
id|sys_listen
c_func
(paren
id|a0
comma
id|a1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_ACCEPT
suffix:colon
id|ret
op_assign
id|sys_accept
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_GETSOCKNAME
suffix:colon
id|ret
op_assign
id|sys_getsockname
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_GETPEERNAME
suffix:colon
id|ret
op_assign
id|sys_getpeername
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_SOCKETPAIR
suffix:colon
id|ret
op_assign
id|sys_socketpair
c_func
(paren
id|a0
comma
id|a1
comma
id|a
(braket
l_int|2
)braket
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_SEND
suffix:colon
id|ret
op_assign
id|sys_send
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
comma
id|a
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_SENDTO
suffix:colon
id|ret
op_assign
id|sys_sendto
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
comma
id|a
(braket
l_int|3
)braket
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|4
)braket
)paren
comma
id|a
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_RECV
suffix:colon
id|ret
op_assign
id|sys_recv
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
comma
id|a
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_RECVFROM
suffix:colon
id|ret
op_assign
id|sys_recvfrom
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
comma
id|a
(braket
l_int|3
)braket
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|4
)braket
)paren
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_SHUTDOWN
suffix:colon
id|ret
op_assign
id|sys_shutdown
c_func
(paren
id|a0
comma
id|a1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_SETSOCKOPT
suffix:colon
id|ret
op_assign
id|compat_sys_setsockopt
c_func
(paren
id|a0
comma
id|a1
comma
id|a
(braket
l_int|2
)braket
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|3
)braket
)paren
comma
id|a
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_GETSOCKOPT
suffix:colon
id|ret
op_assign
id|compat_sys_getsockopt
c_func
(paren
id|a0
comma
id|a1
comma
id|a
(braket
l_int|2
)braket
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|3
)braket
)paren
comma
id|compat_ptr
c_func
(paren
id|a
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_SENDMSG
suffix:colon
id|ret
op_assign
id|compat_sys_sendmsg
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_RECVMSG
suffix:colon
id|ret
op_assign
id|compat_sys_recvmsg
c_func
(paren
id|a0
comma
id|compat_ptr
c_func
(paren
id|a1
)paren
comma
id|a
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
