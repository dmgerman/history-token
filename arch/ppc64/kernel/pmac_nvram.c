multiline_comment|/*&n; *  c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * Miscellaneous procedures for dealing with the PowerMac hardware.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
multiline_comment|/*&n; * Read and write the non-volatile RAM on PowerMacs and CHRP machines.&n; */
DECL|variable|nvram_naddrs
r_static
r_int
id|nvram_naddrs
suffix:semicolon
DECL|variable|nvram_addr
r_static
r_volatile
r_int
r_char
op_star
id|nvram_addr
suffix:semicolon
DECL|variable|nvram_data
r_static
r_volatile
r_int
r_char
op_star
id|nvram_data
suffix:semicolon
DECL|variable|nvram_mult
DECL|variable|is_core_99
r_static
r_int
id|nvram_mult
comma
id|is_core_99
suffix:semicolon
DECL|variable|nvram_image
r_static
r_char
op_star
id|nvram_image
suffix:semicolon
DECL|variable|core99_bank
r_static
r_int
id|core99_bank
op_assign
l_int|0
suffix:semicolon
DECL|variable|sys_ctrler
id|sys_ctrler_t
id|sys_ctrler
op_assign
id|SYS_CTRLER_UNKNOWN
suffix:semicolon
DECL|macro|NVRAM_SIZE
mdefine_line|#define NVRAM_SIZE&t;&t;0x2000&t;/* 8kB of non-volatile RAM */
DECL|macro|CORE99_SIGNATURE
mdefine_line|#define CORE99_SIGNATURE&t;0x5a
DECL|macro|CORE99_ADLER_START
mdefine_line|#define CORE99_ADLER_START&t;0x14
multiline_comment|/* Core99 nvram is a flash */
DECL|macro|CORE99_FLASH_STATUS_DONE
mdefine_line|#define CORE99_FLASH_STATUS_DONE&t;0x80
DECL|macro|CORE99_FLASH_STATUS_ERR
mdefine_line|#define CORE99_FLASH_STATUS_ERR&t;&t;0x38
DECL|macro|CORE99_FLASH_CMD_ERASE_CONFIRM
mdefine_line|#define CORE99_FLASH_CMD_ERASE_CONFIRM&t;0xd0
DECL|macro|CORE99_FLASH_CMD_ERASE_SETUP
mdefine_line|#define CORE99_FLASH_CMD_ERASE_SETUP&t;0x20
DECL|macro|CORE99_FLASH_CMD_RESET
mdefine_line|#define CORE99_FLASH_CMD_RESET&t;&t;0xff
DECL|macro|CORE99_FLASH_CMD_WRITE_SETUP
mdefine_line|#define CORE99_FLASH_CMD_WRITE_SETUP&t;0x40
multiline_comment|/* CHRP NVRAM header */
DECL|struct|chrp_header
r_struct
id|chrp_header
(brace
DECL|member|signature
id|u8
id|signature
suffix:semicolon
DECL|member|cksum
id|u8
id|cksum
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|core99_header
r_struct
id|core99_header
(brace
DECL|member|hdr
r_struct
id|chrp_header
id|hdr
suffix:semicolon
DECL|member|adler
id|u32
id|adler
suffix:semicolon
DECL|member|generation
id|u32
id|generation
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|nvram_partitions
r_static
r_int
id|nvram_partitions
(braket
l_int|3
)braket
suffix:semicolon
r_static
id|u8
DECL|function|chrp_checksum
id|chrp_checksum
c_func
(paren
r_struct
id|chrp_header
op_star
id|hdr
)paren
(brace
id|u8
op_star
id|ptr
suffix:semicolon
id|u16
id|sum
op_assign
id|hdr-&gt;signature
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|hdr-&gt;len
suffix:semicolon
id|ptr
OL
id|hdr-&gt;data
suffix:semicolon
id|ptr
op_increment
)paren
id|sum
op_add_assign
op_star
id|ptr
suffix:semicolon
r_while
c_loop
(paren
id|sum
OG
l_int|0xFF
)paren
id|sum
op_assign
(paren
id|sum
op_amp
l_int|0xFF
)paren
op_plus
(paren
id|sum
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_static
id|u32
DECL|function|core99_calc_adler
id|core99_calc_adler
c_func
(paren
id|u8
op_star
id|buffer
)paren
(brace
r_int
id|cnt
suffix:semicolon
id|u32
id|low
comma
id|high
suffix:semicolon
id|buffer
op_add_assign
id|CORE99_ADLER_START
suffix:semicolon
id|low
op_assign
l_int|1
suffix:semicolon
id|high
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
(paren
id|NVRAM_SIZE
op_minus
id|CORE99_ADLER_START
)paren
suffix:semicolon
id|cnt
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|cnt
op_mod
l_int|5000
)paren
op_eq
l_int|0
)paren
(brace
id|high
op_mod_assign
l_int|65521UL
suffix:semicolon
id|high
op_mod_assign
l_int|65521UL
suffix:semicolon
)brace
id|low
op_add_assign
id|buffer
(braket
id|cnt
)braket
suffix:semicolon
id|high
op_add_assign
id|low
suffix:semicolon
)brace
id|low
op_mod_assign
l_int|65521UL
suffix:semicolon
id|high
op_mod_assign
l_int|65521UL
suffix:semicolon
r_return
(paren
id|high
op_lshift
l_int|16
)paren
op_or
id|low
suffix:semicolon
)brace
r_static
id|u32
DECL|function|core99_check
id|core99_check
c_func
(paren
id|u8
op_star
id|datas
)paren
(brace
r_struct
id|core99_header
op_star
id|hdr99
op_assign
(paren
r_struct
id|core99_header
op_star
)paren
id|datas
suffix:semicolon
r_if
c_cond
(paren
id|hdr99-&gt;hdr.signature
op_ne
id|CORE99_SIGNATURE
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Invalid signature&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;&t;
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr99-&gt;hdr.cksum
op_ne
id|chrp_checksum
c_func
(paren
op_amp
id|hdr99-&gt;hdr
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Invalid checksum&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr99-&gt;adler
op_ne
id|core99_calc_adler
c_func
(paren
id|datas
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Invalid adler&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|hdr99-&gt;generation
suffix:semicolon
)brace
r_static
r_int
DECL|function|core99_erase_bank
id|core99_erase_bank
c_func
(paren
r_int
id|bank
)paren
(brace
r_int
id|stat
comma
id|i
suffix:semicolon
id|u8
op_star
id|base
op_assign
(paren
id|u8
op_star
)paren
id|nvram_data
op_plus
id|core99_bank
op_star
id|NVRAM_SIZE
suffix:semicolon
id|out_8
c_func
(paren
id|base
comma
id|CORE99_FLASH_CMD_ERASE_SETUP
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|base
comma
id|CORE99_FLASH_CMD_ERASE_CONFIRM
)paren
suffix:semicolon
r_do
(brace
id|stat
op_assign
id|in_8
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|stat
op_amp
id|CORE99_FLASH_STATUS_DONE
)paren
)paren
(brace
suffix:semicolon
)brace
id|out_8
c_func
(paren
id|base
comma
id|CORE99_FLASH_CMD_RESET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|CORE99_FLASH_STATUS_ERR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nvram: flash error 0x%02x on erase !&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NVRAM_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|base
(braket
id|i
)braket
op_ne
l_int|0xff
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nvram: flash erase failed !&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|core99_write_bank
id|core99_write_bank
c_func
(paren
r_int
id|bank
comma
id|u8
op_star
id|datas
)paren
(brace
r_int
id|i
comma
id|stat
op_assign
l_int|0
suffix:semicolon
id|u8
op_star
id|base
op_assign
(paren
id|u8
op_star
)paren
id|nvram_data
op_plus
id|core99_bank
op_star
id|NVRAM_SIZE
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
id|NVRAM_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|out_8
c_func
(paren
id|base
op_plus
id|i
comma
id|CORE99_FLASH_CMD_WRITE_SETUP
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|base
op_plus
id|i
comma
id|datas
(braket
id|i
)braket
)paren
suffix:semicolon
r_do
(brace
id|stat
op_assign
id|in_8
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|stat
op_amp
id|CORE99_FLASH_STATUS_DONE
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
op_amp
id|CORE99_FLASH_STATUS_ERR
)paren
r_break
suffix:semicolon
)brace
id|out_8
c_func
(paren
id|base
comma
id|CORE99_FLASH_CMD_RESET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|CORE99_FLASH_STATUS_ERR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nvram: flash error 0x%02x on write !&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NVRAM_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|base
(braket
id|i
)braket
op_ne
id|datas
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nvram: flash write failed !&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|__init
DECL|function|pmac_nvram_init
r_void
id|pmac_nvram_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|dp
suffix:semicolon
id|nvram_naddrs
op_assign
l_int|0
suffix:semicolon
id|dp
op_assign
id|find_devices
c_func
(paren
l_string|&quot;nvram&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Can&squot;t find NVRAM device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nvram_naddrs
op_assign
id|dp-&gt;n_addrs
suffix:semicolon
id|is_core_99
op_assign
id|device_is_compatible
c_func
(paren
id|dp
comma
l_string|&quot;nvram,flash&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_core_99
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|gen_bank0
comma
id|gen_bank1
suffix:semicolon
r_if
c_cond
(paren
id|nvram_naddrs
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram: no address&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nvram_image
op_assign
id|kmalloc
c_func
(paren
id|NVRAM_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nvram_image
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram: can&squot;t allocate image&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nvram_data
op_assign
id|ioremap
c_func
(paren
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|NVRAM_SIZE
op_star
l_int|2
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;nvram: Checking bank 0...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|gen_bank0
op_assign
id|core99_check
c_func
(paren
(paren
id|u8
op_star
)paren
id|nvram_data
)paren
suffix:semicolon
id|gen_bank1
op_assign
id|core99_check
c_func
(paren
(paren
id|u8
op_star
)paren
id|nvram_data
op_plus
id|NVRAM_SIZE
)paren
suffix:semicolon
id|core99_bank
op_assign
(paren
id|gen_bank0
OL
id|gen_bank1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;nvram: gen0=%d, gen1=%d&bslash;n&quot;
comma
id|gen_bank0
comma
id|gen_bank1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;nvram: Active bank is: %d&bslash;n&quot;
comma
id|core99_bank
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NVRAM_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|nvram_image
(braket
id|i
)braket
op_assign
id|nvram_data
(braket
id|i
op_plus
id|core99_bank
op_star
id|NVRAM_SIZE
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_pSeries
op_logical_and
id|nvram_naddrs
op_eq
l_int|1
)paren
(brace
id|nvram_data
op_assign
id|ioremap
c_func
(paren
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
id|nvram_mult
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nvram_naddrs
op_eq
l_int|1
)paren
(brace
id|nvram_data
op_assign
id|ioremap
c_func
(paren
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
id|nvram_mult
op_assign
(paren
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
op_plus
id|NVRAM_SIZE
op_minus
l_int|1
)paren
op_div
id|NVRAM_SIZE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nvram_naddrs
op_eq
l_int|2
)paren
(brace
id|nvram_addr
op_assign
id|ioremap
c_func
(paren
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
id|nvram_data
op_assign
id|ioremap
c_func
(paren
id|dp-&gt;addrs
(braket
l_int|1
)braket
dot
id|address
comma
id|dp-&gt;addrs
(braket
l_int|1
)braket
dot
id|size
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nvram_naddrs
op_eq
l_int|0
op_logical_and
id|sys_ctrler
op_eq
id|SYS_CTRLER_PMU
)paren
(brace
id|nvram_naddrs
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Don&squot;t know how to access NVRAM with %d addresses&bslash;n&quot;
comma
id|nvram_naddrs
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|pmac_nvram_update
id|pmac_nvram_update
c_func
(paren
r_void
)paren
(brace
r_struct
id|core99_header
op_star
id|hdr99
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_core_99
op_logical_or
op_logical_neg
id|nvram_data
op_logical_or
op_logical_neg
id|nvram_image
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|nvram_image
comma
(paren
id|u8
op_star
)paren
id|nvram_data
op_plus
id|core99_bank
op_star
id|NVRAM_SIZE
comma
id|NVRAM_SIZE
)paren
)paren
r_return
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Updating nvram...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|hdr99
op_assign
(paren
r_struct
id|core99_header
op_star
)paren
id|nvram_image
suffix:semicolon
id|hdr99-&gt;generation
op_increment
suffix:semicolon
id|hdr99-&gt;hdr.signature
op_assign
id|CORE99_SIGNATURE
suffix:semicolon
id|hdr99-&gt;hdr.cksum
op_assign
id|chrp_checksum
c_func
(paren
op_amp
id|hdr99-&gt;hdr
)paren
suffix:semicolon
id|hdr99-&gt;adler
op_assign
id|core99_calc_adler
c_func
(paren
id|nvram_image
)paren
suffix:semicolon
id|core99_bank
op_assign
id|core99_bank
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|core99_erase_bank
c_func
(paren
id|core99_bank
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nvram: Error erasing bank %d&bslash;n&quot;
comma
id|core99_bank
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|core99_write_bank
c_func
(paren
id|core99_bank
comma
id|nvram_image
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;nvram: Error writing bank %d&bslash;n&quot;
comma
id|core99_bank
)paren
suffix:semicolon
)brace
id|__openfirmware
DECL|function|nvram_read_byte
r_int
r_char
id|nvram_read_byte
c_func
(paren
r_int
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU  
singleline_comment|// -aglitke
r_struct
id|adb_request
id|req
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|nvram_naddrs
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU
r_case
op_minus
l_int|1
suffix:colon
r_if
c_cond
(paren
id|pmu_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|3
comma
id|PMU_READ_NVRAM
comma
(paren
id|addr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|addr
op_amp
l_int|0xff
)paren
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|pmu_poll
c_func
(paren
)paren
suffix:semicolon
r_return
id|req.reply
(braket
l_int|1
)braket
suffix:semicolon
macro_line|#endif
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|is_core_99
)paren
r_return
id|nvram_image
(braket
id|addr
)braket
suffix:semicolon
r_return
id|nvram_data
(braket
(paren
id|addr
op_amp
(paren
id|NVRAM_SIZE
op_minus
l_int|1
)paren
)paren
op_star
id|nvram_mult
)braket
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|nvram_addr
op_assign
id|addr
op_rshift
l_int|5
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
r_return
id|nvram_data
(braket
(paren
id|addr
op_amp
l_int|0x1f
)paren
op_lshift
l_int|4
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|__openfirmware
DECL|function|nvram_write_byte
r_void
id|nvram_write_byte
c_func
(paren
r_int
r_char
id|val
comma
r_int
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU  
singleline_comment|// -aglitke
r_struct
id|adb_request
id|req
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|nvram_naddrs
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU
r_case
op_minus
l_int|1
suffix:colon
r_if
c_cond
(paren
id|pmu_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|4
comma
id|PMU_WRITE_NVRAM
comma
(paren
id|addr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|addr
op_amp
l_int|0xff
comma
id|val
)paren
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|pmu_poll
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|is_core_99
)paren
(brace
id|nvram_image
(braket
id|addr
)braket
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
)brace
id|nvram_data
(braket
(paren
id|addr
op_amp
(paren
id|NVRAM_SIZE
op_minus
l_int|1
)paren
)paren
op_star
id|nvram_mult
)braket
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|nvram_addr
op_assign
id|addr
op_rshift
l_int|5
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|nvram_data
(braket
(paren
id|addr
op_amp
l_int|0x1f
)paren
op_lshift
l_int|4
)braket
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
)brace
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|pmac_get_partition
id|pmac_get_partition
c_func
(paren
r_int
id|partition
)paren
(brace
r_return
id|nvram_partitions
(braket
id|partition
)braket
suffix:semicolon
)brace
id|u8
DECL|function|pmac_xpram_read
id|pmac_xpram_read
c_func
(paren
r_int
id|xpaddr
)paren
(brace
r_int
id|offset
op_assign
id|nvram_partitions
(braket
id|pmac_nvram_XPRAM
)braket
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|nvram_read_byte
c_func
(paren
id|xpaddr
op_plus
id|offset
)paren
suffix:semicolon
)brace
r_void
DECL|function|pmac_xpram_write
id|pmac_xpram_write
c_func
(paren
r_int
id|xpaddr
comma
id|u8
id|data
)paren
(brace
r_int
id|offset
op_assign
id|nvram_partitions
(braket
id|pmac_nvram_XPRAM
)braket
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_return
suffix:semicolon
id|nvram_write_byte
c_func
(paren
id|xpaddr
op_plus
id|offset
comma
id|data
)paren
suffix:semicolon
)brace
eof
