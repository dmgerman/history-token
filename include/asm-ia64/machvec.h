multiline_comment|/*&n; * Machine vector for IA-64.&n; *&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) Srinivasa Thirumalachar &lt;sprasad@engr.sgi.com&gt;&n; * Copyright (C) Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; * Copyright (C) 1999-2001 Hewlett-Packard Co.&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_MACHVEC_H
DECL|macro|_ASM_IA64_MACHVEC_H
mdefine_line|#define _ASM_IA64_MACHVEC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* forward declarations: */
r_struct
id|pci_dev
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
c_func
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
DECL|typedef|ia64_mv_pci_fixup_t
r_typedef
r_void
id|ia64_mv_pci_fixup_t
(paren
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_map_nr_t
r_typedef
r_int
r_int
id|ia64_mv_map_nr_t
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_mca_init_t
r_typedef
r_void
id|ia64_mv_mca_init_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_mca_handler_t
r_typedef
r_void
id|ia64_mv_mca_handler_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_cmci_handler_t
r_typedef
r_void
id|ia64_mv_cmci_handler_t
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
DECL|typedef|ia64_mv_log_print_t
r_typedef
r_void
id|ia64_mv_log_print_t
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
id|u8
)paren
suffix:semicolon
DECL|typedef|ia64_mv_local_vector_to_irq
r_typedef
r_int
r_int
id|ia64_mv_local_vector_to_irq
(paren
id|u8
id|vector
)paren
suffix:semicolon
multiline_comment|/* PCI-DMA interface: */
DECL|typedef|ia64_mv_pci_dma_init
r_typedef
r_void
id|ia64_mv_pci_dma_init
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_pci_alloc_consistent
r_typedef
r_void
op_star
id|ia64_mv_pci_alloc_consistent
(paren
r_struct
id|pci_dev
op_star
comma
r_int
comma
id|dma_addr_t
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_pci_free_consistent
r_typedef
r_void
id|ia64_mv_pci_free_consistent
(paren
r_struct
id|pci_dev
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
DECL|typedef|ia64_mv_pci_map_single
r_typedef
id|dma_addr_t
id|ia64_mv_pci_map_single
(paren
r_struct
id|pci_dev
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
DECL|typedef|ia64_mv_pci_unmap_single
r_typedef
r_void
id|ia64_mv_pci_unmap_single
(paren
r_struct
id|pci_dev
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_pci_map_sg
r_typedef
r_int
id|ia64_mv_pci_map_sg
(paren
r_struct
id|pci_dev
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
DECL|typedef|ia64_mv_pci_unmap_sg
r_typedef
r_void
id|ia64_mv_pci_unmap_sg
(paren
r_struct
id|pci_dev
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
DECL|typedef|ia64_mv_pci_dma_sync_single
r_typedef
r_void
id|ia64_mv_pci_dma_sync_single
(paren
r_struct
id|pci_dev
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_pci_dma_sync_sg
r_typedef
r_void
id|ia64_mv_pci_dma_sync_sg
(paren
r_struct
id|pci_dev
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
DECL|typedef|ia64_mv_pci_dma_address
r_typedef
r_int
r_int
id|ia64_mv_pci_dma_address
(paren
r_struct
id|scatterlist
op_star
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
DECL|typedef|ia64_mv_mmiob_t
r_typedef
r_void
id|ia64_mv_mmiob_t
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|machvec_noop
(paren
r_void
)paren
suffix:semicolon
macro_line|# if defined (CONFIG_IA64_HP_SIM)
macro_line|#  include &lt;asm/machvec_hpsim.h&gt;
macro_line|# elif defined (CONFIG_IA64_DIG)
macro_line|#  include &lt;asm/machvec_dig.h&gt;
macro_line|# elif defined (CONFIG_IA64_SGI_SN1)
macro_line|#  include &lt;asm/machvec_sn1.h&gt;
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
DECL|macro|platform_map_nr
macro_line|#  define platform_map_nr&t;ia64_mv.map_nr
DECL|macro|platform_mca_init
macro_line|#  define platform_mca_init&t;ia64_mv.mca_init
DECL|macro|platform_mca_handler
macro_line|#  define platform_mca_handler&t;ia64_mv.mca_handler
DECL|macro|platform_cmci_handler
macro_line|#  define platform_cmci_handler&t;ia64_mv.cmci_handler
DECL|macro|platform_log_print
macro_line|#  define platform_log_print&t;ia64_mv.log_print
DECL|macro|platform_pci_fixup
macro_line|#  define platform_pci_fixup&t;ia64_mv.pci_fixup
DECL|macro|platform_send_ipi
macro_line|#  define platform_send_ipi&t;ia64_mv.send_ipi
DECL|macro|platform_global_tlb_purge
macro_line|#  define platform_global_tlb_purge&t;ia64_mv.global_tlb_purge
DECL|macro|platform_pci_dma_init
macro_line|#  define platform_pci_dma_init&t;&t;ia64_mv.dma_init
DECL|macro|platform_pci_alloc_consistent
macro_line|#  define platform_pci_alloc_consistent&t;ia64_mv.alloc_consistent
DECL|macro|platform_pci_free_consistent
macro_line|#  define platform_pci_free_consistent&t;ia64_mv.free_consistent
DECL|macro|platform_pci_map_single
macro_line|#  define platform_pci_map_single&t;ia64_mv.map_single
DECL|macro|platform_pci_unmap_single
macro_line|#  define platform_pci_unmap_single&t;ia64_mv.unmap_single
DECL|macro|platform_pci_map_sg
macro_line|#  define platform_pci_map_sg&t;&t;ia64_mv.map_sg
DECL|macro|platform_pci_unmap_sg
macro_line|#  define platform_pci_unmap_sg&t;&t;ia64_mv.unmap_sg
DECL|macro|platform_pci_dma_sync_single
macro_line|#  define platform_pci_dma_sync_single&t;ia64_mv.sync_single
DECL|macro|platform_pci_dma_sync_sg
macro_line|#  define platform_pci_dma_sync_sg&t;ia64_mv.sync_sg
DECL|macro|platform_pci_dma_address
macro_line|#  define platform_pci_dma_address&t;ia64_mv.dma_address
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
DECL|macro|platofrm_mmiob
macro_line|#  define platofrm_mmiob        ia64_mv.mmiob
macro_line|# endif
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
DECL|member|pci_fixup
id|ia64_mv_pci_fixup_t
op_star
id|pci_fixup
suffix:semicolon
DECL|member|map_nr
id|ia64_mv_map_nr_t
op_star
id|map_nr
suffix:semicolon
DECL|member|mca_init
id|ia64_mv_mca_init_t
op_star
id|mca_init
suffix:semicolon
DECL|member|mca_handler
id|ia64_mv_mca_handler_t
op_star
id|mca_handler
suffix:semicolon
DECL|member|cmci_handler
id|ia64_mv_cmci_handler_t
op_star
id|cmci_handler
suffix:semicolon
DECL|member|log_print
id|ia64_mv_log_print_t
op_star
id|log_print
suffix:semicolon
DECL|member|send_ipi
id|ia64_mv_send_ipi_t
op_star
id|send_ipi
suffix:semicolon
DECL|member|dma_init
id|ia64_mv_pci_dma_init
op_star
id|dma_init
suffix:semicolon
DECL|member|alloc_consistent
id|ia64_mv_pci_alloc_consistent
op_star
id|alloc_consistent
suffix:semicolon
DECL|member|free_consistent
id|ia64_mv_pci_free_consistent
op_star
id|free_consistent
suffix:semicolon
DECL|member|map_single
id|ia64_mv_pci_map_single
op_star
id|map_single
suffix:semicolon
DECL|member|unmap_single
id|ia64_mv_pci_unmap_single
op_star
id|unmap_single
suffix:semicolon
DECL|member|map_sg
id|ia64_mv_pci_map_sg
op_star
id|map_sg
suffix:semicolon
DECL|member|unmap_sg
id|ia64_mv_pci_unmap_sg
op_star
id|unmap_sg
suffix:semicolon
DECL|member|sync_single
id|ia64_mv_pci_dma_sync_single
op_star
id|sync_single
suffix:semicolon
DECL|member|sync_sg
id|ia64_mv_pci_dma_sync_sg
op_star
id|sync_sg
suffix:semicolon
DECL|member|dma_address
id|ia64_mv_pci_dma_address
op_star
id|dma_address
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
DECL|member|mmiob
id|ia64_mv_mmiob_t
op_star
id|mmiob
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MACHVEC_INIT
mdefine_line|#define MACHVEC_INIT(name)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;#name,&t;&t;&t;&t;&t;&bslash;&n;&t;platform_setup,&t;&t;&t;&t;&bslash;&n;&t;platform_irq_init,&t;&t;&t;&bslash;&n;&t;platform_pci_fixup,&t;&t;&t;&bslash;&n;&t;platform_map_nr,&t;&t;&t;&bslash;&n;&t;platform_mca_init,&t;&t;&t;&bslash;&n;&t;platform_mca_handler,&t;&t;&t;&bslash;&n;&t;platform_cmci_handler,&t;&t;&t;&bslash;&n;&t;platform_log_print,&t;&t;&t;&bslash;&n;&t;platform_send_ipi,&t;&t;&t;&bslash;&n;&t;platform_global_tlb_purge,&t;&t;&bslash;&n;&t;platform_pci_dma_init,&t;&t;&t;&bslash;&n;&t;platform_pci_alloc_consistent,&t;&t;&bslash;&n;&t;platform_pci_free_consistent,&t;&t;&bslash;&n;&t;platform_pci_map_single,&t;&t;&bslash;&n;&t;platform_pci_unmap_single,&t;&t;&bslash;&n;&t;platform_pci_map_sg,&t;&t;&t;&bslash;&n;&t;platform_pci_unmap_sg,&t;&t;&t;&bslash;&n;&t;platform_pci_dma_sync_single,&t;&t;&bslash;&n;&t;platform_pci_dma_sync_sg,&t;&t;&bslash;&n;&t;platform_pci_dma_address,&t;&t;&bslash;&n;&t;platform_irq_desc,&t;&t;&t;&bslash;&n;&t;platform_irq_to_vector,&t;&t;&t;&bslash;&n;&t;platform_local_vector_to_irq,&t;&t;&bslash;&n;&t;platform_inb,&t;&t;&t;&t;&bslash;&n;&t;platform_inw,&t;&t;&t;&t;&bslash;&n;&t;platform_inl,&t;&t;&t;&t;&bslash;&n;&t;platform_outb,&t;&t;&t;&t;&bslash;&n;&t;platform_outw,&t;&t;&t;&t;&bslash;&n;&t;platform_outl,&t;&t;&t;&t;&bslash;&n;        platform_mmiob                          &bslash;&n;}
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
id|ia64_mv_pci_dma_init
id|swiotlb_init
suffix:semicolon
r_extern
id|ia64_mv_pci_alloc_consistent
id|swiotlb_alloc_consistent
suffix:semicolon
r_extern
id|ia64_mv_pci_free_consistent
id|swiotlb_free_consistent
suffix:semicolon
r_extern
id|ia64_mv_pci_map_single
id|swiotlb_map_single
suffix:semicolon
r_extern
id|ia64_mv_pci_unmap_single
id|swiotlb_unmap_single
suffix:semicolon
r_extern
id|ia64_mv_pci_map_sg
id|swiotlb_map_sg
suffix:semicolon
r_extern
id|ia64_mv_pci_unmap_sg
id|swiotlb_unmap_sg
suffix:semicolon
r_extern
id|ia64_mv_pci_dma_sync_single
id|swiotlb_sync_single
suffix:semicolon
r_extern
id|ia64_mv_pci_dma_sync_sg
id|swiotlb_sync_sg
suffix:semicolon
r_extern
id|ia64_mv_pci_dma_address
id|swiotlb_dma_address
suffix:semicolon
multiline_comment|/*&n; * Define default versions so we can extend machvec for new platforms without having&n; * to update the machvec files for all existing platforms.&n; */
macro_line|#ifndef platform_setup
DECL|macro|platform_setup
macro_line|# define platform_setup&t;&t;((ia64_mv_setup_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_cpu_init
DECL|macro|platform_cpu_init
macro_line|# define platform_cpu_init&t;((ia64_mv_cpu_init_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_irq_init
DECL|macro|platform_irq_init
macro_line|# define platform_irq_init&t;((ia64_mv_irq_init_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_mca_init
DECL|macro|platform_mca_init
macro_line|# define platform_mca_init&t;((ia64_mv_mca_init_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_mca_handler
DECL|macro|platform_mca_handler
macro_line|# define platform_mca_handler&t;((ia64_mv_mca_handler_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_cmci_handler
DECL|macro|platform_cmci_handler
macro_line|# define platform_cmci_handler&t;((ia64_mv_cmci_handler_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_log_print
DECL|macro|platform_log_print
macro_line|# define platform_log_print&t;((ia64_mv_log_print_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_pci_fixup
DECL|macro|platform_pci_fixup
macro_line|# define platform_pci_fixup&t;((ia64_mv_pci_fixup_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_send_ipi
DECL|macro|platform_send_ipi
macro_line|# define platform_send_ipi&t;ia64_send_ipi&t;/* default to architected version */
macro_line|#endif
macro_line|#ifndef platform_global_tlb_purge
DECL|macro|platform_global_tlb_purge
macro_line|# define platform_global_tlb_purge&t;ia64_global_tlb_purge /* default to architected version */
macro_line|#endif
macro_line|#ifndef platform_pci_dma_init
DECL|macro|platform_pci_dma_init
macro_line|# define platform_pci_dma_init&t;&t;swiotlb_init
macro_line|#endif
macro_line|#ifndef platform_pci_alloc_consistent
DECL|macro|platform_pci_alloc_consistent
macro_line|# define platform_pci_alloc_consistent&t;swiotlb_alloc_consistent
macro_line|#endif
macro_line|#ifndef platform_pci_free_consistent
DECL|macro|platform_pci_free_consistent
macro_line|# define platform_pci_free_consistent&t;swiotlb_free_consistent
macro_line|#endif
macro_line|#ifndef platform_pci_map_single
DECL|macro|platform_pci_map_single
macro_line|# define platform_pci_map_single&t;swiotlb_map_single
macro_line|#endif
macro_line|#ifndef platform_pci_unmap_single
DECL|macro|platform_pci_unmap_single
macro_line|# define platform_pci_unmap_single&t;swiotlb_unmap_single
macro_line|#endif
macro_line|#ifndef platform_pci_map_sg
DECL|macro|platform_pci_map_sg
macro_line|# define platform_pci_map_sg&t;&t;swiotlb_map_sg
macro_line|#endif
macro_line|#ifndef platform_pci_unmap_sg
DECL|macro|platform_pci_unmap_sg
macro_line|# define platform_pci_unmap_sg&t;&t;swiotlb_unmap_sg
macro_line|#endif
macro_line|#ifndef platform_pci_dma_sync_single
DECL|macro|platform_pci_dma_sync_single
macro_line|# define platform_pci_dma_sync_single&t;swiotlb_sync_single
macro_line|#endif
macro_line|#ifndef platform_pci_dma_sync_sg
DECL|macro|platform_pci_dma_sync_sg
macro_line|# define platform_pci_dma_sync_sg&t;swiotlb_sync_sg
macro_line|#endif
macro_line|#ifndef platform_pci_dma_address
DECL|macro|platform_pci_dma_address
macro_line|# define  platform_pci_dma_address&t;swiotlb_dma_address
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
macro_line|#ifndef platform_mmiob
DECL|macro|platform_mmiob
macro_line|# define platform_mmiob         __ia64_mmiob
macro_line|#endif
macro_line|#endif /* _ASM_IA64_MACHVEC_H */
eof
