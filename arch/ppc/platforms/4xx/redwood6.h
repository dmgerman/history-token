multiline_comment|/*&n; * arch/ppc/platforms/4xx/redwood6.h&n; *&n; * Macros, definitions, and data structures specific to the IBM PowerPC&n; * STBx25xx &quot;Redwood6&quot; evaluation board.&n; *&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_REDWOOD5_H__
DECL|macro|__ASM_REDWOOD5_H__
mdefine_line|#define __ASM_REDWOOD5_H__
multiline_comment|/* Redwood6 has an STBx25xx core */
macro_line|#include &lt;platforms/4xx/ibmstbx25.h&gt;
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
DECL|member|bi_tbfreq
r_int
r_int
id|bi_tbfreq
suffix:semicolon
multiline_comment|/* Software timebase freq */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* !__ASSEMBLY__ */
DECL|macro|SMC91111_BASE_ADDR
mdefine_line|#define SMC91111_BASE_ADDR&t;0xf2030300
DECL|macro|SMC91111_IRQ
mdefine_line|#define SMC91111_IRQ&t;&t;27
DECL|macro|IDE_XLINUX_MUX_BASE
mdefine_line|#define IDE_XLINUX_MUX_BASE        0xf2040000
DECL|macro|IDE_DMA_ADDR
mdefine_line|#define IDE_DMA_ADDR&t;0xfce00000
macro_line|#ifdef MAX_HWIFS
DECL|macro|MAX_HWIFS
macro_line|#undef MAX_HWIFS
macro_line|#endif
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;&t;1
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;0
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;1267200
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME&t;&quot;IBM Redwood6&quot;
macro_line|#endif&t;&t;&t;&t;/* __ASM_REDWOOD5_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
