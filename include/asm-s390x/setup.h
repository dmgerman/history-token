multiline_comment|/*&n; *  include/asm-s390/setup.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; */
macro_line|#ifndef _ASM_S390_SETUP_H
DECL|macro|_ASM_S390_SETUP_H
mdefine_line|#define _ASM_S390_SETUP_H
DECL|macro|PARMAREA
mdefine_line|#define PARMAREA 0x10400
macro_line|#ifndef __ASSEMBLER__
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV     (*(unsigned long *) (0x10400))
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY (*(unsigned short *) (0x10408))
DECL|macro|MEMORY_SIZE
mdefine_line|#define MEMORY_SIZE       (*(unsigned long *)  (0x1040a))
DECL|macro|MACHINE_FLAGS
mdefine_line|#define MACHINE_FLAGS     (*(unsigned long *)  (0x10412))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      (*(unsigned long *)  (0x1041a))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       (*(unsigned long *)  (0x10422))
DECL|macro|RAMDISK_FLAGS
mdefine_line|#define RAMDISK_FLAGS     (*(unsigned short *) (0x1042a))
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE      ((char *)            (0x10480))
macro_line|#else 
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV     0x10400
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY 0x10408
DECL|macro|MEMORY_SIZE
mdefine_line|#define MEMORY_SIZE       0x1040a
DECL|macro|MACHINE_FLAGS
mdefine_line|#define MACHINE_FLAGS     0x10412
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START      0x1041a
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE       0x10422
DECL|macro|RAMDISK_FLAGS
mdefine_line|#define RAMDISK_FLAGS     0x1042a
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE      0x10480
macro_line|#endif
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 896
multiline_comment|/*&n; * Machine features detected in head.S&n; */
DECL|macro|MACHINE_IS_VM
mdefine_line|#define MACHINE_IS_VM    (MACHINE_FLAGS &amp; 1)
DECL|macro|MACHINE_IS_P390
mdefine_line|#define MACHINE_IS_P390  (MACHINE_FLAGS &amp; 4)
DECL|macro|RAMDISK_ORIGIN
mdefine_line|#define RAMDISK_ORIGIN            0x800000
DECL|macro|RAMDISK_SIZE
mdefine_line|#define RAMDISK_SIZE              0x800000
DECL|macro|RAMDISK_BLKSIZE
mdefine_line|#define RAMDISK_BLKSIZE           0x1000
DECL|macro|RAMDISK_IMAGE_START_MASK
mdefine_line|#define RAMDISK_IMAGE_START_MASK  0x07FF
DECL|macro|RAMDISK_PROMPT_FLAG
mdefine_line|#define RAMDISK_PROMPT_FLAG       0x8000
DECL|macro|RAMDISK_LOAD_FLAG
mdefine_line|#define RAMDISK_LOAD_FLAG         0x4000
macro_line|#endif
eof
