multiline_comment|/*&n; * Definitions for the KLSI KL5KUSB105 serial port adapter&n; */
multiline_comment|/* vendor/product pairs that are known to contain this chipset */
DECL|macro|PALMCONNECT_VID
mdefine_line|#define PALMCONNECT_VID&t;&t;0x0830
DECL|macro|PALMCONNECT_PID
mdefine_line|#define PALMCONNECT_PID&t;&t;0x0080
DECL|macro|KLSI_VID
mdefine_line|#define KLSI_VID&t;&t;0x05e9
DECL|macro|KLSI_KL5KUSB105D_PID
mdefine_line|#define KLSI_KL5KUSB105D_PID&t;0x00c0
multiline_comment|/* Vendor commands: */
multiline_comment|/* port table -- the chip supports up to 4 channels */
multiline_comment|/* baud rates */
r_enum
(brace
DECL|enumerator|kl5kusb105a_sio_b115200
id|kl5kusb105a_sio_b115200
op_assign
l_int|0
comma
DECL|enumerator|kl5kusb105a_sio_b57600
id|kl5kusb105a_sio_b57600
op_assign
l_int|1
comma
DECL|enumerator|kl5kusb105a_sio_b38400
id|kl5kusb105a_sio_b38400
op_assign
l_int|2
comma
DECL|enumerator|kl5kusb105a_sio_b19200
id|kl5kusb105a_sio_b19200
op_assign
l_int|4
comma
DECL|enumerator|kl5kusb105a_sio_b14400
id|kl5kusb105a_sio_b14400
op_assign
l_int|5
comma
DECL|enumerator|kl5kusb105a_sio_b9600
id|kl5kusb105a_sio_b9600
op_assign
l_int|6
comma
DECL|enumerator|kl5kusb105a_sio_b4800
id|kl5kusb105a_sio_b4800
op_assign
l_int|8
comma
multiline_comment|/* unchecked */
DECL|enumerator|kl5kusb105a_sio_b2400
id|kl5kusb105a_sio_b2400
op_assign
l_int|9
comma
multiline_comment|/* unchecked */
DECL|enumerator|kl5kusb105a_sio_b1200
id|kl5kusb105a_sio_b1200
op_assign
l_int|0xa
comma
multiline_comment|/* unchecked */
DECL|enumerator|kl5kusb105a_sio_b600
id|kl5kusb105a_sio_b600
op_assign
l_int|0xb
multiline_comment|/* unchecked */
)brace
suffix:semicolon
multiline_comment|/* data bits */
DECL|macro|kl5kusb105a_dtb_7
mdefine_line|#define kl5kusb105a_dtb_7   7
DECL|macro|kl5kusb105a_dtb_8
mdefine_line|#define kl5kusb105a_dtb_8   8
multiline_comment|/* requests: */
DECL|macro|KL5KUSB105A_SIO_SET_DATA
mdefine_line|#define KL5KUSB105A_SIO_SET_DATA  1
DECL|macro|KL5KUSB105A_SIO_POLL
mdefine_line|#define KL5KUSB105A_SIO_POLL      2
DECL|macro|KL5KUSB105A_SIO_CONFIGURE
mdefine_line|#define KL5KUSB105A_SIO_CONFIGURE      3
multiline_comment|/* values used for request KL5KUSB105A_SIO_CONFIGURE */
DECL|macro|KL5KUSB105A_SIO_CONFIGURE_READ_ON
mdefine_line|#define KL5KUSB105A_SIO_CONFIGURE_READ_ON      3
DECL|macro|KL5KUSB105A_SIO_CONFIGURE_READ_OFF
mdefine_line|#define KL5KUSB105A_SIO_CONFIGURE_READ_OFF     2
multiline_comment|/* Interpretation of modem status lines */
multiline_comment|/* These need sorting out by individually connecting pins and checking&n; * results. FIXME!&n; * When data is being sent we see 0x30 in the lower byte; this must&n; * contain DSR and CTS ...&n; */
DECL|macro|KL5KUSB105A_DSR
mdefine_line|#define KL5KUSB105A_DSR&t;&t;&t;((1&lt;&lt;4) | (1&lt;&lt;5))
DECL|macro|KL5KUSB105A_CTS
mdefine_line|#define KL5KUSB105A_CTS&t;&t;&t;((1&lt;&lt;5) | (1&lt;&lt;4))
DECL|macro|KL5KUSB105A_WANTS_TO_SEND
mdefine_line|#define KL5KUSB105A_WANTS_TO_SEND&t;0x30
singleline_comment|//#define KL5KUSB105A_DTR&t;&t;&t;/* Data Terminal Ready */
singleline_comment|//#define KL5KUSB105A_CTS&t;&t;&t;/* Clear To Send */
singleline_comment|//#define KL5KUSB105A_CD&t;&t;&t;/* Carrier Detect */
singleline_comment|//#define KL5KUSB105A_DSR&t;&t;&t;/* Data Set Ready */
singleline_comment|//#define KL5KUSB105A_RxD&t;&t;&t;/* Receive pin */
singleline_comment|//#define KL5KUSB105A_LE
singleline_comment|//#define KL5KUSB105A_RTS&t;&t;
singleline_comment|//#define KL5KUSB105A_ST&t;&t;
singleline_comment|//#define KL5KUSB105A_SR&t;&t;
singleline_comment|//#define KL5KUSB105A_RI&t;&t;&t;/* Ring Indicator */
multiline_comment|/* vim: set ts=8 sts=8: */
eof
