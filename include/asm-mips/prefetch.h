multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_PREFETCH_H
DECL|macro|__ASM_PREFETCH_H
mdefine_line|#define __ASM_PREFETCH_H
multiline_comment|/*&n; * R5000 and RM5200 implements pref and prefx instructions but they&squot;re nops, so&n; * rather than wasting time we pretend these processors don&squot;t support&n; * prefetching at all.&n; *&n; * R5432 implements Load, Store, LoadStreamed, StoreStreamed, LoadRetained,&n; * StoreRetained and WriteBackInvalidate but not Pref_PrepareForStore.&n; *&n; * Hell (and the book on my shelf I can&squot;t open ...) know what the R8000 does.&n; *&n; * RM7000 version 1.0 interprets all hints as Pref_Load; version 2.0 implements&n; * Pref_PrepareForStore also.&n; *&n; * RM9000 is MIPS IV but implements prefetching like MIPS32/MIPS64; it&squot;s&n; * Pref_WriteBackInvalidate is a nop and Pref_PrepareForStore is broken in&n; * current versions due to erratum G105.&n; *&n; * VR7701 only implements the Load prefetch.&n; *&n; * Finally MIPS32 and MIPS64 implement all of the following hints.&n; */
DECL|macro|Pref_Load
mdefine_line|#define Pref_Load&t;&t;&t;0
DECL|macro|Pref_Store
mdefine_line|#define Pref_Store&t;&t;&t;1
multiline_comment|/* 2 and 3 are reserved */
DECL|macro|Pref_LoadStreamed
mdefine_line|#define Pref_LoadStreamed&t;&t;4
DECL|macro|Pref_StoreStreamed
mdefine_line|#define Pref_StoreStreamed&t;&t;5
DECL|macro|Pref_LoadRetained
mdefine_line|#define Pref_LoadRetained&t;&t;6
DECL|macro|Pref_StoreRetained
mdefine_line|#define Pref_StoreRetained&t;&t;7
multiline_comment|/* 8 ... 24 are reserved */
DECL|macro|Pref_WriteBackInvalidate
mdefine_line|#define Pref_WriteBackInvalidate&t;25
DECL|macro|Pref_PrepareForStore
mdefine_line|#define Pref_PrepareForStore&t;&t;30
macro_line|#endif /* __ASM_PREFETCH_H */
eof
