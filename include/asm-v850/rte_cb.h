multiline_comment|/*&n; * include/asm-v850/rte_cb.h -- Midas labs RTE-CB series of evaluation boards&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_RTE_CB_H__
DECL|macro|__V850_RTE_CB_H__
mdefine_line|#define __V850_RTE_CB_H__
multiline_comment|/* The SRAM on the Mother-A motherboard.  */
DECL|macro|MB_A_SRAM_ADDR
mdefine_line|#define MB_A_SRAM_ADDR&t;&t;GCS0_ADDR
DECL|macro|MB_A_SRAM_SIZE
mdefine_line|#define MB_A_SRAM_SIZE&t;&t;0x00200000 /* 2MB */
macro_line|#ifdef CONFIG_RTE_GBUS_INT
multiline_comment|/* GBUS interrupt support.  */
macro_line|# include &lt;asm/gbus_int.h&gt;
DECL|macro|GBUS_INT_BASE_IRQ
macro_line|# define GBUS_INT_BASE_IRQ&t;NUM_RTE_CB_IRQS
DECL|macro|GBUS_INT_BASE_ADDR
macro_line|# define GBUS_INT_BASE_ADDR&t;(GCS2_ADDR + 0x00006000)
multiline_comment|/* Some specific interrupts.  */
DECL|macro|IRQ_MB_A_LAN
macro_line|# define IRQ_MB_A_LAN&t;&t;IRQ_GBUS_INT(10)
DECL|macro|IRQ_MB_A_PCI1
macro_line|# define IRQ_MB_A_PCI1(n)&t;(IRQ_GBUS_INT(16) + (n))
DECL|macro|IRQ_MB_A_PCI1_NUM
macro_line|# define IRQ_MB_A_PCI1_NUM&t;4
DECL|macro|IRQ_MB_A_PCI2
macro_line|# define IRQ_MB_A_PCI2(n)&t;(IRQ_GBUS_INT(20) + (n))
DECL|macro|IRQ_MB_A_PCI2_NUM
macro_line|# define IRQ_MB_A_PCI2_NUM&t;4
DECL|macro|IRQ_MB_A_EXT
macro_line|# define IRQ_MB_A_EXT(n)&t;(IRQ_GBUS_INT(24) + (n))
DECL|macro|IRQ_MB_A_EXT_NUM
macro_line|# define IRQ_MB_A_EXT_NUM&t;4
DECL|macro|IRQ_MB_A_USB_OC
macro_line|# define IRQ_MB_A_USB_OC(n)&t;(IRQ_GBUS_INT(28) + (n))
DECL|macro|IRQ_MB_A_USB_OC_NUM
macro_line|# define IRQ_MB_A_USB_OC_NUM&t;2
DECL|macro|IRQ_MB_A_PCMCIA_OC
macro_line|# define IRQ_MB_A_PCMCIA_OC&t;IRQ_GBUS_INT(30)
multiline_comment|/* We define NUM_MACH_IRQS to include extra interrupts from the GBUS.  */
DECL|macro|NUM_MACH_IRQS
macro_line|# define NUM_MACH_IRQS&t;&t;(NUM_RTE_CB_IRQS + IRQ_GBUS_INT_NUM)
macro_line|#else /* !CONFIG_RTE_GBUS_INT */
DECL|macro|NUM_MACH_IRQS
macro_line|# define NUM_MACH_IRQS&t;&t;NUM_RTE_CB_IRQS
macro_line|#endif /* CONFIG_RTE_GBUS_INT */
macro_line|#ifdef CONFIG_RTE_MB_A_PCI
multiline_comment|/* Mother-A PCI bus support.  */
macro_line|# include &lt;asm/rte_mb_a_pci.h&gt;
multiline_comment|/* These are the base addresses used for allocating device address&n;   space.  512K of the motherboard SRAM is in the same space, so we have&n;   to be careful not to let it be allocated.  */
DECL|macro|PCIBIOS_MIN_MEM
macro_line|# define PCIBIOS_MIN_MEM&t;(MB_A_PCI_MEM_ADDR + 0x80000)
DECL|macro|PCIBIOS_MIN_IO
macro_line|# define PCIBIOS_MIN_IO&t;&t;MB_A_PCI_IO_ADDR
multiline_comment|/* As we don&squot;t really support PCI DMA to cpu memory, and use bounce-buffers&n;   instead, perversely enough, this becomes always true! */
DECL|macro|pci_dma_supported
macro_line|# define pci_dma_supported(dev, mask)&t;&t;1
DECL|macro|pci_dac_dma_supported
macro_line|# define pci_dac_dma_supported(dev, mask)&t;0
DECL|macro|pcibios_assign_all_busses
macro_line|# define pcibios_assign_all_busses()&t;&t;1
macro_line|#endif /* CONFIG_RTE_MB_A_PCI */
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;100
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|rte_cb_early_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rte_cb_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_RTE_CB_H__ */
eof
