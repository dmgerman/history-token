multiline_comment|/***********************************************************************&n; *  drivers/s390/char/tapedefs.h&n; *    tape device driver for S/390 and zSeries tapes.&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s):  Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *                Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; *&n; ***********************************************************************&n; */
DECL|macro|TAPE_DEBUG
mdefine_line|#define TAPE_DEBUG               
singleline_comment|// use s390 debug feature
DECL|macro|CONFIG_S390_TAPE_DYNAMIC
mdefine_line|#define CONFIG_S390_TAPE_DYNAMIC 
singleline_comment|// allow devices to be attached or detached on the fly
DECL|macro|TAPEBLOCK_RETRIES
mdefine_line|#define TAPEBLOCK_RETRIES 20     
singleline_comment|// number of retries, when a block-dev request fails.
multiline_comment|/* Kernel Version Compatibility section */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#if (LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,98))
DECL|macro|INIT_BLK_DEV
mdefine_line|#define INIT_BLK_DEV(d_major,d_request_fn,d_queue_fn,d_current) &bslash;&n;do { &bslash;&n;        blk_dev[d_major].queue = d_queue_fn; &bslash;&n;} while(0)
r_static
r_inline
r_struct
id|request
op_star
DECL|function|tape_next_request
id|tape_next_request
c_func
(paren
id|request_queue_t
op_star
id|queue
)paren
(brace
r_return
id|blkdev_entry_next_request
c_func
(paren
op_amp
id|queue-&gt;queue_head
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|tape_dequeue_request
id|tape_dequeue_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|req
)paren
(brace
id|blkdev_dequeue_request
(paren
id|req
)paren
suffix:semicolon
)brace
macro_line|#else 
DECL|macro|s390_dev_info_t
mdefine_line|#define s390_dev_info_t dev_info_t
DECL|typedef|request_queue_t
r_typedef
r_struct
id|request
op_star
id|request_queue_t
suffix:semicolon
macro_line|#ifndef init_waitqueue_head
DECL|macro|init_waitqueue_head
mdefine_line|#define init_waitqueue_head(x) do { *x = NULL; } while(0)
macro_line|#endif
DECL|macro|blk_init_queue
mdefine_line|#define blk_init_queue(x,y) do {} while(0)
DECL|macro|blk_queue_headactive
mdefine_line|#define blk_queue_headactive(x,y) do {} while(0)
DECL|macro|INIT_BLK_DEV
mdefine_line|#define INIT_BLK_DEV(d_major,d_request_fn,d_queue_fn,d_current) &bslash;&n;do { &bslash;&n;        blk_dev[d_major].request_fn = d_request_fn; &bslash;&n;        blk_dev[d_major].queue = d_queue_fn; &bslash;&n;        blk_dev[d_major].current_request = d_current; &bslash;&n;} while(0)
r_static
r_inline
r_struct
id|request
op_star
DECL|function|tape_next_request
id|tape_next_request
c_func
(paren
id|request_queue_t
op_star
id|queue
)paren
(brace
r_return
op_star
id|queue
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|tape_dequeue_request
id|tape_dequeue_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|req
)paren
(brace
op_star
id|q
op_assign
id|req-&gt;next
suffix:semicolon
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif 
eof
