multiline_comment|/***********************************&n; * $Id: m68360_regs.h,v 1.2 2002/10/26 15:03:55 gerg Exp $&n; ***********************************&n; *&n; ***************************************&n; * Definitions of the QUICC registers&n; ***************************************&n; */
macro_line|#ifndef __REGISTERS_H
DECL|macro|__REGISTERS_H
mdefine_line|#define __REGISTERS_H
DECL|macro|CLEAR_BIT
mdefine_line|#define CLEAR_BIT(x, bit)  x =bit 
multiline_comment|/*****************************************************************&n;        Command Register&n;*****************************************************************/
multiline_comment|/* bit fields within command register */
DECL|macro|SOFTWARE_RESET
mdefine_line|#define SOFTWARE_RESET  0x8000
DECL|macro|CMD_OPCODE
mdefine_line|#define CMD_OPCODE      0x0f00
DECL|macro|CMD_CHANNEL
mdefine_line|#define CMD_CHANNEL     0x00f0
DECL|macro|CMD_FLAG
mdefine_line|#define CMD_FLAG        0x0001
multiline_comment|/* general command opcodes */
DECL|macro|INIT_RXTX_PARAMS
mdefine_line|#define INIT_RXTX_PARAMS        0x0000
DECL|macro|INIT_RX_PARAMS
mdefine_line|#define INIT_RX_PARAMS          0x0100
DECL|macro|INIT_TX_PARAMS
mdefine_line|#define INIT_TX_PARAMS          0x0200
DECL|macro|ENTER_HUNT_MODE
mdefine_line|#define ENTER_HUNT_MODE         0x0300
DECL|macro|STOP_TX
mdefine_line|#define STOP_TX                 0x0400
DECL|macro|GR_STOP_TX
mdefine_line|#define GR_STOP_TX              0x0500
DECL|macro|RESTART_TX
mdefine_line|#define RESTART_TX              0x0600
DECL|macro|CLOSE_RX_BD
mdefine_line|#define CLOSE_RX_BD             0x0700
DECL|macro|SET_ENET_GROUP
mdefine_line|#define SET_ENET_GROUP          0x0800
DECL|macro|RESET_ENET_GROUP
mdefine_line|#define RESET_ENET_GROUP        0x0900
multiline_comment|/* quicc32 CP commands */
DECL|macro|STOP_TX_32
mdefine_line|#define STOP_TX_32&t;&t;0x0e00&t;/*add chan# bits 2-6 */
DECL|macro|ENTER_HUNT_MODE_32
mdefine_line|#define ENTER_HUNT_MODE_32&t;0x1e00
multiline_comment|/* quicc32 mask/event SCC register */
DECL|macro|GOV
mdefine_line|#define GOV&t;0x01
DECL|macro|GUN
mdefine_line|#define GUN&t;0x02
DECL|macro|GINT
mdefine_line|#define GINT&t;0x04
DECL|macro|IQOV
mdefine_line|#define IQOV&t;0x08
multiline_comment|/* Timer commands */
DECL|macro|SET_TIMER
mdefine_line|#define SET_TIMER               0x0800
multiline_comment|/* Multi channel Interrupt structure */
DECL|macro|INTR_VALID
mdefine_line|#define INTR_VALID&t;0x8000&t;/* Valid interrupt entry */
DECL|macro|INTR_WRAP
mdefine_line|#define INTR_WRAP&t;0x4000&t;/* Wrap bit in the interrupt entry table */
DECL|macro|INTR_CH_NU
mdefine_line|#define INTR_CH_NU&t;0x07c0&t;/* Channel Num in interrupt table */
DECL|macro|INTR_MASK_BITS
mdefine_line|#define INTR_MASK_BITS&t;0x383f
multiline_comment|/*&n; * General SCC mode register (GSMR)&n; */
DECL|macro|MODE_HDLC
mdefine_line|#define MODE_HDLC               0x0
DECL|macro|MODE_APPLE_TALK
mdefine_line|#define MODE_APPLE_TALK         0x2
DECL|macro|MODE_SS7
mdefine_line|#define MODE_SS7                0x3
DECL|macro|MODE_UART
mdefine_line|#define MODE_UART               0x4
DECL|macro|MODE_PROFIBUS
mdefine_line|#define MODE_PROFIBUS           0x5
DECL|macro|MODE_ASYNC_HDLC
mdefine_line|#define MODE_ASYNC_HDLC         0x6
DECL|macro|MODE_V14
mdefine_line|#define MODE_V14                0x7
DECL|macro|MODE_BISYNC
mdefine_line|#define MODE_BISYNC             0x8
DECL|macro|MODE_DDCMP
mdefine_line|#define MODE_DDCMP              0x9
DECL|macro|MODE_MULTI_CHANNEL
mdefine_line|#define MODE_MULTI_CHANNEL      0xa
DECL|macro|MODE_ETHERNET
mdefine_line|#define MODE_ETHERNET           0xc
DECL|macro|DIAG_NORMAL
mdefine_line|#define DIAG_NORMAL             0x0
DECL|macro|DIAG_LOCAL_LPB
mdefine_line|#define DIAG_LOCAL_LPB          0x1
DECL|macro|DIAG_AUTO_ECHO
mdefine_line|#define DIAG_AUTO_ECHO          0x2
DECL|macro|DIAG_LBP_ECHO
mdefine_line|#define DIAG_LBP_ECHO           0x3
multiline_comment|/* For RENC and TENC fields in GSMR */
DECL|macro|ENC_NRZ
mdefine_line|#define ENC_NRZ                 0x0
DECL|macro|ENC_NRZI
mdefine_line|#define ENC_NRZI                0x1
DECL|macro|ENC_FM0
mdefine_line|#define ENC_FM0                 0x2
DECL|macro|ENC_MANCH
mdefine_line|#define ENC_MANCH               0x4
DECL|macro|ENC_DIFF_MANC
mdefine_line|#define ENC_DIFF_MANC           0x6
multiline_comment|/* For TDCR and RDCR fields in GSMR */
DECL|macro|CLOCK_RATE_1
mdefine_line|#define CLOCK_RATE_1            0x0
DECL|macro|CLOCK_RATE_8
mdefine_line|#define CLOCK_RATE_8            0x1
DECL|macro|CLOCK_RATE_16
mdefine_line|#define CLOCK_RATE_16           0x2
DECL|macro|CLOCK_RATE_32
mdefine_line|#define CLOCK_RATE_32           0x3
DECL|macro|TPP_00
mdefine_line|#define TPP_00                  0x0
DECL|macro|TPP_10
mdefine_line|#define TPP_10                  0x1
DECL|macro|TPP_01
mdefine_line|#define TPP_01                  0x2
DECL|macro|TPP_11
mdefine_line|#define TPP_11                  0x3
DECL|macro|TPL_NO
mdefine_line|#define TPL_NO                  0x0
DECL|macro|TPL_8
mdefine_line|#define TPL_8                   0x1
DECL|macro|TPL_16
mdefine_line|#define TPL_16                  0x2
DECL|macro|TPL_32
mdefine_line|#define TPL_32                  0x3
DECL|macro|TPL_48
mdefine_line|#define TPL_48                  0x4
DECL|macro|TPL_64
mdefine_line|#define TPL_64                  0x5
DECL|macro|TPL_128
mdefine_line|#define TPL_128                 0x6
DECL|macro|TSNC_INFINITE
mdefine_line|#define TSNC_INFINITE           0x0
DECL|macro|TSNC_14_65
mdefine_line|#define TSNC_14_65              0x1
DECL|macro|TSNC_4_15
mdefine_line|#define TSNC_4_15               0x2
DECL|macro|TSNC_3_1
mdefine_line|#define TSNC_3_1                0x3
DECL|macro|EDGE_BOTH
mdefine_line|#define EDGE_BOTH               0x0
DECL|macro|EDGE_POS
mdefine_line|#define EDGE_POS                0x1
DECL|macro|EDGE_NEG
mdefine_line|#define EDGE_NEG                0x2
DECL|macro|EDGE_NO
mdefine_line|#define EDGE_NO                 0x3
DECL|macro|SYNL_NO
mdefine_line|#define SYNL_NO                 0x0
DECL|macro|SYNL_4
mdefine_line|#define SYNL_4                  0x1
DECL|macro|SYNL_8
mdefine_line|#define SYNL_8                  0x2
DECL|macro|SYNL_16
mdefine_line|#define SYNL_16                 0x3
DECL|macro|TCRC_CCITT16
mdefine_line|#define TCRC_CCITT16            0x0
DECL|macro|TCRC_CRC16
mdefine_line|#define TCRC_CRC16              0x1
DECL|macro|TCRC_CCITT32
mdefine_line|#define TCRC_CCITT32            0x2
multiline_comment|/*****************************************************************&n;        TODR (Transmit on demand) Register&n;*****************************************************************/
DECL|macro|TODR_TOD
mdefine_line|#define TODR_TOD        0x8000  /* Transmit on demand */
multiline_comment|/*****************************************************************&n;        CICR register settings&n;*****************************************************************/
multiline_comment|/* note that relative irq priorities of the SCCs can be reordered&n; * if desired - see p. 7-377 of the MC68360UM */
DECL|macro|CICR_SCA_SCC1
mdefine_line|#define CICR_SCA_SCC1           ((uint)0x00000000)      /* SCC1 @ SCCa */
DECL|macro|CICR_SCB_SCC2
mdefine_line|#define CICR_SCB_SCC2           ((uint)0x00040000)      /* SCC2 @ SCCb */
DECL|macro|CICR_SCC_SCC3
mdefine_line|#define CICR_SCC_SCC3           ((uint)0x00200000)      /* SCC3 @ SCCc */
DECL|macro|CICR_SCD_SCC4
mdefine_line|#define CICR_SCD_SCC4           ((uint)0x00c00000)      /* SCC4 @ SCCd */
DECL|macro|CICR_IRL_MASK
mdefine_line|#define CICR_IRL_MASK           ((uint)0x0000e000)      /* Core interrrupt */
DECL|macro|CICR_HP_MASK
mdefine_line|#define CICR_HP_MASK            ((uint)0x00001f00)      /* Hi-pri int. */
DECL|macro|CICR_VBA_MASK
mdefine_line|#define CICR_VBA_MASK           ((uint)0x000000e0)      /* Vector Base Address */
DECL|macro|CICR_SPS
mdefine_line|#define CICR_SPS                ((uint)0x00000001)      /* SCC Spread */
multiline_comment|/*****************************************************************&n;       Interrupt bits for CIPR and CIMR (MC68360UM p. 7-379)&n;*****************************************************************/
DECL|macro|INTR_PIO_PC0
mdefine_line|#define INTR_PIO_PC0    0x80000000      /* parallel I/O C bit 0 */
DECL|macro|INTR_SCC1
mdefine_line|#define INTR_SCC1       0x40000000      /* SCC port 1 */
DECL|macro|INTR_SCC2
mdefine_line|#define INTR_SCC2       0x20000000      /* SCC port 2 */
DECL|macro|INTR_SCC3
mdefine_line|#define INTR_SCC3       0x10000000      /* SCC port 3 */
DECL|macro|INTR_SCC4
mdefine_line|#define INTR_SCC4       0x08000000      /* SCC port 4 */
DECL|macro|INTR_PIO_PC1
mdefine_line|#define INTR_PIO_PC1    0x04000000      /* parallel i/o C bit 1 */
DECL|macro|INTR_TIMER1
mdefine_line|#define INTR_TIMER1     0x02000000      /* timer 1 */
DECL|macro|INTR_PIO_PC2
mdefine_line|#define INTR_PIO_PC2    0x01000000      /* parallel i/o C bit 2 */
DECL|macro|INTR_PIO_PC3
mdefine_line|#define INTR_PIO_PC3    0x00800000      /* parallel i/o C bit 3 */
DECL|macro|INTR_SDMA_BERR
mdefine_line|#define INTR_SDMA_BERR  0x00400000      /* SDMA channel bus error */
DECL|macro|INTR_DMA1
mdefine_line|#define INTR_DMA1       0x00200000      /* idma 1 */
DECL|macro|INTR_DMA2
mdefine_line|#define INTR_DMA2       0x00100000      /* idma 2 */
DECL|macro|INTR_TIMER2
mdefine_line|#define INTR_TIMER2     0x00040000      /* timer 2 */
DECL|macro|INTR_CP_TIMER
mdefine_line|#define INTR_CP_TIMER   0x00020000      /* CP timer */
DECL|macro|INTR_PIP_STATUS
mdefine_line|#define INTR_PIP_STATUS 0x00010000      /* PIP status */
DECL|macro|INTR_PIO_PC4
mdefine_line|#define INTR_PIO_PC4    0x00008000      /* parallel i/o C bit 4 */
DECL|macro|INTR_PIO_PC5
mdefine_line|#define INTR_PIO_PC5    0x00004000      /* parallel i/o C bit 5 */
DECL|macro|INTR_TIMER3
mdefine_line|#define INTR_TIMER3     0x00001000      /* timer 3 */
DECL|macro|INTR_PIO_PC6
mdefine_line|#define INTR_PIO_PC6    0x00000800      /* parallel i/o C bit 6 */
DECL|macro|INTR_PIO_PC7
mdefine_line|#define INTR_PIO_PC7    0x00000400      /* parallel i/o C bit 7 */
DECL|macro|INTR_PIO_PC8
mdefine_line|#define INTR_PIO_PC8    0x00000200      /* parallel i/o C bit 8 */
DECL|macro|INTR_TIMER4
mdefine_line|#define INTR_TIMER4     0x00000080      /* timer 4 */
DECL|macro|INTR_PIO_PC9
mdefine_line|#define INTR_PIO_PC9    0x00000040      /* parallel i/o C bit 9 */
DECL|macro|INTR_SCP
mdefine_line|#define INTR_SCP        0x00000020      /* SCP */
DECL|macro|INTR_SMC1
mdefine_line|#define INTR_SMC1       0x00000010      /* SMC 1 */
DECL|macro|INTR_SMC2
mdefine_line|#define INTR_SMC2       0x00000008      /* SMC 2 */
DECL|macro|INTR_PIO_PC10
mdefine_line|#define INTR_PIO_PC10   0x00000004      /* parallel i/o C bit 10 */
DECL|macro|INTR_PIO_PC11
mdefine_line|#define INTR_PIO_PC11   0x00000002      /* parallel i/o C bit 11 */
DECL|macro|INTR_ERR
mdefine_line|#define INTR_ERR        0x00000001      /* error */
multiline_comment|/*****************************************************************&n;        CPM Interrupt vector encodings (MC68360UM p. 7-376)&n;*****************************************************************/
DECL|macro|CPMVEC_NR
mdefine_line|#define CPMVEC_NR&t;&t;32
DECL|macro|CPMVEC_PIO_PC0
mdefine_line|#define CPMVEC_PIO_PC0&t;&t;0x1f
DECL|macro|CPMVEC_SCC1
mdefine_line|#define CPMVEC_SCC1&t;&t;0x1e
DECL|macro|CPMVEC_SCC2
mdefine_line|#define CPMVEC_SCC2&t;&t;0x1d
DECL|macro|CPMVEC_SCC3
mdefine_line|#define CPMVEC_SCC3&t;&t;0x1c
DECL|macro|CPMVEC_SCC4
mdefine_line|#define CPMVEC_SCC4&t;&t;0x1b
DECL|macro|CPMVEC_PIO_PC1
mdefine_line|#define CPMVEC_PIO_PC1&t;&t;0x1a
DECL|macro|CPMVEC_TIMER1
mdefine_line|#define CPMVEC_TIMER1&t;&t;0x19
DECL|macro|CPMVEC_PIO_PC2
mdefine_line|#define CPMVEC_PIO_PC2&t;&t;0x18
DECL|macro|CPMVEC_PIO_PC3
mdefine_line|#define CPMVEC_PIO_PC3&t;&t;0x17
DECL|macro|CPMVEC_SDMA_CB_ERR
mdefine_line|#define CPMVEC_SDMA_CB_ERR&t;0x16
DECL|macro|CPMVEC_IDMA1
mdefine_line|#define CPMVEC_IDMA1&t;&t;0x15
DECL|macro|CPMVEC_IDMA2
mdefine_line|#define CPMVEC_IDMA2&t;&t;0x14
DECL|macro|CPMVEC_RESERVED3
mdefine_line|#define CPMVEC_RESERVED3&t;0x13
DECL|macro|CPMVEC_TIMER2
mdefine_line|#define CPMVEC_TIMER2&t;&t;0x12
DECL|macro|CPMVEC_RISCTIMER
mdefine_line|#define CPMVEC_RISCTIMER&t;0x11
DECL|macro|CPMVEC_RESERVED2
mdefine_line|#define CPMVEC_RESERVED2&t;0x10
DECL|macro|CPMVEC_PIO_PC4
mdefine_line|#define CPMVEC_PIO_PC4&t;&t;0x0f
DECL|macro|CPMVEC_PIO_PC5
mdefine_line|#define CPMVEC_PIO_PC5&t;&t;0x0e
DECL|macro|CPMVEC_TIMER3
mdefine_line|#define CPMVEC_TIMER3&t;&t;0x0c
DECL|macro|CPMVEC_PIO_PC6
mdefine_line|#define CPMVEC_PIO_PC6&t;&t;0x0b
DECL|macro|CPMVEC_PIO_PC7
mdefine_line|#define CPMVEC_PIO_PC7&t;&t;0x0a
DECL|macro|CPMVEC_PIO_PC8
mdefine_line|#define CPMVEC_PIO_PC8&t;&t;0x09
DECL|macro|CPMVEC_RESERVED1
mdefine_line|#define CPMVEC_RESERVED1&t;0x08
DECL|macro|CPMVEC_TIMER4
mdefine_line|#define CPMVEC_TIMER4&t;&t;0x07
DECL|macro|CPMVEC_PIO_PC9
mdefine_line|#define CPMVEC_PIO_PC9&t;&t;0x06
DECL|macro|CPMVEC_SPI
mdefine_line|#define CPMVEC_SPI&t;&t;0x05
DECL|macro|CPMVEC_SMC1
mdefine_line|#define CPMVEC_SMC1&t;&t;0x04
DECL|macro|CPMVEC_SMC2
mdefine_line|#define CPMVEC_SMC2&t;&t;0x03
DECL|macro|CPMVEC_PIO_PC10
mdefine_line|#define CPMVEC_PIO_PC10&t;&t;0x02
DECL|macro|CPMVEC_PIO_PC11
mdefine_line|#define CPMVEC_PIO_PC11&t;&t;0x01
DECL|macro|CPMVEC_ERROR
mdefine_line|#define CPMVEC_ERROR&t;&t;0x00
multiline_comment|/* #define CPMVEC_PIO_PC0&t;&t;((ushort)0x1f) */
multiline_comment|/* #define CPMVEC_SCC1&t;&t;((ushort)0x1e) */
multiline_comment|/* #define CPMVEC_SCC2&t;&t;((ushort)0x1d) */
multiline_comment|/* #define CPMVEC_SCC3&t;&t;((ushort)0x1c) */
multiline_comment|/* #define CPMVEC_SCC4&t;&t;((ushort)0x1b) */
multiline_comment|/* #define CPMVEC_PIO_PC1&t;&t;((ushort)0x1a) */
multiline_comment|/* #define CPMVEC_TIMER1&t;&t;((ushort)0x19) */
multiline_comment|/* #define CPMVEC_PIO_PC2&t;&t;((ushort)0x18) */
multiline_comment|/* #define CPMVEC_PIO_PC3&t;&t;((ushort)0x17) */
multiline_comment|/* #define CPMVEC_SDMA_CB_ERR&t;((ushort)0x16) */
multiline_comment|/* #define CPMVEC_IDMA1&t;&t;((ushort)0x15) */
multiline_comment|/* #define CPMVEC_IDMA2&t;&t;((ushort)0x14) */
multiline_comment|/* #define CPMVEC_RESERVED3&t;((ushort)0x13) */
multiline_comment|/* #define CPMVEC_TIMER2&t;&t;((ushort)0x12) */
multiline_comment|/* #define CPMVEC_RISCTIMER&t;((ushort)0x11) */
multiline_comment|/* #define CPMVEC_RESERVED2&t;((ushort)0x10) */
multiline_comment|/* #define CPMVEC_PIO_PC4&t;&t;((ushort)0x0f) */
multiline_comment|/* #define CPMVEC_PIO_PC5&t;&t;((ushort)0x0e) */
multiline_comment|/* #define CPMVEC_TIMER3&t;&t;((ushort)0x0c) */
multiline_comment|/* #define CPMVEC_PIO_PC6&t;&t;((ushort)0x0b) */
multiline_comment|/* #define CPMVEC_PIO_PC7&t;&t;((ushort)0x0a) */
multiline_comment|/* #define CPMVEC_PIO_PC8&t;&t;((ushort)0x09) */
multiline_comment|/* #define CPMVEC_RESERVED1&t;((ushort)0x08) */
multiline_comment|/* #define CPMVEC_TIMER4&t;&t;((ushort)0x07) */
multiline_comment|/* #define CPMVEC_PIO_PC9&t;&t;((ushort)0x06) */
multiline_comment|/* #define CPMVEC_SPI&t;&t;((ushort)0x05) */
multiline_comment|/* #define CPMVEC_SMC1&t;&t;((ushort)0x04) */
multiline_comment|/* #define CPMVEC_SMC2&t;&t;((ushort)0x03) */
multiline_comment|/* #define CPMVEC_PIO_PC10&t;&t;((ushort)0x02) */
multiline_comment|/* #define CPMVEC_PIO_PC11&t;&t;((ushort)0x01) */
multiline_comment|/* #define CPMVEC_ERROR&t;&t;((ushort)0x00) */
multiline_comment|/*****************************************************************&n; *        PIO control registers&n; *****************************************************************/
multiline_comment|/* Port A - See 360UM p. 7-358&n; * &n; *  Note that most of these pins have alternate functions&n; */
multiline_comment|/* The macros are nice, but there are all sorts of references to 1-indexed&n; * facilities on the 68360... */
multiline_comment|/* #define PA_RXD(n)&t;((ushort)(0x01&lt;&lt;(2*n))) */
multiline_comment|/* #define PA_TXD(n)&t;((ushort)(0x02&lt;&lt;(2*n))) */
DECL|macro|PA_RXD1
mdefine_line|#define PA_RXD1&t;&t;((ushort)0x0001)
DECL|macro|PA_TXD1
mdefine_line|#define PA_TXD1&t;&t;((ushort)0x0002)
DECL|macro|PA_RXD2
mdefine_line|#define PA_RXD2&t;&t;((ushort)0x0004)
DECL|macro|PA_TXD2
mdefine_line|#define PA_TXD2&t;&t;((ushort)0x0008)
DECL|macro|PA_RXD3
mdefine_line|#define PA_RXD3&t;&t;((ushort)0x0010)
DECL|macro|PA_TXD3
mdefine_line|#define PA_TXD3&t;&t;((ushort)0x0020)
DECL|macro|PA_RXD4
mdefine_line|#define PA_RXD4&t;&t;((ushort)0x0040)
DECL|macro|PA_TXD4
mdefine_line|#define PA_TXD4&t;&t;((ushort)0x0080)
DECL|macro|PA_CLK1
mdefine_line|#define PA_CLK1&t;&t;((ushort)0x0100)
DECL|macro|PA_CLK2
mdefine_line|#define PA_CLK2&t;&t;((ushort)0x0200)
DECL|macro|PA_CLK3
mdefine_line|#define PA_CLK3&t;&t;((ushort)0x0400)
DECL|macro|PA_CLK4
mdefine_line|#define PA_CLK4&t;&t;((ushort)0x0800)
DECL|macro|PA_CLK5
mdefine_line|#define PA_CLK5&t;&t;((ushort)0x1000)
DECL|macro|PA_CLK6
mdefine_line|#define PA_CLK6&t;&t;((ushort)0x2000)
DECL|macro|PA_CLK7
mdefine_line|#define PA_CLK7&t;&t;((ushort)0x4000)
DECL|macro|PA_CLK8
mdefine_line|#define PA_CLK8&t;&t;((ushort)0x8000)
multiline_comment|/* Port B - See 360UM p. 7-362&n; */
multiline_comment|/* Port C - See 360UM p. 7-365&n; */
DECL|macro|PC_RTS1
mdefine_line|#define PC_RTS1&t;&t;((ushort)0x0001)
DECL|macro|PC_RTS2
mdefine_line|#define PC_RTS2&t;&t;((ushort)0x0002)
DECL|macro|PC__RTS3
mdefine_line|#define PC__RTS3&t;((ushort)0x0004) /* !RTS3 */
DECL|macro|PC__RTS4
mdefine_line|#define PC__RTS4&t;((ushort)0x0008) /* !RTS4 */
DECL|macro|PC_CTS1
mdefine_line|#define PC_CTS1&t;&t;((ushort)0x0010)
DECL|macro|PC_CD1
mdefine_line|#define PC_CD1&t;&t;((ushort)0x0020)
DECL|macro|PC_CTS2
mdefine_line|#define PC_CTS2&t;&t;((ushort)0x0040)
DECL|macro|PC_CD2
mdefine_line|#define PC_CD2&t;&t;((ushort)0x0080)
DECL|macro|PC_CTS3
mdefine_line|#define PC_CTS3&t;&t;((ushort)0x0100)
DECL|macro|PC_CD3
mdefine_line|#define PC_CD3&t;&t;((ushort)0x0200)
DECL|macro|PC_CTS4
mdefine_line|#define PC_CTS4&t;&t;((ushort)0x0400)
DECL|macro|PC_CD4
mdefine_line|#define PC_CD4&t;&t;((ushort)0x0800)
multiline_comment|/*****************************************************************&n;        chip select option register&n;*****************************************************************/
DECL|macro|DTACK
mdefine_line|#define DTACK           0xe000
DECL|macro|ADR_MASK
mdefine_line|#define ADR_MASK        0x1ffc
DECL|macro|RDWR_MASK
mdefine_line|#define RDWR_MASK       0x0002
DECL|macro|FC_MASK
mdefine_line|#define FC_MASK         0x0001
multiline_comment|/*****************************************************************&n;        tbase and rbase registers&n;*****************************************************************/
DECL|macro|TBD_ADDR
mdefine_line|#define TBD_ADDR(quicc,pram) ((struct quicc_bd *) &bslash;&n;    (quicc-&gt;ch_or_u.u.udata_bd_ucode + pram-&gt;tbase))
DECL|macro|RBD_ADDR
mdefine_line|#define RBD_ADDR(quicc,pram) ((struct quicc_bd *) &bslash;&n;    (quicc-&gt;ch_or_u.u.udata_bd_ucode + pram-&gt;rbase))
DECL|macro|TBD_CUR_ADDR
mdefine_line|#define TBD_CUR_ADDR(quicc,pram) ((struct quicc_bd *) &bslash;&n;    (quicc-&gt;ch_or_u.u.udata_bd_ucode + pram-&gt;tbptr))
DECL|macro|RBD_CUR_ADDR
mdefine_line|#define RBD_CUR_ADDR(quicc,pram) ((struct quicc_bd *) &bslash;&n;    (quicc-&gt;ch_or_u.u.udata_bd_ucode + pram-&gt;rbptr))
DECL|macro|TBD_SET_CUR_ADDR
mdefine_line|#define TBD_SET_CUR_ADDR(bd,quicc,pram) pram-&gt;tbptr = &bslash;&n;    ((unsigned short)((char *)(bd) - (char *)(quicc-&gt;ch_or_u.u.udata_bd_ucode)))
DECL|macro|RBD_SET_CUR_ADDR
mdefine_line|#define RBD_SET_CUR_ADDR(bd,quicc,pram) pram-&gt;rbptr = &bslash;&n;    ((unsigned short)((char *)(bd) - (char *)(quicc-&gt;ch_or_u.u.udata_bd_ucode)))
DECL|macro|INCREASE_TBD
mdefine_line|#define INCREASE_TBD(bd,quicc,pram) {  &bslash;&n;    if((bd)-&gt;status &amp; T_W)             &bslash;&n;        (bd) = TBD_ADDR(quicc,pram);   &bslash;&n;    else                               &bslash;&n;        (bd)++;                        &bslash;&n;}
DECL|macro|DECREASE_TBD
mdefine_line|#define DECREASE_TBD(bd,quicc,pram) {  &bslash;&n;    if ((bd) == TBD_ADDR(quicc, pram)) &bslash;&n;        while (!((bd)-&gt;status &amp; T_W))  &bslash;&n;            (bd)++;                    &bslash;&n;    else                               &bslash;&n;        (bd)--;                        &bslash;&n;}
DECL|macro|INCREASE_RBD
mdefine_line|#define INCREASE_RBD(bd,quicc,pram) {  &bslash;&n;    if((bd)-&gt;status &amp; R_W)             &bslash;&n;        (bd) = RBD_ADDR(quicc,pram);   &bslash;&n;    else                               &bslash;&n;        (bd)++;                        &bslash;&n;}
DECL|macro|DECREASE_RBD
mdefine_line|#define DECREASE_RBD(bd,quicc,pram) {  &bslash;&n;    if ((bd) == RBD_ADDR(quicc, pram)) &bslash;&n;        while (!((bd)-&gt;status &amp; T_W))  &bslash;&n;            (bd)++;                    &bslash;&n;    else                               &bslash;&n;        (bd)--;                        &bslash;&n;}
multiline_comment|/*****************************************************************&n;        Macros for Multi channel&n;*****************************************************************/
DECL|macro|QMC_BASE
mdefine_line|#define QMC_BASE(quicc,page) (struct global_multi_pram *)(&amp;quicc-&gt;pram[page])
DECL|macro|MCBASE
mdefine_line|#define MCBASE(quicc,page) (unsigned long)(quicc-&gt;pram[page].m.mcbase)
DECL|macro|CHANNEL_PRAM_BASE
mdefine_line|#define CHANNEL_PRAM_BASE(quicc,channel) ((struct quicc32_pram *) &bslash;&n;&t;&t;(&amp;(quicc-&gt;ch_or_u.ch_pram_tbl[channel])))
DECL|macro|TBD_32_ADDR
mdefine_line|#define TBD_32_ADDR(quicc,page,channel) ((struct quicc_bd *) &bslash;&n;    (MCBASE(quicc,page) + (CHANNEL_PRAM_BASE(quicc,channel)-&gt;tbase)))
DECL|macro|RBD_32_ADDR
mdefine_line|#define RBD_32_ADDR(quicc,page,channel) ((struct quicc_bd *) &bslash;&n;    (MCBASE(quicc,page) + (CHANNEL_PRAM_BASE(quicc,channel)-&gt;rbase)))
DECL|macro|TBD_32_CUR_ADDR
mdefine_line|#define TBD_32_CUR_ADDR(quicc,page,channel) ((struct quicc_bd *) &bslash;&n;    (MCBASE(quicc,page) + (CHANNEL_PRAM_BASE(quicc,channel)-&gt;tbptr)))
DECL|macro|RBD_32_CUR_ADDR
mdefine_line|#define RBD_32_CUR_ADDR(quicc,page,channel) ((struct quicc_bd *) &bslash;&n;    (MCBASE(quicc,page) + (CHANNEL_PRAM_BASE(quicc,channel)-&gt;rbptr)))
DECL|macro|TBD_32_SET_CUR_ADDR
mdefine_line|#define TBD_32_SET_CUR_ADDR(bd,quicc,page,channel) &bslash;&n;     CHANNEL_PRAM_BASE(quicc,channel)-&gt;tbptr = &bslash;&n;    ((unsigned short)((char *)(bd) - (char *)(MCBASE(quicc,page))))
DECL|macro|RBD_32_SET_CUR_ADDR
mdefine_line|#define RBD_32_SET_CUR_ADDR(bd,quicc,page,channel) &bslash;&n;     CHANNEL_PRAM_BASE(quicc,channel)-&gt;rbptr = &bslash;&n;    ((unsigned short)((char *)(bd) - (char *)(MCBASE(quicc,page))))
DECL|macro|INCREASE_TBD_32
mdefine_line|#define INCREASE_TBD_32(bd,quicc,page,channel) {  &bslash;&n;    if((bd)-&gt;status &amp; T_W)                        &bslash;&n;        (bd) = TBD_32_ADDR(quicc,page,channel);   &bslash;&n;    else                                          &bslash;&n;        (bd)++;                                   &bslash;&n;}
DECL|macro|DECREASE_TBD_32
mdefine_line|#define DECREASE_TBD_32(bd,quicc,page,channel) {  &bslash;&n;    if ((bd) == TBD_32_ADDR(quicc, page,channel)) &bslash;&n;        while (!((bd)-&gt;status &amp; T_W))             &bslash;&n;            (bd)++;                               &bslash;&n;    else                                          &bslash;&n;        (bd)--;                                   &bslash;&n;}
DECL|macro|INCREASE_RBD_32
mdefine_line|#define INCREASE_RBD_32(bd,quicc,page,channel) {  &bslash;&n;    if((bd)-&gt;status &amp; R_W)                        &bslash;&n;        (bd) = RBD_32_ADDR(quicc,page,channel);   &bslash;&n;    else                                          &bslash;&n;        (bd)++;                                   &bslash;&n;}
DECL|macro|DECREASE_RBD_32
mdefine_line|#define DECREASE_RBD_32(bd,quicc,page,channel) {  &bslash;&n;    if ((bd) == RBD_32_ADDR(quicc, page,channel)) &bslash;&n;        while (!((bd)-&gt;status &amp; T_W))             &bslash;&n;            (bd)++;                               &bslash;&n;    else                                          &bslash;&n;        (bd)--;                                   &bslash;&n;}
macro_line|#endif
eof
