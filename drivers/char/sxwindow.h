multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Title&t;&t;:&t;SX Shared Memory Window Structure&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Author&t;&t;:&t;N.P.Vassallo&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Creation&t;:&t;16th March 1998&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Version&t;&t;:&t;3.0.0&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Copyright&t;:&t;(c) Specialix International Ltd. 1998&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Description&t;:&t;Prototypes, structures and definitions&t;*/
multiline_comment|/*&t;&t;&t;&t;describing the SX/SI/XIO cards shared&t;*/
multiline_comment|/*&t;&t;&t;&t;memory window structure:&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;SXCARD&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;SXMODULE&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;SXCHANNEL&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* History...&n;&n;3.0.0&t;16/03/98 NPV&t;Creation. (based on STRUCT.H)&n;&n;*/
macro_line|#ifndef&t;_sxwindow_h&t;&t;&t;&t;/* If SXWINDOW.H not already defined */
DECL|macro|_sxwindow_h
mdefine_line|#define&t;_sxwindow_h    1
multiline_comment|/*****************************************************************************&n;***************************                        ***************************&n;***************************   Common Definitions   ***************************&n;***************************                        ***************************&n;*****************************************************************************/
DECL|typedef|PSXCARD
r_typedef
r_struct
id|_SXCARD
op_star
id|PSXCARD
suffix:semicolon
multiline_comment|/* SXCARD structure pointer */
DECL|typedef|PMOD
r_typedef
r_struct
id|_SXMODULE
op_star
id|PMOD
suffix:semicolon
multiline_comment|/* SXMODULE structure pointer */
DECL|typedef|PCHAN
r_typedef
r_struct
id|_SXCHANNEL
op_star
id|PCHAN
suffix:semicolon
multiline_comment|/* SXCHANNEL structure pointer */
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   SXCARD   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
DECL|struct|_SXCARD
r_typedef
r_struct
id|_SXCARD
(brace
DECL|member|cc_init_status
id|BYTE
id|cc_init_status
suffix:semicolon
multiline_comment|/* 0x00 Initialisation status */
DECL|member|cc_mem_size
id|BYTE
id|cc_mem_size
suffix:semicolon
multiline_comment|/* 0x01 Size of memory on card */
DECL|member|cc_int_count
id|WORD
id|cc_int_count
suffix:semicolon
multiline_comment|/* 0x02 Interrupt count */
DECL|member|cc_revision
id|WORD
id|cc_revision
suffix:semicolon
multiline_comment|/* 0x04 Download code revision */
DECL|member|cc_isr_count
id|BYTE
id|cc_isr_count
suffix:semicolon
multiline_comment|/* 0x06 Count when ISR is run */
DECL|member|cc_main_count
id|BYTE
id|cc_main_count
suffix:semicolon
multiline_comment|/* 0x07 Count when main loop is run */
DECL|member|cc_int_pending
id|WORD
id|cc_int_pending
suffix:semicolon
multiline_comment|/* 0x08 Interrupt pending */
DECL|member|cc_poll_count
id|WORD
id|cc_poll_count
suffix:semicolon
multiline_comment|/* 0x0A Count when poll is run */
DECL|member|cc_int_set_count
id|BYTE
id|cc_int_set_count
suffix:semicolon
multiline_comment|/* 0x0C Count when host interrupt is set */
DECL|member|cc_rfu
id|BYTE
id|cc_rfu
(braket
l_int|0x80
op_minus
l_int|0x0D
)braket
suffix:semicolon
multiline_comment|/* 0x0D Pad structure to 128 bytes (0x80) */
DECL|typedef|SXCARD
)brace
id|SXCARD
suffix:semicolon
multiline_comment|/* SXCARD.cc_init_status definitions... */
DECL|macro|ADAPTERS_FOUND
mdefine_line|#define &t;ADAPTERS_FOUND&t;&t;(BYTE)0x01
DECL|macro|NO_ADAPTERS_FOUND
mdefine_line|#define &t;NO_ADAPTERS_FOUND&t;(BYTE)0xFF
multiline_comment|/* SXCARD.cc_mem_size definitions... */
DECL|macro|SX_MEMORY_SIZE
mdefine_line|#define &t;SX_MEMORY_SIZE&t;&t;(BYTE)0x40
multiline_comment|/* SXCARD.cc_int_count definitions... */
DECL|macro|INT_COUNT_DEFAULT
mdefine_line|#define &t;INT_COUNT_DEFAULT&t;100&t;/* Hz */
multiline_comment|/*****************************************************************************&n;********************************              ********************************&n;********************************   SXMODULE   ********************************&n;********************************              ********************************&n;*****************************************************************************/
DECL|macro|TOP_POINTER
mdefine_line|#define&t;TOP_POINTER(a)&t;&t;((a)|0x8000)&t;/* Sets top bit of word */
DECL|macro|UNTOP_POINTER
mdefine_line|#define UNTOP_POINTER(a)&t;((a)&amp;~0x8000)&t;/* Clears top bit of word */
DECL|struct|_SXMODULE
r_typedef
r_struct
id|_SXMODULE
(brace
DECL|member|mc_next
id|WORD
id|mc_next
suffix:semicolon
multiline_comment|/* 0x00 Next module &quot;pointer&quot; (ORed with 0x8000) */
DECL|member|mc_type
id|BYTE
id|mc_type
suffix:semicolon
multiline_comment|/* 0x02 Type of TA in terms of number of channels */
DECL|member|mc_mod_no
id|BYTE
id|mc_mod_no
suffix:semicolon
multiline_comment|/* 0x03 Module number on SI bus cable (0 closest to card) */
DECL|member|mc_dtr
id|BYTE
id|mc_dtr
suffix:semicolon
multiline_comment|/* 0x04 Private DTR copy (TA only) */
DECL|member|mc_rfu1
id|BYTE
id|mc_rfu1
suffix:semicolon
multiline_comment|/* 0x05 Reserved */
DECL|member|mc_uart
id|WORD
id|mc_uart
suffix:semicolon
multiline_comment|/* 0x06 UART base address for this module */
DECL|member|mc_chip
id|BYTE
id|mc_chip
suffix:semicolon
multiline_comment|/* 0x08 Chip type / number of ports */
DECL|member|mc_current_uart
id|BYTE
id|mc_current_uart
suffix:semicolon
multiline_comment|/* 0x09 Current uart selected for this module */
macro_line|#ifdef&t;DOWNLOAD
DECL|member|mc_chan_pointer
id|PCHAN
id|mc_chan_pointer
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0A Pointer to each channel structure */
macro_line|#else
DECL|member|mc_chan_pointer
id|WORD
id|mc_chan_pointer
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0A Define as WORD if not compiling into download */
macro_line|#endif
DECL|member|mc_rfu2
id|WORD
id|mc_rfu2
suffix:semicolon
multiline_comment|/* 0x1A Reserved */
DECL|member|mc_opens1
id|BYTE
id|mc_opens1
suffix:semicolon
multiline_comment|/* 0x1C Number of open ports on first four ports on MTA/SXDC */
DECL|member|mc_opens2
id|BYTE
id|mc_opens2
suffix:semicolon
multiline_comment|/* 0x1D Number of open ports on second four ports on MTA/SXDC */
DECL|member|mc_mods
id|BYTE
id|mc_mods
suffix:semicolon
multiline_comment|/* 0x1E Types of connector module attached to MTA/SXDC */
DECL|member|mc_rev1
id|BYTE
id|mc_rev1
suffix:semicolon
multiline_comment|/* 0x1F Revision of first CD1400 on MTA/SXDC */
DECL|member|mc_rev2
id|BYTE
id|mc_rev2
suffix:semicolon
multiline_comment|/* 0x20 Revision of second CD1400 on MTA/SXDC */
DECL|member|mc_mtaasic_rev
id|BYTE
id|mc_mtaasic_rev
suffix:semicolon
multiline_comment|/* 0x21 Revision of MTA ASIC 1..4 -&gt; A, B, C, D */
DECL|member|mc_rfu3
id|BYTE
id|mc_rfu3
(braket
l_int|0x100
op_minus
l_int|0x22
)braket
suffix:semicolon
multiline_comment|/* 0x22 Pad structure to 256 bytes (0x100) */
DECL|typedef|SXMODULE
)brace
id|SXMODULE
suffix:semicolon
multiline_comment|/* SXMODULE.mc_type definitions... */
DECL|macro|FOUR_PORTS
mdefine_line|#define&t;&t;FOUR_PORTS&t;(BYTE)4
DECL|macro|EIGHT_PORTS
mdefine_line|#define &t;EIGHT_PORTS&t;(BYTE)8
multiline_comment|/* SXMODULE.mc_chip definitions... */
DECL|macro|CHIP_MASK
mdefine_line|#define &t;CHIP_MASK&t;0xF0
DECL|macro|TA
mdefine_line|#define&t;&t;TA&t;&t;(BYTE)0
DECL|macro|TA4
mdefine_line|#define &t;TA4&t;&t;(TA | FOUR_PORTS)
DECL|macro|TA8
mdefine_line|#define &t;TA8&t;&t;(TA | EIGHT_PORTS)
DECL|macro|TA4_ASIC
mdefine_line|#define&t;&t;TA4_ASIC&t;(BYTE)0x0A
DECL|macro|TA8_ASIC
mdefine_line|#define&t;&t;TA8_ASIC&t;(BYTE)0x0B
DECL|macro|MTA_CD1400
mdefine_line|#define &t;MTA_CD1400&t;(BYTE)0x28
DECL|macro|SXDC
mdefine_line|#define &t;SXDC&t;&t;(BYTE)0x48
multiline_comment|/* SXMODULE.mc_mods definitions... */
DECL|macro|MOD_RS232DB25
mdefine_line|#define&t;&t;MOD_RS232DB25&t;0x00&t;&t;/* RS232 DB25 (socket/plug) */
DECL|macro|MOD_RS232RJ45
mdefine_line|#define&t;&t;MOD_RS232RJ45&t;0x01&t;&t;/* RS232 RJ45 (shielded/opto-isolated) */
DECL|macro|MOD_RESERVED_2
mdefine_line|#define&t;&t;MOD_RESERVED_2&t;0x02&t;&t;/* Reserved (RS485) */
DECL|macro|MOD_RS422DB25
mdefine_line|#define&t;&t;MOD_RS422DB25&t;0x03&t;&t;/* RS422 DB25 Socket */
DECL|macro|MOD_RESERVED_4
mdefine_line|#define&t;&t;MOD_RESERVED_4&t;0x04&t;&t;/* Reserved */
DECL|macro|MOD_PARALLEL
mdefine_line|#define&t;&t;MOD_PARALLEL&t;0x05&t;&t;/* Parallel */
DECL|macro|MOD_RESERVED_6
mdefine_line|#define&t;&t;MOD_RESERVED_6&t;0x06&t;&t;/* Reserved (RS423) */
DECL|macro|MOD_RESERVED_7
mdefine_line|#define&t;&t;MOD_RESERVED_7&t;0x07&t;&t;/* Reserved */
DECL|macro|MOD_2_RS232DB25
mdefine_line|#define&t;&t;MOD_2_RS232DB25&t;0x08&t;&t;/* Rev 2.0 RS232 DB25 (socket/plug) */
DECL|macro|MOD_2_RS232RJ45
mdefine_line|#define&t;&t;MOD_2_RS232RJ45&t;0x09&t;&t;/* Rev 2.0 RS232 RJ45 */
DECL|macro|MOD_RESERVED_A
mdefine_line|#define&t;&t;MOD_RESERVED_A&t;0x0A&t;&t;/* Rev 2.0 Reserved */
DECL|macro|MOD_2_RS422DB25
mdefine_line|#define&t;&t;MOD_2_RS422DB25&t;0x0B&t;&t;/* Rev 2.0 RS422 DB25 */
DECL|macro|MOD_RESERVED_C
mdefine_line|#define&t;&t;MOD_RESERVED_C&t;0x0C&t;&t;/* Rev 2.0 Reserved */
DECL|macro|MOD_2_PARALLEL
mdefine_line|#define&t;&t;MOD_2_PARALLEL&t;0x0D&t;&t;/* Rev 2.0 Parallel */
DECL|macro|MOD_RESERVED_E
mdefine_line|#define&t;&t;MOD_RESERVED_E&t;0x0E&t;&t;/* Rev 2.0 Reserved */
DECL|macro|MOD_BLANK
mdefine_line|#define&t;&t;MOD_BLANK&t;0x0F&t;&t;/* Blank Panel */
multiline_comment|/*****************************************************************************&n;********************************               *******************************&n;********************************   SXCHANNEL   *******************************&n;********************************               *******************************&n;*****************************************************************************/
DECL|macro|TX_BUFF_OFFSET
mdefine_line|#define&t;&t;TX_BUFF_OFFSET&t;&t;0x60&t;/* Transmit buffer offset in channel structure */
DECL|macro|BUFF_POINTER
mdefine_line|#define&t;&t;BUFF_POINTER(a)&t;&t;(((a)+TX_BUFF_OFFSET)|0x8000)
DECL|macro|UNBUFF_POINTER
mdefine_line|#define&t;&t;UNBUFF_POINTER(a)&t;(jet_channel*)(((a)&amp;~0x8000)-TX_BUFF_OFFSET) 
DECL|macro|BUFFER_SIZE
mdefine_line|#define &t;BUFFER_SIZE&t;&t;256
DECL|macro|HIGH_WATER
mdefine_line|#define &t;HIGH_WATER&t;&t;((BUFFER_SIZE / 4) * 3)
DECL|macro|LOW_WATER
mdefine_line|#define &t;LOW_WATER&t;&t;(BUFFER_SIZE / 4)
DECL|struct|_SXCHANNEL
r_typedef
r_struct
id|_SXCHANNEL
(brace
DECL|member|next_item
id|WORD
id|next_item
suffix:semicolon
multiline_comment|/* 0x00 Offset from window base of next channels hi_txbuf (ORred with 0x8000) */
DECL|member|addr_uart
id|WORD
id|addr_uart
suffix:semicolon
multiline_comment|/* 0x02 INTERNAL pointer to uart address. Includes FASTPATH bit */
DECL|member|module
id|WORD
id|module
suffix:semicolon
multiline_comment|/* 0x04 Offset from window base of parent SXMODULE structure */
DECL|member|type
id|BYTE
id|type
suffix:semicolon
multiline_comment|/* 0x06 Chip type / number of ports (copy of mc_chip) */
DECL|member|chan_number
id|BYTE
id|chan_number
suffix:semicolon
multiline_comment|/* 0x07 Channel number on the TA/MTA/SXDC */
DECL|member|xc_status
id|WORD
id|xc_status
suffix:semicolon
multiline_comment|/* 0x08 Flow control and I/O status */
DECL|member|hi_rxipos
id|BYTE
id|hi_rxipos
suffix:semicolon
multiline_comment|/* 0x0A Receive buffer input index */
DECL|member|hi_rxopos
id|BYTE
id|hi_rxopos
suffix:semicolon
multiline_comment|/* 0x0B Receive buffer output index */
DECL|member|hi_txopos
id|BYTE
id|hi_txopos
suffix:semicolon
multiline_comment|/* 0x0C Transmit buffer output index */
DECL|member|hi_txipos
id|BYTE
id|hi_txipos
suffix:semicolon
multiline_comment|/* 0x0D Transmit buffer input index */
DECL|member|hi_hstat
id|BYTE
id|hi_hstat
suffix:semicolon
multiline_comment|/* 0x0E Command register */
DECL|member|dtr_bit
id|BYTE
id|dtr_bit
suffix:semicolon
multiline_comment|/* 0x0F INTERNAL DTR control byte (TA only) */
DECL|member|txon
id|BYTE
id|txon
suffix:semicolon
multiline_comment|/* 0x10 INTERNAL copy of hi_txon */
DECL|member|txoff
id|BYTE
id|txoff
suffix:semicolon
multiline_comment|/* 0x11 INTERNAL copy of hi_txoff */
DECL|member|rxon
id|BYTE
id|rxon
suffix:semicolon
multiline_comment|/* 0x12 INTERNAL copy of hi_rxon */
DECL|member|rxoff
id|BYTE
id|rxoff
suffix:semicolon
multiline_comment|/* 0x13 INTERNAL copy of hi_rxoff */
DECL|member|hi_mr1
id|BYTE
id|hi_mr1
suffix:semicolon
multiline_comment|/* 0x14 Mode Register 1 (databits,parity,RTS rx flow)*/
DECL|member|hi_mr2
id|BYTE
id|hi_mr2
suffix:semicolon
multiline_comment|/* 0x15 Mode Register 2 (stopbits,local,CTS tx flow)*/
DECL|member|hi_csr
id|BYTE
id|hi_csr
suffix:semicolon
multiline_comment|/* 0x16 Clock Select Register (baud rate) */
DECL|member|hi_op
id|BYTE
id|hi_op
suffix:semicolon
multiline_comment|/* 0x17 Modem Output Signal */
DECL|member|hi_ip
id|BYTE
id|hi_ip
suffix:semicolon
multiline_comment|/* 0x18 Modem Input Signal */
DECL|member|hi_state
id|BYTE
id|hi_state
suffix:semicolon
multiline_comment|/* 0x19 Channel status */
DECL|member|hi_prtcl
id|BYTE
id|hi_prtcl
suffix:semicolon
multiline_comment|/* 0x1A Channel protocol (flow control) */
DECL|member|hi_txon
id|BYTE
id|hi_txon
suffix:semicolon
multiline_comment|/* 0x1B Transmit XON character */
DECL|member|hi_txoff
id|BYTE
id|hi_txoff
suffix:semicolon
multiline_comment|/* 0x1C Transmit XOFF character */
DECL|member|hi_rxon
id|BYTE
id|hi_rxon
suffix:semicolon
multiline_comment|/* 0x1D Receive XON character */
DECL|member|hi_rxoff
id|BYTE
id|hi_rxoff
suffix:semicolon
multiline_comment|/* 0x1E Receive XOFF character */
DECL|member|close_prev
id|BYTE
id|close_prev
suffix:semicolon
multiline_comment|/* 0x1F INTERNAL channel previously closed flag */
DECL|member|hi_break
id|BYTE
id|hi_break
suffix:semicolon
multiline_comment|/* 0x20 Break and error control */
DECL|member|break_state
id|BYTE
id|break_state
suffix:semicolon
multiline_comment|/* 0x21 INTERNAL copy of hi_break */
DECL|member|hi_mask
id|BYTE
id|hi_mask
suffix:semicolon
multiline_comment|/* 0x22 Mask for received data */
DECL|member|mask
id|BYTE
id|mask
suffix:semicolon
multiline_comment|/* 0x23 INTERNAL copy of hi_mask */
DECL|member|mod_type
id|BYTE
id|mod_type
suffix:semicolon
multiline_comment|/* 0x24 MTA/SXDC hardware module type */
DECL|member|ccr_state
id|BYTE
id|ccr_state
suffix:semicolon
multiline_comment|/* 0x25 INTERNAL MTA/SXDC state of CCR register */
DECL|member|ip_mask
id|BYTE
id|ip_mask
suffix:semicolon
multiline_comment|/* 0x26 Input handshake mask */
DECL|member|hi_parallel
id|BYTE
id|hi_parallel
suffix:semicolon
multiline_comment|/* 0x27 Parallel port flag */
DECL|member|par_error
id|BYTE
id|par_error
suffix:semicolon
multiline_comment|/* 0x28 Error code for parallel loopback test */
DECL|member|any_sent
id|BYTE
id|any_sent
suffix:semicolon
multiline_comment|/* 0x29 INTERNAL data sent flag */
DECL|member|asic_txfifo_size
id|BYTE
id|asic_txfifo_size
suffix:semicolon
multiline_comment|/* 0x2A INTERNAL SXDC transmit FIFO size */
DECL|member|rfu1
id|BYTE
id|rfu1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x2B Reserved */
DECL|member|csr
id|BYTE
id|csr
suffix:semicolon
multiline_comment|/* 0x2D INTERNAL copy of hi_csr */
macro_line|#ifdef&t;DOWNLOAD
DECL|member|nextp
id|PCHAN
id|nextp
suffix:semicolon
multiline_comment|/* 0x2E Offset from window base of next channel structure */
macro_line|#else
DECL|member|nextp
id|WORD
id|nextp
suffix:semicolon
multiline_comment|/* 0x2E Define as WORD if not compiling into download */
macro_line|#endif
DECL|member|prtcl
id|BYTE
id|prtcl
suffix:semicolon
multiline_comment|/* 0x30 INTERNAL copy of hi_prtcl */
DECL|member|mr1
id|BYTE
id|mr1
suffix:semicolon
multiline_comment|/* 0x31 INTERNAL copy of hi_mr1 */
DECL|member|mr2
id|BYTE
id|mr2
suffix:semicolon
multiline_comment|/* 0x32 INTERNAL copy of hi_mr2 */
DECL|member|hi_txbaud
id|BYTE
id|hi_txbaud
suffix:semicolon
multiline_comment|/* 0x33 Extended transmit baud rate (SXDC only if((hi_csr&amp;0x0F)==0x0F) */
DECL|member|hi_rxbaud
id|BYTE
id|hi_rxbaud
suffix:semicolon
multiline_comment|/* 0x34 Extended receive baud rate  (SXDC only if((hi_csr&amp;0xF0)==0xF0) */
DECL|member|txbreak_state
id|BYTE
id|txbreak_state
suffix:semicolon
multiline_comment|/* 0x35 INTERNAL MTA/SXDC transmit break state */
DECL|member|txbaud
id|BYTE
id|txbaud
suffix:semicolon
multiline_comment|/* 0x36 INTERNAL copy of hi_txbaud */
DECL|member|rxbaud
id|BYTE
id|rxbaud
suffix:semicolon
multiline_comment|/* 0x37 INTERNAL copy of hi_rxbaud */
DECL|member|err_framing
id|WORD
id|err_framing
suffix:semicolon
multiline_comment|/* 0x38 Count of receive framing errors */
DECL|member|err_parity
id|WORD
id|err_parity
suffix:semicolon
multiline_comment|/* 0x3A Count of receive parity errors */
DECL|member|err_overrun
id|WORD
id|err_overrun
suffix:semicolon
multiline_comment|/* 0x3C Count of receive overrun errors */
DECL|member|err_overflow
id|WORD
id|err_overflow
suffix:semicolon
multiline_comment|/* 0x3E Count of receive buffer overflow errors */
DECL|member|rfu2
id|BYTE
id|rfu2
(braket
id|TX_BUFF_OFFSET
op_minus
l_int|0x40
)braket
suffix:semicolon
multiline_comment|/* 0x40 Reserved until hi_txbuf */
DECL|member|hi_txbuf
id|BYTE
id|hi_txbuf
(braket
id|BUFFER_SIZE
)braket
suffix:semicolon
multiline_comment|/* 0x060 Transmit buffer */
DECL|member|hi_rxbuf
id|BYTE
id|hi_rxbuf
(braket
id|BUFFER_SIZE
)braket
suffix:semicolon
multiline_comment|/* 0x160 Receive buffer */
DECL|member|rfu3
id|BYTE
id|rfu3
(braket
l_int|0x300
op_minus
l_int|0x260
)braket
suffix:semicolon
multiline_comment|/* 0x260 Reserved until 768 bytes (0x300) */
DECL|typedef|SXCHANNEL
)brace
id|SXCHANNEL
suffix:semicolon
multiline_comment|/* SXCHANNEL.addr_uart definitions... */
DECL|macro|FASTPATH
mdefine_line|#define&t;&t;FASTPATH&t;0x1000&t;&t;/* Set to indicate fast rx/tx processing (TA only) */
multiline_comment|/* SXCHANNEL.xc_status definitions... */
DECL|macro|X_TANY
mdefine_line|#define&t;&t;X_TANY&t;&t;0x0001&t;&t;/* XON is any character (TA only) */
DECL|macro|X_TION
mdefine_line|#define&t;&t;X_TION&t;&t;0x0001&t;&t;/* Tx interrupts on (MTA only) */
DECL|macro|X_TXEN
mdefine_line|#define&t;&t;X_TXEN&t;&t;0x0002&t;&t;/* Tx XON/XOFF enabled (TA only) */
DECL|macro|X_RTSEN
mdefine_line|#define&t;&t;X_RTSEN&t;&t;0x0002&t;&t;/* RTS FLOW enabled (MTA only) */
DECL|macro|X_TXRC
mdefine_line|#define&t;&t;X_TXRC&t;&t;0x0004&t;&t;/* XOFF received (TA only) */
DECL|macro|X_RTSLOW
mdefine_line|#define&t;&t;X_RTSLOW&t;0x0004&t;&t;/* RTS dropped (MTA only) */
DECL|macro|X_RXEN
mdefine_line|#define&t;&t;X_RXEN&t;&t;0x0008&t;&t;/* Rx XON/XOFF enabled */
DECL|macro|X_ANYXO
mdefine_line|#define&t;&t;X_ANYXO&t;&t;0x0010&t;&t;/* XOFF pending/sent or RTS dropped */
DECL|macro|X_RXSE
mdefine_line|#define&t;&t;X_RXSE&t;&t;0x0020&t;&t;/* Rx XOFF sent */
DECL|macro|X_NPEND
mdefine_line|#define&t;&t;X_NPEND&t;&t;0x0040&t;&t;/* Rx XON pending or XOFF pending */
DECL|macro|X_FPEND
mdefine_line|#define&t;&t;X_FPEND&t;&t;0x0080&t;&t;/* Rx XOFF pending */
DECL|macro|C_CRSE
mdefine_line|#define&t;&t;C_CRSE&t;&t;0x0100&t;&t;/* Carriage return sent (TA only) */
DECL|macro|C_TEMR
mdefine_line|#define&t;&t;C_TEMR&t;&t;0x0100&t;&t;/* Tx empty requested (MTA only) */
DECL|macro|C_TEMA
mdefine_line|#define&t;&t;C_TEMA&t;&t;0x0200&t;&t;/* Tx empty acked (MTA only) */
DECL|macro|C_ANYP
mdefine_line|#define&t;&t;C_ANYP&t;&t;0x0200&t;&t;/* Any protocol bar tx XON/XOFF (TA only) */
DECL|macro|C_EN
mdefine_line|#define&t;&t;C_EN&t;&t;0x0400&t;&t;/* Cooking enabled (on MTA means port is also || */
DECL|macro|C_HIGH
mdefine_line|#define&t;&t;C_HIGH&t;&t;0x0800&t;&t;/* Buffer previously hit high water */
DECL|macro|C_CTSEN
mdefine_line|#define&t;&t;C_CTSEN&t;&t;0x1000&t;&t;/* CTS automatic flow-control enabled */
DECL|macro|C_DCDEN
mdefine_line|#define&t;&t;C_DCDEN&t;&t;0x2000&t;&t;/* DCD/DTR checking enabled */
DECL|macro|C_BREAK
mdefine_line|#define&t;&t;C_BREAK&t;&t;0x4000&t;&t;/* Break detected */
DECL|macro|C_RTSEN
mdefine_line|#define&t;&t;C_RTSEN&t;&t;0x8000&t;&t;/* RTS automatic flow control enabled (MTA only) */
DECL|macro|C_PARITY
mdefine_line|#define&t;&t;C_PARITY&t;0x8000&t;&t;/* Parity checking enabled (TA only) */
multiline_comment|/* SXCHANNEL.hi_hstat definitions... */
DECL|macro|HS_IDLE_OPEN
mdefine_line|#define&t;&t;HS_IDLE_OPEN&t;0x00&t;&t;/* Channel open state */
DECL|macro|HS_LOPEN
mdefine_line|#define&t;&t;HS_LOPEN&t;0x02&t;&t;/* Local open command (no modem monitoring) */
DECL|macro|HS_MOPEN
mdefine_line|#define&t;&t;HS_MOPEN&t;0x04&t;&t;/* Modem open command (wait for DCD signal) */
DECL|macro|HS_IDLE_MPEND
mdefine_line|#define&t;&t;HS_IDLE_MPEND&t;0x06&t;&t;/* Waiting for DCD signal state */
DECL|macro|HS_CONFIG
mdefine_line|#define&t;&t;HS_CONFIG&t;0x08&t;&t;/* Configuration command */
DECL|macro|HS_CLOSE
mdefine_line|#define&t;&t;HS_CLOSE&t;0x0A&t;&t;/* Close command */
DECL|macro|HS_START
mdefine_line|#define&t;&t;HS_START&t;0x0C&t;&t;/* Start transmit break command */
DECL|macro|HS_STOP
mdefine_line|#define&t;&t;HS_STOP&t;&t;0x0E&t;&t;/* Stop transmit break command */
DECL|macro|HS_IDLE_CLOSED
mdefine_line|#define&t;&t;HS_IDLE_CLOSED&t;0x10&t;&t;/* Closed channel state */
DECL|macro|HS_IDLE_BREAK
mdefine_line|#define&t;&t;HS_IDLE_BREAK&t;0x12&t;&t;/* Transmit break state */
DECL|macro|HS_FORCE_CLOSED
mdefine_line|#define&t;&t;HS_FORCE_CLOSED&t;0x14&t;&t;/* Force close command */
DECL|macro|HS_RESUME
mdefine_line|#define&t;&t;HS_RESUME&t;0x16&t;&t;/* Clear pending XOFF command */
DECL|macro|HS_WFLUSH
mdefine_line|#define&t;&t;HS_WFLUSH&t;0x18&t;&t;/* Flush transmit buffer command */
DECL|macro|HS_RFLUSH
mdefine_line|#define&t;&t;HS_RFLUSH&t;0x1A&t;&t;/* Flush receive buffer command */
DECL|macro|HS_SUSPEND
mdefine_line|#define&t;&t;HS_SUSPEND&t;0x1C&t;&t;/* Suspend output command (like XOFF received) */
DECL|macro|PARALLEL
mdefine_line|#define&t;&t;PARALLEL&t;0x1E&t;&t;/* Parallel port loopback test command (Diagnostics Only) */
DECL|macro|ENABLE_RX_INTS
mdefine_line|#define&t;&t;ENABLE_RX_INTS&t;0x20&t;&t;/* Enable receive interrupts command (Diagnostics Only) */
DECL|macro|ENABLE_TX_INTS
mdefine_line|#define&t;&t;ENABLE_TX_INTS&t;0x22&t;&t;/* Enable transmit interrupts command (Diagnostics Only) */
DECL|macro|ENABLE_MDM_INTS
mdefine_line|#define&t;&t;ENABLE_MDM_INTS&t;0x24&t;&t;/* Enable modem interrupts command (Diagnostics Only) */
DECL|macro|DISABLE_INTS
mdefine_line|#define&t;&t;DISABLE_INTS&t;0x26&t;&t;/* Disable interrupts command (Diagnostics Only) */
multiline_comment|/* SXCHANNEL.hi_mr1 definitions... */
DECL|macro|MR1_BITS
mdefine_line|#define&t;&t;MR1_BITS&t;0x03&t;&t;/* Data bits mask */
DECL|macro|MR1_5_BITS
mdefine_line|#define&t;&t;MR1_5_BITS&t;0x00&t;&t;/* 5 data bits */
DECL|macro|MR1_6_BITS
mdefine_line|#define&t;&t;MR1_6_BITS&t;0x01&t;&t;/* 6 data bits */
DECL|macro|MR1_7_BITS
mdefine_line|#define&t;&t;MR1_7_BITS&t;0x02&t;&t;/* 7 data bits */
DECL|macro|MR1_8_BITS
mdefine_line|#define&t;&t;MR1_8_BITS&t;0x03&t;&t;/* 8 data bits */
DECL|macro|MR1_PARITY
mdefine_line|#define&t;&t;MR1_PARITY&t;0x1C&t;&t;/* Parity mask */
DECL|macro|MR1_ODD
mdefine_line|#define&t;&t;MR1_ODD&t;&t;0x04&t;&t;/* Odd parity */
DECL|macro|MR1_EVEN
mdefine_line|#define&t;&t;MR1_EVEN&t;0x00&t;&t;/* Even parity */
DECL|macro|MR1_WITH
mdefine_line|#define&t;&t;MR1_WITH&t;0x00&t;&t;/* Parity enabled */
DECL|macro|MR1_FORCE
mdefine_line|#define&t;&t;MR1_FORCE&t;0x08&t;&t;/* Force parity */
DECL|macro|MR1_NONE
mdefine_line|#define&t;&t;MR1_NONE&t;0x10&t;&t;/* No parity */
DECL|macro|MR1_NOPARITY
mdefine_line|#define&t;&t;MR1_NOPARITY&t;MR1_NONE&t;&t;/* No parity */
DECL|macro|MR1_ODDPARITY
mdefine_line|#define&t;&t;MR1_ODDPARITY&t;(MR1_WITH|MR1_ODD)&t;/* Odd parity */
DECL|macro|MR1_EVENPARITY
mdefine_line|#define&t;&t;MR1_EVENPARITY&t;(MR1_WITH|MR1_EVEN)&t;/* Even parity */
DECL|macro|MR1_MARKPARITY
mdefine_line|#define&t;&t;MR1_MARKPARITY&t;(MR1_FORCE|MR1_ODD)&t;/* Mark parity */
DECL|macro|MR1_SPACEPARITY
mdefine_line|#define&t;&t;MR1_SPACEPARITY&t;(MR1_FORCE|MR1_EVEN)&t;/* Space parity */
DECL|macro|MR1_RTS_RXFLOW
mdefine_line|#define&t;&t;MR1_RTS_RXFLOW&t;0x80&t;&t;/* RTS receive flow control */
multiline_comment|/* SXCHANNEL.hi_mr2 definitions... */
DECL|macro|MR2_STOP
mdefine_line|#define&t;&t;MR2_STOP&t;0x0F&t;&t;/* Stop bits mask */
DECL|macro|MR2_1_STOP
mdefine_line|#define&t;&t;MR2_1_STOP&t;0x07&t;&t;/* 1 stop bit */
DECL|macro|MR2_2_STOP
mdefine_line|#define&t;&t;MR2_2_STOP&t;0x0F&t;&t;/* 2 stop bits */
DECL|macro|MR2_CTS_TXFLOW
mdefine_line|#define&t;&t;MR2_CTS_TXFLOW&t;0x10&t;&t;/* CTS transmit flow control */
DECL|macro|MR2_RTS_TOGGLE
mdefine_line|#define&t;&t;MR2_RTS_TOGGLE&t;0x20&t;&t;/* RTS toggle on transmit */
DECL|macro|MR2_NORMAL
mdefine_line|#define&t;&t;MR2_NORMAL&t;0x00&t;&t;/* Normal mode */
DECL|macro|MR2_AUTO
mdefine_line|#define&t;&t;MR2_AUTO&t;0x40&t;&t;/* Auto-echo mode (TA only) */
DECL|macro|MR2_LOCAL
mdefine_line|#define&t;&t;MR2_LOCAL&t;0x80&t;&t;/* Local echo mode */
DECL|macro|MR2_REMOTE
mdefine_line|#define&t;&t;MR2_REMOTE&t;0xC0&t;&t;/* Remote echo mode (TA only) */
multiline_comment|/* SXCHANNEL.hi_csr definitions... */
DECL|macro|CSR_75
mdefine_line|#define&t;&t;CSR_75&t;&t;0x0&t;&t;/*    75 baud */
DECL|macro|CSR_110
mdefine_line|#define&t;&t;CSR_110&t;&t;0x1&t;&t;/*   110 baud (TA), 115200 (MTA/SXDC) */
DECL|macro|CSR_38400
mdefine_line|#define&t;&t;CSR_38400&t;0x2&t;&t;/* 38400 baud */
DECL|macro|CSR_150
mdefine_line|#define&t;&t;CSR_150&t;&t;0x3&t;&t;/*   150 baud */
DECL|macro|CSR_300
mdefine_line|#define&t;&t;CSR_300&t;&t;0x4&t;&t;/*   300 baud */
DECL|macro|CSR_600
mdefine_line|#define&t;&t;CSR_600&t;&t;0x5&t;&t;/*   600 baud */
DECL|macro|CSR_1200
mdefine_line|#define&t;&t;CSR_1200&t;0x6&t;&t;/*  1200 baud */
DECL|macro|CSR_2000
mdefine_line|#define&t;&t;CSR_2000&t;0x7&t;&t;/*  2000 baud */
DECL|macro|CSR_2400
mdefine_line|#define&t;&t;CSR_2400&t;0x8&t;&t;/*  2400 baud */
DECL|macro|CSR_4800
mdefine_line|#define&t;&t;CSR_4800&t;0x9&t;&t;/*  4800 baud */
DECL|macro|CSR_1800
mdefine_line|#define&t;&t;CSR_1800&t;0xA&t;&t;/*  1800 baud */
DECL|macro|CSR_9600
mdefine_line|#define&t;&t;CSR_9600&t;0xB&t;&t;/*  9600 baud */
DECL|macro|CSR_19200
mdefine_line|#define&t;&t;CSR_19200&t;0xC&t;&t;/* 19200 baud */
DECL|macro|CSR_57600
mdefine_line|#define&t;&t;CSR_57600&t;0xD&t;&t;/* 57600 baud */
DECL|macro|CSR_EXTBAUD
mdefine_line|#define&t;&t;CSR_EXTBAUD&t;0xF&t;&t;/* Extended baud rate (hi_txbaud/hi_rxbaud) */
multiline_comment|/* SXCHANNEL.hi_op definitions... */
DECL|macro|OP_RTS
mdefine_line|#define&t;&t;OP_RTS&t;&t;0x01&t;&t;/* RTS modem output signal */
DECL|macro|OP_DTR
mdefine_line|#define&t;&t;OP_DTR&t;&t;0x02&t;&t;/* DTR modem output signal */
multiline_comment|/* SXCHANNEL.hi_ip definitions... */
DECL|macro|IP_CTS
mdefine_line|#define&t;&t;IP_CTS&t;&t;0x02&t;&t;/* CTS modem input signal */
DECL|macro|IP_DCD
mdefine_line|#define&t;&t;IP_DCD&t;&t;0x04&t;&t;/* DCD modem input signal */
DECL|macro|IP_DSR
mdefine_line|#define&t;&t;IP_DSR&t;&t;0x20&t;&t;/* DTR modem input signal */
DECL|macro|IP_RI
mdefine_line|#define&t;&t;IP_RI&t;&t;0x40&t;&t;/* RI modem input signal */
multiline_comment|/* SXCHANNEL.hi_state definitions... */
DECL|macro|ST_BREAK
mdefine_line|#define&t;&t;ST_BREAK&t;0x01&t;&t;/* Break received (clear with config) */
DECL|macro|ST_DCD
mdefine_line|#define&t;&t;ST_DCD&t;&t;0x02&t;&t;/* DCD signal changed state */
multiline_comment|/* SXCHANNEL.hi_prtcl definitions... */
DECL|macro|SP_TANY
mdefine_line|#define&t;&t;SP_TANY&t;&t;0x01&t;&t;/* Transmit XON/XANY (if SP_TXEN enabled) */
DECL|macro|SP_TXEN
mdefine_line|#define&t;&t;SP_TXEN&t;&t;0x02&t;&t;/* Transmit XON/XOFF flow control */
DECL|macro|SP_CEN
mdefine_line|#define&t;&t;SP_CEN&t;&t;0x04&t;&t;/* Cooking enabled */
DECL|macro|SP_RXEN
mdefine_line|#define&t;&t;SP_RXEN&t;&t;0x08&t;&t;/* Rx XON/XOFF enabled */
DECL|macro|SP_DCEN
mdefine_line|#define&t;&t;SP_DCEN&t;&t;0x20&t;&t;/* DCD / DTR check */
DECL|macro|SP_DTR_RXFLOW
mdefine_line|#define&t;&t;SP_DTR_RXFLOW&t;0x40&t;&t;/* DTR receive flow control */
DECL|macro|SP_PAEN
mdefine_line|#define&t;&t;SP_PAEN&t;&t;0x80&t;&t;/* Parity checking enabled */
multiline_comment|/* SXCHANNEL.hi_break definitions... */
DECL|macro|BR_IGN
mdefine_line|#define&t;&t;BR_IGN&t;&t;0x01&t;&t;/* Ignore any received breaks */
DECL|macro|BR_INT
mdefine_line|#define&t;&t;BR_INT&t;&t;0x02&t;&t;/* Interrupt on received break */
DECL|macro|BR_PARMRK
mdefine_line|#define&t;&t;BR_PARMRK&t;0x04&t;&t;/* Enable parmrk parity error processing */
DECL|macro|BR_PARIGN
mdefine_line|#define&t;&t;BR_PARIGN&t;0x08&t;&t;/* Ignore chars with parity errors */
DECL|macro|BR_ERRINT
mdefine_line|#define &t;BR_ERRINT&t;0x80&t;&t;/* Treat parity/framing/overrun errors as exceptions */
multiline_comment|/* SXCHANNEL.par_error definitions.. */
DECL|macro|DIAG_IRQ_RX
mdefine_line|#define&t;&t;DIAG_IRQ_RX&t;0x01&t;&t;/* Indicate serial receive interrupt (diags only) */
DECL|macro|DIAG_IRQ_TX
mdefine_line|#define&t;&t;DIAG_IRQ_TX&t;0x02&t;&t;/* Indicate serial transmit interrupt (diags only) */
DECL|macro|DIAG_IRQ_MD
mdefine_line|#define&t;&t;DIAG_IRQ_MD&t;0x04&t;&t;/* Indicate serial modem interrupt (diags only) */
multiline_comment|/* SXCHANNEL.hi_txbaud/hi_rxbaud definitions... (SXDC only) */
DECL|macro|BAUD_75
mdefine_line|#define&t;&t;BAUD_75&t;&t;0x00&t;&t;/*     75 baud */
DECL|macro|BAUD_115200
mdefine_line|#define&t;&t;BAUD_115200&t;0x01&t;&t;/* 115200 baud */
DECL|macro|BAUD_38400
mdefine_line|#define&t;&t;BAUD_38400&t;0x02&t;&t;/*  38400 baud */
DECL|macro|BAUD_150
mdefine_line|#define&t;&t;BAUD_150&t;0x03&t;&t;/*    150 baud */
DECL|macro|BAUD_300
mdefine_line|#define&t;&t;BAUD_300&t;0x04&t;&t;/*    300 baud */
DECL|macro|BAUD_600
mdefine_line|#define&t;&t;BAUD_600&t;0x05&t;&t;/*    600 baud */
DECL|macro|BAUD_1200
mdefine_line|#define&t;&t;BAUD_1200&t;0x06&t;&t;/*   1200 baud */
DECL|macro|BAUD_2000
mdefine_line|#define&t;&t;BAUD_2000&t;0x07&t;&t;/*   2000 baud */
DECL|macro|BAUD_2400
mdefine_line|#define&t;&t;BAUD_2400&t;0x08&t;&t;/*   2400 baud */
DECL|macro|BAUD_4800
mdefine_line|#define&t;&t;BAUD_4800&t;0x09&t;&t;/*   4800 baud */
DECL|macro|BAUD_1800
mdefine_line|#define&t;&t;BAUD_1800&t;0x0A&t;&t;/*   1800 baud */
DECL|macro|BAUD_9600
mdefine_line|#define&t;&t;BAUD_9600&t;0x0B&t;&t;/*   9600 baud */
DECL|macro|BAUD_19200
mdefine_line|#define&t;&t;BAUD_19200&t;0x0C&t;&t;/*  19200 baud */
DECL|macro|BAUD_57600
mdefine_line|#define&t;&t;BAUD_57600&t;0x0D&t;&t;/*  57600 baud */
DECL|macro|BAUD_230400
mdefine_line|#define&t;&t;BAUD_230400&t;0x0E&t;&t;/* 230400 baud */
DECL|macro|BAUD_460800
mdefine_line|#define&t;&t;BAUD_460800&t;0x0F&t;&t;/* 460800 baud */
DECL|macro|BAUD_921600
mdefine_line|#define&t;&t;BAUD_921600&t;0x10&t;&t;/* 921600 baud */
DECL|macro|BAUD_50
mdefine_line|#define&t;&t;BAUD_50&t;&t;0x11    &t;/*     50 baud */
DECL|macro|BAUD_110
mdefine_line|#define&t;&t;BAUD_110&t;0x12&t;&t;/*    110 baud */
DECL|macro|BAUD_134_5
mdefine_line|#define&t;&t;BAUD_134_5&t;0x13&t;&t;/*  134.5 baud */
DECL|macro|BAUD_200
mdefine_line|#define&t;&t;BAUD_200&t;0x14&t;&t;/*    200 baud */
DECL|macro|BAUD_7200
mdefine_line|#define&t;&t;BAUD_7200&t;0x15&t;&t;/*   7200 baud */
DECL|macro|BAUD_56000
mdefine_line|#define&t;&t;BAUD_56000&t;0x16&t;&t;/*  56000 baud */
DECL|macro|BAUD_64000
mdefine_line|#define&t;&t;BAUD_64000&t;0x17&t;&t;/*  64000 baud */
DECL|macro|BAUD_76800
mdefine_line|#define&t;&t;BAUD_76800&t;0x18&t;&t;/*  76800 baud */
DECL|macro|BAUD_128000
mdefine_line|#define&t;&t;BAUD_128000&t;0x19&t;&t;/* 128000 baud */
DECL|macro|BAUD_150000
mdefine_line|#define&t;&t;BAUD_150000&t;0x1A&t;&t;/* 150000 baud */
DECL|macro|BAUD_14400
mdefine_line|#define&t;&t;BAUD_14400&t;0x1B&t;&t;/*  14400 baud */
DECL|macro|BAUD_256000
mdefine_line|#define&t;&t;BAUD_256000&t;0x1C&t;&t;/* 256000 baud */
DECL|macro|BAUD_28800
mdefine_line|#define&t;&t;BAUD_28800&t;0x1D&t;&t;/*  28800 baud */
multiline_comment|/* SXCHANNEL.txbreak_state definiions... */
DECL|macro|TXBREAK_OFF
mdefine_line|#define&t;&t;TXBREAK_OFF&t;0&t;&t;/* Not sending break */
DECL|macro|TXBREAK_START
mdefine_line|#define&t;&t;TXBREAK_START&t;1&t;&t;/* Begin sending break */
DECL|macro|TXBREAK_START1
mdefine_line|#define&t;&t;TXBREAK_START1&t;2&t;&t;/* Begin sending break, part 1 */
DECL|macro|TXBREAK_ON
mdefine_line|#define&t;&t;TXBREAK_ON&t;3&t;&t;/* Sending break */
DECL|macro|TXBREAK_STOP
mdefine_line|#define&t;&t;TXBREAK_STOP&t;4&t;&t;/* Stop sending break */
DECL|macro|TXBREAK_STOP1
mdefine_line|#define&t;&t;TXBREAK_STOP1&t;5&t;&t;/* Stop sending break, part 1 */
macro_line|#endif&t;&t;&t;&t;&t;&t;/* _sxwindow_h */
multiline_comment|/* End of SXWINDOW.H */
eof
