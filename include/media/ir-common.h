multiline_comment|/*&n; * $Id: ir-common.h,v 1.6 2004/09/15 16:15:24 kraxel Exp $&n; *&n; * some common structs and functions to handle infrared remotes via&n; * input layer ...&n; *&n; * (c) 2003 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/input.h&gt;
DECL|macro|IR_TYPE_RC5
mdefine_line|#define IR_TYPE_RC5     1
DECL|macro|IR_TYPE_OTHER
mdefine_line|#define IR_TYPE_OTHER  99
DECL|macro|IR_KEYTAB_TYPE
mdefine_line|#define IR_KEYTAB_TYPE&t;u32
DECL|macro|IR_KEYTAB_SIZE
mdefine_line|#define IR_KEYTAB_SIZE&t;128  
singleline_comment|// enougth for rc5, probably need more some day ...
DECL|macro|IR_KEYCODE
mdefine_line|#define IR_KEYCODE(tab,code)&t;(((unsigned)code &lt; IR_KEYTAB_SIZE) &bslash;&n;&t;&t;&t;&t; ? tab[code] : KEY_RESERVED)
DECL|struct|ir_input_state
r_struct
id|ir_input_state
(brace
multiline_comment|/* configuration */
DECL|member|ir_type
r_int
id|ir_type
suffix:semicolon
DECL|member|ir_codes
id|IR_KEYTAB_TYPE
id|ir_codes
(braket
id|IR_KEYTAB_SIZE
)braket
suffix:semicolon
multiline_comment|/* key info */
DECL|member|ir_raw
id|u32
id|ir_raw
suffix:semicolon
multiline_comment|/* raw data */
DECL|member|ir_key
id|u32
id|ir_key
suffix:semicolon
multiline_comment|/* ir key code */
DECL|member|keycode
id|u32
id|keycode
suffix:semicolon
multiline_comment|/* linux key code */
DECL|member|keypressed
r_int
id|keypressed
suffix:semicolon
multiline_comment|/* current state */
)brace
suffix:semicolon
r_extern
id|IR_KEYTAB_TYPE
id|ir_codes_rc5_tv
(braket
id|IR_KEYTAB_SIZE
)braket
suffix:semicolon
r_extern
id|IR_KEYTAB_TYPE
id|ir_codes_empty
(braket
id|IR_KEYTAB_SIZE
)braket
suffix:semicolon
r_void
id|ir_input_init
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|ir_input_state
op_star
id|ir
comma
r_int
id|ir_type
comma
id|IR_KEYTAB_TYPE
op_star
id|ir_codes
)paren
suffix:semicolon
r_void
id|ir_input_nokey
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|ir_input_state
op_star
id|ir
)paren
suffix:semicolon
r_void
id|ir_input_keydown
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|ir_input_state
op_star
id|ir
comma
id|u32
id|ir_key
comma
id|u32
id|ir_raw
)paren
suffix:semicolon
id|u32
id|ir_extract_bits
c_func
(paren
id|u32
id|data
comma
id|u32
id|mask
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
