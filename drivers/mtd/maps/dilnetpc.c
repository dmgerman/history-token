multiline_comment|/* dilnetpc.c -- MTD map driver for SSV DIL/Net PC Boards &quot;DNP&quot; and &quot;ADNP&quot;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA&n; *&n; * $Id: dilnetpc.c,v 1.16 2004/11/04 13:24:14 gleixner Exp $&n; *&n; * The DIL/Net PC is a tiny embedded PC board made by SSV Embedded Systems&n; * featuring the AMD Elan SC410 processor. There are two variants of this&n; * board: DNP/1486 and ADNP/1486. The DNP version has 2 megs of flash&n; * ROM (Intel 28F016S3) and 8 megs of DRAM, the ADNP version has 4 megs&n; * flash and 16 megs of RAM.&n; * For details, see http://www.ssv-embedded.de/ssv/pc104/p169.htm&n; * and http://www.ssv-embedded.de/ssv/pc104/p170.htm&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/mtd/concat.h&gt;
multiline_comment|/*&n;** The DIL/NetPC keeps its BIOS in two distinct flash blocks.&n;** Destroying any of these blocks transforms the DNPC into&n;** a paperweight (albeit not a very useful one, considering&n;** it only weighs a few grams).&n;**&n;** Therefore, the BIOS blocks must never be erased or written to&n;** except by people who know exactly what they are doing (e.g.&n;** to install a BIOS update). These partitions are marked read-only&n;** by default, but can be made read/write by undefining&n;** DNPC_BIOS_BLOCKS_WRITEPROTECTED:&n;*/
DECL|macro|DNPC_BIOS_BLOCKS_WRITEPROTECTED
mdefine_line|#define DNPC_BIOS_BLOCKS_WRITEPROTECTED
multiline_comment|/*&n;** The ID string (in ROM) is checked to determine whether we&n;** are running on a DNP/1486 or ADNP/1486&n;*/
DECL|macro|BIOSID_BASE
mdefine_line|#define BIOSID_BASE&t;0x000fe100
DECL|macro|ID_DNPC
mdefine_line|#define ID_DNPC&t;&quot;DNP1486&quot;
DECL|macro|ID_ADNP
mdefine_line|#define ID_ADNP&t;&quot;ADNP1486&quot;
multiline_comment|/*&n;** Address where the flash should appear in CPU space&n;*/
DECL|macro|FLASH_BASE
mdefine_line|#define FLASH_BASE&t;0x2000000
multiline_comment|/*&n;** Chip Setup and Control (CSC) indexed register space&n;*/
DECL|macro|CSC_INDEX
mdefine_line|#define CSC_INDEX&t;0x22
DECL|macro|CSC_DATA
mdefine_line|#define CSC_DATA&t;0x23
DECL|macro|CSC_MMSWAR
mdefine_line|#define CSC_MMSWAR&t;0x30&t;/* MMS window C-F attributes register */
DECL|macro|CSC_MMSWDSR
mdefine_line|#define CSC_MMSWDSR&t;0x31&t;/* MMS window C-F device select register */
DECL|macro|CSC_RBWR
mdefine_line|#define CSC_RBWR&t;0xa7&t;/* GPIO Read-Back/Write Register B */
DECL|macro|CSC_CR
mdefine_line|#define CSC_CR&t;&t;0xd0&t;/* internal I/O device disable/Echo */
multiline_comment|/* Z-bus/configuration register */
DECL|macro|CSC_PCCMDCR
mdefine_line|#define CSC_PCCMDCR&t;0xf1&t;/* PC card mode and DMA control register */
multiline_comment|/*&n;** PC Card indexed register space:&n;*/
DECL|macro|PCC_INDEX
mdefine_line|#define PCC_INDEX&t;0x3e0
DECL|macro|PCC_DATA
mdefine_line|#define PCC_DATA&t;0x3e1
DECL|macro|PCC_AWER_B
mdefine_line|#define PCC_AWER_B&t;&t;0x46&t;/* Socket B Address Window enable register */
DECL|macro|PCC_MWSAR_1_Lo
mdefine_line|#define PCC_MWSAR_1_Lo&t;0x58&t;/* memory window 1 start address low register */
DECL|macro|PCC_MWSAR_1_Hi
mdefine_line|#define PCC_MWSAR_1_Hi&t;0x59&t;/* memory window 1 start address high register */
DECL|macro|PCC_MWEAR_1_Lo
mdefine_line|#define PCC_MWEAR_1_Lo&t;0x5A&t;/* memory window 1 stop address low register */
DECL|macro|PCC_MWEAR_1_Hi
mdefine_line|#define PCC_MWEAR_1_Hi&t;0x5B&t;/* memory window 1 stop address high register */
DECL|macro|PCC_MWAOR_1_Lo
mdefine_line|#define PCC_MWAOR_1_Lo&t;0x5C&t;/* memory window 1 address offset low register */
DECL|macro|PCC_MWAOR_1_Hi
mdefine_line|#define PCC_MWAOR_1_Hi&t;0x5D&t;/* memory window 1 address offset high register */
multiline_comment|/*&n;** Access to SC4x0&squot;s Chip Setup and Control (CSC)&n;** and PC Card (PCC) indexed registers:&n;*/
DECL|function|setcsc
r_static
r_inline
r_void
id|setcsc
c_func
(paren
r_int
id|reg
comma
r_int
r_char
id|data
)paren
(brace
id|outb
c_func
(paren
id|reg
comma
id|CSC_INDEX
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|CSC_DATA
)paren
suffix:semicolon
)brace
DECL|function|getcsc
r_static
r_inline
r_int
r_char
id|getcsc
c_func
(paren
r_int
id|reg
)paren
(brace
id|outb
c_func
(paren
id|reg
comma
id|CSC_INDEX
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|CSC_DATA
)paren
suffix:semicolon
)brace
DECL|function|setpcc
r_static
r_inline
r_void
id|setpcc
c_func
(paren
r_int
id|reg
comma
r_int
r_char
id|data
)paren
(brace
id|outb
c_func
(paren
id|reg
comma
id|PCC_INDEX
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|PCC_DATA
)paren
suffix:semicolon
)brace
DECL|function|getpcc
r_static
r_inline
r_int
r_char
id|getpcc
c_func
(paren
r_int
id|reg
)paren
(brace
id|outb
c_func
(paren
id|reg
comma
id|PCC_INDEX
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|PCC_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;************************************************************&n;** Enable access to DIL/NetPC&squot;s flash by mapping it into&n;** the SC4x0&squot;s MMS Window C.&n;************************************************************&n;*/
DECL|function|dnpc_map_flash
r_static
r_void
id|dnpc_map_flash
c_func
(paren
r_int
r_int
id|flash_base
comma
r_int
r_int
id|flash_size
)paren
(brace
r_int
r_int
id|flash_end
op_assign
id|flash_base
op_plus
id|flash_size
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;** enable setup of MMS windows C-F:&n;&t;*/
multiline_comment|/* - enable PC Card indexed register space */
id|setcsc
c_func
(paren
id|CSC_CR
comma
id|getcsc
c_func
(paren
id|CSC_CR
)paren
op_or
l_int|0x2
)paren
suffix:semicolon
multiline_comment|/* - set PC Card controller to operate in standard mode */
id|setcsc
c_func
(paren
id|CSC_PCCMDCR
comma
id|getcsc
c_func
(paren
id|CSC_PCCMDCR
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;** Program base address and end address of window&n;&t;** where the flash ROM should appear in CPU address space&n;&t;*/
id|setpcc
c_func
(paren
id|PCC_MWSAR_1_Lo
comma
(paren
id|flash_base
op_rshift
l_int|12
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|setpcc
c_func
(paren
id|PCC_MWSAR_1_Hi
comma
(paren
id|flash_base
op_rshift
l_int|20
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|setpcc
c_func
(paren
id|PCC_MWEAR_1_Lo
comma
(paren
id|flash_end
op_rshift
l_int|12
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|setpcc
c_func
(paren
id|PCC_MWEAR_1_Hi
comma
(paren
id|flash_end
op_rshift
l_int|20
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
multiline_comment|/* program offset of first flash location to appear in this window (0) */
id|setpcc
c_func
(paren
id|PCC_MWAOR_1_Lo
comma
(paren
(paren
l_int|0
op_minus
id|flash_base
)paren
op_rshift
l_int|12
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|setpcc
c_func
(paren
id|PCC_MWAOR_1_Hi
comma
(paren
(paren
l_int|0
op_minus
id|flash_base
)paren
op_rshift
l_int|20
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
multiline_comment|/* set attributes for MMS window C: non-cacheable, write-enabled */
id|setcsc
c_func
(paren
id|CSC_MMSWAR
comma
id|getcsc
c_func
(paren
id|CSC_MMSWAR
)paren
op_amp
op_complement
l_int|0x11
)paren
suffix:semicolon
multiline_comment|/* select physical device ROMCS0 (i.e. flash) for MMS Window C */
id|setcsc
c_func
(paren
id|CSC_MMSWDSR
comma
id|getcsc
c_func
(paren
id|CSC_MMSWDSR
)paren
op_amp
op_complement
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* enable memory window 1 */
id|setpcc
c_func
(paren
id|PCC_AWER_B
comma
id|getpcc
c_func
(paren
id|PCC_AWER_B
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* now disable PC Card indexed register space again */
id|setcsc
c_func
(paren
id|CSC_CR
comma
id|getcsc
c_func
(paren
id|CSC_CR
)paren
op_amp
op_complement
l_int|0x2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;************************************************************&n;** Disable access to DIL/NetPC&squot;s flash by mapping it into&n;** the SC4x0&squot;s MMS Window C.&n;************************************************************&n;*/
DECL|function|dnpc_unmap_flash
r_static
r_void
id|dnpc_unmap_flash
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* - enable PC Card indexed register space */
id|setcsc
c_func
(paren
id|CSC_CR
comma
id|getcsc
c_func
(paren
id|CSC_CR
)paren
op_or
l_int|0x2
)paren
suffix:semicolon
multiline_comment|/* disable memory window 1 */
id|setpcc
c_func
(paren
id|PCC_AWER_B
comma
id|getpcc
c_func
(paren
id|PCC_AWER_B
)paren
op_amp
op_complement
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* now disable PC Card indexed register space again */
id|setcsc
c_func
(paren
id|CSC_CR
comma
id|getcsc
c_func
(paren
id|CSC_CR
)paren
op_amp
op_complement
l_int|0x2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;************************************************************&n;** Enable/Disable VPP to write to flash&n;************************************************************&n;*/
DECL|variable|dnpc_spin
r_static
id|spinlock_t
id|dnpc_spin
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|vpp_counter
r_static
r_int
id|vpp_counter
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;** This is what has to be done for the DNP board ..&n;*/
DECL|function|dnp_set_vpp
r_static
r_void
id|dnp_set_vpp
c_func
(paren
r_struct
id|map_info
op_star
id|not_used
comma
r_int
id|on
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|dnpc_spin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
r_if
c_cond
(paren
op_increment
id|vpp_counter
op_eq
l_int|1
)paren
(brace
id|setcsc
c_func
(paren
id|CSC_RBWR
comma
id|getcsc
c_func
(paren
id|CSC_RBWR
)paren
op_amp
op_complement
l_int|0x4
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_decrement
id|vpp_counter
op_eq
l_int|0
)paren
(brace
id|setcsc
c_func
(paren
id|CSC_RBWR
comma
id|getcsc
c_func
(paren
id|CSC_RBWR
)paren
op_or
l_int|0x4
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|vpp_counter
OL
l_int|0
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|dnpc_spin
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;** .. and this the ADNP version:&n;*/
DECL|function|adnp_set_vpp
r_static
r_void
id|adnp_set_vpp
c_func
(paren
r_struct
id|map_info
op_star
id|not_used
comma
r_int
id|on
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|dnpc_spin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
r_if
c_cond
(paren
op_increment
id|vpp_counter
op_eq
l_int|1
)paren
(brace
id|setcsc
c_func
(paren
id|CSC_RBWR
comma
id|getcsc
c_func
(paren
id|CSC_RBWR
)paren
op_amp
op_complement
l_int|0x8
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_decrement
id|vpp_counter
op_eq
l_int|0
)paren
(brace
id|setcsc
c_func
(paren
id|CSC_RBWR
comma
id|getcsc
c_func
(paren
id|CSC_RBWR
)paren
op_or
l_int|0x8
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|vpp_counter
OL
l_int|0
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|dnpc_spin
)paren
suffix:semicolon
)brace
DECL|macro|DNP_WINDOW_SIZE
mdefine_line|#define DNP_WINDOW_SIZE&t;&t;0x00200000&t;/*  DNP flash size is 2MiB  */
DECL|macro|ADNP_WINDOW_SIZE
mdefine_line|#define ADNP_WINDOW_SIZE&t;0x00400000&t;/* ADNP flash size is 4MiB */
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR&t;&t;FLASH_BASE
DECL|variable|dnpc_map
r_static
r_struct
id|map_info
id|dnpc_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ADNP Flash Bank&quot;
comma
dot
id|size
op_assign
id|ADNP_WINDOW_SIZE
comma
dot
id|bankwidth
op_assign
l_int|1
comma
dot
id|set_vpp
op_assign
id|adnp_set_vpp
comma
dot
id|phys
op_assign
id|WINDOW_ADDR
)brace
suffix:semicolon
multiline_comment|/*&n;** The layout of the flash is somewhat &quot;strange&quot;:&n;**&n;** 1.  960 KiB (15 blocks) : Space for ROM Bootloader and user data&n;** 2.   64 KiB (1 block)   : System BIOS&n;** 3.  960 KiB (15 blocks) : User Data (DNP model) or&n;** 3. 3008 KiB (47 blocks) : User Data (ADNP model)&n;** 4.   64 KiB (1 block)   : System BIOS Entry&n;*/
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;ADNP boot&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|0xf0000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;ADNP system BIOS&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_NXTBLK
comma
dot
id|size
op_assign
l_int|0x10000
comma
macro_line|#ifdef DNPC_BIOS_BLOCKS_WRITEPROTECTED
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
comma
macro_line|#endif
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;ADNP file system&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_NXTBLK
comma
dot
id|size
op_assign
l_int|0x2f0000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;ADNP system BIOS entry&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_NXTBLK
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
comma
macro_line|#ifdef DNPC_BIOS_BLOCKS_WRITEPROTECTED
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
comma
macro_line|#endif
)brace
comma
)brace
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS (sizeof(partition_info)/sizeof(partition_info[0]))
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|variable|lowlvl_parts
r_static
r_struct
id|mtd_info
op_star
id|lowlvl_parts
(braket
id|NUM_PARTITIONS
)braket
suffix:semicolon
DECL|variable|merged_mtd
r_static
r_struct
id|mtd_info
op_star
id|merged_mtd
suffix:semicolon
multiline_comment|/*&n;** &quot;Highlevel&quot; partition info:&n;**&n;** Using the MTD concat layer, we can re-arrange partitions to our&n;** liking: we construct a virtual MTD device by concatenating the&n;** partitions, specifying the sequence such that the boot block&n;** is immediately followed by the filesystem block (i.e. the stupid&n;** system BIOS block is mapped to a different place). When re-partitioning&n;** this concatenated MTD device, we can set the boot block size to&n;** an arbitrary (though erase block aligned) value i.e. not one that&n;** is dictated by the flash&squot;s physical layout. We can thus set the&n;** boot block to be e.g. 64 KB (which is fully sufficient if we want&n;** to boot an etherboot image) or to -say- 1.5 MB if we want to boot&n;** a large kernel image. In all cases, the remainder of the flash&n;** is available as file system space.&n;*/
DECL|variable|higlvl_partition_info
r_static
r_struct
id|mtd_partition
id|higlvl_partition_info
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;ADNP boot block&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
id|CONFIG_MTD_DILNETPC_BOOTSIZE
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;ADNP file system space&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_NXTBLK
comma
dot
id|size
op_assign
id|ADNP_WINDOW_SIZE
op_minus
id|CONFIG_MTD_DILNETPC_BOOTSIZE
op_minus
l_int|0x20000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;ADNP system BIOS + BIOS Entry&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_NXTBLK
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
comma
macro_line|#ifdef DNPC_BIOS_BLOCKS_WRITEPROTECTED
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
comma
macro_line|#endif
)brace
comma
)brace
suffix:semicolon
DECL|macro|NUM_HIGHLVL_PARTITIONS
mdefine_line|#define NUM_HIGHLVL_PARTITIONS (sizeof(higlvl_partition_info)/sizeof(partition_info[0]))
DECL|function|dnp_adnp_probe
r_static
r_int
id|dnp_adnp_probe
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|biosid
comma
id|rc
op_assign
op_minus
l_int|1
suffix:semicolon
id|biosid
op_assign
(paren
r_char
op_star
)paren
id|ioremap
c_func
(paren
id|BIOSID_BASE
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|biosid
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|biosid
comma
id|ID_DNPC
)paren
)paren
(brace
id|rc
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* this is a DNPC  */
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|biosid
comma
id|ID_ADNP
)paren
)paren
(brace
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this is a ADNPC */
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|biosid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|init_dnpc
r_static
r_int
id|__init
id|init_dnpc
c_func
(paren
r_void
)paren
(brace
r_int
id|is_dnp
suffix:semicolon
multiline_comment|/*&n;&t;** determine hardware (DNP/ADNP/invalid)&n;&t;*/
r_if
c_cond
(paren
(paren
id|is_dnp
op_assign
id|dnp_adnp_probe
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t;** Things are set up for ADNP by default&n;&t;** -&gt; modify all that needs to be different for DNP&n;&t;*/
r_if
c_cond
(paren
id|is_dnp
)paren
(brace
multiline_comment|/*&n;&t;&t;** Adjust window size, select correct set_vpp function.&n;&t;&t;** The partitioning scheme is identical on both DNP&n;&t;&t;** and ADNP except for the size of the third partition.&n;&t;&t;*/
r_int
id|i
suffix:semicolon
id|dnpc_map.size
op_assign
id|DNP_WINDOW_SIZE
suffix:semicolon
id|dnpc_map.set_vpp
op_assign
id|dnp_set_vpp
suffix:semicolon
id|partition_info
(braket
l_int|2
)braket
dot
id|size
op_assign
l_int|0xf0000
suffix:semicolon
multiline_comment|/*&n;&t;&t;** increment all string pointers so the leading &squot;A&squot; gets skipped,&n;&t;&t;** thus turning all occurrences of &quot;ADNP ...&quot; into &quot;DNP ...&quot;&n;&t;&t;*/
op_increment
id|dnpc_map.name
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
id|NUM_PARTITIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
op_increment
id|partition_info
(braket
id|i
)braket
dot
id|name
suffix:semicolon
)brace
id|higlvl_partition_info
(braket
l_int|1
)braket
dot
id|size
op_assign
id|DNP_WINDOW_SIZE
op_minus
id|CONFIG_MTD_DILNETPC_BOOTSIZE
op_minus
l_int|0x20000
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
id|NUM_HIGHLVL_PARTITIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
op_increment
id|higlvl_partition_info
(braket
id|i
)braket
dot
id|name
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;DIL/Net %s flash: 0x%lx at 0x%lx&bslash;n&quot;
comma
id|is_dnp
ques
c_cond
l_string|&quot;DNPC&quot;
suffix:colon
l_string|&quot;ADNP&quot;
comma
id|dnpc_map.size
comma
id|dnpc_map.phys
)paren
suffix:semicolon
id|dnpc_map.virt
op_assign
id|ioremap_nocache
c_func
(paren
id|dnpc_map.phys
comma
id|dnpc_map.size
)paren
suffix:semicolon
id|dnpc_map_flash
c_func
(paren
id|dnpc_map.phys
comma
id|dnpc_map.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dnpc_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap_nocache&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|dnpc_map
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FLASH virtual address: 0x%p&bslash;n&quot;
comma
id|dnpc_map.virt
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;jedec_probe&quot;
comma
op_amp
id|dnpc_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|dnpc_map
)paren
suffix:semicolon
multiline_comment|/*&n;&t;** If flash probes fail, try to make flashes accessible&n;&t;** at least as ROM. Ajust erasesize in this case since&n;&t;** the default one (128M) will break our partitioning&n;&t;*/
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
r_if
c_cond
(paren
(paren
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_rom&quot;
comma
op_amp
id|dnpc_map
)paren
)paren
)paren
(brace
id|mymtd-&gt;erasesize
op_assign
l_int|0x10000
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|iounmap
c_func
(paren
id|dnpc_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/*&n;&t;** Supply pointers to lowlvl_parts[] array to add_mtd_partitions()&n;&t;** -&gt; add_mtd_partitions() will _not_ register MTD devices for&n;&t;** the partitions, but will instead store pointers to the MTD&n;&t;** objects it creates into our lowlvl_parts[] array.&n;&t;** NOTE: we arrange the pointers such that the sequence of the&n;&t;**       partitions gets re-arranged: partition #2 follows&n;&t;**       partition #0.&n;&t;*/
id|partition_info
(braket
l_int|0
)braket
dot
id|mtdp
op_assign
op_amp
id|lowlvl_parts
(braket
l_int|0
)braket
suffix:semicolon
id|partition_info
(braket
l_int|1
)braket
dot
id|mtdp
op_assign
op_amp
id|lowlvl_parts
(braket
l_int|2
)braket
suffix:semicolon
id|partition_info
(braket
l_int|2
)braket
dot
id|mtdp
op_assign
op_amp
id|lowlvl_parts
(braket
l_int|1
)braket
suffix:semicolon
id|partition_info
(braket
l_int|3
)braket
dot
id|mtdp
op_assign
op_amp
id|lowlvl_parts
(braket
l_int|3
)braket
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|partition_info
comma
id|NUM_PARTITIONS
)paren
suffix:semicolon
multiline_comment|/*&n;&t;** now create a virtual MTD device by concatenating the for partitions&n;&t;** (in the sequence given by the lowlvl_parts[] array.&n;&t;*/
id|merged_mtd
op_assign
id|mtd_concat_create
c_func
(paren
id|lowlvl_parts
comma
id|NUM_PARTITIONS
comma
l_string|&quot;(A)DNP Flash Concatenated&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|merged_mtd
)paren
(brace
multiline_comment|/*&n;&t;&t;** now partition the new device the way we want it. This time,&n;&t;&t;** we do not supply mtd pointers in higlvl_partition_info, so&n;&t;&t;** add_mtd_partitions() will register the devices.&n;&t;&t;*/
id|add_mtd_partitions
c_func
(paren
id|merged_mtd
comma
id|higlvl_partition_info
comma
id|NUM_HIGHLVL_PARTITIONS
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_dnpc
r_static
r_void
id|__exit
id|cleanup_dnpc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|merged_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|merged_mtd
)paren
suffix:semicolon
id|mtd_concat_destroy
c_func
(paren
id|merged_mtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dnpc_map.virt
)paren
(brace
id|iounmap
c_func
(paren
id|dnpc_map.virt
)paren
suffix:semicolon
id|dnpc_unmap_flash
c_func
(paren
)paren
suffix:semicolon
id|dnpc_map.virt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|init_dnpc
id|module_init
c_func
(paren
id|init_dnpc
)paren
suffix:semicolon
DECL|variable|cleanup_dnpc
id|module_exit
c_func
(paren
id|cleanup_dnpc
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
l_string|&quot;Sysgo Real-Time Solutions GmbH&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for SSV DIL/NetPC DNP &amp; ADNP&quot;
)paren
suffix:semicolon
eof
