multiline_comment|/*&n; *&t;$Id: pci.h,v 1.87 1998/10/11 15:13:12 mj Exp $&n; *&n; *&t;PCI defines and function prototypes&n; *&t;Copyright 1994, Drew Eckhardt&n; *&t;Copyright 1997--1999 Martin Mares &lt;mj@suse.cz&gt;&n; *&n; *&t;For more information, please consult the following manuals (look at&n; *&t;http://www.pcisig.com/ for how to get them):&n; *&n; *&t;PCI BIOS Specification&n; *&t;PCI Local Bus Specification&n; *&t;PCI to PCI Bridge Specification&n; *&t;PCI System Design Guide&n; */
macro_line|#ifndef LINUX_PCI_H
DECL|macro|LINUX_PCI_H
mdefine_line|#define LINUX_PCI_H
multiline_comment|/*&n; * Under PCI, each device has 256 bytes of configuration address space,&n; * of which the first 64 bytes are standardized as follows:&n; */
DECL|macro|PCI_VENDOR_ID
mdefine_line|#define PCI_VENDOR_ID&t;&t;0x00&t;/* 16 bits */
DECL|macro|PCI_DEVICE_ID
mdefine_line|#define PCI_DEVICE_ID&t;&t;0x02&t;/* 16 bits */
DECL|macro|PCI_COMMAND
mdefine_line|#define PCI_COMMAND&t;&t;0x04&t;/* 16 bits */
DECL|macro|PCI_COMMAND_IO
mdefine_line|#define  PCI_COMMAND_IO&t;&t;0x1&t;/* Enable response in I/O space */
DECL|macro|PCI_COMMAND_MEMORY
mdefine_line|#define  PCI_COMMAND_MEMORY&t;0x2&t;/* Enable response in Memory space */
DECL|macro|PCI_COMMAND_MASTER
mdefine_line|#define  PCI_COMMAND_MASTER&t;0x4&t;/* Enable bus mastering */
DECL|macro|PCI_COMMAND_SPECIAL
mdefine_line|#define  PCI_COMMAND_SPECIAL&t;0x8&t;/* Enable response to special cycles */
DECL|macro|PCI_COMMAND_INVALIDATE
mdefine_line|#define  PCI_COMMAND_INVALIDATE&t;0x10&t;/* Use memory write and invalidate */
DECL|macro|PCI_COMMAND_VGA_PALETTE
mdefine_line|#define  PCI_COMMAND_VGA_PALETTE 0x20&t;/* Enable palette snooping */
DECL|macro|PCI_COMMAND_PARITY
mdefine_line|#define  PCI_COMMAND_PARITY&t;0x40&t;/* Enable parity checking */
DECL|macro|PCI_COMMAND_WAIT
mdefine_line|#define  PCI_COMMAND_WAIT &t;0x80&t;/* Enable address/data stepping */
DECL|macro|PCI_COMMAND_SERR
mdefine_line|#define  PCI_COMMAND_SERR&t;0x100&t;/* Enable SERR */
DECL|macro|PCI_COMMAND_FAST_BACK
mdefine_line|#define  PCI_COMMAND_FAST_BACK&t;0x200&t;/* Enable back-to-back writes */
DECL|macro|PCI_STATUS
mdefine_line|#define PCI_STATUS&t;&t;0x06&t;/* 16 bits */
DECL|macro|PCI_STATUS_CAP_LIST
mdefine_line|#define  PCI_STATUS_CAP_LIST&t;0x10&t;/* Support Capability List */
DECL|macro|PCI_STATUS_66MHZ
mdefine_line|#define  PCI_STATUS_66MHZ&t;0x20&t;/* Support 66 Mhz PCI 2.1 bus */
DECL|macro|PCI_STATUS_UDF
mdefine_line|#define  PCI_STATUS_UDF&t;&t;0x40&t;/* Support User Definable Features [obsolete] */
DECL|macro|PCI_STATUS_FAST_BACK
mdefine_line|#define  PCI_STATUS_FAST_BACK&t;0x80&t;/* Accept fast-back to back */
DECL|macro|PCI_STATUS_PARITY
mdefine_line|#define  PCI_STATUS_PARITY&t;0x100&t;/* Detected parity error */
DECL|macro|PCI_STATUS_DEVSEL_MASK
mdefine_line|#define  PCI_STATUS_DEVSEL_MASK&t;0x600&t;/* DEVSEL timing */
DECL|macro|PCI_STATUS_DEVSEL_FAST
mdefine_line|#define  PCI_STATUS_DEVSEL_FAST&t;0x000&t;
DECL|macro|PCI_STATUS_DEVSEL_MEDIUM
mdefine_line|#define  PCI_STATUS_DEVSEL_MEDIUM 0x200
DECL|macro|PCI_STATUS_DEVSEL_SLOW
mdefine_line|#define  PCI_STATUS_DEVSEL_SLOW 0x400
DECL|macro|PCI_STATUS_SIG_TARGET_ABORT
mdefine_line|#define  PCI_STATUS_SIG_TARGET_ABORT 0x800 /* Set on target abort */
DECL|macro|PCI_STATUS_REC_TARGET_ABORT
mdefine_line|#define  PCI_STATUS_REC_TARGET_ABORT 0x1000 /* Master ack of &quot; */
DECL|macro|PCI_STATUS_REC_MASTER_ABORT
mdefine_line|#define  PCI_STATUS_REC_MASTER_ABORT 0x2000 /* Set on master abort */
DECL|macro|PCI_STATUS_SIG_SYSTEM_ERROR
mdefine_line|#define  PCI_STATUS_SIG_SYSTEM_ERROR 0x4000 /* Set when we drive SERR */
DECL|macro|PCI_STATUS_DETECTED_PARITY
mdefine_line|#define  PCI_STATUS_DETECTED_PARITY 0x8000 /* Set on parity error */
DECL|macro|PCI_CLASS_REVISION
mdefine_line|#define PCI_CLASS_REVISION&t;0x08&t;/* High 24 bits are class, low 8&n;&t;&t;&t;&t;&t;   revision */
DECL|macro|PCI_REVISION_ID
mdefine_line|#define PCI_REVISION_ID         0x08    /* Revision ID */
DECL|macro|PCI_CLASS_PROG
mdefine_line|#define PCI_CLASS_PROG          0x09    /* Reg. Level Programming Interface */
DECL|macro|PCI_CLASS_DEVICE
mdefine_line|#define PCI_CLASS_DEVICE        0x0a    /* Device class */
DECL|macro|PCI_CACHE_LINE_SIZE
mdefine_line|#define PCI_CACHE_LINE_SIZE&t;0x0c&t;/* 8 bits */
DECL|macro|PCI_LATENCY_TIMER
mdefine_line|#define PCI_LATENCY_TIMER&t;0x0d&t;/* 8 bits */
DECL|macro|PCI_HEADER_TYPE
mdefine_line|#define PCI_HEADER_TYPE&t;&t;0x0e&t;/* 8 bits */
DECL|macro|PCI_HEADER_TYPE_NORMAL
mdefine_line|#define  PCI_HEADER_TYPE_NORMAL&t;0
DECL|macro|PCI_HEADER_TYPE_BRIDGE
mdefine_line|#define  PCI_HEADER_TYPE_BRIDGE 1
DECL|macro|PCI_HEADER_TYPE_CARDBUS
mdefine_line|#define  PCI_HEADER_TYPE_CARDBUS 2
DECL|macro|PCI_BIST
mdefine_line|#define PCI_BIST&t;&t;0x0f&t;/* 8 bits */
DECL|macro|PCI_BIST_CODE_MASK
mdefine_line|#define PCI_BIST_CODE_MASK&t;0x0f&t;/* Return result */
DECL|macro|PCI_BIST_START
mdefine_line|#define PCI_BIST_START&t;&t;0x40&t;/* 1 to start BIST, 2 secs or less */
DECL|macro|PCI_BIST_CAPABLE
mdefine_line|#define PCI_BIST_CAPABLE&t;0x80&t;/* 1 if BIST capable */
multiline_comment|/*&n; * Base addresses specify locations in memory or I/O space.&n; * Decoded size can be determined by writing a value of &n; * 0xffffffff to the register, and reading it back.  Only &n; * 1 bits are decoded.&n; */
DECL|macro|PCI_BASE_ADDRESS_0
mdefine_line|#define PCI_BASE_ADDRESS_0&t;0x10&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_1
mdefine_line|#define PCI_BASE_ADDRESS_1&t;0x14&t;/* 32 bits [htype 0,1 only] */
DECL|macro|PCI_BASE_ADDRESS_2
mdefine_line|#define PCI_BASE_ADDRESS_2&t;0x18&t;/* 32 bits [htype 0 only] */
DECL|macro|PCI_BASE_ADDRESS_3
mdefine_line|#define PCI_BASE_ADDRESS_3&t;0x1c&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_4
mdefine_line|#define PCI_BASE_ADDRESS_4&t;0x20&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_5
mdefine_line|#define PCI_BASE_ADDRESS_5&t;0x24&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_SPACE
mdefine_line|#define  PCI_BASE_ADDRESS_SPACE&t;0x01&t;/* 0 = memory, 1 = I/O */
DECL|macro|PCI_BASE_ADDRESS_SPACE_IO
mdefine_line|#define  PCI_BASE_ADDRESS_SPACE_IO 0x01
DECL|macro|PCI_BASE_ADDRESS_SPACE_MEMORY
mdefine_line|#define  PCI_BASE_ADDRESS_SPACE_MEMORY 0x00
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_MASK 0x06
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_32
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_32&t;0x00&t;/* 32 bit address */
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_1M
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_1M&t;0x02&t;/* Below 1M [obsolete] */
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_64
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_64&t;0x04&t;/* 64 bit address */
DECL|macro|PCI_BASE_ADDRESS_MEM_PREFETCH
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_PREFETCH&t;0x08&t;/* prefetchable? */
DECL|macro|PCI_BASE_ADDRESS_MEM_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_MASK&t;(~0x0fUL)
DECL|macro|PCI_BASE_ADDRESS_IO_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_IO_MASK&t;(~0x03UL)
multiline_comment|/* bit 1 is reserved if address_space = 1 */
multiline_comment|/* Header type 0 (normal devices) */
DECL|macro|PCI_CARDBUS_CIS
mdefine_line|#define PCI_CARDBUS_CIS&t;&t;0x28
DECL|macro|PCI_SUBSYSTEM_VENDOR_ID
mdefine_line|#define PCI_SUBSYSTEM_VENDOR_ID&t;0x2c
DECL|macro|PCI_SUBSYSTEM_ID
mdefine_line|#define PCI_SUBSYSTEM_ID&t;0x2e  
DECL|macro|PCI_ROM_ADDRESS
mdefine_line|#define PCI_ROM_ADDRESS&t;&t;0x30&t;/* Bits 31..11 are address, 10..1 reserved */
DECL|macro|PCI_ROM_ADDRESS_ENABLE
mdefine_line|#define  PCI_ROM_ADDRESS_ENABLE&t;0x01
DECL|macro|PCI_ROM_ADDRESS_MASK
mdefine_line|#define PCI_ROM_ADDRESS_MASK&t;(~0x7ffUL)
DECL|macro|PCI_CAPABILITY_LIST
mdefine_line|#define PCI_CAPABILITY_LIST&t;0x34&t;/* Offset of first capability list entry */
multiline_comment|/* 0x35-0x3b are reserved */
DECL|macro|PCI_INTERRUPT_LINE
mdefine_line|#define PCI_INTERRUPT_LINE&t;0x3c&t;/* 8 bits */
DECL|macro|PCI_INTERRUPT_PIN
mdefine_line|#define PCI_INTERRUPT_PIN&t;0x3d&t;/* 8 bits */
DECL|macro|PCI_MIN_GNT
mdefine_line|#define PCI_MIN_GNT&t;&t;0x3e&t;/* 8 bits */
DECL|macro|PCI_MAX_LAT
mdefine_line|#define PCI_MAX_LAT&t;&t;0x3f&t;/* 8 bits */
multiline_comment|/* Header type 1 (PCI-to-PCI bridges) */
DECL|macro|PCI_PRIMARY_BUS
mdefine_line|#define PCI_PRIMARY_BUS&t;&t;0x18&t;/* Primary bus number */
DECL|macro|PCI_SECONDARY_BUS
mdefine_line|#define PCI_SECONDARY_BUS&t;0x19&t;/* Secondary bus number */
DECL|macro|PCI_SUBORDINATE_BUS
mdefine_line|#define PCI_SUBORDINATE_BUS&t;0x1a&t;/* Highest bus number behind the bridge */
DECL|macro|PCI_SEC_LATENCY_TIMER
mdefine_line|#define PCI_SEC_LATENCY_TIMER&t;0x1b&t;/* Latency timer for secondary interface */
DECL|macro|PCI_IO_BASE
mdefine_line|#define PCI_IO_BASE&t;&t;0x1c&t;/* I/O range behind the bridge */
DECL|macro|PCI_IO_LIMIT
mdefine_line|#define PCI_IO_LIMIT&t;&t;0x1d
DECL|macro|PCI_IO_RANGE_TYPE_MASK
mdefine_line|#define  PCI_IO_RANGE_TYPE_MASK&t;0x0f&t;/* I/O bridging type */
DECL|macro|PCI_IO_RANGE_TYPE_16
mdefine_line|#define  PCI_IO_RANGE_TYPE_16&t;0x00
DECL|macro|PCI_IO_RANGE_TYPE_32
mdefine_line|#define  PCI_IO_RANGE_TYPE_32&t;0x01
DECL|macro|PCI_IO_RANGE_MASK
mdefine_line|#define  PCI_IO_RANGE_MASK&t;~0x0f
DECL|macro|PCI_SEC_STATUS
mdefine_line|#define PCI_SEC_STATUS&t;&t;0x1e&t;/* Secondary status register, only bit 14 used */
DECL|macro|PCI_MEMORY_BASE
mdefine_line|#define PCI_MEMORY_BASE&t;&t;0x20&t;/* Memory range behind */
DECL|macro|PCI_MEMORY_LIMIT
mdefine_line|#define PCI_MEMORY_LIMIT&t;0x22
DECL|macro|PCI_MEMORY_RANGE_TYPE_MASK
mdefine_line|#define  PCI_MEMORY_RANGE_TYPE_MASK 0x0f
DECL|macro|PCI_MEMORY_RANGE_MASK
mdefine_line|#define  PCI_MEMORY_RANGE_MASK&t;~0x0f
DECL|macro|PCI_PREF_MEMORY_BASE
mdefine_line|#define PCI_PREF_MEMORY_BASE&t;0x24&t;/* Prefetchable memory range behind */
DECL|macro|PCI_PREF_MEMORY_LIMIT
mdefine_line|#define PCI_PREF_MEMORY_LIMIT&t;0x26
DECL|macro|PCI_PREF_RANGE_TYPE_MASK
mdefine_line|#define  PCI_PREF_RANGE_TYPE_MASK 0x0f
DECL|macro|PCI_PREF_RANGE_TYPE_32
mdefine_line|#define  PCI_PREF_RANGE_TYPE_32&t;0x00
DECL|macro|PCI_PREF_RANGE_TYPE_64
mdefine_line|#define  PCI_PREF_RANGE_TYPE_64&t;0x01
DECL|macro|PCI_PREF_RANGE_MASK
mdefine_line|#define  PCI_PREF_RANGE_MASK&t;~0x0f
DECL|macro|PCI_PREF_BASE_UPPER32
mdefine_line|#define PCI_PREF_BASE_UPPER32&t;0x28&t;/* Upper half of prefetchable memory range */
DECL|macro|PCI_PREF_LIMIT_UPPER32
mdefine_line|#define PCI_PREF_LIMIT_UPPER32&t;0x2c
DECL|macro|PCI_IO_BASE_UPPER16
mdefine_line|#define PCI_IO_BASE_UPPER16&t;0x30&t;/* Upper half of I/O addresses */
DECL|macro|PCI_IO_LIMIT_UPPER16
mdefine_line|#define PCI_IO_LIMIT_UPPER16&t;0x32
multiline_comment|/* 0x34 same as for htype 0 */
multiline_comment|/* 0x35-0x3b is reserved */
DECL|macro|PCI_ROM_ADDRESS1
mdefine_line|#define PCI_ROM_ADDRESS1&t;0x38&t;/* Same as PCI_ROM_ADDRESS, but for htype 1 */
multiline_comment|/* 0x3c-0x3d are same as for htype 0 */
DECL|macro|PCI_BRIDGE_CONTROL
mdefine_line|#define PCI_BRIDGE_CONTROL&t;0x3e
DECL|macro|PCI_BRIDGE_CTL_PARITY
mdefine_line|#define  PCI_BRIDGE_CTL_PARITY&t;0x01&t;/* Enable parity detection on secondary interface */
DECL|macro|PCI_BRIDGE_CTL_SERR
mdefine_line|#define  PCI_BRIDGE_CTL_SERR&t;0x02&t;/* The same for SERR forwarding */
DECL|macro|PCI_BRIDGE_CTL_NO_ISA
mdefine_line|#define  PCI_BRIDGE_CTL_NO_ISA&t;0x04&t;/* Disable bridging of ISA ports */
DECL|macro|PCI_BRIDGE_CTL_VGA
mdefine_line|#define  PCI_BRIDGE_CTL_VGA&t;0x08&t;/* Forward VGA addresses */
DECL|macro|PCI_BRIDGE_CTL_MASTER_ABORT
mdefine_line|#define  PCI_BRIDGE_CTL_MASTER_ABORT 0x20  /* Report master aborts */
DECL|macro|PCI_BRIDGE_CTL_BUS_RESET
mdefine_line|#define  PCI_BRIDGE_CTL_BUS_RESET 0x40&t;/* Secondary bus reset */
DECL|macro|PCI_BRIDGE_CTL_FAST_BACK
mdefine_line|#define  PCI_BRIDGE_CTL_FAST_BACK 0x80&t;/* Fast Back2Back enabled on secondary interface */
multiline_comment|/* Header type 2 (CardBus bridges) */
DECL|macro|PCI_CB_CAPABILITY_LIST
mdefine_line|#define PCI_CB_CAPABILITY_LIST&t;0x14
multiline_comment|/* 0x15 reserved */
DECL|macro|PCI_CB_SEC_STATUS
mdefine_line|#define PCI_CB_SEC_STATUS&t;0x16&t;/* Secondary status */
DECL|macro|PCI_CB_PRIMARY_BUS
mdefine_line|#define PCI_CB_PRIMARY_BUS&t;0x18&t;/* PCI bus number */
DECL|macro|PCI_CB_CARD_BUS
mdefine_line|#define PCI_CB_CARD_BUS&t;&t;0x19&t;/* CardBus bus number */
DECL|macro|PCI_CB_SUBORDINATE_BUS
mdefine_line|#define PCI_CB_SUBORDINATE_BUS&t;0x1a&t;/* Subordinate bus number */
DECL|macro|PCI_CB_LATENCY_TIMER
mdefine_line|#define PCI_CB_LATENCY_TIMER&t;0x1b&t;/* CardBus latency timer */
DECL|macro|PCI_CB_MEMORY_BASE_0
mdefine_line|#define PCI_CB_MEMORY_BASE_0&t;0x1c
DECL|macro|PCI_CB_MEMORY_LIMIT_0
mdefine_line|#define PCI_CB_MEMORY_LIMIT_0&t;0x20
DECL|macro|PCI_CB_MEMORY_BASE_1
mdefine_line|#define PCI_CB_MEMORY_BASE_1&t;0x24
DECL|macro|PCI_CB_MEMORY_LIMIT_1
mdefine_line|#define PCI_CB_MEMORY_LIMIT_1&t;0x28
DECL|macro|PCI_CB_IO_BASE_0
mdefine_line|#define PCI_CB_IO_BASE_0&t;0x2c
DECL|macro|PCI_CB_IO_BASE_0_HI
mdefine_line|#define PCI_CB_IO_BASE_0_HI&t;0x2e
DECL|macro|PCI_CB_IO_LIMIT_0
mdefine_line|#define PCI_CB_IO_LIMIT_0&t;0x30
DECL|macro|PCI_CB_IO_LIMIT_0_HI
mdefine_line|#define PCI_CB_IO_LIMIT_0_HI&t;0x32
DECL|macro|PCI_CB_IO_BASE_1
mdefine_line|#define PCI_CB_IO_BASE_1&t;0x34
DECL|macro|PCI_CB_IO_BASE_1_HI
mdefine_line|#define PCI_CB_IO_BASE_1_HI&t;0x36
DECL|macro|PCI_CB_IO_LIMIT_1
mdefine_line|#define PCI_CB_IO_LIMIT_1&t;0x38
DECL|macro|PCI_CB_IO_LIMIT_1_HI
mdefine_line|#define PCI_CB_IO_LIMIT_1_HI&t;0x3a
DECL|macro|PCI_CB_IO_RANGE_MASK
mdefine_line|#define  PCI_CB_IO_RANGE_MASK&t;~0x03
multiline_comment|/* 0x3c-0x3d are same as for htype 0 */
DECL|macro|PCI_CB_BRIDGE_CONTROL
mdefine_line|#define PCI_CB_BRIDGE_CONTROL&t;0x3e
DECL|macro|PCI_CB_BRIDGE_CTL_PARITY
mdefine_line|#define  PCI_CB_BRIDGE_CTL_PARITY&t;0x01&t;/* Similar to standard bridge control register */
DECL|macro|PCI_CB_BRIDGE_CTL_SERR
mdefine_line|#define  PCI_CB_BRIDGE_CTL_SERR&t;&t;0x02
DECL|macro|PCI_CB_BRIDGE_CTL_ISA
mdefine_line|#define  PCI_CB_BRIDGE_CTL_ISA&t;&t;0x04
DECL|macro|PCI_CB_BRIDGE_CTL_VGA
mdefine_line|#define  PCI_CB_BRIDGE_CTL_VGA&t;&t;0x08
DECL|macro|PCI_CB_BRIDGE_CTL_MASTER_ABORT
mdefine_line|#define  PCI_CB_BRIDGE_CTL_MASTER_ABORT&t;0x20
DECL|macro|PCI_CB_BRIDGE_CTL_CB_RESET
mdefine_line|#define  PCI_CB_BRIDGE_CTL_CB_RESET&t;0x40&t;/* CardBus reset */
DECL|macro|PCI_CB_BRIDGE_CTL_16BIT_INT
mdefine_line|#define  PCI_CB_BRIDGE_CTL_16BIT_INT&t;0x80&t;/* Enable interrupt for 16-bit cards */
DECL|macro|PCI_CB_BRIDGE_CTL_PREFETCH_MEM0
mdefine_line|#define  PCI_CB_BRIDGE_CTL_PREFETCH_MEM0 0x100&t;/* Prefetch enable for both memory regions */
DECL|macro|PCI_CB_BRIDGE_CTL_PREFETCH_MEM1
mdefine_line|#define  PCI_CB_BRIDGE_CTL_PREFETCH_MEM1 0x200
DECL|macro|PCI_CB_BRIDGE_CTL_POST_WRITES
mdefine_line|#define  PCI_CB_BRIDGE_CTL_POST_WRITES&t;0x400
DECL|macro|PCI_CB_SUBSYSTEM_VENDOR_ID
mdefine_line|#define PCI_CB_SUBSYSTEM_VENDOR_ID 0x40
DECL|macro|PCI_CB_SUBSYSTEM_ID
mdefine_line|#define PCI_CB_SUBSYSTEM_ID&t;0x42
DECL|macro|PCI_CB_LEGACY_MODE_BASE
mdefine_line|#define PCI_CB_LEGACY_MODE_BASE&t;0x44&t;/* 16-bit PC Card legacy mode base address (ExCa) */
multiline_comment|/* 0x48-0x7f reserved */
multiline_comment|/* Capability lists */
DECL|macro|PCI_CAP_LIST_ID
mdefine_line|#define PCI_CAP_LIST_ID&t;&t;0&t;/* Capability ID */
DECL|macro|PCI_CAP_ID_PM
mdefine_line|#define  PCI_CAP_ID_PM&t;&t;0x01&t;/* Power Management */
DECL|macro|PCI_CAP_ID_AGP
mdefine_line|#define  PCI_CAP_ID_AGP&t;&t;0x02&t;/* Accelerated Graphics Port */
DECL|macro|PCI_CAP_ID_VPD
mdefine_line|#define  PCI_CAP_ID_VPD&t;&t;0x03&t;/* Vital Product Data */
DECL|macro|PCI_CAP_ID_SLOTID
mdefine_line|#define  PCI_CAP_ID_SLOTID&t;0x04&t;/* Slot Identification */
DECL|macro|PCI_CAP_ID_MSI
mdefine_line|#define  PCI_CAP_ID_MSI&t;&t;0x05&t;/* Message Signalled Interrupts */
DECL|macro|PCI_CAP_ID_CHSWP
mdefine_line|#define  PCI_CAP_ID_CHSWP&t;0x06&t;/* CompactPCI HotSwap */
DECL|macro|PCI_CAP_LIST_NEXT
mdefine_line|#define PCI_CAP_LIST_NEXT&t;1&t;/* Next capability in the list */
DECL|macro|PCI_CAP_FLAGS
mdefine_line|#define PCI_CAP_FLAGS&t;&t;2&t;/* Capability defined flags (16 bits) */
DECL|macro|PCI_CAP_SIZEOF
mdefine_line|#define PCI_CAP_SIZEOF&t;&t;4
multiline_comment|/* Power Management Registers */
DECL|macro|PCI_PM_CAP_VER_MASK
mdefine_line|#define  PCI_PM_CAP_VER_MASK&t;0x0007&t;/* Version */
DECL|macro|PCI_PM_CAP_PME_CLOCK
mdefine_line|#define  PCI_PM_CAP_PME_CLOCK&t;0x0008&t;/* PME clock required */
DECL|macro|PCI_PM_CAP_AUX_POWER
mdefine_line|#define  PCI_PM_CAP_AUX_POWER&t;0x0010&t;/* Auxilliary power support */
DECL|macro|PCI_PM_CAP_DSI
mdefine_line|#define  PCI_PM_CAP_DSI&t;&t;0x0020&t;/* Device specific initialization */
DECL|macro|PCI_PM_CAP_D1
mdefine_line|#define  PCI_PM_CAP_D1&t;&t;0x0200&t;/* D1 power state support */
DECL|macro|PCI_PM_CAP_D2
mdefine_line|#define  PCI_PM_CAP_D2&t;&t;0x0400&t;/* D2 power state support */
DECL|macro|PCI_PM_CAP_PME
mdefine_line|#define  PCI_PM_CAP_PME&t;&t;0x0800&t;/* PME pin supported */
DECL|macro|PCI_PM_CTRL
mdefine_line|#define PCI_PM_CTRL&t;&t;4&t;/* PM control and status register */
DECL|macro|PCI_PM_CTRL_STATE_MASK
mdefine_line|#define  PCI_PM_CTRL_STATE_MASK&t;0x0003&t;/* Current power state (D0 to D3) */
DECL|macro|PCI_PM_CTRL_PME_ENABLE
mdefine_line|#define  PCI_PM_CTRL_PME_ENABLE&t;0x0100&t;/* PME pin enable */
DECL|macro|PCI_PM_CTRL_DATA_SEL_MASK
mdefine_line|#define  PCI_PM_CTRL_DATA_SEL_MASK&t;0x1e00&t;/* Data select (??) */
DECL|macro|PCI_PM_CTRL_DATA_SCALE_MASK
mdefine_line|#define  PCI_PM_CTRL_DATA_SCALE_MASK&t;0x6000&t;/* Data scale (??) */
DECL|macro|PCI_PM_CTRL_PME_STATUS
mdefine_line|#define  PCI_PM_CTRL_PME_STATUS&t;0x8000&t;/* PME pin status */
DECL|macro|PCI_PM_PPB_EXTENSIONS
mdefine_line|#define PCI_PM_PPB_EXTENSIONS&t;6&t;/* PPB support extensions (??) */
DECL|macro|PCI_PM_PPB_B2_B3
mdefine_line|#define  PCI_PM_PPB_B2_B3&t;0x40&t;/* Stop clock when in D3hot (??) */
DECL|macro|PCI_PM_BPCC_ENABLE
mdefine_line|#define  PCI_PM_BPCC_ENABLE&t;0x80&t;/* Bus power/clock control enable (??) */
DECL|macro|PCI_PM_DATA_REGISTER
mdefine_line|#define PCI_PM_DATA_REGISTER&t;7&t;/* (??) */
DECL|macro|PCI_PM_SIZEOF
mdefine_line|#define PCI_PM_SIZEOF&t;&t;8
multiline_comment|/* AGP registers */
DECL|macro|PCI_AGP_VERSION
mdefine_line|#define PCI_AGP_VERSION&t;&t;2&t;/* BCD version number */
DECL|macro|PCI_AGP_RFU
mdefine_line|#define PCI_AGP_RFU&t;&t;3&t;/* Rest of capability flags */
DECL|macro|PCI_AGP_STATUS
mdefine_line|#define PCI_AGP_STATUS&t;&t;4&t;/* Status register */
DECL|macro|PCI_AGP_STATUS_RQ_MASK
mdefine_line|#define  PCI_AGP_STATUS_RQ_MASK&t;0xff000000&t;/* Maximum number of requests - 1 */
DECL|macro|PCI_AGP_STATUS_SBA
mdefine_line|#define  PCI_AGP_STATUS_SBA&t;0x0200&t;/* Sideband addressing supported */
DECL|macro|PCI_AGP_STATUS_64BIT
mdefine_line|#define  PCI_AGP_STATUS_64BIT&t;0x0020&t;/* 64-bit addressing supported */
DECL|macro|PCI_AGP_STATUS_FW
mdefine_line|#define  PCI_AGP_STATUS_FW&t;0x0010&t;/* FW transfers supported */
DECL|macro|PCI_AGP_STATUS_RATE4
mdefine_line|#define  PCI_AGP_STATUS_RATE4&t;0x0004&t;/* 4x transfer rate supported */
DECL|macro|PCI_AGP_STATUS_RATE2
mdefine_line|#define  PCI_AGP_STATUS_RATE2&t;0x0002&t;/* 2x transfer rate supported */
DECL|macro|PCI_AGP_STATUS_RATE1
mdefine_line|#define  PCI_AGP_STATUS_RATE1&t;0x0001&t;/* 1x transfer rate supported */
DECL|macro|PCI_AGP_COMMAND
mdefine_line|#define PCI_AGP_COMMAND&t;&t;8&t;/* Control register */
DECL|macro|PCI_AGP_COMMAND_RQ_MASK
mdefine_line|#define  PCI_AGP_COMMAND_RQ_MASK 0xff000000  /* Master: Maximum number of requests */
DECL|macro|PCI_AGP_COMMAND_SBA
mdefine_line|#define  PCI_AGP_COMMAND_SBA&t;0x0200&t;/* Sideband addressing enabled */
DECL|macro|PCI_AGP_COMMAND_AGP
mdefine_line|#define  PCI_AGP_COMMAND_AGP&t;0x0100&t;/* Allow processing of AGP transactions */
DECL|macro|PCI_AGP_COMMAND_64BIT
mdefine_line|#define  PCI_AGP_COMMAND_64BIT&t;0x0020 &t;/* Allow processing of 64-bit addresses */
DECL|macro|PCI_AGP_COMMAND_FW
mdefine_line|#define  PCI_AGP_COMMAND_FW&t;0x0010 &t;/* Force FW transfers */
DECL|macro|PCI_AGP_COMMAND_RATE4
mdefine_line|#define  PCI_AGP_COMMAND_RATE4&t;0x0004&t;/* Use 4x rate */
DECL|macro|PCI_AGP_COMMAND_RATE2
mdefine_line|#define  PCI_AGP_COMMAND_RATE2&t;0x0002&t;/* Use 4x rate */
DECL|macro|PCI_AGP_COMMAND_RATE1
mdefine_line|#define  PCI_AGP_COMMAND_RATE1&t;0x0001&t;/* Use 4x rate */
DECL|macro|PCI_AGP_SIZEOF
mdefine_line|#define PCI_AGP_SIZEOF&t;&t;12
multiline_comment|/* Slot Identification */
DECL|macro|PCI_SID_ESR
mdefine_line|#define PCI_SID_ESR&t;&t;2&t;/* Expansion Slot Register */
DECL|macro|PCI_SID_ESR_NSLOTS
mdefine_line|#define  PCI_SID_ESR_NSLOTS&t;0x1f&t;/* Number of expansion slots available */
DECL|macro|PCI_SID_ESR_FIC
mdefine_line|#define  PCI_SID_ESR_FIC&t;0x20&t;/* First In Chassis Flag */
DECL|macro|PCI_SID_CHASSIS_NR
mdefine_line|#define PCI_SID_CHASSIS_NR&t;3&t;/* Chassis Number */
multiline_comment|/* Message Signalled Interrupts registers */
DECL|macro|PCI_MSI_FLAGS
mdefine_line|#define PCI_MSI_FLAGS&t;&t;2&t;/* Various flags */
DECL|macro|PCI_MSI_FLAGS_64BIT
mdefine_line|#define  PCI_MSI_FLAGS_64BIT&t;0x80&t;/* 64-bit addresses allowed */
DECL|macro|PCI_MSI_FLAGS_QSIZE
mdefine_line|#define  PCI_MSI_FLAGS_QSIZE&t;0x70&t;/* Message queue size configured */
DECL|macro|PCI_MSI_FLAGS_QMASK
mdefine_line|#define  PCI_MSI_FLAGS_QMASK&t;0x0e&t;/* Maximum queue size available */
DECL|macro|PCI_MSI_FLAGS_ENABLE
mdefine_line|#define  PCI_MSI_FLAGS_ENABLE&t;0x01&t;/* MSI feature enabled */
DECL|macro|PCI_MSI_RFU
mdefine_line|#define PCI_MSI_RFU&t;&t;3&t;/* Rest of capability flags */
DECL|macro|PCI_MSI_ADDRESS_LO
mdefine_line|#define PCI_MSI_ADDRESS_LO&t;4&t;/* Lower 32 bits */
DECL|macro|PCI_MSI_ADDRESS_HI
mdefine_line|#define PCI_MSI_ADDRESS_HI&t;8&t;/* Upper 32 bits (if PCI_MSI_FLAGS_64BIT set) */
DECL|macro|PCI_MSI_DATA_32
mdefine_line|#define PCI_MSI_DATA_32&t;&t;8&t;/* 16 bits of data for 32-bit devices */
DECL|macro|PCI_MSI_DATA_64
mdefine_line|#define PCI_MSI_DATA_64&t;&t;12&t;/* 16 bits of data for 64-bit devices */
multiline_comment|/* Include the ID list */
macro_line|#include &lt;linux/pci_ids.h&gt;
multiline_comment|/*&n; * The PCI interface treats multi-function devices as independent&n; * devices.  The slot/function address of each device is encoded&n; * in a single byte as follows:&n; *&n; *&t;7:3 = slot&n; *&t;2:0 = function&n; */
DECL|macro|PCI_DEVFN
mdefine_line|#define PCI_DEVFN(slot,func)&t;((((slot) &amp; 0x1f) &lt;&lt; 3) | ((func) &amp; 0x07))
DECL|macro|PCI_SLOT
mdefine_line|#define PCI_SLOT(devfn)&t;&t;(((devfn) &gt;&gt; 3) &amp; 0x1f)
DECL|macro|PCI_FUNC
mdefine_line|#define PCI_FUNC(devfn)&t;&t;((devfn) &amp; 0x07)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* This defines the direction arg to the DMA mapping routines. */
DECL|macro|PCI_DMA_BIDIRECTIONAL
mdefine_line|#define PCI_DMA_BIDIRECTIONAL&t;0
DECL|macro|PCI_DMA_TODEVICE
mdefine_line|#define PCI_DMA_TODEVICE&t;1
DECL|macro|PCI_DMA_FROMDEVICE
mdefine_line|#define PCI_DMA_FROMDEVICE&t;2
DECL|macro|PCI_DMA_NONE
mdefine_line|#define PCI_DMA_NONE&t;&t;3
DECL|macro|DEVICE_COUNT_COMPATIBLE
mdefine_line|#define DEVICE_COUNT_COMPATIBLE&t;4
DECL|macro|DEVICE_COUNT_IRQ
mdefine_line|#define DEVICE_COUNT_IRQ&t;2
DECL|macro|DEVICE_COUNT_DMA
mdefine_line|#define DEVICE_COUNT_DMA&t;2
DECL|macro|DEVICE_COUNT_RESOURCE
mdefine_line|#define DEVICE_COUNT_RESOURCE&t;12
DECL|macro|PCI_ANY_ID
mdefine_line|#define PCI_ANY_ID (~0)
DECL|macro|pci_present
mdefine_line|#define pci_present pcibios_present
DECL|macro|pci_for_each_dev
mdefine_line|#define pci_for_each_dev(dev) &bslash;&n;&t;for(dev = pci_dev_g(pci_devices.next); dev != pci_dev_g(&amp;pci_devices); dev = pci_dev_g(dev-&gt;global_list.next))
DECL|macro|pci_for_each_dev_reverse
mdefine_line|#define pci_for_each_dev_reverse(dev) &bslash;&n;&t;for(dev = pci_dev_g(pci_devices.prev); dev != pci_dev_g(&amp;pci_devices); dev = pci_dev_g(dev-&gt;global_list.prev))
multiline_comment|/*&n; * The pci_dev structure is used to describe both PCI and ISAPnP devices.&n; */
DECL|struct|pci_dev
r_struct
id|pci_dev
(brace
DECL|member|global_list
r_struct
id|list_head
id|global_list
suffix:semicolon
multiline_comment|/* node in list of all PCI devices */
DECL|member|bus_list
r_struct
id|list_head
id|bus_list
suffix:semicolon
multiline_comment|/* node in per-bus list */
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* bus this device is on */
DECL|member|subordinate
r_struct
id|pci_bus
op_star
id|subordinate
suffix:semicolon
multiline_comment|/* bus this device bridges to */
DECL|member|sysdata
r_void
op_star
id|sysdata
suffix:semicolon
multiline_comment|/* hook for sys-specific extension */
DECL|member|procent
r_struct
id|proc_dir_entry
op_star
id|procent
suffix:semicolon
multiline_comment|/* device entry in /proc/bus/pci */
DECL|member|devfn
r_int
r_int
id|devfn
suffix:semicolon
multiline_comment|/* encoded device &amp; function index */
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|subsystem_vendor
r_int
r_int
id|subsystem_vendor
suffix:semicolon
DECL|member|subsystem_device
r_int
r_int
id|subsystem_device
suffix:semicolon
DECL|member|class
r_int
r_int
r_class
suffix:semicolon
multiline_comment|/* 3 bytes: (base,sub,prog-if) */
DECL|member|hdr_type
id|u8
id|hdr_type
suffix:semicolon
multiline_comment|/* PCI header type (`multi&squot; flag masked out) */
DECL|member|rom_base_reg
id|u8
id|rom_base_reg
suffix:semicolon
multiline_comment|/* which config register controls the ROM */
DECL|member|driver
r_struct
id|pci_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* which driver has allocated this device */
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
DECL|member|dma_mask
id|dma_addr_t
id|dma_mask
suffix:semicolon
multiline_comment|/* Mask of the bits of bus address this&n;&t;&t;&t;&t;&t;   device implements.  Normally this is&n;&t;&t;&t;&t;&t;   0xffffffff.  You only need to change&n;&t;&t;&t;&t;&t;   this if your device has broken DMA&n;&t;&t;&t;&t;&t;   or supports 64-bit transfers.  */
multiline_comment|/* device is compatible with these IDs */
DECL|member|vendor_compatible
r_int
r_int
id|vendor_compatible
(braket
id|DEVICE_COUNT_COMPATIBLE
)braket
suffix:semicolon
DECL|member|device_compatible
r_int
r_int
id|device_compatible
(braket
id|DEVICE_COUNT_COMPATIBLE
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Instead of touching interrupt line and base address registers&n;&t; * directly, use the values stored here. They might be different!&n;&t; */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|resource
r_struct
id|resource
id|resource
(braket
id|DEVICE_COUNT_RESOURCE
)braket
suffix:semicolon
multiline_comment|/* I/O and memory regions + expansion ROMs */
DECL|member|dma_resource
r_struct
id|resource
id|dma_resource
(braket
id|DEVICE_COUNT_DMA
)braket
suffix:semicolon
DECL|member|irq_resource
r_struct
id|resource
id|irq_resource
(braket
id|DEVICE_COUNT_IRQ
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* device name */
DECL|member|slot_name
r_char
id|slot_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* slot name */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* ISAPnP: device is active */
DECL|member|ro
r_int
id|ro
suffix:semicolon
multiline_comment|/* ISAPnP: read only */
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
multiline_comment|/* ISAPnP: supported registers */
DECL|member|prepare
r_int
(paren
op_star
id|prepare
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* ISAPnP hooks */
DECL|member|activate
r_int
(paren
op_star
id|activate
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|deactivate
r_int
(paren
op_star
id|deactivate
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|pci_dev_g
mdefine_line|#define pci_dev_g(n) list_entry(n, struct pci_dev, global_list)
DECL|macro|pci_dev_b
mdefine_line|#define pci_dev_b(n) list_entry(n, struct pci_dev, bus_list)
multiline_comment|/*&n; *  For PCI devices, the region numbers are assigned this way:&n; *&n; *&t;0-5&t;standard PCI regions&n; *&t;6&t;expansion ROM&n; *&t;7-10&t;bridges: address space assigned to buses behind the bridge&n; */
DECL|macro|PCI_ROM_RESOURCE
mdefine_line|#define PCI_ROM_RESOURCE 6
DECL|macro|PCI_BRIDGE_RESOURCES
mdefine_line|#define PCI_BRIDGE_RESOURCES 7
DECL|macro|PCI_NUM_RESOURCES
mdefine_line|#define PCI_NUM_RESOURCES 11
DECL|macro|PCI_REGION_FLAG_MASK
mdefine_line|#define PCI_REGION_FLAG_MASK 0x0f&t;/* These bits of resource flags tell us the PCI region flags */
DECL|struct|pci_bus
r_struct
id|pci_bus
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in list of buses */
DECL|member|parent
r_struct
id|pci_bus
op_star
id|parent
suffix:semicolon
multiline_comment|/* parent bus this bridge is on */
DECL|member|children
r_struct
id|list_head
id|children
suffix:semicolon
multiline_comment|/* list of child buses */
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* list of devices on this bus */
DECL|member|self
r_struct
id|pci_dev
op_star
id|self
suffix:semicolon
multiline_comment|/* bridge device as seen by parent */
DECL|member|resource
r_struct
id|resource
op_star
id|resource
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* address space routed to this bus */
DECL|member|ops
r_struct
id|pci_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* configuration access functions */
DECL|member|sysdata
r_void
op_star
id|sysdata
suffix:semicolon
multiline_comment|/* hook for sys-specific extension */
DECL|member|procdir
r_struct
id|proc_dir_entry
op_star
id|procdir
suffix:semicolon
multiline_comment|/* directory entry in /proc/bus/pci */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* bus number */
DECL|member|primary
r_int
r_char
id|primary
suffix:semicolon
multiline_comment|/* number of primary bridge */
DECL|member|secondary
r_int
r_char
id|secondary
suffix:semicolon
multiline_comment|/* number of secondary bridge */
DECL|member|subordinate
r_int
r_char
id|subordinate
suffix:semicolon
multiline_comment|/* max number of subordinate buses */
DECL|member|name
r_char
id|name
(braket
l_int|48
)braket
suffix:semicolon
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|serial
r_int
r_int
id|serial
suffix:semicolon
multiline_comment|/* serial number */
DECL|member|pnpver
r_int
r_char
id|pnpver
suffix:semicolon
multiline_comment|/* Plug &amp; Play version */
DECL|member|productver
r_int
r_char
id|productver
suffix:semicolon
multiline_comment|/* product version */
DECL|member|checksum
r_int
r_char
id|checksum
suffix:semicolon
multiline_comment|/* if zero - checksum passed */
DECL|member|pad1
r_int
r_char
id|pad1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|pci_bus_b
mdefine_line|#define pci_bus_b(n) list_entry(n, struct pci_bus, node)
r_extern
r_struct
id|list_head
id|pci_root_buses
suffix:semicolon
multiline_comment|/* list of all known PCI buses */
r_extern
r_struct
id|list_head
id|pci_devices
suffix:semicolon
multiline_comment|/* list of all devices */
multiline_comment|/*&n; * Error values that may be returned by PCI functions.&n; */
DECL|macro|PCIBIOS_SUCCESSFUL
mdefine_line|#define PCIBIOS_SUCCESSFUL&t;&t;0x00
DECL|macro|PCIBIOS_FUNC_NOT_SUPPORTED
mdefine_line|#define PCIBIOS_FUNC_NOT_SUPPORTED&t;0x81
DECL|macro|PCIBIOS_BAD_VENDOR_ID
mdefine_line|#define PCIBIOS_BAD_VENDOR_ID&t;&t;0x83
DECL|macro|PCIBIOS_DEVICE_NOT_FOUND
mdefine_line|#define PCIBIOS_DEVICE_NOT_FOUND&t;0x86
DECL|macro|PCIBIOS_BAD_REGISTER_NUMBER
mdefine_line|#define PCIBIOS_BAD_REGISTER_NUMBER&t;0x87
DECL|macro|PCIBIOS_SET_FAILED
mdefine_line|#define PCIBIOS_SET_FAILED&t;&t;0x88
DECL|macro|PCIBIOS_BUFFER_TOO_SMALL
mdefine_line|#define PCIBIOS_BUFFER_TOO_SMALL&t;0x89
multiline_comment|/* Low-level architecture-dependent routines */
DECL|struct|pci_ops
r_struct
id|pci_ops
(brace
DECL|member|read_byte
r_int
(paren
op_star
id|read_byte
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|where
comma
id|u8
op_star
id|val
)paren
suffix:semicolon
DECL|member|read_word
r_int
(paren
op_star
id|read_word
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|where
comma
id|u16
op_star
id|val
)paren
suffix:semicolon
DECL|member|read_dword
r_int
(paren
op_star
id|read_dword
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|where
comma
id|u32
op_star
id|val
)paren
suffix:semicolon
DECL|member|write_byte
r_int
(paren
op_star
id|write_byte
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|where
comma
id|u8
id|val
)paren
suffix:semicolon
DECL|member|write_word
r_int
(paren
op_star
id|write_word
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|where
comma
id|u16
id|val
)paren
suffix:semicolon
DECL|member|write_dword
r_int
(paren
op_star
id|write_dword
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|where
comma
id|u32
id|val
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pbus_set_ranges_data
r_struct
id|pbus_set_ranges_data
(brace
DECL|member|found_vga
r_int
id|found_vga
suffix:semicolon
DECL|member|io_start
DECL|member|io_end
r_int
r_int
id|io_start
comma
id|io_end
suffix:semicolon
DECL|member|mem_start
DECL|member|mem_end
r_int
r_int
id|mem_start
comma
id|mem_end
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_device_id
r_struct
id|pci_device_id
(brace
DECL|member|vendor
DECL|member|device
r_int
r_int
id|vendor
comma
id|device
suffix:semicolon
multiline_comment|/* Vendor and device ID or PCI_ANY_ID */
DECL|member|subvendor
DECL|member|subdevice
r_int
r_int
id|subvendor
comma
id|subdevice
suffix:semicolon
multiline_comment|/* Subsystem ID&squot;s or PCI_ANY_ID */
DECL|member|class
DECL|member|class_mask
r_int
r_int
r_class
comma
id|class_mask
suffix:semicolon
multiline_comment|/* (class,subclass,prog-if) triplet */
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* Data private to the driver */
)brace
suffix:semicolon
DECL|struct|pci_driver
r_struct
id|pci_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|pci_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* NULL if wants all devices */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
suffix:semicolon
multiline_comment|/* New device inserted */
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Device removed (NULL if not a hot-plug capable driver) */
DECL|member|suspend
r_void
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Device suspended */
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Device woken up */
)brace
suffix:semicolon
multiline_comment|/* these external functions are only available when PCI support is enabled */
macro_line|#ifdef CONFIG_PCI
r_void
id|pcibios_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
r_int
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_char
op_star
id|pcibios_setup
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
multiline_comment|/* Used only when drivers/pci/setup.c is used */
r_void
id|pcibios_align_resource
c_func
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|pcibios_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|resource
op_star
comma
r_struct
id|resource
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|pcibios_update_irq
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|irq
)paren
suffix:semicolon
r_void
id|pcibios_fixup_pbus_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
comma
r_struct
id|pbus_set_ranges_data
op_star
)paren
suffix:semicolon
multiline_comment|/* Backward compatibility, don&squot;t use in new code! */
r_int
id|pcibios_present
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pcibios_read_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|where
comma
r_int
r_char
op_star
id|val
)paren
suffix:semicolon
r_int
id|pcibios_read_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_int
id|pcibios_read_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_int
id|pcibios_write_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|where
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
id|pcibios_write_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_int
id|pcibios_write_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_int
id|pcibios_find_class
(paren
r_int
r_int
id|class_code
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|dev_fn
)paren
suffix:semicolon
r_int
id|pcibios_find_device
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|dev_id
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|dev_fn
)paren
suffix:semicolon
multiline_comment|/* Generic PCI functions used internally */
r_void
id|pci_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pci_bus_exists
c_func
(paren
r_const
r_struct
id|list_head
op_star
id|list
comma
r_int
id|nr
)paren
suffix:semicolon
r_struct
id|pci_bus
op_star
id|pci_scan_bus
c_func
(paren
r_int
id|bus
comma
r_struct
id|pci_ops
op_star
id|ops
comma
r_void
op_star
id|sysdata
)paren
suffix:semicolon
r_struct
id|pci_bus
op_star
id|pci_alloc_primary_bus
c_func
(paren
r_int
id|bus
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_scan_slot
c_func
(paren
r_struct
id|pci_dev
op_star
id|temp
)paren
suffix:semicolon
r_int
id|pci_proc_attach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pci_proc_detach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pci_name_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_char
op_star
id|pci_class_name
c_func
(paren
id|u32
r_class
)paren
suffix:semicolon
r_void
id|pci_read_bridge_bases
c_func
(paren
r_struct
id|pci_bus
op_star
id|child
)paren
suffix:semicolon
r_struct
id|resource
op_star
id|pci_find_parent_resource
c_func
(paren
r_const
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
)paren
suffix:semicolon
r_int
id|pci_setup_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pci_get_interrupt_pin
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_dev
op_star
op_star
id|bridge
)paren
suffix:semicolon
multiline_comment|/* Generic PCI functions exported to card drivers */
r_struct
id|pci_dev
op_star
id|pci_find_device
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_find_subsys
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_int
r_int
id|ss_vendor
comma
r_int
r_int
id|ss_device
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_find_class
(paren
r_int
r_int
r_class
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_find_slot
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
)paren
suffix:semicolon
r_int
id|pci_find_capability
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|cap
)paren
suffix:semicolon
r_int
id|pci_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|val
)paren
suffix:semicolon
r_int
id|pci_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|val
)paren
suffix:semicolon
r_int
id|pci_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|val
)paren
suffix:semicolon
r_int
id|pci_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|val
)paren
suffix:semicolon
r_int
id|pci_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|val
)paren
suffix:semicolon
r_int
id|pci_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|val
)paren
suffix:semicolon
r_int
id|pci_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pci_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pci_set_power_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|state
)paren
suffix:semicolon
r_int
id|pci_assign_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|i
)paren
suffix:semicolon
multiline_comment|/* Helper functions for low-level code (drivers/pci/setup-[bus,res].c) */
r_int
id|pci_claim_resource
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|pci_assign_unassigned_resources
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pdev_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_void
id|pdev_sort_resources
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|resource_list
op_star
comma
id|u32
)paren
suffix:semicolon
r_int
r_int
id|pci_bridge_check_io
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_void
id|pci_fixup_irqs
c_func
(paren
id|u8
(paren
op_star
)paren
(paren
r_struct
id|pci_dev
op_star
comma
id|u8
op_star
)paren
comma
r_int
(paren
op_star
)paren
(paren
r_struct
id|pci_dev
op_star
comma
id|u8
comma
id|u8
)paren
)paren
suffix:semicolon
DECL|macro|HAVE_PCI_REQ_REGIONS
mdefine_line|#define HAVE_PCI_REQ_REGIONS 1
r_int
id|pci_request_regions
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_void
id|pci_release_regions
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* New-style probing supporting hot-pluggable devices */
r_int
id|pci_register_driver
c_func
(paren
r_struct
id|pci_driver
op_star
)paren
suffix:semicolon
r_void
id|pci_unregister_driver
c_func
(paren
r_struct
id|pci_driver
op_star
)paren
suffix:semicolon
r_void
id|pci_insert_device
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
r_void
id|pci_remove_device
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_struct
id|pci_driver
op_star
id|pci_dev_driver
c_func
(paren
r_const
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_const
r_struct
id|pci_device_id
op_star
id|pci_match_device
c_func
(paren
r_const
r_struct
id|pci_device_id
op_star
id|ids
comma
r_const
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/* Include architecture-dependent settings and functions */
macro_line|#include &lt;asm/pci.h&gt;
multiline_comment|/*&n; *  If the system does not have PCI, clearly these return errors.  Define&n; *  these as simple inline functions to avoid hair in drivers.&n; */
macro_line|#ifndef CONFIG_PCI
DECL|function|pcibios_present
r_static
r_inline
r_int
id|pcibios_present
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcibios_find_class
r_static
r_inline
r_int
id|pcibios_find_class
(paren
r_int
r_int
id|class_code
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|dev_fn
)paren
(brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
DECL|macro|_PCI_NOP
mdefine_line|#define _PCI_NOP(o,s,t) &bslash;&n;&t;static inline int pcibios_##o##_config_##s (u8 bus, u8 dfn, u8 where, t val) &bslash;&n;&t;&t;{ return PCIBIOS_FUNC_NOT_SUPPORTED; } &bslash;&n;&t;static inline int pci_##o##_config_##s (struct pci_dev *dev, int where, t val) &bslash;&n;&t;&t;{ return PCIBIOS_FUNC_NOT_SUPPORTED; }
DECL|macro|_PCI_NOP_ALL
mdefine_line|#define _PCI_NOP_ALL(o,x)&t;_PCI_NOP(o,byte,u8 x) &bslash;&n;&t;&t;&t;&t;_PCI_NOP(o,word,u16 x) &bslash;&n;&t;&t;&t;&t;_PCI_NOP(o,dword,u32 x)
id|_PCI_NOP_ALL
c_func
(paren
id|read
comma
op_star
)paren
id|_PCI_NOP_ALL
c_func
(paren
id|write
comma
)paren
DECL|function|pci_find_device
r_static
r_inline
r_struct
id|pci_dev
op_star
id|pci_find_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_find_class
r_static
r_inline
r_struct
id|pci_dev
op_star
id|pci_find_class
c_func
(paren
r_int
r_int
r_class
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_find_slot
r_static
r_inline
r_struct
id|pci_dev
op_star
id|pci_find_slot
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_find_subsys
r_static
r_inline
r_struct
id|pci_dev
op_star
id|pci_find_subsys
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_int
r_int
id|ss_vendor
comma
r_int
r_int
id|ss_device
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_set_master
r_static
r_inline
r_void
id|pci_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pci_enable_device
r_static
r_inline
r_int
id|pci_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|pci_module_init
r_static
r_inline
r_int
id|pci_module_init
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pci_assign_resource
r_static
r_inline
r_int
id|pci_assign_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|i
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|pci_register_driver
r_static
r_inline
r_int
id|pci_register_driver
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_unregister_driver
r_static
r_inline
r_void
id|pci_unregister_driver
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
)brace
DECL|function|scsi_to_pci_dma_dir
r_static
r_inline
r_int
id|scsi_to_pci_dma_dir
c_func
(paren
r_int
r_char
id|scsi_dir
)paren
(brace
r_return
id|scsi_dir
suffix:semicolon
)brace
DECL|function|pci_find_capability
r_static
r_inline
r_int
id|pci_find_capability
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|cap
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * a helper function which helps ensure correct pci_driver&n; * setup and cleanup for commonly-encountered hotplug/modular cases&n; *&n; * This MUST stay in a header, as it checks for -DMODULE&n; */
DECL|function|pci_module_init
r_static
r_inline
r_int
id|pci_module_init
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
r_int
id|rc
op_assign
id|pci_register_driver
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* iff CONFIG_HOTPLUG and built into kernel, we should&n;&t; * leave the driver around for future hotplug events.&n;&t; * For the module case, a hotplug daemon of some sort&n;&t; * should load a module in response to an insert event. */
macro_line|#if defined(CONFIG_HOTPLUG) &amp;&amp; !defined(MODULE)
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* if we get here, we need to clean up pci driver instance&n;&t; * and return some sort of error */
id|pci_unregister_driver
(paren
id|drv
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_PCI */
multiline_comment|/* these helpers provide future and backwards compatibility&n; * for accessing popular PCI BAR info */
DECL|macro|pci_resource_start
mdefine_line|#define pci_resource_start(dev,bar)   ((dev)-&gt;resource[(bar)].start)
DECL|macro|pci_resource_end
mdefine_line|#define pci_resource_end(dev,bar)     ((dev)-&gt;resource[(bar)].end)
DECL|macro|pci_resource_flags
mdefine_line|#define pci_resource_flags(dev,bar)   ((dev)-&gt;resource[(bar)].flags)
DECL|macro|pci_resource_len
mdefine_line|#define pci_resource_len(dev,bar) &bslash;&n;&t;((pci_resource_start((dev),(bar)) == 0 &amp;&amp;&t;&bslash;&n;&t;  pci_resource_end((dev),(bar)) ==&t;&t;&bslash;&n;&t;  pci_resource_start((dev),(bar))) ? 0 :&t;&bslash;&n;&t;  &t;&t;&t;&t;&t;&t;&bslash;&n;&t; (pci_resource_end((dev),(bar)) -&t;&t;&bslash;&n;&t;  pci_resource_start((dev),(bar)) + 1))
multiline_comment|/* Similar to the helpers above, these manipulate per-pci_dev&n; * driver-specific data.  Currently stored as pci_dev::driver_data,&n; * a void pointer, but it is not present on older kernels.&n; */
DECL|function|pci_get_drvdata
r_static
r_inline
r_void
op_star
id|pci_get_drvdata
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_return
id|pdev-&gt;driver_data
suffix:semicolon
)brace
DECL|function|pci_set_drvdata
r_static
r_inline
r_void
id|pci_set_drvdata
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_void
op_star
id|data
)paren
(brace
id|pdev-&gt;driver_data
op_assign
id|data
suffix:semicolon
)brace
multiline_comment|/*&n; *  The world is not perfect and supplies us with broken PCI devices.&n; *  For at least a part of these bugs we need a work-around, so both&n; *  generic (drivers/pci/quirks.c) and per-architecture code can define&n; *  fixup hooks to be called for particular buggy devices.&n; */
DECL|struct|pci_fixup
r_struct
id|pci_fixup
(brace
DECL|member|pass
r_int
id|pass
suffix:semicolon
DECL|member|vendor
DECL|member|device
id|u16
id|vendor
comma
id|device
suffix:semicolon
multiline_comment|/* You can use PCI_ANY_ID here of course */
DECL|member|hook
r_void
(paren
op_star
id|hook
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
suffix:semicolon
DECL|macro|PCI_FIXUP_HEADER
mdefine_line|#define PCI_FIXUP_HEADER&t;1&t;&t;/* Called immediately after reading configuration header */
DECL|macro|PCI_FIXUP_FINAL
mdefine_line|#define PCI_FIXUP_FINAL&t;&t;2&t;&t;/* Final phase of device fixups */
r_void
id|pci_fixup_device
c_func
(paren
r_int
id|pass
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|pci_pci_problems
suffix:semicolon
DECL|macro|PCIPCI_FAIL
mdefine_line|#define PCIPCI_FAIL&t;&t;1
DECL|macro|PCIPCI_TRITON
mdefine_line|#define PCIPCI_TRITON&t;&t;2
DECL|macro|PCIPCI_NATOMA
mdefine_line|#define PCIPCI_NATOMA&t;&t;4
DECL|macro|PCIPCI_VIAETBF
mdefine_line|#define PCIPCI_VIAETBF&t;&t;8
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_PCI_H */
eof
