macro_line|#ifndef __LINUX_FBIO_H
DECL|macro|__LINUX_FBIO_H
mdefine_line|#define __LINUX_FBIO_H
multiline_comment|/* Constants used for fbio SunOS compatibility */
multiline_comment|/* (C) 1996 Miguel de Icaza */
multiline_comment|/* Frame buffer types */
DECL|macro|FBTYPE_NOTYPE
mdefine_line|#define FBTYPE_NOTYPE           -1
DECL|macro|FBTYPE_SUN1BW
mdefine_line|#define FBTYPE_SUN1BW           0   /* mono */
DECL|macro|FBTYPE_SUN1COLOR
mdefine_line|#define FBTYPE_SUN1COLOR        1 
DECL|macro|FBTYPE_SUN2BW
mdefine_line|#define FBTYPE_SUN2BW           2 
DECL|macro|FBTYPE_SUN2COLOR
mdefine_line|#define FBTYPE_SUN2COLOR        3 
DECL|macro|FBTYPE_SUN2GP
mdefine_line|#define FBTYPE_SUN2GP           4 
DECL|macro|FBTYPE_SUN5COLOR
mdefine_line|#define FBTYPE_SUN5COLOR        5 
DECL|macro|FBTYPE_SUN3COLOR
mdefine_line|#define FBTYPE_SUN3COLOR        6 
DECL|macro|FBTYPE_MEMCOLOR
mdefine_line|#define FBTYPE_MEMCOLOR         7 
DECL|macro|FBTYPE_SUN4COLOR
mdefine_line|#define FBTYPE_SUN4COLOR        8 
DECL|macro|FBTYPE_NOTSUN1
mdefine_line|#define FBTYPE_NOTSUN1          9 
DECL|macro|FBTYPE_NOTSUN2
mdefine_line|#define FBTYPE_NOTSUN2          10
DECL|macro|FBTYPE_NOTSUN3
mdefine_line|#define FBTYPE_NOTSUN3          11
DECL|macro|FBTYPE_SUNFAST_COLOR
mdefine_line|#define FBTYPE_SUNFAST_COLOR    12  /* cg6 */
DECL|macro|FBTYPE_SUNROP_COLOR
mdefine_line|#define FBTYPE_SUNROP_COLOR     13
DECL|macro|FBTYPE_SUNFB_VIDEO
mdefine_line|#define FBTYPE_SUNFB_VIDEO      14
DECL|macro|FBTYPE_SUNGIFB
mdefine_line|#define FBTYPE_SUNGIFB          15
DECL|macro|FBTYPE_SUNGPLAS
mdefine_line|#define FBTYPE_SUNGPLAS         16
DECL|macro|FBTYPE_SUNGP3
mdefine_line|#define FBTYPE_SUNGP3           17
DECL|macro|FBTYPE_SUNGT
mdefine_line|#define FBTYPE_SUNGT            18
DECL|macro|FBTYPE_SUNLEO
mdefine_line|#define FBTYPE_SUNLEO           19      /* zx Leo card */
DECL|macro|FBTYPE_MDICOLOR
mdefine_line|#define FBTYPE_MDICOLOR         20      /* cg14 */
DECL|macro|FBTYPE_TCXCOLOR
mdefine_line|#define FBTYPE_TCXCOLOR&t;&t;21&t;/* SUNW,tcx card */
DECL|macro|FBTYPE_LASTPLUSONE
mdefine_line|#define FBTYPE_LASTPLUSONE      21&t;/* This is not last + 1 in fact... */
multiline_comment|/* Does not seem to be listed in the Sun file either */
DECL|macro|FBTYPE_CREATOR
mdefine_line|#define FBTYPE_CREATOR          22
DECL|macro|FBTYPE_PCI_IGA1682
mdefine_line|#define FBTYPE_PCI_IGA1682&t;23
DECL|macro|FBTYPE_P9100COLOR
mdefine_line|#define FBTYPE_P9100COLOR&t;24
DECL|macro|FBTYPE_PCI_GENERIC
mdefine_line|#define FBTYPE_PCI_GENERIC&t;1000
DECL|macro|FBTYPE_PCI_MACH64
mdefine_line|#define FBTYPE_PCI_MACH64&t;1001
multiline_comment|/* fbio ioctls */
multiline_comment|/* Returned by FBIOGTYPE */
DECL|struct|fbtype
r_struct
id|fbtype
(brace
DECL|member|fb_type
r_int
id|fb_type
suffix:semicolon
multiline_comment|/* fb type, see above */
DECL|member|fb_height
r_int
id|fb_height
suffix:semicolon
multiline_comment|/* pixels */
DECL|member|fb_width
r_int
id|fb_width
suffix:semicolon
multiline_comment|/* pixels */
DECL|member|fb_depth
r_int
id|fb_depth
suffix:semicolon
DECL|member|fb_cmsize
r_int
id|fb_cmsize
suffix:semicolon
multiline_comment|/* color map entries */
DECL|member|fb_size
r_int
id|fb_size
suffix:semicolon
multiline_comment|/* fb size in bytes */
)brace
suffix:semicolon
DECL|macro|FBIOGTYPE
mdefine_line|#define FBIOGTYPE _IOR(&squot;F&squot;, 0, struct fbtype)
DECL|struct|fbcmap
r_struct
id|fbcmap
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* first element (0 origin) */
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|red
r_int
r_char
op_star
id|red
suffix:semicolon
DECL|member|green
r_int
r_char
op_star
id|green
suffix:semicolon
DECL|member|blue
r_int
r_char
op_star
id|blue
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|FBIOPUTCMAP_SPARC
mdefine_line|#define FBIOPUTCMAP_SPARC _IOW(&squot;F&squot;, 3, struct fbcmap)
DECL|macro|FBIOGETCMAP_SPARC
mdefine_line|#define FBIOGETCMAP_SPARC _IOW(&squot;F&squot;, 4, struct fbcmap)
macro_line|#else
DECL|macro|FBIOPUTCMAP
mdefine_line|#define FBIOPUTCMAP _IOW(&squot;F&squot;, 3, struct fbcmap)
DECL|macro|FBIOGETCMAP
mdefine_line|#define FBIOGETCMAP _IOW(&squot;F&squot;, 4, struct fbcmap)
macro_line|#endif
multiline_comment|/* # of device specific values */
DECL|macro|FB_ATTR_NDEVSPECIFIC
mdefine_line|#define FB_ATTR_NDEVSPECIFIC    8
multiline_comment|/* # of possible emulations */
DECL|macro|FB_ATTR_NEMUTYPES
mdefine_line|#define FB_ATTR_NEMUTYPES       4
DECL|struct|fbsattr
r_struct
id|fbsattr
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|emu_type
r_int
id|emu_type
suffix:semicolon
multiline_comment|/* -1 if none */
DECL|member|dev_specific
r_int
id|dev_specific
(braket
id|FB_ATTR_NDEVSPECIFIC
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fbgattr
r_struct
id|fbgattr
(brace
DECL|member|real_type
r_int
id|real_type
suffix:semicolon
multiline_comment|/* real frame buffer type */
DECL|member|owner
r_int
id|owner
suffix:semicolon
multiline_comment|/* unknown */
DECL|member|fbtype
r_struct
id|fbtype
id|fbtype
suffix:semicolon
multiline_comment|/* real frame buffer fbtype */
DECL|member|sattr
r_struct
id|fbsattr
id|sattr
suffix:semicolon
DECL|member|emu_types
r_int
id|emu_types
(braket
id|FB_ATTR_NEMUTYPES
)braket
suffix:semicolon
multiline_comment|/* supported emulations */
)brace
suffix:semicolon
DECL|macro|FBIOSATTR
mdefine_line|#define FBIOSATTR  _IOW(&squot;F&squot;, 5, struct fbgattr) /* Unsupported: */
DECL|macro|FBIOGATTR
mdefine_line|#define FBIOGATTR  _IOR(&squot;F&squot;, 6, struct fbgattr)&t;/* supported */
DECL|macro|FBIOSVIDEO
mdefine_line|#define FBIOSVIDEO _IOW(&squot;F&squot;, 7, int)
DECL|macro|FBIOGVIDEO
mdefine_line|#define FBIOGVIDEO _IOR(&squot;F&squot;, 8, int)
multiline_comment|/* Cursor position */
DECL|struct|fbcurpos
r_struct
id|fbcurpos
(brace
macro_line|#ifdef __KERNEL__
DECL|member|fbx
DECL|member|fby
r_int
id|fbx
comma
id|fby
suffix:semicolon
macro_line|#else
r_int
id|x
comma
id|y
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Cursor operations */
DECL|macro|FB_CUR_SETCUR
mdefine_line|#define FB_CUR_SETCUR   0x01&t;/* Enable/disable cursor display */
DECL|macro|FB_CUR_SETPOS
mdefine_line|#define FB_CUR_SETPOS   0x02&t;/* set cursor position */
DECL|macro|FB_CUR_SETHOT
mdefine_line|#define FB_CUR_SETHOT   0x04&t;/* set cursor hotspot */
DECL|macro|FB_CUR_SETCMAP
mdefine_line|#define FB_CUR_SETCMAP  0x08&t;/* set color map for the cursor */
DECL|macro|FB_CUR_SETSHAPE
mdefine_line|#define FB_CUR_SETSHAPE 0x10&t;/* set shape */
DECL|macro|FB_CUR_SETALL
mdefine_line|#define FB_CUR_SETALL   0x1F&t;/* all of the above */
DECL|struct|fbcursor
r_struct
id|fbcursor
(brace
DECL|member|set
r_int
id|set
suffix:semicolon
multiline_comment|/* what to set, choose from the list above */
DECL|member|enable
r_int
id|enable
suffix:semicolon
multiline_comment|/* cursor on/off */
DECL|member|pos
r_struct
id|fbcurpos
id|pos
suffix:semicolon
multiline_comment|/* cursor position */
DECL|member|hot
r_struct
id|fbcurpos
id|hot
suffix:semicolon
multiline_comment|/* cursor hot spot */
DECL|member|cmap
r_struct
id|fbcmap
id|cmap
suffix:semicolon
multiline_comment|/* color map info */
DECL|member|size
r_struct
id|fbcurpos
id|size
suffix:semicolon
multiline_comment|/* cursor bit map size */
DECL|member|image
r_char
op_star
id|image
suffix:semicolon
multiline_comment|/* cursor image bits */
DECL|member|mask
r_char
op_star
id|mask
suffix:semicolon
multiline_comment|/* cursor mask bits */
)brace
suffix:semicolon
multiline_comment|/* set/get cursor attributes/shape */
DECL|macro|FBIOSCURSOR
mdefine_line|#define FBIOSCURSOR     _IOW(&squot;F&squot;, 24, struct fbcursor)
DECL|macro|FBIOGCURSOR
mdefine_line|#define FBIOGCURSOR     _IOWR(&squot;F&squot;, 25, struct fbcursor)
multiline_comment|/* set/get cursor position */
DECL|macro|FBIOSCURPOS
mdefine_line|#define FBIOSCURPOS     _IOW(&squot;F&squot;, 26, struct fbcurpos)
DECL|macro|FBIOGCURPOS
mdefine_line|#define FBIOGCURPOS     _IOW(&squot;F&squot;, 27, struct fbcurpos)
multiline_comment|/* get max cursor size */
DECL|macro|FBIOGCURMAX
mdefine_line|#define FBIOGCURMAX     _IOR(&squot;F&squot;, 28, struct fbcurpos)
multiline_comment|/* wid manipulation */
DECL|struct|fb_wid_alloc
r_struct
id|fb_wid_alloc
(brace
DECL|macro|FB_WID_SHARED_8
mdefine_line|#define FB_WID_SHARED_8&t;&t;0
DECL|macro|FB_WID_SHARED_24
mdefine_line|#define FB_WID_SHARED_24&t;1
DECL|macro|FB_WID_DBL_8
mdefine_line|#define FB_WID_DBL_8&t;&t;2
DECL|macro|FB_WID_DBL_24
mdefine_line|#define FB_WID_DBL_24&t;&t;3
DECL|member|wa_type
id|__u32
id|wa_type
suffix:semicolon
DECL|member|wa_index
id|__s32
id|wa_index
suffix:semicolon
multiline_comment|/* Set on return */
DECL|member|wa_count
id|__u32
id|wa_count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_wid_item
r_struct
id|fb_wid_item
(brace
DECL|member|wi_type
id|__u32
id|wi_type
suffix:semicolon
DECL|member|wi_index
id|__s32
id|wi_index
suffix:semicolon
DECL|member|wi_attrs
id|__u32
id|wi_attrs
suffix:semicolon
DECL|member|wi_values
id|__u32
id|wi_values
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_wid_list
r_struct
id|fb_wid_list
(brace
DECL|member|wl_flags
id|__u32
id|wl_flags
suffix:semicolon
DECL|member|wl_count
id|__u32
id|wl_count
suffix:semicolon
DECL|member|wl_list
r_struct
id|fb_wid_item
op_star
id|wl_list
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FBIO_WID_ALLOC
mdefine_line|#define FBIO_WID_ALLOC&t;_IOWR(&squot;F&squot;, 30, struct fb_wid_alloc)
DECL|macro|FBIO_WID_FREE
mdefine_line|#define FBIO_WID_FREE&t;_IOW(&squot;F&squot;, 31, struct fb_wid_alloc)
DECL|macro|FBIO_WID_PUT
mdefine_line|#define FBIO_WID_PUT&t;_IOW(&squot;F&squot;, 32, struct fb_wid_list)
DECL|macro|FBIO_WID_GET
mdefine_line|#define FBIO_WID_GET&t;_IOWR(&squot;F&squot;, 33, struct fb_wid_list)
multiline_comment|/* Creator ioctls */
DECL|macro|FFB_IOCTL
mdefine_line|#define FFB_IOCTL&t;(&squot;F&squot;&lt;&lt;8)
DECL|macro|FFB_SYS_INFO
mdefine_line|#define FFB_SYS_INFO&t;&t;(FFB_IOCTL|80)
DECL|macro|FFB_CLUTREAD
mdefine_line|#define FFB_CLUTREAD&t;&t;(FFB_IOCTL|81)
DECL|macro|FFB_CLUTPOST
mdefine_line|#define FFB_CLUTPOST&t;&t;(FFB_IOCTL|82)
DECL|macro|FFB_SETDIAGMODE
mdefine_line|#define FFB_SETDIAGMODE&t;&t;(FFB_IOCTL|83)
DECL|macro|FFB_GETMONITORID
mdefine_line|#define FFB_GETMONITORID&t;(FFB_IOCTL|84)
DECL|macro|FFB_GETVIDEOMODE
mdefine_line|#define FFB_GETVIDEOMODE&t;(FFB_IOCTL|85)
DECL|macro|FFB_SETVIDEOMODE
mdefine_line|#define FFB_SETVIDEOMODE&t;(FFB_IOCTL|86)
DECL|macro|FFB_SETSERVER
mdefine_line|#define FFB_SETSERVER&t;&t;(FFB_IOCTL|87)
DECL|macro|FFB_SETOVCTL
mdefine_line|#define FFB_SETOVCTL&t;&t;(FFB_IOCTL|88)
DECL|macro|FFB_GETOVCTL
mdefine_line|#define FFB_GETOVCTL&t;&t;(FFB_IOCTL|89)
DECL|macro|FFB_GETSAXNUM
mdefine_line|#define FFB_GETSAXNUM&t;&t;(FFB_IOCTL|90)
DECL|macro|FFB_FBDEBUG
mdefine_line|#define FFB_FBDEBUG&t;&t;(FFB_IOCTL|91)
multiline_comment|/* Cg14 ioctls */
DECL|macro|MDI_IOCTL
mdefine_line|#define MDI_IOCTL          (&squot;M&squot;&lt;&lt;8)
DECL|macro|MDI_RESET
mdefine_line|#define MDI_RESET          (MDI_IOCTL|1)
DECL|macro|MDI_GET_CFGINFO
mdefine_line|#define MDI_GET_CFGINFO    (MDI_IOCTL|2)
DECL|macro|MDI_SET_PIXELMODE
mdefine_line|#define MDI_SET_PIXELMODE  (MDI_IOCTL|3)
DECL|macro|MDI_32_PIX
macro_line|#    define MDI_32_PIX     32
DECL|macro|MDI_16_PIX
macro_line|#    define MDI_16_PIX     16
DECL|macro|MDI_8_PIX
macro_line|#    define MDI_8_PIX      8
DECL|struct|mdi_cfginfo
r_struct
id|mdi_cfginfo
(brace
DECL|member|mdi_ncluts
r_int
id|mdi_ncluts
suffix:semicolon
multiline_comment|/* Number of implemented CLUTs in this MDI */
DECL|member|mdi_type
r_int
id|mdi_type
suffix:semicolon
multiline_comment|/* FBTYPE name */
DECL|member|mdi_height
r_int
id|mdi_height
suffix:semicolon
multiline_comment|/* height */
DECL|member|mdi_width
r_int
id|mdi_width
suffix:semicolon
multiline_comment|/* widht */
DECL|member|mdi_size
r_int
id|mdi_size
suffix:semicolon
multiline_comment|/* available ram */
DECL|member|mdi_mode
r_int
id|mdi_mode
suffix:semicolon
multiline_comment|/* 8bpp, 16bpp or 32bpp */
DECL|member|mdi_pixfreq
r_int
id|mdi_pixfreq
suffix:semicolon
multiline_comment|/* pixel clock (from PROM) */
)brace
suffix:semicolon
multiline_comment|/* SparcLinux specific ioctl for the MDI, should be replaced for&n; * the SET_XLUT/SET_CLUTn ioctls instead&n; */
DECL|macro|MDI_CLEAR_XLUT
mdefine_line|#define MDI_CLEAR_XLUT       (MDI_IOCTL|9)
multiline_comment|/* leo &amp; ffb ioctls */
DECL|struct|fb_clut_alloc
r_struct
id|fb_clut_alloc
(brace
DECL|member|clutid
id|__u32
id|clutid
suffix:semicolon
multiline_comment|/* Set on return */
DECL|member|flag
id|__u32
id|flag
suffix:semicolon
DECL|member|index
id|__u32
id|index
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_clut
r_struct
id|fb_clut
(brace
DECL|macro|FB_CLUT_WAIT
mdefine_line|#define FB_CLUT_WAIT&t;0x00000001&t;/* Not yet implemented */
DECL|member|flag
id|__u32
id|flag
suffix:semicolon
DECL|member|clutid
id|__u32
id|clutid
suffix:semicolon
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|red
r_char
op_star
id|red
suffix:semicolon
DECL|member|green
r_char
op_star
id|green
suffix:semicolon
DECL|member|blue
r_char
op_star
id|blue
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_clut32
r_struct
id|fb_clut32
(brace
DECL|member|flag
id|__u32
id|flag
suffix:semicolon
DECL|member|clutid
id|__u32
id|clutid
suffix:semicolon
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|red
id|__u32
id|red
suffix:semicolon
DECL|member|green
id|__u32
id|green
suffix:semicolon
DECL|member|blue
id|__u32
id|blue
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LEO_CLUTALLOC
mdefine_line|#define LEO_CLUTALLOC&t;_IOWR(&squot;L&squot;, 53, struct fb_clut_alloc)
DECL|macro|LEO_CLUTFREE
mdefine_line|#define LEO_CLUTFREE&t;_IOW(&squot;L&squot;, 54, struct fb_clut_alloc)
DECL|macro|LEO_CLUTREAD
mdefine_line|#define LEO_CLUTREAD&t;_IOW(&squot;L&squot;, 55, struct fb_clut)
DECL|macro|LEO_CLUTPOST
mdefine_line|#define LEO_CLUTPOST&t;_IOW(&squot;L&squot;, 56, struct fb_clut)
DECL|macro|LEO_SETGAMMA
mdefine_line|#define LEO_SETGAMMA&t;_IOW(&squot;L&squot;, 68, int) /* Not yet implemented */
DECL|macro|LEO_GETGAMMA
mdefine_line|#define LEO_GETGAMMA&t;_IOR(&squot;L&squot;, 69, int) /* Not yet implemented */
macro_line|#ifdef __KERNEL__
multiline_comment|/* Addresses on the fd of a cgsix that are mappable */
DECL|macro|CG6_FBC
mdefine_line|#define CG6_FBC    0x70000000
DECL|macro|CG6_TEC
mdefine_line|#define CG6_TEC    0x70001000
DECL|macro|CG6_BTREGS
mdefine_line|#define CG6_BTREGS 0x70002000
DECL|macro|CG6_FHC
mdefine_line|#define CG6_FHC    0x70004000
DECL|macro|CG6_THC
mdefine_line|#define CG6_THC    0x70005000
DECL|macro|CG6_ROM
mdefine_line|#define CG6_ROM    0x70006000
DECL|macro|CG6_RAM
mdefine_line|#define CG6_RAM    0x70016000
DECL|macro|CG6_DHC
mdefine_line|#define CG6_DHC    0x80000000
DECL|macro|CG3_MMAP_OFFSET
mdefine_line|#define CG3_MMAP_OFFSET 0x4000000
multiline_comment|/* Addresses on the fd of a tcx that are mappable */
DECL|macro|TCX_RAM8BIT
mdefine_line|#define TCX_RAM8BIT   &t;&t;0x00000000
DECL|macro|TCX_RAM24BIT
mdefine_line|#define TCX_RAM24BIT   &t;&t;0x01000000
DECL|macro|TCX_UNK3
mdefine_line|#define TCX_UNK3   &t;&t;0x10000000
DECL|macro|TCX_UNK4
mdefine_line|#define TCX_UNK4   &t;&t;0x20000000
DECL|macro|TCX_CONTROLPLANE
mdefine_line|#define TCX_CONTROLPLANE   &t;0x28000000
DECL|macro|TCX_UNK6
mdefine_line|#define TCX_UNK6   &t;&t;0x30000000
DECL|macro|TCX_UNK7
mdefine_line|#define TCX_UNK7   &t;&t;0x38000000
DECL|macro|TCX_TEC
mdefine_line|#define TCX_TEC    &t;&t;0x70000000
DECL|macro|TCX_BTREGS
mdefine_line|#define TCX_BTREGS &t;&t;0x70002000
DECL|macro|TCX_THC
mdefine_line|#define TCX_THC    &t;&t;0x70004000
DECL|macro|TCX_DHC
mdefine_line|#define TCX_DHC    &t;&t;0x70008000
DECL|macro|TCX_ALT
mdefine_line|#define TCX_ALT&t;   &t;&t;0x7000a000
DECL|macro|TCX_SYNC
mdefine_line|#define TCX_SYNC   &t;&t;0x7000e000
DECL|macro|TCX_UNK2
mdefine_line|#define TCX_UNK2    &t;&t;0x70010000
multiline_comment|/* CG14 definitions */
multiline_comment|/* Offsets into the OBIO space: */
DECL|macro|CG14_REGS
mdefine_line|#define CG14_REGS        0       /* registers */
DECL|macro|CG14_CURSORREGS
mdefine_line|#define CG14_CURSORREGS  0x1000  /* cursor registers */
DECL|macro|CG14_DACREGS
mdefine_line|#define CG14_DACREGS     0x2000  /* DAC registers */
DECL|macro|CG14_XLUT
mdefine_line|#define CG14_XLUT        0x3000  /* X Look Up Table -- ??? */
DECL|macro|CG14_CLUT1
mdefine_line|#define CG14_CLUT1       0x4000  /* Color Look Up Table */
DECL|macro|CG14_CLUT2
mdefine_line|#define CG14_CLUT2       0x5000  /* Color Look Up Table */
DECL|macro|CG14_CLUT3
mdefine_line|#define CG14_CLUT3       0x6000  /* Color Look Up Table */
DECL|macro|CG14_AUTO
mdefine_line|#define CG14_AUTO&t; 0xf000
macro_line|#endif /* KERNEL */
multiline_comment|/* These are exported to userland for applications to use */
multiline_comment|/* Mappable offsets for the cg14: control registers */
DECL|macro|MDI_DIRECT_MAP
mdefine_line|#define MDI_DIRECT_MAP 0x10000000
DECL|macro|MDI_CTLREG_MAP
mdefine_line|#define MDI_CTLREG_MAP 0x20000000
DECL|macro|MDI_CURSOR_MAP
mdefine_line|#define MDI_CURSOR_MAP 0x30000000
DECL|macro|MDI_SHDW_VRT_MAP
mdefine_line|#define MDI_SHDW_VRT_MAP 0x40000000
multiline_comment|/* Mappable offsets for the cg14: frame buffer resolutions */
multiline_comment|/* 32 bits */
DECL|macro|MDI_CHUNKY_XBGR_MAP
mdefine_line|#define MDI_CHUNKY_XBGR_MAP 0x50000000
DECL|macro|MDI_CHUNKY_BGR_MAP
mdefine_line|#define MDI_CHUNKY_BGR_MAP 0x60000000
multiline_comment|/* 16 bits */
DECL|macro|MDI_PLANAR_X16_MAP
mdefine_line|#define MDI_PLANAR_X16_MAP 0x70000000
DECL|macro|MDI_PLANAR_C16_MAP
mdefine_line|#define MDI_PLANAR_C16_MAP 0x80000000
multiline_comment|/* 8 bit is done as CG3 MMAP offset */
multiline_comment|/* 32 bits, planar */
DECL|macro|MDI_PLANAR_X32_MAP
mdefine_line|#define MDI_PLANAR_X32_MAP 0x90000000
DECL|macro|MDI_PLANAR_B32_MAP
mdefine_line|#define MDI_PLANAR_B32_MAP 0xa0000000
DECL|macro|MDI_PLANAR_G32_MAP
mdefine_line|#define MDI_PLANAR_G32_MAP 0xb0000000
DECL|macro|MDI_PLANAR_R32_MAP
mdefine_line|#define MDI_PLANAR_R32_MAP 0xc0000000
multiline_comment|/* Mappable offsets on leo */
DECL|macro|LEO_SS0_MAP
mdefine_line|#define LEO_SS0_MAP            0x00000000
DECL|macro|LEO_LC_SS0_USR_MAP
mdefine_line|#define LEO_LC_SS0_USR_MAP     0x00800000
DECL|macro|LEO_LD_SS0_MAP
mdefine_line|#define LEO_LD_SS0_MAP         0x00801000
DECL|macro|LEO_LX_CURSOR_MAP
mdefine_line|#define LEO_LX_CURSOR_MAP      0x00802000
DECL|macro|LEO_SS1_MAP
mdefine_line|#define LEO_SS1_MAP            0x00803000
DECL|macro|LEO_LC_SS1_USR_MAP
mdefine_line|#define LEO_LC_SS1_USR_MAP     0x01003000
DECL|macro|LEO_LD_SS1_MAP
mdefine_line|#define LEO_LD_SS1_MAP         0x01004000
DECL|macro|LEO_UNK_MAP
mdefine_line|#define LEO_UNK_MAP            0x01005000
DECL|macro|LEO_LX_KRN_MAP
mdefine_line|#define LEO_LX_KRN_MAP         0x01006000
DECL|macro|LEO_LC_SS0_KRN_MAP
mdefine_line|#define LEO_LC_SS0_KRN_MAP     0x01007000
DECL|macro|LEO_LC_SS1_KRN_MAP
mdefine_line|#define LEO_LC_SS1_KRN_MAP     0x01008000
DECL|macro|LEO_LD_GBL_MAP
mdefine_line|#define LEO_LD_GBL_MAP         0x01009000
DECL|macro|LEO_UNK2_MAP
mdefine_line|#define LEO_UNK2_MAP           0x0100a000
macro_line|#endif /* __LINUX_FBIO_H */
eof
