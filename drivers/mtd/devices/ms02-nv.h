multiline_comment|/*&n; *&t;Copyright (c) 2001, 2003  Maciej W. Rozycki&n; *&n; *&t;DEC MS02-NV (54-20948-01) battery backed-up NVRAM module for&n; *&t;DECstation/DECsystem 5000/2x0 and DECsystem 5900 and 5900/260&n; *&t;systems.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;$Id: ms02-nv.h,v 1.3 2003/08/19 09:25:36 dwmw2 Exp $&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
multiline_comment|/*&n; * Addresses are decoded as follows:&n; *&n; * 0x000000 - 0x3fffff&t;SRAM&n; * 0x400000 - 0x7fffff&t;CSR&n; *&n; * Within the SRAM area the following ranges are forced by the system&n; * firmware:&n; *&n; * 0x000000 - 0x0003ff&t;diagnostic area, destroyed upon a reboot&n; * 0x000400 - ENDofRAM&t;storage area, available to operating systems&n; *&n; * but we can&squot;t really use the available area right from 0x000400 as&n; * the first word is used by the firmware as a status flag passed&n; * from an operating system.  If anything but the valid data magic&n; * ID value is found, the firmware considers the SRAM clean, i.e.&n; * containing no valid data, and disables the battery resulting in&n; * data being erased as soon as power is switched off.  So the choice&n; * for the start address of the user-available is 0x001000 which is&n; * nicely page aligned.  The area between 0x000404 and 0x000fff may&n; * be used by the driver for own needs.&n; *&n; * The diagnostic area defines two status words to be read by an&n; * operating system, a magic ID to distinguish a MS02-NV board from&n; * anything else and a status information providing results of tests&n; * as well as the size of SRAM available, which can be 1MiB or 2MiB&n; * (that&squot;s what the firmware handles; no idea if 2MiB modules ever&n; * existed).&n; *&n; * The firmware only handles the MS02-NV board if installed in the&n; * last (15th) slot, so for any other location the status information&n; * stored in the SRAM cannot be relied upon.  But from the hardware&n; * point of view there is no problem using up to 14 such boards in a&n; * system -- only the 1st slot needs to be filled with a DRAM module.&n; * The MS02-NV board is ECC-protected, like other MS02 memory boards.&n; *&n; * The state of the battery as provided by the CSR is reflected on&n; * the two onboard LEDs.  When facing the battery side of the board,&n; * with the LEDs at the top left and the battery at the bottom right&n; * (i.e. looking from the back side of the system box), their meaning&n; * is as follows (the system has to be powered on):&n; *&n; * left LED&t;&t;battery disable status: lit = enabled&n; * right LED&t;&t;battery condition status: lit = OK&n; */
multiline_comment|/* MS02-NV iomem register offsets. */
DECL|macro|MS02NV_CSR
mdefine_line|#define MS02NV_CSR&t;&t;0x400000&t;/* control &amp; status register */
multiline_comment|/* MS02-NV CSR status bits. */
DECL|macro|MS02NV_CSR_BATT_OK
mdefine_line|#define MS02NV_CSR_BATT_OK&t;0x01&t;&t;/* battery OK */
DECL|macro|MS02NV_CSR_BATT_OFF
mdefine_line|#define MS02NV_CSR_BATT_OFF&t;0x02&t;&t;/* battery disabled */
multiline_comment|/* MS02-NV memory offsets. */
DECL|macro|MS02NV_DIAG
mdefine_line|#define MS02NV_DIAG&t;&t;0x0003f8&t;/* diagnostic status */
DECL|macro|MS02NV_MAGIC
mdefine_line|#define MS02NV_MAGIC&t;&t;0x0003fc&t;/* MS02-NV magic ID */
DECL|macro|MS02NV_VALID
mdefine_line|#define MS02NV_VALID&t;&t;0x000400&t;/* valid data magic ID */
DECL|macro|MS02NV_RAM
mdefine_line|#define MS02NV_RAM&t;&t;0x001000&t;/* user-exposed RAM start */
multiline_comment|/* MS02-NV diagnostic status bits. */
DECL|macro|MS02NV_DIAG_TEST
mdefine_line|#define MS02NV_DIAG_TEST&t;0x01&t;&t;/* SRAM test done (?) */
DECL|macro|MS02NV_DIAG_RO
mdefine_line|#define MS02NV_DIAG_RO&t;&t;0x02&t;&t;/* SRAM r/o test done */
DECL|macro|MS02NV_DIAG_RW
mdefine_line|#define MS02NV_DIAG_RW&t;&t;0x04&t;&t;/* SRAM r/w test done */
DECL|macro|MS02NV_DIAG_FAIL
mdefine_line|#define MS02NV_DIAG_FAIL&t;0x08&t;&t;/* SRAM test failed */
DECL|macro|MS02NV_DIAG_SIZE_MASK
mdefine_line|#define MS02NV_DIAG_SIZE_MASK&t;0xf0&t;&t;/* SRAM size mask */
DECL|macro|MS02NV_DIAG_SIZE_SHIFT
mdefine_line|#define MS02NV_DIAG_SIZE_SHIFT&t;0x10&t;&t;/* SRAM size shift (left) */
multiline_comment|/* MS02-NV general constants. */
DECL|macro|MS02NV_ID
mdefine_line|#define MS02NV_ID&t;&t;0x03021966&t;/* MS02-NV magic ID value */
DECL|macro|MS02NV_VALID_ID
mdefine_line|#define MS02NV_VALID_ID&t;&t;0xbd100248&t;/* valid data magic ID value */
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
