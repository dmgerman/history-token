multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 - 2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_HUBSTAT_H
DECL|macro|_ASM_IA64_SN_SN1_HUBSTAT_H
mdefine_line|#define _ASM_IA64_SN_SN1_HUBSTAT_H
DECL|typedef|hub_count_t
r_typedef
r_int64
id|hub_count_t
suffix:semicolon
DECL|macro|HUBSTAT_VERSION
mdefine_line|#define HUBSTAT_VERSION&t;1
DECL|struct|hubstat_s
r_typedef
r_struct
id|hubstat_s
(brace
DECL|member|hs_version
r_char
id|hs_version
suffix:semicolon
multiline_comment|/* structure version    */
DECL|member|hs_cnode
id|cnodeid_t
id|hs_cnode
suffix:semicolon
multiline_comment|/* cnode of this hub    */
DECL|member|hs_nasid
id|nasid_t
id|hs_nasid
suffix:semicolon
multiline_comment|/* Nasid of same        */
DECL|member|hs_timebase
r_int64
id|hs_timebase
suffix:semicolon
multiline_comment|/* Time of first sample */
DECL|member|hs_timestamp
r_int64
id|hs_timestamp
suffix:semicolon
multiline_comment|/* Time of last sample&t;*/
DECL|member|hs_per_minute
r_int64
id|hs_per_minute
suffix:semicolon
multiline_comment|/* Ticks per minute &t;*/
r_union
(brace
DECL|member|hs_niu_stat_rev_id
id|hubreg_t
id|hs_niu_stat_rev_id
suffix:semicolon
multiline_comment|/* SN0: Status rev ID */
DECL|member|hs_niu_port_status
id|hubreg_t
id|hs_niu_port_status
suffix:semicolon
multiline_comment|/* SN1: Port status */
DECL|member|hs_niu
)brace
id|hs_niu
suffix:semicolon
DECL|member|hs_ni_retry_errors
id|hub_count_t
id|hs_ni_retry_errors
suffix:semicolon
multiline_comment|/* Total retry errors   */
DECL|member|hs_ni_sn_errors
id|hub_count_t
id|hs_ni_sn_errors
suffix:semicolon
multiline_comment|/* Total sn errors      */
DECL|member|hs_ni_cb_errors
id|hub_count_t
id|hs_ni_cb_errors
suffix:semicolon
multiline_comment|/* Total cb errors      */
DECL|member|hs_ni_overflows
r_int
id|hs_ni_overflows
suffix:semicolon
multiline_comment|/* NI count overflows   */
DECL|member|hs_ii_sn_errors
id|hub_count_t
id|hs_ii_sn_errors
suffix:semicolon
multiline_comment|/* Total sn errors      */
DECL|member|hs_ii_cb_errors
id|hub_count_t
id|hs_ii_cb_errors
suffix:semicolon
multiline_comment|/* Total cb errors      */
DECL|member|hs_ii_overflows
r_int
id|hs_ii_overflows
suffix:semicolon
multiline_comment|/* II count overflows   */
multiline_comment|/*&n;&t; * Anything below this comment is intended for kernel internal-use&n;&t; * only and may be changed at any time.&n;&t; *&n;&t; * Any members that contain pointers or are conditionally compiled&n;&t; * need to be below here also.&n;&t; */
DECL|member|hs_last_print
r_int64
id|hs_last_print
suffix:semicolon
multiline_comment|/* When we last printed */
DECL|member|hs_print
r_char
id|hs_print
suffix:semicolon
multiline_comment|/* Should we print      */
DECL|member|hs_name
r_char
op_star
id|hs_name
suffix:semicolon
multiline_comment|/* This hub&squot;s name */
DECL|member|hs_maint
r_int
r_char
id|hs_maint
suffix:semicolon
multiline_comment|/* Should we print to availmon */
DECL|typedef|hubstat_t
)brace
id|hubstat_t
suffix:semicolon
DECL|macro|hs_ni_stat_rev_id
mdefine_line|#define       hs_ni_stat_rev_id       hs_niu.hs_niu_stat_rev_id
DECL|macro|hs_ni_port_status
mdefine_line|#define       hs_ni_port_status       hs_niu.hs_niu_port_status
r_extern
r_struct
id|file_operations
id|hub_mon_fops
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_SN1_HUBSTAT_H */
eof
