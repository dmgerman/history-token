multiline_comment|/*&n; * This file contains the HP SKI Simulator PMU register description tables&n; * and pmc checkers used by perfmon.c.&n; *&n; * Copyright (C) 2002-2003  Hewlett Packard Co&n; *               Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * File mostly contributed by Ian Wienand &lt;ianw@gelato.unsw.edu.au&gt;&n; *&n; * This file is included as a dummy template so the kernel does not&n; * try to initalize registers the simulator can&squot;t handle.&n; *&n; * Note the simulator does not (currently) implement these registers, i.e.,&n; * they do not count anything. But you can read/write them.&n; */
DECL|macro|RDEP
mdefine_line|#define RDEP(x)&t;(1UL&lt;&lt;(x))
macro_line|#ifndef CONFIG_IA64_HP_SIM
macro_line|#error &quot;This file should only be included for the HP Simulator&quot;
macro_line|#endif
DECL|variable|pfm_hpsim_pmc_desc
r_static
id|pfm_reg_desc_t
id|pfm_hpsim_pmc_desc
(braket
id|PMU_MAX_PMCS
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|pfm_hpsim_pmd_desc
r_static
id|pfm_reg_desc_t
id|pfm_hpsim_pmd_desc
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
