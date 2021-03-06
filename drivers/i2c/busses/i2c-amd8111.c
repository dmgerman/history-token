multiline_comment|/*&n; * SMBus 2.0 driver for AMD-8111 IO-Hub.&n; *&n; * Copyright (c) 2002 Vojtech Pavlik&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation version 2.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AMD8111 SMBus 2.0 driver&quot;
)paren
suffix:semicolon
DECL|struct|amd_smbus
r_struct
id|amd_smbus
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|base
r_int
id|base
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * AMD PCI control registers definitions.&n; */
DECL|macro|AMD_PCI_MISC
mdefine_line|#define AMD_PCI_MISC&t;0x48
DECL|macro|AMD_PCI_MISC_SCI
mdefine_line|#define AMD_PCI_MISC_SCI&t;0x04&t;/* deliver SCI */
DECL|macro|AMD_PCI_MISC_INT
mdefine_line|#define AMD_PCI_MISC_INT&t;0x02&t;/* deliver PCI IRQ */
DECL|macro|AMD_PCI_MISC_SPEEDUP
mdefine_line|#define AMD_PCI_MISC_SPEEDUP&t;0x01&t;/* 16x clock speedup */
multiline_comment|/*&n; * ACPI 2.0 chapter 13 PCI interface definitions.&n; */
DECL|macro|AMD_EC_DATA
mdefine_line|#define AMD_EC_DATA&t;0x00&t;/* data register */
DECL|macro|AMD_EC_SC
mdefine_line|#define AMD_EC_SC&t;0x04&t;/* status of controller */
DECL|macro|AMD_EC_CMD
mdefine_line|#define AMD_EC_CMD&t;0x04&t;/* command register */
DECL|macro|AMD_EC_ICR
mdefine_line|#define AMD_EC_ICR&t;0x08&t;/* interrupt control register */
DECL|macro|AMD_EC_SC_SMI
mdefine_line|#define AMD_EC_SC_SMI&t;0x04&t;/* smi event pending */
DECL|macro|AMD_EC_SC_SCI
mdefine_line|#define AMD_EC_SC_SCI&t;0x02&t;/* sci event pending */
DECL|macro|AMD_EC_SC_BURST
mdefine_line|#define AMD_EC_SC_BURST&t;0x01&t;/* burst mode enabled */
DECL|macro|AMD_EC_SC_CMD
mdefine_line|#define AMD_EC_SC_CMD&t;0x08&t;/* byte in data reg is command */
DECL|macro|AMD_EC_SC_IBF
mdefine_line|#define AMD_EC_SC_IBF&t;0x02&t;/* data ready for embedded controller */
DECL|macro|AMD_EC_SC_OBF
mdefine_line|#define AMD_EC_SC_OBF&t;0x01&t;/* data ready for host */
DECL|macro|AMD_EC_CMD_RD
mdefine_line|#define AMD_EC_CMD_RD&t;0x80&t;/* read EC */
DECL|macro|AMD_EC_CMD_WR
mdefine_line|#define AMD_EC_CMD_WR&t;0x81&t;/* write EC */
DECL|macro|AMD_EC_CMD_BE
mdefine_line|#define AMD_EC_CMD_BE&t;0x82&t;/* enable burst mode */
DECL|macro|AMD_EC_CMD_BD
mdefine_line|#define AMD_EC_CMD_BD&t;0x83&t;/* disable burst mode */
DECL|macro|AMD_EC_CMD_QR
mdefine_line|#define AMD_EC_CMD_QR&t;0x84&t;/* query EC */
multiline_comment|/*&n; * ACPI 2.0 chapter 13 access of registers of the EC&n; */
DECL|function|amd_ec_wait_write
r_static
r_int
r_int
id|amd_ec_wait_write
c_func
(paren
r_struct
id|amd_smbus
op_star
id|smbus
)paren
(brace
r_int
id|timeout
op_assign
l_int|500
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_decrement
op_logical_and
(paren
id|inb
c_func
(paren
id|smbus-&gt;base
op_plus
id|AMD_EC_SC
)paren
op_amp
id|AMD_EC_SC_IBF
)paren
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|smbus-&gt;dev-&gt;dev
comma
l_string|&quot;Timeout while waiting for IBF to clear&bslash;n&quot;
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
DECL|function|amd_ec_wait_read
r_static
r_int
r_int
id|amd_ec_wait_read
c_func
(paren
r_struct
id|amd_smbus
op_star
id|smbus
)paren
(brace
r_int
id|timeout
op_assign
l_int|500
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_decrement
op_logical_and
(paren
op_complement
id|inb
c_func
(paren
id|smbus-&gt;base
op_plus
id|AMD_EC_SC
)paren
op_amp
id|AMD_EC_SC_OBF
)paren
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|smbus-&gt;dev-&gt;dev
comma
l_string|&quot;Timeout while waiting for OBF to set&bslash;n&quot;
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
DECL|function|amd_ec_read
r_static
r_int
r_int
id|amd_ec_read
c_func
(paren
r_struct
id|amd_smbus
op_star
id|smbus
comma
r_int
r_char
id|address
comma
r_int
r_char
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|amd_ec_wait_write
c_func
(paren
id|smbus
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|AMD_EC_CMD_RD
comma
id|smbus-&gt;base
op_plus
id|AMD_EC_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amd_ec_wait_write
c_func
(paren
id|smbus
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|address
comma
id|smbus-&gt;base
op_plus
id|AMD_EC_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amd_ec_wait_read
c_func
(paren
id|smbus
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|data
op_assign
id|inb
c_func
(paren
id|smbus-&gt;base
op_plus
id|AMD_EC_DATA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_ec_write
r_static
r_int
r_int
id|amd_ec_write
c_func
(paren
r_struct
id|amd_smbus
op_star
id|smbus
comma
r_int
r_char
id|address
comma
r_int
r_char
id|data
)paren
(brace
r_if
c_cond
(paren
id|amd_ec_wait_write
c_func
(paren
id|smbus
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|AMD_EC_CMD_WR
comma
id|smbus-&gt;base
op_plus
id|AMD_EC_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amd_ec_wait_write
c_func
(paren
id|smbus
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|address
comma
id|smbus-&gt;base
op_plus
id|AMD_EC_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amd_ec_wait_write
c_func
(paren
id|smbus
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|smbus-&gt;base
op_plus
id|AMD_EC_DATA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * ACPI 2.0 chapter 13 SMBus 2.0 EC register model&n; */
DECL|macro|AMD_SMB_PRTCL
mdefine_line|#define AMD_SMB_PRTCL&t;0x00&t;/* protocol, PEC */
DECL|macro|AMD_SMB_STS
mdefine_line|#define AMD_SMB_STS&t;0x01&t;/* status */
DECL|macro|AMD_SMB_ADDR
mdefine_line|#define AMD_SMB_ADDR&t;0x02&t;/* address */
DECL|macro|AMD_SMB_CMD
mdefine_line|#define AMD_SMB_CMD&t;0x03&t;/* command */
DECL|macro|AMD_SMB_DATA
mdefine_line|#define AMD_SMB_DATA&t;0x04&t;/* 32 data registers */
DECL|macro|AMD_SMB_BCNT
mdefine_line|#define AMD_SMB_BCNT&t;0x24&t;/* number of data bytes */
DECL|macro|AMD_SMB_ALRM_A
mdefine_line|#define AMD_SMB_ALRM_A&t;0x25&t;/* alarm address */
DECL|macro|AMD_SMB_ALRM_D
mdefine_line|#define AMD_SMB_ALRM_D&t;0x26&t;/* 2 bytes alarm data */
DECL|macro|AMD_SMB_STS_DONE
mdefine_line|#define AMD_SMB_STS_DONE&t;0x80
DECL|macro|AMD_SMB_STS_ALRM
mdefine_line|#define AMD_SMB_STS_ALRM&t;0x40
DECL|macro|AMD_SMB_STS_RES
mdefine_line|#define AMD_SMB_STS_RES&t;&t;0x20
DECL|macro|AMD_SMB_STS_STATUS
mdefine_line|#define AMD_SMB_STS_STATUS&t;0x1f
DECL|macro|AMD_SMB_STATUS_OK
mdefine_line|#define AMD_SMB_STATUS_OK&t;0x00
DECL|macro|AMD_SMB_STATUS_FAIL
mdefine_line|#define AMD_SMB_STATUS_FAIL&t;0x07
DECL|macro|AMD_SMB_STATUS_DNAK
mdefine_line|#define AMD_SMB_STATUS_DNAK&t;0x10
DECL|macro|AMD_SMB_STATUS_DERR
mdefine_line|#define AMD_SMB_STATUS_DERR&t;0x11
DECL|macro|AMD_SMB_STATUS_CMD_DENY
mdefine_line|#define AMD_SMB_STATUS_CMD_DENY&t;0x12
DECL|macro|AMD_SMB_STATUS_UNKNOWN
mdefine_line|#define AMD_SMB_STATUS_UNKNOWN&t;0x13
DECL|macro|AMD_SMB_STATUS_ACC_DENY
mdefine_line|#define AMD_SMB_STATUS_ACC_DENY&t;0x17
DECL|macro|AMD_SMB_STATUS_TIMEOUT
mdefine_line|#define AMD_SMB_STATUS_TIMEOUT&t;0x18
DECL|macro|AMD_SMB_STATUS_NOTSUP
mdefine_line|#define AMD_SMB_STATUS_NOTSUP&t;0x19
DECL|macro|AMD_SMB_STATUS_BUSY
mdefine_line|#define AMD_SMB_STATUS_BUSY&t;0x1A
DECL|macro|AMD_SMB_STATUS_PEC
mdefine_line|#define AMD_SMB_STATUS_PEC&t;0x1F
DECL|macro|AMD_SMB_PRTCL_WRITE
mdefine_line|#define AMD_SMB_PRTCL_WRITE&t;&t;0x00
DECL|macro|AMD_SMB_PRTCL_READ
mdefine_line|#define AMD_SMB_PRTCL_READ&t;&t;0x01
DECL|macro|AMD_SMB_PRTCL_QUICK
mdefine_line|#define AMD_SMB_PRTCL_QUICK&t;&t;0x02
DECL|macro|AMD_SMB_PRTCL_BYTE
mdefine_line|#define AMD_SMB_PRTCL_BYTE&t;&t;0x04
DECL|macro|AMD_SMB_PRTCL_BYTE_DATA
mdefine_line|#define AMD_SMB_PRTCL_BYTE_DATA&t;&t;0x06
DECL|macro|AMD_SMB_PRTCL_WORD_DATA
mdefine_line|#define AMD_SMB_PRTCL_WORD_DATA&t;&t;0x08
DECL|macro|AMD_SMB_PRTCL_BLOCK_DATA
mdefine_line|#define AMD_SMB_PRTCL_BLOCK_DATA&t;0x0a
DECL|macro|AMD_SMB_PRTCL_PROC_CALL
mdefine_line|#define AMD_SMB_PRTCL_PROC_CALL&t;&t;0x0c
DECL|macro|AMD_SMB_PRTCL_BLOCK_PROC_CALL
mdefine_line|#define AMD_SMB_PRTCL_BLOCK_PROC_CALL&t;0x0d
DECL|macro|AMD_SMB_PRTCL_I2C_BLOCK_DATA
mdefine_line|#define AMD_SMB_PRTCL_I2C_BLOCK_DATA&t;0x4a
DECL|macro|AMD_SMB_PRTCL_PEC
mdefine_line|#define AMD_SMB_PRTCL_PEC&t;&t;0x80
DECL|function|amd8111_access
r_static
id|s32
id|amd8111_access
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
id|u16
id|addr
comma
r_int
r_int
id|flags
comma
r_char
id|read_write
comma
id|u8
id|command
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
r_struct
id|amd_smbus
op_star
id|smbus
op_assign
id|adap-&gt;algo_data
suffix:semicolon
r_int
r_char
id|protocol
comma
id|len
comma
id|pec
comma
id|temp
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|protocol
op_assign
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
ques
c_cond
id|AMD_SMB_PRTCL_READ
suffix:colon
id|AMD_SMB_PRTCL_WRITE
suffix:semicolon
id|pec
op_assign
(paren
id|flags
op_amp
id|I2C_CLIENT_PEC
)paren
ques
c_cond
id|AMD_SMB_PRTCL_PEC
suffix:colon
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|protocol
op_or_assign
id|AMD_SMB_PRTCL_QUICK
suffix:semicolon
id|read_write
op_assign
id|I2C_SMBUS_WRITE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_CMD
comma
id|command
)paren
suffix:semicolon
id|protocol
op_or_assign
id|AMD_SMB_PRTCL_BYTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_CMD
comma
id|command
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
comma
id|data-&gt;byte
)paren
suffix:semicolon
id|protocol
op_or_assign
id|AMD_SMB_PRTCL_BYTE_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_CMD
comma
id|command
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
comma
id|data-&gt;word
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
op_plus
l_int|1
comma
id|data-&gt;word
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|protocol
op_or_assign
id|AMD_SMB_PRTCL_WORD_DATA
op_or
id|pec
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_CMD
comma
id|command
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|len
op_assign
id|min_t
c_func
(paren
id|u8
comma
id|data-&gt;block
(braket
l_int|0
)braket
comma
l_int|32
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_BCNT
comma
id|len
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
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
op_plus
id|i
comma
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|protocol
op_or_assign
id|AMD_SMB_PRTCL_BLOCK_DATA
op_or
id|pec
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_I2C_BLOCK_DATA
suffix:colon
id|len
op_assign
id|min_t
c_func
(paren
id|u8
comma
id|data-&gt;block
(braket
l_int|0
)braket
comma
l_int|32
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_CMD
comma
id|command
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_BCNT
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
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
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
op_plus
id|i
comma
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|protocol
op_or_assign
id|AMD_SMB_PRTCL_I2C_BLOCK_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_CMD
comma
id|command
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
comma
id|data-&gt;word
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
op_plus
l_int|1
comma
id|data-&gt;word
op_rshift
l_int|8
)paren
suffix:semicolon
id|protocol
op_assign
id|AMD_SMB_PRTCL_PROC_CALL
op_or
id|pec
suffix:semicolon
id|read_write
op_assign
id|I2C_SMBUS_READ
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_PROC_CALL
suffix:colon
id|protocol
op_or_assign
id|pec
suffix:semicolon
id|len
op_assign
id|min_t
c_func
(paren
id|u8
comma
id|data-&gt;block
(braket
l_int|0
)braket
comma
l_int|31
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_CMD
comma
id|command
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_BCNT
comma
id|len
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
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
op_plus
id|i
comma
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|protocol
op_assign
id|AMD_SMB_PRTCL_BLOCK_PROC_CALL
op_or
id|pec
suffix:semicolon
id|read_write
op_assign
id|I2C_SMBUS_READ
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA_PEC
suffix:colon
r_case
id|I2C_SMBUS_BLOCK_DATA_PEC
suffix:colon
r_case
id|I2C_SMBUS_PROC_CALL_PEC
suffix:colon
r_case
id|I2C_SMBUS_BLOCK_PROC_CALL_PEC
suffix:colon
id|dev_warn
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Unexpected software PEC transaction %d&bslash;n.&quot;
comma
id|size
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
r_default
suffix:colon
id|dev_warn
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Unsupported transaction %d&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_ADDR
comma
id|addr
op_lshift
l_int|1
)paren
suffix:semicolon
id|amd_ec_write
c_func
(paren
id|smbus
comma
id|AMD_SMB_PRTCL
comma
id|protocol
)paren
suffix:semicolon
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_STS
comma
id|temp
op_plus
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|temp
(braket
l_int|0
)braket
op_amp
id|AMD_SMB_STS_DONE
)paren
(brace
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_STS
comma
id|temp
op_plus
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|temp
(braket
l_int|0
)braket
op_amp
id|AMD_SMB_STS_DONE
)paren
(brace
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_STS
comma
id|temp
op_plus
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_complement
id|temp
(braket
l_int|0
)braket
op_amp
id|AMD_SMB_STS_DONE
)paren
op_logical_or
(paren
id|temp
(braket
l_int|0
)braket
op_amp
id|AMD_SMB_STS_STATUS
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_BYTE
suffix:colon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
comma
op_amp
id|data-&gt;byte
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
comma
id|temp
op_plus
l_int|0
)paren
suffix:semicolon
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
op_plus
l_int|1
comma
id|temp
op_plus
l_int|1
)paren
suffix:semicolon
id|data-&gt;word
op_assign
(paren
id|temp
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|temp
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
r_case
id|I2C_SMBUS_BLOCK_PROC_CALL
suffix:colon
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_BCNT
comma
op_amp
id|len
)paren
suffix:semicolon
id|len
op_assign
id|min_t
c_func
(paren
id|u8
comma
id|len
comma
l_int|32
)paren
suffix:semicolon
r_case
id|I2C_SMBUS_I2C_BLOCK_DATA
suffix:colon
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
id|amd_ec_read
c_func
(paren
id|smbus
comma
id|AMD_SMB_DATA
op_plus
id|i
comma
id|data-&gt;block
op_plus
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|len
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd8111_func
r_static
id|u32
id|amd8111_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
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
op_or
id|I2C_FUNC_SMBUS_PROC_CALL
op_or
id|I2C_FUNC_SMBUS_BLOCK_PROC_CALL
op_or
id|I2C_FUNC_SMBUS_I2C_BLOCK
op_or
id|I2C_FUNC_SMBUS_HWPEC_CALC
suffix:semicolon
)brace
DECL|variable|smbus_algorithm
r_static
r_struct
id|i2c_algorithm
id|smbus_algorithm
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Non-I2C SMBus 2.0 adapter&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SMBUS
comma
dot
id|smbus_xfer
op_assign
id|amd8111_access
comma
dot
id|functionality
op_assign
id|amd8111_func
comma
)brace
suffix:semicolon
DECL|variable|amd8111_ids
r_static
r_struct
id|pci_device_id
id|amd8111_ids
(braket
)braket
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_8111_SMBUS2
)paren
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|amd8111_ids
)paren
suffix:semicolon
DECL|function|amd8111_probe
r_static
r_int
id|__devinit
id|amd8111_probe
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
id|id
)paren
(brace
r_struct
id|amd_smbus
op_star
id|smbus
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|pci_resource_flags
c_func
(paren
id|dev
comma
l_int|0
)paren
op_amp
id|IORESOURCE_IO
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|smbus
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|amd_smbus
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smbus
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|smbus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|amd_smbus
)paren
)paren
suffix:semicolon
id|smbus-&gt;dev
op_assign
id|dev
suffix:semicolon
id|smbus-&gt;base
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|smbus-&gt;size
op_assign
id|pci_resource_len
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|smbus-&gt;base
comma
id|smbus-&gt;size
comma
l_string|&quot;amd8111 SMBus 2.0&quot;
)paren
)paren
r_goto
id|out_kfree
suffix:semicolon
id|smbus-&gt;adapter.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|snprintf
c_func
(paren
id|smbus-&gt;adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus2 AMD8111 adapter at %04x&quot;
comma
id|smbus-&gt;base
)paren
suffix:semicolon
id|smbus-&gt;adapter
dot
r_class
op_assign
id|I2C_CLASS_HWMON
suffix:semicolon
id|smbus-&gt;adapter.algo
op_assign
op_amp
id|smbus_algorithm
suffix:semicolon
id|smbus-&gt;adapter.algo_data
op_assign
id|smbus
suffix:semicolon
multiline_comment|/* set up the driverfs linkage to our parent device */
id|smbus-&gt;adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|error
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|smbus-&gt;adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_release_region
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|smbus-&gt;dev
comma
id|AMD_PCI_MISC
comma
l_int|0
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
id|smbus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_release_region
suffix:colon
id|release_region
c_func
(paren
id|smbus-&gt;base
comma
id|smbus-&gt;size
)paren
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
id|smbus
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|amd8111_remove
r_static
r_void
id|__devexit
id|amd8111_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|amd_smbus
op_star
id|smbus
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|i2c_del_adapter
c_func
(paren
op_amp
id|smbus-&gt;adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|smbus-&gt;base
comma
id|smbus-&gt;size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|smbus
)paren
suffix:semicolon
)brace
DECL|variable|amd8111_driver
r_static
r_struct
id|pci_driver
id|amd8111_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;amd8111_smbus2&quot;
comma
dot
id|id_table
op_assign
id|amd8111_ids
comma
dot
id|probe
op_assign
id|amd8111_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|amd8111_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_amd8111_init
r_static
r_int
id|__init
id|i2c_amd8111_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|amd8111_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_amd8111_exit
r_static
r_void
id|__exit
id|i2c_amd8111_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|amd8111_driver
)paren
suffix:semicolon
)brace
DECL|variable|i2c_amd8111_init
id|module_init
c_func
(paren
id|i2c_amd8111_init
)paren
suffix:semicolon
DECL|variable|i2c_amd8111_exit
id|module_exit
c_func
(paren
id|i2c_amd8111_exit
)paren
suffix:semicolon
eof
