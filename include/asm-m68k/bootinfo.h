multiline_comment|/*&n;** asm/bootinfo.h -- Definition of the Linux/m68k boot information structure&n;**&n;** Copyright 1992 by Greg Harp&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created 09/29/92 by Greg Harp&n;**&n;** 5/2/94 Roman Hodek:&n;**   Added bi_atari part of the machine dependent union bi_un; for now it&n;**   contains just a model field to distinguish between TT and Falcon.&n;** 26/7/96 Roman Zippel:&n;**   Renamed to setup.h; added some useful macros to allow gcc some&n;**   optimizations if possible.&n;** 5/10/96 Geert Uytterhoeven:&n;**   Redesign of the boot information structure; renamed to bootinfo.h again&n;** 27/11/96 Geert Uytterhoeven:&n;**   Backwards compatibility with bootinfo interface version 1.0&n;*/
macro_line|#ifndef _M68K_BOOTINFO_H
DECL|macro|_M68K_BOOTINFO_H
mdefine_line|#define _M68K_BOOTINFO_H
multiline_comment|/*&n;     *  Bootinfo definitions&n;     *&n;     *  This is an easily parsable and extendable structure containing all&n;     *  information to be passed from the bootstrap to the kernel.&n;     *&n;     *  This way I hope to keep all future changes back/forewards compatible.&n;     *  Thus, keep your fingers crossed...&n;     *&n;     *  This structure is copied right after the kernel bss by the bootstrap&n;     *  routine.&n;     */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|bi_record
r_struct
id|bi_record
(brace
DECL|member|tag
r_int
r_int
id|tag
suffix:semicolon
multiline_comment|/* tag ID */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of record (in bytes) */
DECL|member|data
r_int
r_int
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* data */
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n;     *  Tag Definitions&n;     *&n;     *  Machine independent tags start counting from 0x0000&n;     *  Machine dependent tags start counting from 0x8000&n;     */
DECL|macro|BI_LAST
mdefine_line|#define BI_LAST&t;&t;&t;0x0000&t;/* last record (sentinel) */
DECL|macro|BI_MACHTYPE
mdefine_line|#define BI_MACHTYPE&t;&t;0x0001&t;/* machine type (u_long) */
DECL|macro|BI_CPUTYPE
mdefine_line|#define BI_CPUTYPE&t;&t;0x0002&t;/* cpu type (u_long) */
DECL|macro|BI_FPUTYPE
mdefine_line|#define BI_FPUTYPE&t;&t;0x0003&t;/* fpu type (u_long) */
DECL|macro|BI_MMUTYPE
mdefine_line|#define BI_MMUTYPE&t;&t;0x0004&t;/* mmu type (u_long) */
DECL|macro|BI_MEMCHUNK
mdefine_line|#define BI_MEMCHUNK&t;&t;0x0005&t;/* memory chunk address and size */
multiline_comment|/* (struct mem_info) */
DECL|macro|BI_RAMDISK
mdefine_line|#define BI_RAMDISK&t;&t;0x0006&t;/* ramdisk address and size */
multiline_comment|/* (struct mem_info) */
DECL|macro|BI_COMMAND_LINE
mdefine_line|#define BI_COMMAND_LINE&t;&t;0x0007&t;/* kernel command line parameters */
multiline_comment|/* (string) */
multiline_comment|/*&n;     *  Amiga-specific tags&n;     */
DECL|macro|BI_AMIGA_MODEL
mdefine_line|#define BI_AMIGA_MODEL&t;&t;0x8000&t;/* model (u_long) */
DECL|macro|BI_AMIGA_AUTOCON
mdefine_line|#define BI_AMIGA_AUTOCON&t;0x8001&t;/* AutoConfig device */
multiline_comment|/* (struct ConfigDev) */
DECL|macro|BI_AMIGA_CHIP_SIZE
mdefine_line|#define BI_AMIGA_CHIP_SIZE&t;0x8002&t;/* size of Chip RAM (u_long) */
DECL|macro|BI_AMIGA_VBLANK
mdefine_line|#define BI_AMIGA_VBLANK&t;&t;0x8003&t;/* VBLANK frequency (u_char) */
DECL|macro|BI_AMIGA_PSFREQ
mdefine_line|#define BI_AMIGA_PSFREQ&t;&t;0x8004&t;/* power supply frequency (u_char) */
DECL|macro|BI_AMIGA_ECLOCK
mdefine_line|#define BI_AMIGA_ECLOCK&t;&t;0x8005&t;/* EClock frequency (u_long) */
DECL|macro|BI_AMIGA_CHIPSET
mdefine_line|#define BI_AMIGA_CHIPSET&t;0x8006&t;/* native chipset present (u_long) */
DECL|macro|BI_AMIGA_SERPER
mdefine_line|#define BI_AMIGA_SERPER&t;&t;0x8007&t;/* serial port period (u_short) */
multiline_comment|/*&n;     *  Atari-specific tags&n;     */
DECL|macro|BI_ATARI_MCH_COOKIE
mdefine_line|#define BI_ATARI_MCH_COOKIE&t;0x8000&t;/* _MCH cookie from TOS (u_long) */
DECL|macro|BI_ATARI_MCH_TYPE
mdefine_line|#define BI_ATARI_MCH_TYPE&t;0x8001&t;/* special machine type (u_long) */
multiline_comment|/* (values are ATARI_MACH_* defines */
multiline_comment|/* mch_cookie values (upper word) */
DECL|macro|ATARI_MCH_ST
mdefine_line|#define ATARI_MCH_ST&t;&t;0
DECL|macro|ATARI_MCH_STE
mdefine_line|#define ATARI_MCH_STE&t;&t;1
DECL|macro|ATARI_MCH_TT
mdefine_line|#define ATARI_MCH_TT&t;&t;2
DECL|macro|ATARI_MCH_FALCON
mdefine_line|#define ATARI_MCH_FALCON&t;3
multiline_comment|/* mch_type values */
DECL|macro|ATARI_MACH_NORMAL
mdefine_line|#define ATARI_MACH_NORMAL&t;0&t;/* no special machine type */
DECL|macro|ATARI_MACH_MEDUSA
mdefine_line|#define ATARI_MACH_MEDUSA&t;1&t;/* Medusa 040 */
DECL|macro|ATARI_MACH_HADES
mdefine_line|#define ATARI_MACH_HADES&t;2&t;/* Hades 040 or 060 */
DECL|macro|ATARI_MACH_AB40
mdefine_line|#define ATARI_MACH_AB40&t;&t;3&t;/* Afterburner040 on Falcon */
multiline_comment|/*&n;     *  VME-specific tags&n;     */
DECL|macro|BI_VME_TYPE
mdefine_line|#define BI_VME_TYPE&t;&t;0x8000&t;/* VME sub-architecture (u_long) */
DECL|macro|BI_VME_BRDINFO
mdefine_line|#define BI_VME_BRDINFO&t;&t;0x8001&t;/* VME board information (struct) */
multiline_comment|/* BI_VME_TYPE codes */
DECL|macro|VME_TYPE_TP34V
mdefine_line|#define&t;VME_TYPE_TP34V&t;&t;0x0034&t;/* Tadpole TP34V */
DECL|macro|VME_TYPE_MVME147
mdefine_line|#define VME_TYPE_MVME147&t;0x0147&t;/* Motorola MVME147 */
DECL|macro|VME_TYPE_MVME162
mdefine_line|#define VME_TYPE_MVME162&t;0x0162&t;/* Motorola MVME162 */
DECL|macro|VME_TYPE_MVME166
mdefine_line|#define VME_TYPE_MVME166&t;0x0166&t;/* Motorola MVME166 */
DECL|macro|VME_TYPE_MVME167
mdefine_line|#define VME_TYPE_MVME167&t;0x0167&t;/* Motorola MVME167 */
DECL|macro|VME_TYPE_MVME172
mdefine_line|#define VME_TYPE_MVME172&t;0x0172&t;/* Motorola MVME172 */
DECL|macro|VME_TYPE_MVME177
mdefine_line|#define VME_TYPE_MVME177&t;0x0177&t;/* Motorola MVME177 */
DECL|macro|VME_TYPE_BVME4000
mdefine_line|#define VME_TYPE_BVME4000&t;0x4000&t;/* BVM Ltd. BVME4000 */
DECL|macro|VME_TYPE_BVME6000
mdefine_line|#define VME_TYPE_BVME6000&t;0x6000&t;/* BVM Ltd. BVME6000 */
multiline_comment|/* BI_VME_BRDINFO is a 32 byte struct as returned by the Bug code on&n; * Motorola VME boards.  Contains board number, Bug version, board&n; * configuration options, etc.  See include/asm/mvme16xhw.h for details.&n; */
multiline_comment|/*&n;     *  Macintosh-specific tags (all u_long)&n;     */
DECL|macro|BI_MAC_MODEL
mdefine_line|#define BI_MAC_MODEL&t;&t;0x8000&t;/* Mac Gestalt ID (model type) */
DECL|macro|BI_MAC_VADDR
mdefine_line|#define BI_MAC_VADDR&t;&t;0x8001&t;/* Mac video base address */
DECL|macro|BI_MAC_VDEPTH
mdefine_line|#define BI_MAC_VDEPTH&t;&t;0x8002&t;/* Mac video depth */
DECL|macro|BI_MAC_VROW
mdefine_line|#define BI_MAC_VROW&t;&t;0x8003&t;/* Mac video rowbytes */
DECL|macro|BI_MAC_VDIM
mdefine_line|#define BI_MAC_VDIM&t;&t;0x8004&t;/* Mac video dimensions */
DECL|macro|BI_MAC_VLOGICAL
mdefine_line|#define BI_MAC_VLOGICAL&t;&t;0x8005&t;/* Mac video logical base */
DECL|macro|BI_MAC_SCCBASE
mdefine_line|#define BI_MAC_SCCBASE&t;&t;0x8006&t;/* Mac SCC base address */
DECL|macro|BI_MAC_BTIME
mdefine_line|#define BI_MAC_BTIME&t;&t;0x8007&t;/* Mac boot time */
DECL|macro|BI_MAC_GMTBIAS
mdefine_line|#define BI_MAC_GMTBIAS&t;&t;0x8008&t;/* Mac GMT timezone offset */
DECL|macro|BI_MAC_MEMSIZE
mdefine_line|#define BI_MAC_MEMSIZE&t;&t;0x8009&t;/* Mac RAM size (sanity check) */
DECL|macro|BI_MAC_CPUID
mdefine_line|#define BI_MAC_CPUID&t;&t;0x800a&t;/* Mac CPU type (sanity check) */
DECL|macro|BI_MAC_ROMBASE
mdefine_line|#define BI_MAC_ROMBASE&t;&t;0x800b&t;/* Mac system ROM base address */ 
multiline_comment|/*&n;     *  Macintosh hardware profile data - unused, see macintosh.h for &n;     *  resonable type values &n;     */
DECL|macro|BI_MAC_VIA1BASE
mdefine_line|#define BI_MAC_VIA1BASE&t;&t;0x8010&t;/* Mac VIA1 base address (always present) */
DECL|macro|BI_MAC_VIA2BASE
mdefine_line|#define BI_MAC_VIA2BASE&t;&t;0x8011&t;/* Mac VIA2 base address (type varies) */
DECL|macro|BI_MAC_VIA2TYPE
mdefine_line|#define BI_MAC_VIA2TYPE&t;&t;0x8012&t;/* Mac VIA2 type (VIA, RBV, OSS) */
DECL|macro|BI_MAC_ADBTYPE
mdefine_line|#define BI_MAC_ADBTYPE&t;&t;0x8013&t;/* Mac ADB interface type */
DECL|macro|BI_MAC_ASCBASE
mdefine_line|#define BI_MAC_ASCBASE&t;&t;0x8014&t;/* Mac Apple Sound Chip base address */
DECL|macro|BI_MAC_SCSI5380
mdefine_line|#define BI_MAC_SCSI5380&t;&t;0x8015&t;/* Mac NCR 5380 SCSI (base address, multi) */
DECL|macro|BI_MAC_SCSIDMA
mdefine_line|#define BI_MAC_SCSIDMA&t;&t;0x8016&t;/* Mac SCSI DMA (base address) */
DECL|macro|BI_MAC_SCSI5396
mdefine_line|#define BI_MAC_SCSI5396&t;&t;0x8017&t;/* Mac NCR 53C96 SCSI (base address, multi) */
DECL|macro|BI_MAC_IDETYPE
mdefine_line|#define BI_MAC_IDETYPE&t;&t;0x8018&t;/* Mac IDE interface type */
DECL|macro|BI_MAC_IDEBASE
mdefine_line|#define BI_MAC_IDEBASE&t;&t;0x8019&t;/* Mac IDE interface base address */
DECL|macro|BI_MAC_NUBUS
mdefine_line|#define BI_MAC_NUBUS&t;&t;0x801a&t;/* Mac Nubus type (none, regular, pseudo) */
DECL|macro|BI_MAC_SLOTMASK
mdefine_line|#define BI_MAC_SLOTMASK&t;&t;0x801b&t;/* Mac Nubus slots present */
DECL|macro|BI_MAC_SCCTYPE
mdefine_line|#define BI_MAC_SCCTYPE&t;&t;0x801c&t;/* Mac SCC serial type (normal, IOP) */
DECL|macro|BI_MAC_ETHTYPE
mdefine_line|#define BI_MAC_ETHTYPE&t;&t;0x801d&t;/* Mac builtin ethernet type (Sonic, MACE */
DECL|macro|BI_MAC_ETHBASE
mdefine_line|#define BI_MAC_ETHBASE&t;&t;0x801e&t;/* Mac builtin ethernet base address */
DECL|macro|BI_MAC_PMU
mdefine_line|#define BI_MAC_PMU&t;&t;0x801f&t;/* Mac power managment / poweroff hardware */
DECL|macro|BI_MAC_IOP_SWIM
mdefine_line|#define BI_MAC_IOP_SWIM&t;&t;0x8020&t;/* Mac SWIM floppy IOP */
DECL|macro|BI_MAC_IOP_ADB
mdefine_line|#define BI_MAC_IOP_ADB&t;&t;0x8021&t;/* Mac ADB IOP */
multiline_comment|/*&n;     * Mac: compatibility with old booter data format (temporarily)&n;     * Fields unused with the new bootinfo can be deleted now; instead of&n;     * adding new fields the struct might be splitted into a hardware address&n;     * part and a hardware type part&n;     */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|mac_booter_data
r_struct
id|mac_booter_data
(brace
DECL|member|videoaddr
r_int
r_int
id|videoaddr
suffix:semicolon
DECL|member|videorow
r_int
r_int
id|videorow
suffix:semicolon
DECL|member|videodepth
r_int
r_int
id|videodepth
suffix:semicolon
DECL|member|dimensions
r_int
r_int
id|dimensions
suffix:semicolon
DECL|member|args
r_int
r_int
id|args
suffix:semicolon
DECL|member|boottime
r_int
r_int
id|boottime
suffix:semicolon
DECL|member|gmtbias
r_int
r_int
id|gmtbias
suffix:semicolon
DECL|member|bootver
r_int
r_int
id|bootver
suffix:semicolon
DECL|member|videological
r_int
r_int
id|videological
suffix:semicolon
DECL|member|sccbase
r_int
r_int
id|sccbase
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|memsize
r_int
r_int
id|memsize
suffix:semicolon
DECL|member|serialmf
r_int
r_int
id|serialmf
suffix:semicolon
DECL|member|serialhsk
r_int
r_int
id|serialhsk
suffix:semicolon
DECL|member|serialgpi
r_int
r_int
id|serialgpi
suffix:semicolon
DECL|member|printmf
r_int
r_int
id|printmf
suffix:semicolon
DECL|member|printhsk
r_int
r_int
id|printhsk
suffix:semicolon
DECL|member|printgpi
r_int
r_int
id|printgpi
suffix:semicolon
DECL|member|cpuid
r_int
r_int
id|cpuid
suffix:semicolon
DECL|member|rombase
r_int
r_int
id|rombase
suffix:semicolon
DECL|member|adbdelay
r_int
r_int
id|adbdelay
suffix:semicolon
DECL|member|timedbra
r_int
r_int
id|timedbra
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|mac_booter_data
id|mac_bi_data
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;     *  Apollo-specific tags&n;     */
DECL|macro|BI_APOLLO_MODEL
mdefine_line|#define BI_APOLLO_MODEL         0x8000  /* model (u_long) */
multiline_comment|/*&n;     * Stuff for bootinfo interface versioning&n;     *&n;     * At the start of kernel code, a &squot;struct bootversion&squot; is located.&n;     * bootstrap checks for a matching version of the interface before booting&n;     * a kernel, to avoid user confusion if kernel and bootstrap don&squot;t work&n;     * together :-)&n;     *&n;     * If incompatible changes are made to the bootinfo interface, the major&n;     * number below should be stepped (and the minor reset to 0) for the&n;     * appropriate machine. If a change is backward-compatible, the minor&n;     * should be stepped. &quot;Backwards-compatible&quot; means that booting will work,&n;     * but certain features may not.&n;     */
DECL|macro|BOOTINFOV_MAGIC
mdefine_line|#define BOOTINFOV_MAGIC&t;&t;&t;0x4249561A&t;/* &squot;BIV^Z&squot; */
DECL|macro|MK_BI_VERSION
mdefine_line|#define MK_BI_VERSION(major,minor)&t;(((major)&lt;&lt;16)+(minor))
DECL|macro|BI_VERSION_MAJOR
mdefine_line|#define BI_VERSION_MAJOR(v)&t;&t;(((v) &gt;&gt; 16) &amp; 0xffff)
DECL|macro|BI_VERSION_MINOR
mdefine_line|#define BI_VERSION_MINOR(v)&t;&t;((v) &amp; 0xffff)
macro_line|#ifndef __ASSEMBLY__
DECL|struct|bootversion
r_struct
id|bootversion
(brace
DECL|member|branch
r_int
r_int
id|branch
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
r_struct
(brace
DECL|member|machtype
r_int
r_int
id|machtype
suffix:semicolon
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|machversions
)brace
id|machversions
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|AMIGA_BOOTI_VERSION
mdefine_line|#define AMIGA_BOOTI_VERSION    MK_BI_VERSION( 2, 0 )
DECL|macro|ATARI_BOOTI_VERSION
mdefine_line|#define ATARI_BOOTI_VERSION    MK_BI_VERSION( 2, 1 )
DECL|macro|MAC_BOOTI_VERSION
mdefine_line|#define MAC_BOOTI_VERSION      MK_BI_VERSION( 2, 0 )
DECL|macro|MVME147_BOOTI_VERSION
mdefine_line|#define MVME147_BOOTI_VERSION  MK_BI_VERSION( 2, 0 )
DECL|macro|MVME16x_BOOTI_VERSION
mdefine_line|#define MVME16x_BOOTI_VERSION  MK_BI_VERSION( 2, 0 )
DECL|macro|BVME6000_BOOTI_VERSION
mdefine_line|#define BVME6000_BOOTI_VERSION MK_BI_VERSION( 2, 0 )
DECL|macro|Q40_BOOTI_VERSION
mdefine_line|#define Q40_BOOTI_VERSION      MK_BI_VERSION( 2, 0 )
macro_line|#ifdef BOOTINFO_COMPAT_1_0
multiline_comment|/*&n;     *  Backwards compatibility with bootinfo interface version 1.0&n;     */
DECL|macro|COMPAT_AMIGA_BOOTI_VERSION
mdefine_line|#define COMPAT_AMIGA_BOOTI_VERSION    MK_BI_VERSION( 1, 0 )
DECL|macro|COMPAT_ATARI_BOOTI_VERSION
mdefine_line|#define COMPAT_ATARI_BOOTI_VERSION    MK_BI_VERSION( 1, 0 )
DECL|macro|COMPAT_MAC_BOOTI_VERSION
mdefine_line|#define COMPAT_MAC_BOOTI_VERSION      MK_BI_VERSION( 1, 0 )
macro_line|#include &lt;linux/zorro.h&gt;
DECL|macro|COMPAT_NUM_AUTO
mdefine_line|#define COMPAT_NUM_AUTO    16
DECL|struct|compat_bi_Amiga
r_struct
id|compat_bi_Amiga
(brace
DECL|member|model
r_int
id|model
suffix:semicolon
DECL|member|num_autocon
r_int
id|num_autocon
suffix:semicolon
DECL|member|autocon
r_struct
id|ConfigDev
id|autocon
(braket
id|COMPAT_NUM_AUTO
)braket
suffix:semicolon
DECL|member|chip_size
r_int
r_int
id|chip_size
suffix:semicolon
DECL|member|vblank
r_int
r_char
id|vblank
suffix:semicolon
DECL|member|psfreq
r_int
r_char
id|psfreq
suffix:semicolon
DECL|member|eclock
r_int
r_int
id|eclock
suffix:semicolon
DECL|member|chipset
r_int
r_int
id|chipset
suffix:semicolon
DECL|member|hw_present
r_int
r_int
id|hw_present
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_bi_Atari
r_struct
id|compat_bi_Atari
(brace
DECL|member|hw_present
r_int
r_int
id|hw_present
suffix:semicolon
DECL|member|mch_cookie
r_int
r_int
id|mch_cookie
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef __ASSEMBLY__
DECL|struct|compat_bi_Macintosh
r_struct
id|compat_bi_Macintosh
(brace
DECL|member|videoaddr
r_int
r_int
id|videoaddr
suffix:semicolon
DECL|member|videorow
r_int
r_int
id|videorow
suffix:semicolon
DECL|member|videodepth
r_int
r_int
id|videodepth
suffix:semicolon
DECL|member|dimensions
r_int
r_int
id|dimensions
suffix:semicolon
DECL|member|args
r_int
r_int
id|args
suffix:semicolon
DECL|member|boottime
r_int
r_int
id|boottime
suffix:semicolon
DECL|member|gmtbias
r_int
r_int
id|gmtbias
suffix:semicolon
DECL|member|bootver
r_int
r_int
id|bootver
suffix:semicolon
DECL|member|videological
r_int
r_int
id|videological
suffix:semicolon
DECL|member|sccbase
r_int
r_int
id|sccbase
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|memsize
r_int
r_int
id|memsize
suffix:semicolon
DECL|member|serialmf
r_int
r_int
id|serialmf
suffix:semicolon
DECL|member|serialhsk
r_int
r_int
id|serialhsk
suffix:semicolon
DECL|member|serialgpi
r_int
r_int
id|serialgpi
suffix:semicolon
DECL|member|printmf
r_int
r_int
id|printmf
suffix:semicolon
DECL|member|printhsk
r_int
r_int
id|printhsk
suffix:semicolon
DECL|member|printgpi
r_int
r_int
id|printgpi
suffix:semicolon
DECL|member|cpuid
r_int
r_int
id|cpuid
suffix:semicolon
DECL|member|rombase
r_int
r_int
id|rombase
suffix:semicolon
DECL|member|adbdelay
r_int
r_int
id|adbdelay
suffix:semicolon
DECL|member|timedbra
r_int
r_int
id|timedbra
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|compat_mem_info
r_struct
id|compat_mem_info
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|COMPAT_NUM_MEMINFO
mdefine_line|#define COMPAT_NUM_MEMINFO  4
DECL|macro|COMPAT_CPUB_68020
mdefine_line|#define COMPAT_CPUB_68020 0
DECL|macro|COMPAT_CPUB_68030
mdefine_line|#define COMPAT_CPUB_68030 1
DECL|macro|COMPAT_CPUB_68040
mdefine_line|#define COMPAT_CPUB_68040 2
DECL|macro|COMPAT_CPUB_68060
mdefine_line|#define COMPAT_CPUB_68060 3
DECL|macro|COMPAT_FPUB_68881
mdefine_line|#define COMPAT_FPUB_68881 5
DECL|macro|COMPAT_FPUB_68882
mdefine_line|#define COMPAT_FPUB_68882 6
DECL|macro|COMPAT_FPUB_68040
mdefine_line|#define COMPAT_FPUB_68040 7
DECL|macro|COMPAT_FPUB_68060
mdefine_line|#define COMPAT_FPUB_68060 8
DECL|macro|COMPAT_CPU_68020
mdefine_line|#define COMPAT_CPU_68020    (1&lt;&lt;COMPAT_CPUB_68020)
DECL|macro|COMPAT_CPU_68030
mdefine_line|#define COMPAT_CPU_68030    (1&lt;&lt;COMPAT_CPUB_68030)
DECL|macro|COMPAT_CPU_68040
mdefine_line|#define COMPAT_CPU_68040    (1&lt;&lt;COMPAT_CPUB_68040)
DECL|macro|COMPAT_CPU_68060
mdefine_line|#define COMPAT_CPU_68060    (1&lt;&lt;COMPAT_CPUB_68060)
DECL|macro|COMPAT_CPU_MASK
mdefine_line|#define COMPAT_CPU_MASK     (31)
DECL|macro|COMPAT_FPU_68881
mdefine_line|#define COMPAT_FPU_68881    (1&lt;&lt;COMPAT_FPUB_68881)
DECL|macro|COMPAT_FPU_68882
mdefine_line|#define COMPAT_FPU_68882    (1&lt;&lt;COMPAT_FPUB_68882)
DECL|macro|COMPAT_FPU_68040
mdefine_line|#define COMPAT_FPU_68040    (1&lt;&lt;COMPAT_FPUB_68040)
DECL|macro|COMPAT_FPU_68060
mdefine_line|#define COMPAT_FPU_68060    (1&lt;&lt;COMPAT_FPUB_68060)
DECL|macro|COMPAT_FPU_MASK
mdefine_line|#define COMPAT_FPU_MASK     (0xfe0)
DECL|macro|COMPAT_CL_SIZE
mdefine_line|#define COMPAT_CL_SIZE      (256)
DECL|struct|compat_bootinfo
r_struct
id|compat_bootinfo
(brace
DECL|member|machtype
r_int
r_int
id|machtype
suffix:semicolon
DECL|member|cputype
r_int
r_int
id|cputype
suffix:semicolon
DECL|member|memory
r_struct
id|compat_mem_info
id|memory
(braket
id|COMPAT_NUM_MEMINFO
)braket
suffix:semicolon
DECL|member|num_memory
r_int
id|num_memory
suffix:semicolon
DECL|member|ramdisk_size
r_int
r_int
id|ramdisk_size
suffix:semicolon
DECL|member|ramdisk_addr
r_int
r_int
id|ramdisk_addr
suffix:semicolon
DECL|member|command_line
r_char
id|command_line
(braket
id|COMPAT_CL_SIZE
)braket
suffix:semicolon
r_union
(brace
DECL|member|bi_ami
r_struct
id|compat_bi_Amiga
id|bi_ami
suffix:semicolon
DECL|member|bi_ata
r_struct
id|compat_bi_Atari
id|bi_ata
suffix:semicolon
DECL|member|bi_mac
r_struct
id|compat_bi_Macintosh
id|bi_mac
suffix:semicolon
DECL|member|bi_un
)brace
id|bi_un
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bi_amiga
mdefine_line|#define bi_amiga&t;bi_un.bi_ami
DECL|macro|bi_atari
mdefine_line|#define bi_atari&t;bi_un.bi_ata
DECL|macro|bi_mac
mdefine_line|#define bi_mac&t;&t;bi_un.bi_mac
macro_line|#endif /* BOOTINFO_COMPAT_1_0 */
macro_line|#endif /* _M68K_BOOTINFO_H */
eof
