multiline_comment|/*&n; *  linux/zorro.h -- Amiga AutoConfig (Zorro) Bus Definitions&n; *&n; *  Copyright (C) 1995--2000 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _LINUX_ZORRO_H
DECL|macro|_LINUX_ZORRO_H
mdefine_line|#define _LINUX_ZORRO_H
macro_line|#ifndef __ASSEMBLY__
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
r_void
id|zorro_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zorro_name_device
c_func
(paren
r_struct
id|zorro_dev
op_star
id|dev
)paren
suffix:semicolon
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
DECL|macro|zorro_request_device
mdefine_line|#define zorro_request_device(z, name) &bslash;&n;    request_mem_region((z)-&gt;resource.start, &bslash;&n;&t;&t;       (z)-&gt;resource.end-(z)-&gt;resource.start+1, (name))
DECL|macro|zorro_check_device
mdefine_line|#define zorro_check_device(z) &bslash;&n;    check_mem_region((z)-&gt;resource.start, &bslash;&n;&t;&t;     (z)-&gt;resource.end-(z)-&gt;resource.start+1)
DECL|macro|zorro_release_device
mdefine_line|#define zorro_release_device(z) &bslash;&n;    release_mem_region((z)-&gt;resource.start, &bslash;&n;&t;&t;       (z)-&gt;resource.end-(z)-&gt;resource.start+1)
multiline_comment|/*&n;     *  Bitmask indicating portions of available Zorro II RAM that are unused&n;     *  by the system. Every bit represents a 64K chunk, for a maximum of 8MB&n;     *  (128 chunks, physical 0x00200000-0x009fffff).&n;     *&n;     *  If you want to use (= allocate) portions of this RAM, you should clear&n;     *  the corresponding bits.&n;     */
r_extern
id|__u32
id|zorro_unused_z2ram
(braket
l_int|4
)braket
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
