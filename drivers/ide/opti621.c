multiline_comment|/*&n; *  linux/drivers/ide/opti621.c&t;&t;Version 0.6&t;Jan 02, 1999&n; *&n; *  Copyright (C) 1996-1998  Linus Torvalds &amp; authors (see below)&n; */
multiline_comment|/*&n; * Authors:&n; * Jaromir Koutek &lt;miri@punknet.cz&gt;,&n; * Jan Harkes &lt;jaharkes@cwi.nl&gt;,&n; * Mark Lord &lt;mlord@pobox.com&gt;&n; * Some parts of code are from ali14xx.c and from rz1000.c.&n; *&n; * OPTi is trademark of OPTi, Octek is trademark of Octek.&n; *&n; * I used docs from OPTi databook, from ftp.opti.com, file 9123-0002.ps&n; * and disassembled/traced setupvic.exe (DOS program).&n; * It increases kernel code about 2 kB.&n; * I don&squot;t have this card no more, but I hope I can get some in case&n; * of needed development.&n; * My card is Octek PIDE 1.01 (on card) or OPTiViC (program).&n; * It has a place for a secondary connector in circuit, but nothing&n; * is there. Also BIOS says no address for&n; * secondary controller (see bellow in ide_init_opti621).&n; * I&squot;ve only tested this on my system, which only has one disk.&n; * It&squot;s Western Digital WDAC2850, with PIO mode 3. The PCI bus&n; * is at 20 MHz (I have DX2/80, I tried PCI at 40, but I got random&n; * lockups). I tried the OCTEK double speed CD-ROM and&n; * it does not work! But I can&squot;t boot DOS also, so it&squot;s probably&n; * hardware fault. I have connected Conner 80MB, the Seagate 850MB (no&n; * problems) and Seagate 1GB (as slave, WD as master). My experiences&n; * with the third, 1GB drive: I got 3MB/s (hdparm), but sometimes&n; * it slows to about 100kB/s! I don&squot;t know why and I have&n; * not this drive now, so I can&squot;t try it again.&n; * I write this driver because I lost the paper (&quot;manual&quot;) with&n; * settings of jumpers on the card and I have to boot Linux with&n; * Loadlin except LILO, cause I have to run the setupvic.exe program&n; * already or I get disk errors (my test: rpm -Vf&n; * /usr/X11R6/bin/XF86_SVGA - or any big file).&n; * Some numbers from hdparm -t /dev/hda:&n; * Timing buffer-cache reads:   32 MB in  3.02 seconds =10.60 MB/sec&n; * Timing buffered disk reads:  16 MB in  5.52 seconds = 2.90 MB/sec&n; * I have 4 Megs/s before, but I don&squot;t know why (maybe changes&n; * in hdparm test).&n; * After release of 0.1, I got some successful reports, so it might work.&n; *&n; * The main problem with OPTi is that some timings for master&n; * and slave must be the same. For example, if you have master&n; * PIO 3 and slave PIO 0, driver have to set some timings of&n; * master for PIO 0. Second problem is that opti621_tune_drive&n; * got only one drive to set, but have to set both drives.&n; * This is solved in compute_pios. If you don&squot;t set&n; * the second drive, compute_pios use ide_get_best_pio_mode&n; * for autoselect mode (you can change it to PIO 0, if you want).&n; * If you then set the second drive to another PIO, the old value&n; * (automatically selected) will be overrided by yours.&n; * There is a 25/33MHz switch in configuration&n; * register, but driver is written for use at any frequency which get&n; * (use idebus=xx to select PCI bus speed).&n; * Use ide0=autotune for automatical tune of the PIO modes.&n; * If you get strange results, do not use this and set PIO manually&n; * by hdparm.&n; *&n; * Version 0.1, Nov 8, 1996&n; * by Jaromir Koutek, for 2.1.8. &n; * Initial version of driver.&n; * &n; * Version 0.2&n; * Number 0.2 skipped.&n; *&n; * Version 0.3, Nov 29, 1997&n; * by Mark Lord (probably), for 2.1.68&n; * Updates for use with new IDE block driver.&n; *&n; * Version 0.4, Dec 14, 1997&n; * by Jan Harkes&n; * Fixed some errors and cleaned the code.&n; *&n; * Version 0.5, Jan 2, 1998&n; * by Jaromir Koutek&n; * Updates for use with (again) new IDE block driver.&n; * Update of documentation.&n; * &n; * Version 0.6, Jan 2, 1999&n; * by Jaromir Koutek&n; * Reversed to version 0.3 of the driver, because&n; * 0.5 doesn&squot;t work.&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;/* most systems can safely undef this */
DECL|macro|OPTI621_DEBUG
mdefine_line|#define OPTI621_DEBUG&t;&t;/* define for debug messages */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
DECL|macro|OPTI621_MAX_PIO
mdefine_line|#define OPTI621_MAX_PIO 3
multiline_comment|/* In fact, I do not have any PIO 4 drive&n; * (address: 25 ns, data: 70 ns, recovery: 35 ns),&n; * but OPTi 82C621 is programmable and it can do (minimal values):&n; * on 40MHz PCI bus (pulse 25 ns):&n; *  address: 25 ns, data: 25 ns, recovery: 50 ns;&n; * on 20MHz PCI bus (pulse 50 ns):&n; *  address: 50 ns, data: 50 ns, recovery: 100 ns.&n; */
multiline_comment|/* #define READ_PREFETCH 0 */
multiline_comment|/* Uncommnent for disable read prefetch.&n; * There is some readprefetch capatibility in hdparm,&n; * but when I type hdparm -P 1 /dev/hda, I got errors&n; * and till reset drive is inaccessible.&n; * This (hw) read prefetch is safe on my drive.&n; */
macro_line|#ifndef READ_PREFETCH
DECL|macro|READ_PREFETCH
mdefine_line|#define READ_PREFETCH 0x40 /* read prefetch is enabled */
macro_line|#endif /* else read prefetch is disabled */
DECL|macro|READ_REG
mdefine_line|#define READ_REG 0&t;/* index of Read cycle timing register */
DECL|macro|WRITE_REG
mdefine_line|#define WRITE_REG 1&t;/* index of Write cycle timing register */
DECL|macro|CNTRL_REG
mdefine_line|#define CNTRL_REG 3&t;/* index of Control register */
DECL|macro|STRAP_REG
mdefine_line|#define STRAP_REG 5&t;/* index of Strap register */
DECL|macro|MISC_REG
mdefine_line|#define MISC_REG 6&t;/* index of Miscellaneous register */
DECL|variable|reg_base
r_int
id|reg_base
suffix:semicolon
DECL|macro|PIO_NOT_EXIST
mdefine_line|#define PIO_NOT_EXIST 254
DECL|macro|PIO_DONT_KNOW
mdefine_line|#define PIO_DONT_KNOW 255
multiline_comment|/* there are stored pio numbers from other calls of opti621_tune_drive */
DECL|function|compute_pios
r_static
r_void
id|compute_pios
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
multiline_comment|/* Store values into drive-&gt;drive_data&n; *&t;second_contr - 0 for primary controller, 1 for secondary&n; *&t;slave_drive - 0 -&gt; pio is for master, 1 -&gt; pio is for slave&n; *&t;pio - PIO mode for selected drive (for other we don&squot;t know)&n; */
(brace
r_int
id|d
suffix:semicolon
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
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
id|OPTI621_MAX_PIO
comma
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
l_int|2
suffix:semicolon
op_increment
id|d
)paren
(brace
id|drive
op_assign
op_amp
id|hwif-&gt;drives
(braket
id|d
)braket
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;present
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;drive_data
op_eq
id|PIO_DONT_KNOW
)paren
id|drive-&gt;drive_data
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
l_int|255
comma
id|OPTI621_MAX_PIO
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef OPTI621_DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: Selected PIO mode %d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|drive-&gt;drive_data
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|drive-&gt;drive_data
op_assign
id|PIO_NOT_EXIST
suffix:semicolon
)brace
)brace
)brace
DECL|function|cmpt_clk
r_int
id|cmpt_clk
c_func
(paren
r_int
id|time
comma
r_int
id|bus_speed
)paren
multiline_comment|/* Returns (rounded up) time in clocks for time in ns,&n; * with bus_speed in MHz.&n; * Example: bus_speed = 40 MHz, time = 80 ns&n; * 1000/40 = 25 ns (clk value),&n; * 80/25 = 3.2, rounded up to 4 (I hope ;-)).&n; * Use idebus=xx to select right frequency.&n; */
(brace
r_return
(paren
(paren
id|time
op_star
id|bus_speed
op_plus
l_int|999
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
DECL|function|write_reg
r_static
r_void
id|write_reg
c_func
(paren
id|byte
id|value
comma
r_int
id|reg
)paren
multiline_comment|/* Write value to register reg, base of register&n; * is at reg_base (0x1f0 primary, 0x170 secondary,&n; * if not changed by PCI configuration).&n; * This is from setupvic.exe program.&n; */
(brace
id|IN_WORD
c_func
(paren
id|reg_base
op_plus
l_int|1
)paren
suffix:semicolon
id|IN_WORD
c_func
(paren
id|reg_base
op_plus
l_int|1
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
l_int|3
comma
id|reg_base
op_plus
l_int|2
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|value
comma
id|reg_base
op_plus
id|reg
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
l_int|0x83
comma
id|reg_base
op_plus
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|read_reg
r_static
id|byte
id|read_reg
c_func
(paren
r_int
id|reg
)paren
multiline_comment|/* Read value from register reg, base of register&n; * is at reg_base (0x1f0 primary, 0x170 secondary,&n; * if not changed by PCI configuration).&n; * This is from setupvic.exe program.&n; */
(brace
id|byte
id|ret
suffix:semicolon
id|IN_WORD
c_func
(paren
id|reg_base
op_plus
l_int|1
)paren
suffix:semicolon
id|IN_WORD
c_func
(paren
id|reg_base
op_plus
l_int|1
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
l_int|3
comma
id|reg_base
op_plus
l_int|2
)paren
suffix:semicolon
id|ret
op_assign
id|IN_BYTE
c_func
(paren
id|reg_base
op_plus
id|reg
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
l_int|0x83
comma
id|reg_base
op_plus
l_int|2
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|struct|pio_clocks_s
r_typedef
r_struct
id|pio_clocks_s
(brace
DECL|member|address_time
r_int
id|address_time
suffix:semicolon
multiline_comment|/* Address setup (clocks) */
DECL|member|data_time
r_int
id|data_time
suffix:semicolon
multiline_comment|/* Active/data pulse (clocks) */
DECL|member|recovery_time
r_int
id|recovery_time
suffix:semicolon
multiline_comment|/* Recovery time (clocks) */
DECL|typedef|pio_clocks_t
)brace
id|pio_clocks_t
suffix:semicolon
DECL|function|compute_clocks
r_static
r_void
id|compute_clocks
c_func
(paren
r_int
id|pio
comma
id|pio_clocks_t
op_star
id|clks
)paren
(brace
r_if
c_cond
(paren
id|pio
op_ne
id|PIO_NOT_EXIST
)paren
(brace
r_int
id|adr_setup
comma
id|data_pls
suffix:semicolon
r_int
id|bus_speed
op_assign
id|system_bus_clock
c_func
(paren
)paren
suffix:semicolon
id|adr_setup
op_assign
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|setup_time
suffix:semicolon
id|data_pls
op_assign
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|active_time
suffix:semicolon
id|clks-&gt;address_time
op_assign
id|cmpt_clk
c_func
(paren
id|adr_setup
comma
id|bus_speed
)paren
suffix:semicolon
id|clks-&gt;data_time
op_assign
id|cmpt_clk
c_func
(paren
id|data_pls
comma
id|bus_speed
)paren
suffix:semicolon
id|clks-&gt;recovery_time
op_assign
id|cmpt_clk
c_func
(paren
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|cycle_time
op_minus
id|adr_setup
op_minus
id|data_pls
comma
id|bus_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clks-&gt;address_time
OL
l_int|1
)paren
id|clks-&gt;address_time
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|clks-&gt;address_time
OG
l_int|4
)paren
id|clks-&gt;address_time
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|clks-&gt;data_time
OL
l_int|1
)paren
id|clks-&gt;data_time
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|clks-&gt;data_time
OG
l_int|16
)paren
id|clks-&gt;data_time
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|clks-&gt;recovery_time
OL
l_int|2
)paren
id|clks-&gt;recovery_time
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|clks-&gt;recovery_time
OG
l_int|17
)paren
id|clks-&gt;recovery_time
op_assign
l_int|17
suffix:semicolon
)brace
r_else
(brace
id|clks-&gt;address_time
op_assign
l_int|1
suffix:semicolon
id|clks-&gt;data_time
op_assign
l_int|1
suffix:semicolon
id|clks-&gt;recovery_time
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* minimal values */
)brace
)brace
multiline_comment|/* Main tune procedure, called from tuneproc. */
DECL|function|opti621_tune_drive
r_static
r_void
id|opti621_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
multiline_comment|/* primary and secondary drives share some registers,&n;&t; * so we have to program both drives&n;&t; */
r_int
r_int
id|flags
suffix:semicolon
id|byte
id|pio1
comma
id|pio2
suffix:semicolon
id|pio_clocks_t
id|first
comma
id|second
suffix:semicolon
r_int
id|ax
comma
id|drdy
suffix:semicolon
id|byte
id|cycle1
comma
id|cycle2
comma
id|misc
suffix:semicolon
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
multiline_comment|/* sets drive-&gt;drive_data for both drives */
id|compute_pios
c_func
(paren
id|drive
comma
id|pio
)paren
suffix:semicolon
id|pio1
op_assign
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|drive_data
suffix:semicolon
id|pio2
op_assign
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|drive_data
suffix:semicolon
id|compute_clocks
c_func
(paren
id|pio1
comma
op_amp
id|first
)paren
suffix:semicolon
id|compute_clocks
c_func
(paren
id|pio2
comma
op_amp
id|second
)paren
suffix:semicolon
multiline_comment|/* ax = max(a1,a2) */
id|ax
op_assign
(paren
id|first.address_time
OL
id|second.address_time
)paren
ques
c_cond
id|second.address_time
suffix:colon
id|first.address_time
suffix:semicolon
id|drdy
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* DRDY is default 2 (by OPTi Databook) */
id|cycle1
op_assign
(paren
(paren
id|first.data_time
op_minus
l_int|1
)paren
op_lshift
l_int|4
)paren
op_or
(paren
id|first.recovery_time
op_minus
l_int|2
)paren
suffix:semicolon
id|cycle2
op_assign
(paren
(paren
id|second.data_time
op_minus
l_int|1
)paren
op_lshift
l_int|4
)paren
op_or
(paren
id|second.recovery_time
op_minus
l_int|2
)paren
suffix:semicolon
id|misc
op_assign
id|READ_PREFETCH
op_or
(paren
(paren
id|ax
op_minus
l_int|1
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|drdy
op_minus
l_int|2
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef OPTI621_DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: master: address: %d, data: %d, recovery: %d, drdy: %d [clk]&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|ax
comma
id|first.data_time
comma
id|first.recovery_time
comma
id|drdy
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: slave:  address: %d, data: %d, recovery: %d, drdy: %d [clk]&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|ax
comma
id|second.data_time
comma
id|second.recovery_time
comma
id|drdy
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|reg_base
op_assign
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
suffix:semicolon
id|OUT_BYTE
c_func
(paren
l_int|0xc0
comma
id|reg_base
op_plus
id|CNTRL_REG
)paren
suffix:semicolon
multiline_comment|/* allow Register-B */
id|OUT_BYTE
c_func
(paren
l_int|0xff
comma
id|reg_base
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* hmm, setupvic.exe does this ;-) */
id|IN_BYTE
c_func
(paren
id|reg_base
op_plus
id|CNTRL_REG
)paren
suffix:semicolon
multiline_comment|/* if reads 0xff, adapter not exist? */
id|read_reg
c_func
(paren
id|CNTRL_REG
)paren
suffix:semicolon
multiline_comment|/* if reads 0xc0, no interface exist? */
id|read_reg
c_func
(paren
id|STRAP_REG
)paren
suffix:semicolon
multiline_comment|/* read version, probably 0 */
multiline_comment|/* program primary drive */
id|write_reg
c_func
(paren
l_int|0
comma
id|MISC_REG
)paren
suffix:semicolon
multiline_comment|/* select Index-0 for Register-A */
id|write_reg
c_func
(paren
id|cycle1
comma
id|READ_REG
)paren
suffix:semicolon
multiline_comment|/* set read cycle timings */
id|write_reg
c_func
(paren
id|cycle1
comma
id|WRITE_REG
)paren
suffix:semicolon
multiline_comment|/* set write cycle timings */
multiline_comment|/* program secondary drive */
id|write_reg
c_func
(paren
l_int|1
comma
id|MISC_REG
)paren
suffix:semicolon
multiline_comment|/* select Index-1 for Register-B */
id|write_reg
c_func
(paren
id|cycle2
comma
id|READ_REG
)paren
suffix:semicolon
multiline_comment|/* set read cycle timings */
id|write_reg
c_func
(paren
id|cycle2
comma
id|WRITE_REG
)paren
suffix:semicolon
multiline_comment|/* set write cycle timings */
id|write_reg
c_func
(paren
l_int|0x85
comma
id|CNTRL_REG
)paren
suffix:semicolon
multiline_comment|/* use Register-A for drive 0 */
multiline_comment|/* use Register-B for drive 1 */
id|write_reg
c_func
(paren
id|misc
comma
id|MISC_REG
)paren
suffix:semicolon
multiline_comment|/* set address setup, DRDY timings,   */
multiline_comment|/*  and read prefetch for both drives */
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
multiline_comment|/*&n; * ide_init_opti621() is called once for each hwif found at boot.&n; */
DECL|function|ide_init_opti621
r_void
id|__init
id|ide_init_opti621
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|drive_data
op_assign
id|PIO_DONT_KNOW
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|drive_data
op_assign
id|PIO_DONT_KNOW
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|opti621_tune_drive
suffix:semicolon
multiline_comment|/* safety call for Anton A */
id|hwif-&gt;dma_base
op_assign
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|ide_setup_pci_device
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|ide_pci_device_t
op_star
id|d
)paren
suffix:semicolon
DECL|function|fixup_device_opti621
r_void
id|__init
id|fixup_device_opti621
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|ide_pci_device_t
op_star
id|d
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|IDE_PCI_DEVID_EQ
c_func
(paren
id|d-&gt;devid
comma
id|DEVID_OPTI621V
)paren
op_logical_and
op_logical_neg
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_amp
l_int|1
)paren
)paren
macro_line|#else
r_if
c_cond
(paren
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_OPTI_82C558
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_amp
l_int|1
)paren
)paren
)paren
macro_line|#endif
r_return
suffix:semicolon
multiline_comment|/* OPTI621 is more than only a IDE controller */
id|printk
c_func
(paren
l_string|&quot;%s: IDE controller on PCI bus %02x dev %02x&bslash;n&quot;
comma
id|d-&gt;name
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
)paren
suffix:semicolon
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
)brace
eof
