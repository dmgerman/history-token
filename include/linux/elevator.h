macro_line|#ifndef _LINUX_ELEVATOR_H
DECL|macro|_LINUX_ELEVATOR_H
mdefine_line|#define _LINUX_ELEVATOR_H
DECL|typedef|elevator_fn
r_typedef
r_void
(paren
id|elevator_fn
)paren
(paren
r_struct
id|request
op_star
comma
id|elevator_t
op_star
comma
r_struct
id|list_head
op_star
comma
r_struct
id|list_head
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|elevator_merge_fn
r_typedef
r_int
(paren
id|elevator_merge_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
op_star
comma
r_struct
id|list_head
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_merge_cleanup_fn
r_typedef
r_void
(paren
id|elevator_merge_cleanup_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|elevator_merge_req_fn
r_typedef
r_void
(paren
id|elevator_merge_req_fn
)paren
(paren
r_struct
id|request
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_next_req_fn
r_typedef
r_struct
id|request
op_star
(paren
id|elevator_next_req_fn
)paren
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_add_req_fn
r_typedef
r_void
(paren
id|elevator_add_req_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_struct
id|list_head
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_init_fn
r_typedef
r_int
(paren
id|elevator_init_fn
)paren
(paren
id|request_queue_t
op_star
comma
id|elevator_t
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_exit_fn
r_typedef
r_void
(paren
id|elevator_exit_fn
)paren
(paren
id|request_queue_t
op_star
comma
id|elevator_t
op_star
)paren
suffix:semicolon
DECL|struct|elevator_s
r_struct
id|elevator_s
(brace
DECL|member|read_latency
r_int
id|read_latency
suffix:semicolon
DECL|member|write_latency
r_int
id|write_latency
suffix:semicolon
DECL|member|elevator_merge_fn
id|elevator_merge_fn
op_star
id|elevator_merge_fn
suffix:semicolon
DECL|member|elevator_merge_cleanup_fn
id|elevator_merge_cleanup_fn
op_star
id|elevator_merge_cleanup_fn
suffix:semicolon
DECL|member|elevator_merge_req_fn
id|elevator_merge_req_fn
op_star
id|elevator_merge_req_fn
suffix:semicolon
DECL|member|elevator_next_req_fn
id|elevator_next_req_fn
op_star
id|elevator_next_req_fn
suffix:semicolon
DECL|member|elevator_add_req_fn
id|elevator_add_req_fn
op_star
id|elevator_add_req_fn
suffix:semicolon
DECL|member|elevator_init_fn
id|elevator_init_fn
op_star
id|elevator_init_fn
suffix:semicolon
DECL|member|elevator_exit_fn
id|elevator_exit_fn
op_star
id|elevator_exit_fn
suffix:semicolon
multiline_comment|/*&n;&t; * per-elevator private data&n;&t; */
DECL|member|elevator_data
r_void
op_star
id|elevator_data
suffix:semicolon
DECL|member|queue_name
r_char
id|queue_name
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
r_int
id|elevator_noop_merge
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
op_star
comma
r_struct
id|list_head
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_void
id|elevator_noop_merge_cleanup
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|elevator_noop_merge_req
c_func
(paren
r_struct
id|request
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_int
id|elevator_linus_merge
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
op_star
comma
r_struct
id|list_head
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_void
id|elevator_linus_merge_cleanup
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|elevator_linus_merge_req
c_func
(paren
r_struct
id|request
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_int
id|elv_linus_init
c_func
(paren
id|request_queue_t
op_star
comma
id|elevator_t
op_star
)paren
suffix:semicolon
r_void
id|elv_linus_exit
c_func
(paren
id|request_queue_t
op_star
comma
id|elevator_t
op_star
)paren
suffix:semicolon
r_struct
id|request
op_star
id|elv_next_request_fn
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_void
id|elv_add_request_fn
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_struct
id|list_head
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * use the /proc/iosched interface, all the below is history -&gt;&n; */
DECL|struct|blkelv_ioctl_arg_s
r_typedef
r_struct
id|blkelv_ioctl_arg_s
(brace
DECL|member|queue_ID
r_int
id|queue_ID
suffix:semicolon
DECL|member|read_latency
r_int
id|read_latency
suffix:semicolon
DECL|member|write_latency
r_int
id|write_latency
suffix:semicolon
DECL|member|max_bomb_segments
r_int
id|max_bomb_segments
suffix:semicolon
DECL|typedef|blkelv_ioctl_arg_t
)brace
id|blkelv_ioctl_arg_t
suffix:semicolon
DECL|macro|BLKELVGET
mdefine_line|#define BLKELVGET   _IOR(0x12,106,sizeof(blkelv_ioctl_arg_t))
DECL|macro|BLKELVSET
mdefine_line|#define BLKELVSET   _IOW(0x12,107,sizeof(blkelv_ioctl_arg_t))
r_extern
r_int
id|elevator_init
c_func
(paren
id|request_queue_t
op_star
comma
id|elevator_t
op_star
comma
id|elevator_t
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|elevator_exit
c_func
(paren
id|request_queue_t
op_star
comma
id|elevator_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Return values from elevator merger&n; */
DECL|macro|ELEVATOR_NO_MERGE
mdefine_line|#define ELEVATOR_NO_MERGE&t;0
DECL|macro|ELEVATOR_FRONT_MERGE
mdefine_line|#define ELEVATOR_FRONT_MERGE&t;1
DECL|macro|ELEVATOR_BACK_MERGE
mdefine_line|#define ELEVATOR_BACK_MERGE&t;2
multiline_comment|/*&n; * This is used in the elevator algorithm.  We don&squot;t prioritise reads&n; * over writes any more --- although reads are more time-critical than&n; * writes, by treating them equally we increase filesystem throughput.&n; * This turns out to give better overall performance.  -- sct&n; */
DECL|macro|IN_ORDER
mdefine_line|#define IN_ORDER(s1,s2)&t;&t;&t;&t;&bslash;&n;&t;((((s1)-&gt;rq_dev == (s2)-&gt;rq_dev &amp;&amp;&t;&bslash;&n;&t;   (s1)-&gt;sector &lt; (s2)-&gt;sector)) ||&t;&bslash;&n;&t; (s1)-&gt;rq_dev &lt; (s2)-&gt;rq_dev)
DECL|macro|BHRQ_IN_ORDER
mdefine_line|#define BHRQ_IN_ORDER(bh, rq)&t;&t;&t;&bslash;&n;&t;((((bh)-&gt;b_rdev == (rq)-&gt;rq_dev &amp;&amp;&t;&bslash;&n;&t;   (bh)-&gt;b_rsector &lt; (rq)-&gt;sector)) ||&t;&bslash;&n;&t; (bh)-&gt;b_rdev &lt; (rq)-&gt;rq_dev)
DECL|function|elevator_request_latency
r_static
r_inline
r_int
id|elevator_request_latency
c_func
(paren
id|elevator_t
op_star
id|elevator
comma
r_int
id|rw
)paren
(brace
r_int
id|latency
suffix:semicolon
id|latency
op_assign
id|elevator-&gt;read_latency
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_ne
id|READ
)paren
id|latency
op_assign
id|elevator-&gt;write_latency
suffix:semicolon
r_return
id|latency
suffix:semicolon
)brace
multiline_comment|/*&n; * will change once we move to a more complex data structure than a simple&n; * list for pending requests&n; */
DECL|macro|elv_queue_empty
mdefine_line|#define elv_queue_empty(q)&t;list_empty(&amp;(q)-&gt;queue_head)
multiline_comment|/*&n; * elevator private data&n; */
DECL|struct|elv_linus_data
r_struct
id|elv_linus_data
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ELV_DAT
mdefine_line|#define ELV_DAT(e) ((struct elv_linus_data *)(e)-&gt;elevator_data)
DECL|macro|ELV_LINUS_BACK_MERGE
mdefine_line|#define ELV_LINUS_BACK_MERGE&t;1
DECL|macro|ELV_LINUS_FRONT_MERGE
mdefine_line|#define ELV_LINUS_FRONT_MERGE&t;2
DECL|macro|ELEVATOR_NOOP
mdefine_line|#define ELEVATOR_NOOP&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((elevator_t) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;/* read_latency */&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;/* write_latency */&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elevator_noop_merge,&t;&t;/* elevator_merge_fn */&t;&t;&bslash;&n;&t;elevator_noop_merge_cleanup,&t;/* elevator_merge_cleanup_fn */&t;&bslash;&n;&t;elevator_noop_merge_req,&t;/* elevator_merge_req_fn */&t;&bslash;&n;&t;elv_next_request_fn,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elv_add_request_fn,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elv_linus_init,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elv_linus_exit,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ELEVATOR_LINUS
mdefine_line|#define ELEVATOR_LINUS&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((elevator_t) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;8192,&t;&t;&t;&t;/* read passovers */&t;&t;&bslash;&n;&t;16384,&t;&t;&t;&t;/* write passovers */&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elevator_linus_merge,&t;&t;/* elevator_merge_fn */&t;&t;&bslash;&n;&t;elevator_linus_merge_cleanup,&t;/* elevator_merge_cleanup_fn */&t;&bslash;&n;&t;elevator_linus_merge_req,&t;/* elevator_merge_req_fn */&t;&bslash;&n;&t;elv_next_request_fn,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elv_add_request_fn,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elv_linus_init,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;elv_linus_exit,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#endif
eof
