multiline_comment|/*&n; * triflex.c&n; * &n; * IDE Chipset driver for the Compaq TriFlex IDE controller.&n; * &n; * Known to work with the Compaq Workstation 5x00 series.&n; *&n; * Copyright (C) 2002 Hewlett-Packard Development Group, L.P.&n; * Author: Torben Mathiasen &lt;torben.mathiasen@hp.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; * &n; * Loosely based on the piix &amp; svwks drivers.&n; *&n; * Documentation:&n; *&t;Not publically available.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
macro_line|#include &quot;triflex.h&quot;
DECL|variable|triflex_dev
r_static
r_struct
id|pci_dev
op_star
id|triflex_dev
suffix:semicolon
DECL|function|triflex_get_info
r_static
r_int
id|triflex_get_info
c_func
(paren
r_char
op_star
id|buf
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
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|triflex_dev
suffix:semicolon
r_int
r_int
id|bibma
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
)paren
suffix:semicolon
id|u8
id|c0
op_assign
l_int|0
comma
id|c1
op_assign
l_int|0
suffix:semicolon
id|u32
id|pri_timing
comma
id|sec_timing
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n                                Compaq Triflex Chipset&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x70
comma
op_amp
id|pri_timing
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x74
comma
op_amp
id|sec_timing
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * at that point bibma+0x2 et bibma+0xa are byte registers&n;&t; * to investigate:&n;&t; */
id|c0
op_assign
id|inb
c_func
(paren
(paren
r_int
r_int
)paren
id|bibma
op_plus
l_int|0x02
)paren
suffix:semicolon
id|c1
op_assign
id|inb
c_func
(paren
(paren
r_int
r_int
)paren
id|bibma
op_plus
l_int|0x0a
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- Primary Channel &quot;
l_string|&quot;---------------- Secondary Channel &quot;
l_string|&quot;-------------&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;                %sabled &quot;
l_string|&quot;                        %sabled&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;dis&quot;
suffix:colon
l_string|&quot; en&quot;
comma
(paren
id|c1
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;dis&quot;
suffix:colon
l_string|&quot; en&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- drive0 --------- drive1 &quot;
l_string|&quot;-------- drive0 ---------- drive1 ------&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA enabled:    %s              %s &quot;
l_string|&quot;            %s               %s&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c0
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c1
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c1
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;PIO&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|triflex_tune_chipset
r_static
r_int
id|triflex_tune_chipset
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|xferspeed
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u8
id|channel_offset
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x74
suffix:colon
l_int|0x70
suffix:semicolon
id|u16
id|timing
op_assign
l_int|0
suffix:semicolon
id|u32
id|triflex_timings
op_assign
l_int|0
suffix:semicolon
id|u8
id|unit
op_assign
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
suffix:semicolon
id|u8
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
l_int|0
comma
id|xferspeed
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|channel_offset
comma
op_amp
id|triflex_timings
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
id|XFER_MW_DMA_2
suffix:colon
id|timing
op_assign
l_int|0x0103
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
id|timing
op_assign
l_int|0x0203
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
id|timing
op_assign
l_int|0x0808
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_SW_DMA_2
suffix:colon
r_case
id|XFER_SW_DMA_1
suffix:colon
r_case
id|XFER_SW_DMA_0
suffix:colon
id|timing
op_assign
l_int|0x0f0f
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_4
suffix:colon
id|timing
op_assign
l_int|0x0202
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_3
suffix:colon
id|timing
op_assign
l_int|0x0204
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_2
suffix:colon
id|timing
op_assign
l_int|0x0404
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_1
suffix:colon
id|timing
op_assign
l_int|0x0508
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_0
suffix:colon
id|timing
op_assign
l_int|0x0808
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|triflex_timings
op_and_assign
op_complement
(paren
l_int|0xFFFF
op_lshift
(paren
l_int|16
op_star
id|unit
)paren
)paren
suffix:semicolon
id|triflex_timings
op_or_assign
(paren
id|timing
op_lshift
(paren
l_int|16
op_star
id|unit
)paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|channel_offset
comma
id|triflex_timings
)paren
suffix:semicolon
r_return
(paren
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
)paren
suffix:semicolon
)brace
DECL|function|triflex_tune_drive
r_static
r_void
id|triflex_tune_drive
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
r_int
id|use_pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|4
comma
l_int|NULL
)paren
suffix:semicolon
(paren
r_void
)paren
id|triflex_tune_chipset
c_func
(paren
id|drive
comma
(paren
id|XFER_PIO_0
op_plus
id|use_pio
)paren
)paren
suffix:semicolon
)brace
DECL|function|triflex_config_drive_for_dma
r_static
r_int
id|triflex_config_drive_for_dma
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_int
id|speed
op_assign
id|ide_dma_speed
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* No ultra speeds */
r_if
c_cond
(paren
op_logical_neg
id|speed
)paren
(brace
id|u8
id|pspeed
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
l_int|255
comma
l_int|4
comma
l_int|NULL
)paren
suffix:semicolon
id|speed
op_assign
id|XFER_PIO_0
op_plus
id|pspeed
suffix:semicolon
)brace
(paren
r_void
)paren
id|triflex_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
r_return
id|ide_dma_enable
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|triflex_config_drive_xfer_rate
r_static
r_int
id|triflex_config_drive_xfer_rate
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_if
c_cond
(paren
id|id
op_logical_and
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_logical_and
id|drive-&gt;autodma
)paren
(brace
r_if
c_cond
(paren
id|hwif
op_member_access_from_pointer
id|ide_dma_bad_drive
c_func
(paren
id|drive
)paren
)paren
r_goto
id|tune_pio
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_mword
op_amp
id|hwif-&gt;mwdma_mask
)paren
op_logical_or
(paren
id|id-&gt;dma_1word
op_amp
id|hwif-&gt;swdma_mask
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|triflex_config_drive_for_dma
c_func
(paren
id|drive
)paren
)paren
r_goto
id|tune_pio
suffix:semicolon
)brace
)brace
r_else
r_goto
id|tune_pio
suffix:semicolon
)brace
r_else
(brace
id|tune_pio
suffix:colon
id|hwif
op_member_access_from_pointer
id|tuneproc
c_func
(paren
id|drive
comma
l_int|255
)paren
suffix:semicolon
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|init_hwif_triflex
r_static
r_void
id|__init
id|init_hwif_triflex
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|hwif-&gt;tuneproc
op_assign
op_amp
id|triflex_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|triflex_tune_chipset
suffix:semicolon
id|hwif-&gt;atapi_dma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|triflex_config_drive_xfer_rate
suffix:semicolon
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
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
)brace
DECL|function|init_chipset_triflex
r_static
r_int
r_int
id|__init
id|init_chipset_triflex
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
macro_line|#ifdef CONFIG_PROC_FS
id|ide_pci_register_host_proc
c_func
(paren
op_amp
id|triflex_proc
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|triflex_init_one
r_static
r_int
id|__devinit
id|triflex_init_one
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
id|ide_pci_device_t
op_star
id|d
op_assign
op_amp
id|triflex_devices
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_ne
id|d-&gt;device
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
id|triflex_dev
op_assign
id|dev
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;TRIFLEX IDE&quot;
comma
dot
id|id_table
op_assign
id|triflex_pci_tbl
comma
dot
id|probe
op_assign
id|triflex_init_one
comma
)brace
suffix:semicolon
DECL|function|triflex_ide_init
r_static
r_int
id|triflex_ide_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ide_pci_register_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|triflex_ide_exit
r_static
r_void
id|triflex_ide_exit
c_func
(paren
r_void
)paren
(brace
id|ide_pci_unregister_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|triflex_ide_init
id|module_init
c_func
(paren
id|triflex_ide_init
)paren
suffix:semicolon
DECL|variable|triflex_ide_exit
id|module_exit
c_func
(paren
id|triflex_ide_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Torben Mathiasen&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for Compaq Triflex IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
