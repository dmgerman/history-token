multiline_comment|/************************************************************************&n; *&n; *&t;USBVEND.H&t;&t;Vendor-specific USB definitions&n; *&n; *&t;NOTE: This must be kept in sync with the Edgeport firmware and&n; *&t;must be kept backward-compatible with older firmware.&n; *&n; ************************************************************************&n; *&n; *&t;Copyright (c) 1998 Inside Out Networks, Inc.&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; ************************************************************************/
macro_line|#if !defined(_USBVEND_H)
DECL|macro|_USBVEND_H
mdefine_line|#define&t;_USBVEND_H
macro_line|#ifndef __KERNEL__
macro_line|#include &quot;ionprag.h&quot;&t;/* Extra I/O Networks pragmas */
macro_line|#include &lt;usbdi.h&gt;
macro_line|#include &quot;iondef.h&quot;&t;/* Standard I/O Networks definitions */
macro_line|#endif
multiline_comment|/************************************************************************&n; *&n; *&t;&t;D e f i n e s   /   T y p e d e f s&n; *&n; ************************************************************************/
singleline_comment|//
singleline_comment|// Definitions of USB product IDs
singleline_comment|// 
DECL|macro|USB_VENDOR_ID_ION
mdefine_line|#define&t;USB_VENDOR_ID_ION&t;0x1608&t;&t;
singleline_comment|// Our VID
singleline_comment|//
singleline_comment|// Definitions of USB product IDs (PID)
singleline_comment|// We break the USB-defined PID into an OEM Id field (upper 6 bits)
singleline_comment|// and a Device Id (bottom 10 bits). The Device Id defines what
singleline_comment|// device this actually is regardless of what the OEM wants to
singleline_comment|// call it.
singleline_comment|//
singleline_comment|// ION-device OEM IDs
DECL|macro|ION_OEM_ID_ION
mdefine_line|#define&t;ION_OEM_ID_ION&t;&t;0&t;&t;
singleline_comment|// 00h Inside Out Networks
DECL|macro|ION_OEM_ID_NLYNX
mdefine_line|#define&t;ION_OEM_ID_NLYNX&t;1&t;&t;
singleline_comment|// 01h NLynx Systems&t;  
DECL|macro|ION_OEM_ID_GENERIC
mdefine_line|#define&t;ION_OEM_ID_GENERIC&t;2&t;&t;
singleline_comment|// 02h Generic OEM
DECL|macro|ION_OEM_ID_MAC
mdefine_line|#define&t;ION_OEM_ID_MAC&t;&t;3&t;&t;
singleline_comment|// 03h Mac Version
DECL|macro|ION_OEM_ID_MEGAWOLF
mdefine_line|#define&t;ION_OEM_ID_MEGAWOLF&t;4&t;&t;
singleline_comment|// 04h Lupusb OEM Mac version (MegaWolf)
DECL|macro|ION_OEM_ID_MULTITECH
mdefine_line|#define&t;ION_OEM_ID_MULTITECH&t;5&t;&t;
singleline_comment|// 05h Multitech Rapidports
singleline_comment|// ION-device Device IDs
singleline_comment|// Product IDs - assigned to match middle digit of serial number
singleline_comment|// The ION_DEVICE_ID_GENERATION_2 bit (0x20) will be ORed into the existing edgeport
singleline_comment|// PIDs to identify 80251+Netchip hardware.  This will guarantee that if a second
singleline_comment|// generation edgeport device is plugged into a PC with an older (pre 2.0) driver,
singleline_comment|// it will not enumerate.
DECL|macro|ION_DEVICE_ID_GENERATION_2
mdefine_line|#define ION_DEVICE_ID_GENERATION_2&t;0x020&t;
singleline_comment|// This bit is set in the PID if this edgeport hardware
singleline_comment|// is based on the 80251+Netchip.  
DECL|macro|EDGEPORT_DEVICE_ID_MASK
mdefine_line|#define EDGEPORT_DEVICE_ID_MASK&t;&t;&t;0x3df&t;
singleline_comment|// Not including GEN_2 bit
DECL|macro|ION_DEVICE_ID_UNCONFIGURED_EDGE_DEVICE
mdefine_line|#define&t;ION_DEVICE_ID_UNCONFIGURED_EDGE_DEVICE&t;0x000&t;
singleline_comment|// In manufacturing only
DECL|macro|ION_DEVICE_ID_EDGEPORT_4
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4&t;&t;0x001&t;
singleline_comment|// Edgeport/4 RS232
singleline_comment|//&t;ION_DEVICE_ID_HUBPORT_7&t;&t;&t;0x002&t;// Hubport/7 (Placeholder, not used by software)
DECL|macro|ION_DEVICE_ID_RAPIDPORT_4
mdefine_line|#define ION_DEVICE_ID_RAPIDPORT_4&t;&t;0x003&t;
singleline_comment|// Rapidport/4
DECL|macro|ION_DEVICE_ID_EDGEPORT_4T
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4T&t;&t;0x004&t;
singleline_comment|// Edgeport/4 RS232 for Telxon (aka &quot;Fleetport&quot;)
DECL|macro|ION_DEVICE_ID_EDGEPORT_2
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_2&t;&t;0x005&t;
singleline_comment|// Edgeport/2 RS232
DECL|macro|ION_DEVICE_ID_EDGEPORT_4I
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4I&t;&t;0x006&t;
singleline_comment|// Edgeport/4 RS422
DECL|macro|ION_DEVICE_ID_EDGEPORT_2I
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_2I&t;&t;0x007&t;
singleline_comment|// Edgeport/2 RS422/RS485
singleline_comment|//&t;ION_DEVICE_ID_HUBPORT_4&t;&t;&t;0x008&t;// Hubport/4 (Placeholder, not used by software)
singleline_comment|//&t;ION_DEVICE_ID_EDGEPORT_8_HANDBUILT&t;0x009&t;// Hand-built Edgeport/8 (Placeholder, used in middle digit of serial number only!)
singleline_comment|//&t;ION_DEVICE_ID_MULTIMODEM_4X56&t;&t;0x00A&t;// MultiTech version of RP/4 (Placeholder, used in middle digit of serial number only!)
DECL|macro|ION_DEVICE_ID_EDGEPORT_PARALLEL_PORT
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_PARALLEL_PORT&t;0x00B&t;
singleline_comment|// Edgeport/(4)21 Parallel port (USS720)
DECL|macro|ION_DEVICE_ID_EDGEPORT_421
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_421&t;&t;0x00C&t;
singleline_comment|// Edgeport/421 Hub+RS232+Parallel
DECL|macro|ION_DEVICE_ID_EDGEPORT_21
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_21&t;&t;0x00D&t;
singleline_comment|// Edgeport/21  RS232+Parallel
DECL|macro|ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU&t;0x00E&t;
singleline_comment|// Half of an Edgeport/8 (the kind with 2 EP/4s on 1 PCB)
DECL|macro|ION_DEVICE_ID_EDGEPORT_8
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_8&t;&t;0x00F&t;
singleline_comment|// Edgeport/8 (single-CPU)
DECL|macro|ION_DEVICE_ID_EDGEPORT_2_DIN
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_2_DIN&t;&t;0x010&t;
singleline_comment|// Edgeport/2 RS232 with Apple DIN connector
DECL|macro|ION_DEVICE_ID_EDGEPORT_4_DIN
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4_DIN&t;&t;0x011&t;
singleline_comment|// Edgeport/4 RS232 with Apple DIN connector
DECL|macro|ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU&t;0x012&t;
singleline_comment|// Half of an Edgeport/16 (the kind with 2 EP/8s)
DECL|macro|ION_DEVICE_ID_EDGEPORT_COMPATIBLE
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_COMPATIBLE&t;0x013&t;
singleline_comment|// Edgeport Compatible, for NCR, Axiohm etc. testing
DECL|macro|ION_DEVICE_ID_EDGEPORT_8I
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_8I&t;&t;0x014&t;
singleline_comment|// Edgeport/8 RS422 (single-CPU)
singleline_comment|// These IDs are used by the Edgeport.exe program for uninstalling.
singleline_comment|// 
DECL|macro|EDGEPORT_DEVICE_IDS
mdefine_line|#define EDGEPORT_DEVICE_IDS&t;{0x001, 0x003, 0x004, 0x005, 0x006, 0x007, 0x00B, &bslash;&n;&t;&t;&t;&t; 0x00C, 0x00D, 0x00E, 0x00F, 0x010, 0x011, 0x012, &bslash;&n;&t;&t;&t;&t; 0x013, 0x014 }
DECL|macro|MAKE_USB_PRODUCT_ID
mdefine_line|#define&t;MAKE_USB_PRODUCT_ID( OemId, DeviceId )&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;( (__u16) (((OemId) &lt;&lt; 10) || (DeviceId)) )
DECL|macro|DEVICE_ID_FROM_USB_PRODUCT_ID
mdefine_line|#define&t;DEVICE_ID_FROM_USB_PRODUCT_ID( ProductId )&t;&t;&t;&t;&bslash;&n;&t;&t;&t;( (__u16) ((ProductId) &amp; (EDGEPORT_DEVICE_ID_MASK)) )
DECL|macro|OEM_ID_FROM_USB_PRODUCT_ID
mdefine_line|#define&t;OEM_ID_FROM_USB_PRODUCT_ID( ProductId )&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;( (__u16) (((ProductId) &gt;&gt; 10) &amp; 0x3F) )
singleline_comment|//
singleline_comment|// Definitions of parameters for download code. Note that these are
singleline_comment|// specific to a given version of download code and must change if the
singleline_comment|// corresponding download code changes.
singleline_comment|//
singleline_comment|// TxCredits value below which driver won&squot;t bother sending (to prevent too many small writes).
singleline_comment|// Send only if above 25%
DECL|macro|EDGE_FW_GET_TX_CREDITS_SEND_THRESHOLD
mdefine_line|#define EDGE_FW_GET_TX_CREDITS_SEND_THRESHOLD(InitialCredit)&t;(max_t(int, ((InitialCredit) / 4), EDGE_FW_BULK_MAX_PACKET_SIZE))
DECL|macro|EDGE_FW_BULK_MAX_PACKET_SIZE
mdefine_line|#define&t;EDGE_FW_BULK_MAX_PACKET_SIZE&t;&t;64&t;
singleline_comment|// Max Packet Size for Bulk In Endpoint (EP1)
DECL|macro|EDGE_FW_BULK_READ_BUFFER_SIZE
mdefine_line|#define EDGE_FW_BULK_READ_BUFFER_SIZE&t;&t;1024&t;
singleline_comment|// Size to use for Bulk reads
DECL|macro|EDGE_FW_INT_MAX_PACKET_SIZE
mdefine_line|#define&t;EDGE_FW_INT_MAX_PACKET_SIZE&t;&t;32&t;
singleline_comment|// Max Packet Size for Interrupt In Endpoint
singleline_comment|// Note that many units were shipped with MPS=16, we
singleline_comment|// force an upgrade to this value).
DECL|macro|EDGE_FW_INT_INTERVAL
mdefine_line|#define EDGE_FW_INT_INTERVAL&t;&t;&t;2&t;
singleline_comment|// 2ms polling on IntPipe
singleline_comment|//
singleline_comment|// Definitions of I/O Networks vendor-specific requests
singleline_comment|// for default endpoint
singleline_comment|//
singleline_comment|//&t;bmRequestType = 00100000&t;Set vendor-specific, to device
singleline_comment|//&t;bmRequestType = 10100000&t;Get vendor-specific, to device
singleline_comment|//
singleline_comment|// These are the definitions for the bRequest field for the
singleline_comment|// above bmRequestTypes.
singleline_comment|//
singleline_comment|// For the read/write Edgeport memory commands, the parameters
singleline_comment|// are as follows:
singleline_comment|//&t;&t;wValue = 16-bit address
singleline_comment|//&t;&t;wIndex = unused (though we could put segment 00: or FF: here)
singleline_comment|//&t;&t;wLength = # bytes to read/write (max 64)
singleline_comment|//&t;&t;&t;&t;&t;&t;&t;
DECL|macro|USB_REQUEST_ION_RESET_DEVICE
mdefine_line|#define USB_REQUEST_ION_RESET_DEVICE&t;0&t;
singleline_comment|// Warm reboot Edgeport, retaining USB address
DECL|macro|USB_REQUEST_ION_GET_EPIC_DESC
mdefine_line|#define USB_REQUEST_ION_GET_EPIC_DESC&t;1&t;
singleline_comment|// Get Edgeport Compatibility Descriptor
singleline_comment|// unused&t;&t;&t;&t;2&t;// Unused, available
DECL|macro|USB_REQUEST_ION_READ_RAM
mdefine_line|#define USB_REQUEST_ION_READ_RAM&t;3&t;
singleline_comment|// Read  EdgePort RAM at specified addr
DECL|macro|USB_REQUEST_ION_WRITE_RAM
mdefine_line|#define USB_REQUEST_ION_WRITE_RAM&t;4&t;
singleline_comment|// Write EdgePort RAM at specified addr
DECL|macro|USB_REQUEST_ION_READ_ROM
mdefine_line|#define USB_REQUEST_ION_READ_ROM&t;5&t;
singleline_comment|// Read  EdgePort ROM at specified addr
DECL|macro|USB_REQUEST_ION_WRITE_ROM
mdefine_line|#define USB_REQUEST_ION_WRITE_ROM&t;6&t;
singleline_comment|// Write EdgePort ROM at specified addr
DECL|macro|USB_REQUEST_ION_EXEC_DL_CODE
mdefine_line|#define USB_REQUEST_ION_EXEC_DL_CODE&t;7&t;
singleline_comment|// Begin execution of RAM-based download
singleline_comment|// code by jumping to address in wIndex:wValue
singleline_comment|//&t;&t;&t;&t;&t;8&t;// Unused, available
DECL|macro|USB_REQUEST_ION_ENABLE_SUSPEND
mdefine_line|#define USB_REQUEST_ION_ENABLE_SUSPEND&t;9&t;
singleline_comment|// Enable/Disable suspend feature
singleline_comment|// (wValue != 0: Enable; wValue = 0: Disable)
singleline_comment|//
singleline_comment|// Define parameter values for our vendor-specific commands
singleline_comment|//
singleline_comment|// Values for iDownloadFile
DECL|macro|EDGE_DOWNLOAD_FILE_NONE
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_NONE&t;&t;0&t;
singleline_comment|// No download requested
DECL|macro|EDGE_DOWNLOAD_FILE_INTERNAL
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_INTERNAL&t;0xFF&t;
singleline_comment|// Download the file compiled into driver (930 version)
DECL|macro|EDGE_DOWNLOAD_FILE_I930
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_I930&t;&t;0xFF&t;
singleline_comment|// Download the file compiled into driver (930 version)
DECL|macro|EDGE_DOWNLOAD_FILE_80251
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_80251&t;0xFE&t;
singleline_comment|// Download the file compiled into driver (80251 version)
multiline_comment|/*&n; *&t;Special addresses for READ/WRITE_RAM/ROM&n; */
singleline_comment|// Version 1 (original) format of DeviceParams
DECL|macro|EDGE_MANUF_DESC_ADDR_V1
mdefine_line|#define&t;EDGE_MANUF_DESC_ADDR_V1&t;&t;0x00FF7F00
DECL|macro|EDGE_MANUF_DESC_LEN_V1
mdefine_line|#define&t;EDGE_MANUF_DESC_LEN_V1&t;&t;sizeof(EDGE_MANUF_DESCRIPTOR_V1)
singleline_comment|// Version 2 format of DeviceParams. This format is longer (3C0h)
singleline_comment|// and starts lower in memory, at the uppermost 1K in ROM.
DECL|macro|EDGE_MANUF_DESC_ADDR
mdefine_line|#define&t;EDGE_MANUF_DESC_ADDR&t;&t;0x00FF7C00
DECL|macro|EDGE_MANUF_DESC_LEN
mdefine_line|#define&t;EDGE_MANUF_DESC_LEN&t;&t;sizeof(EDGE_MANUF_DESCRIPTOR)
singleline_comment|// Boot params descriptor
DECL|macro|EDGE_BOOT_DESC_ADDR
mdefine_line|#define&t;EDGE_BOOT_DESC_ADDR&t;&t;0x00FF7FC0
DECL|macro|EDGE_BOOT_DESC_LEN
mdefine_line|#define&t;EDGE_BOOT_DESC_LEN&t;&t;sizeof(EDGE_BOOT_DESCRIPTOR)
singleline_comment|// Define the max block size that may be read or written
singleline_comment|// in a read/write RAM/ROM command.
DECL|macro|MAX_SIZE_REQ_ION_READ_MEM
mdefine_line|#define&t;MAX_SIZE_REQ_ION_READ_MEM&t;( (__u16) 64 )
DECL|macro|MAX_SIZE_REQ_ION_WRITE_MEM
mdefine_line|#define&t;MAX_SIZE_REQ_ION_WRITE_MEM&t;( (__u16) 64 )
singleline_comment|//
singleline_comment|// Notes for the following two ION vendor-specific param descriptors:
singleline_comment|//
singleline_comment|//&t;1.&t;These have a standard USB descriptor header so they look like a
singleline_comment|//&t;&t;normal descriptor.
singleline_comment|//&t;2.&t;Any strings in the structures are in USB-defined string
singleline_comment|//&t;&t;descriptor format, so that they may be separately retrieved,
singleline_comment|//&t;&t;if necessary, with a minimum of work on the 930. This also
singleline_comment|//&t;&t;requires them to be in UNICODE format, which, for English at
singleline_comment|//&t;&t;least, simply means extending each UCHAR into a USHORT.
singleline_comment|//&t;3.&t;For all fields, 00 means &squot;uninitialized&squot;.
singleline_comment|//&t;4.&t;All unused areas should be set to 00 for future expansion.
singleline_comment|//
singleline_comment|// This structure is ver 2 format. It contains ALL USB descriptors as
singleline_comment|// well as the configuration parameters that were in the original V1
singleline_comment|// structure. It is NOT modified when new boot code is downloaded; rather,
singleline_comment|// these values are set or modified by manufacturing. It is located at
singleline_comment|// xC00-xFBF (length 3C0h) in the ROM.
singleline_comment|// This structure is a superset of the v1 structure and is arranged so
singleline_comment|// that all of the v1 fields remain at the same address. We are just
singleline_comment|// adding more room to the front of the structure to hold the descriptors.
singleline_comment|//
singleline_comment|// The actual contents of this structure are defined in a 930 assembly
singleline_comment|// file, converted to a binary image, and then written by the serialization
singleline_comment|// program. The C definition of this structure just defines a dummy
singleline_comment|// area for general USB descriptors and the descriptor tables (the root
singleline_comment|// descriptor starts at xC00). At the bottom of the structure are the
singleline_comment|// fields inherited from the v1 structure.
DECL|macro|MAX_SERIALNUMBER_LEN
mdefine_line|#define MAX_SERIALNUMBER_LEN&t;12
DECL|macro|MAX_ASSEMBLYNUMBER_LEN
mdefine_line|#define MAX_ASSEMBLYNUMBER_LEN&t;14
DECL|struct|_EDGE_MANUF_DESCRIPTOR
r_typedef
r_struct
id|_EDGE_MANUF_DESCRIPTOR
(brace
DECL|member|RootDescTable
id|__u16
id|RootDescTable
(braket
l_int|0x10
)braket
suffix:semicolon
singleline_comment|// C00 Root of descriptor tables (just a placeholder)
DECL|member|DescriptorArea
id|__u8
id|DescriptorArea
(braket
l_int|0x2E0
)braket
suffix:semicolon
singleline_comment|// C20 Descriptors go here, up to 2E0h (just a placeholder)
singleline_comment|//     Start of v1-compatible section
DECL|member|Length
id|__u8
id|Length
suffix:semicolon
singleline_comment|// F00 Desc length for what follows, per USB (= C0h )
DECL|member|DescType
id|__u8
id|DescType
suffix:semicolon
singleline_comment|// F01 Desc type, per USB (=DEVICE type)
DECL|member|DescVer
id|__u8
id|DescVer
suffix:semicolon
singleline_comment|// F02 Desc version/format (currently 2)
DECL|member|NumRootDescEntries
id|__u8
id|NumRootDescEntries
suffix:semicolon
singleline_comment|// F03 # entries in RootDescTable
DECL|member|RomSize
id|__u8
id|RomSize
suffix:semicolon
singleline_comment|// F04 Size of ROM/E2PROM in K
DECL|member|RamSize
id|__u8
id|RamSize
suffix:semicolon
singleline_comment|// F05 Size of external RAM in K
DECL|member|CpuRev
id|__u8
id|CpuRev
suffix:semicolon
singleline_comment|// F06 CPU revision level (chg only if s/w visible)
DECL|member|BoardRev
id|__u8
id|BoardRev
suffix:semicolon
singleline_comment|// F07 PCB revision level (chg only if s/w visible)
DECL|member|NumPorts
id|__u8
id|NumPorts
suffix:semicolon
singleline_comment|// F08 Number of ports
DECL|member|DescDate
id|__u8
id|DescDate
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// F09 MM/DD/YY when descriptor template was compiler,
singleline_comment|//&t;   so host can track changes to USB-only descriptors.
DECL|member|SerNumLength
id|__u8
id|SerNumLength
suffix:semicolon
singleline_comment|// F0C USB string descriptor len
DECL|member|SerNumDescType
id|__u8
id|SerNumDescType
suffix:semicolon
singleline_comment|// F0D USB descriptor type (=STRING type)
DECL|member|SerialNumber
id|__u16
id|SerialNumber
(braket
id|MAX_SERIALNUMBER_LEN
)braket
suffix:semicolon
singleline_comment|// F0E &quot;01-01-000100&quot; Unicode Serial Number
DECL|member|AssemblyNumLength
id|__u8
id|AssemblyNumLength
suffix:semicolon
singleline_comment|// F26 USB string descriptor len
DECL|member|AssemblyNumDescType
id|__u8
id|AssemblyNumDescType
suffix:semicolon
singleline_comment|// F27 USB descriptor type (=STRING type)
DECL|member|AssemblyNumber
id|__u16
id|AssemblyNumber
(braket
id|MAX_ASSEMBLYNUMBER_LEN
)braket
suffix:semicolon
singleline_comment|// F28 &quot;350-1000-01-A &quot; assembly number
DECL|member|OemAssyNumLength
id|__u8
id|OemAssyNumLength
suffix:semicolon
singleline_comment|// F44 USB string descriptor len
DECL|member|OemAssyNumDescType
id|__u8
id|OemAssyNumDescType
suffix:semicolon
singleline_comment|// F45 USB descriptor type (=STRING type)
DECL|member|OemAssyNumber
id|__u16
id|OemAssyNumber
(braket
id|MAX_ASSEMBLYNUMBER_LEN
)braket
suffix:semicolon
singleline_comment|// F46 &quot;xxxxxxxxxxxxxx&quot; OEM assembly number
DECL|member|ManufDateLength
id|__u8
id|ManufDateLength
suffix:semicolon
singleline_comment|// F62 USB string descriptor len
DECL|member|ManufDateDescType
id|__u8
id|ManufDateDescType
suffix:semicolon
singleline_comment|// F63 USB descriptor type (=STRING type)
DECL|member|ManufDate
id|__u16
id|ManufDate
(braket
l_int|6
)braket
suffix:semicolon
singleline_comment|// F64 &quot;MMDDYY&quot; manufacturing date
DECL|member|Reserved3
id|__u8
id|Reserved3
(braket
l_int|0x4D
)braket
suffix:semicolon
singleline_comment|// F70 -- unused, set to 0 --
DECL|member|UartType
id|__u8
id|UartType
suffix:semicolon
singleline_comment|// FBD Uart Type
DECL|member|IonPid
id|__u8
id|IonPid
suffix:semicolon
singleline_comment|// FBE Product ID, == LSB of USB DevDesc.PID
singleline_comment|//     (Note: Edgeport/4s before 11/98 will have
singleline_comment|//&t;&t;00 here instead of 01)
DECL|member|IonConfig
id|__u8
id|IonConfig
suffix:semicolon
singleline_comment|// FBF Config byte for ION manufacturing use
singleline_comment|// FBF end of structure, total len = 3C0h
DECL|typedef|EDGE_MANUF_DESCRIPTOR
DECL|typedef|PEDGE_MANUF_DESCRIPTOR
)brace
id|EDGE_MANUF_DESCRIPTOR
comma
op_star
id|PEDGE_MANUF_DESCRIPTOR
suffix:semicolon
DECL|macro|MANUF_DESC_VER_1
mdefine_line|#define MANUF_DESC_VER_1&t;1&t;
singleline_comment|// Original definition of MANUF_DESC
DECL|macro|MANUF_DESC_VER_2
mdefine_line|#define MANUF_DESC_VER_2&t;2&t;
singleline_comment|// Ver 2, starts at xC00h len 3C0h
singleline_comment|// Uart Types
singleline_comment|// Note: Since this field was added only recently, all Edgeport/4 units
singleline_comment|// shipped before 11/98 will have 00 in this field. Therefore,
singleline_comment|// both 00 and 01 values mean &squot;654.
DECL|macro|MANUF_UART_EXAR_654_EARLY
mdefine_line|#define MANUF_UART_EXAR_654_EARLY&t;0&t;
singleline_comment|// Exar 16C654 in Edgeport/4s before 11/98
DECL|macro|MANUF_UART_EXAR_654
mdefine_line|#define MANUF_UART_EXAR_654&t;&t;1&t;
singleline_comment|// Exar 16C654
DECL|macro|MANUF_UART_EXAR_2852
mdefine_line|#define MANUF_UART_EXAR_2852&t;&t;2&t;
singleline_comment|// Exar 16C2852 
singleline_comment|//
singleline_comment|// Note: The CpuRev and BoardRev values do not conform to manufacturing
singleline_comment|// revisions; they are to be incremented only when the CPU or hardware
singleline_comment|// changes in a software-visible way, such that the 930 software or
singleline_comment|// the host driver needs to handle the hardware differently.
singleline_comment|//
singleline_comment|// Values of bottom 5 bits of CpuRev &amp; BoardRev for
singleline_comment|// Implementation 0 (ie, 930-based)
DECL|macro|MANUF_CPU_REV_AD4
mdefine_line|#define&t;MANUF_CPU_REV_AD4&t;&t;1&t;
singleline_comment|// 930 AD4, with EP1 Rx bug (needs RXSPM)
DECL|macro|MANUF_CPU_REV_AD5
mdefine_line|#define&t;MANUF_CPU_REV_AD5&t;&t;2&t;
singleline_comment|// 930 AD5, with above bug (supposedly) fixed
DECL|macro|MANUF_CPU_80251
mdefine_line|#define&t;MANUF_CPU_80251&t;&t;&t;0x20&t;
singleline_comment|// Intel 80251
DECL|macro|MANUF_BOARD_REV_A
mdefine_line|#define MANUF_BOARD_REV_A&t;&t;1&t;
singleline_comment|// Original version, == Manuf Rev A
DECL|macro|MANUF_BOARD_REV_B
mdefine_line|#define MANUF_BOARD_REV_B&t;&t;2&t;
singleline_comment|// Manuf Rev B, wakeup interrupt works
DECL|macro|MANUF_BOARD_REV_C
mdefine_line|#define MANUF_BOARD_REV_C&t;&t;3&t;
singleline_comment|// Manuf Rev C, 2/4 ports, rs232/rs422
DECL|macro|MANUF_BOARD_REV_GENERATION_2
mdefine_line|#define MANUF_BOARD_REV_GENERATION_2&t;0x20&t;
singleline_comment|// Second generaiton edgeport
singleline_comment|// Values of bottom 5 bits of CpuRev &amp; BoardRev for
singleline_comment|// Implementation 1 (ie, 251+Netchip-based)
DECL|macro|MANUF_CPU_REV_1
mdefine_line|#define&t;MANUF_CPU_REV_1&t;&t;&t;1&t;
singleline_comment|// C251TB Rev 1 (Need actual Intel rev here)
DECL|macro|MANUF_BOARD_REV_A
mdefine_line|#define MANUF_BOARD_REV_A&t;&t;1&t;
singleline_comment|// First rev of 251+Netchip design
DECL|macro|MANUF_SERNUM_LENGTH
mdefine_line|#define&t;MANUF_SERNUM_LENGTH&t;&t;sizeof(((PEDGE_MANUF_DESCRIPTOR)0)-&gt;SerialNumber)
DECL|macro|MANUF_ASSYNUM_LENGTH
mdefine_line|#define&t;MANUF_ASSYNUM_LENGTH&t;&t;sizeof(((PEDGE_MANUF_DESCRIPTOR)0)-&gt;AssemblyNumber)
DECL|macro|MANUF_OEMASSYNUM_LENGTH
mdefine_line|#define&t;MANUF_OEMASSYNUM_LENGTH&t;&t;sizeof(((PEDGE_MANUF_DESCRIPTOR)0)-&gt;OemAssyNumber)
DECL|macro|MANUF_MANUFDATE_LENGTH
mdefine_line|#define&t;MANUF_MANUFDATE_LENGTH&t;&t;sizeof(((PEDGE_MANUF_DESCRIPTOR)0)-&gt;ManufDate)
DECL|macro|MANUF_ION_CONFIG_MASTER
mdefine_line|#define&t;MANUF_ION_CONFIG_MASTER&t;&t;0x80&t;
singleline_comment|// 1=Master mode, 0=Normal
DECL|macro|MANUF_ION_CONFIG_DIAG
mdefine_line|#define&t;MANUF_ION_CONFIG_DIAG&t;&t;0x40&t;
singleline_comment|// 1=Run h/w diags, 0=norm
DECL|macro|MANUF_ION_CONFIG_DIAG_NO_LOOP
mdefine_line|#define&t;MANUF_ION_CONFIG_DIAG_NO_LOOP&t;0x20&t;
singleline_comment|// As above but no ext loopback test
singleline_comment|//
singleline_comment|// This structure describes parameters for the boot code, and
singleline_comment|// is programmed along with new boot code. These are values
singleline_comment|// which are specific to a given build of the boot code. It
singleline_comment|// is exactly 64 bytes long and is fixed at address FF:xFC0
singleline_comment|// - FF:xFFF. Note that the 930-mandated UCONFIG bytes are
singleline_comment|// included in this structure.
singleline_comment|//
DECL|struct|_EDGE_BOOT_DESCRIPTOR
r_typedef
r_struct
id|_EDGE_BOOT_DESCRIPTOR
(brace
DECL|member|Length
id|__u8
id|Length
suffix:semicolon
singleline_comment|// C0 Desc length, per USB (= 40h)
DECL|member|DescType
id|__u8
id|DescType
suffix:semicolon
singleline_comment|// C1 Desc type, per USB (= DEVICE type)
DECL|member|DescVer
id|__u8
id|DescVer
suffix:semicolon
singleline_comment|// C2 Desc version/format
DECL|member|Reserved1
id|__u8
id|Reserved1
suffix:semicolon
singleline_comment|// C3 -- unused, set to 0 --
DECL|member|BootCodeLength
id|__u16
id|BootCodeLength
suffix:semicolon
singleline_comment|// C4 Boot code goes from FF:0000 to FF:(len-1)
singleline_comment|//&t;  (LE format)
DECL|member|MajorVersion
id|__u8
id|MajorVersion
suffix:semicolon
singleline_comment|// C6 Firmware version: xx.
DECL|member|MinorVersion
id|__u8
id|MinorVersion
suffix:semicolon
singleline_comment|// C7&t;&t;&t;yy.
DECL|member|BuildNumber
id|__u16
id|BuildNumber
suffix:semicolon
singleline_comment|// C8&t;&t;&t;zzzz (LE format)
DECL|member|EnumRootDescTable
id|__u16
id|EnumRootDescTable
suffix:semicolon
singleline_comment|// CA Root of ROM-based descriptor table
DECL|member|NumDescTypes
id|__u8
id|NumDescTypes
suffix:semicolon
singleline_comment|// CC Number of supported descriptor types
DECL|member|Reserved4
id|__u8
id|Reserved4
suffix:semicolon
singleline_comment|// CD Fix Compiler Packing
DECL|member|Capabilities
id|__u16
id|Capabilities
suffix:semicolon
singleline_comment|// CE-CF Capabilities flags (LE format)
DECL|member|Reserved2
id|__u8
id|Reserved2
(braket
l_int|0x28
)braket
suffix:semicolon
singleline_comment|// D0 -- unused, set to 0 --
DECL|member|UConfig0
id|__u8
id|UConfig0
suffix:semicolon
singleline_comment|// F8 930-defined CPU configuration byte 0
DECL|member|UConfig1
id|__u8
id|UConfig1
suffix:semicolon
singleline_comment|// F9 930-defined CPU configuration byte 1
DECL|member|Reserved3
id|__u8
id|Reserved3
(braket
l_int|6
)braket
suffix:semicolon
singleline_comment|// FA -- unused, set to 0 --
singleline_comment|// FF end of structure, total len = 80
DECL|typedef|EDGE_BOOT_DESCRIPTOR
DECL|typedef|PEDGE_BOOT_DESCRIPTOR
)brace
id|EDGE_BOOT_DESCRIPTOR
comma
op_star
id|PEDGE_BOOT_DESCRIPTOR
suffix:semicolon
DECL|macro|BOOT_DESC_VER_1
mdefine_line|#define BOOT_DESC_VER_1&t;&t;1&t;
singleline_comment|// Original definition of BOOT_PARAMS
DECL|macro|BOOT_DESC_VER_2
mdefine_line|#define BOOT_DESC_VER_2&t;&t;2&t;
singleline_comment|// 2nd definition, descriptors not included in boot
singleline_comment|// Capabilities flags
DECL|macro|BOOT_CAP_RESET_CMD
mdefine_line|#define&t;BOOT_CAP_RESET_CMD&t;0x0001&t;
singleline_comment|// If set, boot correctly supports ION_RESET_DEVICE
macro_line|#endif&t;
singleline_comment|// if !defined()
eof
