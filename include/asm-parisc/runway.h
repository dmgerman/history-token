macro_line|#ifndef ASM_PARISC_RUNWAY_H
DECL|macro|ASM_PARISC_RUNWAY_H
mdefine_line|#define ASM_PARISC_RUNWAY_H
macro_line|#ifdef __KERNEL__
multiline_comment|/* declared in arch/parisc/kernel/setup.c */
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_runway_root
suffix:semicolon
DECL|macro|RUNWAY_STATUS
mdefine_line|#define RUNWAY_STATUS&t;0x10
DECL|macro|RUNWAY_DEBUG
mdefine_line|#define RUNWAY_DEBUG&t;0x40
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* ASM_PARISC_RUNWAY_H */
eof
