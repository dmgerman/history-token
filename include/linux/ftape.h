macro_line|#ifndef _FTAPE_H
DECL|macro|_FTAPE_H
mdefine_line|#define _FTAPE_H
multiline_comment|/*&n; * Copyright (C) 1994-1996 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/include/linux/ftape.h,v $&n; * $Revision: 1.17.6.4 $&n; * $Date: 1997/11/25 01:52:54 $&n; *&n; *      This file contains global definitions, typedefs and macro&squot;s&n; *      for the QIC-40/80/3010/3020 floppy-tape driver for Linux.&n; */
DECL|macro|FTAPE_VERSION
mdefine_line|#define FTAPE_VERSION &quot;ftape v3.04d 25/11/97&quot;
multiline_comment|/* this makes the Kernel version numbers readable */
DECL|macro|KERNEL_VER
mdefine_line|#define KERNEL_VER(major,minor,sublvl) (((major)&lt;&lt;16)+((minor)&lt;&lt;8)+(sublvl))
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
DECL|macro|FT_SECTOR
mdefine_line|#define FT_SECTOR(x)&t;&t;(x+1)&t;/* sector offset into real sector */
DECL|macro|FT_SECTOR_SIZE
mdefine_line|#define FT_SECTOR_SIZE&t;&t;1024
DECL|macro|FT_SECTORS_PER_SEGMENT
mdefine_line|#define FT_SECTORS_PER_SEGMENT&t;  32
DECL|macro|FT_ECC_SECTORS
mdefine_line|#define FT_ECC_SECTORS&t;&t;   3
DECL|macro|FT_SEGMENT_SIZE
mdefine_line|#define FT_SEGMENT_SIZE&t;&t;((FT_SECTORS_PER_SEGMENT - FT_ECC_SECTORS) * FT_SECTOR_SIZE)
DECL|macro|FT_BUFF_SIZE
mdefine_line|#define FT_BUFF_SIZE    (FT_SECTORS_PER_SEGMENT * FT_SECTOR_SIZE)
multiline_comment|/*&n; *   bits of the minor device number that define drive selection&n; *   methods. Could be used one day to access multiple tape&n; *   drives on the same controller.&n; */
DECL|macro|FTAPE_SEL_A
mdefine_line|#define FTAPE_SEL_A     0
DECL|macro|FTAPE_SEL_B
mdefine_line|#define FTAPE_SEL_B     1
DECL|macro|FTAPE_SEL_C
mdefine_line|#define FTAPE_SEL_C     2
DECL|macro|FTAPE_SEL_D
mdefine_line|#define FTAPE_SEL_D     3
DECL|macro|FTAPE_SEL_MASK
mdefine_line|#define FTAPE_SEL_MASK     3
DECL|macro|FTAPE_SEL
mdefine_line|#define FTAPE_SEL(unit) ((unit) &amp; FTAPE_SEL_MASK)
DECL|macro|FTAPE_NO_REWIND
mdefine_line|#define FTAPE_NO_REWIND 4&t;/* mask for minor nr */
multiline_comment|/* the following two may be reported when MTIOCGET is requested ... */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|error
id|__u8
id|error
suffix:semicolon
DECL|member|command
id|__u8
id|command
suffix:semicolon
DECL|member|error
)brace
id|error
suffix:semicolon
DECL|member|space
r_int
id|space
suffix:semicolon
DECL|typedef|ft_drive_error
)brace
id|ft_drive_error
suffix:semicolon
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|drive_status
id|__u8
id|drive_status
suffix:semicolon
DECL|member|drive_config
id|__u8
id|drive_config
suffix:semicolon
DECL|member|tape_status
id|__u8
id|tape_status
suffix:semicolon
DECL|member|status
)brace
id|status
suffix:semicolon
DECL|member|space
r_int
id|space
suffix:semicolon
DECL|typedef|ft_drive_status
)brace
id|ft_drive_status
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|FT_RQM_DELAY
mdefine_line|#define FT_RQM_DELAY    12
DECL|macro|FT_MILLISECOND
mdefine_line|#define FT_MILLISECOND  1
DECL|macro|FT_SECOND
mdefine_line|#define FT_SECOND       1000
DECL|macro|FT_FOREVER
mdefine_line|#define FT_FOREVER      -1
macro_line|#ifndef HZ
macro_line|#error &quot;HZ undefined.&quot;
macro_line|#endif
DECL|macro|FT_USPT
mdefine_line|#define FT_USPT         (1000000/HZ) /* microseconds per tick */
multiline_comment|/* This defines the number of retries that the driver will allow&n; * before giving up (and letting a higher level handle the error).&n; */
macro_line|#ifdef TESTING
DECL|macro|FT_SOFT_RETRIES
mdefine_line|#define FT_SOFT_RETRIES 1&t;   /* number of low level retries */
DECL|macro|FT_RETRIES_ON_ECC_ERROR
mdefine_line|#define FT_RETRIES_ON_ECC_ERROR 3  /* ecc error when correcting segment */
macro_line|#else
DECL|macro|FT_SOFT_RETRIES
mdefine_line|#define FT_SOFT_RETRIES 6&t;   /* number of low level retries (triple) */
DECL|macro|FT_RETRIES_ON_ECC_ERROR
mdefine_line|#define FT_RETRIES_ON_ECC_ERROR 3  /* ecc error when correcting segment */
macro_line|#endif
macro_line|#ifndef THE_FTAPE_MAINTAINER
DECL|macro|THE_FTAPE_MAINTAINER
mdefine_line|#define THE_FTAPE_MAINTAINER &quot;the ftape maintainer&quot;
macro_line|#endif
multiline_comment|/* Initialize missing configuration parameters.&n; */
macro_line|#ifndef CONFIG_FT_NR_BUFFERS
DECL|macro|CONFIG_FT_NR_BUFFERS
macro_line|# define CONFIG_FT_NR_BUFFERS 3
macro_line|#endif
macro_line|#ifndef CONFIG_FT_FDC_THR
DECL|macro|CONFIG_FT_FDC_THR
macro_line|# define CONFIG_FT_FDC_THR 8
macro_line|#endif
macro_line|#ifndef CONFIG_FT_FDC_MAX_RATE
DECL|macro|CONFIG_FT_FDC_MAX_RATE
macro_line|# define CONFIG_FT_FDC_MAX_RATE 2000
macro_line|#endif
macro_line|#ifndef CONFIG_FT_FDC_BASE
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|# define CONFIG_FT_FDC_BASE 0
macro_line|#endif
macro_line|#ifndef CONFIG_FT_FDC_IRQ
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|# define CONFIG_FT_FDC_IRQ  0
macro_line|#endif
macro_line|#ifndef CONFIG_FT_FDC_DMA
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|# define CONFIG_FT_FDC_DMA  0
macro_line|#endif
multiline_comment|/* Turn some booleans into numbers.&n; */
macro_line|#ifdef CONFIG_FT_PROBE_FC10
DECL|macro|CONFIG_FT_PROBE_FC10
macro_line|# undef CONFIG_FT_PROBE_FC10
DECL|macro|CONFIG_FT_PROBE_FC10
macro_line|# define CONFIG_FT_PROBE_FC10 1
macro_line|#else
DECL|macro|CONFIG_FT_PROBE_FC10
macro_line|# define CONFIG_FT_PROBE_FC10 0
macro_line|#endif
macro_line|#ifdef CONFIG_FT_MACH2
DECL|macro|CONFIG_FT_MACH2
macro_line|# undef CONFIG_FT_MACH2
DECL|macro|CONFIG_FT_MACH2
macro_line|# define CONFIG_FT_MACH2 1
macro_line|#else
DECL|macro|CONFIG_FT_MACH2
macro_line|# define CONFIG_FT_MACH2 0
macro_line|#endif
multiline_comment|/* Insert default settings&n; */
macro_line|#if CONFIG_FT_PROBE_FC10 == 1
macro_line|# if CONFIG_FT_FDC_BASE == 0
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  undef  CONFIG_FT_FDC_BASE
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  define CONFIG_FT_FDC_BASE 0x180
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_IRQ == 0
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  undef  CONFIG_FT_FDC_IRQ
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  define CONFIG_FT_FDC_IRQ 9
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_DMA == 0
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  undef  CONFIG_FT_FDC_DMA
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  define CONFIG_FT_FDC_DMA 3
macro_line|# endif
macro_line|#elif CONFIG_FT_MACH2 == 1    /* CONFIG_FT_PROBE_FC10 == 1 */
macro_line|# if CONFIG_FT_FDC_BASE == 0
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  undef  CONFIG_FT_FDC_BASE
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  define CONFIG_FT_FDC_BASE 0x1E0
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_IRQ == 0
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  undef  CONFIG_FT_FDC_IRQ
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  define CONFIG_FT_FDC_IRQ 6
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_DMA == 0
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  undef  CONFIG_FT_FDC_DMA
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  define CONFIG_FT_FDC_DMA 2
macro_line|# endif
macro_line|#elif CONFIG_FT_ALT_FDC == 1  /* CONFIG_FT_MACH2 */
macro_line|# if CONFIG_FT_FDC_BASE == 0
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  undef  CONFIG_FT_FDC_BASE
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  define CONFIG_FT_FDC_BASE 0x370
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_IRQ == 0
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  undef  CONFIG_FT_FDC_IRQ
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  define CONFIG_FT_FDC_IRQ 6
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_DMA == 0
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  undef  CONFIG_FT_FDC_DMA
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  define CONFIG_FT_FDC_DMA 2
macro_line|# endif
macro_line|#else                          /* CONFIG_FT_ALT_FDC */
macro_line|# if CONFIG_FT_FDC_BASE == 0
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  undef  CONFIG_FT_FDC_BASE
DECL|macro|CONFIG_FT_FDC_BASE
macro_line|#  define CONFIG_FT_FDC_BASE 0x3f0
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_IRQ == 0
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  undef  CONFIG_FT_FDC_IRQ
DECL|macro|CONFIG_FT_FDC_IRQ
macro_line|#  define CONFIG_FT_FDC_IRQ 6
macro_line|# endif
macro_line|# if CONFIG_FT_FDC_DMA == 0
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  undef  CONFIG_FT_FDC_DMA
DECL|macro|CONFIG_FT_FDC_DMA
macro_line|#  define CONFIG_FT_FDC_DMA 2
macro_line|# endif
macro_line|#endif                         /* standard FDC */
multiline_comment|/*      some useful macro&squot;s&n; */
DECL|macro|ABS
mdefine_line|#define ABS(a)          ((a) &lt; 0 ? -(a) : (a))
DECL|macro|NR_ITEMS
mdefine_line|#define NR_ITEMS(x)     (int)(sizeof(x)/ sizeof(*x))
r_extern
r_int
id|ftape_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif
eof
