macro_line|#ifndef _LINUX_BOOT_H
DECL|macro|_LINUX_BOOT_H
mdefine_line|#define _LINUX_BOOT_H
multiline_comment|/* Don&squot;t touch these, unless you really know what you&squot;re doing. */
DECL|macro|DEF_INITSEG
mdefine_line|#define DEF_INITSEG&t;0x9000
DECL|macro|DEF_SYSSEG
mdefine_line|#define DEF_SYSSEG&t;0x1000
DECL|macro|DEF_SETUPSEG
mdefine_line|#define DEF_SETUPSEG&t;0x9020
DECL|macro|DEF_SYSSIZE
mdefine_line|#define DEF_SYSSIZE&t;0x7F00
multiline_comment|/* Internal svga startup constants */
DECL|macro|NORMAL_VGA
mdefine_line|#define NORMAL_VGA&t;0xffff&t;&t;/* 80x25 mode */
DECL|macro|EXTENDED_VGA
mdefine_line|#define EXTENDED_VGA&t;0xfffe&t;&t;/* 80x50 mode */
DECL|macro|ASK_VGA
mdefine_line|#define ASK_VGA&t;&t;0xfffd&t;&t;/* ask for it at bootup */
macro_line|#endif
eof
