multiline_comment|/*&n; *&t;include/asm-mips/dec/prom.h&n; *&n; *&t;DECstation PROM interface.&n; *&n; *&t;Copyright (C) 2002  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Based on arch/mips/dec/prom/prom.h by the Anonymous.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_PROM_H
DECL|macro|__ASM_MIPS_DEC_PROM_H
mdefine_line|#define __ASM_MIPS_DEC_PROM_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * PMAX/3MAX PROM entry points for DS2100/3100&squot;s and DS5000/2xx&squot;s.&n; * Many of these will work for MIPSen as well!&n; */
DECL|macro|VEC_RESET
mdefine_line|#define VEC_RESET&t;&t;(u64 *)KSEG1ADDR(0x1fc00000)
multiline_comment|/* Prom base address */
DECL|macro|PMAX_PROM_ENTRY
mdefine_line|#define PMAX_PROM_ENTRY(x)&t;(VEC_RESET + (x))&t;/* Prom jump table */
DECL|macro|PMAX_PROM_HALT
mdefine_line|#define PMAX_PROM_HALT&t;&t;PMAX_PROM_ENTRY(2)&t;/* valid on MIPSen */
DECL|macro|PMAX_PROM_AUTOBOOT
mdefine_line|#define PMAX_PROM_AUTOBOOT&t;PMAX_PROM_ENTRY(5)&t;/* valid on MIPSen */
DECL|macro|PMAX_PROM_OPEN
mdefine_line|#define PMAX_PROM_OPEN&t;&t;PMAX_PROM_ENTRY(6)
DECL|macro|PMAX_PROM_READ
mdefine_line|#define PMAX_PROM_READ&t;&t;PMAX_PROM_ENTRY(7)
DECL|macro|PMAX_PROM_CLOSE
mdefine_line|#define PMAX_PROM_CLOSE&t;&t;PMAX_PROM_ENTRY(10)
DECL|macro|PMAX_PROM_LSEEK
mdefine_line|#define PMAX_PROM_LSEEK&t;&t;PMAX_PROM_ENTRY(11)
DECL|macro|PMAX_PROM_GETCHAR
mdefine_line|#define PMAX_PROM_GETCHAR&t;PMAX_PROM_ENTRY(12)
DECL|macro|PMAX_PROM_PUTCHAR
mdefine_line|#define PMAX_PROM_PUTCHAR&t;PMAX_PROM_ENTRY(13)&t;/* 12 on MIPSen */
DECL|macro|PMAX_PROM_GETS
mdefine_line|#define PMAX_PROM_GETS&t;&t;PMAX_PROM_ENTRY(15)
DECL|macro|PMAX_PROM_PRINTF
mdefine_line|#define PMAX_PROM_PRINTF&t;PMAX_PROM_ENTRY(17)
DECL|macro|PMAX_PROM_GETENV
mdefine_line|#define PMAX_PROM_GETENV&t;PMAX_PROM_ENTRY(33)&t;/* valid on MIPSen */
multiline_comment|/*&n; * Magic number indicating REX PROM available on DECstation.  Found in&n; * register a2 on transfer of control to program from PROM.&n; */
DECL|macro|REX_PROM_MAGIC
mdefine_line|#define REX_PROM_MAGIC&t;&t;0x30464354
macro_line|#ifdef CONFIG_MIPS64
DECL|macro|prom_is_rex
mdefine_line|#define prom_is_rex(magic)&t;1&t;/* KN04 and KN05 are REX PROMs.  */
macro_line|#else /* !CONFIG_MIPS64 */
DECL|macro|prom_is_rex
mdefine_line|#define prom_is_rex(magic)&t;((magic) == REX_PROM_MAGIC)
macro_line|#endif /* !CONFIG_MIPS64 */
multiline_comment|/*&n; * 3MIN/MAXINE PROM entry points for DS5000/1xx&squot;s, DS5000/xx&squot;s and&n; * DS5000/2x0.&n; */
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
multiline_comment|/*&n; * Used by rex_getbitmap().&n; */
r_typedef
r_struct
(brace
DECL|member|pagesize
r_int
id|pagesize
suffix:semicolon
DECL|member|bitmap
r_int
r_char
id|bitmap
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|memmap
)brace
id|memmap
suffix:semicolon
multiline_comment|/*&n; * Function pointers as read from a PROM&squot;s callback vector.&n; */
r_extern
r_int
(paren
op_star
id|__rex_bootinit
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__rex_bootread
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__rex_getbitmap
)paren
(paren
id|memmap
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
(paren
op_star
id|__rex_slot_address
)paren
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
(paren
op_star
id|__rex_gettcinfo
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__rex_getsysid
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|__rex_clear_cache
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__prom_getchar
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
(paren
op_star
id|__prom_getenv
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__prom_printf
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__pmax_open
)paren
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__pmax_lseek
)paren
(paren
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__pmax_read
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__pmax_close
)paren
(paren
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n; * On MIPS64 we have to call PROM functions via a helper&n; * dispatcher to accomodate ABI incompatibilities.&n; */
DECL|macro|__DEC_PROM_O32
mdefine_line|#define __DEC_PROM_O32 __attribute__((alias(&quot;call_o32&quot;)))
r_int
id|_rex_bootinit
c_func
(paren
r_int
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_int
id|_rex_bootread
c_func
(paren
r_int
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_int
id|_rex_getbitmap
c_func
(paren
r_int
(paren
op_star
)paren
(paren
id|memmap
op_star
)paren
comma
id|memmap
op_star
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_int
r_int
op_star
id|_rex_slot_address
c_func
(paren
r_int
r_int
op_star
(paren
op_star
)paren
(paren
r_int
)paren
comma
r_int
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_void
op_star
id|_rex_gettcinfo
c_func
(paren
r_void
op_star
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_int
id|_rex_getsysid
c_func
(paren
r_int
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_void
id|_rex_clear_cache
c_func
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_int
id|_prom_getchar
c_func
(paren
r_int
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_char
op_star
id|_prom_getenv
c_func
(paren
r_char
op_star
(paren
op_star
)paren
(paren
r_char
op_star
)paren
comma
r_char
op_star
)paren
id|__DEC_PROM_O32
suffix:semicolon
r_int
id|_prom_printf
c_func
(paren
r_int
(paren
op_star
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
comma
r_char
op_star
comma
dot
dot
dot
)paren
id|__DEC_PROM_O32
suffix:semicolon
DECL|macro|rex_bootinit
mdefine_line|#define rex_bootinit()&t;&t;_rex_bootinit(__rex_bootinit)
DECL|macro|rex_bootread
mdefine_line|#define rex_bootread()&t;&t;_rex_bootread(__rex_bootread)
DECL|macro|rex_getbitmap
mdefine_line|#define rex_getbitmap(x)&t;_rex_getbitmap(__rex_getbitmap, x)
DECL|macro|rex_slot_address
mdefine_line|#define rex_slot_address(x)&t;_rex_slot_address(__rex_slot_address, x)
DECL|macro|rex_gettcinfo
mdefine_line|#define rex_gettcinfo()&t;&t;_rex_gettcinfo(__rex_gettcinfo)
DECL|macro|rex_getsysid
mdefine_line|#define rex_getsysid()&t;&t;_rex_getsysid(__rex_getsysid)
DECL|macro|rex_clear_cache
mdefine_line|#define rex_clear_cache()&t;_rex_clear_cache(__rex_clear_cache)
DECL|macro|prom_getchar
mdefine_line|#define prom_getchar()&t;&t;_prom_getchar(__prom_getchar)
DECL|macro|prom_getenv
mdefine_line|#define prom_getenv(x)&t;&t;_prom_getenv(__prom_getenv, x)
DECL|macro|prom_printf
mdefine_line|#define prom_printf(x...)&t;_prom_printf(__prom_printf, x)
macro_line|#else /* !CONFIG_MIPS64 */
multiline_comment|/*&n; * On plain MIPS we just call PROM functions directly.&n; */
DECL|macro|rex_bootinit
mdefine_line|#define rex_bootinit&t;&t;__rex_bootinit
DECL|macro|rex_bootread
mdefine_line|#define rex_bootread&t;&t;__rex_bootread
DECL|macro|rex_getbitmap
mdefine_line|#define rex_getbitmap&t;&t;__rex_getbitmap
DECL|macro|rex_slot_address
mdefine_line|#define rex_slot_address&t;__rex_slot_address
DECL|macro|rex_gettcinfo
mdefine_line|#define rex_gettcinfo&t;&t;__rex_gettcinfo
DECL|macro|rex_getsysid
mdefine_line|#define rex_getsysid&t;&t;__rex_getsysid
DECL|macro|rex_clear_cache
mdefine_line|#define rex_clear_cache&t;&t;__rex_clear_cache
DECL|macro|prom_getchar
mdefine_line|#define prom_getchar&t;&t;__prom_getchar
DECL|macro|prom_getenv
mdefine_line|#define prom_getenv&t;&t;__prom_getenv
DECL|macro|prom_printf
mdefine_line|#define prom_printf&t;&t;__prom_printf
DECL|macro|pmax_open
mdefine_line|#define pmax_open&t;&t;__pmax_open
DECL|macro|pmax_lseek
mdefine_line|#define pmax_lseek&t;&t;__pmax_lseek
DECL|macro|pmax_read
mdefine_line|#define pmax_read&t;&t;__pmax_read
DECL|macro|pmax_close
mdefine_line|#define pmax_close&t;&t;__pmax_close
macro_line|#endif /* !CONFIG_MIPS64 */
r_extern
r_void
id|prom_meminit
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|prom_identify_arch
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|prom_init_cmdline
c_func
(paren
id|s32
comma
id|s32
op_star
comma
id|u32
)paren
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_DEC_PROM_H */
eof
