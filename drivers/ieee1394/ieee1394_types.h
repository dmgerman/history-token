macro_line|#ifndef _IEEE1394_TYPES_H
DECL|macro|_IEEE1394_TYPES_H
mdefine_line|#define _IEEE1394_TYPES_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
macro_line|#include &quot;linux22compat.h&quot;
macro_line|#else
DECL|macro|V22_COMPAT_MOD_INC_USE_COUNT
mdefine_line|#define V22_COMPAT_MOD_INC_USE_COUNT do {} while (0)
DECL|macro|V22_COMPAT_MOD_DEC_USE_COUNT
mdefine_line|#define V22_COMPAT_MOD_DEC_USE_COUNT do {} while (0)
DECL|macro|OWNER_THIS_MODULE
mdefine_line|#define OWNER_THIS_MODULE owner: THIS_MODULE,
DECL|macro|INIT_TQ_LINK
mdefine_line|#define INIT_TQ_LINK(tq) INIT_LIST_HEAD(&amp;(tq).list)
DECL|macro|INIT_TQ_HEAD
mdefine_line|#define INIT_TQ_HEAD(tq) INIT_LIST_HEAD(&amp;(tq))
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,18)
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#else
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#endif
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a) &lt; (b) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef MAX
DECL|macro|MAX
mdefine_line|#define MAX(a,b) ((a) &gt; (b) ? (a) : (b))
macro_line|#endif
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
DECL|macro|BUS_MASK
mdefine_line|#define BUS_MASK  0xffc0
DECL|macro|NODE_MASK
mdefine_line|#define NODE_MASK 0x003f
DECL|macro|LOCAL_BUS
mdefine_line|#define LOCAL_BUS 0xffc0
DECL|macro|ALL_NODES
mdefine_line|#define ALL_NODES 0x003f
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
id|src
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
