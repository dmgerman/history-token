multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_XTALK_XBOW_INFO_H
DECL|macro|_ASM_SN_XTALK_XBOW_INFO_H
mdefine_line|#define _ASM_SN_XTALK_XBOW_INFO_H
DECL|macro|XBOW_PERF_MODES
mdefine_line|#define XBOW_PERF_MODES&t;       0x03
DECL|macro|XBOW_PERF_COUNTERS
mdefine_line|#define XBOW_PERF_COUNTERS     0x02
DECL|macro|XBOW_MONITOR_NONE
mdefine_line|#define XBOW_MONITOR_NONE      0x00
DECL|macro|XBOW_MONITOR_SRC_LINK
mdefine_line|#define XBOW_MONITOR_SRC_LINK  0x01
DECL|macro|XBOW_MONITOR_DEST_LINK
mdefine_line|#define XBOW_MONITOR_DEST_LINK 0x02
DECL|macro|XBOW_MONITOR_INP_PKT
mdefine_line|#define XBOW_MONITOR_INP_PKT   0x03
DECL|macro|XBOW_MONITOR_MULTIPLEX
mdefine_line|#define XBOW_MONITOR_MULTIPLEX 0x04
DECL|macro|XBOW_LINK_MULTIPLEX
mdefine_line|#define XBOW_LINK_MULTIPLEX    0x20
DECL|macro|XBOW_PERF_TIMEOUT
mdefine_line|#define XBOW_PERF_TIMEOUT&t;4
DECL|macro|XBOW_STATS_TIMEOUT
mdefine_line|#define XBOW_STATS_TIMEOUT&t;HZ
DECL|struct|xbow_perf_link
r_typedef
r_struct
id|xbow_perf_link
(brace
DECL|member|xlp_cumulative
r_uint64
id|xlp_cumulative
(braket
id|XBOW_PERF_MODES
)braket
suffix:semicolon
DECL|member|xlp_link_alive
r_int
r_char
id|xlp_link_alive
suffix:semicolon
DECL|typedef|xbow_perf_link_t
)brace
id|xbow_perf_link_t
suffix:semicolon
DECL|struct|xbow_link_status
r_typedef
r_struct
id|xbow_link_status
(brace
DECL|member|rx_err_count
r_uint64
id|rx_err_count
suffix:semicolon
DECL|member|tx_retry_count
r_uint64
id|tx_retry_count
suffix:semicolon
DECL|typedef|xbow_link_status_t
)brace
id|xbow_link_status_t
suffix:semicolon
DECL|struct|xbow_perf
r_typedef
r_struct
id|xbow_perf
(brace
DECL|member|xp_current
r_uint32
id|xp_current
suffix:semicolon
DECL|member|xp_link
r_int
r_char
id|xp_link
suffix:semicolon
DECL|member|xp_mode
r_int
r_char
id|xp_mode
suffix:semicolon
DECL|member|xp_curlink
r_int
r_char
id|xp_curlink
suffix:semicolon
DECL|member|xp_curmode
r_int
r_char
id|xp_curmode
suffix:semicolon
DECL|member|xp_perf_reg
r_volatile
r_uint32
op_star
id|xp_perf_reg
suffix:semicolon
DECL|typedef|xbow_perf_t
)brace
id|xbow_perf_t
suffix:semicolon
r_extern
r_void
id|xbow_update_perf_counters
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
id|xbow_perf_link_t
op_star
id|xbow_get_perf_counters
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
r_int
id|xbow_enable_perf_counter
c_func
(paren
id|devfs_handle_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|XBOWIOC_PERF_ENABLE
mdefine_line|#define XBOWIOC_PERF_ENABLE&t;  &t;1
DECL|macro|XBOWIOC_PERF_DISABLE
mdefine_line|#define XBOWIOC_PERF_DISABLE&t; &t;2
DECL|macro|XBOWIOC_PERF_GET
mdefine_line|#define XBOWIOC_PERF_GET&t; &t;3
DECL|macro|XBOWIOC_LLP_ERROR_ENABLE
mdefine_line|#define XBOWIOC_LLP_ERROR_ENABLE &t;4
DECL|macro|XBOWIOC_LLP_ERROR_DISABLE
mdefine_line|#define XBOWIOC_LLP_ERROR_DISABLE&t;5
DECL|macro|XBOWIOC_LLP_ERROR_GET
mdefine_line|#define XBOWIOC_LLP_ERROR_GET&t; &t;6
DECL|struct|xbow_perfarg_t
r_struct
id|xbow_perfarg_t
(brace
DECL|member|link
r_int
id|link
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|counter
r_int
id|counter
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_SN_XTALK_XBOW_INFO_H */
eof
