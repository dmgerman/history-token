multiline_comment|/*&n; *  include/asm-s390/setup.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; */
macro_line|#ifndef _ASM_S390_SETUP_H
DECL|macro|_ASM_S390_SETUP_H
mdefine_line|#define _ASM_S390_SETUP_H
DECL|macro|PARMAREA
mdefine_line|#define PARMAREA&t;&t;0x10400
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE &t;896
DECL|macro|RAMDISK_ORIGIN
mdefine_line|#define RAMDISK_ORIGIN&t;&t;0x800000
DECL|macro|RAMDISK_SIZE
mdefine_line|#define RAMDISK_SIZE&t;&t;0x800000
macro_line|#ifndef __ASSEMBLER__
DECL|macro|IPL_DEVICE
mdefine_line|#define IPL_DEVICE        (*(unsigned long *)  (0x10404))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      (*(unsigned long *)  (0x1040C))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       (*(unsigned long *)  (0x10414))
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE      ((char *)            (0x10480))
multiline_comment|/*&n; * Machine features detected in head.S&n; */
r_extern
r_int
r_int
id|machine_flags
suffix:semicolon
DECL|macro|MACHINE_IS_VM
mdefine_line|#define MACHINE_IS_VM    (machine_flags &amp; 1)
DECL|macro|MACHINE_HAS_IEEE
mdefine_line|#define MACHINE_HAS_IEEE (machine_flags &amp; 2)
DECL|macro|MACHINE_IS_P390
mdefine_line|#define MACHINE_IS_P390  (machine_flags &amp; 4)
DECL|macro|MACHINE_HAS_CSP
mdefine_line|#define MACHINE_HAS_CSP  (machine_flags &amp; 8)
DECL|macro|MACHINE_HAS_MVPG
mdefine_line|#define MACHINE_HAS_MVPG (machine_flags &amp; 16)
macro_line|#else 
DECL|macro|IPL_DEVICE
mdefine_line|#define IPL_DEVICE        0x10404
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      0x1040C
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       0x10414
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE      0x10480
macro_line|#endif
macro_line|#endif
eof
