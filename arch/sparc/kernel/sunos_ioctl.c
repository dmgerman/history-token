multiline_comment|/* $Id: sunos_ioctl.c,v 1.34 2000/09/03 14:10:56 anton Exp $&n; * sunos_ioctl.c: The Linux Operating system: SunOS ioctl compatibility.&n; * &n; * Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;asm/kbio.h&gt;
macro_line|#if 0
r_extern
r_char
id|sunkbd_type
suffix:semicolon
r_extern
r_char
id|sunkbd_layout
suffix:semicolon
macro_line|#endif
multiline_comment|/* NR_OPEN is now larger and dynamic in recent kernels. */
DECL|macro|SUNOS_NR_OPEN
mdefine_line|#define SUNOS_NR_OPEN&t;256
DECL|function|sunos_ioctl
id|asmlinkage
r_int
id|sunos_ioctl
(paren
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
id|SUNOS_NR_OPEN
op_logical_or
op_logical_neg
id|fcheck
c_func
(paren
id|fd
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* First handle an easy compat. case for tty ldisc. */
r_if
c_cond
(paren
id|cmd
op_eq
id|TIOCSETD
)paren
(brace
r_int
id|__user
op_star
id|p
suffix:semicolon
r_int
id|ntty
op_assign
id|N_TTY
comma
id|tmp
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
id|p
op_assign
(paren
r_int
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|tmp
comma
id|p
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|2
)paren
(brace
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
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
op_amp
id|ntty
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|ret
op_eq
op_minus
id|EINVAL
ques
c_cond
op_minus
id|EOPNOTSUPP
suffix:colon
id|ret
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/* Binary compatibility is good American knowhow fuckin&squot; up. */
r_if
c_cond
(paren
id|cmd
op_eq
id|TIOCNOTTY
)paren
(brace
id|ret
op_assign
id|sys_setsid
c_func
(paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* SunOS networking ioctls. */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|_IOW
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|10
comma
r_struct
id|rtentry
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCADDRT
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|11
comma
r_struct
id|rtentry
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCDELRT
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|12
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFADDR
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|13
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFADDR
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|14
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFDSTADDR
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|15
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFDSTADDR
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|16
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFFLAGS
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|17
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFFLAGS
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|18
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFMEM
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|19
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFMEM
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|20
comma
r_struct
id|ifconf
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFCONF
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|21
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCSIFMTU */
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFMTU
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|22
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCGIFMTU */
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFMTU
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|23
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFBRDADDR
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|24
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFBRDADDR
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|25
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFNETMASK
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|26
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFNETMASK
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|27
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFMETRIC
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|28
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFMETRIC
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|30
comma
r_struct
id|arpreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSARP
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOWR
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|31
comma
r_struct
id|arpreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGARP
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|32
comma
r_struct
id|arpreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCDARP
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|40
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCUPPER */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|41
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCLOWER */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|44
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCSETSYNC */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|45
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCGETSYNC */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|46
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCSSDSTATS */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|47
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCSSESTATS */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|48
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCSPROMISC */
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|49
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCADDMULTI
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|50
comma
r_struct
id|ifreq
)paren
suffix:colon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCDELMULTI
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* FDDI interface ioctls, unsupported. */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|51
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCFDRESET */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|52
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCFDSLEEP */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|53
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCSTRTFMWAR */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|54
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCLDNSTRTFW */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|55
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCGETFDSTAT */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|56
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCFDNMIINT */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|57
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCFDEXUSER */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|58
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCFDGNETMAP */
r_case
id|_IOW
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|59
comma
r_struct
id|ifreq
)paren
suffix:colon
multiline_comment|/* SIOCFDGIOCTL */
id|printk
c_func
(paren
l_string|&quot;FDDI ioctl, returning EOPNOTSUPP&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|_IOW
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|125
comma
r_int
)paren
suffix:colon
multiline_comment|/* More stupid tty sunos ioctls, just&n;&t;&t; * say it worked.&n;&t;&t; */
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* Non posix grp */
r_case
id|_IOW
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|118
comma
r_int
)paren
suffix:colon
(brace
r_int
id|oldval
comma
id|newval
comma
id|__user
op_star
id|ptr
suffix:semicolon
id|cmd
op_assign
id|TIOCSPGRP
suffix:semicolon
id|ptr
op_assign
(paren
r_int
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|oldval
comma
id|ptr
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|newval
comma
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newval
op_eq
op_minus
l_int|1
)paren
(brace
id|__put_user
c_func
(paren
id|oldval
comma
id|ptr
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOTTY
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_case
id|_IOR
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|119
comma
r_int
)paren
suffix:colon
(brace
r_int
id|oldval
comma
id|newval
comma
id|__user
op_star
id|ptr
suffix:semicolon
id|cmd
op_assign
id|TIOCGPGRP
suffix:semicolon
id|ptr
op_assign
(paren
r_int
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|oldval
comma
id|ptr
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|newval
comma
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newval
op_eq
op_minus
l_int|1
)paren
(brace
id|__put_user
c_func
(paren
id|oldval
comma
id|ptr
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOTTY
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|cmd
op_amp
l_int|0xff00
)paren
op_eq
(paren
l_char|&squot;k&squot;
op_lshift
l_int|8
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[[KBIO: %8.8x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|cmd
)paren
suffix:semicolon
)brace
macro_line|#endif
id|ret
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* so stupid... */
id|ret
op_assign
(paren
id|ret
op_eq
op_minus
id|EINVAL
ques
c_cond
op_minus
id|EOPNOTSUPP
suffix:colon
id|ret
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
eof
