multiline_comment|/*&n;    i2c-ali1535.c - Part of lm_sensors, Linux kernel modules for hardware&n;                    monitoring&n;    Copyright (c) 2000  Frodo Looijaard &lt;frodol@dds.nl&gt;, &n;                        Philip Edelbrock &lt;phil@netroedge.com&gt;, &n;                        Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;,&n;                        Dan Eaton &lt;dan.eaton@rocketlogix.com&gt; and &n;                        Stephen Rousset&lt;stephen.rousset@rocketlogix.com&gt; &n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    This is the driver for the SMB Host controller on&n;    Acer Labs Inc. (ALI) M1535 South Bridge.&n;&n;    The M1535 is a South bridge for portable systems.&n;    It is very similar to the M15x3 South bridges also produced&n;    by Acer Labs Inc.  Some of the registers within the part&n;    have moved and some have been redefined slightly. Additionally,&n;    the sequencing of the SMBus transactions has been modified&n;    to be more consistent with the sequencing recommended by&n;    the manufacturer and observed through testing.  These&n;    changes are reflected in this driver and can be identified&n;    by comparing this driver to the i2c-ali15x3 driver.&n;    For an overview of these chips see http://www.acerlabs.com&n;&n;    The SMB controller is part of the 7101 device, which is an&n;    ACPI-compliant Power Management Unit (PMU).&n;&n;    The whole 7101 device has to be enabled for the SMB to work.&n;    You can&squot;t just enable the SMB alone.&n;    The SMB and the ACPI have separate I/O spaces.&n;    We make sure that the SMB is enabled. We leave the ACPI alone.&n;&n;    This driver controls the SMB Host only.&n;&n;    This driver does not use interrupts.&n;*/
multiline_comment|/* Note: we assume there can only be one ALI1535, with one SMBus interface */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/* ALI1535 SMBus address offsets */
DECL|macro|SMBHSTSTS
mdefine_line|#define SMBHSTSTS&t;(0 + ali1535_smba)
DECL|macro|SMBHSTTYP
mdefine_line|#define SMBHSTTYP&t;(1 + ali1535_smba)
DECL|macro|SMBHSTPORT
mdefine_line|#define SMBHSTPORT&t;(2 + ali1535_smba)
DECL|macro|SMBHSTCMD
mdefine_line|#define SMBHSTCMD&t;(7 + ali1535_smba)
DECL|macro|SMBHSTADD
mdefine_line|#define SMBHSTADD&t;(3 + ali1535_smba)
DECL|macro|SMBHSTDAT0
mdefine_line|#define SMBHSTDAT0&t;(4 + ali1535_smba)
DECL|macro|SMBHSTDAT1
mdefine_line|#define SMBHSTDAT1&t;(5 + ali1535_smba)
DECL|macro|SMBBLKDAT
mdefine_line|#define SMBBLKDAT&t;(6 + ali1535_smba)
multiline_comment|/* PCI Address Constants */
DECL|macro|SMBCOM
mdefine_line|#define SMBCOM&t;&t;0x004
DECL|macro|SMBREV
mdefine_line|#define SMBREV&t;&t;0x008
DECL|macro|SMBCFG
mdefine_line|#define SMBCFG&t;&t;0x0D1
DECL|macro|SMBBA
mdefine_line|#define SMBBA&t;&t;0x0E2
DECL|macro|SMBHSTCFG
mdefine_line|#define SMBHSTCFG&t;0x0F0
DECL|macro|SMBCLK
mdefine_line|#define SMBCLK&t;&t;0x0F2
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT&t;&t;500&t;/* times 1/100 sec */
DECL|macro|ALI1535_SMB_IOSIZE
mdefine_line|#define ALI1535_SMB_IOSIZE&t;32
DECL|macro|ALI1535_SMB_DEFAULTBASE
mdefine_line|#define ALI1535_SMB_DEFAULTBASE&t;0x8040
multiline_comment|/* ALI1535 address lock bits */
DECL|macro|ALI1535_LOCK
mdefine_line|#define ALI1535_LOCK&t;&t;0x06&t;/* dwe */
multiline_comment|/* ALI1535 command constants */
DECL|macro|ALI1535_QUICK
mdefine_line|#define ALI1535_QUICK&t;&t;0x00
DECL|macro|ALI1535_BYTE
mdefine_line|#define ALI1535_BYTE&t;&t;0x10
DECL|macro|ALI1535_BYTE_DATA
mdefine_line|#define ALI1535_BYTE_DATA&t;0x20
DECL|macro|ALI1535_WORD_DATA
mdefine_line|#define ALI1535_WORD_DATA&t;0x30
DECL|macro|ALI1535_BLOCK_DATA
mdefine_line|#define ALI1535_BLOCK_DATA&t;0x40
DECL|macro|ALI1535_I2C_READ
mdefine_line|#define ALI1535_I2C_READ&t;0x60
DECL|macro|ALI1535_DEV10B_EN
mdefine_line|#define&t;ALI1535_DEV10B_EN&t;0x80&t;/* Enable 10-bit addressing in&t;*/
multiline_comment|/*  I2C read&t;&t;&t;*/
DECL|macro|ALI1535_T_OUT
mdefine_line|#define&t;ALI1535_T_OUT&t;&t;0x08&t;/* Time-out Command (write)&t;*/
DECL|macro|ALI1535_A_HIGH_BIT9
mdefine_line|#define&t;ALI1535_A_HIGH_BIT9&t;0x08&t;/* Bit 9 of 10-bit address in&t;*/
multiline_comment|/* Alert-Response-Address&t;*/
multiline_comment|/* (read)&t;&t;&t;*/
DECL|macro|ALI1535_KILL
mdefine_line|#define&t;ALI1535_KILL&t;&t;0x04&t;/* Kill Command (write)&t;&t;*/
DECL|macro|ALI1535_A_HIGH_BIT8
mdefine_line|#define&t;ALI1535_A_HIGH_BIT8&t;0x04&t;/* Bit 8 of 10-bit address in&t;*/
multiline_comment|/*  Alert-Response-Address&t;*/
multiline_comment|/*  (read)&t;&t;&t;*/
DECL|macro|ALI1535_D_HI_MASK
mdefine_line|#define&t;ALI1535_D_HI_MASK&t;0x03&t;/* Mask for isolating bits 9-8&t;*/
multiline_comment|/*  of 10-bit address in I2C&t;*/
multiline_comment|/*  Read Command&t;&t;*/
multiline_comment|/* ALI1535 status register bits */
DECL|macro|ALI1535_STS_IDLE
mdefine_line|#define ALI1535_STS_IDLE&t;0x04
DECL|macro|ALI1535_STS_BUSY
mdefine_line|#define ALI1535_STS_BUSY&t;0x08&t;/* host busy */
DECL|macro|ALI1535_STS_DONE
mdefine_line|#define ALI1535_STS_DONE&t;0x10&t;/* transaction complete */
DECL|macro|ALI1535_STS_DEV
mdefine_line|#define ALI1535_STS_DEV&t;&t;0x20&t;/* device error */
DECL|macro|ALI1535_STS_BUSERR
mdefine_line|#define ALI1535_STS_BUSERR&t;0x40&t;/* bus error    */
DECL|macro|ALI1535_STS_FAIL
mdefine_line|#define ALI1535_STS_FAIL&t;0x80&t;/* failed bus transaction */
DECL|macro|ALI1535_STS_ERR
mdefine_line|#define ALI1535_STS_ERR&t;&t;0xE0&t;/* all the bad error bits */
DECL|macro|ALI1535_BLOCK_CLR
mdefine_line|#define ALI1535_BLOCK_CLR&t;0x04&t;/* reset block data index */
multiline_comment|/* ALI1535 device address register bits */
DECL|macro|ALI1535_RD_ADDR
mdefine_line|#define&t;ALI1535_RD_ADDR&t;&t;0x01&t;/* Read/Write Bit in Device&t;*/
multiline_comment|/*  Address field&t;&t;*/
multiline_comment|/*  -&gt; Write = 0&t;&t;*/
multiline_comment|/*  -&gt; Read  = 1&t;&t;*/
DECL|macro|ALI1535_SMBIO_EN
mdefine_line|#define&t;ALI1535_SMBIO_EN&t;0x04&t;/* SMB I/O Space enable&t;&t;*/
DECL|variable|ali1535_smba
r_static
r_int
r_int
id|ali1535_smba
suffix:semicolon
DECL|variable|i2c_ali1535_sem
id|DECLARE_MUTEX
c_func
(paren
id|i2c_ali1535_sem
)paren
suffix:semicolon
multiline_comment|/* Detect whether a ALI1535 can be found, and initialize it, where necessary.&n;   Note the differences between kernels with the old PCI BIOS interface and&n;   newer kernels with the real PCI interface. In compat.h some things are&n;   defined to make the transition easier. */
DECL|function|ali1535_setup
r_static
r_int
id|ali1535_setup
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_int
r_char
id|temp
suffix:semicolon
multiline_comment|/* Check the following things:&n;&t;&t;- SMB I/O address is initialized&n;&t;&t;- Device is enabled&n;&t;&t;- We can use the addresses&n;&t;*/
multiline_comment|/* Determine the address of the SMBus area */
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|SMBBA
comma
op_amp
id|ali1535_smba
)paren
suffix:semicolon
id|ali1535_smba
op_and_assign
(paren
l_int|0xffff
op_amp
op_complement
(paren
id|ALI1535_SMB_IOSIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ali1535_smba
op_eq
l_int|0
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;ALI1535_smb region uninitialized - upgrade BIOS?&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ali1535_smba
comma
id|ALI1535_SMB_IOSIZE
comma
l_string|&quot;ali1535-smb&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;ALI1535_smb region 0x%x already in use!&bslash;n&quot;
comma
id|ali1535_smba
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* check if whole device is enabled */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|SMBCFG
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_amp
id|ALI1535_SMBIO_EN
)paren
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SMB device not enabled - upgrade BIOS?&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|exit_free
suffix:semicolon
)brace
multiline_comment|/* Is SMB Host controller enabled? */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|SMBHSTCFG
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SMBus controller not enabled - upgrade BIOS?&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|exit_free
suffix:semicolon
)brace
multiline_comment|/* set SMB clock to 74KHz as recommended in data sheet */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|SMBCLK
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/*&n;&t;  The interrupt routing for SMB is set up in register 0x77 in the&n;&t;  1533 ISA Bridge device, NOT in the 7101 device.&n;&t;  Don&squot;t bother with finding the 1533 device and reading the register.&n;&t;if ((....... &amp; 0x0F) == 1)&n;&t;&t;dev_dbg(&amp;dev-&gt;dev, &quot;ALI1535 using Interrupt 9 for SMBus.&bslash;n&quot;);&n;&t;*/
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|SMBREV
comma
op_amp
id|temp
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SMBREV = 0x%X&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;ALI1535_smba = 0x%X&bslash;n&quot;
comma
id|ali1535_smba
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
id|exit_free
suffix:colon
id|release_region
c_func
(paren
id|ali1535_smba
comma
id|ALI1535_SMB_IOSIZE
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ali1535_transaction
r_static
r_int
id|ali1535_transaction
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_int
id|temp
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|timeout
op_assign
l_int|0
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Transaction (pre): STS=%02x, TYP=%02x, &quot;
l_string|&quot;CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTTYP
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTCMD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTADD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT1
)paren
)paren
suffix:semicolon
multiline_comment|/* get status */
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
multiline_comment|/* Make sure the SMBus host is ready to start transmitting */
multiline_comment|/* Check the busy bit first */
r_if
c_cond
(paren
id|temp
op_amp
id|ALI1535_STS_BUSY
)paren
(brace
multiline_comment|/* If the host controller is still busy, it may have timed out&n;&t;&t; * in the previous transaction, resulting in a &quot;SMBus Timeout&quot;&n;&t;&t; * printk.  I&squot;ve tried the following to reset a stuck busy bit.&n;&t;&t; *   1. Reset the controller with an KILL command. (this&n;&t;&t; *      doesn&squot;t seem to clear the controller if an external&n;&t;&t; *      device is hung)&n;&t;&t; *   2. Reset the controller and the other SMBus devices with a&n;&t;&t; *      T_OUT command. (this clears the host busy bit if an&n;&t;&t; *      external device is hung, but it comes back upon a new&n;&t;&t; *      access to a device)&n;&t;&t; *   3. Disable and reenable the controller in SMBHSTCFG. Worst&n;&t;&t; *      case, nothing seems to work except power reset.&n;&t;&t; */
multiline_comment|/* Try resetting entire SMB bus, including other devices - This&n;&t;&t; * may not work either - it clears the BUSY bit but then the&n;&t;&t; * BUSY bit may come back on when you try and use the chip&n;&t;&t; * again.  If that&squot;s the case you are stuck.&n;&t;&t; */
id|dev_info
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Resetting entire SMB Bus to clear busy condition (%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ALI1535_T_OUT
comma
id|SMBHSTTYP
)paren
suffix:semicolon
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
multiline_comment|/* now check the error bits and the busy bit */
r_if
c_cond
(paren
id|temp
op_amp
(paren
id|ALI1535_STS_ERR
op_or
id|ALI1535_STS_BUSY
)paren
)paren
(brace
multiline_comment|/* do a clear-on-write */
id|outb_p
c_func
(paren
l_int|0xFF
comma
id|SMBHSTSTS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
)paren
op_amp
(paren
id|ALI1535_STS_ERR
op_or
id|ALI1535_STS_BUSY
)paren
)paren
(brace
multiline_comment|/* This is probably going to be correctable only by a&n;&t;&t;&t; * power reset as one of the bits now appears to be&n;&t;&t;&t; * stuck */
multiline_comment|/* This may be a bus or device with electrical problems. */
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;SMBus reset failed! (0x%02x) - controller or &quot;
l_string|&quot;device on bus is probably hung&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* check and clear done bit */
r_if
c_cond
(paren
id|temp
op_amp
id|ALI1535_STS_DONE
)paren
(brace
id|outb_p
c_func
(paren
id|temp
comma
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* start the transaction by writing anything to the start register */
id|outb_p
c_func
(paren
l_int|0xFF
comma
id|SMBHSTPORT
)paren
suffix:semicolon
multiline_comment|/* We will always wait for a fraction of a second! */
id|timeout
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|temp
op_amp
id|ALI1535_STS_BUSY
)paren
op_logical_and
op_logical_neg
(paren
id|temp
op_amp
id|ALI1535_STS_IDLE
)paren
)paren
op_logical_and
(paren
id|timeout
op_increment
OL
id|MAX_TIMEOUT
)paren
)paren
suffix:semicolon
multiline_comment|/* If the SMBus is still busy, we give up */
r_if
c_cond
(paren
id|timeout
op_ge
id|MAX_TIMEOUT
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;SMBus Timeout!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
id|ALI1535_STS_FAIL
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Error: Failed bus transaction&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Unfortunately the ALI SMB controller maps &quot;no response&quot; and &quot;bus&n;&t; * collision&quot; into a single bit. No reponse is the usual case so don&squot;t&n;&t; * do a printk.  This means that bus collisions go unreported.&n;&t; */
r_if
c_cond
(paren
id|temp
op_amp
id|ALI1535_STS_BUSERR
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Error: no response or bus collision ADD=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMBHSTADD
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* haven&squot;t ever seen this */
r_if
c_cond
(paren
id|temp
op_amp
id|ALI1535_STS_DEV
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Error: device error&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* check to see if the &quot;command complete&quot; indication is set */
r_if
c_cond
(paren
op_logical_neg
(paren
id|temp
op_amp
id|ALI1535_STS_DONE
)paren
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Error: command never completed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Transaction (post): STS=%02x, TYP=%02x, &quot;
l_string|&quot;CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTTYP
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTCMD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTADD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT1
)paren
)paren
suffix:semicolon
multiline_comment|/* take consequent actions for error conditions */
r_if
c_cond
(paren
op_logical_neg
(paren
id|temp
op_amp
id|ALI1535_STS_DONE
)paren
)paren
(brace
multiline_comment|/* issue &quot;kill&quot; to reset host controller */
id|outb_p
c_func
(paren
id|ALI1535_KILL
comma
id|SMBHSTTYP
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xFF
comma
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|temp
op_amp
id|ALI1535_STS_ERR
)paren
(brace
multiline_comment|/* issue &quot;timeout&quot; to reset all devices on bus */
id|outb_p
c_func
(paren
id|ALI1535_T_OUT
comma
id|SMBHSTTYP
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xFF
comma
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Return -1 on error. */
DECL|function|ali1535_access
r_static
id|s32
id|ali1535_access
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
r_int
id|i
comma
id|len
suffix:semicolon
r_int
id|temp
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|s32
id|result
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|i2c_ali1535_sem
)paren
suffix:semicolon
multiline_comment|/* make sure SMBus is idle */
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
r_for
c_loop
(paren
id|timeout
op_assign
l_int|0
suffix:semicolon
(paren
id|timeout
OL
id|MAX_TIMEOUT
)paren
op_logical_and
op_logical_neg
(paren
id|temp
op_amp
id|ALI1535_STS_IDLE
)paren
suffix:semicolon
id|timeout
op_increment
)paren
(brace
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timeout
op_ge
id|MAX_TIMEOUT
)paren
id|dev_warn
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Idle wait Timeout! STS=0x%02x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* clear status register (clear-on-write) */
id|outb_p
c_func
(paren
l_int|0xFF
comma
id|SMBHSTSTS
)paren
suffix:semicolon
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
id|adap-&gt;dev
comma
l_string|&quot;I2C_SMBUS_PROC_CALL not supported!&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|EXIT
suffix:semicolon
r_case
id|I2C_SMBUS_QUICK
suffix:colon
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
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMBHSTADD
)paren
suffix:semicolon
id|size
op_assign
id|ALI1535_QUICK
suffix:semicolon
id|outb_p
c_func
(paren
id|size
comma
id|SMBHSTTYP
)paren
suffix:semicolon
multiline_comment|/* output command */
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
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
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMBHSTADD
)paren
suffix:semicolon
id|size
op_assign
id|ALI1535_BYTE
suffix:semicolon
id|outb_p
c_func
(paren
id|size
comma
id|SMBHSTTYP
)paren
suffix:semicolon
multiline_comment|/* output command */
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outb_p
c_func
(paren
id|command
comma
id|SMBHSTCMD
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
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
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMBHSTADD
)paren
suffix:semicolon
id|size
op_assign
id|ALI1535_BYTE_DATA
suffix:semicolon
id|outb_p
c_func
(paren
id|size
comma
id|SMBHSTTYP
)paren
suffix:semicolon
multiline_comment|/* output command */
id|outb_p
c_func
(paren
id|command
comma
id|SMBHSTCMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outb_p
c_func
(paren
id|data-&gt;byte
comma
id|SMBHSTDAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
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
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMBHSTADD
)paren
suffix:semicolon
id|size
op_assign
id|ALI1535_WORD_DATA
suffix:semicolon
id|outb_p
c_func
(paren
id|size
comma
id|SMBHSTTYP
)paren
suffix:semicolon
multiline_comment|/* output command */
id|outb_p
c_func
(paren
id|command
comma
id|SMBHSTCMD
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
id|outb_p
c_func
(paren
id|data-&gt;word
op_amp
l_int|0xff
comma
id|SMBHSTDAT0
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
id|SMBHSTDAT1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
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
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMBHSTADD
)paren
suffix:semicolon
id|size
op_assign
id|ALI1535_BLOCK_DATA
suffix:semicolon
id|outb_p
c_func
(paren
id|size
comma
id|SMBHSTTYP
)paren
suffix:semicolon
multiline_comment|/* output command */
id|outb_p
c_func
(paren
id|command
comma
id|SMBHSTCMD
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
l_int|0
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
l_int|32
)paren
(brace
id|len
op_assign
l_int|32
suffix:semicolon
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|len
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|len
comma
id|SMBHSTDAT0
)paren
suffix:semicolon
multiline_comment|/* Reset SMBBLKDAT */
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|SMBHSTTYP
)paren
op_or
id|ALI1535_BLOCK_CLR
comma
id|SMBHSTTYP
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|len
suffix:semicolon
id|i
op_increment
)paren
id|outb_p
c_func
(paren
id|data-&gt;block
(braket
id|i
)braket
comma
id|SMBBLKDAT
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ali1535_transaction
c_func
(paren
id|adap
)paren
)paren
(brace
multiline_comment|/* Error in transaction */
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|EXIT
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
op_logical_or
(paren
id|size
op_eq
id|ALI1535_QUICK
)paren
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
r_goto
id|EXIT
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|ALI1535_BYTE
suffix:colon
multiline_comment|/* Result put in SMBHSTDAT0 */
id|data-&gt;byte
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI1535_BYTE_DATA
suffix:colon
id|data-&gt;byte
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI1535_WORD_DATA
suffix:colon
id|data-&gt;word
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
op_plus
(paren
id|inb_p
c_func
(paren
id|SMBHSTDAT1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI1535_BLOCK_DATA
suffix:colon
id|len
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
suffix:semicolon
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
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|len
suffix:semicolon
multiline_comment|/* Reset SMBBLKDAT */
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|SMBHSTTYP
)paren
op_or
id|ALI1535_BLOCK_CLR
comma
id|SMBHSTTYP
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|data-&gt;block
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data-&gt;block
(braket
id|i
)braket
op_assign
id|inb_p
c_func
(paren
id|SMBBLKDAT
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Blk: len=%d, i=%d, data=%02x&bslash;n&quot;
comma
id|len
comma
id|i
comma
id|data-&gt;block
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|EXIT
suffix:colon
id|up
c_func
(paren
op_amp
id|i2c_ali1535_sem
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ali1535_func
id|u32
id|ali1535_func
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
id|ali1535_access
comma
dot
id|functionality
op_assign
id|ali1535_func
comma
)brace
suffix:semicolon
DECL|variable|ali1535_adapter
r_static
r_struct
id|i2c_adapter
id|ali1535_adapter
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
id|I2C_CLASS_HWMON
comma
dot
id|algo
op_assign
op_amp
id|smbus_algorithm
comma
dot
id|name
op_assign
l_string|&quot;unset&quot;
comma
)brace
suffix:semicolon
DECL|variable|ali1535_ids
r_static
r_struct
id|pci_device_id
id|ali1535_ids
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
id|PCI_DEVICE_ID_AL_M7101
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
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|ali1535_ids
)paren
suffix:semicolon
DECL|function|ali1535_probe
r_static
r_int
id|__devinit
id|ali1535_probe
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
r_if
c_cond
(paren
id|ali1535_setup
c_func
(paren
id|dev
)paren
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;ALI1535 not detected, module not inserted.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* set up the driverfs linkage to our parent device */
id|ali1535_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|ali1535_adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus ALI1535 adapter at %04x&quot;
comma
id|ali1535_smba
)paren
suffix:semicolon
r_return
id|i2c_add_adapter
c_func
(paren
op_amp
id|ali1535_adapter
)paren
suffix:semicolon
)brace
DECL|function|ali1535_remove
r_static
r_void
id|__devexit
id|ali1535_remove
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
id|ali1535_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ali1535_smba
comma
id|ALI1535_SMB_IOSIZE
)paren
suffix:semicolon
)brace
DECL|variable|ali1535_driver
r_static
r_struct
id|pci_driver
id|ali1535_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ali1535_smbus&quot;
comma
dot
id|id_table
op_assign
id|ali1535_ids
comma
dot
id|probe
op_assign
id|ali1535_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|ali1535_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_ali1535_init
r_static
r_int
id|__init
id|i2c_ali1535_init
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
id|ali1535_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_ali1535_exit
r_static
r_void
id|__exit
id|i2c_ali1535_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|ali1535_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt;, &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt;, &quot;
l_string|&quot;Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt; &quot;
l_string|&quot;and Dan Eaton &lt;dan.eaton@rocketlogix.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ALI1535 SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_ali1535_init
id|module_init
c_func
(paren
id|i2c_ali1535_init
)paren
suffix:semicolon
DECL|variable|i2c_ali1535_exit
id|module_exit
c_func
(paren
id|i2c_ali1535_exit
)paren
suffix:semicolon
eof
