multiline_comment|/*&n; * ocp.h&n; *&n; *      (c) Benjamin Herrenschmidt (benh@kernel.crashing.org)&n; *          Mipsys - France&n; *&n; *          Derived from work (c) Armin Kuster akuster@pacbell.net&n; *&n; *          Additional support and port to 2.6 LDM/sysfs by&n; *          Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *          Copyright 2003-2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; *  TODO: - Add get/put interface &amp; fixup locking to provide same API for&n; *          2.4 and 2.5&n; *&t;  - Rework PM callbacks&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __OCP_H__
DECL|macro|__OCP_H__
mdefine_line|#define __OCP_H__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/ocp_ids.h&gt;
macro_line|#include &lt;asm/rwsem.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#ifdef CONFIG_PPC_OCP
DECL|macro|OCP_MAX_IRQS
mdefine_line|#define OCP_MAX_IRQS&t;7
DECL|macro|MAX_EMACS
mdefine_line|#define MAX_EMACS&t;4
DECL|macro|OCP_IRQ_NA
mdefine_line|#define OCP_IRQ_NA&t;-1&t;/* used when ocp device does not have an irq */
DECL|macro|OCP_IRQ_MUL
mdefine_line|#define OCP_IRQ_MUL&t;-2&t;/* used for ocp devices with multiply irqs */
DECL|macro|OCP_NULL_TYPE
mdefine_line|#define OCP_NULL_TYPE&t;-1&t;/* used to mark end of list */
DECL|macro|OCP_CPM_NA
mdefine_line|#define OCP_CPM_NA&t;0&t;/* No Clock or Power Management avaliable */
DECL|macro|OCP_PADDR_NA
mdefine_line|#define OCP_PADDR_NA&t;0&t;/* No MMIO registers */
DECL|macro|OCP_ANY_ID
mdefine_line|#define OCP_ANY_ID&t;(~0)
DECL|macro|OCP_ANY_INDEX
mdefine_line|#define OCP_ANY_INDEX&t;-1
r_extern
r_struct
id|list_head
id|ocp_devices
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
id|ocp_devices_sem
suffix:semicolon
DECL|struct|ocp_device_id
r_struct
id|ocp_device_id
(brace
DECL|member|vendor
DECL|member|function
r_int
r_int
id|vendor
comma
id|function
suffix:semicolon
multiline_comment|/* Vendor and function ID or OCP_ANY_ID */
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* Data private to the driver */
)brace
suffix:semicolon
multiline_comment|/*&n; * Static definition of an OCP device.&n; *&n; * @vendor:    Vendor code. It is _STRONGLY_ discouraged to use&n; *             the vendor code as a way to match a unique device,&n; *             though I kept that possibility open, you should&n; *             really define different function codes for different&n; *             device types&n; * @function:  This is the function code for this device.&n; * @index:     This index is used for mapping the Nth function of a&n; *             given core. This is typically used for cross-driver&n; *             matching, like looking for a given MAL or ZMII from&n; *             an EMAC or for getting to the proper set of DCRs.&n; *             Indices are no longer magically calculated based on&n; *             structure ordering, they have to be actually coded&n; *             into the ocp_def to avoid any possible confusion&n; *             I _STRONGLY_ (again ? wow !) encourage anybody relying&n; *             on index mapping to encode the &quot;target&quot; index in an&n; *             associated structure pointed to by &quot;additions&quot;, see&n; *             how it&squot;s done for the EMAC driver.&n; * @paddr:     Device physical address (may not mean anything...)&n; * @irq:       Interrupt line for this device (TODO: think about making&n; *             an array with this)&n; * @pm:        Currently, contains the bitmask in CPMFR DCR for the device&n; * @additions: Optionally points to a function specific structure&n; *             providing additional informations for a given device&n; *             instance. It&squot;s currently used by the EMAC driver for MAL&n; *             channel &amp; ZMII port mapping among others.&n; * @show:      Optionally points to a function specific structure&n; *             providing a sysfs show routine for additions fields.&n; */
DECL|struct|ocp_def
r_struct
id|ocp_def
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|function
r_int
r_int
id|function
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|paddr
id|phys_addr_t
id|paddr
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|pm
r_int
r_int
id|pm
suffix:semicolon
DECL|member|additions
r_void
op_star
id|additions
suffix:semicolon
DECL|member|show
r_void
(paren
op_star
id|show
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Struct for a given device instance */
DECL|struct|ocp_device
r_struct
id|ocp_device
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* device name */
DECL|member|def
r_struct
id|ocp_def
op_star
id|def
suffix:semicolon
multiline_comment|/* device definition */
DECL|member|drvdata
r_void
op_star
id|drvdata
suffix:semicolon
multiline_comment|/* driver data for this device */
DECL|member|driver
r_struct
id|ocp_driver
op_star
id|driver
suffix:semicolon
DECL|member|current_state
id|u32
id|current_state
suffix:semicolon
multiline_comment|/* Current operating state. In ACPI-speak,&n;&t;&t;&t;&t;&t;&t;   this is D0-D3, D0 being fully functional,&n;&t;&t;&t;&t;&t;&t;   and D3 being off. */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ocp_driver
r_struct
id|ocp_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|ocp_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* NULL if wants all devices */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|ocp_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* New device inserted */
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|ocp_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Device removed (NULL if not a hot-plug capable driver) */
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|ocp_device
op_star
id|dev
comma
id|u32
id|state
)paren
suffix:semicolon
multiline_comment|/* Device suspended */
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|ocp_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Device woken up */
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_ocp_dev
mdefine_line|#define to_ocp_dev(n) container_of(n, struct ocp_device, dev)
DECL|macro|to_ocp_drv
mdefine_line|#define to_ocp_drv(n) container_of(n, struct ocp_driver, driver)
multiline_comment|/* Similar to the helpers above, these manipulate per-ocp_dev&n; * driver-specific data.  Currently stored as ocp_dev::ocpdev,&n; * a void pointer, but it is not present on older kernels.&n; */
r_static
r_inline
r_void
op_star
DECL|function|ocp_get_drvdata
id|ocp_get_drvdata
c_func
(paren
r_struct
id|ocp_device
op_star
id|pdev
)paren
(brace
r_return
id|pdev-&gt;drvdata
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ocp_set_drvdata
id|ocp_set_drvdata
c_func
(paren
r_struct
id|ocp_device
op_star
id|pdev
comma
r_void
op_star
id|data
)paren
(brace
id|pdev-&gt;drvdata
op_assign
id|data
suffix:semicolon
)brace
macro_line|#if defined (CONFIG_PM)
multiline_comment|/*&n; * This is right for the IBM 405 and 440 but will need to be&n; * generalized if the OCP stuff gets used on other processors.&n; */
r_static
r_inline
r_void
DECL|function|ocp_force_power_off
id|ocp_force_power_off
c_func
(paren
r_struct
id|ocp_device
op_star
id|odev
)paren
(brace
id|mtdcr
c_func
(paren
id|DCRN_CPMFR
comma
id|mfdcr
c_func
(paren
id|DCRN_CPMFR
)paren
op_or
id|odev-&gt;def-&gt;pm
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ocp_force_power_on
id|ocp_force_power_on
c_func
(paren
r_struct
id|ocp_device
op_star
id|odev
)paren
(brace
id|mtdcr
c_func
(paren
id|DCRN_CPMFR
comma
id|mfdcr
c_func
(paren
id|DCRN_CPMFR
)paren
op_amp
op_complement
id|odev-&gt;def-&gt;pm
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|ocp_force_power_off
mdefine_line|#define ocp_force_power_off(x)&t;(void)(x)
DECL|macro|ocp_force_power_on
mdefine_line|#define ocp_force_power_on(x)&t;(void)(x)
macro_line|#endif
multiline_comment|/* Register/Unregister an OCP driver */
r_extern
r_int
id|ocp_register_driver
c_func
(paren
r_struct
id|ocp_driver
op_star
id|drv
)paren
suffix:semicolon
r_extern
r_void
id|ocp_unregister_driver
c_func
(paren
r_struct
id|ocp_driver
op_star
id|drv
)paren
suffix:semicolon
multiline_comment|/* Build list of devices */
r_extern
r_int
id|ocp_early_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* Find a device by index */
r_extern
r_struct
id|ocp_device
op_star
id|ocp_find_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_int
id|index
)paren
suffix:semicolon
multiline_comment|/* Get a def by index */
r_extern
r_struct
id|ocp_def
op_star
id|ocp_get_one_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_int
id|index
)paren
suffix:semicolon
multiline_comment|/* Add a device by index */
r_extern
r_int
id|ocp_add_one_device
c_func
(paren
r_struct
id|ocp_def
op_star
id|def
)paren
suffix:semicolon
multiline_comment|/* Remove a device by index */
r_extern
r_int
id|ocp_remove_one_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_int
id|index
)paren
suffix:semicolon
multiline_comment|/* Iterate over devices and execute a routine */
r_extern
r_void
id|ocp_for_each_device
c_func
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|ocp_device
op_star
comma
r_void
op_star
id|arg
)paren
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* Sysfs support */
DECL|macro|OCP_SYSFS_ADDTL
mdefine_line|#define OCP_SYSFS_ADDTL(type, format, name, field)&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##name##_##field(struct device *dev, char *buf)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct ocp_device *odev = to_ocp_dev(dev);&t;&t;&t;&bslash;&n;&t;type *add = odev-&gt;def-&gt;additions;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf(buf, format, add-&gt;field);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(name##_##field, S_IRUGO, show_##name##_##field, NULL);
macro_line|#ifdef CONFIG_IBM_OCP
macro_line|#include &lt;asm/ibm_ocp.h&gt;
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* CONFIG_PPC_OCP */
macro_line|#endif&t;&t;&t;&t;/* __OCP_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
