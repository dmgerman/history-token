macro_line|#ifndef __NET_PKT_SCHED_H
DECL|macro|__NET_PKT_SCHED_H
mdefine_line|#define __NET_PKT_SCHED_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pkt_sched.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;net/pkt_cls.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/gen_stats.h&gt;
r_struct
id|rtattr
suffix:semicolon
r_struct
id|Qdisc
suffix:semicolon
DECL|struct|qdisc_walker
r_struct
id|qdisc_walker
(brace
DECL|member|stop
r_int
id|stop
suffix:semicolon
DECL|member|skip
r_int
id|skip
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
id|cl
comma
r_struct
id|qdisc_walker
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Qdisc_class_ops
r_struct
id|Qdisc_class_ops
(brace
multiline_comment|/* Child qdisc manipulation */
DECL|member|graft
r_int
(paren
op_star
id|graft
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
id|cl
comma
r_struct
id|Qdisc
op_star
comma
r_struct
id|Qdisc
op_star
op_star
)paren
suffix:semicolon
DECL|member|leaf
r_struct
id|Qdisc
op_star
(paren
op_star
id|leaf
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
id|cl
)paren
suffix:semicolon
multiline_comment|/* Class manipulation routines */
DECL|member|get
r_int
r_int
(paren
op_star
id|get
)paren
(paren
r_struct
id|Qdisc
op_star
comma
id|u32
id|classid
)paren
suffix:semicolon
DECL|member|put
r_void
(paren
op_star
id|put
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|change
r_int
(paren
op_star
id|change
)paren
(paren
r_struct
id|Qdisc
op_star
comma
id|u32
comma
id|u32
comma
r_struct
id|rtattr
op_star
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
DECL|member|delete
r_int
(paren
op_star
r_delete
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|walk
r_void
(paren
op_star
id|walk
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_struct
id|qdisc_walker
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* Filter manipulation */
DECL|member|tcf_chain
r_struct
id|tcf_proto
op_star
op_star
(paren
op_star
id|tcf_chain
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|bind_tcf
r_int
r_int
(paren
op_star
id|bind_tcf
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
comma
id|u32
id|classid
)paren
suffix:semicolon
DECL|member|unbind_tcf
r_void
(paren
op_star
id|unbind_tcf
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* rtnetlink specific */
DECL|member|dump
r_int
(paren
op_star
id|dump
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_int
r_int
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcmsg
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|module
suffix:semicolon
DECL|struct|Qdisc_ops
r_struct
id|Qdisc_ops
(brace
DECL|member|next
r_struct
id|Qdisc_ops
op_star
id|next
suffix:semicolon
DECL|member|cl_ops
r_struct
id|Qdisc_class_ops
op_star
id|cl_ops
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|priv_size
r_int
id|priv_size
suffix:semicolon
DECL|member|enqueue
r_int
(paren
op_star
id|enqueue
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|Qdisc
op_star
)paren
suffix:semicolon
DECL|member|dequeue
r_struct
id|sk_buff
op_star
(paren
op_star
id|dequeue
)paren
(paren
r_struct
id|Qdisc
op_star
)paren
suffix:semicolon
DECL|member|requeue
r_int
(paren
op_star
id|requeue
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|Qdisc
op_star
)paren
suffix:semicolon
DECL|member|drop
r_int
r_int
(paren
op_star
id|drop
)paren
(paren
r_struct
id|Qdisc
op_star
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_struct
id|rtattr
op_star
id|arg
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_struct
id|Qdisc
op_star
)paren
suffix:semicolon
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|Qdisc
op_star
)paren
suffix:semicolon
DECL|member|change
r_int
(paren
op_star
id|change
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_struct
id|rtattr
op_star
id|arg
)paren
suffix:semicolon
DECL|member|dump
r_int
(paren
op_star
id|dump
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|dump_stats
r_int
(paren
op_star
id|dump_stats
)paren
(paren
r_struct
id|Qdisc
op_star
comma
r_struct
id|gnet_dump
op_star
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|rwlock_t
id|qdisc_tree_lock
suffix:semicolon
DECL|struct|Qdisc
r_struct
id|Qdisc
(brace
DECL|member|enqueue
r_int
(paren
op_star
id|enqueue
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|dev
)paren
suffix:semicolon
DECL|member|dequeue
r_struct
id|sk_buff
op_star
(paren
op_star
id|dequeue
)paren
(paren
r_struct
id|Qdisc
op_star
id|dev
)paren
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|macro|TCQ_F_BUILTIN
mdefine_line|#define TCQ_F_BUILTIN&t;1
DECL|macro|TCQ_F_THROTTLED
mdefine_line|#define TCQ_F_THROTTLED&t;2
DECL|macro|TCQ_F_INGRES
mdefine_line|#define TCQ_F_INGRES&t;4
DECL|member|padded
r_int
id|padded
suffix:semicolon
DECL|member|ops
r_struct
id|Qdisc_ops
op_star
id|ops
suffix:semicolon
DECL|member|handle
id|u32
id|handle
suffix:semicolon
DECL|member|parent
id|u32
id|parent
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|q
r_struct
id|sk_buff_head
id|q
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|bstats
r_struct
id|gnet_stats_basic
id|bstats
suffix:semicolon
DECL|member|qstats
r_struct
id|gnet_stats_queue
id|qstats
suffix:semicolon
DECL|member|rate_est
r_struct
id|gnet_stats_rate_est
id|rate_est
suffix:semicolon
DECL|member|stats_lock
id|spinlock_t
op_star
id|stats_lock
suffix:semicolon
DECL|member|q_rcu
r_struct
id|rcu_head
id|q_rcu
suffix:semicolon
DECL|member|reshape_fail
r_int
(paren
op_star
id|reshape_fail
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|q
)paren
suffix:semicolon
multiline_comment|/* This field is deprecated, but it is still used by CBQ&n;&t; * and it will live until better solution will be invented.&n;&t; */
DECL|member|__parent
r_struct
id|Qdisc
op_star
id|__parent
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|QDISC_ALIGN
mdefine_line|#define&t;QDISC_ALIGN&t;&t;32
DECL|macro|QDISC_ALIGN_CONST
mdefine_line|#define&t;QDISC_ALIGN_CONST&t;(QDISC_ALIGN - 1)
DECL|function|qdisc_priv
r_static
r_inline
r_void
op_star
id|qdisc_priv
c_func
(paren
r_struct
id|Qdisc
op_star
id|q
)paren
(brace
r_return
(paren
r_char
op_star
)paren
id|q
op_plus
(paren
(paren
r_sizeof
(paren
r_struct
id|Qdisc
)paren
op_plus
id|QDISC_ALIGN_CONST
)paren
op_amp
op_complement
id|QDISC_ALIGN_CONST
)paren
suffix:semicolon
)brace
DECL|struct|qdisc_rate_table
r_struct
id|qdisc_rate_table
(brace
DECL|member|rate
r_struct
id|tc_ratespec
id|rate
suffix:semicolon
DECL|member|data
id|u32
id|data
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|next
r_struct
id|qdisc_rate_table
op_star
id|next
suffix:semicolon
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|qdisc_lock_tree
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|qdisc_unlock_tree
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|macro|sch_tree_lock
mdefine_line|#define sch_tree_lock(q)&t;qdisc_lock_tree((q)-&gt;dev)
DECL|macro|sch_tree_unlock
mdefine_line|#define sch_tree_unlock(q)&t;qdisc_unlock_tree((q)-&gt;dev)
DECL|macro|tcf_tree_lock
mdefine_line|#define tcf_tree_lock(tp)&t;qdisc_lock_tree((tp)-&gt;q-&gt;dev)
DECL|macro|tcf_tree_unlock
mdefine_line|#define tcf_tree_unlock(tp)&t;qdisc_unlock_tree((tp)-&gt;q-&gt;dev)
DECL|macro|cls_set_class
mdefine_line|#define cls_set_class(tp, clp, cl) tcf_set_class(tp, clp, cl)
r_static
r_inline
r_int
r_int
DECL|function|__cls_set_class
id|__cls_set_class
c_func
(paren
r_int
r_int
op_star
id|clp
comma
r_int
r_int
id|cl
)paren
(brace
r_int
r_int
id|old_cl
suffix:semicolon
id|old_cl
op_assign
op_star
id|clp
suffix:semicolon
op_star
id|clp
op_assign
id|cl
suffix:semicolon
r_return
id|old_cl
suffix:semicolon
)brace
multiline_comment|/* &n;   Timer resolution MUST BE &lt; 10% of min_schedulable_packet_size/bandwidth&n;   &n;   Normal IP packet size ~ 512byte, hence:&n;&n;   0.5Kbyte/1Mbyte/sec = 0.5msec, so that we need 50usec timer for&n;   10Mbit ethernet.&n;&n;   10msec resolution -&gt; &lt;50Kbit/sec.&n;   &n;   The result: [34]86 is not good choice for QoS router :-(&n;&n;   The things are not so bad, because we may use artifical&n;   clock evaluated by integration of network data flow&n;   in the most critical places.&n;&n;   Note: we do not use fastgettimeofday.&n;   The reason is that, when it is not the same thing as&n;   gettimeofday, it returns invalid timestamp, which is&n;   not updated, when net_bh is active.&n; */
multiline_comment|/* General note about internal clock.&n;&n;   Any clock source returns time intervals, measured in units&n;   close to 1usec. With source CONFIG_NET_SCH_CLK_GETTIMEOFDAY it is precisely&n;   microseconds, otherwise something close but different chosen to minimize&n;   arithmetic cost. Ratio usec/internal untis in form nominator/denominator&n;   may be read from /proc/net/psched.&n; */
macro_line|#ifdef CONFIG_NET_SCH_CLK_GETTIMEOFDAY
DECL|typedef|psched_time_t
r_typedef
r_struct
id|timeval
id|psched_time_t
suffix:semicolon
DECL|typedef|psched_tdiff_t
r_typedef
r_int
id|psched_tdiff_t
suffix:semicolon
DECL|macro|PSCHED_GET_TIME
mdefine_line|#define PSCHED_GET_TIME(stamp) do_gettimeofday(&amp;(stamp))
DECL|macro|PSCHED_US2JIFFIE
mdefine_line|#define PSCHED_US2JIFFIE(usecs) (((usecs)+(1000000/HZ-1))/(1000000/HZ))
DECL|macro|PSCHED_JIFFIE2US
mdefine_line|#define PSCHED_JIFFIE2US(delay) ((delay)*(1000000/HZ))
macro_line|#else /* !CONFIG_NET_SCH_CLK_GETTIMEOFDAY */
DECL|typedef|psched_time_t
r_typedef
id|u64
id|psched_time_t
suffix:semicolon
DECL|typedef|psched_tdiff_t
r_typedef
r_int
id|psched_tdiff_t
suffix:semicolon
macro_line|#ifdef CONFIG_NET_SCH_CLK_JIFFIES
macro_line|#if HZ &lt; 96
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 14
macro_line|#elif HZ &gt;= 96 &amp;&amp; HZ &lt; 192
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 13
macro_line|#elif HZ &gt;= 192 &amp;&amp; HZ &lt; 384
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 12
macro_line|#elif HZ &gt;= 384 &amp;&amp; HZ &lt; 768
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 11
macro_line|#elif HZ &gt;= 768
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 10
macro_line|#endif
DECL|macro|PSCHED_GET_TIME
mdefine_line|#define PSCHED_GET_TIME(stamp) ((stamp) = (get_jiffies_64()&lt;&lt;PSCHED_JSCALE))
DECL|macro|PSCHED_US2JIFFIE
mdefine_line|#define PSCHED_US2JIFFIE(delay) (((delay)+(1&lt;&lt;PSCHED_JSCALE)-1)&gt;&gt;PSCHED_JSCALE)
DECL|macro|PSCHED_JIFFIE2US
mdefine_line|#define PSCHED_JIFFIE2US(delay) ((delay)&lt;&lt;PSCHED_JSCALE)
macro_line|#endif /* CONFIG_NET_SCH_CLK_JIFFIES */
macro_line|#ifdef CONFIG_NET_SCH_CLK_CPU
macro_line|#include &lt;asm/timex.h&gt;
r_extern
id|psched_tdiff_t
id|psched_clock_per_hz
suffix:semicolon
r_extern
r_int
id|psched_clock_scale
suffix:semicolon
r_extern
id|psched_time_t
id|psched_time_base
suffix:semicolon
r_extern
id|cycles_t
id|psched_time_mark
suffix:semicolon
DECL|macro|PSCHED_GET_TIME
mdefine_line|#define PSCHED_GET_TIME(stamp)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cycles_t cur = get_cycles();&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(cycles_t) == sizeof(u32)) {&t;&t;&t;&t;&bslash;&n;&t;&t;if (cur &lt;= psched_time_mark)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;psched_time_base += 0x100000000ULL;&t;&t;&bslash;&n;&t;&t;psched_time_mark = cur;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(stamp) = (psched_time_base + cur)&gt;&gt;psched_clock_scale;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(stamp) = cur&gt;&gt;psched_clock_scale;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|PSCHED_US2JIFFIE
mdefine_line|#define PSCHED_US2JIFFIE(delay) (((delay)+psched_clock_per_hz-1)/psched_clock_per_hz)
DECL|macro|PSCHED_JIFFIE2US
mdefine_line|#define PSCHED_JIFFIE2US(delay) ((delay)*psched_clock_per_hz)
macro_line|#endif /* CONFIG_NET_SCH_CLK_CPU */
macro_line|#endif /* !CONFIG_NET_SCH_CLK_GETTIMEOFDAY */
macro_line|#ifdef CONFIG_NET_SCH_CLK_GETTIMEOFDAY
DECL|macro|PSCHED_TDIFF
mdefine_line|#define PSCHED_TDIFF(tv1, tv2) &bslash;&n;({ &bslash;&n;&t;   int __delta_sec = (tv1).tv_sec - (tv2).tv_sec; &bslash;&n;&t;   int __delta = (tv1).tv_usec - (tv2).tv_usec; &bslash;&n;&t;   if (__delta_sec) { &bslash;&n;&t;           switch (__delta_sec) { &bslash;&n;&t;&t;   default: &bslash;&n;&t;&t;&t;   __delta = 0; &bslash;&n;&t;&t;   case 2: &bslash;&n;&t;&t;&t;   __delta += 1000000; &bslash;&n;&t;&t;   case 1: &bslash;&n;&t;&t;&t;   __delta += 1000000; &bslash;&n;&t;           } &bslash;&n;&t;   } &bslash;&n;&t;   __delta; &bslash;&n;})
r_extern
r_int
id|psched_tod_diff
c_func
(paren
r_int
id|delta_sec
comma
r_int
id|bound
)paren
suffix:semicolon
DECL|macro|PSCHED_TDIFF_SAFE
mdefine_line|#define PSCHED_TDIFF_SAFE(tv1, tv2, bound) &bslash;&n;({ &bslash;&n;&t;   int __delta_sec = (tv1).tv_sec - (tv2).tv_sec; &bslash;&n;&t;   int __delta = (tv1).tv_usec - (tv2).tv_usec; &bslash;&n;&t;   switch (__delta_sec) { &bslash;&n;&t;   default: &bslash;&n;&t;&t;   __delta = psched_tod_diff(__delta_sec, bound);  break; &bslash;&n;&t;   case 2: &bslash;&n;&t;&t;   __delta += 1000000; &bslash;&n;&t;   case 1: &bslash;&n;&t;&t;   __delta += 1000000; &bslash;&n;&t;   case 0: ; &bslash;&n;&t;   } &bslash;&n;&t;   __delta; &bslash;&n;})
DECL|macro|PSCHED_TLESS
mdefine_line|#define PSCHED_TLESS(tv1, tv2) (((tv1).tv_usec &lt; (tv2).tv_usec &amp;&amp; &bslash;&n;&t;&t;&t;&t;(tv1).tv_sec &lt;= (tv2).tv_sec) || &bslash;&n;&t;&t;&t;&t; (tv1).tv_sec &lt; (tv2).tv_sec)
DECL|macro|PSCHED_TADD2
mdefine_line|#define PSCHED_TADD2(tv, delta, tv_res) &bslash;&n;({ &bslash;&n;&t;   int __delta = (tv).tv_usec + (delta); &bslash;&n;&t;   (tv_res).tv_sec = (tv).tv_sec; &bslash;&n;&t;   if (__delta &gt; 1000000) { (tv_res).tv_sec++; __delta -= 1000000; } &bslash;&n;&t;   (tv_res).tv_usec = __delta; &bslash;&n;})
DECL|macro|PSCHED_TADD
mdefine_line|#define PSCHED_TADD(tv, delta) &bslash;&n;({ &bslash;&n;&t;   (tv).tv_usec += (delta); &bslash;&n;&t;   if ((tv).tv_usec &gt; 1000000) { (tv).tv_sec++; &bslash;&n;&t;&t; (tv).tv_usec -= 1000000; } &bslash;&n;})
multiline_comment|/* Set/check that time is in the &quot;past perfect&quot;;&n;   it depends on concrete representation of system time&n; */
DECL|macro|PSCHED_SET_PASTPERFECT
mdefine_line|#define PSCHED_SET_PASTPERFECT(t)&t;((t).tv_sec = 0)
DECL|macro|PSCHED_IS_PASTPERFECT
mdefine_line|#define PSCHED_IS_PASTPERFECT(t)&t;((t).tv_sec == 0)
DECL|macro|PSCHED_AUDIT_TDIFF
mdefine_line|#define&t;PSCHED_AUDIT_TDIFF(t) ({ if ((t) &gt; 2000000) (t) = 2000000; })
macro_line|#else /* !CONFIG_NET_SCH_CLK_GETTIMEOFDAY */
DECL|macro|PSCHED_TDIFF
mdefine_line|#define PSCHED_TDIFF(tv1, tv2) (long)((tv1) - (tv2))
DECL|macro|PSCHED_TDIFF_SAFE
mdefine_line|#define PSCHED_TDIFF_SAFE(tv1, tv2, bound) &bslash;&n;&t;min_t(long long, (tv1) - (tv2), bound)
DECL|macro|PSCHED_TLESS
mdefine_line|#define PSCHED_TLESS(tv1, tv2) ((tv1) &lt; (tv2))
DECL|macro|PSCHED_TADD2
mdefine_line|#define PSCHED_TADD2(tv, delta, tv_res) ((tv_res) = (tv) + (delta))
DECL|macro|PSCHED_TADD
mdefine_line|#define PSCHED_TADD(tv, delta) ((tv) += (delta))
DECL|macro|PSCHED_SET_PASTPERFECT
mdefine_line|#define PSCHED_SET_PASTPERFECT(t)&t;((t) = 0)
DECL|macro|PSCHED_IS_PASTPERFECT
mdefine_line|#define PSCHED_IS_PASTPERFECT(t)&t;((t) == 0)
DECL|macro|PSCHED_AUDIT_TDIFF
mdefine_line|#define&t;PSCHED_AUDIT_TDIFF(t)
macro_line|#endif /* !CONFIG_NET_SCH_CLK_GETTIMEOFDAY */
DECL|struct|tcf_police
r_struct
id|tcf_police
(brace
DECL|member|next
r_struct
id|tcf_police
op_star
id|next
suffix:semicolon
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
DECL|member|bindcnt
r_int
id|bindcnt
suffix:semicolon
macro_line|#endif
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|member|action
r_int
id|action
suffix:semicolon
DECL|member|result
r_int
id|result
suffix:semicolon
DECL|member|ewma_rate
id|u32
id|ewma_rate
suffix:semicolon
DECL|member|burst
id|u32
id|burst
suffix:semicolon
DECL|member|mtu
id|u32
id|mtu
suffix:semicolon
DECL|member|toks
id|u32
id|toks
suffix:semicolon
DECL|member|ptoks
id|u32
id|ptoks
suffix:semicolon
DECL|member|t_c
id|psched_time_t
id|t_c
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|R_tab
r_struct
id|qdisc_rate_table
op_star
id|R_tab
suffix:semicolon
DECL|member|P_tab
r_struct
id|qdisc_rate_table
op_star
id|P_tab
suffix:semicolon
DECL|member|stats
r_struct
id|tc_stats
id|stats
suffix:semicolon
DECL|member|stats_lock
id|spinlock_t
op_star
id|stats_lock
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
DECL|macro|ACT_P_CREATED
mdefine_line|#define ACT_P_CREATED 1
DECL|macro|ACT_P_DELETED
mdefine_line|#define ACT_P_DELETED 1
DECL|macro|tca_gen
mdefine_line|#define tca_gen(name) &bslash;&n;struct tcf_##name *next; &bslash;&n;&t;u32 index; &bslash;&n;&t;int refcnt; &bslash;&n;&t;int bindcnt; &bslash;&n;&t;u32 capab; &bslash;&n;&t;int action; &bslash;&n;&t;struct tcf_t tm; &bslash;&n;&t;struct tc_stats stats; &bslash;&n;&t;spinlock_t *stats_lock; &bslash;&n;&t;spinlock_t lock
DECL|struct|tc_action
r_struct
id|tc_action
(brace
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|ops
r_struct
id|tc_action_ops
op_star
id|ops
suffix:semicolon
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* for backward compat(TCA_OLD_COMPAT) */
DECL|member|order
id|__u32
id|order
suffix:semicolon
DECL|member|next
r_struct
id|tc_action
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TCA_CAP_NONE
mdefine_line|#define TCA_CAP_NONE 0
DECL|struct|tc_action_ops
r_struct
id|tc_action_ops
(brace
DECL|member|next
r_struct
id|tc_action_ops
op_star
id|next
suffix:semicolon
DECL|member|kind
r_char
id|kind
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* TBD to match kind */
DECL|member|capab
id|__u32
id|capab
suffix:semicolon
multiline_comment|/* capabilities includes 4 bit version */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|act
r_int
(paren
op_star
id|act
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
comma
r_struct
id|tc_action
op_star
)paren
suffix:semicolon
DECL|member|get_stats
r_int
(paren
op_star
id|get_stats
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tc_action
op_star
)paren
suffix:semicolon
DECL|member|dump
r_int
(paren
op_star
id|dump
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tc_action
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|cleanup
r_int
(paren
op_star
id|cleanup
)paren
(paren
r_struct
id|tc_action
op_star
comma
r_int
id|bind
)paren
suffix:semicolon
DECL|member|lookup
r_int
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|tc_action
op_star
comma
id|u32
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|rtattr
op_star
comma
r_struct
id|rtattr
op_star
comma
r_struct
id|tc_action
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|walk
r_int
(paren
op_star
id|walk
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|netlink_callback
op_star
comma
r_int
comma
r_struct
id|tc_action
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|tcf_register_action
c_func
(paren
r_struct
id|tc_action_ops
op_star
id|a
)paren
suffix:semicolon
r_extern
r_int
id|tcf_unregister_action
c_func
(paren
r_struct
id|tc_action_ops
op_star
id|a
)paren
suffix:semicolon
r_extern
r_void
id|tcf_action_destroy
c_func
(paren
r_struct
id|tc_action
op_star
id|a
comma
r_int
id|bind
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_exec
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_action
op_star
id|a
comma
r_struct
id|tcf_result
op_star
id|res
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_init
c_func
(paren
r_struct
id|rtattr
op_star
id|rta
comma
r_struct
id|rtattr
op_star
id|est
comma
r_struct
id|tc_action
op_star
id|a
comma
r_char
op_star
id|n
comma
r_int
id|ovr
comma
r_int
id|bind
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_init_1
c_func
(paren
r_struct
id|rtattr
op_star
id|rta
comma
r_struct
id|rtattr
op_star
id|est
comma
r_struct
id|tc_action
op_star
id|a
comma
r_char
op_star
id|n
comma
r_int
id|ovr
comma
r_int
id|bind
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_dump_old
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_dump_1
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_copy_stats
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tc_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tcf_act_police_locate
c_func
(paren
r_struct
id|rtattr
op_star
id|rta
comma
r_struct
id|rtattr
op_star
id|est
comma
r_struct
id|tc_action
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_act_police_dump
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tc_action
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_act_police
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|tc_action
op_star
id|a
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|tcf_set_class
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
op_star
id|clp
comma
r_int
r_int
id|cl
)paren
suffix:semicolon
r_extern
r_int
id|tcf_police
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_police
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|qdisc_copy_stats
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_stats
op_star
id|st
comma
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|tcf_police_destroy
c_func
(paren
r_struct
id|tcf_police
op_star
id|p
)paren
suffix:semicolon
r_extern
r_struct
id|tcf_police
op_star
id|tcf_police_locate
c_func
(paren
r_struct
id|rtattr
op_star
id|rta
comma
r_struct
id|rtattr
op_star
id|est
)paren
suffix:semicolon
r_extern
r_int
id|tcf_police_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_police
op_star
id|p
)paren
suffix:semicolon
DECL|function|tcf_police_release
r_static
r_inline
r_int
id|tcf_police_release
c_func
(paren
r_struct
id|tcf_police
op_star
id|p
comma
r_int
id|bind
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|bind
)paren
(brace
id|p-&gt;bindcnt
op_decrement
suffix:semicolon
)brace
id|p-&gt;refcnt
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;refcnt
op_le
l_int|0
op_logical_and
op_logical_neg
id|p-&gt;bindcnt
)paren
(brace
id|tcf_police_destroy
c_func
(paren
id|p
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#else
r_if
c_cond
(paren
id|p
op_logical_and
op_decrement
id|p-&gt;refcnt
op_eq
l_int|0
)paren
id|tcf_police_destroy
c_func
(paren
id|p
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_struct
id|Qdisc
id|noop_qdisc
suffix:semicolon
r_extern
r_struct
id|Qdisc_ops
id|noop_qdisc_ops
suffix:semicolon
r_extern
r_struct
id|Qdisc_ops
id|pfifo_qdisc_ops
suffix:semicolon
r_extern
r_struct
id|Qdisc_ops
id|bfifo_qdisc_ops
suffix:semicolon
r_int
id|register_qdisc
c_func
(paren
r_struct
id|Qdisc_ops
op_star
id|qops
)paren
suffix:semicolon
r_int
id|unregister_qdisc
c_func
(paren
r_struct
id|Qdisc_ops
op_star
id|qops
)paren
suffix:semicolon
r_struct
id|Qdisc
op_star
id|qdisc_lookup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|handle
)paren
suffix:semicolon
r_struct
id|Qdisc
op_star
id|qdisc_lookup_class
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|handle
)paren
suffix:semicolon
r_void
id|dev_init_scheduler
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|dev_shutdown
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|dev_activate
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|dev_deactivate
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|qdisc_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
)paren
suffix:semicolon
r_void
id|qdisc_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
)paren
suffix:semicolon
r_struct
id|Qdisc
op_star
id|qdisc_create_dflt
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|Qdisc_ops
op_star
id|ops
)paren
suffix:semicolon
r_int
id|qdisc_new_estimator
c_func
(paren
r_struct
id|tc_stats
op_star
id|stats
comma
id|spinlock_t
op_star
id|stats_lock
comma
r_struct
id|rtattr
op_star
id|opt
)paren
suffix:semicolon
r_void
id|qdisc_kill_estimator
c_func
(paren
r_struct
id|tc_stats
op_star
id|stats
)paren
suffix:semicolon
r_struct
id|qdisc_rate_table
op_star
id|qdisc_get_rtab
c_func
(paren
r_struct
id|tc_ratespec
op_star
id|r
comma
r_struct
id|rtattr
op_star
id|tab
)paren
suffix:semicolon
r_void
id|qdisc_put_rtab
c_func
(paren
r_struct
id|qdisc_rate_table
op_star
id|tab
)paren
suffix:semicolon
r_extern
r_int
id|qdisc_restart
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Calculate maximal size of packet seen by hard_start_xmit&n;   routine of this device.&n; */
DECL|function|psched_mtu
r_static
r_inline
r_int
id|psched_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|mtu
op_assign
id|dev-&gt;mtu
suffix:semicolon
r_return
id|dev-&gt;hard_header
ques
c_cond
id|mtu
op_plus
id|dev-&gt;hard_header_len
suffix:colon
id|mtu
suffix:semicolon
)brace
macro_line|#endif
eof
