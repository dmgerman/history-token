multiline_comment|/*&n; * atari_SCC.h: Definitions for the Am8530 Serial Communications Controller&n; *&n; * Copyright 1994 Roman Hodek &lt;Roman.Hodek@informatik.uni-erlangen.de&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#ifndef _SCC_H
DECL|macro|_SCC_H
mdefine_line|#define _SCC_H
macro_line|#include &lt;linux/delay.h&gt;
multiline_comment|/* Special configuration ioctls for the Atari SCC5380 Serial&n; * Communications Controller&n; */
multiline_comment|/* ioctl command codes */
DECL|macro|TIOCGATSCC
mdefine_line|#define TIOCGATSCC&t;0x54c0&t;/* get SCC configuration */
DECL|macro|TIOCSATSCC
mdefine_line|#define TIOCSATSCC&t;0x54c1&t;/* set SCC configuration */
DECL|macro|TIOCDATSCC
mdefine_line|#define TIOCDATSCC&t;0x54c2&t;/* reset configuration to defaults */
multiline_comment|/* Clock sources */
DECL|macro|CLK_RTxC
mdefine_line|#define CLK_RTxC&t;0
DECL|macro|CLK_TRxC
mdefine_line|#define CLK_TRxC&t;1
DECL|macro|CLK_PCLK
mdefine_line|#define CLK_PCLK&t;2
multiline_comment|/* baud_bases for the common clocks in the Atari. These are the real&n; * frequencies divided by 16.&n; */
DECL|macro|SCC_BAUD_BASE_TIMC
mdefine_line|#define SCC_BAUD_BASE_TIMC&t;19200&t;/* 0.3072 MHz from TT-MFP, Timer C */
DECL|macro|SCC_BAUD_BASE_BCLK
mdefine_line|#define SCC_BAUD_BASE_BCLK&t;153600&t;/* 2.4576 MHz */
DECL|macro|SCC_BAUD_BASE_PCLK4
mdefine_line|#define SCC_BAUD_BASE_PCLK4&t;229500&t;/* 3.6720 MHz */
DECL|macro|SCC_BAUD_BASE_PCLK
mdefine_line|#define SCC_BAUD_BASE_PCLK&t;503374&t;/* 8.0539763 MHz */
DECL|macro|SCC_BAUD_BASE_NONE
mdefine_line|#define SCC_BAUD_BASE_NONE&t;0&t;/* for not connected or unused&n;&t;&t;&t;&t;&t; * clock sources */
multiline_comment|/* The SCC clock configuration structure */
DECL|struct|scc_clock_config
r_struct
id|scc_clock_config
(brace
DECL|member|RTxC_base
r_int
id|RTxC_base
suffix:semicolon
multiline_comment|/* base_baud of RTxC */
DECL|member|TRxC_base
r_int
id|TRxC_base
suffix:semicolon
multiline_comment|/* base_baud of TRxC */
DECL|member|PCLK_base
r_int
id|PCLK_base
suffix:semicolon
multiline_comment|/* base_baud of PCLK, both channels! */
r_struct
(brace
DECL|member|clksrc
r_int
id|clksrc
suffix:semicolon
multiline_comment|/* CLK_RTxC, CLK_TRxC or CLK_PCLK */
DECL|member|divisor
r_int
id|divisor
suffix:semicolon
multiline_comment|/* divisor for base baud, valid values:&n;&t;&t;&t;&t;&t; * see below */
DECL|member|baud_table
)brace
id|baud_table
(braket
l_int|17
)braket
suffix:semicolon
multiline_comment|/* For 50, 75, 110, 135, 150, 200, 300,&n;&t;&t;&t;&t;&t; * 600, 1200, 1800, 2400, 4800, 9600,&n;&t;&t;&t;&t;&t; * 19200, 38400, 57600 and 115200 bps.&n;&t;&t;&t;&t;&t; * The last two could be replaced by&n;&t;&t;&t;&t;&t; * other rates &gt; 38400 if they&squot;re not&n;&t;&t;&t;&t;&t; * possible.&n;&t;&t;&t;&t;&t; */
)brace
suffix:semicolon
multiline_comment|/* The following divisors are valid:&n; *&n; *   - CLK_RTxC: 1 or even (1, 2 and 4 are the direct modes, &gt; 4 use&n; *               the BRG)&n; *&n; *   - CLK_TRxC: 1, 2 or 4 (no BRG, only direct modes possible)&n; *&n; *   - CLK_PCLK: &gt;= 4 and even (no direct modes, only BRG)&n; *&n; */
DECL|struct|scc_port
r_struct
id|scc_port
(brace
DECL|member|gs
r_struct
id|gs_port
id|gs
suffix:semicolon
DECL|member|ctrlp
r_volatile
r_int
r_char
op_star
id|ctrlp
suffix:semicolon
DECL|member|datap
r_volatile
r_int
r_char
op_star
id|datap
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff character */
DECL|member|c_dcd
r_int
id|c_dcd
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|port_a
r_struct
id|scc_port
op_star
id|port_a
suffix:semicolon
multiline_comment|/* Reference to port A and B */
DECL|member|port_b
r_struct
id|scc_port
op_star
id|port_b
suffix:semicolon
multiline_comment|/*   structs for reg access  */
)brace
suffix:semicolon
DECL|macro|SCC_MAGIC
mdefine_line|#define SCC_MAGIC&t;0x52696368
multiline_comment|/***********************************************************************/
multiline_comment|/*                                                                     */
multiline_comment|/*                             Register Names                          */
multiline_comment|/*                                                                     */
multiline_comment|/***********************************************************************/
multiline_comment|/* The SCC documentation gives no explicit names to the registers,&n; * they&squot;re just called WR0..15 and RR0..15. To make the source code&n; * better readable and make the transparent write reg read access (see&n; * below) possible, I christen them here with self-invented names.&n; * Note that (real) read registers are assigned numbers 16..31. WR7&squot;&n; * has number 33.&n; */
DECL|macro|COMMAND_REG
mdefine_line|#define&t;COMMAND_REG&t;&t;0&t;/* wo */
DECL|macro|INT_AND_DMA_REG
mdefine_line|#define&t;INT_AND_DMA_REG&t;&t;1&t;/* wo */
DECL|macro|INT_VECTOR_REG
mdefine_line|#define&t;INT_VECTOR_REG&t;&t;2&t;/* rw, common to both channels */
DECL|macro|RX_CTRL_REG
mdefine_line|#define&t;RX_CTRL_REG&t;&t;3&t;/* rw */
DECL|macro|AUX1_CTRL_REG
mdefine_line|#define&t;AUX1_CTRL_REG&t;&t;4&t;/* rw */
DECL|macro|TX_CTRL_REG
mdefine_line|#define&t;TX_CTRL_REG&t;&t;5&t;/* rw */
DECL|macro|SYNC_ADR_REG
mdefine_line|#define&t;SYNC_ADR_REG&t;&t;6&t;/* wo */
DECL|macro|SYNC_CHAR_REG
mdefine_line|#define&t;SYNC_CHAR_REG&t;&t;7&t;/* wo */
DECL|macro|SDLC_OPTION_REG
mdefine_line|#define&t;SDLC_OPTION_REG&t;&t;33&t;/* wo */
DECL|macro|TX_DATA_REG
mdefine_line|#define&t;TX_DATA_REG&t;&t;8&t;/* wo */
DECL|macro|MASTER_INT_CTRL
mdefine_line|#define&t;MASTER_INT_CTRL&t;&t;9&t;/* wo, common to both channels */
DECL|macro|AUX2_CTRL_REG
mdefine_line|#define&t;AUX2_CTRL_REG&t;&t;10&t;/* rw */
DECL|macro|CLK_CTRL_REG
mdefine_line|#define&t;CLK_CTRL_REG&t;&t;11&t;/* wo */
DECL|macro|TIMER_LOW_REG
mdefine_line|#define&t;TIMER_LOW_REG&t;&t;12&t;/* rw */
DECL|macro|TIMER_HIGH_REG
mdefine_line|#define&t;TIMER_HIGH_REG&t;&t;13&t;/* rw */
DECL|macro|DPLL_CTRL_REG
mdefine_line|#define&t;DPLL_CTRL_REG&t;&t;14&t;/* wo */
DECL|macro|INT_CTRL_REG
mdefine_line|#define&t;INT_CTRL_REG&t;&t;15&t;/* rw */
DECL|macro|STATUS_REG
mdefine_line|#define&t;STATUS_REG&t;&t;16&t;/* ro */
DECL|macro|SPCOND_STATUS_REG
mdefine_line|#define&t;SPCOND_STATUS_REG&t;17&t;/* wo */
multiline_comment|/* RR2 is WR2 for Channel A, Channel B gives vector + current status: */
DECL|macro|CURR_VECTOR_REG
mdefine_line|#define&t;CURR_VECTOR_REG&t;&t;18&t;/* Ch. B only, Ch. A for rw */
DECL|macro|INT_PENDING_REG
mdefine_line|#define&t;INT_PENDING_REG&t;&t;19&t;/* Channel A only! */
multiline_comment|/* RR4 is WR4, if b6(MR7&squot;) == 1 */
multiline_comment|/* RR5 is WR5, if b6(MR7&squot;) == 1 */
DECL|macro|FS_FIFO_LOW_REG
mdefine_line|#define&t;FS_FIFO_LOW_REG&t;&t;22&t;/* ro */
DECL|macro|FS_FIFO_HIGH_REG
mdefine_line|#define&t;FS_FIFO_HIGH_REG&t;23&t;/* ro */
DECL|macro|RX_DATA_REG
mdefine_line|#define&t;RX_DATA_REG&t;&t;24&t;/* ro */
multiline_comment|/* RR9 is WR3, if b6(MR7&squot;) == 1 */
DECL|macro|DPLL_STATUS_REG
mdefine_line|#define&t;DPLL_STATUS_REG&t;&t;26&t;/* ro */
multiline_comment|/* RR11 is WR10, if b6(MR7&squot;) == 1 */
multiline_comment|/* RR12 is WR12 */
multiline_comment|/* RR13 is WR13 */
multiline_comment|/* RR14 not present */
multiline_comment|/* RR15 is WR15 */
multiline_comment|/***********************************************************************/
multiline_comment|/*                                                                     */
multiline_comment|/*                             Register Values                         */
multiline_comment|/*                                                                     */
multiline_comment|/***********************************************************************/
multiline_comment|/* WR0: COMMAND_REG &quot;CR&quot; */
DECL|macro|CR_RX_CRC_RESET
mdefine_line|#define&t;CR_RX_CRC_RESET&t;&t;0x40
DECL|macro|CR_TX_CRC_RESET
mdefine_line|#define&t;CR_TX_CRC_RESET&t;&t;0x80
DECL|macro|CR_TX_UNDERRUN_RESET
mdefine_line|#define&t;CR_TX_UNDERRUN_RESET&t;0xc0
DECL|macro|CR_EXTSTAT_RESET
mdefine_line|#define&t;CR_EXTSTAT_RESET&t;0x10
DECL|macro|CR_SEND_ABORT
mdefine_line|#define&t;CR_SEND_ABORT&t;&t;0x18
DECL|macro|CR_ENAB_INT_NEXT_RX
mdefine_line|#define&t;CR_ENAB_INT_NEXT_RX&t;0x20
DECL|macro|CR_TX_PENDING_RESET
mdefine_line|#define&t;CR_TX_PENDING_RESET&t;0x28
DECL|macro|CR_ERROR_RESET
mdefine_line|#define&t;CR_ERROR_RESET&t;&t;0x30
DECL|macro|CR_HIGHEST_IUS_RESET
mdefine_line|#define&t;CR_HIGHEST_IUS_RESET&t;0x38
multiline_comment|/* WR1: INT_AND_DMA_REG &quot;IDR&quot; */
DECL|macro|IDR_EXTSTAT_INT_ENAB
mdefine_line|#define&t;IDR_EXTSTAT_INT_ENAB&t;0x01
DECL|macro|IDR_TX_INT_ENAB
mdefine_line|#define&t;IDR_TX_INT_ENAB&t;&t;0x02
DECL|macro|IDR_PARERR_AS_SPCOND
mdefine_line|#define&t;IDR_PARERR_AS_SPCOND&t;0x04
DECL|macro|IDR_RX_INT_DISAB
mdefine_line|#define&t;IDR_RX_INT_DISAB&t;0x00
DECL|macro|IDR_RX_INT_FIRST
mdefine_line|#define&t;IDR_RX_INT_FIRST&t;0x08
DECL|macro|IDR_RX_INT_ALL
mdefine_line|#define&t;IDR_RX_INT_ALL&t;&t;0x10
DECL|macro|IDR_RX_INT_SPCOND
mdefine_line|#define&t;IDR_RX_INT_SPCOND&t;0x18
DECL|macro|IDR_RX_INT_MASK
mdefine_line|#define&t;IDR_RX_INT_MASK&t;&t;0x18
DECL|macro|IDR_WAITREQ_RX
mdefine_line|#define&t;IDR_WAITREQ_RX&t;&t;0x20
DECL|macro|IDR_WAITREQ_IS_REQ
mdefine_line|#define&t;IDR_WAITREQ_IS_REQ&t;0x40
DECL|macro|IDR_WAITREQ_ENAB
mdefine_line|#define&t;IDR_WAITREQ_ENAB&t;0x80
multiline_comment|/* WR3: RX_CTRL_REG &quot;RCR&quot; */
DECL|macro|RCR_RX_ENAB
mdefine_line|#define&t;RCR_RX_ENAB&t;&t;0x01
DECL|macro|RCR_DISCARD_SYNC_CHARS
mdefine_line|#define&t;RCR_DISCARD_SYNC_CHARS&t;0x02
DECL|macro|RCR_ADDR_SEARCH
mdefine_line|#define&t;RCR_ADDR_SEARCH&t;&t;0x04
DECL|macro|RCR_CRC_ENAB
mdefine_line|#define&t;RCR_CRC_ENAB&t;&t;0x08
DECL|macro|RCR_SEARCH_MODE
mdefine_line|#define&t;RCR_SEARCH_MODE&t;&t;0x10
DECL|macro|RCR_AUTO_ENAB_MODE
mdefine_line|#define&t;RCR_AUTO_ENAB_MODE&t;0x20
DECL|macro|RCR_CHSIZE_MASK
mdefine_line|#define&t;RCR_CHSIZE_MASK&t;&t;0xc0
DECL|macro|RCR_CHSIZE_5
mdefine_line|#define&t;RCR_CHSIZE_5&t;&t;0x00
DECL|macro|RCR_CHSIZE_6
mdefine_line|#define&t;RCR_CHSIZE_6&t;&t;0x40
DECL|macro|RCR_CHSIZE_7
mdefine_line|#define&t;RCR_CHSIZE_7&t;&t;0x80
DECL|macro|RCR_CHSIZE_8
mdefine_line|#define&t;RCR_CHSIZE_8&t;&t;0xc0
multiline_comment|/* WR4: AUX1_CTRL_REG &quot;A1CR&quot; */
DECL|macro|A1CR_PARITY_MASK
mdefine_line|#define&t;A1CR_PARITY_MASK&t;0x03
DECL|macro|A1CR_PARITY_NONE
mdefine_line|#define&t;A1CR_PARITY_NONE&t;0x00
DECL|macro|A1CR_PARITY_ODD
mdefine_line|#define&t;A1CR_PARITY_ODD&t;&t;0x01
DECL|macro|A1CR_PARITY_EVEN
mdefine_line|#define&t;A1CR_PARITY_EVEN&t;0x03
DECL|macro|A1CR_MODE_MASK
mdefine_line|#define&t;A1CR_MODE_MASK&t;&t;0x0c
DECL|macro|A1CR_MODE_SYNCR
mdefine_line|#define&t;A1CR_MODE_SYNCR&t;&t;0x00
DECL|macro|A1CR_MODE_ASYNC_1
mdefine_line|#define&t;A1CR_MODE_ASYNC_1&t;0x04
DECL|macro|A1CR_MODE_ASYNC_15
mdefine_line|#define&t;A1CR_MODE_ASYNC_15&t;0x08
DECL|macro|A1CR_MODE_ASYNC_2
mdefine_line|#define&t;A1CR_MODE_ASYNC_2&t;0x0c
DECL|macro|A1CR_SYNCR_MODE_MASK
mdefine_line|#define&t;A1CR_SYNCR_MODE_MASK&t;0x30
DECL|macro|A1CR_SYNCR_MONOSYNC
mdefine_line|#define&t;A1CR_SYNCR_MONOSYNC&t;0x00
DECL|macro|A1CR_SYNCR_BISYNC
mdefine_line|#define&t;A1CR_SYNCR_BISYNC&t;0x10
DECL|macro|A1CR_SYNCR_SDLC
mdefine_line|#define&t;A1CR_SYNCR_SDLC&t;&t;0x20
DECL|macro|A1CR_SYNCR_EXTCSYNC
mdefine_line|#define&t;A1CR_SYNCR_EXTCSYNC&t;0x30
DECL|macro|A1CR_CLKMODE_MASK
mdefine_line|#define&t;A1CR_CLKMODE_MASK&t;0xc0
DECL|macro|A1CR_CLKMODE_x1
mdefine_line|#define&t;A1CR_CLKMODE_x1&t;&t;0x00
DECL|macro|A1CR_CLKMODE_x16
mdefine_line|#define&t;A1CR_CLKMODE_x16&t;0x40
DECL|macro|A1CR_CLKMODE_x32
mdefine_line|#define&t;A1CR_CLKMODE_x32&t;0x80
DECL|macro|A1CR_CLKMODE_x64
mdefine_line|#define&t;A1CR_CLKMODE_x64&t;0xc0
multiline_comment|/* WR5: TX_CTRL_REG &quot;TCR&quot; */
DECL|macro|TCR_TX_CRC_ENAB
mdefine_line|#define&t;TCR_TX_CRC_ENAB&t;&t;0x01
DECL|macro|TCR_RTS
mdefine_line|#define&t;TCR_RTS&t;&t;&t;0x02
DECL|macro|TCR_USE_CRC_CCITT
mdefine_line|#define&t;TCR_USE_CRC_CCITT&t;0x00
DECL|macro|TCR_USE_CRC_16
mdefine_line|#define&t;TCR_USE_CRC_16&t;&t;0x04
DECL|macro|TCR_TX_ENAB
mdefine_line|#define&t;TCR_TX_ENAB&t;&t;0x08
DECL|macro|TCR_SEND_BREAK
mdefine_line|#define&t;TCR_SEND_BREAK&t;&t;0x10
DECL|macro|TCR_CHSIZE_MASK
mdefine_line|#define&t;TCR_CHSIZE_MASK&t;&t;0x60
DECL|macro|TCR_CHSIZE_5
mdefine_line|#define&t;TCR_CHSIZE_5&t;&t;0x00
DECL|macro|TCR_CHSIZE_6
mdefine_line|#define&t;TCR_CHSIZE_6&t;&t;0x20
DECL|macro|TCR_CHSIZE_7
mdefine_line|#define&t;TCR_CHSIZE_7&t;&t;0x40
DECL|macro|TCR_CHSIZE_8
mdefine_line|#define&t;TCR_CHSIZE_8&t;&t;0x60
DECL|macro|TCR_DTR
mdefine_line|#define&t;TCR_DTR&t;&t;&t;0x80
multiline_comment|/* WR7&squot;: SLDC_OPTION_REG &quot;SOR&quot; */
DECL|macro|SOR_AUTO_TX_ENAB
mdefine_line|#define&t;SOR_AUTO_TX_ENAB&t;0x01
DECL|macro|SOR_AUTO_EOM_RESET
mdefine_line|#define&t;SOR_AUTO_EOM_RESET&t;0x02
DECL|macro|SOR_AUTO_RTS_MODE
mdefine_line|#define&t;SOR_AUTO_RTS_MODE&t;0x04
DECL|macro|SOR_NRZI_DISAB_HIGH
mdefine_line|#define&t;SOR_NRZI_DISAB_HIGH&t;0x08
DECL|macro|SOR_ALT_DTRREQ_TIMING
mdefine_line|#define&t;SOR_ALT_DTRREQ_TIMING&t;0x10
DECL|macro|SOR_READ_CRC_CHARS
mdefine_line|#define&t;SOR_READ_CRC_CHARS&t;0x20
DECL|macro|SOR_EXTENDED_REG_ACCESS
mdefine_line|#define&t;SOR_EXTENDED_REG_ACCESS&t;0x40
multiline_comment|/* WR9: MASTER_INT_CTRL &quot;MIC&quot; */
DECL|macro|MIC_VEC_INCL_STAT
mdefine_line|#define&t;MIC_VEC_INCL_STAT&t;0x01
DECL|macro|MIC_NO_VECTOR
mdefine_line|#define&t;MIC_NO_VECTOR&t;&t;0x02
DECL|macro|MIC_DISAB_LOWER_CHAIN
mdefine_line|#define&t;MIC_DISAB_LOWER_CHAIN&t;0x04
DECL|macro|MIC_MASTER_INT_ENAB
mdefine_line|#define&t;MIC_MASTER_INT_ENAB&t;0x08
DECL|macro|MIC_STATUS_HIGH
mdefine_line|#define&t;MIC_STATUS_HIGH&t;&t;0x10
DECL|macro|MIC_IGN_INTACK
mdefine_line|#define&t;MIC_IGN_INTACK&t;&t;0x20
DECL|macro|MIC_NO_RESET
mdefine_line|#define&t;MIC_NO_RESET&t;&t;0x00
DECL|macro|MIC_CH_A_RESET
mdefine_line|#define&t;MIC_CH_A_RESET&t;&t;0x40
DECL|macro|MIC_CH_B_RESET
mdefine_line|#define&t;MIC_CH_B_RESET&t;&t;0x80
DECL|macro|MIC_HARD_RESET
mdefine_line|#define&t;MIC_HARD_RESET&t;&t;0xc0
multiline_comment|/* WR10: AUX2_CTRL_REG &quot;A2CR&quot; */
DECL|macro|A2CR_SYNC_6
mdefine_line|#define&t;A2CR_SYNC_6&t;&t;0x01
DECL|macro|A2CR_LOOP_MODE
mdefine_line|#define&t;A2CR_LOOP_MODE&t;&t;0x02
DECL|macro|A2CR_ABORT_ON_UNDERRUN
mdefine_line|#define&t;A2CR_ABORT_ON_UNDERRUN&t;0x04
DECL|macro|A2CR_MARK_IDLE
mdefine_line|#define&t;A2CR_MARK_IDLE&t;&t;0x08
DECL|macro|A2CR_GO_ACTIVE_ON_POLL
mdefine_line|#define&t;A2CR_GO_ACTIVE_ON_POLL&t;0x10
DECL|macro|A2CR_CODING_MASK
mdefine_line|#define&t;A2CR_CODING_MASK&t;0x60
DECL|macro|A2CR_CODING_NRZ
mdefine_line|#define&t;A2CR_CODING_NRZ&t;&t;0x00
DECL|macro|A2CR_CODING_NRZI
mdefine_line|#define&t;A2CR_CODING_NRZI&t;0x20
DECL|macro|A2CR_CODING_FM1
mdefine_line|#define&t;A2CR_CODING_FM1&t;&t;0x40
DECL|macro|A2CR_CODING_FM0
mdefine_line|#define&t;A2CR_CODING_FM0&t;&t;0x60
DECL|macro|A2CR_PRESET_CRC_1
mdefine_line|#define&t;A2CR_PRESET_CRC_1&t;0x80
multiline_comment|/* WR11: CLK_CTRL_REG &quot;CCR&quot; */
DECL|macro|CCR_TRxCOUT_MASK
mdefine_line|#define&t;CCR_TRxCOUT_MASK&t;0x03
DECL|macro|CCR_TRxCOUT_XTAL
mdefine_line|#define&t;CCR_TRxCOUT_XTAL&t;0x00
DECL|macro|CCR_TRxCOUT_TXCLK
mdefine_line|#define&t;CCR_TRxCOUT_TXCLK&t;0x01
DECL|macro|CCR_TRxCOUT_BRG
mdefine_line|#define&t;CCR_TRxCOUT_BRG&t;&t;0x02
DECL|macro|CCR_TRxCOUT_DPLL
mdefine_line|#define&t;CCR_TRxCOUT_DPLL&t;0x03
DECL|macro|CCR_TRxC_OUTPUT
mdefine_line|#define&t;CCR_TRxC_OUTPUT&t;&t;0x04
DECL|macro|CCR_TXCLK_MASK
mdefine_line|#define&t;CCR_TXCLK_MASK&t;&t;0x18
DECL|macro|CCR_TXCLK_RTxC
mdefine_line|#define&t;CCR_TXCLK_RTxC&t;&t;0x00
DECL|macro|CCR_TXCLK_TRxC
mdefine_line|#define&t;CCR_TXCLK_TRxC&t;&t;0x08
DECL|macro|CCR_TXCLK_BRG
mdefine_line|#define&t;CCR_TXCLK_BRG&t;&t;0x10
DECL|macro|CCR_TXCLK_DPLL
mdefine_line|#define&t;CCR_TXCLK_DPLL&t;&t;0x18
DECL|macro|CCR_RXCLK_MASK
mdefine_line|#define&t;CCR_RXCLK_MASK&t;&t;0x60
DECL|macro|CCR_RXCLK_RTxC
mdefine_line|#define&t;CCR_RXCLK_RTxC&t;&t;0x00
DECL|macro|CCR_RXCLK_TRxC
mdefine_line|#define&t;CCR_RXCLK_TRxC&t;&t;0x20
DECL|macro|CCR_RXCLK_BRG
mdefine_line|#define&t;CCR_RXCLK_BRG&t;&t;0x40
DECL|macro|CCR_RXCLK_DPLL
mdefine_line|#define&t;CCR_RXCLK_DPLL&t;&t;0x60
DECL|macro|CCR_RTxC_XTAL
mdefine_line|#define&t;CCR_RTxC_XTAL&t;&t;0x80
multiline_comment|/* WR14: DPLL_CTRL_REG &quot;DCR&quot; */
DECL|macro|DCR_BRG_ENAB
mdefine_line|#define&t;DCR_BRG_ENAB&t;&t;0x01
DECL|macro|DCR_BRG_USE_PCLK
mdefine_line|#define&t;DCR_BRG_USE_PCLK&t;0x02
DECL|macro|DCR_DTRREQ_IS_REQ
mdefine_line|#define&t;DCR_DTRREQ_IS_REQ&t;0x04
DECL|macro|DCR_AUTO_ECHO
mdefine_line|#define&t;DCR_AUTO_ECHO&t;&t;0x08
DECL|macro|DCR_LOCAL_LOOPBACK
mdefine_line|#define&t;DCR_LOCAL_LOOPBACK&t;0x10
DECL|macro|DCR_DPLL_EDGE_SEARCH
mdefine_line|#define&t;DCR_DPLL_EDGE_SEARCH&t;0x20
DECL|macro|DCR_DPLL_ERR_RESET
mdefine_line|#define&t;DCR_DPLL_ERR_RESET&t;0x40
DECL|macro|DCR_DPLL_DISAB
mdefine_line|#define&t;DCR_DPLL_DISAB&t;&t;0x60
DECL|macro|DCR_DPLL_CLK_BRG
mdefine_line|#define&t;DCR_DPLL_CLK_BRG&t;0x80
DECL|macro|DCR_DPLL_CLK_RTxC
mdefine_line|#define&t;DCR_DPLL_CLK_RTxC&t;0xa0
DECL|macro|DCR_DPLL_FM
mdefine_line|#define&t;DCR_DPLL_FM&t;&t;0xc0
DECL|macro|DCR_DPLL_NRZI
mdefine_line|#define&t;DCR_DPLL_NRZI&t;&t;0xe0
multiline_comment|/* WR15: INT_CTRL_REG &quot;ICR&quot; */
DECL|macro|ICR_OPTIONREG_SELECT
mdefine_line|#define&t;ICR_OPTIONREG_SELECT&t;0x01
DECL|macro|ICR_ENAB_BRG_ZERO_INT
mdefine_line|#define&t;ICR_ENAB_BRG_ZERO_INT&t;0x02
DECL|macro|ICR_USE_FS_FIFO
mdefine_line|#define&t;ICR_USE_FS_FIFO&t;&t;0x04
DECL|macro|ICR_ENAB_DCD_INT
mdefine_line|#define&t;ICR_ENAB_DCD_INT&t;0x08
DECL|macro|ICR_ENAB_SYNC_INT
mdefine_line|#define&t;ICR_ENAB_SYNC_INT&t;0x10
DECL|macro|ICR_ENAB_CTS_INT
mdefine_line|#define&t;ICR_ENAB_CTS_INT&t;0x20
DECL|macro|ICR_ENAB_UNDERRUN_INT
mdefine_line|#define&t;ICR_ENAB_UNDERRUN_INT&t;0x40
DECL|macro|ICR_ENAB_BREAK_INT
mdefine_line|#define&t;ICR_ENAB_BREAK_INT&t;0x80
multiline_comment|/* RR0: STATUS_REG &quot;SR&quot; */
DECL|macro|SR_CHAR_AVAIL
mdefine_line|#define&t;SR_CHAR_AVAIL&t;&t;0x01
DECL|macro|SR_BRG_ZERO
mdefine_line|#define&t;SR_BRG_ZERO&t;&t;0x02
DECL|macro|SR_TX_BUF_EMPTY
mdefine_line|#define&t;SR_TX_BUF_EMPTY&t;&t;0x04
DECL|macro|SR_DCD
mdefine_line|#define&t;SR_DCD&t;&t;&t;0x08
DECL|macro|SR_SYNC_ABORT
mdefine_line|#define&t;SR_SYNC_ABORT&t;&t;0x10
DECL|macro|SR_CTS
mdefine_line|#define&t;SR_CTS&t;&t;&t;0x20
DECL|macro|SR_TX_UNDERRUN
mdefine_line|#define&t;SR_TX_UNDERRUN&t;&t;0x40
DECL|macro|SR_BREAK
mdefine_line|#define&t;SR_BREAK&t;&t;0x80
multiline_comment|/* RR1: SPCOND_STATUS_REG &quot;SCSR&quot; */
DECL|macro|SCSR_ALL_SENT
mdefine_line|#define&t;SCSR_ALL_SENT&t;&t;0x01
DECL|macro|SCSR_RESIDUAL_MASK
mdefine_line|#define&t;SCSR_RESIDUAL_MASK&t;0x0e
DECL|macro|SCSR_PARITY_ERR
mdefine_line|#define&t;SCSR_PARITY_ERR&t;&t;0x10
DECL|macro|SCSR_RX_OVERRUN
mdefine_line|#define&t;SCSR_RX_OVERRUN&t;&t;0x20
DECL|macro|SCSR_CRC_FRAME_ERR
mdefine_line|#define&t;SCSR_CRC_FRAME_ERR&t;0x40
DECL|macro|SCSR_END_OF_FRAME
mdefine_line|#define&t;SCSR_END_OF_FRAME&t;0x80
multiline_comment|/* RR3: INT_PENDING_REG &quot;IPR&quot; */
DECL|macro|IPR_B_EXTSTAT
mdefine_line|#define&t;IPR_B_EXTSTAT&t;&t;0x01
DECL|macro|IPR_B_TX
mdefine_line|#define&t;IPR_B_TX&t;&t;0x02
DECL|macro|IPR_B_RX
mdefine_line|#define&t;IPR_B_RX&t;&t;0x04
DECL|macro|IPR_A_EXTSTAT
mdefine_line|#define&t;IPR_A_EXTSTAT&t;&t;0x08
DECL|macro|IPR_A_TX
mdefine_line|#define&t;IPR_A_TX&t;&t;0x10
DECL|macro|IPR_A_RX
mdefine_line|#define&t;IPR_A_RX&t;&t;0x20
multiline_comment|/* RR7: FS_FIFO_HIGH_REG &quot;FFHR&quot; */
DECL|macro|FFHR_CNT_MASK
mdefine_line|#define&t;FFHR_CNT_MASK&t;&t;0x3f
DECL|macro|FFHR_IS_FROM_FIFO
mdefine_line|#define&t;FFHR_IS_FROM_FIFO&t;0x40
DECL|macro|FFHR_FIFO_OVERRUN
mdefine_line|#define&t;FFHR_FIFO_OVERRUN&t;0x80
multiline_comment|/* RR10: DPLL_STATUS_REG &quot;DSR&quot; */
DECL|macro|DSR_ON_LOOP
mdefine_line|#define&t;DSR_ON_LOOP&t;&t;0x02
DECL|macro|DSR_ON_LOOP_SENDING
mdefine_line|#define&t;DSR_ON_LOOP_SENDING&t;0x10
DECL|macro|DSR_TWO_CLK_MISSING
mdefine_line|#define&t;DSR_TWO_CLK_MISSING&t;0x40
DECL|macro|DSR_ONE_CLK_MISSING
mdefine_line|#define&t;DSR_ONE_CLK_MISSING&t;0x80
multiline_comment|/***********************************************************************/
multiline_comment|/*                                                                     */
multiline_comment|/*                             Register Access                         */
multiline_comment|/*                                                                     */
multiline_comment|/***********************************************************************/
multiline_comment|/* The SCC needs 3.5 PCLK cycles recovery time between to register&n; * accesses. PCLK runs with 8 MHz on an Atari, so this delay is 3.5 *&n; * 125 ns = 437.5 ns. This is too short for udelay().&n; * 10/16/95: A tstb mfp.par_dt_reg takes 600ns (sure?) and thus should be&n; * quite right&n; */
DECL|macro|scc_reg_delay
mdefine_line|#define scc_reg_delay() &bslash;&n;    do {&t;&t;&t;&bslash;&n;&t;if (MACH_IS_MVME16x || MACH_IS_BVME6000 || MACH_IS_MVME147)&t;&bslash;&n;&t;&t;__asm__ __volatile__ ( &quot; nop; nop&quot;);&t;&t;&t;&bslash;&n;&t;else if (MACH_IS_ATARI)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ ( &quot;tstb %0&quot; : : &quot;g&quot; (*_scc_del) : &quot;cc&quot; );&bslash;&n;    } while (0)
r_extern
r_int
r_char
id|scc_shadow
(braket
l_int|2
)braket
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* The following functions should relax the somehow complicated&n; * register access of the SCC. _SCCwrite() stores all written values&n; * (except for WR0 and WR8) in shadow registers for later recall. This&n; * removes the burden of remembering written values as needed. The&n; * extra work of storing the value doesn&squot;t count, since a delay is&n; * needed after a SCC access anyway. Additionally, _SCCwrite() manages&n; * writes to WR0 and WR8 differently, because these can be accessed&n; * directly with less overhead. Another special case are WR7 and WR7&squot;.&n; * _SCCwrite automatically checks what of this registers is selected&n; * and changes b0 of WR15 if needed.&n; * &n; * _SCCread() for standard read registers is straightforward, except&n; * for RR2 (split into two &quot;virtual&quot; registers: one for the value&n; * written to WR2 (from the shadow) and one for the vector including&n; * status from RR2, Ch. B) and RR3. The latter must be read from&n; * Channel A, because it reads as all zeros on Ch. B. RR0 and RR8 can&n; * be accessed directly as before.&n; * &n; * The two inline function contain complicated switch statements. But&n; * I rely on regno and final_delay being constants, so gcc can reduce&n; * the whole stuff to just some assembler statements.&n; * &n; * _SCCwrite and _SCCread aren&squot;t intended to be used directly under&n; * normal circumstances. The macros SCCread[_ND] and SCCwrite[_ND] are&n; * for that purpose. They assume that a local variable &squot;port&squot; is&n; * declared and pointing to the port&squot;s scc_struct entry. The&n; * variants with &quot;_NB&quot; appended should be used if no other SCC&n; * accesses follow immediatly (within 0.5 usecs). They just skip the&n; * final delay nops.&n; * &n; * Please note that accesses to SCC registers should only take place&n; * when interrupts are turned off (at least if SCC interrupts are&n; * enabled). Otherwise, an interrupt could interfere with the&n; * two-stage accessing process.&n; *&n; */
DECL|function|_SCCwrite
r_static
id|__inline__
r_void
id|_SCCwrite
c_func
(paren
r_struct
id|scc_port
op_star
id|port
comma
r_int
r_char
op_star
id|shadow
comma
r_volatile
r_int
r_char
op_star
id|_scc_del
comma
r_int
id|regno
comma
r_int
r_char
id|val
comma
r_int
id|final_delay
)paren
(brace
r_switch
c_cond
(paren
id|regno
)paren
(brace
r_case
id|COMMAND_REG
suffix:colon
multiline_comment|/* WR0 can be written directly without pointing */
op_star
id|port-&gt;ctrlp
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYNC_CHAR_REG
suffix:colon
multiline_comment|/* For WR7, first set b0 of WR15 to 0, if needed */
r_if
c_cond
(paren
id|shadow
(braket
id|INT_CTRL_REG
)braket
op_amp
id|ICR_OPTIONREG_SELECT
)paren
(brace
op_star
id|port-&gt;ctrlp
op_assign
l_int|15
suffix:semicolon
id|shadow
(braket
id|INT_CTRL_REG
)braket
op_and_assign
op_complement
id|ICR_OPTIONREG_SELECT
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|port-&gt;ctrlp
op_assign
id|shadow
(braket
id|INT_CTRL_REG
)braket
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
)brace
r_goto
id|normal_case
suffix:semicolon
r_case
id|SDLC_OPTION_REG
suffix:colon
multiline_comment|/* For WR7&squot;, first set b0 of WR15 to 1, if needed */
r_if
c_cond
(paren
op_logical_neg
(paren
id|shadow
(braket
id|INT_CTRL_REG
)braket
op_amp
id|ICR_OPTIONREG_SELECT
)paren
)paren
(brace
op_star
id|port-&gt;ctrlp
op_assign
l_int|15
suffix:semicolon
id|shadow
(braket
id|INT_CTRL_REG
)braket
op_or_assign
id|ICR_OPTIONREG_SELECT
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|port-&gt;ctrlp
op_assign
id|shadow
(braket
id|INT_CTRL_REG
)braket
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|port-&gt;ctrlp
op_assign
l_int|7
suffix:semicolon
id|shadow
(braket
l_int|8
)braket
op_assign
id|val
suffix:semicolon
multiline_comment|/* WR7&squot; shadowed at WR8 */
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|port-&gt;ctrlp
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TX_DATA_REG
suffix:colon
multiline_comment|/* WR8 */
multiline_comment|/* TX_DATA_REG can be accessed directly on some h/w */
r_if
c_cond
(paren
id|MACH_IS_MVME16x
op_logical_or
id|MACH_IS_BVME6000
op_logical_or
id|MACH_IS_MVME147
)paren
(brace
op_star
id|port-&gt;ctrlp
op_assign
id|regno
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|port-&gt;ctrlp
op_assign
id|val
suffix:semicolon
)brace
r_else
op_star
id|port-&gt;datap
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MASTER_INT_CTRL
suffix:colon
op_star
id|port-&gt;ctrlp
op_assign
id|regno
suffix:semicolon
id|val
op_and_assign
l_int|0x3f
suffix:semicolon
multiline_comment|/* bits 6..7 are the reset commands */
id|scc_shadow
(braket
l_int|0
)braket
(braket
id|regno
)braket
op_assign
id|val
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|port-&gt;ctrlp
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DPLL_CTRL_REG
suffix:colon
op_star
id|port-&gt;ctrlp
op_assign
id|regno
suffix:semicolon
id|val
op_and_assign
l_int|0x1f
suffix:semicolon
multiline_comment|/* bits 5..7 are the DPLL commands */
id|shadow
(braket
id|regno
)braket
op_assign
id|val
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|port-&gt;ctrlp
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
dot
dot
dot
l_int|6
suffix:colon
r_case
l_int|10
dot
dot
dot
l_int|13
suffix:colon
r_case
l_int|15
suffix:colon
id|normal_case
suffix:colon
op_star
id|port-&gt;ctrlp
op_assign
id|regno
suffix:semicolon
id|shadow
(braket
id|regno
)braket
op_assign
id|val
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|port-&gt;ctrlp
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Bad SCC write access to WR%d&bslash;n&quot;
comma
id|regno
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|final_delay
)paren
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_SCCread
r_static
id|__inline__
r_int
r_char
id|_SCCread
c_func
(paren
r_struct
id|scc_port
op_star
id|port
comma
r_int
r_char
op_star
id|shadow
comma
r_volatile
r_int
r_char
op_star
id|_scc_del
comma
r_int
id|regno
comma
r_int
id|final_delay
)paren
(brace
r_int
r_char
id|rv
suffix:semicolon
r_switch
c_cond
(paren
id|regno
)paren
(brace
multiline_comment|/* --- real read registers --- */
r_case
id|STATUS_REG
suffix:colon
id|rv
op_assign
op_star
id|port-&gt;ctrlp
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INT_PENDING_REG
suffix:colon
multiline_comment|/* RR3: read only from Channel A! */
id|port
op_assign
id|port-&gt;port_a
suffix:semicolon
r_goto
id|normal_case
suffix:semicolon
r_case
id|RX_DATA_REG
suffix:colon
multiline_comment|/* RR8 can be accessed directly on some h/w */
r_if
c_cond
(paren
id|MACH_IS_MVME16x
op_logical_or
id|MACH_IS_BVME6000
op_logical_or
id|MACH_IS_MVME147
)paren
(brace
op_star
id|port-&gt;ctrlp
op_assign
l_int|8
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
id|rv
op_assign
op_star
id|port-&gt;ctrlp
suffix:semicolon
)brace
r_else
id|rv
op_assign
op_star
id|port-&gt;datap
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CURR_VECTOR_REG
suffix:colon
multiline_comment|/* RR2 (vector including status) from Ch. B */
id|port
op_assign
id|port-&gt;port_b
suffix:semicolon
r_goto
id|normal_case
suffix:semicolon
multiline_comment|/* --- reading write registers: access the shadow --- */
r_case
l_int|1
dot
dot
dot
l_int|7
suffix:colon
r_case
l_int|10
dot
dot
dot
l_int|15
suffix:colon
r_return
id|shadow
(braket
id|regno
)braket
suffix:semicolon
multiline_comment|/* no final delay! */
multiline_comment|/* WR7&squot; is special, because it is shadowed at the place of WR8 */
r_case
id|SDLC_OPTION_REG
suffix:colon
r_return
id|shadow
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* no final delay! */
multiline_comment|/* WR9 is special too, because it is common for both channels */
r_case
id|MASTER_INT_CTRL
suffix:colon
r_return
id|scc_shadow
(braket
l_int|0
)braket
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* no final delay! */
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Bad SCC read access to %cR%d&bslash;n&quot;
comma
(paren
id|regno
op_amp
l_int|16
)paren
ques
c_cond
l_char|&squot;R&squot;
suffix:colon
l_char|&squot;W&squot;
comma
id|regno
op_amp
op_complement
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPCOND_STATUS_REG
suffix:colon
r_case
id|FS_FIFO_LOW_REG
suffix:colon
r_case
id|FS_FIFO_HIGH_REG
suffix:colon
r_case
id|DPLL_STATUS_REG
suffix:colon
id|normal_case
suffix:colon
op_star
id|port-&gt;ctrlp
op_assign
id|regno
op_amp
l_int|0x0f
suffix:semicolon
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
id|rv
op_assign
op_star
id|port-&gt;ctrlp
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|final_delay
)paren
id|scc_reg_delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|macro|SCC_ACCESS_INIT
mdefine_line|#define SCC_ACCESS_INIT(port)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char *_scc_shadow = &amp;scc_shadow[port-&gt;channel][0]
DECL|macro|SCCwrite
mdefine_line|#define&t;SCCwrite(reg,val)&t;_SCCwrite(port,_scc_shadow,scc_del,(reg),(val),1)
DECL|macro|SCCwrite_NB
mdefine_line|#define&t;SCCwrite_NB(reg,val)&t;_SCCwrite(port,_scc_shadow,scc_del,(reg),(val),0)
DECL|macro|SCCread
mdefine_line|#define&t;SCCread(reg)&t;&t;_SCCread(port,_scc_shadow,scc_del,(reg),1)
DECL|macro|SCCread_NB
mdefine_line|#define&t;SCCread_NB(reg)&t;&t;_SCCread(port,_scc_shadow,scc_del,(reg),0)
DECL|macro|SCCmod
mdefine_line|#define SCCmod(reg,and,or)&t;SCCwrite((reg),(SCCread(reg)&amp;(and))|(or))
macro_line|#endif /* _SCC_H */
eof
