multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/hardware.h&n; *&n; * by Alexander Schulz&n; *&n; * derived from:&n; * linux/include/asm-arm/arch-ebsa110/hardware.h&n; * Copyright (C) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Mapping areas&n; */
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x80000000
macro_line|#else
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0
macro_line|#endif
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x08000000
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x40000000
DECL|macro|ROMCARD_SIZE
mdefine_line|#define ROMCARD_SIZE&t;&t;0x08000000
DECL|macro|ROMCARD_START
mdefine_line|#define ROMCARD_START&t;&t;0x10000000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xe0000000
multiline_comment|/* defines for the Framebuffer */
DECL|macro|FB_START
mdefine_line|#define FB_START&t;&t;0x06000000
DECL|macro|FB_SIZE
mdefine_line|#define FB_SIZE&t;&t;&t;0x01000000
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR        0xdf010000
DECL|macro|SEQUOIA_LED_GREEN
mdefine_line|#define SEQUOIA_LED_GREEN       (1&lt;&lt;6)
DECL|macro|SEQUOIA_LED_AMBER
mdefine_line|#define SEQUOIA_LED_AMBER       (1&lt;&lt;5)
DECL|macro|SEQUOIA_LED_BACK
mdefine_line|#define SEQUOIA_LED_BACK        (1&lt;&lt;7)
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()     1
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO          0x6000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM         0x50000000
macro_line|#endif
eof
