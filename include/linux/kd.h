macro_line|#ifndef _LINUX_KD_H
DECL|macro|_LINUX_KD_H
mdefine_line|#define _LINUX_KD_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* 0x4B is &squot;K&squot;, to avoid collision with termios and vt */
DECL|macro|GIO_FONT
mdefine_line|#define GIO_FONT&t;0x4B60&t;/* gets font in expanded form */
DECL|macro|PIO_FONT
mdefine_line|#define PIO_FONT&t;0x4B61&t;/* use font in expanded form */
DECL|macro|GIO_FONTX
mdefine_line|#define GIO_FONTX&t;0x4B6B&t;/* get font using struct consolefontdesc */
DECL|macro|PIO_FONTX
mdefine_line|#define PIO_FONTX&t;0x4B6C&t;/* set font using struct consolefontdesc */
DECL|struct|consolefontdesc
r_struct
id|consolefontdesc
(brace
DECL|member|charcount
r_int
r_int
id|charcount
suffix:semicolon
multiline_comment|/* characters in font (256 or 512) */
DECL|member|charheight
r_int
r_int
id|charheight
suffix:semicolon
multiline_comment|/* scan lines per character (1-32) */
DECL|member|chardata
r_char
op_star
id|chardata
suffix:semicolon
multiline_comment|/* font data in expanded form */
)brace
suffix:semicolon
DECL|macro|PIO_FONTRESET
mdefine_line|#define PIO_FONTRESET   0x4B6D&t;/* reset to default font */
DECL|macro|GIO_CMAP
mdefine_line|#define GIO_CMAP&t;0x4B70&t;/* gets colour palette on VGA+ */
DECL|macro|PIO_CMAP
mdefine_line|#define PIO_CMAP&t;0x4B71&t;/* sets colour palette on VGA+ */
DECL|macro|KIOCSOUND
mdefine_line|#define KIOCSOUND&t;0x4B2F&t;/* start sound generation (0 for off) */
DECL|macro|KDMKTONE
mdefine_line|#define KDMKTONE&t;0x4B30&t;/* generate tone */
DECL|macro|KDGETLED
mdefine_line|#define KDGETLED&t;0x4B31&t;/* return current led state */
DECL|macro|KDSETLED
mdefine_line|#define KDSETLED&t;0x4B32&t;/* set led state [lights, not flags] */
DECL|macro|LED_SCR
mdefine_line|#define &t;LED_SCR&t;&t;0x01&t;/* scroll lock led */
DECL|macro|LED_NUM
mdefine_line|#define &t;LED_NUM&t;&t;0x02&t;/* num lock led */
DECL|macro|LED_CAP
mdefine_line|#define &t;LED_CAP&t;&t;0x04&t;/* caps lock led */
DECL|macro|KDGKBTYPE
mdefine_line|#define KDGKBTYPE&t;0x4B33&t;/* get keyboard type */
DECL|macro|KB_84
mdefine_line|#define &t;KB_84&t;&t;0x01
DECL|macro|KB_101
mdefine_line|#define &t;KB_101&t;&t;0x02 &t;/* this is what we always answer */
DECL|macro|KB_OTHER
mdefine_line|#define &t;KB_OTHER&t;0x03
DECL|macro|KDADDIO
mdefine_line|#define KDADDIO&t;&t;0x4B34&t;/* add i/o port as valid */
DECL|macro|KDDELIO
mdefine_line|#define KDDELIO&t;&t;0x4B35&t;/* del i/o port as valid */
DECL|macro|KDENABIO
mdefine_line|#define KDENABIO&t;0x4B36&t;/* enable i/o to video board */
DECL|macro|KDDISABIO
mdefine_line|#define KDDISABIO&t;0x4B37&t;/* disable i/o to video board */
DECL|macro|KDSETMODE
mdefine_line|#define KDSETMODE&t;0x4B3A&t;/* set text/graphics mode */
DECL|macro|KD_TEXT
mdefine_line|#define&t;&t;KD_TEXT&t;&t;0x00
DECL|macro|KD_GRAPHICS
mdefine_line|#define&t;&t;KD_GRAPHICS&t;0x01
DECL|macro|KD_TEXT0
mdefine_line|#define&t;&t;KD_TEXT0&t;0x02&t;/* obsolete */
DECL|macro|KD_TEXT1
mdefine_line|#define&t;&t;KD_TEXT1&t;0x03&t;/* obsolete */
DECL|macro|KDGETMODE
mdefine_line|#define KDGETMODE&t;0x4B3B&t;/* get current mode */
DECL|macro|KDMAPDISP
mdefine_line|#define KDMAPDISP&t;0x4B3C&t;/* map display into address space */
DECL|macro|KDUNMAPDISP
mdefine_line|#define KDUNMAPDISP&t;0x4B3D&t;/* unmap display from address space */
DECL|typedef|scrnmap_t
r_typedef
r_char
id|scrnmap_t
suffix:semicolon
DECL|macro|E_TABSZ
mdefine_line|#define&t;&t;E_TABSZ&t;&t;256
DECL|macro|GIO_SCRNMAP
mdefine_line|#define GIO_SCRNMAP&t;0x4B40&t;/* get screen mapping from kernel */
DECL|macro|PIO_SCRNMAP
mdefine_line|#define PIO_SCRNMAP&t;0x4B41&t;/* put screen mapping table in kernel */
DECL|macro|GIO_UNISCRNMAP
mdefine_line|#define GIO_UNISCRNMAP  0x4B69&t;/* get full Unicode screen mapping */
DECL|macro|PIO_UNISCRNMAP
mdefine_line|#define PIO_UNISCRNMAP  0x4B6A  /* set full Unicode screen mapping */
DECL|macro|GIO_UNIMAP
mdefine_line|#define GIO_UNIMAP&t;0x4B66&t;/* get unicode-to-font mapping from kernel */
DECL|struct|unipair
r_struct
id|unipair
(brace
DECL|member|unicode
r_int
r_int
id|unicode
suffix:semicolon
DECL|member|fontpos
r_int
r_int
id|fontpos
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|unimapdesc
r_struct
id|unimapdesc
(brace
DECL|member|entry_ct
r_int
r_int
id|entry_ct
suffix:semicolon
DECL|member|entries
r_struct
id|unipair
op_star
id|entries
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PIO_UNIMAP
mdefine_line|#define PIO_UNIMAP&t;0x4B67&t;/* put unicode-to-font mapping in kernel */
DECL|macro|PIO_UNIMAPCLR
mdefine_line|#define PIO_UNIMAPCLR&t;0x4B68&t;/* clear table, possibly advise hash algorithm */
DECL|struct|unimapinit
r_struct
id|unimapinit
(brace
DECL|member|advised_hashsize
r_int
r_int
id|advised_hashsize
suffix:semicolon
multiline_comment|/* 0 if no opinion */
DECL|member|advised_hashstep
r_int
r_int
id|advised_hashstep
suffix:semicolon
multiline_comment|/* 0 if no opinion */
DECL|member|advised_hashlevel
r_int
r_int
id|advised_hashlevel
suffix:semicolon
multiline_comment|/* 0 if no opinion */
)brace
suffix:semicolon
DECL|macro|UNI_DIRECT_BASE
mdefine_line|#define UNI_DIRECT_BASE 0xF000&t;/* start of Direct Font Region */
DECL|macro|UNI_DIRECT_MASK
mdefine_line|#define UNI_DIRECT_MASK 0x01FF&t;/* Direct Font Region bitmask */
DECL|macro|K_RAW
mdefine_line|#define&t;&t;K_RAW&t;&t;0x00
DECL|macro|K_XLATE
mdefine_line|#define&t;&t;K_XLATE&t;&t;0x01
DECL|macro|K_MEDIUMRAW
mdefine_line|#define&t;&t;K_MEDIUMRAW&t;0x02
DECL|macro|K_UNICODE
mdefine_line|#define&t;&t;K_UNICODE&t;0x03
DECL|macro|KDGKBMODE
mdefine_line|#define KDGKBMODE&t;0x4B44&t;/* gets current keyboard mode */
DECL|macro|KDSKBMODE
mdefine_line|#define KDSKBMODE&t;0x4B45&t;/* sets current keyboard mode */
DECL|macro|K_METABIT
mdefine_line|#define&t;&t;K_METABIT&t;0x03
DECL|macro|K_ESCPREFIX
mdefine_line|#define&t;&t;K_ESCPREFIX&t;0x04
DECL|macro|KDGKBMETA
mdefine_line|#define KDGKBMETA&t;0x4B62&t;/* gets meta key handling mode */
DECL|macro|KDSKBMETA
mdefine_line|#define KDSKBMETA&t;0x4B63&t;/* sets meta key handling mode */
DECL|macro|K_SCROLLLOCK
mdefine_line|#define&t;&t;K_SCROLLLOCK&t;0x01
DECL|macro|K_NUMLOCK
mdefine_line|#define&t;&t;K_NUMLOCK&t;0x02
DECL|macro|K_CAPSLOCK
mdefine_line|#define&t;&t;K_CAPSLOCK&t;0x04
DECL|macro|KDGKBLED
mdefine_line|#define&t;KDGKBLED&t;0x4B64&t;/* get led flags (not lights) */
DECL|macro|KDSKBLED
mdefine_line|#define&t;KDSKBLED&t;0x4B65&t;/* set led flags (not lights) */
DECL|struct|kbentry
r_struct
id|kbentry
(brace
DECL|member|kb_table
r_int
r_char
id|kb_table
suffix:semicolon
DECL|member|kb_index
r_int
r_char
id|kb_index
suffix:semicolon
DECL|member|kb_value
r_int
r_int
id|kb_value
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|K_NORMTAB
mdefine_line|#define&t;&t;K_NORMTAB&t;0x00
DECL|macro|K_SHIFTTAB
mdefine_line|#define&t;&t;K_SHIFTTAB&t;0x01
DECL|macro|K_ALTTAB
mdefine_line|#define&t;&t;K_ALTTAB&t;0x02
DECL|macro|K_ALTSHIFTTAB
mdefine_line|#define&t;&t;K_ALTSHIFTTAB&t;0x03
DECL|macro|KDGKBENT
mdefine_line|#define KDGKBENT&t;0x4B46&t;/* gets one entry in translation table */
DECL|macro|KDSKBENT
mdefine_line|#define KDSKBENT&t;0x4B47&t;/* sets one entry in translation table */
DECL|struct|kbsentry
r_struct
id|kbsentry
(brace
DECL|member|kb_func
r_int
r_char
id|kb_func
suffix:semicolon
DECL|member|kb_string
r_int
r_char
id|kb_string
(braket
l_int|512
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|KDGKBSENT
mdefine_line|#define KDGKBSENT&t;0x4B48&t;/* gets one function key string entry */
DECL|macro|KDSKBSENT
mdefine_line|#define KDSKBSENT&t;0x4B49&t;/* sets one function key string entry */
DECL|struct|kbdiacr
r_struct
id|kbdiacr
(brace
DECL|member|diacr
DECL|member|base
DECL|member|result
r_int
r_char
id|diacr
comma
id|base
comma
id|result
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kbdiacrs
r_struct
id|kbdiacrs
(brace
DECL|member|kb_cnt
r_int
r_int
id|kb_cnt
suffix:semicolon
multiline_comment|/* number of entries in following array */
DECL|member|kbdiacr
r_struct
id|kbdiacr
id|kbdiacr
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* MAX_DIACR from keyboard.h */
)brace
suffix:semicolon
DECL|macro|KDGKBDIACR
mdefine_line|#define KDGKBDIACR      0x4B4A  /* read kernel accent table */
DECL|macro|KDSKBDIACR
mdefine_line|#define KDSKBDIACR      0x4B4B  /* write kernel accent table */
DECL|struct|kbkeycode
r_struct
id|kbkeycode
(brace
DECL|member|scancode
DECL|member|keycode
r_int
r_int
id|scancode
comma
id|keycode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|KDGETKEYCODE
mdefine_line|#define KDGETKEYCODE&t;0x4B4C&t;/* read kernel keycode table entry */
DECL|macro|KDSETKEYCODE
mdefine_line|#define KDSETKEYCODE&t;0x4B4D&t;/* write kernel keycode table entry */
DECL|macro|KDSIGACCEPT
mdefine_line|#define KDSIGACCEPT&t;0x4B4E&t;/* accept kbd generated signals */
DECL|struct|kbd_repeat
r_struct
id|kbd_repeat
(brace
DECL|member|delay
r_int
id|delay
suffix:semicolon
multiline_comment|/* in msec; &lt;= 0: don&squot;t change */
DECL|member|rate
r_int
id|rate
suffix:semicolon
multiline_comment|/* in msec; &lt;= 0: don&squot;t change */
)brace
suffix:semicolon
DECL|macro|KDKBDREP
mdefine_line|#define KDKBDREP        0x4B52  /* set keyboard delay/repeat rate;&n;&t;&t;&t;&t; * actually used values are returned */
DECL|macro|KDFONTOP
mdefine_line|#define KDFONTOP&t;0x4B72&t;/* font operations */
DECL|struct|console_font_op
r_struct
id|console_font_op
(brace
DECL|member|op
r_int
r_int
id|op
suffix:semicolon
multiline_comment|/* operation code KD_FONT_OP_* */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* KD_FONT_FLAG_* */
DECL|member|width
DECL|member|height
r_int
r_int
id|width
comma
id|height
suffix:semicolon
multiline_comment|/* font size */
DECL|member|charcount
r_int
r_int
id|charcount
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* font data with height fixed to 32 */
)brace
suffix:semicolon
DECL|macro|KD_FONT_OP_SET
mdefine_line|#define KD_FONT_OP_SET&t;&t;0&t;/* Set font */
DECL|macro|KD_FONT_OP_GET
mdefine_line|#define KD_FONT_OP_GET&t;&t;1&t;/* Get font */
DECL|macro|KD_FONT_OP_SET_DEFAULT
mdefine_line|#define KD_FONT_OP_SET_DEFAULT&t;2&t;/* Set font to default, data points to name / NULL */
DECL|macro|KD_FONT_OP_COPY
mdefine_line|#define KD_FONT_OP_COPY&t;&t;3&t;/* Copy from another console */
DECL|macro|KD_FONT_FLAG_DONT_RECALC
mdefine_line|#define KD_FONT_FLAG_DONT_RECALC &t;1&t;/* Don&squot;t recalculate hw charcell size [compat] */
macro_line|#ifdef __KERNEL__
DECL|macro|KD_FONT_FLAG_OLD
mdefine_line|#define KD_FONT_FLAG_OLD&t;&t;0x80000000&t;/* Invoked via old interface [compat] */
macro_line|#endif
multiline_comment|/* note: 0x4B00-0x4B4E all have had a value at some time;&n;   don&squot;t reuse for the time being */
multiline_comment|/* note: 0x4B60-0x4B6D, 0x4B70-0x4B72 used above */
macro_line|#endif /* _LINUX_KD_H */
eof
