multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_XTALK_XBOW_INFO_H
DECL|macro|_ASM_IA64_SN_XTALK_XBOW_INFO_H
mdefine_line|#define _ASM_IA64_SN_XTALK_XBOW_INFO_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|XBOW_PERF_MODES
mdefine_line|#define XBOW_PERF_MODES&t;       0x03
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
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_XTALK_XBOW_INFO_H */
eof
