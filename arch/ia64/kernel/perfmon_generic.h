DECL|macro|RDEP
mdefine_line|#define RDEP(x)&t;(1UL&lt;&lt;(x))
macro_line|#if defined(CONFIG_ITANIUM) || defined(CONFIG_MCKINLEY)
macro_line|#error &quot;This file should only be used when CONFIG_ITANIUM and CONFIG_MCKINLEY are not defined&quot;
macro_line|#endif
DECL|variable|pmc_desc
r_static
id|pfm_reg_desc_t
id|pmc_desc
(braket
id|PMU_MAX_PMCS
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|pmd_desc
r_static
id|pfm_reg_desc_t
id|pmd_desc
(braket
id|PMU_MAX_PMDS
)braket
op_assign
initialization_block
suffix:semicolon
eof
