multiline_comment|/*********************************************************************&n; *&n; *&t;vlsi_ir.h:&t;VLSI82C147 PCI IrDA controller driver for Linux&n; *&n; *&t;Version:&t;0.5&n; *&n; *&t;Copyright (c) 2001-2003 Martin Diehl&n; *&n; *&t;This program is free software; you can redistribute it and/or &n; *&t;modify it under the terms of the GNU General Public License as &n; *&t;published by the Free Software Foundation; either version 2 of &n; *&t;the License, or (at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License &n; *&t;along with this program; if not, write to the Free Software &n; *&t;Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *&t;MA 02111-1307 USA&n; *&n; ********************************************************************/
macro_line|#ifndef IRDA_VLSI_FIR_H
DECL|macro|IRDA_VLSI_FIR_H
mdefine_line|#define IRDA_VLSI_FIR_H
multiline_comment|/* ================================================================&n; * compatibility stuff&n; */
multiline_comment|/* definitions not present in pci_ids.h */
macro_line|#ifndef PCI_CLASS_WIRELESS_IRDA
DECL|macro|PCI_CLASS_WIRELESS_IRDA
mdefine_line|#define PCI_CLASS_WIRELESS_IRDA&t;&t;0x0d00
macro_line|#endif
macro_line|#ifndef PCI_CLASS_SUBCLASS_MASK
DECL|macro|PCI_CLASS_SUBCLASS_MASK
mdefine_line|#define PCI_CLASS_SUBCLASS_MASK&t;&t;0xffff
macro_line|#endif
multiline_comment|/* missing pci-dma api call to give streaming dma buffer back to hw&n; * patch was floating on lkml around 2.5.2x and might be present later.&n; * Defining it this way is ok, since the vlsi-ir is only&n; * used on two oldish x86-based notebooks which are cache-coherent&n; * (and flush_write_buffers also handles PPro errata and C3 OOstore)&n; */
macro_line|#ifdef CONFIG_X86
macro_line|#include &lt;asm-i386/io.h&gt;
DECL|macro|pci_dma_prep_single
mdefine_line|#define pci_dma_prep_single(dev, addr, size, direction)&t;flush_write_buffers()
macro_line|#else
macro_line|#error missing pci dma api call
macro_line|#endif
multiline_comment|/* in recent 2.5 interrupt handlers have non-void return value */
macro_line|#ifndef IRQ_RETVAL
DECL|typedef|irqreturn_t
r_typedef
r_void
id|irqreturn_t
suffix:semicolon
DECL|macro|IRQ_NONE
mdefine_line|#define IRQ_NONE
DECL|macro|IRQ_HANDLED
mdefine_line|#define IRQ_HANDLED
DECL|macro|IRQ_RETVAL
mdefine_line|#define IRQ_RETVAL(x)
macro_line|#endif
multiline_comment|/* some stuff need to check kernelversion. Not all 2.5 stuff was present&n; * in early 2.5.x - the test is merely to separate 2.4 from 2.5&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
multiline_comment|/* PDE() introduced in 2.5.4 */
macro_line|#ifdef CONFIG_PROC_FS
DECL|macro|PDE
mdefine_line|#define PDE(inode) ((inode)-&gt;u.generic_ip)
macro_line|#endif
multiline_comment|/* irda crc16 calculation exported in 2.5.42 */
DECL|macro|irda_calc_crc16
mdefine_line|#define irda_calc_crc16(fcs,buf,len)&t;(GOOD_FCS)
multiline_comment|/* we use this for unified pci device name access */
DECL|macro|PCIDEV_NAME
mdefine_line|#define PCIDEV_NAME(pdev)&t;((pdev)-&gt;name)
macro_line|#else /* 2.5 or later */
multiline_comment|/* recent 2.5/2.6 stores pci device names at varying places ;-) */
macro_line|#ifdef CONFIG_PCI_NAMES
multiline_comment|/* human readable name */
DECL|macro|PCIDEV_NAME
mdefine_line|#define PCIDEV_NAME(pdev)&t;((pdev)-&gt;pretty_name)
macro_line|#else
multiline_comment|/* whatever we get from the associated struct device - bus:slot:dev.fn id */
DECL|macro|PCIDEV_NAME
mdefine_line|#define PCIDEV_NAME(pdev)&t;(pci_name(pdev))
macro_line|#endif
macro_line|#endif
multiline_comment|/* ================================================================ */
multiline_comment|/* non-standard PCI registers */
DECL|enum|vlsi_pci_regs
r_enum
id|vlsi_pci_regs
(brace
DECL|enumerator|VLSI_PCI_CLKCTL
id|VLSI_PCI_CLKCTL
op_assign
l_int|0x40
comma
multiline_comment|/* chip clock input control */
DECL|enumerator|VLSI_PCI_MSTRPAGE
id|VLSI_PCI_MSTRPAGE
op_assign
l_int|0x41
comma
multiline_comment|/* addr [31:24] for all busmaster cycles */
DECL|enumerator|VLSI_PCI_IRMISC
id|VLSI_PCI_IRMISC
op_assign
l_int|0x42
multiline_comment|/* mainly legacy UART related */
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PCI_CLKCTL: Clock Control Register (u8, rw) */
multiline_comment|/* Three possible clock sources: either on-chip 48MHz PLL or&n; * external clock applied to EXTCLK pin. External clock may&n; * be either 48MHz or 40MHz, which is indicated by XCKSEL.&n; * CLKSTP controls whether the selected clock source gets&n; * connected to the IrDA block.&n; *&n; * On my HP OB-800 the BIOS sets external 40MHz clock as source&n; * when IrDA enabled and I&squot;ve never detected any PLL lock success.&n; * Apparently the 14.3...MHz OSC input required for the PLL to work&n; * is not connected and the 40MHz EXTCLK is provided externally.&n; * At least this is what makes the driver working for me.&n; */
DECL|enum|vlsi_pci_clkctl
r_enum
id|vlsi_pci_clkctl
(brace
multiline_comment|/* PLL control */
DECL|enumerator|CLKCTL_PD_INV
id|CLKCTL_PD_INV
op_assign
l_int|0x04
comma
multiline_comment|/* PD#: inverted power down signal,&n;&t;&t;&t;&t;&t;&t; * i.e. PLL is powered, if PD_INV set */
DECL|enumerator|CLKCTL_LOCK
id|CLKCTL_LOCK
op_assign
l_int|0x40
comma
multiline_comment|/* (ro) set, if PLL is locked */
multiline_comment|/* clock source selection */
DECL|enumerator|CLKCTL_EXTCLK
id|CLKCTL_EXTCLK
op_assign
l_int|0x20
comma
multiline_comment|/* set to select external clock input, not PLL */
DECL|enumerator|CLKCTL_XCKSEL
id|CLKCTL_XCKSEL
op_assign
l_int|0x10
comma
multiline_comment|/* set to indicate EXTCLK is 40MHz, not 48MHz */
multiline_comment|/* IrDA block control */
DECL|enumerator|CLKCTL_CLKSTP
id|CLKCTL_CLKSTP
op_assign
l_int|0x80
comma
multiline_comment|/* set to disconnect from selected clock source */
DECL|enumerator|CLKCTL_WAKE
id|CLKCTL_WAKE
op_assign
l_int|0x08
multiline_comment|/* set to enable wakeup feature: whenever IR activity&n;&t;&t;&t;&t;&t;&t; * is detected, PD_INV gets set(?) and CLKSTP cleared */
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PCI_MSTRPAGE: Master Page Register (u8, rw) and busmastering stuff */
DECL|macro|DMA_MASK_USED_BY_HW
mdefine_line|#define DMA_MASK_USED_BY_HW&t;0xffffffff
DECL|macro|DMA_MASK_MSTRPAGE
mdefine_line|#define DMA_MASK_MSTRPAGE&t;0x00ffffff
DECL|macro|MSTRPAGE_VALUE
mdefine_line|#define MSTRPAGE_VALUE&t;&t;(DMA_MASK_MSTRPAGE &gt;&gt; 24)
multiline_comment|/* PCI busmastering is somewhat special for this guy - in short:&n;&t; *&n;&t; * We select to operate using fixed MSTRPAGE=0, use ISA DMA&n;&t; * address restrictions to make the PCI BM api aware of this,&n;&t; * but ensure the hardware is dealing with real 32bit access.&n;&t; *&n;&t; * In detail:&n;&t; * The chip executes normal 32bit busmaster cycles, i.e.&n;&t; * drives all 32 address lines. These addresses however are&n;&t; * composed of [0:23] taken from various busaddr-pointers&n;&t; * and [24:31] taken from the MSTRPAGE register in the VLSI82C147&n;&t; * config space. Therefore _all_ busmastering must be&n;&t; * targeted to/from one single 16MB (busaddr-) superpage!&n;&t; * The point is to make sure all the allocations for memory&n;&t; * locations with busmaster access (ring descriptors, buffers)&n;&t; * are indeed bus-mappable to the same 16MB range (for x86 this&n;&t; * means they must reside in the same 16MB physical memory address&n;&t; * range). The only constraint we have which supports &quot;several objects&n;&t; * mappable to common 16MB range&quot; paradigma, is the old ISA DMA&n;&t; * restriction to the first 16MB of physical address range.&n;&t; * Hence the approach here is to enable PCI busmaster support using&n;&t; * the correct 32bit dma-mask used by the chip. Afterwards the device&squot;s&n;&t; * dma-mask gets restricted to 24bit, which must be honoured somehow by&n;&t; * all allocations for memory areas to be exposed to the chip ...&n;&t; *&n;&t; * Note:&n;&t; * Don&squot;t be surprised to get &quot;Setting latency timer...&quot; messages every&n;&t; * time when PCI busmastering is enabled for the chip.&n;&t; * The chip has its PCI latency timer RO fixed at 0 - which is not a&n;&t; * problem here, because it is never requesting _burst_ transactions.&n;&t; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PCIIRMISC: IR Miscellaneous Register (u8, rw) */
multiline_comment|/* legacy UART emulation - not used by this driver - would require:&n; * (see below for some register-value definitions)&n; *&n; *&t;- IRMISC_UARTEN must be set to enable UART address decoding&n; *&t;- IRMISC_UARTSEL configured&n; *&t;- IRCFG_MASTER must be cleared&n; *&t;- IRCFG_SIR must be set&n; *&t;- IRENABLE_PHYANDCLOCK must be asserted 0-&gt;1 (and hence IRENABLE_SIR_ON)&n; */
DECL|enum|vlsi_pci_irmisc
r_enum
id|vlsi_pci_irmisc
(brace
multiline_comment|/* IR transceiver control */
DECL|enumerator|IRMISC_IRRAIL
id|IRMISC_IRRAIL
op_assign
l_int|0x40
comma
multiline_comment|/* (ro?) IR rail power indication (and control?)&n;&t;&t;&t;&t;&t;&t; * 0=3.3V / 1=5V. Probably set during power-on?&n;&t;&t;&t;&t;&t;&t; * unclear - not touched by driver */
DECL|enumerator|IRMISC_IRPD
id|IRMISC_IRPD
op_assign
l_int|0x08
comma
multiline_comment|/* transceiver power down, if set */
multiline_comment|/* legacy UART control */
DECL|enumerator|IRMISC_UARTTST
id|IRMISC_UARTTST
op_assign
l_int|0x80
comma
multiline_comment|/* UART test mode - &quot;always write 0&quot; */
DECL|enumerator|IRMISC_UARTEN
id|IRMISC_UARTEN
op_assign
l_int|0x04
comma
multiline_comment|/* enable UART address decoding */
multiline_comment|/* bits [1:0] IRMISC_UARTSEL to select legacy UART address */
DECL|enumerator|IRMISC_UARTSEL_3f8
id|IRMISC_UARTSEL_3f8
op_assign
l_int|0x00
comma
DECL|enumerator|IRMISC_UARTSEL_2f8
id|IRMISC_UARTSEL_2f8
op_assign
l_int|0x01
comma
DECL|enumerator|IRMISC_UARTSEL_3e8
id|IRMISC_UARTSEL_3e8
op_assign
l_int|0x02
comma
DECL|enumerator|IRMISC_UARTSEL_2e8
id|IRMISC_UARTSEL_2e8
op_assign
l_int|0x03
)brace
suffix:semicolon
multiline_comment|/* ================================================================ */
multiline_comment|/* registers mapped to 32 byte PCI IO space */
multiline_comment|/* note: better access all registers at the indicated u8/u16 size&n; *&t; although some of them contain only 1 byte of information.&n; *&t; some of them (particaluarly PROMPT and IRCFG) ignore&n; *&t; access when using the wrong addressing mode!&n; */
DECL|enum|vlsi_pio_regs
r_enum
id|vlsi_pio_regs
(brace
DECL|enumerator|VLSI_PIO_IRINTR
id|VLSI_PIO_IRINTR
op_assign
l_int|0x00
comma
multiline_comment|/* interrupt enable/request (u8, rw) */
DECL|enumerator|VLSI_PIO_RINGPTR
id|VLSI_PIO_RINGPTR
op_assign
l_int|0x02
comma
multiline_comment|/* rx/tx ring pointer (u16, ro) */
DECL|enumerator|VLSI_PIO_RINGBASE
id|VLSI_PIO_RINGBASE
op_assign
l_int|0x04
comma
multiline_comment|/* [23:10] of ring address (u16, rw) */
DECL|enumerator|VLSI_PIO_RINGSIZE
id|VLSI_PIO_RINGSIZE
op_assign
l_int|0x06
comma
multiline_comment|/* rx/tx ring size (u16, rw) */
DECL|enumerator|VLSI_PIO_PROMPT
id|VLSI_PIO_PROMPT
op_assign
l_int|0x08
comma
multiline_comment|/* triggers ring processing (u16, wo) */
multiline_comment|/* 0x0a-0x0f: reserved / duplicated UART regs */
DECL|enumerator|VLSI_PIO_IRCFG
id|VLSI_PIO_IRCFG
op_assign
l_int|0x10
comma
multiline_comment|/* configuration select (u16, rw) */
DECL|enumerator|VLSI_PIO_SIRFLAG
id|VLSI_PIO_SIRFLAG
op_assign
l_int|0x12
comma
multiline_comment|/* BOF/EOF for filtered SIR (u16, ro) */
DECL|enumerator|VLSI_PIO_IRENABLE
id|VLSI_PIO_IRENABLE
op_assign
l_int|0x14
comma
multiline_comment|/* enable and status register (u16, rw/ro) */
DECL|enumerator|VLSI_PIO_PHYCTL
id|VLSI_PIO_PHYCTL
op_assign
l_int|0x16
comma
multiline_comment|/* physical layer current status (u16, ro) */
DECL|enumerator|VLSI_PIO_NPHYCTL
id|VLSI_PIO_NPHYCTL
op_assign
l_int|0x18
comma
multiline_comment|/* next physical layer select (u16, rw) */
DECL|enumerator|VLSI_PIO_MAXPKT
id|VLSI_PIO_MAXPKT
op_assign
l_int|0x1a
comma
multiline_comment|/* [11:0] max len for packet receive (u16, rw) */
DECL|enumerator|VLSI_PIO_RCVBCNT
id|VLSI_PIO_RCVBCNT
op_assign
l_int|0x1c
multiline_comment|/* current receive-FIFO byte count (u16, ro) */
multiline_comment|/* 0x1e-0x1f: reserved / duplicated UART regs */
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_IRINTR: Interrupt Register (u8, rw) */
multiline_comment|/* enable-bits:&n; *&t;&t;1 = enable / 0 = disable&n; * interrupt condition bits:&n; * &t;&t;set according to corresponding interrupt source&n; *&t;&t;(regardless of the state of the enable bits)&n; *&t;&t;enable bit status indicates whether interrupt gets raised&n; *&t;&t;write-to-clear&n; * note: RPKTINT and TPKTINT behave different in legacy UART mode (which we don&squot;t use :-)&n; */
DECL|enum|vlsi_pio_irintr
r_enum
id|vlsi_pio_irintr
(brace
DECL|enumerator|IRINTR_ACTEN
id|IRINTR_ACTEN
op_assign
l_int|0x80
comma
multiline_comment|/* activity interrupt enable */
DECL|enumerator|IRINTR_ACTIVITY
id|IRINTR_ACTIVITY
op_assign
l_int|0x40
comma
multiline_comment|/* activity monitor (traffic detected) */
DECL|enumerator|IRINTR_RPKTEN
id|IRINTR_RPKTEN
op_assign
l_int|0x20
comma
multiline_comment|/* receive packet interrupt enable*/
DECL|enumerator|IRINTR_RPKTINT
id|IRINTR_RPKTINT
op_assign
l_int|0x10
comma
multiline_comment|/* rx-packet transfered from fifo to memory finished */
DECL|enumerator|IRINTR_TPKTEN
id|IRINTR_TPKTEN
op_assign
l_int|0x08
comma
multiline_comment|/* transmit packet interrupt enable */
DECL|enumerator|IRINTR_TPKTINT
id|IRINTR_TPKTINT
op_assign
l_int|0x04
comma
multiline_comment|/* last bit of tx-packet+crc shifted to ir-pulser */
DECL|enumerator|IRINTR_OE_EN
id|IRINTR_OE_EN
op_assign
l_int|0x02
comma
multiline_comment|/* UART rx fifo overrun error interrupt enable */
DECL|enumerator|IRINTR_OE_INT
id|IRINTR_OE_INT
op_assign
l_int|0x01
multiline_comment|/* UART rx fifo overrun error (read LSR to clear) */
)brace
suffix:semicolon
multiline_comment|/* we use this mask to check whether the (shared PCI) interrupt is ours */
DECL|macro|IRINTR_INT_MASK
mdefine_line|#define IRINTR_INT_MASK&t;&t;(IRINTR_ACTIVITY|IRINTR_RPKTINT|IRINTR_TPKTINT)
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_RINGPTR: Ring Pointer Read-Back Register (u16, ro) */
multiline_comment|/* _both_ ring pointers are indices relative to the _entire_ rx,tx-ring!&n; * i.e. the referenced descriptor is located&n; * at RINGBASE + PTR * sizeof(descr) for rx and tx&n; * therefore, the tx-pointer has offset MAX_RING_DESCR&n; */
DECL|macro|MAX_RING_DESCR
mdefine_line|#define MAX_RING_DESCR&t;&t;64&t;/* tx, rx rings may contain up to 64 descr each */
DECL|macro|RINGPTR_RX_MASK
mdefine_line|#define RINGPTR_RX_MASK&t;&t;(MAX_RING_DESCR-1)
DECL|macro|RINGPTR_TX_MASK
mdefine_line|#define RINGPTR_TX_MASK&t;&t;((MAX_RING_DESCR-1)&lt;&lt;8)
DECL|macro|RINGPTR_GET_RX
mdefine_line|#define RINGPTR_GET_RX(p)&t;((p)&amp;RINGPTR_RX_MASK)
DECL|macro|RINGPTR_GET_TX
mdefine_line|#define RINGPTR_GET_TX(p)&t;(((p)&amp;RINGPTR_TX_MASK)&gt;&gt;8)
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_RINGBASE: Ring Pointer Base Address Register (u16, ro) */
multiline_comment|/* Contains [23:10] part of the ring base (bus-) address&n; * which must be 1k-alinged. [31:24] is taken from&n; * VLSI_PCI_MSTRPAGE above.&n; * The controller initiates non-burst PCI BM cycles to&n; * fetch and update the descriptors in the ring.&n; * Once fetched, the descriptor remains cached onchip&n; * until it gets closed and updated due to the ring&n; * processing state machine.&n; * The entire ring area is split in rx and tx areas with each&n; * area consisting of 64 descriptors of 8 bytes each.&n; * The rx(tx) ring is located at ringbase+0 (ringbase+64*8).&n; */
DECL|macro|BUS_TO_RINGBASE
mdefine_line|#define BUS_TO_RINGBASE(p)&t;(((p)&gt;&gt;10)&amp;0x3fff)
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_RINGSIZE: Ring Size Register (u16, rw) */
multiline_comment|/* bit mask to indicate the ring size to be used for rx and tx.&n; * &t;possible values&t;&t;encoded bits&n; *&t;&t; 4&t;&t;   0000&n; *&t;&t; 8&t;&t;   0001&n; *&t;&t;16&t;&t;   0011&n; *&t;&t;32&t;&t;   0111&n; *&t;&t;64&t;&t;   1111&n; * located at [15:12] for tx and [11:8] for rx ([7:0] unused)&n; *&n; * note: probably a good idea to have IRCFG_MSTR cleared when writing&n; *&t; this so the state machines are stopped and the RINGPTR is reset!&n; */
DECL|macro|SIZE_TO_BITS
mdefine_line|#define SIZE_TO_BITS(num)&t;&t;((((num)-1)&gt;&gt;2)&amp;0x0f)
DECL|macro|TX_RX_TO_RINGSIZE
mdefine_line|#define TX_RX_TO_RINGSIZE(tx,rx)&t;((SIZE_TO_BITS(tx)&lt;&lt;12)|(SIZE_TO_BITS(rx)&lt;&lt;8))
DECL|macro|RINGSIZE_TO_RXSIZE
mdefine_line|#define RINGSIZE_TO_RXSIZE(rs)&t;&t;((((rs)&amp;0x0f00)&gt;&gt;6)+4)
DECL|macro|RINGSIZE_TO_TXSIZE
mdefine_line|#define RINGSIZE_TO_TXSIZE(rs)&t;&t;((((rs)&amp;0xf000)&gt;&gt;10)+4)
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_PROMPT: Ring Prompting Register (u16, write-to-start) */
multiline_comment|/* writing any value kicks the ring processing state machines&n; * for both tx, rx rings as follows:&n; * &t;- active rings (currently owning an active descriptor)&n; *&t;  ignore the prompt and continue&n; *&t;- idle rings fetch the next descr from the ring and start&n; *&t;  their processing&n; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_IRCFG: IR Config Register (u16, rw) */
multiline_comment|/* notes:&n; *&t;- not more than one SIR/MIR/FIR bit must be set at any time&n; *&t;- SIR, MIR, FIR and CRC16 select the configuration which will&n; *&t;  be applied on next 0-&gt;1 transition of IRENABLE_PHYANDCLOCK (see below).&n; *&t;- besides allowing the PCI interface to execute busmaster cycles&n; *&t;  and therefore the ring SM to operate, the MSTR bit has side-effects:&n; *&t;  when MSTR is cleared, the RINGPTR&squot;s get reset and the legacy UART mode&n; *&t;  (in contrast to busmaster access mode) gets enabled.&n; *&t;- clearing ENRX or setting ENTX while data is received may stall the&n; *&t;  receive fifo until ENRX reenabled _and_ another packet arrives&n; *&t;- SIRFILT means the chip performs the required unwrapping of hardware&n; *&t;  headers (XBOF&squot;s, BOF/EOF) and un-escaping in the _receive_ direction.&n; *&t;  Only the resulting IrLAP payload is copied to the receive buffers -&n; *&t;  but with the 16bit FCS still encluded. Question remains, whether it&n; *&t;  was already checked or we should do it before passing the packet to IrLAP?&n; */
DECL|enum|vlsi_pio_ircfg
r_enum
id|vlsi_pio_ircfg
(brace
DECL|enumerator|IRCFG_LOOP
id|IRCFG_LOOP
op_assign
l_int|0x4000
comma
multiline_comment|/* enable loopback test mode */
DECL|enumerator|IRCFG_ENTX
id|IRCFG_ENTX
op_assign
l_int|0x1000
comma
multiline_comment|/* transmit enable */
DECL|enumerator|IRCFG_ENRX
id|IRCFG_ENRX
op_assign
l_int|0x0800
comma
multiline_comment|/* receive enable */
DECL|enumerator|IRCFG_MSTR
id|IRCFG_MSTR
op_assign
l_int|0x0400
comma
multiline_comment|/* master enable */
DECL|enumerator|IRCFG_RXANY
id|IRCFG_RXANY
op_assign
l_int|0x0200
comma
multiline_comment|/* receive any packet */
DECL|enumerator|IRCFG_CRC16
id|IRCFG_CRC16
op_assign
l_int|0x0080
comma
multiline_comment|/* 16bit (not 32bit) CRC select for MIR/FIR */
DECL|enumerator|IRCFG_FIR
id|IRCFG_FIR
op_assign
l_int|0x0040
comma
multiline_comment|/* FIR 4PPM encoding mode enable */
DECL|enumerator|IRCFG_MIR
id|IRCFG_MIR
op_assign
l_int|0x0020
comma
multiline_comment|/* MIR HDLC encoding mode enable */
DECL|enumerator|IRCFG_SIR
id|IRCFG_SIR
op_assign
l_int|0x0010
comma
multiline_comment|/* SIR encoding mode enable */
DECL|enumerator|IRCFG_SIRFILT
id|IRCFG_SIRFILT
op_assign
l_int|0x0008
comma
multiline_comment|/* enable SIR decode filter (receiver unwrapping) */
DECL|enumerator|IRCFG_SIRTEST
id|IRCFG_SIRTEST
op_assign
l_int|0x0004
comma
multiline_comment|/* allow SIR decode filter when not in SIR mode */
DECL|enumerator|IRCFG_TXPOL
id|IRCFG_TXPOL
op_assign
l_int|0x0002
comma
multiline_comment|/* invert tx polarity when set */
DECL|enumerator|IRCFG_RXPOL
id|IRCFG_RXPOL
op_assign
l_int|0x0001
multiline_comment|/* invert rx polarity when set */
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_SIRFLAG: SIR Flag Register (u16, ro) */
multiline_comment|/* register contains hardcoded BOF=0xc0 at [7:0] and EOF=0xc1 at [15:8]&n; * which is used for unwrapping received frames in SIR decode-filter mode&n; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_IRENABLE: IR Enable Register (u16, rw/ro) */
multiline_comment|/* notes:&n; *&t;- IREN acts as gate for latching the configured IR mode information&n; *&t;  from IRCFG and IRPHYCTL when IREN=reset and applying them when&n; *&t;  IREN gets set afterwards.&n; *&t;- ENTXST reflects IRCFG_ENTX&n; *&t;- ENRXST = IRCFG_ENRX &amp;&amp; (!IRCFG_ENTX || IRCFG_LOOP)&n; */
DECL|enum|vlsi_pio_irenable
r_enum
id|vlsi_pio_irenable
(brace
DECL|enumerator|IRENABLE_PHYANDCLOCK
id|IRENABLE_PHYANDCLOCK
op_assign
l_int|0x8000
comma
multiline_comment|/* enable IR phy and gate the mode config (rw) */
DECL|enumerator|IRENABLE_CFGER
id|IRENABLE_CFGER
op_assign
l_int|0x4000
comma
multiline_comment|/* mode configuration error (ro) */
DECL|enumerator|IRENABLE_FIR_ON
id|IRENABLE_FIR_ON
op_assign
l_int|0x2000
comma
multiline_comment|/* FIR on status (ro) */
DECL|enumerator|IRENABLE_MIR_ON
id|IRENABLE_MIR_ON
op_assign
l_int|0x1000
comma
multiline_comment|/* MIR on status (ro) */
DECL|enumerator|IRENABLE_SIR_ON
id|IRENABLE_SIR_ON
op_assign
l_int|0x0800
comma
multiline_comment|/* SIR on status (ro) */
DECL|enumerator|IRENABLE_ENTXST
id|IRENABLE_ENTXST
op_assign
l_int|0x0400
comma
multiline_comment|/* transmit enable status (ro) */
DECL|enumerator|IRENABLE_ENRXST
id|IRENABLE_ENRXST
op_assign
l_int|0x0200
comma
multiline_comment|/* Receive enable status (ro) */
DECL|enumerator|IRENABLE_CRC16_ON
id|IRENABLE_CRC16_ON
op_assign
l_int|0x0100
multiline_comment|/* 16bit (not 32bit) CRC enabled status (ro) */
)brace
suffix:semicolon
DECL|macro|IRENABLE_MASK
mdefine_line|#define&t;  IRENABLE_MASK&t;    0xff00  /* Read mask */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_PHYCTL: IR Physical Layer Current Control Register (u16, ro) */
multiline_comment|/* read-back of the currently applied physical layer status.&n; * applied from VLSI_PIO_NPHYCTL at rising edge of IRENABLE_PHYANDCLOCK&n; * contents identical to VLSI_PIO_NPHYCTL (see below)&n; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_NPHYCTL: IR Physical Layer Next Control Register (u16, rw) */
multiline_comment|/* latched during IRENABLE_PHYANDCLOCK=0 and applied at 0-1 transition&n; *&n; * consists of BAUD[15:10], PLSWID[9:5] and PREAMB[4:0] bits defined as follows:&n; *&n; * SIR-mode:&t;BAUD = (115.2kHz / baudrate) - 1&n; *&t;&t;PLSWID = (pulsetime * freq / (BAUD+1)) - 1&n; *&t;&t;&t;where pulsetime is the requested IrPHY pulse width&n; *&t;&t;&t;and freq is 8(16)MHz for 40(48)MHz primary input clock&n; *&t;&t;PREAMB: don&squot;t care for SIR&n; *&n; *&t;&t;The nominal SIR pulse width is 3/16 bit time so we have PLSWID=12&n; *&t;&t;fixed for all SIR speeds at 40MHz input clock (PLSWID=24 at 48MHz).&n; *&t;&t;IrPHY also allows shorter pulses down to the nominal pulse duration&n; *&t;&t;at 115.2kbaud (minus some tolerance) which is 1.41 usec.&n; *&t;&t;Using the expression PLSWID = 12/(BAUD+1)-1 (multiplied by two for 48MHz)&n; *&t;&t;we get the minimum acceptable PLSWID values according to the VLSI&n; *&t;&t;specification, which provides 1.5 usec pulse width for all speeds (except&n; *&t;&t;for 2.4kbaud getting 6usec). This is fine with IrPHY v1.3 specs and&n; *&t;&t;reduces the transceiver power which drains the battery. At 9.6kbaud for&n; *&t;&t;example this amounts to more than 90% battery power saving!&n; *&n; * MIR-mode:&t;BAUD = 0&n; *&t;&t;PLSWID = 9(10) for 40(48) MHz input clock&n; *&t;&t;&t;to get nominal MIR pulse width&n; *&t;&t;PREAMB = 1&n; *&n; * FIR-mode:&t;BAUD = 0&n; *&t;&t;PLSWID: don&squot;t care&n; *&t;&t;PREAMB = 15&n; */
DECL|macro|PHYCTL_BAUD_SHIFT
mdefine_line|#define PHYCTL_BAUD_SHIFT&t;10
DECL|macro|PHYCTL_BAUD_MASK
mdefine_line|#define PHYCTL_BAUD_MASK&t;0xfc00
DECL|macro|PHYCTL_PLSWID_SHIFT
mdefine_line|#define PHYCTL_PLSWID_SHIFT&t;5
DECL|macro|PHYCTL_PLSWID_MASK
mdefine_line|#define PHYCTL_PLSWID_MASK&t;0x03e0
DECL|macro|PHYCTL_PREAMB_SHIFT
mdefine_line|#define PHYCTL_PREAMB_SHIFT&t;0
DECL|macro|PHYCTL_PREAMB_MASK
mdefine_line|#define PHYCTL_PREAMB_MASK&t;0x001f
DECL|macro|PHYCTL_TO_BAUD
mdefine_line|#define PHYCTL_TO_BAUD(bwp)&t;(((bwp)&amp;PHYCTL_BAUD_MASK)&gt;&gt;PHYCTL_BAUD_SHIFT)
DECL|macro|PHYCTL_TO_PLSWID
mdefine_line|#define PHYCTL_TO_PLSWID(bwp)&t;(((bwp)&amp;PHYCTL_PLSWID_MASK)&gt;&gt;PHYCTL_PLSWID_SHIFT)
DECL|macro|PHYCTL_TO_PREAMB
mdefine_line|#define PHYCTL_TO_PREAMB(bwp)&t;(((bwp)&amp;PHYCTL_PREAMB_MASK)&gt;&gt;PHYCTL_PREAMB_SHIFT)
DECL|macro|BWP_TO_PHYCTL
mdefine_line|#define BWP_TO_PHYCTL(b,w,p)&t;((((b)&lt;&lt;PHYCTL_BAUD_SHIFT)&amp;PHYCTL_BAUD_MASK) &bslash;&n;&t;&t;&t;&t; | (((w)&lt;&lt;PHYCTL_PLSWID_SHIFT)&amp;PHYCTL_PLSWID_MASK) &bslash;&n;&t;&t;&t;&t; | (((p)&lt;&lt;PHYCTL_PREAMB_SHIFT)&amp;PHYCTL_PREAMB_MASK))
DECL|macro|BAUD_BITS
mdefine_line|#define BAUD_BITS(br)&t;&t;((115200/(br))-1)
r_static
r_inline
r_int
DECL|function|calc_width_bits
id|calc_width_bits
c_func
(paren
r_int
id|baudrate
comma
r_int
id|widthselect
comma
r_int
id|clockselect
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|widthselect
)paren
multiline_comment|/* nominal 3/16 puls width */
r_return
(paren
id|clockselect
)paren
ques
c_cond
l_int|12
suffix:colon
l_int|24
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|clockselect
)paren
ques
c_cond
l_int|12
suffix:colon
l_int|24
)paren
op_div
(paren
id|BAUD_BITS
c_func
(paren
id|baudrate
)paren
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* intermediate result of integer division needed here */
r_return
(paren
id|tmp
OG
l_int|0
)paren
ques
c_cond
(paren
id|tmp
op_minus
l_int|1
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|macro|PHYCTL_SIR
mdefine_line|#define PHYCTL_SIR(br,ws,cs)&t;BWP_TO_PHYCTL(BAUD_BITS(br),calc_width_bits((br),(ws),(cs)),0)
DECL|macro|PHYCTL_MIR
mdefine_line|#define PHYCTL_MIR(cs)&t;&t;BWP_TO_PHYCTL(0,((cs)?9:10),1)
DECL|macro|PHYCTL_FIR
mdefine_line|#define PHYCTL_FIR&t;&t;BWP_TO_PHYCTL(0,0,15)
multiline_comment|/* quite ugly, I know. But implementing these calculations here avoids&n; * having magic numbers in the code and allows some playing with pulsewidths&n; * without risk to violate the standards.&n; * FWIW, here is the table for reference:&n; *&n; * baudrate&t;BAUD&t;min-PLSWID&t;nom-PLSWID&t;PREAMB&n; *     2400&t;  47&t;   0(0)&t;&t;   12(24)&t;   0&n; *     9600&t;  11&t;   0(0)&t;&t;   12(24)&t;   0&n; *    19200&t;   5&t;   1(2)&t;&t;   12(24)&t;   0&n; *    38400&t;   2&t;   3(6)&t;           12(24)&t;   0&n; *    57600&t;   1&t;   5(10)&t;   12(24)&t;   0&n; *   115200&t;   0&t;  11(22)&t;   12(24)&t;   0&n; *&t;MIR&t;   0&t;    -&t;&t;    9(10)&t;   1&n; *&t;FIR&t;   0        -               0&t;&t;  15&n; *&n; * note: x(y) means x-value for 40MHz / y-value for 48MHz primary input clock&n; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_MAXPKT: Maximum Packet Length register (u16, rw) */
multiline_comment|/* maximum acceptable length for received packets */
multiline_comment|/* hw imposed limitation - register uses only [11:0] */
DECL|macro|MAX_PACKET_LENGTH
mdefine_line|#define MAX_PACKET_LENGTH&t;0x0fff
multiline_comment|/* IrLAP I-field (apparently not defined elsewhere) */
DECL|macro|IRDA_MTU
mdefine_line|#define IRDA_MTU&t;&t;2048
multiline_comment|/* complete packet consists of A(1)+C(1)+I(&lt;=IRDA_MTU) */
DECL|macro|IRLAP_SKB_ALLOCSIZE
mdefine_line|#define IRLAP_SKB_ALLOCSIZE&t;(1+1+IRDA_MTU)
multiline_comment|/* the buffers we use to exchange frames with the hardware need to be&n; * larger than IRLAP_SKB_ALLOCSIZE because we may have up to 4 bytes FCS&n; * appended and, in SIR mode, a lot of frame wrapping bytes. The worst&n; * case appears to be a SIR packet with I-size==IRDA_MTU and all bytes&n; * requiring to be escaped to provide transparency. Furthermore, the peer&n; * might ask for quite a number of additional XBOFs:&n; *&t;up to 115+48 XBOFS&t;&t; 163&n; *&t;regular BOF&t;&t;&t;   1&n; *&t;A-field&t;&t;&t;&t;   1&n; *&t;C-field&t;&t;&t;&t;   1&n; *&t;I-field, IRDA_MTU, all escaped&t;4096&n; *&t;FCS (16 bit at SIR, escaped)&t;   4&n; *&t;EOF&t;&t;&t;&t;   1&n; * AFAICS nothing in IrLAP guarantees A/C field not to need escaping&n; * (f.e. 0xc0/0xc1 - i.e. BOF/EOF - are legal values there) so in the&n; * worst case we have 4269 bytes total frame size.&n; * However, the VLSI uses 12 bits only for all buffer length values,&n; * which limits the maximum useable buffer size &lt;= 4095.&n; * Note this is not a limitation in the receive case because we use&n; * the SIR filtering mode where the hw unwraps the frame and only the&n; * bare packet+fcs is stored into the buffer - in contrast to the SIR&n; * tx case where we have to pass frame-wrapped packets to the hw.&n; * If this would ever become an issue in real life, the only workaround&n; * I see would be using the legacy UART emulation in SIR mode.&n; */
DECL|macro|XFER_BUF_SIZE
mdefine_line|#define XFER_BUF_SIZE&t;&t;MAX_PACKET_LENGTH
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_RCVBCNT: Receive Byte Count Register (u16, ro) */
multiline_comment|/* receive packet counter gets incremented on every non-filtered&n; * byte which was put in the receive fifo and reset for each&n; * new packet. Used to decide whether we are just in the middle&n; * of receiving&n; */
multiline_comment|/* better apply the [11:0] mask when reading, as some docs say the&n; * reserved [15:12] would return 1 when reading - which is wrong AFAICS&n; */
DECL|macro|RCVBCNT_MASK
mdefine_line|#define RCVBCNT_MASK&t;0x0fff
multiline_comment|/******************************************************************/
multiline_comment|/* descriptors for rx/tx ring&n; *&n; * accessed by hardware - don&squot;t change!&n; *&n; * the descriptor is owned by hardware, when the ACTIVE status bit&n; * is set and nothing (besides reading status to test the bit)&n; * shall be done. The bit gets cleared by hw, when the descriptor&n; * gets closed. Premature reaping of descriptors owned be the chip&n; * can be achieved by disabling IRCFG_MSTR&n; *&n; * Attention: Writing addr overwrites status!&n; *&n; * ### FIXME: depends on endianess (but there ain&squot;t no non-i586 ob800 ;-)&n; */
DECL|struct|ring_descr_hw
r_struct
id|ring_descr_hw
(brace
DECL|member|rd_count
r_volatile
id|u16
id|rd_count
suffix:semicolon
multiline_comment|/* tx/rx count [11:0] */
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
r_union
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
multiline_comment|/* [23:0] of the buffer&squot;s busaddress */
r_struct
(brace
DECL|member|addr_res
id|u8
id|addr_res
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|status
r_volatile
id|u8
id|status
suffix:semicolon
multiline_comment|/* descriptor status */
DECL|member|rd_s
)brace
id|rd_s
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
id|rd_u
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|rd_addr
mdefine_line|#define rd_addr&t;&t;rd_u.addr
DECL|macro|rd_status
mdefine_line|#define rd_status&t;rd_u.rd_s.status
multiline_comment|/* ring descriptor status bits */
DECL|macro|RD_ACTIVE
mdefine_line|#define RD_ACTIVE&t;&t;0x80&t;/* descriptor owned by hw (both TX,RX) */
multiline_comment|/* TX ring descriptor status */
DECL|macro|RD_TX_DISCRC
mdefine_line|#define&t;RD_TX_DISCRC&t;&t;0x40&t;/* do not send CRC (for SIR) */
DECL|macro|RD_TX_BADCRC
mdefine_line|#define&t;RD_TX_BADCRC&t;&t;0x20&t;/* force a bad CRC */
DECL|macro|RD_TX_PULSE
mdefine_line|#define&t;RD_TX_PULSE&t;&t;0x10&t;/* send indication pulse after this frame (MIR/FIR) */
DECL|macro|RD_TX_FRCEUND
mdefine_line|#define&t;RD_TX_FRCEUND&t;&t;0x08&t;/* force underrun */
DECL|macro|RD_TX_CLRENTX
mdefine_line|#define&t;RD_TX_CLRENTX&t;&t;0x04&t;/* clear ENTX after this frame */
DECL|macro|RD_TX_UNDRN
mdefine_line|#define&t;RD_TX_UNDRN&t;&t;0x01&t;/* TX fifo underrun (probably PCI problem) */
multiline_comment|/* RX ring descriptor status */
DECL|macro|RD_RX_PHYERR
mdefine_line|#define RD_RX_PHYERR&t;&t;0x40&t;/* physical encoding error */
DECL|macro|RD_RX_CRCERR
mdefine_line|#define RD_RX_CRCERR&t;&t;0x20&t;/* CRC error (MIR/FIR) */
DECL|macro|RD_RX_LENGTH
mdefine_line|#define RD_RX_LENGTH&t;&t;0x10&t;/* frame exceeds buffer length */
DECL|macro|RD_RX_OVER
mdefine_line|#define RD_RX_OVER&t;&t;0x08&t;/* RX fifo overrun (probably PCI problem) */
DECL|macro|RD_RX_SIRBAD
mdefine_line|#define RD_RX_SIRBAD&t;&t;0x04&t;/* EOF missing: BOF follows BOF (SIR, filtered) */
DECL|macro|RD_RX_ERROR
mdefine_line|#define RD_RX_ERROR&t;&t;0x7c&t;/* any error in received frame */
multiline_comment|/* the memory required to hold the 2 descriptor rings */
DECL|macro|HW_RING_AREA_SIZE
mdefine_line|#define HW_RING_AREA_SIZE&t;(2 * MAX_RING_DESCR * sizeof(struct ring_descr_hw))
multiline_comment|/******************************************************************/
multiline_comment|/* sw-ring descriptors consists of a bus-mapped transfer buffer with&n; * associated skb and a pointer to the hw entry descriptor&n; */
DECL|struct|ring_descr
r_struct
id|ring_descr
(brace
DECL|member|hw
r_struct
id|ring_descr_hw
op_star
id|hw
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* wrappers for operations on hw-exposed ring descriptors&n; * access to the hw-part of the descriptors must use these.&n; */
DECL|function|rd_is_active
r_static
r_inline
r_int
id|rd_is_active
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
)paren
(brace
r_return
(paren
(paren
id|rd-&gt;hw-&gt;rd_status
op_amp
id|RD_ACTIVE
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|rd_activate
r_static
r_inline
r_void
id|rd_activate
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
)paren
(brace
id|rd-&gt;hw-&gt;rd_status
op_or_assign
id|RD_ACTIVE
suffix:semicolon
)brace
DECL|function|rd_set_status
r_static
r_inline
r_void
id|rd_set_status
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
comma
id|u8
id|s
)paren
(brace
id|rd-&gt;hw-&gt;rd_status
op_assign
id|s
suffix:semicolon
multiline_comment|/* may pass ownership to the hardware */
)brace
DECL|function|rd_set_addr_status
r_static
r_inline
r_void
id|rd_set_addr_status
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
comma
id|dma_addr_t
id|a
comma
id|u8
id|s
)paren
(brace
multiline_comment|/* order is important for two reasons:&n;&t; *  - overlayed: writing addr overwrites status&n;&t; *  - we want to write status last so we have valid address in&n;&t; *    case status has RD_ACTIVE set&n;&t; */
r_if
c_cond
(paren
(paren
id|a
op_amp
op_complement
id|DMA_MASK_MSTRPAGE
)paren
op_rshift
l_int|24
op_ne
id|MSTRPAGE_VALUE
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;%s: pci busaddr inconsistency!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|a
op_and_assign
id|DMA_MASK_MSTRPAGE
suffix:semicolon
multiline_comment|/* clear highbyte to make sure we won&squot;t write&n;&t;&t;&t;&t;  * to status - just in case MSTRPAGE_VALUE!=0&n;&t;&t;&t;&t;  */
id|rd-&gt;hw-&gt;rd_addr
op_assign
id|cpu_to_le32
c_func
(paren
id|a
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|rd_set_status
c_func
(paren
id|rd
comma
id|s
)paren
suffix:semicolon
multiline_comment|/* may pass ownership to the hardware */
)brace
DECL|function|rd_set_count
r_static
r_inline
r_void
id|rd_set_count
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
comma
id|u16
id|c
)paren
(brace
id|rd-&gt;hw-&gt;rd_count
op_assign
id|cpu_to_le16
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|rd_get_status
r_static
r_inline
id|u8
id|rd_get_status
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
)paren
(brace
r_return
id|rd-&gt;hw-&gt;rd_status
suffix:semicolon
)brace
DECL|function|rd_get_addr
r_static
r_inline
id|dma_addr_t
id|rd_get_addr
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
)paren
(brace
id|dma_addr_t
id|a
suffix:semicolon
id|a
op_assign
id|le32_to_cpu
c_func
(paren
id|rd-&gt;hw-&gt;rd_addr
)paren
suffix:semicolon
r_return
(paren
id|a
op_amp
id|DMA_MASK_MSTRPAGE
)paren
op_or
(paren
id|MSTRPAGE_VALUE
op_lshift
l_int|24
)paren
suffix:semicolon
)brace
DECL|function|rd_get_count
r_static
r_inline
id|u16
id|rd_get_count
c_func
(paren
r_struct
id|ring_descr
op_star
id|rd
)paren
(brace
r_return
id|le16_to_cpu
c_func
(paren
id|rd-&gt;hw-&gt;rd_count
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************/
multiline_comment|/* sw descriptor rings for rx, tx:&n; *&n; * operations follow producer-consumer paradigm, with the hw&n; * in the middle doing the processing.&n; * ring size must be power of two.&n; *&n; * producer advances r-&gt;tail after inserting for processing&n; * consumer advances r-&gt;head after removing processed rd&n; * ring is empty if head==tail / full if (tail+1)==head&n; */
DECL|struct|vlsi_ring
r_struct
id|vlsi_ring
(brace
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|dir
r_int
id|dir
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|mask
r_int
id|mask
suffix:semicolon
DECL|member|head
DECL|member|tail
id|atomic_t
id|head
comma
id|tail
suffix:semicolon
DECL|member|rd
r_struct
id|ring_descr
op_star
id|rd
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ring processing helpers */
DECL|function|ring_last
r_static
r_inline
r_struct
id|ring_descr
op_star
id|ring_last
c_func
(paren
r_struct
id|vlsi_ring
op_star
id|r
)paren
(brace
r_int
id|t
suffix:semicolon
id|t
op_assign
id|atomic_read
c_func
(paren
op_amp
id|r-&gt;tail
)paren
op_amp
id|r-&gt;mask
suffix:semicolon
r_return
(paren
(paren
(paren
id|t
op_plus
l_int|1
)paren
op_amp
id|r-&gt;mask
)paren
op_eq
(paren
id|atomic_read
c_func
(paren
op_amp
id|r-&gt;head
)paren
op_amp
id|r-&gt;mask
)paren
)paren
ques
c_cond
l_int|NULL
suffix:colon
op_amp
id|r-&gt;rd
(braket
id|t
)braket
suffix:semicolon
)brace
DECL|function|ring_put
r_static
r_inline
r_struct
id|ring_descr
op_star
id|ring_put
c_func
(paren
r_struct
id|vlsi_ring
op_star
id|r
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|r-&gt;tail
)paren
suffix:semicolon
r_return
id|ring_last
c_func
(paren
id|r
)paren
suffix:semicolon
)brace
DECL|function|ring_first
r_static
r_inline
r_struct
id|ring_descr
op_star
id|ring_first
c_func
(paren
r_struct
id|vlsi_ring
op_star
id|r
)paren
(brace
r_int
id|h
suffix:semicolon
id|h
op_assign
id|atomic_read
c_func
(paren
op_amp
id|r-&gt;head
)paren
op_amp
id|r-&gt;mask
suffix:semicolon
r_return
(paren
id|h
op_eq
(paren
id|atomic_read
c_func
(paren
op_amp
id|r-&gt;tail
)paren
op_amp
id|r-&gt;mask
)paren
)paren
ques
c_cond
l_int|NULL
suffix:colon
op_amp
id|r-&gt;rd
(braket
id|h
)braket
suffix:semicolon
)brace
DECL|function|ring_get
r_static
r_inline
r_struct
id|ring_descr
op_star
id|ring_get
c_func
(paren
r_struct
id|vlsi_ring
op_star
id|r
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|r-&gt;head
)paren
suffix:semicolon
r_return
id|ring_first
c_func
(paren
id|r
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************/
multiline_comment|/* our private compound VLSI-PCI-IRDA device information */
DECL|struct|vlsi_irda_dev
r_typedef
r_struct
id|vlsi_irda_dev
(brace
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|baud
DECL|member|new_baud
r_int
id|baud
comma
id|new_baud
suffix:semicolon
DECL|member|busaddr
id|dma_addr_t
id|busaddr
suffix:semicolon
DECL|member|virtaddr
r_void
op_star
id|virtaddr
suffix:semicolon
DECL|member|tx_ring
DECL|member|rx_ring
r_struct
id|vlsi_ring
op_star
id|tx_ring
comma
op_star
id|rx_ring
suffix:semicolon
DECL|member|last_rx
r_struct
id|timeval
id|last_rx
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|cfg_space
id|u32
id|cfg_space
(braket
l_int|64
op_div
r_sizeof
(paren
id|u32
)paren
)braket
suffix:semicolon
DECL|member|resume_ok
id|u8
id|resume_ok
suffix:semicolon
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
DECL|typedef|vlsi_irda_dev_t
)brace
id|vlsi_irda_dev_t
suffix:semicolon
multiline_comment|/********************************************************/
multiline_comment|/* the remapped error flags we use for returning from frame&n; * post-processing in vlsi_process_tx/rx() after it was completed&n; * by the hardware. These functions either return the &gt;=0 number&n; * of transfered bytes in case of success or the negative (-)&n; * of the or&squot;ed error flags.&n; */
DECL|macro|VLSI_TX_DROP
mdefine_line|#define VLSI_TX_DROP&t;&t;0x0001
DECL|macro|VLSI_TX_FIFO
mdefine_line|#define VLSI_TX_FIFO&t;&t;0x0002
DECL|macro|VLSI_RX_DROP
mdefine_line|#define VLSI_RX_DROP&t;&t;0x0100
DECL|macro|VLSI_RX_OVER
mdefine_line|#define VLSI_RX_OVER&t;&t;0x0200
DECL|macro|VLSI_RX_LENGTH
mdefine_line|#define VLSI_RX_LENGTH  &t;0x0400
DECL|macro|VLSI_RX_FRAME
mdefine_line|#define VLSI_RX_FRAME&t;&t;0x0800
DECL|macro|VLSI_RX_CRC
mdefine_line|#define VLSI_RX_CRC&t;&t;0x1000
multiline_comment|/********************************************************/
macro_line|#endif /* IRDA_VLSI_FIR_H */
eof
