multiline_comment|/* $Id: socksys.h,v 1.2 1998/03/26 08:46:07 jj Exp $&n; * socksys.h: Definitions for STREAMS modules emulation code.&n; *&n; * Copyright (C) 1998 Patrik Rak (prak3264@ss1000.ms.mff.cuni.cz)&n; */
DECL|macro|MSG_HIPRI
mdefine_line|#define MSG_HIPRI&t;0x01
DECL|macro|MSG_ANY
mdefine_line|#define MSG_ANY&t;&t;0x02
DECL|macro|MSG_BAND
mdefine_line|#define MSG_BAND&t;0x04
DECL|macro|MORECTL
mdefine_line|#define MORECTL&t;&t;1
DECL|macro|MOREDATA
mdefine_line|#define MOREDATA&t;2
DECL|macro|TBADADDR
mdefine_line|#define&t;TBADADDR&t;&t;1
DECL|macro|TBADOPT
mdefine_line|#define&t;TBADOPT&t;&t;&t;2
DECL|macro|TACCES
mdefine_line|#define&t;TACCES&t;&t;&t;3
DECL|macro|TBADF
mdefine_line|#define TBADF&t;&t;&t;4
DECL|macro|TNOADDR
mdefine_line|#define TNOADDR&t;&t;&t;5
DECL|macro|TOUTSTATE
mdefine_line|#define TOUTSTATE&t;        6
DECL|macro|TBADSEQ
mdefine_line|#define TBADSEQ&t;&t;        7
DECL|macro|TSYSERR
mdefine_line|#define TSYSERR&t;&t;&t;8
DECL|macro|TLOOK
mdefine_line|#define TLOOK&t;&t;        9
DECL|macro|TBADDATA
mdefine_line|#define TBADDATA&t;       10
DECL|macro|TBUFOVFLW
mdefine_line|#define TBUFOVFLW&t;       11
DECL|macro|TFLOW
mdefine_line|#define TFLOW&t;&t;       12
DECL|macro|TNODATA
mdefine_line|#define&t;TNODATA&t;&t;       13
DECL|macro|TNODIS
mdefine_line|#define TNODIS&t;&t;       14
DECL|macro|TNOUDERR
mdefine_line|#define TNOUDERR&t;       15
DECL|macro|TBADFLAG
mdefine_line|#define TBADFLAG&t;       16
DECL|macro|TNOREL
mdefine_line|#define TNOREL&t;&t;       17
DECL|macro|TNOTSUPPORT
mdefine_line|#define TNOTSUPPORT&t;       18
DECL|macro|TSTATECHNG
mdefine_line|#define TSTATECHNG&t;       19
DECL|macro|T_CONN_REQ
mdefine_line|#define T_CONN_REQ      0
DECL|macro|T_CONN_RES
mdefine_line|#define T_CONN_RES      1
DECL|macro|T_DISCON_REQ
mdefine_line|#define T_DISCON_REQ    2
DECL|macro|T_DATA_REQ
mdefine_line|#define T_DATA_REQ      3
DECL|macro|T_EXDATA_REQ
mdefine_line|#define T_EXDATA_REQ    4
DECL|macro|T_INFO_REQ
mdefine_line|#define T_INFO_REQ      5
DECL|macro|T_BIND_REQ
mdefine_line|#define T_BIND_REQ      6
DECL|macro|T_UNBIND_REQ
mdefine_line|#define T_UNBIND_REQ    7
DECL|macro|T_UNITDATA_REQ
mdefine_line|#define T_UNITDATA_REQ  8
DECL|macro|T_OPTMGMT_REQ
mdefine_line|#define T_OPTMGMT_REQ   9
DECL|macro|T_ORDREL_REQ
mdefine_line|#define T_ORDREL_REQ    10
DECL|macro|T_CONN_IND
mdefine_line|#define T_CONN_IND      11
DECL|macro|T_CONN_CON
mdefine_line|#define T_CONN_CON      12
DECL|macro|T_DISCON_IND
mdefine_line|#define T_DISCON_IND    13
DECL|macro|T_DATA_IND
mdefine_line|#define T_DATA_IND      14
DECL|macro|T_EXDATA_IND
mdefine_line|#define T_EXDATA_IND    15
DECL|macro|T_INFO_ACK
mdefine_line|#define T_INFO_ACK      16
DECL|macro|T_BIND_ACK
mdefine_line|#define T_BIND_ACK      17
DECL|macro|T_ERROR_ACK
mdefine_line|#define T_ERROR_ACK     18
DECL|macro|T_OK_ACK
mdefine_line|#define T_OK_ACK        19
DECL|macro|T_UNITDATA_IND
mdefine_line|#define T_UNITDATA_IND  20
DECL|macro|T_UDERROR_IND
mdefine_line|#define T_UDERROR_IND   21
DECL|macro|T_OPTMGMT_ACK
mdefine_line|#define T_OPTMGMT_ACK   22
DECL|macro|T_ORDREL_IND
mdefine_line|#define T_ORDREL_IND    23
DECL|macro|T_NEGOTIATE
mdefine_line|#define T_NEGOTIATE&t;0x0004
DECL|macro|T_FAILURE
mdefine_line|#define T_FAILURE&t;0x0040
DECL|macro|TS_UNBND
mdefine_line|#define TS_UNBND&t;0&t;/* unbound */
DECL|macro|TS_WACK_BREQ
mdefine_line|#define&t;TS_WACK_BREQ&t;1&t;/* waiting for T_BIND_REQ ack  */
DECL|macro|TS_WACK_UREQ
mdefine_line|#define TS_WACK_UREQ&t;2&t;/* waiting for T_UNBIND_REQ ack */
DECL|macro|TS_IDLE
mdefine_line|#define TS_IDLE&t;&t;3&t;/* idle */
DECL|macro|TS_WACK_OPTREQ
mdefine_line|#define TS_WACK_OPTREQ&t;4&t;/* waiting for T_OPTMGMT_REQ ack */
DECL|macro|TS_WACK_CREQ
mdefine_line|#define TS_WACK_CREQ&t;5&t;/* waiting for T_CONN_REQ ack */
DECL|macro|TS_WCON_CREQ
mdefine_line|#define TS_WCON_CREQ&t;6&t;/* waiting for T_CONN_REQ confirmation */
DECL|macro|TS_WRES_CIND
mdefine_line|#define&t;TS_WRES_CIND&t;7&t;/* waiting for T_CONN_IND */
DECL|macro|TS_WACK_CRES
mdefine_line|#define TS_WACK_CRES&t;8&t;/* waiting for T_CONN_RES ack */
DECL|macro|TS_DATA_XFER
mdefine_line|#define TS_DATA_XFER&t;9&t;/* data transfer */
DECL|macro|TS_WIND_ORDREL
mdefine_line|#define TS_WIND_ORDREL&t;10&t;/* releasing read but not write */
DECL|macro|TS_WREQ_ORDREL
mdefine_line|#define TS_WREQ_ORDREL&t;11      /* wait to release write but not read */
DECL|macro|TS_WACK_DREQ6
mdefine_line|#define TS_WACK_DREQ6&t;12&t;/* waiting for T_DISCON_REQ ack */
DECL|macro|TS_WACK_DREQ7
mdefine_line|#define TS_WACK_DREQ7&t;13&t;/* waiting for T_DISCON_REQ ack */
DECL|macro|TS_WACK_DREQ9
mdefine_line|#define TS_WACK_DREQ9&t;14&t;/* waiting for T_DISCON_REQ ack */
DECL|macro|TS_WACK_DREQ10
mdefine_line|#define TS_WACK_DREQ10&t;15&t;/* waiting for T_DISCON_REQ ack */
DECL|macro|TS_WACK_DREQ11
mdefine_line|#define TS_WACK_DREQ11&t;16&t;/* waiting for T_DISCON_REQ ack */
DECL|macro|TS_NOSTATES
mdefine_line|#define TS_NOSTATES&t;17
DECL|struct|T_conn_req
r_struct
id|T_conn_req
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|DEST_length
id|s32
id|DEST_length
suffix:semicolon
DECL|member|DEST_offset
id|s32
id|DEST_offset
suffix:semicolon
DECL|member|OPT_length
id|s32
id|OPT_length
suffix:semicolon
DECL|member|OPT_offset
id|s32
id|OPT_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_bind_req
r_struct
id|T_bind_req
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|ADDR_length
id|s32
id|ADDR_length
suffix:semicolon
DECL|member|ADDR_offset
id|s32
id|ADDR_offset
suffix:semicolon
DECL|member|CONIND_number
id|u32
id|CONIND_number
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_unitdata_req
r_struct
id|T_unitdata_req
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|DEST_length
id|s32
id|DEST_length
suffix:semicolon
DECL|member|DEST_offset
id|s32
id|DEST_offset
suffix:semicolon
DECL|member|OPT_length
id|s32
id|OPT_length
suffix:semicolon
DECL|member|OPT_offset
id|s32
id|OPT_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_optmgmt_req
r_struct
id|T_optmgmt_req
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|OPT_length
id|s32
id|OPT_length
suffix:semicolon
DECL|member|OPT_offset
id|s32
id|OPT_offset
suffix:semicolon
DECL|member|MGMT_flags
id|s32
id|MGMT_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_bind_ack
r_struct
id|T_bind_ack
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|ADDR_length
id|s32
id|ADDR_length
suffix:semicolon
DECL|member|ADDR_offset
id|s32
id|ADDR_offset
suffix:semicolon
DECL|member|CONIND_number
id|u32
id|CONIND_number
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_error_ack
r_struct
id|T_error_ack
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|ERROR_prim
id|s32
id|ERROR_prim
suffix:semicolon
DECL|member|TLI_error
id|s32
id|TLI_error
suffix:semicolon
DECL|member|UNIX_error
id|s32
id|UNIX_error
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_ok_ack
r_struct
id|T_ok_ack
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|CORRECT_prim
id|s32
id|CORRECT_prim
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_conn_ind
r_struct
id|T_conn_ind
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|SRC_length
id|s32
id|SRC_length
suffix:semicolon
DECL|member|SRC_offset
id|s32
id|SRC_offset
suffix:semicolon
DECL|member|OPT_length
id|s32
id|OPT_length
suffix:semicolon
DECL|member|OPT_offset
id|s32
id|OPT_offset
suffix:semicolon
DECL|member|SEQ_number
id|s32
id|SEQ_number
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_conn_con
r_struct
id|T_conn_con
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|RES_length
id|s32
id|RES_length
suffix:semicolon
DECL|member|RES_offset
id|s32
id|RES_offset
suffix:semicolon
DECL|member|OPT_length
id|s32
id|OPT_length
suffix:semicolon
DECL|member|OPT_offset
id|s32
id|OPT_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_discon_ind
r_struct
id|T_discon_ind
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|DISCON_reason
id|s32
id|DISCON_reason
suffix:semicolon
DECL|member|SEQ_number
id|s32
id|SEQ_number
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_unitdata_ind
r_struct
id|T_unitdata_ind
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|SRC_length
id|s32
id|SRC_length
suffix:semicolon
DECL|member|SRC_offset
id|s32
id|SRC_offset
suffix:semicolon
DECL|member|OPT_length
id|s32
id|OPT_length
suffix:semicolon
DECL|member|OPT_offset
id|s32
id|OPT_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_optmgmt_ack
r_struct
id|T_optmgmt_ack
(brace
DECL|member|PRIM_type
id|s32
id|PRIM_type
suffix:semicolon
DECL|member|OPT_length
id|s32
id|OPT_length
suffix:semicolon
DECL|member|OPT_offset
id|s32
id|OPT_offset
suffix:semicolon
DECL|member|MGMT_flags
id|s32
id|MGMT_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|opthdr
r_struct
id|opthdr
(brace
DECL|member|level
id|s32
id|level
suffix:semicolon
DECL|member|name
id|s32
id|name
suffix:semicolon
DECL|member|len
id|s32
id|len
suffix:semicolon
DECL|member|value
r_char
id|value
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|T_primsg
r_struct
id|T_primsg
(brace
DECL|member|next
r_struct
id|T_primsg
op_star
id|next
suffix:semicolon
DECL|member|pri
r_int
r_char
id|pri
suffix:semicolon
DECL|member|band
r_int
r_char
id|band
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|type
id|s32
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|strbuf
r_struct
id|strbuf
(brace
DECL|member|maxlen
id|s32
id|maxlen
suffix:semicolon
DECL|member|len
id|s32
id|len
suffix:semicolon
DECL|member|buf
id|u32
id|buf
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Constants used by STREAMS modules emulation code */
DECL|typedef|sol_module
r_typedef
r_char
id|sol_module
suffix:semicolon
DECL|macro|MAX_NR_STREAM_MODULES
mdefine_line|#define MAX_NR_STREAM_MODULES   16
multiline_comment|/* Private data structure assigned to sockets. */
DECL|struct|sol_socket_struct
r_struct
id|sol_socket_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|modcount
r_int
id|modcount
suffix:semicolon
DECL|member|module
id|sol_module
id|module
(braket
id|MAX_NR_STREAM_MODULES
)braket
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|pfirst
DECL|member|plast
r_struct
id|T_primsg
op_star
id|pfirst
comma
op_star
id|plast
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SOLARIS_SOCKET_MAGIC
mdefine_line|#define SOLARIS_SOCKET_MAGIC    0xADDED
eof
