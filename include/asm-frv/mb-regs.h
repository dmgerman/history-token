multiline_comment|/* mb-regs.h: motherboard registers&n; *&n; * Copyright (C) 2003, 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MB_REGS_H
DECL|macro|_ASM_MB_REGS_H
mdefine_line|#define _ASM_MB_REGS_H
macro_line|#include &lt;asm/cpu-irqs.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/mem-layout.h&gt;
DECL|macro|__region_IO
mdefine_line|#define __region_IO&t;KERNEL_IO_START&t;/* the region from 0xe0000000 to 0xffffffff has suitable&n;&t;&t;&t;&t;&t; * protection laid over the top for use in memory-mapped&n;&t;&t;&t;&t;&t; * I/O&n;&t;&t;&t;&t;&t; */
DECL|macro|__region_CS0
mdefine_line|#define __region_CS0&t;0xff000000&t;/* Boot ROMs area */
macro_line|#ifdef CONFIG_MB93091_VDK
multiline_comment|/*&n; * VDK motherboard and CPU card specific stuff&n; */
macro_line|#include &lt;asm/mb93091-fpga-irqs.h&gt;
DECL|macro|IRQ_CPU_MB93493_0
mdefine_line|#define IRQ_CPU_MB93493_0&t;IRQ_CPU_EXTERNAL0
DECL|macro|IRQ_CPU_MB93493_1
mdefine_line|#define IRQ_CPU_MB93493_1&t;IRQ_CPU_EXTERNAL1
DECL|macro|__region_CS2
mdefine_line|#define __region_CS2&t;0xe0000000&t;/* SLBUS/PCI I/O space */
DECL|macro|__region_CS2_M
mdefine_line|#define __region_CS2_M&t;&t;0x0fffffff /* mask */
DECL|macro|__region_CS2_C
mdefine_line|#define __region_CS2_C&t;&t;0x00000000 /* control */
DECL|macro|__region_CS5
mdefine_line|#define __region_CS5&t;0xf0000000&t;/* MB93493 CSC area (DAV daughter board) */
DECL|macro|__region_CS5_M
mdefine_line|#define __region_CS5_M&t;&t;0x00ffffff
DECL|macro|__region_CS5_C
mdefine_line|#define __region_CS5_C&t;&t;0x00010000
DECL|macro|__region_CS7
mdefine_line|#define __region_CS7&t;0xf1000000&t;/* CB70 CPU-card PCMCIA port I/O space */
DECL|macro|__region_CS7_M
mdefine_line|#define __region_CS7_M&t;&t;0x00ffffff
DECL|macro|__region_CS7_C
mdefine_line|#define __region_CS7_C&t;&t;0x00410701
DECL|macro|__region_CS1
mdefine_line|#define __region_CS1&t;0xfc000000&t;/* SLBUS/PCI bridge control registers */
DECL|macro|__region_CS1_M
mdefine_line|#define __region_CS1_M&t;&t;0x000fffff
DECL|macro|__region_CS1_C
mdefine_line|#define __region_CS1_C&t;&t;0x00000000
DECL|macro|__region_CS6
mdefine_line|#define __region_CS6&t;0xfc100000&t;/* CB70 CPU-card DM9000 LAN I/O space */
DECL|macro|__region_CS6_M
mdefine_line|#define __region_CS6_M&t;&t;0x000fffff
DECL|macro|__region_CS6_C
mdefine_line|#define __region_CS6_C&t;&t;0x00400707
DECL|macro|__region_CS3
mdefine_line|#define __region_CS3&t;0xfc200000&t;/* MB93493 CSR area (DAV daughter board) */
DECL|macro|__region_CS3_M
mdefine_line|#define __region_CS3_M&t;&t;0x000fffff
DECL|macro|__region_CS3_C
mdefine_line|#define __region_CS3_C&t;&t;0xc8100000
DECL|macro|__region_CS4
mdefine_line|#define __region_CS4&t;0xfd000000&t;/* CB70 CPU-card extra flash space */
DECL|macro|__region_CS4_M
mdefine_line|#define __region_CS4_M&t;&t;0x00ffffff
DECL|macro|__region_CS4_C
mdefine_line|#define __region_CS4_C&t;&t;0x00000f07
DECL|macro|__region_PCI_IO
mdefine_line|#define __region_PCI_IO&t;&t;(__region_CS2 + 0x04000000UL)
DECL|macro|__region_PCI_MEM
mdefine_line|#define __region_PCI_MEM&t;(__region_CS2 + 0x08000000UL)
DECL|macro|__flush_PCI_writes
mdefine_line|#define __flush_PCI_writes()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__builtin_write8((volatile void *) __region_PCI_MEM, 0);&t;&bslash;&n;} while(0)
DECL|macro|__is_PCI_IO
mdefine_line|#define __is_PCI_IO(addr) &bslash;&n;&t;(((unsigned long)(addr) &gt;&gt; 24) - (__region_PCI_IO &gt;&gt; 24)  &lt; (0x04000000UL &gt;&gt; 24))
DECL|macro|__is_PCI_MEM
mdefine_line|#define __is_PCI_MEM(addr) &bslash;&n;&t;((unsigned long)(addr) - __region_PCI_MEM &lt; 0x08000000UL)
DECL|macro|__get_CLKSW
mdefine_line|#define __get_CLKSW()&t;({ *(volatile unsigned long *)(__region_CS2 + 0x0130000cUL) &amp; 0xffUL; })
DECL|macro|__get_CLKIN
mdefine_line|#define __get_CLKIN()&t;(__get_CLKSW() * 125U * 100000U / 24U)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
id|__nongprelbss
id|mb93090_mb00_detected
suffix:semicolon
macro_line|#endif
DECL|macro|__addr_LEDS
mdefine_line|#define __addr_LEDS()&t;&t;(__region_CS2 + 0x01200004UL)
macro_line|#ifdef CONFIG_MB93090_MB00
DECL|macro|__set_LEDS
mdefine_line|#define __set_LEDS(X)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (mb93090_mb00_detected)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__builtin_write32((void *) __addr_LEDS(), ~(X));&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|__set_LEDS
mdefine_line|#define __set_LEDS(X)
macro_line|#endif
DECL|macro|__addr_LCD
mdefine_line|#define __addr_LCD()&t;&t;(__region_CS2 + 0x01200008UL)
DECL|macro|__get_LCD
mdefine_line|#define __get_LCD(B)&t;&t;__builtin_read32((volatile void *) (B))
DECL|macro|__set_LCD
mdefine_line|#define __set_LCD(B,X)&t;&t;__builtin_write32((volatile void *) (B), (X))
DECL|macro|LCD_D
mdefine_line|#define LCD_D&t;&t;&t;0x000000ff&t;&t;/* LCD data bus */
DECL|macro|LCD_RW
mdefine_line|#define LCD_RW&t;&t;&t;0x00000100&t;&t;/* LCD R/W signal */
DECL|macro|LCD_RS
mdefine_line|#define LCD_RS&t;&t;&t;0x00000200&t;&t;/* LCD Register Select */
DECL|macro|LCD_E
mdefine_line|#define LCD_E&t;&t;&t;0x00000400&t;&t;/* LCD Start Enable Signal */
DECL|macro|LCD_CMD_CLEAR
mdefine_line|#define LCD_CMD_CLEAR&t;&t;(LCD_E|0x001)
DECL|macro|LCD_CMD_HOME
mdefine_line|#define LCD_CMD_HOME&t;&t;(LCD_E|0x002)
DECL|macro|LCD_CMD_CURSOR_INC
mdefine_line|#define LCD_CMD_CURSOR_INC&t;(LCD_E|0x004)
DECL|macro|LCD_CMD_SCROLL_INC
mdefine_line|#define LCD_CMD_SCROLL_INC&t;(LCD_E|0x005)
DECL|macro|LCD_CMD_CURSOR_DEC
mdefine_line|#define LCD_CMD_CURSOR_DEC&t;(LCD_E|0x006)
DECL|macro|LCD_CMD_SCROLL_DEC
mdefine_line|#define LCD_CMD_SCROLL_DEC&t;(LCD_E|0x007)
DECL|macro|LCD_CMD_OFF
mdefine_line|#define LCD_CMD_OFF&t;&t;(LCD_E|0x008)
DECL|macro|LCD_CMD_ON
mdefine_line|#define LCD_CMD_ON(CRSR,BLINK)&t;(LCD_E|0x00c|(CRSR&lt;&lt;1)|BLINK)
DECL|macro|LCD_CMD_CURSOR_MOVE_L
mdefine_line|#define LCD_CMD_CURSOR_MOVE_L&t;(LCD_E|0x010)
DECL|macro|LCD_CMD_CURSOR_MOVE_R
mdefine_line|#define LCD_CMD_CURSOR_MOVE_R&t;(LCD_E|0x014)
DECL|macro|LCD_CMD_DISPLAY_SHIFT_L
mdefine_line|#define LCD_CMD_DISPLAY_SHIFT_L&t;(LCD_E|0x018)
DECL|macro|LCD_CMD_DISPLAY_SHIFT_R
mdefine_line|#define LCD_CMD_DISPLAY_SHIFT_R&t;(LCD_E|0x01c)
DECL|macro|LCD_CMD_FUNCSET
mdefine_line|#define LCD_CMD_FUNCSET(DL,N,F)&t;(LCD_E|0x020|(DL&lt;&lt;4)|(N&lt;&lt;3)|(F&lt;&lt;2))
DECL|macro|LCD_CMD_SET_CG_ADDR
mdefine_line|#define LCD_CMD_SET_CG_ADDR(X)&t;(LCD_E|0x040|X)
DECL|macro|LCD_CMD_SET_DD_ADDR
mdefine_line|#define LCD_CMD_SET_DD_ADDR(X)&t;(LCD_E|0x080|X)
DECL|macro|LCD_CMD_READ_BUSY
mdefine_line|#define LCD_CMD_READ_BUSY&t;(LCD_E|LCD_RW)
DECL|macro|LCD_DATA_WRITE
mdefine_line|#define LCD_DATA_WRITE(X)&t;(LCD_E|LCD_RS|(X))
DECL|macro|LCD_DATA_READ
mdefine_line|#define LCD_DATA_READ&t;&t;(LCD_E|LCD_RS|LCD_RW)
macro_line|#else
multiline_comment|/*&n; * PDK unit specific stuff&n; */
macro_line|#include &lt;asm/mb93093-fpga-irqs.h&gt;
DECL|macro|IRQ_CPU_MB93493_0
mdefine_line|#define IRQ_CPU_MB93493_0&t;IRQ_CPU_EXTERNAL0
DECL|macro|IRQ_CPU_MB93493_1
mdefine_line|#define IRQ_CPU_MB93493_1&t;IRQ_CPU_EXTERNAL1
DECL|macro|__region_CS5
mdefine_line|#define __region_CS5&t;0xf0000000&t;/* MB93493 CSC area (DAV daughter board) */
DECL|macro|__region_CS5_M
mdefine_line|#define __region_CS5_M&t;&t;0x00ffffff /* mask */
DECL|macro|__region_CS5_C
mdefine_line|#define __region_CS5_C&t;&t;0x00010000 /* control */
DECL|macro|__region_CS2
mdefine_line|#define __region_CS2&t;0x20000000&t;/* FPGA registers */
DECL|macro|__region_CS2_M
mdefine_line|#define __region_CS2_M&t;&t;0x000fffff
DECL|macro|__region_CS2_C
mdefine_line|#define __region_CS2_C&t;&t;0x00000000
DECL|macro|__region_CS1
mdefine_line|#define __region_CS1&t;0xfc100000&t;/* LAN registers */
DECL|macro|__region_CS1_M
mdefine_line|#define __region_CS1_M&t;&t;0x000fffff
DECL|macro|__region_CS1_C
mdefine_line|#define __region_CS1_C&t;&t;0x00010404
DECL|macro|__region_CS3
mdefine_line|#define __region_CS3&t;0xfc200000&t;/* MB93493 CSR area (DAV daughter board) */
DECL|macro|__region_CS3_M
mdefine_line|#define __region_CS3_M&t;&t;0x000fffff
DECL|macro|__region_CS3_C
mdefine_line|#define __region_CS3_C&t;&t;0xc8000000
DECL|macro|__region_CS4
mdefine_line|#define __region_CS4&t;0xfd000000&t;/* extra ROMs area */
DECL|macro|__region_CS4_M
mdefine_line|#define __region_CS4_M&t;&t;0x00ffffff
DECL|macro|__region_CS4_C
mdefine_line|#define __region_CS4_C&t;&t;0x00000f07
DECL|macro|__region_CS6
mdefine_line|#define __region_CS6&t;0xfe000000&t;/* not used - hide behind CPU resource I/O regs */
DECL|macro|__region_CS6_M
mdefine_line|#define __region_CS6_M&t;&t;0x000fffff
DECL|macro|__region_CS6_C
mdefine_line|#define __region_CS6_C&t;&t;0x00000f07
DECL|macro|__region_CS7
mdefine_line|#define __region_CS7&t;0xfe000000&t;/* not used - hide behind CPU resource I/O regs */
DECL|macro|__region_CS7_M
mdefine_line|#define __region_CS7_M&t;&t;0x000fffff
DECL|macro|__region_CS7_C
mdefine_line|#define __region_CS7_C&t;&t;0x00000f07
DECL|macro|__is_PCI_IO
mdefine_line|#define __is_PCI_IO(addr)&t;0&t;/* no PCI */
DECL|macro|__is_PCI_MEM
mdefine_line|#define __is_PCI_MEM(addr)&t;0
DECL|macro|__region_PCI_IO
mdefine_line|#define __region_PCI_IO&t;&t;0
DECL|macro|__region_PCI_MEM
mdefine_line|#define __region_PCI_MEM&t;0
DECL|macro|__flush_PCI_writes
mdefine_line|#define __flush_PCI_writes()&t;do { } while(0)
DECL|macro|__get_CLKSW
mdefine_line|#define __get_CLKSW()&t;&t;0UL
DECL|macro|__get_CLKIN
mdefine_line|#define __get_CLKIN()&t;&t;66000000UL
DECL|macro|__addr_LEDS
mdefine_line|#define __addr_LEDS()&t;&t;(__region_CS2 + 0x00000023UL)
DECL|macro|__set_LEDS
mdefine_line|#define __set_LEDS(X)&t;&t;__builtin_write8((volatile void *) __addr_LEDS(), (X))
DECL|macro|__addr_FPGATR
mdefine_line|#define __addr_FPGATR()&t;&t;(__region_CS2 + 0x00000030UL)
DECL|macro|__set_FPGATR
mdefine_line|#define __set_FPGATR(X)&t;&t;__builtin_write32((volatile void *) __addr_FPGATR(), (X))
DECL|macro|__get_FPGATR
mdefine_line|#define __get_FPGATR()&t;&t;__builtin_read32((volatile void *) __addr_FPGATR())
DECL|macro|MB93093_FPGA_FPGATR_AUDIO_CLK
mdefine_line|#define MB93093_FPGA_FPGATR_AUDIO_CLK&t;0x00000003
DECL|macro|__set_FPGATR_AUDIO_CLK
mdefine_line|#define __set_FPGATR_AUDIO_CLK(V) &bslash;&n;&t;__set_FPGATR((__get_FPGATR() &amp; ~MB93093_FPGA_FPGATR_AUDIO_CLK) | (V))
DECL|macro|MB93093_FPGA_FPGATR_AUDIO_CLK_OFF
mdefine_line|#define MB93093_FPGA_FPGATR_AUDIO_CLK_OFF&t;0x0
DECL|macro|MB93093_FPGA_FPGATR_AUDIO_CLK_11MHz
mdefine_line|#define MB93093_FPGA_FPGATR_AUDIO_CLK_11MHz&t;0x1
DECL|macro|MB93093_FPGA_FPGATR_AUDIO_CLK_12MHz
mdefine_line|#define MB93093_FPGA_FPGATR_AUDIO_CLK_12MHz&t;0x2
DECL|macro|MB93093_FPGA_FPGATR_AUDIO_CLK_02MHz
mdefine_line|#define MB93093_FPGA_FPGATR_AUDIO_CLK_02MHz&t;0x3
DECL|macro|MB93093_FPGA_SWR_PUSHSWMASK
mdefine_line|#define MB93093_FPGA_SWR_PUSHSWMASK&t;(0x1F&lt;&lt;26)
DECL|macro|MB93093_FPGA_SWR_PUSHSW4
mdefine_line|#define MB93093_FPGA_SWR_PUSHSW4&t;(1&lt;&lt;29)
DECL|macro|__addr_FPGA_SWR
mdefine_line|#define __addr_FPGA_SWR&t;&t;((volatile void *)(__region_CS2 + 0x28UL))
DECL|macro|__get_FPGA_PUSHSW1_5
mdefine_line|#define __get_FPGA_PUSHSW1_5()&t;(__builtin_read32(__addr_FPGA_SWR) &amp; MB93093_FPGA_SWR_PUSHSWMASK)
macro_line|#endif
macro_line|#endif /* _ASM_MB_REGS_H */
eof
