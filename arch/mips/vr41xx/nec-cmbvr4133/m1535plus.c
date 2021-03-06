multiline_comment|/*&n; * arch/mips/vr41xx/nec-cmbvr4133/m1535plus.c&n; *&n; * Initialize for ALi M1535+(included M5229 and M5237).&n; *&n; * Author: Yoichi Yuasa &lt;yyuasa@mvista.com, or source@mvista.com&gt; and&n; *         Alex Sapkov &lt;asapkov@ru.mvista.com&gt;&n; *&n; * 2003-2004 (c) MontaVista, Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; *&n; * Support for NEC-CMBVR4133 in 2.6&n; * Author: Manish Lachwani (mlachwani@mvista.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;asm/vr41xx/cmbvr4133.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|CONFIG_PORT
mdefine_line|#define CONFIG_PORT(port)&t;((port) ? 0x3f0 : 0x370)
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT(port)&t;&t;((port) ? 0x3f1 : 0x371)
DECL|macro|INDEX_PORT
mdefine_line|#define INDEX_PORT(port)&t;CONFIG_PORT(port)
DECL|macro|ENTER_CONFIG_MODE
mdefine_line|#define ENTER_CONFIG_MODE(port)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;outb_p(0x51, CONFIG_PORT(port));&t;&bslash;&n;&t;&t;outb_p(0x23, CONFIG_PORT(port));&t;&bslash;&n;&t;} while(0)
DECL|macro|SELECT_LOGICAL_DEVICE
mdefine_line|#define SELECT_LOGICAL_DEVICE(port, dev_no)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;outb_p(0x07, INDEX_PORT(port));&t;&t;&bslash;&n;&t;&t;outb_p((dev_no), DATA_PORT(port));&t;&bslash;&n;&t;} while(0)
DECL|macro|WRITE_CONFIG_DATA
mdefine_line|#define WRITE_CONFIG_DATA(port,index,data)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;outb_p((index), INDEX_PORT(port));&t;&bslash;&n;&t;&t;outb_p((data), DATA_PORT(port));&t;&bslash;&n;&t;} while(0)
DECL|macro|EXIT_CONFIG_MODE
mdefine_line|#define EXIT_CONFIG_MODE(port)&t;outb(0xbb, CONFIG_PORT(port))
DECL|macro|PCI_CONFIG_ADDR
mdefine_line|#define PCI_CONFIG_ADDR&t;KSEG1ADDR(0x0f000c18)
DECL|macro|PCI_CONFIG_DATA
mdefine_line|#define PCI_CONFIG_DATA&t;KSEG1ADDR(0x0f000c14)
macro_line|#ifdef CONFIG_BLK_DEV_FD
DECL|function|ali_m1535plus_fdc_init
r_void
id|__devinit
id|ali_m1535plus_fdc_init
c_func
(paren
r_int
id|port
)paren
(brace
id|ENTER_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
id|SELECT_LOGICAL_DEVICE
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* FDC */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x30
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* FDC: enable */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x60
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* I/O port base: 0x3f0 */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x61
comma
l_int|0xf0
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x70
comma
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/* IRQ: 6 */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x74
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* DMA: channel 2 */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf0
comma
l_int|0x08
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf1
comma
l_int|0x00
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf2
comma
l_int|0xff
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf4
comma
l_int|0x00
)paren
suffix:semicolon
id|EXIT_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|ali_m1535plus_parport_init
r_void
id|__devinit
id|ali_m1535plus_parport_init
c_func
(paren
r_int
id|port
)paren
(brace
id|ENTER_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
id|SELECT_LOGICAL_DEVICE
c_func
(paren
id|port
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Parallel Port */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x30
comma
l_int|0x01
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x60
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* I/O port base: 0x378 */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x61
comma
l_int|0x78
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x70
comma
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* IRQ: 7 */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x74
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* DMA: None */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf0
comma
l_int|0x8c
)paren
suffix:semicolon
multiline_comment|/* IRQ polarity: Active Low */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf1
comma
l_int|0xc5
)paren
suffix:semicolon
id|EXIT_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|ali_m1535plus_keyboard_init
r_void
id|__devinit
id|ali_m1535plus_keyboard_init
c_func
(paren
r_int
id|port
)paren
(brace
id|ENTER_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
id|SELECT_LOGICAL_DEVICE
c_func
(paren
id|port
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* KEYBOARD */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x30
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* KEYBOARD: eable */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x70
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* IRQ: 1 */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x72
comma
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* PS/2 Mouse IRQ: 12 */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf0
comma
l_int|0x00
)paren
suffix:semicolon
id|EXIT_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|ali_m1535plus_hotkey_init
r_void
id|__devinit
id|ali_m1535plus_hotkey_init
c_func
(paren
r_int
id|port
)paren
(brace
id|ENTER_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
id|SELECT_LOGICAL_DEVICE
c_func
(paren
id|port
comma
l_int|0xc
)paren
suffix:semicolon
multiline_comment|/* HOTKEY */
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0x30
comma
l_int|0x00
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf0
comma
l_int|0x35
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf1
comma
l_int|0x14
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf2
comma
l_int|0x11
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf3
comma
l_int|0x71
)paren
suffix:semicolon
id|WRITE_CONFIG_DATA
c_func
(paren
id|port
comma
l_int|0xf5
comma
l_int|0x05
)paren
suffix:semicolon
id|EXIT_CONFIG_MODE
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|ali_m1535plus_init
r_void
id|ali_m1535plus_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x18
)paren
suffix:semicolon
multiline_comment|/* PCI Interface Control */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x41
comma
l_int|0xc0
)paren
suffix:semicolon
multiline_comment|/* PS2 keyb &amp; mouse enable */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x42
comma
l_int|0x41
)paren
suffix:semicolon
multiline_comment|/* ISA bus cycle control */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x43
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* ISA bus cycle control 2 */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x44
comma
l_int|0x5d
)paren
suffix:semicolon
multiline_comment|/* IDE enable &amp; IRQ 14 */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x45
comma
l_int|0x0b
)paren
suffix:semicolon
multiline_comment|/* PCI int polling mode */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x47
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* BIOS chip select control */
multiline_comment|/* IRQ routing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* INTA IRQ10, INTB disable */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x49
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* INTC and INTD disable */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4a
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* INTE and INTF disable */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
l_int|0x90
)paren
suffix:semicolon
multiline_comment|/* Audio IRQ11, Modem disable */
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x50
comma
l_int|0x4000
)paren
suffix:semicolon
multiline_comment|/* Parity check IDE enable */
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x52
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* USB &amp; RTC disable */
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x54
comma
l_int|0x0002
)paren
suffix:semicolon
multiline_comment|/* ??? no info */
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x56
comma
l_int|0x0002
)paren
suffix:semicolon
multiline_comment|/* PCS1J signal disable */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x59
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* PCSDS */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5a
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5b
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x5c
comma
l_int|0x0000
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5e
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5f
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x60
comma
l_int|0x0000
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x6c
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x6d
comma
l_int|0x48
)paren
suffix:semicolon
multiline_comment|/* ROM address mapping */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x6e
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* ??? what for? */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x70
comma
l_int|0x12
)paren
suffix:semicolon
multiline_comment|/* Serial IRQ control */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x71
comma
l_int|0xEF
)paren
suffix:semicolon
multiline_comment|/* DMA channel select */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x72
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* USB IDSEL */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x73
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* ??? no info */
multiline_comment|/*&n;&t; * IRQ setup ALi M5237 USB Host Controller&n;&t; * IRQ: 9&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x74
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* USB IRQ9 */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x75
comma
l_int|0x1f
)paren
suffix:semicolon
multiline_comment|/* IDE2 IRQ 15  */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x76
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* ACPI disable */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x77
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* Modem disable */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x78
comma
l_int|0x20000000
)paren
suffix:semicolon
multiline_comment|/* Pin select 2 */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x7c
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Pin select 3 */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x81
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* ID read/write control */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x90
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* PCI PM block control */
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0xa4
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* PMSCR */
macro_line|#ifdef CONFIG_BLK_DEV_FD
id|ali_m1535plus_fdc_init
c_func
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|ali_m1535plus_keyboard_init
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ali_m1535plus_hotkey_init
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ali_config_writeb
r_static
r_inline
r_void
id|ali_config_writeb
c_func
(paren
id|u8
id|reg
comma
id|u8
id|val
comma
r_int
id|devfn
)paren
(brace
id|u32
id|data
suffix:semicolon
r_int
id|shift
suffix:semicolon
id|writel
c_func
(paren
(paren
l_int|1
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
op_or
(paren
id|reg
op_amp
l_int|0xfc
)paren
op_or
l_int|1UL
comma
id|PCI_CONFIG_ADDR
)paren
suffix:semicolon
id|data
op_assign
id|readl
c_func
(paren
id|PCI_CONFIG_DATA
)paren
suffix:semicolon
id|shift
op_assign
(paren
id|reg
op_amp
l_int|3
)paren
op_lshift
l_int|3
suffix:semicolon
id|data
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|shift
)paren
suffix:semicolon
id|data
op_or_assign
(paren
(paren
(paren
id|u32
)paren
id|val
)paren
op_lshift
id|shift
)paren
suffix:semicolon
id|writel
c_func
(paren
id|data
comma
id|PCI_CONFIG_DATA
)paren
suffix:semicolon
)brace
DECL|function|ali_config_readb
r_static
r_inline
id|u8
id|ali_config_readb
c_func
(paren
id|u8
id|reg
comma
r_int
id|devfn
)paren
(brace
id|u32
id|data
suffix:semicolon
id|writel
c_func
(paren
(paren
l_int|1
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
op_or
(paren
id|reg
op_amp
l_int|0xfc
)paren
op_or
l_int|1UL
comma
id|PCI_CONFIG_ADDR
)paren
suffix:semicolon
id|data
op_assign
id|readl
c_func
(paren
id|PCI_CONFIG_DATA
)paren
suffix:semicolon
r_return
(paren
id|u8
)paren
(paren
id|data
op_rshift
(paren
(paren
id|reg
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
)brace
DECL|function|ali_config_readw
r_static
r_inline
id|u16
id|ali_config_readw
c_func
(paren
id|u8
id|reg
comma
r_int
id|devfn
)paren
(brace
id|u32
id|data
suffix:semicolon
id|writel
c_func
(paren
(paren
l_int|1
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
op_or
(paren
id|reg
op_amp
l_int|0xfc
)paren
op_or
l_int|1UL
comma
id|PCI_CONFIG_ADDR
)paren
suffix:semicolon
id|data
op_assign
id|readl
c_func
(paren
id|PCI_CONFIG_DATA
)paren
suffix:semicolon
r_return
(paren
id|u16
)paren
(paren
id|data
op_rshift
(paren
(paren
id|reg
op_amp
l_int|2
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
)brace
DECL|variable|vr4133_rockhopper
r_int
id|vr4133_rockhopper
op_assign
l_int|0
suffix:semicolon
DECL|function|ali_m5229_preinit
r_void
id|__init
id|ali_m5229_preinit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ali_config_readw
c_func
(paren
id|PCI_VENDOR_ID
comma
l_int|16
)paren
op_eq
id|PCI_VENDOR_ID_AL
op_logical_and
id|ali_config_readw
c_func
(paren
id|PCI_DEVICE_ID
comma
l_int|16
)paren
op_eq
id|PCI_DEVICE_ID_AL_M1533
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Found an NEC Rockhopper &bslash;n&quot;
)paren
suffix:semicolon
id|vr4133_rockhopper
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Enable ALi M5229 IDE Controller (both channels)&n;&t;&t; * IDSEL: A27&n;&t;&t; */
id|ali_config_writeb
c_func
(paren
l_int|0x58
comma
l_int|0x4c
comma
l_int|16
)paren
suffix:semicolon
)brace
)brace
DECL|function|ali_m5229_init
r_void
id|__init
id|ali_m5229_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; * Enable Primary/Secondary Channel Cable Detect 40-Pin&n;&t; */
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
l_int|0xc023
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set only the 3rd byteis for the master IDE&squot;s cycle and&n;&t; * enable Internal IDE Function&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x50
comma
l_int|0x23
)paren
suffix:semicolon
multiline_comment|/* Class code attr register */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x09
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Set native mode &amp; stuff */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x52
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* use timing registers */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x58
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* Primary addr setup timing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x59
comma
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/* Primary cmd block timing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5a
comma
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/* Pr drv 0 R/W timing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5b
comma
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/* Pr drv 1 R/W timing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5c
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* Sec addr setup timing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5d
comma
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/* Sec cmd block timing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5e
comma
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/* Sec drv 0 R/W timing */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x5f
comma
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/* Sec drv 1 R/W timing */
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
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|PCI_COMMAND_PARITY
op_or
id|PCI_COMMAND_MASTER
op_or
id|PCI_COMMAND_IO
)paren
suffix:semicolon
)brace
eof
