multiline_comment|/*&n; * BK Id: SCCS/s.residual.h 1.8 08/09/01 09:11:24 trini&n; */
multiline_comment|/* 7/18/95                                                                    */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*      Residual Data header definitions and prototypes                       */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/* Structure map for RESIDUAL on PowerPC Reference Platform                   */
multiline_comment|/* residual.h - Residual data structure passed in r3.                         */
multiline_comment|/*              Load point passed in r4 to boot image.                        */
multiline_comment|/* For enum&squot;s: if given in hex then they are bit significant,                 */
multiline_comment|/*             i.e. only one bit is on for each enum                          */
multiline_comment|/* Reserved fields must be filled with zeros.                                */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _RESIDUAL_
DECL|macro|_RESIDUAL_
mdefine_line|#define _RESIDUAL_
macro_line|#ifndef __ASSEMBLY__
DECL|macro|MAX_CPUS
mdefine_line|#define MAX_CPUS 32                     /* These should be set to the maximum */
DECL|macro|MAX_MEMS
mdefine_line|#define MAX_MEMS 64                     /* number possible for this system.   */
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES 256                 /* Changing these will change the     */
DECL|macro|AVE_PNP_SIZE
mdefine_line|#define AVE_PNP_SIZE 32                 /* structure, hence the version of    */
DECL|macro|MAX_MEM_SEGS
mdefine_line|#define MAX_MEM_SEGS 64                 /* this header file.                  */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*               Public structures...                                         */
multiline_comment|/*----------------------------------------------------------------------------*/
macro_line|#include &lt;asm/pnp.h&gt;
DECL|enum|_L1CACHE_TYPE
r_typedef
r_enum
id|_L1CACHE_TYPE
(brace
DECL|enumerator|NoneCAC
id|NoneCAC
op_assign
l_int|0
comma
DECL|enumerator|SplitCAC
id|SplitCAC
op_assign
l_int|1
comma
DECL|enumerator|CombinedCAC
id|CombinedCAC
op_assign
l_int|2
DECL|typedef|L1CACHE_TYPE
)brace
id|L1CACHE_TYPE
suffix:semicolon
DECL|enum|_TLB_TYPE
r_typedef
r_enum
id|_TLB_TYPE
(brace
DECL|enumerator|NoneTLB
id|NoneTLB
op_assign
l_int|0
comma
DECL|enumerator|SplitTLB
id|SplitTLB
op_assign
l_int|1
comma
DECL|enumerator|CombinedTLB
id|CombinedTLB
op_assign
l_int|2
DECL|typedef|TLB_TYPE
)brace
id|TLB_TYPE
suffix:semicolon
DECL|enum|_FIRMWARE_SUPPORT
r_typedef
r_enum
id|_FIRMWARE_SUPPORT
(brace
DECL|enumerator|Conventional
id|Conventional
op_assign
l_int|0x01
comma
DECL|enumerator|OpenFirmware
id|OpenFirmware
op_assign
l_int|0x02
comma
DECL|enumerator|Diagnostics
id|Diagnostics
op_assign
l_int|0x04
comma
DECL|enumerator|LowDebug
id|LowDebug
op_assign
l_int|0x08
comma
DECL|enumerator|Multiboot
id|Multiboot
op_assign
l_int|0x10
comma
DECL|enumerator|LowClient
id|LowClient
op_assign
l_int|0x20
comma
DECL|enumerator|Hex41
id|Hex41
op_assign
l_int|0x40
comma
DECL|enumerator|FAT
id|FAT
op_assign
l_int|0x80
comma
DECL|enumerator|ISO9660
id|ISO9660
op_assign
l_int|0x0100
comma
DECL|enumerator|SCSI_InitiatorID_Override
id|SCSI_InitiatorID_Override
op_assign
l_int|0x0200
comma
DECL|enumerator|Tape_Boot
id|Tape_Boot
op_assign
l_int|0x0400
comma
DECL|enumerator|FW_Boot_Path
id|FW_Boot_Path
op_assign
l_int|0x0800
DECL|typedef|FIRMWARE_SUPPORT
)brace
id|FIRMWARE_SUPPORT
suffix:semicolon
DECL|enum|_FIRMWARE_SUPPLIERS
r_typedef
r_enum
id|_FIRMWARE_SUPPLIERS
(brace
DECL|enumerator|IBMFirmware
id|IBMFirmware
op_assign
l_int|0x00
comma
DECL|enumerator|MotoFirmware
id|MotoFirmware
op_assign
l_int|0x01
comma
multiline_comment|/* 7/18/95                            */
DECL|enumerator|FirmWorks
id|FirmWorks
op_assign
l_int|0x02
comma
multiline_comment|/* 10/5/95                            */
DECL|enumerator|Bull
id|Bull
op_assign
l_int|0x03
comma
multiline_comment|/* 04/03/96                           */
DECL|typedef|FIRMWARE_SUPPLIERS
)brace
id|FIRMWARE_SUPPLIERS
suffix:semicolon
DECL|enum|_ENDIAN_SWITCH_METHODS
r_typedef
r_enum
id|_ENDIAN_SWITCH_METHODS
(brace
DECL|enumerator|UsePort92
id|UsePort92
op_assign
l_int|0x01
comma
DECL|enumerator|UsePCIConfigA8
id|UsePCIConfigA8
op_assign
l_int|0x02
comma
DECL|enumerator|UseFF001030
id|UseFF001030
op_assign
l_int|0x03
comma
DECL|typedef|ENDIAN_SWITCH_METHODS
)brace
id|ENDIAN_SWITCH_METHODS
suffix:semicolon
DECL|enum|_SPREAD_IO_METHODS
r_typedef
r_enum
id|_SPREAD_IO_METHODS
(brace
DECL|enumerator|UsePort850
id|UsePort850
op_assign
l_int|0x00
comma
multiline_comment|/*UsePCIConfigA8 = 0x02,*/
DECL|typedef|SPREAD_IO_METHODS
)brace
id|SPREAD_IO_METHODS
suffix:semicolon
DECL|struct|_VPD
r_typedef
r_struct
id|_VPD
(brace
multiline_comment|/* Box dependent stuff */
DECL|member|PrintableModel
r_int
r_char
id|PrintableModel
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Null terminated string.&n;                                           Must be of the form:&n;                                           vvv,&lt;20h&gt;,&lt;model designation&gt;,&lt;0x0&gt;&n;                                           where vvv is the vendor ID&n;                                           e.g. IBM PPS MODEL 6015&lt;0x0&gt;       */
DECL|member|Serial
r_int
r_char
id|Serial
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 12/94:&n;                                           Serial Number; must be of the form:&n;                                           vvv&lt;serial number&gt; where vvv is the&n;                                           vendor ID.&n;                                           e.g. IBM60151234567&lt;20h&gt;&lt;20h&gt;      */
DECL|member|Reserved
r_int
r_char
id|Reserved
(braket
l_int|48
)braket
suffix:semicolon
DECL|member|FirmwareSupplier
r_int
r_int
id|FirmwareSupplier
suffix:semicolon
multiline_comment|/* See FirmwareSuppliers enum         */
DECL|member|FirmwareSupports
r_int
r_int
id|FirmwareSupports
suffix:semicolon
multiline_comment|/* See FirmwareSupport enum           */
DECL|member|NvramSize
r_int
r_int
id|NvramSize
suffix:semicolon
multiline_comment|/* Size of nvram in bytes             */
DECL|member|NumSIMMSlots
r_int
r_int
id|NumSIMMSlots
suffix:semicolon
DECL|member|EndianSwitchMethod
r_int
r_int
id|EndianSwitchMethod
suffix:semicolon
multiline_comment|/* See EndianSwitchMethods enum       */
DECL|member|SpreadIOMethod
r_int
r_int
id|SpreadIOMethod
suffix:semicolon
multiline_comment|/* See SpreadIOMethods enum           */
DECL|member|SmpIar
r_int
r_int
id|SmpIar
suffix:semicolon
DECL|member|RAMErrLogOffset
r_int
r_int
id|RAMErrLogOffset
suffix:semicolon
multiline_comment|/* Heap offset to error log           */
DECL|member|Reserved5
r_int
r_int
id|Reserved5
suffix:semicolon
DECL|member|Reserved6
r_int
r_int
id|Reserved6
suffix:semicolon
DECL|member|ProcessorHz
r_int
r_int
id|ProcessorHz
suffix:semicolon
multiline_comment|/* Processor clock frequency in Hertz */
DECL|member|ProcessorBusHz
r_int
r_int
id|ProcessorBusHz
suffix:semicolon
multiline_comment|/* Processor bus clock frequency      */
DECL|member|Reserved7
r_int
r_int
id|Reserved7
suffix:semicolon
DECL|member|TimeBaseDivisor
r_int
r_int
id|TimeBaseDivisor
suffix:semicolon
multiline_comment|/* (Bus clocks per timebase tic)*1000 */
DECL|member|WordWidth
r_int
r_int
id|WordWidth
suffix:semicolon
multiline_comment|/* Word width in bits                 */
DECL|member|PageSize
r_int
r_int
id|PageSize
suffix:semicolon
multiline_comment|/* Page size in bytes                 */
DECL|member|CoherenceBlockSize
r_int
r_int
id|CoherenceBlockSize
suffix:semicolon
multiline_comment|/* Unit of transfer in/out of cache&n;                                           for which coherency is maintained;&n;                                           normally &lt;= CacheLineSize.         */
DECL|member|GranuleSize
r_int
r_int
id|GranuleSize
suffix:semicolon
multiline_comment|/* Unit of lock allocation to avoid   */
multiline_comment|/*   false sharing of locks.          */
multiline_comment|/* L1 Cache variables */
DECL|member|CacheSize
r_int
r_int
id|CacheSize
suffix:semicolon
multiline_comment|/* L1 Cache size in KB. This is the   */
multiline_comment|/*   total size of the L1, whether    */
multiline_comment|/*   combined or split                */
DECL|member|CacheAttrib
r_int
r_int
id|CacheAttrib
suffix:semicolon
multiline_comment|/* L1CACHE_TYPE                       */
DECL|member|CacheAssoc
r_int
r_int
id|CacheAssoc
suffix:semicolon
multiline_comment|/* L1 Cache associativity. Use this&n;                                           for combined cache. If split, put&n;                                           zeros here.                        */
DECL|member|CacheLineSize
r_int
r_int
id|CacheLineSize
suffix:semicolon
multiline_comment|/* L1 Cache line size in bytes. Use&n;                                           for combined cache. If split, put&n;                                           zeros here.                        */
multiline_comment|/* For split L1 Cache: (= combined if combined cache) */
DECL|member|I_CacheSize
r_int
r_int
id|I_CacheSize
suffix:semicolon
DECL|member|I_CacheAssoc
r_int
r_int
id|I_CacheAssoc
suffix:semicolon
DECL|member|I_CacheLineSize
r_int
r_int
id|I_CacheLineSize
suffix:semicolon
DECL|member|D_CacheSize
r_int
r_int
id|D_CacheSize
suffix:semicolon
DECL|member|D_CacheAssoc
r_int
r_int
id|D_CacheAssoc
suffix:semicolon
DECL|member|D_CacheLineSize
r_int
r_int
id|D_CacheLineSize
suffix:semicolon
multiline_comment|/* Translation Lookaside Buffer variables */
DECL|member|TLBSize
r_int
r_int
id|TLBSize
suffix:semicolon
multiline_comment|/* Total number of TLBs on the system */
DECL|member|TLBAttrib
r_int
r_int
id|TLBAttrib
suffix:semicolon
multiline_comment|/* Combined I+D or split TLB          */
DECL|member|TLBAssoc
r_int
r_int
id|TLBAssoc
suffix:semicolon
multiline_comment|/* TLB Associativity. Use this for&n;                                           combined TLB. If split, put zeros&n;                                           here.                              */
multiline_comment|/* For split TLB: (= combined if combined TLB) */
DECL|member|I_TLBSize
r_int
r_int
id|I_TLBSize
suffix:semicolon
DECL|member|I_TLBAssoc
r_int
r_int
id|I_TLBAssoc
suffix:semicolon
DECL|member|D_TLBSize
r_int
r_int
id|D_TLBSize
suffix:semicolon
DECL|member|D_TLBAssoc
r_int
r_int
id|D_TLBAssoc
suffix:semicolon
DECL|member|ExtendedVPD
r_int
r_int
id|ExtendedVPD
suffix:semicolon
multiline_comment|/* Offset to extended VPD area;&n;                                           null if unused                     */
DECL|typedef|VPD
)brace
id|VPD
suffix:semicolon
DECL|enum|_DEVICE_FLAGS
r_typedef
r_enum
id|_DEVICE_FLAGS
(brace
DECL|enumerator|Enabled
id|Enabled
op_assign
l_int|0x4000
comma
multiline_comment|/* 1 - PCI device is enabled          */
DECL|enumerator|Integrated
id|Integrated
op_assign
l_int|0x2000
comma
DECL|enumerator|Failed
id|Failed
op_assign
l_int|0x1000
comma
multiline_comment|/* 1 - device failed POST code tests  */
DECL|enumerator|Static
id|Static
op_assign
l_int|0x0800
comma
multiline_comment|/* 0 - dynamically configurable&n;                                           1 - static                         */
DECL|enumerator|Dock
id|Dock
op_assign
l_int|0x0400
comma
multiline_comment|/* 0 - not a docking station device&n;                                           1 - is a docking station device    */
DECL|enumerator|Boot
id|Boot
op_assign
l_int|0x0200
comma
multiline_comment|/* 0 - device cannot be used for BOOT&n;                                           1 - can be a BOOT device           */
DECL|enumerator|Configurable
id|Configurable
op_assign
l_int|0x0100
comma
multiline_comment|/* 1 - device is configurable         */
DECL|enumerator|Disableable
id|Disableable
op_assign
l_int|0x80
comma
multiline_comment|/* 1 - device can be disabled         */
DECL|enumerator|PowerManaged
id|PowerManaged
op_assign
l_int|0x40
comma
multiline_comment|/* 0 - not managed; 1 - managed       */
DECL|enumerator|ReadOnly
id|ReadOnly
op_assign
l_int|0x20
comma
multiline_comment|/* 1 - device is read only            */
DECL|enumerator|Removable
id|Removable
op_assign
l_int|0x10
comma
multiline_comment|/* 1 - device is removable            */
DECL|enumerator|ConsoleIn
id|ConsoleIn
op_assign
l_int|0x08
comma
DECL|enumerator|ConsoleOut
id|ConsoleOut
op_assign
l_int|0x04
comma
DECL|enumerator|Input
id|Input
op_assign
l_int|0x02
comma
DECL|enumerator|Output
id|Output
op_assign
l_int|0x01
DECL|typedef|DEVICE_FLAGS
)brace
id|DEVICE_FLAGS
suffix:semicolon
DECL|enum|_BUS_ID
r_typedef
r_enum
id|_BUS_ID
(brace
DECL|enumerator|ISADEVICE
id|ISADEVICE
op_assign
l_int|0x01
comma
DECL|enumerator|EISADEVICE
id|EISADEVICE
op_assign
l_int|0x02
comma
DECL|enumerator|PCIDEVICE
id|PCIDEVICE
op_assign
l_int|0x04
comma
DECL|enumerator|PCMCIADEVICE
id|PCMCIADEVICE
op_assign
l_int|0x08
comma
DECL|enumerator|PNPISADEVICE
id|PNPISADEVICE
op_assign
l_int|0x10
comma
DECL|enumerator|MCADEVICE
id|MCADEVICE
op_assign
l_int|0x20
comma
DECL|enumerator|MXDEVICE
id|MXDEVICE
op_assign
l_int|0x40
comma
multiline_comment|/* Devices on mezzanine bus           */
DECL|enumerator|PROCESSORDEVICE
id|PROCESSORDEVICE
op_assign
l_int|0x80
comma
multiline_comment|/* Devices on processor bus           */
DECL|enumerator|VMEDEVICE
id|VMEDEVICE
op_assign
l_int|0x100
comma
DECL|typedef|BUS_ID
)brace
id|BUS_ID
suffix:semicolon
DECL|struct|_DEVICE_ID
r_typedef
r_struct
id|_DEVICE_ID
(brace
DECL|member|BusId
r_int
r_int
id|BusId
suffix:semicolon
multiline_comment|/* See BUS_ID enum above              */
DECL|member|DevId
r_int
r_int
id|DevId
suffix:semicolon
multiline_comment|/* Big Endian format                  */
DECL|member|SerialNum
r_int
r_int
id|SerialNum
suffix:semicolon
multiline_comment|/* For multiple usage of a single&n;                                           DevId                              */
DECL|member|Flags
r_int
r_int
id|Flags
suffix:semicolon
multiline_comment|/* See DEVICE_FLAGS enum above        */
DECL|member|BaseType
r_int
r_char
id|BaseType
suffix:semicolon
multiline_comment|/* See pnp.h for bit definitions      */
DECL|member|SubType
r_int
r_char
id|SubType
suffix:semicolon
multiline_comment|/* See pnp.h for bit definitions      */
DECL|member|Interface
r_int
r_char
id|Interface
suffix:semicolon
multiline_comment|/* See pnp.h for bit definitions      */
DECL|member|Spare
r_int
r_char
id|Spare
suffix:semicolon
DECL|typedef|DEVICE_ID
)brace
id|DEVICE_ID
suffix:semicolon
DECL|union|_BUS_ACCESS
r_typedef
r_union
id|_BUS_ACCESS
(brace
DECL|struct|_PnPAccess
r_struct
id|_PnPAccess
(brace
DECL|member|CSN
r_int
r_char
id|CSN
suffix:semicolon
DECL|member|LogicalDevNumber
r_int
r_char
id|LogicalDevNumber
suffix:semicolon
DECL|member|ReadDataPort
r_int
r_int
id|ReadDataPort
suffix:semicolon
DECL|member|PnPAccess
)brace
id|PnPAccess
suffix:semicolon
DECL|struct|_ISAAccess
r_struct
id|_ISAAccess
(brace
DECL|member|SlotNumber
r_int
r_char
id|SlotNumber
suffix:semicolon
multiline_comment|/* ISA Slot Number generally not&n;                                           available; 0 if unknown            */
DECL|member|LogicalDevNumber
r_int
r_char
id|LogicalDevNumber
suffix:semicolon
DECL|member|ISAReserved
r_int
r_int
id|ISAReserved
suffix:semicolon
DECL|member|ISAAccess
)brace
id|ISAAccess
suffix:semicolon
DECL|struct|_MCAAccess
r_struct
id|_MCAAccess
(brace
DECL|member|SlotNumber
r_int
r_char
id|SlotNumber
suffix:semicolon
DECL|member|LogicalDevNumber
r_int
r_char
id|LogicalDevNumber
suffix:semicolon
DECL|member|MCAReserved
r_int
r_int
id|MCAReserved
suffix:semicolon
DECL|member|MCAAccess
)brace
id|MCAAccess
suffix:semicolon
DECL|struct|_PCMCIAAccess
r_struct
id|_PCMCIAAccess
(brace
DECL|member|SlotNumber
r_int
r_char
id|SlotNumber
suffix:semicolon
DECL|member|LogicalDevNumber
r_int
r_char
id|LogicalDevNumber
suffix:semicolon
DECL|member|PCMCIAReserved
r_int
r_int
id|PCMCIAReserved
suffix:semicolon
DECL|member|PCMCIAAccess
)brace
id|PCMCIAAccess
suffix:semicolon
DECL|struct|_EISAAccess
r_struct
id|_EISAAccess
(brace
DECL|member|SlotNumber
r_int
r_char
id|SlotNumber
suffix:semicolon
DECL|member|FunctionNumber
r_int
r_char
id|FunctionNumber
suffix:semicolon
DECL|member|EISAReserved
r_int
r_int
id|EISAReserved
suffix:semicolon
DECL|member|EISAAccess
)brace
id|EISAAccess
suffix:semicolon
DECL|struct|_PCIAccess
r_struct
id|_PCIAccess
(brace
DECL|member|BusNumber
r_int
r_char
id|BusNumber
suffix:semicolon
DECL|member|DevFuncNumber
r_int
r_char
id|DevFuncNumber
suffix:semicolon
DECL|member|PCIReserved
r_int
r_int
id|PCIReserved
suffix:semicolon
DECL|member|PCIAccess
)brace
id|PCIAccess
suffix:semicolon
DECL|struct|_ProcBusAccess
r_struct
id|_ProcBusAccess
(brace
DECL|member|BusNumber
r_int
r_char
id|BusNumber
suffix:semicolon
DECL|member|BUID
r_int
r_char
id|BUID
suffix:semicolon
DECL|member|ProcBusReserved
r_int
r_int
id|ProcBusReserved
suffix:semicolon
DECL|member|ProcBusAccess
)brace
id|ProcBusAccess
suffix:semicolon
DECL|typedef|BUS_ACCESS
)brace
id|BUS_ACCESS
suffix:semicolon
multiline_comment|/* Per logical device information */
DECL|struct|_PPC_DEVICE
r_typedef
r_struct
id|_PPC_DEVICE
(brace
DECL|member|DeviceId
id|DEVICE_ID
id|DeviceId
suffix:semicolon
DECL|member|BusAccess
id|BUS_ACCESS
id|BusAccess
suffix:semicolon
multiline_comment|/* The following three are offsets into the DevicePnPHeap */
multiline_comment|/* All are in PnP compressed format                       */
DECL|member|AllocatedOffset
r_int
r_int
id|AllocatedOffset
suffix:semicolon
multiline_comment|/* Allocated resource description     */
DECL|member|PossibleOffset
r_int
r_int
id|PossibleOffset
suffix:semicolon
multiline_comment|/* Possible resource description      */
DECL|member|CompatibleOffset
r_int
r_int
id|CompatibleOffset
suffix:semicolon
multiline_comment|/* Compatible device identifiers      */
DECL|typedef|PPC_DEVICE
)brace
id|PPC_DEVICE
suffix:semicolon
DECL|enum|_CPU_STATE
r_typedef
r_enum
id|_CPU_STATE
(brace
DECL|enumerator|CPU_GOOD
id|CPU_GOOD
op_assign
l_int|0
comma
multiline_comment|/* CPU is present, and active         */
DECL|enumerator|CPU_GOOD_FW
id|CPU_GOOD_FW
op_assign
l_int|1
comma
multiline_comment|/* CPU is present, and in firmware    */
DECL|enumerator|CPU_OFF
id|CPU_OFF
op_assign
l_int|2
comma
multiline_comment|/* CPU is present, but inactive       */
DECL|enumerator|CPU_FAILED
id|CPU_FAILED
op_assign
l_int|3
comma
multiline_comment|/* CPU is present, but failed POST    */
DECL|enumerator|CPU_NOT_PRESENT
id|CPU_NOT_PRESENT
op_assign
l_int|255
multiline_comment|/* CPU not present                    */
DECL|typedef|CPU_STATE
)brace
id|CPU_STATE
suffix:semicolon
DECL|struct|_PPC_CPU
r_typedef
r_struct
id|_PPC_CPU
(brace
DECL|member|CpuType
r_int
r_int
id|CpuType
suffix:semicolon
multiline_comment|/* Result of mfspr from Processor&n;                                           Version Register (PVR).&n;                                           PVR(0-15) = Version (e.g. 601)&n;                                           PVR(16-31 = EC Level               */
DECL|member|CpuNumber
r_int
r_char
id|CpuNumber
suffix:semicolon
multiline_comment|/* CPU Number for this processor      */
DECL|member|CpuState
r_int
r_char
id|CpuState
suffix:semicolon
multiline_comment|/* CPU State, see CPU_STATE enum      */
DECL|member|Reserved
r_int
r_int
id|Reserved
suffix:semicolon
DECL|typedef|PPC_CPU
)brace
id|PPC_CPU
suffix:semicolon
DECL|struct|_PPC_MEM
r_typedef
r_struct
id|_PPC_MEM
(brace
DECL|member|SIMMSize
r_int
r_int
id|SIMMSize
suffix:semicolon
multiline_comment|/* 0 - absent or bad&n;                                           8M, 32M (in MB)                    */
DECL|typedef|PPC_MEM
)brace
id|PPC_MEM
suffix:semicolon
DECL|enum|_MEM_USAGE
r_typedef
r_enum
id|_MEM_USAGE
(brace
DECL|enumerator|Other
id|Other
op_assign
l_int|0x8000
comma
DECL|enumerator|ResumeBlock
id|ResumeBlock
op_assign
l_int|0x4000
comma
multiline_comment|/* for use by power management        */
DECL|enumerator|SystemROM
id|SystemROM
op_assign
l_int|0x2000
comma
multiline_comment|/* Flash memory (populated)           */
DECL|enumerator|UnPopSystemROM
id|UnPopSystemROM
op_assign
l_int|0x1000
comma
multiline_comment|/* Unpopulated part of SystemROM area */
DECL|enumerator|IOMemory
id|IOMemory
op_assign
l_int|0x0800
comma
DECL|enumerator|SystemIO
id|SystemIO
op_assign
l_int|0x0400
comma
DECL|enumerator|SystemRegs
id|SystemRegs
op_assign
l_int|0x0200
comma
DECL|enumerator|PCIAddr
id|PCIAddr
op_assign
l_int|0x0100
comma
DECL|enumerator|PCIConfig
id|PCIConfig
op_assign
l_int|0x80
comma
DECL|enumerator|ISAAddr
id|ISAAddr
op_assign
l_int|0x40
comma
DECL|enumerator|Unpopulated
id|Unpopulated
op_assign
l_int|0x20
comma
multiline_comment|/* Unpopulated part of System Memory  */
DECL|enumerator|Free
id|Free
op_assign
l_int|0x10
comma
multiline_comment|/* Free part of System Memory         */
DECL|enumerator|BootImage
id|BootImage
op_assign
l_int|0x08
comma
multiline_comment|/* BootImage part of System Memory    */
DECL|enumerator|FirmwareCode
id|FirmwareCode
op_assign
l_int|0x04
comma
multiline_comment|/* FirmwareCode part of System Memory */
DECL|enumerator|FirmwareHeap
id|FirmwareHeap
op_assign
l_int|0x02
comma
multiline_comment|/* FirmwareHeap part of System Memory */
DECL|enumerator|FirmwareStack
id|FirmwareStack
op_assign
l_int|0x01
multiline_comment|/* FirmwareStack part of System Memory*/
DECL|typedef|MEM_USAGE
)brace
id|MEM_USAGE
suffix:semicolon
DECL|struct|_MEM_MAP
r_typedef
r_struct
id|_MEM_MAP
(brace
DECL|member|Usage
r_int
r_int
id|Usage
suffix:semicolon
multiline_comment|/* See MEM_USAGE above                */
DECL|member|BasePage
r_int
r_int
id|BasePage
suffix:semicolon
multiline_comment|/* Page number measured in 4KB pages  */
DECL|member|PageCount
r_int
r_int
id|PageCount
suffix:semicolon
multiline_comment|/* Page count measured in 4KB pages   */
DECL|typedef|MEM_MAP
)brace
id|MEM_MAP
suffix:semicolon
DECL|struct|_RESIDUAL
r_typedef
r_struct
id|_RESIDUAL
(brace
DECL|member|ResidualLength
r_int
r_int
id|ResidualLength
suffix:semicolon
multiline_comment|/* Length of Residual                 */
DECL|member|Version
r_int
r_char
id|Version
suffix:semicolon
multiline_comment|/* of this data structure             */
DECL|member|Revision
r_int
r_char
id|Revision
suffix:semicolon
multiline_comment|/* of this data structure             */
DECL|member|EC
r_int
r_int
id|EC
suffix:semicolon
multiline_comment|/* of this data structure             */
multiline_comment|/* VPD */
DECL|member|VitalProductData
id|VPD
id|VitalProductData
suffix:semicolon
multiline_comment|/* CPU */
DECL|member|MaxNumCpus
r_int
r_int
id|MaxNumCpus
suffix:semicolon
multiline_comment|/* Max CPUs in this system            */
DECL|member|ActualNumCpus
r_int
r_int
id|ActualNumCpus
suffix:semicolon
multiline_comment|/* ActualNumCpus &lt; MaxNumCpus means   */
multiline_comment|/* that there are unpopulated or      */
multiline_comment|/* otherwise unusable cpu locations   */
DECL|member|Cpus
id|PPC_CPU
id|Cpus
(braket
id|MAX_CPUS
)braket
suffix:semicolon
multiline_comment|/* Memory */
DECL|member|TotalMemory
r_int
r_int
id|TotalMemory
suffix:semicolon
multiline_comment|/* Total amount of memory installed   */
DECL|member|GoodMemory
r_int
r_int
id|GoodMemory
suffix:semicolon
multiline_comment|/* Total amount of good memory        */
DECL|member|ActualNumMemSegs
r_int
r_int
id|ActualNumMemSegs
suffix:semicolon
DECL|member|Segs
id|MEM_MAP
id|Segs
(braket
id|MAX_MEM_SEGS
)braket
suffix:semicolon
DECL|member|ActualNumMemories
r_int
r_int
id|ActualNumMemories
suffix:semicolon
DECL|member|Memories
id|PPC_MEM
id|Memories
(braket
id|MAX_MEMS
)braket
suffix:semicolon
multiline_comment|/* Devices */
DECL|member|ActualNumDevices
r_int
r_int
id|ActualNumDevices
suffix:semicolon
DECL|member|Devices
id|PPC_DEVICE
id|Devices
(braket
id|MAX_DEVICES
)braket
suffix:semicolon
DECL|member|DevicePnPHeap
r_int
r_char
id|DevicePnPHeap
(braket
l_int|2
op_star
id|MAX_DEVICES
op_star
id|AVE_PNP_SIZE
)braket
suffix:semicolon
DECL|typedef|RESIDUAL
)brace
id|RESIDUAL
suffix:semicolon
r_extern
id|RESIDUAL
op_star
id|res
suffix:semicolon
r_extern
r_void
id|print_residual_device_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|PPC_DEVICE
op_star
id|residual_find_device
c_func
(paren
r_int
r_int
id|BusMask
comma
r_int
r_char
op_star
id|DevID
comma
r_int
id|BaseType
comma
r_int
id|SubType
comma
r_int
id|Interface
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
id|PnP_TAG_PACKET
op_star
id|PnP_find_packet
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_int
id|packet_tag
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
id|PnP_TAG_PACKET
op_star
id|PnP_find_small_vendor_packet
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_int
id|packet_type
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
id|PnP_TAG_PACKET
op_star
id|PnP_find_large_vendor_packet
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_int
id|packet_type
comma
r_int
id|n
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif  /* ndef _RESIDUAL_ */
macro_line|#endif /* __KERNEL__ */
eof
