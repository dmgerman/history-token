multiline_comment|/*&n; * Driver for Digigram VX222 PCI soundcards&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __VX222_H
DECL|macro|__VX222_H
mdefine_line|#define __VX222_H
macro_line|#include &lt;sound/vx_core.h&gt;
DECL|struct|snd_vx222
r_struct
id|snd_vx222
(brace
DECL|member|core
id|vx_core_t
id|core
suffix:semicolon
multiline_comment|/* h/w config; for PLX and for DSP */
DECL|member|port
r_int
r_int
id|port
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|port_res
r_struct
id|resource
op_star
id|port_res
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|regCDSP
r_int
r_int
id|regCDSP
suffix:semicolon
multiline_comment|/* current CDSP register */
DECL|member|regCFG
r_int
r_int
id|regCFG
suffix:semicolon
multiline_comment|/* current CFG register */
DECL|member|regSELMIC
r_int
r_int
id|regSELMIC
suffix:semicolon
multiline_comment|/* current SELMIC reg. (for VX222 Mic) */
DECL|member|input_level
r_int
id|input_level
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* input level for vx222 mic */
DECL|member|mic_level
r_int
id|mic_level
suffix:semicolon
multiline_comment|/* mic level for vx222 mic */
)brace
suffix:semicolon
multiline_comment|/* we use a lookup table with 148 values, see vx_mixer.c */
DECL|macro|VX2_AKM_LEVEL_MAX
mdefine_line|#define VX2_AKM_LEVEL_MAX&t;0x93
r_extern
r_struct
id|snd_vx_ops
id|vx222_ops
suffix:semicolon
r_extern
r_struct
id|snd_vx_ops
id|vx222_old_ops
suffix:semicolon
multiline_comment|/* Offset of registers with base equal to portDSP. */
DECL|macro|VX_RESET_DMA_REGISTER_OFFSET
mdefine_line|#define VX_RESET_DMA_REGISTER_OFFSET    0x00000008
multiline_comment|/* Constants used to access the INTCSR register. */
DECL|macro|VX_INTCSR_VALUE
mdefine_line|#define VX_INTCSR_VALUE                 0x00000001
DECL|macro|VX_PCI_INTERRUPT_MASK
mdefine_line|#define VX_PCI_INTERRUPT_MASK           0x00000040
multiline_comment|/* Constants used to access the CDSP register (0x20). */
DECL|macro|VX_CDSP_TEST1_MASK
mdefine_line|#define VX_CDSP_TEST1_MASK              0x00000080
DECL|macro|VX_CDSP_TOR1_MASK
mdefine_line|#define VX_CDSP_TOR1_MASK               0x00000040
DECL|macro|VX_CDSP_TOR2_MASK
mdefine_line|#define VX_CDSP_TOR2_MASK               0x00000020
DECL|macro|VX_CDSP_RESERVED0_0_MASK
mdefine_line|#define VX_CDSP_RESERVED0_0_MASK        0x00000010
DECL|macro|VX_CDSP_CODEC_RESET_MASK
mdefine_line|#define VX_CDSP_CODEC_RESET_MASK        0x00000008
DECL|macro|VX_CDSP_VALID_IRQ_MASK
mdefine_line|#define VX_CDSP_VALID_IRQ_MASK          0x00000004
DECL|macro|VX_CDSP_TEST0_MASK
mdefine_line|#define VX_CDSP_TEST0_MASK              0x00000002
DECL|macro|VX_CDSP_DSP_RESET_MASK
mdefine_line|#define VX_CDSP_DSP_RESET_MASK          0x00000001
DECL|macro|VX_CDSP_GPIO_OUT_MASK
mdefine_line|#define VX_CDSP_GPIO_OUT_MASK           0x00000060
DECL|macro|VX_GPIO_OUT_BIT_OFFSET
mdefine_line|#define VX_GPIO_OUT_BIT_OFFSET          5               
singleline_comment|// transform output to bit 0 and 1
multiline_comment|/* Constants used to access the CFG register (0x24). */
DECL|macro|VX_CFG_SYNCDSP_MASK
mdefine_line|#define VX_CFG_SYNCDSP_MASK             0x00000080
DECL|macro|VX_CFG_RESERVED0_0_MASK
mdefine_line|#define VX_CFG_RESERVED0_0_MASK         0x00000040
DECL|macro|VX_CFG_RESERVED1_0_MASK
mdefine_line|#define VX_CFG_RESERVED1_0_MASK         0x00000020
DECL|macro|VX_CFG_RESERVED2_0_MASK
mdefine_line|#define VX_CFG_RESERVED2_0_MASK         0x00000010
DECL|macro|VX_CFG_DATAIN_SEL_MASK
mdefine_line|#define VX_CFG_DATAIN_SEL_MASK          0x00000008     
singleline_comment|// 0 (ana), 1 (UER)
DECL|macro|VX_CFG_RESERVED3_0_MASK
mdefine_line|#define VX_CFG_RESERVED3_0_MASK         0x00000004
DECL|macro|VX_CFG_RESERVED4_0_MASK
mdefine_line|#define VX_CFG_RESERVED4_0_MASK         0x00000002
DECL|macro|VX_CFG_CLOCKIN_SEL_MASK
mdefine_line|#define VX_CFG_CLOCKIN_SEL_MASK         0x00000001     
singleline_comment|// 0 (internal), 1 (AES/EBU)
multiline_comment|/* Constants used to access the STATUS register (0x30). */
DECL|macro|VX_STATUS_DATA_XICOR_MASK
mdefine_line|#define VX_STATUS_DATA_XICOR_MASK       0x00000080
DECL|macro|VX_STATUS_VAL_TEST1_MASK
mdefine_line|#define VX_STATUS_VAL_TEST1_MASK        0x00000040
DECL|macro|VX_STATUS_VAL_TEST0_MASK
mdefine_line|#define VX_STATUS_VAL_TEST0_MASK        0x00000020
DECL|macro|VX_STATUS_RESERVED0_MASK
mdefine_line|#define VX_STATUS_RESERVED0_MASK        0x00000010
DECL|macro|VX_STATUS_VAL_TOR1_MASK
mdefine_line|#define VX_STATUS_VAL_TOR1_MASK         0x00000008
DECL|macro|VX_STATUS_VAL_TOR0_MASK
mdefine_line|#define VX_STATUS_VAL_TOR0_MASK         0x00000004
DECL|macro|VX_STATUS_LEVEL_IN_MASK
mdefine_line|#define VX_STATUS_LEVEL_IN_MASK         0x00000002    
singleline_comment|// 6 dBu (0), 22 dBu (1)
DECL|macro|VX_STATUS_MEMIRQ_MASK
mdefine_line|#define VX_STATUS_MEMIRQ_MASK           0x00000001
DECL|macro|VX_STATUS_GPIO_IN_MASK
mdefine_line|#define VX_STATUS_GPIO_IN_MASK          0x0000000C
DECL|macro|VX_GPIO_IN_BIT_OFFSET
mdefine_line|#define VX_GPIO_IN_BIT_OFFSET           0             
singleline_comment|// leave input as bit 2 and 3
multiline_comment|/* Constants used to access the MICRO INPUT SELECT register (0x40). */
DECL|macro|MICRO_SELECT_INPUT_NORM
mdefine_line|#define MICRO_SELECT_INPUT_NORM        0x00
DECL|macro|MICRO_SELECT_INPUT_MUTE
mdefine_line|#define MICRO_SELECT_INPUT_MUTE        0x01
DECL|macro|MICRO_SELECT_INPUT_LIMIT
mdefine_line|#define MICRO_SELECT_INPUT_LIMIT       0x02
DECL|macro|MICRO_SELECT_INPUT_MASK
mdefine_line|#define MICRO_SELECT_INPUT_MASK        0x03
DECL|macro|MICRO_SELECT_PREAMPLI_G_0
mdefine_line|#define MICRO_SELECT_PREAMPLI_G_0      0x00
DECL|macro|MICRO_SELECT_PREAMPLI_G_1
mdefine_line|#define MICRO_SELECT_PREAMPLI_G_1      0x04
DECL|macro|MICRO_SELECT_PREAMPLI_G_2
mdefine_line|#define MICRO_SELECT_PREAMPLI_G_2      0x08
DECL|macro|MICRO_SELECT_PREAMPLI_G_3
mdefine_line|#define MICRO_SELECT_PREAMPLI_G_3      0x0C
DECL|macro|MICRO_SELECT_PREAMPLI_MASK
mdefine_line|#define MICRO_SELECT_PREAMPLI_MASK     0x0C
DECL|macro|MICRO_SELECT_PREAMPLI_OFFSET
mdefine_line|#define MICRO_SELECT_PREAMPLI_OFFSET   2
DECL|macro|MICRO_SELECT_RAISE_COMPR
mdefine_line|#define MICRO_SELECT_RAISE_COMPR       0x10
DECL|macro|MICRO_SELECT_NOISE_T_52DB
mdefine_line|#define MICRO_SELECT_NOISE_T_52DB      0x00
DECL|macro|MICRO_SELECT_NOISE_T_42DB
mdefine_line|#define MICRO_SELECT_NOISE_T_42DB      0x20
DECL|macro|MICRO_SELECT_NOISE_T_32DB
mdefine_line|#define MICRO_SELECT_NOISE_T_32DB      0x40
DECL|macro|MICRO_SELECT_NOISE_T_MASK
mdefine_line|#define MICRO_SELECT_NOISE_T_MASK      0x60
DECL|macro|MICRO_SELECT_PHANTOM_ALIM
mdefine_line|#define MICRO_SELECT_PHANTOM_ALIM      0x80
macro_line|#endif /* __VX222_H */
eof
