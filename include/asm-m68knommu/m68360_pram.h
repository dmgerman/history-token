multiline_comment|/***********************************&n; * $Id: m68360_pram.h,v 1.1 2002/03/02 15:01:07 gerg Exp $&n; ***********************************&n; *&n; ***************************************&n; * Definitions of the parameter area RAM.&n; * Note that different structures are overlaid&n; * at the same offsets for the different modes&n; * of operation.&n; ***************************************&n; */
macro_line|#ifndef __PRAM_H
DECL|macro|__PRAM_H
mdefine_line|#define __PRAM_H
multiline_comment|/* Time slot assignment table */
DECL|macro|VALID_SLOT
mdefine_line|#define VALID_SLOT&t;0x8000
DECL|macro|WRAP_SLOT
mdefine_line|#define WRAP_SLOT&t;0x4000
multiline_comment|/*****************************************************************&n;        Global Multichannel parameter RAM&n;*****************************************************************/
DECL|struct|global_multi_pram
r_struct
id|global_multi_pram
(brace
multiline_comment|/*&n;     * Global Multichannel parameter RAM&n;     */
DECL|member|mcbase
r_int
r_int
id|mcbase
suffix:semicolon
multiline_comment|/* Multichannel Base pointer */
DECL|member|qmcstate
r_int
r_int
id|qmcstate
suffix:semicolon
multiline_comment|/* Multichannel Controller state */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Maximum Receive Buffer Length */
DECL|member|tx_s_ptr
r_int
r_int
id|tx_s_ptr
suffix:semicolon
multiline_comment|/* TSTATx Pointer */
DECL|member|rxptr
r_int
r_int
id|rxptr
suffix:semicolon
multiline_comment|/* Current Time slot entry in TSATRx */
DECL|member|grfthr
r_int
r_int
id|grfthr
suffix:semicolon
multiline_comment|/* Global Receive frame threshold */
DECL|member|grfcnt
r_int
r_int
id|grfcnt
suffix:semicolon
multiline_comment|/* Global Receive Frame Count */
DECL|member|intbase
r_int
r_int
id|intbase
suffix:semicolon
multiline_comment|/* Multichannel Base address */
DECL|member|iintptr
r_int
r_int
id|iintptr
suffix:semicolon
multiline_comment|/* Pointer to interrupt queue */
DECL|member|rx_s_ptr
r_int
r_int
id|rx_s_ptr
suffix:semicolon
multiline_comment|/* TSTARx Pointer */
DECL|member|txptr
r_int
r_int
id|txptr
suffix:semicolon
multiline_comment|/* Current Time slot entry in TSATTx */
DECL|member|c_mask32
r_int
r_int
id|c_mask32
suffix:semicolon
multiline_comment|/* CRC Constant (debb20e3) */
DECL|member|tsatrx
r_int
r_int
id|tsatrx
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Time Slot Assignment Table Rx */
DECL|member|tsattx
r_int
r_int
id|tsattx
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Time Slot Assignment Table Tx */
DECL|member|c_mask16
r_int
r_int
id|c_mask16
suffix:semicolon
multiline_comment|/* CRC Constant (f0b8) */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n;        Quicc32 HDLC parameter RAM&n;*****************************************************************/
DECL|struct|quicc32_pram
r_struct
id|quicc32_pram
(brace
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* Tx Buffer Descriptors Base Address */
DECL|member|chamr
r_int
r_int
id|chamr
suffix:semicolon
multiline_comment|/* Channel Mode Register */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx Internal State */
DECL|member|txintr
r_int
r_int
id|txintr
suffix:semicolon
multiline_comment|/* Tx Internal Data Pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx Buffer Descriptor Pointer */
DECL|member|txcntr
r_int
r_int
id|txcntr
suffix:semicolon
multiline_comment|/* Tx Internal Byte Count */
DECL|member|tupack
r_int
r_int
id|tupack
suffix:semicolon
multiline_comment|/* (Tx Temp) */
DECL|member|zistate
r_int
r_int
id|zistate
suffix:semicolon
multiline_comment|/* Zero Insertion machine state */
DECL|member|tcrc
r_int
r_int
id|tcrc
suffix:semicolon
multiline_comment|/* Temp Transmit CRC */
DECL|member|intmask
r_int
r_int
id|intmask
suffix:semicolon
multiline_comment|/* Channel&squot;s interrupt mask flags */
DECL|member|bdflags
r_int
r_int
id|bdflags
suffix:semicolon
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* Rx Buffer Descriptors Base Address */
DECL|member|mflr
r_int
r_int
id|mflr
suffix:semicolon
multiline_comment|/* Max Frame Length Register */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx Internal State */
DECL|member|rxintr
r_int
r_int
id|rxintr
suffix:semicolon
multiline_comment|/* Rx Internal Data Pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* Rx Buffer Descriptor Pointer */
DECL|member|rxbyc
r_int
r_int
id|rxbyc
suffix:semicolon
multiline_comment|/* Rx Internal Byte Count */
DECL|member|rpack
r_int
r_int
id|rpack
suffix:semicolon
multiline_comment|/* (Rx Temp) */
DECL|member|zdstate
r_int
r_int
id|zdstate
suffix:semicolon
multiline_comment|/* Zero Deletion machine state */
DECL|member|rcrc
r_int
r_int
id|rcrc
suffix:semicolon
multiline_comment|/* Temp Transmit CRC */
DECL|member|maxc
r_int
r_int
id|maxc
suffix:semicolon
multiline_comment|/* Max_length counter */
DECL|member|tmp_mb
r_int
r_int
id|tmp_mb
suffix:semicolon
multiline_comment|/* Temp */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n;        HDLC parameter RAM&n;*****************************************************************/
DECL|struct|hdlc_pram
r_struct
id|hdlc_pram
(brace
multiline_comment|/*&n;     * SCC parameter RAM&n;     */
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* RX BD base address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* TX BD base address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
DECL|member|rcrc
r_int
r_int
id|rcrc
suffix:semicolon
multiline_comment|/* temp receive CRC */
DECL|member|tcrc
r_int
r_int
id|tcrc
suffix:semicolon
multiline_comment|/* temp transmit CRC */
multiline_comment|/*&n;     * HDLC specific parameter RAM&n;     */
DECL|member|RESERVED1
r_int
r_char
id|RESERVED1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Reserved area */
DECL|member|c_mask
r_int
r_int
id|c_mask
suffix:semicolon
multiline_comment|/* CRC constant */
DECL|member|c_pres
r_int
r_int
id|c_pres
suffix:semicolon
multiline_comment|/* CRC preset */
DECL|member|disfc
r_int
r_int
id|disfc
suffix:semicolon
multiline_comment|/* discarded frame counter */
DECL|member|crcec
r_int
r_int
id|crcec
suffix:semicolon
multiline_comment|/* CRC error counter */
DECL|member|abtsc
r_int
r_int
id|abtsc
suffix:semicolon
multiline_comment|/* abort sequence counter */
DECL|member|nmarc
r_int
r_int
id|nmarc
suffix:semicolon
multiline_comment|/* nonmatching address rx cnt */
DECL|member|retrc
r_int
r_int
id|retrc
suffix:semicolon
multiline_comment|/* frame retransmission cnt */
DECL|member|mflr
r_int
r_int
id|mflr
suffix:semicolon
multiline_comment|/* maximum frame length reg */
DECL|member|max_cnt
r_int
r_int
id|max_cnt
suffix:semicolon
multiline_comment|/* maximum length counter */
DECL|member|rfthr
r_int
r_int
id|rfthr
suffix:semicolon
multiline_comment|/* received frames threshold */
DECL|member|rfcnt
r_int
r_int
id|rfcnt
suffix:semicolon
multiline_comment|/* received frames count */
DECL|member|hmask
r_int
r_int
id|hmask
suffix:semicolon
multiline_comment|/* user defined frm addr mask */
DECL|member|haddr1
r_int
r_int
id|haddr1
suffix:semicolon
multiline_comment|/* user defined frm address 1 */
DECL|member|haddr2
r_int
r_int
id|haddr2
suffix:semicolon
multiline_comment|/* user defined frm address 2 */
DECL|member|haddr3
r_int
r_int
id|haddr3
suffix:semicolon
multiline_comment|/* user defined frm address 3 */
DECL|member|haddr4
r_int
r_int
id|haddr4
suffix:semicolon
multiline_comment|/* user defined frm address 4 */
DECL|member|tmp
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* temp */
DECL|member|tmp_mb
r_int
r_int
id|tmp_mb
suffix:semicolon
multiline_comment|/* temp */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n;        UART parameter RAM&n;*****************************************************************/
multiline_comment|/*&n; * bits in uart control characters table&n; */
DECL|macro|CC_INVALID
mdefine_line|#define CC_INVALID  0x8000          /* control character is valid */
DECL|macro|CC_REJ
mdefine_line|#define CC_REJ      0x4000          /* don&squot;t store char in buffer */
DECL|macro|CC_CHAR
mdefine_line|#define CC_CHAR     0x00ff          /* control character */
multiline_comment|/* UART */
DECL|struct|uart_pram
r_struct
id|uart_pram
(brace
multiline_comment|/*&n;     * SCC parameter RAM&n;     */
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* RX BD base address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* TX BD base address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rx_temp
r_int
r_int
id|rx_temp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
DECL|member|rcrc
r_int
r_int
id|rcrc
suffix:semicolon
multiline_comment|/* temp receive CRC */
DECL|member|tcrc
r_int
r_int
id|tcrc
suffix:semicolon
multiline_comment|/* temp transmit CRC */
multiline_comment|/*&n;     * UART specific parameter RAM&n;     */
DECL|member|RESERVED1
r_int
r_char
id|RESERVED1
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Reserved area */
DECL|member|max_idl
r_int
r_int
id|max_idl
suffix:semicolon
multiline_comment|/* maximum idle characters */
DECL|member|idlc
r_int
r_int
id|idlc
suffix:semicolon
multiline_comment|/* rx idle counter (internal) */
DECL|member|brkcr
r_int
r_int
id|brkcr
suffix:semicolon
multiline_comment|/* break count register */
DECL|member|parec
r_int
r_int
id|parec
suffix:semicolon
multiline_comment|/* Rx parity error counter */
DECL|member|frmer
r_int
r_int
id|frmer
suffix:semicolon
multiline_comment|/* Rx framing error counter */
DECL|member|nosec
r_int
r_int
id|nosec
suffix:semicolon
multiline_comment|/* Rx noise counter */
DECL|member|brkec
r_int
r_int
id|brkec
suffix:semicolon
multiline_comment|/* Rx break character counter */
DECL|member|brkln
r_int
r_int
id|brkln
suffix:semicolon
multiline_comment|/* Reaceive break length */
DECL|member|uaddr1
r_int
r_int
id|uaddr1
suffix:semicolon
multiline_comment|/* address character 1 */
DECL|member|uaddr2
r_int
r_int
id|uaddr2
suffix:semicolon
multiline_comment|/* address character 2 */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* temp storage */
DECL|member|toseq
r_int
r_int
id|toseq
suffix:semicolon
multiline_comment|/* Tx out of sequence char */
DECL|member|cc
r_int
r_int
id|cc
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Rx control characters */
DECL|member|rccm
r_int
r_int
id|rccm
suffix:semicolon
multiline_comment|/* Rx control char mask */
DECL|member|rccr
r_int
r_int
id|rccr
suffix:semicolon
multiline_comment|/* Rx control char register */
DECL|member|rlbc
r_int
r_int
id|rlbc
suffix:semicolon
multiline_comment|/* Receive last break char */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n;        BISYNC parameter RAM&n;*****************************************************************/
DECL|struct|bisync_pram
r_struct
id|bisync_pram
(brace
multiline_comment|/*&n;     * SCC parameter RAM&n;     */
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* RX BD base address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* TX BD base address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
DECL|member|rcrc
r_int
r_int
id|rcrc
suffix:semicolon
multiline_comment|/* temp receive CRC */
DECL|member|tcrc
r_int
r_int
id|tcrc
suffix:semicolon
multiline_comment|/* temp transmit CRC */
multiline_comment|/*&n;     * BISYNC specific parameter RAM&n;     */
DECL|member|RESERVED1
r_int
r_char
id|RESERVED1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Reserved area */
DECL|member|crcc
r_int
r_int
id|crcc
suffix:semicolon
multiline_comment|/* CRC Constant Temp Value */
DECL|member|prcrc
r_int
r_int
id|prcrc
suffix:semicolon
multiline_comment|/* Preset Receiver CRC-16/LRC */
DECL|member|ptcrc
r_int
r_int
id|ptcrc
suffix:semicolon
multiline_comment|/* Preset Transmitter CRC-16/LRC */
DECL|member|parec
r_int
r_int
id|parec
suffix:semicolon
multiline_comment|/* Receive Parity Error Counter */
DECL|member|bsync
r_int
r_int
id|bsync
suffix:semicolon
multiline_comment|/* BISYNC SYNC Character */
DECL|member|bdle
r_int
r_int
id|bdle
suffix:semicolon
multiline_comment|/* BISYNC DLE Character */
DECL|member|cc
r_int
r_int
id|cc
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Rx control characters */
DECL|member|rccm
r_int
r_int
id|rccm
suffix:semicolon
multiline_comment|/* Receive Control Character Mask */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n;        IOM2 parameter RAM&n;        (overlaid on tx bd[5] of SCC channel[2])&n;*****************************************************************/
DECL|struct|iom2_pram
r_struct
id|iom2_pram
(brace
DECL|member|ci_data
r_int
r_int
id|ci_data
suffix:semicolon
multiline_comment|/* ci data */
DECL|member|monitor_data
r_int
r_int
id|monitor_data
suffix:semicolon
multiline_comment|/* monitor data */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* transmitter state */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* receiver state */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n;        SPI/SMC parameter RAM&n;        (overlaid on tx bd[6,7] of SCC channel[2])&n;*****************************************************************/
DECL|macro|SPI_R
mdefine_line|#define SPI_R       0x8000          /* Ready bit in BD */
DECL|struct|spi_pram
r_struct
id|spi_pram
(brace
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* Rx BD Base Address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* Tx BD Base Address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
)brace
suffix:semicolon
DECL|struct|smc_uart_pram
r_struct
id|smc_uart_pram
(brace
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* Rx BD Base Address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* Tx BD Base Address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
DECL|member|max_idl
r_int
r_int
id|max_idl
suffix:semicolon
multiline_comment|/* Maximum IDLE Characters */
DECL|member|idlc
r_int
r_int
id|idlc
suffix:semicolon
multiline_comment|/* Temporary IDLE Counter */
DECL|member|brkln
r_int
r_int
id|brkln
suffix:semicolon
multiline_comment|/* Last Rx Break Length */
DECL|member|brkec
r_int
r_int
id|brkec
suffix:semicolon
multiline_comment|/* Rx Break Condition Counter */
DECL|member|brkcr
r_int
r_int
id|brkcr
suffix:semicolon
multiline_comment|/* Break Count Register (Tx) */
DECL|member|r_mask
r_int
r_int
id|r_mask
suffix:semicolon
multiline_comment|/* Temporary bit mask */
)brace
suffix:semicolon
DECL|struct|smc_trnsp_pram
r_struct
id|smc_trnsp_pram
(brace
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* rx BD Base Address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* Tx BD Base Address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Reserved */
)brace
suffix:semicolon
DECL|struct|idma_pram
r_struct
id|idma_pram
(brace
DECL|member|ibase
r_int
r_int
id|ibase
suffix:semicolon
multiline_comment|/* IDMA BD Base Address */
DECL|member|ibptr
r_int
r_int
id|ibptr
suffix:semicolon
multiline_comment|/* IDMA buffer descriptor pointer */
DECL|member|istate
r_int
r_int
id|istate
suffix:semicolon
multiline_comment|/* IDMA internal state */
DECL|member|itemp
r_int
r_int
id|itemp
suffix:semicolon
multiline_comment|/* IDMA temp */
)brace
suffix:semicolon
DECL|struct|ethernet_pram
r_struct
id|ethernet_pram
(brace
multiline_comment|/*&n;     * SCC parameter RAM&n;     */
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* RX BD base address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* TX BD base address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
DECL|member|rcrc
r_int
r_int
id|rcrc
suffix:semicolon
multiline_comment|/* temp receive CRC */
DECL|member|tcrc
r_int
r_int
id|tcrc
suffix:semicolon
multiline_comment|/* temp transmit CRC */
multiline_comment|/*&n;     * ETHERNET specific parameter RAM&n;     */
DECL|member|c_pres
r_int
r_int
id|c_pres
suffix:semicolon
multiline_comment|/* preset CRC */
DECL|member|c_mask
r_int
r_int
id|c_mask
suffix:semicolon
multiline_comment|/* constant mask for CRC */
DECL|member|crcec
r_int
r_int
id|crcec
suffix:semicolon
multiline_comment|/* CRC error counter */
DECL|member|alec
r_int
r_int
id|alec
suffix:semicolon
multiline_comment|/* alighnment error counter */
DECL|member|disfc
r_int
r_int
id|disfc
suffix:semicolon
multiline_comment|/* discard frame counter */
DECL|member|pads
r_int
r_int
id|pads
suffix:semicolon
multiline_comment|/* short frame PAD characters */
DECL|member|ret_lim
r_int
r_int
id|ret_lim
suffix:semicolon
multiline_comment|/* retry limit threshold */
DECL|member|ret_cnt
r_int
r_int
id|ret_cnt
suffix:semicolon
multiline_comment|/* retry limit counter */
DECL|member|mflr
r_int
r_int
id|mflr
suffix:semicolon
multiline_comment|/* maximum frame length reg */
DECL|member|minflr
r_int
r_int
id|minflr
suffix:semicolon
multiline_comment|/* minimum frame length reg */
DECL|member|maxd1
r_int
r_int
id|maxd1
suffix:semicolon
multiline_comment|/* maximum DMA1 length reg */
DECL|member|maxd2
r_int
r_int
id|maxd2
suffix:semicolon
multiline_comment|/* maximum DMA2 length reg */
DECL|member|maxd
r_int
r_int
id|maxd
suffix:semicolon
multiline_comment|/* rx max DMA */
DECL|member|dma_cnt
r_int
r_int
id|dma_cnt
suffix:semicolon
multiline_comment|/* rx dma counter */
DECL|member|max_b
r_int
r_int
id|max_b
suffix:semicolon
multiline_comment|/* max bd byte count */
DECL|member|gaddr1
r_int
r_int
id|gaddr1
suffix:semicolon
multiline_comment|/* group address filter 1 */
DECL|member|gaddr2
r_int
r_int
id|gaddr2
suffix:semicolon
multiline_comment|/* group address filter 2 */
DECL|member|gaddr3
r_int
r_int
id|gaddr3
suffix:semicolon
multiline_comment|/* group address filter 3 */
DECL|member|gaddr4
r_int
r_int
id|gaddr4
suffix:semicolon
multiline_comment|/* group address filter 4 */
DECL|member|tbuf0_data0
r_int
r_int
id|tbuf0_data0
suffix:semicolon
multiline_comment|/* save area 0 - current frm */
DECL|member|tbuf0_data1
r_int
r_int
id|tbuf0_data1
suffix:semicolon
multiline_comment|/* save area 1 - current frm */
DECL|member|tbuf0_rba0
r_int
r_int
id|tbuf0_rba0
suffix:semicolon
DECL|member|tbuf0_crc
r_int
r_int
id|tbuf0_crc
suffix:semicolon
DECL|member|tbuf0_bcnt
r_int
r_int
id|tbuf0_bcnt
suffix:semicolon
r_union
(brace
DECL|member|b
r_int
r_char
id|b
(braket
l_int|6
)braket
suffix:semicolon
r_struct
(brace
DECL|member|high
r_int
r_int
id|high
suffix:semicolon
DECL|member|middl
r_int
r_int
id|middl
suffix:semicolon
DECL|member|low
r_int
r_int
id|low
suffix:semicolon
DECL|member|w
)brace
id|w
suffix:semicolon
DECL|member|paddr
)brace
id|paddr
suffix:semicolon
DECL|member|p_per
r_int
r_int
id|p_per
suffix:semicolon
multiline_comment|/* persistence */
DECL|member|rfbd_ptr
r_int
r_int
id|rfbd_ptr
suffix:semicolon
multiline_comment|/* rx first bd pointer */
DECL|member|tfbd_ptr
r_int
r_int
id|tfbd_ptr
suffix:semicolon
multiline_comment|/* tx first bd pointer */
DECL|member|tlbd_ptr
r_int
r_int
id|tlbd_ptr
suffix:semicolon
multiline_comment|/* tx last bd pointer */
DECL|member|tbuf1_data0
r_int
r_int
id|tbuf1_data0
suffix:semicolon
multiline_comment|/* save area 0 - next frame */
DECL|member|tbuf1_data1
r_int
r_int
id|tbuf1_data1
suffix:semicolon
multiline_comment|/* save area 1 - next frame */
DECL|member|tbuf1_rba0
r_int
r_int
id|tbuf1_rba0
suffix:semicolon
DECL|member|tbuf1_crc
r_int
r_int
id|tbuf1_crc
suffix:semicolon
DECL|member|tbuf1_bcnt
r_int
r_int
id|tbuf1_bcnt
suffix:semicolon
DECL|member|tx_len
r_int
r_int
id|tx_len
suffix:semicolon
multiline_comment|/* tx frame length counter */
DECL|member|iaddr1
r_int
r_int
id|iaddr1
suffix:semicolon
multiline_comment|/* individual address filter 1*/
DECL|member|iaddr2
r_int
r_int
id|iaddr2
suffix:semicolon
multiline_comment|/* individual address filter 2*/
DECL|member|iaddr3
r_int
r_int
id|iaddr3
suffix:semicolon
multiline_comment|/* individual address filter 3*/
DECL|member|iaddr4
r_int
r_int
id|iaddr4
suffix:semicolon
multiline_comment|/* individual address filter 4*/
DECL|member|boff_cnt
r_int
r_int
id|boff_cnt
suffix:semicolon
multiline_comment|/* back-off counter */
DECL|member|taddr_h
r_int
r_int
id|taddr_h
suffix:semicolon
multiline_comment|/* temp address (MSB) */
DECL|member|taddr_m
r_int
r_int
id|taddr_m
suffix:semicolon
multiline_comment|/* temp address */
DECL|member|taddr_l
r_int
r_int
id|taddr_l
suffix:semicolon
multiline_comment|/* temp address (LSB) */
)brace
suffix:semicolon
DECL|struct|transparent_pram
r_struct
id|transparent_pram
(brace
multiline_comment|/*&n;     * SCC parameter RAM&n;     */
DECL|member|rbase
r_int
r_int
id|rbase
suffix:semicolon
multiline_comment|/* RX BD base address */
DECL|member|tbase
r_int
r_int
id|tbase
suffix:semicolon
multiline_comment|/* TX BD base address */
DECL|member|rfcr
r_int
r_char
id|rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|tfcr
r_int
r_char
id|tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|mrblr
r_int
r_int
id|mrblr
suffix:semicolon
multiline_comment|/* Rx buffer length */
DECL|member|rstate
r_int
r_int
id|rstate
suffix:semicolon
multiline_comment|/* Rx internal state */
DECL|member|rptr
r_int
r_int
id|rptr
suffix:semicolon
multiline_comment|/* Rx internal data pointer */
DECL|member|rbptr
r_int
r_int
id|rbptr
suffix:semicolon
multiline_comment|/* rb BD Pointer */
DECL|member|rcount
r_int
r_int
id|rcount
suffix:semicolon
multiline_comment|/* Rx internal byte count */
DECL|member|rtemp
r_int
r_int
id|rtemp
suffix:semicolon
multiline_comment|/* Rx temp */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
multiline_comment|/* Tx internal state */
DECL|member|tptr
r_int
r_int
id|tptr
suffix:semicolon
multiline_comment|/* Tx internal data pointer */
DECL|member|tbptr
r_int
r_int
id|tbptr
suffix:semicolon
multiline_comment|/* Tx BD pointer */
DECL|member|tcount
r_int
r_int
id|tcount
suffix:semicolon
multiline_comment|/* Tx byte count */
DECL|member|ttemp
r_int
r_int
id|ttemp
suffix:semicolon
multiline_comment|/* Tx temp */
DECL|member|rcrc
r_int
r_int
id|rcrc
suffix:semicolon
multiline_comment|/* temp receive CRC */
DECL|member|tcrc
r_int
r_int
id|tcrc
suffix:semicolon
multiline_comment|/* temp transmit CRC */
multiline_comment|/*&n;     * TRANSPARENT specific parameter RAM&n;     */
DECL|member|crc_p
r_int
r_int
id|crc_p
suffix:semicolon
multiline_comment|/* CRC Preset */
DECL|member|crc_c
r_int
r_int
id|crc_c
suffix:semicolon
multiline_comment|/* CRC constant */
)brace
suffix:semicolon
DECL|struct|timer_pram
r_struct
id|timer_pram
(brace
multiline_comment|/*&n;     * RISC timers parameter RAM&n;     */
DECL|member|tm_base
r_int
r_int
id|tm_base
suffix:semicolon
multiline_comment|/* RISC timer table base adr */
DECL|member|tm_ptr
r_int
r_int
id|tm_ptr
suffix:semicolon
multiline_comment|/* RISC timer table pointer */
DECL|member|r_tmr
r_int
r_int
id|r_tmr
suffix:semicolon
multiline_comment|/* RISC timer mode register */
DECL|member|r_tmv
r_int
r_int
id|r_tmv
suffix:semicolon
multiline_comment|/* RISC timer valid register */
DECL|member|tm_cmd
r_int
r_int
id|tm_cmd
suffix:semicolon
multiline_comment|/* RISC timer cmd register */
DECL|member|tm_cnt
r_int
r_int
id|tm_cnt
suffix:semicolon
multiline_comment|/* RISC timer internal cnt */
)brace
suffix:semicolon
macro_line|#endif
eof
