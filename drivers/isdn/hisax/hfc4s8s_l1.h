multiline_comment|/***************************************************************/
multiline_comment|/*  $Id: hfc4s8s_l1.h,v 1.1 2005/02/02 17:28:55 martinb1 Exp $ */
multiline_comment|/*                                                             */
multiline_comment|/*  This file is a minimal required extraction of hfc48scu.h   */
multiline_comment|/*  (Genero 3.2, HFC XML 1.7a for HFC-E1, HFC-4S and HFC-8S)   */
multiline_comment|/*                                                             */
multiline_comment|/*  To get this complete register description contact          */
multiline_comment|/*  Cologne Chip AG :                                          */
multiline_comment|/*  Internet:  http://www.colognechip.com/                     */
multiline_comment|/*  E-Mail:    info@colognechip.com                            */
multiline_comment|/***************************************************************/
macro_line|#ifndef _HFC4S8S_L1_H_
DECL|macro|_HFC4S8S_L1_H_
mdefine_line|#define _HFC4S8S_L1_H_
multiline_comment|/*&n;*  include Genero generated HFC-4S/8S header file hfc48scu.h&n;*  for comlete register description. This will define _HFC48SCU_H_&n;*  to prevent redefinitions&n;*/
singleline_comment|// #include &quot;hfc48scu.h&quot;
macro_line|#ifndef _HFC48SCU_H_
DECL|macro|_HFC48SCU_H_
mdefine_line|#define _HFC48SCU_H_
macro_line|#ifndef PCI_VENDOR_ID_CCD
DECL|macro|PCI_VENDOR_ID_CCD
mdefine_line|#define PCI_VENDOR_ID_CCD&t;0x1397
macro_line|#endif
DECL|macro|CHIP_ID_4S
mdefine_line|#define CHIP_ID_4S&t;&t;0x0C
DECL|macro|CHIP_ID_8S
mdefine_line|#define CHIP_ID_8S&t;&t;0x08
DECL|macro|PCI_DEVICE_ID_4S
mdefine_line|#define PCI_DEVICE_ID_4S&t;0x08B4
DECL|macro|PCI_DEVICE_ID_8S
mdefine_line|#define PCI_DEVICE_ID_8S&t;0x16B8
DECL|macro|R_IRQ_MISC
mdefine_line|#define R_IRQ_MISC&t;0x11
DECL|macro|M_TI_IRQ
mdefine_line|#define M_TI_IRQ&t;0x02
DECL|macro|A_ST_RD_STA
mdefine_line|#define A_ST_RD_STA&t;0x30
DECL|macro|A_ST_WR_STA
mdefine_line|#define A_ST_WR_STA&t;0x30
DECL|macro|M_SET_G2_G3
mdefine_line|#define M_SET_G2_G3&t;0x80
DECL|macro|A_ST_CTRL0
mdefine_line|#define A_ST_CTRL0&t;0x31
DECL|macro|A_ST_CTRL2
mdefine_line|#define A_ST_CTRL2&t;0x33
DECL|macro|A_ST_CLK_DLY
mdefine_line|#define A_ST_CLK_DLY&t;0x37
DECL|macro|A_Z1
mdefine_line|#define A_Z1&t;&t;0x04
DECL|macro|A_Z2
mdefine_line|#define A_Z2&t;&t;0x06
DECL|macro|R_CIRM
mdefine_line|#define R_CIRM&t;&t;0x00
DECL|macro|M_SRES
mdefine_line|#define M_SRES&t;&t;0x08
DECL|macro|R_CTRL
mdefine_line|#define R_CTRL&t;&t;0x01
DECL|macro|R_BRG_PCM_CFG
mdefine_line|#define R_BRG_PCM_CFG&t;0x02
DECL|macro|M_PCM_CLK
mdefine_line|#define M_PCM_CLK&t;0x20
DECL|macro|R_RAM_MISC
mdefine_line|#define R_RAM_MISC&t;0x0C
DECL|macro|M_FZ_MD
mdefine_line|#define M_FZ_MD&t;&t;0x80
DECL|macro|R_FIFO_MD
mdefine_line|#define R_FIFO_MD&t;0x0D
DECL|macro|A_INC_RES_FIFO
mdefine_line|#define A_INC_RES_FIFO&t;0x0E
DECL|macro|R_FIFO
mdefine_line|#define R_FIFO&t;&t;0x0F
DECL|macro|A_F1
mdefine_line|#define A_F1&t;&t;0x0C
DECL|macro|A_F2
mdefine_line|#define A_F2&t;&t;0x0D
DECL|macro|R_IRQ_OVIEW
mdefine_line|#define R_IRQ_OVIEW&t;0x10
DECL|macro|R_CHIP_ID
mdefine_line|#define R_CHIP_ID&t;0x16
DECL|macro|R_STATUS
mdefine_line|#define R_STATUS&t;0x1C
DECL|macro|M_BUSY
mdefine_line|#define M_BUSY&t;&t;0x01
DECL|macro|M_MISC_IRQSTA
mdefine_line|#define M_MISC_IRQSTA&t;0x40
DECL|macro|M_FR_IRQSTA
mdefine_line|#define M_FR_IRQSTA&t;0x80
DECL|macro|R_CHIP_RV
mdefine_line|#define R_CHIP_RV&t;0x1F
DECL|macro|R_IRQ_CTRL
mdefine_line|#define R_IRQ_CTRL&t;0x13
DECL|macro|M_FIFO_IRQ
mdefine_line|#define M_FIFO_IRQ&t;0x01
DECL|macro|M_GLOB_IRQ_EN
mdefine_line|#define M_GLOB_IRQ_EN&t;0x08
DECL|macro|R_PCM_MD0
mdefine_line|#define R_PCM_MD0&t;0x14
DECL|macro|M_PCM_MD
mdefine_line|#define M_PCM_MD&t;0x01
DECL|macro|A_FIFO_DATA0
mdefine_line|#define A_FIFO_DATA0&t;0x80
DECL|macro|R_TI_WD
mdefine_line|#define R_TI_WD&t;&t;0x1A
DECL|macro|R_PWM1
mdefine_line|#define R_PWM1&t;&t;0x39
DECL|macro|R_PWM_MD
mdefine_line|#define R_PWM_MD&t;0x46
DECL|macro|R_IRQ_FIFO_BL0
mdefine_line|#define R_IRQ_FIFO_BL0&t;0xC8
DECL|macro|A_CON_HDLC
mdefine_line|#define A_CON_HDLC&t;0xFA
DECL|macro|A_SUBCH_CFG
mdefine_line|#define A_SUBCH_CFG&t;0xFB
DECL|macro|A_IRQ_MSK
mdefine_line|#define A_IRQ_MSK&t;0xFF
DECL|macro|R_SCI_MSK
mdefine_line|#define R_SCI_MSK&t;0x12
DECL|macro|R_ST_SEL
mdefine_line|#define R_ST_SEL&t;0x16
DECL|macro|R_ST_SYNC
mdefine_line|#define R_ST_SYNC&t;0x17
DECL|macro|M_AUTO_SYNC
mdefine_line|#define M_AUTO_SYNC&t;0x08
DECL|macro|R_SCI
mdefine_line|#define R_SCI&t;&t;0x12
DECL|macro|R_IRQMSK_MISC
mdefine_line|#define R_IRQMSK_MISC&t;0x11
DECL|macro|M_TI_IRQMSK
mdefine_line|#define M_TI_IRQMSK&t;0x02
macro_line|#endif&t;/* _HFC4S8S_L1_H_ */
macro_line|#endif&t;/* _HFC48SCU_H_ */
eof
