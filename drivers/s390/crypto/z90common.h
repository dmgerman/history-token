multiline_comment|/*&n; *  linux/drivers/s390/misc/z90common.h&n; *&n; *  z90crypt 1.3.1&n; *&n; *  Copyright (C)  2001, 2004 IBM Corporation&n; *  Author(s): Robert Burroughs (burrough@us.ibm.com)&n; *&t;       Eric Rossman (edrossma@us.ibm.com)&n; *&n; *  Hotplug &amp; misc device support: Jochen Roehrig (roehrig@de.ibm.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&t; See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _Z90COMMON_
DECL|macro|_Z90COMMON_
mdefine_line|#define _Z90COMMON_
DECL|macro|VERSION_Z90COMMON_H
mdefine_line|#define VERSION_Z90COMMON_H &quot;$Revision: 1.8 $&quot;
DECL|macro|RESPBUFFSIZE
mdefine_line|#define RESPBUFFSIZE 256
DECL|macro|PCI_FUNC_KEY_DECRYPT
mdefine_line|#define PCI_FUNC_KEY_DECRYPT 0x5044
DECL|macro|PCI_FUNC_KEY_ENCRYPT
mdefine_line|#define PCI_FUNC_KEY_ENCRYPT 0x504B
DECL|enum|devstat
r_enum
id|devstat
(brace
DECL|enumerator|DEV_GONE
id|DEV_GONE
comma
DECL|enumerator|DEV_ONLINE
id|DEV_ONLINE
comma
DECL|enumerator|DEV_QUEUE_FULL
id|DEV_QUEUE_FULL
comma
DECL|enumerator|DEV_EMPTY
id|DEV_EMPTY
comma
DECL|enumerator|DEV_NO_WORK
id|DEV_NO_WORK
comma
DECL|enumerator|DEV_BAD_MESSAGE
id|DEV_BAD_MESSAGE
comma
DECL|enumerator|DEV_TSQ_EXCEPTION
id|DEV_TSQ_EXCEPTION
comma
DECL|enumerator|DEV_RSQ_EXCEPTION
id|DEV_RSQ_EXCEPTION
comma
DECL|enumerator|DEV_SEN_EXCEPTION
id|DEV_SEN_EXCEPTION
comma
DECL|enumerator|DEV_REC_EXCEPTION
id|DEV_REC_EXCEPTION
)brace
suffix:semicolon
DECL|enum|hdstat
r_enum
id|hdstat
(brace
DECL|enumerator|HD_NOT_THERE
id|HD_NOT_THERE
comma
DECL|enumerator|HD_BUSY
id|HD_BUSY
comma
DECL|enumerator|HD_DECONFIGURED
id|HD_DECONFIGURED
comma
DECL|enumerator|HD_CHECKSTOPPED
id|HD_CHECKSTOPPED
comma
DECL|enumerator|HD_ONLINE
id|HD_ONLINE
comma
DECL|enumerator|HD_TSQ_EXCEPTION
id|HD_TSQ_EXCEPTION
)brace
suffix:semicolon
DECL|macro|Z90C_AMBIGUOUS_DOMAIN
mdefine_line|#define Z90C_AMBIGUOUS_DOMAIN&t;2
DECL|macro|Z90C_INCORRECT_DOMAIN
mdefine_line|#define Z90C_INCORRECT_DOMAIN&t;3
DECL|macro|ENOTINIT
mdefine_line|#define ENOTINIT&t;&t;4
DECL|macro|SEN_BUSY
mdefine_line|#define SEN_BUSY&t; 7
DECL|macro|SEN_USER_ERROR
mdefine_line|#define SEN_USER_ERROR&t; 8
DECL|macro|SEN_QUEUE_FULL
mdefine_line|#define SEN_QUEUE_FULL&t;11
DECL|macro|SEN_NOT_AVAIL
mdefine_line|#define SEN_NOT_AVAIL&t;16
DECL|macro|SEN_PAD_ERROR
mdefine_line|#define SEN_PAD_ERROR&t;17
DECL|macro|SEN_RETRY
mdefine_line|#define SEN_RETRY&t;18
DECL|macro|SEN_RELEASED
mdefine_line|#define SEN_RELEASED&t;24
DECL|macro|REC_EMPTY
mdefine_line|#define REC_EMPTY&t; 4
DECL|macro|REC_BUSY
mdefine_line|#define REC_BUSY&t; 6
DECL|macro|REC_OPERAND_INV
mdefine_line|#define REC_OPERAND_INV&t; 8
DECL|macro|REC_OPERAND_SIZE
mdefine_line|#define REC_OPERAND_SIZE 9
DECL|macro|REC_EVEN_MOD
mdefine_line|#define REC_EVEN_MOD&t;10
DECL|macro|REC_NO_WORK
mdefine_line|#define REC_NO_WORK&t;11
DECL|macro|REC_HARDWAR_ERR
mdefine_line|#define REC_HARDWAR_ERR 12
DECL|macro|REC_NO_RESPONSE
mdefine_line|#define REC_NO_RESPONSE 13
DECL|macro|REC_RETRY_DEV
mdefine_line|#define REC_RETRY_DEV&t;14
DECL|macro|REC_USER_GONE
mdefine_line|#define REC_USER_GONE&t;15
DECL|macro|REC_BAD_MESSAGE
mdefine_line|#define REC_BAD_MESSAGE 16
DECL|macro|REC_INVALID_PAD
mdefine_line|#define REC_INVALID_PAD 17
DECL|macro|REC_RELEASED
mdefine_line|#define REC_RELEASED&t;28
DECL|macro|WRONG_DEVICE_TYPE
mdefine_line|#define WRONG_DEVICE_TYPE 20
DECL|macro|REC_FATAL_ERROR
mdefine_line|#define REC_FATAL_ERROR 32
DECL|macro|SEN_FATAL_ERROR
mdefine_line|#define SEN_FATAL_ERROR 33
DECL|macro|TSQ_FATAL_ERROR
mdefine_line|#define TSQ_FATAL_ERROR 34
DECL|macro|RSQ_FATAL_ERROR
mdefine_line|#define RSQ_FATAL_ERROR 35
DECL|macro|PCICA
mdefine_line|#define PCICA&t;0
DECL|macro|PCICC
mdefine_line|#define PCICC&t;1
DECL|macro|PCIXCC
mdefine_line|#define PCIXCC&t;2
DECL|macro|NILDEV
mdefine_line|#define NILDEV&t;-1
DECL|macro|ANYDEV
mdefine_line|#define ANYDEV&t;-1
DECL|enum|hdevice_type
r_enum
id|hdevice_type
(brace
DECL|enumerator|PCICC_HW
id|PCICC_HW
op_assign
l_int|3
comma
DECL|enumerator|PCICA_HW
id|PCICA_HW
op_assign
l_int|4
comma
DECL|enumerator|PCIXCC_HW
id|PCIXCC_HW
op_assign
l_int|5
comma
DECL|enumerator|OTHER_HW
id|OTHER_HW
op_assign
l_int|6
comma
DECL|enumerator|OTHER2_HW
id|OTHER2_HW
op_assign
l_int|7
)brace
suffix:semicolon
macro_line|#ifndef DEV_NAME
DECL|macro|DEV_NAME
mdefine_line|#define DEV_NAME&t;&quot;z90crypt&quot;
macro_line|#endif
DECL|macro|PRINTK
mdefine_line|#define PRINTK(fmt, args...) &bslash;&n;&t;printk(KERN_DEBUG DEV_NAME &quot;: %s -&gt; &quot; fmt, __FUNCTION__ , ## args)
DECL|macro|PRINTKN
mdefine_line|#define PRINTKN(fmt, args...) &bslash;&n;&t;printk(KERN_DEBUG DEV_NAME &quot;: &quot; fmt, ## args)
DECL|macro|PRINTKW
mdefine_line|#define PRINTKW(fmt, args...) &bslash;&n;&t;printk(KERN_WARNING DEV_NAME &quot;: %s -&gt; &quot; fmt, __FUNCTION__ , ## args)
DECL|macro|PRINTKC
mdefine_line|#define PRINTKC(fmt, args...) &bslash;&n;&t;printk(KERN_CRIT DEV_NAME &quot;: %s -&gt; &quot; fmt, __FUNCTION__ , ## args)
macro_line|#ifdef Z90CRYPT_DEBUG
DECL|macro|PDEBUG
mdefine_line|#define PDEBUG(fmt, args...) &bslash;&n;&t;printk(KERN_DEBUG DEV_NAME &quot;: %s -&gt; &quot; fmt, __FUNCTION__ , ## args)
macro_line|#else
DECL|macro|PDEBUG
mdefine_line|#define PDEBUG(fmt, args...) do {} while (0)
macro_line|#endif
DECL|macro|UMIN
mdefine_line|#define UMIN(a,b) ((a) &lt; (b) ? (a) : (b))
DECL|macro|IS_EVEN
mdefine_line|#define IS_EVEN(x) ((x) == (2 * ((x) / 2)))
macro_line|#endif
eof
