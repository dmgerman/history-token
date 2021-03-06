multiline_comment|/*&n; *  linux/zorro.h -- Amiga AutoConfig (Zorro) Bus Definitions&n; *&n; *  Copyright (C) 1995--2003 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _LINUX_ZORRO_H
DECL|macro|_LINUX_ZORRO_H
mdefine_line|#define _LINUX_ZORRO_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/device.h&gt;
multiline_comment|/*&n;     *  Each Zorro board has a 32-bit ID of the form&n;     *&n;     *      mmmmmmmmmmmmmmmmppppppppeeeeeeee&n;     *&n;     *  with&n;     *&n;     *      mmmmmmmmmmmmmmmm&t;16-bit Manufacturer ID (assigned by CBM (sigh))&n;     *      pppppppp&t;&t;8-bit Product ID (assigned by manufacturer)&n;     *      eeeeeeee&t;&t;8-bit Extended Product ID (currently only used&n;     *&t;&t;&t;&t;for some GVP boards)&n;     */
DECL|macro|ZORRO_MANUF
mdefine_line|#define ZORRO_MANUF(id)&t;&t;((id) &gt;&gt; 16)
DECL|macro|ZORRO_PROD
mdefine_line|#define ZORRO_PROD(id)&t;&t;(((id) &gt;&gt; 8) &amp; 0xff)
DECL|macro|ZORRO_EPC
mdefine_line|#define ZORRO_EPC(id)&t;&t;((id) &amp; 0xff)
DECL|macro|ZORRO_ID
mdefine_line|#define ZORRO_ID(manuf, prod, epc) &bslash;&n;    ((ZORRO_MANUF_##manuf &lt;&lt; 16) | ((prod) &lt;&lt; 8) | (epc))
DECL|typedef|zorro_id
r_typedef
id|__u32
id|zorro_id
suffix:semicolon
DECL|macro|ZORRO_WILDCARD
mdefine_line|#define ZORRO_WILDCARD&t;&t;(0xffffffff)&t;/* not official */
multiline_comment|/* Include the ID list */
macro_line|#include &lt;linux/zorro_ids.h&gt;
multiline_comment|/*&n;     *  GVP identifies most of its products through the &squot;extended product code&squot;&n;     *  (epc). The epc has to be ANDed with the GVP_PRODMASK before the&n;     *  identification.&n;     */
DECL|macro|GVP_PRODMASK
mdefine_line|#define GVP_PRODMASK&t;&t;&t;(0xf8)
DECL|macro|GVP_SCSICLKMASK
mdefine_line|#define GVP_SCSICLKMASK&t;&t;&t;(0x01)
DECL|enum|GVP_flags
r_enum
id|GVP_flags
(brace
DECL|enumerator|GVP_IO
id|GVP_IO
op_assign
l_int|0x01
comma
DECL|enumerator|GVP_ACCEL
id|GVP_ACCEL
op_assign
l_int|0x02
comma
DECL|enumerator|GVP_SCSI
id|GVP_SCSI
op_assign
l_int|0x04
comma
DECL|enumerator|GVP_24BITDMA
id|GVP_24BITDMA
op_assign
l_int|0x08
comma
DECL|enumerator|GVP_25BITDMA
id|GVP_25BITDMA
op_assign
l_int|0x10
comma
DECL|enumerator|GVP_NOBANK
id|GVP_NOBANK
op_assign
l_int|0x20
comma
DECL|enumerator|GVP_14MHZ
id|GVP_14MHZ
op_assign
l_int|0x40
comma
)brace
suffix:semicolon
DECL|struct|Node
r_struct
id|Node
(brace
DECL|member|ln_Succ
r_struct
id|Node
op_star
id|ln_Succ
suffix:semicolon
multiline_comment|/* Pointer to next (successor) */
DECL|member|ln_Pred
r_struct
id|Node
op_star
id|ln_Pred
suffix:semicolon
multiline_comment|/* Pointer to previous (predecessor) */
DECL|member|ln_Type
id|__u8
id|ln_Type
suffix:semicolon
DECL|member|ln_Pri
id|__s8
id|ln_Pri
suffix:semicolon
multiline_comment|/* Priority, for sorting */
DECL|member|ln_Name
id|__s8
op_star
id|ln_Name
suffix:semicolon
multiline_comment|/* ID string, null terminated */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ExpansionRom
r_struct
id|ExpansionRom
(brace
multiline_comment|/* -First 16 bytes of the expansion ROM */
DECL|member|er_Type
id|__u8
id|er_Type
suffix:semicolon
multiline_comment|/* Board type, size and flags */
DECL|member|er_Product
id|__u8
id|er_Product
suffix:semicolon
multiline_comment|/* Product number, assigned by manufacturer */
DECL|member|er_Flags
id|__u8
id|er_Flags
suffix:semicolon
multiline_comment|/* Flags */
DECL|member|er_Reserved03
id|__u8
id|er_Reserved03
suffix:semicolon
multiline_comment|/* Must be zero ($ff inverted) */
DECL|member|er_Manufacturer
id|__u16
id|er_Manufacturer
suffix:semicolon
multiline_comment|/* Unique ID, ASSIGNED BY COMMODORE-AMIGA! */
DECL|member|er_SerialNumber
id|__u32
id|er_SerialNumber
suffix:semicolon
multiline_comment|/* Available for use by manufacturer */
DECL|member|er_InitDiagVec
id|__u16
id|er_InitDiagVec
suffix:semicolon
multiline_comment|/* Offset to optional &quot;DiagArea&quot; structure */
DECL|member|er_Reserved0c
id|__u8
id|er_Reserved0c
suffix:semicolon
DECL|member|er_Reserved0d
id|__u8
id|er_Reserved0d
suffix:semicolon
DECL|member|er_Reserved0e
id|__u8
id|er_Reserved0e
suffix:semicolon
DECL|member|er_Reserved0f
id|__u8
id|er_Reserved0f
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* er_Type board type bits */
DECL|macro|ERT_TYPEMASK
mdefine_line|#define ERT_TYPEMASK&t;0xc0
DECL|macro|ERT_ZORROII
mdefine_line|#define ERT_ZORROII&t;0xc0
DECL|macro|ERT_ZORROIII
mdefine_line|#define ERT_ZORROIII&t;0x80
multiline_comment|/* other bits defined in er_Type */
DECL|macro|ERTB_MEMLIST
mdefine_line|#define ERTB_MEMLIST&t;5&t;&t;/* Link RAM into free memory list */
DECL|macro|ERTF_MEMLIST
mdefine_line|#define ERTF_MEMLIST&t;(1&lt;&lt;5)
DECL|struct|ConfigDev
r_struct
id|ConfigDev
(brace
DECL|member|cd_Node
r_struct
id|Node
id|cd_Node
suffix:semicolon
DECL|member|cd_Flags
id|__u8
id|cd_Flags
suffix:semicolon
multiline_comment|/* (read/write) */
DECL|member|cd_Pad
id|__u8
id|cd_Pad
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|cd_Rom
r_struct
id|ExpansionRom
id|cd_Rom
suffix:semicolon
multiline_comment|/* copy of board&squot;s expansion ROM */
DECL|member|cd_BoardAddr
r_void
op_star
id|cd_BoardAddr
suffix:semicolon
multiline_comment|/* where in memory the board was placed */
DECL|member|cd_BoardSize
id|__u32
id|cd_BoardSize
suffix:semicolon
multiline_comment|/* size of board in bytes */
DECL|member|cd_SlotAddr
id|__u16
id|cd_SlotAddr
suffix:semicolon
multiline_comment|/* which slot number (PRIVATE) */
DECL|member|cd_SlotSize
id|__u16
id|cd_SlotSize
suffix:semicolon
multiline_comment|/* number of slots (PRIVATE) */
DECL|member|cd_Driver
r_void
op_star
id|cd_Driver
suffix:semicolon
multiline_comment|/* pointer to node of driver */
DECL|member|cd_NextCD
r_struct
id|ConfigDev
op_star
id|cd_NextCD
suffix:semicolon
multiline_comment|/* linked list of drivers to config */
DECL|member|cd_Unused
id|__u32
id|cd_Unused
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* for whatever the driver wants */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#else /* __ASSEMBLY__ */
id|LN_Succ
op_assign
l_int|0
id|LN_Pred
op_assign
id|LN_Succ
op_plus
l_int|4
id|LN_Type
op_assign
id|LN_Pred
op_plus
l_int|4
id|LN_Pri
op_assign
id|LN_Type
op_plus
l_int|1
id|LN_Name
op_assign
id|LN_Pri
op_plus
l_int|1
id|LN_sizeof
op_assign
id|LN_Name
op_plus
l_int|4
id|ER_Type
op_assign
l_int|0
id|ER_Product
op_assign
id|ER_Type
op_plus
l_int|1
id|ER_Flags
op_assign
id|ER_Product
op_plus
l_int|1
id|ER_Reserved03
op_assign
id|ER_Flags
op_plus
l_int|1
id|ER_Manufacturer
op_assign
id|ER_Reserved03
op_plus
l_int|1
id|ER_SerialNumber
op_assign
id|ER_Manufacturer
op_plus
l_int|2
id|ER_InitDiagVec
op_assign
id|ER_SerialNumber
op_plus
l_int|4
id|ER_Reserved0c
op_assign
id|ER_InitDiagVec
op_plus
l_int|2
id|ER_Reserved0d
op_assign
id|ER_Reserved0c
op_plus
l_int|1
id|ER_Reserved0e
op_assign
id|ER_Reserved0d
op_plus
l_int|1
id|ER_Reserved0f
op_assign
id|ER_Reserved0e
op_plus
l_int|1
id|ER_sizeof
op_assign
id|ER_Reserved0f
op_plus
l_int|1
id|CD_Node
op_assign
l_int|0
id|CD_Flags
op_assign
id|CD_Node
op_plus
id|LN_sizeof
id|CD_Pad
op_assign
id|CD_Flags
op_plus
l_int|1
id|CD_Rom
op_assign
id|CD_Pad
op_plus
l_int|1
id|CD_BoardAddr
op_assign
id|CD_Rom
op_plus
id|ER_sizeof
id|CD_BoardSize
op_assign
id|CD_BoardAddr
op_plus
l_int|4
id|CD_SlotAddr
op_assign
id|CD_BoardSize
op_plus
l_int|4
id|CD_SlotSize
op_assign
id|CD_SlotAddr
op_plus
l_int|2
id|CD_Driver
op_assign
id|CD_SlotSize
op_plus
l_int|2
id|CD_NextCD
op_assign
id|CD_Driver
op_plus
l_int|4
id|CD_Unused
op_assign
id|CD_NextCD
op_plus
l_int|4
id|CD_sizeof
op_assign
id|CD_Unused
op_plus
(paren
l_int|4
op_star
l_int|4
)paren
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|ZORRO_NUM_AUTO
mdefine_line|#define ZORRO_NUM_AUTO&t;&t;16
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/zorro.h&gt;
multiline_comment|/*&n;     *  Zorro devices&n;     */
r_struct
id|zorro_dev
(brace
r_struct
id|ExpansionRom
id|rom
suffix:semicolon
id|zorro_id
id|id
suffix:semicolon
r_struct
id|zorro_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* which driver has allocated this device */
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Generic device interface */
id|u16
id|slotaddr
suffix:semicolon
id|u16
id|slotsize
suffix:semicolon
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
r_struct
id|resource
id|resource
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_zorro_dev
mdefine_line|#define&t;to_zorro_dev(n)&t;container_of(n, struct zorro_dev, dev)
multiline_comment|/*&n;     *  Zorro bus&n;     */
DECL|struct|zorro_bus
r_struct
id|zorro_bus
(brace
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* list of devices on this bus */
DECL|member|num_resources
r_int
r_int
id|num_resources
suffix:semicolon
multiline_comment|/* number of resources */
DECL|member|resources
r_struct
id|resource
id|resources
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* address space routed to this bus */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|zorro_bus
id|zorro_bus
suffix:semicolon
multiline_comment|/* single Zorro bus */
r_extern
r_struct
id|bus_type
id|zorro_bus_type
suffix:semicolon
multiline_comment|/*&n;     *  Zorro device IDs&n;     */
DECL|struct|zorro_device_id
r_struct
id|zorro_device_id
(brace
DECL|member|id
id|zorro_id
id|id
suffix:semicolon
multiline_comment|/* Device ID or ZORRO_WILDCARD */
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* Data private to the driver */
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Zorro device drivers&n;     */
DECL|struct|zorro_driver
r_struct
id|zorro_driver
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
id|zorro_device_id
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
id|zorro_dev
op_star
id|z
comma
r_const
r_struct
id|zorro_device_id
op_star
id|id
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
id|zorro_dev
op_star
id|z
)paren
suffix:semicolon
multiline_comment|/* Device removed (NULL if not a hot-plug capable driver) */
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_zorro_driver
mdefine_line|#define&t;to_zorro_driver(drv)&t;container_of(drv, struct zorro_driver, driver)
DECL|macro|zorro_for_each_dev
mdefine_line|#define zorro_for_each_dev(dev)&t;&bslash;&n;&t;for (dev = &amp;zorro_autocon[0]; dev &lt; zorro_autocon+zorro_num_autocon; dev++)
multiline_comment|/* New-style probing */
r_extern
r_int
id|zorro_register_driver
c_func
(paren
r_struct
id|zorro_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zorro_unregister_driver
c_func
(paren
r_struct
id|zorro_driver
op_star
)paren
suffix:semicolon
r_extern
r_const
r_struct
id|zorro_device_id
op_star
id|zorro_match_device
c_func
(paren
r_const
r_struct
id|zorro_device_id
op_star
id|ids
comma
r_const
r_struct
id|zorro_dev
op_star
id|z
)paren
suffix:semicolon
DECL|function|zorro_dev_driver
r_static
r_inline
r_struct
id|zorro_driver
op_star
id|zorro_dev_driver
c_func
(paren
r_const
r_struct
id|zorro_dev
op_star
id|z
)paren
(brace
r_return
id|z-&gt;driver
suffix:semicolon
)brace
r_extern
r_int
r_int
id|zorro_num_autocon
suffix:semicolon
multiline_comment|/* # of autoconfig devices found */
r_extern
r_struct
id|zorro_dev
id|zorro_autocon
(braket
id|ZORRO_NUM_AUTO
)braket
suffix:semicolon
multiline_comment|/*&n;     *  Zorro Functions&n;     */
r_extern
r_struct
id|zorro_dev
op_star
id|zorro_find_device
c_func
(paren
id|zorro_id
id|id
comma
r_struct
id|zorro_dev
op_star
id|from
)paren
suffix:semicolon
DECL|macro|zorro_resource_start
mdefine_line|#define zorro_resource_start(z)&t;((z)-&gt;resource.start)
DECL|macro|zorro_resource_end
mdefine_line|#define zorro_resource_end(z)&t;((z)-&gt;resource.end)
DECL|macro|zorro_resource_len
mdefine_line|#define zorro_resource_len(z)&t;((z)-&gt;resource.end-(z)-&gt;resource.start+1)
DECL|macro|zorro_resource_flags
mdefine_line|#define zorro_resource_flags(z)&t;((z)-&gt;resource.flags)
DECL|macro|zorro_request_device
mdefine_line|#define zorro_request_device(z, name) &bslash;&n;    request_mem_region(zorro_resource_start(z), zorro_resource_len(z), name)
DECL|macro|zorro_release_device
mdefine_line|#define zorro_release_device(z) &bslash;&n;    release_mem_region(zorro_resource_start(z), zorro_resource_len(z))
multiline_comment|/* Similar to the helpers above, these manipulate per-zorro_dev&n; * driver-specific data.  They are really just a wrapper around&n; * the generic device structure functions of these calls.&n; */
DECL|function|zorro_get_drvdata
r_static
r_inline
r_void
op_star
id|zorro_get_drvdata
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
(brace
r_return
id|dev_get_drvdata
c_func
(paren
op_amp
id|z-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|zorro_set_drvdata
r_static
r_inline
r_void
id|zorro_set_drvdata
(paren
r_struct
id|zorro_dev
op_star
id|z
comma
r_void
op_star
id|data
)paren
(brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|z-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A helper function which helps ensure correct zorro_driver&n; * setup and cleanup for commonly-encountered hotplug/modular cases&n; *&n; * This MUST stay in a header, as it checks for -DMODULE&n; */
DECL|function|zorro_module_init
r_static
r_inline
r_int
id|zorro_module_init
c_func
(paren
r_struct
id|zorro_driver
op_star
id|drv
)paren
(brace
r_int
id|rc
op_assign
id|zorro_register_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* iff CONFIG_HOTPLUG and built into kernel, we should&n;&t; * leave the driver around for future hotplug events.&n;&t; * For the module case, a hotplug daemon of some sort&n;&t; * should load a module in response to an insert event. */
macro_line|#if defined(CONFIG_HOTPLUG) &amp;&amp; !defined(MODULE)
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
multiline_comment|/* if we get here, we need to clean up Zorro driver instance&n;&t; * and return some sort of error */
id|zorro_unregister_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Bitmask indicating portions of available Zorro II RAM that are unused&n;     *  by the system. Every bit represents a 64K chunk, for a maximum of 8MB&n;     *  (128 chunks, physical 0x00200000-0x009fffff).&n;     *&n;     *  If you want to use (= allocate) portions of this RAM, you should clear&n;     *  the corresponding bits.&n;     */
r_extern
id|DECLARE_BITMAP
c_func
(paren
id|zorro_unused_z2ram
comma
l_int|128
)paren
suffix:semicolon
DECL|macro|Z2RAM_START
mdefine_line|#define Z2RAM_START&t;&t;(0x00200000)
DECL|macro|Z2RAM_END
mdefine_line|#define Z2RAM_END&t;&t;(0x00a00000)
DECL|macro|Z2RAM_SIZE
mdefine_line|#define Z2RAM_SIZE&t;&t;(0x00800000)
DECL|macro|Z2RAM_CHUNKSIZE
mdefine_line|#define Z2RAM_CHUNKSIZE&t;&t;(0x00010000)
DECL|macro|Z2RAM_CHUNKMASK
mdefine_line|#define Z2RAM_CHUNKMASK&t;&t;(0x0000ffff)
DECL|macro|Z2RAM_CHUNKSHIFT
mdefine_line|#define Z2RAM_CHUNKSHIFT&t;(16)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_ZORRO_H */
eof
