multiline_comment|/*&n; *  linux/drivers/ide/ali14xx.c&t;&t;Version 0.03&t;Feb 09, 1996&n; *&n; *  Copyright (C) 1996  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; * ALI M14xx chipset EIDE controller&n; *&n; * Works for ALI M1439/1443/1445/1487/1489 chipsets.&n; *&n; * Adapted from code developed by derekn@vw.ece.cmu.edu.  -ml&n; * Derek&squot;s notes follow:&n; *&n; * I think the code should be pretty understandable,&n; * but I&squot;ll be happy to (try to) answer questions.&n; *&n; * The critical part is in the setupDrive function.  The initRegisters&n; * function doesn&squot;t seem to be necessary, but the DOS driver does it, so&n; * I threw it in.&n; *&n; * I&squot;ve only tested this on my system, which only has one disk.  I posted&n; * it to comp.sys.linux.hardware, so maybe some other people will try it&n; * out.&n; *&n; * Derek Noonburg  (derekn@ece.cmu.edu)&n; * 95-sep-26&n; *&n; * Update 96-jul-13:&n; *&n; * I&squot;ve since upgraded to two disks and a CD-ROM, with no trouble, and&n; * I&squot;ve also heard from several others who have used it successfully.&n; * This driver appears to work with both the 1443/1445 and the 1487/1489&n; * chipsets.  I&squot;ve added support for PIO mode 4 for the 1487.  This&n; * seems to work just fine on the 1443 also, although I&squot;m not sure it&squot;s&n; * advertised as supporting mode 4.  (I&squot;ve been running a WDC AC21200 in&n; * mode 4 for a while now with no trouble.)  -Derek&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO           /* most systems can safely undef this */
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
macro_line|#include &quot;ide_modes.h&quot;
multiline_comment|/* port addresses for auto-detection */
DECL|macro|ALI_NUM_PORTS
mdefine_line|#define ALI_NUM_PORTS 4
DECL|variable|__initdata
r_static
r_int
id|ports
(braket
id|ALI_NUM_PORTS
)braket
id|__initdata
op_assign
(brace
l_int|0x074
comma
l_int|0x0f4
comma
l_int|0x034
comma
l_int|0x0e4
)brace
suffix:semicolon
multiline_comment|/* register initialization data */
DECL|member|reg
DECL|member|data
DECL|typedef|RegInitializer
r_typedef
r_struct
(brace
id|byte
id|reg
comma
id|data
suffix:semicolon
)brace
id|RegInitializer
suffix:semicolon
DECL|variable|__initdata
r_static
id|RegInitializer
id|initData
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0x01
comma
l_int|0x0f
)brace
comma
(brace
l_int|0x02
comma
l_int|0x00
)brace
comma
(brace
l_int|0x03
comma
l_int|0x00
)brace
comma
(brace
l_int|0x04
comma
l_int|0x00
)brace
comma
(brace
l_int|0x05
comma
l_int|0x00
)brace
comma
(brace
l_int|0x06
comma
l_int|0x00
)brace
comma
(brace
l_int|0x07
comma
l_int|0x2b
)brace
comma
(brace
l_int|0x0a
comma
l_int|0x0f
)brace
comma
(brace
l_int|0x25
comma
l_int|0x00
)brace
comma
(brace
l_int|0x26
comma
l_int|0x00
)brace
comma
(brace
l_int|0x27
comma
l_int|0x00
)brace
comma
(brace
l_int|0x28
comma
l_int|0x00
)brace
comma
(brace
l_int|0x29
comma
l_int|0x00
)brace
comma
(brace
l_int|0x2a
comma
l_int|0x00
)brace
comma
(brace
l_int|0x2f
comma
l_int|0x00
)brace
comma
(brace
l_int|0x2b
comma
l_int|0x00
)brace
comma
(brace
l_int|0x2c
comma
l_int|0x00
)brace
comma
(brace
l_int|0x2d
comma
l_int|0x00
)brace
comma
(brace
l_int|0x2e
comma
l_int|0x00
)brace
comma
(brace
l_int|0x30
comma
l_int|0x00
)brace
comma
(brace
l_int|0x31
comma
l_int|0x00
)brace
comma
(brace
l_int|0x32
comma
l_int|0x00
)brace
comma
(brace
l_int|0x33
comma
l_int|0x00
)brace
comma
(brace
l_int|0x34
comma
l_int|0xff
)brace
comma
(brace
l_int|0x35
comma
l_int|0x03
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
)brace
)brace
suffix:semicolon
DECL|macro|ALI_MAX_PIO
mdefine_line|#define ALI_MAX_PIO 4
multiline_comment|/* timing parameter registers for each drive */
DECL|member|reg1
DECL|member|reg2
DECL|member|reg3
DECL|member|reg4
DECL|variable|regTab
r_static
r_struct
(brace
id|byte
id|reg1
comma
id|reg2
comma
id|reg3
comma
id|reg4
suffix:semicolon
)brace
id|regTab
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x03
comma
l_int|0x26
comma
l_int|0x04
comma
l_int|0x27
)brace
comma
multiline_comment|/* drive 0 */
(brace
l_int|0x05
comma
l_int|0x28
comma
l_int|0x06
comma
l_int|0x29
)brace
comma
multiline_comment|/* drive 1 */
(brace
l_int|0x2b
comma
l_int|0x30
comma
l_int|0x2c
comma
l_int|0x31
)brace
comma
multiline_comment|/* drive 2 */
(brace
l_int|0x2d
comma
l_int|0x32
comma
l_int|0x2e
comma
l_int|0x33
)brace
comma
multiline_comment|/* drive 3 */
)brace
suffix:semicolon
DECL|variable|basePort
r_static
r_int
id|basePort
suffix:semicolon
multiline_comment|/* base port address */
DECL|variable|regPort
r_static
r_int
id|regPort
suffix:semicolon
multiline_comment|/* port for register number */
DECL|variable|dataPort
r_static
r_int
id|dataPort
suffix:semicolon
multiline_comment|/* port for register data */
DECL|variable|regOn
r_static
id|byte
id|regOn
suffix:semicolon
multiline_comment|/* output to base port to access registers */
DECL|variable|regOff
r_static
id|byte
id|regOff
suffix:semicolon
multiline_comment|/* output to base port to close registers */
multiline_comment|/*------------------------------------------------------------------------*/
multiline_comment|/*&n; * Read a controller register.&n; */
DECL|function|inReg
r_static
r_inline
id|byte
id|inReg
(paren
id|byte
id|reg
)paren
(brace
id|outb_p
c_func
(paren
id|reg
comma
id|regPort
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|dataPort
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a controller register.&n; */
DECL|function|outReg
r_static
r_void
id|outReg
(paren
id|byte
id|data
comma
id|byte
id|reg
)paren
(brace
id|outb_p
c_func
(paren
id|reg
comma
id|regPort
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data
comma
id|dataPort
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set PIO mode for the specified drive.&n; * This function computes timing parameters&n; * and sets controller registers accordingly.&n; */
DECL|function|ali14xx_tune_drive
r_static
r_void
id|ali14xx_tune_drive
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
id|driveNum
suffix:semicolon
r_int
id|time1
comma
id|time2
suffix:semicolon
id|byte
id|param1
comma
id|param2
comma
id|param3
comma
id|param4
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|ide_pio_data_t
id|d
suffix:semicolon
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
id|ALI_MAX_PIO
comma
op_amp
id|d
)paren
suffix:semicolon
multiline_comment|/* calculate timing, according to PIO mode */
id|time1
op_assign
id|d.cycle_time
suffix:semicolon
id|time2
op_assign
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|active_time
suffix:semicolon
id|param3
op_assign
id|param1
op_assign
(paren
id|time2
op_star
id|system_bus_speed
op_plus
l_int|999
)paren
op_div
l_int|1000
suffix:semicolon
id|param4
op_assign
id|param2
op_assign
(paren
id|time1
op_star
id|system_bus_speed
op_plus
l_int|999
)paren
op_div
l_int|1000
op_minus
id|param1
suffix:semicolon
r_if
c_cond
(paren
id|pio
OL
l_int|3
)paren
(brace
id|param3
op_add_assign
l_int|8
suffix:semicolon
id|param4
op_add_assign
l_int|8
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: PIO mode%d, t1=%dns, t2=%dns, cycles = %d+%d, %d+%d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
comma
id|time1
comma
id|time2
comma
id|param1
comma
id|param2
comma
id|param3
comma
id|param4
)paren
suffix:semicolon
multiline_comment|/* stuff timing parameters into controller registers */
id|driveNum
op_assign
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|index
op_lshift
l_int|1
)paren
op_plus
id|drive-&gt;select.b.unit
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
id|outb_p
c_func
(paren
id|regOn
comma
id|basePort
)paren
suffix:semicolon
id|outReg
c_func
(paren
id|param1
comma
id|regTab
(braket
id|driveNum
)braket
dot
id|reg1
)paren
suffix:semicolon
id|outReg
c_func
(paren
id|param2
comma
id|regTab
(braket
id|driveNum
)braket
dot
id|reg2
)paren
suffix:semicolon
id|outReg
c_func
(paren
id|param3
comma
id|regTab
(braket
id|driveNum
)braket
dot
id|reg3
)paren
suffix:semicolon
id|outReg
c_func
(paren
id|param4
comma
id|regTab
(braket
id|driveNum
)braket
dot
id|reg4
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|regOff
comma
id|basePort
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
)brace
multiline_comment|/*&n; * Auto-detect the IDE controller port.&n; */
DECL|function|findPort
r_static
r_int
id|__init
id|findPort
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|byte
id|t
suffix:semicolon
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ALI_NUM_PORTS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|basePort
op_assign
id|ports
(braket
id|i
)braket
suffix:semicolon
id|regOff
op_assign
id|inb
c_func
(paren
id|basePort
)paren
suffix:semicolon
r_for
c_loop
(paren
id|regOn
op_assign
l_int|0x30
suffix:semicolon
id|regOn
op_le
l_int|0x33
suffix:semicolon
op_increment
id|regOn
)paren
(brace
id|outb_p
c_func
(paren
id|regOn
comma
id|basePort
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|basePort
)paren
op_eq
id|regOn
)paren
(brace
id|regPort
op_assign
id|basePort
op_plus
l_int|4
suffix:semicolon
id|dataPort
op_assign
id|basePort
op_plus
l_int|8
suffix:semicolon
id|t
op_assign
id|inReg
c_func
(paren
l_int|0
)paren
op_amp
l_int|0xf0
suffix:semicolon
id|outb_p
c_func
(paren
id|regOff
comma
id|basePort
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_if
c_cond
(paren
id|t
op_ne
l_int|0x50
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* success */
)brace
)brace
id|outb_p
c_func
(paren
id|regOff
comma
id|basePort
)paren
suffix:semicolon
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize controller registers with default values.&n; */
DECL|function|initRegisters
r_static
r_int
id|__init
id|initRegisters
(paren
r_void
)paren
(brace
id|RegInitializer
op_star
id|p
suffix:semicolon
id|byte
id|t
suffix:semicolon
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
id|outb_p
c_func
(paren
id|regOn
comma
id|basePort
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|initData
suffix:semicolon
id|p-&gt;reg
op_ne
l_int|0
suffix:semicolon
op_increment
id|p
)paren
id|outReg
c_func
(paren
id|p-&gt;data
comma
id|p-&gt;reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x01
comma
id|regPort
)paren
suffix:semicolon
id|t
op_assign
id|inb
c_func
(paren
id|regPort
)paren
op_amp
l_int|0x01
suffix:semicolon
id|outb_p
c_func
(paren
id|regOff
comma
id|basePort
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_return
id|t
suffix:semicolon
)brace
DECL|function|init_ali14xx
r_void
id|__init
id|init_ali14xx
(paren
r_void
)paren
(brace
multiline_comment|/* auto-detect IDE controller port */
r_if
c_cond
(paren
op_logical_neg
id|findPort
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nali14xx: not found&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nali14xx: base= 0x%03x, regOn = 0x%02x&quot;
comma
id|basePort
comma
id|regOn
)paren
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|chipset
op_assign
id|ide_ali14xx
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|chipset
op_assign
id|ide_ali14xx
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|tuneproc
op_assign
op_amp
id|ali14xx_tune_drive
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|tuneproc
op_assign
op_amp
id|ali14xx_tune_drive
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
multiline_comment|/* initialize controller registers */
r_if
c_cond
(paren
op_logical_neg
id|initRegisters
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nali14xx: Chip initialization failed&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
eof
