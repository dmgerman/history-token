multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; */
macro_line|#ifndef __PRESTO_PSDEV_H
DECL|macro|__PRESTO_PSDEV_H
mdefine_line|#define __PRESTO_PSDEV_H
DECL|macro|MAX_CHANNEL
mdefine_line|#define MAX_CHANNEL 16
DECL|macro|PROCNAME_SIZE
mdefine_line|#define PROCNAME_SIZE 32
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/version.h&gt;
multiline_comment|/* represents state of an instance reached with /dev/intermezzo */
multiline_comment|/* communication pending &amp; processing queues */
DECL|struct|upc_channel
r_struct
id|upc_channel
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
DECL|member|uc_lock
id|spinlock_t
id|uc_lock
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
)brace
suffix:semicolon
DECL|macro|ISLENTO
mdefine_line|#define ISLENTO(minor) (current-&gt;pid == izo_channels[minor].uc_pid &bslash;&n;                || current-&gt;real_parent-&gt;pid == izo_channels[minor].uc_pid &bslash;&n;                || current-&gt;real_parent-&gt;real_parent-&gt;pid == izo_channels[minor].uc_pid)
r_extern
r_struct
id|upc_channel
id|izo_channels
(braket
id|MAX_CHANNEL
)braket
suffix:semicolon
multiline_comment|/* message types between presto filesystem in kernel */
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
r_int
id|rq_flags
suffix:semicolon
DECL|member|rq_bufsize
r_int
id|rq_bufsize
suffix:semicolon
DECL|member|rq_rep_size
r_int
id|rq_rep_size
suffix:semicolon
DECL|member|rq_opcode
r_int
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
