multiline_comment|/*&n; * arch/ppc/boot/prep/misc.c&n; *&n; * Adapted for PowerPC by Gary Thomas&n; *&n; * Rewritten by Cort Dougan (cort@cs.nmt.edu)&n; * One day to be replaced by a single bootloader for chrp/prep/pmac. -- Cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;nonstdio.h&quot;
macro_line|#include &quot;zlib.h&quot;
multiline_comment|/*&n; * Please send me load/board info and such data for hardware not&n; * listed here so I can keep track since things are getting tricky&n; * with the different load addrs with different firmware.  This will&n; * help to avoid breaking the load/boot process.&n; * -- Cort&n; */
DECL|variable|avail_ram
r_char
op_star
id|avail_ram
suffix:semicolon
DECL|variable|end_avail
r_char
op_star
id|end_avail
suffix:semicolon
multiline_comment|/* The linker tells us where the image is. */
r_extern
r_char
id|__image_begin
comma
id|__image_end
suffix:semicolon
r_extern
r_char
id|__ramdisk_begin
comma
id|__ramdisk_end
suffix:semicolon
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_CMDLINE
DECL|macro|CMDLINE
mdefine_line|#define CMDLINE CONFIG_CMDLINE
macro_line|#else
DECL|macro|CMDLINE
mdefine_line|#define CMDLINE &quot;&quot;
macro_line|#endif
DECL|variable|cmd_preset
r_char
id|cmd_preset
(braket
)braket
op_assign
id|CMDLINE
suffix:semicolon
DECL|variable|cmd_buf
r_char
id|cmd_buf
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|cmd_line
r_char
op_star
id|cmd_line
op_assign
id|cmd_buf
suffix:semicolon
DECL|variable|keyb_present
r_int
id|keyb_present
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* keyboard controller is present by default */
DECL|variable|hold_resid_buf
id|RESIDUAL
id|hold_resid_buf
suffix:semicolon
DECL|variable|hold_residual
id|RESIDUAL
op_star
id|hold_residual
op_assign
op_amp
id|hold_resid_buf
suffix:semicolon
DECL|variable|initrd_size
r_int
r_int
id|initrd_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|zimage_start
r_char
op_star
id|zimage_start
suffix:semicolon
DECL|variable|zimage_size
r_int
id|zimage_size
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_8250_CONSOLE)
DECL|variable|com_port
r_int
r_int
id|com_port
suffix:semicolon
macro_line|#endif /* CONFIG_SERIAL_8250_CONSOLE */
macro_line|#ifdef CONFIG_VGA_CONSOLE
DECL|variable|vidmem
r_char
op_star
id|vidmem
op_assign
(paren
r_char
op_star
)paren
l_int|0xC00B8000
suffix:semicolon
DECL|variable|lines
DECL|variable|cols
r_int
id|lines
op_assign
l_int|25
comma
id|cols
op_assign
l_int|80
suffix:semicolon
DECL|variable|orig_x
DECL|variable|orig_y
r_int
id|orig_x
comma
id|orig_y
op_assign
l_int|24
suffix:semicolon
macro_line|#endif /* CONFIG_VGA_CONSOLE */
r_extern
r_int
id|CRT_tstc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|vga_init
c_func
(paren
r_int
r_char
op_star
id|ISA_mem
)paren
suffix:semicolon
r_extern
r_void
id|gunzip
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|serial_init
c_func
(paren
r_int
id|chan
comma
r_void
op_star
id|ignored
)paren
suffix:semicolon
r_extern
r_void
id|serial_fixups
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_mem_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
DECL|function|writel
id|writel
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|address
)paren
(brace
multiline_comment|/* Ensure I/O operations complete */
id|__asm__
r_volatile
(paren
l_string|&quot;eieio&quot;
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|address
op_assign
id|cpu_to_le32
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|readl
id|readl
c_func
(paren
r_int
r_int
id|address
)paren
(brace
multiline_comment|/* Ensure I/O operations complete */
id|__asm__
r_volatile
(paren
l_string|&quot;eieio&quot;
)paren
suffix:semicolon
r_return
id|le32_to_cpu
c_func
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|address
)paren
suffix:semicolon
)brace
DECL|macro|PCI_CFG_ADDR
mdefine_line|#define PCI_CFG_ADDR(dev,off)&t;((0x80&lt;&lt;24) | (dev&lt;&lt;8) | (off&amp;0xfc))
DECL|macro|PCI_CFG_DATA
mdefine_line|#define PCI_CFG_DATA(off)&t;(0x80000cfc+(off&amp;3))
r_static
r_void
DECL|function|pci_read_config_32
id|pci_read_config_32
c_func
(paren
r_int
r_char
id|devfn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
id|writel
c_func
(paren
id|PCI_CFG_ADDR
c_func
(paren
id|devfn
comma
id|offset
)paren
comma
l_int|0x80000cf8
)paren
suffix:semicolon
op_star
id|val
op_assign
id|readl
c_func
(paren
id|PCI_CFG_DATA
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VGA_CONSOLE
r_void
DECL|function|scroll
id|scroll
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|memcpy
(paren
id|vidmem
comma
id|vidmem
op_plus
id|cols
op_star
l_int|2
comma
(paren
id|lines
op_minus
l_int|1
)paren
op_star
id|cols
op_star
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
(paren
id|lines
op_minus
l_int|1
)paren
op_star
id|cols
op_star
l_int|2
suffix:semicolon
id|i
OL
id|lines
op_star
id|cols
op_star
l_int|2
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
id|vidmem
(braket
id|i
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_VGA_CONSOLE */
r_int
r_int
DECL|function|decompress_kernel
id|decompress_kernel
c_func
(paren
r_int
r_int
id|load_addr
comma
r_int
id|num_words
comma
r_int
r_int
id|cksum
comma
id|RESIDUAL
op_star
id|residual
)paren
(brace
r_int
id|timer
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
r_int
id|start
suffix:semicolon
r_char
op_star
id|cp
comma
id|ch
suffix:semicolon
r_int
r_int
id|TotalMemory
suffix:semicolon
r_int
r_char
id|board_type
suffix:semicolon
r_int
r_char
id|base_mod
suffix:semicolon
r_int
id|start_multi
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pci_viddid
comma
id|pci_did
comma
id|tulip_pci_base
comma
id|tulip_base
suffix:semicolon
id|serial_fixups
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_8250_CONSOLE)
id|com_port
op_assign
id|serial_init
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SERIAL_8250_CONSOLE */
macro_line|#if defined(CONFIG_VGA_CONSOLE)
id|vga_init
c_func
(paren
(paren
r_int
r_char
op_star
)paren
l_int|0xC0000000
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_VGA_CONSOLE */
multiline_comment|/*&n;&t; * Tell the user where we were loaded at and where we were relocated&n;&t; * to for debugging this process.&n;&t; */
id|puts
c_func
(paren
l_string|&quot;loaded at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
id|load_addr
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|load_addr
op_plus
(paren
l_int|4
op_star
id|num_words
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|load_addr
op_ne
(paren
r_int
r_int
)paren
op_amp
id|start
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;relocated to:  &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|start
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|start
op_plus
(paren
l_int|4
op_star
id|num_words
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|residual
)paren
(brace
multiline_comment|/*&n;&t;&t; * Tell the user where the residual data is.&n;&t;&t; */
id|puts
c_func
(paren
l_string|&quot;board data at: &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|residual
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
id|residual
op_plus
r_sizeof
(paren
id|RESIDUAL
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;nrelocated to:  &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|hold_residual
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
id|hold_residual
op_plus
r_sizeof
(paren
id|RESIDUAL
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Is this Motorola PPCBug? */
r_if
c_cond
(paren
(paren
l_int|1
op_amp
id|residual-&gt;VitalProductData.FirmwareSupports
)paren
op_logical_and
(paren
l_int|1
op_eq
id|residual-&gt;VitalProductData.FirmwareSupplier
)paren
)paren
(brace
id|board_type
op_assign
id|inb
c_func
(paren
l_int|0x800
)paren
op_amp
l_int|0xF0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Reset the onboard 21x4x Ethernet&n;&t;&t;&t; * Motorola Ethernet is at IDSEL 14 (devfn 0x70)&n;&t;&t;&t; */
id|pci_read_config_32
c_func
(paren
l_int|0x70
comma
l_int|0x00
comma
op_amp
id|pci_viddid
)paren
suffix:semicolon
id|pci_did
op_assign
(paren
id|pci_viddid
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* Be sure we&squot;ve really found a 21x4x chip */
r_if
c_cond
(paren
(paren
(paren
id|pci_viddid
op_amp
l_int|0xffff
)paren
op_eq
id|PCI_VENDOR_ID_DEC
)paren
op_logical_and
(paren
(paren
id|pci_did
op_eq
id|PCI_DEVICE_ID_DEC_TULIP_FAST
)paren
op_logical_or
(paren
id|pci_did
op_eq
id|PCI_DEVICE_ID_DEC_TULIP
)paren
op_logical_or
(paren
id|pci_did
op_eq
id|PCI_DEVICE_ID_DEC_TULIP_PLUS
)paren
op_logical_or
(paren
id|pci_did
op_eq
id|PCI_DEVICE_ID_DEC_21142
)paren
)paren
)paren
(brace
id|pci_read_config_32
c_func
(paren
l_int|0x70
comma
l_int|0x10
comma
op_amp
id|tulip_pci_base
)paren
suffix:semicolon
multiline_comment|/* Get the physical base address */
id|tulip_base
op_assign
(paren
id|tulip_pci_base
op_amp
op_complement
l_int|0x03UL
)paren
op_plus
l_int|0x80000000
suffix:semicolon
multiline_comment|/* Strobe the 21x4x reset bit in CSR0 */
id|writel
c_func
(paren
l_int|0x1
comma
id|tulip_base
)paren
suffix:semicolon
)brace
multiline_comment|/* If this is genesis 2 board then check for no&n;&t;&t;&t; * keyboard controller and more than one processor.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|board_type
op_eq
l_int|0xe0
)paren
(brace
id|base_mod
op_assign
id|inb
c_func
(paren
l_int|0x803
)paren
suffix:semicolon
multiline_comment|/* if a MVME2300/2400 or a Sitka then no keyboard */
r_if
c_cond
(paren
(paren
id|base_mod
op_eq
l_int|0xFA
)paren
op_logical_or
(paren
id|base_mod
op_eq
l_int|0xF9
)paren
op_logical_or
(paren
id|base_mod
op_eq
l_int|0xE1
)paren
)paren
(brace
id|keyb_present
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no keyboard */
)brace
)brace
multiline_comment|/* If this is a multiprocessor system then&n;&t;&t;&t; * park the other processor so that the&n;&t;&t;&t; * kernel knows where to find them.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|residual-&gt;MaxNumCpus
OG
l_int|1
)paren
id|start_multi
op_assign
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|hold_residual
comma
id|residual
comma
r_sizeof
(paren
id|RESIDUAL
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Tell the user we didn&squot;t find anything. */
id|puts
c_func
(paren
l_string|&quot;No residual data found.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* First, figure out what kind of host bridge we are on.  If it&squot;s&n;&t; * an MPC10x, we can ask it directly how much memory it has.&n;&t; * Otherwise, see if the residual data has anything.  This isn&squot;t&n;&t; * the best way, but it can be the only way.  If there&squot;s nothing,&n;&t; * assume 32MB. -- Tom.&n;&t; */
multiline_comment|/* See what our host bridge is. */
id|pci_read_config_32
c_func
(paren
l_int|0x00
comma
l_int|0x00
comma
op_amp
id|pci_viddid
)paren
suffix:semicolon
id|pci_did
op_assign
(paren
id|pci_viddid
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* See if we are on an MPC10x. */
r_if
c_cond
(paren
(paren
(paren
id|pci_viddid
op_amp
l_int|0xffff
)paren
op_eq
id|PCI_VENDOR_ID_MOTOROLA
)paren
op_logical_and
(paren
(paren
id|pci_did
op_eq
id|PCI_DEVICE_ID_MOTOROLA_MPC105
)paren
op_logical_or
(paren
id|pci_did
op_eq
id|PCI_DEVICE_ID_MOTOROLA_MPC106
)paren
op_logical_or
(paren
id|pci_did
op_eq
id|PCI_DEVICE_ID_MOTOROLA_MPC107
)paren
)paren
)paren
id|TotalMemory
op_assign
id|get_mem_size
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If it&squot;s not, see if we have anything in the residual data. */
r_else
r_if
c_cond
(paren
id|residual
op_logical_and
id|residual-&gt;TotalMemory
)paren
id|TotalMemory
op_assign
id|residual-&gt;TotalMemory
suffix:semicolon
multiline_comment|/* Fall back to hard-coding 32MB. */
r_else
id|TotalMemory
op_assign
l_int|32
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* assume the chunk below 8M is free */
id|end_avail
op_assign
(paren
r_char
op_star
)paren
l_int|0x00800000
suffix:semicolon
multiline_comment|/*&n;&t; * We link ourself to 0x00800000.  When we run, we relocate&n;&t; * ourselves there.  So we just need __image_begin for the&n;&t; * start. -- Tom&n;&t; */
id|zimage_start
op_assign
(paren
r_char
op_star
)paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
id|zimage_size
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_end
)paren
op_minus
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
id|initrd_size
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_end
)paren
op_minus
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The zImage and initrd will be between start and _end, so they&squot;ve&n;&t; * already been moved once.  We&squot;re good to go now. -- Tom&n;&t; */
id|avail_ram
op_assign
(paren
r_char
op_star
)paren
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|_end
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;zimage at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|zimage_start
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|zimage_size
op_plus
id|zimage_start
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;initrd at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_end
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|avail_ram
op_assign
(paren
r_char
op_star
)paren
l_int|0x00400000
suffix:semicolon
id|end_avail
op_assign
(paren
r_char
op_star
)paren
l_int|0x00800000
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;avail ram:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|avail_ram
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|end_avail
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|keyb_present
)paren
id|CRT_tstc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Forces keyboard to be initialized */
id|puts
c_func
(paren
l_string|&quot;&bslash;nLinux/PPC load: &quot;
)paren
suffix:semicolon
id|cp
op_assign
id|cmd_line
suffix:semicolon
id|memcpy
(paren
id|cmd_line
comma
id|cmd_preset
comma
r_sizeof
(paren
id|cmd_preset
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
)paren
id|putc
c_func
(paren
op_star
id|cp
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|timer
op_increment
OL
l_int|5
op_star
l_int|1000
)paren
(brace
r_if
c_cond
(paren
id|tstc
c_func
(paren
)paren
)paren
(brace
r_while
c_loop
(paren
(paren
id|ch
op_assign
id|getc
c_func
(paren
)paren
)paren
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
id|ch
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
multiline_comment|/* Test for backspace/delete */
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;b&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;&bslash;177&squot;
)paren
(brace
r_if
c_cond
(paren
id|cp
op_ne
id|cmd_line
)paren
(brace
id|cp
op_decrement
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;b &bslash;b&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Test for ^x/^u (and wipe the line) */
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;030&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;&bslash;025&squot;
)paren
(brace
r_while
c_loop
(paren
id|cp
op_ne
id|cmd_line
)paren
(brace
id|cp
op_decrement
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;b &bslash;b&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|cp
op_increment
op_assign
id|ch
suffix:semicolon
id|putc
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
multiline_comment|/* Exit &squot;timer&squot; loop */
)brace
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* 1 msec */
)brace
op_star
id|cp
op_assign
l_int|0
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;nUncompressing Linux...&quot;
)paren
suffix:semicolon
id|gunzip
c_func
(paren
l_int|0
comma
l_int|0x400000
comma
id|zimage_start
comma
op_amp
id|zimage_size
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_multi
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;Parking cpu1 at 0xc0&bslash;n&quot;
)paren
suffix:semicolon
id|residual-&gt;VitalProductData.SmpIar
op_assign
(paren
r_int
r_int
)paren
l_int|0xc0
suffix:semicolon
id|residual-&gt;Cpus
(braket
l_int|1
)braket
dot
id|CpuState
op_assign
id|CPU_GOOD
suffix:semicolon
id|hold_residual-&gt;VitalProductData.Reserved5
op_assign
l_int|0xdeadbeef
suffix:semicolon
)brace
(brace
r_struct
id|bi_record
op_star
id|rec
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
id|_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|zimage_size
)paren
op_plus
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_FIRST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_BOOTLOADER_ID
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|rec-&gt;data
comma
l_string|&quot;prepboot&quot;
comma
l_int|9
)paren
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
l_int|8
op_plus
l_int|1
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_MACHTYPE
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
id|_MACH_prep
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_MEMSIZE
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
id|TotalMemory
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_CMD_LINE
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|rec-&gt;data
comma
id|cmd_line
comma
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
l_int|1
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
id|rec-&gt;tag
op_assign
id|BI_INITRD
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
id|initrd_size
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
id|rec-&gt;tag
op_assign
id|BI_LAST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
id|puts
c_func
(paren
l_string|&quot;Now booting the kernel&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|hold_residual
suffix:semicolon
)brace
eof
