macro_line|#ifndef CY82C693_H
DECL|macro|CY82C693_H
mdefine_line|#define CY82C693_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
multiline_comment|/* the current version */
DECL|macro|CY82_VERSION
mdefine_line|#define CY82_VERSION&t;&quot;CY82C693U driver v0.34 99-13-12 Andreas S. Krebs (akrebs@altavista.net)&quot;
multiline_comment|/*&n; *&t;The following are used to debug the driver.&n; */
DECL|macro|CY82C693_DEBUG_LOGS
mdefine_line|#define&t;CY82C693_DEBUG_LOGS&t;0
DECL|macro|CY82C693_DEBUG_INFO
mdefine_line|#define&t;CY82C693_DEBUG_INFO&t;0
multiline_comment|/* define CY82C693_SETDMA_CLOCK to set DMA Controller Clock Speed to ATCLK */
DECL|macro|CY82C693_SETDMA_CLOCK
macro_line|#undef CY82C693_SETDMA_CLOCK
multiline_comment|/*&n; *&t;NOTE: the value for busmaster timeout is tricky and I got it by&n; *&t; trial and error!  By using a to low value will cause DMA timeouts&n; *&t; and drop IDE performance, and by using a to high value will cause&n; *&t; audio playback to scatter.&n; *&t; If you know a better value or how to calc it, please let me know.&n; */
multiline_comment|/* twice the value written in cy82c693ub datasheet */
DECL|macro|BUSMASTER_TIMEOUT
mdefine_line|#define BUSMASTER_TIMEOUT&t;0x50
multiline_comment|/*&n; * the value above was tested on my machine and it seems to work okay&n; */
multiline_comment|/* here are the offset definitions for the registers */
DECL|macro|CY82_IDE_CMDREG
mdefine_line|#define CY82_IDE_CMDREG&t;&t;0x04
DECL|macro|CY82_IDE_ADDRSETUP
mdefine_line|#define CY82_IDE_ADDRSETUP&t;0x48
DECL|macro|CY82_IDE_MASTER_IOR
mdefine_line|#define CY82_IDE_MASTER_IOR&t;0x4C&t;
DECL|macro|CY82_IDE_MASTER_IOW
mdefine_line|#define CY82_IDE_MASTER_IOW&t;0x4D&t;
DECL|macro|CY82_IDE_SLAVE_IOR
mdefine_line|#define CY82_IDE_SLAVE_IOR&t;0x4E&t;
DECL|macro|CY82_IDE_SLAVE_IOW
mdefine_line|#define CY82_IDE_SLAVE_IOW&t;0x4F
DECL|macro|CY82_IDE_MASTER_8BIT
mdefine_line|#define CY82_IDE_MASTER_8BIT&t;0x50&t;
DECL|macro|CY82_IDE_SLAVE_8BIT
mdefine_line|#define CY82_IDE_SLAVE_8BIT&t;0x51&t;
DECL|macro|CY82_INDEX_PORT
mdefine_line|#define CY82_INDEX_PORT&t;&t;0x22
DECL|macro|CY82_DATA_PORT
mdefine_line|#define CY82_DATA_PORT&t;&t;0x23
DECL|macro|CY82_INDEX_CTRLREG1
mdefine_line|#define CY82_INDEX_CTRLREG1&t;0x01
DECL|macro|CY82_INDEX_CHANNEL0
mdefine_line|#define CY82_INDEX_CHANNEL0&t;0x30
DECL|macro|CY82_INDEX_CHANNEL1
mdefine_line|#define CY82_INDEX_CHANNEL1&t;0x31
DECL|macro|CY82_INDEX_TIMEOUT
mdefine_line|#define CY82_INDEX_TIMEOUT&t;0x32
multiline_comment|/* the max PIO mode - from datasheet */
DECL|macro|CY82C693_MAX_PIO
mdefine_line|#define CY82C693_MAX_PIO&t;4
multiline_comment|/* the min and max PCI bus speed in MHz - from datasheet */
DECL|macro|CY82C963_MIN_BUS_SPEED
mdefine_line|#define CY82C963_MIN_BUS_SPEED&t;25
DECL|macro|CY82C963_MAX_BUS_SPEED
mdefine_line|#define CY82C963_MAX_BUS_SPEED&t;33
multiline_comment|/* the struct for the PIO mode timings */
DECL|struct|pio_clocks_s
r_typedef
r_struct
id|pio_clocks_s
(brace
DECL|member|address_time
id|u8
id|address_time
suffix:semicolon
multiline_comment|/* Address setup (clocks) */
DECL|member|time_16r
id|u8
id|time_16r
suffix:semicolon
multiline_comment|/* clocks for 16bit IOR (0xF0=Active/data, 0x0F=Recovery) */
DECL|member|time_16w
id|u8
id|time_16w
suffix:semicolon
multiline_comment|/* clocks for 16bit IOW (0xF0=Active/data, 0x0F=Recovery) */
DECL|member|time_8
id|u8
id|time_8
suffix:semicolon
multiline_comment|/* clocks for 8bit (0xF0=Active/data, 0x0F=Recovery) */
DECL|typedef|pio_clocks_t
)brace
id|pio_clocks_t
suffix:semicolon
r_static
r_int
r_int
id|init_chipset_cy82c693
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_hwif_cy82c693
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_iops_cy82c693
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|cy82c693_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_CONTAQ
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_CONTAQ_82C693
comma
dot
id|name
op_assign
l_string|&quot;CY82C693&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_cy82c693
comma
dot
id|init_iops
op_assign
id|init_iops_cy82c693
comma
dot
id|init_hwif
op_assign
id|init_hwif_cy82c693
comma
dot
id|init_dma
op_assign
l_int|NULL
comma
dot
id|channels
op_assign
l_int|1
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|vendor
op_assign
l_int|0
comma
dot
id|device
op_assign
l_int|0
comma
dot
id|channels
op_assign
l_int|0
comma
dot
id|bootable
op_assign
id|EOL
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* CY82C693_H */
eof
