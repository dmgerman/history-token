multiline_comment|/*&n; * hd64572.h&t;Description of the Hitachi HD64572 (SCA-II), valid for &n; * &t;&t;CPU modes 0 &amp; 2.&n; *&n; * Author:&t;Ivan Passos &lt;ivan@cyclades.com&gt;&n; *&n; * Copyright:   (c) 2000-2001 Cyclades Corp.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; * $Log: hd64572.h,v $&n; * Revision 3.1  2001/06/15 12:41:10  regina&n; * upping major version number&n; *&n; * Revision 1.1.1.1  2001/06/13 20:24:49  daniela&n; * PC300 initial CVS version (3.4.0-pre1)&n; *&n; * Revision 1.0 2000/01/25 ivan&n; * Initial version.&n; *&n; */
macro_line|#ifndef _HD64572_H
DECL|macro|_HD64572_H
mdefine_line|#define _HD64572_H
multiline_comment|/* Illegal Access Register */
DECL|macro|ILAR
mdefine_line|#define&t;ILAR&t;0x00
multiline_comment|/* Wait Controller Registers */
DECL|macro|PABR0L
mdefine_line|#define PABR0L&t;0x20&t;/* Physical Addr Boundary Register 0 L */
DECL|macro|PABR0H
mdefine_line|#define PABR0H&t;0x21&t;/* Physical Addr Boundary Register 0 H */
DECL|macro|PABR1L
mdefine_line|#define PABR1L&t;0x22&t;/* Physical Addr Boundary Register 1 L */
DECL|macro|PABR1H
mdefine_line|#define PABR1H&t;0x23&t;/* Physical Addr Boundary Register 1 H */
DECL|macro|WCRL
mdefine_line|#define WCRL&t;0x24&t;/* Wait Control Register L */
DECL|macro|WCRM
mdefine_line|#define WCRM&t;0x25&t;/* Wait Control Register M */
DECL|macro|WCRH
mdefine_line|#define WCRH&t;0x26&t;/* Wait Control Register H */
multiline_comment|/* Interrupt Registers */
DECL|macro|IVR
mdefine_line|#define IVR&t;0x60&t;/* Interrupt Vector Register */
DECL|macro|IMVR
mdefine_line|#define IMVR&t;0x64&t;/* Interrupt Modified Vector Register */
DECL|macro|ITCR
mdefine_line|#define ITCR&t;0x68&t;/* Interrupt Control Register */
DECL|macro|ISR0
mdefine_line|#define ISR0&t;0x6c&t;/* Interrupt Status Register 0 */
DECL|macro|ISR1
mdefine_line|#define ISR1&t;0x70&t;/* Interrupt Status Register 1 */
DECL|macro|IER0
mdefine_line|#define IER0&t;0x74&t;/* Interrupt Enable Register 0 */
DECL|macro|IER1
mdefine_line|#define IER1&t;0x78&t;/* Interrupt Enable Register 1 */
multiline_comment|/* Register Access Macros (chan is 0 or 1 in _any_ case) */
DECL|macro|M_REG
mdefine_line|#define&t;M_REG(reg, chan)&t;(reg + 0x80*chan)&t;&t;/* MSCI */
DECL|macro|DRX_REG
mdefine_line|#define&t;DRX_REG(reg, chan)&t;(reg + 0x40*chan)&t;&t;/* DMA Rx */
DECL|macro|DTX_REG
mdefine_line|#define&t;DTX_REG(reg, chan)&t;(reg + 0x20*(2*chan + 1))&t;/* DMA Tx */
DECL|macro|TRX_REG
mdefine_line|#define&t;TRX_REG(reg, chan)&t;(reg + 0x20*chan)&t;&t;/* Timer Rx */
DECL|macro|TTX_REG
mdefine_line|#define&t;TTX_REG(reg, chan)&t;(reg + 0x10*(2*chan + 1))&t;/* Timer Tx */
DECL|macro|ST_REG
mdefine_line|#define&t;ST_REG(reg, chan)&t;(reg + 0x80*chan)&t;&t;/* Status Cnt */
DECL|macro|IR0_DRX
mdefine_line|#define IR0_DRX(val, chan)&t;((val)&lt;&lt;(8*(chan)))&t;&t;/* Int DMA Rx */
DECL|macro|IR0_DTX
mdefine_line|#define IR0_DTX(val, chan)&t;((val)&lt;&lt;(4*(2*chan + 1)))&t;/* Int DMA Tx */
DECL|macro|IR0_M
mdefine_line|#define IR0_M(val, chan)&t;((val)&lt;&lt;(8*(chan)))&t;&t;/* Int MSCI */
multiline_comment|/* MSCI Channel Registers */
DECL|macro|MD0
mdefine_line|#define MD0&t;0x138&t;/* Mode reg 0 */
DECL|macro|MD1
mdefine_line|#define MD1&t;0x139&t;/* Mode reg 1 */
DECL|macro|MD2
mdefine_line|#define MD2&t;0x13a&t;/* Mode reg 2 */
DECL|macro|MD3
mdefine_line|#define MD3&t;0x13b&t;/* Mode reg 3 */
DECL|macro|CTL
mdefine_line|#define CTL&t;0x130&t;/* Control reg */
DECL|macro|RXS
mdefine_line|#define RXS&t;0x13c&t;/* RX clock source */
DECL|macro|TXS
mdefine_line|#define TXS&t;0x13d&t;/* TX clock source */
DECL|macro|EXS
mdefine_line|#define EXS&t;0x13e&t;/* External clock input selection */
DECL|macro|TMCT
mdefine_line|#define TMCT&t;0x144&t;/* Time constant (Tx) */
DECL|macro|TMCR
mdefine_line|#define TMCR&t;0x145&t;/* Time constant (Rx) */
DECL|macro|CMD
mdefine_line|#define CMD&t;0x128&t;/* Command reg */
DECL|macro|ST0
mdefine_line|#define ST0&t;0x118&t;/* Status reg 0 */
DECL|macro|ST1
mdefine_line|#define ST1&t;0x119&t;/* Status reg 1 */
DECL|macro|ST2
mdefine_line|#define ST2&t;0x11a&t;/* Status reg 2 */
DECL|macro|ST3
mdefine_line|#define ST3&t;0x11b&t;/* Status reg 3 */
DECL|macro|ST4
mdefine_line|#define ST4&t;0x11c&t;/* Status reg 4 */
DECL|macro|FST
mdefine_line|#define FST&t;0x11d&t;/* frame Status reg  */
DECL|macro|IE0
mdefine_line|#define IE0&t;0x120&t;/* Interrupt enable reg 0 */
DECL|macro|IE1
mdefine_line|#define IE1&t;0x121&t;/* Interrupt enable reg 1 */
DECL|macro|IE2
mdefine_line|#define IE2&t;0x122&t;/* Interrupt enable reg 2 */
DECL|macro|IE4
mdefine_line|#define IE4&t;0x124&t;/* Interrupt enable reg 4 */
DECL|macro|FIE
mdefine_line|#define FIE&t;0x125&t;/* Frame Interrupt enable reg  */
DECL|macro|SA0
mdefine_line|#define SA0&t;0x140&t;/* Syn Address reg 0 */
DECL|macro|SA1
mdefine_line|#define SA1&t;0x141&t;/* Syn Address reg 1 */
DECL|macro|IDL
mdefine_line|#define IDL&t;0x142&t;/* Idle register */
DECL|macro|TRBL
mdefine_line|#define TRBL&t;0x100&t;/* TX/RX buffer reg L */ 
DECL|macro|TRBK
mdefine_line|#define TRBK&t;0x101&t;/* TX/RX buffer reg K */ 
DECL|macro|TRBJ
mdefine_line|#define TRBJ&t;0x102&t;/* TX/RX buffer reg J */ 
DECL|macro|TRBH
mdefine_line|#define TRBH&t;0x103&t;/* TX/RX buffer reg H */ 
DECL|macro|TRC0
mdefine_line|#define TRC0&t;0x148&t;/* TX Ready control reg 0 */ 
DECL|macro|TRC1
mdefine_line|#define TRC1&t;0x149&t;/* TX Ready control reg 1 */ 
DECL|macro|RRC
mdefine_line|#define RRC&t;0x14a&t;/* RX Ready control reg */ 
DECL|macro|CST0
mdefine_line|#define CST0&t;0x108&t;/* Current Status Register 0 */ 
DECL|macro|CST1
mdefine_line|#define CST1&t;0x109&t;/* Current Status Register 1 */ 
DECL|macro|CST2
mdefine_line|#define CST2&t;0x10a&t;/* Current Status Register 2 */ 
DECL|macro|CST3
mdefine_line|#define CST3&t;0x10b&t;/* Current Status Register 3 */ 
DECL|macro|GPO
mdefine_line|#define GPO&t;0x131&t;/* General Purpose Output Pin Ctl Reg */
DECL|macro|TFS
mdefine_line|#define TFS&t;0x14b&t;/* Tx Start Threshold Ctl Reg */
DECL|macro|TFN
mdefine_line|#define TFN&t;0x143&t;/* Inter-transmit-frame Time Fill Ctl Reg */
DECL|macro|TBN
mdefine_line|#define TBN&t;0x110&t;/* Tx Buffer Number Reg */
DECL|macro|RBN
mdefine_line|#define RBN&t;0x111&t;/* Rx Buffer Number Reg */
DECL|macro|TNR0
mdefine_line|#define TNR0&t;0x150&t;/* Tx DMA Request Ctl Reg 0 */
DECL|macro|TNR1
mdefine_line|#define TNR1&t;0x151&t;/* Tx DMA Request Ctl Reg 1 */
DECL|macro|TCR
mdefine_line|#define TCR&t;0x152&t;/* Tx DMA Critical Request Reg */
DECL|macro|RNR
mdefine_line|#define RNR&t;0x154&t;/* Rx DMA Request Ctl Reg */
DECL|macro|RCR
mdefine_line|#define RCR&t;0x156&t;/* Rx DMA Critical Request Reg */
multiline_comment|/* Timer Registers */
DECL|macro|TCNTL
mdefine_line|#define TCNTL&t;0x200&t;/* Timer Upcounter L */
DECL|macro|TCNTH
mdefine_line|#define TCNTH&t;0x201&t;/* Timer Upcounter H */
DECL|macro|TCONRL
mdefine_line|#define TCONRL&t;0x204&t;/* Timer Constant Register L */
DECL|macro|TCONRH
mdefine_line|#define TCONRH&t;0x205&t;/* Timer Constant Register H */
DECL|macro|TCSR
mdefine_line|#define TCSR&t;0x206&t;/* Timer Control/Status Register */
DECL|macro|TEPR
mdefine_line|#define TEPR&t;0x207&t;/* Timer Expand Prescale Register */
multiline_comment|/* DMA registers */
DECL|macro|PCR
mdefine_line|#define PCR&t;&t;0x40&t;&t;/* DMA priority control reg */
DECL|macro|DRR
mdefine_line|#define DRR&t;&t;0x44&t;&t;/* DMA reset reg */
DECL|macro|DMER
mdefine_line|#define DMER&t;&t;0x07&t;&t;/* DMA Master Enable reg */
DECL|macro|BTCR
mdefine_line|#define BTCR&t;&t;0x08&t;&t;/* Burst Tx Ctl Reg */
DECL|macro|BOLR
mdefine_line|#define BOLR&t;&t;0x0c&t;&t;/* Back-off Length Reg */
DECL|macro|DSR_RX
mdefine_line|#define DSR_RX(chan)&t;(0x48 + 2*chan)&t;/* DMA Status Reg (Rx) */
DECL|macro|DSR_TX
mdefine_line|#define DSR_TX(chan)&t;(0x49 + 2*chan)&t;/* DMA Status Reg (Tx) */
DECL|macro|DIR_RX
mdefine_line|#define DIR_RX(chan)&t;(0x4c + 2*chan)&t;/* DMA Interrupt Enable Reg (Rx) */
DECL|macro|DIR_TX
mdefine_line|#define DIR_TX(chan)&t;(0x4d + 2*chan)&t;/* DMA Interrupt Enable Reg (Tx) */
DECL|macro|FCT_RX
mdefine_line|#define FCT_RX(chan)&t;(0x50 + 2*chan)&t;/* Frame End Interrupt Counter (Rx) */
DECL|macro|FCT_TX
mdefine_line|#define FCT_TX(chan)&t;(0x51 + 2*chan)&t;/* Frame End Interrupt Counter (Tx) */
DECL|macro|DMR_RX
mdefine_line|#define DMR_RX(chan)&t;(0x54 + 2*chan)&t;/* DMA Mode Reg (Rx) */
DECL|macro|DMR_TX
mdefine_line|#define DMR_TX(chan)&t;(0x55 + 2*chan)&t;/* DMA Mode Reg (Tx) */
DECL|macro|DCR_RX
mdefine_line|#define DCR_RX(chan)&t;(0x58 + 2*chan)&t;/* DMA Command Reg (Rx) */
DECL|macro|DCR_TX
mdefine_line|#define DCR_TX(chan)&t;(0x59 + 2*chan)&t;/* DMA Command Reg (Tx) */
multiline_comment|/* DMA Channel Registers */
DECL|macro|DARL
mdefine_line|#define DARL&t;0x80&t;/* Dest Addr Register L (single-block, RX only) */
DECL|macro|DARH
mdefine_line|#define DARH&t;0x81&t;/* Dest Addr Register H (single-block, RX only) */
DECL|macro|DARB
mdefine_line|#define DARB&t;0x82&t;/* Dest Addr Register B (single-block, RX only) */
DECL|macro|DARBH
mdefine_line|#define DARBH&t;0x83&t;/* Dest Addr Register BH (single-block, RX only) */
DECL|macro|SARL
mdefine_line|#define SARL&t;0x80&t;/* Source Addr Register L (single-block, TX only) */
DECL|macro|SARH
mdefine_line|#define SARH&t;0x81&t;/* Source Addr Register H (single-block, TX only) */
DECL|macro|SARB
mdefine_line|#define SARB&t;0x82&t;/* Source Addr Register B (single-block, TX only) */
DECL|macro|DARBH
mdefine_line|#define DARBH&t;0x83&t;/* Source Addr Register BH (single-block, TX only) */
DECL|macro|BARL
mdefine_line|#define BARL&t;0x80&t;/* Buffer Addr Register L (chained-block) */
DECL|macro|BARH
mdefine_line|#define BARH&t;0x81&t;/* Buffer Addr Register H (chained-block) */
DECL|macro|BARB
mdefine_line|#define BARB&t;0x82&t;/* Buffer Addr Register B (chained-block) */
DECL|macro|BARBH
mdefine_line|#define BARBH&t;0x83&t;/* Buffer Addr Register BH (chained-block) */
DECL|macro|CDAL
mdefine_line|#define CDAL&t;0x84&t;/* Current Descriptor Addr Register L */
DECL|macro|CDAH
mdefine_line|#define CDAH&t;0x85&t;/* Current Descriptor Addr Register H */
DECL|macro|CDAB
mdefine_line|#define CDAB&t;0x86&t;/* Current Descriptor Addr Register B */
DECL|macro|CDABH
mdefine_line|#define CDABH&t;0x87&t;/* Current Descriptor Addr Register BH */
DECL|macro|EDAL
mdefine_line|#define EDAL&t;0x88&t;/* Error Descriptor Addr Register L */
DECL|macro|EDAH
mdefine_line|#define EDAH&t;0x89&t;/* Error Descriptor Addr Register H */
DECL|macro|EDAB
mdefine_line|#define EDAB&t;0x8a&t;/* Error Descriptor Addr Register B */
DECL|macro|EDABH
mdefine_line|#define EDABH&t;0x8b&t;/* Error Descriptor Addr Register BH */
DECL|macro|BFLL
mdefine_line|#define BFLL&t;0x90&t;/* RX Buffer Length L (only RX) */
DECL|macro|BFLH
mdefine_line|#define BFLH&t;0x91&t;/* RX Buffer Length H (only RX) */
DECL|macro|BCRL
mdefine_line|#define BCRL&t;0x8c&t;/* Byte Count Register L */
DECL|macro|BCRH
mdefine_line|#define BCRH&t;0x8d&t;/* Byte Count Register H */
multiline_comment|/* Block Descriptor Structure */
r_typedef
r_struct
(brace
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* pointer to next block descriptor */
DECL|member|ptbuf
r_int
r_int
id|ptbuf
suffix:semicolon
multiline_comment|/* buffer pointer */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* data length */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* status */
DECL|member|filler
r_int
r_char
id|filler
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* alignment filler (16 bytes) */
DECL|typedef|pcsca_bd_t
)brace
id|pcsca_bd_t
suffix:semicolon
multiline_comment|/* &n;&t;Descriptor Status definitions:&n;&n;&t;Bit&t;Transmission&t;Reception&n;&n;&t;7&t;EOM&t;&t;EOM&n;&t;6&t;-&t;&t;Short Frame&n;&t;5&t;-&t;&t;Abort&n;&t;4&t;-&t;&t;Residual bit&n;&t;3&t;Underrun&t;Overrun&t;&n;&t;2&t;-&t;&t;CRC&n;&t;1&t;Ownership&t;Ownership&n;&t;0&t;EOT&t;&t;-&n;*/
DECL|macro|DST_EOT
mdefine_line|#define DST_EOT&t;&t;0x01&t;/* End of transmit command */
DECL|macro|DST_OSB
mdefine_line|#define DST_OSB&t;&t;0x02&t;/* Ownership bit */
DECL|macro|DST_CRC
mdefine_line|#define DST_CRC&t;&t;0x04&t;/* CRC Error */
DECL|macro|DST_OVR
mdefine_line|#define DST_OVR&t;&t;0x08&t;/* Overrun */
DECL|macro|DST_UDR
mdefine_line|#define DST_UDR&t;&t;0x08&t;/* Underrun */
DECL|macro|DST_RBIT
mdefine_line|#define DST_RBIT&t;0x10&t;/* Residual bit */
DECL|macro|DST_ABT
mdefine_line|#define DST_ABT&t;&t;0x20&t;/* Abort */
DECL|macro|DST_SHRT
mdefine_line|#define DST_SHRT&t;0x40&t;/* Short Frame  */
DECL|macro|DST_EOM
mdefine_line|#define DST_EOM&t;&t;0x80&t;/* End of Message  */
multiline_comment|/* Status Counter Registers */
DECL|macro|CMCR
mdefine_line|#define CMCR&t;0x158&t;/* Counter Master Ctl Reg */
DECL|macro|TECNTL
mdefine_line|#define TECNTL&t;0x160&t;/* Tx EOM Counter L */
DECL|macro|TECNTM
mdefine_line|#define TECNTM&t;0x161&t;/* Tx EOM Counter M */
DECL|macro|TECNTH
mdefine_line|#define TECNTH&t;0x162&t;/* Tx EOM Counter H */
DECL|macro|TECCR
mdefine_line|#define TECCR&t;0x163&t;/* Tx EOM Counter Ctl Reg */
DECL|macro|URCNTL
mdefine_line|#define URCNTL&t;0x164&t;/* Underrun Counter L */
DECL|macro|URCNTH
mdefine_line|#define URCNTH&t;0x165&t;/* Underrun Counter H */
DECL|macro|URCCR
mdefine_line|#define URCCR&t;0x167&t;/* Underrun Counter Ctl Reg */
DECL|macro|RECNTL
mdefine_line|#define RECNTL&t;0x168&t;/* Rx EOM Counter L */
DECL|macro|RECNTM
mdefine_line|#define RECNTM&t;0x169&t;/* Rx EOM Counter M */
DECL|macro|RECNTH
mdefine_line|#define RECNTH&t;0x16a&t;/* Rx EOM Counter H */
DECL|macro|RECCR
mdefine_line|#define RECCR&t;0x16b&t;/* Rx EOM Counter Ctl Reg */
DECL|macro|ORCNTL
mdefine_line|#define ORCNTL&t;0x16c&t;/* Overrun Counter L */
DECL|macro|ORCNTH
mdefine_line|#define ORCNTH&t;0x16d&t;/* Overrun Counter H */
DECL|macro|ORCCR
mdefine_line|#define ORCCR&t;0x16f&t;/* Overrun Counter Ctl Reg */
DECL|macro|CECNTL
mdefine_line|#define CECNTL&t;0x170&t;/* CRC Counter L */
DECL|macro|CECNTH
mdefine_line|#define CECNTH&t;0x171&t;/* CRC Counter H */
DECL|macro|CECCR
mdefine_line|#define CECCR&t;0x173&t;/* CRC Counter Ctl Reg */
DECL|macro|ABCNTL
mdefine_line|#define ABCNTL&t;0x174&t;/* Abort frame Counter L */
DECL|macro|ABCNTH
mdefine_line|#define ABCNTH&t;0x175&t;/* Abort frame Counter H */
DECL|macro|ABCCR
mdefine_line|#define ABCCR&t;0x177&t;/* Abort frame Counter Ctl Reg */
DECL|macro|SHCNTL
mdefine_line|#define SHCNTL&t;0x178&t;/* Short frame Counter L */
DECL|macro|SHCNTH
mdefine_line|#define SHCNTH&t;0x179&t;/* Short frame Counter H */
DECL|macro|SHCCR
mdefine_line|#define SHCCR&t;0x17b&t;/* Short frame Counter Ctl Reg */
DECL|macro|RSCNTL
mdefine_line|#define RSCNTL&t;0x17c&t;/* Residual bit Counter L */
DECL|macro|RSCNTH
mdefine_line|#define RSCNTH&t;0x17d&t;/* Residual bit Counter H */
DECL|macro|RSCCR
mdefine_line|#define RSCCR&t;0x17f&t;/* Residual bit Counter Ctl Reg */
multiline_comment|/* Register Programming Constants */
DECL|macro|IR0_DMIC
mdefine_line|#define IR0_DMIC&t;0x00000001
DECL|macro|IR0_DMIB
mdefine_line|#define IR0_DMIB&t;0x00000002
DECL|macro|IR0_DMIA
mdefine_line|#define IR0_DMIA&t;0x00000004
DECL|macro|IR0_EFT
mdefine_line|#define IR0_EFT&t;&t;0x00000008
DECL|macro|IR0_DMAREQ
mdefine_line|#define IR0_DMAREQ&t;0x00010000
DECL|macro|IR0_TXINT
mdefine_line|#define IR0_TXINT&t;0x00020000
DECL|macro|IR0_RXINTB
mdefine_line|#define IR0_RXINTB&t;0x00040000
DECL|macro|IR0_RXINTA
mdefine_line|#define IR0_RXINTA&t;0x00080000
DECL|macro|IR0_TXRDY
mdefine_line|#define IR0_TXRDY&t;0x00100000
DECL|macro|IR0_RXRDY
mdefine_line|#define IR0_RXRDY&t;0x00200000
DECL|macro|MD0_CRC16_0
mdefine_line|#define MD0_CRC16_0&t;0x00
DECL|macro|MD0_CRC16_1
mdefine_line|#define MD0_CRC16_1&t;0x01
DECL|macro|MD0_CRC32
mdefine_line|#define MD0_CRC32&t;0x02
DECL|macro|MD0_CRC_CCITT
mdefine_line|#define MD0_CRC_CCITT&t;0x03
DECL|macro|MD0_CRCC0
mdefine_line|#define MD0_CRCC0&t;0x04
DECL|macro|MD0_CRCC1
mdefine_line|#define MD0_CRCC1&t;0x08
DECL|macro|MD0_AUTO_ENA
mdefine_line|#define MD0_AUTO_ENA&t;0x10
DECL|macro|MD0_ASYNC
mdefine_line|#define MD0_ASYNC&t;0x00
DECL|macro|MD0_BY_MSYNC
mdefine_line|#define MD0_BY_MSYNC&t;0x20
DECL|macro|MD0_BY_BISYNC
mdefine_line|#define MD0_BY_BISYNC&t;0x40
DECL|macro|MD0_BY_EXT
mdefine_line|#define MD0_BY_EXT&t;0x60
DECL|macro|MD0_BIT_SYNC
mdefine_line|#define MD0_BIT_SYNC&t;0x80
DECL|macro|MD0_TRANSP
mdefine_line|#define MD0_TRANSP&t;0xc0
DECL|macro|MD1_NOADDR
mdefine_line|#define MD1_NOADDR&t;0x00
DECL|macro|MD1_SADDR1
mdefine_line|#define MD1_SADDR1&t;0x40
DECL|macro|MD1_SADDR2
mdefine_line|#define MD1_SADDR2&t;0x80
DECL|macro|MD1_DADDR
mdefine_line|#define MD1_DADDR&t;0xc0
DECL|macro|MD2_F_DUPLEX
mdefine_line|#define MD2_F_DUPLEX&t;0x00
DECL|macro|MD2_AUTO_ECHO
mdefine_line|#define MD2_AUTO_ECHO&t;0x01
DECL|macro|MD2_LOOP_HI_Z
mdefine_line|#define MD2_LOOP_HI_Z&t;0x02
DECL|macro|MD2_LOOP_MIR
mdefine_line|#define MD2_LOOP_MIR&t;0x03
DECL|macro|MD2_ADPLL_X8
mdefine_line|#define MD2_ADPLL_X8&t;0x00
DECL|macro|MD2_ADPLL_X16
mdefine_line|#define MD2_ADPLL_X16&t;0x08
DECL|macro|MD2_ADPLL_X32
mdefine_line|#define MD2_ADPLL_X32&t;0x10
DECL|macro|MD2_NRZ
mdefine_line|#define MD2_NRZ&t;&t;0x00
DECL|macro|MD2_NRZI
mdefine_line|#define MD2_NRZI&t;0x20
DECL|macro|MD2_NRZ_IEEE
mdefine_line|#define MD2_NRZ_IEEE&t;0x40
DECL|macro|MD2_MANCH
mdefine_line|#define MD2_MANCH&t;0x00
DECL|macro|MD2_FM1
mdefine_line|#define MD2_FM1&t;&t;0x20
DECL|macro|MD2_FM0
mdefine_line|#define MD2_FM0&t;&t;0x40
DECL|macro|MD2_FM
mdefine_line|#define MD2_FM&t;&t;0x80
DECL|macro|CTL_RTS
mdefine_line|#define CTL_RTS&t;&t;0x01
DECL|macro|CTL_DTR
mdefine_line|#define CTL_DTR&t;&t;0x02
DECL|macro|CTL_SYN
mdefine_line|#define CTL_SYN&t;&t;0x04
DECL|macro|CTL_IDLC
mdefine_line|#define CTL_IDLC&t;0x10
DECL|macro|CTL_UDRNC
mdefine_line|#define CTL_UDRNC&t;0x20
DECL|macro|CTL_URSKP
mdefine_line|#define CTL_URSKP&t;0x40
DECL|macro|CTL_URCT
mdefine_line|#define CTL_URCT&t;0x80
DECL|macro|RXS_BR0
mdefine_line|#define&t;RXS_BR0&t;&t;0x01
DECL|macro|RXS_BR1
mdefine_line|#define&t;RXS_BR1&t;&t;0x02
DECL|macro|RXS_BR2
mdefine_line|#define&t;RXS_BR2&t;&t;0x04
DECL|macro|RXS_BR3
mdefine_line|#define&t;RXS_BR3&t;&t;0x08
DECL|macro|RXS_ECLK
mdefine_line|#define&t;RXS_ECLK&t;0x00
DECL|macro|RXS_ECLK_NS
mdefine_line|#define&t;RXS_ECLK_NS&t;0x20
DECL|macro|RXS_IBRG
mdefine_line|#define&t;RXS_IBRG&t;0x40
DECL|macro|RXS_PLL1
mdefine_line|#define&t;RXS_PLL1&t;0x50
DECL|macro|RXS_PLL2
mdefine_line|#define&t;RXS_PLL2&t;0x60
DECL|macro|RXS_PLL3
mdefine_line|#define&t;RXS_PLL3&t;0x70
DECL|macro|RXS_DRTXC
mdefine_line|#define&t;RXS_DRTXC&t;0x80
DECL|macro|TXS_BR0
mdefine_line|#define&t;TXS_BR0&t;&t;0x01
DECL|macro|TXS_BR1
mdefine_line|#define&t;TXS_BR1&t;&t;0x02
DECL|macro|TXS_BR2
mdefine_line|#define&t;TXS_BR2&t;&t;0x04
DECL|macro|TXS_BR3
mdefine_line|#define&t;TXS_BR3&t;&t;0x08
DECL|macro|TXS_ECLK
mdefine_line|#define&t;TXS_ECLK&t;0x00
DECL|macro|TXS_IBRG
mdefine_line|#define&t;TXS_IBRG&t;0x40
DECL|macro|TXS_RCLK
mdefine_line|#define&t;TXS_RCLK&t;0x60
DECL|macro|TXS_DTRXC
mdefine_line|#define&t;TXS_DTRXC&t;0x80
DECL|macro|EXS_RES0
mdefine_line|#define&t;EXS_RES0&t;0x01
DECL|macro|EXS_RES1
mdefine_line|#define&t;EXS_RES1&t;0x02
DECL|macro|EXS_RES2
mdefine_line|#define&t;EXS_RES2&t;0x04
DECL|macro|EXS_TES0
mdefine_line|#define&t;EXS_TES0&t;0x10
DECL|macro|EXS_TES1
mdefine_line|#define&t;EXS_TES1&t;0x20
DECL|macro|EXS_TES2
mdefine_line|#define&t;EXS_TES2&t;0x40
DECL|macro|CMD_RX_RST
mdefine_line|#define CMD_RX_RST&t;0x11
DECL|macro|CMD_RX_ENA
mdefine_line|#define CMD_RX_ENA&t;0x12
DECL|macro|CMD_RX_DIS
mdefine_line|#define CMD_RX_DIS&t;0x13
DECL|macro|CMD_RX_CRC_INIT
mdefine_line|#define CMD_RX_CRC_INIT&t;0x14
DECL|macro|CMD_RX_MSG_REJ
mdefine_line|#define CMD_RX_MSG_REJ&t;0x15
DECL|macro|CMD_RX_MP_SRCH
mdefine_line|#define CMD_RX_MP_SRCH&t;0x16
DECL|macro|CMD_RX_CRC_EXC
mdefine_line|#define CMD_RX_CRC_EXC&t;0x17
DECL|macro|CMD_RX_CRC_FRC
mdefine_line|#define CMD_RX_CRC_FRC&t;0x18
DECL|macro|CMD_TX_RST
mdefine_line|#define CMD_TX_RST&t;0x01
DECL|macro|CMD_TX_ENA
mdefine_line|#define CMD_TX_ENA&t;0x02
DECL|macro|CMD_TX_DISA
mdefine_line|#define CMD_TX_DISA&t;0x03
DECL|macro|CMD_TX_CRC_INIT
mdefine_line|#define CMD_TX_CRC_INIT&t;0x04
DECL|macro|CMD_TX_CRC_EXC
mdefine_line|#define CMD_TX_CRC_EXC&t;0x05
DECL|macro|CMD_TX_EOM
mdefine_line|#define CMD_TX_EOM&t;0x06
DECL|macro|CMD_TX_ABORT
mdefine_line|#define CMD_TX_ABORT&t;0x07
DECL|macro|CMD_TX_MP_ON
mdefine_line|#define CMD_TX_MP_ON&t;0x08
DECL|macro|CMD_TX_BUF_CLR
mdefine_line|#define CMD_TX_BUF_CLR&t;0x09
DECL|macro|CMD_TX_DISB
mdefine_line|#define CMD_TX_DISB&t;0x0b
DECL|macro|CMD_CH_RST
mdefine_line|#define CMD_CH_RST&t;0x21
DECL|macro|CMD_SRCH_MODE
mdefine_line|#define CMD_SRCH_MODE&t;0x31
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;0x00
DECL|macro|ST0_RXRDY
mdefine_line|#define ST0_RXRDY&t;0x01
DECL|macro|ST0_TXRDY
mdefine_line|#define ST0_TXRDY&t;0x02
DECL|macro|ST0_RXINTB
mdefine_line|#define ST0_RXINTB&t;0x20
DECL|macro|ST0_RXINTA
mdefine_line|#define ST0_RXINTA&t;0x40
DECL|macro|ST0_TXINT
mdefine_line|#define ST0_TXINT&t;0x80
DECL|macro|ST1_IDLE
mdefine_line|#define ST1_IDLE&t;0x01
DECL|macro|ST1_ABORT
mdefine_line|#define ST1_ABORT&t;0x02
DECL|macro|ST1_CDCD
mdefine_line|#define ST1_CDCD&t;0x04
DECL|macro|ST1_CCTS
mdefine_line|#define ST1_CCTS&t;0x08
DECL|macro|ST1_SYN_FLAG
mdefine_line|#define ST1_SYN_FLAG&t;0x10
DECL|macro|ST1_CLMD
mdefine_line|#define ST1_CLMD&t;0x20
DECL|macro|ST1_TXIDLE
mdefine_line|#define ST1_TXIDLE&t;0x40
DECL|macro|ST1_UDRN
mdefine_line|#define ST1_UDRN&t;0x80
DECL|macro|ST2_CRCE
mdefine_line|#define ST2_CRCE&t;0x04
DECL|macro|ST2_ONRN
mdefine_line|#define ST2_ONRN&t;0x08
DECL|macro|ST2_RBIT
mdefine_line|#define ST2_RBIT&t;0x10
DECL|macro|ST2_ABORT
mdefine_line|#define ST2_ABORT&t;0x20
DECL|macro|ST2_SHORT
mdefine_line|#define ST2_SHORT&t;0x40
DECL|macro|ST2_EOM
mdefine_line|#define ST2_EOM&t;&t;0x80
DECL|macro|ST3_RX_ENA
mdefine_line|#define ST3_RX_ENA&t;0x01
DECL|macro|ST3_TX_ENA
mdefine_line|#define ST3_TX_ENA&t;0x02
DECL|macro|ST3_DCD
mdefine_line|#define ST3_DCD&t;&t;0x04
DECL|macro|ST3_CTS
mdefine_line|#define ST3_CTS&t;&t;0x08
DECL|macro|ST3_SRCH_MODE
mdefine_line|#define ST3_SRCH_MODE&t;0x10
DECL|macro|ST3_SLOOP
mdefine_line|#define ST3_SLOOP&t;0x20
DECL|macro|ST3_GPI
mdefine_line|#define ST3_GPI&t;&t;0x80
DECL|macro|ST4_RDNR
mdefine_line|#define ST4_RDNR&t;0x01
DECL|macro|ST4_RDCR
mdefine_line|#define ST4_RDCR&t;0x02
DECL|macro|ST4_TDNR
mdefine_line|#define ST4_TDNR&t;0x04
DECL|macro|ST4_TDCR
mdefine_line|#define ST4_TDCR&t;0x08
DECL|macro|ST4_OCLM
mdefine_line|#define ST4_OCLM&t;0x20
DECL|macro|ST4_CFT
mdefine_line|#define ST4_CFT&t;&t;0x40
DECL|macro|ST4_CGPI
mdefine_line|#define ST4_CGPI&t;0x80
DECL|macro|FST_CRCEF
mdefine_line|#define FST_CRCEF&t;0x04
DECL|macro|FST_OVRNF
mdefine_line|#define FST_OVRNF&t;0x08
DECL|macro|FST_RBIF
mdefine_line|#define FST_RBIF&t;0x10
DECL|macro|FST_ABTF
mdefine_line|#define FST_ABTF&t;0x20
DECL|macro|FST_SHRTF
mdefine_line|#define FST_SHRTF&t;0x40
DECL|macro|FST_EOMF
mdefine_line|#define FST_EOMF&t;0x80
DECL|macro|IE0_RXRDY
mdefine_line|#define IE0_RXRDY&t;0x01
DECL|macro|IE0_TXRDY
mdefine_line|#define IE0_TXRDY&t;0x02
DECL|macro|IE0_RXINTB
mdefine_line|#define IE0_RXINTB&t;0x20
DECL|macro|IE0_RXINTA
mdefine_line|#define IE0_RXINTA&t;0x40
DECL|macro|IE0_TXINT
mdefine_line|#define IE0_TXINT&t;0x80
DECL|macro|IE1_IDLD
mdefine_line|#define IE1_IDLD&t;0x01
DECL|macro|IE1_ABTD
mdefine_line|#define IE1_ABTD&t;0x02
DECL|macro|IE1_CDCD
mdefine_line|#define IE1_CDCD&t;0x04
DECL|macro|IE1_CCTS
mdefine_line|#define IE1_CCTS&t;0x08
DECL|macro|IE1_SYNCD
mdefine_line|#define IE1_SYNCD&t;0x10
DECL|macro|IE1_CLMD
mdefine_line|#define IE1_CLMD&t;0x20
DECL|macro|IE1_IDL
mdefine_line|#define IE1_IDL&t;&t;0x40
DECL|macro|IE1_UDRN
mdefine_line|#define IE1_UDRN&t;0x80
DECL|macro|IE2_CRCE
mdefine_line|#define IE2_CRCE&t;0x04
DECL|macro|IE2_OVRN
mdefine_line|#define IE2_OVRN&t;0x08
DECL|macro|IE2_RBIT
mdefine_line|#define IE2_RBIT&t;0x10
DECL|macro|IE2_ABT
mdefine_line|#define IE2_ABT&t;&t;0x20
DECL|macro|IE2_SHRT
mdefine_line|#define IE2_SHRT&t;0x40
DECL|macro|IE2_EOM
mdefine_line|#define IE2_EOM&t;&t;0x80
DECL|macro|IE4_RDNR
mdefine_line|#define IE4_RDNR&t;0x01
DECL|macro|IE4_RDCR
mdefine_line|#define IE4_RDCR&t;0x02
DECL|macro|IE4_TDNR
mdefine_line|#define IE4_TDNR&t;0x04
DECL|macro|IE4_TDCR
mdefine_line|#define IE4_TDCR&t;0x08
DECL|macro|IE4_OCLM
mdefine_line|#define IE4_OCLM&t;0x20
DECL|macro|IE4_CFT
mdefine_line|#define IE4_CFT&t;&t;0x40
DECL|macro|IE4_CGPI
mdefine_line|#define IE4_CGPI&t;0x80
DECL|macro|FIE_CRCEF
mdefine_line|#define FIE_CRCEF&t;0x04
DECL|macro|FIE_OVRNF
mdefine_line|#define FIE_OVRNF&t;0x08
DECL|macro|FIE_RBIF
mdefine_line|#define FIE_RBIF&t;0x10
DECL|macro|FIE_ABTF
mdefine_line|#define FIE_ABTF&t;0x20
DECL|macro|FIE_SHRTF
mdefine_line|#define FIE_SHRTF&t;0x40
DECL|macro|FIE_EOMF
mdefine_line|#define FIE_EOMF&t;0x80
DECL|macro|DSR_DWE
mdefine_line|#define DSR_DWE&t;&t;0x01
DECL|macro|DSR_DE
mdefine_line|#define DSR_DE&t;&t;0x02
DECL|macro|DSR_REF
mdefine_line|#define DSR_REF&t;&t;0x04
DECL|macro|DSR_UDRF
mdefine_line|#define DSR_UDRF&t;0x04
DECL|macro|DSR_COA
mdefine_line|#define DSR_COA&t;&t;0x08
DECL|macro|DSR_COF
mdefine_line|#define DSR_COF&t;&t;0x10
DECL|macro|DSR_BOF
mdefine_line|#define DSR_BOF&t;&t;0x20
DECL|macro|DSR_EOM
mdefine_line|#define DSR_EOM&t;&t;0x40
DECL|macro|DSR_EOT
mdefine_line|#define DSR_EOT&t;&t;0x80
DECL|macro|DIR_REF
mdefine_line|#define DIR_REF&t;&t;0x04
DECL|macro|DIR_UDRF
mdefine_line|#define DIR_UDRF&t;0x04
DECL|macro|DIR_COA
mdefine_line|#define DIR_COA&t;&t;0x08
DECL|macro|DIR_COF
mdefine_line|#define DIR_COF&t;&t;0x10
DECL|macro|DIR_BOF
mdefine_line|#define DIR_BOF&t;&t;0x20
DECL|macro|DIR_EOM
mdefine_line|#define DIR_EOM&t;&t;0x40
DECL|macro|DIR_EOT
mdefine_line|#define DIR_EOT&t;&t;0x80
DECL|macro|DMR_CNTE
mdefine_line|#define DMR_CNTE&t;0x02
DECL|macro|DMR_NF
mdefine_line|#define DMR_NF&t;&t;0x04
DECL|macro|DMR_SEOME
mdefine_line|#define DMR_SEOME&t;0x08
DECL|macro|DMR_TMOD
mdefine_line|#define DMR_TMOD&t;0x10
DECL|macro|DCR_SW_ABT
mdefine_line|#define DCR_SW_ABT&t;0x01
DECL|macro|DCR_FCT_CLR
mdefine_line|#define DCR_FCT_CLR&t;0x02
DECL|macro|PCR_PR0
mdefine_line|#define PCR_PR0&t;&t;0x01
DECL|macro|PCR_PR1
mdefine_line|#define PCR_PR1&t;&t;0x02
DECL|macro|PCR_PR2
mdefine_line|#define PCR_PR2&t;&t;0x04
DECL|macro|PCR_CCC
mdefine_line|#define PCR_CCC&t;&t;0x08
DECL|macro|PCR_BRC
mdefine_line|#define PCR_BRC&t;&t;0x10
DECL|macro|PCR_OSB
mdefine_line|#define PCR_OSB&t;&t;0x40
DECL|macro|PCR_BURST
mdefine_line|#define PCR_BURST&t;0x80
macro_line|#endif /* (_HD64572_H) */
eof
