multiline_comment|/*&n;    Retrieve encoded MAC address from 24C16 serial 2-wire EEPROM,&n;    decode it and store it in the associated adapter struct for&n;    use by dvb_net.c&n;&n;    This card appear to have the 24C16 write protect held to ground,&n;    thus permitting normal read/write operation. Theoretically it&n;    would be possible to write routines to burn a different (encoded)&n;    MAC address into the EEPROM.&n;&n;    Robert Schlabbach&t;GMX&n;    Michael Glaum&t;KVH Industries&n;    Holger Waechtler&t;Convergence&n;&n;    Copyright (C) 2002-2003 Ralph Metzler &lt;rjkm@metzlerbros.de&gt;&n;                            Metzler Brothers Systementwicklung GbR&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#if 1
DECL|macro|dprintk
mdefine_line|#define dprintk(x...) do { printk(x); } while (0)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(x...) do { } while (0)
macro_line|#endif
DECL|function|check_mac_tt
r_static
r_int
id|check_mac_tt
c_func
(paren
id|u8
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
id|u16
id|tmp
op_assign
l_int|0xffff
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
(paren
id|tmp
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|tmp
op_rshift
l_int|8
)paren
op_xor
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
id|tmp
op_xor_assign
(paren
id|tmp
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|tmp
op_xor_assign
(paren
id|tmp
op_lshift
l_int|12
)paren
op_xor
(paren
(paren
id|tmp
op_amp
l_int|0xff
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
)brace
id|tmp
op_xor_assign
l_int|0xffff
suffix:semicolon
r_return
(paren
(paren
(paren
id|tmp
op_rshift
l_int|8
)paren
op_xor
id|buf
(braket
l_int|8
)braket
)paren
op_or
(paren
(paren
id|tmp
op_amp
l_int|0xff
)paren
op_xor
id|buf
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|function|getmac_tt
r_static
r_int
id|getmac_tt
c_func
(paren
id|u8
op_star
id|decodedMAC
comma
id|u8
op_star
id|encodedMAC
)paren
(brace
id|u8
op_xor
(braket
l_int|20
)braket
op_assign
(brace
l_int|0x72
comma
l_int|0x23
comma
l_int|0x68
comma
l_int|0x19
comma
l_int|0x5c
comma
l_int|0xa8
comma
l_int|0x71
comma
l_int|0x2c
comma
l_int|0x54
comma
l_int|0xd3
comma
l_int|0x7b
comma
l_int|0xf1
comma
l_int|0x9E
comma
l_int|0x23
comma
l_int|0x16
comma
l_int|0xf6
comma
l_int|0x1d
comma
l_int|0x36
comma
l_int|0x64
comma
l_int|0x78
)brace
suffix:semicolon
id|u8
id|data
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* In case there is a sig check failure have the orig contents available */
id|memcpy
c_func
(paren
id|data
comma
id|encodedMAC
comma
l_int|20
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_xor_assign
op_xor
(braket
id|i
)braket
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
l_int|10
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
(paren
(paren
id|data
(braket
l_int|2
op_star
id|i
op_plus
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|2
op_star
id|i
)braket
)paren
op_rshift
(paren
(paren
id|data
(braket
l_int|2
op_star
id|i
op_plus
l_int|1
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_mac_tt
c_func
(paren
id|data
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|decodedMAC
(braket
l_int|0
)braket
op_assign
id|data
(braket
l_int|2
)braket
suffix:semicolon
id|decodedMAC
(braket
l_int|1
)braket
op_assign
id|data
(braket
l_int|1
)braket
suffix:semicolon
id|decodedMAC
(braket
l_int|2
)braket
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
id|decodedMAC
(braket
l_int|3
)braket
op_assign
id|data
(braket
l_int|6
)braket
suffix:semicolon
id|decodedMAC
(braket
l_int|4
)braket
op_assign
id|data
(braket
l_int|5
)braket
suffix:semicolon
id|decodedMAC
(braket
l_int|5
)braket
op_assign
id|data
(braket
l_int|4
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ttpci_eeprom_read_encodedMAC
r_static
r_int
id|ttpci_eeprom_read_encodedMAC
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
id|u8
op_star
id|encodedMAC
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|b0
(braket
)braket
op_assign
(brace
l_int|0xcc
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
)braket
op_assign
(brace
(brace
dot
id|addr
op_assign
l_int|0x50
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|b0
comma
dot
id|len
op_assign
l_int|1
)brace
comma
(brace
dot
id|addr
op_assign
l_int|0x50
comma
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|buf
op_assign
id|encodedMAC
comma
dot
id|len
op_assign
l_int|20
)brace
)brace
suffix:semicolon
multiline_comment|/* dprintk(&quot;%s&bslash;n&quot;, __FUNCTION__); */
id|ret
op_assign
id|i2c_transfer
c_func
(paren
id|adapter
comma
id|msg
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|2
)paren
multiline_comment|/* Assume EEPROM isn&squot;t there */
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ttpci_eeprom_parse_mac
r_int
id|ttpci_eeprom_parse_mac
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
id|u8
op_star
id|proposed_mac
)paren
(brace
r_int
id|ret
comma
id|i
suffix:semicolon
id|u8
id|encodedMAC
(braket
l_int|20
)braket
suffix:semicolon
id|u8
id|decodedMAC
(braket
l_int|6
)braket
suffix:semicolon
id|ret
op_assign
id|ttpci_eeprom_read_encodedMAC
c_func
(paren
id|adapter
comma
id|encodedMAC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Will only be -ENODEV */
id|dprintk
c_func
(paren
l_string|&quot;Couldn&squot;t read from EEPROM: not there?&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|proposed_mac
comma
l_int|0
comma
l_int|6
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|getmac_tt
c_func
(paren
id|decodedMAC
comma
id|encodedMAC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;adapter failed MAC signature check&bslash;n&quot;
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;encoded MAC from EEPROM was &quot;
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
l_int|19
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;%.2x:&quot;
comma
id|encodedMAC
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;%.2x&bslash;n&quot;
comma
id|encodedMAC
(braket
l_int|19
)braket
)paren
suffix:semicolon
id|memset
c_func
(paren
id|proposed_mac
comma
l_int|0
comma
l_int|6
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|proposed_mac
comma
id|decodedMAC
comma
l_int|6
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;adapter has MAC addr = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x&bslash;n&quot;
comma
id|decodedMAC
(braket
l_int|0
)braket
comma
id|decodedMAC
(braket
l_int|1
)braket
comma
id|decodedMAC
(braket
l_int|2
)braket
comma
id|decodedMAC
(braket
l_int|3
)braket
comma
id|decodedMAC
(braket
l_int|4
)braket
comma
id|decodedMAC
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ttpci_eeprom_parse_mac
id|EXPORT_SYMBOL
c_func
(paren
id|ttpci_eeprom_parse_mac
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralph Metzler, Marcus Metzler, others&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Decode dvb_net MAC address from EEPROM of PCI DVB cards &quot;
l_string|&quot;made by Siemens, Technotrend, Hauppauge&quot;
)paren
suffix:semicolon
eof
