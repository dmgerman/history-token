multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tapeblock.c&n; *    block device frontend for tape device driver&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Corporation&n; *    Author(s): Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; *  UNDER CONSTRUCTION: Work in progress...:-)&n; ****************************************************************************&n; */
macro_line|#include &quot;tapedefs.h&quot;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/ccwcache.h&gt;&t;/* CCW allocations      */
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/s390dyn.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#endif
macro_line|#include &quot;tape.h&quot;
macro_line|#include &quot;tapeblock.h&quot;
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;TBLOCK:&quot;
multiline_comment|/*&n; * file operation structure for tape devices&n; */
macro_line|#if (LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,98))
DECL|variable|tapeblock_fops
r_static
r_struct
id|block_device_operations
id|tapeblock_fops
op_assign
(brace
macro_line|#else
r_static
r_struct
id|file_operations
id|tapeblock_fops
op_assign
(brace
macro_line|#endif
id|open
suffix:colon
id|tapeblock_open
comma
multiline_comment|/* open */
id|release
suffix:colon
id|tapeblock_release
comma
multiline_comment|/* release */
)brace
suffix:semicolon
DECL|variable|tapeblock_major
r_int
id|tapeblock_major
op_assign
l_int|0
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,98))
r_static
r_void
id|tape_request_fn
(paren
id|request_queue_t
op_star
id|queue
)paren
suffix:semicolon
macro_line|#else
r_static
r_void
id|tape_request_fn
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_static
id|request_queue_t
op_star
id|tapeblock_getqueue
(paren
id|kdev_t
id|kdev
)paren
suffix:semicolon
r_void
DECL|function|tapeblock_setup
id|tapeblock_setup
c_func
(paren
id|tape_info_t
op_star
id|tape
)paren
(brace
id|blk_size
(braket
id|tapeblock_major
)braket
(braket
id|tape-&gt;blk_minor
)braket
op_assign
l_int|0
suffix:semicolon
singleline_comment|// this will be detected
id|blksize_size
(braket
id|tapeblock_major
)braket
(braket
id|tape-&gt;blk_minor
)braket
op_assign
l_int|2048
suffix:semicolon
singleline_comment|// blocks are 2k by default.
id|hardsect_size
(braket
id|tapeblock_major
)braket
(braket
id|tape-&gt;blk_minor
)braket
op_assign
l_int|512
suffix:semicolon
id|blk_init_queue
(paren
op_amp
id|tape-&gt;request_queue
comma
id|tape_request_fn
)paren
suffix:semicolon
id|blk_queue_headactive
(paren
op_amp
id|tape-&gt;request_queue
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|tapeblock_init
id|tapeblock_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
id|tape_frontend_t
op_star
id|blkfront
comma
op_star
id|temp
suffix:semicolon
id|tape_info_t
op_star
id|tape
suffix:semicolon
id|tape_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Register the tape major number to the kernel */
id|result
op_assign
id|register_blkdev
c_func
(paren
id|tapeblock_major
comma
l_string|&quot;tBLK&quot;
comma
op_amp
id|tapeblock_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|PRINT_WARN
c_func
(paren
id|KERN_ERR
l_string|&quot;tape: can&squot;t get major %d for block device&bslash;n&quot;
comma
id|tapeblock_major
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;cannot get major number for tape block device&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tapeblock_major
op_eq
l_int|0
)paren
id|tapeblock_major
op_assign
id|result
suffix:semicolon
multiline_comment|/* accept dynamic major number*/
id|INIT_BLK_DEV
c_func
(paren
id|tapeblock_major
comma
id|tape_request_fn
comma
id|tapeblock_getqueue
comma
l_int|NULL
)paren
suffix:semicolon
id|read_ahead
(braket
id|tapeblock_major
)braket
op_assign
id|TAPEBLOCK_READAHEAD
suffix:semicolon
id|PRINT_WARN
c_func
(paren
id|KERN_ERR
l_string|&quot; tape gets major %d for block device&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|blk_size
(braket
id|tapeblock_major
)braket
op_assign
(paren
r_int
op_star
)paren
id|kmalloc
(paren
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
c_func
(paren
id|blk_size
(braket
id|tapeblock_major
)braket
comma
l_int|0
comma
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|blksize_size
(braket
id|tapeblock_major
)braket
op_assign
(paren
r_int
op_star
)paren
id|kmalloc
(paren
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
c_func
(paren
id|blksize_size
(braket
id|tapeblock_major
)braket
comma
l_int|0
comma
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|hardsect_size
(braket
id|tapeblock_major
)braket
op_assign
(paren
r_int
op_star
)paren
id|kmalloc
(paren
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
c_func
(paren
id|hardsect_size
(braket
id|tapeblock_major
)braket
comma
l_int|0
comma
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|max_sectors
(braket
id|tapeblock_major
)braket
op_assign
(paren
r_int
op_star
)paren
id|kmalloc
(paren
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
c_func
(paren
id|max_sectors
(braket
id|tapeblock_major
)braket
comma
l_int|0
comma
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|blkfront
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|tape_frontend_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blkfront
op_eq
l_int|NULL
)paren
id|panic
(paren
l_string|&quot;no mem for tape block device structure&quot;
)paren
suffix:semicolon
id|blkfront-&gt;device_setup
op_assign
id|tapeblock_setup
suffix:semicolon
id|blkfront-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|first_frontend
op_eq
l_int|NULL
)paren
(brace
id|first_frontend
op_assign
id|blkfront
suffix:semicolon
)brace
r_else
(brace
id|temp
op_assign
id|first_frontend
suffix:semicolon
r_while
c_loop
(paren
id|temp-&gt;next
op_ne
l_int|NULL
)paren
id|temp
op_assign
id|temp-&gt;next
suffix:semicolon
id|temp-&gt;next
op_assign
id|blkfront
suffix:semicolon
)brace
id|tape
op_assign
id|first_tape_info
suffix:semicolon
r_while
c_loop
(paren
id|tape
op_ne
l_int|NULL
)paren
(brace
id|tapeblock_setup
c_func
(paren
id|tape
)paren
suffix:semicolon
id|tape
op_assign
id|tape-&gt;next
suffix:semicolon
)brace
)brace
r_void
DECL|function|tapeblock_uninit
id|tapeblock_uninit
c_func
(paren
r_void
)paren
(brace
id|unregister_blkdev
c_func
(paren
id|tapeblock_major
comma
l_string|&quot;tBLK&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tapeblock_open
id|tapeblock_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
id|tape_info_t
op_star
id|ti
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|lockflags
suffix:semicolon
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ti
op_assign
id|first_tape_info
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ti
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|ti-&gt;blk_minor
op_ne
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
)paren
)paren
id|ti
op_assign
(paren
id|tape_info_t
op_star
)paren
id|ti-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ti
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:open:&quot;
)paren
suffix:semicolon
id|debug_int_event
(paren
id|tape_debug_area
comma
l_int|6
comma
id|ti-&gt;blk_minor
)paren
suffix:semicolon
macro_line|#endif
id|s390irq_spin_lock_irqsave
(paren
id|ti-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tapestate_get
(paren
id|ti
)paren
op_ne
id|TS_UNUSED
)paren
(brace
id|s390irq_spin_unlock_irqrestore
(paren
id|ti-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:dbusy&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|tapestate_set
(paren
id|ti
comma
id|TS_IDLE
)paren
suffix:semicolon
id|ti-&gt;position
op_assign
op_minus
l_int|1
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|ti-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|rc
op_assign
id|tapeblock_mediumdetect
c_func
(paren
id|ti
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// in case of errors, we don&squot;t have a size of the medium
id|dev
op_assign
id|MKDEV
(paren
id|tapeblock_major
comma
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the device */
id|s390irq_spin_lock_irqsave
(paren
id|ti-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|ti-&gt;blk_filp
op_assign
id|filp
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|ti
suffix:semicolon
multiline_comment|/* save the dev.info for later reference */
id|ti-&gt;cqr
op_assign
l_int|NULL
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|ti-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* MODULE */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|tapeblock_release
id|tapeblock_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|lockflags
suffix:semicolon
id|tape_info_t
op_star
id|ti
comma
op_star
id|lastti
suffix:semicolon
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ti
op_assign
id|first_tape_info
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ti
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|ti-&gt;blk_minor
op_ne
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
)paren
)paren
id|ti
op_assign
(paren
id|tape_info_t
op_star
)paren
id|ti-&gt;next
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ti
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|tapestate_get
(paren
id|ti
)paren
op_eq
id|TS_NOT_OPER
)paren
)paren
(brace
r_if
c_cond
(paren
id|ti
op_eq
id|first_tape_info
)paren
(brace
id|first_tape_info
op_assign
id|ti-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|lastti
op_assign
id|first_tape_info
suffix:semicolon
r_while
c_loop
(paren
id|lastti-&gt;next
op_ne
id|ti
)paren
id|lastti
op_assign
id|lastti-&gt;next
suffix:semicolon
id|lastti-&gt;next
op_assign
id|ti-&gt;next
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|ti
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ti
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|tapestate_get
(paren
id|ti
)paren
op_ne
id|TS_IDLE
)paren
)paren
(brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:notidle!&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* error in tape_release */
)brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:release:&quot;
)paren
suffix:semicolon
id|debug_int_event
(paren
id|tape_debug_area
comma
l_int|6
comma
id|ti-&gt;blk_minor
)paren
suffix:semicolon
macro_line|#endif
id|s390irq_spin_lock_irqsave
(paren
id|ti-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tapestate_set
(paren
id|ti
comma
id|TS_UNUSED
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|ti-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* MODULE */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|tapeblock_end_request
id|tapeblock_end_request
c_func
(paren
id|tape_info_t
op_star
id|tape
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|uptodate
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tapestate_get
c_func
(paren
id|tape
)paren
op_ne
id|TS_FAILED
)paren
op_logical_and
(paren
id|tapestate_get
c_func
(paren
id|tape
)paren
op_ne
id|TS_DONE
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
singleline_comment|// A request has to be completed to end it
id|uptodate
op_assign
(paren
id|tapestate_get
c_func
(paren
id|tape
)paren
op_eq
id|TS_DONE
)paren
suffix:semicolon
singleline_comment|// is the buffer up to date?
macro_line|#ifdef TAPE_DEBUG
r_if
c_cond
(paren
id|uptodate
)paren
(brace
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:done:&quot;
)paren
suffix:semicolon
id|debug_int_event
(paren
id|tape_debug_area
comma
l_int|6
comma
(paren
r_int
)paren
id|tape-&gt;cqr
)paren
suffix:semicolon
)brace
r_else
(brace
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;b:failed:&quot;
)paren
suffix:semicolon
id|debug_int_event
(paren
id|tape_debug_area
comma
l_int|3
comma
(paren
r_int
)paren
id|tape-&gt;cqr
)paren
suffix:semicolon
)brace
macro_line|#endif
singleline_comment|// now inform ll_rw_block about a request status
r_while
c_loop
(paren
(paren
id|bh
op_assign
id|tape-&gt;current_request-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|tape-&gt;current_request-&gt;bh
op_assign
id|bh-&gt;b_reqnext
suffix:semicolon
id|bh-&gt;b_reqnext
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_end_io
(paren
id|bh
comma
id|uptodate
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|end_that_request_first
(paren
id|tape-&gt;current_request
comma
id|uptodate
comma
l_string|&quot;tBLK&quot;
)paren
)paren
(brace
macro_line|#ifndef DEVICE_NO_RANDOM
id|add_blkdev_randomness
(paren
id|MAJOR
(paren
id|tape-&gt;current_request-&gt;rq_dev
)paren
)paren
suffix:semicolon
macro_line|#endif
id|end_that_request_last
(paren
id|tape-&gt;current_request
)paren
suffix:semicolon
)brace
id|tape-&gt;discipline
op_member_access_from_pointer
id|free_bread
c_func
(paren
id|tape-&gt;cqr
comma
id|tape
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
l_int|NULL
suffix:semicolon
id|tape-&gt;current_request
op_assign
l_int|NULL
suffix:semicolon
id|tapestate_set
c_func
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|tapeblock_exec_IO
id|tapeblock_exec_IO
(paren
id|tape_info_t
op_star
id|tape
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|request
op_star
id|req
suffix:semicolon
r_if
c_cond
(paren
id|tape-&gt;cqr
)paren
(brace
singleline_comment|// process done/failed request
r_while
c_loop
(paren
(paren
id|tapestate_get
c_func
(paren
id|tape
)paren
op_eq
id|TS_FAILED
)paren
op_logical_and
id|tape-&gt;blk_retries
OG
l_int|0
)paren
(brace
id|tape-&gt;blk_retries
op_decrement
suffix:semicolon
id|tape-&gt;position
op_assign
op_minus
l_int|1
suffix:semicolon
id|tapestate_set
c_func
(paren
id|tape
comma
id|TS_BLOCK_INIT
)paren
suffix:semicolon
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;b:retryreq:&quot;
)paren
suffix:semicolon
id|debug_int_event
(paren
id|tape_debug_area
comma
l_int|3
comma
(paren
r_int
)paren
id|tape-&gt;cqr
)paren
suffix:semicolon
macro_line|#endif
id|rc
op_assign
id|do_IO
(paren
id|tape-&gt;devinfo.irq
comma
id|tape-&gt;cqr-&gt;cpaddr
comma
(paren
r_int
r_int
)paren
id|tape-&gt;cqr
comma
l_int|0x00
comma
id|tape-&gt;cqr-&gt;options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;b:doIOfail:&quot;
)paren
suffix:semicolon
id|debug_int_event
(paren
id|tape_debug_area
comma
l_int|3
comma
(paren
r_int
)paren
id|tape-&gt;cqr
)paren
suffix:semicolon
macro_line|#endif 
r_continue
suffix:semicolon
singleline_comment|// one retry lost &squot;cause doIO failed
)brace
r_return
suffix:semicolon
)brace
id|tapeblock_end_request
(paren
id|tape
)paren
suffix:semicolon
singleline_comment|// check state, inform user, free mem, dev=idl
)brace
r_if
c_cond
(paren
id|tape-&gt;cqr
op_ne
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
singleline_comment|// tape should be idle now, request should be freed!
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|tape-&gt;request_queue.queue_head
)paren
)paren
(brace
singleline_comment|// nothing more to do ;)
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:Qempty&quot;
)paren
suffix:semicolon
macro_line|#endif
id|tapestate_set
c_func
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
singleline_comment|// queue is not empty, fetch a request and start IO!
id|req
op_assign
id|tape-&gt;current_request
op_assign
id|tape_next_request
c_func
(paren
op_amp
id|tape-&gt;request_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
l_int|NULL
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
singleline_comment|// Yo. The queue was not reported empy, but no request found. This is _bad_.
)brace
r_if
c_cond
(paren
id|req-&gt;cmd
op_ne
id|READ
)paren
(brace
singleline_comment|// we only support reading
id|tapestate_set
c_func
(paren
id|tape
comma
id|TS_FAILED
)paren
suffix:semicolon
id|tapeblock_end_request
(paren
id|tape
)paren
suffix:semicolon
singleline_comment|// check state, inform user, free mem, dev=idl
id|tapestate_set
c_func
(paren
id|tape
comma
id|TS_BLOCK_INIT
)paren
suffix:semicolon
id|schedule_tapeblock_exec_IO
c_func
(paren
id|tape
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tape-&gt;cqr
op_assign
id|tape-&gt;discipline
op_member_access_from_pointer
id|bread
c_func
(paren
id|req
comma
id|tape
comma
id|tapeblock_major
)paren
suffix:semicolon
singleline_comment|//build channel program from request
r_if
c_cond
(paren
op_logical_neg
id|tape-&gt;cqr
)paren
(brace
singleline_comment|// ccw generation failed. we try again later.
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;b:cqrNULL&quot;
)paren
suffix:semicolon
macro_line|#endif
id|schedule_tapeblock_exec_IO
c_func
(paren
id|tape
)paren
suffix:semicolon
id|tape-&gt;current_request
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tape-&gt;blk_retries
op_assign
id|TAPEBLOCK_RETRIES
suffix:semicolon
id|rc
op_assign
id|do_IO
(paren
id|tape-&gt;devinfo.irq
comma
id|tape-&gt;cqr-&gt;cpaddr
comma
(paren
r_int
r_int
)paren
id|tape-&gt;cqr
comma
l_int|0x00
comma
id|tape-&gt;cqr-&gt;options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
singleline_comment|// okay. ssch failed. we try later.
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;b:doIOfail&quot;
)paren
suffix:semicolon
macro_line|#endif
id|tape-&gt;discipline
op_member_access_from_pointer
id|free_bread
c_func
(paren
id|tape-&gt;cqr
comma
id|tape
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
l_int|NULL
suffix:semicolon
id|tape-&gt;current_request
op_assign
l_int|NULL
suffix:semicolon
id|schedule_tapeblock_exec_IO
c_func
(paren
id|tape
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
singleline_comment|// our request is in IO. we remove it from the queue and exit
id|tape_dequeue_request
(paren
op_amp
id|tape-&gt;request_queue
comma
id|req
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|do_tape_request
id|do_tape_request
(paren
id|request_queue_t
op_star
id|queue
)paren
(brace
id|tape_info_t
op_star
id|tape
suffix:semicolon
r_int
id|lockflags
suffix:semicolon
r_for
c_loop
(paren
id|tape
op_assign
id|first_tape_info
suffix:semicolon
(paren
(paren
id|tape
op_ne
l_int|NULL
)paren
op_logical_and
(paren
(paren
op_amp
id|tape-&gt;request_queue
)paren
op_ne
id|queue
)paren
)paren
suffix:semicolon
id|tape
op_assign
id|tape-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tape
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tapestate_get
c_func
(paren
id|tape
)paren
op_ne
id|TS_IDLE
)paren
(brace
id|s390irq_spin_unlock_irqrestore
c_func
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tapestate_get
c_func
(paren
id|tape
)paren
op_ne
id|TS_IDLE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|tapestate_set
c_func
(paren
id|tape
comma
id|TS_BLOCK_INIT
)paren
suffix:semicolon
id|tapeblock_exec_IO
c_func
(paren
id|tape
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
c_func
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|run_tapeblock_exec_IO
id|run_tapeblock_exec_IO
(paren
id|tape_info_t
op_star
id|tape
)paren
(brace
r_int
id|flags_390irq
comma
id|flags_ior
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|io_request_lock
comma
id|flags_ior
)paren
suffix:semicolon
id|s390irq_spin_lock_irqsave
c_func
(paren
id|tape-&gt;devinfo.irq
comma
id|flags_390irq
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|tape-&gt;bh_scheduled
comma
l_int|0
)paren
suffix:semicolon
id|tapeblock_exec_IO
c_func
(paren
id|tape
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
c_func
(paren
id|tape-&gt;devinfo.irq
comma
id|flags_390irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|io_request_lock
comma
id|flags_ior
)paren
suffix:semicolon
)brace
r_void
DECL|function|schedule_tapeblock_exec_IO
id|schedule_tapeblock_exec_IO
(paren
id|tape_info_t
op_star
id|tape
)paren
(brace
multiline_comment|/* Protect against rescheduling, when already running */
r_if
c_cond
(paren
id|atomic_compare_and_swap
c_func
(paren
l_int|0
comma
l_int|1
comma
op_amp
id|tape-&gt;bh_scheduled
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|tape-&gt;bh_tq.list
)paren
suffix:semicolon
id|tape-&gt;bh_tq.sync
op_assign
l_int|0
suffix:semicolon
id|tape-&gt;bh_tq.routine
op_assign
(paren
r_void
op_star
)paren
(paren
r_void
op_star
)paren
id|run_tapeblock_exec_IO
suffix:semicolon
id|tape-&gt;bh_tq.data
op_assign
id|tape
suffix:semicolon
id|queue_task
(paren
op_amp
id|tape-&gt;bh_tq
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* wrappers around do_tape_request for different kernel versions */
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,98))
DECL|function|tape_request_fn
r_static
r_void
id|tape_request_fn
(paren
r_void
)paren
(brace
id|tape_info_t
op_star
id|tape
op_assign
id|first_tape_info
suffix:semicolon
r_while
c_loop
(paren
id|tape
op_ne
l_int|NULL
)paren
(brace
id|do_tape_request
c_func
(paren
op_amp
id|tape-&gt;request_queue
)paren
suffix:semicolon
id|tape
op_assign
id|tape-&gt;next
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|function|tape_request_fn
r_static
r_void
id|tape_request_fn
(paren
id|request_queue_t
op_star
id|queue
)paren
(brace
id|do_tape_request
c_func
(paren
id|queue
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|tapeblock_getqueue
r_static
id|request_queue_t
op_star
id|tapeblock_getqueue
(paren
id|kdev_t
id|kdev
)paren
(brace
id|tape_info_t
op_star
id|tape
op_assign
id|first_tape_info
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tape
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|MINOR
c_func
(paren
id|kdev
)paren
op_ne
id|tape-&gt;blk_minor
)paren
)paren
id|tape
op_assign
id|tape-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|tape
op_ne
l_int|NULL
)paren
r_return
op_amp
id|tape-&gt;request_queue
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|tapeblock_mediumdetect
r_static
r_int
id|tapeblock_mediumdetect
c_func
(paren
id|tape_info_t
op_star
id|tape
)paren
(brace
id|ccw_req_t
op_star
id|cqr
suffix:semicolon
r_int
id|losize
op_assign
l_int|1
comma
id|hisize
op_assign
l_int|1
comma
id|rc
suffix:semicolon
r_int
id|lockflags
suffix:semicolon
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;b:medDet&quot;
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
)paren
(brace
singleline_comment|//is interruped by break
id|hisize
op_assign
id|hisize
op_lshift
l_int|1
suffix:semicolon
singleline_comment|// try twice the size tested before 
id|cqr
op_assign
id|tape-&gt;discipline-&gt;mtseek
(paren
id|tape
comma
id|hisize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cqr
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:ccwg fail&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
id|cqr
suffix:semicolon
id|tape-&gt;wanna_wakeup
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|do_IO
(paren
id|tape-&gt;devinfo.irq
comma
id|cqr-&gt;cpaddr
comma
(paren
r_int
r_int
)paren
id|cqr
comma
l_int|0x00
comma
id|cqr-&gt;options
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|wait_event_interruptible
(paren
id|tape-&gt;wq
comma
id|tape-&gt;wanna_wakeup
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
l_int|NULL
suffix:semicolon
id|tape_free_request
(paren
id|cqr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tape-&gt;kernbuf
)paren
(brace
id|kfree
(paren
id|tape-&gt;kernbuf
)paren
suffix:semicolon
id|tape-&gt;kernbuf
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_eq
id|TS_FAILED
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_ne
id|TS_DONE
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|losize
op_assign
id|hisize
suffix:semicolon
)brace
id|cqr
op_assign
id|tape-&gt;discipline-&gt;mtrew
(paren
id|tape
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cqr
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:ccwg fail&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
id|cqr
suffix:semicolon
id|tape-&gt;wanna_wakeup
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|do_IO
(paren
id|tape-&gt;devinfo.irq
comma
id|cqr-&gt;cpaddr
comma
(paren
r_int
r_int
)paren
id|cqr
comma
l_int|0x00
comma
id|cqr-&gt;options
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|wait_event_interruptible
(paren
id|tape-&gt;wq
comma
id|tape-&gt;wanna_wakeup
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
l_int|NULL
suffix:semicolon
id|tape_free_request
(paren
id|cqr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_eq
id|TS_FAILED
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_ne
id|TS_DONE
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|losize
op_ne
id|hisize
)paren
(brace
id|cqr
op_assign
id|tape-&gt;discipline-&gt;mtseek
(paren
id|tape
comma
(paren
id|hisize
op_plus
id|losize
)paren
op_div
l_int|2
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cqr
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:ccwg fail&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
id|cqr
suffix:semicolon
id|tape-&gt;wanna_wakeup
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|do_IO
(paren
id|tape-&gt;devinfo.irq
comma
id|cqr-&gt;cpaddr
comma
(paren
r_int
r_int
)paren
id|cqr
comma
l_int|0x00
comma
id|cqr-&gt;options
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|wait_event_interruptible
(paren
id|tape-&gt;wq
comma
id|tape-&gt;wanna_wakeup
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
l_int|NULL
suffix:semicolon
id|tape_free_request
(paren
id|cqr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tape-&gt;kernbuf
)paren
(brace
id|kfree
(paren
id|tape-&gt;kernbuf
)paren
suffix:semicolon
id|tape-&gt;kernbuf
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_eq
id|TS_FAILED
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|hisize
op_assign
(paren
id|hisize
op_plus
id|losize
)paren
op_div
l_int|2
suffix:semicolon
id|cqr
op_assign
id|tape-&gt;discipline-&gt;mtrew
(paren
id|tape
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cqr
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;b:ccwg fail&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
id|cqr
suffix:semicolon
id|tape-&gt;wanna_wakeup
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|do_IO
(paren
id|tape-&gt;devinfo.irq
comma
id|cqr-&gt;cpaddr
comma
(paren
r_int
r_int
)paren
id|cqr
comma
l_int|0x00
comma
id|cqr-&gt;options
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|wait_event_interruptible
(paren
id|tape-&gt;wq
comma
id|tape-&gt;wanna_wakeup
)paren
suffix:semicolon
id|tape-&gt;cqr
op_assign
l_int|NULL
suffix:semicolon
id|tape_free_request
(paren
id|cqr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_eq
id|TS_FAILED
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_ne
id|TS_DONE
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tapestate_get
(paren
id|tape
)paren
op_ne
id|TS_DONE
)paren
(brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tapestate_set
(paren
id|tape
comma
id|TS_IDLE
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|tape-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|losize
op_assign
(paren
id|hisize
op_plus
id|losize
)paren
op_div
l_int|2
op_plus
l_int|1
suffix:semicolon
)brace
id|blk_size
(braket
id|tapeblock_major
)braket
(braket
id|tape-&gt;blk_minor
)braket
op_assign
(paren
id|losize
)paren
op_star
(paren
id|blksize_size
(braket
id|tapeblock_major
)braket
(braket
id|tape-&gt;blk_minor
)braket
op_div
l_int|1024
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
