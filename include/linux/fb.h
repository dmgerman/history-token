macro_line|#ifndef _LINUX_FB_H
DECL|macro|_LINUX_FB_H
mdefine_line|#define _LINUX_FB_H
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Definitions of frame buffers&t;&t;&t;&t;&t;&t;*/
DECL|macro|FB_MAJOR
mdefine_line|#define FB_MAJOR&t;&t;29
DECL|macro|FB_MAX
mdefine_line|#define FB_MAX&t;&t;&t;32&t;/* sufficient for now */
multiline_comment|/* ioctls&n;   0x46 is &squot;F&squot;&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|FBIOGET_VSCREENINFO
mdefine_line|#define FBIOGET_VSCREENINFO&t;0x4600
DECL|macro|FBIOPUT_VSCREENINFO
mdefine_line|#define FBIOPUT_VSCREENINFO&t;0x4601
DECL|macro|FBIOGET_FSCREENINFO
mdefine_line|#define FBIOGET_FSCREENINFO&t;0x4602
DECL|macro|FBIOGETCMAP
mdefine_line|#define FBIOGETCMAP&t;&t;0x4604
DECL|macro|FBIOPUTCMAP
mdefine_line|#define FBIOPUTCMAP&t;&t;0x4605
DECL|macro|FBIOPAN_DISPLAY
mdefine_line|#define FBIOPAN_DISPLAY&t;&t;0x4606
macro_line|#ifdef __KERNEL__
DECL|macro|FBIO_CURSOR
mdefine_line|#define FBIO_CURSOR            _IOWR(&squot;F&squot;, 0x08, struct fb_cursor_user)
macro_line|#else
DECL|macro|FBIO_CURSOR
mdefine_line|#define FBIO_CURSOR            _IOWR(&squot;F&squot;, 0x08, struct fb_cursor)
macro_line|#endif
multiline_comment|/* 0x4607-0x460B are defined below */
multiline_comment|/* #define FBIOGET_MONITORSPEC&t;0x460C */
multiline_comment|/* #define FBIOPUT_MONITORSPEC&t;0x460D */
multiline_comment|/* #define FBIOSWITCH_MONIBIT&t;0x460E */
DECL|macro|FBIOGET_CON2FBMAP
mdefine_line|#define FBIOGET_CON2FBMAP&t;0x460F
DECL|macro|FBIOPUT_CON2FBMAP
mdefine_line|#define FBIOPUT_CON2FBMAP&t;0x4610
DECL|macro|FBIOBLANK
mdefine_line|#define FBIOBLANK&t;&t;0x4611&t;&t;/* arg: 0 or vesa level + 1 */
DECL|macro|FBIOGET_VBLANK
mdefine_line|#define FBIOGET_VBLANK&t;&t;_IOR(&squot;F&squot;, 0x12, struct fb_vblank)
DECL|macro|FBIO_ALLOC
mdefine_line|#define FBIO_ALLOC              0x4613
DECL|macro|FBIO_FREE
mdefine_line|#define FBIO_FREE               0x4614
DECL|macro|FBIOGET_GLYPH
mdefine_line|#define FBIOGET_GLYPH           0x4615
DECL|macro|FBIOGET_HWCINFO
mdefine_line|#define FBIOGET_HWCINFO         0x4616
DECL|macro|FBIOPUT_MODEINFO
mdefine_line|#define FBIOPUT_MODEINFO        0x4617
DECL|macro|FBIOGET_DISPINFO
mdefine_line|#define FBIOGET_DISPINFO        0x4618
DECL|macro|FB_TYPE_PACKED_PIXELS
mdefine_line|#define FB_TYPE_PACKED_PIXELS&t;&t;0&t;/* Packed Pixels&t;*/
DECL|macro|FB_TYPE_PLANES
mdefine_line|#define FB_TYPE_PLANES&t;&t;&t;1&t;/* Non interleaved planes */
DECL|macro|FB_TYPE_INTERLEAVED_PLANES
mdefine_line|#define FB_TYPE_INTERLEAVED_PLANES&t;2&t;/* Interleaved planes&t;*/
DECL|macro|FB_TYPE_TEXT
mdefine_line|#define FB_TYPE_TEXT&t;&t;&t;3&t;/* Text/attributes&t;*/
DECL|macro|FB_TYPE_VGA_PLANES
mdefine_line|#define FB_TYPE_VGA_PLANES&t;&t;4&t;/* EGA/VGA planes&t;*/
DECL|macro|FB_AUX_TEXT_MDA
mdefine_line|#define FB_AUX_TEXT_MDA&t;&t;0&t;/* Monochrome text */
DECL|macro|FB_AUX_TEXT_CGA
mdefine_line|#define FB_AUX_TEXT_CGA&t;&t;1&t;/* CGA/EGA/VGA Color text */
DECL|macro|FB_AUX_TEXT_S3_MMIO
mdefine_line|#define FB_AUX_TEXT_S3_MMIO&t;2&t;/* S3 MMIO fasttext */
DECL|macro|FB_AUX_TEXT_MGA_STEP16
mdefine_line|#define FB_AUX_TEXT_MGA_STEP16&t;3&t;/* MGA Millenium I: text, attr, 14 reserved bytes */
DECL|macro|FB_AUX_TEXT_MGA_STEP8
mdefine_line|#define FB_AUX_TEXT_MGA_STEP8&t;4&t;/* other MGAs:      text, attr,  6 reserved bytes */
DECL|macro|FB_AUX_VGA_PLANES_VGA4
mdefine_line|#define FB_AUX_VGA_PLANES_VGA4&t;&t;0&t;/* 16 color planes (EGA/VGA) */
DECL|macro|FB_AUX_VGA_PLANES_CFB4
mdefine_line|#define FB_AUX_VGA_PLANES_CFB4&t;&t;1&t;/* CFB4 in planes (VGA) */
DECL|macro|FB_AUX_VGA_PLANES_CFB8
mdefine_line|#define FB_AUX_VGA_PLANES_CFB8&t;&t;2&t;/* CFB8 in planes (VGA) */
DECL|macro|FB_VISUAL_MONO01
mdefine_line|#define FB_VISUAL_MONO01&t;&t;0&t;/* Monochr. 1=Black 0=White */
DECL|macro|FB_VISUAL_MONO10
mdefine_line|#define FB_VISUAL_MONO10&t;&t;1&t;/* Monochr. 1=White 0=Black */
DECL|macro|FB_VISUAL_TRUECOLOR
mdefine_line|#define FB_VISUAL_TRUECOLOR&t;&t;2&t;/* True color&t;*/
DECL|macro|FB_VISUAL_PSEUDOCOLOR
mdefine_line|#define FB_VISUAL_PSEUDOCOLOR&t;&t;3&t;/* Pseudo color (like atari) */
DECL|macro|FB_VISUAL_DIRECTCOLOR
mdefine_line|#define FB_VISUAL_DIRECTCOLOR&t;&t;4&t;/* Direct color */
DECL|macro|FB_VISUAL_STATIC_PSEUDOCOLOR
mdefine_line|#define FB_VISUAL_STATIC_PSEUDOCOLOR&t;5&t;/* Pseudo color readonly */
DECL|macro|FB_ACCEL_NONE
mdefine_line|#define FB_ACCEL_NONE&t;&t;0&t;/* no hardware accelerator&t;*/
DECL|macro|FB_ACCEL_ATARIBLITT
mdefine_line|#define FB_ACCEL_ATARIBLITT&t;1&t;/* Atari Blitter&t;&t;*/
DECL|macro|FB_ACCEL_AMIGABLITT
mdefine_line|#define FB_ACCEL_AMIGABLITT&t;2&t;/* Amiga Blitter                */
DECL|macro|FB_ACCEL_S3_TRIO64
mdefine_line|#define FB_ACCEL_S3_TRIO64&t;3&t;/* Cybervision64 (S3 Trio64)    */
DECL|macro|FB_ACCEL_NCR_77C32BLT
mdefine_line|#define FB_ACCEL_NCR_77C32BLT&t;4&t;/* RetinaZ3 (NCR 77C32BLT)      */
DECL|macro|FB_ACCEL_S3_VIRGE
mdefine_line|#define FB_ACCEL_S3_VIRGE&t;5&t;/* Cybervision64/3D (S3 ViRGE)&t;*/
DECL|macro|FB_ACCEL_ATI_MACH64GX
mdefine_line|#define FB_ACCEL_ATI_MACH64GX&t;6&t;/* ATI Mach 64GX family&t;&t;*/
DECL|macro|FB_ACCEL_DEC_TGA
mdefine_line|#define FB_ACCEL_DEC_TGA&t;7&t;/* DEC 21030 TGA&t;&t;*/
DECL|macro|FB_ACCEL_ATI_MACH64CT
mdefine_line|#define FB_ACCEL_ATI_MACH64CT&t;8&t;/* ATI Mach 64CT family&t;&t;*/
DECL|macro|FB_ACCEL_ATI_MACH64VT
mdefine_line|#define FB_ACCEL_ATI_MACH64VT&t;9&t;/* ATI Mach 64CT family VT class */
DECL|macro|FB_ACCEL_ATI_MACH64GT
mdefine_line|#define FB_ACCEL_ATI_MACH64GT&t;10&t;/* ATI Mach 64CT family GT class */
DECL|macro|FB_ACCEL_SUN_CREATOR
mdefine_line|#define FB_ACCEL_SUN_CREATOR&t;11&t;/* Sun Creator/Creator3D&t;*/
DECL|macro|FB_ACCEL_SUN_CGSIX
mdefine_line|#define FB_ACCEL_SUN_CGSIX&t;12&t;/* Sun cg6&t;&t;&t;*/
DECL|macro|FB_ACCEL_SUN_LEO
mdefine_line|#define FB_ACCEL_SUN_LEO&t;13&t;/* Sun leo/zx&t;&t;&t;*/
DECL|macro|FB_ACCEL_IMS_TWINTURBO
mdefine_line|#define FB_ACCEL_IMS_TWINTURBO&t;14&t;/* IMS Twin Turbo&t;&t;*/
DECL|macro|FB_ACCEL_3DLABS_PERMEDIA2
mdefine_line|#define FB_ACCEL_3DLABS_PERMEDIA2 15&t;/* 3Dlabs Permedia 2&t;&t;*/
DECL|macro|FB_ACCEL_MATROX_MGA2064W
mdefine_line|#define FB_ACCEL_MATROX_MGA2064W 16&t;/* Matrox MGA2064W (Millenium)&t;*/
DECL|macro|FB_ACCEL_MATROX_MGA1064SG
mdefine_line|#define FB_ACCEL_MATROX_MGA1064SG 17&t;/* Matrox MGA1064SG (Mystique)&t;*/
DECL|macro|FB_ACCEL_MATROX_MGA2164W
mdefine_line|#define FB_ACCEL_MATROX_MGA2164W 18&t;/* Matrox MGA2164W (Millenium II) */
DECL|macro|FB_ACCEL_MATROX_MGA2164W_AGP
mdefine_line|#define FB_ACCEL_MATROX_MGA2164W_AGP 19&t;/* Matrox MGA2164W (Millenium II) */
DECL|macro|FB_ACCEL_MATROX_MGAG100
mdefine_line|#define FB_ACCEL_MATROX_MGAG100&t;20&t;/* Matrox G100 (Productiva G100) */
DECL|macro|FB_ACCEL_MATROX_MGAG200
mdefine_line|#define FB_ACCEL_MATROX_MGAG200&t;21&t;/* Matrox G200 (Myst, Mill, ...) */
DECL|macro|FB_ACCEL_SUN_CG14
mdefine_line|#define FB_ACCEL_SUN_CG14&t;22&t;/* Sun cgfourteen&t;&t; */
DECL|macro|FB_ACCEL_SUN_BWTWO
mdefine_line|#define FB_ACCEL_SUN_BWTWO&t;23&t;/* Sun bwtwo&t;&t;&t;*/
DECL|macro|FB_ACCEL_SUN_CGTHREE
mdefine_line|#define FB_ACCEL_SUN_CGTHREE&t;24&t;/* Sun cgthree&t;&t;&t;*/
DECL|macro|FB_ACCEL_SUN_TCX
mdefine_line|#define FB_ACCEL_SUN_TCX&t;25&t;/* Sun tcx&t;&t;&t;*/
DECL|macro|FB_ACCEL_MATROX_MGAG400
mdefine_line|#define FB_ACCEL_MATROX_MGAG400&t;26&t;/* Matrox G400&t;&t;&t;*/
DECL|macro|FB_ACCEL_NV3
mdefine_line|#define FB_ACCEL_NV3&t;&t;27&t;/* nVidia RIVA 128              */
DECL|macro|FB_ACCEL_NV4
mdefine_line|#define FB_ACCEL_NV4&t;&t;28&t;/* nVidia RIVA TNT&t;&t;*/
DECL|macro|FB_ACCEL_NV5
mdefine_line|#define FB_ACCEL_NV5&t;&t;29&t;/* nVidia RIVA TNT2&t;&t;*/
DECL|macro|FB_ACCEL_CT_6555x
mdefine_line|#define FB_ACCEL_CT_6555x&t;30&t;/* C&amp;T 6555x&t;&t;&t;*/
DECL|macro|FB_ACCEL_3DFX_BANSHEE
mdefine_line|#define FB_ACCEL_3DFX_BANSHEE&t;31&t;/* 3Dfx Banshee&t;&t;&t;*/
DECL|macro|FB_ACCEL_ATI_RAGE128
mdefine_line|#define FB_ACCEL_ATI_RAGE128&t;32&t;/* ATI Rage128 family&t;&t;*/
DECL|macro|FB_ACCEL_IGS_CYBER2000
mdefine_line|#define FB_ACCEL_IGS_CYBER2000&t;33&t;/* CyberPro 2000&t;&t;*/
DECL|macro|FB_ACCEL_IGS_CYBER2010
mdefine_line|#define FB_ACCEL_IGS_CYBER2010&t;34&t;/* CyberPro 2010&t;&t;*/
DECL|macro|FB_ACCEL_IGS_CYBER5000
mdefine_line|#define FB_ACCEL_IGS_CYBER5000&t;35&t;/* CyberPro 5000&t;&t;*/
DECL|macro|FB_ACCEL_SIS_GLAMOUR
mdefine_line|#define FB_ACCEL_SIS_GLAMOUR    36&t;/* SiS 300/630/540              */
DECL|macro|FB_ACCEL_3DLABS_PERMEDIA3
mdefine_line|#define FB_ACCEL_3DLABS_PERMEDIA3 37&t;/* 3Dlabs Permedia 3&t;&t;*/
DECL|macro|FB_ACCEL_ATI_RADEON
mdefine_line|#define FB_ACCEL_ATI_RADEON&t;38&t;/* ATI Radeon family&t;&t;*/
DECL|macro|FB_ACCEL_I810
mdefine_line|#define FB_ACCEL_I810           39      /* Intel 810/815                */
DECL|macro|FB_ACCEL_SIS_GLAMOUR_2
mdefine_line|#define FB_ACCEL_SIS_GLAMOUR_2  40&t;/* SiS 315, 650, 740&t;&t;*/
DECL|macro|FB_ACCEL_SIS_XABRE
mdefine_line|#define FB_ACCEL_SIS_XABRE      41&t;/* SiS 330 (&quot;Xabre&quot;)&t;&t;*/
DECL|macro|FB_ACCEL_I830
mdefine_line|#define FB_ACCEL_I830           42      /* Intel 830M/845G/85x/865G     */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2070
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2070 90&t;/* NeoMagic NM2070              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2090
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2090 91&t;/* NeoMagic NM2090              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2093
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2093 92&t;/* NeoMagic NM2093              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2097
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2097 93&t;/* NeoMagic NM2097              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2160
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2160 94&t;/* NeoMagic NM2160              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2200
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2200 95&t;/* NeoMagic NM2200              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2230
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2230 96&t;/* NeoMagic NM2230              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2360
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2360 97&t;/* NeoMagic NM2360              */
DECL|macro|FB_ACCEL_NEOMAGIC_NM2380
mdefine_line|#define FB_ACCEL_NEOMAGIC_NM2380 98&t;/* NeoMagic NM2380              */
DECL|macro|FB_ACCEL_SAVAGE4
mdefine_line|#define FB_ACCEL_SAVAGE4        0x80&t;/* S3 Savage4                   */
DECL|macro|FB_ACCEL_SAVAGE3D
mdefine_line|#define FB_ACCEL_SAVAGE3D       0x81&t;/* S3 Savage3D                  */
DECL|macro|FB_ACCEL_SAVAGE3D_MV
mdefine_line|#define FB_ACCEL_SAVAGE3D_MV    0x82&t;/* S3 Savage3D-MV               */
DECL|macro|FB_ACCEL_SAVAGE2000
mdefine_line|#define FB_ACCEL_SAVAGE2000     0x83&t;/* S3 Savage2000                */
DECL|macro|FB_ACCEL_SAVAGE_MX_MV
mdefine_line|#define FB_ACCEL_SAVAGE_MX_MV   0x84&t;/* S3 Savage/MX-MV              */
DECL|macro|FB_ACCEL_SAVAGE_MX
mdefine_line|#define FB_ACCEL_SAVAGE_MX      0x85&t;/* S3 Savage/MX                 */
DECL|macro|FB_ACCEL_SAVAGE_IX_MV
mdefine_line|#define FB_ACCEL_SAVAGE_IX_MV   0x86&t;/* S3 Savage/IX-MV              */
DECL|macro|FB_ACCEL_SAVAGE_IX
mdefine_line|#define FB_ACCEL_SAVAGE_IX      0x87&t;/* S3 Savage/IX                 */
DECL|macro|FB_ACCEL_PROSAVAGE_PM
mdefine_line|#define FB_ACCEL_PROSAVAGE_PM   0x88&t;/* S3 ProSavage PM133           */
DECL|macro|FB_ACCEL_PROSAVAGE_KM
mdefine_line|#define FB_ACCEL_PROSAVAGE_KM   0x89&t;/* S3 ProSavage KM133           */
DECL|macro|FB_ACCEL_S3TWISTER_P
mdefine_line|#define FB_ACCEL_S3TWISTER_P    0x8a&t;/* S3 Twister                   */
DECL|macro|FB_ACCEL_S3TWISTER_K
mdefine_line|#define FB_ACCEL_S3TWISTER_K    0x8b&t;/* S3 TwisterK                  */
DECL|macro|FB_ACCEL_SUPERSAVAGE
mdefine_line|#define FB_ACCEL_SUPERSAVAGE    0x8c    /* S3 Supersavage               */
DECL|macro|FB_ACCEL_PROSAVAGE_DDR
mdefine_line|#define FB_ACCEL_PROSAVAGE_DDR  0x8d&t;/* S3 ProSavage DDR             */
DECL|macro|FB_ACCEL_PROSAVAGE_DDRK
mdefine_line|#define FB_ACCEL_PROSAVAGE_DDRK 0x8e&t;/* S3 ProSavage DDR-K           */
DECL|struct|fb_fix_screeninfo
r_struct
id|fb_fix_screeninfo
(brace
DECL|member|id
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* identification string eg &quot;TT Builtin&quot; */
DECL|member|smem_start
r_int
r_int
id|smem_start
suffix:semicolon
multiline_comment|/* Start of frame buffer mem */
multiline_comment|/* (physical address) */
DECL|member|smem_len
id|__u32
id|smem_len
suffix:semicolon
multiline_comment|/* Length of frame buffer mem */
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* see FB_TYPE_*&t;&t;*/
DECL|member|type_aux
id|__u32
id|type_aux
suffix:semicolon
multiline_comment|/* Interleave for interleaved Planes */
DECL|member|visual
id|__u32
id|visual
suffix:semicolon
multiline_comment|/* see FB_VISUAL_*&t;&t;*/
DECL|member|xpanstep
id|__u16
id|xpanstep
suffix:semicolon
multiline_comment|/* zero if no hardware panning  */
DECL|member|ypanstep
id|__u16
id|ypanstep
suffix:semicolon
multiline_comment|/* zero if no hardware panning  */
DECL|member|ywrapstep
id|__u16
id|ywrapstep
suffix:semicolon
multiline_comment|/* zero if no hardware ywrap    */
DECL|member|line_length
id|__u32
id|line_length
suffix:semicolon
multiline_comment|/* length of a line in bytes    */
DECL|member|mmio_start
r_int
r_int
id|mmio_start
suffix:semicolon
multiline_comment|/* Start of Memory Mapped I/O   */
multiline_comment|/* (physical address) */
DECL|member|mmio_len
id|__u32
id|mmio_len
suffix:semicolon
multiline_comment|/* Length of Memory Mapped I/O  */
DECL|member|accel
id|__u32
id|accel
suffix:semicolon
multiline_comment|/* Indicate to driver which&t;*/
multiline_comment|/*  specific chip/card we have&t;*/
DECL|member|reserved
id|__u16
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved for future compatibility */
)brace
suffix:semicolon
multiline_comment|/* Interpretation of offset for color fields: All offsets are from the right,&n; * inside a &quot;pixel&quot; value, which is exactly &squot;bits_per_pixel&squot; wide (means: you&n; * can use the offset as right argument to &lt;&lt;). A pixel afterwards is a bit&n; * stream and is written to video memory as that unmodified. This implies&n; * big-endian byte order if bits_per_pixel is greater than 8.&n; */
DECL|struct|fb_bitfield
r_struct
id|fb_bitfield
(brace
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* beginning of bitfield&t;*/
DECL|member|length
id|__u32
id|length
suffix:semicolon
multiline_comment|/* length of bitfield&t;&t;*/
DECL|member|msb_right
id|__u32
id|msb_right
suffix:semicolon
multiline_comment|/* != 0 : Most significant bit is */
multiline_comment|/* right */
)brace
suffix:semicolon
DECL|macro|FB_NONSTD_HAM
mdefine_line|#define FB_NONSTD_HAM&t;&t;1&t;/* Hold-And-Modify (HAM)        */
DECL|macro|FB_ACTIVATE_NOW
mdefine_line|#define FB_ACTIVATE_NOW&t;&t;0&t;/* set values immediately (or vbl)*/
DECL|macro|FB_ACTIVATE_NXTOPEN
mdefine_line|#define FB_ACTIVATE_NXTOPEN&t;1&t;/* activate on next open&t;*/
DECL|macro|FB_ACTIVATE_TEST
mdefine_line|#define FB_ACTIVATE_TEST&t;2&t;/* don&squot;t set, round up impossible */
DECL|macro|FB_ACTIVATE_MASK
mdefine_line|#define FB_ACTIVATE_MASK       15
multiline_comment|/* values&t;&t;&t;*/
DECL|macro|FB_ACTIVATE_VBL
mdefine_line|#define FB_ACTIVATE_VBL&t;       16&t;/* activate values on next vbl  */
DECL|macro|FB_CHANGE_CMAP_VBL
mdefine_line|#define FB_CHANGE_CMAP_VBL     32&t;/* change colormap on vbl&t;*/
DECL|macro|FB_ACTIVATE_ALL
mdefine_line|#define FB_ACTIVATE_ALL&t;       64&t;/* change all VCs on this fb&t;*/
DECL|macro|FB_ACTIVATE_FORCE
mdefine_line|#define FB_ACTIVATE_FORCE     128&t;/* force apply even when no change*/
DECL|macro|FB_ACTIVATE_INV_MODE
mdefine_line|#define FB_ACTIVATE_INV_MODE  256       /* invalidate videomode */
DECL|macro|FB_ACCELF_TEXT
mdefine_line|#define FB_ACCELF_TEXT&t;&t;1&t;/* (OBSOLETE) see fb_info.flags and vc_mode */
DECL|macro|FB_SYNC_HOR_HIGH_ACT
mdefine_line|#define FB_SYNC_HOR_HIGH_ACT&t;1&t;/* horizontal sync high active&t;*/
DECL|macro|FB_SYNC_VERT_HIGH_ACT
mdefine_line|#define FB_SYNC_VERT_HIGH_ACT&t;2&t;/* vertical sync high active&t;*/
DECL|macro|FB_SYNC_EXT
mdefine_line|#define FB_SYNC_EXT&t;&t;4&t;/* external sync&t;&t;*/
DECL|macro|FB_SYNC_COMP_HIGH_ACT
mdefine_line|#define FB_SYNC_COMP_HIGH_ACT&t;8&t;/* composite sync high active   */
DECL|macro|FB_SYNC_BROADCAST
mdefine_line|#define FB_SYNC_BROADCAST&t;16&t;/* broadcast video timings      */
multiline_comment|/* vtotal = 144d/288n/576i =&gt; PAL  */
multiline_comment|/* vtotal = 121d/242n/484i =&gt; NTSC */
DECL|macro|FB_SYNC_ON_GREEN
mdefine_line|#define FB_SYNC_ON_GREEN&t;32&t;/* sync on green */
DECL|macro|FB_VMODE_NONINTERLACED
mdefine_line|#define FB_VMODE_NONINTERLACED  0&t;/* non interlaced */
DECL|macro|FB_VMODE_INTERLACED
mdefine_line|#define FB_VMODE_INTERLACED&t;1&t;/* interlaced&t;*/
DECL|macro|FB_VMODE_DOUBLE
mdefine_line|#define FB_VMODE_DOUBLE&t;&t;2&t;/* double scan */
DECL|macro|FB_VMODE_MASK
mdefine_line|#define FB_VMODE_MASK&t;&t;255
DECL|macro|FB_VMODE_YWRAP
mdefine_line|#define FB_VMODE_YWRAP&t;&t;256&t;/* ywrap instead of panning     */
DECL|macro|FB_VMODE_SMOOTH_XPAN
mdefine_line|#define FB_VMODE_SMOOTH_XPAN&t;512&t;/* smooth xpan possible (internally used) */
DECL|macro|FB_VMODE_CONUPDATE
mdefine_line|#define FB_VMODE_CONUPDATE&t;512&t;/* don&squot;t update x/yoffset&t;*/
DECL|macro|PICOS2KHZ
mdefine_line|#define PICOS2KHZ(a) (1000000000UL/(a))
DECL|macro|KHZ2PICOS
mdefine_line|#define KHZ2PICOS(a) (1000000000UL/(a))
DECL|struct|fb_var_screeninfo
r_struct
id|fb_var_screeninfo
(brace
DECL|member|xres
id|__u32
id|xres
suffix:semicolon
multiline_comment|/* visible resolution&t;&t;*/
DECL|member|yres
id|__u32
id|yres
suffix:semicolon
DECL|member|xres_virtual
id|__u32
id|xres_virtual
suffix:semicolon
multiline_comment|/* virtual resolution&t;&t;*/
DECL|member|yres_virtual
id|__u32
id|yres_virtual
suffix:semicolon
DECL|member|xoffset
id|__u32
id|xoffset
suffix:semicolon
multiline_comment|/* offset from virtual to visible */
DECL|member|yoffset
id|__u32
id|yoffset
suffix:semicolon
multiline_comment|/* resolution&t;&t;&t;*/
DECL|member|bits_per_pixel
id|__u32
id|bits_per_pixel
suffix:semicolon
multiline_comment|/* guess what&t;&t;&t;*/
DECL|member|grayscale
id|__u32
id|grayscale
suffix:semicolon
multiline_comment|/* != 0 Graylevels instead of colors */
DECL|member|red
r_struct
id|fb_bitfield
id|red
suffix:semicolon
multiline_comment|/* bitfield in fb mem if true color, */
DECL|member|green
r_struct
id|fb_bitfield
id|green
suffix:semicolon
multiline_comment|/* else only length is significant */
DECL|member|blue
r_struct
id|fb_bitfield
id|blue
suffix:semicolon
DECL|member|transp
r_struct
id|fb_bitfield
id|transp
suffix:semicolon
multiline_comment|/* transparency&t;&t;&t;*/
DECL|member|nonstd
id|__u32
id|nonstd
suffix:semicolon
multiline_comment|/* != 0 Non standard pixel format */
DECL|member|activate
id|__u32
id|activate
suffix:semicolon
multiline_comment|/* see FB_ACTIVATE_*&t;&t;*/
DECL|member|height
id|__u32
id|height
suffix:semicolon
multiline_comment|/* height of picture in mm    */
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* width of picture in mm     */
DECL|member|accel_flags
id|__u32
id|accel_flags
suffix:semicolon
multiline_comment|/* (OBSOLETE) see fb_info.flags */
multiline_comment|/* Timing: All values in pixclocks, except pixclock (of course) */
DECL|member|pixclock
id|__u32
id|pixclock
suffix:semicolon
multiline_comment|/* pixel clock in ps (pico seconds) */
DECL|member|left_margin
id|__u32
id|left_margin
suffix:semicolon
multiline_comment|/* time from sync to picture&t;*/
DECL|member|right_margin
id|__u32
id|right_margin
suffix:semicolon
multiline_comment|/* time from picture to sync&t;*/
DECL|member|upper_margin
id|__u32
id|upper_margin
suffix:semicolon
multiline_comment|/* time from sync to picture&t;*/
DECL|member|lower_margin
id|__u32
id|lower_margin
suffix:semicolon
DECL|member|hsync_len
id|__u32
id|hsync_len
suffix:semicolon
multiline_comment|/* length of horizontal sync&t;*/
DECL|member|vsync_len
id|__u32
id|vsync_len
suffix:semicolon
multiline_comment|/* length of vertical sync&t;*/
DECL|member|sync
id|__u32
id|sync
suffix:semicolon
multiline_comment|/* see FB_SYNC_*&t;&t;*/
DECL|member|vmode
id|__u32
id|vmode
suffix:semicolon
multiline_comment|/* see FB_VMODE_*&t;&t;*/
DECL|member|rotate
id|__u32
id|rotate
suffix:semicolon
multiline_comment|/* angle we rotate counter clockwise */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Reserved for future compatibility */
)brace
suffix:semicolon
DECL|struct|fb_cmap
r_struct
id|fb_cmap
(brace
DECL|member|start
id|__u32
id|start
suffix:semicolon
multiline_comment|/* First entry&t;*/
DECL|member|len
id|__u32
id|len
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|red
id|__u16
op_star
id|red
suffix:semicolon
multiline_comment|/* Red values&t;*/
DECL|member|green
id|__u16
op_star
id|green
suffix:semicolon
DECL|member|blue
id|__u16
op_star
id|blue
suffix:semicolon
DECL|member|transp
id|__u16
op_star
id|transp
suffix:semicolon
multiline_comment|/* transparency, can be NULL */
)brace
suffix:semicolon
DECL|struct|fb_con2fbmap
r_struct
id|fb_con2fbmap
(brace
DECL|member|console
id|__u32
id|console
suffix:semicolon
DECL|member|framebuffer
id|__u32
id|framebuffer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* VESA Blanking Levels */
DECL|macro|VESA_NO_BLANKING
mdefine_line|#define VESA_NO_BLANKING        0
DECL|macro|VESA_VSYNC_SUSPEND
mdefine_line|#define VESA_VSYNC_SUSPEND      1
DECL|macro|VESA_HSYNC_SUSPEND
mdefine_line|#define VESA_HSYNC_SUSPEND      2
DECL|macro|VESA_POWERDOWN
mdefine_line|#define VESA_POWERDOWN          3
r_enum
(brace
multiline_comment|/* screen: unblanked, hsync: on,  vsync: on */
DECL|enumerator|FB_BLANK_UNBLANK
id|FB_BLANK_UNBLANK
op_assign
id|VESA_NO_BLANKING
comma
multiline_comment|/* screen: blanked,   hsync: on,  vsync: on */
DECL|enumerator|FB_BLANK_NORMAL
id|FB_BLANK_NORMAL
op_assign
id|VESA_NO_BLANKING
op_plus
l_int|1
comma
multiline_comment|/* screen: blanked,   hsync: on,  vsync: off */
DECL|enumerator|FB_BLANK_VSYNC_SUSPEND
id|FB_BLANK_VSYNC_SUSPEND
op_assign
id|VESA_VSYNC_SUSPEND
op_plus
l_int|1
comma
multiline_comment|/* screen: blanked,   hsync: off, vsync: on */
DECL|enumerator|FB_BLANK_HSYNC_SUSPEND
id|FB_BLANK_HSYNC_SUSPEND
op_assign
id|VESA_HSYNC_SUSPEND
op_plus
l_int|1
comma
multiline_comment|/* screen: blanked,   hsync: off, vsync: off */
DECL|enumerator|FB_BLANK_POWERDOWN
id|FB_BLANK_POWERDOWN
op_assign
id|VESA_POWERDOWN
op_plus
l_int|1
)brace
suffix:semicolon
DECL|macro|FB_VBLANK_VBLANKING
mdefine_line|#define FB_VBLANK_VBLANKING&t;0x001&t;/* currently in a vertical blank */
DECL|macro|FB_VBLANK_HBLANKING
mdefine_line|#define FB_VBLANK_HBLANKING&t;0x002&t;/* currently in a horizontal blank */
DECL|macro|FB_VBLANK_HAVE_VBLANK
mdefine_line|#define FB_VBLANK_HAVE_VBLANK&t;0x004&t;/* vertical blanks can be detected */
DECL|macro|FB_VBLANK_HAVE_HBLANK
mdefine_line|#define FB_VBLANK_HAVE_HBLANK&t;0x008&t;/* horizontal blanks can be detected */
DECL|macro|FB_VBLANK_HAVE_COUNT
mdefine_line|#define FB_VBLANK_HAVE_COUNT&t;0x010&t;/* global retrace counter is available */
DECL|macro|FB_VBLANK_HAVE_VCOUNT
mdefine_line|#define FB_VBLANK_HAVE_VCOUNT&t;0x020&t;/* the vcount field is valid */
DECL|macro|FB_VBLANK_HAVE_HCOUNT
mdefine_line|#define FB_VBLANK_HAVE_HCOUNT&t;0x040&t;/* the hcount field is valid */
DECL|macro|FB_VBLANK_VSYNCING
mdefine_line|#define FB_VBLANK_VSYNCING&t;0x080&t;/* currently in a vsync */
DECL|macro|FB_VBLANK_HAVE_VSYNC
mdefine_line|#define FB_VBLANK_HAVE_VSYNC&t;0x100&t;/* verical syncs can be detected */
DECL|struct|fb_vblank
r_struct
id|fb_vblank
(brace
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* FB_VBLANK flags */
DECL|member|count
id|__u32
id|count
suffix:semicolon
multiline_comment|/* counter of retraces since boot */
DECL|member|vcount
id|__u32
id|vcount
suffix:semicolon
multiline_comment|/* current scanline position */
DECL|member|hcount
id|__u32
id|hcount
suffix:semicolon
multiline_comment|/* current scandot position */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved for future compatibility */
)brace
suffix:semicolon
multiline_comment|/* Internal HW accel */
DECL|macro|ROP_COPY
mdefine_line|#define ROP_COPY 0
DECL|macro|ROP_XOR
mdefine_line|#define ROP_XOR  1
DECL|struct|fb_copyarea
r_struct
id|fb_copyarea
(brace
DECL|member|dx
id|__u32
id|dx
suffix:semicolon
DECL|member|dy
id|__u32
id|dy
suffix:semicolon
DECL|member|width
id|__u32
id|width
suffix:semicolon
DECL|member|height
id|__u32
id|height
suffix:semicolon
DECL|member|sx
id|__u32
id|sx
suffix:semicolon
DECL|member|sy
id|__u32
id|sy
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_fillrect
r_struct
id|fb_fillrect
(brace
DECL|member|dx
id|__u32
id|dx
suffix:semicolon
multiline_comment|/* screen-relative */
DECL|member|dy
id|__u32
id|dy
suffix:semicolon
DECL|member|width
id|__u32
id|width
suffix:semicolon
DECL|member|height
id|__u32
id|height
suffix:semicolon
DECL|member|color
id|__u32
id|color
suffix:semicolon
DECL|member|rop
id|__u32
id|rop
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_image
r_struct
id|fb_image
(brace
DECL|member|dx
id|__u32
id|dx
suffix:semicolon
multiline_comment|/* Where to place image */
DECL|member|dy
id|__u32
id|dy
suffix:semicolon
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* Size of image */
DECL|member|height
id|__u32
id|height
suffix:semicolon
DECL|member|fg_color
id|__u32
id|fg_color
suffix:semicolon
multiline_comment|/* Only used when a mono bitmap */
DECL|member|bg_color
id|__u32
id|bg_color
suffix:semicolon
DECL|member|depth
id|__u8
id|depth
suffix:semicolon
multiline_comment|/* Depth of the image */
DECL|member|data
r_const
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to image data */
DECL|member|cmap
r_struct
id|fb_cmap
id|cmap
suffix:semicolon
multiline_comment|/* color map info */
)brace
suffix:semicolon
multiline_comment|/*&n; * hardware cursor control&n; */
DECL|macro|FB_CUR_SETIMAGE
mdefine_line|#define FB_CUR_SETIMAGE 0x01
DECL|macro|FB_CUR_SETPOS
mdefine_line|#define FB_CUR_SETPOS   0x02
DECL|macro|FB_CUR_SETHOT
mdefine_line|#define FB_CUR_SETHOT   0x04
DECL|macro|FB_CUR_SETCMAP
mdefine_line|#define FB_CUR_SETCMAP  0x08
DECL|macro|FB_CUR_SETSHAPE
mdefine_line|#define FB_CUR_SETSHAPE 0x10
DECL|macro|FB_CUR_SETSIZE
mdefine_line|#define FB_CUR_SETSIZE&t;0x20
DECL|macro|FB_CUR_SETALL
mdefine_line|#define FB_CUR_SETALL   0xFF
DECL|struct|fbcurpos
r_struct
id|fbcurpos
(brace
DECL|member|x
DECL|member|y
id|__u16
id|x
comma
id|y
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_cursor
r_struct
id|fb_cursor
(brace
DECL|member|set
id|__u16
id|set
suffix:semicolon
multiline_comment|/* what to set */
DECL|member|enable
id|__u16
id|enable
suffix:semicolon
multiline_comment|/* cursor on/off */
DECL|member|rop
id|__u16
id|rop
suffix:semicolon
multiline_comment|/* bitop operation */
DECL|member|mask
r_const
r_char
op_star
id|mask
suffix:semicolon
multiline_comment|/* cursor mask bits */
DECL|member|hot
r_struct
id|fbcurpos
id|hot
suffix:semicolon
multiline_comment|/* cursor hot spot */
DECL|member|image
r_struct
id|fb_image
id|image
suffix:semicolon
multiline_comment|/* Cursor image */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_struct
id|vm_area_struct
suffix:semicolon
r_struct
id|fb_info
suffix:semicolon
r_struct
id|device
suffix:semicolon
r_struct
id|file
suffix:semicolon
multiline_comment|/* Definitions below are used in the parsed monitor specs */
DECL|macro|FB_DPMS_ACTIVE_OFF
mdefine_line|#define FB_DPMS_ACTIVE_OFF&t;1
DECL|macro|FB_DPMS_SUSPEND
mdefine_line|#define FB_DPMS_SUSPEND&t;&t;2
DECL|macro|FB_DPMS_STANDBY
mdefine_line|#define FB_DPMS_STANDBY&t;&t;4
DECL|macro|FB_DISP_DDI
mdefine_line|#define FB_DISP_DDI&t;&t;1
DECL|macro|FB_DISP_ANA_700_300
mdefine_line|#define FB_DISP_ANA_700_300&t;2
DECL|macro|FB_DISP_ANA_714_286
mdefine_line|#define FB_DISP_ANA_714_286&t;4
DECL|macro|FB_DISP_ANA_1000_400
mdefine_line|#define FB_DISP_ANA_1000_400&t;8
DECL|macro|FB_DISP_ANA_700_000
mdefine_line|#define FB_DISP_ANA_700_000&t;16
DECL|macro|FB_DISP_MONO
mdefine_line|#define FB_DISP_MONO&t;&t;32
DECL|macro|FB_DISP_RGB
mdefine_line|#define FB_DISP_RGB&t;&t;64
DECL|macro|FB_DISP_MULTI
mdefine_line|#define FB_DISP_MULTI&t;&t;128
DECL|macro|FB_DISP_UNKNOWN
mdefine_line|#define FB_DISP_UNKNOWN&t;&t;256
DECL|macro|FB_SIGNAL_NONE
mdefine_line|#define FB_SIGNAL_NONE&t;&t;0
DECL|macro|FB_SIGNAL_BLANK_BLANK
mdefine_line|#define FB_SIGNAL_BLANK_BLANK&t;1
DECL|macro|FB_SIGNAL_SEPARATE
mdefine_line|#define FB_SIGNAL_SEPARATE&t;2
DECL|macro|FB_SIGNAL_COMPOSITE
mdefine_line|#define FB_SIGNAL_COMPOSITE&t;4
DECL|macro|FB_SIGNAL_SYNC_ON_GREEN
mdefine_line|#define FB_SIGNAL_SYNC_ON_GREEN&t;8
DECL|macro|FB_SIGNAL_SERRATION_ON
mdefine_line|#define FB_SIGNAL_SERRATION_ON&t;16
DECL|macro|FB_MISC_PRIM_COLOR
mdefine_line|#define FB_MISC_PRIM_COLOR&t;1
DECL|macro|FB_MISC_1ST_DETAIL
mdefine_line|#define FB_MISC_1ST_DETAIL&t;2&t;/* First Detailed Timing is preferred */
DECL|struct|fb_chroma
r_struct
id|fb_chroma
(brace
DECL|member|redx
id|__u32
id|redx
suffix:semicolon
multiline_comment|/* in fraction of 1024 */
DECL|member|greenx
id|__u32
id|greenx
suffix:semicolon
DECL|member|bluex
id|__u32
id|bluex
suffix:semicolon
DECL|member|whitex
id|__u32
id|whitex
suffix:semicolon
DECL|member|redy
id|__u32
id|redy
suffix:semicolon
DECL|member|greeny
id|__u32
id|greeny
suffix:semicolon
DECL|member|bluey
id|__u32
id|bluey
suffix:semicolon
DECL|member|whitey
id|__u32
id|whitey
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_monspecs
r_struct
id|fb_monspecs
(brace
DECL|member|chroma
r_struct
id|fb_chroma
id|chroma
suffix:semicolon
DECL|member|modedb
r_struct
id|fb_videomode
op_star
id|modedb
suffix:semicolon
multiline_comment|/* mode database */
DECL|member|manufacturer
id|__u8
id|manufacturer
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Manufacturer */
DECL|member|monitor
id|__u8
id|monitor
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Monitor String */
DECL|member|serial_no
id|__u8
id|serial_no
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Serial Number */
DECL|member|ascii
id|__u8
id|ascii
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* ? */
DECL|member|modedb_len
id|__u32
id|modedb_len
suffix:semicolon
multiline_comment|/* mode database length */
DECL|member|model
id|__u32
id|model
suffix:semicolon
multiline_comment|/* Monitor Model */
DECL|member|serial
id|__u32
id|serial
suffix:semicolon
multiline_comment|/* Serial Number - Integer */
DECL|member|year
id|__u32
id|year
suffix:semicolon
multiline_comment|/* Year manufactured */
DECL|member|week
id|__u32
id|week
suffix:semicolon
multiline_comment|/* Week Manufactured */
DECL|member|hfmin
id|__u32
id|hfmin
suffix:semicolon
multiline_comment|/* hfreq lower limit (Hz) */
DECL|member|hfmax
id|__u32
id|hfmax
suffix:semicolon
multiline_comment|/* hfreq upper limit (Hz) */
DECL|member|dclkmin
id|__u32
id|dclkmin
suffix:semicolon
multiline_comment|/* pixelclock lower limit (Hz) */
DECL|member|dclkmax
id|__u32
id|dclkmax
suffix:semicolon
multiline_comment|/* pixelclock upper limit (Hz) */
DECL|member|input
id|__u16
id|input
suffix:semicolon
multiline_comment|/* display type - see FB_DISP_* */
DECL|member|dpms
id|__u16
id|dpms
suffix:semicolon
multiline_comment|/* DPMS support - see FB_DPMS_ */
DECL|member|signal
id|__u16
id|signal
suffix:semicolon
multiline_comment|/* Signal Type - see FB_SIGNAL_* */
DECL|member|vfmin
id|__u16
id|vfmin
suffix:semicolon
multiline_comment|/* vfreq lower limit (Hz) */
DECL|member|vfmax
id|__u16
id|vfmax
suffix:semicolon
multiline_comment|/* vfreq upper limit (Hz) */
DECL|member|gamma
id|__u16
id|gamma
suffix:semicolon
multiline_comment|/* Gamma - in fractions of 100 */
DECL|member|gtf
id|__u16
id|gtf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* supports GTF */
DECL|member|misc
id|__u16
id|misc
suffix:semicolon
multiline_comment|/* Misc flags - see FB_MISC_* */
DECL|member|version
id|__u8
id|version
suffix:semicolon
multiline_comment|/* EDID version... */
DECL|member|revision
id|__u8
id|revision
suffix:semicolon
multiline_comment|/* ...and revision */
DECL|member|max_x
id|__u8
id|max_x
suffix:semicolon
multiline_comment|/* Maximum horizontal size (cm) */
DECL|member|max_y
id|__u8
id|max_y
suffix:semicolon
multiline_comment|/* Maximum vertical size (cm) */
)brace
suffix:semicolon
DECL|struct|fb_cmap_user
r_struct
id|fb_cmap_user
(brace
DECL|member|start
id|__u32
id|start
suffix:semicolon
multiline_comment|/* First entry&t;*/
DECL|member|len
id|__u32
id|len
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|red
id|__u16
id|__user
op_star
id|red
suffix:semicolon
multiline_comment|/* Red values&t;*/
DECL|member|green
id|__u16
id|__user
op_star
id|green
suffix:semicolon
DECL|member|blue
id|__u16
id|__user
op_star
id|blue
suffix:semicolon
DECL|member|transp
id|__u16
id|__user
op_star
id|transp
suffix:semicolon
multiline_comment|/* transparency, can be NULL */
)brace
suffix:semicolon
DECL|struct|fb_image_user
r_struct
id|fb_image_user
(brace
DECL|member|dx
id|__u32
id|dx
suffix:semicolon
multiline_comment|/* Where to place image */
DECL|member|dy
id|__u32
id|dy
suffix:semicolon
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* Size of image */
DECL|member|height
id|__u32
id|height
suffix:semicolon
DECL|member|fg_color
id|__u32
id|fg_color
suffix:semicolon
multiline_comment|/* Only used when a mono bitmap */
DECL|member|bg_color
id|__u32
id|bg_color
suffix:semicolon
DECL|member|depth
id|__u8
id|depth
suffix:semicolon
multiline_comment|/* Depth of the image */
DECL|member|data
r_const
r_char
id|__user
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to image data */
DECL|member|cmap
r_struct
id|fb_cmap_user
id|cmap
suffix:semicolon
multiline_comment|/* color map info */
)brace
suffix:semicolon
DECL|struct|fb_cursor_user
r_struct
id|fb_cursor_user
(brace
DECL|member|set
id|__u16
id|set
suffix:semicolon
multiline_comment|/* what to set */
DECL|member|enable
id|__u16
id|enable
suffix:semicolon
multiline_comment|/* cursor on/off */
DECL|member|rop
id|__u16
id|rop
suffix:semicolon
multiline_comment|/* bitop operation */
DECL|member|mask
r_const
r_char
id|__user
op_star
id|mask
suffix:semicolon
multiline_comment|/* cursor mask bits */
DECL|member|hot
r_struct
id|fbcurpos
id|hot
suffix:semicolon
multiline_comment|/* cursor hot spot */
DECL|member|image
r_struct
id|fb_image_user
id|image
suffix:semicolon
multiline_comment|/* Cursor image */
)brace
suffix:semicolon
multiline_comment|/*&n; * Register/unregister for framebuffer events&n; */
multiline_comment|/*&t;The resolution of the passed in fb_info about to change */
DECL|macro|FB_EVENT_MODE_CHANGE
mdefine_line|#define FB_EVENT_MODE_CHANGE&t;&t;0x01
multiline_comment|/*&t;The display on this fb_info is beeing suspended, no access to the&n; *&t;framebuffer is allowed any more after that call returns&n; */
DECL|macro|FB_EVENT_SUSPEND
mdefine_line|#define FB_EVENT_SUSPEND&t;&t;0x02
multiline_comment|/*&t;The display on this fb_info was resumed, you can restore the display&n; *&t;if you own it&n; */
DECL|macro|FB_EVENT_RESUME
mdefine_line|#define FB_EVENT_RESUME&t;&t;&t;0x03
multiline_comment|/*      An entry from the modelist was removed */
DECL|macro|FB_EVENT_MODE_DELETE
mdefine_line|#define FB_EVENT_MODE_DELETE            0x04
multiline_comment|/*      A driver registered itself */
DECL|macro|FB_EVENT_FB_REGISTERED
mdefine_line|#define FB_EVENT_FB_REGISTERED          0x05
multiline_comment|/*      get console to framebuffer mapping */
DECL|macro|FB_EVENT_GET_CONSOLE_MAP
mdefine_line|#define FB_EVENT_GET_CONSOLE_MAP        0x06
multiline_comment|/*      set console to framebuffer mapping */
DECL|macro|FB_EVENT_SET_CONSOLE_MAP
mdefine_line|#define FB_EVENT_SET_CONSOLE_MAP        0x07
multiline_comment|/*      A display blank is requested       */
DECL|macro|FB_EVENT_BLANK
mdefine_line|#define FB_EVENT_BLANK                  0x08
DECL|struct|fb_event
r_struct
id|fb_event
(brace
DECL|member|info
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|fb_register_client
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_int
id|fb_unregister_client
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
multiline_comment|/*&n; * Pixmap structure definition&n; *&n; * The purpose of this structure is to translate data&n; * from the hardware independent format of fbdev to what&n; * format the hardware needs.&n; */
DECL|macro|FB_PIXMAP_DEFAULT
mdefine_line|#define FB_PIXMAP_DEFAULT 1     /* used internally by fbcon */
DECL|macro|FB_PIXMAP_SYSTEM
mdefine_line|#define FB_PIXMAP_SYSTEM  2     /* memory is in system RAM  */
DECL|macro|FB_PIXMAP_IO
mdefine_line|#define FB_PIXMAP_IO      4     /* memory is iomapped       */
DECL|macro|FB_PIXMAP_SYNC
mdefine_line|#define FB_PIXMAP_SYNC    256   /* set if GPU can DMA       */
DECL|struct|fb_pixmap
r_struct
id|fb_pixmap
(brace
DECL|member|addr
id|u8
op_star
id|addr
suffix:semicolon
multiline_comment|/* pointer to memory&t;&t;&t;*/
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* size of buffer in bytes&t;&t;*/
DECL|member|offset
id|u32
id|offset
suffix:semicolon
multiline_comment|/* current offset to buffer&t;&t;*/
DECL|member|buf_align
id|u32
id|buf_align
suffix:semicolon
multiline_comment|/* byte alignment of each bitmap&t;*/
DECL|member|scan_align
id|u32
id|scan_align
suffix:semicolon
multiline_comment|/* alignment per scanline&t;&t;*/
DECL|member|access_align
id|u32
id|access_align
suffix:semicolon
multiline_comment|/* alignment per read/write&t;&t;*/
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* see FB_PIXMAP_*&t;&t;&t;*/
multiline_comment|/* access methods */
DECL|member|outbuf
r_void
(paren
op_star
id|outbuf
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
id|u8
op_star
id|addr
comma
id|u8
op_star
id|src
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|inbuf
id|u8
(paren
op_star
id|inbuf
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
id|u8
op_star
id|addr
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Frame buffer operations&n; *&n; * LOCKING NOTE: those functions must _ALL_ be called with the console&n; * semaphore held, this is the only suitable locking mecanism we have&n; * in 2.6. Some may be called at interrupt time at this point though.&n; */
DECL|struct|fb_ops
r_struct
id|fb_ops
(brace
multiline_comment|/* open/release and usage marking */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|fb_open
r_int
(paren
op_star
id|fb_open
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
suffix:semicolon
DECL|member|fb_release
r_int
(paren
op_star
id|fb_release
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
suffix:semicolon
multiline_comment|/* For framebuffers with strange non linear layouts or that do not&n;&t; * work with normal memory mapped access&n;&t; */
DECL|member|fb_read
id|ssize_t
(paren
op_star
id|fb_read
)paren
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
DECL|member|fb_write
id|ssize_t
(paren
op_star
id|fb_write
)paren
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
multiline_comment|/* checks var and eventually tweaks it to something supported,&n;&t; * DO NOT MODIFY PAR */
DECL|member|fb_check_var
r_int
(paren
op_star
id|fb_check_var
)paren
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* set the video mode according to info-&gt;var */
DECL|member|fb_set_par
r_int
(paren
op_star
id|fb_set_par
)paren
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* set color register */
DECL|member|fb_setcolreg
r_int
(paren
op_star
id|fb_setcolreg
)paren
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* blank display */
DECL|member|fb_blank
r_int
(paren
op_star
id|fb_blank
)paren
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* pan display */
DECL|member|fb_pan_display
r_int
(paren
op_star
id|fb_pan_display
)paren
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* Draws a rectangle */
DECL|member|fb_fillrect
r_void
(paren
op_star
id|fb_fillrect
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
suffix:semicolon
multiline_comment|/* Copy data from area to another */
DECL|member|fb_copyarea
r_void
(paren
op_star
id|fb_copyarea
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_copyarea
op_star
id|region
)paren
suffix:semicolon
multiline_comment|/* Draws a image to the display */
DECL|member|fb_imageblit
r_void
(paren
op_star
id|fb_imageblit
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_image
op_star
id|image
)paren
suffix:semicolon
multiline_comment|/* Draws cursor */
DECL|member|fb_cursor
r_int
(paren
op_star
id|fb_cursor
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_cursor
op_star
id|cursor
)paren
suffix:semicolon
multiline_comment|/* Rotates the display */
DECL|member|fb_rotate
r_void
(paren
op_star
id|fb_rotate
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|angle
)paren
suffix:semicolon
multiline_comment|/* wait for blit idle, optional */
DECL|member|fb_sync
r_int
(paren
op_star
id|fb_sync
)paren
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* perform fb specific ioctl (optional) */
DECL|member|fb_ioctl
r_int
(paren
op_star
id|fb_ioctl
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* perform fb specific mmap */
DECL|member|fb_mmap
r_int
(paren
op_star
id|fb_mmap
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_FB_TILEBLITTING
DECL|macro|FB_TILE_CURSOR_NONE
mdefine_line|#define FB_TILE_CURSOR_NONE        0
DECL|macro|FB_TILE_CURSOR_UNDERLINE
mdefine_line|#define FB_TILE_CURSOR_UNDERLINE   1
DECL|macro|FB_TILE_CURSOR_LOWER_THIRD
mdefine_line|#define FB_TILE_CURSOR_LOWER_THIRD 2
DECL|macro|FB_TILE_CURSOR_LOWER_HALF
mdefine_line|#define FB_TILE_CURSOR_LOWER_HALF  3
DECL|macro|FB_TILE_CURSOR_TWO_THIRDS
mdefine_line|#define FB_TILE_CURSOR_TWO_THIRDS  4
DECL|macro|FB_TILE_CURSOR_BLOCK
mdefine_line|#define FB_TILE_CURSOR_BLOCK       5
DECL|struct|fb_tilemap
r_struct
id|fb_tilemap
(brace
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* width of each tile in pixels */
DECL|member|height
id|__u32
id|height
suffix:semicolon
multiline_comment|/* height of each tile in scanlines */
DECL|member|depth
id|__u32
id|depth
suffix:semicolon
multiline_comment|/* color depth of each tile */
DECL|member|length
id|__u32
id|length
suffix:semicolon
multiline_comment|/* number of tiles in the map */
DECL|member|data
id|__u8
op_star
id|data
suffix:semicolon
multiline_comment|/* actual tile map: a bitmap array, packed&n;&t;&t;&t;&t;       to the nearest byte */
)brace
suffix:semicolon
DECL|struct|fb_tilerect
r_struct
id|fb_tilerect
(brace
DECL|member|sx
id|__u32
id|sx
suffix:semicolon
multiline_comment|/* origin in the x-axis */
DECL|member|sy
id|__u32
id|sy
suffix:semicolon
multiline_comment|/* origin in the y-axis */
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* number of tiles in the x-axis */
DECL|member|height
id|__u32
id|height
suffix:semicolon
multiline_comment|/* number of tiles in the y-axis */
DECL|member|index
id|__u32
id|index
suffix:semicolon
multiline_comment|/* what tile to use: index to tile map */
DECL|member|fg
id|__u32
id|fg
suffix:semicolon
multiline_comment|/* foreground color */
DECL|member|bg
id|__u32
id|bg
suffix:semicolon
multiline_comment|/* background color */
DECL|member|rop
id|__u32
id|rop
suffix:semicolon
multiline_comment|/* raster operation */
)brace
suffix:semicolon
DECL|struct|fb_tilearea
r_struct
id|fb_tilearea
(brace
DECL|member|sx
id|__u32
id|sx
suffix:semicolon
multiline_comment|/* source origin in the x-axis */
DECL|member|sy
id|__u32
id|sy
suffix:semicolon
multiline_comment|/* source origin in the y-axis */
DECL|member|dx
id|__u32
id|dx
suffix:semicolon
multiline_comment|/* destination origin in the x-axis */
DECL|member|dy
id|__u32
id|dy
suffix:semicolon
multiline_comment|/* destination origin in the y-axis */
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* number of tiles in the x-axis */
DECL|member|height
id|__u32
id|height
suffix:semicolon
multiline_comment|/* number of tiles in the y-axis */
)brace
suffix:semicolon
DECL|struct|fb_tileblit
r_struct
id|fb_tileblit
(brace
DECL|member|sx
id|__u32
id|sx
suffix:semicolon
multiline_comment|/* origin in the x-axis */
DECL|member|sy
id|__u32
id|sy
suffix:semicolon
multiline_comment|/* origin in the y-axis */
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* number of tiles in the x-axis */
DECL|member|height
id|__u32
id|height
suffix:semicolon
multiline_comment|/* number of tiles in the y-axis */
DECL|member|fg
id|__u32
id|fg
suffix:semicolon
multiline_comment|/* foreground color */
DECL|member|bg
id|__u32
id|bg
suffix:semicolon
multiline_comment|/* background color */
DECL|member|length
id|__u32
id|length
suffix:semicolon
multiline_comment|/* number of tiles to draw */
DECL|member|indices
id|__u32
op_star
id|indices
suffix:semicolon
multiline_comment|/* array of indices to tile map */
)brace
suffix:semicolon
DECL|struct|fb_tilecursor
r_struct
id|fb_tilecursor
(brace
DECL|member|sx
id|__u32
id|sx
suffix:semicolon
multiline_comment|/* cursor position in the x-axis */
DECL|member|sy
id|__u32
id|sy
suffix:semicolon
multiline_comment|/* cursor position in the y-axis */
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
multiline_comment|/* 0 = erase, 1 = draw */
DECL|member|shape
id|__u32
id|shape
suffix:semicolon
multiline_comment|/* see FB_TILE_CURSOR_* */
DECL|member|fg
id|__u32
id|fg
suffix:semicolon
multiline_comment|/* foreground color */
DECL|member|bg
id|__u32
id|bg
suffix:semicolon
multiline_comment|/* background color */
)brace
suffix:semicolon
DECL|struct|fb_tile_ops
r_struct
id|fb_tile_ops
(brace
multiline_comment|/* set tile characteristics */
DECL|member|fb_settile
r_void
(paren
op_star
id|fb_settile
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_tilemap
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/* all dimensions from hereon are in terms of tiles */
multiline_comment|/* move a rectangular region of tiles from one area to another*/
DECL|member|fb_tilecopy
r_void
(paren
op_star
id|fb_tilecopy
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_tilearea
op_star
id|area
)paren
suffix:semicolon
multiline_comment|/* fill a rectangular region with a tile */
DECL|member|fb_tilefill
r_void
(paren
op_star
id|fb_tilefill
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_tilerect
op_star
id|rect
)paren
suffix:semicolon
multiline_comment|/* copy an array of tiles */
DECL|member|fb_tileblit
r_void
(paren
op_star
id|fb_tileblit
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_tileblit
op_star
id|blit
)paren
suffix:semicolon
multiline_comment|/* cursor */
DECL|member|fb_tilecursor
r_void
(paren
op_star
id|fb_tilecursor
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_tilecursor
op_star
id|cursor
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_FB_TILEBLITTING */
multiline_comment|/* FBINFO_* = fb_info.flags bit flags */
DECL|macro|FBINFO_MODULE
mdefine_line|#define FBINFO_MODULE&t;&t;0x0001&t;/* Low-level driver is a module */
DECL|macro|FBINFO_HWACCEL_DISABLED
mdefine_line|#define FBINFO_HWACCEL_DISABLED&t;0x0002
multiline_comment|/* When FBINFO_HWACCEL_DISABLED is set:&n;&t; *  Hardware acceleration is turned off.  Software implementations&n;&t; *  of required functions (copyarea(), fillrect(), and imageblit())&n;&t; *  takes over; acceleration engine should be in a quiescent state */
multiline_comment|/* hints */
DECL|macro|FBINFO_PARTIAL_PAN_OK
mdefine_line|#define FBINFO_PARTIAL_PAN_OK&t;0x0040 /* otw use pan only for double-buffering */
DECL|macro|FBINFO_READS_FAST
mdefine_line|#define FBINFO_READS_FAST&t;0x0080 /* soft-copy faster than rendering */
multiline_comment|/* hardware supported ops */
multiline_comment|/*  semantics: when a bit is set, it indicates that the operation is&n; *   accelerated by hardware.&n; *  required functions will still work even if the bit is not set.&n; *  optional functions may not even exist if the flag bit is not set.&n; */
DECL|macro|FBINFO_HWACCEL_NONE
mdefine_line|#define FBINFO_HWACCEL_NONE&t;&t;0x0000
DECL|macro|FBINFO_HWACCEL_COPYAREA
mdefine_line|#define FBINFO_HWACCEL_COPYAREA&t;&t;0x0100 /* required */
DECL|macro|FBINFO_HWACCEL_FILLRECT
mdefine_line|#define FBINFO_HWACCEL_FILLRECT&t;&t;0x0200 /* required */
DECL|macro|FBINFO_HWACCEL_IMAGEBLIT
mdefine_line|#define FBINFO_HWACCEL_IMAGEBLIT&t;0x0400 /* required */
DECL|macro|FBINFO_HWACCEL_ROTATE
mdefine_line|#define FBINFO_HWACCEL_ROTATE&t;&t;0x0800 /* optional */
DECL|macro|FBINFO_HWACCEL_XPAN
mdefine_line|#define FBINFO_HWACCEL_XPAN&t;&t;0x1000 /* optional */
DECL|macro|FBINFO_HWACCEL_YPAN
mdefine_line|#define FBINFO_HWACCEL_YPAN&t;&t;0x2000 /* optional */
DECL|macro|FBINFO_HWACCEL_YWRAP
mdefine_line|#define FBINFO_HWACCEL_YWRAP&t;&t;0x4000 /* optional */
DECL|macro|FBINFO_MISC_USEREVENT
mdefine_line|#define FBINFO_MISC_USEREVENT          0x10000 /* event request&n;&t;&t;&t;&t;&t;&t;  from userspace */
DECL|macro|FBINFO_MISC_MODESWITCH
mdefine_line|#define FBINFO_MISC_MODESWITCH         0x20000 /* mode switch */
DECL|macro|FBINFO_MISC_MODESWITCHLATE
mdefine_line|#define FBINFO_MISC_MODESWITCHLATE     0x40000 /* init hardware later */
DECL|macro|FBINFO_MISC_TILEBLITTING
mdefine_line|#define FBINFO_MISC_TILEBLITTING       0x80000 /* use tile blitting */
DECL|struct|fb_info
r_struct
id|fb_info
(brace
DECL|member|node
r_int
id|node
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|var
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
multiline_comment|/* Current var */
DECL|member|fix
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
multiline_comment|/* Current fix */
DECL|member|monspecs
r_struct
id|fb_monspecs
id|monspecs
suffix:semicolon
multiline_comment|/* Current Monitor specs */
DECL|member|queue
r_struct
id|work_struct
id|queue
suffix:semicolon
multiline_comment|/* Framebuffer event queue */
DECL|member|pixmap
r_struct
id|fb_pixmap
id|pixmap
suffix:semicolon
multiline_comment|/* Image hardware mapper */
DECL|member|sprite
r_struct
id|fb_pixmap
id|sprite
suffix:semicolon
multiline_comment|/* Cursor hardware mapper */
DECL|member|cmap
r_struct
id|fb_cmap
id|cmap
suffix:semicolon
multiline_comment|/* Current cmap */
DECL|member|modelist
r_struct
id|list_head
id|modelist
suffix:semicolon
multiline_comment|/* mode list */
DECL|member|fbops
r_struct
id|fb_ops
op_star
id|fbops
suffix:semicolon
DECL|member|device
r_struct
id|device
op_star
id|device
suffix:semicolon
macro_line|#ifdef CONFIG_FB_TILEBLITTING
DECL|member|tileops
r_struct
id|fb_tile_ops
op_star
id|tileops
suffix:semicolon
multiline_comment|/* Tile Blitting */
macro_line|#endif
DECL|member|screen_base
r_char
id|__iomem
op_star
id|screen_base
suffix:semicolon
multiline_comment|/* Virtual address */
DECL|member|screen_size
r_int
r_int
id|screen_size
suffix:semicolon
multiline_comment|/* Amount of ioremapped VRAM or 0 */
DECL|member|pseudo_palette
r_void
op_star
id|pseudo_palette
suffix:semicolon
multiline_comment|/* Fake palette of 16 colors */
DECL|macro|FBINFO_STATE_RUNNING
mdefine_line|#define FBINFO_STATE_RUNNING&t;0
DECL|macro|FBINFO_STATE_SUSPENDED
mdefine_line|#define FBINFO_STATE_SUSPENDED&t;1
DECL|member|state
id|u32
id|state
suffix:semicolon
multiline_comment|/* Hardware state i.e suspend */
DECL|member|fbcon_par
r_void
op_star
id|fbcon_par
suffix:semicolon
multiline_comment|/* fbcon use-only private area */
multiline_comment|/* From here on everything is device dependent */
DECL|member|par
r_void
op_star
id|par
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|macro|FBINFO_DEFAULT
mdefine_line|#define FBINFO_DEFAULT&t;FBINFO_MODULE
macro_line|#else
DECL|macro|FBINFO_DEFAULT
mdefine_line|#define FBINFO_DEFAULT&t;0
macro_line|#endif
singleline_comment|// This will go away
DECL|macro|FBINFO_FLAG_MODULE
mdefine_line|#define FBINFO_FLAG_MODULE&t;FBINFO_MODULE
DECL|macro|FBINFO_FLAG_DEFAULT
mdefine_line|#define FBINFO_FLAG_DEFAULT&t;FBINFO_DEFAULT
multiline_comment|/* This will go away&n; * fbset currently hacks in FB_ACCELF_TEXT into var.accel_flags&n; * when it wants to turn the acceleration engine on.  This is&n; * really a separate operation, and should be modified via sysfs.&n; *  But for now, we leave it broken with the following define&n; */
DECL|macro|STUPID_ACCELF_TEXT_SHIT
mdefine_line|#define STUPID_ACCELF_TEXT_SHIT
singleline_comment|// This will go away
macro_line|#if defined(__sparc__)
multiline_comment|/* We map all of our framebuffers such that big-endian accesses&n; * are what we want, so the following is sufficient.&n; */
singleline_comment|// This will go away
DECL|macro|fb_readb
mdefine_line|#define fb_readb sbus_readb
DECL|macro|fb_readw
mdefine_line|#define fb_readw sbus_readw
DECL|macro|fb_readl
mdefine_line|#define fb_readl sbus_readl
DECL|macro|fb_readq
mdefine_line|#define fb_readq sbus_readq
DECL|macro|fb_writeb
mdefine_line|#define fb_writeb sbus_writeb
DECL|macro|fb_writew
mdefine_line|#define fb_writew sbus_writew
DECL|macro|fb_writel
mdefine_line|#define fb_writel sbus_writel
DECL|macro|fb_writeq
mdefine_line|#define fb_writeq sbus_writeq
DECL|macro|fb_memset
mdefine_line|#define fb_memset sbus_memset_io
macro_line|#elif defined(__i386__) || defined(__alpha__) || defined(__x86_64__) || defined(__hppa__) || (defined(__sh__) &amp;&amp; !defined(__SH5__)) || defined(__powerpc__)
DECL|macro|fb_readb
mdefine_line|#define fb_readb __raw_readb
DECL|macro|fb_readw
mdefine_line|#define fb_readw __raw_readw
DECL|macro|fb_readl
mdefine_line|#define fb_readl __raw_readl
DECL|macro|fb_readq
mdefine_line|#define fb_readq __raw_readq
DECL|macro|fb_writeb
mdefine_line|#define fb_writeb __raw_writeb
DECL|macro|fb_writew
mdefine_line|#define fb_writew __raw_writew
DECL|macro|fb_writel
mdefine_line|#define fb_writel __raw_writel
DECL|macro|fb_writeq
mdefine_line|#define fb_writeq __raw_writeq
DECL|macro|fb_memset
mdefine_line|#define fb_memset memset_io
macro_line|#else
DECL|macro|fb_readb
mdefine_line|#define fb_readb(addr) (*(volatile u8 *) (addr))
DECL|macro|fb_readw
mdefine_line|#define fb_readw(addr) (*(volatile u16 *) (addr))
DECL|macro|fb_readl
mdefine_line|#define fb_readl(addr) (*(volatile u32 *) (addr))
DECL|macro|fb_readq
mdefine_line|#define fb_readq(addr) (*(volatile u64 *) (addr))
DECL|macro|fb_writeb
mdefine_line|#define fb_writeb(b,addr) (*(volatile u8 *) (addr) = (b))
DECL|macro|fb_writew
mdefine_line|#define fb_writew(b,addr) (*(volatile u16 *) (addr) = (b))
DECL|macro|fb_writel
mdefine_line|#define fb_writel(b,addr) (*(volatile u32 *) (addr) = (b))
DECL|macro|fb_writeq
mdefine_line|#define fb_writeq(b,addr) (*(volatile u64 *) (addr) = (b))
DECL|macro|fb_memset
mdefine_line|#define fb_memset memset
macro_line|#endif
multiline_comment|/*&n;     *  `Generic&squot; versions of the frame buffer device operations&n;     */
r_extern
r_int
id|fb_set_var
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_extern
r_int
id|fb_pan_display
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_extern
r_int
id|fb_blank
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|blank
)paren
suffix:semicolon
r_extern
r_int
id|soft_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_cursor
op_star
id|cursor
)paren
suffix:semicolon
r_extern
r_void
id|cfb_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
suffix:semicolon
r_extern
r_void
id|cfb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_copyarea
op_star
id|area
)paren
suffix:semicolon
r_extern
r_void
id|cfb_imageblit
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_image
op_star
id|image
)paren
suffix:semicolon
multiline_comment|/* drivers/video/fbmem.c */
r_extern
r_int
id|register_framebuffer
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|unregister_framebuffer
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fb_prepare_logo
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fb_show_logo
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_char
op_star
id|fb_get_buffer_offset
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_pixmap
op_star
id|buf
comma
id|u32
id|size
)paren
suffix:semicolon
r_extern
r_void
id|fb_iomove_buf_unaligned
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_pixmap
op_star
id|buf
comma
id|u8
op_star
id|dst
comma
id|u32
id|d_pitch
comma
id|u8
op_star
id|src
comma
id|u32
id|idx
comma
id|u32
id|height
comma
id|u32
id|shift_high
comma
id|u32
id|shift_low
comma
id|u32
id|mod
)paren
suffix:semicolon
r_extern
r_void
id|fb_iomove_buf_aligned
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_pixmap
op_star
id|buf
comma
id|u8
op_star
id|dst
comma
id|u32
id|d_pitch
comma
id|u8
op_star
id|src
comma
id|u32
id|s_pitch
comma
id|u32
id|height
)paren
suffix:semicolon
r_extern
r_void
id|fb_sysmove_buf_unaligned
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_pixmap
op_star
id|buf
comma
id|u8
op_star
id|dst
comma
id|u32
id|d_pitch
comma
id|u8
op_star
id|src
comma
id|u32
id|idx
comma
id|u32
id|height
comma
id|u32
id|shift_high
comma
id|u32
id|shift_low
comma
id|u32
id|mod
)paren
suffix:semicolon
r_extern
r_void
id|fb_sysmove_buf_aligned
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_pixmap
op_star
id|buf
comma
id|u8
op_star
id|dst
comma
id|u32
id|d_pitch
comma
id|u8
op_star
id|src
comma
id|u32
id|s_pitch
comma
id|u32
id|height
)paren
suffix:semicolon
r_extern
r_void
id|fb_set_suspend
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|state
)paren
suffix:semicolon
r_extern
r_int
id|fb_get_color_depth
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fb_get_options
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
op_star
id|option
)paren
suffix:semicolon
r_extern
r_struct
id|fb_info
op_star
id|registered_fb
(braket
id|FB_MAX
)braket
suffix:semicolon
r_extern
r_int
id|num_registered_fb
suffix:semicolon
multiline_comment|/* drivers/video/fbsysfs.c */
r_extern
r_struct
id|fb_info
op_star
id|framebuffer_alloc
c_func
(paren
r_int
id|size
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|framebuffer_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* drivers/video/fbmon.c */
DECL|macro|FB_MAXTIMINGS
mdefine_line|#define FB_MAXTIMINGS&t;&t;0
DECL|macro|FB_VSYNCTIMINGS
mdefine_line|#define FB_VSYNCTIMINGS&t;&t;1
DECL|macro|FB_HSYNCTIMINGS
mdefine_line|#define FB_HSYNCTIMINGS&t;&t;2
DECL|macro|FB_DCLKTIMINGS
mdefine_line|#define FB_DCLKTIMINGS&t;&t;3
DECL|macro|FB_IGNOREMON
mdefine_line|#define FB_IGNOREMON&t;&t;0x100
DECL|macro|FB_MODE_IS_UNKNOWN
mdefine_line|#define FB_MODE_IS_UNKNOWN&t;0
DECL|macro|FB_MODE_IS_DETAILED
mdefine_line|#define FB_MODE_IS_DETAILED&t;1
DECL|macro|FB_MODE_IS_STANDARD
mdefine_line|#define FB_MODE_IS_STANDARD&t;2
DECL|macro|FB_MODE_IS_VESA
mdefine_line|#define FB_MODE_IS_VESA&t;&t;4
DECL|macro|FB_MODE_IS_CALCULATED
mdefine_line|#define FB_MODE_IS_CALCULATED&t;8
DECL|macro|FB_MODE_IS_FIRST
mdefine_line|#define FB_MODE_IS_FIRST&t;16
DECL|macro|FB_MODE_IS_FROM_VAR
mdefine_line|#define FB_MODE_IS_FROM_VAR     32
r_extern
r_int
id|fbmon_valid_timings
c_func
(paren
id|u_int
id|pixclock
comma
id|u_int
id|htotal
comma
id|u_int
id|vtotal
comma
r_const
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fbmon_dpms
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fb_get_mode
c_func
(paren
r_int
id|flags
comma
id|u32
id|val
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fb_validate_mode
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fb_parse_edid
c_func
(paren
r_int
r_char
op_star
id|edid
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_extern
r_int
id|fb_get_monitor_limits
c_func
(paren
r_int
r_char
op_star
id|edid
comma
r_struct
id|fb_monspecs
op_star
id|specs
)paren
suffix:semicolon
r_extern
r_void
id|fb_edid_to_monspecs
c_func
(paren
r_int
r_char
op_star
id|edid
comma
r_struct
id|fb_monspecs
op_star
id|specs
)paren
suffix:semicolon
r_extern
r_int
id|fb_get_monitor_limits
c_func
(paren
r_int
r_char
op_star
id|edid
comma
r_struct
id|fb_monspecs
op_star
id|specs
)paren
suffix:semicolon
r_extern
r_struct
id|fb_videomode
op_star
id|fb_create_modedb
c_func
(paren
r_int
r_char
op_star
id|edid
comma
r_int
op_star
id|dbsize
)paren
suffix:semicolon
r_extern
r_void
id|fb_destroy_modedb
c_func
(paren
r_struct
id|fb_videomode
op_star
id|modedb
)paren
suffix:semicolon
multiline_comment|/* drivers/video/modedb.c */
DECL|macro|VESA_MODEDB_SIZE
mdefine_line|#define VESA_MODEDB_SIZE 34
r_extern
r_const
r_struct
id|fb_videomode
id|vesa_modes
(braket
)braket
suffix:semicolon
r_extern
r_void
id|fb_var_to_videomode
c_func
(paren
r_struct
id|fb_videomode
op_star
id|mode
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_extern
r_void
id|fb_videomode_to_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_videomode
op_star
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|fb_mode_is_equal
c_func
(paren
r_struct
id|fb_videomode
op_star
id|mode1
comma
r_struct
id|fb_videomode
op_star
id|mode2
)paren
suffix:semicolon
r_extern
r_int
id|fb_add_videomode
c_func
(paren
r_struct
id|fb_videomode
op_star
id|mode
comma
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
r_extern
r_void
id|fb_delete_videomode
c_func
(paren
r_struct
id|fb_videomode
op_star
id|mode
comma
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
r_extern
r_struct
id|fb_videomode
op_star
id|fb_match_mode
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
r_extern
r_struct
id|fb_videomode
op_star
id|fb_find_best_mode
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
r_extern
r_void
id|fb_destroy_modelist
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
r_extern
r_void
id|fb_videomode_to_modelist
c_func
(paren
r_struct
id|fb_videomode
op_star
id|modedb
comma
r_int
id|num
comma
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
multiline_comment|/* drivers/video/fbcmap.c */
r_extern
r_int
id|fb_alloc_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|len
comma
r_int
id|transp
)paren
suffix:semicolon
r_extern
r_void
id|fb_dealloc_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
)paren
suffix:semicolon
r_extern
r_int
id|fb_copy_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|from
comma
r_struct
id|fb_cmap
op_star
id|to
)paren
suffix:semicolon
r_extern
r_int
id|fb_cmap_to_user
c_func
(paren
r_struct
id|fb_cmap
op_star
id|from
comma
r_struct
id|fb_cmap_user
op_star
id|to
)paren
suffix:semicolon
r_extern
r_int
id|fb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fb_set_user_cmap
c_func
(paren
r_struct
id|fb_cmap_user
op_star
id|cmap
comma
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_struct
id|fb_cmap
op_star
id|fb_default_cmap
c_func
(paren
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|fb_invert_cmaps
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|struct|fb_videomode
r_struct
id|fb_videomode
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* optional */
DECL|member|refresh
id|u32
id|refresh
suffix:semicolon
multiline_comment|/* optional */
DECL|member|xres
id|u32
id|xres
suffix:semicolon
DECL|member|yres
id|u32
id|yres
suffix:semicolon
DECL|member|pixclock
id|u32
id|pixclock
suffix:semicolon
DECL|member|left_margin
id|u32
id|left_margin
suffix:semicolon
DECL|member|right_margin
id|u32
id|right_margin
suffix:semicolon
DECL|member|upper_margin
id|u32
id|upper_margin
suffix:semicolon
DECL|member|lower_margin
id|u32
id|lower_margin
suffix:semicolon
DECL|member|hsync_len
id|u32
id|hsync_len
suffix:semicolon
DECL|member|vsync_len
id|u32
id|vsync_len
suffix:semicolon
DECL|member|sync
id|u32
id|sync
suffix:semicolon
DECL|member|vmode
id|u32
id|vmode
suffix:semicolon
DECL|member|flag
id|u32
id|flag
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_modelist
r_struct
id|fb_modelist
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|mode
r_struct
id|fb_videomode
id|mode
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|fb_find_mode
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_char
op_star
id|mode_option
comma
r_const
r_struct
id|fb_videomode
op_star
id|db
comma
r_int
r_int
id|dbsize
comma
r_const
r_struct
id|fb_videomode
op_star
id|default_mode
comma
r_int
r_int
id|default_bpp
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_FB_H */
eof
