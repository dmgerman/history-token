multiline_comment|/*&n; * BK Id: SCCS/s.pnp.h 1.5 05/17/01 18:14:25 cort&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/* 11/02/95                                                                   */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*      Plug and Play header definitions                                      */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/* Structure map for PnP on PowerPC Reference Platform                        */
multiline_comment|/* See Plug and Play ISA Specification, Version 1.0, May 28, 1993.  It        */
multiline_comment|/* (or later versions) is available on Compuserve in the PLUGPLAY area.       */
multiline_comment|/* This code has extensions to that specification, namely new short and       */
multiline_comment|/* long tag types for platform dependent information                          */
multiline_comment|/* Warning: LE notation used throughout this file                             */
multiline_comment|/* For enum&squot;s: if given in hex then they are bit significant, i.e.            */
multiline_comment|/* only one bit is on for each enum                                           */
macro_line|#ifndef _PNP_
DECL|macro|_PNP_
mdefine_line|#define _PNP_
macro_line|#ifndef __ASSEMBLY__
DECL|macro|MAX_MEM_REGISTERS
mdefine_line|#define MAX_MEM_REGISTERS 9
DECL|macro|MAX_IO_PORTS
mdefine_line|#define MAX_IO_PORTS 20
DECL|macro|MAX_IRQS
mdefine_line|#define MAX_IRQS 7
multiline_comment|/*#define MAX_DMA_CHANNELS 7*/
multiline_comment|/* Interrupt controllers */
DECL|macro|PNPinterrupt0
mdefine_line|#define PNPinterrupt0 &quot;PNP0000&quot;      /* AT Interrupt Controller               */
DECL|macro|PNPinterrupt1
mdefine_line|#define PNPinterrupt1 &quot;PNP0001&quot;      /* EISA Interrupt Controller             */
DECL|macro|PNPinterrupt2
mdefine_line|#define PNPinterrupt2 &quot;PNP0002&quot;      /* MCA Interrupt Controller              */
DECL|macro|PNPinterrupt3
mdefine_line|#define PNPinterrupt3 &quot;PNP0003&quot;      /* APIC                                  */
DECL|macro|PNPExtInt
mdefine_line|#define PNPExtInt     &quot;IBM000D&quot;      /* PowerPC Extended Interrupt Controller */
multiline_comment|/* Timers */
DECL|macro|PNPtimer0
mdefine_line|#define PNPtimer0     &quot;PNP0100&quot;      /* AT Timer                              */
DECL|macro|PNPtimer1
mdefine_line|#define PNPtimer1     &quot;PNP0101&quot;      /* EISA Timer                            */
DECL|macro|PNPtimer2
mdefine_line|#define PNPtimer2     &quot;PNP0102&quot;      /* MCA Timer                             */
multiline_comment|/* DMA controllers */
DECL|macro|PNPdma0
mdefine_line|#define PNPdma0       &quot;PNP0200&quot;      /* AT DMA Controller                     */
DECL|macro|PNPdma1
mdefine_line|#define PNPdma1       &quot;PNP0201&quot;      /* EISA DMA Controller                   */
DECL|macro|PNPdma2
mdefine_line|#define PNPdma2       &quot;PNP0202&quot;      /* MCA DMA Controller                    */
multiline_comment|/* start of August 15, 1994 additions */
multiline_comment|/* CMOS */
DECL|macro|PNPCMOS
mdefine_line|#define PNPCMOS       &quot;IBM0009&quot;      /* CMOS                                  */
multiline_comment|/* L2 Cache */
DECL|macro|PNPL2
mdefine_line|#define PNPL2         &quot;IBM0007&quot;      /* L2 Cache                              */
multiline_comment|/* NVRAM */
DECL|macro|PNPNVRAM
mdefine_line|#define PNPNVRAM      &quot;IBM0008&quot;      /* NVRAM                                 */
multiline_comment|/* Power Management */
DECL|macro|PNPPM
mdefine_line|#define PNPPM         &quot;IBM0005&quot;      /* Power Management                      */
multiline_comment|/* end of August 15, 1994 additions */
multiline_comment|/* Keyboards */
DECL|macro|PNPkeyboard0
mdefine_line|#define PNPkeyboard0  &quot;PNP0300&quot;      /* IBM PC/XT KB Cntlr (83 key, no mouse) */
DECL|macro|PNPkeyboard1
mdefine_line|#define PNPkeyboard1  &quot;PNP0301&quot;      /* Olivetti ICO (102 key)                */
DECL|macro|PNPkeyboard2
mdefine_line|#define PNPkeyboard2  &quot;PNP0302&quot;      /* IBM PC/AT KB Cntlr (84 key)           */
DECL|macro|PNPkeyboard3
mdefine_line|#define PNPkeyboard3  &quot;PNP0303&quot;      /* IBM Enhanced (101/2 key, PS/2 mouse)  */
DECL|macro|PNPkeyboard4
mdefine_line|#define PNPkeyboard4  &quot;PNP0304&quot;      /* Nokia 1050 KB Cntlr                   */
DECL|macro|PNPkeyboard5
mdefine_line|#define PNPkeyboard5  &quot;PNP0305&quot;      /* Nokia 9140 KB Cntlr                   */
DECL|macro|PNPkeyboard6
mdefine_line|#define PNPkeyboard6  &quot;PNP0306&quot;      /* Standard Japanese KB Cntlr            */
DECL|macro|PNPkeyboard7
mdefine_line|#define PNPkeyboard7  &quot;PNP0307&quot;      /* Microsoft Windows (R) KB Cntlr        */
multiline_comment|/* Parallel port controllers */
DECL|macro|PNPparallel0
mdefine_line|#define PNPparallel0 &quot;PNP0400&quot;       /* Standard LPT Parallel Port            */
DECL|macro|PNPparallel1
mdefine_line|#define PNPparallel1 &quot;PNP0401&quot;       /* ECP Parallel Port                     */
DECL|macro|PNPepp
mdefine_line|#define PNPepp       &quot;IBM001C&quot;       /* EPP Parallel Port                     */
multiline_comment|/* Serial port controllers */
DECL|macro|PNPserial0
mdefine_line|#define PNPserial0   &quot;PNP0500&quot;       /* Standard PC Serial port               */
DECL|macro|PNPSerial1
mdefine_line|#define PNPSerial1   &quot;PNP0501&quot;       /* 16550A Compatible Serial port         */
multiline_comment|/* Disk controllers */
DECL|macro|PNPdisk0
mdefine_line|#define PNPdisk0     &quot;PNP0600&quot;       /* Generic ESDI/IDE/ATA Compat HD Cntlr  */
DECL|macro|PNPdisk1
mdefine_line|#define PNPdisk1     &quot;PNP0601&quot;       /* Plus Hardcard II                      */
DECL|macro|PNPdisk2
mdefine_line|#define PNPdisk2     &quot;PNP0602&quot;       /* Plus Hardcard IIXL/EZ                 */
multiline_comment|/* Diskette controllers */
DECL|macro|PNPdiskette0
mdefine_line|#define PNPdiskette0 &quot;PNP0700&quot;       /* PC Standard Floppy Disk Controller    */
multiline_comment|/* Display controllers */
DECL|macro|PNPdisplay0
mdefine_line|#define PNPdisplay0  &quot;PNP0900&quot;       /* VGA Compatible                        */
DECL|macro|PNPdisplay1
mdefine_line|#define PNPdisplay1  &quot;PNP0901&quot;       /* Video Seven VGA                       */
DECL|macro|PNPdisplay2
mdefine_line|#define PNPdisplay2  &quot;PNP0902&quot;       /* 8514/A Compatible                     */
DECL|macro|PNPdisplay3
mdefine_line|#define PNPdisplay3  &quot;PNP0903&quot;       /* Trident VGA                           */
DECL|macro|PNPdisplay4
mdefine_line|#define PNPdisplay4  &quot;PNP0904&quot;       /* Cirrus Logic Laptop VGA               */
DECL|macro|PNPdisplay5
mdefine_line|#define PNPdisplay5  &quot;PNP0905&quot;       /* Cirrus Logic VGA                      */
DECL|macro|PNPdisplay6
mdefine_line|#define PNPdisplay6  &quot;PNP0906&quot;       /* Tseng ET4000 or ET4000/W32            */
DECL|macro|PNPdisplay7
mdefine_line|#define PNPdisplay7  &quot;PNP0907&quot;       /* Western Digital VGA                   */
DECL|macro|PNPdisplay8
mdefine_line|#define PNPdisplay8  &quot;PNP0908&quot;       /* Western Digital Laptop VGA            */
DECL|macro|PNPdisplay9
mdefine_line|#define PNPdisplay9  &quot;PNP0909&quot;       /* S3                                    */
DECL|macro|PNPdisplayA
mdefine_line|#define PNPdisplayA  &quot;PNP090A&quot;       /* ATI Ultra Pro/Plus (Mach 32)          */
DECL|macro|PNPdisplayB
mdefine_line|#define PNPdisplayB  &quot;PNP090B&quot;       /* ATI Ultra (Mach 8)                    */
DECL|macro|PNPdisplayC
mdefine_line|#define PNPdisplayC  &quot;PNP090C&quot;       /* XGA Compatible                        */
DECL|macro|PNPdisplayD
mdefine_line|#define PNPdisplayD  &quot;PNP090D&quot;       /* ATI VGA Wonder                        */
DECL|macro|PNPdisplayE
mdefine_line|#define PNPdisplayE  &quot;PNP090E&quot;       /* Weitek P9000 Graphics Adapter         */
DECL|macro|PNPdisplayF
mdefine_line|#define PNPdisplayF  &quot;PNP090F&quot;       /* Oak Technology VGA                    */
multiline_comment|/* Peripheral busses */
DECL|macro|PNPbuses0
mdefine_line|#define PNPbuses0    &quot;PNP0A00&quot;       /* ISA Bus                               */
DECL|macro|PNPbuses1
mdefine_line|#define PNPbuses1    &quot;PNP0A01&quot;       /* EISA Bus                              */
DECL|macro|PNPbuses2
mdefine_line|#define PNPbuses2    &quot;PNP0A02&quot;       /* MCA Bus                               */
DECL|macro|PNPbuses3
mdefine_line|#define PNPbuses3    &quot;PNP0A03&quot;       /* PCI Bus                               */
DECL|macro|PNPbuses4
mdefine_line|#define PNPbuses4    &quot;PNP0A04&quot;       /* VESA/VL Bus                           */
multiline_comment|/* RTC, BIOS, planar devices */
DECL|macro|PNPspeaker0
mdefine_line|#define PNPspeaker0  &quot;PNP0800&quot;       /* AT Style Speaker Sound                */
DECL|macro|PNPrtc0
mdefine_line|#define PNPrtc0      &quot;PNP0B00&quot;       /* AT RTC                                */
DECL|macro|PNPpnpbios0
mdefine_line|#define PNPpnpbios0  &quot;PNP0C00&quot;       /* PNP BIOS (only created by root enum)  */
DECL|macro|PNPpnpbios1
mdefine_line|#define PNPpnpbios1  &quot;PNP0C01&quot;       /* System Board Memory Device            */
DECL|macro|PNPpnpbios2
mdefine_line|#define PNPpnpbios2  &quot;PNP0C02&quot;       /* Math Coprocessor                      */
DECL|macro|PNPpnpbios3
mdefine_line|#define PNPpnpbios3  &quot;PNP0C03&quot;       /* PNP BIOS Event Notification Interrupt */
multiline_comment|/* PCMCIA controller */
DECL|macro|PNPpcmcia0
mdefine_line|#define PNPpcmcia0   &quot;PNP0E00&quot;       /* Intel 82365 Compatible PCMCIA Cntlr   */
multiline_comment|/* Mice */
DECL|macro|PNPmouse0
mdefine_line|#define PNPmouse0    &quot;PNP0F00&quot;       /* Microsoft Bus Mouse                   */
DECL|macro|PNPmouse1
mdefine_line|#define PNPmouse1    &quot;PNP0F01&quot;       /* Microsoft Serial Mouse                */
DECL|macro|PNPmouse2
mdefine_line|#define PNPmouse2    &quot;PNP0F02&quot;       /* Microsoft Inport Mouse                */
DECL|macro|PNPmouse3
mdefine_line|#define PNPmouse3    &quot;PNP0F03&quot;       /* Microsoft PS/2 Mouse                  */
DECL|macro|PNPmouse4
mdefine_line|#define PNPmouse4    &quot;PNP0F04&quot;       /* Mousesystems Mouse                    */
DECL|macro|PNPmouse5
mdefine_line|#define PNPmouse5    &quot;PNP0F05&quot;       /* Mousesystems 3 Button Mouse - COM2    */
DECL|macro|PNPmouse6
mdefine_line|#define PNPmouse6    &quot;PNP0F06&quot;       /* Genius Mouse - COM1                   */
DECL|macro|PNPmouse7
mdefine_line|#define PNPmouse7    &quot;PNP0F07&quot;       /* Genius Mouse - COM2                   */
DECL|macro|PNPmouse8
mdefine_line|#define PNPmouse8    &quot;PNP0F08&quot;       /* Logitech Serial Mouse                 */
DECL|macro|PNPmouse9
mdefine_line|#define PNPmouse9    &quot;PNP0F09&quot;       /* Microsoft Ballpoint Serial Mouse      */
DECL|macro|PNPmouseA
mdefine_line|#define PNPmouseA    &quot;PNP0F0A&quot;       /* Microsoft PNP Mouse                   */
DECL|macro|PNPmouseB
mdefine_line|#define PNPmouseB    &quot;PNP0F0B&quot;       /* Microsoft PNP Ballpoint Mouse         */
multiline_comment|/* Modems */
DECL|macro|PNPmodem0
mdefine_line|#define PNPmodem0    &quot;PNP9000&quot;       /* Specific IDs TBD                      */
multiline_comment|/* Network controllers */
DECL|macro|PNPnetworkC9
mdefine_line|#define PNPnetworkC9 &quot;PNP80C9&quot;       /* IBM Token Ring                        */
DECL|macro|PNPnetworkCA
mdefine_line|#define PNPnetworkCA &quot;PNP80CA&quot;       /* IBM Token Ring II                     */
DECL|macro|PNPnetworkCB
mdefine_line|#define PNPnetworkCB &quot;PNP80CB&quot;       /* IBM Token Ring II/Short               */
DECL|macro|PNPnetworkCC
mdefine_line|#define PNPnetworkCC &quot;PNP80CC&quot;       /* IBM Token Ring 4/16Mbs                */
DECL|macro|PNPnetwork27
mdefine_line|#define PNPnetwork27 &quot;PNP8327&quot;       /* IBM Token Ring (All types)            */
DECL|macro|PNPnetworket
mdefine_line|#define PNPnetworket &quot;IBM0010&quot;       /* IBM Ethernet used by Power PC         */
DECL|macro|PNPneteisaet
mdefine_line|#define PNPneteisaet &quot;IBM2001&quot;       /* IBM Ethernet EISA adapter             */
DECL|macro|PNPAMD79C970
mdefine_line|#define PNPAMD79C970 &quot;IBM0016&quot;       /* AMD 79C970 (PCI Ethernet)             */
multiline_comment|/* SCSI controllers */
DECL|macro|PNPscsi0
mdefine_line|#define PNPscsi0     &quot;PNPA000&quot;       /* Adaptec 154x Compatible SCSI Cntlr    */
DECL|macro|PNPscsi1
mdefine_line|#define PNPscsi1     &quot;PNPA001&quot;       /* Adaptec 174x Compatible SCSI Cntlr    */
DECL|macro|PNPscsi2
mdefine_line|#define PNPscsi2     &quot;PNPA002&quot;       /* Future Domain 16-700 Compat SCSI Cntlr*/
DECL|macro|PNPscsi3
mdefine_line|#define PNPscsi3     &quot;PNPA003&quot;       /* Panasonic CDROM Adapter (SBPro/SB16)  */
DECL|macro|PNPscsiF
mdefine_line|#define PNPscsiF     &quot;IBM000F&quot;       /* NCR 810 SCSI Controller               */
DECL|macro|PNPscsi825
mdefine_line|#define PNPscsi825   &quot;IBM001B&quot;       /* NCR 825 SCSI Controller               */
DECL|macro|PNPscsi875
mdefine_line|#define PNPscsi875   &quot;IBM0018&quot;       /* NCR 875 SCSI Controller               */
multiline_comment|/* Sound/Video, Multimedia */
DECL|macro|PNPmm0
mdefine_line|#define PNPmm0       &quot;PNPB000&quot;       /* Sound Blaster Compatible Sound Device */
DECL|macro|PNPmm1
mdefine_line|#define PNPmm1       &quot;PNPB001&quot;       /* MS Windows Sound System Compat Device */
DECL|macro|PNPmmF
mdefine_line|#define PNPmmF       &quot;IBM000E&quot;       /* Crystal CS4231 Audio Device           */
DECL|macro|PNPv7310
mdefine_line|#define PNPv7310     &quot;IBM0015&quot;       /* ASCII V7310 Video Capture Device      */
DECL|macro|PNPmm4232
mdefine_line|#define PNPmm4232    &quot;IBM0017&quot;       /* Crystal CS4232 Audio Device           */
DECL|macro|PNPpmsyn
mdefine_line|#define PNPpmsyn     &quot;IBM001D&quot;       /* YMF 289B chip (Yamaha)                */
DECL|macro|PNPgp4232
mdefine_line|#define PNPgp4232    &quot;IBM0012&quot;       /* Crystal CS4232 Game Port              */
DECL|macro|PNPmidi4232
mdefine_line|#define PNPmidi4232  &quot;IBM0013&quot;       /* Crystal CS4232 MIDI                   */
multiline_comment|/* Operator Panel */
DECL|macro|PNPopctl
mdefine_line|#define PNPopctl     &quot;IBM000B&quot;       /* Operator&squot;s panel                      */
multiline_comment|/* Service Processor */
DECL|macro|PNPsp
mdefine_line|#define PNPsp        &quot;IBM0011&quot;       /* IBM Service Processor                 */
DECL|macro|PNPLTsp
mdefine_line|#define PNPLTsp      &quot;IBM001E&quot;       /* Lightning/Terlingua Support Processor */
DECL|macro|PNPLTmsp
mdefine_line|#define PNPLTmsp     &quot;IBM001F&quot;       /* Lightning/Terlingua Mini-SP           */
multiline_comment|/* Memory Controller */
DECL|macro|PNPmemctl
mdefine_line|#define PNPmemctl    &quot;IBM000A&quot;       /* Memory controller                     */
multiline_comment|/* Graphics Assist */
DECL|macro|PNPg_assist
mdefine_line|#define PNPg_assist  &quot;IBM0014&quot;       /* Graphics Assist                       */
multiline_comment|/* Miscellaneous Device Controllers */
DECL|macro|PNPtablet
mdefine_line|#define PNPtablet    &quot;IBM0019&quot;       /* IBM Tablet Controller                 */
multiline_comment|/* PNP Packet Handles */
DECL|macro|S1_Packet
mdefine_line|#define S1_Packet                0x0A   /* Version resource                   */
DECL|macro|S2_Packet
mdefine_line|#define S2_Packet                0x15   /* Logical DEVID (without flags)      */
DECL|macro|S2_Packet_flags
mdefine_line|#define S2_Packet_flags          0x16   /* Logical DEVID (with flags)         */
DECL|macro|S3_Packet
mdefine_line|#define S3_Packet                0x1C   /* Compatible device ID               */
DECL|macro|S4_Packet
mdefine_line|#define S4_Packet                0x22   /* IRQ resource (without flags)       */
DECL|macro|S4_Packet_flags
mdefine_line|#define S4_Packet_flags          0x23   /* IRQ resource (with flags)          */
DECL|macro|S5_Packet
mdefine_line|#define S5_Packet                0x2A   /* DMA resource                       */
DECL|macro|S6_Packet
mdefine_line|#define S6_Packet                0x30   /* Depend funct start (w/o priority)  */
DECL|macro|S6_Packet_priority
mdefine_line|#define S6_Packet_priority       0x31   /* Depend funct start (w/ priority)   */
DECL|macro|S7_Packet
mdefine_line|#define S7_Packet                0x38   /* Depend funct end                   */
DECL|macro|S8_Packet
mdefine_line|#define S8_Packet                0x47   /* I/O port resource (w/o fixed loc)  */
DECL|macro|S9_Packet_fixed
mdefine_line|#define S9_Packet_fixed          0x4B   /* I/O port resource (w/ fixed loc)   */
DECL|macro|S14_Packet
mdefine_line|#define S14_Packet               0x71   /* Vendor defined                     */
DECL|macro|S15_Packet
mdefine_line|#define S15_Packet               0x78   /* End of resource (w/o checksum)     */
DECL|macro|S15_Packet_checksum
mdefine_line|#define S15_Packet_checksum      0x79   /* End of resource (w/ checksum)      */
DECL|macro|L1_Packet
mdefine_line|#define L1_Packet                0x81   /* Memory range                       */
DECL|macro|L1_Shadow
mdefine_line|#define L1_Shadow                0x20   /* Memory is shadowable               */
DECL|macro|L1_32bit_mem
mdefine_line|#define L1_32bit_mem             0x18   /* 32-bit memory only                 */
DECL|macro|L1_8_16bit_mem
mdefine_line|#define L1_8_16bit_mem           0x10   /* 8- and 16-bit supported            */
DECL|macro|L1_Decode_Hi
mdefine_line|#define L1_Decode_Hi             0x04   /* decode supports high address       */
DECL|macro|L1_Cache
mdefine_line|#define L1_Cache                 0x02   /* read cacheable, write-through      */
DECL|macro|L1_Writeable
mdefine_line|#define L1_Writeable             0x01   /* Memory is writeable                */
DECL|macro|L2_Packet
mdefine_line|#define L2_Packet                0x82   /* ANSI ID string                     */
DECL|macro|L3_Packet
mdefine_line|#define L3_Packet                0x83   /* Unicode ID string                  */
DECL|macro|L4_Packet
mdefine_line|#define L4_Packet                0x84   /* Vendor defined                     */
DECL|macro|L5_Packet
mdefine_line|#define L5_Packet                0x85   /* Large I/O                          */
DECL|macro|L6_Packet
mdefine_line|#define L6_Packet                0x86   /* 32-bit Fixed Loc Mem Range Desc    */
DECL|macro|END_TAG
mdefine_line|#define END_TAG                  0x78   /* End of resource                    */
DECL|macro|DF_START_TAG
mdefine_line|#define DF_START_TAG             0x30   /* Dependent function start           */
DECL|macro|DF_START_TAG_priority
mdefine_line|#define DF_START_TAG_priority    0x31   /* Dependent function start           */
DECL|macro|DF_END_TAG
mdefine_line|#define DF_END_TAG               0x38   /* Dependent function end             */
DECL|macro|SUBOPTIMAL_CONFIGURATION
mdefine_line|#define SUBOPTIMAL_CONFIGURATION 0x2    /* Priority byte sub optimal config   */
multiline_comment|/* Device Base Type Codes */
DECL|enum|_PnP_BASE_TYPE
r_typedef
r_enum
id|_PnP_BASE_TYPE
(brace
DECL|enumerator|Reserved
id|Reserved
op_assign
l_int|0
comma
DECL|enumerator|MassStorageDevice
id|MassStorageDevice
op_assign
l_int|1
comma
DECL|enumerator|NetworkInterfaceController
id|NetworkInterfaceController
op_assign
l_int|2
comma
DECL|enumerator|DisplayController
id|DisplayController
op_assign
l_int|3
comma
DECL|enumerator|MultimediaController
id|MultimediaController
op_assign
l_int|4
comma
DECL|enumerator|MemoryController
id|MemoryController
op_assign
l_int|5
comma
DECL|enumerator|BridgeController
id|BridgeController
op_assign
l_int|6
comma
DECL|enumerator|CommunicationsDevice
id|CommunicationsDevice
op_assign
l_int|7
comma
DECL|enumerator|SystemPeripheral
id|SystemPeripheral
op_assign
l_int|8
comma
DECL|enumerator|InputDevice
id|InputDevice
op_assign
l_int|9
comma
DECL|enumerator|ServiceProcessor
id|ServiceProcessor
op_assign
l_int|0x0A
comma
multiline_comment|/* 11/2/95                            */
DECL|typedef|PnP_BASE_TYPE
)brace
id|PnP_BASE_TYPE
suffix:semicolon
multiline_comment|/* Device Sub Type Codes */
DECL|enum|_PnP_SUB_TYPE
r_typedef
r_enum
id|_PnP_SUB_TYPE
(brace
DECL|enumerator|SCSIController
id|SCSIController
op_assign
l_int|0
comma
DECL|enumerator|IDEController
id|IDEController
op_assign
l_int|1
comma
DECL|enumerator|FloppyController
id|FloppyController
op_assign
l_int|2
comma
DECL|enumerator|IPIController
id|IPIController
op_assign
l_int|3
comma
DECL|enumerator|OtherMassStorageController
id|OtherMassStorageController
op_assign
l_int|0x80
comma
DECL|enumerator|EthernetController
id|EthernetController
op_assign
l_int|0
comma
DECL|enumerator|TokenRingController
id|TokenRingController
op_assign
l_int|1
comma
DECL|enumerator|FDDIController
id|FDDIController
op_assign
l_int|2
comma
DECL|enumerator|OtherNetworkController
id|OtherNetworkController
op_assign
l_int|0x80
comma
DECL|enumerator|VGAController
id|VGAController
op_assign
l_int|0
comma
DECL|enumerator|SVGAController
id|SVGAController
op_assign
l_int|1
comma
DECL|enumerator|XGAController
id|XGAController
op_assign
l_int|2
comma
DECL|enumerator|OtherDisplayController
id|OtherDisplayController
op_assign
l_int|0x80
comma
DECL|enumerator|VideoController
id|VideoController
op_assign
l_int|0
comma
DECL|enumerator|AudioController
id|AudioController
op_assign
l_int|1
comma
DECL|enumerator|OtherMultimediaController
id|OtherMultimediaController
op_assign
l_int|0x80
comma
DECL|enumerator|RAM
id|RAM
op_assign
l_int|0
comma
DECL|enumerator|FLASH
id|FLASH
op_assign
l_int|1
comma
DECL|enumerator|OtherMemoryDevice
id|OtherMemoryDevice
op_assign
l_int|0x80
comma
DECL|enumerator|HostProcessorBridge
id|HostProcessorBridge
op_assign
l_int|0
comma
DECL|enumerator|ISABridge
id|ISABridge
op_assign
l_int|1
comma
DECL|enumerator|EISABridge
id|EISABridge
op_assign
l_int|2
comma
DECL|enumerator|MicroChannelBridge
id|MicroChannelBridge
op_assign
l_int|3
comma
DECL|enumerator|PCIBridge
id|PCIBridge
op_assign
l_int|4
comma
DECL|enumerator|PCMCIABridge
id|PCMCIABridge
op_assign
l_int|5
comma
DECL|enumerator|VMEBridge
id|VMEBridge
op_assign
l_int|6
comma
DECL|enumerator|OtherBridgeDevice
id|OtherBridgeDevice
op_assign
l_int|0x80
comma
DECL|enumerator|RS232Device
id|RS232Device
op_assign
l_int|0
comma
DECL|enumerator|ATCompatibleParallelPort
id|ATCompatibleParallelPort
op_assign
l_int|1
comma
DECL|enumerator|OtherCommunicationsDevice
id|OtherCommunicationsDevice
op_assign
l_int|0x80
comma
DECL|enumerator|ProgrammableInterruptController
id|ProgrammableInterruptController
op_assign
l_int|0
comma
DECL|enumerator|DMAController
id|DMAController
op_assign
l_int|1
comma
DECL|enumerator|SystemTimer
id|SystemTimer
op_assign
l_int|2
comma
DECL|enumerator|RealTimeClock
id|RealTimeClock
op_assign
l_int|3
comma
DECL|enumerator|L2Cache
id|L2Cache
op_assign
l_int|4
comma
DECL|enumerator|NVRAM
id|NVRAM
op_assign
l_int|5
comma
DECL|enumerator|PowerManagement
id|PowerManagement
op_assign
l_int|6
comma
DECL|enumerator|CMOS
id|CMOS
op_assign
l_int|7
comma
DECL|enumerator|OperatorPanel
id|OperatorPanel
op_assign
l_int|8
comma
DECL|enumerator|ServiceProcessorClass1
id|ServiceProcessorClass1
op_assign
l_int|9
comma
DECL|enumerator|ServiceProcessorClass2
id|ServiceProcessorClass2
op_assign
l_int|0xA
comma
DECL|enumerator|ServiceProcessorClass3
id|ServiceProcessorClass3
op_assign
l_int|0xB
comma
DECL|enumerator|GraphicAssist
id|GraphicAssist
op_assign
l_int|0xC
comma
DECL|enumerator|SystemPlanar
id|SystemPlanar
op_assign
l_int|0xF
comma
multiline_comment|/* 10/5/95                            */
DECL|enumerator|OtherSystemPeripheral
id|OtherSystemPeripheral
op_assign
l_int|0x80
comma
DECL|enumerator|KeyboardController
id|KeyboardController
op_assign
l_int|0
comma
DECL|enumerator|Digitizer
id|Digitizer
op_assign
l_int|1
comma
DECL|enumerator|MouseController
id|MouseController
op_assign
l_int|2
comma
DECL|enumerator|TabletController
id|TabletController
op_assign
l_int|3
comma
multiline_comment|/* 10/27/95                           */
DECL|enumerator|OtherInputController
id|OtherInputController
op_assign
l_int|0x80
comma
DECL|enumerator|GeneralMemoryController
id|GeneralMemoryController
op_assign
l_int|0
comma
DECL|typedef|PnP_SUB_TYPE
)brace
id|PnP_SUB_TYPE
suffix:semicolon
multiline_comment|/* Device Interface Type Codes */
DECL|enum|_PnP_INTERFACE
r_typedef
r_enum
id|_PnP_INTERFACE
(brace
DECL|enumerator|General
id|General
op_assign
l_int|0
comma
DECL|enumerator|GeneralSCSI
id|GeneralSCSI
op_assign
l_int|0
comma
DECL|enumerator|GeneralIDE
id|GeneralIDE
op_assign
l_int|0
comma
DECL|enumerator|ATACompatible
id|ATACompatible
op_assign
l_int|1
comma
DECL|enumerator|GeneralFloppy
id|GeneralFloppy
op_assign
l_int|0
comma
DECL|enumerator|Compatible765
id|Compatible765
op_assign
l_int|1
comma
DECL|enumerator|NS398_Floppy
id|NS398_Floppy
op_assign
l_int|2
comma
multiline_comment|/* NS Super I/O wired to use index&n;                                           register at port 398 and data&n;                                           register at port 399               */
DECL|enumerator|NS26E_Floppy
id|NS26E_Floppy
op_assign
l_int|3
comma
multiline_comment|/* Ports 26E and 26F                  */
DECL|enumerator|NS15C_Floppy
id|NS15C_Floppy
op_assign
l_int|4
comma
multiline_comment|/* Ports 15C and 15D                  */
DECL|enumerator|NS2E_Floppy
id|NS2E_Floppy
op_assign
l_int|5
comma
multiline_comment|/* Ports 2E and 2F                    */
DECL|enumerator|CHRP_Floppy
id|CHRP_Floppy
op_assign
l_int|6
comma
multiline_comment|/* CHRP Floppy in PR*P system         */
DECL|enumerator|GeneralIPI
id|GeneralIPI
op_assign
l_int|0
comma
DECL|enumerator|GeneralEther
id|GeneralEther
op_assign
l_int|0
comma
DECL|enumerator|GeneralToken
id|GeneralToken
op_assign
l_int|0
comma
DECL|enumerator|GeneralFDDI
id|GeneralFDDI
op_assign
l_int|0
comma
DECL|enumerator|GeneralVGA
id|GeneralVGA
op_assign
l_int|0
comma
DECL|enumerator|GeneralSVGA
id|GeneralSVGA
op_assign
l_int|0
comma
DECL|enumerator|GeneralXGA
id|GeneralXGA
op_assign
l_int|0
comma
DECL|enumerator|GeneralVideo
id|GeneralVideo
op_assign
l_int|0
comma
DECL|enumerator|GeneralAudio
id|GeneralAudio
op_assign
l_int|0
comma
DECL|enumerator|CS4232Audio
id|CS4232Audio
op_assign
l_int|1
comma
multiline_comment|/* CS 4232 Plug &squot;n Play Configured    */
DECL|enumerator|GeneralRAM
id|GeneralRAM
op_assign
l_int|0
comma
DECL|enumerator|GeneralFLASH
id|GeneralFLASH
op_assign
l_int|0
comma
DECL|enumerator|PCIMemoryController
id|PCIMemoryController
op_assign
l_int|0
comma
multiline_comment|/* PCI Config Method                  */
DECL|enumerator|RS6KMemoryController
id|RS6KMemoryController
op_assign
l_int|1
comma
multiline_comment|/* RS6K Config Method                 */
DECL|enumerator|GeneralHostBridge
id|GeneralHostBridge
op_assign
l_int|0
comma
DECL|enumerator|GeneralISABridge
id|GeneralISABridge
op_assign
l_int|0
comma
DECL|enumerator|GeneralEISABridge
id|GeneralEISABridge
op_assign
l_int|0
comma
DECL|enumerator|GeneralMCABridge
id|GeneralMCABridge
op_assign
l_int|0
comma
DECL|enumerator|GeneralPCIBridge
id|GeneralPCIBridge
op_assign
l_int|0
comma
DECL|enumerator|PCIBridgeDirect
id|PCIBridgeDirect
op_assign
l_int|0
comma
DECL|enumerator|PCIBridgeIndirect
id|PCIBridgeIndirect
op_assign
l_int|1
comma
DECL|enumerator|PCIBridgeRS6K
id|PCIBridgeRS6K
op_assign
l_int|2
comma
DECL|enumerator|GeneralPCMCIABridge
id|GeneralPCMCIABridge
op_assign
l_int|0
comma
DECL|enumerator|GeneralVMEBridge
id|GeneralVMEBridge
op_assign
l_int|0
comma
DECL|enumerator|GeneralRS232
id|GeneralRS232
op_assign
l_int|0
comma
DECL|enumerator|COMx
id|COMx
op_assign
l_int|1
comma
DECL|enumerator|Compatible16450
id|Compatible16450
op_assign
l_int|2
comma
DECL|enumerator|Compatible16550
id|Compatible16550
op_assign
l_int|3
comma
DECL|enumerator|NS398SerPort
id|NS398SerPort
op_assign
l_int|4
comma
multiline_comment|/* NS Super I/O wired to use index&n;                                           register at port 398 and data&n;                                           register at port 399               */
DECL|enumerator|NS26ESerPort
id|NS26ESerPort
op_assign
l_int|5
comma
multiline_comment|/* Ports 26E and 26F                  */
DECL|enumerator|NS15CSerPort
id|NS15CSerPort
op_assign
l_int|6
comma
multiline_comment|/* Ports 15C and 15D                  */
DECL|enumerator|NS2ESerPort
id|NS2ESerPort
op_assign
l_int|7
comma
multiline_comment|/* Ports 2E and 2F                    */
DECL|enumerator|GeneralParPort
id|GeneralParPort
op_assign
l_int|0
comma
DECL|enumerator|LPTx
id|LPTx
op_assign
l_int|1
comma
DECL|enumerator|NS398ParPort
id|NS398ParPort
op_assign
l_int|2
comma
multiline_comment|/* NS Super I/O wired to use index&n;                                           register at port 398 and data&n;                                           register at port 399               */
DECL|enumerator|NS26EParPort
id|NS26EParPort
op_assign
l_int|3
comma
multiline_comment|/* Ports 26E and 26F                  */
DECL|enumerator|NS15CParPort
id|NS15CParPort
op_assign
l_int|4
comma
multiline_comment|/* Ports 15C and 15D                  */
DECL|enumerator|NS2EParPort
id|NS2EParPort
op_assign
l_int|5
comma
multiline_comment|/* Ports 2E and 2F                    */
DECL|enumerator|GeneralPIC
id|GeneralPIC
op_assign
l_int|0
comma
DECL|enumerator|ISA_PIC
id|ISA_PIC
op_assign
l_int|1
comma
DECL|enumerator|EISA_PIC
id|EISA_PIC
op_assign
l_int|2
comma
DECL|enumerator|MPIC
id|MPIC
op_assign
l_int|3
comma
DECL|enumerator|RS6K_PIC
id|RS6K_PIC
op_assign
l_int|4
comma
DECL|enumerator|GeneralDMA
id|GeneralDMA
op_assign
l_int|0
comma
DECL|enumerator|ISA_DMA
id|ISA_DMA
op_assign
l_int|1
comma
DECL|enumerator|EISA_DMA
id|EISA_DMA
op_assign
l_int|2
comma
DECL|enumerator|GeneralTimer
id|GeneralTimer
op_assign
l_int|0
comma
DECL|enumerator|ISA_Timer
id|ISA_Timer
op_assign
l_int|1
comma
DECL|enumerator|EISA_Timer
id|EISA_Timer
op_assign
l_int|2
comma
DECL|enumerator|GeneralRTC
id|GeneralRTC
op_assign
l_int|0
comma
DECL|enumerator|ISA_RTC
id|ISA_RTC
op_assign
l_int|1
comma
DECL|enumerator|StoreThruOnly
id|StoreThruOnly
op_assign
l_int|1
comma
DECL|enumerator|StoreInEnabled
id|StoreInEnabled
op_assign
l_int|2
comma
DECL|enumerator|RS6KL2Cache
id|RS6KL2Cache
op_assign
l_int|3
comma
DECL|enumerator|IndirectNVRAM
id|IndirectNVRAM
op_assign
l_int|0
comma
multiline_comment|/* Indirectly addressed               */
DECL|enumerator|DirectNVRAM
id|DirectNVRAM
op_assign
l_int|1
comma
multiline_comment|/* Memory Mapped                      */
DECL|enumerator|IndirectNVRAM24
id|IndirectNVRAM24
op_assign
l_int|2
comma
multiline_comment|/* Indirectly addressed - 24 bit      */
DECL|enumerator|GeneralPowerManagement
id|GeneralPowerManagement
op_assign
l_int|0
comma
DECL|enumerator|EPOWPowerManagement
id|EPOWPowerManagement
op_assign
l_int|1
comma
DECL|enumerator|PowerControl
id|PowerControl
op_assign
l_int|2
comma
singleline_comment|// d1378
DECL|enumerator|GeneralCMOS
id|GeneralCMOS
op_assign
l_int|0
comma
DECL|enumerator|GeneralOPPanel
id|GeneralOPPanel
op_assign
l_int|0
comma
DECL|enumerator|HarddiskLight
id|HarddiskLight
op_assign
l_int|1
comma
DECL|enumerator|CDROMLight
id|CDROMLight
op_assign
l_int|2
comma
DECL|enumerator|PowerLight
id|PowerLight
op_assign
l_int|3
comma
DECL|enumerator|KeyLock
id|KeyLock
op_assign
l_int|4
comma
DECL|enumerator|ANDisplay
id|ANDisplay
op_assign
l_int|5
comma
multiline_comment|/* AlphaNumeric Display               */
DECL|enumerator|SystemStatusLED
id|SystemStatusLED
op_assign
l_int|6
comma
multiline_comment|/* 3 digit 7 segment LED              */
DECL|enumerator|CHRP_SystemStatusLED
id|CHRP_SystemStatusLED
op_assign
l_int|7
comma
multiline_comment|/* CHRP LEDs in PR*P system           */
DECL|enumerator|GeneralServiceProcessor
id|GeneralServiceProcessor
op_assign
l_int|0
comma
DECL|enumerator|TransferData
id|TransferData
op_assign
l_int|1
comma
DECL|enumerator|IGMC32
id|IGMC32
op_assign
l_int|2
comma
DECL|enumerator|IGMC64
id|IGMC64
op_assign
l_int|3
comma
DECL|enumerator|GeneralSystemPlanar
id|GeneralSystemPlanar
op_assign
l_int|0
comma
multiline_comment|/* 10/5/95                            */
DECL|typedef|PnP_INTERFACE
)brace
id|PnP_INTERFACE
suffix:semicolon
multiline_comment|/* PnP resources */
multiline_comment|/* Compressed ASCII is 5 bits per char; 00001=A ... 11010=Z */
DECL|struct|_SERIAL_ID
r_typedef
r_struct
id|_SERIAL_ID
(brace
DECL|member|VendorID0
r_int
r_char
id|VendorID0
suffix:semicolon
multiline_comment|/*    Bit(7)=0                        */
multiline_comment|/*    Bits(6:2)=1st character in      */
multiline_comment|/*       compressed ASCII             */
multiline_comment|/*    Bits(1:0)=2nd character in      */
multiline_comment|/*       compressed ASCII bits(4:3)   */
DECL|member|VendorID1
r_int
r_char
id|VendorID1
suffix:semicolon
multiline_comment|/*    Bits(7:5)=2nd character in      */
multiline_comment|/*       compressed ASCII bits(2:0)   */
multiline_comment|/*    Bits(4:0)=3rd character in      */
multiline_comment|/*       compressed ASCII             */
DECL|member|VendorID2
r_int
r_char
id|VendorID2
suffix:semicolon
multiline_comment|/* Product number - vendor assigned   */
DECL|member|VendorID3
r_int
r_char
id|VendorID3
suffix:semicolon
multiline_comment|/* Product number - vendor assigned   */
multiline_comment|/* Serial number is to provide uniqueness if more than one board of same      */
multiline_comment|/* type is in system.  Must be &quot;FFFFFFFF&quot; if feature not supported.           */
DECL|member|Serial0
r_int
r_char
id|Serial0
suffix:semicolon
multiline_comment|/* Unique serial number bits (7:0)    */
DECL|member|Serial1
r_int
r_char
id|Serial1
suffix:semicolon
multiline_comment|/* Unique serial number bits (15:8)   */
DECL|member|Serial2
r_int
r_char
id|Serial2
suffix:semicolon
multiline_comment|/* Unique serial number bits (23:16)  */
DECL|member|Serial3
r_int
r_char
id|Serial3
suffix:semicolon
multiline_comment|/* Unique serial number bits (31:24)  */
DECL|member|Checksum
r_int
r_char
id|Checksum
suffix:semicolon
DECL|typedef|SERIAL_ID
)brace
id|SERIAL_ID
suffix:semicolon
DECL|enum|_PnPItemName
r_typedef
r_enum
id|_PnPItemName
(brace
DECL|enumerator|Unused
id|Unused
op_assign
l_int|0
comma
DECL|enumerator|PnPVersion
id|PnPVersion
op_assign
l_int|1
comma
DECL|enumerator|LogicalDevice
id|LogicalDevice
op_assign
l_int|2
comma
DECL|enumerator|CompatibleDevice
id|CompatibleDevice
op_assign
l_int|3
comma
DECL|enumerator|IRQFormat
id|IRQFormat
op_assign
l_int|4
comma
DECL|enumerator|DMAFormat
id|DMAFormat
op_assign
l_int|5
comma
DECL|enumerator|StartDepFunc
id|StartDepFunc
op_assign
l_int|6
comma
DECL|enumerator|EndDepFunc
id|EndDepFunc
op_assign
l_int|7
comma
DECL|enumerator|IOPort
id|IOPort
op_assign
l_int|8
comma
DECL|enumerator|FixedIOPort
id|FixedIOPort
op_assign
l_int|9
comma
DECL|enumerator|Res1
id|Res1
op_assign
l_int|10
comma
DECL|enumerator|Res2
id|Res2
op_assign
l_int|11
comma
DECL|enumerator|Res3
id|Res3
op_assign
l_int|12
comma
DECL|enumerator|SmallVendorItem
id|SmallVendorItem
op_assign
l_int|14
comma
DECL|enumerator|EndTag
id|EndTag
op_assign
l_int|15
comma
DECL|enumerator|MemoryRange
id|MemoryRange
op_assign
l_int|1
comma
DECL|enumerator|ANSIIdentifier
id|ANSIIdentifier
op_assign
l_int|2
comma
DECL|enumerator|UnicodeIdentifier
id|UnicodeIdentifier
op_assign
l_int|3
comma
DECL|enumerator|LargeVendorItem
id|LargeVendorItem
op_assign
l_int|4
comma
DECL|enumerator|MemoryRange32
id|MemoryRange32
op_assign
l_int|5
comma
DECL|enumerator|MemoryRangeFixed32
id|MemoryRangeFixed32
op_assign
l_int|6
comma
DECL|typedef|PnPItemName
)brace
id|PnPItemName
suffix:semicolon
multiline_comment|/* Define a bunch of access functions for the bits in the tag field */
multiline_comment|/* Tag type - 0 = small; 1 = large */
DECL|macro|tag_type
mdefine_line|#define tag_type(t) (((t) &amp; 0x80)&gt;&gt;7)
DECL|macro|set_tag_type
mdefine_line|#define set_tag_type(t,v) (t = (t &amp; 0x7f) | ((v)&lt;&lt;7))
multiline_comment|/* Small item name is 4 bits - one of PnPItemName enum above */
DECL|macro|tag_small_item_name
mdefine_line|#define tag_small_item_name(t) (((t) &amp; 0x78)&gt;&gt;3)
DECL|macro|set_tag_small_item_name
mdefine_line|#define set_tag_small_item_name(t,v) (t = (t &amp; 0x07) | ((v)&lt;&lt;3))
multiline_comment|/* Small item count is 3 bits - count of further bytes in packet */
DECL|macro|tag_small_count
mdefine_line|#define tag_small_count(t) ((t) &amp; 0x07)
DECL|macro|set_tag_count
mdefine_line|#define set_tag_count(t,v) (t = (t &amp; 0x78) | (v))
multiline_comment|/* Large item name is 7 bits - one of PnPItemName enum above */
DECL|macro|tag_large_item_name
mdefine_line|#define tag_large_item_name(t) ((t) &amp; 0x7f)
DECL|macro|set_tag_large_item_name
mdefine_line|#define set_tag_large_item_name(t,v) (t = (t | 0x80) | (v))
multiline_comment|/* a PnP resource is a bunch of contiguous TAG packets ending with an end tag */
DECL|union|_PnP_TAG_PACKET
r_typedef
r_union
id|_PnP_TAG_PACKET
(brace
DECL|struct|_S1_Pack
r_struct
id|_S1_Pack
(brace
multiline_comment|/* VERSION PACKET                     */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x0a                   */
DECL|member|Version
r_int
r_char
id|Version
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* PnP version, Vendor version        */
DECL|member|S1_Pack
)brace
id|S1_Pack
suffix:semicolon
DECL|struct|_S2_Pack
r_struct
id|_S2_Pack
(brace
multiline_comment|/* LOGICAL DEVICE ID PACKET           */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x15 or 0x16           */
DECL|member|DevId
r_int
r_char
id|DevId
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Logical device id                  */
DECL|member|Flags
r_int
r_char
id|Flags
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* bit(0) boot device;                */
multiline_comment|/* bit(7:1) cmd in range x31-x37      */
multiline_comment|/* bit(7:0) cmd in range x28-x3f (opt)*/
DECL|member|S2_Pack
)brace
id|S2_Pack
suffix:semicolon
DECL|struct|_S3_Pack
r_struct
id|_S3_Pack
(brace
multiline_comment|/* COMPATIBLE DEVICE ID PACKET        */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x1c                   */
DECL|member|CompatId
r_int
r_char
id|CompatId
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Compatible device id               */
DECL|member|S3_Pack
)brace
id|S3_Pack
suffix:semicolon
DECL|struct|_S4_Pack
r_struct
id|_S4_Pack
(brace
multiline_comment|/* IRQ PACKET                         */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x22 or 0x23           */
DECL|member|IRQMask
r_int
r_char
id|IRQMask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* bit(0) is IRQ0, ...;               */
multiline_comment|/* bit(0) is IRQ8 ...                 */
DECL|member|IRQInfo
r_int
r_char
id|IRQInfo
suffix:semicolon
multiline_comment|/* optional; assume bit(0)=1; else    */
multiline_comment|/*  bit(0) - high true edge sensitive */
multiline_comment|/*  bit(1) - low true edge sensitive  */
multiline_comment|/*  bit(2) - high true level sensitive*/
multiline_comment|/*  bit(3) - low true level sensitive */
multiline_comment|/*  bit(7:4) - must be 0              */
DECL|member|S4_Pack
)brace
id|S4_Pack
suffix:semicolon
DECL|struct|_S5_Pack
r_struct
id|_S5_Pack
(brace
multiline_comment|/* DMA PACKET                         */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x2a                   */
DECL|member|DMAMask
r_int
r_char
id|DMAMask
suffix:semicolon
multiline_comment|/* bit(0) is channel 0 ...            */
DECL|member|DMAInfo
r_int
r_char
id|DMAInfo
suffix:semicolon
DECL|member|S5_Pack
)brace
id|S5_Pack
suffix:semicolon
DECL|struct|_S6_Pack
r_struct
id|_S6_Pack
(brace
multiline_comment|/* START DEPENDENT FUNCTION PACKET    */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x30 or 0x31           */
DECL|member|Priority
r_int
r_char
id|Priority
suffix:semicolon
multiline_comment|/* Optional; if missing then x01; else*/
multiline_comment|/*  x00 = best possible               */
multiline_comment|/*  x01 = acceptible                  */
multiline_comment|/*  x02 = sub-optimal but functional  */
DECL|member|S6_Pack
)brace
id|S6_Pack
suffix:semicolon
DECL|struct|_S7_Pack
r_struct
id|_S7_Pack
(brace
multiline_comment|/* END DEPENDENT FUNCTION PACKET      */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x38                   */
DECL|member|S7_Pack
)brace
id|S7_Pack
suffix:semicolon
DECL|struct|_S8_Pack
r_struct
id|_S8_Pack
(brace
multiline_comment|/* VARIABLE I/O PORT PACKET           */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag x47                      */
DECL|member|IOInfo
r_int
r_char
id|IOInfo
suffix:semicolon
multiline_comment|/* x0  = decode only bits(9:0);       */
DECL|macro|ISAAddr16bit
mdefine_line|#define  ISAAddr16bit         0x01      /* x01 = decode bits(15:0)            */
DECL|member|RangeMin
r_int
r_char
id|RangeMin
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Min base address                   */
DECL|member|RangeMax
r_int
r_char
id|RangeMax
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Max base address                   */
DECL|member|IOAlign
r_int
r_char
id|IOAlign
suffix:semicolon
multiline_comment|/* base alignmt, incr in 1B blocks    */
DECL|member|IONum
r_int
r_char
id|IONum
suffix:semicolon
multiline_comment|/* number of contiguous I/O ports     */
DECL|member|S8_Pack
)brace
id|S8_Pack
suffix:semicolon
DECL|struct|_S9_Pack
r_struct
id|_S9_Pack
(brace
multiline_comment|/* FIXED I/O PORT PACKET              */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x4b                   */
DECL|member|Range
r_int
r_char
id|Range
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* base address 10 bits               */
DECL|member|IONum
r_int
r_char
id|IONum
suffix:semicolon
multiline_comment|/* number of contiguous I/O ports     */
DECL|member|S9_Pack
)brace
id|S9_Pack
suffix:semicolon
DECL|struct|_S14_Pack
r_struct
id|_S14_Pack
(brace
multiline_comment|/* VENDOR DEFINED PACKET              */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x7m m = 1-7           */
DECL|union|_S14_Data
r_union
id|_S14_Data
(brace
DECL|member|Data
r_int
r_char
id|Data
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* Vendor defined                     */
DECL|struct|_S14_PPCPack
r_struct
id|_S14_PPCPack
(brace
multiline_comment|/* Pr*p s14 pack                      */
DECL|member|Type
r_int
r_char
id|Type
suffix:semicolon
multiline_comment|/* 00=non-IBM                         */
DECL|member|PPCData
r_int
r_char
id|PPCData
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Vendor defined                     */
DECL|member|S14_PPCPack
)brace
id|S14_PPCPack
suffix:semicolon
DECL|member|S14_Data
)brace
id|S14_Data
suffix:semicolon
DECL|member|S14_Pack
)brace
id|S14_Pack
suffix:semicolon
DECL|struct|_S15_Pack
r_struct
id|_S15_Pack
(brace
multiline_comment|/* END PACKET                         */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* small tag = 0x78 or 0x79           */
DECL|member|Check
r_int
r_char
id|Check
suffix:semicolon
multiline_comment|/* optional - checksum                */
DECL|member|S15_Pack
)brace
id|S15_Pack
suffix:semicolon
DECL|struct|_L1_Pack
r_struct
id|_L1_Pack
(brace
multiline_comment|/* MEMORY RANGE PACKET                */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* large tag = 0x81                   */
DECL|member|Count0
r_int
r_char
id|Count0
suffix:semicolon
multiline_comment|/* x09                                */
DECL|member|Count1
r_int
r_char
id|Count1
suffix:semicolon
multiline_comment|/* x00                                */
DECL|member|Data
r_int
r_char
id|Data
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* a variable array of bytes,         */
multiline_comment|/* count in tag                       */
DECL|member|L1_Pack
)brace
id|L1_Pack
suffix:semicolon
DECL|struct|_L2_Pack
r_struct
id|_L2_Pack
(brace
multiline_comment|/* ANSI ID STRING PACKET              */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* large tag = 0x82                   */
DECL|member|Count0
r_int
r_char
id|Count0
suffix:semicolon
multiline_comment|/* Length of string                   */
DECL|member|Count1
r_int
r_char
id|Count1
suffix:semicolon
DECL|member|Identifier
r_int
r_char
id|Identifier
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* a variable array of bytes,         */
multiline_comment|/* count in tag                       */
DECL|member|L2_Pack
)brace
id|L2_Pack
suffix:semicolon
DECL|struct|_L3_Pack
r_struct
id|_L3_Pack
(brace
multiline_comment|/* UNICODE ID STRING PACKET           */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* large tag = 0x83                   */
DECL|member|Count0
r_int
r_char
id|Count0
suffix:semicolon
multiline_comment|/* Length + 2 of string               */
DECL|member|Count1
r_int
r_char
id|Count1
suffix:semicolon
DECL|member|Country0
r_int
r_char
id|Country0
suffix:semicolon
multiline_comment|/* TBD                                */
DECL|member|Country1
r_int
r_char
id|Country1
suffix:semicolon
multiline_comment|/* TBD                                */
DECL|member|Identifier
r_int
r_char
id|Identifier
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* a variable array of bytes,         */
multiline_comment|/* count in tag                       */
DECL|member|L3_Pack
)brace
id|L3_Pack
suffix:semicolon
DECL|struct|_L4_Pack
r_struct
id|_L4_Pack
(brace
multiline_comment|/* VENDOR DEFINED PACKET              */
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* large tag = 0x84                   */
DECL|member|Count0
r_int
r_char
id|Count0
suffix:semicolon
DECL|member|Count1
r_int
r_char
id|Count1
suffix:semicolon
DECL|union|_L4_Data
r_union
id|_L4_Data
(brace
DECL|member|Data
r_int
r_char
id|Data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* a variable array of bytes,         */
multiline_comment|/* count in tag                       */
DECL|struct|_L4_PPCPack
r_struct
id|_L4_PPCPack
(brace
multiline_comment|/* Pr*p L4 packet                     */
DECL|member|Type
r_int
r_char
id|Type
suffix:semicolon
multiline_comment|/* 00=non-IBM                         */
DECL|member|PPCData
r_int
r_char
id|PPCData
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* a variable array of bytes,         */
multiline_comment|/* count in tag                       */
DECL|member|L4_PPCPack
)brace
id|L4_PPCPack
suffix:semicolon
DECL|member|L4_Data
)brace
id|L4_Data
suffix:semicolon
DECL|member|L4_Pack
)brace
id|L4_Pack
suffix:semicolon
DECL|struct|_L5_Pack
r_struct
id|_L5_Pack
(brace
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* large tag = 0x85                   */
DECL|member|Count0
r_int
r_char
id|Count0
suffix:semicolon
multiline_comment|/* Count = 17                         */
DECL|member|Count1
r_int
r_char
id|Count1
suffix:semicolon
DECL|member|Data
r_int
r_char
id|Data
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|L5_Pack
)brace
id|L5_Pack
suffix:semicolon
DECL|struct|_L6_Pack
r_struct
id|_L6_Pack
(brace
DECL|member|Tag
r_int
r_char
id|Tag
suffix:semicolon
multiline_comment|/* large tag = 0x86                   */
DECL|member|Count0
r_int
r_char
id|Count0
suffix:semicolon
multiline_comment|/* Count = 9                          */
DECL|member|Count1
r_int
r_char
id|Count1
suffix:semicolon
DECL|member|Data
r_int
r_char
id|Data
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|L6_Pack
)brace
id|L6_Pack
suffix:semicolon
DECL|typedef|PnP_TAG_PACKET
)brace
id|PnP_TAG_PACKET
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif  /* ndef _PNP_ */
macro_line|#endif /* __KERNEL__ */
eof
