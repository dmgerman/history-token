multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/* This is the single file included by all MPC8260 build options.&n; * Since there are many different boards and no standard configuration,&n; * we have a unique include file for each.  Rather than change every&n; * file that has to include MPC8260 configuration, they all include&n; * this one and the configuration switching is done here.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __CONFIG_8260_DEFS
DECL|macro|__CONFIG_8260_DEFS
mdefine_line|#define __CONFIG_8260_DEFS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_8260
macro_line|#ifdef CONFIG_EST8260
macro_line|#include &lt;platforms/est8260.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SBS8260
macro_line|#include &lt;platforms/sbs8260.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RPX6
macro_line|#include &lt;platforms/rpxsuper.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_WILLOW
macro_line|#include &lt;platforms/willow.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_TQM8260
macro_line|#include &lt;platforms/tqm8260.h&gt;
macro_line|#endif
multiline_comment|/* I don&squot;t yet have the ISA or PCI stuff done....no 8260 with&n; * such thing.....&n; */
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE        0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE   0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET 0
multiline_comment|/* The &quot;residual&quot; data board information structure the boot loader&n; * hands to us.&n; */
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
multiline_comment|/* I need this to get pt_regs.......&n;*/
macro_line|#include &lt;asm/ptrace.h&gt;
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
macro_line|#endif /* CONFIG_8260 */
macro_line|#endif /* !__CONFIG_8260_DEFS */
macro_line|#endif /* __KERNEL__ */
eof
