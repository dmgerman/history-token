macro_line|#ifndef _ASM_IA64_MACHVEC_HPZX1_SWIOTLB_h
DECL|macro|_ASM_IA64_MACHVEC_HPZX1_SWIOTLB_h
mdefine_line|#define _ASM_IA64_MACHVEC_HPZX1_SWIOTLB_h
r_extern
id|ia64_mv_setup_t
id|dig_setup
suffix:semicolon
r_extern
id|ia64_mv_dma_init
id|hwsw_init
suffix:semicolon
r_extern
id|ia64_mv_dma_alloc_coherent
id|hwsw_alloc_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_free_coherent
id|hwsw_free_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_map_single
id|hwsw_map_single
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_single
id|hwsw_unmap_single
suffix:semicolon
r_extern
id|ia64_mv_dma_map_sg
id|hwsw_map_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_sg
id|hwsw_unmap_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_supported
id|hwsw_dma_supported
suffix:semicolon
r_extern
id|ia64_mv_dma_mapping_error
id|hwsw_dma_mapping_error
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_single_for_cpu
id|hwsw_sync_single_for_cpu
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_sg_for_cpu
id|hwsw_sync_sg_for_cpu
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_single_for_device
id|hwsw_sync_single_for_device
suffix:semicolon
r_extern
id|ia64_mv_dma_sync_sg_for_device
id|hwsw_sync_sg_for_device
suffix:semicolon
multiline_comment|/*&n; * This stuff has dual use!&n; *&n; * For a generic kernel, the macros are used to initialize the&n; * platform&squot;s machvec structure.  When compiling a non-generic kernel,&n; * the macros are used directly.&n; */
DECL|macro|platform_name
mdefine_line|#define platform_name&t;&t;&t;&t;&quot;hpzx1_swiotlb&quot;
DECL|macro|platform_setup
mdefine_line|#define platform_setup&t;&t;&t;&t;dig_setup
DECL|macro|platform_dma_init
mdefine_line|#define platform_dma_init&t;&t;&t;hwsw_init
DECL|macro|platform_dma_alloc_coherent
mdefine_line|#define platform_dma_alloc_coherent&t;&t;hwsw_alloc_coherent
DECL|macro|platform_dma_free_coherent
mdefine_line|#define platform_dma_free_coherent&t;&t;hwsw_free_coherent
DECL|macro|platform_dma_map_single
mdefine_line|#define platform_dma_map_single&t;&t;&t;hwsw_map_single
DECL|macro|platform_dma_unmap_single
mdefine_line|#define platform_dma_unmap_single&t;&t;hwsw_unmap_single
DECL|macro|platform_dma_map_sg
mdefine_line|#define platform_dma_map_sg&t;&t;&t;hwsw_map_sg
DECL|macro|platform_dma_unmap_sg
mdefine_line|#define platform_dma_unmap_sg&t;&t;&t;hwsw_unmap_sg
DECL|macro|platform_dma_supported
mdefine_line|#define platform_dma_supported&t;&t;&t;hwsw_dma_supported
DECL|macro|platform_dma_mapping_error
mdefine_line|#define platform_dma_mapping_error&t;&t;hwsw_dma_mapping_error
DECL|macro|platform_dma_sync_single_for_cpu
mdefine_line|#define platform_dma_sync_single_for_cpu&t;hwsw_sync_single_for_cpu
DECL|macro|platform_dma_sync_sg_for_cpu
mdefine_line|#define platform_dma_sync_sg_for_cpu&t;&t;hwsw_sync_sg_for_cpu
DECL|macro|platform_dma_sync_single_for_device
mdefine_line|#define platform_dma_sync_single_for_device&t;hwsw_sync_single_for_device
DECL|macro|platform_dma_sync_sg_for_device
mdefine_line|#define platform_dma_sync_sg_for_device&t;&t;hwsw_sync_sg_for_device
macro_line|#endif /* _ASM_IA64_MACHVEC_HPZX1_SWIOTLB_h */
eof
