multiline_comment|/*&n; *  include/asm-s390/posix_types.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/posix_types.h&quot;&n; */
macro_line|#ifndef __ARCH_S390_POSIX_TYPES_H
DECL|macro|__ARCH_S390_POSIX_TYPES_H
mdefine_line|#define __ARCH_S390_POSIX_TYPES_H
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
DECL|typedef|__kernel_loff_t
r_typedef
r_int
r_int
id|__kernel_loff_t
suffix:semicolon
DECL|typedef|__kernel_pid_t
r_typedef
r_int
id|__kernel_pid_t
suffix:semicolon
DECL|typedef|__kernel_ipc_pid_t
r_typedef
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
DECL|typedef|__kernel_sigset_t
r_typedef
r_int
r_int
id|__kernel_sigset_t
suffix:semicolon
multiline_comment|/* at least 32 bits */
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
DECL|typedef|__kernel_old_uid_t
r_typedef
id|__kernel_uid_t
id|__kernel_old_uid_t
suffix:semicolon
DECL|typedef|__kernel_old_gid_t
r_typedef
id|__kernel_gid_t
id|__kernel_old_gid_t
suffix:semicolon
DECL|typedef|__kernel_uid32_t
r_typedef
id|__kernel_uid_t
id|__kernel_uid32_t
suffix:semicolon
DECL|typedef|__kernel_gid32_t
r_typedef
id|__kernel_gid_t
id|__kernel_gid32_t
suffix:semicolon
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
macro_line|#else                        /* !defined(__KERNEL__) &amp;&amp; !defined(__USE_ALL)*/
r_int
id|__val
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif                       /* !defined(__KERNEL__) &amp;&amp; !defined(__USE_ALL)*/
DECL|typedef|__kernel_fsid_t
)brace
id|__kernel_fsid_t
suffix:semicolon
macro_line|#if defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ &lt; 2)
macro_line|#ifndef _S390_BITOPS_H
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#endif
DECL|macro|__FD_SET
macro_line|#undef  __FD_SET
DECL|macro|__FD_SET
mdefine_line|#define __FD_SET(fd,fdsetp)  set_bit(fd,fdsetp)
DECL|macro|__FD_CLR
macro_line|#undef  __FD_CLR
DECL|macro|__FD_CLR
mdefine_line|#define __FD_CLR(fd,fdsetp)  clear_bit(fd,fdsetp)
DECL|macro|__FD_ISSET
macro_line|#undef  __FD_ISSET
DECL|macro|__FD_ISSET
mdefine_line|#define __FD_ISSET(fd,fdsetp)  test_bit(fd,fdsetp)
DECL|macro|__FD_ZERO
macro_line|#undef  __FD_ZERO
DECL|macro|__FD_ZERO
mdefine_line|#define __FD_ZERO(fdsetp) (memset (fdsetp, 0, sizeof(*(fd_set *)fdsetp)))
macro_line|#endif     /* defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ &lt; 2)*/
macro_line|#endif
eof
