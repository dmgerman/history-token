multiline_comment|/*&n; * $Source: /homes/cvs/ftape-stacked/ftape/compressor/lzrw3.c,v $&n; * $Revision: 1.1 $&n; * $Date: 1997/10/05 19:12:29 $&n; *&n; * Implementation of Ross Williams lzrw3 algorithm. Adaption for zftape.&n; *&n; */
macro_line|#include &quot;../compressor/lzrw3.h&quot;       /* Defines single exported function &quot;compress&quot;.   */
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/*                                    LZRW3.C                                 */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/* Author  : Ross Williams.                                                   */
multiline_comment|/* Date    : 30-Jun-1991.                                                     */
multiline_comment|/* Release : 1.                                                               */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/* This file contains an implementation of the LZRW3 data compression         */
multiline_comment|/* algorithm in C.                                                            */
multiline_comment|/*                                                                            */
multiline_comment|/* The algorithm is a general purpose compression algorithm that runs fast    */
multiline_comment|/* and gives reasonable compression. The algorithm is a member of the Lempel  */
multiline_comment|/* Ziv family of algorithms and bases its compression on the presence in the  */
multiline_comment|/* data of repeated substrings.                                               */
multiline_comment|/*                                                                            */
multiline_comment|/* This algorithm is unpatented and the code is public domain. As the         */
multiline_comment|/* algorithm is based on the LZ77 class of algorithms, it is unlikely to be   */
multiline_comment|/* the subject of a patent challenge.                                         */
multiline_comment|/*                                                                            */
multiline_comment|/* Unlike the LZRW1 and LZRW1-A algorithms, the LZRW3 algorithm is            */
multiline_comment|/* deterministic and is guaranteed to yield the same compressed               */
multiline_comment|/* representation for a given file each time it is run.                       */
multiline_comment|/*                                                                            */
multiline_comment|/* The LZRW3 algorithm was originally designed and implemented                */
multiline_comment|/* by Ross Williams on 31-Dec-1990.                                           */
multiline_comment|/*                                                                            */
multiline_comment|/* Here are the results of applying this code, compiled under THINK C 4.0     */
multiline_comment|/* and running on a Mac-SE (8MHz 68000), to the standard calgary corpus.      */
multiline_comment|/*                                                                            */
multiline_comment|/*    +----------------------------------------------------------------+      */
multiline_comment|/*    | DATA COMPRESSION TEST                                          |      */
multiline_comment|/*    | =====================                                          |      */
multiline_comment|/*    | Time of run     : Sun 30-Jun-1991 09:31PM                      |      */
multiline_comment|/*    | Timing accuracy : One part in 100                              |      */
multiline_comment|/*    | Context length  : 262144 bytes (= 256.0000K)                   |      */
multiline_comment|/*    | Test suite      : Calgary Corpus Suite                         |      */
multiline_comment|/*    | Files in suite  : 14                                           |      */
multiline_comment|/*    | Algorithm       : LZRW3                                        |      */
multiline_comment|/*    | Note: All averages are calculated from the un-rounded values.  |      */
multiline_comment|/*    +----------------------------------------------------------------+      */
multiline_comment|/*    | File Name   Length  CxB  ComLen  %Remn  Bits  Com K/s  Dec K/s |      */
multiline_comment|/*    | ----------  ------  ---  ------  -----  ----  -------  ------- |      */
multiline_comment|/*    | rpus:Bib.D  111261    1   55033   49.5  3.96    19.46    32.27 |      */
multiline_comment|/*    | us:Book1.D  768771    3  467962   60.9  4.87    17.03    31.07 |      */
multiline_comment|/*    | us:Book2.D  610856    3  317102   51.9  4.15    19.39    34.15 |      */
multiline_comment|/*    | rpus:Geo.D  102400    1   82424   80.5  6.44    11.65    18.18 |      */
multiline_comment|/*    | pus:News.D  377109    2  205670   54.5  4.36    17.14    27.47 |      */
multiline_comment|/*    | pus:Obj1.D   21504    1   13027   60.6  4.85    13.40    18.95 |      */
multiline_comment|/*    | pus:Obj2.D  246814    1  116286   47.1  3.77    19.31    30.10 |      */
multiline_comment|/*    | s:Paper1.D   53161    1   27522   51.8  4.14    18.60    31.15 |      */
multiline_comment|/*    | s:Paper2.D   82199    1   45160   54.9  4.40    18.45    32.84 |      */
multiline_comment|/*    | rpus:Pic.D  513216    2  122388   23.8  1.91    35.29    51.05 |      */
multiline_comment|/*    | us:Progc.D   39611    1   19669   49.7  3.97    18.87    30.64 |      */
multiline_comment|/*    | us:Progl.D   71646    1   28247   39.4  3.15    24.34    40.66 |      */
multiline_comment|/*    | us:Progp.D   49379    1   19377   39.2  3.14    23.91    39.23 |      */
multiline_comment|/*    | us:Trans.D   93695    1   33481   35.7  2.86    25.48    40.37 |      */
multiline_comment|/*    +----------------------------------------------------------------+      */
multiline_comment|/*    | Average     224401    1  110953   50.0  4.00    20.17    32.72 |      */
multiline_comment|/*    +----------------------------------------------------------------+      */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/******************************************************************************/
multiline_comment|/* The following structure is returned by the &quot;compress&quot; function below when  */
multiline_comment|/* the user asks the function to return identifying information.              */
multiline_comment|/* The most important field in the record is the working memory field which   */
multiline_comment|/* tells the calling program how much working memory should be passed to      */
multiline_comment|/* &quot;compress&quot; when it is called to perform a compression or decompression.    */
multiline_comment|/* LZRW3 uses the same amount of memory during compression and decompression. */
multiline_comment|/* For more information on this structure see &quot;compress.h&quot;.                   */
DECL|macro|U
mdefine_line|#define U(X)            ((ULONG) X)
DECL|macro|SIZE_P_BYTE
mdefine_line|#define SIZE_P_BYTE     (U(sizeof(UBYTE *)))
DECL|macro|SIZE_WORD
mdefine_line|#define SIZE_WORD       (U(sizeof(UWORD  )))
DECL|macro|ALIGNMENT_FUDGE
mdefine_line|#define ALIGNMENT_FUDGE (U(16))
DECL|macro|MEM_REQ
mdefine_line|#define MEM_REQ ( U(4096)*(SIZE_P_BYTE) + ALIGNMENT_FUDGE )
DECL|variable|identity
r_static
r_struct
id|compress_identity
id|identity
op_assign
(brace
id|U
c_func
(paren
l_int|0x032DDEA8
)paren
comma
multiline_comment|/* Algorithm identification number. */
id|MEM_REQ
comma
multiline_comment|/* Working memory (bytes) required. */
l_string|&quot;LZRW3&quot;
comma
multiline_comment|/* Name of algorithm.               */
l_string|&quot;1.0&quot;
comma
multiline_comment|/* Version number of algorithm.     */
l_string|&quot;31-Dec-1990&quot;
comma
multiline_comment|/* Date of algorithm.               */
l_string|&quot;Public Domain&quot;
comma
multiline_comment|/* Copyright notice.                */
l_string|&quot;Ross N. Williams&quot;
comma
multiline_comment|/* Author of algorithm.             */
l_string|&quot;Renaissance Software&quot;
comma
multiline_comment|/* Affiliation of author.           */
l_string|&quot;Public Domain&quot;
multiline_comment|/* Vendor of algorithm.             */
)brace
suffix:semicolon
id|LOCAL
r_void
id|compress_compress
(paren
id|UBYTE
op_star
comma
id|UBYTE
op_star
comma
id|ULONG
comma
id|UBYTE
op_star
comma
id|LONG
op_star
)paren
suffix:semicolon
id|LOCAL
r_void
id|compress_decompress
c_func
(paren
id|UBYTE
op_star
comma
id|UBYTE
op_star
comma
id|LONG
comma
id|UBYTE
op_star
comma
id|ULONG
op_star
)paren
suffix:semicolon
multiline_comment|/******************************************************************************/
multiline_comment|/* This function is the only function exported by this module.                */
multiline_comment|/* Depending on its first parameter, the function can be requested to         */
multiline_comment|/* compress a block of memory, decompress a block of memory, or to identify   */
multiline_comment|/* itself. For more information, see the specification file &quot;compress.h&quot;.     */
DECL|function|lzrw3_compress
id|EXPORT
r_void
id|lzrw3_compress
c_func
(paren
id|action
comma
id|wrk_mem
comma
id|src_adr
comma
id|src_len
comma
id|dst_adr
comma
id|p_dst_len
)paren
id|UWORD
id|action
suffix:semicolon
multiline_comment|/* Action to be performed.                             */
id|UBYTE
op_star
id|wrk_mem
suffix:semicolon
multiline_comment|/* Address of working memory we can use.               */
id|UBYTE
op_star
id|src_adr
suffix:semicolon
multiline_comment|/* Address of input data.                              */
id|LONG
id|src_len
suffix:semicolon
multiline_comment|/* Length  of input data.                              */
id|UBYTE
op_star
id|dst_adr
suffix:semicolon
multiline_comment|/* Address to put output data.                         */
r_void
op_star
id|p_dst_len
suffix:semicolon
multiline_comment|/* Address of longword for length of output data.      */
(brace
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|COMPRESS_ACTION_IDENTITY
suffix:colon
op_star
(paren
(paren
r_struct
id|compress_identity
op_star
op_star
)paren
id|p_dst_len
)paren
op_assign
op_amp
id|identity
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMPRESS_ACTION_COMPRESS
suffix:colon
id|compress_compress
c_func
(paren
id|wrk_mem
comma
id|src_adr
comma
id|src_len
comma
id|dst_adr
comma
(paren
id|LONG
op_star
)paren
id|p_dst_len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMPRESS_ACTION_DECOMPRESS
suffix:colon
id|compress_decompress
c_func
(paren
id|wrk_mem
comma
id|src_adr
comma
id|src_len
comma
id|dst_adr
comma
(paren
id|LONG
op_star
)paren
id|p_dst_len
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/* BRIEF DESCRIPTION OF THE LZRW3 ALGORITHM                                   */
multiline_comment|/* ========================================                                   */
multiline_comment|/* The LZRW3 algorithm is identical to the LZRW1-A algorithm except that      */
multiline_comment|/* instead of transmitting history offsets, it transmits hash table indexes.  */
multiline_comment|/* In order to decode the indexes, the decompressor must maintain an          */
multiline_comment|/* identical hash table. Copy items are straightforward:when the decompressor */
multiline_comment|/* receives a copy item, it simply looks up the hash table to translate the   */
multiline_comment|/* index into a pointer into the data already decompressed. To update the     */
multiline_comment|/* hash table, it replaces the same table entry with a pointer to the start   */
multiline_comment|/* of the newly decoded phrase. The tricky part is with literal items, for at */
multiline_comment|/* the time that the decompressor receives a literal item the decompressor    */
multiline_comment|/* does not have the three bytes in the Ziv (that the compressor has) to      */
multiline_comment|/* perform the three-byte hash. To solve this problem, in LZRW3, both the     */
multiline_comment|/* compressor and decompressor are wired up so that they &quot;buffer&quot; these       */
multiline_comment|/* literals and update their hash tables only when three bytes are available. */
multiline_comment|/* This makes the maximum buffering 2 bytes.                                  */
multiline_comment|/*                                                                            */
multiline_comment|/* Replacement of offsets by hash table indexes yields a few percent extra    */
multiline_comment|/* compression at the cost of some speed. LZRW3 is slower than LZRW1, LZRW1-A */
multiline_comment|/* and LZRW2, but yields better compression.                                  */
multiline_comment|/*                                                                            */
multiline_comment|/* Extra compression could be obtained by using a hash table of depth two.    */
multiline_comment|/* However, increasing the depth above one incurs a significant decrease in   */
multiline_comment|/* compression speed which was not considered worthwhile. Another reason for  */
multiline_comment|/* keeping the depth down to one was to allow easy comparison with the        */
multiline_comment|/* LZRW1-A and LZRW2 algorithms so as to demonstrate the exact effect of the  */
multiline_comment|/* use of direct hash indexes.                                                */
multiline_comment|/*                                                                            */
multiline_comment|/*                                  +---+                                     */
multiline_comment|/*                                  |___|4095                                 */
multiline_comment|/*                                  |___|                                     */
multiline_comment|/*              +---------------------*_|&lt;---+   /----+---&bslash;                   */
multiline_comment|/*              |                   |___|    +---|Hash    |                   */
multiline_comment|/*              |                   |___|        |Function|                   */
multiline_comment|/*              |                   |___|        &bslash;--------/                   */
multiline_comment|/*              |                   |___|0            ^                       */
multiline_comment|/*              |                   +---+             |                       */
multiline_comment|/*              |                   Hash        +-----+                       */
multiline_comment|/*              |                   Table       |                             */
multiline_comment|/*              |                              ---                            */
multiline_comment|/*              v                              ^^^                            */
multiline_comment|/*      +-------------------------------------|----------------+              */
multiline_comment|/*      ||||||||||||||||||||||||||||||||||||||||||||||||||||||||              */
multiline_comment|/*      +-------------------------------------|----------------+              */
multiline_comment|/*      |                                     |1......18|      |              */
multiline_comment|/*      |&lt;------- Lempel=History ------------&gt;|&lt;--Ziv--&gt;|      |              */
multiline_comment|/*      |     (=bytes already processed)      |&lt;-Still to go--&gt;|              */
multiline_comment|/*      |&lt;-------------------- INPUT BLOCK -------------------&gt;|              */
multiline_comment|/*                                                                            */
multiline_comment|/* The diagram above for LZRW3 looks almost identical to the diagram for      */
multiline_comment|/* LZRW1. The difference is that in LZRW3, the compressor transmits hash      */
multiline_comment|/* table indices instead of Lempel offsets. For this to work, the             */
multiline_comment|/* decompressor must maintain a hash table as well as the compressor and both */
multiline_comment|/* compressor and decompressor must &quot;buffer&quot; literals, as the decompressor    */
multiline_comment|/* cannot hash phrases commencing with a literal until another two bytes have */
multiline_comment|/* arrived.                                                                   */
multiline_comment|/*                                                                            */
multiline_comment|/*  LZRW3 Algorithm Execution Summary                                         */
multiline_comment|/*  ---------------------------------                                         */
multiline_comment|/*  1. Hash the first three bytes of the Ziv to yield a hash table index h.   */
multiline_comment|/*  2. Look up the hash table yielding history pointer p.                     */
multiline_comment|/*  3. Match where p points with the Ziv. If there is a match of three or     */
multiline_comment|/*     more bytes, code those bytes (in the Ziv) as a copy item, otherwise    */
multiline_comment|/*     code the next byte in the Ziv as a literal item.                       */
multiline_comment|/*  4. Update the hash table as possible subject to the constraint that only  */
multiline_comment|/*     phrases commencing three bytes back from the Ziv can be hashed and     */
multiline_comment|/*     entered into the hash table. (This enables the decompressor to keep    */
multiline_comment|/*     pace). See the description and code for more details.                  */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/*                     DEFINITION OF COMPRESSED FILE FORMAT                   */
multiline_comment|/*                     ====================================                   */
multiline_comment|/*  * A compressed file consists of a COPY FLAG followed by a REMAINDER.      */
multiline_comment|/*  * The copy flag CF uses up four bytes with the first byte being the       */
multiline_comment|/*    least significant.                                                      */
multiline_comment|/*  * If CF=1, then the compressed file represents the remainder of the file  */
multiline_comment|/*    exactly. Otherwise CF=0 and the remainder of the file consists of zero  */
multiline_comment|/*    or more GROUPS, each of which represents one or more bytes.             */
multiline_comment|/*  * Each group consists of two bytes of CONTROL information followed by     */
multiline_comment|/*    sixteen ITEMs except for the last group which can contain from one      */
multiline_comment|/*    to sixteen items.                                                       */
multiline_comment|/*  * An item can be either a LITERAL item or a COPY item.                    */
multiline_comment|/*  * Each item corresponds to a bit in the control bytes.                    */
multiline_comment|/*  * The first control byte corresponds to the first 8 items in the group    */
multiline_comment|/*    with bit 0 corresponding to the first item in the group and bit 7 to    */
multiline_comment|/*    the eighth item in the group.                                           */
multiline_comment|/*  * The second control byte corresponds to the second 8 items in the group  */
multiline_comment|/*    with bit 0 corresponding to the ninth item in the group and bit 7 to    */
multiline_comment|/*    the sixteenth item in the group.                                        */
multiline_comment|/*  * A zero bit in a control word means that the corresponding item is a     */
multiline_comment|/*    literal item. A one bit corresponds to a copy item.                     */
multiline_comment|/*  * A literal item consists of a single byte which represents itself.       */
multiline_comment|/*  * A copy item consists of two bytes that represent from 3 to 18 bytes.    */
multiline_comment|/*  * The first  byte in a copy item will be denoted C1.                      */
multiline_comment|/*  * The second byte in a copy item will be denoted C2.                      */
multiline_comment|/*  * Bits will be selected using square brackets.                            */
multiline_comment|/*    For example: C1[0..3] is the low nibble of the first control byte.      */
multiline_comment|/*    of copy item C1.                                                        */
multiline_comment|/*  * The LENGTH of a copy item is defined to be C1[0..3]+3 which is a number */
multiline_comment|/*    in the range [3,18].                                                    */
multiline_comment|/*  * The INDEX of a copy item is defined to be C1[4..7]*256+C2[0..8] which   */
multiline_comment|/*    is a number in the range [0,4095].                                      */
multiline_comment|/*  * A copy item represents the sequence of bytes                            */
multiline_comment|/*       text[POS-OFFSET..POS-OFFSET+LENGTH-1] where                          */
multiline_comment|/*          text   is the entire text of the uncompressed string.             */
multiline_comment|/*          POS    is the index in the text of the character following the    */
multiline_comment|/*                   string represented by all the items preceeding the item  */
multiline_comment|/*                   being defined.                                           */
multiline_comment|/*          OFFSET is obtained from INDEX by looking up the hash table.       */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/* The following #define defines the length of the copy flag that appears at  */
multiline_comment|/* the start of the compressed file. The value of four bytes was chosen       */
multiline_comment|/* because the fast_copy routine on my Macintosh runs faster if the source    */
multiline_comment|/* and destination blocks are relatively longword aligned.                    */
multiline_comment|/* The actual flag data appears in the first byte. The rest are zeroed so as  */
multiline_comment|/* to normalize the compressed representation (i.e. not non-deterministic).   */
DECL|macro|FLAG_BYTES
mdefine_line|#define FLAG_BYTES 4
multiline_comment|/* The following #defines define the meaning of the values of the copy        */
multiline_comment|/* flag at the start of the compressed file.                                  */
DECL|macro|FLAG_COMPRESS
mdefine_line|#define FLAG_COMPRESS 0     /* Signals that output was result of compression. */
DECL|macro|FLAG_COPY
mdefine_line|#define FLAG_COPY     1     /* Signals that output was simply copied over.    */
multiline_comment|/* The 68000 microprocessor (on which this algorithm was originally developed */
multiline_comment|/* is fussy about non-aligned arrays of words. To avoid these problems the    */
multiline_comment|/* following macro can be used to &quot;waste&quot; from 0 to 3 bytes so as to align    */
multiline_comment|/* the argument pointer.                                                      */
DECL|macro|ULONG_ALIGN_UP
mdefine_line|#define ULONG_ALIGN_UP(X) ((((ULONG)X)+sizeof(ULONG)-1)&amp;~(sizeof(ULONG)-1))
multiline_comment|/* The following constant defines the maximum length of an uncompressed item. */
multiline_comment|/* This definition must not be changed; its value is hardwired into the code. */
multiline_comment|/* The longest number of bytes that can be spanned by a single item is 18     */
multiline_comment|/* for the longest copy item.                                                 */
DECL|macro|MAX_RAW_ITEM
mdefine_line|#define MAX_RAW_ITEM (18)
multiline_comment|/* The following constant defines the maximum length of an uncompressed group.*/
multiline_comment|/* This definition must not be changed; its value is hardwired into the code. */
multiline_comment|/* A group contains at most 16 items which explains this definition.          */
DECL|macro|MAX_RAW_GROUP
mdefine_line|#define MAX_RAW_GROUP (16*MAX_RAW_ITEM)
multiline_comment|/* The following constant defines the maximum length of a compressed group.   */
multiline_comment|/* This definition must not be changed; its value is hardwired into the code. */
multiline_comment|/* A compressed group consists of two control bytes followed by up to 16      */
multiline_comment|/* compressed items each of which can have a maximum length of two bytes.     */
DECL|macro|MAX_CMP_GROUP
mdefine_line|#define MAX_CMP_GROUP (2+16*2)
multiline_comment|/* The following constant defines the number of entries in the hash table.    */
multiline_comment|/* This definition must not be changed; its value is hardwired into the code. */
DECL|macro|HASH_TABLE_LENGTH
mdefine_line|#define HASH_TABLE_LENGTH (4096)
multiline_comment|/* LZRW3, unlike LZRW1(-A), must initialize its hash table so as to enable    */
multiline_comment|/* the compressor and decompressor to stay in step maintaining identical hash */
multiline_comment|/* tables. In an early version of the algorithm, the tables were simply       */
multiline_comment|/* initialized to zero and a check for zero was included just before the      */
multiline_comment|/* matching code. However, this test costs time. A better solution is to      */
multiline_comment|/* initialize all the entries in the hash table to point to a constant        */
multiline_comment|/* string. The decompressor does the same. This solution requires no extra    */
multiline_comment|/* test. The contents of the string do not matter so long as the string is    */
multiline_comment|/* the same for the compressor and decompressor and contains at least         */
multiline_comment|/* MAX_RAW_ITEM bytes. I chose consecutive decimal digits because they do not */
multiline_comment|/* have white space problems (e.g. there is no chance that the compiler will  */
multiline_comment|/* replace more than one space by a TAB) and because they make the length of  */
multiline_comment|/* the string obvious by inspection.                                          */
DECL|macro|START_STRING_18
mdefine_line|#define START_STRING_18 ((UBYTE *) &quot;123456789012345678&quot;)
multiline_comment|/* In this algorithm, hash values have to be calculated at more than one      */
multiline_comment|/* point. The following macro neatens the code up for this.                   */
DECL|macro|HASH
mdefine_line|#define HASH(PTR) &bslash;&n;   (((40543*(((*(PTR))&lt;&lt;8)^((*((PTR)+1))&lt;&lt;4)^(*((PTR)+2))))&gt;&gt;4) &amp; 0xFFF)
multiline_comment|/******************************************************************************/
DECL|function|compress_compress
id|LOCAL
r_void
id|compress_compress
(paren
id|p_wrk_mem
comma
id|p_src_first
comma
id|src_len
comma
id|p_dst_first
comma
id|p_dst_len
)paren
multiline_comment|/* Input  : Hand over the required amount of working memory in p_wrk_mem.     */
multiline_comment|/* Input  : Specify input block using p_src_first and src_len.                */
multiline_comment|/* Input  : Point p_dst_first to the start of the output zone (OZ).           */
multiline_comment|/* Input  : Point p_dst_len to a ULONG to receive the output length.          */
multiline_comment|/* Input  : Input block and output zone must not overlap.                     */
multiline_comment|/* Output : Length of output block written to *p_dst_len.                     */
multiline_comment|/* Output : Output block in Mem[p_dst_first..p_dst_first+*p_dst_len-1]. May   */
multiline_comment|/* Output : write in OZ=Mem[p_dst_first..p_dst_first+src_len+MAX_CMP_GROUP-1].*/
multiline_comment|/* Output : Upon completion guaranteed *p_dst_len&lt;=src_len+FLAG_BYTES.        */
id|UBYTE
op_star
id|p_wrk_mem
suffix:semicolon
id|UBYTE
op_star
id|p_src_first
suffix:semicolon
id|ULONG
id|src_len
suffix:semicolon
id|UBYTE
op_star
id|p_dst_first
suffix:semicolon
id|LONG
op_star
id|p_dst_len
suffix:semicolon
(brace
multiline_comment|/* p_src and p_dst step through the source and destination blocks.           */
r_register
id|UBYTE
op_star
id|p_src
op_assign
id|p_src_first
suffix:semicolon
r_register
id|UBYTE
op_star
id|p_dst
op_assign
id|p_dst_first
suffix:semicolon
multiline_comment|/* The following variables are never modified and are used in the            */
multiline_comment|/* calculations that determine when the main loop terminates.                */
id|UBYTE
op_star
id|p_src_post
op_assign
id|p_src_first
op_plus
id|src_len
suffix:semicolon
id|UBYTE
op_star
id|p_dst_post
op_assign
id|p_dst_first
op_plus
id|src_len
suffix:semicolon
id|UBYTE
op_star
id|p_src_max1
op_assign
id|p_src_first
op_plus
id|src_len
op_minus
id|MAX_RAW_ITEM
suffix:semicolon
id|UBYTE
op_star
id|p_src_max16
op_assign
id|p_src_first
op_plus
id|src_len
op_minus
id|MAX_RAW_ITEM
op_star
l_int|16
suffix:semicolon
multiline_comment|/* The variables &squot;p_control&squot; and &squot;control&squot; are used to buffer control bits.  */
multiline_comment|/* Before each group is processed, the next two bytes of the output block    */
multiline_comment|/* are set aside for the control word for the group about to be processed.   */
multiline_comment|/* &squot;p_control&squot; is set to point to the first byte of that word. Meanwhile,    */
multiline_comment|/* &squot;control&squot; buffers the control bits being generated during the processing  */
multiline_comment|/* of the group. Instead of having a counter to keep track of how many items */
multiline_comment|/* have been processed (=the number of bits in the control word), at the     */
multiline_comment|/* start of each group, the top word of &squot;control&squot; is filled with 1 bits.     */
multiline_comment|/* As &squot;control&squot; is shifted for each item, the 1 bits in the top word are     */
multiline_comment|/* absorbed or destroyed. When they all run out (i.e. when the top word is   */
multiline_comment|/* all zero bits, we know that we are at the end of a group.                 */
DECL|macro|TOPWORD
macro_line|# define TOPWORD 0xFFFF0000
id|UBYTE
op_star
id|p_control
suffix:semicolon
r_register
id|ULONG
id|control
op_assign
id|TOPWORD
suffix:semicolon
multiline_comment|/* THe variable &squot;hash&squot; always points to the first element of the hash table. */
id|UBYTE
op_star
op_star
id|hash
op_assign
(paren
id|UBYTE
op_star
op_star
)paren
id|ULONG_ALIGN_UP
c_func
(paren
id|p_wrk_mem
)paren
suffix:semicolon
multiline_comment|/* The following two variables represent the literal buffer. p_h1 points to  */
multiline_comment|/* the hash table entry corresponding to the youngest literal. p_h2 points   */
multiline_comment|/* to the hash table entry corresponding to the second youngest literal.     */
multiline_comment|/* Note: p_h1=0=&gt;p_h2=0 because zero values denote absence of a pending      */
multiline_comment|/* literal. The variables are initialized to zero meaning an empty &quot;buffer&quot;. */
id|UBYTE
op_star
op_star
id|p_h1
op_assign
l_int|0
suffix:semicolon
id|UBYTE
op_star
op_star
id|p_h2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* To start, we write the flag bytes. Being optimistic, we set the flag to   */
multiline_comment|/* FLAG_COMPRESS. The remaining flag bytes are zeroed so as to keep the      */
multiline_comment|/* algorithm deterministic.                                                  */
op_star
id|p_dst
op_increment
op_assign
id|FLAG_COMPRESS
suffix:semicolon
(brace
id|UWORD
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
op_le
id|FLAG_BYTES
suffix:semicolon
id|i
op_increment
)paren
op_star
id|p_dst
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reserve the first word of output as the control word for the first group. */
multiline_comment|/* Note: This is undone at the end if the input block is empty.              */
id|p_control
op_assign
id|p_dst
suffix:semicolon
id|p_dst
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* Initialize all elements of the hash table to point to a constant string.  */
multiline_comment|/* Use of an unrolled loop speeds this up considerably.                      */
(brace
id|UWORD
id|i
suffix:semicolon
id|UBYTE
op_star
op_star
id|p_h
op_assign
id|hash
suffix:semicolon
DECL|macro|ZH
macro_line|#  define ZH *p_h++=START_STRING_18
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* 256=HASH_TABLE_LENGTH/16. */
(brace
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
id|ZH
suffix:semicolon
)brace
)brace
multiline_comment|/* The main loop processes either 1 or 16 items per iteration. As its        */
multiline_comment|/* termination logic is complicated, I have opted for an infinite loop       */
multiline_comment|/* structure containing &squot;break&squot; and &squot;goto&squot; statements.                       */
r_while
c_loop
(paren
id|TRUE
)paren
(brace
multiline_comment|/* Begin main processing loop. */
multiline_comment|/* Note: All the variables here except unroll should be defined within    */
multiline_comment|/*       the inner loop. Unfortunately the loop hasn&squot;t got a block.       */
r_register
id|UBYTE
op_star
id|p
suffix:semicolon
multiline_comment|/* Scans through targ phrase during matching. */
r_register
id|UBYTE
op_star
id|p_ziv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Points to first byte of current Ziv.       */
r_register
id|UWORD
id|unroll
suffix:semicolon
multiline_comment|/* Loop counter for unrolled inner loop.      */
r_register
id|UWORD
id|index
suffix:semicolon
multiline_comment|/* Index of current hash table entry.         */
r_register
id|UBYTE
op_star
op_star
id|p_h0
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Pointer to current hash table entry.       */
multiline_comment|/* Test for overrun and jump to overrun code if necessary.                */
r_if
c_cond
(paren
id|p_dst
OG
id|p_dst_post
)paren
r_goto
id|overrun
suffix:semicolon
multiline_comment|/* The following cascade of if statements efficiently catches and deals   */
multiline_comment|/* with varying degrees of closeness to the end of the input block.       */
multiline_comment|/* When we get very close to the end, we stop updating the table and      */
multiline_comment|/* code the remaining bytes as literals. This makes the code simpler.     */
id|unroll
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|p_src
OG
id|p_src_max16
)paren
(brace
id|unroll
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|p_src
OG
id|p_src_max1
)paren
(brace
r_if
c_cond
(paren
id|p_src
op_eq
id|p_src_post
)paren
r_break
suffix:semicolon
r_else
r_goto
id|literal
suffix:semicolon
)brace
)brace
multiline_comment|/* This inner unrolled loop processes &squot;unroll&squot; (whose value is either 1   */
multiline_comment|/* or 16) items. I have chosen to implement this loop with labels and     */
multiline_comment|/* gotos to heighten the ease with which the loop may be implemented with */
multiline_comment|/* a single decrement and branch instruction in assembly language and     */
multiline_comment|/* also because the labels act as highly readable place markers.          */
multiline_comment|/* (Also because we jump into the loop for endgame literals (see above)). */
id|begin_unrolled_loop
suffix:colon
multiline_comment|/* To process the next phrase, we hash the next three bytes and use    */
multiline_comment|/* the resultant hash table index to look up the hash table. A pointer */
multiline_comment|/* to the entry is stored in p_h0 so as to avoid an array lookup. The  */
multiline_comment|/* hash table entry *p_h0 is looked up yielding a pointer p to a       */
multiline_comment|/* potential match of the Ziv in the history.                          */
id|index
op_assign
id|HASH
c_func
(paren
id|p_src
)paren
suffix:semicolon
id|p_h0
op_assign
op_amp
id|hash
(braket
id|index
)braket
suffix:semicolon
id|p
op_assign
op_star
id|p_h0
suffix:semicolon
multiline_comment|/* Having looked up the candidate position, we are in a position to    */
multiline_comment|/* attempt a match. The match loop has been unrolled using the PS      */
multiline_comment|/* macro so that failure within the first three bytes automatically    */
multiline_comment|/* results in the literal branch being taken. The coding is simple.    */
multiline_comment|/* p_ziv saves p_src so we can let p_src wander.                       */
DECL|macro|PS
macro_line|#       define PS *p++!=*p_src++
id|p_ziv
op_assign
id|p_src
suffix:semicolon
r_if
c_cond
(paren
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
)paren
(brace
multiline_comment|/* Literal. */
multiline_comment|/* Code the literal byte as itself and a zero control bit.          */
id|p_src
op_assign
id|p_ziv
suffix:semicolon
id|literal
suffix:colon
op_star
id|p_dst
op_increment
op_assign
op_star
id|p_src
op_increment
suffix:semicolon
id|control
op_and_assign
l_int|0xFFFEFFFF
suffix:semicolon
multiline_comment|/* We have just coded a literal. If we had two pending ones, that   */
multiline_comment|/* makes three and we can update the hash table.                    */
r_if
c_cond
(paren
id|p_h2
op_ne
l_int|0
)paren
(brace
op_star
id|p_h2
op_assign
id|p_ziv
op_minus
l_int|2
suffix:semicolon
)brace
multiline_comment|/* In any case, rotate the hash table pointers for next time. */
id|p_h2
op_assign
id|p_h1
suffix:semicolon
id|p_h1
op_assign
id|p_h0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Copy */
multiline_comment|/* Match up to 15 remaining bytes using an unrolled loop and code. */
macro_line|#if 0
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|p_src
op_increment
suffix:semicolon
macro_line|#else     
r_if
c_cond
(paren
op_logical_neg
(paren
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
op_logical_or
id|PS
)paren
)paren
id|p_src
op_increment
suffix:semicolon
macro_line|#endif
op_star
id|p_dst
op_increment
op_assign
(paren
(paren
id|index
op_amp
l_int|0xF00
)paren
op_rshift
l_int|4
)paren
op_or
(paren
op_decrement
id|p_src
op_minus
id|p_ziv
op_minus
l_int|3
)paren
suffix:semicolon
op_star
id|p_dst
op_increment
op_assign
id|index
op_amp
l_int|0xFF
suffix:semicolon
multiline_comment|/* As we have just coded three bytes, we are now in a position to   */
multiline_comment|/* update the hash table with the literal bytes that were pending   */
multiline_comment|/* upon the arrival of extra context bytes.                         */
r_if
c_cond
(paren
id|p_h1
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|p_h2
op_ne
l_int|0
)paren
(brace
op_star
id|p_h2
op_assign
id|p_ziv
op_minus
l_int|2
suffix:semicolon
id|p_h2
op_assign
l_int|0
suffix:semicolon
)brace
op_star
id|p_h1
op_assign
id|p_ziv
op_minus
l_int|1
suffix:semicolon
id|p_h1
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* In any case, we can update the hash table based on the current   */
multiline_comment|/* position as we just coded at least three bytes in a copy items.  */
op_star
id|p_h0
op_assign
id|p_ziv
suffix:semicolon
)brace
id|control
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* This loop is all set up for a decrement and jump instruction! */
macro_line|#ifndef linux
"`"
id|end_unrolled_loop
suffix:colon
r_if
c_cond
(paren
op_decrement
id|unroll
)paren
r_goto
id|begin_unrolled_loop
suffix:semicolon
macro_line|#else
multiline_comment|/* end_unrolled_loop: */
r_if
c_cond
(paren
op_decrement
id|unroll
)paren
r_goto
id|begin_unrolled_loop
suffix:semicolon
macro_line|#endif
multiline_comment|/* At this point it will nearly always be the end of a group in which     */
multiline_comment|/* case, we have to do some control-word processing. However, near the    */
multiline_comment|/* end of the input block, the inner unrolled loop is only executed once. */
multiline_comment|/* This necessitates the &squot;if&squot; test.                                       */
r_if
c_cond
(paren
(paren
id|control
op_amp
id|TOPWORD
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Write the control word to the place we saved for it in the output. */
op_star
id|p_control
op_increment
op_assign
id|control
op_amp
l_int|0xFF
suffix:semicolon
op_star
id|p_control
op_assign
(paren
id|control
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
multiline_comment|/* Reserve the next word in the output block for the control word */
multiline_comment|/* for the group about to be processed.                           */
id|p_control
op_assign
id|p_dst
suffix:semicolon
id|p_dst
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* Reset the control bits buffer. */
id|control
op_assign
id|TOPWORD
suffix:semicolon
)brace
)brace
multiline_comment|/* End main processing loop. */
multiline_comment|/* After the main processing loop has executed, all the input bytes have     */
multiline_comment|/* been processed. However, the control word has still to be written to the  */
multiline_comment|/* word reserved for it in the output at the start of the most recent group. */
multiline_comment|/* Before writing, the control word has to be shifted so that all the bits   */
multiline_comment|/* are in the right place. The &quot;empty&quot; bit positions are filled with 1s      */
multiline_comment|/* which partially fill the top word.                                        */
r_while
c_loop
(paren
id|control
op_amp
id|TOPWORD
)paren
(brace
id|control
op_rshift_assign
l_int|1
suffix:semicolon
)brace
op_star
id|p_control
op_increment
op_assign
id|control
op_amp
l_int|0xFF
suffix:semicolon
op_star
id|p_control
op_increment
op_assign
(paren
id|control
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
multiline_comment|/* If the last group contained no items, delete the control word too.        */
r_if
c_cond
(paren
id|p_control
op_eq
id|p_dst
)paren
id|p_dst
op_sub_assign
l_int|2
suffix:semicolon
multiline_comment|/* Write the length of the output block to the dst_len parameter and return. */
op_star
id|p_dst_len
op_assign
id|p_dst
op_minus
id|p_dst_first
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* Jump here as soon as an overrun is detected. An overrun is defined to     */
multiline_comment|/* have occurred if p_dst&gt;p_dst_first+src_len. That is, the moment the       */
multiline_comment|/* length of the output written so far exceeds the length of the input block.*/
multiline_comment|/* The algorithm checks for overruns at least at the end of each group       */
multiline_comment|/* which means that the maximum overrun is MAX_CMP_GROUP bytes.              */
multiline_comment|/* Once an overrun occurs, the only thing to do is to set the copy flag and  */
multiline_comment|/* copy the input over.                                                      */
id|overrun
suffix:colon
macro_line|#if 0
op_star
id|p_dst_first
op_assign
id|FLAG_COPY
suffix:semicolon
id|fast_copy
c_func
(paren
id|p_src_first
comma
id|p_dst_first
op_plus
id|FLAG_BYTES
comma
id|src_len
)paren
suffix:semicolon
op_star
id|p_dst_len
op_assign
id|src_len
op_plus
id|FLAG_BYTES
suffix:semicolon
macro_line|#else
id|fast_copy
c_func
(paren
id|p_src_first
comma
id|p_dst_first
comma
id|src_len
)paren
suffix:semicolon
op_star
id|p_dst_len
op_assign
op_minus
id|src_len
suffix:semicolon
multiline_comment|/* return a negative number to indicate uncompressed data */
macro_line|#endif
)brace
multiline_comment|/******************************************************************************/
DECL|function|compress_decompress
id|LOCAL
r_void
id|compress_decompress
(paren
id|p_wrk_mem
comma
id|p_src_first
comma
id|src_len
comma
id|p_dst_first
comma
id|p_dst_len
)paren
multiline_comment|/* Input  : Hand over the required amount of working memory in p_wrk_mem.     */
multiline_comment|/* Input  : Specify input block using p_src_first and src_len.                */
multiline_comment|/* Input  : Point p_dst_first to the start of the output zone.                */
multiline_comment|/* Input  : Point p_dst_len to a ULONG to receive the output length.          */
multiline_comment|/* Input  : Input block and output zone must not overlap. User knows          */
multiline_comment|/* Input  : upperbound on output block length from earlier compression.       */
multiline_comment|/* Input  : In any case, maximum expansion possible is nine times.            */
multiline_comment|/* Output : Length of output block written to *p_dst_len.                     */
multiline_comment|/* Output : Output block in Mem[p_dst_first..p_dst_first+*p_dst_len-1].       */
multiline_comment|/* Output : Writes only  in Mem[p_dst_first..p_dst_first+*p_dst_len-1].       */
id|UBYTE
op_star
id|p_wrk_mem
suffix:semicolon
id|UBYTE
op_star
id|p_src_first
suffix:semicolon
id|LONG
id|src_len
suffix:semicolon
id|UBYTE
op_star
id|p_dst_first
suffix:semicolon
id|ULONG
op_star
id|p_dst_len
suffix:semicolon
(brace
multiline_comment|/* Byte pointers p_src and p_dst scan through the input and output blocks.   */
r_register
id|UBYTE
op_star
id|p_src
op_assign
id|p_src_first
op_plus
id|FLAG_BYTES
suffix:semicolon
r_register
id|UBYTE
op_star
id|p_dst
op_assign
id|p_dst_first
suffix:semicolon
multiline_comment|/* we need to avoid a SEGV when trying to uncompress corrupt data */
r_register
id|UBYTE
op_star
id|p_dst_post
op_assign
id|p_dst_first
op_plus
op_star
id|p_dst_len
suffix:semicolon
multiline_comment|/* The following two variables are never modified and are used to control    */
multiline_comment|/* the main loop.                                                            */
id|UBYTE
op_star
id|p_src_post
op_assign
id|p_src_first
op_plus
id|src_len
suffix:semicolon
id|UBYTE
op_star
id|p_src_max16
op_assign
id|p_src_first
op_plus
id|src_len
op_minus
(paren
id|MAX_CMP_GROUP
op_minus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* The hash table is the only resident of the working memory. The hash table */
multiline_comment|/* contains HASH_TABLE_LENGTH=4096 pointers to positions in the history. To  */
multiline_comment|/* keep Macintoshes happy, it is longword aligned.                           */
id|UBYTE
op_star
op_star
id|hash
op_assign
(paren
id|UBYTE
op_star
op_star
)paren
id|ULONG_ALIGN_UP
c_func
(paren
id|p_wrk_mem
)paren
suffix:semicolon
multiline_comment|/* The variable &squot;control&squot; is used to buffer the control bits which appear in */
multiline_comment|/* groups of 16 bits (control words) at the start of each compressed group.  */
multiline_comment|/* When each group is read, bit 16 of the register is set to one. Whenever   */
multiline_comment|/* a new bit is needed, the register is shifted right. When the value of the */
multiline_comment|/* register becomes 1, we know that we have reached the end of a group.      */
multiline_comment|/* Initializing the register to 1 thus instructs the code to follow that it  */
multiline_comment|/* should read a new control word immediately.                               */
r_register
id|ULONG
id|control
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* The value of &squot;literals&squot; is always in the range 0..3. It is the number of  */
multiline_comment|/* consecutive literal items just seen. We have to record this number so as  */
multiline_comment|/* to know when to update the hash table. When literals gets to 3, there     */
multiline_comment|/* have been three consecutive literals and we can update at the position of */
multiline_comment|/* the oldest of the three.                                                  */
r_register
id|UWORD
id|literals
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check the leading copy flag to see if the compressor chose to use a copy  */
multiline_comment|/* operation instead of a compression operation. If a copy operation was     */
multiline_comment|/* used, then all we need to do is copy the data over, set the output length */
multiline_comment|/* and return.                                                               */
macro_line|#if 0
r_if
c_cond
(paren
op_star
id|p_src_first
op_eq
id|FLAG_COPY
)paren
(brace
id|fast_copy
c_func
(paren
id|p_src_first
op_plus
id|FLAG_BYTES
comma
id|p_dst_first
comma
id|src_len
op_minus
id|FLAG_BYTES
)paren
suffix:semicolon
op_star
id|p_dst_len
op_assign
id|src_len
op_minus
id|FLAG_BYTES
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|src_len
OL
l_int|0
)paren
(brace
id|fast_copy
c_func
(paren
id|p_src_first
comma
id|p_dst_first
comma
op_minus
id|src_len
)paren
suffix:semicolon
op_star
id|p_dst_len
op_assign
(paren
id|ULONG
)paren
op_minus
id|src_len
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Initialize all elements of the hash table to point to a constant string.  */
multiline_comment|/* Use of an unrolled loop speeds this up considerably.                      */
(brace
id|UWORD
id|i
suffix:semicolon
id|UBYTE
op_star
op_star
id|p_h
op_assign
id|hash
suffix:semicolon
DECL|macro|ZJ
macro_line|#  define ZJ *p_h++=START_STRING_18
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* 256=HASH_TABLE_LENGTH/16. */
(brace
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
id|ZJ
suffix:semicolon
)brace
)brace
multiline_comment|/* The outer loop processes either 1 or 16 items per iteration depending on  */
multiline_comment|/* how close p_src is to the end of the input block.                         */
r_while
c_loop
(paren
id|p_src
op_ne
id|p_src_post
)paren
(brace
multiline_comment|/* Start of outer loop */
r_register
id|UWORD
id|unroll
suffix:semicolon
multiline_comment|/* Counts unrolled loop executions.              */
multiline_comment|/* When &squot;control&squot; has the value 1, it means that the 16 buffered control  */
multiline_comment|/* bits that were read in at the start of the current group have all been */
multiline_comment|/* shifted out and that all that is left is the 1 bit that was injected   */
multiline_comment|/* into bit 16 at the start of the current group. When we reach the end   */
multiline_comment|/* of a group, we have to load a new control word and inject a new 1 bit. */
r_if
c_cond
(paren
id|control
op_eq
l_int|1
)paren
(brace
id|control
op_assign
l_int|0x10000
op_or
op_star
id|p_src
op_increment
suffix:semicolon
id|control
op_or_assign
(paren
op_star
id|p_src
op_increment
)paren
op_lshift
l_int|8
suffix:semicolon
)brace
multiline_comment|/* If it is possible that we are within 16 groups from the end of the     */
multiline_comment|/* input, execute the unrolled loop only once, else process a whole group */
multiline_comment|/* of 16 items by looping 16 times.                                       */
id|unroll
op_assign
id|p_src
op_le
id|p_src_max16
ques
c_cond
l_int|16
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* This inner loop processes one phrase (item) per iteration. */
r_while
c_loop
(paren
id|unroll
op_decrement
)paren
(brace
multiline_comment|/* Begin unrolled inner loop. */
multiline_comment|/* Process a literal or copy item depending on the next control bit. */
r_if
c_cond
(paren
id|control
op_amp
l_int|1
)paren
(brace
multiline_comment|/* Copy item. */
r_register
id|UBYTE
op_star
id|p
suffix:semicolon
multiline_comment|/* Points to place from which to copy. */
r_register
id|UWORD
id|lenmt
suffix:semicolon
multiline_comment|/* Length of copy item minus three.    */
r_register
id|UBYTE
op_star
op_star
id|p_hte
suffix:semicolon
multiline_comment|/* Pointer to current hash table entry.*/
r_register
id|UBYTE
op_star
id|p_ziv
op_assign
id|p_dst
suffix:semicolon
multiline_comment|/* Pointer to start of current Ziv.    */
multiline_comment|/* Read and dismantle the copy word. Work out from where to copy.   */
id|lenmt
op_assign
op_star
id|p_src
op_increment
suffix:semicolon
id|p_hte
op_assign
op_amp
id|hash
(braket
(paren
(paren
id|lenmt
op_amp
l_int|0xF0
)paren
op_lshift
l_int|4
)paren
op_or
op_star
id|p_src
op_increment
)braket
suffix:semicolon
id|p
op_assign
op_star
id|p_hte
suffix:semicolon
id|lenmt
op_and_assign
l_int|0xF
suffix:semicolon
multiline_comment|/* Now perform the copy using a half unrolled loop. */
op_star
id|p_dst
op_increment
op_assign
op_star
id|p
op_increment
suffix:semicolon
op_star
id|p_dst
op_increment
op_assign
op_star
id|p
op_increment
suffix:semicolon
op_star
id|p_dst
op_increment
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|lenmt
op_decrement
)paren
op_star
id|p_dst
op_increment
op_assign
op_star
id|p
op_increment
suffix:semicolon
multiline_comment|/* Because we have just received 3 or more bytes in a copy item     */
multiline_comment|/* (whose bytes we have just installed in the output), we are now   */
multiline_comment|/* in a position to flush all the pending literal hashings that had */
multiline_comment|/* been postponed for lack of bytes.                                */
r_if
c_cond
(paren
id|literals
OG
l_int|0
)paren
(brace
r_register
id|UBYTE
op_star
id|r
op_assign
id|p_ziv
op_minus
id|literals
suffix:semicolon
suffix:semicolon
id|hash
(braket
id|HASH
c_func
(paren
id|r
)paren
)braket
op_assign
id|r
suffix:semicolon
r_if
c_cond
(paren
id|literals
op_eq
l_int|2
)paren
(brace
id|r
op_increment
suffix:semicolon
id|hash
(braket
id|HASH
c_func
(paren
id|r
)paren
)braket
op_assign
id|r
suffix:semicolon
)brace
id|literals
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* In any case, we can immediately update the hash table with the   */
multiline_comment|/* current position. We don&squot;t need to do a HASH(...) to work out    */
multiline_comment|/* where to put the pointer, as the compressor just told us!!!      */
op_star
id|p_hte
op_assign
id|p_ziv
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Literal item. */
multiline_comment|/* Copy over the literal byte. */
op_star
id|p_dst
op_increment
op_assign
op_star
id|p_src
op_increment
suffix:semicolon
multiline_comment|/* If we now have three literals waiting to be hashed into the hash */
multiline_comment|/* table, we can do one of them now (because there are three).      */
r_if
c_cond
(paren
op_increment
id|literals
op_eq
l_int|3
)paren
(brace
r_register
id|UBYTE
op_star
id|p
op_assign
id|p_dst
op_minus
l_int|3
suffix:semicolon
id|hash
(braket
id|HASH
c_func
(paren
id|p
)paren
)braket
op_assign
id|p
suffix:semicolon
id|literals
op_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/* Shift the control buffer so the next control bit is in bit 0. */
id|control
op_rshift_assign
l_int|1
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|p_dst
OG
id|p_dst_post
)paren
(brace
multiline_comment|/* Shit: we tried to decompress corrupt data */
op_star
id|p_dst_len
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* End unrolled inner loop. */
)brace
multiline_comment|/* End of outer loop */
multiline_comment|/* Write the length of the decompressed data before returning. */
op_star
id|p_dst_len
op_assign
id|p_dst
op_minus
id|p_dst_first
suffix:semicolon
)brace
multiline_comment|/******************************************************************************/
multiline_comment|/*                               End of LZRW3.C                               */
multiline_comment|/******************************************************************************/
eof
