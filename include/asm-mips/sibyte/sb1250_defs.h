multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  Global constants and macros&t;&t;File: sb1250_defs.h&t;&n;    *  &n;    *  This file contains macros and definitions used by the other&n;    *  include files.&n;    *&n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_DEFS_H
DECL|macro|_SB1250_DEFS_H
mdefine_line|#define _SB1250_DEFS_H
multiline_comment|/*&n; * These headers require ANSI C89 string concatenation, and GCC or other&n; * &squot;long long&squot; (64-bit integer) support.&n; */
macro_line|#if !defined(__STDC__) &amp;&amp; !defined(_MSC_VER)
macro_line|#error SiByte headers require ANSI C89 support
macro_line|#endif
multiline_comment|/*  *********************************************************************&n;    *  Macros for feature tests, used to enable include file features&n;    *  for chip features only present in certain chip revisions.&n;    *&n;    *  SIBYTE_HDR_FEATURES may be defined to be the mask value chip/revision&n;    *  which is to be exposed by the headers.  If undefined, it defaults to&n;    *  &quot;all features.&quot;&n;    *&n;    *  Use like:&n;    *&n;    *    #define SIBYTE_HDR_FEATURES&t;SIBYTE_HDR_FMASK_112x_PASS1&n;    *&n;    *&t;&t;Generate defines only for that revision of chip.&n;    *&n;    *    #if SIBYTE_HDR_FEATURE(chip,pass)&n;    *&n;    *&t;&t;True if header features for that revision or later of&n;    *&t;        that particular chip type are enabled in SIBYTE_HDR_FEATURES.&n;    *&t;        (Use this to bracket #defines for features present in a given&n;    *&t;&t;revision and later.)&n;    *&n;    *&t;&t;Note that there is no implied ordering between chip types.&n;    *&n;    *&t;&t;Note also that &squot;chip&squot; and &squot;pass&squot; must textually exactly&n;    *&t;&t;match the defines below.  So, for example,&n;    *&t;&t;SIBYTE_HDR_FEATURE(112x, PASS1) is OK, but&n;    *&t;&t;SIBYTE_HDR_FEATURE(1120, pass1) is not (for two reasons).&n;    *&n;    *    #if SIBYTE_HDR_FEATURE_UP_TO(chip,pass)&n;    *&n;    *&t;&t;Same as SIBYTE_HDR_FEATURE, but true for the named revision&n;    *&t;&t;and earlier revisions of the named chip type.&n;    *&n;    *    #if SIBYTE_HDR_FEATURE_EXACT(chip,pass)&n;    *&n;    *&t;&t;Same as SIBYTE_HDR_FEATURE, but only true for the named&n;    *&t;&t;revision of the named chip type.  (Note that this CANNOT&n;    *&t;&t;be used to verify that you&squot;re compiling only for that&n;    *&t;&t;particular chip/revision.  It will be true any time this&n;    *&t;&t;chip/revision is included in SIBYTE_HDR_FEATURES.)&n;    *&n;    *    #if SIBYTE_HDR_FEATURE_CHIP(chip)&n;    *&n;    *&t;&t;True if header features for (any revision of) that chip type&n;    *&t;&t;are enabled in SIBYTE_HDR_FEATURES.  (Use this to bracket&n;    *&t;&t;#defines for features specific to a given chip type.)&n;    *&n;    *  Mask values currently include room for additional revisions of each&n;    *  chip type, but can be renumbered at will.  Note that they MUST fit&n;    *  into 31 bits and may not include C type constructs, for safe use in&n;    *  CPP conditionals.  Bit positions within chip types DO indicate&n;    *  ordering, so be careful when adding support for new minor revs.&n;    ********************************************************************* */
DECL|macro|SIBYTE_HDR_FMASK_1250_ALL
mdefine_line|#define&t;SIBYTE_HDR_FMASK_1250_ALL&t;&t;0x00000ff
DECL|macro|SIBYTE_HDR_FMASK_1250_PASS1
mdefine_line|#define&t;SIBYTE_HDR_FMASK_1250_PASS1&t;&t;0x0000001
DECL|macro|SIBYTE_HDR_FMASK_1250_PASS2
mdefine_line|#define&t;SIBYTE_HDR_FMASK_1250_PASS2&t;&t;0x0000002
DECL|macro|SIBYTE_HDR_FMASK_112x_ALL
mdefine_line|#define&t;SIBYTE_HDR_FMASK_112x_ALL&t;&t;0x0000f00
DECL|macro|SIBYTE_HDR_FMASK_112x_PASS1
mdefine_line|#define&t;SIBYTE_HDR_FMASK_112x_PASS1&t;&t;0x0000100
DECL|macro|SIBYTE_HDR_FMASK_112x_PASS3
mdefine_line|#define SIBYTE_HDR_FMASK_112x_PASS3&t;&t;0x0000200
multiline_comment|/* Bit mask for chip/revision.  (use _ALL for all revisions of a chip).  */
DECL|macro|SIBYTE_HDR_FMASK
mdefine_line|#define&t;SIBYTE_HDR_FMASK(chip, pass)&t;&t;&t;&t;&t;&bslash;&n;    (SIBYTE_HDR_FMASK_ ## chip ## _ ## pass)
DECL|macro|SIBYTE_HDR_FMASK_ALLREVS
mdefine_line|#define&t;SIBYTE_HDR_FMASK_ALLREVS(chip)&t;&t;&t;&t;&t;&bslash;&n;    (SIBYTE_HDR_FMASK_ ## chip ## _ALL)
DECL|macro|SIBYTE_HDR_FMASK_ALL
mdefine_line|#define&t;SIBYTE_HDR_FMASK_ALL&t;&t;&t;&t;&t;&t;&bslash;&n;    (SIBYTE_HDR_FMASK_1250_ALL | SIBYTE_HDR_FMASK_112x_ALL)
macro_line|#ifndef SIBYTE_HDR_FEATURES
DECL|macro|SIBYTE_HDR_FEATURES
mdefine_line|#define&t;SIBYTE_HDR_FEATURES&t;&t;&t;SIBYTE_HDR_FMASK_ALL
macro_line|#endif
multiline_comment|/* Bit mask for revisions of chip exclusively before the named revision.  */
DECL|macro|SIBYTE_HDR_FMASK_BEFORE
mdefine_line|#define&t;SIBYTE_HDR_FMASK_BEFORE(chip, pass)&t;&t;&t;&t;&bslash;&n;    ((SIBYTE_HDR_FMASK(chip, pass) - 1) &amp; SIBYTE_HDR_FMASK_ALLREVS(chip))
multiline_comment|/* Bit mask for revisions of chip exclusively after the named revision.  */
DECL|macro|SIBYTE_HDR_FMASK_AFTER
mdefine_line|#define&t;SIBYTE_HDR_FMASK_AFTER(chip, pass)&t;&t;&t;&t;&bslash;&n;    (~(SIBYTE_HDR_FMASK(chip, pass)&t;&t;&t;&t;&t;&bslash;&n;     | (SIBYTE_HDR_FMASK(chip, pass) - 1)) &amp; SIBYTE_HDR_FMASK_ALLREVS(chip))
multiline_comment|/* True if header features enabled for (any revision of) that chip type.  */
DECL|macro|SIBYTE_HDR_FEATURE_CHIP
mdefine_line|#define SIBYTE_HDR_FEATURE_CHIP(chip)&t;&t;&t;&t;&t;&bslash;&n;    (!! (SIBYTE_HDR_FMASK_ALLREVS(chip) &amp; SIBYTE_HDR_FEATURES))
multiline_comment|/* True if header features enabled for that rev or later, inclusive.  */
DECL|macro|SIBYTE_HDR_FEATURE
mdefine_line|#define SIBYTE_HDR_FEATURE(chip, pass)&t;&t;&t;&t;&t;&bslash;&n;    (!! ((SIBYTE_HDR_FMASK(chip, pass)&t;&t;&t;&t;&t;&bslash;&n;&t;  | SIBYTE_HDR_FMASK_AFTER(chip, pass)) &amp; SIBYTE_HDR_FEATURES))
multiline_comment|/* True if header features enabled for exactly that rev.  */
DECL|macro|SIBYTE_HDR_FEATURE_EXACT
mdefine_line|#define SIBYTE_HDR_FEATURE_EXACT(chip, pass)&t;&t;&t;&t;&bslash;&n;    (!! (SIBYTE_HDR_FMASK(chip, pass) &amp; SIBYTE_HDR_FEATURES))
multiline_comment|/* True if header features enabled for that rev or before, inclusive.  */
DECL|macro|SIBYTE_HDR_FEATURE_UP_TO
mdefine_line|#define SIBYTE_HDR_FEATURE_UP_TO(chip, pass)&t;&t;&t;&t;&bslash;&n;    (!! ((SIBYTE_HDR_FMASK(chip, pass)&t;&t;&t;&t;&t;&bslash;&n;&t; | SIBYTE_HDR_FMASK_BEFORE(chip, pass)) &amp; SIBYTE_HDR_FEATURES))
multiline_comment|/*  *********************************************************************&n;    *  Naming schemes for constants in these files:&n;    *  &n;    *  M_xxx           MASK constant (identifies bits in a register). &n;    *                  For multi-bit fields, all bits in the field will&n;    *                  be set.&n;    *&n;    *  K_xxx           &quot;Code&quot; constant (value for data in a multi-bit&n;    *                  field).  The value is right justified.&n;    *&n;    *  V_xxx           &quot;Value&quot; constant.  This is the same as the &n;    *                  corresponding &quot;K_xxx&quot; constant, except it is&n;    *                  shifted to the correct position in the register.&n;    *&n;    *  S_xxx           SHIFT constant.  This is the number of bits that&n;    *                  a field value (code) needs to be shifted &n;    *                  (towards the left) to put the value in the right&n;    *                  position for the register.&n;    *&n;    *  A_xxx           ADDRESS constant.  This will be a physical &n;    *                  address.  Use the PHYS_TO_K1 macro to generate&n;    *                  a K1SEG address.&n;    *&n;    *  R_xxx           RELATIVE offset constant.  This is an offset from&n;    *                  an A_xxx constant (usually the first register in&n;    *                  a group).&n;    *  &n;    *  G_xxx(X)        GET value.  This macro obtains a multi-bit field&n;    *                  from a register, masks it, and shifts it to&n;    *                  the bottom of the register (retrieving a K_xxx&n;    *                  value, for example).&n;    *&n;    *  V_xxx(X)        VALUE.  This macro computes the value of a&n;    *                  K_xxx constant shifted to the correct position&n;    *                  in the register.&n;    ********************************************************************* */
multiline_comment|/*&n; * Cast to 64-bit number.  Presumably the syntax is different in &n; * assembly language.&n; *&n; * Note: you&squot;ll need to define uint32_t and uint64_t in your headers.&n; */
macro_line|#if !defined(__ASSEMBLER__)
DECL|macro|_SB_MAKE64
mdefine_line|#define _SB_MAKE64(x) ((uint64_t)(x))
DECL|macro|_SB_MAKE32
mdefine_line|#define _SB_MAKE32(x) ((uint32_t)(x))
macro_line|#else
DECL|macro|_SB_MAKE64
mdefine_line|#define _SB_MAKE64(x) (x)
DECL|macro|_SB_MAKE32
mdefine_line|#define _SB_MAKE32(x) (x)
macro_line|#endif
multiline_comment|/*&n; * Make a mask for 1 bit at position &squot;n&squot;&n; */
DECL|macro|_SB_MAKEMASK1
mdefine_line|#define _SB_MAKEMASK1(n) (_SB_MAKE64(1) &lt;&lt; _SB_MAKE64(n))
DECL|macro|_SB_MAKEMASK1_32
mdefine_line|#define _SB_MAKEMASK1_32(n) (_SB_MAKE32(1) &lt;&lt; _SB_MAKE32(n))
multiline_comment|/*&n; * Make a mask for &squot;v&squot; bits at position &squot;n&squot;&n; */
DECL|macro|_SB_MAKEMASK
mdefine_line|#define _SB_MAKEMASK(v,n) (_SB_MAKE64((_SB_MAKE64(1)&lt;&lt;(v))-1) &lt;&lt; _SB_MAKE64(n))
DECL|macro|_SB_MAKEMASK_32
mdefine_line|#define _SB_MAKEMASK_32(v,n) (_SB_MAKE32((_SB_MAKE32(1)&lt;&lt;(v))-1) &lt;&lt; _SB_MAKE32(n))
multiline_comment|/*&n; * Make a value at &squot;v&squot; at bit position &squot;n&squot;&n; */
DECL|macro|_SB_MAKEVALUE
mdefine_line|#define _SB_MAKEVALUE(v,n) (_SB_MAKE64(v) &lt;&lt; _SB_MAKE64(n))
DECL|macro|_SB_MAKEVALUE_32
mdefine_line|#define _SB_MAKEVALUE_32(v,n) (_SB_MAKE32(v) &lt;&lt; _SB_MAKE32(n))
DECL|macro|_SB_GETVALUE
mdefine_line|#define _SB_GETVALUE(v,n,m) ((_SB_MAKE64(v) &amp; _SB_MAKE64(m)) &gt;&gt; _SB_MAKE64(n))
DECL|macro|_SB_GETVALUE_32
mdefine_line|#define _SB_GETVALUE_32(v,n,m) ((_SB_MAKE32(v) &amp; _SB_MAKE32(m)) &gt;&gt; _SB_MAKE32(n))
multiline_comment|/*&n; * Macros to read/write on-chip registers&n; * XXX should we do the PHYS_TO_K1 here?&n; */
macro_line|#if !defined(__ASSEMBLER__)
DECL|macro|SBWRITECSR
mdefine_line|#define SBWRITECSR(csr,val) *((volatile uint64_t *) PHYS_TO_K1(csr)) = (val)
DECL|macro|SBREADCSR
mdefine_line|#define SBREADCSR(csr) (*((volatile uint64_t *) PHYS_TO_K1(csr)))
macro_line|#endif /* __ASSEMBLER__ */
macro_line|#endif
eof
