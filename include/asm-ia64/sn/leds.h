multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; * Copyright (C) 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_LEDS_H
DECL|macro|_ASM_IA64_SN_LEDS_H
mdefine_line|#define _ASM_IA64_SN_LEDS_H
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/sn/shub_mmr.h&gt;
DECL|macro|LED0
mdefine_line|#define LED0&t;&t;(LOCAL_MMR_ADDR(SH_REAL_JUNK_BUS_LED0))
DECL|macro|LED_CPU_SHIFT
mdefine_line|#define LED_CPU_SHIFT&t;16
DECL|macro|LED_CPU_HEARTBEAT
mdefine_line|#define LED_CPU_HEARTBEAT&t;0x01
DECL|macro|LED_CPU_ACTIVITY
mdefine_line|#define LED_CPU_ACTIVITY&t;0x02
DECL|macro|LED_ALWAYS_SET
mdefine_line|#define LED_ALWAYS_SET&t;&t;0x00
multiline_comment|/*&n; * Basic macros for flashing the LEDS on an SGI SN.&n; */
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
id|pda-&gt;led_state
op_assign
(paren
id|pda-&gt;led_state
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
id|pda-&gt;led_address
op_assign
(paren
r_int
)paren
id|pda-&gt;led_state
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_SN_LEDS_H */
eof
