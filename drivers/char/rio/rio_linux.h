multiline_comment|/*&n; *  rio_linux.h&n; *&n; *  Copyright (C) 1998,1999,2000 R.E.Wolff@BitWizard.nl&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  RIO serial driver.&n; *&n; *  Version 1.0 -- July, 1999. &n; * &n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|RIO_NBOARDS
mdefine_line|#define RIO_NBOARDS        4
DECL|macro|RIO_PORTSPERBOARD
mdefine_line|#define RIO_PORTSPERBOARD 128
DECL|macro|RIO_NPORTS
mdefine_line|#define RIO_NPORTS        (RIO_NBOARDS * RIO_PORTSPERBOARD)
DECL|macro|MODEM_SUPPORT
mdefine_line|#define MODEM_SUPPORT
macro_line|#ifdef __KERNEL__
DECL|macro|RIO_MAGIC
mdefine_line|#define RIO_MAGIC 0x12345678
DECL|struct|vpd_prom
r_struct
id|vpd_prom
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|hwrev
r_char
id|hwrev
suffix:semicolon
DECL|member|hwass
r_char
id|hwass
suffix:semicolon
DECL|member|uniqid
r_int
id|uniqid
suffix:semicolon
DECL|member|myear
r_char
id|myear
suffix:semicolon
DECL|member|mweek
r_char
id|mweek
suffix:semicolon
DECL|member|hw_feature
r_char
id|hw_feature
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|oem_id
r_char
id|oem_id
suffix:semicolon
DECL|member|identifier
r_char
id|identifier
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RIO_DEBUG_ALL
mdefine_line|#define RIO_DEBUG_ALL           0xffffffff
DECL|macro|O_OTHER
mdefine_line|#define O_OTHER(tty)    &bslash;&n;      ((O_OLCUC(tty))  ||&bslash;&n;      (O_ONLCR(tty))   ||&bslash;&n;      (O_OCRNL(tty))   ||&bslash;&n;      (O_ONOCR(tty))   ||&bslash;&n;      (O_ONLRET(tty))  ||&bslash;&n;      (O_OFILL(tty))   ||&bslash;&n;      (O_OFDEL(tty))   ||&bslash;&n;      (O_NLDLY(tty))   ||&bslash;&n;      (O_CRDLY(tty))   ||&bslash;&n;      (O_TABDLY(tty))  ||&bslash;&n;      (O_BSDLY(tty))   ||&bslash;&n;      (O_VTDLY(tty))   ||&bslash;&n;      (O_FFDLY(tty)))
multiline_comment|/* Same for input. */
DECL|macro|I_OTHER
mdefine_line|#define I_OTHER(tty)    &bslash;&n;      ((I_INLCR(tty))  ||&bslash;&n;      (I_IGNCR(tty))   ||&bslash;&n;      (I_ICRNL(tty))   ||&bslash;&n;      (I_IUCLC(tty))   ||&bslash;&n;      (L_ISIG(tty)))
macro_line|#endif /* __KERNEL__ */
DECL|macro|RIO_BOARD_INTR_LOCK
mdefine_line|#define RIO_BOARD_INTR_LOCK  1
macro_line|#ifndef RIOCTL_MISC_MINOR 
multiline_comment|/* Allow others to gather this into &quot;major.h&quot; or something like that */
DECL|macro|RIOCTL_MISC_MINOR
mdefine_line|#define RIOCTL_MISC_MINOR    169
macro_line|#endif
r_void
id|rio_dec_mod_count
(paren
r_void
)paren
suffix:semicolon
r_void
id|rio_inc_mod_count
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Allow us to debug &quot;in the field&quot; without requiring clients to&n;   recompile.... */
macro_line|#if 1
DECL|macro|rio_spin_lock_irqsave
mdefine_line|#define rio_spin_lock_irqsave(sem, flags) do { &bslash;&n;&t;rio_dprintk (RIO_DEBUG_SPINLOCK, &quot;spinlockirqsave: %p %s:%d&bslash;n&quot;, &bslash;&n;&t;                                sem, __FILE__, __LINE__);&bslash;&n;&t;spin_lock_irqsave(sem, flags);&bslash;&n;&t;} while (0)
DECL|macro|rio_spin_unlock_irqrestore
mdefine_line|#define rio_spin_unlock_irqrestore(sem, flags) do { &bslash;&n;&t;rio_dprintk (RIO_DEBUG_SPINLOCK, &quot;spinunlockirqrestore: %p %s:%d&bslash;n&quot;,&bslash;&n;&t;                                sem, __FILE__, __LINE__);&bslash;&n;&t;spin_unlock_irqrestore(sem, flags);&bslash;&n;&t;} while (0)
DECL|macro|rio_spin_lock
mdefine_line|#define rio_spin_lock(sem) do { &bslash;&n;&t;rio_dprintk (RIO_DEBUG_SPINLOCK, &quot;spinlock: %p %s:%d&bslash;n&quot;,&bslash;&n;&t;                                sem, __FILE__, __LINE__);&bslash;&n;&t;spin_lock(sem);&bslash;&n;&t;} while (0)
DECL|macro|rio_spin_unlock
mdefine_line|#define rio_spin_unlock(sem) do { &bslash;&n;&t;rio_dprintk (RIO_DEBUG_SPINLOCK, &quot;spinunlock: %p %s:%d&bslash;n&quot;,&bslash;&n;&t;                                sem, __FILE__, __LINE__);&bslash;&n;&t;spin_unlock(sem);&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|rio_spin_lock_irqsave
mdefine_line|#define rio_spin_lock_irqsave(sem, flags) &bslash;&n;            spin_lock_irqsave(sem, flags)
DECL|macro|rio_spin_unlock_irqrestore
mdefine_line|#define rio_spin_unlock_irqrestore(sem, flags) &bslash;&n;            spin_unlock_irqrestore(sem, flags)
DECL|macro|rio_spin_lock
mdefine_line|#define rio_spin_lock(sem) &bslash;&n;            spin_lock(sem) 
DECL|macro|rio_spin_unlock
mdefine_line|#define rio_spin_unlock(sem) &bslash;&n;            spin_unlock(sem) 
macro_line|#endif
macro_line|#ifdef CONFIG_RIO_OLDPCI
DECL|function|rio_memcpy_toio
r_static
r_inline
r_void
op_star
id|rio_memcpy_toio
(paren
r_void
op_star
id|dummy
comma
r_void
op_star
id|dest
comma
r_void
op_star
id|source
comma
r_int
id|n
)paren
(brace
r_char
op_star
id|dst
op_assign
id|dest
suffix:semicolon
r_char
op_star
id|src
op_assign
id|source
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|writeb
(paren
op_star
id|src
op_increment
comma
id|dst
op_increment
)paren
suffix:semicolon
(paren
r_void
)paren
id|readb
(paren
id|dummy
)paren
suffix:semicolon
)brace
r_return
id|dest
suffix:semicolon
)brace
DECL|function|rio_memcpy_fromio
r_static
r_inline
r_void
op_star
id|rio_memcpy_fromio
(paren
r_void
op_star
id|dest
comma
r_void
op_star
id|source
comma
r_int
id|n
)paren
(brace
r_char
op_star
id|dst
op_assign
id|dest
suffix:semicolon
r_char
op_star
id|src
op_assign
id|source
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
op_star
id|dst
op_increment
op_assign
id|readb
(paren
id|src
op_increment
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
macro_line|#else
DECL|macro|rio_memcpy_toio
mdefine_line|#define rio_memcpy_toio(dummy,dest,source,n)   memcpy_toio(dest, source, n)
DECL|macro|rio_memcpy_fromio
mdefine_line|#define rio_memcpy_fromio                      memcpy_fromio
macro_line|#endif
DECL|macro|DEBUG
mdefine_line|#define DEBUG 1
multiline_comment|/* &n;   This driver can spew a whole lot of debugging output at you. If you&n;   need maximum performance, you should disable the DEBUG define. To&n;   aid in debugging in the field, I&squot;m leaving the compile-time debug&n;   features enabled, and disable them &quot;runtime&quot;. That allows me to&n;   instruct people with problems to enable debugging without requiring&n;   them to recompile... &n;*/
macro_line|#ifdef DEBUG
DECL|macro|rio_dprintk
mdefine_line|#define rio_dprintk(f, str...) do { if (rio_debug &amp; f) printk (str);} while (0)
DECL|macro|func_enter
mdefine_line|#define func_enter() rio_dprintk (RIO_DEBUG_FLOW, &quot;rio: enter &quot; __FUNCTION__ &quot;&bslash;n&quot;)
DECL|macro|func_exit
mdefine_line|#define func_exit()  rio_dprintk (RIO_DEBUG_FLOW, &quot;rio: exit  &quot; __FUNCTION__ &quot;&bslash;n&quot;)
DECL|macro|func_enter2
mdefine_line|#define func_enter2() rio_dprintk (RIO_DEBUG_FLOW, &quot;rio: enter &quot; __FUNCTION__ &bslash;&n;                                   &quot;(port %d)&bslash;n&quot;, port-&gt;line)
macro_line|#else
DECL|macro|rio_dprintk
mdefine_line|#define rio_dprintk(f, str...) /* nothing */
DECL|macro|func_enter
mdefine_line|#define func_enter()
DECL|macro|func_exit
mdefine_line|#define func_exit()
DECL|macro|func_enter2
mdefine_line|#define func_enter2()
macro_line|#endif
eof
