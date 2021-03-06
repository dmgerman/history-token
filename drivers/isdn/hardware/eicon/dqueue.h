multiline_comment|/* $Id: dqueue.h,v 1.1.2.2 2001/02/08 12:25:43 armin Exp $ */
macro_line|#ifndef _DIVA_USER_MODE_IDI_DATA_QUEUE_H__
DECL|macro|_DIVA_USER_MODE_IDI_DATA_QUEUE_H__
mdefine_line|#define _DIVA_USER_MODE_IDI_DATA_QUEUE_H__
DECL|macro|DIVA_UM_IDI_MAX_MSGS
mdefine_line|#define DIVA_UM_IDI_MAX_MSGS 64
DECL|struct|_diva_um_idi_data_queue
r_typedef
r_struct
id|_diva_um_idi_data_queue
(brace
DECL|member|segments
r_int
id|segments
suffix:semicolon
DECL|member|max_length
r_int
id|max_length
suffix:semicolon
DECL|member|read
r_int
id|read
suffix:semicolon
DECL|member|write
r_int
id|write
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|segment_pending
r_int
id|segment_pending
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
(braket
id|DIVA_UM_IDI_MAX_MSGS
)braket
suffix:semicolon
DECL|member|length
r_int
id|length
(braket
id|DIVA_UM_IDI_MAX_MSGS
)braket
suffix:semicolon
DECL|typedef|diva_um_idi_data_queue_t
)brace
id|diva_um_idi_data_queue_t
suffix:semicolon
r_int
id|diva_data_q_init
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
comma
r_int
id|max_length
comma
r_int
id|max_segments
)paren
suffix:semicolon
r_int
id|diva_data_q_finit
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
suffix:semicolon
r_int
id|diva_data_q_get_max_length
c_func
(paren
r_const
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
suffix:semicolon
r_void
op_star
id|diva_data_q_get_segment4write
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
suffix:semicolon
r_void
id|diva_data_q_ack_segment4write
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
comma
r_int
id|length
)paren
suffix:semicolon
r_const
r_void
op_star
id|diva_data_q_get_segment4read
c_func
(paren
r_const
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
suffix:semicolon
r_int
id|diva_data_q_get_segment_length
c_func
(paren
r_const
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
suffix:semicolon
r_void
id|diva_data_q_ack_segment4read
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
suffix:semicolon
macro_line|#endif
eof
