multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_PCIIO_H
DECL|macro|_ASM_IA64_SN_PCI_PCIIO_H
mdefine_line|#define _ASM_IA64_SN_PCI_PCIIO_H
multiline_comment|/*&n; * pciio.h -- platform-independent PCI interface&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/sn/ioerror.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#else
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;ioerror.h&gt;
macro_line|#include &lt;driver.h&gt;
macro_line|#include &lt;hcl.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/sn/dmamap.h&gt;
macro_line|#include &lt;asm/sn/alenlist.h&gt;
macro_line|#else
macro_line|#include &lt;dmamap.h&gt;
macro_line|#include &lt;alenlist.h&gt;
macro_line|#endif
DECL|typedef|pciio_vendor_id_t
r_typedef
r_int
id|pciio_vendor_id_t
suffix:semicolon
DECL|macro|PCIIO_VENDOR_ID_NONE
mdefine_line|#define PCIIO_VENDOR_ID_NONE&t;(-1)
DECL|typedef|pciio_device_id_t
r_typedef
r_int
id|pciio_device_id_t
suffix:semicolon
DECL|macro|PCIIO_DEVICE_ID_NONE
mdefine_line|#define PCIIO_DEVICE_ID_NONE&t;(-1)
DECL|typedef|pciio_bus_t
r_typedef
r_uint8
id|pciio_bus_t
suffix:semicolon
multiline_comment|/* PCI bus number (0..255) */
DECL|typedef|pciio_slot_t
r_typedef
r_uint8
id|pciio_slot_t
suffix:semicolon
multiline_comment|/* PCI slot number (0..31, 255) */
DECL|typedef|pciio_function_t
r_typedef
r_uint8
id|pciio_function_t
suffix:semicolon
multiline_comment|/* PCI func number (0..7, 255) */
DECL|macro|PCIIO_SLOTS
mdefine_line|#define&t;PCIIO_SLOTS&t;&t;((pciio_slot_t)32)
DECL|macro|PCIIO_FUNCS
mdefine_line|#define&t;PCIIO_FUNCS&t;&t;((pciio_function_t)8)
DECL|macro|PCIIO_SLOT_NONE
mdefine_line|#define&t;PCIIO_SLOT_NONE&t;&t;((pciio_slot_t)255)
DECL|macro|PCIIO_FUNC_NONE
mdefine_line|#define&t;PCIIO_FUNC_NONE&t;&t;((pciio_function_t)255)
DECL|typedef|pciio_intr_line_t
r_typedef
r_int
id|pciio_intr_line_t
suffix:semicolon
multiline_comment|/* PCI interrupt line(s) */
DECL|macro|PCIIO_INTR_LINE
mdefine_line|#define PCIIO_INTR_LINE(n)      (0x1 &lt;&lt; (n))
DECL|macro|PCIIO_INTR_LINE_A
mdefine_line|#define PCIIO_INTR_LINE_A&t;(0x1)
DECL|macro|PCIIO_INTR_LINE_B
mdefine_line|#define PCIIO_INTR_LINE_B&t;(0x2)
DECL|macro|PCIIO_INTR_LINE_C
mdefine_line|#define PCIIO_INTR_LINE_C&t;(0x4)
DECL|macro|PCIIO_INTR_LINE_D
mdefine_line|#define PCIIO_INTR_LINE_D&t;(0x8)
DECL|typedef|pciio_space_t
r_typedef
r_int
id|pciio_space_t
suffix:semicolon
multiline_comment|/* PCI address space designation */
DECL|macro|PCIIO_SPACE_NONE
mdefine_line|#define PCIIO_SPACE_NONE&t;(0)
DECL|macro|PCIIO_SPACE_ROM
mdefine_line|#define&t;PCIIO_SPACE_ROM&t;&t;(1)
DECL|macro|PCIIO_SPACE_IO
mdefine_line|#define PCIIO_SPACE_IO&t;&t;(2)
multiline_comment|/*&t;PCIIO_SPACE_&t;&t;(3) */
DECL|macro|PCIIO_SPACE_MEM
mdefine_line|#define PCIIO_SPACE_MEM&t;&t;(4)
DECL|macro|PCIIO_SPACE_MEM32
mdefine_line|#define PCIIO_SPACE_MEM32&t;(5)
DECL|macro|PCIIO_SPACE_MEM64
mdefine_line|#define PCIIO_SPACE_MEM64&t;(6)
DECL|macro|PCIIO_SPACE_CFG
mdefine_line|#define PCIIO_SPACE_CFG&t;&t;(7)
DECL|macro|PCIIO_SPACE_WIN0
mdefine_line|#define PCIIO_SPACE_WIN0&t;(8)
DECL|macro|PCIIO_SPACE_WIN
mdefine_line|#define PCIIO_SPACE_WIN(n)&t;(PCIIO_SPACE_WIN0+(n))&t;/* 8..13 */
multiline_comment|/*&t;PCIIO_SPACE_&t;&t;(14) */
DECL|macro|PCIIO_SPACE_BAD
mdefine_line|#define PCIIO_SPACE_BAD&t;&t;(15)
macro_line|#if 1&t;/* does anyone really use these? */
DECL|macro|PCIIO_SPACE_USER0
mdefine_line|#define PCIIO_SPACE_USER0&t;(20)
DECL|macro|PCIIO_SPACE_USER
mdefine_line|#define PCIIO_SPACE_USER(n)&t;(PCIIO_SPACE_USER0+(n))&t;/* 20 .. ? */
macro_line|#endif
multiline_comment|/*&n; * PCI_NOWHERE is the error value returned in&n; * place of a PCI address when there is no&n; * corresponding address.&n; */
DECL|macro|PCI_NOWHERE
mdefine_line|#define&t;PCI_NOWHERE&t;&t;(0)
multiline_comment|/*&n; *    Acceptable flag bits for pciio service calls&n; *&n; * PCIIO_FIXED: require that mappings be established&n; *&t;using fixed sharable resources; address&n; *&t;translation results will be permanently&n; *&t;available. (PIOMAP_FIXED and DMAMAP_FIXED are&n; *&t;the same numeric value and are acceptable).&n; * PCIIO_NOSLEEP: if any part of the operation would&n; *&t;sleep waiting for resoruces, return an error&n; *&t;instead. (PIOMAP_NOSLEEP and DMAMAP_NOSLEEP are&n; *&t;the same numeric value and are acceptable).&n; * PCIIO_INPLACE: when operating on alenlist structures,&n; *&t;reuse the source alenlist rather than creating a&n; *&t;new one. (PIOMAP_INPLACE and DMAMAP_INPLACE are&n; *&t;the same numeric value and are acceptable).&n; *&n; * PCIIO_DMA_CMD: configure this stream as a&n; *&t;generic &quot;command&quot; stream. Generally this&n; *&t;means turn off prefetchers and write&n; *&t;gatherers, and whatever else might be&n; *&t;necessary to make command ring DMAs&n; *&t;work as expected.&n; * PCIIO_DMA_DATA: configure this stream as a&n; *&t;generic &quot;data&quot; stream. Generally, this&n; *&t;means turning on prefetchers and write&n; *&t;gatherers, and anything else that might&n; *&t;increase the DMA throughput (short of&n; *&t;using &quot;high priority&quot; or &quot;real time&quot;&n; *&t;resources that may lower overall system&n; *&t;performance).&n; * PCIIO_DMA_A64: this device is capable of&n; *&t;using 64-bit DMA addresses. Unless this&n; *&t;flag is specified, it is assumed that&n; *&t;the DMA address must be in the low 4G&n; *&t;of PCI space.&n; * PCIIO_PREFETCH: if there are prefetchers&n; *&t;available, they can be turned on.&n; * PCIIO_NOPREFETCH: any prefetchers along&n; *&t;the dma path should be turned off.&n; * PCIIO_WRITE_GATHER: if there are write gatherers&n; *&t;available, they can be turned on.&n; * PCIIO_NOWRITE_GATHER: any write gatherers along&n; *&t;the dma path should be turned off.&n; *&n; * PCIIO_BYTE_STREAM: the DMA stream represents a group&n; *&t;of ordered bytes. Arrange all byte swapping&n; *&t;hardware so that the bytes land in the correct&n; *&t;order. This is a common setting for data&n; *&t;channels, but is NOT implied by PCIIO_DMA_DATA.&n; * PCIIO_WORD_VALUES: the DMA stream is used to&n; *&t;communicate quantities stored in multiple bytes,&n; *&t;and the device doing the DMA is little-endian;&n; *&t;arrange any swapping hardware so that&n; *&t;32-bit-wide values are maintained. This is a&n; *&t;common setting for command rings that contain&n; *&t;DMA addresses and counts, but is NOT implied by&n; *&t;PCIIO_DMA_CMD. CPU Accesses to 16-bit fields&n; *&t;must have their address xor-ed with 2, and&n; *&t;accesses to individual bytes must have their&n; *&t;addresses xor-ed with 3 relative to what the&n; *&t;device expects.&n; *&n; * NOTE: any &quot;provider specific&quot; flags that&n; * conflict with the generic flags will&n; * override the generic flags, locally&n; * at that provider.&n; *&n; * Also, note that PCI-generic flags (PCIIO_) are&n; * in bits 0-14. The upper bits, 15-31, are reserved&n; * for PCI implementation-specific flags.&n; */
DECL|macro|PCIIO_FIXED
mdefine_line|#define&t;PCIIO_FIXED&t;&t;DMAMAP_FIXED
DECL|macro|PCIIO_NOSLEEP
mdefine_line|#define&t;PCIIO_NOSLEEP&t;&t;DMAMAP_NOSLEEP
DECL|macro|PCIIO_INPLACE
mdefine_line|#define&t;PCIIO_INPLACE&t;&t;DMAMAP_INPLACE
DECL|macro|PCIIO_DMA_CMD
mdefine_line|#define PCIIO_DMA_CMD&t;&t;0x0010
DECL|macro|PCIIO_DMA_DATA
mdefine_line|#define PCIIO_DMA_DATA&t;&t;0x0020
DECL|macro|PCIIO_DMA_A64
mdefine_line|#define PCIIO_DMA_A64&t;&t;0x0040
DECL|macro|PCIIO_WRITE_GATHER
mdefine_line|#define PCIIO_WRITE_GATHER&t;0x0100
DECL|macro|PCIIO_NOWRITE_GATHER
mdefine_line|#define PCIIO_NOWRITE_GATHER&t;0x0200
DECL|macro|PCIIO_PREFETCH
mdefine_line|#define PCIIO_PREFETCH&t;&t;0x0400
DECL|macro|PCIIO_NOPREFETCH
mdefine_line|#define PCIIO_NOPREFETCH&t;0x0800
multiline_comment|/* Requesting an endianness setting that the&n; * underlieing hardware can not support&n; * WILL result in a failure to allocate&n; * dmamaps or complete a dmatrans.&n; */
DECL|macro|PCIIO_BYTE_STREAM
mdefine_line|#define&t;PCIIO_BYTE_STREAM&t;0x1000&t;/* set BYTE SWAP for &quot;byte stream&quot; */
DECL|macro|PCIIO_WORD_VALUES
mdefine_line|#define&t;PCIIO_WORD_VALUES&t;0x2000&t;/* set BYTE SWAP for &quot;word values&quot; */
multiline_comment|/*&n; * Interface to deal with PCI endianness.&n; * The driver calls pciio_endian_set once, supplying the actual endianness of&n; * the device and the desired endianness.  On SGI systems, only use LITTLE if&n; * dealing with a driver that does software swizzling.  Most of the time,&n; * it&squot;s preferable to request BIG.  The return value indicates the endianness&n; * that is actually achieved.  On systems that support hardware swizzling,&n; * the achieved endianness will be the desired endianness.  On systems without&n; * swizzle hardware, the achieved endianness will be the device&squot;s endianness.&n; */
DECL|enum|pciio_endian_e
r_typedef
r_enum
id|pciio_endian_e
(brace
DECL|enumerator|PCIDMA_ENDIAN_BIG
id|PCIDMA_ENDIAN_BIG
comma
DECL|enumerator|PCIDMA_ENDIAN_LITTLE
id|PCIDMA_ENDIAN_LITTLE
DECL|typedef|pciio_endian_t
)brace
id|pciio_endian_t
suffix:semicolon
multiline_comment|/*&n; * Generic PCI bus information&n; */
DECL|enum|pciio_asic_type_e
r_typedef
r_enum
id|pciio_asic_type_e
(brace
DECL|enumerator|PCIIO_ASIC_TYPE_UNKNOWN
id|PCIIO_ASIC_TYPE_UNKNOWN
comma
DECL|enumerator|PCIIO_ASIC_TYPE_MACE
id|PCIIO_ASIC_TYPE_MACE
comma
DECL|enumerator|PCIIO_ASIC_TYPE_BRIDGE
id|PCIIO_ASIC_TYPE_BRIDGE
comma
DECL|enumerator|PCIIO_ASIC_TYPE_XBRIDGE
id|PCIIO_ASIC_TYPE_XBRIDGE
comma
DECL|enumerator|PCIIO_ASIC_TYPE_PIC
id|PCIIO_ASIC_TYPE_PIC
comma
DECL|typedef|pciio_asic_type_t
)brace
id|pciio_asic_type_t
suffix:semicolon
DECL|enum|pciio_bus_type_e
r_typedef
r_enum
id|pciio_bus_type_e
(brace
DECL|enumerator|PCIIO_BUS_TYPE_UNKNOWN
id|PCIIO_BUS_TYPE_UNKNOWN
comma
DECL|enumerator|PCIIO_BUS_TYPE_PCI
id|PCIIO_BUS_TYPE_PCI
comma
DECL|enumerator|PCIIO_BUS_TYPE_PCIX
id|PCIIO_BUS_TYPE_PCIX
DECL|typedef|pciio_bus_type_t
)brace
id|pciio_bus_type_t
suffix:semicolon
DECL|enum|pciio_bus_speed_e
r_typedef
r_enum
id|pciio_bus_speed_e
(brace
DECL|enumerator|PCIIO_BUS_SPEED_UNKNOWN
id|PCIIO_BUS_SPEED_UNKNOWN
comma
DECL|enumerator|PCIIO_BUS_SPEED_33
id|PCIIO_BUS_SPEED_33
comma
DECL|enumerator|PCIIO_BUS_SPEED_66
id|PCIIO_BUS_SPEED_66
comma
DECL|enumerator|PCIIO_BUS_SPEED_100
id|PCIIO_BUS_SPEED_100
comma
DECL|enumerator|PCIIO_BUS_SPEED_133
id|PCIIO_BUS_SPEED_133
DECL|typedef|pciio_bus_speed_t
)brace
id|pciio_bus_speed_t
suffix:semicolon
multiline_comment|/*&n; * Interface to set PCI arbitration priority for devices that require&n; * realtime characteristics.  pciio_priority_set is used to switch a&n; * device between the PCI high-priority arbitration ring and the low&n; * priority arbitration ring.&n; *&n; * (Note: this is strictly for the PCI arbitrary priority.  It has&n; * no direct relationship to GBR.)&n; */
DECL|enum|pciio_priority_e
r_typedef
r_enum
id|pciio_priority_e
(brace
DECL|enumerator|PCI_PRIO_LOW
id|PCI_PRIO_LOW
comma
DECL|enumerator|PCI_PRIO_HIGH
id|PCI_PRIO_HIGH
DECL|typedef|pciio_priority_t
)brace
id|pciio_priority_t
suffix:semicolon
multiline_comment|/*&n; * handles of various sorts&n; */
DECL|typedef|pciio_piomap_t
r_typedef
r_struct
id|pciio_piomap_s
op_star
id|pciio_piomap_t
suffix:semicolon
DECL|typedef|pciio_dmamap_t
r_typedef
r_struct
id|pciio_dmamap_s
op_star
id|pciio_dmamap_t
suffix:semicolon
DECL|typedef|pciio_intr_t
r_typedef
r_struct
id|pciio_intr_s
op_star
id|pciio_intr_t
suffix:semicolon
DECL|typedef|pciio_info_t
r_typedef
r_struct
id|pciio_info_s
op_star
id|pciio_info_t
suffix:semicolon
DECL|typedef|pciio_piospace_t
r_typedef
r_struct
id|pciio_piospace_s
op_star
id|pciio_piospace_t
suffix:semicolon
DECL|typedef|pciio_win_info_t
r_typedef
r_struct
id|pciio_win_info_s
op_star
id|pciio_win_info_t
suffix:semicolon
DECL|typedef|pciio_win_map_t
r_typedef
r_struct
id|pciio_win_map_s
op_star
id|pciio_win_map_t
suffix:semicolon
DECL|typedef|pciio_win_alloc_t
r_typedef
r_struct
id|pciio_win_alloc_s
op_star
id|pciio_win_alloc_t
suffix:semicolon
DECL|typedef|pciio_bus_map_t
r_typedef
r_struct
id|pciio_bus_map_s
op_star
id|pciio_bus_map_t
suffix:semicolon
DECL|typedef|pciio_businfo_t
r_typedef
r_struct
id|pciio_businfo_s
op_star
id|pciio_businfo_t
suffix:semicolon
multiline_comment|/* PIO MANAGEMENT */
multiline_comment|/*&n; *    A NOTE ON PCI PIO ADDRESSES&n; *&n; *      PCI supports three different address spaces: CFG&n; *      space, MEM space and I/O space. Further, each&n; *      card always accepts CFG accesses at an address&n; *      based on which slot it is attached to, but can&n; *      decode up to six address ranges.&n; *&n; *      Assignment of the base address registers for all&n; *      PCI devices is handled centrally; most commonly,&n; *      device drivers will want to talk to offsets&n; *      within one or another of the address ranges. In&n; *      order to do this, which of these &quot;address&n; *      spaces&quot; the PIO is directed into must be encoded&n; *      in the flag word.&n; *&n; *      We reserve the right to defer allocation of PCI&n; *      address space for a device window until the&n; *      driver makes a piomap_alloc or piotrans_addr&n; *      request.&n; *&n; *      If a device driver mucks with its device&squot;s base&n; *      registers through a PIO mapping to CFG space,&n; *      results of further PIO through the corresponding&n; *      window are UNDEFINED.&n; *&n; *      Windows are named by the index in the base&n; *      address register set for the device of the&n; *      desired register; IN THE CASE OF 64 BIT base&n; *      registers, the index should be to the word of&n; *      the register that contains the mapping type&n; *      bits; since the PCI CFG space is natively&n; *      organized little-endian fashion, this is the&n; *      first of the two words.&n; *&n; *      AT THE MOMENT, any required corrections for&n; *      endianness are the responsibility of the device&n; *      driver; not all platforms support control in&n; *      hardware of byteswapping hardware. We anticipate&n; *      providing flag bits to the PIO and DMA&n; *      management interfaces to request different&n; *      configurations of byteswapping hardware.&n; *&n; *      PIO Accesses to CFG space via the &quot;Bridge&quot; ASIC&n; *      used in IP30 platforms preserve the native byte&n; *      significance within the 32-bit word; byte&n; *      addresses for single byte accesses need to be&n; *      XORed with 3, and addresses for 16-bit accesses&n; *      need to be XORed with 2.&n; *&n; *      The IOC3 used on IP30, and other SGI PCI devices&n; *      as well, require use of 32-bit accesses to their&n; *      configuration space registers. Any potential PCI&n; *      bus providers need to be aware of this requirement.&n; */
DECL|macro|PCIIO_PIOMAP_CFG
mdefine_line|#define PCIIO_PIOMAP_CFG&t;(0x1)
DECL|macro|PCIIO_PIOMAP_MEM
mdefine_line|#define PCIIO_PIOMAP_MEM&t;(0x2)
DECL|macro|PCIIO_PIOMAP_IO
mdefine_line|#define PCIIO_PIOMAP_IO&t;&t;(0x4)
DECL|macro|PCIIO_PIOMAP_WIN
mdefine_line|#define PCIIO_PIOMAP_WIN(n)&t;(0x8+(n))
r_typedef
id|pciio_piomap_t
DECL|typedef|pciio_piomap_alloc_f
id|pciio_piomap_alloc_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* set up mapping for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|pciio_space_t
id|space
comma
multiline_comment|/* which address space */
id|iopaddr_t
id|pcipio_addr
comma
multiline_comment|/* starting address */
r_int
id|byte_count
comma
r_int
id|byte_count_max
comma
multiline_comment|/* maximum size of a mapping */
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in sys/pio.h */
r_typedef
r_void
DECL|typedef|pciio_piomap_free_f
id|pciio_piomap_free_f
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
r_typedef
id|caddr_t
DECL|typedef|pciio_piomap_addr_f
id|pciio_piomap_addr_f
(paren
id|pciio_piomap_t
id|pciio_piomap
comma
multiline_comment|/* mapping resources */
id|iopaddr_t
id|pciio_addr
comma
multiline_comment|/* map for this pcipio address */
r_int
id|byte_count
)paren
suffix:semicolon
multiline_comment|/* map this many bytes */
r_typedef
r_void
DECL|typedef|pciio_piomap_done_f
id|pciio_piomap_done_f
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
r_typedef
id|caddr_t
DECL|typedef|pciio_piotrans_addr_f
id|pciio_piotrans_addr_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|pciio_space_t
id|space
comma
multiline_comment|/* which address space */
id|iopaddr_t
id|pciio_addr
comma
multiline_comment|/* starting address */
r_int
id|byte_count
comma
multiline_comment|/* map this many bytes */
r_int
r_int
id|flags
)paren
suffix:semicolon
r_typedef
id|caddr_t
DECL|typedef|pciio_pio_addr_f
id|pciio_pio_addr_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|pciio_space_t
id|space
comma
multiline_comment|/* which address space */
id|iopaddr_t
id|pciio_addr
comma
multiline_comment|/* starting address */
r_int
id|byte_count
comma
multiline_comment|/* map this many bytes */
id|pciio_piomap_t
op_star
id|mapp
comma
multiline_comment|/* in case a piomap was needed */
r_int
r_int
id|flags
)paren
suffix:semicolon
r_typedef
id|iopaddr_t
DECL|typedef|pciio_piospace_alloc_f
id|pciio_piospace_alloc_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* PIO space for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* Device descriptor   */
id|pciio_space_t
id|space
comma
multiline_comment|/* which address space  */
r_int
id|byte_count
comma
multiline_comment|/* Number of bytes of space */
r_int
id|alignment
)paren
suffix:semicolon
multiline_comment|/* Alignment of allocation  */
r_typedef
r_void
DECL|typedef|pciio_piospace_free_f
id|pciio_piospace_free_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* Device freeing space */
id|pciio_space_t
id|space
comma
multiline_comment|/* Which space is freed */
id|iopaddr_t
id|pci_addr
comma
multiline_comment|/* Address being freed */
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Size freed           */
multiline_comment|/* DMA MANAGEMENT */
r_typedef
id|pciio_dmamap_t
DECL|typedef|pciio_dmamap_alloc_f
id|pciio_dmamap_alloc_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* set up mappings for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
r_int
id|byte_count_max
comma
multiline_comment|/* max size of a mapping */
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in dma.h */
r_typedef
r_void
DECL|typedef|pciio_dmamap_free_f
id|pciio_dmamap_free_f
(paren
id|pciio_dmamap_t
id|dmamap
)paren
suffix:semicolon
r_typedef
id|iopaddr_t
DECL|typedef|pciio_dmamap_addr_f
id|pciio_dmamap_addr_f
(paren
id|pciio_dmamap_t
id|dmamap
comma
multiline_comment|/* use these mapping resources */
id|paddr_t
id|paddr
comma
multiline_comment|/* map for this address */
r_int
id|byte_count
)paren
suffix:semicolon
multiline_comment|/* map this many bytes */
r_typedef
r_void
DECL|typedef|pciio_dmamap_done_f
id|pciio_dmamap_done_f
(paren
id|pciio_dmamap_t
id|dmamap
)paren
suffix:semicolon
r_typedef
id|iopaddr_t
DECL|typedef|pciio_dmatrans_addr_f
id|pciio_dmatrans_addr_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|paddr_t
id|paddr
comma
multiline_comment|/* system physical address */
r_int
id|byte_count
comma
multiline_comment|/* length */
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in dma.h */
r_typedef
r_void
DECL|typedef|pciio_dmamap_drain_f
id|pciio_dmamap_drain_f
(paren
id|pciio_dmamap_t
id|map
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|pciio_dmaaddr_drain_f
id|pciio_dmaaddr_drain_f
(paren
id|vertex_hdl_t
id|vhdl
comma
id|paddr_t
id|addr
comma
r_int
id|bytes
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|pciio_dmalist_drain_f
id|pciio_dmalist_drain_f
(paren
id|vertex_hdl_t
id|vhdl
comma
id|alenlist_t
id|list
)paren
suffix:semicolon
multiline_comment|/* INTERRUPT MANAGEMENT */
r_typedef
id|pciio_intr_t
DECL|typedef|pciio_intr_alloc_f
id|pciio_intr_alloc_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* which PCI device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|pciio_intr_line_t
id|lines
comma
multiline_comment|/* which line(s) will be used */
id|vertex_hdl_t
id|owner_dev
)paren
suffix:semicolon
multiline_comment|/* owner of this intr */
r_typedef
r_void
DECL|typedef|pciio_intr_free_f
id|pciio_intr_free_f
(paren
id|pciio_intr_t
id|intr_hdl
)paren
suffix:semicolon
r_typedef
r_int
DECL|typedef|pciio_intr_connect_f
id|pciio_intr_connect_f
(paren
id|pciio_intr_t
id|intr_hdl
comma
id|intr_func_t
id|intr_func
comma
id|intr_arg_t
id|intr_arg
)paren
suffix:semicolon
multiline_comment|/* pciio intr resource handle */
r_typedef
r_void
DECL|typedef|pciio_intr_disconnect_f
id|pciio_intr_disconnect_f
(paren
id|pciio_intr_t
id|intr_hdl
)paren
suffix:semicolon
r_typedef
id|vertex_hdl_t
DECL|typedef|pciio_intr_cpu_get_f
id|pciio_intr_cpu_get_f
(paren
id|pciio_intr_t
id|intr_hdl
)paren
suffix:semicolon
multiline_comment|/* pciio intr resource handle */
multiline_comment|/* CONFIGURATION MANAGEMENT */
r_typedef
r_void
DECL|typedef|pciio_provider_startup_f
id|pciio_provider_startup_f
(paren
id|vertex_hdl_t
id|pciio_provider
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|pciio_provider_shutdown_f
id|pciio_provider_shutdown_f
(paren
id|vertex_hdl_t
id|pciio_provider
)paren
suffix:semicolon
r_typedef
r_int
DECL|typedef|pciio_reset_f
id|pciio_reset_f
(paren
id|vertex_hdl_t
id|conn
)paren
suffix:semicolon
multiline_comment|/* pci connection point */
r_typedef
id|pciio_endian_t
multiline_comment|/* actual endianness */
DECL|typedef|pciio_endian_set_f
id|pciio_endian_set_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* specify endianness for this device */
id|pciio_endian_t
id|device_end
comma
multiline_comment|/* endianness of device */
id|pciio_endian_t
id|desired_end
)paren
suffix:semicolon
multiline_comment|/* desired endianness */
r_typedef
r_uint64
DECL|typedef|pciio_config_get_f
id|pciio_config_get_f
(paren
id|vertex_hdl_t
id|conn
comma
multiline_comment|/* pci connection point */
r_int
r_int
id|reg
comma
multiline_comment|/* register byte offset */
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* width in bytes (1..4) */
r_typedef
r_void
DECL|typedef|pciio_config_set_f
id|pciio_config_set_f
(paren
id|vertex_hdl_t
id|conn
comma
multiline_comment|/* pci connection point */
r_int
r_int
id|reg
comma
multiline_comment|/* register byte offset */
r_int
r_int
id|size
comma
multiline_comment|/* width in bytes (1..4) */
r_uint64
id|value
)paren
suffix:semicolon
multiline_comment|/* value to store */
r_typedef
id|pciio_slot_t
DECL|typedef|pciio_error_extract_f
id|pciio_error_extract_f
(paren
id|vertex_hdl_t
id|vhdl
comma
id|pciio_space_t
op_star
id|spacep
comma
id|iopaddr_t
op_star
id|addrp
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|pciio_driver_reg_callback_f
id|pciio_driver_reg_callback_f
(paren
id|vertex_hdl_t
id|conn
comma
r_int
id|key1
comma
r_int
id|key2
comma
r_int
id|error
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|pciio_driver_unreg_callback_f
id|pciio_driver_unreg_callback_f
(paren
id|vertex_hdl_t
id|conn
comma
multiline_comment|/* pci connection point */
r_int
id|key1
comma
r_int
id|key2
comma
r_int
id|error
)paren
suffix:semicolon
r_typedef
r_int
DECL|typedef|pciio_device_unregister_f
id|pciio_device_unregister_f
(paren
id|vertex_hdl_t
id|conn
)paren
suffix:semicolon
multiline_comment|/*&n; * Adapters that provide a PCI interface adhere to this software interface.&n; */
DECL|struct|pciio_provider_s
r_typedef
r_struct
id|pciio_provider_s
(brace
multiline_comment|/* ASIC PROVIDER ID */
DECL|member|provider_asic
id|pciio_asic_type_t
id|provider_asic
suffix:semicolon
multiline_comment|/* PIO MANAGEMENT */
DECL|member|piomap_alloc
id|pciio_piomap_alloc_f
op_star
id|piomap_alloc
suffix:semicolon
DECL|member|piomap_free
id|pciio_piomap_free_f
op_star
id|piomap_free
suffix:semicolon
DECL|member|piomap_addr
id|pciio_piomap_addr_f
op_star
id|piomap_addr
suffix:semicolon
DECL|member|piomap_done
id|pciio_piomap_done_f
op_star
id|piomap_done
suffix:semicolon
DECL|member|piotrans_addr
id|pciio_piotrans_addr_f
op_star
id|piotrans_addr
suffix:semicolon
DECL|member|piospace_alloc
id|pciio_piospace_alloc_f
op_star
id|piospace_alloc
suffix:semicolon
DECL|member|piospace_free
id|pciio_piospace_free_f
op_star
id|piospace_free
suffix:semicolon
multiline_comment|/* DMA MANAGEMENT */
DECL|member|dmamap_alloc
id|pciio_dmamap_alloc_f
op_star
id|dmamap_alloc
suffix:semicolon
DECL|member|dmamap_free
id|pciio_dmamap_free_f
op_star
id|dmamap_free
suffix:semicolon
DECL|member|dmamap_addr
id|pciio_dmamap_addr_f
op_star
id|dmamap_addr
suffix:semicolon
DECL|member|dmamap_done
id|pciio_dmamap_done_f
op_star
id|dmamap_done
suffix:semicolon
DECL|member|dmatrans_addr
id|pciio_dmatrans_addr_f
op_star
id|dmatrans_addr
suffix:semicolon
DECL|member|dmamap_drain
id|pciio_dmamap_drain_f
op_star
id|dmamap_drain
suffix:semicolon
DECL|member|dmaaddr_drain
id|pciio_dmaaddr_drain_f
op_star
id|dmaaddr_drain
suffix:semicolon
DECL|member|dmalist_drain
id|pciio_dmalist_drain_f
op_star
id|dmalist_drain
suffix:semicolon
multiline_comment|/* INTERRUPT MANAGEMENT */
DECL|member|intr_alloc
id|pciio_intr_alloc_f
op_star
id|intr_alloc
suffix:semicolon
DECL|member|intr_free
id|pciio_intr_free_f
op_star
id|intr_free
suffix:semicolon
DECL|member|intr_connect
id|pciio_intr_connect_f
op_star
id|intr_connect
suffix:semicolon
DECL|member|intr_disconnect
id|pciio_intr_disconnect_f
op_star
id|intr_disconnect
suffix:semicolon
DECL|member|intr_cpu_get
id|pciio_intr_cpu_get_f
op_star
id|intr_cpu_get
suffix:semicolon
multiline_comment|/* CONFIGURATION MANAGEMENT */
DECL|member|provider_startup
id|pciio_provider_startup_f
op_star
id|provider_startup
suffix:semicolon
DECL|member|provider_shutdown
id|pciio_provider_shutdown_f
op_star
id|provider_shutdown
suffix:semicolon
DECL|member|reset
id|pciio_reset_f
op_star
id|reset
suffix:semicolon
DECL|member|endian_set
id|pciio_endian_set_f
op_star
id|endian_set
suffix:semicolon
DECL|member|config_get
id|pciio_config_get_f
op_star
id|config_get
suffix:semicolon
DECL|member|config_set
id|pciio_config_set_f
op_star
id|config_set
suffix:semicolon
multiline_comment|/* Error handling interface */
DECL|member|error_extract
id|pciio_error_extract_f
op_star
id|error_extract
suffix:semicolon
multiline_comment|/* Callback support */
DECL|member|driver_reg_callback
id|pciio_driver_reg_callback_f
op_star
id|driver_reg_callback
suffix:semicolon
DECL|member|driver_unreg_callback
id|pciio_driver_unreg_callback_f
op_star
id|driver_unreg_callback
suffix:semicolon
DECL|member|device_unregister
id|pciio_device_unregister_f
op_star
id|device_unregister
suffix:semicolon
DECL|typedef|pciio_provider_t
)brace
id|pciio_provider_t
suffix:semicolon
multiline_comment|/* PCI devices use these standard PCI provider interfaces */
r_extern
id|pciio_piomap_alloc_f
id|pciio_piomap_alloc
suffix:semicolon
r_extern
id|pciio_piomap_free_f
id|pciio_piomap_free
suffix:semicolon
r_extern
id|pciio_piomap_addr_f
id|pciio_piomap_addr
suffix:semicolon
r_extern
id|pciio_piomap_done_f
id|pciio_piomap_done
suffix:semicolon
r_extern
id|pciio_piotrans_addr_f
id|pciio_piotrans_addr
suffix:semicolon
r_extern
id|pciio_pio_addr_f
id|pciio_pio_addr
suffix:semicolon
r_extern
id|pciio_piospace_alloc_f
id|pciio_piospace_alloc
suffix:semicolon
r_extern
id|pciio_piospace_free_f
id|pciio_piospace_free
suffix:semicolon
r_extern
id|pciio_dmamap_alloc_f
id|pciio_dmamap_alloc
suffix:semicolon
r_extern
id|pciio_dmamap_free_f
id|pciio_dmamap_free
suffix:semicolon
r_extern
id|pciio_dmamap_addr_f
id|pciio_dmamap_addr
suffix:semicolon
r_extern
id|pciio_dmamap_done_f
id|pciio_dmamap_done
suffix:semicolon
r_extern
id|pciio_dmatrans_addr_f
id|pciio_dmatrans_addr
suffix:semicolon
r_extern
id|pciio_dmamap_drain_f
id|pciio_dmamap_drain
suffix:semicolon
r_extern
id|pciio_dmaaddr_drain_f
id|pciio_dmaaddr_drain
suffix:semicolon
r_extern
id|pciio_dmalist_drain_f
id|pciio_dmalist_drain
suffix:semicolon
r_extern
id|pciio_intr_alloc_f
id|pciio_intr_alloc
suffix:semicolon
r_extern
id|pciio_intr_free_f
id|pciio_intr_free
suffix:semicolon
r_extern
id|pciio_intr_connect_f
id|pciio_intr_connect
suffix:semicolon
r_extern
id|pciio_intr_disconnect_f
id|pciio_intr_disconnect
suffix:semicolon
r_extern
id|pciio_intr_cpu_get_f
id|pciio_intr_cpu_get
suffix:semicolon
r_extern
id|pciio_provider_startup_f
id|pciio_provider_startup
suffix:semicolon
r_extern
id|pciio_provider_shutdown_f
id|pciio_provider_shutdown
suffix:semicolon
r_extern
id|pciio_reset_f
id|pciio_reset
suffix:semicolon
r_extern
id|pciio_endian_set_f
id|pciio_endian_set
suffix:semicolon
r_extern
id|pciio_config_get_f
id|pciio_config_get
suffix:semicolon
r_extern
id|pciio_config_set_f
id|pciio_config_set
suffix:semicolon
multiline_comment|/* Widgetdev in the IOERROR structure is encoded as follows.&n; *&t;+---------------------------+&n; *&t;| slot (7:3) | function(2:0)|&n; *&t;+---------------------------+&n; * Following are the convenience interfaces to get at form&n; * a widgetdev or to break it into its constituents.&n; */
DECL|macro|PCIIO_WIDGETDEV_SLOT_SHFT
mdefine_line|#define PCIIO_WIDGETDEV_SLOT_SHFT&t;&t;3
DECL|macro|PCIIO_WIDGETDEV_SLOT_MASK
mdefine_line|#define PCIIO_WIDGETDEV_SLOT_MASK&t;&t;0x1f
DECL|macro|PCIIO_WIDGETDEV_FUNC_MASK
mdefine_line|#define PCIIO_WIDGETDEV_FUNC_MASK&t;&t;0x7
DECL|macro|pciio_widgetdev_create
mdefine_line|#define pciio_widgetdev_create(slot,func)       &bslash;&n;        (((slot) &lt;&lt; PCIIO_WIDGETDEV_SLOT_SHFT) + (func))
DECL|macro|pciio_widgetdev_slot_get
mdefine_line|#define pciio_widgetdev_slot_get(wdev)&t;&t;&bslash;&n;&t;(((wdev) &gt;&gt; PCIIO_WIDGETDEV_SLOT_SHFT) &amp; PCIIO_WIDGETDEV_SLOT_MASK)
DECL|macro|pciio_widgetdev_func_get
mdefine_line|#define pciio_widgetdev_func_get(wdev)&t;&t;&bslash;&n;&t;((wdev) &amp; PCIIO_WIDGETDEV_FUNC_MASK)
multiline_comment|/* Generic PCI card initialization interface&n; */
r_extern
r_int
id|pciio_driver_register
(paren
id|pciio_vendor_id_t
id|vendor_id
comma
multiline_comment|/* card&squot;s vendor number */
id|pciio_device_id_t
id|device_id
comma
multiline_comment|/* card&squot;s device number */
r_char
op_star
id|driver_prefix
comma
multiline_comment|/* driver prefix */
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|pciio_error_register
(paren
id|vertex_hdl_t
id|pconn
comma
multiline_comment|/* which slot */
id|error_handler_f
op_star
id|efunc
comma
multiline_comment|/* function to call */
id|error_handler_arg_t
id|einfo
)paren
suffix:semicolon
multiline_comment|/* first parameter */
r_extern
r_void
id|pciio_driver_unregister
c_func
(paren
r_char
op_star
id|driver_prefix
)paren
suffix:semicolon
DECL|typedef|pciio_iter_f
r_typedef
r_void
id|pciio_iter_f
c_func
(paren
id|vertex_hdl_t
id|pconn
)paren
suffix:semicolon
multiline_comment|/* a connect point */
multiline_comment|/* Interfaces used by PCI Bus Providers to talk to&n; * the Generic PCI layer.&n; */
r_extern
id|vertex_hdl_t
id|pciio_device_register
(paren
id|vertex_hdl_t
id|connectpt
comma
multiline_comment|/* vertex at center of bus */
id|vertex_hdl_t
id|master
comma
multiline_comment|/* card&squot;s master ASIC (pci provider) */
id|pciio_slot_t
id|slot
comma
multiline_comment|/* card&squot;s slot (0..?) */
id|pciio_function_t
id|func
comma
multiline_comment|/* card&squot;s func (0..?) */
id|pciio_vendor_id_t
id|vendor
comma
multiline_comment|/* card&squot;s vendor number */
id|pciio_device_id_t
id|device
)paren
suffix:semicolon
multiline_comment|/* card&squot;s device number */
r_extern
r_void
id|pciio_device_unregister
c_func
(paren
id|vertex_hdl_t
id|connectpt
)paren
suffix:semicolon
r_extern
id|pciio_info_t
id|pciio_device_info_new
(paren
id|pciio_info_t
id|pciio_info
comma
multiline_comment|/* preallocated info struct */
id|vertex_hdl_t
id|master
comma
multiline_comment|/* card&squot;s master ASIC (pci provider) */
id|pciio_slot_t
id|slot
comma
multiline_comment|/* card&squot;s slot (0..?) */
id|pciio_function_t
id|func
comma
multiline_comment|/* card&squot;s func (0..?) */
id|pciio_vendor_id_t
id|vendor
comma
multiline_comment|/* card&squot;s vendor number */
id|pciio_device_id_t
id|device
)paren
suffix:semicolon
multiline_comment|/* card&squot;s device number */
r_extern
r_void
id|pciio_device_info_free
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|vertex_hdl_t
id|pciio_device_info_register
c_func
(paren
id|vertex_hdl_t
id|connectpt
comma
multiline_comment|/* vertex at center of bus */
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
multiline_comment|/* details about conn point */
r_extern
r_void
id|pciio_device_info_unregister
c_func
(paren
id|vertex_hdl_t
id|connectpt
comma
multiline_comment|/* vertex at center of bus */
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
multiline_comment|/* details about conn point */
r_extern
r_int
id|pciio_device_attach
c_func
(paren
id|vertex_hdl_t
id|pcicard
comma
multiline_comment|/* vertex created by pciio_device_register */
r_int
id|drv_flags
)paren
suffix:semicolon
r_extern
r_int
id|pciio_device_detach
c_func
(paren
id|vertex_hdl_t
id|pcicard
comma
multiline_comment|/* vertex created by pciio_device_register */
r_int
id|drv_flags
)paren
suffix:semicolon
multiline_comment|/* create and initialize empty window mapping resource */
r_extern
id|pciio_win_map_t
id|pciio_device_win_map_new
c_func
(paren
id|pciio_win_map_t
id|win_map
comma
multiline_comment|/* preallocated win map structure */
r_int
id|region_size
comma
multiline_comment|/* size of region to be tracked */
r_int
id|page_size
)paren
suffix:semicolon
multiline_comment|/* allocation page size */
multiline_comment|/* destroy window mapping resource freeing up ancillary resources */
r_extern
r_void
id|pciio_device_win_map_free
c_func
(paren
id|pciio_win_map_t
id|win_map
)paren
suffix:semicolon
multiline_comment|/* preallocated win map structure */
multiline_comment|/* populate window mapping with free range of addresses */
r_extern
r_void
id|pciio_device_win_populate
c_func
(paren
id|pciio_win_map_t
id|win_map
comma
multiline_comment|/* win map */
id|iopaddr_t
id|ioaddr
comma
multiline_comment|/* base address of free range */
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* size of free range */
multiline_comment|/* allocate window from mapping resource */
r_extern
id|iopaddr_t
id|pciio_device_win_alloc
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
id|pciio_win_alloc_t
id|win_alloc
comma
multiline_comment|/* opaque allocation cookie */
r_int
id|start
comma
multiline_comment|/* start unit, or 0 */
r_int
id|size
comma
multiline_comment|/* size of allocation */
r_int
id|align
)paren
suffix:semicolon
multiline_comment|/* alignment of allocation */
multiline_comment|/* free previously allocated window */
r_extern
r_void
id|pciio_device_win_free
c_func
(paren
id|pciio_win_alloc_t
id|win_alloc
)paren
suffix:semicolon
multiline_comment|/* opaque allocation cookie */
multiline_comment|/*&n; * Generic PCI interface, for use with all PCI providers&n; * and all PCI devices.&n; */
multiline_comment|/* Generic PCI interrupt interfaces */
r_extern
id|vertex_hdl_t
id|pciio_intr_dev_get
c_func
(paren
id|pciio_intr_t
id|pciio_intr
)paren
suffix:semicolon
r_extern
id|vertex_hdl_t
id|pciio_intr_cpu_get
c_func
(paren
id|pciio_intr_t
id|pciio_intr
)paren
suffix:semicolon
multiline_comment|/* Generic PCI pio interfaces */
r_extern
id|vertex_hdl_t
id|pciio_pio_dev_get
c_func
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
r_extern
id|pciio_slot_t
id|pciio_pio_slot_get
c_func
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
r_extern
id|pciio_space_t
id|pciio_pio_space_get
c_func
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
r_extern
id|iopaddr_t
id|pciio_pio_pciaddr_get
c_func
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
r_extern
id|ulong
id|pciio_pio_mapsz_get
c_func
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
r_extern
id|caddr_t
id|pciio_pio_kvaddr_get
c_func
(paren
id|pciio_piomap_t
id|pciio_piomap
)paren
suffix:semicolon
multiline_comment|/* Generic PCI dma interfaces */
r_extern
id|vertex_hdl_t
id|pciio_dma_dev_get
c_func
(paren
id|pciio_dmamap_t
id|pciio_dmamap
)paren
suffix:semicolon
multiline_comment|/* Register/unregister PCI providers and get implementation handle */
r_extern
r_void
id|pciio_provider_register
c_func
(paren
id|vertex_hdl_t
id|provider
comma
id|pciio_provider_t
op_star
id|pciio_fns
)paren
suffix:semicolon
r_extern
r_void
id|pciio_provider_unregister
c_func
(paren
id|vertex_hdl_t
id|provider
)paren
suffix:semicolon
r_extern
id|pciio_provider_t
op_star
id|pciio_provider_fns_get
c_func
(paren
id|vertex_hdl_t
id|provider
)paren
suffix:semicolon
multiline_comment|/* Generic pci slot information access interface */
r_extern
id|pciio_info_t
id|pciio_info_chk
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
suffix:semicolon
r_extern
id|pciio_info_t
id|pciio_info_get
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
suffix:semicolon
r_extern
r_void
id|pciio_info_set
c_func
(paren
id|vertex_hdl_t
id|vhdl
comma
id|pciio_info_t
id|widget_info
)paren
suffix:semicolon
r_extern
id|vertex_hdl_t
id|pciio_info_dev_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|pciio_bus_t
id|pciio_info_bus_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|pciio_slot_t
id|pciio_info_slot_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|pciio_function_t
id|pciio_info_function_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|pciio_vendor_id_t
id|pciio_info_vendor_id_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|pciio_device_id_t
id|pciio_info_device_id_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|vertex_hdl_t
id|pciio_info_master_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|arbitrary_info_t
id|pciio_info_mfast_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|pciio_provider_t
op_star
id|pciio_info_pops_get
c_func
(paren
id|pciio_info_t
id|pciio_info
)paren
suffix:semicolon
r_extern
id|error_handler_f
op_star
id|pciio_info_efunc_get
c_func
(paren
id|pciio_info_t
)paren
suffix:semicolon
r_extern
id|error_handler_arg_t
op_star
id|pciio_info_einfo_get
c_func
(paren
id|pciio_info_t
)paren
suffix:semicolon
r_extern
id|pciio_space_t
id|pciio_info_bar_space_get
c_func
(paren
id|pciio_info_t
comma
r_int
)paren
suffix:semicolon
r_extern
id|iopaddr_t
id|pciio_info_bar_base_get
c_func
(paren
id|pciio_info_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pciio_info_bar_size_get
c_func
(paren
id|pciio_info_t
comma
r_int
)paren
suffix:semicolon
r_extern
id|iopaddr_t
id|pciio_info_rom_base_get
c_func
(paren
id|pciio_info_t
)paren
suffix:semicolon
r_extern
r_int
id|pciio_info_rom_size_get
c_func
(paren
id|pciio_info_t
)paren
suffix:semicolon
r_extern
r_int
id|pciio_info_type1_get
c_func
(paren
id|pciio_info_t
)paren
suffix:semicolon
r_extern
r_int
id|pciio_error_handler
c_func
(paren
id|vertex_hdl_t
comma
r_int
comma
id|ioerror_mode_t
comma
id|ioerror_t
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * sn_pci_set_vchan - Set the requested Virtual Channel bits into the mapped DMA&n; *                    address.&n; * @pci_dev: pci device pointer&n; * @addr: mapped dma address&n; * @vchan: Virtual Channel to use 0 or 1.&n; *&n; * Set the Virtual Channel bit in the mapped dma address.&n; */
r_static
r_inline
r_int
DECL|function|sn_pci_set_vchan
id|sn_pci_set_vchan
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci_dev
comma
id|dma_addr_t
op_star
id|addr
comma
r_int
id|vchan
)paren
(brace
r_if
c_cond
(paren
id|vchan
OG
l_int|1
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|addr
op_rshift
l_int|32
)paren
)paren
multiline_comment|/* Using a mask here would be cleaner */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* but this generates better code */
r_if
c_cond
(paren
id|vchan
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Set Bit 57 */
op_star
id|addr
op_or_assign
(paren
l_int|1UL
op_lshift
l_int|57
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Clear Bit 57 */
op_star
id|addr
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
l_int|57
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* C or C++ */
multiline_comment|/*&n; * Prototypes&n; */
r_int
id|snia_badaddr_val
c_func
(paren
r_volatile
r_void
op_star
id|addr
comma
r_int
id|len
comma
r_volatile
r_void
op_star
id|ptr
)paren
suffix:semicolon
id|nasid_t
id|snia_get_console_nasid
c_func
(paren
r_void
)paren
suffix:semicolon
id|nasid_t
id|snia_get_master_baseio_nasid
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_PCI_PCIIO_H */
eof
