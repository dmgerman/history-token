multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_profile.c 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &quot;mthca_profile.h&quot;
r_enum
(brace
DECL|enumerator|MTHCA_RES_QP
id|MTHCA_RES_QP
comma
DECL|enumerator|MTHCA_RES_EEC
id|MTHCA_RES_EEC
comma
DECL|enumerator|MTHCA_RES_SRQ
id|MTHCA_RES_SRQ
comma
DECL|enumerator|MTHCA_RES_CQ
id|MTHCA_RES_CQ
comma
DECL|enumerator|MTHCA_RES_EQP
id|MTHCA_RES_EQP
comma
DECL|enumerator|MTHCA_RES_EEEC
id|MTHCA_RES_EEEC
comma
DECL|enumerator|MTHCA_RES_EQ
id|MTHCA_RES_EQ
comma
DECL|enumerator|MTHCA_RES_RDB
id|MTHCA_RES_RDB
comma
DECL|enumerator|MTHCA_RES_MCG
id|MTHCA_RES_MCG
comma
DECL|enumerator|MTHCA_RES_MPT
id|MTHCA_RES_MPT
comma
DECL|enumerator|MTHCA_RES_MTT
id|MTHCA_RES_MTT
comma
DECL|enumerator|MTHCA_RES_UAR
id|MTHCA_RES_UAR
comma
DECL|enumerator|MTHCA_RES_UDAV
id|MTHCA_RES_UDAV
comma
DECL|enumerator|MTHCA_RES_UARC
id|MTHCA_RES_UARC
comma
DECL|enumerator|MTHCA_RES_NUM
id|MTHCA_RES_NUM
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|MTHCA_NUM_EQS
id|MTHCA_NUM_EQS
op_assign
l_int|32
comma
DECL|enumerator|MTHCA_NUM_PDS
id|MTHCA_NUM_PDS
op_assign
l_int|1
op_lshift
l_int|15
)brace
suffix:semicolon
DECL|function|mthca_make_profile
r_int
id|mthca_make_profile
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_profile
op_star
id|request
comma
r_struct
id|mthca_dev_lim
op_star
id|dev_lim
comma
r_struct
id|mthca_init_hca_param
op_star
id|init_hca
)paren
(brace
r_struct
id|mthca_resource
(brace
id|u64
id|size
suffix:semicolon
id|u64
id|start
suffix:semicolon
r_int
id|type
suffix:semicolon
r_int
id|num
suffix:semicolon
r_int
id|log_num
suffix:semicolon
)brace
suffix:semicolon
id|u64
id|mem_base
comma
id|mem_avail
suffix:semicolon
id|u64
id|total_size
op_assign
l_int|0
suffix:semicolon
r_struct
id|mthca_resource
op_star
id|profile
suffix:semicolon
r_struct
id|mthca_resource
id|tmp
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|profile
op_assign
id|kmalloc
c_func
(paren
id|MTHCA_RES_NUM
op_star
r_sizeof
op_star
id|profile
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|profile
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|profile
comma
l_int|0
comma
id|MTHCA_RES_NUM
op_star
r_sizeof
op_star
id|profile
)paren
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_QP
)braket
dot
id|size
op_assign
id|dev_lim-&gt;qpc_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_EEC
)braket
dot
id|size
op_assign
id|dev_lim-&gt;eec_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_SRQ
)braket
dot
id|size
op_assign
id|dev_lim-&gt;srq_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_CQ
)braket
dot
id|size
op_assign
id|dev_lim-&gt;cqc_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_EQP
)braket
dot
id|size
op_assign
id|dev_lim-&gt;eqpc_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_EEEC
)braket
dot
id|size
op_assign
id|dev_lim-&gt;eeec_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_EQ
)braket
dot
id|size
op_assign
id|dev_lim-&gt;eqc_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_RDB
)braket
dot
id|size
op_assign
id|MTHCA_RDB_ENTRY_SIZE
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_MCG
)braket
dot
id|size
op_assign
id|MTHCA_MGM_ENTRY_SIZE
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_MPT
)braket
dot
id|size
op_assign
id|dev_lim-&gt;mpt_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_MTT
)braket
dot
id|size
op_assign
id|dev_lim-&gt;mtt_seg_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_UAR
)braket
dot
id|size
op_assign
id|dev_lim-&gt;uar_scratch_entry_sz
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_UDAV
)braket
dot
id|size
op_assign
id|MTHCA_AV_SIZE
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_UARC
)braket
dot
id|size
op_assign
id|request-&gt;uarc_size
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_QP
)braket
dot
id|num
op_assign
id|request-&gt;num_qp
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_EQP
)braket
dot
id|num
op_assign
id|request-&gt;num_qp
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_RDB
)braket
dot
id|num
op_assign
id|request-&gt;num_qp
op_star
id|request-&gt;rdb_per_qp
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_CQ
)braket
dot
id|num
op_assign
id|request-&gt;num_cq
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_EQ
)braket
dot
id|num
op_assign
id|MTHCA_NUM_EQS
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_MCG
)braket
dot
id|num
op_assign
id|request-&gt;num_mcg
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_MPT
)braket
dot
id|num
op_assign
id|request-&gt;num_mpt
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_MTT
)braket
dot
id|num
op_assign
id|request-&gt;num_mtt
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_UAR
)braket
dot
id|num
op_assign
id|request-&gt;num_uar
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_UARC
)braket
dot
id|num
op_assign
id|request-&gt;num_uar
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_UDAV
)braket
dot
id|num
op_assign
id|request-&gt;num_udav
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MTHCA_RES_NUM
suffix:semicolon
op_increment
id|i
)paren
(brace
id|profile
(braket
id|i
)braket
dot
id|type
op_assign
id|i
suffix:semicolon
id|profile
(braket
id|i
)braket
dot
id|log_num
op_assign
id|max
c_func
(paren
id|ffs
c_func
(paren
id|profile
(braket
id|i
)braket
dot
id|num
)paren
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|profile
(braket
id|i
)braket
dot
id|size
op_mul_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;hca_type
op_eq
id|ARBEL_NATIVE
)paren
(brace
id|mem_base
op_assign
l_int|0
suffix:semicolon
id|mem_avail
op_assign
id|dev_lim-&gt;hca.arbel.max_icm_sz
suffix:semicolon
)brace
r_else
(brace
id|mem_base
op_assign
id|dev-&gt;ddr_start
suffix:semicolon
id|mem_avail
op_assign
id|dev-&gt;fw.tavor.fw_start
op_minus
id|dev-&gt;ddr_start
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Sort the resources in decreasing order of size.  Since they&n;&t; * all have sizes that are powers of 2, we&squot;ll be able to keep&n;&t; * resources aligned to their size and pack them without gaps&n;&t; * using the sorted order.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|MTHCA_RES_NUM
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
op_increment
id|j
)paren
(brace
r_if
c_cond
(paren
id|profile
(braket
id|j
)braket
dot
id|size
OG
id|profile
(braket
id|j
op_minus
l_int|1
)braket
dot
id|size
)paren
(brace
id|tmp
op_assign
id|profile
(braket
id|j
)braket
suffix:semicolon
id|profile
(braket
id|j
)braket
op_assign
id|profile
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|profile
(braket
id|j
op_minus
l_int|1
)braket
op_assign
id|tmp
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MTHCA_RES_NUM
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|profile
(braket
id|i
)braket
dot
id|size
)paren
(brace
id|profile
(braket
id|i
)braket
dot
id|start
op_assign
id|mem_base
op_plus
id|total_size
suffix:semicolon
id|total_size
op_add_assign
id|profile
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|total_size
OG
id|mem_avail
)paren
(brace
id|mthca_err
c_func
(paren
id|dev
comma
l_string|&quot;Profile requires 0x%llx bytes; &quot;
l_string|&quot;won&squot;t in 0x%llx bytes of context memory.&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|total_size
comma
(paren
r_int
r_int
r_int
)paren
id|mem_avail
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|profile
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|profile
(braket
id|i
)braket
dot
id|size
)paren
id|mthca_dbg
c_func
(paren
id|dev
comma
l_string|&quot;profile[%2d]--%2d/%2d @ 0x%16llx &quot;
l_string|&quot;(size 0x%8llx)&bslash;n&quot;
comma
id|i
comma
id|profile
(braket
id|i
)braket
dot
id|type
comma
id|profile
(braket
id|i
)braket
dot
id|log_num
comma
(paren
r_int
r_int
r_int
)paren
id|profile
(braket
id|i
)braket
dot
id|start
comma
(paren
r_int
r_int
r_int
)paren
id|profile
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;hca_type
op_eq
id|ARBEL_NATIVE
)paren
id|mthca_dbg
c_func
(paren
id|dev
comma
l_string|&quot;HCA context memory: reserving %d KB&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|total_size
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
r_else
id|mthca_dbg
c_func
(paren
id|dev
comma
l_string|&quot;HCA memory: allocated %d KB/%d KB (%d KB free)&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|total_size
op_rshift
l_int|10
)paren
comma
(paren
r_int
)paren
(paren
id|mem_avail
op_rshift
l_int|10
)paren
comma
(paren
r_int
)paren
(paren
(paren
id|mem_avail
op_minus
id|total_size
)paren
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MTHCA_RES_NUM
suffix:semicolon
op_increment
id|i
)paren
(brace
r_switch
c_cond
(paren
id|profile
(braket
id|i
)braket
dot
id|type
)paren
(brace
r_case
id|MTHCA_RES_QP
suffix:colon
id|dev-&gt;limits.num_qps
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
id|init_hca-&gt;qpc_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;log_num_qps
op_assign
id|profile
(braket
id|i
)braket
dot
id|log_num
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_EEC
suffix:colon
id|dev-&gt;limits.num_eecs
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
id|init_hca-&gt;eec_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;log_num_eecs
op_assign
id|profile
(braket
id|i
)braket
dot
id|log_num
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_SRQ
suffix:colon
id|dev-&gt;limits.num_srqs
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
id|init_hca-&gt;srqc_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;log_num_srqs
op_assign
id|profile
(braket
id|i
)braket
dot
id|log_num
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_CQ
suffix:colon
id|dev-&gt;limits.num_cqs
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
id|init_hca-&gt;cqc_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;log_num_cqs
op_assign
id|profile
(braket
id|i
)braket
dot
id|log_num
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_EQP
suffix:colon
id|init_hca-&gt;eqpc_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_EEEC
suffix:colon
id|init_hca-&gt;eeec_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_EQ
suffix:colon
id|dev-&gt;limits.num_eqs
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
id|init_hca-&gt;eqc_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;log_num_eqs
op_assign
id|profile
(braket
id|i
)braket
dot
id|log_num
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_RDB
suffix:colon
r_for
c_loop
(paren
id|dev-&gt;qp_table.rdb_shift
op_assign
l_int|0
suffix:semicolon
id|profile
(braket
id|MTHCA_RES_QP
)braket
dot
id|num
op_lshift
id|dev-&gt;qp_table.rdb_shift
OL
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
op_increment
id|dev-&gt;qp_table.rdb_shift
)paren
suffix:semicolon
multiline_comment|/* nothing */
id|dev-&gt;qp_table.rdb_base
op_assign
(paren
id|u32
)paren
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;rdb_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_MCG
suffix:colon
id|dev-&gt;limits.num_mgms
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
op_rshift
l_int|1
suffix:semicolon
id|dev-&gt;limits.num_amgms
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
op_rshift
l_int|1
suffix:semicolon
id|init_hca-&gt;mc_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;log_mc_entry_sz
op_assign
id|ffs
c_func
(paren
id|MTHCA_MGM_ENTRY_SIZE
)paren
op_minus
l_int|1
suffix:semicolon
id|init_hca-&gt;log_mc_table_sz
op_assign
id|profile
(braket
id|i
)braket
dot
id|log_num
suffix:semicolon
id|init_hca-&gt;mc_hash_sz
op_assign
l_int|1
op_lshift
(paren
id|profile
(braket
id|i
)braket
dot
id|log_num
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_MPT
suffix:colon
id|dev-&gt;limits.num_mpts
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
id|init_hca-&gt;mpt_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;log_mpt_sz
op_assign
id|profile
(braket
id|i
)braket
dot
id|log_num
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_MTT
suffix:colon
id|dev-&gt;limits.num_mtt_segs
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
id|dev-&gt;limits.mtt_seg_size
op_assign
id|dev_lim-&gt;mtt_seg_sz
suffix:semicolon
id|dev-&gt;mr_table.mtt_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;mtt_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_hca-&gt;mtt_seg_sz
op_assign
id|ffs
c_func
(paren
id|dev_lim-&gt;mtt_seg_sz
)paren
op_minus
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_UAR
suffix:colon
id|init_hca-&gt;uar_scratch_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTHCA_RES_UDAV
suffix:colon
id|dev-&gt;av_table.ddr_av_base
op_assign
id|profile
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;av_table.num_ddr_avs
op_assign
id|profile
(braket
id|i
)braket
dot
id|num
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * PDs don&squot;t take any HCA memory, but we assign them as part&n;&t; * of the HCA profile anyway.&n;&t; */
id|dev-&gt;limits.num_pds
op_assign
id|MTHCA_NUM_PDS
suffix:semicolon
id|kfree
c_func
(paren
id|profile
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
