multiline_comment|/*&n; * This file contains the McKinley PMU register description tables&n; * and pmc checker used by perfmon.c.&n; *&n; * Copyright (C) 2002-2003  Hewlett Packard Co&n; *               Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
DECL|macro|RDEP
mdefine_line|#define RDEP(x)&t;(1UL&lt;&lt;(x))
macro_line|#ifndef CONFIG_MCKINLEY
macro_line|#error &quot;This file is only valid when CONFIG_MCKINLEY is defined&quot;
macro_line|#endif
r_static
r_int
id|pfm_mck_pmc_check
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
id|pfm_context_t
op_star
id|ctx
comma
r_int
r_int
id|cnum
comma
r_int
r_int
op_star
id|val
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|pfm_write_ibr_dbr
c_func
(paren
r_int
id|mode
comma
id|pfm_context_t
op_star
id|ctx
comma
r_void
op_star
id|arg
comma
r_int
id|count
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|pfm_mck_pmc_desc
r_static
id|pfm_reg_desc_t
id|pfm_mck_pmc_desc
(braket
id|PMU_MAX_PMCS
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|pfm_mck_pmd_desc
r_static
id|pfm_reg_desc_t
id|pfm_mck_pmd_desc
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
multiline_comment|/*&n; * PMC reserved fields must have their power-up values preserved&n; */
r_static
r_int
DECL|function|pfm_mck_reserved
id|pfm_mck_reserved
c_func
(paren
r_int
r_int
id|cnum
comma
r_int
r_int
op_star
id|val
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|tmp1
comma
id|tmp2
comma
id|ival
op_assign
op_star
id|val
suffix:semicolon
multiline_comment|/* remove reserved areas from user value */
id|tmp1
op_assign
id|ival
op_amp
id|PMC_RSVD_MASK
c_func
(paren
id|cnum
)paren
suffix:semicolon
multiline_comment|/* get reserved fields values */
id|tmp2
op_assign
id|PMC_DFL_VAL
c_func
(paren
id|cnum
)paren
op_amp
op_complement
id|PMC_RSVD_MASK
c_func
(paren
id|cnum
)paren
suffix:semicolon
op_star
id|val
op_assign
id|tmp1
op_or
id|tmp2
suffix:semicolon
id|DPRINT
c_func
(paren
(paren
l_string|&quot;pmc[%d]=0x%lx, mask=0x%lx, reset=0x%lx, val=0x%lx&bslash;n&quot;
comma
id|cnum
comma
id|ival
comma
id|PMC_RSVD_MASK
c_func
(paren
id|cnum
)paren
comma
id|PMC_DFL_VAL
c_func
(paren
id|cnum
)paren
comma
op_star
id|val
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * task can be NULL if the context is unloaded&n; */
r_static
r_int
DECL|function|pfm_mck_pmc_check
id|pfm_mck_pmc_check
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
id|pfm_context_t
op_star
id|ctx
comma
r_int
r_int
id|cnum
comma
r_int
r_int
op_star
id|val
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|ret
op_assign
l_int|0
comma
id|check_case1
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|val8
op_assign
l_int|0
comma
id|val14
op_assign
l_int|0
comma
id|val13
op_assign
l_int|0
suffix:semicolon
r_int
id|is_loaded
suffix:semicolon
multiline_comment|/* first preserve the reserved fields */
id|pfm_mck_reserved
c_func
(paren
id|cnum
comma
id|val
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* sanitfy check */
r_if
c_cond
(paren
id|ctx
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|is_loaded
op_assign
id|ctx-&gt;ctx_state
op_eq
id|PFM_CTX_LOADED
op_logical_or
id|ctx-&gt;ctx_state
op_eq
id|PFM_CTX_MASKED
suffix:semicolon
multiline_comment|/*&n;&t; * we must clear the debug registers if pmc13 has a value which enable&n;&t; * memory pipeline event constraints. In this case we need to clear the&n;&t; * the debug registers if they have not yet been accessed. This is required&n;&t; * to avoid picking stale state.&n;&t; * PMC13 is &quot;active&quot; if:&n;&t; * &t;one of the pmc13.cfg_dbrpXX field is different from 0x3&n;&t; * AND&n;&t; * &t;at the corresponding pmc13.ena_dbrpXX is set.&n;&t; *&n;&t; * For now, we just check on cfg_dbrXX != 0x3.&n;&t; */
id|DPRINT
c_func
(paren
(paren
l_string|&quot;cnum=%u val=0x%lx, using_dbreg=%d loaded=%d&bslash;n&quot;
comma
id|cnum
comma
op_star
id|val
comma
id|ctx-&gt;ctx_fl_using_dbreg
comma
id|is_loaded
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnum
op_eq
l_int|13
op_logical_and
id|is_loaded
op_logical_and
(paren
(paren
op_star
id|val
op_amp
l_int|0x18181818UL
)paren
op_ne
l_int|0x18181818UL
)paren
op_logical_and
id|ctx-&gt;ctx_fl_using_dbreg
op_eq
l_int|0
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;pmc[%d]=0x%lx has active pmc13 settings, clearing dbr&bslash;n&quot;
comma
id|cnum
comma
op_star
id|val
)paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t mix debug with perfmon */
r_if
c_cond
(paren
id|task
op_logical_and
(paren
id|task-&gt;thread.flags
op_amp
id|IA64_THREAD_DBG_VALID
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * a count of 0 will mark the debug registers as in use and also&n;&t;&t; * ensure that they are properly cleared.&n;&t;&t; */
id|ret
op_assign
id|pfm_write_ibr_dbr
c_func
(paren
id|PFM_DATA_RR
comma
id|ctx
comma
l_int|NULL
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * we must clear the (instruction) debug registers if any pmc14.ibrpX bit is enabled&n;&t; * before they are (fl_using_dbreg==0) to avoid picking up stale information.&n;&t; */
r_if
c_cond
(paren
id|cnum
op_eq
l_int|14
op_logical_and
id|is_loaded
op_logical_and
(paren
(paren
op_star
id|val
op_amp
l_int|0x2222UL
)paren
op_ne
l_int|0x2222UL
)paren
op_logical_and
id|ctx-&gt;ctx_fl_using_dbreg
op_eq
l_int|0
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;pmc[%d]=0x%lx has active pmc14 settings, clearing ibr&bslash;n&quot;
comma
id|cnum
comma
op_star
id|val
)paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t mix debug with perfmon */
r_if
c_cond
(paren
id|task
op_logical_and
(paren
id|task-&gt;thread.flags
op_amp
id|IA64_THREAD_DBG_VALID
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * a count of 0 will mark the debug registers as in use and also&n;&t;&t; * ensure that they are properly cleared.&n;&t;&t; */
id|ret
op_assign
id|pfm_write_ibr_dbr
c_func
(paren
id|PFM_CODE_RR
comma
id|ctx
comma
l_int|NULL
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cnum
)paren
(brace
r_case
l_int|4
suffix:colon
op_star
id|val
op_or_assign
l_int|1UL
op_lshift
l_int|23
suffix:semicolon
multiline_comment|/* force power enable bit */
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|val8
op_assign
op_star
id|val
suffix:semicolon
id|val13
op_assign
id|ctx-&gt;ctx_pmcs
(braket
l_int|13
)braket
suffix:semicolon
id|val14
op_assign
id|ctx-&gt;ctx_pmcs
(braket
l_int|14
)braket
suffix:semicolon
id|check_case1
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
id|val8
op_assign
id|ctx-&gt;ctx_pmcs
(braket
l_int|8
)braket
suffix:semicolon
id|val13
op_assign
op_star
id|val
suffix:semicolon
id|val14
op_assign
id|ctx-&gt;ctx_pmcs
(braket
l_int|14
)braket
suffix:semicolon
id|check_case1
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
id|val8
op_assign
id|ctx-&gt;ctx_pmcs
(braket
l_int|8
)braket
suffix:semicolon
id|val13
op_assign
id|ctx-&gt;ctx_pmcs
(braket
l_int|13
)braket
suffix:semicolon
id|val14
op_assign
op_star
id|val
suffix:semicolon
id|check_case1
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* check illegal configuration which can produce inconsistencies in tagging&n;&t; * i-side events in L1D and L2 caches&n;&t; */
r_if
c_cond
(paren
id|check_case1
)paren
(brace
id|ret
op_assign
(paren
(paren
id|val13
op_rshift
l_int|45
)paren
op_amp
l_int|0xf
)paren
op_eq
l_int|0
op_logical_and
(paren
(paren
id|val8
op_amp
l_int|0x1
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
(paren
(paren
id|val14
op_rshift
l_int|1
)paren
op_amp
l_int|0x3
)paren
op_eq
l_int|0x2
op_logical_or
(paren
(paren
id|val14
op_rshift
l_int|1
)paren
op_amp
l_int|0x3
)paren
op_eq
l_int|0x0
)paren
op_logical_or
(paren
(paren
(paren
id|val14
op_rshift
l_int|4
)paren
op_amp
l_int|0x3
)paren
op_eq
l_int|0x2
op_logical_or
(paren
(paren
id|val14
op_rshift
l_int|4
)paren
op_amp
l_int|0x3
)paren
op_eq
l_int|0x0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|DPRINT
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;perfmon: failure check_case1&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_return
id|ret
ques
c_cond
op_minus
id|EINVAL
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
