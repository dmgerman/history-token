multiline_comment|/* $Id: um_xdi.h,v 1.1.2.2 2002/10/02 14:38:38 armin Exp $ */
macro_line|#ifndef __DIVA_USER_MODE_XDI_H__
DECL|macro|__DIVA_USER_MODE_XDI_H__
mdefine_line|#define __DIVA_USER_MODE_XDI_H__
multiline_comment|/*&n;  Contains declaratiom of structures shared between application&n;  and user mode idi driver&n;*/
DECL|struct|_diva_um_idi_adapter_features
r_typedef
r_struct
id|_diva_um_idi_adapter_features
(brace
DECL|member|type
id|dword
id|type
suffix:semicolon
DECL|member|features
id|dword
id|features
suffix:semicolon
DECL|member|channels
id|dword
id|channels
suffix:semicolon
DECL|member|serial_number
id|dword
id|serial_number
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
DECL|typedef|diva_um_idi_adapter_features_t
)brace
id|diva_um_idi_adapter_features_t
suffix:semicolon
DECL|macro|DIVA_UM_IDI_REQ_MASK
mdefine_line|#define DIVA_UM_IDI_REQ_MASK&t;&t;&t;0x0000FFFF
DECL|macro|DIVA_UM_IDI_REQ_TYPE_MASK
mdefine_line|#define DIVA_UM_IDI_REQ_TYPE_MASK&t;&t;(~(DIVA_UM_IDI_REQ_MASK))
DECL|macro|DIVA_UM_IDI_GET_FEATURES
mdefine_line|#define DIVA_UM_IDI_GET_FEATURES&t;&t;1&t;/* trigger features indication */
DECL|macro|DIVA_UM_IDI_REQ
mdefine_line|#define DIVA_UM_IDI_REQ&t;&t;&t;&t;2
DECL|macro|DIVA_UM_IDI_REQ_TYPE_MAN
mdefine_line|#define DIVA_UM_IDI_REQ_TYPE_MAN&t;&t;0x10000000
DECL|macro|DIVA_UM_IDI_REQ_TYPE_SIG
mdefine_line|#define DIVA_UM_IDI_REQ_TYPE_SIG&t;&t;0x20000000
DECL|macro|DIVA_UM_IDI_REQ_TYPE_NET
mdefine_line|#define DIVA_UM_IDI_REQ_TYPE_NET&t;&t;0x30000000
DECL|macro|DIVA_UM_IDI_REQ_MAN
mdefine_line|#define DIVA_UM_IDI_REQ_MAN&t;&t;&t;(DIVA_UM_IDI_REQ | DIVA_UM_IDI_REQ_TYPE_MAN)
DECL|macro|DIVA_UM_IDI_REQ_SIG
mdefine_line|#define DIVA_UM_IDI_REQ_SIG&t;&t;&t;(DIVA_UM_IDI_REQ | DIVA_UM_IDI_REQ_TYPE_SIG)
DECL|macro|DIVA_UM_IDI_REQ_NET
mdefine_line|#define DIVA_UM_IDI_REQ_NET&t;&t;&t;(DIVA_UM_IDI_REQ | DIVA_UM_IDI_REQ_TYPE_NET)
multiline_comment|/*&n;  data_length  bytes will follow this structure&n;*/
DECL|struct|_diva_um_idi_req_hdr
r_typedef
r_struct
id|_diva_um_idi_req_hdr
(brace
DECL|member|type
id|dword
id|type
suffix:semicolon
DECL|member|Req
id|dword
id|Req
suffix:semicolon
DECL|member|ReqCh
id|dword
id|ReqCh
suffix:semicolon
DECL|member|data_length
id|dword
id|data_length
suffix:semicolon
DECL|typedef|diva_um_idi_req_hdr_t
)brace
id|diva_um_idi_req_hdr_t
suffix:semicolon
DECL|struct|_diva_um_idi_ind_parameters
r_typedef
r_struct
id|_diva_um_idi_ind_parameters
(brace
DECL|member|Ind
id|dword
id|Ind
suffix:semicolon
DECL|member|IndCh
id|dword
id|IndCh
suffix:semicolon
DECL|typedef|diva_um_idi_ind_parameters_t
)brace
id|diva_um_idi_ind_parameters_t
suffix:semicolon
DECL|struct|_diva_um_idi_rc_parameters
r_typedef
r_struct
id|_diva_um_idi_rc_parameters
(brace
DECL|member|Rc
id|dword
id|Rc
suffix:semicolon
DECL|member|RcCh
id|dword
id|RcCh
suffix:semicolon
DECL|typedef|diva_um_idi_rc_parameters_t
)brace
id|diva_um_idi_rc_parameters_t
suffix:semicolon
DECL|union|_diva_um_idi_ind
r_typedef
r_union
id|_diva_um_idi_ind
(brace
DECL|member|features
id|diva_um_idi_adapter_features_t
id|features
suffix:semicolon
DECL|member|ind
id|diva_um_idi_ind_parameters_t
id|ind
suffix:semicolon
DECL|member|rc
id|diva_um_idi_rc_parameters_t
id|rc
suffix:semicolon
DECL|typedef|diva_um_idi_ind_t
)brace
id|diva_um_idi_ind_t
suffix:semicolon
DECL|macro|DIVA_UM_IDI_IND_FEATURES
mdefine_line|#define DIVA_UM_IDI_IND_FEATURES  1  /* features indication */
DECL|macro|DIVA_UM_IDI_IND
mdefine_line|#define DIVA_UM_IDI_IND           2
DECL|macro|DIVA_UM_IDI_IND_RC
mdefine_line|#define DIVA_UM_IDI_IND_RC        3
multiline_comment|/*&n;  data_length bytes of data follow&n;  this structure&n;*/
DECL|struct|_diva_um_idi_ind_hdr
r_typedef
r_struct
id|_diva_um_idi_ind_hdr
(brace
DECL|member|type
id|dword
id|type
suffix:semicolon
DECL|member|hdr
id|diva_um_idi_ind_t
id|hdr
suffix:semicolon
DECL|member|data_length
id|dword
id|data_length
suffix:semicolon
DECL|typedef|diva_um_idi_ind_hdr_t
)brace
id|diva_um_idi_ind_hdr_t
suffix:semicolon
macro_line|#endif
eof
