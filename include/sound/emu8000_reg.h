macro_line|#ifndef __SOUND_EMU8000_REG_H
DECL|macro|__SOUND_EMU8000_REG_H
mdefine_line|#define __SOUND_EMU8000_REG_H
multiline_comment|/*&n; *  Register operations for the EMU8000&n; *&n; *  Copyright (C) 1999 Steve Ratcliffe&n; *&n; *  Based on awe_wave.c by Takashi Iwai&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/*&n; * Data port addresses relative to the EMU base.&n; */
DECL|macro|EMU8000_DATA0
mdefine_line|#define EMU8000_DATA0(e)    ((e)-&gt;port1)
DECL|macro|EMU8000_DATA1
mdefine_line|#define EMU8000_DATA1(e)    ((e)-&gt;port2)
DECL|macro|EMU8000_DATA2
mdefine_line|#define EMU8000_DATA2(e)    ((e)-&gt;port2+2)
DECL|macro|EMU8000_DATA3
mdefine_line|#define EMU8000_DATA3(e)    ((e)-&gt;port3)
DECL|macro|EMU8000_PTR
mdefine_line|#define EMU8000_PTR(e)      ((e)-&gt;port3+2)
multiline_comment|/*&n; * Make a command from a register and channel.&n; */
DECL|macro|EMU8000_CMD
mdefine_line|#define EMU8000_CMD(reg, chan) ((reg)&lt;&lt;5 | (chan))
multiline_comment|/*&n; * Commands to read and write the EMU8000 registers.&n; * These macros should be used for all register accesses.&n; */
DECL|macro|EMU8000_CPF_READ
mdefine_line|#define EMU8000_CPF_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(0, (chan)))
DECL|macro|EMU8000_PTRX_READ
mdefine_line|#define EMU8000_PTRX_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (chan)))
DECL|macro|EMU8000_CVCF_READ
mdefine_line|#define EMU8000_CVCF_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(2, (chan)))
DECL|macro|EMU8000_VTFT_READ
mdefine_line|#define EMU8000_VTFT_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(3, (chan)))
DECL|macro|EMU8000_PSST_READ
mdefine_line|#define EMU8000_PSST_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(6, (chan)))
DECL|macro|EMU8000_CSL_READ
mdefine_line|#define EMU8000_CSL_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(7, (chan)))
DECL|macro|EMU8000_CCCA_READ
mdefine_line|#define EMU8000_CCCA_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(0, (chan)))
DECL|macro|EMU8000_HWCF4_READ
mdefine_line|#define EMU8000_HWCF4_READ(emu) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 9))
DECL|macro|EMU8000_HWCF5_READ
mdefine_line|#define EMU8000_HWCF5_READ(emu) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 10))
DECL|macro|EMU8000_HWCF6_READ
mdefine_line|#define EMU8000_HWCF6_READ(emu) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 13))
DECL|macro|EMU8000_SMALR_READ
mdefine_line|#define EMU8000_SMALR_READ(emu) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 20))
DECL|macro|EMU8000_SMARR_READ
mdefine_line|#define EMU8000_SMARR_READ(emu) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 21))
DECL|macro|EMU8000_SMALW_READ
mdefine_line|#define EMU8000_SMALW_READ(emu) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 22))
DECL|macro|EMU8000_SMARW_READ
mdefine_line|#define EMU8000_SMARW_READ(emu) &bslash;&n;&t;snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 23))
DECL|macro|EMU8000_SMLD_READ
mdefine_line|#define EMU8000_SMLD_READ(emu) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 26))
DECL|macro|EMU8000_SMRD_READ
mdefine_line|#define EMU8000_SMRD_READ(emu) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 26))
DECL|macro|EMU8000_WC_READ
mdefine_line|#define EMU8000_WC_READ(emu) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 27))
DECL|macro|EMU8000_HWCF1_READ
mdefine_line|#define EMU8000_HWCF1_READ(emu) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 29))
DECL|macro|EMU8000_HWCF2_READ
mdefine_line|#define EMU8000_HWCF2_READ(emu) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 30))
DECL|macro|EMU8000_HWCF3_READ
mdefine_line|#define EMU8000_HWCF3_READ(emu) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 31))
DECL|macro|EMU8000_INIT1_READ
mdefine_line|#define EMU8000_INIT1_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(2, (chan)))
DECL|macro|EMU8000_INIT2_READ
mdefine_line|#define EMU8000_INIT2_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(2, (chan)))
DECL|macro|EMU8000_INIT3_READ
mdefine_line|#define EMU8000_INIT3_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(3, (chan)))
DECL|macro|EMU8000_INIT4_READ
mdefine_line|#define EMU8000_INIT4_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(3, (chan)))
DECL|macro|EMU8000_ENVVOL_READ
mdefine_line|#define EMU8000_ENVVOL_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(4, (chan)))
DECL|macro|EMU8000_DCYSUSV_READ
mdefine_line|#define EMU8000_DCYSUSV_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(5, (chan)))
DECL|macro|EMU8000_ENVVAL_READ
mdefine_line|#define EMU8000_ENVVAL_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(6, (chan)))
DECL|macro|EMU8000_DCYSUS_READ
mdefine_line|#define EMU8000_DCYSUS_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(7, (chan)))
DECL|macro|EMU8000_ATKHLDV_READ
mdefine_line|#define EMU8000_ATKHLDV_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(4, (chan)))
DECL|macro|EMU8000_LFO1VAL_READ
mdefine_line|#define EMU8000_LFO1VAL_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(5, (chan)))
DECL|macro|EMU8000_ATKHLD_READ
mdefine_line|#define EMU8000_ATKHLD_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(6, (chan)))
DECL|macro|EMU8000_LFO2VAL_READ
mdefine_line|#define EMU8000_LFO2VAL_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(7, (chan)))
DECL|macro|EMU8000_IP_READ
mdefine_line|#define EMU8000_IP_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(0, (chan)))
DECL|macro|EMU8000_IFATN_READ
mdefine_line|#define EMU8000_IFATN_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(1, (chan)))
DECL|macro|EMU8000_PEFE_READ
mdefine_line|#define EMU8000_PEFE_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(2, (chan)))
DECL|macro|EMU8000_FMMOD_READ
mdefine_line|#define EMU8000_FMMOD_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(3, (chan)))
DECL|macro|EMU8000_TREMFRQ_READ
mdefine_line|#define EMU8000_TREMFRQ_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(4, (chan)))
DECL|macro|EMU8000_FM2FRQ2_READ
mdefine_line|#define EMU8000_FM2FRQ2_READ(emu, chan) &bslash;&n;&t;snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(5, (chan)))
DECL|macro|EMU8000_CPF_WRITE
mdefine_line|#define EMU8000_CPF_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(0, (chan)), (val))
DECL|macro|EMU8000_PTRX_WRITE
mdefine_line|#define EMU8000_PTRX_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (chan)), (val))
DECL|macro|EMU8000_CVCF_WRITE
mdefine_line|#define EMU8000_CVCF_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(2, (chan)), (val))
DECL|macro|EMU8000_VTFT_WRITE
mdefine_line|#define EMU8000_VTFT_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(3, (chan)), (val))
DECL|macro|EMU8000_PSST_WRITE
mdefine_line|#define EMU8000_PSST_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(6, (chan)), (val))
DECL|macro|EMU8000_CSL_WRITE
mdefine_line|#define EMU8000_CSL_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(7, (chan)), (val))
DECL|macro|EMU8000_CCCA_WRITE
mdefine_line|#define EMU8000_CCCA_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(0, (chan)), (val))
DECL|macro|EMU8000_HWCF4_WRITE
mdefine_line|#define EMU8000_HWCF4_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 9), (val))
DECL|macro|EMU8000_HWCF5_WRITE
mdefine_line|#define EMU8000_HWCF5_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 10), (val))
DECL|macro|EMU8000_HWCF6_WRITE
mdefine_line|#define EMU8000_HWCF6_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 13), (val))
multiline_comment|/* this register is not documented */
DECL|macro|EMU8000_HWCF7_WRITE
mdefine_line|#define EMU8000_HWCF7_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 14), (val))
DECL|macro|EMU8000_SMALR_WRITE
mdefine_line|#define EMU8000_SMALR_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 20), (val))
DECL|macro|EMU8000_SMARR_WRITE
mdefine_line|#define EMU8000_SMARR_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 21), (val))
DECL|macro|EMU8000_SMALW_WRITE
mdefine_line|#define EMU8000_SMALW_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 22), (val))
DECL|macro|EMU8000_SMARW_WRITE
mdefine_line|#define EMU8000_SMARW_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 23), (val))
DECL|macro|EMU8000_SMLD_WRITE
mdefine_line|#define EMU8000_SMLD_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 26), (val))
DECL|macro|EMU8000_SMRD_WRITE
mdefine_line|#define EMU8000_SMRD_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 26), (val))
DECL|macro|EMU8000_WC_WRITE
mdefine_line|#define EMU8000_WC_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 27), (val))
DECL|macro|EMU8000_HWCF1_WRITE
mdefine_line|#define EMU8000_HWCF1_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 29), (val))
DECL|macro|EMU8000_HWCF2_WRITE
mdefine_line|#define EMU8000_HWCF2_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 30), (val))
DECL|macro|EMU8000_HWCF3_WRITE
mdefine_line|#define EMU8000_HWCF3_WRITE(emu, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 31), (val))
DECL|macro|EMU8000_INIT1_WRITE
mdefine_line|#define EMU8000_INIT1_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(2, (chan)), (val))
DECL|macro|EMU8000_INIT2_WRITE
mdefine_line|#define EMU8000_INIT2_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(2, (chan)), (val))
DECL|macro|EMU8000_INIT3_WRITE
mdefine_line|#define EMU8000_INIT3_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(3, (chan)), (val))
DECL|macro|EMU8000_INIT4_WRITE
mdefine_line|#define EMU8000_INIT4_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(3, (chan)), (val))
DECL|macro|EMU8000_ENVVOL_WRITE
mdefine_line|#define EMU8000_ENVVOL_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(4, (chan)), (val))
DECL|macro|EMU8000_DCYSUSV_WRITE
mdefine_line|#define EMU8000_DCYSUSV_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(5, (chan)), (val))
DECL|macro|EMU8000_ENVVAL_WRITE
mdefine_line|#define EMU8000_ENVVAL_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(6, (chan)), (val))
DECL|macro|EMU8000_DCYSUS_WRITE
mdefine_line|#define EMU8000_DCYSUS_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(7, (chan)), (val))
DECL|macro|EMU8000_ATKHLDV_WRITE
mdefine_line|#define EMU8000_ATKHLDV_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(4, (chan)), (val))
DECL|macro|EMU8000_LFO1VAL_WRITE
mdefine_line|#define EMU8000_LFO1VAL_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(5, (chan)), (val))
DECL|macro|EMU8000_ATKHLD_WRITE
mdefine_line|#define EMU8000_ATKHLD_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(6, (chan)), (val))
DECL|macro|EMU8000_LFO2VAL_WRITE
mdefine_line|#define EMU8000_LFO2VAL_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(7, (chan)), (val))
DECL|macro|EMU8000_IP_WRITE
mdefine_line|#define EMU8000_IP_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(0, (chan)), (val))
DECL|macro|EMU8000_IFATN_WRITE
mdefine_line|#define EMU8000_IFATN_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(1, (chan)), (val))
DECL|macro|EMU8000_PEFE_WRITE
mdefine_line|#define EMU8000_PEFE_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(2, (chan)), (val))
DECL|macro|EMU8000_FMMOD_WRITE
mdefine_line|#define EMU8000_FMMOD_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(3, (chan)), (val))
DECL|macro|EMU8000_TREMFRQ_WRITE
mdefine_line|#define EMU8000_TREMFRQ_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(4, (chan)), (val))
DECL|macro|EMU8000_FM2FRQ2_WRITE
mdefine_line|#define EMU8000_FM2FRQ2_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(5, (chan)), (val))
DECL|macro|EMU8000_0080_WRITE
mdefine_line|#define EMU8000_0080_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(4, (chan)), (val))
DECL|macro|EMU8000_00A0_WRITE
mdefine_line|#define EMU8000_00A0_WRITE(emu, chan, val) &bslash;&n;&t;snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(5, (chan)), (val))
macro_line|#endif /* __SOUND_EMU8000_REG_H */
eof
