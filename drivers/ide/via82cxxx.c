multiline_comment|/*&n; * $Id: via82cxxx.c,v 3.29 2001/09/10 10:06:00 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Michel Aubry&n; *&t;Jeff Garzik&n; *&t;Andre Hedrick&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * VIA IDE driver for Linux. Supports&n; *&n; *   vt82c576, vt82c586, vt82c586a, vt82c586b, vt82c596a, vt82c596b,&n; *   vt82c686, vt82c686a, vt82c686b, vt8231, vt8233&n; *&n; * southbridges, which can be found in&n; *&n; *  VIA Apollo Master, VP, VP2, VP2/97, VP3, VPX, VPX/97, MVP3, MVP4, P6, Pro,&n; *    ProII, ProPlus, Pro133, Pro133+, Pro133A, Pro133A Dual, Pro133T, Pro133Z,&n; *    PLE133, PLE133T, Pro266, Pro266T, ProP4X266, PM601, PM133, PN133, PL133T,&n; *    PX266, PM266, KX133, KT133, KT133A, KLE133, KT266, KX266, KM133, KM133A,&n; *    KL133, KN133, KM266&n; *  PC-Chips VXPro, VXPro+, VXTwo, TXPro-III, TXPro-AGP, AGPPro, ViaGra, BXToo,&n; *    BXTel, BXpert&n; *  AMD 640, 640 AGP, 750 IronGate, 760, 760MP&n; *  ETEQ 6618, 6628, 6629, 6638&n; *  Micron Samurai&n; *&n; * chipsets. Supports&n; *&n; *   PIO 0-5, MWDMA 0-2, SWDMA 0-2 and UDMA 0-5&n; *&n; * (this includes UDMA33, 66 and 100) modes. UDMA66 and higher modes are&n; * autoenabled only in case the BIOS has detected a 80 wire cable. To ignore&n; * the BIOS data and assume the cable is present, use &squot;ide0=ata66&squot; or&n; * &squot;ide1=ata66&squot; on the kernel command line.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide-timing.h&quot;
DECL|macro|VIA_IDE_ENABLE
mdefine_line|#define VIA_IDE_ENABLE&t;&t;0x40
DECL|macro|VIA_IDE_CONFIG
mdefine_line|#define VIA_IDE_CONFIG&t;&t;0x41
DECL|macro|VIA_FIFO_CONFIG
mdefine_line|#define VIA_FIFO_CONFIG&t;&t;0x43
DECL|macro|VIA_MISC_1
mdefine_line|#define VIA_MISC_1&t;&t;0x44
DECL|macro|VIA_MISC_2
mdefine_line|#define VIA_MISC_2&t;&t;0x45
DECL|macro|VIA_MISC_3
mdefine_line|#define VIA_MISC_3&t;&t;0x46
DECL|macro|VIA_DRIVE_TIMING
mdefine_line|#define VIA_DRIVE_TIMING&t;0x48
DECL|macro|VIA_8BIT_TIMING
mdefine_line|#define VIA_8BIT_TIMING&t;&t;0x4e
DECL|macro|VIA_ADDRESS_SETUP
mdefine_line|#define VIA_ADDRESS_SETUP&t;0x4c
DECL|macro|VIA_UDMA_TIMING
mdefine_line|#define VIA_UDMA_TIMING&t;&t;0x50
DECL|macro|VIA_UDMA
mdefine_line|#define VIA_UDMA&t;&t;0x007
DECL|macro|VIA_UDMA_NONE
mdefine_line|#define VIA_UDMA_NONE&t;&t;0x000
DECL|macro|VIA_UDMA_33
mdefine_line|#define VIA_UDMA_33&t;&t;0x001
DECL|macro|VIA_UDMA_66
mdefine_line|#define VIA_UDMA_66&t;&t;0x002
DECL|macro|VIA_UDMA_100
mdefine_line|#define VIA_UDMA_100&t;&t;0x003
DECL|macro|VIA_BAD_PREQ
mdefine_line|#define VIA_BAD_PREQ&t;&t;0x010&t;/* Crashes if PREQ# till DDACK# set */
DECL|macro|VIA_BAD_CLK66
mdefine_line|#define VIA_BAD_CLK66&t;&t;0x020&t;/* 66 MHz clock doesn&squot;t work correctly */
DECL|macro|VIA_SET_FIFO
mdefine_line|#define VIA_SET_FIFO&t;&t;0x040&t;/* Needs to have FIFO split set */
DECL|macro|VIA_NO_UNMASK
mdefine_line|#define VIA_NO_UNMASK&t;&t;0x080&t;/* Doesn&squot;t work with IRQ unmasking on */
multiline_comment|/*&n; * VIA SouthBridge chips.&n; */
DECL|struct|via_isa_bridge
r_static
r_struct
id|via_isa_bridge
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|rev_min
r_int
r_char
id|rev_min
suffix:semicolon
DECL|member|rev_max
r_int
r_char
id|rev_max
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|variable|via_isa_bridges
)brace
id|via_isa_bridges
(braket
)braket
op_assign
(brace
macro_line|#ifdef FUTURE_BRIDGES
(brace
l_string|&quot;vt8237&quot;
comma
id|PCI_DEVICE_ID_VIA_8237
comma
l_int|0x00
comma
l_int|0x2f
comma
id|VIA_UDMA_100
)brace
comma
(brace
l_string|&quot;vt8235&quot;
comma
id|PCI_DEVICE_ID_VIA_8235
comma
l_int|0x00
comma
l_int|0x2f
comma
id|VIA_UDMA_100
)brace
comma
(brace
l_string|&quot;vt8233c&quot;
comma
id|PCI_DEVICE_ID_VIA_8233C
comma
l_int|0x00
comma
l_int|0x2f
comma
id|VIA_UDMA_100
)brace
comma
macro_line|#endif
(brace
l_string|&quot;vt8233&quot;
comma
id|PCI_DEVICE_ID_VIA_8233_0
comma
l_int|0x00
comma
l_int|0x2f
comma
id|VIA_UDMA_100
)brace
comma
(brace
l_string|&quot;vt8231&quot;
comma
id|PCI_DEVICE_ID_VIA_8231
comma
l_int|0x00
comma
l_int|0x2f
comma
id|VIA_UDMA_100
)brace
comma
(brace
l_string|&quot;vt82c686b&quot;
comma
id|PCI_DEVICE_ID_VIA_82C686
comma
l_int|0x40
comma
l_int|0x4f
comma
id|VIA_UDMA_100
)brace
comma
(brace
l_string|&quot;vt82c686a&quot;
comma
id|PCI_DEVICE_ID_VIA_82C686
comma
l_int|0x10
comma
l_int|0x2f
comma
id|VIA_UDMA_66
)brace
comma
(brace
l_string|&quot;vt82c686&quot;
comma
id|PCI_DEVICE_ID_VIA_82C686
comma
l_int|0x00
comma
l_int|0x0f
comma
id|VIA_UDMA_33
op_or
id|VIA_BAD_CLK66
)brace
comma
(brace
l_string|&quot;vt82c596b&quot;
comma
id|PCI_DEVICE_ID_VIA_82C596
comma
l_int|0x10
comma
l_int|0x2f
comma
id|VIA_UDMA_66
)brace
comma
(brace
l_string|&quot;vt82c596a&quot;
comma
id|PCI_DEVICE_ID_VIA_82C596
comma
l_int|0x00
comma
l_int|0x0f
comma
id|VIA_UDMA_33
op_or
id|VIA_BAD_CLK66
)brace
comma
(brace
l_string|&quot;vt82c586b&quot;
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
l_int|0x47
comma
l_int|0x4f
comma
id|VIA_UDMA_33
op_or
id|VIA_SET_FIFO
)brace
comma
(brace
l_string|&quot;vt82c586b&quot;
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
l_int|0x40
comma
l_int|0x46
comma
id|VIA_UDMA_33
op_or
id|VIA_SET_FIFO
op_or
id|VIA_BAD_PREQ
)brace
comma
(brace
l_string|&quot;vt82c586b&quot;
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
l_int|0x30
comma
l_int|0x3f
comma
id|VIA_UDMA_33
op_or
id|VIA_SET_FIFO
)brace
comma
(brace
l_string|&quot;vt82c586a&quot;
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
l_int|0x20
comma
l_int|0x2f
comma
id|VIA_UDMA_33
op_or
id|VIA_SET_FIFO
)brace
comma
(brace
l_string|&quot;vt82c586&quot;
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
l_int|0x00
comma
l_int|0x0f
comma
id|VIA_UDMA_NONE
op_or
id|VIA_SET_FIFO
)brace
comma
(brace
l_string|&quot;vt82c576&quot;
comma
id|PCI_DEVICE_ID_VIA_82C576
comma
l_int|0x00
comma
l_int|0x2f
comma
id|VIA_UDMA_NONE
op_or
id|VIA_SET_FIFO
op_or
id|VIA_NO_UNMASK
)brace
comma
(brace
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|variable|via_config
r_static
r_struct
id|via_isa_bridge
op_star
id|via_config
suffix:semicolon
DECL|variable|via_enabled
r_static
r_int
r_char
id|via_enabled
suffix:semicolon
DECL|variable|via_80w
r_static
r_int
r_int
id|via_80w
suffix:semicolon
DECL|variable|via_clock
r_static
r_int
r_int
id|via_clock
suffix:semicolon
DECL|variable|via_dma
r_static
r_char
op_star
id|via_dma
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
multiline_comment|/*&n; * VIA /proc entry.&n; */
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|via_proc
DECL|variable|via_base
r_int
id|via_proc
comma
id|via_base
suffix:semicolon
DECL|variable|bmide_dev
DECL|variable|isa_dev
r_static
r_struct
id|pci_dev
op_star
id|bmide_dev
comma
op_star
id|isa_dev
suffix:semicolon
r_extern
r_int
(paren
op_star
id|via_display_info
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
DECL|variable|via_control3
r_static
r_char
op_star
id|via_control3
(braket
)braket
op_assign
(brace
l_string|&quot;No limit&quot;
comma
l_string|&quot;64&quot;
comma
l_string|&quot;128&quot;
comma
l_string|&quot;192&quot;
)brace
suffix:semicolon
DECL|macro|via_print
mdefine_line|#define via_print(format, arg...) p += sprintf(p, format &quot;&bslash;n&quot; , ## arg)
DECL|macro|via_print_drive
mdefine_line|#define via_print_drive(name, format, arg...)&bslash;&n;&t;p += sprintf(p, name); for (i = 0; i &lt; 4; i++) p += sprintf(p, format, ## arg); p += sprintf(p, &quot;&bslash;n&quot;);
DECL|function|via_get_info
r_static
r_int
id|via_get_info
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
id|umul
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
comma
id|x
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;----------VIA BusMastering IDE Configuration----------------&quot;
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;Driver Version:                     3.29&quot;
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;South Bridge:                       VIA %s&quot;
comma
id|via_config-&gt;name
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|isa_dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|t
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
id|x
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;Revision:                           ISA %#x IDE %#x&quot;
comma
id|t
comma
id|x
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;Highest DMA rate:                   %s&quot;
comma
id|via_dma
(braket
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)braket
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;BM-DMA base:                        %#x&quot;
comma
id|via_base
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;PCI clock:                          %dMHz&quot;
comma
id|via_clock
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|VIA_MISC_1
comma
op_amp
id|t
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;Master Read  Cycle IRDY:            %dws&quot;
comma
(paren
id|t
op_amp
l_int|64
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;Master Write Cycle IRDY:            %dws&quot;
comma
(paren
id|t
op_amp
l_int|32
)paren
op_rshift
l_int|5
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;BM IDE Status Register Read Retry:  %s&quot;
comma
(paren
id|t
op_amp
l_int|8
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
id|VIA_MISC_3
comma
op_amp
id|t
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;Max DRDY Pulse Width:               %s%s&quot;
comma
id|via_control3
(braket
(paren
id|t
op_amp
l_int|0x03
)paren
)braket
comma
(paren
id|t
op_amp
l_int|0x03
)paren
ques
c_cond
l_string|&quot; PCI clocks&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;-----------------------Primary IDE-------Secondary IDE------&quot;
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;Read DMA FIFO flush:   %10s%20s&quot;
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
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|via_print
c_func
(paren
l_string|&quot;End Sector FIFO flush: %10s%20s&quot;
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
id|VIA_IDE_CONFIG
comma
op_amp
id|t
)paren
suffix:semicolon
id|via_print
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
id|via_print
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
id|VIA_IDE_ENABLE
comma
op_amp
id|t
)paren
suffix:semicolon
id|via_print
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
id|via_base
op_plus
l_int|0x02
)paren
op_or
(paren
id|inb
c_func
(paren
id|via_base
op_plus
l_int|0x0a
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|via_print
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
id|via_print
c_func
(paren
l_string|&quot;Cable Type:            %10s%20s&quot;
comma
(paren
id|via_80w
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
id|via_80w
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
id|via_print
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
id|VIA_ADDRESS_SETUP
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
id|VIA_DRIVE_TIMING
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
id|VIA_8BIT_TIMING
comma
op_amp
id|w
)paren
suffix:semicolon
r_if
c_cond
(paren
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)paren
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|VIA_UDMA_TIMING
comma
op_amp
id|u
)paren
suffix:semicolon
r_else
id|u
op_assign
l_int|0
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
op_plus
l_int|2
suffix:semicolon
id|umul
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
(paren
l_int|3
op_minus
id|i
)paren
op_amp
l_int|2
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0x8
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|2
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
l_int|0x20
)paren
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
id|speed
(braket
id|i
)braket
op_assign
l_int|20
op_star
id|via_clock
op_div
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
suffix:semicolon
id|cycle
(braket
id|i
)braket
op_assign
l_int|1000
op_div
id|via_clock
op_star
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
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uen
(braket
id|i
)braket
op_logical_or
op_logical_neg
id|den
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)paren
(brace
r_case
id|VIA_UDMA_100
suffix:colon
id|speed
(braket
id|i
)braket
op_assign
l_int|60
op_star
id|via_clock
op_div
id|udma
(braket
id|i
)braket
suffix:semicolon
id|cycle
(braket
id|i
)braket
op_assign
l_int|333
op_div
id|via_clock
op_star
id|udma
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_UDMA_66
suffix:colon
id|speed
(braket
id|i
)braket
op_assign
l_int|40
op_star
id|via_clock
op_div
(paren
id|udma
(braket
id|i
)braket
op_star
id|umul
(braket
id|i
)braket
)paren
suffix:semicolon
id|cycle
(braket
id|i
)braket
op_assign
l_int|500
op_div
id|via_clock
op_star
(paren
id|udma
(braket
id|i
)braket
op_star
id|umul
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_UDMA_33
suffix:colon
id|speed
(braket
id|i
)braket
op_assign
l_int|20
op_star
id|via_clock
op_div
id|udma
(braket
id|i
)braket
suffix:semicolon
id|cycle
(braket
id|i
)braket
op_assign
l_int|1000
op_div
id|via_clock
op_star
id|udma
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|via_print_drive
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
id|via_print_drive
c_func
(paren
l_string|&quot;Address Setup: &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000
op_div
id|via_clock
)paren
op_star
id|setup
(braket
id|i
)braket
)paren
suffix:semicolon
id|via_print_drive
c_func
(paren
l_string|&quot;Cmd Active:    &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000
op_div
id|via_clock
)paren
op_star
id|active8b
(braket
id|i
)braket
)paren
suffix:semicolon
id|via_print_drive
c_func
(paren
l_string|&quot;Cmd Recovery:  &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000
op_div
id|via_clock
)paren
op_star
id|recover8b
(braket
id|i
)braket
)paren
suffix:semicolon
id|via_print_drive
c_func
(paren
l_string|&quot;Data Active:   &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000
op_div
id|via_clock
)paren
op_star
id|active
(braket
id|i
)braket
)paren
suffix:semicolon
id|via_print_drive
c_func
(paren
l_string|&quot;Data Recovery: &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000
op_div
id|via_clock
)paren
op_star
id|recover
(braket
id|i
)braket
)paren
suffix:semicolon
id|via_print_drive
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
id|via_print_drive
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
l_int|10
comma
id|speed
(braket
id|i
)braket
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
multiline_comment|/*&n; * via_set_speed() writes timing values to the chipset registers&n; */
DECL|function|via_set_speed
r_static
r_void
id|via_set_speed
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
id|ide_timing
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
id|VIA_ADDRESS_SETUP
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
id|VIA_ADDRESS_SETUP
comma
id|t
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|VIA_8BIT_TIMING
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
id|VIA_DRIVE_TIMING
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
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)paren
(brace
r_case
id|VIA_UDMA_33
suffix:colon
id|t
op_assign
id|timing-&gt;udma
ques
c_cond
(paren
l_int|0xe0
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
id|VIA_UDMA_66
suffix:colon
id|t
op_assign
id|timing-&gt;udma
ques
c_cond
(paren
l_int|0xe8
op_or
(paren
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|9
)paren
op_minus
l_int|2
)paren
)paren
suffix:colon
l_int|0x0f
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_UDMA_100
suffix:colon
id|t
op_assign
id|timing-&gt;udma
ques
c_cond
(paren
l_int|0xe0
op_or
(paren
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|9
)paren
op_minus
l_int|2
)paren
)paren
suffix:colon
l_int|0x07
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
id|VIA_UDMA_TIMING
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
multiline_comment|/*&n; * via_set_drive() computes timing values configures the drive and&n; * the chipset to a desired transfer mode. It also can be called&n; * by upper layers.&n; */
DECL|function|via_set_drive
r_static
r_int
id|via_set_drive
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
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|drives
op_plus
(paren
op_complement
id|drive-&gt;dn
op_amp
l_int|1
)paren
suffix:semicolon
r_struct
id|ide_timing
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
l_int|1000
op_div
id|via_clock
suffix:semicolon
r_switch
c_cond
(paren
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)paren
(brace
r_case
id|VIA_UDMA_33
suffix:colon
id|UT
op_assign
id|T
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_UDMA_66
suffix:colon
id|UT
op_assign
id|T
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_UDMA_100
suffix:colon
id|UT
op_assign
id|T
op_div
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|UT
op_assign
id|T
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ide_timing_compute
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
id|ide_timing_compute
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
id|ide_timing_merge
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
id|via_set_speed
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
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
multiline_comment|/*&n; * via82cxxx_tune_drive() is a callback from upper layers for&n; * PIO-only tuning.&n; */
DECL|function|via82cxxx_tune_drive
r_static
r_void
id|via82cxxx_tune_drive
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
id|via_enabled
op_rshift
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|channel
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
id|via_set_drive
c_func
(paren
id|drive
comma
id|ide_find_best_mode
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
id|via_set_drive
c_func
(paren
id|drive
comma
id|XFER_PIO_0
op_plus
id|MIN
c_func
(paren
id|pio
comma
l_int|5
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
multiline_comment|/*&n; * via82cxxx_dmaproc() is a callback from upper layers that can do&n; * a lot, but we use it for DMA/PIO tuning only, delegating everything&n; * else to the default ide_dmaproc().&n; */
DECL|function|via82cxxx_dmaproc
r_int
id|via82cxxx_dmaproc
c_func
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|func
op_eq
id|ide_dma_check
)paren
(brace
r_int
id|w80
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|udma_four
suffix:semicolon
r_int
id|speed
op_assign
id|ide_find_best_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
op_or
id|XFER_SWDMA
op_or
id|XFER_MWDMA
op_or
(paren
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
ques
c_cond
id|XFER_UDMA
suffix:colon
l_int|0
)paren
op_or
(paren
id|w80
op_logical_and
(paren
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)paren
op_ge
id|VIA_UDMA_66
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
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)paren
op_ge
id|VIA_UDMA_100
ques
c_cond
id|XFER_UDMA_100
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|via_set_drive
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
id|func
op_assign
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|autodma
op_logical_and
(paren
id|speed
op_amp
id|XFER_MODE
)paren
op_ne
id|XFER_PIO
)paren
ques
c_cond
id|ide_dma_on
suffix:colon
id|ide_dma_off_quietly
suffix:semicolon
)brace
r_return
id|ide_dmaproc
c_func
(paren
id|func
comma
id|drive
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
multiline_comment|/*&n; * The initialization callback. Here we determine the IDE chip type&n; * and initialize its drive independent registers.&n; */
DECL|function|pci_init_via82cxxx
r_int
r_int
id|__init
id|pci_init_via82cxxx
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|pci_dev
op_star
id|isa
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|t
comma
id|v
suffix:semicolon
r_int
r_int
id|u
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n; * Find the ISA bridge to see how good the IDE is.&n; */
r_for
c_loop
(paren
id|via_config
op_assign
id|via_isa_bridges
suffix:semicolon
id|via_config-&gt;id
suffix:semicolon
id|via_config
op_increment
)paren
r_if
c_cond
(paren
(paren
id|isa
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|via_config-&gt;id
comma
l_int|NULL
)paren
)paren
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|isa
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
id|t
op_ge
id|via_config-&gt;rev_min
op_logical_and
id|t
op_le
id|via_config-&gt;rev_max
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|via_config-&gt;id
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VP_IDE: Unknown VIA SouthBridge, contact Vojtech Pavlik &lt;vojtech@suse.cz&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n; * Check 80-wire cable presence and setup Clk66.&n; */
r_switch
c_cond
(paren
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)paren
(brace
r_case
id|VIA_UDMA_100
suffix:colon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|VIA_UDMA_TIMING
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
(paren
id|u
op_rshift
id|i
)paren
op_amp
l_int|0x10
)paren
op_logical_or
(paren
(paren
(paren
id|u
op_rshift
id|i
)paren
op_amp
l_int|0x20
)paren
op_logical_and
(paren
(paren
(paren
id|u
op_rshift
id|i
)paren
op_amp
l_int|7
)paren
OL
l_int|3
)paren
)paren
)paren
id|via_80w
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
multiline_comment|/* BIOS 80-wire bit or UDMA w/ &lt; 50ns/cycle */
r_break
suffix:semicolon
r_case
id|VIA_UDMA_66
suffix:colon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|VIA_UDMA_TIMING
comma
op_amp
id|u
)paren
suffix:semicolon
multiline_comment|/* Enable Clk66 */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|VIA_UDMA_TIMING
comma
id|u
op_or
l_int|0x80008
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
(paren
id|i
op_amp
l_int|16
)paren
)paren
op_amp
l_int|8
)paren
op_logical_and
(paren
(paren
id|u
op_rshift
id|i
)paren
op_amp
l_int|0x20
)paren
op_logical_and
(paren
(paren
(paren
id|u
op_rshift
id|i
)paren
op_amp
l_int|7
)paren
OL
l_int|2
)paren
)paren
id|via_80w
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
multiline_comment|/* 2x PCI clock and UDMA w/ &lt; 3T/cycle */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|via_config-&gt;flags
op_amp
id|VIA_BAD_CLK66
)paren
(brace
multiline_comment|/* Disable Clk66 */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|VIA_UDMA_TIMING
comma
op_amp
id|u
)paren
suffix:semicolon
multiline_comment|/* Would cause trouble on 596a and 686 */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|VIA_UDMA_TIMING
comma
id|u
op_amp
op_complement
l_int|0x80008
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether interfaces are enabled.&n; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|VIA_IDE_ENABLE
comma
op_amp
id|v
)paren
suffix:semicolon
id|via_enabled
op_assign
(paren
(paren
id|v
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
id|v
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
multiline_comment|/*&n; * Set up FIFO sizes and thresholds.&n; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|VIA_FIFO_CONFIG
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|via_config-&gt;flags
op_amp
id|VIA_BAD_PREQ
)paren
multiline_comment|/* Disable PREQ# till DDACK# */
id|t
op_and_assign
l_int|0x7f
suffix:semicolon
multiline_comment|/* Would crash on 586b rev 41 */
r_if
c_cond
(paren
id|via_config-&gt;flags
op_amp
id|VIA_SET_FIFO
)paren
(brace
multiline_comment|/* Fix FIFO split between channels */
id|t
op_and_assign
(paren
id|t
op_amp
l_int|0x9f
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|via_enabled
)paren
(brace
r_case
l_int|1
suffix:colon
id|t
op_or_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* 16 on primary */
r_case
l_int|2
suffix:colon
id|t
op_or_assign
l_int|0x60
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* 16 on secondary */
r_case
l_int|3
suffix:colon
id|t
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* 8 pri 8 sec */
)brace
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|VIA_FIFO_CONFIG
comma
id|t
)paren
suffix:semicolon
multiline_comment|/*&n; * Determine system bus clock.&n; */
id|via_clock
op_assign
id|system_bus_clock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|via_clock
template_param
l_int|50
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VP_IDE: User given PCI clock speed impossible (%d), using 33 MHz instead.&bslash;n&quot;
comma
id|via_clock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VP_IDE: Use ide0=ata66 if you want to force UDMA66/UDMA100.&bslash;n&quot;
)paren
suffix:semicolon
id|via_clock
op_assign
l_int|33
suffix:semicolon
)brace
multiline_comment|/*&n; * Print the boot message.&n; */
id|pci_read_config_byte
c_func
(paren
id|isa
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
l_string|&quot;VP_IDE: VIA %s (rev %02x) IDE %s controller on pci%s&bslash;n&quot;
comma
id|via_config-&gt;name
comma
id|t
comma
id|via_dma
(braket
id|via_config-&gt;flags
op_amp
id|VIA_UDMA
)braket
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/*&n; * Setup /proc/ide/via entry.&n; */
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
op_logical_neg
id|via_proc
)paren
(brace
id|via_base
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
id|isa_dev
op_assign
id|isa
suffix:semicolon
id|via_display_info
op_assign
op_amp
id|via_get_info
suffix:semicolon
id|via_proc
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ata66_via82cxxx
r_int
r_int
id|__init
id|ata66_via82cxxx
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_return
(paren
(paren
id|via_enabled
op_amp
id|via_80w
)paren
op_rshift
id|hwif-&gt;channel
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|function|ide_init_via82cxxx
r_void
id|__init
id|ide_init_via82cxxx
c_func
(paren
id|ide_hwif_t
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
id|via82cxxx_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|via_set_drive
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
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
id|io_32bit
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
id|i
)braket
dot
id|unmask
op_assign
(paren
id|via_config-&gt;flags
op_amp
id|VIA_NO_UNMASK
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
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
id|hwif-&gt;channel
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
id|hwif-&gt;dmaproc
op_assign
op_amp
id|via82cxxx_dmaproc
suffix:semicolon
macro_line|#ifdef CONFIG_IDEDMA_AUTO
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
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
)brace
multiline_comment|/*&n; * We allow the BM-DMA driver to only work on enabled interfaces.&n; */
DECL|function|ide_dmacapable_via82cxxx
r_void
id|__init
id|ide_dmacapable_via82cxxx
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
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
id|via_enabled
op_rshift
id|hwif-&gt;channel
)paren
op_amp
l_int|1
)paren
id|ide_setup_dma
c_func
(paren
id|hwif
comma
id|dmabase
comma
l_int|8
)paren
suffix:semicolon
)brace
eof
