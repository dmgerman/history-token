multiline_comment|/*&n; * include/asm-arh/arch-ixp2000/platform.h&n; *&n; * Various bits of code used by platform-level code.&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2004 (c) MontaVista Software, Inc. &n; * &n; * This file is licensed under  the terms of the GNU General Public &n; * License version 2. This program is licensed &quot;as is&quot; without any &n; * warranty of any kind, whether express or implied.&n; */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * The IXP2400 B0 silicon contains an errata that causes writes to &n; * on-chip I/O register to not complete fully. What this means is&n; * that if you have a write to on-chip I/O followed by a back-to-back&n; * read or write, the first write will happend twice. OR...if it&squot;s&n; * not a back-to-back trasaction, the read or write will generate &n; * incorrect data.&n; *&n; * The official work around for this is to set the on-chip I/O regions&n; * as XCB=101 and then force a read-back from the register.&n; *&n; */
macro_line|#if defined(CONFIG_ARCH_ENP2611) || defined(CONFIG_ARCH_IXDP2400) || defined(CONFIG_ARCH_IXDP2401)
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* Pickup local_irq_ functions */
DECL|function|ixp2000_reg_write
r_static
r_inline
r_void
id|ixp2000_reg_write
c_func
(paren
r_volatile
r_int
r_int
op_star
id|reg
comma
r_int
r_int
id|val
)paren
(brace
r_volatile
r_int
r_int
id|dummy
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
op_star
id|reg
op_assign
id|val
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|dummy
op_assign
op_star
id|reg
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|ixp2000_reg_write
mdefine_line|#define&t;ixp2000_reg_write(reg, val) (*reg = val)
macro_line|#endif&t;/* IXDP2400 || IXDP2401 */
multiline_comment|/*&n; * Boards may multiplex different devices on the 2nd channel of &n; * the slowport interface that each need different configuration &n; * settings.  For example, the IXDP2400 uses channel 2 on the interface &n; * to access the CPLD, the switch fabric card, and te media card.  Each &n; * one needs a different mode so drivers must save/restore the mode &n; * before and after each operation.  &n; *&n; * acquire_slowport(&amp;your_config);&n; * ...&n; * do slowport operations&n; * ...&n; * release_slowport();&n; *&n; * Note that while you have the slowport, you are holding a spinlock,&n; * so your code should be written as if you explicitly acquired a lock.&n; *&n; * The configuration only affects device 2 on the slowport, so the&n; * MTD map driver does not acquire/release the slowport.  &n; */
DECL|struct|slowport_cfg
r_struct
id|slowport_cfg
(brace
DECL|member|CCR
r_int
r_int
id|CCR
suffix:semicolon
multiline_comment|/* Clock divide */
DECL|member|WTC
r_int
r_int
id|WTC
suffix:semicolon
multiline_comment|/* Write Timing Control */
DECL|member|RTC
r_int
r_int
id|RTC
suffix:semicolon
multiline_comment|/* Read Timing Control */
DECL|member|PCR
r_int
r_int
id|PCR
suffix:semicolon
multiline_comment|/* Protocol Control Register */
DECL|member|ADC
r_int
r_int
id|ADC
suffix:semicolon
multiline_comment|/* Address/Data Width Control */
)brace
suffix:semicolon
r_void
id|ixp2000_acquire_slowport
c_func
(paren
r_struct
id|slowport_cfg
op_star
comma
r_struct
id|slowport_cfg
op_star
)paren
suffix:semicolon
r_void
id|ixp2000_release_slowport
c_func
(paren
r_struct
id|slowport_cfg
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * IXP2400 A0/A1 and  IXP2800 A0/A1/A2 have broken slowport that requires&n; * tweaking of addresses in the MTD driver.&n; */
DECL|function|ixp2000_has_broken_slowport
r_static
r_inline
r_int
id|ixp2000_has_broken_slowport
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|id
op_assign
op_star
id|IXP2000_PROD_ID
suffix:semicolon
r_int
r_int
id|id_prod
op_assign
id|id
op_amp
(paren
id|IXP2000_MAJ_PROD_TYPE_MASK
op_or
id|IXP2000_MIN_PROD_TYPE_MASK
)paren
suffix:semicolon
r_return
(paren
(paren
(paren
id|id_prod
op_eq
multiline_comment|/* fixed in IXP2400-B0 */
(paren
id|IXP2000_MAJ_PROD_TYPE_IXP2000
op_or
id|IXP2000_MIN_PROD_TYPE_IXP2400
)paren
)paren
op_logical_and
(paren
(paren
id|id
op_amp
id|IXP2000_MAJ_REV_MASK
)paren
op_eq
l_int|0
)paren
)paren
op_logical_or
(paren
(paren
id|id_prod
op_eq
multiline_comment|/* fixed in IXP2800-B0 */
(paren
id|IXP2000_MAJ_PROD_TYPE_IXP2000
op_or
id|IXP2000_MIN_PROD_TYPE_IXP2800
)paren
)paren
op_logical_and
(paren
(paren
id|id
op_amp
id|IXP2000_MAJ_REV_MASK
)paren
op_eq
l_int|0
)paren
)paren
op_logical_or
(paren
(paren
id|id_prod
op_eq
multiline_comment|/* fixed in IXP2850-B0 */
(paren
id|IXP2000_MAJ_PROD_TYPE_IXP2000
op_or
id|IXP2000_MIN_PROD_TYPE_IXP2850
)paren
)paren
op_logical_and
(paren
(paren
id|id
op_amp
id|IXP2000_MAJ_REV_MASK
)paren
op_eq
l_int|0
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_has_flash
r_static
r_inline
r_int
r_int
id|ixp2000_has_flash
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
op_star
id|IXP2000_STRAP_OPTIONS
)paren
op_amp
(paren
id|CFG_BOOT_PROM
)paren
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_is_pcimaster
r_static
r_inline
r_int
r_int
id|ixp2000_is_pcimaster
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
op_star
id|IXP2000_STRAP_OPTIONS
)paren
op_amp
(paren
id|CFG_PCI_BOOT_HOST
)paren
)paren
suffix:semicolon
)brace
r_void
id|ixp2000_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ixp2000_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ixp2000_init_time
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|ixp2000_gettimeoffset
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|pci_sys_data
suffix:semicolon
r_void
id|ixp2000_pci_preinit
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ixp2000_pci_setup
c_func
(paren
r_int
comma
r_struct
id|pci_sys_data
op_star
)paren
suffix:semicolon
r_struct
id|pci_bus
op_star
id|ixp2000_pci_scan_bus
c_func
(paren
r_int
comma
r_struct
id|pci_sys_data
op_star
)paren
suffix:semicolon
r_int
id|ixp2000_pci_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
comma
r_int
r_int
comma
r_int
comma
r_int
comma
id|u32
op_star
)paren
suffix:semicolon
r_int
id|ixp2000_pci_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
comma
r_int
r_int
comma
r_int
comma
r_int
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/*&n; * Several of the IXP2000 systems have banked flash so we need to extend the&n; * flash_platform_data structure with some private pointers&n; */
DECL|struct|ixp2000_flash_data
r_struct
id|ixp2000_flash_data
(brace
DECL|member|platform_data
r_struct
id|flash_platform_data
op_star
id|platform_data
suffix:semicolon
DECL|member|nr_banks
r_int
id|nr_banks
suffix:semicolon
DECL|member|bank_setup
r_int
r_int
(paren
op_star
id|bank_setup
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * GPIO helper functions&n; */
DECL|macro|GPIO_IN
mdefine_line|#define&t;GPIO_IN&t;&t;0
DECL|macro|GPIO_OUT
mdefine_line|#define&t;GPIO_OUT&t;1
r_extern
r_void
id|gpio_line_config
c_func
(paren
r_int
id|line
comma
r_int
id|style
)paren
suffix:semicolon
DECL|function|gpio_line_get
r_static
r_inline
r_int
id|gpio_line_get
c_func
(paren
r_int
id|line
)paren
(brace
r_return
(paren
(paren
(paren
op_star
id|IXP2000_GPIO_PLR
)paren
op_rshift
id|line
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|gpio_line_set
r_static
r_inline
r_void
id|gpio_line_set
c_func
(paren
r_int
id|line
comma
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_POSR
comma
(paren
l_int|1
op_lshift
id|line
)paren
)paren
suffix:semicolon
r_else
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_POCR
comma
(paren
l_int|1
op_lshift
id|line
)paren
)paren
suffix:semicolon
)brace
DECL|struct|ixp2000_i2c_pins
r_struct
id|ixp2000_i2c_pins
(brace
DECL|member|sda_pin
r_int
r_int
id|sda_pin
suffix:semicolon
DECL|member|scl_pin
r_int
r_int
id|scl_pin
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*  !__ASSEMBLY__ */
eof
