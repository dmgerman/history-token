multiline_comment|/*&n; * arch/ppc/platforms/pplus.h&n; *&n; * Definitions for Motorola MCG Falcon/Raven &amp; HAWK North Bridge &amp; Memory ctlr.&n; *&n; * Author: Mark A. Greerinclude/asm-ppc/hawk.h&n; *         mgreer@mvista.com&n; *&n; * Modified by Randy Vinson (rvinson@mvista.com)&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __PPC_PPLUS_H
DECL|macro|__PPC_PPLUS_H
mdefine_line|#define __PPC_PPLUS_H
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Due to limiations imposed by legacy hardware (primaryily IDE controllers),&n; * the PPLUS boards operate using a PReP address map.&n; *&n; * From Processor (physical) -&gt; PCI:&n; *   PCI Mem Space: 0xc0000000 - 0xfe000000 -&gt; 0x00000000 - 0x3e000000 (768 MB)&n; *   PCI I/O Space: 0x80000000 - 0x90000000 -&gt; 0x00000000 - 0x10000000 (256 MB)&n; *&t;Note: Must skip 0xfe000000-0xfe400000 for CONFIG_HIGHMEM/PKMAP area&n; *&n; * From PCI -&gt; Processor (physical):&n; *   System Memory: 0x80000000 -&gt; 0x00000000&n; */
DECL|macro|PPLUS_ISA_MEM_BASE
mdefine_line|#define PPLUS_ISA_MEM_BASE&t;&t;PREP_ISA_MEM_BASE
DECL|macro|PPLUS_ISA_IO_BASE
mdefine_line|#define PPLUS_ISA_IO_BASE&t;&t;PREP_ISA_IO_BASE
multiline_comment|/* PCI Memory space mapping info */
DECL|macro|PPLUS_PCI_MEM_SIZE
mdefine_line|#define PPLUS_PCI_MEM_SIZE&t;&t;0x30000000U
DECL|macro|PPLUS_PROC_PCI_MEM_START
mdefine_line|#define PPLUS_PROC_PCI_MEM_START&t;PPLUS_ISA_MEM_BASE
DECL|macro|PPLUS_PROC_PCI_MEM_END
mdefine_line|#define PPLUS_PROC_PCI_MEM_END&t;&t;(PPLUS_PROC_PCI_MEM_START +&t;&bslash;&n;&t;&t;&t;&t;&t; PPLUS_PCI_MEM_SIZE - 1)
DECL|macro|PPLUS_PCI_MEM_START
mdefine_line|#define PPLUS_PCI_MEM_START&t;&t;0x00000000U
DECL|macro|PPLUS_PCI_MEM_END
mdefine_line|#define PPLUS_PCI_MEM_END&t;&t;(PPLUS_PCI_MEM_START +&t;&bslash;&n;&t;&t;&t;&t;&t; PPLUS_PCI_MEM_SIZE - 1)
multiline_comment|/* PCI I/O space mapping info */
DECL|macro|PPLUS_PCI_IO_SIZE
mdefine_line|#define PPLUS_PCI_IO_SIZE&t;&t;0x10000000U
DECL|macro|PPLUS_PROC_PCI_IO_START
mdefine_line|#define PPLUS_PROC_PCI_IO_START&t;&t;PPLUS_ISA_IO_BASE
DECL|macro|PPLUS_PROC_PCI_IO_END
mdefine_line|#define PPLUS_PROC_PCI_IO_END&t;&t;(PPLUS_PROC_PCI_IO_START +&t;&bslash;&n;&t;&t;&t;&t;&t; PPLUS_PCI_IO_SIZE - 1)
DECL|macro|PPLUS_PCI_IO_START
mdefine_line|#define PPLUS_PCI_IO_START&t;&t;0x00000000U
DECL|macro|PPLUS_PCI_IO_END
mdefine_line|#define PPLUS_PCI_IO_END&t;&t;(PPLUS_PCI_IO_START + &t;&bslash;&n;&t;&t;&t;&t;&t; PPLUS_PCI_IO_SIZE - 1)
multiline_comment|/* System memory mapping info */
DECL|macro|PPLUS_PCI_DRAM_OFFSET
mdefine_line|#define PPLUS_PCI_DRAM_OFFSET&t;&t;PREP_PCI_DRAM_OFFSET
DECL|macro|PPLUS_PCI_PHY_MEM_OFFSET
mdefine_line|#define PPLUS_PCI_PHY_MEM_OFFSET&t;(PPLUS_ISA_MEM_BASE-PPLUS_PCI_MEM_START)
multiline_comment|/* Define base addresses for important sets of registers */
DECL|macro|PPLUS_HAWK_SMC_BASE
mdefine_line|#define PPLUS_HAWK_SMC_BASE&t;&t;0xfef80000U
DECL|macro|PPLUS_HAWK_PPC_REG_BASE
mdefine_line|#define PPLUS_HAWK_PPC_REG_BASE&t;&t;0xfeff0000U
DECL|macro|PPLUS_SYS_CONFIG_REG
mdefine_line|#define PPLUS_SYS_CONFIG_REG&t;&t;0xfef80400U
DECL|macro|PPLUS_L2_CONTROL_REG
mdefine_line|#define PPLUS_L2_CONTROL_REG&t;&t;0x8000081cU
DECL|macro|PPLUS_VGA_MEM_BASE
mdefine_line|#define PPLUS_VGA_MEM_BASE&t;&t;0xf0000000U
macro_line|#endif&t;/* __PPC_PPLUS_H */
eof
