multiline_comment|/* inftrees.c -- generate Huffman trees for efficient decoding&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
macro_line|#include &lt;linux/zutil.h&gt;
macro_line|#include &quot;inftrees.h&quot;
macro_line|#include &quot;infutil.h&quot;
DECL|variable|inflate_copyright
r_static
r_const
r_char
id|inflate_copyright
(braket
)braket
op_assign
l_string|&quot; inflate 1.1.3 Copyright 1995-1998 Mark Adler &quot;
suffix:semicolon
multiline_comment|/*&n;  If you use the zlib library in a product, an acknowledgment is welcome&n;  in the documentation of your product. If for some reason you cannot&n;  include such an acknowledgment, I would appreciate that you keep this&n;  copyright string in the executable of your product.&n; */
r_struct
id|internal_state
suffix:semicolon
multiline_comment|/* simplify the use of the inflate_huft type with some defines */
DECL|macro|exop
mdefine_line|#define exop word.what.Exop
DECL|macro|bits
mdefine_line|#define bits word.what.Bits
id|local
r_int
id|huft_build
id|OF
c_func
(paren
(paren
id|uIntf
op_star
comma
multiline_comment|/* code lengths in bits */
id|uInt
comma
multiline_comment|/* number of codes */
id|uInt
comma
multiline_comment|/* number of &quot;simple&quot; codes */
r_const
id|uIntf
op_star
comma
multiline_comment|/* list of base values for non-simple codes */
r_const
id|uIntf
op_star
comma
multiline_comment|/* list of extra bits for non-simple codes */
id|inflate_huft
op_star
id|FAR
op_star
comma
multiline_comment|/* result: starting table */
id|uIntf
op_star
comma
multiline_comment|/* maximum lookup bits (returns actual) */
id|inflate_huft
op_star
comma
multiline_comment|/* space for trees */
id|uInt
op_star
comma
multiline_comment|/* hufts used in space */
id|uIntf
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* space for values */
multiline_comment|/* Tables for deflate from PKZIP&squot;s appnote.txt. */
DECL|variable|cplens
id|local
r_const
id|uInt
id|cplens
(braket
l_int|31
)braket
op_assign
(brace
multiline_comment|/* Copy lengths for literal codes 257..285 */
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|13
comma
l_int|15
comma
l_int|17
comma
l_int|19
comma
l_int|23
comma
l_int|27
comma
l_int|31
comma
l_int|35
comma
l_int|43
comma
l_int|51
comma
l_int|59
comma
l_int|67
comma
l_int|83
comma
l_int|99
comma
l_int|115
comma
l_int|131
comma
l_int|163
comma
l_int|195
comma
l_int|227
comma
l_int|258
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* see note #13 above about 258 */
DECL|variable|cplext
id|local
r_const
id|uInt
id|cplext
(braket
l_int|31
)braket
op_assign
(brace
multiline_comment|/* Extra bits for literal codes 257..285 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|0
comma
l_int|112
comma
l_int|112
)brace
suffix:semicolon
multiline_comment|/* 112==invalid */
DECL|variable|cpdist
id|local
r_const
id|uInt
id|cpdist
(braket
l_int|30
)braket
op_assign
(brace
multiline_comment|/* Copy offsets for distance codes 0..29 */
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|9
comma
l_int|13
comma
l_int|17
comma
l_int|25
comma
l_int|33
comma
l_int|49
comma
l_int|65
comma
l_int|97
comma
l_int|129
comma
l_int|193
comma
l_int|257
comma
l_int|385
comma
l_int|513
comma
l_int|769
comma
l_int|1025
comma
l_int|1537
comma
l_int|2049
comma
l_int|3073
comma
l_int|4097
comma
l_int|6145
comma
l_int|8193
comma
l_int|12289
comma
l_int|16385
comma
l_int|24577
)brace
suffix:semicolon
DECL|variable|cpdext
id|local
r_const
id|uInt
id|cpdext
(braket
l_int|30
)braket
op_assign
(brace
multiline_comment|/* Extra bits for distance codes */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
l_int|6
comma
l_int|7
comma
l_int|7
comma
l_int|8
comma
l_int|8
comma
l_int|9
comma
l_int|9
comma
l_int|10
comma
l_int|10
comma
l_int|11
comma
l_int|11
comma
l_int|12
comma
l_int|12
comma
l_int|13
comma
l_int|13
)brace
suffix:semicolon
multiline_comment|/*&n;   Huffman code decoding is performed using a multi-level table lookup.&n;   The fastest way to decode is to simply build a lookup table whose&n;   size is determined by the longest code.  However, the time it takes&n;   to build this table can also be a factor if the data being decoded&n;   is not very long.  The most common codes are necessarily the&n;   shortest codes, so those codes dominate the decoding time, and hence&n;   the speed.  The idea is you can have a shorter table that decodes the&n;   shorter, more probable codes, and then point to subsidiary tables for&n;   the longer codes.  The time it costs to decode the longer codes is&n;   then traded against the time it takes to make longer tables.&n;&n;   This results of this trade are in the variables lbits and dbits&n;   below.  lbits is the number of bits the first level table for literal/&n;   length codes can decode in one step, and dbits is the same thing for&n;   the distance codes.  Subsequent tables are also less than or equal to&n;   those sizes.  These values may be adjusted either when all of the&n;   codes are shorter than that, in which case the longest code length in&n;   bits is used, or when the shortest code is *longer* than the requested&n;   table size, in which case the length of the shortest code in bits is&n;   used.&n;&n;   There are two different values for the two tables, since they code a&n;   different number of possibilities each.  The literal/length table&n;   codes 286 possible values, or in a flat code, a little over eight&n;   bits.  The distance table codes 30 possible values, or a little less&n;   than five bits, flat.  The optimum values for speed end up being&n;   about one bit more than those, so lbits is 8+1 and dbits is 5+1.&n;   The optimum values may differ though from machine to machine, and&n;   possibly even between compilers.  Your mileage may vary.&n; */
multiline_comment|/* If BMAX needs to be larger than 16, then h and x[] should be uLong. */
DECL|macro|BMAX
mdefine_line|#define BMAX 15         /* maximum bit length of any code */
DECL|function|huft_build
id|local
r_int
id|huft_build
c_func
(paren
id|uIntf
op_star
id|b
comma
multiline_comment|/* code lengths in bits (all assumed &lt;= BMAX) */
id|uInt
id|n
comma
multiline_comment|/* number of codes (assumed &lt;= 288) */
id|uInt
id|s
comma
multiline_comment|/* number of simple-valued codes (0..s-1) */
r_const
id|uIntf
op_star
id|d
comma
multiline_comment|/* list of base values for non-simple codes */
r_const
id|uIntf
op_star
id|e
comma
multiline_comment|/* list of extra bits for non-simple codes */
id|inflate_huft
op_star
id|FAR
op_star
id|t
comma
multiline_comment|/* result: starting table */
id|uIntf
op_star
id|m
comma
multiline_comment|/* maximum lookup bits, returns actual */
id|inflate_huft
op_star
id|hp
comma
multiline_comment|/* space for trees */
id|uInt
op_star
id|hn
comma
multiline_comment|/* hufts used in space */
id|uIntf
op_star
id|v
multiline_comment|/* working area: values in order of bit length */
)paren
multiline_comment|/* Given a list of code lengths and a maximum table size, make a set of&n;   tables to decode that set of codes.  Return Z_OK on success, Z_BUF_ERROR&n;   if the given code set is incomplete (the tables are still built in this&n;   case), Z_DATA_ERROR if the input is invalid (an over-subscribed set of&n;   lengths), or Z_MEM_ERROR if not enough memory. */
(brace
id|uInt
id|a
suffix:semicolon
multiline_comment|/* counter for codes of length k */
id|uInt
id|c
(braket
id|BMAX
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* bit length count table */
id|uInt
id|f
suffix:semicolon
multiline_comment|/* i repeats in table every f entries */
r_int
id|g
suffix:semicolon
multiline_comment|/* maximum code length */
r_int
id|h
suffix:semicolon
multiline_comment|/* table level */
r_register
id|uInt
id|i
suffix:semicolon
multiline_comment|/* counter, current code */
r_register
id|uInt
id|j
suffix:semicolon
multiline_comment|/* counter */
r_register
r_int
id|k
suffix:semicolon
multiline_comment|/* number of bits in current code */
r_int
id|l
suffix:semicolon
multiline_comment|/* bits per table (returned in m) */
id|uInt
id|mask
suffix:semicolon
multiline_comment|/* (1 &lt;&lt; w) - 1, to avoid cc -O bug on HP */
r_register
id|uIntf
op_star
id|p
suffix:semicolon
multiline_comment|/* pointer into c[], b[], or v[] */
id|inflate_huft
op_star
id|q
suffix:semicolon
multiline_comment|/* points to current table */
r_struct
id|inflate_huft_s
id|r
suffix:semicolon
multiline_comment|/* table entry for structure assignment */
id|inflate_huft
op_star
id|u
(braket
id|BMAX
)braket
suffix:semicolon
multiline_comment|/* table stack */
r_register
r_int
id|w
suffix:semicolon
multiline_comment|/* bits before this table == (l * h) */
id|uInt
id|x
(braket
id|BMAX
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* bit offsets, then code stack */
id|uIntf
op_star
id|xp
suffix:semicolon
multiline_comment|/* pointer into x */
r_int
id|y
suffix:semicolon
multiline_comment|/* number of dummy codes added */
id|uInt
id|z
suffix:semicolon
multiline_comment|/* number of entries in current table */
multiline_comment|/* Generate counts for each bit length */
id|p
op_assign
id|c
suffix:semicolon
DECL|macro|C0
mdefine_line|#define C0 *p++ = 0;
DECL|macro|C2
mdefine_line|#define C2 C0 C0 C0 C0
DECL|macro|C4
mdefine_line|#define C4 C2 C2 C2 C2
id|C4
multiline_comment|/* clear c[]--assume BMAX+1 is 16 */
id|p
op_assign
id|b
suffix:semicolon
id|i
op_assign
id|n
suffix:semicolon
r_do
(brace
id|c
(braket
op_star
id|p
op_increment
)braket
op_increment
suffix:semicolon
multiline_comment|/* assume all entries &lt;= BMAX */
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
(braket
l_int|0
)braket
op_eq
id|n
)paren
multiline_comment|/* null input--all zero length codes */
(brace
op_star
id|t
op_assign
(paren
id|inflate_huft
op_star
)paren
id|Z_NULL
suffix:semicolon
op_star
id|m
op_assign
l_int|0
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
multiline_comment|/* Find minimum and maximum length, bound *m by those */
id|l
op_assign
op_star
id|m
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
op_le
id|BMAX
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|c
(braket
id|j
)braket
)paren
r_break
suffix:semicolon
id|k
op_assign
id|j
suffix:semicolon
multiline_comment|/* minimum code length */
r_if
c_cond
(paren
(paren
id|uInt
)paren
id|l
OL
id|j
)paren
id|l
op_assign
id|j
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|BMAX
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|c
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
id|g
op_assign
id|i
suffix:semicolon
multiline_comment|/* maximum code length */
r_if
c_cond
(paren
(paren
id|uInt
)paren
id|l
OG
id|i
)paren
id|l
op_assign
id|i
suffix:semicolon
op_star
id|m
op_assign
id|l
suffix:semicolon
multiline_comment|/* Adjust last length count to fill out codes, if needed */
r_for
c_loop
(paren
id|y
op_assign
l_int|1
op_lshift
id|j
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
comma
id|y
op_lshift_assign
l_int|1
)paren
r_if
c_cond
(paren
(paren
id|y
op_sub_assign
id|c
(braket
id|j
)braket
)paren
OL
l_int|0
)paren
r_return
id|Z_DATA_ERROR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|y
op_sub_assign
id|c
(braket
id|i
)braket
)paren
OL
l_int|0
)paren
r_return
id|Z_DATA_ERROR
suffix:semicolon
id|c
(braket
id|i
)braket
op_add_assign
id|y
suffix:semicolon
multiline_comment|/* Generate starting offsets into the value table for each length */
id|x
(braket
l_int|1
)braket
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|c
op_plus
l_int|1
suffix:semicolon
id|xp
op_assign
id|x
op_plus
l_int|2
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
)paren
(brace
multiline_comment|/* note that i == g from above */
op_star
id|xp
op_increment
op_assign
(paren
id|j
op_add_assign
op_star
id|p
op_increment
)paren
suffix:semicolon
)brace
multiline_comment|/* Make a table of values in order of bit lengths */
id|p
op_assign
id|b
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|j
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_int|0
)paren
id|v
(braket
id|x
(braket
id|j
)braket
op_increment
)braket
op_assign
id|i
suffix:semicolon
)brace
r_while
c_loop
(paren
op_increment
id|i
OL
id|n
)paren
suffix:semicolon
id|n
op_assign
id|x
(braket
id|g
)braket
suffix:semicolon
multiline_comment|/* set n to length of v */
multiline_comment|/* Generate the Huffman codes and for each, make the table entries */
id|x
(braket
l_int|0
)braket
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* first Huffman code is zero */
id|p
op_assign
id|v
suffix:semicolon
multiline_comment|/* grab values in bit order */
id|h
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* no tables yet--level -1 */
id|w
op_assign
op_minus
id|l
suffix:semicolon
multiline_comment|/* bits decoded == (l * h) */
id|u
(braket
l_int|0
)braket
op_assign
(paren
id|inflate_huft
op_star
)paren
id|Z_NULL
suffix:semicolon
multiline_comment|/* just to keep compilers happy */
id|q
op_assign
(paren
id|inflate_huft
op_star
)paren
id|Z_NULL
suffix:semicolon
multiline_comment|/* ditto */
id|z
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ditto */
multiline_comment|/* go through the bit lengths (k already is bits in shortest code) */
r_for
c_loop
(paren
suffix:semicolon
id|k
op_le
id|g
suffix:semicolon
id|k
op_increment
)paren
(brace
id|a
op_assign
id|c
(braket
id|k
)braket
suffix:semicolon
r_while
c_loop
(paren
id|a
op_decrement
)paren
(brace
multiline_comment|/* here i is the Huffman code of length k bits for value *p */
multiline_comment|/* make tables up to required level */
r_while
c_loop
(paren
id|k
OG
id|w
op_plus
id|l
)paren
(brace
id|h
op_increment
suffix:semicolon
id|w
op_add_assign
id|l
suffix:semicolon
multiline_comment|/* previous table always l bits */
multiline_comment|/* compute minimum size table less than or equal to l bits */
id|z
op_assign
id|g
op_minus
id|w
suffix:semicolon
id|z
op_assign
id|z
OG
(paren
id|uInt
)paren
id|l
ques
c_cond
id|l
suffix:colon
id|z
suffix:semicolon
multiline_comment|/* table size upper limit */
r_if
c_cond
(paren
(paren
id|f
op_assign
l_int|1
op_lshift
(paren
id|j
op_assign
id|k
op_minus
id|w
)paren
)paren
OG
id|a
op_plus
l_int|1
)paren
multiline_comment|/* try a k-w bit table */
(brace
multiline_comment|/* too few codes for k-w bit table */
id|f
op_sub_assign
id|a
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* deduct codes from patterns left */
id|xp
op_assign
id|c
op_plus
id|k
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
id|z
)paren
r_while
c_loop
(paren
op_increment
id|j
OL
id|z
)paren
multiline_comment|/* try smaller tables up to z bits */
(brace
r_if
c_cond
(paren
(paren
id|f
op_lshift_assign
l_int|1
)paren
op_le
op_star
op_increment
id|xp
)paren
r_break
suffix:semicolon
multiline_comment|/* enough codes to use up j bits */
id|f
op_sub_assign
op_star
id|xp
suffix:semicolon
multiline_comment|/* else deduct codes from patterns */
)brace
)brace
id|z
op_assign
l_int|1
op_lshift
id|j
suffix:semicolon
multiline_comment|/* table entries for j-bit table */
multiline_comment|/* allocate new table */
r_if
c_cond
(paren
op_star
id|hn
op_plus
id|z
OG
id|MANY
)paren
multiline_comment|/* (note: doesn&squot;t matter for fixed) */
r_return
id|Z_MEM_ERROR
suffix:semicolon
multiline_comment|/* not enough memory */
id|u
(braket
id|h
)braket
op_assign
id|q
op_assign
id|hp
op_plus
op_star
id|hn
suffix:semicolon
op_star
id|hn
op_add_assign
id|z
suffix:semicolon
multiline_comment|/* connect to last table, if there is one */
r_if
c_cond
(paren
id|h
)paren
(brace
id|x
(braket
id|h
)braket
op_assign
id|i
suffix:semicolon
multiline_comment|/* save pattern for backing up */
id|r.bits
op_assign
(paren
id|Byte
)paren
id|l
suffix:semicolon
multiline_comment|/* bits to dump before this table */
id|r.exop
op_assign
(paren
id|Byte
)paren
id|j
suffix:semicolon
multiline_comment|/* bits in this table */
id|j
op_assign
id|i
op_rshift
(paren
id|w
op_minus
id|l
)paren
suffix:semicolon
id|r.base
op_assign
(paren
id|uInt
)paren
(paren
id|q
op_minus
id|u
(braket
id|h
op_minus
l_int|1
)braket
op_minus
id|j
)paren
suffix:semicolon
multiline_comment|/* offset to this table */
id|u
(braket
id|h
op_minus
l_int|1
)braket
(braket
id|j
)braket
op_assign
id|r
suffix:semicolon
multiline_comment|/* connect to last table */
)brace
r_else
op_star
id|t
op_assign
id|q
suffix:semicolon
multiline_comment|/* first table is returned result */
)brace
multiline_comment|/* set up table entry in r */
id|r.bits
op_assign
(paren
id|Byte
)paren
(paren
id|k
op_minus
id|w
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
id|v
op_plus
id|n
)paren
id|r.exop
op_assign
l_int|128
op_plus
l_int|64
suffix:semicolon
multiline_comment|/* out of values--invalid code */
r_else
r_if
c_cond
(paren
op_star
id|p
OL
id|s
)paren
(brace
id|r.exop
op_assign
(paren
id|Byte
)paren
(paren
op_star
id|p
OL
l_int|256
ques
c_cond
l_int|0
suffix:colon
l_int|32
op_plus
l_int|64
)paren
suffix:semicolon
multiline_comment|/* 256 is end-of-block */
id|r.base
op_assign
op_star
id|p
op_increment
suffix:semicolon
multiline_comment|/* simple code is just the value */
)brace
r_else
(brace
id|r.exop
op_assign
(paren
id|Byte
)paren
(paren
id|e
(braket
op_star
id|p
op_minus
id|s
)braket
op_plus
l_int|16
op_plus
l_int|64
)paren
suffix:semicolon
multiline_comment|/* non-simple--look up in lists */
id|r.base
op_assign
id|d
(braket
op_star
id|p
op_increment
op_minus
id|s
)braket
suffix:semicolon
)brace
multiline_comment|/* fill code-like entries with r */
id|f
op_assign
l_int|1
op_lshift
(paren
id|k
op_minus
id|w
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
op_rshift
id|w
suffix:semicolon
id|j
OL
id|z
suffix:semicolon
id|j
op_add_assign
id|f
)paren
id|q
(braket
id|j
)braket
op_assign
id|r
suffix:semicolon
multiline_comment|/* backwards increment the k-bit code i */
r_for
c_loop
(paren
id|j
op_assign
l_int|1
op_lshift
(paren
id|k
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_amp
id|j
suffix:semicolon
id|j
op_rshift_assign
l_int|1
)paren
id|i
op_xor_assign
id|j
suffix:semicolon
id|i
op_xor_assign
id|j
suffix:semicolon
multiline_comment|/* backup over finished tables */
id|mask
op_assign
(paren
l_int|1
op_lshift
id|w
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* needed on HP, cc -O bug */
r_while
c_loop
(paren
(paren
id|i
op_amp
id|mask
)paren
op_ne
id|x
(braket
id|h
)braket
)paren
(brace
id|h
op_decrement
suffix:semicolon
multiline_comment|/* don&squot;t need to update q */
id|w
op_sub_assign
id|l
suffix:semicolon
id|mask
op_assign
(paren
l_int|1
op_lshift
id|w
)paren
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Return Z_BUF_ERROR if we were given an incomplete table */
r_return
id|y
op_ne
l_int|0
op_logical_and
id|g
op_ne
l_int|1
ques
c_cond
id|Z_BUF_ERROR
suffix:colon
id|Z_OK
suffix:semicolon
)brace
DECL|function|zlib_inflate_trees_bits
r_int
id|zlib_inflate_trees_bits
c_func
(paren
id|uIntf
op_star
id|c
comma
multiline_comment|/* 19 code lengths */
id|uIntf
op_star
id|bb
comma
multiline_comment|/* bits tree desired/actual depth */
id|inflate_huft
op_star
id|FAR
op_star
id|tb
comma
multiline_comment|/* bits tree result */
id|inflate_huft
op_star
id|hp
comma
multiline_comment|/* space for trees */
id|z_streamp
id|z
multiline_comment|/* for messages */
)paren
(brace
r_int
id|r
suffix:semicolon
id|uInt
id|hn
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* hufts used in space */
id|uIntf
op_star
id|v
suffix:semicolon
multiline_comment|/* work area for huft_build */
id|v
op_assign
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|tree_work_area_1
suffix:semicolon
id|r
op_assign
id|huft_build
c_func
(paren
id|c
comma
l_int|19
comma
l_int|19
comma
(paren
id|uIntf
op_star
)paren
id|Z_NULL
comma
(paren
id|uIntf
op_star
)paren
id|Z_NULL
comma
id|tb
comma
id|bb
comma
id|hp
comma
op_amp
id|hn
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
id|Z_DATA_ERROR
)paren
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;oversubscribed dynamic bit lengths tree&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r
op_eq
id|Z_BUF_ERROR
op_logical_or
op_star
id|bb
op_eq
l_int|0
)paren
(brace
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;incomplete dynamic bit lengths tree&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|zlib_inflate_trees_dynamic
r_int
id|zlib_inflate_trees_dynamic
c_func
(paren
id|uInt
id|nl
comma
multiline_comment|/* number of literal/length codes */
id|uInt
id|nd
comma
multiline_comment|/* number of distance codes */
id|uIntf
op_star
id|c
comma
multiline_comment|/* that many (total) code lengths */
id|uIntf
op_star
id|bl
comma
multiline_comment|/* literal desired/actual bit depth */
id|uIntf
op_star
id|bd
comma
multiline_comment|/* distance desired/actual bit depth */
id|inflate_huft
op_star
id|FAR
op_star
id|tl
comma
multiline_comment|/* literal/length tree result */
id|inflate_huft
op_star
id|FAR
op_star
id|td
comma
multiline_comment|/* distance tree result */
id|inflate_huft
op_star
id|hp
comma
multiline_comment|/* space for trees */
id|z_streamp
id|z
multiline_comment|/* for messages */
)paren
(brace
r_int
id|r
suffix:semicolon
id|uInt
id|hn
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* hufts used in space */
id|uIntf
op_star
id|v
suffix:semicolon
multiline_comment|/* work area for huft_build */
multiline_comment|/* allocate work area */
id|v
op_assign
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|tree_work_area_2
suffix:semicolon
multiline_comment|/* build literal/length tree */
id|r
op_assign
id|huft_build
c_func
(paren
id|c
comma
id|nl
comma
l_int|257
comma
id|cplens
comma
id|cplext
comma
id|tl
comma
id|bl
comma
id|hp
comma
op_amp
id|hn
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
op_logical_or
op_star
id|bl
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|r
op_eq
id|Z_DATA_ERROR
)paren
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;oversubscribed literal/length tree&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r
op_ne
id|Z_MEM_ERROR
)paren
(brace
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;incomplete literal/length tree&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/* build distance tree */
id|r
op_assign
id|huft_build
c_func
(paren
id|c
op_plus
id|nl
comma
id|nd
comma
l_int|0
comma
id|cpdist
comma
id|cpdext
comma
id|td
comma
id|bd
comma
id|hp
comma
op_amp
id|hn
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
op_logical_or
(paren
op_star
id|bd
op_eq
l_int|0
op_logical_and
id|nl
OG
l_int|257
)paren
)paren
(brace
r_if
c_cond
(paren
id|r
op_eq
id|Z_DATA_ERROR
)paren
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;oversubscribed distance tree&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r
op_eq
id|Z_BUF_ERROR
)paren
(brace
macro_line|#ifdef PKZIP_BUG_WORKAROUND
id|r
op_assign
id|Z_OK
suffix:semicolon
)brace
macro_line|#else
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;incomplete distance tree&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|r
op_ne
id|Z_MEM_ERROR
)paren
(brace
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;empty distance tree with lengths&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* done */
r_return
id|Z_OK
suffix:semicolon
)brace
multiline_comment|/* build fixed tables only once--keep them here */
macro_line|#include &quot;inffixed.h&quot;
DECL|function|zlib_inflate_trees_fixed
r_int
id|zlib_inflate_trees_fixed
c_func
(paren
id|uIntf
op_star
id|bl
comma
multiline_comment|/* literal desired/actual bit depth */
id|uIntf
op_star
id|bd
comma
multiline_comment|/* distance desired/actual bit depth */
id|inflate_huft
op_star
id|FAR
op_star
id|tl
comma
multiline_comment|/* literal/length tree result */
id|inflate_huft
op_star
id|FAR
op_star
id|td
comma
multiline_comment|/* distance tree result */
id|z_streamp
id|z
multiline_comment|/* for memory allocation */
)paren
(brace
op_star
id|bl
op_assign
id|fixed_bl
suffix:semicolon
op_star
id|bd
op_assign
id|fixed_bd
suffix:semicolon
op_star
id|tl
op_assign
id|fixed_tl
suffix:semicolon
op_star
id|td
op_assign
id|fixed_td
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
eof
