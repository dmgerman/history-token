multiline_comment|/*&n; * Architecture specific parts of HP&squot;s STI (framebuffer) driver&n; * structures are HP-UX compatible for XFree86 usage &n; */
macro_line|#ifndef __ASM_PARISC_GRFIOCTL_H
DECL|macro|__ASM_PARISC_GRFIOCTL_H
mdefine_line|#define __ASM_PARISC_GRFIOCTL_H
multiline_comment|/* upper 32 bits of graphics id (HP/UX identifier) */
DECL|macro|GRFGATOR
mdefine_line|#define GRFGATOR&t;&t;8
DECL|macro|S9000_ID_S300
mdefine_line|#define S9000_ID_S300&t;&t;9
DECL|macro|GRFBOBCAT
mdefine_line|#define GRFBOBCAT&t;&t;9
DECL|macro|GRFCATSEYE
mdefine_line|#define&t;GRFCATSEYE&t;&t;9
DECL|macro|S9000_ID_98720
mdefine_line|#define S9000_ID_98720&t;&t;10
DECL|macro|GRFRBOX
mdefine_line|#define GRFRBOX&t;&t;&t;10
DECL|macro|S9000_ID_98550
mdefine_line|#define S9000_ID_98550&t;&t;11
DECL|macro|GRFFIREEYE
mdefine_line|#define GRFFIREEYE&t;&t;11
DECL|macro|S9000_ID_A1096A
mdefine_line|#define S9000_ID_A1096A&t;&t;12
DECL|macro|GRFHYPERION
mdefine_line|#define GRFHYPERION&t;&t;12
DECL|macro|S9000_ID_FRI
mdefine_line|#define S9000_ID_FRI&t;&t;13
DECL|macro|S9000_ID_98730
mdefine_line|#define S9000_ID_98730&t;&t;14
DECL|macro|GRFDAVINCI
mdefine_line|#define GRFDAVINCI&t;&t;14
DECL|macro|S9000_ID_98705
mdefine_line|#define S9000_ID_98705&t;&t;0x26C08070&t;/* Tigershark */
DECL|macro|S9000_ID_98736
mdefine_line|#define S9000_ID_98736&t;&t;0x26D148AB
DECL|macro|S9000_ID_A1659A
mdefine_line|#define S9000_ID_A1659A&t;&t;0x26D1482A&t;/* CRX 8 plane color (=ELK) */
DECL|macro|S9000_ID_ELK
mdefine_line|#define S9000_ID_ELK&t;&t;S9000_ID_A1659A
DECL|macro|S9000_ID_A1439A
mdefine_line|#define S9000_ID_A1439A&t;&t;0x26D148EE&t;/* CRX24 = CRX+ (24-plane color) */
DECL|macro|S9000_ID_A1924A
mdefine_line|#define S9000_ID_A1924A&t;&t;0x26D1488C&t;/* GRX gray-scale */
DECL|macro|S9000_ID_ELM
mdefine_line|#define S9000_ID_ELM&t;&t;S9000_ID_A1924A
DECL|macro|S9000_ID_98765
mdefine_line|#define S9000_ID_98765&t;&t;0x27480DEF
DECL|macro|S9000_ID_ELK_768
mdefine_line|#define S9000_ID_ELK_768&t;0x27482101
DECL|macro|S9000_ID_STINGER
mdefine_line|#define S9000_ID_STINGER&t;0x27A4A402
DECL|macro|S9000_ID_TIMBER
mdefine_line|#define S9000_ID_TIMBER&t;&t;0x27F12392&t;/* Bushmaster (710) Graphics */
DECL|macro|S9000_ID_TOMCAT
mdefine_line|#define S9000_ID_TOMCAT&t;&t;0x27FCCB6D&t;/* dual-headed ELK (Dual CRX) */
DECL|macro|S9000_ID_ARTIST
mdefine_line|#define S9000_ID_ARTIST&t;&t;0x2B4DED6D&t;/* Artist (Gecko/712 &amp; 715) onboard Graphics */
DECL|macro|S9000_ID_HCRX
mdefine_line|#define S9000_ID_HCRX&t;&t;0x2BCB015A&t;/* Hyperdrive/Hyperbowl (A4071A) Graphics */
DECL|macro|CRX24_OVERLAY_PLANES
mdefine_line|#define CRX24_OVERLAY_PLANES&t;0x920825AA&t;/* Overlay planes on CRX24 */
DECL|macro|CRT_ID_ELK_1024
mdefine_line|#define CRT_ID_ELK_1024&t;&t;S9000_ID_ELK_768 /* Elk 1024x768  CRX */
DECL|macro|CRT_ID_ELK_1280
mdefine_line|#define CRT_ID_ELK_1280&t;&t;S9000_ID_A1659A&t;/* Elk 1280x1024 CRX */
DECL|macro|CRT_ID_ELK_1024DB
mdefine_line|#define CRT_ID_ELK_1024DB&t;0x27849CA5      /* Elk 1024x768 double buffer */
DECL|macro|CRT_ID_ELK_GS
mdefine_line|#define CRT_ID_ELK_GS&t;&t;S9000_ID_A1924A&t;/* Elk 1280x1024 GreyScale    */
DECL|macro|CRT_ID_CRX24
mdefine_line|#define CRT_ID_CRX24&t;&t;S9000_ID_A1439A&t;/* Piranha */
DECL|macro|CRT_ID_VISUALIZE_EG
mdefine_line|#define CRT_ID_VISUALIZE_EG&t;0x2D08C0A7      /* Graffiti (built-in B132+/B160L) */
DECL|macro|CRT_ID_THUNDER
mdefine_line|#define CRT_ID_THUNDER&t;&t;0x2F23E5FC      /* Thunder 1 VISUALIZE 48*/
DECL|macro|CRT_ID_THUNDER2
mdefine_line|#define CRT_ID_THUNDER2&t;&t;0x2F8D570E      /* Thunder 2 VISUALIZE 48 XP*/
DECL|macro|CRT_ID_HCRX
mdefine_line|#define CRT_ID_HCRX&t;&t;S9000_ID_HCRX&t;/* Hyperdrive HCRX */
DECL|macro|CRT_ID_CRX48Z
mdefine_line|#define CRT_ID_CRX48Z&t;&t;S9000_ID_STINGER /* Stinger */
DECL|macro|CRT_ID_DUAL_CRX
mdefine_line|#define CRT_ID_DUAL_CRX&t;&t;S9000_ID_TOMCAT&t;/* Tomcat */
DECL|macro|CRT_ID_PVRX
mdefine_line|#define CRT_ID_PVRX&t;&t;S9000_ID_98705&t;/* Tigershark */
DECL|macro|CRT_ID_TIMBER
mdefine_line|#define CRT_ID_TIMBER&t;&t;S9000_ID_TIMBER&t;/* Timber (710 builtin) */
DECL|macro|CRT_ID_TVRX
mdefine_line|#define CRT_ID_TVRX&t;&t;S9000_ID_98765&t;/* TVRX (gto/falcon) */
DECL|macro|CRT_ID_ARTIST
mdefine_line|#define CRT_ID_ARTIST&t;&t;S9000_ID_ARTIST&t;/* Artist */
DECL|macro|CRT_ID_SUMMIT
mdefine_line|#define CRT_ID_SUMMIT&t;&t;0x2FC1066B      /* Summit FX2, FX4, FX6 ... */
multiline_comment|/* structure for ioctl(GCDESCRIBE) */
DECL|macro|gaddr_t
mdefine_line|#define gaddr_t unsigned long&t;/* FIXME: PA2.0 (64bit) portable ? */
DECL|struct|grf_fbinfo
r_struct
id|grf_fbinfo
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* upper 32 bits of graphics id */
DECL|member|mapsize
r_int
r_int
id|mapsize
suffix:semicolon
multiline_comment|/* mapped size of framebuffer */
DECL|member|dwidth
DECL|member|dlength
r_int
r_int
id|dwidth
comma
id|dlength
suffix:semicolon
multiline_comment|/* x and y sizes */
DECL|member|width
DECL|member|length
r_int
r_int
id|width
comma
id|length
suffix:semicolon
multiline_comment|/* total x and total y size */
DECL|member|xlen
r_int
r_int
id|xlen
suffix:semicolon
multiline_comment|/* x pitch size */
DECL|member|bpp
DECL|member|bppu
r_int
r_int
id|bpp
comma
id|bppu
suffix:semicolon
multiline_comment|/* bits per pixel and used bpp */
DECL|member|npl
DECL|member|nplbytes
r_int
r_int
id|npl
comma
id|nplbytes
suffix:semicolon
multiline_comment|/* # of planes and bytes per plane */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* name of the device (from ROM) */
DECL|member|attr
r_int
r_int
id|attr
suffix:semicolon
multiline_comment|/* attributes */
DECL|member|fbbase
DECL|member|regbase
id|gaddr_t
id|fbbase
comma
id|regbase
suffix:semicolon
multiline_comment|/* framebuffer and register base addr */
DECL|member|regions
id|gaddr_t
id|regions
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* region bases */
)brace
suffix:semicolon
DECL|macro|GCID
mdefine_line|#define&t;GCID&t;&t;_IOR(&squot;G&squot;, 0, int)
DECL|macro|GCON
mdefine_line|#define&t;GCON&t;&t;_IO(&squot;G&squot;, 1)
DECL|macro|GCOFF
mdefine_line|#define&t;GCOFF&t;&t;_IO(&squot;G&squot;, 2)
DECL|macro|GCAON
mdefine_line|#define&t;GCAON&t;&t;_IO(&squot;G&squot;, 3)
DECL|macro|GCAOFF
mdefine_line|#define&t;GCAOFF&t;&t;_IO(&squot;G&squot;, 4)
DECL|macro|GCMAP
mdefine_line|#define&t;GCMAP&t;&t;_IOWR(&squot;G&squot;, 5, int)
DECL|macro|GCUNMAP
mdefine_line|#define&t;GCUNMAP&t;&t;_IOWR(&squot;G&squot;, 6, int)
DECL|macro|GCMAP_HPUX
mdefine_line|#define&t;GCMAP_HPUX&t;_IO(&squot;G&squot;, 5)
DECL|macro|GCUNMAP_HPUX
mdefine_line|#define&t;GCUNMAP_HPUX&t;_IO(&squot;G&squot;, 6)
DECL|macro|GCLOCK
mdefine_line|#define&t;GCLOCK&t;&t;_IO(&squot;G&squot;, 7)
DECL|macro|GCUNLOCK
mdefine_line|#define&t;GCUNLOCK&t;_IO(&squot;G&squot;, 8)
DECL|macro|GCLOCK_MINIMUM
mdefine_line|#define&t;GCLOCK_MINIMUM&t;_IO(&squot;G&squot;, 9)
DECL|macro|GCUNLOCK_MINIMUM
mdefine_line|#define&t;GCUNLOCK_MINIMUM _IO(&squot;G&squot;, 10)
DECL|macro|GCSTATIC_CMAP
mdefine_line|#define&t;GCSTATIC_CMAP&t;_IO(&squot;G&squot;, 11)
DECL|macro|GCVARIABLE_CMAP
mdefine_line|#define&t;GCVARIABLE_CMAP _IO(&squot;G&squot;, 12)
DECL|macro|GCTERM
mdefine_line|#define GCTERM&t;&t;_IOWR(&squot;G&squot;,20,int)&t;/* multi-headed Tomcat */ 
DECL|macro|GCDESCRIBE
mdefine_line|#define GCDESCRIBE&t;_IOR(&squot;G&squot;, 21, struct grf_fbinfo)
DECL|macro|GCFASTLOCK
mdefine_line|#define GCFASTLOCK&t;_IO(&squot;G&squot;, 26)
macro_line|#endif /* __ASM_PARISC_GRFIOCTL_H */
eof
