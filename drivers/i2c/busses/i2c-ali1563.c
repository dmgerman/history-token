multiline_comment|/**&n; *&t;i2c-ali1563.c - i2c driver for the ALi 1563 Southbridge&n; *&n; *&t;Copyright (C) 2004 Patrick Mochel&n; *&n; *&t;The 1563 southbridge is deceptively similar to the 1533, with a&n; *&t;few notable exceptions. One of those happens to be the fact they&n; *&t;upgraded the i2c core to be 2.0 compliant, and happens to be almost&n; *&t;identical to the i2c controller found in the Intel 801 south&n; *&t;bridges.&n; *&n; *&t;This driver is based on a mix of the 15x3, 1535, and i801 drivers,&n; *&t;with a little help from the ALi 1563 spec.&n; *&n; *&t;This file is released under the GPLv2&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|ALI1563_MAX_TIMEOUT
mdefine_line|#define ALI1563_MAX_TIMEOUT&t;500
DECL|macro|ALI1563_SMBBA
mdefine_line|#define&t;ALI1563_SMBBA&t;&t;0x80
DECL|macro|ALI1563_SMB_IOEN
mdefine_line|#define ALI1563_SMB_IOEN&t;1
DECL|macro|ALI1563_SMB_HOSTEN
mdefine_line|#define ALI1563_SMB_HOSTEN&t;2
DECL|macro|ALI1563_SMB_IOSIZE
mdefine_line|#define ALI1563_SMB_IOSIZE&t;16
DECL|macro|SMB_HST_STS
mdefine_line|#define SMB_HST_STS&t;(ali1563_smba + 0)
DECL|macro|SMB_HST_CNTL1
mdefine_line|#define SMB_HST_CNTL1&t;(ali1563_smba + 1)
DECL|macro|SMB_HST_CNTL2
mdefine_line|#define SMB_HST_CNTL2&t;(ali1563_smba + 2)
DECL|macro|SMB_HST_CMD
mdefine_line|#define SMB_HST_CMD&t;(ali1563_smba + 3)
DECL|macro|SMB_HST_ADD
mdefine_line|#define SMB_HST_ADD&t;(ali1563_smba + 4)
DECL|macro|SMB_HST_DAT0
mdefine_line|#define SMB_HST_DAT0&t;(ali1563_smba + 5)
DECL|macro|SMB_HST_DAT1
mdefine_line|#define SMB_HST_DAT1&t;(ali1563_smba + 6)
DECL|macro|SMB_BLK_DAT
mdefine_line|#define SMB_BLK_DAT&t;(ali1563_smba + 7)
DECL|macro|HST_STS_BUSY
mdefine_line|#define HST_STS_BUSY&t;0x01
DECL|macro|HST_STS_INTR
mdefine_line|#define HST_STS_INTR&t;0x02
DECL|macro|HST_STS_DEVERR
mdefine_line|#define HST_STS_DEVERR&t;0x04
DECL|macro|HST_STS_BUSERR
mdefine_line|#define HST_STS_BUSERR&t;0x08
DECL|macro|HST_STS_FAIL
mdefine_line|#define HST_STS_FAIL&t;0x10
DECL|macro|HST_STS_DONE
mdefine_line|#define HST_STS_DONE&t;0x80
DECL|macro|HST_STS_BAD
mdefine_line|#define HST_STS_BAD&t;0x1c
DECL|macro|HST_CNTL1_TIMEOUT
mdefine_line|#define HST_CNTL1_TIMEOUT&t;0x80
DECL|macro|HST_CNTL1_LAST
mdefine_line|#define HST_CNTL1_LAST&t;&t;0x40
DECL|macro|HST_CNTL2_KILL
mdefine_line|#define HST_CNTL2_KILL&t;&t;0x04
DECL|macro|HST_CNTL2_START
mdefine_line|#define HST_CNTL2_START&t;&t;0x40
DECL|macro|HST_CNTL2_QUICK
mdefine_line|#define HST_CNTL2_QUICK&t;&t;0x00
DECL|macro|HST_CNTL2_BYTE
mdefine_line|#define HST_CNTL2_BYTE&t;&t;0x01
DECL|macro|HST_CNTL2_BYTE_DATA
mdefine_line|#define HST_CNTL2_BYTE_DATA&t;0x02
DECL|macro|HST_CNTL2_WORD_DATA
mdefine_line|#define HST_CNTL2_WORD_DATA&t;0x03
DECL|macro|HST_CNTL2_BLOCK
mdefine_line|#define HST_CNTL2_BLOCK&t;&t;0x05
DECL|variable|ali1563_smba
r_static
r_int
r_int
id|ali1563_smba
suffix:semicolon
DECL|function|ali1563_transaction
r_static
r_int
id|ali1563_transaction
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|a
)paren
(brace
id|u32
id|data
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;Transaction (pre): STS=%02x, CNTL1=%02x, &quot;
l_string|&quot;CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL1
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CMD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_ADD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT1
)paren
)paren
suffix:semicolon
id|data
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|HST_STS_BAD
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;ali1563: Trying to reset busy device&bslash;n&quot;
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data
op_or
id|HST_STS_BAD
comma
id|SMB_HST_STS
)paren
suffix:semicolon
id|data
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|HST_STS_BAD
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
op_or
id|HST_CNTL2_START
comma
id|SMB_HST_CNTL2
)paren
suffix:semicolon
id|timeout
op_assign
id|ALI1563_MAX_TIMEOUT
suffix:semicolon
r_do
id|i2c_delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|data
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
)paren
op_amp
id|HST_STS_BUSY
)paren
op_logical_and
op_decrement
id|timeout
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;Transaction (post): STS=%02x, CNTL1=%02x, &quot;
l_string|&quot;CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL1
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CMD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_ADD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
op_logical_and
op_logical_neg
(paren
id|data
op_amp
id|HST_STS_BAD
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|dev_warn
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;SMBus Error: %s%s%s%s%s&bslash;n&quot;
comma
id|timeout
ques
c_cond
l_string|&quot;Timeout &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|data
op_amp
id|HST_STS_FAIL
ques
c_cond
l_string|&quot;Transaction Failed &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|data
op_amp
id|HST_STS_BUSERR
ques
c_cond
l_string|&quot;No response or Bus Collision &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|data
op_amp
id|HST_STS_DEVERR
ques
c_cond
l_string|&quot;Device Error &quot;
suffix:colon
l_string|&quot;&quot;
comma
op_logical_neg
(paren
id|data
op_amp
id|HST_STS_DONE
)paren
ques
c_cond
l_string|&quot;Transaction Never Finished &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_amp
id|HST_STS_DONE
)paren
)paren
multiline_comment|/* Issue &squot;kill&squot; to host controller */
id|outb_p
c_func
(paren
id|HST_CNTL2_KILL
comma
id|SMB_HST_CNTL2
)paren
suffix:semicolon
r_else
multiline_comment|/* Issue timeout to reset all devices on bus */
id|outb_p
c_func
(paren
id|HST_CNTL1_TIMEOUT
comma
id|SMB_HST_CNTL1
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ali1563_block_start
r_static
r_int
id|ali1563_block_start
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|a
)paren
(brace
id|u32
id|data
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;Block (pre): STS=%02x, CNTL1=%02x, &quot;
l_string|&quot;CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL1
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CMD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_ADD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT1
)paren
)paren
suffix:semicolon
id|data
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|HST_STS_BAD
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;ali1563: Trying to reset busy device&bslash;n&quot;
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data
op_or
id|HST_STS_BAD
comma
id|SMB_HST_STS
)paren
suffix:semicolon
id|data
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|HST_STS_BAD
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* Clear byte-ready bit */
id|outb_p
c_func
(paren
id|data
op_or
id|HST_STS_DONE
comma
id|SMB_HST_STS
)paren
suffix:semicolon
multiline_comment|/* Start transaction and wait for byte-ready bit to be set */
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
op_or
id|HST_CNTL2_START
comma
id|SMB_HST_CNTL2
)paren
suffix:semicolon
id|timeout
op_assign
id|ALI1563_MAX_TIMEOUT
suffix:semicolon
r_do
id|i2c_delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
(paren
id|data
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
)paren
op_amp
id|HST_STS_DONE
)paren
op_logical_and
op_decrement
id|timeout
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;Block (post): STS=%02x, CNTL1=%02x, &quot;
l_string|&quot;CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL1
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_CMD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_ADD
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HST_DAT1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
op_logical_and
op_logical_neg
(paren
id|data
op_amp
id|HST_STS_BAD
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|dev_warn
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;SMBus Error: %s%s%s%s%s&bslash;n&quot;
comma
id|timeout
ques
c_cond
l_string|&quot;Timeout &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|data
op_amp
id|HST_STS_FAIL
ques
c_cond
l_string|&quot;Transaction Failed &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|data
op_amp
id|HST_STS_BUSERR
ques
c_cond
l_string|&quot;No response or Bus Collision &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|data
op_amp
id|HST_STS_DEVERR
ques
c_cond
l_string|&quot;Device Error &quot;
suffix:colon
l_string|&quot;&quot;
comma
op_logical_neg
(paren
id|data
op_amp
id|HST_STS_DONE
)paren
ques
c_cond
l_string|&quot;Transaction Never Finished &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ali1563_block
r_static
r_int
id|ali1563_block
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|a
comma
r_union
id|i2c_smbus_data
op_star
id|data
comma
id|u8
id|rw
)paren
(brace
r_int
id|i
comma
id|len
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do we need this? */
id|outb_p
c_func
(paren
id|HST_CNTL1_LAST
comma
id|SMB_HST_CNTL1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|len
op_assign
id|data-&gt;block
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|1
)paren
id|len
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
OG
l_int|32
)paren
id|len
op_assign
l_int|32
suffix:semicolon
id|outb_p
c_func
(paren
id|len
comma
id|SMB_HST_DAT0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data-&gt;block
(braket
l_int|1
)braket
comma
id|SMB_BLK_DAT
)paren
suffix:semicolon
)brace
r_else
id|len
op_assign
l_int|32
suffix:semicolon
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
op_or
id|HST_CNTL2_BLOCK
comma
id|SMB_HST_CNTL2
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rw
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|outb_p
c_func
(paren
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
comma
id|SMB_BLK_DAT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|ali1563_block_start
c_func
(paren
id|a
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|ali1563_block_start
c_func
(paren
id|a
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|len
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|1
)paren
id|len
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
OG
l_int|32
)paren
id|len
op_assign
l_int|32
suffix:semicolon
)brace
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|inb_p
c_func
(paren
id|SMB_BLK_DAT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Do we need this? */
id|outb_p
c_func
(paren
id|HST_CNTL1_LAST
comma
id|SMB_HST_CNTL1
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|ali1563_access
r_static
id|s32
id|ali1563_access
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|a
comma
id|u16
id|addr
comma
r_int
r_int
id|flags
comma
r_char
id|rw
comma
id|u8
id|cmd
comma
r_int
id|size
comma
r_union
id|i2c_smbus_data
op_star
id|data
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|u32
id|reg
suffix:semicolon
r_for
c_loop
(paren
id|timeout
op_assign
id|ALI1563_MAX_TIMEOUT
suffix:semicolon
id|timeout
suffix:semicolon
id|timeout
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_STS
)paren
op_amp
id|HST_STS_BUSY
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
id|dev_warn
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;SMBus not idle. HST_STS = %02x&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xff
comma
id|SMB_HST_STS
)paren
suffix:semicolon
multiline_comment|/* Map the size to what the chip understands */
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|a-&gt;dev
comma
l_string|&quot;I2C_SMBUS_PROC_CALL not supported!&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|size
op_assign
id|HST_CNTL2_QUICK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
id|size
op_assign
id|HST_CNTL2_BYTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|size
op_assign
id|HST_CNTL2_BYTE_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|size
op_assign
id|HST_CNTL2_WORD_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
id|size
op_assign
id|HST_CNTL2_BLOCK
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb_p
c_func
(paren
(paren
(paren
id|addr
op_amp
l_int|0x7f
)paren
op_lshift
l_int|1
)paren
op_or
(paren
id|rw
op_amp
l_int|0x01
)paren
comma
id|SMB_HST_ADD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|SMB_HST_CNTL2
)paren
op_or
(paren
id|size
op_lshift
l_int|3
)paren
comma
id|SMB_HST_CNTL2
)paren
suffix:semicolon
multiline_comment|/* Write the command register */
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|HST_CNTL2_BYTE
suffix:colon
r_if
c_cond
(paren
id|rw
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outb_p
c_func
(paren
id|cmd
comma
id|SMB_HST_CMD
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HST_CNTL2_BYTE_DATA
suffix:colon
id|outb_p
c_func
(paren
id|cmd
comma
id|SMB_HST_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outb_p
c_func
(paren
id|data-&gt;byte
comma
id|SMB_HST_DAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HST_CNTL2_WORD_DATA
suffix:colon
id|outb_p
c_func
(paren
id|cmd
comma
id|SMB_HST_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|outb_p
c_func
(paren
id|data-&gt;word
op_amp
l_int|0xff
comma
id|SMB_HST_DAT0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|data-&gt;word
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
comma
id|SMB_HST_DAT1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HST_CNTL2_BLOCK
suffix:colon
id|outb_p
c_func
(paren
id|cmd
comma
id|SMB_HST_CMD
)paren
suffix:semicolon
id|error
op_assign
id|ali1563_block
c_func
(paren
id|a
comma
id|data
comma
id|rw
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|ali1563_transaction
c_func
(paren
id|a
)paren
)paren
)paren
r_goto
id|Done
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rw
op_eq
id|I2C_SMBUS_WRITE
)paren
op_logical_or
(paren
id|size
op_eq
id|HST_CNTL2_QUICK
)paren
)paren
r_goto
id|Done
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|HST_CNTL2_BYTE
suffix:colon
multiline_comment|/* Result put in SMBHSTDAT0 */
id|data-&gt;byte
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HST_CNTL2_BYTE_DATA
suffix:colon
id|data-&gt;byte
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HST_CNTL2_WORD_DATA
suffix:colon
id|data-&gt;word
op_assign
id|inb_p
c_func
(paren
id|SMB_HST_DAT0
)paren
op_plus
(paren
id|inb_p
c_func
(paren
id|SMB_HST_DAT1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|ali1563_func
r_static
id|u32
id|ali1563_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|a
)paren
(brace
r_return
id|I2C_FUNC_SMBUS_QUICK
op_or
id|I2C_FUNC_SMBUS_BYTE
op_or
id|I2C_FUNC_SMBUS_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
op_or
id|I2C_FUNC_SMBUS_BLOCK_DATA
suffix:semicolon
)brace
DECL|function|ali1563_enable
r_static
r_void
id|ali1563_enable
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|ctrl
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|ALI1563_SMBBA
comma
op_amp
id|ctrl
)paren
suffix:semicolon
id|ctrl
op_or_assign
l_int|0x7
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|ALI1563_SMBBA
comma
id|ctrl
)paren
suffix:semicolon
)brace
DECL|function|ali1563_setup
r_static
r_int
id|__init
id|ali1563_setup
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|ctrl
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|ALI1563_SMBBA
comma
op_amp
id|ctrl
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ali1563: SMBus control = %04x&bslash;n&quot;
comma
id|ctrl
)paren
suffix:semicolon
multiline_comment|/* Check if device is even enabled first */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctrl
op_amp
id|ALI1563_SMB_IOEN
)paren
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;I/O space not enabled, trying manually&bslash;n&quot;
)paren
suffix:semicolon
id|ali1563_enable
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctrl
op_amp
id|ALI1563_SMB_IOEN
)paren
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;I/O space still not enabled, giving up&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|Err
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctrl
op_amp
id|ALI1563_SMB_HOSTEN
)paren
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Host Controller not enabled&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|Err
suffix:semicolon
)brace
multiline_comment|/* SMB I/O Base in high 12 bits and must be aligned with the&n;&t; * size of the I/O space. */
id|ali1563_smba
op_assign
id|ctrl
op_amp
op_complement
(paren
id|ALI1563_SMB_IOSIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ali1563_smba
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;ali1563_smba Uninitialized&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|Err
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ali1563_smba
comma
id|ALI1563_SMB_IOSIZE
comma
l_string|&quot;i2c-ali1563&quot;
)paren
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Could not allocate I/O space&quot;
)paren
suffix:semicolon
r_goto
id|Err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|Err
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|ali1563_shutdown
r_static
r_void
id|ali1563_shutdown
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|release_region
c_func
(paren
id|ali1563_smba
comma
id|ALI1563_SMB_IOSIZE
)paren
suffix:semicolon
)brace
DECL|variable|ali1563_algorithm
r_static
r_struct
id|i2c_algorithm
id|ali1563_algorithm
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Non-i2c SMBus adapter&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SMBUS
comma
dot
id|smbus_xfer
op_assign
id|ali1563_access
comma
dot
id|functionality
op_assign
id|ali1563_func
comma
)brace
suffix:semicolon
DECL|variable|ali1563_adapter
r_static
r_struct
id|i2c_adapter
id|ali1563_adapter
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
r_class
op_assign
id|I2C_CLASS_SMBUS
comma
dot
id|algo
op_assign
op_amp
id|ali1563_algorithm
comma
)brace
suffix:semicolon
DECL|function|ali1563_probe
r_static
r_int
id|__init
id|ali1563_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id_table
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|ali1563_setup
c_func
(paren
id|dev
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
id|ali1563_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|sprintf
c_func
(paren
id|ali1563_adapter.name
comma
l_string|&quot;SMBus ALi 1563 Adapter @ %04x&quot;
comma
id|ali1563_smba
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|ali1563_adapter
)paren
)paren
)paren
id|ali1563_shutdown
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Returning %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|ali1563_remove
r_static
r_void
id|__exit
id|ali1563_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|ali1563_adapter
)paren
suffix:semicolon
id|ali1563_shutdown
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|ali1563_id_table
r_static
r_struct
id|pci_device_id
id|__devinitdata
id|ali1563_id_table
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_AL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AL_M1563
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|ali1563_pci_driver
r_static
r_struct
id|pci_driver
id|ali1563_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i2c-ali1563&quot;
comma
dot
id|id_table
op_assign
id|ali1563_id_table
comma
dot
id|probe
op_assign
id|ali1563_probe
comma
dot
id|remove
op_assign
id|ali1563_remove
comma
)brace
suffix:semicolon
DECL|function|ali1563_init
r_static
r_int
id|__init
id|ali1563_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|ali1563_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|ali1563_init
id|module_init
c_func
(paren
id|ali1563_init
)paren
suffix:semicolon
DECL|function|ali1563_exit
r_static
r_void
id|__exit
id|ali1563_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|ali1563_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|ali1563_exit
id|module_exit
c_func
(paren
id|ali1563_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
