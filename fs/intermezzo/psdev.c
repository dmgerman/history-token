multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *              An implementation of a loadable kernel mode driver providing&n; *              multiple kernel/user space bidirectional communications links.&n; *&n; *              Author:         Alan Cox &lt;alan@cymru.net&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              version 2 as published by the Free Software Foundation.&n; *&n; *              Adapted to become the Linux 2.0 Coda pseudo device&n; *              Peter  Braam  &lt;braam@maths.ox.ac.uk&gt;&n; *              Michael Callahan &lt;mjc@emmy.smith.edu&gt;&n; *&n; *              Changes for Linux 2.1&n; *              Copyright (c) 1997 Carnegie-Mellon University&n; *&n; *              Redone again for InterMezzo&n; *              Copyright (c) 1998 Peter J. Braam&n; *              Copyright (c) 2000 Mountain View Data, Inc.&n; *              Copyright (c) 2000 Tacitus Systems, Inc.&n; *              Copyright (c) 2001 Cluster File Systems, Inc.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/lp.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/poll.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
macro_line|#ifdef PRESTO_DEVEL
DECL|variable|presto_print_entry
r_int
id|presto_print_entry
op_assign
l_int|1
suffix:semicolon
DECL|variable|presto_debug
r_int
id|presto_debug
op_assign
l_int|4095
suffix:semicolon
macro_line|#else
DECL|variable|presto_print_entry
r_int
id|presto_print_entry
op_assign
l_int|0
suffix:semicolon
DECL|variable|presto_debug
r_int
id|presto_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Like inode.c (presto_sym_iops), the initializer is just to prevent&n;   izo_channels from appearing as a COMMON symbol (and therefore&n;   interfering with other modules that use the same variable name). */
DECL|variable|izo_channels
r_struct
id|upc_channel
id|izo_channels
(braket
id|MAX_CHANNEL
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|izo_psdev_get_free_channel
r_int
id|izo_psdev_get_free_channel
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|result
op_assign
op_minus
l_int|1
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
id|MAX_CHANNEL
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
(paren
id|izo_channels
(braket
id|i
)braket
dot
id|uc_cache_list
)paren
)paren
)paren
(brace
id|result
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|izo_psdev_setpid
r_int
id|izo_psdev_setpid
c_func
(paren
r_int
id|minor
)paren
(brace
r_struct
id|upc_channel
op_star
id|channel
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
op_logical_or
id|minor
op_ge
id|MAX_CHANNEL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|channel
op_assign
op_amp
(paren
id|izo_channels
(braket
id|minor
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;         * This ioctl is performed by each Lento that starts up&n;         * and wants to do further communication with presto.&n;         */
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Setting current pid to %d channel %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|minor
)paren
suffix:semicolon
id|channel-&gt;uc_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|channel-&gt;uc_processing
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
id|CERROR
c_func
(paren
l_string|&quot;WARNING: setpid &amp; processing not empty!&bslash;n&quot;
)paren
suffix:semicolon
id|lh
op_assign
op_amp
id|channel-&gt;uc_processing
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|lh-&gt;next
)paren
op_ne
op_amp
id|channel-&gt;uc_processing
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
multiline_comment|/* freeing of req and data is done by the sleeper */
id|wake_up
c_func
(paren
op_amp
id|req-&gt;rq_sleep
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|channel-&gt;uc_processing
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;BAD: FAILDED TO CLEAN PROCESSING LIST!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|izo_psdev_setchannel
r_int
id|izo_psdev_setchannel
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
id|fd
)paren
(brace
r_struct
id|file
op_star
id|psdev_file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|psdev_file
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: no psdev_file!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: no cache!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|fput
c_func
(paren
id|psdev_file
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psdev_file-&gt;private_data
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: channel already set!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|fput
c_func
(paren
id|psdev_file
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|psdev_file-&gt;private_data
op_assign
id|cache-&gt;cache_psdev
suffix:semicolon
id|fput
c_func
(paren
id|psdev_file
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_lento_up
r_inline
r_int
id|presto_lento_up
c_func
(paren
r_int
id|minor
)paren
(brace
r_return
id|izo_channels
(braket
id|minor
)braket
dot
id|uc_pid
suffix:semicolon
)brace
DECL|function|presto_psdev_poll
r_static
r_int
r_int
id|presto_psdev_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|upc_channel
op_star
id|channel
op_assign
(paren
r_struct
id|upc_channel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
multiline_comment|/* ENTRY; this will flood you */
r_if
c_cond
(paren
op_logical_neg
id|channel
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: bad psdev file&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
(paren
id|channel-&gt;uc_waitq
)paren
comma
id|wait
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|channel-&gt;uc_pending
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Non-empty pending list.&bslash;n&quot;
)paren
suffix:semicolon
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
multiline_comment|/* EXIT; will flood you */
r_return
id|mask
suffix:semicolon
)brace
multiline_comment|/*&n; *      Receive a message written by Lento to the psdev&n; */
DECL|function|presto_psdev_write
r_static
id|ssize_t
id|presto_psdev_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|upc_channel
op_star
id|channel
op_assign
(paren
r_struct
id|upc_channel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|upc_req
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|izo_upcall_resp
id|hdr
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|channel
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: bad psdev file&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
multiline_comment|/* Peek at the opcode, uniquefier */
r_if
c_cond
(paren
id|count
OL
r_sizeof
(paren
id|hdr
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto_psdev_write: Lento didn&squot;t write full hdr.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|error
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|hdr
comma
id|buf
comma
r_sizeof
(paren
id|hdr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;(process,opc,uniq)=(%d,%d,%d)&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
multiline_comment|/* Look for the message on the processing queue. */
id|lh
op_assign
op_amp
id|channel-&gt;uc_processing
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|lh-&gt;next
)paren
op_ne
op_amp
id|channel-&gt;uc_processing
)paren
(brace
id|tmp
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;rq_unique
op_eq
id|hdr.unique
)paren
(brace
id|req
op_assign
id|tmp
suffix:semicolon
multiline_comment|/* unlink here: keeps search length minimal */
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;rq_chain
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Eureka opc %d uniq %d!&bslash;n&quot;
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;psdev_write: msg (%d, %d) not found&bslash;n&quot;
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
multiline_comment|/* move data into response buffer. */
r_if
c_cond
(paren
id|req-&gt;rq_bufsize
OL
id|count
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;psdev_write: too much cnt: %d, cnt: %d, &quot;
l_string|&quot;opc: %d, uniq: %d.&bslash;n&quot;
comma
id|req-&gt;rq_bufsize
comma
id|count
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
id|count
op_assign
id|req-&gt;rq_bufsize
suffix:semicolon
multiline_comment|/* don&squot;t have more space! */
)brace
id|error
op_assign
id|copy_from_user
c_func
(paren
id|req-&gt;rq_data
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* adjust outsize: good upcalls can be aware of this */
id|req-&gt;rq_rep_size
op_assign
id|count
suffix:semicolon
id|req-&gt;rq_flags
op_or_assign
id|REQ_WRITE
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;rq_sleep
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; *      Read a message from the kernel to Lento&n; */
DECL|function|presto_psdev_read
r_static
id|ssize_t
id|presto_psdev_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|upc_channel
op_star
id|channel
op_assign
(paren
r_struct
id|upc_channel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
r_int
id|result
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|channel
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: bad psdev file&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
(paren
id|channel-&gt;uc_pending
)paren
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_UPCALL
comma
l_string|&quot;Empty pending list in read, not good&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|req
op_assign
id|list_entry
c_func
(paren
(paren
id|channel-&gt;uc_pending.next
)paren
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
(paren
id|req-&gt;rq_chain
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_ASYNC
)paren
)paren
(brace
id|list_add
c_func
(paren
op_amp
(paren
id|req-&gt;rq_chain
)paren
comma
id|channel-&gt;uc_processing.prev
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|req-&gt;rq_flags
op_or_assign
id|REQ_READ
suffix:semicolon
multiline_comment|/* Move the input args into userspace */
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;rq_bufsize
op_le
id|count
)paren
(brace
id|result
op_assign
id|req-&gt;rq_bufsize
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OL
id|req-&gt;rq_bufsize
)paren
(brace
id|CERROR
(paren
l_string|&quot;psdev_read: buffer too small, read %d of %d bytes&bslash;n&quot;
comma
id|count
comma
id|req-&gt;rq_bufsize
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|req-&gt;rq_data
comma
id|result
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* If request was asynchronous don&squot;t enqueue, but free */
r_if
c_cond
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_ASYNC
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;psdev_read: async msg (%d, %d), result %d&bslash;n&quot;
comma
id|req-&gt;rq_opcode
comma
id|req-&gt;rq_unique
comma
id|result
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|req-&gt;rq_data
comma
id|req-&gt;rq_bufsize
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|req
comma
r_sizeof
(paren
op_star
id|req
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|presto_psdev_open
r_static
r_int
id|presto_psdev_open
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
id|file
)paren
(brace
id|ENTRY
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Psdev_open: caller: %d, flags: %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|file-&gt;f_flags
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_psdev_release
r_static
r_int
id|presto_psdev_release
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
id|file
)paren
(brace
r_struct
id|upc_channel
op_star
id|channel
op_assign
(paren
r_struct
id|upc_channel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|channel
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: bad psdev file&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Lento: pid %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|channel-&gt;uc_pid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Wake up clients so they can return. */
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Wake up clients sleeping for pending.&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|lh
op_assign
op_amp
id|channel-&gt;uc_pending
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|lh-&gt;next
)paren
op_ne
op_amp
id|channel-&gt;uc_pending
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
multiline_comment|/* Async requests stay around for a new lento */
r_if
c_cond
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_ASYNC
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/* the sleeper will free the req and data */
id|req-&gt;rq_flags
op_or_assign
id|REQ_DEAD
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;rq_sleep
)paren
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Wake up clients sleeping for processing&bslash;n&quot;
)paren
suffix:semicolon
id|lh
op_assign
op_amp
id|channel-&gt;uc_processing
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|lh-&gt;next
)paren
op_ne
op_amp
id|channel-&gt;uc_processing
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
multiline_comment|/* freeing of req and data is done by the sleeper */
id|req-&gt;rq_flags
op_or_assign
id|REQ_DEAD
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;rq_sleep
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|presto_psdev_fops
r_static
r_struct
id|file_operations
id|presto_psdev_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|presto_psdev_read
comma
dot
id|write
op_assign
id|presto_psdev_write
comma
dot
id|poll
op_assign
id|presto_psdev_poll
comma
dot
id|open
op_assign
id|presto_psdev_open
comma
dot
id|release
op_assign
id|presto_psdev_release
)brace
suffix:semicolon
multiline_comment|/* modules setup */
DECL|variable|intermezzo_psdev
r_static
r_struct
id|miscdevice
id|intermezzo_psdev
op_assign
(brace
id|INTERMEZZO_MINOR
comma
l_string|&quot;intermezzo&quot;
comma
op_amp
id|presto_psdev_fops
)brace
suffix:semicolon
DECL|function|presto_psdev_init
r_int
id|presto_psdev_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|misc_register
c_func
(paren
op_amp
id|intermezzo_psdev
)paren
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: cannot register %d err %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|INTERMEZZO_MINOR
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|izo_channels
comma
l_int|0
comma
r_sizeof
(paren
id|izo_channels
)paren
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
id|MAX_CHANNEL
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|upc_channel
op_star
id|channel
op_assign
op_amp
(paren
id|izo_channels
(braket
id|i
)braket
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|channel-&gt;uc_pending
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|channel-&gt;uc_processing
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|channel-&gt;uc_cache_list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|channel-&gt;uc_waitq
)paren
suffix:semicolon
id|channel-&gt;uc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|channel-&gt;uc_hard
op_assign
l_int|0
suffix:semicolon
id|channel-&gt;uc_no_filter
op_assign
l_int|0
suffix:semicolon
id|channel-&gt;uc_no_journal
op_assign
l_int|0
suffix:semicolon
id|channel-&gt;uc_no_upcall
op_assign
l_int|0
suffix:semicolon
id|channel-&gt;uc_timeout
op_assign
l_int|30
suffix:semicolon
id|channel-&gt;uc_errorval
op_assign
l_int|0
suffix:semicolon
id|channel-&gt;uc_minor
op_assign
id|i
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_psdev_cleanup
r_void
id|presto_psdev_cleanup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|intermezzo_psdev
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
id|MAX_CHANNEL
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|upc_channel
op_star
id|channel
op_assign
op_amp
(paren
id|izo_channels
(braket
id|i
)braket
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|channel-&gt;uc_pending
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Weird, tell Peter: module cleanup and pending list not empty dev %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|channel-&gt;uc_processing
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Weird, tell Peter: module cleanup and processing list not empty dev %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|channel-&gt;uc_cache_list
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Weird, tell Peter: module cleanup and cache listnot empty dev %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|lh
op_assign
id|channel-&gt;uc_pending.next
suffix:semicolon
r_while
c_loop
(paren
id|lh
op_ne
op_amp
id|channel-&gt;uc_pending
)paren
(brace
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
id|lh
op_assign
id|lh-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_ASYNC
)paren
(brace
id|list_del
c_func
(paren
op_amp
(paren
id|req-&gt;rq_chain
)paren
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_UPCALL
comma
l_string|&quot;free pending upcall type %d&bslash;n&quot;
comma
id|req-&gt;rq_opcode
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|req-&gt;rq_data
comma
id|req-&gt;rq_bufsize
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|req
comma
r_sizeof
(paren
r_struct
id|upc_req
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|req-&gt;rq_flags
op_or_assign
id|REQ_DEAD
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;rq_sleep
)paren
suffix:semicolon
)brace
)brace
id|lh
op_assign
op_amp
id|channel-&gt;uc_processing
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|lh-&gt;next
)paren
op_ne
op_amp
id|channel-&gt;uc_processing
)paren
(brace
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
(paren
id|req-&gt;rq_chain
)paren
)paren
suffix:semicolon
id|req-&gt;rq_flags
op_or_assign
id|REQ_DEAD
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;rq_sleep
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * lento_upcall and lento_downcall routines&n; */
DECL|function|lento_waitfor_upcall
r_static
r_inline
r_int
r_int
id|lento_waitfor_upcall
(paren
r_struct
id|upc_channel
op_star
id|channel
comma
r_struct
id|upc_req
op_star
id|req
comma
r_int
id|minor
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
r_int
id|posttime
suffix:semicolon
id|req-&gt;rq_posttime
op_assign
id|posttime
op_assign
id|jiffies
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|req-&gt;rq_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|izo_channels
(braket
id|minor
)braket
dot
id|uc_hard
op_eq
l_int|0
)paren
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_else
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* got a reply */
r_if
c_cond
(paren
id|req-&gt;rq_flags
op_amp
(paren
id|REQ_WRITE
op_or
id|REQ_DEAD
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* these cases only apply when TASK_INTERRUPTIBLE */
r_if
c_cond
(paren
op_logical_neg
id|izo_channels
(braket
id|minor
)braket
dot
id|uc_hard
op_logical_and
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
multiline_comment|/* if this process really wants to die, let it go */
r_if
c_cond
(paren
id|sigismember
c_func
(paren
op_amp
(paren
id|current-&gt;pending.signal
)paren
comma
id|SIGKILL
)paren
op_logical_or
id|sigismember
c_func
(paren
op_amp
(paren
id|current-&gt;pending.signal
)paren
comma
id|SIGINT
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* signal is present: after timeout always return&n;                           really smart idea, probably useless ... */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|req-&gt;rq_posttime
op_plus
id|izo_channels
(braket
id|minor
)braket
dot
id|uc_timeout
op_star
id|HZ
)paren
)paren
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;rq_chain
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|req-&gt;rq_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SPECIAL
comma
l_string|&quot;posttime: %ld, returned: %ld&bslash;n&quot;
comma
id|posttime
comma
id|jiffies
op_minus
id|posttime
)paren
suffix:semicolon
r_return
(paren
id|jiffies
op_minus
id|posttime
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lento_upcall will return an error in the case of&n; * failed communication with Lento _or_ will peek at Lento&n; * reply and return Lento&squot;s error.&n; *&n; * As lento has 2 types of errors, normal errors (positive) and internal&n; * errors (negative), normal errors are negated, while internal errors&n; * are all mapped to -EINTR, while showing a nice warning message. (jh)&n; *&n; * lento_upcall will always free buffer, either directly, when an upcall&n; * is read (in presto_psdev_read), when the filesystem is unmounted, or&n; * when the module is unloaded.&n; */
DECL|function|izo_upc_upcall
r_int
id|izo_upc_upcall
c_func
(paren
r_int
id|minor
comma
r_int
op_star
id|size
comma
r_struct
id|izo_upcall_hdr
op_star
id|buffer
comma
r_int
id|async
)paren
(brace
r_int
r_int
id|runtime
suffix:semicolon
r_struct
id|upc_channel
op_star
id|channel
suffix:semicolon
r_struct
id|izo_upcall_resp
op_star
id|out
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
id|channel
op_assign
op_amp
(paren
id|izo_channels
(braket
id|minor
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel-&gt;uc_no_upcall
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|exit_buf
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|channel-&gt;uc_pid
op_logical_and
op_logical_neg
id|async
)paren
(brace
id|EXIT
suffix:semicolon
id|error
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|exit_buf
suffix:semicolon
)brace
multiline_comment|/* Format the request message. */
id|PRESTO_ALLOC
c_func
(paren
id|req
comma
r_sizeof
(paren
r_struct
id|upc_req
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
id|EXIT
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|exit_buf
suffix:semicolon
)brace
id|req-&gt;rq_data
op_assign
(paren
r_void
op_star
)paren
id|buffer
suffix:semicolon
id|req-&gt;rq_flags
op_assign
l_int|0
suffix:semicolon
id|req-&gt;rq_bufsize
op_assign
op_star
id|size
suffix:semicolon
id|req-&gt;rq_rep_size
op_assign
l_int|0
suffix:semicolon
id|req-&gt;rq_opcode
op_assign
id|buffer-&gt;u_opc
suffix:semicolon
id|req-&gt;rq_unique
op_assign
op_increment
id|channel-&gt;uc_seq
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|req-&gt;rq_sleep
)paren
suffix:semicolon
multiline_comment|/* Fill in the common input args. */
id|buffer-&gt;u_uniq
op_assign
id|req-&gt;rq_unique
suffix:semicolon
id|buffer-&gt;u_async
op_assign
id|async
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
multiline_comment|/* Append msg to pending queue and poke Lento. */
id|list_add
c_func
(paren
op_amp
id|req-&gt;rq_chain
comma
id|channel-&gt;uc_pending.prev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_UPCALL
comma
l_string|&quot;Proc %d waking Lento %d for(opc,uniq) =(%d,%d) msg at %p.&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|channel-&gt;uc_pid
comma
id|req-&gt;rq_opcode
comma
id|req-&gt;rq_unique
comma
id|req
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|channel-&gt;uc_waitq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|async
)paren
(brace
multiline_comment|/* req, rq_data are freed in presto_psdev_read for async */
id|req-&gt;rq_flags
op_assign
id|REQ_ASYNC
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We can be interrupted while we wait for Lento to process&n;         * our request.  If the interrupt occurs before Lento has read&n;         * the request, we dequeue and return. If it occurs after the&n;         * read but before the reply, we dequeue, send a signal&n;         * message, and return. If it occurs after the reply we ignore&n;         * it. In no case do we want to restart the syscall.  If it&n;         * was interrupted by a lento shutdown (psdev_close), return&n;         * ENODEV.  */
multiline_comment|/* Go to sleep.  Wake up on signals only after the timeout. */
id|runtime
op_assign
id|lento_waitfor_upcall
c_func
(paren
id|channel
comma
id|req
comma
id|minor
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_TIMING
comma
l_string|&quot;opc: %d time: %ld uniq: %d size: %d&bslash;n&quot;
comma
id|req-&gt;rq_opcode
comma
id|jiffies
op_minus
id|req-&gt;rq_posttime
comma
id|req-&gt;rq_unique
comma
id|req-&gt;rq_rep_size
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_UPCALL
comma
l_string|&quot;..process %d woken up by Lento for req at 0x%x, data at %x&bslash;n&quot;
comma
id|current-&gt;pid
comma
(paren
r_int
)paren
id|req
comma
(paren
r_int
)paren
id|req-&gt;rq_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel-&gt;uc_pid
)paren
(brace
multiline_comment|/* i.e. Lento is still alive */
multiline_comment|/* Op went through, interrupt or not we go on */
r_if
c_cond
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_WRITE
)paren
(brace
id|out
op_assign
(paren
r_struct
id|izo_upcall_resp
op_star
)paren
id|req-&gt;rq_data
suffix:semicolon
multiline_comment|/* here we map positive Lento errors to kernel errors */
r_if
c_cond
(paren
id|out-&gt;result
OL
l_int|0
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Tell Peter: Lento returns negative error %d, for oc %d!&bslash;n&quot;
comma
id|out-&gt;result
comma
id|out-&gt;opcode
)paren
suffix:semicolon
id|out-&gt;result
op_assign
id|EINVAL
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|out-&gt;result
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_UPCALL
comma
l_string|&quot;upcall: (u,o,r) (%d, %d, %d) out at %p&bslash;n&quot;
comma
id|out-&gt;unique
comma
id|out-&gt;opcode
comma
id|out-&gt;result
comma
id|out
)paren
suffix:semicolon
op_star
id|size
op_assign
id|req-&gt;rq_rep_size
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|exit_req
suffix:semicolon
)brace
multiline_comment|/* Interrupted before lento read it. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_READ
)paren
op_logical_and
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_UPCALL
comma
l_string|&quot;Interrupt before read: (op,un)=(%d,%d), flags %x&bslash;n&quot;
comma
id|req-&gt;rq_opcode
comma
id|req-&gt;rq_unique
comma
id|req-&gt;rq_flags
)paren
suffix:semicolon
multiline_comment|/* perhaps the best way to convince the app to give up? */
id|error
op_assign
op_minus
id|EINTR
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|exit_req
suffix:semicolon
)brace
multiline_comment|/* interrupted after Lento did its read, send signal */
r_if
c_cond
(paren
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_READ
)paren
op_logical_and
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_UPCALL
comma
l_string|&quot;Interrupt after read: op = %d.%d, flags = %x&bslash;n&quot;
comma
id|req-&gt;rq_opcode
comma
id|req-&gt;rq_unique
comma
id|req-&gt;rq_flags
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
r_else
(brace
id|CERROR
c_func
(paren
l_string|&quot;Lento: Strange interruption - tell Peter.&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* If lento died i.e. !UC_OPEN(channel) */
id|CERROR
c_func
(paren
l_string|&quot;lento_upcall: Lento dead on (op,un) (%d.%d) flags %d&bslash;n&quot;
comma
id|req-&gt;rq_opcode
comma
id|req-&gt;rq_unique
comma
id|req-&gt;rq_flags
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
id|exit_req
suffix:colon
id|PRESTO_FREE
c_func
(paren
id|req
comma
r_sizeof
(paren
r_struct
id|upc_req
)paren
)paren
suffix:semicolon
id|exit_buf
suffix:colon
r_return
id|error
suffix:semicolon
)brace
eof
