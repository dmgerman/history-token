multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * This source file is supplied for the exclusive use with Eicon&n; * Technology Corporation&squot;s range of DIVA Server Adapters.&n; *&n; * Eicon File Revision :    1.0  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/* External IDI interface */
macro_line|#if !defined(IDI_H)
DECL|macro|IDI_H
mdefine_line|#define IDI_H
macro_line|#include &quot;sys.h&quot;
multiline_comment|/* typedefs for our data structures */
DECL|typedef|GET_NAME
r_typedef
r_struct
id|get_name_s
id|GET_NAME
suffix:semicolon
DECL|typedef|ENTITY
r_typedef
r_struct
id|entity_s
id|ENTITY
suffix:semicolon
DECL|typedef|BUFFERS
r_typedef
r_struct
id|buffers_s
id|BUFFERS
suffix:semicolon
multiline_comment|/* IDI request/callback function pointer */
DECL|typedef|IDI_CALL
r_typedef
r_void
(paren
op_star
id|IDI_CALL
)paren
(paren
id|ENTITY
op_star
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|length
id|word
id|length
suffix:semicolon
multiline_comment|/* length of data/parameter field           */
DECL|member|P
id|byte
id|P
(braket
l_int|270
)braket
suffix:semicolon
multiline_comment|/* data/parameter field                     */
DECL|typedef|DBUFFER
)brace
id|DBUFFER
suffix:semicolon
DECL|macro|REQ_NAME
mdefine_line|#define REQ_NAME&t;0x0100
DECL|macro|BOARD_NAME_LENGTH
mdefine_line|#define BOARD_NAME_LENGTH 9
DECL|struct|get_name_s
r_struct
id|get_name_s
(brace
DECL|member|command
id|word
id|command
suffix:semicolon
multiline_comment|/* command = 0x0100 */
DECL|member|name
id|byte
id|name
(braket
id|BOARD_NAME_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|REQ_REMOVE
mdefine_line|#define REQ_REMOVE    0x0000    /* pointer to word which is 0 */
DECL|macro|REQ_SERIAL
mdefine_line|#define REQ_SERIAL    0x0200  
DECL|struct|get_serial_s
r_struct
id|get_serial_s
(brace
DECL|member|command
id|word
id|command
suffix:semicolon
multiline_comment|/* command = 0x0200 */
DECL|member|serial
id|dword
id|serial
suffix:semicolon
multiline_comment|/* serial number */
)brace
suffix:semicolon
DECL|macro|REQ_POSTCALL
mdefine_line|#define REQ_POSTCALL  0x0300  
DECL|struct|postcall_s
r_struct
id|postcall_s
(brace
DECL|member|command
id|word
id|command
suffix:semicolon
multiline_comment|/* command = 0x0300 */
DECL|member|dummy
id|word
id|dummy
suffix:semicolon
multiline_comment|/* not used */
DECL|member|callback
id|IDI_CALL
id|callback
suffix:semicolon
multiline_comment|/* routine adress to call back */
DECL|member|contxt
id|ENTITY
op_star
id|contxt
suffix:semicolon
multiline_comment|/* ptr to entity to use */
)brace
suffix:semicolon
DECL|macro|REQ_XLOG
mdefine_line|#define REQ_XLOG      0x0400   /* structure is card dependent/defined locally */
DECL|struct|buffers_s
r_struct
id|buffers_s
(brace
DECL|member|PLength
id|word
id|PLength
suffix:semicolon
DECL|member|P
id|byte
op_star
id|P
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|entity_s
r_struct
id|entity_s
(brace
DECL|member|Req
id|byte
id|Req
suffix:semicolon
multiline_comment|/* pending request          */
DECL|member|Rc
id|byte
id|Rc
suffix:semicolon
multiline_comment|/* return code received     */
DECL|member|Ind
id|byte
id|Ind
suffix:semicolon
multiline_comment|/* indication received      */
DECL|member|ReqCh
id|byte
id|ReqCh
suffix:semicolon
multiline_comment|/* channel of current Req   */
DECL|member|RcCh
id|byte
id|RcCh
suffix:semicolon
multiline_comment|/* channel of current Rc    */
DECL|member|IndCh
id|byte
id|IndCh
suffix:semicolon
multiline_comment|/* channel of current Ind   */
DECL|member|Id
id|byte
id|Id
suffix:semicolon
multiline_comment|/* ID used by this entity   */
DECL|member|GlobalId
id|byte
id|GlobalId
suffix:semicolon
multiline_comment|/* reserved field           */
DECL|member|XNum
id|byte
id|XNum
suffix:semicolon
multiline_comment|/* number of X-buffers      */
DECL|member|RNum
id|byte
id|RNum
suffix:semicolon
multiline_comment|/* number of R-buffers      */
DECL|member|X
id|BUFFERS
op_star
id|X
suffix:semicolon
multiline_comment|/* pointer to X-buffer list */
DECL|member|R
id|BUFFERS
op_star
id|R
suffix:semicolon
multiline_comment|/* pointer to R-buffer list */
DECL|member|RLength
id|word
id|RLength
suffix:semicolon
multiline_comment|/* length of current R-data */
DECL|member|RBuffer
id|DBUFFER
op_star
id|RBuffer
suffix:semicolon
multiline_comment|/* buffer of current R-data */
DECL|member|RNR
id|byte
id|RNR
suffix:semicolon
multiline_comment|/* receive not ready flag   */
DECL|member|complete
id|byte
id|complete
suffix:semicolon
multiline_comment|/* receive complete status  */
DECL|member|callback
id|IDI_CALL
id|callback
suffix:semicolon
DECL|member|user
id|word
id|user
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* fields used by the driver internally                     */
DECL|member|No
id|byte
id|No
suffix:semicolon
multiline_comment|/* entity number            */
DECL|member|reserved2
id|byte
id|reserved2
suffix:semicolon
multiline_comment|/* reserved field           */
DECL|member|More
id|byte
id|More
suffix:semicolon
multiline_comment|/* R/X More flags           */
DECL|member|MInd
id|byte
id|MInd
suffix:semicolon
multiline_comment|/* MDATA coding for this ID */
DECL|member|XCurrent
id|byte
id|XCurrent
suffix:semicolon
multiline_comment|/* current transmit buffer  */
DECL|member|RCurrent
id|byte
id|RCurrent
suffix:semicolon
multiline_comment|/* current receive buffer   */
DECL|member|XOffset
id|word
id|XOffset
suffix:semicolon
multiline_comment|/* offset in x-buffer       */
DECL|member|ROffset
id|word
id|ROffset
suffix:semicolon
multiline_comment|/* offset in r-buffer       */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|byte
id|type
suffix:semicolon
DECL|member|channels
id|byte
id|channels
suffix:semicolon
DECL|member|features
id|word
id|features
suffix:semicolon
multiline_comment|/* dword&t;&t;serial; */
DECL|member|request
id|IDI_CALL
id|request
suffix:semicolon
DECL|typedef|DESCRIPTOR
)brace
id|DESCRIPTOR
suffix:semicolon
r_extern
r_void
id|DIVA_DIDD_Read
c_func
(paren
id|DESCRIPTOR
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* descriptor type field coding */
DECL|macro|IDI_ADAPTER_S
mdefine_line|#define IDI_ADAPTER_S           1
DECL|macro|IDI_ADAPTER_PR
mdefine_line|#define IDI_ADAPTER_PR          2
DECL|macro|IDI_ADAPTER_DIVA
mdefine_line|#define IDI_ADAPTER_DIVA        3
DECL|macro|IDI_ADAPTER_MAESTRA
mdefine_line|#define IDI_ADAPTER_MAESTRA     4
DECL|macro|IDI_ADAPTER_MAESTRAQ
mdefine_line|#define IDI_ADAPTER_MAESTRAQ    5
DECL|macro|IDI_ADAPTER_MAESTRAP
mdefine_line|#define IDI_ADAPTER_MAESTRAP    6
DECL|macro|IDI_VADAPTER
mdefine_line|#define IDI_VADAPTER            0x40
DECL|macro|IDI_DRIVER
mdefine_line|#define IDI_DRIVER              0x80
DECL|macro|IDI_DIMAINT
mdefine_line|#define IDI_DIMAINT             0xff
multiline_comment|/* feature bit mask values */
DECL|macro|DI_VOICE
mdefine_line|#define DI_VOICE        0x0 /* obsolete define */
DECL|macro|DI_FAX3
mdefine_line|#define DI_FAX3         0x1
DECL|macro|DI_MODEM
mdefine_line|#define DI_MODEM        0x2
DECL|macro|DI_POST
mdefine_line|#define DI_POST         0x4
DECL|macro|DI_V110
mdefine_line|#define DI_V110         0x8
DECL|macro|DI_V120
mdefine_line|#define DI_V120         0x10
DECL|macro|DI_POTS
mdefine_line|#define DI_POTS         0x20
DECL|macro|DI_CODEC
mdefine_line|#define DI_CODEC        0x40
DECL|macro|DI_MANAGE
mdefine_line|#define DI_MANAGE       0x80
DECL|macro|DI_V_42
mdefine_line|#define DI_V_42         0x0100
DECL|macro|DI_EXTD_FAX
mdefine_line|#define DI_EXTD_FAX     0x0200 /* Extended FAX (ECM, 2D, T.6, Polling) */
macro_line|#endif /* IDI_H */
eof
