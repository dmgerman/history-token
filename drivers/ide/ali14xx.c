multiline_comment|/*&n; *  Copyright (C) 1996  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; * ALI M14xx chipset EIDE controller&n; *&n; * Works for ALI M1439/1443/1445/1487/1489 chipsets.&n; *&n; * Adapted from code developed by derekn@vw.ece.cmu.edu.  -ml&n; * Derek&squot;s notes follow:&n; *&n; * I think the code should be pretty understandable,&n; * but I&squot;ll be happy to (try to) answer questions.&n; *&n; * The critical part is in the ali14xx_tune_drive function.  The init_registers&n; * function doesn&squot;t seem to be necessary, but the DOS driver does it, so&n; * I threw it in.&n; *&n; * I&squot;ve only tested this on my system, which only has one disk.  I posted&n; * it to comp.sys.linux.hardware, so maybe some other people will try it&n; * out.&n; *&n; * Derek Noonburg  (derekn@ece.cmu.edu)&n; * 95-sep-26&n; *&n; * Update 96-jul-13:&n; *&n; * I&squot;ve since upgraded to two disks and a CD-ROM, with no trouble, and&n; * I&squot;ve also heard from several others who have used it successfully.&n; * This driver appears to work with both the 1443/1445 and the 1487/1489&n; * chipsets.  I&squot;ve added support for PIO mode 4 for the 1487.  This&n; * seems to work just fine on the 1443 also, although I&squot;m not sure it&squot;s&n; * advertised as supporting mode 4.  (I&squot;ve been running a WDC AC21200 in&n; * mode 4 for a while now with no trouble.)  -Derek&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;timing.h&quot;
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
DECL|struct|reg_initializer
r_struct
id|reg_initializer
(brace
DECL|member|reg
DECL|member|data
id|u8
id|reg
comma
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|reg_initializer
id|init_data
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
multiline_comment|/* timing parameter registers for each drive */
r_static
r_struct
(brace
DECL|member|reg1
DECL|member|reg2
DECL|member|reg3
DECL|member|reg4
id|u8
id|reg1
comma
id|reg2
comma
id|reg3
comma
id|reg4
suffix:semicolon
DECL|variable|reg_tab
)brace
id|reg_tab
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
DECL|variable|base_port
r_static
r_int
id|base_port
suffix:semicolon
multiline_comment|/* base port address */
DECL|variable|reg_port
r_static
r_int
id|reg_port
suffix:semicolon
multiline_comment|/* port for register number */
DECL|variable|data_port
r_static
r_int
id|data_port
suffix:semicolon
multiline_comment|/* port for register data */
DECL|variable|reg_on
r_static
id|u8
id|reg_on
suffix:semicolon
multiline_comment|/* output to base port to access registers */
DECL|variable|reg_off
r_static
id|u8
id|reg_off
suffix:semicolon
multiline_comment|/* output to base port to close registers */
multiline_comment|/*&n; * Read a controller register.&n; */
DECL|function|in_reg
r_static
r_inline
id|u8
id|in_reg
c_func
(paren
id|u8
id|reg
)paren
(brace
id|outb_p
c_func
(paren
id|reg
comma
id|reg_port
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|data_port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a controller register.&n; */
DECL|function|out_reg
r_static
r_inline
r_void
id|out_reg
c_func
(paren
id|u8
id|data
comma
id|u8
id|reg
)paren
(brace
id|outb_p
c_func
(paren
id|reg
comma
id|reg_port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data
comma
id|data_port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set PIO mode for the specified drive.&n; * This function computes timing parameters&n; * and sets controller registers accordingly.&n; * It assumes IRQ&squot;s are disabled or at least that no other process will&n; * attempt to access the IDE registers concurrently.&n; */
DECL|function|ali14xx_tune_drive
r_static
r_void
id|ali14xx_tune_drive
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
r_int
id|drive_num
suffix:semicolon
r_int
id|time1
comma
id|time2
suffix:semicolon
id|u8
id|param1
comma
id|param2
comma
id|param3
comma
id|param4
suffix:semicolon
r_struct
id|ata_timing
op_star
id|t
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
suffix:semicolon
r_else
id|pio
op_assign
id|XFER_PIO_0
op_plus
id|min_t
c_func
(paren
id|u8
comma
id|pio
comma
l_int|4
)paren
suffix:semicolon
id|t
op_assign
id|ata_timing_data
c_func
(paren
id|pio
)paren
suffix:semicolon
multiline_comment|/* calculate timing, according to PIO mode */
id|time1
op_assign
id|t-&gt;cycle
suffix:semicolon
id|time2
op_assign
id|t-&gt;active
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
l_int|999999
)paren
op_div
l_int|1000000
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
l_int|999999
)paren
op_div
l_int|1000000
op_minus
id|param1
suffix:semicolon
r_if
c_cond
(paren
id|pio
OL
id|XFER_PIO_3
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
id|KERN_DEBUG
l_string|&quot;%s: PIO mode%d, t1=%dns, t2=%dns, cycles = %d+%d, %d+%d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
op_minus
id|XFER_PIO_0
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
id|drive_num
op_assign
(paren
id|drive-&gt;channel-&gt;index
op_lshift
l_int|1
)paren
op_plus
id|drive-&gt;select.b.unit
suffix:semicolon
id|outb_p
c_func
(paren
id|reg_on
comma
id|base_port
)paren
suffix:semicolon
id|out_reg
c_func
(paren
id|param1
comma
id|reg_tab
(braket
id|drive_num
)braket
dot
id|reg1
)paren
suffix:semicolon
id|out_reg
c_func
(paren
id|param2
comma
id|reg_tab
(braket
id|drive_num
)braket
dot
id|reg2
)paren
suffix:semicolon
id|out_reg
c_func
(paren
id|param3
comma
id|reg_tab
(braket
id|drive_num
)braket
dot
id|reg3
)paren
suffix:semicolon
id|out_reg
c_func
(paren
id|param4
comma
id|reg_tab
(braket
id|drive_num
)braket
dot
id|reg4
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|reg_off
comma
id|base_port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Auto-detect the IDE controller port.&n; */
DECL|function|find_port
r_static
r_int
id|__init
id|find_port
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
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
id|ALI_NUM_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|base_port
op_assign
id|ports
(braket
id|i
)braket
suffix:semicolon
id|reg_off
op_assign
id|inb
c_func
(paren
id|base_port
)paren
suffix:semicolon
r_for
c_loop
(paren
id|reg_on
op_assign
l_int|0x30
suffix:semicolon
id|reg_on
op_le
l_int|0x33
suffix:semicolon
id|reg_on
op_increment
)paren
(brace
id|outb_p
c_func
(paren
id|reg_on
comma
id|base_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|base_port
)paren
op_eq
id|reg_on
)paren
(brace
id|u8
id|t
suffix:semicolon
id|reg_port
op_assign
id|base_port
op_plus
l_int|4
suffix:semicolon
id|data_port
op_assign
id|base_port
op_plus
l_int|8
suffix:semicolon
id|t
op_assign
id|in_reg
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
id|reg_off
comma
id|base_port
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
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
id|reg_off
comma
id|base_port
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize controller registers with default values.&n; */
DECL|function|init_registers
r_static
r_int
id|__init
id|init_registers
c_func
(paren
r_void
)paren
(brace
r_struct
id|reg_initializer
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|t
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|reg_on
comma
id|base_port
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|init_data
suffix:semicolon
id|p-&gt;reg
op_ne
l_int|0
suffix:semicolon
op_increment
id|p
)paren
id|out_reg
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
id|reg_port
)paren
suffix:semicolon
id|t
op_assign
id|inb
c_func
(paren
id|reg_port
)paren
op_amp
l_int|0x01
suffix:semicolon
id|outb_p
c_func
(paren
id|reg_off
comma
id|base_port
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|function|init_ali14xx
r_void
id|__init
id|init_ali14xx
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* auto-detect IDE controller port */
r_if
c_cond
(paren
op_logical_neg
id|find_port
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ali14xx: not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ali14xx: base=%#03x, reg_on=%#02x&bslash;n&quot;
comma
id|base_port
comma
id|reg_on
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
id|unit
op_assign
id|ATA_PRIMARY
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|unit
op_assign
id|ATA_SECONDARY
suffix:semicolon
multiline_comment|/* initialize controller registers */
r_if
c_cond
(paren
op_logical_neg
id|init_registers
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ali14xx: Chip initialization failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
eof
