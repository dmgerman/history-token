multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcfpit.h -- ColdFire internal PIT timer support defines.&n; *&n; *&t;(C) Copyright 2003, Greg Ungerer (gerg@snapgear.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;mcfpit_h
DECL|macro|mcfpit_h
mdefine_line|#define&t;mcfpit_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Get address specific defines for the 5270/5271 and 5280/5282.&n; */
DECL|macro|MCFPIT_BASE1
mdefine_line|#define&t;MCFPIT_BASE1&t;&t;0x00150000&t;/* Base address of TIMER1 */
DECL|macro|MCFPIT_BASE2
mdefine_line|#define&t;MCFPIT_BASE2&t;&t;0x00160000&t;/* Base address of TIMER2 */
DECL|macro|MCFPIT_BASE3
mdefine_line|#define&t;MCFPIT_BASE3&t;&t;0x00170000&t;/* Base address of TIMER3 */
DECL|macro|MCFPIT_BASE4
mdefine_line|#define&t;MCFPIT_BASE4&t;&t;0x00180000&t;/* Base address of TIMER4 */
multiline_comment|/*&n; *&t;Define the PIT timer register set addresses.&n; */
DECL|struct|mcfpit
r_struct
id|mcfpit
(brace
DECL|member|pcsr
r_int
r_int
id|pcsr
suffix:semicolon
multiline_comment|/* PIT control and status */
DECL|member|pmr
r_int
r_int
id|pmr
suffix:semicolon
multiline_comment|/* PIT modulus register */
DECL|member|pcntr
r_int
r_int
id|pcntr
suffix:semicolon
multiline_comment|/* PIT count register */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Bit definitions for the PIT Control and Status register.&n; */
DECL|macro|MCFPIT_PCSR_CLK1
mdefine_line|#define&t;MCFPIT_PCSR_CLK1&t;0x0000&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK2
mdefine_line|#define&t;MCFPIT_PCSR_CLK2&t;0x0100&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK4
mdefine_line|#define&t;MCFPIT_PCSR_CLK4&t;0x0200&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK8
mdefine_line|#define&t;MCFPIT_PCSR_CLK8&t;0x0300&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK16
mdefine_line|#define&t;MCFPIT_PCSR_CLK16&t;0x0400&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK32
mdefine_line|#define&t;MCFPIT_PCSR_CLK32&t;0x0500&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK64
mdefine_line|#define&t;MCFPIT_PCSR_CLK64&t;0x0600&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK128
mdefine_line|#define&t;MCFPIT_PCSR_CLK128&t;0x0700&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK256
mdefine_line|#define&t;MCFPIT_PCSR_CLK256&t;0x0800&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK512
mdefine_line|#define&t;MCFPIT_PCSR_CLK512&t;0x0900&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK1024
mdefine_line|#define&t;MCFPIT_PCSR_CLK1024&t;0x0a00&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK2048
mdefine_line|#define&t;MCFPIT_PCSR_CLK2048&t;0x0b00&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK4096
mdefine_line|#define&t;MCFPIT_PCSR_CLK4096&t;0x0c00&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK8192
mdefine_line|#define&t;MCFPIT_PCSR_CLK8192&t;0x0d00&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK16384
mdefine_line|#define&t;MCFPIT_PCSR_CLK16384&t;0x0e00&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_CLK32768
mdefine_line|#define&t;MCFPIT_PCSR_CLK32768&t;0x0f00&t;&t;/* System clock divisor */
DECL|macro|MCFPIT_PCSR_DOZE
mdefine_line|#define&t;MCFPIT_PCSR_DOZE&t;0x0040&t;&t;/* Clock run in doze mode */
DECL|macro|MCFPIT_PCSR_HALTED
mdefine_line|#define&t;MCFPIT_PCSR_HALTED&t;0x0020&t;&t;/* Clock run in halt mode */
DECL|macro|MCFPIT_PCSR_OVW
mdefine_line|#define&t;MCFPIT_PCSR_OVW&t;&t;0x0010&t;&t;/* Overwrite PIT counter now */
DECL|macro|MCFPIT_PCSR_PIE
mdefine_line|#define&t;MCFPIT_PCSR_PIE&t;&t;0x0008&t;&t;/* Enable PIT interrupt */
DECL|macro|MCFPIT_PCSR_PIF
mdefine_line|#define&t;MCFPIT_PCSR_PIF&t;&t;0x0004&t;&t;/* PIT interrupt flag */
DECL|macro|MCFPIT_PCSR_RLD
mdefine_line|#define&t;MCFPIT_PCSR_RLD&t;&t;0x0002&t;&t;/* Reload counter */
DECL|macro|MCFPIT_PCSR_EN
mdefine_line|#define&t;MCFPIT_PCSR_EN&t;&t;0x0001&t;&t;/* Enable PIT */
DECL|macro|MCFPIT_PCSR_DISABLE
mdefine_line|#define&t;MCFPIT_PCSR_DISABLE&t;0x0000&t;&t;/* Disable PIT */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* mcfpit_h */
eof
