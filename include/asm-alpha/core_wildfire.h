macro_line|#ifndef __ALPHA_WILDFIRE__H__
DECL|macro|__ALPHA_WILDFIRE__H__
mdefine_line|#define __ALPHA_WILDFIRE__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
DECL|macro|WILDFIRE_MAX_QBB
mdefine_line|#define WILDFIRE_MAX_QBB&t;8&t;/* more than 8 requires other mods */
DECL|macro|WILDFIRE_PCA_PER_QBB
mdefine_line|#define WILDFIRE_PCA_PER_QBB&t;4
DECL|macro|WILDFIRE_IRQ_PER_PCA
mdefine_line|#define WILDFIRE_IRQ_PER_PCA&t;64
DECL|macro|WILDFIRE_NR_IRQS
mdefine_line|#define WILDFIRE_NR_IRQS &bslash;&n;  (WILDFIRE_MAX_QBB * WILDFIRE_PCA_PER_QBB * WILDFIRE_IRQ_PER_PCA)
r_extern
r_int
r_char
id|wildfire_hard_qbb_map
(braket
id|WILDFIRE_MAX_QBB
)braket
suffix:semicolon
r_extern
r_int
r_char
id|wildfire_soft_qbb_map
(braket
id|WILDFIRE_MAX_QBB
)braket
suffix:semicolon
DECL|macro|QBB_MAP_EMPTY
mdefine_line|#define QBB_MAP_EMPTY&t;0xff
r_extern
r_int
r_int
id|wildfire_hard_qbb_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_soft_qbb_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_gp_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_hs_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_iop_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_ior_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_pca_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_cpu_mask
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_mem_mask
suffix:semicolon
DECL|macro|WILDFIRE_QBB_EXISTS
mdefine_line|#define WILDFIRE_QBB_EXISTS(qbbno) (wildfire_soft_qbb_mask &amp; (1 &lt;&lt; (qbbno)))
DECL|macro|WILDFIRE_MEM_EXISTS
mdefine_line|#define WILDFIRE_MEM_EXISTS(qbbno) (wildfire_mem_mask &amp; (0xf &lt;&lt; ((qbbno) &lt;&lt; 2)))
DECL|macro|WILDFIRE_PCA_EXISTS
mdefine_line|#define WILDFIRE_PCA_EXISTS(qbbno, pcano) &bslash;&n;&t;&t;(wildfire_pca_mask &amp; (1 &lt;&lt; (((qbbno) &lt;&lt; 2) + (pcano))))
r_typedef
r_struct
(brace
DECL|member|csr
r_volatile
r_int
r_int
id|csr
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|wildfire_64
)brace
id|wildfire_64
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|csr
r_volatile
r_int
r_int
id|csr
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|wildfire_256
)brace
id|wildfire_256
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|csr
r_volatile
r_int
r_int
id|csr
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|2048
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|wildfire_2k
)brace
id|wildfire_2k
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|qsd_whami
id|wildfire_64
id|qsd_whami
suffix:semicolon
DECL|member|qsd_rev
id|wildfire_64
id|qsd_rev
suffix:semicolon
DECL|member|qsd_port_present
id|wildfire_64
id|qsd_port_present
suffix:semicolon
DECL|member|qsd_port_active
id|wildfire_64
id|qsd_port_active
suffix:semicolon
DECL|member|qsd_fault_ena
id|wildfire_64
id|qsd_fault_ena
suffix:semicolon
DECL|member|qsd_cpu_int_ena
id|wildfire_64
id|qsd_cpu_int_ena
suffix:semicolon
DECL|member|qsd_mem_config
id|wildfire_64
id|qsd_mem_config
suffix:semicolon
DECL|member|qsd_err_sum
id|wildfire_64
id|qsd_err_sum
suffix:semicolon
DECL|member|ce_sum
id|wildfire_64
id|ce_sum
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dev_init
id|wildfire_64
id|dev_init
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|it_int
id|wildfire_64
id|it_int
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ip_int
id|wildfire_64
id|ip_int
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|uce_sum
id|wildfire_64
id|uce_sum
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|se_sum__non_dev_int
id|wildfire_64
id|se_sum__non_dev_int
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|scratch
id|wildfire_64
id|scratch
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|qsd_timer
id|wildfire_64
id|qsd_timer
suffix:semicolon
DECL|member|qsd_diag
id|wildfire_64
id|qsd_diag
suffix:semicolon
DECL|typedef|wildfire_qsd
)brace
id|wildfire_qsd
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|qsd_whami
id|wildfire_256
id|qsd_whami
suffix:semicolon
DECL|member|__pad1
id|wildfire_256
id|__pad1
suffix:semicolon
DECL|member|ce_sum
id|wildfire_256
id|ce_sum
suffix:semicolon
DECL|member|dev_init
id|wildfire_256
id|dev_init
suffix:semicolon
DECL|member|it_int
id|wildfire_256
id|it_int
suffix:semicolon
DECL|member|ip_int
id|wildfire_256
id|ip_int
suffix:semicolon
DECL|member|uce_sum
id|wildfire_256
id|uce_sum
suffix:semicolon
DECL|member|se_sum
id|wildfire_256
id|se_sum
suffix:semicolon
DECL|typedef|wildfire_fast_qsd
)brace
id|wildfire_fast_qsd
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|qsa_qbb_id
id|wildfire_2k
id|qsa_qbb_id
suffix:semicolon
DECL|member|__pad1
id|wildfire_2k
id|__pad1
suffix:semicolon
DECL|member|qsa_port_ena
id|wildfire_2k
id|qsa_port_ena
suffix:semicolon
DECL|member|qsa_scratch
id|wildfire_2k
id|qsa_scratch
suffix:semicolon
DECL|member|qsa_config
id|wildfire_2k
id|qsa_config
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|qsa_ref_int
id|wildfire_2k
id|qsa_ref_int
suffix:semicolon
DECL|member|qsa_qbb_pop
id|wildfire_2k
id|qsa_qbb_pop
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|qsa_dtag_fc
id|wildfire_2k
id|qsa_dtag_fc
suffix:semicolon
DECL|member|__pad2
id|wildfire_2k
id|__pad2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|qsa_diag
id|wildfire_2k
id|qsa_diag
suffix:semicolon
DECL|member|qsa_diag_lock
id|wildfire_2k
id|qsa_diag_lock
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|__pad3
id|wildfire_2k
id|__pad3
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|qsa_cpu_err_sum
id|wildfire_2k
id|qsa_cpu_err_sum
suffix:semicolon
DECL|member|qsa_misc_err_sum
id|wildfire_2k
id|qsa_misc_err_sum
suffix:semicolon
DECL|member|qsa_tmo_err_sum
id|wildfire_2k
id|qsa_tmo_err_sum
suffix:semicolon
DECL|member|qsa_err_ena
id|wildfire_2k
id|qsa_err_ena
suffix:semicolon
DECL|member|qsa_tmo_config
id|wildfire_2k
id|qsa_tmo_config
suffix:semicolon
DECL|member|qsa_ill_cmd_err_sum
id|wildfire_2k
id|qsa_ill_cmd_err_sum
suffix:semicolon
DECL|member|__pad4
id|wildfire_2k
id|__pad4
(braket
l_int|26
)braket
suffix:semicolon
DECL|member|qsa_busy_mask
id|wildfire_2k
id|qsa_busy_mask
suffix:semicolon
DECL|member|qsa_arr_valid
id|wildfire_2k
id|qsa_arr_valid
suffix:semicolon
DECL|member|__pad5
id|wildfire_2k
id|__pad5
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|qsa_port_map
id|wildfire_2k
id|qsa_port_map
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|qsa_arr_addr
id|wildfire_2k
id|qsa_arr_addr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|qsa_arr_mask
id|wildfire_2k
id|qsa_arr_mask
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|wildfire_qsa
)brace
id|wildfire_qsa
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ioa_config
id|wildfire_64
id|ioa_config
suffix:semicolon
DECL|member|iod_config
id|wildfire_64
id|iod_config
suffix:semicolon
DECL|member|iop_switch_credits
id|wildfire_64
id|iop_switch_credits
suffix:semicolon
DECL|member|__pad1
id|wildfire_64
id|__pad1
suffix:semicolon
DECL|member|iop_hose_credits
id|wildfire_64
id|iop_hose_credits
suffix:semicolon
DECL|member|__pad2
id|wildfire_64
id|__pad2
(braket
l_int|11
)braket
suffix:semicolon
r_struct
(brace
DECL|member|__pad3
id|wildfire_64
id|__pad3
suffix:semicolon
DECL|member|init
id|wildfire_64
id|init
suffix:semicolon
DECL|member|iop_hose
)brace
id|iop_hose
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ioa_hose_0_ctrl
id|wildfire_64
id|ioa_hose_0_ctrl
suffix:semicolon
DECL|member|iod_hose_0_ctrl
id|wildfire_64
id|iod_hose_0_ctrl
suffix:semicolon
DECL|member|ioa_hose_1_ctrl
id|wildfire_64
id|ioa_hose_1_ctrl
suffix:semicolon
DECL|member|iod_hose_1_ctrl
id|wildfire_64
id|iod_hose_1_ctrl
suffix:semicolon
DECL|member|ioa_hose_2_ctrl
id|wildfire_64
id|ioa_hose_2_ctrl
suffix:semicolon
DECL|member|iod_hose_2_ctrl
id|wildfire_64
id|iod_hose_2_ctrl
suffix:semicolon
DECL|member|ioa_hose_3_ctrl
id|wildfire_64
id|ioa_hose_3_ctrl
suffix:semicolon
DECL|member|iod_hose_3_ctrl
id|wildfire_64
id|iod_hose_3_ctrl
suffix:semicolon
r_struct
(brace
DECL|member|target
id|wildfire_64
id|target
suffix:semicolon
DECL|member|__pad4
id|wildfire_64
id|__pad4
suffix:semicolon
DECL|member|iop_dev_int
)brace
id|iop_dev_int
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|iop_err_int_target
id|wildfire_64
id|iop_err_int_target
suffix:semicolon
DECL|member|__pad5
id|wildfire_64
id|__pad5
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|iop_qbb_err_sum
id|wildfire_64
id|iop_qbb_err_sum
suffix:semicolon
DECL|member|__pad6
id|wildfire_64
id|__pad6
suffix:semicolon
DECL|member|iop_qbb_se_sum
id|wildfire_64
id|iop_qbb_se_sum
suffix:semicolon
DECL|member|__pad7
id|wildfire_64
id|__pad7
suffix:semicolon
DECL|member|ioa_err_sum
id|wildfire_64
id|ioa_err_sum
suffix:semicolon
DECL|member|iod_err_sum
id|wildfire_64
id|iod_err_sum
suffix:semicolon
DECL|member|__pad8
id|wildfire_64
id|__pad8
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ioa_diag_force_err
id|wildfire_64
id|ioa_diag_force_err
suffix:semicolon
DECL|member|iod_diag_force_err
id|wildfire_64
id|iod_diag_force_err
suffix:semicolon
DECL|member|__pad9
id|wildfire_64
id|__pad9
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|iop_diag_send_err_int
id|wildfire_64
id|iop_diag_send_err_int
suffix:semicolon
DECL|member|__pad10
id|wildfire_64
id|__pad10
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|ioa_scratch
id|wildfire_64
id|ioa_scratch
suffix:semicolon
DECL|member|iod_scratch
id|wildfire_64
id|iod_scratch
suffix:semicolon
DECL|typedef|wildfire_iop
)brace
id|wildfire_iop
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|gpa_qbb_map
id|wildfire_2k
id|gpa_qbb_map
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|gpa_mem_pop_map
id|wildfire_2k
id|gpa_mem_pop_map
suffix:semicolon
DECL|member|gpa_scratch
id|wildfire_2k
id|gpa_scratch
suffix:semicolon
DECL|member|gpa_diag
id|wildfire_2k
id|gpa_diag
suffix:semicolon
DECL|member|gpa_config_0
id|wildfire_2k
id|gpa_config_0
suffix:semicolon
DECL|member|__pad1
id|wildfire_2k
id|__pad1
suffix:semicolon
DECL|member|gpa_init_id
id|wildfire_2k
id|gpa_init_id
suffix:semicolon
DECL|member|gpa_config_2
id|wildfire_2k
id|gpa_config_2
suffix:semicolon
multiline_comment|/* not complete */
DECL|typedef|wildfire_gp
)brace
id|wildfire_gp
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pca_what_am_i
id|wildfire_64
id|pca_what_am_i
suffix:semicolon
DECL|member|pca_err_sum
id|wildfire_64
id|pca_err_sum
suffix:semicolon
DECL|member|pca_diag_force_err
id|wildfire_64
id|pca_diag_force_err
suffix:semicolon
DECL|member|pca_diag_send_err_int
id|wildfire_64
id|pca_diag_send_err_int
suffix:semicolon
DECL|member|pca_hose_credits
id|wildfire_64
id|pca_hose_credits
suffix:semicolon
DECL|member|pca_scratch
id|wildfire_64
id|pca_scratch
suffix:semicolon
DECL|member|pca_micro_addr
id|wildfire_64
id|pca_micro_addr
suffix:semicolon
DECL|member|pca_micro_data
id|wildfire_64
id|pca_micro_data
suffix:semicolon
DECL|member|pca_pend_int
id|wildfire_64
id|pca_pend_int
suffix:semicolon
DECL|member|pca_sent_int
id|wildfire_64
id|pca_sent_int
suffix:semicolon
DECL|member|__pad1
id|wildfire_64
id|__pad1
suffix:semicolon
DECL|member|pca_stdio_edge_level
id|wildfire_64
id|pca_stdio_edge_level
suffix:semicolon
DECL|member|__pad2
id|wildfire_64
id|__pad2
(braket
l_int|52
)braket
suffix:semicolon
r_struct
(brace
DECL|member|target
id|wildfire_64
id|target
suffix:semicolon
DECL|member|enable
id|wildfire_64
id|enable
suffix:semicolon
DECL|member|pca_int
)brace
id|pca_int
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|__pad3
id|wildfire_64
id|__pad3
(braket
l_int|56
)braket
suffix:semicolon
DECL|member|pca_alt_sent_int
id|wildfire_64
id|pca_alt_sent_int
(braket
l_int|32
)braket
suffix:semicolon
DECL|typedef|wildfire_pca
)brace
id|wildfire_pca
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ne_what_am_i
id|wildfire_64
id|ne_what_am_i
suffix:semicolon
multiline_comment|/* not complete */
DECL|typedef|wildfire_ne
)brace
id|wildfire_ne
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fe_what_am_i
id|wildfire_64
id|fe_what_am_i
suffix:semicolon
multiline_comment|/* not complete */
DECL|typedef|wildfire_fe
)brace
id|wildfire_fe
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pci_io_addr_ext
id|wildfire_64
id|pci_io_addr_ext
suffix:semicolon
DECL|member|pci_ctrl
id|wildfire_64
id|pci_ctrl
suffix:semicolon
DECL|member|pci_err_sum
id|wildfire_64
id|pci_err_sum
suffix:semicolon
DECL|member|pci_err_addr
id|wildfire_64
id|pci_err_addr
suffix:semicolon
DECL|member|pci_stall_cnt
id|wildfire_64
id|pci_stall_cnt
suffix:semicolon
DECL|member|pci_iack_special
id|wildfire_64
id|pci_iack_special
suffix:semicolon
DECL|member|__pad1
id|wildfire_64
id|__pad1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pci_pend_int
id|wildfire_64
id|pci_pend_int
suffix:semicolon
DECL|member|pci_sent_int
id|wildfire_64
id|pci_sent_int
suffix:semicolon
DECL|member|__pad2
id|wildfire_64
id|__pad2
(braket
l_int|54
)braket
suffix:semicolon
r_struct
(brace
DECL|member|wbase
id|wildfire_64
id|wbase
suffix:semicolon
DECL|member|wmask
id|wildfire_64
id|wmask
suffix:semicolon
DECL|member|tbase
id|wildfire_64
id|tbase
suffix:semicolon
DECL|member|pci_window
)brace
id|pci_window
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pci_flush_tlb
id|wildfire_64
id|pci_flush_tlb
suffix:semicolon
DECL|member|pci_perf_mon
id|wildfire_64
id|pci_perf_mon
suffix:semicolon
DECL|typedef|wildfire_pci
)brace
id|wildfire_pci
suffix:semicolon
DECL|macro|WILDFIRE_ENTITY_SHIFT
mdefine_line|#define WILDFIRE_ENTITY_SHIFT&t;&t;18
DECL|macro|WILDFIRE_GP_ENTITY
mdefine_line|#define WILDFIRE_GP_ENTITY&t;&t;(0x10UL &lt;&lt; WILDFIRE_ENTITY_SHIFT)
DECL|macro|WILDFIRE_IOP_ENTITY
mdefine_line|#define WILDFIRE_IOP_ENTITY&t;&t;(0x08UL &lt;&lt; WILDFIRE_ENTITY_SHIFT)
DECL|macro|WILDFIRE_QSA_ENTITY
mdefine_line|#define WILDFIRE_QSA_ENTITY&t;&t;(0x04UL &lt;&lt; WILDFIRE_ENTITY_SHIFT)
DECL|macro|WILDFIRE_QSD_ENTITY_SLOW
mdefine_line|#define WILDFIRE_QSD_ENTITY_SLOW&t;(0x05UL &lt;&lt; WILDFIRE_ENTITY_SHIFT)
DECL|macro|WILDFIRE_QSD_ENTITY_FAST
mdefine_line|#define WILDFIRE_QSD_ENTITY_FAST&t;(0x01UL &lt;&lt; WILDFIRE_ENTITY_SHIFT)
DECL|macro|WILDFIRE_PCA_ENTITY
mdefine_line|#define WILDFIRE_PCA_ENTITY(pca)&t;((0xc|(pca))&lt;&lt;WILDFIRE_ENTITY_SHIFT)
DECL|macro|WILDFIRE_BASE
mdefine_line|#define WILDFIRE_BASE&t;&t;(IDENT_ADDR | (1UL &lt;&lt; 40))
DECL|macro|WILDFIRE_QBB_MASK
mdefine_line|#define WILDFIRE_QBB_MASK&t;0x0fUL&t;/* for now, only 4 bits/16 QBBs */
DECL|macro|WILDFIRE_QBB
mdefine_line|#define WILDFIRE_QBB(q)&t;&t;((~((long)(q)) &amp; WILDFIRE_QBB_MASK) &lt;&lt; 36)
DECL|macro|WILDFIRE_HOSE
mdefine_line|#define WILDFIRE_HOSE(h)&t;((long)(h) &lt;&lt; 33)
DECL|macro|WILDFIRE_QBB_IO
mdefine_line|#define WILDFIRE_QBB_IO(q)&t;(WILDFIRE_BASE | WILDFIRE_QBB(q))
DECL|macro|WILDFIRE_QBB_HOSE
mdefine_line|#define WILDFIRE_QBB_HOSE(q,h)&t;(WILDFIRE_QBB_IO(q) | WILDFIRE_HOSE(h))
DECL|macro|WILDFIRE_MEM
mdefine_line|#define WILDFIRE_MEM(q,h)&t;(WILDFIRE_QBB_HOSE(q,h) | 0x000000000UL)
DECL|macro|WILDFIRE_CONF
mdefine_line|#define WILDFIRE_CONF(q,h)&t;(WILDFIRE_QBB_HOSE(q,h) | 0x1FE000000UL)
DECL|macro|WILDFIRE_IO
mdefine_line|#define WILDFIRE_IO(q,h)&t;(WILDFIRE_QBB_HOSE(q,h) | 0x1FF000000UL)
DECL|macro|WILDFIRE_qsd
mdefine_line|#define WILDFIRE_qsd(q) &bslash;&n; ((wildfire_qsd *)(WILDFIRE_QBB_IO(q)|WILDFIRE_QSD_ENTITY_SLOW|(((1UL&lt;&lt;13)-1)&lt;&lt;23)))
DECL|macro|WILDFIRE_fast_qsd
mdefine_line|#define WILDFIRE_fast_qsd() &bslash;&n; ((wildfire_fast_qsd *)(WILDFIRE_QBB_IO(0)|WILDFIRE_QSD_ENTITY_FAST|(((1UL&lt;&lt;13)-1)&lt;&lt;23)))
DECL|macro|WILDFIRE_qsa
mdefine_line|#define WILDFIRE_qsa(q) &bslash;&n; ((wildfire_qsa *)(WILDFIRE_QBB_IO(q)|WILDFIRE_QSA_ENTITY|(((1UL&lt;&lt;13)-1)&lt;&lt;23)))
DECL|macro|WILDFIRE_iop
mdefine_line|#define WILDFIRE_iop(q) &bslash;&n; ((wildfire_iop *)(WILDFIRE_QBB_IO(q)|WILDFIRE_IOP_ENTITY|(((1UL&lt;&lt;13)-1)&lt;&lt;23)))
DECL|macro|WILDFIRE_gp
mdefine_line|#define WILDFIRE_gp(q) &bslash;&n; ((wildfire_gp *)(WILDFIRE_QBB_IO(q)|WILDFIRE_GP_ENTITY|(((1UL&lt;&lt;13)-1)&lt;&lt;23)))
DECL|macro|WILDFIRE_pca
mdefine_line|#define WILDFIRE_pca(q,pca) &bslash;&n; ((wildfire_pca *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(pca)|(((1UL&lt;&lt;13)-1)&lt;&lt;23)))
DECL|macro|WILDFIRE_ne
mdefine_line|#define WILDFIRE_ne(q,pca) &bslash;&n; ((wildfire_ne *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(pca)|(((1UL&lt;&lt;13)-1)&lt;&lt;23)|(1UL&lt;&lt;16)))
DECL|macro|WILDFIRE_fe
mdefine_line|#define WILDFIRE_fe(q,pca) &bslash;&n; ((wildfire_fe *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(pca)|(((1UL&lt;&lt;13)-1)&lt;&lt;23)|(3UL&lt;&lt;15)))
DECL|macro|WILDFIRE_pci
mdefine_line|#define WILDFIRE_pci(q,h) &bslash;&n; ((wildfire_pci *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(((h)&amp;6)&gt;&gt;1)|((((h)&amp;1)|2)&lt;&lt;16)|(((1UL&lt;&lt;13)-1)&lt;&lt;23)))
DECL|macro|WILDFIRE_IO_BIAS
mdefine_line|#define WILDFIRE_IO_BIAS        WILDFIRE_IO(0,0)
DECL|macro|WILDFIRE_MEM_BIAS
mdefine_line|#define WILDFIRE_MEM_BIAS       WILDFIRE_MEM(0,0) /* ??? */
multiline_comment|/* The IO address space is larger than 0xffff */
DECL|macro|WILDFIRE_IO_SPACE
mdefine_line|#define WILDFIRE_IO_SPACE&t;(8UL*1024*1024)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|function|wildfire_inb
id|__EXTERN_INLINE
id|u8
id|wildfire_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* ??? I wish I could get rid of this.  But there&squot;s no ioremap&n;&t;   equivalent for I/O space.  PCI I/O can be forced into the&n;&t;   correct hose&squot;s I/O region, but that doesn&squot;t take care of&n;&t;   legacy ISA crap.  */
id|addr
op_add_assign
id|WILDFIRE_IO_BIAS
suffix:semicolon
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|wildfire_outb
id|__EXTERN_INLINE
r_void
id|wildfire_outb
c_func
(paren
id|u8
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|WILDFIRE_IO_BIAS
suffix:semicolon
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|wildfire_inw
id|__EXTERN_INLINE
id|u16
id|wildfire_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|WILDFIRE_IO_BIAS
suffix:semicolon
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|wildfire_outw
id|__EXTERN_INLINE
r_void
id|wildfire_outw
c_func
(paren
id|u16
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|WILDFIRE_IO_BIAS
suffix:semicolon
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|wildfire_inl
id|__EXTERN_INLINE
id|u32
id|wildfire_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|WILDFIRE_IO_BIAS
suffix:semicolon
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|wildfire_outl
id|__EXTERN_INLINE
r_void
id|wildfire_outl
c_func
(paren
id|u32
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|WILDFIRE_IO_BIAS
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.  all accesses are done through linear space.&n; */
DECL|function|wildfire_ioremap
id|__EXTERN_INLINE
r_int
r_int
id|wildfire_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
)paren
(brace
r_return
id|addr
op_plus
id|WILDFIRE_MEM_BIAS
suffix:semicolon
)brace
DECL|function|wildfire_iounmap
id|__EXTERN_INLINE
r_void
id|wildfire_iounmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|wildfire_is_ioaddr
id|__EXTERN_INLINE
r_int
id|wildfire_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|WILDFIRE_BASE
suffix:semicolon
)brace
DECL|function|wildfire_readb
id|__EXTERN_INLINE
id|u8
id|wildfire_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|wildfire_readw
id|__EXTERN_INLINE
id|u16
id|wildfire_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|wildfire_readl
id|__EXTERN_INLINE
id|u32
id|wildfire_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
op_star
(paren
id|vuip
)paren
id|addr
)paren
op_amp
l_int|0xffffffff
suffix:semicolon
)brace
DECL|function|wildfire_readq
id|__EXTERN_INLINE
id|u64
id|wildfire_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vulp
)paren
id|addr
suffix:semicolon
)brace
DECL|function|wildfire_writeb
id|__EXTERN_INLINE
r_void
id|wildfire_writeb
c_func
(paren
id|u8
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|wildfire_writew
id|__EXTERN_INLINE
r_void
id|wildfire_writew
c_func
(paren
id|u16
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|wildfire_writel
id|__EXTERN_INLINE
r_void
id|wildfire_writel
c_func
(paren
id|u32
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|wildfire_writeq
id|__EXTERN_INLINE
r_void
id|wildfire_writeq
c_func
(paren
id|u64
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vulp
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
mdefine_line|#define __inb(p)&t;&t;wildfire_inb((unsigned long)(p))
DECL|macro|__inw
mdefine_line|#define __inw(p)&t;&t;wildfire_inw((unsigned long)(p))
DECL|macro|__inl
mdefine_line|#define __inl(p)&t;&t;wildfire_inl((unsigned long)(p))
DECL|macro|__outb
mdefine_line|#define __outb(x,p)&t;&t;wildfire_outb((x),(unsigned long)(p))
DECL|macro|__outw
mdefine_line|#define __outw(x,p)&t;&t;wildfire_outw((x),(unsigned long)(p))
DECL|macro|__outl
mdefine_line|#define __outl(x,p)&t;&t;wildfire_outl((x),(unsigned long)(p))
DECL|macro|__readb
mdefine_line|#define __readb(a)&t;&t;wildfire_readb((unsigned long)(a))
DECL|macro|__readw
mdefine_line|#define __readw(a)&t;&t;wildfire_readw((unsigned long)(a))
DECL|macro|__readl
mdefine_line|#define __readl(a)&t;&t;wildfire_readl((unsigned long)(a))
DECL|macro|__readq
mdefine_line|#define __readq(a)&t;&t;wildfire_readq((unsigned long)(a))
DECL|macro|__writeb
mdefine_line|#define __writeb(x,a)&t;&t;wildfire_writeb((x),(unsigned long)(a))
DECL|macro|__writew
mdefine_line|#define __writew(x,a)&t;&t;wildfire_writew((x),(unsigned long)(a))
DECL|macro|__writel
mdefine_line|#define __writel(x,a)&t;&t;wildfire_writel((x),(unsigned long)(a))
DECL|macro|__writeq
mdefine_line|#define __writeq(x,a)&t;&t;wildfire_writeq((x),(unsigned long)(a))
DECL|macro|__ioremap
mdefine_line|#define __ioremap(a,s)&t;&t;wildfire_ioremap((unsigned long)(a),(s))
DECL|macro|__iounmap
mdefine_line|#define __iounmap(a)&t;&t;wildfire_iounmap((unsigned long)(a))
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr(a)&t;&t;wildfire_is_ioaddr((unsigned long)(a))
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;&t;__inb(p)
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&t;__inw(p)
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&t;__inl(p)
DECL|macro|outb
mdefine_line|#define outb(x,p)&t;&t;__outb((x),(p))
DECL|macro|outw
mdefine_line|#define outw(x,p)&t;&t;__outw((x),(p))
DECL|macro|outl
mdefine_line|#define outl(x,p)&t;&t;__outl((x),(p))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)&t;&t;__readb(a)
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)&t;&t;__readw(a)
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;__readl(a)
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a)&t;&t;__readq(a)
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v,a)&t;__writeb((v),(a))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)&t;__writew((v),(a))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;__writel((v),(a))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v,a)&t;__writeq((v),(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_WILDFIRE__H__ */
eof
