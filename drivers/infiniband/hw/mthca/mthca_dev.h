multiline_comment|/*&n; * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_dev.h 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#ifndef MTHCA_DEV_H
DECL|macro|MTHCA_DEV_H
mdefine_line|#define MTHCA_DEV_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;mthca_provider.h&quot;
macro_line|#include &quot;mthca_doorbell.h&quot;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;ib_mthca&quot;
DECL|macro|PFX
mdefine_line|#define PFX&t;&t;DRV_NAME &quot;: &quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.06-pre&quot;
DECL|macro|DRV_RELDATE
mdefine_line|#define DRV_RELDATE&t;&quot;November 8, 2004&quot;
multiline_comment|/* Types of supported HCA */
r_enum
(brace
DECL|enumerator|TAVOR
id|TAVOR
comma
multiline_comment|/* MT23108                        */
DECL|enumerator|ARBEL_COMPAT
id|ARBEL_COMPAT
comma
multiline_comment|/* MT25208 in Tavor compat mode   */
DECL|enumerator|ARBEL_NATIVE
id|ARBEL_NATIVE
multiline_comment|/* MT25208 with extended features */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|MTHCA_FLAG_DDR_HIDDEN
id|MTHCA_FLAG_DDR_HIDDEN
op_assign
l_int|1
op_lshift
l_int|1
comma
DECL|enumerator|MTHCA_FLAG_SRQ
id|MTHCA_FLAG_SRQ
op_assign
l_int|1
op_lshift
l_int|2
comma
DECL|enumerator|MTHCA_FLAG_MSI
id|MTHCA_FLAG_MSI
op_assign
l_int|1
op_lshift
l_int|3
comma
DECL|enumerator|MTHCA_FLAG_MSI_X
id|MTHCA_FLAG_MSI_X
op_assign
l_int|1
op_lshift
l_int|4
comma
DECL|enumerator|MTHCA_FLAG_NO_LAM
id|MTHCA_FLAG_NO_LAM
op_assign
l_int|1
op_lshift
l_int|5
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|MTHCA_KAR_PAGE
id|MTHCA_KAR_PAGE
op_assign
l_int|1
comma
DECL|enumerator|MTHCA_MAX_PORTS
id|MTHCA_MAX_PORTS
op_assign
l_int|2
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|MTHCA_EQ_CONTEXT_SIZE
id|MTHCA_EQ_CONTEXT_SIZE
op_assign
l_int|0x40
comma
DECL|enumerator|MTHCA_CQ_CONTEXT_SIZE
id|MTHCA_CQ_CONTEXT_SIZE
op_assign
l_int|0x40
comma
DECL|enumerator|MTHCA_QP_CONTEXT_SIZE
id|MTHCA_QP_CONTEXT_SIZE
op_assign
l_int|0x200
comma
DECL|enumerator|MTHCA_RDB_ENTRY_SIZE
id|MTHCA_RDB_ENTRY_SIZE
op_assign
l_int|0x20
comma
DECL|enumerator|MTHCA_AV_SIZE
id|MTHCA_AV_SIZE
op_assign
l_int|0x20
comma
DECL|enumerator|MTHCA_MGM_ENTRY_SIZE
id|MTHCA_MGM_ENTRY_SIZE
op_assign
l_int|0x40
comma
multiline_comment|/* Arbel FW gives us these, but we need them for Tavor */
DECL|enumerator|MTHCA_MPT_ENTRY_SIZE
id|MTHCA_MPT_ENTRY_SIZE
op_assign
l_int|0x40
comma
DECL|enumerator|MTHCA_MTT_SEG_SIZE
id|MTHCA_MTT_SEG_SIZE
op_assign
l_int|0x40
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|MTHCA_EQ_CMD
id|MTHCA_EQ_CMD
comma
DECL|enumerator|MTHCA_EQ_ASYNC
id|MTHCA_EQ_ASYNC
comma
DECL|enumerator|MTHCA_EQ_COMP
id|MTHCA_EQ_COMP
comma
DECL|enumerator|MTHCA_NUM_EQ
id|MTHCA_NUM_EQ
)brace
suffix:semicolon
DECL|struct|mthca_cmd
r_struct
id|mthca_cmd
(brace
DECL|member|use_events
r_int
id|use_events
suffix:semicolon
DECL|member|hcr_sem
r_struct
id|semaphore
id|hcr_sem
suffix:semicolon
DECL|member|poll_sem
r_struct
id|semaphore
id|poll_sem
suffix:semicolon
DECL|member|event_sem
r_struct
id|semaphore
id|event_sem
suffix:semicolon
DECL|member|max_cmds
r_int
id|max_cmds
suffix:semicolon
DECL|member|context_lock
id|spinlock_t
id|context_lock
suffix:semicolon
DECL|member|free_head
r_int
id|free_head
suffix:semicolon
DECL|member|context
r_struct
id|mthca_cmd_context
op_star
id|context
suffix:semicolon
DECL|member|token_mask
id|u16
id|token_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_limits
r_struct
id|mthca_limits
(brace
DECL|member|num_ports
r_int
id|num_ports
suffix:semicolon
DECL|member|vl_cap
r_int
id|vl_cap
suffix:semicolon
DECL|member|mtu_cap
r_int
id|mtu_cap
suffix:semicolon
DECL|member|gid_table_len
r_int
id|gid_table_len
suffix:semicolon
DECL|member|pkey_table_len
r_int
id|pkey_table_len
suffix:semicolon
DECL|member|local_ca_ack_delay
r_int
id|local_ca_ack_delay
suffix:semicolon
DECL|member|max_sg
r_int
id|max_sg
suffix:semicolon
DECL|member|num_qps
r_int
id|num_qps
suffix:semicolon
DECL|member|reserved_qps
r_int
id|reserved_qps
suffix:semicolon
DECL|member|num_srqs
r_int
id|num_srqs
suffix:semicolon
DECL|member|reserved_srqs
r_int
id|reserved_srqs
suffix:semicolon
DECL|member|num_eecs
r_int
id|num_eecs
suffix:semicolon
DECL|member|reserved_eecs
r_int
id|reserved_eecs
suffix:semicolon
DECL|member|num_cqs
r_int
id|num_cqs
suffix:semicolon
DECL|member|reserved_cqs
r_int
id|reserved_cqs
suffix:semicolon
DECL|member|num_eqs
r_int
id|num_eqs
suffix:semicolon
DECL|member|reserved_eqs
r_int
id|reserved_eqs
suffix:semicolon
DECL|member|num_mpts
r_int
id|num_mpts
suffix:semicolon
DECL|member|num_mtt_segs
r_int
id|num_mtt_segs
suffix:semicolon
DECL|member|mtt_seg_size
r_int
id|mtt_seg_size
suffix:semicolon
DECL|member|reserved_mtts
r_int
id|reserved_mtts
suffix:semicolon
DECL|member|reserved_mrws
r_int
id|reserved_mrws
suffix:semicolon
DECL|member|reserved_uars
r_int
id|reserved_uars
suffix:semicolon
DECL|member|num_mgms
r_int
id|num_mgms
suffix:semicolon
DECL|member|num_amgms
r_int
id|num_amgms
suffix:semicolon
DECL|member|reserved_mcgs
r_int
id|reserved_mcgs
suffix:semicolon
DECL|member|num_pds
r_int
id|num_pds
suffix:semicolon
DECL|member|reserved_pds
r_int
id|reserved_pds
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_alloc
r_struct
id|mthca_alloc
(brace
DECL|member|last
id|u32
id|last
suffix:semicolon
DECL|member|top
id|u32
id|top
suffix:semicolon
DECL|member|max
id|u32
id|max
suffix:semicolon
DECL|member|mask
id|u32
id|mask
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|table
r_int
r_int
op_star
id|table
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_array
r_struct
id|mthca_array
(brace
r_struct
(brace
DECL|member|page
r_void
op_star
op_star
id|page
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|page_list
)brace
op_star
id|page_list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_pd_table
r_struct
id|mthca_pd_table
(brace
DECL|member|alloc
r_struct
id|mthca_alloc
id|alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_mr_table
r_struct
id|mthca_mr_table
(brace
DECL|member|mpt_alloc
r_struct
id|mthca_alloc
id|mpt_alloc
suffix:semicolon
DECL|member|max_mtt_order
r_int
id|max_mtt_order
suffix:semicolon
DECL|member|mtt_buddy
r_int
r_int
op_star
op_star
id|mtt_buddy
suffix:semicolon
DECL|member|mtt_base
id|u64
id|mtt_base
suffix:semicolon
DECL|member|mtt_table
r_struct
id|mthca_icm_table
op_star
id|mtt_table
suffix:semicolon
DECL|member|mpt_table
r_struct
id|mthca_icm_table
op_star
id|mpt_table
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_eq_table
r_struct
id|mthca_eq_table
(brace
DECL|member|alloc
r_struct
id|mthca_alloc
id|alloc
suffix:semicolon
DECL|member|clr_int
r_void
id|__iomem
op_star
id|clr_int
suffix:semicolon
DECL|member|clr_mask
id|u32
id|clr_mask
suffix:semicolon
DECL|member|eq
r_struct
id|mthca_eq
id|eq
(braket
id|MTHCA_NUM_EQ
)braket
suffix:semicolon
DECL|member|icm_virt
id|u64
id|icm_virt
suffix:semicolon
DECL|member|icm_page
r_struct
id|page
op_star
id|icm_page
suffix:semicolon
DECL|member|icm_dma
id|dma_addr_t
id|icm_dma
suffix:semicolon
DECL|member|have_irq
r_int
id|have_irq
suffix:semicolon
DECL|member|inta_pin
id|u8
id|inta_pin
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_cq_table
r_struct
id|mthca_cq_table
(brace
DECL|member|alloc
r_struct
id|mthca_alloc
id|alloc
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|cq
r_struct
id|mthca_array
id|cq
suffix:semicolon
DECL|member|table
r_struct
id|mthca_icm_table
op_star
id|table
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_qp_table
r_struct
id|mthca_qp_table
(brace
DECL|member|alloc
r_struct
id|mthca_alloc
id|alloc
suffix:semicolon
DECL|member|rdb_base
id|u32
id|rdb_base
suffix:semicolon
DECL|member|rdb_shift
r_int
id|rdb_shift
suffix:semicolon
DECL|member|sqp_start
r_int
id|sqp_start
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|qp
r_struct
id|mthca_array
id|qp
suffix:semicolon
DECL|member|qp_table
r_struct
id|mthca_icm_table
op_star
id|qp_table
suffix:semicolon
DECL|member|eqp_table
r_struct
id|mthca_icm_table
op_star
id|eqp_table
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_av_table
r_struct
id|mthca_av_table
(brace
DECL|member|pool
r_struct
id|pci_pool
op_star
id|pool
suffix:semicolon
DECL|member|num_ddr_avs
r_int
id|num_ddr_avs
suffix:semicolon
DECL|member|ddr_av_base
id|u64
id|ddr_av_base
suffix:semicolon
DECL|member|av_map
r_void
id|__iomem
op_star
id|av_map
suffix:semicolon
DECL|member|alloc
r_struct
id|mthca_alloc
id|alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_mcg_table
r_struct
id|mthca_mcg_table
(brace
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|alloc
r_struct
id|mthca_alloc
id|alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mthca_dev
r_struct
id|mthca_dev
(brace
DECL|member|ib_dev
r_struct
id|ib_device
id|ib_dev
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|hca_type
r_int
id|hca_type
suffix:semicolon
DECL|member|mthca_flags
r_int
r_int
id|mthca_flags
suffix:semicolon
DECL|member|rev_id
id|u32
id|rev_id
suffix:semicolon
multiline_comment|/* firmware info */
DECL|member|fw_ver
id|u64
id|fw_ver
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|fw_start
id|u64
id|fw_start
suffix:semicolon
DECL|member|fw_end
id|u64
id|fw_end
suffix:semicolon
DECL|member|tavor
)brace
id|tavor
suffix:semicolon
r_struct
(brace
DECL|member|clr_int_base
id|u64
id|clr_int_base
suffix:semicolon
DECL|member|eq_arm_base
id|u64
id|eq_arm_base
suffix:semicolon
DECL|member|eq_set_ci_base
id|u64
id|eq_set_ci_base
suffix:semicolon
DECL|member|fw_icm
r_struct
id|mthca_icm
op_star
id|fw_icm
suffix:semicolon
DECL|member|aux_icm
r_struct
id|mthca_icm
op_star
id|aux_icm
suffix:semicolon
DECL|member|fw_pages
id|u16
id|fw_pages
suffix:semicolon
DECL|member|arbel
)brace
id|arbel
suffix:semicolon
DECL|member|fw
)brace
id|fw
suffix:semicolon
DECL|member|ddr_start
id|u64
id|ddr_start
suffix:semicolon
DECL|member|ddr_end
id|u64
id|ddr_end
suffix:semicolon
id|MTHCA_DECLARE_DOORBELL_LOCK
c_func
(paren
id|doorbell_lock
)paren
r_struct
id|semaphore
id|cap_mask_mutex
suffix:semicolon
DECL|member|hcr
r_void
id|__iomem
op_star
id|hcr
suffix:semicolon
DECL|member|ecr_base
r_void
id|__iomem
op_star
id|ecr_base
suffix:semicolon
DECL|member|clr_base
r_void
id|__iomem
op_star
id|clr_base
suffix:semicolon
DECL|member|kar
r_void
id|__iomem
op_star
id|kar
suffix:semicolon
DECL|member|cmd
r_struct
id|mthca_cmd
id|cmd
suffix:semicolon
DECL|member|limits
r_struct
id|mthca_limits
id|limits
suffix:semicolon
DECL|member|pd_table
r_struct
id|mthca_pd_table
id|pd_table
suffix:semicolon
DECL|member|mr_table
r_struct
id|mthca_mr_table
id|mr_table
suffix:semicolon
DECL|member|eq_table
r_struct
id|mthca_eq_table
id|eq_table
suffix:semicolon
DECL|member|cq_table
r_struct
id|mthca_cq_table
id|cq_table
suffix:semicolon
DECL|member|qp_table
r_struct
id|mthca_qp_table
id|qp_table
suffix:semicolon
DECL|member|av_table
r_struct
id|mthca_av_table
id|av_table
suffix:semicolon
DECL|member|mcg_table
r_struct
id|mthca_mcg_table
id|mcg_table
suffix:semicolon
DECL|member|driver_pd
r_struct
id|mthca_pd
id|driver_pd
suffix:semicolon
DECL|member|driver_mr
r_struct
id|mthca_mr
id|driver_mr
suffix:semicolon
DECL|member|send_agent
r_struct
id|ib_mad_agent
op_star
id|send_agent
(braket
id|MTHCA_MAX_PORTS
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sm_ah
r_struct
id|ib_ah
op_star
id|sm_ah
(braket
id|MTHCA_MAX_PORTS
)braket
suffix:semicolon
DECL|member|sm_lock
id|spinlock_t
id|sm_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|mthca_dbg
mdefine_line|#define mthca_dbg(mdev, format, arg...) &bslash;&n;&t;dev_dbg(&amp;mdev-&gt;pdev-&gt;dev, format, ## arg)
DECL|macro|mthca_err
mdefine_line|#define mthca_err(mdev, format, arg...) &bslash;&n;&t;dev_err(&amp;mdev-&gt;pdev-&gt;dev, format, ## arg)
DECL|macro|mthca_info
mdefine_line|#define mthca_info(mdev, format, arg...) &bslash;&n;&t;dev_info(&amp;mdev-&gt;pdev-&gt;dev, format, ## arg)
DECL|macro|mthca_warn
mdefine_line|#define mthca_warn(mdev, format, arg...) &bslash;&n;&t;dev_warn(&amp;mdev-&gt;pdev-&gt;dev, format, ## arg)
r_extern
r_void
id|__buggy_use_of_MTHCA_GET
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__buggy_use_of_MTHCA_PUT
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|MTHCA_GET
mdefine_line|#define MTHCA_GET(dest, source, offset)                               &bslash;&n;&t;do {                                                          &bslash;&n;&t;&t;void *__p = (char *) (source) + (offset);             &bslash;&n;&t;&t;switch (sizeof (dest)) {                              &bslash;&n;&t;&t;&t;case 1: (dest) = *(u8 *) __p;       break;    &bslash;&n;&t;&t;&t;case 2: (dest) = be16_to_cpup(__p); break;    &bslash;&n;&t;&t;&t;case 4: (dest) = be32_to_cpup(__p); break;    &bslash;&n;&t;&t;&t;case 8: (dest) = be64_to_cpup(__p); break;    &bslash;&n;&t;&t;&t;default: __buggy_use_of_MTHCA_GET();          &bslash;&n;&t;&t;}                                                     &bslash;&n;&t;} while (0)
DECL|macro|MTHCA_PUT
mdefine_line|#define MTHCA_PUT(dest, source, offset)                               &bslash;&n;&t;do {                                                          &bslash;&n;&t;&t;__typeof__(source) *__p =                             &bslash;&n;&t;&t;&t;(__typeof__(source) *) ((char *) (dest) + (offset)); &bslash;&n;&t;&t;switch (sizeof(source)) {                             &bslash;&n;&t;&t;&t;case 1: *__p = (source);            break;    &bslash;&n;&t;&t;&t;case 2: *__p = cpu_to_be16(source); break;    &bslash;&n;&t;&t;&t;case 4: *__p = cpu_to_be32(source); break;    &bslash;&n;&t;&t;&t;case 8: *__p = cpu_to_be64(source); break;    &bslash;&n;&t;&t;&t;default: __buggy_use_of_MTHCA_PUT();          &bslash;&n;&t;&t;}                                                     &bslash;&n;&t;} while (0)
r_int
id|mthca_reset
c_func
(paren
r_struct
id|mthca_dev
op_star
id|mdev
)paren
suffix:semicolon
id|u32
id|mthca_alloc
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
)paren
suffix:semicolon
r_void
id|mthca_free
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
comma
id|u32
id|obj
)paren
suffix:semicolon
r_int
id|mthca_alloc_init
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
comma
id|u32
id|num
comma
id|u32
id|mask
comma
id|u32
id|reserved
)paren
suffix:semicolon
r_void
id|mthca_alloc_cleanup
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
)paren
suffix:semicolon
r_void
op_star
id|mthca_array_get
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|index
)paren
suffix:semicolon
r_int
id|mthca_array_set
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|index
comma
r_void
op_star
id|value
)paren
suffix:semicolon
r_void
id|mthca_array_clear
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|index
)paren
suffix:semicolon
r_int
id|mthca_array_init
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|nent
)paren
suffix:semicolon
r_void
id|mthca_array_cleanup
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|nent
)paren
suffix:semicolon
r_int
id|mthca_init_pd_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_init_mr_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_init_eq_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_init_cq_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_init_qp_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_init_av_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_init_mcg_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_cleanup_pd_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_cleanup_mr_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_cleanup_eq_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_cleanup_cq_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_cleanup_qp_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_cleanup_av_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_cleanup_mcg_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_register_device
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_unregister_device
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_pd_alloc
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_pd
op_star
id|pd
)paren
suffix:semicolon
r_void
id|mthca_pd_free
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_pd
op_star
id|pd
)paren
suffix:semicolon
r_int
id|mthca_mr_alloc_notrans
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|pd
comma
id|u32
id|access
comma
r_struct
id|mthca_mr
op_star
id|mr
)paren
suffix:semicolon
r_int
id|mthca_mr_alloc_phys
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|pd
comma
id|u64
op_star
id|buffer_list
comma
r_int
id|buffer_size_shift
comma
r_int
id|list_len
comma
id|u64
id|iova
comma
id|u64
id|total_size
comma
id|u32
id|access
comma
r_struct
id|mthca_mr
op_star
id|mr
)paren
suffix:semicolon
r_void
id|mthca_free_mr
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_mr
op_star
id|mr
)paren
suffix:semicolon
r_int
id|mthca_map_eq_icm
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u64
id|icm_virt
)paren
suffix:semicolon
r_void
id|mthca_unmap_eq_icm
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|mthca_poll_cq
c_func
(paren
r_struct
id|ib_cq
op_star
id|ibcq
comma
r_int
id|num_entries
comma
r_struct
id|ib_wc
op_star
id|entry
)paren
suffix:semicolon
r_void
id|mthca_arm_cq
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_cq
op_star
id|cq
comma
r_int
id|solicited
)paren
suffix:semicolon
r_int
id|mthca_init_cq
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_int
id|nent
comma
r_struct
id|mthca_cq
op_star
id|cq
)paren
suffix:semicolon
r_void
id|mthca_free_cq
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_cq
op_star
id|cq
)paren
suffix:semicolon
r_void
id|mthca_cq_event
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|cqn
)paren
suffix:semicolon
r_void
id|mthca_cq_clean
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|cqn
comma
id|u32
id|qpn
)paren
suffix:semicolon
r_void
id|mthca_qp_event
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|qpn
comma
r_enum
id|ib_event_type
id|event_type
)paren
suffix:semicolon
r_int
id|mthca_modify_qp
c_func
(paren
r_struct
id|ib_qp
op_star
id|ibqp
comma
r_struct
id|ib_qp_attr
op_star
id|attr
comma
r_int
id|attr_mask
)paren
suffix:semicolon
r_int
id|mthca_post_send
c_func
(paren
r_struct
id|ib_qp
op_star
id|ibqp
comma
r_struct
id|ib_send_wr
op_star
id|wr
comma
r_struct
id|ib_send_wr
op_star
op_star
id|bad_wr
)paren
suffix:semicolon
r_int
id|mthca_post_receive
c_func
(paren
r_struct
id|ib_qp
op_star
id|ibqp
comma
r_struct
id|ib_recv_wr
op_star
id|wr
comma
r_struct
id|ib_recv_wr
op_star
op_star
id|bad_wr
)paren
suffix:semicolon
r_int
id|mthca_free_err_wqe
c_func
(paren
r_struct
id|mthca_qp
op_star
id|qp
comma
r_int
id|is_send
comma
r_int
id|index
comma
r_int
op_star
id|dbd
comma
id|u32
op_star
id|new_wqe
)paren
suffix:semicolon
r_int
id|mthca_alloc_qp
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_pd
op_star
id|pd
comma
r_struct
id|mthca_cq
op_star
id|send_cq
comma
r_struct
id|mthca_cq
op_star
id|recv_cq
comma
r_enum
id|ib_qp_type
id|type
comma
r_enum
id|ib_sig_type
id|send_policy
comma
r_enum
id|ib_sig_type
id|recv_policy
comma
r_struct
id|mthca_qp
op_star
id|qp
)paren
suffix:semicolon
r_int
id|mthca_alloc_sqp
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_pd
op_star
id|pd
comma
r_struct
id|mthca_cq
op_star
id|send_cq
comma
r_struct
id|mthca_cq
op_star
id|recv_cq
comma
r_enum
id|ib_sig_type
id|send_policy
comma
r_enum
id|ib_sig_type
id|recv_policy
comma
r_int
id|qpn
comma
r_int
id|port
comma
r_struct
id|mthca_sqp
op_star
id|sqp
)paren
suffix:semicolon
r_void
id|mthca_free_qp
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_qp
op_star
id|qp
)paren
suffix:semicolon
r_int
id|mthca_create_ah
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_pd
op_star
id|pd
comma
r_struct
id|ib_ah_attr
op_star
id|ah_attr
comma
r_struct
id|mthca_ah
op_star
id|ah
)paren
suffix:semicolon
r_int
id|mthca_destroy_ah
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_ah
op_star
id|ah
)paren
suffix:semicolon
r_int
id|mthca_read_ah
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_ah
op_star
id|ah
comma
r_struct
id|ib_ud_header
op_star
id|header
)paren
suffix:semicolon
r_int
id|mthca_multicast_attach
c_func
(paren
r_struct
id|ib_qp
op_star
id|ibqp
comma
r_union
id|ib_gid
op_star
id|gid
comma
id|u16
id|lid
)paren
suffix:semicolon
r_int
id|mthca_multicast_detach
c_func
(paren
r_struct
id|ib_qp
op_star
id|ibqp
comma
r_union
id|ib_gid
op_star
id|gid
comma
id|u16
id|lid
)paren
suffix:semicolon
r_int
id|mthca_process_mad
c_func
(paren
r_struct
id|ib_device
op_star
id|ibdev
comma
r_int
id|mad_flags
comma
id|u8
id|port_num
comma
r_struct
id|ib_wc
op_star
id|in_wc
comma
r_struct
id|ib_grh
op_star
id|in_grh
comma
r_struct
id|ib_mad
op_star
id|in_mad
comma
r_struct
id|ib_mad
op_star
id|out_mad
)paren
suffix:semicolon
r_int
id|mthca_create_agents
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|mthca_free_agents
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|function|to_mdev
r_static
r_inline
r_struct
id|mthca_dev
op_star
id|to_mdev
c_func
(paren
r_struct
id|ib_device
op_star
id|ibdev
)paren
(brace
r_return
id|container_of
c_func
(paren
id|ibdev
comma
r_struct
id|mthca_dev
comma
id|ib_dev
)paren
suffix:semicolon
)brace
macro_line|#endif /* MTHCA_DEV_H */
eof
