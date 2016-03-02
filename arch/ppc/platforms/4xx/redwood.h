multiline_comment|/*&n; * arch/ppc/platforms/4xx/redwood.h&n; *&n; * Macros, definitions, and data structures specific to the IBM PowerPC&n; * STB03xxx &quot;Redwood&quot; evaluation board.&n; *&n; * Author: Frank Rowand &lt;frank_rowand@mvista.com&gt;, or source@mvista.com&n; * &n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_REDWOOD_H__
DECL|macro|__ASM_REDWOOD_H__
mdefine_line|#define __ASM_REDWOOD_H__
multiline_comment|/* Redwoods have an STB03xxx or STB04xxx core */
macro_line|#include &lt;platforms/4xx/ibmstb3.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|struct|board_info
r_typedef
r_struct
id|board_info
(brace
DECL|member|bi_s_version
r_int
r_char
id|bi_s_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Version of this structure */
DECL|member|bi_r_version
r_int
r_char
id|bi_r_version
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* Version of the IBM ROM */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* DRAM installed, in bytes */
DECL|member|bi_dummy
r_int
r_int
id|bi_dummy
suffix:semicolon
multiline_comment|/* field shouldn&squot;t exist */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet MAC address */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Processor speed, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus speed, in Hz */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
DECL|macro|OAKNET_IO_PADDR
mdefine_line|#define OAKNET_IO_PADDR&t;&t;((uint)0xf2000000)
DECL|macro|OAKNET_IO_VADDR
mdefine_line|#define OAKNET_IO_VADDR&t;&t;OAKNET_IO_PADDR
DECL|macro|OAKNET_IO_BASE
mdefine_line|#define OAKNET_IO_BASE&t;&t;OAKNET_IO_VADDR
multiline_comment|/* ftr revisit- io size was 0xffff in old-line, is 0x40 in oak.h */
DECL|macro|OAKNET_IO_SIZE
mdefine_line|#define OAKNET_IO_SIZE&t;&t;0xffff
DECL|macro|OAKNET_INT
mdefine_line|#define OAKNET_INT&t;&t;26&t;/* EXTINT1 */
DECL|macro|IDE_XLINUX_MUX_BASE
mdefine_line|#define IDE_XLINUX_MUX_BASE        0xf2040000
DECL|macro|IDE_DMA_ADDR
mdefine_line|#define IDE_DMA_ADDR&t;0xfce00000
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;0
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;(378000000 / 18 / 16)
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME&t;&quot;IBM Redwood&quot;
macro_line|#endif /* __ASM_REDWOOD_H__ */
macro_line|#endif /* __KERNEL__ */
eof
