multiline_comment|/*&n; * Copyright (c) 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#ifndef _ASM_IA64_MACHVEC_SN2_H
DECL|macro|_ASM_IA64_MACHVEC_SN2_H
mdefine_line|#define _ASM_IA64_MACHVEC_SN2_H
r_extern
id|ia64_mv_setup_t
id|sn1_setup
suffix:semicolon
r_extern
id|ia64_mv_cpu_init_t
id|sn_cpu_init
suffix:semicolon
r_extern
id|ia64_mv_irq_init_t
id|sn1_irq_init
suffix:semicolon
r_extern
id|ia64_mv_map_nr_t
id|sn2_map_nr
suffix:semicolon
r_extern
id|ia64_mv_send_ipi_t
id|sn2_send_IPI
suffix:semicolon
r_extern
id|ia64_mv_global_tlb_purge_t
id|sn2_global_tlb_purge
suffix:semicolon
r_extern
id|ia64_mv_irq_desc
id|sn1_irq_desc
suffix:semicolon
r_extern
id|ia64_mv_irq_to_vector
id|sn1_irq_to_vector
suffix:semicolon
r_extern
id|ia64_mv_local_vector_to_irq
id|sn1_local_vector_to_irq
suffix:semicolon
r_extern
id|ia64_mv_valid_irq
id|sn1_valid_irq
suffix:semicolon
r_extern
id|ia64_mv_pci_fixup_t
id|sn1_pci_fixup
suffix:semicolon
macro_line|#ifdef Colin /* We are using the same is Generic IA64 calls defined in io.h */
r_extern
id|ia64_mv_inb_t
id|sn1_inb
suffix:semicolon
r_extern
id|ia64_mv_inw_t
id|sn1_inw
suffix:semicolon
r_extern
id|ia64_mv_inl_t
id|sn1_inl
suffix:semicolon
r_extern
id|ia64_mv_outb_t
id|sn1_outb
suffix:semicolon
r_extern
id|ia64_mv_outw_t
id|sn1_outw
suffix:semicolon
r_extern
id|ia64_mv_outl_t
id|sn1_outl
suffix:semicolon
macro_line|#endif
r_extern
id|ia64_mv_pci_alloc_consistent
id|sn1_pci_alloc_consistent
suffix:semicolon
r_extern
id|ia64_mv_pci_free_consistent
id|sn1_pci_free_consistent
suffix:semicolon
r_extern
id|ia64_mv_pci_map_single
id|sn1_pci_map_single
suffix:semicolon
r_extern
id|ia64_mv_pci_unmap_single
id|sn1_pci_unmap_single
suffix:semicolon
r_extern
id|ia64_mv_pci_map_sg
id|sn1_pci_map_sg
suffix:semicolon
r_extern
id|ia64_mv_pci_unmap_sg
id|sn1_pci_unmap_sg
suffix:semicolon
r_extern
id|ia64_mv_pci_dma_sync_single
id|sn1_pci_dma_sync_single
suffix:semicolon
r_extern
id|ia64_mv_pci_dma_sync_sg
id|sn1_pci_dma_sync_sg
suffix:semicolon
r_extern
id|ia64_mv_pci_dma_address
id|sn1_dma_address
suffix:semicolon
multiline_comment|/*&n; * This stuff has dual use!&n; *&n; * For a generic kernel, the macros are used to initialize the&n; * platform&squot;s machvec structure.  When compiling a non-generic kernel,&n; * the macros are used directly.&n; */
DECL|macro|platform_name
mdefine_line|#define platform_name&t;&t;&quot;sn2&quot;
DECL|macro|platform_setup
mdefine_line|#define platform_setup&t;&t;sn1_setup
DECL|macro|platform_cpu_init
mdefine_line|#define platform_cpu_init&t;sn_cpu_init
DECL|macro|platform_irq_init
mdefine_line|#define platform_irq_init&t;sn1_irq_init
DECL|macro|platform_map_nr
mdefine_line|#define platform_map_nr&t;&t;sn2_map_nr
DECL|macro|platform_send_ipi
mdefine_line|#define platform_send_ipi&t;sn2_send_IPI
DECL|macro|platform_global_tlb_purge
mdefine_line|#define platform_global_tlb_purge       sn2_global_tlb_purge
DECL|macro|platform_pci_fixup
mdefine_line|#define platform_pci_fixup&t;sn1_pci_fixup
macro_line|#ifdef Colin /* We are using the same is Generic IA64 calls defined in io.h */
DECL|macro|platform_inb
mdefine_line|#define platform_inb&t;&t;sn1_inb
DECL|macro|platform_inw
mdefine_line|#define platform_inw&t;&t;sn1_inw
DECL|macro|platform_inl
mdefine_line|#define platform_inl&t;&t;sn1_inl
DECL|macro|platform_outb
mdefine_line|#define platform_outb&t;&t;sn1_outb
DECL|macro|platform_outw
mdefine_line|#define platform_outw&t;&t;sn1_outw
DECL|macro|platform_outl
mdefine_line|#define platform_outl&t;&t;sn1_outl
macro_line|#endif
DECL|macro|platform_irq_desc
mdefine_line|#define platform_irq_desc&t;sn1_irq_desc
DECL|macro|platform_irq_to_vector
mdefine_line|#define platform_irq_to_vector&t;sn1_irq_to_vector
DECL|macro|platform_local_vector_to_irq
mdefine_line|#define platform_local_vector_to_irq&t;sn1_local_vector_to_irq
DECL|macro|platform_valid_irq
mdefine_line|#define platform_valid_irq&t;sn1_valid_irq
DECL|macro|platform_pci_dma_init
mdefine_line|#define platform_pci_dma_init&t;machvec_noop
DECL|macro|platform_pci_alloc_consistent
mdefine_line|#define platform_pci_alloc_consistent&t;sn1_pci_alloc_consistent
DECL|macro|platform_pci_free_consistent
mdefine_line|#define platform_pci_free_consistent&t;sn1_pci_free_consistent
DECL|macro|platform_pci_map_single
mdefine_line|#define platform_pci_map_single&t;&t;sn1_pci_map_single
DECL|macro|platform_pci_unmap_single
mdefine_line|#define platform_pci_unmap_single&t;sn1_pci_unmap_single
DECL|macro|platform_pci_map_sg
mdefine_line|#define platform_pci_map_sg&t;&t;sn1_pci_map_sg
DECL|macro|platform_pci_unmap_sg
mdefine_line|#define platform_pci_unmap_sg&t;&t;sn1_pci_unmap_sg
DECL|macro|platform_pci_dma_sync_single
mdefine_line|#define platform_pci_dma_sync_single&t;sn1_pci_dma_sync_single
DECL|macro|platform_pci_dma_sync_sg
mdefine_line|#define platform_pci_dma_sync_sg&t;sn1_pci_dma_sync_sg
DECL|macro|platform_pci_dma_address
mdefine_line|#define platform_pci_dma_address&t;sn1_dma_address
macro_line|#endif /* _ASM_IA64_MACHVEC_SN2_H */
eof
