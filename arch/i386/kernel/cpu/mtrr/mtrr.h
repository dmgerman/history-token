multiline_comment|/*&n; * local mtrr defines.&n; */
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE  1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|MTRRcap_MSR
mdefine_line|#define MTRRcap_MSR     0x0fe
DECL|macro|MTRRdefType_MSR
mdefine_line|#define MTRRdefType_MSR 0x2ff
DECL|macro|MTRRphysBase_MSR
mdefine_line|#define MTRRphysBase_MSR(reg) (0x200 + 2 * (reg))
DECL|macro|MTRRphysMask_MSR
mdefine_line|#define MTRRphysMask_MSR(reg) (0x200 + 2 * (reg) + 1)
DECL|macro|NUM_FIXED_RANGES
mdefine_line|#define NUM_FIXED_RANGES 88
DECL|macro|MTRRfix64K_00000_MSR
mdefine_line|#define MTRRfix64K_00000_MSR 0x250
DECL|macro|MTRRfix16K_80000_MSR
mdefine_line|#define MTRRfix16K_80000_MSR 0x258
DECL|macro|MTRRfix16K_A0000_MSR
mdefine_line|#define MTRRfix16K_A0000_MSR 0x259
DECL|macro|MTRRfix4K_C0000_MSR
mdefine_line|#define MTRRfix4K_C0000_MSR 0x268
DECL|macro|MTRRfix4K_C8000_MSR
mdefine_line|#define MTRRfix4K_C8000_MSR 0x269
DECL|macro|MTRRfix4K_D0000_MSR
mdefine_line|#define MTRRfix4K_D0000_MSR 0x26a
DECL|macro|MTRRfix4K_D8000_MSR
mdefine_line|#define MTRRfix4K_D8000_MSR 0x26b
DECL|macro|MTRRfix4K_E0000_MSR
mdefine_line|#define MTRRfix4K_E0000_MSR 0x26c
DECL|macro|MTRRfix4K_E8000_MSR
mdefine_line|#define MTRRfix4K_E8000_MSR 0x26d
DECL|macro|MTRRfix4K_F0000_MSR
mdefine_line|#define MTRRfix4K_F0000_MSR 0x26e
DECL|macro|MTRRfix4K_F8000_MSR
mdefine_line|#define MTRRfix4K_F8000_MSR 0x26f
DECL|macro|MTRR_CHANGE_MASK_FIXED
mdefine_line|#define MTRR_CHANGE_MASK_FIXED     0x01
DECL|macro|MTRR_CHANGE_MASK_VARIABLE
mdefine_line|#define MTRR_CHANGE_MASK_VARIABLE  0x02
DECL|macro|MTRR_CHANGE_MASK_DEFTYPE
mdefine_line|#define MTRR_CHANGE_MASK_DEFTYPE   0x04
multiline_comment|/* In the Intel processor&squot;s MTRR interface, the MTRR type is always held in&n;   an 8 bit field: */
DECL|typedef|mtrr_type
r_typedef
id|u8
id|mtrr_type
suffix:semicolon
DECL|struct|mtrr_ops
r_struct
id|mtrr_ops
(brace
DECL|member|vendor
id|u32
id|vendor
suffix:semicolon
DECL|member|use_intel_if
id|u32
id|use_intel_if
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|set
r_void
(paren
op_star
id|set
)paren
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
id|mtrr_type
id|type
)paren
suffix:semicolon
DECL|member|set_all
r_void
(paren
op_star
id|set_all
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|get
r_void
(paren
op_star
id|get
)paren
(paren
r_int
r_int
id|reg
comma
r_int
r_int
op_star
id|base
comma
r_int
r_int
op_star
id|size
comma
id|mtrr_type
op_star
id|type
)paren
suffix:semicolon
DECL|member|get_free_region
r_int
(paren
op_star
id|get_free_region
)paren
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|validate_add_page
r_int
(paren
op_star
id|validate_add_page
)paren
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
)paren
suffix:semicolon
DECL|member|have_wrcomb
r_int
(paren
op_star
id|have_wrcomb
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|generic_get_free_region
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|generic_init_secondary
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|generic_validate_add_page
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
)paren
suffix:semicolon
r_extern
r_struct
id|mtrr_ops
id|generic_mtrr_ops
suffix:semicolon
r_extern
r_int
id|generic_have_wrcomb
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|positive_have_wrcomb
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* library functions for processor-specific routines */
DECL|struct|set_mtrr_context
r_struct
id|set_mtrr_context
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|deftype_lo
r_int
r_int
id|deftype_lo
suffix:semicolon
DECL|member|deftype_hi
r_int
r_int
id|deftype_hi
suffix:semicolon
DECL|member|cr4val
r_int
r_int
id|cr4val
suffix:semicolon
DECL|member|ccr3
r_int
r_int
id|ccr3
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mtrr_var_range
r_struct
id|mtrr_var_range
(brace
DECL|member|base_lo
r_int
r_int
id|base_lo
suffix:semicolon
DECL|member|base_hi
r_int
r_int
id|base_hi
suffix:semicolon
DECL|member|mask_lo
r_int
r_int
id|mask_lo
suffix:semicolon
DECL|member|mask_hi
r_int
r_int
id|mask_hi
suffix:semicolon
)brace
suffix:semicolon
r_void
id|set_mtrr_done
c_func
(paren
r_struct
id|set_mtrr_context
op_star
id|ctxt
)paren
suffix:semicolon
r_void
id|set_mtrr_cache_disable
c_func
(paren
r_struct
id|set_mtrr_context
op_star
id|ctxt
)paren
suffix:semicolon
r_void
id|set_mtrr_prepare_save
c_func
(paren
r_struct
id|set_mtrr_context
op_star
id|ctxt
)paren
suffix:semicolon
r_void
id|get_mtrr_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_mtrr_ops
c_func
(paren
r_struct
id|mtrr_ops
op_star
id|ops
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t even ask... */
r_extern
r_void
id|compute_ascii
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u32
id|size_or_mask
comma
id|size_and_mask
suffix:semicolon
r_extern
r_struct
id|mtrr_ops
op_star
id|mtrr_if
suffix:semicolon
DECL|macro|is_cpu
mdefine_line|#define is_cpu(vnd)&t;(mtrr_if &amp;&amp; mtrr_if-&gt;vendor == X86_VENDOR_##vnd)
DECL|macro|use_intel
mdefine_line|#define use_intel()&t;(mtrr_if &amp;&amp; mtrr_if-&gt;use_intel_if == 1)
r_extern
r_int
r_int
id|num_var_ranges
suffix:semicolon
r_extern
r_char
op_star
id|mtrr_if_name
(braket
)braket
suffix:semicolon
eof
