multiline_comment|/*&n; *  linux/drivers/ide/umc8672.c&t;&t;Version 0.05&t;Jul 31, 1996&n; *&n; *  Copyright (C) 1995-1996  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *  Principal Author/Maintainer:  PODIEN@hml2.atlas.de (Wolfram Podien)&n; *&n; *  This file provides support for the advanced features&n; *  of the UMC 8672 IDE interface.&n; *&n; *  Version 0.01&t;Initial version, hacked out of ide.c,&n; *&t;&t;&t;and #include&squot;d rather than compiled separately.&n; *&t;&t;&t;This will get cleaned up in a subsequent release.&n; *&n; *  Version 0.02&t;now configs/compiles separate from ide.c  -ml&n; *  Version 0.03&t;enhanced auto-tune, fix display bug&n; *  Version 0.05&t;replace sti() with restore_flags()  -ml&n; *&t;&t;&t;add detection of possible race condition  -ml&n; */
multiline_comment|/*&n; * VLB Controller Support from &n; * Wolfram Podien&n; * Rohoefe 3&n; * D28832 Achim&n; * Germany&n; *&n; * To enable UMC8672 support there must a lilo line like&n; * append=&quot;ide0=umc8672&quot;...&n; * To set the speed according to the abilities of the hardware there must be a&n; * line like&n; * #define UMC_DRIVE0 11&n; * in the beginning of the driver, which sets the speed of drive 0 to 11 (there&n; * are some lines present). 0 - 11 are allowed speed values. These values are&n; * the results from the DOS speed test program supplied from UMC. 11 is the &n; * highest speed (about PIO mode 3)&n; */
DECL|macro|REALLY_SLOW_IO
mdefine_line|#define REALLY_SLOW_IO&t;&t;/* some systems can safely undef this */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ata-timing.h&quot;
multiline_comment|/*&n; * Default speeds.  These can be changed with &quot;auto-tune&quot; and/or hdparm.&n; */
DECL|macro|UMC_DRIVE0
mdefine_line|#define UMC_DRIVE0      1              /* DOS measured drive speeds */
DECL|macro|UMC_DRIVE1
mdefine_line|#define UMC_DRIVE1      1              /* 0 to 11 allowed */
DECL|macro|UMC_DRIVE2
mdefine_line|#define UMC_DRIVE2      1              /* 11 = Fastest Speed */
DECL|macro|UMC_DRIVE3
mdefine_line|#define UMC_DRIVE3      1              /* In case of crash reduce speed */
DECL|variable|current_speeds
r_static
id|byte
id|current_speeds
(braket
l_int|4
)braket
op_assign
(brace
id|UMC_DRIVE0
comma
id|UMC_DRIVE1
comma
id|UMC_DRIVE2
comma
id|UMC_DRIVE3
)brace
suffix:semicolon
DECL|variable|pio_to_umc
r_static
r_const
id|byte
id|pio_to_umc
(braket
l_int|5
)braket
op_assign
(brace
l_int|0
comma
l_int|3
comma
l_int|7
comma
l_int|10
comma
l_int|11
)brace
suffix:semicolon
multiline_comment|/* rough guesses */
multiline_comment|/*       0    1    2    3    4    5    6    7    8    9    10   11      */
DECL|variable|speedtab
r_static
r_const
id|byte
id|speedtab
(braket
l_int|3
)braket
(braket
l_int|12
)braket
op_assign
(brace
(brace
l_int|0xf
comma
l_int|0xb
comma
l_int|0x2
comma
l_int|0x2
comma
l_int|0x2
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
)brace
comma
(brace
l_int|0x3
comma
l_int|0x2
comma
l_int|0x2
comma
l_int|0x2
comma
l_int|0x2
comma
l_int|0x2
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
comma
l_int|0x1
)brace
comma
(brace
l_int|0xff
comma
l_int|0xcb
comma
l_int|0xc0
comma
l_int|0x58
comma
l_int|0x36
comma
l_int|0x33
comma
l_int|0x23
comma
l_int|0x22
comma
l_int|0x21
comma
l_int|0x11
comma
l_int|0x10
comma
l_int|0x0
)brace
)brace
suffix:semicolon
DECL|function|out_umc
r_static
r_void
id|out_umc
(paren
r_char
id|port
comma
r_char
id|wert
)paren
(brace
id|outb_p
(paren
id|port
comma
l_int|0x108
)paren
suffix:semicolon
id|outb_p
(paren
id|wert
comma
l_int|0x109
)paren
suffix:semicolon
)brace
DECL|function|in_umc
r_static
r_inline
id|byte
id|in_umc
(paren
r_char
id|port
)paren
(brace
id|outb_p
(paren
id|port
comma
l_int|0x108
)paren
suffix:semicolon
r_return
id|inb_p
(paren
l_int|0x109
)paren
suffix:semicolon
)brace
DECL|function|umc_set_speeds
r_static
r_void
id|umc_set_speeds
(paren
id|byte
id|speeds
(braket
)braket
)paren
(brace
r_int
id|i
comma
id|tmp
suffix:semicolon
id|outb_p
(paren
l_int|0x5A
comma
l_int|0x108
)paren
suffix:semicolon
multiline_comment|/* enable umc */
id|out_umc
(paren
l_int|0xd7
comma
(paren
id|speedtab
(braket
l_int|0
)braket
(braket
id|speeds
(braket
l_int|2
)braket
)braket
op_or
(paren
id|speedtab
(braket
l_int|0
)braket
(braket
id|speeds
(braket
l_int|3
)braket
)braket
op_lshift
l_int|4
)paren
)paren
)paren
suffix:semicolon
id|out_umc
(paren
l_int|0xd6
comma
(paren
id|speedtab
(braket
l_int|0
)braket
(braket
id|speeds
(braket
l_int|0
)braket
)braket
op_or
(paren
id|speedtab
(braket
l_int|0
)braket
(braket
id|speeds
(braket
l_int|1
)braket
)braket
op_lshift
l_int|4
)paren
)paren
)paren
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|tmp
op_assign
(paren
id|tmp
op_lshift
l_int|2
)paren
op_or
id|speedtab
(braket
l_int|1
)braket
(braket
id|speeds
(braket
id|i
)braket
)braket
suffix:semicolon
)brace
id|out_umc
(paren
l_int|0xdc
comma
id|tmp
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|out_umc
(paren
l_int|0xd0
op_plus
id|i
comma
id|speedtab
(braket
l_int|2
)braket
(braket
id|speeds
(braket
id|i
)braket
)braket
)paren
suffix:semicolon
id|out_umc
(paren
l_int|0xd8
op_plus
id|i
comma
id|speedtab
(braket
l_int|2
)braket
(braket
id|speeds
(braket
id|i
)braket
)braket
)paren
suffix:semicolon
)brace
id|outb_p
(paren
l_int|0xa5
comma
l_int|0x108
)paren
suffix:semicolon
multiline_comment|/* disable umc */
id|printk
(paren
l_string|&quot;umc8672: drive speeds [0 to 11]: %d %d %d %d&bslash;n&quot;
comma
id|speeds
(braket
l_int|0
)braket
comma
id|speeds
(braket
l_int|1
)braket
comma
id|speeds
(braket
l_int|2
)braket
comma
id|speeds
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
DECL|function|tune_umc
r_static
r_void
id|tune_umc
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|ide_hwgroup_t
op_star
id|hwgroup
op_assign
id|ide_hwifs
(braket
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|index
op_xor
l_int|1
)braket
dot
id|hwgroup
suffix:semicolon
r_if
c_cond
(paren
id|pio
op_eq
l_int|255
)paren
id|pio
op_assign
id|ata_timing_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
)paren
op_minus
id|XFER_PIO_0
suffix:semicolon
r_else
id|pio
op_assign
id|min_t
c_func
(paren
id|byte
comma
id|pio
comma
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: setting umc8672 to PIO mode%d (speed %d)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
comma
id|pio_to_umc
(braket
id|pio
)braket
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
r_if
c_cond
(paren
id|hwgroup
op_logical_and
id|hwgroup-&gt;handler
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;umc8672: other interface is busy: exiting tune_umc()&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|current_speeds
(braket
id|drive-&gt;name
(braket
l_int|2
)braket
op_minus
l_char|&squot;a&squot;
)braket
op_assign
id|pio_to_umc
(braket
id|pio
)braket
suffix:semicolon
id|umc_set_speeds
(paren
id|current_speeds
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
)brace
DECL|function|init_umc8672
r_void
id|__init
id|init_umc8672
(paren
r_void
)paren
multiline_comment|/* called from ide.c */
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_if
c_cond
(paren
id|check_region
c_func
(paren
l_int|0x108
comma
l_int|2
)paren
)paren
(brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;numc8672: PORTS 0x108-0x109 ALREADY IN USE&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|outb_p
(paren
l_int|0x5A
comma
l_int|0x108
)paren
suffix:semicolon
multiline_comment|/* enable umc */
r_if
c_cond
(paren
id|in_umc
(paren
l_int|0xd5
)paren
op_ne
l_int|0xa0
)paren
(brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|printk
(paren
l_string|&quot;umc8672: not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|outb_p
(paren
l_int|0xa5
comma
l_int|0x108
)paren
suffix:semicolon
multiline_comment|/* disable umc */
id|umc_set_speeds
(paren
id|current_speeds
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|request_region
c_func
(paren
l_int|0x108
comma
l_int|2
comma
l_string|&quot;umc8672&quot;
)paren
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|chipset
op_assign
id|ide_umc8672
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|chipset
op_assign
id|ide_umc8672
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|tuneproc
op_assign
op_amp
id|tune_umc
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|tuneproc
op_assign
op_amp
id|tune_umc
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|mate
op_assign
op_amp
id|ide_hwifs
(braket
l_int|1
)braket
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|mate
op_assign
op_amp
id|ide_hwifs
(braket
l_int|0
)braket
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|channel
op_assign
l_int|1
suffix:semicolon
)brace
eof
