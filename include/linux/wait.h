macro_line|#ifndef _LINUX_WAIT_H
DECL|macro|_LINUX_WAIT_H
mdefine_line|#define _LINUX_WAIT_H
DECL|macro|WNOHANG
mdefine_line|#define WNOHANG&t;&t;0x00000001
DECL|macro|WUNTRACED
mdefine_line|#define WUNTRACED&t;0x00000002
DECL|macro|__WNOTHREAD
mdefine_line|#define __WNOTHREAD&t;0x20000000&t;/* Don&squot;t wait on children of other threads in this group */
DECL|macro|__WALL
mdefine_line|#define __WALL&t;&t;0x40000000&t;/* Wait on all children, regardless of type */
DECL|macro|__WCLONE
mdefine_line|#define __WCLONE&t;0x80000000&t;/* Wait only on non-SIGCHLD children */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * Temporary debugging help until all code is converted to the new&n; * waitqueue usage.&n; */
DECL|macro|WAITQUEUE_DEBUG
mdefine_line|#define WAITQUEUE_DEBUG 0
macro_line|#if WAITQUEUE_DEBUG
r_extern
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|WQ_BUG
mdefine_line|#define WQ_BUG() do { &bslash;&n;&t;printk(&quot;wq bug, forcing oops.&bslash;n&quot;); &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
DECL|macro|CHECK_MAGIC
mdefine_line|#define CHECK_MAGIC(x) if (x != (long)&amp;(x)) &bslash;&n;&t;{ printk(&quot;bad magic %lx (should be %lx), &quot;, (long)x, (long)&amp;(x)); WQ_BUG(); }
DECL|macro|CHECK_MAGIC_WQHEAD
mdefine_line|#define CHECK_MAGIC_WQHEAD(x) do { &bslash;&n;&t;if (x-&gt;__magic != (long)&amp;(x-&gt;__magic)) { &bslash;&n;&t;&t;printk(&quot;bad magic %lx (should be %lx, creator %lx), &quot;, &bslash;&n;&t;&t;&t;x-&gt;__magic, (long)&amp;(x-&gt;__magic), x-&gt;__creator); &bslash;&n;&t;&t;WQ_BUG(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
DECL|struct|__wait_queue
r_struct
id|__wait_queue
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|WQ_FLAG_EXCLUSIVE
mdefine_line|#define WQ_FLAG_EXCLUSIVE&t;0x01
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|task_list
r_struct
id|list_head
id|task_list
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
DECL|member|__waker
r_int
id|__waker
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|typedef|wait_queue_t
r_typedef
r_struct
id|__wait_queue
id|wait_queue_t
suffix:semicolon
multiline_comment|/*&n; * &squot;dual&squot; spinlock architecture. Can be switched between spinlock_t and&n; * rwlock_t locks via changing this define. Since waitqueues are quite&n; * decoupled in the new architecture, lightweight &squot;simple&squot; spinlocks give&n; * us slightly better latencies and smaller waitqueue structure size.&n; */
DECL|macro|USE_RW_WAIT_QUEUE_SPINLOCK
mdefine_line|#define USE_RW_WAIT_QUEUE_SPINLOCK 0
macro_line|#if USE_RW_WAIT_QUEUE_SPINLOCK
DECL|macro|wq_lock_t
macro_line|# define wq_lock_t rwlock_t
DECL|macro|WAITQUEUE_RW_LOCK_UNLOCKED
macro_line|# define WAITQUEUE_RW_LOCK_UNLOCKED RW_LOCK_UNLOCKED
DECL|macro|wq_read_lock
macro_line|# define wq_read_lock read_lock
DECL|macro|wq_read_lock_irqsave
macro_line|# define wq_read_lock_irqsave read_lock_irqsave
DECL|macro|wq_read_unlock_irqrestore
macro_line|# define wq_read_unlock_irqrestore read_unlock_irqrestore
DECL|macro|wq_read_unlock
macro_line|# define wq_read_unlock read_unlock
DECL|macro|wq_write_lock_irq
macro_line|# define wq_write_lock_irq write_lock_irq
DECL|macro|wq_write_lock_irqsave
macro_line|# define wq_write_lock_irqsave write_lock_irqsave
DECL|macro|wq_write_unlock_irqrestore
macro_line|# define wq_write_unlock_irqrestore write_unlock_irqrestore
DECL|macro|wq_write_unlock
macro_line|# define wq_write_unlock write_unlock
macro_line|#else
DECL|macro|wq_lock_t
macro_line|# define wq_lock_t spinlock_t
DECL|macro|WAITQUEUE_RW_LOCK_UNLOCKED
macro_line|# define WAITQUEUE_RW_LOCK_UNLOCKED SPIN_LOCK_UNLOCKED
DECL|macro|wq_read_lock
macro_line|# define wq_read_lock spin_lock
DECL|macro|wq_read_lock_irqsave
macro_line|# define wq_read_lock_irqsave spin_lock_irqsave
DECL|macro|wq_read_unlock
macro_line|# define wq_read_unlock spin_unlock
DECL|macro|wq_read_unlock_irqrestore
macro_line|# define wq_read_unlock_irqrestore spin_unlock_irqrestore
DECL|macro|wq_write_lock_irq
macro_line|# define wq_write_lock_irq spin_lock_irq
DECL|macro|wq_write_lock_irqsave
macro_line|# define wq_write_lock_irqsave spin_lock_irqsave
DECL|macro|wq_write_unlock_irqrestore
macro_line|# define wq_write_unlock_irqrestore spin_unlock_irqrestore
DECL|macro|wq_write_unlock
macro_line|# define wq_write_unlock spin_unlock
macro_line|#endif
DECL|struct|__wait_queue_head
r_struct
id|__wait_queue_head
(brace
DECL|member|lock
id|wq_lock_t
id|lock
suffix:semicolon
DECL|member|task_list
r_struct
id|list_head
id|task_list
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
DECL|member|__creator
r_int
id|__creator
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|typedef|wait_queue_head_t
r_typedef
r_struct
id|__wait_queue_head
id|wait_queue_head_t
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|macro|__WAITQUEUE_DEBUG_INIT
macro_line|# define __WAITQUEUE_DEBUG_INIT(name) &bslash;&n;&t;&t;, (long)&amp;(name).__magic, 0
DECL|macro|__WAITQUEUE_HEAD_DEBUG_INIT
macro_line|# define __WAITQUEUE_HEAD_DEBUG_INIT(name) &bslash;&n;&t;&t;, (long)&amp;(name).__magic, (long)&amp;(name).__magic
macro_line|#else
DECL|macro|__WAITQUEUE_DEBUG_INIT
macro_line|# define __WAITQUEUE_DEBUG_INIT(name)
DECL|macro|__WAITQUEUE_HEAD_DEBUG_INIT
macro_line|# define __WAITQUEUE_HEAD_DEBUG_INIT(name)
macro_line|#endif
DECL|macro|__WAITQUEUE_INITIALIZER
mdefine_line|#define __WAITQUEUE_INITIALIZER(name,task) &bslash;&n;&t;{ 0x0, task, { NULL, NULL } __WAITQUEUE_DEBUG_INIT(name)}
DECL|macro|DECLARE_WAITQUEUE
mdefine_line|#define DECLARE_WAITQUEUE(name,task) &bslash;&n;&t;wait_queue_t name = __WAITQUEUE_INITIALIZER(name,task)
DECL|macro|__WAIT_QUEUE_HEAD_INITIALIZER
mdefine_line|#define __WAIT_QUEUE_HEAD_INITIALIZER(name) &bslash;&n;{ WAITQUEUE_RW_LOCK_UNLOCKED, { &amp;(name).task_list, &amp;(name).task_list } &bslash;&n;&t;&t;__WAITQUEUE_HEAD_DEBUG_INIT(name)}
DECL|macro|DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define DECLARE_WAIT_QUEUE_HEAD(name) &bslash;&n;&t;wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
DECL|function|init_waitqueue_head
r_static
r_inline
r_void
id|init_waitqueue_head
c_func
(paren
id|wait_queue_head_t
op_star
id|q
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|q-&gt;lock
op_assign
id|WAITQUEUE_RW_LOCK_UNLOCKED
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|q-&gt;task_list
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|q-&gt;__magic
op_assign
(paren
r_int
)paren
op_amp
id|q-&gt;__magic
suffix:semicolon
id|q-&gt;__creator
op_assign
(paren
r_int
)paren
id|current_text_addr
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|init_waitqueue_entry
r_static
r_inline
r_void
id|init_waitqueue_entry
c_func
(paren
id|wait_queue_t
op_star
id|q
comma
r_struct
id|task_struct
op_star
id|p
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|q
op_logical_or
op_logical_neg
id|p
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|q-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|q-&gt;task
op_assign
id|p
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|q-&gt;__magic
op_assign
(paren
r_int
)paren
op_amp
id|q-&gt;__magic
suffix:semicolon
macro_line|#endif
)brace
DECL|function|waitqueue_active
r_static
r_inline
r_int
id|waitqueue_active
c_func
(paren
id|wait_queue_head_t
op_star
id|q
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
id|CHECK_MAGIC_WQHEAD
c_func
(paren
id|q
)paren
suffix:semicolon
macro_line|#endif
r_return
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;task_list
)paren
suffix:semicolon
)brace
DECL|function|__add_wait_queue
r_static
r_inline
r_void
id|__add_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|head
comma
id|wait_queue_t
op_star
r_new
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|head
op_logical_or
op_logical_neg
r_new
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
id|CHECK_MAGIC_WQHEAD
c_func
(paren
id|head
)paren
suffix:semicolon
id|CHECK_MAGIC
c_func
(paren
r_new
op_member_access_from_pointer
id|__magic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head-&gt;task_list.next
op_logical_or
op_logical_neg
id|head-&gt;task_list.prev
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|task_list
comma
op_amp
id|head-&gt;task_list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Used for wake-one threads:&n; */
DECL|function|__add_wait_queue_tail
r_static
r_inline
r_void
id|__add_wait_queue_tail
c_func
(paren
id|wait_queue_head_t
op_star
id|head
comma
id|wait_queue_t
op_star
r_new
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|head
op_logical_or
op_logical_neg
r_new
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
id|CHECK_MAGIC_WQHEAD
c_func
(paren
id|head
)paren
suffix:semicolon
id|CHECK_MAGIC
c_func
(paren
r_new
op_member_access_from_pointer
id|__magic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head-&gt;task_list.next
op_logical_or
op_logical_neg
id|head-&gt;task_list.prev
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|list_add_tail
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|task_list
comma
op_amp
id|head-&gt;task_list
)paren
suffix:semicolon
)brace
DECL|function|__remove_wait_queue
r_static
r_inline
r_void
id|__remove_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|head
comma
id|wait_queue_t
op_star
id|old
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|old
)paren
id|WQ_BUG
c_func
(paren
)paren
suffix:semicolon
id|CHECK_MAGIC
c_func
(paren
id|old-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|list_del
c_func
(paren
op_amp
id|old-&gt;task_list
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
