multiline_comment|/*&n; *&t;Description of Z8530 Z85C30 and Z85230 communications chips&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998 Alan Cox &lt;alan@redhat.com&gt;&n; */
macro_line|#ifndef _Z8530_H
DECL|macro|_Z8530_H
mdefine_line|#define _Z8530_H
macro_line|#include &lt;linux/tty.h&gt;
multiline_comment|/* Conversion routines to/from brg time constants from/to bits&n; * per second.&n; */
DECL|macro|BRG_TO_BPS
mdefine_line|#define BRG_TO_BPS(brg, freq) ((freq) / 2 / ((brg) + 2))
DECL|macro|BPS_TO_BRG
mdefine_line|#define BPS_TO_BRG(bps, freq) ((((freq) + (bps)) / (2 * (bps))) - 2)
multiline_comment|/* The Zilog register set */
DECL|macro|FLAG
mdefine_line|#define&t;FLAG&t;0x7e
multiline_comment|/* Write Register 0 */
DECL|macro|R0
mdefine_line|#define&t;R0&t;0&t;&t;/* Register selects */
DECL|macro|R1
mdefine_line|#define&t;R1&t;1
DECL|macro|R2
mdefine_line|#define&t;R2&t;2
DECL|macro|R3
mdefine_line|#define&t;R3&t;3
DECL|macro|R4
mdefine_line|#define&t;R4&t;4
DECL|macro|R5
mdefine_line|#define&t;R5&t;5
DECL|macro|R6
mdefine_line|#define&t;R6&t;6
DECL|macro|R7
mdefine_line|#define&t;R7&t;7
DECL|macro|R8
mdefine_line|#define&t;R8&t;8
DECL|macro|R9
mdefine_line|#define&t;R9&t;9
DECL|macro|R10
mdefine_line|#define&t;R10&t;10
DECL|macro|R11
mdefine_line|#define&t;R11&t;11
DECL|macro|R12
mdefine_line|#define&t;R12&t;12
DECL|macro|R13
mdefine_line|#define&t;R13&t;13
DECL|macro|R14
mdefine_line|#define&t;R14&t;14
DECL|macro|R15
mdefine_line|#define&t;R15&t;15
DECL|macro|RPRIME
mdefine_line|#define RPRIME&t;16&t;&t;/* Indicate a prime register access on 230 */
DECL|macro|NULLCODE
mdefine_line|#define&t;NULLCODE&t;0&t;/* Null Code */
DECL|macro|POINT_HIGH
mdefine_line|#define&t;POINT_HIGH&t;0x8&t;/* Select upper half of registers */
DECL|macro|RES_EXT_INT
mdefine_line|#define&t;RES_EXT_INT&t;0x10&t;/* Reset Ext. Status Interrupts */
DECL|macro|SEND_ABORT
mdefine_line|#define&t;SEND_ABORT&t;0x18&t;/* HDLC Abort */
DECL|macro|RES_RxINT_FC
mdefine_line|#define&t;RES_RxINT_FC&t;0x20&t;/* Reset RxINT on First Character */
DECL|macro|RES_Tx_P
mdefine_line|#define&t;RES_Tx_P&t;0x28&t;/* Reset TxINT Pending */
DECL|macro|ERR_RES
mdefine_line|#define&t;ERR_RES&t;&t;0x30&t;/* Error Reset */
DECL|macro|RES_H_IUS
mdefine_line|#define&t;RES_H_IUS&t;0x38&t;/* Reset highest IUS */
DECL|macro|RES_Rx_CRC
mdefine_line|#define&t;RES_Rx_CRC&t;0x40&t;/* Reset Rx CRC Checker */
DECL|macro|RES_Tx_CRC
mdefine_line|#define&t;RES_Tx_CRC&t;0x80&t;/* Reset Tx CRC Checker */
DECL|macro|RES_EOM_L
mdefine_line|#define&t;RES_EOM_L&t;0xC0&t;/* Reset EOM latch */
multiline_comment|/* Write Register 1 */
DECL|macro|EXT_INT_ENAB
mdefine_line|#define&t;EXT_INT_ENAB&t;0x1&t;/* Ext Int Enable */
DECL|macro|TxINT_ENAB
mdefine_line|#define&t;TxINT_ENAB&t;0x2&t;/* Tx Int Enable */
DECL|macro|PAR_SPEC
mdefine_line|#define&t;PAR_SPEC&t;0x4&t;/* Parity is special condition */
DECL|macro|RxINT_DISAB
mdefine_line|#define&t;RxINT_DISAB&t;0&t;/* Rx Int Disable */
DECL|macro|RxINT_FCERR
mdefine_line|#define&t;RxINT_FCERR&t;0x8&t;/* Rx Int on First Character Only or Error */
DECL|macro|INT_ALL_Rx
mdefine_line|#define&t;INT_ALL_Rx&t;0x10&t;/* Int on all Rx Characters or error */
DECL|macro|INT_ERR_Rx
mdefine_line|#define&t;INT_ERR_Rx&t;0x18&t;/* Int on error only */
DECL|macro|WT_RDY_RT
mdefine_line|#define&t;WT_RDY_RT&t;0x20&t;/* Wait/Ready on R/T */
DECL|macro|WT_FN_RDYFN
mdefine_line|#define&t;WT_FN_RDYFN&t;0x40&t;/* Wait/FN/Ready FN */
DECL|macro|WT_RDY_ENAB
mdefine_line|#define&t;WT_RDY_ENAB&t;0x80&t;/* Wait/Ready Enable */
multiline_comment|/* Write Register #2 (Interrupt Vector) */
multiline_comment|/* Write Register 3 */
DECL|macro|RxENABLE
mdefine_line|#define&t;RxENABLE&t;0x1&t;/* Rx Enable */
DECL|macro|SYNC_L_INH
mdefine_line|#define&t;SYNC_L_INH&t;0x2&t;/* Sync Character Load Inhibit */
DECL|macro|ADD_SM
mdefine_line|#define&t;ADD_SM&t;&t;0x4&t;/* Address Search Mode (SDLC) */
DECL|macro|RxCRC_ENAB
mdefine_line|#define&t;RxCRC_ENAB&t;0x8&t;/* Rx CRC Enable */
DECL|macro|ENT_HM
mdefine_line|#define&t;ENT_HM&t;&t;0x10&t;/* Enter Hunt Mode */
DECL|macro|AUTO_ENAB
mdefine_line|#define&t;AUTO_ENAB&t;0x20&t;/* Auto Enables */
DECL|macro|Rx5
mdefine_line|#define&t;Rx5&t;&t;0x0&t;/* Rx 5 Bits/Character */
DECL|macro|Rx7
mdefine_line|#define&t;Rx7&t;&t;0x40&t;/* Rx 7 Bits/Character */
DECL|macro|Rx6
mdefine_line|#define&t;Rx6&t;&t;0x80&t;/* Rx 6 Bits/Character */
DECL|macro|Rx8
mdefine_line|#define&t;Rx8&t;&t;0xc0&t;/* Rx 8 Bits/Character */
multiline_comment|/* Write Register 4 */
DECL|macro|PAR_ENA
mdefine_line|#define&t;PAR_ENA&t;&t;0x1&t;/* Parity Enable */
DECL|macro|PAR_EVEN
mdefine_line|#define&t;PAR_EVEN&t;0x2&t;/* Parity Even/Odd* */
DECL|macro|SYNC_ENAB
mdefine_line|#define&t;SYNC_ENAB&t;0&t;/* Sync Modes Enable */
DECL|macro|SB1
mdefine_line|#define&t;SB1&t;&t;0x4&t;/* 1 stop bit/char */
DECL|macro|SB15
mdefine_line|#define&t;SB15&t;&t;0x8&t;/* 1.5 stop bits/char */
DECL|macro|SB2
mdefine_line|#define&t;SB2&t;&t;0xc&t;/* 2 stop bits/char */
DECL|macro|MONSYNC
mdefine_line|#define&t;MONSYNC&t;&t;0&t;/* 8 Bit Sync character */
DECL|macro|BISYNC
mdefine_line|#define&t;BISYNC&t;&t;0x10&t;/* 16 bit sync character */
DECL|macro|SDLC
mdefine_line|#define&t;SDLC&t;&t;0x20&t;/* SDLC Mode (01111110 Sync Flag) */
DECL|macro|EXTSYNC
mdefine_line|#define&t;EXTSYNC&t;&t;0x30&t;/* External Sync Mode */
DECL|macro|X1CLK
mdefine_line|#define&t;X1CLK&t;&t;0x0&t;/* x1 clock mode */
DECL|macro|X16CLK
mdefine_line|#define&t;X16CLK&t;&t;0x40&t;/* x16 clock mode */
DECL|macro|X32CLK
mdefine_line|#define&t;X32CLK&t;&t;0x80&t;/* x32 clock mode */
DECL|macro|X64CLK
mdefine_line|#define&t;X64CLK&t;&t;0xC0&t;/* x64 clock mode */
multiline_comment|/* Write Register 5 */
DECL|macro|TxCRC_ENAB
mdefine_line|#define&t;TxCRC_ENAB&t;0x1&t;/* Tx CRC Enable */
DECL|macro|RTS
mdefine_line|#define&t;RTS&t;&t;0x2&t;/* RTS */
DECL|macro|SDLC_CRC
mdefine_line|#define&t;SDLC_CRC&t;0x4&t;/* SDLC/CRC-16 */
DECL|macro|TxENAB
mdefine_line|#define&t;TxENAB&t;&t;0x8&t;/* Tx Enable */
DECL|macro|SND_BRK
mdefine_line|#define&t;SND_BRK&t;&t;0x10&t;/* Send Break */
DECL|macro|Tx5
mdefine_line|#define&t;Tx5&t;&t;0x0&t;/* Tx 5 bits (or less)/character */
DECL|macro|Tx7
mdefine_line|#define&t;Tx7&t;&t;0x20&t;/* Tx 7 bits/character */
DECL|macro|Tx6
mdefine_line|#define&t;Tx6&t;&t;0x40&t;/* Tx 6 bits/character */
DECL|macro|Tx8
mdefine_line|#define&t;Tx8&t;&t;0x60&t;/* Tx 8 bits/character */
DECL|macro|DTR
mdefine_line|#define&t;DTR&t;&t;0x80&t;/* DTR */
multiline_comment|/* Write Register 6 (Sync bits 0-7/SDLC Address Field) */
multiline_comment|/* Write Register 7 (Sync bits 8-15/SDLC 01111110) */
multiline_comment|/* Write Register 8 (transmit buffer) */
multiline_comment|/* Write Register 9 (Master interrupt control) */
DECL|macro|VIS
mdefine_line|#define&t;VIS&t;1&t;/* Vector Includes Status */
DECL|macro|NV
mdefine_line|#define&t;NV&t;2&t;/* No Vector */
DECL|macro|DLC
mdefine_line|#define&t;DLC&t;4&t;/* Disable Lower Chain */
DECL|macro|MIE
mdefine_line|#define&t;MIE&t;8&t;/* Master Interrupt Enable */
DECL|macro|STATHI
mdefine_line|#define&t;STATHI&t;0x10&t;/* Status high */
DECL|macro|NORESET
mdefine_line|#define&t;NORESET&t;0&t;/* No reset on write to R9 */
DECL|macro|CHRB
mdefine_line|#define&t;CHRB&t;0x40&t;/* Reset channel B */
DECL|macro|CHRA
mdefine_line|#define&t;CHRA&t;0x80&t;/* Reset channel A */
DECL|macro|FHWRES
mdefine_line|#define&t;FHWRES&t;0xc0&t;/* Force hardware reset */
multiline_comment|/* Write Register 10 (misc control bits) */
DECL|macro|BIT6
mdefine_line|#define&t;BIT6&t;1&t;/* 6 bit/8bit sync */
DECL|macro|LOOPMODE
mdefine_line|#define&t;LOOPMODE 2&t;/* SDLC Loop mode */
DECL|macro|ABUNDER
mdefine_line|#define&t;ABUNDER&t;4&t;/* Abort/flag on SDLC xmit underrun */
DECL|macro|MARKIDLE
mdefine_line|#define&t;MARKIDLE 8&t;/* Mark/flag on idle */
DECL|macro|GAOP
mdefine_line|#define&t;GAOP&t;0x10&t;/* Go active on poll */
DECL|macro|NRZ
mdefine_line|#define&t;NRZ&t;0&t;/* NRZ mode */
DECL|macro|NRZI
mdefine_line|#define&t;NRZI&t;0x20&t;/* NRZI mode */
DECL|macro|FM1
mdefine_line|#define&t;FM1&t;0x40&t;/* FM1 (transition = 1) */
DECL|macro|FM0
mdefine_line|#define&t;FM0&t;0x60&t;/* FM0 (transition = 0) */
DECL|macro|CRCPS
mdefine_line|#define&t;CRCPS&t;0x80&t;/* CRC Preset I/O */
multiline_comment|/* Write Register 11 (Clock Mode control) */
DECL|macro|TRxCXT
mdefine_line|#define&t;TRxCXT&t;0&t;/* TRxC = Xtal output */
DECL|macro|TRxCTC
mdefine_line|#define&t;TRxCTC&t;1&t;/* TRxC = Transmit clock */
DECL|macro|TRxCBR
mdefine_line|#define&t;TRxCBR&t;2&t;/* TRxC = BR Generator Output */
DECL|macro|TRxCDP
mdefine_line|#define&t;TRxCDP&t;3&t;/* TRxC = DPLL output */
DECL|macro|TRxCOI
mdefine_line|#define&t;TRxCOI&t;4&t;/* TRxC O/I */
DECL|macro|TCRTxCP
mdefine_line|#define&t;TCRTxCP&t;0&t;/* Transmit clock = RTxC pin */
DECL|macro|TCTRxCP
mdefine_line|#define&t;TCTRxCP&t;8&t;/* Transmit clock = TRxC pin */
DECL|macro|TCBR
mdefine_line|#define&t;TCBR&t;0x10&t;/* Transmit clock = BR Generator output */
DECL|macro|TCDPLL
mdefine_line|#define&t;TCDPLL&t;0x18&t;/* Transmit clock = DPLL output */
DECL|macro|RCRTxCP
mdefine_line|#define&t;RCRTxCP&t;0&t;/* Receive clock = RTxC pin */
DECL|macro|RCTRxCP
mdefine_line|#define&t;RCTRxCP&t;0x20&t;/* Receive clock = TRxC pin */
DECL|macro|RCBR
mdefine_line|#define&t;RCBR&t;0x40&t;/* Receive clock = BR Generator output */
DECL|macro|RCDPLL
mdefine_line|#define&t;RCDPLL&t;0x60&t;/* Receive clock = DPLL output */
DECL|macro|RTxCX
mdefine_line|#define&t;RTxCX&t;0x80&t;/* RTxC Xtal/No Xtal */
multiline_comment|/* Write Register 12 (lower byte of baud rate generator time constant) */
multiline_comment|/* Write Register 13 (upper byte of baud rate generator time constant) */
multiline_comment|/* Write Register 14 (Misc control bits) */
DECL|macro|BRENABL
mdefine_line|#define&t;BRENABL&t;1&t;/* Baud rate generator enable */
DECL|macro|BRSRC
mdefine_line|#define&t;BRSRC&t;2&t;/* Baud rate generator source */
DECL|macro|DTRREQ
mdefine_line|#define&t;DTRREQ&t;4&t;/* DTR/Request function */
DECL|macro|AUTOECHO
mdefine_line|#define&t;AUTOECHO 8&t;/* Auto Echo */
DECL|macro|LOOPBAK
mdefine_line|#define&t;LOOPBAK&t;0x10&t;/* Local loopback */
DECL|macro|SEARCH
mdefine_line|#define&t;SEARCH&t;0x20&t;/* Enter search mode */
DECL|macro|RMC
mdefine_line|#define&t;RMC&t;0x40&t;/* Reset missing clock */
DECL|macro|DISDPLL
mdefine_line|#define&t;DISDPLL&t;0x60&t;/* Disable DPLL */
DECL|macro|SSBR
mdefine_line|#define&t;SSBR&t;0x80&t;/* Set DPLL source = BR generator */
DECL|macro|SSRTxC
mdefine_line|#define&t;SSRTxC&t;0xa0&t;/* Set DPLL source = RTxC */
DECL|macro|SFMM
mdefine_line|#define&t;SFMM&t;0xc0&t;/* Set FM mode */
DECL|macro|SNRZI
mdefine_line|#define&t;SNRZI&t;0xe0&t;/* Set NRZI mode */
multiline_comment|/* Write Register 15 (external/status interrupt control) */
DECL|macro|PRIME
mdefine_line|#define PRIME&t;1&t;/* R5&squot; etc register access (Z85C30/230 only) */
DECL|macro|ZCIE
mdefine_line|#define&t;ZCIE&t;2&t;/* Zero count IE */
DECL|macro|FIFOE
mdefine_line|#define FIFOE&t;4&t;/* Z85230 only */
DECL|macro|DCDIE
mdefine_line|#define&t;DCDIE&t;8&t;/* DCD IE */
DECL|macro|SYNCIE
mdefine_line|#define&t;SYNCIE&t;0x10&t;/* Sync/hunt IE */
DECL|macro|CTSIE
mdefine_line|#define&t;CTSIE&t;0x20&t;/* CTS IE */
DECL|macro|TxUIE
mdefine_line|#define&t;TxUIE&t;0x40&t;/* Tx Underrun/EOM IE */
DECL|macro|BRKIE
mdefine_line|#define&t;BRKIE&t;0x80&t;/* Break/Abort IE */
multiline_comment|/* Read Register 0 */
DECL|macro|Rx_CH_AV
mdefine_line|#define&t;Rx_CH_AV&t;0x1&t;/* Rx Character Available */
DECL|macro|ZCOUNT
mdefine_line|#define&t;ZCOUNT&t;&t;0x2&t;/* Zero count */
DECL|macro|Tx_BUF_EMP
mdefine_line|#define&t;Tx_BUF_EMP&t;0x4&t;/* Tx Buffer empty */
DECL|macro|DCD
mdefine_line|#define&t;DCD&t;&t;0x8&t;/* DCD */
DECL|macro|SYNC_HUNT
mdefine_line|#define&t;SYNC_HUNT&t;0x10&t;/* Sync/hunt */
DECL|macro|CTS
mdefine_line|#define&t;CTS&t;&t;0x20&t;/* CTS */
DECL|macro|TxEOM
mdefine_line|#define&t;TxEOM&t;&t;0x40&t;/* Tx underrun */
DECL|macro|BRK_ABRT
mdefine_line|#define&t;BRK_ABRT&t;0x80&t;/* Break/Abort */
multiline_comment|/* Read Register 1 */
DECL|macro|ALL_SNT
mdefine_line|#define&t;ALL_SNT&t;&t;0x1&t;/* All sent */
multiline_comment|/* Residue Data for 8 Rx bits/char programmed */
DECL|macro|RES3
mdefine_line|#define&t;RES3&t;&t;0x8&t;/* 0/3 */
DECL|macro|RES4
mdefine_line|#define&t;RES4&t;&t;0x4&t;/* 0/4 */
DECL|macro|RES5
mdefine_line|#define&t;RES5&t;&t;0xc&t;/* 0/5 */
DECL|macro|RES6
mdefine_line|#define&t;RES6&t;&t;0x2&t;/* 0/6 */
DECL|macro|RES7
mdefine_line|#define&t;RES7&t;&t;0xa&t;/* 0/7 */
DECL|macro|RES8
mdefine_line|#define&t;RES8&t;&t;0x6&t;/* 0/8 */
DECL|macro|RES18
mdefine_line|#define&t;RES18&t;&t;0xe&t;/* 1/8 */
DECL|macro|RES28
mdefine_line|#define&t;RES28&t;&t;0x0&t;/* 2/8 */
multiline_comment|/* Special Rx Condition Interrupts */
DECL|macro|PAR_ERR
mdefine_line|#define&t;PAR_ERR&t;&t;0x10&t;/* Parity error */
DECL|macro|Rx_OVR
mdefine_line|#define&t;Rx_OVR&t;&t;0x20&t;/* Rx Overrun Error */
DECL|macro|CRC_ERR
mdefine_line|#define&t;CRC_ERR&t;&t;0x40&t;/* CRC/Framing Error */
DECL|macro|END_FR
mdefine_line|#define&t;END_FR&t;&t;0x80&t;/* End of Frame (SDLC) */
multiline_comment|/* Read Register 2 (channel b only) - Interrupt vector */
multiline_comment|/* Read Register 3 (interrupt pending register) ch a only */
DECL|macro|CHBEXT
mdefine_line|#define&t;CHBEXT&t;0x1&t;&t;/* Channel B Ext/Stat IP */
DECL|macro|CHBTxIP
mdefine_line|#define&t;CHBTxIP&t;0x2&t;&t;/* Channel B Tx IP */
DECL|macro|CHBRxIP
mdefine_line|#define&t;CHBRxIP&t;0x4&t;&t;/* Channel B Rx IP */
DECL|macro|CHAEXT
mdefine_line|#define&t;CHAEXT&t;0x8&t;&t;/* Channel A Ext/Stat IP */
DECL|macro|CHATxIP
mdefine_line|#define&t;CHATxIP&t;0x10&t;&t;/* Channel A Tx IP */
DECL|macro|CHARxIP
mdefine_line|#define&t;CHARxIP&t;0x20&t;&t;/* Channel A Rx IP */
multiline_comment|/* Read Register 8 (receive data register) */
multiline_comment|/* Read Register 10  (misc status bits) */
DECL|macro|ONLOOP
mdefine_line|#define&t;ONLOOP&t;2&t;&t;/* On loop */
DECL|macro|LOOPSEND
mdefine_line|#define&t;LOOPSEND 0x10&t;&t;/* Loop sending */
DECL|macro|CLK2MIS
mdefine_line|#define&t;CLK2MIS&t;0x40&t;&t;/* Two clocks missing */
DECL|macro|CLK1MIS
mdefine_line|#define&t;CLK1MIS&t;0x80&t;&t;/* One clock missing */
multiline_comment|/* Read Register 12 (lower byte of baud rate generator constant) */
multiline_comment|/* Read Register 13 (upper byte of baud rate generator constant) */
multiline_comment|/* Read Register 15 (value of WR 15) */
multiline_comment|/*&n; *&t;Interrupt handling functions for this SCC&n; */
r_struct
id|z8530_channel
suffix:semicolon
DECL|struct|z8530_irqhandler
r_struct
id|z8530_irqhandler
(brace
DECL|member|rx
r_void
(paren
op_star
id|rx
)paren
(paren
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
DECL|member|tx
r_void
(paren
op_star
id|tx
)paren
(paren
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
DECL|member|status
r_void
(paren
op_star
id|status
)paren
(paren
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;A channel of the Z8530&n; */
DECL|struct|z8530_channel
r_struct
id|z8530_channel
(brace
DECL|member|irqs
r_struct
id|z8530_irqhandler
op_star
id|irqs
suffix:semicolon
multiline_comment|/* IRQ handlers */
multiline_comment|/*&n;&t; *&t;Synchronous&n;&t; */
DECL|member|count
id|u16
id|count
suffix:semicolon
multiline_comment|/* Buyes received */
DECL|member|max
id|u16
id|max
suffix:semicolon
multiline_comment|/* Most we can receive this frame */
DECL|member|mtu
id|u16
id|mtu
suffix:semicolon
multiline_comment|/* MTU of the device */
DECL|member|dptr
id|u8
op_star
id|dptr
suffix:semicolon
multiline_comment|/* Pointer into rx buffer */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* Buffer dptr points into */
DECL|member|skb2
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
multiline_comment|/* Pending buffer */
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* Current DCD */
DECL|member|dcdcheck
id|u8
id|dcdcheck
suffix:semicolon
multiline_comment|/* which bit to check for line */
DECL|member|sync
id|u8
id|sync
suffix:semicolon
multiline_comment|/* Set if in sync mode */
DECL|member|regs
id|u8
id|regs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Register map for the chip */
DECL|member|pendregs
id|u8
id|pendregs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Pending register values */
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
multiline_comment|/* Buffer being transmitted */
DECL|member|tx_next_skb
r_struct
id|sk_buff
op_star
id|tx_next_skb
suffix:semicolon
multiline_comment|/* Next transmit buffer */
DECL|member|tx_ptr
id|u8
op_star
id|tx_ptr
suffix:semicolon
multiline_comment|/* Byte pointer into the buffer */
DECL|member|tx_next_ptr
id|u8
op_star
id|tx_next_ptr
suffix:semicolon
multiline_comment|/* Next pointer to use */
DECL|member|tx_dma_buf
id|u8
op_star
id|tx_dma_buf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* TX flip buffers for DMA */
DECL|member|tx_dma_used
id|u8
id|tx_dma_used
suffix:semicolon
multiline_comment|/* Flip buffer usage toggler */
DECL|member|txcount
id|u16
id|txcount
suffix:semicolon
multiline_comment|/* Count of bytes to transmit */
DECL|member|rx_function
r_void
(paren
op_star
id|rx_function
)paren
(paren
r_struct
id|z8530_channel
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Sync DMA&n;&t; */
DECL|member|rxdma
id|u8
id|rxdma
suffix:semicolon
multiline_comment|/* DMA channels */
DECL|member|txdma
id|u8
id|txdma
suffix:semicolon
DECL|member|rxdma_on
id|u8
id|rxdma_on
suffix:semicolon
multiline_comment|/* DMA active if flag set */
DECL|member|txdma_on
id|u8
id|txdma_on
suffix:semicolon
DECL|member|dma_num
id|u8
id|dma_num
suffix:semicolon
multiline_comment|/* Buffer we are DMAing into */
DECL|member|dma_ready
id|u8
id|dma_ready
suffix:semicolon
multiline_comment|/* Is the other buffer free */
DECL|member|dma_tx
id|u8
id|dma_tx
suffix:semicolon
multiline_comment|/* TX is to use DMA */
DECL|member|rx_buf
id|u8
op_star
id|rx_buf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* The flip buffers */
multiline_comment|/*&n;&t; *&t;System&n;&t; */
DECL|member|dev
r_struct
id|z8530_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* Z85230 chip instance we are from */
DECL|member|ctrlio
r_int
r_int
id|ctrlio
suffix:semicolon
multiline_comment|/* I/O ports */
DECL|member|dataio
r_int
r_int
id|dataio
suffix:semicolon
multiline_comment|/*&n;&t; *&t;For PC we encode this way.&n;&t; */
DECL|macro|Z8530_PORT_SLEEP
mdefine_line|#define Z8530_PORT_SLEEP&t;0x80000000
DECL|macro|Z8530_PORT_OF
mdefine_line|#define Z8530_PORT_OF(x)&t;((x)&amp;0xFFFF)
DECL|member|rx_overrun
id|u32
id|rx_overrun
suffix:semicolon
multiline_comment|/* Overruns - not done yet */
DECL|member|rx_crc_err
id|u32
id|rx_crc_err
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Bound device pointers&n;&t; */
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* For our owner */
DECL|member|netdevice
r_struct
id|net_device
op_star
id|netdevice
suffix:semicolon
multiline_comment|/* Network layer device */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* Network layer statistics */
multiline_comment|/*&n;&t; *&t;Async features&n;&t; */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* Attached terminal */
DECL|member|line
r_int
id|line
suffix:semicolon
multiline_comment|/* Minor number */
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
multiline_comment|/* Terminal settings */
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
multiline_comment|/* Tasks waiting to open */
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
multiline_comment|/* and for close to end */
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
multiline_comment|/* Pending events */
DECL|member|fdcount
r_int
id|fdcount
suffix:semicolon
multiline_comment|/* # of fd on device */
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* XON/XOF char */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
multiline_comment|/* Transmit pointer */
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
multiline_comment|/* Transmit ring */
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
multiline_comment|/* Transmit FIFO info */
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
multiline_comment|/* Do we wait for drain on close ? */
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* We need to know the current clock divisor&n;&t; * to read the bps rate the chip has currently&n;&t; * loaded.&n;&t; */
DECL|member|clk_divisor
r_int
r_char
id|clk_divisor
suffix:semicolon
multiline_comment|/* May be 1, 16, 32, or 64 */
DECL|member|zs_baud
r_int
id|zs_baud
suffix:semicolon
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
multiline_comment|/* Baud parameters */
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|tx_active
r_int
r_char
id|tx_active
suffix:semicolon
multiline_comment|/* character is being xmitted */
DECL|member|tx_stopped
r_int
r_char
id|tx_stopped
suffix:semicolon
multiline_comment|/* output is suspended */
DECL|member|lock
id|spinlock_t
op_star
id|lock
suffix:semicolon
multiline_comment|/* Devicr lock */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Each Z853x0 device.&n; */
DECL|struct|z8530_dev
r_struct
id|z8530_dev
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Device instance name */
DECL|member|chanA
r_struct
id|z8530_channel
id|chanA
suffix:semicolon
multiline_comment|/* SCC channel A */
DECL|member|chanB
r_struct
id|z8530_channel
id|chanB
suffix:semicolon
multiline_comment|/* SCC channel B */
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|macro|Z8530
mdefine_line|#define Z8530&t;0&t;/* NMOS dinosaur */&t;
DECL|macro|Z85C30
mdefine_line|#define Z85C30&t;1&t;/* CMOS - better */
DECL|macro|Z85230
mdefine_line|#define Z85230&t;2&t;/* CMOS with real FIFO */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* Interrupt for the device */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* Soft interrupt enable - the Mac doesn&squot;t &n;&t;&t;&t;   always have a hard disable on its 8530s... */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Functions&n; */
r_extern
id|u8
id|z8530_dead_port
(braket
)braket
suffix:semicolon
r_extern
id|u8
id|z8530_hdlc_kilostream_85230
(braket
)braket
suffix:semicolon
r_extern
id|u8
id|z8530_hdlc_kilostream
(braket
)braket
suffix:semicolon
r_extern
r_void
id|z8530_interrupt
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|z8530_describe
c_func
(paren
r_struct
id|z8530_dev
op_star
comma
r_char
op_star
id|mapping
comma
r_int
r_int
id|io
)paren
suffix:semicolon
r_extern
r_int
id|z8530_init
c_func
(paren
r_struct
id|z8530_dev
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_shutdown
c_func
(paren
r_struct
id|z8530_dev
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_sync_open
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_sync_close
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_sync_dma_open
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_sync_dma_close
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_sync_txdma_open
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_sync_txdma_close
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|z8530_channel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_channel_load
c_func
(paren
r_struct
id|z8530_channel
op_star
comma
id|u8
op_star
)paren
suffix:semicolon
r_extern
r_int
id|z8530_queue_xmit
c_func
(paren
r_struct
id|z8530_channel
op_star
id|c
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_struct
id|net_device_stats
op_star
id|z8530_get_stats
c_func
(paren
r_struct
id|z8530_channel
op_star
id|c
)paren
suffix:semicolon
r_extern
r_void
id|z8530_null_rx
c_func
(paren
r_struct
id|z8530_channel
op_star
id|c
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Standard interrupt vector sets&n; */
r_extern
r_struct
id|z8530_irqhandler
id|z8530_sync
comma
id|z8530_async
comma
id|z8530_nop
suffix:semicolon
multiline_comment|/*&n; *&t;Asynchronous Interfacing&n; */
DECL|macro|SERIAL_MAGIC
mdefine_line|#define SERIAL_MAGIC 0x5301
multiline_comment|/*&n; * The size of the serial xmit buffer is 1 page, or 4096 bytes&n; */
DECL|macro|SERIAL_XMIT_SIZE
mdefine_line|#define SERIAL_XMIT_SIZE 4096
DECL|macro|WAKEUP_CHARS
mdefine_line|#define WAKEUP_CHARS&t;256
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|RS_EVENT_WRITE_WAKEUP
mdefine_line|#define RS_EVENT_WRITE_WAKEUP&t;0
multiline_comment|/* Internal flags used only by kernel/chr_drv/serial.c */
DECL|macro|ZILOG_INITIALIZED
mdefine_line|#define ZILOG_INITIALIZED&t;0x80000000 /* Serial port was initialized */
DECL|macro|ZILOG_CALLOUT_ACTIVE
mdefine_line|#define ZILOG_CALLOUT_ACTIVE&t;0x40000000 /* Call out device is active */
DECL|macro|ZILOG_NORMAL_ACTIVE
mdefine_line|#define ZILOG_NORMAL_ACTIVE&t;0x20000000 /* Normal device is active */
DECL|macro|ZILOG_BOOT_AUTOCONF
mdefine_line|#define ZILOG_BOOT_AUTOCONF&t;0x10000000 /* Autoconfigure port on bootup */
DECL|macro|ZILOG_CLOSING
mdefine_line|#define ZILOG_CLOSING&t;&t;0x08000000 /* Serial port is closing */
DECL|macro|ZILOG_CTS_FLOW
mdefine_line|#define ZILOG_CTS_FLOW&t;&t;0x04000000 /* Do CTS flow control */
DECL|macro|ZILOG_CHECK_CD
mdefine_line|#define ZILOG_CHECK_CD&t;&t;0x02000000 /* i.e., CLOCAL */
macro_line|#endif /* !(_Z8530_H) */
eof
