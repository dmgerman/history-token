multiline_comment|/*&n; * linux/drivers/ide/pci/hpt34x.c&t;&t;Version 0.40&t;Sept 10, 2002&n; *&n; * Copyright (C) 1998-2000&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; *&n; * 00:12.0 Unknown mass storage controller:&n; * Triones Technologies, Inc.&n; * Unknown device 0003 (rev 01)&n; *&n; * hde: UDMA 2 (0x0000 0x0002) (0x0000 0x0010)&n; * hdf: UDMA 2 (0x0002 0x0012) (0x0010 0x0030)&n; * hde: DMA 2  (0x0000 0x0002) (0x0000 0x0010)&n; * hdf: DMA 2  (0x0002 0x0012) (0x0010 0x0030)&n; * hdg: DMA 1  (0x0012 0x0052) (0x0030 0x0070)&n; * hdh: DMA 1  (0x0052 0x0252) (0x0070 0x00f0)&n; *&n; * ide-pci.c reference&n; *&n; * Since there are two cards that report almost identically,&n; * the only discernable difference is the values reported in pcicmd.&n; * Booting-BIOS card or HPT363 :: pcicmd == 0x07&n; * Non-bootable card or HPT343 :: pcicmd == 0x05&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;hpt34x.h&quot;
macro_line|#if defined(DISPLAY_HPT34X_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|hpt34x_proc
r_static
id|u8
id|hpt34x_proc
op_assign
l_int|0
suffix:semicolon
DECL|macro|HPT34X_MAX_DEVS
mdefine_line|#define HPT34X_MAX_DEVS&t;&t;8
DECL|variable|hpt34x_devs
r_static
r_struct
id|pci_dev
op_star
id|hpt34x_devs
(braket
id|HPT34X_MAX_DEVS
)braket
suffix:semicolon
DECL|variable|n_hpt34x_devs
r_static
r_int
id|n_hpt34x_devs
suffix:semicolon
DECL|function|hpt34x_get_info
r_static
r_int
id|hpt34x_get_info
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
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
r_int
id|i
comma
id|len
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n                             &quot;
l_string|&quot;HPT34X Chipset.&bslash;n&quot;
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
id|n_hpt34x_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hpt34x_devs
(braket
id|i
)braket
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
multiline_comment|/*&n;&t;&t; * at that point bibma+0x2 et bibma+0xa are byte registers&n;&t;&t; * to investigate:&n;&t;&t; */
id|c0
op_assign
id|inb_p
c_func
(paren
(paren
id|u16
)paren
id|bibma
op_plus
l_int|0x02
)paren
suffix:semicolon
id|c1
op_assign
id|inb_p
c_func
(paren
(paren
id|u16
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
l_string|&quot;&bslash;nController: %d&bslash;n&quot;
comma
id|i
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
l_string|&quot;DMA enabled:    %s              %s&quot;
l_string|&quot;             %s               %s&bslash;n&quot;
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
l_string|&quot;UDMA&bslash;n&quot;
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
)brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* p - buffer must be less than 4k! */
id|len
op_assign
(paren
id|p
op_minus
id|buffer
)paren
op_minus
id|offset
suffix:semicolon
op_star
id|addr
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_return
id|len
OG
id|count
ques
c_cond
id|count
suffix:colon
id|len
suffix:semicolon
)brace
macro_line|#endif  /* defined(DISPLAY_HPT34X_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
DECL|function|hpt34x_ratemask
r_static
id|u8
id|hpt34x_ratemask
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpt34x_clear_chipset
r_static
r_void
id|hpt34x_clear_chipset
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
suffix:semicolon
id|u32
id|reg1
op_assign
l_int|0
comma
id|tmp1
op_assign
l_int|0
comma
id|reg2
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|reg1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|reg2
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
l_int|0x00
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
op_or
(paren
id|reg1
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
id|reg2
op_amp
op_complement
(paren
l_int|0x11
op_lshift
id|drive-&gt;dn
)paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x44
comma
id|tmp1
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|tmp2
)paren
suffix:semicolon
)brace
DECL|function|hpt34x_tune_chipset
r_static
r_int
id|hpt34x_tune_chipset
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|xferspeed
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
suffix:semicolon
id|u8
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
id|hpt34x_ratemask
c_func
(paren
id|drive
)paren
comma
id|xferspeed
)paren
suffix:semicolon
id|u32
id|reg1
op_assign
l_int|0
comma
id|tmp1
op_assign
l_int|0
comma
id|reg2
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
id|u8
id|hi_speed
comma
id|lo_speed
suffix:semicolon
id|SPLIT_BYTE
c_func
(paren
id|speed
comma
id|hi_speed
comma
id|lo_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi_speed
op_amp
l_int|7
)paren
(brace
id|hi_speed
op_assign
(paren
id|hi_speed
op_amp
l_int|4
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x10
suffix:semicolon
)brace
r_else
(brace
id|lo_speed
op_lshift_assign
l_int|5
suffix:semicolon
id|lo_speed
op_rshift_assign
l_int|5
suffix:semicolon
)brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|reg1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|reg2
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
id|lo_speed
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
op_or
(paren
id|reg1
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
(paren
id|hi_speed
op_lshift
id|drive-&gt;dn
)paren
op_or
id|reg2
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x44
comma
id|tmp1
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|tmp2
)paren
suffix:semicolon
macro_line|#if HPT343_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: %s drive%d (0x%04x 0x%04x) (0x%04x 0x%04x)&quot;
"&bslash;"
l_string|&quot; (0x%02x 0x%02x)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|ide_xfer_verbose
c_func
(paren
id|speed
)paren
comma
id|drive-&gt;dn
comma
id|reg1
comma
id|tmp1
comma
id|reg2
comma
id|tmp2
comma
id|hi_speed
comma
id|lo_speed
)paren
suffix:semicolon
macro_line|#endif /* HPT343_DEBUG_DRIVE_INFO */
r_return
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
DECL|function|hpt34x_tune_drive
r_static
r_void
id|hpt34x_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|5
comma
l_int|NULL
)paren
suffix:semicolon
id|hpt34x_clear_chipset
c_func
(paren
id|drive
)paren
suffix:semicolon
(paren
r_void
)paren
id|hpt34x_tune_chipset
c_func
(paren
id|drive
comma
(paren
id|XFER_PIO_0
op_plus
id|pio
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This allows the configuration of ide_pci chipset registers&n; * for cards that learn about the drive&squot;s UDMA, DMA, PIO capabilities&n; * after the drive is reported by the OS.  Initially for designed for&n; * HPT343 UDMA chipset by HighPoint|Triones Technologies, Inc.&n; */
DECL|function|config_chipset_for_dma
r_static
r_int
id|config_chipset_for_dma
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|speed
op_assign
id|ide_dma_speed
c_func
(paren
id|drive
comma
id|hpt34x_ratemask
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|speed
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hpt34x_clear_chipset
c_func
(paren
id|drive
)paren
suffix:semicolon
(paren
r_void
)paren
id|hpt34x_tune_chipset
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
DECL|function|hpt34x_config_drive_xfer_rate
r_static
r_int
id|hpt34x_config_drive_xfer_rate
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
id|drive-&gt;init_speed
op_assign
l_int|0
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
multiline_comment|/* Consult the list of known &quot;bad&quot; drives */
r_if
c_cond
(paren
id|__ide_dma_bad_drive
c_func
(paren
id|drive
)paren
)paren
r_goto
id|fast_ata_pio
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
(brace
multiline_comment|/* Force if Capable UltraDMA */
r_int
id|dma
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
op_logical_and
id|dma
)paren
r_goto
id|try_dma_modes
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
id|try_dma_modes
suffix:colon
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
multiline_comment|/* Force if Capable regular DMA modes */
r_if
c_cond
(paren
op_logical_neg
id|config_chipset_for_dma
c_func
(paren
id|drive
)paren
)paren
r_goto
id|no_dma_set
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|__ide_dma_good_drive
c_func
(paren
id|drive
)paren
op_logical_and
(paren
id|id-&gt;eide_dma_time
OL
l_int|150
)paren
)paren
(brace
multiline_comment|/* Consult the list of known &quot;good&quot; drives */
r_if
c_cond
(paren
op_logical_neg
id|config_chipset_for_dma
c_func
(paren
id|drive
)paren
)paren
r_goto
id|no_dma_set
suffix:semicolon
)brace
r_else
(brace
r_goto
id|fast_ata_pio
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_HPT34X_AUTODMA
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
macro_line|#else
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
(paren
id|id-&gt;capability
op_amp
l_int|8
)paren
op_logical_or
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
)paren
(brace
id|fast_ata_pio
suffix:colon
id|no_dma_set
suffix:colon
id|hpt34x_tune_drive
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
multiline_comment|/* IORDY not supported */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * If the BIOS does not set the IO base addaress to XX00, 343 will fail.&n; */
DECL|macro|HPT34X_PCI_INIT_REG
mdefine_line|#define&t;HPT34X_PCI_INIT_REG&t;&t;0x80
DECL|function|init_chipset_hpt34x
r_static
r_int
r_int
id|__devinit
id|init_chipset_hpt34x
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
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|hpt34xIoBase
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
)paren
suffix:semicolon
r_int
r_int
id|hpt_addr
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x20
comma
l_int|0x34
comma
l_int|0x28
comma
l_int|0x3c
)brace
suffix:semicolon
r_int
r_int
id|hpt_addr_len
(braket
l_int|4
)braket
op_assign
(brace
l_int|7
comma
l_int|3
comma
l_int|7
comma
l_int|3
)brace
suffix:semicolon
id|u16
id|cmd
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|HPT34X_PCI_INIT_REG
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
(brace
r_if
c_cond
(paren
id|pci_resource_start
c_func
(paren
id|dev
comma
id|PCI_ROM_RESOURCE
)paren
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_ROM_ADDRESS
comma
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
op_or
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HPT345: ROM enabled at 0x%08lx&bslash;n&quot;
comma
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|0xF0
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|0x20
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Since 20-23 can be assigned and are R/W, we correct them.&n;&t; */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
op_amp
op_complement
id|PCI_COMMAND_IO
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
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
(paren
id|hpt34xIoBase
op_plus
id|hpt_addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_plus
id|hpt_addr_len
(braket
id|i
)braket
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
(paren
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|i
op_star
l_int|4
)paren
)paren
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#if defined(DISPLAY_HPT34X_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
id|hpt34x_devs
(braket
id|n_hpt34x_devs
op_increment
)braket
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpt34x_proc
)paren
(brace
id|hpt34x_proc
op_assign
l_int|1
suffix:semicolon
id|ide_pci_create_host_proc
c_func
(paren
l_string|&quot;hpt34x&quot;
comma
id|hpt34x_get_info
)paren
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_HPT34X_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
DECL|function|init_hwif_hpt34x
r_static
r_void
id|__devinit
id|init_hwif_hpt34x
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|u16
id|pcicmd
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|hpt34x_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|hpt34x_tune_chipset
suffix:semicolon
id|hwif-&gt;no_dsc
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|PCI_COMMAND
comma
op_amp
id|pcicmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;dma_base
)paren
r_return
suffix:semicolon
id|hwif-&gt;ultra_mask
op_assign
l_int|0x07
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
id|hpt34x_config_drive_xfer_rate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|noautodma
)paren
id|hwif-&gt;autodma
op_assign
(paren
id|pcicmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
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
DECL|function|hpt34x_init_one
r_static
r_int
id|__devinit
id|hpt34x_init_one
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
id|hpt34x_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_static
r_char
op_star
id|chipset_names
(braket
)braket
op_assign
(brace
l_string|&quot;HPT343&quot;
comma
l_string|&quot;HPT345&quot;
)brace
suffix:semicolon
id|u16
id|pcicmd
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|pcicmd
)paren
suffix:semicolon
id|d-&gt;name
op_assign
id|chipset_names
(braket
(paren
id|pcicmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)braket
suffix:semicolon
id|d-&gt;bootable
op_assign
(paren
id|pcicmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
ques
c_cond
id|OFF_BOARD
suffix:colon
id|NEVER_BOARD
suffix:semicolon
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hpt34x_pci_tbl
r_static
r_struct
id|pci_device_id
id|hpt34x_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_TTI
comma
id|PCI_DEVICE_ID_TTI_HPT343
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|hpt34x_pci_tbl
)paren
suffix:semicolon
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
l_string|&quot;HPT34x_IDE&quot;
comma
dot
id|id_table
op_assign
id|hpt34x_pci_tbl
comma
dot
id|probe
op_assign
id|hpt34x_init_one
comma
)brace
suffix:semicolon
DECL|function|hpt34x_ide_init
r_static
r_int
id|hpt34x_ide_init
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
DECL|variable|hpt34x_ide_init
id|module_init
c_func
(paren
id|hpt34x_ide_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andre Hedrick&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for Highpoint 34x IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
