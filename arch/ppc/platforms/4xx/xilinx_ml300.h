multiline_comment|/*&n; * arch/ppc/platforms/4xx/xilinx_ml300.h&n; *&n; * Include file that defines the Xilinx ML300 evaluation board&n; *&n; * Author: MontaVista Software, Inc.&n; *         source@mvista.com&n; *&n; * 2002-2004 (c) MontaVista Software, Inc.  This file is licensed under the&n; * terms of the GNU General Public License version 2.  This program is licensed&n; * &quot;as is&quot; without any warranty of any kind, whether express or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_XILINX_ML300_H__
DECL|macro|__ASM_XILINX_ML300_H__
mdefine_line|#define __ASM_XILINX_ML300_H__
multiline_comment|/* ML300 has a Xilinx Virtex-II Pro processor */
macro_line|#include &lt;platforms/4xx/virtex-ii_pro.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|board_info
r_typedef
r_struct
id|board_info
(brace
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* DRAM installed, in bytes */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Local Ethernet MAC address */
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
multiline_comment|/* PLB Bus speed, in Hz */
DECL|member|bi_pci_busfreq
r_int
r_int
id|bi_pci_busfreq
suffix:semicolon
multiline_comment|/* PCI Bus speed, in Hz */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* Some 4xx parts use a different timebase frequency from the internal clock.&n;*/
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* We don&squot;t need anything mapped.  Size of zero will accomplish that. */
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR&t;0u
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR&t;0u
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;0u
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME &quot;Xilinx ML300&quot;
macro_line|#endif /* __ASM_XILINX_ML300_H__ */
macro_line|#endif /* __KERNEL__ */
eof
