multiline_comment|/*&n; * Copyright (C) 2002 Sistina Software (UK) Limited.&n; *&n; * This file is released under the GPL.&n; *&n; * Kcopyd provides a simple interface for copying an area of one&n; * block-device to one or more other block-devices, with an asynchronous&n; * completion notification.&n; */
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &quot;kcopyd.h&quot;
DECL|variable|_kcopyd_wq
r_static
r_struct
id|workqueue_struct
op_star
id|_kcopyd_wq
suffix:semicolon
DECL|variable|_kcopyd_work
r_static
r_struct
id|work_struct
id|_kcopyd_work
suffix:semicolon
DECL|function|wake
r_static
r_inline
r_void
id|wake
c_func
(paren
r_void
)paren
(brace
id|queue_work
c_func
(paren
id|_kcopyd_wq
comma
op_amp
id|_kcopyd_work
)paren
suffix:semicolon
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * Each kcopyd client has its own little pool of preallocated&n; * pages for kcopyd io.&n; *---------------------------------------------------------------*/
DECL|struct|kcopyd_client
r_struct
id|kcopyd_client
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|pages
r_struct
id|page_list
op_star
id|pages
suffix:semicolon
DECL|member|nr_pages
r_int
r_int
id|nr_pages
suffix:semicolon
DECL|member|nr_free_pages
r_int
r_int
id|nr_free_pages
suffix:semicolon
)brace
suffix:semicolon
DECL|function|alloc_pl
r_static
r_struct
id|page_list
op_star
id|alloc_pl
c_func
(paren
r_void
)paren
(brace
r_struct
id|page_list
op_star
id|pl
suffix:semicolon
id|pl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|pl
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pl
)paren
r_return
l_int|NULL
suffix:semicolon
id|pl-&gt;page
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pl-&gt;page
)paren
(brace
id|kfree
c_func
(paren
id|pl
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|pl
suffix:semicolon
)brace
DECL|function|free_pl
r_static
r_void
id|free_pl
c_func
(paren
r_struct
id|page_list
op_star
id|pl
)paren
(brace
id|__free_page
c_func
(paren
id|pl-&gt;page
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pl
)paren
suffix:semicolon
)brace
DECL|function|kcopyd_get_pages
r_static
r_int
id|kcopyd_get_pages
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
comma
r_int
r_int
id|nr
comma
r_struct
id|page_list
op_star
op_star
id|pages
)paren
(brace
r_struct
id|page_list
op_star
id|pl
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kc-&gt;nr_free_pages
OL
id|nr
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|kc-&gt;lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|kc-&gt;nr_free_pages
op_sub_assign
id|nr
suffix:semicolon
r_for
c_loop
(paren
op_star
id|pages
op_assign
id|pl
op_assign
id|kc-&gt;pages
suffix:semicolon
op_decrement
id|nr
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
)paren
suffix:semicolon
id|kc-&gt;pages
op_assign
id|pl-&gt;next
suffix:semicolon
id|pl-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kc-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kcopyd_put_pages
r_static
r_void
id|kcopyd_put_pages
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
comma
r_struct
id|page_list
op_star
id|pl
)paren
(brace
r_struct
id|page_list
op_star
id|cursor
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kc-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cursor
op_assign
id|pl
suffix:semicolon
id|cursor-&gt;next
suffix:semicolon
id|cursor
op_assign
id|cursor-&gt;next
)paren
id|kc-&gt;nr_free_pages
op_increment
suffix:semicolon
id|kc-&gt;nr_free_pages
op_increment
suffix:semicolon
id|cursor-&gt;next
op_assign
id|kc-&gt;pages
suffix:semicolon
id|kc-&gt;pages
op_assign
id|pl
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kc-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These three functions resize the page pool.&n; */
DECL|function|drop_pages
r_static
r_void
id|drop_pages
c_func
(paren
r_struct
id|page_list
op_star
id|pl
)paren
(brace
r_struct
id|page_list
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|next
op_assign
id|pl-&gt;next
suffix:semicolon
id|free_pl
c_func
(paren
id|pl
)paren
suffix:semicolon
id|pl
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|client_alloc_pages
r_static
r_int
id|client_alloc_pages
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_struct
id|page_list
op_star
id|pl
op_assign
l_int|NULL
comma
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|next
op_assign
id|alloc_pl
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
)paren
(brace
r_if
c_cond
(paren
id|pl
)paren
id|drop_pages
c_func
(paren
id|pl
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|next-&gt;next
op_assign
id|pl
suffix:semicolon
id|pl
op_assign
id|next
suffix:semicolon
)brace
id|kcopyd_put_pages
c_func
(paren
id|kc
comma
id|pl
)paren
suffix:semicolon
id|kc-&gt;nr_pages
op_add_assign
id|nr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|client_free_pages
r_static
r_void
id|client_free_pages
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
)paren
(brace
id|BUG_ON
c_func
(paren
id|kc-&gt;nr_free_pages
op_ne
id|kc-&gt;nr_pages
)paren
suffix:semicolon
id|drop_pages
c_func
(paren
id|kc-&gt;pages
)paren
suffix:semicolon
id|kc-&gt;pages
op_assign
l_int|NULL
suffix:semicolon
id|kc-&gt;nr_free_pages
op_assign
id|kc-&gt;nr_pages
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * kcopyd_jobs need to be allocated by the *clients* of kcopyd,&n; * for this reason we use a mempool to prevent the client from&n; * ever having to do io (which could cause a deadlock).&n; *---------------------------------------------------------------*/
DECL|struct|kcopyd_job
r_struct
id|kcopyd_job
(brace
DECL|member|kc
r_struct
id|kcopyd_client
op_star
id|kc
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * Error state of the job.&n;&t; */
DECL|member|read_err
r_int
id|read_err
suffix:semicolon
DECL|member|write_err
r_int
r_int
id|write_err
suffix:semicolon
multiline_comment|/*&n;&t; * Either READ or WRITE&n;&t; */
DECL|member|rw
r_int
id|rw
suffix:semicolon
DECL|member|source
r_struct
id|io_region
id|source
suffix:semicolon
multiline_comment|/*&n;&t; * The destinations for the transfer.&n;&t; */
DECL|member|num_dests
r_int
r_int
id|num_dests
suffix:semicolon
DECL|member|dests
r_struct
id|io_region
id|dests
(braket
id|KCOPYD_MAX_REGIONS
)braket
suffix:semicolon
DECL|member|offset
id|sector_t
id|offset
suffix:semicolon
DECL|member|nr_pages
r_int
r_int
id|nr_pages
suffix:semicolon
DECL|member|pages
r_struct
id|page_list
op_star
id|pages
suffix:semicolon
multiline_comment|/*&n;&t; * Set this to ensure you are notified when the job has&n;&t; * completed.  &squot;context&squot; is for callback to use.&n;&t; */
DECL|member|fn
id|kcopyd_notify_fn
id|fn
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/*&n;&t; * These fields are only used if the job has been split&n;&t; * into more manageable parts.&n;&t; */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|sub_jobs
id|atomic_t
id|sub_jobs
suffix:semicolon
DECL|member|progress
id|sector_t
id|progress
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FIXME: this should scale with the number of pages */
DECL|macro|MIN_JOBS
mdefine_line|#define MIN_JOBS 512
DECL|variable|_job_cache
r_static
id|kmem_cache_t
op_star
id|_job_cache
suffix:semicolon
DECL|variable|_job_pool
r_static
id|mempool_t
op_star
id|_job_pool
suffix:semicolon
multiline_comment|/*&n; * We maintain three lists of jobs:&n; *&n; * i)   jobs waiting for pages&n; * ii)  jobs that have pages, and are waiting for the io to be issued.&n; * iii) jobs that have completed.&n; *&n; * All three of these are protected by job_lock.&n; */
DECL|variable|_job_lock
r_static
id|spinlock_t
id|_job_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|_complete_jobs
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|_io_jobs
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|_pages_jobs
)paren
suffix:semicolon
DECL|function|jobs_init
r_static
r_int
id|jobs_init
c_func
(paren
r_void
)paren
(brace
id|_job_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;kcopyd-jobs&quot;
comma
r_sizeof
(paren
r_struct
id|kcopyd_job
)paren
comma
id|__alignof__
c_func
(paren
r_struct
id|kcopyd_job
)paren
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_job_cache
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|_job_pool
op_assign
id|mempool_create
c_func
(paren
id|MIN_JOBS
comma
id|mempool_alloc_slab
comma
id|mempool_free_slab
comma
id|_job_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_job_pool
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|_job_cache
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jobs_exit
r_static
r_void
id|jobs_exit
c_func
(paren
r_void
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|_complete_jobs
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|_io_jobs
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|_pages_jobs
)paren
)paren
suffix:semicolon
id|mempool_destroy
c_func
(paren
id|_job_pool
)paren
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|_job_cache
)paren
suffix:semicolon
id|_job_pool
op_assign
l_int|NULL
suffix:semicolon
id|_job_cache
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Functions to push and pop a job onto the head of a given job&n; * list.&n; */
DECL|function|pop
r_static
r_inline
r_struct
id|kcopyd_job
op_star
id|pop
c_func
(paren
r_struct
id|list_head
op_star
id|jobs
)paren
(brace
r_struct
id|kcopyd_job
op_star
id|job
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|_job_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|jobs
)paren
)paren
(brace
id|job
op_assign
id|list_entry
c_func
(paren
id|jobs-&gt;next
comma
r_struct
id|kcopyd_job
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|job-&gt;list
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|_job_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|job
suffix:semicolon
)brace
DECL|function|push
r_static
r_inline
r_void
id|push
c_func
(paren
r_struct
id|list_head
op_star
id|jobs
comma
r_struct
id|kcopyd_job
op_star
id|job
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|_job_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|job-&gt;list
comma
id|jobs
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|_job_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These three functions process 1 item from the corresponding&n; * job list.&n; *&n; * They return:&n; * &lt; 0: error&n; *   0: success&n; * &gt; 0: can&squot;t process yet.&n; */
DECL|function|run_complete_job
r_static
r_int
id|run_complete_job
c_func
(paren
r_struct
id|kcopyd_job
op_star
id|job
)paren
(brace
r_void
op_star
id|context
op_assign
id|job-&gt;context
suffix:semicolon
r_int
id|read_err
op_assign
id|job-&gt;read_err
suffix:semicolon
r_int
r_int
id|write_err
op_assign
id|job-&gt;write_err
suffix:semicolon
id|kcopyd_notify_fn
id|fn
op_assign
id|job-&gt;fn
suffix:semicolon
id|kcopyd_put_pages
c_func
(paren
id|job-&gt;kc
comma
id|job-&gt;pages
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|job
comma
id|_job_pool
)paren
suffix:semicolon
id|fn
c_func
(paren
id|read_err
comma
id|write_err
comma
id|context
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|complete_io
r_static
r_void
id|complete_io
c_func
(paren
r_int
r_int
id|error
comma
r_void
op_star
id|context
)paren
(brace
r_struct
id|kcopyd_job
op_star
id|job
op_assign
(paren
r_struct
id|kcopyd_job
op_star
)paren
id|context
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_if
c_cond
(paren
id|job-&gt;rw
op_eq
id|WRITE
)paren
id|job-&gt;write_err
op_and_assign
id|error
suffix:semicolon
r_else
id|job-&gt;read_err
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|KCOPYD_IGNORE_ERROR
comma
op_amp
id|job-&gt;flags
)paren
)paren
(brace
id|push
c_func
(paren
op_amp
id|_complete_jobs
comma
id|job
)paren
suffix:semicolon
id|wake
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|job-&gt;rw
op_eq
id|WRITE
)paren
id|push
c_func
(paren
op_amp
id|_complete_jobs
comma
id|job
)paren
suffix:semicolon
r_else
(brace
id|job-&gt;rw
op_assign
id|WRITE
suffix:semicolon
id|push
c_func
(paren
op_amp
id|_io_jobs
comma
id|job
)paren
suffix:semicolon
)brace
id|wake
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Request io on as many buffer heads as we can currently get for&n; * a particular job.&n; */
DECL|function|run_io_job
r_static
r_int
id|run_io_job
c_func
(paren
r_struct
id|kcopyd_job
op_star
id|job
)paren
(brace
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
id|job-&gt;rw
op_eq
id|READ
)paren
id|r
op_assign
id|dm_io_async
c_func
(paren
l_int|1
comma
op_amp
id|job-&gt;source
comma
id|job-&gt;rw
comma
id|job-&gt;pages
comma
id|job-&gt;offset
comma
id|complete_io
comma
id|job
)paren
suffix:semicolon
r_else
id|r
op_assign
id|dm_io_async
c_func
(paren
id|job-&gt;num_dests
comma
id|job-&gt;dests
comma
id|job-&gt;rw
comma
id|job-&gt;pages
comma
id|job-&gt;offset
comma
id|complete_io
comma
id|job
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|run_pages_job
r_static
r_int
id|run_pages_job
c_func
(paren
r_struct
id|kcopyd_job
op_star
id|job
)paren
(brace
r_int
id|r
suffix:semicolon
id|job-&gt;nr_pages
op_assign
id|dm_div_up
c_func
(paren
id|job-&gt;dests
(braket
l_int|0
)braket
dot
id|count
op_plus
id|job-&gt;offset
comma
id|PAGE_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
id|r
op_assign
id|kcopyd_get_pages
c_func
(paren
id|job-&gt;kc
comma
id|job-&gt;nr_pages
comma
op_amp
id|job-&gt;pages
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
(brace
multiline_comment|/* this job is ready for io */
id|push
c_func
(paren
op_amp
id|_io_jobs
comma
id|job
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r
op_eq
op_minus
id|ENOMEM
)paren
multiline_comment|/* can&squot;t complete now */
r_return
l_int|1
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * Run through a list for as long as possible.  Returns the count&n; * of successful jobs.&n; */
DECL|function|process_jobs
r_static
r_int
id|process_jobs
c_func
(paren
r_struct
id|list_head
op_star
id|jobs
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|kcopyd_job
op_star
)paren
)paren
(brace
r_struct
id|kcopyd_job
op_star
id|job
suffix:semicolon
r_int
id|r
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|job
op_assign
id|pop
c_func
(paren
id|jobs
)paren
)paren
)paren
(brace
id|r
op_assign
id|fn
c_func
(paren
id|job
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
(brace
multiline_comment|/* error this rogue job */
r_if
c_cond
(paren
id|job-&gt;rw
op_eq
id|WRITE
)paren
id|job-&gt;write_err
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_else
id|job-&gt;read_err
op_assign
l_int|1
suffix:semicolon
id|push
c_func
(paren
op_amp
id|_complete_jobs
comma
id|job
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We couldn&squot;t service this job ATM, so&n;&t;&t;&t; * push this job back onto the list.&n;&t;&t;&t; */
id|push
c_func
(paren
id|jobs
comma
id|job
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|count
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * kcopyd does this every time it&squot;s woken up.&n; */
DECL|function|do_work
r_static
r_void
id|do_work
c_func
(paren
r_void
op_star
id|ignored
)paren
(brace
multiline_comment|/*&n;&t; * The order that these are called is *very* important.&n;&t; * complete jobs can free some pages for pages jobs.&n;&t; * Pages jobs when successful will jump onto the io jobs&n;&t; * list.  io jobs call wake when they complete and it all&n;&t; * starts again.&n;&t; */
id|process_jobs
c_func
(paren
op_amp
id|_complete_jobs
comma
id|run_complete_job
)paren
suffix:semicolon
id|process_jobs
c_func
(paren
op_amp
id|_pages_jobs
comma
id|run_pages_job
)paren
suffix:semicolon
id|process_jobs
c_func
(paren
op_amp
id|_io_jobs
comma
id|run_io_job
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If we are copying a small region we just dispatch a single job&n; * to do the copy, otherwise the io has to be split up into many&n; * jobs.&n; */
DECL|function|dispatch_job
r_static
r_void
id|dispatch_job
c_func
(paren
r_struct
id|kcopyd_job
op_star
id|job
)paren
(brace
id|push
c_func
(paren
op_amp
id|_pages_jobs
comma
id|job
)paren
suffix:semicolon
id|wake
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|SUB_JOB_SIZE
mdefine_line|#define SUB_JOB_SIZE 128
DECL|function|segment_complete
r_static
r_void
id|segment_complete
c_func
(paren
r_int
id|read_err
comma
r_int
r_int
id|write_err
comma
r_void
op_star
id|context
)paren
(brace
multiline_comment|/* FIXME: tidy this function */
id|sector_t
id|progress
op_assign
l_int|0
suffix:semicolon
id|sector_t
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|kcopyd_job
op_star
id|job
op_assign
(paren
r_struct
id|kcopyd_job
op_star
)paren
id|context
suffix:semicolon
id|down
c_func
(paren
op_amp
id|job-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* update the error */
r_if
c_cond
(paren
id|read_err
)paren
id|job-&gt;read_err
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write_err
)paren
id|job-&gt;write_err
op_and_assign
id|write_err
suffix:semicolon
multiline_comment|/*&n;&t; * Only dispatch more work if there hasn&squot;t been an error.&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|job-&gt;read_err
op_logical_and
op_logical_neg
id|job-&gt;write_err
)paren
op_logical_or
id|test_bit
c_func
(paren
id|KCOPYD_IGNORE_ERROR
comma
op_amp
id|job-&gt;flags
)paren
)paren
(brace
multiline_comment|/* get the next chunk of work */
id|progress
op_assign
id|job-&gt;progress
suffix:semicolon
id|count
op_assign
id|job-&gt;source.count
op_minus
id|progress
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|SUB_JOB_SIZE
)paren
id|count
op_assign
id|SUB_JOB_SIZE
suffix:semicolon
id|job-&gt;progress
op_add_assign
id|count
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|job-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|kcopyd_job
op_star
id|sub_job
op_assign
id|mempool_alloc
c_func
(paren
id|_job_pool
comma
id|GFP_NOIO
)paren
suffix:semicolon
op_star
id|sub_job
op_assign
op_star
id|job
suffix:semicolon
id|sub_job-&gt;source.sector
op_add_assign
id|progress
suffix:semicolon
id|sub_job-&gt;source.count
op_assign
id|count
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|job-&gt;num_dests
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sub_job-&gt;dests
(braket
id|i
)braket
dot
id|sector
op_add_assign
id|progress
suffix:semicolon
id|sub_job-&gt;dests
(braket
id|i
)braket
dot
id|count
op_assign
id|count
suffix:semicolon
)brace
id|sub_job-&gt;fn
op_assign
id|segment_complete
suffix:semicolon
id|sub_job-&gt;context
op_assign
id|job
suffix:semicolon
id|dispatch_job
c_func
(paren
id|sub_job
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|job-&gt;sub_jobs
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * To avoid a race we must keep the job around&n;&t;&t; * until after the notify function has completed.&n;&t;&t; * Otherwise the client may try and stop the job&n;&t;&t; * after we&squot;ve completed.&n;&t;&t; */
id|job
op_member_access_from_pointer
id|fn
c_func
(paren
id|read_err
comma
id|write_err
comma
id|job-&gt;context
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|job
comma
id|_job_pool
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Create some little jobs that will do the move between&n; * them.&n; */
DECL|macro|SPLIT_COUNT
mdefine_line|#define SPLIT_COUNT 8
DECL|function|split_job
r_static
r_void
id|split_job
c_func
(paren
r_struct
id|kcopyd_job
op_star
id|job
)paren
(brace
r_int
id|i
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|job-&gt;sub_jobs
comma
id|SPLIT_COUNT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SPLIT_COUNT
suffix:semicolon
id|i
op_increment
)paren
id|segment_complete
c_func
(paren
l_int|0
comma
l_int|0u
comma
id|job
)paren
suffix:semicolon
)brace
DECL|function|kcopyd_copy
r_int
id|kcopyd_copy
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
comma
r_struct
id|io_region
op_star
id|from
comma
r_int
r_int
id|num_dests
comma
r_struct
id|io_region
op_star
id|dests
comma
r_int
r_int
id|flags
comma
id|kcopyd_notify_fn
id|fn
comma
r_void
op_star
id|context
)paren
(brace
r_struct
id|kcopyd_job
op_star
id|job
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a new job.&n;&t; */
id|job
op_assign
id|mempool_alloc
c_func
(paren
id|_job_pool
comma
id|GFP_NOIO
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set up for the read.&n;&t; */
id|job-&gt;kc
op_assign
id|kc
suffix:semicolon
id|job-&gt;flags
op_assign
id|flags
suffix:semicolon
id|job-&gt;read_err
op_assign
l_int|0
suffix:semicolon
id|job-&gt;write_err
op_assign
l_int|0
suffix:semicolon
id|job-&gt;rw
op_assign
id|READ
suffix:semicolon
id|job-&gt;source
op_assign
op_star
id|from
suffix:semicolon
id|job-&gt;num_dests
op_assign
id|num_dests
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|job-&gt;dests
comma
id|dests
comma
r_sizeof
(paren
op_star
id|dests
)paren
op_star
id|num_dests
)paren
suffix:semicolon
id|job-&gt;offset
op_assign
l_int|0
suffix:semicolon
id|job-&gt;nr_pages
op_assign
l_int|0
suffix:semicolon
id|job-&gt;pages
op_assign
l_int|NULL
suffix:semicolon
id|job-&gt;fn
op_assign
id|fn
suffix:semicolon
id|job-&gt;context
op_assign
id|context
suffix:semicolon
r_if
c_cond
(paren
id|job-&gt;source.count
OL
id|SUB_JOB_SIZE
)paren
id|dispatch_job
c_func
(paren
id|job
)paren
suffix:semicolon
r_else
(brace
id|init_MUTEX
c_func
(paren
op_amp
id|job-&gt;lock
)paren
suffix:semicolon
id|job-&gt;progress
op_assign
l_int|0
suffix:semicolon
id|split_job
c_func
(paren
id|job
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Cancels a kcopyd job, eg. someone might be deactivating a&n; * mirror.&n; */
DECL|function|kcopyd_cancel
r_int
id|kcopyd_cancel
c_func
(paren
r_struct
id|kcopyd_job
op_star
id|job
comma
r_int
id|block
)paren
(brace
multiline_comment|/* FIXME: finish */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * Unit setup&n; *---------------------------------------------------------------*/
r_static
id|DECLARE_MUTEX
c_func
(paren
id|_client_lock
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|_clients
)paren
suffix:semicolon
DECL|function|client_add
r_static
r_void
id|client_add
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
)paren
(brace
id|down
c_func
(paren
op_amp
id|_client_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|kc-&gt;list
comma
op_amp
id|_clients
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|_client_lock
)paren
suffix:semicolon
)brace
DECL|function|client_del
r_static
r_void
id|client_del
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
)paren
(brace
id|down
c_func
(paren
op_amp
id|_client_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|kc-&gt;list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|_client_lock
)paren
suffix:semicolon
)brace
r_static
id|DECLARE_MUTEX
c_func
(paren
id|kcopyd_init_lock
)paren
suffix:semicolon
DECL|variable|kcopyd_clients
r_static
r_int
id|kcopyd_clients
op_assign
l_int|0
suffix:semicolon
DECL|function|kcopyd_init
r_static
r_int
id|kcopyd_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
id|down
c_func
(paren
op_amp
id|kcopyd_init_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kcopyd_clients
)paren
(brace
multiline_comment|/* Already initialized. */
id|kcopyd_clients
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|kcopyd_init_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|r
op_assign
id|jobs_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|up
c_func
(paren
op_amp
id|kcopyd_init_lock
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
id|_kcopyd_wq
op_assign
id|create_singlethread_workqueue
c_func
(paren
l_string|&quot;kcopyd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_kcopyd_wq
)paren
(brace
id|jobs_exit
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|kcopyd_init_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|kcopyd_clients
op_increment
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|_kcopyd_work
comma
id|do_work
comma
l_int|NULL
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|kcopyd_init_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kcopyd_exit
r_static
r_void
id|kcopyd_exit
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|kcopyd_init_lock
)paren
suffix:semicolon
id|kcopyd_clients
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kcopyd_clients
)paren
(brace
id|jobs_exit
c_func
(paren
)paren
suffix:semicolon
id|destroy_workqueue
c_func
(paren
id|_kcopyd_wq
)paren
suffix:semicolon
id|_kcopyd_wq
op_assign
l_int|NULL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|kcopyd_init_lock
)paren
suffix:semicolon
)brace
DECL|function|kcopyd_client_create
r_int
id|kcopyd_client_create
c_func
(paren
r_int
r_int
id|nr_pages
comma
r_struct
id|kcopyd_client
op_star
op_star
id|result
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
r_struct
id|kcopyd_client
op_star
id|kc
suffix:semicolon
id|r
op_assign
id|kcopyd_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
id|kc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|kc
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kc
)paren
(brace
id|kcopyd_exit
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|kc-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|kc-&gt;pages
op_assign
l_int|NULL
suffix:semicolon
id|kc-&gt;nr_pages
op_assign
id|kc-&gt;nr_free_pages
op_assign
l_int|0
suffix:semicolon
id|r
op_assign
id|client_alloc_pages
c_func
(paren
id|kc
comma
id|nr_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|kfree
c_func
(paren
id|kc
)paren
suffix:semicolon
id|kcopyd_exit
c_func
(paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
id|r
op_assign
id|dm_io_get
c_func
(paren
id|nr_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|client_free_pages
c_func
(paren
id|kc
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kc
)paren
suffix:semicolon
id|kcopyd_exit
c_func
(paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
id|client_add
c_func
(paren
id|kc
)paren
suffix:semicolon
op_star
id|result
op_assign
id|kc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kcopyd_client_destroy
r_void
id|kcopyd_client_destroy
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
)paren
(brace
id|dm_io_put
c_func
(paren
id|kc-&gt;nr_pages
)paren
suffix:semicolon
id|client_free_pages
c_func
(paren
id|kc
)paren
suffix:semicolon
id|client_del
c_func
(paren
id|kc
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kc
)paren
suffix:semicolon
id|kcopyd_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|kcopyd_client_create
id|EXPORT_SYMBOL
c_func
(paren
id|kcopyd_client_create
)paren
suffix:semicolon
DECL|variable|kcopyd_client_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|kcopyd_client_destroy
)paren
suffix:semicolon
DECL|variable|kcopyd_copy
id|EXPORT_SYMBOL
c_func
(paren
id|kcopyd_copy
)paren
suffix:semicolon
DECL|variable|kcopyd_cancel
id|EXPORT_SYMBOL
c_func
(paren
id|kcopyd_cancel
)paren
suffix:semicolon
eof
