multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tapeblock.c&n; *    block device frontend for tape device driver&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *               Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; *&n; ****************************************************************************&n; */
macro_line|#include &quot;tapedefs.h&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/s390dyn.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#ifdef MODULE
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#endif
macro_line|#include &quot;tape.h&quot;
macro_line|#include &quot;tapeblock.h&quot;
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;TBLOCK:&quot;
multiline_comment|/*&n; * file operation structure for tape devices&n; */
DECL|variable|tapeblock_fops
r_static
r_struct
id|block_device_operations
id|tapeblock_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|tapeblock_open
comma
dot
id|release
op_assign
id|tapeblock_release
comma
)brace
suffix:semicolon
DECL|variable|tapeblock_major
r_int
id|tapeblock_major
op_assign
l_int|0
suffix:semicolon
r_static
r_void
id|tape_request_fn
(paren
id|request_queue_t
op_star
id|queue
)paren
suffix:semicolon
r_static
id|request_queue_t
op_star
id|tapeblock_getqueue
(paren
id|kdev_t
id|kdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|devfs_handle_t
DECL|function|tapeblock_mkdevfstree
id|tapeblock_mkdevfstree
(paren
id|tape_dev_t
op_star
id|td
)paren
(brace
id|devfs_handle_t
id|rc
op_assign
l_int|NULL
suffix:semicolon
id|rc
op_assign
id|td-&gt;blk_data.devfs_block_dir
op_assign
id|devfs_mk_dir
(paren
id|td-&gt;devfs_dir
comma
l_string|&quot;block&quot;
comma
id|td
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|NULL
)paren
r_goto
id|out_undo
suffix:semicolon
id|rc
op_assign
id|td-&gt;blk_data.devfs_disc
op_assign
id|devfs_register
c_func
(paren
id|td-&gt;blk_data.devfs_block_dir
comma
l_string|&quot;disc&quot;
comma
id|DEVFS_FL_DEFAULT
comma
id|tapeblock_major
comma
id|td-&gt;first_minor
comma
id|TAPEBLOCK_DEVFSMODE
comma
op_amp
id|tapeblock_fops
comma
id|td
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|NULL
)paren
r_goto
id|out_undo
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_undo
suffix:colon
id|tapeblock_rmdevfstree
c_func
(paren
id|td
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
r_void
DECL|function|tapeblock_rmdevfstree
id|tapeblock_rmdevfstree
(paren
id|tape_dev_t
op_star
id|td
)paren
(brace
r_if
c_cond
(paren
id|td-&gt;blk_data.devfs_disc
)paren
id|devfs_unregister
c_func
(paren
id|td-&gt;blk_data.devfs_disc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|td-&gt;blk_data.devfs_block_dir
)paren
id|devfs_unregister
c_func
(paren
id|td-&gt;blk_data.devfs_block_dir
)paren
suffix:semicolon
)brace
macro_line|#endif
r_void
DECL|function|tapeblock_setup
id|tapeblock_setup
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
(brace
id|blk_queue_hardsect_size
c_func
(paren
op_amp
id|ti-&gt;request_queue
comma
l_int|2048
)paren
suffix:semicolon
id|blk_init_queue
(paren
op_amp
id|td-&gt;blk_data.request_queue
comma
id|tape_request_fn
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|tapeblock_mkdevfstree
c_func
(paren
id|td
)paren
suffix:semicolon
macro_line|#endif
id|set_device_ro
(paren
id|MKDEV
c_func
(paren
id|tapeblock_major
comma
id|td-&gt;first_minor
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
r_int
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
id|tape_dev_t
op_star
id|td
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
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
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
id|PRINT_WARN
c_func
(paren
id|KERN_ERR
l_string|&quot; tape gets major %d for block device&bslash;n&quot;
comma
id|tapeblock_major
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
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_sectors
(braket
id|tapeblock_major
)braket
op_eq
l_int|NULL
)paren
r_goto
id|out_undo_hardsect_size
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
r_goto
id|out_undo_max_sectors
suffix:semicolon
id|blkfront-&gt;device_setup
op_assign
(paren
id|tape_setup_device_t
)paren
id|tapeblock_setup
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|blkfront-&gt;mkdevfstree
op_assign
id|tapeblock_mkdevfstree
suffix:semicolon
id|blkfront-&gt;rmdevfstree
op_assign
id|tapeblock_rmdevfstree
suffix:semicolon
macro_line|#endif
id|blkfront-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tape_first_front
op_eq
l_int|NULL
)paren
(brace
id|tape_first_front
op_assign
id|blkfront
suffix:semicolon
)brace
r_else
(brace
id|temp
op_assign
id|tape_first_front
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
id|td
op_assign
id|tape_first_dev
suffix:semicolon
r_while
c_loop
(paren
id|td
op_ne
l_int|NULL
)paren
(brace
id|tapeblock_setup
c_func
(paren
id|td
)paren
suffix:semicolon
id|td
op_assign
id|td-&gt;next
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_undo_max_sectors
suffix:colon
id|kfree
c_func
(paren
id|max_sectors
(braket
id|tapeblock_major
)braket
)paren
suffix:semicolon
id|out_undo_hardsect_size
suffix:colon
id|out_undo_blk_size
suffix:colon
id|out_undo_bdev
suffix:colon
id|unregister_blkdev
c_func
(paren
id|tapeblock_major
comma
l_string|&quot;tBLK&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|max_sectors
(braket
id|tapeblock_major
)braket
op_assign
l_int|NULL
suffix:semicolon
id|tapeblock_major
op_assign
op_minus
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
r_void
DECL|function|tapeblock_uninit
id|tapeblock_uninit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|tapeblock_major
op_eq
op_minus
l_int|1
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* init failed so there is nothing to clean up */
r_if
c_cond
(paren
id|max_sectors
(braket
id|tapeblock_major
)braket
op_ne
l_int|NULL
)paren
(brace
id|kfree
(paren
id|max_sectors
(braket
id|tapeblock_major
)braket
)paren
suffix:semicolon
id|max_sectors
(braket
id|tapeblock_major
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|unregister_blkdev
c_func
(paren
id|tapeblock_major
comma
l_string|&quot;tBLK&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
suffix:semicolon
)brace
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
id|tape_dev_t
op_star
id|td
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|lockflags
suffix:semicolon
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|6
comma
l_string|&quot;b:open:  %x&bslash;n&quot;
comma
id|td-&gt;first_minor
)paren
suffix:semicolon
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|td
op_assign
id|tape_get_device_by_minor
c_func
(paren
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|td
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tape_state_get
c_func
(paren
id|td
)paren
op_eq
id|TS_NOT_OPER
)paren
(brace
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|6
comma
l_string|&quot;c:nodev&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_rel_lock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tape_state_get
(paren
id|td
)paren
op_ne
id|TS_UNUSED
)paren
(brace
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|6
comma
l_string|&quot;b:dbusy&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out_rel_lock
suffix:semicolon
)brace
id|tape_state_set
(paren
id|td
comma
id|TS_IN_USE
)paren
suffix:semicolon
id|td-&gt;blk_data.position
op_assign
op_minus
l_int|1
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|rc
op_assign
id|tapeblock_mediumdetect
c_func
(paren
id|td
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|s390irq_spin_lock_irqsave
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tape_state_set
(paren
id|td
comma
id|TS_UNUSED
)paren
suffix:semicolon
r_goto
id|out_rel_lock
suffix:semicolon
singleline_comment|// in case of errors, we don&squot;t have a size of the medium
)brace
r_if
c_cond
(paren
id|td-&gt;discipline-&gt;owner
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|td-&gt;discipline-&gt;owner
)paren
suffix:semicolon
id|s390irq_spin_lock_irqsave
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|td-&gt;filp
op_assign
id|filp
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|td
suffix:semicolon
multiline_comment|/* save the dev.info for later reference */
id|out_rel_lock
suffix:colon
id|s390irq_spin_unlock_irqrestore
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|td
op_ne
l_int|NULL
)paren
id|tape_put_device
c_func
(paren
id|td
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
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
id|tape_dev_t
op_star
id|td
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|inode
)paren
op_logical_or
op_logical_neg
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|td
op_assign
id|tape_get_device_by_minor
c_func
(paren
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|td
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s390irq_spin_lock_irqsave
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|6
comma
l_string|&quot;b:release: %x&bslash;n&quot;
comma
id|td-&gt;first_minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tape_state_get
c_func
(paren
id|td
)paren
op_eq
id|TS_IN_USE
)paren
(brace
id|tape_state_set
(paren
id|td
comma
id|TS_UNUSED
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tape_state_get
c_func
(paren
id|td
)paren
op_ne
id|TS_NOT_OPER
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
id|tape_put_device
c_func
(paren
id|td
)paren
suffix:semicolon
id|tape_put_device
c_func
(paren
id|td
)paren
suffix:semicolon
multiline_comment|/* 2x ! */
r_if
c_cond
(paren
id|td-&gt;discipline-&gt;owner
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|td-&gt;discipline-&gt;owner
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
DECL|function|tapeblock_end_request
id|tapeblock_end_request
c_func
(paren
id|tape_dev_t
op_star
id|td
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
id|tape_ccw_req_t
op_star
id|treq
op_assign
id|tape_get_active_ccw_req
c_func
(paren
id|td
)paren
suffix:semicolon
r_if
c_cond
(paren
id|treq
op_eq
l_int|NULL
)paren
(brace
id|uptodate
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|uptodate
op_assign
(paren
id|treq-&gt;rc
op_eq
l_int|0
)paren
suffix:semicolon
singleline_comment|// is the buffer up to date?
r_if
c_cond
(paren
id|uptodate
)paren
(brace
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|6
comma
l_string|&quot;b:done: %x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|treq
)paren
suffix:semicolon
)brace
r_else
(brace
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|3
comma
l_string|&quot;b:failed: %x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|treq
)paren
suffix:semicolon
)brace
singleline_comment|// now inform ll_rw_block about a request status
r_while
c_loop
(paren
(paren
id|bh
op_assign
id|td-&gt;blk_data.current_request-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|td-&gt;blk_data.current_request-&gt;bh
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
id|td-&gt;blk_data.current_request
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
id|td-&gt;blk_data.current_request-&gt;rq_dev
)paren
)paren
suffix:semicolon
macro_line|#endif
id|end_that_request_last
(paren
id|td-&gt;blk_data.current_request
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|treq
op_ne
l_int|NULL
)paren
(brace
id|tape_remove_ccw_req
c_func
(paren
id|td
comma
id|treq
)paren
suffix:semicolon
id|td-&gt;discipline
op_member_access_from_pointer
id|free_bread
c_func
(paren
id|treq
)paren
suffix:semicolon
)brace
id|td-&gt;blk_data.current_request
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|tapeblock_exec_IO
id|tapeblock_exec_IO
(paren
id|tape_dev_t
op_star
id|td
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
id|tape_ccw_req_t
op_star
id|treq
op_assign
id|tape_get_active_ccw_req
c_func
(paren
id|td
)paren
suffix:semicolon
r_if
c_cond
(paren
id|treq
)paren
(brace
singleline_comment|// process done/failed request
r_while
c_loop
(paren
id|treq-&gt;rc
op_ne
l_int|0
op_logical_and
id|td-&gt;blk_data.blk_retries
OG
l_int|0
)paren
(brace
id|td-&gt;blk_data.blk_retries
op_decrement
suffix:semicolon
id|td-&gt;blk_data.position
op_assign
op_minus
l_int|1
suffix:semicolon
id|td-&gt;discipline
op_member_access_from_pointer
id|bread_enable_locate
c_func
(paren
id|treq
)paren
suffix:semicolon
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|3
comma
l_string|&quot;b:retryreq: %x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|treq
)paren
suffix:semicolon
id|rc
op_assign
id|tape_do_io_irq
c_func
(paren
id|td
comma
id|treq
comma
id|TAPE_SCHED_BLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|3
comma
l_string|&quot;b:doIOfail: %x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|treq
)paren
suffix:semicolon
r_continue
suffix:semicolon
singleline_comment|// one retry lost &squot;cause doIO failed
)brace
r_return
suffix:semicolon
)brace
id|tapeblock_end_request
(paren
id|td
)paren
suffix:semicolon
singleline_comment|// check state, inform user, free mem, dev=idl
)brace
r_if
c_cond
(paren
id|TAPE_BUSY
c_func
(paren
id|td
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
singleline_comment|// tape should be idle now, request should be freed!
r_if
c_cond
(paren
id|tape_state_get
(paren
id|td
)paren
op_eq
id|TS_NOT_OPER
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
(paren
op_amp
id|td-&gt;blk_data.request_queue.queue_head
)paren
)paren
(brace
singleline_comment|// nothing more to do or device has dissapeared;)
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|6
comma
l_string|&quot;b:Qempty&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
singleline_comment|// queue is not empty, fetch a request and start IO!
id|req
op_assign
id|td-&gt;blk_data.current_request
op_assign
id|tape_next_request
c_func
(paren
op_amp
id|td-&gt;blk_data.request_queue
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
id|tapeblock_end_request
(paren
id|td
)paren
suffix:semicolon
singleline_comment|// check state, inform user, free mem, dev=idl
id|tapeblock_schedule_exec_io
c_func
(paren
id|td
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|treq
op_assign
id|td-&gt;discipline
op_member_access_from_pointer
id|bread
c_func
(paren
id|req
comma
id|td
comma
id|tapeblock_major
)paren
suffix:semicolon
singleline_comment|//build channel program from request
r_if
c_cond
(paren
op_logical_neg
id|treq
)paren
(brace
singleline_comment|// ccw generation failed. we try again later.
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|3
comma
l_string|&quot;b:cqrNULL&bslash;n&quot;
)paren
suffix:semicolon
id|tapeblock_schedule_exec_io
c_func
(paren
id|td
)paren
suffix:semicolon
id|td-&gt;blk_data.current_request
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|td-&gt;blk_data.blk_retries
op_assign
id|TAPEBLOCK_RETRIES
suffix:semicolon
id|rc
op_assign
id|tape_do_io_irq
c_func
(paren
id|td
comma
id|treq
comma
id|TAPE_SCHED_BLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
singleline_comment|// okay. ssch failed. we try later.
id|tape_sprintf_event
(paren
id|tape_dbf_area
comma
l_int|3
comma
l_string|&quot;b:doIOfail&bslash;n&quot;
)paren
suffix:semicolon
id|tape_remove_ccw_req
c_func
(paren
id|td
comma
id|treq
)paren
suffix:semicolon
id|td-&gt;discipline
op_member_access_from_pointer
id|free_bread
c_func
(paren
id|treq
)paren
suffix:semicolon
id|td-&gt;blk_data.current_request
op_assign
l_int|NULL
suffix:semicolon
id|tapeblock_schedule_exec_io
c_func
(paren
id|td
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
singleline_comment|// our request is in IO. we remove it from the queue and exit
id|tape_dequeue_request
(paren
op_amp
id|td-&gt;blk_data.request_queue
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
id|tape_dev_t
op_star
id|td
)paren
(brace
r_int
id|lockflags
suffix:semicolon
r_if
c_cond
(paren
id|td
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
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tape_state_get
c_func
(paren
id|td
)paren
op_ne
id|TS_IN_USE
)paren
(brace
id|s390irq_spin_unlock_irqrestore
c_func
(paren
id|td-&gt;devinfo.irq
comma
id|lockflags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tapeblock_exec_IO
c_func
(paren
id|td
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
c_func
(paren
id|td-&gt;devinfo.irq
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
id|tape_dev_t
op_star
id|td
)paren
(brace
r_int
id|flags_390irq
comma
id|flags_ior
suffix:semicolon
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|tape-&gt;request_queue
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|q-&gt;queue_lock
comma
id|flags_ior
)paren
suffix:semicolon
id|s390irq_spin_lock_irqsave
c_func
(paren
id|td-&gt;devinfo.irq
comma
id|flags_390irq
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|td-&gt;blk_data.bh_scheduled
comma
l_int|0
)paren
suffix:semicolon
id|tapeblock_exec_IO
c_func
(paren
id|td
)paren
suffix:semicolon
id|s390irq_spin_unlock_irqrestore
c_func
(paren
id|td-&gt;devinfo.irq
comma
id|flags_390irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|q-&gt;queue_lock
comma
id|flags_ior
)paren
suffix:semicolon
)brace
r_void
DECL|function|tapeblock_schedule_exec_io
id|tapeblock_schedule_exec_io
(paren
id|tape_dev_t
op_star
id|td
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
id|td-&gt;blk_data.bh_scheduled
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
id|td-&gt;blk_data.bh_tq.list
)paren
suffix:semicolon
id|td-&gt;blk_data.bh_tq.sync
op_assign
l_int|0
suffix:semicolon
id|td-&gt;blk_data.bh_tq.routine
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
id|td-&gt;blk_data.bh_tq.data
op_assign
id|td
suffix:semicolon
id|queue_task
(paren
op_amp
id|td-&gt;blk_data.bh_tq
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
id|tape_dev_t
op_star
id|td
op_assign
id|tape_get_device_by_queue
c_func
(paren
id|queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|td
op_ne
l_int|NULL
)paren
(brace
id|do_tape_request
c_func
(paren
id|td
)paren
suffix:semicolon
id|tape_put_device
c_func
(paren
id|td
)paren
suffix:semicolon
)brace
)brace
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
id|tape_dev_t
op_star
id|td
op_assign
id|tape_get_device_by_minor
c_func
(paren
id|MINOR
c_func
(paren
id|kdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|td
op_ne
l_int|NULL
)paren
r_return
op_amp
id|td-&gt;blk_data.request_queue
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|tapeblock_mediumdetect
r_int
id|tapeblock_mediumdetect
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
(brace
id|tape_ccw_req_t
op_star
id|treq
suffix:semicolon
r_int
r_int
id|nr_of_blks
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|PRINT_INFO
c_func
(paren
l_string|&quot;Detecting media size...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Rewind */
id|treq
op_assign
id|td-&gt;discipline-&gt;ioctl
(paren
id|td
comma
id|MTREW
comma
l_int|1
comma
op_amp
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|treq
op_eq
l_int|NULL
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|tape_do_io_and_wait
(paren
id|td
comma
id|treq
comma
id|TAPE_WAIT_INTERRUPTIBLE
)paren
suffix:semicolon
id|TAPE_MERGE_RC
c_func
(paren
id|treq
comma
id|rc
)paren
suffix:semicolon
id|tape_free_ccw_req
(paren
id|treq
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
multiline_comment|/* FSF */
id|treq
op_assign
id|td-&gt;discipline-&gt;ioctl
(paren
id|td
comma
id|MTFSF
comma
l_int|1
comma
op_amp
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|treq
op_eq
l_int|NULL
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|tape_do_io_and_wait
(paren
id|td
comma
id|treq
comma
id|TAPE_WAIT_INTERRUPTIBLE
)paren
suffix:semicolon
id|TAPE_MERGE_RC
c_func
(paren
id|treq
comma
id|rc
)paren
suffix:semicolon
id|tape_free_ccw_req
(paren
id|treq
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
multiline_comment|/* TELL */
id|treq
op_assign
id|td-&gt;discipline-&gt;ioctl
(paren
id|td
comma
id|MTTELL
comma
l_int|1
comma
op_amp
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|treq
op_eq
l_int|NULL
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|tape_do_io_and_wait
c_func
(paren
id|td
comma
id|treq
comma
id|TAPE_WAIT_INTERRUPTIBLE
)paren
suffix:semicolon
id|TAPE_MERGE_RC
c_func
(paren
id|treq
comma
id|rc
)paren
suffix:semicolon
id|nr_of_blks
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
(paren
id|treq-&gt;kernbuf
)paren
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t count FM */
id|tape_free_ccw_req
(paren
id|treq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* Rewind */
id|treq
op_assign
id|td-&gt;discipline-&gt;ioctl
(paren
id|td
comma
id|MTREW
comma
l_int|1
comma
op_amp
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|treq
op_eq
l_int|NULL
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|tape_do_io_and_wait
c_func
(paren
id|td
comma
id|treq
comma
id|TAPE_WAIT_INTERRUPTIBLE
)paren
suffix:semicolon
id|TAPE_MERGE_RC
c_func
(paren
id|treq
comma
id|rc
)paren
suffix:semicolon
id|tape_free_ccw_req
(paren
id|treq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
