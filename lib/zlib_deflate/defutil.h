DECL|macro|Assert
mdefine_line|#define Assert(err, str) 
DECL|macro|Trace
mdefine_line|#define Trace(dummy) 
DECL|macro|Tracev
mdefine_line|#define Tracev(dummy) 
DECL|macro|Tracecv
mdefine_line|#define Tracecv(err, dummy) 
DECL|macro|Tracevv
mdefine_line|#define Tracevv(dummy) 
DECL|macro|LENGTH_CODES
mdefine_line|#define LENGTH_CODES 29
multiline_comment|/* number of length codes, not counting the special END_BLOCK code */
DECL|macro|LITERALS
mdefine_line|#define LITERALS  256
multiline_comment|/* number of literal bytes 0..255 */
DECL|macro|L_CODES
mdefine_line|#define L_CODES (LITERALS+1+LENGTH_CODES)
multiline_comment|/* number of Literal or Length codes, including the END_BLOCK code */
DECL|macro|D_CODES
mdefine_line|#define D_CODES   30
multiline_comment|/* number of distance codes */
DECL|macro|BL_CODES
mdefine_line|#define BL_CODES  19
multiline_comment|/* number of codes used to transfer the bit lengths */
DECL|macro|HEAP_SIZE
mdefine_line|#define HEAP_SIZE (2*L_CODES+1)
multiline_comment|/* maximum heap size */
DECL|macro|MAX_BITS
mdefine_line|#define MAX_BITS 15
multiline_comment|/* All codes must not exceed MAX_BITS bits */
DECL|macro|INIT_STATE
mdefine_line|#define INIT_STATE    42
DECL|macro|BUSY_STATE
mdefine_line|#define BUSY_STATE   113
DECL|macro|FINISH_STATE
mdefine_line|#define FINISH_STATE 666
multiline_comment|/* Stream status */
multiline_comment|/* Data structure describing a single value and its code string. */
DECL|struct|ct_data_s
r_typedef
r_struct
id|ct_data_s
(brace
r_union
(brace
DECL|member|freq
id|ush
id|freq
suffix:semicolon
multiline_comment|/* frequency count */
DECL|member|code
id|ush
id|code
suffix:semicolon
multiline_comment|/* bit string */
DECL|member|fc
)brace
id|fc
suffix:semicolon
r_union
(brace
DECL|member|dad
id|ush
id|dad
suffix:semicolon
multiline_comment|/* father node in Huffman tree */
DECL|member|len
id|ush
id|len
suffix:semicolon
multiline_comment|/* length of bit string */
DECL|member|dl
)brace
id|dl
suffix:semicolon
DECL|typedef|ct_data
)brace
id|FAR
id|ct_data
suffix:semicolon
DECL|macro|Freq
mdefine_line|#define Freq fc.freq
DECL|macro|Code
mdefine_line|#define Code fc.code
DECL|macro|Dad
mdefine_line|#define Dad  dl.dad
DECL|macro|Len
mdefine_line|#define Len  dl.len
DECL|typedef|static_tree_desc
r_typedef
r_struct
id|static_tree_desc_s
id|static_tree_desc
suffix:semicolon
DECL|struct|tree_desc_s
r_typedef
r_struct
id|tree_desc_s
(brace
DECL|member|dyn_tree
id|ct_data
op_star
id|dyn_tree
suffix:semicolon
multiline_comment|/* the dynamic tree */
DECL|member|max_code
r_int
id|max_code
suffix:semicolon
multiline_comment|/* largest code with non zero frequency */
DECL|member|stat_desc
id|static_tree_desc
op_star
id|stat_desc
suffix:semicolon
multiline_comment|/* the corresponding static tree */
DECL|typedef|tree_desc
)brace
id|FAR
id|tree_desc
suffix:semicolon
DECL|typedef|Pos
r_typedef
id|ush
id|Pos
suffix:semicolon
DECL|typedef|Posf
r_typedef
id|Pos
id|FAR
id|Posf
suffix:semicolon
DECL|typedef|IPos
r_typedef
r_int
id|IPos
suffix:semicolon
multiline_comment|/* A Pos is an index in the character window. We use short instead of int to&n; * save space in the various tables. IPos is used only for parameter passing.&n; */
DECL|struct|deflate_state
r_typedef
r_struct
id|deflate_state
(brace
DECL|member|strm
id|z_streamp
id|strm
suffix:semicolon
multiline_comment|/* pointer back to this zlib stream */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* as the name implies */
DECL|member|pending_buf
id|Bytef
op_star
id|pending_buf
suffix:semicolon
multiline_comment|/* output still pending */
DECL|member|pending_buf_size
id|ulg
id|pending_buf_size
suffix:semicolon
multiline_comment|/* size of pending_buf */
DECL|member|pending_out
id|Bytef
op_star
id|pending_out
suffix:semicolon
multiline_comment|/* next pending byte to output to the stream */
DECL|member|pending
r_int
id|pending
suffix:semicolon
multiline_comment|/* nb of bytes in the pending buffer */
DECL|member|noheader
r_int
id|noheader
suffix:semicolon
multiline_comment|/* suppress zlib header and adler32 */
DECL|member|data_type
id|Byte
id|data_type
suffix:semicolon
multiline_comment|/* UNKNOWN, BINARY or ASCII */
DECL|member|method
id|Byte
id|method
suffix:semicolon
multiline_comment|/* STORED (for zip only) or DEFLATED */
DECL|member|last_flush
r_int
id|last_flush
suffix:semicolon
multiline_comment|/* value of flush param for previous deflate call */
multiline_comment|/* used by deflate.c: */
DECL|member|w_size
id|uInt
id|w_size
suffix:semicolon
multiline_comment|/* LZ77 window size (32K by default) */
DECL|member|w_bits
id|uInt
id|w_bits
suffix:semicolon
multiline_comment|/* log2(w_size)  (8..16) */
DECL|member|w_mask
id|uInt
id|w_mask
suffix:semicolon
multiline_comment|/* w_size - 1 */
DECL|member|window
id|Bytef
op_star
id|window
suffix:semicolon
multiline_comment|/* Sliding window. Input bytes are read into the second half of the window,&n;     * and move to the first half later to keep a dictionary of at least wSize&n;     * bytes. With this organization, matches are limited to a distance of&n;     * wSize-MAX_MATCH bytes, but this ensures that IO is always&n;     * performed with a length multiple of the block size. Also, it limits&n;     * the window size to 64K, which is quite useful on MSDOS.&n;     * To do: use the user input buffer as sliding window.&n;     */
DECL|member|window_size
id|ulg
id|window_size
suffix:semicolon
multiline_comment|/* Actual size of window: 2*wSize, except when the user input buffer&n;     * is directly used as sliding window.&n;     */
DECL|member|prev
id|Posf
op_star
id|prev
suffix:semicolon
multiline_comment|/* Link to older string with same hash index. To limit the size of this&n;     * array to 64K, this link is maintained only for the last 32K strings.&n;     * An index in this array is thus a window index modulo 32K.&n;     */
DECL|member|head
id|Posf
op_star
id|head
suffix:semicolon
multiline_comment|/* Heads of the hash chains or NIL. */
DECL|member|ins_h
id|uInt
id|ins_h
suffix:semicolon
multiline_comment|/* hash index of string to be inserted */
DECL|member|hash_size
id|uInt
id|hash_size
suffix:semicolon
multiline_comment|/* number of elements in hash table */
DECL|member|hash_bits
id|uInt
id|hash_bits
suffix:semicolon
multiline_comment|/* log2(hash_size) */
DECL|member|hash_mask
id|uInt
id|hash_mask
suffix:semicolon
multiline_comment|/* hash_size-1 */
DECL|member|hash_shift
id|uInt
id|hash_shift
suffix:semicolon
multiline_comment|/* Number of bits by which ins_h must be shifted at each input&n;     * step. It must be such that after MIN_MATCH steps, the oldest&n;     * byte no longer takes part in the hash key, that is:&n;     *   hash_shift * MIN_MATCH &gt;= hash_bits&n;     */
DECL|member|block_start
r_int
id|block_start
suffix:semicolon
multiline_comment|/* Window position at the beginning of the current output block. Gets&n;     * negative when the window is moved backwards.&n;     */
DECL|member|match_length
id|uInt
id|match_length
suffix:semicolon
multiline_comment|/* length of best match */
DECL|member|prev_match
id|IPos
id|prev_match
suffix:semicolon
multiline_comment|/* previous match */
DECL|member|match_available
r_int
id|match_available
suffix:semicolon
multiline_comment|/* set if previous match exists */
DECL|member|strstart
id|uInt
id|strstart
suffix:semicolon
multiline_comment|/* start of string to insert */
DECL|member|match_start
id|uInt
id|match_start
suffix:semicolon
multiline_comment|/* start of matching string */
DECL|member|lookahead
id|uInt
id|lookahead
suffix:semicolon
multiline_comment|/* number of valid bytes ahead in window */
DECL|member|prev_length
id|uInt
id|prev_length
suffix:semicolon
multiline_comment|/* Length of the best match at previous step. Matches not greater than this&n;     * are discarded. This is used in the lazy match evaluation.&n;     */
DECL|member|max_chain_length
id|uInt
id|max_chain_length
suffix:semicolon
multiline_comment|/* To speed up deflation, hash chains are never searched beyond this&n;     * length.  A higher limit improves compression ratio but degrades the&n;     * speed.&n;     */
DECL|member|max_lazy_match
id|uInt
id|max_lazy_match
suffix:semicolon
multiline_comment|/* Attempt to find a better match only when the current match is strictly&n;     * smaller than this value. This mechanism is used only for compression&n;     * levels &gt;= 4.&n;     */
DECL|macro|max_insert_length
macro_line|#   define max_insert_length  max_lazy_match
multiline_comment|/* Insert new strings in the hash table only if the match length is not&n;     * greater than this length. This saves time but degrades compression.&n;     * max_insert_length is used only for compression levels &lt;= 3.&n;     */
DECL|member|level
r_int
id|level
suffix:semicolon
multiline_comment|/* compression level (1..9) */
DECL|member|strategy
r_int
id|strategy
suffix:semicolon
multiline_comment|/* favor or force Huffman coding*/
DECL|member|good_match
id|uInt
id|good_match
suffix:semicolon
multiline_comment|/* Use a faster search when the previous match is longer than this */
DECL|member|nice_match
r_int
id|nice_match
suffix:semicolon
multiline_comment|/* Stop searching when current match exceeds this */
multiline_comment|/* used by trees.c: */
multiline_comment|/* Didn&squot;t use ct_data typedef below to supress compiler warning */
DECL|member|dyn_ltree
r_struct
id|ct_data_s
id|dyn_ltree
(braket
id|HEAP_SIZE
)braket
suffix:semicolon
multiline_comment|/* literal and length tree */
DECL|member|dyn_dtree
r_struct
id|ct_data_s
id|dyn_dtree
(braket
l_int|2
op_star
id|D_CODES
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* distance tree */
DECL|member|bl_tree
r_struct
id|ct_data_s
id|bl_tree
(braket
l_int|2
op_star
id|BL_CODES
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Huffman tree for bit lengths */
DECL|member|l_desc
r_struct
id|tree_desc_s
id|l_desc
suffix:semicolon
multiline_comment|/* desc. for literal tree */
DECL|member|d_desc
r_struct
id|tree_desc_s
id|d_desc
suffix:semicolon
multiline_comment|/* desc. for distance tree */
DECL|member|bl_desc
r_struct
id|tree_desc_s
id|bl_desc
suffix:semicolon
multiline_comment|/* desc. for bit length tree */
DECL|member|bl_count
id|ush
id|bl_count
(braket
id|MAX_BITS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* number of codes at each bit length for an optimal tree */
DECL|member|heap
r_int
id|heap
(braket
l_int|2
op_star
id|L_CODES
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* heap used to build the Huffman trees */
DECL|member|heap_len
r_int
id|heap_len
suffix:semicolon
multiline_comment|/* number of elements in the heap */
DECL|member|heap_max
r_int
id|heap_max
suffix:semicolon
multiline_comment|/* element of largest frequency */
multiline_comment|/* The sons of heap[n] are heap[2*n] and heap[2*n+1]. heap[0] is not used.&n;     * The same heap array is used to build all trees.&n;     */
DECL|member|depth
id|uch
id|depth
(braket
l_int|2
op_star
id|L_CODES
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Depth of each subtree used as tie breaker for trees of equal frequency&n;     */
DECL|member|l_buf
id|uchf
op_star
id|l_buf
suffix:semicolon
multiline_comment|/* buffer for literals or lengths */
DECL|member|lit_bufsize
id|uInt
id|lit_bufsize
suffix:semicolon
multiline_comment|/* Size of match buffer for literals/lengths.  There are 4 reasons for&n;     * limiting lit_bufsize to 64K:&n;     *   - frequencies can be kept in 16 bit counters&n;     *   - if compression is not successful for the first block, all input&n;     *     data is still in the window so we can still emit a stored block even&n;     *     when input comes from standard input.  (This can also be done for&n;     *     all blocks if lit_bufsize is not greater than 32K.)&n;     *   - if compression is not successful for a file smaller than 64K, we can&n;     *     even emit a stored file instead of a stored block (saving 5 bytes).&n;     *     This is applicable only for zip (not gzip or zlib).&n;     *   - creating new Huffman trees less frequently may not provide fast&n;     *     adaptation to changes in the input data statistics. (Take for&n;     *     example a binary file with poorly compressible code followed by&n;     *     a highly compressible string table.) Smaller buffer sizes give&n;     *     fast adaptation but have of course the overhead of transmitting&n;     *     trees more frequently.&n;     *   - I can&squot;t count above 4&n;     */
DECL|member|last_lit
id|uInt
id|last_lit
suffix:semicolon
multiline_comment|/* running index in l_buf */
DECL|member|d_buf
id|ushf
op_star
id|d_buf
suffix:semicolon
multiline_comment|/* Buffer for distances. To simplify the code, d_buf and l_buf have&n;     * the same number of elements. To use different lengths, an extra flag&n;     * array would be necessary.&n;     */
DECL|member|opt_len
id|ulg
id|opt_len
suffix:semicolon
multiline_comment|/* bit length of current block with optimal trees */
DECL|member|static_len
id|ulg
id|static_len
suffix:semicolon
multiline_comment|/* bit length of current block with static trees */
DECL|member|compressed_len
id|ulg
id|compressed_len
suffix:semicolon
multiline_comment|/* total bit length of compressed file */
DECL|member|matches
id|uInt
id|matches
suffix:semicolon
multiline_comment|/* number of string matches in current block */
DECL|member|last_eob_len
r_int
id|last_eob_len
suffix:semicolon
multiline_comment|/* bit length of EOB code for last block */
macro_line|#ifdef DEBUG_ZLIB
DECL|member|bits_sent
id|ulg
id|bits_sent
suffix:semicolon
multiline_comment|/* bit length of the compressed data */
macro_line|#endif
DECL|member|bi_buf
id|ush
id|bi_buf
suffix:semicolon
multiline_comment|/* Output buffer. bits are inserted starting at the bottom (least&n;     * significant bits).&n;     */
DECL|member|bi_valid
r_int
id|bi_valid
suffix:semicolon
multiline_comment|/* Number of valid bits in bi_buf.  All bits above the last valid bit&n;     * are always zero.&n;     */
DECL|typedef|deflate_state
)brace
id|FAR
id|deflate_state
suffix:semicolon
DECL|struct|deflate_workspace
r_typedef
r_struct
id|deflate_workspace
(brace
multiline_comment|/* State memory for the deflator */
DECL|member|deflate_memory
id|deflate_state
id|deflate_memory
suffix:semicolon
DECL|member|window_memory
id|Byte
id|window_memory
(braket
l_int|2
op_star
(paren
l_int|1
op_lshift
id|MAX_WBITS
)paren
)braket
suffix:semicolon
DECL|member|prev_memory
id|Pos
id|prev_memory
(braket
l_int|1
op_lshift
id|MAX_WBITS
)braket
suffix:semicolon
DECL|member|head_memory
id|Pos
id|head_memory
(braket
l_int|1
op_lshift
(paren
id|MAX_MEM_LEVEL
op_plus
l_int|7
)paren
)braket
suffix:semicolon
DECL|member|overlay_memory
r_char
id|overlay_memory
(braket
(paren
l_int|1
op_lshift
(paren
id|MAX_MEM_LEVEL
op_plus
l_int|6
)paren
)paren
op_star
(paren
r_sizeof
(paren
id|ush
)paren
op_plus
l_int|2
)paren
)braket
suffix:semicolon
DECL|typedef|deflate_workspace
)brace
id|deflate_workspace
suffix:semicolon
multiline_comment|/* Output a byte on the stream.&n; * IN assertion: there is enough room in pending_buf.&n; */
DECL|macro|put_byte
mdefine_line|#define put_byte(s, c) {s-&gt;pending_buf[s-&gt;pending++] = (c);}
DECL|macro|MIN_LOOKAHEAD
mdefine_line|#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
multiline_comment|/* Minimum amount of lookahead, except at the end of the input file.&n; * See deflate.c for comments about the MIN_MATCH+1.&n; */
DECL|macro|MAX_DIST
mdefine_line|#define MAX_DIST(s)  ((s)-&gt;w_size-MIN_LOOKAHEAD)
multiline_comment|/* In order to simplify the code, particularly on 16 bit machines, match&n; * distances are limited to MAX_DIST instead of WSIZE.&n; */
multiline_comment|/* in trees.c */
r_void
id|zlib_tr_init
id|OF
c_func
(paren
(paren
id|deflate_state
op_star
id|s
)paren
)paren
suffix:semicolon
r_int
id|zlib_tr_tally
id|OF
c_func
(paren
(paren
id|deflate_state
op_star
id|s
comma
r_int
id|dist
comma
r_int
id|lc
)paren
)paren
suffix:semicolon
id|ulg
id|zlib_tr_flush_block
id|OF
c_func
(paren
(paren
id|deflate_state
op_star
id|s
comma
id|charf
op_star
id|buf
comma
id|ulg
id|stored_len
comma
r_int
id|eof
)paren
)paren
suffix:semicolon
r_void
id|zlib_tr_align
id|OF
c_func
(paren
(paren
id|deflate_state
op_star
id|s
)paren
)paren
suffix:semicolon
r_void
id|zlib_tr_stored_block
id|OF
c_func
(paren
(paren
id|deflate_state
op_star
id|s
comma
id|charf
op_star
id|buf
comma
id|ulg
id|stored_len
comma
r_int
id|eof
)paren
)paren
suffix:semicolon
r_void
id|zlib_tr_stored_type_only
id|OF
c_func
(paren
(paren
id|deflate_state
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* ===========================================================================&n; * Output a short LSB first on the stream.&n; * IN assertion: there is enough room in pendingBuf.&n; */
DECL|macro|put_short
mdefine_line|#define put_short(s, w) { &bslash;&n;    put_byte(s, (uch)((w) &amp; 0xff)); &bslash;&n;    put_byte(s, (uch)((ush)(w) &gt;&gt; 8)); &bslash;&n;}
multiline_comment|/* ===========================================================================&n; * Reverse the first len bits of a code, using straightforward code (a faster&n; * method would use a table)&n; * IN assertion: 1 &lt;= len &lt;= 15&n; */
DECL|function|bi_reverse
r_static
r_inline
r_int
id|bi_reverse
c_func
(paren
r_int
id|code
comma
multiline_comment|/* the value to invert */
r_int
id|len
)paren
multiline_comment|/* its bit length */
(brace
r_register
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|res
op_or_assign
id|code
op_amp
l_int|1
suffix:semicolon
id|code
op_rshift_assign
l_int|1
comma
id|res
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|len
OG
l_int|0
)paren
suffix:semicolon
r_return
id|res
op_rshift
l_int|1
suffix:semicolon
)brace
multiline_comment|/* ===========================================================================&n; * Flush the bit buffer, keeping at most 7 bits in it.&n; */
DECL|function|bi_flush
r_static
r_inline
r_void
id|bi_flush
c_func
(paren
id|deflate_state
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;bi_valid
op_eq
l_int|16
)paren
(brace
id|put_short
c_func
(paren
id|s
comma
id|s-&gt;bi_buf
)paren
suffix:semicolon
id|s-&gt;bi_buf
op_assign
l_int|0
suffix:semicolon
id|s-&gt;bi_valid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;bi_valid
op_ge
l_int|8
)paren
(brace
id|put_byte
c_func
(paren
id|s
comma
(paren
id|Byte
)paren
id|s-&gt;bi_buf
)paren
suffix:semicolon
id|s-&gt;bi_buf
op_rshift_assign
l_int|8
suffix:semicolon
id|s-&gt;bi_valid
op_sub_assign
l_int|8
suffix:semicolon
)brace
)brace
multiline_comment|/* ===========================================================================&n; * Flush the bit buffer and align the output on a byte boundary&n; */
DECL|function|bi_windup
r_static
r_inline
r_void
id|bi_windup
c_func
(paren
id|deflate_state
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;bi_valid
OG
l_int|8
)paren
(brace
id|put_short
c_func
(paren
id|s
comma
id|s-&gt;bi_buf
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;bi_valid
OG
l_int|0
)paren
(brace
id|put_byte
c_func
(paren
id|s
comma
(paren
id|Byte
)paren
id|s-&gt;bi_buf
)paren
suffix:semicolon
)brace
id|s-&gt;bi_buf
op_assign
l_int|0
suffix:semicolon
id|s-&gt;bi_valid
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG_ZLIB
id|s-&gt;bits_sent
op_assign
(paren
id|s-&gt;bits_sent
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
suffix:semicolon
macro_line|#endif
)brace
eof
