multiline_comment|/*&n; * memory buffer pool support&n; */
macro_line|#ifndef _LINUX_MEMPOOL_H
DECL|macro|_LINUX_MEMPOOL_H
mdefine_line|#define _LINUX_MEMPOOL_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
r_struct
id|mempool_s
suffix:semicolon
DECL|typedef|mempool_t
r_typedef
r_struct
id|mempool_s
id|mempool_t
suffix:semicolon
DECL|typedef|mempool_alloc_t
r_typedef
r_void
op_star
(paren
id|mempool_alloc_t
)paren
(paren
r_int
id|gfp_mask
comma
r_void
op_star
id|pool_data
)paren
suffix:semicolon
DECL|typedef|mempool_free_t
r_typedef
r_void
(paren
id|mempool_free_t
)paren
(paren
r_void
op_star
id|element
comma
r_void
op_star
id|pool_data
)paren
suffix:semicolon
DECL|struct|mempool_s
r_struct
id|mempool_s
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|min_nr
DECL|member|curr_nr
r_int
id|min_nr
comma
id|curr_nr
suffix:semicolon
DECL|member|elements
r_struct
id|list_head
id|elements
suffix:semicolon
DECL|member|pool_data
r_void
op_star
id|pool_data
suffix:semicolon
DECL|member|alloc
id|mempool_alloc_t
op_star
id|alloc
suffix:semicolon
DECL|member|free
id|mempool_free_t
op_star
id|free
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|mempool_t
op_star
id|mempool_create
c_func
(paren
r_int
id|min_nr
comma
id|mempool_alloc_t
op_star
id|alloc_fn
comma
id|mempool_free_t
op_star
id|free_fn
comma
r_void
op_star
id|pool_data
)paren
suffix:semicolon
r_extern
r_void
id|mempool_destroy
c_func
(paren
id|mempool_t
op_star
id|pool
)paren
suffix:semicolon
r_extern
r_void
op_star
id|mempool_alloc
c_func
(paren
id|mempool_t
op_star
id|pool
comma
r_int
id|gfp_mask
)paren
suffix:semicolon
r_extern
r_void
id|mempool_free
c_func
(paren
r_void
op_star
id|element
comma
id|mempool_t
op_star
id|pool
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_MEMPOOL_H */
eof
