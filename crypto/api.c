multiline_comment|/*&n; * Scatterlist Cryptographic API.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; * Copyright (c) 2002 David S. Miller (davem@redhat.com)&n; *&n; * Portions derived from Cryptoapi, by Alexander Kjeldaas &lt;astor@fast.no&gt;&n; * and Nettle, by Niels M&#xfffd;ller.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &quot;internal.h&quot;
r_static
id|LIST_HEAD
c_func
(paren
id|crypto_alg_list
)paren
suffix:semicolon
DECL|variable|crypto_alg_sem
r_static
r_struct
id|rw_semaphore
id|crypto_alg_sem
suffix:semicolon
DECL|function|crypto_alg_get
r_static
r_inline
r_int
id|crypto_alg_get
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
r_return
id|try_inc_mod_count
c_func
(paren
id|alg-&gt;cra_module
)paren
suffix:semicolon
)brace
DECL|function|crypto_alg_put
r_static
r_inline
r_void
id|crypto_alg_put
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
r_if
c_cond
(paren
id|alg-&gt;cra_module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|alg-&gt;cra_module
)paren
suffix:semicolon
)brace
DECL|function|crypto_alg_lookup
r_struct
id|crypto_alg
op_star
id|crypto_alg_lookup
c_func
(paren
id|u32
id|algid
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|crypto_alg
op_star
id|alg
op_assign
l_int|NULL
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|crypto_alg_list
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
(paren
r_struct
id|crypto_alg
op_star
)paren
id|p
)paren
op_member_access_from_pointer
id|cra_id
op_amp
id|CRYPTO_ALG_MASK
)paren
op_eq
id|algid
)paren
(brace
r_if
c_cond
(paren
id|crypto_alg_get
c_func
(paren
(paren
r_struct
id|crypto_alg
op_star
)paren
id|p
)paren
)paren
id|alg
op_assign
(paren
r_struct
id|crypto_alg
op_star
)paren
id|p
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up_read
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
r_return
id|alg
suffix:semicolon
)brace
DECL|function|crypto_init_ops
r_static
r_void
id|crypto_init_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_switch
c_cond
(paren
id|crypto_tfm_type
c_func
(paren
id|tfm
)paren
op_amp
id|CRYPTO_TYPE_MASK
)paren
(brace
r_case
id|CRYPTO_TYPE_CIPHER
suffix:colon
id|crypto_init_cipher_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_TYPE_DIGEST
suffix:colon
id|crypto_init_digest_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_TYPE_COMP
suffix:colon
id|crypto_init_compress_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|crypto_alloc_tfm
r_struct
id|crypto_tfm
op_star
id|crypto_alloc_tfm
c_func
(paren
id|u32
id|id
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|crypto_alg
op_star
id|alg
suffix:semicolon
id|alg
op_assign
id|crypto_alg_lookup
c_func
(paren
id|id
op_amp
id|CRYPTO_ALG_MASK
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|alg
op_eq
l_int|NULL
)paren
(brace
id|crypto_alg_autoload
c_func
(paren
id|id
op_amp
id|CRYPTO_ALG_MASK
)paren
suffix:semicolon
id|alg
op_assign
id|crypto_alg_lookup
c_func
(paren
id|id
op_amp
id|CRYPTO_ALG_MASK
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|alg
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|tfm
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tfm
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tfm
op_eq
l_int|NULL
)paren
r_goto
id|out_put
suffix:semicolon
r_if
c_cond
(paren
id|alg-&gt;cra_ctxsize
)paren
(brace
id|tfm-&gt;crt_ctx
op_assign
id|kmalloc
c_func
(paren
id|alg-&gt;cra_ctxsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tfm-&gt;crt_ctx
op_eq
l_int|NULL
)paren
r_goto
id|out_free_tfm
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|alg-&gt;cra_id
op_amp
id|CRYPTO_TYPE_MASK
)paren
op_eq
id|CRYPTO_TYPE_CIPHER
)paren
(brace
r_if
c_cond
(paren
id|alg-&gt;cra_cipher.cia_ivsize
)paren
(brace
id|tfm-&gt;crt_cipher.cit_iv
op_assign
id|kmalloc
c_func
(paren
id|alg-&gt;cra_cipher.cia_ivsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tfm-&gt;crt_cipher.cit_iv
op_eq
l_int|NULL
)paren
r_goto
id|out_free_ctx
suffix:semicolon
)brace
id|tfm-&gt;crt_cipher.cit_mode
op_assign
id|id
op_amp
id|CRYPTO_MODE_MASK
suffix:semicolon
)brace
id|tfm-&gt;__crt_alg
op_assign
id|alg
suffix:semicolon
id|crypto_init_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_free_ctx
suffix:colon
r_if
c_cond
(paren
id|tfm-&gt;__crt_alg-&gt;cra_ctxsize
)paren
id|kfree
c_func
(paren
id|tfm-&gt;crt_ctx
)paren
suffix:semicolon
id|out_free_tfm
suffix:colon
id|kfree
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|tfm
op_assign
l_int|NULL
suffix:semicolon
id|out_put
suffix:colon
id|crypto_alg_put
c_func
(paren
id|alg
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|tfm
suffix:semicolon
)brace
DECL|function|crypto_free_tfm
r_void
id|crypto_free_tfm
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_if
c_cond
(paren
id|tfm-&gt;__crt_alg-&gt;cra_ctxsize
)paren
id|kfree
c_func
(paren
id|tfm-&gt;crt_ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crypto_tfm_type
c_func
(paren
id|tfm
)paren
op_eq
id|CRYPTO_TYPE_CIPHER
)paren
r_if
c_cond
(paren
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_ivsize
)paren
id|kfree
c_func
(paren
id|tfm-&gt;crt_cipher.cit_iv
)paren
suffix:semicolon
id|crypto_alg_put
c_func
(paren
id|tfm-&gt;__crt_alg
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tfm
)paren
suffix:semicolon
)brace
DECL|function|crypto_register_alg
r_int
id|crypto_register_alg
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|crypto_alg_list
)paren
(brace
r_struct
id|crypto_alg
op_star
id|q
op_assign
(paren
r_struct
id|crypto_alg
op_star
)paren
id|p
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;cra_id
op_eq
id|alg-&gt;cra_id
)paren
(brace
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|alg-&gt;cra_list
comma
op_amp
id|crypto_alg_list
)paren
suffix:semicolon
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|crypto_unregister_alg
r_int
id|crypto_unregister_alg
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|alg-&gt;cra_module
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|crypto_alg_list
)paren
(brace
r_if
c_cond
(paren
id|alg
op_eq
(paren
r_struct
id|crypto_alg
op_star
)paren
id|p
)paren
(brace
id|list_del
c_func
(paren
id|p
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|c_start
r_static
r_void
op_star
id|c_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|v
suffix:semicolon
id|loff_t
id|n
op_assign
op_star
id|pos
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|v
comma
op_amp
id|crypto_alg_list
)paren
r_if
c_cond
(paren
op_logical_neg
id|n
op_decrement
)paren
r_return
id|list_entry
c_func
(paren
id|v
comma
r_struct
id|crypto_alg
comma
id|cra_list
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_next
r_static
r_void
op_star
id|c_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|p
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|v
op_assign
id|p
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
id|v
op_assign
id|v-&gt;next
suffix:semicolon
r_return
(paren
id|v
op_eq
op_amp
id|crypto_alg_list
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|list_entry
c_func
(paren
id|v
comma
r_struct
id|crypto_alg
comma
id|cra_list
)paren
suffix:semicolon
)brace
DECL|function|c_stop
r_static
r_void
id|c_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|p
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
)brace
DECL|function|c_show
r_static
r_int
id|c_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|p
)paren
(brace
r_struct
id|crypto_alg
op_star
id|alg
op_assign
(paren
r_struct
id|crypto_alg
op_star
)paren
id|p
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;name       : %s&bslash;n&quot;
comma
id|alg-&gt;cra_name
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;id         : 0x%08x&bslash;n&quot;
comma
id|alg-&gt;cra_id
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;blocksize  : %Zd&bslash;n&quot;
comma
id|alg-&gt;cra_blocksize
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|alg-&gt;cra_id
op_amp
id|CRYPTO_TYPE_MASK
)paren
(brace
r_case
id|CRYPTO_TYPE_CIPHER
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;keysize    : %Zd&bslash;n&quot;
comma
id|alg-&gt;cra_cipher.cia_keysize
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;ivsize     : %Zd&bslash;n&quot;
comma
id|alg-&gt;cra_cipher.cia_ivsize
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_TYPE_DIGEST
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;digestsize : %Zd&bslash;n&quot;
comma
id|alg-&gt;cra_digest.dia_digestsize
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|m
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|crypto_seq_ops
r_static
r_struct
id|seq_operations
id|crypto_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
id|c_show
)brace
suffix:semicolon
DECL|function|crypto_info_open
r_static
r_int
id|crypto_info_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|crypto_seq_ops
)paren
suffix:semicolon
)brace
DECL|variable|proc_crypto_ops
r_struct
id|file_operations
id|proc_crypto_ops
op_assign
(brace
dot
id|open
op_assign
id|crypto_info_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
)brace
suffix:semicolon
DECL|function|init_crypto
r_static
r_int
id|__init
id|init_crypto
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Initializing Cryptographic API&bslash;n&quot;
)paren
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|proc
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;crypto&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc
)paren
id|proc-&gt;proc_fops
op_assign
op_amp
id|proc_crypto_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_crypto
id|__initcall
c_func
(paren
id|init_crypto
)paren
suffix:semicolon
DECL|variable|crypto_register_alg
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_register_alg
)paren
suffix:semicolon
DECL|variable|crypto_unregister_alg
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_unregister_alg
)paren
suffix:semicolon
DECL|variable|crypto_alloc_tfm
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_alloc_tfm
)paren
suffix:semicolon
DECL|variable|crypto_free_tfm
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_free_tfm
)paren
suffix:semicolon
eof
