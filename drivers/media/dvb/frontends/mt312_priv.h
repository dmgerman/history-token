multiline_comment|/*&n;    Driver for Zarlink MT312 QPSK Frontend&n;&n;    Copyright (C) 2003 Andreas Oberritter &lt;obi@linuxtv.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#ifndef _DVB_FRONTENDS_MT312_PRIV
DECL|macro|_DVB_FRONTENDS_MT312_PRIV
mdefine_line|#define _DVB_FRONTENDS_MT312_PRIV
DECL|enum|mt312_reg_addr
r_enum
id|mt312_reg_addr
(brace
DECL|enumerator|QPSK_INT_H
id|QPSK_INT_H
op_assign
l_int|0
comma
DECL|enumerator|QPSK_INT_M
id|QPSK_INT_M
op_assign
l_int|1
comma
DECL|enumerator|QPSK_INT_L
id|QPSK_INT_L
op_assign
l_int|2
comma
DECL|enumerator|FEC_INT
id|FEC_INT
op_assign
l_int|3
comma
DECL|enumerator|QPSK_STAT_H
id|QPSK_STAT_H
op_assign
l_int|4
comma
DECL|enumerator|QPSK_STAT_L
id|QPSK_STAT_L
op_assign
l_int|5
comma
DECL|enumerator|FEC_STATUS
id|FEC_STATUS
op_assign
l_int|6
comma
DECL|enumerator|LNB_FREQ_H
id|LNB_FREQ_H
op_assign
l_int|7
comma
DECL|enumerator|LNB_FREQ_L
id|LNB_FREQ_L
op_assign
l_int|8
comma
DECL|enumerator|M_SNR_H
id|M_SNR_H
op_assign
l_int|9
comma
DECL|enumerator|M_SNR_L
id|M_SNR_L
op_assign
l_int|10
comma
DECL|enumerator|VIT_ERRCNT_H
id|VIT_ERRCNT_H
op_assign
l_int|11
comma
DECL|enumerator|VIT_ERRCNT_M
id|VIT_ERRCNT_M
op_assign
l_int|12
comma
DECL|enumerator|VIT_ERRCNT_L
id|VIT_ERRCNT_L
op_assign
l_int|13
comma
DECL|enumerator|RS_BERCNT_H
id|RS_BERCNT_H
op_assign
l_int|14
comma
DECL|enumerator|RS_BERCNT_M
id|RS_BERCNT_M
op_assign
l_int|15
comma
DECL|enumerator|RS_BERCNT_L
id|RS_BERCNT_L
op_assign
l_int|16
comma
DECL|enumerator|RS_UBC_H
id|RS_UBC_H
op_assign
l_int|17
comma
DECL|enumerator|RS_UBC_L
id|RS_UBC_L
op_assign
l_int|18
comma
DECL|enumerator|SIG_LEVEL
id|SIG_LEVEL
op_assign
l_int|19
comma
DECL|enumerator|GPP_CTRL
id|GPP_CTRL
op_assign
l_int|20
comma
DECL|enumerator|RESET
id|RESET
op_assign
l_int|21
comma
DECL|enumerator|DISEQC_MODE
id|DISEQC_MODE
op_assign
l_int|22
comma
DECL|enumerator|SYM_RATE_H
id|SYM_RATE_H
op_assign
l_int|23
comma
DECL|enumerator|SYM_RATE_L
id|SYM_RATE_L
op_assign
l_int|24
comma
DECL|enumerator|VIT_MODE
id|VIT_MODE
op_assign
l_int|25
comma
DECL|enumerator|QPSK_CTRL
id|QPSK_CTRL
op_assign
l_int|26
comma
DECL|enumerator|GO
id|GO
op_assign
l_int|27
comma
DECL|enumerator|IE_QPSK_H
id|IE_QPSK_H
op_assign
l_int|28
comma
DECL|enumerator|IE_QPSK_M
id|IE_QPSK_M
op_assign
l_int|29
comma
DECL|enumerator|IE_QPSK_L
id|IE_QPSK_L
op_assign
l_int|30
comma
DECL|enumerator|IE_FEC
id|IE_FEC
op_assign
l_int|31
comma
DECL|enumerator|QPSK_STAT_EN
id|QPSK_STAT_EN
op_assign
l_int|32
comma
DECL|enumerator|FEC_STAT_EN
id|FEC_STAT_EN
op_assign
l_int|33
comma
DECL|enumerator|SYS_CLK
id|SYS_CLK
op_assign
l_int|34
comma
DECL|enumerator|DISEQC_RATIO
id|DISEQC_RATIO
op_assign
l_int|35
comma
DECL|enumerator|DISEQC_INSTR
id|DISEQC_INSTR
op_assign
l_int|36
comma
DECL|enumerator|FR_LIM
id|FR_LIM
op_assign
l_int|37
comma
DECL|enumerator|FR_OFF
id|FR_OFF
op_assign
l_int|38
comma
DECL|enumerator|AGC_CTRL
id|AGC_CTRL
op_assign
l_int|39
comma
DECL|enumerator|AGC_INIT
id|AGC_INIT
op_assign
l_int|40
comma
DECL|enumerator|AGC_REF
id|AGC_REF
op_assign
l_int|41
comma
DECL|enumerator|AGC_MAX
id|AGC_MAX
op_assign
l_int|42
comma
DECL|enumerator|AGC_MIN
id|AGC_MIN
op_assign
l_int|43
comma
DECL|enumerator|AGC_LK_TH
id|AGC_LK_TH
op_assign
l_int|44
comma
DECL|enumerator|TS_AGC_LK_TH
id|TS_AGC_LK_TH
op_assign
l_int|45
comma
DECL|enumerator|AGC_PWR_SET
id|AGC_PWR_SET
op_assign
l_int|46
comma
DECL|enumerator|QPSK_MISC
id|QPSK_MISC
op_assign
l_int|47
comma
DECL|enumerator|SNR_THS_LOW
id|SNR_THS_LOW
op_assign
l_int|48
comma
DECL|enumerator|SNR_THS_HIGH
id|SNR_THS_HIGH
op_assign
l_int|49
comma
DECL|enumerator|TS_SW_RATE
id|TS_SW_RATE
op_assign
l_int|50
comma
DECL|enumerator|TS_SW_LIM_L
id|TS_SW_LIM_L
op_assign
l_int|51
comma
DECL|enumerator|TS_SW_LIM_H
id|TS_SW_LIM_H
op_assign
l_int|52
comma
DECL|enumerator|CS_SW_RATE_1
id|CS_SW_RATE_1
op_assign
l_int|53
comma
DECL|enumerator|CS_SW_RATE_2
id|CS_SW_RATE_2
op_assign
l_int|54
comma
DECL|enumerator|CS_SW_RATE_3
id|CS_SW_RATE_3
op_assign
l_int|55
comma
DECL|enumerator|CS_SW_RATE_4
id|CS_SW_RATE_4
op_assign
l_int|56
comma
DECL|enumerator|CS_SW_LIM
id|CS_SW_LIM
op_assign
l_int|57
comma
DECL|enumerator|TS_LPK
id|TS_LPK
op_assign
l_int|58
comma
DECL|enumerator|TS_LPK_M
id|TS_LPK_M
op_assign
l_int|59
comma
DECL|enumerator|TS_LPK_L
id|TS_LPK_L
op_assign
l_int|60
comma
DECL|enumerator|CS_KPROP_H
id|CS_KPROP_H
op_assign
l_int|61
comma
DECL|enumerator|CS_KPROP_L
id|CS_KPROP_L
op_assign
l_int|62
comma
DECL|enumerator|CS_KINT_H
id|CS_KINT_H
op_assign
l_int|63
comma
DECL|enumerator|CS_KINT_L
id|CS_KINT_L
op_assign
l_int|64
comma
DECL|enumerator|QPSK_SCALE
id|QPSK_SCALE
op_assign
l_int|65
comma
DECL|enumerator|TLD_OUTCLK_TH
id|TLD_OUTCLK_TH
op_assign
l_int|66
comma
DECL|enumerator|TLD_INCLK_TH
id|TLD_INCLK_TH
op_assign
l_int|67
comma
DECL|enumerator|FLD_TH
id|FLD_TH
op_assign
l_int|68
comma
DECL|enumerator|PLD_OUTLK3
id|PLD_OUTLK3
op_assign
l_int|69
comma
DECL|enumerator|PLD_OUTLK2
id|PLD_OUTLK2
op_assign
l_int|70
comma
DECL|enumerator|PLD_OUTLK1
id|PLD_OUTLK1
op_assign
l_int|71
comma
DECL|enumerator|PLD_OUTLK0
id|PLD_OUTLK0
op_assign
l_int|72
comma
DECL|enumerator|PLD_INLK3
id|PLD_INLK3
op_assign
l_int|73
comma
DECL|enumerator|PLD_INLK2
id|PLD_INLK2
op_assign
l_int|74
comma
DECL|enumerator|PLD_INLK1
id|PLD_INLK1
op_assign
l_int|75
comma
DECL|enumerator|PLD_INLK0
id|PLD_INLK0
op_assign
l_int|76
comma
DECL|enumerator|PLD_ACC_TIME
id|PLD_ACC_TIME
op_assign
l_int|77
comma
DECL|enumerator|SWEEP_PAR
id|SWEEP_PAR
op_assign
l_int|78
comma
DECL|enumerator|STARTUP_TIME
id|STARTUP_TIME
op_assign
l_int|79
comma
DECL|enumerator|LOSSLOCK_TH
id|LOSSLOCK_TH
op_assign
l_int|80
comma
DECL|enumerator|FEC_LOCK_TM
id|FEC_LOCK_TM
op_assign
l_int|81
comma
DECL|enumerator|LOSSLOCK_TM
id|LOSSLOCK_TM
op_assign
l_int|82
comma
DECL|enumerator|VIT_ERRPER_H
id|VIT_ERRPER_H
op_assign
l_int|83
comma
DECL|enumerator|VIT_ERRPER_M
id|VIT_ERRPER_M
op_assign
l_int|84
comma
DECL|enumerator|VIT_ERRPER_L
id|VIT_ERRPER_L
op_assign
l_int|85
comma
DECL|enumerator|VIT_SETUP
id|VIT_SETUP
op_assign
l_int|86
comma
DECL|enumerator|VIT_REF0
id|VIT_REF0
op_assign
l_int|87
comma
DECL|enumerator|VIT_REF1
id|VIT_REF1
op_assign
l_int|88
comma
DECL|enumerator|VIT_REF2
id|VIT_REF2
op_assign
l_int|89
comma
DECL|enumerator|VIT_REF3
id|VIT_REF3
op_assign
l_int|90
comma
DECL|enumerator|VIT_REF4
id|VIT_REF4
op_assign
l_int|91
comma
DECL|enumerator|VIT_REF5
id|VIT_REF5
op_assign
l_int|92
comma
DECL|enumerator|VIT_REF6
id|VIT_REF6
op_assign
l_int|93
comma
DECL|enumerator|VIT_MAXERR
id|VIT_MAXERR
op_assign
l_int|94
comma
DECL|enumerator|BA_SETUPT
id|BA_SETUPT
op_assign
l_int|95
comma
DECL|enumerator|OP_CTRL
id|OP_CTRL
op_assign
l_int|96
comma
DECL|enumerator|FEC_SETUP
id|FEC_SETUP
op_assign
l_int|97
comma
DECL|enumerator|PROG_SYNC
id|PROG_SYNC
op_assign
l_int|98
comma
DECL|enumerator|AFC_SEAR_TH
id|AFC_SEAR_TH
op_assign
l_int|99
comma
DECL|enumerator|CSACC_DIF_TH
id|CSACC_DIF_TH
op_assign
l_int|100
comma
DECL|enumerator|QPSK_LK_CT
id|QPSK_LK_CT
op_assign
l_int|101
comma
DECL|enumerator|QPSK_ST_CT
id|QPSK_ST_CT
op_assign
l_int|102
comma
DECL|enumerator|MON_CTRL
id|MON_CTRL
op_assign
l_int|103
comma
DECL|enumerator|QPSK_RESET
id|QPSK_RESET
op_assign
l_int|104
comma
DECL|enumerator|QPSK_TST_CT
id|QPSK_TST_CT
op_assign
l_int|105
comma
DECL|enumerator|QPSK_TST_ST
id|QPSK_TST_ST
op_assign
l_int|106
comma
DECL|enumerator|TEST_R
id|TEST_R
op_assign
l_int|107
comma
DECL|enumerator|AGC_H
id|AGC_H
op_assign
l_int|108
comma
DECL|enumerator|AGC_M
id|AGC_M
op_assign
l_int|109
comma
DECL|enumerator|AGC_L
id|AGC_L
op_assign
l_int|110
comma
DECL|enumerator|FREQ_ERR1_H
id|FREQ_ERR1_H
op_assign
l_int|111
comma
DECL|enumerator|FREQ_ERR1_M
id|FREQ_ERR1_M
op_assign
l_int|112
comma
DECL|enumerator|FREQ_ERR1_L
id|FREQ_ERR1_L
op_assign
l_int|113
comma
DECL|enumerator|FREQ_ERR2_H
id|FREQ_ERR2_H
op_assign
l_int|114
comma
DECL|enumerator|FREQ_ERR2_L
id|FREQ_ERR2_L
op_assign
l_int|115
comma
DECL|enumerator|SYM_RAT_OP_H
id|SYM_RAT_OP_H
op_assign
l_int|116
comma
DECL|enumerator|SYM_RAT_OP_L
id|SYM_RAT_OP_L
op_assign
l_int|117
comma
DECL|enumerator|DESEQC2_INT
id|DESEQC2_INT
op_assign
l_int|118
comma
DECL|enumerator|DISEQC2_STAT
id|DISEQC2_STAT
op_assign
l_int|119
comma
DECL|enumerator|DISEQC2_FIFO
id|DISEQC2_FIFO
op_assign
l_int|120
comma
DECL|enumerator|DISEQC2_CTRL1
id|DISEQC2_CTRL1
op_assign
l_int|121
comma
DECL|enumerator|DISEQC2_CTRL2
id|DISEQC2_CTRL2
op_assign
l_int|122
comma
DECL|enumerator|MONITOR_H
id|MONITOR_H
op_assign
l_int|123
comma
DECL|enumerator|MONITOR_L
id|MONITOR_L
op_assign
l_int|124
comma
DECL|enumerator|TEST_MODE
id|TEST_MODE
op_assign
l_int|125
comma
DECL|enumerator|ID
id|ID
op_assign
l_int|126
comma
DECL|enumerator|CONFIG
id|CONFIG
op_assign
l_int|127
)brace
suffix:semicolon
DECL|enum|mt312_model_id
r_enum
id|mt312_model_id
(brace
DECL|enumerator|ID_VP310
id|ID_VP310
op_assign
l_int|1
comma
DECL|enumerator|ID_MT312
id|ID_MT312
op_assign
l_int|3
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* DVB_FRONTENDS_MT312_PRIV */
eof
