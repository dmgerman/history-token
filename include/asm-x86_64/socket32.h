macro_line|#ifndef SOCKET32_H
DECL|macro|SOCKET32_H
mdefine_line|#define SOCKET32_H 1
multiline_comment|/* XXX This really belongs in some header file... -DaveM */
DECL|macro|MAX_SOCK_ADDR
mdefine_line|#define MAX_SOCK_ADDR&t;128&t;&t;/* 108 for Unix domain - &n;&t;&t;&t;&t;&t;   16 for IP, 16 for IPX,&n;&t;&t;&t;&t;&t;   24 for IPv6,&n;&t;&t;&t;&t;&t;   about 80 for AX.25 */
DECL|struct|msghdr32
r_struct
id|msghdr32
(brace
DECL|member|msg_name
id|u32
id|msg_name
suffix:semicolon
DECL|member|msg_namelen
r_int
id|msg_namelen
suffix:semicolon
DECL|member|msg_iov
id|u32
id|msg_iov
suffix:semicolon
DECL|member|msg_iovlen
id|__kernel_size_t32
id|msg_iovlen
suffix:semicolon
DECL|member|msg_control
id|u32
id|msg_control
suffix:semicolon
DECL|member|msg_controllen
id|__kernel_size_t32
id|msg_controllen
suffix:semicolon
DECL|member|msg_flags
r_int
id|msg_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cmsghdr32
r_struct
id|cmsghdr32
(brace
DECL|member|cmsg_len
id|__kernel_size_t32
id|cmsg_len
suffix:semicolon
DECL|member|cmsg_level
r_int
id|cmsg_level
suffix:semicolon
DECL|member|cmsg_type
r_int
id|cmsg_type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bleech... */
DECL|macro|__CMSG32_NXTHDR
mdefine_line|#define __CMSG32_NXTHDR(ctl, len, cmsg, cmsglen) __cmsg32_nxthdr((ctl),(len),(cmsg),(cmsglen))
DECL|macro|CMSG32_NXTHDR
mdefine_line|#define CMSG32_NXTHDR(mhdr, cmsg, cmsglen) cmsg32_nxthdr((mhdr), (cmsg), (cmsglen))
DECL|macro|CMSG32_ALIGN
mdefine_line|#define CMSG32_ALIGN(len) ( ((len)+sizeof(int)-1) &amp; ~(sizeof(int)-1) )
DECL|macro|CMSG32_DATA
mdefine_line|#define CMSG32_DATA(cmsg)&t;((void *)((char *)(cmsg) + CMSG32_ALIGN(sizeof(struct cmsghdr32))))
DECL|macro|CMSG32_SPACE
mdefine_line|#define CMSG32_SPACE(len) (CMSG32_ALIGN(sizeof(struct cmsghdr32)) + CMSG32_ALIGN(len))
DECL|macro|CMSG32_LEN
mdefine_line|#define CMSG32_LEN(len) (CMSG32_ALIGN(sizeof(struct cmsghdr32)) + (len))
DECL|macro|__CMSG32_FIRSTHDR
mdefine_line|#define __CMSG32_FIRSTHDR(ctl,len) ((len) &gt;= sizeof(struct cmsghdr32) ? &bslash;&n;&t;&t;&t;&t;    (struct cmsghdr32 *)(ctl) : &bslash;&n;&t;&t;&t;&t;    (struct cmsghdr32 *)NULL)
DECL|macro|CMSG32_FIRSTHDR
mdefine_line|#define CMSG32_FIRSTHDR(msg)&t;__CMSG32_FIRSTHDR((msg)-&gt;msg_control, (msg)-&gt;msg_controllen)
DECL|function|__cmsg32_nxthdr
id|__inline__
r_struct
id|cmsghdr32
op_star
id|__cmsg32_nxthdr
c_func
(paren
r_void
op_star
id|__ctl
comma
id|__kernel_size_t
id|__size
comma
r_struct
id|cmsghdr32
op_star
id|__cmsg
comma
r_int
id|__cmsg_len
)paren
(brace
r_struct
id|cmsghdr32
op_star
id|__ptr
suffix:semicolon
id|__ptr
op_assign
(paren
r_struct
id|cmsghdr32
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|__cmsg
)paren
op_plus
id|CMSG32_ALIGN
c_func
(paren
id|__cmsg_len
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
id|__ptr
op_plus
l_int|1
)paren
op_minus
(paren
r_char
op_star
)paren
id|__ctl
)paren
OG
id|__size
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|__ptr
suffix:semicolon
)brace
DECL|function|cmsg32_nxthdr
id|__inline__
r_struct
id|cmsghdr32
op_star
id|cmsg32_nxthdr
(paren
r_struct
id|msghdr
op_star
id|__msg
comma
r_struct
id|cmsghdr32
op_star
id|__cmsg
comma
r_int
id|__cmsg_len
)paren
(brace
r_return
id|__cmsg32_nxthdr
c_func
(paren
id|__msg-&gt;msg_control
comma
id|__msg-&gt;msg_controllen
comma
id|__cmsg
comma
id|__cmsg_len
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
