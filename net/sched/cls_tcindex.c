multiline_comment|/*&n; * net/sched/cls_tcindex.c&t;Packet classifier for skb-&gt;tc_index&n; *&n; * Written 1998,1999 by Werner Almesberger, EPFL ICA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;net/route.h&gt;
multiline_comment|/*&n; * Not quite sure if we need all the xchgs Alexey uses when accessing things.&n; * Can always add them later ... :)&n; */
multiline_comment|/*&n; * Passing parameters to the root seems to be done more awkwardly than really&n; * necessary. At least, u32 doesn&squot;t seem to use such dirty hacks. To be&n; * verified. FIXME.&n; */
DECL|macro|PERFECT_HASH_THRESHOLD
mdefine_line|#define PERFECT_HASH_THRESHOLD&t;64&t;/* use perfect hash if not bigger */
DECL|macro|DEFAULT_HASH_SIZE
mdefine_line|#define DEFAULT_HASH_SIZE&t;64&t;/* optimized for diffserv */
macro_line|#if 1 /* control */
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
macro_line|#if 0 /* data */
mdefine_line|#define D2PRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|D2PRINTK
mdefine_line|#define D2PRINTK(format,args...)
macro_line|#endif
DECL|macro|PRIV
mdefine_line|#define&t;PRIV(tp)&t;((struct tcindex_data *) (tp)-&gt;root)
DECL|struct|tcindex_filter_result
r_struct
id|tcindex_filter_result
(brace
DECL|member|police
r_struct
id|tcf_police
op_star
id|police
suffix:semicolon
DECL|member|res
r_struct
id|tcf_result
id|res
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcindex_filter
r_struct
id|tcindex_filter
(brace
DECL|member|key
id|__u16
id|key
suffix:semicolon
DECL|member|result
r_struct
id|tcindex_filter_result
id|result
suffix:semicolon
DECL|member|next
r_struct
id|tcindex_filter
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcindex_data
r_struct
id|tcindex_data
(brace
DECL|member|perfect
r_struct
id|tcindex_filter_result
op_star
id|perfect
suffix:semicolon
multiline_comment|/* perfect hash; NULL if none */
DECL|member|h
r_struct
id|tcindex_filter
op_star
op_star
id|h
suffix:semicolon
multiline_comment|/* imperfect hash; only used if !perfect;&n;&t;&t;&t;&t;      NULL if unused */
DECL|member|mask
id|__u16
id|mask
suffix:semicolon
multiline_comment|/* AND key with mask */
DECL|member|shift
r_int
id|shift
suffix:semicolon
multiline_comment|/* shift ANDed key to the right */
DECL|member|hash
r_int
id|hash
suffix:semicolon
multiline_comment|/* hash table size; 0 if undefined */
DECL|member|alloc_hash
r_int
id|alloc_hash
suffix:semicolon
multiline_comment|/* allocated size */
DECL|member|fall_through
r_int
id|fall_through
suffix:semicolon
multiline_comment|/* 0: only classify if explicit match */
)brace
suffix:semicolon
DECL|function|lookup
r_static
r_struct
id|tcindex_filter_result
op_star
id|lookup
c_func
(paren
r_struct
id|tcindex_data
op_star
id|p
comma
id|__u16
id|key
)paren
(brace
r_struct
id|tcindex_filter
op_star
id|f
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;perfect
)paren
r_return
id|p-&gt;perfect
(braket
id|key
)braket
dot
id|res
dot
r_class
ques
c_cond
id|p-&gt;perfect
op_plus
id|key
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;h
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|p-&gt;h
(braket
id|key
op_mod
id|p-&gt;hash
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;key
op_eq
id|key
)paren
r_return
op_amp
id|f-&gt;result
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|tcindex_classify
r_static
r_int
id|tcindex_classify
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_result
op_star
id|res
)paren
(brace
r_struct
id|tcindex_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|tp
)paren
suffix:semicolon
r_struct
id|tcindex_filter_result
op_star
id|f
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;tcindex_classify(skb %p,tp %p,res %p),p %p&bslash;n&quot;
comma
id|skb
comma
id|tp
comma
id|res
comma
id|p
)paren
suffix:semicolon
id|f
op_assign
id|lookup
c_func
(paren
id|p
comma
(paren
id|skb-&gt;tc_index
op_amp
id|p-&gt;mask
)paren
op_rshift
id|p-&gt;shift
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;fall_through
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|res-&gt;classid
op_assign
id|TC_H_MAKE
c_func
(paren
id|TC_H_MAJ
c_func
(paren
id|tp-&gt;q-&gt;handle
)paren
comma
(paren
id|skb-&gt;tc_index
op_amp
id|p-&gt;mask
)paren
op_rshift
id|p-&gt;shift
)paren
suffix:semicolon
id|res
op_member_access_from_pointer
r_class
op_assign
l_int|0
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;alg 0x%x&bslash;n&quot;
comma
id|res-&gt;classid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|res
op_assign
id|f-&gt;res
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;map 0x%x&bslash;n&quot;
comma
id|res-&gt;classid
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|f-&gt;police
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
id|tcf_police
c_func
(paren
id|skb
comma
id|f-&gt;police
)paren
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;police %d&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tcindex_get
r_static
r_int
r_int
id|tcindex_get
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
id|u32
id|handle
)paren
(brace
r_struct
id|tcindex_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|tp
)paren
suffix:semicolon
r_struct
id|tcindex_filter_result
op_star
id|r
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_get(tp %p,handle 0x%08x)&bslash;n&quot;
comma
id|tp
comma
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;perfect
op_logical_and
id|handle
op_ge
id|p-&gt;alloc_hash
)paren
r_return
l_int|0
suffix:semicolon
id|r
op_assign
id|lookup
c_func
(paren
id|PRIV
c_func
(paren
id|tp
)paren
comma
id|handle
)paren
suffix:semicolon
r_return
id|r
op_logical_and
id|r-&gt;res
dot
r_class
ques
c_cond
(paren
r_int
r_int
)paren
id|r
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|tcindex_put
r_static
r_void
id|tcindex_put
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|f
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_put(tp %p,f 0x%lx)&bslash;n&quot;
comma
id|tp
comma
id|f
)paren
suffix:semicolon
)brace
DECL|function|tcindex_init
r_static
r_int
id|tcindex_init
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
r_struct
id|tcindex_data
op_star
id|p
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_init(tp %p)&bslash;n&quot;
comma
id|tp
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tcindex_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|tp-&gt;root
op_assign
id|p
suffix:semicolon
id|p-&gt;perfect
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;h
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;hash
op_assign
l_int|0
suffix:semicolon
id|p-&gt;mask
op_assign
l_int|0xffff
suffix:semicolon
id|p-&gt;shift
op_assign
l_int|0
suffix:semicolon
id|p-&gt;fall_through
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tcindex_delete
r_static
r_int
id|tcindex_delete
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|tcindex_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|tp
)paren
suffix:semicolon
r_struct
id|tcindex_filter_result
op_star
id|r
op_assign
(paren
r_struct
id|tcindex_filter_result
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|tcindex_filter
op_star
id|f
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|cl
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_delete(tp %p,arg 0x%lx),p %p,f %p&bslash;n&quot;
comma
id|tp
comma
id|arg
comma
id|p
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;perfect
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;res
dot
r_class
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
suffix:semicolon
r_struct
id|tcindex_filter
op_star
op_star
id|walk
op_assign
l_int|NULL
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
id|p-&gt;hash
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|walk
op_assign
id|p-&gt;h
op_plus
id|i
suffix:semicolon
op_star
id|walk
suffix:semicolon
id|walk
op_assign
op_amp
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
op_amp
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|result
op_eq
id|r
)paren
r_goto
id|found
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
id|found
suffix:colon
id|f
op_assign
op_star
id|walk
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
op_star
id|walk
op_assign
id|f-&gt;next
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
id|cl
op_assign
id|__cls_set_class
c_func
(paren
op_amp
id|r-&gt;res
dot
r_class
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
)paren
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|unbind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|cl
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
id|tcf_police_release
c_func
(paren
id|r-&gt;police
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|f
)paren
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * There are no parameters for tcindex_init, so we overload tcindex_change&n; */
DECL|function|tcindex_change
r_static
r_int
id|tcindex_change
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|base
comma
id|u32
id|handle
comma
r_struct
id|rtattr
op_star
op_star
id|tca
comma
r_int
r_int
op_star
id|arg
)paren
(brace
r_struct
id|tcindex_filter_result
id|new_filter_result
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no policing */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* no classification */
)brace
suffix:semicolon
r_struct
id|rtattr
op_star
id|opt
op_assign
id|tca
(braket
id|TCA_OPTIONS
op_minus
l_int|1
)braket
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_TCINDEX_MAX
)braket
suffix:semicolon
r_struct
id|tcindex_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|tp
)paren
suffix:semicolon
r_struct
id|tcindex_filter
op_star
id|f
suffix:semicolon
r_struct
id|tcindex_filter_result
op_star
id|r
op_assign
(paren
r_struct
id|tcindex_filter_result
op_star
)paren
op_star
id|arg
suffix:semicolon
r_struct
id|tcindex_filter
op_star
op_star
id|walk
suffix:semicolon
r_int
id|hash
comma
id|shift
suffix:semicolon
id|__u16
id|mask
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_change(tp %p,handle 0x%08x,tca %p,arg %p),opt %p,&quot;
l_string|&quot;p %p,r %p&bslash;n&quot;
comma
id|tp
comma
id|handle
comma
id|tca
comma
id|arg
comma
id|opt
comma
id|p
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
id|DPRINTK
c_func
(paren
l_string|&quot;*arg = 0x%lx&bslash;n&quot;
comma
op_star
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_TCINDEX_MAX
comma
id|RTA_DATA
c_func
(paren
id|opt
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|opt
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tb
(braket
id|TCA_TCINDEX_HASH
op_minus
l_int|1
)braket
)paren
(brace
id|hash
op_assign
id|p-&gt;hash
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_HASH
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|hash
op_assign
op_star
(paren
r_int
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_HASH
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tb
(braket
id|TCA_TCINDEX_MASK
op_minus
l_int|1
)braket
)paren
(brace
id|mask
op_assign
id|p-&gt;mask
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_MASK
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
id|__u16
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|mask
op_assign
op_star
(paren
id|__u16
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_MASK
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tb
(braket
id|TCA_TCINDEX_SHIFT
op_minus
l_int|1
)braket
)paren
id|shift
op_assign
id|p-&gt;shift
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_SHIFT
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
id|__u16
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|shift
op_assign
op_star
(paren
r_int
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_SHIFT
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;perfect
op_logical_and
id|hash
op_le
(paren
id|mask
op_rshift
id|shift
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;perfect
op_logical_and
id|hash
OG
id|p-&gt;alloc_hash
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;h
op_logical_and
id|hash
op_ne
id|p-&gt;alloc_hash
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|p-&gt;hash
op_assign
id|hash
suffix:semicolon
id|p-&gt;mask
op_assign
id|mask
suffix:semicolon
id|p-&gt;shift
op_assign
id|shift
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_TCINDEX_FALL_THROUGH
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_FALL_THROUGH
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;fall_through
op_assign
op_star
(paren
r_int
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_FALL_THROUGH
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;classid/police %p/%p&bslash;n&quot;
comma
id|tb
(braket
id|TCA_TCINDEX_CLASSID
op_minus
l_int|1
)braket
comma
id|tb
(braket
id|TCA_TCINDEX_POLICE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tb
(braket
id|TCA_TCINDEX_CLASSID
op_minus
l_int|1
)braket
op_logical_and
op_logical_neg
id|tb
(braket
id|TCA_TCINDEX_POLICE
op_minus
l_int|1
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hash
)paren
(brace
r_if
c_cond
(paren
(paren
id|mask
op_rshift
id|shift
)paren
OL
id|PERFECT_HASH_THRESHOLD
)paren
(brace
id|p-&gt;hash
op_assign
(paren
id|mask
op_rshift
id|shift
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;hash
op_assign
id|DEFAULT_HASH_SIZE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;perfect
op_logical_and
op_logical_neg
id|p-&gt;h
)paren
(brace
id|p-&gt;alloc_hash
op_assign
id|p-&gt;hash
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;hash %d mask %d&bslash;n&quot;
comma
id|p-&gt;hash
comma
id|p-&gt;mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;hash
OG
(paren
id|mask
op_rshift
id|shift
)paren
)paren
(brace
id|p-&gt;perfect
op_assign
id|kmalloc
c_func
(paren
id|p-&gt;hash
op_star
r_sizeof
(paren
r_struct
id|tcindex_filter_result
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;perfect
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|p-&gt;perfect
comma
l_int|0
comma
id|p-&gt;hash
op_star
r_sizeof
(paren
r_struct
id|tcindex_filter_result
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;h
op_assign
id|kmalloc
c_func
(paren
id|p-&gt;hash
op_star
r_sizeof
(paren
r_struct
id|tcindex_filter
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;h
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|p-&gt;h
comma
l_int|0
comma
id|p-&gt;hash
op_star
r_sizeof
(paren
r_struct
id|tcindex_filter
op_star
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Note: this could be as restrictive as&n;&t; * if (handle &amp; ~(mask &gt;&gt; shift))&n;&t; * but then, we&squot;d fail handles that may become valid after some&n;&t; * future mask change. While this is extremely unlikely to ever&n;&t; * matter, the check below is safer (and also more&n;&t; * backwards-compatible).&n;&t; */
r_if
c_cond
(paren
id|p-&gt;perfect
op_logical_and
id|handle
op_ge
id|p-&gt;alloc_hash
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;perfect
)paren
(brace
id|r
op_assign
id|p-&gt;perfect
op_plus
id|handle
suffix:semicolon
)brace
r_else
(brace
id|r
op_assign
id|lookup
c_func
(paren
id|p
comma
id|handle
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;r=%p&bslash;n&quot;
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
id|r
op_assign
op_amp
id|new_filter_result
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;r=%p&bslash;n&quot;
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_TCINDEX_CLASSID
op_minus
l_int|1
)braket
)paren
(brace
r_int
r_int
id|cl
op_assign
id|cls_set_class
c_func
(paren
id|tp
comma
op_amp
id|r-&gt;res
dot
r_class
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
)paren
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|unbind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|cl
)paren
suffix:semicolon
id|r-&gt;res.classid
op_assign
op_star
(paren
id|__u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_CLASSID
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|r-&gt;res
dot
r_class
op_assign
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|bind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|base
comma
id|r-&gt;res.classid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;res
dot
r_class
)paren
(brace
id|r-&gt;res.classid
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_NET_CLS_POLICE
(brace
r_struct
id|tcf_police
op_star
id|police
suffix:semicolon
id|police
op_assign
id|tb
(braket
id|TCA_TCINDEX_POLICE
op_minus
l_int|1
)braket
ques
c_cond
id|tcf_police_locate
c_func
(paren
id|tb
(braket
id|TCA_TCINDEX_POLICE
op_minus
l_int|1
)braket
comma
l_int|NULL
)paren
suffix:colon
l_int|NULL
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|police
op_assign
id|xchg
c_func
(paren
op_amp
id|r-&gt;police
comma
id|police
)paren
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tcf_police_release
c_func
(paren
id|police
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|r
op_ne
op_amp
id|new_filter_result
)paren
r_return
l_int|0
suffix:semicolon
id|f
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tcindex_filter
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|f-&gt;key
op_assign
id|handle
suffix:semicolon
id|f-&gt;result
op_assign
id|new_filter_result
suffix:semicolon
id|f-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|p-&gt;h
op_plus
(paren
id|handle
op_mod
id|p-&gt;hash
)paren
suffix:semicolon
op_star
id|walk
suffix:semicolon
id|walk
op_assign
op_amp
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|next
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
op_star
id|walk
op_assign
id|f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tcindex_walk
r_static
r_void
id|tcindex_walk
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_walker
op_star
id|walker
)paren
(brace
r_struct
id|tcindex_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|tp
)paren
suffix:semicolon
r_struct
id|tcindex_filter
op_star
id|f
comma
op_star
id|next
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_walk(tp %p,walker %p),p %p&bslash;n&quot;
comma
id|tp
comma
id|walker
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;perfect
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|p-&gt;hash
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;perfect
(braket
id|i
)braket
dot
id|res
dot
r_class
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;count
op_ge
id|walker-&gt;skip
)paren
(brace
r_if
c_cond
(paren
id|walker
op_member_access_from_pointer
id|fn
c_func
(paren
id|tp
comma
(paren
r_int
r_int
)paren
(paren
id|p-&gt;perfect
op_plus
id|i
)paren
comma
id|walker
)paren
OL
l_int|0
)paren
(brace
id|walker-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|walker-&gt;count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;h
)paren
r_return
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
id|p-&gt;hash
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|f
op_assign
id|p-&gt;h
(braket
id|i
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|next
)paren
(brace
id|next
op_assign
id|f-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;count
op_ge
id|walker-&gt;skip
)paren
(brace
r_if
c_cond
(paren
id|walker
op_member_access_from_pointer
id|fn
c_func
(paren
id|tp
comma
(paren
r_int
r_int
)paren
op_amp
id|f-&gt;result
comma
id|walker
)paren
OL
l_int|0
)paren
(brace
id|walker-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|walker-&gt;count
op_increment
suffix:semicolon
)brace
)brace
)brace
DECL|function|tcindex_destroy_element
r_static
r_int
id|tcindex_destroy_element
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|arg
comma
r_struct
id|tcf_walker
op_star
id|walker
)paren
(brace
r_return
id|tcindex_delete
c_func
(paren
id|tp
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|tcindex_destroy
r_static
r_void
id|tcindex_destroy
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
r_struct
id|tcindex_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|tp
)paren
suffix:semicolon
r_struct
id|tcf_walker
id|walker
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_destroy(tp %p),p %p&bslash;n&quot;
comma
id|tp
comma
id|p
)paren
suffix:semicolon
id|walker.count
op_assign
l_int|0
suffix:semicolon
id|walker.skip
op_assign
l_int|0
suffix:semicolon
id|walker.fn
op_assign
op_amp
id|tcindex_destroy_element
suffix:semicolon
id|tcindex_walk
c_func
(paren
id|tp
comma
op_amp
id|walker
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;perfect
)paren
id|kfree
c_func
(paren
id|p-&gt;perfect
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;h
)paren
id|kfree
c_func
(paren
id|p-&gt;h
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
id|tp-&gt;root
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_RTNETLINK
DECL|function|tcindex_dump
r_static
r_int
id|tcindex_dump
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|fh
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcmsg
op_star
id|t
)paren
(brace
r_struct
id|tcindex_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|tp
)paren
suffix:semicolon
r_struct
id|tcindex_filter_result
op_star
id|r
op_assign
(paren
r_struct
id|tcindex_filter_result
op_star
)paren
id|fh
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|rtattr
op_star
id|rta
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;tcindex_dump(tp %p,fh 0x%lx,skb %p,t %p),p %p,r %p,b %p&bslash;n&quot;
comma
id|tp
comma
id|fh
comma
id|skb
comma
id|t
comma
id|p
comma
id|r
comma
id|b
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;p-&gt;perfect %p p-&gt;h %p&bslash;n&quot;
comma
id|p-&gt;perfect
comma
id|p-&gt;h
)paren
suffix:semicolon
id|rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|b
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_OPTIONS
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fh
)paren
(brace
id|t-&gt;tcm_handle
op_assign
op_complement
l_int|0
suffix:semicolon
multiline_comment|/* whatever ... */
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_TCINDEX_HASH
comma
r_sizeof
(paren
id|p-&gt;hash
)paren
comma
op_amp
id|p-&gt;hash
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_TCINDEX_MASK
comma
r_sizeof
(paren
id|p-&gt;mask
)paren
comma
op_amp
id|p-&gt;mask
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_TCINDEX_SHIFT
comma
r_sizeof
(paren
id|p-&gt;shift
)paren
comma
op_amp
id|p-&gt;shift
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_TCINDEX_FALL_THROUGH
comma
r_sizeof
(paren
id|p-&gt;fall_through
)paren
comma
op_amp
id|p-&gt;fall_through
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|p-&gt;perfect
)paren
(brace
id|t-&gt;tcm_handle
op_assign
id|r
op_minus
id|p-&gt;perfect
suffix:semicolon
)brace
r_else
(brace
r_struct
id|tcindex_filter
op_star
id|f
suffix:semicolon
r_int
id|i
suffix:semicolon
id|t-&gt;tcm_handle
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|t-&gt;tcm_handle
op_logical_and
id|i
OL
id|p-&gt;hash
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|f
op_assign
id|p-&gt;h
(braket
id|i
)braket
suffix:semicolon
op_logical_neg
id|t-&gt;tcm_handle
op_logical_and
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_amp
id|f-&gt;result
op_eq
id|r
)paren
id|t-&gt;tcm_handle
op_assign
id|f-&gt;key
suffix:semicolon
)brace
)brace
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;handle = %d&bslash;n&quot;
comma
id|t-&gt;tcm_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;res
dot
r_class
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_TCINDEX_CLASSID
comma
l_int|4
comma
op_amp
id|r-&gt;res.classid
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|r-&gt;police
)paren
(brace
r_struct
id|rtattr
op_star
id|p_rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_TCINDEX_POLICE
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcf_police_dump
c_func
(paren
id|skb
comma
id|r-&gt;police
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
id|p_rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|p_rta
suffix:semicolon
)brace
macro_line|#endif
)brace
id|rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
id|b
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|cls_tcindex_ops
r_struct
id|tcf_proto_ops
id|cls_tcindex_ops
op_assign
(brace
l_int|NULL
comma
l_string|&quot;tcindex&quot;
comma
id|tcindex_classify
comma
id|tcindex_init
comma
id|tcindex_destroy
comma
id|tcindex_get
comma
id|tcindex_put
comma
id|tcindex_change
comma
id|tcindex_delete
comma
id|tcindex_walk
comma
macro_line|#ifdef CONFIG_RTNETLINK
id|tcindex_dump
macro_line|#else
l_int|NULL
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|register_tcf_proto_ops
c_func
(paren
op_amp
id|cls_tcindex_ops
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_tcf_proto_ops
c_func
(paren
op_amp
id|cls_tcindex_ops
)paren
suffix:semicolon
)brace
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
