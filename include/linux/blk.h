macro_line|#ifndef _BLK_H
DECL|macro|_BLK_H
mdefine_line|#define _BLK_H
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/elevator.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
r_extern
r_void
id|set_device_ro
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_void
id|add_blkdev_randomness
c_func
(paren
r_int
id|major
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|macro|INITRD_MINOR
mdefine_line|#define INITRD_MINOR 250 /* shouldn&squot;t collide with /dev/ram* too soon ... */
r_extern
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
r_extern
r_int
id|initrd_below_start_ok
suffix:semicolon
multiline_comment|/* 1 if it is not an error if initrd_start &lt; memory_start */
r_void
id|initrd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
macro_line|#endif
multiline_comment|/*&n; * end_request() and friends. Must be called with the request queue spinlock&n; * acquired. All functions called within end_request() _must_be_ atomic.&n; *&n; * Several drivers define their own end_request and call&n; * end_that_request_first() and end_that_request_last()&n; * for parts of the original function. This prevents&n; * code duplication in drivers.&n; */
r_extern
r_int
id|end_that_request_first
c_func
(paren
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
id|end_that_request_last
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
r_struct
id|request
op_star
id|elv_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
DECL|function|blkdev_dequeue_request
r_static
r_inline
r_void
id|blkdev_dequeue_request
c_func
(paren
r_struct
id|request
op_star
id|req
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|req-&gt;queuelist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;q
)paren
id|elv_remove_request
c_func
(paren
id|req-&gt;q
comma
id|req
)paren
suffix:semicolon
)brace
DECL|macro|_elv_add_request_core
mdefine_line|#define _elv_add_request_core(q, rq, where, plug)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((plug))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;blk_plug_device((q));&t;&t;&t;&t;&bslash;&n;&t;&t;(q)-&gt;elevator.elevator_add_req_fn((q), (rq), (where));&t;&bslash;&n;&t;} while (0)
DECL|macro|_elv_add_request
mdefine_line|#define _elv_add_request(q, rq, back, p) do {&t;&t;&t;&t;      &bslash;&n;&t;if ((back))&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;_elv_add_request_core((q), (rq), (q)-&gt;queue_head.prev, (p));  &bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;_elv_add_request_core((q), (rq), &amp;(q)-&gt;queue_head, (p));      &bslash;&n;} while (0)
DECL|macro|elv_add_request
mdefine_line|#define elv_add_request(q, rq, back) _elv_add_request((q), (rq), (back), 1)
macro_line|#if defined(MAJOR_NR) || defined(IDE_DRIVER)
macro_line|#if (MAJOR_NR != SCSI_TAPE_MAJOR) &amp;&amp; (MAJOR_NR != OSST_MAJOR)
macro_line|#if !defined(IDE_DRIVER)
macro_line|#ifndef QUEUE
DECL|macro|QUEUE
macro_line|# define QUEUE (&amp;blk_dev[MAJOR_NR].request_queue)
macro_line|#endif
macro_line|#ifndef CURRENT
DECL|macro|CURRENT
macro_line|# define CURRENT elv_next_request(QUEUE)
macro_line|#endif
macro_line|#endif /* !defined(IDE_DRIVER) */
multiline_comment|/*&n; * If we have our own end_request, we do not want to include this mess&n; */
macro_line|#ifndef LOCAL_END_REQUEST
DECL|function|end_request
r_static
r_inline
r_void
id|end_request
c_func
(paren
r_struct
id|request
op_star
id|req
comma
r_int
id|uptodate
)paren
(brace
r_if
c_cond
(paren
id|end_that_request_first
c_func
(paren
id|req
comma
id|uptodate
comma
id|req-&gt;hard_cur_sectors
)paren
)paren
r_return
suffix:semicolon
id|add_blkdev_randomness
c_func
(paren
id|major
c_func
(paren
id|req-&gt;rq_dev
)paren
)paren
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
macro_line|#endif /* !LOCAL_END_REQUEST */
macro_line|#endif /* (MAJOR_NR != SCSI_TAPE_MAJOR) */
macro_line|#endif /* defined(MAJOR_NR) || defined(IDE_DRIVER) */
macro_line|#endif /* _BLK_H */
eof
