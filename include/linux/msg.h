macro_line|#ifndef _LINUX_MSG_H
DECL|macro|_LINUX_MSG_H
mdefine_line|#define _LINUX_MSG_H
macro_line|#include &lt;linux/ipc.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/* ipcs ctl commands */
DECL|macro|MSG_STAT
mdefine_line|#define MSG_STAT 11
DECL|macro|MSG_INFO
mdefine_line|#define MSG_INFO 12
multiline_comment|/* msgrcv options */
DECL|macro|MSG_NOERROR
mdefine_line|#define MSG_NOERROR     010000  /* no error if message is too big */
DECL|macro|MSG_EXCEPT
mdefine_line|#define MSG_EXCEPT      020000  /* recv any msg except of specified type.*/
multiline_comment|/* Obsolete, used only for backwards compatibility and libc5 compiles */
DECL|struct|msqid_ds
r_struct
id|msqid_ds
(brace
DECL|member|msg_perm
r_struct
id|ipc_perm
id|msg_perm
suffix:semicolon
DECL|member|msg_first
r_struct
id|msg
op_star
id|msg_first
suffix:semicolon
multiline_comment|/* first message on queue,unused  */
DECL|member|msg_last
r_struct
id|msg
op_star
id|msg_last
suffix:semicolon
multiline_comment|/* last message in queue,unused */
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
DECL|member|msg_lcbytes
r_int
r_int
id|msg_lcbytes
suffix:semicolon
multiline_comment|/* Reuse junk fields for 32 bit */
DECL|member|msg_lqbytes
r_int
r_int
id|msg_lqbytes
suffix:semicolon
multiline_comment|/* ditto */
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
id|__kernel_ipc_pid_t
id|msg_lspid
suffix:semicolon
multiline_comment|/* pid of last msgsnd */
DECL|member|msg_lrpid
id|__kernel_ipc_pid_t
id|msg_lrpid
suffix:semicolon
multiline_comment|/* last receive pid */
)brace
suffix:semicolon
multiline_comment|/* Include the definition of msqid64_ds */
macro_line|#include &lt;asm/msgbuf.h&gt;
multiline_comment|/* message buffer for msgsnd and msgrcv calls */
DECL|struct|msgbuf
r_struct
id|msgbuf
(brace
DECL|member|mtype
r_int
id|mtype
suffix:semicolon
multiline_comment|/* type of message */
DECL|member|mtext
r_char
id|mtext
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* message text */
)brace
suffix:semicolon
multiline_comment|/* buffer for msgctl calls IPC_INFO, MSG_INFO */
DECL|struct|msginfo
r_struct
id|msginfo
(brace
DECL|member|msgpool
r_int
id|msgpool
suffix:semicolon
DECL|member|msgmap
r_int
id|msgmap
suffix:semicolon
DECL|member|msgmax
r_int
id|msgmax
suffix:semicolon
DECL|member|msgmnb
r_int
id|msgmnb
suffix:semicolon
DECL|member|msgmni
r_int
id|msgmni
suffix:semicolon
DECL|member|msgssz
r_int
id|msgssz
suffix:semicolon
DECL|member|msgtql
r_int
id|msgtql
suffix:semicolon
DECL|member|msgseg
r_int
r_int
id|msgseg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MSGMNI
mdefine_line|#define MSGMNI    16   /* &lt;= IPCMNI */     /* max # of msg queue identifiers */
DECL|macro|MSGMAX
mdefine_line|#define MSGMAX  8192   /* &lt;= INT_MAX */   /* max size of message (bytes) */
DECL|macro|MSGMNB
mdefine_line|#define MSGMNB 16384   /* &lt;= INT_MAX */   /* default max size of a message queue */
multiline_comment|/* unused */
DECL|macro|MSGPOOL
mdefine_line|#define MSGPOOL (MSGMNI*MSGMNB/1024)  /* size in kilobytes of message pool */
DECL|macro|MSGTQL
mdefine_line|#define MSGTQL  MSGMNB            /* number of system message headers */
DECL|macro|MSGMAP
mdefine_line|#define MSGMAP  MSGMNB            /* number of entries in message map */
DECL|macro|MSGSSZ
mdefine_line|#define MSGSSZ  16                /* message segment size */
DECL|macro|__MSGSEG
mdefine_line|#define __MSGSEG ((MSGPOOL*1024)/ MSGSSZ) /* max no. of segments */
DECL|macro|MSGSEG
mdefine_line|#define MSGSEG (__MSGSEG &lt;= 0xffff ? __MSGSEG : 0xffff)
macro_line|#ifdef __KERNEL__
multiline_comment|/* one msg_msg structure for each message */
DECL|struct|msg_msg
r_struct
id|msg_msg
(brace
DECL|member|m_list
r_struct
id|list_head
id|m_list
suffix:semicolon
DECL|member|m_type
r_int
id|m_type
suffix:semicolon
DECL|member|m_ts
r_int
id|m_ts
suffix:semicolon
multiline_comment|/* message text size */
DECL|member|next
r_struct
id|msg_msgseg
op_star
id|next
suffix:semicolon
DECL|member|security
r_void
op_star
id|security
suffix:semicolon
multiline_comment|/* the actual message follows immediately */
)brace
suffix:semicolon
multiline_comment|/* one msq_queue structure for each present queue on the system */
DECL|struct|msg_queue
r_struct
id|msg_queue
(brace
DECL|member|q_perm
r_struct
id|kern_ipc_perm
id|q_perm
suffix:semicolon
DECL|member|q_stime
id|time_t
id|q_stime
suffix:semicolon
multiline_comment|/* last msgsnd time */
DECL|member|q_rtime
id|time_t
id|q_rtime
suffix:semicolon
multiline_comment|/* last msgrcv time */
DECL|member|q_ctime
id|time_t
id|q_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|q_cbytes
r_int
r_int
id|q_cbytes
suffix:semicolon
multiline_comment|/* current number of bytes on queue */
DECL|member|q_qnum
r_int
r_int
id|q_qnum
suffix:semicolon
multiline_comment|/* number of messages in queue */
DECL|member|q_qbytes
r_int
r_int
id|q_qbytes
suffix:semicolon
multiline_comment|/* max number of bytes on queue */
DECL|member|q_lspid
id|pid_t
id|q_lspid
suffix:semicolon
multiline_comment|/* pid of last msgsnd */
DECL|member|q_lrpid
id|pid_t
id|q_lrpid
suffix:semicolon
multiline_comment|/* last receive pid */
DECL|member|q_messages
r_struct
id|list_head
id|q_messages
suffix:semicolon
DECL|member|q_receivers
r_struct
id|list_head
id|q_receivers
suffix:semicolon
DECL|member|q_senders
r_struct
id|list_head
id|q_senders
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_MSG_H */
eof
