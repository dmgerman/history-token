multiline_comment|/*&n; *&n; *&n; *    Copyright 2000 MontaVista Software Inc.&n; * &t;Author: MontaVista Software, Inc.&n; *         &t;akuster@mvista.com or source@mvista.com&n; *&n; *    Module name: ceder.h&n; *&n; *    Description:&n; *      Macros, definitions, and data structures specific to the IBM PowerPC&n; *      Ceder eval board.&n; *&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_CEDER_H__
DECL|macro|__ASM_CEDER_H__
mdefine_line|#define __ASM_CEDER_H__
macro_line|#include &lt;platforms/ibmnp405l.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Data structure defining board information maintained by the boot&n; * ROM on IBM&squot;s &quot;Ceder&quot; evaluation board. An effort has been made to&n; * keep the field names consistent with the 8xx &squot;bd_t&squot; board info&n; * structures.&n; */
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
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
id|EMAC_NUMS
)braket
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Local Ethernet MAC address */
DECL|member|bi_pci_mac
r_int
r_char
id|bi_pci_mac
(braket
l_int|6
)braket
suffix:semicolon
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
multiline_comment|/* PCI speed in Hz */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* Some 4xx parts use a different timebase frequency from the internal clock.&n;*/
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
multiline_comment|/* Memory map for the IBM &quot;Ceder&quot; NP405 evaluation board.&n; */
r_extern
r_void
op_star
id|ceder_rtc_base
suffix:semicolon
DECL|macro|CEDER_RTC_PADDR
mdefine_line|#define CEDER_RTC_PADDR&t;&t;((uint)0xf0000000)
DECL|macro|CEDER_RTC_VADDR
mdefine_line|#define CEDER_RTC_VADDR&t;&t;CEDER_RTC_PADDR
DECL|macro|CEDER_RTC_SIZE
mdefine_line|#define CEDER_RTC_SIZE&t;&t;((uint)8*1024)
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
DECL|macro|NR_BOARD_IRQS
mdefine_line|#define NR_BOARD_IRQS 32
macro_line|#ifdef CONFIG_PPC405GP_INTERNAL_CLOCK
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;201600
macro_line|#else
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;691200
macro_line|#endif
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME &quot;IBM NP405L Ceder&quot;
r_extern
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_CEDER_H__ */
macro_line|#endif /* __KERNEL__ */
eof
