multiline_comment|/*&n; * Driver for Digigram VXpocket soundcards&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __VXPOCKET_H
DECL|macro|__VXPOCKET_H
mdefine_line|#define __VXPOCKET_H
macro_line|#include &lt;sound/vx_core.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
DECL|struct|snd_vxp_entry
r_struct
id|snd_vxp_entry
(brace
DECL|member|dev_info
id|dev_info_t
op_star
id|dev_info
suffix:semicolon
multiline_comment|/* module parameters */
DECL|member|index_table
r_int
op_star
id|index_table
suffix:semicolon
DECL|member|id_table
r_char
op_star
op_star
id|id_table
suffix:semicolon
DECL|member|enable_table
r_int
op_star
id|enable_table
suffix:semicolon
DECL|member|ibl
r_int
op_star
id|ibl
suffix:semicolon
multiline_comment|/* h/w config */
DECL|member|hardware
r_struct
id|snd_vx_hardware
op_star
id|hardware
suffix:semicolon
DECL|member|ops
r_struct
id|snd_vx_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* slots */
DECL|member|card_list
id|vx_core_t
op_star
id|card_list
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
DECL|member|dev_list
id|dev_link_t
op_star
id|dev_list
suffix:semicolon
multiline_comment|/* Linked list of devices */
)brace
suffix:semicolon
DECL|struct|snd_vxpocket
r_struct
id|snd_vxpocket
(brace
DECL|member|core
id|vx_core_t
id|core
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|mic_level
r_int
id|mic_level
suffix:semicolon
multiline_comment|/* analog mic level (or boost) */
DECL|member|regCDSP
r_int
r_int
id|regCDSP
suffix:semicolon
multiline_comment|/* current CDSP register */
DECL|member|regDIALOG
r_int
r_int
id|regDIALOG
suffix:semicolon
multiline_comment|/* current DIALOG register */
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|hw_entry
r_struct
id|snd_vxp_entry
op_star
id|hw_entry
suffix:semicolon
multiline_comment|/* pcmcia stuff */
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|snd_vx_ops
id|snd_vxpocket_ops
suffix:semicolon
r_void
id|vx_set_mic_boost
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|boost
)paren
suffix:semicolon
r_void
id|vx_set_mic_level
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|level
)paren
suffix:semicolon
multiline_comment|/*&n; * pcmcia stuff&n; */
id|dev_link_t
op_star
id|snd_vxpocket_attach
c_func
(paren
r_struct
id|snd_vxp_entry
op_star
id|hw
)paren
suffix:semicolon
r_void
id|snd_vxpocket_detach
c_func
(paren
r_struct
id|snd_vxp_entry
op_star
id|hw
comma
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_int
id|vxp_add_mic_controls
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/* Constants used to access the CDSP register (0x08). */
DECL|macro|CDSP_MAGIC
mdefine_line|#define CDSP_MAGIC&t;0xA7&t;/* magic value (for read) */
multiline_comment|/* for write */
DECL|macro|VXP_CDSP_CLOCKIN_SEL_MASK
mdefine_line|#define VXP_CDSP_CLOCKIN_SEL_MASK&t;0x80&t;/* 0 (internal), 1 (AES/EBU) */
DECL|macro|VXP_CDSP_DATAIN_SEL_MASK
mdefine_line|#define VXP_CDSP_DATAIN_SEL_MASK&t;0x40&t;/* 0 (analog), 1 (UER) */
DECL|macro|VXP_CDSP_SMPTE_SEL_MASK
mdefine_line|#define VXP_CDSP_SMPTE_SEL_MASK&t;&t;0x20
DECL|macro|VXP_CDSP_RESERVED_MASK
mdefine_line|#define VXP_CDSP_RESERVED_MASK&t;&t;0x10
DECL|macro|VXP_CDSP_MIC_SEL_MASK
mdefine_line|#define VXP_CDSP_MIC_SEL_MASK&t;&t;0x08
DECL|macro|VXP_CDSP_VALID_IRQ_MASK
mdefine_line|#define VXP_CDSP_VALID_IRQ_MASK&t;&t;0x04
DECL|macro|VXP_CDSP_CODEC_RESET_MASK
mdefine_line|#define VXP_CDSP_CODEC_RESET_MASK&t;0x02
DECL|macro|VXP_CDSP_DSP_RESET_MASK
mdefine_line|#define VXP_CDSP_DSP_RESET_MASK&t;&t;0x01
multiline_comment|/* VXPOCKET 240/440 */
DECL|macro|P24_CDSP_MICS_SEL_MASK
mdefine_line|#define P24_CDSP_MICS_SEL_MASK&t;&t;0x18
DECL|macro|P24_CDSP_MIC20_SEL_MASK
mdefine_line|#define P24_CDSP_MIC20_SEL_MASK&t;&t;0x10
DECL|macro|P24_CDSP_MIC38_SEL_MASK
mdefine_line|#define P24_CDSP_MIC38_SEL_MASK&t;&t;0x08
multiline_comment|/* Constants used to access the MEMIRQ register (0x0C). */
DECL|macro|P44_MEMIRQ_MASTER_SLAVE_SEL_MASK
mdefine_line|#define P44_MEMIRQ_MASTER_SLAVE_SEL_MASK 0x08
DECL|macro|P44_MEMIRQ_SYNCED_ALONE_SEL_MASK
mdefine_line|#define P44_MEMIRQ_SYNCED_ALONE_SEL_MASK 0x04
DECL|macro|P44_MEMIRQ_WCLK_OUT_IN_SEL_MASK
mdefine_line|#define P44_MEMIRQ_WCLK_OUT_IN_SEL_MASK  0x02 /* Not used */
DECL|macro|P44_MEMIRQ_WCLK_UER_SEL_MASK
mdefine_line|#define P44_MEMIRQ_WCLK_UER_SEL_MASK     0x01 /* Not used */
multiline_comment|/* Micro levels (0x0C) */
multiline_comment|/* Constants used to access the DIALOG register (0x0D). */
DECL|macro|VXP_DLG_XILINX_REPROG_MASK
mdefine_line|#define VXP_DLG_XILINX_REPROG_MASK&t;0x80&t;/* W */
DECL|macro|VXP_DLG_DATA_XICOR_MASK
mdefine_line|#define VXP_DLG_DATA_XICOR_MASK&t;&t;0x80&t;/* R */
DECL|macro|VXP_DLG_RESERVED4_0_MASK
mdefine_line|#define VXP_DLG_RESERVED4_0_MASK&t;0x40
DECL|macro|VXP_DLG_RESERVED2_0_MASK
mdefine_line|#define VXP_DLG_RESERVED2_0_MASK&t;0x20
DECL|macro|VXP_DLG_RESERVED1_0_MASK
mdefine_line|#define VXP_DLG_RESERVED1_0_MASK&t;0x10
DECL|macro|VXP_DLG_DMAWRITE_SEL_MASK
mdefine_line|#define VXP_DLG_DMAWRITE_SEL_MASK&t;0x08&t;/* W */
DECL|macro|VXP_DLG_DMAREAD_SEL_MASK
mdefine_line|#define VXP_DLG_DMAREAD_SEL_MASK&t;0x04&t;/* W */
DECL|macro|VXP_DLG_MEMIRQ_MASK
mdefine_line|#define VXP_DLG_MEMIRQ_MASK&t;&t;0x02&t;/* R */
DECL|macro|VXP_DLG_DMA16_SEL_MASK
mdefine_line|#define VXP_DLG_DMA16_SEL_MASK&t;&t;0x02&t;/* W */
DECL|macro|VXP_DLG_ACK_MEMIRQ_MASK
mdefine_line|#define VXP_DLG_ACK_MEMIRQ_MASK&t;&t;0x01&t;/* R/W */
macro_line|#endif /* __VXPOCKET_H */
eof
