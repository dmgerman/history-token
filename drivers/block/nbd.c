multiline_comment|/*&n; * Network block device - make block devices work over TCP&n; *&n; * Note that you can not swap over this thing, yet. Seems to work but&n; * deadlocks sometimes - you can not swap over TCP in general.&n; * &n; * Copyright 1997-2000 Pavel Machek &lt;pavel@ucw.cz&gt;&n; * Parts copyright 2001 Steven Whitehouse &lt;steve@chygwyn.com&gt;&n; *&n; * (part of code stolen from loop.c)&n; *&n; * 97-3-25 compiled 0-th version, not yet tested it &n; *   (it did not work, BTW) (later that day) HEY! it works!&n; *   (bit later) hmm, not that much... 2:00am next day:&n; *   yes, it works, but it gives something like 50kB/sec&n; * 97-4-01 complete rewrite to make it possible for many requests at &n; *   once to be processed&n; * 97-4-11 Making protocol independent of endianity etc.&n; * 97-9-13 Cosmetic changes&n; * 98-5-13 Attempt to make 64-bit-clean on 64-bit machines&n; * 99-1-11 Attempt to make 64-bit-clean on 32-bit machines &lt;ankry@mif.pg.gda.pl&gt;&n; * 01-2-27 Fix to store proper blockcount for kernel (calculated using&n; *   BLOCK_SIZE_BITS, not device blocksize) &lt;aga@permonline.ru&gt;&n; * 01-3-11 Make nbd work with new Linux block layer code. It now supports&n; *   plugging like all the other block devices. Also added in MSG_MORE to&n; *   reduce number of partial TCP segments sent. &lt;steve@chygwyn.com&gt;&n; * 01-12-6 Fix deadlock condition by making queue locks independant of&n; *   the transmit lock. &lt;steve@chygwyn.com&gt;&n; * 02-10-11 Allow hung xmit to be aborted via SIGKILL &amp; various fixes.&n; *   &lt;Paul.Clements@SteelEye.com&gt; &lt;James.Bottomley@SteelEye.com&gt;&n; *&n; * possible FIXME: make set_sock / set_blksize / set_size / do_it one syscall&n; * why not: would need verify_area and friends, would share yet another &n; *          structure with userland&n; */
DECL|macro|PARANOIA
mdefine_line|#define PARANOIA
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/nbd.h&gt;
DECL|macro|LO_MAGIC
mdefine_line|#define LO_MAGIC 0x68797548
DECL|variable|nbd_dev
r_static
r_struct
id|nbd_device
id|nbd_dev
(braket
id|MAX_NBD
)braket
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
DECL|function|nbd_end_request
r_static
r_void
id|nbd_end_request
c_func
(paren
r_struct
id|request
op_star
id|req
)paren
(brace
r_int
id|uptodate
op_assign
(paren
id|req-&gt;errors
op_eq
l_int|0
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|request_queue_t
op_star
id|q
op_assign
id|req-&gt;q
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_int
id|nsect
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef PARANOIA
id|requests_out
op_increment
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
id|q-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|bio
op_assign
id|req-&gt;bio
)paren
op_ne
l_int|NULL
)paren
(brace
id|nsect
op_assign
id|bio_sectors
c_func
(paren
id|bio
)paren
suffix:semicolon
id|blk_finished_io
c_func
(paren
id|nsect
)paren
suffix:semicolon
id|req-&gt;bio
op_assign
id|bio-&gt;bi_next
suffix:semicolon
id|bio-&gt;bi_next
op_assign
l_int|NULL
suffix:semicolon
id|bio_endio
c_func
(paren
id|bio
comma
id|nsect
op_lshift
l_int|9
comma
id|uptodate
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
)paren
suffix:semicolon
)brace
id|blk_put_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|q-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
)brace
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
r_struct
id|nbd_device
op_star
id|lo
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
id|lo-&gt;refcnt
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
multiline_comment|/* Allow interception of SIGKILL only&n;&t; * Don&squot;t allow other signals to interrupt the transmission */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
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
id|sigdelsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|sigmask
c_func
(paren
id|SIGKILL
)paren
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
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
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NBD (pid %d: %s) got signal %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|dequeue_signal
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|info
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
comma
id|flags
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|current-&gt;sig-&gt;siglock
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
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
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
id|nbd_device
op_star
id|lo
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
r_struct
id|socket
op_star
id|sock
op_assign
id|lo-&gt;sock
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
id|nbd_cmd
c_func
(paren
id|req
)paren
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
id|down
c_func
(paren
op_amp
id|lo-&gt;tx_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock
op_logical_or
op_logical_neg
id|lo-&gt;sock
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NBD: Attempted sendmsg to closed socket&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
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
id|nbd_cmd
c_func
(paren
id|req
)paren
op_eq
id|NBD_CMD_WRITE
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
id|nbd_cmd
c_func
(paren
id|req
)paren
op_eq
id|NBD_CMD_WRITE
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
id|up
c_func
(paren
op_amp
id|lo-&gt;tx_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
id|error_out
suffix:colon
id|up
c_func
(paren
op_amp
id|lo-&gt;tx_lock
)paren
suffix:semicolon
id|req-&gt;errors
op_increment
suffix:semicolon
)brace
DECL|function|nbd_find_request
r_static
r_struct
id|request
op_star
id|nbd_find_request
c_func
(paren
r_struct
id|nbd_device
op_star
id|lo
comma
r_char
op_star
id|handle
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|request
op_star
id|xreq
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|xreq
comma
id|handle
comma
r_sizeof
(paren
id|xreq
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|lo-&gt;queue_head
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|request
comma
id|queuelist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_ne
id|xreq
)paren
r_continue
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|req-&gt;queuelist
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|req
op_assign
id|nbd_find_request
c_func
(paren
id|lo
comma
id|reply.handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
l_int|NULL
)paren
id|HARDFAIL
c_func
(paren
l_string|&quot;Unexpected reply&quot;
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
id|nbd_cmd
c_func
(paren
id|req
)paren
op_eq
id|NBD_CMD_READ
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
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|req
op_assign
id|nbd_read_stat
c_func
(paren
id|lo
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
id|BUG_ON
c_func
(paren
id|lo-&gt;magic
op_ne
id|LO_MAGIC
)paren
suffix:semicolon
id|nbd_end_request
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
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
id|BUG_ON
c_func
(paren
id|lo-&gt;magic
op_ne
id|LO_MAGIC
)paren
suffix:semicolon
r_do
(brace
id|req
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
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
id|req
op_assign
id|list_entry
c_func
(paren
id|lo-&gt;queue_head.next
comma
r_struct
id|request
comma
id|queuelist
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|req-&gt;queuelist
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
)paren
(brace
id|req-&gt;errors
op_increment
suffix:semicolon
id|nbd_end_request
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|req
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We always wait for result of write, for now. It would be nice to make it optional&n; * in future&n; * if ((req-&gt;cmd == WRITE) &amp;&amp; (lo-&gt;flags &amp; NBD_WRITE_NOCHK)) &n; *   { printk( &quot;Warning: Ignoring result!&bslash;n&quot;); nbd_end_request( req ); }&n; */
DECL|macro|FAIL
macro_line|#undef FAIL
DECL|macro|FAIL
mdefine_line|#define FAIL( s ) { printk( KERN_ERR &quot;%s: &quot; s &quot;&bslash;n&quot;, req-&gt;rq_disk-&gt;disk_name ); goto error_out; }
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
r_while
c_loop
(paren
op_logical_neg
id|blk_queue_empty
c_func
(paren
id|q
)paren
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|elv_next_request
c_func
(paren
id|q
)paren
suffix:semicolon
r_struct
id|nbd_device
op_star
id|lo
suffix:semicolon
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
id|req-&gt;rq_disk-&gt;private_data
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
id|nbd_cmd
c_func
(paren
id|req
)paren
op_assign
id|NBD_CMD_READ
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
id|WRITE
)paren
(brace
id|nbd_cmd
c_func
(paren
id|req
)paren
op_assign
id|NBD_CMD_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|lo-&gt;flags
op_amp
id|NBD_READ_ONLY
)paren
id|FAIL
c_func
(paren
l_string|&quot;Write on read-only&quot;
)paren
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
id|lo-&gt;magic
op_ne
id|LO_MAGIC
)paren
suffix:semicolon
id|requests_in
op_increment
suffix:semicolon
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
id|spin_lock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;file
)paren
(brace
id|spin_unlock
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
l_string|&quot;nbd: failed between accept and semaphore, file lost&bslash;n&quot;
)paren
suffix:semicolon
id|req-&gt;errors
op_increment
suffix:semicolon
id|nbd_end_request
c_func
(paren
id|req
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
)brace
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
id|spin_unlock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|nbd_send_req
c_func
(paren
id|lo
comma
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;errors
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nbd: nbd_send_req failed&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|req-&gt;queuelist
)paren
suffix:semicolon
id|spin_unlock
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
id|spin_lock_irq
c_func
(paren
id|q-&gt;queue_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
r_int
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
id|KERN_INFO
l_string|&quot;NBD_DISCONNECT&bslash;n&quot;
)paren
suffix:semicolon
id|sreq.flags
op_assign
id|REQ_SPECIAL
suffix:semicolon
id|nbd_cmd
c_func
(paren
op_amp
id|sreq
)paren
op_assign
id|NBD_CMD_DISC
suffix:semicolon
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
id|lo
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
id|nbd_clear_que
c_func
(paren
id|lo
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
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
id|spin_unlock
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
(brace
id|spin_unlock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|lo-&gt;file
op_assign
l_int|NULL
suffix:semicolon
id|lo-&gt;sock
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lo-&gt;queue_lock
)paren
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
r_if
c_cond
(paren
id|inode-&gt;i_sock
)paren
(brace
id|lo-&gt;file
op_assign
id|file
suffix:semicolon
id|lo-&gt;sock
op_assign
id|SOCKET_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
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
id|lo-&gt;blksize
op_assign
id|arg
suffix:semicolon
id|temp
op_assign
id|arg
op_rshift
l_int|9
suffix:semicolon
id|lo-&gt;blksize_bits
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
id|lo-&gt;blksize_bits
op_increment
suffix:semicolon
id|temp
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|lo-&gt;bytesize
op_and_assign
op_complement
(paren
id|lo-&gt;blksize
op_minus
l_int|1
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|lo-&gt;disk
comma
id|lo-&gt;bytesize
op_rshift
l_int|9
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NBD_SET_SIZE
suffix:colon
id|lo-&gt;bytesize
op_assign
id|arg
op_amp
op_complement
(paren
id|lo-&gt;blksize
op_minus
l_int|1
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|lo-&gt;disk
comma
id|lo-&gt;bytesize
op_rshift
l_int|9
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NBD_SET_SIZE_BLOCKS
suffix:colon
id|lo-&gt;bytesize
op_assign
(paren
(paren
id|u64
)paren
id|arg
)paren
op_lshift
id|lo-&gt;blksize_bits
suffix:semicolon
id|set_capacity
c_func
(paren
id|lo-&gt;disk
comma
id|lo-&gt;bytesize
op_rshift
l_int|9
)paren
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
multiline_comment|/* on return tidy up in case we have a signal */
multiline_comment|/* Forcibly shutdown the socket causing all listeners&n;&t;&t; * to error&n;&t;&t; *&n;&t;&t; * FIXME: This code is duplicated from sys_shutdown, but&n;&t;&t; * there should be a more generic interface rather than&n;&t;&t; * calling socket ops directly here */
id|down
c_func
(paren
op_amp
id|lo-&gt;tx_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nbd: shutting down socket&bslash;n&quot;
)paren
suffix:semicolon
id|lo-&gt;sock-&gt;ops
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|lo-&gt;sock
comma
id|SEND_SHUTDOWN
op_or
id|RCV_SHUTDOWN
)paren
suffix:semicolon
id|lo-&gt;sock
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|lo-&gt;tx_lock
)paren
suffix:semicolon
id|spin_lock
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
id|lo-&gt;file
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nbd: queue cleared&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|fput
c_func
(paren
id|file
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
l_string|&quot;%s: next = %p, prev = %p. Global: in %d, out %d&bslash;n&quot;
comma
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;disk_name
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
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|nbd_open
comma
dot
id|release
op_assign
id|nbd_release
comma
dot
id|ioctl
op_assign
id|nbd_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * And here should be modules and kernel interface &n; *  (Just smiley confuses emacs :-)&n; */
DECL|variable|nbd_queue
r_static
r_struct
id|request_queue
id|nbd_queue
suffix:semicolon
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
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
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
r_struct
id|gendisk
op_star
id|disk
op_assign
id|alloc_disk
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk
)paren
r_goto
id|out
suffix:semicolon
id|nbd_dev
(braket
id|i
)braket
dot
id|disk
op_assign
id|disk
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|NBD_MAJOR
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
id|NBD_MAJOR
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
l_string|&quot;nbd: registered device at major %d&bslash;n&quot;
comma
id|NBD_MAJOR
)paren
suffix:semicolon
macro_line|#endif
id|blk_init_queue
c_func
(paren
op_amp
id|nbd_queue
comma
id|do_nbd_request
comma
op_amp
id|nbd_lock
)paren
suffix:semicolon
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;nbd&quot;
comma
l_int|NULL
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
r_struct
id|gendisk
op_star
id|disk
op_assign
id|nbd_dev
(braket
id|i
)braket
dot
id|disk
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
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
id|spin_lock_init
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
id|tx_lock
)paren
suffix:semicolon
id|nbd_dev
(braket
id|i
)braket
dot
id|blksize
op_assign
l_int|1024
suffix:semicolon
id|nbd_dev
(braket
id|i
)braket
dot
id|blksize_bits
op_assign
l_int|10
suffix:semicolon
id|nbd_dev
(braket
id|i
)braket
dot
id|bytesize
op_assign
(paren
(paren
id|u64
)paren
l_int|0x7ffffc00
)paren
op_lshift
l_int|10
suffix:semicolon
multiline_comment|/* 2TB */
id|disk-&gt;major
op_assign
id|NBD_MAJOR
suffix:semicolon
id|disk-&gt;first_minor
op_assign
id|i
suffix:semicolon
id|disk-&gt;fops
op_assign
op_amp
id|nbd_fops
suffix:semicolon
id|disk-&gt;private_data
op_assign
op_amp
id|nbd_dev
(braket
id|i
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|disk-&gt;disk_name
comma
l_string|&quot;nbd%d&quot;
comma
id|i
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|disk
comma
l_int|0x3ffffe
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;nbd/%d&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
c_func
(paren
l_int|NULL
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|disk-&gt;major
comma
id|disk-&gt;first_minor
comma
id|S_IFBLK
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|disk-&gt;fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|put_disk
c_func
(paren
id|nbd_dev
(braket
id|i
)braket
dot
id|disk
)paren
suffix:semicolon
r_return
id|err
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
r_int
id|i
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
id|del_gendisk
c_func
(paren
id|nbd_dev
(braket
id|i
)braket
dot
id|disk
)paren
suffix:semicolon
id|put_disk
c_func
(paren
id|nbd_dev
(braket
id|i
)braket
dot
id|disk
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;nbd/%d&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|devfs_remove
c_func
(paren
l_string|&quot;nbd&quot;
)paren
suffix:semicolon
id|blk_cleanup_queue
c_func
(paren
op_amp
id|nbd_queue
)paren
suffix:semicolon
id|unregister_blkdev
c_func
(paren
id|NBD_MAJOR
comma
l_string|&quot;nbd&quot;
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
