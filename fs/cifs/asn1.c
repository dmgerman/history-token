multiline_comment|/* &n; * The ASB.1/BER parsing code is derived from ip_nat_snmp_basic.c which was in&n; * turn derived from the gxsnmp package by Gregory McLean &amp; Jochen Friedrich&n; *      &n; * Copyright (c) 2000 RP Internet (www.rpi.net.au).&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
multiline_comment|/*****************************************************************************&n; *&n; * Basic ASN.1 decoding routines (gxsnmp author Dirk Wisse)&n; *&n; *****************************************************************************/
multiline_comment|/* Class */
DECL|macro|ASN1_UNI
mdefine_line|#define ASN1_UNI&t;0&t;/* Universal */
DECL|macro|ASN1_APL
mdefine_line|#define ASN1_APL&t;1&t;/* Application */
DECL|macro|ASN1_CTX
mdefine_line|#define ASN1_CTX&t;2&t;/* Context */
DECL|macro|ASN1_PRV
mdefine_line|#define ASN1_PRV&t;3&t;/* Private */
multiline_comment|/* Tag */
DECL|macro|ASN1_EOC
mdefine_line|#define ASN1_EOC&t;0&t;/* End Of Contents or N/A */
DECL|macro|ASN1_BOL
mdefine_line|#define ASN1_BOL&t;1&t;/* Boolean */
DECL|macro|ASN1_INT
mdefine_line|#define ASN1_INT&t;2&t;/* Integer */
DECL|macro|ASN1_BTS
mdefine_line|#define ASN1_BTS&t;3&t;/* Bit String */
DECL|macro|ASN1_OTS
mdefine_line|#define ASN1_OTS&t;4&t;/* Octet String */
DECL|macro|ASN1_NUL
mdefine_line|#define ASN1_NUL&t;5&t;/* Null */
DECL|macro|ASN1_OJI
mdefine_line|#define ASN1_OJI&t;6&t;/* Object Identifier  */
DECL|macro|ASN1_OJD
mdefine_line|#define ASN1_OJD&t;7&t;/* Object Description */
DECL|macro|ASN1_EXT
mdefine_line|#define ASN1_EXT&t;8&t;/* External */
DECL|macro|ASN1_SEQ
mdefine_line|#define ASN1_SEQ&t;16&t;/* Sequence */
DECL|macro|ASN1_SET
mdefine_line|#define ASN1_SET&t;17&t;/* Set */
DECL|macro|ASN1_NUMSTR
mdefine_line|#define ASN1_NUMSTR&t;18&t;/* Numerical String */
DECL|macro|ASN1_PRNSTR
mdefine_line|#define ASN1_PRNSTR&t;19&t;/* Printable String */
DECL|macro|ASN1_TEXSTR
mdefine_line|#define ASN1_TEXSTR&t;20&t;/* Teletext String */
DECL|macro|ASN1_VIDSTR
mdefine_line|#define ASN1_VIDSTR&t;21&t;/* Video String */
DECL|macro|ASN1_IA5STR
mdefine_line|#define ASN1_IA5STR&t;22&t;/* IA5 String */
DECL|macro|ASN1_UNITIM
mdefine_line|#define ASN1_UNITIM&t;23&t;/* Universal Time */
DECL|macro|ASN1_GENTIM
mdefine_line|#define ASN1_GENTIM&t;24&t;/* General Time */
DECL|macro|ASN1_GRASTR
mdefine_line|#define ASN1_GRASTR&t;25&t;/* Graphical String */
DECL|macro|ASN1_VISSTR
mdefine_line|#define ASN1_VISSTR&t;26&t;/* Visible String */
DECL|macro|ASN1_GENSTR
mdefine_line|#define ASN1_GENSTR&t;27&t;/* General String */
multiline_comment|/* Primitive / Constructed methods*/
DECL|macro|ASN1_PRI
mdefine_line|#define ASN1_PRI&t;0&t;/* Primitive */
DECL|macro|ASN1_CON
mdefine_line|#define ASN1_CON&t;1&t;/* Constructed */
multiline_comment|/*&n; * Error codes.&n; */
DECL|macro|ASN1_ERR_NOERROR
mdefine_line|#define ASN1_ERR_NOERROR&t;&t;0
DECL|macro|ASN1_ERR_DEC_EMPTY
mdefine_line|#define ASN1_ERR_DEC_EMPTY&t;&t;2
DECL|macro|ASN1_ERR_DEC_EOC_MISMATCH
mdefine_line|#define ASN1_ERR_DEC_EOC_MISMATCH&t;3
DECL|macro|ASN1_ERR_DEC_LENGTH_MISMATCH
mdefine_line|#define ASN1_ERR_DEC_LENGTH_MISMATCH&t;4
DECL|macro|ASN1_ERR_DEC_BADVALUE
mdefine_line|#define ASN1_ERR_DEC_BADVALUE&t;&t;5
DECL|macro|SPNEGO_OID_LEN
mdefine_line|#define SPNEGO_OID_LEN 7
DECL|macro|NTLMSSP_OID_LEN
mdefine_line|#define NTLMSSP_OID_LEN  10
DECL|variable|SPNEGO_OID
r_int
r_int
id|SPNEGO_OID
(braket
l_int|7
)braket
op_assign
(brace
l_int|1
comma
l_int|3
comma
l_int|6
comma
l_int|1
comma
l_int|5
comma
l_int|5
comma
l_int|2
)brace
suffix:semicolon
DECL|variable|NTLMSSP_OID
r_int
r_int
id|NTLMSSP_OID
(braket
l_int|10
)braket
op_assign
(brace
l_int|1
comma
l_int|3
comma
l_int|6
comma
l_int|1
comma
l_int|4
comma
l_int|1
comma
l_int|311
comma
l_int|2
comma
l_int|2
comma
l_int|10
)brace
suffix:semicolon
multiline_comment|/* &n; * ASN.1 context.&n; */
DECL|struct|asn1_ctx
r_struct
id|asn1_ctx
(brace
DECL|member|error
r_int
id|error
suffix:semicolon
multiline_comment|/* Error condition */
DECL|member|pointer
r_int
r_char
op_star
id|pointer
suffix:semicolon
multiline_comment|/* Octet just to be decoded */
DECL|member|begin
r_int
r_char
op_star
id|begin
suffix:semicolon
multiline_comment|/* First octet */
DECL|member|end
r_int
r_char
op_star
id|end
suffix:semicolon
multiline_comment|/* Octet after last octet */
)brace
suffix:semicolon
multiline_comment|/*&n; * Octet string (not null terminated)&n; */
DECL|struct|asn1_octstr
r_struct
id|asn1_octstr
(brace
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
DECL|function|asn1_open
id|asn1_open
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
id|ctx-&gt;begin
op_assign
id|buf
suffix:semicolon
id|ctx-&gt;end
op_assign
id|buf
op_plus
id|len
suffix:semicolon
id|ctx-&gt;pointer
op_assign
id|buf
suffix:semicolon
id|ctx-&gt;error
op_assign
id|ASN1_ERR_NOERROR
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|asn1_octet_decode
id|asn1_octet_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_char
op_star
id|ch
)paren
(brace
r_if
c_cond
(paren
id|ctx-&gt;pointer
op_ge
id|ctx-&gt;end
)paren
(brace
id|ctx-&gt;error
op_assign
id|ASN1_ERR_DEC_EMPTY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|ch
op_assign
op_star
(paren
id|ctx-&gt;pointer
)paren
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|asn1_tag_decode
id|asn1_tag_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_int
op_star
id|tag
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
op_star
id|tag
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|asn1_octet_decode
c_func
(paren
id|ctx
comma
op_amp
id|ch
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|tag
op_lshift_assign
l_int|7
suffix:semicolon
op_star
id|tag
op_or_assign
id|ch
op_amp
l_int|0x7F
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|ch
op_amp
l_int|0x80
)paren
op_eq
l_int|0x80
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|asn1_id_decode
id|asn1_id_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_int
op_star
id|cls
comma
r_int
r_int
op_star
id|con
comma
r_int
r_int
op_star
id|tag
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asn1_octet_decode
c_func
(paren
id|ctx
comma
op_amp
id|ch
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|cls
op_assign
(paren
id|ch
op_amp
l_int|0xC0
)paren
op_rshift
l_int|6
suffix:semicolon
op_star
id|con
op_assign
(paren
id|ch
op_amp
l_int|0x20
)paren
op_rshift
l_int|5
suffix:semicolon
op_star
id|tag
op_assign
(paren
id|ch
op_amp
l_int|0x1F
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|tag
op_eq
l_int|0x1F
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|asn1_tag_decode
c_func
(paren
id|ctx
comma
id|tag
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|asn1_length_decode
id|asn1_length_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_int
op_star
id|def
comma
r_int
r_int
op_star
id|len
)paren
(brace
r_int
r_char
id|ch
comma
id|cnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asn1_octet_decode
c_func
(paren
id|ctx
comma
op_amp
id|ch
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_int|0x80
)paren
op_star
id|def
op_assign
l_int|0
suffix:semicolon
r_else
(brace
op_star
id|def
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ch
OL
l_int|0x80
)paren
op_star
id|len
op_assign
id|ch
suffix:semicolon
r_else
(brace
id|cnt
op_assign
(paren
r_int
r_char
)paren
(paren
id|ch
op_amp
l_int|0x7F
)paren
suffix:semicolon
op_star
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cnt
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|asn1_octet_decode
c_func
(paren
id|ctx
comma
op_amp
id|ch
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|len
op_lshift_assign
l_int|8
suffix:semicolon
op_star
id|len
op_or_assign
id|ch
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|asn1_header_decode
id|asn1_header_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_char
op_star
op_star
id|eoc
comma
r_int
r_int
op_star
id|cls
comma
r_int
r_int
op_star
id|con
comma
r_int
r_int
op_star
id|tag
)paren
(brace
r_int
r_int
id|def
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asn1_id_decode
c_func
(paren
id|ctx
comma
id|cls
comma
id|con
comma
id|tag
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asn1_length_decode
c_func
(paren
id|ctx
comma
op_amp
id|def
comma
op_amp
id|len
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|def
)paren
op_star
id|eoc
op_assign
id|ctx-&gt;pointer
op_plus
id|len
suffix:semicolon
r_else
op_star
id|eoc
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|asn1_eoc_decode
id|asn1_eoc_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_char
op_star
id|eoc
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|eoc
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|asn1_octet_decode
c_func
(paren
id|ctx
comma
op_amp
id|ch
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ne
l_int|0x00
)paren
(brace
id|ctx-&gt;error
op_assign
id|ASN1_ERR_DEC_EOC_MISMATCH
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|asn1_octet_decode
c_func
(paren
id|ctx
comma
op_amp
id|ch
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ne
l_int|0x00
)paren
(brace
id|ctx-&gt;error
op_assign
id|ASN1_ERR_DEC_EOC_MISMATCH
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ctx-&gt;pointer
op_ne
id|eoc
)paren
(brace
id|ctx-&gt;error
op_assign
id|ASN1_ERR_DEC_LENGTH_MISMATCH
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* static unsigned char asn1_null_decode(struct asn1_ctx *ctx,&n;&t;&t;&t;&t;      unsigned char *eoc)&n;{&n;&t;ctx-&gt;pointer = eoc;&n;&t;return 1;&n;}&n;&n;static unsigned char asn1_long_decode(struct asn1_ctx *ctx,&n;&t;&t;&t;&t;      unsigned char *eoc, long *integer)&n;{&n;&t;unsigned char ch;&n;&t;unsigned int len;&n;&n;&t;if (!asn1_octet_decode(ctx, &amp;ch))&n;&t;&t;return 0;&n;&n;&t;*integer = (signed char) ch;&n;&t;len = 1;&n;&n;&t;while (ctx-&gt;pointer &lt; eoc) {&n;&t;&t;if (++len &gt; sizeof(long)) {&n;&t;&t;&t;ctx-&gt;error = ASN1_ERR_DEC_BADVALUE;&n;&t;&t;&t;return 0;&n;&t;&t;}&n;&n;&t;&t;if (!asn1_octet_decode(ctx, &amp;ch))&n;&t;&t;&t;return 0;&n;&n;&t;&t;*integer &lt;&lt;= 8;&n;&t;&t;*integer |= ch;&n;&t;}&n;&t;return 1;&n;}&n;&n;static unsigned char asn1_uint_decode(struct asn1_ctx *ctx,&n;&t;&t;&t;&t;      unsigned char *eoc,&n;&t;&t;&t;&t;      unsigned int *integer)&n;{&n;&t;unsigned char ch;&n;&t;unsigned int len;&n;&n;&t;if (!asn1_octet_decode(ctx, &amp;ch))&n;&t;&t;return 0;&n;&n;&t;*integer = ch;&n;&t;if (ch == 0)&n;&t;&t;len = 0;&n;&t;else&n;&t;&t;len = 1;&n;&n;&t;while (ctx-&gt;pointer &lt; eoc) {&n;&t;&t;if (++len &gt; sizeof(unsigned int)) {&n;&t;&t;&t;ctx-&gt;error = ASN1_ERR_DEC_BADVALUE;&n;&t;&t;&t;return 0;&n;&t;&t;}&n;&n;&t;&t;if (!asn1_octet_decode(ctx, &amp;ch))&n;&t;&t;&t;return 0;&n;&n;&t;&t;*integer &lt;&lt;= 8;&n;&t;&t;*integer |= ch;&n;&t;}&n;&t;return 1;&n;}&n;&n;static unsigned char asn1_ulong_decode(struct asn1_ctx *ctx,&n;&t;&t;&t;&t;       unsigned char *eoc,&n;&t;&t;&t;&t;       unsigned long *integer)&n;{&n;&t;unsigned char ch;&n;&t;unsigned int len;&n;&n;&t;if (!asn1_octet_decode(ctx, &amp;ch))&n;&t;&t;return 0;&n;&n;&t;*integer = ch;&n;&t;if (ch == 0)&n;&t;&t;len = 0;&n;&t;else&n;&t;&t;len = 1;&n;&n;&t;while (ctx-&gt;pointer &lt; eoc) {&n;&t;&t;if (++len &gt; sizeof(unsigned long)) {&n;&t;&t;&t;ctx-&gt;error = ASN1_ERR_DEC_BADVALUE;&n;&t;&t;&t;return 0;&n;&t;&t;}&n;&n;&t;&t;if (!asn1_octet_decode(ctx, &amp;ch))&n;&t;&t;&t;return 0;&n;&n;&t;&t;*integer &lt;&lt;= 8;&n;&t;&t;*integer |= ch;&n;&t;}&n;&t;return 1;&n;} &n;&n;static unsigned char&n;asn1_octets_decode(struct asn1_ctx *ctx,&n;&t;&t;   unsigned char *eoc,&n;&t;&t;   unsigned char **octets, unsigned int *len)&n;{&n;&t;unsigned char *ptr;&n;&n;&t;*len = 0;&n;&n;&t;*octets = kmalloc(eoc - ctx-&gt;pointer, GFP_ATOMIC);&n;&t;if (*octets == NULL) {&n;&t;&t;return 0;&n;&t;}&n;&n;&t;ptr = *octets;&n;&t;while (ctx-&gt;pointer &lt; eoc) {&n;&t;&t;if (!asn1_octet_decode(ctx, (unsigned char *) ptr++)) {&n;&t;&t;&t;kfree(*octets);&n;&t;&t;&t;*octets = NULL;&n;&t;&t;&t;return 0;&n;&t;&t;}&n;&t;&t;(*len)++;&n;&t;}&n;&t;return 1;&n;} */
r_static
r_int
r_char
DECL|function|asn1_subid_decode
id|asn1_subid_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_int
op_star
id|subid
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
op_star
id|subid
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|asn1_octet_decode
c_func
(paren
id|ctx
comma
op_amp
id|ch
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|subid
op_lshift_assign
l_int|7
suffix:semicolon
op_star
id|subid
op_or_assign
id|ch
op_amp
l_int|0x7F
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|ch
op_amp
l_int|0x80
)paren
op_eq
l_int|0x80
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|asn1_oid_decode
id|asn1_oid_decode
c_func
(paren
r_struct
id|asn1_ctx
op_star
id|ctx
comma
r_int
r_char
op_star
id|eoc
comma
r_int
r_int
op_star
op_star
id|oid
comma
r_int
r_int
op_star
id|len
)paren
(brace
r_int
r_int
id|subid
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
op_star
id|optr
suffix:semicolon
id|size
op_assign
id|eoc
op_minus
id|ctx-&gt;pointer
op_plus
l_int|1
suffix:semicolon
op_star
id|oid
op_assign
id|kmalloc
c_func
(paren
id|size
op_star
r_sizeof
(paren
r_int
r_int
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|oid
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|optr
op_assign
op_star
id|oid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asn1_subid_decode
c_func
(paren
id|ctx
comma
op_amp
id|subid
)paren
)paren
(brace
id|kfree
c_func
(paren
op_star
id|oid
)paren
suffix:semicolon
op_star
id|oid
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|subid
OL
l_int|40
)paren
(brace
id|optr
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|optr
(braket
l_int|1
)braket
op_assign
id|subid
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|subid
OL
l_int|80
)paren
(brace
id|optr
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|optr
(braket
l_int|1
)braket
op_assign
id|subid
op_minus
l_int|40
suffix:semicolon
)brace
r_else
(brace
id|optr
(braket
l_int|0
)braket
op_assign
l_int|2
suffix:semicolon
id|optr
(braket
l_int|1
)braket
op_assign
id|subid
op_minus
l_int|80
suffix:semicolon
)brace
op_star
id|len
op_assign
l_int|2
suffix:semicolon
id|optr
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|ctx-&gt;pointer
OL
id|eoc
)paren
(brace
r_if
c_cond
(paren
op_increment
(paren
op_star
id|len
)paren
OG
id|size
)paren
(brace
id|ctx-&gt;error
op_assign
id|ASN1_ERR_DEC_BADVALUE
suffix:semicolon
id|kfree
c_func
(paren
op_star
id|oid
)paren
suffix:semicolon
op_star
id|oid
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|asn1_subid_decode
c_func
(paren
id|ctx
comma
id|optr
op_increment
)paren
)paren
(brace
id|kfree
c_func
(paren
op_star
id|oid
)paren
suffix:semicolon
op_star
id|oid
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|compare_oid
id|compare_oid
c_func
(paren
r_int
r_int
op_star
id|oid1
comma
r_int
r_int
id|oid1len
comma
r_int
r_int
op_star
id|oid2
comma
r_int
r_int
id|oid2len
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|oid1len
op_ne
id|oid2len
)paren
r_return
l_int|0
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|oid1len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|oid1
(braket
id|i
)braket
op_ne
id|oid2
(braket
id|i
)braket
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* BB check for endian conversion issues here */
r_int
DECL|function|decode_negTokenInit
id|decode_negTokenInit
c_func
(paren
r_int
r_char
op_star
id|security_blob
comma
r_int
id|length
comma
r_enum
id|securityEnum
op_star
id|secType
)paren
(brace
r_struct
id|asn1_ctx
id|ctx
suffix:semicolon
r_int
r_char
op_star
id|end
suffix:semicolon
r_int
r_char
op_star
id|sequence_end
suffix:semicolon
r_int
r_int
op_star
id|oid
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|cls
comma
id|con
comma
id|tag
comma
id|oidlen
comma
id|rc
suffix:semicolon
r_int
id|use_ntlmssp
op_assign
id|FALSE
suffix:semicolon
op_star
id|secType
op_assign
id|NTLM
suffix:semicolon
multiline_comment|/* BB eventually make Kerberos or NLTMSSP the default */
multiline_comment|/* cifs_dump_mem(&quot; Received SecBlob &quot;, security_blob, length); */
id|asn1_open
c_func
(paren
op_amp
id|ctx
comma
id|security_blob
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding negTokenInit header &quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_APL
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
op_logical_or
(paren
id|tag
op_ne
id|ASN1_EOC
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cls = %d con = %d tag = %d&quot;
comma
id|cls
comma
id|con
comma
id|tag
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*      remember to free obj-&gt;oid */
id|rc
op_assign
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_if
c_cond
(paren
(paren
id|tag
op_eq
id|ASN1_OJI
)paren
op_logical_and
(paren
id|cls
op_eq
id|ASN1_PRI
)paren
)paren
(brace
id|rc
op_assign
id|asn1_oid_decode
c_func
(paren
op_amp
id|ctx
comma
id|end
comma
op_amp
id|oid
comma
op_amp
id|oidlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|rc
op_assign
id|compare_oid
c_func
(paren
id|oid
comma
id|oidlen
comma
id|SPNEGO_OID
comma
id|SPNEGO_OID_LEN
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|oid
)paren
suffix:semicolon
)brace
)brace
r_else
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding negTokenInit header&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding negTokenInit &quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_CTX
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
op_logical_or
(paren
id|tag
op_ne
id|ASN1_EOC
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cls = %d con = %d tag = %d end = %p (%d) exit 0&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding negTokenInit &quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_UNI
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
op_logical_or
(paren
id|tag
op_ne
id|ASN1_SEQ
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cls = %d con = %d tag = %d end = %p (%d) exit 1&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding 2nd part of negTokenInit &quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_CTX
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
op_logical_or
(paren
id|tag
op_ne
id|ASN1_EOC
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cls = %d con = %d tag = %d end = %p (%d) exit 0&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asn1_header_decode
(paren
op_amp
id|ctx
comma
op_amp
id|sequence_end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding 2nd part of negTokenInit &quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_UNI
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
op_logical_or
(paren
id|tag
op_ne
id|ASN1_SEQ
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cls = %d con = %d tag = %d end = %p (%d) exit 1&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|asn1_eoc_decode
c_func
(paren
op_amp
id|ctx
comma
id|sequence_end
)paren
)paren
(brace
id|rc
op_assign
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error 1 decoding negTokenInit header exit 2&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tag
op_eq
id|ASN1_OJI
)paren
op_logical_and
(paren
id|con
op_eq
id|ASN1_PRI
)paren
)paren
(brace
id|rc
op_assign
id|asn1_oid_decode
c_func
(paren
op_amp
id|ctx
comma
id|end
comma
op_amp
id|oid
comma
op_amp
id|oidlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;OID len = %d oid = 0x%lx 0x%lx 0x%lx 0x%lx&quot;
comma
id|oidlen
comma
op_star
id|oid
comma
op_star
(paren
id|oid
op_plus
l_int|1
)paren
comma
op_star
(paren
id|oid
op_plus
l_int|2
)paren
comma
op_star
(paren
id|oid
op_plus
l_int|3
)paren
)paren
)paren
suffix:semicolon
id|rc
op_assign
id|compare_oid
c_func
(paren
id|oid
comma
id|oidlen
comma
id|NTLMSSP_OID
comma
id|NTLMSSP_OID_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oid
)paren
(brace
id|kfree
c_func
(paren
id|oid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
)paren
id|use_ntlmssp
op_assign
id|TRUE
suffix:semicolon
)brace
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;This should be an oid what is going on? &quot;
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding last part of negTokenInit exit 3&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_CTX
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
)paren
(brace
multiline_comment|/* tag = 3 indicating mechListMIC */
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Exit 4 cls = %d con = %d tag = %d end = %p (%d)&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding last part of negTokenInit exit 5&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_UNI
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
op_logical_or
(paren
id|tag
op_ne
id|ASN1_SEQ
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Exit 6 cls = %d con = %d tag = %d end = %p (%d)&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding last part of negTokenInit exit 7&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_CTX
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_CON
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Exit 8 cls = %d con = %d tag = %d end = %p (%d)&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asn1_header_decode
c_func
(paren
op_amp
id|ctx
comma
op_amp
id|end
comma
op_amp
id|cls
comma
op_amp
id|con
comma
op_amp
id|tag
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error decoding last part of negTokenInit exit 9&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cls
op_ne
id|ASN1_UNI
)paren
op_logical_or
(paren
id|con
op_ne
id|ASN1_PRI
)paren
op_logical_or
(paren
id|tag
op_ne
id|ASN1_GENSTR
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Exit 10 cls = %d con = %d tag = %d end = %p (%d)&quot;
comma
id|cls
comma
id|con
comma
id|tag
comma
id|end
comma
op_star
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Need to call asn1_octets_decode() function for this %s&quot;
comma
id|ctx.pointer
)paren
)paren
suffix:semicolon
multiline_comment|/* is this UTF-8 or ASCII? */
)brace
multiline_comment|/* if (use_kerberos) &n;&t;   *secType = Kerberos &n;&t;   else */
r_if
c_cond
(paren
id|use_ntlmssp
)paren
(brace
op_star
id|secType
op_assign
id|NTLMSSP
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
