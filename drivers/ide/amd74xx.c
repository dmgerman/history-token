multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * $Id: amd74xx.c,v 2.8 2002/03/14 11:52:20 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Andre Hedrick&n; */
multiline_comment|/*&n; * AMD 755/756/766/8111 IDE driver for Linux.&n; *&n; * UDMA66 and higher modes are autoenabled only in case the BIOS has detected a&n; * 80 wire cable. To ignore the BIOS data and assume the cable is present, use&n; * &squot;ide0=ata66&squot; or &squot;ide1=ata66&squot; on the kernel command line.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ata-timing.h&quot;
macro_line|#include &quot;pcihost.h&quot;
DECL|macro|AMD_IDE_ENABLE
mdefine_line|#define AMD_IDE_ENABLE&t;&t;(0x00 + amd_config-&gt;base)
DECL|macro|AMD_IDE_CONFIG
mdefine_line|#define AMD_IDE_CONFIG&t;&t;(0x01 + amd_config-&gt;base)
DECL|macro|AMD_CABLE_DETECT
mdefine_line|#define AMD_CABLE_DETECT&t;(0x02 + amd_config-&gt;base)
DECL|macro|AMD_DRIVE_TIMING
mdefine_line|#define AMD_DRIVE_TIMING&t;(0x08 + amd_config-&gt;base)
DECL|macro|AMD_8BIT_TIMING
mdefine_line|#define AMD_8BIT_TIMING&t;&t;(0x0e + amd_config-&gt;base)
DECL|macro|AMD_ADDRESS_SETUP
mdefine_line|#define AMD_ADDRESS_SETUP&t;(0x0c + amd_config-&gt;base)
DECL|macro|AMD_UDMA_TIMING
mdefine_line|#define AMD_UDMA_TIMING&t;&t;(0x10 + amd_config-&gt;base)
DECL|macro|AMD_UDMA
mdefine_line|#define AMD_UDMA&t;&t;0x07
DECL|macro|AMD_UDMA_33
mdefine_line|#define AMD_UDMA_33&t;&t;0x01
DECL|macro|AMD_UDMA_66
mdefine_line|#define AMD_UDMA_66&t;&t;0x02
DECL|macro|AMD_UDMA_100
mdefine_line|#define AMD_UDMA_100&t;&t;0x03
DECL|macro|AMD_BAD_SWDMA
mdefine_line|#define AMD_BAD_SWDMA&t;&t;0x08
DECL|macro|AMD_BAD_FIFO
mdefine_line|#define AMD_BAD_FIFO&t;&t;0x10
multiline_comment|/*&n; * AMD SouthBridge chips.&n; */
DECL|struct|amd_ide_chip
r_static
r_struct
id|amd_ide_chip
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|rev
r_int
r_char
id|rev
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|variable|amd_ide_chips
)brace
id|amd_ide_chips
(braket
)braket
op_assign
(brace
(brace
id|PCI_DEVICE_ID_AMD_8111_IDE
comma
l_int|0x00
comma
l_int|0x40
comma
id|AMD_UDMA_100
)brace
comma
multiline_comment|/* AMD-8111 */
(brace
id|PCI_DEVICE_ID_AMD_OPUS_7441
comma
l_int|0x00
comma
l_int|0x40
comma
id|AMD_UDMA_100
)brace
comma
multiline_comment|/* AMD-768 Opus */
(brace
id|PCI_DEVICE_ID_AMD_VIPER_7411
comma
l_int|0x00
comma
l_int|0x40
comma
id|AMD_UDMA_100
op_or
id|AMD_BAD_FIFO
)brace
comma
multiline_comment|/* AMD-766 Viper */
(brace
id|PCI_DEVICE_ID_AMD_VIPER_7409
comma
l_int|0x07
comma
l_int|0x40
comma
id|AMD_UDMA_66
)brace
comma
multiline_comment|/* AMD-756/c4+ Viper */
(brace
id|PCI_DEVICE_ID_AMD_VIPER_7409
comma
l_int|0x00
comma
l_int|0x40
comma
id|AMD_UDMA_66
op_or
id|AMD_BAD_SWDMA
)brace
comma
multiline_comment|/* AMD-756 Viper */
(brace
id|PCI_DEVICE_ID_AMD_COBRA_7401
comma
l_int|0x00
comma
l_int|0x40
comma
id|AMD_UDMA_33
op_or
id|AMD_BAD_SWDMA
)brace
comma
multiline_comment|/* AMD-755 Cobra */
(brace
id|PCI_DEVICE_ID_NVIDIA_NFORCE_IDE
comma
l_int|0x00
comma
l_int|0x50
comma
id|AMD_UDMA_100
)brace
comma
multiline_comment|/* nVidia nForce */
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|amd_config
r_static
r_struct
id|amd_ide_chip
op_star
id|amd_config
suffix:semicolon
DECL|variable|amd_enabled
r_static
r_int
r_char
id|amd_enabled
suffix:semicolon
DECL|variable|amd_80w
r_static
r_int
r_int
id|amd_80w
suffix:semicolon
DECL|variable|amd_clock
r_static
r_int
r_int
id|amd_clock
suffix:semicolon
DECL|variable|amd_cyc2udma
r_static
r_int
r_char
id|amd_cyc2udma
(braket
)braket
op_assign
(brace
l_int|6
comma
l_int|6
comma
l_int|5
comma
l_int|4
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|3
)brace
suffix:semicolon
DECL|variable|amd_udma2cyc
r_static
r_int
r_char
id|amd_udma2cyc
(braket
)braket
op_assign
(brace
l_int|4
comma
l_int|6
comma
l_int|8
comma
l_int|10
comma
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|amd_dma
r_static
r_char
op_star
id|amd_dma
(braket
)braket
op_assign
(brace
l_string|&quot;MWDMA16&quot;
comma
l_string|&quot;UDMA33&quot;
comma
l_string|&quot;UDMA66&quot;
comma
l_string|&quot;UDMA100&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * AMD /proc entry.&n; */
macro_line|#if 0 &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
id|byte
id|amd74xx_proc
suffix:semicolon
r_int
id|amd_base
suffix:semicolon
r_static
r_struct
id|pci_dev
op_star
id|bmide_dev
suffix:semicolon
r_extern
r_int
(paren
op_star
id|amd74xx_display_info
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ide-proc.c */
mdefine_line|#define amd_print(format, arg...) p += sprintf(p, format &quot;&bslash;n&quot; , ## arg)
mdefine_line|#define amd_print_drive(name, format, arg...)&bslash;&n;&t;p += sprintf(p, name); for (i = 0; i &lt; 4; i++) p += sprintf(p, format, ## arg); p += sprintf(p, &quot;&bslash;n&quot;);
r_static
r_int
id|amd_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|addr
comma
id|off_t
id|offset
comma
r_int
id|count
)paren
(brace
r_int
id|speed
(braket
l_int|4
)braket
comma
id|cycle
(braket
l_int|4
)braket
comma
id|setup
(braket
l_int|4
)braket
comma
id|active
(braket
l_int|4
)braket
comma
id|recover
(braket
l_int|4
)braket
comma
id|den
(braket
l_int|4
)braket
comma
id|uen
(braket
l_int|4
)braket
comma
id|udma
(braket
l_int|4
)braket
comma
id|active8b
(braket
l_int|4
)braket
comma
id|recover8b
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|bmide_dev
suffix:semicolon
r_int
r_int
id|v
comma
id|u
comma
id|i
suffix:semicolon
r_int
r_int
id|c
comma
id|w
suffix:semicolon
r_int
r_char
id|t
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;----------AMD BusMastering IDE Configuration----------------&quot;
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Driver Version:                     2.8&quot;
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;South Bridge:                       %s&quot;
comma
id|bmide_dev-&gt;name
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|t
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Revision:                           IDE %#x&quot;
comma
id|t
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Highest DMA rate:                   %s&quot;
comma
id|amd_dma
(braket
id|amd_config-&gt;flags
op_amp
id|AMD_UDMA
)braket
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;BM-DMA base:                        %#x&quot;
comma
id|amd_base
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;PCI clock:                          %d.%dMHz&quot;
comma
id|amd_clock
op_div
l_int|1000
comma
id|amd_clock
op_div
l_int|100
op_mod
l_int|10
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;-----------------------Primary IDE-------Secondary IDE------&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AMD_IDE_CONFIG
comma
op_amp
id|t
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Prefetch Buffer:       %10s%20s&quot;
comma
(paren
id|t
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|t
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Post Write Buffer:     %10s%20s&quot;
comma
(paren
id|t
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|t
op_amp
l_int|0x10
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AMD_IDE_ENABLE
comma
op_amp
id|t
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Enabled:               %10s%20s&quot;
comma
(paren
id|t
op_amp
l_int|0x02
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|t
op_amp
l_int|0x01
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|c
op_assign
id|inb
c_func
(paren
id|amd_base
op_plus
l_int|0x02
)paren
op_or
(paren
id|inb
c_func
(paren
id|amd_base
op_plus
l_int|0x0a
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Simplex only:          %10s%20s&quot;
comma
(paren
id|c
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|c
op_amp
l_int|0x8000
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;Cable Type:            %10s%20s&quot;
comma
(paren
id|amd_80w
op_amp
l_int|1
)paren
ques
c_cond
l_string|&quot;80w&quot;
suffix:colon
l_string|&quot;40w&quot;
comma
(paren
id|amd_80w
op_amp
l_int|2
)paren
ques
c_cond
l_string|&quot;80w&quot;
suffix:colon
l_string|&quot;40w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|amd_clock
)paren
r_return
id|p
op_minus
id|buffer
suffix:semicolon
id|amd_print
c_func
(paren
l_string|&quot;-------------------drive0----drive1----drive2----drive3-----&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AMD_ADDRESS_SETUP
comma
op_amp
id|t
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD_DRIVE_TIMING
comma
op_amp
id|v
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|AMD_8BIT_TIMING
comma
op_amp
id|w
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD_UDMA_TIMING
comma
op_amp
id|u
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|setup
(braket
id|i
)braket
op_assign
(paren
(paren
id|t
op_rshift
(paren
(paren
l_int|3
op_minus
id|i
)paren
op_lshift
l_int|1
)paren
)paren
op_amp
l_int|0x3
)paren
op_plus
l_int|1
suffix:semicolon
id|recover8b
(braket
id|i
)braket
op_assign
(paren
(paren
id|w
op_rshift
(paren
(paren
l_int|1
op_minus
(paren
id|i
op_rshift
l_int|1
)paren
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xf
)paren
op_plus
l_int|1
suffix:semicolon
id|active8b
(braket
id|i
)braket
op_assign
(paren
(paren
id|w
op_rshift
(paren
(paren
(paren
l_int|1
op_minus
(paren
id|i
op_rshift
l_int|1
)paren
)paren
op_lshift
l_int|3
)paren
op_plus
l_int|4
)paren
)paren
op_amp
l_int|0xf
)paren
op_plus
l_int|1
suffix:semicolon
id|active
(braket
id|i
)braket
op_assign
(paren
(paren
id|v
op_rshift
(paren
(paren
(paren
l_int|3
op_minus
id|i
)paren
op_lshift
l_int|3
)paren
op_plus
l_int|4
)paren
)paren
op_amp
l_int|0xf
)paren
op_plus
l_int|1
suffix:semicolon
id|recover
(braket
id|i
)braket
op_assign
(paren
(paren
id|v
op_rshift
(paren
(paren
l_int|3
op_minus
id|i
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xf
)paren
op_plus
l_int|1
suffix:semicolon
id|udma
(braket
id|i
)braket
op_assign
id|amd_udma2cyc
(braket
(paren
(paren
id|u
op_rshift
(paren
(paren
l_int|3
op_minus
id|i
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0x7
)paren
)braket
suffix:semicolon
id|uen
(braket
id|i
)braket
op_assign
(paren
(paren
id|u
op_rshift
(paren
(paren
l_int|3
op_minus
id|i
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0x40
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|den
(braket
id|i
)braket
op_assign
(paren
id|c
op_amp
(paren
(paren
id|i
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x40
suffix:colon
l_int|0x20
)paren
op_lshift
(paren
(paren
id|i
op_amp
l_int|2
)paren
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|den
(braket
id|i
)braket
op_logical_and
id|uen
(braket
id|i
)braket
op_logical_and
id|udma
(braket
id|i
)braket
op_eq
l_int|1
)paren
(brace
id|speed
(braket
id|i
)braket
op_assign
id|amd_clock
op_star
l_int|3
suffix:semicolon
id|cycle
(braket
id|i
)braket
op_assign
l_int|666666
op_div
id|amd_clock
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|speed
(braket
id|i
)braket
op_assign
l_int|4
op_star
id|amd_clock
op_div
(paren
(paren
id|den
(braket
id|i
)braket
op_logical_and
id|uen
(braket
id|i
)braket
)paren
ques
c_cond
id|udma
(braket
id|i
)braket
suffix:colon
(paren
id|active
(braket
id|i
)braket
op_plus
id|recover
(braket
id|i
)braket
)paren
op_star
l_int|2
)paren
suffix:semicolon
id|cycle
(braket
id|i
)braket
op_assign
l_int|1000000
op_star
(paren
(paren
id|den
(braket
id|i
)braket
op_logical_and
id|uen
(braket
id|i
)braket
)paren
ques
c_cond
id|udma
(braket
id|i
)braket
suffix:colon
(paren
id|active
(braket
id|i
)braket
op_plus
id|recover
(braket
id|i
)braket
)paren
op_star
l_int|2
)paren
op_div
id|amd_clock
op_div
l_int|2
suffix:semicolon
)brace
id|amd_print_drive
c_func
(paren
l_string|&quot;Transfer Mode: &quot;
comma
l_string|&quot;%10s&quot;
comma
id|den
(braket
id|i
)braket
ques
c_cond
(paren
id|uen
(braket
id|i
)braket
ques
c_cond
l_string|&quot;UDMA&quot;
suffix:colon
l_string|&quot;DMA&quot;
)paren
suffix:colon
l_string|&quot;PIO&quot;
)paren
suffix:semicolon
id|amd_print_drive
c_func
(paren
l_string|&quot;Address Setup: &quot;
comma
l_string|&quot;%8dns&quot;
comma
l_int|1000000
op_star
id|setup
(braket
id|i
)braket
op_div
id|amd_clock
)paren
suffix:semicolon
id|amd_print_drive
c_func
(paren
l_string|&quot;Cmd Active:    &quot;
comma
l_string|&quot;%8dns&quot;
comma
l_int|1000000
op_star
id|active8b
(braket
id|i
)braket
op_div
id|amd_clock
)paren
suffix:semicolon
id|amd_print_drive
c_func
(paren
l_string|&quot;Cmd Recovery:  &quot;
comma
l_string|&quot;%8dns&quot;
comma
l_int|1000000
op_star
id|recover8b
(braket
id|i
)braket
op_div
id|amd_clock
)paren
suffix:semicolon
id|amd_print_drive
c_func
(paren
l_string|&quot;Data Active:   &quot;
comma
l_string|&quot;%8dns&quot;
comma
l_int|1000000
op_star
id|active
(braket
id|i
)braket
op_div
id|amd_clock
)paren
suffix:semicolon
id|amd_print_drive
c_func
(paren
l_string|&quot;Data Recovery: &quot;
comma
l_string|&quot;%8dns&quot;
comma
l_int|1000000
op_star
id|recover
(braket
id|i
)braket
op_div
id|amd_clock
)paren
suffix:semicolon
id|amd_print_drive
c_func
(paren
l_string|&quot;Cycle Time:    &quot;
comma
l_string|&quot;%8dns&quot;
comma
id|cycle
(braket
id|i
)braket
)paren
suffix:semicolon
id|amd_print_drive
c_func
(paren
l_string|&quot;Transfer Rate: &quot;
comma
l_string|&quot;%4d.%dMB/s&quot;
comma
id|speed
(braket
id|i
)braket
op_div
l_int|1000
comma
id|speed
(braket
id|i
)braket
op_div
l_int|100
op_mod
l_int|10
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buffer
suffix:semicolon
multiline_comment|/* hoping it is less than 4K... */
)brace
macro_line|#endif
multiline_comment|/*&n; * amd_set_speed() writes timing values to the chipset registers&n; */
DECL|function|amd_set_speed
r_static
r_void
id|amd_set_speed
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|dn
comma
r_struct
id|ata_timing
op_star
id|timing
)paren
(brace
r_int
r_char
id|t
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AMD_ADDRESS_SETUP
comma
op_amp
id|t
)paren
suffix:semicolon
id|t
op_assign
(paren
id|t
op_amp
op_complement
(paren
l_int|3
op_lshift
(paren
(paren
l_int|3
op_minus
id|dn
)paren
op_lshift
l_int|1
)paren
)paren
)paren
op_or
(paren
(paren
id|FIT
c_func
(paren
id|timing-&gt;setup
comma
l_int|1
comma
l_int|4
)paren
op_minus
l_int|1
)paren
op_lshift
(paren
(paren
l_int|3
op_minus
id|dn
)paren
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AMD_ADDRESS_SETUP
comma
id|t
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AMD_8BIT_TIMING
op_plus
(paren
l_int|1
op_minus
(paren
id|dn
op_rshift
l_int|1
)paren
)paren
comma
(paren
(paren
id|FIT
c_func
(paren
id|timing-&gt;act8b
comma
l_int|1
comma
l_int|16
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|4
)paren
op_or
(paren
id|FIT
c_func
(paren
id|timing-&gt;rec8b
comma
l_int|1
comma
l_int|16
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AMD_DRIVE_TIMING
op_plus
(paren
l_int|3
op_minus
id|dn
)paren
comma
(paren
(paren
id|FIT
c_func
(paren
id|timing-&gt;active
comma
l_int|1
comma
l_int|16
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|4
)paren
op_or
(paren
id|FIT
c_func
(paren
id|timing-&gt;recover
comma
l_int|1
comma
l_int|16
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|amd_config-&gt;flags
op_amp
id|AMD_UDMA
)paren
(brace
r_case
id|AMD_UDMA_33
suffix:colon
id|t
op_assign
id|timing-&gt;udma
ques
c_cond
(paren
l_int|0xc0
op_or
(paren
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|5
)paren
op_minus
l_int|2
)paren
)paren
suffix:colon
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AMD_UDMA_66
suffix:colon
id|t
op_assign
id|timing-&gt;udma
ques
c_cond
(paren
l_int|0xc0
op_or
id|amd_cyc2udma
(braket
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|10
)paren
)braket
)paren
suffix:colon
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AMD_UDMA_100
suffix:colon
id|t
op_assign
id|timing-&gt;udma
ques
c_cond
(paren
l_int|0xc0
op_or
id|amd_cyc2udma
(braket
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|1
comma
l_int|10
)paren
)braket
)paren
suffix:colon
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AMD_UDMA_TIMING
op_plus
(paren
l_int|3
op_minus
id|dn
)paren
comma
id|t
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * amd_set_drive() computes timing values configures the drive and&n; * the chipset to a desired transfer mode. It also can be called&n; * by upper layers.&n; */
DECL|function|amd_set_drive
r_static
r_int
id|amd_set_drive
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_char
id|speed
)paren
(brace
id|ide_drive_t
op_star
id|peer
op_assign
id|drive-&gt;channel-&gt;drives
op_plus
(paren
op_complement
id|drive-&gt;dn
op_amp
l_int|1
)paren
suffix:semicolon
r_struct
id|ata_timing
id|t
comma
id|p
suffix:semicolon
r_int
id|T
comma
id|UT
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_ne
id|XFER_PIO_SLOW
op_logical_and
id|speed
op_ne
id|drive-&gt;current_speed
)paren
r_if
c_cond
(paren
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ide%d: Drive %d didn&squot;t accept speed setting. Oh, well.&bslash;n&quot;
comma
id|drive-&gt;dn
op_rshift
l_int|1
comma
id|drive-&gt;dn
op_amp
l_int|1
)paren
suffix:semicolon
id|T
op_assign
l_int|1000000000
op_div
id|amd_clock
suffix:semicolon
id|UT
op_assign
id|T
op_div
id|min_t
c_func
(paren
r_int
comma
id|max_t
c_func
(paren
r_int
comma
id|amd_config-&gt;flags
op_amp
id|AMD_UDMA
comma
l_int|1
)paren
comma
l_int|2
)paren
suffix:semicolon
id|ata_timing_compute
c_func
(paren
id|drive
comma
id|speed
comma
op_amp
id|t
comma
id|T
comma
id|UT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer-&gt;present
)paren
(brace
id|ata_timing_compute
c_func
(paren
id|peer
comma
id|peer-&gt;current_speed
comma
op_amp
id|p
comma
id|T
comma
id|UT
)paren
suffix:semicolon
id|ata_timing_merge
c_func
(paren
op_amp
id|p
comma
op_amp
id|t
comma
op_amp
id|t
comma
id|IDE_TIMING_8BIT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|speed
op_eq
id|XFER_UDMA_5
op_logical_and
id|amd_clock
op_le
l_int|33333
)paren
id|t.udma
op_assign
l_int|1
suffix:semicolon
id|amd_set_speed
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
id|drive-&gt;dn
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;init_speed
)paren
id|drive-&gt;init_speed
op_assign
id|speed
suffix:semicolon
id|drive-&gt;current_speed
op_assign
id|speed
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * amd74xx_tune_drive() is a callback from upper layers for&n; * PIO-only tuning.&n; */
DECL|function|amd74xx_tune_drive
r_static
r_void
id|amd74xx_tune_drive
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_char
id|pio
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|amd_enabled
op_rshift
id|drive-&gt;channel-&gt;unit
)paren
op_amp
l_int|1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pio
op_eq
l_int|255
)paren
(brace
id|amd_set_drive
c_func
(paren
id|drive
comma
id|ata_timing_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|amd_set_drive
c_func
(paren
id|drive
comma
id|XFER_PIO_0
op_plus
id|min_t
c_func
(paren
id|byte
comma
id|pio
comma
l_int|5
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
DECL|function|amd74xx_dmaproc
r_int
id|amd74xx_dmaproc
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
id|w80
op_assign
id|drive-&gt;channel-&gt;udma_four
suffix:semicolon
r_int
id|speed
op_assign
id|ata_timing_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
op_or
id|XFER_MWDMA
op_or
id|XFER_UDMA
op_or
(paren
(paren
id|amd_config-&gt;flags
op_amp
id|AMD_BAD_SWDMA
)paren
ques
c_cond
l_int|0
suffix:colon
id|XFER_SWDMA
)paren
op_or
(paren
id|w80
op_logical_and
(paren
id|amd_config-&gt;flags
op_amp
id|AMD_UDMA
)paren
op_ge
id|AMD_UDMA_66
ques
c_cond
id|XFER_UDMA_66
suffix:colon
l_int|0
)paren
op_or
(paren
id|w80
op_logical_and
(paren
id|amd_config-&gt;flags
op_amp
id|AMD_UDMA
)paren
op_ge
id|AMD_UDMA_100
ques
c_cond
id|XFER_UDMA_100
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|amd_set_drive
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
id|udma_enable
c_func
(paren
id|drive
comma
id|drive-&gt;channel-&gt;autodma
op_logical_and
(paren
id|speed
op_amp
id|XFER_MODE
)paren
op_ne
id|XFER_PIO
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * The initialization callback. Here we determine the IDE chip type&n; * and initialize its drive independent registers.&n; */
DECL|function|amd74xx_init_chipset
r_static
r_int
r_int
id|__init
id|amd74xx_init_chipset
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_char
id|t
suffix:semicolon
r_int
r_int
id|u
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n; * Find out what AMD IDE is this.&n; */
r_for
c_loop
(paren
id|amd_config
op_assign
id|amd_ide_chips
suffix:semicolon
id|amd_config-&gt;id
suffix:semicolon
id|amd_config
op_increment
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
id|amd_config-&gt;id
op_logical_and
id|t
op_ge
id|amd_config-&gt;rev
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|amd_config-&gt;id
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AMD_IDE: Unknown AMD IDE Chip, contact Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n; * Check 80-wire cable presence.&n; */
r_switch
c_cond
(paren
id|amd_config-&gt;flags
op_amp
id|AMD_UDMA
)paren
(brace
r_case
id|AMD_UDMA_100
suffix:colon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AMD_CABLE_DETECT
comma
op_amp
id|t
)paren
suffix:semicolon
id|amd_80w
op_assign
(paren
(paren
id|u
op_amp
l_int|0x3
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|u
op_amp
l_int|0xc
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|24
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_sub_assign
l_int|8
)paren
r_if
c_cond
(paren
(paren
(paren
id|u
op_rshift
id|i
)paren
op_amp
l_int|4
)paren
op_logical_and
op_logical_neg
(paren
id|amd_80w
op_amp
(paren
l_int|1
op_lshift
(paren
l_int|1
op_minus
(paren
id|i
op_rshift
l_int|4
)paren
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AMD_IDE: Bios didn&squot;t set cable bits corectly. Enabling workaround.&bslash;n&quot;
)paren
suffix:semicolon
id|amd_80w
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|1
op_minus
(paren
id|i
op_rshift
l_int|4
)paren
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AMD_UDMA_66
suffix:colon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD_UDMA_TIMING
comma
op_amp
id|u
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|24
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_sub_assign
l_int|8
)paren
r_if
c_cond
(paren
(paren
id|u
op_rshift
id|i
)paren
op_amp
l_int|4
)paren
id|amd_80w
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|1
op_minus
(paren
id|i
op_rshift
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD_IDE_ENABLE
comma
op_amp
id|u
)paren
suffix:semicolon
id|amd_enabled
op_assign
(paren
(paren
id|u
op_amp
l_int|1
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|u
op_amp
l_int|2
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n; * Take care of prefetch &amp; postwrite.&n; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AMD_IDE_CONFIG
comma
op_amp
id|t
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AMD_IDE_CONFIG
comma
(paren
id|amd_config-&gt;flags
op_amp
id|AMD_BAD_FIFO
)paren
ques
c_cond
(paren
id|t
op_amp
l_int|0x0f
)paren
suffix:colon
(paren
id|t
op_or
l_int|0xf0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Determine the system bus clock.&n; */
id|amd_clock
op_assign
id|system_bus_speed
op_star
l_int|1000
suffix:semicolon
r_switch
c_cond
(paren
id|amd_clock
)paren
(brace
r_case
l_int|33000
suffix:colon
id|amd_clock
op_assign
l_int|33333
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|37000
suffix:colon
id|amd_clock
op_assign
l_int|37500
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|41000
suffix:colon
id|amd_clock
op_assign
l_int|41666
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|amd_clock
template_param
l_int|50000
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AMD_IDE: User given PCI clock speed impossible (%d), using 33 MHz instead.&bslash;n&quot;
comma
id|amd_clock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AMD_IDE: Use ide0=ata66 if you want to assume 80-wire cable&bslash;n&quot;
)paren
suffix:semicolon
id|amd_clock
op_assign
l_int|33333
suffix:semicolon
)brace
multiline_comment|/*&n; * Print the boot message.&n; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|t
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AMD_IDE: %s (rev %02x) %s controller on pci%s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|t
comma
id|amd_dma
(braket
id|amd_config-&gt;flags
op_amp
id|AMD_UDMA
)braket
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/*&n; * Register /proc/ide/amd74xx entry&n; */
macro_line|#if 0 &amp;&amp; defined(CONFIG_PROC_FS)
r_if
c_cond
(paren
op_logical_neg
id|amd74xx_proc
)paren
(brace
id|amd_base
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
)paren
suffix:semicolon
id|bmide_dev
op_assign
id|dev
suffix:semicolon
id|amd74xx_display_info
op_assign
op_amp
id|amd_get_info
suffix:semicolon
id|amd74xx_proc
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd74xx_ata66_check
r_static
r_int
r_int
id|__init
id|amd74xx_ata66_check
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
)paren
(brace
r_return
(paren
(paren
id|amd_enabled
op_amp
id|amd_80w
)paren
op_rshift
id|hwif-&gt;unit
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|function|amd74xx_init_channel
r_static
r_void
id|__init
id|amd74xx_init_channel
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
)paren
(brace
r_int
id|i
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|amd74xx_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|amd_set_drive
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;io_32bit
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;unmask
op_assign
l_int|1
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hwif-&gt;drives
(braket
id|i
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
id|i
)braket
dot
id|dn
op_assign
id|hwif-&gt;unit
op_star
l_int|2
op_plus
id|i
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_if
c_cond
(paren
id|hwif-&gt;dma_base
)paren
(brace
id|hwif-&gt;highmem
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;XXX_udma
op_assign
id|amd74xx_dmaproc
suffix:semicolon
macro_line|# ifdef CONFIG_IDEDMA_AUTO
r_if
c_cond
(paren
op_logical_neg
id|noautodma
)paren
id|hwif-&gt;autodma
op_assign
l_int|1
suffix:semicolon
macro_line|# endif
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * We allow the BM-DMA driver only work on enabled interfaces.&n; */
DECL|function|amd74xx_init_dma
r_static
r_void
id|__init
id|amd74xx_init_dma
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
comma
r_int
r_int
id|dmabase
)paren
(brace
r_if
c_cond
(paren
(paren
id|amd_enabled
op_rshift
id|ch-&gt;unit
)paren
op_amp
l_int|1
)paren
id|ata_init_dma
c_func
(paren
id|ch
comma
id|dmabase
)paren
suffix:semicolon
)brace
multiline_comment|/* module data table */
DECL|variable|__initdata
r_static
r_struct
id|ata_pci_device
id|chipsets
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_AMD
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_AMD_COBRA_7401
comma
id|init_chipset
suffix:colon
id|amd74xx_init_chipset
comma
id|ata66_check
suffix:colon
id|amd74xx_ata66_check
comma
id|init_channel
suffix:colon
id|amd74xx_init_channel
comma
id|init_dma
suffix:colon
id|amd74xx_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x40
comma
l_int|0x02
comma
l_int|0x02
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_AMD
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_AMD_VIPER_7409
comma
id|init_chipset
suffix:colon
id|amd74xx_init_chipset
comma
id|ata66_check
suffix:colon
id|amd74xx_ata66_check
comma
id|init_channel
suffix:colon
id|amd74xx_init_channel
comma
id|init_dma
suffix:colon
id|amd74xx_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x40
comma
l_int|0x02
comma
l_int|0x02
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_AMD
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_AMD_VIPER_7411
comma
id|init_chipset
suffix:colon
id|amd74xx_init_chipset
comma
id|ata66_check
suffix:colon
id|amd74xx_ata66_check
comma
id|init_channel
suffix:colon
id|amd74xx_init_channel
comma
id|init_dma
suffix:colon
id|amd74xx_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x40
comma
l_int|0x02
comma
l_int|0x02
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_AMD
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_AMD_OPUS_7441
comma
id|init_chipset
suffix:colon
id|amd74xx_init_chipset
comma
id|ata66_check
suffix:colon
id|amd74xx_ata66_check
comma
id|init_channel
suffix:colon
id|amd74xx_init_channel
comma
id|init_dma
suffix:colon
id|amd74xx_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x40
comma
l_int|0x02
comma
l_int|0x02
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_AMD
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_AMD_8111_IDE
comma
id|init_chipset
suffix:colon
id|amd74xx_init_chipset
comma
id|ata66_check
suffix:colon
id|amd74xx_ata66_check
comma
id|init_channel
suffix:colon
id|amd74xx_init_channel
comma
id|init_dma
suffix:colon
id|amd74xx_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x40
comma
l_int|0x02
comma
l_int|0x02
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_NVIDIA
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_NVIDIA_NFORCE_IDE
comma
id|init_chipset
suffix:colon
id|amd74xx_init_chipset
comma
id|ata66_check
suffix:colon
id|amd74xx_ata66_check
comma
id|init_channel
suffix:colon
id|amd74xx_init_channel
comma
id|init_dma
suffix:colon
id|amd74xx_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
comma
)brace
suffix:semicolon
DECL|function|init_amd74xx
r_int
id|__init
id|init_amd74xx
c_func
(paren
r_void
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
id|ARRAY_SIZE
c_func
(paren
id|chipsets
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
id|ata_register_chipset
c_func
(paren
op_amp
id|chipsets
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
