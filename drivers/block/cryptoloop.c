multiline_comment|/*&n;   Linux loop encryption enabling module&n;&n;   Copyright (C)  2002 Herbert Valerio Riedel &lt;hvr@gnu.org&gt;&n;   Copyright (C)  2003 Fruhwirth Clemens &lt;clemens@endorphin.org&gt;&n;&n;   This module is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This module is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this module; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/loop.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;loop blockdevice transferfunction adaptor / CryptoAPI&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Herbert Valerio Riedel &lt;hvr@gnu.org&gt;&quot;
)paren
suffix:semicolon
DECL|macro|LOOP_IV_SECTOR_BITS
mdefine_line|#define LOOP_IV_SECTOR_BITS 9
DECL|macro|LOOP_IV_SECTOR_SIZE
mdefine_line|#define LOOP_IV_SECTOR_SIZE (1 &lt;&lt; LOOP_IV_SECTOR_BITS)
r_static
r_int
DECL|function|cryptoloop_init
id|cryptoloop_init
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_const
r_struct
id|loop_info64
op_star
id|info
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_char
id|cms
(braket
id|LO_NAME_SIZE
)braket
suffix:semicolon
multiline_comment|/* cipher-mode string */
r_char
op_star
id|cipher
suffix:semicolon
r_char
op_star
id|mode
suffix:semicolon
r_char
op_star
id|cmsp
op_assign
id|cms
suffix:semicolon
multiline_comment|/* c-m string pointer */
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* encryption breaks for non sector aligned offsets */
r_if
c_cond
(paren
id|info-&gt;lo_offset
op_mod
id|LOOP_IV_SECTOR_SIZE
)paren
r_goto
id|out
suffix:semicolon
id|strncpy
c_func
(paren
id|cms
comma
id|info-&gt;lo_crypt_name
comma
id|LO_NAME_SIZE
)paren
suffix:semicolon
id|cms
(braket
id|LO_NAME_SIZE
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|cipher
op_assign
id|strsep
c_func
(paren
op_amp
id|cmsp
comma
l_string|&quot;-&quot;
)paren
suffix:semicolon
id|mode
op_assign
id|strsep
c_func
(paren
op_amp
id|cmsp
comma
l_string|&quot;-&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
l_int|NULL
op_logical_or
id|strcmp
c_func
(paren
id|mode
comma
l_string|&quot;cbc&quot;
)paren
op_eq
l_int|0
)paren
id|tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|cipher
comma
id|CRYPTO_TFM_MODE_CBC
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|mode
comma
l_string|&quot;ecb&quot;
)paren
op_eq
l_int|0
)paren
id|tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|cipher
comma
id|CRYPTO_TFM_MODE_ECB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tfm
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|tfm-&gt;crt_u.cipher
dot
id|cit_setkey
c_func
(paren
id|tfm
comma
id|info-&gt;lo_encrypt_key
comma
id|info-&gt;lo_encrypt_key_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
r_goto
id|out_free_tfm
suffix:semicolon
id|lo-&gt;key_data
op_assign
id|tfm
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_free_tfm
suffix:colon
id|crypto_free_tfm
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|typedef|encdec_ecb_t
r_typedef
r_int
(paren
op_star
id|encdec_ecb_t
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg_out
comma
r_struct
id|scatterlist
op_star
id|sg_in
comma
r_int
r_int
id|nsg
)paren
suffix:semicolon
r_static
r_int
DECL|function|cryptoloop_transfer_ecb
id|cryptoloop_transfer_ecb
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_struct
id|page
op_star
id|raw_page
comma
r_int
id|raw_off
comma
r_struct
id|page
op_star
id|loop_page
comma
r_int
id|loop_off
comma
r_int
id|size
comma
id|sector_t
id|IV
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
(paren
r_struct
id|crypto_tfm
op_star
)paren
id|lo-&gt;key_data
suffix:semicolon
r_struct
id|scatterlist
id|sg_out
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
r_struct
id|scatterlist
id|sg_in
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
id|encdec_ecb_t
id|encdecfunc
suffix:semicolon
r_struct
id|page
op_star
id|in_page
comma
op_star
id|out_page
suffix:semicolon
r_int
id|in_offs
comma
id|out_offs
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|READ
)paren
(brace
id|in_page
op_assign
id|raw_page
suffix:semicolon
id|in_offs
op_assign
id|raw_off
suffix:semicolon
id|out_page
op_assign
id|loop_page
suffix:semicolon
id|out_offs
op_assign
id|loop_off
suffix:semicolon
id|encdecfunc
op_assign
id|tfm-&gt;crt_u.cipher.cit_decrypt
suffix:semicolon
)brace
r_else
(brace
id|in_page
op_assign
id|loop_page
suffix:semicolon
id|in_offs
op_assign
id|loop_off
suffix:semicolon
id|out_page
op_assign
id|raw_page
suffix:semicolon
id|out_offs
op_assign
id|raw_off
suffix:semicolon
id|encdecfunc
op_assign
id|tfm-&gt;crt_u.cipher.cit_encrypt
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_const
r_int
id|sz
op_assign
id|min
c_func
(paren
id|size
comma
id|LOOP_IV_SECTOR_SIZE
)paren
suffix:semicolon
id|sg_in.page
op_assign
id|in_page
suffix:semicolon
id|sg_in.offset
op_assign
id|in_offs
suffix:semicolon
id|sg_in.length
op_assign
id|sz
suffix:semicolon
id|sg_out.page
op_assign
id|out_page
suffix:semicolon
id|sg_out.offset
op_assign
id|out_offs
suffix:semicolon
id|sg_out.length
op_assign
id|sz
suffix:semicolon
id|encdecfunc
c_func
(paren
id|tfm
comma
op_amp
id|sg_out
comma
op_amp
id|sg_in
comma
id|sz
)paren
suffix:semicolon
id|size
op_sub_assign
id|sz
suffix:semicolon
id|in_offs
op_add_assign
id|sz
suffix:semicolon
id|out_offs
op_add_assign
id|sz
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|typedef|encdec_cbc_t
r_typedef
r_int
(paren
op_star
id|encdec_cbc_t
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg_out
comma
r_struct
id|scatterlist
op_star
id|sg_in
comma
r_int
r_int
id|nsg
comma
id|u8
op_star
id|iv
)paren
suffix:semicolon
r_static
r_int
DECL|function|cryptoloop_transfer_cbc
id|cryptoloop_transfer_cbc
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_struct
id|page
op_star
id|raw_page
comma
r_int
id|raw_off
comma
r_struct
id|page
op_star
id|loop_page
comma
r_int
id|loop_off
comma
r_int
id|size
comma
id|sector_t
id|IV
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
(paren
r_struct
id|crypto_tfm
op_star
)paren
id|lo-&gt;key_data
suffix:semicolon
r_struct
id|scatterlist
id|sg_out
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
r_struct
id|scatterlist
id|sg_in
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
id|encdec_cbc_t
id|encdecfunc
suffix:semicolon
r_struct
id|page
op_star
id|in_page
comma
op_star
id|out_page
suffix:semicolon
r_int
id|in_offs
comma
id|out_offs
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|READ
)paren
(brace
id|in_page
op_assign
id|raw_page
suffix:semicolon
id|in_offs
op_assign
id|raw_off
suffix:semicolon
id|out_page
op_assign
id|loop_page
suffix:semicolon
id|out_offs
op_assign
id|loop_off
suffix:semicolon
id|encdecfunc
op_assign
id|tfm-&gt;crt_u.cipher.cit_decrypt_iv
suffix:semicolon
)brace
r_else
(brace
id|in_page
op_assign
id|loop_page
suffix:semicolon
id|in_offs
op_assign
id|loop_off
suffix:semicolon
id|out_page
op_assign
id|raw_page
suffix:semicolon
id|out_offs
op_assign
id|raw_off
suffix:semicolon
id|encdecfunc
op_assign
id|tfm-&gt;crt_u.cipher.cit_encrypt_iv
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_const
r_int
id|sz
op_assign
id|min
c_func
(paren
id|size
comma
id|LOOP_IV_SECTOR_SIZE
)paren
suffix:semicolon
id|u32
id|iv
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
id|iv
(braket
l_int|0
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|IV
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|sg_in.page
op_assign
id|in_page
suffix:semicolon
id|sg_in.offset
op_assign
id|in_offs
suffix:semicolon
id|sg_in.length
op_assign
id|sz
suffix:semicolon
id|sg_out.page
op_assign
id|out_page
suffix:semicolon
id|sg_out.offset
op_assign
id|out_offs
suffix:semicolon
id|sg_out.length
op_assign
id|sz
suffix:semicolon
id|encdecfunc
c_func
(paren
id|tfm
comma
op_amp
id|sg_out
comma
op_amp
id|sg_in
comma
id|sz
comma
(paren
id|u8
op_star
)paren
id|iv
)paren
suffix:semicolon
id|IV
op_increment
suffix:semicolon
id|size
op_sub_assign
id|sz
suffix:semicolon
id|in_offs
op_add_assign
id|sz
suffix:semicolon
id|out_offs
op_add_assign
id|sz
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|cryptoloop_transfer
id|cryptoloop_transfer
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_struct
id|page
op_star
id|raw_page
comma
r_int
id|raw_off
comma
r_struct
id|page
op_star
id|loop_page
comma
r_int
id|loop_off
comma
r_int
id|size
comma
id|sector_t
id|IV
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
(paren
r_struct
id|crypto_tfm
op_star
)paren
id|lo-&gt;key_data
suffix:semicolon
r_if
c_cond
(paren
id|tfm-&gt;crt_cipher.cit_mode
op_eq
id|CRYPTO_TFM_MODE_ECB
)paren
(brace
id|lo-&gt;transfer
op_assign
id|cryptoloop_transfer_ecb
suffix:semicolon
r_return
id|cryptoloop_transfer_ecb
c_func
(paren
id|lo
comma
id|cmd
comma
id|raw_page
comma
id|raw_off
comma
id|loop_page
comma
id|loop_off
comma
id|size
comma
id|IV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tfm-&gt;crt_cipher.cit_mode
op_eq
id|CRYPTO_TFM_MODE_CBC
)paren
(brace
id|lo-&gt;transfer
op_assign
id|cryptoloop_transfer_cbc
suffix:semicolon
r_return
id|cryptoloop_transfer_cbc
c_func
(paren
id|lo
comma
id|cmd
comma
id|raw_page
comma
id|raw_off
comma
id|loop_page
comma
id|loop_off
comma
id|size
comma
id|IV
)paren
suffix:semicolon
)brace
multiline_comment|/*  This is not supposed to happen */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cryptoloop: unsupported cipher mode in cryptoloop_transfer!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|cryptoloop_ioctl
id|cryptoloop_ioctl
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|cryptoloop_release
id|cryptoloop_release
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
(paren
r_struct
id|crypto_tfm
op_star
)paren
id|lo-&gt;key_data
suffix:semicolon
r_if
c_cond
(paren
id|tfm
op_ne
l_int|NULL
)paren
(brace
id|crypto_free_tfm
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|lo-&gt;key_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cryptoloop_release(): tfm == NULL?&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|cryptoloop_funcs
r_static
r_struct
id|loop_func_table
id|cryptoloop_funcs
op_assign
(brace
dot
id|number
op_assign
id|LO_CRYPT_CRYPTOAPI
comma
dot
id|init
op_assign
id|cryptoloop_init
comma
dot
id|ioctl
op_assign
id|cryptoloop_ioctl
comma
dot
id|transfer
op_assign
id|cryptoloop_transfer
comma
dot
id|release
op_assign
id|cryptoloop_release
comma
dot
id|owner
op_assign
id|THIS_MODULE
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|init_cryptoloop
id|init_cryptoloop
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
id|loop_register_transfer
c_func
(paren
op_amp
id|cryptoloop_funcs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cryptoloop: loop_register_transfer failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|cleanup_cryptoloop
id|cleanup_cryptoloop
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|loop_unregister_transfer
c_func
(paren
id|LO_CRYPT_CRYPTOAPI
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cryptoloop: loop_unregister_transfer failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|init_cryptoloop
id|module_init
c_func
(paren
id|init_cryptoloop
)paren
suffix:semicolon
DECL|variable|cleanup_cryptoloop
id|module_exit
c_func
(paren
id|cleanup_cryptoloop
)paren
suffix:semicolon
eof
