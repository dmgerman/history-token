multiline_comment|/*&n; * arch/ppc/platforms/sandpoint_setup.c&n; *&n; * Board setup routines for the Motorola SPS Sandpoint Test Platform.&n; *&n; * Author: Mark A. Greer&n; *&t; mgreer@mvista.com&n; *&n; * 2000-2003 (c) MontaVista Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * This file adds support for the Motorola SPS Sandpoint Test Platform.&n; * These boards have a PPMC slot for the processor so any combination&n; * of cpu and host bridge can be attached.  This port is for an 8240 PPMC&n; * module from Motorola SPS and other closely related cpu/host bridge&n; * combinations (e.g., 750/755/7400 with MPC107 host bridge).&n; * The sandpoint itself has a Windbond 83c553 (PCI-ISA bridge, 2 DMA ctlrs, 2&n; * cascaded 8259 interrupt ctlrs, 8254 Timer/Counter, and an IDE ctlr), a&n; * National 87308 (RTC, 2 UARTs, Keyboard &amp; mouse ctlrs, and a floppy ctlr),&n; * and 4 PCI slots (only 2 of which are usable; the other 2 are keyed for 3.3V&n; * but are really 5V).&n; *&n; * The firmware on the sandpoint is called DINK (not my acronym :).  This port&n; * depends on DINK to do some basic initialization (e.g., initialize the memory&n; * ctlr) and to ensure that the processor is using MAP B (CHRP map).&n; *&n; * The switch settings for the Sandpoint board MUST be as follows:&n; * &t;S3: down&n; * &t;S4: up&n; * &t;S5: up&n; * &t;S6: down&n; *&n; * &squot;down&squot; is in the direction from the PCI slots towards the PPMC slot;&n; * &squot;up&squot; is in the direction from the PPMC slot towards the PCI slots.&n; * Be careful, the way the sandpoint board is installed in XT chasses will&n; * make the directions reversed.&n; *&n; * Since Motorola listened to our suggestions for improvement, we now have&n; * the Sandpoint X3 board.  All of the PCI slots are available, it uses&n; * the serial interrupt interface (just a hardware thing we need to&n; * configure properly).&n; *&n; * Use the default X3 switch settings.  The interrupts are then:&n; *&t;&t;EPIC&t;Source&n; *&t;&t;  0&t;SIOINT &t;&t;(8259, active low)&n; *&t;&t;  1&t;PCI #1&n; *&t;&t;  2&t;PCI #2&n; *&t;&t;  3&t;PCI #3&n; *&t;&t;  4&t;PCI #4&n; *&t;&t;  7&t;Winbond INTC&t;(IDE interrupt)&n; *&t;&t;  8&t;Winbond INTD&t;(IDE interrupt)&n; *&n; *&n; * Motorola has finally released a version of DINK32 that correctly&n; * (seemingly) initalizes the memory controller correctly, regardless&n; * of the amount of memory in the system.  Once a method of determining&n; * what version of DINK initializes the system for us, if applicable, is&n; * found, we can hopefully stop hardcoding 32MB of RAM.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;&t;/* for linux/serial_core.h */
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/vga.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mpc10x.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &quot;sandpoint.h&quot;
multiline_comment|/* Set non-zero if an X2 Sandpoint detected. */
DECL|variable|sandpoint_is_x2
r_static
r_int
id|sandpoint_is_x2
suffix:semicolon
DECL|variable|__res
r_int
r_char
id|__res
(braket
r_sizeof
(paren
id|bd_t
)paren
)braket
suffix:semicolon
r_static
r_void
id|sandpoint_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|sandpoint_probe_type
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Define all of the IRQ senses and polarities.  Taken from the&n; * Sandpoint X3 User&squot;s manual.&n; */
DECL|variable|__initdata
r_static
id|u_char
id|sandpoint_openpic_initsenses
(braket
)braket
id|__initdata
op_assign
(brace
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* 0: SIOINT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* 2: PCI Slot 1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* 3: PCI Slot 2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* 4: PCI Slot 3 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* 5: PCI Slot 4 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* 8: IDE (INT C) */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
multiline_comment|/* 9: IDE (INT D) */
)brace
suffix:semicolon
multiline_comment|/*&n; * Motorola SPS Sandpoint interrupt routing.&n; */
r_static
r_inline
r_int
DECL|function|x3_map_irq
id|x3_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t; *&t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; * &t;   A   B   C   D&n;&t; */
(brace
(brace
l_int|16
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 11 - i8259 on Winbond */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 12 - unused */
(brace
l_int|18
comma
l_int|21
comma
l_int|20
comma
l_int|19
)brace
comma
multiline_comment|/* IDSEL 13 - PCI slot 1 */
(brace
l_int|19
comma
l_int|18
comma
l_int|21
comma
l_int|20
)brace
comma
multiline_comment|/* IDSEL 14 - PCI slot 2 */
(brace
l_int|20
comma
l_int|19
comma
l_int|18
comma
l_int|21
)brace
comma
multiline_comment|/* IDSEL 15 - PCI slot 3 */
(brace
l_int|21
comma
l_int|20
comma
l_int|19
comma
l_int|18
)brace
comma
multiline_comment|/* IDSEL 16 - PCI slot 4 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|11
comma
id|max_idsel
op_assign
l_int|16
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|x2_map_irq
id|x2_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t; *&t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; * &t;   A   B   C   D&n;&t; */
(brace
(brace
l_int|18
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 11 - i8259 on Windbond */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 12 - unused */
(brace
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
)brace
comma
multiline_comment|/* IDSEL 13 - PCI slot 1 */
(brace
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|16
)brace
comma
multiline_comment|/* IDSEL 14 - PCI slot 2 */
(brace
l_int|18
comma
l_int|19
comma
l_int|16
comma
l_int|17
)brace
comma
multiline_comment|/* IDSEL 15 - PCI slot 3 */
(brace
l_int|19
comma
l_int|16
comma
l_int|17
comma
l_int|18
)brace
comma
multiline_comment|/* IDSEL 16 - PCI slot 4 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|11
comma
id|max_idsel
op_assign
l_int|16
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|sandpoint_setup_winbond_83553
id|sandpoint_setup_winbond_83553
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
(brace
r_int
id|devfn
suffix:semicolon
multiline_comment|/*&n;&t; * Route IDE interrupts directly to the 8259&squot;s IRQ 14 &amp; 15.&n;&t; * We can&squot;t route the IDE interrupt to PCI INTC# or INTD# because those&n;&t; * woule interfere with the PMC&squot;s INTC# and INTD# lines.&n;&t; */
multiline_comment|/*&n;&t; * Winbond Fcn 0&n;&t; */
id|devfn
op_assign
id|PCI_DEVFN
c_func
(paren
l_int|11
comma
l_int|0
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x43
comma
multiline_comment|/* IDE Interrupt Routing Control */
l_int|0xef
)paren
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x44
comma
multiline_comment|/* PCI Interrupt Routing Control */
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* Want ISA memory cycles to be forwarded to PCI bus */
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x48
comma
multiline_comment|/* ISA-to-PCI Addr Decoder Control */
l_int|0xf0
)paren
suffix:semicolon
multiline_comment|/* Enable RTC and Keyboard address locations.  */
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x4d
comma
multiline_comment|/* Chip Select Control Register */
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Enable Port 92.  */
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x4e
comma
multiline_comment|/* AT System Control Register */
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Winbond Fcn 1&n;&t; */
id|devfn
op_assign
id|PCI_DEVFN
c_func
(paren
l_int|11
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Put IDE controller into native mode. */
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x09
comma
multiline_comment|/* Programming interface Register */
l_int|0x8f
)paren
suffix:semicolon
multiline_comment|/* Init IRQ routing, enable both ports, disable fast 16 */
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x40
comma
multiline_comment|/* IDE Control/Status Register */
l_int|0x00ff0011
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* On the sandpoint X2, we must avoid sending configuration cycles to&n; * device #12 (IDSEL addr = AD12).&n; */
r_static
r_int
DECL|function|x2_exclude_device
id|x2_exclude_device
c_func
(paren
id|u_char
id|bus
comma
id|u_char
id|devfn
)paren
(brace
r_if
c_cond
(paren
(paren
id|bus
op_eq
l_int|0
)paren
op_logical_and
(paren
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_eq
id|SANDPOINT_HOST_BRIDGE_IDSEL
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_else
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|sandpoint_find_bridges
id|sandpoint_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|hose
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
suffix:semicolon
id|hose-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|mpc10x_bridge_init
c_func
(paren
id|hose
comma
id|MPC10X_MEM_MAP_B
comma
id|MPC10X_MEM_MAP_B
comma
id|MPC10X_MAPB_EUMB_BASE
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Do early winbond init, then scan PCI bus */
id|sandpoint_setup_winbond_83553
c_func
(paren
id|hose
)paren
suffix:semicolon
id|hose-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|hose-&gt;first_busno
)paren
suffix:semicolon
id|ppc_md.pcibios_fixup
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.pcibios_fixup_bus
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
r_if
c_cond
(paren
id|sandpoint_is_x2
)paren
(brace
id|ppc_md.pci_map_irq
op_assign
id|x2_map_irq
suffix:semicolon
id|ppc_md.pci_exclude_device
op_assign
id|x2_exclude_device
suffix:semicolon
)brace
r_else
id|ppc_md.pci_map_irq
op_assign
id|x3_map_irq
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Bridge init failed&quot;
comma
l_int|0x100
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Host bridge init failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|sandpoint_setup_arch
id|sandpoint_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Probe for Sandpoint model */
id|sandpoint_probe_type
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sandpoint_is_x2
)paren
id|epic_serial_mode
op_assign
l_int|0
suffix:semicolon
id|loops_per_jiffy
op_assign
l_int|100000000
op_div
id|HZ
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_else
macro_line|#endif
macro_line|#ifdef&t;CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_HDA1
suffix:semicolon
macro_line|#endif
multiline_comment|/* Lookup PCI host bridges */
id|sandpoint_find_bridges
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Motorola SPS Sandpoint Test Platform&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Port by MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* DINK32 12.3 and below do not correctly enable any caches.&n;&t; * We will do this now with good known values.  Future versions&n;&t; * of DINK32 are supposed to get this correct.&n;&t; */
r_if
c_cond
(paren
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_SPEC7450
)paren
)paren
multiline_comment|/* 745x is different.  We only want to pass along enable. */
id|_set_L2CR
c_func
(paren
id|L2CR_L2E
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_L2CR
)paren
)paren
multiline_comment|/* All modules have 1MB of L2.  We also assume that an&n;&t;&t; * L2 divisor of 3 will work.&n;&t;&t; */
id|_set_L2CR
c_func
(paren
id|L2CR_L2E
op_or
id|L2CR_L2SIZ_1MB
op_or
id|L2CR_L2CLK_DIV3
op_or
id|L2CR_L2RAM_PIPE
op_or
id|L2CR_L2OH_1_0
op_or
id|L2CR_L2DF
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Untested right now. */
r_if
c_cond
(paren
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_L3CR
)paren
)paren
(brace
multiline_comment|/* Magic value. */
id|_set_L3CR
c_func
(paren
l_int|0x8f032000
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|macro|SANDPOINT_87308_CFG_ADDR
mdefine_line|#define&t;SANDPOINT_87308_CFG_ADDR&t;&t;0x15c
DECL|macro|SANDPOINT_87308_CFG_DATA
mdefine_line|#define&t;SANDPOINT_87308_CFG_DATA&t;&t;0x15d
DECL|macro|SANDPOINT_87308_CFG_INB
mdefine_line|#define&t;SANDPOINT_87308_CFG_INB(addr, byte) {&t;&t;&t;&t;&bslash;&n;&t;outb((addr), SANDPOINT_87308_CFG_ADDR);&t;&t;&t;&t;&bslash;&n;&t;(byte) = inb(SANDPOINT_87308_CFG_DATA);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SANDPOINT_87308_CFG_OUTB
mdefine_line|#define&t;SANDPOINT_87308_CFG_OUTB(addr, byte) {&t;&t;&t;&t;&bslash;&n;&t;outb((addr), SANDPOINT_87308_CFG_ADDR);&t;&t;&t;&t;&bslash;&n;&t;outb((byte), SANDPOINT_87308_CFG_DATA);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SANDPOINT_87308_SELECT_DEV
mdefine_line|#define SANDPOINT_87308_SELECT_DEV(dev_num) {&t;&t;&t;&t;&bslash;&n;&t;SANDPOINT_87308_CFG_OUTB(0x07, (dev_num));&t;&t;&t;&bslash;&n;}
DECL|macro|SANDPOINT_87308_DEV_ENABLE
mdefine_line|#define&t;SANDPOINT_87308_DEV_ENABLE(dev_num) {&t;&t;&t;&t;&bslash;&n;&t;SANDPOINT_87308_SELECT_DEV(dev_num);&t;&t;&t;&t;&bslash;&n;&t;SANDPOINT_87308_CFG_OUTB(0x30, 0x01);&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * To probe the Sandpoint type, we need to check for a connection between GPIO&n; * pins 6 and 7 on the NS87308 SuperIO.&n; */
DECL|function|sandpoint_probe_type
r_static
r_void
id|__init
id|sandpoint_probe_type
c_func
(paren
r_void
)paren
(brace
id|u8
id|x
suffix:semicolon
multiline_comment|/* First, ensure that the GPIO pins are enabled. */
id|SANDPOINT_87308_SELECT_DEV
c_func
(paren
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* Select GPIO logical device */
id|SANDPOINT_87308_CFG_OUTB
c_func
(paren
l_int|0x60
comma
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* Base address 0x700 */
id|SANDPOINT_87308_CFG_OUTB
c_func
(paren
l_int|0x61
comma
l_int|0x00
)paren
suffix:semicolon
id|SANDPOINT_87308_CFG_OUTB
c_func
(paren
l_int|0x30
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Enable */
multiline_comment|/* Now, set pin 7 to output and pin 6 to input. */
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
l_int|0x701
)paren
op_or
l_int|0x80
)paren
op_amp
l_int|0xbf
comma
l_int|0x701
)paren
suffix:semicolon
multiline_comment|/* Set push-pull output */
id|outb
c_func
(paren
id|inb
c_func
(paren
l_int|0x702
)paren
op_or
l_int|0x80
comma
l_int|0x702
)paren
suffix:semicolon
multiline_comment|/* Set pull-up on input */
id|outb
c_func
(paren
id|inb
c_func
(paren
l_int|0x703
)paren
op_or
l_int|0x40
comma
l_int|0x703
)paren
suffix:semicolon
multiline_comment|/* Set output high and check */
id|x
op_assign
id|inb
c_func
(paren
l_int|0x700
)paren
suffix:semicolon
id|outb
c_func
(paren
id|x
op_or
l_int|0x80
comma
l_int|0x700
)paren
suffix:semicolon
id|x
op_assign
id|inb
c_func
(paren
l_int|0x700
)paren
suffix:semicolon
id|sandpoint_is_x2
op_assign
op_logical_neg
(paren
id|x
op_amp
l_int|0x40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
op_logical_and
id|sandpoint_is_x2
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;High output says X2&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set output low and check */
id|outb
c_func
(paren
id|x
op_amp
l_int|0x7f
comma
l_int|0x700
)paren
suffix:semicolon
id|sandpoint_is_x2
op_or_assign
id|inb
c_func
(paren
l_int|0x700
)paren
op_amp
l_int|0x40
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
op_logical_and
id|sandpoint_is_x2
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Low output says X2&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
op_logical_and
op_logical_neg
id|sandpoint_is_x2
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Sandpoint is X3&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Fix IDE interrupts.&n; */
r_static
r_int
id|__init
DECL|function|sandpoint_fix_winbond_83553
id|sandpoint_fix_winbond_83553
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Make some 8259 interrupt level sensitive */
id|outb
c_func
(paren
l_int|0xe0
comma
l_int|0x4d0
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xde
comma
l_int|0x4d1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sandpoint_fix_winbond_83553
id|arch_initcall
c_func
(paren
id|sandpoint_fix_winbond_83553
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize the ISA devices on the Nat&squot;l PC87308VUL SuperIO chip.&n; */
r_static
r_int
id|__init
DECL|function|sandpoint_setup_natl_87308
id|sandpoint_setup_natl_87308
c_func
(paren
r_void
)paren
(brace
id|u_char
id|reg
suffix:semicolon
multiline_comment|/*&n;&t; * Enable all the devices on the Super I/O chip.&n;&t; */
id|SANDPOINT_87308_SELECT_DEV
c_func
(paren
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Select kbd logical device */
id|SANDPOINT_87308_CFG_OUTB
c_func
(paren
l_int|0xf0
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Set KBC clock to 8 Mhz */
id|SANDPOINT_87308_DEV_ENABLE
c_func
(paren
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Enable keyboard */
id|SANDPOINT_87308_DEV_ENABLE
c_func
(paren
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Enable mouse */
id|SANDPOINT_87308_DEV_ENABLE
c_func
(paren
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* Enable rtc */
id|SANDPOINT_87308_DEV_ENABLE
c_func
(paren
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Enable fdc (floppy) */
id|SANDPOINT_87308_DEV_ENABLE
c_func
(paren
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* Enable parallel */
id|SANDPOINT_87308_DEV_ENABLE
c_func
(paren
l_int|0x05
)paren
suffix:semicolon
multiline_comment|/* Enable UART 2 */
id|SANDPOINT_87308_CFG_OUTB
c_func
(paren
l_int|0xf0
comma
l_int|0x82
)paren
suffix:semicolon
multiline_comment|/* Enable bank select regs */
id|SANDPOINT_87308_DEV_ENABLE
c_func
(paren
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/* Enable UART 1 */
id|SANDPOINT_87308_CFG_OUTB
c_func
(paren
l_int|0xf0
comma
l_int|0x82
)paren
suffix:semicolon
multiline_comment|/* Enable bank select regs */
multiline_comment|/* Set up floppy in PS/2 mode */
id|outb
c_func
(paren
l_int|0x09
comma
id|SIO_CONFIG_RA
)paren
suffix:semicolon
id|reg
op_assign
id|inb
c_func
(paren
id|SIO_CONFIG_RD
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|reg
op_amp
l_int|0x3F
)paren
op_or
l_int|0x40
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|SIO_CONFIG_RD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|SIO_CONFIG_RD
)paren
suffix:semicolon
multiline_comment|/* Have to write twice to change! */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sandpoint_setup_natl_87308
id|arch_initcall
c_func
(paren
id|sandpoint_setup_natl_87308
)paren
suffix:semicolon
r_static
r_int
id|__init
DECL|function|sandpoint_request_io
id|sandpoint_request_io
c_func
(paren
r_void
)paren
(brace
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x20
comma
l_int|0x20
comma
l_string|&quot;pic1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xa0
comma
l_int|0x20
comma
l_string|&quot;pic2&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sandpoint_request_io
id|arch_initcall
c_func
(paren
id|sandpoint_request_io
)paren
suffix:semicolon
multiline_comment|/*&n; * Interrupt setup and service.  Interrrupts on the Sandpoint come&n; * from the four PCI slots plus the 8259 in the Winbond Super I/O (SIO).&n; * The 8259 is cascaded from EPIC IRQ0, IRQ1-4 map to PCI slots 1-4,&n; * IDE is on EPIC 7 and 8.&n; */
r_static
r_void
id|__init
DECL|function|sandpoint_init_IRQ
id|sandpoint_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|OpenPIC_InitSenses
op_assign
id|sandpoint_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|sandpoint_openpic_initsenses
)paren
suffix:semicolon
id|mpc10x_set_openpic
c_func
(paren
)paren
suffix:semicolon
id|openpic_hookup_cascade
c_func
(paren
id|sandpoint_is_x2
ques
c_cond
l_int|17
suffix:colon
id|NUM_8259_INTERRUPTS
comma
l_string|&quot;82c59 cascade&quot;
comma
id|i8259_irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * openpic_init() has set up irq_desc[16-31] to be openpic&n;&t; * interrupts.  We need to set irq_desc[0-15] to be i8259&n;&t; * interrupts.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_8259_INTERRUPTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259_pic
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The EPIC allows for a read in the range of 0xFEF00000 -&gt;&n;&t; * 0xFEFFFFFF to generate a PCI interrupt-acknowledge transaction.&n;&t; */
id|i8259_init
c_func
(paren
l_int|0xfef00000
)paren
suffix:semicolon
)brace
r_static
id|u32
DECL|function|sandpoint_irq_canonicalize
id|sandpoint_irq_canonicalize
c_func
(paren
id|u32
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
r_return
l_int|9
suffix:semicolon
r_else
r_return
id|irq
suffix:semicolon
)brace
r_static
r_int
r_int
id|__init
DECL|function|sandpoint_find_end_of_memory
id|sandpoint_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|bp
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_if
c_cond
(paren
id|bp-&gt;bi_memsize
)paren
r_return
id|bp-&gt;bi_memsize
suffix:semicolon
multiline_comment|/* DINK32 13.0 correctly initalizes things, so iff you use&n;&t; * this you _should_ be able to change this instead of a&n;&t; * hardcoded value. */
macro_line|#if 0
r_return
id|mpc10x_get_mem_size
c_func
(paren
id|MPC10X_MEM_MAP_B
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|32
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
id|__init
DECL|function|sandpoint_map_io
id|sandpoint_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0xfe000000
comma
l_int|0xfe000000
comma
l_int|0x02000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sandpoint_restart
id|sandpoint_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set exception prefix high - to the firmware */
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_IP
)paren
suffix:semicolon
multiline_comment|/* Reset system via Port 92 */
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x92
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
l_int|0x92
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Spin until reset happens */
)brace
r_static
r_void
DECL|function|sandpoint_power_off
id|sandpoint_power_off
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* No way to shut power off with software */
multiline_comment|/* NOTREACHED */
)brace
r_static
r_void
DECL|function|sandpoint_halt
id|sandpoint_halt
c_func
(paren
r_void
)paren
(brace
id|sandpoint_power_off
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_static
r_int
DECL|function|sandpoint_show_cpuinfo
id|sandpoint_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: Motorola SPS&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: Sandpoint&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
multiline_comment|/*&n; * IDE support.&n; */
DECL|variable|sandpoint_ide_ports_known
r_static
r_int
id|sandpoint_ide_ports_known
op_assign
l_int|0
suffix:semicolon
DECL|variable|sandpoint_ide_regbase
r_static
r_int
r_int
id|sandpoint_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|sandpoint_ide_ctl_regbase
r_static
r_int
r_int
id|sandpoint_ide_ctl_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|sandpoint_idedma_regbase
r_static
r_int
r_int
id|sandpoint_idedma_regbase
suffix:semicolon
r_static
r_void
DECL|function|sandpoint_ide_probe
id|sandpoint_ide_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_82C105
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
)paren
(brace
id|sandpoint_ide_regbase
(braket
l_int|0
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|sandpoint_ide_regbase
(braket
l_int|1
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
suffix:semicolon
id|sandpoint_ide_ctl_regbase
(braket
l_int|0
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|sandpoint_ide_ctl_regbase
(braket
l_int|1
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|3
)braket
dot
id|start
suffix:semicolon
id|sandpoint_idedma_regbase
op_assign
id|pdev-&gt;resource
(braket
l_int|4
)braket
dot
id|start
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
id|sandpoint_ide_ports_known
op_assign
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|sandpoint_ide_default_irq
id|sandpoint_ide_default_irq
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_if
c_cond
(paren
id|sandpoint_ide_ports_known
op_eq
l_int|0
)paren
id|sandpoint_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
id|sandpoint_ide_regbase
(braket
l_int|0
)braket
)paren
r_return
id|SANDPOINT_IDE_INT0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
id|sandpoint_ide_regbase
(braket
l_int|1
)braket
)paren
r_return
id|SANDPOINT_IDE_INT1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|sandpoint_ide_default_io_base
id|sandpoint_ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|sandpoint_ide_ports_known
op_eq
l_int|0
)paren
id|sandpoint_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_return
id|sandpoint_ide_regbase
(braket
id|index
)braket
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|sandpoint_ide_init_hwif_ports
id|sandpoint_ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
r_int
r_int
id|data_port
comma
r_int
r_int
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
r_int
r_int
id|reg
op_assign
id|data_port
suffix:semicolon
id|uint
id|alt_status_base
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data_port
op_eq
id|sandpoint_ide_regbase
(braket
l_int|0
)braket
)paren
(brace
id|alt_status_base
op_assign
id|sandpoint_ide_ctl_regbase
(braket
l_int|0
)braket
op_plus
l_int|2
suffix:semicolon
id|hw-&gt;irq
op_assign
l_int|14
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data_port
op_eq
id|sandpoint_ide_regbase
(braket
l_int|1
)braket
)paren
(brace
id|alt_status_base
op_assign
id|sandpoint_ide_ctl_regbase
(braket
l_int|1
)braket
op_plus
l_int|2
suffix:semicolon
id|hw-&gt;irq
op_assign
l_int|15
suffix:semicolon
)brace
r_else
(brace
id|alt_status_base
op_assign
l_int|0
suffix:semicolon
id|hw-&gt;irq
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctrl_port
)paren
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctrl_port
suffix:semicolon
)brace
r_else
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|alt_status_base
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
(brace
op_star
id|irq
op_assign
id|hw-&gt;irq
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * Set BAT 3 to map 0xf8000000 to end of physical memory space 1-to-1.&n; */
r_static
id|__inline__
r_void
DECL|function|sandpoint_set_bat
id|sandpoint_set_bat
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|bat3u
comma
id|bat3l
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot; lis %0,0xf800&bslash;n&t;&bslash;&n;&t;&t;&t;ori %1,%0,0x002a&bslash;n&t;&bslash;&n;&t;&t;&t;ori %0,%0,0x0ffe&bslash;n&t;&bslash;&n;&t;&t;&t;mtspr 0x21e,%0&bslash;n&t;&bslash;&n;&t;&t;&t;mtspr 0x21f,%1&bslash;n&t;&bslash;&n;&t;&t;&t;isync&bslash;n&t;&t;&t;&bslash;&n;&t;&t;&t;sync &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|bat3u
)paren
comma
l_string|&quot;=r&quot;
(paren
id|bat3l
)paren
)paren
suffix:semicolon
)brace
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* ASSUMPTION:  If both r3 (bd_t pointer) and r6 (cmdline pointer)&n;&t; * are non-zero, then we should use the board info from the bd_t&n;&t; * structure and the cmdline pointed to by r6 instead of the&n;&t; * information from birecs, if any.  Otherwise, use the information&n;&t; * from birecs as discovered by the preceeding call to&n;&t; * parse_bootinfo().  This rule should work with both PPCBoot, which&n;&t; * uses a bd_t board info structure, and the kernel boot wrapper,&n;&t; * which uses birecs.&n;&t; */
r_if
c_cond
(paren
id|r3
op_logical_and
id|r6
)paren
(brace
multiline_comment|/* copy board info structure */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|__res
comma
(paren
r_void
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
comma
r_sizeof
(paren
id|bd_t
)paren
)paren
suffix:semicolon
multiline_comment|/* copy command line */
op_star
(paren
r_char
op_star
)paren
(paren
id|r7
op_plus
id|KERNELBASE
)paren
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|cmd_line
comma
(paren
r_char
op_star
)paren
(paren
id|r6
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* take care of initrd if we have one */
r_if
c_cond
(paren
id|r4
)paren
(brace
id|initrd_start
op_assign
id|r4
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|r5
op_plus
id|KERNELBASE
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
multiline_comment|/* Map in board regs, etc. */
id|sandpoint_set_bat
c_func
(paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|MPC10X_MAPB_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|MPC10X_MAPB_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|MPC10X_MAPB_DRAM_OFFSET
suffix:semicolon
id|ISA_DMA_THRESHOLD
op_assign
l_int|0x00ffffff
suffix:semicolon
id|DMA_MODE_READ
op_assign
l_int|0x44
suffix:semicolon
id|DMA_MODE_WRITE
op_assign
l_int|0x48
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|sandpoint_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|sandpoint_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_canonicalize
op_assign
id|sandpoint_irq_canonicalize
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|sandpoint_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|sandpoint_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|sandpoint_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|sandpoint_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|sandpoint_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|sandpoint_map_io
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_PC97307
comma
l_int|0x70
comma
l_int|0x00
comma
l_int|0x71
comma
l_int|8
)paren
suffix:semicolon
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|todc_calibrate_decr
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_mc146818_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_mc146818_write_val
suffix:semicolon
macro_line|#ifdef CONFIG_KGDB
id|ppc_md.kgdb_map_scc
op_assign
id|gen550_kgdb_map_scc
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|gen550_progress
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
id|ppc_ide_md.default_irq
op_assign
id|sandpoint_ide_default_irq
suffix:semicolon
id|ppc_ide_md.default_io_base
op_assign
id|sandpoint_ide_default_io_base
suffix:semicolon
id|ppc_ide_md.ide_init_hwif
op_assign
id|sandpoint_ide_init_hwif_ports
suffix:semicolon
macro_line|#endif
)brace
eof
