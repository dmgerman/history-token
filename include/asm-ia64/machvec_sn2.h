multiline_comment|/*&n; * Copyright (c) 2002-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#ifndef _ASM_IA64_MACHVEC_SN2_H
DECL|macro|_ASM_IA64_MACHVEC_SN2_H
mdefine_line|#define _ASM_IA64_MACHVEC_SN2_H
r_extern
id|ia64_mv_setup_t
id|sn_setup
suffix:semicolon
r_extern
id|ia64_mv_cpu_init_t
id|sn_cpu_init
suffix:semicolon
r_extern
id|ia64_mv_irq_init_t
id|sn_irq_init
suffix:semicolon
r_extern
id|ia64_mv_send_ipi_t
id|sn2_send_IPI
suffix:semicolon
r_extern
id|ia64_mv_timer_interrupt_t
id|sn_timer_interrupt
suffix:semicolon
r_extern
id|ia64_mv_global_tlb_purge_t
id|sn2_global_tlb_purge
suffix:semicolon
r_extern
id|ia64_mv_tlb_migrate_finish_t
id|sn_tlb_migrate_finish
suffix:semicolon
r_extern
id|ia64_mv_irq_desc
id|sn_irq_desc
suffix:semicolon
r_extern
id|ia64_mv_irq_to_vector
id|sn_irq_to_vector
suffix:semicolon
r_extern
id|ia64_mv_local_vector_to_irq
id|sn_local_vector_to_irq
suffix:semicolon
r_extern
id|ia64_mv_pci_get_legacy_mem_t
id|sn_pci_get_legacy_mem
suffix:semicolon
r_extern
id|ia64_mv_pci_legacy_read_t
id|sn_pci_legacy_read
suffix:semicolon
r_extern
id|ia64_mv_pci_legacy_write_t
id|sn_pci_legacy_write
suffix:semicolon
r_extern
id|ia64_mv_inb_t
id|__sn_inb
suffix:semicolon
r_extern
id|ia64_mv_inw_t
id|__sn_inw
suffix:semicolon
r_extern
id|ia64_mv_inl_t
id|__sn_inl
suffix:semicolon
r_extern
id|ia64_mv_outb_t
id|__sn_outb
suffix:semicolon
r_extern
id|ia64_mv_outw_t
id|__sn_outw
suffix:semicolon
r_extern
id|ia64_mv_outl_t
id|__sn_outl
suffix:semicolon
r_extern
id|ia64_mv_mmiowb_t
id|__sn_mmiowb
suffix:semicolon
r_extern
id|ia64_mv_readb_t
id|__sn_readb
suffix:semicolon
r_extern
id|ia64_mv_readw_t
id|__sn_readw
suffix:semicolon
r_extern
id|ia64_mv_readl_t
id|__sn_readl
suffix:semicolon
r_extern
id|ia64_mv_readq_t
id|__sn_readq
suffix:semicolon
r_extern
id|ia64_mv_readb_t
id|__sn_readb_relaxed
suffix:semicolon
r_extern
id|ia64_mv_readw_t
id|__sn_readw_relaxed
suffix:semicolon
r_extern
id|ia64_mv_readl_t
id|__sn_readl_relaxed
suffix:semicolon
r_extern
id|ia64_mv_readq_t
id|__sn_readq_relaxed
suffix:semicolon
r_extern
id|ia64_mv_dma_alloc_coherent
id|sn_dma_alloc_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_free_coherent
id|sn_dma_free_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_map_single
id|sn_dma_map_single
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_single
id|sn_dma_unmap_single
suffix:semicolon
r_extern
id|ia64_mv_dma_map_sg
id|sn_dma_map_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_sg
id|sn_dma_unmap_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_single_for_cpu
id|sn_dma_sync_single_for_cpu
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_sg_for_cpu
id|sn_dma_sync_sg_for_cpu
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_single_for_device
id|sn_dma_sync_single_for_device
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_sg_for_device
id|sn_dma_sync_sg_for_device
suffix:semicolon
r_extern
id|ia64_mv_dma_mapping_error
id|sn_dma_mapping_error
suffix:semicolon
r_extern
id|ia64_mv_dma_supported
id|sn_dma_supported
suffix:semicolon
multiline_comment|/*&n; * This stuff has dual use!&n; *&n; * For a generic kernel, the macros are used to initialize the&n; * platform&squot;s machvec structure.  When compiling a non-generic kernel,&n; * the macros are used directly.&n; */
DECL|macro|platform_name
mdefine_line|#define platform_name&t;&t;&t;&quot;sn2&quot;
DECL|macro|platform_setup
mdefine_line|#define platform_setup&t;&t;&t;sn_setup
DECL|macro|platform_cpu_init
mdefine_line|#define platform_cpu_init&t;&t;sn_cpu_init
DECL|macro|platform_irq_init
mdefine_line|#define platform_irq_init&t;&t;sn_irq_init
DECL|macro|platform_send_ipi
mdefine_line|#define platform_send_ipi&t;&t;sn2_send_IPI
DECL|macro|platform_timer_interrupt
mdefine_line|#define platform_timer_interrupt&t;sn_timer_interrupt
DECL|macro|platform_global_tlb_purge
mdefine_line|#define platform_global_tlb_purge       sn2_global_tlb_purge
DECL|macro|platform_tlb_migrate_finish
mdefine_line|#define platform_tlb_migrate_finish&t;sn_tlb_migrate_finish
DECL|macro|platform_pci_fixup
mdefine_line|#define platform_pci_fixup&t;&t;sn_pci_fixup
DECL|macro|platform_inb
mdefine_line|#define platform_inb&t;&t;&t;__sn_inb
DECL|macro|platform_inw
mdefine_line|#define platform_inw&t;&t;&t;__sn_inw
DECL|macro|platform_inl
mdefine_line|#define platform_inl&t;&t;&t;__sn_inl
DECL|macro|platform_outb
mdefine_line|#define platform_outb&t;&t;&t;__sn_outb
DECL|macro|platform_outw
mdefine_line|#define platform_outw&t;&t;&t;__sn_outw
DECL|macro|platform_outl
mdefine_line|#define platform_outl&t;&t;&t;__sn_outl
DECL|macro|platform_mmiowb
mdefine_line|#define platform_mmiowb&t;&t;&t;__sn_mmiowb
DECL|macro|platform_readb
mdefine_line|#define platform_readb&t;&t;&t;__sn_readb
DECL|macro|platform_readw
mdefine_line|#define platform_readw&t;&t;&t;__sn_readw
DECL|macro|platform_readl
mdefine_line|#define platform_readl&t;&t;&t;__sn_readl
DECL|macro|platform_readq
mdefine_line|#define platform_readq&t;&t;&t;__sn_readq
DECL|macro|platform_readb_relaxed
mdefine_line|#define platform_readb_relaxed&t;&t;__sn_readb_relaxed
DECL|macro|platform_readw_relaxed
mdefine_line|#define platform_readw_relaxed&t;&t;__sn_readw_relaxed
DECL|macro|platform_readl_relaxed
mdefine_line|#define platform_readl_relaxed&t;&t;__sn_readl_relaxed
DECL|macro|platform_readq_relaxed
mdefine_line|#define platform_readq_relaxed&t;&t;__sn_readq_relaxed
DECL|macro|platform_irq_desc
mdefine_line|#define platform_irq_desc&t;&t;sn_irq_desc
DECL|macro|platform_irq_to_vector
mdefine_line|#define platform_irq_to_vector&t;&t;sn_irq_to_vector
DECL|macro|platform_local_vector_to_irq
mdefine_line|#define platform_local_vector_to_irq&t;sn_local_vector_to_irq
DECL|macro|platform_pci_get_legacy_mem
mdefine_line|#define platform_pci_get_legacy_mem&t;sn_pci_get_legacy_mem
DECL|macro|platform_pci_legacy_read
mdefine_line|#define platform_pci_legacy_read&t;sn_pci_legacy_read
DECL|macro|platform_pci_legacy_write
mdefine_line|#define platform_pci_legacy_write&t;sn_pci_legacy_write
DECL|macro|platform_dma_init
mdefine_line|#define platform_dma_init&t;&t;machvec_noop
DECL|macro|platform_dma_alloc_coherent
mdefine_line|#define platform_dma_alloc_coherent&t;sn_dma_alloc_coherent
DECL|macro|platform_dma_free_coherent
mdefine_line|#define platform_dma_free_coherent&t;sn_dma_free_coherent
DECL|macro|platform_dma_map_single
mdefine_line|#define platform_dma_map_single&t;&t;sn_dma_map_single
DECL|macro|platform_dma_unmap_single
mdefine_line|#define platform_dma_unmap_single&t;sn_dma_unmap_single
DECL|macro|platform_dma_map_sg
mdefine_line|#define platform_dma_map_sg&t;&t;sn_dma_map_sg
DECL|macro|platform_dma_unmap_sg
mdefine_line|#define platform_dma_unmap_sg&t;&t;sn_dma_unmap_sg
DECL|macro|platform_dma_sync_single_for_cpu
mdefine_line|#define platform_dma_sync_single_for_cpu sn_dma_sync_single_for_cpu
DECL|macro|platform_dma_sync_sg_for_cpu
mdefine_line|#define platform_dma_sync_sg_for_cpu&t;sn_dma_sync_sg_for_cpu
DECL|macro|platform_dma_sync_single_for_device
mdefine_line|#define platform_dma_sync_single_for_device sn_dma_sync_single_for_device
DECL|macro|platform_dma_sync_sg_for_device
mdefine_line|#define platform_dma_sync_sg_for_device&t;sn_dma_sync_sg_for_device
DECL|macro|platform_dma_mapping_error
mdefine_line|#define platform_dma_mapping_error&t;&t;sn_dma_mapping_error
DECL|macro|platform_dma_supported
mdefine_line|#define platform_dma_supported&t;&t;sn_dma_supported
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#endif /* _ASM_IA64_MACHVEC_SN2_H */
eof
