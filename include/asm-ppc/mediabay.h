multiline_comment|/*&n; * mediabay.h: definitions for using the media bay&n; * on PowerBook 3400 and similar computers.&n; *&n; * Copyright (C) 1997 Paul Mackerras.&n; */
macro_line|#ifndef _PPC_MEDIABAY_H
DECL|macro|_PPC_MEDIABAY_H
mdefine_line|#define _PPC_MEDIABAY_H
macro_line|#ifdef __KERNEL__
DECL|macro|MB_FD
mdefine_line|#define MB_FD&t;0&t;&t;/* media bay contains floppy drive */
DECL|macro|MB_FD1
mdefine_line|#define MB_FD1&t;1&t;&t;/* media bay contains floppy drive */
DECL|macro|MB_CD
mdefine_line|#define MB_CD&t;3&t;&t;/* media bay contains ATA drive such as CD */
DECL|macro|MB_NO
mdefine_line|#define MB_NO&t;7&t;&t;/* media bay contains nothing */
r_void
id|media_bay_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|check_media_bay
c_func
(paren
r_struct
id|device_node
op_star
id|which_bay
comma
r_int
id|what
)paren
suffix:semicolon
r_int
id|check_media_bay_by_base
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|what
)paren
suffix:semicolon
multiline_comment|/* Number of bays in the machine or 0 */
r_extern
r_int
id|media_bay_count
suffix:semicolon
multiline_comment|/* called by pmac-ide.c to register IDE controller for media bay */
r_extern
r_int
id|media_bay_set_ide_infos
c_func
(paren
r_struct
id|device_node
op_star
id|which_bay
comma
r_int
r_int
id|base
comma
r_int
id|irq
comma
r_int
id|index
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC_MEDIABAY_H */
eof
