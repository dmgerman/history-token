macro_line|#ifndef _ASM_PARISC_COMPAT_H
DECL|macro|_ASM_PARISC_COMPAT_H
mdefine_line|#define _ASM_PARISC_COMPAT_H
multiline_comment|/*&n; * Architecture specific compatibility types&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|COMPAT_USER_HZ
mdefine_line|#define COMPAT_USER_HZ 100
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
id|u32
id|compat_uid_t
suffix:semicolon
DECL|typedef|compat_gid_t
r_typedef
id|u32
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
id|u32
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
id|u16
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
DECL|typedef|compat_timer_t
r_typedef
id|u32
id|compat_timer_t
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
multiline_comment|/* dev_t is 32 bits on parisc */
DECL|member|st_ino
id|compat_ino_t
id|st_ino
suffix:semicolon
multiline_comment|/* 32 bits */
DECL|member|st_mode
id|compat_mode_t
id|st_mode
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|member|st_nlink
id|compat_nlink_t
id|st_nlink
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|member|st_reserved1
id|u16
id|st_reserved1
suffix:semicolon
multiline_comment|/* old st_uid */
DECL|member|st_reserved2
id|u16
id|st_reserved2
suffix:semicolon
multiline_comment|/* old st_gid */
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
DECL|member|st_atime_nsec
id|u32
id|st_atime_nsec
suffix:semicolon
DECL|member|st_mtime
id|compat_time_t
id|st_mtime
suffix:semicolon
DECL|member|st_mtime_nsec
id|u32
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_ctime
id|compat_time_t
id|st_ctime
suffix:semicolon
DECL|member|st_ctime_nsec
id|u32
id|st_ctime_nsec
suffix:semicolon
DECL|member|st_blksize
id|s32
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
id|s32
id|st_blocks
suffix:semicolon
DECL|member|__unused1
id|u32
id|__unused1
suffix:semicolon
multiline_comment|/* ACL stuff */
DECL|member|__unused2
id|compat_dev_t
id|__unused2
suffix:semicolon
multiline_comment|/* network */
DECL|member|__unused3
id|compat_ino_t
id|__unused3
suffix:semicolon
multiline_comment|/* network */
DECL|member|__unused4
id|u32
id|__unused4
suffix:semicolon
multiline_comment|/* cnodes */
DECL|member|__unused5
id|u16
id|__unused5
suffix:semicolon
multiline_comment|/* netsite */
DECL|member|st_fstype
r_int
id|st_fstype
suffix:semicolon
DECL|member|st_realdev
id|compat_dev_t
id|st_realdev
suffix:semicolon
DECL|member|st_basemode
id|u16
id|st_basemode
suffix:semicolon
DECL|member|st_spareshort
id|u16
id|st_spareshort
suffix:semicolon
DECL|member|st_uid
id|compat_uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|compat_gid_t
id|st_gid
suffix:semicolon
DECL|member|st_spare4
id|u32
id|st_spare4
(braket
l_int|3
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
)brace
suffix:semicolon
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
)brace
suffix:semicolon
DECL|struct|compat_statfs
r_struct
id|compat_statfs
(brace
DECL|member|f_type
id|s32
id|f_type
suffix:semicolon
DECL|member|f_bsize
id|s32
id|f_bsize
suffix:semicolon
DECL|member|f_blocks
id|s32
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
id|s32
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
id|s32
id|f_bavail
suffix:semicolon
DECL|member|f_files
id|s32
id|f_files
suffix:semicolon
DECL|member|f_ffree
id|s32
id|f_ffree
suffix:semicolon
DECL|member|f_fsid
id|__kernel_fsid_t
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
id|s32
id|f_namelen
suffix:semicolon
DECL|member|f_frsize
id|s32
id|f_frsize
suffix:semicolon
DECL|member|f_spare
id|s32
id|f_spare
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_sigcontext
r_struct
id|compat_sigcontext
(brace
DECL|member|sc_flags
id|compat_int_t
id|sc_flags
suffix:semicolon
DECL|member|sc_gr
id|compat_int_t
id|sc_gr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* PSW in sc_gr[0] */
DECL|member|sc_fr
id|u64
id|sc_fr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_iasq
id|compat_int_t
id|sc_iasq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sc_iaoq
id|compat_int_t
id|sc_iaoq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sc_sar
id|compat_int_t
id|sc_sar
suffix:semicolon
multiline_comment|/* cr11 */
)brace
suffix:semicolon
DECL|macro|COMPAT_RLIM_INFINITY
mdefine_line|#define COMPAT_RLIM_INFINITY 0xffffffff
DECL|typedef|compat_old_sigset_t
r_typedef
id|u32
id|compat_old_sigset_t
suffix:semicolon
multiline_comment|/* at least 32 bits */
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
id|__user
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
id|__user
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
id|__user
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
op_amp
id|current-&gt;thread.regs
suffix:semicolon
r_return
(paren
r_void
id|__user
op_star
)paren
id|regs-&gt;gr
(braket
l_int|30
)braket
suffix:semicolon
)brace
macro_line|#endif /* _ASM_PARISC_COMPAT_H */
eof
