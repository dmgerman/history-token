multiline_comment|/* infblock.c -- interpret and process block types to last block&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
macro_line|#include &lt;linux/zutil.h&gt;
macro_line|#include &quot;infblock.h&quot;
macro_line|#include &quot;inftrees.h&quot;
macro_line|#include &quot;infcodes.h&quot;
macro_line|#include &quot;infutil.h&quot;
r_struct
id|inflate_codes_state
suffix:semicolon
multiline_comment|/* simplify the use of the inflate_huft type with some defines */
DECL|macro|exop
mdefine_line|#define exop word.what.Exop
DECL|macro|bits
mdefine_line|#define bits word.what.Bits
multiline_comment|/* Table for deflate from PKZIP&squot;s appnote.txt. */
DECL|variable|border
id|local
r_const
id|uInt
id|border
(braket
)braket
op_assign
(brace
multiline_comment|/* Order of the bit length code lengths */
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|0
comma
l_int|8
comma
l_int|7
comma
l_int|9
comma
l_int|6
comma
l_int|10
comma
l_int|5
comma
l_int|11
comma
l_int|4
comma
l_int|12
comma
l_int|3
comma
l_int|13
comma
l_int|2
comma
l_int|14
comma
l_int|1
comma
l_int|15
)brace
suffix:semicolon
multiline_comment|/*&n;   Notes beyond the 1.93a appnote.txt:&n;&n;   1. Distance pointers never point before the beginning of the output&n;      stream.&n;   2. Distance pointers can point back across blocks, up to 32k away.&n;   3. There is an implied maximum of 7 bits for the bit length table and&n;      15 bits for the actual data.&n;   4. If only one code exists, then it is encoded using one bit.  (Zero&n;      would be more efficient, but perhaps a little confusing.)  If two&n;      codes exist, they are coded using one bit each (0 and 1).&n;   5. There is no way of sending zero distance codes--a dummy must be&n;      sent if there are none.  (History: a pre 2.0 version of PKZIP would&n;      store blocks with no distance codes, but this was discovered to be&n;      too harsh a criterion.)  Valid only for 1.93a.  2.04c does allow&n;      zero distance codes, which is sent as one code of zero bits in&n;      length.&n;   6. There are up to 286 literal/length codes.  Code 256 represents the&n;      end-of-block.  Note however that the static length tree defines&n;      288 codes just to fill out the Huffman codes.  Codes 286 and 287&n;      cannot be used though, since there is no length base or extra bits&n;      defined for them.  Similarily, there are up to 30 distance codes.&n;      However, static trees define 32 codes (all 5 bits) to fill out the&n;      Huffman codes, but the last two had better not show up in the data.&n;   7. Unzip can check dynamic Huffman blocks for complete code sets.&n;      The exception is that a single code would not be complete (see #4).&n;   8. The five bits following the block type is really the number of&n;      literal codes sent minus 257.&n;   9. Length codes 8,16,16 are interpreted as 13 length codes of 8 bits&n;      (1+6+6).  Therefore, to output three times the length, you output&n;      three codes (1+1+1), whereas to output four times the same length,&n;      you only need two codes (1+3).  Hmm.&n;  10. In the tree reconstruction algorithm, Code = Code + Increment&n;      only if BitLength(i) is not zero.  (Pretty obvious.)&n;  11. Correction: 4 Bits: # of Bit Length codes - 4     (4 - 19)&n;  12. Note: length code 284 can represent 227-258, but length code 285&n;      really is 258.  The last length deserves its own, short code&n;      since it gets used a lot in very redundant files.  The length&n;      258 is special since 258 - 3 (the min match length) is 255.&n;  13. The literal/length and distance code bit lengths are read as a&n;      single stream of lengths.  It is possible (and advantageous) for&n;      a repeat code (16, 17, or 18) to go across the boundary between&n;      the two sets of lengths.&n; */
DECL|function|zlib_inflate_blocks_reset
r_void
id|zlib_inflate_blocks_reset
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
comma
id|z_streamp
id|z
comma
id|uLong
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|c
op_ne
id|Z_NULL
)paren
op_star
id|c
op_assign
id|s-&gt;check
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;mode
op_eq
id|CODES
)paren
id|zlib_inflate_codes_free
c_func
(paren
id|s-&gt;sub.decode.codes
comma
id|z
)paren
suffix:semicolon
id|s-&gt;mode
op_assign
id|TYPE
suffix:semicolon
id|s-&gt;bitk
op_assign
l_int|0
suffix:semicolon
id|s-&gt;bitb
op_assign
l_int|0
suffix:semicolon
id|s-&gt;read
op_assign
id|s-&gt;write
op_assign
id|s-&gt;window
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;checkfn
op_ne
id|Z_NULL
)paren
id|z-&gt;adler
op_assign
id|s-&gt;check
op_assign
(paren
op_star
id|s-&gt;checkfn
)paren
(paren
l_int|0L
comma
(paren
r_const
id|Byte
op_star
)paren
id|Z_NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|zlib_inflate_blocks_new
id|inflate_blocks_statef
op_star
id|zlib_inflate_blocks_new
c_func
(paren
id|z_streamp
id|z
comma
id|check_func
id|c
comma
id|uInt
id|w
)paren
(brace
id|inflate_blocks_statef
op_star
id|s
suffix:semicolon
id|s
op_assign
op_amp
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|working_blocks_state
suffix:semicolon
id|s-&gt;hufts
op_assign
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|working_hufts
suffix:semicolon
id|s-&gt;window
op_assign
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|working_window
suffix:semicolon
id|s-&gt;end
op_assign
id|s-&gt;window
op_plus
id|w
suffix:semicolon
id|s-&gt;checkfn
op_assign
id|c
suffix:semicolon
id|s-&gt;mode
op_assign
id|TYPE
suffix:semicolon
id|zlib_inflate_blocks_reset
c_func
(paren
id|s
comma
id|z
comma
id|Z_NULL
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|zlib_inflate_blocks
r_int
id|zlib_inflate_blocks
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
comma
id|z_streamp
id|z
comma
r_int
id|r
)paren
(brace
id|uInt
id|t
suffix:semicolon
multiline_comment|/* temporary storage */
id|uLong
id|b
suffix:semicolon
multiline_comment|/* bit buffer */
id|uInt
id|k
suffix:semicolon
multiline_comment|/* bits in bit buffer */
id|Byte
op_star
id|p
suffix:semicolon
multiline_comment|/* input data pointer */
id|uInt
id|n
suffix:semicolon
multiline_comment|/* bytes available there */
id|Byte
op_star
id|q
suffix:semicolon
multiline_comment|/* output window write pointer */
id|uInt
id|m
suffix:semicolon
multiline_comment|/* bytes to end of window or read pointer */
multiline_comment|/* copy input/output information to locals (UPDATE macro restores) */
id|LOAD
multiline_comment|/* process input based on current state */
r_while
c_loop
(paren
l_int|1
)paren
r_switch
c_cond
(paren
id|s-&gt;mode
)paren
(brace
r_case
id|TYPE
suffix:colon
id|NEEDBITS
c_func
(paren
l_int|3
)paren
id|t
op_assign
(paren
id|uInt
)paren
id|b
op_amp
l_int|7
suffix:semicolon
id|s-&gt;last
op_assign
id|t
op_amp
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|t
op_rshift
l_int|1
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* stored */
id|DUMPBITS
c_func
(paren
l_int|3
)paren
id|t
op_assign
id|k
op_amp
l_int|7
suffix:semicolon
multiline_comment|/* go to byte boundary */
id|DUMPBITS
c_func
(paren
id|t
)paren
id|s-&gt;mode
op_assign
id|LENS
suffix:semicolon
multiline_comment|/* get length of stored block */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* fixed */
(brace
id|uInt
id|bl
comma
id|bd
suffix:semicolon
id|inflate_huft
op_star
id|tl
comma
op_star
id|td
suffix:semicolon
id|zlib_inflate_trees_fixed
c_func
(paren
op_amp
id|bl
comma
op_amp
id|bd
comma
op_amp
id|tl
comma
op_amp
id|td
comma
id|z
)paren
suffix:semicolon
id|s-&gt;sub.decode.codes
op_assign
id|zlib_inflate_codes_new
c_func
(paren
id|bl
comma
id|bd
comma
id|tl
comma
id|td
comma
id|z
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;sub.decode.codes
op_eq
id|Z_NULL
)paren
(brace
id|r
op_assign
id|Z_MEM_ERROR
suffix:semicolon
id|LEAVE
)brace
)brace
id|DUMPBITS
c_func
(paren
l_int|3
)paren
id|s-&gt;mode
op_assign
id|CODES
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* dynamic */
id|DUMPBITS
c_func
(paren
l_int|3
)paren
id|s-&gt;mode
op_assign
id|TABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* illegal */
id|DUMPBITS
c_func
(paren
l_int|3
)paren
id|s-&gt;mode
op_assign
id|B_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;invalid block type&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
)brace
r_break
suffix:semicolon
r_case
id|LENS
suffix:colon
id|NEEDBITS
c_func
(paren
l_int|32
)paren
r_if
c_cond
(paren
(paren
(paren
(paren
op_complement
id|b
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
)paren
op_ne
(paren
id|b
op_amp
l_int|0xffff
)paren
)paren
(brace
id|s-&gt;mode
op_assign
id|B_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;invalid stored block lengths&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
)brace
id|s-&gt;sub.left
op_assign
(paren
id|uInt
)paren
id|b
op_amp
l_int|0xffff
suffix:semicolon
id|b
op_assign
id|k
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* dump bits */
id|s-&gt;mode
op_assign
id|s-&gt;sub.left
ques
c_cond
id|STORED
suffix:colon
(paren
id|s-&gt;last
ques
c_cond
id|DRY
suffix:colon
id|TYPE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STORED
suffix:colon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
id|LEAVE
id|NEEDOUT
id|t
op_assign
id|s-&gt;sub.left
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
id|n
)paren
id|t
op_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
id|m
)paren
id|t
op_assign
id|m
suffix:semicolon
id|memcpy
c_func
(paren
id|q
comma
id|p
comma
id|t
)paren
suffix:semicolon
id|p
op_add_assign
id|t
suffix:semicolon
id|n
op_sub_assign
id|t
suffix:semicolon
id|q
op_add_assign
id|t
suffix:semicolon
id|m
op_sub_assign
id|t
suffix:semicolon
r_if
c_cond
(paren
(paren
id|s-&gt;sub.left
op_sub_assign
id|t
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|s-&gt;mode
op_assign
id|s-&gt;last
ques
c_cond
id|DRY
suffix:colon
id|TYPE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TABLE
suffix:colon
id|NEEDBITS
c_func
(paren
l_int|14
)paren
id|s-&gt;sub.trees.table
op_assign
id|t
op_assign
(paren
id|uInt
)paren
id|b
op_amp
l_int|0x3fff
suffix:semicolon
macro_line|#ifndef PKZIP_BUG_WORKAROUND
r_if
c_cond
(paren
(paren
id|t
op_amp
l_int|0x1f
)paren
OG
l_int|29
op_logical_or
(paren
(paren
id|t
op_rshift
l_int|5
)paren
op_amp
l_int|0x1f
)paren
OG
l_int|29
)paren
(brace
id|s-&gt;mode
op_assign
id|B_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;too many length or distance symbols&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
)brace
macro_line|#endif
(brace
id|s-&gt;sub.trees.blens
op_assign
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|working_blens
suffix:semicolon
)brace
id|DUMPBITS
c_func
(paren
l_int|14
)paren
id|s-&gt;sub.trees.index
op_assign
l_int|0
suffix:semicolon
id|s-&gt;mode
op_assign
id|BTREE
suffix:semicolon
r_case
id|BTREE
suffix:colon
r_while
c_loop
(paren
id|s-&gt;sub.trees.index
OL
l_int|4
op_plus
(paren
id|s-&gt;sub.trees.table
op_rshift
l_int|10
)paren
)paren
(brace
id|NEEDBITS
c_func
(paren
l_int|3
)paren
id|s-&gt;sub.trees.blens
(braket
id|border
(braket
id|s-&gt;sub.trees.index
op_increment
)braket
)braket
op_assign
(paren
id|uInt
)paren
id|b
op_amp
l_int|7
suffix:semicolon
id|DUMPBITS
c_func
(paren
l_int|3
)paren
)brace
r_while
c_loop
(paren
id|s-&gt;sub.trees.index
OL
l_int|19
)paren
id|s-&gt;sub.trees.blens
(braket
id|border
(braket
id|s-&gt;sub.trees.index
op_increment
)braket
)braket
op_assign
l_int|0
suffix:semicolon
id|s-&gt;sub.trees.bb
op_assign
l_int|7
suffix:semicolon
id|t
op_assign
id|zlib_inflate_trees_bits
c_func
(paren
id|s-&gt;sub.trees.blens
comma
op_amp
id|s-&gt;sub.trees.bb
comma
op_amp
id|s-&gt;sub.trees.tb
comma
id|s-&gt;hufts
comma
id|z
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_ne
id|Z_OK
)paren
(brace
id|r
op_assign
id|t
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
id|Z_DATA_ERROR
)paren
id|s-&gt;mode
op_assign
id|B_BAD
suffix:semicolon
id|LEAVE
)brace
id|s-&gt;sub.trees.index
op_assign
l_int|0
suffix:semicolon
id|s-&gt;mode
op_assign
id|DTREE
suffix:semicolon
r_case
id|DTREE
suffix:colon
r_while
c_loop
(paren
id|t
op_assign
id|s-&gt;sub.trees.table
comma
id|s-&gt;sub.trees.index
OL
l_int|258
op_plus
(paren
id|t
op_amp
l_int|0x1f
)paren
op_plus
(paren
(paren
id|t
op_rshift
l_int|5
)paren
op_amp
l_int|0x1f
)paren
)paren
(brace
id|inflate_huft
op_star
id|h
suffix:semicolon
id|uInt
id|i
comma
id|j
comma
id|c
suffix:semicolon
id|t
op_assign
id|s-&gt;sub.trees.bb
suffix:semicolon
id|NEEDBITS
c_func
(paren
id|t
)paren
id|h
op_assign
id|s-&gt;sub.trees.tb
op_plus
(paren
(paren
id|uInt
)paren
id|b
op_amp
id|zlib_inflate_mask
(braket
id|t
)braket
)paren
suffix:semicolon
id|t
op_assign
id|h-&gt;bits
suffix:semicolon
id|c
op_assign
id|h-&gt;base
suffix:semicolon
r_if
c_cond
(paren
id|c
OL
l_int|16
)paren
(brace
id|DUMPBITS
c_func
(paren
id|t
)paren
id|s-&gt;sub.trees.blens
(braket
id|s-&gt;sub.trees.index
op_increment
)braket
op_assign
id|c
suffix:semicolon
)brace
r_else
multiline_comment|/* c == 16..18 */
(brace
id|i
op_assign
id|c
op_eq
l_int|18
ques
c_cond
l_int|7
suffix:colon
id|c
op_minus
l_int|14
suffix:semicolon
id|j
op_assign
id|c
op_eq
l_int|18
ques
c_cond
l_int|11
suffix:colon
l_int|3
suffix:semicolon
id|NEEDBITS
c_func
(paren
id|t
op_plus
id|i
)paren
id|DUMPBITS
c_func
(paren
id|t
)paren
id|j
op_add_assign
(paren
id|uInt
)paren
id|b
op_amp
id|zlib_inflate_mask
(braket
id|i
)braket
suffix:semicolon
id|DUMPBITS
c_func
(paren
id|i
)paren
id|i
op_assign
id|s-&gt;sub.trees.index
suffix:semicolon
id|t
op_assign
id|s-&gt;sub.trees.table
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
id|j
OG
l_int|258
op_plus
(paren
id|t
op_amp
l_int|0x1f
)paren
op_plus
(paren
(paren
id|t
op_rshift
l_int|5
)paren
op_amp
l_int|0x1f
)paren
op_logical_or
(paren
id|c
op_eq
l_int|16
op_logical_and
id|i
OL
l_int|1
)paren
)paren
(brace
id|s-&gt;mode
op_assign
id|B_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;invalid bit length repeat&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
)brace
id|c
op_assign
id|c
op_eq
l_int|16
ques
c_cond
id|s-&gt;sub.trees.blens
(braket
id|i
op_minus
l_int|1
)braket
suffix:colon
l_int|0
suffix:semicolon
r_do
(brace
id|s-&gt;sub.trees.blens
(braket
id|i
op_increment
)braket
op_assign
id|c
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
id|s-&gt;sub.trees.index
op_assign
id|i
suffix:semicolon
)brace
)brace
id|s-&gt;sub.trees.tb
op_assign
id|Z_NULL
suffix:semicolon
(brace
id|uInt
id|bl
comma
id|bd
suffix:semicolon
id|inflate_huft
op_star
id|tl
comma
op_star
id|td
suffix:semicolon
id|inflate_codes_statef
op_star
id|c
suffix:semicolon
id|bl
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* must be &lt;= 9 for lookahead assumptions */
id|bd
op_assign
l_int|6
suffix:semicolon
multiline_comment|/* must be &lt;= 9 for lookahead assumptions */
id|t
op_assign
id|s-&gt;sub.trees.table
suffix:semicolon
id|t
op_assign
id|zlib_inflate_trees_dynamic
c_func
(paren
l_int|257
op_plus
(paren
id|t
op_amp
l_int|0x1f
)paren
comma
l_int|1
op_plus
(paren
(paren
id|t
op_rshift
l_int|5
)paren
op_amp
l_int|0x1f
)paren
comma
id|s-&gt;sub.trees.blens
comma
op_amp
id|bl
comma
op_amp
id|bd
comma
op_amp
id|tl
comma
op_amp
id|td
comma
id|s-&gt;hufts
comma
id|z
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_ne
id|Z_OK
)paren
(brace
r_if
c_cond
(paren
id|t
op_eq
(paren
id|uInt
)paren
id|Z_DATA_ERROR
)paren
id|s-&gt;mode
op_assign
id|B_BAD
suffix:semicolon
id|r
op_assign
id|t
suffix:semicolon
id|LEAVE
)brace
r_if
c_cond
(paren
(paren
id|c
op_assign
id|zlib_inflate_codes_new
c_func
(paren
id|bl
comma
id|bd
comma
id|tl
comma
id|td
comma
id|z
)paren
)paren
op_eq
id|Z_NULL
)paren
(brace
id|r
op_assign
id|Z_MEM_ERROR
suffix:semicolon
id|LEAVE
)brace
id|s-&gt;sub.decode.codes
op_assign
id|c
suffix:semicolon
)brace
id|s-&gt;mode
op_assign
id|CODES
suffix:semicolon
r_case
id|CODES
suffix:colon
id|UPDATE
r_if
c_cond
(paren
(paren
id|r
op_assign
id|zlib_inflate_codes
c_func
(paren
id|s
comma
id|z
comma
id|r
)paren
)paren
op_ne
id|Z_STREAM_END
)paren
r_return
id|zlib_inflate_flush
c_func
(paren
id|s
comma
id|z
comma
id|r
)paren
suffix:semicolon
id|r
op_assign
id|Z_OK
suffix:semicolon
id|zlib_inflate_codes_free
c_func
(paren
id|s-&gt;sub.decode.codes
comma
id|z
)paren
suffix:semicolon
id|LOAD
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;last
)paren
(brace
id|s-&gt;mode
op_assign
id|TYPE
suffix:semicolon
r_break
suffix:semicolon
)brace
id|s-&gt;mode
op_assign
id|DRY
suffix:semicolon
r_case
id|DRY
suffix:colon
id|FLUSH
r_if
c_cond
(paren
id|s-&gt;read
op_ne
id|s-&gt;write
)paren
id|LEAVE
id|s-&gt;mode
op_assign
id|B_DONE
suffix:semicolon
r_case
id|B_DONE
suffix:colon
id|r
op_assign
id|Z_STREAM_END
suffix:semicolon
id|LEAVE
r_case
id|B_BAD
suffix:colon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
r_default
suffix:colon
id|r
op_assign
id|Z_STREAM_ERROR
suffix:semicolon
id|LEAVE
)brace
)brace
DECL|function|zlib_inflate_blocks_free
r_int
id|zlib_inflate_blocks_free
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
comma
id|z_streamp
id|z
)paren
(brace
id|zlib_inflate_blocks_reset
c_func
(paren
id|s
comma
id|z
comma
id|Z_NULL
)paren
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
DECL|function|zlib_inflate_set_dictionary
r_void
id|zlib_inflate_set_dictionary
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
comma
r_const
id|Byte
op_star
id|d
comma
id|uInt
id|n
)paren
(brace
id|memcpy
c_func
(paren
id|s-&gt;window
comma
id|d
comma
id|n
)paren
suffix:semicolon
id|s-&gt;read
op_assign
id|s-&gt;write
op_assign
id|s-&gt;window
op_plus
id|n
suffix:semicolon
)brace
multiline_comment|/* Returns true if inflate is currently at the end of a block generated&n; * by Z_SYNC_FLUSH or Z_FULL_FLUSH. &n; * IN assertion: s != Z_NULL&n; */
DECL|function|zlib_inflate_blocks_sync_point
r_int
id|zlib_inflate_blocks_sync_point
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
)paren
(brace
r_return
id|s-&gt;mode
op_eq
id|LENS
suffix:semicolon
)brace
eof
