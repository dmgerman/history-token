multiline_comment|/* linux/include/asm/arch-s3c2410/regs-udc.h&n; *&n; * Copyright (C) 2004 Herbert Poetzl &lt;herbert@13thfloor.at&gt;&n; *&n; * This include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of&n; * the License, or (at your option) any later version.&n; *&n; *  Changelog:&n; *    01-08-2004&t;Initial creation&n; *    12-09-2004&t;Cleanup for submission&n; *    24-10-2004&t;Fixed S3C2410_UDC_MAXP_REG definition&n; */
macro_line|#ifndef __ASM_ARCH_REGS_UDC_H
DECL|macro|__ASM_ARCH_REGS_UDC_H
mdefine_line|#define __ASM_ARCH_REGS_UDC_H
DECL|macro|S3C2410_USBDREG
mdefine_line|#define S3C2410_USBDREG(x) ((x) + S3C2410_VA_USBDEV)
DECL|macro|S3C2410_UDC_FUNC_ADDR_REG
mdefine_line|#define S3C2410_UDC_FUNC_ADDR_REG&t;S3C2410_USBDREG(0x0140)
DECL|macro|S3C2410_UDC_PWR_REG
mdefine_line|#define S3C2410_UDC_PWR_REG&t;&t;S3C2410_USBDREG(0x0144)
DECL|macro|S3C2410_UDC_EP_INT_REG
mdefine_line|#define S3C2410_UDC_EP_INT_REG&t;&t;S3C2410_USBDREG(0x0148)
DECL|macro|S3C2410_UDC_USB_INT_REG
mdefine_line|#define S3C2410_UDC_USB_INT_REG&t;&t;S3C2410_USBDREG(0x0158)
DECL|macro|S3C2410_UDC_EP_INT_EN_REG
mdefine_line|#define S3C2410_UDC_EP_INT_EN_REG&t;S3C2410_USBDREG(0x015c)
DECL|macro|S3C2410_UDC_USB_INT_EN_REG
mdefine_line|#define S3C2410_UDC_USB_INT_EN_REG&t;S3C2410_USBDREG(0x016c)
DECL|macro|S3C2410_UDC_FRAME_NUM1_REG
mdefine_line|#define S3C2410_UDC_FRAME_NUM1_REG&t;S3C2410_USBDREG(0x0170)
DECL|macro|S3C2410_UDC_FRAME_NUM2_REG
mdefine_line|#define S3C2410_UDC_FRAME_NUM2_REG&t;S3C2410_USBDREG(0x0174)
DECL|macro|S3C2410_UDC_EP0_FIFO_REG
mdefine_line|#define S3C2410_UDC_EP0_FIFO_REG&t;S3C2410_USBDREG(0x01c0)
DECL|macro|S3C2410_UDC_EP1_FIFO_REG
mdefine_line|#define S3C2410_UDC_EP1_FIFO_REG&t;S3C2410_USBDREG(0x01c4)
DECL|macro|S3C2410_UDC_EP2_FIFO_REG
mdefine_line|#define S3C2410_UDC_EP2_FIFO_REG&t;S3C2410_USBDREG(0x01c8)
DECL|macro|S3C2410_UDC_EP3_FIFO_REG
mdefine_line|#define S3C2410_UDC_EP3_FIFO_REG&t;S3C2410_USBDREG(0x01cc)
DECL|macro|S3C2410_UDC_EP4_FIFO_REG
mdefine_line|#define S3C2410_UDC_EP4_FIFO_REG&t;S3C2410_USBDREG(0x01d0)
DECL|macro|S3C2410_UDC_EP1_DMA_CON
mdefine_line|#define S3C2410_UDC_EP1_DMA_CON&t;&t;S3C2410_USBDREG(0x0200)
DECL|macro|S3C2410_UDC_EP1_DMA_UNIT
mdefine_line|#define S3C2410_UDC_EP1_DMA_UNIT&t;S3C2410_USBDREG(0x0204)
DECL|macro|S3C2410_UDC_EP1_DMA_FIFO
mdefine_line|#define S3C2410_UDC_EP1_DMA_FIFO&t;S3C2410_USBDREG(0x0208)
DECL|macro|S3C2410_UDC_EP1_DMA_TTC_L
mdefine_line|#define S3C2410_UDC_EP1_DMA_TTC_L&t;S3C2410_USBDREG(0x020c)
DECL|macro|S3C2410_UDC_EP1_DMA_TTC_M
mdefine_line|#define S3C2410_UDC_EP1_DMA_TTC_M&t;S3C2410_USBDREG(0x0210)
DECL|macro|S3C2410_UDC_EP1_DMA_TTC_H
mdefine_line|#define S3C2410_UDC_EP1_DMA_TTC_H&t;S3C2410_USBDREG(0x0214)
DECL|macro|S3C2410_UDC_EP2_DMA_CON
mdefine_line|#define S3C2410_UDC_EP2_DMA_CON&t;&t;S3C2410_USBDREG(0x0218)
DECL|macro|S3C2410_UDC_EP2_DMA_UNIT
mdefine_line|#define S3C2410_UDC_EP2_DMA_UNIT&t;S3C2410_USBDREG(0x021c)
DECL|macro|S3C2410_UDC_EP2_DMA_FIFO
mdefine_line|#define S3C2410_UDC_EP2_DMA_FIFO&t;S3C2410_USBDREG(0x0220)
DECL|macro|S3C2410_UDC_EP2_DMA_TTC_L
mdefine_line|#define S3C2410_UDC_EP2_DMA_TTC_L&t;S3C2410_USBDREG(0x0224)
DECL|macro|S3C2410_UDC_EP2_DMA_TTC_M
mdefine_line|#define S3C2410_UDC_EP2_DMA_TTC_M&t;S3C2410_USBDREG(0x0228)
DECL|macro|S3C2410_UDC_EP2_DMA_TTC_H
mdefine_line|#define S3C2410_UDC_EP2_DMA_TTC_H&t;S3C2410_USBDREG(0x022c)
DECL|macro|S3C2410_UDC_EP3_DMA_CON
mdefine_line|#define S3C2410_UDC_EP3_DMA_CON&t;&t;S3C2410_USBDREG(0x0240)
DECL|macro|S3C2410_UDC_EP3_DMA_UNIT
mdefine_line|#define S3C2410_UDC_EP3_DMA_UNIT&t;S3C2410_USBDREG(0x0244)
DECL|macro|S3C2410_UDC_EP3_DMA_FIFO
mdefine_line|#define S3C2410_UDC_EP3_DMA_FIFO&t;S3C2410_USBDREG(0x0248)
DECL|macro|S3C2410_UDC_EP3_DMA_TTC_L
mdefine_line|#define S3C2410_UDC_EP3_DMA_TTC_L&t;S3C2410_USBDREG(0x024c)
DECL|macro|S3C2410_UDC_EP3_DMA_TTC_M
mdefine_line|#define S3C2410_UDC_EP3_DMA_TTC_M&t;S3C2410_USBDREG(0x0250)
DECL|macro|S3C2410_UDC_EP3_DMA_TTC_H
mdefine_line|#define S3C2410_UDC_EP3_DMA_TTC_H&t;S3C2410_USBDREG(0x0254)
DECL|macro|S3C2410_UDC_EP4_DMA_CON
mdefine_line|#define S3C2410_UDC_EP4_DMA_CON&t;&t;S3C2410_USBDREG(0x0258)
DECL|macro|S3C2410_UDC_EP4_DMA_UNIT
mdefine_line|#define S3C2410_UDC_EP4_DMA_UNIT&t;S3C2410_USBDREG(0x025c)
DECL|macro|S3C2410_UDC_EP4_DMA_FIFO
mdefine_line|#define S3C2410_UDC_EP4_DMA_FIFO&t;S3C2410_USBDREG(0x0260)
DECL|macro|S3C2410_UDC_EP4_DMA_TTC_L
mdefine_line|#define S3C2410_UDC_EP4_DMA_TTC_L&t;S3C2410_USBDREG(0x0264)
DECL|macro|S3C2410_UDC_EP4_DMA_TTC_M
mdefine_line|#define S3C2410_UDC_EP4_DMA_TTC_M&t;S3C2410_USBDREG(0x0268)
DECL|macro|S3C2410_UDC_EP4_DMA_TTC_H
mdefine_line|#define S3C2410_UDC_EP4_DMA_TTC_H&t;S3C2410_USBDREG(0x026c)
DECL|macro|S3C2410_UDC_INDEX_REG
mdefine_line|#define S3C2410_UDC_INDEX_REG&t;&t;S3C2410_USBDREG(0x0178)
multiline_comment|/* indexed registers */
DECL|macro|S3C2410_UDC_MAXP_REG
mdefine_line|#define S3C2410_UDC_MAXP_REG&t;&t;S3C2410_USBDREG(0x0180)
DECL|macro|S3C2410_UDC_EP0_CSR_REG
mdefine_line|#define S3C2410_UDC_EP0_CSR_REG&t;&t;S3C2410_USBDREG(0x0184)
DECL|macro|S3C2410_UDC_IN_CSR1_REG
mdefine_line|#define S3C2410_UDC_IN_CSR1_REG&t;&t;S3C2410_USBDREG(0x0184)
DECL|macro|S3C2410_UDC_IN_CSR2_REG
mdefine_line|#define S3C2410_UDC_IN_CSR2_REG&t;&t;S3C2410_USBDREG(0x0188)
DECL|macro|S3C2410_UDC_OUT_CSR1_REG
mdefine_line|#define S3C2410_UDC_OUT_CSR1_REG&t;S3C2410_USBDREG(0x0190)
DECL|macro|S3C2410_UDC_OUT_CSR2_REG
mdefine_line|#define S3C2410_UDC_OUT_CSR2_REG&t;S3C2410_USBDREG(0x0194)
DECL|macro|S3C2410_UDC_OUT_FIFO_CNT1_REG
mdefine_line|#define S3C2410_UDC_OUT_FIFO_CNT1_REG&t;S3C2410_USBDREG(0x0198)
DECL|macro|S3C2410_UDC_OUT_FIFO_CNT2_REG
mdefine_line|#define S3C2410_UDC_OUT_FIFO_CNT2_REG&t;S3C2410_USBDREG(0x019c)
DECL|macro|S3C2410_UDC_PWR_ISOUP
mdefine_line|#define S3C2410_UDC_PWR_ISOUP&t;&t;(1&lt;&lt;7) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_PWR_RESET
mdefine_line|#define S3C2410_UDC_PWR_RESET&t;&t;(1&lt;&lt;3) 
singleline_comment|// R
DECL|macro|S3C2410_UDC_PWR_RESUME
mdefine_line|#define S3C2410_UDC_PWR_RESUME&t;&t;(1&lt;&lt;2) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_PWR_SUSPEND
mdefine_line|#define S3C2410_UDC_PWR_SUSPEND&t;&t;(1&lt;&lt;1) 
singleline_comment|// R
DECL|macro|S3C2410_UDC_PWR_ENSUSPEND
mdefine_line|#define S3C2410_UDC_PWR_ENSUSPEND&t;(1&lt;&lt;0) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_PWR_DEFAULT
mdefine_line|#define S3C2410_UDC_PWR_DEFAULT&t;&t;0x00
DECL|macro|S3C2410_UDC_INT_EP4
mdefine_line|#define S3C2410_UDC_INT_EP4&t;&t;(1&lt;&lt;4) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_INT_EP3
mdefine_line|#define S3C2410_UDC_INT_EP3&t;&t;(1&lt;&lt;3) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_INT_EP2
mdefine_line|#define S3C2410_UDC_INT_EP2&t;&t;(1&lt;&lt;2) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_INT_EP1
mdefine_line|#define S3C2410_UDC_INT_EP1&t;&t;(1&lt;&lt;1) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_INT_EP0
mdefine_line|#define S3C2410_UDC_INT_EP0&t;&t;(1&lt;&lt;0) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_USBINT_RESET
mdefine_line|#define S3C2410_UDC_USBINT_RESET&t;(1&lt;&lt;2) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_USBINT_RESUME
mdefine_line|#define S3C2410_UDC_USBINT_RESUME&t;(1&lt;&lt;1) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_USBINT_SUSPEND
mdefine_line|#define S3C2410_UDC_USBINT_SUSPEND&t;(1&lt;&lt;0) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_INTE_EP4
mdefine_line|#define S3C2410_UDC_INTE_EP4&t;&t;(1&lt;&lt;4) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_INTE_EP3
mdefine_line|#define S3C2410_UDC_INTE_EP3&t;&t;(1&lt;&lt;3) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_INTE_EP2
mdefine_line|#define S3C2410_UDC_INTE_EP2&t;&t;(1&lt;&lt;2) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_INTE_EP1
mdefine_line|#define S3C2410_UDC_INTE_EP1&t;&t;(1&lt;&lt;1) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_INTE_EP0
mdefine_line|#define S3C2410_UDC_INTE_EP0&t;&t;(1&lt;&lt;0) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_USBINTE_RESET
mdefine_line|#define S3C2410_UDC_USBINTE_RESET&t;(1&lt;&lt;2) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_USBINTE_SUSPEND
mdefine_line|#define S3C2410_UDC_USBINTE_SUSPEND&t;(1&lt;&lt;0) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_INDEX_EP0
mdefine_line|#define S3C2410_UDC_INDEX_EP0&t;&t;(0x00)
DECL|macro|S3C2410_UDC_INDEX_EP1
mdefine_line|#define S3C2410_UDC_INDEX_EP1&t;&t;(0x01) 
singleline_comment|// ??
DECL|macro|S3C2410_UDC_INDEX_EP2
mdefine_line|#define S3C2410_UDC_INDEX_EP2&t;&t;(0x02) 
singleline_comment|// ??
DECL|macro|S3C2410_UDC_INDEX_EP3
mdefine_line|#define S3C2410_UDC_INDEX_EP3&t;&t;(0x03) 
singleline_comment|// ??
DECL|macro|S3C2410_UDC_INDEX_EP4
mdefine_line|#define S3C2410_UDC_INDEX_EP4&t;&t;(0x04) 
singleline_comment|// ??
DECL|macro|S3C2410_UDC_ICSR1_CLRDT
mdefine_line|#define S3C2410_UDC_ICSR1_CLRDT&t;&t;(1&lt;&lt;6) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_ICSR1_SENTSTL
mdefine_line|#define S3C2410_UDC_ICSR1_SENTSTL&t;(1&lt;&lt;5) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_ICSR1_SENDSTL
mdefine_line|#define S3C2410_UDC_ICSR1_SENDSTL&t;(1&lt;&lt;4) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_ICSR1_FFLUSH
mdefine_line|#define S3C2410_UDC_ICSR1_FFLUSH&t;(1&lt;&lt;3) 
singleline_comment|// W   (set only)
DECL|macro|S3C2410_UDC_ICSR1_UNDRUN
mdefine_line|#define S3C2410_UDC_ICSR1_UNDRUN&t;(1&lt;&lt;2) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_ICSR1_PKTRDY
mdefine_line|#define S3C2410_UDC_ICSR1_PKTRDY&t;(1&lt;&lt;0) 
singleline_comment|// R/W (set only)
DECL|macro|S3C2410_UDC_ICSR2_AUTOSET
mdefine_line|#define S3C2410_UDC_ICSR2_AUTOSET&t;(1&lt;&lt;7) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_ICSR2_ISO
mdefine_line|#define S3C2410_UDC_ICSR2_ISO&t;&t;(1&lt;&lt;6) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_ICSR2_MODEIN
mdefine_line|#define S3C2410_UDC_ICSR2_MODEIN&t;(1&lt;&lt;5) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_ICSR2_DMAIEN
mdefine_line|#define S3C2410_UDC_ICSR2_DMAIEN&t;(1&lt;&lt;4) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_OCSR1_CLRDT
mdefine_line|#define S3C2410_UDC_OCSR1_CLRDT&t;&t;(1&lt;&lt;7) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_OCSR1_SENTSTL
mdefine_line|#define S3C2410_UDC_OCSR1_SENTSTL&t;(1&lt;&lt;6) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_OCSR1_SENDSTL
mdefine_line|#define S3C2410_UDC_OCSR1_SENDSTL&t;(1&lt;&lt;5) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_OCSR1_FFLUSH
mdefine_line|#define S3C2410_UDC_OCSR1_FFLUSH&t;(1&lt;&lt;4) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_OCSR1_DERROR
mdefine_line|#define S3C2410_UDC_OCSR1_DERROR&t;(1&lt;&lt;3) 
singleline_comment|// R
DECL|macro|S3C2410_UDC_OCSR1_OVRRUN
mdefine_line|#define S3C2410_UDC_OCSR1_OVRRUN&t;(1&lt;&lt;2) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_OCSR1_PKTRDY
mdefine_line|#define S3C2410_UDC_OCSR1_PKTRDY&t;(1&lt;&lt;0) 
singleline_comment|// R/W (clear only)
DECL|macro|S3C2410_UDC_OCSR2_AUTOCLR
mdefine_line|#define S3C2410_UDC_OCSR2_AUTOCLR&t;(1&lt;&lt;7) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_OCSR2_ISO
mdefine_line|#define S3C2410_UDC_OCSR2_ISO&t;&t;(1&lt;&lt;6) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_OCSR2_DMAIEN
mdefine_line|#define S3C2410_UDC_OCSR2_DMAIEN&t;(1&lt;&lt;5) 
singleline_comment|// R/W
DECL|macro|S3C2410_UDC_SETIX
mdefine_line|#define S3C2410_UDC_SETIX(x)&t;    &bslash;&n;&t;__raw_writel(S3C2410_UDC_INDEX_ ## x, S3C2410_UDC_INDEX_REG);
DECL|macro|S3C2410_UDC_EP0_CSR_OPKRDY
mdefine_line|#define S3C2410_UDC_EP0_CSR_OPKRDY&t;(1&lt;&lt;0)
DECL|macro|S3C2410_UDC_EP0_CSR_IPKRDY
mdefine_line|#define S3C2410_UDC_EP0_CSR_IPKRDY&t;(1&lt;&lt;1)
DECL|macro|S3C2410_UDC_EP0_CSR_SENTSTL
mdefine_line|#define S3C2410_UDC_EP0_CSR_SENTSTL&t;(1&lt;&lt;2)
DECL|macro|S3C2410_UDC_EP0_CSR_DE
mdefine_line|#define S3C2410_UDC_EP0_CSR_DE&t;&t;(1&lt;&lt;3)
DECL|macro|S3C2410_UDC_EP0_CSR_SE
mdefine_line|#define S3C2410_UDC_EP0_CSR_SE&t;&t;(1&lt;&lt;4)
DECL|macro|S3C2410_UDC_EP0_CSR_SENDSTL
mdefine_line|#define S3C2410_UDC_EP0_CSR_SENDSTL&t;(1&lt;&lt;5)
DECL|macro|S3C2410_UDC_EP0_CSR_SOPKTRDY
mdefine_line|#define S3C2410_UDC_EP0_CSR_SOPKTRDY&t;(1&lt;&lt;6)
DECL|macro|S3C2410_UDC_EP0_CSR_SSE
mdefine_line|#define S3C2410_UDC_EP0_CSR_SSE&t;(1&lt;&lt;7)
DECL|macro|S3C2410_UDC_MAXP_8
mdefine_line|#define S3C2410_UDC_MAXP_8&t;&t;(1&lt;&lt;0)
DECL|macro|S3C2410_UDC_MAXP_16
mdefine_line|#define S3C2410_UDC_MAXP_16&t;&t;(1&lt;&lt;1)
DECL|macro|S3C2410_UDC_MAXP_32
mdefine_line|#define S3C2410_UDC_MAXP_32&t;&t;(1&lt;&lt;2)
DECL|macro|S3C2410_UDC_MAXP_64
mdefine_line|#define S3C2410_UDC_MAXP_64&t;&t;(1&lt;&lt;3)
macro_line|#endif
eof
