multiline_comment|/*&n; *  arch/ppc/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  Modified for MBX using prep/chrp/pmac functions by Dan (dmalek@jlc.net)&n; *  Further modified for generic 8xx by Dan.&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/xmon.h&gt;
macro_line|#include &quot;ppc8xx_pic.h&quot;
r_static
r_int
id|m8xx_set_rtc_time
c_func
(paren
r_int
r_int
id|time
)paren
suffix:semicolon
r_static
r_int
r_int
id|m8xx_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|m8xx_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__res
r_int
r_char
id|__res
(braket
r_sizeof
(paren
id|bd_t
)paren
)braket
suffix:semicolon
r_extern
r_void
id|m8xx_ide_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|find_available_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|m8xx_cpm_reset
c_func
(paren
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|rpxfb_alloc_pages
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__attribute__
(paren
(paren
id|weak
)paren
)paren
DECL|function|board_init
id|board_init
c_func
(paren
r_void
)paren
(brace
)brace
r_void
id|__init
DECL|function|m8xx_setup_arch
id|m8xx_setup_arch
c_func
(paren
r_void
)paren
(brace
r_int
id|cpm_page
suffix:semicolon
id|cpm_page
op_assign
(paren
r_int
)paren
id|alloc_bootmem_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Reset the Communication Processor Module.&n;&t;*/
id|m8xx_cpm_reset
c_func
(paren
id|cpm_page
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FB_RPX
id|rpxfb_alloc_pages
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef notdef
id|ROOT_DEV
op_assign
id|Root_HDA1
suffix:semicolon
multiline_comment|/* hda1 */
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#if 0
id|ROOT_DEV
op_assign
id|Root_FD0
suffix:semicolon
multiline_comment|/* floppy */
id|rd_prompt
op_assign
l_int|1
suffix:semicolon
id|rd_doload
op_assign
l_int|1
suffix:semicolon
id|rd_image_start
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if 0&t;/* XXX this may need to be updated for the new bootmem stuff,&n;&t;   or possibly just deleted (see set_phys_avail() in init.c).&n;&t;   - paulus. */
multiline_comment|/* initrd_start and size are setup by boot/head.S and kernel/head.S */
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
r_if
c_cond
(paren
id|initrd_end
OG
op_star
id|memory_end_p
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_end
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#endif
id|board_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|abort
m_abort
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_XMON
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* not reached */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
multiline_comment|/* A place holder for time base interrupts, if they are ever enabled. */
DECL|function|timebase_interrupt
r_void
id|timebase_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
l_string|&quot;timebase_interrupt()&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* The decrementer counts at the system (internal) clock frequency divided by&n; * sixteen, or external oscillator divided by four.  We force the processor&n; * to use system clock divided by sixteen.&n; */
DECL|function|m8xx_calibrate_decr
r_void
id|__init
id|m8xx_calibrate_decr
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_int
id|freq
comma
id|fp
comma
id|divisor
suffix:semicolon
multiline_comment|/* Unlock the SCCR. */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_clkrstk.cark_sccrk
op_assign
op_complement
id|KAPWR_KEY
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_clkrstk.cark_sccrk
op_assign
id|KAPWR_KEY
suffix:semicolon
multiline_comment|/* Force all 8xx processors to use divide by 16 processor clock. */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_clkrst.car_sccr
op_or_assign
l_int|0x02000000
suffix:semicolon
multiline_comment|/* Processor frequency is MHz.&n;&t; * The value &squot;fp&squot; is the number of decrementer ticks per second.&n;&t; */
id|fp
op_assign
id|binfo-&gt;bi_intfreq
op_div
l_int|16
suffix:semicolon
id|freq
op_assign
id|fp
op_star
l_int|60
suffix:semicolon
multiline_comment|/* try to make freq/1e6 an integer */
id|divisor
op_assign
l_int|60
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Decrementer Frequency = %d/%d&bslash;n&quot;
comma
id|freq
comma
id|divisor
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
op_div
id|divisor
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
op_div
id|divisor
comma
l_int|1000000
)paren
suffix:semicolon
multiline_comment|/* Perform some more timer/timebase initialization.  This used&n;&t; * to be done elsewhere, but other changes caused it to get&n;&t; * called more than once....that is a bad thing.&n;&t; *&n;&t; * First, unlock all of the registers we are going to modify.&n;&t; * To protect them from corruption during power down, registers&n;&t; * that are maintained by keep alive power are &quot;locked&quot;.  To&n;&t; * modify these registers we have to write the key value to&n;&t; * the key location associated with the register.&n;&t; * Some boards power up with these unlocked, while others&n;&t; * are locked.  Writing anything (including the unlock code?)&n;&t; * to the unlocked registers will lock them again.  So, here&n;&t; * we guarantee the registers are locked, then we unlock them&n;&t; * for our use.&n;&t; */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_tbscrk
op_assign
op_complement
id|KAPWR_KEY
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_rtcsck
op_assign
op_complement
id|KAPWR_KEY
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_tbk
op_assign
op_complement
id|KAPWR_KEY
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_tbscrk
op_assign
id|KAPWR_KEY
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_rtcsck
op_assign
id|KAPWR_KEY
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_tbk
op_assign
id|KAPWR_KEY
suffix:semicolon
multiline_comment|/* Disable the RTC one second and alarm interrupts. */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_rtcsc
op_and_assign
op_complement
(paren
id|RTCSC_SIE
op_or
id|RTCSC_ALE
)paren
suffix:semicolon
multiline_comment|/* Enable the RTC */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_rtcsc
op_or_assign
(paren
id|RTCSC_RTF
op_or
id|RTCSC_RTE
)paren
suffix:semicolon
multiline_comment|/* Enabling the decrementer also enables the timebase interrupts&n;&t; * (or from the other point of view, to get decrementer interrupts&n;&t; * we have to enable the timebase).  The decrementer interrupt&n;&t; * is wired into the vector table, nothing to do here for that.&n;&t; */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_tbscr
op_assign
(paren
(paren
id|mk_int_int_mask
c_func
(paren
id|DEC_INTERRUPT
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|TBSCR_TBF
op_or
id|TBSCR_TBE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_8xxirq
c_func
(paren
id|DEC_INTERRUPT
comma
id|timebase_interrupt
comma
l_int|0
comma
l_string|&quot;tbint&quot;
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Could not allocate timer IRQ!&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* The RTC on the MPC8xx is an internal register.&n; * We want to protect this during power down, so we need to unlock,&n; * modify, and re-lock.&n; */
r_static
r_int
DECL|function|m8xx_set_rtc_time
id|m8xx_set_rtc_time
c_func
(paren
r_int
r_int
id|time
)paren
(brace
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_rtck
op_assign
id|KAPWR_KEY
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_rtc
op_assign
id|time
suffix:semicolon
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sitk.sitk_rtck
op_assign
op_complement
id|KAPWR_KEY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|m8xx_get_rtc_time
id|m8xx_get_rtc_time
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Get time from the RTC. */
r_return
(paren
r_int
r_int
)paren
(paren
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_rtc
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|m8xx_restart
id|m8xx_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|__volatile__
r_int
r_char
id|dummy
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_clkrst.car_plprcr
op_or_assign
l_int|0x00000080
suffix:semicolon
multiline_comment|/* Clear the ME bit in MSR to cause checkstop on machine check&n;&t;*/
id|mtmsr
c_func
(paren
id|mfmsr
c_func
(paren
)paren
op_amp
op_complement
l_int|0x1000
)paren
suffix:semicolon
id|dummy
op_assign
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_clkrst.res
(braket
l_int|0
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Restart failed&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|m8xx_power_off
id|m8xx_power_off
c_func
(paren
r_void
)paren
(brace
id|m8xx_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|m8xx_halt
id|m8xx_halt
c_func
(paren
r_void
)paren
(brace
id|m8xx_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|m8xx_show_percpuinfo
id|m8xx_show_percpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_int
id|i
)paren
(brace
id|bd_t
op_star
id|bp
suffix:semicolon
id|bp
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;clock&bslash;t&bslash;t: %ldMHz&bslash;n&quot;
l_string|&quot;bus clock&bslash;t: %ldMHz&bslash;n&quot;
comma
id|bp-&gt;bi_intfreq
op_div
l_int|1000000
comma
id|bp-&gt;bi_busfreq
op_div
l_int|1000000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Initialize the internal interrupt controller.  The number of&n; * interrupts supported can vary with the processor type, and the&n; * 82xx family can have up to 64.&n; * External interrupts can be either edge or level triggered, and&n; * need to be initialized by the appropriate driver.&n; */
r_static
r_void
id|__init
DECL|function|m8xx_init_IRQ
id|m8xx_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_void
id|cpm_interrupt_init
c_func
(paren
r_void
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
id|NR_SIU_INTS
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|ppc8xx_pic
suffix:semicolon
multiline_comment|/* We could probably incorporate the CPM into the multilevel&n;&t; * interrupt structure.&n;&t; */
id|cpm_interrupt_init
c_func
(paren
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|CPM_INTERRUPT
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PCI)
r_for
c_loop
(paren
id|i
op_assign
id|NR_SIU_INTS
suffix:semicolon
id|i
OL
(paren
id|NR_SIU_INTS
op_plus
id|NR_8259_INTS
)paren
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259_pic
suffix:semicolon
id|i8259_pic.irq_offset
op_assign
id|NR_SIU_INTS
suffix:semicolon
id|i8259_init
c_func
(paren
)paren
suffix:semicolon
id|request_8xxirq
c_func
(paren
id|ISA_BRIDGE_INT
comma
id|mbx_i8259_action
comma
l_int|0
comma
l_string|&quot;8259 cascade&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|ISA_BRIDGE_INT
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*&n; * This is a big hack right now, but it may turn into something real&n; * someday.&n; *&n; * For the 8xx boards (at this time anyway), there is nothing to initialize&n; * associated the PROM.  Rather than include all of the prom.c&n; * functions in the image just to get prom_init, all we really need right&n; * now is the initialization of the physical memory region.&n; */
r_static
r_int
r_int
id|__init
DECL|function|m8xx_find_end_of_memory
id|m8xx_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|binfo
suffix:semicolon
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_return
id|binfo-&gt;bi_memsize
suffix:semicolon
)brace
multiline_comment|/*&n; * Now map in some of the I/O space that is generically needed&n; * or shared with multiple devices.&n; * All of this fits into the same 4Mbyte region, so it only&n; * requires one page table page.  (or at least it used to  -- paulus)&n; */
r_static
r_void
id|__init
DECL|function|m8xx_map_io
id|m8xx_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
id|IMAP_ADDR
comma
id|IMAP_ADDR
comma
id|IMAP_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MBX
id|io_block_mapping
c_func
(paren
id|NVRAM_ADDR
comma
id|NVRAM_ADDR
comma
id|NVRAM_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|MBX_CSR_ADDR
comma
id|MBX_CSR_ADDR
comma
id|MBX_CSR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|PCI_CSR_ADDR
comma
id|PCI_CSR_ADDR
comma
id|PCI_CSR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
multiline_comment|/* Map some of the PCI/ISA I/O space to get the IDE interface.&n;&t;*/
id|io_block_mapping
c_func
(paren
id|PCI_ISA_IO_ADDR
comma
id|PCI_ISA_IO_ADDR
comma
l_int|0x4000
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|PCI_IDE_ADDR
comma
id|PCI_IDE_ADDR
comma
l_int|0x4000
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_RPXLITE) || defined(CONFIG_RPXCLASSIC)
id|io_block_mapping
c_func
(paren
id|RPX_CSR_ADDR
comma
id|RPX_CSR_ADDR
comma
id|RPX_CSR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_PCI)
id|io_block_mapping
c_func
(paren
id|_IO_BASE
comma
id|_IO_BASE
comma
id|_IO_BASE_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_HTDMSOUND
id|io_block_mapping
c_func
(paren
id|HIOX_CSR_ADDR
comma
id|HIOX_CSR_ADDR
comma
id|HIOX_CSR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FADS
id|io_block_mapping
c_func
(paren
id|BCSR_ADDR
comma
id|BCSR_ADDR
comma
id|BCSR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
id|io_block_mapping
c_func
(paren
id|PCI_CSR_ADDR
comma
id|PCI_CSR_ADDR
comma
id|PCI_CSR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r3
)paren
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|__res
comma
(paren
r_void
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
comma
r_sizeof
(paren
id|bd_t
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|m8xx_setup_pci_ptrs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* take care of initrd if we have one */
r_if
c_cond
(paren
id|r4
)paren
(brace
id|initrd_start
op_assign
id|r4
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|r5
op_plus
id|KERNELBASE
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
multiline_comment|/* take care of cmd line */
r_if
c_cond
(paren
id|r6
)paren
(brace
op_star
(paren
r_char
op_star
)paren
(paren
id|r7
op_plus
id|KERNELBASE
)paren
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|cmd_line
comma
(paren
r_char
op_star
)paren
(paren
id|r6
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
)brace
id|ppc_md.setup_arch
op_assign
id|m8xx_setup_arch
suffix:semicolon
id|ppc_md.show_percpuinfo
op_assign
id|m8xx_show_percpuinfo
suffix:semicolon
id|ppc_md.irq_canonicalize
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|m8xx_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|m8xx_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.restart
op_assign
id|m8xx_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|m8xx_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|m8xx_halt
suffix:semicolon
id|ppc_md.time_init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|m8xx_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|m8xx_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|m8xx_calibrate_decr
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|m8xx_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|m8xx_map_io
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
id|m8xx_ide_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
