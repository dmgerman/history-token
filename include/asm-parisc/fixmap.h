macro_line|#ifndef _ASM_FIXMAP_H
DECL|macro|_ASM_FIXMAP_H
mdefine_line|#define _ASM_FIXMAP_H
multiline_comment|/*&n; * Allocate a 8 Mb temporary mapping area for copy_user_page/clear_user_page.&n; * This area needs to be aligned on a 8 Mb boundary.&n; */
DECL|macro|TMPALIAS_MAP_START
mdefine_line|#define TMPALIAS_MAP_START (__PAGE_OFFSET - 0x01000000)
DECL|macro|FIXADDR_START
mdefine_line|#define FIXADDR_START   ((unsigned long)TMPALIAS_MAP_START)
macro_line|#endif
eof
