multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/* This is the single file included by all MPC8xx build options.&n; * Since there are many different boards and no standard configuration,&n; * we have a unique include file for each.  Rather than change every&n; * file that has to include MPC8xx configuration, they all include&n; * this one and the configuration switching is done here.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __CONFIG_8xx_DEFS
DECL|macro|__CONFIG_8xx_DEFS
mdefine_line|#define __CONFIG_8xx_DEFS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_8xx
macro_line|#ifdef CONFIG_MBX
macro_line|#include &lt;platforms/mbx.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_FADS
macro_line|#include &lt;platforms/fads.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RPXLITE
macro_line|#include &lt;platforms/rpxlite.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_BSEIP
macro_line|#include &lt;platforms/bseip.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RPXCLASSIC
macro_line|#include &lt;platforms/rpxclassic.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_TQM8xxL)
macro_line|#include &lt;platforms/tqm8xx.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_SPD823TS)
macro_line|#include &lt;platforms/spd8xx.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_IVMS8) || defined(CONFIG_IVML24)
macro_line|#include &lt;platforms/ivms8.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_HERMES_PRO)
macro_line|#include &lt;platforms/hermes.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_IP860)
macro_line|#include &lt;platforms/ip860.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_LWMON)
macro_line|#include &lt;platforms/lwmon.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_PCU_E)
macro_line|#include &lt;platforms/pcu_e.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_CCM)
macro_line|#include &lt;platforms/ccm.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_LANTEC)
macro_line|#include &lt;platforms/lantec.h&gt;
macro_line|#endif
multiline_comment|/* Currently, all 8xx boards that support a processor to PCI/ISA bridge&n; * use the same memory map.&n; */
macro_line|#if 0
macro_line|#if defined(CONFIG_PCI) &amp;&amp; defined(PCI_ISA_IO_ADDR)
mdefine_line|#define&t;_IO_BASE PCI_ISA_IO_ADDR
mdefine_line|#define&t;_ISA_MEM_BASE PCI_ISA_MEM_ADDR
mdefine_line|#define PCI_DRAM_OFFSET 0x80000000
macro_line|#else
mdefine_line|#define _IO_BASE        0
mdefine_line|#define _ISA_MEM_BASE   0
mdefine_line|#define PCI_DRAM_OFFSET 0
macro_line|#endif
macro_line|#else
macro_line|#if !defined(_IO_BASE)  /* defined in board specific header */
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE        0
macro_line|#endif
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE   0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET 0
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* The &quot;residual&quot; data board information structure the boot loader&n; * hands to us.&n; */
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_int
id|request_8xxirq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|device
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* CONFIG_8xx */
macro_line|#endif /* __CONFIG_8xx_DEFS */
macro_line|#endif /* __KERNEL__ */
eof
