multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_provider.h 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#ifndef MTHCA_PROVIDER_H
DECL|macro|MTHCA_PROVIDER_H
mdefine_line|#define MTHCA_PROVIDER_H
macro_line|#include &lt;ib_verbs.h&gt;
macro_line|#include &lt;ib_pack.h&gt;
DECL|macro|MTHCA_MPT_FLAG_ATOMIC
mdefine_line|#define MTHCA_MPT_FLAG_ATOMIC        (1 &lt;&lt; 14)
DECL|macro|MTHCA_MPT_FLAG_REMOTE_WRITE
mdefine_line|#define MTHCA_MPT_FLAG_REMOTE_WRITE  (1 &lt;&lt; 13)
DECL|macro|MTHCA_MPT_FLAG_REMOTE_READ
mdefine_line|#define MTHCA_MPT_FLAG_REMOTE_READ   (1 &lt;&lt; 12)
DECL|macro|MTHCA_MPT_FLAG_LOCAL_WRITE
mdefine_line|#define MTHCA_MPT_FLAG_LOCAL_WRITE   (1 &lt;&lt; 11)
DECL|macro|MTHCA_MPT_FLAG_LOCAL_READ
mdefine_line|#define MTHCA_MPT_FLAG_LOCAL_READ    (1 &lt;&lt; 10)
DECL|struct|mthca_buf_list
r_struct
id|mthca_buf_list
(brace
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
id|DECLARE_PCI_UNMAP_ADDR
c_func
(paren
id|mapping
)paren
)brace
suffix:semicolon
DECL|struct|mthca_uar
r_struct
id|mthca_uar
(brace
DECL|member|pfn
r_int
r_int
id|pfn
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_mr
r_struct
id|mthca_mr
(brace
DECL|member|ibmr
r_struct
id|ib_mr
id|ibmr
suffix:semicolon
DECL|member|order
r_int
id|order
suffix:semicolon
DECL|member|first_seg
id|u32
id|first_seg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_pd
r_struct
id|mthca_pd
(brace
DECL|member|ibpd
r_struct
id|ib_pd
id|ibpd
suffix:semicolon
DECL|member|pd_num
id|u32
id|pd_num
suffix:semicolon
DECL|member|sqp_count
id|atomic_t
id|sqp_count
suffix:semicolon
DECL|member|ntmr
r_struct
id|mthca_mr
id|ntmr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_eq
r_struct
id|mthca_eq
(brace
DECL|member|dev
r_struct
id|mthca_dev
op_star
id|dev
suffix:semicolon
DECL|member|eqn
r_int
id|eqn
suffix:semicolon
DECL|member|eqn_mask
id|u32
id|eqn_mask
suffix:semicolon
DECL|member|cons_index
id|u32
id|cons_index
suffix:semicolon
DECL|member|msi_x_vector
id|u16
id|msi_x_vector
suffix:semicolon
DECL|member|msi_x_entry
id|u16
id|msi_x_entry
suffix:semicolon
DECL|member|have_irq
r_int
id|have_irq
suffix:semicolon
DECL|member|nent
r_int
id|nent
suffix:semicolon
DECL|member|page_list
r_struct
id|mthca_buf_list
op_star
id|page_list
suffix:semicolon
DECL|member|mr
r_struct
id|mthca_mr
id|mr
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|mthca_av
suffix:semicolon
DECL|enum|mthca_ah_type
r_enum
id|mthca_ah_type
(brace
DECL|enumerator|MTHCA_AH_ON_HCA
id|MTHCA_AH_ON_HCA
comma
DECL|enumerator|MTHCA_AH_PCI_POOL
id|MTHCA_AH_PCI_POOL
comma
DECL|enumerator|MTHCA_AH_KMALLOC
id|MTHCA_AH_KMALLOC
)brace
suffix:semicolon
DECL|struct|mthca_ah
r_struct
id|mthca_ah
(brace
DECL|member|ibah
r_struct
id|ib_ah
id|ibah
suffix:semicolon
DECL|member|type
r_enum
id|mthca_ah_type
id|type
suffix:semicolon
DECL|member|key
id|u32
id|key
suffix:semicolon
DECL|member|av
r_struct
id|mthca_av
op_star
id|av
suffix:semicolon
DECL|member|avdma
id|dma_addr_t
id|avdma
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Quick description of our CQ/QP locking scheme:&n; *&n; * We have one global lock that protects dev-&gt;cq/qp_table.  Each&n; * struct mthca_cq/qp also has its own lock.  An individual qp lock&n; * may be taken inside of an individual cq lock.  Both cqs attached to&n; * a qp may be locked, with the send cq locked first.  No other&n; * nesting should be done.&n; *&n; * Each struct mthca_cq/qp also has an atomic_t ref count.  The&n; * pointer from the cq/qp_table to the struct counts as one reference.&n; * This reference also is good for access through the consumer API, so&n; * modifying the CQ/QP etc doesn&squot;t need to take another reference.&n; * Access because of a completion being polled does need a reference.&n; *&n; * Finally, each struct mthca_cq/qp has a wait_queue_head_t for the&n; * destroy function to sleep on.&n; *&n; * This means that access from the consumer API requires nothing but&n; * taking the struct&squot;s lock.&n; *&n; * Access because of a completion event should go as follows:&n; * - lock cq/qp_table and look up struct&n; * - increment ref count in struct&n; * - drop cq/qp_table lock&n; * - lock struct, do your thing, and unlock struct&n; * - decrement ref count; if zero, wake up waiters&n; *&n; * To destroy a CQ/QP, we can do the following:&n; * - lock cq/qp_table, remove pointer, unlock cq/qp_table lock&n; * - decrement ref count&n; * - wait_event until ref count is zero&n; *&n; * It is the consumer&squot;s responsibilty to make sure that no QP&n; * operations (WQE posting or state modification) are pending when the&n; * QP is destroyed.  Also, the consumer must make sure that calls to&n; * qp_modify are serialized.&n; *&n; * Possible optimizations (wait for profile data to see if/where we&n; * have locks bouncing between CPUs):&n; * - split cq/qp table lock into n separate (cache-aligned) locks,&n; *   indexed (say) by the page in the table&n; * - split QP struct lock into three (one for common info, one for the&n; *   send queue and one for the receive queue)&n; */
DECL|struct|mthca_cq
r_struct
id|mthca_cq
(brace
DECL|member|ibcq
r_struct
id|ib_cq
id|ibcq
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
DECL|member|cqn
r_int
id|cqn
suffix:semicolon
DECL|member|cons_index
id|u32
id|cons_index
suffix:semicolon
DECL|member|is_direct
r_int
id|is_direct
suffix:semicolon
multiline_comment|/* Next fields are Arbel only */
DECL|member|set_ci_db_index
r_int
id|set_ci_db_index
suffix:semicolon
DECL|member|set_ci_db
id|u32
op_star
id|set_ci_db
suffix:semicolon
DECL|member|arm_db_index
r_int
id|arm_db_index
suffix:semicolon
DECL|member|arm_db
id|u32
op_star
id|arm_db
suffix:semicolon
DECL|member|arm_sn
r_int
id|arm_sn
suffix:semicolon
r_union
(brace
DECL|member|direct
r_struct
id|mthca_buf_list
id|direct
suffix:semicolon
DECL|member|page_list
r_struct
id|mthca_buf_list
op_star
id|page_list
suffix:semicolon
DECL|member|queue
)brace
id|queue
suffix:semicolon
DECL|member|mr
r_struct
id|mthca_mr
id|mr
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_wq
r_struct
id|mthca_wq
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|max
r_int
id|max
suffix:semicolon
DECL|member|next_ind
r_int
id|next_ind
suffix:semicolon
DECL|member|last_comp
r_int
id|last_comp
suffix:semicolon
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|last
r_void
op_star
id|last
suffix:semicolon
DECL|member|max_gs
r_int
id|max_gs
suffix:semicolon
DECL|member|wqe_shift
r_int
id|wqe_shift
suffix:semicolon
DECL|member|db_index
r_int
id|db_index
suffix:semicolon
multiline_comment|/* Arbel only */
DECL|member|db
id|u32
op_star
id|db
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_qp
r_struct
id|mthca_qp
(brace
DECL|member|ibqp
r_struct
id|ib_qp
id|ibqp
suffix:semicolon
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
DECL|member|qpn
id|u32
id|qpn
suffix:semicolon
DECL|member|is_direct
r_int
id|is_direct
suffix:semicolon
DECL|member|transport
id|u8
id|transport
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|atomic_rd_en
id|u8
id|atomic_rd_en
suffix:semicolon
DECL|member|resp_depth
id|u8
id|resp_depth
suffix:semicolon
DECL|member|mr
r_struct
id|mthca_mr
id|mr
suffix:semicolon
DECL|member|rq
r_struct
id|mthca_wq
id|rq
suffix:semicolon
DECL|member|sq
r_struct
id|mthca_wq
id|sq
suffix:semicolon
DECL|member|sq_policy
r_enum
id|ib_sig_type
id|sq_policy
suffix:semicolon
DECL|member|send_wqe_offset
r_int
id|send_wqe_offset
suffix:semicolon
DECL|member|wrid
id|u64
op_star
id|wrid
suffix:semicolon
r_union
(brace
DECL|member|direct
r_struct
id|mthca_buf_list
id|direct
suffix:semicolon
DECL|member|page_list
r_struct
id|mthca_buf_list
op_star
id|page_list
suffix:semicolon
DECL|member|queue
)brace
id|queue
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_sqp
r_struct
id|mthca_sqp
(brace
DECL|member|qp
r_struct
id|mthca_qp
id|qp
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|pkey_index
r_int
id|pkey_index
suffix:semicolon
DECL|member|qkey
id|u32
id|qkey
suffix:semicolon
DECL|member|send_psn
id|u32
id|send_psn
suffix:semicolon
DECL|member|ud_header
r_struct
id|ib_ud_header
id|ud_header
suffix:semicolon
DECL|member|header_buf_size
r_int
id|header_buf_size
suffix:semicolon
DECL|member|header_buf
r_void
op_star
id|header_buf
suffix:semicolon
DECL|member|header_dma
id|dma_addr_t
id|header_dma
suffix:semicolon
)brace
suffix:semicolon
DECL|function|to_mmr
r_static
r_inline
r_struct
id|mthca_mr
op_star
id|to_mmr
c_func
(paren
r_struct
id|ib_mr
op_star
id|ibmr
)paren
(brace
r_return
id|container_of
c_func
(paren
id|ibmr
comma
r_struct
id|mthca_mr
comma
id|ibmr
)paren
suffix:semicolon
)brace
DECL|function|to_mpd
r_static
r_inline
r_struct
id|mthca_pd
op_star
id|to_mpd
c_func
(paren
r_struct
id|ib_pd
op_star
id|ibpd
)paren
(brace
r_return
id|container_of
c_func
(paren
id|ibpd
comma
r_struct
id|mthca_pd
comma
id|ibpd
)paren
suffix:semicolon
)brace
DECL|function|to_mah
r_static
r_inline
r_struct
id|mthca_ah
op_star
id|to_mah
c_func
(paren
r_struct
id|ib_ah
op_star
id|ibah
)paren
(brace
r_return
id|container_of
c_func
(paren
id|ibah
comma
r_struct
id|mthca_ah
comma
id|ibah
)paren
suffix:semicolon
)brace
DECL|function|to_mcq
r_static
r_inline
r_struct
id|mthca_cq
op_star
id|to_mcq
c_func
(paren
r_struct
id|ib_cq
op_star
id|ibcq
)paren
(brace
r_return
id|container_of
c_func
(paren
id|ibcq
comma
r_struct
id|mthca_cq
comma
id|ibcq
)paren
suffix:semicolon
)brace
DECL|function|to_mqp
r_static
r_inline
r_struct
id|mthca_qp
op_star
id|to_mqp
c_func
(paren
r_struct
id|ib_qp
op_star
id|ibqp
)paren
(brace
r_return
id|container_of
c_func
(paren
id|ibqp
comma
r_struct
id|mthca_qp
comma
id|ibqp
)paren
suffix:semicolon
)brace
DECL|function|to_msqp
r_static
r_inline
r_struct
id|mthca_sqp
op_star
id|to_msqp
c_func
(paren
r_struct
id|mthca_qp
op_star
id|qp
)paren
(brace
r_return
id|container_of
c_func
(paren
id|qp
comma
r_struct
id|mthca_sqp
comma
id|qp
)paren
suffix:semicolon
)brace
macro_line|#endif /* MTHCA_PROVIDER_H */
eof
