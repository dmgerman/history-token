multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: ib_sa.h 1389 2004-12-27 22:56:47Z roland $&n; */
macro_line|#ifndef IB_SA_H
DECL|macro|IB_SA_H
mdefine_line|#define IB_SA_H
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;ib_verbs.h&gt;
macro_line|#include &lt;ib_mad.h&gt;
r_enum
(brace
DECL|enumerator|IB_SA_CLASS_VERSION
id|IB_SA_CLASS_VERSION
op_assign
l_int|2
comma
multiline_comment|/* IB spec version 1.1/1.2 */
DECL|enumerator|IB_SA_METHOD_DELETE
id|IB_SA_METHOD_DELETE
op_assign
l_int|0x15
)brace
suffix:semicolon
DECL|enum|ib_sa_selector
r_enum
id|ib_sa_selector
(brace
DECL|enumerator|IB_SA_GTE
id|IB_SA_GTE
op_assign
l_int|0
comma
DECL|enumerator|IB_SA_LTE
id|IB_SA_LTE
op_assign
l_int|1
comma
DECL|enumerator|IB_SA_EQ
id|IB_SA_EQ
op_assign
l_int|2
comma
multiline_comment|/*&n;&t; * The meaning of &quot;best&quot; depends on the attribute: for&n;&t; * example, for MTU best will return the largest available&n;&t; * MTU, while for packet life time, best will return the&n;&t; * smallest available life time.&n;&t; */
DECL|enumerator|IB_SA_BEST
id|IB_SA_BEST
op_assign
l_int|3
)brace
suffix:semicolon
DECL|typedef|ib_sa_comp_mask
r_typedef
id|u64
id|__bitwise
id|ib_sa_comp_mask
suffix:semicolon
DECL|macro|IB_SA_COMP_MASK
mdefine_line|#define IB_SA_COMP_MASK(n)&t;((__force ib_sa_comp_mask) cpu_to_be64(1ull &lt;&lt; n))
multiline_comment|/*&n; * Structures for SA records are named &quot;struct ib_sa_xxx_rec.&quot;  No&n; * attempt is made to pack structures to match the physical layout of&n; * SA records in SA MADs; all packing and unpacking is handled by the&n; * SA query code.&n; *&n; * For a record with structure ib_sa_xxx_rec, the naming convention&n; * for the component mask value for field yyy is IB_SA_XXX_REC_YYY (we&n; * never use different abbreviations or otherwise change the spelling&n; * of xxx/yyy between ib_sa_xxx_rec.yyy and IB_SA_XXX_REC_YYY).&n; *&n; * Reserved rows are indicated with comments to help maintainability.&n; */
multiline_comment|/* reserved:&t;&t;&t;&t;&t;&t;&t;&t; 0 */
multiline_comment|/* reserved:&t;&t;&t;&t;&t;&t;&t;&t; 1 */
DECL|macro|IB_SA_PATH_REC_DGID
mdefine_line|#define IB_SA_PATH_REC_DGID&t;&t;&t;&t;IB_SA_COMP_MASK( 2)
DECL|macro|IB_SA_PATH_REC_SGID
mdefine_line|#define IB_SA_PATH_REC_SGID&t;&t;&t;&t;IB_SA_COMP_MASK( 3)
DECL|macro|IB_SA_PATH_REC_DLID
mdefine_line|#define IB_SA_PATH_REC_DLID&t;&t;&t;&t;IB_SA_COMP_MASK( 4)
DECL|macro|IB_SA_PATH_REC_SLID
mdefine_line|#define IB_SA_PATH_REC_SLID&t;&t;&t;&t;IB_SA_COMP_MASK( 5)
DECL|macro|IB_SA_PATH_REC_RAW_TRAFFIC
mdefine_line|#define IB_SA_PATH_REC_RAW_TRAFFIC&t;&t;&t;IB_SA_COMP_MASK( 6)
multiline_comment|/* reserved:&t;&t;&t;&t;&t;&t;&t;&t; 7 */
DECL|macro|IB_SA_PATH_REC_FLOW_LABEL
mdefine_line|#define IB_SA_PATH_REC_FLOW_LABEL       &t;&t;IB_SA_COMP_MASK( 8)
DECL|macro|IB_SA_PATH_REC_HOP_LIMIT
mdefine_line|#define IB_SA_PATH_REC_HOP_LIMIT&t;&t;&t;IB_SA_COMP_MASK( 9)
DECL|macro|IB_SA_PATH_REC_TRAFFIC_CLASS
mdefine_line|#define IB_SA_PATH_REC_TRAFFIC_CLASS&t;&t;&t;IB_SA_COMP_MASK(10)
DECL|macro|IB_SA_PATH_REC_REVERSIBLE
mdefine_line|#define IB_SA_PATH_REC_REVERSIBLE&t;&t;&t;IB_SA_COMP_MASK(11)
DECL|macro|IB_SA_PATH_REC_NUMB_PATH
mdefine_line|#define IB_SA_PATH_REC_NUMB_PATH&t;&t;&t;IB_SA_COMP_MASK(12)
DECL|macro|IB_SA_PATH_REC_PKEY
mdefine_line|#define IB_SA_PATH_REC_PKEY&t;&t;&t;&t;IB_SA_COMP_MASK(13)
multiline_comment|/* reserved:&t;&t;&t;&t;&t;&t;&t;&t;14 */
DECL|macro|IB_SA_PATH_REC_SL
mdefine_line|#define IB_SA_PATH_REC_SL&t;&t;&t;&t;IB_SA_COMP_MASK(15)
DECL|macro|IB_SA_PATH_REC_MTU_SELECTOR
mdefine_line|#define IB_SA_PATH_REC_MTU_SELECTOR&t;&t;&t;IB_SA_COMP_MASK(16)
DECL|macro|IB_SA_PATH_REC_MTU
mdefine_line|#define IB_SA_PATH_REC_MTU&t;&t;&t;&t;IB_SA_COMP_MASK(17)
DECL|macro|IB_SA_PATH_REC_RATE_SELECTOR
mdefine_line|#define IB_SA_PATH_REC_RATE_SELECTOR&t;&t;&t;IB_SA_COMP_MASK(18)
DECL|macro|IB_SA_PATH_REC_RATE
mdefine_line|#define IB_SA_PATH_REC_RATE&t;&t;&t;&t;IB_SA_COMP_MASK(19)
DECL|macro|IB_SA_PATH_REC_PACKET_LIFE_TIME_SELECTOR
mdefine_line|#define IB_SA_PATH_REC_PACKET_LIFE_TIME_SELECTOR&t;IB_SA_COMP_MASK(20)
DECL|macro|IB_SA_PATH_REC_PACKET_LIFE_TIME
mdefine_line|#define IB_SA_PATH_REC_PACKET_LIFE_TIME&t;&t;&t;IB_SA_COMP_MASK(21)
DECL|macro|IB_SA_PATH_REC_PREFERENCE
mdefine_line|#define IB_SA_PATH_REC_PREFERENCE&t;&t;&t;IB_SA_COMP_MASK(22)
DECL|struct|ib_sa_path_rec
r_struct
id|ib_sa_path_rec
(brace
multiline_comment|/* reserved */
multiline_comment|/* reserved */
DECL|member|dgid
r_union
id|ib_gid
id|dgid
suffix:semicolon
DECL|member|sgid
r_union
id|ib_gid
id|sgid
suffix:semicolon
DECL|member|dlid
id|u16
id|dlid
suffix:semicolon
DECL|member|slid
id|u16
id|slid
suffix:semicolon
DECL|member|raw_traffic
r_int
id|raw_traffic
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|flow_label
id|u32
id|flow_label
suffix:semicolon
DECL|member|hop_limit
id|u8
id|hop_limit
suffix:semicolon
DECL|member|traffic_class
id|u8
id|traffic_class
suffix:semicolon
DECL|member|reversible
r_int
id|reversible
suffix:semicolon
DECL|member|numb_path
id|u8
id|numb_path
suffix:semicolon
DECL|member|pkey
id|u16
id|pkey
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|sl
id|u8
id|sl
suffix:semicolon
DECL|member|mtu_selector
id|u8
id|mtu_selector
suffix:semicolon
DECL|member|mtu
r_enum
id|ib_mtu
id|mtu
suffix:semicolon
DECL|member|rate_selector
id|u8
id|rate_selector
suffix:semicolon
DECL|member|rate
id|u8
id|rate
suffix:semicolon
DECL|member|packet_life_time_selector
id|u8
id|packet_life_time_selector
suffix:semicolon
DECL|member|packet_life_time
id|u8
id|packet_life_time
suffix:semicolon
DECL|member|preference
id|u8
id|preference
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IB_SA_MCMEMBER_REC_MGID
mdefine_line|#define IB_SA_MCMEMBER_REC_MGID&t;&t;&t;&t;IB_SA_COMP_MASK( 0)
DECL|macro|IB_SA_MCMEMBER_REC_PORT_GID
mdefine_line|#define IB_SA_MCMEMBER_REC_PORT_GID&t;&t;&t;IB_SA_COMP_MASK( 1)
DECL|macro|IB_SA_MCMEMBER_REC_QKEY
mdefine_line|#define IB_SA_MCMEMBER_REC_QKEY&t;&t;&t;&t;IB_SA_COMP_MASK( 2)
DECL|macro|IB_SA_MCMEMBER_REC_MLID
mdefine_line|#define IB_SA_MCMEMBER_REC_MLID&t;&t;&t;&t;IB_SA_COMP_MASK( 3)
DECL|macro|IB_SA_MCMEMBER_REC_MTU_SELECTOR
mdefine_line|#define IB_SA_MCMEMBER_REC_MTU_SELECTOR&t;&t;&t;IB_SA_COMP_MASK( 4)
DECL|macro|IB_SA_MCMEMBER_REC_MTU
mdefine_line|#define IB_SA_MCMEMBER_REC_MTU&t;&t;&t;&t;IB_SA_COMP_MASK( 5)
DECL|macro|IB_SA_MCMEMBER_REC_TRAFFIC_CLASS
mdefine_line|#define IB_SA_MCMEMBER_REC_TRAFFIC_CLASS&t;&t;IB_SA_COMP_MASK( 6)
DECL|macro|IB_SA_MCMEMBER_REC_PKEY
mdefine_line|#define IB_SA_MCMEMBER_REC_PKEY&t;&t;&t;&t;IB_SA_COMP_MASK( 7)
DECL|macro|IB_SA_MCMEMBER_REC_RATE_SELECTOR
mdefine_line|#define IB_SA_MCMEMBER_REC_RATE_SELECTOR&t;&t;IB_SA_COMP_MASK( 8)
DECL|macro|IB_SA_MCMEMBER_REC_RATE
mdefine_line|#define IB_SA_MCMEMBER_REC_RATE&t;&t;&t;&t;IB_SA_COMP_MASK( 9)
DECL|macro|IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR
mdefine_line|#define IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR&t;IB_SA_COMP_MASK(10)
DECL|macro|IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME
mdefine_line|#define IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME&t;&t;IB_SA_COMP_MASK(11)
DECL|macro|IB_SA_MCMEMBER_REC_SL
mdefine_line|#define IB_SA_MCMEMBER_REC_SL&t;&t;&t;&t;IB_SA_COMP_MASK(12)
DECL|macro|IB_SA_MCMEMBER_REC_FLOW_LABEL
mdefine_line|#define IB_SA_MCMEMBER_REC_FLOW_LABEL&t;&t;&t;IB_SA_COMP_MASK(13)
DECL|macro|IB_SA_MCMEMBER_REC_HOP_LIMIT
mdefine_line|#define IB_SA_MCMEMBER_REC_HOP_LIMIT&t;&t;&t;IB_SA_COMP_MASK(14)
DECL|macro|IB_SA_MCMEMBER_REC_SCOPE
mdefine_line|#define IB_SA_MCMEMBER_REC_SCOPE&t;&t;&t;IB_SA_COMP_MASK(15)
DECL|macro|IB_SA_MCMEMBER_REC_JOIN_STATE
mdefine_line|#define IB_SA_MCMEMBER_REC_JOIN_STATE&t;&t;&t;IB_SA_COMP_MASK(16)
DECL|macro|IB_SA_MCMEMBER_REC_PROXY_JOIN
mdefine_line|#define IB_SA_MCMEMBER_REC_PROXY_JOIN&t;&t;&t;IB_SA_COMP_MASK(17)
DECL|struct|ib_sa_mcmember_rec
r_struct
id|ib_sa_mcmember_rec
(brace
DECL|member|mgid
r_union
id|ib_gid
id|mgid
suffix:semicolon
DECL|member|port_gid
r_union
id|ib_gid
id|port_gid
suffix:semicolon
DECL|member|qkey
id|u32
id|qkey
suffix:semicolon
DECL|member|mlid
id|u16
id|mlid
suffix:semicolon
DECL|member|mtu_selector
id|u8
id|mtu_selector
suffix:semicolon
DECL|member|mtu
r_enum
id|ib_mtu
id|mtu
suffix:semicolon
DECL|member|traffic_class
id|u8
id|traffic_class
suffix:semicolon
DECL|member|pkey
id|u16
id|pkey
suffix:semicolon
DECL|member|rate_selector
id|u8
id|rate_selector
suffix:semicolon
DECL|member|rate
id|u8
id|rate
suffix:semicolon
DECL|member|packet_life_time_selector
id|u8
id|packet_life_time_selector
suffix:semicolon
DECL|member|packet_life_time
id|u8
id|packet_life_time
suffix:semicolon
DECL|member|sl
id|u8
id|sl
suffix:semicolon
DECL|member|flow_label
id|u32
id|flow_label
suffix:semicolon
DECL|member|hop_limit
id|u8
id|hop_limit
suffix:semicolon
DECL|member|scope
id|u8
id|scope
suffix:semicolon
DECL|member|join_state
id|u8
id|join_state
suffix:semicolon
DECL|member|proxy_join
r_int
id|proxy_join
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|ib_sa_query
suffix:semicolon
r_void
id|ib_sa_cancel_query
c_func
(paren
r_int
id|id
comma
r_struct
id|ib_sa_query
op_star
id|query
)paren
suffix:semicolon
r_int
id|ib_sa_path_rec_get
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
id|u8
id|port_num
comma
r_struct
id|ib_sa_path_rec
op_star
id|rec
comma
id|ib_sa_comp_mask
id|comp_mask
comma
r_int
id|timeout_ms
comma
r_int
id|gfp_mask
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
id|status
comma
r_struct
id|ib_sa_path_rec
op_star
id|resp
comma
r_void
op_star
id|context
)paren
comma
r_void
op_star
id|context
comma
r_struct
id|ib_sa_query
op_star
op_star
id|query
)paren
suffix:semicolon
r_int
id|ib_sa_mcmember_rec_query
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
id|u8
id|port_num
comma
id|u8
id|method
comma
r_struct
id|ib_sa_mcmember_rec
op_star
id|rec
comma
id|ib_sa_comp_mask
id|comp_mask
comma
r_int
id|timeout_ms
comma
r_int
id|gfp_mask
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
id|status
comma
r_struct
id|ib_sa_mcmember_rec
op_star
id|resp
comma
r_void
op_star
id|context
)paren
comma
r_void
op_star
id|context
comma
r_struct
id|ib_sa_query
op_star
op_star
id|query
)paren
suffix:semicolon
multiline_comment|/**&n; * ib_sa_mcmember_rec_set - Start an MCMember set query&n; * @device:device to send query on&n; * @port_num: port number to send query on&n; * @rec:MCMember Record to send in query&n; * @comp_mask:component mask to send in query&n; * @timeout_ms:time to wait for response&n; * @gfp_mask:GFP mask to use for internal allocations&n; * @callback:function called when query completes, times out or is&n; * canceled&n; * @context:opaque user context passed to callback&n; * @sa_query:query context, used to cancel query&n; *&n; * Send an MCMember Set query to the SA (eg to join a multicast&n; * group).  The callback function will be called when the query&n; * completes (or fails); status is 0 for a successful response, -EINTR&n; * if the query is canceled, -ETIMEDOUT is the query timed out, or&n; * -EIO if an error occurred sending the query.  The resp parameter of&n; * the callback is only valid if status is 0.&n; *&n; * If the return value of ib_sa_mcmember_rec_set() is negative, it is&n; * an error code.  Otherwise it is a query ID that can be used to&n; * cancel the query.&n; */
r_static
r_inline
r_int
DECL|function|ib_sa_mcmember_rec_set
id|ib_sa_mcmember_rec_set
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
id|u8
id|port_num
comma
r_struct
id|ib_sa_mcmember_rec
op_star
id|rec
comma
id|ib_sa_comp_mask
id|comp_mask
comma
r_int
id|timeout_ms
comma
r_int
id|gfp_mask
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
id|status
comma
r_struct
id|ib_sa_mcmember_rec
op_star
id|resp
comma
r_void
op_star
id|context
)paren
comma
r_void
op_star
id|context
comma
r_struct
id|ib_sa_query
op_star
op_star
id|query
)paren
(brace
r_return
id|ib_sa_mcmember_rec_query
c_func
(paren
id|device
comma
id|port_num
comma
id|IB_MGMT_METHOD_SET
comma
id|rec
comma
id|comp_mask
comma
id|timeout_ms
comma
id|gfp_mask
comma
id|callback
comma
id|context
comma
id|query
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * ib_sa_mcmember_rec_delete - Start an MCMember delete query&n; * @device:device to send query on&n; * @port_num: port number to send query on&n; * @rec:MCMember Record to send in query&n; * @comp_mask:component mask to send in query&n; * @timeout_ms:time to wait for response&n; * @gfp_mask:GFP mask to use for internal allocations&n; * @callback:function called when query completes, times out or is&n; * canceled&n; * @context:opaque user context passed to callback&n; * @sa_query:query context, used to cancel query&n; *&n; * Send an MCMember Delete query to the SA (eg to leave a multicast&n; * group).  The callback function will be called when the query&n; * completes (or fails); status is 0 for a successful response, -EINTR&n; * if the query is canceled, -ETIMEDOUT is the query timed out, or&n; * -EIO if an error occurred sending the query.  The resp parameter of&n; * the callback is only valid if status is 0.&n; *&n; * If the return value of ib_sa_mcmember_rec_delete() is negative, it&n; * is an error code.  Otherwise it is a query ID that can be used to&n; * cancel the query.&n; */
r_static
r_inline
r_int
DECL|function|ib_sa_mcmember_rec_delete
id|ib_sa_mcmember_rec_delete
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
id|u8
id|port_num
comma
r_struct
id|ib_sa_mcmember_rec
op_star
id|rec
comma
id|ib_sa_comp_mask
id|comp_mask
comma
r_int
id|timeout_ms
comma
r_int
id|gfp_mask
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
id|status
comma
r_struct
id|ib_sa_mcmember_rec
op_star
id|resp
comma
r_void
op_star
id|context
)paren
comma
r_void
op_star
id|context
comma
r_struct
id|ib_sa_query
op_star
op_star
id|query
)paren
(brace
r_return
id|ib_sa_mcmember_rec_query
c_func
(paren
id|device
comma
id|port_num
comma
id|IB_SA_METHOD_DELETE
comma
id|rec
comma
id|comp_mask
comma
id|timeout_ms
comma
id|gfp_mask
comma
id|callback
comma
id|context
comma
id|query
)paren
suffix:semicolon
)brace
macro_line|#endif /* IB_SA_H */
eof
