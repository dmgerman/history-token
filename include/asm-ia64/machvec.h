multiline_comment|/*&n; * Machine vector for IA-64.&n; *&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) Srinivasa Thirumalachar &lt;sprasad@engr.sgi.com&gt;&n; * Copyright (C) Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; * Copyright (C) 1999-2001, 2003-2004 Hewlett-Packard Co.&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_MACHVEC_H
DECL|macro|_ASM_IA64_MACHVEC_H
mdefine_line|#define _ASM_IA64_MACHVEC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* forward declarations: */
r_struct
id|device
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|scatterlist
suffix:semicolon
r_struct
id|irq_desc
suffix:semicolon
r_struct
id|page
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
DECL|typedef|ia64_mv_setup_t
r_typedef
r_void
id|ia64_mv_setup_t
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_cpu_init_t
r_typedef
r_void
id|ia64_mv_cpu_init_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_irq_init_t
r_typedef
r_void
id|ia64_mv_irq_init_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_send_ipi_t
r_typedef
r_void
id|ia64_mv_send_ipi_t
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_timer_interrupt_t
r_typedef
r_void
id|ia64_mv_timer_interrupt_t
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_global_tlb_purge_t
r_typedef
r_void
id|ia64_mv_global_tlb_purge_t
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_tlb_migrate_finish_t
r_typedef
r_void
id|ia64_mv_tlb_migrate_finish_t
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_irq_desc
r_typedef
r_struct
id|irq_desc
op_star
id|ia64_mv_irq_desc
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_irq_to_vector
r_typedef
id|u8
id|ia64_mv_irq_to_vector
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_local_vector_to_irq
r_typedef
r_int
r_int
id|ia64_mv_local_vector_to_irq
(paren
id|u8
)paren
suffix:semicolon
multiline_comment|/* DMA-mapping interface: */
DECL|typedef|ia64_mv_dma_init
r_typedef
r_void
id|ia64_mv_dma_init
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_alloc_coherent
r_typedef
r_void
op_star
id|ia64_mv_dma_alloc_coherent
(paren
r_struct
id|device
op_star
comma
r_int
comma
id|dma_addr_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_free_coherent
r_typedef
r_void
id|ia64_mv_dma_free_coherent
(paren
r_struct
id|device
op_star
comma
r_int
comma
r_void
op_star
comma
id|dma_addr_t
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_map_single
r_typedef
id|dma_addr_t
id|ia64_mv_dma_map_single
(paren
r_struct
id|device
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_unmap_single
r_typedef
r_void
id|ia64_mv_dma_unmap_single
(paren
r_struct
id|device
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_map_sg
r_typedef
r_int
id|ia64_mv_dma_map_sg
(paren
r_struct
id|device
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_unmap_sg
r_typedef
r_void
id|ia64_mv_dma_unmap_sg
(paren
r_struct
id|device
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_sync_single_for_cpu
r_typedef
r_void
id|ia64_mv_dma_sync_single_for_cpu
(paren
r_struct
id|device
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_sync_sg_for_cpu
r_typedef
r_void
id|ia64_mv_dma_sync_sg_for_cpu
(paren
r_struct
id|device
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_sync_single_for_device
r_typedef
r_void
id|ia64_mv_dma_sync_single_for_device
(paren
r_struct
id|device
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_sync_sg_for_device
r_typedef
r_void
id|ia64_mv_dma_sync_sg_for_device
(paren
r_struct
id|device
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_mapping_error
r_typedef
r_int
id|ia64_mv_dma_mapping_error
(paren
id|dma_addr_t
id|dma_addr
)paren
suffix:semicolon
DECL|typedef|ia64_mv_dma_supported
r_typedef
r_int
id|ia64_mv_dma_supported
(paren
r_struct
id|device
op_star
comma
id|u64
)paren
suffix:semicolon
multiline_comment|/*&n; * WARNING: The legacy I/O space is _architected_.  Platforms are&n; * expected to follow this architected model (see Section 10.7 in the&n; * IA-64 Architecture Software Developer&squot;s Manual).  Unfortunately,&n; * some broken machines do not follow that model, which is why we have&n; * to make the inX/outX operations part of the machine vector.&n; * Platform designers should follow the architected model whenever&n; * possible.&n; */
DECL|typedef|ia64_mv_inb_t
r_typedef
r_int
r_int
id|ia64_mv_inb_t
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_inw_t
r_typedef
r_int
r_int
id|ia64_mv_inw_t
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_inl_t
r_typedef
r_int
r_int
id|ia64_mv_inl_t
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_outb_t
r_typedef
r_void
id|ia64_mv_outb_t
(paren
r_int
r_char
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_outw_t
r_typedef
r_void
id|ia64_mv_outw_t
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_outl_t
r_typedef
r_void
id|ia64_mv_outl_t
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_mmiowb_t
r_typedef
r_void
id|ia64_mv_mmiowb_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readb_t
r_typedef
r_int
r_char
id|ia64_mv_readb_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readw_t
r_typedef
r_int
r_int
id|ia64_mv_readw_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readl_t
r_typedef
r_int
r_int
id|ia64_mv_readl_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readq_t
r_typedef
r_int
r_int
id|ia64_mv_readq_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readb_relaxed_t
r_typedef
r_int
r_char
id|ia64_mv_readb_relaxed_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readw_relaxed_t
r_typedef
r_int
r_int
id|ia64_mv_readw_relaxed_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readl_relaxed_t
r_typedef
r_int
r_int
id|ia64_mv_readl_relaxed_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_readq_relaxed_t
r_typedef
r_int
r_int
id|ia64_mv_readq_relaxed_t
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|machvec_noop
id|machvec_noop
(paren
r_void
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|machvec_noop_mm
id|machvec_noop_mm
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
)brace
r_extern
r_void
id|machvec_setup
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|machvec_timer_interrupt
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|machvec_dma_sync_single
(paren
r_struct
id|device
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|machvec_dma_sync_sg
(paren
r_struct
id|device
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|machvec_tlb_migrate_finish
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
macro_line|# if defined (CONFIG_IA64_HP_SIM)
macro_line|#  include &lt;asm/machvec_hpsim.h&gt;
macro_line|# elif defined (CONFIG_IA64_DIG)
macro_line|#  include &lt;asm/machvec_dig.h&gt;
macro_line|# elif defined (CONFIG_IA64_HP_ZX1)
macro_line|#  include &lt;asm/machvec_hpzx1.h&gt;
macro_line|# elif defined (CONFIG_IA64_HP_ZX1_SWIOTLB)
macro_line|#  include &lt;asm/machvec_hpzx1_swiotlb.h&gt;
macro_line|# elif defined (CONFIG_IA64_SGI_SN2)
macro_line|#  include &lt;asm/machvec_sn2.h&gt;
macro_line|# elif defined (CONFIG_IA64_GENERIC)
macro_line|# ifdef MACHVEC_PLATFORM_HEADER
macro_line|#  include MACHVEC_PLATFORM_HEADER
macro_line|# else
DECL|macro|platform_name
macro_line|#  define platform_name&t;&t;ia64_mv.name
DECL|macro|platform_setup
macro_line|#  define platform_setup&t;ia64_mv.setup
DECL|macro|platform_cpu_init
macro_line|#  define platform_cpu_init&t;ia64_mv.cpu_init
DECL|macro|platform_irq_init
macro_line|#  define platform_irq_init&t;ia64_mv.irq_init
DECL|macro|platform_send_ipi
macro_line|#  define platform_send_ipi&t;ia64_mv.send_ipi
DECL|macro|platform_timer_interrupt
macro_line|#  define platform_timer_interrupt&t;ia64_mv.timer_interrupt
DECL|macro|platform_global_tlb_purge
macro_line|#  define platform_global_tlb_purge&t;ia64_mv.global_tlb_purge
DECL|macro|platform_tlb_migrate_finish
macro_line|#  define platform_tlb_migrate_finish&t;ia64_mv.tlb_migrate_finish
DECL|macro|platform_dma_init
macro_line|#  define platform_dma_init&t;&t;ia64_mv.dma_init
DECL|macro|platform_dma_alloc_coherent
macro_line|#  define platform_dma_alloc_coherent&t;ia64_mv.dma_alloc_coherent
DECL|macro|platform_dma_free_coherent
macro_line|#  define platform_dma_free_coherent&t;ia64_mv.dma_free_coherent
DECL|macro|platform_dma_map_single
macro_line|#  define platform_dma_map_single&t;ia64_mv.dma_map_single
DECL|macro|platform_dma_unmap_single
macro_line|#  define platform_dma_unmap_single&t;ia64_mv.dma_unmap_single
DECL|macro|platform_dma_map_sg
macro_line|#  define platform_dma_map_sg&t;&t;ia64_mv.dma_map_sg
DECL|macro|platform_dma_unmap_sg
macro_line|#  define platform_dma_unmap_sg&t;&t;ia64_mv.dma_unmap_sg
DECL|macro|platform_dma_sync_single_for_cpu
macro_line|#  define platform_dma_sync_single_for_cpu ia64_mv.dma_sync_single_for_cpu
DECL|macro|platform_dma_sync_sg_for_cpu
macro_line|#  define platform_dma_sync_sg_for_cpu&t;ia64_mv.dma_sync_sg_for_cpu
DECL|macro|platform_dma_sync_single_for_device
macro_line|#  define platform_dma_sync_single_for_device ia64_mv.dma_sync_single_for_device
DECL|macro|platform_dma_sync_sg_for_device
macro_line|#  define platform_dma_sync_sg_for_device ia64_mv.dma_sync_sg_for_device
DECL|macro|platform_dma_mapping_error
macro_line|#  define platform_dma_mapping_error&t;&t;ia64_mv.dma_mapping_error
DECL|macro|platform_dma_supported
macro_line|#  define platform_dma_supported&t;ia64_mv.dma_supported
DECL|macro|platform_irq_desc
macro_line|#  define platform_irq_desc&t;&t;ia64_mv.irq_desc
DECL|macro|platform_irq_to_vector
macro_line|#  define platform_irq_to_vector&t;ia64_mv.irq_to_vector
DECL|macro|platform_local_vector_to_irq
macro_line|#  define platform_local_vector_to_irq&t;ia64_mv.local_vector_to_irq
DECL|macro|platform_inb
macro_line|#  define platform_inb&t;&t;ia64_mv.inb
DECL|macro|platform_inw
macro_line|#  define platform_inw&t;&t;ia64_mv.inw
DECL|macro|platform_inl
macro_line|#  define platform_inl&t;&t;ia64_mv.inl
DECL|macro|platform_outb
macro_line|#  define platform_outb&t;&t;ia64_mv.outb
DECL|macro|platform_outw
macro_line|#  define platform_outw&t;&t;ia64_mv.outw
DECL|macro|platform_outl
macro_line|#  define platform_outl&t;&t;ia64_mv.outl
DECL|macro|platform_mmiowb
macro_line|#  define platform_mmiowb&t;ia64_mv.mmiowb
DECL|macro|platform_readb
macro_line|#  define platform_readb        ia64_mv.readb
DECL|macro|platform_readw
macro_line|#  define platform_readw        ia64_mv.readw
DECL|macro|platform_readl
macro_line|#  define platform_readl        ia64_mv.readl
DECL|macro|platform_readq
macro_line|#  define platform_readq        ia64_mv.readq
DECL|macro|platform_readb_relaxed
macro_line|#  define platform_readb_relaxed        ia64_mv.readb_relaxed
DECL|macro|platform_readw_relaxed
macro_line|#  define platform_readw_relaxed        ia64_mv.readw_relaxed
DECL|macro|platform_readl_relaxed
macro_line|#  define platform_readl_relaxed        ia64_mv.readl_relaxed
DECL|macro|platform_readq_relaxed
macro_line|#  define platform_readq_relaxed        ia64_mv.readq_relaxed
macro_line|# endif
multiline_comment|/* __attribute__((__aligned__(16))) is required to make size of the&n; * structure multiple of 16 bytes.&n; * This will fillup the holes created because of section 3.3.1 in&n; * Software Conventions guide.&n; */
DECL|struct|ia64_machine_vector
r_struct
id|ia64_machine_vector
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|setup
id|ia64_mv_setup_t
op_star
id|setup
suffix:semicolon
DECL|member|cpu_init
id|ia64_mv_cpu_init_t
op_star
id|cpu_init
suffix:semicolon
DECL|member|irq_init
id|ia64_mv_irq_init_t
op_star
id|irq_init
suffix:semicolon
DECL|member|send_ipi
id|ia64_mv_send_ipi_t
op_star
id|send_ipi
suffix:semicolon
DECL|member|timer_interrupt
id|ia64_mv_timer_interrupt_t
op_star
id|timer_interrupt
suffix:semicolon
DECL|member|global_tlb_purge
id|ia64_mv_global_tlb_purge_t
op_star
id|global_tlb_purge
suffix:semicolon
DECL|member|tlb_migrate_finish
id|ia64_mv_tlb_migrate_finish_t
op_star
id|tlb_migrate_finish
suffix:semicolon
DECL|member|dma_init
id|ia64_mv_dma_init
op_star
id|dma_init
suffix:semicolon
DECL|member|dma_alloc_coherent
id|ia64_mv_dma_alloc_coherent
op_star
id|dma_alloc_coherent
suffix:semicolon
DECL|member|dma_free_coherent
id|ia64_mv_dma_free_coherent
op_star
id|dma_free_coherent
suffix:semicolon
DECL|member|dma_map_single
id|ia64_mv_dma_map_single
op_star
id|dma_map_single
suffix:semicolon
DECL|member|dma_unmap_single
id|ia64_mv_dma_unmap_single
op_star
id|dma_unmap_single
suffix:semicolon
DECL|member|dma_map_sg
id|ia64_mv_dma_map_sg
op_star
id|dma_map_sg
suffix:semicolon
DECL|member|dma_unmap_sg
id|ia64_mv_dma_unmap_sg
op_star
id|dma_unmap_sg
suffix:semicolon
DECL|member|dma_sync_single_for_cpu
id|ia64_mv_dma_sync_single_for_cpu
op_star
id|dma_sync_single_for_cpu
suffix:semicolon
DECL|member|dma_sync_sg_for_cpu
id|ia64_mv_dma_sync_sg_for_cpu
op_star
id|dma_sync_sg_for_cpu
suffix:semicolon
DECL|member|dma_sync_single_for_device
id|ia64_mv_dma_sync_single_for_device
op_star
id|dma_sync_single_for_device
suffix:semicolon
DECL|member|dma_sync_sg_for_device
id|ia64_mv_dma_sync_sg_for_device
op_star
id|dma_sync_sg_for_device
suffix:semicolon
DECL|member|dma_mapping_error
id|ia64_mv_dma_mapping_error
op_star
id|dma_mapping_error
suffix:semicolon
DECL|member|dma_supported
id|ia64_mv_dma_supported
op_star
id|dma_supported
suffix:semicolon
DECL|member|irq_desc
id|ia64_mv_irq_desc
op_star
id|irq_desc
suffix:semicolon
DECL|member|irq_to_vector
id|ia64_mv_irq_to_vector
op_star
id|irq_to_vector
suffix:semicolon
DECL|member|local_vector_to_irq
id|ia64_mv_local_vector_to_irq
op_star
id|local_vector_to_irq
suffix:semicolon
DECL|member|inb
id|ia64_mv_inb_t
op_star
id|inb
suffix:semicolon
DECL|member|inw
id|ia64_mv_inw_t
op_star
id|inw
suffix:semicolon
DECL|member|inl
id|ia64_mv_inl_t
op_star
id|inl
suffix:semicolon
DECL|member|outb
id|ia64_mv_outb_t
op_star
id|outb
suffix:semicolon
DECL|member|outw
id|ia64_mv_outw_t
op_star
id|outw
suffix:semicolon
DECL|member|outl
id|ia64_mv_outl_t
op_star
id|outl
suffix:semicolon
DECL|member|mmiowb
id|ia64_mv_mmiowb_t
op_star
id|mmiowb
suffix:semicolon
DECL|member|readb
id|ia64_mv_readb_t
op_star
id|readb
suffix:semicolon
DECL|member|readw
id|ia64_mv_readw_t
op_star
id|readw
suffix:semicolon
DECL|member|readl
id|ia64_mv_readl_t
op_star
id|readl
suffix:semicolon
DECL|member|readq
id|ia64_mv_readq_t
op_star
id|readq
suffix:semicolon
DECL|member|readb_relaxed
id|ia64_mv_readb_relaxed_t
op_star
id|readb_relaxed
suffix:semicolon
DECL|member|readw_relaxed
id|ia64_mv_readw_relaxed_t
op_star
id|readw_relaxed
suffix:semicolon
DECL|member|readl_relaxed
id|ia64_mv_readl_relaxed_t
op_star
id|readl_relaxed
suffix:semicolon
DECL|member|readq_relaxed
id|ia64_mv_readq_relaxed_t
op_star
id|readq_relaxed
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* align attrib? see above comment */
DECL|macro|MACHVEC_INIT
mdefine_line|#define MACHVEC_INIT(name)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;#name,&t;&t;&t;&t;&t;&bslash;&n;&t;platform_setup,&t;&t;&t;&t;&bslash;&n;&t;platform_cpu_init,&t;&t;&t;&bslash;&n;&t;platform_irq_init,&t;&t;&t;&bslash;&n;&t;platform_send_ipi,&t;&t;&t;&bslash;&n;&t;platform_timer_interrupt,&t;&t;&bslash;&n;&t;platform_global_tlb_purge,&t;&t;&bslash;&n;&t;platform_tlb_migrate_finish,&t;&t;&bslash;&n;&t;platform_dma_init,&t;&t;&t;&bslash;&n;&t;platform_dma_alloc_coherent,&t;&t;&bslash;&n;&t;platform_dma_free_coherent,&t;&t;&bslash;&n;&t;platform_dma_map_single,&t;&t;&bslash;&n;&t;platform_dma_unmap_single,&t;&t;&bslash;&n;&t;platform_dma_map_sg,&t;&t;&t;&bslash;&n;&t;platform_dma_unmap_sg,&t;&t;&t;&bslash;&n;&t;platform_dma_sync_single_for_cpu,&t;&bslash;&n;&t;platform_dma_sync_sg_for_cpu,&t;&t;&bslash;&n;&t;platform_dma_sync_single_for_device,&t;&bslash;&n;&t;platform_dma_sync_sg_for_device,&t;&bslash;&n;&t;platform_dma_mapping_error,&t;&t;&t;&bslash;&n;&t;platform_dma_supported,&t;&t;&t;&bslash;&n;&t;platform_irq_desc,&t;&t;&t;&bslash;&n;&t;platform_irq_to_vector,&t;&t;&t;&bslash;&n;&t;platform_local_vector_to_irq,&t;&t;&bslash;&n;&t;platform_inb,&t;&t;&t;&t;&bslash;&n;&t;platform_inw,&t;&t;&t;&t;&bslash;&n;&t;platform_inl,&t;&t;&t;&t;&bslash;&n;&t;platform_outb,&t;&t;&t;&t;&bslash;&n;&t;platform_outw,&t;&t;&t;&t;&bslash;&n;&t;platform_outl,&t;&t;&t;&t;&bslash;&n;&t;platform_mmiowb,&t;&t;&t;&bslash;&n;&t;platform_readb,&t;&t;&t;&t;&bslash;&n;&t;platform_readw,&t;&t;&t;&t;&bslash;&n;&t;platform_readl,&t;&t;&t;&t;&bslash;&n;&t;platform_readq,&t;&t;&t;&t;&bslash;&n;&t;platform_readb_relaxed,&t;&t;&t;&bslash;&n;&t;platform_readw_relaxed,&t;&t;&t;&bslash;&n;&t;platform_readl_relaxed,&t;&t;&t;&bslash;&n;&t;platform_readq_relaxed,&t;&t;&t;&bslash;&n;}
r_extern
r_struct
id|ia64_machine_vector
id|ia64_mv
suffix:semicolon
r_extern
r_void
id|machvec_init
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|# else
macro_line|#  error Unknown configuration.  Update asm-ia64/machvec.h.
macro_line|# endif /* CONFIG_IA64_GENERIC */
multiline_comment|/*&n; * Declare default routines which aren&squot;t declared anywhere else:&n; */
r_extern
id|ia64_mv_dma_init
id|swiotlb_init
suffix:semicolon
r_extern
id|ia64_mv_dma_alloc_coherent
id|swiotlb_alloc_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_free_coherent
id|swiotlb_free_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_map_single
id|swiotlb_map_single
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_single
id|swiotlb_unmap_single
suffix:semicolon
r_extern
id|ia64_mv_dma_map_sg
id|swiotlb_map_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_sg
id|swiotlb_unmap_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_single_for_cpu
id|swiotlb_sync_single_for_cpu
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_sg_for_cpu
id|swiotlb_sync_sg_for_cpu
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_single_for_device
id|swiotlb_sync_single_for_device
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_sg_for_device
id|swiotlb_sync_sg_for_device
suffix:semicolon
r_extern
id|ia64_mv_dma_mapping_error
id|swiotlb_dma_mapping_error
suffix:semicolon
r_extern
id|ia64_mv_dma_supported
id|swiotlb_dma_supported
suffix:semicolon
multiline_comment|/*&n; * Define default versions so we can extend machvec for new platforms without having&n; * to update the machvec files for all existing platforms.&n; */
macro_line|#ifndef platform_setup
DECL|macro|platform_setup
macro_line|# define platform_setup&t;&t;&t;machvec_setup
macro_line|#endif
macro_line|#ifndef platform_cpu_init
DECL|macro|platform_cpu_init
macro_line|# define platform_cpu_init&t;&t;machvec_noop
macro_line|#endif
macro_line|#ifndef platform_irq_init
DECL|macro|platform_irq_init
macro_line|# define platform_irq_init&t;&t;machvec_noop
macro_line|#endif
macro_line|#ifndef platform_send_ipi
DECL|macro|platform_send_ipi
macro_line|# define platform_send_ipi&t;&t;ia64_send_ipi&t;/* default to architected version */
macro_line|#endif
macro_line|#ifndef platform_timer_interrupt
DECL|macro|platform_timer_interrupt
macro_line|# define platform_timer_interrupt &t;machvec_timer_interrupt
macro_line|#endif
macro_line|#ifndef platform_global_tlb_purge
DECL|macro|platform_global_tlb_purge
macro_line|# define platform_global_tlb_purge&t;ia64_global_tlb_purge /* default to architected version */
macro_line|#endif
macro_line|#ifndef platform_tlb_migrate_finish
DECL|macro|platform_tlb_migrate_finish
macro_line|# define platform_tlb_migrate_finish&t;machvec_noop_mm
macro_line|#endif
macro_line|#ifndef platform_dma_init
DECL|macro|platform_dma_init
macro_line|# define platform_dma_init&t;&t;swiotlb_init
macro_line|#endif
macro_line|#ifndef platform_dma_alloc_coherent
DECL|macro|platform_dma_alloc_coherent
macro_line|# define platform_dma_alloc_coherent&t;swiotlb_alloc_coherent
macro_line|#endif
macro_line|#ifndef platform_dma_free_coherent
DECL|macro|platform_dma_free_coherent
macro_line|# define platform_dma_free_coherent&t;swiotlb_free_coherent
macro_line|#endif
macro_line|#ifndef platform_dma_map_single
DECL|macro|platform_dma_map_single
macro_line|# define platform_dma_map_single&t;swiotlb_map_single
macro_line|#endif
macro_line|#ifndef platform_dma_unmap_single
DECL|macro|platform_dma_unmap_single
macro_line|# define platform_dma_unmap_single&t;swiotlb_unmap_single
macro_line|#endif
macro_line|#ifndef platform_dma_map_sg
DECL|macro|platform_dma_map_sg
macro_line|# define platform_dma_map_sg&t;&t;swiotlb_map_sg
macro_line|#endif
macro_line|#ifndef platform_dma_unmap_sg
DECL|macro|platform_dma_unmap_sg
macro_line|# define platform_dma_unmap_sg&t;&t;swiotlb_unmap_sg
macro_line|#endif
macro_line|#ifndef platform_dma_sync_single_for_cpu
DECL|macro|platform_dma_sync_single_for_cpu
macro_line|# define platform_dma_sync_single_for_cpu&t;swiotlb_sync_single_for_cpu
macro_line|#endif
macro_line|#ifndef platform_dma_sync_sg_for_cpu
DECL|macro|platform_dma_sync_sg_for_cpu
macro_line|# define platform_dma_sync_sg_for_cpu&t;&t;swiotlb_sync_sg_for_cpu
macro_line|#endif
macro_line|#ifndef platform_dma_sync_single_for_device
DECL|macro|platform_dma_sync_single_for_device
macro_line|# define platform_dma_sync_single_for_device&t;swiotlb_sync_single_for_device
macro_line|#endif
macro_line|#ifndef platform_dma_sync_sg_for_device
DECL|macro|platform_dma_sync_sg_for_device
macro_line|# define platform_dma_sync_sg_for_device&t;swiotlb_sync_sg_for_device
macro_line|#endif
macro_line|#ifndef platform_dma_mapping_error
DECL|macro|platform_dma_mapping_error
macro_line|# define platform_dma_mapping_error&t;&t;swiotlb_dma_mapping_error
macro_line|#endif
macro_line|#ifndef platform_dma_supported
DECL|macro|platform_dma_supported
macro_line|# define  platform_dma_supported&t;swiotlb_dma_supported
macro_line|#endif
macro_line|#ifndef platform_irq_desc
DECL|macro|platform_irq_desc
macro_line|# define platform_irq_desc&t;&t;__ia64_irq_desc
macro_line|#endif
macro_line|#ifndef platform_irq_to_vector
DECL|macro|platform_irq_to_vector
macro_line|# define platform_irq_to_vector&t;&t;__ia64_irq_to_vector
macro_line|#endif
macro_line|#ifndef platform_local_vector_to_irq
DECL|macro|platform_local_vector_to_irq
macro_line|# define platform_local_vector_to_irq&t;__ia64_local_vector_to_irq
macro_line|#endif
macro_line|#ifndef platform_inb
DECL|macro|platform_inb
macro_line|# define platform_inb&t;&t;__ia64_inb
macro_line|#endif
macro_line|#ifndef platform_inw
DECL|macro|platform_inw
macro_line|# define platform_inw&t;&t;__ia64_inw
macro_line|#endif
macro_line|#ifndef platform_inl
DECL|macro|platform_inl
macro_line|# define platform_inl&t;&t;__ia64_inl
macro_line|#endif
macro_line|#ifndef platform_outb
DECL|macro|platform_outb
macro_line|# define platform_outb&t;&t;__ia64_outb
macro_line|#endif
macro_line|#ifndef platform_outw
DECL|macro|platform_outw
macro_line|# define platform_outw&t;&t;__ia64_outw
macro_line|#endif
macro_line|#ifndef platform_outl
DECL|macro|platform_outl
macro_line|# define platform_outl&t;&t;__ia64_outl
macro_line|#endif
macro_line|#ifndef platform_mmiowb
DECL|macro|platform_mmiowb
macro_line|# define platform_mmiowb&t;__ia64_mmiowb
macro_line|#endif
macro_line|#ifndef platform_readb
DECL|macro|platform_readb
macro_line|# define platform_readb&t;&t;__ia64_readb
macro_line|#endif
macro_line|#ifndef platform_readw
DECL|macro|platform_readw
macro_line|# define platform_readw&t;&t;__ia64_readw
macro_line|#endif
macro_line|#ifndef platform_readl
DECL|macro|platform_readl
macro_line|# define platform_readl&t;&t;__ia64_readl
macro_line|#endif
macro_line|#ifndef platform_readq
DECL|macro|platform_readq
macro_line|# define platform_readq&t;&t;__ia64_readq
macro_line|#endif
macro_line|#ifndef platform_readb_relaxed
DECL|macro|platform_readb_relaxed
macro_line|# define platform_readb_relaxed&t;__ia64_readb_relaxed
macro_line|#endif
macro_line|#ifndef platform_readw_relaxed
DECL|macro|platform_readw_relaxed
macro_line|# define platform_readw_relaxed&t;__ia64_readw_relaxed
macro_line|#endif
macro_line|#ifndef platform_readl_relaxed
DECL|macro|platform_readl_relaxed
macro_line|# define platform_readl_relaxed&t;__ia64_readl_relaxed
macro_line|#endif
macro_line|#ifndef platform_readq_relaxed
DECL|macro|platform_readq_relaxed
macro_line|# define platform_readq_relaxed&t;__ia64_readq_relaxed
macro_line|#endif
macro_line|#endif /* _ASM_IA64_MACHVEC_H */
eof
