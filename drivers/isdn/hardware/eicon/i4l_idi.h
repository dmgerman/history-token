multiline_comment|/* $Id: i4l_idi.h,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $&n; *&n; * ISDN interface module for Eicon active cards.&n; * I4L - IDI Interface&n; *&n; * Copyright 1998-2000  by Armin Schindler (mac@melware.de)&n; * Copyright 1999-2002  Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef E_IDI_H
DECL|macro|E_IDI_H
mdefine_line|#define E_IDI_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|N_DATA
macro_line|#undef N_DATA
DECL|macro|ID_MASK
macro_line|#undef ID_MASK
macro_line|#include &quot;pc.h&quot;
DECL|macro|AOC_IND
mdefine_line|#define AOC_IND  26&t;&t;/* Advice of Charge                         */
DECL|macro|PI
mdefine_line|#define PI  0x1e                /* Progress Indicator               */
DECL|macro|NI
mdefine_line|#define NI  0x27                /* Notification Indicator           */
multiline_comment|/* defines for statectrl */
DECL|macro|WAITING_FOR_HANGUP
mdefine_line|#define WAITING_FOR_HANGUP&t;0x01
DECL|macro|HAVE_CONN_REQ
mdefine_line|#define HAVE_CONN_REQ&t;&t;0x02
DECL|macro|IN_HOLD
mdefine_line|#define IN_HOLD&t;&t;&t;0x04
r_typedef
r_struct
(brace
DECL|member|cpn
r_char
id|cpn
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|oad
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|dsa
r_char
id|dsa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|osa
r_char
id|osa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|plan
id|__u8
id|plan
suffix:semicolon
DECL|member|screen
id|__u8
id|screen
suffix:semicolon
DECL|member|sin
id|__u8
id|sin
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|chi
id|__u8
id|chi
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|e_chi
id|__u8
id|e_chi
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bc
id|__u8
id|bc
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|e_bc
id|__u8
id|e_bc
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|llc
id|__u8
id|llc
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|hlc
id|__u8
id|hlc
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|cau
id|__u8
id|cau
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|e_cau
id|__u8
id|e_cau
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|e_mt
id|__u8
id|e_mt
suffix:semicolon
DECL|member|dt
id|__u8
id|dt
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|display
r_char
id|display
(braket
l_int|83
)braket
suffix:semicolon
DECL|member|keypad
r_char
id|keypad
(braket
l_int|35
)braket
suffix:semicolon
DECL|member|rdn
r_char
id|rdn
(braket
l_int|32
)braket
suffix:semicolon
DECL|typedef|idi_ind_message
)brace
id|idi_ind_message
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|next
id|__u16
id|next
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Req
id|__u8
id|Req
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ReqId
id|__u8
id|ReqId
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ReqCh
id|__u8
id|ReqCh
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved1
id|__u8
id|Reserved1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reference
id|__u16
id|Reference
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
(braket
l_int|8
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|XBuffer
id|eicon_PBUFFER
id|XBuffer
suffix:semicolon
DECL|typedef|eicon_REQ
)brace
id|eicon_REQ
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|next
id|__u16
id|next
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Rc
id|__u8
id|Rc
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RcId
id|__u8
id|RcId
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RcCh
id|__u8
id|RcCh
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved1
id|__u8
id|Reserved1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reference
id|__u16
id|Reference
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved2
id|__u8
id|Reserved2
(braket
l_int|8
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|eicon_RC
)brace
id|eicon_RC
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|next
id|__u16
id|next
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Ind
id|__u8
id|Ind
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|IndId
id|__u8
id|IndId
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|IndCh
id|__u8
id|IndCh
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|MInd
id|__u8
id|MInd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|MLength
id|__u16
id|MLength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reference
id|__u16
id|Reference
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RNR
id|__u8
id|RNR
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Ack
id|__u32
id|Ack
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RBuffer
id|eicon_PBUFFER
id|RBuffer
suffix:semicolon
DECL|typedef|eicon_IND
)brace
id|eicon_IND
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|Data
id|__u8
op_star
id|Data
suffix:semicolon
DECL|member|Size
r_int
r_int
id|Size
suffix:semicolon
DECL|member|Len
r_int
r_int
id|Len
suffix:semicolon
DECL|member|Next
id|__u8
op_star
id|Next
suffix:semicolon
DECL|typedef|eicon_OBJBUFFER
)brace
id|eicon_OBJBUFFER
suffix:semicolon
r_extern
r_int
id|idi_do_req
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
comma
r_int
id|cmd
comma
r_int
id|layer
)paren
suffix:semicolon
r_extern
r_int
id|idi_hangup
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|idi_connect_res
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|eicon_idi_listen_req
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|idi_connect_req
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
comma
r_char
op_star
id|phone
comma
r_char
op_star
id|eazmsn
comma
r_int
id|si1
comma
r_int
id|si2
)paren
suffix:semicolon
r_extern
r_void
id|idi_handle_ack
c_func
(paren
id|eicon_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|idi_handle_ind
c_func
(paren
id|eicon_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|eicon_idi_manage
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_manifbuf
op_star
id|mb
)paren
suffix:semicolon
r_extern
r_int
id|idi_send_data
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
comma
r_int
id|ack
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|que
comma
r_int
id|chk
)paren
suffix:semicolon
r_extern
r_void
id|idi_audio_cmd
c_func
(paren
id|eicon_card
op_star
id|ccard
comma
id|eicon_chan
op_star
id|chan
comma
r_int
id|cmd
comma
id|u_char
op_star
id|value
)paren
suffix:semicolon
r_extern
r_int
id|capipmsg
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
comma
id|capi_msg
op_star
id|cm
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_TTY_FAX
r_extern
r_void
id|idi_fax_cmd
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|idi_faxdata_send
c_func
(paren
id|eicon_card
op_star
id|ccard
comma
id|eicon_chan
op_star
id|chan
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;dsp_defs.h&quot;
DECL|macro|DSP_UDATA_REQUEST_SWITCH_FRAMER
mdefine_line|#define DSP_UDATA_REQUEST_SWITCH_FRAMER         1
multiline_comment|/*&n;parameters:&n;  &lt;byte&gt; transmit framer type&n;  &lt;byte&gt; receive framer type&n;*/
DECL|macro|DSP_REQUEST_SWITCH_FRAMER_HDLC
mdefine_line|#define DSP_REQUEST_SWITCH_FRAMER_HDLC          0
DECL|macro|DSP_REQUEST_SWITCH_FRAMER_TRANSPARENT
mdefine_line|#define DSP_REQUEST_SWITCH_FRAMER_TRANSPARENT   1
DECL|macro|DSP_REQUEST_SWITCH_FRAMER_ASYNC
mdefine_line|#define DSP_REQUEST_SWITCH_FRAMER_ASYNC         2
DECL|macro|DSP_UDATA_REQUEST_CLEARDOWN
mdefine_line|#define DSP_UDATA_REQUEST_CLEARDOWN             2
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_REQUEST_TX_CONFIRMATION_ON
mdefine_line|#define DSP_UDATA_REQUEST_TX_CONFIRMATION_ON    3
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_REQUEST_TX_CONFIRMATION_OFF
mdefine_line|#define DSP_UDATA_REQUEST_TX_CONFIRMATION_OFF   4
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|struct|eicon_dsp_ind
r_typedef
r_struct
id|eicon_dsp_ind
(brace
DECL|member|time
id|__u16
id|time
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|norm
id|__u8
id|norm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|options
id|__u16
id|options
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|speed
id|__u32
id|speed
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|delay
id|__u16
id|delay
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|txspeed
id|__u32
id|txspeed
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rxspeed
id|__u32
id|rxspeed
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|eicon_dsp_ind
)brace
id|eicon_dsp_ind
suffix:semicolon
DECL|macro|DSP_CONNECTED_OPTION_V42_TRANS
mdefine_line|#define DSP_CONNECTED_OPTION_V42_TRANS           0x0002
DECL|macro|DSP_CONNECTED_OPTION_V42_LAPM
mdefine_line|#define DSP_CONNECTED_OPTION_V42_LAPM            0x0004
DECL|macro|DSP_CONNECTED_OPTION_SHORT_TRAIN
mdefine_line|#define DSP_CONNECTED_OPTION_SHORT_TRAIN         0x0008
DECL|macro|DSP_CONNECTED_OPTION_TALKER_ECHO_PROTECT
mdefine_line|#define DSP_CONNECTED_OPTION_TALKER_ECHO_PROTECT 0x0010
DECL|macro|DSP_UDATA_INDICATION_DISCONNECT
mdefine_line|#define DSP_UDATA_INDICATION_DISCONNECT         5
multiline_comment|/*&n;returns:&n;  &lt;byte&gt; cause&n;*/
DECL|macro|DSP_DISCONNECT_CAUSE_NONE
mdefine_line|#define DSP_DISCONNECT_CAUSE_NONE               0x00
DECL|macro|DSP_DISCONNECT_CAUSE_BUSY_TONE
mdefine_line|#define DSP_DISCONNECT_CAUSE_BUSY_TONE          0x01
DECL|macro|DSP_DISCONNECT_CAUSE_CONGESTION_TONE
mdefine_line|#define DSP_DISCONNECT_CAUSE_CONGESTION_TONE    0x02
DECL|macro|DSP_DISCONNECT_CAUSE_INCOMPATIBILITY
mdefine_line|#define DSP_DISCONNECT_CAUSE_INCOMPATIBILITY    0x03
DECL|macro|DSP_DISCONNECT_CAUSE_CLEARDOWN
mdefine_line|#define DSP_DISCONNECT_CAUSE_CLEARDOWN          0x04
DECL|macro|DSP_DISCONNECT_CAUSE_TRAINING_TIMEOUT
mdefine_line|#define DSP_DISCONNECT_CAUSE_TRAINING_TIMEOUT   0x05
DECL|macro|DSP_UDATA_INDICATION_TX_CONFIRMATION
mdefine_line|#define DSP_UDATA_INDICATION_TX_CONFIRMATION    6
multiline_comment|/*&n;returns:&n;  &lt;word&gt; confirmation number&n;*/
DECL|macro|DSP_UDATA_REQUEST_SEND_DTMF_DIGITS
mdefine_line|#define DSP_UDATA_REQUEST_SEND_DTMF_DIGITS      16
multiline_comment|/*&n;parameters:&n;  &lt;word&gt; tone duration (ms)&n;  &lt;word&gt; gap duration (ms)&n;  &lt;byte&gt; digit 0 tone code&n;  ...&n;  &lt;byte&gt; digit n tone code&n;*/
DECL|macro|DSP_SEND_DTMF_DIGITS_HEADER_LENGTH
mdefine_line|#define DSP_SEND_DTMF_DIGITS_HEADER_LENGTH      5
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_697_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_697_HZ    0x00
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_770_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_770_HZ    0x01
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_852_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_852_HZ    0x02
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_941_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_941_HZ    0x03
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_MASK
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_MASK      0x03
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1209_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1209_HZ  0x00
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1336_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1336_HZ  0x04
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1477_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1477_HZ  0x08
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1633_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1633_HZ  0x0c
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_MASK
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_MASK     0x0c
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_0
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_0              0x07
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_1
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_1              0x00
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_2
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_2              0x04
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_3
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_3              0x08
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_4
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_4              0x01
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_5
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_5              0x05
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_6
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_6              0x09
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_7
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_7              0x02
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_8
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_8              0x06
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_9
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_9              0x0a
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_STAR
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_STAR           0x03
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_HASHMARK
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_HASHMARK       0x0b
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_A
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_A              0x0c
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_B
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_B              0x0d
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_C
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_C              0x0e
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_D
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_D              0x0f
DECL|macro|DSP_UDATA_INDICATION_DTMF_DIGITS_SENT
mdefine_line|#define DSP_UDATA_INDICATION_DTMF_DIGITS_SENT   16
multiline_comment|/*&n;returns:&n;  - none -&n;  One indication will be sent for every request.&n;*/
DECL|macro|DSP_UDATA_REQUEST_ENABLE_DTMF_RECEIVER
mdefine_line|#define DSP_UDATA_REQUEST_ENABLE_DTMF_RECEIVER  17
multiline_comment|/*&n;parameters:&n;  &lt;word&gt; tone duration (ms)&n;  &lt;word&gt; gap duration (ms)&n;*/
DECL|struct|enable_dtmf_s
r_typedef
r_struct
id|enable_dtmf_s
(brace
DECL|member|tone
id|__u16
id|tone
suffix:semicolon
DECL|member|gap
id|__u16
id|gap
suffix:semicolon
DECL|typedef|enable_dtmf_s
)brace
id|enable_dtmf_s
suffix:semicolon
DECL|macro|DSP_UDATA_REQUEST_DISABLE_DTMF_RECEIVER
mdefine_line|#define DSP_UDATA_REQUEST_DISABLE_DTMF_RECEIVER 18
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_INDICATION_DTMF_DIGITS_RECEIVED
mdefine_line|#define DSP_UDATA_INDICATION_DTMF_DIGITS_RECEIVED 17
multiline_comment|/*&n;returns:&n;  &lt;byte&gt; digit 0 tone code&n;  ...&n;  &lt;byte&gt; digit n tone code&n;*/
DECL|macro|DSP_DTMF_DIGITS_RECEIVED_HEADER_LENGTH
mdefine_line|#define DSP_DTMF_DIGITS_RECEIVED_HEADER_LENGTH  1
DECL|macro|DSP_UDATA_INDICATION_MODEM_CALLING_TONE
mdefine_line|#define DSP_UDATA_INDICATION_MODEM_CALLING_TONE 18
multiline_comment|/*&n;returns:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_INDICATION_FAX_CALLING_TONE
mdefine_line|#define DSP_UDATA_INDICATION_FAX_CALLING_TONE   19
multiline_comment|/*&n;returns:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_INDICATION_ANSWER_TONE
mdefine_line|#define DSP_UDATA_INDICATION_ANSWER_TONE        20
multiline_comment|/*&n;returns:&n;  - none -&n;*/
multiline_comment|/* ============= FAX ================ */
DECL|macro|EICON_FAXID_LEN
mdefine_line|#define EICON_FAXID_LEN 20
DECL|struct|eicon_t30_s
r_typedef
r_struct
id|eicon_t30_s
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|rate
id|__u8
id|rate
suffix:semicolon
DECL|member|resolution
id|__u8
id|resolution
suffix:semicolon
DECL|member|format
id|__u8
id|format
suffix:semicolon
DECL|member|pages_low
id|__u8
id|pages_low
suffix:semicolon
DECL|member|pages_high
id|__u8
id|pages_high
suffix:semicolon
DECL|member|atf
id|__u8
id|atf
suffix:semicolon
DECL|member|control_bits_low
id|__u8
id|control_bits_low
suffix:semicolon
DECL|member|control_bits_high
id|__u8
id|control_bits_high
suffix:semicolon
DECL|member|feature_bits_low
id|__u8
id|feature_bits_low
suffix:semicolon
DECL|member|feature_bits_high
id|__u8
id|feature_bits_high
suffix:semicolon
DECL|member|universal_5
id|__u8
id|universal_5
suffix:semicolon
DECL|member|universal_6
id|__u8
id|universal_6
suffix:semicolon
DECL|member|universal_7
id|__u8
id|universal_7
suffix:semicolon
DECL|member|station_id_len
id|__u8
id|station_id_len
suffix:semicolon
DECL|member|head_line_len
id|__u8
id|head_line_len
suffix:semicolon
DECL|member|station_id
id|__u8
id|station_id
(braket
id|EICON_FAXID_LEN
)braket
suffix:semicolon
multiline_comment|/* __u8          head_line[]; */
DECL|typedef|eicon_t30_s
)brace
id|eicon_t30_s
suffix:semicolon
multiline_comment|/* EDATA transmit messages */
DECL|macro|EDATA_T30_DIS
mdefine_line|#define EDATA_T30_DIS       0x01
DECL|macro|EDATA_T30_FTT
mdefine_line|#define EDATA_T30_FTT       0x02
DECL|macro|EDATA_T30_MCF
mdefine_line|#define EDATA_T30_MCF       0x03
multiline_comment|/* EDATA receive messages */
DECL|macro|EDATA_T30_DCS
mdefine_line|#define EDATA_T30_DCS       0x81
DECL|macro|EDATA_T30_TRAIN_OK
mdefine_line|#define EDATA_T30_TRAIN_OK  0x82
DECL|macro|EDATA_T30_EOP
mdefine_line|#define EDATA_T30_EOP       0x83
DECL|macro|EDATA_T30_MPS
mdefine_line|#define EDATA_T30_MPS       0x84
DECL|macro|EDATA_T30_EOM
mdefine_line|#define EDATA_T30_EOM       0x85
DECL|macro|EDATA_T30_DTC
mdefine_line|#define EDATA_T30_DTC       0x86
DECL|macro|T30_FORMAT_SFF
mdefine_line|#define T30_FORMAT_SFF            0
DECL|macro|T30_FORMAT_ASCII
mdefine_line|#define T30_FORMAT_ASCII          1
DECL|macro|T30_FORMAT_COUNT
mdefine_line|#define T30_FORMAT_COUNT          2
DECL|macro|T30_CONTROL_BIT_DISABLE_FINE
mdefine_line|#define T30_CONTROL_BIT_DISABLE_FINE      0x0001
DECL|macro|T30_CONTROL_BIT_ENABLE_ECM
mdefine_line|#define T30_CONTROL_BIT_ENABLE_ECM        0x0002
DECL|macro|T30_CONTROL_BIT_ECM_64_BYTES
mdefine_line|#define T30_CONTROL_BIT_ECM_64_BYTES      0x0004
DECL|macro|T30_CONTROL_BIT_ENABLE_2D_CODING
mdefine_line|#define T30_CONTROL_BIT_ENABLE_2D_CODING  0x0008
DECL|macro|T30_CONTROL_BIT_ENABLE_T6_CODING
mdefine_line|#define T30_CONTROL_BIT_ENABLE_T6_CODING  0x0010
DECL|macro|T30_CONTROL_BIT_ENABLE_UNCOMPR
mdefine_line|#define T30_CONTROL_BIT_ENABLE_UNCOMPR    0x0020
DECL|macro|T30_CONTROL_BIT_ACCEPT_POLLING
mdefine_line|#define T30_CONTROL_BIT_ACCEPT_POLLING    0x0040
DECL|macro|T30_CONTROL_BIT_REQUEST_POLLING
mdefine_line|#define T30_CONTROL_BIT_REQUEST_POLLING   0x0080
DECL|macro|T30_CONTROL_BIT_MORE_DOCUMENTS
mdefine_line|#define T30_CONTROL_BIT_MORE_DOCUMENTS    0x0100
DECL|macro|T30_CONTROL_BIT_ALL_FEATURES
mdefine_line|#define T30_CONTROL_BIT_ALL_FEATURES&bslash;&n;  (T30_CONTROL_BIT_ENABLE_ECM | T30_CONTROL_BIT_ENABLE_2D_CODING |&bslash;&n;   T30_CONTROL_BIT_ENABLE_T6_CODING | T30_CONTROL_BIT_ENABLE_UNCOMPR)
DECL|macro|T30_FEATURE_BIT_FINE
mdefine_line|#define T30_FEATURE_BIT_FINE              0x0001
DECL|macro|T30_FEATURE_BIT_ECM
mdefine_line|#define T30_FEATURE_BIT_ECM               0x0002
DECL|macro|T30_FEATURE_BIT_ECM_64_BYTES
mdefine_line|#define T30_FEATURE_BIT_ECM_64_BYTES      0x0004
DECL|macro|T30_FEATURE_BIT_2D_CODING
mdefine_line|#define T30_FEATURE_BIT_2D_CODING         0x0008
DECL|macro|T30_FEATURE_BIT_T6_CODING
mdefine_line|#define T30_FEATURE_BIT_T6_CODING         0x0010
DECL|macro|T30_FEATURE_BIT_UNCOMPR_ENABLED
mdefine_line|#define T30_FEATURE_BIT_UNCOMPR_ENABLED   0x0020
DECL|macro|T30_FEATURE_BIT_POLLING
mdefine_line|#define T30_FEATURE_BIT_POLLING           0x0040
DECL|macro|FAX_OBJECT_DOCU
mdefine_line|#define FAX_OBJECT_DOCU&t;&t;1
DECL|macro|FAX_OBJECT_PAGE
mdefine_line|#define FAX_OBJECT_PAGE&t;&t;2
DECL|macro|FAX_OBJECT_LINE
mdefine_line|#define FAX_OBJECT_LINE&t;&t;3
DECL|macro|T4_EOL
mdefine_line|#define T4_EOL&t;&t;&t;0x800
DECL|macro|T4_EOL_BITSIZE
mdefine_line|#define T4_EOL_BITSIZE&t;&t;12
DECL|macro|T4_EOL_DWORD
mdefine_line|#define T4_EOL_DWORD&t;&t;(T4_EOL &lt;&lt; (32 - T4_EOL_BITSIZE))
DECL|macro|T4_EOL_MASK_DWORD
mdefine_line|#define T4_EOL_MASK_DWORD&t;((__u32) -1 &lt;&lt; (32 - T4_EOL_BITSIZE))
DECL|macro|SFF_LEN_FLD_SIZE
mdefine_line|#define SFF_LEN_FLD_SIZE&t;3
DECL|macro|_DLE_
mdefine_line|#define _DLE_&t;0x10
DECL|macro|_ETX_
mdefine_line|#define _ETX_&t;0x03
DECL|struct|eicon_sff_dochead
r_typedef
r_struct
id|eicon_sff_dochead
(brace
DECL|member|id
id|__u32
id|id
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|version
id|__u8
id|version
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|userinfo
id|__u16
id|userinfo
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|pagecount
id|__u16
id|pagecount
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|off1pagehead
id|__u16
id|off1pagehead
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|offnpagehead
id|__u32
id|offnpagehead
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|offdocend
id|__u32
id|offdocend
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|eicon_sff_dochead
)brace
id|eicon_sff_dochead
suffix:semicolon
DECL|struct|eicon_sff_pagehead
r_typedef
r_struct
id|eicon_sff_pagehead
(brace
DECL|member|pageheadid
id|__u8
id|pageheadid
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|pageheadlen
id|__u8
id|pageheadlen
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|resvert
id|__u8
id|resvert
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reshoriz
id|__u8
id|reshoriz
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|coding
id|__u8
id|coding
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|linelength
id|__u16
id|linelength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|pagelength
id|__u16
id|pagelength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|offprevpage
id|__u32
id|offprevpage
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|offnextpage
id|__u32
id|offnextpage
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|eicon_sff_pagehead
)brace
id|eicon_sff_pagehead
suffix:semicolon
macro_line|#endif&t;/* E_IDI_H */
eof
