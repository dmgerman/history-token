macro_line|#ifndef _SPARC64_MSGBUF_H
DECL|macro|_SPARC64_MSGBUF_H
mdefine_line|#define _SPARC64_MSGBUF_H
multiline_comment|/* &n; * The msqid64_ds structure for sparc64 architecture.&n; * Note extra padding because this structure is passed back and forth&n; * between kernel and user space.&n; *&n; * Pad space is left for:&n; * - 2 miscellaneous 64-bit values&n; */
DECL|struct|msqid64_ds
r_struct
id|msqid64_ds
(brace
DECL|member|msg_perm
r_struct
id|ipc64_perm
id|msg_perm
suffix:semicolon
DECL|member|msg_stime
id|__kernel_time_t
id|msg_stime
suffix:semicolon
multiline_comment|/* last msgsnd time */
DECL|member|msg_rtime
id|__kernel_time_t
id|msg_rtime
suffix:semicolon
multiline_comment|/* last msgrcv time */
DECL|member|msg_ctime
id|__kernel_time_t
id|msg_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|msg_cbytes
r_int
r_int
id|msg_cbytes
suffix:semicolon
multiline_comment|/* current number of bytes on queue */
DECL|member|msg_qnum
r_int
r_int
id|msg_qnum
suffix:semicolon
multiline_comment|/* number of messages in queue */
DECL|member|msg_qbytes
r_int
r_int
id|msg_qbytes
suffix:semicolon
multiline_comment|/* max number of bytes on queue */
DECL|member|msg_lspid
id|__kernel_pid_t
id|msg_lspid
suffix:semicolon
multiline_comment|/* pid of last msgsnd */
DECL|member|msg_lrpid
id|__kernel_pid_t
id|msg_lrpid
suffix:semicolon
multiline_comment|/* last receive pid */
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _SPARC64_MSGBUF_H */
eof
