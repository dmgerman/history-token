macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;media/saa7146_vv.h&gt;
DECL|function|saa7146_i2c_func
r_static
id|u32
id|saa7146_i2c_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
singleline_comment|//fm&t;DEB_I2C((&quot;&squot;%s&squot;.&bslash;n&quot;, adapter-&gt;name));
r_return
id|I2C_FUNC_I2C
op_or
id|I2C_FUNC_SMBUS_QUICK
op_or
id|I2C_FUNC_SMBUS_READ_BYTE
op_or
id|I2C_FUNC_SMBUS_WRITE_BYTE
op_or
id|I2C_FUNC_SMBUS_READ_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WRITE_BYTE_DATA
suffix:semicolon
)brace
multiline_comment|/* this function returns the status-register of our i2c-device */
DECL|function|saa7146_i2c_status
r_static
r_inline
id|u32
id|saa7146_i2c_status
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
id|u32
id|iicsta
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|I2C_STATUS
)paren
suffix:semicolon
multiline_comment|/*&n;&t;DEB_I2C((&quot;status: 0x%08x&bslash;n&quot;,iicsta));&n;*/
r_return
id|iicsta
suffix:semicolon
)brace
multiline_comment|/* this function runs through the i2c-messages and prepares the data to be&n;   sent through the saa7146. have a look at the specifications p. 122 ff&n;   to understand this. it returns the number of u32s to send, or -1&n;   in case of an error. */
DECL|function|saa7146_i2c_msg_prepare
r_static
r_int
id|saa7146_i2c_msg_prepare
c_func
(paren
r_const
r_struct
id|i2c_msg
op_star
id|m
comma
r_int
id|num
comma
id|u32
op_star
id|op
)paren
(brace
r_int
id|h1
comma
id|h2
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|addr
suffix:semicolon
r_int
id|mem
op_assign
l_int|0
comma
id|op_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* first determine size of needed memory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mem
op_add_assign
id|m
(braket
id|i
)braket
dot
id|len
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* worst case: we need one u32 for three bytes to be send&n;&t;   plus one extra byte to address the device */
id|mem
op_assign
l_int|1
op_plus
(paren
(paren
id|mem
op_minus
l_int|1
)paren
op_div
l_int|3
)paren
suffix:semicolon
multiline_comment|/* we assume that op points to a memory of at least SAA7146_I2C_MEM bytes&n;&t;   size. if we exceed this limit... */
r_if
c_cond
(paren
(paren
l_int|4
op_star
id|mem
)paren
OG
id|SAA7146_I2C_MEM
)paren
(brace
singleline_comment|//fm&t;&t;DEB_I2C((&quot;cannot prepare i2c-message.&bslash;n&quot;));
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* be careful: clear out the i2c-mem first */
id|memset
c_func
(paren
id|op
comma
l_int|0
comma
r_sizeof
(paren
id|u32
)paren
op_star
id|mem
)paren
suffix:semicolon
multiline_comment|/* loop through all messages */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* insert the address of the i2c-slave.&n;&t;&t;   note: we get 7 bit i2c-addresses,&n;&t;&t;   so we have to perform a translation */
id|addr
op_assign
(paren
id|m
(braket
id|i
)braket
dot
id|addr
op_star
l_int|2
)paren
op_plus
(paren
(paren
l_int|0
op_ne
(paren
id|m
(braket
id|i
)braket
dot
id|flags
op_amp
id|I2C_M_RD
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|h1
op_assign
id|op_count
op_div
l_int|3
suffix:semicolon
id|h2
op_assign
id|op_count
op_mod
l_int|3
suffix:semicolon
id|op
(braket
id|h1
)braket
op_or_assign
(paren
(paren
id|u8
)paren
id|addr
op_lshift
(paren
(paren
l_int|3
op_minus
id|h2
)paren
op_star
l_int|8
)paren
)paren
suffix:semicolon
id|op
(braket
id|h1
)braket
op_or_assign
(paren
id|SAA7146_I2C_START
op_lshift
(paren
(paren
l_int|3
op_minus
id|h2
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|op_count
op_increment
suffix:semicolon
multiline_comment|/* loop through all bytes of message i */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|m
(braket
id|i
)braket
dot
id|len
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* insert the data bytes */
id|h1
op_assign
id|op_count
op_div
l_int|3
suffix:semicolon
id|h2
op_assign
id|op_count
op_mod
l_int|3
suffix:semicolon
id|op
(braket
id|h1
)braket
op_or_assign
(paren
(paren
id|u32
)paren
(paren
(paren
id|u8
)paren
id|m
(braket
id|i
)braket
dot
id|buf
(braket
id|j
)braket
)paren
op_lshift
(paren
(paren
l_int|3
op_minus
id|h2
)paren
op_star
l_int|8
)paren
)paren
suffix:semicolon
id|op
(braket
id|h1
)braket
op_or_assign
(paren
id|SAA7146_I2C_CONT
op_lshift
(paren
(paren
l_int|3
op_minus
id|h2
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|op_count
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/* have a look at the last byte inserted:&n;&t;  if it was: ...CONT change it to ...STOP */
id|h1
op_assign
(paren
id|op_count
op_minus
l_int|1
)paren
op_div
l_int|3
suffix:semicolon
id|h2
op_assign
(paren
id|op_count
op_minus
l_int|1
)paren
op_mod
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|SAA7146_I2C_CONT
op_eq
(paren
l_int|0x3
op_amp
(paren
id|op
(braket
id|h1
)braket
op_rshift
(paren
(paren
l_int|3
op_minus
id|h2
)paren
op_star
l_int|2
)paren
)paren
)paren
)paren
(brace
id|op
(braket
id|h1
)braket
op_and_assign
op_complement
(paren
l_int|0x2
op_lshift
(paren
(paren
l_int|3
op_minus
id|h2
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|op
(braket
id|h1
)braket
op_or_assign
(paren
id|SAA7146_I2C_STOP
op_lshift
(paren
(paren
l_int|3
op_minus
id|h2
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* return the number of u32s to send */
r_return
id|mem
suffix:semicolon
)brace
multiline_comment|/* this functions loops through all i2c-messages. normally, it should determine&n;   which bytes were read through the adapter and write them back to the corresponding&n;   i2c-message. but instead, we simply write back all bytes.&n;   fixme: this could be improved. */
DECL|function|saa7146_i2c_msg_cleanup
r_static
r_int
id|saa7146_i2c_msg_cleanup
c_func
(paren
r_const
r_struct
id|i2c_msg
op_star
id|m
comma
r_int
id|num
comma
id|u32
op_star
id|op
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|op_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* loop through all messages */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|op_count
op_increment
suffix:semicolon
multiline_comment|/* loop throgh all bytes of message i */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|m
(braket
id|i
)braket
dot
id|len
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* write back all bytes that could have been read */
id|m
(braket
id|i
)braket
dot
id|buf
(braket
id|j
)braket
op_assign
(paren
id|op
(braket
id|op_count
op_div
l_int|3
)braket
op_rshift
(paren
(paren
l_int|3
op_minus
(paren
id|op_count
op_mod
l_int|3
)paren
)paren
op_star
l_int|8
)paren
)paren
suffix:semicolon
id|op_count
op_increment
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this functions resets the i2c-device and returns 0 if everything was fine, otherwise -1 */
DECL|function|saa7146_i2c_reset
r_static
r_int
id|saa7146_i2c_reset
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* get current status */
id|u32
id|status
op_assign
id|saa7146_i2c_status
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* clear registers for sure */
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
id|dev-&gt;i2c_bitrate
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_TRANSFER
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* check if any operation is still in progress */
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|status
op_amp
id|SAA7146_I2C_BUSY
)paren
)paren
(brace
multiline_comment|/* yes, kill ongoing operation */
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;busy_state detected.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* set &quot;ABORT-OPERATION&quot;-bit (bit 7)*/
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
(paren
id|dev-&gt;i2c_bitrate
op_or
id|MASK_07
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_00
op_or
id|MASK_16
)paren
)paren
suffix:semicolon
id|msleep
c_func
(paren
id|SAA7146_I2C_DELAY
)paren
suffix:semicolon
multiline_comment|/* clear all error-bits pending; this is needed because p.123, note 1 */
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
id|dev-&gt;i2c_bitrate
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_00
op_or
id|MASK_16
)paren
)paren
suffix:semicolon
id|msleep
c_func
(paren
id|SAA7146_I2C_DELAY
)paren
suffix:semicolon
)brace
multiline_comment|/* check if any error is (still) present. (this can be necessary because p.123, note 1) */
id|status
op_assign
id|saa7146_i2c_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;i2c_bitrate
op_ne
id|status
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;error_state detected. status:0x%08x&bslash;n&quot;
comma
id|status
)paren
)paren
suffix:semicolon
multiline_comment|/* Repeat the abort operation. This seems to be necessary&n;&t;&t;   after serious protocol errors caused by e.g. the SAA7740 */
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
(paren
id|dev-&gt;i2c_bitrate
op_or
id|MASK_07
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_00
op_or
id|MASK_16
)paren
)paren
suffix:semicolon
id|msleep
c_func
(paren
id|SAA7146_I2C_DELAY
)paren
suffix:semicolon
multiline_comment|/* clear all error-bits pending */
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
id|dev-&gt;i2c_bitrate
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_00
op_or
id|MASK_16
)paren
)paren
suffix:semicolon
id|msleep
c_func
(paren
id|SAA7146_I2C_DELAY
)paren
suffix:semicolon
multiline_comment|/* the data sheet says it might be necessary to clear the status&n;&t;&t;   twice after an abort */
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
id|dev-&gt;i2c_bitrate
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_00
op_or
id|MASK_16
)paren
)paren
suffix:semicolon
id|msleep
c_func
(paren
id|SAA7146_I2C_DELAY
)paren
suffix:semicolon
)brace
multiline_comment|/* if any error is still present, a fatal error has occured ... */
id|status
op_assign
id|saa7146_i2c_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;i2c_bitrate
op_ne
id|status
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;fatal error. status:0x%08x&bslash;n&quot;
comma
id|status
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this functions writes out the data-byte &squot;dword&squot; to the i2c-device.&n;   it returns 0 if ok, -1 if the transfer failed, -2 if the transfer&n;   failed badly (e.g. address error) */
DECL|function|saa7146_i2c_writeout
r_static
r_int
id|saa7146_i2c_writeout
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
id|u32
op_star
id|dword
comma
r_int
id|short_delay
)paren
(brace
id|u32
id|status
op_assign
l_int|0
comma
id|mc2
op_assign
l_int|0
suffix:semicolon
r_int
id|trial
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* write out i2c-command */
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;before: 0x%08x (status: 0x%08x), %d&bslash;n&quot;
comma
op_star
id|dword
comma
id|saa7146_read
c_func
(paren
id|dev
comma
id|I2C_STATUS
)paren
comma
id|dev-&gt;i2c_op
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|SAA7146_USE_I2C_IRQ
op_amp
id|dev-&gt;ext-&gt;flags
)paren
)paren
(brace
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
id|dev-&gt;i2c_bitrate
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_TRANSFER
comma
op_star
id|dword
)paren
suffix:semicolon
id|dev-&gt;i2c_op
op_assign
l_int|1
suffix:semicolon
id|SAA7146_IER_ENABLE
c_func
(paren
id|dev
comma
id|MASK_16
op_or
id|MASK_17
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_00
op_or
id|MASK_16
)paren
)paren
suffix:semicolon
id|wait_event_interruptible
c_func
(paren
id|dev-&gt;i2c_wq
comma
id|dev-&gt;i2c_op
op_eq
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
multiline_comment|/* a signal arrived */
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|status
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|I2C_STATUS
)paren
suffix:semicolon
)brace
r_else
(brace
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_STATUS
comma
id|dev-&gt;i2c_bitrate
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|I2C_TRANSFER
comma
op_star
id|dword
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_00
op_or
id|MASK_16
)paren
)paren
suffix:semicolon
multiline_comment|/* do not poll for i2c-status before upload is complete */
id|timeout
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|100
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* 10ms */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|mc2
op_assign
(paren
id|saa7146_read
c_func
(paren
id|dev
comma
id|MC2
)paren
op_amp
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|mc2
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;saa7146_i2c_writeout: timed out waiting for MC2&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
multiline_comment|/* wait until we get a transfer done or error */
id|timeout
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|100
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* 10ms */
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/**&n;&t;&t;&t; *  first read usually delivers bogus results...&n;&t;&t;&t; */
id|saa7146_i2c_status
c_func
(paren
id|dev
)paren
suffix:semicolon
id|status
op_assign
id|saa7146_i2c_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x3
)paren
op_ne
l_int|1
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
(brace
multiline_comment|/* this is normal when probing the bus&n;&t;&t;&t;&t; * (no answer from nonexisistant device...)&n;&t;&t;&t;&t; */
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;saa7146_i2c_writeout: timed out waiting for end of xfer&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_increment
id|trial
OL
l_int|20
)paren
op_logical_and
id|short_delay
)paren
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_else
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* give a detailed status report */
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|status
op_amp
id|SAA7146_I2C_ERR
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|status
op_amp
id|SAA7146_I2C_SPERR
)paren
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;error due to invalid start/stop condition.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|status
op_amp
id|SAA7146_I2C_DTERR
)paren
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;error in data transmission.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|status
op_amp
id|SAA7146_I2C_DRERR
)paren
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;error when receiving data.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|status
op_amp
id|SAA7146_I2C_AL
)paren
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;error because arbitration lost.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* we handle address-errors here */
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|status
op_amp
id|SAA7146_I2C_APERR
)paren
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;error in address phase.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* read back data, just in case we were reading ... */
op_star
id|dword
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|I2C_TRANSFER
)paren
suffix:semicolon
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;after: 0x%08x&bslash;n&quot;
comma
op_star
id|dword
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_i2c_transfer
r_int
id|saa7146_i2c_transfer
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_const
r_struct
id|i2c_msg
op_star
id|msgs
comma
r_int
id|num
comma
r_int
id|retries
)paren
(brace
r_int
id|i
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
suffix:semicolon
id|u32
op_star
id|buffer
op_assign
id|dev-&gt;d_i2c.cpu_addr
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|address_err
op_assign
l_int|0
suffix:semicolon
r_int
id|short_delay
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
(paren
op_amp
id|dev-&gt;i2c_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;msg:%d/%d&bslash;n&quot;
comma
id|i
op_plus
l_int|1
comma
id|num
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* prepare the message(s), get number of u32s to transfer */
id|count
op_assign
id|saa7146_i2c_msg_prepare
c_func
(paren
id|msgs
comma
id|num
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
id|count
)paren
(brace
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|3
op_logical_or
l_int|0
op_ne
(paren
id|SAA7146_I2C_SHORT_DELAY
op_amp
id|dev-&gt;ext-&gt;flags
)paren
)paren
id|short_delay
op_assign
l_int|1
suffix:semicolon
r_do
(brace
multiline_comment|/* reset the i2c-device if necessary */
id|err
op_assign
id|saa7146_i2c_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
id|err
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;could not reset i2c-device.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* write out the u32s one after another */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|err
op_assign
id|saa7146_i2c_writeout
c_func
(paren
id|dev
comma
op_amp
id|buffer
(braket
id|i
)braket
comma
id|short_delay
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|err
)paren
(brace
multiline_comment|/* this one is unsatisfying: some i2c slaves on some&n;&t;&t;&t;&t;   dvb cards don&squot;t acknowledge correctly, so the saa7146&n;&t;&t;&t;&t;   thinks that an address error occured. in that case, the&n;&t;&t;&t;&t;   transaction should be retrying, even if an address error&n;&t;&t;&t;&t;   occured. analog saa7146 based cards extensively rely on&n;&t;&t;&t;&t;   i2c address probing, however, and address errors indicate that a&n;&t;&t;&t;&t;   device is really *not* there. retrying in that case&n;&t;&t;&t;&t;   increases the time the device needs to probe greatly, so&n;&t;&t;&t;&t;   it should be avoided. because of the fact, that only&n;&t;&t;&t;&t;   analog based cards use irq based i2c transactions (for dvb&n;&t;&t;&t;&t;   cards, this screwes up other interrupt sources), we bail out&n;&t;&t;&t;&t;   completely for analog cards after an address error and trust&n;&t;&t;&t;&t;   the saa7146 address error detection. */
r_if
c_cond
(paren
op_minus
id|EREMOTEIO
op_eq
id|err
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|SAA7146_USE_I2C_IRQ
op_amp
id|dev-&gt;ext-&gt;flags
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|address_err
op_increment
suffix:semicolon
)brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;error while sending message(s). starting again.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|err
)paren
(brace
id|err
op_assign
id|num
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* delay a bit before retrying */
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|err
op_ne
id|num
op_logical_and
id|retries
op_decrement
)paren
suffix:semicolon
multiline_comment|/* if every retry had an address error, exit right away */
r_if
c_cond
(paren
id|address_err
op_eq
id|retries
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* if any things had to be read, get the results */
r_if
c_cond
(paren
l_int|0
op_ne
id|saa7146_i2c_msg_cleanup
c_func
(paren
id|msgs
comma
id|num
comma
id|buffer
)paren
)paren
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;could not cleanup i2c-message.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* return the number of delivered messages */
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;transmission successful. (msg:%d).&bslash;n&quot;
comma
id|err
)paren
)paren
suffix:semicolon
id|out
suffix:colon
multiline_comment|/* another bug in revision 0: the i2c-registers get uploaded randomly by other&n;&t;   uploads, so we better clear them out before continueing */
r_if
c_cond
(paren
l_int|0
op_eq
id|dev-&gt;revision
)paren
(brace
id|u32
id|zero
op_assign
l_int|0
suffix:semicolon
id|saa7146_i2c_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|saa7146_i2c_writeout
c_func
(paren
id|dev
comma
op_amp
id|zero
comma
id|short_delay
)paren
)paren
(brace
id|INFO
c_func
(paren
(paren
l_string|&quot;revision 0 error. this should never happen.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;i2c_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* utility functions */
DECL|function|saa7146_i2c_xfer
r_static
r_int
id|saa7146_i2c_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_struct
id|i2c_msg
op_star
id|msg
comma
r_int
id|num
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|i2c_get_adapdata
c_func
(paren
id|adapter
)paren
suffix:semicolon
multiline_comment|/* use helper function to transfer data */
r_return
id|saa7146_i2c_transfer
c_func
(paren
id|dev
comma
id|msg
comma
id|num
comma
id|adapter-&gt;retries
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/* i2c-adapter helper functions                                              */
macro_line|#include &lt;linux/i2c-id.h&gt;
multiline_comment|/* exported algorithm data */
DECL|variable|saa7146_algo
r_static
r_struct
id|i2c_algorithm
id|saa7146_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;saa7146 i2c algorithm&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SAA7146
comma
dot
id|master_xfer
op_assign
id|saa7146_i2c_xfer
comma
dot
id|functionality
op_assign
id|saa7146_i2c_func
comma
)brace
suffix:semicolon
DECL|function|saa7146_i2c_adapter_prepare
r_int
id|saa7146_i2c_adapter_prepare
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|i2c_adapter
op_star
id|i2c_adapter
comma
id|u32
id|bitrate
)paren
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;bitrate: 0x%08x&bslash;n&quot;
comma
id|bitrate
)paren
)paren
suffix:semicolon
multiline_comment|/* enable i2c-port pins */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
(paren
id|MASK_08
op_or
id|MASK_24
)paren
)paren
suffix:semicolon
id|dev-&gt;i2c_bitrate
op_assign
id|bitrate
suffix:semicolon
id|saa7146_i2c_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_ne
id|i2c_adapter
)paren
(brace
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0))
id|i2c_adapter-&gt;data
op_assign
id|dev
suffix:semicolon
macro_line|#else
id|BUG_ON
c_func
(paren
op_logical_neg
id|i2c_adapter
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
id|i2c_adapter
comma
id|dev
)paren
suffix:semicolon
macro_line|#endif
id|i2c_adapter-&gt;algo
op_assign
op_amp
id|saa7146_algo
suffix:semicolon
id|i2c_adapter-&gt;algo_data
op_assign
l_int|NULL
suffix:semicolon
id|i2c_adapter-&gt;id
op_assign
id|I2C_ALGO_SAA7146
suffix:semicolon
id|i2c_adapter-&gt;timeout
op_assign
id|SAA7146_I2C_TIMEOUT
suffix:semicolon
id|i2c_adapter-&gt;retries
op_assign
id|SAA7146_I2C_RETRIES
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
