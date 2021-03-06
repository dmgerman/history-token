multiline_comment|/*&n; *  ISA Plug &amp; Play support&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef LINUX_ISAPNP_H
DECL|macro|LINUX_ISAPNP_H
mdefine_line|#define LINUX_ISAPNP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
multiline_comment|/*&n; *  Configuration registers (TODO: change by specification)&n; */
DECL|macro|ISAPNP_CFG_ACTIVATE
mdefine_line|#define ISAPNP_CFG_ACTIVATE&t;&t;0x30&t;/* byte */
DECL|macro|ISAPNP_CFG_MEM
mdefine_line|#define ISAPNP_CFG_MEM&t;&t;&t;0x40&t;/* 4 * dword */
DECL|macro|ISAPNP_CFG_PORT
mdefine_line|#define ISAPNP_CFG_PORT&t;&t;&t;0x60&t;/* 8 * word */
DECL|macro|ISAPNP_CFG_IRQ
mdefine_line|#define ISAPNP_CFG_IRQ&t;&t;&t;0x70&t;/* 2 * word */
DECL|macro|ISAPNP_CFG_DMA
mdefine_line|#define ISAPNP_CFG_DMA&t;&t;&t;0x74&t;/* 2 * byte */
multiline_comment|/*&n; *&n; */
DECL|macro|ISAPNP_VENDOR
mdefine_line|#define ISAPNP_VENDOR(a,b,c)&t;(((((a)-&squot;A&squot;+1)&amp;0x3f)&lt;&lt;2)|&bslash;&n;&t;&t;&t;&t;((((b)-&squot;A&squot;+1)&amp;0x18)&gt;&gt;3)|((((b)-&squot;A&squot;+1)&amp;7)&lt;&lt;13)|&bslash;&n;&t;&t;&t;&t;((((c)-&squot;A&squot;+1)&amp;0x1f)&lt;&lt;8))
DECL|macro|ISAPNP_DEVICE
mdefine_line|#define ISAPNP_DEVICE(x)&t;((((x)&amp;0xf000)&gt;&gt;8)|&bslash;&n;&t;&t;&t;&t; (((x)&amp;0x0f00)&gt;&gt;8)|&bslash;&n;&t;&t;&t;&t; (((x)&amp;0x00f0)&lt;&lt;8)|&bslash;&n;&t;&t;&t;&t; (((x)&amp;0x000f)&lt;&lt;8))
DECL|macro|ISAPNP_FUNCTION
mdefine_line|#define ISAPNP_FUNCTION(x)&t;ISAPNP_DEVICE(x)
multiline_comment|/*&n; *&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|DEVICE_COUNT_COMPATIBLE
mdefine_line|#define DEVICE_COUNT_COMPATIBLE 4
DECL|macro|ISAPNP_ANY_ID
mdefine_line|#define ISAPNP_ANY_ID&t;&t;0xffff
DECL|macro|ISAPNP_CARD_DEVS
mdefine_line|#define ISAPNP_CARD_DEVS&t;8
DECL|macro|ISAPNP_CARD_ID
mdefine_line|#define ISAPNP_CARD_ID(_va, _vb, _vc, _device) &bslash;&n;&t;&t;.card_vendor = ISAPNP_VENDOR(_va, _vb, _vc), .card_device = ISAPNP_DEVICE(_device)
DECL|macro|ISAPNP_CARD_END
mdefine_line|#define ISAPNP_CARD_END &bslash;&n;&t;&t;.card_vendor = 0, .card_device = 0
DECL|macro|ISAPNP_DEVICE_ID
mdefine_line|#define ISAPNP_DEVICE_ID(_va, _vb, _vc, _function) &bslash;&n;&t;&t;{ .vendor = ISAPNP_VENDOR(_va, _vb, _vc), .function = ISAPNP_FUNCTION(_function) }
multiline_comment|/* export used IDs outside module */
DECL|macro|ISAPNP_CARD_TABLE
mdefine_line|#define ISAPNP_CARD_TABLE(name) &bslash;&n;&t;&t;MODULE_GENERIC_TABLE(isapnp_card, name)
DECL|struct|isapnp_card_id
r_struct
id|isapnp_card_id
(brace
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
DECL|member|card_vendor
DECL|member|card_device
r_int
r_int
id|card_vendor
comma
id|card_device
suffix:semicolon
r_struct
(brace
DECL|member|vendor
DECL|member|function
r_int
r_int
id|vendor
comma
id|function
suffix:semicolon
DECL|member|devs
)brace
id|devs
(braket
id|ISAPNP_CARD_DEVS
)braket
suffix:semicolon
multiline_comment|/* logical devices */
)brace
suffix:semicolon
DECL|macro|ISAPNP_DEVICE_SINGLE
mdefine_line|#define ISAPNP_DEVICE_SINGLE(_cva, _cvb, _cvc, _cdevice, _dva, _dvb, _dvc, _dfunction) &bslash;&n;&t;&t;.card_vendor = ISAPNP_VENDOR(_cva, _cvb, _cvc), .card_device =  ISAPNP_DEVICE(_cdevice), &bslash;&n;&t;&t;.vendor = ISAPNP_VENDOR(_dva, _dvb, _dvc), .function = ISAPNP_FUNCTION(_dfunction)
DECL|macro|ISAPNP_DEVICE_SINGLE_END
mdefine_line|#define ISAPNP_DEVICE_SINGLE_END &bslash;&n;&t;&t;.card_vendor = 0, .card_device = 0
DECL|struct|isapnp_device_id
r_struct
id|isapnp_device_id
(brace
DECL|member|card_vendor
DECL|member|card_device
r_int
r_int
id|card_vendor
comma
id|card_device
suffix:semicolon
DECL|member|vendor
DECL|member|function
r_int
r_int
id|vendor
comma
id|function
suffix:semicolon
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_ISAPNP) || (defined(CONFIG_ISAPNP_MODULE) &amp;&amp; defined(MODULE))
DECL|macro|__ISAPNP__
mdefine_line|#define __ISAPNP__
multiline_comment|/* lowlevel configuration */
r_int
id|isapnp_present
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|isapnp_cfg_begin
c_func
(paren
r_int
id|csn
comma
r_int
id|device
)paren
suffix:semicolon
r_int
id|isapnp_cfg_end
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_char
id|isapnp_read_byte
c_func
(paren
r_int
r_char
id|idx
)paren
suffix:semicolon
r_void
id|isapnp_write_byte
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_char
id|val
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_int
id|isapnp_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|isapnp_proc_done
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|isapnp_proc_init
r_static
r_inline
r_int
id|isapnp_proc_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|isapnp_proc_done
r_static
r_inline
r_int
id|isapnp_proc_done
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* compat */
r_struct
id|pnp_card
op_star
id|pnp_find_card
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pnp_card
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|pnp_find_dev
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_struct
id|pnp_dev
op_star
id|from
)paren
suffix:semicolon
macro_line|#else /* !CONFIG_ISAPNP */
multiline_comment|/* lowlevel configuration */
DECL|function|isapnp_present
r_static
r_inline
r_int
id|isapnp_present
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|isapnp_cfg_begin
r_static
r_inline
r_int
id|isapnp_cfg_begin
c_func
(paren
r_int
id|csn
comma
r_int
id|device
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|isapnp_cfg_end
r_static
r_inline
r_int
id|isapnp_cfg_end
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|isapnp_read_byte
r_static
r_inline
r_int
r_char
id|isapnp_read_byte
c_func
(paren
r_int
r_char
id|idx
)paren
(brace
r_return
l_int|0xff
suffix:semicolon
)brace
DECL|function|isapnp_write_byte
r_static
r_inline
r_void
id|isapnp_write_byte
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_char
id|val
)paren
(brace
suffix:semicolon
)brace
DECL|function|pnp_find_card
r_static
r_inline
r_struct
id|pnp_card
op_star
id|pnp_find_card
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pnp_card
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_find_dev
r_static
r_inline
r_struct
id|pnp_dev
op_star
id|pnp_find_dev
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_struct
id|pnp_dev
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ISAPNP */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_ISAPNP_H */
eof
