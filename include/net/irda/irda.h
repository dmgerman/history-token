multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda.h&n; * Version:       1.0&n; * Description:   IrDA common include file for kernel internal use&n; * Status:        Stable&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Dec  9 21:13:12 1997&n; * Modified at:   Fri Jan 28 13:16:32 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-2000 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2002 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef NET_IRDA_H
DECL|macro|NET_IRDA_H
mdefine_line|#define NET_IRDA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;&t;&t;/* struct sk_buff */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/if.h&gt;&t;&t;&t;/* sa_family_t in &lt;linux/irda.h&gt; */
macro_line|#include &lt;linux/irda.h&gt;
DECL|typedef|magic_t
r_typedef
id|__u32
id|magic_t
suffix:semicolon
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE 
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
multiline_comment|/* Hack to do small backoff when setting media busy in IrLAP */
macro_line|#ifndef SMALL
DECL|macro|SMALL
mdefine_line|#define SMALL 5
macro_line|#endif
macro_line|#ifndef IRDA_MIN /* Lets not mix this MIN with other header files */
DECL|macro|IRDA_MIN
mdefine_line|#define IRDA_MIN(a, b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef IRDA_ALIGN
DECL|macro|IRDA_ALIGN
macro_line|#  define IRDA_ALIGN __attribute__((aligned))
macro_line|#endif
macro_line|#ifndef IRDA_PACK
DECL|macro|IRDA_PACK
macro_line|#  define IRDA_PACK __attribute__((packed))
macro_line|#endif
macro_line|#ifdef CONFIG_IRDA_DEBUG
r_extern
id|__u32
id|irda_debug
suffix:semicolon
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
DECL|macro|IRDA_DEBUG_LEVEL
mdefine_line|#define IRDA_DEBUG_LEVEL 0
DECL|macro|IRDA_DEBUG
mdefine_line|#define IRDA_DEBUG(n, args...) (irda_debug &gt;= (n)) ? (printk(KERN_DEBUG args)) : 0
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr, func) &bslash;&n;if(!(expr)) { &bslash;&n;        printk( &quot;Assertion failed! %s:%s:%d %s&bslash;n&quot;, &bslash;&n;        __FILE__,__FUNCTION__,__LINE__,(#expr));  &bslash;&n;        func }
macro_line|#else
DECL|macro|IRDA_DEBUG
mdefine_line|#define IRDA_DEBUG(n, args...)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr, func) &bslash;&n;if(!(expr)) do { &bslash;&n;        func } while (0)
macro_line|#endif /* CONFIG_IRDA_DEBUG */
DECL|macro|WARNING
mdefine_line|#define WARNING(args...) printk(KERN_WARNING args)
DECL|macro|MESSAGE
mdefine_line|#define MESSAGE(args...) printk(KERN_INFO args)
DECL|macro|ERROR
mdefine_line|#define ERROR(args...)   printk(KERN_ERR args)
DECL|macro|MSECS_TO_JIFFIES
mdefine_line|#define MSECS_TO_JIFFIES(ms) (((ms)*HZ+999)/1000)
multiline_comment|/*&n; *  Magic numbers used by Linux-IrDA. Random numbers which must be unique to &n; *  give the best protection&n; */
DECL|macro|IRTTY_MAGIC
mdefine_line|#define IRTTY_MAGIC        0x2357
DECL|macro|LAP_MAGIC
mdefine_line|#define LAP_MAGIC          0x1357
DECL|macro|LMP_MAGIC
mdefine_line|#define LMP_MAGIC          0x4321
DECL|macro|LMP_LSAP_MAGIC
mdefine_line|#define LMP_LSAP_MAGIC     0x69333
DECL|macro|LMP_LAP_MAGIC
mdefine_line|#define LMP_LAP_MAGIC      0x3432
DECL|macro|IRDA_DEVICE_MAGIC
mdefine_line|#define IRDA_DEVICE_MAGIC  0x63454
DECL|macro|IAS_MAGIC
mdefine_line|#define IAS_MAGIC          0x007
DECL|macro|TTP_MAGIC
mdefine_line|#define TTP_MAGIC          0x241169
DECL|macro|TTP_TSAP_MAGIC
mdefine_line|#define TTP_TSAP_MAGIC     0x4345
DECL|macro|IROBEX_MAGIC
mdefine_line|#define IROBEX_MAGIC       0x341324
DECL|macro|HB_MAGIC
mdefine_line|#define HB_MAGIC           0x64534
DECL|macro|IRLAN_MAGIC
mdefine_line|#define IRLAN_MAGIC        0x754
DECL|macro|IAS_OBJECT_MAGIC
mdefine_line|#define IAS_OBJECT_MAGIC   0x34234
DECL|macro|IAS_ATTRIB_MAGIC
mdefine_line|#define IAS_ATTRIB_MAGIC   0x45232
DECL|macro|IRDA_TASK_MAGIC
mdefine_line|#define IRDA_TASK_MAGIC    0x38423
DECL|macro|IAS_DEVICE_ID
mdefine_line|#define IAS_DEVICE_ID 0x0000 /* Defined by IrDA, IrLMP section 4.1 (page 68) */
DECL|macro|IAS_PNP_ID
mdefine_line|#define IAS_PNP_ID    0xd342
DECL|macro|IAS_OBEX_ID
mdefine_line|#define IAS_OBEX_ID   0x34323
DECL|macro|IAS_IRLAN_ID
mdefine_line|#define IAS_IRLAN_ID  0x34234
DECL|macro|IAS_IRCOMM_ID
mdefine_line|#define IAS_IRCOMM_ID 0x2343
DECL|macro|IAS_IRLPT_ID
mdefine_line|#define IAS_IRLPT_ID  0x9876
macro_line|#endif /* NET_IRDA_H */
eof
