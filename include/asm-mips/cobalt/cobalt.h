multiline_comment|/*&n; * Lowlevel hardware stuff for the MIPS based Cobalt microservers.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997 Cobalt Microserver&n; * Copyright (C) 1997, 2003 Ralf Baechle&n; * Copyright (C) 2001, 2002, 2003 Liam Davies (ldavies@agile.tv)&n; */
macro_line|#ifndef __ASM_COBALT_H
DECL|macro|__ASM_COBALT_H
mdefine_line|#define __ASM_COBALT_H
multiline_comment|/*&n; * i8259 legacy interrupts used on Cobalt:&n; *&n; *     8  - RTC&n; *     9  - PCI&n; *    14  - IDE0&n; *    15  - IDE1&n; *&n; * CPU IRQs  are 16 ... 23&n; */
DECL|macro|COBALT_TIMER_IRQ
mdefine_line|#define COBALT_TIMER_IRQ&t;18
DECL|macro|COBALT_SCC_IRQ
mdefine_line|#define COBALT_SCC_IRQ          19&t;&t;/* pre-production has 85C30 */
DECL|macro|COBALT_RAQ_SCSI_IRQ
mdefine_line|#define COBALT_RAQ_SCSI_IRQ&t;19
DECL|macro|COBALT_ETH0_IRQ
mdefine_line|#define COBALT_ETH0_IRQ&t;&t;19
DECL|macro|COBALT_ETH1_IRQ
mdefine_line|#define COBALT_ETH1_IRQ&t;&t;20
DECL|macro|COBALT_SERIAL_IRQ
mdefine_line|#define COBALT_SERIAL_IRQ&t;21
DECL|macro|COBALT_SCSI_IRQ
mdefine_line|#define COBALT_SCSI_IRQ         21
DECL|macro|COBALT_VIA_IRQ
mdefine_line|#define COBALT_VIA_IRQ&t;&t;22&t;&t;/* Chained to VIA ISA bridge */
DECL|macro|COBALT_QUBE_SLOT_IRQ
mdefine_line|#define COBALT_QUBE_SLOT_IRQ&t;23
multiline_comment|/*&n; * PCI configuration space manifest constants.  These are wired into&n; * the board layout according to the PCI spec to enable the software&n; * to probe the hardware configuration space in a well defined manner.&n; *&n; * The PCI_DEVSHFT() macro transforms these values into numbers&n; * suitable for passing as the dev parameter to the various&n; * pcibios_read/write_config routines.&n; */
DECL|macro|COBALT_PCICONF_CPU
mdefine_line|#define COBALT_PCICONF_CPU      0x06
DECL|macro|COBALT_PCICONF_ETH0
mdefine_line|#define COBALT_PCICONF_ETH0     0x07
DECL|macro|COBALT_PCICONF_RAQSCSI
mdefine_line|#define COBALT_PCICONF_RAQSCSI  0x08
DECL|macro|COBALT_PCICONF_VIA
mdefine_line|#define COBALT_PCICONF_VIA      0x09
DECL|macro|COBALT_PCICONF_PCISLOT
mdefine_line|#define COBALT_PCICONF_PCISLOT  0x0A
DECL|macro|COBALT_PCICONF_ETH1
mdefine_line|#define COBALT_PCICONF_ETH1     0x0C
multiline_comment|/*&n; * The Cobalt board id information.  The boards have an ID number wired&n; * into the VIA that is available in the high nibble of register 94.&n; * This register is available in the VIA configuration space through the&n; * interface routines qube_pcibios_read/write_config. See cobalt/pci.c&n; */
DECL|macro|VIA_COBALT_BRD_ID_REG
mdefine_line|#define VIA_COBALT_BRD_ID_REG  0x94
DECL|macro|VIA_COBALT_BRD_REG_to_ID
mdefine_line|#define VIA_COBALT_BRD_REG_to_ID(reg)  ((unsigned char) (reg) &gt;&gt; 4)
DECL|macro|COBALT_BRD_ID_QUBE1
mdefine_line|#define COBALT_BRD_ID_QUBE1    0x3
DECL|macro|COBALT_BRD_ID_RAQ1
mdefine_line|#define COBALT_BRD_ID_RAQ1     0x4
DECL|macro|COBALT_BRD_ID_QUBE2
mdefine_line|#define COBALT_BRD_ID_QUBE2    0x5
DECL|macro|COBALT_BRD_ID_RAQ2
mdefine_line|#define COBALT_BRD_ID_RAQ2     0x6
multiline_comment|/*&n; * Galileo chipset access macros for the Cobalt. The base address for&n; * the GT64111 chip is 0x14000000&n; *&n; * Most of this really should go into a separate GT64111 header file.&n; */
DECL|macro|GT64111_IO_BASE
mdefine_line|#define GT64111_IO_BASE&t;&t;0x10000000UL
DECL|macro|GT64111_BASE
mdefine_line|#define GT64111_BASE&t;&t;0x14000000UL
DECL|macro|GALILEO_REG
mdefine_line|#define GALILEO_REG(ofs)&t;(KSEG0 + GT64111_BASE + (unsigned long)(ofs))
DECL|macro|GALILEO_INL
mdefine_line|#define GALILEO_INL(port)&t;(*(volatile unsigned int *) GALILEO_REG(port))
DECL|macro|GALILEO_OUTL
mdefine_line|#define GALILEO_OUTL(val, port)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile unsigned int *) GALILEO_REG(port) = (port);&t;&t;&bslash;&n;} while (0)
DECL|macro|GALILEO_T0EXP
mdefine_line|#define GALILEO_T0EXP&t;&t;0x0100
DECL|macro|GALILEO_ENTC0
mdefine_line|#define GALILEO_ENTC0&t;&t;0x01
DECL|macro|GALILEO_SELTC0
mdefine_line|#define GALILEO_SELTC0&t;&t;0x02
DECL|macro|PCI_CFG_SET
mdefine_line|#define PCI_CFG_SET(devfn,where)&t;&t;&t;&t;&t;&bslash;&n;&t;GALILEO_OUTL((0x80000000 | (PCI_SLOT (devfn) &lt;&lt; 11) |&t;&t;&bslash;&n;&t;&t;(PCI_FUNC (devfn) &lt;&lt; 8) | (where)), GT_PCI0_CFGADDR_OFS)
macro_line|#endif /* __ASM_COBALT_H */
eof
