multiline_comment|/*&n; *  linux/drivers/ide/legacy/qd65xx.c&t;&t;Version 0.07&t;Sep 30, 2001&n; *&n; *  Copyright (C) 1996-2001  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *  Version 0.03&t;Cleaned auto-tune, added probe&n; *  Version 0.04&t;Added second channel tuning&n; *  Version 0.05&t;Enhanced tuning ; added qd6500 support&n; *  Version 0.06&t;Added dos driver&squot;s list&n; *  Version 0.07&t;Second channel bug fix &n; *&n; * QDI QD6500/QD6580 EIDE controller fast support&n; *&n; * Please set local bus speed using kernel parameter idebus&n; * &t;for example, &quot;idebus=33&quot; stands for 33Mhz VLbus&n; * To activate controller support, use &quot;ide0=qd65xx&quot;&n; * To enable tuning, use &quot;ide0=autotune&quot;&n; * To enable second channel tuning (qd6580 only), use &quot;ide1=autotune&quot;&n; */
multiline_comment|/*&n; * Rewritten from the work of Colten Edwards &lt;pje120@cs.usask.ca&gt; by&n; * Samuel Thibault &lt;samuel.thibault@fnac.net&gt;&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;qd65xx.h&quot;
multiline_comment|/*&n; * I/O ports are 0x30-0x31 (and 0x32-0x33 for qd6580)&n; *            or 0xb0-0xb1 (and 0xb2-0xb3 for qd6580)&n; *&t;-- qd6500 is a single IDE interface&n; *&t;-- qd6580 is a dual IDE interface&n; *&n; * More research on qd6580 being done by willmore@cig.mot.com (David)&n; * More Information given by Petr Soucek (petr@ryston.cz)&n; * http://www.ryston.cz/petr/vlb&n; */
multiline_comment|/*&n; * base: Timer1&n; *&n; *&n; * base+0x01: Config (R/O)&n; *&n; * bit 0: ide baseport: 1 = 0x1f0 ; 0 = 0x170 (only useful for qd6500)&n; * bit 1: qd65xx baseport: 1 = 0xb0 ; 0 = 0x30&n; * bit 2: ID3: bus speed: 1 = &lt;=33MHz ; 0 = &gt;33MHz&n; * bit 3: qd6500: 1 = disabled, 0 = enabled&n; *        qd6580: 1&n; * upper nibble:&n; *        qd6500: 1100&n; *        qd6580: either 1010 or 0101&n; *&n; *&n; * base+0x02: Timer2 (qd6580 only)&n; *&n; *&n; * base+0x03: Control (qd6580 only)&n; *&n; * bits 0-3 must always be set 1&n; * bit 4 must be set 1, but is set 0 by dos driver while measuring vlb clock&n; * bit 0 : 1 = Only primary port enabled : channel 0 for hda, channel 1 for hdb&n; *         0 = Primary and Secondary ports enabled : channel 0 for hda &amp; hdb&n; *                                                   channel 1 for hdc &amp; hdd&n; * bit 1 : 1 = only disks on primary port&n; *         0 = disks &amp; ATAPI devices on primary port&n; * bit 2-4 : always 0&n; * bit 5 : status, but of what ?&n; * bit 6 : always set 1 by dos driver&n; * bit 7 : set 1 for non-ATAPI devices on primary port&n; *&t;(maybe read-ahead and post-write buffer ?)&n; */
DECL|variable|timings
r_static
r_int
id|timings
(braket
l_int|4
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* stores current timing for each timer */
DECL|function|qd_write_reg
r_static
r_void
id|qd_write_reg
(paren
id|u8
id|content
comma
r_int
r_int
id|reg
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|content
comma
id|reg
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|qd_read_reg
r_static
id|u8
id|__init
id|qd_read_reg
(paren
r_int
r_int
id|reg
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|read
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|read
op_assign
id|inb
c_func
(paren
id|reg
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * qd_select:&n; *&n; * This routine is invoked from ide.c to prepare for access to a given drive.&n; */
DECL|function|qd_select
r_static
r_void
id|qd_select
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|index
op_assign
(paren
(paren
(paren
id|QD_TIMREG
c_func
(paren
id|drive
)paren
)paren
op_amp
l_int|0x80
)paren
op_rshift
l_int|7
)paren
op_or
(paren
id|QD_TIMREG
c_func
(paren
id|drive
)paren
op_amp
l_int|0x02
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timings
(braket
id|index
)braket
op_ne
id|QD_TIMING
c_func
(paren
id|drive
)paren
)paren
id|qd_write_reg
c_func
(paren
id|timings
(braket
id|index
)braket
op_assign
id|QD_TIMING
c_func
(paren
id|drive
)paren
comma
id|QD_TIMREG
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * qd6500_compute_timing&n; *&n; * computes the timing value where&n; *&t;lower nibble represents active time,   in count of VLB clocks&n; *&t;upper nibble represents recovery time, in count of VLB clocks&n; */
DECL|function|qd6500_compute_timing
r_static
id|u8
id|qd6500_compute_timing
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
id|active_time
comma
r_int
id|recovery_time
)paren
(brace
id|u8
id|active_cycle
comma
id|recovery_cycle
suffix:semicolon
r_if
c_cond
(paren
id|system_bus_clock
c_func
(paren
)paren
op_le
l_int|33
)paren
(brace
id|active_cycle
op_assign
l_int|9
op_minus
id|IDE_IN
c_func
(paren
id|active_time
op_star
id|system_bus_clock
c_func
(paren
)paren
op_div
l_int|1000
op_plus
l_int|1
comma
l_int|2
comma
l_int|9
)paren
suffix:semicolon
id|recovery_cycle
op_assign
l_int|15
op_minus
id|IDE_IN
c_func
(paren
id|recovery_time
op_star
id|system_bus_clock
c_func
(paren
)paren
op_div
l_int|1000
op_plus
l_int|1
comma
l_int|0
comma
l_int|15
)paren
suffix:semicolon
)brace
r_else
(brace
id|active_cycle
op_assign
l_int|8
op_minus
id|IDE_IN
c_func
(paren
id|active_time
op_star
id|system_bus_clock
c_func
(paren
)paren
op_div
l_int|1000
op_plus
l_int|1
comma
l_int|1
comma
l_int|8
)paren
suffix:semicolon
id|recovery_cycle
op_assign
l_int|18
op_minus
id|IDE_IN
c_func
(paren
id|recovery_time
op_star
id|system_bus_clock
c_func
(paren
)paren
op_div
l_int|1000
op_plus
l_int|1
comma
l_int|3
comma
l_int|18
)paren
suffix:semicolon
)brace
r_return
(paren
id|recovery_cycle
op_lshift
l_int|4
)paren
op_or
l_int|0x08
op_or
id|active_cycle
suffix:semicolon
)brace
multiline_comment|/*&n; * qd6580_compute_timing&n; *&n; * idem for qd6580&n; */
DECL|function|qd6580_compute_timing
r_static
id|u8
id|qd6580_compute_timing
(paren
r_int
id|active_time
comma
r_int
id|recovery_time
)paren
(brace
id|u8
id|active_cycle
op_assign
l_int|17
op_minus
id|IDE_IN
c_func
(paren
id|active_time
op_star
id|system_bus_clock
c_func
(paren
)paren
op_div
l_int|1000
op_plus
l_int|1
comma
l_int|2
comma
l_int|17
)paren
suffix:semicolon
id|u8
id|recovery_cycle
op_assign
l_int|15
op_minus
id|IDE_IN
c_func
(paren
id|recovery_time
op_star
id|system_bus_clock
c_func
(paren
)paren
op_div
l_int|1000
op_plus
l_int|1
comma
l_int|2
comma
l_int|15
)paren
suffix:semicolon
r_return
(paren
id|recovery_cycle
op_lshift
l_int|4
)paren
op_or
id|active_cycle
suffix:semicolon
)brace
multiline_comment|/*&n; * qd_find_disk_type&n; *&n; * tries to find timing from dos driver&squot;s table&n; */
DECL|function|qd_find_disk_type
r_static
r_int
id|qd_find_disk_type
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
op_star
id|active_time
comma
r_int
op_star
id|recovery_time
)paren
(brace
r_struct
id|qd65xx_timing_s
op_star
id|p
suffix:semicolon
r_char
id|model
(braket
l_int|40
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|drive-&gt;id-&gt;model
)paren
r_return
l_int|0
suffix:semicolon
id|strncpy
c_func
(paren
id|model
comma
id|drive-&gt;id-&gt;model
comma
l_int|40
)paren
suffix:semicolon
id|ide_fixstring
c_func
(paren
id|model
comma
l_int|40
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* byte-swap */
r_for
c_loop
(paren
id|p
op_assign
id|qd65xx_timing
suffix:semicolon
id|p-&gt;offset
op_ne
op_minus
l_int|1
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|p-&gt;model
comma
id|model
op_plus
id|p-&gt;offset
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: listed !&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
op_star
id|active_time
op_assign
id|p-&gt;active
suffix:semicolon
op_star
id|recovery_time
op_assign
id|p-&gt;recovery
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * qd_timing_ok:&n; *&n; * check whether timings don&squot;t conflict&n; */
DECL|function|qd_timing_ok
r_static
r_int
id|qd_timing_ok
(paren
id|ide_drive_t
id|drives
(braket
)braket
)paren
(brace
r_return
(paren
id|IDE_IMPLY
c_func
(paren
id|drives
(braket
l_int|0
)braket
dot
id|present
op_logical_and
id|drives
(braket
l_int|1
)braket
dot
id|present
comma
id|IDE_IMPLY
c_func
(paren
id|QD_TIMREG
c_func
(paren
id|drives
)paren
op_eq
id|QD_TIMREG
c_func
(paren
id|drives
op_plus
l_int|1
)paren
comma
id|QD_TIMING
c_func
(paren
id|drives
)paren
op_eq
id|QD_TIMING
c_func
(paren
id|drives
op_plus
l_int|1
)paren
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* if same timing register, must be same timing */
)brace
multiline_comment|/*&n; * qd_set_timing:&n; *&n; * records the timing, and enables selectproc as needed&n; */
DECL|function|qd_set_timing
r_static
r_void
id|qd_set_timing
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|timing
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
id|drive-&gt;drive_data
op_and_assign
l_int|0xff00
suffix:semicolon
id|drive-&gt;drive_data
op_or_assign
id|timing
suffix:semicolon
r_if
c_cond
(paren
id|qd_timing_ok
c_func
(paren
id|hwif-&gt;drives
)paren
)paren
(brace
id|qd_select
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* selects once */
id|hwif-&gt;selectproc
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|hwif-&gt;selectproc
op_assign
op_amp
id|qd_select
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: %#x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|timing
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * qd6500_tune_drive&n; */
DECL|function|qd6500_tune_drive
r_static
r_void
id|qd6500_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
r_int
id|active_time
op_assign
l_int|175
suffix:semicolon
r_int
id|recovery_time
op_assign
l_int|415
suffix:semicolon
multiline_comment|/* worst case values from the dos driver */
r_if
c_cond
(paren
id|drive-&gt;id
op_logical_and
op_logical_neg
id|qd_find_disk_type
c_func
(paren
id|drive
comma
op_amp
id|active_time
comma
op_amp
id|recovery_time
)paren
op_logical_and
id|drive-&gt;id-&gt;tPIO
op_logical_and
(paren
id|drive-&gt;id-&gt;field_valid
op_amp
l_int|0x02
)paren
op_logical_and
id|drive-&gt;id-&gt;eide_pio
op_ge
l_int|240
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: PIO mode%d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|drive-&gt;id-&gt;tPIO
)paren
suffix:semicolon
id|active_time
op_assign
l_int|110
suffix:semicolon
id|recovery_time
op_assign
id|drive-&gt;id-&gt;eide_pio
op_minus
l_int|120
suffix:semicolon
)brace
id|qd_set_timing
c_func
(paren
id|drive
comma
id|qd6500_compute_timing
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
comma
id|active_time
comma
id|recovery_time
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * qd6580_tune_drive&n; */
DECL|function|qd6580_tune_drive
r_static
r_void
id|qd6580_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
id|ide_pio_data_t
id|d
suffix:semicolon
r_int
id|base
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|select_data
suffix:semicolon
r_int
id|active_time
op_assign
l_int|175
suffix:semicolon
r_int
id|recovery_time
op_assign
l_int|415
suffix:semicolon
multiline_comment|/* worst case values from the dos driver */
r_if
c_cond
(paren
id|drive-&gt;id
op_logical_and
op_logical_neg
id|qd_find_disk_type
c_func
(paren
id|drive
comma
op_amp
id|active_time
comma
op_amp
id|recovery_time
)paren
)paren
(brace
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|255
comma
op_amp
id|d
)paren
suffix:semicolon
id|pio
op_assign
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
r_switch
c_cond
(paren
id|pio
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|d.cycle_time
op_ge
l_int|110
)paren
(brace
id|active_time
op_assign
l_int|86
suffix:semicolon
id|recovery_time
op_assign
id|d.cycle_time
op_minus
l_int|102
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Strange recovery time !&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
id|d.cycle_time
op_ge
l_int|69
)paren
(brace
id|active_time
op_assign
l_int|70
suffix:semicolon
id|recovery_time
op_assign
id|d.cycle_time
op_minus
l_int|61
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Strange recovery time !&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|d.cycle_time
op_ge
l_int|180
)paren
(brace
id|active_time
op_assign
l_int|110
suffix:semicolon
id|recovery_time
op_assign
id|d.cycle_time
op_minus
l_int|120
suffix:semicolon
)brace
r_else
(brace
id|active_time
op_assign
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|active_time
suffix:semicolon
id|recovery_time
op_assign
id|d.cycle_time
op_minus
id|active_time
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: PIO mode%d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|channel
op_logical_and
id|drive-&gt;media
op_ne
id|ide_disk
)paren
(brace
id|qd_write_reg
c_func
(paren
l_int|0x5f
comma
id|QD_CONTROL_PORT
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: ATAPI: disabled read-ahead FIFO &quot;
l_string|&quot;and post-write buffer on %s.&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
id|qd_set_timing
c_func
(paren
id|drive
comma
id|qd6580_compute_timing
c_func
(paren
id|active_time
comma
id|recovery_time
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * qd_testreg&n; *&n; * tests if the given port is a register&n; */
DECL|function|qd_testreg
r_static
r_int
id|__init
id|qd_testreg
c_func
(paren
r_int
id|port
)paren
(brace
id|u8
id|savereg
suffix:semicolon
id|u8
id|readreg
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|savereg
op_assign
id|inb_p
c_func
(paren
id|port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|QD_TESTVAL
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* safe value */
id|readreg
op_assign
id|inb_p
c_func
(paren
id|port
)paren
suffix:semicolon
id|outb
c_func
(paren
id|savereg
comma
id|port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|savereg
op_eq
id|QD_TESTVAL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Outch ! the probe for qd65xx isn&squot;t reliable !&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Please contact maintainers to tell about your hardware&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Assuming qd65xx is not present.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
(paren
id|readreg
op_ne
id|QD_TESTVAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * qd_setup:&n; *&n; * called to setup an ata channel : adjusts attributes &amp; links for tuning&n; */
DECL|function|qd_setup
r_static
r_void
id|__init
id|qd_setup
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
id|base
comma
r_int
id|config
comma
r_int
r_int
id|data0
comma
r_int
r_int
id|data1
comma
r_void
(paren
op_star
id|tuneproc
)paren
(paren
id|ide_drive_t
op_star
comma
id|u8
id|pio
)paren
)paren
(brace
id|hwif-&gt;chipset
op_assign
id|ide_qd65xx
suffix:semicolon
id|hwif-&gt;channel
op_assign
id|hwif-&gt;index
suffix:semicolon
id|hwif-&gt;select_data
op_assign
id|base
suffix:semicolon
id|hwif-&gt;config_data
op_assign
id|config
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|drive_data
op_assign
id|data0
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|drive_data
op_assign
id|data1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|io_32bit
op_assign
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|io_32bit
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
id|tuneproc
suffix:semicolon
id|probe_hwif_init
c_func
(paren
id|hwif
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * qd_unsetup:&n; *&n; * called to unsetup an ata channel : back to default values, unlinks tuning&n; */
multiline_comment|/*&n;static void __exit qd_unsetup(ide_hwif_t *hwif)&n;{&n;&t;u8 config = hwif-&gt;config_data;&n;&t;int base = hwif-&gt;select_data;&n;&t;void *tuneproc = (void *) hwif-&gt;tuneproc;&n;&n;&t;if (hwif-&gt;chipset != ide_qd65xx)&n;&t;&t;return;&n;&n;&t;printk(KERN_NOTICE &quot;%s: back to defaults&bslash;n&quot;, hwif-&gt;name);&n;&n;&t;hwif-&gt;selectproc = NULL;&n;&t;hwif-&gt;tuneproc = NULL;&n;&n;&t;if (tuneproc == (void *) qd6500_tune_drive) {&n;&t;&t;// will do it for both&n;&t;&t;qd_write_reg(QD6500_DEF_DATA, QD_TIMREG(&amp;hwif-&gt;drives[0]));&n;&t;} else if (tuneproc == (void *) qd6580_tune_drive) {&n;&t;&t;if (QD_CONTROL(hwif) &amp; QD_CONTR_SEC_DISABLED) {&n;&t;&t;&t;qd_write_reg(QD6580_DEF_DATA, QD_TIMREG(&amp;hwif-&gt;drives[0]));&n;&t;&t;&t;qd_write_reg(QD6580_DEF_DATA2, QD_TIMREG(&amp;hwif-&gt;drives[1]));&n;&t;&t;} else {&n;&t;&t;&t;qd_write_reg(hwif-&gt;channel ? QD6580_DEF_DATA2 : QD6580_DEF_DATA, QD_TIMREG(&amp;hwif-&gt;drives[0]));&n;&t;&t;}&n;&t;} else {&n;&t;&t;printk(KERN_WARNING &quot;Unknown qd65xx tuning fonction !&bslash;n&quot;);&n;&t;&t;printk(KERN_WARNING &quot;keeping settings !&bslash;n&quot;);&n;&t;}&n;}&n;*/
multiline_comment|/*&n; * qd_probe:&n; *&n; * looks at the specified baseport, and if qd found, registers &amp; initialises it&n; * return 1 if another qd may be probed&n; */
DECL|function|qd_probe
r_static
r_int
id|__init
id|qd_probe
c_func
(paren
r_int
id|base
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
suffix:semicolon
id|u8
id|config
suffix:semicolon
id|u8
id|unit
suffix:semicolon
id|config
op_assign
id|qd_read_reg
c_func
(paren
id|QD_CONFIG_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|config
op_amp
id|QD_CONFIG_BASEPORT
)paren
op_rshift
l_int|1
op_eq
(paren
id|base
op_eq
l_int|0xb0
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|unit
op_assign
op_logical_neg
(paren
id|config
op_amp
id|QD_CONFIG_IDE_BASEPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|config
op_amp
l_int|0xf0
)paren
op_eq
id|QD_CONFIG_QD6500
)paren
(brace
r_if
c_cond
(paren
id|qd_testreg
c_func
(paren
id|base
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* bad register */
multiline_comment|/* qd6500 found */
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
id|unit
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: qd6500 at %#x&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|base
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;qd6500: config=%#x, ID3=%u&bslash;n&quot;
comma
id|config
comma
id|QD_ID3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config
op_amp
id|QD_CONFIG_DISABLED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;qd6500 is disabled !&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|qd_setup
c_func
(paren
id|hwif
comma
id|base
comma
id|config
comma
id|QD6500_DEF_DATA
comma
id|QD6500_DEF_DATA
comma
op_amp
id|qd6500_tune_drive
)paren
suffix:semicolon
id|create_proc_ide_interfaces
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|config
op_amp
l_int|0xf0
)paren
op_eq
id|QD_CONFIG_QD6580_A
)paren
op_logical_or
(paren
(paren
id|config
op_amp
l_int|0xf0
)paren
op_eq
id|QD_CONFIG_QD6580_B
)paren
)paren
(brace
id|u8
id|control
suffix:semicolon
r_if
c_cond
(paren
id|qd_testreg
c_func
(paren
id|base
)paren
op_logical_or
id|qd_testreg
c_func
(paren
id|base
op_plus
l_int|0x02
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* bad registers */
multiline_comment|/* qd6580 found */
id|control
op_assign
id|qd_read_reg
c_func
(paren
id|QD_CONTROL_PORT
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;qd6580 at %#x&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;qd6580: config=%#x, control=%#x, ID3=%u&bslash;n&quot;
comma
id|config
comma
id|control
comma
id|QD_ID3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|QD_CONTR_SEC_DISABLED
)paren
(brace
multiline_comment|/* secondary disabled */
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
id|unit
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: qd6580: single IDE board&bslash;n&quot;
comma
id|hwif-&gt;name
)paren
suffix:semicolon
id|qd_setup
c_func
(paren
id|hwif
comma
id|base
comma
id|config
op_or
(paren
id|control
op_lshift
l_int|8
)paren
comma
id|QD6580_DEF_DATA
comma
id|QD6580_DEF_DATA2
comma
op_amp
id|qd6580_tune_drive
)paren
suffix:semicolon
id|qd_write_reg
c_func
(paren
id|QD_DEF_CONTR
comma
id|QD_CONTROL_PORT
)paren
suffix:semicolon
id|create_proc_ide_interfaces
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ide_hwif_t
op_star
id|mate
suffix:semicolon
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
l_int|0
)braket
suffix:semicolon
id|mate
op_assign
op_amp
id|ide_hwifs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* secondary enabled */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&amp;%s: qd6580: dual IDE board&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|mate-&gt;name
)paren
suffix:semicolon
id|qd_setup
c_func
(paren
id|hwif
comma
id|base
comma
id|config
op_or
(paren
id|control
op_lshift
l_int|8
)paren
comma
id|QD6580_DEF_DATA
comma
id|QD6580_DEF_DATA
comma
op_amp
id|qd6580_tune_drive
)paren
suffix:semicolon
id|qd_setup
c_func
(paren
id|mate
comma
id|base
comma
id|config
op_or
(paren
id|control
op_lshift
l_int|8
)paren
comma
id|QD6580_DEF_DATA2
comma
id|QD6580_DEF_DATA2
comma
op_amp
id|qd6580_tune_drive
)paren
suffix:semicolon
id|qd_write_reg
c_func
(paren
id|QD_DEF_CONTR
comma
id|QD_CONTROL_PORT
)paren
suffix:semicolon
id|create_proc_ide_interfaces
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no other qd65xx possible */
)brace
)brace
multiline_comment|/* no qd65xx found */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Can be called directly from ide.c. */
DECL|function|qd65xx_init
r_int
id|__init
id|qd65xx_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|qd_probe
c_func
(paren
l_int|0x30
)paren
)paren
id|qd_probe
c_func
(paren
l_int|0xb0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|chipset
op_ne
id|ide_qd65xx
op_logical_and
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|chipset
op_ne
id|ide_qd65xx
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|qd65xx_init
id|module_init
c_func
(paren
id|qd65xx_init
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Samuel Thibault&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;support of qd65xx vlb ide chipset&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
