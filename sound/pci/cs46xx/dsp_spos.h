multiline_comment|/*&n; *  The driver for the Cirrus Logic&squot;s Sound Fusion CS46XX based soundcards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/*&n; * 2002-07 Benny Sjostrand benny@hostmobility.com&n; */
macro_line|#ifdef  CONFIG_SND_CS46XX_NEW_DSP /* hack ... */
macro_line|#ifndef __DSP_SPOS_H__
DECL|macro|__DSP_SPOS_H__
mdefine_line|#define __DSP_SPOS_H__
DECL|macro|DSP_MAX_SYMBOLS
mdefine_line|#define DSP_MAX_SYMBOLS 1024
DECL|macro|DSP_MAX_MODULES
mdefine_line|#define DSP_MAX_MODULES 64
DECL|macro|DSP_CODE_BYTE_SIZE
mdefine_line|#define DSP_CODE_BYTE_SIZE             0x00007000UL
DECL|macro|DSP_PARAMETER_BYTE_SIZE
mdefine_line|#define DSP_PARAMETER_BYTE_SIZE        0x00003000UL
DECL|macro|DSP_SAMPLE_BYTE_SIZE
mdefine_line|#define DSP_SAMPLE_BYTE_SIZE           0x00003800UL
DECL|macro|DSP_PARAMETER_BYTE_OFFSET
mdefine_line|#define DSP_PARAMETER_BYTE_OFFSET      0x00000000UL
DECL|macro|DSP_SAMPLE_BYTE_OFFSET
mdefine_line|#define DSP_SAMPLE_BYTE_OFFSET         0x00010000UL
DECL|macro|DSP_CODE_BYTE_OFFSET
mdefine_line|#define DSP_CODE_BYTE_OFFSET           0x00020000UL
DECL|macro|WIDE_INSTR_MASK
mdefine_line|#define WIDE_INSTR_MASK       0x0040
DECL|macro|WIDE_LADD_INSTR_MASK
mdefine_line|#define WIDE_LADD_INSTR_MASK  0x0380
multiline_comment|/* this instruction types&n;   needs to be reallocated when load&n;   code into DSP */
r_typedef
r_enum
(brace
DECL|enumerator|WIDE_FOR_BEGIN_LOOP
id|WIDE_FOR_BEGIN_LOOP
op_assign
l_int|0x20
comma
DECL|enumerator|WIDE_FOR_BEGIN_LOOP2
id|WIDE_FOR_BEGIN_LOOP2
comma
DECL|enumerator|WIDE_COND_GOTO_ADDR
id|WIDE_COND_GOTO_ADDR
op_assign
l_int|0x30
comma
DECL|enumerator|WIDE_COND_GOTO_CALL
id|WIDE_COND_GOTO_CALL
comma
DECL|enumerator|WIDE_TBEQ_COND_GOTO_ADDR
id|WIDE_TBEQ_COND_GOTO_ADDR
op_assign
l_int|0x70
comma
DECL|enumerator|WIDE_TBEQ_COND_CALL_ADDR
id|WIDE_TBEQ_COND_CALL_ADDR
comma
DECL|enumerator|WIDE_TBEQ_NCOND_GOTO_ADDR
id|WIDE_TBEQ_NCOND_GOTO_ADDR
comma
DECL|enumerator|WIDE_TBEQ_NCOND_CALL_ADDR
id|WIDE_TBEQ_NCOND_CALL_ADDR
comma
DECL|enumerator|WIDE_TBEQ_COND_GOTO1_ADDR
id|WIDE_TBEQ_COND_GOTO1_ADDR
comma
DECL|enumerator|WIDE_TBEQ_COND_CALL1_ADDR
id|WIDE_TBEQ_COND_CALL1_ADDR
comma
DECL|enumerator|WIDE_TBEQ_NCOND_GOTOI_ADDR
id|WIDE_TBEQ_NCOND_GOTOI_ADDR
comma
DECL|enumerator|WIDE_TBEQ_NCOND_CALL1_ADDR
id|WIDE_TBEQ_NCOND_CALL1_ADDR
comma
DECL|typedef|wide_opcode_t
)brace
id|wide_opcode_t
suffix:semicolon
multiline_comment|/* SAMPLE segment */
DECL|macro|VARI_DECIMATE_BUF1
mdefine_line|#define VARI_DECIMATE_BUF1       0x0000
DECL|macro|WRITE_BACK_BUF1
mdefine_line|#define WRITE_BACK_BUF1          0x0400
DECL|macro|CODEC_INPUT_BUF1
mdefine_line|#define CODEC_INPUT_BUF1         0x0500
DECL|macro|PCM_READER_BUF1
mdefine_line|#define PCM_READER_BUF1          0x0600
DECL|macro|SRC_DELAY_BUF1
mdefine_line|#define SRC_DELAY_BUF1           0x0680
DECL|macro|VARI_DECIMATE_BUF0
mdefine_line|#define VARI_DECIMATE_BUF0       0x0780
DECL|macro|SRC_OUTPUT_BUF1
mdefine_line|#define SRC_OUTPUT_BUF1          0x07A0
DECL|macro|ASYNC_IP_OUTPUT_BUFFER1
mdefine_line|#define ASYNC_IP_OUTPUT_BUFFER1  0x0A00
DECL|macro|OUTPUT_SNOOP_BUFFER
mdefine_line|#define OUTPUT_SNOOP_BUFFER      0x0B00
DECL|macro|SPDIFI_IP_OUTPUT_BUFFER1
mdefine_line|#define SPDIFI_IP_OUTPUT_BUFFER1 0x0E00
DECL|macro|SPDIFO_IP_OUTPUT_BUFFER1
mdefine_line|#define SPDIFO_IP_OUTPUT_BUFFER1 0x1000
DECL|macro|MIX_SAMPLE_BUF1
mdefine_line|#define MIX_SAMPLE_BUF1          0x1400
DECL|macro|MIX_SAMPLE_BUF2
mdefine_line|#define MIX_SAMPLE_BUF2          0x2D00
DECL|macro|MIX_SAMPLE_BUF3
mdefine_line|#define MIX_SAMPLE_BUF3          0x2E00
DECL|macro|MIX_SAMPLE_BUF4
mdefine_line|#define MIX_SAMPLE_BUF4          0x2F00
DECL|macro|MIX_SAMPLE_BUF5
mdefine_line|#define MIX_SAMPLE_BUF5          0x3000
multiline_comment|/* Task stack address */
DECL|macro|HFG_STACK
mdefine_line|#define HFG_STACK                0x066A
DECL|macro|FG_STACK
mdefine_line|#define FG_STACK                 0x066E
DECL|macro|BG_STACK
mdefine_line|#define BG_STACK                 0x068E
multiline_comment|/* SCB&squot;s addresses */
DECL|macro|SPOSCB_ADDR
mdefine_line|#define SPOSCB_ADDR              0x070
DECL|macro|BG_TREE_SCB_ADDR
mdefine_line|#define BG_TREE_SCB_ADDR         0x635
DECL|macro|NULL_SCB_ADDR
mdefine_line|#define NULL_SCB_ADDR            0x000
DECL|macro|TIMINGMASTER_SCB_ADDR
mdefine_line|#define TIMINGMASTER_SCB_ADDR    0x010
DECL|macro|CODECOUT_SCB_ADDR
mdefine_line|#define CODECOUT_SCB_ADDR        0x020
DECL|macro|PCMREADER_SCB_ADDR
mdefine_line|#define PCMREADER_SCB_ADDR       0x030
DECL|macro|WRITEBACK_SCB_ADDR
mdefine_line|#define WRITEBACK_SCB_ADDR       0x040
DECL|macro|CODECIN_SCB_ADDR
mdefine_line|#define CODECIN_SCB_ADDR         0x080
DECL|macro|MASTERMIX_SCB_ADDR
mdefine_line|#define MASTERMIX_SCB_ADDR       0x090
DECL|macro|SRCTASK_SCB_ADDR
mdefine_line|#define SRCTASK_SCB_ADDR         0x0A0
DECL|macro|VARIDECIMATE_SCB_ADDR
mdefine_line|#define VARIDECIMATE_SCB_ADDR    0x0B0
DECL|macro|PCMSERIALIN_SCB_ADDR
mdefine_line|#define PCMSERIALIN_SCB_ADDR     0x0C0
DECL|macro|FG_TASK_HEADER_ADDR
mdefine_line|#define FG_TASK_HEADER_ADDR      0x600
DECL|macro|ASYNCTX_SCB_ADDR
mdefine_line|#define ASYNCTX_SCB_ADDR         0x0E0
DECL|macro|ASYNCRX_SCB_ADDR
mdefine_line|#define ASYNCRX_SCB_ADDR         0x0F0
DECL|macro|SRCTASKII_SCB_ADDR
mdefine_line|#define SRCTASKII_SCB_ADDR       0x100
DECL|macro|OUTPUTSNOOP_SCB_ADDR
mdefine_line|#define OUTPUTSNOOP_SCB_ADDR     0x110
DECL|macro|PCMSERIALINII_SCB_ADDR
mdefine_line|#define PCMSERIALINII_SCB_ADDR   0x120
DECL|macro|SPIOWRITE_SCB_ADDR
mdefine_line|#define SPIOWRITE_SCB_ADDR       0x130
DECL|macro|SEC_CODECOUT_SCB_ADDR
mdefine_line|#define SEC_CODECOUT_SCB_ADDR    0x140
DECL|macro|OUTPUTSNOOPII_SCB_ADDR
mdefine_line|#define OUTPUTSNOOPII_SCB_ADDR   0x150
DECL|macro|PCMSERIALIN_PCM_SCB_ADDR
mdefine_line|#define PCMSERIALIN_PCM_SCB_ADDR 0x160
DECL|macro|RECORD_MIXER_SCB_ADDR
mdefine_line|#define RECORD_MIXER_SCB_ADDR    0x170
DECL|macro|REAR_MIXER_SCB_ADDR
mdefine_line|#define REAR_MIXER_SCB_ADDR      0x180
DECL|macro|SPDIF_MIXER_SCB_ADDR
mdefine_line|#define SPDIF_MIXER_SCB_ADDR     0x190
multiline_comment|/* hyperforground SCB&squot;s*/
DECL|macro|HFG_TREE_SCB
mdefine_line|#define HFG_TREE_SCB             0xBA0
DECL|macro|SPDIFI_SCB_INST
mdefine_line|#define SPDIFI_SCB_INST          0xBB0
DECL|macro|SPDIFO_SCB_INST
mdefine_line|#define SPDIFO_SCB_INST          0xBC0
DECL|macro|WRITE_BACK_SPB
mdefine_line|#define WRITE_BACK_SPB           0x0D0
multiline_comment|/* offsets */
DECL|macro|AsyncCIOFIFOPointer
mdefine_line|#define AsyncCIOFIFOPointer  0xd
DECL|macro|SPDIFOFIFOPointer
mdefine_line|#define SPDIFOFIFOPointer    0xd
DECL|macro|SPDIFIFIFOPointer
mdefine_line|#define SPDIFIFIFOPointer    0xd
DECL|macro|TCBData
mdefine_line|#define TCBData              0xb
DECL|macro|HFGFlags
mdefine_line|#define HFGFlags             0xa
DECL|macro|TCBContextBlk
mdefine_line|#define TCBContextBlk        0x10
DECL|macro|AFGTxAccumPhi
mdefine_line|#define AFGTxAccumPhi        0x4
DECL|macro|SCBsubListPtr
mdefine_line|#define SCBsubListPtr        0x9
DECL|macro|SCBfuncEntryPtr
mdefine_line|#define SCBfuncEntryPtr      0xA
DECL|macro|SRCCorPerGof
mdefine_line|#define SRCCorPerGof         0x2
DECL|macro|SRCPhiIncr6Int26Frac
mdefine_line|#define SRCPhiIncr6Int26Frac 0xd
DECL|macro|SCBVolumeCtrl
mdefine_line|#define SCBVolumeCtrl        0xe
multiline_comment|/* conf */
DECL|macro|UseASER1Input
mdefine_line|#define UseASER1Input 1
multiline_comment|/*&n; * The following defines are for the flags in the rsConfig01/23 registers of&n; * the SP.&n; */
DECL|macro|RSCONFIG_MODULO_SIZE_MASK
mdefine_line|#define RSCONFIG_MODULO_SIZE_MASK               0x0000000FL
DECL|macro|RSCONFIG_MODULO_16
mdefine_line|#define RSCONFIG_MODULO_16                      0x00000001L
DECL|macro|RSCONFIG_MODULO_32
mdefine_line|#define RSCONFIG_MODULO_32                      0x00000002L
DECL|macro|RSCONFIG_MODULO_64
mdefine_line|#define RSCONFIG_MODULO_64                      0x00000003L
DECL|macro|RSCONFIG_MODULO_128
mdefine_line|#define RSCONFIG_MODULO_128                     0x00000004L
DECL|macro|RSCONFIG_MODULO_256
mdefine_line|#define RSCONFIG_MODULO_256                     0x00000005L
DECL|macro|RSCONFIG_MODULO_512
mdefine_line|#define RSCONFIG_MODULO_512                     0x00000006L
DECL|macro|RSCONFIG_MODULO_1024
mdefine_line|#define RSCONFIG_MODULO_1024                    0x00000007L
DECL|macro|RSCONFIG_MODULO_4
mdefine_line|#define RSCONFIG_MODULO_4                       0x00000008L
DECL|macro|RSCONFIG_MODULO_8
mdefine_line|#define RSCONFIG_MODULO_8                       0x00000009L
DECL|macro|RSCONFIG_SAMPLE_SIZE_MASK
mdefine_line|#define RSCONFIG_SAMPLE_SIZE_MASK               0x000000C0L
DECL|macro|RSCONFIG_SAMPLE_8MONO
mdefine_line|#define RSCONFIG_SAMPLE_8MONO                   0x00000000L
DECL|macro|RSCONFIG_SAMPLE_8STEREO
mdefine_line|#define RSCONFIG_SAMPLE_8STEREO                 0x00000040L
DECL|macro|RSCONFIG_SAMPLE_16MONO
mdefine_line|#define RSCONFIG_SAMPLE_16MONO                  0x00000080L
DECL|macro|RSCONFIG_SAMPLE_16STEREO
mdefine_line|#define RSCONFIG_SAMPLE_16STEREO                0x000000C0L
DECL|macro|RSCONFIG_UNDERRUN_ZERO
mdefine_line|#define RSCONFIG_UNDERRUN_ZERO                  0x00004000L
DECL|macro|RSCONFIG_DMA_TO_HOST
mdefine_line|#define RSCONFIG_DMA_TO_HOST                    0x00008000L
DECL|macro|RSCONFIG_STREAM_NUM_MASK
mdefine_line|#define RSCONFIG_STREAM_NUM_MASK                0x00FF0000L
DECL|macro|RSCONFIG_MAX_DMA_SIZE_MASK
mdefine_line|#define RSCONFIG_MAX_DMA_SIZE_MASK              0x1F000000L
DECL|macro|RSCONFIG_DMA_ENABLE
mdefine_line|#define RSCONFIG_DMA_ENABLE                     0x20000000L
DECL|macro|RSCONFIG_PRIORITY_MASK
mdefine_line|#define RSCONFIG_PRIORITY_MASK                  0xC0000000L
DECL|macro|RSCONFIG_PRIORITY_HIGH
mdefine_line|#define RSCONFIG_PRIORITY_HIGH                  0x00000000L
DECL|macro|RSCONFIG_PRIORITY_MEDIUM_HIGH
mdefine_line|#define RSCONFIG_PRIORITY_MEDIUM_HIGH           0x40000000L
DECL|macro|RSCONFIG_PRIORITY_MEDIUM_LOW
mdefine_line|#define RSCONFIG_PRIORITY_MEDIUM_LOW            0x80000000L
DECL|macro|RSCONFIG_PRIORITY_LOW
mdefine_line|#define RSCONFIG_PRIORITY_LOW                   0xC0000000L
DECL|macro|RSCONFIG_STREAM_NUM_SHIFT
mdefine_line|#define RSCONFIG_STREAM_NUM_SHIFT               16L
DECL|macro|RSCONFIG_MAX_DMA_SIZE_SHIFT
mdefine_line|#define RSCONFIG_MAX_DMA_SIZE_SHIFT             24L
multiline_comment|/* SP constants */
DECL|macro|FG_INTERVAL_TIMER_PERIOD
mdefine_line|#define FG_INTERVAL_TIMER_PERIOD                0x0051
DECL|macro|BG_INTERVAL_TIMER_PERIOD
mdefine_line|#define BG_INTERVAL_TIMER_PERIOD                0x0100
multiline_comment|/* Only SP accessible registers */
DECL|macro|SP_ASER_COUNTDOWN
mdefine_line|#define SP_ASER_COUNTDOWN 0x8040
DECL|macro|SP_SPDOUT_FIFO
mdefine_line|#define SP_SPDOUT_FIFO    0x0108
DECL|macro|SP_SPDIN_MI_FIFO
mdefine_line|#define SP_SPDIN_MI_FIFO  0x01E0
DECL|macro|SP_SPDIN_D_FIFO
mdefine_line|#define SP_SPDIN_D_FIFO   0x01F0
DECL|macro|SP_SPDIN_STATUS
mdefine_line|#define SP_SPDIN_STATUS   0x8048
DECL|macro|SP_SPDIN_CONTROL
mdefine_line|#define SP_SPDIN_CONTROL  0x8049
DECL|macro|SP_SPDIN_FIFOPTR
mdefine_line|#define SP_SPDIN_FIFOPTR  0x804A
DECL|macro|SP_SPDOUT_STATUS
mdefine_line|#define SP_SPDOUT_STATUS  0x804C
DECL|macro|SP_SPDOUT_CONTROL
mdefine_line|#define SP_SPDOUT_CONTROL 0x804D
DECL|macro|SP_SPDOUT_CSUV
mdefine_line|#define SP_SPDOUT_CSUV    0x808E
DECL|function|_wrap_all_bits
r_static
r_inline
id|u8
id|_wrap_all_bits
(paren
id|u8
id|val
)paren
(brace
id|u8
id|wrapped
suffix:semicolon
multiline_comment|/* wrap all 8 bits */
id|wrapped
op_assign
(paren
(paren
id|val
op_amp
l_int|0x1
)paren
op_lshift
l_int|7
)paren
op_or
(paren
(paren
id|val
op_amp
l_int|0x2
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|val
op_amp
l_int|0x4
)paren
op_lshift
l_int|3
)paren
op_or
(paren
(paren
id|val
op_amp
l_int|0x8
)paren
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|val
op_amp
l_int|0x10
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|val
op_amp
l_int|0x20
)paren
op_rshift
l_int|3
)paren
op_or
(paren
(paren
id|val
op_amp
l_int|0x40
)paren
op_rshift
l_int|5
)paren
op_or
(paren
(paren
id|val
op_amp
l_int|0x80
)paren
op_rshift
l_int|7
)paren
suffix:semicolon
r_return
id|wrapped
suffix:semicolon
)brace
DECL|function|cs46xx_dsp_spos_update_scb
r_static
r_inline
r_void
id|cs46xx_dsp_spos_update_scb
(paren
id|cs46xx_t
op_star
id|chip
comma
id|dsp_scb_descriptor_t
op_star
id|scb
)paren
(brace
multiline_comment|/* update nextSCB and subListPtr in SCB */
id|snd_cs46xx_poke
c_func
(paren
id|chip
comma
(paren
id|scb-&gt;address
op_plus
id|SCBsubListPtr
)paren
op_lshift
l_int|2
comma
(paren
id|scb-&gt;sub_list_ptr-&gt;address
op_lshift
l_int|0x10
)paren
op_or
(paren
id|scb-&gt;next_scb_ptr-&gt;address
)paren
)paren
suffix:semicolon
)brace
DECL|function|cs46xx_dsp_scb_set_volume
r_static
r_inline
r_void
id|cs46xx_dsp_scb_set_volume
(paren
id|cs46xx_t
op_star
id|chip
comma
id|dsp_scb_descriptor_t
op_star
id|scb
comma
id|u16
id|left
comma
id|u16
id|right
)paren
(brace
r_int
r_int
id|val
op_assign
(paren
(paren
l_int|0xffff
op_minus
id|left
)paren
op_lshift
l_int|16
op_or
(paren
l_int|0xffff
op_minus
id|right
)paren
)paren
suffix:semicolon
id|snd_cs46xx_poke
c_func
(paren
id|chip
comma
(paren
id|scb-&gt;address
op_plus
id|SCBVolumeCtrl
)paren
op_lshift
l_int|2
comma
id|val
)paren
suffix:semicolon
id|snd_cs46xx_poke
c_func
(paren
id|chip
comma
(paren
id|scb-&gt;address
op_plus
id|SCBVolumeCtrl
op_plus
l_int|1
)paren
op_lshift
l_int|2
comma
id|val
)paren
suffix:semicolon
)brace
macro_line|#endif /* __DSP_SPOS_H__ */
macro_line|#endif /* CONFIG_SND_CS46XX_NEW_DSP  */
eof
