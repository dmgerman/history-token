multiline_comment|/*&n;    Retrieve encoded MAC address from ATMEL ttpci_eeprom serial 2-wire EEPROM,&n;    decode it and store it in associated adapter net device&n;&n;    Robert Schlabbach&t;GMX&n;    Michael Glaum&t;KVH Industries&n;    Holger Waechtler&t;Convergence&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#ifndef __TTPCI_EEPROM_H__
DECL|macro|__TTPCI_EEPROM_H__
mdefine_line|#define __TTPCI_EEPROM_H__
macro_line|#include &quot;dvb_i2c.h&quot;
r_extern
r_int
id|ttpci_eeprom_parse_mac
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
suffix:semicolon
macro_line|#endif
eof
