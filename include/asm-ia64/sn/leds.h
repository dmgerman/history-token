macro_line|#ifndef _ASM_IA64_SN_LEDS_H
DECL|macro|_ASM_IA64_SN_LEDS_H
mdefine_line|#define _ASM_IA64_SN_LEDS_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; * Copyright (C) 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#ifdef CONFIG_IA64_SGI_SN1
DECL|macro|LED0
mdefine_line|#define LED0&t;&t;0xc0000b00100000c0LL&t;/* ZZZ fixme */
DECL|macro|LED_CPU_SHIFT
mdefine_line|#define LED_CPU_SHIFT&t;3
macro_line|#else
macro_line|#include &lt;asm/sn/sn2/shub.h&gt;
DECL|macro|LED0
mdefine_line|#define LED0&t;&t;(LOCAL_MMR_ADDR(SH_REAL_JUNK_BUS_LED0))
DECL|macro|LED_CPU_SHIFT
mdefine_line|#define LED_CPU_SHIFT&t;16
macro_line|#endif
DECL|macro|LED_CPU_HEARTBEAT
mdefine_line|#define LED_CPU_HEARTBEAT&t;0x01
DECL|macro|LED_CPU_ACTIVITY
mdefine_line|#define LED_CPU_ACTIVITY&t;0x02
DECL|macro|LED_MASK_AUTOTEST
mdefine_line|#define LED_MASK_AUTOTEST&t;0xfe
multiline_comment|/*&n; * Basic macros for flashing the LEDS on an SGI, SN1.&n; */
r_static
id|__inline__
r_void
DECL|function|set_led_bits
id|set_led_bits
c_func
(paren
id|u8
id|value
comma
id|u8
id|mask
)paren
(brace
id|pda.led_state
op_assign
(paren
id|pda.led_state
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|value
op_amp
id|mask
)paren
suffix:semicolon
op_star
id|pda.led_address
op_assign
(paren
r_int
)paren
id|pda.led_state
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_SN_LEDS_H */
eof
