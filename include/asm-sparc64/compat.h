macro_line|#ifndef _ASM_SPARC64_COMPAT_H
DECL|macro|_ASM_SPARC64_COMPAT_H
mdefine_line|#define _ASM_SPARC64_COMPAT_H
multiline_comment|/*&n; * Architecture specific compatibility types&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|COMPAT_USER_HZ
mdefine_line|#define COMPAT_USER_HZ&t;100
DECL|typedef|compat_size_t
r_typedef
id|u32
id|compat_size_t
suffix:semicolon
DECL|typedef|compat_ssize_t
r_typedef
id|s32
id|compat_ssize_t
suffix:semicolon
DECL|typedef|compat_time_t
r_typedef
id|s32
id|compat_time_t
suffix:semicolon
DECL|typedef|compat_clock_t
r_typedef
id|s32
id|compat_clock_t
suffix:semicolon
DECL|typedef|compat_pid_t
r_typedef
id|s32
id|compat_pid_t
suffix:semicolon
DECL|typedef|compat_uid_t
r_typedef
id|u16
id|compat_uid_t
suffix:semicolon
DECL|typedef|compat_gid_t
r_typedef
id|u16
id|compat_gid_t
suffix:semicolon
DECL|typedef|compat_mode_t
r_typedef
id|u16
id|compat_mode_t
suffix:semicolon
DECL|typedef|compat_ino_t
r_typedef
id|u32
id|compat_ino_t
suffix:semicolon
DECL|typedef|compat_dev_t
r_typedef
id|u16
id|compat_dev_t
suffix:semicolon
DECL|typedef|compat_off_t
r_typedef
id|s32
id|compat_off_t
suffix:semicolon
DECL|typedef|compat_loff_t
r_typedef
id|s64
id|compat_loff_t
suffix:semicolon
DECL|typedef|compat_nlink_t
r_typedef
id|s16
id|compat_nlink_t
suffix:semicolon
DECL|typedef|compat_ipc_pid_t
r_typedef
id|u16
id|compat_ipc_pid_t
suffix:semicolon
DECL|typedef|compat_daddr_t
r_typedef
id|s32
id|compat_daddr_t
suffix:semicolon
DECL|typedef|compat_caddr_t
r_typedef
id|u32
id|compat_caddr_t
suffix:semicolon
DECL|typedef|compat_fsid_t
r_typedef
id|__kernel_fsid_t
id|compat_fsid_t
suffix:semicolon
DECL|typedef|compat_int_t
r_typedef
id|s32
id|compat_int_t
suffix:semicolon
DECL|typedef|compat_long_t
r_typedef
id|s32
id|compat_long_t
suffix:semicolon
DECL|typedef|compat_uint_t
r_typedef
id|u32
id|compat_uint_t
suffix:semicolon
DECL|typedef|compat_ulong_t
r_typedef
id|u32
id|compat_ulong_t
suffix:semicolon
DECL|struct|compat_timespec
r_struct
id|compat_timespec
(brace
DECL|member|tv_sec
id|compat_time_t
id|tv_sec
suffix:semicolon
DECL|member|tv_nsec
id|s32
id|tv_nsec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_timeval
r_struct
id|compat_timeval
(brace
DECL|member|tv_sec
id|compat_time_t
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
id|s32
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_stat
r_struct
id|compat_stat
(brace
DECL|member|st_dev
id|compat_dev_t
id|st_dev
suffix:semicolon
DECL|member|st_ino
id|compat_ino_t
id|st_ino
suffix:semicolon
DECL|member|st_mode
id|compat_mode_t
id|st_mode
suffix:semicolon
DECL|member|st_nlink
id|compat_nlink_t
id|st_nlink
suffix:semicolon
DECL|member|st_uid
id|compat_uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|compat_gid_t
id|st_gid
suffix:semicolon
DECL|member|st_rdev
id|compat_dev_t
id|st_rdev
suffix:semicolon
DECL|member|st_size
id|compat_off_t
id|st_size
suffix:semicolon
DECL|member|st_atime
id|compat_time_t
id|st_atime
suffix:semicolon
DECL|member|__unused1
id|u32
id|__unused1
suffix:semicolon
DECL|member|st_mtime
id|compat_time_t
id|st_mtime
suffix:semicolon
DECL|member|__unused2
id|u32
id|__unused2
suffix:semicolon
DECL|member|st_ctime
id|compat_time_t
id|st_ctime
suffix:semicolon
DECL|member|__unused3
id|u32
id|__unused3
suffix:semicolon
DECL|member|st_blksize
id|compat_off_t
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
id|compat_off_t
id|st_blocks
suffix:semicolon
DECL|member|__unused4
id|u32
id|__unused4
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_flock
r_struct
id|compat_flock
(brace
DECL|member|l_type
r_int
id|l_type
suffix:semicolon
DECL|member|l_whence
r_int
id|l_whence
suffix:semicolon
DECL|member|l_start
id|compat_off_t
id|l_start
suffix:semicolon
DECL|member|l_len
id|compat_off_t
id|l_len
suffix:semicolon
DECL|member|l_pid
id|compat_pid_t
id|l_pid
suffix:semicolon
DECL|member|__unused
r_int
id|__unused
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|F_GETLK64
mdefine_line|#define F_GETLK64&t;12
DECL|macro|F_SETLK64
mdefine_line|#define F_SETLK64&t;13
DECL|macro|F_SETLKW64
mdefine_line|#define F_SETLKW64&t;14
DECL|struct|compat_flock64
r_struct
id|compat_flock64
(brace
DECL|member|l_type
r_int
id|l_type
suffix:semicolon
DECL|member|l_whence
r_int
id|l_whence
suffix:semicolon
DECL|member|l_start
id|compat_loff_t
id|l_start
suffix:semicolon
DECL|member|l_len
id|compat_loff_t
id|l_len
suffix:semicolon
DECL|member|l_pid
id|compat_pid_t
id|l_pid
suffix:semicolon
DECL|member|__unused
r_int
id|__unused
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_statfs
r_struct
id|compat_statfs
(brace
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|member|f_bsize
r_int
id|f_bsize
suffix:semicolon
DECL|member|f_blocks
r_int
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
r_int
id|f_bavail
suffix:semicolon
DECL|member|f_files
r_int
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int
id|f_ffree
suffix:semicolon
DECL|member|f_fsid
id|compat_fsid_t
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
r_int
id|f_namelen
suffix:semicolon
multiline_comment|/* SunOS ignores this field. */
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|COMPAT_RLIM_INFINITY
mdefine_line|#define COMPAT_RLIM_INFINITY 0x7fffffff
DECL|typedef|compat_old_sigset_t
r_typedef
id|u32
id|compat_old_sigset_t
suffix:semicolon
DECL|macro|_COMPAT_NSIG
mdefine_line|#define _COMPAT_NSIG&t;&t;64
DECL|macro|_COMPAT_NSIG_BPW
mdefine_line|#define _COMPAT_NSIG_BPW&t;32
DECL|typedef|compat_sigset_word
r_typedef
id|u32
id|compat_sigset_word
suffix:semicolon
DECL|macro|COMPAT_OFF_T_MAX
mdefine_line|#define COMPAT_OFF_T_MAX&t;0x7fffffff
DECL|macro|COMPAT_LOFF_T_MAX
mdefine_line|#define COMPAT_LOFF_T_MAX&t;0x7fffffffffffffffL
multiline_comment|/*&n; * A pointer passed in from user mode. This should not&n; * be used for syscall parameters, just declare them&n; * as pointers because the syscall entry code will have&n; * appropriately comverted them already.&n; */
DECL|typedef|compat_uptr_t
r_typedef
id|u32
id|compat_uptr_t
suffix:semicolon
DECL|function|compat_ptr
r_static
r_inline
r_void
op_star
id|compat_ptr
c_func
(paren
id|compat_uptr_t
id|uptr
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
id|uptr
suffix:semicolon
)brace
DECL|function|compat_alloc_user_space
r_static
id|__inline__
r_void
op_star
id|compat_alloc_user_space
c_func
(paren
r_int
id|len
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kregs
suffix:semicolon
r_int
r_int
id|usp
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_I6
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
)paren
id|usp
op_add_assign
id|STACK_BIAS
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|usp
op_minus
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SPARC64_COMPAT_H */
eof
