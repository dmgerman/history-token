multiline_comment|/* atm_zatm.h - Driver-specific declarations of the ZATM driver (for use by&n;&t;&t;driver-specific utilities) */
multiline_comment|/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef LINUX_ATM_ZATM_H
DECL|macro|LINUX_ATM_ZATM_H
mdefine_line|#define LINUX_ATM_ZATM_H
multiline_comment|/*&n; * Note: non-kernel programs including this file must also include&n; * sys/types.h for struct timeval&n; */
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|ZATM_GETPOOL
mdefine_line|#define ZATM_GETPOOL&t;_IOW(&squot;a&squot;,ATMIOC_SARPRV+1,struct atmif_sioc)
multiline_comment|/* get pool statistics */
DECL|macro|ZATM_GETPOOLZ
mdefine_line|#define ZATM_GETPOOLZ&t;_IOW(&squot;a&squot;,ATMIOC_SARPRV+2,struct atmif_sioc)
multiline_comment|/* get statistics and zero */
DECL|macro|ZATM_SETPOOL
mdefine_line|#define ZATM_SETPOOL&t;_IOW(&squot;a&squot;,ATMIOC_SARPRV+3,struct atmif_sioc)
multiline_comment|/* set pool parameters */
DECL|macro|ZATM_GETTHIST
mdefine_line|#define ZATM_GETTHIST&t;_IOW(&squot;a&squot;,ATMIOC_SARPRV+4,struct atmif_sioc)
multiline_comment|/* get a history of timer&n;&t;&t;&t;&t;&t;&t;   differences */
DECL|struct|zatm_pool_info
r_struct
id|zatm_pool_info
(brace
DECL|member|ref_count
r_int
id|ref_count
suffix:semicolon
multiline_comment|/* free buffer pool usage counters */
DECL|member|low_water
DECL|member|high_water
r_int
id|low_water
comma
id|high_water
suffix:semicolon
multiline_comment|/* refill parameters */
DECL|member|rqa_count
DECL|member|rqu_count
r_int
id|rqa_count
comma
id|rqu_count
suffix:semicolon
multiline_comment|/* queue condition counters */
DECL|member|offset
DECL|member|next_off
r_int
id|offset
comma
id|next_off
suffix:semicolon
multiline_comment|/* alignment optimizations: offset */
DECL|member|next_cnt
DECL|member|next_thres
r_int
id|next_cnt
comma
id|next_thres
suffix:semicolon
multiline_comment|/* repetition counter and threshold */
)brace
suffix:semicolon
DECL|struct|zatm_pool_req
r_struct
id|zatm_pool_req
(brace
DECL|member|pool_num
r_int
id|pool_num
suffix:semicolon
multiline_comment|/* pool number */
DECL|member|info
r_struct
id|zatm_pool_info
id|info
suffix:semicolon
multiline_comment|/* actual information */
)brace
suffix:semicolon
DECL|struct|zatm_t_hist
r_struct
id|zatm_t_hist
(brace
DECL|member|real
r_struct
id|timeval
id|real
suffix:semicolon
multiline_comment|/* real (wall-clock) time */
DECL|member|expected
r_struct
id|timeval
id|expected
suffix:semicolon
multiline_comment|/* expected real time */
)brace
suffix:semicolon
DECL|macro|ZATM_OAM_POOL
mdefine_line|#define ZATM_OAM_POOL&t;&t;0&t;/* free buffer pool for OAM cells */
DECL|macro|ZATM_AAL0_POOL
mdefine_line|#define ZATM_AAL0_POOL&t;&t;1&t;/* free buffer pool for AAL0 cells */
DECL|macro|ZATM_AAL5_POOL_BASE
mdefine_line|#define ZATM_AAL5_POOL_BASE&t;2&t;/* first AAL5 free buffer pool */
DECL|macro|ZATM_LAST_POOL
mdefine_line|#define ZATM_LAST_POOL&t;ZATM_AAL5_POOL_BASE+10 /* max. 64 kB */
DECL|macro|ZATM_TIMER_HISTORY_SIZE
mdefine_line|#define ZATM_TIMER_HISTORY_SIZE&t;16&t;/* number of timer adjustments to&n;&t;&t;&t;&t;&t;   record; must be 2^n */
macro_line|#endif
eof
