multiline_comment|/*&n; * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.&n; * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.&n; * Copyright (c) 2004 Intel Corporation.  All rights reserved.&n; * Copyright (c) 2004 Topspin Corporation.  All rights reserved.&n; * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: verbs.c 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;ib_verbs.h&gt;
multiline_comment|/* Protection domains */
DECL|function|ib_alloc_pd
r_struct
id|ib_pd
op_star
id|ib_alloc_pd
c_func
(paren
r_struct
id|ib_device
op_star
id|device
)paren
(brace
r_struct
id|ib_pd
op_star
id|pd
suffix:semicolon
id|pd
op_assign
id|device
op_member_access_from_pointer
id|alloc_pd
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|pd
)paren
)paren
(brace
id|pd-&gt;device
op_assign
id|device
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|pd-&gt;usecnt
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|pd
suffix:semicolon
)brace
DECL|variable|ib_alloc_pd
id|EXPORT_SYMBOL
c_func
(paren
id|ib_alloc_pd
)paren
suffix:semicolon
DECL|function|ib_dealloc_pd
r_int
id|ib_dealloc_pd
c_func
(paren
r_struct
id|ib_pd
op_star
id|pd
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_return
id|pd-&gt;device
op_member_access_from_pointer
id|dealloc_pd
c_func
(paren
id|pd
)paren
suffix:semicolon
)brace
DECL|variable|ib_dealloc_pd
id|EXPORT_SYMBOL
c_func
(paren
id|ib_dealloc_pd
)paren
suffix:semicolon
multiline_comment|/* Address handles */
DECL|function|ib_create_ah
r_struct
id|ib_ah
op_star
id|ib_create_ah
c_func
(paren
r_struct
id|ib_pd
op_star
id|pd
comma
r_struct
id|ib_ah_attr
op_star
id|ah_attr
)paren
(brace
r_struct
id|ib_ah
op_star
id|ah
suffix:semicolon
id|ah
op_assign
id|pd-&gt;device
op_member_access_from_pointer
id|create_ah
c_func
(paren
id|pd
comma
id|ah_attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|ah
)paren
)paren
(brace
id|ah-&gt;device
op_assign
id|pd-&gt;device
suffix:semicolon
id|ah-&gt;pd
op_assign
id|pd
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
)brace
r_return
id|ah
suffix:semicolon
)brace
DECL|variable|ib_create_ah
id|EXPORT_SYMBOL
c_func
(paren
id|ib_create_ah
)paren
suffix:semicolon
DECL|function|ib_modify_ah
r_int
id|ib_modify_ah
c_func
(paren
r_struct
id|ib_ah
op_star
id|ah
comma
r_struct
id|ib_ah_attr
op_star
id|ah_attr
)paren
(brace
r_return
id|ah-&gt;device-&gt;modify_ah
ques
c_cond
id|ah-&gt;device
op_member_access_from_pointer
id|modify_ah
c_func
(paren
id|ah
comma
id|ah_attr
)paren
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|variable|ib_modify_ah
id|EXPORT_SYMBOL
c_func
(paren
id|ib_modify_ah
)paren
suffix:semicolon
DECL|function|ib_query_ah
r_int
id|ib_query_ah
c_func
(paren
r_struct
id|ib_ah
op_star
id|ah
comma
r_struct
id|ib_ah_attr
op_star
id|ah_attr
)paren
(brace
r_return
id|ah-&gt;device-&gt;query_ah
ques
c_cond
id|ah-&gt;device
op_member_access_from_pointer
id|query_ah
c_func
(paren
id|ah
comma
id|ah_attr
)paren
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|variable|ib_query_ah
id|EXPORT_SYMBOL
c_func
(paren
id|ib_query_ah
)paren
suffix:semicolon
DECL|function|ib_destroy_ah
r_int
id|ib_destroy_ah
c_func
(paren
r_struct
id|ib_ah
op_star
id|ah
)paren
(brace
r_struct
id|ib_pd
op_star
id|pd
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pd
op_assign
id|ah-&gt;pd
suffix:semicolon
id|ret
op_assign
id|ah-&gt;device
op_member_access_from_pointer
id|destroy_ah
c_func
(paren
id|ah
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|atomic_dec
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ib_destroy_ah
id|EXPORT_SYMBOL
c_func
(paren
id|ib_destroy_ah
)paren
suffix:semicolon
multiline_comment|/* Queue pairs */
DECL|function|ib_create_qp
r_struct
id|ib_qp
op_star
id|ib_create_qp
c_func
(paren
r_struct
id|ib_pd
op_star
id|pd
comma
r_struct
id|ib_qp_init_attr
op_star
id|qp_init_attr
)paren
(brace
r_struct
id|ib_qp
op_star
id|qp
suffix:semicolon
id|qp
op_assign
id|pd-&gt;device
op_member_access_from_pointer
id|create_qp
c_func
(paren
id|pd
comma
id|qp_init_attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|qp
)paren
)paren
(brace
id|qp-&gt;device
op_assign
id|pd-&gt;device
suffix:semicolon
id|qp-&gt;pd
op_assign
id|pd
suffix:semicolon
id|qp-&gt;send_cq
op_assign
id|qp_init_attr-&gt;send_cq
suffix:semicolon
id|qp-&gt;recv_cq
op_assign
id|qp_init_attr-&gt;recv_cq
suffix:semicolon
id|qp-&gt;srq
op_assign
id|qp_init_attr-&gt;srq
suffix:semicolon
id|qp-&gt;event_handler
op_assign
id|qp_init_attr-&gt;event_handler
suffix:semicolon
id|qp-&gt;qp_context
op_assign
id|qp_init_attr-&gt;qp_context
suffix:semicolon
id|qp-&gt;qp_type
op_assign
id|qp_init_attr-&gt;qp_type
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|qp_init_attr-&gt;send_cq-&gt;usecnt
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|qp_init_attr-&gt;recv_cq-&gt;usecnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qp_init_attr-&gt;srq
)paren
id|atomic_inc
c_func
(paren
op_amp
id|qp_init_attr-&gt;srq-&gt;usecnt
)paren
suffix:semicolon
)brace
r_return
id|qp
suffix:semicolon
)brace
DECL|variable|ib_create_qp
id|EXPORT_SYMBOL
c_func
(paren
id|ib_create_qp
)paren
suffix:semicolon
DECL|function|ib_modify_qp
r_int
id|ib_modify_qp
c_func
(paren
r_struct
id|ib_qp
op_star
id|qp
comma
r_struct
id|ib_qp_attr
op_star
id|qp_attr
comma
r_int
id|qp_attr_mask
)paren
(brace
r_return
id|qp-&gt;device
op_member_access_from_pointer
id|modify_qp
c_func
(paren
id|qp
comma
id|qp_attr
comma
id|qp_attr_mask
)paren
suffix:semicolon
)brace
DECL|variable|ib_modify_qp
id|EXPORT_SYMBOL
c_func
(paren
id|ib_modify_qp
)paren
suffix:semicolon
DECL|function|ib_query_qp
r_int
id|ib_query_qp
c_func
(paren
r_struct
id|ib_qp
op_star
id|qp
comma
r_struct
id|ib_qp_attr
op_star
id|qp_attr
comma
r_int
id|qp_attr_mask
comma
r_struct
id|ib_qp_init_attr
op_star
id|qp_init_attr
)paren
(brace
r_return
id|qp-&gt;device-&gt;query_qp
ques
c_cond
id|qp-&gt;device
op_member_access_from_pointer
id|query_qp
c_func
(paren
id|qp
comma
id|qp_attr
comma
id|qp_attr_mask
comma
id|qp_init_attr
)paren
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|variable|ib_query_qp
id|EXPORT_SYMBOL
c_func
(paren
id|ib_query_qp
)paren
suffix:semicolon
DECL|function|ib_destroy_qp
r_int
id|ib_destroy_qp
c_func
(paren
r_struct
id|ib_qp
op_star
id|qp
)paren
(brace
r_struct
id|ib_pd
op_star
id|pd
suffix:semicolon
r_struct
id|ib_cq
op_star
id|scq
comma
op_star
id|rcq
suffix:semicolon
r_struct
id|ib_srq
op_star
id|srq
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pd
op_assign
id|qp-&gt;pd
suffix:semicolon
id|scq
op_assign
id|qp-&gt;send_cq
suffix:semicolon
id|rcq
op_assign
id|qp-&gt;recv_cq
suffix:semicolon
id|srq
op_assign
id|qp-&gt;srq
suffix:semicolon
id|ret
op_assign
id|qp-&gt;device
op_member_access_from_pointer
id|destroy_qp
c_func
(paren
id|qp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|scq-&gt;usecnt
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|rcq-&gt;usecnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srq
)paren
id|atomic_dec
c_func
(paren
op_amp
id|srq-&gt;usecnt
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ib_destroy_qp
id|EXPORT_SYMBOL
c_func
(paren
id|ib_destroy_qp
)paren
suffix:semicolon
multiline_comment|/* Completion queues */
DECL|function|ib_create_cq
r_struct
id|ib_cq
op_star
id|ib_create_cq
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
id|ib_comp_handler
id|comp_handler
comma
r_void
(paren
op_star
id|event_handler
)paren
(paren
r_struct
id|ib_event
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
id|cq_context
comma
r_int
id|cqe
)paren
(brace
r_struct
id|ib_cq
op_star
id|cq
suffix:semicolon
id|cq
op_assign
id|device
op_member_access_from_pointer
id|create_cq
c_func
(paren
id|device
comma
id|cqe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|cq
)paren
)paren
(brace
id|cq-&gt;device
op_assign
id|device
suffix:semicolon
id|cq-&gt;comp_handler
op_assign
id|comp_handler
suffix:semicolon
id|cq-&gt;event_handler
op_assign
id|event_handler
suffix:semicolon
id|cq-&gt;cq_context
op_assign
id|cq_context
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|cq-&gt;usecnt
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|cq
suffix:semicolon
)brace
DECL|variable|ib_create_cq
id|EXPORT_SYMBOL
c_func
(paren
id|ib_create_cq
)paren
suffix:semicolon
DECL|function|ib_destroy_cq
r_int
id|ib_destroy_cq
c_func
(paren
r_struct
id|ib_cq
op_star
id|cq
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|cq-&gt;usecnt
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_return
id|cq-&gt;device
op_member_access_from_pointer
id|destroy_cq
c_func
(paren
id|cq
)paren
suffix:semicolon
)brace
DECL|variable|ib_destroy_cq
id|EXPORT_SYMBOL
c_func
(paren
id|ib_destroy_cq
)paren
suffix:semicolon
DECL|function|ib_resize_cq
r_int
id|ib_resize_cq
c_func
(paren
r_struct
id|ib_cq
op_star
id|cq
comma
r_int
id|cqe
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cq-&gt;device-&gt;resize_cq
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|ret
op_assign
id|cq-&gt;device
op_member_access_from_pointer
id|resize_cq
c_func
(paren
id|cq
comma
op_amp
id|cqe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|cq-&gt;cqe
op_assign
id|cqe
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ib_resize_cq
id|EXPORT_SYMBOL
c_func
(paren
id|ib_resize_cq
)paren
suffix:semicolon
multiline_comment|/* Memory regions */
DECL|function|ib_get_dma_mr
r_struct
id|ib_mr
op_star
id|ib_get_dma_mr
c_func
(paren
r_struct
id|ib_pd
op_star
id|pd
comma
r_int
id|mr_access_flags
)paren
(brace
r_struct
id|ib_mr
op_star
id|mr
suffix:semicolon
id|mr
op_assign
id|pd-&gt;device
op_member_access_from_pointer
id|get_dma_mr
c_func
(paren
id|pd
comma
id|mr_access_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|mr
)paren
)paren
(brace
id|mr-&gt;device
op_assign
id|pd-&gt;device
suffix:semicolon
id|mr-&gt;pd
op_assign
id|pd
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mr-&gt;usecnt
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|mr
suffix:semicolon
)brace
DECL|variable|ib_get_dma_mr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_get_dma_mr
)paren
suffix:semicolon
DECL|function|ib_reg_phys_mr
r_struct
id|ib_mr
op_star
id|ib_reg_phys_mr
c_func
(paren
r_struct
id|ib_pd
op_star
id|pd
comma
r_struct
id|ib_phys_buf
op_star
id|phys_buf_array
comma
r_int
id|num_phys_buf
comma
r_int
id|mr_access_flags
comma
id|u64
op_star
id|iova_start
)paren
(brace
r_struct
id|ib_mr
op_star
id|mr
suffix:semicolon
id|mr
op_assign
id|pd-&gt;device
op_member_access_from_pointer
id|reg_phys_mr
c_func
(paren
id|pd
comma
id|phys_buf_array
comma
id|num_phys_buf
comma
id|mr_access_flags
comma
id|iova_start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|mr
)paren
)paren
(brace
id|mr-&gt;device
op_assign
id|pd-&gt;device
suffix:semicolon
id|mr-&gt;pd
op_assign
id|pd
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mr-&gt;usecnt
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|mr
suffix:semicolon
)brace
DECL|variable|ib_reg_phys_mr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_reg_phys_mr
)paren
suffix:semicolon
DECL|function|ib_rereg_phys_mr
r_int
id|ib_rereg_phys_mr
c_func
(paren
r_struct
id|ib_mr
op_star
id|mr
comma
r_int
id|mr_rereg_mask
comma
r_struct
id|ib_pd
op_star
id|pd
comma
r_struct
id|ib_phys_buf
op_star
id|phys_buf_array
comma
r_int
id|num_phys_buf
comma
r_int
id|mr_access_flags
comma
id|u64
op_star
id|iova_start
)paren
(brace
r_struct
id|ib_pd
op_star
id|old_pd
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mr-&gt;device-&gt;rereg_phys_mr
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|mr-&gt;usecnt
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|old_pd
op_assign
id|mr-&gt;pd
suffix:semicolon
id|ret
op_assign
id|mr-&gt;device
op_member_access_from_pointer
id|rereg_phys_mr
c_func
(paren
id|mr
comma
id|mr_rereg_mask
comma
id|pd
comma
id|phys_buf_array
comma
id|num_phys_buf
comma
id|mr_access_flags
comma
id|iova_start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
(paren
id|mr_rereg_mask
op_amp
id|IB_MR_REREG_PD
)paren
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|old_pd-&gt;usecnt
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ib_rereg_phys_mr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_rereg_phys_mr
)paren
suffix:semicolon
DECL|function|ib_query_mr
r_int
id|ib_query_mr
c_func
(paren
r_struct
id|ib_mr
op_star
id|mr
comma
r_struct
id|ib_mr_attr
op_star
id|mr_attr
)paren
(brace
r_return
id|mr-&gt;device-&gt;query_mr
ques
c_cond
id|mr-&gt;device
op_member_access_from_pointer
id|query_mr
c_func
(paren
id|mr
comma
id|mr_attr
)paren
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|variable|ib_query_mr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_query_mr
)paren
suffix:semicolon
DECL|function|ib_dereg_mr
r_int
id|ib_dereg_mr
c_func
(paren
r_struct
id|ib_mr
op_star
id|mr
)paren
(brace
r_struct
id|ib_pd
op_star
id|pd
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|mr-&gt;usecnt
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|pd
op_assign
id|mr-&gt;pd
suffix:semicolon
id|ret
op_assign
id|mr-&gt;device
op_member_access_from_pointer
id|dereg_mr
c_func
(paren
id|mr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|atomic_dec
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ib_dereg_mr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_dereg_mr
)paren
suffix:semicolon
multiline_comment|/* Memory windows */
DECL|function|ib_alloc_mw
r_struct
id|ib_mw
op_star
id|ib_alloc_mw
c_func
(paren
r_struct
id|ib_pd
op_star
id|pd
)paren
(brace
r_struct
id|ib_mw
op_star
id|mw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pd-&gt;device-&gt;alloc_mw
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSYS
)paren
suffix:semicolon
id|mw
op_assign
id|pd-&gt;device
op_member_access_from_pointer
id|alloc_mw
c_func
(paren
id|pd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|mw
)paren
)paren
(brace
id|mw-&gt;device
op_assign
id|pd-&gt;device
suffix:semicolon
id|mw-&gt;pd
op_assign
id|pd
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
)brace
r_return
id|mw
suffix:semicolon
)brace
DECL|variable|ib_alloc_mw
id|EXPORT_SYMBOL
c_func
(paren
id|ib_alloc_mw
)paren
suffix:semicolon
DECL|function|ib_dealloc_mw
r_int
id|ib_dealloc_mw
c_func
(paren
r_struct
id|ib_mw
op_star
id|mw
)paren
(brace
r_struct
id|ib_pd
op_star
id|pd
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pd
op_assign
id|mw-&gt;pd
suffix:semicolon
id|ret
op_assign
id|mw-&gt;device
op_member_access_from_pointer
id|dealloc_mw
c_func
(paren
id|mw
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|atomic_dec
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ib_dealloc_mw
id|EXPORT_SYMBOL
c_func
(paren
id|ib_dealloc_mw
)paren
suffix:semicolon
multiline_comment|/* &quot;Fast&quot; memory regions */
DECL|function|ib_alloc_fmr
r_struct
id|ib_fmr
op_star
id|ib_alloc_fmr
c_func
(paren
r_struct
id|ib_pd
op_star
id|pd
comma
r_int
id|mr_access_flags
comma
r_struct
id|ib_fmr_attr
op_star
id|fmr_attr
)paren
(brace
r_struct
id|ib_fmr
op_star
id|fmr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pd-&gt;device-&gt;alloc_fmr
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSYS
)paren
suffix:semicolon
id|fmr
op_assign
id|pd-&gt;device
op_member_access_from_pointer
id|alloc_fmr
c_func
(paren
id|pd
comma
id|mr_access_flags
comma
id|fmr_attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|fmr
)paren
)paren
(brace
id|fmr-&gt;device
op_assign
id|pd-&gt;device
suffix:semicolon
id|fmr-&gt;pd
op_assign
id|pd
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
)brace
r_return
id|fmr
suffix:semicolon
)brace
DECL|variable|ib_alloc_fmr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_alloc_fmr
)paren
suffix:semicolon
DECL|function|ib_unmap_fmr
r_int
id|ib_unmap_fmr
c_func
(paren
r_struct
id|list_head
op_star
id|fmr_list
)paren
(brace
r_struct
id|ib_fmr
op_star
id|fmr
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
id|fmr_list
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|fmr
op_assign
id|list_entry
c_func
(paren
id|fmr_list-&gt;next
comma
r_struct
id|ib_fmr
comma
id|list
)paren
suffix:semicolon
r_return
id|fmr-&gt;device
op_member_access_from_pointer
id|unmap_fmr
c_func
(paren
id|fmr_list
)paren
suffix:semicolon
)brace
DECL|variable|ib_unmap_fmr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_unmap_fmr
)paren
suffix:semicolon
DECL|function|ib_dealloc_fmr
r_int
id|ib_dealloc_fmr
c_func
(paren
r_struct
id|ib_fmr
op_star
id|fmr
)paren
(brace
r_struct
id|ib_pd
op_star
id|pd
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pd
op_assign
id|fmr-&gt;pd
suffix:semicolon
id|ret
op_assign
id|fmr-&gt;device
op_member_access_from_pointer
id|dealloc_fmr
c_func
(paren
id|fmr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|atomic_dec
c_func
(paren
op_amp
id|pd-&gt;usecnt
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ib_dealloc_fmr
id|EXPORT_SYMBOL
c_func
(paren
id|ib_dealloc_fmr
)paren
suffix:semicolon
multiline_comment|/* Multicast groups */
DECL|function|ib_attach_mcast
r_int
id|ib_attach_mcast
c_func
(paren
r_struct
id|ib_qp
op_star
id|qp
comma
r_union
id|ib_gid
op_star
id|gid
comma
id|u16
id|lid
)paren
(brace
r_return
id|qp-&gt;device-&gt;attach_mcast
ques
c_cond
id|qp-&gt;device
op_member_access_from_pointer
id|attach_mcast
c_func
(paren
id|qp
comma
id|gid
comma
id|lid
)paren
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|variable|ib_attach_mcast
id|EXPORT_SYMBOL
c_func
(paren
id|ib_attach_mcast
)paren
suffix:semicolon
DECL|function|ib_detach_mcast
r_int
id|ib_detach_mcast
c_func
(paren
r_struct
id|ib_qp
op_star
id|qp
comma
r_union
id|ib_gid
op_star
id|gid
comma
id|u16
id|lid
)paren
(brace
r_return
id|qp-&gt;device-&gt;detach_mcast
ques
c_cond
id|qp-&gt;device
op_member_access_from_pointer
id|detach_mcast
c_func
(paren
id|qp
comma
id|gid
comma
id|lid
)paren
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|variable|ib_detach_mcast
id|EXPORT_SYMBOL
c_func
(paren
id|ib_detach_mcast
)paren
suffix:semicolon
eof
