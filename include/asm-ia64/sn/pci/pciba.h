multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_PCI_PCIBA_H
DECL|macro|_ASM_SN_PCI_PCIBA_H
mdefine_line|#define _ASM_SN_PCI_PCIBA_H
multiline_comment|/*&n; * These are all the HACKS from ioccom.h ..&n; */
DECL|macro|IOCPARM_MASK
mdefine_line|#define IOCPARM_MASK    0xff            /* parameters must be &lt; 256 bytes */
DECL|macro|IOC_VOID
mdefine_line|#define IOC_VOID        0x20000000      /* no parameters */
multiline_comment|/*&n; * The above needs to be modified and follow LINUX ...&n; */
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
DECL|macro|PCIIOCGETBASE
mdefine_line|#define&t;PCIIOCGETBASE(n)&t;PCIIOCCFGRD(uint32_t,PCI_CFG_BASE_ADDR(n))
multiline_comment|/* /hw/.../pci/[slot]/intr accepts an ioctl to&n; * set up user level interrupt handling as follows:&n; *&n; * &quot;n&quot; is a bitmap of which of the four PCI interrupt&n; * lines are of interest, using PCIIO_INTR_LINE_[ABCD].&n; */
DECL|macro|PCIIOCSETULI
mdefine_line|#define&t;PCIIOCSETULI(n)&t;&t;_IOWR(1,n,struct uliargs)
macro_line|#if _KERNEL
DECL|macro|PCIIOCSETULI32
mdefine_line|#define PCIIOCSETULI32(n)&t;_IOWR(1,n,struct uliargs32)
macro_line|#endif
multiline_comment|/* /hw/.../pci/[slot]/dma accepts ioctls to allocate&n; * and free physical memory for use in user-triggered&n; * DMA operations.&n; */
DECL|macro|PCIIOCDMAALLOC
mdefine_line|#define&t;PCIIOCDMAALLOC&t;&t;_IOWR(0,1,uint64_t)
DECL|macro|PCIIOCDMAFREE
mdefine_line|#define&t;PCIIOCDMAFREE&t;&t;_IOW(0,1,uint64_t)
multiline_comment|/* The parameter for PCIIOCDMAALLOC needs to contain&n; * both the size of the request and the flag values&n; * to be used in setting up the DMA.&n; *&n; * Any flags normally useful in pciio_dmamap&n; * or pciio_dmatrans function calls can6 be used here.&n; */
DECL|macro|PCIIOCDMAALLOC_REQUEST_PACK
mdefine_line|#define&t;PCIIOCDMAALLOC_REQUEST_PACK(flags,size)&t;&t;&bslash;&n;&t;((((uint64_t)(flags))&lt;&lt;32)|&t;&t;&t;&bslash;&n;&t; (((uint64_t)(size))&amp;0xFFFFFFFF))
macro_line|#endif&t;/* _ASM_SN_PCI_PCIBA_H */
eof
