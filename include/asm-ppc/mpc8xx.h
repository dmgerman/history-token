multiline_comment|/* This is the single file included by all MPC8xx build options.&n; * Since there are many different boards and no standard configuration,&n; * we have a unique include file for each.  Rather than change every&n; * file that has to include MPC8xx configuration, they all include&n; * this one and the configuration switching is done here.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __CONFIG_8xx_DEFS
DECL|macro|__CONFIG_8xx_DEFS
mdefine_line|#define __CONFIG_8xx_DEFS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_8xx
macro_line|#ifdef CONFIG_MBX
macro_line|#include &lt;asm/mbx.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_FADS
macro_line|#include &lt;asm/fads.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RPXLITE
macro_line|#include &lt;asm/rpxlite.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_BSEIP
macro_line|#include &lt;asm/bseip.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RPXCLASSIC
macro_line|#include &lt;asm/rpxclassic.h&gt;
macro_line|#endif
macro_line|#if (defined(CONFIG_TQM860) || defined(CONFIG_TQM8xxL))
macro_line|#include &lt;asm/tqm8xx.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_SPD823TS)
macro_line|#include &lt;asm/spd8xx.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_IVMS8)
macro_line|#include &lt;asm/ivms8.h&gt;
macro_line|#endif
multiline_comment|/* I need this to get pt_regs.......&n;*/
macro_line|#include &lt;asm/ptrace.h&gt;
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
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE        0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE   0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET 0
macro_line|#endif
r_extern
r_int
r_int
id|isa_io_base
suffix:semicolon
r_extern
r_int
r_int
id|isa_mem_base
suffix:semicolon
r_extern
r_int
r_int
id|pci_dram_offset
suffix:semicolon
multiline_comment|/* The &quot;residual&quot; data board information structure the boot loader&n; * hands to us.&n; */
r_extern
r_int
r_char
id|__res
(braket
)braket
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
macro_line|#endif /* CONFIG_8xx */
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
