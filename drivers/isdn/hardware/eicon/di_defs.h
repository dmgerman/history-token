multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef _DI_DEFS_  
DECL|macro|_DI_DEFS_
mdefine_line|#define _DI_DEFS_
multiline_comment|/* typedefs for our data structures                         */
DECL|typedef|GET_NAME
r_typedef
r_struct
id|get_name_s
id|GET_NAME
suffix:semicolon
multiline_comment|/*  The entity_s structure is used to pass all&n;    parameters between application and IDI   */
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
DECL|typedef|POSTCALL
r_typedef
r_struct
id|postcall_s
id|POSTCALL
suffix:semicolon
DECL|typedef|GET_PARA
r_typedef
r_struct
id|get_para_s
id|GET_PARA
suffix:semicolon
DECL|macro|BOARD_NAME_LENGTH
mdefine_line|#define BOARD_NAME_LENGTH 9
DECL|macro|IDI_CALL_LINK_T
mdefine_line|#define IDI_CALL_LINK_T
DECL|macro|IDI_CALL_ENTITY_T
mdefine_line|#define IDI_CALL_ENTITY_T
multiline_comment|/* typedef void ( * IDI_CALL)(ENTITY *); */
multiline_comment|/* --------------------------------------------------------&n;    IDI_CALL&n;   -------------------------------------------------------- */
DECL|typedef|IDI_CALL
r_typedef
r_void
(paren
id|IDI_CALL_LINK_T
op_star
id|IDI_CALL
)paren
(paren
id|ENTITY
id|IDI_CALL_ENTITY_T
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
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* call back */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* context pointer */
)brace
suffix:semicolon
DECL|macro|REQ_PARA
mdefine_line|#define REQ_PARA            0x0600   /* request command line parameters */
DECL|macro|REQ_PARA_LEN
mdefine_line|#define REQ_PARA_LEN             1   /* number of data bytes */
DECL|macro|L1_STARTUP_DOWN_POS
mdefine_line|#define L1_STARTUP_DOWN_POS      0   /* &squot;-y&squot; command line parameter in......*/
DECL|macro|L1_STARTUP_DOWN_MSK
mdefine_line|#define L1_STARTUP_DOWN_MSK   0x01   /* first byte position (index 0) with value 0x01 */
DECL|struct|get_para_s
r_struct
id|get_para_s
(brace
DECL|member|command
id|word
id|command
suffix:semicolon
multiline_comment|/* command = 0x0600 */
DECL|member|len
id|byte
id|len
suffix:semicolon
multiline_comment|/* max length of para field in bytes */
DECL|member|para
id|byte
id|para
(braket
id|REQ_PARA_LEN
)braket
suffix:semicolon
multiline_comment|/* parameter field */
)brace
suffix:semicolon
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
DECL|member|request
id|IDI_CALL
id|request
suffix:semicolon
DECL|typedef|DESCRIPTOR
)brace
id|DESCRIPTOR
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
DECL|macro|IDI_VADAPTER
mdefine_line|#define IDI_VADAPTER            0x40
DECL|macro|IDI_DRIVER
mdefine_line|#define IDI_DRIVER              0x80
DECL|macro|IDI_DADAPTER
mdefine_line|#define IDI_DADAPTER            0xfd
DECL|macro|IDI_DIDDPNP
mdefine_line|#define IDI_DIDDPNP             0xfe
DECL|macro|IDI_DIMAINT
mdefine_line|#define IDI_DIMAINT             0xff
multiline_comment|/* Hardware IDs ISA PNP */
DECL|macro|HW_ID_DIVA_PRO
mdefine_line|#define HW_ID_DIVA_PRO     3    /* same as IDI_ADAPTER_DIVA    */
DECL|macro|HW_ID_MAESTRA
mdefine_line|#define HW_ID_MAESTRA      4    /* same as IDI_ADAPTER_MAESTRA */
DECL|macro|HW_ID_PICCOLA
mdefine_line|#define HW_ID_PICCOLA      5
DECL|macro|HW_ID_DIVA_PRO20
mdefine_line|#define HW_ID_DIVA_PRO20   6
DECL|macro|HW_ID_DIVA20
mdefine_line|#define HW_ID_DIVA20       7
DECL|macro|HW_ID_DIVA_PRO20_U
mdefine_line|#define HW_ID_DIVA_PRO20_U 8
DECL|macro|HW_ID_DIVA20_U
mdefine_line|#define HW_ID_DIVA20_U     9
DECL|macro|HW_ID_DIVA30
mdefine_line|#define HW_ID_DIVA30       10
DECL|macro|HW_ID_DIVA30_U
mdefine_line|#define HW_ID_DIVA30_U     11
multiline_comment|/* Hardware IDs PCI */
DECL|macro|HW_ID_EICON_PCI
mdefine_line|#define HW_ID_EICON_PCI              0x1133
DECL|macro|HW_ID_SIEMENS_PCI
mdefine_line|#define HW_ID_SIEMENS_PCI            0x8001 /* unused SubVendor ID for Siemens Cornet-N cards */
DECL|macro|HW_ID_PROTTYPE_CORNETN
mdefine_line|#define HW_ID_PROTTYPE_CORNETN       0x0014 /* SubDevice ID for Siemens Cornet-N cards */
DECL|macro|HW_ID_FUJITSU_SIEMENS_PCI
mdefine_line|#define HW_ID_FUJITSU_SIEMENS_PCI    0x110A /* SubVendor ID for Fujitsu Siemens */
DECL|macro|HW_ID_GS03_PCI
mdefine_line|#define HW_ID_GS03_PCI               0x0021 /* SubDevice ID for Fujitsu Siemens ISDN S0 card */
DECL|macro|HW_ID_DIVA_PRO20_PCI
mdefine_line|#define HW_ID_DIVA_PRO20_PCI         0xe001
DECL|macro|HW_ID_DIVA20_PCI
mdefine_line|#define HW_ID_DIVA20_PCI             0xe002
DECL|macro|HW_ID_DIVA_PRO20_PCI_U
mdefine_line|#define HW_ID_DIVA_PRO20_PCI_U       0xe003
DECL|macro|HW_ID_DIVA20_PCI_U
mdefine_line|#define HW_ID_DIVA20_PCI_U           0xe004
DECL|macro|HW_ID_DIVA201_PCI
mdefine_line|#define HW_ID_DIVA201_PCI            0xe005
DECL|macro|HW_ID_DIVA_CT_ST
mdefine_line|#define HW_ID_DIVA_CT_ST             0xe006
DECL|macro|HW_ID_DIVA_CT_U
mdefine_line|#define HW_ID_DIVA_CT_U              0xe007
DECL|macro|HW_ID_DIVA_CTL_ST
mdefine_line|#define HW_ID_DIVA_CTL_ST            0xe008
DECL|macro|HW_ID_DIVA_CTL_U
mdefine_line|#define HW_ID_DIVA_CTL_U             0xe009
DECL|macro|HW_ID_DIVA_ISDN_V90_PCI
mdefine_line|#define HW_ID_DIVA_ISDN_V90_PCI      0xe00a
DECL|macro|HW_ID_DIVA202_PCI_ST
mdefine_line|#define HW_ID_DIVA202_PCI_ST         0xe00b
DECL|macro|HW_ID_DIVA202_PCI_U
mdefine_line|#define HW_ID_DIVA202_PCI_U          0xe00c
DECL|macro|HW_ID_DIVA_PRO30_PCI
mdefine_line|#define HW_ID_DIVA_PRO30_PCI         0xe00d
DECL|macro|HW_ID_MAESTRA_PCI
mdefine_line|#define HW_ID_MAESTRA_PCI            0xe010
DECL|macro|HW_ID_MAESTRAQ_PCI
mdefine_line|#define HW_ID_MAESTRAQ_PCI           0xe012
DECL|macro|HW_ID_DSRV_Q8M_V2_PCI
mdefine_line|#define HW_ID_DSRV_Q8M_V2_PCI        0xe013
DECL|macro|HW_ID_MAESTRAP_PCI
mdefine_line|#define HW_ID_MAESTRAP_PCI           0xe014
DECL|macro|HW_ID_DSRV_P30M_V2_PCI
mdefine_line|#define HW_ID_DSRV_P30M_V2_PCI       0xe015
DECL|macro|HW_ID_DSRV_VOICE_Q8M_PCI
mdefine_line|#define HW_ID_DSRV_VOICE_Q8M_PCI     0xe016
DECL|macro|HW_ID_DSRV_VOICE_Q8M_V2_PCI
mdefine_line|#define HW_ID_DSRV_VOICE_Q8M_V2_PCI  0xe017
DECL|macro|HW_ID_DSRV_B2M_V2_PCI
mdefine_line|#define HW_ID_DSRV_B2M_V2_PCI        0xe018
DECL|macro|HW_ID_DSRV_VOICE_P30M_V2_PCI
mdefine_line|#define HW_ID_DSRV_VOICE_P30M_V2_PCI 0xe019
DECL|macro|HW_ID_DSRV_B2F_PCI
mdefine_line|#define HW_ID_DSRV_B2F_PCI           0xe01a
DECL|macro|HW_ID_DSRV_VOICE_B2M_V2_PCI
mdefine_line|#define HW_ID_DSRV_VOICE_B2M_V2_PCI  0xe01b
multiline_comment|/* Hardware IDs USB */
DECL|macro|EICON_USB_VENDOR_ID
mdefine_line|#define EICON_USB_VENDOR_ID          0x071D
DECL|macro|HW_ID_DIVA_USB_REV1
mdefine_line|#define HW_ID_DIVA_USB_REV1          0x1000
DECL|macro|HW_ID_DIVA_USB_REV2
mdefine_line|#define HW_ID_DIVA_USB_REV2          0x1003
DECL|macro|HW_ID_TELEDAT_SURF_USB_REV2
mdefine_line|#define HW_ID_TELEDAT_SURF_USB_REV2  0x1004
DECL|macro|HW_ID_TELEDAT_SURF_USB_REV1
mdefine_line|#define HW_ID_TELEDAT_SURF_USB_REV1  0x2000
multiline_comment|/* --------------------------------------------------------------------------&n;  Adapter array change notification framework&n;  -------------------------------------------------------------------------- */
DECL|typedef|didd_adapter_change_callback_t
r_typedef
r_void
(paren
id|IDI_CALL_LINK_T
op_star
id|didd_adapter_change_callback_t
)paren
(paren
r_void
id|IDI_CALL_ENTITY_T
op_star
id|context
comma
id|DESCRIPTOR
op_star
id|adapter
comma
r_int
id|removal
)paren
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------------- */
DECL|macro|DI_VOICE
mdefine_line|#define DI_VOICE          0x0 /* obsolete define */
DECL|macro|DI_FAX3
mdefine_line|#define DI_FAX3           0x1
DECL|macro|DI_MODEM
mdefine_line|#define DI_MODEM          0x2
DECL|macro|DI_POST
mdefine_line|#define DI_POST           0x4
DECL|macro|DI_V110
mdefine_line|#define DI_V110           0x8
DECL|macro|DI_V120
mdefine_line|#define DI_V120           0x10
DECL|macro|DI_POTS
mdefine_line|#define DI_POTS           0x20
DECL|macro|DI_CODEC
mdefine_line|#define DI_CODEC          0x40
DECL|macro|DI_MANAGE
mdefine_line|#define DI_MANAGE         0x80
DECL|macro|DI_V_42
mdefine_line|#define DI_V_42           0x0100
DECL|macro|DI_EXTD_FAX
mdefine_line|#define DI_EXTD_FAX       0x0200 /* Extended FAX (ECM, 2D, T.6, Polling) */
DECL|macro|DI_AT_PARSER
mdefine_line|#define DI_AT_PARSER      0x0400 /* Build-in AT Parser in the L2 */
DECL|macro|DI_VOICE_OVER_IP
mdefine_line|#define DI_VOICE_OVER_IP  0x0800 /* Voice over IP support */
DECL|typedef|_IDI_CALL
r_typedef
r_void
(paren
id|IDI_CALL_LINK_T
op_star
id|_IDI_CALL
)paren
(paren
r_void
op_star
comma
id|ENTITY
op_star
)paren
suffix:semicolon
macro_line|#endif  
eof
