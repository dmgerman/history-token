multiline_comment|/*&n; * Zoran ZR36050 basic configuration functions - header file&n; *&n; * Copyright (C) 2001 Wolfgang Scherr &lt;scherr@net4you.at&gt;&n; *&n; * $Id: zr36050.h,v 1.1.2.2 2003/01/14 21:18:22 rbultje Exp $&n; *&n; * ------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * ------------------------------------------------------------------------&n; */
macro_line|#ifndef ZR36050_H
DECL|macro|ZR36050_H
mdefine_line|#define ZR36050_H
macro_line|#include &quot;videocodec.h&quot;
multiline_comment|/* data stored for each zoran jpeg codec chip */
DECL|struct|zr36050
r_struct
id|zr36050
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
DECL|member|status1
id|__u8
id|status1
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
multiline_comment|/* com/app marker */
DECL|member|com
r_struct
id|jpeg_com_marker
id|com
suffix:semicolon
DECL|member|app
r_struct
id|jpeg_app_marker
id|app
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* zr36050 register addresses */
DECL|macro|ZR050_GO
mdefine_line|#define ZR050_GO                  0x000
DECL|macro|ZR050_HARDWARE
mdefine_line|#define ZR050_HARDWARE            0x002
DECL|macro|ZR050_MODE
mdefine_line|#define ZR050_MODE                0x003
DECL|macro|ZR050_OPTIONS
mdefine_line|#define ZR050_OPTIONS             0x004
DECL|macro|ZR050_MBCV
mdefine_line|#define ZR050_MBCV                0x005
DECL|macro|ZR050_MARKERS_EN
mdefine_line|#define ZR050_MARKERS_EN          0x006
DECL|macro|ZR050_INT_REQ_0
mdefine_line|#define ZR050_INT_REQ_0           0x007
DECL|macro|ZR050_INT_REQ_1
mdefine_line|#define ZR050_INT_REQ_1           0x008
DECL|macro|ZR050_TCV_NET_HI
mdefine_line|#define ZR050_TCV_NET_HI          0x009
DECL|macro|ZR050_TCV_NET_MH
mdefine_line|#define ZR050_TCV_NET_MH          0x00a
DECL|macro|ZR050_TCV_NET_ML
mdefine_line|#define ZR050_TCV_NET_ML          0x00b
DECL|macro|ZR050_TCV_NET_LO
mdefine_line|#define ZR050_TCV_NET_LO          0x00c
DECL|macro|ZR050_TCV_DATA_HI
mdefine_line|#define ZR050_TCV_DATA_HI         0x00d
DECL|macro|ZR050_TCV_DATA_MH
mdefine_line|#define ZR050_TCV_DATA_MH         0x00e
DECL|macro|ZR050_TCV_DATA_ML
mdefine_line|#define ZR050_TCV_DATA_ML         0x00f
DECL|macro|ZR050_TCV_DATA_LO
mdefine_line|#define ZR050_TCV_DATA_LO         0x010
DECL|macro|ZR050_SF_HI
mdefine_line|#define ZR050_SF_HI               0x011
DECL|macro|ZR050_SF_LO
mdefine_line|#define ZR050_SF_LO               0x012
DECL|macro|ZR050_AF_HI
mdefine_line|#define ZR050_AF_HI               0x013
DECL|macro|ZR050_AF_M
mdefine_line|#define ZR050_AF_M                0x014
DECL|macro|ZR050_AF_LO
mdefine_line|#define ZR050_AF_LO               0x015
DECL|macro|ZR050_ACV_HI
mdefine_line|#define ZR050_ACV_HI              0x016
DECL|macro|ZR050_ACV_MH
mdefine_line|#define ZR050_ACV_MH              0x017
DECL|macro|ZR050_ACV_ML
mdefine_line|#define ZR050_ACV_ML              0x018
DECL|macro|ZR050_ACV_LO
mdefine_line|#define ZR050_ACV_LO              0x019
DECL|macro|ZR050_ACT_HI
mdefine_line|#define ZR050_ACT_HI              0x01a
DECL|macro|ZR050_ACT_MH
mdefine_line|#define ZR050_ACT_MH              0x01b
DECL|macro|ZR050_ACT_ML
mdefine_line|#define ZR050_ACT_ML              0x01c
DECL|macro|ZR050_ACT_LO
mdefine_line|#define ZR050_ACT_LO              0x01d
DECL|macro|ZR050_ACV_TRUN_HI
mdefine_line|#define ZR050_ACV_TRUN_HI         0x01e
DECL|macro|ZR050_ACV_TRUN_MH
mdefine_line|#define ZR050_ACV_TRUN_MH         0x01f
DECL|macro|ZR050_ACV_TRUN_ML
mdefine_line|#define ZR050_ACV_TRUN_ML         0x020
DECL|macro|ZR050_ACV_TRUN_LO
mdefine_line|#define ZR050_ACV_TRUN_LO         0x021
DECL|macro|ZR050_STATUS_0
mdefine_line|#define ZR050_STATUS_0            0x02e
DECL|macro|ZR050_STATUS_1
mdefine_line|#define ZR050_STATUS_1            0x02f
DECL|macro|ZR050_SOF_IDX
mdefine_line|#define ZR050_SOF_IDX             0x040
DECL|macro|ZR050_SOS1_IDX
mdefine_line|#define ZR050_SOS1_IDX            0x07a
DECL|macro|ZR050_SOS2_IDX
mdefine_line|#define ZR050_SOS2_IDX            0x08a
DECL|macro|ZR050_SOS3_IDX
mdefine_line|#define ZR050_SOS3_IDX            0x09a
DECL|macro|ZR050_SOS4_IDX
mdefine_line|#define ZR050_SOS4_IDX            0x0aa
DECL|macro|ZR050_DRI_IDX
mdefine_line|#define ZR050_DRI_IDX             0x0c0
DECL|macro|ZR050_DNL_IDX
mdefine_line|#define ZR050_DNL_IDX             0x0c6
DECL|macro|ZR050_DQT_IDX
mdefine_line|#define ZR050_DQT_IDX             0x0cc
DECL|macro|ZR050_DHT_IDX
mdefine_line|#define ZR050_DHT_IDX             0x1d4
DECL|macro|ZR050_APP_IDX
mdefine_line|#define ZR050_APP_IDX             0x380
DECL|macro|ZR050_COM_IDX
mdefine_line|#define ZR050_COM_IDX             0x3c0
multiline_comment|/* zr36050 hardware register bits */
DECL|macro|ZR050_HW_BSWD
mdefine_line|#define ZR050_HW_BSWD                0x80
DECL|macro|ZR050_HW_MSTR
mdefine_line|#define ZR050_HW_MSTR                0x40
DECL|macro|ZR050_HW_DMA
mdefine_line|#define ZR050_HW_DMA                 0x20
DECL|macro|ZR050_HW_CFIS_1_CLK
mdefine_line|#define ZR050_HW_CFIS_1_CLK          0x00
DECL|macro|ZR050_HW_CFIS_2_CLK
mdefine_line|#define ZR050_HW_CFIS_2_CLK          0x04
DECL|macro|ZR050_HW_CFIS_3_CLK
mdefine_line|#define ZR050_HW_CFIS_3_CLK          0x08
DECL|macro|ZR050_HW_CFIS_4_CLK
mdefine_line|#define ZR050_HW_CFIS_4_CLK          0x0C
DECL|macro|ZR050_HW_CFIS_5_CLK
mdefine_line|#define ZR050_HW_CFIS_5_CLK          0x10
DECL|macro|ZR050_HW_CFIS_6_CLK
mdefine_line|#define ZR050_HW_CFIS_6_CLK          0x14
DECL|macro|ZR050_HW_CFIS_7_CLK
mdefine_line|#define ZR050_HW_CFIS_7_CLK          0x18
DECL|macro|ZR050_HW_CFIS_8_CLK
mdefine_line|#define ZR050_HW_CFIS_8_CLK          0x1C
DECL|macro|ZR050_HW_BELE
mdefine_line|#define ZR050_HW_BELE                0x01
multiline_comment|/* zr36050 mode register bits */
DECL|macro|ZR050_MO_COMP
mdefine_line|#define ZR050_MO_COMP                0x80
DECL|macro|ZR050_MO_COMP
mdefine_line|#define ZR050_MO_COMP                0x80
DECL|macro|ZR050_MO_ATP
mdefine_line|#define ZR050_MO_ATP                 0x40
DECL|macro|ZR050_MO_PASS2
mdefine_line|#define ZR050_MO_PASS2               0x20
DECL|macro|ZR050_MO_TLM
mdefine_line|#define ZR050_MO_TLM                 0x10
DECL|macro|ZR050_MO_DCONLY
mdefine_line|#define ZR050_MO_DCONLY              0x08
DECL|macro|ZR050_MO_BRC
mdefine_line|#define ZR050_MO_BRC                 0x04
DECL|macro|ZR050_MO_ATP
mdefine_line|#define ZR050_MO_ATP                 0x40
DECL|macro|ZR050_MO_PASS2
mdefine_line|#define ZR050_MO_PASS2               0x20
DECL|macro|ZR050_MO_TLM
mdefine_line|#define ZR050_MO_TLM                 0x10
DECL|macro|ZR050_MO_DCONLY
mdefine_line|#define ZR050_MO_DCONLY              0x08
multiline_comment|/* zr36050 option register bits */
DECL|macro|ZR050_OP_NSCN_1
mdefine_line|#define ZR050_OP_NSCN_1              0x00
DECL|macro|ZR050_OP_NSCN_2
mdefine_line|#define ZR050_OP_NSCN_2              0x20
DECL|macro|ZR050_OP_NSCN_3
mdefine_line|#define ZR050_OP_NSCN_3              0x40
DECL|macro|ZR050_OP_NSCN_4
mdefine_line|#define ZR050_OP_NSCN_4              0x60
DECL|macro|ZR050_OP_NSCN_5
mdefine_line|#define ZR050_OP_NSCN_5              0x80
DECL|macro|ZR050_OP_NSCN_6
mdefine_line|#define ZR050_OP_NSCN_6              0xA0
DECL|macro|ZR050_OP_NSCN_7
mdefine_line|#define ZR050_OP_NSCN_7              0xC0
DECL|macro|ZR050_OP_NSCN_8
mdefine_line|#define ZR050_OP_NSCN_8              0xE0
DECL|macro|ZR050_OP_OVF
mdefine_line|#define ZR050_OP_OVF                 0x10
multiline_comment|/* zr36050 markers-enable register bits */
DECL|macro|ZR050_ME_APP
mdefine_line|#define ZR050_ME_APP                 0x80
DECL|macro|ZR050_ME_COM
mdefine_line|#define ZR050_ME_COM                 0x40
DECL|macro|ZR050_ME_DRI
mdefine_line|#define ZR050_ME_DRI                 0x20
DECL|macro|ZR050_ME_DQT
mdefine_line|#define ZR050_ME_DQT                 0x10
DECL|macro|ZR050_ME_DHT
mdefine_line|#define ZR050_ME_DHT                 0x08
DECL|macro|ZR050_ME_DNL
mdefine_line|#define ZR050_ME_DNL                 0x04
DECL|macro|ZR050_ME_DQTI
mdefine_line|#define ZR050_ME_DQTI                0x02
DECL|macro|ZR050_ME_DHTI
mdefine_line|#define ZR050_ME_DHTI                0x01
multiline_comment|/* zr36050 status0/1 register bit masks */
DECL|macro|ZR050_ST_RST_MASK
mdefine_line|#define ZR050_ST_RST_MASK            0x20
DECL|macro|ZR050_ST_SOF_MASK
mdefine_line|#define ZR050_ST_SOF_MASK            0x02
DECL|macro|ZR050_ST_SOS_MASK
mdefine_line|#define ZR050_ST_SOS_MASK            0x02
DECL|macro|ZR050_ST_DATRDY_MASK
mdefine_line|#define ZR050_ST_DATRDY_MASK         0x80
DECL|macro|ZR050_ST_MRKDET_MASK
mdefine_line|#define ZR050_ST_MRKDET_MASK         0x40
DECL|macro|ZR050_ST_RFM_MASK
mdefine_line|#define ZR050_ST_RFM_MASK            0x10
DECL|macro|ZR050_ST_RFD_MASK
mdefine_line|#define ZR050_ST_RFD_MASK            0x08
DECL|macro|ZR050_ST_END_MASK
mdefine_line|#define ZR050_ST_END_MASK            0x04
DECL|macro|ZR050_ST_TCVOVF_MASK
mdefine_line|#define ZR050_ST_TCVOVF_MASK         0x02
DECL|macro|ZR050_ST_DATOVF_MASK
mdefine_line|#define ZR050_ST_DATOVF_MASK         0x01
multiline_comment|/* pixel component idx */
DECL|macro|ZR050_Y_COMPONENT
mdefine_line|#define ZR050_Y_COMPONENT         0
DECL|macro|ZR050_U_COMPONENT
mdefine_line|#define ZR050_U_COMPONENT         1
DECL|macro|ZR050_V_COMPONENT
mdefine_line|#define ZR050_V_COMPONENT         2
macro_line|#endif&t;&t;&t;&t;/*fndef ZR36050_H */
eof
