multiline_comment|/*********************************************************************&n; *&n; *&t;vlsi_ir.h:&t;VLSI82C147 PCI IrDA controller driver for Linux&n; *&n; *&t;Version:&t;0.1, Aug 6, 2001&n; *&n; *&t;Copyright (c) 2001 Martin Diehl&n; *&n; *&t;This program is free software; you can redistribute it and/or &n; *&t;modify it under the terms of the GNU General Public License as &n; *&t;published by the Free Software Foundation; either version 2 of &n; *&t;the License, or (at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License &n; *&t;along with this program; if not, write to the Free Software &n; *&t;Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *&t;MA 02111-1307 USA&n; *&n; ********************************************************************/
macro_line|#ifndef IRDA_VLSI_FIR_H
DECL|macro|IRDA_VLSI_FIR_H
mdefine_line|#define IRDA_VLSI_FIR_H
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
multiline_comment|/* Three possible clock sources: either on-chip 48MHz PLL or&n; * external clock applied to EXTCLK pin. External clock may&n; * be either 48MHz or 40MHz, which is indicated by XCKSEL.&n; * CLKSTP controls whether the selected clock source gets&n; * connected to the IrDA block.&n; *&n; * On my HP OB-800 the BIOS sets external 40MHz clock as source&n; * when IrDA enabled and I&squot;ve never detected any PLL lock success.&n; * Apparently the 14.31818MHz OSC input required for the PLL to work&n; * is not connected and the 40MHz EXTCLK is provided externally.&n; * At least this is what makes the driver working for me.&n; */
DECL|enum|vlsi_pci_clkctl
r_enum
id|vlsi_pci_clkctl
(brace
multiline_comment|/* PLL control */
DECL|enumerator|CLKCTL_NO_PD
id|CLKCTL_NO_PD
op_assign
l_int|0x04
comma
multiline_comment|/* PD# (inverted power down) signal,&n;&t;&t;&t;&t;&t;&t; * i.e. PLL is powered, if PD_INV is set */
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
multiline_comment|/* set to select external clock input */
DECL|enumerator|CLKCTL_XCKSEL
id|CLKCTL_XCKSEL
op_assign
l_int|0x10
comma
multiline_comment|/* set to indicate 40MHz EXTCLK, not 48MHz */
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
multiline_comment|/* set to enable wakeup feature: whenever IR activity&n;&t;&t;&t;&t;&t;&t; * is detected, PD_INV gets set and CLKSTP cleared */
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
multiline_comment|/* PCI busmastering is somewhat special for this guy - in short:&n;&t; *&n;&t; * We select to operate using MSTRPAGE=0 fixed, use ISA DMA&n;&t; * address restrictions to make the PCI BM api aware of this,&n;&t; * but ensure the hardware is dealing with real 32bit access.&n;&t; *&n;&t; * In detail:&n;&t; * The chip executes normal 32bit busmaster cycles, i.e.&n;&t; * drives all 32 address lines. These addresses however are&n;&t; * composed of [0:23] taken from various busaddr-pointers&n;&t; * and [24:31] taken from the MSTRPAGE register in the VLSI82C147&n;&t; * config space. Therefore _all_ busmastering must be&n;&t; * targeted to/from one single 16MB (busaddr-) superpage!&n;&t; * The point is to make sure all the allocations for memory&n;&t; * locations with busmaster access (ring descriptors, buffers)&n;&t; * are indeed bus-mappable to the same 16MB range (for x86 this&n;&t; * means they must reside in the same 16MB physical memory address&n;&t; * range). The only constraint we have which supports &quot;several objects&n;&t; * mappable to common 16MB range&quot; paradigma, is the old ISA DMA&n;&t; * restriction to the first 16MB of physical address range.&n;&t; * Hence the approach here is to enable PCI busmaster support using&n;&t; * the correct 32bit dma-mask used by the chip. Afterwards the device&squot;s&n;&t; * dma-mask gets restricted to 24bit, which must be honoured by all&n;&t; * allocations for memory areas to be exposed to the chip.&n;&t; *&n;&t; * Note:&n;&t; * Don&squot;t be surprised to get &quot;Setting latency timer...&quot; messages every&n;&t; * time when PCI busmastering is enabled for the chip.&n;&t; * The chip has its PCI latency timer RO fixed at 0 - which is not a&n;&t; * problem here, because it is never requesting _burst_ transactions.&n;&t; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PCIIRMISC: IR Miscellaneous Register (u8, rw) */
multiline_comment|/* leagcy UART emulation - not used by this driver - would require:&n; * (see below for some register-value definitions)&n; *&n; *&t;- IRMISC_UARTEN must be set to enable UART address decoding&n; *&t;- IRMISC_UARTSEL configured&n; *&t;- IRCFG_MASTER must be cleared&n; *&t;- IRCFG_SIR must be set&n; *&t;- IRENABLE_IREN must be asserted 0-&gt;1 (and hence IRENABLE_SIR_ON)&n; */
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
multiline_comment|/* (ro?) IR rail power indication (and control?)&n;&t;&t;&t;&t;&t;&t; * 0=3.3V / 1=5V. Probably set during power-on?&n;&t;&t;&t;&t;&t;&t; * Not touched by driver */
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
multiline_comment|/* 0x0a-0x0f: reserved, duplicated UART regs */
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
multiline_comment|/* 0x1e-0x1f: reserved, duplicated UART regs */
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_IRINTR: Interrupt Register (u8, rw) */
multiline_comment|/* enable-bits:&n; *&t;&t;1 = enable / 0 = disable&n; * interrupt condition bits:&n; * &t;&t;set according to corresponding interrupt source&n; *&t;&t;(regardless of the state of the enable bits)&n; *&t;&t;enable bit status indicated whether interrupt gets raised&n; *&t;&t;write-to-clear&n; * note: RPKTINT and TPKTINT behave different in legacy UART mode (which we don&squot;t use :-)&n; */
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
DECL|macro|MAX_RING_DESCR
mdefine_line|#define MAX_RING_DESCR&t;&t;64&t;/* tx, rx rings may contain up to 64 descr each */
multiline_comment|/* _both_ ring pointers are indices relative to the _entire_ rx,tx-ring!&n; * i.e. the referenced descriptor is located&n; * at RINGBASE + PTR * sizeof(descr) for rx and tx&n; * therefore, the tx-pointer has offset by MAX_RING_DESCR&n; */
DECL|macro|RINGPTR_RX_MASK
mdefine_line|#define RINGPTR_RX_MASK&t;&t;(MAX_RING_DESCR-1)
DECL|macro|RINGPTR_TX_MASK
mdefine_line|#define RINGPTR_TX_MASK&t;&t;((MAX_RING_DESCR|(MAX_RING_DESCR-1))&lt;&lt;8)
DECL|macro|RINGPTR_GET_RX
mdefine_line|#define RINGPTR_GET_RX(p)&t;((p)&amp;RINGPTR_RX_MASK)
DECL|macro|RINGPTR_GET_TX
mdefine_line|#define RINGPTR_GET_TX(p)&t;(((p)&amp;RINGPTR_TX_MASK)&gt;&gt;8)
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_RINGBASE: Ring Pointer Base Address Register (u16, ro) */
multiline_comment|/* Contains [23:10] part of the ring base (bus-) address&n; * which must be 1k-alinged. [31:24] is taken from&n; * VLSI_PCI_MSTRPAGE above.&n; * The controler initiates non-burst PCI BM cycles to&n; * fetch and update the descriptors in the ring.&n; * Once fetched, the descriptor remains cached onchip&n; * until it gets closed and updated due to the ring&n; * processing state machine.&n; * The entire ring area is split in rx and tx areas with each&n; * area consisting of 64 descriptors of 8 bytes each.&n; * The rx(tx) ring is located at ringbase+0 (ringbase+8*64).&n; */
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
multiline_comment|/* writing any value kicks the ring processing state machines&n; * for both tx, rx rings.&n; * currently enabled rings (according to IRENABLE_ENTXST, IRENABLE_ENRXST&n; * status reporting - see below) are considered as follows:&n; * &t;- active rings (currently owning an active descriptor)&n; *&t;  ignore the prompt and continue&n; *&t;- idle rings fetch the next descr from the ring and start&n; *&t;  their processing&n; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_IRCFG: IR Config Register (u16, rw) */
multiline_comment|/* notes:&n; *&t;- not more than one SIR/MIR/FIR bit must be set at any time&n; *&t;- SIR, MIR, FIR and CRC16 select the configuration which will&n; *&t;  be applied now/next time if/when IRENABLE_IREN is _cleared_ (see below)&n; *&t;- besides allowing the PCI interface to execute busmaster cycles&n; *&t;  and therefore the ring SM to operate, the MSTR bit has side-effects:&n; *&t;  when MSTR is cleared, the RINGPTR&squot;s get reset and the legacy UART mode&n; *&t;  (in contrast to busmaster access mode) gets enabled.&n; *&t;- clearing ENRX or setting ENTX while data is received may stall the&n; *&t;  receive fifo until ENRX reenabled _and_ another packet arrives&n; *&t;- SIRFILT means the chip performs the required unwrapping of hardware&n; *&t;  headers (XBOF&squot;s, BOF/EOF) and un-escaping in the _receive_ direction.&n; *&t;  Only the resulting IrLAP payload is copied to the receive buffers -&n; *&t;  but with the 16bit FCS still encluded. Question remains, whether it&n; *&t;  was already checked or we should do it before passing the packet to IrLAP?&n; */
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
DECL|enumerator|IRENABLE_IREN
id|IRENABLE_IREN
op_assign
l_int|0x8000
comma
multiline_comment|/* enable IR phy and gate mode config (rw) */
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
multiline_comment|/* read-back of the currently applied physical layer status.&n; * applied from VLSI_PIO_NPHYCTL at rising edge of IRENABLE_IREN&n; * contents identical to VLSI_PIO_NPHYCTL (see below)&n; */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_NPHYCTL: IR Physical Layer Next Control Register (u16, rw) */
multiline_comment|/* latched during IRENABLE_IREN=0 and applied at 0-1 transition&n; *&n; * consists of BAUD[15:10], PLSWID[9:5] and PREAMB[4:0] bits defined as follows:&n; *&n; * SIR-mode:&t;BAUD = (115.2kHz / baudrate) - 1&n; *&t;&t;PLSWID = (pulsetime * freq / (BAUD+1)) - 1&n; *&t;&t;&t;where pulsetime is the requested IrPHY pulse width&n; *&t;&t;&t;and freq is 8(16)MHz for 40(48)MHz primary input clock&n; *&t;&t;PREAMB: dont care for SIR&n; *&n; *&t;&t;The nominal SIR pulse width is 3/16 bit time so we have PLSWID=12&n; *&t;&t;fixed for all SIR speeds at 40MHz input clock (PLSWID=24 at 48MHz).&n; *&t;&t;IrPHY also allows shorter pulses down to the nominal pulse duration&n; *&t;&t;at 115.2kbaud (minus some tolerance) which is 1.41 usec.&n; *&t;&t;Using the expression PLSWID = 12/(BAUD+1)-1 (multiplied by to for 48MHz)&n; *&t;&t;we get the minimum acceptable PLSWID values according to the VLSI&n; *&t;&t;specification, which provides 1.5 usec pulse width for all speeds (except&n; *&t;&t;for 2.4kbaud getting 6usec). This is well inside IrPHY v1.3 specs and&n; *&t;&t;reduces the transceiver power which drains the battery. At 9.6kbaud for&n; *&t;&t;example this makes more than 90% battery power saving!&n; *&n; * MIR-mode:&t;BAUD = 0&n; *&t;&t;PLSWID = 9(10) for 40(48) MHz input clock&n; *&t;&t;&t;to get nominal MIR pulse width&n; *&t;&t;PREAMB = 1&n; *&n; * FIR-mode:&t;BAUD = 0&n; *&t;&t;PLSWID: dont care&n; *&t;&t;PREAMB = 15&n; */
DECL|macro|BWP_TO_PHYCTL
mdefine_line|#define BWP_TO_PHYCTL(B,W,P)&t;((((B)&amp;0x3f)&lt;&lt;10) | (((W)&amp;0x1f)&lt;&lt;5) | (((P)&amp;0x1f)&lt;&lt;0))
DECL|macro|BAUD_BITS
mdefine_line|#define BAUD_BITS(br)&t;&t;((115200/br)-1)
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
multiline_comment|/* specifies the maximum legth (up to 4096 bytes), which a&n; * received frame may have - i.e. the size of the corresponding&n; * receive buffers. For simplicity we use the same length for&n; * receive and submit buffers. Therefore we use 3k to have&n; * enough space for a lot of XBOF&squot;s and escapes we may need at&n; * some point when wrapping MTU=2048 sized packets for transmission.&n; */
DECL|macro|MAX_PACKET_LENGTH
mdefine_line|#define MAX_PACKET_LENGTH&t;3172
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* VLSI_PIO_RCVBCNT: Receive Byte Count Register (u16, ro) */
multiline_comment|/* recive packet counter gets incremented on every non-filtered&n; * byte which was put in the receive fifo and reset for each&n; * new packet. Used to decide whether we are just in the middle&n; * of receiving receiving&n; */
DECL|macro|RCVBCNT_MASK
mdefine_line|#define RCVBCNT_MASK&t;0x0fff
multiline_comment|/* ================================================================ */
multiline_comment|/* descriptors for rx/tx ring&n; *&n; * accessed by hardware - don&squot;t change!&n; *&n; * the descriptor is owned by hardware, when the ACTIVE status bit&n; * is set and nothing (besides reading status to test the bit)&n; * shall be done. The bit gets cleared by hw, when the descriptor&n; * gets closed. Premature reaping of descriptors owned be the chip&n; * can be achieved by disabling IRCFG_MSTR&n; *&n; * Attention: Writing addr overwrites status!&n; *&n; * ### FIXME: we depend on endianess here&n; */
DECL|struct|ring_descr
r_struct
id|ring_descr
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
suffix:semicolon
DECL|member|rd_u
)brace
id|rd_u
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|rd_addr
mdefine_line|#define rd_addr&t;&t;rd_u.addr
DECL|macro|rd_status
mdefine_line|#define rd_status&t;rd_u.rd_s.status
multiline_comment|/* ring descriptor status bits */
DECL|macro|RD_STAT_ACTIVE
mdefine_line|#define RD_STAT_ACTIVE&t;&t;0x80&t;/* descriptor owned by hw (both TX,RX) */
multiline_comment|/* TX ring descriptor status */
DECL|macro|TX_STAT_DISCRC
mdefine_line|#define&t;TX_STAT_DISCRC&t;&t;0x40&t;/* do not send CRC (for SIR) */
DECL|macro|TX_STAT_BADCRC
mdefine_line|#define&t;TX_STAT_BADCRC&t;&t;0x20&t;/* force a bad CRC */
DECL|macro|TX_STAT_PULSE
mdefine_line|#define&t;TX_STAT_PULSE&t;&t;0x10&t;/* send indication pulse after this frame (MIR/FIR) */
DECL|macro|TX_STAT_FRCEUND
mdefine_line|#define&t;TX_STAT_FRCEUND&t;&t;0x08&t;/* force underrun */
DECL|macro|TX_STAT_CLRENTX
mdefine_line|#define&t;TX_STAT_CLRENTX&t;&t;0x04&t;/* clear ENTX after this frame */
DECL|macro|TX_STAT_UNDRN
mdefine_line|#define&t;TX_STAT_UNDRN&t;&t;0x01&t;/* TX fifo underrun (probably PCI problem) */
multiline_comment|/* RX ring descriptor status */
DECL|macro|RX_STAT_PHYERR
mdefine_line|#define RX_STAT_PHYERR&t;&t;0x40&t;/* physical encoding error */
DECL|macro|RX_STAT_CRCERR
mdefine_line|#define RX_STAT_CRCERR&t;&t;0x20&t;/* CRC error (MIR/FIR) */
DECL|macro|RX_STAT_LENGTH
mdefine_line|#define RX_STAT_LENGTH&t;&t;0x10&t;/* frame exceeds buffer length */
DECL|macro|RX_STAT_OVER
mdefine_line|#define RX_STAT_OVER&t;&t;0x08&t;/* RX fifo overrun (probably PCI problem) */
DECL|macro|RX_STAT_SIRBAD
mdefine_line|#define RX_STAT_SIRBAD&t;&t;0x04&t;/* EOF missing: BOF follows BOF (SIR, filtered) */
DECL|macro|RX_STAT_ERROR
mdefine_line|#define RX_STAT_ERROR&t;&t;0x7c&t;/* any error in frame */
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* contains the objects we&squot;ve put into the ring descriptors&n; * static buffers for now - probably skb&squot;s later&n; */
DECL|struct|ring_entry
r_struct
id|ring_entry
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|head
r_void
op_star
id|head
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------ */
multiline_comment|/* our compound VLSI-PCI-IRDA device information */
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
DECL|member|ring_hw
r_struct
id|ring_descr
op_star
id|ring_hw
suffix:semicolon
DECL|member|ring_buf
r_struct
id|ring_entry
op_star
id|ring_buf
suffix:semicolon
DECL|member|tx_mask
DECL|member|rx_mask
r_int
id|tx_mask
comma
id|rx_mask
suffix:semicolon
DECL|member|tx_put
DECL|member|tx_get
DECL|member|rx_put
DECL|member|rx_get
r_int
id|tx_put
comma
id|tx_get
comma
id|rx_put
comma
id|rx_get
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|typedef|vlsi_irda_dev_t
)brace
id|vlsi_irda_dev_t
suffix:semicolon
multiline_comment|/********************************************************/
macro_line|#endif /* IRDA_VLSI_FIR_H */
eof
