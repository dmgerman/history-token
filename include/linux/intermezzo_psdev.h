macro_line|#ifndef __PRESTO_PSDEV_H
DECL|macro|__PRESTO_PSDEV_H
mdefine_line|#define __PRESTO_PSDEV_H
macro_line|#ifdef PRESTO_DEVEL
DECL|macro|PRESTO_FS_NAME
macro_line|# define PRESTO_FS_NAME &quot;izofs&quot;
DECL|macro|PRESTO_PSDEV_NAME
macro_line|# define PRESTO_PSDEV_NAME &quot;/dev/izo&quot;
DECL|macro|PRESTO_PSDEV_MAJOR
macro_line|# define PRESTO_PSDEV_MAJOR 186
macro_line|#else
DECL|macro|PRESTO_FS_NAME
macro_line|# define PRESTO_FS_NAME &quot;InterMezzo&quot;
DECL|macro|PRESTO_PSDEV_NAME
macro_line|# define PRESTO_PSDEV_NAME &quot;/dev/intermezzo&quot;
DECL|macro|PRESTO_PSDEV_MAJOR
macro_line|# define PRESTO_PSDEV_MAJOR 185
macro_line|#endif
DECL|macro|MAX_PRESTODEV
mdefine_line|#define MAX_PRESTODEV 16
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
DECL|macro|wait_queue_head_t
mdefine_line|#define wait_queue_head_t  struct wait_queue *
DECL|macro|DECLARE_WAITQUEUE
mdefine_line|#define DECLARE_WAITQUEUE(name,task) &bslash;&n;        struct wait_queue name = { task, NULL }
DECL|macro|init_waitqueue_head
mdefine_line|#define init_waitqueue_head(arg) 
macro_line|#else
macro_line|#ifndef __initfunc
DECL|macro|__initfunc
mdefine_line|#define __initfunc(arg) arg
macro_line|#endif
macro_line|#endif
multiline_comment|/* represents state of a /dev/presto */
multiline_comment|/* communication pending &amp; processing queues */
DECL|struct|upc_comm
r_struct
id|upc_comm
(brace
DECL|member|uc_seq
r_int
r_int
id|uc_seq
suffix:semicolon
DECL|member|uc_waitq
id|wait_queue_head_t
id|uc_waitq
suffix:semicolon
multiline_comment|/* Lento wait queue */
DECL|member|uc_pending
r_struct
id|list_head
id|uc_pending
suffix:semicolon
DECL|member|uc_processing
r_struct
id|list_head
id|uc_processing
suffix:semicolon
DECL|member|uc_pid
r_int
id|uc_pid
suffix:semicolon
multiline_comment|/* Lento&squot;s pid */
DECL|member|uc_hard
r_int
id|uc_hard
suffix:semicolon
multiline_comment|/* allows signals during upcalls */
DECL|member|uc_no_filter
r_int
id|uc_no_filter
suffix:semicolon
DECL|member|uc_no_journal
r_int
id|uc_no_journal
suffix:semicolon
DECL|member|uc_no_upcall
r_int
id|uc_no_upcall
suffix:semicolon
DECL|member|uc_timeout
r_int
id|uc_timeout
suffix:semicolon
multiline_comment|/* . sec: signals will dequeue upc */
DECL|member|uc_errorval
r_int
id|uc_errorval
suffix:semicolon
multiline_comment|/* for testing I/O failures */
DECL|member|uc_cache_list
r_struct
id|list_head
id|uc_cache_list
suffix:semicolon
DECL|member|uc_minor
r_int
id|uc_minor
suffix:semicolon
DECL|member|uc_devname
r_char
op_star
id|uc_devname
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISLENTO
mdefine_line|#define ISLENTO(minor) (current-&gt;pid == upc_comms[minor].uc_pid &bslash;&n;                || current-&gt;parent-&gt;pid == upc_comms[minor].uc_pid)
r_extern
r_struct
id|upc_comm
id|upc_comms
(braket
id|MAX_PRESTODEV
)braket
suffix:semicolon
multiline_comment|/* messages between presto filesystem in kernel and Venus */
DECL|macro|REQ_READ
mdefine_line|#define REQ_READ   1
DECL|macro|REQ_WRITE
mdefine_line|#define REQ_WRITE  2
DECL|macro|REQ_ASYNC
mdefine_line|#define REQ_ASYNC  4
DECL|macro|REQ_DEAD
mdefine_line|#define REQ_DEAD   8
DECL|struct|upc_req
r_struct
id|upc_req
(brace
DECL|member|rq_chain
r_struct
id|list_head
id|rq_chain
suffix:semicolon
DECL|member|rq_data
id|caddr_t
id|rq_data
suffix:semicolon
DECL|member|rq_flags
id|u_short
id|rq_flags
suffix:semicolon
DECL|member|rq_bufsize
id|u_short
id|rq_bufsize
suffix:semicolon
DECL|member|rq_rep_size
id|u_short
id|rq_rep_size
suffix:semicolon
DECL|member|rq_opcode
id|u_short
id|rq_opcode
suffix:semicolon
multiline_comment|/* copied from data to save lookup */
DECL|member|rq_unique
r_int
id|rq_unique
suffix:semicolon
DECL|member|rq_sleep
id|wait_queue_head_t
id|rq_sleep
suffix:semicolon
multiline_comment|/* process&squot; wait queue */
DECL|member|rq_posttime
r_int
r_int
id|rq_posttime
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
