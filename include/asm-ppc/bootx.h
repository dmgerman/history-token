multiline_comment|/*&n; * This file describes the structure passed from the BootX application&n; * (for MacOS) when it is used to boot Linux.&n; *&n; * Written by Benjamin Herrenschmidt.&n; */
macro_line|#ifndef __ASM_BOOTX_H__
DECL|macro|__ASM_BOOTX_H__
mdefine_line|#define __ASM_BOOTX_H__
macro_line|#ifdef macintosh
macro_line|#include &lt;Types.h&gt;
macro_line|#include &quot;linux_type_defs.h&quot;
macro_line|#endif
macro_line|#ifdef macintosh
multiline_comment|/* All this requires PowerPC alignment */
macro_line|#pragma options align=power
macro_line|#endif
multiline_comment|/* On kernel entry:&n; *&n; * r3 = 0x426f6f58    (&squot;BooX&squot;)&n; * r4 = pointer to boot_infos&n; * r5 = NULL&n; *&n; * Data and instruction translation disabled, interrupts&n; * disabled, kernel loaded at physical 0x00000000 on PCI&n; * machines (will be different on NuBus).&n; */
DECL|macro|BOOT_INFO_VERSION
mdefine_line|#define BOOT_INFO_VERSION               5
DECL|macro|BOOT_INFO_COMPATIBLE_VERSION
mdefine_line|#define BOOT_INFO_COMPATIBLE_VERSION    1
multiline_comment|/* Bit in the architecture flag mask. More to be defined in&n;   future versions. Note that either BOOT_ARCH_PCI or&n;   BOOT_ARCH_NUBUS is set. The other BOOT_ARCH_NUBUS_xxx are&n;   set additionally when BOOT_ARCH_NUBUS is set.&n; */
DECL|macro|BOOT_ARCH_PCI
mdefine_line|#define BOOT_ARCH_PCI                   0x00000001UL
DECL|macro|BOOT_ARCH_NUBUS
mdefine_line|#define BOOT_ARCH_NUBUS                 0x00000002UL
DECL|macro|BOOT_ARCH_NUBUS_PDM
mdefine_line|#define BOOT_ARCH_NUBUS_PDM             0x00000010UL
DECL|macro|BOOT_ARCH_NUBUS_PERFORMA
mdefine_line|#define BOOT_ARCH_NUBUS_PERFORMA        0x00000020UL
DECL|macro|BOOT_ARCH_NUBUS_POWERBOOK
mdefine_line|#define BOOT_ARCH_NUBUS_POWERBOOK       0x00000040UL
multiline_comment|/*  Maximum number of ranges in phys memory map */
DECL|macro|MAX_MEM_MAP_SIZE
mdefine_line|#define MAX_MEM_MAP_SIZE&t;&t;&t;&t;26
multiline_comment|/* This is the format of an element in the physical memory map. Note that&n;   the map is optional and current BootX will only build it for pre-PCI&n;   machines */
DECL|struct|boot_info_map_entry
r_typedef
r_struct
id|boot_info_map_entry
(brace
DECL|member|physAddr
id|__u32
id|physAddr
suffix:semicolon
multiline_comment|/* Physical starting address */
DECL|member|size
id|__u32
id|size
suffix:semicolon
multiline_comment|/* Size in bytes */
DECL|typedef|boot_info_map_entry_t
)brace
id|boot_info_map_entry_t
suffix:semicolon
multiline_comment|/* Here are the boot informations that are passed to the bootstrap&n; * Note that the kernel arguments and the device tree are appended&n; * at the end of this structure. */
DECL|struct|boot_infos
r_typedef
r_struct
id|boot_infos
(brace
multiline_comment|/* Version of this structure */
DECL|member|version
id|__u32
id|version
suffix:semicolon
multiline_comment|/* backward compatible down to version: */
DECL|member|compatible_version
id|__u32
id|compatible_version
suffix:semicolon
multiline_comment|/* NEW (vers. 2) this holds the current _logical_ base addr of&n;       the frame buffer (for use by early boot message) */
DECL|member|logicalDisplayBase
id|__u8
op_star
id|logicalDisplayBase
suffix:semicolon
multiline_comment|/* NEW (vers. 4) Apple&squot;s machine identification */
DECL|member|machineID
id|__u32
id|machineID
suffix:semicolon
multiline_comment|/* NEW (vers. 4) Detected hw architecture */
DECL|member|architecture
id|__u32
id|architecture
suffix:semicolon
multiline_comment|/* The device tree (internal addresses relative to the beginning of the tree,&n;     * device tree offset relative to the beginning of this structure).&n;     * On pre-PCI macintosh (BOOT_ARCH_PCI bit set to 0 in architecture), this&n;     * field is 0.&n;     */
DECL|member|deviceTreeOffset
id|__u32
id|deviceTreeOffset
suffix:semicolon
multiline_comment|/* Device tree offset */
DECL|member|deviceTreeSize
id|__u32
id|deviceTreeSize
suffix:semicolon
multiline_comment|/* Size of the device tree */
multiline_comment|/* Some infos about the current MacOS display */
DECL|member|dispDeviceRect
id|__u32
id|dispDeviceRect
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* left,top,right,bottom */
DECL|member|dispDeviceDepth
id|__u32
id|dispDeviceDepth
suffix:semicolon
multiline_comment|/* (8, 16 or 32) */
DECL|member|dispDeviceBase
id|__u8
op_star
id|dispDeviceBase
suffix:semicolon
multiline_comment|/* base address (physical) */
DECL|member|dispDeviceRowBytes
id|__u32
id|dispDeviceRowBytes
suffix:semicolon
multiline_comment|/* rowbytes (in bytes) */
DECL|member|dispDeviceColorsOffset
id|__u32
id|dispDeviceColorsOffset
suffix:semicolon
multiline_comment|/* Colormap (8 bits only) or 0 (*) */
multiline_comment|/* Optional offset in the registry to the current&n;     * MacOS display. (Can be 0 when not detected) */
DECL|member|dispDeviceRegEntryOffset
id|__u32
id|dispDeviceRegEntryOffset
suffix:semicolon
multiline_comment|/* Optional pointer to boot ramdisk (offset from this structure) */
DECL|member|ramDisk
id|__u32
id|ramDisk
suffix:semicolon
DECL|member|ramDiskSize
id|__u32
id|ramDiskSize
suffix:semicolon
multiline_comment|/* size of ramdisk image */
multiline_comment|/* Kernel command line arguments (offset from this structure) */
DECL|member|kernelParamsOffset
id|__u32
id|kernelParamsOffset
suffix:semicolon
multiline_comment|/* ALL BELOW NEW (vers. 4) */
multiline_comment|/* This defines the physical memory. Valid with BOOT_ARCH_NUBUS flag&n;       (non-PCI) only. On PCI, memory is contiguous and it&squot;s size is in the&n;       device-tree. */
id|boot_info_map_entry_t
DECL|member|physMemoryMap
id|physMemoryMap
(braket
id|MAX_MEM_MAP_SIZE
)braket
suffix:semicolon
multiline_comment|/* Where the phys memory is */
DECL|member|physMemoryMapSize
id|__u32
id|physMemoryMapSize
suffix:semicolon
multiline_comment|/* How many entries in map */
multiline_comment|/* The framebuffer size (optional, currently 0) */
DECL|member|frameBufferSize
id|__u32
id|frameBufferSize
suffix:semicolon
multiline_comment|/* Represents a max size, can be 0. */
multiline_comment|/* NEW (vers. 5) */
multiline_comment|/* Total params size (args + colormap + device tree + ramdisk) */
DECL|member|totalParamsSize
id|__u32
id|totalParamsSize
suffix:semicolon
DECL|typedef|boot_infos_t
)brace
id|boot_infos_t
suffix:semicolon
multiline_comment|/* (*) The format of the colormap is 256 * 3 * 2 bytes. Each color index is represented&n; * by 3 short words containing a 16 bits (unsigned) color component.&n; * Later versions may contain the gamma table for direct-color devices here.&n; */
DECL|macro|BOOTX_COLORTABLE_SIZE
mdefine_line|#define BOOTX_COLORTABLE_SIZE    (256UL*3UL*2UL)
macro_line|#ifdef macintosh
macro_line|#pragma options align=reset
macro_line|#endif
macro_line|#endif
eof
