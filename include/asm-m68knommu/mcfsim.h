multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcfsim.h -- ColdFire System Integration Module support.&n; *&n; *&t;(C) Copyright 1999-2003, Greg Ungerer (gerg@snapgear.com)&n; * &t;(C) Copyright 2000, Lineo Inc. (www.lineo.com) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;mcfsim_h
DECL|macro|mcfsim_h
mdefine_line|#define&t;mcfsim_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Include 5204, 5206/e, 5249, 5270/5271, 5272, 5280/5282, 5307 or&n; *&t;5407 specific addresses.&n; */
macro_line|#if defined(CONFIG_M5204)
macro_line|#include &lt;asm/m5204sim.h&gt;
macro_line|#elif defined(CONFIG_M5206) || defined(CONFIG_M5206e)
macro_line|#include &lt;asm/m5206sim.h&gt;
macro_line|#elif defined(CONFIG_M5249)
macro_line|#include &lt;asm/m5249sim.h&gt;
macro_line|#elif defined(CONFIG_M527x)
macro_line|#include &lt;asm/m527xsim.h&gt;
macro_line|#elif defined(CONFIG_M5272)
macro_line|#include &lt;asm/m5272sim.h&gt;
macro_line|#elif defined(CONFIG_M528x)
macro_line|#include &lt;asm/m528xsim.h&gt;
macro_line|#elif defined(CONFIG_M5307)
macro_line|#include &lt;asm/m5307sim.h&gt;
macro_line|#elif defined(CONFIG_M5407)
macro_line|#include &lt;asm/m5407sim.h&gt;
macro_line|#endif
multiline_comment|/*&n; *&t;Define the base address of the SIM within the MBAR address space.&n; */
DECL|macro|MCFSIM_BASE
mdefine_line|#define&t;MCFSIM_BASE&t;&t;0x0&t;&t;/* Base address of SIM */
multiline_comment|/*&n; *&t;Bit definitions for the ICR family of registers.&n; */
DECL|macro|MCFSIM_ICR_AUTOVEC
mdefine_line|#define&t;MCFSIM_ICR_AUTOVEC&t;0x80&t;&t;/* Auto-vectored intr */
DECL|macro|MCFSIM_ICR_LEVEL0
mdefine_line|#define&t;MCFSIM_ICR_LEVEL0&t;0x00&t;&t;/* Level 0 intr */
DECL|macro|MCFSIM_ICR_LEVEL1
mdefine_line|#define&t;MCFSIM_ICR_LEVEL1&t;0x04&t;&t;/* Level 1 intr */
DECL|macro|MCFSIM_ICR_LEVEL2
mdefine_line|#define&t;MCFSIM_ICR_LEVEL2&t;0x08&t;&t;/* Level 2 intr */
DECL|macro|MCFSIM_ICR_LEVEL3
mdefine_line|#define&t;MCFSIM_ICR_LEVEL3&t;0x0c&t;&t;/* Level 3 intr */
DECL|macro|MCFSIM_ICR_LEVEL4
mdefine_line|#define&t;MCFSIM_ICR_LEVEL4&t;0x10&t;&t;/* Level 4 intr */
DECL|macro|MCFSIM_ICR_LEVEL5
mdefine_line|#define&t;MCFSIM_ICR_LEVEL5&t;0x14&t;&t;/* Level 5 intr */
DECL|macro|MCFSIM_ICR_LEVEL6
mdefine_line|#define&t;MCFSIM_ICR_LEVEL6&t;0x18&t;&t;/* Level 6 intr */
DECL|macro|MCFSIM_ICR_LEVEL7
mdefine_line|#define&t;MCFSIM_ICR_LEVEL7&t;0x1c&t;&t;/* Level 7 intr */
DECL|macro|MCFSIM_ICR_PRI0
mdefine_line|#define&t;MCFSIM_ICR_PRI0&t;&t;0x00&t;&t;/* Priority 0 intr */
DECL|macro|MCFSIM_ICR_PRI1
mdefine_line|#define&t;MCFSIM_ICR_PRI1&t;&t;0x01&t;&t;/* Priority 1 intr */
DECL|macro|MCFSIM_ICR_PRI2
mdefine_line|#define&t;MCFSIM_ICR_PRI2&t;&t;0x02&t;&t;/* Priority 2 intr */
DECL|macro|MCFSIM_ICR_PRI3
mdefine_line|#define&t;MCFSIM_ICR_PRI3&t;&t;0x03&t;&t;/* Priority 3 intr */
multiline_comment|/*&n; *&t;Bit definitions for the Interrupt Mask register (IMR).&n; */
DECL|macro|MCFSIM_IMR_EINT1
mdefine_line|#define&t;MCFSIM_IMR_EINT1&t;0x0002&t;&t;/* External intr # 1 */
DECL|macro|MCFSIM_IMR_EINT2
mdefine_line|#define&t;MCFSIM_IMR_EINT2&t;0x0004&t;&t;/* External intr # 2 */
DECL|macro|MCFSIM_IMR_EINT3
mdefine_line|#define&t;MCFSIM_IMR_EINT3&t;0x0008&t;&t;/* External intr # 3 */
DECL|macro|MCFSIM_IMR_EINT4
mdefine_line|#define&t;MCFSIM_IMR_EINT4&t;0x0010&t;&t;/* External intr # 4 */
DECL|macro|MCFSIM_IMR_EINT5
mdefine_line|#define&t;MCFSIM_IMR_EINT5&t;0x0020&t;&t;/* External intr # 5 */
DECL|macro|MCFSIM_IMR_EINT6
mdefine_line|#define&t;MCFSIM_IMR_EINT6&t;0x0040&t;&t;/* External intr # 6 */
DECL|macro|MCFSIM_IMR_EINT7
mdefine_line|#define&t;MCFSIM_IMR_EINT7&t;0x0080&t;&t;/* External intr # 7 */
DECL|macro|MCFSIM_IMR_SWD
mdefine_line|#define&t;MCFSIM_IMR_SWD&t;&t;0x0100&t;&t;/* Software Watchdog intr */
DECL|macro|MCFSIM_IMR_TIMER1
mdefine_line|#define&t;MCFSIM_IMR_TIMER1&t;0x0200&t;&t;/* TIMER 1 intr */
DECL|macro|MCFSIM_IMR_TIMER2
mdefine_line|#define&t;MCFSIM_IMR_TIMER2&t;0x0400&t;&t;/* TIMER 2 intr */
DECL|macro|MCFSIM_IMR_MBUS
mdefine_line|#define MCFSIM_IMR_MBUS&t;&t;0x0800&t;&t;/* MBUS intr&t;*/
DECL|macro|MCFSIM_IMR_UART1
mdefine_line|#define&t;MCFSIM_IMR_UART1&t;0x1000&t;&t;/* UART 1 intr */
DECL|macro|MCFSIM_IMR_UART2
mdefine_line|#define&t;MCFSIM_IMR_UART2&t;0x2000&t;&t;/* UART 2 intr */
macro_line|#if defined(CONFIG_M5206e)
DECL|macro|MCFSIM_IMR_DMA1
mdefine_line|#define&t;MCFSIM_IMR_DMA1&t;&t;0x4000&t;&t;/* DMA 1 intr */
DECL|macro|MCFSIM_IMR_DMA2
mdefine_line|#define&t;MCFSIM_IMR_DMA2&t;&t;0x8000&t;&t;/* DMA 2 intr */
macro_line|#elif defined(CONFIG_M5249) || defined(CONFIG_M5307)
DECL|macro|MCFSIM_IMR_DMA0
mdefine_line|#define&t;MCFSIM_IMR_DMA0&t;&t;0x4000&t;&t;/* DMA 0 intr */
DECL|macro|MCFSIM_IMR_DMA1
mdefine_line|#define&t;MCFSIM_IMR_DMA1&t;&t;0x8000&t;&t;/* DMA 1 intr */
DECL|macro|MCFSIM_IMR_DMA2
mdefine_line|#define&t;MCFSIM_IMR_DMA2&t;&t;0x10000&t;&t;/* DMA 2 intr */
DECL|macro|MCFSIM_IMR_DMA3
mdefine_line|#define&t;MCFSIM_IMR_DMA3&t;&t;0x20000&t;&t;/* DMA 3 intr */
macro_line|#endif
multiline_comment|/*&n; *&t;Mask for all of the SIM devices. Some parts have more or less&n; *&t;SIM devices. This is a catchall for the sandard set.&n; */
macro_line|#ifndef MCFSIM_IMR_MASKALL
DECL|macro|MCFSIM_IMR_MASKALL
mdefine_line|#define&t;MCFSIM_IMR_MASKALL&t;0x3ffe&t;&t;/* All intr sources */
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; *&t;Definition for the interrupt auto-vectoring support.&n; */
r_extern
r_void
id|mcf_autovector
c_func
(paren
r_int
r_int
id|vec
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* mcfsim_h */
eof
