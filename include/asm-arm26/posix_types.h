multiline_comment|/*&n; *  linux/include/asm-arm/posix_types.h&n; *&n; *  Copyright (C) 1996-1998 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   27-06-1996&t;RMK&t;Created&n; */
macro_line|#ifndef __ARCH_ARM_POSIX_TYPES_H
DECL|macro|__ARCH_ARM_POSIX_TYPES_H
mdefine_line|#define __ARCH_ARM_POSIX_TYPES_H
multiline_comment|/*&n; * This file is generally used by user-level software, so you need to&n; * be a little careful about namespace pollution etc.  Also, we cannot&n; * assume GCC is being used.&n; */
DECL|typedef|__kernel_dev_t
r_typedef
r_int
r_int
id|__kernel_dev_t
suffix:semicolon
DECL|typedef|__kernel_ino_t
r_typedef
r_int
r_int
id|__kernel_ino_t
suffix:semicolon
DECL|typedef|__kernel_mode_t
r_typedef
r_int
r_int
id|__kernel_mode_t
suffix:semicolon
DECL|typedef|__kernel_nlink_t
r_typedef
r_int
r_int
id|__kernel_nlink_t
suffix:semicolon
DECL|typedef|__kernel_off_t
r_typedef
r_int
id|__kernel_off_t
suffix:semicolon
DECL|typedef|__kernel_pid_t
r_typedef
r_int
id|__kernel_pid_t
suffix:semicolon
DECL|typedef|__kernel_ipc_pid_t
r_typedef
r_int
r_int
id|__kernel_ipc_pid_t
suffix:semicolon
DECL|typedef|__kernel_uid_t
r_typedef
r_int
r_int
id|__kernel_uid_t
suffix:semicolon
DECL|typedef|__kernel_gid_t
r_typedef
r_int
r_int
id|__kernel_gid_t
suffix:semicolon
DECL|typedef|__kernel_size_t
r_typedef
r_int
r_int
id|__kernel_size_t
suffix:semicolon
DECL|typedef|__kernel_ssize_t
r_typedef
r_int
id|__kernel_ssize_t
suffix:semicolon
DECL|typedef|__kernel_ptrdiff_t
r_typedef
r_int
id|__kernel_ptrdiff_t
suffix:semicolon
DECL|typedef|__kernel_time_t
r_typedef
r_int
id|__kernel_time_t
suffix:semicolon
DECL|typedef|__kernel_suseconds_t
r_typedef
r_int
id|__kernel_suseconds_t
suffix:semicolon
DECL|typedef|__kernel_clock_t
r_typedef
r_int
id|__kernel_clock_t
suffix:semicolon
DECL|typedef|__kernel_timer_t
r_typedef
r_int
id|__kernel_timer_t
suffix:semicolon
DECL|typedef|__kernel_clockid_t
r_typedef
r_int
id|__kernel_clockid_t
suffix:semicolon
DECL|typedef|__kernel_daddr_t
r_typedef
r_int
id|__kernel_daddr_t
suffix:semicolon
DECL|typedef|__kernel_caddr_t
r_typedef
r_char
op_star
id|__kernel_caddr_t
suffix:semicolon
DECL|typedef|__kernel_uid16_t
r_typedef
r_int
r_int
id|__kernel_uid16_t
suffix:semicolon
DECL|typedef|__kernel_gid16_t
r_typedef
r_int
r_int
id|__kernel_gid16_t
suffix:semicolon
DECL|typedef|__kernel_uid32_t
r_typedef
r_int
r_int
id|__kernel_uid32_t
suffix:semicolon
DECL|typedef|__kernel_gid32_t
r_typedef
r_int
r_int
id|__kernel_gid32_t
suffix:semicolon
DECL|typedef|__kernel_old_uid_t
r_typedef
r_int
r_int
id|__kernel_old_uid_t
suffix:semicolon
DECL|typedef|__kernel_old_gid_t
r_typedef
r_int
r_int
id|__kernel_old_gid_t
suffix:semicolon
macro_line|#ifdef __GNUC__
DECL|typedef|__kernel_loff_t
r_typedef
r_int
r_int
id|__kernel_loff_t
suffix:semicolon
macro_line|#endif
r_typedef
r_struct
(brace
macro_line|#if defined(__KERNEL__) || defined(__USE_ALL)
DECL|member|val
r_int
id|val
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#else /* !defined(__KERNEL__) &amp;&amp; !defined(__USE_ALL) */
r_int
id|__val
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif /* !defined(__KERNEL__) &amp;&amp; !defined(__USE_ALL) */
DECL|typedef|__kernel_fsid_t
)brace
id|__kernel_fsid_t
suffix:semicolon
macro_line|#if defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ &lt; 2)
DECL|macro|__FD_SET
macro_line|#undef&t;__FD_SET
DECL|macro|__FD_SET
mdefine_line|#define __FD_SET(fd, fdsetp) &bslash;&n;&t;&t;(((fd_set *)fdsetp)-&gt;fds_bits[fd &gt;&gt; 5] |= (1&lt;&lt;(fd &amp; 31)))
DECL|macro|__FD_CLR
macro_line|#undef&t;__FD_CLR
DECL|macro|__FD_CLR
mdefine_line|#define __FD_CLR(fd, fdsetp) &bslash;&n;&t;&t;(((fd_set *)fdsetp)-&gt;fds_bits[fd &gt;&gt; 5] &amp;= ~(1&lt;&lt;(fd &amp; 31)))
DECL|macro|__FD_ISSET
macro_line|#undef&t;__FD_ISSET
DECL|macro|__FD_ISSET
mdefine_line|#define __FD_ISSET(fd, fdsetp) &bslash;&n;&t;&t;((((fd_set *)fdsetp)-&gt;fds_bits[fd &gt;&gt; 5] &amp; (1&lt;&lt;(fd &amp; 31))) != 0)
DECL|macro|__FD_ZERO
macro_line|#undef&t;__FD_ZERO
DECL|macro|__FD_ZERO
mdefine_line|#define __FD_ZERO(fdsetp) &bslash;&n;&t;&t;(memset (fdsetp, 0, sizeof (*(fd_set *)fdsetp)))
macro_line|#endif
macro_line|#endif
eof
