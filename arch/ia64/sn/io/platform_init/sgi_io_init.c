multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
multiline_comment|/*&n; * per_hub_init&n; *&n; * &t;This code is executed once for each Hub chip.&n; */
r_void
DECL|function|per_hub_init
id|per_hub_init
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|nodepda_t
op_star
id|npdap
suffix:semicolon
id|ii_icmr_u_t
id|ii_icmr
suffix:semicolon
id|ii_ibcr_u_t
id|ii_ibcr
suffix:semicolon
id|ii_ilcsr_u_t
id|ii_ilcsr
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|nasid
op_ne
id|INVALID_NASID
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|nasid
)paren
op_eq
id|cnode
)paren
suffix:semicolon
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
suffix:semicolon
multiline_comment|/* Disable the request and reply errors. */
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_IWEIM
comma
l_int|0xC000
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the total number of CRBs that can be used.&n;&t; */
id|ii_icmr.ii_icmr_regval
op_assign
l_int|0x0
suffix:semicolon
id|ii_icmr.ii_icmr_fld_s.i_c_cnt
op_assign
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|enable_shub_wars_1_1
c_func
(paren
)paren
)paren
(brace
singleline_comment|// Set bit one of ICMR to prevent II from sending interrupt for II bug.
id|ii_icmr.ii_icmr_regval
op_or_assign
l_int|0x1
suffix:semicolon
)brace
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ICMR
comma
id|ii_icmr.ii_icmr_regval
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the number of CRBs that both of the BTEs combined&n;&t; * can use minus 1.&n;&t; */
id|ii_ibcr.ii_ibcr_regval
op_assign
l_int|0x0
suffix:semicolon
id|ii_ilcsr.ii_ilcsr_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_LLP_CSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ii_ilcsr.ii_ilcsr_fld_s.i_llp_stat
op_amp
id|LNK_STAT_WORKING
)paren
(brace
id|ii_ibcr.ii_ibcr_fld_s.i_count
op_assign
l_int|0x8
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;     * if the LLP is down, there is no attached I/O, so&n;&t;    * give BTE all the CRBs.&n;&t;    */
id|ii_ibcr.ii_ibcr_fld_s.i_count
op_assign
l_int|0x14
suffix:semicolon
)brace
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_IBCR
comma
id|ii_ibcr.ii_ibcr_regval
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set CRB timeout to be 10ms.&n;&t; */
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ICTP
comma
l_int|0xffffff
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ICTO
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Initialize error interrupts for this hub. */
id|hub_error_init
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
eof
