multiline_comment|/*&n; * lasat.h&n; *&n; * Thomas Horsten &lt;thh@lasat.com&gt;&n; * Copyright (C) 2000 LASAT Networks A/S.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Configuration for LASAT boards, loads the appropriate include files.&n; */
macro_line|#ifndef _LASAT_H
DECL|macro|_LASAT_H
mdefine_line|#define _LASAT_H
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|struct|lasat_misc
r_extern
r_struct
id|lasat_misc
(brace
DECL|member|reset_reg
r_volatile
id|u32
op_star
id|reset_reg
suffix:semicolon
DECL|member|flash_wp_reg
r_volatile
id|u32
op_star
id|flash_wp_reg
suffix:semicolon
DECL|member|flash_wp_bit
id|u32
id|flash_wp_bit
suffix:semicolon
)brace
op_star
id|lasat_misc
suffix:semicolon
DECL|enum|lasat_mtdparts
r_enum
id|lasat_mtdparts
(brace
DECL|enumerator|LASAT_MTD_BOOTLOADER
id|LASAT_MTD_BOOTLOADER
comma
DECL|enumerator|LASAT_MTD_SERVICE
id|LASAT_MTD_SERVICE
comma
DECL|enumerator|LASAT_MTD_NORMAL
id|LASAT_MTD_NORMAL
comma
DECL|enumerator|LASAT_MTD_CONFIG
id|LASAT_MTD_CONFIG
comma
DECL|enumerator|LASAT_MTD_FS
id|LASAT_MTD_FS
comma
DECL|enumerator|LASAT_MTD_LAST
id|LASAT_MTD_LAST
)brace
suffix:semicolon
multiline_comment|/*&n; * The format of the data record in the EEPROM.&n; * See Documentation/LASAT/eeprom.txt for a detailed description&n; * of the fields in this struct, and the LASAT Hardware Configuration&n; * field specification for a detailed description of the config&n; * field.&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|LASAT_EEPROM_VERSION
mdefine_line|#define LASAT_EEPROM_VERSION 7
DECL|struct|lasat_eeprom_struct
r_struct
id|lasat_eeprom_struct
(brace
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|cfg
r_int
r_int
id|cfg
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|hwaddr
r_int
r_char
id|hwaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|print_partno
r_int
r_char
id|print_partno
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|term0
r_int
r_char
id|term0
suffix:semicolon
DECL|member|print_serial
r_int
r_char
id|print_serial
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|term1
r_int
r_char
id|term1
suffix:semicolon
DECL|member|prod_partno
r_int
r_char
id|prod_partno
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|term2
r_int
r_char
id|term2
suffix:semicolon
DECL|member|prod_serial
r_int
r_char
id|prod_serial
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|term3
r_int
r_char
id|term3
suffix:semicolon
DECL|member|passwd_hash
r_int
r_char
id|passwd_hash
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pwdnull
r_int
r_char
id|pwdnull
suffix:semicolon
DECL|member|vendid
r_int
r_char
id|vendid
suffix:semicolon
DECL|member|ts_ref
r_int
r_char
id|ts_ref
suffix:semicolon
DECL|member|ts_signoff
r_int
r_char
id|ts_signoff
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|debugaccess
r_int
r_char
id|debugaccess
suffix:semicolon
DECL|member|prid
r_int
r_int
id|prid
suffix:semicolon
DECL|member|serviceflag
r_int
r_int
id|serviceflag
suffix:semicolon
DECL|member|ipaddr
r_int
r_int
id|ipaddr
suffix:semicolon
DECL|member|netmask
r_int
r_int
id|netmask
suffix:semicolon
DECL|member|crc32
r_int
r_int
id|crc32
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lasat_eeprom_struct_pre7
r_struct
id|lasat_eeprom_struct_pre7
(brace
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|hwaddr0
r_int
r_char
id|hwaddr0
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|hwaddr1
r_int
r_char
id|hwaddr1
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|print_partno
r_int
r_char
id|print_partno
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|term0
r_int
r_char
id|term0
suffix:semicolon
DECL|member|print_serial
r_int
r_char
id|print_serial
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|term1
r_int
r_char
id|term1
suffix:semicolon
DECL|member|prod_partno
r_int
r_char
id|prod_partno
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|term2
r_int
r_char
id|term2
suffix:semicolon
DECL|member|prod_serial
r_int
r_char
id|prod_serial
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|term3
r_int
r_char
id|term3
suffix:semicolon
DECL|member|passwd_hash
r_int
r_char
id|passwd_hash
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|pwdnull
r_int
r_char
id|pwdnull
suffix:semicolon
DECL|member|vendor
r_int
r_char
id|vendor
suffix:semicolon
DECL|member|ts_ref
r_int
r_char
id|ts_ref
suffix:semicolon
DECL|member|ts_signoff
r_int
r_char
id|ts_signoff
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|writecount
r_int
r_int
id|writecount
suffix:semicolon
DECL|member|ipaddr
r_int
r_int
id|ipaddr
suffix:semicolon
DECL|member|netmask
r_int
r_int
id|netmask
suffix:semicolon
DECL|member|crc32
r_int
r_int
id|crc32
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Configuration descriptor encoding - see the doc for details */
DECL|macro|LASAT_W0_DSCTYPE
mdefine_line|#define LASAT_W0_DSCTYPE(v)&t;&t;( ( (v)         ) &amp; 0xf )
DECL|macro|LASAT_W0_BMID
mdefine_line|#define LASAT_W0_BMID(v)&t;&t;( ( (v) &gt;&gt; 0x04 ) &amp; 0xf )
DECL|macro|LASAT_W0_CPUTYPE
mdefine_line|#define LASAT_W0_CPUTYPE(v)&t;&t;( ( (v) &gt;&gt; 0x08 ) &amp; 0xf )
DECL|macro|LASAT_W0_BUSSPEED
mdefine_line|#define LASAT_W0_BUSSPEED(v)&t;&t;( ( (v) &gt;&gt; 0x0c ) &amp; 0xf )
DECL|macro|LASAT_W0_CPUCLK
mdefine_line|#define LASAT_W0_CPUCLK(v)&t;&t;( ( (v) &gt;&gt; 0x10 ) &amp; 0xf )
DECL|macro|LASAT_W0_SDRAMBANKSZ
mdefine_line|#define LASAT_W0_SDRAMBANKSZ(v)&t;&t;( ( (v) &gt;&gt; 0x14 ) &amp; 0xf )
DECL|macro|LASAT_W0_SDRAMBANKS
mdefine_line|#define LASAT_W0_SDRAMBANKS(v)&t;&t;( ( (v) &gt;&gt; 0x18 ) &amp; 0xf )
DECL|macro|LASAT_W0_L2CACHE
mdefine_line|#define LASAT_W0_L2CACHE(v)&t;&t;( ( (v) &gt;&gt; 0x1c ) &amp; 0xf )
DECL|macro|LASAT_W1_EDHAC
mdefine_line|#define LASAT_W1_EDHAC(v)&t;&t;( ( (v)         ) &amp; 0xf )
DECL|macro|LASAT_W1_HIFN
mdefine_line|#define LASAT_W1_HIFN(v)&t;&t;( ( (v) &gt;&gt; 0x04 ) &amp; 0x1 )
DECL|macro|LASAT_W1_ISDN
mdefine_line|#define LASAT_W1_ISDN(v)&t;&t;( ( (v) &gt;&gt; 0x05 ) &amp; 0x1 )
DECL|macro|LASAT_W1_IDE
mdefine_line|#define LASAT_W1_IDE(v)&t;&t;&t;( ( (v) &gt;&gt; 0x06 ) &amp; 0x1 )
DECL|macro|LASAT_W1_HDLC
mdefine_line|#define LASAT_W1_HDLC(v)&t;&t;( ( (v) &gt;&gt; 0x07 ) &amp; 0x1 )
DECL|macro|LASAT_W1_USVERSION
mdefine_line|#define LASAT_W1_USVERSION(v)&t;&t;( ( (v) &gt;&gt; 0x08 ) &amp; 0x1 )
DECL|macro|LASAT_W1_4MACS
mdefine_line|#define LASAT_W1_4MACS(v)&t;&t;( ( (v) &gt;&gt; 0x09 ) &amp; 0x1 )
DECL|macro|LASAT_W1_EXTSERIAL
mdefine_line|#define LASAT_W1_EXTSERIAL(v)&t;&t;( ( (v) &gt;&gt; 0x0a ) &amp; 0x1 )
DECL|macro|LASAT_W1_FLASHSIZE
mdefine_line|#define LASAT_W1_FLASHSIZE(v)&t;&t;( ( (v) &gt;&gt; 0x0c ) &amp; 0xf )
DECL|macro|LASAT_W1_PCISLOTS
mdefine_line|#define LASAT_W1_PCISLOTS(v)&t;&t;( ( (v) &gt;&gt; 0x10 ) &amp; 0xf )
DECL|macro|LASAT_W1_PCI1OPT
mdefine_line|#define LASAT_W1_PCI1OPT(v)&t;&t;( ( (v) &gt;&gt; 0x14 ) &amp; 0xf )
DECL|macro|LASAT_W1_PCI2OPT
mdefine_line|#define LASAT_W1_PCI2OPT(v)&t;&t;( ( (v) &gt;&gt; 0x18 ) &amp; 0xf )
DECL|macro|LASAT_W1_PCI3OPT
mdefine_line|#define LASAT_W1_PCI3OPT(v)&t;&t;( ( (v) &gt;&gt; 0x1c ) &amp; 0xf )
multiline_comment|/* Routines specific to LASAT boards */
DECL|macro|LASAT_BMID_MASQUERADE2
mdefine_line|#define LASAT_BMID_MASQUERADE2&t;&t;0
DECL|macro|LASAT_BMID_MASQUERADEPRO
mdefine_line|#define LASAT_BMID_MASQUERADEPRO&t;1
DECL|macro|LASAT_BMID_SAFEPIPE25
mdefine_line|#define LASAT_BMID_SAFEPIPE25&t;&t;&t;2
DECL|macro|LASAT_BMID_SAFEPIPE50
mdefine_line|#define LASAT_BMID_SAFEPIPE50&t;&t;&t;3
DECL|macro|LASAT_BMID_SAFEPIPE100
mdefine_line|#define LASAT_BMID_SAFEPIPE100&t;&t;4
DECL|macro|LASAT_BMID_SAFEPIPE5000
mdefine_line|#define LASAT_BMID_SAFEPIPE5000&t;&t;5
DECL|macro|LASAT_BMID_SAFEPIPE7000
mdefine_line|#define LASAT_BMID_SAFEPIPE7000&t;&t;6
DECL|macro|LASAT_BMID_SAFEPIPE1000
mdefine_line|#define LASAT_BMID_SAFEPIPE1000&t;&t;7
singleline_comment|//#define LASAT_BMID_SAFEPIPE30&t;&t;7
singleline_comment|//#define LASAT_BMID_SAFEPIPE5100&t;8
singleline_comment|//#define LASAT_BMID_SAFEPIPE7100&t;9
DECL|macro|LASAT_BMID_UNKNOWN
mdefine_line|#define LASAT_BMID_UNKNOWN&t;&t;&t;&t;0xf
DECL|macro|LASAT_MAX_BMID_NAMES
mdefine_line|#define LASAT_MAX_BMID_NAMES&t;&t;&t;9   
singleline_comment|// no larger than 15!
DECL|macro|LASAT_HAS_EDHAC
mdefine_line|#define LASAT_HAS_EDHAC&t;&t;&t;( 1 &lt;&lt; 0 )
DECL|macro|LASAT_EDHAC_FAST
mdefine_line|#define LASAT_EDHAC_FAST&t;&t;( 1 &lt;&lt; 1 )
DECL|macro|LASAT_HAS_EADI
mdefine_line|#define LASAT_HAS_EADI&t;&t;&t;( 1 &lt;&lt; 2 )
DECL|macro|LASAT_HAS_HIFN
mdefine_line|#define LASAT_HAS_HIFN&t;&t;&t;( 1 &lt;&lt; 3 )
DECL|macro|LASAT_HAS_ISDN
mdefine_line|#define LASAT_HAS_ISDN&t;&t;&t;( 1 &lt;&lt; 4 )
DECL|macro|LASAT_HAS_LEASEDLINE_IF
mdefine_line|#define LASAT_HAS_LEASEDLINE_IF&t;&t;( 1 &lt;&lt; 5 )
DECL|macro|LASAT_HAS_HDC
mdefine_line|#define LASAT_HAS_HDC&t;&t;&t;( 1 &lt;&lt; 6 )
DECL|macro|LASAT_PRID_MASQUERADE2
mdefine_line|#define LASAT_PRID_MASQUERADE2&t;&t;0
DECL|macro|LASAT_PRID_MASQUERADEPRO
mdefine_line|#define LASAT_PRID_MASQUERADEPRO&t;1
DECL|macro|LASAT_PRID_SAFEPIPE25
mdefine_line|#define LASAT_PRID_SAFEPIPE25&t;&t;&t;2
DECL|macro|LASAT_PRID_SAFEPIPE50
mdefine_line|#define LASAT_PRID_SAFEPIPE50&t;&t;&t;3
DECL|macro|LASAT_PRID_SAFEPIPE100
mdefine_line|#define LASAT_PRID_SAFEPIPE100&t;&t;4
DECL|macro|LASAT_PRID_SAFEPIPE5000
mdefine_line|#define LASAT_PRID_SAFEPIPE5000&t;&t;5
DECL|macro|LASAT_PRID_SAFEPIPE7000
mdefine_line|#define LASAT_PRID_SAFEPIPE7000&t;&t;6
DECL|macro|LASAT_PRID_SAFEPIPE30
mdefine_line|#define LASAT_PRID_SAFEPIPE30&t;&t;&t;7
DECL|macro|LASAT_PRID_SAFEPIPE5100
mdefine_line|#define LASAT_PRID_SAFEPIPE5100&t;&t;8
DECL|macro|LASAT_PRID_SAFEPIPE7100
mdefine_line|#define LASAT_PRID_SAFEPIPE7100&t;&t;9
DECL|macro|LASAT_PRID_SAFEPIPE1110
mdefine_line|#define LASAT_PRID_SAFEPIPE1110&t;&t;10
DECL|macro|LASAT_PRID_SAFEPIPE3020
mdefine_line|#define LASAT_PRID_SAFEPIPE3020&t;&t;11
DECL|macro|LASAT_PRID_SAFEPIPE3030
mdefine_line|#define LASAT_PRID_SAFEPIPE3030&t;&t;12
DECL|macro|LASAT_PRID_SAFEPIPE5020
mdefine_line|#define LASAT_PRID_SAFEPIPE5020&t;&t;13
DECL|macro|LASAT_PRID_SAFEPIPE5030
mdefine_line|#define LASAT_PRID_SAFEPIPE5030&t;&t;14
DECL|macro|LASAT_PRID_SAFEPIPE1120
mdefine_line|#define LASAT_PRID_SAFEPIPE1120&t;&t;15
DECL|macro|LASAT_PRID_SAFEPIPE1130
mdefine_line|#define LASAT_PRID_SAFEPIPE1130&t;&t;16
DECL|macro|LASAT_PRID_SAFEPIPE6010
mdefine_line|#define LASAT_PRID_SAFEPIPE6010&t;&t;17
DECL|macro|LASAT_PRID_SAFEPIPE6110
mdefine_line|#define LASAT_PRID_SAFEPIPE6110&t;&t;18
DECL|macro|LASAT_PRID_SAFEPIPE6210
mdefine_line|#define LASAT_PRID_SAFEPIPE6210&t;&t;19
DECL|macro|LASAT_PRID_SAFEPIPE1020
mdefine_line|#define LASAT_PRID_SAFEPIPE1020&t;&t;20
DECL|macro|LASAT_PRID_SAFEPIPE1040
mdefine_line|#define LASAT_PRID_SAFEPIPE1040&t;&t;21
DECL|macro|LASAT_PRID_SAFEPIPE1060
mdefine_line|#define LASAT_PRID_SAFEPIPE1060&t;&t;22
DECL|struct|lasat_info
r_struct
id|lasat_info
(brace
DECL|member|li_cpu_hz
r_int
r_int
id|li_cpu_hz
suffix:semicolon
DECL|member|li_bus_hz
r_int
r_int
id|li_bus_hz
suffix:semicolon
DECL|member|li_bmid
r_int
r_int
id|li_bmid
suffix:semicolon
DECL|member|li_memsize
r_int
r_int
id|li_memsize
suffix:semicolon
DECL|member|li_flash_size
r_int
r_int
id|li_flash_size
suffix:semicolon
DECL|member|li_prid
r_int
r_int
id|li_prid
suffix:semicolon
DECL|member|li_bmstr
r_int
r_char
id|li_bmstr
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|li_namestr
r_int
r_char
id|li_namestr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|li_typestr
r_int
r_char
id|li_typestr
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Info on the Flash layout */
DECL|member|li_flash_base
r_int
r_int
id|li_flash_base
suffix:semicolon
DECL|member|li_flashpart_base
r_int
r_int
id|li_flashpart_base
(braket
id|LASAT_MTD_LAST
)braket
suffix:semicolon
DECL|member|li_flashpart_size
r_int
r_int
id|li_flashpart_size
(braket
id|LASAT_MTD_LAST
)braket
suffix:semicolon
DECL|member|li_eeprom_info
r_struct
id|lasat_eeprom_struct
id|li_eeprom_info
suffix:semicolon
DECL|member|li_eeprom_upgrade_version
r_int
r_int
id|li_eeprom_upgrade_version
suffix:semicolon
DECL|member|li_debugaccess
r_int
r_int
id|li_debugaccess
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|lasat_info
id|lasat_board_info
suffix:semicolon
DECL|function|lasat_flash_partition_start
r_static
r_inline
r_int
r_int
id|lasat_flash_partition_start
c_func
(paren
r_int
id|partno
)paren
(brace
r_if
c_cond
(paren
id|partno
OL
l_int|0
op_logical_or
id|partno
op_ge
id|LASAT_MTD_LAST
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|lasat_board_info.li_flashpart_base
(braket
id|partno
)braket
suffix:semicolon
)brace
DECL|function|lasat_flash_partition_size
r_static
r_inline
r_int
r_int
id|lasat_flash_partition_size
c_func
(paren
r_int
id|partno
)paren
(brace
r_if
c_cond
(paren
id|partno
OL
l_int|0
op_logical_or
id|partno
op_ge
id|LASAT_MTD_LAST
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|lasat_board_info.li_flashpart_size
(braket
id|partno
)braket
suffix:semicolon
)brace
multiline_comment|/* Called from setup() to initialize the global board_info struct */
r_extern
r_int
id|lasat_init_board_info
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Write the modified EEPROM info struct */
r_extern
r_void
id|lasat_write_eeprom_info
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|N_MACHTYPES
mdefine_line|#define N_MACHTYPES&t;&t;2
multiline_comment|/* for calibration of delays */
macro_line|#include &lt;asm/delay.h&gt;
r_extern
r_void
(paren
op_star
id|prom_printf
)paren
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
DECL|macro|LASAT_SERVICEMODE_MAGIC_1
mdefine_line|#define LASAT_SERVICEMODE_MAGIC_1     0xdeadbeef
DECL|macro|LASAT_SERVICEMODE_MAGIC_2
mdefine_line|#define LASAT_SERVICEMODE_MAGIC_2     0xfedeabba
multiline_comment|/* Lasat 100 boards */
DECL|macro|LASAT_GT_BASE
mdefine_line|#define LASAT_GT_BASE           (KSEG1ADDR(0x14000000))
multiline_comment|/* Lasat 200 boards */
DECL|macro|Vrc5074_PHYS_BASE
mdefine_line|#define Vrc5074_PHYS_BASE       0x1fa00000
DECL|macro|Vrc5074_BASE
mdefine_line|#define Vrc5074_BASE            (KSEG1ADDR(Vrc5074_PHYS_BASE))
DECL|macro|PCI_WINDOW1
mdefine_line|#define PCI_WINDOW1             0x1a000000
macro_line|#endif /* _LASAT_H */
eof
