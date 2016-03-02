macro_line|#ifndef _ASM_IA64_MACHVEC_HPZX1_h
DECL|macro|_ASM_IA64_MACHVEC_HPZX1_h
mdefine_line|#define _ASM_IA64_MACHVEC_HPZX1_h
r_extern
id|ia64_mv_setup_t
id|dig_setup
suffix:semicolon
r_extern
id|ia64_mv_dma_alloc_coherent
id|sba_alloc_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_free_coherent
id|sba_free_coherent
suffix:semicolon
r_extern
id|ia64_mv_dma_map_single
id|sba_map_single
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_single
id|sba_unmap_single
suffix:semicolon
r_extern
id|ia64_mv_dma_map_sg
id|sba_map_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_unmap_sg
id|sba_unmap_sg
suffix:semicolon
r_extern
id|ia64_mv_dma_supported
id|sba_dma_supported
suffix:semicolon
multiline_comment|/*&n; * This stuff has dual use!&n; *&n; * For a generic kernel, the macros are used to initialize the&n; * platform&squot;s machvec structure.  When compiling a non-generic kernel,&n; * the macros are used directly.&n; */
DECL|macro|platform_name
mdefine_line|#define platform_name&t;&t;&t;&quot;hpzx1&quot;
DECL|macro|platform_setup
mdefine_line|#define platform_setup&t;&t;&t;dig_setup
DECL|macro|platform_dma_init
mdefine_line|#define platform_dma_init&t;&t;((ia64_mv_dma_init *) machvec_noop)
DECL|macro|platform_dma_alloc_coherent
mdefine_line|#define platform_dma_alloc_coherent&t;sba_alloc_coherent
DECL|macro|platform_dma_free_coherent
mdefine_line|#define platform_dma_free_coherent&t;sba_free_coherent
DECL|macro|platform_dma_map_single
mdefine_line|#define platform_dma_map_single&t;&t;sba_map_single
DECL|macro|platform_dma_unmap_single
mdefine_line|#define platform_dma_unmap_single&t;sba_unmap_single
DECL|macro|platform_dma_map_sg
mdefine_line|#define platform_dma_map_sg&t;&t;sba_map_sg
DECL|macro|platform_dma_unmap_sg
mdefine_line|#define platform_dma_unmap_sg&t;&t;sba_unmap_sg
DECL|macro|platform_dma_sync_single
mdefine_line|#define platform_dma_sync_single&t;((ia64_mv_dma_sync_single *) machvec_memory_fence)
DECL|macro|platform_dma_sync_sg
mdefine_line|#define platform_dma_sync_sg&t;&t;((ia64_mv_dma_sync_sg *) machvec_memory_fence)
DECL|macro|platform_dma_supported
mdefine_line|#define platform_dma_supported&t;&t;sba_dma_supported
macro_line|#endif /* _ASM_IA64_MACHVEC_HPZX1_h */
eof
