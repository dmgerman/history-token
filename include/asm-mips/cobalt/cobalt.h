multiline_comment|/*&n; * Lowlevel hardware stuff for the MIPS based Cobalt microservers.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997 Cobalt Microserver&n; * Copyright (C) 1997 Ralf Baechle&n; * Copyright (C) 2001, 2002, 2003 Liam Davies (ldavies@agile.tv)&n; *&n; */
macro_line|#ifndef __ASM_MIPS_COBALT_H
DECL|macro|__ASM_MIPS_COBALT_H
mdefine_line|#define __ASM_MIPS_COBALT_H
multiline_comment|/*&n; * COBALT interrupt enable bits&n; */
DECL|macro|COBALT_IE_PCI
mdefine_line|#define COBALT_IE_PCI          (1 &lt;&lt; 0)
DECL|macro|COBALT_IE_FLOPPY
mdefine_line|#define COBALT_IE_FLOPPY       (1 &lt;&lt; 1)
DECL|macro|COBALT_IE_KEYBOARD
mdefine_line|#define COBALT_IE_KEYBOARD     (1 &lt;&lt; 2)
DECL|macro|COBALT_IE_SERIAL1
mdefine_line|#define COBALT_IE_SERIAL1      (1 &lt;&lt; 3)
DECL|macro|COBALT_IE_SERIAL2
mdefine_line|#define COBALT_IE_SERIAL2      (1 &lt;&lt; 4)
DECL|macro|COBALT_IE_PARALLEL
mdefine_line|#define COBALT_IE_PARALLEL     (1 &lt;&lt; 5)
DECL|macro|COBALT_IE_GPIO
mdefine_line|#define COBALT_IE_GPIO         (1 &lt;&lt; 6)
DECL|macro|COBALT_IE_RTC
mdefine_line|#define COBALT_IE_RTC          (1 &lt;&lt; 7)
multiline_comment|/*&n; * PCI defines&n; */
DECL|macro|COBALT_IE_ETHERNET
mdefine_line|#define COBALT_IE_ETHERNET     (1 &lt;&lt; 7)
DECL|macro|COBALT_IE_SCSI
mdefine_line|#define COBALT_IE_SCSI         (1 &lt;&lt; 7)
multiline_comment|/*&n; * COBALT Interrupt Level definitions.&n; * These should match the request IRQ id&squot;s.&n; */
DECL|macro|COBALT_TIMER_IRQ
mdefine_line|#define COBALT_TIMER_IRQ       0
DECL|macro|COBALT_KEYBOARD_IRQ
mdefine_line|#define COBALT_KEYBOARD_IRQ    1
DECL|macro|COBALT_QUBE_SLOT_IRQ
mdefine_line|#define COBALT_QUBE_SLOT_IRQ   9
DECL|macro|COBALT_ETH0_IRQ
mdefine_line|#define COBALT_ETH0_IRQ        4
DECL|macro|COBALT_ETH1_IRQ
mdefine_line|#define COBALT_ETH1_IRQ        13
DECL|macro|COBALT_SCC_IRQ
mdefine_line|#define COBALT_SCC_IRQ         4
DECL|macro|COBALT_SERIAL2_IRQ
mdefine_line|#define COBALT_SERIAL2_IRQ     4
DECL|macro|COBALT_PARALLEL_IRQ
mdefine_line|#define COBALT_PARALLEL_IRQ    5
DECL|macro|COBALT_FLOPPY_IRQ
mdefine_line|#define COBALT_FLOPPY_IRQ      6 /* needs to be consistent with floppy driver! */
DECL|macro|COBALT_SCSI_IRQ
mdefine_line|#define COBALT_SCSI_IRQ        7
DECL|macro|COBALT_SERIAL_IRQ
mdefine_line|#define COBALT_SERIAL_IRQ      7
DECL|macro|COBALT_RAQ_SCSI_IRQ
mdefine_line|#define COBALT_RAQ_SCSI_IRQ    4
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
multiline_comment|/*&n; * Galileo chipset access macros for the Cobalt. The base address for&n; * the GT64111 chip is 0x14000000&n; */
DECL|macro|GT64111_BASE
mdefine_line|#define GT64111_BASE&t;&t;0x04000000
DECL|macro|GALILEO_REG
mdefine_line|#define GALILEO_REG(ofs)&t;(GT64111_BASE + (ofs))
DECL|macro|GALILEO_INL
mdefine_line|#define GALILEO_INL(port)&t;(inl(GALILEO_REG(port)))
DECL|macro|GALILEO_OUTL
mdefine_line|#define GALILEO_OUTL(val, port)&t;outl(val, GALILEO_REG(port))
DECL|macro|GALILEO_T0EXP
mdefine_line|#define GALILEO_T0EXP&t;&t;0x0100
DECL|macro|GALILEO_ENTC0
mdefine_line|#define GALILEO_ENTC0&t;&t;0x01
DECL|macro|GALILEO_SELTC0
mdefine_line|#define GALILEO_SELTC0&t;&t;0x02
macro_line|#endif /* __ASM_MIPS_COBALT_H */
eof
