multiline_comment|/*&n;    piix4.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;    Copyright (c) 1998 - 2002 Frodo Looijaard &lt;frodol@dds.nl&gt; and&n;    Philip Edelbrock &lt;phil@netroedge.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;   Supports:&n;&t;Intel PIIX4, 440MX&n;&t;Serverworks OSB4, CSB5, CSB6&n;&t;SMSC Victory66&n;&n;   Note: we assume there can only be one device, with one SMBus interface.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|struct|sd
r_struct
id|sd
(brace
DECL|member|mfr
r_const
r_int
r_int
id|mfr
suffix:semicolon
DECL|member|dev
r_const
r_int
r_int
id|dev
suffix:semicolon
DECL|member|fn
r_const
r_int
r_char
id|fn
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* PIIX4 SMBus address offsets */
DECL|macro|SMBHSTSTS
mdefine_line|#define SMBHSTSTS&t;(0 + piix4_smba)
DECL|macro|SMBHSLVSTS
mdefine_line|#define SMBHSLVSTS&t;(1 + piix4_smba)
DECL|macro|SMBHSTCNT
mdefine_line|#define SMBHSTCNT&t;(2 + piix4_smba)
DECL|macro|SMBHSTCMD
mdefine_line|#define SMBHSTCMD&t;(3 + piix4_smba)
DECL|macro|SMBHSTADD
mdefine_line|#define SMBHSTADD&t;(4 + piix4_smba)
DECL|macro|SMBHSTDAT0
mdefine_line|#define SMBHSTDAT0&t;(5 + piix4_smba)
DECL|macro|SMBHSTDAT1
mdefine_line|#define SMBHSTDAT1&t;(6 + piix4_smba)
DECL|macro|SMBBLKDAT
mdefine_line|#define SMBBLKDAT&t;(7 + piix4_smba)
DECL|macro|SMBSLVCNT
mdefine_line|#define SMBSLVCNT&t;(8 + piix4_smba)
DECL|macro|SMBSHDWCMD
mdefine_line|#define SMBSHDWCMD&t;(9 + piix4_smba)
DECL|macro|SMBSLVEVT
mdefine_line|#define SMBSLVEVT&t;(0xA + piix4_smba)
DECL|macro|SMBSLVDAT
mdefine_line|#define SMBSLVDAT&t;(0xC + piix4_smba)
multiline_comment|/* count for request_region */
DECL|macro|SMBIOSIZE
mdefine_line|#define SMBIOSIZE&t;8
multiline_comment|/* PCI Address Constants */
DECL|macro|SMBBA
mdefine_line|#define SMBBA&t;&t;0x090
DECL|macro|SMBHSTCFG
mdefine_line|#define SMBHSTCFG&t;0x0D2
DECL|macro|SMBSLVC
mdefine_line|#define SMBSLVC&t;&t;0x0D3
DECL|macro|SMBSHDW1
mdefine_line|#define SMBSHDW1&t;0x0D4
DECL|macro|SMBSHDW2
mdefine_line|#define SMBSHDW2&t;0x0D5
DECL|macro|SMBREV
mdefine_line|#define SMBREV&t;&t;0x0D6
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT&t;500
DECL|macro|ENABLE_INT9
mdefine_line|#define  ENABLE_INT9&t;0
multiline_comment|/* PIIX4 constants */
DECL|macro|PIIX4_QUICK
mdefine_line|#define PIIX4_QUICK&t;&t;0x00
DECL|macro|PIIX4_BYTE
mdefine_line|#define PIIX4_BYTE&t;&t;0x04
DECL|macro|PIIX4_BYTE_DATA
mdefine_line|#define PIIX4_BYTE_DATA&t;&t;0x08
DECL|macro|PIIX4_WORD_DATA
mdefine_line|#define PIIX4_WORD_DATA&t;&t;0x0C
DECL|macro|PIIX4_BLOCK_DATA
mdefine_line|#define PIIX4_BLOCK_DATA&t;0x14
multiline_comment|/* insmod parameters */
multiline_comment|/* If force is set to anything different from 0, we forcibly enable the&n;   PIIX4. DANGEROUS! */
DECL|variable|force
r_static
r_int
id|force
op_assign
l_int|0
suffix:semicolon
id|module_param
(paren
id|force
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|force
comma
l_string|&quot;Forcibly enable the PIIX4. DANGEROUS!&quot;
)paren
suffix:semicolon
multiline_comment|/* If force_addr is set to anything different from 0, we forcibly enable&n;   the PIIX4 at the given address. VERY DANGEROUS! */
DECL|variable|force_addr
r_static
r_int
id|force_addr
op_assign
l_int|0
suffix:semicolon
id|module_param
(paren
id|force_addr
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|force_addr
comma
l_string|&quot;Forcibly enable the PIIX4 at the given address. &quot;
l_string|&quot;EXTREMELY DANGEROUS!&quot;
)paren
suffix:semicolon
multiline_comment|/* If fix_hstcfg is set to anything different from 0, we reset one of the&n;   registers to be a valid value. */
DECL|variable|fix_hstcfg
r_static
r_int
id|fix_hstcfg
op_assign
l_int|0
suffix:semicolon
id|module_param
(paren
id|fix_hstcfg
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|fix_hstcfg
comma
l_string|&quot;Fix config register. Needed on some boards (Force CPCI735).&quot;
)paren
suffix:semicolon
r_static
r_int
id|piix4_transaction
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|piix4_smba
r_static
r_int
r_int
id|piix4_smba
op_assign
l_int|0
suffix:semicolon
DECL|variable|piix4_adapter
r_static
r_struct
id|i2c_adapter
id|piix4_adapter
suffix:semicolon
multiline_comment|/*&n; * Get DMI information.&n; */
DECL|function|ibm_dmi_probe
r_static
r_int
id|__devinit
id|ibm_dmi_probe
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_X86
r_extern
r_int
id|is_unsafe_smbus
suffix:semicolon
r_return
id|is_unsafe_smbus
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|piix4_setup
r_static
r_int
id|__devinit
id|piix4_setup
c_func
(paren
r_struct
id|pci_dev
op_star
id|PIIX4_dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_int
r_char
id|temp
suffix:semicolon
multiline_comment|/* match up the function */
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|PIIX4_dev-&gt;devfn
)paren
op_ne
id|id-&gt;driver_data
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Found %s device&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|PIIX4_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ibm_dmi_probe
c_func
(paren
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;IBM Laptop detected; this module &quot;
l_string|&quot;may corrupt your serial eeprom! Refusing to load &quot;
l_string|&quot;module!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
multiline_comment|/* Determine the address of the SMBus areas */
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|piix4_smba
op_assign
id|force_addr
op_amp
l_int|0xfff0
suffix:semicolon
id|force
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|pci_read_config_word
c_func
(paren
id|PIIX4_dev
comma
id|SMBBA
comma
op_amp
id|piix4_smba
)paren
suffix:semicolon
id|piix4_smba
op_and_assign
l_int|0xfff0
suffix:semicolon
r_if
c_cond
(paren
id|piix4_smba
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;SMB base address &quot;
l_string|&quot;uninitialized - upgrade BIOS or use &quot;
l_string|&quot;force_addr=0xaddr&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|piix4_smba
comma
id|SMBIOSIZE
comma
l_string|&quot;piix4-smbus&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;SMB region 0x%x already in use!&bslash;n&quot;
comma
id|piix4_smba
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|PIIX4_dev
comma
id|SMBHSTCFG
comma
op_amp
id|temp
)paren
suffix:semicolon
multiline_comment|/* Some BIOS will set up the chipset incorrectly and leave a register&n;&t;   in an undefined state (causing I2C to act very strangely). */
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x02
)paren
(brace
r_if
c_cond
(paren
id|fix_hstcfg
)paren
(brace
id|dev_info
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Working around buggy BIOS &quot;
l_string|&quot;(I2C)&bslash;n&quot;
)paren
suffix:semicolon
id|temp
op_and_assign
l_int|0xfd
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|PIIX4_dev
comma
id|SMBHSTCFG
comma
id|temp
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev_info
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Unusual config register &quot;
l_string|&quot;value&bslash;n&quot;
)paren
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Try using fix_hstcfg=1 if &quot;
l_string|&quot;you experience problems&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* If force_addr is set, we program the new address here. Just to make&n;&t;   sure, we disable the PIIX4 first. */
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|PIIX4_dev
comma
id|SMBHSTCFG
comma
id|temp
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|PIIX4_dev
comma
id|SMBBA
comma
id|piix4_smba
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|PIIX4_dev
comma
id|SMBHSTCFG
comma
id|temp
op_or
l_int|0x01
)paren
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;WARNING: SMBus interface set to &quot;
l_string|&quot;new address %04x!&bslash;n&quot;
comma
id|piix4_smba
)paren
suffix:semicolon
)brace
r_else
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
r_if
c_cond
(paren
id|force
)paren
(brace
multiline_comment|/* This should never need to be done, but has been&n;&t;&t;&t; * noted that many Dell machines have the SMBus&n;&t;&t;&t; * interface on the PIIX4 disabled!? NOTE: This assumes&n;&t;&t;&t; * I/O space and other allocations WERE done by the&n;&t;&t;&t; * Bios!  Don&squot;t complain if your hardware does weird&n;&t;&t;&t; * things after enabling this. :&squot;) Check for Bios&n;&t;&t;&t; * updates before resorting to this.&n;&t;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|PIIX4_dev
comma
id|SMBHSTCFG
comma
id|temp
op_or
l_int|1
)paren
suffix:semicolon
id|dev_printk
c_func
(paren
id|KERN_NOTICE
comma
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;WARNING: SMBus interface has been &quot;
l_string|&quot;FORCEFULLY ENABLED!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev_err
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Host SMBus controller not enabled!&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|piix4_smba
comma
id|SMBIOSIZE
)paren
suffix:semicolon
id|piix4_smba
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|0x0E
)paren
op_eq
l_int|8
)paren
id|dev_dbg
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Using Interrupt 9 for SMBus.&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|0x0E
)paren
op_eq
l_int|0
)paren
id|dev_dbg
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Using Interrupt SMI# for SMBus.&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|dev_err
c_func
(paren
op_amp
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;Illegal Interrupt configuration &quot;
l_string|&quot;(or code out of date)!&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|PIIX4_dev
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
id|PIIX4_dev-&gt;dev
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
id|PIIX4_dev-&gt;dev
comma
l_string|&quot;SMBA = 0x%X&bslash;n&quot;
comma
id|piix4_smba
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Another internally used function */
DECL|function|piix4_transaction
r_static
r_int
id|piix4_transaction
c_func
(paren
r_void
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
id|piix4_adapter.dev
comma
l_string|&quot;Transaction (pre): CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
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
multiline_comment|/* Make sure the SMBus host is ready to start transmitting */
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
op_ne
l_int|0x00
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|piix4_adapter.dev
comma
l_string|&quot;SMBus busy (%02x). &quot;
l_string|&quot;Resetting... &bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|temp
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
op_ne
l_int|0x00
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|piix4_adapter.dev
comma
l_string|&quot;Failed! (%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|dev_dbg
c_func
(paren
op_amp
id|piix4_adapter.dev
comma
l_string|&quot;Successfull!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* start the transaction by setting bit 6 */
id|outb_p
c_func
(paren
id|inb
c_func
(paren
id|SMBHSTCNT
)paren
op_or
l_int|0x040
comma
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* We will always wait for a fraction of a second! (See PIIX4 docs errata) */
r_do
(brace
id|i2c_delay
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
id|temp
op_amp
l_int|0x01
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
id|dev_err
c_func
(paren
op_amp
id|piix4_adapter.dev
comma
l_string|&quot;SMBus Timeout!&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x10
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
id|piix4_adapter.dev
comma
l_string|&quot;Error: Failed bus transaction&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x08
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
id|piix4_adapter.dev
comma
l_string|&quot;Bus collision! SMBus may be &quot;
l_string|&quot;locked until next hard reset. (sorry!)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Clock stops and slave is stuck in mid-transmission */
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x04
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
id|piix4_adapter.dev
comma
l_string|&quot;Error: no response!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
op_ne
l_int|0x00
)paren
id|outb_p
c_func
(paren
id|inb
c_func
(paren
id|SMBHSTSTS
)paren
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
op_ne
l_int|0x00
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|piix4_adapter.dev
comma
l_string|&quot;Failed reset at end of &quot;
l_string|&quot;transaction (%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
id|dev_dbg
c_func
(paren
op_amp
id|piix4_adapter.dev
comma
l_string|&quot;Transaction (post): CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
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
DECL|function|piix4_access
r_static
id|s32
id|piix4_access
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
id|PIIX4_QUICK
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
id|PIIX4_BYTE
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
id|PIIX4_BYTE_DATA
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
id|PIIX4_WORD_DATA
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
id|len
op_assign
l_int|0
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
id|outb_p
c_func
(paren
id|len
comma
id|SMBHSTDAT0
)paren
suffix:semicolon
id|i
op_assign
id|inb_p
c_func
(paren
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* Reset SMBBLKDAT */
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
id|PIIX4_BLOCK_DATA
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb_p
c_func
(paren
(paren
id|size
op_amp
l_int|0x1C
)paren
op_plus
(paren
id|ENABLE_INT9
op_amp
l_int|1
)paren
comma
id|SMBHSTCNT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|piix4_transaction
c_func
(paren
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
id|PIIX4_QUICK
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
id|PIIX4_BYTE
suffix:colon
multiline_comment|/* Where is the result put? I assume here it is in&n;&t;&t;&t;&t;   SMBHSTDAT0 but it might just as well be in the&n;&t;&t;&t;&t;   SMBHSTCMD. No clue in the docs */
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
id|PIIX4_BYTE_DATA
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
id|PIIX4_WORD_DATA
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
id|PIIX4_BLOCK_DATA
suffix:colon
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
suffix:semicolon
id|i
op_assign
id|inb_p
c_func
(paren
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* Reset SMBBLKDAT */
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
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|piix4_func
r_static
id|u32
id|piix4_func
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
id|piix4_access
comma
dot
id|functionality
op_assign
id|piix4_func
comma
)brace
suffix:semicolon
DECL|variable|piix4_adapter
r_static
r_struct
id|i2c_adapter
id|piix4_adapter
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
id|smbus_algorithm
comma
dot
id|name
op_assign
l_string|&quot;unset&quot;
comma
)brace
suffix:semicolon
DECL|variable|piix4_ids
r_static
r_struct
id|pci_device_id
id|piix4_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82371AB_3
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
dot
id|driver_data
op_assign
l_int|3
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_SERVERWORKS
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_SERVERWORKS_OSB4
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
dot
id|driver_data
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_SERVERWORKS
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_SERVERWORKS_CSB5
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
dot
id|driver_data
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_SERVERWORKS
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_SERVERWORKS_CSB6
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
dot
id|driver_data
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82443MX_3
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
dot
id|driver_data
op_assign
l_int|3
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_EFAR
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_EFAR_SLC90E66_3
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
dot
id|driver_data
op_assign
l_int|0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|piix4_probe
r_static
r_int
id|__devinit
id|piix4_probe
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
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|piix4_setup
c_func
(paren
id|dev
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* set up the driverfs linkage to our parent device */
id|piix4_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|piix4_adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus PIIX4 adapter at %04x&quot;
comma
id|piix4_smba
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|piix4_adapter
)paren
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Couldn&squot;t register adapter!&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|piix4_smba
comma
id|SMBIOSIZE
)paren
suffix:semicolon
id|piix4_smba
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|piix4_remove
r_static
r_void
id|__devexit
id|piix4_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|piix4_smba
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|piix4_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|piix4_smba
comma
id|SMBIOSIZE
)paren
suffix:semicolon
id|piix4_smba
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|piix4_driver
r_static
r_struct
id|pci_driver
id|piix4_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;piix4-smbus&quot;
comma
dot
id|id_table
op_assign
id|piix4_ids
comma
dot
id|probe
op_assign
id|piix4_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|piix4_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_piix4_init
r_static
r_int
id|__init
id|i2c_piix4_init
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
id|piix4_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_piix4_exit
r_static
r_void
id|__exit
id|i2c_piix4_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|piix4_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt; and &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PIIX4 SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_piix4_init
id|module_init
c_func
(paren
id|i2c_piix4_init
)paren
suffix:semicolon
DECL|variable|i2c_piix4_exit
id|module_exit
c_func
(paren
id|i2c_piix4_exit
)paren
suffix:semicolon
eof
