multiline_comment|/* linux/arch/arm/mach-s3c2410/pm.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 Power Manager (Suspend-To-RAM) support&n; *&n; * See Documentation/arm/Samsung-S3C24XX/Suspend.txt for more information&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Parts based on arch/arm/mach-pxa/pm.c&n; *&n; * Thanks to Dimitry Andric for debugging&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &lt;asm/arch/regs-clock.h&gt;
macro_line|#include &lt;asm/arch/regs-gpio.h&gt;
macro_line|#include &lt;asm/arch/regs-mem.h&gt;
macro_line|#include &lt;asm/arch/regs-irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &quot;pm.h&quot;
multiline_comment|/* for external use */
DECL|variable|s3c_pm_flags
r_int
r_int
id|s3c_pm_flags
suffix:semicolon
multiline_comment|/* cache functions from arch/arm/mm/proc-arm920.S */
r_extern
r_void
id|arm920_flush_kern_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PFX
mdefine_line|#define PFX &quot;s3c24xx-pm: &quot;
DECL|variable|core_save
r_static
r_struct
id|sleep_save
id|core_save
(braket
)braket
op_assign
(brace
id|SAVE_ITEM
c_func
(paren
id|S3C2410_LOCKTIME
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_CLKCON
)paren
comma
multiline_comment|/* we restore the timings here, with the proviso that the board&n;&t; * brings the system up in an slower, or equal frequency setting&n;&t; * to the original system.&n;&t; *&n;&t; * if we cannot guarantee this, then things are going to go very&n;&t; * wrong here, as we modify the refresh and both pll settings.&n;&t; */
id|SAVE_ITEM
c_func
(paren
id|S3C2410_BWSCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_BANKCON0
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_BANKCON1
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_BANKCON2
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_BANKCON3
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_BANKCON4
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_BANKCON5
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_CLKDIVN
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_MPLLCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_UPLLCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_CLKSLOW
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_REFRESH
)paren
comma
)brace
suffix:semicolon
multiline_comment|/* this lot should be really saved by the IRQ code */
DECL|variable|irq_save
r_static
r_struct
id|sleep_save
id|irq_save
(braket
)braket
op_assign
(brace
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EXTINT0
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EXTINT1
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EXTINT2
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EINFLT0
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EINFLT1
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EINFLT2
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EINFLT3
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_EINTMASK
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_INTMSK
)paren
)brace
suffix:semicolon
DECL|variable|gpio_save
r_static
r_struct
id|sleep_save
id|gpio_save
(braket
)braket
op_assign
(brace
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPACON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPADAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPBCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPBDAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPBUP
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPCCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPCDAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPCUP
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPDCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPDDAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPDUP
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPECON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPEDAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPEUP
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPFCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPFDAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPFUP
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPGCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPGDAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPGUP
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPHCON
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPHDAT
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_GPHUP
)paren
comma
id|SAVE_ITEM
c_func
(paren
id|S3C2410_DCLKCON
)paren
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_S3C2410_PM_DEBUG
DECL|macro|SAVE_UART
mdefine_line|#define SAVE_UART(va) &bslash;&n;&t;SAVE_ITEM((va) + S3C2410_ULCON), &bslash;&n;&t;SAVE_ITEM((va) + S3C2410_UCON), &bslash;&n;&t;SAVE_ITEM((va) + S3C2410_UFCON), &bslash;&n;&t;SAVE_ITEM((va) + S3C2410_UMCON), &bslash;&n;&t;SAVE_ITEM((va) + S3C2410_UBRDIV)
DECL|variable|uart_save
r_static
r_struct
id|sleep_save
id|uart_save
(braket
)braket
op_assign
(brace
id|SAVE_UART
c_func
(paren
id|S3C2410_VA_UART0
)paren
comma
id|SAVE_UART
c_func
(paren
id|S3C2410_VA_UART1
)paren
comma
id|SAVE_UART
c_func
(paren
id|S3C2410_VA_UART2
)paren
comma
)brace
suffix:semicolon
multiline_comment|/* debug&n; *&n; * we send the debug to printascii() to allow it to be seen if the&n; * system never wakes up from the sleep&n;*/
r_extern
r_void
id|printascii
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|function|pm_dbg
r_static
r_void
id|pm_dbg
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|va
suffix:semicolon
r_char
id|buff
(braket
l_int|256
)braket
suffix:semicolon
id|va_start
c_func
(paren
id|va
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buff
comma
id|fmt
comma
id|va
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|va
)paren
suffix:semicolon
id|printascii
c_func
(paren
id|buff
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_pm_debug_init
r_static
r_void
id|s3c2410_pm_debug_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|__raw_readl
c_func
(paren
id|S3C2410_CLKCON
)paren
suffix:semicolon
multiline_comment|/* re-start uart clocks */
id|tmp
op_or_assign
id|S3C2410_CLKCON_UART0
suffix:semicolon
id|tmp
op_or_assign
id|S3C2410_CLKCON_UART1
suffix:semicolon
id|tmp
op_or_assign
id|S3C2410_CLKCON_UART2
suffix:semicolon
id|__raw_writel
c_func
(paren
id|tmp
comma
id|S3C2410_CLKCON
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
DECL|macro|DBG
mdefine_line|#define DBG(fmt...) pm_dbg(fmt)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt...) printk(KERN_DEBUG fmt)
DECL|macro|s3c2410_pm_debug_init
mdefine_line|#define s3c2410_pm_debug_init() do { } while(0)
macro_line|#endif
macro_line|#if defined(CONFIG_S3C2410_PM_CHECK) &amp;&amp; CONFIG_S3C2410_PM_CHECK_CHUNKSIZE != 0
multiline_comment|/* suspend checking code...&n; *&n; * this next area does a set of crc checks over all the installed&n; * memory, so the system can verify if the resume was ok.&n; *&n; * CONFIG_S3C2410_PM_CHECK_CHUNKSIZE defines the block-size for the CRC,&n; * increasing it will mean that the area corrupted will be less easy to spot,&n; * and reducing the size will cause the CRC save area to grow&n;*/
DECL|macro|CHECK_CHUNKSIZE
mdefine_line|#define CHECK_CHUNKSIZE (CONFIG_S3C2410_PM_CHECK_CHUNKSIZE * 1024)
DECL|variable|crc_size
r_static
id|u32
id|crc_size
suffix:semicolon
multiline_comment|/* size needed for the crc block */
DECL|variable|crcs
r_static
id|u32
op_star
id|crcs
suffix:semicolon
multiline_comment|/* allocated over suspend/resume */
DECL|typedef|run_fn_t
r_typedef
id|u32
op_star
(paren
id|run_fn_t
)paren
(paren
r_struct
id|resource
op_star
id|ptr
comma
id|u32
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* s3c2410_pm_run_res&n; *&n; * go thorugh the given resource list, and look for system ram&n;*/
DECL|function|s3c2410_pm_run_res
r_static
r_void
id|s3c2410_pm_run_res
c_func
(paren
r_struct
id|resource
op_star
id|ptr
comma
id|run_fn_t
id|fn
comma
id|u32
op_star
id|arg
)paren
(brace
r_while
c_loop
(paren
id|ptr
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ptr-&gt;child
op_ne
l_int|NULL
)paren
id|s3c2410_pm_run_res
c_func
(paren
id|ptr-&gt;child
comma
id|fn
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptr-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
op_logical_and
id|strcmp
c_func
(paren
id|ptr-&gt;name
comma
l_string|&quot;System RAM&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Found system RAM at %08lx..%08lx&bslash;n&quot;
comma
id|ptr-&gt;start
comma
id|ptr-&gt;end
)paren
suffix:semicolon
id|arg
op_assign
(paren
id|fn
)paren
(paren
id|ptr
comma
id|arg
)paren
suffix:semicolon
)brace
id|ptr
op_assign
id|ptr-&gt;sibling
suffix:semicolon
)brace
)brace
DECL|function|s3c2410_pm_run_sysram
r_static
r_void
id|s3c2410_pm_run_sysram
c_func
(paren
id|run_fn_t
id|fn
comma
id|u32
op_star
id|arg
)paren
(brace
id|s3c2410_pm_run_res
c_func
(paren
op_amp
id|iomem_resource
comma
id|fn
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_pm_countram
r_static
id|u32
op_star
id|s3c2410_pm_countram
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
id|u32
op_star
id|val
)paren
(brace
id|u32
id|size
op_assign
(paren
id|u32
)paren
(paren
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
op_plus
l_int|1
suffix:semicolon
id|size
op_add_assign
id|CHECK_CHUNKSIZE
op_minus
l_int|1
suffix:semicolon
id|size
op_div_assign
id|CHECK_CHUNKSIZE
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Area %08lx..%08lx, %d blocks&bslash;n&quot;
comma
id|res-&gt;start
comma
id|res-&gt;end
comma
id|size
)paren
suffix:semicolon
op_star
id|val
op_add_assign
id|size
op_star
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* s3c2410_pm_prepare_check&n; *&n; * prepare the necessary information for creating the CRCs. This&n; * must be done before the final save, as it will require memory&n; * allocating, and thus touching bits of the kernel we do not&n; * know about.&n;*/
DECL|function|s3c2410_pm_check_prepare
r_static
r_void
id|s3c2410_pm_check_prepare
c_func
(paren
r_void
)paren
(brace
id|crc_size
op_assign
l_int|0
suffix:semicolon
id|s3c2410_pm_run_sysram
c_func
(paren
id|s3c2410_pm_countram
comma
op_amp
id|crc_size
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;s3c2410_pm_prepare_check: %u checks needed&bslash;n&quot;
comma
id|crc_size
)paren
suffix:semicolon
id|crcs
op_assign
id|kmalloc
c_func
(paren
id|crc_size
op_plus
l_int|4
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crcs
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Cannot allocated CRC save area&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_pm_makecheck
r_static
id|u32
op_star
id|s3c2410_pm_makecheck
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
id|u32
op_star
id|val
)paren
(brace
r_int
r_int
id|addr
comma
id|left
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|res-&gt;start
suffix:semicolon
id|addr
OL
id|res-&gt;end
suffix:semicolon
id|addr
op_add_assign
id|CHECK_CHUNKSIZE
)paren
(brace
id|left
op_assign
id|res-&gt;end
op_minus
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
id|CHECK_CHUNKSIZE
)paren
id|left
op_assign
id|CHECK_CHUNKSIZE
suffix:semicolon
op_star
id|val
op_assign
id|crc32_le
c_func
(paren
op_complement
l_int|0
comma
id|phys_to_virt
c_func
(paren
id|addr
)paren
comma
id|left
)paren
suffix:semicolon
id|val
op_increment
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* s3c2410_pm_check_store&n; *&n; * compute the CRC values for the memory blocks before the final&n; * sleep.&n;*/
DECL|function|s3c2410_pm_check_store
r_static
r_void
id|s3c2410_pm_check_store
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|crcs
op_ne
l_int|NULL
)paren
id|s3c2410_pm_run_sysram
c_func
(paren
id|s3c2410_pm_makecheck
comma
id|crcs
)paren
suffix:semicolon
)brace
multiline_comment|/* in_region&n; *&n; * return TRUE if the area defined by ptr..ptr+size contatins the&n; * what..what+whatsz&n;*/
DECL|function|in_region
r_static
r_inline
r_int
id|in_region
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
comma
r_void
op_star
id|what
comma
r_int
id|whatsz
)paren
(brace
r_if
c_cond
(paren
(paren
id|what
op_plus
id|whatsz
)paren
OL
id|ptr
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|what
OG
(paren
id|ptr
op_plus
id|size
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|s3c2410_pm_runcheck
r_static
id|u32
op_star
id|s3c2410_pm_runcheck
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
id|u32
op_star
id|val
)paren
(brace
r_void
op_star
id|save_at
op_assign
id|phys_to_virt
c_func
(paren
id|s3c2410_sleep_save_phys
)paren
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|left
suffix:semicolon
r_void
op_star
id|ptr
suffix:semicolon
id|u32
id|calc
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|res-&gt;start
suffix:semicolon
id|addr
OL
id|res-&gt;end
suffix:semicolon
id|addr
op_add_assign
id|CHECK_CHUNKSIZE
)paren
(brace
id|left
op_assign
id|res-&gt;end
op_minus
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
id|CHECK_CHUNKSIZE
)paren
id|left
op_assign
id|CHECK_CHUNKSIZE
suffix:semicolon
id|ptr
op_assign
id|phys_to_virt
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_region
c_func
(paren
id|ptr
comma
id|left
comma
id|crcs
comma
id|crc_size
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;skipping %08lx, has crc block in&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_goto
id|skip_check
suffix:semicolon
)brace
r_if
c_cond
(paren
id|in_region
c_func
(paren
id|ptr
comma
id|left
comma
id|save_at
comma
l_int|32
op_star
l_int|4
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;skipping %08lx, has save block in&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_goto
id|skip_check
suffix:semicolon
)brace
multiline_comment|/* calculate and check the checksum */
id|calc
op_assign
id|crc32_le
c_func
(paren
op_complement
l_int|0
comma
id|ptr
comma
id|left
)paren
suffix:semicolon
r_if
c_cond
(paren
id|calc
op_ne
op_star
id|val
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Restore CRC error at &quot;
l_string|&quot;%08lx (%08x vs %08x)&bslash;n&quot;
comma
id|addr
comma
id|calc
comma
op_star
id|val
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Restore CRC error at %08lx (%08x vs %08x)&bslash;n&quot;
comma
id|addr
comma
id|calc
comma
op_star
id|val
)paren
suffix:semicolon
)brace
id|skip_check
suffix:colon
id|val
op_increment
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* s3c2410_pm_check_restore&n; *&n; * check the CRCs after the restore event and free the memory used&n; * to hold them&n;*/
DECL|function|s3c2410_pm_check_restore
r_static
r_void
id|s3c2410_pm_check_restore
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|crcs
op_ne
l_int|NULL
)paren
(brace
id|s3c2410_pm_run_sysram
c_func
(paren
id|s3c2410_pm_runcheck
comma
id|crcs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|crcs
)paren
suffix:semicolon
id|crcs
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|variable|uart_save
r_static
r_struct
id|sleep_save
id|uart_save
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|s3c2410_pm_check_prepare
mdefine_line|#define s3c2410_pm_check_prepare() do { } while(0)
DECL|macro|s3c2410_pm_check_restore
mdefine_line|#define s3c2410_pm_check_restore() do { } while(0)
DECL|macro|s3c2410_pm_check_store
mdefine_line|#define s3c2410_pm_check_store()   do { } while(0)
macro_line|#endif
multiline_comment|/* helper functions to save and restore register state */
DECL|function|s3c2410_pm_do_save
r_void
id|s3c2410_pm_do_save
c_func
(paren
r_struct
id|sleep_save
op_star
id|ptr
comma
r_int
id|count
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
id|count
op_decrement
comma
id|ptr
op_increment
)paren
(brace
id|ptr-&gt;val
op_assign
id|__raw_readl
c_func
(paren
id|ptr-&gt;reg
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;saved %08lx value %08lx&bslash;n&quot;
comma
id|ptr-&gt;reg
comma
id|ptr-&gt;val
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* s3c2410_pm_do_restore&n; *&n; * restore the system from the given list of saved registers&n; *&n; * Note, we do not use DBG() in here, as the system may not have&n; * restore the UARTs state yet&n;*/
DECL|function|s3c2410_pm_do_restore
r_void
id|s3c2410_pm_do_restore
c_func
(paren
r_struct
id|sleep_save
op_star
id|ptr
comma
r_int
id|count
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
id|count
op_decrement
comma
id|ptr
op_increment
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;restore %08lx (restore %08lx, was %08x)&bslash;n&quot;
comma
id|ptr-&gt;reg
comma
id|ptr-&gt;val
comma
id|__raw_readl
c_func
(paren
id|ptr-&gt;reg
)paren
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|ptr-&gt;val
comma
id|ptr-&gt;reg
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* s3c2410_pm_do_restore_core&n; *&n; * similar to s3c2410_pm_do_restore_core&n; *&n; * WARNING: Do not put any debug in here that may effect memory or use&n; * peripherals, as things may be changing!&n;*/
DECL|function|s3c2410_pm_do_restore_core
r_static
r_void
id|s3c2410_pm_do_restore_core
c_func
(paren
r_struct
id|sleep_save
op_star
id|ptr
comma
r_int
id|count
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
id|count
op_decrement
comma
id|ptr
op_increment
)paren
(brace
id|__raw_writel
c_func
(paren
id|ptr-&gt;val
comma
id|ptr-&gt;reg
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* s3c2410_pm_show_resume_irqs&n; *&n; * print any IRQs asserted at resume time (ie, we woke from)&n;*/
DECL|function|s3c2410_pm_show_resume_irqs
r_static
r_void
id|s3c2410_pm_show_resume_irqs
c_func
(paren
r_int
id|start
comma
r_int
r_int
id|which
comma
r_int
r_int
id|mask
)paren
(brace
r_int
id|i
suffix:semicolon
id|which
op_and_assign
op_complement
id|mask
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|31
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|which
)paren
op_amp
(paren
l_int|1L
op_lshift
id|i
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;IRQ %d asserted at resume&bslash;n&quot;
comma
id|start
op_plus
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* s3c2410_pm_check_resume_pin&n; *&n; * check to see if the pin is configured correctly for sleep mode, and&n; * make any necessary adjustments if it is not&n;*/
DECL|function|s3c2410_pm_check_resume_pin
r_static
r_void
id|s3c2410_pm_check_resume_pin
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|irqoffs
)paren
(brace
r_int
r_int
id|irqstate
suffix:semicolon
r_int
r_int
id|pinstate
suffix:semicolon
r_int
id|irq
op_assign
id|s3c2410_gpio_getirq
c_func
(paren
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqoffs
OL
l_int|4
)paren
id|irqstate
op_assign
id|s3c_irqwake_intmask
op_amp
(paren
l_int|1L
op_lshift
id|irqoffs
)paren
suffix:semicolon
r_else
id|irqstate
op_assign
id|s3c_irqwake_eintmask
op_amp
(paren
l_int|1L
op_lshift
id|irqoffs
)paren
suffix:semicolon
id|pinstate
op_assign
id|s3c2410_gpio_getcfg
c_func
(paren
id|pin
)paren
suffix:semicolon
id|pinstate
op_rshift_assign
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irqstate
)paren
(brace
r_if
c_cond
(paren
id|pinstate
op_eq
l_int|0x02
)paren
id|DBG
c_func
(paren
l_string|&quot;Leaving IRQ %d (pin %d) enabled&bslash;n&quot;
comma
id|irq
comma
id|pin
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pinstate
op_eq
l_int|0x02
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Disabling IRQ %d (pin %d)&bslash;n&quot;
comma
id|irq
comma
id|pin
)paren
suffix:semicolon
id|s3c2410_gpio_cfgpin
c_func
(paren
id|pin
comma
l_int|0x00
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* s3c2410_pm_configure_extint&n; *&n; * configure all external interrupt pins&n;*/
DECL|function|s3c2410_pm_configure_extint
r_static
r_void
id|s3c2410_pm_configure_extint
c_func
(paren
r_void
)paren
(brace
r_int
id|pin
suffix:semicolon
multiline_comment|/* for each of the external interrupts (EINT0..EINT15) we&n;&t; * need to check wether it is an external interrupt source,&n;&t; * and then configure it as an input if it is not&n;&t;*/
r_for
c_loop
(paren
id|pin
op_assign
id|S3C2410_GPF0
suffix:semicolon
id|pin
op_le
id|S3C2410_GPF7
suffix:semicolon
id|pin
op_increment
)paren
(brace
id|s3c2410_pm_check_resume_pin
c_func
(paren
id|pin
comma
id|pin
op_minus
id|S3C2410_GPF0
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|pin
op_assign
id|S3C2410_GPG0
suffix:semicolon
id|pin
op_le
id|S3C2410_GPG7
suffix:semicolon
id|pin
op_increment
)paren
(brace
id|s3c2410_pm_check_resume_pin
c_func
(paren
id|pin
comma
(paren
id|pin
op_minus
id|S3C2410_GPG0
)paren
op_plus
l_int|8
)paren
suffix:semicolon
)brace
)brace
DECL|macro|any_allowed
mdefine_line|#define any_allowed(mask, allow) (((mask) &amp; (allow)) != (allow))
multiline_comment|/* s3c2410_pm_enter&n; *&n; * central control for sleep/resume process&n;*/
DECL|function|s3c2410_pm_enter
r_static
r_int
id|s3c2410_pm_enter
c_func
(paren
id|suspend_state_t
id|state
)paren
(brace
r_int
r_int
id|regs_save
(braket
l_int|16
)braket
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* ensure the debug is initialised (if enabled) */
id|s3c2410_pm_debug_init
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;s3c2410_pm_enter(%d)&bslash;n&quot;
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_ne
id|PM_SUSPEND_MEM
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;error: only PM_SUSPEND_MEM supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* check if we have anything to wake-up with... bad things seem&n;&t; * to happen if you suspend with no wakeup (system will often&n;&t; * require a full power-cycle)&n;&t;*/
r_if
c_cond
(paren
op_logical_neg
id|any_allowed
c_func
(paren
id|s3c_irqwake_intmask
comma
id|s3c_irqwake_intallow
)paren
op_logical_and
op_logical_neg
id|any_allowed
c_func
(paren
id|s3c_irqwake_eintmask
comma
id|s3c_irqwake_eintallow
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;No sources enabled for wake-up!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Aborting sleep&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* prepare check area if configured */
id|s3c2410_pm_check_prepare
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* store the physical address of the register recovery block */
id|s3c2410_sleep_save_phys
op_assign
id|virt_to_phys
c_func
(paren
id|regs_save
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;s3c2410_sleep_save_phys=0x%08lx&bslash;n&quot;
comma
id|s3c2410_sleep_save_phys
)paren
suffix:semicolon
multiline_comment|/* ensure at least GESTATUS3 has the resume address */
id|__raw_writel
c_func
(paren
id|virt_to_phys
c_func
(paren
id|s3c2410_cpu_resume
)paren
comma
id|S3C2410_GSTATUS3
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;GSTATUS3 0x%08x&bslash;n&quot;
comma
id|__raw_readl
c_func
(paren
id|S3C2410_GSTATUS3
)paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;GSTATUS4 0x%08x&bslash;n&quot;
comma
id|__raw_readl
c_func
(paren
id|S3C2410_GSTATUS4
)paren
)paren
suffix:semicolon
multiline_comment|/* save all necessary core registers not covered by the drivers */
id|s3c2410_pm_do_save
c_func
(paren
id|gpio_save
comma
id|ARRAY_SIZE
c_func
(paren
id|gpio_save
)paren
)paren
suffix:semicolon
id|s3c2410_pm_do_save
c_func
(paren
id|irq_save
comma
id|ARRAY_SIZE
c_func
(paren
id|irq_save
)paren
)paren
suffix:semicolon
id|s3c2410_pm_do_save
c_func
(paren
id|core_save
comma
id|ARRAY_SIZE
c_func
(paren
id|core_save
)paren
)paren
suffix:semicolon
id|s3c2410_pm_do_save
c_func
(paren
id|uart_save
comma
id|ARRAY_SIZE
c_func
(paren
id|uart_save
)paren
)paren
suffix:semicolon
multiline_comment|/* set the irq configuration for wake */
id|s3c2410_pm_configure_extint
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;sleep: irq wakeup masks: %08lx,%08lx&bslash;n&quot;
comma
id|s3c_irqwake_intmask
comma
id|s3c_irqwake_eintmask
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|s3c_irqwake_intmask
comma
id|S3C2410_INTMSK
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|s3c_irqwake_eintmask
comma
id|S3C2410_EINTMASK
)paren
suffix:semicolon
multiline_comment|/* ack any outstanding external interrupts before we go to sleep */
id|__raw_writel
c_func
(paren
id|__raw_readl
c_func
(paren
id|S3C2410_EINTPEND
)paren
comma
id|S3C2410_EINTPEND
)paren
suffix:semicolon
multiline_comment|/* flush cache back to ram */
id|arm920_flush_kern_cache_all
c_func
(paren
)paren
suffix:semicolon
id|s3c2410_pm_check_store
c_func
(paren
)paren
suffix:semicolon
singleline_comment|// need to make some form of time-delta
multiline_comment|/* send the cpu to sleep... */
id|__raw_writel
c_func
(paren
l_int|0x00
comma
id|S3C2410_CLKCON
)paren
suffix:semicolon
multiline_comment|/* turn off clocks over sleep */
id|s3c2410_cpu_suspend
c_func
(paren
id|regs_save
)paren
suffix:semicolon
multiline_comment|/* unset the return-from-sleep flag, to ensure reset */
id|tmp
op_assign
id|__raw_readl
c_func
(paren
id|S3C2410_GSTATUS2
)paren
suffix:semicolon
id|tmp
op_and_assign
id|S3C2410_GSTATUS2_OFFRESET
suffix:semicolon
id|__raw_writel
c_func
(paren
id|tmp
comma
id|S3C2410_GSTATUS2
)paren
suffix:semicolon
multiline_comment|/* restore the system state */
id|s3c2410_pm_do_restore_core
c_func
(paren
id|core_save
comma
id|ARRAY_SIZE
c_func
(paren
id|core_save
)paren
)paren
suffix:semicolon
id|s3c2410_pm_do_restore
c_func
(paren
id|gpio_save
comma
id|ARRAY_SIZE
c_func
(paren
id|gpio_save
)paren
)paren
suffix:semicolon
id|s3c2410_pm_do_restore
c_func
(paren
id|irq_save
comma
id|ARRAY_SIZE
c_func
(paren
id|irq_save
)paren
)paren
suffix:semicolon
id|s3c2410_pm_do_restore
c_func
(paren
id|uart_save
comma
id|ARRAY_SIZE
c_func
(paren
id|uart_save
)paren
)paren
suffix:semicolon
id|s3c2410_pm_debug_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* check what irq (if any) restored the system */
id|DBG
c_func
(paren
l_string|&quot;post sleep: IRQs 0x%08x, 0x%08x&bslash;n&quot;
comma
id|__raw_readl
c_func
(paren
id|S3C2410_SRCPND
)paren
comma
id|__raw_readl
c_func
(paren
id|S3C2410_EINTPEND
)paren
)paren
suffix:semicolon
id|s3c2410_pm_show_resume_irqs
c_func
(paren
id|IRQ_EINT0
comma
id|__raw_readl
c_func
(paren
id|S3C2410_SRCPND
)paren
comma
id|s3c_irqwake_intmask
)paren
suffix:semicolon
id|s3c2410_pm_show_resume_irqs
c_func
(paren
id|IRQ_EINT4
op_minus
l_int|4
comma
id|__raw_readl
c_func
(paren
id|S3C2410_EINTPEND
)paren
comma
id|s3c_irqwake_eintmask
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;post sleep, preparing to return&bslash;n&quot;
)paren
suffix:semicolon
id|s3c2410_pm_check_restore
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ok, let&squot;s return from sleep */
id|DBG
c_func
(paren
l_string|&quot;S3C2410 PM Resume (post-restore)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called after processes are frozen, but before we shut down devices.&n; */
DECL|function|s3c2410_pm_prepare
r_static
r_int
id|s3c2410_pm_prepare
c_func
(paren
id|suspend_state_t
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called after devices are re-setup, but before processes are thawed.&n; */
DECL|function|s3c2410_pm_finish
r_static
r_int
id|s3c2410_pm_finish
c_func
(paren
id|suspend_state_t
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set to PM_DISK_FIRMWARE so we can quickly veto suspend-to-disk.&n; */
DECL|variable|s3c2410_pm_ops
r_static
r_struct
id|pm_ops
id|s3c2410_pm_ops
op_assign
(brace
dot
id|pm_disk_mode
op_assign
id|PM_DISK_FIRMWARE
comma
dot
id|prepare
op_assign
id|s3c2410_pm_prepare
comma
dot
id|enter
op_assign
id|s3c2410_pm_enter
comma
dot
id|finish
op_assign
id|s3c2410_pm_finish
comma
)brace
suffix:semicolon
multiline_comment|/* s3c2410_pm_init&n; *&n; * Attach the power management functions. This should be called&n; * from the board specific initialisation if the board supports&n; * it.&n;*/
DECL|function|s3c2410_pm_init
r_int
id|__init
id|s3c2410_pm_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;S3C2410 Power Management, (c) 2004 Simtec Electronics&bslash;n&quot;
)paren
suffix:semicolon
id|pm_set_ops
c_func
(paren
op_amp
id|s3c2410_pm_ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
