multiline_comment|/*&n; * include/asm-v850/rte_me2_cb.h -- Midas labs RTE-V850E/ME2-CB board&n; *&n; *  Copyright (C) 2001,02,03  NEC Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_RTE_ME2_CB_H__
DECL|macro|__V850_RTE_ME2_CB_H__
mdefine_line|#define __V850_RTE_ME2_CB_H__
macro_line|#include &lt;asm/rte_cb.h&gt;&t;&t;/* Common defs for Midas RTE-CB boards.  */
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&t;&quot;rte-v850e/me2-cb&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&t;&quot;Midas lab RTE-V850E/ME2-CB&quot;
DECL|macro|CPU_CLOCK_FREQ
mdefine_line|#define CPU_CLOCK_FREQ&t;&t;150000000 /* 150MHz */
DECL|macro|FIXED_BOGOMIPS
mdefine_line|#define FIXED_BOGOMIPS&t;&t;50
multiline_comment|/* 32MB of onbard SDRAM.  */
DECL|macro|SDRAM_ADDR
mdefine_line|#define SDRAM_ADDR&t;&t;0x00800000
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;&t;0x02000000 /* 32MB */
multiline_comment|/* CPU addresses of GBUS memory spaces.  */
DECL|macro|GCS0_ADDR
mdefine_line|#define GCS0_ADDR&t;&t;0x04000000 /* GCS0 - Common SRAM (2MB) */
DECL|macro|GCS0_SIZE
mdefine_line|#define GCS0_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS1_ADDR
mdefine_line|#define GCS1_ADDR&t;&t;0x04800000 /* GCS1 - Flash ROM (8MB) */
DECL|macro|GCS1_SIZE
mdefine_line|#define GCS1_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS2_ADDR
mdefine_line|#define GCS2_ADDR&t;&t;0x07000000 /* GCS2 - I/O registers */
DECL|macro|GCS2_SIZE
mdefine_line|#define GCS2_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS5_ADDR
mdefine_line|#define GCS5_ADDR&t;&t;0x08000000 /* GCS5 - PCI bus space */
DECL|macro|GCS5_SIZE
mdefine_line|#define GCS5_SIZE&t;&t;0x02000000 /*   32MB */
DECL|macro|GCS6_ADDR
mdefine_line|#define GCS6_ADDR&t;&t;0x07800000 /* GCS6 - PCI control registers */
DECL|macro|GCS6_SIZE
mdefine_line|#define GCS6_SIZE&t;&t;0x00800000 /*   8MB */
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET &t;&t;SDRAM_ADDR
macro_line|#ifdef CONFIG_ROM_KERNEL
multiline_comment|/* Kernel is in ROM, starting at address 0.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;&t;0
DECL|macro|ROOT_FS_IMAGE_RW
mdefine_line|#define ROOT_FS_IMAGE_RW&t;0
macro_line|#else /* !CONFIG_ROM_KERNEL */
multiline_comment|/* Using RAM-kernel.  Assume some sort of boot-loader got us loaded at&n;   address 0.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;&t;0
DECL|macro|ROOT_FS_IMAGE_RW
mdefine_line|#define ROOT_FS_IMAGE_RW&t;1
macro_line|#endif /* CONFIG_ROM_KERNEL */
multiline_comment|/* Some misc. on-board devices.  */
multiline_comment|/* Seven-segment LED display (four digits).  */
DECL|macro|LED_ADDR
mdefine_line|#define LED_ADDR(n)&t;&t;(0x0FE02000 + (n))
DECL|macro|LED
mdefine_line|#define LED(n)&t;&t;&t;(*(volatile unsigned char *)LED_ADDR(n))
DECL|macro|LED_NUM_DIGITS
mdefine_line|#define LED_NUM_DIGITS&t;&t;4
multiline_comment|/* On-board PIC.  */
DECL|macro|CB_PIC_BASE_ADDR
mdefine_line|#define CB_PIC_BASE_ADDR &t;0x0FE04000
DECL|macro|CB_PIC_INT0M_ADDR
mdefine_line|#define CB_PIC_INT0M_ADDR &t;(CB_PIC_BASE_ADDR + 0x00)
DECL|macro|CB_PIC_INT0M
mdefine_line|#define CB_PIC_INT0M      &t;(*(volatile u16 *)CB_PIC_INT0M_ADDR)
DECL|macro|CB_PIC_INT1M_ADDR
mdefine_line|#define CB_PIC_INT1M_ADDR &t;(CB_PIC_BASE_ADDR + 0x10)
DECL|macro|CB_PIC_INT1M
mdefine_line|#define CB_PIC_INT1M      &t;(*(volatile u16 *)CB_PIC_INT1M_ADDR)
DECL|macro|CB_PIC_INTR_ADDR
mdefine_line|#define CB_PIC_INTR_ADDR  &t;(CB_PIC_BASE_ADDR + 0x20)
DECL|macro|CB_PIC_INTR
mdefine_line|#define CB_PIC_INTR       &t;(*(volatile u16 *)CB_PIC_INTR_ADDR)
DECL|macro|CB_PIC_INTEN_ADDR
mdefine_line|#define CB_PIC_INTEN_ADDR &t;(CB_PIC_BASE_ADDR + 0x30)
DECL|macro|CB_PIC_INTEN
mdefine_line|#define CB_PIC_INTEN      &t;(*(volatile u16 *)CB_PIC_INTEN_ADDR)
DECL|macro|CB_PIC_INT0EN
mdefine_line|#define CB_PIC_INT0EN        &t;0x0001
DECL|macro|CB_PIC_INT1EN
mdefine_line|#define CB_PIC_INT1EN        &t;0x0002
DECL|macro|CB_PIC_INT0SEL
mdefine_line|#define CB_PIC_INT0SEL       &t;0x0080
multiline_comment|/* The PIC interrupts themselves.  */
DECL|macro|CB_PIC_BASE_IRQ
mdefine_line|#define CB_PIC_BASE_IRQ&t;&t;NUM_CPU_IRQS
DECL|macro|IRQ_CB_PIC_NUM
mdefine_line|#define IRQ_CB_PIC_NUM&t;&t;10
multiline_comment|/* Some specific CB_PIC interrupts. */
DECL|macro|IRQ_CB_EXTTM0
mdefine_line|#define IRQ_CB_EXTTM0&t;&t;(CB_PIC_BASE_IRQ + 0)
DECL|macro|IRQ_CB_EXTSIO
mdefine_line|#define IRQ_CB_EXTSIO&t;&t;(CB_PIC_BASE_IRQ + 1)
DECL|macro|IRQ_CB_TOVER
mdefine_line|#define IRQ_CB_TOVER&t;&t;(CB_PIC_BASE_IRQ + 2)
DECL|macro|IRQ_CB_GINT0
mdefine_line|#define IRQ_CB_GINT0&t;&t;(CB_PIC_BASE_IRQ + 3)
DECL|macro|IRQ_CB_USB
mdefine_line|#define IRQ_CB_USB&t;&t;(CB_PIC_BASE_IRQ + 4)
DECL|macro|IRQ_CB_LANC
mdefine_line|#define IRQ_CB_LANC&t;&t;(CB_PIC_BASE_IRQ + 5)
DECL|macro|IRQ_CB_USB_VBUS_ON
mdefine_line|#define IRQ_CB_USB_VBUS_ON&t;(CB_PIC_BASE_IRQ + 6)
DECL|macro|IRQ_CB_USB_VBUS_OFF
mdefine_line|#define IRQ_CB_USB_VBUS_OFF&t;(CB_PIC_BASE_IRQ + 7)
DECL|macro|IRQ_CB_EXTTM1
mdefine_line|#define IRQ_CB_EXTTM1&t;&t;(CB_PIC_BASE_IRQ + 8)
DECL|macro|IRQ_CB_EXTTM2
mdefine_line|#define IRQ_CB_EXTTM2&t;&t;(CB_PIC_BASE_IRQ + 9)
multiline_comment|/* The GBUS GINT1 - GINT3 (note, not GINT0!) interrupts are connected to&n;   the INTP65 - INTP67 pins on the CPU.  These are shared among the GBUS&n;   interrupts.  */
DECL|macro|IRQ_GINT
mdefine_line|#define IRQ_GINT(n)&t;&t;IRQ_INTP((n) + 9)  /* 0 is unused! */
DECL|macro|IRQ_GINT_NUM
mdefine_line|#define IRQ_GINT_NUM&t;&t;4&t;&t;   /* 0 is unused! */
multiline_comment|/* The shared interrupt line from the PIC is connected to CPU pin INTP23.  */
DECL|macro|IRQ_CB_PIC
mdefine_line|#define IRQ_CB_PIC&t;&t;IRQ_INTP(4) /* P23 */
multiline_comment|/* Used by &lt;asm/rte_cb.h&gt; to derive NUM_MACH_IRQS.  */
DECL|macro|NUM_RTE_CB_IRQS
mdefine_line|#define NUM_RTE_CB_IRQS&t;&t;(NUM_CPU_IRQS + IRQ_CB_PIC_NUM)
macro_line|#ifndef __ASSEMBLY__
DECL|struct|cb_pic_irq_init
r_struct
id|cb_pic_irq_init
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of interrupt type */
multiline_comment|/* Range of kernel irq numbers for this type:&n;&t;   BASE, BASE+INTERVAL, ..., BASE+INTERVAL*NUM  */
DECL|member|base
DECL|member|num
DECL|member|interval
r_int
id|base
comma
id|num
comma
id|interval
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
multiline_comment|/* interrupt priority to assign */
)brace
suffix:semicolon
r_struct
id|hw_interrupt_type
suffix:semicolon
multiline_comment|/* fwd decl */
multiline_comment|/* Enable interrupt handling for interrupt IRQ.  */
r_extern
r_void
id|cb_pic_enable_irq
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Disable interrupt handling for interrupt IRQ.  Note that any interrupts&n;   received while disabled will be delivered once the interrupt is enabled&n;   again, unless they are explicitly cleared using `cb_pic_clear_pending_irq&squot;.  */
r_extern
r_void
id|cb_pic_disable_irq
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Initialize HW_IRQ_TYPES for PIC irqs described in array INITS (which is&n;   terminated by an entry with the name field == 0).  */
r_extern
r_void
id|cb_pic_init_irq_types
(paren
r_struct
id|cb_pic_irq_init
op_star
id|inits
comma
r_struct
id|hw_interrupt_type
op_star
id|hw_irq_types
)paren
suffix:semicolon
multiline_comment|/* Initialize PIC interrupts.  */
r_extern
r_void
id|cb_pic_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* TL16C550C on board UART see also asm/serial.h */
DECL|macro|CB_UART_BASE
mdefine_line|#define CB_UART_BASE    &t;0x0FE08000
DECL|macro|CB_UART_REG_GAP
mdefine_line|#define CB_UART_REG_GAP &t;0x10
DECL|macro|CB_UART_CLOCK
mdefine_line|#define CB_UART_CLOCK   &t;0x16000000
multiline_comment|/* CompactFlash setting see also asm/ide.h, asm/hdreg.h.  */
DECL|macro|CB_CF_BASE
mdefine_line|#define CB_CF_BASE     &t;&t;0x0FE0C000
DECL|macro|CB_CF_CCR_ADDR
mdefine_line|#define CB_CF_CCR_ADDR &t;&t;(CB_CF_BASE+0x200)
DECL|macro|CB_CF_CCR
mdefine_line|#define CB_CF_CCR      &t;&t;(*(volatile u8 *)CB_CF_CCR_ADDR)
DECL|macro|CB_CF_REG0_ADDR
mdefine_line|#define CB_CF_REG0_ADDR&t;&t;(CB_CF_BASE+0x1000)
DECL|macro|CB_CF_REG0
mdefine_line|#define CB_CF_REG0     &t;&t;(*(volatile u16 *)CB_CF_REG0_ADDR)
DECL|macro|CB_CF_STS0_ADDR
mdefine_line|#define CB_CF_STS0_ADDR&t;&t;(CB_CF_BASE+0x1004)
DECL|macro|CB_CF_STS0
mdefine_line|#define CB_CF_STS0     &t;&t;(*(volatile u16 *)CB_CF_STS0_ADDR)
DECL|macro|CB_PCATA_BASE
mdefine_line|#define CB_PCATA_BASE  &t;&t;(CB_CF_BASE+0x800)
DECL|macro|CB_IDE_BASE
mdefine_line|#define CB_IDE_BASE    &t;&t;(CB_CF_BASE+0x9F0)
DECL|macro|CB_IDE_CTRL
mdefine_line|#define CB_IDE_CTRL    &t;&t;(CB_CF_BASE+0xBF6)
DECL|macro|CB_IDE_REG_OFFS
mdefine_line|#define CB_IDE_REG_OFFS&t;&t;0x1
multiline_comment|/* SMSC LAN91C111 setting */
macro_line|#if defined(CONFIG_SMC91111)
DECL|macro|CB_LANC_BASE
mdefine_line|#define CB_LANC_BASE &t;&t;0x0FE10300
DECL|macro|CONFIG_SMC16BITONLY
mdefine_line|#define CONFIG_SMC16BITONLY
DECL|macro|ETH0_ADDR
mdefine_line|#define ETH0_ADDR &t;&t;CB_LANC_BASE
DECL|macro|ETH0_IRQ
mdefine_line|#define ETH0_IRQ &t;&t;IRQ_CB_LANC
macro_line|#endif /* CONFIG_SMC16BITONLY */
DECL|macro|V850E_UART_PRE_CONFIGURE
macro_line|#undef V850E_UART_PRE_CONFIGURE
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;rte_me2_cb_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|rte_me2_cb_uart_pre_configure
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
multiline_comment|/* This board supports RTS/CTS for the on-chip UART, but only for channel 0. */
multiline_comment|/* CTS for UART channel 0 is pin P22 (bit 2 of port 2).  */
DECL|macro|V850E_UART_CTS
mdefine_line|#define V850E_UART_CTS(chan)&t;((chan) == 0 ? !(ME2_PORT2_IO &amp; 0x4) : 1)
multiline_comment|/* RTS for UART channel 0 is pin P21 (bit 1 of port 2).  */
DECL|macro|V850E_UART_SET_RTS
mdefine_line|#define V850E_UART_SET_RTS(chan, val)&t;&t;&t;&t;&t;      &bslash;&n;   do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;   if (chan == 0) {&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;   unsigned old = ME2_PORT2_IO; &t;&t;&t;      &bslash;&n;&t;&t;   if (val)&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   ME2_PORT2_IO = old &amp; ~0x2;&t;&t;&t;      &bslash;&n;&t;&t;   else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   ME2_PORT2_IO = old | 0x2;&t;&t;&t;      &bslash;&n;&t;   }&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   } while (0)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|rte_me2_cb_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_RTE_ME2_CB_H__ */
eof
