multiline_comment|/*&n; *  ncpsign_kernel.c&n; *&n; *  Arne de Bruijn (arne@knoware.nl), 1997&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_NCPFS_PACKET_SIGNING
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ncp.h&gt;
macro_line|#include &quot;ncpsign_kernel.h&quot;
DECL|macro|rol32
mdefine_line|#define rol32(i,c) (((((i)&amp;0xffffffff)&lt;&lt;c)&amp;0xffffffff)| &bslash;&n;                    (((i)&amp;0xffffffff)&gt;&gt;(32-c)))
multiline_comment|/* i386: 32-bit, little endian, handles mis-alignment */
macro_line|#ifdef __i386__
DECL|macro|GET_LE32
mdefine_line|#define GET_LE32(p) (*(int *)(p))
DECL|macro|PUT_LE32
mdefine_line|#define PUT_LE32(p,v) { *(int *)(p)=v; }
macro_line|#else
multiline_comment|/* from include/ncplib.h */
DECL|macro|BVAL
mdefine_line|#define BVAL(buf,pos) (((__u8 *)(buf))[pos])
DECL|macro|PVAL
mdefine_line|#define PVAL(buf,pos) ((unsigned)BVAL(buf,pos))
DECL|macro|BSET
mdefine_line|#define BSET(buf,pos,val) (BVAL(buf,pos) = (val))
r_static
r_inline
id|__u16
DECL|function|WVAL_LH
id|WVAL_LH
c_func
(paren
id|__u8
op_star
id|buf
comma
r_int
id|pos
)paren
(brace
r_return
id|PVAL
c_func
(paren
id|buf
comma
id|pos
)paren
op_or
id|PVAL
c_func
(paren
id|buf
comma
id|pos
op_plus
l_int|1
)paren
op_lshift
l_int|8
suffix:semicolon
)brace
r_static
r_inline
id|__u32
DECL|function|DVAL_LH
id|DVAL_LH
c_func
(paren
id|__u8
op_star
id|buf
comma
r_int
id|pos
)paren
(brace
r_return
id|WVAL_LH
c_func
(paren
id|buf
comma
id|pos
)paren
op_or
id|WVAL_LH
c_func
(paren
id|buf
comma
id|pos
op_plus
l_int|2
)paren
op_lshift
l_int|16
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|WSET_LH
id|WSET_LH
c_func
(paren
id|__u8
op_star
id|buf
comma
r_int
id|pos
comma
id|__u16
id|val
)paren
(brace
id|BSET
c_func
(paren
id|buf
comma
id|pos
comma
id|val
op_amp
l_int|0xff
)paren
suffix:semicolon
id|BSET
c_func
(paren
id|buf
comma
id|pos
op_plus
l_int|1
comma
id|val
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|DSET_LH
id|DSET_LH
c_func
(paren
id|__u8
op_star
id|buf
comma
r_int
id|pos
comma
id|__u32
id|val
)paren
(brace
id|WSET_LH
c_func
(paren
id|buf
comma
id|pos
comma
id|val
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|WSET_LH
c_func
(paren
id|buf
comma
id|pos
op_plus
l_int|2
comma
id|val
op_rshift
l_int|16
)paren
suffix:semicolon
)brace
DECL|macro|GET_LE32
mdefine_line|#define GET_LE32(p) DVAL_LH(p,0)
DECL|macro|PUT_LE32
mdefine_line|#define PUT_LE32(p,v) DSET_LH(p,0,v)
macro_line|#endif
DECL|function|nwsign
r_static
r_void
id|nwsign
c_func
(paren
r_char
op_star
id|r_data1
comma
r_char
op_star
id|r_data2
comma
r_char
op_star
id|outdata
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|w0
comma
id|w1
comma
id|w2
comma
id|w3
suffix:semicolon
r_static
r_int
id|rbit
(braket
l_int|4
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#ifdef __i386__
r_int
r_int
op_star
id|data2
op_assign
(paren
r_int
op_star
)paren
id|r_data2
suffix:semicolon
macro_line|#else
r_int
r_int
id|data2
(braket
l_int|16
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|data2
(braket
id|i
)braket
op_assign
id|GET_LE32
c_func
(paren
id|r_data2
op_plus
(paren
id|i
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
macro_line|#endif 
id|w0
op_assign
id|GET_LE32
c_func
(paren
id|r_data1
)paren
suffix:semicolon
id|w1
op_assign
id|GET_LE32
c_func
(paren
id|r_data1
op_plus
l_int|4
)paren
suffix:semicolon
id|w2
op_assign
id|GET_LE32
c_func
(paren
id|r_data1
op_plus
l_int|8
)paren
suffix:semicolon
id|w3
op_assign
id|GET_LE32
c_func
(paren
id|r_data1
op_plus
l_int|12
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
(brace
id|w0
op_assign
id|rol32
c_func
(paren
id|w0
op_plus
(paren
(paren
id|w1
op_amp
id|w2
)paren
op_or
(paren
(paren
op_complement
id|w1
)paren
op_amp
id|w3
)paren
)paren
op_plus
id|data2
(braket
id|i
op_plus
l_int|0
)braket
comma
l_int|3
)paren
suffix:semicolon
id|w3
op_assign
id|rol32
c_func
(paren
id|w3
op_plus
(paren
(paren
id|w0
op_amp
id|w1
)paren
op_or
(paren
(paren
op_complement
id|w0
)paren
op_amp
id|w2
)paren
)paren
op_plus
id|data2
(braket
id|i
op_plus
l_int|1
)braket
comma
l_int|7
)paren
suffix:semicolon
id|w2
op_assign
id|rol32
c_func
(paren
id|w2
op_plus
(paren
(paren
id|w3
op_amp
id|w0
)paren
op_or
(paren
(paren
op_complement
id|w3
)paren
op_amp
id|w1
)paren
)paren
op_plus
id|data2
(braket
id|i
op_plus
l_int|2
)braket
comma
l_int|11
)paren
suffix:semicolon
id|w1
op_assign
id|rol32
c_func
(paren
id|w1
op_plus
(paren
(paren
id|w2
op_amp
id|w3
)paren
op_or
(paren
(paren
op_complement
id|w2
)paren
op_amp
id|w0
)paren
)paren
op_plus
id|data2
(braket
id|i
op_plus
l_int|3
)braket
comma
l_int|19
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|w0
op_assign
id|rol32
c_func
(paren
id|w0
op_plus
(paren
(paren
(paren
id|w2
op_or
id|w3
)paren
op_amp
id|w1
)paren
op_or
(paren
id|w2
op_amp
id|w3
)paren
)paren
op_plus
l_int|0x5a827999
op_plus
id|data2
(braket
id|i
op_plus
l_int|0
)braket
comma
l_int|3
)paren
suffix:semicolon
id|w3
op_assign
id|rol32
c_func
(paren
id|w3
op_plus
(paren
(paren
(paren
id|w1
op_or
id|w2
)paren
op_amp
id|w0
)paren
op_or
(paren
id|w1
op_amp
id|w2
)paren
)paren
op_plus
l_int|0x5a827999
op_plus
id|data2
(braket
id|i
op_plus
l_int|4
)braket
comma
l_int|5
)paren
suffix:semicolon
id|w2
op_assign
id|rol32
c_func
(paren
id|w2
op_plus
(paren
(paren
(paren
id|w0
op_or
id|w1
)paren
op_amp
id|w3
)paren
op_or
(paren
id|w0
op_amp
id|w1
)paren
)paren
op_plus
l_int|0x5a827999
op_plus
id|data2
(braket
id|i
op_plus
l_int|8
)braket
comma
l_int|9
)paren
suffix:semicolon
id|w1
op_assign
id|rol32
c_func
(paren
id|w1
op_plus
(paren
(paren
(paren
id|w3
op_or
id|w0
)paren
op_amp
id|w2
)paren
op_or
(paren
id|w3
op_amp
id|w0
)paren
)paren
op_plus
l_int|0x5a827999
op_plus
id|data2
(braket
id|i
op_plus
l_int|12
)braket
comma
l_int|13
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|w0
op_assign
id|rol32
c_func
(paren
id|w0
op_plus
(paren
(paren
id|w1
op_xor
id|w2
)paren
op_xor
id|w3
)paren
op_plus
l_int|0x6ed9eba1
op_plus
id|data2
(braket
id|rbit
(braket
id|i
)braket
op_plus
l_int|0
)braket
comma
l_int|3
)paren
suffix:semicolon
id|w3
op_assign
id|rol32
c_func
(paren
id|w3
op_plus
(paren
(paren
id|w0
op_xor
id|w1
)paren
op_xor
id|w2
)paren
op_plus
l_int|0x6ed9eba1
op_plus
id|data2
(braket
id|rbit
(braket
id|i
)braket
op_plus
l_int|8
)braket
comma
l_int|9
)paren
suffix:semicolon
id|w2
op_assign
id|rol32
c_func
(paren
id|w2
op_plus
(paren
(paren
id|w3
op_xor
id|w0
)paren
op_xor
id|w1
)paren
op_plus
l_int|0x6ed9eba1
op_plus
id|data2
(braket
id|rbit
(braket
id|i
)braket
op_plus
l_int|4
)braket
comma
l_int|11
)paren
suffix:semicolon
id|w1
op_assign
id|rol32
c_func
(paren
id|w1
op_plus
(paren
(paren
id|w2
op_xor
id|w3
)paren
op_xor
id|w0
)paren
op_plus
l_int|0x6ed9eba1
op_plus
id|data2
(braket
id|rbit
(braket
id|i
)braket
op_plus
l_int|12
)braket
comma
l_int|15
)paren
suffix:semicolon
)brace
id|PUT_LE32
c_func
(paren
id|outdata
comma
(paren
id|w0
op_plus
id|GET_LE32
c_func
(paren
id|r_data1
)paren
)paren
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|PUT_LE32
c_func
(paren
id|outdata
op_plus
l_int|4
comma
(paren
id|w1
op_plus
id|GET_LE32
c_func
(paren
id|r_data1
op_plus
l_int|4
)paren
)paren
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|PUT_LE32
c_func
(paren
id|outdata
op_plus
l_int|8
comma
(paren
id|w2
op_plus
id|GET_LE32
c_func
(paren
id|r_data1
op_plus
l_int|8
)paren
)paren
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|PUT_LE32
c_func
(paren
id|outdata
op_plus
l_int|12
comma
(paren
id|w3
op_plus
id|GET_LE32
c_func
(paren
id|r_data1
op_plus
l_int|12
)paren
)paren
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
)brace
multiline_comment|/* Make a signature for the current packet and add it at the end of the */
multiline_comment|/* packet. */
DECL|function|sign_packet
r_void
id|sign_packet
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_int
op_star
id|size
)paren
(brace
r_char
id|data
(braket
l_int|64
)braket
suffix:semicolon
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
l_int|64
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|data
comma
id|server-&gt;sign_root
comma
l_int|8
)paren
suffix:semicolon
id|PUT_LE32
c_func
(paren
id|data
op_plus
l_int|8
comma
(paren
op_star
id|size
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|data
op_plus
l_int|12
comma
id|server-&gt;packet
op_plus
r_sizeof
(paren
r_struct
id|ncp_request_header
)paren
op_minus
l_int|1
comma
id|min
c_func
(paren
r_int
r_int
comma
(paren
op_star
id|size
)paren
op_minus
r_sizeof
(paren
r_struct
id|ncp_request_header
)paren
op_plus
l_int|1
comma
l_int|52
)paren
)paren
suffix:semicolon
id|nwsign
c_func
(paren
id|server-&gt;sign_last
comma
id|data
comma
id|server-&gt;sign_last
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|server-&gt;packet
op_plus
(paren
op_star
id|size
)paren
comma
id|server-&gt;sign_last
comma
l_int|8
)paren
suffix:semicolon
(paren
op_star
id|size
)paren
op_add_assign
l_int|8
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_NCPFS_PACKET_SIGNING */
eof
