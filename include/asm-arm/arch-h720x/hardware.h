multiline_comment|/*&n; * linux/include/asm-arm/arch-h720x/hardware.h&n; *&n; * Copyright (C) 2000 Jungjun Kim, Hynix Semiconductor Inc.&n; *           (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *           (C) 2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *&n; * This file contains the hardware definitions of the h720x processors&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Do not add implementations specific defines here. This files contains&n; * only defines of the onchip peripherals. Add those defines to boards.h,&n; * which is included by this file.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
DECL|macro|IOCLK
mdefine_line|#define IOCLK (3686400L)
multiline_comment|/* Onchip peripherals */
DECL|macro|IO_VIRT
mdefine_line|#define IO_VIRT&t;&t;&t;0xf0000000&t;/* IO peripherals */
DECL|macro|IO_PHYS
mdefine_line|#define IO_PHYS&t;&t;&t;0x80000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x00050000
macro_line|#ifdef CONFIG_CPU_H7202
macro_line|#include &quot;h7202-regs.h&quot;
macro_line|#elif defined CONFIG_CPU_H7201
macro_line|#include &quot;h7201-regs.h&quot;
macro_line|#else
macro_line|#error machine definition mismatch
macro_line|#endif
multiline_comment|/* Macro to access the CPU IO */
DECL|macro|CPU_IO
mdefine_line|#define CPU_IO(x) (*(volatile u32*)(x))
multiline_comment|/* Macro to access general purpose regs (base, offset) */
DECL|macro|CPU_REG
mdefine_line|#define CPU_REG(x,y) CPU_IO(x+y)
multiline_comment|/* Macro to access irq related regs */
DECL|macro|IRQ_REG
mdefine_line|#define IRQ_REG(x) CPU_REG(IRQC_VIRT,x)
multiline_comment|/* CPU registers */
multiline_comment|/* general purpose I/O */
DECL|macro|GPIO_VIRT
mdefine_line|#define GPIO_VIRT(x)&t;&t;(IO_VIRT + 0x23000 + ((x)&lt;&lt;5))
DECL|macro|GPIO_A_VIRT
mdefine_line|#define GPIO_A_VIRT&t;&t;(GPIO_VIRT(0))
DECL|macro|GPIO_B_VIRT
mdefine_line|#define GPIO_B_VIRT&t;&t;(GPIO_VIRT(1))
DECL|macro|GPIO_C_VIRT
mdefine_line|#define GPIO_C_VIRT&t;&t;(GPIO_VIRT(2))
DECL|macro|GPIO_D_VIRT
mdefine_line|#define GPIO_D_VIRT&t;&t;(GPIO_VIRT(3))
DECL|macro|GPIO_E_VIRT
mdefine_line|#define GPIO_E_VIRT&t;&t;(GPIO_VIRT(4))
DECL|macro|GPIO_AMULSEL
mdefine_line|#define GPIO_AMULSEL&t;&t;(GPIO_VIRT(0) + 0xA4)
DECL|macro|AMULSEL_USIN2
mdefine_line|#define AMULSEL_USIN2&t;(1&lt;&lt;5)
DECL|macro|AMULSEL_USOUT2
mdefine_line|#define AMULSEL_USOUT2&t;(1&lt;&lt;6)
DECL|macro|AMULSEL_USIN3
mdefine_line|#define AMULSEL_USIN3&t;(1&lt;&lt;13)
DECL|macro|AMULSEL_USOUT3
mdefine_line|#define AMULSEL_USOUT3&t;(1&lt;&lt;14)
DECL|macro|AMULSEL_IRDIN
mdefine_line|#define AMULSEL_IRDIN&t;(1&lt;&lt;15)
DECL|macro|AMULSEL_IRDOUT
mdefine_line|#define AMULSEL_IRDOUT&t;(1&lt;&lt;7)
multiline_comment|/* Register offsets general purpose I/O */
DECL|macro|GPIO_DATA
mdefine_line|#define GPIO_DATA&t;&t;0x00
DECL|macro|GPIO_DIR
mdefine_line|#define GPIO_DIR&t;&t;0x04
DECL|macro|GPIO_MASK
mdefine_line|#define GPIO_MASK&t;&t;0x08
DECL|macro|GPIO_STAT
mdefine_line|#define GPIO_STAT&t;&t;0x0C
DECL|macro|GPIO_EDGE
mdefine_line|#define GPIO_EDGE&t;&t;0x10
DECL|macro|GPIO_CLR
mdefine_line|#define GPIO_CLR&t;&t;0x14
DECL|macro|GPIO_POL
mdefine_line|#define GPIO_POL&t;&t;0x18
DECL|macro|GPIO_EN
mdefine_line|#define GPIO_EN&t;&t;&t;0x1C
multiline_comment|/*interrupt controller */
DECL|macro|IRQC_VIRT
mdefine_line|#define IRQC_VIRT&t;&t;(IO_VIRT + 0x24000)
multiline_comment|/* register offset interrupt controller */
DECL|macro|IRQC_IER
mdefine_line|#define IRQC_IER&t;&t;0x00
DECL|macro|IRQC_ISR
mdefine_line|#define IRQC_ISR&t;&t;0x04
multiline_comment|/* timer unit */
DECL|macro|TIMER_VIRT
mdefine_line|#define TIMER_VIRT&t;&t;(IO_VIRT + 0x25000)
multiline_comment|/* Register offsets timer unit */
DECL|macro|TM0_PERIOD
mdefine_line|#define TM0_PERIOD   &t;&t;0x00
DECL|macro|TM0_COUNT
mdefine_line|#define TM0_COUNT    &t;&t;0x08
DECL|macro|TM0_CTRL
mdefine_line|#define TM0_CTRL     &t;&t;0x10
DECL|macro|TM1_PERIOD
mdefine_line|#define TM1_PERIOD   &t;&t;0x20
DECL|macro|TM1_COUNT
mdefine_line|#define TM1_COUNT    &t;&t;0x28
DECL|macro|TM1_CTRL
mdefine_line|#define TM1_CTRL     &t;&t;0x30
DECL|macro|TM2_PERIOD
mdefine_line|#define TM2_PERIOD   &t;&t;0x40
DECL|macro|TM2_COUNT
mdefine_line|#define TM2_COUNT    &t;&t;0x48
DECL|macro|TM2_CTRL
mdefine_line|#define TM2_CTRL     &t;&t;0x50
DECL|macro|TIMER_TOPCTRL
mdefine_line|#define TIMER_TOPCTRL&t;&t;0x60
DECL|macro|TIMER_TOPSTAT
mdefine_line|#define TIMER_TOPSTAT&t;&t;0x64
DECL|macro|T64_COUNTL
mdefine_line|#define T64_COUNTL&t;&t;0x80
DECL|macro|T64_COUNTH
mdefine_line|#define T64_COUNTH&t;&t;0x84
DECL|macro|T64_CTRL
mdefine_line|#define T64_CTRL&t;&t;0x88
DECL|macro|T64_BASEL
mdefine_line|#define T64_BASEL&t;&t;0x94
DECL|macro|T64_BASEH
mdefine_line|#define T64_BASEH&t;&t;0x98
multiline_comment|/* Bitmaks timer unit TOPSTAT reg */
DECL|macro|TSTAT_T0INT
mdefine_line|#define TSTAT_T0INT&t;&t;0x1
DECL|macro|TSTAT_T1INT
mdefine_line|#define TSTAT_T1INT&t;&t;0x2
DECL|macro|TSTAT_T2INT
mdefine_line|#define TSTAT_T2INT&t;&t;0x4
DECL|macro|TSTAT_T3INT
mdefine_line|#define TSTAT_T3INT&t;&t;0x8
multiline_comment|/* Bit description of TMx_CTRL register */
DECL|macro|TM_START
mdefine_line|#define TM_START  &t;&t;0x1
DECL|macro|TM_REPEAT
mdefine_line|#define TM_REPEAT &t;&t;0x2
DECL|macro|TM_RESET
mdefine_line|#define TM_RESET  &t;&t;0x4
multiline_comment|/* Bit description of TIMER_CTRL register */
DECL|macro|ENABLE_TM0_INTR
mdefine_line|#define ENABLE_TM0_INTR  &t;0x1
DECL|macro|ENABLE_TM1_INTR
mdefine_line|#define ENABLE_TM1_INTR  &t;0x2
DECL|macro|ENABLE_TM2_INTR
mdefine_line|#define ENABLE_TM2_INTR  &t;0x4
DECL|macro|TIMER_ENABLE_BIT
mdefine_line|#define TIMER_ENABLE_BIT &t;0x8
DECL|macro|ENABLE_TIMER64
mdefine_line|#define ENABLE_TIMER64   &t;0x10
DECL|macro|ENABLE_TIMER64_INT
mdefine_line|#define ENABLE_TIMER64_INT&t;0x20
multiline_comment|/* PMU &amp; PLL */
DECL|macro|PMU_BASE
mdefine_line|#define PMU_BASE &t;&t;(IO_VIRT + 0x1000)
DECL|macro|PMU_MODE
mdefine_line|#define PMU_MODE&t;&t;0x00
DECL|macro|PMU_STAT
mdefine_line|#define PMU_STAT   &t;&t;0x20
DECL|macro|PMU_PLL_CTRL
mdefine_line|#define PMU_PLL_CTRL &t;&t;0x28
multiline_comment|/* PMU Mode bits */
DECL|macro|PMU_MODE_SLOW
mdefine_line|#define PMU_MODE_SLOW&t;&t;0x00
DECL|macro|PMU_MODE_RUN
mdefine_line|#define PMU_MODE_RUN&t;&t;0x01
DECL|macro|PMU_MODE_IDLE
mdefine_line|#define PMU_MODE_IDLE&t;&t;0x02
DECL|macro|PMU_MODE_SLEEP
mdefine_line|#define PMU_MODE_SLEEP&t;&t;0x03
DECL|macro|PMU_MODE_INIT
mdefine_line|#define PMU_MODE_INIT&t;&t;0x04
DECL|macro|PMU_MODE_DEEPSLEEP
mdefine_line|#define PMU_MODE_DEEPSLEEP&t;0x07
DECL|macro|PMU_MODE_WAKEUP
mdefine_line|#define PMU_MODE_WAKEUP&t;&t;0x08
multiline_comment|/* PMU ... */
DECL|macro|PLL_2_EN
mdefine_line|#define PLL_2_EN&t;&t;0x8000
DECL|macro|PLL_1_EN
mdefine_line|#define PLL_1_EN&t;&t;0x4000
DECL|macro|PLL_3_MUTE
mdefine_line|#define PLL_3_MUTE&t;&t;0x0080
multiline_comment|/* Control bits for PMU/ PLL */
DECL|macro|PMU_WARMRESET
mdefine_line|#define PMU_WARMRESET&t;&t;0x00010000
DECL|macro|PLL_CTRL_MASK23
mdefine_line|#define PLL_CTRL_MASK23&t;&t;0x000080ff
multiline_comment|/* LCD Controller */
DECL|macro|LCD_BASE
mdefine_line|#define LCD_BASE &t;&t;(IO_VIRT + 0x10000)
DECL|macro|LCD_CTRL
mdefine_line|#define LCD_CTRL &t;&t;0x00
DECL|macro|LCD_STATUS
mdefine_line|#define LCD_STATUS&t;&t;0x04
DECL|macro|LCD_STATUS_M
mdefine_line|#define LCD_STATUS_M&t;&t;0x08
DECL|macro|LCD_INTERRUPT
mdefine_line|#define LCD_INTERRUPT&t;&t;0x0C
DECL|macro|LCD_DBAR
mdefine_line|#define LCD_DBAR&t;&t;0x10
DECL|macro|LCD_DCAR
mdefine_line|#define LCD_DCAR&t;&t;0x14
DECL|macro|LCD_TIMING0
mdefine_line|#define LCD_TIMING0 &t;&t;0x20
DECL|macro|LCD_TIMING1
mdefine_line|#define LCD_TIMING1 &t;&t;0x24
DECL|macro|LCD_TIMING2
mdefine_line|#define LCD_TIMING2 &t;&t;0x28
DECL|macro|LCD_TEST
mdefine_line|#define LCD_TEST&t;&t;0x40
multiline_comment|/* LCD Control Bits */
DECL|macro|LCD_CTRL_LCD_ENABLE
mdefine_line|#define LCD_CTRL_LCD_ENABLE   &t;0x00000001
multiline_comment|/* Bits per pixel */
DECL|macro|LCD_CTRL_LCD_BPP_MASK
mdefine_line|#define LCD_CTRL_LCD_BPP_MASK &t;0x00000006
DECL|macro|LCD_CTRL_LCD_4BPP
mdefine_line|#define LCD_CTRL_LCD_4BPP    &t;0x00000000
DECL|macro|LCD_CTRL_LCD_8BPP
mdefine_line|#define LCD_CTRL_LCD_8BPP    &t;0x00000002
DECL|macro|LCD_CTRL_LCD_16BPP
mdefine_line|#define LCD_CTRL_LCD_16BPP   &t;0x00000004
DECL|macro|LCD_CTRL_LCD_BW
mdefine_line|#define LCD_CTRL_LCD_BW&t;&t;0x00000008
DECL|macro|LCD_CTRL_LCD_TFT
mdefine_line|#define LCD_CTRL_LCD_TFT&t;0x00000010
DECL|macro|LCD_CTRL_BGR
mdefine_line|#define LCD_CTRL_BGR&t;&t;0x00001000
DECL|macro|LCD_CTRL_LCD_VCOMP
mdefine_line|#define LCD_CTRL_LCD_VCOMP&t;0x00080000
DECL|macro|LCD_CTRL_LCD_MONO8
mdefine_line|#define LCD_CTRL_LCD_MONO8&t;0x00200000
DECL|macro|LCD_CTRL_LCD_PWR
mdefine_line|#define LCD_CTRL_LCD_PWR&t;0x00400000
DECL|macro|LCD_CTRL_LCD_BLE
mdefine_line|#define LCD_CTRL_LCD_BLE&t;0x00800000
DECL|macro|LCD_CTRL_LDBUSEN
mdefine_line|#define LCD_CTRL_LDBUSEN&t;0x01000000
multiline_comment|/* Palette */
DECL|macro|LCD_PALETTE_BASE
mdefine_line|#define LCD_PALETTE_BASE &t;(IO_VIRT + 0x10400)
multiline_comment|/* Serial ports */
DECL|macro|SERIAL0_OFS
mdefine_line|#define SERIAL0_OFS&t;&t;0x20000
DECL|macro|SERIAL0_VIRT
mdefine_line|#define SERIAL0_VIRT &t;&t;(IO_VIRT + SERIAL0_OFS)
DECL|macro|SERIAL0_BASE
mdefine_line|#define SERIAL0_BASE&t;&t;(IO_PHYS + SERIAL0_OFS)
DECL|macro|SERIAL1_OFS
mdefine_line|#define SERIAL1_OFS&t;&t;0x21000
DECL|macro|SERIAL1_VIRT
mdefine_line|#define SERIAL1_VIRT &t;&t;(IO_VIRT + SERIAL1_OFS)
DECL|macro|SERIAL1_BASE
mdefine_line|#define SERIAL1_BASE&t;&t;(IO_PHYS + SERIAL1_OFS)
DECL|macro|SERIAL_ENABLE
mdefine_line|#define SERIAL_ENABLE&t;&t;0x30
DECL|macro|SERIAL_ENABLE_EN
mdefine_line|#define SERIAL_ENABLE_EN&t;(1&lt;&lt;0)
multiline_comment|/* General defines to pacify gcc */
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE &t;&t;(0)&t;/* for inb, outb and friends */
DECL|macro|PCIO_VIRT
mdefine_line|#define PCIO_VIRT&t;&t;PCIO_BASE
DECL|macro|__ASM_ARCH_HARDWARE_INCMACH_H
mdefine_line|#define __ASM_ARCH_HARDWARE_INCMACH_H
macro_line|#include &quot;boards.h&quot;
DECL|macro|__ASM_ARCH_HARDWARE_INCMACH_H
macro_line|#undef __ASM_ARCH_HARDWARE_INCMACH_H
macro_line|#endif&t;&t;&t;&t;/* __ASM_ARCH_HARDWARE_H */
eof
