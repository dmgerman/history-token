multiline_comment|/*&n; * $Id: piix.c,v 1.3 2002/03/29 16:06:06 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Andrzej Krzysztofowicz&n; *      Andre Hedrick&n; *&n; *  Thanks to Daniela Egbert for advice on PIIX bugs.&n; */
multiline_comment|/*&n; * Intel PIIX/ICH and Efar Victory66 IDE driver for Linux.&n; *&n; * UDMA66 and higher modes are autoenabled only in case the BIOS has detected a&n; * 80 wire cable. To ignore the BIOS data and assume the cable is present, use&n; * &squot;ide0=ata66&squot; or &squot;ide1=ata66&squot; on the kernel command line.&n; */
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
DECL|macro|PIIX_IDETIM0
mdefine_line|#define PIIX_IDETIM0&t;&t;0x40
DECL|macro|PIIX_IDETIM1
mdefine_line|#define PIIX_IDETIM1&t;&t;0x42
DECL|macro|PIIX_SIDETIM
mdefine_line|#define PIIX_SIDETIM&t;&t;0x44
DECL|macro|PIIX_IDESTAT
mdefine_line|#define PIIX_IDESTAT&t;&t;0x47
DECL|macro|PIIX_UDMACTL
mdefine_line|#define PIIX_UDMACTL&t;&t;0x48
DECL|macro|PIIX_UDMATIM
mdefine_line|#define PIIX_UDMATIM&t;&t;0x4a
DECL|macro|PIIX_IDECFG
mdefine_line|#define PIIX_IDECFG&t;&t;0x54
DECL|macro|PIIX_UDMA
mdefine_line|#define PIIX_UDMA&t;&t;0x07
DECL|macro|PIIX_UDMA_NONE
mdefine_line|#define PIIX_UDMA_NONE&t;&t;0x00
DECL|macro|PIIX_UDMA_33
mdefine_line|#define PIIX_UDMA_33&t;&t;0x01
DECL|macro|PIIX_UDMA_66
mdefine_line|#define PIIX_UDMA_66&t;&t;0x02
DECL|macro|PIIX_UDMA_V66
mdefine_line|#define PIIX_UDMA_V66&t;&t;0x03
DECL|macro|PIIX_UDMA_100
mdefine_line|#define PIIX_UDMA_100&t;&t;0x04
DECL|macro|PIIX_NO_SITRE
mdefine_line|#define PIIX_NO_SITRE&t;&t;0x08&t;/* Chip doesn&squot;t have separate slave timing */
DECL|macro|PIIX_PINGPONG
mdefine_line|#define PIIX_PINGPONG&t;&t;0x10&t;/* Enable ping-pong buffers */
DECL|macro|PIIX_VICTORY
mdefine_line|#define PIIX_VICTORY&t;&t;0x20&t;/* Efar Victory66 has a different UDMA setup */
DECL|macro|PIIX_CHECK_REV
mdefine_line|#define PIIX_CHECK_REV&t;&t;0x40&t;/* May be a buggy revision of PIIX */
DECL|macro|PIIX_NODMA
mdefine_line|#define PIIX_NODMA&t;&t;0x80&t;/* Don&squot;t do DMA with this chip */
multiline_comment|/*&n; * Intel IDE chips&n; */
DECL|struct|piix_ide_chip
r_static
r_struct
id|piix_ide_chip
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|variable|piix_ide_chips
)brace
id|piix_ide_chips
(braket
)braket
op_assign
(brace
(brace
id|PCI_DEVICE_ID_INTEL_82801CA_11
comma
id|PIIX_UDMA_100
op_or
id|PIIX_PINGPONG
)brace
comma
multiline_comment|/* Intel 82801CA ICH3 */
(brace
id|PCI_DEVICE_ID_INTEL_82801CA_10
comma
id|PIIX_UDMA_100
op_or
id|PIIX_PINGPONG
)brace
comma
multiline_comment|/* Intel 82801CAM ICH3-M */
(brace
id|PCI_DEVICE_ID_INTEL_82801BA_9
comma
id|PIIX_UDMA_100
op_or
id|PIIX_PINGPONG
)brace
comma
multiline_comment|/* Intel 82801BA ICH2 */
(brace
id|PCI_DEVICE_ID_INTEL_82801BA_8
comma
id|PIIX_UDMA_100
op_or
id|PIIX_PINGPONG
)brace
comma
multiline_comment|/* Intel 82801BAM ICH2-M */
(brace
id|PCI_DEVICE_ID_INTEL_82801AB_1
comma
id|PIIX_UDMA_33
op_or
id|PIIX_PINGPONG
)brace
comma
multiline_comment|/* Intel 82801AB ICH0 */
(brace
id|PCI_DEVICE_ID_INTEL_82801AA_1
comma
id|PIIX_UDMA_66
op_or
id|PIIX_PINGPONG
)brace
comma
multiline_comment|/* Intel 82801AA ICH */
(brace
id|PCI_DEVICE_ID_INTEL_82372FB_1
comma
id|PIIX_UDMA_66
)brace
comma
multiline_comment|/* Intel 82372FB PIIX5 */
(brace
id|PCI_DEVICE_ID_INTEL_82443MX_1
comma
id|PIIX_UDMA_33
)brace
comma
multiline_comment|/* Intel 82443MX MPIIX4 */
(brace
id|PCI_DEVICE_ID_INTEL_82371AB
comma
id|PIIX_UDMA_33
)brace
comma
multiline_comment|/* Intel 82371AB/EB PIIX4/4E */
(brace
id|PCI_DEVICE_ID_INTEL_82371SB_1
comma
id|PIIX_UDMA_NONE
)brace
comma
multiline_comment|/* Intel 82371SB PIIX3 */
(brace
id|PCI_DEVICE_ID_INTEL_82371FB_1
comma
id|PIIX_UDMA_NONE
op_or
id|PIIX_NO_SITRE
op_or
id|PIIX_CHECK_REV
)brace
comma
multiline_comment|/* Intel 82371FB PIIX */
(brace
id|PCI_DEVICE_ID_EFAR_SLC90E66_1
comma
id|PIIX_UDMA_V66
op_or
id|PIIX_VICTORY
)brace
comma
multiline_comment|/* Efar Victory66 */
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|piix_config
r_static
r_struct
id|piix_ide_chip
op_star
id|piix_config
suffix:semicolon
DECL|variable|piix_enabled
r_static
r_int
r_char
id|piix_enabled
suffix:semicolon
DECL|variable|piix_80w
r_static
r_int
r_int
id|piix_80w
suffix:semicolon
DECL|variable|piix_clock
r_static
r_int
r_int
id|piix_clock
suffix:semicolon
DECL|variable|piix_dma
r_static
r_char
op_star
id|piix_dma
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
l_string|&quot;UDMA66&quot;
comma
l_string|&quot;UDMA100&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * PIIX/ICH /proc entry.&n; */
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|piix_proc
id|byte
id|piix_proc
suffix:semicolon
DECL|variable|piix_base
r_int
id|piix_base
suffix:semicolon
DECL|variable|bmide_dev
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
id|piix_display_info
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
DECL|macro|piix_print
mdefine_line|#define piix_print(format, arg...) p += sprintf(p, format &quot;&bslash;n&quot; , ## arg)
DECL|macro|piix_print_drive
mdefine_line|#define piix_print_drive(name, format, arg...)&bslash;&n;&t;p += sprintf(p, name); for (i = 0; i &lt; 4; i++) p += sprintf(p, format, ## arg); p += sprintf(p, &quot;&bslash;n&quot;);
DECL|function|piix_get_info
r_static
r_int
id|piix_get_info
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
id|dmaen
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
id|i
comma
id|u
suffix:semicolon
r_int
r_int
id|c
comma
id|d
comma
id|e
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
id|piix_print
c_func
(paren
l_string|&quot;----------PIIX BusMastering IDE Configuration---------------&quot;
)paren
suffix:semicolon
id|piix_print
c_func
(paren
l_string|&quot;Driver Version:                     1.3&quot;
)paren
suffix:semicolon
id|piix_print
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
id|piix_print
c_func
(paren
l_string|&quot;Revision:                           IDE %#x&quot;
comma
id|t
)paren
suffix:semicolon
id|piix_print
c_func
(paren
l_string|&quot;Highest DMA rate:                   %s&quot;
comma
id|piix_config-&gt;flags
op_amp
id|PIIX_NODMA
ques
c_cond
l_string|&quot;No DMA&quot;
suffix:colon
id|piix_dma
(braket
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)braket
)paren
suffix:semicolon
id|piix_print
c_func
(paren
l_string|&quot;BM-DMA base:                        %#x&quot;
comma
id|piix_base
)paren
suffix:semicolon
id|piix_print
c_func
(paren
l_string|&quot;PCI clock:                          %d.%dMHz&quot;
comma
id|piix_clock
op_div
l_int|1000
comma
id|piix_clock
op_div
l_int|100
op_mod
l_int|10
)paren
suffix:semicolon
id|piix_print
c_func
(paren
l_string|&quot;-----------------------Primary IDE-------Secondary IDE------&quot;
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PIIX_IDETIM0
comma
op_amp
id|d
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PIIX_IDETIM1
comma
op_amp
id|e
)paren
suffix:semicolon
id|piix_print
c_func
(paren
l_string|&quot;Enabled:               %10s%20s&quot;
comma
(paren
id|d
op_amp
l_int|0x8000
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|e
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
id|c
op_assign
id|inb
c_func
(paren
id|piix_base
op_plus
l_int|0x02
)paren
op_or
(paren
id|inb
c_func
(paren
id|piix_base
op_plus
l_int|0x0a
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|piix_print
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
id|piix_print
c_func
(paren
l_string|&quot;Cable Type:            %10s%20s&quot;
comma
(paren
id|piix_80w
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
id|piix_80w
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
id|piix_clock
)paren
r_return
id|p
op_minus
id|buffer
suffix:semicolon
id|piix_print
c_func
(paren
l_string|&quot;-------------------drive0----drive1----drive2----drive3-----&quot;
)paren
suffix:semicolon
id|piix_print_drive
c_func
(paren
l_string|&quot;Prefetch+Post: &quot;
comma
l_string|&quot;%10s&quot;
comma
(paren
(paren
(paren
id|i
op_amp
l_int|2
)paren
ques
c_cond
id|d
suffix:colon
id|e
)paren
op_amp
(paren
l_int|1
op_lshift
(paren
l_int|2
op_plus
(paren
(paren
id|i
op_amp
l_int|1
)paren
op_lshift
l_int|2
)paren
)paren
)paren
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
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
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PIIX_IDETIM0
op_plus
(paren
id|i
op_amp
l_int|2
)paren
comma
op_amp
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|piix_config-&gt;flags
op_amp
id|PIIX_NO_SITRE
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PIIX_SIDETIM
comma
op_amp
id|t
)paren
suffix:semicolon
id|umul
op_assign
l_int|4
suffix:semicolon
id|udma
(braket
id|i
)braket
op_assign
id|uen
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|active
(braket
id|i
)braket
op_assign
l_int|12
suffix:semicolon
id|recover
(braket
id|i
)braket
op_assign
l_int|18
suffix:semicolon
r_switch
c_cond
(paren
id|i
op_amp
l_int|1
)paren
(brace
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
op_complement
id|d
op_amp
l_int|0x10
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
op_complement
id|piix_config-&gt;flags
op_amp
id|PIIX_NO_SITRE
)paren
op_logical_and
(paren
id|d
op_amp
l_int|0x4000
)paren
)paren
(brace
id|active
(braket
id|i
)braket
op_assign
l_int|5
op_minus
(paren
(paren
id|t
op_rshift
(paren
(paren
(paren
id|i
op_amp
l_int|2
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|2
)paren
)paren
op_amp
l_int|3
)paren
suffix:semicolon
id|recover
(braket
id|i
)braket
op_assign
l_int|4
op_minus
(paren
(paren
id|t
op_rshift
(paren
(paren
(paren
id|i
op_amp
l_int|2
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|0
)paren
)paren
op_amp
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
op_complement
id|d
op_amp
l_int|0x01
)paren
r_break
suffix:semicolon
id|active
(braket
id|i
)braket
op_assign
l_int|5
op_minus
(paren
(paren
id|d
op_rshift
l_int|12
)paren
op_amp
l_int|3
)paren
suffix:semicolon
id|recover
(braket
id|i
)braket
op_assign
l_int|4
op_minus
(paren
(paren
id|d
op_rshift
l_int|8
)paren
op_amp
l_int|3
)paren
suffix:semicolon
)brace
id|dmaen
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
id|cycle
(braket
id|i
)braket
op_assign
l_int|1000000
op_div
id|piix_clock
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
id|speed
(braket
id|i
)braket
op_assign
l_int|2
op_star
id|piix_clock
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
)paren
r_continue
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PIIX_UDMACTL
comma
op_amp
id|t
)paren
suffix:semicolon
id|uen
(braket
id|i
)braket
op_assign
(paren
id|t
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|dmaen
(braket
id|i
)braket
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uen
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PIIX_UDMATIM
comma
op_amp
id|e
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PIIX_IDECFG
comma
op_amp
id|u
)paren
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|piix_config-&gt;flags
op_amp
id|PIIX_VICTORY
)paren
(brace
r_if
c_cond
(paren
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
op_ge
id|PIIX_UDMA_66
op_logical_and
(paren
id|u
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
id|umul
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
op_ge
id|PIIX_UDMA_100
op_logical_and
(paren
id|u
op_amp
(paren
l_int|1
op_lshift
(paren
id|i
op_plus
l_int|12
)paren
)paren
)paren
)paren
id|umul
op_assign
l_int|1
suffix:semicolon
id|udma
(braket
id|i
)braket
op_assign
(paren
l_int|4
op_minus
(paren
(paren
id|e
op_rshift
(paren
id|i
op_lshift
l_int|2
)paren
)paren
op_amp
l_int|3
)paren
)paren
op_star
id|umul
suffix:semicolon
)brace
r_else
id|udma
(braket
id|i
)braket
op_assign
(paren
l_int|8
op_minus
(paren
(paren
id|e
op_rshift
(paren
id|i
op_lshift
l_int|2
)paren
)paren
op_amp
l_int|7
)paren
)paren
op_star
l_int|2
suffix:semicolon
id|speed
(braket
id|i
)braket
op_assign
l_int|8
op_star
id|piix_clock
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
l_int|250000
op_star
id|udma
(braket
id|i
)braket
op_div
id|piix_clock
suffix:semicolon
)brace
id|piix_print_drive
c_func
(paren
l_string|&quot;Transfer Mode: &quot;
comma
l_string|&quot;%10s&quot;
comma
id|dmaen
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
id|piix_print_drive
c_func
(paren
l_string|&quot;Address Setup: &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000000
op_div
id|piix_clock
)paren
op_star
l_int|3
)paren
suffix:semicolon
id|piix_print_drive
c_func
(paren
l_string|&quot;Cmd Active:    &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000000
op_div
id|piix_clock
)paren
op_star
l_int|12
)paren
suffix:semicolon
id|piix_print_drive
c_func
(paren
l_string|&quot;Cmd Recovery:  &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000000
op_div
id|piix_clock
)paren
op_star
l_int|18
)paren
suffix:semicolon
id|piix_print_drive
c_func
(paren
l_string|&quot;Data Active:   &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000000
op_div
id|piix_clock
)paren
op_star
id|active
(braket
id|i
)braket
)paren
suffix:semicolon
id|piix_print_drive
c_func
(paren
l_string|&quot;Data Recovery: &quot;
comma
l_string|&quot;%8dns&quot;
comma
(paren
l_int|1000000
op_div
id|piix_clock
)paren
op_star
id|recover
(braket
id|i
)braket
)paren
suffix:semicolon
id|piix_print_drive
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
id|piix_print_drive
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
multiline_comment|/*&n; * piix_set_speed() writes timing values to the chipset registers&n; */
DECL|function|piix_set_speed
r_static
r_void
id|piix_set_speed
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
comma
r_int
id|umul
)paren
(brace
r_int
r_int
id|t
suffix:semicolon
r_int
r_char
id|u
suffix:semicolon
r_int
r_int
id|c
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PIIX_IDETIM0
op_plus
(paren
id|dn
op_amp
l_int|2
)paren
comma
op_amp
id|t
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dn
op_amp
l_int|1
)paren
(brace
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|timing-&gt;cycle
OG
l_int|9
)paren
(brace
id|t
op_and_assign
op_complement
l_int|0x30
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|piix_config-&gt;flags
op_amp
id|PIIX_NO_SITRE
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PIIX_SIDETIM
comma
op_amp
id|u
)paren
suffix:semicolon
id|u
op_and_assign
op_complement
(paren
l_int|0xf
op_lshift
(paren
(paren
id|dn
op_amp
l_int|2
)paren
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
id|t
op_or_assign
l_int|0x30
suffix:semicolon
id|u
op_or_assign
(paren
l_int|4
op_minus
id|FIT
c_func
(paren
id|timing-&gt;recover
comma
l_int|1
comma
l_int|4
)paren
)paren
op_lshift
(paren
(paren
id|dn
op_amp
l_int|2
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|u
op_or_assign
(paren
l_int|5
op_minus
id|FIT
c_func
(paren
id|timing-&gt;active
comma
l_int|2
comma
l_int|5
)paren
)paren
op_lshift
(paren
(paren
(paren
id|dn
op_amp
l_int|2
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|2
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PIIX_SIDETIM
comma
id|u
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
(paren
op_complement
id|dn
op_amp
l_int|1
)paren
op_logical_and
id|timing-&gt;cycle
OG
l_int|9
)paren
(brace
id|t
op_and_assign
op_complement
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
)brace
id|t
op_and_assign
l_int|0xccff
suffix:semicolon
id|t
op_or_assign
l_int|0x03
op_lshift
(paren
(paren
id|dn
op_amp
l_int|1
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|t
op_or_assign
(paren
l_int|4
op_minus
id|FIT
c_func
(paren
id|timing-&gt;recover
comma
l_int|1
comma
l_int|4
)paren
)paren
op_lshift
l_int|8
suffix:semicolon
id|t
op_or_assign
(paren
l_int|5
op_minus
id|FIT
c_func
(paren
id|timing-&gt;active
comma
l_int|2
comma
l_int|5
)paren
)paren
op_lshift
l_int|12
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PIIX_IDETIM0
op_plus
(paren
id|dn
op_amp
l_int|2
)paren
comma
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
)paren
r_return
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PIIX_UDMACTL
comma
op_amp
id|u
)paren
suffix:semicolon
id|u
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|dn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timing-&gt;udma
)paren
(brace
id|u
op_or_assign
l_int|1
op_lshift
id|dn
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PIIX_UDMATIM
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_VICTORY
)paren
(brace
id|t
op_and_assign
op_complement
(paren
l_int|0x07
op_lshift
(paren
id|dn
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|t
op_or_assign
(paren
l_int|8
op_minus
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|8
)paren
)paren
op_lshift
(paren
id|dn
op_lshift
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|t
op_and_assign
op_complement
(paren
l_int|0x03
op_lshift
(paren
id|dn
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|t
op_or_assign
(paren
l_int|4
op_minus
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|4
)paren
)paren
op_lshift
(paren
id|dn
op_lshift
l_int|2
)paren
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PIIX_UDMATIM
comma
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
OG
id|PIIX_UDMA_33
op_logical_and
op_complement
id|piix_config-&gt;flags
op_amp
id|PIIX_VICTORY
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PIIX_IDECFG
comma
op_amp
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
OG
id|PIIX_UDMA_66
)paren
id|c
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|dn
op_plus
l_int|12
)paren
)paren
suffix:semicolon
id|c
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|dn
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|umul
)paren
(brace
r_case
l_int|2
suffix:colon
id|c
op_or_assign
l_int|1
op_lshift
id|dn
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|c
op_or_assign
l_int|1
op_lshift
(paren
id|dn
op_plus
l_int|12
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PIIX_IDECFG
comma
id|c
)paren
suffix:semicolon
)brace
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PIIX_UDMACTL
comma
id|u
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * piix_set_drive() computes timing values configures the drive and&n; * the chipset to a desired transfer mode. It also can be called&n; * by upper layers.&n; */
DECL|function|piix_set_drive
r_static
r_int
id|piix_set_drive
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
id|err
comma
id|T
comma
id|UT
comma
id|umul
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
(paren
id|err
op_assign
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|umul
op_assign
id|min
c_func
(paren
(paren
id|speed
OG
id|XFER_UDMA_4
)paren
ques
c_cond
l_int|4
suffix:colon
(paren
(paren
id|speed
OG
id|XFER_UDMA_2
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
)paren
comma
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_VICTORY
)paren
id|umul
op_assign
l_int|2
suffix:semicolon
id|T
op_assign
l_int|1000000000
op_div
id|piix_clock
suffix:semicolon
id|UT
op_assign
id|umul
ques
c_cond
(paren
id|T
op_div
id|umul
)paren
suffix:colon
l_int|0
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
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_NO_SITRE
)paren
op_logical_and
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
r_if
c_cond
(paren
id|t.cycle
op_le
l_int|9
op_logical_and
id|p.cycle
op_le
l_int|9
)paren
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
id|IDE_TIMING_ALL
)paren
suffix:semicolon
)brace
id|piix_set_speed
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
id|drive-&gt;dn
comma
op_amp
id|t
comma
id|umul
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
multiline_comment|/*&n; * piix_tune_drive() is a callback from upper layers for&n; * PIO-only tuning.&n; */
DECL|function|piix_tune_drive
r_static
r_void
id|piix_tune_drive
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
id|piix_enabled
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
id|piix_set_drive
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
id|piix_set_drive
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
multiline_comment|/*&n; * piix_dmaproc() is a callback from upper layers that can do&n; * a lot, but we use it for DMA/PIO tuning only, delegating everything&n; * else to the default ide_dmaproc().&n; */
DECL|function|piix_dmaproc
r_int
id|piix_dmaproc
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
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_NODMA
ques
c_cond
l_int|0
suffix:colon
(paren
id|XFER_SWDMA
op_or
id|XFER_MWDMA
op_or
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
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
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
op_ge
id|PIIX_UDMA_66
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
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
op_ge
id|PIIX_UDMA_100
ques
c_cond
id|XFER_UDMA_100
suffix:colon
l_int|0
)paren
)paren
)paren
)paren
suffix:semicolon
id|piix_set_drive
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
id|drive-&gt;channel-&gt;autodma
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
DECL|function|pci_init_piix
r_int
r_int
id|__init
id|pci_init_piix
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
r_int
r_int
id|u
suffix:semicolon
r_int
r_int
id|w
suffix:semicolon
r_int
r_char
id|t
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n; * Find out which Intel IDE this is.&n; */
r_for
c_loop
(paren
id|piix_config
op_assign
id|piix_ide_chips
suffix:semicolon
id|piix_config-&gt;id
op_ne
l_int|0
suffix:semicolon
op_increment
id|piix_config
)paren
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
id|piix_config-&gt;id
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|piix_config-&gt;id
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PIIX: Unknown PIIX/ICH chip %#x, contact Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&bslash;n&quot;
comma
id|dev-&gt;device
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n; * Check for possibly broken DMA configs.&n; */
(brace
r_struct
id|pci_dev
op_star
id|orion
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_CHECK_REV
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
id|t
OL
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PIIX: Found buggy old PIIX rev %#x, disabling DMA&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
id|piix_config-&gt;flags
op_or_assign
id|PIIX_NODMA
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|orion
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82454GX
comma
l_int|NULL
)paren
)paren
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|orion
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
OL
l_int|4
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PIIX: Found buggy 82454GX Orion bridge rev %#x, disabling DMA&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
id|piix_config-&gt;flags
op_or_assign
id|PIIX_NODMA
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Check 80-wire cable presence.&n; */
r_switch
c_cond
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)paren
(brace
r_case
id|PIIX_UDMA_66
suffix:colon
r_case
id|PIIX_UDMA_100
suffix:colon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PIIX_IDECFG
comma
op_amp
id|u
)paren
suffix:semicolon
id|piix_80w
op_assign
(paren
(paren
id|u
op_amp
l_int|0x30
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
l_int|0xc0
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIIX_UDMA_V66
suffix:colon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PIIX_IDESTAT
comma
op_amp
id|t
)paren
suffix:semicolon
id|piix_80w
op_assign
(paren
(paren
id|t
op_amp
l_int|2
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
id|t
op_amp
l_int|1
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable ping-pong buffers where applicable.&n; */
r_if
c_cond
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_PINGPONG
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PIIX_IDECFG
comma
op_amp
id|u
)paren
suffix:semicolon
id|u
op_or_assign
l_int|0x400
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PIIX_IDECFG
comma
id|u
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Detect enabled interfaces, enable slave separate timing if possible.&n; */
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
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PIIX_IDETIM0
op_plus
(paren
id|i
op_lshift
l_int|1
)paren
comma
op_amp
id|w
)paren
suffix:semicolon
id|piix_enabled
op_or_assign
(paren
id|w
op_amp
l_int|0x8000
)paren
ques
c_cond
(paren
l_int|1
op_lshift
id|i
)paren
suffix:colon
l_int|0
suffix:semicolon
id|w
op_and_assign
l_int|0x8c00
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|piix_config-&gt;flags
op_amp
id|PIIX_NO_SITRE
)paren
id|w
op_or_assign
l_int|0x4000
suffix:semicolon
id|w
op_or_assign
l_int|0x44
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PIIX_IDETIM0
op_plus
(paren
id|i
op_lshift
l_int|1
)paren
comma
id|w
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Determine the system bus clock.&n; */
id|piix_clock
op_assign
id|system_bus_speed
op_star
l_int|1000
suffix:semicolon
r_switch
c_cond
(paren
id|piix_clock
)paren
(brace
r_case
l_int|33000
suffix:colon
id|piix_clock
op_assign
l_int|33333
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|37000
suffix:colon
id|piix_clock
op_assign
l_int|37500
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|41000
suffix:colon
id|piix_clock
op_assign
l_int|41666
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|piix_clock
template_param
l_int|50000
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PIIX: User given PCI clock speed impossible (%d), using 33 MHz instead.&bslash;n&quot;
comma
id|piix_clock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PIIX: Use ide0=ata66 if you want to assume 80-wire cable&bslash;n&quot;
)paren
suffix:semicolon
id|piix_clock
op_assign
l_int|33333
suffix:semicolon
)brace
multiline_comment|/*&n; * Print the boot message.&n; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PIIX: %s %s controller on pci%s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|piix_dma
(braket
id|piix_config-&gt;flags
op_amp
id|PIIX_UDMA
)braket
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/*&n; * Register /proc/ide/piix entry&n; */
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
op_logical_neg
id|piix_proc
)paren
(brace
id|piix_base
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
id|piix_display_info
op_assign
op_amp
id|piix_get_info
suffix:semicolon
id|piix_proc
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ata66_piix
r_int
r_int
id|__init
id|ata66_piix
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
id|piix_enabled
op_amp
id|piix_80w
)paren
op_rshift
id|hwif-&gt;unit
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|function|ide_init_piix
r_void
id|__init
id|ide_init_piix
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
id|piix_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|piix_set_drive
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
id|hwif-&gt;dmaproc
op_assign
op_amp
id|piix_dmaproc
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
multiline_comment|/*&n; * We allow the BM-DMA driver only work on enabled interfaces,&n; * and only if DMA is safe with the chip and bridge.&n; */
DECL|function|ide_dmacapable_piix
r_void
id|__init
id|ide_dmacapable_piix
c_func
(paren
r_struct
id|ata_channel
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
(paren
id|piix_enabled
op_rshift
id|hwif-&gt;unit
)paren
op_amp
l_int|1
)paren
op_logical_and
op_logical_neg
(paren
id|piix_config-&gt;flags
op_amp
id|PIIX_NODMA
)paren
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
