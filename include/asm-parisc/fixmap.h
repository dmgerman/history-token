macro_line|#ifndef _ASM_FIXMAP_H
DECL|macro|_ASM_FIXMAP_H
mdefine_line|#define _ASM_FIXMAP_H
multiline_comment|/*&n; * Allocate a 8 Mb temporary mapping area for copy_user_page/clear_user_page.&n; * This area needs to be aligned on a 8 Mb boundary.&n; *&n; * FIXME:&n; *&n; * For PA-RISC, this has no meaning.  It is starting to be used on x86&n; * for vsyscalls.  PA will probably do this using space registers.&n; */
multiline_comment|/* This TMPALIAS_MAP_START reserves some of the memory where the&n; * FIXMAP region is on x86.  It&squot;s only real use is to constrain&n; * VMALLOC_END (see pktable.h) */
DECL|macro|TMPALIAS_MAP_START
mdefine_line|#define TMPALIAS_MAP_START (__PAGE_OFFSET - 0x01000000)
macro_line|#endif
eof
