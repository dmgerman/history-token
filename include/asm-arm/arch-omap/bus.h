multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/bus.h&n; *&n; * Virtual bus for OMAP. Allows better power management, such as managing&n; * shared clocks, and mapping of bus addresses to Local Bus addresses.&n; *&n; * See drivers/usb/host/ohci-omap.c or drivers/video/omap/omapfb.c for&n; * examples on how to register drivers to this bus.&n; *&n; * Copyright (C) 2003 - 2004 Nokia Corporation&n; * Written by Tony Lindgren &lt;tony@atomide.com&gt;&n; * Portions of code based on sa1111.c.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef __ASM_ARM_ARCH_OMAP_BUS_H
DECL|macro|__ASM_ARM_ARCH_OMAP_BUS_H
mdefine_line|#define __ASM_ARM_ARCH_OMAP_BUS_H
r_extern
r_struct
id|bus_type
id|omap_bus_types
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Description for physical device&n; */
DECL|struct|omap_dev
r_struct
id|omap_dev
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Standard device description */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|devid
r_int
r_int
id|devid
suffix:semicolon
multiline_comment|/* OMAP device id */
DECL|member|busid
r_int
r_int
id|busid
suffix:semicolon
multiline_comment|/* OMAP virtual busid */
DECL|member|res
r_struct
id|resource
id|res
suffix:semicolon
multiline_comment|/* Standard resource description */
DECL|member|mapbase
r_void
op_star
id|mapbase
suffix:semicolon
multiline_comment|/* OMAP physical address */
DECL|member|irq
r_int
r_int
id|irq
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* OMAP interrupts */
DECL|member|dma_mask
id|u64
op_star
id|dma_mask
suffix:semicolon
multiline_comment|/* Used by USB OHCI only */
DECL|member|coherent_dma_mask
id|u64
id|coherent_dma_mask
suffix:semicolon
multiline_comment|/* Used by USB OHCI only */
)brace
suffix:semicolon
DECL|macro|OMAP_DEV
mdefine_line|#define OMAP_DEV(_d)&t;container_of((_d), struct omap_dev, dev)
DECL|macro|omap_get_drvdata
mdefine_line|#define omap_get_drvdata(d)&t;dev_get_drvdata(&amp;(d)-&gt;dev)
DECL|macro|omap_set_drvdata
mdefine_line|#define omap_set_drvdata(d,p)&t;dev_set_drvdata(&amp;(d)-&gt;dev, p)
multiline_comment|/*&n; * Description for device driver&n; */
DECL|struct|omap_driver
r_struct
id|omap_driver
(brace
DECL|member|drv
r_struct
id|device_driver
id|drv
suffix:semicolon
multiline_comment|/* Standard driver description */
DECL|member|devid
r_int
r_int
id|devid
suffix:semicolon
multiline_comment|/* OMAP device id for bus */
DECL|member|busid
r_int
r_int
id|busid
suffix:semicolon
multiline_comment|/* OMAP virtual busid */
DECL|member|clocks
r_int
r_int
id|clocks
suffix:semicolon
multiline_comment|/* OMAP shared clocks */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|omap_dev
op_star
)paren
suffix:semicolon
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|omap_dev
op_star
)paren
suffix:semicolon
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|omap_dev
op_star
comma
id|u32
)paren
suffix:semicolon
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|omap_dev
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OMAP_DRV
mdefine_line|#define OMAP_DRV(_d)&t;container_of((_d), struct omap_driver, drv)
DECL|macro|OMAP_DRIVER_NAME
mdefine_line|#define OMAP_DRIVER_NAME(_omapdev) ((_omapdev)-&gt;dev.driver-&gt;name)
multiline_comment|/*&n; * Device ID numbers for bus types&n; */
DECL|macro|OMAP_OCP_DEVID_USB
mdefine_line|#define OMAP_OCP_DEVID_USB&t;0
DECL|macro|OMAP_TIPB_DEVID_OHCI
mdefine_line|#define OMAP_TIPB_DEVID_OHCI&t;0
DECL|macro|OMAP_TIPB_DEVID_LCD
mdefine_line|#define OMAP_TIPB_DEVID_LCD&t;1
DECL|macro|OMAP_TIPB_DEVID_MMC
mdefine_line|#define OMAP_TIPB_DEVID_MMC&t;2
DECL|macro|OMAP_TIPB_DEVID_OTG
mdefine_line|#define OMAP_TIPB_DEVID_OTG&t;3
DECL|macro|OMAP_TIPB_DEVID_UDC
mdefine_line|#define OMAP_TIPB_DEVID_UDC&t;4
multiline_comment|/*&n; * Virtual bus definitions for OMAP&n; */
DECL|macro|OMAP_NR_BUSES
mdefine_line|#define OMAP_NR_BUSES&t;2
DECL|macro|OMAP_BUS_NAME_TIPB
mdefine_line|#define OMAP_BUS_NAME_TIPB&t;&quot;tipb&quot;
DECL|macro|OMAP_BUS_NAME_LBUS
mdefine_line|#define OMAP_BUS_NAME_LBUS&t;&quot;lbus&quot;
r_enum
(brace
DECL|enumerator|OMAP_BUS_TIPB
id|OMAP_BUS_TIPB
op_assign
l_int|0
comma
DECL|enumerator|OMAP_BUS_LBUS
id|OMAP_BUS_LBUS
comma
)brace
suffix:semicolon
multiline_comment|/* See arch/arm/mach-omap/bus.c for the rest of the bus definitions. */
r_extern
r_int
id|omap_driver_register
c_func
(paren
r_struct
id|omap_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_void
id|omap_driver_unregister
c_func
(paren
r_struct
id|omap_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_int
id|omap_device_register
c_func
(paren
r_struct
id|omap_dev
op_star
id|odev
)paren
suffix:semicolon
r_extern
r_void
id|omap_device_unregister
c_func
(paren
r_struct
id|omap_dev
op_star
id|odev
)paren
suffix:semicolon
macro_line|#endif
eof
