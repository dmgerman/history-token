macro_line|#ifndef _LINUX_IPC_H
DECL|macro|_LINUX_IPC_H
mdefine_line|#define _LINUX_IPC_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|IPC_PRIVATE
mdefine_line|#define IPC_PRIVATE ((__kernel_key_t) 0)  
multiline_comment|/* Obsolete, used only for backwards compatibility and libc5 compiles */
DECL|struct|ipc_perm
r_struct
id|ipc_perm
(brace
DECL|member|key
id|__kernel_key_t
id|key
suffix:semicolon
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
DECL|member|cuid
id|__kernel_uid_t
id|cuid
suffix:semicolon
DECL|member|cgid
id|__kernel_gid_t
id|cgid
suffix:semicolon
DECL|member|mode
id|__kernel_mode_t
id|mode
suffix:semicolon
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Include the definition of ipc64_perm */
macro_line|#include &lt;asm/ipcbuf.h&gt;
multiline_comment|/* resource get request flags */
DECL|macro|IPC_CREAT
mdefine_line|#define IPC_CREAT  00001000   /* create if key is nonexistent */
DECL|macro|IPC_EXCL
mdefine_line|#define IPC_EXCL   00002000   /* fail if key exists */
DECL|macro|IPC_NOWAIT
mdefine_line|#define IPC_NOWAIT 00004000   /* return error on wait */
multiline_comment|/* these fields are used by the DIPC package so the kernel as standard&n;   should avoid using them if possible */
DECL|macro|IPC_DIPC
mdefine_line|#define IPC_DIPC 00010000  /* make it distributed */
DECL|macro|IPC_OWN
mdefine_line|#define IPC_OWN  00020000  /* this machine is the DIPC owner */
multiline_comment|/* &n; * Control commands used with semctl, msgctl and shmctl &n; * see also specific commands in sem.h, msg.h and shm.h&n; */
DECL|macro|IPC_RMID
mdefine_line|#define IPC_RMID 0     /* remove resource */
DECL|macro|IPC_SET
mdefine_line|#define IPC_SET  1     /* set ipc_perm options */
DECL|macro|IPC_STAT
mdefine_line|#define IPC_STAT 2     /* get ipc_perm options */
DECL|macro|IPC_INFO
mdefine_line|#define IPC_INFO 3     /* see ipcs */
multiline_comment|/*&n; * Version flags for semctl, msgctl, and shmctl commands&n; * These are passed as bitflags or-ed with the actual command&n; */
DECL|macro|IPC_OLD
mdefine_line|#define IPC_OLD 0&t;/* Old version (no 32-bit UID support on many&n;&t;&t;&t;   architectures) */
DECL|macro|IPC_64
mdefine_line|#define IPC_64  0x0100  /* New version (support 32-bit UIDs, bigger&n;&t;&t;&t;   message sizes, etc. */
macro_line|#ifdef __KERNEL__
DECL|macro|IPCMNI
mdefine_line|#define IPCMNI 32768  /* &lt;= MAX_INT limit for ipc arrays (including sysctl changes) */
multiline_comment|/* used by in-kernel data structures */
DECL|struct|kern_ipc_perm
r_struct
id|kern_ipc_perm
(brace
DECL|member|key
id|key_t
id|key
suffix:semicolon
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|cuid
id|uid_t
id|cuid
suffix:semicolon
DECL|member|cgid
id|gid_t
id|cgid
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_IPC_H */
eof
