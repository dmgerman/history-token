multiline_comment|/*&n; *    Copyright 2001 MontaVista Software Inc.&n; *&t;PPC405 modifications&n; * &t;Author: MontaVista Software, Inc.&n; *          Armin Kuster&n; *&n; *    Module name: redwood5.h&n; *&n; *    Description:&n; *      Macros, definitions, and data structures specific to the IBM PowerPC&n; *      STB03xxx &quot;Redwood&quot; evaluation board.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_REDWOOD5_H__
DECL|macro|__ASM_REDWOOD5_H__
mdefine_line|#define __ASM_REDWOOD5_H__
multiline_comment|/* Redwood5 has an STB04xxx core */
macro_line|#include &lt;platforms/ibmstb4.h&gt;
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
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|SMC91111_BASE_ADDR
mdefine_line|#define SMC91111_BASE_ADDR&t;0xf2000300
DECL|macro|SMC91111_IRQ
mdefine_line|#define SMC91111_IRQ&t;&t;28
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
multiline_comment|/* serail defines moved from ppc4xx_serial.h *&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;1267200
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME&t;&quot;IBM Redwood5&quot;
macro_line|#endif /* __ASM_REDWOOD5_H__ */
macro_line|#endif /* __KERNEL__ */
eof
