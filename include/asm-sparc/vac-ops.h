multiline_comment|/* $Id: vac-ops.h,v 1.13 1998/01/30 10:59:59 jj Exp $ */
macro_line|#ifndef _SPARC_VAC_OPS_H
DECL|macro|_SPARC_VAC_OPS_H
mdefine_line|#define _SPARC_VAC_OPS_H
multiline_comment|/* vac-ops.h: Inline assembly routines to do operations on the Sparc&n; *            VAC (virtual address cache) for the sun4c.&n; *&n; * Copyright (C) 1994, David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sysen.h&gt;
macro_line|#include &lt;asm/contregs.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
multiline_comment|/* The SUN4C models have a virtually addressed write-through&n; * cache.&n; *&n; * The cache tags are directly accessible through an ASI and&n; * each have the form:&n; *&n; * ------------------------------------------------------------&n; * | MBZ | CONTEXT | WRITE | PRIV | VALID | MBZ | TagID | MBZ |&n; * ------------------------------------------------------------&n; *  31 25  24   22     21     20     19    18 16  15   2  1  0&n; *&n; * MBZ: These bits are either unused and/or reserved and should&n; *      be written as zeroes.&n; *&n; * CONTEXT: Records the context to which this cache line belongs.&n; *&n; * WRITE: A copy of the writable bit from the mmu pte access bits.&n; *&n; * PRIV: A copy of the privileged bit from the pte access bits.&n; *&n; * VALID: If set, this line is valid, else invalid.&n; *&n; * TagID: Fourteen bits of tag ID.&n; *&n; * Every virtual address is seen by the cache like this:&n; *&n; * ----------------------------------------&n; * |  RESV  | TagID | LINE | BYTE-in-LINE |&n; * ----------------------------------------&n; *  31    30 29   16 15   4 3            0&n; *&n; * RESV: Unused/reserved.&n; *&n; * TagID: Used to match the Tag-ID in that vac tags.&n; *&n; * LINE: Which line within the cache&n; *&n; * BYTE-in-LINE: Which byte within the cache line.&n; */
multiline_comment|/* Sun4c VAC Tags */
DECL|macro|S4CVACTAG_CID
mdefine_line|#define S4CVACTAG_CID      0x01c00000
DECL|macro|S4CVACTAG_W
mdefine_line|#define S4CVACTAG_W        0x00200000
DECL|macro|S4CVACTAG_P
mdefine_line|#define S4CVACTAG_P        0x00100000
DECL|macro|S4CVACTAG_V
mdefine_line|#define S4CVACTAG_V        0x00080000
DECL|macro|S4CVACTAG_TID
mdefine_line|#define S4CVACTAG_TID      0x0000fffc
multiline_comment|/* Sun4c VAC Virtual Address */
multiline_comment|/* These aren&squot;t used, why bother? (Anton) */
macro_line|#if 0
mdefine_line|#define S4CVACVA_TID       0x3fff0000
mdefine_line|#define S4CVACVA_LINE      0x0000fff0
mdefine_line|#define S4CVACVA_BIL       0x0000000f
macro_line|#endif
multiline_comment|/* The indexing of cache lines creates a problem.  Because the line&n; * field of a virtual address extends past the page offset within&n; * the virtual address it is possible to have what are called&n; * &squot;bad aliases&squot; which will create inconsistencies.  So we must make&n; * sure that within a context that if a physical page is mapped&n; * more than once, that &squot;extra&squot; line bits are the same.  If this is&n; * not the case, and thus is a &squot;bad alias&squot; we must turn off the&n; * cacheable bit in the pte&squot;s of all such pages.&n; */
macro_line|#ifdef CONFIG_SUN4
DECL|macro|S4CVAC_BADBITS
mdefine_line|#define S4CVAC_BADBITS     0x0001e000
macro_line|#else
DECL|macro|S4CVAC_BADBITS
mdefine_line|#define S4CVAC_BADBITS    0x0000f000
macro_line|#endif
multiline_comment|/* The following is true if vaddr1 and vaddr2 would cause&n; * a &squot;bad alias&squot;.&n; */
DECL|macro|S4CVAC_BADALIAS
mdefine_line|#define S4CVAC_BADALIAS(vaddr1, vaddr2) &bslash;&n;        ((((unsigned long) (vaddr1)) ^ ((unsigned long) (vaddr2))) &amp; &bslash;&n;&t; (S4CVAC_BADBITS))
multiline_comment|/* The following structure describes the characteristics of a sun4c&n; * VAC as probed from the prom during boot time.&n; */
DECL|struct|sun4c_vac_props
r_struct
id|sun4c_vac_props
(brace
DECL|member|num_bytes
r_int
r_int
id|num_bytes
suffix:semicolon
multiline_comment|/* Size of the cache */
DECL|member|num_lines
r_int
r_int
id|num_lines
suffix:semicolon
multiline_comment|/* Number of cache lines */
DECL|member|do_hwflushes
r_int
r_int
id|do_hwflushes
suffix:semicolon
multiline_comment|/* Hardware flushing available? */
DECL|enumerator|NONE
DECL|enumerator|WRITE_THROUGH
r_enum
(brace
id|NONE
comma
id|WRITE_THROUGH
comma
DECL|enumerator|WRITE_BACK
DECL|member|type
id|WRITE_BACK
)brace
id|type
suffix:semicolon
multiline_comment|/* What type of VAC? */
DECL|member|linesize
r_int
r_int
id|linesize
suffix:semicolon
multiline_comment|/* Size of each line in bytes */
DECL|member|log2lsize
r_int
r_int
id|log2lsize
suffix:semicolon
multiline_comment|/* log2(linesize) */
DECL|member|on
r_int
r_int
id|on
suffix:semicolon
multiline_comment|/* VAC is enabled */
)brace
suffix:semicolon
r_extern
r_struct
id|sun4c_vac_props
id|sun4c_vacinfo
suffix:semicolon
multiline_comment|/* sun4c_enable_vac() enables the sun4c virtual address cache. */
DECL|function|sun4c_enable_vac
r_extern
id|__inline__
r_void
id|sun4c_enable_vac
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba [%0] %1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;or    %%g1, %2, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;stba  %%g1, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
id|AC_SENABLE
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
comma
l_string|&quot;i&quot;
(paren
id|SENABLE_CACHE
)paren
suffix:colon
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|sun4c_vacinfo.on
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* sun4c_disable_vac() disables the virtual address cache. */
DECL|function|sun4c_disable_vac
r_extern
id|__inline__
r_void
id|sun4c_disable_vac
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba [%0] %1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;andn  %%g1, %2, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;stba  %%g1, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
id|AC_SENABLE
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
comma
l_string|&quot;i&quot;
(paren
id|SENABLE_CACHE
)paren
suffix:colon
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|sun4c_vacinfo.on
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_VAC_OPS_H) */
eof
