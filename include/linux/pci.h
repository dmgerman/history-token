multiline_comment|/*&n; *&t;pci.h&n; *&n; *&t;PCI defines and function prototypes&n; *&t;Copyright 1994, Drew Eckhardt&n; *&t;Copyright 1997--1999 Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; *&t;For more information, please consult the following manuals (look at&n; *&t;http://www.pcisig.com/ for how to get them):&n; *&n; *&t;PCI BIOS Specification&n; *&t;PCI Local Bus Specification&n; *&t;PCI to PCI Bridge Specification&n; *&t;PCI System Design Guide&n; */
macro_line|#ifndef LINUX_PCI_H
DECL|macro|LINUX_PCI_H
mdefine_line|#define LINUX_PCI_H
macro_line|#include &lt;linux/mod_devicetable.h&gt;
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
DECL|macro|PCI_COMMAND_INTX_DISABLE
mdefine_line|#define  PCI_COMMAND_INTX_DISABLE 0x400 /* INTx Emulation Disable */
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
mdefine_line|#define  PCI_BIST_CODE_MASK&t;0x0f&t;/* Return result */
DECL|macro|PCI_BIST_START
mdefine_line|#define  PCI_BIST_START&t;&t;0x40&t;/* 1 to start BIST, 2 secs or less */
DECL|macro|PCI_BIST_CAPABLE
mdefine_line|#define  PCI_BIST_CAPABLE&t;0x80&t;/* 1 if BIST capable */
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
mdefine_line|#define  PCI_IO_RANGE_TYPE_MASK&t;0x0fUL&t;/* I/O bridging type */
DECL|macro|PCI_IO_RANGE_TYPE_16
mdefine_line|#define  PCI_IO_RANGE_TYPE_16&t;0x00
DECL|macro|PCI_IO_RANGE_TYPE_32
mdefine_line|#define  PCI_IO_RANGE_TYPE_32&t;0x01
DECL|macro|PCI_IO_RANGE_MASK
mdefine_line|#define  PCI_IO_RANGE_MASK&t;(~0x0fUL)
DECL|macro|PCI_SEC_STATUS
mdefine_line|#define PCI_SEC_STATUS&t;&t;0x1e&t;/* Secondary status register, only bit 14 used */
DECL|macro|PCI_MEMORY_BASE
mdefine_line|#define PCI_MEMORY_BASE&t;&t;0x20&t;/* Memory range behind */
DECL|macro|PCI_MEMORY_LIMIT
mdefine_line|#define PCI_MEMORY_LIMIT&t;0x22
DECL|macro|PCI_MEMORY_RANGE_TYPE_MASK
mdefine_line|#define  PCI_MEMORY_RANGE_TYPE_MASK 0x0fUL
DECL|macro|PCI_MEMORY_RANGE_MASK
mdefine_line|#define  PCI_MEMORY_RANGE_MASK&t;(~0x0fUL)
DECL|macro|PCI_PREF_MEMORY_BASE
mdefine_line|#define PCI_PREF_MEMORY_BASE&t;0x24&t;/* Prefetchable memory range behind */
DECL|macro|PCI_PREF_MEMORY_LIMIT
mdefine_line|#define PCI_PREF_MEMORY_LIMIT&t;0x26
DECL|macro|PCI_PREF_RANGE_TYPE_MASK
mdefine_line|#define  PCI_PREF_RANGE_TYPE_MASK 0x0fUL
DECL|macro|PCI_PREF_RANGE_TYPE_32
mdefine_line|#define  PCI_PREF_RANGE_TYPE_32&t;0x00
DECL|macro|PCI_PREF_RANGE_TYPE_64
mdefine_line|#define  PCI_PREF_RANGE_TYPE_64&t;0x01
DECL|macro|PCI_PREF_RANGE_MASK
mdefine_line|#define  PCI_PREF_RANGE_MASK&t;(~0x0fUL)
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
mdefine_line|#define  PCI_CB_IO_RANGE_MASK&t;(~0x03UL)
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
DECL|macro|PCI_CAP_ID_PCIX
mdefine_line|#define  PCI_CAP_ID_PCIX&t;0x07&t;/* PCI-X */
DECL|macro|PCI_CAP_ID_SHPC
mdefine_line|#define  PCI_CAP_ID_SHPC &t;0x0C&t;/* PCI Standard Hot-Plug Controller */
DECL|macro|PCI_CAP_ID_EXP
mdefine_line|#define  PCI_CAP_ID_EXP &t;0x10&t;/* PCI Express */
DECL|macro|PCI_CAP_ID_MSIX
mdefine_line|#define  PCI_CAP_ID_MSIX&t;0x11&t;/* MSI-X */
DECL|macro|PCI_CAP_LIST_NEXT
mdefine_line|#define PCI_CAP_LIST_NEXT&t;1&t;/* Next capability in the list */
DECL|macro|PCI_CAP_FLAGS
mdefine_line|#define PCI_CAP_FLAGS&t;&t;2&t;/* Capability defined flags (16 bits) */
DECL|macro|PCI_CAP_SIZEOF
mdefine_line|#define PCI_CAP_SIZEOF&t;&t;4
multiline_comment|/* Power Management Registers */
DECL|macro|PCI_PM_PMC
mdefine_line|#define PCI_PM_PMC              2       /* PM Capabilities Register */
DECL|macro|PCI_PM_CAP_VER_MASK
mdefine_line|#define  PCI_PM_CAP_VER_MASK&t;0x0007&t;/* Version */
DECL|macro|PCI_PM_CAP_PME_CLOCK
mdefine_line|#define  PCI_PM_CAP_PME_CLOCK&t;0x0008&t;/* PME clock required */
DECL|macro|PCI_PM_CAP_RESERVED
mdefine_line|#define  PCI_PM_CAP_RESERVED    0x0010  /* Reserved field */
DECL|macro|PCI_PM_CAP_DSI
mdefine_line|#define  PCI_PM_CAP_DSI&t;&t;0x0020&t;/* Device specific initialization */
DECL|macro|PCI_PM_CAP_AUX_POWER
mdefine_line|#define  PCI_PM_CAP_AUX_POWER&t;0x01C0&t;/* Auxilliary power support mask */
DECL|macro|PCI_PM_CAP_D1
mdefine_line|#define  PCI_PM_CAP_D1&t;&t;0x0200&t;/* D1 power state support */
DECL|macro|PCI_PM_CAP_D2
mdefine_line|#define  PCI_PM_CAP_D2&t;&t;0x0400&t;/* D2 power state support */
DECL|macro|PCI_PM_CAP_PME
mdefine_line|#define  PCI_PM_CAP_PME&t;&t;0x0800&t;/* PME pin supported */
DECL|macro|PCI_PM_CAP_PME_MASK
mdefine_line|#define  PCI_PM_CAP_PME_MASK    0xF800  /* PME Mask of all supported states */
DECL|macro|PCI_PM_CAP_PME_D0
mdefine_line|#define  PCI_PM_CAP_PME_D0      0x0800  /* PME# from D0 */
DECL|macro|PCI_PM_CAP_PME_D1
mdefine_line|#define  PCI_PM_CAP_PME_D1      0x1000  /* PME# from D1 */
DECL|macro|PCI_PM_CAP_PME_D2
mdefine_line|#define  PCI_PM_CAP_PME_D2      0x2000  /* PME# from D2 */
DECL|macro|PCI_PM_CAP_PME_D3
mdefine_line|#define  PCI_PM_CAP_PME_D3      0x4000  /* PME# from D3 (hot) */
DECL|macro|PCI_PM_CAP_PME_D3cold
mdefine_line|#define  PCI_PM_CAP_PME_D3cold  0x8000  /* PME# from D3 (cold) */
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
mdefine_line|#define  PCI_AGP_COMMAND_RATE2&t;0x0002&t;/* Use 2x rate */
DECL|macro|PCI_AGP_COMMAND_RATE1
mdefine_line|#define  PCI_AGP_COMMAND_RATE1&t;0x0001&t;/* Use 1x rate */
DECL|macro|PCI_AGP_SIZEOF
mdefine_line|#define PCI_AGP_SIZEOF&t;&t;12
multiline_comment|/* Vital Product Data */
DECL|macro|PCI_VPD_ADDR
mdefine_line|#define PCI_VPD_ADDR&t;&t;2&t;/* Address to access (15 bits!) */
DECL|macro|PCI_VPD_ADDR_MASK
mdefine_line|#define  PCI_VPD_ADDR_MASK&t;0x7fff&t;/* Address mask */
DECL|macro|PCI_VPD_ADDR_F
mdefine_line|#define  PCI_VPD_ADDR_F&t;&t;0x8000&t;/* Write 0, 1 indicates completion */
DECL|macro|PCI_VPD_DATA
mdefine_line|#define PCI_VPD_DATA&t;&t;4&t;/* 32-bits of data returned here */
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
DECL|macro|PCI_MSI_FLAGS_MASKBIT
mdefine_line|#define  PCI_MSI_FLAGS_MASKBIT&t;0x100&t;/* 64-bit mask bits allowed */
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
DECL|macro|PCI_MSI_MASK_BIT
mdefine_line|#define PCI_MSI_MASK_BIT&t;16&t;/* Mask bits register */
multiline_comment|/* CompactPCI Hotswap Register */
DECL|macro|PCI_CHSWP_CSR
mdefine_line|#define PCI_CHSWP_CSR&t;&t;2&t;/* Control and Status Register */
DECL|macro|PCI_CHSWP_DHA
mdefine_line|#define  PCI_CHSWP_DHA&t;&t;0x01&t;/* Device Hiding Arm */
DECL|macro|PCI_CHSWP_EIM
mdefine_line|#define  PCI_CHSWP_EIM&t;&t;0x02&t;/* ENUM# Signal Mask */
DECL|macro|PCI_CHSWP_PIE
mdefine_line|#define  PCI_CHSWP_PIE&t;&t;0x04&t;/* Pending Insert or Extract */
DECL|macro|PCI_CHSWP_LOO
mdefine_line|#define  PCI_CHSWP_LOO&t;&t;0x08&t;/* LED On / Off */
DECL|macro|PCI_CHSWP_PI
mdefine_line|#define  PCI_CHSWP_PI&t;&t;0x30&t;/* Programming Interface */
DECL|macro|PCI_CHSWP_EXT
mdefine_line|#define  PCI_CHSWP_EXT&t;&t;0x40&t;/* ENUM# status - extraction */
DECL|macro|PCI_CHSWP_INS
mdefine_line|#define  PCI_CHSWP_INS&t;&t;0x80&t;/* ENUM# status - insertion */
multiline_comment|/* PCI-X registers */
DECL|macro|PCI_X_CMD
mdefine_line|#define PCI_X_CMD&t;&t;2&t;/* Modes &amp; Features */
DECL|macro|PCI_X_CMD_DPERR_E
mdefine_line|#define  PCI_X_CMD_DPERR_E&t;0x0001&t;/* Data Parity Error Recovery Enable */
DECL|macro|PCI_X_CMD_ERO
mdefine_line|#define  PCI_X_CMD_ERO&t;&t;0x0002&t;/* Enable Relaxed Ordering */
DECL|macro|PCI_X_CMD_MAX_READ
mdefine_line|#define  PCI_X_CMD_MAX_READ&t;0x000c&t;/* Max Memory Read Byte Count */
DECL|macro|PCI_X_CMD_MAX_SPLIT
mdefine_line|#define  PCI_X_CMD_MAX_SPLIT&t;0x0070&t;/* Max Outstanding Split Transactions */
DECL|macro|PCI_X_CMD_VERSION
mdefine_line|#define  PCI_X_CMD_VERSION(x) &t;(((x) &gt;&gt; 12) &amp; 3) /* Version */
DECL|macro|PCI_X_STATUS
mdefine_line|#define PCI_X_STATUS&t;&t;4&t;/* PCI-X capabilities */
DECL|macro|PCI_X_STATUS_DEVFN
mdefine_line|#define  PCI_X_STATUS_DEVFN&t;0x000000ff&t;/* A copy of devfn */
DECL|macro|PCI_X_STATUS_BUS
mdefine_line|#define  PCI_X_STATUS_BUS&t;0x0000ff00&t;/* A copy of bus nr */
DECL|macro|PCI_X_STATUS_64BIT
mdefine_line|#define  PCI_X_STATUS_64BIT&t;0x00010000&t;/* 64-bit device */
DECL|macro|PCI_X_STATUS_133MHZ
mdefine_line|#define  PCI_X_STATUS_133MHZ&t;0x00020000&t;/* 133 MHz capable */
DECL|macro|PCI_X_STATUS_SPL_DISC
mdefine_line|#define  PCI_X_STATUS_SPL_DISC&t;0x00040000&t;/* Split Completion Discarded */
DECL|macro|PCI_X_STATUS_UNX_SPL
mdefine_line|#define  PCI_X_STATUS_UNX_SPL&t;0x00080000&t;/* Unexpected Split Completion */
DECL|macro|PCI_X_STATUS_COMPLEX
mdefine_line|#define  PCI_X_STATUS_COMPLEX&t;0x00100000&t;/* Device Complexity */
DECL|macro|PCI_X_STATUS_MAX_READ
mdefine_line|#define  PCI_X_STATUS_MAX_READ&t;0x00600000&t;/* Designed Max Memory Read Count */
DECL|macro|PCI_X_STATUS_MAX_SPLIT
mdefine_line|#define  PCI_X_STATUS_MAX_SPLIT&t;0x03800000&t;/* Designed Max Outstanding Split Transactions */
DECL|macro|PCI_X_STATUS_MAX_CUM
mdefine_line|#define  PCI_X_STATUS_MAX_CUM&t;0x1c000000&t;/* Designed Max Cumulative Read Size */
DECL|macro|PCI_X_STATUS_SPL_ERR
mdefine_line|#define  PCI_X_STATUS_SPL_ERR&t;0x20000000&t;/* Rcvd Split Completion Error Msg */
DECL|macro|PCI_X_STATUS_266MHZ
mdefine_line|#define  PCI_X_STATUS_266MHZ&t;0x40000000&t;/* 266 MHz capable */
DECL|macro|PCI_X_STATUS_533MHZ
mdefine_line|#define  PCI_X_STATUS_533MHZ&t;0x80000000&t;/* 533 MHz capable */
multiline_comment|/* PCI Express capability registers */
DECL|macro|PCI_EXP_FLAGS
mdefine_line|#define PCI_EXP_FLAGS&t;&t;2&t;/* Capabilities register */
DECL|macro|PCI_EXP_FLAGS_VERS
mdefine_line|#define PCI_EXP_FLAGS_VERS&t;0x000f&t;/* Capability version */
DECL|macro|PCI_EXP_FLAGS_TYPE
mdefine_line|#define PCI_EXP_FLAGS_TYPE&t;0x00f0&t;/* Device/Port type */
DECL|macro|PCI_EXP_TYPE_ENDPOINT
mdefine_line|#define  PCI_EXP_TYPE_ENDPOINT&t;0x0&t;/* Express Endpoint */
DECL|macro|PCI_EXP_TYPE_LEG_END
mdefine_line|#define  PCI_EXP_TYPE_LEG_END&t;0x1&t;/* Legacy Endpoint */
DECL|macro|PCI_EXP_TYPE_ROOT_PORT
mdefine_line|#define  PCI_EXP_TYPE_ROOT_PORT 0x4&t;/* Root Port */
DECL|macro|PCI_EXP_TYPE_UPSTREAM
mdefine_line|#define  PCI_EXP_TYPE_UPSTREAM&t;0x5&t;/* Upstream Port */
DECL|macro|PCI_EXP_TYPE_DOWNSTREAM
mdefine_line|#define  PCI_EXP_TYPE_DOWNSTREAM 0x6&t;/* Downstream Port */
DECL|macro|PCI_EXP_TYPE_PCI_BRIDGE
mdefine_line|#define  PCI_EXP_TYPE_PCI_BRIDGE 0x7&t;/* PCI/PCI-X Bridge */
DECL|macro|PCI_EXP_FLAGS_SLOT
mdefine_line|#define PCI_EXP_FLAGS_SLOT&t;0x0100&t;/* Slot implemented */
DECL|macro|PCI_EXP_FLAGS_IRQ
mdefine_line|#define PCI_EXP_FLAGS_IRQ&t;0x3e00&t;/* Interrupt message number */
DECL|macro|PCI_EXP_DEVCAP
mdefine_line|#define PCI_EXP_DEVCAP&t;&t;4&t;/* Device capabilities */
DECL|macro|PCI_EXP_DEVCAP_PAYLOAD
mdefine_line|#define  PCI_EXP_DEVCAP_PAYLOAD&t;0x07&t;/* Max_Payload_Size */
DECL|macro|PCI_EXP_DEVCAP_PHANTOM
mdefine_line|#define  PCI_EXP_DEVCAP_PHANTOM&t;0x18&t;/* Phantom functions */
DECL|macro|PCI_EXP_DEVCAP_EXT_TAG
mdefine_line|#define  PCI_EXP_DEVCAP_EXT_TAG&t;0x20&t;/* Extended tags */
DECL|macro|PCI_EXP_DEVCAP_L0S
mdefine_line|#define  PCI_EXP_DEVCAP_L0S&t;0x1c0&t;/* L0s Acceptable Latency */
DECL|macro|PCI_EXP_DEVCAP_L1
mdefine_line|#define  PCI_EXP_DEVCAP_L1&t;0xe00&t;/* L1 Acceptable Latency */
DECL|macro|PCI_EXP_DEVCAP_ATN_BUT
mdefine_line|#define  PCI_EXP_DEVCAP_ATN_BUT&t;0x1000&t;/* Attention Button Present */
DECL|macro|PCI_EXP_DEVCAP_ATN_IND
mdefine_line|#define  PCI_EXP_DEVCAP_ATN_IND&t;0x2000&t;/* Attention Indicator Present */
DECL|macro|PCI_EXP_DEVCAP_PWR_IND
mdefine_line|#define  PCI_EXP_DEVCAP_PWR_IND&t;0x4000&t;/* Power Indicator Present */
DECL|macro|PCI_EXP_DEVCAP_PWR_VAL
mdefine_line|#define  PCI_EXP_DEVCAP_PWR_VAL&t;0x3fc0000 /* Slot Power Limit Value */
DECL|macro|PCI_EXP_DEVCAP_PWR_SCL
mdefine_line|#define  PCI_EXP_DEVCAP_PWR_SCL&t;0xc000000 /* Slot Power Limit Scale */
DECL|macro|PCI_EXP_DEVCTL
mdefine_line|#define PCI_EXP_DEVCTL&t;&t;8&t;/* Device Control */
DECL|macro|PCI_EXP_DEVCTL_CERE
mdefine_line|#define  PCI_EXP_DEVCTL_CERE&t;0x0001&t;/* Correctable Error Reporting En. */
DECL|macro|PCI_EXP_DEVCTL_NFERE
mdefine_line|#define  PCI_EXP_DEVCTL_NFERE&t;0x0002&t;/* Non-Fatal Error Reporting Enable */
DECL|macro|PCI_EXP_DEVCTL_FERE
mdefine_line|#define  PCI_EXP_DEVCTL_FERE&t;0x0004&t;/* Fatal Error Reporting Enable */
DECL|macro|PCI_EXP_DEVCTL_URRE
mdefine_line|#define  PCI_EXP_DEVCTL_URRE&t;0x0008&t;/* Unsupported Request Reporting En. */
DECL|macro|PCI_EXP_DEVCTL_RELAX_EN
mdefine_line|#define  PCI_EXP_DEVCTL_RELAX_EN 0x0010 /* Enable relaxed ordering */
DECL|macro|PCI_EXP_DEVCTL_PAYLOAD
mdefine_line|#define  PCI_EXP_DEVCTL_PAYLOAD&t;0x00e0&t;/* Max_Payload_Size */
DECL|macro|PCI_EXP_DEVCTL_EXT_TAG
mdefine_line|#define  PCI_EXP_DEVCTL_EXT_TAG&t;0x0100&t;/* Extended Tag Field Enable */
DECL|macro|PCI_EXP_DEVCTL_PHANTOM
mdefine_line|#define  PCI_EXP_DEVCTL_PHANTOM&t;0x0200&t;/* Phantom Functions Enable */
DECL|macro|PCI_EXP_DEVCTL_AUX_PME
mdefine_line|#define  PCI_EXP_DEVCTL_AUX_PME&t;0x0400&t;/* Auxiliary Power PM Enable */
DECL|macro|PCI_EXP_DEVCTL_NOSNOOP_EN
mdefine_line|#define  PCI_EXP_DEVCTL_NOSNOOP_EN 0x0800  /* Enable No Snoop */
DECL|macro|PCI_EXP_DEVCTL_READRQ
mdefine_line|#define  PCI_EXP_DEVCTL_READRQ&t;0x7000&t;/* Max_Read_Request_Size */
DECL|macro|PCI_EXP_DEVSTA
mdefine_line|#define PCI_EXP_DEVSTA&t;&t;10&t;/* Device Status */
DECL|macro|PCI_EXP_DEVSTA_CED
mdefine_line|#define  PCI_EXP_DEVSTA_CED&t;0x01&t;/* Correctable Error Detected */
DECL|macro|PCI_EXP_DEVSTA_NFED
mdefine_line|#define  PCI_EXP_DEVSTA_NFED&t;0x02&t;/* Non-Fatal Error Detected */
DECL|macro|PCI_EXP_DEVSTA_FED
mdefine_line|#define  PCI_EXP_DEVSTA_FED&t;0x04&t;/* Fatal Error Detected */
DECL|macro|PCI_EXP_DEVSTA_URD
mdefine_line|#define  PCI_EXP_DEVSTA_URD&t;0x08&t;/* Unsupported Request Detected */
DECL|macro|PCI_EXP_DEVSTA_AUXPD
mdefine_line|#define  PCI_EXP_DEVSTA_AUXPD&t;0x10&t;/* AUX Power Detected */
DECL|macro|PCI_EXP_DEVSTA_TRPND
mdefine_line|#define  PCI_EXP_DEVSTA_TRPND&t;0x20&t;/* Transactions Pending */
DECL|macro|PCI_EXP_LNKCAP
mdefine_line|#define PCI_EXP_LNKCAP&t;&t;12&t;/* Link Capabilities */
DECL|macro|PCI_EXP_LNKCTL
mdefine_line|#define PCI_EXP_LNKCTL&t;&t;16&t;/* Link Control */
DECL|macro|PCI_EXP_LNKSTA
mdefine_line|#define PCI_EXP_LNKSTA&t;&t;18&t;/* Link Status */
DECL|macro|PCI_EXP_SLTCAP
mdefine_line|#define PCI_EXP_SLTCAP&t;&t;20&t;/* Slot Capabilities */
DECL|macro|PCI_EXP_SLTCTL
mdefine_line|#define PCI_EXP_SLTCTL&t;&t;24&t;/* Slot Control */
DECL|macro|PCI_EXP_SLTSTA
mdefine_line|#define PCI_EXP_SLTSTA&t;&t;26&t;/* Slot Status */
DECL|macro|PCI_EXP_RTCTL
mdefine_line|#define PCI_EXP_RTCTL&t;&t;28&t;/* Root Control */
DECL|macro|PCI_EXP_RTCTL_SECEE
mdefine_line|#define  PCI_EXP_RTCTL_SECEE&t;0x01&t;/* System Error on Correctable Error */
DECL|macro|PCI_EXP_RTCTL_SENFEE
mdefine_line|#define  PCI_EXP_RTCTL_SENFEE&t;0x02&t;/* System Error on Non-Fatal Error */
DECL|macro|PCI_EXP_RTCTL_SEFEE
mdefine_line|#define  PCI_EXP_RTCTL_SEFEE&t;0x04&t;/* System Error on Fatal Error */
DECL|macro|PCI_EXP_RTCTL_PMEIE
mdefine_line|#define  PCI_EXP_RTCTL_PMEIE&t;0x08&t;/* PME Interrupt Enable */
DECL|macro|PCI_EXP_RTCTL_CRSSVE
mdefine_line|#define  PCI_EXP_RTCTL_CRSSVE&t;0x10&t;/* CRS Software Visibility Enable */
DECL|macro|PCI_EXP_RTCAP
mdefine_line|#define PCI_EXP_RTCAP&t;&t;30&t;/* Root Capabilities */
DECL|macro|PCI_EXP_RTSTA
mdefine_line|#define PCI_EXP_RTSTA&t;&t;32&t;/* Root Status */
multiline_comment|/* Extended Capabilities (PCI-X 2.0 and Express) */
DECL|macro|PCI_EXT_CAP_ID
mdefine_line|#define PCI_EXT_CAP_ID(header)&t;&t;(header &amp; 0x0000ffff)
DECL|macro|PCI_EXT_CAP_VER
mdefine_line|#define PCI_EXT_CAP_VER(header)&t;&t;((header &gt;&gt; 16) &amp; 0xf)
DECL|macro|PCI_EXT_CAP_NEXT
mdefine_line|#define PCI_EXT_CAP_NEXT(header)&t;((header &gt;&gt; 20) &amp; 0xffc)
DECL|macro|PCI_EXT_CAP_ID_ERR
mdefine_line|#define PCI_EXT_CAP_ID_ERR&t;1
DECL|macro|PCI_EXT_CAP_ID_VC
mdefine_line|#define PCI_EXT_CAP_ID_VC&t;2
DECL|macro|PCI_EXT_CAP_ID_DSN
mdefine_line|#define PCI_EXT_CAP_ID_DSN&t;3
DECL|macro|PCI_EXT_CAP_ID_PWR
mdefine_line|#define PCI_EXT_CAP_ID_PWR&t;4
multiline_comment|/* Advanced Error Reporting */
DECL|macro|PCI_ERR_UNCOR_STATUS
mdefine_line|#define PCI_ERR_UNCOR_STATUS&t;4&t;/* Uncorrectable Error Status */
DECL|macro|PCI_ERR_UNC_TRAIN
mdefine_line|#define  PCI_ERR_UNC_TRAIN&t;0x00000001&t;/* Training */
DECL|macro|PCI_ERR_UNC_DLP
mdefine_line|#define  PCI_ERR_UNC_DLP&t;0x00000010&t;/* Data Link Protocol */
DECL|macro|PCI_ERR_UNC_POISON_TLP
mdefine_line|#define  PCI_ERR_UNC_POISON_TLP&t;0x00001000&t;/* Poisoned TLP */
DECL|macro|PCI_ERR_UNC_FCP
mdefine_line|#define  PCI_ERR_UNC_FCP&t;0x00002000&t;/* Flow Control Protocol */
DECL|macro|PCI_ERR_UNC_COMP_TIME
mdefine_line|#define  PCI_ERR_UNC_COMP_TIME&t;0x00004000&t;/* Completion Timeout */
DECL|macro|PCI_ERR_UNC_COMP_ABORT
mdefine_line|#define  PCI_ERR_UNC_COMP_ABORT&t;0x00008000&t;/* Completer Abort */
DECL|macro|PCI_ERR_UNC_UNX_COMP
mdefine_line|#define  PCI_ERR_UNC_UNX_COMP&t;0x00010000&t;/* Unexpected Completion */
DECL|macro|PCI_ERR_UNC_RX_OVER
mdefine_line|#define  PCI_ERR_UNC_RX_OVER&t;0x00020000&t;/* Receiver Overflow */
DECL|macro|PCI_ERR_UNC_MALF_TLP
mdefine_line|#define  PCI_ERR_UNC_MALF_TLP&t;0x00040000&t;/* Malformed TLP */
DECL|macro|PCI_ERR_UNC_ECRC
mdefine_line|#define  PCI_ERR_UNC_ECRC&t;0x00080000&t;/* ECRC Error Status */
DECL|macro|PCI_ERR_UNC_UNSUP
mdefine_line|#define  PCI_ERR_UNC_UNSUP&t;0x00100000&t;/* Unsupported Request */
DECL|macro|PCI_ERR_UNCOR_MASK
mdefine_line|#define PCI_ERR_UNCOR_MASK&t;8&t;/* Uncorrectable Error Mask */
multiline_comment|/* Same bits as above */
DECL|macro|PCI_ERR_UNCOR_SEVER
mdefine_line|#define PCI_ERR_UNCOR_SEVER&t;12&t;/* Uncorrectable Error Severity */
multiline_comment|/* Same bits as above */
DECL|macro|PCI_ERR_COR_STATUS
mdefine_line|#define PCI_ERR_COR_STATUS&t;16&t;/* Correctable Error Status */
DECL|macro|PCI_ERR_COR_RCVR
mdefine_line|#define  PCI_ERR_COR_RCVR&t;0x00000001&t;/* Receiver Error Status */
DECL|macro|PCI_ERR_COR_BAD_TLP
mdefine_line|#define  PCI_ERR_COR_BAD_TLP&t;0x00000040&t;/* Bad TLP Status */
DECL|macro|PCI_ERR_COR_BAD_DLLP
mdefine_line|#define  PCI_ERR_COR_BAD_DLLP&t;0x00000080&t;/* Bad DLLP Status */
DECL|macro|PCI_ERR_COR_REP_ROLL
mdefine_line|#define  PCI_ERR_COR_REP_ROLL&t;0x00000100&t;/* REPLAY_NUM Rollover */
DECL|macro|PCI_ERR_COR_REP_TIMER
mdefine_line|#define  PCI_ERR_COR_REP_TIMER&t;0x00001000&t;/* Replay Timer Timeout */
DECL|macro|PCI_ERR_COR_MASK
mdefine_line|#define PCI_ERR_COR_MASK&t;20&t;/* Correctable Error Mask */
multiline_comment|/* Same bits as above */
DECL|macro|PCI_ERR_CAP
mdefine_line|#define PCI_ERR_CAP&t;&t;24&t;/* Advanced Error Capabilities */
DECL|macro|PCI_ERR_CAP_FEP
mdefine_line|#define  PCI_ERR_CAP_FEP(x)&t;((x) &amp; 31)&t;/* First Error Pointer */
DECL|macro|PCI_ERR_CAP_ECRC_GENC
mdefine_line|#define  PCI_ERR_CAP_ECRC_GENC&t;0x00000020&t;/* ECRC Generation Capable */
DECL|macro|PCI_ERR_CAP_ECRC_GENE
mdefine_line|#define  PCI_ERR_CAP_ECRC_GENE&t;0x00000040&t;/* ECRC Generation Enable */
DECL|macro|PCI_ERR_CAP_ECRC_CHKC
mdefine_line|#define  PCI_ERR_CAP_ECRC_CHKC&t;0x00000080&t;/* ECRC Check Capable */
DECL|macro|PCI_ERR_CAP_ECRC_CHKE
mdefine_line|#define  PCI_ERR_CAP_ECRC_CHKE&t;0x00000100&t;/* ECRC Check Enable */
DECL|macro|PCI_ERR_HEADER_LOG
mdefine_line|#define PCI_ERR_HEADER_LOG&t;28&t;/* Header Log Register (16 bytes) */
DECL|macro|PCI_ERR_ROOT_COMMAND
mdefine_line|#define PCI_ERR_ROOT_COMMAND&t;44&t;/* Root Error Command */
DECL|macro|PCI_ERR_ROOT_STATUS
mdefine_line|#define PCI_ERR_ROOT_STATUS&t;48
DECL|macro|PCI_ERR_ROOT_COR_SRC
mdefine_line|#define PCI_ERR_ROOT_COR_SRC&t;52
DECL|macro|PCI_ERR_ROOT_SRC
mdefine_line|#define PCI_ERR_ROOT_SRC&t;54
multiline_comment|/* Virtual Channel */
DECL|macro|PCI_VC_PORT_REG1
mdefine_line|#define PCI_VC_PORT_REG1&t;4
DECL|macro|PCI_VC_PORT_REG2
mdefine_line|#define PCI_VC_PORT_REG2&t;8
DECL|macro|PCI_VC_PORT_CTRL
mdefine_line|#define PCI_VC_PORT_CTRL&t;12
DECL|macro|PCI_VC_PORT_STATUS
mdefine_line|#define PCI_VC_PORT_STATUS&t;14
DECL|macro|PCI_VC_RES_CAP
mdefine_line|#define PCI_VC_RES_CAP&t;&t;16
DECL|macro|PCI_VC_RES_CTRL
mdefine_line|#define PCI_VC_RES_CTRL&t;&t;20
DECL|macro|PCI_VC_RES_STATUS
mdefine_line|#define PCI_VC_RES_STATUS&t;26
multiline_comment|/* Power Budgeting */
DECL|macro|PCI_PWR_DSR
mdefine_line|#define PCI_PWR_DSR&t;&t;4&t;/* Data Select Register */
DECL|macro|PCI_PWR_DATA
mdefine_line|#define PCI_PWR_DATA&t;&t;8&t;/* Data Register */
DECL|macro|PCI_PWR_DATA_BASE
mdefine_line|#define  PCI_PWR_DATA_BASE(x)&t;((x) &amp; 0xff)&t;    /* Base Power */
DECL|macro|PCI_PWR_DATA_SCALE
mdefine_line|#define  PCI_PWR_DATA_SCALE(x)&t;(((x) &gt;&gt; 8) &amp; 3)    /* Data Scale */
DECL|macro|PCI_PWR_DATA_PM_SUB
mdefine_line|#define  PCI_PWR_DATA_PM_SUB(x)&t;(((x) &gt;&gt; 10) &amp; 7)   /* PM Sub State */
DECL|macro|PCI_PWR_DATA_PM_STATE
mdefine_line|#define  PCI_PWR_DATA_PM_STATE(x) (((x) &gt;&gt; 13) &amp; 3) /* PM State */
DECL|macro|PCI_PWR_DATA_TYPE
mdefine_line|#define  PCI_PWR_DATA_TYPE(x)&t;(((x) &gt;&gt; 15) &amp; 7)   /* Type */
DECL|macro|PCI_PWR_DATA_RAIL
mdefine_line|#define  PCI_PWR_DATA_RAIL(x)&t;(((x) &gt;&gt; 18) &amp; 7)   /* Power Rail */
DECL|macro|PCI_PWR_CAP
mdefine_line|#define PCI_PWR_CAP&t;&t;12&t;/* Capability */
DECL|macro|PCI_PWR_CAP_BUDGET
mdefine_line|#define  PCI_PWR_CAP_BUDGET(x)&t;((x) &amp; 1)&t;/* Included in system budget */
multiline_comment|/* Include the ID list */
macro_line|#include &lt;linux/pci_ids.h&gt;
multiline_comment|/*&n; * The PCI interface treats multi-function devices as independent&n; * devices.  The slot/function address of each device is encoded&n; * in a single byte as follows:&n; *&n; *&t;7:3 = slot&n; *&t;2:0 = function&n; */
DECL|macro|PCI_DEVFN
mdefine_line|#define PCI_DEVFN(slot,func)&t;((((slot) &amp; 0x1f) &lt;&lt; 3) | ((func) &amp; 0x07))
DECL|macro|PCI_SLOT
mdefine_line|#define PCI_SLOT(devfn)&t;&t;(((devfn) &gt;&gt; 3) &amp; 0x1f)
DECL|macro|PCI_FUNC
mdefine_line|#define PCI_FUNC(devfn)&t;&t;((devfn) &amp; 0x07)
multiline_comment|/* Ioctls for /proc/bus/pci/X/Y nodes. */
DECL|macro|PCIIOC_BASE
mdefine_line|#define PCIIOC_BASE&t;&t;(&squot;P&squot; &lt;&lt; 24 | &squot;C&squot; &lt;&lt; 16 | &squot;I&squot; &lt;&lt; 8)
DECL|macro|PCIIOC_CONTROLLER
mdefine_line|#define PCIIOC_CONTROLLER&t;(PCIIOC_BASE | 0x00)&t;/* Get controller for PCI device. */
DECL|macro|PCIIOC_MMAP_IS_IO
mdefine_line|#define PCIIOC_MMAP_IS_IO&t;(PCIIOC_BASE | 0x01)&t;/* Set mmap state to I/O space. */
DECL|macro|PCIIOC_MMAP_IS_MEM
mdefine_line|#define PCIIOC_MMAP_IS_MEM&t;(PCIIOC_BASE | 0x02)&t;/* Set mmap state to MEM space. */
DECL|macro|PCIIOC_WRITE_COMBINE
mdefine_line|#define PCIIOC_WRITE_COMBINE&t;(PCIIOC_BASE | 0x03)&t;/* Enable/disable write-combining. */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/device.h&gt;
multiline_comment|/* File state for mmap()s on /proc/bus/pci/X/Y */
DECL|enum|pci_mmap_state
r_enum
id|pci_mmap_state
(brace
DECL|enumerator|pci_mmap_io
id|pci_mmap_io
comma
DECL|enumerator|pci_mmap_mem
id|pci_mmap_mem
)brace
suffix:semicolon
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
DECL|macro|DEVICE_COUNT_RESOURCE
mdefine_line|#define DEVICE_COUNT_RESOURCE&t;12
DECL|typedef|pci_power_t
r_typedef
r_int
id|__bitwise
id|pci_power_t
suffix:semicolon
DECL|macro|PCI_D0
mdefine_line|#define PCI_D0&t;((pci_power_t __force) 0)
DECL|macro|PCI_D1
mdefine_line|#define PCI_D1&t;((pci_power_t __force) 1)
DECL|macro|PCI_D2
mdefine_line|#define PCI_D2&t;((pci_power_t __force) 2)
DECL|macro|PCI_D3hot
mdefine_line|#define PCI_D3hot&t;((pci_power_t __force) 3)
DECL|macro|PCI_D3cold
mdefine_line|#define PCI_D3cold&t;((pci_power_t __force) 4)
multiline_comment|/*&n; * The pci_dev structure is used to describe PCI devices.&n; */
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
DECL|member|dma_mask
id|u64
id|dma_mask
suffix:semicolon
multiline_comment|/* Mask of the bits of bus address this&n;&t;&t;&t;&t;&t;   device implements.  Normally this is&n;&t;&t;&t;&t;&t;   0xffffffff.  You only need to change&n;&t;&t;&t;&t;&t;   this if your device has broken DMA&n;&t;&t;&t;&t;&t;   or supports 64-bit transfers.  */
DECL|member|current_state
id|pci_power_t
id|current_state
suffix:semicolon
multiline_comment|/* Current operating state. In ACPI-speak,&n;&t;&t;&t;&t;&t;   this is D0-D3, D0 being fully functional,&n;&t;&t;&t;&t;&t;   and D3 being off. */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Generic device interface */
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
DECL|member|cfg_size
r_int
id|cfg_size
suffix:semicolon
multiline_comment|/* Size of configuration space */
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
multiline_comment|/* These fields are used by common fixups */
DECL|member|transparent
r_int
r_int
id|transparent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Transparent PCI bridge */
DECL|member|multifunction
r_int
r_int
id|multifunction
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Part of multi-function device */
multiline_comment|/* keep track of device state */
DECL|member|is_enabled
r_int
r_int
id|is_enabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* pci_enable_device has been called */
DECL|member|is_busmaster
r_int
r_int
id|is_busmaster
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device is busmaster */
DECL|member|saved_config_space
id|u32
id|saved_config_space
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* config space saved at suspend time */
DECL|member|rom_attr
r_struct
id|bin_attribute
op_star
id|rom_attr
suffix:semicolon
multiline_comment|/* attribute descriptor for sysfs ROM entry */
DECL|member|rom_attr_enabled
r_int
id|rom_attr_enabled
suffix:semicolon
multiline_comment|/* has display of the rom attribute been enabled? */
DECL|member|res_attr
r_struct
id|bin_attribute
op_star
id|res_attr
(braket
id|DEVICE_COUNT_RESOURCE
)braket
suffix:semicolon
multiline_comment|/* sysfs file for resources */
macro_line|#ifdef CONFIG_PCI_NAMES
DECL|macro|PCI_NAME_SIZE
mdefine_line|#define PCI_NAME_SIZE&t;255
DECL|macro|PCI_NAME_HALF
mdefine_line|#define PCI_NAME_HALF&t;__stringify(43)&t;/* less than half to handle slop */
DECL|member|pretty_name
r_char
id|pretty_name
(braket
id|PCI_NAME_SIZE
)braket
suffix:semicolon
multiline_comment|/* pretty name for users to see */
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|pci_dev_g
mdefine_line|#define pci_dev_g(n) list_entry(n, struct pci_dev, global_list)
DECL|macro|pci_dev_b
mdefine_line|#define pci_dev_b(n) list_entry(n, struct pci_dev, bus_list)
DECL|macro|to_pci_dev
mdefine_line|#define&t;to_pci_dev(n) container_of(n, struct pci_dev, dev)
DECL|macro|for_each_pci_dev
mdefine_line|#define for_each_pci_dev(d) while ((d = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, d)) != NULL)
multiline_comment|/*&n; *  For PCI devices, the region numbers are assigned this way:&n; *&n; *&t;0-5&t;standard PCI regions&n; *&t;6&t;expansion ROM&n; *&t;7-10&t;bridges: address space assigned to buses behind the bridge&n; */
DECL|macro|PCI_ROM_RESOURCE
mdefine_line|#define PCI_ROM_RESOURCE 6
DECL|macro|PCI_BRIDGE_RESOURCES
mdefine_line|#define PCI_BRIDGE_RESOURCES 7
DECL|macro|PCI_NUM_RESOURCES
mdefine_line|#define PCI_NUM_RESOURCES 11
macro_line|#ifndef PCI_BUS_NUM_RESOURCES
DECL|macro|PCI_BUS_NUM_RESOURCES
mdefine_line|#define PCI_BUS_NUM_RESOURCES 4
macro_line|#endif
DECL|macro|PCI_REGION_FLAG_MASK
mdefine_line|#define PCI_REGION_FLAG_MASK 0x0fU&t;/* These bits of resource flags tell us the PCI region flags */
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
id|PCI_BUS_NUM_RESOURCES
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
DECL|member|bridge_ctl
r_int
r_int
id|bridge_ctl
suffix:semicolon
multiline_comment|/* manage NO_ISA/FBB/et al behaviors */
DECL|member|pad2
r_int
r_int
id|pad2
suffix:semicolon
DECL|member|bridge
r_struct
id|device
op_star
id|bridge
suffix:semicolon
DECL|member|class_dev
r_struct
id|class_device
id|class_dev
suffix:semicolon
DECL|member|legacy_io
r_struct
id|bin_attribute
op_star
id|legacy_io
suffix:semicolon
multiline_comment|/* legacy I/O for this bus */
DECL|member|legacy_mem
r_struct
id|bin_attribute
op_star
id|legacy_mem
suffix:semicolon
multiline_comment|/* legacy mem */
)brace
suffix:semicolon
DECL|macro|pci_bus_b
mdefine_line|#define pci_bus_b(n)&t;list_entry(n, struct pci_bus, node)
DECL|macro|to_pci_bus
mdefine_line|#define to_pci_bus(n)&t;container_of(n, struct pci_bus, class_dev)
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
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|val
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_raw_ops
r_struct
id|pci_raw_ops
(brace
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_int
r_int
id|domain
comma
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
op_star
id|val
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_int
r_int
id|domain
comma
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
id|val
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|pci_raw_ops
op_star
id|raw_pci_ops
suffix:semicolon
DECL|struct|pci_bus_region
r_struct
id|pci_bus_region
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_dynids
r_struct
id|pci_dynids
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* protects list, index */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* for IDs added at runtime */
DECL|member|use_driver_data
r_int
r_int
id|use_driver_data
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* pci_driver-&gt;driver_data is used */
)brace
suffix:semicolon
r_struct
id|module
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
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|pci_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* must be non-NULL for probe to be called */
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
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|pm_message_t
id|state
)paren
suffix:semicolon
multiline_comment|/* Device suspended */
DECL|member|resume
r_int
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
DECL|member|enable_wake
r_int
(paren
op_star
id|enable_wake
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
comma
r_int
id|enable
)paren
suffix:semicolon
multiline_comment|/* Enable wake event */
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
DECL|member|dynids
r_struct
id|pci_dynids
id|dynids
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_pci_driver
mdefine_line|#define&t;to_pci_driver(drv) container_of(drv,struct pci_driver, driver)
multiline_comment|/**&n; * PCI_DEVICE - macro used to describe a specific pci device&n; * @vend: the 16 bit PCI Vendor ID&n; * @dev: the 16 bit PCI Device ID&n; *&n; * This macro is used to create a struct pci_device_id that matches a&n; * specific device.  The subvendor and subdevice fields will be set to&n; * PCI_ANY_ID.&n; */
DECL|macro|PCI_DEVICE
mdefine_line|#define PCI_DEVICE(vend,dev) &bslash;&n;&t;.vendor = (vend), .device = (dev), &bslash;&n;&t;.subvendor = PCI_ANY_ID, .subdevice = PCI_ANY_ID
multiline_comment|/**&n; * PCI_DEVICE_CLASS - macro used to describe a specific pci device class&n; * @dev_class: the class, subclass, prog-if triple for this device&n; * @dev_class_mask: the class mask for this device&n; *&n; * This macro is used to create a struct pci_device_id that matches a&n; * specific PCI class.  The vendor, device, subvendor, and subdevice &n; * fields will be set to PCI_ANY_ID.&n; */
DECL|macro|PCI_DEVICE_CLASS
mdefine_line|#define PCI_DEVICE_CLASS(dev_class,dev_class_mask) &bslash;&n;&t;.class = (dev_class), .class_mask = (dev_class_mask), &bslash;&n;&t;.vendor = PCI_ANY_ID, .device = PCI_ANY_ID, &bslash;&n;&t;.subvendor = PCI_ANY_ID, .subdevice = PCI_ANY_ID
multiline_comment|/* &n; * pci_module_init is obsolete, this stays here till we fix up all usages of it&n; * in the tree.&n; */
DECL|macro|pci_module_init
mdefine_line|#define pci_module_init&t;pci_register_driver
multiline_comment|/* these external functions are only available when PCI support is enabled */
macro_line|#ifdef CONFIG_PCI
r_extern
r_struct
id|bus_type
id|pci_bus_type
suffix:semicolon
multiline_comment|/* Do NOT directly access these two variables, unless you are arch specific pci&n; * code, or pci core code. */
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
comma
r_int
id|mask
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
comma
r_int
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
multiline_comment|/* Generic PCI functions used internally */
r_extern
r_struct
id|pci_bus
op_star
id|pci_find_bus
c_func
(paren
r_int
id|domain
comma
r_int
id|busnr
)paren
suffix:semicolon
r_struct
id|pci_bus
op_star
id|pci_scan_bus_parented
c_func
(paren
r_struct
id|device
op_star
id|parent
comma
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
DECL|function|pci_scan_bus
r_static
r_inline
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
(brace
r_return
id|pci_scan_bus_parented
c_func
(paren
l_int|NULL
comma
id|bus
comma
id|ops
comma
id|sysdata
)paren
suffix:semicolon
)brace
r_int
id|pci_scan_slot
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|devfn
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_scan_single_device
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|devfn
)paren
suffix:semicolon
r_int
r_int
id|pci_scan_child_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
r_void
id|pci_bus_add_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pci_bus_add_devices
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
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
r_extern
r_struct
id|pci_dev
op_star
id|pci_dev_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|pci_dev_put
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|pci_remove_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
suffix:semicolon
r_extern
r_void
id|pci_remove_bus_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
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
id|pci_find_device_reverse
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
id|pci_find_ext_capability
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
r_struct
id|pci_bus
op_star
id|pci_find_next_bus
c_func
(paren
r_const
r_struct
id|pci_bus
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_get_device
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_get_subsys
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
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_get_slot
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_get_class
(paren
r_int
r_int
r_class
comma
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
r_int
id|pci_dev_present
c_func
(paren
r_const
r_struct
id|pci_device_id
op_star
id|ids
)paren
suffix:semicolon
r_int
id|pci_bus_read_config_byte
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
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
id|pci_bus_read_config_word
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
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
id|pci_bus_read_config_dword
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
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
id|pci_bus_write_config_byte
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
id|u8
id|val
)paren
suffix:semicolon
r_int
id|pci_bus_write_config_word
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
id|u16
id|val
)paren
suffix:semicolon
r_int
id|pci_bus_write_config_dword
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
id|u32
id|val
)paren
suffix:semicolon
DECL|function|pci_read_config_byte
r_static
r_inline
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
(brace
r_return
id|pci_bus_read_config_byte
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pci_read_config_word
r_static
r_inline
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
(brace
r_return
id|pci_bus_read_config_word
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pci_read_config_dword
r_static
r_inline
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
(brace
r_return
id|pci_bus_read_config_dword
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pci_write_config_byte
r_static
r_inline
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
(brace
r_return
id|pci_bus_write_config_byte
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pci_write_config_word
r_static
r_inline
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
(brace
r_return
id|pci_bus_write_config_word
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pci_write_config_dword
r_static
r_inline
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
(brace
r_return
id|pci_bus_write_config_dword
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
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
r_int
id|pci_enable_device_bars
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|mask
)paren
suffix:semicolon
r_void
id|pci_disable_device
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
DECL|macro|HAVE_PCI_SET_MWI
mdefine_line|#define HAVE_PCI_SET_MWI
r_int
id|pci_set_mwi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pci_clear_mwi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pci_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
suffix:semicolon
r_int
id|pci_dac_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
suffix:semicolon
r_int
id|pci_set_consistent_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
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
multiline_comment|/* ROM control related routines */
r_void
id|__iomem
op_star
id|pci_map_rom
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
op_star
id|size
)paren
suffix:semicolon
r_void
id|__iomem
op_star
id|pci_map_rom_copy
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
op_star
id|size
)paren
suffix:semicolon
r_void
id|pci_unmap_rom
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_void
id|__iomem
op_star
id|rom
)paren
suffix:semicolon
r_void
id|pci_remove_rom
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/* Power management related routines */
r_int
id|pci_save_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pci_restore_state
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
id|pci_power_t
id|state
)paren
suffix:semicolon
id|pci_power_t
id|pci_choose_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|pm_message_t
id|state
)paren
suffix:semicolon
r_int
id|pci_enable_wake
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|pci_power_t
id|state
comma
r_int
id|enable
)paren
suffix:semicolon
multiline_comment|/* Helper functions for low-level code (drivers/pci/setup-[bus,res].c) */
r_void
id|pci_bus_assign_resources
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
r_void
id|pci_bus_size_bridges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
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
mdefine_line|#define HAVE_PCI_REQ_REGIONS&t;2
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
r_int
id|pci_request_region
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_void
id|pci_release_region
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* drivers/pci/bus.c */
r_int
id|pci_bus_alloc_resource
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
comma
r_int
r_int
id|min
comma
r_int
r_int
id|type_mask
comma
r_void
(paren
op_star
id|alignf
)paren
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
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
suffix:semicolon
r_void
id|pci_enable_bridges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
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
id|pci_remove_behind_bridge
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
r_int
id|pci_scan_bridge
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|max
comma
r_int
id|pass
)paren
suffix:semicolon
multiline_comment|/* kmem_cache style wrapper around pci_alloc_consistent() */
macro_line|#include &lt;linux/dmapool.h&gt;
DECL|macro|pci_pool
mdefine_line|#define&t;pci_pool dma_pool
DECL|macro|pci_pool_create
mdefine_line|#define pci_pool_create(name, pdev, size, align, allocation) &bslash;&n;&t;&t;dma_pool_create(name, &amp;pdev-&gt;dev, size, align, allocation)
DECL|macro|pci_pool_destroy
mdefine_line|#define&t;pci_pool_destroy(pool) dma_pool_destroy(pool)
DECL|macro|pci_pool_alloc
mdefine_line|#define&t;pci_pool_alloc(pool, flags, handle) dma_pool_alloc(pool, flags, handle)
DECL|macro|pci_pool_free
mdefine_line|#define&t;pci_pool_free(pool, vaddr, addr) dma_pool_free(pool, vaddr, addr)
macro_line|#if defined(CONFIG_ISA) || defined(CONFIG_EISA)
r_extern
r_struct
id|pci_dev
op_star
id|isa_bridge
suffix:semicolon
macro_line|#endif
DECL|struct|msix_entry
r_struct
id|msix_entry
(brace
DECL|member|vector
id|u16
id|vector
suffix:semicolon
multiline_comment|/* kernel uses to write allocated vector */
DECL|member|entry
id|u16
id|entry
suffix:semicolon
multiline_comment|/* driver uses to specify entry, OS writes */
)brace
suffix:semicolon
macro_line|#ifndef CONFIG_PCI_MSI
DECL|function|pci_scan_msi_device
r_static
r_inline
r_void
id|pci_scan_msi_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pci_enable_msi
r_static
r_inline
r_int
id|pci_enable_msi
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
l_int|1
suffix:semicolon
)brace
DECL|function|pci_disable_msi
r_static
r_inline
r_void
id|pci_disable_msi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pci_enable_msix
r_static
r_inline
r_int
id|pci_enable_msix
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|msix_entry
op_star
id|entries
comma
r_int
id|nvec
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pci_disable_msix
r_static
r_inline
r_void
id|pci_disable_msix
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|msi_remove_pci_irq_vectors
r_static
r_inline
r_void
id|msi_remove_pci_irq_vectors
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#else
r_extern
r_void
id|pci_scan_msi_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|pci_enable_msi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|pci_disable_msi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|pci_enable_msix
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|msix_entry
op_star
id|entries
comma
r_int
id|nvec
)paren
suffix:semicolon
r_extern
r_void
id|pci_disable_msix
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|msi_remove_pci_irq_vectors
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/* Include architecture-dependent settings and functions */
macro_line|#include &lt;asm/pci.h&gt;
multiline_comment|/*&n; *  If the system does not have PCI, clearly these return errors.  Define&n; *  these as simple inline functions to avoid hair in drivers.&n; */
macro_line|#ifndef CONFIG_PCI
DECL|macro|_PCI_NOP
mdefine_line|#define _PCI_NOP(o,s,t) &bslash;&n;&t;static inline int pci_##o##_config_##s (struct pci_dev *dev, int where, t val) &bslash;&n;&t;&t;{ return PCIBIOS_FUNC_NOT_SUPPORTED; }
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
DECL|function|pci_get_device
r_static
r_inline
r_struct
id|pci_dev
op_star
id|pci_get_device
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
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
DECL|function|pci_get_subsys
r_static
r_inline
r_struct
id|pci_dev
op_star
id|pci_get_subsys
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
DECL|function|pci_get_class
r_static
r_inline
r_struct
id|pci_dev
op_star
id|pci_get_class
c_func
(paren
r_int
r_int
r_class
comma
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
DECL|macro|pci_dev_present
mdefine_line|#define pci_dev_present(ids)&t;(0)
DECL|macro|pci_dev_put
mdefine_line|#define pci_dev_put(dev)&t;do { } while (0)
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
DECL|function|pci_disable_device
r_static
r_inline
r_void
id|pci_disable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pci_set_dma_mask
r_static
r_inline
r_int
id|pci_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|pci_dac_set_dma_mask
r_static
r_inline
r_int
id|pci_dac_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_return
op_minus
id|EIO
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
DECL|function|pci_find_ext_capability
r_static
r_inline
r_int
id|pci_find_ext_capability
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
DECL|function|pci_match_device
r_static
r_inline
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
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Power management related routines */
DECL|function|pci_save_state
r_static
r_inline
r_int
id|pci_save_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_restore_state
r_static
r_inline
r_int
id|pci_restore_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_set_power_state
r_static
r_inline
r_int
id|pci_set_power_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|pci_power_t
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_choose_state
r_static
r_inline
id|pci_power_t
id|pci_choose_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
r_return
id|PCI_D0
suffix:semicolon
)brace
DECL|function|pci_enable_wake
r_static
r_inline
r_int
id|pci_enable_wake
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|pci_power_t
id|state
comma
r_int
id|enable
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|isa_bridge
mdefine_line|#define&t;isa_bridge&t;((struct pci_dev *)NULL)
macro_line|#else
multiline_comment|/*&n; * PCI domain support.  Sometimes called PCI segment (eg by ACPI),&n; * a PCI domain is defined to be a set of PCI busses which share&n; * configuration space.&n; */
macro_line|#ifndef CONFIG_PCI_DOMAINS
DECL|function|pci_domain_nr
r_static
r_inline
r_int
id|pci_domain_nr
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_domain
r_static
r_inline
r_int
id|pci_proc_domain
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
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
multiline_comment|/* Similar to the helpers above, these manipulate per-pci_dev&n; * driver-specific data.  They are really just a wrapper around&n; * the generic device structure functions of these calls.&n; */
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
id|dev_get_drvdata
c_func
(paren
op_amp
id|pdev-&gt;dev
)paren
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
id|dev_set_drvdata
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/* If you want to know what to call your pci_dev, ask this function.&n; * Again, it&squot;s a wrapper around the generic device.&n; */
DECL|function|pci_name
r_static
r_inline
r_char
op_star
id|pci_name
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_return
id|pdev-&gt;dev.bus_id
suffix:semicolon
)brace
multiline_comment|/* Some archs want to see the pretty pci name, so use this macro */
macro_line|#ifdef CONFIG_PCI_NAMES
DECL|macro|pci_pretty_name
mdefine_line|#define pci_pretty_name(dev) ((dev)-&gt;pretty_name)
macro_line|#else
DECL|macro|pci_pretty_name
mdefine_line|#define pci_pretty_name(dev) &quot;&quot;
macro_line|#endif
multiline_comment|/*&n; *  The world is not perfect and supplies us with broken PCI devices.&n; *  For at least a part of these bugs we need a work-around, so both&n; *  generic (drivers/pci/quirks.c) and per-architecture code can define&n; *  fixup hooks to be called for particular buggy devices.&n; */
DECL|struct|pci_fixup
r_struct
id|pci_fixup
(brace
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
DECL|enum|pci_fixup_pass
r_enum
id|pci_fixup_pass
(brace
DECL|enumerator|pci_fixup_early
id|pci_fixup_early
comma
multiline_comment|/* Before probing BARs */
DECL|enumerator|pci_fixup_header
id|pci_fixup_header
comma
multiline_comment|/* After reading configuration header */
DECL|enumerator|pci_fixup_final
id|pci_fixup_final
comma
multiline_comment|/* Final phase of device fixups */
DECL|enumerator|pci_fixup_enable
id|pci_fixup_enable
comma
multiline_comment|/* pci_enable_device() time */
)brace
suffix:semicolon
multiline_comment|/* Anonymous variables would be nice... */
DECL|macro|DECLARE_PCI_FIXUP_SECTION
mdefine_line|#define DECLARE_PCI_FIXUP_SECTION(section, name, vendor, device, hook)&t;&bslash;&n;&t;static struct pci_fixup __pci_fixup_##name __attribute_used__&t;&bslash;&n;&t;__attribute__((__section__(#section))) = { vendor, device, hook };
DECL|macro|DECLARE_PCI_FIXUP_EARLY
mdefine_line|#define DECLARE_PCI_FIXUP_EARLY(vendor, device, hook)&t;&t;&t;&bslash;&n;&t;DECLARE_PCI_FIXUP_SECTION(.pci_fixup_early,&t;&t;&t;&bslash;&n;&t;&t;&t;vendor##device##hook, vendor, device, hook)
DECL|macro|DECLARE_PCI_FIXUP_HEADER
mdefine_line|#define DECLARE_PCI_FIXUP_HEADER(vendor, device, hook)&t;&t;&t;&bslash;&n;&t;DECLARE_PCI_FIXUP_SECTION(.pci_fixup_header,&t;&t;&t;&bslash;&n;&t;&t;&t;vendor##device##hook, vendor, device, hook)
DECL|macro|DECLARE_PCI_FIXUP_FINAL
mdefine_line|#define DECLARE_PCI_FIXUP_FINAL(vendor, device, hook)&t;&t;&t;&bslash;&n;&t;DECLARE_PCI_FIXUP_SECTION(.pci_fixup_final,&t;&t;&t;&bslash;&n;&t;&t;&t;vendor##device##hook, vendor, device, hook)
DECL|macro|DECLARE_PCI_FIXUP_ENABLE
mdefine_line|#define DECLARE_PCI_FIXUP_ENABLE(vendor, device, hook)&t;&t;&t;&bslash;&n;&t;DECLARE_PCI_FIXUP_SECTION(.pci_fixup_enable,&t;&t;&t;&bslash;&n;&t;&t;&t;vendor##device##hook, vendor, device, hook)
r_void
id|pci_fixup_device
c_func
(paren
r_enum
id|pci_fixup_pass
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
DECL|macro|PCIPCI_VSFX
mdefine_line|#define PCIPCI_VSFX&t;&t;16
DECL|macro|PCIPCI_ALIMAGIK
mdefine_line|#define PCIPCI_ALIMAGIK&t;&t;32
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_PCI_H */
eof
