macro_line|#ifndef __NET_PKT_SCHED_H
DECL|macro|__NET_PKT_SCHED_H
mdefine_line|#define __NET_PKT_SCHED_H
macro_line|#include &lt;net/sch_generic.h&gt;
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
r_extern
id|rwlock_t
id|qdisc_tree_lock
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
r_static
r_inline
r_int
DECL|function|psched_tod_diff
id|psched_tod_diff
c_func
(paren
r_int
id|delta_sec
comma
r_int
id|bound
)paren
(brace
r_int
id|delta
suffix:semicolon
r_if
c_cond
(paren
id|bound
op_le
l_int|1000000
op_logical_or
id|delta_sec
OG
(paren
l_int|0x7FFFFFFF
op_div
l_int|1000000
)paren
op_minus
l_int|1
)paren
r_return
id|bound
suffix:semicolon
id|delta
op_assign
id|delta_sec
op_star
l_int|1000000
suffix:semicolon
r_if
c_cond
(paren
id|delta
OG
id|bound
)paren
id|delta
op_assign
id|bound
suffix:semicolon
r_return
id|delta
suffix:semicolon
)brace
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
r_int
id|tc_classify
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
