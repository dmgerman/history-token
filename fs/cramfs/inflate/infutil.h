multiline_comment|/* infutil.h -- types and macros common to blocks and codes&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
macro_line|#ifndef _INFUTIL_H
DECL|macro|_INFUTIL_H
mdefine_line|#define _INFUTIL_H
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
DECL|enumerator|DONE
id|DONE
comma
multiline_comment|/* finished last block, done */
DECL|enumerator|BAD
id|BAD
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
mdefine_line|#define LEAVE {UPDATE return cramfs_inflate_flush(s,z,r);}
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
mdefine_line|#define FLUSH {UPDOUT r=cramfs_inflate_flush(s,z,r); LOADOUT}
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
id|cramfs_inflate_mask
(braket
l_int|17
)braket
suffix:semicolon
multiline_comment|/* copy as much as possible from the sliding window to the output area */
r_extern
r_int
id|cramfs_inflate_flush
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
DECL|struct|internal_state
DECL|member|dummy
r_struct
id|internal_state
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for buggy compilers */
macro_line|#endif
eof
