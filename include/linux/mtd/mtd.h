multiline_comment|/* &n; * $Id: mtd.h,v 1.56 2004/08/09 18:46:04 dmarlin Exp $&n; *&n; * Copyright (C) 1999-2003 David Woodhouse &lt;dwmw2@infradead.org&gt; et al.&n; *&n; * Released under GPL&n; */
macro_line|#ifndef __MTD_MTD_H__
DECL|macro|__MTD_MTD_H__
mdefine_line|#define __MTD_MTD_H__
macro_line|#ifndef __KERNEL__
macro_line|#error This is a kernel header. Perhaps include mtd-user.h instead?
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
macro_line|#include &lt;mtd/mtd-abi.h&gt;
DECL|macro|MTD_CHAR_MAJOR
mdefine_line|#define MTD_CHAR_MAJOR 90
DECL|macro|MTD_BLOCK_MAJOR
mdefine_line|#define MTD_BLOCK_MAJOR 31
DECL|macro|MAX_MTD_DEVICES
mdefine_line|#define MAX_MTD_DEVICES 16
DECL|macro|MTD_ERASE_PENDING
mdefine_line|#define MTD_ERASE_PENDING      &t;0x01
DECL|macro|MTD_ERASING
mdefine_line|#define MTD_ERASING&t;&t;0x02
DECL|macro|MTD_ERASE_SUSPEND
mdefine_line|#define MTD_ERASE_SUSPEND&t;0x04
DECL|macro|MTD_ERASE_DONE
mdefine_line|#define MTD_ERASE_DONE          0x08
DECL|macro|MTD_ERASE_FAILED
mdefine_line|#define MTD_ERASE_FAILED        0x10
multiline_comment|/* If the erase fails, fail_addr might indicate exactly which block failed.  If&n;   fail_addr = 0xffffffff, the failure was not at the device level or was not&n;   specific to any particular block. */
DECL|struct|erase_info
r_struct
id|erase_info
(brace
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
DECL|member|addr
id|u_int32_t
id|addr
suffix:semicolon
DECL|member|len
id|u_int32_t
id|len
suffix:semicolon
DECL|member|fail_addr
id|u_int32_t
id|fail_addr
suffix:semicolon
DECL|member|time
id|u_long
id|time
suffix:semicolon
DECL|member|retries
id|u_long
id|retries
suffix:semicolon
DECL|member|dev
id|u_int
id|dev
suffix:semicolon
DECL|member|cell
id|u_int
id|cell
suffix:semicolon
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|erase_info
op_star
id|self
)paren
suffix:semicolon
DECL|member|priv
id|u_long
id|priv
suffix:semicolon
DECL|member|state
id|u_char
id|state
suffix:semicolon
DECL|member|next
r_struct
id|erase_info
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mtd_erase_region_info
r_struct
id|mtd_erase_region_info
(brace
DECL|member|offset
id|u_int32_t
id|offset
suffix:semicolon
multiline_comment|/* At which this region starts, from the beginning of the MTD */
DECL|member|erasesize
id|u_int32_t
id|erasesize
suffix:semicolon
multiline_comment|/* For this region */
DECL|member|numblocks
id|u_int32_t
id|numblocks
suffix:semicolon
multiline_comment|/* Number of blocks of erasesize in this region */
)brace
suffix:semicolon
DECL|struct|mtd_info
r_struct
id|mtd_info
(brace
DECL|member|type
id|u_char
id|type
suffix:semicolon
DECL|member|flags
id|u_int32_t
id|flags
suffix:semicolon
DECL|member|size
id|u_int32_t
id|size
suffix:semicolon
singleline_comment|// Total size of the MTD
multiline_comment|/* &quot;Major&quot; erase size for the device. Na&#xfffd;ve users may take this&n;&t; * to be the only erase size available, or may use the more detailed&n;&t; * information below if they desire&n;&t; */
DECL|member|erasesize
id|u_int32_t
id|erasesize
suffix:semicolon
DECL|member|oobblock
id|u_int32_t
id|oobblock
suffix:semicolon
singleline_comment|// Size of OOB blocks (e.g. 512)
DECL|member|oobsize
id|u_int32_t
id|oobsize
suffix:semicolon
singleline_comment|// Amount of OOB data per block (e.g. 16)
DECL|member|oobavail
id|u_int32_t
id|oobavail
suffix:semicolon
singleline_comment|// Number of bytes in OOB area available for fs 
DECL|member|ecctype
id|u_int32_t
id|ecctype
suffix:semicolon
DECL|member|eccsize
id|u_int32_t
id|eccsize
suffix:semicolon
singleline_comment|// Kernel-only stuff starts here.
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
singleline_comment|// oobinfo is a nand_oobinfo structure, which can be set by iotcl (MEMSETOOBINFO)
DECL|member|oobinfo
r_struct
id|nand_oobinfo
id|oobinfo
suffix:semicolon
multiline_comment|/* Data for variable erase regions. If numeraseregions is zero,&n;&t; * it means that the whole device has erasesize as given above. &n;&t; */
DECL|member|numeraseregions
r_int
id|numeraseregions
suffix:semicolon
DECL|member|eraseregions
r_struct
id|mtd_erase_region_info
op_star
id|eraseregions
suffix:semicolon
multiline_comment|/* This really shouldn&squot;t be here. It can go away in 2.5 */
DECL|member|bank_size
id|u_int32_t
id|bank_size
suffix:semicolon
DECL|member|erase
r_int
(paren
op_star
id|erase
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|erase_info
op_star
id|instr
)paren
suffix:semicolon
multiline_comment|/* This stuff for eXecute-In-Place */
DECL|member|point
r_int
(paren
op_star
id|point
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
op_star
id|mtdbuf
)paren
suffix:semicolon
multiline_comment|/* We probably shouldn&squot;t allow XIP if the unpoint isn&squot;t a NULL */
DECL|member|unpoint
r_void
(paren
op_star
id|unpoint
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
op_star
id|addr
comma
id|loff_t
id|from
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|read_ecc
r_int
(paren
op_star
id|read_ecc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
comma
id|u_char
op_star
id|eccbuf
comma
r_struct
id|nand_oobinfo
op_star
id|oobsel
)paren
suffix:semicolon
DECL|member|write_ecc
r_int
(paren
op_star
id|write_ecc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
comma
id|u_char
op_star
id|eccbuf
comma
r_struct
id|nand_oobinfo
op_star
id|oobsel
)paren
suffix:semicolon
DECL|member|read_oob
r_int
(paren
op_star
id|read_oob
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|write_oob
r_int
(paren
op_star
id|write_oob
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Methods to access the protection register area, present in some &n;&t; * flash devices. The user data is one time programmable but the&n;&t; * factory data is read only. &n;&t; */
DECL|member|read_user_prot_reg
r_int
(paren
op_star
id|read_user_prot_reg
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|read_fact_prot_reg
r_int
(paren
op_star
id|read_fact_prot_reg
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* This function is not yet implemented */
DECL|member|write_user_prot_reg
r_int
(paren
op_star
id|write_user_prot_reg
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* kvec-based read/write methods. We need these especially for NAND flash,&n;&t;   with its limited number of write cycles per erase.&n;&t;   NB: The &squot;count&squot; parameter is the number of _vectors_, each of &n;&t;   which contains an (ofs, len) tuple.&n;&t;*/
DECL|member|readv
r_int
(paren
op_star
id|readv
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|from
comma
r_int
op_star
id|retlen
)paren
suffix:semicolon
DECL|member|readv_ecc
r_int
(paren
op_star
id|readv_ecc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|from
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|eccbuf
comma
r_struct
id|nand_oobinfo
op_star
id|oobsel
)paren
suffix:semicolon
DECL|member|writev
r_int
(paren
op_star
id|writev
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
suffix:semicolon
DECL|member|writev_ecc
r_int
(paren
op_star
id|writev_ecc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|eccbuf
comma
r_struct
id|nand_oobinfo
op_star
id|oobsel
)paren
suffix:semicolon
multiline_comment|/* Sync */
DECL|member|sync
r_void
(paren
op_star
id|sync
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
multiline_comment|/* Chip-supported device locking */
DECL|member|lock
r_int
(paren
op_star
id|lock
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|unlock
r_int
(paren
op_star
id|unlock
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* Power Management functions */
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
multiline_comment|/* Bad block management functions */
DECL|member|block_isbad
r_int
(paren
op_star
id|block_isbad
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
)paren
suffix:semicolon
DECL|member|block_markbad
r_int
(paren
op_star
id|block_markbad
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
)paren
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|usecount
r_int
id|usecount
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Kernel-side ioctl definitions */
r_extern
r_int
id|add_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
r_extern
r_int
id|del_mtd_device
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
r_extern
r_struct
id|mtd_info
op_star
id|get_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|num
)paren
suffix:semicolon
r_extern
r_void
id|put_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|struct|mtd_notifier
r_struct
id|mtd_notifier
(brace
DECL|member|add
r_void
(paren
op_star
id|add
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|register_mtd_user
(paren
r_struct
id|mtd_notifier
op_star
r_new
)paren
suffix:semicolon
r_extern
r_int
id|unregister_mtd_user
(paren
r_struct
id|mtd_notifier
op_star
id|old
)paren
suffix:semicolon
r_int
id|default_mtd_writev
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
suffix:semicolon
r_int
id|default_mtd_readv
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|from
comma
r_int
op_star
id|retlen
)paren
suffix:semicolon
DECL|macro|MTD_ERASE
mdefine_line|#define MTD_ERASE(mtd, args...) (*(mtd-&gt;erase))(mtd, args)
DECL|macro|MTD_POINT
mdefine_line|#define MTD_POINT(mtd, a,b,c,d) (*(mtd-&gt;point))(mtd, a,b,c, (u_char **)(d))
DECL|macro|MTD_UNPOINT
mdefine_line|#define MTD_UNPOINT(mtd, arg) (*(mtd-&gt;unpoint))(mtd, (u_char *)arg)
DECL|macro|MTD_READ
mdefine_line|#define MTD_READ(mtd, args...) (*(mtd-&gt;read))(mtd, args)
DECL|macro|MTD_WRITE
mdefine_line|#define MTD_WRITE(mtd, args...) (*(mtd-&gt;write))(mtd, args)
DECL|macro|MTD_READV
mdefine_line|#define MTD_READV(mtd, args...) (*(mtd-&gt;readv))(mtd, args)
DECL|macro|MTD_WRITEV
mdefine_line|#define MTD_WRITEV(mtd, args...) (*(mtd-&gt;writev))(mtd, args)
DECL|macro|MTD_READECC
mdefine_line|#define MTD_READECC(mtd, args...) (*(mtd-&gt;read_ecc))(mtd, args)
DECL|macro|MTD_WRITEECC
mdefine_line|#define MTD_WRITEECC(mtd, args...) (*(mtd-&gt;write_ecc))(mtd, args)
DECL|macro|MTD_READOOB
mdefine_line|#define MTD_READOOB(mtd, args...) (*(mtd-&gt;read_oob))(mtd, args)
DECL|macro|MTD_WRITEOOB
mdefine_line|#define MTD_WRITEOOB(mtd, args...) (*(mtd-&gt;write_oob))(mtd, args)
DECL|macro|MTD_SYNC
mdefine_line|#define MTD_SYNC(mtd) do { if (mtd-&gt;sync) (*(mtd-&gt;sync))(mtd);  } while (0) 
macro_line|#ifdef CONFIG_MTD_PARTITIONS
r_void
id|mtd_erase_callback
c_func
(paren
r_struct
id|erase_info
op_star
id|instr
)paren
suffix:semicolon
macro_line|#else
DECL|function|mtd_erase_callback
r_static
r_inline
r_void
id|mtd_erase_callback
c_func
(paren
r_struct
id|erase_info
op_star
id|instr
)paren
(brace
r_if
c_cond
(paren
id|instr-&gt;callback
)paren
id|instr
op_member_access_from_pointer
id|callback
c_func
(paren
id|instr
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Debugging macro and defines&n; */
DECL|macro|MTD_DEBUG_LEVEL0
mdefine_line|#define MTD_DEBUG_LEVEL0&t;(0)&t;/* Quiet   */
DECL|macro|MTD_DEBUG_LEVEL1
mdefine_line|#define MTD_DEBUG_LEVEL1&t;(1)&t;/* Audible */
DECL|macro|MTD_DEBUG_LEVEL2
mdefine_line|#define MTD_DEBUG_LEVEL2&t;(2)&t;/* Loud    */
DECL|macro|MTD_DEBUG_LEVEL3
mdefine_line|#define MTD_DEBUG_LEVEL3&t;(3)&t;/* Noisy   */
macro_line|#ifdef CONFIG_MTD_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)&t;&t;&t;&t;&bslash;&n; &t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (n &lt;= CONFIG_MTD_DEBUG_VERBOSE)&t;&bslash;&n;&t;&t;&t;printk(KERN_INFO args);&t;&t;&bslash;&n;&t;} while(0)
macro_line|#else /* CONFIG_MTD_DEBUG */
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) do { } while(0)
macro_line|#endif /* CONFIG_MTD_DEBUG */
macro_line|#endif /* __MTD_MTD_H__ */
eof
