multiline_comment|/* $Id: sbus.c,v 1.100 2002/01/24 15:36:24 davem Exp $&n; * sbus.c:  SBus support routines.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/bpp.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pcic.h&gt;&t;&t;/* pcic_present */
DECL|variable|sbus_root
r_struct
id|sbus_bus
op_star
id|sbus_root
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|linux_prom_irqs
id|irqs
(braket
id|PROMINTR_MAX
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* Perhaps when I figure out more about the iommu we&squot;ll put a&n; * device registration routine here that probe_sbus() calls to&n; * setup the iommu for each Sbus.&n; */
multiline_comment|/* We call this for each SBus device, and fill the structure based&n; * upon the prom device tree.  We return the start of memory after&n; * the things we have allocated.&n; */
multiline_comment|/* #define DEBUG_FILL */
DECL|function|fill_sbus_device
r_static
r_void
id|__init
id|fill_sbus_device
c_func
(paren
r_int
id|prom_node
comma
r_struct
id|sbus_dev
op_star
id|sdev
)paren
(brace
r_int
r_int
id|address
comma
id|base
suffix:semicolon
r_int
id|len
suffix:semicolon
id|sdev-&gt;prom_node
op_assign
id|prom_node
suffix:semicolon
id|prom_getstring
c_func
(paren
id|prom_node
comma
l_string|&quot;name&quot;
comma
id|sdev-&gt;prom_name
comma
r_sizeof
(paren
id|sdev-&gt;prom_name
)paren
)paren
suffix:semicolon
id|address
op_assign
id|prom_getint
c_func
(paren
id|prom_node
comma
l_string|&quot;address&quot;
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|prom_node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|sdev-&gt;reg_addrs
comma
r_sizeof
(paren
id|sdev-&gt;reg_addrs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
)paren
(brace
id|sdev-&gt;num_registers
op_assign
l_int|0
suffix:semicolon
r_goto
id|no_regs
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_mod
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;fill_sbus_device: proplen for regs of %s &quot;
l_string|&quot; was %d, need multiple of %d&bslash;n&quot;
comma
id|sdev-&gt;prom_name
comma
id|len
comma
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
(paren
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
op_star
id|PROMREG_MAX
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;fill_sbus_device: Too many register properties &quot;
l_string|&quot;for device %s, len=%d&bslash;n&quot;
comma
id|sdev-&gt;prom_name
comma
id|len
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|sdev-&gt;num_registers
op_assign
id|len
op_div
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
suffix:semicolon
id|sdev-&gt;ranges_applied
op_assign
l_int|0
suffix:semicolon
id|base
op_assign
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
multiline_comment|/* Compute the slot number. */
r_if
c_cond
(paren
id|base
op_ge
id|SUN_SBUS_BVADDR
op_logical_and
id|sparc_cpu_model
op_eq
id|sun4m
)paren
(brace
id|sdev-&gt;slot
op_assign
id|sbus_dev_slot
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
id|sdev-&gt;slot
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
suffix:semicolon
)brace
id|no_regs
suffix:colon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|prom_node
comma
l_string|&quot;ranges&quot;
comma
(paren
r_char
op_star
)paren
id|sdev-&gt;device_ranges
comma
r_sizeof
(paren
id|sdev-&gt;device_ranges
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
)paren
(brace
id|sdev-&gt;num_device_ranges
op_assign
l_int|0
suffix:semicolon
r_goto
id|no_ranges
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_mod
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;fill_sbus_device: proplen for ranges of %s &quot;
l_string|&quot; was %d, need multiple of %d&bslash;n&quot;
comma
id|sdev-&gt;prom_name
comma
id|len
comma
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
(paren
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
op_star
id|PROMREG_MAX
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;fill_sbus_device: Too many range properties &quot;
l_string|&quot;for device %s, len=%d&bslash;n&quot;
comma
id|sdev-&gt;prom_name
comma
id|len
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|sdev-&gt;num_device_ranges
op_assign
id|len
op_div
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
suffix:semicolon
id|no_ranges
suffix:colon
multiline_comment|/* XXX Unfortunately, IRQ issues are very arch specific.&n;&t; * XXX Pull this crud out into an arch specific area&n;&t; * XXX at some point. -DaveM&n;&t; */
macro_line|#ifdef __sparc_v9__
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|prom_node
comma
l_string|&quot;interrupts&quot;
comma
(paren
r_char
op_star
)paren
id|irqs
comma
r_sizeof
(paren
id|irqs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
op_logical_or
id|len
op_eq
l_int|0
)paren
(brace
id|sdev-&gt;irqs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|sdev-&gt;num_irqs
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|pri
op_assign
id|irqs
(braket
l_int|0
)braket
dot
id|pri
suffix:semicolon
id|sdev-&gt;num_irqs
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pri
OL
l_int|0x20
)paren
id|pri
op_add_assign
id|sdev-&gt;slot
op_star
l_int|8
suffix:semicolon
id|sdev-&gt;irqs
(braket
l_int|0
)braket
op_assign
id|sbus_build_irq
c_func
(paren
id|sdev-&gt;bus
comma
id|pri
)paren
suffix:semicolon
)brace
macro_line|#else
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|prom_node
comma
l_string|&quot;intr&quot;
comma
(paren
r_char
op_star
)paren
id|irqs
comma
r_sizeof
(paren
id|irqs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
)paren
id|len
op_assign
l_int|0
suffix:semicolon
id|sdev-&gt;num_irqs
op_assign
id|len
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;num_irqs
op_eq
l_int|0
)paren
(brace
id|sdev-&gt;irqs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
r_extern
r_int
r_int
id|sun4d_build_irq
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|irq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|sdev-&gt;num_irqs
suffix:semicolon
id|len
op_increment
)paren
id|sdev-&gt;irqs
(braket
id|len
)braket
op_assign
id|sun4d_build_irq
c_func
(paren
id|sdev
comma
id|irqs
(braket
id|len
)braket
dot
id|pri
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|sdev-&gt;num_irqs
suffix:semicolon
id|len
op_increment
)paren
id|sdev-&gt;irqs
(braket
id|len
)braket
op_assign
id|irqs
(braket
id|len
)braket
dot
id|pri
suffix:semicolon
)brace
macro_line|#endif /* !__sparc_v9__ */
)brace
multiline_comment|/* This routine gets called from whoever needs the sbus first, to scan&n; * the SBus device tree.  Currently it just prints out the devices&n; * found on the bus and builds trees of SBUS structs and attached&n; * devices.&n; */
r_extern
r_void
id|iommu_init
c_func
(paren
r_int
id|iommu_node
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
suffix:semicolon
r_extern
r_void
id|iounit_init
c_func
(paren
r_int
id|sbi_node
comma
r_int
id|iounit_node
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
suffix:semicolon
r_void
id|sun4_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_AUXIO
r_extern
r_void
id|auxio_probe
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|sbus_do_child_siblings
r_static
r_void
id|__init
id|sbus_do_child_siblings
c_func
(paren
r_int
id|start_node
comma
r_struct
id|sbus_dev
op_star
id|child
comma
r_struct
id|sbus_dev
op_star
id|parent
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_struct
id|sbus_dev
op_star
id|this_dev
op_assign
id|child
suffix:semicolon
r_int
id|this_node
op_assign
id|start_node
suffix:semicolon
multiline_comment|/* Child already filled in, just need to traverse siblings. */
id|child-&gt;child
op_assign
l_int|NULL
suffix:semicolon
id|child-&gt;parent
op_assign
id|parent
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_node
op_assign
id|prom_getsibling
c_func
(paren
id|this_node
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|this_dev-&gt;next
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dev
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|this_dev
op_assign
id|this_dev-&gt;next
suffix:semicolon
id|this_dev-&gt;next
op_assign
l_int|0
suffix:semicolon
id|this_dev-&gt;parent
op_assign
id|parent
suffix:semicolon
id|this_dev-&gt;bus
op_assign
id|sbus
suffix:semicolon
id|fill_sbus_device
c_func
(paren
id|this_node
comma
id|this_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_getchild
c_func
(paren
id|this_node
)paren
)paren
(brace
id|this_dev-&gt;child
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dev
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|this_dev-&gt;child-&gt;bus
op_assign
id|sbus
suffix:semicolon
id|this_dev-&gt;child-&gt;next
op_assign
l_int|0
suffix:semicolon
id|fill_sbus_device
c_func
(paren
id|prom_getchild
c_func
(paren
id|this_node
)paren
comma
id|this_dev-&gt;child
)paren
suffix:semicolon
id|sbus_do_child_siblings
c_func
(paren
id|prom_getchild
c_func
(paren
id|this_node
)paren
comma
id|this_dev-&gt;child
comma
id|this_dev
comma
id|sbus
)paren
suffix:semicolon
)brace
r_else
(brace
id|this_dev-&gt;child
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * XXX This functions appears to be a distorted version of&n; * prom_sbus_ranges_init(), with all sun4d stuff cut away.&n; * Ask DaveM what is going on here, how is sun4d supposed to work... XXX&n; */
DECL|function|sbus_bus_ranges_init
r_static
r_void
id|__init
id|sbus_bus_ranges_init
c_func
(paren
r_int
id|parent_node
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|sbus-&gt;prom_node
comma
l_string|&quot;ranges&quot;
comma
(paren
r_char
op_star
)paren
id|sbus-&gt;sbus_ranges
comma
r_sizeof
(paren
id|sbus-&gt;sbus_ranges
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
op_logical_or
id|len
op_eq
l_int|0
)paren
(brace
id|sbus-&gt;num_sbus_ranges
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sbus-&gt;num_sbus_ranges
op_assign
id|len
op_div
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
suffix:semicolon
)brace
DECL|function|__apply_ranges_to_regs
r_static
r_void
id|__init
id|__apply_ranges_to_regs
c_func
(paren
r_struct
id|linux_prom_ranges
op_star
id|ranges
comma
r_int
id|num_ranges
comma
r_struct
id|linux_prom_registers
op_star
id|regs
comma
r_int
id|num_regs
)paren
(brace
r_if
c_cond
(paren
id|num_ranges
)paren
(brace
r_int
id|regnum
suffix:semicolon
r_for
c_loop
(paren
id|regnum
op_assign
l_int|0
suffix:semicolon
id|regnum
OL
id|num_regs
suffix:semicolon
id|regnum
op_increment
)paren
(brace
r_int
id|rngnum
suffix:semicolon
r_for
c_loop
(paren
id|rngnum
op_assign
l_int|0
suffix:semicolon
id|rngnum
OL
id|num_ranges
suffix:semicolon
id|rngnum
op_increment
)paren
(brace
r_if
c_cond
(paren
id|regs
(braket
id|regnum
)braket
dot
id|which_io
op_eq
id|ranges
(braket
id|rngnum
)braket
dot
id|ot_child_space
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rngnum
op_eq
id|num_ranges
)paren
(brace
multiline_comment|/* We used to flag this as an error.  Actually&n;&t;&t;&t;&t; * some devices do not report the regs as we expect.&n;&t;&t;&t;&t; * For example, see SUNW,pln device.  In that case&n;&t;&t;&t;&t; * the reg property is in a format internal to that&n;&t;&t;&t;&t; * node, ie. it is not in the SBUS register space&n;&t;&t;&t;&t; * per se. -DaveM&n;&t;&t;&t;&t; */
r_return
suffix:semicolon
)brace
id|regs
(braket
id|regnum
)braket
dot
id|which_io
op_assign
id|ranges
(braket
id|rngnum
)braket
dot
id|ot_parent_space
suffix:semicolon
id|regs
(braket
id|regnum
)braket
dot
id|phys_addr
op_sub_assign
id|ranges
(braket
id|rngnum
)braket
dot
id|ot_child_base
suffix:semicolon
id|regs
(braket
id|regnum
)braket
dot
id|phys_addr
op_add_assign
id|ranges
(braket
id|rngnum
)braket
dot
id|ot_parent_base
suffix:semicolon
)brace
)brace
)brace
DECL|function|__fixup_regs_sdev
r_static
r_void
id|__init
id|__fixup_regs_sdev
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;num_registers
op_ne
l_int|0
)paren
(brace
r_struct
id|sbus_dev
op_star
id|parent
op_assign
id|sdev-&gt;parent
suffix:semicolon
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
id|parent
op_ne
l_int|NULL
)paren
(brace
id|__apply_ranges_to_regs
c_func
(paren
id|parent-&gt;device_ranges
comma
id|parent-&gt;num_device_ranges
comma
id|sdev-&gt;reg_addrs
comma
id|sdev-&gt;num_registers
)paren
suffix:semicolon
id|parent
op_assign
id|parent-&gt;parent
suffix:semicolon
)brace
id|__apply_ranges_to_regs
c_func
(paren
id|sdev-&gt;bus-&gt;sbus_ranges
comma
id|sdev-&gt;bus-&gt;num_sbus_ranges
comma
id|sdev-&gt;reg_addrs
comma
id|sdev-&gt;num_registers
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
id|sdev-&gt;num_registers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|sdev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
id|res-&gt;start
op_assign
id|sdev-&gt;reg_addrs
(braket
id|i
)braket
dot
id|phys_addr
suffix:semicolon
id|res-&gt;end
op_assign
(paren
id|res-&gt;start
op_plus
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
id|i
)braket
dot
id|reg_size
op_minus
l_int|1UL
)paren
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_IO
op_or
(paren
id|sdev-&gt;reg_addrs
(braket
id|i
)braket
dot
id|which_io
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|sbus_fixup_all_regs
r_static
r_void
id|__init
id|sbus_fixup_all_regs
c_func
(paren
r_struct
id|sbus_dev
op_star
id|first_sdev
)paren
(brace
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
r_for
c_loop
(paren
id|sdev
op_assign
id|first_sdev
suffix:semicolon
id|sdev
suffix:semicolon
id|sdev
op_assign
id|sdev-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;child
)paren
id|sbus_fixup_all_regs
c_func
(paren
id|sdev-&gt;child
)paren
suffix:semicolon
id|__fixup_regs_sdev
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
)brace
r_extern
r_void
id|register_proc_sparc_ioport
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|firetruck_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rs_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|sbus_init
r_static
r_int
id|__init
id|sbus_init
c_func
(paren
r_void
)paren
(brace
r_int
id|nd
comma
id|this_sbus
comma
id|sbus_devs
comma
id|topnd
comma
id|iommund
suffix:semicolon
r_int
r_int
id|sbus_clock
suffix:semicolon
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|this_dev
suffix:semicolon
r_int
id|num_sbus
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* How many did we find? */
macro_line|#ifndef __sparc_v9__
id|register_proc_sparc_ioport
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN4
id|sun4_dvma_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#endif
id|topnd
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
multiline_comment|/* Finding the first sbus is a special case... */
id|iommund
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4u
)paren
(brace
id|nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|topnd
comma
l_string|&quot;sbus&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nd
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
op_logical_neg
id|pcibios_present
c_func
(paren
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Neither SBUS nor PCI found.&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef __sparc_v9__
id|firetruck_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#else
id|prom_printf
c_func
(paren
l_string|&quot;YEEE, UltraSparc sbus not found&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_else
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
r_if
c_cond
(paren
(paren
id|iommund
op_assign
id|prom_searchsiblings
c_func
(paren
id|topnd
comma
l_string|&quot;io-unit&quot;
)paren
)paren
op_eq
l_int|0
op_logical_or
(paren
id|nd
op_assign
id|prom_getchild
c_func
(paren
id|iommund
)paren
)paren
op_eq
l_int|0
op_logical_or
(paren
id|nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|nd
comma
l_string|&quot;sbi&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;sbi not found&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|topnd
comma
l_string|&quot;sbus&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|iommund
op_assign
id|prom_searchsiblings
c_func
(paren
id|topnd
comma
l_string|&quot;iommu&quot;
)paren
)paren
op_eq
l_int|0
op_logical_or
(paren
id|nd
op_assign
id|prom_getchild
c_func
(paren
id|iommund
)paren
)paren
op_eq
l_int|0
op_logical_or
(paren
id|nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|nd
comma
l_string|&quot;sbus&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
op_logical_neg
id|pcic_present
c_func
(paren
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Neither SBUS nor PCI found.&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#else
multiline_comment|/* No reason to run further - the data access trap will occur. */
id|panic
c_func
(paren
l_string|&quot;sbus not found&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/* Ok, we&squot;ve found the first one, allocate first SBus struct&n;&t; * and place in chain.&n;&t; */
id|sbus
op_assign
id|sbus_root
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_bus
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|sbus-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|sbus-&gt;prom_node
op_assign
id|nd
suffix:semicolon
id|this_sbus
op_assign
id|nd
suffix:semicolon
r_if
c_cond
(paren
id|iommund
op_logical_and
id|sparc_cpu_model
op_ne
id|sun4u
op_logical_and
id|sparc_cpu_model
op_ne
id|sun4d
)paren
(brace
id|iommu_init
c_func
(paren
id|iommund
comma
id|sbus
)paren
suffix:semicolon
)brace
multiline_comment|/* Loop until we find no more SBUS&squot;s */
r_while
c_loop
(paren
id|this_sbus
)paren
(brace
macro_line|#ifdef __sparc_v9__&t;&t;&t;&t;&t;&t;  
multiline_comment|/* IOMMU hides inside SBUS/SYSIO prom node on Ultra. */
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4u
)paren
(brace
r_extern
r_void
id|sbus_iommu_init
c_func
(paren
r_int
id|prom_node
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
suffix:semicolon
id|sbus_iommu_init
c_func
(paren
id|this_sbus
comma
id|sbus
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __sparc_v9__&t;&t;&t;&t;&t;&t;  
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
id|iounit_init
c_func
(paren
id|this_sbus
comma
id|iommund
comma
id|sbus
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;&t;&t;   
id|printk
c_func
(paren
l_string|&quot;sbus%d: &quot;
comma
id|num_sbus
)paren
suffix:semicolon
id|sbus_clock
op_assign
id|prom_getint
c_func
(paren
id|this_sbus
comma
l_string|&quot;clock-frequency&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbus_clock
op_eq
op_minus
l_int|1
)paren
(brace
id|sbus_clock
op_assign
(paren
l_int|25
op_star
l_int|1000
op_star
l_int|1000
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Clock %d.%d MHz&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
(paren
id|sbus_clock
op_div
l_int|1000
)paren
op_div
l_int|1000
)paren
comma
(paren
r_int
)paren
(paren
(paren
(paren
id|sbus_clock
op_div
l_int|1000
)paren
op_mod
l_int|1000
op_ne
l_int|0
)paren
ques
c_cond
(paren
(paren
(paren
id|sbus_clock
op_div
l_int|1000
)paren
op_mod
l_int|1000
)paren
op_plus
l_int|1000
)paren
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|prom_getstring
c_func
(paren
id|this_sbus
comma
l_string|&quot;name&quot;
comma
id|sbus-&gt;prom_name
comma
r_sizeof
(paren
id|sbus-&gt;prom_name
)paren
)paren
suffix:semicolon
id|sbus-&gt;clock_freq
op_assign
id|sbus_clock
suffix:semicolon
macro_line|#ifndef __sparc_v9__&t;&t;
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
id|sbus-&gt;devid
op_assign
id|prom_getint
c_func
(paren
id|iommund
comma
l_string|&quot;device-id&quot;
)paren
suffix:semicolon
id|sbus-&gt;board
op_assign
id|prom_getint
c_func
(paren
id|iommund
comma
l_string|&quot;board#&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|sbus_bus_ranges_init
c_func
(paren
id|iommund
comma
id|sbus
)paren
suffix:semicolon
id|sbus_devs
op_assign
id|prom_getchild
c_func
(paren
id|this_sbus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbus_devs
)paren
(brace
id|sbus-&gt;devices
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|next_bus
suffix:semicolon
)brace
id|sbus-&gt;devices
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dev
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|this_dev
op_assign
id|sbus-&gt;devices
suffix:semicolon
id|this_dev-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|this_dev-&gt;bus
op_assign
id|sbus
suffix:semicolon
id|this_dev-&gt;parent
op_assign
l_int|NULL
suffix:semicolon
id|fill_sbus_device
c_func
(paren
id|sbus_devs
comma
id|this_dev
)paren
suffix:semicolon
multiline_comment|/* Should we traverse for children? */
r_if
c_cond
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
)paren
(brace
multiline_comment|/* Allocate device node */
id|this_dev-&gt;child
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dev
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* Fill it */
id|this_dev-&gt;child-&gt;bus
op_assign
id|sbus
suffix:semicolon
id|this_dev-&gt;child-&gt;next
op_assign
l_int|0
suffix:semicolon
id|fill_sbus_device
c_func
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
comma
id|this_dev-&gt;child
)paren
suffix:semicolon
id|sbus_do_child_siblings
c_func
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
comma
id|this_dev-&gt;child
comma
id|this_dev
comma
id|sbus
)paren
suffix:semicolon
)brace
r_else
(brace
id|this_dev-&gt;child
op_assign
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|sbus_devs
op_assign
id|prom_getsibling
c_func
(paren
id|sbus_devs
)paren
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Allocate device node */
id|this_dev-&gt;next
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dev
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|this_dev
op_assign
id|this_dev-&gt;next
suffix:semicolon
id|this_dev-&gt;next
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Fill it */
id|this_dev-&gt;bus
op_assign
id|sbus
suffix:semicolon
id|this_dev-&gt;parent
op_assign
l_int|NULL
suffix:semicolon
id|fill_sbus_device
c_func
(paren
id|sbus_devs
comma
id|this_dev
)paren
suffix:semicolon
multiline_comment|/* Is there a child node hanging off of us? */
r_if
c_cond
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
)paren
(brace
multiline_comment|/* Get new device struct */
id|this_dev-&gt;child
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dev
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* Fill it */
id|this_dev-&gt;child-&gt;bus
op_assign
id|sbus
suffix:semicolon
id|this_dev-&gt;child-&gt;next
op_assign
l_int|0
suffix:semicolon
id|fill_sbus_device
c_func
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
comma
id|this_dev-&gt;child
)paren
suffix:semicolon
id|sbus_do_child_siblings
c_func
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
comma
id|this_dev-&gt;child
comma
id|this_dev
comma
id|sbus
)paren
suffix:semicolon
)brace
r_else
(brace
id|this_dev-&gt;child
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* Walk all devices and apply parent ranges. */
id|sbus_fixup_all_regs
c_func
(paren
id|sbus-&gt;devices
)paren
suffix:semicolon
id|dvma_init
c_func
(paren
id|sbus
)paren
suffix:semicolon
id|next_bus
suffix:colon
id|num_sbus
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4u
)paren
(brace
id|this_sbus
op_assign
id|prom_getsibling
c_func
(paren
id|this_sbus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this_sbus
)paren
(brace
r_break
suffix:semicolon
)brace
id|this_sbus
op_assign
id|prom_searchsiblings
c_func
(paren
id|this_sbus
comma
l_string|&quot;sbus&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
id|iommund
op_assign
id|prom_getsibling
c_func
(paren
id|iommund
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iommund
)paren
(brace
r_break
suffix:semicolon
)brace
id|iommund
op_assign
id|prom_searchsiblings
c_func
(paren
id|iommund
comma
l_string|&quot;io-unit&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iommund
)paren
(brace
r_break
suffix:semicolon
)brace
id|this_sbus
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getchild
c_func
(paren
id|iommund
)paren
comma
l_string|&quot;sbi&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|this_sbus
op_assign
id|prom_getsibling
c_func
(paren
id|this_sbus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this_sbus
)paren
(brace
r_break
suffix:semicolon
)brace
id|this_sbus
op_assign
id|prom_searchsiblings
c_func
(paren
id|this_sbus
comma
l_string|&quot;sbus&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_sbus
)paren
(brace
id|sbus-&gt;next
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_bus
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|sbus
op_assign
id|sbus-&gt;next
suffix:semicolon
id|sbus-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|sbus-&gt;prom_node
op_assign
id|this_sbus
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* while(this_sbus) */
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
r_extern
r_void
id|sun4d_init_sbi_irq
c_func
(paren
r_void
)paren
suffix:semicolon
id|sun4d_init_sbi_irq
c_func
(paren
)paren
suffix:semicolon
)brace
id|rs_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef __sparc_v9__
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4u
)paren
(brace
id|firetruck_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SUN_AUXIO
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4u
)paren
id|auxio_probe
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __sparc_v9__
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4u
)paren
(brace
r_extern
r_void
id|clock_probe
c_func
(paren
r_void
)paren
suffix:semicolon
id|clock_probe
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sbus_init
id|subsys_initcall
c_func
(paren
id|sbus_init
)paren
suffix:semicolon
eof
