macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
DECL|macro|DBG
mdefine_line|#define DBG(format, arg...) do { &bslash;&n;printk(KERN_DEBUG &quot;%s: &quot; format &quot;&bslash;n&quot; , __FUNCTION__ , ## arg); &bslash;&n;} while (0)
DECL|struct|capilib_msgidqueue
r_struct
id|capilib_msgidqueue
(brace
DECL|member|next
r_struct
id|capilib_msgidqueue
op_star
id|next
suffix:semicolon
DECL|member|msgid
id|u16
id|msgid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|capilib_ncci
r_struct
id|capilib_ncci
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|applid
id|u16
id|applid
suffix:semicolon
DECL|member|ncci
id|u32
id|ncci
suffix:semicolon
DECL|member|winsize
id|u32
id|winsize
suffix:semicolon
DECL|member|nmsg
r_int
id|nmsg
suffix:semicolon
DECL|member|msgidqueue
r_struct
id|capilib_msgidqueue
op_star
id|msgidqueue
suffix:semicolon
DECL|member|msgidlast
r_struct
id|capilib_msgidqueue
op_star
id|msgidlast
suffix:semicolon
DECL|member|msgidfree
r_struct
id|capilib_msgidqueue
op_star
id|msgidfree
suffix:semicolon
DECL|member|msgidpool
r_struct
id|capilib_msgidqueue
id|msgidpool
(braket
id|CAPI_MAXDATAWINDOW
)braket
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// ---------------------------------------------------------------------------
singleline_comment|// NCCI Handling
DECL|function|mq_init
r_static
r_inline
r_void
id|mq_init
c_func
(paren
r_struct
id|capilib_ncci
op_star
id|np
)paren
(brace
id|u_int
id|i
suffix:semicolon
id|np-&gt;msgidqueue
op_assign
l_int|0
suffix:semicolon
id|np-&gt;msgidlast
op_assign
l_int|0
suffix:semicolon
id|np-&gt;nmsg
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|np-&gt;msgidpool
comma
l_int|0
comma
r_sizeof
(paren
id|np-&gt;msgidpool
)paren
)paren
suffix:semicolon
id|np-&gt;msgidfree
op_assign
op_amp
id|np-&gt;msgidpool
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|np-&gt;winsize
suffix:semicolon
id|i
op_increment
)paren
(brace
id|np-&gt;msgidpool
(braket
id|i
)braket
dot
id|next
op_assign
id|np-&gt;msgidfree
suffix:semicolon
id|np-&gt;msgidfree
op_assign
op_amp
id|np-&gt;msgidpool
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
DECL|function|mq_enqueue
r_static
r_inline
r_int
id|mq_enqueue
c_func
(paren
r_struct
id|capilib_ncci
op_star
id|np
comma
id|u16
id|msgid
)paren
(brace
r_struct
id|capilib_msgidqueue
op_star
id|mq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mq
op_assign
id|np-&gt;msgidfree
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|np-&gt;msgidfree
op_assign
id|mq-&gt;next
suffix:semicolon
id|mq-&gt;msgid
op_assign
id|msgid
suffix:semicolon
id|mq-&gt;next
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;msgidlast
)paren
id|np-&gt;msgidlast-&gt;next
op_assign
id|mq
suffix:semicolon
id|np-&gt;msgidlast
op_assign
id|mq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np-&gt;msgidqueue
)paren
id|np-&gt;msgidqueue
op_assign
id|mq
suffix:semicolon
id|np-&gt;nmsg
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mq_dequeue
r_static
r_inline
r_int
id|mq_dequeue
c_func
(paren
r_struct
id|capilib_ncci
op_star
id|np
comma
id|u16
id|msgid
)paren
(brace
r_struct
id|capilib_msgidqueue
op_star
op_star
id|pp
suffix:semicolon
r_for
c_loop
(paren
id|pp
op_assign
op_amp
id|np-&gt;msgidqueue
suffix:semicolon
op_star
id|pp
suffix:semicolon
id|pp
op_assign
op_amp
(paren
op_star
id|pp
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|pp
)paren
op_member_access_from_pointer
id|msgid
op_eq
id|msgid
)paren
(brace
r_struct
id|capilib_msgidqueue
op_star
id|mq
op_assign
op_star
id|pp
suffix:semicolon
op_star
id|pp
op_assign
id|mq-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|mq
op_eq
id|np-&gt;msgidlast
)paren
id|np-&gt;msgidlast
op_assign
l_int|0
suffix:semicolon
id|mq-&gt;next
op_assign
id|np-&gt;msgidfree
suffix:semicolon
id|np-&gt;msgidfree
op_assign
id|mq
suffix:semicolon
id|np-&gt;nmsg
op_decrement
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|capilib_new_ncci
r_void
id|capilib_new_ncci
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
id|u16
id|applid
comma
id|u32
id|ncci
comma
id|u32
id|winsize
)paren
(brace
r_struct
id|capilib_ncci
op_star
id|np
suffix:semicolon
id|np
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|np
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;capilib_new_ncci: no memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|winsize
OG
id|CAPI_MAXDATAWINDOW
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;capi_new_ncci: winsize %d too big&bslash;n&quot;
comma
id|winsize
)paren
suffix:semicolon
id|winsize
op_assign
id|CAPI_MAXDATAWINDOW
suffix:semicolon
)brace
id|np-&gt;applid
op_assign
id|applid
suffix:semicolon
id|np-&gt;ncci
op_assign
id|ncci
suffix:semicolon
id|np-&gt;winsize
op_assign
id|winsize
suffix:semicolon
id|mq_init
c_func
(paren
id|np
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|np-&gt;list
comma
id|head
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;kcapi: appl %d ncci 0x%x up&quot;
comma
id|applid
comma
id|ncci
)paren
suffix:semicolon
)brace
DECL|variable|capilib_new_ncci
id|EXPORT_SYMBOL
c_func
(paren
id|capilib_new_ncci
)paren
suffix:semicolon
DECL|function|capilib_free_ncci
r_void
id|capilib_free_ncci
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
id|u16
id|applid
comma
id|u32
id|ncci
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|capilib_ncci
op_star
id|np
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
id|head
)paren
(brace
id|np
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|capilib_ncci
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;applid
op_ne
id|applid
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;ncci
op_ne
id|ncci
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;kcapi: appl %d ncci 0x%x down&bslash;n&quot;
comma
id|applid
comma
id|ncci
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|np-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|np
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;capilib_free_ncci: ncci 0x%x not found&bslash;n&quot;
comma
id|ncci
)paren
suffix:semicolon
)brace
DECL|variable|capilib_free_ncci
id|EXPORT_SYMBOL
c_func
(paren
id|capilib_free_ncci
)paren
suffix:semicolon
DECL|function|capilib_release_appl
r_void
id|capilib_release_appl
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
id|u16
id|applid
)paren
(brace
r_struct
id|list_head
op_star
id|l
comma
op_star
id|n
suffix:semicolon
r_struct
id|capilib_ncci
op_star
id|np
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|l
comma
id|n
comma
id|head
)paren
(brace
id|np
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|capilib_ncci
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;applid
op_ne
id|applid
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;kcapi: appl %d ncci 0x%x forced down&bslash;n&quot;
comma
id|applid
comma
id|np-&gt;ncci
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|np-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|np
)paren
suffix:semicolon
)brace
)brace
DECL|variable|capilib_release_appl
id|EXPORT_SYMBOL
c_func
(paren
id|capilib_release_appl
)paren
suffix:semicolon
DECL|function|capilib_release
r_void
id|capilib_release
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|l
comma
op_star
id|n
suffix:semicolon
r_struct
id|capilib_ncci
op_star
id|np
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|l
comma
id|n
comma
id|head
)paren
(brace
id|np
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|capilib_ncci
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;kcapi: appl %d ncci 0x%x forced down&bslash;n&quot;
comma
id|np-&gt;applid
comma
id|np-&gt;ncci
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|np-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|np
)paren
suffix:semicolon
)brace
)brace
DECL|variable|capilib_release
id|EXPORT_SYMBOL
c_func
(paren
id|capilib_release
)paren
suffix:semicolon
DECL|function|capilib_data_b3_req
id|u16
id|capilib_data_b3_req
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
id|u16
id|applid
comma
id|u32
id|ncci
comma
id|u16
id|msgid
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|capilib_ncci
op_star
id|np
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
id|head
)paren
(brace
id|np
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|capilib_ncci
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;applid
op_ne
id|applid
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;ncci
op_ne
id|ncci
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|mq_enqueue
c_func
(paren
id|np
comma
id|msgid
)paren
op_eq
l_int|0
)paren
r_return
id|CAPI_SENDQUEUEFULL
suffix:semicolon
r_return
id|CAPI_NOERROR
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;capilib_data_b3_req: ncci 0x%x not found&bslash;n&quot;
comma
id|ncci
)paren
suffix:semicolon
r_return
id|CAPI_NOERROR
suffix:semicolon
)brace
DECL|variable|capilib_data_b3_req
id|EXPORT_SYMBOL
c_func
(paren
id|capilib_data_b3_req
)paren
suffix:semicolon
DECL|function|capilib_data_b3_conf
r_void
id|capilib_data_b3_conf
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
id|u16
id|applid
comma
id|u32
id|ncci
comma
id|u16
id|msgid
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|capilib_ncci
op_star
id|np
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
id|head
)paren
(brace
id|np
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|capilib_ncci
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;applid
op_ne
id|applid
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;ncci
op_ne
id|ncci
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|mq_dequeue
c_func
(paren
id|np
comma
id|msgid
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kcapi: msgid %hu ncci 0x%x not on queue&bslash;n&quot;
comma
id|msgid
comma
id|ncci
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;capilib_data_b3_conf: ncci 0x%x not found&bslash;n&quot;
comma
id|ncci
)paren
suffix:semicolon
)brace
DECL|variable|capilib_data_b3_conf
id|EXPORT_SYMBOL
c_func
(paren
id|capilib_data_b3_conf
)paren
suffix:semicolon
eof
