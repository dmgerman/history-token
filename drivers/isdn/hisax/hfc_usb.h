multiline_comment|/*&n;* hfc_usb.h&n;*&n;* $Id: hfc_usb.h,v 4.1 2005/01/26 17:25:53 martinb1 Exp $&n;*/
macro_line|#ifndef __HFC_USB_H__
DECL|macro|__HFC_USB_H__
mdefine_line|#define __HFC_USB_H__
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR   &quot;Peter Sprenger (sprenger@moving-byters.de)&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC     &quot;HFC-S USB based HiSAX ISDN driver&quot;
DECL|macro|VERBOSE_USB_DEBUG
mdefine_line|#define VERBOSE_USB_DEBUG
DECL|macro|TRUE
mdefine_line|#define TRUE  1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
multiline_comment|/***********/
multiline_comment|/* defines */
multiline_comment|/***********/
DECL|macro|HFC_CTRL_TIMEOUT
mdefine_line|#define HFC_CTRL_TIMEOUT 20&t;/* 5ms timeout writing/reading regs */
DECL|macro|HFC_TIMER_T3
mdefine_line|#define HFC_TIMER_T3 8000&t;/* timeout for l1 activation timer */
DECL|macro|HFC_TIMER_T4
mdefine_line|#define HFC_TIMER_T4 500&t;/* time for state change interval */
DECL|macro|HFCUSB_L1_STATECHANGE
mdefine_line|#define HFCUSB_L1_STATECHANGE 0&t;/* L1 state changed */
DECL|macro|HFCUSB_L1_DRX
mdefine_line|#define HFCUSB_L1_DRX 1&t;&t;/* D-frame received */
DECL|macro|HFCUSB_L1_ERX
mdefine_line|#define HFCUSB_L1_ERX 2&t;&t;/* E-frame received */
DECL|macro|HFCUSB_L1_DTX
mdefine_line|#define HFCUSB_L1_DTX 4&t;&t;/* D-frames completed */
DECL|macro|MAX_BCH_SIZE
mdefine_line|#define MAX_BCH_SIZE 2048&t;/* allowed B-channel packet size */
DECL|macro|HFCUSB_RX_THRESHOLD
mdefine_line|#define HFCUSB_RX_THRESHOLD 64&t;/* threshold for fifo report bit rx */
DECL|macro|HFCUSB_TX_THRESHOLD
mdefine_line|#define HFCUSB_TX_THRESHOLD 64&t;/* threshold for fifo report bit tx */
DECL|macro|HFCUSB_CHIP_ID
mdefine_line|#define HFCUSB_CHIP_ID&t;&t;0x16&t;/* Chip ID register index */
DECL|macro|HFCUSB_CIRM
mdefine_line|#define HFCUSB_CIRM&t;&t;0x00&t;/* cirm register index */
DECL|macro|HFCUSB_USB_SIZE
mdefine_line|#define HFCUSB_USB_SIZE&t;&t;0x07&t;/* int length register */
DECL|macro|HFCUSB_USB_SIZE_I
mdefine_line|#define HFCUSB_USB_SIZE_I&t;0x06&t;/* iso length register */
DECL|macro|HFCUSB_F_CROSS
mdefine_line|#define HFCUSB_F_CROSS&t;&t;0x0b&t;/* bit order register */
DECL|macro|HFCUSB_CLKDEL
mdefine_line|#define HFCUSB_CLKDEL&t;&t;0x37&t;/* bit delay register */
DECL|macro|HFCUSB_CON_HDLC
mdefine_line|#define HFCUSB_CON_HDLC&t;&t;0xfa&t;/* channel connect register */
DECL|macro|HFCUSB_HDLC_PAR
mdefine_line|#define HFCUSB_HDLC_PAR&t;&t;0xfb
DECL|macro|HFCUSB_SCTRL
mdefine_line|#define HFCUSB_SCTRL&t;&t;0x31&t;/* S-bus control register (tx) */
DECL|macro|HFCUSB_SCTRL_E
mdefine_line|#define HFCUSB_SCTRL_E&t;&t;0x32&t;/* same for E and special funcs */
DECL|macro|HFCUSB_SCTRL_R
mdefine_line|#define HFCUSB_SCTRL_R&t;&t;0x33&t;/* S-bus control register (rx) */
DECL|macro|HFCUSB_F_THRES
mdefine_line|#define HFCUSB_F_THRES&t;&t;0x0c&t;/* threshold register */
DECL|macro|HFCUSB_FIFO
mdefine_line|#define HFCUSB_FIFO&t;&t;0x0f&t;/* fifo select register */
DECL|macro|HFCUSB_F_USAGE
mdefine_line|#define HFCUSB_F_USAGE&t;&t;0x1a&t;/* fifo usage register */
DECL|macro|HFCUSB_MST_MODE0
mdefine_line|#define HFCUSB_MST_MODE0&t;0x14
DECL|macro|HFCUSB_MST_MODE1
mdefine_line|#define HFCUSB_MST_MODE1&t;0x15
DECL|macro|HFCUSB_P_DATA
mdefine_line|#define HFCUSB_P_DATA&t;&t;0x1f
DECL|macro|HFCUSB_INC_RES_F
mdefine_line|#define HFCUSB_INC_RES_F&t;0x0e
DECL|macro|HFCUSB_STATES
mdefine_line|#define HFCUSB_STATES&t;&t;0x30
DECL|macro|HFCUSB_CHIPID
mdefine_line|#define HFCUSB_CHIPID&t;&t;0x40&t;/* ID value of HFC-S USB */
multiline_comment|/******************/
multiline_comment|/* fifo registers */
multiline_comment|/******************/
DECL|macro|HFCUSB_NUM_FIFOS
mdefine_line|#define HFCUSB_NUM_FIFOS&t;8&t;/* maximum number of fifos */
DECL|macro|HFCUSB_B1_TX
mdefine_line|#define HFCUSB_B1_TX&t;&t;0&t;/* index for B1 transmit bulk/int */
DECL|macro|HFCUSB_B1_RX
mdefine_line|#define HFCUSB_B1_RX&t;&t;1&t;/* index for B1 receive bulk/int */
DECL|macro|HFCUSB_B2_TX
mdefine_line|#define HFCUSB_B2_TX&t;&t;2
DECL|macro|HFCUSB_B2_RX
mdefine_line|#define HFCUSB_B2_RX&t;&t;3
DECL|macro|HFCUSB_D_TX
mdefine_line|#define HFCUSB_D_TX&t;&t;4
DECL|macro|HFCUSB_D_RX
mdefine_line|#define HFCUSB_D_RX&t;&t;5
DECL|macro|HFCUSB_PCM_TX
mdefine_line|#define HFCUSB_PCM_TX&t;&t;6
DECL|macro|HFCUSB_PCM_RX
mdefine_line|#define HFCUSB_PCM_RX&t;&t;7
multiline_comment|/*&n;* used to switch snd_transfer_mode for different TA modes e.g. the Billion USB TA just&n;* supports ISO out, while the Cologne Chip EVAL TA just supports BULK out&n;*/
DECL|macro|USB_INT
mdefine_line|#define USB_INT&t;&t;0
DECL|macro|USB_BULK
mdefine_line|#define USB_BULK&t;1
DECL|macro|USB_ISOC
mdefine_line|#define USB_ISOC&t;2
DECL|macro|ISOC_PACKETS_D
mdefine_line|#define ISOC_PACKETS_D&t;8
DECL|macro|ISOC_PACKETS_B
mdefine_line|#define ISOC_PACKETS_B&t;8
DECL|macro|ISO_BUFFER_SIZE
mdefine_line|#define ISO_BUFFER_SIZE&t;128
singleline_comment|// ISO send definitions
DECL|macro|SINK_MAX
mdefine_line|#define SINK_MAX&t;68
DECL|macro|SINK_MIN
mdefine_line|#define SINK_MIN&t;48
DECL|macro|SINK_DMIN
mdefine_line|#define SINK_DMIN&t;12
DECL|macro|SINK_DMAX
mdefine_line|#define SINK_DMAX&t;18
DECL|macro|BITLINE_INF
mdefine_line|#define BITLINE_INF&t;(-64*8)
multiline_comment|/**********/
multiline_comment|/* macros */
multiline_comment|/**********/
DECL|macro|write_usb
mdefine_line|#define write_usb(a,b,c)usb_control_msg((a)-&gt;dev,(a)-&gt;ctrl_out_pipe,0,0x40,(c),(b),0,0,HFC_CTRL_TIMEOUT)
DECL|macro|read_usb
mdefine_line|#define read_usb(a,b,c) usb_control_msg((a)-&gt;dev,(a)-&gt;ctrl_in_pipe,1,0xC0,0,(b),(c),1,HFC_CTRL_TIMEOUT)
multiline_comment|/*******************/
multiline_comment|/* Debugging Flags */
multiline_comment|/*******************/
DECL|macro|USB_DBG
mdefine_line|#define USB_DBG   1
DECL|macro|ISDN_DBG
mdefine_line|#define ISDN_DBG  2
multiline_comment|/* *********************/
multiline_comment|/* USB related defines */
multiline_comment|/***********************/
DECL|macro|HFC_CTRL_BUFSIZE
mdefine_line|#define HFC_CTRL_BUFSIZE 32
multiline_comment|/*************************************************/
multiline_comment|/* entry and size of output/input control buffer */
multiline_comment|/*************************************************/
r_typedef
r_struct
(brace
DECL|member|hfc_reg
id|__u8
id|hfc_reg
suffix:semicolon
multiline_comment|/* register number */
DECL|member|reg_val
id|__u8
id|reg_val
suffix:semicolon
multiline_comment|/* value to be written (or read) */
DECL|member|action
r_int
id|action
suffix:semicolon
multiline_comment|/* data for action handler */
DECL|typedef|ctrl_buft
)brace
id|ctrl_buft
suffix:semicolon
multiline_comment|/********************/
multiline_comment|/* URB error codes: */
multiline_comment|/********************/
multiline_comment|/* Used to represent a list of values and their respective symbolic names */
DECL|struct|hfcusb_symbolic_list
r_struct
id|hfcusb_symbolic_list
(brace
DECL|member|num
r_const
r_int
id|num
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|urb_errlist
r_static
r_struct
id|hfcusb_symbolic_list
id|urb_errlist
(braket
)braket
op_assign
(brace
(brace
op_minus
id|ENOMEM
comma
l_string|&quot;No memory for allocation of internal structures&quot;
)brace
comma
(brace
op_minus
id|ENOSPC
comma
l_string|&quot;The host controller&squot;s bandwidth is already consumed&quot;
)brace
comma
(brace
op_minus
id|ENOENT
comma
l_string|&quot;URB was canceled by unlink_urb&quot;
)brace
comma
(brace
op_minus
id|EXDEV
comma
l_string|&quot;ISO transfer only partially completed&quot;
)brace
comma
(brace
op_minus
id|EAGAIN
comma
l_string|&quot;Too match scheduled for the future&quot;
)brace
comma
(brace
op_minus
id|ENXIO
comma
l_string|&quot;URB already queued&quot;
)brace
comma
(brace
op_minus
id|EFBIG
comma
l_string|&quot;Too much ISO frames requested&quot;
)brace
comma
(brace
op_minus
id|ENOSR
comma
l_string|&quot;Buffer error (overrun)&quot;
)brace
comma
(brace
op_minus
id|EPIPE
comma
l_string|&quot;Specified endpoint is stalled (device not responding)&quot;
)brace
comma
(brace
op_minus
id|EOVERFLOW
comma
l_string|&quot;Babble (bad cable?)&quot;
)brace
comma
(brace
op_minus
id|EPROTO
comma
l_string|&quot;Bit-stuff error (bad cable?)&quot;
)brace
comma
(brace
op_minus
id|EILSEQ
comma
l_string|&quot;CRC/Timeout&quot;
)brace
comma
(brace
op_minus
id|ETIMEDOUT
comma
l_string|&quot;NAK (device does not respond)&quot;
)brace
comma
(brace
op_minus
id|ESHUTDOWN
comma
l_string|&quot;Device unplugged&quot;
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*****************************************************/
multiline_comment|/* device dependant information to support different */
multiline_comment|/* ISDN Ta&squot;s using the HFC-S USB chip                */
multiline_comment|/*****************************************************/
multiline_comment|/* USB descriptor need to contain one of the following EndPoint combination: */
DECL|macro|CNF_4INT3ISO
mdefine_line|#define CNF_4INT3ISO&t;1&t;
singleline_comment|// 4 INT IN, 3 ISO OUT
DECL|macro|CNF_3INT3ISO
mdefine_line|#define CNF_3INT3ISO&t;2&t;
singleline_comment|// 3 INT IN, 3 ISO OUT
DECL|macro|CNF_4ISO3ISO
mdefine_line|#define CNF_4ISO3ISO&t;3&t;
singleline_comment|// 4 ISO IN, 3 ISO OUT
DECL|macro|CNF_3ISO3ISO
mdefine_line|#define CNF_3ISO3ISO&t;4&t;
singleline_comment|// 3 ISO IN, 3 ISO OUT
DECL|macro|EP_NUL
mdefine_line|#define EP_NUL 1&t;&t;
singleline_comment|// Endpoint at this position not allowed
DECL|macro|EP_NOP
mdefine_line|#define EP_NOP 2&t;&t;
singleline_comment|// all type of endpoints allowed at this position
DECL|macro|EP_ISO
mdefine_line|#define EP_ISO 3&t;&t;
singleline_comment|// Isochron endpoint mandatory at this position
DECL|macro|EP_BLK
mdefine_line|#define EP_BLK 4&t;&t;
singleline_comment|// Bulk endpoint mandatory at this position
DECL|macro|EP_INT
mdefine_line|#define EP_INT 5&t;&t;
singleline_comment|// Interrupt endpoint mandatory at this position
multiline_comment|/* this array represents all endpoints possible in the HCF-USB the last&n;* 3 entries are the configuration number, the minimum interval for&n;* Interrupt endpoints &amp; boolean if E-channel logging possible&n;*/
DECL|variable|validconf
r_int
id|validconf
(braket
)braket
(braket
l_int|19
)braket
op_assign
(brace
singleline_comment|// INT in, ISO out config
(brace
id|EP_NUL
comma
id|EP_INT
comma
id|EP_NUL
comma
id|EP_INT
comma
id|EP_NUL
comma
id|EP_INT
comma
id|EP_NOP
comma
id|EP_INT
comma
id|EP_ISO
comma
id|EP_NUL
comma
id|EP_ISO
comma
id|EP_NUL
comma
id|EP_ISO
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|CNF_4INT3ISO
comma
l_int|2
comma
l_int|1
)brace
comma
(brace
id|EP_NUL
comma
id|EP_INT
comma
id|EP_NUL
comma
id|EP_INT
comma
id|EP_NUL
comma
id|EP_INT
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_ISO
comma
id|EP_NUL
comma
id|EP_ISO
comma
id|EP_NUL
comma
id|EP_ISO
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|CNF_3INT3ISO
comma
l_int|2
comma
l_int|0
)brace
comma
singleline_comment|// ISO in, ISO out config
(brace
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_NOP
comma
id|EP_ISO
comma
id|CNF_4ISO3ISO
comma
l_int|2
comma
l_int|1
)brace
comma
(brace
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_ISO
comma
id|EP_NUL
comma
id|EP_NUL
comma
id|CNF_3ISO3ISO
comma
l_int|2
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
singleline_comment|// EOL element
)brace
suffix:semicolon
singleline_comment|// string description of chosen config
DECL|variable|conf_str
r_char
op_star
id|conf_str
(braket
)braket
op_assign
(brace
l_string|&quot;4 Interrupt IN + 3 Isochron OUT&quot;
comma
l_string|&quot;3 Interrupt IN + 3 Isochron OUT&quot;
comma
l_string|&quot;4 Isochron IN + 3 Isochron OUT&quot;
comma
l_string|&quot;3 Isochron IN + 3 Isochron OUT&quot;
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|vendor
r_int
id|vendor
suffix:semicolon
singleline_comment|// vendor id
DECL|member|prod_id
r_int
id|prod_id
suffix:semicolon
singleline_comment|// product id
DECL|member|vend_name
r_char
op_star
id|vend_name
suffix:semicolon
singleline_comment|// vendor string
DECL|member|led_scheme
id|__u8
id|led_scheme
suffix:semicolon
singleline_comment|// led display scheme
DECL|member|led_bits
r_int
r_int
id|led_bits
(braket
l_int|8
)braket
suffix:semicolon
singleline_comment|// array of 8 possible LED bitmask settings
DECL|typedef|vendor_data
)brace
id|vendor_data
suffix:semicolon
DECL|macro|LED_OFF
mdefine_line|#define LED_OFF      0&t;&t;
singleline_comment|// no LED support
DECL|macro|LED_SCHEME1
mdefine_line|#define LED_SCHEME1  1&t;&t;
singleline_comment|// LED standard scheme
DECL|macro|LED_SCHEME2
mdefine_line|#define LED_SCHEME2  2&t;&t;
singleline_comment|// not used yet...
DECL|macro|LED_POWER_ON
mdefine_line|#define LED_POWER_ON&t;1
DECL|macro|LED_POWER_OFF
mdefine_line|#define LED_POWER_OFF&t;2
DECL|macro|LED_S0_ON
mdefine_line|#define LED_S0_ON&t;3
DECL|macro|LED_S0_OFF
mdefine_line|#define LED_S0_OFF&t;4
DECL|macro|LED_B1_ON
mdefine_line|#define LED_B1_ON&t;5
DECL|macro|LED_B1_OFF
mdefine_line|#define LED_B1_OFF&t;6
DECL|macro|LED_B1_DATA
mdefine_line|#define LED_B1_DATA&t;7
DECL|macro|LED_B2_ON
mdefine_line|#define LED_B2_ON&t;8
DECL|macro|LED_B2_OFF
mdefine_line|#define LED_B2_OFF&t;9
DECL|macro|LED_B2_DATA
mdefine_line|#define LED_B2_DATA&t;10
DECL|macro|LED_NORMAL
mdefine_line|#define LED_NORMAL   0&t;&t;
singleline_comment|// LEDs are normal
DECL|macro|LED_INVERTED
mdefine_line|#define LED_INVERTED 1&t;&t;
singleline_comment|// LEDs are inverted
multiline_comment|/* time in ms to perform a Flashing LED when B-Channel has traffic */
DECL|macro|LED_TIME
mdefine_line|#define LED_TIME      250
macro_line|#endif&t;&t;&t;&t;
singleline_comment|// __HFC_USB_H__
eof
