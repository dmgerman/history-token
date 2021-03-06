macro_line|#ifndef _LINUX_SHM_H_
DECL|macro|_LINUX_SHM_H_
mdefine_line|#define _LINUX_SHM_H_
macro_line|#include &lt;linux/ipc.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * SHMMAX, SHMMNI and SHMALL are upper limits are defaults which can&n; * be increased by sysctl&n; */
DECL|macro|SHMMAX
mdefine_line|#define SHMMAX 0x2000000&t;&t; /* max shared seg size (bytes) */
DECL|macro|SHMMIN
mdefine_line|#define SHMMIN 1&t;&t;&t; /* min shared seg size (bytes) */
DECL|macro|SHMMNI
mdefine_line|#define SHMMNI 4096&t;&t;&t; /* max num of segs system wide */
DECL|macro|SHMALL
mdefine_line|#define SHMALL (SHMMAX/PAGE_SIZE*(SHMMNI/16)) /* max shm system wide (pages) */
DECL|macro|SHMSEG
mdefine_line|#define SHMSEG SHMMNI&t;&t;&t; /* max shared segs per process */
macro_line|#include &lt;asm/shmparam.h&gt;
multiline_comment|/* Obsolete, used only for backwards compatibility and libc5 compiles */
DECL|struct|shmid_ds
r_struct
id|shmid_ds
(brace
DECL|member|shm_perm
r_struct
id|ipc_perm
id|shm_perm
suffix:semicolon
multiline_comment|/* operation perms */
DECL|member|shm_segsz
r_int
id|shm_segsz
suffix:semicolon
multiline_comment|/* size of segment (bytes) */
DECL|member|shm_atime
id|__kernel_time_t
id|shm_atime
suffix:semicolon
multiline_comment|/* last attach time */
DECL|member|shm_dtime
id|__kernel_time_t
id|shm_dtime
suffix:semicolon
multiline_comment|/* last detach time */
DECL|member|shm_ctime
id|__kernel_time_t
id|shm_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|shm_cpid
id|__kernel_ipc_pid_t
id|shm_cpid
suffix:semicolon
multiline_comment|/* pid of creator */
DECL|member|shm_lpid
id|__kernel_ipc_pid_t
id|shm_lpid
suffix:semicolon
multiline_comment|/* pid of last operator */
DECL|member|shm_nattch
r_int
r_int
id|shm_nattch
suffix:semicolon
multiline_comment|/* no. of current attaches */
DECL|member|shm_unused
r_int
r_int
id|shm_unused
suffix:semicolon
multiline_comment|/* compatibility */
DECL|member|shm_unused2
r_void
op_star
id|shm_unused2
suffix:semicolon
multiline_comment|/* ditto - used by DIPC */
DECL|member|shm_unused3
r_void
op_star
id|shm_unused3
suffix:semicolon
multiline_comment|/* unused */
)brace
suffix:semicolon
multiline_comment|/* Include the definition of shmid64_ds and shminfo64 */
macro_line|#include &lt;asm/shmbuf.h&gt;
multiline_comment|/* permission flag for shmget */
DECL|macro|SHM_R
mdefine_line|#define SHM_R&t;&t;0400&t;/* or S_IRUGO from &lt;linux/stat.h&gt; */
DECL|macro|SHM_W
mdefine_line|#define SHM_W&t;&t;0200&t;/* or S_IWUGO from &lt;linux/stat.h&gt; */
multiline_comment|/* mode for attach */
DECL|macro|SHM_RDONLY
mdefine_line|#define&t;SHM_RDONLY&t;010000&t;/* read-only access */
DECL|macro|SHM_RND
mdefine_line|#define&t;SHM_RND&t;&t;020000&t;/* round attach address to SHMLBA boundary */
DECL|macro|SHM_REMAP
mdefine_line|#define&t;SHM_REMAP&t;040000&t;/* take-over region on attach */
DECL|macro|SHM_EXEC
mdefine_line|#define&t;SHM_EXEC&t;0100000&t;/* execution access */
multiline_comment|/* super user shmctl commands */
DECL|macro|SHM_LOCK
mdefine_line|#define SHM_LOCK &t;11
DECL|macro|SHM_UNLOCK
mdefine_line|#define SHM_UNLOCK &t;12
multiline_comment|/* ipcs ctl commands */
DECL|macro|SHM_STAT
mdefine_line|#define SHM_STAT &t;13
DECL|macro|SHM_INFO
mdefine_line|#define SHM_INFO &t;14
multiline_comment|/* Obsolete, used only for backwards compatibility */
DECL|struct|shminfo
r_struct
id|shminfo
(brace
DECL|member|shmmax
r_int
id|shmmax
suffix:semicolon
DECL|member|shmmin
r_int
id|shmmin
suffix:semicolon
DECL|member|shmmni
r_int
id|shmmni
suffix:semicolon
DECL|member|shmseg
r_int
id|shmseg
suffix:semicolon
DECL|member|shmall
r_int
id|shmall
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|shm_info
r_struct
id|shm_info
(brace
DECL|member|used_ids
r_int
id|used_ids
suffix:semicolon
DECL|member|shm_tot
r_int
r_int
id|shm_tot
suffix:semicolon
multiline_comment|/* total allocated shm */
DECL|member|shm_rss
r_int
r_int
id|shm_rss
suffix:semicolon
multiline_comment|/* total resident shm */
DECL|member|shm_swp
r_int
r_int
id|shm_swp
suffix:semicolon
multiline_comment|/* total swapped shm */
DECL|member|swap_attempts
r_int
r_int
id|swap_attempts
suffix:semicolon
DECL|member|swap_successes
r_int
r_int
id|swap_successes
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|shmid_kernel
r_struct
id|shmid_kernel
multiline_comment|/* private to the kernel */
(brace
DECL|member|shm_perm
r_struct
id|kern_ipc_perm
id|shm_perm
suffix:semicolon
DECL|member|shm_file
r_struct
id|file
op_star
id|shm_file
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|shm_nattch
r_int
r_int
id|shm_nattch
suffix:semicolon
DECL|member|shm_segsz
r_int
r_int
id|shm_segsz
suffix:semicolon
DECL|member|shm_atim
id|time_t
id|shm_atim
suffix:semicolon
DECL|member|shm_dtim
id|time_t
id|shm_dtim
suffix:semicolon
DECL|member|shm_ctim
id|time_t
id|shm_ctim
suffix:semicolon
DECL|member|shm_cprid
id|pid_t
id|shm_cprid
suffix:semicolon
DECL|member|shm_lprid
id|pid_t
id|shm_lprid
suffix:semicolon
DECL|member|mlock_user
r_struct
id|user_struct
op_star
id|mlock_user
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* shm_mode upper byte flags */
DECL|macro|SHM_DEST
mdefine_line|#define&t;SHM_DEST&t;01000&t;/* segment will be destroyed on last detach */
DECL|macro|SHM_LOCKED
mdefine_line|#define SHM_LOCKED      02000   /* segment will not be swapped */
DECL|macro|SHM_HUGETLB
mdefine_line|#define SHM_HUGETLB     04000   /* segment will use huge TLB pages */
macro_line|#ifdef CONFIG_SYSVIPC
r_int
id|do_shmat
c_func
(paren
r_int
id|shmid
comma
r_char
id|__user
op_star
id|shmaddr
comma
r_int
id|shmflg
comma
r_int
r_int
op_star
id|addr
)paren
suffix:semicolon
macro_line|#else
DECL|function|do_shmat
r_static
r_inline
r_int
id|do_shmat
c_func
(paren
r_int
id|shmid
comma
r_char
id|__user
op_star
id|shmaddr
comma
r_int
id|shmflg
comma
r_int
r_int
op_star
id|addr
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SHM_H_ */
eof
