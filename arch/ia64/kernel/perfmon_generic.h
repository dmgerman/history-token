multiline_comment|/*&n; * This file contains the generic PMU register description tables&n; * and pmc checker used by perfmon.c.&n; *&n; * Copyright (C) 2002-2003  Hewlett Packard Co&n; *               Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
DECL|macro|RDEP
mdefine_line|#define RDEP(x)&t;(1UL&lt;&lt;(x))
macro_line|#if defined(CONFIG_ITANIUM) || defined (CONFIG_MCKINLEY)
macro_line|#error &quot;This file should not be used when CONFIG_ITANIUM or CONFIG_MCKINLEY is defined&quot;
macro_line|#endif
DECL|variable|pmc_gen_desc
r_static
id|pfm_reg_desc_t
id|pmc_gen_desc
(braket
id|PMU_MAX_PMCS
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|pmd_gen_desc
r_static
id|pfm_reg_desc_t
id|pmd_gen_desc
(braket
id|PMU_MAX_PMDS
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/*&n; * impl_pmcs, impl_pmds are computed at runtime to minimize errors!&n; */
DECL|variable|pmu_conf
r_static
id|pmu_config_t
id|pmu_conf
op_assign
initialization_block
suffix:semicolon
eof
