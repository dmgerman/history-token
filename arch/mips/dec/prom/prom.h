multiline_comment|/*  &n; * Miscellaneous definitions used to call the routines contained in the boot&n; * PROMs on various models of DECSTATION&squot;s.&n; * the rights to redistribute these changes.&n; */
macro_line|#ifndef __ASM_DEC_PROM_H 
DECL|macro|__ASM_DEC_PROM_H
mdefine_line|#define __ASM_DEC_PROM_H 
multiline_comment|/*&n; * PMAX/3MAX PROM entry points for DS2100/3100&squot;s and DS5000/2xx&squot;s.  Many of&n; * these will work for MIPSen as well!&n; */
DECL|macro|VEC_RESET
mdefine_line|#define VEC_RESET&t;&t;0xBFC00000&t;&t;/* Prom base address */
DECL|macro|PMAX_PROM_ENTRY
mdefine_line|#define&t;PMAX_PROM_ENTRY(x)&t;(VEC_RESET+((x)*8))&t;/* Prom jump table */
DECL|macro|PMAX_PROM_HALT
mdefine_line|#define&t;PMAX_PROM_HALT&t;&t;PMAX_PROM_ENTRY(2)&t;/* valid on MIPSen */
DECL|macro|PMAX_PROM_AUTOBOOT
mdefine_line|#define&t;PMAX_PROM_AUTOBOOT&t;PMAX_PROM_ENTRY(5)&t;/* valid on MIPSen */
DECL|macro|PMAX_PROM_OPEN
mdefine_line|#define&t;PMAX_PROM_OPEN&t;&t;PMAX_PROM_ENTRY(6)
DECL|macro|PMAX_PROM_READ
mdefine_line|#define&t;PMAX_PROM_READ&t;&t;PMAX_PROM_ENTRY(7)
DECL|macro|PMAX_PROM_CLOSE
mdefine_line|#define&t;PMAX_PROM_CLOSE&t;&t;PMAX_PROM_ENTRY(10)
DECL|macro|PMAX_PROM_LSEEK
mdefine_line|#define&t;PMAX_PROM_LSEEK&t;&t;PMAX_PROM_ENTRY(11)
DECL|macro|PMAX_PROM_GETCHAR
mdefine_line|#define PMAX_PROM_GETCHAR       PMAX_PROM_ENTRY(12)
DECL|macro|PMAX_PROM_PUTCHAR
mdefine_line|#define&t;PMAX_PROM_PUTCHAR&t;PMAX_PROM_ENTRY(13)&t;/* 12 on MIPSen */
DECL|macro|PMAX_PROM_GETS
mdefine_line|#define&t;PMAX_PROM_GETS&t;&t;PMAX_PROM_ENTRY(15)
DECL|macro|PMAX_PROM_PRINTF
mdefine_line|#define&t;PMAX_PROM_PRINTF&t;PMAX_PROM_ENTRY(17)
DECL|macro|PMAX_PROM_GETENV
mdefine_line|#define&t;PMAX_PROM_GETENV&t;PMAX_PROM_ENTRY(33)&t;/* valid on MIPSen */
multiline_comment|/*&n; * Magic number indicating REX PROM available on DECSTATION.  Found in&n; * register a2 on transfer of control to program from PROM.&n; */
DECL|macro|REX_PROM_MAGIC
mdefine_line|#define&t;REX_PROM_MAGIC&t;&t;0x30464354
multiline_comment|/*&n; * 3MIN/MAXINE PROM entry points for DS5000/1xx&squot;s, DS5000/xx&squot;s, and&n; * DS5000/2x0.&n; */
DECL|macro|REX_PROM_GETBITMAP
mdefine_line|#define REX_PROM_GETBITMAP&t;0x84/4&t;/* get mem bitmap */
DECL|macro|REX_PROM_GETCHAR
mdefine_line|#define REX_PROM_GETCHAR&t;0x24/4&t;/* getch() */
DECL|macro|REX_PROM_GETENV
mdefine_line|#define REX_PROM_GETENV&t;&t;0x64/4&t;/* get env. variable */
DECL|macro|REX_PROM_GETSYSID
mdefine_line|#define REX_PROM_GETSYSID&t;0x80/4&t;/* get system id */
DECL|macro|REX_PROM_GETTCINFO
mdefine_line|#define REX_PROM_GETTCINFO&t;0xa4/4
DECL|macro|REX_PROM_PRINTF
mdefine_line|#define REX_PROM_PRINTF&t;&t;0x30/4&t;/* printf() */
DECL|macro|REX_PROM_SLOTADDR
mdefine_line|#define REX_PROM_SLOTADDR&t;0x6c/4&t;/* slotaddr */
DECL|macro|REX_PROM_BOOTINIT
mdefine_line|#define REX_PROM_BOOTINIT&t;0x54/4&t;/* open() */
DECL|macro|REX_PROM_BOOTREAD
mdefine_line|#define REX_PROM_BOOTREAD&t;0x58/4&t;/* read() */
DECL|macro|REX_PROM_CLEARCACHE
mdefine_line|#define REX_PROM_CLEARCACHE&t;0x7c/4
macro_line|#endif /* __ASM_DEC_PROM_H */
eof
