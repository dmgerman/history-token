multiline_comment|/* $Id: ip22-mc.c,v 1.2 1999/10/19 20:51:52 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * indy_mc.c: Routines for manipulating the INDY memory controller.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sgi/sgimc.h&gt;
macro_line|#include &lt;asm/sgi/sgihpc.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
multiline_comment|/* #define DEBUG_SGIMC */
DECL|variable|mcmisc_regs
r_struct
id|sgimc_misc_ctrl
op_star
id|mcmisc_regs
suffix:semicolon
DECL|variable|rpsscounter
id|u32
op_star
id|rpsscounter
suffix:semicolon
DECL|variable|dmactrlregs
r_struct
id|sgimc_dma_ctrl
op_star
id|dmactrlregs
suffix:semicolon
DECL|function|mconfig_string
r_static
r_inline
r_char
op_star
id|mconfig_string
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_switch
c_cond
(paren
id|val
op_amp
id|SGIMC_MCONFIG_RMASK
)paren
(brace
r_case
id|SGIMC_MCONFIG_FOURMB
suffix:colon
r_return
l_string|&quot;4MB&quot;
suffix:semicolon
r_case
id|SGIMC_MCONFIG_EIGHTMB
suffix:colon
r_return
l_string|&quot;8MB&quot;
suffix:semicolon
r_case
id|SGIMC_MCONFIG_SXTEENMB
suffix:colon
r_return
l_string|&quot;16MB&quot;
suffix:semicolon
r_case
id|SGIMC_MCONFIG_TTWOMB
suffix:colon
r_return
l_string|&quot;32MB&quot;
suffix:semicolon
r_case
id|SGIMC_MCONFIG_SFOURMB
suffix:colon
r_return
l_string|&quot;64MB&quot;
suffix:semicolon
r_case
id|SGIMC_MCONFIG_OTEIGHTMB
suffix:colon
r_return
l_string|&quot;128MB&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;wheee, unknown&quot;
suffix:semicolon
)brace
suffix:semicolon
)brace
DECL|function|sgimc_init
r_void
id|__init
id|sgimc_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmpreg
suffix:semicolon
id|mcmisc_regs
op_assign
(paren
r_struct
id|sgimc_misc_ctrl
op_star
)paren
(paren
id|KSEG1
op_plus
l_int|0x1fa00000
)paren
suffix:semicolon
id|rpsscounter
op_assign
(paren
id|u32
op_star
)paren
(paren
id|KSEG1
op_plus
l_int|0x1fa01004
)paren
suffix:semicolon
id|dmactrlregs
op_assign
(paren
r_struct
id|sgimc_dma_ctrl
op_star
)paren
(paren
id|KSEG1
op_plus
l_int|0x1fa02000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MC: SGI memory controller Revision %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|mcmisc_regs-&gt;systemid
op_amp
id|SGIMC_SYSID_MASKREV
)paren
suffix:semicolon
macro_line|#if 0 /* XXX Until I figure out what this bit really indicates XXX */
multiline_comment|/* XXX Is this systemid bit reliable? */
r_if
c_cond
(paren
id|mcmisc_regs-&gt;systemid
op_amp
id|SGIMC_SYSID_EPRESENT
)paren
(brace
id|EISA_bus
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;with EISA&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|EISA_bus
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;no EISA&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef DEBUG_SGIMC
id|prom_printf
c_func
(paren
l_string|&quot;sgimc_init: memconfig0&lt;%s&gt; mconfig1&lt;%s&gt;&bslash;n&quot;
comma
id|mconfig_string
c_func
(paren
id|mcmisc_regs-&gt;mconfig0
)paren
comma
id|mconfig_string
c_func
(paren
id|mcmisc_regs-&gt;mconfig1
)paren
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;mcdump: cpuctrl0&lt;%08lx&gt; cpuctrl1&lt;%08lx&gt;&bslash;n&quot;
comma
id|mcmisc_regs-&gt;cpuctrl0
comma
id|mcmisc_regs-&gt;cpuctrl1
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;mcdump: divider&lt;%08lx&gt;, gioparm&lt;%04x&gt;&bslash;n&quot;
comma
id|mcmisc_regs-&gt;divider
comma
id|mcmisc_regs-&gt;gioparm
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Place the MC into a known state.  This must be done before&n;&t; * interrupts are first enabled etc.&n;&t; */
multiline_comment|/* Step 1: The CPU/GIO error status registers will not latch&n;&t; *         up a new error status until the register has been&n;&t; *         cleared by the cpu.  These status registers are&n;&t; *         cleared by writing any value to them.&n;&t; */
id|mcmisc_regs-&gt;cstat
op_assign
id|mcmisc_regs-&gt;gstat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Step 2: Enable all parity checking in cpu control register&n;&t; *         zero.&n;&t; */
id|tmpreg
op_assign
id|mcmisc_regs-&gt;cpuctrl0
suffix:semicolon
id|tmpreg
op_or_assign
(paren
id|SGIMC_CCTRL0_EPERRGIO
op_or
id|SGIMC_CCTRL0_EPERRMEM
op_or
id|SGIMC_CCTRL0_R4KNOCHKPARR
)paren
suffix:semicolon
id|mcmisc_regs-&gt;cpuctrl0
op_assign
id|tmpreg
suffix:semicolon
multiline_comment|/* Step 3: Setup the MC write buffer depth, this is controlled&n;&t; *         in cpu control register 1 in the lower 4 bits.&n;&t; */
id|tmpreg
op_assign
id|mcmisc_regs-&gt;cpuctrl1
suffix:semicolon
id|tmpreg
op_and_assign
op_complement
l_int|0xf
suffix:semicolon
id|tmpreg
op_or_assign
l_int|0xd
suffix:semicolon
id|mcmisc_regs-&gt;cpuctrl1
op_assign
id|tmpreg
suffix:semicolon
multiline_comment|/* Step 4: Initialize the RPSS divider register to run as fast&n;&t; *         as it can correctly operate.  The register is laid&n;&t; *         out as follows:&n;&t; *&n;&t; *         ----------------------------------------&n;&t; *         |  RESERVED  |   INCREMENT   | DIVIDER |&n;&t; *         ----------------------------------------&n;&t; *          31        16 15            8 7       0&n;&t; *&n;&t; *         DIVIDER determines how often a &squot;tick&squot; happens,&n;&t; *         INCREMENT determines by how the RPSS increment&n;&t; *         registers value increases at each &squot;tick&squot;. Thus,&n;&t; *         for IP22 we get INCREMENT=1, DIVIDER=1 == 0x101&n;&t; */
id|mcmisc_regs-&gt;divider
op_assign
l_int|0x101
suffix:semicolon
multiline_comment|/* Step 5: Initialize GIO64 arbitrator configuration register.&n;&t; *&n;&t; * NOTE: If you dork with startup code the HPC init code in&n;&t; *       sgihpc_init() must run before us because of how we&n;&t; *       need to know Guiness vs. FullHouse and the board&n;&t; *       revision on this machine.  You have been warned.&n;&t; */
multiline_comment|/* First the basic invariants across all gio64 implementations. */
id|tmpreg
op_assign
id|SGIMC_GIOPARM_HPC64
suffix:semicolon
multiline_comment|/* All 1st HPC&squot;s interface at 64bits. */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_ONEBUS
suffix:semicolon
multiline_comment|/* Only one physical GIO bus exists. */
r_if
c_cond
(paren
id|sgi_guiness
)paren
(brace
multiline_comment|/* Guiness specific settings. */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_EISA64
suffix:semicolon
multiline_comment|/* MC talks to EISA at 64bits */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_MASTEREISA
suffix:semicolon
multiline_comment|/* EISA bus can act as master */
)brace
r_else
(brace
multiline_comment|/* Fullhouse specific settings. */
r_if
c_cond
(paren
id|sgi_boardid
OL
l_int|2
)paren
(brace
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_HPC264
suffix:semicolon
multiline_comment|/* 2nd HPC at 64bits */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_PLINEEXP0
suffix:semicolon
multiline_comment|/* exp0 pipelines */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_MASTEREXP1
suffix:semicolon
multiline_comment|/* exp1 masters */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_RTIMEEXP0
suffix:semicolon
multiline_comment|/* exp0 is realtime */
)brace
r_else
(brace
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_HPC264
suffix:semicolon
multiline_comment|/* 2nd HPC 64bits */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_PLINEEXP0
suffix:semicolon
multiline_comment|/* exp[01] pipelined */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_PLINEEXP1
suffix:semicolon
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_MASTEREISA
suffix:semicolon
multiline_comment|/* EISA masters */
multiline_comment|/* someone forgot this poor little guy... */
id|tmpreg
op_or_assign
id|SGIMC_GIOPARM_GFX64
suffix:semicolon
multiline_comment|/* GFX at 64 bits */
)brace
)brace
id|mcmisc_regs-&gt;gioparm
op_assign
id|tmpreg
suffix:semicolon
multiline_comment|/* poof */
)brace
eof
