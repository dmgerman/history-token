multiline_comment|/* mb93493-regs.h: MB93493 companion chip registers&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MB93493_REGS_H
DECL|macro|_ASM_MB93493_REGS_H
mdefine_line|#define _ASM_MB93493_REGS_H
macro_line|#include &lt;asm/mb-regs.h&gt;
macro_line|#include &lt;asm/mb93493-irqs.h&gt;
DECL|macro|__get_MB93493
mdefine_line|#define __get_MB93493(X)&t;({ *(volatile unsigned long *)(__region_CS3 + (X)); })
DECL|macro|__set_MB93493
mdefine_line|#define __set_MB93493(X,V)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile unsigned long *)(__region_CS3 + (X)) = (V); mb();&t;&bslash;&n;} while(0)
DECL|macro|__get_MB93493_STSR
mdefine_line|#define __get_MB93493_STSR(X)&t;__get_MB93493(0x3c0 + (X) * 4)
DECL|macro|__set_MB93493_STSR
mdefine_line|#define __set_MB93493_STSR(X,V)&t;__set_MB93493(0x3c0 + (X) * 4, (V))
DECL|macro|MB93493_STSR_EN
mdefine_line|#define MB93493_STSR_EN
DECL|macro|__get_MB93493_IQSR
mdefine_line|#define __get_MB93493_IQSR(X)&t;__get_MB93493(0x3d0 + (X) * 4)
DECL|macro|__set_MB93493_IQSR
mdefine_line|#define __set_MB93493_IQSR(X,V)&t;__set_MB93493(0x3d0 + (X) * 4, (V))
DECL|macro|__get_MB93493_DQSR
mdefine_line|#define __get_MB93493_DQSR(X)&t;__get_MB93493(0x3e0 + (X) * 4)
DECL|macro|__set_MB93493_DQSR
mdefine_line|#define __set_MB93493_DQSR(X,V)&t;__set_MB93493(0x3e0 + (X) * 4, (V))
DECL|macro|__get_MB93493_LBSER
mdefine_line|#define __get_MB93493_LBSER()&t;__get_MB93493(0x3f0)
DECL|macro|__set_MB93493_LBSER
mdefine_line|#define __set_MB93493_LBSER(V)&t;__set_MB93493(0x3f0, (V))
DECL|macro|MB93493_LBSER_VDC
mdefine_line|#define MB93493_LBSER_VDC&t;0x00010000
DECL|macro|MB93493_LBSER_VCC
mdefine_line|#define MB93493_LBSER_VCC&t;0x00020000
DECL|macro|MB93493_LBSER_AUDIO
mdefine_line|#define MB93493_LBSER_AUDIO&t;0x00040000
DECL|macro|MB93493_LBSER_I2C_0
mdefine_line|#define MB93493_LBSER_I2C_0&t;0x00080000
DECL|macro|MB93493_LBSER_I2C_1
mdefine_line|#define MB93493_LBSER_I2C_1&t;0x00100000
DECL|macro|MB93493_LBSER_USB
mdefine_line|#define MB93493_LBSER_USB&t;0x00200000
DECL|macro|MB93493_LBSER_GPIO
mdefine_line|#define MB93493_LBSER_GPIO&t;0x00800000
DECL|macro|MB93493_LBSER_PCMCIA
mdefine_line|#define MB93493_LBSER_PCMCIA&t;0x01000000
DECL|macro|__get_MB93493_LBSR
mdefine_line|#define __get_MB93493_LBSR()&t;__get_MB93493(0x3fc)
DECL|macro|__set_MB93493_LBSR
mdefine_line|#define __set_MB93493_LBSR(V)&t;__set_MB93493(0x3fc, (V))
multiline_comment|/*&n; * video display controller&n; */
DECL|macro|__get_MB93493_VDC
mdefine_line|#define __get_MB93493_VDC(X)&t;__get_MB93493(MB93493_VDC_##X)
DECL|macro|__set_MB93493_VDC
mdefine_line|#define __set_MB93493_VDC(X,V)&t;__set_MB93493(MB93493_VDC_##X, (V))
DECL|macro|MB93493_VDC_RCURSOR
mdefine_line|#define MB93493_VDC_RCURSOR&t;0x140&t;/* cursor position */
DECL|macro|MB93493_VDC_RCT1
mdefine_line|#define MB93493_VDC_RCT1&t;0x144&t;/* cursor colour 1 */
DECL|macro|MB93493_VDC_RCT2
mdefine_line|#define MB93493_VDC_RCT2&t;0x148&t;/* cursor colour 2 */
DECL|macro|MB93493_VDC_RHDC
mdefine_line|#define MB93493_VDC_RHDC&t;0x150&t;/* horizontal display period */
DECL|macro|MB93493_VDC_RH_MARGINS
mdefine_line|#define MB93493_VDC_RH_MARGINS&t;0x154&t;/* horizontal margin sizes */
DECL|macro|MB93493_VDC_RVDC
mdefine_line|#define MB93493_VDC_RVDC&t;0x158&t;/* vertical display period */
DECL|macro|MB93493_VDC_RV_MARGINS
mdefine_line|#define MB93493_VDC_RV_MARGINS&t;0x15c&t;/* vertical margin sizes */
DECL|macro|MB93493_VDC_RC
mdefine_line|#define MB93493_VDC_RC&t;&t;0x170&t;/* VDC control */
DECL|macro|MB93493_VDC_RCLOCK
mdefine_line|#define MB93493_VDC_RCLOCK&t;0x174&t;/* clock divider, DMA req delay */
DECL|macro|MB93493_VDC_RBLACK
mdefine_line|#define MB93493_VDC_RBLACK&t;0x178&t;/* black insert sizes */
DECL|macro|MB93493_VDC_RS
mdefine_line|#define MB93493_VDC_RS&t;&t;0x17c&t;/* VDC status */
DECL|macro|__addr_MB93493_VDC_BCI
mdefine_line|#define __addr_MB93493_VDC_BCI(X)  ({ (volatile unsigned long *)(__region_CS3 + 0x000 + (X)); })
DECL|macro|__addr_MB93493_VDC_TPO
mdefine_line|#define __addr_MB93493_VDC_TPO(X)  (__region_CS3 + 0x1c0 + (X))
DECL|macro|VDC_TPO_WIDTH
mdefine_line|#define VDC_TPO_WIDTH&t;&t;32
DECL|macro|VDC_RC_DSR
mdefine_line|#define VDC_RC_DSR&t;&t;0x00000080&t;/* VDC master reset */
DECL|macro|VDC_RS_IT
mdefine_line|#define VDC_RS_IT&t;&t;0x00060000&t;/* interrupt indicators */
DECL|macro|VDC_RS_IT_UNDERFLOW
mdefine_line|#define VDC_RS_IT_UNDERFLOW&t;0x00040000&t;/* - underflow event */
DECL|macro|VDC_RS_IT_VSYNC
mdefine_line|#define VDC_RS_IT_VSYNC&t;&t;0x00020000&t;/* - VSYNC event */
DECL|macro|VDC_RS_DFI
mdefine_line|#define VDC_RS_DFI&t;&t;0x00010000&t;/* current interlace field number */
DECL|macro|VDC_RS_DFI_TOP
mdefine_line|#define VDC_RS_DFI_TOP&t;&t;0x00000000&t;/* - top field */
DECL|macro|VDC_RS_DFI_BOTTOM
mdefine_line|#define VDC_RS_DFI_BOTTOM&t;0x00010000&t;/* - bottom field */
DECL|macro|VDC_RS_DCSR
mdefine_line|#define VDC_RS_DCSR&t;&t;0x00000010&t;/* cursor state */
DECL|macro|VDC_RS_DCM
mdefine_line|#define VDC_RS_DCM&t;&t;0x00000003&t;/* display mode */
DECL|macro|VDC_RS_DCM_DISABLED
mdefine_line|#define VDC_RS_DCM_DISABLED&t;0x00000000&t;/* - display disabled */
DECL|macro|VDC_RS_DCM_STOPPED
mdefine_line|#define VDC_RS_DCM_STOPPED&t;0x00000001&t;/* - VDC stopped */
DECL|macro|VDC_RS_DCM_FREERUNNING
mdefine_line|#define VDC_RS_DCM_FREERUNNING&t;0x00000002&t;/* - VDC free-running */
DECL|macro|VDC_RS_DCM_TRANSFERRING
mdefine_line|#define VDC_RS_DCM_TRANSFERRING&t;0x00000003&t;/* - data being transferred to VDC */
multiline_comment|/*&n; * video capture controller&n; */
DECL|macro|__get_MB93493_VCC
mdefine_line|#define __get_MB93493_VCC(X)&t;__get_MB93493(MB93493_VCC_##X)
DECL|macro|__set_MB93493_VCC
mdefine_line|#define __set_MB93493_VCC(X,V)&t;__set_MB93493(MB93493_VCC_##X, (V))
DECL|macro|MB93493_VCC_RREDUCT
mdefine_line|#define MB93493_VCC_RREDUCT&t;0x104&t;/* reduction rate */
DECL|macro|MB93493_VCC_RHY
mdefine_line|#define MB93493_VCC_RHY&t;&t;0x108&t;/* horizontal brightness filter coefficients */
DECL|macro|MB93493_VCC_RHC
mdefine_line|#define MB93493_VCC_RHC&t;&t;0x10c&t;/* horizontal colour-difference filter coefficients */
DECL|macro|MB93493_VCC_RHSIZE
mdefine_line|#define MB93493_VCC_RHSIZE&t;0x110&t;/* horizontal cycle sizes */
DECL|macro|MB93493_VCC_RHBC
mdefine_line|#define MB93493_VCC_RHBC&t;0x114&t;/* horizontal back porch size */
DECL|macro|MB93493_VCC_RVCC
mdefine_line|#define MB93493_VCC_RVCC&t;0x118&t;/* vertical capture period */
DECL|macro|MB93493_VCC_RVBC
mdefine_line|#define MB93493_VCC_RVBC&t;0x11c&t;/* vertical back porch period */
DECL|macro|MB93493_VCC_RV
mdefine_line|#define MB93493_VCC_RV&t;&t;0x120&t;/* vertical filter coefficients */
DECL|macro|MB93493_VCC_RDTS
mdefine_line|#define MB93493_VCC_RDTS&t;0x128&t;/* DMA transfer size */
DECL|macro|MB93493_VCC_RDTS_4B
mdefine_line|#define MB93493_VCC_RDTS_4B&t;0x01000000&t;/* 4-byte transfer */
DECL|macro|MB93493_VCC_RDTS_32B
mdefine_line|#define MB93493_VCC_RDTS_32B&t;0x03000000&t;/* 32-byte transfer */
DECL|macro|MB93493_VCC_RDTS_SHIFT
mdefine_line|#define MB93493_VCC_RDTS_SHIFT&t;24
DECL|macro|MB93493_VCC_RCC
mdefine_line|#define MB93493_VCC_RCC&t;&t;0x130&t;/* VCC control */
DECL|macro|MB93493_VCC_RIS
mdefine_line|#define MB93493_VCC_RIS&t;&t;0x134&t;/* VCC interrupt status */
DECL|macro|__addr_MB93493_VCC_TPI
mdefine_line|#define __addr_MB93493_VCC_TPI(X)  (__region_CS3 + 0x180 + (X))
DECL|macro|VCC_RHSIZE_RHCC
mdefine_line|#define VCC_RHSIZE_RHCC&t;&t;0x000007ff
DECL|macro|VCC_RHSIZE_RHCC_SHIFT
mdefine_line|#define VCC_RHSIZE_RHCC_SHIFT&t;0
DECL|macro|VCC_RHSIZE_RHTCC
mdefine_line|#define VCC_RHSIZE_RHTCC&t;0x0fff0000
DECL|macro|VCC_RHSIZE_RHTCC_SHIFT
mdefine_line|#define VCC_RHSIZE_RHTCC_SHIFT&t;16
DECL|macro|VCC_RVBC_RVBC
mdefine_line|#define VCC_RVBC_RVBC&t;&t;0x00003f00
DECL|macro|VCC_RVBC_RVBC_SHIFT
mdefine_line|#define VCC_RVBC_RVBC_SHIFT&t;8
DECL|macro|VCC_RREDUCT_RHR
mdefine_line|#define VCC_RREDUCT_RHR&t;&t;0x07ff0000
DECL|macro|VCC_RREDUCT_RHR_SHIFT
mdefine_line|#define VCC_RREDUCT_RHR_SHIFT&t;16
DECL|macro|VCC_RREDUCT_RVR
mdefine_line|#define VCC_RREDUCT_RVR&t;&t;0x000007ff
DECL|macro|VCC_RREDUCT_RVR_SHIFT
mdefine_line|#define VCC_RREDUCT_RVR_SHIFT&t;0
DECL|macro|VCC_RCC_CE
mdefine_line|#define VCC_RCC_CE&t;&t;0x00000001&t;/* VCC enable */
DECL|macro|VCC_RCC_CS
mdefine_line|#define VCC_RCC_CS&t;&t;0x00000002&t;/* request video capture start */
DECL|macro|VCC_RCC_CPF
mdefine_line|#define VCC_RCC_CPF&t;&t;0x0000000c&t;/* pixel format */
DECL|macro|VCC_RCC_CPF_YCBCR_16
mdefine_line|#define VCC_RCC_CPF_YCBCR_16&t;0x00000000&t;/* - YCbCr 4:2:2 16-bit format */
DECL|macro|VCC_RCC_CPF_RGB
mdefine_line|#define VCC_RCC_CPF_RGB&t;&t;0x00000004&t;/* - RGB 4:4:4 format */
DECL|macro|VCC_RCC_CPF_YCBCR_24
mdefine_line|#define VCC_RCC_CPF_YCBCR_24&t;0x00000008&t;/* - YCbCr 4:2:2 24-bit format */
DECL|macro|VCC_RCC_CPF_BT656
mdefine_line|#define VCC_RCC_CPF_BT656&t;0x0000000c&t;/* - ITU R-BT.656 format */
DECL|macro|VCC_RCC_CPF_SHIFT
mdefine_line|#define VCC_RCC_CPF_SHIFT&t;2
DECL|macro|VCC_RCC_CSR
mdefine_line|#define VCC_RCC_CSR&t;&t;0x00000080&t;/* request reset */
DECL|macro|VCC_RCC_HSIP
mdefine_line|#define VCC_RCC_HSIP&t;&t;0x00000100&t;/* HSYNC polarity */
DECL|macro|VCC_RCC_HSIP_LOACT
mdefine_line|#define VCC_RCC_HSIP_LOACT&t;0x00000000&t;/* - low active */
DECL|macro|VCC_RCC_HSIP_HIACT
mdefine_line|#define VCC_RCC_HSIP_HIACT&t;0x00000100&t;/* - high active */
DECL|macro|VCC_RCC_VSIP
mdefine_line|#define VCC_RCC_VSIP&t;&t;0x00000200&t;/* VSYNC polarity */
DECL|macro|VCC_RCC_VSIP_LOACT
mdefine_line|#define VCC_RCC_VSIP_LOACT&t;0x00000000&t;/* - low active */
DECL|macro|VCC_RCC_VSIP_HIACT
mdefine_line|#define VCC_RCC_VSIP_HIACT&t;0x00000200&t;/* - high active */
DECL|macro|VCC_RCC_CIE
mdefine_line|#define VCC_RCC_CIE&t;&t;0x00000800&t;/* interrupt enable */
DECL|macro|VCC_RCC_CFP
mdefine_line|#define VCC_RCC_CFP&t;&t;0x00001000&t;/* RGB pixel packing */
DECL|macro|VCC_RCC_CFP_4TO3
mdefine_line|#define VCC_RCC_CFP_4TO3&t;0x00000000&t;/* - pack 4 pixels into 3 words */
DECL|macro|VCC_RCC_CFP_1TO1
mdefine_line|#define VCC_RCC_CFP_1TO1&t;0x00001000&t;/* - pack 1 pixel into 1 words */
DECL|macro|VCC_RCC_CSM
mdefine_line|#define VCC_RCC_CSM&t;&t;0x00006000&t;/* interlace specification */
DECL|macro|VCC_RCC_CSM_ONEPASS
mdefine_line|#define VCC_RCC_CSM_ONEPASS&t;0x00002000&t;/* - non-interlaced */
DECL|macro|VCC_RCC_CSM_INTERLACE
mdefine_line|#define VCC_RCC_CSM_INTERLACE&t;0x00004000&t;/* - interlaced */
DECL|macro|VCC_RCC_CSM_SHIFT
mdefine_line|#define VCC_RCC_CSM_SHIFT&t;13
DECL|macro|VCC_RCC_ES
mdefine_line|#define VCC_RCC_ES&t;&t;0x00008000&t;/* capture start polarity */
DECL|macro|VCC_RCC_ES_NEG
mdefine_line|#define VCC_RCC_ES_NEG&t;&t;0x00000000&t;/* - negative edge */
DECL|macro|VCC_RCC_ES_POS
mdefine_line|#define VCC_RCC_ES_POS&t;&t;0x00008000&t;/* - positive edge */
DECL|macro|VCC_RCC_IFI
mdefine_line|#define VCC_RCC_IFI&t;&t;0x00080000&t;/* inferlace field evaluation reverse */
DECL|macro|VCC_RCC_FDTS
mdefine_line|#define VCC_RCC_FDTS&t;&t;0x00300000&t;/* interlace field start */
DECL|macro|VCC_RCC_FDTS_3_8
mdefine_line|#define VCC_RCC_FDTS_3_8&t;0x00000000&t;/* - 3/8 of horizontal entire cycle */
DECL|macro|VCC_RCC_FDTS_1_4
mdefine_line|#define VCC_RCC_FDTS_1_4&t;0x00100000&t;/* - 1/4 of horizontal entire cycle */
DECL|macro|VCC_RCC_FDTS_7_16
mdefine_line|#define VCC_RCC_FDTS_7_16&t;0x00200000&t;/* - 7/16 of horizontal entire cycle */
DECL|macro|VCC_RCC_FDTS_SHIFT
mdefine_line|#define VCC_RCC_FDTS_SHIFT&t;20
DECL|macro|VCC_RCC_MOV
mdefine_line|#define VCC_RCC_MOV&t;&t;0x00400000&t;/* test bit - always set to 1 */
DECL|macro|VCC_RCC_STP
mdefine_line|#define VCC_RCC_STP&t;&t;0x00800000&t;/* request video capture stop */
DECL|macro|VCC_RCC_TO
mdefine_line|#define VCC_RCC_TO&t;&t;0x01000000&t;/* input during top-field only */
DECL|macro|VCC_RIS_VSYNC
mdefine_line|#define VCC_RIS_VSYNC&t;&t;0x01000000&t;/* VSYNC interrupt */
DECL|macro|VCC_RIS_OV
mdefine_line|#define VCC_RIS_OV&t;&t;0x02000000&t;/* overflow interrupt */
DECL|macro|VCC_RIS_BOTTOM
mdefine_line|#define VCC_RIS_BOTTOM&t;&t;0x08000000&t;/* interlace bottom field */
DECL|macro|VCC_RIS_STARTED
mdefine_line|#define VCC_RIS_STARTED&t;&t;0x10000000&t;/* capture started */
multiline_comment|/*&n; * I2C&n; */
DECL|macro|MB93493_I2C_BSR
mdefine_line|#define MB93493_I2C_BSR &t;0x340&t;&t;/* bus status */
DECL|macro|MB93493_I2C_BCR
mdefine_line|#define MB93493_I2C_BCR&t;&t;0x344&t;&t;/* bus control */
DECL|macro|MB93493_I2C_CCR
mdefine_line|#define MB93493_I2C_CCR&t;&t;0x348&t;&t;/* clock control */
DECL|macro|MB93493_I2C_ADR
mdefine_line|#define MB93493_I2C_ADR&t;&t;0x34c&t;&t;/* address */
DECL|macro|MB93493_I2C_DTR
mdefine_line|#define MB93493_I2C_DTR&t;&t;0x350&t;&t;/* data */
DECL|macro|MB93493_I2C_BC2R
mdefine_line|#define MB93493_I2C_BC2R&t;0x35c&t;&t;/* bus control 2 */
DECL|macro|__addr_MB93493_I2C
mdefine_line|#define __addr_MB93493_I2C(port,X)   (__region_CS3 + MB93493_I2C_##X + ((port)*0x20))
DECL|macro|__get_MB93493_I2C
mdefine_line|#define __get_MB93493_I2C(port,X)    __get_MB93493(MB93493_I2C_##X + ((port)*0x20))
DECL|macro|__set_MB93493_I2C
mdefine_line|#define __set_MB93493_I2C(port,X,V)  __set_MB93493(MB93493_I2C_##X + ((port)*0x20), (V))
DECL|macro|I2C_BSR_BB
mdefine_line|#define I2C_BSR_BB&t;(1 &lt;&lt; 7)
multiline_comment|/*&n; * audio controller (I2S) registers&n; */
DECL|macro|__get_MB93493_I2S
mdefine_line|#define __get_MB93493_I2S(X)&t;__get_MB93493(MB93493_I2S_##X)
DECL|macro|__set_MB93493_I2S
mdefine_line|#define __set_MB93493_I2S(X,V)&t;__set_MB93493(MB93493_I2S_##X, (V))
DECL|macro|MB93493_I2S_ALDR
mdefine_line|#define MB93493_I2S_ALDR&t;0x300&t;&t;/* L-channel data */
DECL|macro|MB93493_I2S_ARDR
mdefine_line|#define MB93493_I2S_ARDR&t;0x304&t;&t;/* R-channel data */
DECL|macro|MB93493_I2S_APDR
mdefine_line|#define MB93493_I2S_APDR&t;0x308&t;&t;/* 16-bit packed data */
DECL|macro|MB93493_I2S_AISTR
mdefine_line|#define MB93493_I2S_AISTR&t;0x310&t;&t;/* status */
DECL|macro|MB93493_I2S_AICR
mdefine_line|#define MB93493_I2S_AICR&t;0x314&t;&t;/* control */
DECL|macro|__addr_MB93493_I2S_ALDR
mdefine_line|#define __addr_MB93493_I2S_ALDR(X)&t;(__region_CS3 + MB93493_I2S_ALDR + (X))
DECL|macro|__addr_MB93493_I2S_ARDR
mdefine_line|#define __addr_MB93493_I2S_ARDR(X)&t;(__region_CS3 + MB93493_I2S_ARDR + (X))
DECL|macro|__addr_MB93493_I2S_APDR
mdefine_line|#define __addr_MB93493_I2S_APDR(X)&t;(__region_CS3 + MB93493_I2S_APDR + (X))
DECL|macro|__addr_MB93493_I2S_ADR
mdefine_line|#define __addr_MB93493_I2S_ADR(X)&t;(__region_CS3 + 0x320 + (X))
DECL|macro|I2S_AISTR_OTST
mdefine_line|#define I2S_AISTR_OTST&t;&t;0x00000003&t;/* status of output data transfer */
DECL|macro|I2S_AISTR_OTR
mdefine_line|#define I2S_AISTR_OTR&t;&t;0x00000010&t;/* output transfer request pending */
DECL|macro|I2S_AISTR_OUR
mdefine_line|#define I2S_AISTR_OUR&t;&t;0x00000020&t;/* output FIFO underrun detected */
DECL|macro|I2S_AISTR_OOR
mdefine_line|#define I2S_AISTR_OOR&t;&t;0x00000040&t;/* output FIFO overrun detected */
DECL|macro|I2S_AISTR_ODS
mdefine_line|#define I2S_AISTR_ODS&t;&t;0x00000100&t;/* output DMA transfer size */
DECL|macro|I2S_AISTR_ODE
mdefine_line|#define I2S_AISTR_ODE&t;&t;0x00000400&t;/* output DMA transfer request enable */
DECL|macro|I2S_AISTR_OTRIE
mdefine_line|#define I2S_AISTR_OTRIE&t;&t;0x00001000&t;/* output transfer request interrupt enable */
DECL|macro|I2S_AISTR_OURIE
mdefine_line|#define I2S_AISTR_OURIE&t;&t;0x00002000&t;/* output FIFO underrun interrupt enable */
DECL|macro|I2S_AISTR_OORIE
mdefine_line|#define I2S_AISTR_OORIE&t;&t;0x00004000&t;/* output FIFO overrun interrupt enable */
DECL|macro|I2S_AISTR__OUT_MASK
mdefine_line|#define I2S_AISTR__OUT_MASK&t;0x00007570
DECL|macro|I2S_AISTR_ITST
mdefine_line|#define I2S_AISTR_ITST&t;&t;0x00030000&t;/* status of input data transfer */
DECL|macro|I2S_AISTR_ITST_SHIFT
mdefine_line|#define I2S_AISTR_ITST_SHIFT&t;16
DECL|macro|I2S_AISTR_ITR
mdefine_line|#define I2S_AISTR_ITR&t;&t;0x00100000&t;/* input transfer request pending */
DECL|macro|I2S_AISTR_IUR
mdefine_line|#define I2S_AISTR_IUR&t;&t;0x00200000&t;/* input FIFO underrun detected */
DECL|macro|I2S_AISTR_IOR
mdefine_line|#define I2S_AISTR_IOR&t;&t;0x00400000&t;/* input FIFO overrun detected */
DECL|macro|I2S_AISTR_IDS
mdefine_line|#define I2S_AISTR_IDS&t;&t;0x01000000&t;/* input DMA transfer size */
DECL|macro|I2S_AISTR_IDE
mdefine_line|#define I2S_AISTR_IDE&t;&t;0x04000000&t;/* input DMA transfer request enable */
DECL|macro|I2S_AISTR_ITRIE
mdefine_line|#define I2S_AISTR_ITRIE&t;&t;0x10000000&t;/* input transfer request interrupt enable */
DECL|macro|I2S_AISTR_IURIE
mdefine_line|#define I2S_AISTR_IURIE&t;&t;0x20000000&t;/* input FIFO underrun interrupt enable */
DECL|macro|I2S_AISTR_IORIE
mdefine_line|#define I2S_AISTR_IORIE&t;&t;0x40000000&t;/* input FIFO overrun interrupt enable */
DECL|macro|I2S_AISTR__IN_MASK
mdefine_line|#define I2S_AISTR__IN_MASK&t;0x75700000
DECL|macro|I2S_AICR_MI
mdefine_line|#define I2S_AICR_MI&t;&t;0x00000001&t;/* mono input requested */
DECL|macro|I2S_AICR_AMI
mdefine_line|#define I2S_AICR_AMI&t;&t;0x00000002&t;/* relation between LRCKI/FS1 and SDI */
DECL|macro|I2S_AICR_LRI
mdefine_line|#define I2S_AICR_LRI&t;&t;0x00000004&t;/* function of LRCKI pin */
DECL|macro|I2S_AICR_SDMI
mdefine_line|#define I2S_AICR_SDMI&t;&t;0x00000070&t;/* format of input audio data */
DECL|macro|I2S_AICR_SDMI_SHIFT
mdefine_line|#define I2S_AICR_SDMI_SHIFT&t;4
DECL|macro|I2S_AICR_CLI
mdefine_line|#define I2S_AICR_CLI&t;&t;0x00000080&t;/* input FIFO clearing control */
DECL|macro|I2S_AICR_IM
mdefine_line|#define I2S_AICR_IM&t;&t;0x00000300&t;/* input state control */
DECL|macro|I2S_AICR_IM_SHIFT
mdefine_line|#define I2S_AICR_IM_SHIFT&t;8
DECL|macro|I2S_AICR__IN_MASK
mdefine_line|#define I2S_AICR__IN_MASK&t;0x000003f7
DECL|macro|I2S_AICR_MO
mdefine_line|#define I2S_AICR_MO&t;&t;0x00001000&t;/* mono output requested */
DECL|macro|I2S_AICR_AMO
mdefine_line|#define I2S_AICR_AMO&t;&t;0x00002000&t;/* relation between LRCKO/FS0 and SDO */
DECL|macro|I2S_AICR_AMO_SHIFT
mdefine_line|#define I2S_AICR_AMO_SHIFT&t;13
DECL|macro|I2S_AICR_LRO
mdefine_line|#define I2S_AICR_LRO&t;&t;0x00004000&t;/* function of LRCKO pin */
DECL|macro|I2S_AICR_SDMO
mdefine_line|#define I2S_AICR_SDMO&t;&t;0x00070000&t;/* format of output audio data */
DECL|macro|I2S_AICR_SDMO_SHIFT
mdefine_line|#define I2S_AICR_SDMO_SHIFT&t;16
DECL|macro|I2S_AICR_CLO
mdefine_line|#define I2S_AICR_CLO&t;&t;0x00080000&t;/* output FIFO clearing control */
DECL|macro|I2S_AICR_OM
mdefine_line|#define I2S_AICR_OM&t;&t;0x00100000&t;/* output state control */
DECL|macro|I2S_AICR__OUT_MASK
mdefine_line|#define I2S_AICR__OUT_MASK&t;0x001f7000
DECL|macro|I2S_AICR_DIV
mdefine_line|#define I2S_AICR_DIV&t;&t;0x03000000&t;/* frequency division rate */
DECL|macro|I2S_AICR_DIV_SHIFT
mdefine_line|#define I2S_AICR_DIV_SHIFT&t;24
DECL|macro|I2S_AICR_FL
mdefine_line|#define I2S_AICR_FL&t;&t;0x20000000&t;/* frame length */
DECL|macro|I2S_AICR_FS
mdefine_line|#define I2S_AICR_FS&t;&t;0x40000000&t;/* frame sync method */
DECL|macro|I2S_AICR_ME
mdefine_line|#define I2S_AICR_ME&t;&t;0x80000000&t;/* master enable */
multiline_comment|/*&n; * PCMCIA&n; */
DECL|macro|__addr_MB93493_PCMCIA
mdefine_line|#define __addr_MB93493_PCMCIA(X)  ((volatile unsigned long *)(__region_CS5 + (X)))
multiline_comment|/*&n; * GPIO&n; */
DECL|macro|__get_MB93493_GPIO_PDR
mdefine_line|#define __get_MB93493_GPIO_PDR(X)&t;__get_MB93493(0x380 + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_PDR
mdefine_line|#define __set_MB93493_GPIO_PDR(X,V)&t;__set_MB93493(0x380 + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_GPDR
mdefine_line|#define __get_MB93493_GPIO_GPDR(X)&t;__get_MB93493(0x384 + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_GPDR
mdefine_line|#define __set_MB93493_GPIO_GPDR(X,V)&t;__set_MB93493(0x384 + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_SIR
mdefine_line|#define __get_MB93493_GPIO_SIR(X)&t;__get_MB93493(0x388 + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_SIR
mdefine_line|#define __set_MB93493_GPIO_SIR(X,V)&t;__set_MB93493(0x388 + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_SOR
mdefine_line|#define __get_MB93493_GPIO_SOR(X)&t;__get_MB93493(0x38c + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_SOR
mdefine_line|#define __set_MB93493_GPIO_SOR(X,V)&t;__set_MB93493(0x38c + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_PDSR
mdefine_line|#define __get_MB93493_GPIO_PDSR(X)&t;__get_MB93493(0x390 + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_PDSR
mdefine_line|#define __set_MB93493_GPIO_PDSR(X,V)&t;__set_MB93493(0x390 + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_PDCR
mdefine_line|#define __get_MB93493_GPIO_PDCR(X)&t;__get_MB93493(0x394 + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_PDCR
mdefine_line|#define __set_MB93493_GPIO_PDCR(X,V)&t;__set_MB93493(0x394 + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_INTST
mdefine_line|#define __get_MB93493_GPIO_INTST(X)&t;__get_MB93493(0x398 + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_INTST
mdefine_line|#define __set_MB93493_GPIO_INTST(X,V)&t;__set_MB93493(0x398 + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_IEHL
mdefine_line|#define __get_MB93493_GPIO_IEHL(X)&t;__get_MB93493(0x39c + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_IEHL
mdefine_line|#define __set_MB93493_GPIO_IEHL(X,V)&t;__set_MB93493(0x39c + (X) * 0xc0, (V))
DECL|macro|__get_MB93493_GPIO_IELH
mdefine_line|#define __get_MB93493_GPIO_IELH(X)&t;__get_MB93493(0x3a0 + (X) * 0xc0)
DECL|macro|__set_MB93493_GPIO_IELH
mdefine_line|#define __set_MB93493_GPIO_IELH(X,V)&t;__set_MB93493(0x3a0 + (X) * 0xc0, (V))
macro_line|#endif /* _ASM_MB93493_REGS_H */
eof
