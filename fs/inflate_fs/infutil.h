multiline_comment|/* infutil.h -- types and macros common to blocks and codes&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
macro_line|#ifndef _INFUTIL_H
DECL|macro|_INFUTIL_H
mdefine_line|#define _INFUTIL_H
macro_line|#include &quot;zconf.h&quot;
macro_line|#include &quot;inftrees.h&quot;
macro_line|#include &quot;infcodes.h&quot;
r_typedef
r_enum
(brace
DECL|enumerator|TYPE
id|TYPE
comma
multiline_comment|/* get type bits (3, including end bit) */
DECL|enumerator|LENS
id|LENS
comma
multiline_comment|/* get lengths for stored */
DECL|enumerator|STORED
id|STORED
comma
multiline_comment|/* processing stored block */
DECL|enumerator|TABLE
id|TABLE
comma
multiline_comment|/* get table lengths */
DECL|enumerator|BTREE
id|BTREE
comma
multiline_comment|/* get bit lengths tree for a dynamic block */
DECL|enumerator|DTREE
id|DTREE
comma
multiline_comment|/* get length, distance trees for a dynamic block */
DECL|enumerator|CODES
id|CODES
comma
multiline_comment|/* processing fixed or dynamic block */
DECL|enumerator|DRY
id|DRY
comma
multiline_comment|/* output remaining window bytes */
DECL|enumerator|B_DONE
id|B_DONE
comma
multiline_comment|/* finished last block, done */
DECL|enumerator|B_BAD
id|B_BAD
)brace
multiline_comment|/* got a data error--stuck here */
DECL|typedef|inflate_block_mode
id|inflate_block_mode
suffix:semicolon
multiline_comment|/* inflate blocks semi-private state */
DECL|struct|inflate_blocks_state
r_struct
id|inflate_blocks_state
(brace
multiline_comment|/* mode */
DECL|member|mode
id|inflate_block_mode
id|mode
suffix:semicolon
multiline_comment|/* current inflate_block mode */
multiline_comment|/* mode dependent information */
r_union
(brace
DECL|member|left
id|uInt
id|left
suffix:semicolon
multiline_comment|/* if STORED, bytes left to copy */
r_struct
(brace
DECL|member|table
id|uInt
id|table
suffix:semicolon
multiline_comment|/* table lengths (14 bits) */
DECL|member|index
id|uInt
id|index
suffix:semicolon
multiline_comment|/* index into blens (or border) */
DECL|member|blens
id|uIntf
op_star
id|blens
suffix:semicolon
multiline_comment|/* bit lengths of codes */
DECL|member|bb
id|uInt
id|bb
suffix:semicolon
multiline_comment|/* bit length tree depth */
DECL|member|tb
id|inflate_huft
op_star
id|tb
suffix:semicolon
multiline_comment|/* bit length decoding tree */
DECL|member|trees
)brace
id|trees
suffix:semicolon
multiline_comment|/* if DTREE, decoding info for trees */
r_struct
(brace
id|inflate_codes_statef
DECL|member|codes
op_star
id|codes
suffix:semicolon
DECL|member|decode
)brace
id|decode
suffix:semicolon
multiline_comment|/* if CODES, current state */
DECL|member|sub
)brace
id|sub
suffix:semicolon
multiline_comment|/* submode */
DECL|member|last
id|uInt
id|last
suffix:semicolon
multiline_comment|/* true if this block is the last block */
multiline_comment|/* mode independent information */
DECL|member|bitk
id|uInt
id|bitk
suffix:semicolon
multiline_comment|/* bits in bit buffer */
DECL|member|bitb
id|uLong
id|bitb
suffix:semicolon
multiline_comment|/* bit buffer */
DECL|member|hufts
id|inflate_huft
op_star
id|hufts
suffix:semicolon
multiline_comment|/* single malloc for tree space */
DECL|member|window
id|Bytef
op_star
id|window
suffix:semicolon
multiline_comment|/* sliding window */
DECL|member|end
id|Bytef
op_star
id|end
suffix:semicolon
multiline_comment|/* one byte after sliding window */
DECL|member|read
id|Bytef
op_star
id|read
suffix:semicolon
multiline_comment|/* window read pointer */
DECL|member|write
id|Bytef
op_star
id|write
suffix:semicolon
multiline_comment|/* window write pointer */
DECL|member|checkfn
id|check_func
id|checkfn
suffix:semicolon
multiline_comment|/* check function */
DECL|member|check
id|uLong
id|check
suffix:semicolon
multiline_comment|/* check on output */
)brace
suffix:semicolon
multiline_comment|/* defines for inflate input/output */
multiline_comment|/*   update pointers and return */
DECL|macro|UPDBITS
mdefine_line|#define UPDBITS {s-&gt;bitb=b;s-&gt;bitk=k;}
DECL|macro|UPDIN
mdefine_line|#define UPDIN {z-&gt;avail_in=n;z-&gt;total_in+=p-z-&gt;next_in;z-&gt;next_in=p;}
DECL|macro|UPDOUT
mdefine_line|#define UPDOUT {s-&gt;write=q;}
DECL|macro|UPDATE
mdefine_line|#define UPDATE {UPDBITS UPDIN UPDOUT}
DECL|macro|LEAVE
mdefine_line|#define LEAVE {UPDATE return zlib_fs_inflate_flush(s,z,r);}
multiline_comment|/*   get bytes and bits */
DECL|macro|LOADIN
mdefine_line|#define LOADIN {p=z-&gt;next_in;n=z-&gt;avail_in;b=s-&gt;bitb;k=s-&gt;bitk;}
DECL|macro|NEEDBYTE
mdefine_line|#define NEEDBYTE {if(n)r=Z_OK;else LEAVE}
DECL|macro|NEXTBYTE
mdefine_line|#define NEXTBYTE (n--,*p++)
DECL|macro|NEEDBITS
mdefine_line|#define NEEDBITS(j) {while(k&lt;(j)){NEEDBYTE;b|=((uLong)NEXTBYTE)&lt;&lt;k;k+=8;}}
DECL|macro|DUMPBITS
mdefine_line|#define DUMPBITS(j) {b&gt;&gt;=(j);k-=(j);}
multiline_comment|/*   output bytes */
DECL|macro|WAVAIL
mdefine_line|#define WAVAIL (uInt)(q&lt;s-&gt;read?s-&gt;read-q-1:s-&gt;end-q)
DECL|macro|LOADOUT
mdefine_line|#define LOADOUT {q=s-&gt;write;m=(uInt)WAVAIL;}
DECL|macro|WRAP
mdefine_line|#define WRAP {if(q==s-&gt;end&amp;&amp;s-&gt;read!=s-&gt;window){q=s-&gt;window;m=(uInt)WAVAIL;}}
DECL|macro|FLUSH
mdefine_line|#define FLUSH {UPDOUT r=zlib_fs_inflate_flush(s,z,r); LOADOUT}
DECL|macro|NEEDOUT
mdefine_line|#define NEEDOUT {if(m==0){WRAP if(m==0){FLUSH WRAP if(m==0) LEAVE}}r=Z_OK;}
DECL|macro|OUTBYTE
mdefine_line|#define OUTBYTE(a) {*q++=(Byte)(a);m--;}
multiline_comment|/*   load local pointers */
DECL|macro|LOAD
mdefine_line|#define LOAD {LOADIN LOADOUT}
multiline_comment|/* masks for lower bits (size given to avoid silly warnings with Visual C++) */
r_extern
id|uInt
id|zlib_fs_inflate_mask
(braket
l_int|17
)braket
suffix:semicolon
multiline_comment|/* copy as much as possible from the sliding window to the output area */
r_extern
r_int
id|zlib_fs_inflate_flush
id|OF
c_func
(paren
(paren
id|inflate_blocks_statef
op_star
comma
id|z_streamp
comma
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/* inflate private state */
r_typedef
r_enum
(brace
DECL|enumerator|METHOD
id|METHOD
comma
multiline_comment|/* waiting for method byte */
DECL|enumerator|FLAG
id|FLAG
comma
multiline_comment|/* waiting for flag byte */
DECL|enumerator|DICT4
id|DICT4
comma
multiline_comment|/* four dictionary check bytes to go */
DECL|enumerator|DICT3
id|DICT3
comma
multiline_comment|/* three dictionary check bytes to go */
DECL|enumerator|DICT2
id|DICT2
comma
multiline_comment|/* two dictionary check bytes to go */
DECL|enumerator|DICT1
id|DICT1
comma
multiline_comment|/* one dictionary check byte to go */
DECL|enumerator|DICT0
id|DICT0
comma
multiline_comment|/* waiting for inflateSetDictionary */
DECL|enumerator|BLOCKS
id|BLOCKS
comma
multiline_comment|/* decompressing blocks */
DECL|enumerator|CHECK4
id|CHECK4
comma
multiline_comment|/* four check bytes to go */
DECL|enumerator|CHECK3
id|CHECK3
comma
multiline_comment|/* three check bytes to go */
DECL|enumerator|CHECK2
id|CHECK2
comma
multiline_comment|/* two check bytes to go */
DECL|enumerator|CHECK1
id|CHECK1
comma
multiline_comment|/* one check byte to go */
DECL|enumerator|I_DONE
id|I_DONE
comma
multiline_comment|/* finished check, done */
DECL|enumerator|I_BAD
id|I_BAD
)brace
multiline_comment|/* got an error--stay here */
DECL|typedef|inflate_mode
id|inflate_mode
suffix:semicolon
DECL|struct|internal_state
r_struct
id|internal_state
(brace
multiline_comment|/* mode */
DECL|member|mode
id|inflate_mode
id|mode
suffix:semicolon
multiline_comment|/* current inflate mode */
multiline_comment|/* mode dependent information */
r_union
(brace
DECL|member|method
id|uInt
id|method
suffix:semicolon
multiline_comment|/* if FLAGS, method byte */
r_struct
(brace
DECL|member|was
id|uLong
id|was
suffix:semicolon
multiline_comment|/* computed check value */
DECL|member|need
id|uLong
id|need
suffix:semicolon
multiline_comment|/* stream check value */
DECL|member|check
)brace
id|check
suffix:semicolon
multiline_comment|/* if CHECK, check values to compare */
DECL|member|marker
id|uInt
id|marker
suffix:semicolon
multiline_comment|/* if BAD, inflateSync&squot;s marker bytes count */
DECL|member|sub
)brace
id|sub
suffix:semicolon
multiline_comment|/* submode */
multiline_comment|/* mode independent information */
DECL|member|nowrap
r_int
id|nowrap
suffix:semicolon
multiline_comment|/* flag for no wrapper */
DECL|member|wbits
id|uInt
id|wbits
suffix:semicolon
multiline_comment|/* log2(window size)  (8..15, defaults to 15) */
id|inflate_blocks_statef
DECL|member|blocks
op_star
id|blocks
suffix:semicolon
multiline_comment|/* current inflate_blocks state */
)brace
suffix:semicolon
multiline_comment|/* inflate codes private state */
r_typedef
r_enum
(brace
multiline_comment|/* waiting for &quot;i:&quot;=input, &quot;o:&quot;=output, &quot;x:&quot;=nothing */
DECL|enumerator|START
id|START
comma
multiline_comment|/* x: set up for LEN */
DECL|enumerator|LEN
id|LEN
comma
multiline_comment|/* i: get length/literal/eob next */
DECL|enumerator|LENEXT
id|LENEXT
comma
multiline_comment|/* i: getting length extra (have base) */
DECL|enumerator|DIST
id|DIST
comma
multiline_comment|/* i: get distance next */
DECL|enumerator|DISTEXT
id|DISTEXT
comma
multiline_comment|/* i: getting distance extra */
DECL|enumerator|COPY
id|COPY
comma
multiline_comment|/* o: copying bytes in window, waiting for space */
DECL|enumerator|LIT
id|LIT
comma
multiline_comment|/* o: got literal, waiting for output space */
DECL|enumerator|WASH
id|WASH
comma
multiline_comment|/* o: got eob, possibly still output waiting */
DECL|enumerator|END
id|END
comma
multiline_comment|/* x: got eob and all data flushed */
DECL|enumerator|BADCODE
id|BADCODE
)brace
multiline_comment|/* x: got error */
DECL|typedef|inflate_codes_mode
id|inflate_codes_mode
suffix:semicolon
DECL|struct|inflate_codes_state
r_struct
id|inflate_codes_state
(brace
multiline_comment|/* mode */
DECL|member|mode
id|inflate_codes_mode
id|mode
suffix:semicolon
multiline_comment|/* current inflate_codes mode */
multiline_comment|/* mode dependent information */
DECL|member|len
id|uInt
id|len
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|tree
id|inflate_huft
op_star
id|tree
suffix:semicolon
multiline_comment|/* pointer into tree */
DECL|member|need
id|uInt
id|need
suffix:semicolon
multiline_comment|/* bits needed */
DECL|member|code
)brace
id|code
suffix:semicolon
multiline_comment|/* if LEN or DIST, where in tree */
DECL|member|lit
id|uInt
id|lit
suffix:semicolon
multiline_comment|/* if LIT, literal */
r_struct
(brace
DECL|member|get
id|uInt
id|get
suffix:semicolon
multiline_comment|/* bits to get for extra */
DECL|member|dist
id|uInt
id|dist
suffix:semicolon
multiline_comment|/* distance back to copy from */
DECL|member|copy
)brace
id|copy
suffix:semicolon
multiline_comment|/* if EXT or COPY, where and how much */
DECL|member|sub
)brace
id|sub
suffix:semicolon
multiline_comment|/* submode */
multiline_comment|/* mode independent information */
DECL|member|lbits
id|Byte
id|lbits
suffix:semicolon
multiline_comment|/* ltree bits decoded per branch */
DECL|member|dbits
id|Byte
id|dbits
suffix:semicolon
multiline_comment|/* dtree bits decoder per branch */
DECL|member|ltree
id|inflate_huft
op_star
id|ltree
suffix:semicolon
multiline_comment|/* literal/length/eob tree */
DECL|member|dtree
id|inflate_huft
op_star
id|dtree
suffix:semicolon
multiline_comment|/* distance tree */
)brace
suffix:semicolon
multiline_comment|/* memory allocation for inflation */
DECL|struct|inflate_workspace
r_struct
id|inflate_workspace
(brace
DECL|member|working_state
id|inflate_codes_statef
id|working_state
suffix:semicolon
DECL|member|working_blocks_state
r_struct
id|inflate_blocks_state
id|working_blocks_state
suffix:semicolon
DECL|member|internal_state
r_struct
id|internal_state
id|internal_state
suffix:semicolon
DECL|member|tree_work_area_1
r_int
r_int
id|tree_work_area_1
(braket
l_int|19
)braket
suffix:semicolon
DECL|member|tree_work_area_2
r_int
r_int
id|tree_work_area_2
(braket
l_int|288
)braket
suffix:semicolon
DECL|member|working_blens
r_int
id|working_blens
(braket
l_int|258
op_plus
l_int|0x1f
op_plus
l_int|0x1f
)braket
suffix:semicolon
DECL|member|working_hufts
id|inflate_huft
id|working_hufts
(braket
id|MANY
)braket
suffix:semicolon
DECL|member|working_window
r_int
r_char
id|working_window
(braket
l_int|1
op_lshift
id|MAX_WBITS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|WS
mdefine_line|#define WS(z) ((struct inflate_workspace *)(z-&gt;workspace))
macro_line|#endif
eof
