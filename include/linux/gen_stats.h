macro_line|#ifndef __LINUX_GEN_STATS_H
DECL|macro|__LINUX_GEN_STATS_H
mdefine_line|#define __LINUX_GEN_STATS_H
macro_line|#include &lt;linux/types.h&gt;
r_enum
(brace
DECL|enumerator|TCA_STATS_UNSPEC
id|TCA_STATS_UNSPEC
comma
DECL|enumerator|TCA_STATS_BASIC
id|TCA_STATS_BASIC
comma
DECL|enumerator|TCA_STATS_RATE_EST
id|TCA_STATS_RATE_EST
comma
DECL|enumerator|TCA_STATS_QUEUE
id|TCA_STATS_QUEUE
comma
DECL|enumerator|TCA_STATS_APP
id|TCA_STATS_APP
comma
DECL|enumerator|__TCA_STATS_MAX
id|__TCA_STATS_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_STATS_MAX
mdefine_line|#define TCA_STATS_MAX (__TCA_STATS_MAX - 1)
multiline_comment|/**&n; * struct gnet_stats_basic - byte/packet throughput statistics&n; * @bytes: number of seen bytes&n; * @packets: number of seen packets&n; */
DECL|struct|gnet_stats_basic
r_struct
id|gnet_stats_basic
(brace
DECL|member|bytes
id|__u64
id|bytes
suffix:semicolon
DECL|member|packets
id|__u32
id|packets
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct gnet_stats_rate_est - rate estimator&n; * @bps: current byte rate&n; * @pps: current packet rate&n; */
DECL|struct|gnet_stats_rate_est
r_struct
id|gnet_stats_rate_est
(brace
DECL|member|bps
id|__u32
id|bps
suffix:semicolon
DECL|member|pps
id|__u32
id|pps
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct gnet_stats_queue - queuing statistics&n; * @qlen: queue length&n; * @backlog: backlog size of queue&n; * @drops: number of dropped packets&n; * @requeues: number of requeues&n; * @overlimits: number of enqueues over the limit&n; */
DECL|struct|gnet_stats_queue
r_struct
id|gnet_stats_queue
(brace
DECL|member|qlen
id|__u32
id|qlen
suffix:semicolon
DECL|member|backlog
id|__u32
id|backlog
suffix:semicolon
DECL|member|drops
id|__u32
id|drops
suffix:semicolon
DECL|member|requeues
id|__u32
id|requeues
suffix:semicolon
DECL|member|overlimits
id|__u32
id|overlimits
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct gnet_estimator - rate estimator configuration&n; * @interval: sampling period&n; * @ewma_log: the log of measurement window weight&n; */
DECL|struct|gnet_estimator
r_struct
id|gnet_estimator
(brace
DECL|member|interval
r_int
r_char
id|interval
suffix:semicolon
DECL|member|ewma_log
r_int
r_char
id|ewma_log
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_GEN_STATS_H */
eof
