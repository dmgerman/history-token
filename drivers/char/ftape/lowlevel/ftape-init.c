multiline_comment|/*&n; *      Copyright (C) 1993-1996 Bas Laarhoven,&n; *                (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; *      This file contains the code that interfaces the kernel&n; *      for the QIC-40/80/3010/3020 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VER(2,1,16)
macro_line|#include &lt;linux/init.h&gt;
macro_line|#else
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arg) __arg
macro_line|#endif
macro_line|#include &lt;linux/qic117.h&gt;
macro_line|#ifdef CONFIG_ZFTAPE
macro_line|#include &lt;linux/zftape.h&gt;
macro_line|#endif
macro_line|#include &quot;../lowlevel/ftape-init.h&quot;
macro_line|#include &quot;../lowlevel/ftape_syms.h&quot;
macro_line|#include &quot;../lowlevel/ftape-io.h&quot;
macro_line|#include &quot;../lowlevel/ftape-read.h&quot;
macro_line|#include &quot;../lowlevel/ftape-write.h&quot;
macro_line|#include &quot;../lowlevel/ftape-ctl.h&quot;
macro_line|#include &quot;../lowlevel/ftape-rw.h&quot;
macro_line|#include &quot;../lowlevel/fdc-io.h&quot;
macro_line|#include &quot;../lowlevel/ftape-buffer.h&quot;
macro_line|#include &quot;../lowlevel/ftape-proc.h&quot;
macro_line|#include &quot;../lowlevel/ftape-tracing.h&quot;
multiline_comment|/*      Global vars.&n; */
DECL|variable|__initdata
r_char
id|ft_src
(braket
)braket
id|__initdata
op_assign
l_string|&quot;$Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-init.c,v $&quot;
suffix:semicolon
DECL|variable|__initdata
r_char
id|ft_rev
(braket
)braket
id|__initdata
op_assign
l_string|&quot;$Revision: 1.8 $&quot;
suffix:semicolon
DECL|variable|__initdata
r_char
id|ft_dat
(braket
)braket
id|__initdata
op_assign
l_string|&quot;$Date: 1997/11/06 00:38:08 $&quot;
suffix:semicolon
multiline_comment|/*  Called by modules package when installing the driver&n; *  or by kernel during the initialization phase&n; */
DECL|function|ftape_init
r_int
id|__init
id|ftape_init
c_func
(paren
r_void
)paren
(brace
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_INFO
id|FTAPE_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TRACE_LEVEL
op_ge
id|ft_t_info
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(c) 1993-1996 Bas Laarhoven (bas@vimec.nl)&bslash;n&quot;
id|KERN_INFO
l_string|&quot;(c) 1995-1996 Kai Harrekilde-Petersen (khp@dolphinics.no)&bslash;n&quot;
id|KERN_INFO
l_string|&quot;(c) 1996-1997 Claus-Justus Heine (claus@momo.math.rwth-aachen.de)&bslash;n&quot;
id|KERN_INFO
l_string|&quot;QIC-117 driver for QIC-40/80/3010/3020 floppy tape drives&bslash;n&quot;
id|KERN_INFO
l_string|&quot;Compiled for Linux version %s&quot;
macro_line|#ifdef MODVERSIONS
l_string|&quot; with versioned symbols&quot;
macro_line|#endif
l_string|&quot;&bslash;n&quot;
comma
id|UTS_RELEASE
)paren
suffix:semicolon
)brace
macro_line|#else /* !MODULE */
multiline_comment|/* print a short no-nonsense boot message */
id|printk
c_func
(paren
id|KERN_INFO
id|FTAPE_VERSION
l_string|&quot; for Linux &quot;
id|UTS_RELEASE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;installing QIC-117 floppy tape hardware drive ... &quot;
)paren
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;ftape_init @ 0x%p&quot;
comma
id|ftape_init
)paren
suffix:semicolon
multiline_comment|/*  Allocate the DMA buffers. They are deallocated at cleanup() time.&n;&t; */
macro_line|#if TESTING
macro_line|#ifdef MODULE
r_while
c_loop
(paren
id|ftape_set_nr_buffers
c_func
(paren
id|CONFIG_FT_NR_BUFFERS
)paren
OL
l_int|0
)paren
(brace
id|ftape_sleep
c_func
(paren
id|FT_SECOND
op_div
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
(paren
r_void
)paren
id|ftape_set_nr_buffers
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_bug
comma
l_string|&quot;Killed by signal while allocating buffers.&quot;
)paren
suffix:semicolon
id|TRACE_ABORT
c_func
(paren
op_minus
id|EINTR
comma
id|ft_t_bug
comma
l_string|&quot;Free up memory and retry&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
id|TRACE_CATCH
c_func
(paren
id|ftape_set_nr_buffers
c_func
(paren
id|CONFIG_FT_NR_BUFFERS
)paren
comma
(paren
r_void
)paren
id|ftape_set_nr_buffers
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
id|TRACE_CATCH
c_func
(paren
id|ftape_set_nr_buffers
c_func
(paren
id|CONFIG_FT_NR_BUFFERS
)paren
comma
(paren
r_void
)paren
id|ftape_set_nr_buffers
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
id|ft_drive_sel
op_assign
op_minus
l_int|1
suffix:semicolon
id|ft_failure
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* inhibit any operation but open */
id|ftape_udelay_calibrate
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* must be before fdc_wait_calibrate ! */
id|fdc_wait_calibrate
c_func
(paren
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,18)
id|register_symtab
c_func
(paren
op_amp
id|ftape_symbol_table
)paren
suffix:semicolon
multiline_comment|/* add global ftape symbols */
macro_line|#endif
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_FT_PROC_FS)
(paren
r_void
)paren
id|ftape_proc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ZFTAPE
(paren
r_void
)paren
id|zft_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
macro_line|#ifndef CONFIG_FT_NO_TRACE_AT_ALL
DECL|variable|ft_tracing
r_static
r_int
id|ft_tracing
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VER(2,1,18)
DECL|macro|FT_MOD_PARM
mdefine_line|#define FT_MOD_PARM(var,type,desc) &bslash;&n;&t;MODULE_PARM(var,type); MODULE_PARM_DESC(var,desc)
id|FT_MOD_PARM
c_func
(paren
id|ft_fdc_base
comma
l_string|&quot;i&quot;
comma
l_string|&quot;Base address of FDC controller.&quot;
)paren
suffix:semicolon
id|FT_MOD_PARM
c_func
(paren
id|ft_fdc_irq
comma
l_string|&quot;i&quot;
comma
l_string|&quot;IRQ (interrupt channel) to use.&quot;
)paren
suffix:semicolon
id|FT_MOD_PARM
c_func
(paren
id|ft_fdc_dma
comma
l_string|&quot;i&quot;
comma
l_string|&quot;DMA channel to use.&quot;
)paren
suffix:semicolon
id|FT_MOD_PARM
c_func
(paren
id|ft_fdc_threshold
comma
l_string|&quot;i&quot;
comma
l_string|&quot;Threshold of the FDC Fifo.&quot;
)paren
suffix:semicolon
id|FT_MOD_PARM
c_func
(paren
id|ft_fdc_rate_limit
comma
l_string|&quot;i&quot;
comma
l_string|&quot;Maximal data rate for FDC.&quot;
)paren
suffix:semicolon
id|FT_MOD_PARM
c_func
(paren
id|ft_probe_fc10
comma
l_string|&quot;i&quot;
comma
l_string|&quot;If non-zero, probe for a Colorado FC-10/FC-20 controller.&quot;
)paren
suffix:semicolon
id|FT_MOD_PARM
c_func
(paren
id|ft_mach2
comma
l_string|&quot;i&quot;
comma
l_string|&quot;If non-zero, probe for a Mountain MACH-2 controller.&quot;
)paren
suffix:semicolon
id|FT_MOD_PARM
c_func
(paren
id|ft_tracing
comma
l_string|&quot;i&quot;
comma
l_string|&quot;Amount of debugging output, 0 &lt;= tracing &lt;= 8, default 3.&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;(c) 1993-1996 Bas Laarhoven (bas@vimec.nl), &quot;
l_string|&quot;(c) 1995-1996 Kai Harrekilde-Petersen (khp@dolphinics.no), &quot;
l_string|&quot;(c) 1996, 1997 Claus-Justus Heine (claus@momo.math.rwth-aachen.de)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;QIC-117 driver for QIC-40/80/3010/3020 floppy tape drives.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*  Called by modules package when installing the driver&n; */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_FT_NO_TRACE_AT_ALL
r_if
c_cond
(paren
id|ft_tracing
op_ne
op_minus
l_int|1
)paren
(brace
id|ftape_tracing
op_assign
id|ft_tracing
suffix:semicolon
)brace
macro_line|#endif
r_return
id|ftape_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*  Called by modules package when removing the driver&n; */
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_FT_PROC_FS)
id|ftape_proc_destroy
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
(paren
r_void
)paren
id|ftape_set_nr_buffers
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ftape: unloaded.&bslash;n&quot;
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
