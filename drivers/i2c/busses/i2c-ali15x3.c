multiline_comment|/*&n;    ali15x3.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;    Copyright (c) 1999  Frodo Looijaard &lt;frodol@dds.nl&gt; and&n;    Philip Edelbrock &lt;phil@netroedge.com&gt; and&n;    Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    This is the driver for the SMB Host controller on&n;    Acer Labs Inc. (ALI) M1541 and M1543C South Bridges.&n;&n;    The M1543C is a South bridge for desktop systems.&n;    The M1533 is a South bridge for portable systems.&n;    They are part of the following ALI chipsets:&n;       &quot;Aladdin Pro 2&quot;: Includes the M1621 Slot 1 North bridge&n;       with AGP and 100MHz CPU Front Side bus&n;       &quot;Aladdin V&quot;: Includes the M1541 Socket 7 North bridge&n;       with AGP and 100MHz CPU Front Side bus&n;       &quot;Aladdin IV&quot;: Includes the M1541 Socket 7 North bridge&n;       with host bus up to 83.3 MHz.&n;    For an overview of these chips see http://www.acerlabs.com&n;&n;    The M1533/M1543C devices appear as FOUR separate devices&n;    on the PCI bus. An output of lspci will show something similar&n;    to the following:&n;&n;&t;00:02.0 USB Controller: Acer Laboratories Inc. M5237&n;&t;00:03.0 Bridge: Acer Laboratories Inc. M7101&n;&t;00:07.0 ISA bridge: Acer Laboratories Inc. M1533&n;&t;00:0f.0 IDE interface: Acer Laboratories Inc. M5229&n;&n;    The SMB controller is part of the 7101 device, which is an&n;    ACPI-compliant Power Management Unit (PMU).&n;&n;    The whole 7101 device has to be enabled for the SMB to work.&n;    You can&squot;t just enable the SMB alone.&n;    The SMB and the ACPI have separate I/O spaces.&n;    We make sure that the SMB is enabled. We leave the ACPI alone.&n;&n;    This driver controls the SMB Host only.&n;    The SMB Slave controller on the M15X3 is not enabled.&n;&n;    This driver does not use interrupts.&n;*/
multiline_comment|/* Note: we assume there can only be one ALI15X3, with one SMBus interface */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* ALI15X3 SMBus address offsets */
DECL|macro|SMBHSTSTS
mdefine_line|#define SMBHSTSTS&t;(0 + ali15x3_smba)
DECL|macro|SMBHSTCNT
mdefine_line|#define SMBHSTCNT&t;(1 + ali15x3_smba)
DECL|macro|SMBHSTSTART
mdefine_line|#define SMBHSTSTART&t;(2 + ali15x3_smba)
DECL|macro|SMBHSTCMD
mdefine_line|#define SMBHSTCMD&t;(7 + ali15x3_smba)
DECL|macro|SMBHSTADD
mdefine_line|#define SMBHSTADD&t;(3 + ali15x3_smba)
DECL|macro|SMBHSTDAT0
mdefine_line|#define SMBHSTDAT0&t;(4 + ali15x3_smba)
DECL|macro|SMBHSTDAT1
mdefine_line|#define SMBHSTDAT1&t;(5 + ali15x3_smba)
DECL|macro|SMBBLKDAT
mdefine_line|#define SMBBLKDAT&t;(6 + ali15x3_smba)
multiline_comment|/* PCI Address Constants */
DECL|macro|SMBCOM
mdefine_line|#define SMBCOM&t;&t;0x004
DECL|macro|SMBBA
mdefine_line|#define SMBBA&t;&t;0x014
DECL|macro|SMBATPC
mdefine_line|#define SMBATPC&t;&t;0x05B&t;/* used to unlock xxxBA registers */
DECL|macro|SMBHSTCFG
mdefine_line|#define SMBHSTCFG&t;0x0E0
DECL|macro|SMBSLVC
mdefine_line|#define SMBSLVC&t;&t;0x0E1
DECL|macro|SMBCLK
mdefine_line|#define SMBCLK&t;&t;0x0E2
DECL|macro|SMBREV
mdefine_line|#define SMBREV&t;&t;0x008
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT&t;&t;200&t;/* times 1/100 sec */
DECL|macro|ALI15X3_SMB_IOSIZE
mdefine_line|#define ALI15X3_SMB_IOSIZE&t;32
multiline_comment|/* this is what the Award 1004 BIOS sets them to on a ASUS P5A MB.&n;   We don&squot;t use these here. If the bases aren&squot;t set to some value we&n;   tell user to upgrade BIOS and we fail.&n;*/
DECL|macro|ALI15X3_SMB_DEFAULTBASE
mdefine_line|#define ALI15X3_SMB_DEFAULTBASE&t;0xE800
multiline_comment|/* ALI15X3 address lock bits */
DECL|macro|ALI15X3_LOCK
mdefine_line|#define ALI15X3_LOCK&t;&t;0x06
multiline_comment|/* ALI15X3 command constants */
DECL|macro|ALI15X3_ABORT
mdefine_line|#define ALI15X3_ABORT&t;&t;0x02
DECL|macro|ALI15X3_T_OUT
mdefine_line|#define ALI15X3_T_OUT&t;&t;0x04
DECL|macro|ALI15X3_QUICK
mdefine_line|#define ALI15X3_QUICK&t;&t;0x00
DECL|macro|ALI15X3_BYTE
mdefine_line|#define ALI15X3_BYTE&t;&t;0x10
DECL|macro|ALI15X3_BYTE_DATA
mdefine_line|#define ALI15X3_BYTE_DATA&t;0x20
DECL|macro|ALI15X3_WORD_DATA
mdefine_line|#define ALI15X3_WORD_DATA&t;0x30
DECL|macro|ALI15X3_BLOCK_DATA
mdefine_line|#define ALI15X3_BLOCK_DATA&t;0x40
DECL|macro|ALI15X3_BLOCK_CLR
mdefine_line|#define ALI15X3_BLOCK_CLR&t;0x80
multiline_comment|/* ALI15X3 status register bits */
DECL|macro|ALI15X3_STS_IDLE
mdefine_line|#define ALI15X3_STS_IDLE&t;0x04
DECL|macro|ALI15X3_STS_BUSY
mdefine_line|#define ALI15X3_STS_BUSY&t;0x08
DECL|macro|ALI15X3_STS_DONE
mdefine_line|#define ALI15X3_STS_DONE&t;0x10
DECL|macro|ALI15X3_STS_DEV
mdefine_line|#define ALI15X3_STS_DEV&t;&t;0x20&t;/* device error */
DECL|macro|ALI15X3_STS_COLL
mdefine_line|#define ALI15X3_STS_COLL&t;0x40&t;/* collision or no response */
DECL|macro|ALI15X3_STS_TERM
mdefine_line|#define ALI15X3_STS_TERM&t;0x80&t;/* terminated by abort */
DECL|macro|ALI15X3_STS_ERR
mdefine_line|#define ALI15X3_STS_ERR&t;&t;0xE0&t;/* all the bad error bits */
multiline_comment|/* If force_addr is set to anything different from 0, we forcibly enable&n;   the device at the given address. */
DECL|variable|force_addr
r_static
r_int
id|force_addr
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|force_addr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|force_addr
comma
l_string|&quot;Initialize the base address of the i2c controller&quot;
)paren
suffix:semicolon
DECL|variable|ali15x3_smba
r_static
r_int
r_int
id|ali15x3_smba
op_assign
l_int|0
suffix:semicolon
DECL|function|ali15x3_setup
r_static
r_int
id|ali15x3_setup
c_func
(paren
r_struct
id|pci_dev
op_star
id|ALI15X3_dev
)paren
(brace
id|u16
id|a
suffix:semicolon
r_int
r_char
id|temp
suffix:semicolon
multiline_comment|/* Check the following things:&n;&t;&t;- SMB I/O address is initialized&n;&t;&t;- Device is enabled&n;&t;&t;- We can use the addresses&n;&t;*/
multiline_comment|/* Unlock the register.&n;&t;   The data sheet says that the address registers are read-only&n;&t;   if the lock bits are 1, but in fact the address registers&n;&t;   are zero unless you clear the lock bits.&n;&t;*/
id|pci_read_config_byte
c_func
(paren
id|ALI15X3_dev
comma
id|SMBATPC
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|ALI15X3_LOCK
)paren
(brace
id|temp
op_and_assign
op_complement
id|ALI15X3_LOCK
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|ALI15X3_dev
comma
id|SMBATPC
comma
id|temp
)paren
suffix:semicolon
)brace
multiline_comment|/* Determine the address of the SMBus area */
id|pci_read_config_word
c_func
(paren
id|ALI15X3_dev
comma
id|SMBBA
comma
op_amp
id|ali15x3_smba
)paren
suffix:semicolon
id|ali15x3_smba
op_and_assign
(paren
l_int|0xffff
op_amp
op_complement
(paren
id|ALI15X3_SMB_IOSIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ali15x3_smba
op_eq
l_int|0
op_logical_and
id|force_addr
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|ALI15X3_dev-&gt;dev
comma
l_string|&quot;ALI15X3_smb region uninitialized &quot;
l_string|&quot;- upgrade BIOS or use force_addr=0xaddr&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|ali15x3_smba
op_assign
id|force_addr
op_amp
op_complement
(paren
id|ALI15X3_SMB_IOSIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ali15x3_smba
comma
id|ALI15X3_SMB_IOSIZE
comma
l_string|&quot;ali15x3-smb&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|ALI15X3_dev-&gt;dev
comma
l_string|&quot;ALI15X3_smb region 0x%x already in use!&bslash;n&quot;
comma
id|ali15x3_smba
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|dev_info
c_func
(paren
op_amp
id|ALI15X3_dev-&gt;dev
comma
l_string|&quot;forcing ISA address 0x%04X&bslash;n&quot;
comma
id|ali15x3_smba
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PCIBIOS_SUCCESSFUL
op_ne
id|pci_write_config_word
c_func
(paren
id|ALI15X3_dev
comma
id|SMBBA
comma
id|ali15x3_smba
)paren
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|PCIBIOS_SUCCESSFUL
op_ne
id|pci_read_config_word
c_func
(paren
id|ALI15X3_dev
comma
id|SMBBA
comma
op_amp
id|a
)paren
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a
op_amp
op_complement
(paren
id|ALI15X3_SMB_IOSIZE
op_minus
l_int|1
)paren
)paren
op_ne
id|ali15x3_smba
)paren
(brace
multiline_comment|/* make sure it works */
id|dev_err
c_func
(paren
op_amp
id|ALI15X3_dev-&gt;dev
comma
l_string|&quot;force address failed - not supported?&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
multiline_comment|/* check if whole device is enabled */
id|pci_read_config_byte
c_func
(paren
id|ALI15X3_dev
comma
id|SMBCOM
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
id|dev_info
c_func
(paren
op_amp
id|ALI15X3_dev-&gt;dev
comma
l_string|&quot;enabling SMBus device&bslash;n&quot;
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|ALI15X3_dev
comma
id|SMBCOM
comma
id|temp
op_or
l_int|0x01
)paren
suffix:semicolon
)brace
multiline_comment|/* Is SMB Host controller enabled? */
id|pci_read_config_byte
c_func
(paren
id|ALI15X3_dev
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
id|dev_info
c_func
(paren
op_amp
id|ALI15X3_dev-&gt;dev
comma
l_string|&quot;enabling SMBus controller&bslash;n&quot;
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|ALI15X3_dev
comma
id|SMBHSTCFG
comma
id|temp
op_or
l_int|0x01
)paren
suffix:semicolon
)brace
multiline_comment|/* set SMB clock to 74KHz as recommended in data sheet */
id|pci_write_config_byte
c_func
(paren
id|ALI15X3_dev
comma
id|SMBCLK
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/*&n;&t;  The interrupt routing for SMB is set up in register 0x77 in the&n;&t;  1533 ISA Bridge device, NOT in the 7101 device.&n;&t;  Don&squot;t bother with finding the 1533 device and reading the register.&n;&t;if ((....... &amp; 0x0F) == 1)&n;&t;&t;dev_dbg(&amp;ALI15X3_dev-&gt;dev, &quot;ALI15X3 using Interrupt 9 for SMBus.&bslash;n&quot;);&n;&t;*/
id|pci_read_config_byte
c_func
(paren
id|ALI15X3_dev
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
id|ALI15X3_dev-&gt;dev
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
id|ALI15X3_dev-&gt;dev
comma
l_string|&quot;iALI15X3_smba = 0x%X&bslash;n&quot;
comma
id|ali15x3_smba
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|release_region
c_func
(paren
id|ali15x3_smba
comma
id|ALI15X3_SMB_IOSIZE
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Another internally used function */
DECL|function|ali15x3_transaction
r_static
r_int
id|ali15x3_transaction
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
l_string|&quot;Transaction (pre): STS=%02x, CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
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
id|SMBHSTCNT
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
id|ALI15X3_STS_BUSY
)paren
(brace
multiline_comment|/*&n;&t;   If the host controller is still busy, it may have timed out in the&n;&t;   previous transaction, resulting in a &quot;SMBus Timeout&quot; Dev.&n;&t;   I&squot;ve tried the following to reset a stuck busy bit.&n;&t;&t;1. Reset the controller with an ABORT command.&n;&t;&t;   (this doesn&squot;t seem to clear the controller if an external&n;&t;&t;   device is hung)&n;&t;&t;2. Reset the controller and the other SMBus devices with a&n;&t;&t;   T_OUT command.  (this clears the host busy bit if an&n;&t;&t;   external device is hung, but it comes back upon a new access&n;&t;&t;   to a device)&n;&t;&t;3. Disable and reenable the controller in SMBHSTCFG&n;&t;   Worst case, nothing seems to work except power reset.&n;&t;*/
multiline_comment|/* Abort - reset the host controller */
multiline_comment|/*&n;&t;   Try resetting entire SMB bus, including other devices -&n;&t;   This may not work either - it clears the BUSY bit but&n;&t;   then the BUSY bit may come back on when you try and use the chip again.&n;&t;   If that&squot;s the case you are stuck.&n;&t;*/
id|dev_info
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Resetting entire SMB Bus to &quot;
l_string|&quot;clear busy condition (%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ALI15X3_T_OUT
comma
id|SMBHSTCNT
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
id|ALI15X3_STS_ERR
op_or
id|ALI15X3_STS_BUSY
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
id|ALI15X3_STS_ERR
op_or
id|ALI15X3_STS_BUSY
)paren
)paren
(brace
multiline_comment|/* this is probably going to be correctable only by a power reset&n;&t;&t;&t;   as one of the bits now appears to be stuck */
multiline_comment|/* This may be a bus or device with electrical problems. */
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;SMBus reset failed! (0x%02x) - &quot;
l_string|&quot;controller or device on bus is probably hung&bslash;n&quot;
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
id|ALI15X3_STS_DONE
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
id|SMBHSTSTART
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
op_logical_neg
(paren
id|temp
op_amp
(paren
id|ALI15X3_STS_ERR
op_or
id|ALI15X3_STS_DONE
)paren
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
id|ALI15X3_STS_TERM
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
multiline_comment|/*&n;&t;  Unfortunately the ALI SMB controller maps &quot;no response&quot; and &quot;bus&n;&t;  collision&quot; into a single bit. No reponse is the usual case so don&squot;t&n;&t;  do a printk.&n;&t;  This means that bus collisions go unreported.&n;&t;*/
r_if
c_cond
(paren
id|temp
op_amp
id|ALI15X3_STS_COLL
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
id|ALI15X3_STS_DEV
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
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Transaction (post): STS=%02x, CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
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
id|SMBHSTCNT
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
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Return -1 on error. */
DECL|function|ali15x3_access
r_static
id|s32
id|ali15x3_access
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
multiline_comment|/* clear all the bits (clear-on-write) */
id|outb_p
c_func
(paren
l_int|0xFF
comma
id|SMBHSTSTS
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
id|ALI15X3_STS_IDLE
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
(brace
id|dev_err
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
)brace
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
r_return
op_minus
l_int|1
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
id|ALI15X3_QUICK
suffix:semicolon
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
id|size
op_assign
id|ALI15X3_BYTE
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
id|size
op_assign
id|ALI15X3_BYTE_DATA
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
id|size
op_assign
id|ALI15X3_WORD_DATA
suffix:semicolon
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
id|SMBHSTCNT
)paren
op_or
id|ALI15X3_BLOCK_CLR
comma
id|SMBHSTCNT
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
id|size
op_assign
id|ALI15X3_BLOCK_DATA
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|size
comma
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* output command */
r_if
c_cond
(paren
id|ali15x3_transaction
c_func
(paren
id|adap
)paren
)paren
multiline_comment|/* Error in transaction */
r_return
op_minus
l_int|1
suffix:semicolon
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
id|ALI15X3_QUICK
)paren
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
id|ALI15X3_BYTE
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
id|ALI15X3_BYTE_DATA
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
id|ALI15X3_WORD_DATA
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
id|ALI15X3_BLOCK_DATA
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
id|SMBHSTCNT
)paren
op_or
id|ALI15X3_BLOCK_CLR
comma
id|SMBHSTCNT
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ali15x3_func
r_static
id|u32
id|ali15x3_func
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
l_string|&quot;Non-I2C SMBus adapter&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SMBUS
comma
dot
id|smbus_xfer
op_assign
id|ali15x3_access
comma
dot
id|functionality
op_assign
id|ali15x3_func
comma
)brace
suffix:semicolon
DECL|variable|ali15x3_adapter
r_static
r_struct
id|i2c_adapter
id|ali15x3_adapter
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
DECL|variable|ali15x3_ids
r_static
r_struct
id|pci_device_id
id|ali15x3_ids
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
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|ali15x3_probe
r_static
r_int
id|__devinit
id|ali15x3_probe
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
id|ali15x3_setup
c_func
(paren
id|dev
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;ALI15X3 not detected, module not inserted.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* set up the driverfs linkage to our parent device */
id|ali15x3_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|ali15x3_adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus ALI15X3 adapter at %04x&quot;
comma
id|ali15x3_smba
)paren
suffix:semicolon
r_return
id|i2c_add_adapter
c_func
(paren
op_amp
id|ali15x3_adapter
)paren
suffix:semicolon
)brace
DECL|function|ali15x3_remove
r_static
r_void
id|__devexit
id|ali15x3_remove
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
id|ali15x3_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ali15x3_smba
comma
id|ALI15X3_SMB_IOSIZE
)paren
suffix:semicolon
)brace
DECL|variable|ali15x3_driver
r_static
r_struct
id|pci_driver
id|ali15x3_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ali15x3 smbus&quot;
comma
dot
id|id_table
op_assign
id|ali15x3_ids
comma
dot
id|probe
op_assign
id|ali15x3_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|ali15x3_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_ali15x3_init
r_static
r_int
id|__init
id|i2c_ali15x3_init
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
id|ali15x3_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_ali15x3_exit
r_static
r_void
id|__exit
id|i2c_ali15x3_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|ali15x3_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt;, &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt;, &quot;
l_string|&quot;and Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ALI15X3 SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_ali15x3_init
id|module_init
c_func
(paren
id|i2c_ali15x3_init
)paren
suffix:semicolon
DECL|variable|i2c_ali15x3_exit
id|module_exit
c_func
(paren
id|i2c_ali15x3_exit
)paren
suffix:semicolon
eof
