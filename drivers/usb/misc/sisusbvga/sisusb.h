multiline_comment|/*&n; * sisusb - usb kernel driver for Net2280/SiS315 based USB2VGA dongles&n; *&n; * Copyright (C) 2005 by Thomas Winischhofer, Vienna, Austria&n; *&n; * If distributed as part of the Linux kernel, this code is licensed under the&n; * terms of the GPL v2.&n; *&n; * Otherwise, the following license terms apply:&n; *&n; * * Redistribution and use in source and binary forms, with or without&n; * * modification, are permitted provided that the following conditions&n; * * are met:&n; * * 1) Redistributions of source code must retain the above copyright&n; * *    notice, this list of conditions and the following disclaimer.&n; * * 2) Redistributions in binary form must reproduce the above copyright&n; * *    notice, this list of conditions and the following disclaimer in the&n; * *    documentation and/or other materials provided with the distribution.&n; * * 3) The name of the author may not be used to endorse or promote products&n; * *    derived from this software without specific prior written permission.&n; * *&n; * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESSED OR&n; * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,&n; * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY&n; * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * Author: &t;Thomas Winischhofer &lt;thomas@winischhofer.net&gt;&n; *&n; */
macro_line|#ifndef _SISUSB_H_
DECL|macro|_SISUSB_H_
mdefine_line|#define _SISUSB_H_
macro_line|#ifdef CONFIG_COMPAT
macro_line|#if LINUX_VERSION_CODE &lt;= KERNEL_VERSION(2,6,10)
macro_line|#include &lt;linux/ioctl32.h&gt;
DECL|macro|SISUSB_OLD_CONFIG_COMPAT
mdefine_line|#define SISUSB_OLD_CONFIG_COMPAT
macro_line|#else
DECL|macro|SISUSB_NEW_CONFIG_COMPAT
mdefine_line|#define SISUSB_NEW_CONFIG_COMPAT
macro_line|#endif
macro_line|#endif
multiline_comment|/* Version Information */
DECL|macro|SISUSB_VERSION
mdefine_line|#define SISUSB_VERSION&t;&t;0
DECL|macro|SISUSB_REVISION
mdefine_line|#define SISUSB_REVISION &t;0
DECL|macro|SISUSB_PATCHLEVEL
mdefine_line|#define SISUSB_PATCHLEVEL&t;7
multiline_comment|/* USB related */
DECL|macro|SISUSB_MINOR
mdefine_line|#define SISUSB_MINOR&t;133&t;&t;/* FIXME */
multiline_comment|/* Size of the sisusb input/output buffers */
DECL|macro|SISUSB_IBUF_SIZE
mdefine_line|#define SISUSB_IBUF_SIZE  0x01000
DECL|macro|SISUSB_OBUF_SIZE
mdefine_line|#define SISUSB_OBUF_SIZE  0x10000&t;/* fixed */
DECL|macro|NUMOBUFS
mdefine_line|#define NUMOBUFS 8&t;&t;&t;/* max number of output buffers/output URBs */
multiline_comment|/* About endianness:&n; *&n; * 1) I/O ports, PCI config registers. The read/write()&n; *    calls emulate inX/outX. Hence, the data is&n; *    expected/delivered in machine endiannes by this&n; *    driver.&n; * 2) Video memory. The data is copied 1:1. There is&n; *    no swapping. Ever. This means for userland that&n; *    the data has to be prepared properly. (Hint:&n; *    think graphics data format, command queue,&n; *    hardware cursor.)&n; * 3) MMIO. Data is copied 1:1. MMIO must be swapped&n; *    properly by userland.&n; *&n; */
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|SISUSB_CORRECT_ENDIANNESS_PACKET
mdefine_line|#define SISUSB_CORRECT_ENDIANNESS_PACKET(p) &t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;p-&gt;header  = cpu_to_le16(p-&gt;header);&t;&bslash;&n;&t;&t;p-&gt;address = cpu_to_le32(p-&gt;address);&t;&bslash;&n;&t;&t;p-&gt;data    = cpu_to_le32(p-&gt;data);&t;&bslash;&n;&t;} while(0)
macro_line|#else
DECL|macro|SISUSB_CORRECT_ENDIANNESS_PACKET
mdefine_line|#define SISUSB_CORRECT_ENDIANNESS_PACKET(p)
macro_line|#endif
r_struct
id|sisusb_usb_data
suffix:semicolon
DECL|struct|sisusb_urb_context
r_struct
id|sisusb_urb_context
(brace
multiline_comment|/* urb-&gt;context for outbound bulk URBs */
DECL|member|sisusb
r_struct
id|sisusb_usb_data
op_star
id|sisusb
suffix:semicolon
DECL|member|urbindex
r_int
id|urbindex
suffix:semicolon
DECL|member|actual_length
r_int
op_star
id|actual_length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sisusb_usb_data
r_struct
id|sisusb_usb_data
(brace
DECL|member|sisusb_dev
r_struct
id|usb_device
op_star
id|sisusb_dev
suffix:semicolon
DECL|member|interface
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
DECL|member|kref
r_struct
id|kref
id|kref
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
multiline_comment|/* for syncind and timeouts */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* general race avoidance */
DECL|member|ifnum
r_int
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* interface number of the USB device */
DECL|member|minor
r_int
id|minor
suffix:semicolon
multiline_comment|/* minor (for logging clarity) */
DECL|member|isopen
r_int
id|isopen
suffix:semicolon
multiline_comment|/* !=0 if open */
DECL|member|present
r_int
id|present
suffix:semicolon
multiline_comment|/* !=0 if device is present on the bus */
DECL|member|ready
r_int
id|ready
suffix:semicolon
multiline_comment|/* !=0 if device is ready for userland */
macro_line|#ifdef SISUSB_OLD_CONFIG_COMPAT
DECL|member|ioctl32registered
r_int
id|ioctl32registered
suffix:semicolon
macro_line|#endif
DECL|member|numobufs
r_int
id|numobufs
suffix:semicolon
multiline_comment|/* number of obufs = number of out urbs */
DECL|member|obuf
DECL|member|ibuf
r_char
op_star
id|obuf
(braket
id|NUMOBUFS
)braket
comma
op_star
id|ibuf
suffix:semicolon
multiline_comment|/* transfer buffers */
DECL|member|obufsize
DECL|member|ibufsize
r_int
id|obufsize
comma
id|ibufsize
suffix:semicolon
DECL|member|transfer_dma_out
id|dma_addr_t
id|transfer_dma_out
(braket
id|NUMOBUFS
)braket
suffix:semicolon
DECL|member|transfer_dma_in
id|dma_addr_t
id|transfer_dma_in
suffix:semicolon
DECL|member|sisurbout
r_struct
id|urb
op_star
id|sisurbout
(braket
id|NUMOBUFS
)braket
suffix:semicolon
DECL|member|sisurbin
r_struct
id|urb
op_star
id|sisurbin
suffix:semicolon
DECL|member|urbstatus
r_int
r_char
id|urbstatus
(braket
id|NUMOBUFS
)braket
suffix:semicolon
DECL|member|completein
r_int
r_char
id|completein
suffix:semicolon
DECL|member|urbout_context
r_struct
id|sisusb_urb_context
id|urbout_context
(braket
id|NUMOBUFS
)braket
suffix:semicolon
DECL|member|flagb0
r_int
r_int
id|flagb0
suffix:semicolon
DECL|member|vrambase
r_int
r_int
id|vrambase
suffix:semicolon
multiline_comment|/* framebuffer base */
DECL|member|vramsize
r_int
r_int
id|vramsize
suffix:semicolon
multiline_comment|/* framebuffer size (bytes) */
DECL|member|mmiobase
r_int
r_int
id|mmiobase
suffix:semicolon
DECL|member|mmiosize
r_int
r_int
id|mmiosize
suffix:semicolon
DECL|member|ioportbase
r_int
r_int
id|ioportbase
suffix:semicolon
DECL|member|devinit
r_int
r_char
id|devinit
suffix:semicolon
multiline_comment|/* device initialized? */
DECL|member|gfxinit
r_int
r_char
id|gfxinit
suffix:semicolon
multiline_comment|/* graphics core initialized? */
DECL|member|chipid
DECL|member|chipvendor
r_int
r_int
id|chipid
comma
id|chipvendor
suffix:semicolon
DECL|member|chiprevision
r_int
r_int
id|chiprevision
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_sisusb_dev
mdefine_line|#define to_sisusb_dev(d) container_of(d, struct sisusb_usb_data, kref)
multiline_comment|/* USB transport related */
multiline_comment|/* urbstatus */
DECL|macro|SU_URB_BUSY
mdefine_line|#define SU_URB_BUSY   1
DECL|macro|SU_URB_ALLOC
mdefine_line|#define SU_URB_ALLOC  2
multiline_comment|/* Endpoints */
DECL|macro|SISUSB_EP_GFX_IN
mdefine_line|#define SISUSB_EP_GFX_IN&t;0x0e&t;/* gfx std packet out(0e)/in(8e) */
DECL|macro|SISUSB_EP_GFX_OUT
mdefine_line|#define SISUSB_EP_GFX_OUT&t;0x0e
DECL|macro|SISUSB_EP_GFX_BULK_OUT
mdefine_line|#define SISUSB_EP_GFX_BULK_OUT&t;0x01&t;/* gfx mem bulk out/in */
DECL|macro|SISUSB_EP_GFX_BULK_IN
mdefine_line|#define SISUSB_EP_GFX_BULK_IN&t;0x02&t;/* ? 2 is &quot;OUT&quot; ? */
DECL|macro|SISUSB_EP_GFX_LBULK_OUT
mdefine_line|#define SISUSB_EP_GFX_LBULK_OUT&t;0x03&t;/* gfx large mem bulk out */
DECL|macro|SISUSB_EP_UNKNOWN_04
mdefine_line|#define SISUSB_EP_UNKNOWN_04&t;0x04&t;/* ? 4 is &quot;OUT&quot; ? - unused */
DECL|macro|SISUSB_EP_BRIDGE_IN
mdefine_line|#define SISUSB_EP_BRIDGE_IN&t;0x0d&t;/* Net2280 out(0d)/in(8d) */
DECL|macro|SISUSB_EP_BRIDGE_OUT
mdefine_line|#define SISUSB_EP_BRIDGE_OUT&t;0x0d
DECL|macro|SISUSB_TYPE_MEM
mdefine_line|#define SISUSB_TYPE_MEM&t;&t;0
DECL|macro|SISUSB_TYPE_IO
mdefine_line|#define SISUSB_TYPE_IO&t;&t;1
DECL|struct|sisusb_packet
r_struct
id|sisusb_packet
(brace
DECL|member|header
r_int
r_int
id|header
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|data
id|u32
id|data
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|CLEARPACKET
mdefine_line|#define CLEARPACKET(packet) memset(packet, 0, 10)
multiline_comment|/* PCI bridge related */
DECL|macro|SISUSB_PCI_MEMBASE
mdefine_line|#define SISUSB_PCI_MEMBASE&t;0xd0000000
DECL|macro|SISUSB_PCI_MMIOBASE
mdefine_line|#define SISUSB_PCI_MMIOBASE&t;0xe4000000
DECL|macro|SISUSB_PCI_IOPORTBASE
mdefine_line|#define SISUSB_PCI_IOPORTBASE&t;0x0000d000
DECL|macro|SISUSB_PCI_PSEUDO_MEMBASE
mdefine_line|#define SISUSB_PCI_PSEUDO_MEMBASE&t;0x10000000
DECL|macro|SISUSB_PCI_PSEUDO_MMIOBASE
mdefine_line|#define SISUSB_PCI_PSEUDO_MMIOBASE&t;0x20000000
DECL|macro|SISUSB_PCI_PSEUDO_IOPORTBASE
mdefine_line|#define SISUSB_PCI_PSEUDO_IOPORTBASE&t;0x0000d000
DECL|macro|SISUSB_PCI_PSEUDO_PCIBASE
mdefine_line|#define SISUSB_PCI_PSEUDO_PCIBASE&t;0x00010000
DECL|macro|SISUSB_PCI_MMIOSIZE
mdefine_line|#define SISUSB_PCI_MMIOSIZE&t;(128*1024)
DECL|macro|SISUSB_PCI_PCONFSIZE
mdefine_line|#define SISUSB_PCI_PCONFSIZE&t;0x5c
multiline_comment|/* graphics core related */
DECL|macro|AROFFSET
mdefine_line|#define AROFFSET&t;0x40
DECL|macro|ARROFFSET
mdefine_line|#define ARROFFSET&t;0x41
DECL|macro|GROFFSET
mdefine_line|#define GROFFSET&t;0x4e
DECL|macro|SROFFSET
mdefine_line|#define SROFFSET&t;0x44
DECL|macro|CROFFSET
mdefine_line|#define CROFFSET&t;0x54
DECL|macro|MISCROFFSET
mdefine_line|#define MISCROFFSET&t;0x4c
DECL|macro|MISCWOFFSET
mdefine_line|#define MISCWOFFSET&t;0x42
DECL|macro|INPUTSTATOFFSET
mdefine_line|#define INPUTSTATOFFSET 0x5A
DECL|macro|PART1OFFSET
mdefine_line|#define PART1OFFSET&t;0x04
DECL|macro|PART2OFFSET
mdefine_line|#define PART2OFFSET&t;0x10
DECL|macro|PART3OFFSET
mdefine_line|#define PART3OFFSET&t;0x12
DECL|macro|PART4OFFSET
mdefine_line|#define PART4OFFSET&t;0x14
DECL|macro|PART5OFFSET
mdefine_line|#define PART5OFFSET&t;0x16
DECL|macro|CAPTUREOFFSET
mdefine_line|#define CAPTUREOFFSET&t;0x00
DECL|macro|VIDEOOFFSET
mdefine_line|#define VIDEOOFFSET&t;0x02
DECL|macro|COLREGOFFSET
mdefine_line|#define COLREGOFFSET&t;0x48
DECL|macro|PELMASKOFFSET
mdefine_line|#define PELMASKOFFSET&t;0x46
DECL|macro|VGAENABLE
mdefine_line|#define VGAENABLE&t;0x43
DECL|macro|SISAR
mdefine_line|#define SISAR&t;&t;SISUSB_PCI_IOPORTBASE + AROFFSET
DECL|macro|SISARR
mdefine_line|#define SISARR&t;&t;SISUSB_PCI_IOPORTBASE + ARROFFSET
DECL|macro|SISGR
mdefine_line|#define SISGR&t;&t;SISUSB_PCI_IOPORTBASE + GROFFSET
DECL|macro|SISSR
mdefine_line|#define SISSR&t;&t;SISUSB_PCI_IOPORTBASE + SROFFSET
DECL|macro|SISCR
mdefine_line|#define SISCR&t;&t;SISUSB_PCI_IOPORTBASE + CROFFSET
DECL|macro|SISMISCR
mdefine_line|#define SISMISCR&t;SISUSB_PCI_IOPORTBASE + MISCROFFSET
DECL|macro|SISMISCW
mdefine_line|#define SISMISCW&t;SISUSB_PCI_IOPORTBASE + MISCWOFFSET
DECL|macro|SISINPSTAT
mdefine_line|#define SISINPSTAT&t;SISUSB_PCI_IOPORTBASE + INPUTSTATOFFSET
DECL|macro|SISPART1
mdefine_line|#define SISPART1&t;SISUSB_PCI_IOPORTBASE + PART1OFFSET
DECL|macro|SISPART2
mdefine_line|#define SISPART2&t;SISUSB_PCI_IOPORTBASE + PART2OFFSET
DECL|macro|SISPART3
mdefine_line|#define SISPART3&t;SISUSB_PCI_IOPORTBASE + PART3OFFSET
DECL|macro|SISPART4
mdefine_line|#define SISPART4&t;SISUSB_PCI_IOPORTBASE + PART4OFFSET
DECL|macro|SISPART5
mdefine_line|#define SISPART5&t;SISUSB_PCI_IOPORTBASE + PART5OFFSET
DECL|macro|SISCAP
mdefine_line|#define SISCAP&t;&t;SISUSB_PCI_IOPORTBASE + CAPTUREOFFSET
DECL|macro|SISVID
mdefine_line|#define SISVID&t;&t;SISUSB_PCI_IOPORTBASE + VIDEOOFFSET
DECL|macro|SISCOLIDXR
mdefine_line|#define SISCOLIDXR&t;SISUSB_PCI_IOPORTBASE + COLREGOFFSET - 1
DECL|macro|SISCOLIDX
mdefine_line|#define SISCOLIDX&t;SISUSB_PCI_IOPORTBASE + COLREGOFFSET
DECL|macro|SISCOLDATA
mdefine_line|#define SISCOLDATA&t;SISUSB_PCI_IOPORTBASE + COLREGOFFSET + 1
DECL|macro|SISCOL2IDX
mdefine_line|#define SISCOL2IDX&t;SISPART5
DECL|macro|SISCOL2DATA
mdefine_line|#define SISCOL2DATA&t;SISPART5 + 1
DECL|macro|SISPEL
mdefine_line|#define SISPEL&t;&t;SISUSB_PCI_IOPORTBASE + PELMASKOFFSET
DECL|macro|SISVGAEN
mdefine_line|#define SISVGAEN&t;SISUSB_PCI_IOPORTBASE + VGAENABLE
DECL|macro|SISDACA
mdefine_line|#define SISDACA&t;&t;SISCOLIDX
DECL|macro|SISDACD
mdefine_line|#define SISDACD&t;&t;SISCOLDATA
multiline_comment|/* ioctl related */
multiline_comment|/* Structure argument for SISUSB_GET_INFO ioctl  */
DECL|struct|sisusb_info
r_struct
id|sisusb_info
(brace
DECL|member|sisusb_id
id|__u32
id|sisusb_id
suffix:semicolon
multiline_comment|/* for identifying sisusb */
DECL|macro|SISUSB_ID
mdefine_line|#define SISUSB_ID  0x53495355&t;&t;/* Identify myself with &squot;SISU&squot; */
DECL|member|sisusb_version
id|__u8
id|sisusb_version
suffix:semicolon
DECL|member|sisusb_revision
id|__u8
id|sisusb_revision
suffix:semicolon
DECL|member|sisusb_patchlevel
id|__u8
id|sisusb_patchlevel
suffix:semicolon
DECL|member|sisusb_gfxinit
id|__u8
id|sisusb_gfxinit
suffix:semicolon
multiline_comment|/* graphics core initialized? */
DECL|member|sisusb_vrambase
id|__u32
id|sisusb_vrambase
suffix:semicolon
DECL|member|sisusb_mmiobase
id|__u32
id|sisusb_mmiobase
suffix:semicolon
DECL|member|sisusb_iobase
id|__u32
id|sisusb_iobase
suffix:semicolon
DECL|member|sisusb_pcibase
id|__u32
id|sisusb_pcibase
suffix:semicolon
DECL|member|sisusb_vramsize
id|__u32
id|sisusb_vramsize
suffix:semicolon
multiline_comment|/* framebuffer size in bytes */
DECL|member|sisusb_minor
id|__u32
id|sisusb_minor
suffix:semicolon
DECL|member|sisusb_fbdevactive
id|__u32
id|sisusb_fbdevactive
suffix:semicolon
multiline_comment|/* != 0 if framebuffer device active */
DECL|member|sisusb_reserved
id|__u8
id|sisusb_reserved
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
DECL|struct|sisusb_command
r_struct
id|sisusb_command
(brace
DECL|member|operation
id|__u8
id|operation
suffix:semicolon
multiline_comment|/* see below */
DECL|member|data0
id|__u8
id|data0
suffix:semicolon
multiline_comment|/* operation dependent */
DECL|member|data1
id|__u8
id|data1
suffix:semicolon
multiline_comment|/* operation dependent */
DECL|member|data2
id|__u8
id|data2
suffix:semicolon
multiline_comment|/* operation dependent */
DECL|member|data3
id|__u32
id|data3
suffix:semicolon
multiline_comment|/* operation dependent */
DECL|member|data4
id|__u32
id|data4
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
DECL|macro|SUCMD_GET
mdefine_line|#define SUCMD_GET      0x01&t;/* for all: data0 = index, data3 = port */
DECL|macro|SUCMD_SET
mdefine_line|#define SUCMD_SET      0x02&t;/* data1 = value */
DECL|macro|SUCMD_SETOR
mdefine_line|#define SUCMD_SETOR    0x03&t;/* data1 = or */
DECL|macro|SUCMD_SETAND
mdefine_line|#define SUCMD_SETAND   0x04&t;/* data1 = and */
DECL|macro|SUCMD_SETANDOR
mdefine_line|#define SUCMD_SETANDOR 0x05&t;/* data1 = and, data2 = or */
DECL|macro|SUCMD_SETMASK
mdefine_line|#define SUCMD_SETMASK  0x06&t;/* data1 = data, data2 = mask */
DECL|macro|SUCMD_CLRSCR
mdefine_line|#define SUCMD_CLRSCR   0x07&t;/* data0:1:2 = length, data3 = address */
DECL|macro|SISUSB_COMMAND
mdefine_line|#define SISUSB_COMMAND&t;&t;_IOWR(0xF3,0x3D,struct sisusb_command)
DECL|macro|SISUSB_GET_CONFIG_SIZE
mdefine_line|#define SISUSB_GET_CONFIG_SIZE &t;_IOR(0xF3,0x3E,__u32)
DECL|macro|SISUSB_GET_CONFIG
mdefine_line|#define SISUSB_GET_CONFIG  &t;_IOR(0xF3,0x3F,struct sisusb_info)
macro_line|#endif /* SISUSB_H */
eof
