multiline_comment|/*&n; * Zoran ZR36060 basic configuration functions - header file&n; *&n; * Copyright (C) 2002 Laurent Pinchart &lt;laurent.pinchart@skynet.be&gt;&n; *&n; * $Id: zr36060.h,v 1.1.1.1.2.3 2003/01/14 21:18:47 rbultje Exp $&n; *&n; * ------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * ------------------------------------------------------------------------&n; */
macro_line|#ifndef ZR36060_H
DECL|macro|ZR36060_H
mdefine_line|#define ZR36060_H
macro_line|#include &quot;videocodec.h&quot;
multiline_comment|/* data stored for each zoran jpeg codec chip */
DECL|struct|zr36060
r_struct
id|zr36060
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* io datastructure */
DECL|member|codec
r_struct
id|videocodec
op_star
id|codec
suffix:semicolon
singleline_comment|// last coder status
DECL|member|status
id|__u8
id|status
suffix:semicolon
singleline_comment|// actual coder setup
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|width
id|__u16
id|width
suffix:semicolon
DECL|member|height
id|__u16
id|height
suffix:semicolon
DECL|member|bitrate_ctrl
id|__u16
id|bitrate_ctrl
suffix:semicolon
DECL|member|total_code_vol
id|__u32
id|total_code_vol
suffix:semicolon
DECL|member|real_code_vol
id|__u32
id|real_code_vol
suffix:semicolon
DECL|member|max_block_vol
id|__u16
id|max_block_vol
suffix:semicolon
DECL|member|h_samp_ratio
id|__u8
id|h_samp_ratio
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|v_samp_ratio
id|__u8
id|v_samp_ratio
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|scalefact
id|__u16
id|scalefact
suffix:semicolon
DECL|member|dri
id|__u16
id|dri
suffix:semicolon
multiline_comment|/* app/com marker data */
DECL|member|app
r_struct
id|jpeg_app_marker
id|app
suffix:semicolon
DECL|member|com
r_struct
id|jpeg_com_marker
id|com
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ZR36060 register addresses */
DECL|macro|ZR060_LOAD
mdefine_line|#define ZR060_LOAD&t;&t;&t;0x000
DECL|macro|ZR060_CFSR
mdefine_line|#define ZR060_CFSR&t;&t;&t;0x001
DECL|macro|ZR060_CIR
mdefine_line|#define ZR060_CIR&t;&t;&t;0x002
DECL|macro|ZR060_CMR
mdefine_line|#define ZR060_CMR&t;&t;&t;0x003
DECL|macro|ZR060_MBZ
mdefine_line|#define ZR060_MBZ&t;&t;&t;0x004
DECL|macro|ZR060_MBCVR
mdefine_line|#define ZR060_MBCVR&t;&t;&t;0x005
DECL|macro|ZR060_MER
mdefine_line|#define ZR060_MER&t;&t;&t;0x006
DECL|macro|ZR060_IMR
mdefine_line|#define ZR060_IMR&t;&t;&t;0x007
DECL|macro|ZR060_ISR
mdefine_line|#define ZR060_ISR&t;&t;&t;0x008
DECL|macro|ZR060_TCV_NET_HI
mdefine_line|#define ZR060_TCV_NET_HI&t;&t;0x009
DECL|macro|ZR060_TCV_NET_MH
mdefine_line|#define ZR060_TCV_NET_MH&t;&t;0x00a
DECL|macro|ZR060_TCV_NET_ML
mdefine_line|#define ZR060_TCV_NET_ML&t;&t;0x00b
DECL|macro|ZR060_TCV_NET_LO
mdefine_line|#define ZR060_TCV_NET_LO&t;&t;0x00c
DECL|macro|ZR060_TCV_DATA_HI
mdefine_line|#define ZR060_TCV_DATA_HI&t;&t;0x00d
DECL|macro|ZR060_TCV_DATA_MH
mdefine_line|#define ZR060_TCV_DATA_MH&t;&t;0x00e
DECL|macro|ZR060_TCV_DATA_ML
mdefine_line|#define ZR060_TCV_DATA_ML&t;&t;0x00f
DECL|macro|ZR060_TCV_DATA_LO
mdefine_line|#define ZR060_TCV_DATA_LO&t;&t;0x010
DECL|macro|ZR060_SF_HI
mdefine_line|#define ZR060_SF_HI&t;&t;&t;0x011
DECL|macro|ZR060_SF_LO
mdefine_line|#define ZR060_SF_LO&t;&t;&t;0x012
DECL|macro|ZR060_AF_HI
mdefine_line|#define ZR060_AF_HI&t;&t;&t;0x013
DECL|macro|ZR060_AF_M
mdefine_line|#define ZR060_AF_M&t;&t;&t;0x014
DECL|macro|ZR060_AF_LO
mdefine_line|#define ZR060_AF_LO&t;&t;&t;0x015
DECL|macro|ZR060_ACV_HI
mdefine_line|#define ZR060_ACV_HI&t;&t;&t;0x016
DECL|macro|ZR060_ACV_MH
mdefine_line|#define ZR060_ACV_MH&t;&t;&t;0x017
DECL|macro|ZR060_ACV_ML
mdefine_line|#define ZR060_ACV_ML&t;&t;&t;0x018
DECL|macro|ZR060_ACV_LO
mdefine_line|#define ZR060_ACV_LO&t;&t;&t;0x019
DECL|macro|ZR060_ACT_HI
mdefine_line|#define ZR060_ACT_HI&t;&t;&t;0x01a
DECL|macro|ZR060_ACT_MH
mdefine_line|#define ZR060_ACT_MH&t;&t;&t;0x01b
DECL|macro|ZR060_ACT_ML
mdefine_line|#define ZR060_ACT_ML&t;&t;&t;0x01c
DECL|macro|ZR060_ACT_LO
mdefine_line|#define ZR060_ACT_LO&t;&t;&t;0x01d
DECL|macro|ZR060_ACV_TRUN_HI
mdefine_line|#define ZR060_ACV_TRUN_HI&t;&t;0x01e
DECL|macro|ZR060_ACV_TRUN_MH
mdefine_line|#define ZR060_ACV_TRUN_MH&t;&t;0x01f
DECL|macro|ZR060_ACV_TRUN_ML
mdefine_line|#define ZR060_ACV_TRUN_ML&t;&t;0x020
DECL|macro|ZR060_ACV_TRUN_LO
mdefine_line|#define ZR060_ACV_TRUN_LO&t;&t;0x021
DECL|macro|ZR060_IDR_DEV
mdefine_line|#define ZR060_IDR_DEV&t;&t;&t;0x022
DECL|macro|ZR060_IDR_REV
mdefine_line|#define ZR060_IDR_REV&t;&t;&t;0x023
DECL|macro|ZR060_TCR_HI
mdefine_line|#define ZR060_TCR_HI&t;&t;&t;0x024
DECL|macro|ZR060_TCR_LO
mdefine_line|#define ZR060_TCR_LO&t;&t;&t;0x025
DECL|macro|ZR060_VCR
mdefine_line|#define ZR060_VCR&t;&t;&t;0x030
DECL|macro|ZR060_VPR
mdefine_line|#define ZR060_VPR&t;&t;&t;0x031
DECL|macro|ZR060_SR
mdefine_line|#define ZR060_SR&t;&t;&t;0x032
DECL|macro|ZR060_BCR_Y
mdefine_line|#define ZR060_BCR_Y&t;&t;&t;0x033
DECL|macro|ZR060_BCR_U
mdefine_line|#define ZR060_BCR_U&t;&t;&t;0x034
DECL|macro|ZR060_BCR_V
mdefine_line|#define ZR060_BCR_V&t;&t;&t;0x035
DECL|macro|ZR060_SGR_VTOTAL_HI
mdefine_line|#define ZR060_SGR_VTOTAL_HI&t;&t;0x036
DECL|macro|ZR060_SGR_VTOTAL_LO
mdefine_line|#define ZR060_SGR_VTOTAL_LO&t;&t;0x037
DECL|macro|ZR060_SGR_HTOTAL_HI
mdefine_line|#define ZR060_SGR_HTOTAL_HI&t;&t;0x038
DECL|macro|ZR060_SGR_HTOTAL_LO
mdefine_line|#define ZR060_SGR_HTOTAL_LO&t;&t;0x039
DECL|macro|ZR060_SGR_VSYNC
mdefine_line|#define ZR060_SGR_VSYNC&t;&t;&t;0x03a
DECL|macro|ZR060_SGR_HSYNC
mdefine_line|#define ZR060_SGR_HSYNC&t;&t;&t;0x03b
DECL|macro|ZR060_SGR_BVSTART
mdefine_line|#define ZR060_SGR_BVSTART&t;&t;0x03c
DECL|macro|ZR060_SGR_BHSTART
mdefine_line|#define ZR060_SGR_BHSTART&t;&t;0x03d
DECL|macro|ZR060_SGR_BVEND_HI
mdefine_line|#define ZR060_SGR_BVEND_HI&t;&t;0x03e
DECL|macro|ZR060_SGR_BVEND_LO
mdefine_line|#define ZR060_SGR_BVEND_LO&t;&t;0x03f
DECL|macro|ZR060_SGR_BHEND_HI
mdefine_line|#define ZR060_SGR_BHEND_HI&t;&t;0x040
DECL|macro|ZR060_SGR_BHEND_LO
mdefine_line|#define ZR060_SGR_BHEND_LO&t;&t;0x041
DECL|macro|ZR060_AAR_VSTART_HI
mdefine_line|#define ZR060_AAR_VSTART_HI&t;&t;0x042
DECL|macro|ZR060_AAR_VSTART_LO
mdefine_line|#define ZR060_AAR_VSTART_LO&t;&t;0x043
DECL|macro|ZR060_AAR_VEND_HI
mdefine_line|#define ZR060_AAR_VEND_HI&t;&t;0x044
DECL|macro|ZR060_AAR_VEND_LO
mdefine_line|#define ZR060_AAR_VEND_LO&t;&t;0x045
DECL|macro|ZR060_AAR_HSTART_HI
mdefine_line|#define ZR060_AAR_HSTART_HI&t;&t;0x046
DECL|macro|ZR060_AAR_HSTART_LO
mdefine_line|#define ZR060_AAR_HSTART_LO&t;&t;0x047
DECL|macro|ZR060_AAR_HEND_HI
mdefine_line|#define ZR060_AAR_HEND_HI&t;&t;0x048
DECL|macro|ZR060_AAR_HEND_LO
mdefine_line|#define ZR060_AAR_HEND_LO&t;&t;0x049
DECL|macro|ZR060_SWR_VSTART_HI
mdefine_line|#define ZR060_SWR_VSTART_HI&t;&t;0x04a
DECL|macro|ZR060_SWR_VSTART_LO
mdefine_line|#define ZR060_SWR_VSTART_LO&t;&t;0x04b
DECL|macro|ZR060_SWR_VEND_HI
mdefine_line|#define ZR060_SWR_VEND_HI&t;&t;0x04c
DECL|macro|ZR060_SWR_VEND_LO
mdefine_line|#define ZR060_SWR_VEND_LO&t;&t;0x04d
DECL|macro|ZR060_SWR_HSTART_HI
mdefine_line|#define ZR060_SWR_HSTART_HI&t;&t;0x04e
DECL|macro|ZR060_SWR_HSTART_LO
mdefine_line|#define ZR060_SWR_HSTART_LO&t;&t;0x04f
DECL|macro|ZR060_SWR_HEND_HI
mdefine_line|#define ZR060_SWR_HEND_HI&t;&t;0x050
DECL|macro|ZR060_SWR_HEND_LO
mdefine_line|#define ZR060_SWR_HEND_LO&t;&t;0x051
DECL|macro|ZR060_SOF_IDX
mdefine_line|#define ZR060_SOF_IDX&t;&t;&t;0x060
DECL|macro|ZR060_SOS_IDX
mdefine_line|#define ZR060_SOS_IDX&t;&t;&t;0x07a
DECL|macro|ZR060_DRI_IDX
mdefine_line|#define ZR060_DRI_IDX&t;&t;&t;0x0c0
DECL|macro|ZR060_DQT_IDX
mdefine_line|#define ZR060_DQT_IDX&t;&t;&t;0x0cc
DECL|macro|ZR060_DHT_IDX
mdefine_line|#define ZR060_DHT_IDX&t;&t;&t;0x1d4
DECL|macro|ZR060_APP_IDX
mdefine_line|#define ZR060_APP_IDX&t;&t;&t;0x380
DECL|macro|ZR060_COM_IDX
mdefine_line|#define ZR060_COM_IDX&t;&t;&t;0x3c0
multiline_comment|/* ZR36060 LOAD register bits */
DECL|macro|ZR060_LOAD_Load
mdefine_line|#define ZR060_LOAD_Load&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|ZR060_LOAD_SyncRst
mdefine_line|#define ZR060_LOAD_SyncRst&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* ZR36060 Code FIFO Status register bits */
DECL|macro|ZR060_CFSR_Busy
mdefine_line|#define ZR060_CFSR_Busy&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|ZR060_CFSR_CBusy
mdefine_line|#define ZR060_CFSR_CBusy&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_CFSR_CFIFO
mdefine_line|#define ZR060_CFSR_CFIFO&t;&t;(3 &lt;&lt; 0)
multiline_comment|/* ZR36060 Code Interface register */
DECL|macro|ZR060_CIR_Code16
mdefine_line|#define ZR060_CIR_Code16&t;&t;(1 &lt;&lt; 7)
DECL|macro|ZR060_CIR_Endian
mdefine_line|#define ZR060_CIR_Endian&t;&t;(1 &lt;&lt; 6)
DECL|macro|ZR060_CIR_CFIS
mdefine_line|#define ZR060_CIR_CFIS&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_CIR_CodeMstr
mdefine_line|#define ZR060_CIR_CodeMstr&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* ZR36060 Codec Mode register */
DECL|macro|ZR060_CMR_Comp
mdefine_line|#define ZR060_CMR_Comp&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|ZR060_CMR_ATP
mdefine_line|#define ZR060_CMR_ATP&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|ZR060_CMR_Pass2
mdefine_line|#define ZR060_CMR_Pass2&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|ZR060_CMR_TLM
mdefine_line|#define ZR060_CMR_TLM&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|ZR060_CMR_BRB
mdefine_line|#define ZR060_CMR_BRB&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_CMR_FSF
mdefine_line|#define ZR060_CMR_FSF&t;&t;&t;(1 &lt;&lt; 1)
multiline_comment|/* ZR36060 Markers Enable register */
DECL|macro|ZR060_MER_App
mdefine_line|#define ZR060_MER_App&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|ZR060_MER_Com
mdefine_line|#define ZR060_MER_Com&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|ZR060_MER_DRI
mdefine_line|#define ZR060_MER_DRI&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|ZR060_MER_DQT
mdefine_line|#define ZR060_MER_DQT&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|ZR060_MER_DHT
mdefine_line|#define ZR060_MER_DHT&t;&t;&t;(1 &lt;&lt; 3)
multiline_comment|/* ZR36060 Interrupt Mask register */
DECL|macro|ZR060_IMR_EOAV
mdefine_line|#define ZR060_IMR_EOAV&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|ZR060_IMR_EOI
mdefine_line|#define ZR060_IMR_EOI&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_IMR_End
mdefine_line|#define ZR060_IMR_End&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|ZR060_IMR_DataErr
mdefine_line|#define ZR060_IMR_DataErr&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* ZR36060 Interrupt Status register */
DECL|macro|ZR060_ISR_ProCnt
mdefine_line|#define ZR060_ISR_ProCnt&t;&t;(3 &lt;&lt; 6)
DECL|macro|ZR060_ISR_EOAV
mdefine_line|#define ZR060_ISR_EOAV&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|ZR060_ISR_EOI
mdefine_line|#define ZR060_ISR_EOI&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_ISR_End
mdefine_line|#define ZR060_ISR_End&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|ZR060_ISR_DataErr
mdefine_line|#define ZR060_ISR_DataErr&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* ZR36060 Video Control register */
DECL|macro|ZR060_VCR_Video8
mdefine_line|#define ZR060_VCR_Video8&t;&t;(1 &lt;&lt; 7)
DECL|macro|ZR060_VCR_Range
mdefine_line|#define ZR060_VCR_Range&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|ZR060_VCR_FIDet
mdefine_line|#define ZR060_VCR_FIDet&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|ZR060_VCR_FIVedge
mdefine_line|#define ZR060_VCR_FIVedge&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_VCR_FIExt
mdefine_line|#define ZR060_VCR_FIExt&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|ZR060_VCR_SyncMstr
mdefine_line|#define ZR060_VCR_SyncMstr&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* ZR36060 Video Polarity register */
DECL|macro|ZR060_VPR_VCLKPol
mdefine_line|#define ZR060_VPR_VCLKPol&t;&t;(1 &lt;&lt; 7)
DECL|macro|ZR060_VPR_PValPol
mdefine_line|#define ZR060_VPR_PValPol&t;&t;(1 &lt;&lt; 6)
DECL|macro|ZR060_VPR_PoePol
mdefine_line|#define ZR060_VPR_PoePol&t;&t;(1 &lt;&lt; 5)
DECL|macro|ZR060_VPR_SImgPol
mdefine_line|#define ZR060_VPR_SImgPol&t;&t;(1 &lt;&lt; 4)
DECL|macro|ZR060_VPR_BLPol
mdefine_line|#define ZR060_VPR_BLPol&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|ZR060_VPR_FIPol
mdefine_line|#define ZR060_VPR_FIPol&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_VPR_HSPol
mdefine_line|#define ZR060_VPR_HSPol&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|ZR060_VPR_VSPol
mdefine_line|#define ZR060_VPR_VSPol&t;&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* ZR36060 Scaling register */
DECL|macro|ZR060_SR_VScale
mdefine_line|#define ZR060_SR_VScale&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|ZR060_SR_HScale2
mdefine_line|#define ZR060_SR_HScale2&t;&t;(1 &lt;&lt; 0)
DECL|macro|ZR060_SR_HScale4
mdefine_line|#define ZR060_SR_HScale4&t;&t;(2 &lt;&lt; 0)
macro_line|#endif&t;&t;&t;&t;/*fndef ZR36060_H */
eof
