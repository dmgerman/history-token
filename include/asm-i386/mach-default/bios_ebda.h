macro_line|#ifndef _MACH_BIOS_EBDA_H
DECL|macro|_MACH_BIOS_EBDA_H
mdefine_line|#define _MACH_BIOS_EBDA_H
multiline_comment|/*&n; * there is a real-mode segmented pointer pointing to the&n; * 4K EBDA area at 0x40E.&n; */
DECL|function|get_bios_ebda
r_static
r_inline
r_int
r_int
id|get_bios_ebda
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|address
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|phys_to_virt
c_func
(paren
l_int|0x40E
)paren
suffix:semicolon
id|address
op_lshift_assign
l_int|4
suffix:semicolon
r_return
id|address
suffix:semicolon
multiline_comment|/* 0 means none */
)brace
macro_line|#endif /* _MACH_BIOS_EBDA_H */
eof
