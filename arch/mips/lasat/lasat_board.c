multiline_comment|/*&n; * lasat_board.c&n; *&n; * Thomas Horsten &lt;thh@lasat.com&gt;&n; * Copyright (C) 2000 LASAT Networks A/S.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Routines specific to the LASAT boards&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;asm/lasat/lasat.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &quot;at93c.h&quot;
multiline_comment|/* New model description table */
macro_line|#include &quot;lasat_models.h&quot;
DECL|macro|EEPROM_CRC
mdefine_line|#define EEPROM_CRC(data, len) (~0 ^ crc32(~0, data, len))
DECL|variable|lasat_board_info
r_struct
id|lasat_info
id|lasat_board_info
suffix:semicolon
r_void
id|update_bcastaddr
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|EEPROMRead
r_int
id|EEPROMRead
c_func
(paren
r_int
r_int
id|pos
comma
r_int
r_char
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_int
id|i
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
op_star
id|data
op_increment
op_assign
id|at93c_read
c_func
(paren
id|pos
op_increment
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|EEPROMWrite
r_int
id|EEPROMWrite
c_func
(paren
r_int
r_int
id|pos
comma
r_int
r_char
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_int
id|i
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
id|at93c_write
c_func
(paren
id|pos
op_increment
comma
op_star
id|data
op_increment
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_flash_sizes
r_static
r_void
id|init_flash_sizes
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|lb
op_assign
id|lasat_board_info.li_flashpart_base
suffix:semicolon
r_int
r_int
op_star
id|ls
op_assign
id|lasat_board_info.li_flashpart_size
suffix:semicolon
id|ls
(braket
id|LASAT_MTD_BOOTLOADER
)braket
op_assign
l_int|0x40000
suffix:semicolon
id|ls
(braket
id|LASAT_MTD_SERVICE
)braket
op_assign
l_int|0xC0000
suffix:semicolon
id|ls
(braket
id|LASAT_MTD_NORMAL
)braket
op_assign
l_int|0x100000
suffix:semicolon
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_LASAT_100
)paren
(brace
id|lasat_board_info.li_flash_base
op_assign
l_int|0x1e000000
suffix:semicolon
id|lb
(braket
id|LASAT_MTD_BOOTLOADER
)braket
op_assign
l_int|0x1e400000
suffix:semicolon
r_if
c_cond
(paren
id|lasat_board_info.li_flash_size
OG
l_int|0x200000
)paren
(brace
id|ls
(braket
id|LASAT_MTD_CONFIG
)braket
op_assign
l_int|0x100000
suffix:semicolon
id|ls
(braket
id|LASAT_MTD_FS
)braket
op_assign
l_int|0x500000
suffix:semicolon
)brace
)brace
r_else
(brace
id|lasat_board_info.li_flash_base
op_assign
l_int|0x10000000
suffix:semicolon
r_if
c_cond
(paren
id|lasat_board_info.li_flash_size
OL
l_int|0x1000000
)paren
(brace
id|lb
(braket
id|LASAT_MTD_BOOTLOADER
)braket
op_assign
l_int|0x10000000
suffix:semicolon
id|ls
(braket
id|LASAT_MTD_CONFIG
)braket
op_assign
l_int|0x100000
suffix:semicolon
r_if
c_cond
(paren
id|lasat_board_info.li_flash_size
op_ge
l_int|0x400000
)paren
(brace
id|ls
(braket
id|LASAT_MTD_FS
)braket
op_assign
id|lasat_board_info.li_flash_size
op_minus
l_int|0x300000
suffix:semicolon
)brace
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|LASAT_MTD_LAST
suffix:semicolon
id|i
op_increment
)paren
id|lb
(braket
id|i
)braket
op_assign
id|lb
(braket
id|i
op_minus
l_int|1
)braket
op_plus
id|ls
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|lasat_init_board_info
r_int
id|lasat_init_board_info
c_func
(paren
r_void
)paren
(brace
r_int
id|c
suffix:semicolon
r_int
r_int
id|crc
suffix:semicolon
r_int
r_int
id|cfg0
comma
id|cfg1
suffix:semicolon
r_const
id|product_info_t
op_star
id|ppi
suffix:semicolon
r_int
id|i_n_base_models
op_assign
id|N_BASE_MODELS
suffix:semicolon
r_const
r_char
op_star
r_const
op_star
id|i_txt_base_models
op_assign
id|txt_base_models
suffix:semicolon
r_int
id|i_n_prids
op_assign
id|N_PRIDS
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|lasat_board_info
comma
l_int|0
comma
r_sizeof
(paren
id|lasat_board_info
)paren
)paren
suffix:semicolon
multiline_comment|/* First read the EEPROM info */
id|EEPROMRead
c_func
(paren
l_int|0
comma
(paren
r_int
r_char
op_star
)paren
op_amp
id|lasat_board_info.li_eeprom_info
comma
r_sizeof
(paren
r_struct
id|lasat_eeprom_struct
)paren
)paren
suffix:semicolon
multiline_comment|/* Check the CRC */
id|crc
op_assign
id|EEPROM_CRC
c_func
(paren
(paren
r_int
r_char
op_star
)paren
(paren
op_amp
id|lasat_board_info.li_eeprom_info
)paren
comma
r_sizeof
(paren
r_struct
id|lasat_eeprom_struct
)paren
op_minus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crc
op_ne
id|lasat_board_info.li_eeprom_info.crc32
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;WARNING...&bslash;nWARNING...&bslash;nEEPROM CRC does not match calculated, attempting to soldier on...&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lasat_board_info.li_eeprom_info.version
op_ne
id|LASAT_EEPROM_VERSION
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;WARNING...&bslash;nWARNING...&bslash;nEEPROM version %d, wanted version %d, attempting to soldier on...&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|lasat_board_info.li_eeprom_info.version
comma
id|LASAT_EEPROM_VERSION
)paren
suffix:semicolon
)brace
id|cfg0
op_assign
id|lasat_board_info.li_eeprom_info.cfg
(braket
l_int|0
)braket
suffix:semicolon
id|cfg1
op_assign
id|lasat_board_info.li_eeprom_info.cfg
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|LASAT_W0_DSCTYPE
c_func
(paren
id|cfg0
)paren
op_ne
l_int|1
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;WARNING...&bslash;nWARNING...&bslash;nInvalid configuration read from EEPROM, attempting to soldier on...&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* We have a valid configuration */
r_switch
c_cond
(paren
id|LASAT_W0_SDRAMBANKSZ
c_func
(paren
id|cfg0
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|lasat_board_info.li_memsize
op_assign
l_int|0x0800000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|lasat_board_info.li_memsize
op_assign
l_int|0x1000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|lasat_board_info.li_memsize
op_assign
l_int|0x2000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|lasat_board_info.li_memsize
op_assign
l_int|0x4000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|lasat_board_info.li_memsize
op_assign
l_int|0x8000000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|lasat_board_info.li_memsize
op_assign
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|LASAT_W0_SDRAMBANKS
c_func
(paren
id|cfg0
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|lasat_board_info.li_memsize
op_mul_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|LASAT_W0_BUSSPEED
c_func
(paren
id|cfg0
)paren
)paren
(brace
r_case
l_int|0x0
suffix:colon
id|lasat_board_info.li_bus_hz
op_assign
l_int|60000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1
suffix:colon
id|lasat_board_info.li_bus_hz
op_assign
l_int|66000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2
suffix:colon
id|lasat_board_info.li_bus_hz
op_assign
l_int|66666667
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3
suffix:colon
id|lasat_board_info.li_bus_hz
op_assign
l_int|80000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
id|lasat_board_info.li_bus_hz
op_assign
l_int|83333333
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x5
suffix:colon
id|lasat_board_info.li_bus_hz
op_assign
l_int|100000000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|LASAT_W0_CPUCLK
c_func
(paren
id|cfg0
)paren
)paren
(brace
r_case
l_int|0x0
suffix:colon
id|lasat_board_info.li_cpu_hz
op_assign
id|lasat_board_info.li_bus_hz
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1
suffix:colon
id|lasat_board_info.li_cpu_hz
op_assign
id|lasat_board_info.li_bus_hz
op_plus
(paren
id|lasat_board_info.li_bus_hz
op_rshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2
suffix:colon
id|lasat_board_info.li_cpu_hz
op_assign
id|lasat_board_info.li_bus_hz
op_plus
id|lasat_board_info.li_bus_hz
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3
suffix:colon
id|lasat_board_info.li_cpu_hz
op_assign
id|lasat_board_info.li_bus_hz
op_plus
id|lasat_board_info.li_bus_hz
op_plus
(paren
id|lasat_board_info.li_bus_hz
op_rshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
id|lasat_board_info.li_cpu_hz
op_assign
id|lasat_board_info.li_bus_hz
op_plus
id|lasat_board_info.li_bus_hz
op_plus
id|lasat_board_info.li_bus_hz
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Flash size */
r_switch
c_cond
(paren
id|LASAT_W1_FLASHSIZE
c_func
(paren
id|cfg1
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|lasat_board_info.li_flash_size
op_assign
l_int|0x200000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|lasat_board_info.li_flash_size
op_assign
l_int|0x400000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|lasat_board_info.li_flash_size
op_assign
l_int|0x800000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|lasat_board_info.li_flash_size
op_assign
l_int|0x1000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|lasat_board_info.li_flash_size
op_assign
l_int|0x2000000
suffix:semicolon
r_break
suffix:semicolon
)brace
id|init_flash_sizes
c_func
(paren
)paren
suffix:semicolon
id|lasat_board_info.li_bmid
op_assign
id|LASAT_W0_BMID
c_func
(paren
id|cfg0
)paren
suffix:semicolon
id|lasat_board_info.li_prid
op_assign
id|lasat_board_info.li_eeprom_info.prid
suffix:semicolon
r_if
c_cond
(paren
id|lasat_board_info.li_prid
op_eq
l_int|0xffff
op_logical_or
id|lasat_board_info.li_prid
op_eq
l_int|0
)paren
id|lasat_board_info.li_prid
op_assign
id|lasat_board_info.li_bmid
suffix:semicolon
multiline_comment|/* Base model stuff */
r_if
c_cond
(paren
id|lasat_board_info.li_bmid
OG
id|i_n_base_models
)paren
id|lasat_board_info.li_bmid
op_assign
id|i_n_base_models
suffix:semicolon
id|strcpy
c_func
(paren
id|lasat_board_info.li_bmstr
comma
id|i_txt_base_models
(braket
id|lasat_board_info.li_bmid
)braket
)paren
suffix:semicolon
multiline_comment|/* Product ID dependent values */
id|c
op_assign
id|lasat_board_info.li_prid
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
id|i_n_prids
)paren
(brace
id|strcpy
c_func
(paren
id|lasat_board_info.li_namestr
comma
l_string|&quot;Unknown Model&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|lasat_board_info.li_typestr
comma
l_string|&quot;Unknown Type&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|ppi
op_assign
op_amp
id|vendor_info_table
(braket
l_int|0
)braket
dot
id|vi_product_info
(braket
id|c
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|lasat_board_info.li_namestr
comma
id|ppi-&gt;pi_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppi-&gt;pi_type
)paren
id|strcpy
c_func
(paren
id|lasat_board_info.li_typestr
comma
id|ppi-&gt;pi_type
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|lasat_board_info.li_typestr
comma
l_string|&quot;%d&quot;
comma
l_int|10
op_star
id|c
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_INET) &amp;&amp; defined(CONFIG_SYSCTL)
id|update_bcastaddr
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lasat_write_eeprom_info
r_void
id|lasat_write_eeprom_info
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|crc
suffix:semicolon
multiline_comment|/* Generate the CRC */
id|crc
op_assign
id|EEPROM_CRC
c_func
(paren
(paren
r_int
r_char
op_star
)paren
(paren
op_amp
id|lasat_board_info.li_eeprom_info
)paren
comma
r_sizeof
(paren
r_struct
id|lasat_eeprom_struct
)paren
op_minus
l_int|4
)paren
suffix:semicolon
id|lasat_board_info.li_eeprom_info.crc32
op_assign
id|crc
suffix:semicolon
multiline_comment|/* Write the EEPROM info */
id|EEPROMWrite
c_func
(paren
l_int|0
comma
(paren
r_int
r_char
op_star
)paren
op_amp
id|lasat_board_info.li_eeprom_info
comma
r_sizeof
(paren
r_struct
id|lasat_eeprom_struct
)paren
)paren
suffix:semicolon
)brace
eof
