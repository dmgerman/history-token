multiline_comment|/* $Id: amd7930.h,v 1.8 1999/09/21 14:37:10 davem Exp $&n; * drivers/sbus/audio/amd7930.h&n; *&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; *&n; * Definitions for the AMD79C30 Digital Subscriber Controller which is&n; * used as an audio chip in sun4c architecture machines. The&n; * information in this file is based on Advanced Micro Devices&n; * Publication 09893, Rev G, Amendment /0, Final (a.k.a. the data&n; * sheet).&n; */
macro_line|#ifndef _AMD7930_H_
DECL|macro|_AMD7930_H_
mdefine_line|#define _AMD7930_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
multiline_comment|/* Register interface presented to the CPU by the amd7930. */
DECL|macro|CR
mdefine_line|#define CR&t;0x00UL&t;&t;/* Command Register (W) */
DECL|macro|IR
mdefine_line|#define IR&t;CR&t;&t;/* Interrupt Register (R) */
DECL|macro|DR
mdefine_line|#define DR&t;0x01UL&t;&t;/* Data Register (R/W) */
DECL|macro|DSR1
mdefine_line|#define DSR1&t;0x02UL&t;&t;/* D-channel Status Register 1 (R) */
DECL|macro|DER
mdefine_line|#define DER&t;0x03UL&t;&t;/* D-channel Error Register (R) */
DECL|macro|DCTB
mdefine_line|#define DCTB&t;0x04UL&t;&t;/* D-channel Transmit Buffer (W) */
DECL|macro|DCRB
mdefine_line|#define DCRB&t;DCTB&t;&t;/* D-channel Receive Buffer (R) */
DECL|macro|BBTB
mdefine_line|#define BBTB&t;0x05UL&t;&t;/* Bb-channel Transmit Buffer (W) */
DECL|macro|BBRB
mdefine_line|#define BBRB&t;BBTB&t;&t;/* Bb-channel Receive Buffer (R) */
DECL|macro|BCTB
mdefine_line|#define BCTB&t;0x06UL&t;&t;/* Bc-channel Transmit Buffer (W) */
DECL|macro|BCRB
mdefine_line|#define BCRB&t;BCTB&t;&t;/* Bc-channel Receive Buffer (R) */
DECL|macro|DSR2
mdefine_line|#define DSR2&t;0x07UL&t;&t;/* D-channel Status Register 2 (R) */
multiline_comment|/* Indirect registers in the Main Audio Processor. */
DECL|struct|amd7930_map
r_struct
id|amd7930_map
(brace
DECL|member|x
id|__u16
id|x
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|r
id|__u16
id|r
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|gx
id|__u16
id|gx
suffix:semicolon
DECL|member|gr
id|__u16
id|gr
suffix:semicolon
DECL|member|ger
id|__u16
id|ger
suffix:semicolon
DECL|member|stgr
id|__u16
id|stgr
suffix:semicolon
DECL|member|ftgr
id|__u16
id|ftgr
suffix:semicolon
DECL|member|atgr
id|__u16
id|atgr
suffix:semicolon
DECL|member|mmr1
id|__u8
id|mmr1
suffix:semicolon
DECL|member|mmr2
id|__u8
id|mmr2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* After an amd7930 interrupt, reading the Interrupt Register (ir)&n; * clears the interrupt and returns a bitmask indicated which&n; * interrupt source(s) require service&n; */
DECL|macro|AMR_IR_DTTHRSH
mdefine_line|#define AMR_IR_DTTHRSH&t;&t;&t;0x01 /* D-channel xmit threshold */
DECL|macro|AMR_IR_DRTHRSH
mdefine_line|#define AMR_IR_DRTHRSH&t;&t;&t;0x02 /* D-channel recv threshold */
DECL|macro|AMR_IR_DSRI
mdefine_line|#define AMR_IR_DSRI&t;&t;&t;0x04 /* D-channel packet status */
DECL|macro|AMR_IR_DERI
mdefine_line|#define AMR_IR_DERI&t;&t;&t;0x08 /* D-channel error */
DECL|macro|AMR_IR_BBUF
mdefine_line|#define AMR_IR_BBUF&t;&t;&t;0x10 /* B-channel data xfer */
DECL|macro|AMR_IR_LSRI
mdefine_line|#define AMR_IR_LSRI&t;&t;&t;0x20 /* LIU status */
DECL|macro|AMR_IR_DSR2I
mdefine_line|#define AMR_IR_DSR2I&t;&t;&t;0x40 /* D-channel buffer status */
DECL|macro|AMR_IR_MLTFRMI
mdefine_line|#define AMR_IR_MLTFRMI&t;&t;&t;0x80 /* multiframe or PP */
multiline_comment|/* The amd7930 has &quot;indirect registers&quot; which are accessed by writing&n; * the register number into the Command Register and then reading or&n; * writing values from the Data Register as appropriate. We define the&n; * AMR_* macros to be the indirect register numbers and AM_* macros to&n; * be bits in whatever register is referred to.&n; */
multiline_comment|/* Initialization */
DECL|macro|AMR_INIT
mdefine_line|#define&t;AMR_INIT&t;&t;&t;0x21
DECL|macro|AM_INIT_ACTIVE
mdefine_line|#define&t;&t;AM_INIT_ACTIVE&t;&t;&t;0x01
DECL|macro|AM_INIT_DATAONLY
mdefine_line|#define&t;&t;AM_INIT_DATAONLY&t;&t;0x02
DECL|macro|AM_INIT_POWERDOWN
mdefine_line|#define&t;&t;AM_INIT_POWERDOWN&t;&t;0x03
DECL|macro|AM_INIT_DISABLE_INTS
mdefine_line|#define&t;&t;AM_INIT_DISABLE_INTS&t;&t;0x04
DECL|macro|AMR_INIT2
mdefine_line|#define AMR_INIT2&t;&t;&t;0x20
DECL|macro|AM_INIT2_ENABLE_POWERDOWN
mdefine_line|#define&t;&t;AM_INIT2_ENABLE_POWERDOWN&t;0x20
DECL|macro|AM_INIT2_ENABLE_MULTIFRAME
mdefine_line|#define&t;&t;AM_INIT2_ENABLE_MULTIFRAME&t;0x10
multiline_comment|/* Line Interface Unit */
DECL|macro|AMR_LIU_LSR
mdefine_line|#define&t;AMR_LIU_LSR&t;&t;&t;0xA1
DECL|macro|AM_LIU_LSR_STATE
mdefine_line|#define&t;&t;AM_LIU_LSR_STATE&t;&t;0x07
DECL|macro|AM_LIU_LSR_F3
mdefine_line|#define&t;&t;AM_LIU_LSR_F3&t;&t;&t;0x08
DECL|macro|AM_LIU_LSR_F7
mdefine_line|#define&t;&t;AM_LIU_LSR_F7&t;&t;&t;0x10
DECL|macro|AM_LIU_LSR_F8
mdefine_line|#define&t;&t;AM_LIU_LSR_F8&t;&t;&t;0x20
DECL|macro|AM_LIU_LSR_HSW
mdefine_line|#define&t;&t;AM_LIU_LSR_HSW&t;&t;&t;0x40
DECL|macro|AM_LIU_LSR_HSW_CHG
mdefine_line|#define&t;&t;AM_LIU_LSR_HSW_CHG&t;&t;0x80
DECL|macro|AMR_LIU_LPR
mdefine_line|#define&t;AMR_LIU_LPR&t;&t;&t;0xA2
DECL|macro|AMR_LIU_LMR1
mdefine_line|#define&t;AMR_LIU_LMR1&t;&t;&t;0xA3
DECL|macro|AM_LIU_LMR1_B1_ENABL
mdefine_line|#define&t;&t;AM_LIU_LMR1_B1_ENABL&t;&t;0x01
DECL|macro|AM_LIU_LMR1_B2_ENABL
mdefine_line|#define&t;&t;AM_LIU_LMR1_B2_ENABL&t;&t;0x02
DECL|macro|AM_LIU_LMR1_F_DISABL
mdefine_line|#define&t;&t;AM_LIU_LMR1_F_DISABL&t;&t;0x04
DECL|macro|AM_LIU_LMR1_FA_DISABL
mdefine_line|#define&t;&t;AM_LIU_LMR1_FA_DISABL&t;&t;0x08
DECL|macro|AM_LIU_LMR1_REQ_ACTIV
mdefine_line|#define&t;&t;AM_LIU_LMR1_REQ_ACTIV&t;&t;0x10
DECL|macro|AM_LIU_LMR1_F8_F3
mdefine_line|#define&t;&t;AM_LIU_LMR1_F8_F3&t;&t;0x20
DECL|macro|AM_LIU_LMR1_LIU_ENABL
mdefine_line|#define&t;&t;AM_LIU_LMR1_LIU_ENABL&t;&t;0x40
DECL|macro|AMR_LIU_LMR2
mdefine_line|#define&t;AMR_LIU_LMR2&t;&t;&t;0xA4
DECL|macro|AM_LIU_LMR2_DECHO
mdefine_line|#define&t;&t;AM_LIU_LMR2_DECHO&t;&t;0x01
DECL|macro|AM_LIU_LMR2_DLOOP
mdefine_line|#define&t;&t;AM_LIU_LMR2_DLOOP&t;&t;0x02
DECL|macro|AM_LIU_LMR2_DBACKOFF
mdefine_line|#define&t;&t;AM_LIU_LMR2_DBACKOFF&t;&t;0x04
DECL|macro|AM_LIU_LMR2_EN_F3_INT
mdefine_line|#define&t;&t;AM_LIU_LMR2_EN_F3_INT&t;&t;0x08
DECL|macro|AM_LIU_LMR2_EN_F8_INT
mdefine_line|#define&t;&t;AM_LIU_LMR2_EN_F8_INT&t;&t;0x10
DECL|macro|AM_LIU_LMR2_EN_HSW_INT
mdefine_line|#define&t;&t;AM_LIU_LMR2_EN_HSW_INT&t;&t;0x20
DECL|macro|AM_LIU_LMR2_EN_F7_INT
mdefine_line|#define&t;&t;AM_LIU_LMR2_EN_F7_INT&t;&t;0x40
DECL|macro|AMR_LIU_2_4
mdefine_line|#define&t;AMR_LIU_2_4&t;&t;&t;0xA5
DECL|macro|AMR_LIU_MF
mdefine_line|#define&t;AMR_LIU_MF&t;&t;&t;0xA6
DECL|macro|AMR_LIU_MFSB
mdefine_line|#define&t;AMR_LIU_MFSB&t;&t;&t;0xA7
DECL|macro|AMR_LIU_MFQB
mdefine_line|#define&t;AMR_LIU_MFQB&t;&t;&t;0xA8
multiline_comment|/* Multiplexor */
DECL|macro|AMR_MUX_MCR1
mdefine_line|#define&t;AMR_MUX_MCR1&t;&t;&t;0x41
DECL|macro|AMR_MUX_MCR2
mdefine_line|#define&t;AMR_MUX_MCR2&t;&t;&t;0x42
DECL|macro|AMR_MUX_MCR3
mdefine_line|#define&t;AMR_MUX_MCR3&t;&t;&t;0x43
DECL|macro|AM_MUX_CHANNEL_B1
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_B1&t;&t;0x01
DECL|macro|AM_MUX_CHANNEL_B2
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_B2&t;&t;0x02
DECL|macro|AM_MUX_CHANNEL_Ba
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_Ba&t;&t;0x03
DECL|macro|AM_MUX_CHANNEL_Bb
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_Bb&t;&t;0x04
DECL|macro|AM_MUX_CHANNEL_Bc
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_Bc&t;&t;0x05
DECL|macro|AM_MUX_CHANNEL_Bd
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_Bd&t;&t;0x06
DECL|macro|AM_MUX_CHANNEL_Be
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_Be&t;&t;0x07
DECL|macro|AM_MUX_CHANNEL_Bf
mdefine_line|#define&t;&t;AM_MUX_CHANNEL_Bf&t;&t;0x08
DECL|macro|AMR_MUX_MCR4
mdefine_line|#define&t;AMR_MUX_MCR4&t;&t;&t;0x44
DECL|macro|AM_MUX_MCR4_ENABLE_INTS
mdefine_line|#define&t;&t;AM_MUX_MCR4_ENABLE_INTS&t;&t;0x08
DECL|macro|AM_MUX_MCR4_REVERSE_Bb
mdefine_line|#define&t;&t;AM_MUX_MCR4_REVERSE_Bb&t;&t;0x10
DECL|macro|AM_MUX_MCR4_REVERSE_Bc
mdefine_line|#define&t;&t;AM_MUX_MCR4_REVERSE_Bc&t;&t;0x20
DECL|macro|AMR_MUX_1_4
mdefine_line|#define&t;AMR_MUX_1_4&t;&t;&t;0x45
multiline_comment|/* Main Audio Processor */
DECL|macro|AMR_MAP_X
mdefine_line|#define&t;AMR_MAP_X&t;&t;&t;0x61
DECL|macro|AMR_MAP_R
mdefine_line|#define&t;AMR_MAP_R&t;&t;&t;0x62
DECL|macro|AMR_MAP_GX
mdefine_line|#define&t;AMR_MAP_GX&t;&t;&t;0x63
DECL|macro|AMR_MAP_GR
mdefine_line|#define&t;AMR_MAP_GR&t;&t;&t;0x64
DECL|macro|AMR_MAP_GER
mdefine_line|#define&t;AMR_MAP_GER&t;&t;&t;0x65
DECL|macro|AMR_MAP_STGR
mdefine_line|#define&t;AMR_MAP_STGR&t;&t;&t;0x66
DECL|macro|AMR_MAP_FTGR_1_2
mdefine_line|#define&t;AMR_MAP_FTGR_1_2&t;&t;0x67
DECL|macro|AMR_MAP_ATGR_1_2
mdefine_line|#define&t;AMR_MAP_ATGR_1_2&t;&t;0x68
DECL|macro|AMR_MAP_MMR1
mdefine_line|#define&t;AMR_MAP_MMR1&t;&t;&t;0x69
DECL|macro|AM_MAP_MMR1_ALAW
mdefine_line|#define&t;&t;AM_MAP_MMR1_ALAW&t;&t;0x01
DECL|macro|AM_MAP_MMR1_GX
mdefine_line|#define&t;&t;AM_MAP_MMR1_GX&t;&t;&t;0x02
DECL|macro|AM_MAP_MMR1_GR
mdefine_line|#define&t;&t;AM_MAP_MMR1_GR&t;&t;&t;0x04
DECL|macro|AM_MAP_MMR1_GER
mdefine_line|#define&t;&t;AM_MAP_MMR1_GER&t;&t;&t;0x08
DECL|macro|AM_MAP_MMR1_X
mdefine_line|#define&t;&t;AM_MAP_MMR1_X&t;&t;&t;0x10
DECL|macro|AM_MAP_MMR1_R
mdefine_line|#define&t;&t;AM_MAP_MMR1_R&t;&t;&t;0x20
DECL|macro|AM_MAP_MMR1_STG
mdefine_line|#define&t;&t;AM_MAP_MMR1_STG&t;&t;&t;0x40
DECL|macro|AM_MAP_MMR1_LOOPBACK
mdefine_line|#define&t;&t;AM_MAP_MMR1_LOOPBACK&t;&t;0x80
DECL|macro|AMR_MAP_MMR2
mdefine_line|#define&t;AMR_MAP_MMR2&t;&t;&t;0x6A
DECL|macro|AM_MAP_MMR2_AINB
mdefine_line|#define&t;&t;AM_MAP_MMR2_AINB&t;&t;0x01
DECL|macro|AM_MAP_MMR2_LS
mdefine_line|#define&t;&t;AM_MAP_MMR2_LS&t;&t;&t;0x02
DECL|macro|AM_MAP_MMR2_ENABLE_DTMF
mdefine_line|#define&t;&t;AM_MAP_MMR2_ENABLE_DTMF&t;&t;0x04
DECL|macro|AM_MAP_MMR2_ENABLE_TONEGEN
mdefine_line|#define&t;&t;AM_MAP_MMR2_ENABLE_TONEGEN&t;0x08
DECL|macro|AM_MAP_MMR2_ENABLE_TONERING
mdefine_line|#define&t;&t;AM_MAP_MMR2_ENABLE_TONERING&t;0x10
DECL|macro|AM_MAP_MMR2_DISABLE_HIGHPASS
mdefine_line|#define&t;&t;AM_MAP_MMR2_DISABLE_HIGHPASS&t;0x20
DECL|macro|AM_MAP_MMR2_DISABLE_AUTOZERO
mdefine_line|#define&t;&t;AM_MAP_MMR2_DISABLE_AUTOZERO&t;0x40
DECL|macro|AMR_MAP_1_10
mdefine_line|#define&t;AMR_MAP_1_10&t;&t;&t;0x6B
DECL|macro|AMR_MAP_MMR3
mdefine_line|#define&t;AMR_MAP_MMR3&t;&t;&t;0x6C
DECL|macro|AMR_MAP_STRA
mdefine_line|#define&t;AMR_MAP_STRA&t;&t;&t;0x6D
DECL|macro|AMR_MAP_STRF
mdefine_line|#define&t;AMR_MAP_STRF&t;&t;&t;0x6E
DECL|macro|AMR_MAP_PEAKX
mdefine_line|#define&t;AMR_MAP_PEAKX&t;&t;&t;0x70
DECL|macro|AMR_MAP_PEAKR
mdefine_line|#define&t;AMR_MAP_PEAKR&t;&t;&t;0x71
DECL|macro|AMR_MAP_15_16
mdefine_line|#define&t;AMR_MAP_15_16&t;&t;&t;0x72
multiline_comment|/* Data Link Controller */
DECL|macro|AMR_DLC_FRAR_1_2_3
mdefine_line|#define&t;AMR_DLC_FRAR_1_2_3&t;&t;0x81
DECL|macro|AMR_DLC_SRAR_1_2_3
mdefine_line|#define&t;AMR_DLC_SRAR_1_2_3&t;&t;0x82
DECL|macro|AMR_DLC_TAR
mdefine_line|#define&t;AMR_DLC_TAR&t;&t;&t;0x83
DECL|macro|AMR_DLC_DRLR
mdefine_line|#define&t;AMR_DLC_DRLR&t;&t;&t;0x84
DECL|macro|AMR_DLC_DTCR
mdefine_line|#define&t;AMR_DLC_DTCR&t;&t;&t;0x85
DECL|macro|AMR_DLC_DMR1
mdefine_line|#define&t;AMR_DLC_DMR1&t;&t;&t;0x86
DECL|macro|AMR_DLC_DMR1_DTTHRSH_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR1_DTTHRSH_INT&t;0x01
DECL|macro|AMR_DLC_DMR1_DRTHRSH_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR1_DRTHRSH_INT&t;0x02
DECL|macro|AMR_DLC_DMR1_TAR_ENABL
mdefine_line|#define&t;&t;AMR_DLC_DMR1_TAR_ENABL&t;&t;0x04
DECL|macro|AMR_DLC_DMR1_EORP_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR1_EORP_INT&t;&t;0x08
DECL|macro|AMR_DLC_DMR1_EN_ADDR1
mdefine_line|#define&t;&t;AMR_DLC_DMR1_EN_ADDR1&t;&t;0x10
DECL|macro|AMR_DLC_DMR1_EN_ADDR2
mdefine_line|#define&t;&t;AMR_DLC_DMR1_EN_ADDR2&t;&t;0x20
DECL|macro|AMR_DLC_DMR1_EN_ADDR3
mdefine_line|#define&t;&t;AMR_DLC_DMR1_EN_ADDR3&t;&t;0x40
DECL|macro|AMR_DLC_DMR1_EN_ADDR4
mdefine_line|#define&t;&t;AMR_DLC_DMR1_EN_ADDR4&t;&t;0x80
DECL|macro|AMR_DLC_DMR1_EN_ADDRS
mdefine_line|#define&t;&t;AMR_DLC_DMR1_EN_ADDRS&t;&t;0xf0
DECL|macro|AMR_DLC_DMR2
mdefine_line|#define&t;AMR_DLC_DMR2&t;&t;&t;0x87
DECL|macro|AMR_DLC_DMR2_RABRT_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_RABRT_INT&t;&t;0x01
DECL|macro|AMR_DLC_DMR2_RESID_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_RESID_INT&t;&t;0x02
DECL|macro|AMR_DLC_DMR2_COLL_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_COLL_INT&t;&t;0x04
DECL|macro|AMR_DLC_DMR2_FCS_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_FCS_INT&t;&t;0x08
DECL|macro|AMR_DLC_DMR2_OVFL_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_OVFL_INT&t;&t;0x10
DECL|macro|AMR_DLC_DMR2_UNFL_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_UNFL_INT&t;&t;0x20
DECL|macro|AMR_DLC_DMR2_OVRN_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_OVRN_INT&t;&t;0x40
DECL|macro|AMR_DLC_DMR2_UNRN_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR2_UNRN_INT&t;&t;0x80
DECL|macro|AMR_DLC_1_7
mdefine_line|#define&t;AMR_DLC_1_7&t;&t;&t;0x88
DECL|macro|AMR_DLC_DRCR
mdefine_line|#define&t;AMR_DLC_DRCR&t;&t;&t;0x89
DECL|macro|AMR_DLC_RNGR1
mdefine_line|#define&t;AMR_DLC_RNGR1&t;&t;&t;0x8A
DECL|macro|AMR_DLC_RNGR2
mdefine_line|#define&t;AMR_DLC_RNGR2&t;&t;&t;0x8B
DECL|macro|AMR_DLC_FRAR4
mdefine_line|#define&t;AMR_DLC_FRAR4&t;&t;&t;0x8C
DECL|macro|AMR_DLC_SRAR4
mdefine_line|#define&t;AMR_DLC_SRAR4&t;&t;&t;0x8D
DECL|macro|AMR_DLC_DMR3
mdefine_line|#define&t;AMR_DLC_DMR3&t;&t;&t;0x8E
DECL|macro|AMR_DLC_DMR3_VA_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR3_VA_INT&t;&t;0x01
DECL|macro|AMR_DLC_DMR3_EOTP_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR3_EOTP_INT&t;&t;0x02
DECL|macro|AMR_DLC_DMR3_LBRP_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR3_LBRP_INT&t;&t;0x04
DECL|macro|AMR_DLC_DMR3_RBA_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR3_RBA_INT&t;&t;0x08
DECL|macro|AMR_DLC_DMR3_LBT_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR3_LBT_INT&t;&t;0x10
DECL|macro|AMR_DLC_DMR3_TBE_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR3_TBE_INT&t;&t;0x20
DECL|macro|AMR_DLC_DMR3_RPLOST_INT
mdefine_line|#define&t;&t;AMR_DLC_DMR3_RPLOST_INT&t;&t;0x40
DECL|macro|AMR_DLC_DMR3_KEEP_FCS
mdefine_line|#define&t;&t;AMR_DLC_DMR3_KEEP_FCS&t;&t;0x80
DECL|macro|AMR_DLC_DMR4
mdefine_line|#define&t;AMR_DLC_DMR4&t;&t;&t;0x8F
DECL|macro|AMR_DLC_DMR4_RCV_1
mdefine_line|#define&t;&t;AMR_DLC_DMR4_RCV_1&t;&t;0x00
DECL|macro|AMR_DLC_DMR4_RCV_2
mdefine_line|#define&t;&t;AMR_DLC_DMR4_RCV_2&t;&t;0x01
DECL|macro|AMR_DLC_DMR4_RCV_4
mdefine_line|#define&t;&t;AMR_DLC_DMR4_RCV_4&t;&t;0x02
DECL|macro|AMR_DLC_DMR4_RCV_8
mdefine_line|#define&t;&t;AMR_DLC_DMR4_RCV_8&t;&t;0x03
DECL|macro|AMR_DLC_DMR4_RCV_16
mdefine_line|#define&t;&t;AMR_DLC_DMR4_RCV_16&t;&t;0x01
DECL|macro|AMR_DLC_DMR4_RCV_24
mdefine_line|#define&t;&t;AMR_DLC_DMR4_RCV_24&t;&t;0x02
DECL|macro|AMR_DLC_DMR4_RCV_30
mdefine_line|#define&t;&t;AMR_DLC_DMR4_RCV_30&t;&t;0x03
DECL|macro|AMR_DLC_DMR4_XMT_1
mdefine_line|#define&t;&t;AMR_DLC_DMR4_XMT_1&t;&t;0x00
DECL|macro|AMR_DLC_DMR4_XMT_2
mdefine_line|#define&t;&t;AMR_DLC_DMR4_XMT_2&t;&t;0x04
DECL|macro|AMR_DLC_DMR4_XMT_4
mdefine_line|#define&t;&t;AMR_DLC_DMR4_XMT_4&t;&t;0x08
DECL|macro|AMR_DLC_DMR4_XMT_8
mdefine_line|#define&t;&t;AMR_DLC_DMR4_XMT_8&t;&t;0x0c
DECL|macro|AMR_DLC_DMR4_XMT_10
mdefine_line|#define&t;&t;AMR_DLC_DMR4_XMT_10&t;&t;0x08
DECL|macro|AMR_DLC_DMR4_XMT_14
mdefine_line|#define&t;&t;AMR_DLC_DMR4_XMT_14&t;&t;0x0c
DECL|macro|AMR_DLC_DMR4_IDLE_MARK
mdefine_line|#define&t;&t;AMR_DLC_DMR4_IDLE_MARK&t;&t;0x00
DECL|macro|AMR_DLC_DMR4_IDLE_FLAG
mdefine_line|#define&t;&t;AMR_DLC_DMR4_IDLE_FLAG&t;&t;0x10
DECL|macro|AMR_DLC_DMR4_ADDR_BOTH
mdefine_line|#define&t;&t;AMR_DLC_DMR4_ADDR_BOTH&t;&t;0x00
DECL|macro|AMR_DLC_DMR4_ADDR_1ST
mdefine_line|#define&t;&t;AMR_DLC_DMR4_ADDR_1ST&t;&t;0x20
DECL|macro|AMR_DLC_DMR4_ADDR_2ND
mdefine_line|#define&t;&t;AMR_DLC_DMR4_ADDR_2ND&t;&t;0xa0
DECL|macro|AMR_DLC_DMR4_CR_ENABLE
mdefine_line|#define&t;&t;AMR_DLC_DMR4_CR_ENABLE&t;&t;0x40
DECL|macro|AMR_DLC_12_15
mdefine_line|#define&t;AMR_DLC_12_15&t;&t;&t;0x90
DECL|macro|AMR_DLC_ASR
mdefine_line|#define&t;AMR_DLC_ASR&t;&t;&t;0x91
DECL|macro|AMR_DLC_EFCR
mdefine_line|#define&t;AMR_DLC_EFCR&t;&t;&t;0x92
DECL|macro|AMR_DLC_EFCR_EXTEND_FIFO
mdefine_line|#define&t;&t;AMR_DLC_EFCR_EXTEND_FIFO&t;0x01
DECL|macro|AMR_DLC_EFCR_SEC_PKT_INT
mdefine_line|#define&t;&t;AMR_DLC_EFCR_SEC_PKT_INT&t;0x02
DECL|macro|AMR_DSR1_VADDR
mdefine_line|#define AMR_DSR1_VADDR&t;&t;&t;0x01
DECL|macro|AMR_DSR1_EORP
mdefine_line|#define AMR_DSR1_EORP&t;&t;&t;0x02
DECL|macro|AMR_DSR1_PKT_IP
mdefine_line|#define AMR_DSR1_PKT_IP&t;&t;&t;0x04
DECL|macro|AMR_DSR1_DECHO_ON
mdefine_line|#define AMR_DSR1_DECHO_ON&t;&t;0x08
DECL|macro|AMR_DSR1_DLOOP_ON
mdefine_line|#define AMR_DSR1_DLOOP_ON&t;&t;0x10
DECL|macro|AMR_DSR1_DBACK_OFF
mdefine_line|#define AMR_DSR1_DBACK_OFF&t;&t;0x20
DECL|macro|AMR_DSR1_EOTP
mdefine_line|#define AMR_DSR1_EOTP&t;&t;&t;0x40
DECL|macro|AMR_DSR1_CXMT_ABRT
mdefine_line|#define AMR_DSR1_CXMT_ABRT&t;&t;0x80
DECL|macro|AMR_DSR2_LBRP
mdefine_line|#define AMR_DSR2_LBRP&t;&t;&t;0x01
DECL|macro|AMR_DSR2_RBA
mdefine_line|#define AMR_DSR2_RBA&t;&t;&t;0x02
DECL|macro|AMR_DSR2_RPLOST
mdefine_line|#define AMR_DSR2_RPLOST&t;&t;&t;0x04
DECL|macro|AMR_DSR2_LAST_BYTE
mdefine_line|#define AMR_DSR2_LAST_BYTE&t;&t;0x08
DECL|macro|AMR_DSR2_TBE
mdefine_line|#define AMR_DSR2_TBE&t;&t;&t;0x10
DECL|macro|AMR_DSR2_MARK_IDLE
mdefine_line|#define AMR_DSR2_MARK_IDLE&t;&t;0x20
DECL|macro|AMR_DSR2_FLAG_IDLE
mdefine_line|#define AMR_DSR2_FLAG_IDLE&t;&t;0x40
DECL|macro|AMR_DSR2_SECOND_PKT
mdefine_line|#define AMR_DSR2_SECOND_PKT&t;&t;0x80
DECL|macro|AMR_DER_RABRT
mdefine_line|#define AMR_DER_RABRT&t;&t;&t;0x01
DECL|macro|AMR_DER_RFRAME
mdefine_line|#define AMR_DER_RFRAME&t;&t;&t;0x02
DECL|macro|AMR_DER_COLLISION
mdefine_line|#define AMR_DER_COLLISION&t;&t;0x04
DECL|macro|AMR_DER_FCS
mdefine_line|#define AMR_DER_FCS&t;&t;&t;0x08
DECL|macro|AMR_DER_OVFL
mdefine_line|#define AMR_DER_OVFL&t;&t;&t;0x10
DECL|macro|AMR_DER_UNFL
mdefine_line|#define AMR_DER_UNFL&t;&t;&t;0x20
DECL|macro|AMR_DER_OVRN
mdefine_line|#define AMR_DER_OVRN&t;&t;&t;0x40
DECL|macro|AMR_DER_UNRN
mdefine_line|#define AMR_DER_UNRN&t;&t;&t;0x80
multiline_comment|/* Peripheral Port */
DECL|macro|AMR_PP_PPCR1
mdefine_line|#define&t;AMR_PP_PPCR1&t;&t;&t;0xC0
DECL|macro|AMR_PP_PPSR
mdefine_line|#define&t;AMR_PP_PPSR&t;&t;&t;0xC1
DECL|macro|AMR_PP_PPIER
mdefine_line|#define&t;AMR_PP_PPIER&t;&t;&t;0xC2
DECL|macro|AMR_PP_MTDR
mdefine_line|#define&t;AMR_PP_MTDR&t;&t;&t;0xC3
DECL|macro|AMR_PP_MRDR
mdefine_line|#define&t;AMR_PP_MRDR&t;&t;&t;0xC3
DECL|macro|AMR_PP_CITDR0
mdefine_line|#define&t;AMR_PP_CITDR0&t;&t;&t;0xC4
DECL|macro|AMR_PP_CIRDR0
mdefine_line|#define&t;AMR_PP_CIRDR0&t;&t;&t;0xC4
DECL|macro|AMR_PP_CITDR1
mdefine_line|#define&t;AMR_PP_CITDR1&t;&t;&t;0xC5
DECL|macro|AMR_PP_CIRDR1
mdefine_line|#define&t;AMR_PP_CIRDR1&t;&t;&t;0xC5
DECL|macro|AMR_PP_PPCR2
mdefine_line|#define&t;AMR_PP_PPCR2&t;&t;&t;0xC8
DECL|macro|AMR_PP_PPCR3
mdefine_line|#define&t;AMR_PP_PPCR3&t;&t;&t;0xC9
multiline_comment|/* Give this chip a &quot;default&quot; sample rate */
DECL|macro|AMD7930_RATE
mdefine_line|#define AMD7930_RATE                    (8000)
macro_line|#endif /* _AMD7930_H_ */
eof
