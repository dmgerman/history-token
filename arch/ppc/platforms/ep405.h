multiline_comment|/*&n; *    Copyright 2000 MontaVista Software Inc.&n; *    &t;http://www.mvista.com&n; *&t;&lt;mlocke@mvista.com&gt;&n; *&n; *         Embedded Planet 405GP board&n; *         http://www.embeddedplanet.com&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_EP405_H__
DECL|macro|__ASM_EP405_H__
mdefine_line|#define __ASM_EP405_H__
multiline_comment|/* We have a 405GP core */
macro_line|#include &lt;platforms/ibm405gp.h&gt;
macro_line|#ifndef __ASSEMBLY__
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
r_extern
r_void
op_star
id|ep405_bcsr
suffix:semicolon
r_extern
r_void
op_star
id|ep405_nvram
suffix:semicolon
multiline_comment|/* Map for the BCSR and NVRAM space */
DECL|macro|EP405_BCSR_PADDR
mdefine_line|#define EP405_BCSR_PADDR&t;((uint)0xf4000000)
DECL|macro|EP405_BCSR_SIZE
mdefine_line|#define EP405_BCSR_SIZE&t;&t;((uint)16)
DECL|macro|EP405_NVRAM_PADDR
mdefine_line|#define EP405_NVRAM_PADDR&t;((uint)0xf4200000)
multiline_comment|/* FIXME: what if the board has something other than 512k NVRAM */
DECL|macro|EP405_NVRAM_SIZE
mdefine_line|#define EP405_NVRAM_SIZE&t;((uint)512*1024)
multiline_comment|/* Early initialization address mapping for block_io.&n; * Standard 405GP map.&n; */
DECL|macro|PPC4xx_PCI_IO_PADDR
mdefine_line|#define PPC4xx_PCI_IO_PADDR&t;((uint)PPC405_PCI_PHY_IO_BASE)
DECL|macro|PPC4xx_PCI_IO_VADDR
mdefine_line|#define PPC4xx_PCI_IO_VADDR&t;PPC4xx_PCI_IO_PADDR
DECL|macro|PPC4xx_PCI_IO_SIZE
mdefine_line|#define PPC4xx_PCI_IO_SIZE&t;((uint)64*1024)
DECL|macro|PPC4xx_PCI_CFG_PADDR
mdefine_line|#define PPC4xx_PCI_CFG_PADDR&t;((uint)PPC405_PCI_CONFIG_ADDR)
DECL|macro|PPC4xx_PCI_CFG_VADDR
mdefine_line|#define PPC4xx_PCI_CFG_VADDR&t;PPC4xx_PCI_CFG_PADDR
DECL|macro|PPC4xx_PCI_CFG_SIZE
mdefine_line|#define PPC4xx_PCI_CFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_PCI_LCFG_PADDR
mdefine_line|#define PPC4xx_PCI_LCFG_PADDR&t;((uint)0xef400000)
DECL|macro|PPC4xx_PCI_LCFG_VADDR
mdefine_line|#define PPC4xx_PCI_LCFG_VADDR&t;PPC4xx_PCI_LCFG_PADDR
DECL|macro|PPC4xx_PCI_LCFG_SIZE
mdefine_line|#define PPC4xx_PCI_LCFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR&t;((uint)0xef600000)
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR&t;PPC4xx_ONB_IO_PADDR
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)4*1024)
multiline_comment|/* serial defines */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;399193
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME &quot;Embedded Planet 405GP&quot;
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_EP405_H__ */
macro_line|#endif /* __KERNEL__ */
eof
