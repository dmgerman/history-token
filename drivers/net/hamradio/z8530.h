multiline_comment|/* 8530 Serial Communications Controller Register definitions */
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
DECL|macro|ZCIE
mdefine_line|#define&t;ZCIE&t;2&t;/* Zero count IE */
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
multiline_comment|/* Z85C30/Z85230 Enhanced SCC register definitions */
multiline_comment|/* Write Register 7&squot; (SDLC/HDLC Programmable Enhancements) */
DECL|macro|AUTOTXF
mdefine_line|#define AUTOTXF&t;0x01&t;&t;/* Auto Tx Flag */
DECL|macro|AUTOEOM
mdefine_line|#define AUTOEOM 0x02&t;&t;/* Auto EOM Latch Reset */
DECL|macro|AUTORTS
mdefine_line|#define AUTORTS&t;0x04&t;&t;/* Auto RTS */
DECL|macro|TXDNRZI
mdefine_line|#define TXDNRZI 0x08&t;&t;/* TxD Pulled High in SDLC NRZI mode */
DECL|macro|RXFIFOH
mdefine_line|#define RXFIFOH 0x08&t;&t;/* Z85230: Int on RX FIFO half full */
DECL|macro|FASTDTR
mdefine_line|#define FASTDTR 0x10&t;&t;/* Fast DTR/REQ Mode */
DECL|macro|CRCCBCR
mdefine_line|#define CRCCBCR&t;0x20&t;&t;/* CRC Check Bytes Completely Received */
DECL|macro|TXFIFOE
mdefine_line|#define TXFIFOE 0x20&t;&t;/* Z85230: Int on TX FIFO completely empty */
DECL|macro|EXTRDEN
mdefine_line|#define EXTRDEN&t;0x40&t;&t;/* Extended Read Enabled */
multiline_comment|/* Write Register 15 (external/status interrupt control) */
DECL|macro|SHDLCE
mdefine_line|#define SHDLCE&t;1&t;&t;/* SDLC/HDLC Enhancements Enable */
DECL|macro|FIFOE
mdefine_line|#define FIFOE&t;4&t;&t;/* FIFO Enable */
multiline_comment|/* Read Register 6 (frame status FIFO) */
DECL|macro|BCLSB
mdefine_line|#define BCLSB&t;0xff&t;&t;/* LSB of 14 bits count */
multiline_comment|/* Read Register 7 (frame status FIFO) */
DECL|macro|BCMSB
mdefine_line|#define BCMSB&t;0x3f&t;&t;/* MSB of 14 bits count */
DECL|macro|FDA
mdefine_line|#define FDA&t;0x40&t;&t;/* FIFO Data Available Status */
DECL|macro|FOS
mdefine_line|#define FOS&t;0x80&t;&t;/* FIFO Overflow Status */
eof
