multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/generic.h&n; *&n; * Author: Nicolas Pitre&n; */
r_extern
r_void
id|__init
id|sa1100_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|sa1100_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|SET_BANK
mdefine_line|#define SET_BANK(__nr,__start,__size) &bslash;&n;&t;mi-&gt;bank[__nr].start = (__start), &bslash;&n;&t;mi-&gt;bank[__nr].size = (__size), &bslash;&n;&t;mi-&gt;bank[__nr].node = (((unsigned)(__start) - PHYS_OFFSET) &gt;&gt; 27)
eof
