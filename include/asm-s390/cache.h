multiline_comment|/*&n; *  include/asm-s390/cache.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *&n; *  Derived from &quot;include/asm-i386/cache.h&quot;&n; *    Copyright (C) 1992, Linus Torvalds&n; */
macro_line|#ifndef __ARCH_S390_CACHE_H
DECL|macro|__ARCH_S390_CACHE_H
mdefine_line|#define __ARCH_S390_CACHE_H
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES     256
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT     8
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX 8&t;/* largest L1 which this arch supports */
DECL|macro|ARCH_KMALLOC_MINALIGN
mdefine_line|#define ARCH_KMALLOC_MINALIGN&t;8
macro_line|#endif
eof
