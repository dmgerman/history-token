multiline_comment|/* $Id: sunbpp.h,v 1.1 1999/08/08 14:09:49 shadow Exp $&n; * include/asm-sparc/sunbpp.h&n; */
macro_line|#ifndef _ASM_SPARC_SUNBPP_H
DECL|macro|_ASM_SPARC_SUNBPP_H
mdefine_line|#define _ASM_SPARC_SUNBPP_H
DECL|struct|bpp_regs
r_struct
id|bpp_regs
(brace
multiline_comment|/* DMA registers */
DECL|member|p_csr
id|__volatile__
id|__u32
id|p_csr
suffix:semicolon
multiline_comment|/* DMA Control/Status Register */
DECL|member|p_addr
id|__volatile__
id|__u32
id|p_addr
suffix:semicolon
multiline_comment|/* Address Register */
DECL|member|p_bcnt
id|__volatile__
id|__u32
id|p_bcnt
suffix:semicolon
multiline_comment|/* Byte Count Register */
DECL|member|p_tst_csr
id|__volatile__
id|__u32
id|p_tst_csr
suffix:semicolon
multiline_comment|/* Test Control/Status (DMA2 only) */
multiline_comment|/* Parallel Port registers */
DECL|member|p_hcr
id|__volatile__
id|__u16
id|p_hcr
suffix:semicolon
multiline_comment|/* Hardware Configuration Register */
DECL|member|p_ocr
id|__volatile__
id|__u16
id|p_ocr
suffix:semicolon
multiline_comment|/* Operation Configuration Register */
DECL|member|p_dr
id|__volatile__
id|__u8
id|p_dr
suffix:semicolon
multiline_comment|/* Parallel Data Register */
DECL|member|p_tcr
id|__volatile__
id|__u8
id|p_tcr
suffix:semicolon
multiline_comment|/* Transfer Control Register */
DECL|member|p_or
id|__volatile__
id|__u8
id|p_or
suffix:semicolon
multiline_comment|/* Output Register */
DECL|member|p_ir
id|__volatile__
id|__u8
id|p_ir
suffix:semicolon
multiline_comment|/* Input Register */
DECL|member|p_icr
id|__volatile__
id|__u16
id|p_icr
suffix:semicolon
multiline_comment|/* Interrupt Control Register */
)brace
suffix:semicolon
multiline_comment|/* P_HCR. Time is in increments of SBus clock. */
DECL|macro|P_HCR_TEST
mdefine_line|#define P_HCR_TEST      0x8000      /* Allows buried counters to be read */
DECL|macro|P_HCR_DSW
mdefine_line|#define P_HCR_DSW       0x7f00      /* Data strobe width (in ticks) */
DECL|macro|P_HCR_DDS
mdefine_line|#define P_HCR_DDS       0x007f      /* Data setup before strobe (in ticks) */
multiline_comment|/* P_OCR. */
DECL|macro|P_OCR_MEM_CLR
mdefine_line|#define P_OCR_MEM_CLR   0x8000
DECL|macro|P_OCR_DATA_SRC
mdefine_line|#define P_OCR_DATA_SRC  0x4000      /* )                  */
DECL|macro|P_OCR_DS_DSEL
mdefine_line|#define P_OCR_DS_DSEL   0x2000      /* )  Bidirectional      */
DECL|macro|P_OCR_BUSY_DSEL
mdefine_line|#define P_OCR_BUSY_DSEL 0x1000      /* )    selects            */
DECL|macro|P_OCR_ACK_DSEL
mdefine_line|#define P_OCR_ACK_DSEL  0x0800      /* )                  */
DECL|macro|P_OCR_EN_DIAG
mdefine_line|#define P_OCR_EN_DIAG   0x0400
DECL|macro|P_OCR_BUSY_OP
mdefine_line|#define P_OCR_BUSY_OP   0x0200      /* Busy operation */
DECL|macro|P_OCR_ACK_OP
mdefine_line|#define P_OCR_ACK_OP    0x0100      /* Ack operation */
DECL|macro|P_OCR_SRST
mdefine_line|#define P_OCR_SRST      0x0080      /* Reset state machines. Not selfcleaning. */
DECL|macro|P_OCR_IDLE
mdefine_line|#define P_OCR_IDLE      0x0008      /* PP data transfer state machine is idle */
DECL|macro|P_OCR_V_ILCK
mdefine_line|#define P_OCR_V_ILCK    0x0002      /* Versatec faded. Zebra only. */
DECL|macro|P_OCR_EN_VER
mdefine_line|#define P_OCR_EN_VER    0x0001      /* Enable Versatec (0 - enable). Zebra only. */
multiline_comment|/* P_TCR */
DECL|macro|P_TCR_DIR
mdefine_line|#define P_TCR_DIR       0x08
DECL|macro|P_TCR_BUSY
mdefine_line|#define P_TCR_BUSY      0x04
DECL|macro|P_TCR_ACK
mdefine_line|#define P_TCR_ACK       0x02
DECL|macro|P_TCR_DS
mdefine_line|#define P_TCR_DS        0x01        /* Strobe */
multiline_comment|/* P_OR */
DECL|macro|P_OR_V3
mdefine_line|#define P_OR_V3         0x20        /* )                 */
DECL|macro|P_OR_V2
mdefine_line|#define P_OR_V2         0x10        /* ) on Zebra only   */
DECL|macro|P_OR_V1
mdefine_line|#define P_OR_V1         0x08        /* )                 */
DECL|macro|P_OR_INIT
mdefine_line|#define P_OR_INIT       0x04
DECL|macro|P_OR_AFXN
mdefine_line|#define P_OR_AFXN       0x02        /* Auto Feed */
DECL|macro|P_OR_SLCT_IN
mdefine_line|#define P_OR_SLCT_IN    0x01
multiline_comment|/* P_IR */
DECL|macro|P_IR_PE
mdefine_line|#define P_IR_PE         0x04
DECL|macro|P_IR_SLCT
mdefine_line|#define P_IR_SLCT       0x02
DECL|macro|P_IR_ERR
mdefine_line|#define P_IR_ERR        0x01
multiline_comment|/* P_ICR */
DECL|macro|P_DS_IRQ
mdefine_line|#define P_DS_IRQ        0x8000      /* RW1  */
DECL|macro|P_ACK_IRQ
mdefine_line|#define P_ACK_IRQ       0x4000      /* RW1  */
DECL|macro|P_BUSY_IRQ
mdefine_line|#define P_BUSY_IRQ      0x2000      /* RW1  */
DECL|macro|P_PE_IRQ
mdefine_line|#define P_PE_IRQ        0x1000      /* RW1  */
DECL|macro|P_SLCT_IRQ
mdefine_line|#define P_SLCT_IRQ      0x0800      /* RW1  */
DECL|macro|P_ERR_IRQ
mdefine_line|#define P_ERR_IRQ       0x0400      /* RW1  */
DECL|macro|P_DS_IRQ_EN
mdefine_line|#define P_DS_IRQ_EN     0x0200      /* RW   Always on rising edge */
DECL|macro|P_ACK_IRQ_EN
mdefine_line|#define P_ACK_IRQ_EN    0x0100      /* RW   Always on rising edge */
DECL|macro|P_BUSY_IRP
mdefine_line|#define P_BUSY_IRP      0x0080      /* RW   1= rising edge */
DECL|macro|P_BUSY_IRQ_EN
mdefine_line|#define P_BUSY_IRQ_EN   0x0040      /* RW   */
DECL|macro|P_PE_IRP
mdefine_line|#define P_PE_IRP        0x0020      /* RW   1= rising edge */
DECL|macro|P_PE_IRQ_EN
mdefine_line|#define P_PE_IRQ_EN     0x0010      /* RW   */
DECL|macro|P_SLCT_IRP
mdefine_line|#define P_SLCT_IRP      0x0008      /* RW   1= rising edge */
DECL|macro|P_SLCT_IRQ_EN
mdefine_line|#define P_SLCT_IRQ_EN   0x0004      /* RW   */
DECL|macro|P_ERR_IRP
mdefine_line|#define P_ERR_IRP       0x0002      /* RW1  1= rising edge */
DECL|macro|P_ERR_IRQ_EN
mdefine_line|#define P_ERR_IRQ_EN    0x0001      /* RW   */
macro_line|#endif /* !(_ASM_SPARC_SUNBPP_H) */
eof
