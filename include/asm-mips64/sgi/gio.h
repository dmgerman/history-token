multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * gio.h: Definitions for SGI GIO bus&n; *&n; * Copyright (C) 2002 Ladislav Michl&n; */
macro_line|#ifndef _SGI_GIO_H
DECL|macro|_SGI_GIO_H
mdefine_line|#define _SGI_GIO_H
multiline_comment|/*&n; * GIO bus addresses&n; *&n; * The Indigo and Indy have two GIO bus connectors. Indigo2 (all models) have&n; * three physical connectors, but only two slots, GFX and EXP0.&n; * &n; * There is 10MB of GIO address space for GIO64 slot devices&n; * slot#   slot type address range            size&n; * -----   --------- ----------------------- -----&n; *   0     GFX       0x1f000000 - 0x1f3fffff   4MB&n; *   1     EXP0      0x1f400000 - 0x1f5fffff   2MB&n; *   2     EXP1      0x1f600000 - 0x1f9fffff   4MB&n; *&n; * There are un-slotted devices, HPC, I/O and misc devices, which are grouped&n; * into the HPC address space.&n; *   -     MISC      0x1fb00000 - 0x1fbfffff   1MB&n; *&n; * Following space is reserved and unused&n; *   -     RESERVED  0x18000000 - 0x1effffff 112MB&n; *&n; * GIO bus IDs&n; *&n; * Each GIO bus device identifies itself to the system by answering a&n; * read with an &quot;ID&quot; value. IDs are either 8 or 32 bits long. IDs less&n; * than 128 are 8 bits long, with the most significant 24 bits read from&n; * the slot undefined.&n; *&n; * 32-bit IDs are divided into&n; *&t;bits 0:6        the product ID; ranges from 0x00 to 0x7F.&n; *&t;bit 7&t;&t;0=GIO Product ID is 8 bits wide&n; *&t;&t;&t;1=GIO Product ID is 32 bits wide.&n; *&t;bits 8:15       manufacturer version for the product.&n; *&t;bit 16&t;&t;0=GIO32 and GIO32-bis, 1=GIO64.&n; *&t;bit 17&t;&t;0=no ROM present&n; *&t;&t;&t;1=ROM present on this board AND next three words&n; *&t;&t;&t;space define the ROM.&n; *&t;bits 18:31&t;up to manufacturer.&n; *&n; * IDs above 0x50/0xd0 are of 3rd party boards.&n; *&n; * 8-bit IDs&n; *&t;0x01&t;&t;XPI low cost FDDI&n; *&t;0x02&t;&t;GTR TokenRing&n; *&t;0x04&t;&t;Synchronous ISDN&n; *&t;0x05&t;&t;ATM board [*]&n; *&t;0x06&t;&t;Canon Interface&n; *&t;0x07&t;&t;16 bit SCSI Card [*]&n; *&t;0x08&t;&t;JPEG (Double Wide)&n; *&t;0x09&t;&t;JPEG (Single Wide)&n; *&t;0x0a&t;&t;XPI mez. FDDI device 0&n; *&t;0x0b&t;&t;XPI mez. FDDI device 1&n; *&t;0x0c&t;&t;SMPTE 259M Video [*]&n; *&t;0x0d&t;&t;Babblefish Compression [*]&n; *&t;0x0e&t;&t;E-Plex 8-port Ethernet&n; *&t;0x30&t;&t;Lyon Lamb IVAS&n; *&t;0xb8&t;&t;GIO 100BaseTX Fast Ethernet (gfe)&n; *&n; * [*] Device provide 32-bit ID.&n; *&n; */
DECL|macro|GIO_ID
mdefine_line|#define GIO_ID(x)&t;&t;(x &amp; 0x7f)
DECL|macro|GIO_32BIT_ID
mdefine_line|#define GIO_32BIT_ID&t;&t;0x80
DECL|macro|GIO_REV
mdefine_line|#define GIO_REV(x)&t;&t;((x &gt;&gt; 8) &amp; 0xff)
DECL|macro|GIO_64BIT_IFACE
mdefine_line|#define GIO_64BIT_IFACE&t;&t;0x10000
DECL|macro|GIO_ROM_PRESENT
mdefine_line|#define GIO_ROM_PRESENT&t;&t;0x20000
DECL|macro|GIO_VENDOR_CODE
mdefine_line|#define GIO_VENDOR_CODE(x)&t;((x &gt;&gt; 18) &amp; 0x3fff)
DECL|macro|GIO_SLOT_GFX_BASE
mdefine_line|#define GIO_SLOT_GFX_BASE&t;0x1f000000
DECL|macro|GIO_SLOT_EXP0_BASE
mdefine_line|#define GIO_SLOT_EXP0_BASE&t;0x1f400000
DECL|macro|GIO_SLOT_EXP1_BASE
mdefine_line|#define GIO_SLOT_EXP1_BASE&t;0x1f600000
macro_line|#endif /* _SGI_GIO_H */
eof
