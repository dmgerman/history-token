multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *      IT8172 IDE controller support&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *              stevel@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
macro_line|#include &quot;it8172.h&quot;
multiline_comment|/*&n; * Prototypes&n; */
DECL|function|it8172_ratemask
r_static
id|u8
id|it8172_ratemask
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
DECL|function|it8172_tune_drive
r_static
r_void
id|it8172_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
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
r_int
id|is_slave
op_assign
(paren
id|hwif-&gt;drives
(braket
l_int|1
)braket
op_eq
id|drive
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|drive_enables
suffix:semicolon
id|u32
id|drive_timing
suffix:semicolon
id|pio
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|drive_enables
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|drive_timing
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIX! The DIOR/DIOW pulse width and recovery times in port 0x44&n;&t; * are being left at the default values of 8 PCI clocks (242 nsec&n;&t; * for a 33 MHz clock). These can be safely shortened at higher&n;&t; * PIO modes. The DIOR/DIOW pulse width and recovery times only&n;&t; * apply to PIO modes, not to the DMA modes.&n;&t; */
multiline_comment|/*&n;&t; * Enable port 0x44. The IT8172G spec is confused; it calls&n;&t; * this register the &quot;Slave IDE Timing Register&quot;, but in fact,&n;&t; * it controls timing for both master and slave drives.&n;&t; */
id|drive_enables
op_or_assign
l_int|0x4000
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
)paren
(brace
id|drive_enables
op_and_assign
l_int|0xc006
suffix:semicolon
r_if
c_cond
(paren
id|pio
OG
l_int|1
)paren
multiline_comment|/* enable prefetch and IORDY sample-point */
id|drive_enables
op_or_assign
l_int|0x0060
suffix:semicolon
)brace
r_else
(brace
id|drive_enables
op_and_assign
l_int|0xc060
suffix:semicolon
r_if
c_cond
(paren
id|pio
OG
l_int|1
)paren
multiline_comment|/* enable prefetch and IORDY sample-point */
id|drive_enables
op_or_assign
l_int|0x0006
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|drive_enables
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
)brace
DECL|function|it8172_dma_2_pio
r_static
id|u8
id|it8172_dma_2_pio
(paren
id|u8
id|xfer_rate
)paren
(brace
r_switch
c_cond
(paren
id|xfer_rate
)paren
(brace
r_case
id|XFER_UDMA_5
suffix:colon
r_case
id|XFER_UDMA_4
suffix:colon
r_case
id|XFER_UDMA_3
suffix:colon
r_case
id|XFER_UDMA_2
suffix:colon
r_case
id|XFER_UDMA_1
suffix:colon
r_case
id|XFER_UDMA_0
suffix:colon
r_case
id|XFER_MW_DMA_2
suffix:colon
r_case
id|XFER_PIO_4
suffix:colon
r_return
l_int|4
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_case
id|XFER_PIO_3
suffix:colon
r_return
l_int|3
suffix:semicolon
r_case
id|XFER_SW_DMA_2
suffix:colon
r_case
id|XFER_PIO_2
suffix:colon
r_return
l_int|2
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
r_case
id|XFER_SW_DMA_1
suffix:colon
r_case
id|XFER_SW_DMA_0
suffix:colon
r_case
id|XFER_PIO_1
suffix:colon
r_case
id|XFER_PIO_0
suffix:colon
r_case
id|XFER_PIO_SLOW
suffix:colon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|it8172_tune_chipset
r_static
r_int
id|it8172_tune_chipset
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
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
id|it8172_ratemask
c_func
(paren
id|drive
)paren
comma
id|xferspeed
)paren
suffix:semicolon
r_int
id|a_speed
op_assign
l_int|3
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
suffix:semicolon
r_int
id|u_flag
op_assign
l_int|1
op_lshift
id|drive-&gt;dn
suffix:semicolon
r_int
id|u_speed
op_assign
l_int|0
suffix:semicolon
id|u8
id|reg48
comma
id|reg4a
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|reg48
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4a
comma
op_amp
id|reg4a
)paren
suffix:semicolon
multiline_comment|/*&n;     * Setting the DMA cycle time to 2 or 3 PCI clocks (60 and 91 nsec&n;     * at 33 MHz PCI clock) seems to cause BadCRC errors during DMA&n;     * transfers on some drives, even though both numbers meet the minimum&n;     * ATAPI-4 spec of 73 and 54 nsec for UDMA 1 and 2 respectively.&n;     * So the faster times are just commented out here. The good news is&n;     * that the slower cycle time has very little affect on transfer&n;     * performance.&n;     */
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
id|XFER_UDMA_4
suffix:colon
r_case
id|XFER_UDMA_2
suffix:colon
singleline_comment|//u_speed = 2 &lt;&lt; (drive-&gt;dn * 4); break;
r_case
id|XFER_UDMA_5
suffix:colon
r_case
id|XFER_UDMA_3
suffix:colon
r_case
id|XFER_UDMA_1
suffix:colon
singleline_comment|//u_speed = 1 &lt;&lt; (drive-&gt;dn * 4); break;
r_case
id|XFER_UDMA_0
suffix:colon
id|u_speed
op_assign
l_int|0
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_case
id|XFER_MW_DMA_0
suffix:colon
r_case
id|XFER_SW_DMA_2
suffix:colon
r_break
suffix:semicolon
r_case
id|XFER_PIO_4
suffix:colon
r_case
id|XFER_PIO_3
suffix:colon
r_case
id|XFER_PIO_2
suffix:colon
r_case
id|XFER_PIO_0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_UDMA_0
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg48
op_or
id|u_flag
)paren
suffix:semicolon
id|reg4a
op_and_assign
op_complement
id|a_speed
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_or
id|u_speed
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
l_int|0x48
comma
id|reg48
op_amp
op_complement
id|u_flag
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_amp
op_complement
id|a_speed
)paren
suffix:semicolon
)brace
id|it8172_tune_drive
c_func
(paren
id|drive
comma
id|it8172_dma_2_pio
c_func
(paren
id|speed
)paren
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
DECL|function|it8172_config_chipset_for_dma
r_static
r_int
id|it8172_config_chipset_for_dma
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
id|it8172_ratemask
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
(brace
id|u8
id|tspeed
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
id|it8172_dma_2_pio
c_func
(paren
id|XFER_PIO_0
op_plus
id|tspeed
)paren
suffix:semicolon
)brace
(paren
r_void
)paren
id|it8172_tune_chipset
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
DECL|function|it8172_config_drive_xfer_rate
r_static
r_int
id|it8172_config_drive_xfer_rate
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
id|hwif
op_member_access_from_pointer
id|ide_dma_bad_drive
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
id|it8172_config_chipset_for_dma
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
op_logical_neg
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
id|it8172_config_chipset_for_dma
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
id|hwif
op_member_access_from_pointer
id|ide_dma_good_drive
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
id|it8172_config_chipset_for_dma
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
id|it8172_tune_drive
c_func
(paren
id|drive
comma
l_int|5
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
DECL|function|init_chipset_it8172
r_static
r_int
r_int
id|__init
id|init_chipset_it8172
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
r_char
id|progif
suffix:semicolon
multiline_comment|/*&n;&t; * Place both IDE interfaces into PCI &quot;native&quot; mode&n;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CLASS_PROG
comma
op_amp
id|progif
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CLASS_PROG
comma
id|progif
op_or
l_int|0x05
)paren
suffix:semicolon
r_return
id|IT8172_IDE_IRQ
suffix:semicolon
)brace
DECL|function|init_hwif_it8172
r_static
r_void
id|__init
id|init_hwif_it8172
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|cmdBase
comma
id|ctrlBase
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|it8172_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|it8172_tune_chipset
suffix:semicolon
id|cmdBase
op_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|ctrlBase
op_assign
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|ide_init_hwif_ports
c_func
(paren
op_amp
id|hwif-&gt;hw
comma
id|cmdBase
comma
id|ctrlBase
op_or
l_int|2
comma
l_int|NULL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|hwif-&gt;io_ports
comma
id|hwif-&gt;hw.io_ports
comma
r_sizeof
(paren
id|hwif-&gt;io_ports
)paren
)paren
suffix:semicolon
id|hwif-&gt;noprobe
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;dma_base
)paren
(brace
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
r_return
suffix:semicolon
)brace
id|hwif-&gt;atapi_dma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;ultra_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x06
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0x04
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|it8172_config_drive_xfer_rate
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
DECL|function|init_dma_it8172
r_static
r_void
id|__init
id|init_dma_it8172
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
r_extern
r_void
id|ide_setup_pci_device
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
DECL|function|it8172_init_one
r_static
r_int
id|__devinit
id|it8172_init_one
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
id|it8172_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_amp
l_int|1
)paren
op_logical_or
(paren
op_logical_neg
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
id|PCI_CLASS_STORAGE_IDE
)paren
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* IT8172 is more than only a IDE controller */
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|it8172_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_ITE
comma
id|PCI_DEVICE_ID_ITE_IT8172G
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
l_string|&quot;IT8172IDE&quot;
comma
dot
id|id_table
op_assign
id|it8172_pci_tbl
comma
dot
id|probe
op_assign
id|it8172_init_one
comma
)brace
suffix:semicolon
DECL|function|it8172_ide_init
r_static
r_int
id|it8172_ide_init
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
DECL|function|it8172_ide_exit
r_static
r_void
id|it8172_ide_exit
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
DECL|variable|it8172_ide_init
id|module_init
c_func
(paren
id|it8172_ide_init
)paren
suffix:semicolon
DECL|variable|it8172_ide_exit
id|module_exit
c_func
(paren
id|it8172_ide_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;SteveL@mvista.com&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for ITE 8172 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
eof
