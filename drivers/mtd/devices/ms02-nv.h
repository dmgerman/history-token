multiline_comment|/*&n; *      Copyright (c) 2001 Maciej W. Rozycki&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;$Id: ms02-nv.h,v 1.1 2002/09/13 13:46:55 dwmw2 Exp $&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
multiline_comment|/* MS02-NV iomem register offsets. */
DECL|macro|MS02NV_CSR
mdefine_line|#define MS02NV_CSR&t;&t;0x400000&t;/* control &amp; status register */
multiline_comment|/* MS02-NV memory offsets. */
DECL|macro|MS02NV_DIAG
mdefine_line|#define MS02NV_DIAG&t;&t;0x0003f8&t;/* diagnostic status */
DECL|macro|MS02NV_MAGIC
mdefine_line|#define MS02NV_MAGIC&t;&t;0x0003fc&t;/* MS02-NV magic ID */
DECL|macro|MS02NV_RAM
mdefine_line|#define MS02NV_RAM&t;&t;0x000400&t;/* general-purpose RAM start */
multiline_comment|/* MS02-NV diagnostic status constants. */
DECL|macro|MS02NV_DIAG_SIZE_MASK
mdefine_line|#define MS02NV_DIAG_SIZE_MASK&t;0xf0&t;&t;/* RAM size mask */
DECL|macro|MS02NV_DIAG_SIZE_SHIFT
mdefine_line|#define MS02NV_DIAG_SIZE_SHIFT&t;0x10&t;&t;/* RAM size shift (left) */
multiline_comment|/* MS02-NV general constants. */
DECL|macro|MS02NV_ID
mdefine_line|#define MS02NV_ID&t;&t;0x03021966&t;/* MS02-NV magic ID value */
DECL|macro|MS02NV_SLOT_SIZE
mdefine_line|#define MS02NV_SLOT_SIZE&t;0x800000&t;/* size of the address space&n;&t;&t;&t;&t;&t;&t;   decoded by the module */
DECL|typedef|ms02nv_uint
r_typedef
r_volatile
id|u32
id|ms02nv_uint
suffix:semicolon
DECL|struct|ms02nv_private
r_struct
id|ms02nv_private
(brace
DECL|member|next
r_struct
id|mtd_info
op_star
id|next
suffix:semicolon
r_struct
(brace
DECL|member|module
r_struct
id|resource
op_star
id|module
suffix:semicolon
DECL|member|diag_ram
r_struct
id|resource
op_star
id|diag_ram
suffix:semicolon
DECL|member|user_ram
r_struct
id|resource
op_star
id|user_ram
suffix:semicolon
DECL|member|csr
r_struct
id|resource
op_star
id|csr
suffix:semicolon
DECL|member|resource
)brace
id|resource
suffix:semicolon
DECL|member|addr
id|u_char
op_star
id|addr
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|uaddr
id|u_char
op_star
id|uaddr
suffix:semicolon
)brace
suffix:semicolon
eof
