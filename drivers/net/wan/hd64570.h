macro_line|#ifndef __HD64570_H
DECL|macro|__HD64570_H
mdefine_line|#define __HD64570_H
multiline_comment|/* SCA HD64570 register definitions - all addresses for mode 0 (8086 MPU)&n;   and 1 (64180 MPU). For modes 2 and 3, XOR the address with 0x01.&n;&n;   Source: HD64570 SCA User&squot;s Manual&n;*/
multiline_comment|/* SCA Control Registers */
DECL|macro|LPR
mdefine_line|#define LPR    0x00&t;&t;/* Low Power */
multiline_comment|/* Wait controller registers */
DECL|macro|PABR0
mdefine_line|#define PABR0  0x02&t;&t;/* Physical Address Boundary 0 */
DECL|macro|PABR1
mdefine_line|#define PABR1  0x03&t;&t;/* Physical Address Boundary 1 */
DECL|macro|WCRL
mdefine_line|#define WCRL   0x04&t;&t;/* Wait Control L */
DECL|macro|WCRM
mdefine_line|#define WCRM   0x05&t;&t;/* Wait Control M */
DECL|macro|WCRH
mdefine_line|#define WCRH   0x06&t;&t;/* Wait Control H */
DECL|macro|PCR
mdefine_line|#define PCR    0x08&t;&t;/* DMA Priority Control */
DECL|macro|DMER
mdefine_line|#define DMER   0x09&t;&t;/* DMA Master Enable */
multiline_comment|/* Interrupt registers */
DECL|macro|ISR0
mdefine_line|#define ISR0   0x10&t;&t;/* Interrupt Status 0  */
DECL|macro|ISR1
mdefine_line|#define ISR1   0x11&t;&t;/* Interrupt Status 1  */
DECL|macro|ISR2
mdefine_line|#define ISR2   0x12&t;&t;/* Interrupt Status 2  */
DECL|macro|IER0
mdefine_line|#define IER0   0x14&t;&t;/* Interrupt Enable 0  */
DECL|macro|IER1
mdefine_line|#define IER1   0x15&t;&t;/* Interrupt Enable 1  */
DECL|macro|IER2
mdefine_line|#define IER2   0x16&t;&t;/* Interrupt Enable 2  */
DECL|macro|ITCR
mdefine_line|#define ITCR   0x18&t;&t;/* Interrupt Control */
DECL|macro|IVR
mdefine_line|#define IVR    0x1A&t;&t;/* Interrupt Vector */
DECL|macro|IMVR
mdefine_line|#define IMVR   0x1C&t;&t;/* Interrupt Modified Vector */
multiline_comment|/* MSCI channel (port) 0 registers - offset 0x20&n;   MSCI channel (port) 1 registers - offset 0x40 */
DECL|macro|MSCI0_OFFSET
mdefine_line|#define MSCI0_OFFSET 0x20
DECL|macro|MSCI1_OFFSET
mdefine_line|#define MSCI1_OFFSET 0x40
DECL|macro|TRBL
mdefine_line|#define TRBL   0x00&t;&t;/* TX/RX buffer L */ 
DECL|macro|TRBH
mdefine_line|#define TRBH   0x01&t;&t;/* TX/RX buffer H */ 
DECL|macro|ST0
mdefine_line|#define ST0    0x02&t;&t;/* Status 0 */
DECL|macro|ST1
mdefine_line|#define ST1    0x03&t;&t;/* Status 1 */
DECL|macro|ST2
mdefine_line|#define ST2    0x04&t;&t;/* Status 2 */
DECL|macro|ST3
mdefine_line|#define ST3    0x05&t;&t;/* Status 3 */
DECL|macro|FST
mdefine_line|#define FST    0x06&t;&t;/* Frame Status  */
DECL|macro|IE0
mdefine_line|#define IE0    0x08&t;&t;/* Interrupt Enable 0 */
DECL|macro|IE1
mdefine_line|#define IE1    0x09&t;&t;/* Interrupt Enable 1 */
DECL|macro|IE2
mdefine_line|#define IE2    0x0A&t;&t;/* Interrupt Enable 2 */
DECL|macro|FIE
mdefine_line|#define FIE    0x0B&t;&t;/* Frame Interrupt Enable  */
DECL|macro|CMD
mdefine_line|#define CMD    0x0C&t;&t;/* Command */
DECL|macro|MD0
mdefine_line|#define MD0    0x0E&t;&t;/* Mode 0 */
DECL|macro|MD1
mdefine_line|#define MD1    0x0F&t;&t;/* Mode 1 */
DECL|macro|MD2
mdefine_line|#define MD2    0x10&t;&t;/* Mode 2 */
DECL|macro|CTL
mdefine_line|#define CTL    0x11&t;&t;/* Control */
DECL|macro|SA0
mdefine_line|#define SA0    0x12&t;&t;/* Sync/Address 0 */
DECL|macro|SA1
mdefine_line|#define SA1    0x13&t;&t;/* Sync/Address 1 */
DECL|macro|IDL
mdefine_line|#define IDL    0x14&t;&t;/* Idle Pattern */
DECL|macro|TMC
mdefine_line|#define TMC    0x15&t;&t;/* Time Constant */
DECL|macro|RXS
mdefine_line|#define RXS    0x16&t;&t;/* RX Clock Source */
DECL|macro|TXS
mdefine_line|#define TXS    0x17&t;&t;/* TX Clock Source */
DECL|macro|TRC0
mdefine_line|#define TRC0   0x18&t;&t;/* TX Ready Control 0 */ 
DECL|macro|TRC1
mdefine_line|#define TRC1   0x19&t;&t;/* TX Ready Control 1 */ 
DECL|macro|RRC
mdefine_line|#define RRC    0x1A&t;&t;/* RX Ready Control */ 
DECL|macro|CST0
mdefine_line|#define CST0   0x1C&t;&t;/* Current Status 0 */
DECL|macro|CST1
mdefine_line|#define CST1   0x1D&t;&t;/* Current Status 1 */
multiline_comment|/* Timer channel 0 (port 0 RX) registers - offset 0x60&n;   Timer channel 1 (port 0 TX) registers - offset 0x68&n;   Timer channel 2 (port 1 RX) registers - offset 0x70&n;   Timer channel 3 (port 1 TX) registers - offset 0x78&n;*/
DECL|macro|TIMER0RX_OFFSET
mdefine_line|#define TIMER0RX_OFFSET 0x60
DECL|macro|TIMER0TX_OFFSET
mdefine_line|#define TIMER0TX_OFFSET 0x68
DECL|macro|TIMER1RX_OFFSET
mdefine_line|#define TIMER1RX_OFFSET 0x70
DECL|macro|TIMER1TX_OFFSET
mdefine_line|#define TIMER1TX_OFFSET 0x78
DECL|macro|TCNTL
mdefine_line|#define TCNTL  0x00&t;&t;/* Up-counter L */
DECL|macro|TCNTH
mdefine_line|#define TCNTH  0x01&t;&t;/* Up-counter H */
DECL|macro|TCONRL
mdefine_line|#define TCONRL 0x02&t;&t;/* Constant L */
DECL|macro|TCONRH
mdefine_line|#define TCONRH 0x03&t;&t;/* Constant H */
DECL|macro|TCSR
mdefine_line|#define TCSR   0x04&t;&t;/* Control/Status */
DECL|macro|TEPR
mdefine_line|#define TEPR   0x05&t;&t;/* Expand Prescale */
multiline_comment|/* DMA channel 0 (port 0 RX) registers - offset 0x80&n;   DMA channel 1 (port 0 TX) registers - offset 0xA0&n;   DMA channel 2 (port 1 RX) registers - offset 0xC0&n;   DMA channel 3 (port 1 TX) registers - offset 0xE0&n;*/
DECL|macro|DMAC0RX_OFFSET
mdefine_line|#define DMAC0RX_OFFSET 0x80
DECL|macro|DMAC0TX_OFFSET
mdefine_line|#define DMAC0TX_OFFSET 0xA0
DECL|macro|DMAC1RX_OFFSET
mdefine_line|#define DMAC1RX_OFFSET 0xC0
DECL|macro|DMAC1TX_OFFSET
mdefine_line|#define DMAC1TX_OFFSET 0xE0
DECL|macro|BARL
mdefine_line|#define BARL   0x00&t;&t;/* Buffer Address L (chained block) */
DECL|macro|BARH
mdefine_line|#define BARH   0x01&t;&t;/* Buffer Address H (chained block) */
DECL|macro|BARB
mdefine_line|#define BARB   0x02&t;&t;/* Buffer Address B (chained block) */
DECL|macro|DARL
mdefine_line|#define DARL   0x00&t;&t;/* RX Destination Addr L (single block) */
DECL|macro|DARH
mdefine_line|#define DARH   0x01&t;&t;/* RX Destination Addr H (single block) */
DECL|macro|DARB
mdefine_line|#define DARB   0x02&t;&t;/* RX Destination Addr B (single block) */
DECL|macro|SARL
mdefine_line|#define SARL   0x04&t;&t;/* TX Source Address L (single block) */
DECL|macro|SARH
mdefine_line|#define SARH   0x05&t;&t;/* TX Source Address H (single block) */
DECL|macro|SARB
mdefine_line|#define SARB   0x06&t;&t;/* TX Source Address B (single block) */
DECL|macro|CPB
mdefine_line|#define CPB    0x06&t;&t;/* Chain Pointer Base (chained block) */
DECL|macro|CDAL
mdefine_line|#define CDAL   0x08&t;&t;/* Current Descriptor Addr L (chained block) */
DECL|macro|CDAH
mdefine_line|#define CDAH   0x09&t;&t;/* Current Descriptor Addr H (chained block) */
DECL|macro|EDAL
mdefine_line|#define EDAL   0x0A&t;&t;/* Error Descriptor Addr L (chained block) */
DECL|macro|EDAH
mdefine_line|#define EDAH   0x0B&t;&t;/* Error Descriptor Addr H (chained block) */
DECL|macro|BFLL
mdefine_line|#define BFLL   0x0C&t;&t;/* RX Receive Buffer Length L (chained block)*/
DECL|macro|BFLH
mdefine_line|#define BFLH   0x0D&t;&t;/* RX Receive Buffer Length H (chained block)*/
DECL|macro|BCRL
mdefine_line|#define BCRL   0x0E&t;&t;/* Byte Count L */
DECL|macro|BCRH
mdefine_line|#define BCRH   0x0F&t;&t;/* Byte Count H */
DECL|macro|DSR
mdefine_line|#define DSR    0x10&t;&t;/* DMA Status */
DECL|macro|DSR_RX
mdefine_line|#define DSR_RX(node) (DSR + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
DECL|macro|DSR_TX
mdefine_line|#define DSR_TX(node) (DSR + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
DECL|macro|DMR
mdefine_line|#define DMR    0x11&t;&t;/* DMA Mode */
DECL|macro|DMR_RX
mdefine_line|#define DMR_RX(node) (DMR + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
DECL|macro|DMR_TX
mdefine_line|#define DMR_TX(node) (DMR + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
DECL|macro|FCT
mdefine_line|#define FCT    0x13&t;&t;/* Frame End Interrupt Counter */
DECL|macro|FCT_RX
mdefine_line|#define FCT_RX(node) (FCT + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
DECL|macro|FCT_TX
mdefine_line|#define FCT_TX(node) (FCT + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
DECL|macro|DIR
mdefine_line|#define DIR    0x14&t;&t;/* DMA Interrupt Enable */
DECL|macro|DIR_RX
mdefine_line|#define DIR_RX(node) (DIR + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
DECL|macro|DIR_TX
mdefine_line|#define DIR_TX(node) (DIR + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
DECL|macro|DCR
mdefine_line|#define DCR    0x15&t;&t;/* DMA Command  */
DECL|macro|DCR_RX
mdefine_line|#define DCR_RX(node) (DCR + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
DECL|macro|DCR_TX
mdefine_line|#define DCR_TX(node) (DCR + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
multiline_comment|/* Descriptor Structure */
r_typedef
r_struct
(brace
DECL|member|cp
id|u16
id|cp
suffix:semicolon
multiline_comment|/* Chain Pointer */
DECL|member|bp
id|u32
id|bp
suffix:semicolon
multiline_comment|/* Buffer Pointer (24 bits) */
DECL|member|len
id|u16
id|len
suffix:semicolon
multiline_comment|/* Data Length */
DECL|member|stat
id|u8
id|stat
suffix:semicolon
multiline_comment|/* Status */
DECL|member|unused2
id|u8
id|unused2
suffix:semicolon
DECL|typedef|pkt_desc
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|pkt_desc
suffix:semicolon
multiline_comment|/* Packet Descriptor Status bits */
DECL|macro|ST_TX_EOM
mdefine_line|#define ST_TX_EOM     0x80&t;/* End of frame */
DECL|macro|ST_TX_EOT
mdefine_line|#define ST_TX_EOT     0x01&t;/* End of transmition */
DECL|macro|ST_RX_EOM
mdefine_line|#define ST_RX_EOM     0x80&t;/* End of frame */
DECL|macro|ST_RX_SHORT
mdefine_line|#define ST_RX_SHORT   0x40&t;/* Short frame */
DECL|macro|ST_RX_ABORT
mdefine_line|#define ST_RX_ABORT   0x20&t;/* Abort */
DECL|macro|ST_RX_RESBIT
mdefine_line|#define ST_RX_RESBIT  0x10&t;/* Residual bit */
DECL|macro|ST_RX_OVERRUN
mdefine_line|#define ST_RX_OVERRUN 0x08&t;/* Overrun */
DECL|macro|ST_RX_CRC
mdefine_line|#define ST_RX_CRC     0x04&t;/* CRC */
DECL|macro|ST_ERROR_MASK
mdefine_line|#define ST_ERROR_MASK 0x7C
DECL|macro|DIR_EOTE
mdefine_line|#define DIR_EOTE      0x80      /* Transfer completed */
DECL|macro|DIR_EOME
mdefine_line|#define DIR_EOME      0x40      /* Frame Transfer Completed (chained-block) */
DECL|macro|DIR_BOFE
mdefine_line|#define DIR_BOFE      0x20      /* Buffer Overflow/Underflow (chained-block)*/
DECL|macro|DIR_COFE
mdefine_line|#define DIR_COFE      0x10      /* Counter Overflow (chained-block) */
DECL|macro|DSR_EOT
mdefine_line|#define DSR_EOT       0x80      /* Transfer completed */
DECL|macro|DSR_EOM
mdefine_line|#define DSR_EOM       0x40      /* Frame Transfer Completed (chained-block) */
DECL|macro|DSR_BOF
mdefine_line|#define DSR_BOF       0x20      /* Buffer Overflow/Underflow (chained-block)*/
DECL|macro|DSR_COF
mdefine_line|#define DSR_COF       0x10      /* Counter Overflow (chained-block) */
DECL|macro|DSR_DE
mdefine_line|#define DSR_DE        0x02&t;/* DMA Enable */
DECL|macro|DSR_DWE
mdefine_line|#define DSR_DWE       0x01      /* DMA Write Disable */
multiline_comment|/* DMA Master Enable Register (DMER) bits */
DECL|macro|DMER_DME
mdefine_line|#define DMER_DME      0x80&t;/* DMA Master Enable */
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET     0x21&t;/* Reset Channel */
DECL|macro|CMD_TX_ENABLE
mdefine_line|#define CMD_TX_ENABLE 0x02&t;/* Start transmitter */
DECL|macro|CMD_RX_ENABLE
mdefine_line|#define CMD_RX_ENABLE 0x12&t;/* Start receiver */
DECL|macro|MD0_HDLC
mdefine_line|#define MD0_HDLC      0x80&t;/* Bit-sync HDLC mode */
DECL|macro|MD0_CRC_ENA
mdefine_line|#define MD0_CRC_ENA   0x04&t;/* Enable CRC code calculation */
DECL|macro|MD0_CRC_CCITT
mdefine_line|#define MD0_CRC_CCITT 0x02&t;/* CCITT CRC instead of CRC-16 */
DECL|macro|MD0_CRC_PR1
mdefine_line|#define MD0_CRC_PR1   0x01&t;/* Initial all-ones instead of all-zeros */
DECL|macro|MD0_CRC_NONE
mdefine_line|#define MD0_CRC_NONE  0x00
DECL|macro|MD0_CRC_16_0
mdefine_line|#define MD0_CRC_16_0  0x04
DECL|macro|MD0_CRC_16
mdefine_line|#define MD0_CRC_16    0x05
DECL|macro|MD0_CRC_ITU_0
mdefine_line|#define MD0_CRC_ITU_0 0x06
DECL|macro|MD0_CRC_ITU
mdefine_line|#define MD0_CRC_ITU   0x07
DECL|macro|MD2_NRZI
mdefine_line|#define MD2_NRZI      0x20&t;/* NRZI mode */
DECL|macro|MD2_LOOPBACK
mdefine_line|#define MD2_LOOPBACK  0x03      /* Local data Loopback */
DECL|macro|CTL_NORTS
mdefine_line|#define CTL_NORTS     0x01
DECL|macro|CTL_IDLE
mdefine_line|#define CTL_IDLE      0x10&t;/* Transmit an idle pattern */
DECL|macro|CTL_UDRNC
mdefine_line|#define CTL_UDRNC     0x20&t;/* Idle after CRC or FCS+flag transmition */
DECL|macro|ST0_TXRDY
mdefine_line|#define ST0_TXRDY     0x02&t;/* TX ready */
DECL|macro|ST0_RXRDY
mdefine_line|#define ST0_RXRDY     0x01&t;/* RX ready */
DECL|macro|ST1_UDRN
mdefine_line|#define ST1_UDRN      0x80&t;/* MSCI TX underrun */
DECL|macro|ST3_CTS
mdefine_line|#define ST3_CTS       0x08&t;/* modem input - /CTS */
DECL|macro|ST3_DCD
mdefine_line|#define ST3_DCD       0x04&t;/* modem input - /DCD */
DECL|macro|IE0_TXINT
mdefine_line|#define IE0_TXINT     0x80&t;/* TX INT MSCI interrupt enable */
DECL|macro|IE1_UDRN
mdefine_line|#define IE1_UDRN      0x80&t;/* TX underrun MSCI interrupt enable */
DECL|macro|DCR_ABORT
mdefine_line|#define DCR_ABORT     0x01&t;/* Software abort command */
DECL|macro|DCR_CLEAR_EOF
mdefine_line|#define DCR_CLEAR_EOF 0x02&t;/* Clear EOF interrupt */
multiline_comment|/* TX and RX Clock Source - RXS and TXS */
DECL|macro|CLK_BRG_MASK
mdefine_line|#define CLK_BRG_MASK  0x0F
DECL|macro|CLK_LINE_RX
mdefine_line|#define CLK_LINE_RX   0x00&t;/* TX/RX clock line input */
DECL|macro|CLK_LINE_TX
mdefine_line|#define CLK_LINE_TX   0x00&t;/* TX/RX line input */
DECL|macro|CLK_BRG_RX
mdefine_line|#define CLK_BRG_RX    0x40&t;/* internal baud rate generator */
DECL|macro|CLK_BRG_TX
mdefine_line|#define CLK_BRG_TX    0x40&t;/* internal baud rate generator */
DECL|macro|CLK_RXCLK_TX
mdefine_line|#define CLK_RXCLK_TX  0x60&t;/* TX clock from RX clock */
macro_line|#endif
eof
