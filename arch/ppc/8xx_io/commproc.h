multiline_comment|/*&n; * MPC8xx Communication Processor Module.&n; * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)&n; *&n; * This file contains structures and information for the communication&n; * processor channels.  Some CPM control and status is available&n; * throught the MPC8xx internal memory map.  See immap.h for details.&n; * This file only contains what I need for the moment, not the total&n; * CPM capabilities.  I (or someone else) will add definitions as they&n; * are needed.  -- Dan&n; *&n; * On the MBX board, EPPC-Bug loads CPM microcode into the first 512&n; * bytes of the DP RAM and relocates the I2C parameter area to the&n; * IDMA1 space.  The remaining DP RAM is available for buffer descriptors&n; * or other use.&n; */
macro_line|#ifndef __CPM_8XX__
DECL|macro|__CPM_8XX__
mdefine_line|#define __CPM_8XX__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
multiline_comment|/* CPM Command register.&n;*/
DECL|macro|CPM_CR_RST
mdefine_line|#define CPM_CR_RST&t;((ushort)0x8000)
DECL|macro|CPM_CR_OPCODE
mdefine_line|#define CPM_CR_OPCODE&t;((ushort)0x0f00)
DECL|macro|CPM_CR_CHAN
mdefine_line|#define CPM_CR_CHAN&t;((ushort)0x00f0)
DECL|macro|CPM_CR_FLG
mdefine_line|#define CPM_CR_FLG&t;((ushort)0x0001)
multiline_comment|/* Some commands (there are more...later)&n;*/
DECL|macro|CPM_CR_INIT_TRX
mdefine_line|#define CPM_CR_INIT_TRX&t;&t;((ushort)0x0000)
DECL|macro|CPM_CR_INIT_RX
mdefine_line|#define CPM_CR_INIT_RX&t;&t;((ushort)0x0001)
DECL|macro|CPM_CR_INIT_TX
mdefine_line|#define CPM_CR_INIT_TX&t;&t;((ushort)0x0002)
DECL|macro|CPM_CR_HUNT_MODE
mdefine_line|#define CPM_CR_HUNT_MODE&t;((ushort)0x0003)
DECL|macro|CPM_CR_STOP_TX
mdefine_line|#define CPM_CR_STOP_TX&t;&t;((ushort)0x0004)
DECL|macro|CPM_CR_RESTART_TX
mdefine_line|#define CPM_CR_RESTART_TX&t;((ushort)0x0006)
DECL|macro|CPM_CR_SET_GADDR
mdefine_line|#define CPM_CR_SET_GADDR&t;((ushort)0x0008)
multiline_comment|/* Channel numbers.&n;*/
DECL|macro|CPM_CR_CH_SCC1
mdefine_line|#define CPM_CR_CH_SCC1&t;((ushort)0x0000)
DECL|macro|CPM_CR_CH_I2C
mdefine_line|#define CPM_CR_CH_I2C&t;((ushort)0x0001)&t;/* I2C and IDMA1 */
DECL|macro|CPM_CR_CH_SCC2
mdefine_line|#define CPM_CR_CH_SCC2&t;((ushort)0x0004)
DECL|macro|CPM_CR_CH_SPI
mdefine_line|#define CPM_CR_CH_SPI&t;((ushort)0x0005)&t;/* SPI / IDMA2 / Timers */
DECL|macro|CPM_CR_CH_SCC3
mdefine_line|#define CPM_CR_CH_SCC3&t;((ushort)0x0008)
DECL|macro|CPM_CR_CH_SMC1
mdefine_line|#define CPM_CR_CH_SMC1&t;((ushort)0x0009)&t;/* SMC1 / DSP1 */
DECL|macro|CPM_CR_CH_SCC4
mdefine_line|#define CPM_CR_CH_SCC4&t;((ushort)0x000c)
DECL|macro|CPM_CR_CH_SMC2
mdefine_line|#define CPM_CR_CH_SMC2&t;((ushort)0x000d)&t;/* SMC2 / DSP2 */
DECL|macro|mk_cr_cmd
mdefine_line|#define mk_cr_cmd(CH, CMD)&t;((CMD &lt;&lt; 8) | (CH &lt;&lt; 4))
multiline_comment|/* The dual ported RAM is multi-functional.  Some areas can be (and are&n; * being) used for microcode.  There is an area that can only be used&n; * as data ram for buffer descriptors, which is all we use right now.&n; * Currently the first 512 and last 256 bytes are used for microcode.&n; */
DECL|macro|CPM_DATAONLY_BASE
mdefine_line|#define CPM_DATAONLY_BASE&t;((uint)0x0800)
DECL|macro|CPM_DATAONLY_SIZE
mdefine_line|#define CPM_DATAONLY_SIZE&t;((uint)0x0700)
DECL|macro|CPM_DP_NOSPACE
mdefine_line|#define CPM_DP_NOSPACE&t;&t;((uint)0x7fffffff)
multiline_comment|/* Export the base address of the communication processor registers&n; * and dual port ram.&n; */
r_extern
id|cpm8xx_t
op_star
id|cpmp
suffix:semicolon
multiline_comment|/* Pointer to comm processor */
id|uint
id|m8xx_cpm_dpalloc
c_func
(paren
id|uint
id|size
)paren
suffix:semicolon
id|uint
id|m8xx_cpm_hostalloc
c_func
(paren
id|uint
id|size
)paren
suffix:semicolon
r_void
id|m8xx_cpm_setbrg
c_func
(paren
id|uint
id|brg
comma
id|uint
id|rate
)paren
suffix:semicolon
multiline_comment|/* Buffer descriptors used by many of the CPM protocols.&n;*/
DECL|struct|cpm_buf_desc
r_typedef
r_struct
id|cpm_buf_desc
(brace
DECL|member|cbd_sc
id|ushort
id|cbd_sc
suffix:semicolon
multiline_comment|/* Status and Control */
DECL|member|cbd_datlen
id|ushort
id|cbd_datlen
suffix:semicolon
multiline_comment|/* Data length in buffer */
DECL|member|cbd_bufaddr
id|uint
id|cbd_bufaddr
suffix:semicolon
multiline_comment|/* Buffer address in host memory */
DECL|typedef|cbd_t
)brace
id|cbd_t
suffix:semicolon
DECL|macro|BD_SC_EMPTY
mdefine_line|#define BD_SC_EMPTY&t;((ushort)0x8000)&t;/* Receive is empty */
DECL|macro|BD_SC_READY
mdefine_line|#define BD_SC_READY&t;((ushort)0x8000)&t;/* Transmit is ready */
DECL|macro|BD_SC_WRAP
mdefine_line|#define BD_SC_WRAP&t;((ushort)0x2000)&t;/* Last buffer descriptor */
DECL|macro|BD_SC_INTRPT
mdefine_line|#define BD_SC_INTRPT&t;((ushort)0x1000)&t;/* Interrupt on change */
DECL|macro|BD_SC_LAST
mdefine_line|#define BD_SC_LAST&t;((ushort)0x0800)&t;/* Last buffer in frame */
DECL|macro|BD_SC_CM
mdefine_line|#define BD_SC_CM&t;((ushort)0x0200)&t;/* Continous mode */
DECL|macro|BD_SC_ID
mdefine_line|#define BD_SC_ID&t;((ushort)0x0100)&t;/* Rec&squot;d too many idles */
DECL|macro|BD_SC_P
mdefine_line|#define BD_SC_P&t;&t;((ushort)0x0100)&t;/* xmt preamble */
DECL|macro|BD_SC_BR
mdefine_line|#define BD_SC_BR&t;((ushort)0x0020)&t;/* Break received */
DECL|macro|BD_SC_FR
mdefine_line|#define BD_SC_FR&t;((ushort)0x0010)&t;/* Framing error */
DECL|macro|BD_SC_PR
mdefine_line|#define BD_SC_PR&t;((ushort)0x0008)&t;/* Parity error */
DECL|macro|BD_SC_OV
mdefine_line|#define BD_SC_OV&t;((ushort)0x0002)&t;/* Overrun */
DECL|macro|BD_SC_CD
mdefine_line|#define BD_SC_CD&t;((ushort)0x0001)&t;/* ?? */
multiline_comment|/* Parameter RAM offsets.&n;*/
DECL|macro|PROFF_SCC1
mdefine_line|#define PROFF_SCC1&t;((uint)0x0000)
DECL|macro|PROFF_IIC
mdefine_line|#define PROFF_IIC&t;((uint)0x0080)
DECL|macro|PROFF_SCC2
mdefine_line|#define PROFF_SCC2&t;((uint)0x0100)
DECL|macro|PROFF_SCC3
mdefine_line|#define PROFF_SCC3&t;((uint)0x0200)
DECL|macro|PROFF_SMC1
mdefine_line|#define PROFF_SMC1&t;((uint)0x0280)
DECL|macro|PROFF_SCC4
mdefine_line|#define PROFF_SCC4&t;((uint)0x0300)
DECL|macro|PROFF_SMC2
mdefine_line|#define PROFF_SMC2&t;((uint)0x0380)
multiline_comment|/* Define enough so I can at least use the serial port as a UART.&n; * The MBX uses SMC1 as the host serial port.&n; */
DECL|struct|smc_uart
r_typedef
r_struct
id|smc_uart
(brace
DECL|member|smc_rbase
id|ushort
id|smc_rbase
suffix:semicolon
multiline_comment|/* Rx Buffer descriptor base address */
DECL|member|smc_tbase
id|ushort
id|smc_tbase
suffix:semicolon
multiline_comment|/* Tx Buffer descriptor base address */
DECL|member|smc_rfcr
id|u_char
id|smc_rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|smc_tfcr
id|u_char
id|smc_tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|smc_mrblr
id|ushort
id|smc_mrblr
suffix:semicolon
multiline_comment|/* Max receive buffer length */
DECL|member|smc_rstate
id|uint
id|smc_rstate
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_idp
id|uint
id|smc_idp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_rbptr
id|ushort
id|smc_rbptr
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_ibc
id|ushort
id|smc_ibc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_rxtmp
id|uint
id|smc_rxtmp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_tstate
id|uint
id|smc_tstate
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_tdp
id|uint
id|smc_tdp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_tbptr
id|ushort
id|smc_tbptr
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_tbc
id|ushort
id|smc_tbc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_txtmp
id|uint
id|smc_txtmp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|smc_maxidl
id|ushort
id|smc_maxidl
suffix:semicolon
multiline_comment|/* Maximum idle characters */
DECL|member|smc_tmpidl
id|ushort
id|smc_tmpidl
suffix:semicolon
multiline_comment|/* Temporary idle counter */
DECL|member|smc_brklen
id|ushort
id|smc_brklen
suffix:semicolon
multiline_comment|/* Last received break length */
DECL|member|smc_brkec
id|ushort
id|smc_brkec
suffix:semicolon
multiline_comment|/* rcv&squot;d break condition counter */
DECL|member|smc_brkcr
id|ushort
id|smc_brkcr
suffix:semicolon
multiline_comment|/* xmt break count register */
DECL|member|smc_rmask
id|ushort
id|smc_rmask
suffix:semicolon
multiline_comment|/* Temporary bit mask */
DECL|typedef|smc_uart_t
)brace
id|smc_uart_t
suffix:semicolon
multiline_comment|/* Function code bits.&n;*/
DECL|macro|SMC_EB
mdefine_line|#define SMC_EB&t;((u_char)0x10)&t;/* Set big endian byte order */
multiline_comment|/* SMC uart mode register.&n;*/
DECL|macro|SMCMR_REN
mdefine_line|#define&t;SMCMR_REN&t;((ushort)0x0001)
DECL|macro|SMCMR_TEN
mdefine_line|#define SMCMR_TEN&t;((ushort)0x0002)
DECL|macro|SMCMR_DM
mdefine_line|#define SMCMR_DM&t;((ushort)0x000c)
DECL|macro|SMCMR_SM_GCI
mdefine_line|#define SMCMR_SM_GCI&t;((ushort)0x0000)
DECL|macro|SMCMR_SM_UART
mdefine_line|#define SMCMR_SM_UART&t;((ushort)0x0020)
DECL|macro|SMCMR_SM_TRANS
mdefine_line|#define SMCMR_SM_TRANS&t;((ushort)0x0030)
DECL|macro|SMCMR_SM_MASK
mdefine_line|#define SMCMR_SM_MASK&t;((ushort)0x0030)
DECL|macro|SMCMR_PM_EVEN
mdefine_line|#define SMCMR_PM_EVEN&t;((ushort)0x0100)&t;/* Even parity, else odd */
DECL|macro|SMCMR_REVD
mdefine_line|#define SMCMR_REVD&t;SMCMR_PM_EVEN
DECL|macro|SMCMR_PEN
mdefine_line|#define SMCMR_PEN&t;((ushort)0x0200)&t;/* Parity enable */
DECL|macro|SMCMR_BS
mdefine_line|#define SMCMR_BS&t;SMCMR_PEN
DECL|macro|SMCMR_SL
mdefine_line|#define SMCMR_SL&t;((ushort)0x0400)&t;/* Two stops, else one */
DECL|macro|SMCR_CLEN_MASK
mdefine_line|#define SMCR_CLEN_MASK&t;((ushort)0x7800)&t;/* Character length */
DECL|macro|smcr_mk_clen
mdefine_line|#define smcr_mk_clen(C)&t;(((C) &lt;&lt; 11) &amp; SMCR_CLEN_MASK)
multiline_comment|/* SMC2 as Centronics parallel printer.  It is half duplex, in that&n; * it can only receive or transmit.  The parameter ram values for&n; * each direction are either unique or properly overlap, so we can&n; * include them in one structure.&n; */
DECL|struct|smc_centronics
r_typedef
r_struct
id|smc_centronics
(brace
DECL|member|scent_rbase
id|ushort
id|scent_rbase
suffix:semicolon
DECL|member|scent_tbase
id|ushort
id|scent_tbase
suffix:semicolon
DECL|member|scent_cfcr
id|u_char
id|scent_cfcr
suffix:semicolon
DECL|member|scent_smask
id|u_char
id|scent_smask
suffix:semicolon
DECL|member|scent_mrblr
id|ushort
id|scent_mrblr
suffix:semicolon
DECL|member|scent_rstate
id|uint
id|scent_rstate
suffix:semicolon
DECL|member|scent_r_ptr
id|uint
id|scent_r_ptr
suffix:semicolon
DECL|member|scent_rbptr
id|ushort
id|scent_rbptr
suffix:semicolon
DECL|member|scent_r_cnt
id|ushort
id|scent_r_cnt
suffix:semicolon
DECL|member|scent_rtemp
id|uint
id|scent_rtemp
suffix:semicolon
DECL|member|scent_tstate
id|uint
id|scent_tstate
suffix:semicolon
DECL|member|scent_t_ptr
id|uint
id|scent_t_ptr
suffix:semicolon
DECL|member|scent_tbptr
id|ushort
id|scent_tbptr
suffix:semicolon
DECL|member|scent_t_cnt
id|ushort
id|scent_t_cnt
suffix:semicolon
DECL|member|scent_ttemp
id|uint
id|scent_ttemp
suffix:semicolon
DECL|member|scent_max_sl
id|ushort
id|scent_max_sl
suffix:semicolon
DECL|member|scent_sl_cnt
id|ushort
id|scent_sl_cnt
suffix:semicolon
DECL|member|scent_character1
id|ushort
id|scent_character1
suffix:semicolon
DECL|member|scent_character2
id|ushort
id|scent_character2
suffix:semicolon
DECL|member|scent_character3
id|ushort
id|scent_character3
suffix:semicolon
DECL|member|scent_character4
id|ushort
id|scent_character4
suffix:semicolon
DECL|member|scent_character5
id|ushort
id|scent_character5
suffix:semicolon
DECL|member|scent_character6
id|ushort
id|scent_character6
suffix:semicolon
DECL|member|scent_character7
id|ushort
id|scent_character7
suffix:semicolon
DECL|member|scent_character8
id|ushort
id|scent_character8
suffix:semicolon
DECL|member|scent_rccm
id|ushort
id|scent_rccm
suffix:semicolon
DECL|member|scent_rccr
id|ushort
id|scent_rccr
suffix:semicolon
DECL|typedef|smc_cent_t
)brace
id|smc_cent_t
suffix:semicolon
multiline_comment|/* Centronics Status Mask Register.&n;*/
DECL|macro|SMC_CENT_F
mdefine_line|#define SMC_CENT_F&t;((u_char)0x08)
DECL|macro|SMC_CENT_PE
mdefine_line|#define SMC_CENT_PE&t;((u_char)0x04)
DECL|macro|SMC_CENT_S
mdefine_line|#define SMC_CENT_S&t;((u_char)0x02)
multiline_comment|/* SMC Event and Mask register.&n;*/
DECL|macro|SMCM_BRKE
mdefine_line|#define&t;SMCM_BRKE&t;((unsigned char)0x40)&t;/* When in UART Mode */
DECL|macro|SMCM_BRK
mdefine_line|#define&t;SMCM_BRK&t;((unsigned char)0x10)&t;/* When in UART Mode */
DECL|macro|SMCM_TXE
mdefine_line|#define&t;SMCM_TXE&t;((unsigned char)0x10)&t;/* When in Transparent Mode */
DECL|macro|SMCM_BSY
mdefine_line|#define&t;SMCM_BSY&t;((unsigned char)0x04)
DECL|macro|SMCM_TX
mdefine_line|#define&t;SMCM_TX&t;&t;((unsigned char)0x02)
DECL|macro|SMCM_RX
mdefine_line|#define&t;SMCM_RX&t;&t;((unsigned char)0x01)
multiline_comment|/* Baud rate generators.&n;*/
DECL|macro|CPM_BRG_RST
mdefine_line|#define CPM_BRG_RST&t;&t;((uint)0x00020000)
DECL|macro|CPM_BRG_EN
mdefine_line|#define CPM_BRG_EN&t;&t;((uint)0x00010000)
DECL|macro|CPM_BRG_EXTC_INT
mdefine_line|#define CPM_BRG_EXTC_INT&t;((uint)0x00000000)
DECL|macro|CPM_BRG_EXTC_CLK2
mdefine_line|#define CPM_BRG_EXTC_CLK2&t;((uint)0x00004000)
DECL|macro|CPM_BRG_EXTC_CLK6
mdefine_line|#define CPM_BRG_EXTC_CLK6&t;((uint)0x00008000)
DECL|macro|CPM_BRG_ATB
mdefine_line|#define CPM_BRG_ATB&t;&t;((uint)0x00002000)
DECL|macro|CPM_BRG_CD_MASK
mdefine_line|#define CPM_BRG_CD_MASK&t;&t;((uint)0x00001ffe)
DECL|macro|CPM_BRG_DIV16
mdefine_line|#define CPM_BRG_DIV16&t;&t;((uint)0x00000001)
multiline_comment|/* SCCs.&n;*/
DECL|macro|SCC_GSMRH_IRP
mdefine_line|#define SCC_GSMRH_IRP&t;&t;((uint)0x00040000)
DECL|macro|SCC_GSMRH_GDE
mdefine_line|#define SCC_GSMRH_GDE&t;&t;((uint)0x00010000)
DECL|macro|SCC_GSMRH_TCRC_CCITT
mdefine_line|#define SCC_GSMRH_TCRC_CCITT&t;((uint)0x00008000)
DECL|macro|SCC_GSMRH_TCRC_BISYNC
mdefine_line|#define SCC_GSMRH_TCRC_BISYNC&t;((uint)0x00004000)
DECL|macro|SCC_GSMRH_TCRC_HDLC
mdefine_line|#define SCC_GSMRH_TCRC_HDLC&t;((uint)0x00000000)
DECL|macro|SCC_GSMRH_REVD
mdefine_line|#define SCC_GSMRH_REVD&t;&t;((uint)0x00002000)
DECL|macro|SCC_GSMRH_TRX
mdefine_line|#define SCC_GSMRH_TRX&t;&t;((uint)0x00001000)
DECL|macro|SCC_GSMRH_TTX
mdefine_line|#define SCC_GSMRH_TTX&t;&t;((uint)0x00000800)
DECL|macro|SCC_GSMRH_CDP
mdefine_line|#define SCC_GSMRH_CDP&t;&t;((uint)0x00000400)
DECL|macro|SCC_GSMRH_CTSP
mdefine_line|#define SCC_GSMRH_CTSP&t;&t;((uint)0x00000200)
DECL|macro|SCC_GSMRH_CDS
mdefine_line|#define SCC_GSMRH_CDS&t;&t;((uint)0x00000100)
DECL|macro|SCC_GSMRH_CTSS
mdefine_line|#define SCC_GSMRH_CTSS&t;&t;((uint)0x00000080)
DECL|macro|SCC_GSMRH_TFL
mdefine_line|#define SCC_GSMRH_TFL&t;&t;((uint)0x00000040)
DECL|macro|SCC_GSMRH_RFW
mdefine_line|#define SCC_GSMRH_RFW&t;&t;((uint)0x00000020)
DECL|macro|SCC_GSMRH_TXSY
mdefine_line|#define SCC_GSMRH_TXSY&t;&t;((uint)0x00000010)
DECL|macro|SCC_GSMRH_SYNL16
mdefine_line|#define SCC_GSMRH_SYNL16&t;((uint)0x0000000c)
DECL|macro|SCC_GSMRH_SYNL8
mdefine_line|#define SCC_GSMRH_SYNL8&t;&t;((uint)0x00000008)
DECL|macro|SCC_GSMRH_SYNL4
mdefine_line|#define SCC_GSMRH_SYNL4&t;&t;((uint)0x00000004)
DECL|macro|SCC_GSMRH_RTSM
mdefine_line|#define SCC_GSMRH_RTSM&t;&t;((uint)0x00000002)
DECL|macro|SCC_GSMRH_RSYN
mdefine_line|#define SCC_GSMRH_RSYN&t;&t;((uint)0x00000001)
DECL|macro|SCC_GSMRL_SIR
mdefine_line|#define SCC_GSMRL_SIR&t;&t;((uint)0x80000000)&t;/* SCC2 only */
DECL|macro|SCC_GSMRL_EDGE_NONE
mdefine_line|#define SCC_GSMRL_EDGE_NONE&t;((uint)0x60000000)
DECL|macro|SCC_GSMRL_EDGE_NEG
mdefine_line|#define SCC_GSMRL_EDGE_NEG&t;((uint)0x40000000)
DECL|macro|SCC_GSMRL_EDGE_POS
mdefine_line|#define SCC_GSMRL_EDGE_POS&t;((uint)0x20000000)
DECL|macro|SCC_GSMRL_EDGE_BOTH
mdefine_line|#define SCC_GSMRL_EDGE_BOTH&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_TCI
mdefine_line|#define SCC_GSMRL_TCI&t;&t;((uint)0x10000000)
DECL|macro|SCC_GSMRL_TSNC_3
mdefine_line|#define SCC_GSMRL_TSNC_3&t;((uint)0x0c000000)
DECL|macro|SCC_GSMRL_TSNC_4
mdefine_line|#define SCC_GSMRL_TSNC_4&t;((uint)0x08000000)
DECL|macro|SCC_GSMRL_TSNC_14
mdefine_line|#define SCC_GSMRL_TSNC_14&t;((uint)0x04000000)
DECL|macro|SCC_GSMRL_TSNC_INF
mdefine_line|#define SCC_GSMRL_TSNC_INF&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_RINV
mdefine_line|#define SCC_GSMRL_RINV&t;&t;((uint)0x02000000)
DECL|macro|SCC_GSMRL_TINV
mdefine_line|#define SCC_GSMRL_TINV&t;&t;((uint)0x01000000)
DECL|macro|SCC_GSMRL_TPL_128
mdefine_line|#define SCC_GSMRL_TPL_128&t;((uint)0x00c00000)
DECL|macro|SCC_GSMRL_TPL_64
mdefine_line|#define SCC_GSMRL_TPL_64&t;((uint)0x00a00000)
DECL|macro|SCC_GSMRL_TPL_48
mdefine_line|#define SCC_GSMRL_TPL_48&t;((uint)0x00800000)
DECL|macro|SCC_GSMRL_TPL_32
mdefine_line|#define SCC_GSMRL_TPL_32&t;((uint)0x00600000)
DECL|macro|SCC_GSMRL_TPL_16
mdefine_line|#define SCC_GSMRL_TPL_16&t;((uint)0x00400000)
DECL|macro|SCC_GSMRL_TPL_8
mdefine_line|#define SCC_GSMRL_TPL_8&t;&t;((uint)0x00200000)
DECL|macro|SCC_GSMRL_TPL_NONE
mdefine_line|#define SCC_GSMRL_TPL_NONE&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_TPP_ALL1
mdefine_line|#define SCC_GSMRL_TPP_ALL1&t;((uint)0x00180000)
DECL|macro|SCC_GSMRL_TPP_01
mdefine_line|#define SCC_GSMRL_TPP_01&t;((uint)0x00100000)
DECL|macro|SCC_GSMRL_TPP_10
mdefine_line|#define SCC_GSMRL_TPP_10&t;((uint)0x00080000)
DECL|macro|SCC_GSMRL_TPP_ZEROS
mdefine_line|#define SCC_GSMRL_TPP_ZEROS&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_TEND
mdefine_line|#define SCC_GSMRL_TEND&t;&t;((uint)0x00040000)
DECL|macro|SCC_GSMRL_TDCR_32
mdefine_line|#define SCC_GSMRL_TDCR_32&t;((uint)0x00030000)
DECL|macro|SCC_GSMRL_TDCR_16
mdefine_line|#define SCC_GSMRL_TDCR_16&t;((uint)0x00020000)
DECL|macro|SCC_GSMRL_TDCR_8
mdefine_line|#define SCC_GSMRL_TDCR_8&t;((uint)0x00010000)
DECL|macro|SCC_GSMRL_TDCR_1
mdefine_line|#define SCC_GSMRL_TDCR_1&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_RDCR_32
mdefine_line|#define SCC_GSMRL_RDCR_32&t;((uint)0x0000c000)
DECL|macro|SCC_GSMRL_RDCR_16
mdefine_line|#define SCC_GSMRL_RDCR_16&t;((uint)0x00008000)
DECL|macro|SCC_GSMRL_RDCR_8
mdefine_line|#define SCC_GSMRL_RDCR_8&t;((uint)0x00004000)
DECL|macro|SCC_GSMRL_RDCR_1
mdefine_line|#define SCC_GSMRL_RDCR_1&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_RENC_DFMAN
mdefine_line|#define SCC_GSMRL_RENC_DFMAN&t;((uint)0x00003000)
DECL|macro|SCC_GSMRL_RENC_MANCH
mdefine_line|#define SCC_GSMRL_RENC_MANCH&t;((uint)0x00002000)
DECL|macro|SCC_GSMRL_RENC_FM0
mdefine_line|#define SCC_GSMRL_RENC_FM0&t;((uint)0x00001000)
DECL|macro|SCC_GSMRL_RENC_NRZI
mdefine_line|#define SCC_GSMRL_RENC_NRZI&t;((uint)0x00000800)
DECL|macro|SCC_GSMRL_RENC_NRZ
mdefine_line|#define SCC_GSMRL_RENC_NRZ&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_TENC_DFMAN
mdefine_line|#define SCC_GSMRL_TENC_DFMAN&t;((uint)0x00000600)
DECL|macro|SCC_GSMRL_TENC_MANCH
mdefine_line|#define SCC_GSMRL_TENC_MANCH&t;((uint)0x00000400)
DECL|macro|SCC_GSMRL_TENC_FM0
mdefine_line|#define SCC_GSMRL_TENC_FM0&t;((uint)0x00000200)
DECL|macro|SCC_GSMRL_TENC_NRZI
mdefine_line|#define SCC_GSMRL_TENC_NRZI&t;((uint)0x00000100)
DECL|macro|SCC_GSMRL_TENC_NRZ
mdefine_line|#define SCC_GSMRL_TENC_NRZ&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_DIAG_LE
mdefine_line|#define SCC_GSMRL_DIAG_LE&t;((uint)0x000000c0)&t;/* Loop and echo */
DECL|macro|SCC_GSMRL_DIAG_ECHO
mdefine_line|#define SCC_GSMRL_DIAG_ECHO&t;((uint)0x00000080)
DECL|macro|SCC_GSMRL_DIAG_LOOP
mdefine_line|#define SCC_GSMRL_DIAG_LOOP&t;((uint)0x00000040)
DECL|macro|SCC_GSMRL_DIAG_NORM
mdefine_line|#define SCC_GSMRL_DIAG_NORM&t;((uint)0x00000000)
DECL|macro|SCC_GSMRL_ENR
mdefine_line|#define SCC_GSMRL_ENR&t;&t;((uint)0x00000020)
DECL|macro|SCC_GSMRL_ENT
mdefine_line|#define SCC_GSMRL_ENT&t;&t;((uint)0x00000010)
DECL|macro|SCC_GSMRL_MODE_ENET
mdefine_line|#define SCC_GSMRL_MODE_ENET&t;((uint)0x0000000c)
DECL|macro|SCC_GSMRL_MODE_DDCMP
mdefine_line|#define SCC_GSMRL_MODE_DDCMP&t;((uint)0x00000009)
DECL|macro|SCC_GSMRL_MODE_BISYNC
mdefine_line|#define SCC_GSMRL_MODE_BISYNC&t;((uint)0x00000008)
DECL|macro|SCC_GSMRL_MODE_V14
mdefine_line|#define SCC_GSMRL_MODE_V14&t;((uint)0x00000007)
DECL|macro|SCC_GSMRL_MODE_AHDLC
mdefine_line|#define SCC_GSMRL_MODE_AHDLC&t;((uint)0x00000006)
DECL|macro|SCC_GSMRL_MODE_PROFIBUS
mdefine_line|#define SCC_GSMRL_MODE_PROFIBUS&t;((uint)0x00000005)
DECL|macro|SCC_GSMRL_MODE_UART
mdefine_line|#define SCC_GSMRL_MODE_UART&t;((uint)0x00000004)
DECL|macro|SCC_GSMRL_MODE_SS7
mdefine_line|#define SCC_GSMRL_MODE_SS7&t;((uint)0x00000003)
DECL|macro|SCC_GSMRL_MODE_ATALK
mdefine_line|#define SCC_GSMRL_MODE_ATALK&t;((uint)0x00000002)
DECL|macro|SCC_GSMRL_MODE_HDLC
mdefine_line|#define SCC_GSMRL_MODE_HDLC&t;((uint)0x00000000)
DECL|macro|SCC_TODR_TOD
mdefine_line|#define SCC_TODR_TOD&t;&t;((ushort)0x8000)
multiline_comment|/* SCC Event and Mask register.&n;*/
DECL|macro|SCCM_TXE
mdefine_line|#define&t;SCCM_TXE&t;((unsigned char)0x10)
DECL|macro|SCCM_BSY
mdefine_line|#define&t;SCCM_BSY&t;((unsigned char)0x04)
DECL|macro|SCCM_TX
mdefine_line|#define&t;SCCM_TX&t;&t;((unsigned char)0x02)
DECL|macro|SCCM_RX
mdefine_line|#define&t;SCCM_RX&t;&t;((unsigned char)0x01)
DECL|struct|scc_param
r_typedef
r_struct
id|scc_param
(brace
DECL|member|scc_rbase
id|ushort
id|scc_rbase
suffix:semicolon
multiline_comment|/* Rx Buffer descriptor base address */
DECL|member|scc_tbase
id|ushort
id|scc_tbase
suffix:semicolon
multiline_comment|/* Tx Buffer descriptor base address */
DECL|member|scc_rfcr
id|u_char
id|scc_rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|scc_tfcr
id|u_char
id|scc_tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|scc_mrblr
id|ushort
id|scc_mrblr
suffix:semicolon
multiline_comment|/* Max receive buffer length */
DECL|member|scc_rstate
id|uint
id|scc_rstate
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_idp
id|uint
id|scc_idp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_rbptr
id|ushort
id|scc_rbptr
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_ibc
id|ushort
id|scc_ibc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_rxtmp
id|uint
id|scc_rxtmp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_tstate
id|uint
id|scc_tstate
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_tdp
id|uint
id|scc_tdp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_tbptr
id|ushort
id|scc_tbptr
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_tbc
id|ushort
id|scc_tbc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_txtmp
id|uint
id|scc_txtmp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_rcrc
id|uint
id|scc_rcrc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|scc_tcrc
id|uint
id|scc_tcrc
suffix:semicolon
multiline_comment|/* Internal */
DECL|typedef|sccp_t
)brace
id|sccp_t
suffix:semicolon
multiline_comment|/* Function code bits.&n;*/
DECL|macro|SCC_EB
mdefine_line|#define SCC_EB&t;((u_char)0x10)&t;/* Set big endian byte order */
multiline_comment|/* CPM Ethernet through SCC1.&n; */
DECL|struct|scc_enet
r_typedef
r_struct
id|scc_enet
(brace
DECL|member|sen_genscc
id|sccp_t
id|sen_genscc
suffix:semicolon
DECL|member|sen_cpres
id|uint
id|sen_cpres
suffix:semicolon
multiline_comment|/* Preset CRC */
DECL|member|sen_cmask
id|uint
id|sen_cmask
suffix:semicolon
multiline_comment|/* Constant mask for CRC */
DECL|member|sen_crcec
id|uint
id|sen_crcec
suffix:semicolon
multiline_comment|/* CRC Error counter */
DECL|member|sen_alec
id|uint
id|sen_alec
suffix:semicolon
multiline_comment|/* alignment error counter */
DECL|member|sen_disfc
id|uint
id|sen_disfc
suffix:semicolon
multiline_comment|/* discard frame counter */
DECL|member|sen_pads
id|ushort
id|sen_pads
suffix:semicolon
multiline_comment|/* Tx short frame pad character */
DECL|member|sen_retlim
id|ushort
id|sen_retlim
suffix:semicolon
multiline_comment|/* Retry limit threshold */
DECL|member|sen_retcnt
id|ushort
id|sen_retcnt
suffix:semicolon
multiline_comment|/* Retry limit counter */
DECL|member|sen_maxflr
id|ushort
id|sen_maxflr
suffix:semicolon
multiline_comment|/* maximum frame length register */
DECL|member|sen_minflr
id|ushort
id|sen_minflr
suffix:semicolon
multiline_comment|/* minimum frame length register */
DECL|member|sen_maxd1
id|ushort
id|sen_maxd1
suffix:semicolon
multiline_comment|/* maximum DMA1 length */
DECL|member|sen_maxd2
id|ushort
id|sen_maxd2
suffix:semicolon
multiline_comment|/* maximum DMA2 length */
DECL|member|sen_maxd
id|ushort
id|sen_maxd
suffix:semicolon
multiline_comment|/* Rx max DMA */
DECL|member|sen_dmacnt
id|ushort
id|sen_dmacnt
suffix:semicolon
multiline_comment|/* Rx DMA counter */
DECL|member|sen_maxb
id|ushort
id|sen_maxb
suffix:semicolon
multiline_comment|/* Max BD byte count */
DECL|member|sen_gaddr1
id|ushort
id|sen_gaddr1
suffix:semicolon
multiline_comment|/* Group address filter */
DECL|member|sen_gaddr2
id|ushort
id|sen_gaddr2
suffix:semicolon
DECL|member|sen_gaddr3
id|ushort
id|sen_gaddr3
suffix:semicolon
DECL|member|sen_gaddr4
id|ushort
id|sen_gaddr4
suffix:semicolon
DECL|member|sen_tbuf0data0
id|uint
id|sen_tbuf0data0
suffix:semicolon
multiline_comment|/* Save area 0 - current frame */
DECL|member|sen_tbuf0data1
id|uint
id|sen_tbuf0data1
suffix:semicolon
multiline_comment|/* Save area 1 - current frame */
DECL|member|sen_tbuf0rba
id|uint
id|sen_tbuf0rba
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|sen_tbuf0crc
id|uint
id|sen_tbuf0crc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|sen_tbuf0bcnt
id|ushort
id|sen_tbuf0bcnt
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|sen_paddrh
id|ushort
id|sen_paddrh
suffix:semicolon
multiline_comment|/* physical address (MSB) */
DECL|member|sen_paddrm
id|ushort
id|sen_paddrm
suffix:semicolon
DECL|member|sen_paddrl
id|ushort
id|sen_paddrl
suffix:semicolon
multiline_comment|/* physical address (LSB) */
DECL|member|sen_pper
id|ushort
id|sen_pper
suffix:semicolon
multiline_comment|/* persistence */
DECL|member|sen_rfbdptr
id|ushort
id|sen_rfbdptr
suffix:semicolon
multiline_comment|/* Rx first BD pointer */
DECL|member|sen_tfbdptr
id|ushort
id|sen_tfbdptr
suffix:semicolon
multiline_comment|/* Tx first BD pointer */
DECL|member|sen_tlbdptr
id|ushort
id|sen_tlbdptr
suffix:semicolon
multiline_comment|/* Tx last BD pointer */
DECL|member|sen_tbuf1data0
id|uint
id|sen_tbuf1data0
suffix:semicolon
multiline_comment|/* Save area 0 - current frame */
DECL|member|sen_tbuf1data1
id|uint
id|sen_tbuf1data1
suffix:semicolon
multiline_comment|/* Save area 1 - current frame */
DECL|member|sen_tbuf1rba
id|uint
id|sen_tbuf1rba
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|sen_tbuf1crc
id|uint
id|sen_tbuf1crc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|sen_tbuf1bcnt
id|ushort
id|sen_tbuf1bcnt
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|sen_txlen
id|ushort
id|sen_txlen
suffix:semicolon
multiline_comment|/* Tx Frame length counter */
DECL|member|sen_iaddr1
id|ushort
id|sen_iaddr1
suffix:semicolon
multiline_comment|/* Individual address filter */
DECL|member|sen_iaddr2
id|ushort
id|sen_iaddr2
suffix:semicolon
DECL|member|sen_iaddr3
id|ushort
id|sen_iaddr3
suffix:semicolon
DECL|member|sen_iaddr4
id|ushort
id|sen_iaddr4
suffix:semicolon
DECL|member|sen_boffcnt
id|ushort
id|sen_boffcnt
suffix:semicolon
multiline_comment|/* Backoff counter */
multiline_comment|/* NOTE: Some versions of the manual have the following items&n;&t; * incorrectly documented.  Below is the proper order.&n;&t; */
DECL|member|sen_taddrh
id|ushort
id|sen_taddrh
suffix:semicolon
multiline_comment|/* temp address (MSB) */
DECL|member|sen_taddrm
id|ushort
id|sen_taddrm
suffix:semicolon
DECL|member|sen_taddrl
id|ushort
id|sen_taddrl
suffix:semicolon
multiline_comment|/* temp address (LSB) */
DECL|typedef|scc_enet_t
)brace
id|scc_enet_t
suffix:semicolon
macro_line|#ifdef CONFIG_MBX
multiline_comment|/* Bits in parallel I/O port registers that have to be set/cleared&n; * to configure the pins for SCC1 use.  The TCLK and RCLK seem unique&n; * to the MBX860 board.  Any two of the four available clocks could be&n; * used, and the MPC860 cookbook manual has an example using different&n; * clock pins.&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0001)
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0002)
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0200)
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0800)
DECL|macro|PC_ENET_TENA
mdefine_line|#define PC_ENET_TENA&t;((ushort)0x0001)
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0010)
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0020)
multiline_comment|/* Control bits in the SICR to route TCLK (CLK2) and RCLK (CLK4) to&n; * SCC1.  Also, make sure GR1 (bit 24) and SC1 (bit 25) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x000000ff)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x0000003d)
macro_line|#endif
macro_line|#ifdef CONFIG_RPXLITE
multiline_comment|/* This ENET stuff is for the MPC850 with ethernet on SCC2.  Some of&n; * this may be unique to the RPX-Lite configuration.&n; * Note TENA is on Port B.&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0004)
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0008)
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0200)
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0800)
DECL|macro|PB_ENET_TENA
mdefine_line|#define PB_ENET_TENA&t;((uint)0x00002000)
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0040)
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0080)
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x0000ff00)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00003d00)
macro_line|#endif
macro_line|#ifdef CONFIG_BSEIP
multiline_comment|/* This ENET stuff is for the MPC823 with ethernet on SCC2.&n; * This is unique to the BSE ip-Engine board.&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0004)
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0008)
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0100)
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0200)
DECL|macro|PB_ENET_TENA
mdefine_line|#define PB_ENET_TENA&t;((uint)0x00002000)
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0040)
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0080)
multiline_comment|/* BSE uses port B and C bits for PHY control also.&n;*/
DECL|macro|PB_BSE_POWERUP
mdefine_line|#define PB_BSE_POWERUP&t;((uint)0x00000004)
DECL|macro|PB_BSE_FDXDIS
mdefine_line|#define PB_BSE_FDXDIS&t;((uint)0x00008000)
DECL|macro|PC_BSE_LOOPBACK
mdefine_line|#define PC_BSE_LOOPBACK&t;((ushort)0x0800)
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x0000ff00)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00002c00)
macro_line|#endif
macro_line|#ifdef CONFIG_RPXCLASSIC
multiline_comment|/* Bits in parallel I/O port registers that have to be set/cleared&n; * to configure the pins for SCC1 use.&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0001)
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0002)
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0200)
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0800)
DECL|macro|PB_ENET_TENA
mdefine_line|#define PB_ENET_TENA&t;((uint)0x00001000)
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0010)
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0020)
multiline_comment|/* Control bits in the SICR to route TCLK (CLK2) and RCLK (CLK4) to&n; * SCC1.  Also, make sure GR1 (bit 24) and SC1 (bit 25) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x000000ff)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x0000003d)
macro_line|#endif
macro_line|#if (defined(CONFIG_TQM860) || defined(CONFIG_TQM860L))
multiline_comment|/*&n; * TQM860 and TQM860L Configuration:&n; *&n; * Signal       PAR     DIR     ODR     DAT     Function&n; * Port A,  5    1       0       -       -       TCLK (CLK3) for Ethernet&n; * Port A,  7    1       0       -       -       RCLK (CLK1) for Ethernet&n; * Port A, 14    1       0       -       -       TXD for Ethernet (SCC1)&n; * Port A, 15    1       0       -       -       RXD for Ethernet (SCC1)&n; * Port C,  7    0       0       0       -       -&gt; ETH-LOOP&n; * Port C, 10    0       0       1       -       CD  for Ethernet (SCC1)&n; * Port C, 11    0       0       1       -       CTS for Ethernet (SCC1)&n; * Port C, 15    *       *       0       -       TENA/RTS for Ethernet&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0001)&t;/* PA 15 */
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0002)&t;/* PA 14 */
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0400)&t;/* PA  5 */
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0100)&t;/* PA  7 */
DECL|macro|PC_ENET_TENA
mdefine_line|#define PC_ENET_TENA&t;((ushort)0x0001)&t;/* PC 15 */
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0010)&t;/* PC 11 */
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0020)&t;/* PC 10 */
multiline_comment|/* Control bits in the SICR to route TCLK (CLK3) and RCLK (CLK1) to&n; * SCC1.  Also, make sure GR1 (bit 24) and SC1 (bit 25) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x000000ff)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00000026)
macro_line|#endif&t;/* CONFIG_TQM860, TQM860L */
macro_line|#ifdef CONFIG_TQM8xxL
multiline_comment|/*&n; * TQM8xxL Configuration (except TQM860L):&n; *&n; * Signal       PAR     DIR     ODR     DAT     Function&n; * Port A,  5    1       0       -       -       TCLK (CLK3) for Ethernet&n; * Port A,  7    1       0       -       -       RCLK (CLK1) for Ethernet&n; * Port A, 12    1       0       -       -       TXD for Ethernet (SCC2)&n; * Port A, 13    1       0       -       -       RXD for Ethernet (SCC2)&n; * Port B, 18    1       1       -       -       TENA/RTS for Ethernet on STK8xx&n; * Port C,  7    0       0       0       -       -&gt; ETH-LOOP&n; * Port C,  8    0       0       1       -       CD  for Ethernet (SCC2)&n; * Port C,  9    0       0       1       -       CTS for Ethernet (SCC2)&n; * Port C, 14    *       *       0       -       TENA/RTS for Ethernet on FPS850&n; *&n; * Note: Using PC14 as RTS2 (TENA) does not work on the TQM850L when&n; * used with the starter-kit mainboard; we *must* use PB18 instead.&n; * For the FPS850 system, we *must* use PC14 :-(&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0004)&t;/* PA 13 */
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0008)&t;/* PA 12 */
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0100)&t;/* PA  7 */
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0400)&t;/* PA  5 */
macro_line|#ifndef&t;CONFIG_FPS850&t;/* not valid on FPS board */
DECL|macro|PB_ENET_TENA
mdefine_line|#define&t;PB_ENET_TENA&t;((uint)0x00002000)
macro_line|#endif&t;/* !CONFIG_FPS850 */
macro_line|#ifdef&t;CONFIG_FPS850&t;/* FPS uses default configuration */
DECL|macro|PC_ENET_TENA
mdefine_line|#define PC_ENET_TENA&t;((ushort)0x0002)&t;/* PC 14 */
macro_line|#endif&t;/* CONFIG_FPS850 */
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0040)&t;/* PC  9 */
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0080)&t;/* PC  8 */
multiline_comment|/* Control bits in the SICR to route TCLK (CLK3) and RCLK (CLK1) to&n; * SCC2.  Also, make sure GR2 (bit 16) and SC2 (bit 17) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x0000ff00)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00002600)
macro_line|#endif&t;/* CONFIG_TQM8xxL */
multiline_comment|/* SCC Event register as used by Ethernet.&n;*/
DECL|macro|SCCE_ENET_GRA
mdefine_line|#define SCCE_ENET_GRA&t;((ushort)0x0080)&t;/* Graceful stop complete */
DECL|macro|SCCE_ENET_TXE
mdefine_line|#define SCCE_ENET_TXE&t;((ushort)0x0010)&t;/* Transmit Error */
DECL|macro|SCCE_ENET_RXF
mdefine_line|#define SCCE_ENET_RXF&t;((ushort)0x0008)&t;/* Full frame received */
DECL|macro|SCCE_ENET_BSY
mdefine_line|#define SCCE_ENET_BSY&t;((ushort)0x0004)&t;/* All incoming buffers full */
DECL|macro|SCCE_ENET_TXB
mdefine_line|#define SCCE_ENET_TXB&t;((ushort)0x0002)&t;/* A buffer was transmitted */
DECL|macro|SCCE_ENET_RXB
mdefine_line|#define SCCE_ENET_RXB&t;((ushort)0x0001)&t;/* A buffer was received */
multiline_comment|/* SCC Mode Register (PMSR) as used by Ethernet.&n;*/
DECL|macro|SCC_PMSR_HBC
mdefine_line|#define SCC_PMSR_HBC&t;((ushort)0x8000)&t;/* Enable heartbeat */
DECL|macro|SCC_PMSR_FC
mdefine_line|#define SCC_PMSR_FC&t;((ushort)0x4000)&t;/* Force collision */
DECL|macro|SCC_PMSR_RSH
mdefine_line|#define SCC_PMSR_RSH&t;((ushort)0x2000)&t;/* Receive short frames */
DECL|macro|SCC_PMSR_IAM
mdefine_line|#define SCC_PMSR_IAM&t;((ushort)0x1000)&t;/* Check individual hash */
DECL|macro|SCC_PMSR_ENCRC
mdefine_line|#define SCC_PMSR_ENCRC&t;((ushort)0x0800)&t;/* Ethernet CRC mode */
DECL|macro|SCC_PMSR_PRO
mdefine_line|#define SCC_PMSR_PRO&t;((ushort)0x0200)&t;/* Promiscuous mode */
DECL|macro|SCC_PMSR_BRO
mdefine_line|#define SCC_PMSR_BRO&t;((ushort)0x0100)&t;/* Catch broadcast pkts */
DECL|macro|SCC_PMSR_SBT
mdefine_line|#define SCC_PMSR_SBT&t;((ushort)0x0080)&t;/* Special backoff timer */
DECL|macro|SCC_PMSR_LPB
mdefine_line|#define SCC_PMSR_LPB&t;((ushort)0x0040)&t;/* Set Loopback mode */
DECL|macro|SCC_PMSR_SIP
mdefine_line|#define SCC_PMSR_SIP&t;((ushort)0x0020)&t;/* Sample Input Pins */
DECL|macro|SCC_PMSR_LCW
mdefine_line|#define SCC_PMSR_LCW&t;((ushort)0x0010)&t;/* Late collision window */
DECL|macro|SCC_PMSR_NIB22
mdefine_line|#define SCC_PMSR_NIB22&t;((ushort)0x000a)&t;/* Start frame search */
DECL|macro|SCC_PMSR_FDE
mdefine_line|#define SCC_PMSR_FDE&t;((ushort)0x0001)&t;/* Full duplex enable */
multiline_comment|/* Buffer descriptor control/status used by Ethernet receive.&n;*/
DECL|macro|BD_ENET_RX_EMPTY
mdefine_line|#define BD_ENET_RX_EMPTY&t;((ushort)0x8000)
DECL|macro|BD_ENET_RX_WRAP
mdefine_line|#define BD_ENET_RX_WRAP&t;&t;((ushort)0x2000)
DECL|macro|BD_ENET_RX_INTR
mdefine_line|#define BD_ENET_RX_INTR&t;&t;((ushort)0x1000)
DECL|macro|BD_ENET_RX_LAST
mdefine_line|#define BD_ENET_RX_LAST&t;&t;((ushort)0x0800)
DECL|macro|BD_ENET_RX_FIRST
mdefine_line|#define BD_ENET_RX_FIRST&t;((ushort)0x0400)
DECL|macro|BD_ENET_RX_MISS
mdefine_line|#define BD_ENET_RX_MISS&t;&t;((ushort)0x0100)
DECL|macro|BD_ENET_RX_LG
mdefine_line|#define BD_ENET_RX_LG&t;&t;((ushort)0x0020)
DECL|macro|BD_ENET_RX_NO
mdefine_line|#define BD_ENET_RX_NO&t;&t;((ushort)0x0010)
DECL|macro|BD_ENET_RX_SH
mdefine_line|#define BD_ENET_RX_SH&t;&t;((ushort)0x0008)
DECL|macro|BD_ENET_RX_CR
mdefine_line|#define BD_ENET_RX_CR&t;&t;((ushort)0x0004)
DECL|macro|BD_ENET_RX_OV
mdefine_line|#define BD_ENET_RX_OV&t;&t;((ushort)0x0002)
DECL|macro|BD_ENET_RX_CL
mdefine_line|#define BD_ENET_RX_CL&t;&t;((ushort)0x0001)
DECL|macro|BD_ENET_RX_STATS
mdefine_line|#define BD_ENET_RX_STATS&t;((ushort)0x013f)&t;/* All status bits */
multiline_comment|/* Buffer descriptor control/status used by Ethernet transmit.&n;*/
DECL|macro|BD_ENET_TX_READY
mdefine_line|#define BD_ENET_TX_READY&t;((ushort)0x8000)
DECL|macro|BD_ENET_TX_PAD
mdefine_line|#define BD_ENET_TX_PAD&t;&t;((ushort)0x4000)
DECL|macro|BD_ENET_TX_WRAP
mdefine_line|#define BD_ENET_TX_WRAP&t;&t;((ushort)0x2000)
DECL|macro|BD_ENET_TX_INTR
mdefine_line|#define BD_ENET_TX_INTR&t;&t;((ushort)0x1000)
DECL|macro|BD_ENET_TX_LAST
mdefine_line|#define BD_ENET_TX_LAST&t;&t;((ushort)0x0800)
DECL|macro|BD_ENET_TX_TC
mdefine_line|#define BD_ENET_TX_TC&t;&t;((ushort)0x0400)
DECL|macro|BD_ENET_TX_DEF
mdefine_line|#define BD_ENET_TX_DEF&t;&t;((ushort)0x0200)
DECL|macro|BD_ENET_TX_HB
mdefine_line|#define BD_ENET_TX_HB&t;&t;((ushort)0x0100)
DECL|macro|BD_ENET_TX_LC
mdefine_line|#define BD_ENET_TX_LC&t;&t;((ushort)0x0080)
DECL|macro|BD_ENET_TX_RL
mdefine_line|#define BD_ENET_TX_RL&t;&t;((ushort)0x0040)
DECL|macro|BD_ENET_TX_RCMASK
mdefine_line|#define BD_ENET_TX_RCMASK&t;((ushort)0x003c)
DECL|macro|BD_ENET_TX_UN
mdefine_line|#define BD_ENET_TX_UN&t;&t;((ushort)0x0002)
DECL|macro|BD_ENET_TX_CSL
mdefine_line|#define BD_ENET_TX_CSL&t;&t;((ushort)0x0001)
DECL|macro|BD_ENET_TX_STATS
mdefine_line|#define BD_ENET_TX_STATS&t;((ushort)0x03ff)&t;/* All status bits */
multiline_comment|/* SCC as UART&n;*/
DECL|struct|scc_uart
r_typedef
r_struct
id|scc_uart
(brace
DECL|member|scc_genscc
id|sccp_t
id|scc_genscc
suffix:semicolon
DECL|member|scc_res1
id|uint
id|scc_res1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|scc_res2
id|uint
id|scc_res2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|scc_maxidl
id|ushort
id|scc_maxidl
suffix:semicolon
multiline_comment|/* Maximum idle chars */
DECL|member|scc_idlc
id|ushort
id|scc_idlc
suffix:semicolon
multiline_comment|/* temp idle counter */
DECL|member|scc_brkcr
id|ushort
id|scc_brkcr
suffix:semicolon
multiline_comment|/* Break count register */
DECL|member|scc_parec
id|ushort
id|scc_parec
suffix:semicolon
multiline_comment|/* receive parity error counter */
DECL|member|scc_frmec
id|ushort
id|scc_frmec
suffix:semicolon
multiline_comment|/* receive framing error counter */
DECL|member|scc_nosec
id|ushort
id|scc_nosec
suffix:semicolon
multiline_comment|/* receive noise counter */
DECL|member|scc_brkec
id|ushort
id|scc_brkec
suffix:semicolon
multiline_comment|/* receive break condition counter */
DECL|member|scc_brkln
id|ushort
id|scc_brkln
suffix:semicolon
multiline_comment|/* last received break length */
DECL|member|scc_uaddr1
id|ushort
id|scc_uaddr1
suffix:semicolon
multiline_comment|/* UART address character 1 */
DECL|member|scc_uaddr2
id|ushort
id|scc_uaddr2
suffix:semicolon
multiline_comment|/* UART address character 2 */
DECL|member|scc_rtemp
id|ushort
id|scc_rtemp
suffix:semicolon
multiline_comment|/* Temp storage */
DECL|member|scc_toseq
id|ushort
id|scc_toseq
suffix:semicolon
multiline_comment|/* Transmit out of sequence char */
DECL|member|scc_char1
id|ushort
id|scc_char1
suffix:semicolon
multiline_comment|/* control character 1 */
DECL|member|scc_char2
id|ushort
id|scc_char2
suffix:semicolon
multiline_comment|/* control character 2 */
DECL|member|scc_char3
id|ushort
id|scc_char3
suffix:semicolon
multiline_comment|/* control character 3 */
DECL|member|scc_char4
id|ushort
id|scc_char4
suffix:semicolon
multiline_comment|/* control character 4 */
DECL|member|scc_char5
id|ushort
id|scc_char5
suffix:semicolon
multiline_comment|/* control character 5 */
DECL|member|scc_char6
id|ushort
id|scc_char6
suffix:semicolon
multiline_comment|/* control character 6 */
DECL|member|scc_char7
id|ushort
id|scc_char7
suffix:semicolon
multiline_comment|/* control character 7 */
DECL|member|scc_char8
id|ushort
id|scc_char8
suffix:semicolon
multiline_comment|/* control character 8 */
DECL|member|scc_rccm
id|ushort
id|scc_rccm
suffix:semicolon
multiline_comment|/* receive control character mask */
DECL|member|scc_rccr
id|ushort
id|scc_rccr
suffix:semicolon
multiline_comment|/* receive control character register */
DECL|member|scc_rlbc
id|ushort
id|scc_rlbc
suffix:semicolon
multiline_comment|/* receive last break character */
DECL|typedef|scc_uart_t
)brace
id|scc_uart_t
suffix:semicolon
multiline_comment|/* SCC Event and Mask registers when it is used as a UART.&n;*/
DECL|macro|UART_SCCM_GLR
mdefine_line|#define UART_SCCM_GLR&t;&t;((ushort)0x1000)
DECL|macro|UART_SCCM_GLT
mdefine_line|#define UART_SCCM_GLT&t;&t;((ushort)0x0800)
DECL|macro|UART_SCCM_AB
mdefine_line|#define UART_SCCM_AB&t;&t;((ushort)0x0200)
DECL|macro|UART_SCCM_IDL
mdefine_line|#define UART_SCCM_IDL&t;&t;((ushort)0x0100)
DECL|macro|UART_SCCM_GRA
mdefine_line|#define UART_SCCM_GRA&t;&t;((ushort)0x0080)
DECL|macro|UART_SCCM_BRKE
mdefine_line|#define UART_SCCM_BRKE&t;&t;((ushort)0x0040)
DECL|macro|UART_SCCM_BRKS
mdefine_line|#define UART_SCCM_BRKS&t;&t;((ushort)0x0020)
DECL|macro|UART_SCCM_CCR
mdefine_line|#define UART_SCCM_CCR&t;&t;((ushort)0x0008)
DECL|macro|UART_SCCM_BSY
mdefine_line|#define UART_SCCM_BSY&t;&t;((ushort)0x0004)
DECL|macro|UART_SCCM_TX
mdefine_line|#define UART_SCCM_TX&t;&t;((ushort)0x0002)
DECL|macro|UART_SCCM_RX
mdefine_line|#define UART_SCCM_RX&t;&t;((ushort)0x0001)
multiline_comment|/* The SCC PMSR when used as a UART.&n;*/
DECL|macro|SCU_PMSR_FLC
mdefine_line|#define SCU_PMSR_FLC&t;&t;((ushort)0x8000)
DECL|macro|SCU_PMSR_SL
mdefine_line|#define SCU_PMSR_SL&t;&t;((ushort)0x4000)
DECL|macro|SCU_PMSR_CL
mdefine_line|#define SCU_PMSR_CL&t;&t;((ushort)0x3000)
DECL|macro|SCU_PMSR_UM
mdefine_line|#define SCU_PMSR_UM&t;&t;((ushort)0x0c00)
DECL|macro|SCU_PMSR_FRZ
mdefine_line|#define SCU_PMSR_FRZ&t;&t;((ushort)0x0200)
DECL|macro|SCU_PMSR_RZS
mdefine_line|#define SCU_PMSR_RZS&t;&t;((ushort)0x0100)
DECL|macro|SCU_PMSR_SYN
mdefine_line|#define SCU_PMSR_SYN&t;&t;((ushort)0x0080)
DECL|macro|SCU_PMSR_DRT
mdefine_line|#define SCU_PMSR_DRT&t;&t;((ushort)0x0040)
DECL|macro|SCU_PMSR_PEN
mdefine_line|#define SCU_PMSR_PEN&t;&t;((ushort)0x0010)
DECL|macro|SCU_PMSR_RPM
mdefine_line|#define SCU_PMSR_RPM&t;&t;((ushort)0x000c)
DECL|macro|SCU_PMSR_REVP
mdefine_line|#define SCU_PMSR_REVP&t;&t;((ushort)0x0008)
DECL|macro|SCU_PMSR_TPM
mdefine_line|#define SCU_PMSR_TPM&t;&t;((ushort)0x0003)
DECL|macro|SCU_PMSR_TEVP
mdefine_line|#define SCU_PMSR_TEVP&t;&t;((ushort)0x0003)
multiline_comment|/* CPM Transparent mode SCC.&n; */
DECL|struct|scc_trans
r_typedef
r_struct
id|scc_trans
(brace
DECL|member|st_genscc
id|sccp_t
id|st_genscc
suffix:semicolon
DECL|member|st_cpres
id|uint
id|st_cpres
suffix:semicolon
multiline_comment|/* Preset CRC */
DECL|member|st_cmask
id|uint
id|st_cmask
suffix:semicolon
multiline_comment|/* Constant mask for CRC */
DECL|typedef|scc_trans_t
)brace
id|scc_trans_t
suffix:semicolon
DECL|macro|BD_SCC_TX_LAST
mdefine_line|#define BD_SCC_TX_LAST&t;&t;((ushort)0x0800)
multiline_comment|/* IIC parameter RAM.&n;*/
DECL|struct|iic
r_typedef
r_struct
id|iic
(brace
DECL|member|iic_rbase
id|ushort
id|iic_rbase
suffix:semicolon
multiline_comment|/* Rx Buffer descriptor base address */
DECL|member|iic_tbase
id|ushort
id|iic_tbase
suffix:semicolon
multiline_comment|/* Tx Buffer descriptor base address */
DECL|member|iic_rfcr
id|u_char
id|iic_rfcr
suffix:semicolon
multiline_comment|/* Rx function code */
DECL|member|iic_tfcr
id|u_char
id|iic_tfcr
suffix:semicolon
multiline_comment|/* Tx function code */
DECL|member|iic_mrblr
id|ushort
id|iic_mrblr
suffix:semicolon
multiline_comment|/* Max receive buffer length */
DECL|member|iic_rstate
id|uint
id|iic_rstate
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_rdp
id|uint
id|iic_rdp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_rbptr
id|ushort
id|iic_rbptr
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_rbc
id|ushort
id|iic_rbc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_rxtmp
id|uint
id|iic_rxtmp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_tstate
id|uint
id|iic_tstate
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_tdp
id|uint
id|iic_tdp
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_tbptr
id|ushort
id|iic_tbptr
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_tbc
id|ushort
id|iic_tbc
suffix:semicolon
multiline_comment|/* Internal */
DECL|member|iic_txtmp
id|uint
id|iic_txtmp
suffix:semicolon
multiline_comment|/* Internal */
DECL|typedef|iic_t
)brace
id|iic_t
suffix:semicolon
DECL|macro|BD_IIC_START
mdefine_line|#define BD_IIC_START&t;&t;((ushort)0x0400)
multiline_comment|/* CPM interrupts.  There are nearly 32 interrupts generated by CPM&n; * channels or devices.  All of these are presented to the PPC core&n; * as a single interrupt.  The CPM interrupt handler dispatches its&n; * own handlers, in a similar fashion to the PPC core handler.  We&n; * use the table as defined in the manuals (i.e. no special high&n; * priority and SCC1 == SCCa, etc...).&n; */
DECL|macro|CPMVEC_NR
mdefine_line|#define CPMVEC_NR&t;&t;32
DECL|macro|CPMVEC_PIO_PC15
mdefine_line|#define&t;CPMVEC_PIO_PC15&t;&t;((ushort)0x1f)
DECL|macro|CPMVEC_SCC1
mdefine_line|#define&t;CPMVEC_SCC1&t;&t;((ushort)0x1e)
DECL|macro|CPMVEC_SCC2
mdefine_line|#define&t;CPMVEC_SCC2&t;&t;((ushort)0x1d)
DECL|macro|CPMVEC_SCC3
mdefine_line|#define&t;CPMVEC_SCC3&t;&t;((ushort)0x1c)
DECL|macro|CPMVEC_SCC4
mdefine_line|#define&t;CPMVEC_SCC4&t;&t;((ushort)0x1b)
DECL|macro|CPMVEC_PIO_PC14
mdefine_line|#define&t;CPMVEC_PIO_PC14&t;&t;((ushort)0x1a)
DECL|macro|CPMVEC_TIMER1
mdefine_line|#define&t;CPMVEC_TIMER1&t;&t;((ushort)0x19)
DECL|macro|CPMVEC_PIO_PC13
mdefine_line|#define&t;CPMVEC_PIO_PC13&t;&t;((ushort)0x18)
DECL|macro|CPMVEC_PIO_PC12
mdefine_line|#define&t;CPMVEC_PIO_PC12&t;&t;((ushort)0x17)
DECL|macro|CPMVEC_SDMA_CB_ERR
mdefine_line|#define&t;CPMVEC_SDMA_CB_ERR&t;((ushort)0x16)
DECL|macro|CPMVEC_IDMA1
mdefine_line|#define CPMVEC_IDMA1&t;&t;((ushort)0x15)
DECL|macro|CPMVEC_IDMA2
mdefine_line|#define CPMVEC_IDMA2&t;&t;((ushort)0x14)
DECL|macro|CPMVEC_TIMER2
mdefine_line|#define CPMVEC_TIMER2&t;&t;((ushort)0x12)
DECL|macro|CPMVEC_RISCTIMER
mdefine_line|#define CPMVEC_RISCTIMER&t;((ushort)0x11)
DECL|macro|CPMVEC_I2C
mdefine_line|#define CPMVEC_I2C&t;&t;((ushort)0x10)
DECL|macro|CPMVEC_PIO_PC11
mdefine_line|#define&t;CPMVEC_PIO_PC11&t;&t;((ushort)0x0f)
DECL|macro|CPMVEC_PIO_PC10
mdefine_line|#define&t;CPMVEC_PIO_PC10&t;&t;((ushort)0x0e)
DECL|macro|CPMVEC_TIMER3
mdefine_line|#define CPMVEC_TIMER3&t;&t;((ushort)0x0c)
DECL|macro|CPMVEC_PIO_PC9
mdefine_line|#define&t;CPMVEC_PIO_PC9&t;&t;((ushort)0x0b)
DECL|macro|CPMVEC_PIO_PC8
mdefine_line|#define&t;CPMVEC_PIO_PC8&t;&t;((ushort)0x0a)
DECL|macro|CPMVEC_PIO_PC7
mdefine_line|#define&t;CPMVEC_PIO_PC7&t;&t;((ushort)0x09)
DECL|macro|CPMVEC_TIMER4
mdefine_line|#define CPMVEC_TIMER4&t;&t;((ushort)0x07)
DECL|macro|CPMVEC_PIO_PC6
mdefine_line|#define&t;CPMVEC_PIO_PC6&t;&t;((ushort)0x06)
DECL|macro|CPMVEC_SPI
mdefine_line|#define&t;CPMVEC_SPI&t;&t;((ushort)0x05)
DECL|macro|CPMVEC_SMC1
mdefine_line|#define&t;CPMVEC_SMC1&t;&t;((ushort)0x04)
DECL|macro|CPMVEC_SMC2
mdefine_line|#define&t;CPMVEC_SMC2&t;&t;((ushort)0x03)
DECL|macro|CPMVEC_PIO_PC5
mdefine_line|#define&t;CPMVEC_PIO_PC5&t;&t;((ushort)0x02)
DECL|macro|CPMVEC_PIO_PC4
mdefine_line|#define&t;CPMVEC_PIO_PC4&t;&t;((ushort)0x01)
DECL|macro|CPMVEC_ERROR
mdefine_line|#define&t;CPMVEC_ERROR&t;&t;((ushort)0x00)
r_extern
r_void
id|cpm_install_handler
c_func
(paren
r_int
id|vec
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
multiline_comment|/* CPM interrupt configuration vector.&n;*/
DECL|macro|CICR_SCD_SCC4
mdefine_line|#define&t;CICR_SCD_SCC4&t;&t;((uint)0x00c00000)&t;/* SCC4 @ SCCd */
DECL|macro|CICR_SCC_SCC3
mdefine_line|#define&t;CICR_SCC_SCC3&t;&t;((uint)0x00200000)&t;/* SCC3 @ SCCc */
DECL|macro|CICR_SCB_SCC2
mdefine_line|#define&t;CICR_SCB_SCC2&t;&t;((uint)0x00040000)&t;/* SCC2 @ SCCb */
DECL|macro|CICR_SCA_SCC1
mdefine_line|#define&t;CICR_SCA_SCC1&t;&t;((uint)0x00000000)&t;/* SCC1 @ SCCa */
DECL|macro|CICR_IRL_MASK
mdefine_line|#define CICR_IRL_MASK&t;&t;((uint)0x0000e000)&t;/* Core interrrupt */
DECL|macro|CICR_HP_MASK
mdefine_line|#define CICR_HP_MASK&t;&t;((uint)0x00001f00)&t;/* Hi-pri int. */
DECL|macro|CICR_IEN
mdefine_line|#define CICR_IEN&t;&t;((uint)0x00000080)&t;/* Int. enable */
DECL|macro|CICR_SPS
mdefine_line|#define CICR_SPS&t;&t;((uint)0x00000001)&t;/* SCC Spread */
macro_line|#endif /* __CPM_8XX__ */
eof
