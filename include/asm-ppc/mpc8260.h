multiline_comment|/*&n; * Since there are many different boards and no standard configuration,&n; * we have a unique include file for each.  Rather than change every&n; * file that has to include MPC8260 configuration, they all include&n; * this one and the configuration switching is done here.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_MPC8260_H__
DECL|macro|__ASM_PPC_MPC8260_H__
mdefine_line|#define __ASM_PPC_MPC8260_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_8260
macro_line|#ifdef CONFIG_EST8260
macro_line|#include &lt;platforms/est8260.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SBC82xx
macro_line|#include &lt;platforms/sbc82xx.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SBS8260
macro_line|#include &lt;platforms/sbs8260.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RPX8260
macro_line|#include &lt;platforms/rpx8260.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_WILLOW
macro_line|#include &lt;platforms/willow.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_TQM8260
macro_line|#include &lt;platforms/tqm8260.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_PQ2ADS) || defined (CONFIG_PQ2FADS)
macro_line|#include &lt;platforms/pq2ads.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_PCI_8260
macro_line|#include &lt;syslib/m8260_pci.h&gt;
macro_line|#endif
multiline_comment|/* Make sure the memory translation stuff is there if PCI not used.&n; */
macro_line|#ifndef _IO_BASE
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE        0
macro_line|#endif
macro_line|#ifndef _ISA_MEM_BASE
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE   0
macro_line|#endif
macro_line|#ifndef PCI_DRAM_OFFSET
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET 0
macro_line|#endif
multiline_comment|/* Map 256MB I/O region&n; */
macro_line|#ifndef IO_PHYS_ADDR
DECL|macro|IO_PHYS_ADDR
mdefine_line|#define IO_PHYS_ADDR&t;0xe0000000
macro_line|#endif
macro_line|#ifndef IO_VIRT_ADDR
DECL|macro|IO_VIRT_ADDR
mdefine_line|#define IO_VIRT_ADDR&t;IO_PHYS_ADDR
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
macro_line|#endif
macro_line|#endif /* CONFIG_8260 */
macro_line|#endif /* !__ASM_PPC_MPC8260_H__ */
macro_line|#endif /* __KERNEL__ */
eof
