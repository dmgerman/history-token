macro_line|#ifndef _ASM_SN_SN1_LED_H
DECL|macro|_ASM_SN_SN1_LED_H
mdefine_line|#define _ASM_SN_SN1_LED_H
multiline_comment|/*&n; * Copyright (C) 2000 Silicon Graphics, Inc&n; * Copyright (C) 2000 Jack Steiner (steiner@sgi.com)&n; */
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|LED0
mdefine_line|#define LED0&t;&t;0xc0000b00100000c0LL&t;/* ZZZ fixme */
DECL|macro|LED_AP_START
mdefine_line|#define LED_AP_START&t;0x01&t;&t;/* AP processor started */
DECL|macro|LED_AP_IDLE
mdefine_line|#define LED_AP_IDLE&t;0x01
multiline_comment|/*&n; * Basic macros for flashing the LEDS on an SGI, SN1.&n; */
r_extern
id|__inline__
r_void
DECL|function|HUB_SET_LED
id|HUB_SET_LED
c_func
(paren
r_int
id|val
)paren
(brace
r_int
op_star
id|ledp
suffix:semicolon
r_int
id|eid
suffix:semicolon
id|eid
op_assign
id|hard_processor_sapicid
c_func
(paren
)paren
op_amp
l_int|3
suffix:semicolon
id|ledp
op_assign
(paren
r_int
op_star
)paren
(paren
id|LED0
op_plus
(paren
id|eid
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
op_star
id|ledp
op_assign
id|val
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SN_SN1_LED_H */
eof
