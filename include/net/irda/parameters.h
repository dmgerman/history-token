multiline_comment|/*********************************************************************&n; *                &n; * Filename:      parameters.h&n; * Version:       1.0&n; * Description:   A more general way to handle (pi,pl,pv) parameters&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Jun  7 08:47:28 1999&n; * Modified at:   Sun Jan 30 14:05:14 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999-2000 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *&n; *     Michel D&#xfffd;nzer &lt;daenzer@debian.org&gt;, 10/2001&n; *     - simplify irda_pv_t to avoid endianness issues&n; *     &n; ********************************************************************/
macro_line|#ifndef IRDA_PARAMS_H
DECL|macro|IRDA_PARAMS_H
mdefine_line|#define IRDA_PARAMS_H
multiline_comment|/*&n; *  The currently supported types. Beware not to change the sequence since&n; *  it a good reason why the sized integers has a value equal to their size&n; */
r_typedef
r_enum
(brace
DECL|enumerator|PV_INTEGER
id|PV_INTEGER
comma
multiline_comment|/* Integer of any (pl) length */
DECL|enumerator|PV_INT_8_BITS
id|PV_INT_8_BITS
comma
multiline_comment|/* Integer of 8 bits in length */
DECL|enumerator|PV_INT_16_BITS
id|PV_INT_16_BITS
comma
multiline_comment|/* Integer of 16 bits in length */
DECL|enumerator|PV_STRING
id|PV_STRING
comma
multiline_comment|/* &bslash;0 terminated string */
DECL|enumerator|PV_INT_32_BITS
id|PV_INT_32_BITS
comma
multiline_comment|/* Integer of 32 bits in length */
DECL|enumerator|PV_OCT_SEQ
id|PV_OCT_SEQ
comma
multiline_comment|/* Octet sequence */
DECL|enumerator|PV_NO_VALUE
id|PV_NO_VALUE
multiline_comment|/* Does not contain any value (pl=0) */
DECL|typedef|PV_TYPE
)brace
id|PV_TYPE
suffix:semicolon
multiline_comment|/* Bit 7 of type field */
DECL|macro|PV_BIG_ENDIAN
mdefine_line|#define PV_BIG_ENDIAN    0x80 
DECL|macro|PV_LITTLE_ENDIAN
mdefine_line|#define PV_LITTLE_ENDIAN 0x00
DECL|macro|PV_MASK
mdefine_line|#define PV_MASK          0x7f   /* To mask away endian bit */
DECL|macro|PV_PUT
mdefine_line|#define PV_PUT 0
DECL|macro|PV_GET
mdefine_line|#define PV_GET 1
r_typedef
r_union
(brace
DECL|member|c
r_char
op_star
id|c
suffix:semicolon
DECL|member|i
id|__u32
id|i
suffix:semicolon
DECL|member|ip
id|__u32
op_star
id|ip
suffix:semicolon
DECL|typedef|irda_pv_t
)brace
id|irda_pv_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pi
id|__u8
id|pi
suffix:semicolon
DECL|member|pl
id|__u8
id|pl
suffix:semicolon
DECL|member|pv
id|irda_pv_t
id|pv
suffix:semicolon
DECL|typedef|irda_param_t
)brace
id|irda_param_t
suffix:semicolon
DECL|typedef|PI_HANDLER
r_typedef
r_int
(paren
op_star
id|PI_HANDLER
)paren
(paren
r_void
op_star
id|self
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
DECL|typedef|PV_HANDLER
r_typedef
r_int
(paren
op_star
id|PV_HANDLER
)paren
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|func
id|PI_HANDLER
id|func
suffix:semicolon
multiline_comment|/* Handler for this parameter identifier */
DECL|member|type
id|PV_TYPE
id|type
suffix:semicolon
multiline_comment|/* Data type for this parameter */
DECL|typedef|pi_minor_info_t
)brace
id|pi_minor_info_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pi_minor_call_table
id|pi_minor_info_t
op_star
id|pi_minor_call_table
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|typedef|pi_major_info_t
)brace
id|pi_major_info_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|tables
id|pi_major_info_t
op_star
id|tables
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|pi_mask
id|__u8
id|pi_mask
suffix:semicolon
DECL|member|pi_major_offset
r_int
id|pi_major_offset
suffix:semicolon
DECL|typedef|pi_param_info_t
)brace
id|pi_param_info_t
suffix:semicolon
r_int
id|irda_param_pack
c_func
(paren
id|__u8
op_star
id|buf
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|irda_param_insert
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
id|pi
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|pi_param_info_t
op_star
id|info
)paren
suffix:semicolon
r_int
id|irda_param_extract_all
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|pi_param_info_t
op_star
id|info
)paren
suffix:semicolon
DECL|macro|irda_param_insert_byte
mdefine_line|#define irda_param_insert_byte(buf,pi,pv) irda_param_pack(buf,&quot;bbb&quot;,pi,1,pv)
macro_line|#endif /* IRDA_PARAMS_H */
eof
