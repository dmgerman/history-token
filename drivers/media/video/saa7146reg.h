multiline_comment|/*  &n;    saa7146.h - definitions philips saa7146 based cards&n;    Copyright (C) 1999 Nathan Laredo (laredo@gnu.org)&n;    &n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __SAA7146_REG__
DECL|macro|__SAA7146_REG__
mdefine_line|#define __SAA7146_REG__
DECL|macro|SAA7146_BASE_ODD1
mdefine_line|#define SAA7146_BASE_ODD1&t;0x00
DECL|macro|SAA7146_BASE_EVEN1
mdefine_line|#define SAA7146_BASE_EVEN1&t;0x04
DECL|macro|SAA7146_PROT_ADDR1
mdefine_line|#define SAA7146_PROT_ADDR1&t;0x08
DECL|macro|SAA7146_PITCH1
mdefine_line|#define SAA7146_PITCH1&t;&t;0x0c
DECL|macro|SAA7146_PAGE1
mdefine_line|#define SAA7146_PAGE1&t;&t;0x10
DECL|macro|SAA7146_NUM_LINE_BYTE1
mdefine_line|#define SAA7146_NUM_LINE_BYTE1&t;0x14
DECL|macro|SAA7146_BASE_ODD2
mdefine_line|#define SAA7146_BASE_ODD2&t;0x18
DECL|macro|SAA7146_BASE_EVEN2
mdefine_line|#define SAA7146_BASE_EVEN2&t;0x1c
DECL|macro|SAA7146_PROT_ADDR2
mdefine_line|#define SAA7146_PROT_ADDR2&t;0x20
DECL|macro|SAA7146_PITCH2
mdefine_line|#define SAA7146_PITCH2&t;&t;0x24
DECL|macro|SAA7146_PAGE2
mdefine_line|#define SAA7146_PAGE2&t;&t;0x28
DECL|macro|SAA7146_NUM_LINE_BYTE2
mdefine_line|#define SAA7146_NUM_LINE_BYTE2&t;0x2c
DECL|macro|SAA7146_BASE_ODD3
mdefine_line|#define SAA7146_BASE_ODD3&t;0x30
DECL|macro|SAA7146_BASE_EVEN3
mdefine_line|#define SAA7146_BASE_EVEN3&t;0x34
DECL|macro|SAA7146_PROT_ADDR3
mdefine_line|#define SAA7146_PROT_ADDR3&t;0x38
DECL|macro|SAA7146_PITCH3
mdefine_line|#define SAA7146_PITCH3&t;&t;0x3c
DECL|macro|SAA7146_PAGE3
mdefine_line|#define SAA7146_PAGE3&t;&t;0x40
DECL|macro|SAA7146_NUM_LINE_BYTE3
mdefine_line|#define SAA7146_NUM_LINE_BYTE3&t;0x44
DECL|macro|SAA7146_PCI_BT_V1
mdefine_line|#define SAA7146_PCI_BT_V1&t;0x48
DECL|macro|SAA7146_PCI_BT_V2
mdefine_line|#define SAA7146_PCI_BT_V2&t;0x49
DECL|macro|SAA7146_PCI_BT_V3
mdefine_line|#define SAA7146_PCI_BT_V3&t;0x4a
DECL|macro|SAA7146_PCI_BT_DEBI
mdefine_line|#define SAA7146_PCI_BT_DEBI&t;0x4b
DECL|macro|SAA7146_PCI_BT_A
mdefine_line|#define SAA7146_PCI_BT_A&t;0x4c
DECL|macro|SAA7146_DD1_INIT
mdefine_line|#define SAA7146_DD1_INIT&t;0x50
DECL|macro|SAA7146_DD1_STREAM_B
mdefine_line|#define SAA7146_DD1_STREAM_B&t;0x54
DECL|macro|SAA7146_DD1_STREAM_A
mdefine_line|#define SAA7146_DD1_STREAM_A&t;0x56
DECL|macro|SAA7146_BRS_CTRL
mdefine_line|#define SAA7146_BRS_CTRL&t;0x58
DECL|macro|SAA7146_HPS_CTRL
mdefine_line|#define SAA7146_HPS_CTRL&t;0x5c
DECL|macro|SAA7146_HPS_V_SCALE
mdefine_line|#define SAA7146_HPS_V_SCALE&t;0x60
DECL|macro|SAA7146_HPS_V_GAIN
mdefine_line|#define SAA7146_HPS_V_GAIN&t;0x64
DECL|macro|SAA7146_HPS_H_PRESCALE
mdefine_line|#define SAA7146_HPS_H_PRESCALE&t;0x68
DECL|macro|SAA7146_HPS_H_SCALE
mdefine_line|#define SAA7146_HPS_H_SCALE&t;0x6c
DECL|macro|SAA7146_BCS_CTRL
mdefine_line|#define SAA7146_BCS_CTRL&t;0x70
DECL|macro|SAA7146_CHROMA_KEY_RANGE
mdefine_line|#define SAA7146_CHROMA_KEY_RANGE&t;0x74
DECL|macro|SAA7146_CLIP_FORMAT_CTRL
mdefine_line|#define SAA7146_CLIP_FORMAT_CTRL&t;0x78
DECL|macro|SAA7146_DEBI_CONFIG
mdefine_line|#define SAA7146_DEBI_CONFIG&t;0x7c
DECL|macro|SAA7146_DEBI_COMMAND
mdefine_line|#define SAA7146_DEBI_COMMAND&t;0x80
DECL|macro|SAA7146_DEBI_PAGE
mdefine_line|#define SAA7146_DEBI_PAGE&t;0x84
DECL|macro|SAA7146_DEBI_AD
mdefine_line|#define SAA7146_DEBI_AD&t;&t;0x88
DECL|macro|SAA7146_I2C_TRANSFER
mdefine_line|#define SAA7146_I2C_TRANSFER&t;0x8c
DECL|macro|SAA7146_I2C_STATUS
mdefine_line|#define SAA7146_I2C_STATUS&t;0x90
DECL|macro|SAA7146_BASE_A1_IN
mdefine_line|#define SAA7146_BASE_A1_IN&t;0x94
DECL|macro|SAA7146_PROT_A1_IN
mdefine_line|#define SAA7146_PROT_A1_IN&t;0x98
DECL|macro|SAA7146_PAGE_A1_IN
mdefine_line|#define SAA7146_PAGE_A1_IN&t;0x9C
DECL|macro|SAA7146_BASE_A1_OUT
mdefine_line|#define SAA7146_BASE_A1_OUT&t;0xa0
DECL|macro|SAA7146_PROT_A1_OUT
mdefine_line|#define SAA7146_PROT_A1_OUT&t;0xa4
DECL|macro|SAA7146_PAGE_A1_OUT
mdefine_line|#define SAA7146_PAGE_A1_OUT&t;0xa8
DECL|macro|SAA7146_BASE_A2_IN
mdefine_line|#define SAA7146_BASE_A2_IN&t;0xac
DECL|macro|SAA7146_PROT_A2_IN
mdefine_line|#define SAA7146_PROT_A2_IN&t;0xb0
DECL|macro|SAA7146_PAGE_A2_IN
mdefine_line|#define SAA7146_PAGE_A2_IN&t;0xb4
DECL|macro|SAA7146_BASE_A2_OUT
mdefine_line|#define SAA7146_BASE_A2_OUT&t;0xb8
DECL|macro|SAA7146_PROT_A2_OUT
mdefine_line|#define SAA7146_PROT_A2_OUT&t;0xbc
DECL|macro|SAA7146_PAGE_A2_OUT
mdefine_line|#define SAA7146_PAGE_A2_OUT&t;0xc0
DECL|macro|SAA7146_RPS_PAGE0
mdefine_line|#define SAA7146_RPS_PAGE0&t;0xc4
DECL|macro|SAA7146_RPS_PAGE1
mdefine_line|#define SAA7146_RPS_PAGE1&t;0xc8
DECL|macro|SAA7146_RPS_THRESH0
mdefine_line|#define SAA7146_RPS_THRESH0&t;0xcc
DECL|macro|SAA7146_RPS_THRESH1
mdefine_line|#define SAA7146_RPS_THRESH1&t;0xd0
DECL|macro|SAA7146_RPS_TOV0
mdefine_line|#define SAA7146_RPS_TOV0&t;0xd4
DECL|macro|SAA7146_RPS_TOV1
mdefine_line|#define SAA7146_RPS_TOV1&t;0xd8
DECL|macro|SAA7146_IER
mdefine_line|#define SAA7146_IER&t;&t;0xdc
DECL|macro|SAA7146_GPIO_CTRL
mdefine_line|#define SAA7146_GPIO_CTRL&t;0xe0
DECL|macro|SAA7146_EC1SSR
mdefine_line|#define SAA7146_EC1SSR&t;&t;0xe4
DECL|macro|SAA7146_EC2SSR
mdefine_line|#define SAA7146_EC2SSR&t;&t;0xe8
DECL|macro|SAA7146_ECT1R
mdefine_line|#define SAA7146_ECT1R&t;&t;0xec
DECL|macro|SAA7146_ECT2R
mdefine_line|#define SAA7146_ECT2R&t;&t;0xf0
DECL|macro|SAA7146_ACON1
mdefine_line|#define SAA7146_ACON1&t;&t;0xf4
DECL|macro|SAA7146_ACON2
mdefine_line|#define SAA7146_ACON2&t;&t;0xf8
DECL|macro|SAA7146_MC1
mdefine_line|#define SAA7146_MC1&t;&t;0xfc
DECL|macro|SAA7146_MC2
mdefine_line|#define SAA7146_MC2&t;&t;0x100
DECL|macro|SAA7146_RPS_ADDR0
mdefine_line|#define SAA7146_RPS_ADDR0&t;0x104
DECL|macro|SAA7146_RPS_ADDR1
mdefine_line|#define SAA7146_RPS_ADDR1&t;0x108
DECL|macro|SAA7146_ISR
mdefine_line|#define SAA7146_ISR&t;&t;0x10c
DECL|macro|SAA7146_PSR
mdefine_line|#define SAA7146_PSR&t;&t;0x110
DECL|macro|SAA7146_SSR
mdefine_line|#define SAA7146_SSR&t;&t;0x114
DECL|macro|SAA7146_EC1R
mdefine_line|#define SAA7146_EC1R&t;&t;0x118
DECL|macro|SAA7146_EC2R
mdefine_line|#define SAA7146_EC2R&t;&t;0x11c
DECL|macro|SAA7146_VDP1
mdefine_line|#define SAA7146_VDP1&t;&t;0x120
DECL|macro|SAA7146_VDP2
mdefine_line|#define SAA7146_VDP2&t;&t;0x124
DECL|macro|SAA7146_VDP3
mdefine_line|#define SAA7146_VDP3&t;&t;0x128
DECL|macro|SAA7146_ADP1
mdefine_line|#define SAA7146_ADP1&t;&t;0x12c
DECL|macro|SAA7146_ADP2
mdefine_line|#define SAA7146_ADP2&t;&t;0x130
DECL|macro|SAA7146_ADP3
mdefine_line|#define SAA7146_ADP3&t;&t;0x134
DECL|macro|SAA7146_ADP4
mdefine_line|#define SAA7146_ADP4&t;&t;0x138
DECL|macro|SAA7146_DDP
mdefine_line|#define SAA7146_DDP&t;&t;0x13c
DECL|macro|SAA7146_LEVEL_REP
mdefine_line|#define SAA7146_LEVEL_REP&t;0x140
DECL|macro|SAA7146_FB_BUFFER1
mdefine_line|#define SAA7146_FB_BUFFER1&t;0x144
DECL|macro|SAA7146_FB_BUFFER2
mdefine_line|#define SAA7146_FB_BUFFER2&t;0x148
DECL|macro|SAA7146_A_TIME_SLOT1
mdefine_line|#define SAA7146_A_TIME_SLOT1&t;0x180
DECL|macro|SAA7146_A_TIME_SLOT2
mdefine_line|#define SAA7146_A_TIME_SLOT2&t;0x1C0
multiline_comment|/* bitfield defines */
DECL|macro|MASK_31
mdefine_line|#define MASK_31&t;&t;&t;0x80000000
DECL|macro|MASK_30
mdefine_line|#define MASK_30&t;&t;&t;0x40000000
DECL|macro|MASK_29
mdefine_line|#define MASK_29&t;&t;&t;0x20000000
DECL|macro|MASK_28
mdefine_line|#define MASK_28&t;&t;&t;0x10000000
DECL|macro|MASK_27
mdefine_line|#define MASK_27&t;&t;&t;0x08000000
DECL|macro|MASK_26
mdefine_line|#define MASK_26&t;&t;&t;0x04000000
DECL|macro|MASK_25
mdefine_line|#define MASK_25&t;&t;&t;0x02000000
DECL|macro|MASK_24
mdefine_line|#define MASK_24&t;&t;&t;0x01000000
DECL|macro|MASK_23
mdefine_line|#define MASK_23&t;&t;&t;0x00800000
DECL|macro|MASK_22
mdefine_line|#define MASK_22&t;&t;&t;0x00400000
DECL|macro|MASK_21
mdefine_line|#define MASK_21&t;&t;&t;0x00200000
DECL|macro|MASK_20
mdefine_line|#define MASK_20&t;&t;&t;0x00100000
DECL|macro|MASK_19
mdefine_line|#define MASK_19&t;&t;&t;0x00080000
DECL|macro|MASK_18
mdefine_line|#define MASK_18&t;&t;&t;0x00040000
DECL|macro|MASK_17
mdefine_line|#define MASK_17&t;&t;&t;0x00020000
DECL|macro|MASK_16
mdefine_line|#define MASK_16&t;&t;&t;0x00010000
DECL|macro|MASK_15
mdefine_line|#define MASK_15&t;&t;&t;0x00008000
DECL|macro|MASK_14
mdefine_line|#define MASK_14&t;&t;&t;0x00004000
DECL|macro|MASK_13
mdefine_line|#define MASK_13&t;&t;&t;0x00002000
DECL|macro|MASK_12
mdefine_line|#define MASK_12&t;&t;&t;0x00001000
DECL|macro|MASK_11
mdefine_line|#define MASK_11&t;&t;&t;0x00000800
DECL|macro|MASK_10
mdefine_line|#define MASK_10&t;&t;&t;0x00000400
DECL|macro|MASK_09
mdefine_line|#define MASK_09&t;&t;&t;0x00000200
DECL|macro|MASK_08
mdefine_line|#define MASK_08&t;&t;&t;0x00000100
DECL|macro|MASK_07
mdefine_line|#define MASK_07&t;&t;&t;0x00000080
DECL|macro|MASK_06
mdefine_line|#define MASK_06&t;&t;&t;0x00000040
DECL|macro|MASK_05
mdefine_line|#define MASK_05&t;&t;&t;0x00000020
DECL|macro|MASK_04
mdefine_line|#define MASK_04&t;&t;&t;0x00000010
DECL|macro|MASK_03
mdefine_line|#define MASK_03&t;&t;&t;0x00000008
DECL|macro|MASK_02
mdefine_line|#define MASK_02&t;&t;&t;0x00000004
DECL|macro|MASK_01
mdefine_line|#define MASK_01&t;&t;&t;0x00000002
DECL|macro|MASK_00
mdefine_line|#define MASK_00&t;&t;&t;0x00000001
DECL|macro|MASK_B0
mdefine_line|#define MASK_B0&t;&t;&t;0x000000ff
DECL|macro|MASK_B1
mdefine_line|#define MASK_B1&t;&t;&t;0x0000ff00
DECL|macro|MASK_B2
mdefine_line|#define MASK_B2&t;&t;&t;0x00ff0000
DECL|macro|MASK_B3
mdefine_line|#define MASK_B3&t;&t;&t;0xff000000
DECL|macro|MASK_W0
mdefine_line|#define MASK_W0&t;&t;&t;0x0000ffff
DECL|macro|MASK_W1
mdefine_line|#define MASK_W1&t;&t;&t;0xffff0000
DECL|macro|MASK_PA
mdefine_line|#define MASK_PA&t;&t;&t;0xfffffffc
DECL|macro|MASK_PR
mdefine_line|#define MASK_PR&t;&t;&t;0xfffffffe
DECL|macro|MASK_ER
mdefine_line|#define MASK_ER&t;&t;&t;0xffffffff
DECL|macro|MASK_NONE
mdefine_line|#define MASK_NONE&t;&t;0x00000000
DECL|macro|SAA7146_PAGE_MAP_EN
mdefine_line|#define SAA7146_PAGE_MAP_EN&t;MASK_11
multiline_comment|/* main control register 1 */
DECL|macro|SAA7146_MC1_MRST_N
mdefine_line|#define SAA7146_MC1_MRST_N&t;MASK_15
DECL|macro|SAA7146_MC1_ERPS1
mdefine_line|#define SAA7146_MC1_ERPS1&t;MASK_13
DECL|macro|SAA7146_MC1_ERPS0
mdefine_line|#define SAA7146_MC1_ERPS0&t;MASK_12
DECL|macro|SAA7146_MC1_EDP
mdefine_line|#define SAA7146_MC1_EDP&t;&t;MASK_11
DECL|macro|SAA7146_MC1_EVP
mdefine_line|#define SAA7146_MC1_EVP&t;&t;MASK_10
DECL|macro|SAA7146_MC1_EAP
mdefine_line|#define SAA7146_MC1_EAP&t;&t;MASK_09
DECL|macro|SAA7146_MC1_EI2C
mdefine_line|#define SAA7146_MC1_EI2C&t;MASK_08
DECL|macro|SAA7146_MC1_TR_E_DEBI
mdefine_line|#define SAA7146_MC1_TR_E_DEBI&t;MASK_07
DECL|macro|SAA7146_MC1_TR_E_1
mdefine_line|#define SAA7146_MC1_TR_E_1&t;MASK_06
DECL|macro|SAA7146_MC1_TR_E_2
mdefine_line|#define SAA7146_MC1_TR_E_2&t;MASK_05
DECL|macro|SAA7146_MC1_TR_E_3
mdefine_line|#define SAA7146_MC1_TR_E_3&t;MASK_04
DECL|macro|SAA7146_MC1_TR_E_A2_OUT
mdefine_line|#define SAA7146_MC1_TR_E_A2_OUT&t;MASK_03
DECL|macro|SAA7146_MC1_TR_E_A2_IN
mdefine_line|#define SAA7146_MC1_TR_E_A2_IN&t;MASK_02
DECL|macro|SAA7146_MC1_TR_E_A1_OUT
mdefine_line|#define SAA7146_MC1_TR_E_A1_OUT&t;MASK_01
DECL|macro|SAA7146_MC1_TR_E_A1_IN
mdefine_line|#define SAA7146_MC1_TR_E_A1_IN&t;MASK_00
multiline_comment|/* main control register 2 */
DECL|macro|SAA7146_MC2_RPS_SIG4
mdefine_line|#define SAA7146_MC2_RPS_SIG4&t;MASK_15
DECL|macro|SAA7146_MC2_RPS_SIG3
mdefine_line|#define SAA7146_MC2_RPS_SIG3&t;MASK_14
DECL|macro|SAA7146_MC2_RPS_SIG2
mdefine_line|#define SAA7146_MC2_RPS_SIG2&t;MASK_13
DECL|macro|SAA7146_MC2_RPS_SIG1
mdefine_line|#define SAA7146_MC2_RPS_SIG1&t;MASK_12
DECL|macro|SAA7146_MC2_RPS_SIG0
mdefine_line|#define SAA7146_MC2_RPS_SIG0&t;MASK_11
DECL|macro|SAA7146_MC2_UPLD_D1_B
mdefine_line|#define SAA7146_MC2_UPLD_D1_B&t;MASK_10
DECL|macro|SAA7146_MC2_UPLD_D1_A
mdefine_line|#define SAA7146_MC2_UPLD_D1_A&t;MASK_09
DECL|macro|SAA7146_MC2_UPLD_BRS
mdefine_line|#define SAA7146_MC2_UPLD_BRS&t;MASK_08
DECL|macro|SAA7146_MC2_UPLD_HPS_H
mdefine_line|#define SAA7146_MC2_UPLD_HPS_H&t;MASK_06
DECL|macro|SAA7146_MC2_UPLD_HPS_V
mdefine_line|#define SAA7146_MC2_UPLD_HPS_V&t;MASK_05
DECL|macro|SAA7146_MC2_UPLD_DMA3
mdefine_line|#define SAA7146_MC2_UPLD_DMA3&t;MASK_04
DECL|macro|SAA7146_MC2_UPLD_DMA2
mdefine_line|#define SAA7146_MC2_UPLD_DMA2&t;MASK_03
DECL|macro|SAA7146_MC2_UPLD_DMA1
mdefine_line|#define SAA7146_MC2_UPLD_DMA1&t;MASK_02
DECL|macro|SAA7146_MC2_UPLD_DEBI
mdefine_line|#define SAA7146_MC2_UPLD_DEBI&t;MASK_01
DECL|macro|SAA7146_MC2_UPLD_I2C
mdefine_line|#define SAA7146_MC2_UPLD_I2C&t;MASK_00
multiline_comment|/* Primary Status Register and Interrupt Enable/Status Registers */
DECL|macro|SAA7146_PSR_PPEF
mdefine_line|#define SAA7146_PSR_PPEF&t;MASK_31
DECL|macro|SAA7146_PSR_PABO
mdefine_line|#define SAA7146_PSR_PABO&t;MASK_30
DECL|macro|SAA7146_PSR_PPED
mdefine_line|#define SAA7146_PSR_PPED&t;MASK_29
DECL|macro|SAA7146_PSR_RPS_I1
mdefine_line|#define SAA7146_PSR_RPS_I1&t;MASK_28
DECL|macro|SAA7146_PSR_RPS_I0
mdefine_line|#define SAA7146_PSR_RPS_I0&t;MASK_27
DECL|macro|SAA7146_PSR_RPS_LATE1
mdefine_line|#define SAA7146_PSR_RPS_LATE1&t;MASK_26
DECL|macro|SAA7146_PSR_RPS_LATE0
mdefine_line|#define SAA7146_PSR_RPS_LATE0&t;MASK_25
DECL|macro|SAA7146_PSR_RPS_E1
mdefine_line|#define SAA7146_PSR_RPS_E1&t;MASK_24
DECL|macro|SAA7146_PSR_RPS_E0
mdefine_line|#define SAA7146_PSR_RPS_E0&t;MASK_23
DECL|macro|SAA7146_PSR_RPS_TO1
mdefine_line|#define SAA7146_PSR_RPS_TO1&t;MASK_22
DECL|macro|SAA7146_PSR_RPS_TO0
mdefine_line|#define SAA7146_PSR_RPS_TO0&t;MASK_21
DECL|macro|SAA7146_PSR_UPLD
mdefine_line|#define SAA7146_PSR_UPLD&t;MASK_20
DECL|macro|SAA7146_PSR_DEBI_S
mdefine_line|#define SAA7146_PSR_DEBI_S&t;MASK_19
DECL|macro|SAA7146_PSR_DEBI_E
mdefine_line|#define SAA7146_PSR_DEBI_E&t;MASK_18
DECL|macro|SAA7146_PSR_I2C_S
mdefine_line|#define SAA7146_PSR_I2C_S&t;MASK_17
DECL|macro|SAA7146_PSR_I2C_E
mdefine_line|#define SAA7146_PSR_I2C_E&t;MASK_16
DECL|macro|SAA7146_PSR_A2_IN
mdefine_line|#define SAA7146_PSR_A2_IN&t;MASK_15
DECL|macro|SAA7146_PSR_A2_OUT
mdefine_line|#define SAA7146_PSR_A2_OUT&t;MASK_14
DECL|macro|SAA7146_PSR_A1_IN
mdefine_line|#define SAA7146_PSR_A1_IN&t;MASK_13
DECL|macro|SAA7146_PSR_A1_OUT
mdefine_line|#define SAA7146_PSR_A1_OUT&t;MASK_12
DECL|macro|SAA7146_PSR_AFOU
mdefine_line|#define SAA7146_PSR_AFOU&t;MASK_11
DECL|macro|SAA7146_PSR_V_PE
mdefine_line|#define SAA7146_PSR_V_PE&t;MASK_10
DECL|macro|SAA7146_PSR_VFOU
mdefine_line|#define SAA7146_PSR_VFOU&t;MASK_09
DECL|macro|SAA7146_PSR_FIDA
mdefine_line|#define SAA7146_PSR_FIDA&t;MASK_08
DECL|macro|SAA7146_PSR_FIDB
mdefine_line|#define SAA7146_PSR_FIDB&t;MASK_07
DECL|macro|SAA7146_PSR_PIN3
mdefine_line|#define SAA7146_PSR_PIN3&t;MASK_06
DECL|macro|SAA7146_PSR_PIN2
mdefine_line|#define SAA7146_PSR_PIN2&t;MASK_05
DECL|macro|SAA7146_PSR_PIN1
mdefine_line|#define SAA7146_PSR_PIN1&t;MASK_04
DECL|macro|SAA7146_PSR_PIN0
mdefine_line|#define SAA7146_PSR_PIN0&t;MASK_03
DECL|macro|SAA7146_PSR_ECS
mdefine_line|#define SAA7146_PSR_ECS&t;&t;MASK_02
DECL|macro|SAA7146_PSR_EC3S
mdefine_line|#define SAA7146_PSR_EC3S&t;MASK_01
DECL|macro|SAA7146_PSR_EC0S
mdefine_line|#define SAA7146_PSR_EC0S&t;MASK_00
multiline_comment|/* Secondary Status Register */
DECL|macro|SAA7146_SSR_PRQ
mdefine_line|#define SAA7146_SSR_PRQ&t;&t;MASK_31
DECL|macro|SAA7146_SSR_PMA
mdefine_line|#define SAA7146_SSR_PMA&t;&t;MASK_30
DECL|macro|SAA7146_SSR_RPS_RE1
mdefine_line|#define SAA7146_SSR_RPS_RE1&t;MASK_29
DECL|macro|SAA7146_SSR_RPS_PE1
mdefine_line|#define SAA7146_SSR_RPS_PE1&t;MASK_28
DECL|macro|SAA7146_SSR_RPS_A1
mdefine_line|#define SAA7146_SSR_RPS_A1&t;MASK_27
DECL|macro|SAA7146_SSR_RPS_RE0
mdefine_line|#define SAA7146_SSR_RPS_RE0&t;MASK_26
DECL|macro|SAA7146_SSR_RPS_PE0
mdefine_line|#define SAA7146_SSR_RPS_PE0&t;MASK_25
DECL|macro|SAA7146_SSR_RPS_A0
mdefine_line|#define SAA7146_SSR_RPS_A0&t;MASK_24
DECL|macro|SAA7146_SSR_DEBI_TO
mdefine_line|#define SAA7146_SSR_DEBI_TO&t;MASK_23
DECL|macro|SAA7146_SSR_DEBI_EF
mdefine_line|#define SAA7146_SSR_DEBI_EF&t;MASK_22
DECL|macro|SAA7146_SSR_I2C_EA
mdefine_line|#define SAA7146_SSR_I2C_EA&t;MASK_21
DECL|macro|SAA7146_SSR_I2C_EW
mdefine_line|#define SAA7146_SSR_I2C_EW&t;MASK_20
DECL|macro|SAA7146_SSR_I2C_ER
mdefine_line|#define SAA7146_SSR_I2C_ER&t;MASK_19
DECL|macro|SAA7146_SSR_I2C_EL
mdefine_line|#define SAA7146_SSR_I2C_EL&t;MASK_18
DECL|macro|SAA7146_SSR_I2C_EF
mdefine_line|#define SAA7146_SSR_I2C_EF&t;MASK_17
DECL|macro|SAA7146_SSR_V3P
mdefine_line|#define SAA7146_SSR_V3P&t;&t;MASK_16
DECL|macro|SAA7146_SSR_V2P
mdefine_line|#define SAA7146_SSR_V2P&t;&t;MASK_15
DECL|macro|SAA7146_SSR_V1P
mdefine_line|#define SAA7146_SSR_V1P&t;&t;MASK_14
DECL|macro|SAA7146_SSR_VF3
mdefine_line|#define SAA7146_SSR_VF3&t;&t;MASK_13
DECL|macro|SAA7146_SSR_VF2
mdefine_line|#define SAA7146_SSR_VF2&t;&t;MASK_12
DECL|macro|SAA7146_SSR_VF1
mdefine_line|#define SAA7146_SSR_VF1&t;&t;MASK_11
DECL|macro|SAA7146_SSR_AF2_IN
mdefine_line|#define SAA7146_SSR_AF2_IN&t;MASK_10
DECL|macro|SAA7146_SSR_AF2_OUT
mdefine_line|#define SAA7146_SSR_AF2_OUT&t;MASK_09
DECL|macro|SAA7146_SSR_AF1_IN
mdefine_line|#define SAA7146_SSR_AF1_IN&t;MASK_08
DECL|macro|SAA7146_SSR_AF1_OUT
mdefine_line|#define SAA7146_SSR_AF1_OUT&t;MASK_07
DECL|macro|SAA7146_SSR_VGT
mdefine_line|#define SAA7146_SSR_VGT&t;&t;MASK_05
DECL|macro|SAA7146_SSR_LNQG
mdefine_line|#define SAA7146_SSR_LNQG&t;MASK_04
DECL|macro|SAA7146_SSR_EC5S
mdefine_line|#define SAA7146_SSR_EC5S&t;MASK_03
DECL|macro|SAA7146_SSR_EC4S
mdefine_line|#define SAA7146_SSR_EC4S&t;MASK_02
DECL|macro|SAA7146_SSR_EC2S
mdefine_line|#define SAA7146_SSR_EC2S&t;MASK_01
DECL|macro|SAA7146_SSR_EC1S
mdefine_line|#define SAA7146_SSR_EC1S&t;MASK_00
multiline_comment|/* I2C status register */
DECL|macro|SAA7146_I2C_ABORT
mdefine_line|#define SAA7146_I2C_ABORT&t;MASK_07
DECL|macro|SAA7146_I2C_SPERR
mdefine_line|#define SAA7146_I2C_SPERR&t;MASK_06
DECL|macro|SAA7146_I2C_APERR
mdefine_line|#define SAA7146_I2C_APERR&t;MASK_05
DECL|macro|SAA7146_I2C_DTERR
mdefine_line|#define SAA7146_I2C_DTERR&t;MASK_04
DECL|macro|SAA7146_I2C_DRERR
mdefine_line|#define SAA7146_I2C_DRERR&t;MASK_03
DECL|macro|SAA7146_I2C_AL
mdefine_line|#define SAA7146_I2C_AL&t;&t;MASK_02
DECL|macro|SAA7146_I2C_ERR
mdefine_line|#define SAA7146_I2C_ERR&t;&t;MASK_01
DECL|macro|SAA7146_I2C_BUSY
mdefine_line|#define SAA7146_I2C_BUSY&t;MASK_00
multiline_comment|/* output formats */
DECL|macro|SAA7146_YUV422
mdefine_line|#define SAA7146_YUV422&t;0
DECL|macro|SAA7146_RGB16
mdefine_line|#define SAA7146_RGB16&t;0
DECL|macro|SAA7146_YUV444
mdefine_line|#define SAA7146_YUV444&t;1
DECL|macro|SAA7146_RGB24
mdefine_line|#define SAA7146_RGB24&t;1
DECL|macro|SAA7146_ARGB32
mdefine_line|#define SAA7146_ARGB32&t;2
DECL|macro|SAA7146_YUV411
mdefine_line|#define SAA7146_YUV411&t;3
DECL|macro|SAA7146_ARGB15
mdefine_line|#define SAA7146_ARGB15  3
DECL|macro|SAA7146_YUV2
mdefine_line|#define SAA7146_YUV2&t;4
DECL|macro|SAA7146_RGAB15
mdefine_line|#define SAA7146_RGAB15&t;4
DECL|macro|SAA7146_Y8
mdefine_line|#define SAA7146_Y8&t;6
DECL|macro|SAA7146_YUV8
mdefine_line|#define SAA7146_YUV8&t;7
DECL|macro|SAA7146_RGB8
mdefine_line|#define SAA7146_RGB8&t;7
DECL|macro|SAA7146_YUV444p
mdefine_line|#define SAA7146_YUV444p&t;8
DECL|macro|SAA7146_YUV422p
mdefine_line|#define SAA7146_YUV422p&t;9
DECL|macro|SAA7146_YUV420p
mdefine_line|#define SAA7146_YUV420p&t;10
DECL|macro|SAA7146_YUV1620
mdefine_line|#define SAA7146_YUV1620&t;11
DECL|macro|SAA7146_Y1
mdefine_line|#define SAA7146_Y1&t;13
DECL|macro|SAA7146_Y2
mdefine_line|#define SAA7146_Y2&t;14
DECL|macro|SAA7146_YUV1
mdefine_line|#define SAA7146_YUV1&t;15
macro_line|#endif
eof
