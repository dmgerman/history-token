macro_line|#ifndef __LINUX__AIO_H
DECL|macro|__LINUX__AIO_H
mdefine_line|#define __LINUX__AIO_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/aio_abi.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|AIO_MAXSEGS
mdefine_line|#define AIO_MAXSEGS&t;&t;4
DECL|macro|AIO_KIOGRP_NR_ATOMIC
mdefine_line|#define AIO_KIOGRP_NR_ATOMIC&t;8
r_struct
id|kioctx
suffix:semicolon
multiline_comment|/* Notes on cancelling a kiocb:&n; *&t;If a kiocb is cancelled, aio_complete may return 0 to indicate &n; *&t;that cancel has not yet disposed of the kiocb.  All cancel &n; *&t;operations *must* call aio_put_req to dispose of the kiocb &n; *&t;to guard against races with the completion code.&n; */
DECL|macro|KIOCB_C_CANCELLED
mdefine_line|#define KIOCB_C_CANCELLED&t;0x01
DECL|macro|KIOCB_C_COMPLETE
mdefine_line|#define KIOCB_C_COMPLETE&t;0x02
DECL|macro|KIOCB_SYNC_KEY
mdefine_line|#define KIOCB_SYNC_KEY&t;&t;(~0U)
DECL|macro|KIOCB_PRIVATE_SIZE
mdefine_line|#define KIOCB_PRIVATE_SIZE&t;(24 * sizeof(long))
multiline_comment|/* ki_flags bits */
DECL|macro|KIF_LOCKED
mdefine_line|#define KIF_LOCKED&t;&t;0
DECL|macro|KIF_KICKED
mdefine_line|#define KIF_KICKED&t;&t;1
DECL|macro|KIF_CANCELLED
mdefine_line|#define KIF_CANCELLED&t;&t;2
DECL|macro|kiocbTryLock
mdefine_line|#define kiocbTryLock(iocb)&t;test_and_set_bit(KIF_LOCKED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbTryKick
mdefine_line|#define kiocbTryKick(iocb)&t;test_and_set_bit(KIF_KICKED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbSetLocked
mdefine_line|#define kiocbSetLocked(iocb)&t;set_bit(KIF_LOCKED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbSetKicked
mdefine_line|#define kiocbSetKicked(iocb)&t;set_bit(KIF_KICKED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbSetCancelled
mdefine_line|#define kiocbSetCancelled(iocb)&t;set_bit(KIF_CANCELLED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbClearLocked
mdefine_line|#define kiocbClearLocked(iocb)&t;clear_bit(KIF_LOCKED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbClearKicked
mdefine_line|#define kiocbClearKicked(iocb)&t;clear_bit(KIF_KICKED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbClearCancelled
mdefine_line|#define kiocbClearCancelled(iocb)&t;clear_bit(KIF_CANCELLED, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbIsLocked
mdefine_line|#define kiocbIsLocked(iocb)&t;test_bit(0, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbIsKicked
mdefine_line|#define kiocbIsKicked(iocb)&t;test_bit(1, &amp;(iocb)-&gt;ki_flags)
DECL|macro|kiocbIsCancelled
mdefine_line|#define kiocbIsCancelled(iocb)&t;test_bit(2, &amp;(iocb)-&gt;ki_flags)
DECL|struct|kiocb
r_struct
id|kiocb
(brace
DECL|member|ki_run_list
r_struct
id|list_head
id|ki_run_list
suffix:semicolon
DECL|member|ki_flags
r_int
id|ki_flags
suffix:semicolon
DECL|member|ki_users
r_int
id|ki_users
suffix:semicolon
DECL|member|ki_key
r_int
id|ki_key
suffix:semicolon
multiline_comment|/* id of this request */
DECL|member|ki_filp
r_struct
id|file
op_star
id|ki_filp
suffix:semicolon
DECL|member|ki_ctx
r_struct
id|kioctx
op_star
id|ki_ctx
suffix:semicolon
multiline_comment|/* may be NULL for sync ops */
DECL|member|ki_cancel
r_int
(paren
op_star
id|ki_cancel
)paren
(paren
r_struct
id|kiocb
op_star
comma
r_struct
id|io_event
op_star
)paren
suffix:semicolon
DECL|member|ki_retry
r_int
(paren
op_star
id|ki_retry
)paren
(paren
r_struct
id|kiocb
op_star
)paren
suffix:semicolon
DECL|member|ki_list
r_struct
id|list_head
id|ki_list
suffix:semicolon
multiline_comment|/* the aio core uses this&n;&t;&t;&t;&t;&t;&t; * for cancellation */
DECL|member|ki_user_obj
r_void
op_star
id|ki_user_obj
suffix:semicolon
multiline_comment|/* pointer to userland&squot;s iocb */
DECL|member|ki_user_data
id|__u64
id|ki_user_data
suffix:semicolon
multiline_comment|/* user&squot;s data for completion */
DECL|member|ki_pos
id|loff_t
id|ki_pos
suffix:semicolon
DECL|member|private
r_char
r_private
(braket
id|KIOCB_PRIVATE_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|is_sync_kiocb
mdefine_line|#define is_sync_kiocb(iocb)&t;((iocb)-&gt;ki_key == KIOCB_SYNC_KEY)
DECL|macro|init_sync_kiocb
mdefine_line|#define init_sync_kiocb(x, filp)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct task_struct *tsk = current;&t;&bslash;&n;&t;&t;(x)-&gt;ki_flags = 0;&t;&t;&t;&bslash;&n;&t;&t;(x)-&gt;ki_users = 1;&t;&t;&t;&bslash;&n;&t;&t;(x)-&gt;ki_key = KIOCB_SYNC_KEY;&t;&t;&bslash;&n;&t;&t;(x)-&gt;ki_filp = (filp);&t;&t;&t;&bslash;&n;&t;&t;(x)-&gt;ki_ctx = &amp;tsk-&gt;active_mm-&gt;default_kioctx;&t;&bslash;&n;&t;&t;(x)-&gt;ki_cancel = NULL;&t;&t;&t;&bslash;&n;&t;&t;(x)-&gt;ki_user_obj = tsk;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|AIO_RING_MAGIC
mdefine_line|#define AIO_RING_MAGIC&t;&t;&t;0xa10a10a1
DECL|macro|AIO_RING_COMPAT_FEATURES
mdefine_line|#define AIO_RING_COMPAT_FEATURES&t;1
DECL|macro|AIO_RING_INCOMPAT_FEATURES
mdefine_line|#define AIO_RING_INCOMPAT_FEATURES&t;0
DECL|struct|aio_ring
r_struct
id|aio_ring
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* kernel internal index number */
DECL|member|nr
r_int
id|nr
suffix:semicolon
multiline_comment|/* number of io_events */
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|compat_features
r_int
id|compat_features
suffix:semicolon
DECL|member|incompat_features
r_int
id|incompat_features
suffix:semicolon
DECL|member|header_length
r_int
id|header_length
suffix:semicolon
multiline_comment|/* size of aio_ring */
DECL|member|io_events
r_struct
id|io_event
id|io_events
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* 128 bytes + ring size */
DECL|macro|aio_ring_avail
mdefine_line|#define aio_ring_avail(info, ring)&t;(((ring)-&gt;head + (info)-&gt;nr - 1 - (ring)-&gt;tail) % (info)-&gt;nr)
DECL|macro|AIO_RING_PAGES
mdefine_line|#define AIO_RING_PAGES&t;8
DECL|struct|aio_ring_info
r_struct
id|aio_ring_info
(brace
DECL|member|mmap_base
r_int
r_int
id|mmap_base
suffix:semicolon
DECL|member|mmap_size
r_int
r_int
id|mmap_size
suffix:semicolon
DECL|member|ring_pages
r_struct
id|page
op_star
op_star
id|ring_pages
suffix:semicolon
DECL|member|ring_lock
id|spinlock_t
id|ring_lock
suffix:semicolon
DECL|member|nr_pages
r_int
id|nr_pages
suffix:semicolon
DECL|member|nr
DECL|member|tail
r_int
id|nr
comma
id|tail
suffix:semicolon
DECL|member|internal_pages
r_struct
id|page
op_star
id|internal_pages
(braket
id|AIO_RING_PAGES
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kioctx
r_struct
id|kioctx
(brace
DECL|member|users
id|atomic_t
id|users
suffix:semicolon
DECL|member|dead
r_int
id|dead
suffix:semicolon
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
multiline_comment|/* This needs improving */
DECL|member|user_id
r_int
r_int
id|user_id
suffix:semicolon
DECL|member|next
r_struct
id|kioctx
op_star
id|next
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|ctx_lock
id|spinlock_t
id|ctx_lock
suffix:semicolon
DECL|member|reqs_active
r_int
id|reqs_active
suffix:semicolon
DECL|member|active_reqs
r_struct
id|list_head
id|active_reqs
suffix:semicolon
multiline_comment|/* used for cancellation */
DECL|member|run_list
r_struct
id|list_head
id|run_list
suffix:semicolon
multiline_comment|/* used for kicked reqs */
DECL|member|max_reqs
r_int
id|max_reqs
suffix:semicolon
DECL|member|ring_info
r_struct
id|aio_ring_info
id|ring_info
suffix:semicolon
DECL|member|wq
r_struct
id|work_struct
id|wq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* prototypes */
r_extern
r_int
id|aio_max_size
suffix:semicolon
r_extern
id|ssize_t
id|FASTCALL
c_func
(paren
id|wait_on_sync_kiocb
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
)paren
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
id|aio_put_req
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|kick_iocb
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
)paren
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
id|aio_complete
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_int
id|res
comma
r_int
id|res2
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__put_ioctx
c_func
(paren
r_struct
id|kioctx
op_star
id|ctx
)paren
)paren
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|exit_aio
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|kioctx
op_star
id|lookup_ioctx
c_func
(paren
r_int
r_int
id|ctx_id
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
id|io_submit_one
c_func
(paren
r_struct
id|kioctx
op_star
id|ctx
comma
r_struct
id|iocb
op_star
id|user_iocb
comma
r_struct
id|iocb
op_star
id|iocb
)paren
)paren
suffix:semicolon
multiline_comment|/* semi private, but used by the 32bit emulations: */
r_struct
id|kioctx
op_star
id|lookup_ioctx
c_func
(paren
r_int
r_int
id|ctx_id
)paren
suffix:semicolon
r_int
id|FASTCALL
c_func
(paren
id|io_submit_one
c_func
(paren
r_struct
id|kioctx
op_star
id|ctx
comma
r_struct
id|iocb
op_star
id|user_iocb
comma
r_struct
id|iocb
op_star
id|iocb
)paren
)paren
suffix:semicolon
DECL|macro|get_ioctx
mdefine_line|#define get_ioctx(kioctx)&t;do { if (unlikely(atomic_read(&amp;(kioctx)-&gt;users) &lt;= 0)) BUG(); atomic_inc(&amp;(kioctx)-&gt;users); } while (0)
DECL|macro|put_ioctx
mdefine_line|#define put_ioctx(kioctx)&t;do { if (unlikely(atomic_dec_and_test(&amp;(kioctx)-&gt;users))) __put_ioctx(kioctx); else if (unlikely(atomic_read(&amp;(kioctx)-&gt;users) &lt; 0)) BUG(); } while (0)
macro_line|#include &lt;linux/aio_abi.h&gt;
DECL|function|list_kiocb
r_static
r_inline
r_struct
id|kiocb
op_star
id|list_kiocb
c_func
(paren
r_struct
id|list_head
op_star
id|h
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|h
comma
r_struct
id|kiocb
comma
id|ki_list
)paren
suffix:semicolon
)brace
multiline_comment|/* for sysctl: */
r_extern
r_int
id|aio_max_nr
comma
id|aio_max_size
comma
id|aio_max_pinned
suffix:semicolon
macro_line|#endif /* __LINUX__AIO_H */
eof
