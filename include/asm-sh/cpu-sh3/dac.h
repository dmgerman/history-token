macro_line|#ifndef __ASM_SH_DAC_H
DECL|macro|__ASM_SH_DAC_H
mdefine_line|#define __ASM_SH_DAC_H
multiline_comment|/*&n; * Copyright (C) 2003  Andriy Skulysh&n; */
DECL|macro|DADR0
mdefine_line|#define DADR0&t;0xa40000a0
DECL|macro|DADR1
mdefine_line|#define DADR1&t;0xa40000a2
DECL|macro|DACR
mdefine_line|#define DACR&t;0xa40000a4
DECL|macro|DACR_DAOE1
mdefine_line|#define DACR_DAOE1&t;0x80
DECL|macro|DACR_DAOE0
mdefine_line|#define DACR_DAOE0&t;0x40
DECL|macro|DACR_DAE
mdefine_line|#define DACR_DAE&t;0x20
DECL|function|sh_dac_enable
r_static
id|__inline__
r_void
id|sh_dac_enable
c_func
(paren
r_int
id|channel
)paren
(brace
r_int
r_char
id|v
suffix:semicolon
id|v
op_assign
id|ctrl_inb
c_func
(paren
id|DACR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel
)paren
(brace
id|v
op_or_assign
id|DACR_DAOE1
suffix:semicolon
)brace
r_else
id|v
op_or_assign
id|DACR_DAOE0
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|v
comma
id|DACR
)paren
suffix:semicolon
)brace
DECL|function|sh_dac_disable
r_static
id|__inline__
r_void
id|sh_dac_disable
c_func
(paren
r_int
id|channel
)paren
(brace
r_int
r_char
id|v
suffix:semicolon
id|v
op_assign
id|ctrl_inb
c_func
(paren
id|DACR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel
)paren
(brace
id|v
op_and_assign
op_complement
id|DACR_DAOE1
suffix:semicolon
)brace
r_else
id|v
op_and_assign
op_complement
id|DACR_DAOE0
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|v
comma
id|DACR
)paren
suffix:semicolon
)brace
DECL|function|sh_dac_output
r_static
id|__inline__
r_void
id|sh_dac_output
c_func
(paren
id|u8
id|value
comma
r_int
id|channel
)paren
(brace
r_if
c_cond
(paren
id|channel
)paren
(brace
id|ctrl_outb
c_func
(paren
id|value
comma
id|DADR1
)paren
suffix:semicolon
)brace
r_else
id|ctrl_outb
c_func
(paren
id|value
comma
id|DADR0
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SH_DAC_H */
eof
