multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of&n; * this archive for more details.&n; *&n; * Copyright (C) 1997, 2001 Silicon Graphics, Inc. All rights reserved.&n; *&n; */
macro_line|#ifndef _ASM_SN_PCI_PCIBA_H
DECL|macro|_ASM_SN_PCI_PCIBA_H
mdefine_line|#define _ASM_SN_PCI_PCIBA_H
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* for application compatibility with IRIX (why do I bother?) */
macro_line|#ifndef __KERNEL__
DECL|typedef|uint8_t
r_typedef
id|u_int8_t
r_uint8
suffix:semicolon
DECL|typedef|uint16_t
r_typedef
id|u_int16_t
r_uint16
suffix:semicolon
DECL|typedef|uint32_t
r_typedef
id|u_int32_t
r_uint32
suffix:semicolon
macro_line|#endif
DECL|macro|PCI_CFG_VENDOR_ID
mdefine_line|#define PCI_CFG_VENDOR_ID&t;PCI_VENDOR_ID
DECL|macro|PCI_CFG_COMMAND
mdefine_line|#define PCI_CFG_COMMAND&t;&t;PCI_COMMAND
DECL|macro|PCI_CFG_REV_ID
mdefine_line|#define PCI_CFG_REV_ID&t;&t;PCI_REVISION_ID
DECL|macro|PCI_CFG_HEADER_TYPE
mdefine_line|#define PCI_CFG_HEADER_TYPE&t;PCI_HEADER_TYPE
DECL|macro|PCI_CFG_BASE_ADDR
mdefine_line|#define PCI_CFG_BASE_ADDR(n)&t;PCI_BASE_ADDRESS_##n
multiline_comment|/* /hw/.../pci/[slot]/config accepts ioctls to read&n; * and write specific registers as follows:&n; *&n; * &quot;t&quot; is the native type (char, short, uint32, uint64)&n; * to read from CFG space; results will be arranged in&n; * byte significance (ie. first byte from PCI is lowest&n; * or last byte in result).&n; *&n; * &quot;r&quot; is the byte offset in PCI CFG space of the first&n; * byte of the register (it&squot;s least significant byte,&n; * in the little-endian PCI numbering). This can actually&n; * be as much as 16 bits wide, and is intended to match&n; * the layout of a &quot;Type 1 Configuration Space&quot; address:&n; * the register number in the low eight bits, then three&n; * bits for the function number and five bits for the&n; * slot number.&n; */
DECL|macro|PCIIOCCFGRD
mdefine_line|#define&t;PCIIOCCFGRD(t,r)&t;_IOR(0,(r),t)
DECL|macro|PCIIOCCFGWR
mdefine_line|#define&t;PCIIOCCFGWR(t,r)&t;_IOW(0,(r),t)
multiline_comment|/* Some common config register access commands.&n; * Use these as examples of how to construct&n; * values for other registers you want to access.&n; */
multiline_comment|/* PCIIOCGETID: arg is ptr to 32-bit int,&n; * returns the 32-bit ID value with VENDOR&n; * in the bottom 16 bits and DEVICE in the top.&n; */
DECL|macro|PCIIOCGETID
mdefine_line|#define&t;PCIIOCGETID&t;&t;PCIIOCCFGRD(uint32_t,PCI_CFG_VENDOR_ID)
multiline_comment|/* PCIIOCSETCMD: arg is ptr to a 16-bit short,&n; * which will be written to the CMD register.&n; */
DECL|macro|PCIIOCSETCMD
mdefine_line|#define&t;PCIIOCSETCMD&t;&t;PCIIOCCFGWR(uint16_t,PCI_CFG_COMMAND)
multiline_comment|/* PCIIOCGETREV: arg is ptr to an 8-bit char,&n; * which will get the 8-bit revision number.&n; */
DECL|macro|PCIIOCGETREV
mdefine_line|#define&t;PCIIOCGETREV&t;&t;PCIIOCCFGRD(uint8_t,PCI_CFG_REV_ID)
multiline_comment|/* PCIIOCGETHTYPE: arg is ptr to an 8-bit char,&n; * which will get the 8-bit header type.&n; */
DECL|macro|PCIIOCGETHTYPE
mdefine_line|#define&t;PCIIOCGETHTYPE&t;&t;PCIIOCCFGRD(uint8_t,PCI_CFG_HEADER_TYPE)
multiline_comment|/* PCIIOCGETBASE(n): arg is ptr to a 32-bit int,&n; * which will get the value of the BASE&lt;n&gt; register.&n; */
multiline_comment|/* FIXME chadt: this doesn&squot;t tell me whether or not this will work&n;   with non-constant &squot;n.&squot;  */
DECL|macro|PCIIOCGETBASE
mdefine_line|#define&t;PCIIOCGETBASE(n)&t;PCIIOCCFGRD(uint32_t,PCI_CFG_BASE_ADDR(n))
multiline_comment|/* /hw/.../pci/[slot]/dma accepts ioctls to allocate&n; * and free physical memory for use in user-triggered&n; * DMA operations.&n; */
DECL|macro|PCIIOCDMAALLOC
mdefine_line|#define&t;PCIIOCDMAALLOC&t;&t;_IOWR(0,1,uint64_t)
DECL|macro|PCIIOCDMAFREE
mdefine_line|#define&t;PCIIOCDMAFREE&t;&t;_IOW(0,1,uint64_t)
multiline_comment|/* The parameter for PCIIOCDMAALLOC needs to contain&n; * both the size of the request and the flag values&n; * to be used in setting up the DMA.&n; *&n;&n;FIXME chadt: gonna have to revisit this: what flags would an IRIXer like to&n; have available?&n;&n; * Any flags normally useful in pciio_dmamap&n; * or pciio_dmatrans function calls can6 be used here.  */
DECL|macro|PCIIOCDMAALLOC_REQUEST_PACK
mdefine_line|#define&t;PCIIOCDMAALLOC_REQUEST_PACK(flags,size)&t;&t;&bslash;&n;&t;((((uint64_t)(flags))&lt;&lt;32)|&t;&t;&t;&bslash;&n;&t; (((uint64_t)(size))&amp;0xFFFFFFFF))
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|pciba_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _ASM_SN_PCI_PCIBA_H */
eof
