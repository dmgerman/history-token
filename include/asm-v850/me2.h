multiline_comment|/*&n; * include/asm-v850/me2.h -- V850E/ME2 cpu chip&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_ME2_H__
DECL|macro|__V850_ME2_H__
mdefine_line|#define __V850_ME2_H__
macro_line|#include &lt;asm/v850e.h&gt;
macro_line|#include &lt;asm/v850e_cache.h&gt;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&quot;v850e/me2&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&quot;NEC V850E/ME2&quot;
multiline_comment|/* Hardware-specific interrupt numbers (in the kernel IRQ namespace).  */
DECL|macro|IRQ_INTP
mdefine_line|#define IRQ_INTP(n)       (n) /* Pnnn (pin) interrupts */
DECL|macro|IRQ_INTP_NUM
mdefine_line|#define IRQ_INTP_NUM      31
DECL|macro|IRQ_INTCMD
mdefine_line|#define IRQ_INTCMD(n)     (0x31 + (n)) /* interval timer interrupts 0-3 */
DECL|macro|IRQ_INTCMD_NUM
mdefine_line|#define IRQ_INTCMD_NUM    4
DECL|macro|IRQ_INTDMA
mdefine_line|#define IRQ_INTDMA(n)     (0x41 + (n)) /* DMA interrupts 0-3 */
DECL|macro|IRQ_INTDMA_NUM
mdefine_line|#define IRQ_INTDMA_NUM    4
DECL|macro|IRQ_INTUBTIRE
mdefine_line|#define IRQ_INTUBTIRE(n)  (0x49 + (n)*5)/* UARTB 0-1 reception error */
DECL|macro|IRQ_INTUBTIRE_NUM
mdefine_line|#define IRQ_INTUBTIRE_NUM 2
DECL|macro|IRQ_INTUBTIR
mdefine_line|#define IRQ_INTUBTIR(n)   (0x4a + (n)*5) /* UARTB 0-1 reception complete */
DECL|macro|IRQ_INTUBTIR_NUM
mdefine_line|#define IRQ_INTUBTIR_NUM  2
DECL|macro|IRQ_INTUBTIT
mdefine_line|#define IRQ_INTUBTIT(n)   (0x4b + (n)*5) /* UARTB 0-1 transmission complete */
DECL|macro|IRQ_INTUBTIT_NUM
mdefine_line|#define IRQ_INTUBTIT_NUM  2
DECL|macro|IRQ_INTUBTIF
mdefine_line|#define IRQ_INTUBTIF(n)   (0x4c + (n)*5) /* UARTB 0-1 FIFO trans. complete */
DECL|macro|IRQ_INTUBTIF_NUM
mdefine_line|#define IRQ_INTUBTIF_NUM  2
DECL|macro|IRQ_INTUBTITO
mdefine_line|#define IRQ_INTUBTITO(n)  (0x4d + (n)*5) /* UARTB 0-1 reception timeout */
DECL|macro|IRQ_INTUBTITO_NUM
mdefine_line|#define IRQ_INTUBTITO_NUM 2
multiline_comment|/* For &lt;asm/irq.h&gt; */
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;&t;0x59 /* V850E/ME2 */
multiline_comment|/* For &lt;asm/entry.h&gt; */
multiline_comment|/* We use on-chip RAM, for a few miscellaneous variables that must be&n;   accessible using a load instruction relative to R0.  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;&t;0xFFFFB000 /* V850E/ME2 */
multiline_comment|/* V850E/ME2 UARTB details.*/
DECL|macro|V850E_UART_NUM_CHANNELS
mdefine_line|#define V850E_UART_NUM_CHANNELS&t;&t;2
DECL|macro|V850E_UARTB_BASE_FREQ
mdefine_line|#define V850E_UARTB_BASE_FREQ&t;&t;(CPU_CLOCK_FREQ / 4)
multiline_comment|/* This is a function that gets called before configuring the UART.  */
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;me2_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|me2_uart_pre_configure
(paren
r_int
id|chan
comma
r_int
id|cflags
comma
r_int
id|baud
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* V850E/ME2 timer C details.  */
DECL|macro|V850E_TIMER_C_BASE_ADDR
mdefine_line|#define V850E_TIMER_C_BASE_ADDR&t;&t;0xFFFFF600
multiline_comment|/* V850E/ME2 timer D details.  */
DECL|macro|V850E_TIMER_D_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_BASE_ADDR&t;&t;0xFFFFF540
DECL|macro|V850E_TIMER_D_TMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMD_BASE_ADDR&t;(V850E_TIMER_D_BASE_ADDR + 0x0)
DECL|macro|V850E_TIMER_D_CMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_CMD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x2)
DECL|macro|V850E_TIMER_D_TMCD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMCD_BASE_ADDR&t;(V850E_TIMER_D_BASE_ADDR + 0x4)
DECL|macro|V850E_TIMER_D_BASE_FREQ
mdefine_line|#define V850E_TIMER_D_BASE_FREQ&t;&t;(CPU_CLOCK_FREQ / 2)
multiline_comment|/* Select iRAM mode.  */
DECL|macro|ME2_IRAMM_ADDR
mdefine_line|#define ME2_IRAMM_ADDR&t;&t;&t;0xFFFFF80A
DECL|macro|ME2_IRAMM
mdefine_line|#define ME2_IRAMM&t;&t;&t;(*(volatile u8*)ME2_IRAMM_ADDR)
multiline_comment|/* Interrupt edge-detection configuration.  INTF(n) and INTR(n) are only&n;   valid for n == 1, 2, or 5.  */
DECL|macro|ME2_INTF_ADDR
mdefine_line|#define ME2_INTF_ADDR(n)&t;&t;(0xFFFFFC00 + (n) * 0x2)
DECL|macro|ME2_INTF
mdefine_line|#define ME2_INTF(n)&t;&t;&t;(*(volatile u8*)ME2_INTF_ADDR(n))
DECL|macro|ME2_INTR_ADDR
mdefine_line|#define ME2_INTR_ADDR(n)&t;&t;(0xFFFFFC20 + (n) * 0x2)
DECL|macro|ME2_INTR
mdefine_line|#define ME2_INTR(n)&t;&t;&t;(*(volatile u8*)ME2_INTR_ADDR(n))
DECL|macro|ME2_INTFAL_ADDR
mdefine_line|#define ME2_INTFAL_ADDR&t;&t;&t;0xFFFFFC10
DECL|macro|ME2_INTFAL
mdefine_line|#define ME2_INTFAL&t;&t;&t;(*(volatile u8*)ME2_INTFAL_ADDR)
DECL|macro|ME2_INTRAL_ADDR
mdefine_line|#define ME2_INTRAL_ADDR&t;&t;&t;0xFFFFFC30
DECL|macro|ME2_INTRAL
mdefine_line|#define ME2_INTRAL&t;&t;&t;(*(volatile u8*)ME2_INTRAL_ADDR)
DECL|macro|ME2_INTFDH_ADDR
mdefine_line|#define ME2_INTFDH_ADDR&t;&t;&t;0xFFFFFC16
DECL|macro|ME2_INTFDH
mdefine_line|#define ME2_INTFDH&t;&t;&t;(*(volatile u16*)ME2_INTFDH_ADDR)
DECL|macro|ME2_INTRDH_ADDR
mdefine_line|#define ME2_INTRDH_ADDR&t;&t;&t;0xFFFFFC36
DECL|macro|ME2_INTRDH
mdefine_line|#define ME2_INTRDH&t;&t;&t;(*(volatile u16*)ME2_INTRDH_ADDR)
DECL|macro|ME2_SESC_ADDR
mdefine_line|#define ME2_SESC_ADDR(n)&t;&t;(0xFFFFF609 + (n) * 0x10)
DECL|macro|ME2_SESC
mdefine_line|#define ME2_SESC(n)&t;&t;&t;(*(volatile u8*)ME2_SESC_ADDR(n))
DECL|macro|ME2_SESA10_ADDR
mdefine_line|#define ME2_SESA10_ADDR&t;&t;&t;0xFFFFF5AD
DECL|macro|ME2_SESA10
mdefine_line|#define ME2_SESA10&t;&t;&t;(*(volatile u8*)ME2_SESA10_ADDR)
DECL|macro|ME2_SESA11_ADDR
mdefine_line|#define ME2_SESA11_ADDR&t;&t;&t;0xFFFFF5DD
DECL|macro|ME2_SESA11
mdefine_line|#define ME2_SESA11&t;&t;&t;(*(volatile u8*)ME2_SESA11_ADDR)
multiline_comment|/* Port 1 */
multiline_comment|/* Direct I/O.  Bits 0-3 are pins P10-P13.  */
DECL|macro|ME2_PORT1_IO_ADDR
mdefine_line|#define ME2_PORT1_IO_ADDR&t;&t;0xFFFFF402
DECL|macro|ME2_PORT1_IO
mdefine_line|#define ME2_PORT1_IO&t;&t;&t;(*(volatile u8 *)ME2_PORT1_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|ME2_PORT1_PM_ADDR
mdefine_line|#define ME2_PORT1_PM_ADDR&t;&t;0xFFFFF422
DECL|macro|ME2_PORT1_PM
mdefine_line|#define ME2_PORT1_PM&t;&t;&t;(*(volatile u8 *)ME2_PORT1_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|ME2_PORT1_PMC_ADDR
mdefine_line|#define ME2_PORT1_PMC_ADDR&t;&t;0xFFFFF442
DECL|macro|ME2_PORT1_PMC
mdefine_line|#define ME2_PORT1_PMC&t;&t;&t;(*(volatile u8 *)ME2_PORT1_PMC_ADDR)
multiline_comment|/* Port function control (for serial interfaces, 0 = CSI30, 1 = UARTB0 ).  */
DECL|macro|ME2_PORT1_PFC_ADDR
mdefine_line|#define ME2_PORT1_PFC_ADDR&t;&t;0xFFFFF462
DECL|macro|ME2_PORT1_PFC
mdefine_line|#define ME2_PORT1_PFC&t;&t;&t;(*(volatile u8 *)ME2_PORT1_PFC_ADDR)
multiline_comment|/* Port 2 */
multiline_comment|/* Direct I/O.  Bits 0-3 are pins P20-P25.  */
DECL|macro|ME2_PORT2_IO_ADDR
mdefine_line|#define ME2_PORT2_IO_ADDR&t;&t;0xFFFFF404
DECL|macro|ME2_PORT2_IO
mdefine_line|#define ME2_PORT2_IO&t;&t;&t;(*(volatile u8 *)ME2_PORT2_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|ME2_PORT2_PM_ADDR
mdefine_line|#define ME2_PORT2_PM_ADDR&t;&t;0xFFFFF424
DECL|macro|ME2_PORT2_PM
mdefine_line|#define ME2_PORT2_PM&t;&t;&t;(*(volatile u8 *)ME2_PORT2_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|ME2_PORT2_PMC_ADDR
mdefine_line|#define ME2_PORT2_PMC_ADDR&t;&t;0xFFFFF444
DECL|macro|ME2_PORT2_PMC
mdefine_line|#define ME2_PORT2_PMC&t;&t;&t;(*(volatile u8 *)ME2_PORT2_PMC_ADDR)
multiline_comment|/* Port function control (for serial interfaces, 0 = INTP2x, 1 = UARTB1 ).  */
DECL|macro|ME2_PORT2_PFC_ADDR
mdefine_line|#define ME2_PORT2_PFC_ADDR&t;&t;0xFFFFF464
DECL|macro|ME2_PORT2_PFC
mdefine_line|#define ME2_PORT2_PFC&t;&t;&t;(*(volatile u8 *)ME2_PORT2_PFC_ADDR)
multiline_comment|/* Port 5 */
multiline_comment|/* Direct I/O.  Bits 0-5 are pins P50-P55.  */
DECL|macro|ME2_PORT5_IO_ADDR
mdefine_line|#define ME2_PORT5_IO_ADDR&t;&t;0xFFFFF40A
DECL|macro|ME2_PORT5_IO
mdefine_line|#define ME2_PORT5_IO&t;&t;&t;(*(volatile u8 *)ME2_PORT5_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|ME2_PORT5_PM_ADDR
mdefine_line|#define ME2_PORT5_PM_ADDR&t;&t;0xFFFFF42A
DECL|macro|ME2_PORT5_PM
mdefine_line|#define ME2_PORT5_PM&t;&t;&t;(*(volatile u8 *)ME2_PORT5_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|ME2_PORT5_PMC_ADDR
mdefine_line|#define ME2_PORT5_PMC_ADDR&t;&t;0xFFFFF44A
DECL|macro|ME2_PORT5_PMC
mdefine_line|#define ME2_PORT5_PMC&t;&t;&t;(*(volatile u8 *)ME2_PORT5_PMC_ADDR)
multiline_comment|/* Port function control ().  */
DECL|macro|ME2_PORT5_PFC_ADDR
mdefine_line|#define ME2_PORT5_PFC_ADDR&t;&t;0xFFFFF46A
DECL|macro|ME2_PORT5_PFC
mdefine_line|#define ME2_PORT5_PFC&t;&t;&t;(*(volatile u8 *)ME2_PORT5_PFC_ADDR)
multiline_comment|/* Port 6 */
multiline_comment|/* Direct I/O.  Bits 5-7 are pins P65-P67.  */
DECL|macro|ME2_PORT6_IO_ADDR
mdefine_line|#define ME2_PORT6_IO_ADDR&t;&t;0xFFFFF40C
DECL|macro|ME2_PORT6_IO
mdefine_line|#define ME2_PORT6_IO&t;&t;&t;(*(volatile u8 *)ME2_PORT6_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|ME2_PORT6_PM_ADDR
mdefine_line|#define ME2_PORT6_PM_ADDR&t;&t;0xFFFFF42C
DECL|macro|ME2_PORT6_PM
mdefine_line|#define ME2_PORT6_PM&t;&t;&t;(*(volatile u8 *)ME2_PORT6_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|ME2_PORT6_PMC_ADDR
mdefine_line|#define ME2_PORT6_PMC_ADDR&t;&t;0xFFFFF44C
DECL|macro|ME2_PORT6_PMC
mdefine_line|#define ME2_PORT6_PMC&t;&t;&t;(*(volatile u8 *)ME2_PORT6_PMC_ADDR)
multiline_comment|/* Port function control ().  */
DECL|macro|ME2_PORT6_PFC_ADDR
mdefine_line|#define ME2_PORT6_PFC_ADDR&t;&t;0xFFFFF46C
DECL|macro|ME2_PORT6_PFC
mdefine_line|#define ME2_PORT6_PFC&t;&t;&t;(*(volatile u8 *)ME2_PORT6_PFC_ADDR)
multiline_comment|/* Port 7 */
multiline_comment|/* Direct I/O.  Bits 2-7 are pins P72-P77.  */
DECL|macro|ME2_PORT7_IO_ADDR
mdefine_line|#define ME2_PORT7_IO_ADDR&t;&t;0xFFFFF40E
DECL|macro|ME2_PORT7_IO
mdefine_line|#define ME2_PORT7_IO&t;&t;&t;(*(volatile u8 *)ME2_PORT7_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|ME2_PORT7_PM_ADDR
mdefine_line|#define ME2_PORT7_PM_ADDR&t;&t;0xFFFFF42E
DECL|macro|ME2_PORT7_PM
mdefine_line|#define ME2_PORT7_PM&t;&t;&t;(*(volatile u8 *)ME2_PORT7_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|ME2_PORT7_PMC_ADDR
mdefine_line|#define ME2_PORT7_PMC_ADDR&t;&t;0xFFFFF44E
DECL|macro|ME2_PORT7_PMC
mdefine_line|#define ME2_PORT7_PMC&t;&t;&t;(*(volatile u8 *)ME2_PORT7_PMC_ADDR)
multiline_comment|/* Port function control ().  */
DECL|macro|ME2_PORT7_PFC_ADDR
mdefine_line|#define ME2_PORT7_PFC_ADDR&t;&t;0xFFFFF46E
DECL|macro|ME2_PORT7_PFC
mdefine_line|#define ME2_PORT7_PFC&t;&t;&t;(*(volatile u8 *)ME2_PORT7_PFC_ADDR)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Initialize V850E/ME2 chip interrupts.  */
r_extern
r_void
id|me2_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_ME2_H__ */
eof
