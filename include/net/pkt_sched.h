macro_line|#ifndef __NET_PKT_SCHED_H
DECL|macro|__NET_PKT_SCHED_H
mdefine_line|#define __NET_PKT_SCHED_H
DECL|macro|PSCHED_GETTIMEOFDAY
mdefine_line|#define PSCHED_GETTIMEOFDAY&t;1
DECL|macro|PSCHED_JIFFIES
mdefine_line|#define PSCHED_JIFFIES &t;&t;2
DECL|macro|PSCHED_CPU
mdefine_line|#define PSCHED_CPU &t;&t;3
DECL|macro|PSCHED_CLOCK_SOURCE
mdefine_line|#define PSCHED_CLOCK_SOURCE&t;PSCHED_JIFFIES
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pkt_sched.h&gt;
macro_line|#include &lt;net/pkt_cls.h&gt;
macro_line|#ifdef CONFIG_X86_TSC
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#endif
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
DECL|member|ops
r_struct
id|Qdisc_ops
op_star
id|ops
suffix:semicolon
DECL|member|next
r_struct
id|Qdisc
op_star
id|next
suffix:semicolon
DECL|member|handle
id|u32
id|handle
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
DECL|member|stats
r_struct
id|tc_stats
id|stats
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
DECL|member|data
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
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
DECL|function|sch_tree_lock
r_static
r_inline
r_void
id|sch_tree_lock
c_func
(paren
r_struct
id|Qdisc
op_star
id|q
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|q-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
)brace
DECL|function|sch_tree_unlock
r_static
r_inline
r_void
id|sch_tree_unlock
c_func
(paren
r_struct
id|Qdisc
op_star
id|q
)paren
(brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|q-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
)brace
DECL|function|tcf_tree_lock
r_static
r_inline
r_void
id|tcf_tree_lock
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|tp-&gt;q-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
)brace
DECL|function|tcf_tree_unlock
r_static
r_inline
r_void
id|tcf_tree_unlock
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|tp-&gt;q-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|cls_set_class
id|cls_set_class
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
(brace
r_int
r_int
id|old_cl
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
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
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
r_return
id|old_cl
suffix:semicolon
)brace
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
multiline_comment|/* &n;   Timer resolution MUST BE &lt; 10% of min_schedulable_packet_size/bandwidth&n;   &n;   Normal IP packet size ~ 512byte, hence:&n;&n;   0.5Kbyte/1Mbyte/sec = 0.5msec, so that we need 50usec timer for&n;   10Mbit ethernet.&n;&n;   10msec resolution -&gt; &lt;50Kbit/sec.&n;   &n;   The result: [34]86 is not good choice for QoS router :-(&n;&n;   The things are not so bad, because we may use artifical&n;   clock evaluated by integration of network data flow&n;   in the most critical places.&n;&n;   Note: we do not use fastgettimeofday.&n;   The reason is that, when it is not the same thing as&n;   gettimeofday, it returns invalid timestamp, which is&n;   not updated, when net_bh is active.&n;&n;   So, use PSCHED_CLOCK_SOURCE = PSCHED_CPU on alpha and pentiums&n;   with rtdsc. And PSCHED_JIFFIES on all other architectures, including [34]86&n;   and pentiums without rtdsc.&n;   You can use PSCHED_GETTIMEOFDAY on another architectures,&n;   which have fast and precise clock source, but it is too expensive.&n; */
multiline_comment|/* General note about internal clock.&n;&n;   Any clock source returns time intervals, measured in units&n;   close to 1usec. With source PSCHED_GETTIMEOFDAY it is precisely&n;   microseconds, otherwise something close but different chosen to minimize&n;   arithmetic cost. Ratio usec/internal untis in form nominator/denominator&n;   may be read from /proc/net/psched.&n; */
macro_line|#if PSCHED_CLOCK_SOURCE == PSCHED_GETTIMEOFDAY
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
DECL|macro|PSCHED_EXPORTLIST
mdefine_line|#define PSCHED_EXPORTLIST EXPORT_SYMBOL(psched_tod_diff);
macro_line|#else /* PSCHED_CLOCK_SOURCE != PSCHED_GETTIMEOFDAY */
DECL|macro|PSCHED_EXPORTLIST
mdefine_line|#define PSCHED_EXPORTLIST PSCHED_EXPORTLIST_1 PSCHED_EXPORTLIST_2
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
r_extern
id|psched_time_t
id|psched_time_base
suffix:semicolon
macro_line|#if PSCHED_CLOCK_SOURCE == PSCHED_JIFFIES
macro_line|#if HZ == 100
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 13
macro_line|#elif HZ == 1024
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 10
macro_line|#else
DECL|macro|PSCHED_JSCALE
mdefine_line|#define PSCHED_JSCALE 0
macro_line|#endif
DECL|macro|PSCHED_EXPORTLIST_2
mdefine_line|#define PSCHED_EXPORTLIST_2
macro_line|#if BITS_PER_LONG &lt;= 32
DECL|macro|PSCHED_WATCHER
mdefine_line|#define PSCHED_WATCHER unsigned long
r_extern
id|PSCHED_WATCHER
id|psched_time_mark
suffix:semicolon
DECL|macro|PSCHED_GET_TIME
mdefine_line|#define PSCHED_GET_TIME(stamp) ((stamp) = psched_time_base + (((unsigned long)(jiffies-psched_time_mark))&lt;&lt;PSCHED_JSCALE))
DECL|macro|PSCHED_EXPORTLIST_1
mdefine_line|#define PSCHED_EXPORTLIST_1 EXPORT_SYMBOL(psched_time_base); &bslash;&n;                            EXPORT_SYMBOL(psched_time_mark);
macro_line|#else
DECL|macro|PSCHED_GET_TIME
mdefine_line|#define PSCHED_GET_TIME(stamp) ((stamp) = (jiffies&lt;&lt;PSCHED_JSCALE))
DECL|macro|PSCHED_EXPORTLIST_1
mdefine_line|#define PSCHED_EXPORTLIST_1 
macro_line|#endif
DECL|macro|PSCHED_US2JIFFIE
mdefine_line|#define PSCHED_US2JIFFIE(delay) (((delay)+(1&lt;&lt;PSCHED_JSCALE)-1)&gt;&gt;PSCHED_JSCALE)
macro_line|#elif PSCHED_CLOCK_SOURCE == PSCHED_CPU
r_extern
id|psched_tdiff_t
id|psched_clock_per_hz
suffix:semicolon
r_extern
r_int
id|psched_clock_scale
suffix:semicolon
DECL|macro|PSCHED_EXPORTLIST_2
mdefine_line|#define PSCHED_EXPORTLIST_2 EXPORT_SYMBOL(psched_clock_per_hz); &bslash;&n;                            EXPORT_SYMBOL(psched_clock_scale);
DECL|macro|PSCHED_US2JIFFIE
mdefine_line|#define PSCHED_US2JIFFIE(delay) (((delay)+psched_clock_per_hz-1)/psched_clock_per_hz)
macro_line|#ifdef CONFIG_X86_TSC
DECL|macro|PSCHED_GET_TIME
mdefine_line|#define PSCHED_GET_TIME(stamp) &bslash;&n;({ u64 __cur; &bslash;&n;   rdtscll(__cur); &bslash;&n;   (stamp) = __cur&gt;&gt;psched_clock_scale; &bslash;&n;})
DECL|macro|PSCHED_EXPORTLIST_1
mdefine_line|#define PSCHED_EXPORTLIST_1
macro_line|#elif defined (__alpha__)
DECL|macro|PSCHED_WATCHER
mdefine_line|#define PSCHED_WATCHER u32
r_extern
id|PSCHED_WATCHER
id|psched_time_mark
suffix:semicolon
DECL|macro|PSCHED_GET_TIME
mdefine_line|#define PSCHED_GET_TIME(stamp) &bslash;&n;({ u32 __res; &bslash;&n;   __asm__ __volatile__ (&quot;rpcc %0&quot; : &quot;r=&quot;(__res)); &bslash;&n;   if (__res &lt;= psched_time_mark) psched_time_base += 0x100000000UL; &bslash;&n;   psched_time_mark = __res; &bslash;&n;   (stamp) = (psched_time_base + __res)&gt;&gt;psched_clock_scale; &bslash;&n;})
DECL|macro|PSCHED_EXPORTLIST_1
mdefine_line|#define PSCHED_EXPORTLIST_1 EXPORT_SYMBOL(psched_time_base); &bslash;&n;                            EXPORT_SYMBOL(psched_time_mark);
macro_line|#else
macro_line|#error PSCHED_CLOCK_SOURCE=PSCHED_CPU is not supported on this arch.
macro_line|#endif /* ARCH */
macro_line|#endif /* PSCHED_CLOCK_SOURCE == PSCHED_JIFFIES */
macro_line|#endif /* PSCHED_CLOCK_SOURCE == PSCHED_GETTIMEOFDAY */
macro_line|#if PSCHED_CLOCK_SOURCE == PSCHED_GETTIMEOFDAY
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
mdefine_line|#define PSCHED_TDIFF_SAFE(tv1, tv2, bound, guard) &bslash;&n;({ &bslash;&n;&t;   int __delta_sec = (tv1).tv_sec - (tv2).tv_sec; &bslash;&n;&t;   int __delta = (tv1).tv_usec - (tv2).tv_usec; &bslash;&n;&t;   switch (__delta_sec) { &bslash;&n;&t;   default: &bslash;&n;&t;&t;   __delta = psched_tod_diff(__delta_sec, bound); guard; break; &bslash;&n;&t;   case 2: &bslash;&n;&t;&t;   __delta += 1000000; &bslash;&n;&t;   case 1: &bslash;&n;&t;&t;   __delta += 1000000; &bslash;&n;&t;   case 0: ; &bslash;&n;&t;   } &bslash;&n;&t;   __delta; &bslash;&n;})
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
macro_line|#else
DECL|macro|PSCHED_TDIFF
mdefine_line|#define PSCHED_TDIFF(tv1, tv2) (long)((tv1) - (tv2))
DECL|macro|PSCHED_TDIFF_SAFE
mdefine_line|#define PSCHED_TDIFF_SAFE(tv1, tv2, bound, guard) &bslash;&n;({ &bslash;&n;&t;   long long __delta = (tv1) - (tv2); &bslash;&n;&t;   if ( __delta &gt; (long long)(bound)) {  __delta = (bound); guard; } &bslash;&n;&t;   __delta; &bslash;&n;})
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
macro_line|#endif
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
)brace
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
DECL|function|tcf_police_release
r_static
r_inline
r_void
id|tcf_police_release
c_func
(paren
r_struct
id|tcf_police
op_star
id|p
)paren
(brace
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
r_int
id|teql_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|tc_filter_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pktsched_init
c_func
(paren
r_void
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
DECL|function|qdisc_run
r_static
r_inline
r_void
id|qdisc_run
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|netif_queue_stopped
c_func
(paren
id|dev
)paren
op_logical_and
id|qdisc_restart
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
multiline_comment|/* NOTHING */
suffix:semicolon
)brace
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
