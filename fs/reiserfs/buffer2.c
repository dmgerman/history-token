multiline_comment|/*&n; *  Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README  &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
multiline_comment|/*&n; *  wait_buffer_until_released&n; *  reiserfs_bread&n; */
multiline_comment|/* when we allocate a new block (get_new_buffer, get_empty_nodes) and&n;   get buffer for it, it is possible that it is held by someone else&n;   or even by this process. In this function we wait until all other&n;   holders release buffer. To make sure, that current process does not&n;   hold we did free all buffers in tree balance structure&n;   (get_empty_nodes and get_nodes_for_preserving) or in path structure&n;   only (get_new_buffer) just before calling this */
DECL|function|wait_buffer_until_released
r_void
id|wait_buffer_until_released
(paren
r_const
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|repeat_counter
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
(paren
op_amp
(paren
id|bh-&gt;b_count
)paren
)paren
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_increment
id|repeat_counter
op_mod
l_int|30000000
)paren
)paren
(brace
id|reiserfs_warning
(paren
l_string|&quot;vs-3050: wait_buffer_until_released: nobody releases buffer (%b). Still waiting (%d) %cJDIRTY %cJWAIT&bslash;n&quot;
comma
id|bh
comma
id|repeat_counter
comma
id|buffer_journaled
c_func
(paren
id|bh
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;!&squot;
comma
id|buffer_journal_dirty
c_func
(paren
id|bh
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;!&squot;
)paren
suffix:semicolon
)brace
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
id|yield
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|repeat_counter
OG
l_int|30000000
)paren
(brace
id|reiserfs_warning
c_func
(paren
l_string|&quot;vs-3051: done waiting, ignore vs-3050 messages for (%b)&bslash;n&quot;
comma
id|bh
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * reiserfs_bread() reads a specified block and returns the buffer that contains&n; * it. It returns NULL if the block was unreadable.&n; */
multiline_comment|/* It first tries to find the block in cache, and if it cannot do so&n;   then it creates a new buffer and schedules I/O to read the&n;   block. */
multiline_comment|/* The function is NOT SCHEDULE-SAFE! */
DECL|function|reiserfs_bread
r_struct
id|buffer_head
op_star
id|reiserfs_bread
(paren
r_struct
id|super_block
op_star
id|super
comma
r_int
id|n_block
)paren
(brace
r_struct
id|buffer_head
op_star
id|result
suffix:semicolon
id|PROC_EXP
c_func
(paren
r_int
r_int
id|ctx_switches
op_assign
id|nr_context_switches
c_func
(paren
)paren
)paren
suffix:semicolon
id|result
op_assign
id|sb_bread
c_func
(paren
id|super
comma
id|n_block
)paren
suffix:semicolon
id|PROC_INFO_INC
c_func
(paren
id|super
comma
id|breads
)paren
suffix:semicolon
id|PROC_EXP
c_func
(paren
r_if
(paren
id|nr_context_switches
c_func
(paren
)paren
op_ne
id|ctx_switches
)paren
id|PROC_INFO_INC
c_func
(paren
id|super
comma
id|bread_miss
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof
