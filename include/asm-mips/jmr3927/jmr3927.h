multiline_comment|/*&n; * Defines for the TJSYS JMR-TX3927/JMI-3927IO2/JMY-1394IF.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2001 Toshiba Corporation&n; */
macro_line|#ifndef __ASM_TX3927_JMR3927_H
DECL|macro|__ASM_TX3927_JMR3927_H
mdefine_line|#define __ASM_TX3927_JMR3927_H
macro_line|#include &lt;asm/jmr3927/tx3927.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/jmr3927/irq.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/system.h&gt;
macro_line|#endif
multiline_comment|/* CS */
DECL|macro|JMR3927_ROMCE0
mdefine_line|#define JMR3927_ROMCE0&t;0x1fc00000&t;/* 4M */
DECL|macro|JMR3927_ROMCE1
mdefine_line|#define JMR3927_ROMCE1&t;0x1e000000&t;/* 4M */
DECL|macro|JMR3927_ROMCE2
mdefine_line|#define JMR3927_ROMCE2&t;0x14000000&t;/* 16M */
DECL|macro|JMR3927_ROMCE3
mdefine_line|#define JMR3927_ROMCE3&t;0x10000000&t;/* 64M */
DECL|macro|JMR3927_ROMCE5
mdefine_line|#define JMR3927_ROMCE5&t;0x1d000000&t;/* 4M */
DECL|macro|JMR3927_SDCS0
mdefine_line|#define JMR3927_SDCS0&t;0x00000000&t;/* 32M */
DECL|macro|JMR3927_SDCS1
mdefine_line|#define JMR3927_SDCS1&t;0x02000000&t;/* 32M */
multiline_comment|/* PCI Direct Mappings */
DECL|macro|JMR3927_PCIMEM
mdefine_line|#define JMR3927_PCIMEM&t;0x08000000
DECL|macro|JMR3927_PCIMEM_SIZE
mdefine_line|#define JMR3927_PCIMEM_SIZE&t;0x08000000&t;/* 128M */
DECL|macro|JMR3927_PCIIO
mdefine_line|#define JMR3927_PCIIO&t;0x15000000
DECL|macro|JMR3927_PCIIO_SIZE
mdefine_line|#define JMR3927_PCIIO_SIZE&t;0x01000000&t;/* 16M */
DECL|macro|JMR3927_SDRAM_SIZE
mdefine_line|#define JMR3927_SDRAM_SIZE&t;0x02000000&t;/* 32M */
DECL|macro|JMR3927_PORT_BASE
mdefine_line|#define JMR3927_PORT_BASE&t;KSEG1
multiline_comment|/* select indirect initiator access per errata */
DECL|macro|JMR3927_INIT_INDIRECT_PCI
mdefine_line|#define JMR3927_INIT_INDIRECT_PCI
DECL|macro|PCI_ISTAT_IDICC
mdefine_line|#define PCI_ISTAT_IDICC           0x1000
DECL|macro|PCI_IPCIBE_IBE_LONG
mdefine_line|#define PCI_IPCIBE_IBE_LONG       0
DECL|macro|PCI_IPCIBE_ICMD_IOREAD
mdefine_line|#define PCI_IPCIBE_ICMD_IOREAD    2
DECL|macro|PCI_IPCIBE_ICMD_IOWRITE
mdefine_line|#define PCI_IPCIBE_ICMD_IOWRITE   3
DECL|macro|PCI_IPCIBE_ICMD_MEMREAD
mdefine_line|#define PCI_IPCIBE_ICMD_MEMREAD   6
DECL|macro|PCI_IPCIBE_ICMD_MEMWRITE
mdefine_line|#define PCI_IPCIBE_ICMD_MEMWRITE  7
DECL|macro|PCI_IPCIBE_ICMD_SHIFT
mdefine_line|#define PCI_IPCIBE_ICMD_SHIFT     4
multiline_comment|/* Address map (virtual address) */
DECL|macro|JMR3927_ROM0_BASE
mdefine_line|#define JMR3927_ROM0_BASE&t;(KSEG1 + JMR3927_ROMCE0)
DECL|macro|JMR3927_ROM1_BASE
mdefine_line|#define JMR3927_ROM1_BASE&t;(KSEG1 + JMR3927_ROMCE1)
DECL|macro|JMR3927_IOC_BASE
mdefine_line|#define JMR3927_IOC_BASE&t;(KSEG1 + JMR3927_ROMCE2)
DECL|macro|JMR3927_IOB_BASE
mdefine_line|#define JMR3927_IOB_BASE&t;(KSEG1 + JMR3927_ROMCE3)
DECL|macro|JMR3927_ISAMEM_BASE
mdefine_line|#define JMR3927_ISAMEM_BASE&t;(JMR3927_IOB_BASE)
DECL|macro|JMR3927_ISAIO_BASE
mdefine_line|#define JMR3927_ISAIO_BASE&t;(JMR3927_IOB_BASE + 0x01000000)
DECL|macro|JMR3927_ISAC_BASE
mdefine_line|#define JMR3927_ISAC_BASE&t;(JMR3927_IOB_BASE + 0x02000000)
DECL|macro|JMR3927_LCDVGA_REG_BASE
mdefine_line|#define JMR3927_LCDVGA_REG_BASE&t;(JMR3927_IOB_BASE + 0x03000000)
DECL|macro|JMR3927_LCDVGA_MEM_BASE
mdefine_line|#define JMR3927_LCDVGA_MEM_BASE&t;(JMR3927_IOB_BASE + 0x03800000)
DECL|macro|JMR3927_JMY1394_BASE
mdefine_line|#define JMR3927_JMY1394_BASE&t;(KSEG1 + JMR3927_ROMCE5)
DECL|macro|JMR3927_PREMIER3_BASE
mdefine_line|#define JMR3927_PREMIER3_BASE&t;(JMR3927_JMY1394_BASE + 0x00100000)
DECL|macro|JMR3927_PCIMEM_BASE
mdefine_line|#define JMR3927_PCIMEM_BASE&t;(KSEG1 + JMR3927_PCIMEM)
DECL|macro|JMR3927_PCIIO_BASE
mdefine_line|#define JMR3927_PCIIO_BASE&t;(KSEG1 + JMR3927_PCIIO)
DECL|macro|JMR3927_IOC_REV_ADDR
mdefine_line|#define JMR3927_IOC_REV_ADDR&t;(JMR3927_IOC_BASE + 0x00000000)
DECL|macro|JMR3927_IOC_NVRAMB_ADDR
mdefine_line|#define JMR3927_IOC_NVRAMB_ADDR&t;(JMR3927_IOC_BASE + 0x00010000)
DECL|macro|JMR3927_IOC_LED_ADDR
mdefine_line|#define JMR3927_IOC_LED_ADDR&t;(JMR3927_IOC_BASE + 0x00020000)
DECL|macro|JMR3927_IOC_DIPSW_ADDR
mdefine_line|#define JMR3927_IOC_DIPSW_ADDR&t;(JMR3927_IOC_BASE + 0x00030000)
DECL|macro|JMR3927_IOC_BREV_ADDR
mdefine_line|#define JMR3927_IOC_BREV_ADDR&t;(JMR3927_IOC_BASE + 0x00040000)
DECL|macro|JMR3927_IOC_DTR_ADDR
mdefine_line|#define JMR3927_IOC_DTR_ADDR&t;(JMR3927_IOC_BASE + 0x00050000)
DECL|macro|JMR3927_IOC_INTS1_ADDR
mdefine_line|#define JMR3927_IOC_INTS1_ADDR&t;(JMR3927_IOC_BASE + 0x00080000)
DECL|macro|JMR3927_IOC_INTS2_ADDR
mdefine_line|#define JMR3927_IOC_INTS2_ADDR&t;(JMR3927_IOC_BASE + 0x00090000)
DECL|macro|JMR3927_IOC_INTM_ADDR
mdefine_line|#define JMR3927_IOC_INTM_ADDR&t;(JMR3927_IOC_BASE + 0x000a0000)
DECL|macro|JMR3927_IOC_INTP_ADDR
mdefine_line|#define JMR3927_IOC_INTP_ADDR&t;(JMR3927_IOC_BASE + 0x000b0000)
DECL|macro|JMR3927_IOC_RESET_ADDR
mdefine_line|#define JMR3927_IOC_RESET_ADDR&t;(JMR3927_IOC_BASE + 0x000f0000)
DECL|macro|JMR3927_ISAC_REV_ADDR
mdefine_line|#define JMR3927_ISAC_REV_ADDR&t;(JMR3927_ISAC_BASE + 0x00000000)
DECL|macro|JMR3927_ISAC_EINTS_ADDR
mdefine_line|#define JMR3927_ISAC_EINTS_ADDR&t;(JMR3927_ISAC_BASE + 0x00200000)
DECL|macro|JMR3927_ISAC_EINTM_ADDR
mdefine_line|#define JMR3927_ISAC_EINTM_ADDR&t;(JMR3927_ISAC_BASE + 0x00300000)
DECL|macro|JMR3927_ISAC_NMI_ADDR
mdefine_line|#define JMR3927_ISAC_NMI_ADDR&t;(JMR3927_ISAC_BASE + 0x00400000)
DECL|macro|JMR3927_ISAC_LED_ADDR
mdefine_line|#define JMR3927_ISAC_LED_ADDR&t;(JMR3927_ISAC_BASE + 0x00500000)
DECL|macro|JMR3927_ISAC_INTP_ADDR
mdefine_line|#define JMR3927_ISAC_INTP_ADDR&t;(JMR3927_ISAC_BASE + 0x00800000)
DECL|macro|JMR3927_ISAC_INTS1_ADDR
mdefine_line|#define JMR3927_ISAC_INTS1_ADDR&t;(JMR3927_ISAC_BASE + 0x00900000)
DECL|macro|JMR3927_ISAC_INTS2_ADDR
mdefine_line|#define JMR3927_ISAC_INTS2_ADDR&t;(JMR3927_ISAC_BASE + 0x00a00000)
DECL|macro|JMR3927_ISAC_INTM_ADDR
mdefine_line|#define JMR3927_ISAC_INTM_ADDR&t;(JMR3927_ISAC_BASE + 0x00b00000)
multiline_comment|/* Flash ROM */
DECL|macro|JMR3927_FLASH_BASE
mdefine_line|#define JMR3927_FLASH_BASE&t;(JMR3927_ROM0_BASE)
DECL|macro|JMR3927_FLASH_SIZE
mdefine_line|#define JMR3927_FLASH_SIZE&t;0x00400000
multiline_comment|/* bits for IOC_REV/IOC_BREV/ISAC_REV (high byte) */
DECL|macro|JMR3927_IDT_MASK
mdefine_line|#define JMR3927_IDT_MASK&t;0xfc
DECL|macro|JMR3927_REV_MASK
mdefine_line|#define JMR3927_REV_MASK&t;0x03
DECL|macro|JMR3927_IOC_IDT
mdefine_line|#define JMR3927_IOC_IDT&t;&t;0xe0
DECL|macro|JMR3927_ISAC_IDT
mdefine_line|#define JMR3927_ISAC_IDT&t;0x20
multiline_comment|/* bits for IOC_INTS1/IOC_INTS2/IOC_INTM/IOC_INTP (high byte) */
DECL|macro|JMR3927_IOC_INTB_PCIA
mdefine_line|#define JMR3927_IOC_INTB_PCIA&t;0
DECL|macro|JMR3927_IOC_INTB_PCIB
mdefine_line|#define JMR3927_IOC_INTB_PCIB&t;1
DECL|macro|JMR3927_IOC_INTB_PCIC
mdefine_line|#define JMR3927_IOC_INTB_PCIC&t;2
DECL|macro|JMR3927_IOC_INTB_PCID
mdefine_line|#define JMR3927_IOC_INTB_PCID&t;3
DECL|macro|JMR3927_IOC_INTB_MODEM
mdefine_line|#define JMR3927_IOC_INTB_MODEM&t;4
DECL|macro|JMR3927_IOC_INTB_INT6
mdefine_line|#define JMR3927_IOC_INTB_INT6&t;5
DECL|macro|JMR3927_IOC_INTB_INT7
mdefine_line|#define JMR3927_IOC_INTB_INT7&t;6
DECL|macro|JMR3927_IOC_INTB_SOFT
mdefine_line|#define JMR3927_IOC_INTB_SOFT&t;7
DECL|macro|JMR3927_IOC_INTF_PCIA
mdefine_line|#define JMR3927_IOC_INTF_PCIA&t;(1 &lt;&lt; JMR3927_IOC_INTF_PCIA)
DECL|macro|JMR3927_IOC_INTF_PCIB
mdefine_line|#define JMR3927_IOC_INTF_PCIB&t;(1 &lt;&lt; JMR3927_IOC_INTB_PCIB)
DECL|macro|JMR3927_IOC_INTF_PCIC
mdefine_line|#define JMR3927_IOC_INTF_PCIC&t;(1 &lt;&lt; JMR3927_IOC_INTB_PCIC)
DECL|macro|JMR3927_IOC_INTF_PCID
mdefine_line|#define JMR3927_IOC_INTF_PCID&t;(1 &lt;&lt; JMR3927_IOC_INTB_PCID)
DECL|macro|JMR3927_IOC_INTF_MODEM
mdefine_line|#define JMR3927_IOC_INTF_MODEM&t;(1 &lt;&lt; JMR3927_IOC_INTB_MODEM)
DECL|macro|JMR3927_IOC_INTF_INT6
mdefine_line|#define JMR3927_IOC_INTF_INT6&t;(1 &lt;&lt; JMR3927_IOC_INTB_INT6)
DECL|macro|JMR3927_IOC_INTF_INT7
mdefine_line|#define JMR3927_IOC_INTF_INT7&t;(1 &lt;&lt; JMR3927_IOC_INTB_INT7)
DECL|macro|JMR3927_IOC_INTF_SOFT
mdefine_line|#define JMR3927_IOC_INTF_SOFT&t;(1 &lt;&lt; JMR3927_IOC_INTB_SOFT)
multiline_comment|/* bits for IOC_RESET (high byte) */
DECL|macro|JMR3927_IOC_RESET_CPU
mdefine_line|#define JMR3927_IOC_RESET_CPU&t;1
DECL|macro|JMR3927_IOC_RESET_PCI
mdefine_line|#define JMR3927_IOC_RESET_PCI&t;2
multiline_comment|/* bits for ISAC_EINTS/ISAC_EINTM (high byte) */
DECL|macro|JMR3927_ISAC_EINTB_IOCHK
mdefine_line|#define JMR3927_ISAC_EINTB_IOCHK&t;2
DECL|macro|JMR3927_ISAC_EINTB_BWTH
mdefine_line|#define JMR3927_ISAC_EINTB_BWTH&t;4
DECL|macro|JMR3927_ISAC_EINTF_IOCHK
mdefine_line|#define JMR3927_ISAC_EINTF_IOCHK&t;(1 &lt;&lt; JMR3927_ISAC_EINTB_IOCHK)
DECL|macro|JMR3927_ISAC_EINTF_BWTH
mdefine_line|#define JMR3927_ISAC_EINTF_BWTH&t;(1 &lt;&lt; JMR3927_ISAC_EINTB_BWTH)
multiline_comment|/* bits for ISAC_LED (high byte) */
DECL|macro|JMR3927_ISAC_LED_ISALED
mdefine_line|#define JMR3927_ISAC_LED_ISALED&t;0x01
DECL|macro|JMR3927_ISAC_LED_USRLED
mdefine_line|#define JMR3927_ISAC_LED_USRLED&t;0x02
multiline_comment|/* bits for ISAC_INTS/ISAC_INTM/ISAC_INTP (high byte) */
DECL|macro|JMR3927_ISAC_INTB_IRQ5
mdefine_line|#define JMR3927_ISAC_INTB_IRQ5&t;0
DECL|macro|JMR3927_ISAC_INTB_IRQKB
mdefine_line|#define JMR3927_ISAC_INTB_IRQKB&t;1
DECL|macro|JMR3927_ISAC_INTB_IRQMOUSE
mdefine_line|#define JMR3927_ISAC_INTB_IRQMOUSE&t;2
DECL|macro|JMR3927_ISAC_INTB_IRQ4
mdefine_line|#define JMR3927_ISAC_INTB_IRQ4&t;3
DECL|macro|JMR3927_ISAC_INTB_IRQ12
mdefine_line|#define JMR3927_ISAC_INTB_IRQ12&t;4
DECL|macro|JMR3927_ISAC_INTB_IRQ3
mdefine_line|#define JMR3927_ISAC_INTB_IRQ3&t;5
DECL|macro|JMR3927_ISAC_INTB_IRQ10
mdefine_line|#define JMR3927_ISAC_INTB_IRQ10&t;6
DECL|macro|JMR3927_ISAC_INTB_ISAER
mdefine_line|#define JMR3927_ISAC_INTB_ISAER&t;7
DECL|macro|JMR3927_ISAC_INTF_IRQ5
mdefine_line|#define JMR3927_ISAC_INTF_IRQ5&t;(1 &lt;&lt; JMR3927_ISAC_INTB_IRQ5)
DECL|macro|JMR3927_ISAC_INTF_IRQKB
mdefine_line|#define JMR3927_ISAC_INTF_IRQKB&t;(1 &lt;&lt; JMR3927_ISAC_INTB_IRQKB)
DECL|macro|JMR3927_ISAC_INTF_IRQMOUSE
mdefine_line|#define JMR3927_ISAC_INTF_IRQMOUSE&t;(1 &lt;&lt; JMR3927_ISAC_INTB_IRQMOUSE)
DECL|macro|JMR3927_ISAC_INTF_IRQ4
mdefine_line|#define JMR3927_ISAC_INTF_IRQ4&t;(1 &lt;&lt; JMR3927_ISAC_INTB_IRQ4)
DECL|macro|JMR3927_ISAC_INTF_IRQ12
mdefine_line|#define JMR3927_ISAC_INTF_IRQ12&t;(1 &lt;&lt; JMR3927_ISAC_INTB_IRQ12)
DECL|macro|JMR3927_ISAC_INTF_IRQ3
mdefine_line|#define JMR3927_ISAC_INTF_IRQ3&t;(1 &lt;&lt; JMR3927_ISAC_INTB_IRQ3)
DECL|macro|JMR3927_ISAC_INTF_IRQ10
mdefine_line|#define JMR3927_ISAC_INTF_IRQ10&t;(1 &lt;&lt; JMR3927_ISAC_INTB_IRQ10)
DECL|macro|JMR3927_ISAC_INTF_ISAER
mdefine_line|#define JMR3927_ISAC_INTF_ISAER&t;(1 &lt;&lt; JMR3927_ISAC_INTB_ISAER)
macro_line|#ifndef __ASSEMBLY__
macro_line|#if 0
mdefine_line|#define jmr3927_ioc_reg_out(d, a)&t;((*(volatile unsigned short *)(a)) = (d) &lt;&lt; 8)
mdefine_line|#define jmr3927_ioc_reg_in(a)&t;&t;(((*(volatile unsigned short *)(a)) &gt;&gt; 8) &amp; 0xff)
macro_line|#else
macro_line|#if defined(__BIG_ENDIAN)
DECL|macro|jmr3927_ioc_reg_out
mdefine_line|#define jmr3927_ioc_reg_out(d, a)&t;((*(volatile unsigned char *)(a)) = (d))
DECL|macro|jmr3927_ioc_reg_in
mdefine_line|#define jmr3927_ioc_reg_in(a)&t;&t;(*(volatile unsigned char *)(a))
macro_line|#elif defined(__LITTLE_ENDIAN)
DECL|macro|jmr3927_ioc_reg_out
mdefine_line|#define jmr3927_ioc_reg_out(d, a)&t;((*(volatile unsigned char *)((a)^1)) = (d))
DECL|macro|jmr3927_ioc_reg_in
mdefine_line|#define jmr3927_ioc_reg_in(a)&t;&t;(*(volatile unsigned char *)((a)^1))
macro_line|#else
macro_line|#error &quot;No Endian&quot;
macro_line|#endif
macro_line|#endif
DECL|macro|jmr3927_isac_reg_out
mdefine_line|#define jmr3927_isac_reg_out(d, a)&t;((*(volatile unsigned char *)(a)) = (d))
DECL|macro|jmr3927_isac_reg_in
mdefine_line|#define jmr3927_isac_reg_in(a)&t;&t;(*(volatile unsigned char *)(a))
DECL|function|jmr3927_have_isac
r_static
r_inline
r_int
id|jmr3927_have_isac
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|idt
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|romcr3
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|romcr3
op_assign
id|tx3927_romcptr-&gt;cr
(braket
l_int|3
)braket
suffix:semicolon
id|tx3927_romcptr-&gt;cr
(braket
l_int|3
)braket
op_and_assign
l_int|0xffffefff
suffix:semicolon
multiline_comment|/* do not wait infinitely */
id|idt
op_assign
id|jmr3927_isac_reg_in
c_func
(paren
id|JMR3927_ISAC_REV_ADDR
)paren
op_amp
id|JMR3927_IDT_MASK
suffix:semicolon
id|tx3927_romcptr-&gt;cr
(braket
l_int|3
)braket
op_assign
id|romcr3
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|idt
op_eq
id|JMR3927_ISAC_IDT
suffix:semicolon
)brace
DECL|macro|jmr3927_have_nvram
mdefine_line|#define jmr3927_have_nvram() &bslash;&n;&t;((jmr3927_ioc_reg_in(JMR3927_IOC_REV_ADDR) &amp; JMR3927_IDT_MASK) == JMR3927_IOC_IDT)
multiline_comment|/* NVRAM macro */
DECL|macro|jmr3927_nvram_in
mdefine_line|#define jmr3927_nvram_in(ofs) &bslash;&n;&t;jmr3927_ioc_reg_in(JMR3927_IOC_NVRAMB_ADDR + ((ofs) &lt;&lt; 1))
DECL|macro|jmr3927_nvram_out
mdefine_line|#define jmr3927_nvram_out(d, ofs) &bslash;&n;&t;jmr3927_ioc_reg_out(d, JMR3927_IOC_NVRAMB_ADDR + ((ofs) &lt;&lt; 1))
multiline_comment|/* LED macro */
DECL|macro|jmr3927_led_set
mdefine_line|#define jmr3927_led_set(n/*0-16*/)&t;jmr3927_ioc_reg_out(~(n), JMR3927_IOC_LED_ADDR)
DECL|macro|jmr3927_io_led_set
mdefine_line|#define jmr3927_io_led_set(n/*0-3*/)&t;jmr3927_isac_reg_out((n), JMR3927_ISAC_LED_ADDR)
DECL|macro|jmr3927_led_and_set
mdefine_line|#define jmr3927_led_and_set(n/*0-16*/)&t;jmr3927_ioc_reg_out((~(n)) &amp; jmr3927_ioc_reg_in(JMR3927_IOC_LED_ADDR), JMR3927_IOC_LED_ADDR)
multiline_comment|/* DIPSW4 macro */
DECL|macro|jmr3927_dipsw1
mdefine_line|#define jmr3927_dipsw1()&t;((tx3927_pioptr-&gt;din &amp; (1 &lt;&lt; 11)) == 0)
DECL|macro|jmr3927_dipsw2
mdefine_line|#define jmr3927_dipsw2()&t;((tx3927_pioptr-&gt;din &amp; (1 &lt;&lt; 10)) == 0)
DECL|macro|jmr3927_dipsw3
mdefine_line|#define jmr3927_dipsw3()&t;((jmr3927_ioc_reg_in(JMR3927_IOC_DIPSW_ADDR) &amp; 2) == 0)
DECL|macro|jmr3927_dipsw4
mdefine_line|#define jmr3927_dipsw4()&t;((jmr3927_ioc_reg_in(JMR3927_IOC_DIPSW_ADDR) &amp; 1) == 0)
DECL|macro|jmr3927_io_dipsw
mdefine_line|#define jmr3927_io_dipsw()&t;(jmr3927_isac_reg_in(JMR3927_ISAC_LED_ADDR) &gt;&gt; 4)
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * UART defines for serial.h&n; */
multiline_comment|/* use Pre-scaler T0 (1/2) */
DECL|macro|JMR3927_BASE_BAUD
mdefine_line|#define JMR3927_BASE_BAUD (JMR3927_IMCLK / 2 / 16)
DECL|macro|UART0_ADDR
mdefine_line|#define UART0_ADDR   0xfffef300
DECL|macro|UART1_ADDR
mdefine_line|#define UART1_ADDR   0xfffef400
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT    JMR3927_IRQ_IRC_SIO0
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT    JMR3927_IRQ_IRC_SIO1
DECL|macro|UART0_FLAGS
mdefine_line|#define UART0_FLAGS  ASYNC_BOOT_AUTOCONF
DECL|macro|UART1_FLAGS
mdefine_line|#define UART1_FLAGS  0
multiline_comment|/*&n; * IRQ mappings&n; */
multiline_comment|/* These are the virtual IRQ numbers, we divide all IRQ&squot;s into&n; * &squot;spaces&squot;, the &squot;space&squot; determines where and how to enable/disable&n; * that particular IRQ on an JMR machine.  Add new &squot;spaces&squot; as new&n; * IRQ hardware is supported.&n; */
DECL|macro|JMR3927_NR_IRQ_IRC
mdefine_line|#define JMR3927_NR_IRQ_IRC&t;16&t;/* On-Chip IRC */
DECL|macro|JMR3927_NR_IRQ_IOC
mdefine_line|#define JMR3927_NR_IRQ_IOC&t;8&t;/* PCI/MODEM/INT[6:7] */
DECL|macro|JMR3927_NR_IRQ_ISAC
mdefine_line|#define JMR3927_NR_IRQ_ISAC&t;8&t;/* ISA */
DECL|macro|JMR3927_IRQ_IRC
mdefine_line|#define JMR3927_IRQ_IRC&t;NR_ISA_IRQS
DECL|macro|JMR3927_IRQ_IOC
mdefine_line|#define JMR3927_IRQ_IOC&t;(JMR3927_IRQ_IRC + JMR3927_NR_IRQ_IRC)
DECL|macro|JMR3927_IRQ_ISAC
mdefine_line|#define JMR3927_IRQ_ISAC&t;(JMR3927_IRQ_IOC + JMR3927_NR_IRQ_IOC)
DECL|macro|JMR3927_IRQ_END
mdefine_line|#define JMR3927_IRQ_END&t;(JMR3927_IRQ_ISAC + JMR3927_NR_IRQ_ISAC)
DECL|macro|JMR3927_IRQ_IS_IRC
mdefine_line|#define JMR3927_IRQ_IS_IRC(irq)&t;(JMR3927_IRQ_IRC &lt;= (irq) &amp;&amp; (irq) &lt; JMR3927_IRQ_IOC)
DECL|macro|JMR3927_IRQ_IS_IOC
mdefine_line|#define JMR3927_IRQ_IS_IOC(irq)&t;&t;(JMR3927_IRQ_IOC &lt;= (irq) &amp;&amp; (irq) &lt; JMR3927_IRQ_ISAC)
DECL|macro|JMR3927_IRQ_IS_ISAC
mdefine_line|#define JMR3927_IRQ_IS_ISAC(irq)&t;(JMR3927_IRQ_ISAC &lt;= (irq) &amp;&amp; (irq) &lt; JMR3927_IRQ_END)
DECL|macro|JMR3927_IRQ_IRC_INT0
mdefine_line|#define JMR3927_IRQ_IRC_INT0&t;(JMR3927_IRQ_IRC + TX3927_IR_INT0)
DECL|macro|JMR3927_IRQ_IRC_INT1
mdefine_line|#define JMR3927_IRQ_IRC_INT1&t;(JMR3927_IRQ_IRC + TX3927_IR_INT1)
DECL|macro|JMR3927_IRQ_IRC_INT2
mdefine_line|#define JMR3927_IRQ_IRC_INT2&t;(JMR3927_IRQ_IRC + TX3927_IR_INT2)
DECL|macro|JMR3927_IRQ_IRC_INT3
mdefine_line|#define JMR3927_IRQ_IRC_INT3&t;(JMR3927_IRQ_IRC + TX3927_IR_INT3)
DECL|macro|JMR3927_IRQ_IRC_INT4
mdefine_line|#define JMR3927_IRQ_IRC_INT4&t;(JMR3927_IRQ_IRC + TX3927_IR_INT4)
DECL|macro|JMR3927_IRQ_IRC_INT5
mdefine_line|#define JMR3927_IRQ_IRC_INT5&t;(JMR3927_IRQ_IRC + TX3927_IR_INT5)
DECL|macro|JMR3927_IRQ_IRC_SIO0
mdefine_line|#define JMR3927_IRQ_IRC_SIO0&t;(JMR3927_IRQ_IRC + TX3927_IR_SIO0)
DECL|macro|JMR3927_IRQ_IRC_SIO1
mdefine_line|#define JMR3927_IRQ_IRC_SIO1&t;(JMR3927_IRQ_IRC + TX3927_IR_SIO1)
DECL|macro|JMR3927_IRQ_IRC_SIO
mdefine_line|#define JMR3927_IRQ_IRC_SIO(ch)&t;(JMR3927_IRQ_IRC + TX3927_IR_SIO(ch))
DECL|macro|JMR3927_IRQ_IRC_DMA
mdefine_line|#define JMR3927_IRQ_IRC_DMA&t;(JMR3927_IRQ_IRC + TX3927_IR_DMA)
DECL|macro|JMR3927_IRQ_IRC_PIO
mdefine_line|#define JMR3927_IRQ_IRC_PIO&t;(JMR3927_IRQ_IRC + TX3927_IR_PIO)
DECL|macro|JMR3927_IRQ_IRC_PCI
mdefine_line|#define JMR3927_IRQ_IRC_PCI&t;(JMR3927_IRQ_IRC + TX3927_IR_PCI)
DECL|macro|JMR3927_IRQ_IRC_TMR0
mdefine_line|#define JMR3927_IRQ_IRC_TMR0&t;(JMR3927_IRQ_IRC + TX3927_IR_TMR0)
DECL|macro|JMR3927_IRQ_IRC_TMR1
mdefine_line|#define JMR3927_IRQ_IRC_TMR1&t;(JMR3927_IRQ_IRC + TX3927_IR_TMR1)
DECL|macro|JMR3927_IRQ_IRC_TMR2
mdefine_line|#define JMR3927_IRQ_IRC_TMR2&t;(JMR3927_IRQ_IRC + TX3927_IR_TMR2)
DECL|macro|JMR3927_IRQ_IOC_PCIA
mdefine_line|#define JMR3927_IRQ_IOC_PCIA&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCIA)
DECL|macro|JMR3927_IRQ_IOC_PCIB
mdefine_line|#define JMR3927_IRQ_IOC_PCIB&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCIB)
DECL|macro|JMR3927_IRQ_IOC_PCIC
mdefine_line|#define JMR3927_IRQ_IOC_PCIC&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCIC)
DECL|macro|JMR3927_IRQ_IOC_PCID
mdefine_line|#define JMR3927_IRQ_IOC_PCID&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCID)
DECL|macro|JMR3927_IRQ_IOC_MODEM
mdefine_line|#define JMR3927_IRQ_IOC_MODEM&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_MODEM)
DECL|macro|JMR3927_IRQ_IOC_INT6
mdefine_line|#define JMR3927_IRQ_IOC_INT6&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_INT6)
DECL|macro|JMR3927_IRQ_IOC_INT7
mdefine_line|#define JMR3927_IRQ_IOC_INT7&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_INT7)
DECL|macro|JMR3927_IRQ_IOC_SOFT
mdefine_line|#define JMR3927_IRQ_IOC_SOFT&t;(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_SOFT)
DECL|macro|JMR3927_IRQ_ISAC_IRQ5
mdefine_line|#define JMR3927_IRQ_ISAC_IRQ5&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_IRQ5)
DECL|macro|JMR3927_IRQ_ISAC_IRQKB
mdefine_line|#define JMR3927_IRQ_ISAC_IRQKB&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_IRQKB)
DECL|macro|JMR3927_IRQ_ISAC_IRQMOUSE
mdefine_line|#define JMR3927_IRQ_ISAC_IRQMOUSE&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_IRQMOUSE)
DECL|macro|JMR3927_IRQ_ISAC_IRQ4
mdefine_line|#define JMR3927_IRQ_ISAC_IRQ4&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_IRQ4)
DECL|macro|JMR3927_IRQ_ISAC_IRQ12
mdefine_line|#define JMR3927_IRQ_ISAC_IRQ12&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_IRQ12)
DECL|macro|JMR3927_IRQ_ISAC_IRQ3
mdefine_line|#define JMR3927_IRQ_ISAC_IRQ3&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_IRQ3)
DECL|macro|JMR3927_IRQ_ISAC_IRQ10
mdefine_line|#define JMR3927_IRQ_ISAC_IRQ10&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_IRQ10)
DECL|macro|JMR3927_IRQ_ISAC_ISAER
mdefine_line|#define JMR3927_IRQ_ISAC_ISAER&t;(JMR3927_IRQ_ISAC + JMR3927_ISAC_INTB_ISAER)
macro_line|#if 0&t;/* auto detect */
multiline_comment|/* RTL8019AS 10M Ether (JMI-3927IO2:JPW2:1-2 Short) */
mdefine_line|#define JMR3927_IRQ_ETHER1&t;JMR3927_IRQ_IRC_INT0
macro_line|#endif
multiline_comment|/* IOC (PCI, MODEM) */
DECL|macro|JMR3927_IRQ_IOCINT
mdefine_line|#define JMR3927_IRQ_IOCINT&t;JMR3927_IRQ_IRC_INT1
multiline_comment|/* ISAC (ISA, PCMCIA, KEYBOARD, MOUSE) */
DECL|macro|JMR3927_IRQ_ISACINT
mdefine_line|#define JMR3927_IRQ_ISACINT&t;JMR3927_IRQ_IRC_INT2
multiline_comment|/* TC35815 100M Ether (JMR-TX3912:JPW4:2-3 Short) */
DECL|macro|JMR3927_IRQ_ETHER0
mdefine_line|#define JMR3927_IRQ_ETHER0&t;JMR3927_IRQ_IRC_INT3
multiline_comment|/* Clock Tick (10ms) */
DECL|macro|JMR3927_IRQ_TICK
mdefine_line|#define JMR3927_IRQ_TICK&t;JMR3927_IRQ_IRC_TMR0
DECL|macro|JMR3927_IRQ_IDE
mdefine_line|#define JMR3927_IRQ_IDE&t;&t;JMR3927_IRQ_ISAC_IRQ12
multiline_comment|/* IEEE1394 (Note that this may conflicts with RTL8019AS 10M Ether...) */
DECL|macro|JMR3927_IRQ_PREMIER3
mdefine_line|#define JMR3927_IRQ_PREMIER3&t;JMR3927_IRQ_IRC_INT0
multiline_comment|/* I/O Ports */
multiline_comment|/* RTL8019AS 10M Ether */
DECL|macro|JMR3927_ETHER1_PORT
mdefine_line|#define JMR3927_ETHER1_PORT&t;(JMR3927_ISAIO_BASE - JMR3927_PORT_BASE + 0x280)
DECL|macro|JMR3927_KBD_PORT
mdefine_line|#define JMR3927_KBD_PORT&t;(JMR3927_ISAIO_BASE - JMR3927_PORT_BASE + 0x00800060)
DECL|macro|JMR3927_IDE_PORT
mdefine_line|#define JMR3927_IDE_PORT&t;(JMR3927_ISAIO_BASE - JMR3927_PORT_BASE + 0x001001f0)
multiline_comment|/* Clocks */
DECL|macro|JMR3927_CORECLK
mdefine_line|#define JMR3927_CORECLK&t;132710400&t;/* 132.7MHz */
DECL|macro|JMR3927_GBUSCLK
mdefine_line|#define JMR3927_GBUSCLK&t;(JMR3927_CORECLK / 2)&t;/* 66.35MHz */
DECL|macro|JMR3927_IMCLK
mdefine_line|#define JMR3927_IMCLK&t;(JMR3927_CORECLK / 4)&t;/* 33.17MHz */
DECL|macro|jmr3927_tmrptr
mdefine_line|#define jmr3927_tmrptr&t;&t;tx3927_tmrptr(0)&t;/* TMR0 */
multiline_comment|/*&n; * TX3927 Pin Configuration:&n; *&n; *&t;PCFG bits&t;&t;Avail&t;&t;&t;Dead&n; *&t;SELSIO[1:0]:11&t;&t;RXD[1:0], TXD[1:0]&t;PIO[6:3]&n; *&t;SELSIOC[0]:1&t;&t;CTS[0], RTS[0]&t;&t;INT[5:4]&n; *&t;SELSIOC[1]:0,SELDSF:0,&t;GSDAO[0],GPCST[3]&t;CTS[1], RTS[1],DSF,&n; *&t;  GDBGE*&t;&t;&t;&t;&t;  PIO[2:1]&n; *&t;SELDMA[2]:1&t;&t;DMAREQ[2],DMAACK[2]&t;PIO[13:12]&n; *&t;SELTMR[2:0]:000&t;&t;&t;&t;&t;TIMER[1:0]&n; *&t;SELCS:0,SELDMA[1]:0&t;PIO[11;10]&t;&t;SDCS_CE[7:6],&n; *&t;&t;&t;&t;&t;&t;&t;  DMAREQ[1],DMAACK[1]&n; *&t;SELDMA[0]:1&t;&t;DMAREQ[0],DMAACK[0]&t;PIO[9:8]&n; *&t;SELDMA[3]:1&t;&t;DMAREQ[3],DMAACK[3]&t;PIO[15:14]&n; *&t;SELDONE:1&t;&t;DMADONE&t;&t;&t;PIO[7]&n; *&n; * Usable pins are:&n; *&t;RXD[1;0],TXD[1:0],CTS[0],RTS[0],&n; *&t;DMAREQ[0,2,3],DMAACK[0,2,3],DMADONE,PIO[0,10,11]&n; *&t;INT[3:0]&n; */
macro_line|#endif /* __ASM_TX3927_JMR3927_H */
eof
