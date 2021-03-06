macro_line|#ifndef _ALPHA_AGP_BACKEND_H
DECL|macro|_ALPHA_AGP_BACKEND_H
mdefine_line|#define _ALPHA_AGP_BACKEND_H 1
DECL|union|_alpha_agp_mode
r_typedef
r_union
id|_alpha_agp_mode
(brace
r_struct
(brace
DECL|member|rate
id|u32
id|rate
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved0
id|u32
id|reserved0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fw
id|u32
id|fw
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fourgb
id|u32
id|fourgb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|u32
id|reserved1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|enable
id|u32
id|enable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sba
id|u32
id|sba
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:colon
l_int|14
suffix:semicolon
DECL|member|rq
id|u32
id|rq
suffix:colon
l_int|8
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|lw
id|u32
id|lw
suffix:semicolon
DECL|typedef|alpha_agp_mode
)brace
id|alpha_agp_mode
suffix:semicolon
DECL|struct|_alpha_agp_info
r_typedef
r_struct
id|_alpha_agp_info
(brace
DECL|member|hose
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_struct
(brace
DECL|member|bus_base
id|dma_addr_t
id|bus_base
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|sysdata
r_void
op_star
id|sysdata
suffix:semicolon
DECL|member|aperture
)brace
id|aperture
suffix:semicolon
DECL|member|capability
id|alpha_agp_mode
id|capability
suffix:semicolon
DECL|member|mode
id|alpha_agp_mode
id|mode
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|ops
r_struct
id|alpha_agp_ops
op_star
id|ops
suffix:semicolon
DECL|typedef|alpha_agp_info
)brace
id|alpha_agp_info
suffix:semicolon
DECL|struct|alpha_agp_ops
r_struct
id|alpha_agp_ops
(brace
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
id|alpha_agp_info
op_star
)paren
suffix:semicolon
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
id|alpha_agp_info
op_star
)paren
suffix:semicolon
DECL|member|configure
r_int
(paren
op_star
id|configure
)paren
(paren
id|alpha_agp_info
op_star
)paren
suffix:semicolon
DECL|member|bind
r_int
(paren
op_star
id|bind
)paren
(paren
id|alpha_agp_info
op_star
comma
id|off_t
comma
r_struct
id|agp_memory
op_star
)paren
suffix:semicolon
DECL|member|unbind
r_int
(paren
op_star
id|unbind
)paren
(paren
id|alpha_agp_info
op_star
comma
id|off_t
comma
r_struct
id|agp_memory
op_star
)paren
suffix:semicolon
DECL|member|translate
r_int
r_int
(paren
op_star
id|translate
)paren
(paren
id|alpha_agp_info
op_star
comma
id|dma_addr_t
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ALPHA_AGP_BACKEND_H */
eof
