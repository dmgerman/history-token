macro_line|#ifndef _MACH_BIOS_EBDA_H
DECL|macro|_MACH_BIOS_EBDA_H
mdefine_line|#define _MACH_BIOS_EBDA_H
multiline_comment|/*&n; * PC-9800 has no EBDA.&n; * Its BIOS uses 0x40E for other purpose,&n; * Not pointer to 4K EBDA area.&n; */
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/* 0 means none */
)brace
macro_line|#endif /* _MACH_BIOS_EBDA_H */
eof
