multiline_comment|/*&n; * include/asm-v850/rte_cb.h -- Midas labs RTE-CB series of evaluation boards&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_RTE_CB_H__
DECL|macro|__V850_RTE_CB_H__
mdefine_line|#define __V850_RTE_CB_H__
multiline_comment|/* CPU addresses of GBUS memory spaces.  */
DECL|macro|GCS0_ADDR
mdefine_line|#define GCS0_ADDR&t;&t;0x05000000 /* GCS0 - Common SRAM (2MB) */
DECL|macro|GCS0_SIZE
mdefine_line|#define GCS0_SIZE&t;&t;0x00200000 /*   2MB */
DECL|macro|GCS1_ADDR
mdefine_line|#define GCS1_ADDR&t;&t;0x06000000 /* GCS1 - Flash ROM (8MB) */
DECL|macro|GCS1_SIZE
mdefine_line|#define GCS1_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS2_ADDR
mdefine_line|#define GCS2_ADDR&t;&t;0x07900000 /* GCS2 - I/O registers */
DECL|macro|GCS2_SIZE
mdefine_line|#define GCS2_SIZE&t;&t;0x00400000 /*   4MB */
DECL|macro|GCS5_ADDR
mdefine_line|#define GCS5_ADDR&t;&t;0x04000000 /* GCS5 - PCI bus space */
DECL|macro|GCS5_SIZE
mdefine_line|#define GCS5_SIZE&t;&t;0x01000000 /*   16MB */
DECL|macro|GCS6_ADDR
mdefine_line|#define GCS6_ADDR&t;&t;0x07980000 /* GCS6 - PCI control registers */
DECL|macro|GCS6_SIZE
mdefine_line|#define GCS6_SIZE&t;&t;0x00000200 /*   512B */
multiline_comment|/* The SRAM on the Mother-A motherboard.  */
DECL|macro|MB_A_SRAM_ADDR
mdefine_line|#define MB_A_SRAM_ADDR&t;&t;GCS0_ADDR
DECL|macro|MB_A_SRAM_SIZE
mdefine_line|#define MB_A_SRAM_SIZE&t;&t;0x00200000 /* 2MB */
multiline_comment|/* GBUS interrupt support.  */
DECL|macro|GBUS_INT_BASE_IRQ
mdefine_line|#define GBUS_INT_BASE_IRQ&t;NUM_CPU_IRQS
DECL|macro|GBUS_INT_BASE_ADDR
mdefine_line|#define GBUS_INT_BASE_ADDR&t;(GCS2_ADDR + 0x00006000)
macro_line|#include &lt;asm/gbus_int.h&gt;
multiline_comment|/* We define NUM_MACH_IRQS to include extra interrupts from the GBUS.  */
DECL|macro|NUM_MACH_IRQS
mdefine_line|#define NUM_MACH_IRQS&t;&t;(NUM_CPU_IRQS + IRQ_GBUS_INT_NUM)
multiline_comment|/* Some specific interrupts.  */
DECL|macro|IRQ_MB_A_LAN
mdefine_line|#define IRQ_MB_A_LAN&t;&t;IRQ_GBUS_INT(10)
DECL|macro|IRQ_MB_A_PCI1
mdefine_line|#define IRQ_MB_A_PCI1(n)&t;(IRQ_GBUS_INT(16) + (n))
DECL|macro|IRQ_MB_A_PCI1_NUM
mdefine_line|#define IRQ_MB_A_PCI1_NUM&t;4
DECL|macro|IRQ_MB_A_PCI2
mdefine_line|#define IRQ_MB_A_PCI2(n)&t;(IRQ_GBUS_INT(20) + (n))
DECL|macro|IRQ_MB_A_PCI2_NUM
mdefine_line|#define IRQ_MB_A_PCI2_NUM&t;4
DECL|macro|IRQ_MB_A_EXT
mdefine_line|#define IRQ_MB_A_EXT(n)&t;&t;(IRQ_GBUS_INT(24) + (n))
DECL|macro|IRQ_MB_A_EXT_NUM
mdefine_line|#define IRQ_MB_A_EXT_NUM&t;4
DECL|macro|IRQ_MB_A_USB_OC
mdefine_line|#define IRQ_MB_A_USB_OC(n)&t;(IRQ_GBUS_INT(28) + (n))
DECL|macro|IRQ_MB_A_USB_OC_NUM
mdefine_line|#define IRQ_MB_A_USB_OC_NUM&t;2
DECL|macro|IRQ_MB_A_PCMCIA_OC
mdefine_line|#define IRQ_MB_A_PCMCIA_OC&t;IRQ_GBUS_INT(30)
multiline_comment|/* Mother-A PCI bus support.  */
macro_line|#include &lt;asm/rte_mb_a_pci.h&gt;
multiline_comment|/* These are the base addresses used for allocating device address&n;   space.  512K of the motherboard SRAM is in the same space, so we have&n;   to be careful not to let it be allocated.  */
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;(MB_A_PCI_MEM_ADDR + 0x80000)
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;MB_A_PCI_IO_ADDR
multiline_comment|/* As we don&squot;t really support PCI DMA to cpu memory, and use bounce-buffers&n;   instead, perversely enough, this becomes always true! */
DECL|macro|pci_dma_supported
mdefine_line|#define pci_dma_supported(dev, mask)&t;&t;1
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(dev, mask)&t;0
DECL|macro|pci_controller_num
mdefine_line|#define pci_controller_num(dev)&t;&t;&t;0
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;&t;1
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;100
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
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
