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
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifndef __s390x__
DECL|macro|IPL_DEVICE
mdefine_line|#define IPL_DEVICE        (*(unsigned long *)  (0x10404))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      (*(unsigned long *)  (0x1040C))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       (*(unsigned long *)  (0x10414))
macro_line|#else /* __s390x__ */
DECL|macro|IPL_DEVICE
mdefine_line|#define IPL_DEVICE        (*(unsigned long *)  (0x10400))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      (*(unsigned long *)  (0x10408))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       (*(unsigned long *)  (0x10410))
macro_line|#endif /* __s390x__ */
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE      ((char *)            (0x10480))
multiline_comment|/*&n; * Machine features detected in head.S&n; */
r_extern
r_int
r_int
id|machine_flags
suffix:semicolon
DECL|macro|MACHINE_IS_VM
mdefine_line|#define MACHINE_IS_VM&t;&t;(machine_flags &amp; 1)
DECL|macro|MACHINE_IS_P390
mdefine_line|#define MACHINE_IS_P390&t;&t;(machine_flags &amp; 4)
DECL|macro|MACHINE_HAS_MVPG
mdefine_line|#define MACHINE_HAS_MVPG&t;(machine_flags &amp; 16)
DECL|macro|MACHINE_HAS_DIAG44
mdefine_line|#define MACHINE_HAS_DIAG44&t;(machine_flags &amp; 32)
DECL|macro|MACHINE_NEW_STIDP
mdefine_line|#define MACHINE_NEW_STIDP&t;(machine_flags &amp; 64)
macro_line|#ifndef __s390x__
DECL|macro|MACHINE_HAS_IEEE
mdefine_line|#define MACHINE_HAS_IEEE&t;(machine_flags &amp; 2)
DECL|macro|MACHINE_HAS_CSP
mdefine_line|#define MACHINE_HAS_CSP&t;&t;(machine_flags &amp; 8)
macro_line|#else /* __s390x__ */
DECL|macro|MACHINE_HAS_IEEE
mdefine_line|#define MACHINE_HAS_IEEE&t;(1)
DECL|macro|MACHINE_HAS_CSP
mdefine_line|#define MACHINE_HAS_CSP&t;&t;(1)
macro_line|#endif /* __s390x__ */
DECL|macro|MACHINE_HAS_SCLP
mdefine_line|#define MACHINE_HAS_SCLP&t;(!MACHINE_IS_P390)
multiline_comment|/*&n; * Console mode. Override with conmode=&n; */
r_extern
r_int
r_int
id|console_mode
suffix:semicolon
r_extern
r_int
r_int
id|console_device
suffix:semicolon
r_extern
r_int
r_int
id|console_irq
suffix:semicolon
DECL|macro|CONSOLE_IS_UNDEFINED
mdefine_line|#define CONSOLE_IS_UNDEFINED&t;(console_mode == 0)
DECL|macro|CONSOLE_IS_SCLP
mdefine_line|#define CONSOLE_IS_SCLP&t;&t;(console_mode == 1)
DECL|macro|CONSOLE_IS_3215
mdefine_line|#define CONSOLE_IS_3215&t;&t;(console_mode == 2)
DECL|macro|CONSOLE_IS_3270
mdefine_line|#define CONSOLE_IS_3270&t;&t;(console_mode == 3)
DECL|macro|SET_CONSOLE_SCLP
mdefine_line|#define SET_CONSOLE_SCLP&t;do { console_mode = 1; } while (0)
DECL|macro|SET_CONSOLE_3215
mdefine_line|#define SET_CONSOLE_3215&t;do { console_mode = 2; } while (0)
DECL|macro|SET_CONSOLE_3270
mdefine_line|#define SET_CONSOLE_3270&t;do { console_mode = 3; } while (0)
macro_line|#else 
macro_line|#ifndef __s390x__
DECL|macro|IPL_DEVICE
mdefine_line|#define IPL_DEVICE        0x10404
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      0x1040C
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       0x10414
macro_line|#else /* __s390x__ */
DECL|macro|IPL_DEVICE
mdefine_line|#define IPL_DEVICE        0x10400
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      0x10408
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       0x10410
macro_line|#endif /* __s390x__ */
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE      0x10480
macro_line|#endif
macro_line|#endif
eof
