macro_line|#ifndef __ASM_MACH_APICDEF_H
DECL|macro|__ASM_MACH_APICDEF_H
mdefine_line|#define __ASM_MACH_APICDEF_H
DECL|macro|APIC_ID_MASK
mdefine_line|#define         APIC_ID_MASK            (0xF&lt;&lt;24)
DECL|function|get_apic_id
r_static
r_inline
r_int
id|get_apic_id
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xF
)paren
suffix:semicolon
)brace
DECL|macro|GET_APIC_ID
mdefine_line|#define         GET_APIC_ID(x)  get_apic_id(x)
macro_line|#endif
eof
