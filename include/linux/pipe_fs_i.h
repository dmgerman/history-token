macro_line|#ifndef _LINUX_PIPE_FS_I_H
DECL|macro|_LINUX_PIPE_FS_I_H
mdefine_line|#define _LINUX_PIPE_FS_I_H
DECL|macro|PIPEFS_MAGIC
mdefine_line|#define PIPEFS_MAGIC 0x50495045
DECL|macro|PIPE_BUFFERS
mdefine_line|#define PIPE_BUFFERS (16)
DECL|struct|pipe_buffer
r_struct
id|pipe_buffer
(brace
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|offset
DECL|member|len
r_int
r_int
id|offset
comma
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pipe_inode_info
r_struct
id|pipe_inode_info
(brace
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|nrbufs
DECL|member|curbuf
r_int
r_int
id|nrbufs
comma
id|curbuf
suffix:semicolon
DECL|member|bufs
r_struct
id|pipe_buffer
id|bufs
(braket
id|PIPE_BUFFERS
)braket
suffix:semicolon
DECL|member|tmp_page
r_struct
id|page
op_star
id|tmp_page
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|readers
r_int
r_int
id|readers
suffix:semicolon
DECL|member|writers
r_int
r_int
id|writers
suffix:semicolon
DECL|member|waiting_writers
r_int
r_int
id|waiting_writers
suffix:semicolon
DECL|member|r_counter
r_int
r_int
id|r_counter
suffix:semicolon
DECL|member|w_counter
r_int
r_int
id|w_counter
suffix:semicolon
DECL|member|fasync_readers
r_struct
id|fasync_struct
op_star
id|fasync_readers
suffix:semicolon
DECL|member|fasync_writers
r_struct
id|fasync_struct
op_star
id|fasync_writers
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Differs from PIPE_BUF in that PIPE_SIZE is the length of the actual&n;   memory allocation, whereas PIPE_BUF makes atomicity guarantees.  */
DECL|macro|PIPE_SIZE
mdefine_line|#define PIPE_SIZE&t;&t;PAGE_SIZE
DECL|macro|PIPE_SEM
mdefine_line|#define PIPE_SEM(inode)&t;&t;(&amp;(inode).i_sem)
DECL|macro|PIPE_WAIT
mdefine_line|#define PIPE_WAIT(inode)&t;(&amp;(inode).i_pipe-&gt;wait)
DECL|macro|PIPE_BASE
mdefine_line|#define PIPE_BASE(inode)&t;((inode).i_pipe-&gt;base)
DECL|macro|PIPE_START
mdefine_line|#define PIPE_START(inode)&t;((inode).i_pipe-&gt;start)
DECL|macro|PIPE_LEN
mdefine_line|#define PIPE_LEN(inode)&t;&t;((inode).i_pipe-&gt;len)
DECL|macro|PIPE_READERS
mdefine_line|#define PIPE_READERS(inode)&t;((inode).i_pipe-&gt;readers)
DECL|macro|PIPE_WRITERS
mdefine_line|#define PIPE_WRITERS(inode)&t;((inode).i_pipe-&gt;writers)
DECL|macro|PIPE_WAITING_WRITERS
mdefine_line|#define PIPE_WAITING_WRITERS(inode)&t;((inode).i_pipe-&gt;waiting_writers)
DECL|macro|PIPE_RCOUNTER
mdefine_line|#define PIPE_RCOUNTER(inode)&t;((inode).i_pipe-&gt;r_counter)
DECL|macro|PIPE_WCOUNTER
mdefine_line|#define PIPE_WCOUNTER(inode)&t;((inode).i_pipe-&gt;w_counter)
DECL|macro|PIPE_FASYNC_READERS
mdefine_line|#define PIPE_FASYNC_READERS(inode)     (&amp;((inode).i_pipe-&gt;fasync_readers))
DECL|macro|PIPE_FASYNC_WRITERS
mdefine_line|#define PIPE_FASYNC_WRITERS(inode)     (&amp;((inode).i_pipe-&gt;fasync_writers))
multiline_comment|/* Drop the inode semaphore and wait for a pipe event, atomically */
r_void
id|pipe_wait
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|pipe_new
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|free_pipe_info
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
macro_line|#endif
eof
