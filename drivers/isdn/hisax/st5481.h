multiline_comment|/*&n; * Driver for ST5481 USB ISDN modem&n; *&n; * Author       Frode Isaksen&n; * Copyright    2001 by Frode Isaksen      &lt;fisaksen@bewan.com&gt;&n; *              2001 by Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef _ST5481_H_
DECL|macro|_ST5481_H_
mdefine_line|#define _ST5481_H_
macro_line|#include &lt;linux/config.h&gt;
singleline_comment|// USB IDs, the Product Id is in the range 0x4810-0x481F
DECL|macro|ST_VENDOR_ID
mdefine_line|#define ST_VENDOR_ID 0x0483
DECL|macro|ST5481_PRODUCT_ID
mdefine_line|#define ST5481_PRODUCT_ID 0x4810
DECL|macro|ST5481_PRODUCT_ID_MASK
mdefine_line|#define ST5481_PRODUCT_ID_MASK 0xFFF0
singleline_comment|// ST5481 endpoints when using alternative setting 3 (2B+D).
singleline_comment|// To get the endpoint address, OR with 0x80 for IN endpoints.
DECL|macro|EP_CTRL
mdefine_line|#define EP_CTRL   0x00U /* Control endpoint */
DECL|macro|EP_INT
mdefine_line|#define EP_INT    0x01U /* Interrupt endpoint */
DECL|macro|EP_B1_OUT
mdefine_line|#define EP_B1_OUT 0x02U /* B1 channel out */
DECL|macro|EP_B1_IN
mdefine_line|#define EP_B1_IN  0x03U /* B1 channel in */
DECL|macro|EP_B2_OUT
mdefine_line|#define EP_B2_OUT 0x04U /* B2 channel out */
DECL|macro|EP_B2_IN
mdefine_line|#define EP_B2_IN  0x05U /* B2 channel in */
DECL|macro|EP_D_OUT
mdefine_line|#define EP_D_OUT  0x06U /* D channel out */
DECL|macro|EP_D_IN
mdefine_line|#define EP_D_IN   0x07U /* D channel in */
singleline_comment|// Number of isochronous packets. With 20 packets we get
singleline_comment|// 50 interrupts/sec for each endpoint.
DECL|macro|NUM_ISO_PACKETS_D
mdefine_line|#define NUM_ISO_PACKETS_D      20
DECL|macro|NUM_ISO_PACKETS_B
mdefine_line|#define NUM_ISO_PACKETS_B      20
singleline_comment|// Size of each isochronous packet.
singleline_comment|// In outgoing direction we need to match ISDN data rates:
singleline_comment|// D:  2 bytes / msec -&gt; 16 kbit / s
singleline_comment|// B: 16 bytes / msec -&gt; 64 kbit / s
DECL|macro|SIZE_ISO_PACKETS_D_IN
mdefine_line|#define SIZE_ISO_PACKETS_D_IN  16
DECL|macro|SIZE_ISO_PACKETS_D_OUT
mdefine_line|#define SIZE_ISO_PACKETS_D_OUT 2
DECL|macro|SIZE_ISO_PACKETS_B_IN
mdefine_line|#define SIZE_ISO_PACKETS_B_IN  32
DECL|macro|SIZE_ISO_PACKETS_B_OUT
mdefine_line|#define SIZE_ISO_PACKETS_B_OUT 8
singleline_comment|// If we overrun/underrun, we send one packet with +/- 2 bytes
DECL|macro|B_FLOW_ADJUST
mdefine_line|#define B_FLOW_ADJUST 2
singleline_comment|// Registers that are written using vendor specific device request
singleline_comment|// on endpoint 0. 
DECL|macro|LBA
mdefine_line|#define LBA&t;&t;&t;0x02 /* S loopback */
DECL|macro|SET_DEFAULT
mdefine_line|#define SET_DEFAULT&t;&t;0x06 /* Soft reset */
DECL|macro|LBB
mdefine_line|#define LBB&t;&t;&t;0x1D /* S maintenance loopback */
DECL|macro|STT
mdefine_line|#define STT&t;&t;&t;0x1e /* S force transmission signals */
DECL|macro|SDA_MIN
mdefine_line|#define SDA_MIN&t;&t;&t;0x20 /* SDA-sin minimal value */
DECL|macro|SDA_MAX
mdefine_line|#define SDA_MAX&t;&t;&t;0x21 /* SDA-sin maximal value */
DECL|macro|SDELAY_VALUE
mdefine_line|#define SDELAY_VALUE&t;&t;0x22 /* Delay between Tx and Rx clock */
DECL|macro|IN_D_COUNTER
mdefine_line|#define IN_D_COUNTER&t;&t;0x36 /* D receive channel fifo counter */
DECL|macro|OUT_D_COUNTER
mdefine_line|#define OUT_D_COUNTER&t;&t;0x37 /* D transmit channel fifo counter */
DECL|macro|IN_B1_COUNTER
mdefine_line|#define IN_B1_COUNTER&t;&t;0x38 /* B1 receive channel fifo counter */
DECL|macro|OUT_B1_COUNTER
mdefine_line|#define OUT_B1_COUNTER&t;&t;0x39 /* B1 transmit channel fifo counter */
DECL|macro|IN_B2_COUNTER
mdefine_line|#define IN_B2_COUNTER&t;&t;0x3a /* B2 receive channel fifo counter */
DECL|macro|OUT_B2_COUNTER
mdefine_line|#define OUT_B2_COUNTER&t;&t;0x3b /* B2 transmit channel fifo counter */
DECL|macro|FFCTRL_IN_D
mdefine_line|#define FFCTRL_IN_D&t;&t;0x3C /* D receive channel fifo threshold low */
DECL|macro|FFCTRH_IN_D
mdefine_line|#define FFCTRH_IN_D&t;&t;0x3D /* D receive channel fifo threshold high */
DECL|macro|FFCTRL_OUT_D
mdefine_line|#define FFCTRL_OUT_D&t;&t;0x3E /* D transmit channel fifo threshold low */
DECL|macro|FFCTRH_OUT_D
mdefine_line|#define FFCTRH_OUT_D&t;&t;0x3F /* D transmit channel fifo threshold high */
DECL|macro|FFCTRL_IN_B1
mdefine_line|#define FFCTRL_IN_B1&t;&t;0x40 /* B1 receive channel fifo threshold low */
DECL|macro|FFCTRH_IN_B1
mdefine_line|#define FFCTRH_IN_B1&t;&t;0x41 /* B1 receive channel fifo threshold high */
DECL|macro|FFCTRL_OUT_B1
mdefine_line|#define FFCTRL_OUT_B1&t;&t;0x42 /* B1 transmit channel fifo threshold low */
DECL|macro|FFCTRH_OUT_B1
mdefine_line|#define FFCTRH_OUT_B1&t;&t;0x43 /* B1 transmit channel fifo threshold high */
DECL|macro|FFCTRL_IN_B2
mdefine_line|#define FFCTRL_IN_B2&t;&t;0x44 /* B2 receive channel fifo threshold low */
DECL|macro|FFCTRH_IN_B2
mdefine_line|#define FFCTRH_IN_B2&t;&t;0x45 /* B2 receive channel fifo threshold high */
DECL|macro|FFCTRL_OUT_B2
mdefine_line|#define FFCTRL_OUT_B2&t;&t;0x46 /* B2 transmit channel fifo threshold low */
DECL|macro|FFCTRH_OUT_B2
mdefine_line|#define FFCTRH_OUT_B2&t;&t;0x47 /* B2 transmit channel fifo threshold high */
DECL|macro|MPMSK
mdefine_line|#define MPMSK&t;&t;&t;0x4A /* Multi purpose interrupt MASK register */
DECL|macro|FFMSK_D
mdefine_line|#define&t;FFMSK_D&t;&t;&t;0x4c /* D fifo interrupt MASK register */
DECL|macro|FFMSK_B1
mdefine_line|#define&t;FFMSK_B1&t;&t;0x4e /* B1 fifo interrupt MASK register */
DECL|macro|FFMSK_B2
mdefine_line|#define&t;FFMSK_B2&t;&t;0x50 /* B2 fifo interrupt MASK register */
DECL|macro|GPIO_DIR
mdefine_line|#define GPIO_DIR&t;&t;0x52 /* GPIO pins direction registers */
DECL|macro|GPIO_OUT
mdefine_line|#define GPIO_OUT&t;&t;0x53 /* GPIO pins output register */
DECL|macro|GPIO_IN
mdefine_line|#define GPIO_IN&t;&t;&t;0x54 /* GPIO pins input register */ 
DECL|macro|TXCI
mdefine_line|#define TXCI&t;&t;&t;0x56 /* CI command to be transmitted */
singleline_comment|// Format of the interrupt packet received on endpoint 1:
singleline_comment|//
singleline_comment|// +--------+--------+--------+--------+--------+--------+
singleline_comment|// !MPINT   !FFINT_D !FFINT_B1!FFINT_B2!CCIST   !GPIO_INT!
singleline_comment|// +--------+--------+--------+--------+--------+--------+
singleline_comment|// Offsets in the interrupt packet
DECL|macro|MPINT
mdefine_line|#define MPINT&t;&t;&t;0
DECL|macro|FFINT_D
mdefine_line|#define FFINT_D&t;&t;&t;1
DECL|macro|FFINT_B1
mdefine_line|#define FFINT_B1&t;&t;2
DECL|macro|FFINT_B2
mdefine_line|#define FFINT_B2&t;&t;3
DECL|macro|CCIST
mdefine_line|#define CCIST&t;&t;&t;4
DECL|macro|GPIO_INT
mdefine_line|#define GPIO_INT&t;&t;5
DECL|macro|INT_PKT_SIZE
mdefine_line|#define INT_PKT_SIZE            6
singleline_comment|// MPINT
DECL|macro|LSD_INT
mdefine_line|#define LSD_INT                 0x80 /* S line activity detected */
DECL|macro|RXCI_INT
mdefine_line|#define RXCI_INT&t;&t;0x40 /* Indicate primitive arrived */
DECL|macro|DEN_INT
mdefine_line|#define&t;DEN_INT&t;&t;&t;0x20 /* Signal enabling data out of D Tx fifo */
DECL|macro|DCOLL_INT
mdefine_line|#define DCOLL_INT&t;&t;0x10 /* D channel collision */
DECL|macro|AMIVN_INT
mdefine_line|#define AMIVN_INT&t;&t;0x04 /* AMI violation number reached 2 */
DECL|macro|INFOI_INT
mdefine_line|#define INFOI_INT&t;&t;0x04 /* INFOi changed */
DECL|macro|DRXON_INT
mdefine_line|#define DRXON_INT               0x02 /* Reception channel active */
DECL|macro|GPCHG_INT
mdefine_line|#define GPCHG_INT               0x01 /* GPIO pin value changed */
singleline_comment|// FFINT_x
DECL|macro|IN_OVERRUN
mdefine_line|#define IN_OVERRUN&t;&t;0x80 /* In fifo overrun */
DECL|macro|OUT_UNDERRUN
mdefine_line|#define OUT_UNDERRUN&t;&t;0x40 /* Out fifo underrun */
DECL|macro|IN_UP
mdefine_line|#define IN_UP&t;&t;&t;0x20 /* In fifo thresholdh up-crossed */
DECL|macro|IN_DOWN
mdefine_line|#define IN_DOWN&t;&t;&t;0x10 /* In fifo thresholdl down-crossed */
DECL|macro|OUT_UP
mdefine_line|#define OUT_UP&t;&t;&t;0x08 /* Out fifo thresholdh up-crossed */
DECL|macro|OUT_DOWN
mdefine_line|#define OUT_DOWN&t;&t;0x04 /* Out fifo thresholdl down-crossed */
DECL|macro|IN_COUNTER_ZEROED
mdefine_line|#define IN_COUNTER_ZEROED&t;0x02 /* In down-counter reached 0 */
DECL|macro|OUT_COUNTER_ZEROED
mdefine_line|#define OUT_COUNTER_ZEROED&t;0x01 /* Out down-counter reached 0 */
DECL|macro|ANY_REC_INT
mdefine_line|#define ANY_REC_INT&t;(IN_OVERRUN+IN_UP+IN_DOWN+IN_COUNTER_ZEROED)
DECL|macro|ANY_XMIT_INT
mdefine_line|#define ANY_XMIT_INT&t;(OUT_UNDERRUN+OUT_UP+OUT_DOWN+OUT_COUNTER_ZEROED)
singleline_comment|// Level 1 commands that are sent using the TXCI device request
DECL|macro|ST5481_CMD_DR
mdefine_line|#define ST5481_CMD_DR&t;&t; 0x0 /* Deactivation Request */
DECL|macro|ST5481_CMD_RES
mdefine_line|#define ST5481_CMD_RES&t;&t; 0x1 /* state machine RESet */
DECL|macro|ST5481_CMD_TM1
mdefine_line|#define ST5481_CMD_TM1&t;&t; 0x2 /* Test Mode 1 */
DECL|macro|ST5481_CMD_TM2
mdefine_line|#define ST5481_CMD_TM2&t;&t; 0x3 /* Test Mode 2 */
DECL|macro|ST5481_CMD_PUP
mdefine_line|#define ST5481_CMD_PUP&t;&t; 0x7 /* Power UP */
DECL|macro|ST5481_CMD_AR8
mdefine_line|#define ST5481_CMD_AR8&t;&t; 0x8 /* Activation Request class 1 */
DECL|macro|ST5481_CMD_AR10
mdefine_line|#define ST5481_CMD_AR10&t;&t; 0x9 /* Activation Request class 2 */
DECL|macro|ST5481_CMD_ARL
mdefine_line|#define ST5481_CMD_ARL&t;&t; 0xA /* Activation Request Loopback */
DECL|macro|ST5481_CMD_PDN
mdefine_line|#define ST5481_CMD_PDN&t;&t; 0xF /* Power DoWn */
singleline_comment|// Turn on/off the LEDs using the GPIO device request.
singleline_comment|// To use the B LEDs, number_of_leds must be set to 4
DECL|macro|B1_LED
mdefine_line|#define B1_LED&t;&t;0x10U
DECL|macro|B2_LED
mdefine_line|#define B2_LED&t;&t;0x20U
DECL|macro|GREEN_LED
mdefine_line|#define GREEN_LED&t;0x40U
DECL|macro|RED_LED
mdefine_line|#define RED_LED&t;        0x80U
singleline_comment|// D channel out states
r_enum
(brace
DECL|enumerator|ST_DOUT_NONE
id|ST_DOUT_NONE
comma
DECL|enumerator|ST_DOUT_SHORT_INIT
id|ST_DOUT_SHORT_INIT
comma
DECL|enumerator|ST_DOUT_SHORT_WAIT_DEN
id|ST_DOUT_SHORT_WAIT_DEN
comma
DECL|enumerator|ST_DOUT_LONG_INIT
id|ST_DOUT_LONG_INIT
comma
DECL|enumerator|ST_DOUT_LONG_WAIT_DEN
id|ST_DOUT_LONG_WAIT_DEN
comma
DECL|enumerator|ST_DOUT_NORMAL
id|ST_DOUT_NORMAL
comma
DECL|enumerator|ST_DOUT_WAIT_FOR_UNDERRUN
id|ST_DOUT_WAIT_FOR_UNDERRUN
comma
DECL|enumerator|ST_DOUT_WAIT_FOR_NOT_BUSY
id|ST_DOUT_WAIT_FOR_NOT_BUSY
comma
DECL|enumerator|ST_DOUT_WAIT_FOR_STOP
id|ST_DOUT_WAIT_FOR_STOP
comma
DECL|enumerator|ST_DOUT_WAIT_FOR_RESET
id|ST_DOUT_WAIT_FOR_RESET
comma
)brace
suffix:semicolon
DECL|macro|DOUT_STATE_COUNT
mdefine_line|#define DOUT_STATE_COUNT (ST_DOUT_WAIT_FOR_RESET + 1)
singleline_comment|// D channel out events
r_enum
(brace
DECL|enumerator|EV_DOUT_START_XMIT
id|EV_DOUT_START_XMIT
comma
DECL|enumerator|EV_DOUT_COMPLETE
id|EV_DOUT_COMPLETE
comma
DECL|enumerator|EV_DOUT_DEN
id|EV_DOUT_DEN
comma
DECL|enumerator|EV_DOUT_RESETED
id|EV_DOUT_RESETED
comma
DECL|enumerator|EV_DOUT_STOPPED
id|EV_DOUT_STOPPED
comma
DECL|enumerator|EV_DOUT_COLL
id|EV_DOUT_COLL
comma
DECL|enumerator|EV_DOUT_UNDERRUN
id|EV_DOUT_UNDERRUN
comma
)brace
suffix:semicolon
DECL|macro|DOUT_EVENT_COUNT
mdefine_line|#define DOUT_EVENT_COUNT (EV_DOUT_UNDERRUN + 1)
singleline_comment|// ----------------------------------------------------------------------
r_enum
(brace
DECL|enumerator|ST_L1_F3
id|ST_L1_F3
comma
DECL|enumerator|ST_L1_F4
id|ST_L1_F4
comma
DECL|enumerator|ST_L1_F6
id|ST_L1_F6
comma
DECL|enumerator|ST_L1_F7
id|ST_L1_F7
comma
DECL|enumerator|ST_L1_F8
id|ST_L1_F8
comma
)brace
suffix:semicolon
DECL|macro|L1_STATE_COUNT
mdefine_line|#define L1_STATE_COUNT (ST_L1_F8+1)
singleline_comment|// The first 16 entries match the Level 1 indications that 
singleline_comment|// are found at offset 4 (CCIST) in the interrupt packet
r_enum
(brace
DECL|enumerator|EV_IND_DP
id|EV_IND_DP
comma
singleline_comment|// 0000 Deactivation Pending
DECL|enumerator|EV_IND_1
id|EV_IND_1
comma
singleline_comment|// 0001
DECL|enumerator|EV_IND_2
id|EV_IND_2
comma
singleline_comment|// 0010
DECL|enumerator|EV_IND_3
id|EV_IND_3
comma
singleline_comment|// 0011
DECL|enumerator|EV_IND_RSY
id|EV_IND_RSY
comma
singleline_comment|// 0100 ReSYnchronizing
DECL|enumerator|EV_IND_5
id|EV_IND_5
comma
singleline_comment|// 0101
DECL|enumerator|EV_IND_6
id|EV_IND_6
comma
singleline_comment|// 0110
DECL|enumerator|EV_IND_7
id|EV_IND_7
comma
singleline_comment|// 0111
DECL|enumerator|EV_IND_AP
id|EV_IND_AP
comma
singleline_comment|// 1000 Activation Pending
DECL|enumerator|EV_IND_9
id|EV_IND_9
comma
singleline_comment|// 1001
DECL|enumerator|EV_IND_10
id|EV_IND_10
comma
singleline_comment|// 1010
DECL|enumerator|EV_IND_11
id|EV_IND_11
comma
singleline_comment|// 1011
DECL|enumerator|EV_IND_AI8
id|EV_IND_AI8
comma
singleline_comment|// 1100 Activation Indication class 8
DECL|enumerator|EV_IND_AI10
id|EV_IND_AI10
comma
singleline_comment|// 1101 Activation Indication class 10
DECL|enumerator|EV_IND_AIL
id|EV_IND_AIL
comma
singleline_comment|// 1110 Activation Indication Loopback
DECL|enumerator|EV_IND_DI
id|EV_IND_DI
comma
singleline_comment|// 1111 Deactivation Indication
DECL|enumerator|EV_PH_ACTIVATE_REQ
id|EV_PH_ACTIVATE_REQ
comma
DECL|enumerator|EV_PH_DEACTIVATE_REQ
id|EV_PH_DEACTIVATE_REQ
comma
DECL|enumerator|EV_TIMER3
id|EV_TIMER3
comma
)brace
suffix:semicolon
DECL|macro|L1_EVENT_COUNT
mdefine_line|#define L1_EVENT_COUNT (EV_TIMER3 + 1)
DECL|macro|ERR
mdefine_line|#define ERR(format, arg...) &bslash;&n;printk(KERN_ERR __FILE__ &quot;: &quot; __FUNCTION__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|WARN
mdefine_line|#define WARN(format, arg...) &bslash;&n;printk(KERN_WARNING __FILE__ &quot;: &quot; __FUNCTION__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|INFO
mdefine_line|#define INFO(format, arg...) &bslash;&n;printk(KERN_INFO __FILE__ &quot;: &quot; __FUNCTION__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
macro_line|#include &quot;st5481_hdlc.h&quot;
macro_line|#include &quot;fsm.h&quot;
macro_line|#include &quot;hisax_if.h&quot;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/* ======================================================================&n; * FIFO handling&n; */
multiline_comment|/* Generic FIFO structure */
DECL|struct|fifo
r_struct
id|fifo
(brace
DECL|member|r
DECL|member|w
DECL|member|count
DECL|member|size
id|u_char
id|r
comma
id|w
comma
id|count
comma
id|size
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Init an FIFO&n; */
DECL|function|fifo_init
r_static
r_inline
r_void
id|fifo_init
c_func
(paren
r_struct
id|fifo
op_star
id|fifo
comma
r_int
id|size
)paren
(brace
id|fifo-&gt;r
op_assign
id|fifo-&gt;w
op_assign
id|fifo-&gt;count
op_assign
l_int|0
suffix:semicolon
id|fifo-&gt;size
op_assign
id|size
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|fifo-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add an entry to the FIFO&n; */
DECL|function|fifo_add
r_static
r_inline
r_int
id|fifo_add
c_func
(paren
r_struct
id|fifo
op_star
id|fifo
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fifo
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|fifo-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fifo-&gt;count
op_eq
id|fifo-&gt;size
)paren
(brace
singleline_comment|// FIFO full
id|index
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Return index where to get the next data to add to the FIFO
id|index
op_assign
id|fifo-&gt;w
op_increment
op_amp
(paren
id|fifo-&gt;size
op_minus
l_int|1
)paren
suffix:semicolon
id|fifo-&gt;count
op_increment
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|fifo-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove an entry from the FIFO with the index returned.&n; */
DECL|function|fifo_remove
r_static
r_inline
r_int
id|fifo_remove
c_func
(paren
r_struct
id|fifo
op_star
id|fifo
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fifo
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|fifo-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fifo-&gt;count
)paren
(brace
singleline_comment|// FIFO empty
id|index
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Return index where to get the next data from the FIFO
id|index
op_assign
id|fifo-&gt;r
op_increment
op_amp
(paren
id|fifo-&gt;size
op_minus
l_int|1
)paren
suffix:semicolon
id|fifo-&gt;count
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|fifo-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
multiline_comment|/* ======================================================================&n; * control pipe&n; */
DECL|typedef|ctrl_complete_t
r_typedef
r_void
(paren
op_star
id|ctrl_complete_t
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|struct|ctrl_msg
r_typedef
r_struct
id|ctrl_msg
(brace
DECL|member|dr
r_struct
id|usb_ctrlrequest
id|dr
suffix:semicolon
DECL|member|complete
id|ctrl_complete_t
id|complete
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|typedef|ctrl_msg
)brace
id|ctrl_msg
suffix:semicolon
multiline_comment|/* FIFO of ctrl messages waiting to be sent */
DECL|macro|MAX_EP0_MSG
mdefine_line|#define MAX_EP0_MSG 16
DECL|struct|ctrl_msg_fifo
r_struct
id|ctrl_msg_fifo
(brace
DECL|member|f
r_struct
id|fifo
id|f
suffix:semicolon
DECL|member|data
r_struct
id|ctrl_msg
id|data
(braket
id|MAX_EP0_MSG
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_DFRAME_LEN_L1
mdefine_line|#define MAX_DFRAME_LEN_L1&t;300
DECL|macro|HSCX_BUFMAX
mdefine_line|#define HSCX_BUFMAX&t;4096
DECL|struct|st5481_ctrl
r_struct
id|st5481_ctrl
(brace
DECL|member|msg_fifo
r_struct
id|ctrl_msg_fifo
id|msg_fifo
suffix:semicolon
DECL|member|busy
r_int
r_int
id|busy
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|st5481_intr
r_struct
id|st5481_intr
(brace
singleline_comment|//&t;struct evt_fifo evt_fifo;
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|st5481_d_out
r_struct
id|st5481_d_out
(brace
DECL|member|hdlc_state
r_struct
id|hdlc_vars
id|hdlc_state
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* double buffering */
DECL|member|busy
r_int
r_int
id|busy
suffix:semicolon
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
DECL|member|fsm
r_struct
id|FsmInst
id|fsm
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|st5481_b_out
r_struct
id|st5481_b_out
(brace
DECL|member|hdlc_state
r_struct
id|hdlc_vars
id|hdlc_state
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* double buffering */
DECL|member|flow_event
id|u_char
id|flow_event
suffix:semicolon
DECL|member|busy
id|u_long
id|busy
suffix:semicolon
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|st5481_in
r_struct
id|st5481_in
(brace
DECL|member|hdlc_state
r_struct
id|hdlc_vars
id|hdlc_state
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* double buffering */
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|bufsize
r_int
id|bufsize
suffix:semicolon
DECL|member|num_packets
r_int
r_int
id|num_packets
suffix:semicolon
DECL|member|packet_size
r_int
r_int
id|packet_size
suffix:semicolon
DECL|member|ep
DECL|member|counter
r_int
r_char
id|ep
comma
id|counter
suffix:semicolon
DECL|member|rcvbuf
r_int
r_char
op_star
id|rcvbuf
suffix:semicolon
DECL|member|adapter
r_struct
id|st5481_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|hisax_if
r_struct
id|hisax_if
op_star
id|hisax_if
suffix:semicolon
)brace
suffix:semicolon
r_int
id|st5481_setup_in
c_func
(paren
r_struct
id|st5481_in
op_star
id|in
)paren
suffix:semicolon
r_void
id|st5481_release_in
c_func
(paren
r_struct
id|st5481_in
op_star
id|in
)paren
suffix:semicolon
r_void
id|st5481_in_mode
c_func
(paren
r_struct
id|st5481_in
op_star
id|in
comma
r_int
id|mode
)paren
suffix:semicolon
DECL|struct|st5481_bcs
r_struct
id|st5481_bcs
(brace
DECL|member|b_if
r_struct
id|hisax_b_if
id|b_if
suffix:semicolon
DECL|member|adapter
r_struct
id|st5481_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|b_in
r_struct
id|st5481_in
id|b_in
suffix:semicolon
DECL|member|b_out
r_struct
id|st5481_b_out
id|b_out
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|st5481_adapter
r_struct
id|st5481_adapter
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|number_of_leds
r_int
id|number_of_leds
suffix:semicolon
DECL|member|usb_dev
r_struct
id|usb_device
op_star
id|usb_dev
suffix:semicolon
DECL|member|hisax_d_if
r_struct
id|hisax_d_if
id|hisax_d_if
suffix:semicolon
DECL|member|ctrl
r_struct
id|st5481_ctrl
id|ctrl
suffix:semicolon
DECL|member|intr
r_struct
id|st5481_intr
id|intr
suffix:semicolon
DECL|member|d_in
r_struct
id|st5481_in
id|d_in
suffix:semicolon
DECL|member|d_out
r_struct
id|st5481_d_out
id|d_out
suffix:semicolon
DECL|member|leds
r_int
r_char
id|leds
suffix:semicolon
DECL|member|led_counter
r_int
r_int
id|led_counter
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|l1m
r_struct
id|FsmInst
id|l1m
suffix:semicolon
DECL|member|timer
r_struct
id|FsmTimer
id|timer
suffix:semicolon
DECL|member|bcs
r_struct
id|st5481_bcs
id|bcs
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TIMER3_VALUE
mdefine_line|#define TIMER3_VALUE 7000
multiline_comment|/* ======================================================================&n; *&n; */
multiline_comment|/*&n; * Submit an URB with error reporting. This is a macro so&n; * the __FUNCTION__ returns the caller function name.&n; */
DECL|macro|SUBMIT_URB
mdefine_line|#define SUBMIT_URB(urb) &bslash;&n;({ &bslash;&n;&t;int status; &bslash;&n;&t;if ((status = usb_submit_urb(urb)) &lt; 0) { &bslash;&n;&t;&t;WARN(&quot;usb_submit_urb failed,status=%d&quot;, status); &bslash;&n;&t;} &bslash;&n;        status; &bslash;&n;})
multiline_comment|/*&n; * USB double buffering, return the URB index (0 or 1).&n; */
DECL|function|get_buf_nr
r_static
r_inline
r_int
id|get_buf_nr
c_func
(paren
r_struct
id|urb
op_star
id|urbs
(braket
)braket
comma
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_return
(paren
id|urbs
(braket
l_int|0
)braket
op_eq
id|urb
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* B Channel */
r_int
id|st5481_setup_b
c_func
(paren
r_struct
id|st5481_bcs
op_star
id|bcs
)paren
suffix:semicolon
r_void
id|st5481_release_b
c_func
(paren
r_struct
id|st5481_bcs
op_star
id|bcs
)paren
suffix:semicolon
r_void
id|st5481_d_l2l1
c_func
(paren
r_struct
id|hisax_if
op_star
id|hisax_d_if
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* D Channel */
r_int
id|st5481_setup_d
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_void
id|st5481_release_d
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_void
id|st5481_b_l2l1
c_func
(paren
r_struct
id|hisax_if
op_star
id|b_if
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_int
id|st5481_d_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|st5481_d_exit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* USB */
r_void
id|st5481_ph_command
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
r_int
r_int
id|command
)paren
suffix:semicolon
r_int
id|st5481_setup_isocpipes
c_func
(paren
r_struct
id|urb
op_star
id|urb
(braket
l_int|2
)braket
comma
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
r_int
id|num_packets
comma
r_int
id|packet_size
comma
r_int
id|buf_size
comma
id|usb_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|st5481_release_isocpipes
c_func
(paren
r_struct
id|urb
op_star
id|urb
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_int
id|st5481_isoc_flatten
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_void
id|st5481_usb_pipe_reset
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
id|u_char
id|pipe
comma
id|ctrl_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|st5481_usb_ctrl_msg
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
id|u8
id|request
comma
id|u8
id|requesttype
comma
id|u16
id|value
comma
id|u16
id|index
comma
id|ctrl_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|st5481_usb_device_ctrl_msg
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
id|u8
id|request
comma
id|u16
id|value
comma
id|ctrl_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_int
id|st5481_setup_usb
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_void
id|st5481_release_usb
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_void
id|st5481_start
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_void
id|st5481_stop
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
singleline_comment|// ----------------------------------------------------------------------
singleline_comment|// debugging macros
DECL|macro|__debug_variable
mdefine_line|#define __debug_variable st5481_debug
macro_line|#include &quot;hisax_debug.h&quot;
macro_line|#ifdef CONFIG_HISAX_DEBUG
r_extern
r_int
id|st5481_debug
suffix:semicolon
DECL|macro|DBG_ISO_PACKET
mdefine_line|#define DBG_ISO_PACKET(level,urb) &bslash;&n;  if (level &amp; __debug_variable) dump_iso_packet(__FUNCTION__,urb)
r_static
r_void
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
DECL|function|dump_iso_packet
id|dump_iso_packet
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|urb_t
op_star
id|urb
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|len
comma
id|ofs
suffix:semicolon
id|u_char
op_star
id|data
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: packets=%d,errors=%d&bslash;n&quot;
comma
id|name
comma
id|urb-&gt;number_of_packets
comma
id|urb-&gt;error_count
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|urb-&gt;number_of_packets
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;pipe
op_amp
id|USB_DIR_IN
)paren
(brace
id|len
op_assign
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|actual_length
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|length
suffix:semicolon
)brace
id|ofs
op_assign
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;len=%.2d,ofs=%.3d &quot;
comma
id|len
comma
id|ofs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
id|data
op_assign
id|urb-&gt;transfer_buffer
op_plus
id|ofs
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|len
suffix:semicolon
id|j
op_increment
)paren
(brace
id|printk
(paren
l_string|&quot;%.2x&quot;
comma
id|data
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|ST5481_CMD_string
r_static
r_inline
r_const
r_char
op_star
id|ST5481_CMD_string
c_func
(paren
r_int
id|evt
)paren
(brace
r_static
r_char
id|s
(braket
l_int|16
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|evt
)paren
(brace
r_case
id|ST5481_CMD_DR
suffix:colon
r_return
l_string|&quot;DR&quot;
suffix:semicolon
r_case
id|ST5481_CMD_RES
suffix:colon
r_return
l_string|&quot;RES&quot;
suffix:semicolon
r_case
id|ST5481_CMD_TM1
suffix:colon
r_return
l_string|&quot;TM1&quot;
suffix:semicolon
r_case
id|ST5481_CMD_TM2
suffix:colon
r_return
l_string|&quot;TM2&quot;
suffix:semicolon
r_case
id|ST5481_CMD_PUP
suffix:colon
r_return
l_string|&quot;PUP&quot;
suffix:semicolon
r_case
id|ST5481_CMD_AR8
suffix:colon
r_return
l_string|&quot;AR8&quot;
suffix:semicolon
r_case
id|ST5481_CMD_AR10
suffix:colon
r_return
l_string|&quot;AR10&quot;
suffix:semicolon
r_case
id|ST5481_CMD_ARL
suffix:colon
r_return
l_string|&quot;ARL&quot;
suffix:semicolon
r_case
id|ST5481_CMD_PDN
suffix:colon
r_return
l_string|&quot;PDN&quot;
suffix:semicolon
)brace
suffix:semicolon
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;0x%x&quot;
comma
id|evt
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
macro_line|#else
DECL|macro|DBG_ISO_PACKET
mdefine_line|#define DBG_ISO_PACKET(level,urb) do {} while (0)
macro_line|#endif
macro_line|#endif 
eof
