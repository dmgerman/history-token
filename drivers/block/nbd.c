multiline_comment|/*&n; * Network block device - make block devices work over TCP&n; *&n; * Note that you can not swap over this thing, yet. Seems to work but&n; * deadlocks sometimes - you can not swap over TCP in general.&n; * &n; * Copyright 1997-2000 Pavel Machek &lt;pavel@ucw.cz&gt;&n; * Parts copyright 2001 Steven Whitehouse &lt;steve@chygwyn.com&gt;&n; *&n; * (part of code stolen from loop.c)&n; *&n; * 97-3-25 compiled 0-th version, not yet tested it &n; *   (it did not work, BTW) (later that day) HEY! it works!&n; *   (bit later) hmm, not that much... 2:00am next day:&n; *   yes, it works, but it gives something like 50kB/sec&n; * 97-4-01 complete rewrite to make it possible for many requests at &n; *   once to be processed&n; * 97-4-11 Making protocol independent of endianity etc.&n; * 97-9-13 Cosmetic changes&n; * 98-5-13 Attempt to make 64-bit-clean on 64-bit machines&n; * 99-1-11 Attempt to make 64-bit-clean on 32-bit machines &lt;ankry@mif.pg.gda.pl&gt;&n; * 01-2-27 Fix to store proper blockcount for kernel (calculated using&n; *   BLOCK_SIZE_BITS, not device blocksize) &lt;aga@permonline.ru&gt;&n; * 01-3-11 Make nbd work with new Linux block layer code. It now supports&n; *   plugging like all the other block devices. Also added in MSG_MORE to&n; *   reduce number of partial TCP segments sent. &lt;steve@chygwyn.com&gt;&n; *&n; * possible FIXME: make set_sock / set_blksize / set_size / do_it one syscall&n; * why not: would need verify_area and friends, would share yet another &n; *          structure with userland&n; */
DECL|macro|PARANOIA
mdefine_line|#define PARANOIA
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR NBD_MAJOR
macro_line|#include &lt;linux/nbd.h&gt;
DECL|macro|LO_MAGIC
mdefine_line|#define LO_MAGIC 0x68797548
DECL|variable|nbd_blksizes
r_static
r_int
id|nbd_blksizes
(braket
id|MAX_NBD
)braket
suffix:semicolon
DECL|variable|nbd_blksize_bits
r_static
r_int
id|nbd_blksize_bits
(braket
id|MAX_NBD
)braket
suffix:semicolon
DECL|variable|nbd_sizes
r_static
r_int
id|nbd_sizes
(braket
id|MAX_NBD
)braket
suffix:semicolon
DECL|variable|nbd_bytesizes
r_static
id|u64
id|nbd_bytesizes
(braket
id|MAX_NBD
)braket
suffix:semicolon
DECL|variable|nbd_dev
r_static
r_struct
id|nbd_device
id|nbd_dev
(braket
id|MAX_NBD
)braket
suffix:semicolon
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
DECL|variable|nbd_lock
r_static
id|spinlock_t
id|nbd_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|DEBUG
mdefine_line|#define DEBUG( s )
multiline_comment|/* #define DEBUG( s ) printk( s ) &n; */
macro_line|#ifdef PARANOIA
DECL|variable|requests_in
r_static
r_int
id|requests_in
suffix:semicolon
DECL|variable|requests_out
r_static
r_int
id|requests_out
suffix:semicolon
macro_line|#endif
DECL|function|nbd_open
r_static
r_int
id|nbd_open
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
r_int
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_NBD
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|nbd_dev
(braket
id|dev
)braket
dot
id|refcnt
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Send or receive packet.&n; */
DECL|function|nbd_xmit
r_static
r_int
id|nbd_xmit
c_func
(paren
r_int
id|send
comma
r_struct
id|socket
op_star
id|sock
comma
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_int
id|msg_flags
)paren
(brace
id|mm_segment_t
id|oldfs
suffix:semicolon
r_int
id|result
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|iovec
id|iov
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|sigset_t
id|oldset
suffix:semicolon
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|oldset
op_assign
id|current-&gt;blocked
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
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
r_do
(brace
id|sock-&gt;sk-&gt;allocation
op_assign
id|GFP_NOIO
suffix:semicolon
id|iov.iov_base
op_assign
id|buf
suffix:semicolon
id|iov.iov_len
op_assign
id|size
suffix:semicolon
id|msg.msg_name
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
id|msg.msg_control
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_controllen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_flags
op_assign
id|msg_flags
op_or
id|MSG_NOSIGNAL
suffix:semicolon
r_if
c_cond
(paren
id|send
)paren
id|result
op_assign
id|sock_sendmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|size
)paren
suffix:semicolon
r_else
id|result
op_assign
id|sock_recvmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
(brace
macro_line|#ifdef PARANOIA
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NBD: %s - sock=%ld at buf=%ld, size=%d returned %d.&bslash;n&quot;
comma
id|send
ques
c_cond
l_string|&quot;send&quot;
suffix:colon
l_string|&quot;receive&quot;
comma
(paren
r_int
)paren
id|sock
comma
(paren
r_int
)paren
id|buf
comma
id|size
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
id|size
op_sub_assign
id|result
suffix:semicolon
id|buf
op_add_assign
id|result
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|oldset
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|FAIL
mdefine_line|#define FAIL( s ) { printk( KERN_ERR &quot;NBD: &quot; s &quot;(result %d)&bslash;n&quot;, result ); goto error_out; }
DECL|function|nbd_send_req
r_void
id|nbd_send_req
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|request
op_star
id|req
)paren
(brace
r_int
id|result
comma
id|rw
comma
id|i
comma
id|flags
suffix:semicolon
r_struct
id|nbd_request
id|request
suffix:semicolon
r_int
r_int
id|size
op_assign
id|req-&gt;nr_sectors
op_lshift
l_int|9
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;NBD: sending control, &quot;
)paren
suffix:semicolon
id|request.magic
op_assign
id|htonl
c_func
(paren
id|NBD_REQUEST_MAGIC
)paren
suffix:semicolon
id|request.type
op_assign
id|htonl
c_func
(paren
id|req-&gt;flags
)paren
suffix:semicolon
id|request.from
op_assign
id|cpu_to_be64
c_func
(paren
(paren
id|u64
)paren
id|req-&gt;sector
op_lshift
l_int|9
)paren
suffix:semicolon
id|request.len
op_assign
id|htonl
c_func
(paren
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|request.handle
comma
op_amp
id|req
comma
r_sizeof
(paren
id|req
)paren
)paren
suffix:semicolon
id|rw
op_assign
id|rq_data_dir
c_func
(paren
id|req
)paren
suffix:semicolon
id|result
op_assign
id|nbd_xmit
c_func
(paren
l_int|1
comma
id|sock
comma
(paren
r_char
op_star
)paren
op_amp
id|request
comma
r_sizeof
(paren
id|request
)paren
comma
id|rw
op_amp
id|WRITE
ques
c_cond
id|MSG_MORE
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
id|FAIL
c_func
(paren
l_string|&quot;Sendmsg failed for control.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_amp
id|WRITE
)paren
(brace
r_struct
id|bio
op_star
id|bio
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we are really probing at internals to determine&n;&t;&t; * whether to set MSG_MORE or not...&n;&t;&t; */
id|rq_for_each_bio
c_func
(paren
id|bio
comma
id|req
)paren
(brace
r_struct
id|bio_vec
op_star
id|bvec
suffix:semicolon
id|bio_for_each_segment
c_func
(paren
id|bvec
comma
id|bio
comma
id|i
)paren
(brace
id|flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
OL
(paren
id|bio-&gt;bi_vcnt
op_minus
l_int|1
)paren
)paren
op_logical_or
id|bio-&gt;bi_next
)paren
id|flags
op_assign
id|MSG_MORE
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;data, &quot;
)paren
suffix:semicolon
id|result
op_assign
id|nbd_xmit
c_func
(paren
l_int|1
comma
id|sock
comma
id|page_address
c_func
(paren
id|bvec-&gt;bv_page
)paren
op_plus
id|bvec-&gt;bv_offset
comma
id|bvec-&gt;bv_len
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
id|FAIL
c_func
(paren
l_string|&quot;Send data failed.&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
suffix:semicolon
id|error_out
suffix:colon
id|req-&gt;errors
op_increment
suffix:semicolon
)brace
DECL|macro|HARDFAIL
mdefine_line|#define HARDFAIL( s ) { printk( KERN_ERR &quot;NBD: &quot; s &quot;(result %d)&bslash;n&quot;, result ); lo-&gt;harderror = result; return NULL; }
DECL|function|nbd_read_stat
r_struct
id|request
op_star
id|nbd_read_stat
c_func
(paren
r_struct
id|nbd_device
op_star
id|lo
)paren
multiline_comment|/* NULL returned = something went wrong, inform userspace       */
(brace
r_int
id|result
suffix:semicolon
r_struct
id|nbd_reply
id|reply
suffix:semicolon
r_struct
id|request
op_star
id|xreq
comma
op_star
id|req
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;reading control, &quot;
)paren
suffix:semicolon
id|reply.magic
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
id|nbd_xmit
c_func
(paren
l_int|0
comma
id|lo-&gt;sock
comma
(paren
r_char
op_star
)paren
op_amp
id|reply
comma
r_sizeof
(paren
id|reply
)paren
comma
id|MSG_WAITALL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
id|HARDFAIL
c_func
(paren
l_string|&quot;Recv control failed.&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|xreq
comma
id|reply.handle
comma
r_sizeof
(paren
id|xreq
)paren
)paren
suffix:semicolon
id|req
op_assign
id|blkdev_entry_prev_request
c_func
(paren
op_amp
id|lo-&gt;queue_head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xreq
op_ne
id|req
)paren
id|FAIL
c_func
(paren
l_string|&quot;Unexpected handle received.&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;ok, &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohl
c_func
(paren
id|reply.magic
)paren
op_ne
id|NBD_REPLY_MAGIC
)paren
id|HARDFAIL
c_func
(paren
l_string|&quot;Not enough magic.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohl
c_func
(paren
id|reply.error
)paren
)paren
id|FAIL
c_func
(paren
l_string|&quot;Other side returned error.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|req
)paren
op_eq
id|READ
)paren
(brace
r_struct
id|bio
op_star
id|bio
op_assign
id|req-&gt;bio
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;data, &quot;
)paren
suffix:semicolon
r_do
(brace
id|result
op_assign
id|nbd_xmit
c_func
(paren
l_int|0
comma
id|lo-&gt;sock
comma
id|bio_data
c_func
(paren
id|bio
)paren
comma
id|bio-&gt;bi_size
comma
id|MSG_WAITALL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
id|HARDFAIL
c_func
(paren
l_string|&quot;Recv data failed.&quot;
)paren
suffix:semicolon
id|bio
op_assign
id|bio-&gt;bi_next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|bio
)paren
(brace
suffix:semicolon
)brace
)brace
id|DEBUG
c_func
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|req
suffix:semicolon
multiline_comment|/* Can we get here? Yes, if other side returns error */
id|error_out
suffix:colon
id|req-&gt;errors
op_increment
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
DECL|function|nbd_do_it
r_void
id|nbd_do_it
c_func
(paren
r_struct
id|nbd_device
op_star
id|lo
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
id|down
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|up
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|req
op_assign
id|nbd_read_stat
c_func
(paren
id|lo
)paren
suffix:semicolon
id|down
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;req should never be null&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef PARANOIA
r_if
c_cond
(paren
id|req
op_ne
id|blkdev_entry_prev_request
c_func
(paren
op_amp
id|lo-&gt;queue_head
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;NBD: I have problem...&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lo
op_ne
op_amp
id|nbd_dev
(braket
id|MINOR
c_func
(paren
id|req-&gt;rq_dev
)paren
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;NBD: request corrupted!&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lo-&gt;magic
op_ne
id|LO_MAGIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;NBD: nbd_dev[] corrupted: Not enough magic&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#endif
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|up
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|nbd_end_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|down
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|up
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
)brace
DECL|function|nbd_clear_que
r_void
id|nbd_clear_que
c_func
(paren
r_struct
id|nbd_device
op_star
id|lo
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
macro_line|#ifdef PARANOIA
r_if
c_cond
(paren
id|lo-&gt;magic
op_ne
id|LO_MAGIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NBD: nbd_dev[] corrupted: Not enough magic when clearing!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|lo-&gt;queue_head
)paren
)paren
(brace
id|req
op_assign
id|blkdev_entry_prev_request
c_func
(paren
op_amp
id|lo-&gt;queue_head
)paren
suffix:semicolon
macro_line|#ifdef PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;NBD: panic, panic, panic&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lo
op_ne
op_amp
id|nbd_dev
(braket
id|MINOR
c_func
(paren
id|req-&gt;rq_dev
)paren
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;NBD: request corrupted when clearing!&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif
id|req-&gt;errors
op_increment
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|nbd_end_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We always wait for result of write, for now. It would be nice to make it optional&n; * in future&n; * if ((req-&gt;cmd == WRITE) &amp;&amp; (lo-&gt;flags &amp; NBD_WRITE_NOCHK)) &n; *   { printk( &quot;Warning: Ignoring result!&bslash;n&quot;); nbd_end_request( req ); }&n; */
DECL|macro|FAIL
macro_line|#undef FAIL
DECL|macro|FAIL
mdefine_line|#define FAIL( s ) { printk( KERN_ERR &quot;NBD, minor %d: &quot; s &quot;&bslash;n&quot;, dev ); goto error_out; }
DECL|function|do_nbd_request
r_static
r_void
id|do_nbd_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_int
id|dev
op_assign
l_int|0
suffix:semicolon
r_struct
id|nbd_device
op_star
id|lo
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|QUEUE_EMPTY
)paren
(brace
id|req
op_assign
id|CURRENT
suffix:semicolon
macro_line|#ifdef PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
id|FAIL
c_func
(paren
l_string|&quot;que not empty but no request?&quot;
)paren
suffix:semicolon
macro_line|#endif
id|dev
op_assign
id|MINOR
c_func
(paren
id|req-&gt;rq_dev
)paren
suffix:semicolon
macro_line|#ifdef PARANOIA
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_NBD
)paren
id|FAIL
c_func
(paren
l_string|&quot;Minor too big.&quot;
)paren
suffix:semicolon
multiline_comment|/* Probably can not happen */
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|req-&gt;flags
op_amp
id|REQ_CMD
)paren
)paren
r_goto
id|error_out
suffix:semicolon
id|lo
op_assign
op_amp
id|nbd_dev
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;file
)paren
id|FAIL
c_func
(paren
l_string|&quot;Request when not-ready.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq_data_dir
c_func
(paren
id|req
)paren
op_eq
id|WRITE
)paren
op_logical_and
(paren
id|lo-&gt;flags
op_amp
id|NBD_READ_ONLY
)paren
)paren
id|FAIL
c_func
(paren
l_string|&quot;Write on read-only&quot;
)paren
suffix:semicolon
macro_line|#ifdef PARANOIA
r_if
c_cond
(paren
id|lo-&gt;magic
op_ne
id|LO_MAGIC
)paren
id|FAIL
c_func
(paren
l_string|&quot;nbd[] is not magical!&quot;
)paren
suffix:semicolon
id|requests_in
op_increment
suffix:semicolon
macro_line|#endif
id|req-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
id|down
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|req-&gt;queuelist
comma
op_amp
id|lo-&gt;queue_head
)paren
suffix:semicolon
id|nbd_send_req
c_func
(paren
id|lo-&gt;sock
comma
id|req
)paren
suffix:semicolon
multiline_comment|/* Why does this block?         */
id|up
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
id|error_out
suffix:colon
id|req-&gt;errors
op_increment
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
id|nbd_end_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|nbd_ioctl
r_static
r_int
id|nbd_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|nbd_device
op_star
id|lo
suffix:semicolon
r_int
id|dev
comma
id|error
comma
id|temp
suffix:semicolon
r_struct
id|request
id|sreq
suffix:semicolon
multiline_comment|/* Anyone capable of this syscall can do *real bad* things */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_NBD
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|lo
op_assign
op_amp
id|nbd_dev
(braket
id|dev
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NBD_DISCONNECT
suffix:colon
id|printk
c_func
(paren
l_string|&quot;NBD_DISCONNECT&bslash;n&quot;
)paren
suffix:semicolon
id|sreq.flags
op_assign
id|REQ_SPECIAL
suffix:semicolon
multiline_comment|/* FIXME: interpet as shutdown cmd */
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;sock
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|nbd_send_req
c_func
(paren
id|lo-&gt;sock
comma
op_amp
id|sreq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NBD_CLEAR_SOCK
suffix:colon
id|down
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|nbd_clear_que
c_func
(paren
id|lo
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
id|lo-&gt;queue_head
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nbd: Some requests are in progress -&gt; can not turn off.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|file
op_assign
id|lo-&gt;file
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|lo-&gt;file
op_assign
l_int|NULL
suffix:semicolon
id|lo-&gt;sock
op_assign
l_int|NULL
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NBD_SET_SOCK
suffix:colon
r_if
c_cond
(paren
id|lo-&gt;file
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|file
op_assign
id|fget
c_func
(paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* N.B. Should verify that it&squot;s a socket */
id|lo-&gt;file
op_assign
id|file
suffix:semicolon
id|lo-&gt;sock
op_assign
op_amp
id|inode-&gt;u.socket_i
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
r_case
id|NBD_SET_BLKSIZE
suffix:colon
r_if
c_cond
(paren
(paren
id|arg
op_amp
(paren
id|arg
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|arg
OL
l_int|512
)paren
op_logical_or
(paren
id|arg
OG
id|PAGE_SIZE
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|nbd_blksizes
(braket
id|dev
)braket
op_assign
id|arg
suffix:semicolon
id|temp
op_assign
id|arg
op_rshift
l_int|9
suffix:semicolon
id|nbd_blksize_bits
(braket
id|dev
)braket
op_assign
l_int|9
suffix:semicolon
r_while
c_loop
(paren
id|temp
OG
l_int|1
)paren
(brace
id|nbd_blksize_bits
(braket
id|dev
)braket
op_increment
suffix:semicolon
id|temp
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|nbd_bytesizes
(braket
id|dev
)braket
op_and_assign
op_complement
(paren
id|nbd_blksizes
(braket
id|dev
)braket
op_minus
l_int|1
)paren
suffix:semicolon
id|nbd_sizes
(braket
id|dev
)braket
op_assign
id|nbd_bytesizes
(braket
id|dev
)braket
op_rshift
id|BLOCK_SIZE_BITS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NBD_SET_SIZE
suffix:colon
id|nbd_bytesizes
(braket
id|dev
)braket
op_assign
id|arg
op_amp
op_complement
(paren
id|nbd_blksizes
(braket
id|dev
)braket
op_minus
l_int|1
)paren
suffix:semicolon
id|nbd_sizes
(braket
id|dev
)braket
op_assign
id|nbd_bytesizes
(braket
id|dev
)braket
op_rshift
id|BLOCK_SIZE_BITS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NBD_SET_SIZE_BLOCKS
suffix:colon
id|nbd_bytesizes
(braket
id|dev
)braket
op_assign
(paren
(paren
id|u64
)paren
id|arg
)paren
op_lshift
id|nbd_blksize_bits
(braket
id|dev
)braket
suffix:semicolon
id|nbd_sizes
(braket
id|dev
)braket
op_assign
id|nbd_bytesizes
(braket
id|dev
)braket
op_rshift
id|BLOCK_SIZE_BITS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NBD_DO_IT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;file
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|nbd_do_it
c_func
(paren
id|lo
)paren
suffix:semicolon
r_return
id|lo-&gt;harderror
suffix:semicolon
r_case
id|NBD_CLEAR_QUE
suffix:colon
id|nbd_clear_que
c_func
(paren
id|lo
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef PARANOIA
r_case
id|NBD_PRINT_DEBUG
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NBD device %d: next = %p, prev = %p. Global: in %d, out %d&bslash;n&quot;
comma
id|dev
comma
id|lo-&gt;queue_head.next
comma
id|lo-&gt;queue_head.prev
comma
id|requests_in
comma
id|requests_out
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#endif
r_case
id|BLKGETSIZE
suffix:colon
r_return
id|put_user
c_func
(paren
id|nbd_bytesizes
(braket
id|dev
)braket
op_rshift
l_int|9
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKGETSIZE64
suffix:colon
r_return
id|put_user
c_func
(paren
(paren
id|u64
)paren
id|nbd_bytesizes
(braket
id|dev
)braket
comma
(paren
id|u64
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|nbd_release
r_static
r_int
id|nbd_release
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
id|nbd_device
op_star
id|lo
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_NBD
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|lo
op_assign
op_amp
id|nbd_dev
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|lo-&gt;refcnt
op_le
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;nbd_release: refcount(%d) &lt;= 0&bslash;n&quot;
comma
id|lo-&gt;refcnt
)paren
suffix:semicolon
id|lo-&gt;refcnt
op_decrement
suffix:semicolon
multiline_comment|/* N.B. Doesn&squot;t lo-&gt;file need an fput?? */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nbd_fops
r_static
r_struct
id|block_device_operations
id|nbd_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|open
suffix:colon
id|nbd_open
comma
id|release
suffix:colon
id|nbd_release
comma
id|ioctl
suffix:colon
id|nbd_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * And here should be modules and kernel interface &n; *  (Just smiley confuses emacs :-)&n; */
DECL|function|nbd_init
r_static
r_int
id|__init
id|nbd_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|nbd_request
)paren
op_ne
l_int|28
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Sizeof nbd_request needs to be 28 in order to work!&bslash;n&quot;
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
id|register_blkdev
c_func
(paren
id|MAJOR_NR
comma
l_string|&quot;nbd&quot;
comma
op_amp
id|nbd_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to get major number %d for NBD&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
l_string|&quot;nbd: registered device at major %d&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
macro_line|#endif
id|blksize_size
(braket
id|MAJOR_NR
)braket
op_assign
id|nbd_blksizes
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|nbd_sizes
suffix:semicolon
id|blk_init_queue
c_func
(paren
id|BLK_DEFAULT_QUEUE
c_func
(paren
id|MAJOR_NR
)paren
comma
id|do_nbd_request
comma
op_amp
id|nbd_lock
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
id|MAX_NBD
suffix:semicolon
id|i
op_increment
)paren
(brace
id|nbd_dev
(braket
id|i
)braket
dot
id|refcnt
op_assign
l_int|0
suffix:semicolon
id|nbd_dev
(braket
id|i
)braket
dot
id|file
op_assign
l_int|NULL
suffix:semicolon
id|nbd_dev
(braket
id|i
)braket
dot
id|magic
op_assign
id|LO_MAGIC
suffix:semicolon
id|nbd_dev
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|nbd_dev
(braket
id|i
)braket
dot
id|queue_head
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|nbd_dev
(braket
id|i
)braket
dot
id|queue_lock
)paren
suffix:semicolon
id|nbd_blksizes
(braket
id|i
)braket
op_assign
l_int|1024
suffix:semicolon
id|nbd_blksize_bits
(braket
id|i
)braket
op_assign
l_int|10
suffix:semicolon
id|nbd_bytesizes
(braket
id|i
)braket
op_assign
l_int|0x7ffffc00
suffix:semicolon
multiline_comment|/* 2GB */
id|nbd_sizes
(braket
id|i
)braket
op_assign
id|nbd_bytesizes
(braket
id|i
)braket
op_rshift
id|BLOCK_SIZE_BITS
suffix:semicolon
id|register_disk
c_func
(paren
l_int|NULL
comma
id|MKDEV
c_func
(paren
id|MAJOR_NR
comma
id|i
)paren
comma
l_int|1
comma
op_amp
id|nbd_fops
comma
id|nbd_bytesizes
(braket
id|i
)braket
op_rshift
l_int|9
)paren
suffix:semicolon
)brace
id|devfs_handle
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;nbd&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_register_series
(paren
id|devfs_handle
comma
l_string|&quot;%u&quot;
comma
id|MAX_NBD
comma
id|DEVFS_FL_DEFAULT
comma
id|MAJOR_NR
comma
l_int|0
comma
id|S_IFBLK
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|nbd_fops
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nbd_cleanup
r_static
r_void
id|__exit
id|nbd_cleanup
c_func
(paren
r_void
)paren
(brace
id|devfs_unregister
(paren
id|devfs_handle
)paren
suffix:semicolon
id|blk_cleanup_queue
c_func
(paren
id|BLK_DEFAULT_QUEUE
c_func
(paren
id|MAJOR_NR
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unregister_blkdev
c_func
(paren
id|MAJOR_NR
comma
l_string|&quot;nbd&quot;
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;nbd: cleanup_module failed&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;nbd: module cleaned up.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|nbd_init
id|module_init
c_func
(paren
id|nbd_init
)paren
suffix:semicolon
DECL|variable|nbd_cleanup
id|module_exit
c_func
(paren
id|nbd_cleanup
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Network Block Device&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
