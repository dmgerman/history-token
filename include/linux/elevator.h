macro_line|#ifndef _LINUX_ELEVATOR_H
DECL|macro|_LINUX_ELEVATOR_H
mdefine_line|#define _LINUX_ELEVATOR_H
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
id|bio
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_merge_req_fn
r_typedef
r_void
(paren
id|elevator_merge_req_fn
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
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_merged_fn
r_typedef
r_void
(paren
id|elevator_merged_fn
)paren
(paren
id|request_queue_t
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
r_int
)paren
suffix:semicolon
DECL|typedef|elevator_queue_empty_fn
r_typedef
r_int
(paren
id|elevator_queue_empty_fn
)paren
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_remove_req_fn
r_typedef
r_void
(paren
id|elevator_remove_req_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_requeue_req_fn
r_typedef
r_void
(paren
id|elevator_requeue_req_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_request_list_fn
r_typedef
r_struct
id|request
op_star
(paren
id|elevator_request_list_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_completed_req_fn
r_typedef
r_void
(paren
id|elevator_completed_req_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|elevator_may_queue_fn
r_typedef
r_int
(paren
id|elevator_may_queue_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|elevator_set_req_fn
r_typedef
r_int
(paren
id|elevator_set_req_fn
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
DECL|typedef|elevator_put_req_fn
r_typedef
r_void
(paren
id|elevator_put_req_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
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
id|elevator_t
op_star
)paren
suffix:semicolon
DECL|struct|elevator_ops
r_struct
id|elevator_ops
(brace
DECL|member|elevator_merge_fn
id|elevator_merge_fn
op_star
id|elevator_merge_fn
suffix:semicolon
DECL|member|elevator_merged_fn
id|elevator_merged_fn
op_star
id|elevator_merged_fn
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
DECL|member|elevator_remove_req_fn
id|elevator_remove_req_fn
op_star
id|elevator_remove_req_fn
suffix:semicolon
DECL|member|elevator_requeue_req_fn
id|elevator_requeue_req_fn
op_star
id|elevator_requeue_req_fn
suffix:semicolon
DECL|member|elevator_queue_empty_fn
id|elevator_queue_empty_fn
op_star
id|elevator_queue_empty_fn
suffix:semicolon
DECL|member|elevator_completed_req_fn
id|elevator_completed_req_fn
op_star
id|elevator_completed_req_fn
suffix:semicolon
DECL|member|elevator_former_req_fn
id|elevator_request_list_fn
op_star
id|elevator_former_req_fn
suffix:semicolon
DECL|member|elevator_latter_req_fn
id|elevator_request_list_fn
op_star
id|elevator_latter_req_fn
suffix:semicolon
DECL|member|elevator_set_req_fn
id|elevator_set_req_fn
op_star
id|elevator_set_req_fn
suffix:semicolon
DECL|member|elevator_put_req_fn
id|elevator_put_req_fn
op_star
id|elevator_put_req_fn
suffix:semicolon
DECL|member|elevator_may_queue_fn
id|elevator_may_queue_fn
op_star
id|elevator_may_queue_fn
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
)brace
suffix:semicolon
DECL|macro|ELV_NAME_MAX
mdefine_line|#define ELV_NAME_MAX&t;(16)
multiline_comment|/*&n; * identifies an elevator type, such as AS or deadline&n; */
DECL|struct|elevator_type
r_struct
id|elevator_type
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|ops
r_struct
id|elevator_ops
id|ops
suffix:semicolon
DECL|member|elevator_type
r_struct
id|elevator_type
op_star
id|elevator_type
suffix:semicolon
DECL|member|elevator_ktype
r_struct
id|kobj_type
op_star
id|elevator_ktype
suffix:semicolon
DECL|member|elevator_name
r_char
id|elevator_name
(braket
id|ELV_NAME_MAX
)braket
suffix:semicolon
DECL|member|elevator_owner
r_struct
id|module
op_star
id|elevator_owner
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * each queue has an elevator_queue assoicated with it&n; */
DECL|struct|elevator_queue
r_struct
id|elevator_queue
(brace
DECL|member|ops
r_struct
id|elevator_ops
op_star
id|ops
suffix:semicolon
DECL|member|elevator_data
r_void
op_star
id|elevator_data
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
DECL|member|elevator_type
r_struct
id|elevator_type
op_star
id|elevator_type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * block elevator interface&n; */
r_extern
r_void
id|elv_add_request
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__elv_add_request
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|elv_merge
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
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_void
id|elv_merge_requests
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
id|request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|elv_merged_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|elv_remove_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|elv_requeue_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elv_queue_empty
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|request
op_star
id|elv_next_request
c_func
(paren
r_struct
id|request_queue
op_star
id|q
)paren
suffix:semicolon
r_extern
r_struct
id|request
op_star
id|elv_former_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|request
op_star
id|elv_latter_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elv_register_queue
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_extern
r_void
id|elv_unregister_queue
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_extern
r_int
id|elv_may_queue
c_func
(paren
id|request_queue_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|elv_completed_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elv_set_request
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
r_extern
r_void
id|elv_put_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * io scheduler registration&n; */
r_extern
r_int
id|elv_register
c_func
(paren
r_struct
id|elevator_type
op_star
)paren
suffix:semicolon
r_extern
r_void
id|elv_unregister
c_func
(paren
r_struct
id|elevator_type
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * io scheduler sysfs switching&n; */
r_extern
id|ssize_t
id|elv_iosched_show
c_func
(paren
id|request_queue_t
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
id|ssize_t
id|elv_iosched_store
c_func
(paren
id|request_queue_t
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|elevator_init
c_func
(paren
id|request_queue_t
op_star
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
id|elevator_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elv_rq_merge_ok
c_func
(paren
r_struct
id|request
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elv_try_merge
c_func
(paren
r_struct
id|request
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elv_try_last_merge
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|bio
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
multiline_comment|/*&n; * Insertion selection&n; */
DECL|macro|ELEVATOR_INSERT_FRONT
mdefine_line|#define ELEVATOR_INSERT_FRONT&t;1
DECL|macro|ELEVATOR_INSERT_BACK
mdefine_line|#define ELEVATOR_INSERT_BACK&t;2
DECL|macro|ELEVATOR_INSERT_SORT
mdefine_line|#define ELEVATOR_INSERT_SORT&t;3
multiline_comment|/*&n; * return values from elevator_may_queue_fn&n; */
r_enum
(brace
DECL|enumerator|ELV_MQUEUE_MAY
id|ELV_MQUEUE_MAY
comma
DECL|enumerator|ELV_MQUEUE_NO
id|ELV_MQUEUE_NO
comma
DECL|enumerator|ELV_MQUEUE_MUST
id|ELV_MQUEUE_MUST
comma
)brace
suffix:semicolon
macro_line|#endif
eof
