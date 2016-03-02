macro_line|#ifndef _IEEE1394_TYPES_H
DECL|macro|_IEEE1394_TYPES_H
mdefine_line|#define _IEEE1394_TYPES_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* The great kdev_t changeover in 2.5.x */
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#ifndef minor
DECL|macro|minor
mdefine_line|#define minor(dev) MINOR(dev)
macro_line|#endif
macro_line|#ifndef __devexit_p
DECL|macro|__devexit_p
mdefine_line|#define __devexit_p(x) x
macro_line|#endif
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifndef list_for_each_safe
DECL|macro|list_for_each_safe
mdefine_line|#define list_for_each_safe(pos, n, head) &bslash;&n;&t;for (pos = (head)-&gt;next, n = pos-&gt;next; pos != (head); &bslash;&n;&t;&t;pos = n, n = pos-&gt;next)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,5)
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel pte_offset
macro_line|#endif
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a) &lt; (b) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef MAX
DECL|macro|MAX
mdefine_line|#define MAX(a,b) ((a) &gt; (b) ? (a) : (b))
macro_line|#endif
multiline_comment|/* Compatibility for task/work queues */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,42)
multiline_comment|/* Use task queue */
macro_line|#include &lt;linux/tqueue.h&gt;
DECL|macro|hpsb_queue_struct
mdefine_line|#define hpsb_queue_struct tq_struct
DECL|macro|hpsb_queue_list
mdefine_line|#define hpsb_queue_list list
DECL|macro|hpsb_schedule_work
mdefine_line|#define hpsb_schedule_work(x) schedule_task(x)
DECL|macro|HPSB_INIT_WORK
mdefine_line|#define HPSB_INIT_WORK(x,y,z) INIT_TQUEUE(x,y,z)
DECL|macro|HPSB_PREPARE_WORK
mdefine_line|#define HPSB_PREPARE_WORK(x,y,z) PREPARE_TQUEUE(x,y,z)
macro_line|#else
multiline_comment|/* Use work queue */
macro_line|#include &lt;linux/workqueue.h&gt;
DECL|macro|hpsb_queue_struct
mdefine_line|#define hpsb_queue_struct work_struct
DECL|macro|hpsb_queue_list
mdefine_line|#define hpsb_queue_list entry
DECL|macro|hpsb_schedule_work
mdefine_line|#define hpsb_schedule_work(x) schedule_work(x)
DECL|macro|HPSB_INIT_WORK
mdefine_line|#define HPSB_INIT_WORK(x,y,z) INIT_WORK(x,y,z)
DECL|macro|HPSB_PREPARE_WORK
mdefine_line|#define HPSB_PREPARE_WORK(x,y,z) PREPARE_WORK(x,y,z)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,44)
multiline_comment|/* pci_pool_create changed. does not take the flags arg any longer */
DECL|macro|hpsb_pci_pool_create
mdefine_line|#define hpsb_pci_pool_create(a,b,c,d,e,f) pci_pool_create(a,b,c,d,e,f)
macro_line|#else
DECL|macro|hpsb_pci_pool_create
mdefine_line|#define hpsb_pci_pool_create(a,b,c,d,e,f) pci_pool_create(a,b,c,d,e)
macro_line|#endif
multiline_comment|/* Transaction Label handling */
DECL|struct|hpsb_tlabel_pool
r_struct
id|hpsb_tlabel_pool
(brace
id|DECLARE_BITMAP
c_func
(paren
id|pool
comma
l_int|64
)paren
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|next
id|u8
id|next
suffix:semicolon
DECL|member|allocations
id|u32
id|allocations
suffix:semicolon
DECL|member|count
r_struct
id|semaphore
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HPSB_TPOOL_INIT
mdefine_line|#define HPSB_TPOOL_INIT(_tp)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;CLEAR_BITMAP((_tp)-&gt;pool, 64);&t;&t;&bslash;&n;&t;spin_lock_init(&amp;(_tp)-&gt;lock);&t;&t;&bslash;&n;&t;(_tp)-&gt;next = 0;&t;&t;&t;&bslash;&n;&t;(_tp)-&gt;allocations = 0;&t;&t;&t;&bslash;&n;&t;sema_init(&amp;(_tp)-&gt;count, 63);&t;&t;&bslash;&n;} while(0)
DECL|typedef|quadlet_t
r_typedef
id|u32
id|quadlet_t
suffix:semicolon
DECL|typedef|octlet_t
r_typedef
id|u64
id|octlet_t
suffix:semicolon
DECL|typedef|nodeid_t
r_typedef
id|u16
id|nodeid_t
suffix:semicolon
DECL|typedef|byte_t
r_typedef
id|u8
id|byte_t
suffix:semicolon
DECL|typedef|nodeaddr_t
r_typedef
id|u64
id|nodeaddr_t
suffix:semicolon
DECL|typedef|arm_length_t
r_typedef
id|u16
id|arm_length_t
suffix:semicolon
DECL|macro|BUS_MASK
mdefine_line|#define BUS_MASK  0xffc0
DECL|macro|BUS_SHIFT
mdefine_line|#define BUS_SHIFT 6
DECL|macro|NODE_MASK
mdefine_line|#define NODE_MASK 0x003f
DECL|macro|LOCAL_BUS
mdefine_line|#define LOCAL_BUS 0xffc0
DECL|macro|ALL_NODES
mdefine_line|#define ALL_NODES 0x003f
DECL|macro|NODEID_TO_BUS
mdefine_line|#define NODEID_TO_BUS(nodeid)&t;((nodeid &amp; BUS_MASK) &gt;&gt; BUS_SHIFT)
DECL|macro|NODEID_TO_NODE
mdefine_line|#define NODEID_TO_NODE(nodeid)&t;(nodeid &amp; NODE_MASK)
multiline_comment|/* Can be used to consistently print a node/bus ID. */
DECL|macro|NODE_BUS_FMT
mdefine_line|#define NODE_BUS_FMT&t;&t;&quot;%02d:%04d&quot;
DECL|macro|NODE_BUS_ARGS
mdefine_line|#define NODE_BUS_ARGS(nodeid)&t;NODEID_TO_NODE(nodeid), NODEID_TO_BUS(nodeid)
DECL|macro|HPSB_PRINT
mdefine_line|#define HPSB_PRINT(level, fmt, args...) printk(level &quot;ieee1394: &quot; fmt &quot;&bslash;n&quot; , ## args)
DECL|macro|HPSB_DEBUG
mdefine_line|#define HPSB_DEBUG(fmt, args...) HPSB_PRINT(KERN_DEBUG, fmt , ## args)
DECL|macro|HPSB_INFO
mdefine_line|#define HPSB_INFO(fmt, args...) HPSB_PRINT(KERN_INFO, fmt , ## args)
DECL|macro|HPSB_NOTICE
mdefine_line|#define HPSB_NOTICE(fmt, args...) HPSB_PRINT(KERN_NOTICE, fmt , ## args)
DECL|macro|HPSB_WARN
mdefine_line|#define HPSB_WARN(fmt, args...) HPSB_PRINT(KERN_WARNING, fmt , ## args)
DECL|macro|HPSB_ERR
mdefine_line|#define HPSB_ERR(fmt, args...) HPSB_PRINT(KERN_ERR, fmt , ## args)
DECL|macro|HPSB_PANIC
mdefine_line|#define HPSB_PANIC(fmt, args...) panic(&quot;ieee1394: &quot; fmt &quot;&bslash;n&quot; , ## args)
DECL|macro|HPSB_TRACE
mdefine_line|#define HPSB_TRACE() HPSB_PRINT(KERN_INFO, &quot;TRACE - %s, %s(), line %d&quot;, __FILE__, __FUNCTION__, __LINE__)
macro_line|#ifdef __BIG_ENDIAN
DECL|function|memcpy_le32
r_static
id|__inline__
r_void
op_star
id|memcpy_le32
c_func
(paren
id|u32
op_star
id|dest
comma
r_const
id|u32
op_star
id|__src
comma
r_int
id|count
)paren
(brace
r_void
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
id|u32
op_star
id|src
op_assign
(paren
id|u32
op_star
)paren
id|__src
suffix:semicolon
id|count
op_div_assign
l_int|4
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|dest
op_increment
op_assign
id|swab32p
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
)brace
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#else
DECL|function|memcpy_le32
r_static
id|__inline__
r_void
op_star
id|memcpy_le32
c_func
(paren
id|u32
op_star
id|dest
comma
r_const
id|u32
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_return
id|memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|count
)paren
suffix:semicolon
)brace
macro_line|#endif /* __BIG_ENDIAN */
macro_line|#endif /* _IEEE1394_TYPES_H */
eof
