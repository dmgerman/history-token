multiline_comment|/*&n; *  linux/drivers/s390/crypto/z90common.h&n; *&n; *  z90crypt 1.3.2&n; *&n; *  Copyright (C)  2001, 2004 IBM Corporation&n; *  Author(s): Robert Burroughs (burrough@us.ibm.com)&n; *             Eric Rossman (edrossma@us.ibm.com)&n; *&n; *  Hotplug &amp; misc device support: Jochen Roehrig (roehrig@de.ibm.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _Z90COMMON_H_
DECL|macro|_Z90COMMON_H_
mdefine_line|#define _Z90COMMON_H_
DECL|macro|VERSION_Z90COMMON_H
mdefine_line|#define VERSION_Z90COMMON_H &quot;$Revision: 1.16 $&quot;
DECL|macro|RESPBUFFSIZE
mdefine_line|#define RESPBUFFSIZE 256
DECL|macro|PCI_FUNC_KEY_DECRYPT
mdefine_line|#define PCI_FUNC_KEY_DECRYPT 0x5044
DECL|macro|PCI_FUNC_KEY_ENCRYPT
mdefine_line|#define PCI_FUNC_KEY_ENCRYPT 0x504B
r_extern
r_int
id|ext_bitlens
suffix:semicolon
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
DECL|macro|Z90C_NO_DEVICES
mdefine_line|#define Z90C_NO_DEVICES&t;&t;1
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
mdefine_line|#define REC_HARDWAR_ERR&t;12
DECL|macro|REC_NO_RESPONSE
mdefine_line|#define REC_NO_RESPONSE&t;13
DECL|macro|REC_RETRY_DEV
mdefine_line|#define REC_RETRY_DEV&t;14
DECL|macro|REC_USER_GONE
mdefine_line|#define REC_USER_GONE&t;15
DECL|macro|REC_BAD_MESSAGE
mdefine_line|#define REC_BAD_MESSAGE&t;16
DECL|macro|REC_INVALID_PAD
mdefine_line|#define REC_INVALID_PAD&t;17
DECL|macro|REC_USE_PCICA
mdefine_line|#define REC_USE_PCICA&t;18
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
DECL|macro|Z90CRYPT_NUM_TYPES
mdefine_line|#define Z90CRYPT_NUM_TYPES&t;5
DECL|macro|PCICA
mdefine_line|#define PCICA&t;&t;0
DECL|macro|PCICC
mdefine_line|#define PCICC&t;&t;1
DECL|macro|PCIXCC_MCL2
mdefine_line|#define PCIXCC_MCL2&t;2
DECL|macro|PCIXCC_MCL3
mdefine_line|#define PCIXCC_MCL3&t;3
DECL|macro|CEX2C
mdefine_line|#define CEX2C&t;&t;4
DECL|macro|NILDEV
mdefine_line|#define NILDEV&t;&t;-1
DECL|macro|ANYDEV
mdefine_line|#define ANYDEV&t;&t;-1
DECL|macro|PCIXCC_UNK
mdefine_line|#define PCIXCC_UNK&t;-2
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
DECL|enumerator|CEX2C_HW
id|CEX2C_HW
op_assign
l_int|7
)brace
suffix:semicolon
DECL|struct|CPRBX
r_struct
id|CPRBX
(brace
DECL|member|cprb_len
r_int
r_int
id|cprb_len
suffix:semicolon
DECL|member|cprb_ver_id
r_int
r_char
id|cprb_ver_id
suffix:semicolon
DECL|member|pad_000
r_int
r_char
id|pad_000
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|func_id
r_int
r_char
id|func_id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cprb_flags
r_int
r_char
id|cprb_flags
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|req_parml
r_int
r_int
id|req_parml
suffix:semicolon
DECL|member|req_datal
r_int
r_int
id|req_datal
suffix:semicolon
DECL|member|rpl_msgbl
r_int
r_int
id|rpl_msgbl
suffix:semicolon
DECL|member|rpld_parml
r_int
r_int
id|rpld_parml
suffix:semicolon
DECL|member|rpl_datal
r_int
r_int
id|rpl_datal
suffix:semicolon
DECL|member|rpld_datal
r_int
r_int
id|rpld_datal
suffix:semicolon
DECL|member|req_extbl
r_int
r_int
id|req_extbl
suffix:semicolon
DECL|member|pad_001
r_int
r_char
id|pad_001
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rpld_extbl
r_int
r_int
id|rpld_extbl
suffix:semicolon
DECL|member|req_parmb
r_int
r_char
id|req_parmb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|req_datab
r_int
r_char
id|req_datab
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|rpl_parmb
r_int
r_char
id|rpl_parmb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|rpl_datab
r_int
r_char
id|rpl_datab
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|req_extb
r_int
r_char
id|req_extb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|rpl_extb
r_int
r_char
id|rpl_extb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ccp_rtcode
r_int
r_int
id|ccp_rtcode
suffix:semicolon
DECL|member|ccp_rscode
r_int
r_int
id|ccp_rscode
suffix:semicolon
DECL|member|mac_data_len
r_int
r_int
id|mac_data_len
suffix:semicolon
DECL|member|logon_id
r_int
r_char
id|logon_id
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|mac_value
r_int
r_char
id|mac_value
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|mac_content_flgs
r_int
r_char
id|mac_content_flgs
suffix:semicolon
DECL|member|pad_002
r_int
r_char
id|pad_002
suffix:semicolon
DECL|member|domain
r_int
r_int
id|domain
suffix:semicolon
DECL|member|pad_003
r_int
r_char
id|pad_003
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pad_004
r_int
r_char
id|pad_004
(braket
l_int|36
)braket
suffix:semicolon
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
