multiline_comment|/*&n; *  linux/drivers/mmc/mmc_queue.c&n; *&n; *  Copyright (C) 2003 Russell King, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/mmc/card.h&gt;
macro_line|#include &lt;linux/mmc/host.h&gt;
macro_line|#include &quot;mmc_queue.h&quot;
multiline_comment|/*&n; * Prepare a MMC request.  Essentially, this means passing the&n; * preparation off to the media driver.  The media driver will&n; * create a mmc_io_request in req-&gt;special.&n; */
DECL|function|mmc_prep_request
r_static
r_int
id|mmc_prep_request
c_func
(paren
r_struct
id|request_queue
op_star
id|q
comma
r_struct
id|request
op_star
id|req
)paren
(brace
r_struct
id|mmc_queue
op_star
id|mq
op_assign
id|q-&gt;queuedata
suffix:semicolon
r_int
id|ret
op_assign
id|BLKPREP_KILL
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;flags
op_amp
id|REQ_SPECIAL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Special commands already have the command&n;&t;&t; * blocks already setup in req-&gt;special.&n;&t;&t; */
id|BUG_ON
c_func
(paren
op_logical_neg
id|req-&gt;special
)paren
suffix:semicolon
id|ret
op_assign
id|BLKPREP_OK
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|req-&gt;flags
op_amp
(paren
id|REQ_CMD
op_or
id|REQ_BLOCK_PC
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Block I/O requests need translating according&n;&t;&t; * to the protocol.&n;&t;&t; */
id|ret
op_assign
id|mq
op_member_access_from_pointer
id|prep_fn
c_func
(paren
id|mq
comma
id|req
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Everything else is invalid.&n;&t;&t; */
id|blk_dump_rq_flags
c_func
(paren
id|req
comma
l_string|&quot;MMC bad request&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_eq
id|BLKPREP_OK
)paren
id|req-&gt;flags
op_or_assign
id|REQ_DONTPREP
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mmc_queue_thread
r_static
r_int
id|mmc_queue_thread
c_func
(paren
r_void
op_star
id|d
)paren
(brace
r_struct
id|mmc_queue
op_star
id|mq
op_assign
id|d
suffix:semicolon
r_struct
id|request_queue
op_star
id|q
op_assign
id|mq-&gt;queue
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Set iothread to ensure that we aren&squot;t put to sleep by&n;&t; * the process freezing.  We handle suspension ourselves.&n;&t; */
id|current-&gt;flags
op_or_assign
id|PF_MEMALLOC
op_or
id|PF_NOFREEZE
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;mmcqd&quot;
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|mq-&gt;thread
op_assign
id|current
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|mq-&gt;thread_complete
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|mq-&gt;thread_wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
r_do
(brace
r_struct
id|request
op_star
id|req
op_assign
l_int|NULL
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blk_queue_plugged
c_func
(paren
id|q
)paren
)paren
id|mq-&gt;req
op_assign
id|req
op_assign
id|elv_next_request
c_func
(paren
id|q
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mq-&gt;thread
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|ret
op_assign
id|mq
op_member_access_from_pointer
id|issue_fn
c_func
(paren
id|mq
comma
id|req
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
id|end_request
c_func
(paren
id|req
comma
id|ret
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|mq-&gt;thread_wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|complete_and_exit
c_func
(paren
op_amp
id|mq-&gt;thread_complete
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic MMC request handler.  This is called for any queue on a&n; * particular host.  When the host is not busy, we look for a request&n; * on any queue on this host, and attempt to issue it.  This may&n; * not be the queue we were asked to process.&n; */
DECL|function|mmc_request
r_static
r_void
id|mmc_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|mmc_queue
op_star
id|mq
op_assign
id|q-&gt;queuedata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mq-&gt;req
op_logical_and
op_logical_neg
id|blk_queue_plugged
c_func
(paren
id|q
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|mq-&gt;thread_wq
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * mmc_init_queue - initialise a queue structure.&n; * @mq: mmc queue&n; * @card: mmc card to attach this queue&n; * @lock: queue lock&n; *&n; * Initialise a MMC card request queue.&n; */
DECL|function|mmc_init_queue
r_int
id|mmc_init_queue
c_func
(paren
r_struct
id|mmc_queue
op_star
id|mq
comma
r_struct
id|mmc_card
op_star
id|card
comma
id|spinlock_t
op_star
id|lock
)paren
(brace
id|u64
id|limit
op_assign
id|BLK_BOUNCE_HIGH
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;host-&gt;dev-&gt;dma_mask
)paren
id|limit
op_assign
op_star
id|card-&gt;host-&gt;dev-&gt;dma_mask
suffix:semicolon
id|mq-&gt;card
op_assign
id|card
suffix:semicolon
id|mq-&gt;queue
op_assign
id|blk_init_queue
c_func
(paren
id|mmc_request
comma
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mq-&gt;queue
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|blk_queue_prep_rq
c_func
(paren
id|mq-&gt;queue
comma
id|mmc_prep_request
)paren
suffix:semicolon
id|blk_queue_bounce_limit
c_func
(paren
id|mq-&gt;queue
comma
id|limit
)paren
suffix:semicolon
id|mq-&gt;queue-&gt;queuedata
op_assign
id|mq
suffix:semicolon
id|mq-&gt;req
op_assign
l_int|NULL
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|mq-&gt;thread_complete
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|mq-&gt;thread_wq
)paren
suffix:semicolon
id|ret
op_assign
id|kernel_thread
c_func
(paren
id|mmc_queue_thread
comma
id|mq
comma
id|CLONE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|blk_cleanup_queue
c_func
(paren
id|mq-&gt;queue
)paren
suffix:semicolon
)brace
r_else
(brace
id|wait_for_completion
c_func
(paren
op_amp
id|mq-&gt;thread_complete
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|mq-&gt;thread_complete
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|mmc_init_queue
id|EXPORT_SYMBOL
c_func
(paren
id|mmc_init_queue
)paren
suffix:semicolon
DECL|function|mmc_cleanup_queue
r_void
id|mmc_cleanup_queue
c_func
(paren
r_struct
id|mmc_queue
op_star
id|mq
)paren
(brace
id|mq-&gt;thread
op_assign
l_int|NULL
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|mq-&gt;thread_wq
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|mq-&gt;thread_complete
)paren
suffix:semicolon
id|blk_cleanup_queue
c_func
(paren
id|mq-&gt;queue
)paren
suffix:semicolon
id|mq-&gt;card
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|mmc_cleanup_queue
id|EXPORT_SYMBOL
c_func
(paren
id|mmc_cleanup_queue
)paren
suffix:semicolon
eof
