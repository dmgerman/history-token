multiline_comment|/*&n; * arch/ppc/kernel/ibm440gx_common.c&n; *&n; * PPC440GX system library&n; *&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; * Copyright (c) 2003 Zultys Technologies&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/ibm44x.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;syslib/ibm440gx_common.h&gt;
multiline_comment|/*&n; * Calculate 440GX clocks&n; */
DECL|function|__fix_zero
r_static
r_inline
id|u32
(def_block
id|__fix_zero
c_func
(paren
id|u32
id|v
comma
id|u32
id|def
)paren
(brace
r_return
id|v
ques
c_cond
id|v
suffix:colon
id|def
suffix:semicolon
)brace
)def_block
DECL|function|ibm440gx_get_clocks
r_void
id|__init
id|ibm440gx_get_clocks
c_func
(paren
r_struct
id|ibm44x_clocks
op_star
id|p
comma
r_int
r_int
id|sys_clk
comma
r_int
r_int
id|ser_clk
)paren
(brace
id|u32
id|pllc
op_assign
id|CPR_READ
c_func
(paren
id|DCRN_CPR_PLLC
)paren
suffix:semicolon
id|u32
id|plld
op_assign
id|CPR_READ
c_func
(paren
id|DCRN_CPR_PLLD
)paren
suffix:semicolon
id|u32
id|uart0
op_assign
id|SDR_READ
c_func
(paren
id|DCRN_SDR_UART0
)paren
suffix:semicolon
id|u32
id|uart1
op_assign
id|SDR_READ
c_func
(paren
id|DCRN_SDR_UART1
)paren
suffix:semicolon
multiline_comment|/* Dividers */
id|u32
id|fbdv
op_assign
id|__fix_zero
c_func
(paren
(paren
id|plld
op_rshift
l_int|24
)paren
op_amp
l_int|0x1f
comma
l_int|32
)paren
suffix:semicolon
id|u32
id|fwdva
op_assign
id|__fix_zero
c_func
(paren
(paren
id|plld
op_rshift
l_int|16
)paren
op_amp
l_int|0xf
comma
l_int|16
)paren
suffix:semicolon
id|u32
id|fwdvb
op_assign
id|__fix_zero
c_func
(paren
(paren
id|plld
op_rshift
l_int|8
)paren
op_amp
l_int|7
comma
l_int|8
)paren
suffix:semicolon
id|u32
id|lfbdv
op_assign
id|__fix_zero
c_func
(paren
id|plld
op_amp
l_int|0x3f
comma
l_int|64
)paren
suffix:semicolon
id|u32
id|pradv0
op_assign
id|__fix_zero
c_func
(paren
(paren
id|CPR_READ
c_func
(paren
id|DCRN_CPR_PRIMAD
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|7
comma
l_int|8
)paren
suffix:semicolon
id|u32
id|prbdv0
op_assign
id|__fix_zero
c_func
(paren
(paren
id|CPR_READ
c_func
(paren
id|DCRN_CPR_PRIMBD
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|7
comma
l_int|8
)paren
suffix:semicolon
id|u32
id|opbdv0
op_assign
id|__fix_zero
c_func
(paren
(paren
id|CPR_READ
c_func
(paren
id|DCRN_CPR_OPBD
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|3
comma
l_int|4
)paren
suffix:semicolon
id|u32
id|perdv0
op_assign
id|__fix_zero
c_func
(paren
(paren
id|CPR_READ
c_func
(paren
id|DCRN_CPR_PERD
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|3
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Input clocks for primary dividers */
id|u32
id|clk_a
comma
id|clk_b
suffix:semicolon
r_if
c_cond
(paren
id|pllc
op_amp
l_int|0x40000000
)paren
(brace
id|u32
id|m
suffix:semicolon
multiline_comment|/* Feedback path */
r_switch
c_cond
(paren
(paren
id|pllc
op_rshift
l_int|24
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* PLLOUTx */
id|m
op_assign
(paren
(paren
id|pllc
op_amp
l_int|0x20000000
)paren
ques
c_cond
id|fwdvb
suffix:colon
id|fwdva
)paren
op_star
id|lfbdv
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* CPU */
id|m
op_assign
id|fwdva
op_star
id|pradv0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* PERClk */
id|m
op_assign
id|fwdvb
op_star
id|prbdv0
op_star
id|opbdv0
op_star
id|perdv0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;invalid PLL feedback source&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bypass
suffix:semicolon
)brace
id|m
op_mul_assign
id|fbdv
suffix:semicolon
id|p-&gt;vco
op_assign
id|sys_clk
op_star
id|m
suffix:semicolon
id|clk_a
op_assign
id|p-&gt;vco
op_div
id|fwdva
suffix:semicolon
id|clk_b
op_assign
id|p-&gt;vco
op_div
id|fwdvb
suffix:semicolon
)brace
r_else
(brace
id|bypass
suffix:colon
multiline_comment|/* Bypass system PLL */
id|p-&gt;vco
op_assign
l_int|0
suffix:semicolon
id|clk_a
op_assign
id|clk_b
op_assign
id|sys_clk
suffix:semicolon
)brace
id|p-&gt;cpu
op_assign
id|clk_a
op_div
id|pradv0
suffix:semicolon
id|p-&gt;plb
op_assign
id|clk_b
op_div
id|prbdv0
suffix:semicolon
id|p-&gt;opb
op_assign
id|p-&gt;plb
op_div
id|opbdv0
suffix:semicolon
id|p-&gt;ebc
op_assign
id|p-&gt;opb
op_div
id|perdv0
suffix:semicolon
multiline_comment|/* UARTs clock */
r_if
c_cond
(paren
id|uart0
op_amp
l_int|0x00800000
)paren
id|p-&gt;uart0
op_assign
id|ser_clk
suffix:semicolon
r_else
id|p-&gt;uart0
op_assign
id|p-&gt;plb
op_div
id|__fix_zero
c_func
(paren
id|uart0
op_amp
l_int|0xff
comma
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uart1
op_amp
l_int|0x00800000
)paren
id|p-&gt;uart1
op_assign
id|ser_clk
suffix:semicolon
r_else
id|p-&gt;uart1
op_assign
id|p-&gt;plb
op_div
id|__fix_zero
c_func
(paren
id|uart1
op_amp
l_int|0xff
comma
l_int|256
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable L2 cache (call with IRQs disabled) */
DECL|function|ibm440gx_l2c_enable
r_void
id|__init
(def_block
id|ibm440gx_l2c_enable
c_func
(paren
r_void
)paren
(brace
id|u32
id|r
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Disable SRAM */
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_DPC
comma
id|mfdcr
c_func
(paren
id|DCRN_SRAM0_DPC
)paren
op_amp
op_complement
id|SRAM_DPC_ENABLE
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB0CR
comma
id|mfdcr
c_func
(paren
id|DCRN_SRAM0_SB0CR
)paren
op_amp
op_complement
id|SRAM_SBCR_BU_MASK
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB1CR
comma
id|mfdcr
c_func
(paren
id|DCRN_SRAM0_SB1CR
)paren
op_amp
op_complement
id|SRAM_SBCR_BU_MASK
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB2CR
comma
id|mfdcr
c_func
(paren
id|DCRN_SRAM0_SB2CR
)paren
op_amp
op_complement
id|SRAM_SBCR_BU_MASK
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB3CR
comma
id|mfdcr
c_func
(paren
id|DCRN_SRAM0_SB3CR
)paren
op_amp
op_complement
id|SRAM_SBCR_BU_MASK
)paren
suffix:semicolon
multiline_comment|/* Enable L2_MODE without ICU/DCU */
id|r
op_assign
id|mfdcr
c_func
(paren
id|DCRN_L2C0_CFG
)paren
op_amp
op_complement
(paren
id|L2C_CFG_ICU
op_or
id|L2C_CFG_DCU
op_or
id|L2C_CFG_SS_MASK
)paren
suffix:semicolon
id|r
op_or_assign
id|L2C_CFG_L2M
op_or
id|L2C_CFG_SS_256
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_L2C0_CFG
comma
id|r
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_L2C0_ADDR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Hardware Clear Command */
id|mtdcr
c_func
(paren
id|DCRN_L2C0_CMD
comma
id|L2C_CMD_HCC
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|mfdcr
c_func
(paren
id|DCRN_L2C0_SR
)paren
op_amp
id|L2C_SR_CC
)paren
)paren
suffix:semicolon
multiline_comment|/* Clear Cache Parity and Tag Errors */
id|mtdcr
c_func
(paren
id|DCRN_L2C0_CMD
comma
id|L2C_CMD_CCP
op_or
id|L2C_CMD_CTE
)paren
suffix:semicolon
multiline_comment|/* Enable 64G snoop region starting at 0 */
id|r
op_assign
id|mfdcr
c_func
(paren
id|DCRN_L2C0_SNP0
)paren
op_amp
op_complement
(paren
id|L2C_SNP_BA_MASK
op_or
id|L2C_SNP_SSR_MASK
)paren
suffix:semicolon
id|r
op_or_assign
id|L2C_SNP_SSR_32G
op_or
id|L2C_SNP_ESR
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_L2C0_SNP0
comma
id|r
)paren
suffix:semicolon
id|r
op_assign
id|mfdcr
c_func
(paren
id|DCRN_L2C0_SNP1
)paren
op_amp
op_complement
(paren
id|L2C_SNP_BA_MASK
op_or
id|L2C_SNP_SSR_MASK
)paren
suffix:semicolon
id|r
op_or_assign
l_int|0x80000000
op_or
id|L2C_SNP_SSR_32G
op_or
id|L2C_SNP_ESR
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_L2C0_SNP1
comma
id|r
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Enable ICU/DCU ports */
id|r
op_assign
id|mfdcr
c_func
(paren
id|DCRN_L2C0_CFG
)paren
suffix:semicolon
id|r
op_and_assign
op_complement
(paren
id|L2C_CFG_DCW_MASK
op_or
id|L2C_CFG_CPIM
op_or
id|L2C_CFG_TPIM
op_or
id|L2C_CFG_LIM
op_or
id|L2C_CFG_PMUX_MASK
op_or
id|L2C_CFG_PMIM
op_or
id|L2C_CFG_TPEI
op_or
id|L2C_CFG_CPEI
op_or
id|L2C_CFG_NAM
op_or
id|L2C_CFG_NBRM
)paren
suffix:semicolon
id|r
op_or_assign
id|L2C_CFG_ICU
op_or
id|L2C_CFG_DCU
op_or
id|L2C_CFG_TPC
op_or
id|L2C_CFG_CPC
op_or
id|L2C_CFG_FRAN
op_or
id|L2C_CFG_SMCM
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_L2C0_CFG
comma
id|r
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync; isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
)def_block
multiline_comment|/* Disable L2 cache (call with IRQs disabled) */
DECL|function|ibm440gx_l2c_disable
r_void
id|__init
(def_block
id|ibm440gx_l2c_disable
c_func
(paren
r_void
)paren
(brace
id|u32
id|r
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Disable L2C mode */
id|r
op_assign
id|mfdcr
c_func
(paren
id|DCRN_L2C0_CFG
)paren
op_amp
op_complement
(paren
id|L2C_CFG_L2M
op_or
id|L2C_CFG_ICU
op_or
id|L2C_CFG_DCU
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_L2C0_CFG
comma
id|r
)paren
suffix:semicolon
multiline_comment|/* Enable SRAM */
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_DPC
comma
id|mfdcr
c_func
(paren
id|DCRN_SRAM0_DPC
)paren
op_or
id|SRAM_DPC_ENABLE
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB0CR
comma
id|SRAM_SBCR_BAS0
op_or
id|SRAM_SBCR_BS_64KB
op_or
id|SRAM_SBCR_BU_RW
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB1CR
comma
id|SRAM_SBCR_BAS1
op_or
id|SRAM_SBCR_BS_64KB
op_or
id|SRAM_SBCR_BU_RW
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB2CR
comma
id|SRAM_SBCR_BAS2
op_or
id|SRAM_SBCR_BS_64KB
op_or
id|SRAM_SBCR_BU_RW
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_SRAM0_SB3CR
comma
id|SRAM_SBCR_BAS3
op_or
id|SRAM_SBCR_BS_64KB
op_or
id|SRAM_SBCR_BU_RW
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync; isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
)def_block
DECL|function|ibm440gx_l2c_setup
r_void
id|__init
id|ibm440gx_l2c_setup
c_func
(paren
r_struct
id|ibm44x_clocks
op_star
id|p
)paren
(brace
multiline_comment|/* Disable L2C on rev.A, rev.B and 800MHz version of rev.C,&n;&t;   enable it on all other revisions&n;&t; */
id|u32
id|pvr
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pvr
op_eq
id|PVR_440GX_RA
op_logical_or
id|pvr
op_eq
id|PVR_440GX_RB
op_logical_or
(paren
id|pvr
op_eq
id|PVR_440GX_RC
op_logical_and
id|p-&gt;cpu
OG
l_int|667000000
)paren
)paren
id|ibm440gx_l2c_disable
c_func
(paren
)paren
suffix:semicolon
r_else
id|ibm440gx_l2c_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ibm440gx_get_eth_grp
r_int
id|__init
id|ibm440gx_get_eth_grp
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|SDR_READ
c_func
(paren
id|DCRN_SDR_PFC1
)paren
op_amp
id|DCRN_SDR_PFC1_EPS
)paren
op_rshift
id|DCRN_SDR_PFC1_EPS_SHIFT
suffix:semicolon
)brace
DECL|function|ibm440gx_set_eth_grp
r_void
id|__init
id|ibm440gx_set_eth_grp
c_func
(paren
r_int
id|group
)paren
(brace
id|SDR_WRITE
c_func
(paren
id|DCRN_SDR_PFC1
comma
(paren
id|SDR_READ
c_func
(paren
id|DCRN_SDR_PFC1
)paren
op_amp
op_complement
id|DCRN_SDR_PFC1_EPS
)paren
op_or
(paren
id|group
op_lshift
id|DCRN_SDR_PFC1_EPS_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|ibm440gx_tah_enable
r_void
id|__init
id|ibm440gx_tah_enable
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Enable TAH0 and TAH1 */
id|SDR_WRITE
c_func
(paren
id|DCRN_SDR_MFR
comma
id|SDR_READ
c_func
(paren
id|DCRN_SDR_MFR
)paren
op_amp
op_complement
id|DCRN_SDR_MFR_TAH0
)paren
suffix:semicolon
id|SDR_WRITE
c_func
(paren
id|DCRN_SDR_MFR
comma
id|SDR_READ
c_func
(paren
id|DCRN_SDR_MFR
)paren
op_amp
op_complement
id|DCRN_SDR_MFR_TAH1
)paren
suffix:semicolon
)brace
DECL|function|ibm440gx_show_cpuinfo
r_int
(def_block
id|ibm440gx_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|u32
id|l2c_cfg
op_assign
id|mfdcr
c_func
(paren
id|DCRN_L2C0_CFG
)paren
suffix:semicolon
r_const
r_char
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|l2c_cfg
op_amp
id|L2C_CFG_L2M
)paren
(brace
r_switch
c_cond
(paren
id|l2c_cfg
op_amp
(paren
id|L2C_CFG_ICU
op_or
id|L2C_CFG_DCU
)paren
)paren
(brace
r_case
id|L2C_CFG_ICU
suffix:colon
id|s
op_assign
l_string|&quot;I-Cache only&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|L2C_CFG_DCU
suffix:colon
id|s
op_assign
l_string|&quot;D-Cache only&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|s
op_assign
l_string|&quot;I-Cache/D-Cache&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|s
op_assign
l_string|&quot;disabled&quot;
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;L2-Cache&bslash;t: %s (0x%08x 0x%08x)&bslash;n&quot;
comma
id|s
comma
id|l2c_cfg
comma
id|mfdcr
c_func
(paren
id|DCRN_L2C0_SR
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
eof
