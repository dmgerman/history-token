multiline_comment|/* 2001/10/02&n; *&n; * gerdes_amd7930.h     Header-file included by&n; *                      gerdes_amd7930.c&n; *&n; * Author               Christoph Ersfeld &lt;info@formula-n.de&gt;&n; *                      Formula-n Europe AG (www.formula-n.com)&n; *                      previously Gerdes AG&n; *&n; *&n; *                      This file is (c) under GNU PUBLIC LICENSE&n; */
DECL|macro|AMD_CR
mdefine_line|#define AMD_CR&t;&t;0x00
DECL|macro|AMD_DR
mdefine_line|#define AMD_DR&t;&t;0x01
DECL|macro|DBUSY_TIMER_VALUE
mdefine_line|#define DBUSY_TIMER_VALUE 80
r_extern
r_void
id|Amd7930_interrupt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_char
id|irflags
)paren
suffix:semicolon
r_extern
r_void
id|Amd7930_init
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
