multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_INVENT_H
DECL|macro|_ASM_IA64_SN_INVENT_H
mdefine_line|#define _ASM_IA64_SN_INVENT_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
multiline_comment|/*&n; * sys/sn/invent.h --  Kernel Hardware Inventory&n; *&n; * As the system boots, a list of recognized devices is assembled.&n; * This list can then be accessed through syssgi() by user-level programs&n; * so that they can learn about available peripherals and the system&squot;s&n; * hardware configuration.&n; *&n; * The data is organized into a linked list of structures that are composed&n; * of an inventory item class and a class-specific type.  Each instance may&n; * also specify a 32-bit &quot;state&quot; which might be size, readiness, or&n; * anything else that&squot;s relevant.&n; *&n; */
DECL|macro|major_t
mdefine_line|#define major_t int
DECL|macro|minor_t
mdefine_line|#define minor_t int
DECL|macro|app32_ptr_t
mdefine_line|#define app32_ptr_t unsigned long
DECL|macro|graph_vertex_place_t
mdefine_line|#define graph_vertex_place_t long
DECL|macro|GRAPH_VERTEX_NONE
mdefine_line|#define GRAPH_VERTEX_NONE ((devfs_handle_t)-1)
DECL|macro|GRAPH_EDGE_PLACE_NONE
mdefine_line|#define GRAPH_EDGE_PLACE_NONE ((graph_edge_place_t)0)
DECL|macro|GRAPH_INFO_PLACE_NONE
mdefine_line|#define GRAPH_INFO_PLACE_NONE ((graph_info_place_t)0)
DECL|macro|GRAPH_VERTEX_PLACE_NONE
mdefine_line|#define GRAPH_VERTEX_PLACE_NONE ((graph_vertex_place_t)0)
DECL|struct|inventory_s
r_typedef
r_struct
id|inventory_s
(brace
DECL|member|inv_next
r_struct
id|inventory_s
op_star
id|inv_next
suffix:semicolon
multiline_comment|/* next inventory record in list */
DECL|member|inv_class
r_int
id|inv_class
suffix:semicolon
multiline_comment|/* class of object */
DECL|member|inv_type
r_int
id|inv_type
suffix:semicolon
multiline_comment|/* class sub-type of object */
DECL|member|inv_controller
id|major_t
id|inv_controller
suffix:semicolon
multiline_comment|/* object major identifier */
DECL|member|inv_unit
id|minor_t
id|inv_unit
suffix:semicolon
multiline_comment|/* object minor identifier */
DECL|member|inv_state
r_int
id|inv_state
suffix:semicolon
multiline_comment|/* information specific to object or&n;&t;&t;&t;&t;&t;   class */
DECL|typedef|inventory_t
)brace
id|inventory_t
suffix:semicolon
DECL|struct|cpu_inv_s
r_typedef
r_struct
id|cpu_inv_s
(brace
DECL|member|cpuflavor
r_int
id|cpuflavor
suffix:semicolon
multiline_comment|/* differentiate processor */
DECL|member|cpufq
r_int
id|cpufq
suffix:semicolon
multiline_comment|/* cpu frequency */
DECL|member|sdsize
r_int
id|sdsize
suffix:semicolon
multiline_comment|/* secondary data cache size */
DECL|member|sdfreq
r_int
id|sdfreq
suffix:semicolon
multiline_comment|/* speed of the secondary cache */
DECL|typedef|cpu_inv_t
)brace
id|cpu_inv_t
suffix:semicolon
DECL|struct|diag_inv_s
r_typedef
r_struct
id|diag_inv_s
(brace
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|diagval
r_int
id|diagval
suffix:semicolon
DECL|member|physid
r_int
id|physid
suffix:semicolon
DECL|member|virtid
r_int
id|virtid
suffix:semicolon
DECL|typedef|diag_inv_t
)brace
id|diag_inv_t
suffix:semicolon
DECL|struct|router_inv_s
r_typedef
r_struct
id|router_inv_s
(brace
DECL|member|portmap
r_char
id|portmap
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* String indicating which ports int/ext */
DECL|member|type
r_char
id|type
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* String name: e.g. &quot;star&quot;, &quot;meta&quot;, etc. */
DECL|member|freq
r_int
id|freq
suffix:semicolon
multiline_comment|/* From hub */
DECL|member|rev
r_int
id|rev
suffix:semicolon
multiline_comment|/* From hub */
DECL|typedef|router_inv_t
)brace
id|router_inv_t
suffix:semicolon
multiline_comment|/*&n; * NOTE: This file is a central registry for inventory IDs for each&n; *       class of inventory object.  It is important to keep the central copy&n; *       of this file up-to-date with the work going on in various engineering&n; *       projects.  When making changes to this file in an engineering project&n; *       tree, please make those changes separately from any others and then&n; *       merge the changes to this file into the main line trees in order to&n; *       prevent other engineering projects from conflicting with your ID&n; *       allocations.&n; */
multiline_comment|/* Inventory Classes */
multiline_comment|/* when adding a new class, add also to classes[] in hinv.c */
DECL|macro|INV_PROCESSOR
mdefine_line|#define INV_PROCESSOR&t;1
DECL|macro|INV_DISK
mdefine_line|#define INV_DISK&t;2
DECL|macro|INV_MEMORY
mdefine_line|#define INV_MEMORY&t;3
DECL|macro|INV_SERIAL
mdefine_line|#define INV_SERIAL&t;4
DECL|macro|INV_PARALLEL
mdefine_line|#define INV_PARALLEL&t;5
DECL|macro|INV_TAPE
mdefine_line|#define INV_TAPE&t;6
DECL|macro|INV_GRAPHICS
mdefine_line|#define INV_GRAPHICS&t;7
DECL|macro|INV_NETWORK
mdefine_line|#define INV_NETWORK&t;8
DECL|macro|INV_SCSI
mdefine_line|#define INV_SCSI&t;9&t;/* SCSI devices other than disk and tape */
DECL|macro|INV_AUDIO
mdefine_line|#define INV_AUDIO&t;10
DECL|macro|INV_IOBD
mdefine_line|#define&t;INV_IOBD&t;11
DECL|macro|INV_VIDEO
mdefine_line|#define&t;INV_VIDEO&t;12
DECL|macro|INV_BUS
mdefine_line|#define&t;INV_BUS&t;&t;13
DECL|macro|INV_MISC
mdefine_line|#define&t;INV_MISC&t;14&t;/* miscellaneous: a catchall */
multiline_comment|/*** add post-5.2 classes here for backward compatibility ***/
DECL|macro|INV_COMPRESSION
mdefine_line|#define&t;INV_COMPRESSION&t;15
DECL|macro|INV_VSCSI
mdefine_line|#define&t;INV_VSCSI&t;16&t;/* SCSI devices on jag other than disk and tape */
DECL|macro|INV_DISPLAY
mdefine_line|#define&t;INV_DISPLAY     17
DECL|macro|INV_UNC_SCSILUN
mdefine_line|#define&t;INV_UNC_SCSILUN&t;18&t;/* Unconnected SCSI lun */
DECL|macro|INV_PCI
mdefine_line|#define&t;INV_PCI&t;&t;19&t;/* PCI Bus */
DECL|macro|INV_PCI_NO_DRV
mdefine_line|#define&t;INV_PCI_NO_DRV&t;20&t;/* PCI Bus without any driver */
DECL|macro|INV_PROM
mdefine_line|#define&t;INV_PROM&t;21&t;/* Different proms in the system */
DECL|macro|INV_IEEE1394
mdefine_line|#define INV_IEEE1394&t;22&t;/* IEEE1394 devices */
DECL|macro|INV_RPS
mdefine_line|#define INV_RPS&t;&t;23      /* redundant power source */
DECL|macro|INV_TPU
mdefine_line|#define INV_TPU&t;&t;24&t;/* Tensor Processing Unit */
DECL|macro|INV_FCNODE
mdefine_line|#define INV_FCNODE&t;25&t;/* Helper class for SCSI classes, not in classes[] */
DECL|macro|INV_USB
mdefine_line|#define INV_USB&t;&t;26&t;/* Universal Serial Bus */
DECL|macro|INV_1394NODE
mdefine_line|#define INV_1394NODE    27      /* helper class for 1394/SPB2 classes, not in classes[] */
multiline_comment|/* types for class processor */
DECL|macro|INV_CPUBOARD
mdefine_line|#define INV_CPUBOARD&t;1
DECL|macro|INV_CPUCHIP
mdefine_line|#define INV_CPUCHIP&t;2
DECL|macro|INV_FPUCHIP
mdefine_line|#define INV_FPUCHIP&t;3
DECL|macro|INV_CCSYNC
mdefine_line|#define INV_CCSYNC&t;4&t;/* CC Rev 2+ sync join counter */
multiline_comment|/* states for cpu and fpu chips are revision numbers */
multiline_comment|/* cpuboard states */
DECL|macro|INV_IP20BOARD
mdefine_line|#define INV_IP20BOARD   10
DECL|macro|INV_IP19BOARD
mdefine_line|#define INV_IP19BOARD   11
DECL|macro|INV_IP22BOARD
mdefine_line|#define INV_IP22BOARD   12
DECL|macro|INV_IP21BOARD
mdefine_line|#define INV_IP21BOARD&t;13
DECL|macro|INV_IP26BOARD
mdefine_line|#define INV_IP26BOARD&t;14
DECL|macro|INV_IP25BOARD
mdefine_line|#define INV_IP25BOARD&t;15
DECL|macro|INV_IP30BOARD
mdefine_line|#define INV_IP30BOARD&t;16
DECL|macro|INV_IP28BOARD
mdefine_line|#define INV_IP28BOARD&t;17
DECL|macro|INV_IP32BOARD
mdefine_line|#define INV_IP32BOARD&t;18
DECL|macro|INV_IP27BOARD
mdefine_line|#define INV_IP27BOARD&t;19
DECL|macro|INV_IPMHSIMBOARD
mdefine_line|#define INV_IPMHSIMBOARD 20
DECL|macro|INV_IP33BOARD
mdefine_line|#define INV_IP33BOARD&t;21
DECL|macro|INV_IP35BOARD
mdefine_line|#define INV_IP35BOARD&t;22
multiline_comment|/* types for class INV_IOBD */
DECL|macro|INV_EVIO
mdefine_line|#define INV_EVIO&t;2&t;/* EVEREST I/O board */
DECL|macro|INV_O200IO
mdefine_line|#define INV_O200IO&t;3&t;/* Origin 200 base I/O */
multiline_comment|/* IO board types for origin2000  for class INV_IOBD*/
DECL|macro|INV_O2000BASEIO
mdefine_line|#define INV_O2000BASEIO&t;0x21&t;
DECL|macro|INV_O2000MSCSI
mdefine_line|#define INV_O2000MSCSI&t;0x22&t;
DECL|macro|INV_O2000MENET
mdefine_line|#define INV_O2000MENET&t;0x23
DECL|macro|INV_O2000HIPPI
mdefine_line|#define INV_O2000HIPPI&t;0x24
DECL|macro|INV_O2000GFX
mdefine_line|#define INV_O2000GFX&t;0x25&t;
DECL|macro|INV_O2000HAROLD
mdefine_line|#define INV_O2000HAROLD 0x26
DECL|macro|INV_O2000VME
mdefine_line|#define INV_O2000VME&t;0x27
DECL|macro|INV_O2000MIO
mdefine_line|#define INV_O2000MIO&t;0x28
DECL|macro|INV_O2000FC
mdefine_line|#define INV_O2000FC&t;0x29
DECL|macro|INV_O2000LINC
mdefine_line|#define INV_O2000LINC&t;0x2a
DECL|macro|INV_PCIADAP
mdefine_line|#define INV_PCIADAP&t;4
multiline_comment|/* states for class INV_IOBD type INV_EVERESTIO -- value of eb_type field */
DECL|macro|INV_IO4_REV1
mdefine_line|#define INV_IO4_REV1&t;0x21&t;
multiline_comment|/* types for class disk */
multiline_comment|/* NB: types MUST be unique within a class.&n;   Please check this if adding new types. */
DECL|macro|INV_SCSICONTROL
mdefine_line|#define INV_SCSICONTROL&t;1
DECL|macro|INV_SCSIDRIVE
mdefine_line|#define INV_SCSIDRIVE&t;2
DECL|macro|INV_SCSIFLOPPY
mdefine_line|#define INV_SCSIFLOPPY&t;5&t;/* also cdroms, optical disks, etc. */
DECL|macro|INV_JAGUAR
mdefine_line|#define INV_JAGUAR&t;16&t;/* Interphase Jaguar */
DECL|macro|INV_VSCSIDRIVE
mdefine_line|#define INV_VSCSIDRIVE&t;17&t;/* Disk connected to Jaguar */
DECL|macro|INV_GIO_SCSICONTROL
mdefine_line|#define INV_GIO_SCSICONTROL 18&t;/* optional GIO SCSI controller */
DECL|macro|INV_SCSIRAID
mdefine_line|#define INV_SCSIRAID&t;19&t;/* SCSI attached RAID */
DECL|macro|INV_XLVGEN
mdefine_line|#define INV_XLVGEN      20&t;/* Generic XLV disk device */
DECL|macro|INV_PCCARD
mdefine_line|#define INV_PCCARD&t;21&t;/* PC-card (PCMCIA) devices */
DECL|macro|INV_PCI_SCSICONTROL
mdefine_line|#define INV_PCI_SCSICONTROL&t;22   /* optional PCI SCSI controller */
multiline_comment|/* states for INV_SCSICONTROL disk type; indicate which chip rev;&n; * for 93A and B, unit field has microcode rev. */
DECL|macro|INV_WD93
mdefine_line|#define INV_WD93&t;0&t;/* WD 33C93  */
DECL|macro|INV_WD93A
mdefine_line|#define INV_WD93A&t;1&t;/* WD 33C93A */
DECL|macro|INV_WD93B
mdefine_line|#define INV_WD93B&t;2&t;/* WD 33C93B */
DECL|macro|INV_WD95A
mdefine_line|#define INV_WD95A&t;3&t;/* WD 33C95A */
DECL|macro|INV_SCIP95
mdefine_line|#define INV_SCIP95&t;4       /* SCIP with a WD 33C95A */
DECL|macro|INV_ADP7880
mdefine_line|#define INV_ADP7880&t;5&t;/* Adaptec 7880 (single channel) */
DECL|macro|INV_QL_REV1
mdefine_line|#define INV_QL_REV1     6       /* qlogic 1040  */
DECL|macro|INV_QL_REV2
mdefine_line|#define INV_QL_REV2     7       /* qlogic 1040A */
DECL|macro|INV_QL_REV2_4
mdefine_line|#define INV_QL_REV2_4   8       /* qlogic 1040A rev 4 */
DECL|macro|INV_QL_REV3
mdefine_line|#define INV_QL_REV3     9       /* qlogic 1040B */
DECL|macro|INV_FCADP
mdefine_line|#define INV_FCADP&t;10&t;/* Adaptec Emerald Fibrechannel */
DECL|macro|INV_QL_REV4
mdefine_line|#define INV_QL_REV4     11      /* qlogic 1040B rev 2 */
DECL|macro|INV_QL
mdefine_line|#define INV_QL&t;&t;12&t;/* Unknown QL version */&t;
DECL|macro|INV_QL_1240
mdefine_line|#define INV_QL_1240     13      /* qlogic 1240 */
DECL|macro|INV_QL_1080
mdefine_line|#define INV_QL_1080     14      /* qlogic 1080 */
DECL|macro|INV_QL_1280
mdefine_line|#define INV_QL_1280     15      /* qlogic 1280 */
DECL|macro|INV_QL_10160
mdefine_line|#define INV_QL_10160    16      /* qlogic 10160 */
DECL|macro|INV_QL_12160
mdefine_line|#define INV_QL_12160    17      /* qlogic 12160 */
DECL|macro|INV_QL_2100
mdefine_line|#define INV_QL_2100&t;18&t;/* qLogic 2100 Fibrechannel */
DECL|macro|INV_QL_2200
mdefine_line|#define INV_QL_2200&t;19&t;/* qLogic 2200 Fibrechannel */
DECL|macro|INV_PR_HIO_D
mdefine_line|#define INV_PR_HIO_D&t;20&t;/* Prisa HIO Dual channel */
DECL|macro|INV_PR_PCI64_D
mdefine_line|#define INV_PR_PCI64_D&t;21&t;/* Prisa PCI-64 Dual channel */
DECL|macro|INV_QL_2200A
mdefine_line|#define INV_QL_2200A&t;22&t;/* qLogic 2200A Fibrechannel */
DECL|macro|INV_SBP2
mdefine_line|#define INV_SBP2        23      /* SBP2 protocol over OHCI on 1394 */
DECL|macro|INV_QL_2300
mdefine_line|#define INV_QL_2300&t;24&t;/* qLogic 2300 Fibrechannel */
multiline_comment|/* states for INV_SCSIDRIVE type of class disk */
DECL|macro|INV_RAID5_LUN
mdefine_line|#define INV_RAID5_LUN&t;0x100
DECL|macro|INV_PRIMARY
mdefine_line|#define INV_PRIMARY&t;0x200&t;/* primary path */
DECL|macro|INV_ALTERNATE
mdefine_line|#define INV_ALTERNATE&t;0x400&t;/* alternate path */
DECL|macro|INV_FAILED
mdefine_line|#define INV_FAILED&t;0x800&t;/* path has failed */
DECL|macro|INV_XVMVOL
mdefine_line|#define INV_XVMVOL&t;0x1000&t;/* disk is managed by XVM */
multiline_comment|/* states for INV_SCSIFLOPPY type of class disk */
DECL|macro|INV_TEAC_FLOPPY
mdefine_line|#define INV_TEAC_FLOPPY 1       /* TEAC 3 1/2 inch floppy drive */
DECL|macro|INV_INSITE_FLOPPY
mdefine_line|#define INV_INSITE_FLOPPY 2     /* INSITE, IOMEGA  Io20S, SyQuest floppy drives */
multiline_comment|/* END OF CLASS DISK TYPES */
multiline_comment|/* types for class memory */
multiline_comment|/* NB. the states for class memory are sizes in bytes */
DECL|macro|INV_MAIN
mdefine_line|#define INV_MAIN&t;1
DECL|macro|INV_DCACHE
mdefine_line|#define INV_DCACHE&t;3
DECL|macro|INV_ICACHE
mdefine_line|#define INV_ICACHE&t;4
DECL|macro|INV_WBUFFER
mdefine_line|#define INV_WBUFFER&t;5
DECL|macro|INV_SDCACHE
mdefine_line|#define INV_SDCACHE&t;6
DECL|macro|INV_SICACHE
mdefine_line|#define INV_SICACHE&t;7
DECL|macro|INV_SIDCACHE
mdefine_line|#define INV_SIDCACHE&t;8
DECL|macro|INV_MAIN_MB
mdefine_line|#define INV_MAIN_MB&t;9
DECL|macro|INV_HUBSPC
mdefine_line|#define INV_HUBSPC      10      /* HUBSPC */
DECL|macro|INV_TIDCACHE
mdefine_line|#define INV_TIDCACHE&t;11
multiline_comment|/* types for class serial */
DECL|macro|INV_CDSIO
mdefine_line|#define INV_CDSIO&t;1&t;/* Central Data serial board */
DECL|macro|INV_T3270
mdefine_line|#define INV_T3270&t;2&t;/* T3270 emulation */
DECL|macro|INV_GSE
mdefine_line|#define INV_GSE&t;&t;3&t;/* SpectraGraphics Gerbil coax cable */
DECL|macro|INV_SI
mdefine_line|#define INV_SI&t;&t;4&t;/* SNA SDLC controller */
DECL|macro|INV_M333X25
mdefine_line|#define&t;INV_M333X25 &t;6&t;/* X.25 controller */
DECL|macro|INV_CDSIO_E
mdefine_line|#define INV_CDSIO_E&t;7&t;/* Central Data serial board on E space */
DECL|macro|INV_ONBOARD
mdefine_line|#define INV_ONBOARD&t;8&t;/* Serial ports per CPU board */
DECL|macro|INV_EPC_SERIAL
mdefine_line|#define INV_EPC_SERIAL&t;9&t;/* EVEREST I/O EPC serial port */
DECL|macro|INV_ICA
mdefine_line|#define INV_ICA&t;&t;10&t;/* IRIS (IBM) Channel Adapter card */
DECL|macro|INV_VSC
mdefine_line|#define INV_VSC&t;&t;11&t;/* SBE VME Synch Comm board */
DECL|macro|INV_ISC
mdefine_line|#define INV_ISC&t;&t;12&t;/* SBE ISA Synch Comm board */
DECL|macro|INV_GSC
mdefine_line|#define INV_GSC&t;&t;13&t;/* SGI GIO Synch Comm board */
DECL|macro|INV_ASO_SERIAL
mdefine_line|#define INV_ASO_SERIAL&t;14&t;/* serial portion of SGI ASO board */
DECL|macro|INV_PSC
mdefine_line|#define INV_PSC&t;&t;15&t;/* SBE PCI Synch Comm board */
DECL|macro|INV_IOC3_DMA
mdefine_line|#define INV_IOC3_DMA&t;16&t;/* DMA mode IOC3 serial */
DECL|macro|INV_IOC3_PIO
mdefine_line|#define INV_IOC3_PIO&t;17&t;/* PIO mode IOC3 serial */
DECL|macro|INV_INVISIBLE
mdefine_line|#define INV_INVISIBLE&t;18&t;/* invisible inventory entry for kernel use */
DECL|macro|INV_ISA_DMA
mdefine_line|#define INV_ISA_DMA&t;19&t;/* DMA mode ISA serial -- O2 */
multiline_comment|/* types for class parallel */
DECL|macro|INV_GPIB
mdefine_line|#define INV_GPIB&t;2&t;/* National Instrument GPIB board */
DECL|macro|INV_GPIB_E
mdefine_line|#define INV_GPIB_E&t;3&t;/* National Instrument GPIB board on E space*/
DECL|macro|INV_EPC_PLP
mdefine_line|#define INV_EPC_PLP&t;4&t;/* EVEREST I/O EPC Parallel Port */
DECL|macro|INV_ONBOARD_PLP
mdefine_line|#define INV_ONBOARD_PLP&t;5&t;/* Integral parallel port,&n;&t;&t;&t;&t;      state = 0 -&gt; output only&n;&t;&t;&t;&t;      state = 1 -&gt; bi-directional */
DECL|macro|INV_EPP_ECP_PLP
mdefine_line|#define INV_EPP_ECP_PLP&t;6&t;/* Integral EPP/ECP parallel port */
DECL|macro|INV_EPP_PFD
mdefine_line|#define INV_EPP_PFD&t;7&t;/* External EPP parallel peripheral */
multiline_comment|/* types for class tape */
DECL|macro|INV_SCSIQIC
mdefine_line|#define INV_SCSIQIC&t;1&t;/* Any SCSI tape, not just QIC{24,150}... */
DECL|macro|INV_VSCSITAPE
mdefine_line|#define INV_VSCSITAPE&t;4&t;/* SCSI tape connected to Jaguar */
multiline_comment|/* sub types for type INV_SCSIQIC and INV_VSCSITAPE (in state) */
DECL|macro|TPUNKNOWN
mdefine_line|#define TPUNKNOWN&t;0&t;/* type not known */
DECL|macro|TPQIC24
mdefine_line|#define TPQIC24&t;&t;1&t;/* QIC24 1/4&quot; cartridge */
DECL|macro|TPDAT
mdefine_line|#define TPDAT&t;&t;2&t;/* 4mm Digital Audio Tape cartridge */
DECL|macro|TPQIC150
mdefine_line|#define TPQIC150&t;3&t;/* QIC150 1/4&quot; cartridge */
DECL|macro|TP9TRACK
mdefine_line|#define TP9TRACK&t;4&t;/* 9 track reel */
DECL|macro|TP8MM_8200
mdefine_line|#define TP8MM_8200&t;5&t;/* 8 mm video tape cartridge */
DECL|macro|TP8MM_8500
mdefine_line|#define TP8MM_8500&t;6&t;/* 8 mm video tape cartridge */
DECL|macro|TPQIC1000
mdefine_line|#define TPQIC1000&t;7&t;/* QIC1000 1/4&quot; cartridge */
DECL|macro|TPQIC1350
mdefine_line|#define TPQIC1350&t;8&t;/* QIC1350 1/4&quot; cartridge */
DECL|macro|TP3480
mdefine_line|#define TP3480&t;&t;9&t;/* 3480 compatible cartridge */
DECL|macro|TPDLT
mdefine_line|#define TPDLT&t;&t;10&t;/* DEC Digital Linear Tape cartridge */
DECL|macro|TPD2
mdefine_line|#define TPD2&t;&t;11&t;/* D2 tape cartridge */
DECL|macro|TPDLTSTACKER
mdefine_line|#define TPDLTSTACKER&t;12&t;/* DEC Digital Linear Tape stacker */
DECL|macro|TPNTP
mdefine_line|#define TPNTP&t;&t;13&t;/* IBM Magstar 3590 Tape Device cartridge */
DECL|macro|TPNTPSTACKER
mdefine_line|#define TPNTPSTACKER&t;14&t;/* IBM Magstar 3590 Tape Device stacker */
DECL|macro|TPSTK9490
mdefine_line|#define TPSTK9490       15      /* StorageTeK 9490 */
DECL|macro|TPSTKSD3
mdefine_line|#define TPSTKSD3        16      /* StorageTeK SD3 */
DECL|macro|TPGY10
mdefine_line|#define TPGY10&t;        17      /* Sony GY-10  */
DECL|macro|TP8MM_8900
mdefine_line|#define TP8MM_8900&t;18&t;/* 8 mm (AME) tape cartridge */
DECL|macro|TPMGSTRMP
mdefine_line|#define TPMGSTRMP       19      /* IBM Magster MP 3570 cartridge */
DECL|macro|TPMGSTRMPSTCKR
mdefine_line|#define TPMGSTRMPSTCKR  20      /* IBM Magstar MP stacker */
DECL|macro|TPSTK4791
mdefine_line|#define TPSTK4791       21      /* StorageTek 4791 */
DECL|macro|TPSTK4781
mdefine_line|#define TPSTK4781       22      /* StorageTek 4781 */
DECL|macro|TPFUJDIANA1
mdefine_line|#define TPFUJDIANA1     23      /* Fujitsu Diana-1 (M1016/M1017) */
DECL|macro|TPFUJDIANA2
mdefine_line|#define TPFUJDIANA2     24      /* Fujitsu Diana-2 (M2483) */
DECL|macro|TPFUJDIANA3
mdefine_line|#define TPFUJDIANA3     25      /* Fujitsu Diana-3 (M2488) */
DECL|macro|TP8MM_AIT
mdefine_line|#define TP8MM_AIT&t;26&t;/* Sony AIT format tape */
DECL|macro|TPTD3600
mdefine_line|#define TPTD3600        27      /* Philips TD3600  */
DECL|macro|TPTD3600STCKR
mdefine_line|#define TPTD3600STCKR   28      /* Philips TD3600  stacker */
DECL|macro|TPNCTP
mdefine_line|#define TPNCTP          29      /* Philips NCTP */
DECL|macro|TPGY2120
mdefine_line|#define TPGY2120        30      /* Sony GY-2120 (replaces GY-10)  */
DECL|macro|TPOVL490E
mdefine_line|#define TPOVL490E       31      /* Overland Data L490E (3490E compatible) */
DECL|macro|TPSTK9840
mdefine_line|#define TPSTK9840       32      /* StorageTeK 9840 (aka Eagle) */
multiline_comment|/* Diagnostics inventory */
DECL|macro|INV_CPUDIAGVAL
mdefine_line|#define INV_CPUDIAGVAL  70
multiline_comment|/*&n; *  GFX invent is a subset of gfxinfo&n; */
multiline_comment|/* types for class graphics */
DECL|macro|INV_GR1BOARD
mdefine_line|#define INV_GR1BOARD&t;1&t;/* GR1 (Eclipse) graphics */
DECL|macro|INV_GR1BP
mdefine_line|#define INV_GR1BP&t;2&t;/* OBSOLETE - use INV_GR1BIT24 instead */
DECL|macro|INV_GR1ZBUFFER
mdefine_line|#define INV_GR1ZBUFFER&t;3&t;/* OBSOLETE - use INV_GR1ZBUF24 instead */
DECL|macro|INV_GRODEV
mdefine_line|#define INV_GRODEV&t;4&t;/* Clover1 graphics */
DECL|macro|INV_GMDEV
mdefine_line|#define INV_GMDEV&t;5&t;/* GT graphics */
DECL|macro|INV_CG2
mdefine_line|#define INV_CG2&t;&t;6&t;/* CG2 composite video/genlock board */
DECL|macro|INV_VMUXBOARD
mdefine_line|#define INV_VMUXBOARD&t;7&t;/* VMUX video mux board */
DECL|macro|INV_VGX
mdefine_line|#define&t;INV_VGX&t;&t;8&t;/* VGX (PowerVision) graphics */
DECL|macro|INV_VGXT
mdefine_line|#define&t;INV_VGXT&t;9&t;/* VGXT (PowerVision) graphics with IMP5s. */
DECL|macro|INV_LIGHT
mdefine_line|#define&t;INV_LIGHT&t;10&t;/* LIGHT graphics */
DECL|macro|INV_GR2
mdefine_line|#define INV_GR2&t;&t;11&t;/* EXPRESS graphics */
DECL|macro|INV_RE
mdefine_line|#define INV_RE&t;&t;12&t;/* RealityEngine graphics */
DECL|macro|INV_VTX
mdefine_line|#define INV_VTX&t;&t;13&t;/* RealityEngine graphics - VTX variant */
DECL|macro|INV_NEWPORT
mdefine_line|#define INV_NEWPORT&t;14&t;/* Newport graphics */
DECL|macro|INV_MGRAS
mdefine_line|#define INV_MGRAS&t;15&t;/* Mardigras graphics */
DECL|macro|INV_IR
mdefine_line|#define INV_IR&t;&t;16&t;/* InfiniteReality graphics */
DECL|macro|INV_CRIME
mdefine_line|#define INV_CRIME&t;17&t;/* Moosehead on board CRIME graphics */
DECL|macro|INV_IR2
mdefine_line|#define INV_IR2&t;&t;18&t;/* InfiniteReality2 graphics */
DECL|macro|INV_IR2LITE
mdefine_line|#define INV_IR2LITE&t;19&t;/* Reality graphics */
DECL|macro|INV_IR2E
mdefine_line|#define INV_IR2E&t;20&t;/* InfiniteReality2e graphics */
DECL|macro|INV_ODSY
mdefine_line|#define INV_ODSY        21      /* Odyssey graphics */
DECL|macro|INV_IR3
mdefine_line|#define INV_IR3&t;&t;22&t;/* InfiniteReality3 graphics */
multiline_comment|/* states for graphics class GR1 */
DECL|macro|INV_GR1REMASK
mdefine_line|#define INV_GR1REMASK&t;0x7&t;/* RE version */
DECL|macro|INV_GR1REUNK
mdefine_line|#define INV_GR1REUNK&t;0x0&t;/* RE version unknown */
DECL|macro|INV_GR1RE1
mdefine_line|#define INV_GR1RE1&t;0x1&t;/* RE1 */
DECL|macro|INV_GR1RE2
mdefine_line|#define INV_GR1RE2&t;0x2&t;/* RE2 */
DECL|macro|INV_GR1BUSMASK
mdefine_line|#define INV_GR1BUSMASK&t;0x38&t;/* GR1 bus architecture */
DECL|macro|INV_GR1PB
mdefine_line|#define INV_GR1PB&t;0x00&t;/* Eclipse private bus */
DECL|macro|INV_GR1PBVME
mdefine_line|#define INV_GR1PBVME&t;0x08&t;/* VGR2 board VME and private bus interfaces */
DECL|macro|INV_GR1TURBO
mdefine_line|#define INV_GR1TURBO&t;0x40&t;/* has turbo option */
DECL|macro|INV_GR1BIT24
mdefine_line|#define INV_GR1BIT24  &t;0x80    /* has bitplane option */
DECL|macro|INV_GR1ZBUF24
mdefine_line|#define INV_GR1ZBUF24 &t;0x100   /* has z-buffer option */
DECL|macro|INV_GR1SMALLMON
mdefine_line|#define INV_GR1SMALLMON 0x200   /* using 14&quot; monitor */
DECL|macro|INV_GR1SMALLMAP
mdefine_line|#define INV_GR1SMALLMAP 0x400   /* has 256 entry color map */
DECL|macro|INV_GR1AUX4
mdefine_line|#define INV_GR1AUX4 &t;0x800   /* has AUX/WID plane option */
multiline_comment|/* states for graphics class GR2 */
multiline_comment|/* bitmasks */
DECL|macro|INV_GR2_Z
mdefine_line|#define INV_GR2_Z&t;0x1&t;/* has z-buffer option */
DECL|macro|INV_GR2_24
mdefine_line|#define INV_GR2_24&t;0x2&t;/* has bitplane option */
DECL|macro|INV_GR2_4GE
mdefine_line|#define INV_GR2_4GE     0x4     /* has 4 GEs */
DECL|macro|INV_GR2_1GE
mdefine_line|#define INV_GR2_1GE&t;0x8&t;/* has 1 GEs */
DECL|macro|INV_GR2_2GE
mdefine_line|#define INV_GR2_2GE&t;0x10&t;/* has 2 GEs */
DECL|macro|INV_GR2_8GE
mdefine_line|#define INV_GR2_8GE&t;0x20&t;/* has 8 GEs */
DECL|macro|INV_GR2_GR3
mdefine_line|#define INV_GR2_GR3&t;0x40&t;/* board GR3 */
DECL|macro|INV_GR2_GU1
mdefine_line|#define INV_GR2_GU1&t;0x80&t;/* board GU1 */
DECL|macro|INV_GR2_INDY
mdefine_line|#define INV_GR2_INDY    0x100   /* board GR3 on Indy*/
DECL|macro|INV_GR2_GR5
mdefine_line|#define INV_GR2_GR5&t;0x200&t;/* board GR3 with 4 GEs, hinv prints GR5-XZ */
multiline_comment|/* supported configurations */
DECL|macro|INV_GR2_XS
mdefine_line|#define INV_GR2_XS&t;0x0     /* GR2-XS */
DECL|macro|INV_GR2_XSZ
mdefine_line|#define INV_GR2_XSZ&t;0x1     /* GR2-XS with z-buffer */
DECL|macro|INV_GR2_XS24
mdefine_line|#define INV_GR2_XS24&t;0x2     /* GR2-XS24 */
DECL|macro|INV_GR2_XS24Z
mdefine_line|#define INV_GR2_XS24Z&t;0x3     /* GR2-XS24 with z-buffer */
DECL|macro|INV_GR2_XSM
mdefine_line|#define INV_GR2_XSM&t;0x4     /* GR2-XSM */
DECL|macro|INV_GR2_ELAN
mdefine_line|#define INV_GR2_ELAN&t;0x7&t;/* GR2-Elan */
DECL|macro|INV_GR2_XZ
mdefine_line|#define&t;INV_GR2_XZ&t;0x13&t;/* GR2-XZ */
DECL|macro|INV_GR3_XSM
mdefine_line|#define&t;INV_GR3_XSM&t;0x44&t;/* GR3-XSM */
DECL|macro|INV_GR3_ELAN
mdefine_line|#define&t;INV_GR3_ELAN&t;0x47&t;/* GR3-Elan */
DECL|macro|INV_GU1_EXTREME
mdefine_line|#define&t;INV_GU1_EXTREME&t;0xa3&t;/* GU1-Extreme */
multiline_comment|/* States for graphics class NEWPORT */
DECL|macro|INV_NEWPORT_XL
mdefine_line|#define&t;INV_NEWPORT_XL&t;0x01&t;/* Indigo2 XL model */
DECL|macro|INV_NEWPORT_24
mdefine_line|#define INV_NEWPORT_24&t;0x02&t;/* board has 24 bitplanes */
DECL|macro|INV_NEWTON
mdefine_line|#define INV_NEWTON      0x04    /* Triton SUBGR tagging */
multiline_comment|/* States for graphics class MGRAS */
DECL|macro|INV_MGRAS_ARCHS
mdefine_line|#define INV_MGRAS_ARCHS 0xff000000      /* architectures */
DECL|macro|INV_MGRAS_HQ3
mdefine_line|#define INV_MGRAS_HQ3   0x00000000   /*impact*/
DECL|macro|INV_MGRAS_HQ4
mdefine_line|#define INV_MGRAS_HQ4&t;0x01000000   /*gamera*/
DECL|macro|INV_MGRAS_MOT
mdefine_line|#define INV_MGRAS_MOT   0x02000000   /*mothra*/
DECL|macro|INV_MGRAS_GES
mdefine_line|#define INV_MGRAS_GES&t;0x00ff0000&t;/* number of GEs */
DECL|macro|INV_MGRAS_1GE
mdefine_line|#define INV_MGRAS_1GE&t;0x00010000
DECL|macro|INV_MGRAS_2GE
mdefine_line|#define INV_MGRAS_2GE&t;0x00020000
DECL|macro|INV_MGRAS_RES
mdefine_line|#define INV_MGRAS_RES&t;0x0000ff00&t;/* number of REs */
DECL|macro|INV_MGRAS_1RE
mdefine_line|#define INV_MGRAS_1RE&t;0x00000100
DECL|macro|INV_MGRAS_2RE
mdefine_line|#define INV_MGRAS_2RE&t;0x00000200
DECL|macro|INV_MGRAS_TRS
mdefine_line|#define INV_MGRAS_TRS&t;0x000000ff&t;/* number of TRAMs */
DECL|macro|INV_MGRAS_0TR
mdefine_line|#define INV_MGRAS_0TR&t;0x00000000
DECL|macro|INV_MGRAS_1TR
mdefine_line|#define INV_MGRAS_1TR&t;0x00000001
DECL|macro|INV_MGRAS_2TR
mdefine_line|#define INV_MGRAS_2TR&t;0x00000002
multiline_comment|/* States for graphics class CRIME */
DECL|macro|INV_CRM_BASE
mdefine_line|#define INV_CRM_BASE    0x01            /* Moosehead basic model */
multiline_comment|/* States for graphics class ODSY */
DECL|macro|INV_ODSY_ARCHS
mdefine_line|#define INV_ODSY_ARCHS      0xff000000 /* architectures */
DECL|macro|INV_ODSY_REVA_ARCH
mdefine_line|#define INV_ODSY_REVA_ARCH  0x01000000 /* Buzz Rev A */
DECL|macro|INV_ODSY_REVB_ARCH
mdefine_line|#define INV_ODSY_REVB_ARCH  0x02000000 /* Buzz Rev B */
DECL|macro|INV_ODSY_MEMCFG
mdefine_line|#define INV_ODSY_MEMCFG     0x00ff0000 /* memory configs */
DECL|macro|INV_ODSY_MEMCFG_32
mdefine_line|#define INV_ODSY_MEMCFG_32  0x00010000 /* 32MB memory */
DECL|macro|INV_ODSY_MEMCFG_64
mdefine_line|#define INV_ODSY_MEMCFG_64  0x00020000 /* 64MB memory */
DECL|macro|INV_ODSY_MEMCFG_128
mdefine_line|#define INV_ODSY_MEMCFG_128 0x00030000 /* 128MB memory */
DECL|macro|INV_ODSY_MEMCFG_256
mdefine_line|#define INV_ODSY_MEMCFG_256 0x00040000 /* 256MB memory */
DECL|macro|INV_ODSY_MEMCFG_512
mdefine_line|#define INV_ODSY_MEMCFG_512 0x00050000 /* 512MB memory */
multiline_comment|/* types for class network */
DECL|macro|INV_NET_ETHER
mdefine_line|#define INV_NET_ETHER&t;&t;0&t;/* 10Mb Ethernet */
DECL|macro|INV_NET_HYPER
mdefine_line|#define INV_NET_HYPER&t;&t;1&t;/* HyperNet */
DECL|macro|INV_NET_CRAYIOS
mdefine_line|#define&t;INV_NET_CRAYIOS&t;&t;2&t;/* Cray Input/Ouput Subsystem */
DECL|macro|INV_NET_FDDI
mdefine_line|#define&t;INV_NET_FDDI&t;&t;3&t;/* FDDI */
DECL|macro|INV_NET_TOKEN
mdefine_line|#define INV_NET_TOKEN&t;&t;4&t;/* 16/4 Token Ring */
DECL|macro|INV_NET_HIPPI
mdefine_line|#define INV_NET_HIPPI&t;&t;5&t;/* HIPPI */
DECL|macro|INV_NET_ATM
mdefine_line|#define INV_NET_ATM&t;&t;6&t;/* ATM */
DECL|macro|INV_NET_ISDN_BRI
mdefine_line|#define INV_NET_ISDN_BRI&t;7&t;/* ISDN */
DECL|macro|INV_NET_ISDN_PRI
mdefine_line|#define INV_NET_ISDN_PRI&t;8&t;/* PRI ISDN */
DECL|macro|INV_NET_HIPPIS
mdefine_line|#define INV_NET_HIPPIS&t;&t;9&t;/* HIPPI-Serial */
DECL|macro|INV_NET_GSN
mdefine_line|#define&t;INV_NET_GSN&t;&t;10&t;/* GSN (aka HIPPI-6400) */
DECL|macro|INV_NET_MYRINET
mdefine_line|#define INV_NET_MYRINET&t;&t;11&t;/* Myricom PCI network */
multiline_comment|/* controllers for network types, unique within class network */
DECL|macro|INV_ETHER_EC
mdefine_line|#define INV_ETHER_EC&t;0&t;/* IP6 integral controller */
DECL|macro|INV_ETHER_ENP
mdefine_line|#define INV_ETHER_ENP&t;1&t;/* CMC board */
DECL|macro|INV_ETHER_ET
mdefine_line|#define INV_ETHER_ET&t;2&t;/* IP5 integral controller */
DECL|macro|INV_HYPER_HY
mdefine_line|#define INV_HYPER_HY&t;3&t;/* HyperNet controller */
DECL|macro|INV_CRAYIOS_CFEI3
mdefine_line|#define&t;INV_CRAYIOS_CFEI3 4&t;/* Cray Front End Interface, v3 */
DECL|macro|INV_FDDI_IMF
mdefine_line|#define&t;INV_FDDI_IMF&t;5&t;/* Interphase/Martin 3211 FDDI */
DECL|macro|INV_ETHER_EGL
mdefine_line|#define INV_ETHER_EGL&t;6&t;/* Interphase V/4207 Eagle */
DECL|macro|INV_ETHER_FXP
mdefine_line|#define INV_ETHER_FXP&t;7&t;/* CMC C/130 FXP */
DECL|macro|INV_FDDI_IPG
mdefine_line|#define INV_FDDI_IPG&t;8&t;/* Interphase/SGI 4211 Peregrine FDDI */
DECL|macro|INV_TOKEN_FV
mdefine_line|#define INV_TOKEN_FV&t;9&t;/* Formation fv1600 Token-Ring board */
DECL|macro|INV_FDDI_XPI
mdefine_line|#define INV_FDDI_XPI&t;10&t;/* XPI GIO bus FDDI */
DECL|macro|INV_TOKEN_GTR
mdefine_line|#define INV_TOKEN_GTR&t;11&t;/* GTR GIO bus TokenRing */
DECL|macro|INV_ETHER_GIO
mdefine_line|#define INV_ETHER_GIO&t;12&t;/* IP12/20 optional GIO ethernet controller */
DECL|macro|INV_ETHER_EE
mdefine_line|#define INV_ETHER_EE&t;13&t;/* Everest IO4 EPC SEEQ/EDLC */
DECL|macro|INV_HIO_HIPPI
mdefine_line|#define INV_HIO_HIPPI&t;14&t;/* HIO HIPPI for Challenge/Onyx */
DECL|macro|INV_ATM_GIO64
mdefine_line|#define INV_ATM_GIO64&t;15&t;/* ATM OC-3c Mez card */
DECL|macro|INV_ETHER_EP
mdefine_line|#define INV_ETHER_EP&t;16&t;/* 8-port E-Plex Ethernet */
DECL|macro|INV_ISDN_SM
mdefine_line|#define INV_ISDN_SM&t;17&t;/* Siemens PEB 2085 */
DECL|macro|INV_TOKEN_MTR
mdefine_line|#define INV_TOKEN_MTR&t;18&t;/* EISA TokenRing */
DECL|macro|INV_ETHER_EF
mdefine_line|#define INV_ETHER_EF&t;19&t;/* IOC3 Fast Ethernet */
DECL|macro|INV_ISDN_48XP
mdefine_line|#define INV_ISDN_48XP&t;20&t;/* Xircom PRI-48XP */
DECL|macro|INV_FDDI_RNS
mdefine_line|#define INV_FDDI_RNS&t;21&t;/* Rockwell Network Systems FDDI */
DECL|macro|INV_HIPPIS_XTK
mdefine_line|#define INV_HIPPIS_XTK&t;22&t;/* Xtalk HIPPI-Serial */
DECL|macro|INV_ATM_QUADOC3
mdefine_line|#define INV_ATM_QUADOC3&t;23&t;/* Xtalk Quad OC-3c ATM interface */
DECL|macro|INV_TOKEN_MTRPCI
mdefine_line|#define INV_TOKEN_MTRPCI 24     /* PCI TokenRing */
DECL|macro|INV_ETHER_ECF
mdefine_line|#define INV_ETHER_ECF&t;25&t;/* PCI Fast Ethernet */
DECL|macro|INV_GFE
mdefine_line|#define INV_GFE&t;&t;26&t;/* GIO Fast Ethernet */
DECL|macro|INV_VFE
mdefine_line|#define INV_VFE&t;&t;27&t;/* VME Fast Ethernet */
DECL|macro|INV_ETHER_GE
mdefine_line|#define&t;INV_ETHER_GE&t;28&t;/* Gigabit Ethernet */
DECL|macro|INV_ETHER_EFP
mdefine_line|#define&t;INV_ETHER_EFP&t;INV_ETHER_EF&t;/* unused (same as IOC3 Fast Ethernet) */
DECL|macro|INV_GSN_XTK1
mdefine_line|#define INV_GSN_XTK1&t;29&t;/* single xtalk version of GSN */
DECL|macro|INV_GSN_XTK2
mdefine_line|#define INV_GSN_XTK2&t;30&t;/* dual xtalk version of GSN */
DECL|macro|INV_FORE_HE
mdefine_line|#define INV_FORE_HE&t;31&t;/* FORE HE ATM Card */
DECL|macro|INV_FORE_PCA
mdefine_line|#define INV_FORE_PCA&t;32&t;/* FORE PCA ATM Card */
DECL|macro|INV_FORE_VMA
mdefine_line|#define INV_FORE_VMA    33      /* FORE VMA ATM Card */
DECL|macro|INV_FORE_ESA
mdefine_line|#define INV_FORE_ESA    34      /* FORE ESA ATM Card */
DECL|macro|INV_FORE_GIA
mdefine_line|#define INV_FORE_GIA    35      /* FORE GIA ATM Card */
multiline_comment|/* Types for class INV_SCSI and INV_VSCSI; The type code is the same as&n; * the device type code returned by the Inquiry command, iff the Inquiry&n; * command defines a type code for the device in question.  If it doesn&squot;t,&n; * values over 31 will be used for the device type.&n; * Note: the lun is encoded in bits 8-15 of the state.  The&n; * state field low 3 bits contains the information from the inquiry&n; * cmd that indicates ANSI SCSI 1,2, etc. compliance, and bit 7&n; * contains the inquiry info that indicates whether the media is&n; * removable.&n; */
DECL|macro|INV_PRINTER
mdefine_line|#define INV_PRINTER&t;2&t;/* SCSI printer */
DECL|macro|INV_CPU
mdefine_line|#define INV_CPU&t;&t;3&t;/* SCSI CPU device */
DECL|macro|INV_WORM
mdefine_line|#define INV_WORM&t;4&t;/* write-once-read-many (e.g. optical disks) */
DECL|macro|INV_CDROM
mdefine_line|#define INV_CDROM&t;5&t;/* CD-ROM  */
DECL|macro|INV_SCANNER
mdefine_line|#define INV_SCANNER&t;6&t;/* scanners */
DECL|macro|INV_OPTICAL
mdefine_line|#define INV_OPTICAL&t;7&t;/* optical disks (read-write) */
DECL|macro|INV_CHANGER
mdefine_line|#define INV_CHANGER&t;8&t;/* jukebox&squot;s for CDROMS, for example */
DECL|macro|INV_COMM
mdefine_line|#define INV_COMM&t;9&t;/* Communications device */
DECL|macro|INV_STARCTLR
mdefine_line|#define INV_STARCTLR&t;12&t;/* Storage Array Controller */
DECL|macro|INV_RAIDCTLR
mdefine_line|#define INV_RAIDCTLR&t;32&t;/* RAID ctlr actually gives type 0 */
multiline_comment|/* bit definitions for state field for class INV_SCSI */
DECL|macro|INV_REMOVE
mdefine_line|#define INV_REMOVE&t;0x80&t;/* has removable media */
DECL|macro|INV_SCSI_MASK
mdefine_line|#define INV_SCSI_MASK&t;7&t;/* to which ANSI SCSI standard device conforms*/
multiline_comment|/* types for class INV_AUDIO */
DECL|macro|INV_AUDIO_HDSP
mdefine_line|#define INV_AUDIO_HDSP&t;&t;0&t;/* Indigo DSP system */
DECL|macro|INV_AUDIO_VIGRA110
mdefine_line|#define INV_AUDIO_VIGRA110&t;1&t;/* ViGRA 110 audio board */
DECL|macro|INV_AUDIO_VIGRA210
mdefine_line|#define INV_AUDIO_VIGRA210&t;2&t;/* ViGRA 210 audio board */
DECL|macro|INV_AUDIO_A2
mdefine_line|#define INV_AUDIO_A2&t;&t;3&t;/* HAL2 / Audio Module for Indigo 2 */
DECL|macro|INV_AUDIO_A3
mdefine_line|#define INV_AUDIO_A3&t;&t;4&t;/* Moosehead (IP32) AD1843 codec */
DECL|macro|INV_AUDIO_RAD
mdefine_line|#define INV_AUDIO_RAD&t;&t;5&t;/* RAD PCI chip */
multiline_comment|/* types for class INV_VIDEO */
DECL|macro|INV_VIDEO_LIGHT
mdefine_line|#define&t;INV_VIDEO_LIGHT&t;&t;0
DECL|macro|INV_VIDEO_VS2
mdefine_line|#define&t;INV_VIDEO_VS2&t;&t;1&t;/* MultiChannel Option */
DECL|macro|INV_VIDEO_EXPRESS
mdefine_line|#define&t;INV_VIDEO_EXPRESS&t;2&t;/* kaleidecope video */
DECL|macro|INV_VIDEO_VINO
mdefine_line|#define&t;INV_VIDEO_VINO&t;&t;3
DECL|macro|INV_VIDEO_VO2
mdefine_line|#define&t;INV_VIDEO_VO2&t;&t;4&t;/* Sirius Video */
DECL|macro|INV_VIDEO_INDY
mdefine_line|#define&t;INV_VIDEO_INDY&t;&t;5&t;/* Indy Video - kal vid on Newport&n;&t;&t;&t;&t;&t;  gfx on Indy */
DECL|macro|INV_VIDEO_MVP
mdefine_line|#define&t;INV_VIDEO_MVP&t;&t;6&t;/* Moosehead Video Ports */
DECL|macro|INV_VIDEO_INDY_601
mdefine_line|#define&t;INV_VIDEO_INDY_601&t;7&t;/* Indy Video 601 */
DECL|macro|INV_VIDEO_PMUX
mdefine_line|#define&t;INV_VIDEO_PMUX&t;&t;8&t;/* PALMUX video w/ PGR gfx */
DECL|macro|INV_VIDEO_MGRAS
mdefine_line|#define&t;INV_VIDEO_MGRAS&t;&t;9&t;/* Galileo 1.5 video */
DECL|macro|INV_VIDEO_DIVO
mdefine_line|#define&t;INV_VIDEO_DIVO&t;&t;10&t;/* DIVO video */
DECL|macro|INV_VIDEO_RACER
mdefine_line|#define&t;INV_VIDEO_RACER&t;&t;11&t;/* SpeedRacer Pro Video */
DECL|macro|INV_VIDEO_EVO
mdefine_line|#define&t;INV_VIDEO_EVO&t;&t;12&t;/* EVO Personal Video */
DECL|macro|INV_VIDEO_XTHD
mdefine_line|#define INV_VIDEO_XTHD&t;&t;13&t;/* XIO XT-HDTV video */
DECL|macro|INV_VIDEO_XTDIGVID
mdefine_line|#define INV_VIDEO_XTDIGVID      14      /* XIO XT-HDDIGVID video */
multiline_comment|/* states for video class INV_VIDEO_EXPRESS */
DECL|macro|INV_GALILEO_REV
mdefine_line|#define INV_GALILEO_REV&t;&t;0xF
DECL|macro|INV_GALILEO_JUNIOR
mdefine_line|#define INV_GALILEO_JUNIOR&t;0x10
DECL|macro|INV_GALILEO_INDY_CAM
mdefine_line|#define INV_GALILEO_INDY_CAM&t;0x20
DECL|macro|INV_GALILEO_DBOB
mdefine_line|#define INV_GALILEO_DBOB&t;0x40
DECL|macro|INV_GALILEO_ELANTEC
mdefine_line|#define INV_GALILEO_ELANTEC&t;0x80
multiline_comment|/* states for video class VINO */
DECL|macro|INV_VINO_REV
mdefine_line|#define INV_VINO_REV&t;&t;0xF
DECL|macro|INV_VINO_INDY_CAM
mdefine_line|#define INV_VINO_INDY_CAM&t;0x10
DECL|macro|INV_VINO_INDY_NOSW
mdefine_line|#define INV_VINO_INDY_NOSW&t;0x20&t;/* nebulous - means s/w not installed */
multiline_comment|/* states for video class MVP */
DECL|macro|INV_MVP_REV
mdefine_line|#define INV_MVP_REV(x)&t;&t;(((x)&amp;0x0000000f))
DECL|macro|INV_MVP_REV_SW
mdefine_line|#define INV_MVP_REV_SW(x)&t;(((x)&amp;0x000000f0)&gt;&gt;4)
DECL|macro|INV_MVP_AV_BOARD
mdefine_line|#define INV_MVP_AV_BOARD(x)&t;(((x)&amp;0x00000f00)&gt;&gt;8)
DECL|macro|INV_MVP_AV_REV
mdefine_line|#define&t;INV_MVP_AV_REV(x)&t;(((x)&amp;0x0000f000)&gt;&gt;12)
DECL|macro|INV_MVP_CAMERA
mdefine_line|#define&t;INV_MVP_CAMERA(x)&t;(((x)&amp;0x000f0000)&gt;&gt;16)
DECL|macro|INV_MVP_CAM_REV
mdefine_line|#define&t;INV_MVP_CAM_REV(x)&t;(((x)&amp;0x00f00000)&gt;&gt;20)
DECL|macro|INV_MVP_SDIINF
mdefine_line|#define INV_MVP_SDIINF(x)       (((x)&amp;0x0f000000)&gt;&gt;24)
DECL|macro|INV_MVP_SDI_REV
mdefine_line|#define INV_MVP_SDI_REV(x)      (((x)&amp;0xf0000000)&gt;&gt;28)
multiline_comment|/* types for class INV_BUS */
DECL|macro|INV_BUS_VME
mdefine_line|#define INV_BUS_VME&t;0
DECL|macro|INV_BUS_EISA
mdefine_line|#define INV_BUS_EISA&t;1
DECL|macro|INV_BUS_GIO
mdefine_line|#define INV_BUS_GIO&t;2
DECL|macro|INV_BUS_BT3_PCI
mdefine_line|#define INV_BUS_BT3_PCI&t;3
multiline_comment|/* types for class INV_MISC */
DECL|macro|INV_MISC_EPC_EINT
mdefine_line|#define INV_MISC_EPC_EINT&t;0&t;/* EPC external interrupts */
DECL|macro|INV_MISC_PCKM
mdefine_line|#define INV_MISC_PCKM&t;&t;1&t;/* pc keyboard or mouse */
DECL|macro|INV_MISC_IOC3_EINT
mdefine_line|#define INV_MISC_IOC3_EINT&t;2&t;/* IOC3 external interrupts */
DECL|macro|INV_MISC_OTHER
mdefine_line|#define INV_MISC_OTHER&t;&t;3&t;/* non-specific type */
multiline_comment|/*&n; * The four components below do not actually have inventory information&n; * associated with the vertex. These symbols are used by grio at the &n; * moment to figure out the device type from the vertex. If these get&n; * inventory structures in the future, either the type values must&n; * remain the same or grio code needs to change.&n; */
DECL|macro|INV_XBOW
mdefine_line|#define INV_XBOW        &t;3&t;/* cross bow */
DECL|macro|INV_HUB
mdefine_line|#define INV_HUB         &t;4&t;/* hub */
DECL|macro|INV_PCI_BRIDGE
mdefine_line|#define INV_PCI_BRIDGE  &t;5&t;/* pci bridge */
DECL|macro|INV_ROUTER
mdefine_line|#define INV_ROUTER&t;&t;6&t;/* router */
multiline_comment|/*  types for class INV_PROM */
DECL|macro|INV_IO6PROM
mdefine_line|#define INV_IO6PROM&t;0
DECL|macro|INV_IP27PROM
mdefine_line|#define INV_IP27PROM&t;1
DECL|macro|INV_IP35PROM
mdefine_line|#define INV_IP35PROM&t;2
multiline_comment|/* types for class INV_COMPRESSION */
DECL|macro|INV_COSMO
mdefine_line|#define&t;INV_COSMO&t;&t;0
DECL|macro|INV_INDYCOMP
mdefine_line|#define&t;INV_INDYCOMP&t;&t;1
DECL|macro|INV_IMPACTCOMP
mdefine_line|#define&t;INV_IMPACTCOMP&t;&t;2&t;/* cosmo2, aka impact compression */
DECL|macro|INV_VICE
mdefine_line|#define&t;INV_VICE&t;&t;3 &t;/* Video imaging &amp; compression engine */
multiline_comment|/* types for class INV_DISPLAY */
DECL|macro|INV_PRESENTER_BOARD
mdefine_line|#define INV_PRESENTER_BOARD&t;0       /* Indy Presenter adapter board */
DECL|macro|INV_PRESENTER_PANEL
mdefine_line|#define INV_PRESENTER_PANEL&t;1       /* Indy Presenter board and panel */
DECL|macro|INV_ICO_BOARD
mdefine_line|#define INV_ICO_BOARD&t;&t;2&t;/* IMPACT channel option board */
DECL|macro|INV_DCD_BOARD
mdefine_line|#define INV_DCD_BOARD&t;&t;3&t;/* O2 dual channel option board */
DECL|macro|INV_7of9_BOARD
mdefine_line|#define INV_7of9_BOARD          4       /* 7of9 flatpanel adapter board */
DECL|macro|INV_7of9_PANEL
mdefine_line|#define INV_7of9_PANEL          5       /* 7of9 flatpanel board and panel */
multiline_comment|/* types for class INV_IEEE1394 */
DECL|macro|INV_OHCI
mdefine_line|#define INV_OHCI&t;0&t;/* Ohci IEEE1394 pci card */
multiline_comment|/* state for class INV_IEEE1394 &amp; type INV_OHCI */
DECL|macro|INV_IEEE1394_STATE_TI_REV_1
mdefine_line|#define INV_IEEE1394_STATE_TI_REV_1 0
multiline_comment|/* O2 DVLink 1.1 controller static info */
DECL|macro|INV_IEEE1394_CTLR_O2_DVLINK_11
mdefine_line|#define INV_IEEE1394_CTLR_O2_DVLINK_11 0x8009104c
multiline_comment|/* types for class INV_TPU */
DECL|macro|INV_TPU_EXT
mdefine_line|#define&t;INV_TPU_EXT&t;&t;0&t;/* External XIO Tensor Processing Unit */
DECL|macro|INV_TPU_XIO
mdefine_line|#define&t;INV_TPU_XIO&t;&t;1&t;/* Internal XIO Tensor Processing Unit */
multiline_comment|/*&n; * USB Types.  The upper 8 bits contain general usb device class and are used to&n; * qualify the lower 8 bits which contain device type within a usb class.&n; * Use USB_INV_DEVCLASS and USB_INV_DEVTYPE to to decode an i_type, and&n; * USB_INV_TYPE to set it.&n; */
DECL|macro|USB_INV_DEVCLASS
mdefine_line|#define USB_INV_DEVCLASS(invtype)&t;((invtype) &gt;&gt; 8)
DECL|macro|USB_INV_DEVTYPE
mdefine_line|#define USB_INV_DEVTYPE(invtype)&t;((invtype) &amp; 0xf)
DECL|macro|USB_INV_TYPE
mdefine_line|#define USB_INV_TYPE(usbclass, usbtype)&t;(((usbclass) &lt;&lt; 8) | (usbtype))
multiline_comment|/*&n; * USB device classes.  These classes might not match the classes as defined&n; * by the usb spec, but where possible we will try.&n; */
DECL|macro|USB_INV_CLASS_RH
mdefine_line|#define USB_INV_CLASS_RH&t;0x00&t;/* root hub (ie. controller) */
DECL|macro|USB_INV_CLASS_HID
mdefine_line|#define USB_INV_CLASS_HID&t;0x03&t;/* human interface device */
DECL|macro|USB_INV_CLASS_HUB
mdefine_line|#define USB_INV_CLASS_HUB&t;0x09&t;/* hub device */
multiline_comment|/*&n; * USB device types within a class.  These will not match USB device types,&n; * as the usb is not consistent on how specific types are defined (sometimes&n; * they are found in the interface subclass, sometimes (as in HID devices) they&n; * are found within data generated by the device (hid report descriptors for&n; * example).&n; */
multiline_comment|/*&n; * RH types&n; */
DECL|macro|USB_INV_RH_OHCI
mdefine_line|#define USB_INV_RH_OHCI&t;&t;0x01&t;/* ohci root hub */
multiline_comment|/*&n; * HID types&n; */
DECL|macro|USB_INV_HID_KEYBOARD
mdefine_line|#define USB_INV_HID_KEYBOARD&t;0x01&t;/* kbd (HID class) */
DECL|macro|USB_INV_HID_MOUSE
mdefine_line|#define USB_INV_HID_MOUSE&t;0x02&t;/* mouse (HID class) */
multiline_comment|/*&n; * HUB types - none yet&n; */
DECL|struct|invent_generic_s
r_typedef
r_struct
id|invent_generic_s
(brace
DECL|member|ig_module
r_int
r_int
id|ig_module
suffix:semicolon
DECL|member|ig_slot
r_int
r_int
id|ig_slot
suffix:semicolon
DECL|member|ig_flag
r_int
r_char
id|ig_flag
suffix:semicolon
DECL|member|ig_invclass
r_int
id|ig_invclass
suffix:semicolon
DECL|typedef|invent_generic_t
)brace
id|invent_generic_t
suffix:semicolon
DECL|macro|INVENT_ENABLED
mdefine_line|#define INVENT_ENABLED&t;0x1
DECL|struct|invent_membnkinfo
r_typedef
r_struct
id|invent_membnkinfo
(brace
DECL|member|imb_size
r_int
r_int
id|imb_size
suffix:semicolon
multiline_comment|/* bank size in MB */
DECL|member|imb_attr
r_int
r_int
id|imb_attr
suffix:semicolon
multiline_comment|/* Mem attributes */
DECL|member|imb_flag
r_int
r_int
id|imb_flag
suffix:semicolon
multiline_comment|/* bank flags */
DECL|typedef|invent_membnkinfo_t
)brace
id|invent_membnkinfo_t
suffix:semicolon
DECL|struct|invent_meminfo
r_typedef
r_struct
id|invent_meminfo
(brace
DECL|member|im_gen
id|invent_generic_t
id|im_gen
suffix:semicolon
DECL|member|im_size
r_int
r_int
id|im_size
suffix:semicolon
multiline_comment|/* memory size     */
DECL|member|im_banks
r_int
r_int
id|im_banks
suffix:semicolon
multiline_comment|/* number of banks */
multiline_comment|/*&n;&t; * declare an array with one element. Each platform is expected to&n;&t; * allocate the size required based on the number of banks and set&n;&t; * the im_banks correctly for this array traversal.&n;&t; */
DECL|member|im_bank_info
id|invent_membnkinfo_t
id|im_bank_info
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|invent_meminfo_t
)brace
id|invent_meminfo_t
suffix:semicolon
DECL|macro|INV_MEM_PREMIUM
mdefine_line|#define INV_MEM_PREMIUM&t; 0x01
DECL|struct|invent_cpuinfo
r_typedef
r_struct
id|invent_cpuinfo
(brace
DECL|member|ic_gen
id|invent_generic_t
id|ic_gen
suffix:semicolon
DECL|member|ic_cpu_info
id|cpu_inv_t
id|ic_cpu_info
suffix:semicolon
DECL|member|ic_cpuid
r_int
r_int
id|ic_cpuid
suffix:semicolon
DECL|member|ic_slice
r_int
r_int
id|ic_slice
suffix:semicolon
DECL|member|ic_cpumode
r_int
r_int
id|ic_cpumode
suffix:semicolon
DECL|typedef|invent_cpuinfo_t
)brace
id|invent_cpuinfo_t
suffix:semicolon
DECL|struct|invent_rpsinfo
r_typedef
r_struct
id|invent_rpsinfo
(brace
DECL|member|ir_gen
id|invent_generic_t
id|ir_gen
suffix:semicolon
DECL|member|ir_xbox
r_int
id|ir_xbox
suffix:semicolon
multiline_comment|/* is RPS connected to an xbox */
DECL|typedef|invent_rpsinfo_t
)brace
id|invent_rpsinfo_t
suffix:semicolon
DECL|struct|invent_miscinfo
r_typedef
r_struct
id|invent_miscinfo
(brace
DECL|member|im_gen
id|invent_generic_t
id|im_gen
suffix:semicolon
DECL|member|im_rev
r_int
id|im_rev
suffix:semicolon
DECL|member|im_version
r_int
id|im_version
suffix:semicolon
DECL|member|im_type
r_int
id|im_type
suffix:semicolon
DECL|member|im_speed
r_uint64
id|im_speed
suffix:semicolon
DECL|typedef|invent_miscinfo_t
)brace
id|invent_miscinfo_t
suffix:semicolon
DECL|struct|invent_routerinfo
r_typedef
r_struct
id|invent_routerinfo
(brace
DECL|member|im_gen
id|invent_generic_t
id|im_gen
suffix:semicolon
DECL|member|rip
id|router_inv_t
id|rip
suffix:semicolon
DECL|typedef|invent_routerinfo_t
)brace
id|invent_routerinfo_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|irix5_inventory_s
r_typedef
r_struct
id|irix5_inventory_s
(brace
DECL|member|inv_next
id|app32_ptr_t
id|inv_next
suffix:semicolon
multiline_comment|/* next inventory record in list */
DECL|member|inv_class
r_int
id|inv_class
suffix:semicolon
multiline_comment|/* class of object */
DECL|member|inv_type
r_int
id|inv_type
suffix:semicolon
multiline_comment|/* class sub-type of object */
DECL|member|inv_controller
id|major_t
id|inv_controller
suffix:semicolon
multiline_comment|/* object major identifier */
DECL|member|inv_unit
id|minor_t
id|inv_unit
suffix:semicolon
multiline_comment|/* object minor identifier */
DECL|member|inv_state
r_int
id|inv_state
suffix:semicolon
multiline_comment|/* information specific to object or&n;&t;&t;&t;&t;&t;   class */
DECL|typedef|irix5_inventory_t
)brace
id|irix5_inventory_t
suffix:semicolon
DECL|struct|invplace_s
r_typedef
r_struct
id|invplace_s
(brace
DECL|member|invplace_vhdl
id|devfs_handle_t
id|invplace_vhdl
suffix:semicolon
multiline_comment|/* current vertex */
DECL|member|invplace_vplace
id|devfs_handle_t
id|invplace_vplace
suffix:semicolon
multiline_comment|/* place in vertex list */
DECL|member|invplace_inv
id|inventory_t
op_star
id|invplace_inv
suffix:semicolon
multiline_comment|/* place in inv list on vertex */
DECL|typedef|invplace_t
)brace
id|invplace_t
suffix:semicolon
multiline_comment|/* Magic cookie placeholder in inventory list */
r_extern
id|invplace_t
id|invplace_none
suffix:semicolon
DECL|macro|INVPLACE_NONE
mdefine_line|#define INVPLACE_NONE invplace_none
r_extern
r_void
id|add_to_inventory
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|replace_in_inventory
c_func
(paren
id|inventory_t
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|start_scan_inventory
c_func
(paren
id|invplace_t
op_star
)paren
suffix:semicolon
r_extern
id|inventory_t
op_star
id|get_next_inventory
c_func
(paren
id|invplace_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|end_scan_inventory
c_func
(paren
id|invplace_t
op_star
)paren
suffix:semicolon
r_extern
id|inventory_t
op_star
id|find_inventory
c_func
(paren
id|inventory_t
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scaninvent
c_func
(paren
r_int
(paren
op_star
)paren
(paren
id|inventory_t
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_sizeof_inventory
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|device_inventory_add
c_func
(paren
id|devfs_handle_t
id|device
comma
r_int
r_class
comma
r_int
id|type
comma
id|major_t
id|ctlr
comma
id|minor_t
id|unit
comma
r_int
id|state
)paren
suffix:semicolon
r_extern
id|inventory_t
op_star
id|device_inventory_get_next
c_func
(paren
id|devfs_handle_t
id|device
comma
id|invplace_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|device_controller_num_set
c_func
(paren
id|devfs_handle_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|device_controller_num_get
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_SN_INVENT_H */
eof
