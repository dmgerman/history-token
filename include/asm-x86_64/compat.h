macro_line|#ifndef _ASM_X86_64_COMPAT_H
DECL|macro|_ASM_X86_64_COMPAT_H
mdefine_line|#define _ASM_X86_64_COMPAT_H
multiline_comment|/*&n; * Architecture specific compatibility types&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
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
DECL|typedef|compat_uid32_t
r_typedef
id|u32
id|compat_uid32_t
suffix:semicolon
DECL|typedef|compat_gid32_t
r_typedef
id|u32
id|compat_gid32_t
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
DECL|typedef|compat_fsid_t
r_typedef
id|__kernel_fsid_t
id|compat_fsid_t
suffix:semicolon
DECL|typedef|compat_timer_t
r_typedef
id|s32
id|compat_timer_t
suffix:semicolon
DECL|typedef|compat_key_t
r_typedef
id|s32
id|compat_key_t
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
DECL|member|__pad1
id|u16
id|__pad1
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
DECL|member|__pad2
id|u16
id|__pad2
suffix:semicolon
DECL|member|st_size
id|u32
id|st_size
suffix:semicolon
DECL|member|st_blksize
id|u32
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
id|u32
id|st_blocks
suffix:semicolon
DECL|member|st_atime
id|u32
id|st_atime
suffix:semicolon
DECL|member|st_atime_nsec
id|u32
id|st_atime_nsec
suffix:semicolon
DECL|member|st_mtime
id|u32
id|st_mtime
suffix:semicolon
DECL|member|st_mtime_nsec
id|u32
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_ctime
id|u32
id|st_ctime
suffix:semicolon
DECL|member|st_ctime_nsec
id|u32
id|st_ctime_nsec
suffix:semicolon
DECL|member|__unused4
id|u32
id|__unused4
suffix:semicolon
DECL|member|__unused5
id|u32
id|__unused5
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
DECL|macro|F_GETLK64
mdefine_line|#define F_GETLK64&t;12&t;/*  using &squot;struct flock64&squot; */
DECL|macro|F_SETLK64
mdefine_line|#define F_SETLK64&t;13
DECL|macro|F_SETLKW64
mdefine_line|#define F_SETLKW64&t;14
multiline_comment|/*&n; * IA32 uses 4 byte alignment for 64 bit quantities,&n; * so we need to pack this structure.&n; */
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
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
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
DECL|member|f_frsize
r_int
id|f_frsize
suffix:semicolon
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|COMPAT_RLIM_OLD_INFINITY
mdefine_line|#define COMPAT_RLIM_OLD_INFINITY&t;0x7fffffff
DECL|macro|COMPAT_RLIM_INFINITY
mdefine_line|#define COMPAT_RLIM_INFINITY&t;&t;0xffffffff
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
DECL|struct|compat_ipc64_perm
r_struct
id|compat_ipc64_perm
(brace
DECL|member|key
id|compat_key_t
id|key
suffix:semicolon
DECL|member|uid
id|compat_uid32_t
id|uid
suffix:semicolon
DECL|member|gid
id|compat_gid32_t
id|gid
suffix:semicolon
DECL|member|cuid
id|compat_uid32_t
id|cuid
suffix:semicolon
DECL|member|cgid
id|compat_gid32_t
id|cgid
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|__pad1
r_int
r_int
id|__pad1
suffix:semicolon
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
DECL|member|__pad2
r_int
r_int
id|__pad2
suffix:semicolon
DECL|member|unused1
id|compat_ulong_t
id|unused1
suffix:semicolon
DECL|member|unused2
id|compat_ulong_t
id|unused2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_semid64_ds
r_struct
id|compat_semid64_ds
(brace
DECL|member|sem_perm
r_struct
id|compat_ipc64_perm
id|sem_perm
suffix:semicolon
DECL|member|sem_otime
id|compat_time_t
id|sem_otime
suffix:semicolon
DECL|member|__unused1
id|compat_ulong_t
id|__unused1
suffix:semicolon
DECL|member|sem_ctime
id|compat_time_t
id|sem_ctime
suffix:semicolon
DECL|member|__unused2
id|compat_ulong_t
id|__unused2
suffix:semicolon
DECL|member|sem_nsems
id|compat_ulong_t
id|sem_nsems
suffix:semicolon
DECL|member|__unused3
id|compat_ulong_t
id|__unused3
suffix:semicolon
DECL|member|__unused4
id|compat_ulong_t
id|__unused4
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_msqid64_ds
r_struct
id|compat_msqid64_ds
(brace
DECL|member|msg_perm
r_struct
id|compat_ipc64_perm
id|msg_perm
suffix:semicolon
DECL|member|msg_stime
id|compat_time_t
id|msg_stime
suffix:semicolon
DECL|member|__unused1
id|compat_ulong_t
id|__unused1
suffix:semicolon
DECL|member|msg_rtime
id|compat_time_t
id|msg_rtime
suffix:semicolon
DECL|member|__unused2
id|compat_ulong_t
id|__unused2
suffix:semicolon
DECL|member|msg_ctime
id|compat_time_t
id|msg_ctime
suffix:semicolon
DECL|member|__unused3
id|compat_ulong_t
id|__unused3
suffix:semicolon
DECL|member|msg_cbytes
id|compat_ulong_t
id|msg_cbytes
suffix:semicolon
DECL|member|msg_qnum
id|compat_ulong_t
id|msg_qnum
suffix:semicolon
DECL|member|msg_qbytes
id|compat_ulong_t
id|msg_qbytes
suffix:semicolon
DECL|member|msg_lspid
id|compat_pid_t
id|msg_lspid
suffix:semicolon
DECL|member|msg_lrpid
id|compat_pid_t
id|msg_lrpid
suffix:semicolon
DECL|member|__unused4
id|compat_ulong_t
id|__unused4
suffix:semicolon
DECL|member|__unused5
id|compat_ulong_t
id|__unused5
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_shmid64_ds
r_struct
id|compat_shmid64_ds
(brace
DECL|member|shm_perm
r_struct
id|compat_ipc64_perm
id|shm_perm
suffix:semicolon
DECL|member|shm_segsz
id|compat_size_t
id|shm_segsz
suffix:semicolon
DECL|member|shm_atime
id|compat_time_t
id|shm_atime
suffix:semicolon
DECL|member|__unused1
id|compat_ulong_t
id|__unused1
suffix:semicolon
DECL|member|shm_dtime
id|compat_time_t
id|shm_dtime
suffix:semicolon
DECL|member|__unused2
id|compat_ulong_t
id|__unused2
suffix:semicolon
DECL|member|shm_ctime
id|compat_time_t
id|shm_ctime
suffix:semicolon
DECL|member|__unused3
id|compat_ulong_t
id|__unused3
suffix:semicolon
DECL|member|shm_cpid
id|compat_pid_t
id|shm_cpid
suffix:semicolon
DECL|member|shm_lpid
id|compat_pid_t
id|shm_lpid
suffix:semicolon
DECL|member|shm_nattch
id|compat_ulong_t
id|shm_nattch
suffix:semicolon
DECL|member|__unused4
id|compat_ulong_t
id|__unused4
suffix:semicolon
DECL|member|__unused5
id|compat_ulong_t
id|__unused5
suffix:semicolon
)brace
suffix:semicolon
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
(paren
r_void
op_star
)paren
id|current-&gt;thread.rsp0
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
r_return
(paren
r_void
id|__user
op_star
)paren
id|regs-&gt;rsp
op_minus
id|len
suffix:semicolon
)brace
macro_line|#endif /* _ASM_X86_64_COMPAT_H */
eof
