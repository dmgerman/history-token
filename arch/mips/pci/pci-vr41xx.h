multiline_comment|/*&n; *  pci-vr41xx.h, Include file for PCI Control Unit of the NEC VR4100 series.&n; *&n; *  Copyright (C) 2002  MontaVista Software Inc.&n; *    Author: Yoichi Yuasa &lt;yyuasa@mvista.com or source@mvista.com&gt;&n; *  Copyright (C) 2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __PCI_VR41XX_H
DECL|macro|__PCI_VR41XX_H
mdefine_line|#define __PCI_VR41XX_H
DECL|macro|PCIMMAW1REG
mdefine_line|#define PCIMMAW1REG&t;&t;KSEG1ADDR(0x0f000c00)
DECL|macro|PCIMMAW2REG
mdefine_line|#define PCIMMAW2REG&t;&t;KSEG1ADDR(0x0f000c04)
DECL|macro|PCITAW1REG
mdefine_line|#define PCITAW1REG&t;&t;KSEG1ADDR(0x0f000c08)
DECL|macro|PCITAW2REG
mdefine_line|#define PCITAW2REG&t;&t;KSEG1ADDR(0x0f000c0c)
DECL|macro|PCIMIOAWREG
mdefine_line|#define PCIMIOAWREG&t;&t;KSEG1ADDR(0x0f000c10)
DECL|macro|IBA
mdefine_line|#define IBA(addr)&t;&t;((addr) &amp; 0xff000000U)
DECL|macro|MASTER_MSK
mdefine_line|#define MASTER_MSK(mask)&t;(((mask) &gt;&gt; 11) &amp; 0x000fe000U)
DECL|macro|PCIA
mdefine_line|#define PCIA(addr)&t;&t;(((addr) &gt;&gt; 24) &amp; 0x000000ffU)
DECL|macro|TARGET_MSK
mdefine_line|#define TARGET_MSK(mask)&t;(((mask) &gt;&gt; 8) &amp; 0x000fe000U)
DECL|macro|ITA
mdefine_line|#define ITA(addr)&t;&t;(((addr) &gt;&gt; 24) &amp; 0x000000ffU)
DECL|macro|PCIIA
mdefine_line|#define PCIIA(addr)&t;&t;(((addr) &gt;&gt; 24) &amp; 0x000000ffU)
DECL|macro|WINEN
mdefine_line|#define WINEN&t;&t;&t;0x1000U
DECL|macro|PCICONFDREG
mdefine_line|#define PCICONFDREG&t;&t;KSEG1ADDR(0x0f000c14)
DECL|macro|PCICONFAREG
mdefine_line|#define PCICONFAREG&t;&t;KSEG1ADDR(0x0f000c18)
DECL|macro|PCIMAILREG
mdefine_line|#define PCIMAILREG&t;&t;KSEG1ADDR(0x0f000c1c)
DECL|macro|BUSERRADREG
mdefine_line|#define BUSERRADREG&t;&t;KSEG1ADDR(0x0f000c24)
DECL|macro|EA
mdefine_line|#define EA(reg)&t;&t;((reg) &amp;0xfffffffc)
DECL|macro|INTCNTSTAREG
mdefine_line|#define INTCNTSTAREG&t;&t;KSEG1ADDR(0x0f000c28)
DECL|macro|MABTCLR
mdefine_line|#define MABTCLR&t;&t;0x80000000U
DECL|macro|TRDYCLR
mdefine_line|#define TRDYCLR&t;&t;0x40000000U
DECL|macro|PARCLR
mdefine_line|#define PARCLR&t;&t;&t;0x20000000U
DECL|macro|MBCLR
mdefine_line|#define MBCLR&t;&t;&t;0x10000000U
DECL|macro|SERRCLR
mdefine_line|#define SERRCLR&t;&t;0x08000000U
DECL|macro|RTYCLR
mdefine_line|#define RTYCLR&t;&t;&t;0x04000000U
DECL|macro|MABCLR
mdefine_line|#define MABCLR&t;&t;&t;0x02000000U
DECL|macro|TABCLR
mdefine_line|#define TABCLR&t;&t;&t;0x01000000U
multiline_comment|/* RFU */
DECL|macro|MABTMSK
mdefine_line|#define MABTMSK&t;&t;0x00008000U
DECL|macro|TRDYMSK
mdefine_line|#define TRDYMSK&t;&t;0x00004000U
DECL|macro|PARMSK
mdefine_line|#define PARMSK&t;&t;&t;0x00002000U
DECL|macro|MBMSK
mdefine_line|#define MBMSK&t;&t;&t;0x00001000U
DECL|macro|SERRMSK
mdefine_line|#define SERRMSK&t;&t;0x00000800U
DECL|macro|RTYMSK
mdefine_line|#define RTYMSK&t;&t;&t;0x00000400U
DECL|macro|MABMSK
mdefine_line|#define MABMSK&t;&t;&t;0x00000200U
DECL|macro|TABMSK
mdefine_line|#define TABMSK&t;&t;&t;0x00000100U
DECL|macro|IBAMABT
mdefine_line|#define IBAMABT&t;&t;0x00000080U
DECL|macro|TRDYRCH
mdefine_line|#define TRDYRCH&t;&t;0x00000040U
DECL|macro|PAR
mdefine_line|#define PAR&t;&t;&t;0x00000020U
DECL|macro|MB
mdefine_line|#define MB&t;&t;&t;0x00000010U
DECL|macro|PCISERR
mdefine_line|#define PCISERR&t;&t;0x00000008U
DECL|macro|RTYRCH
mdefine_line|#define RTYRCH&t;&t;&t;0x00000004U
DECL|macro|MABORT
mdefine_line|#define MABORT&t;&t;&t;0x00000002U
DECL|macro|TABORT
mdefine_line|#define TABORT&t;&t;&t;0x00000001U
DECL|macro|PCIEXACCREG
mdefine_line|#define PCIEXACCREG&t;&t;KSEG1ADDR(0x0f000c2c)
DECL|macro|UNLOCK
mdefine_line|#define UNLOCK&t;&t;&t;0x2U
DECL|macro|EAREQ
mdefine_line|#define EAREQ&t;&t;&t;0x1U
DECL|macro|PCIRECONTREG
mdefine_line|#define PCIRECONTREG&t;&t;KSEG1ADDR(0x0f000c30)
DECL|macro|RTRYCNT
mdefine_line|#define RTRYCNT(reg)&t;&t;((reg) &amp; 0x000000ffU)
DECL|macro|PCIENREG
mdefine_line|#define PCIENREG&t;&t;KSEG1ADDR(0x0f000c34)
DECL|macro|BLOODY_CONFIG_DONE
mdefine_line|#define BLOODY_CONFIG_DONE&t;0x4U
DECL|macro|PCICLKSELREG
mdefine_line|#define PCICLKSELREG&t;&t;KSEG1ADDR(0x0f000c38)
DECL|macro|EQUAL_VTCLOCK
mdefine_line|#define EQUAL_VTCLOCK&t;&t;0x2U
DECL|macro|HALF_VTCLOCK
mdefine_line|#define HALF_VTCLOCK&t;&t;0x0U
DECL|macro|ONE_THIRD_VTCLOCK
mdefine_line|#define ONE_THIRD_VTCLOCK&t;0x3U
DECL|macro|QUARTER_VTCLOCK
mdefine_line|#define QUARTER_VTCLOCK&t;0x1U
DECL|macro|PCITRDYVREG
mdefine_line|#define PCITRDYVREG&t;&t;KSEG1ADDR(0x0f000c3c)
DECL|macro|TRDYV
mdefine_line|#define TRDYV(val)&t;&t;((uint32_t)(val) &amp; 0xffU)
DECL|macro|PCICLKRUNREG
mdefine_line|#define PCICLKRUNREG&t;&t;KSEG1ADDR(0x0f000c60)
DECL|macro|VENDORIDREG
mdefine_line|#define VENDORIDREG&t;&t;KSEG1ADDR(0x0f000d00)
DECL|macro|DEVICEIDREG
mdefine_line|#define DEVICEIDREG&t;&t;KSEG1ADDR(0x0f000d00)
DECL|macro|COMMANDREG
mdefine_line|#define COMMANDREG&t;&t;KSEG1ADDR(0x0f000d04)
DECL|macro|STATUSREG
mdefine_line|#define STATUSREG&t;&t;KSEG1ADDR(0x0f000d04)
DECL|macro|REVIDREG
mdefine_line|#define REVIDREG&t;&t;KSEG1ADDR(0x0f000d08)
DECL|macro|CLASSREG
mdefine_line|#define CLASSREG&t;&t;KSEG1ADDR(0x0f000d08)
DECL|macro|CACHELSREG
mdefine_line|#define CACHELSREG&t;&t;KSEG1ADDR(0x0f000d0c)
DECL|macro|LATTIMEREG
mdefine_line|#define LATTIMEREG&t;&t;KSEG1ADDR(0x0f000d0c)
DECL|macro|MLTIM
mdefine_line|#define MLTIM(val)&t;&t;(((uint32_t)(val) &lt;&lt; 7) &amp; 0xff00U)
DECL|macro|MAILBAREG
mdefine_line|#define MAILBAREG&t;&t;KSEG1ADDR(0x0f000d10)
DECL|macro|PCIMBA1REG
mdefine_line|#define PCIMBA1REG&t;&t;KSEG1ADDR(0x0f000d14)
DECL|macro|PCIMBA2REG
mdefine_line|#define PCIMBA2REG&t;&t;KSEG1ADDR(0x0f000d18)
DECL|macro|MBADD
mdefine_line|#define MBADD(base)&t;&t;((base) &amp; 0xfffff800U)
DECL|macro|PMBA
mdefine_line|#define PMBA(base)&t;&t;((base) &amp; 0xffe00000U)
DECL|macro|PREF
mdefine_line|#define PREF&t;&t;&t;0x8U
DECL|macro|PREF_APPROVAL
mdefine_line|#define PREF_APPROVAL&t;&t;0x8U
DECL|macro|PREF_DISAPPROVAL
mdefine_line|#define PREF_DISAPPROVAL&t;0x0U
DECL|macro|TYPE
mdefine_line|#define TYPE&t;&t;&t;0x6U
DECL|macro|TYPE_32BITSPACE
mdefine_line|#define TYPE_32BITSPACE&t;0x0U
DECL|macro|MSI
mdefine_line|#define MSI&t;&t;&t;0x1U
DECL|macro|MSI_MEMORY
mdefine_line|#define MSI_MEMORY&t;&t;0x0U
DECL|macro|INTLINEREG
mdefine_line|#define INTLINEREG&t;&t;KSEG1ADDR(0x0f000d3c)
DECL|macro|INTPINREG
mdefine_line|#define INTPINREG&t;&t;KSEG1ADDR(0x0f000d3c)
DECL|macro|RETVALREG
mdefine_line|#define RETVALREG&t;&t;KSEG1ADDR(0x0f000d40)
DECL|macro|PCIAPCNTREG
mdefine_line|#define PCIAPCNTREG&t;&t;KSEG1ADDR(0x0f000d40)
DECL|macro|TKYGNT
mdefine_line|#define TKYGNT&t;&t;&t;0x04000000U
DECL|macro|TKYGNT_ENABLE
mdefine_line|#define TKYGNT_ENABLE&t;&t;0x04000000U
DECL|macro|TKYGNT_DISABLE
mdefine_line|#define TKYGNT_DISABLE&t;&t;0x00000000U
DECL|macro|PAPC
mdefine_line|#define PAPC&t;&t;&t;0x03000000U
DECL|macro|PAPC_ALTERNATE_B
mdefine_line|#define PAPC_ALTERNATE_B&t;0x02000000U
DECL|macro|PAPC_ALTERNATE_0
mdefine_line|#define PAPC_ALTERNATE_0&t;0x01000000U
DECL|macro|PAPC_FAIR
mdefine_line|#define PAPC_FAIR&t;&t;0x00000000U
DECL|macro|RTYVAL
mdefine_line|#define RTYVAL(val)&t;&t;(((uint32_t)(val) &lt;&lt; 7) &amp; 0xff00U)
DECL|macro|RTYVAL_MASK
mdefine_line|#define RTYVAL_MASK&t;&t;0xff00U
DECL|macro|PCI_CLOCK_MAX
mdefine_line|#define PCI_CLOCK_MAX&t;&t;33333333U
multiline_comment|/*&n; * Default setup&n; */
DECL|macro|PCI_MASTER_MEM1_BUS_BASE_ADDRESS
mdefine_line|#define PCI_MASTER_MEM1_BUS_BASE_ADDRESS&t;0x10000000U
DECL|macro|PCI_MASTER_MEM1_ADDRESS_MASK
mdefine_line|#define PCI_MASTER_MEM1_ADDRESS_MASK&t;&t;0x7c000000U
DECL|macro|PCI_MASTER_MEM1_PCI_BASE_ADDRESS
mdefine_line|#define PCI_MASTER_MEM1_PCI_BASE_ADDRESS&t;0x10000000U
DECL|macro|PCI_TARGET_MEM1_ADDRESS_MASK
mdefine_line|#define PCI_TARGET_MEM1_ADDRESS_MASK&t;&t;0x08000000U
DECL|macro|PCI_TARGET_MEM1_BUS_BASE_ADDRESS
mdefine_line|#define PCI_TARGET_MEM1_BUS_BASE_ADDRESS&t;0x00000000U
DECL|macro|PCI_MASTER_IO_BUS_BASE_ADDRESS
mdefine_line|#define PCI_MASTER_IO_BUS_BASE_ADDRESS&t;&t;0x16000000U
DECL|macro|PCI_MASTER_IO_ADDRESS_MASK
mdefine_line|#define PCI_MASTER_IO_ADDRESS_MASK&t;&t;0x7e000000U
DECL|macro|PCI_MASTER_IO_PCI_BASE_ADDRESS
mdefine_line|#define PCI_MASTER_IO_PCI_BASE_ADDRESS&t;&t;0x00000000U
DECL|macro|PCI_MAILBOX_BASE_ADDRESS
mdefine_line|#define PCI_MAILBOX_BASE_ADDRESS&t;&t;0x00000000U
DECL|macro|PCI_TARGET_WINDOW1_BASE_ADDRESS
mdefine_line|#define PCI_TARGET_WINDOW1_BASE_ADDRESS&t;&t;0x00000000U
DECL|macro|IO_PORT_BASE
mdefine_line|#define IO_PORT_BASE&t;&t;KSEG1ADDR(PCI_MASTER_IO_BUS_BASE_ADDRESS)
DECL|macro|IO_PORT_RESOURCE_START
mdefine_line|#define IO_PORT_RESOURCE_START&t;PCI_MASTER_IO_PCI_BASE_ADDRESS
DECL|macro|IO_PORT_RESOURCE_END
mdefine_line|#define IO_PORT_RESOURCE_END&t;(~PCI_MASTER_IO_ADDRESS_MASK &amp; PCI_MASTER_ADDRESS_MASK)
DECL|macro|PCI_IO_RESOURCE_START
mdefine_line|#define PCI_IO_RESOURCE_START&t;0x01000000UL
DECL|macro|PCI_IO_RESOURCE_END
mdefine_line|#define PCI_IO_RESOURCE_END&t;0x01ffffffUL
DECL|macro|PCI_MEM_RESOURCE_START
mdefine_line|#define PCI_MEM_RESOURCE_START&t;0x11000000UL
DECL|macro|PCI_MEM_RESOURCE_END
mdefine_line|#define PCI_MEM_RESOURCE_END&t;0x13ffffffUL
macro_line|#endif /* __PCI_VR41XX_H */
eof
