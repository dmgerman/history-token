multiline_comment|/*&n; * net/core/ethtool.c - Ethtool ioctl handler&n; * Copyright (c) 2003 Matthew Wilcox &lt;matthew@wil.cx&gt;&n; *&n; * This file is where we call all the ethtool_ops commands to get&n; * the information ethtool needs.  We fall back to calling do_ioctl()&n; * for drivers which haven&squot;t been converted to ethtool_ops yet.&n; *&n; * It&squot;s GPL, stupid.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ethtool.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* &n; * Some useful ethtool_ops methods that&squot;re device independent.&n; * If we find that all drivers want to do the same thing here,&n; * we can turn these into dev_() function calls.&n; */
DECL|function|ethtool_op_get_link
id|u32
id|ethtool_op_get_link
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|netif_carrier_ok
c_func
(paren
id|dev
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_op_get_tx_csum
id|u32
id|ethtool_op_get_tx_csum
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;features
op_amp
id|NETIF_F_IP_CSUM
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_op_get_sg
id|u32
id|ethtool_op_get_sg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;features
op_amp
id|NETIF_F_SG
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_op_set_sg
r_int
id|ethtool_op_set_sg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|data
)paren
(brace
r_if
c_cond
(paren
id|data
)paren
id|dev-&gt;features
op_or_assign
id|NETIF_F_SG
suffix:semicolon
r_else
id|dev-&gt;features
op_and_assign
op_complement
id|NETIF_F_SG
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Handlers for each ethtool command */
DECL|function|ethtool_get_settings
r_static
r_int
id|ethtool_get_settings
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_cmd
id|cmd
op_assign
(brace
id|ETHTOOL_GSET
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_settings
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|err
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_settings
c_func
(paren
id|dev
comma
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|cmd
comma
r_sizeof
(paren
id|cmd
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_settings
r_static
r_int
id|ethtool_set_settings
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_cmd
id|cmd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;set_settings
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|cmd
comma
id|useraddr
comma
r_sizeof
(paren
id|cmd
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_settings
c_func
(paren
id|dev
comma
op_amp
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_drvinfo
r_static
r_int
id|ethtool_get_drvinfo
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_drvinfo
id|info
suffix:semicolon
r_struct
id|ethtool_ops
op_star
id|ops
op_assign
id|dev-&gt;ethtool_ops
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops-&gt;get_drvinfo
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.cmd
op_assign
id|ETHTOOL_GDRVINFO
suffix:semicolon
id|ops
op_member_access_from_pointer
id|get_drvinfo
c_func
(paren
id|dev
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;self_test_count
)paren
id|info.testinfo_len
op_assign
id|ops
op_member_access_from_pointer
id|self_test_count
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;get_stats_count
)paren
id|info.n_stats
op_assign
id|ops
op_member_access_from_pointer
id|get_stats_count
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;get_regs_len
)paren
id|info.regdump_len
op_assign
id|ops
op_member_access_from_pointer
id|get_regs_len
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* XXX: eeprom? */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_get_regs
r_static
r_int
id|ethtool_get_regs
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_regs
id|regs
suffix:semicolon
r_struct
id|ethtool_ops
op_star
id|ops
op_assign
id|dev-&gt;ethtool_ops
suffix:semicolon
r_void
op_star
id|regbuf
suffix:semicolon
r_int
id|reglen
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops-&gt;get_regs
op_logical_or
op_logical_neg
id|ops-&gt;get_regs_len
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|regs
comma
id|useraddr
comma
r_sizeof
(paren
id|regs
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|reglen
op_assign
id|ops
op_member_access_from_pointer
id|get_regs_len
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs.len
OG
id|reglen
)paren
id|regs.len
op_assign
id|reglen
suffix:semicolon
id|regbuf
op_assign
id|kmalloc
c_func
(paren
id|reglen
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|regbuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ops
op_member_access_from_pointer
id|get_regs
c_func
(paren
id|dev
comma
op_amp
id|regs
comma
id|regbuf
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|useraddr
op_add_assign
m_offsetof
(paren
r_struct
id|ethtool_regs
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
id|regbuf
comma
id|reglen
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|regbuf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ethtool_get_wol
r_static
r_int
id|ethtool_get_wol
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_wolinfo
id|wol
op_assign
(brace
id|ETHTOOL_GWOL
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_wol
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_wol
c_func
(paren
id|dev
comma
op_amp
id|wol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|wol
comma
r_sizeof
(paren
id|wol
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_wol
r_static
r_int
id|ethtool_set_wol
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_wolinfo
id|wol
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;set_wol
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|wol
comma
id|useraddr
comma
r_sizeof
(paren
id|wol
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_wol
c_func
(paren
id|dev
comma
op_amp
id|wol
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_msglevel
r_static
r_int
id|ethtool_get_msglevel
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
op_assign
(brace
id|ETHTOOL_GMSGLVL
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_msglevel
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|edata.data
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_msglevel
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|edata
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_msglevel
r_static
r_int
id|ethtool_set_msglevel
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;set_msglevel
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|edata
comma
id|useraddr
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_msglevel
c_func
(paren
id|dev
comma
id|edata.data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_nway_reset
r_static
r_int
id|ethtool_nway_reset
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;nway_reset
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|nway_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_link
r_static
r_int
id|ethtool_get_link
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
op_assign
(brace
id|ETHTOOL_GLINK
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_link
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|edata.data
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_link
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|edata
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_get_eeprom
r_static
r_int
id|ethtool_get_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_eeprom
id|eeprom
suffix:semicolon
id|u8
op_star
id|data
suffix:semicolon
r_int
id|len
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_eeprom
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|eeprom
comma
id|useraddr
comma
r_sizeof
(paren
id|eeprom
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|len
op_assign
id|eeprom.len
suffix:semicolon
multiline_comment|/* Check for wrap and zero */
r_if
c_cond
(paren
id|eeprom.offset
op_plus
id|len
op_le
id|eeprom.offset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|data
comma
id|useraddr
op_plus
r_sizeof
(paren
id|eeprom
)paren
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_eeprom
c_func
(paren
id|dev
comma
op_amp
id|eeprom
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|eeprom
comma
r_sizeof
(paren
id|eeprom
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
op_plus
r_sizeof
(paren
id|eeprom
)paren
comma
id|data
comma
id|eeprom.len
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ethtool_set_eeprom
r_static
r_int
id|ethtool_set_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_eeprom
id|eeprom
suffix:semicolon
id|u8
op_star
id|data
suffix:semicolon
r_int
id|len
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;set_eeprom
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|eeprom
comma
id|useraddr
comma
r_sizeof
(paren
id|eeprom
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|len
op_assign
id|eeprom.len
suffix:semicolon
multiline_comment|/* Check for wrap and zero */
r_if
c_cond
(paren
id|eeprom.offset
op_plus
id|len
op_le
id|eeprom.offset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|data
comma
id|useraddr
op_plus
r_sizeof
(paren
id|eeprom
)paren
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_eeprom
c_func
(paren
id|dev
comma
op_amp
id|eeprom
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
op_plus
r_sizeof
(paren
id|eeprom
)paren
comma
id|data
comma
id|len
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ethtool_get_coalesce
r_static
r_int
id|ethtool_get_coalesce
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_coalesce
id|coalesce
op_assign
(brace
id|ETHTOOL_GCOALESCE
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_coalesce
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_coalesce
c_func
(paren
id|dev
comma
op_amp
id|coalesce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|coalesce
comma
r_sizeof
(paren
id|coalesce
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_coalesce
r_static
r_int
id|ethtool_set_coalesce
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_coalesce
id|coalesce
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_coalesce
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|coalesce
comma
id|useraddr
comma
r_sizeof
(paren
id|coalesce
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_coalesce
c_func
(paren
id|dev
comma
op_amp
id|coalesce
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_ringparam
r_static
r_int
id|ethtool_get_ringparam
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_ringparam
id|ringparam
op_assign
(brace
id|ETHTOOL_GRINGPARAM
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_ringparam
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_ringparam
c_func
(paren
id|dev
comma
op_amp
id|ringparam
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|ringparam
comma
r_sizeof
(paren
id|ringparam
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_ringparam
r_static
r_int
id|ethtool_set_ringparam
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_ringparam
id|ringparam
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_ringparam
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ringparam
comma
id|useraddr
comma
r_sizeof
(paren
id|ringparam
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_ringparam
c_func
(paren
id|dev
comma
op_amp
id|ringparam
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_pauseparam
r_static
r_int
id|ethtool_get_pauseparam
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_pauseparam
id|pauseparam
op_assign
(brace
id|ETHTOOL_GPAUSEPARAM
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_pauseparam
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_pauseparam
c_func
(paren
id|dev
comma
op_amp
id|pauseparam
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|pauseparam
comma
r_sizeof
(paren
id|pauseparam
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_pauseparam
r_static
r_int
id|ethtool_set_pauseparam
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_pauseparam
id|pauseparam
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_pauseparam
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|pauseparam
comma
id|useraddr
comma
r_sizeof
(paren
id|pauseparam
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_pauseparam
c_func
(paren
id|dev
comma
op_amp
id|pauseparam
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_rx_csum
r_static
r_int
id|ethtool_get_rx_csum
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
op_assign
(brace
id|ETHTOOL_GRXCSUM
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_rx_csum
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|edata.data
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_rx_csum
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|edata
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_rx_csum
r_static
r_int
id|ethtool_set_rx_csum
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;set_rx_csum
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|edata
comma
id|useraddr
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_rx_csum
c_func
(paren
id|dev
comma
id|edata.data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_get_tx_csum
r_static
r_int
id|ethtool_get_tx_csum
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
op_assign
(brace
id|ETHTOOL_GTXCSUM
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_tx_csum
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|edata.data
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_tx_csum
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|edata
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_tx_csum
r_static
r_int
id|ethtool_set_tx_csum
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;set_tx_csum
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|edata
comma
id|useraddr
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_tx_csum
c_func
(paren
id|dev
comma
id|edata.data
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_sg
r_static
r_int
id|ethtool_get_sg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
op_assign
(brace
id|ETHTOOL_GSG
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;get_sg
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|edata.data
op_assign
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|get_sg
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|edata
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethtool_set_sg
r_static
r_int
id|ethtool_set_sg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|edata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;set_sg
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|edata
comma
id|useraddr
comma
r_sizeof
(paren
id|edata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|set_sg
c_func
(paren
id|dev
comma
id|edata.data
)paren
suffix:semicolon
)brace
DECL|function|ethtool_self_test
r_static
r_int
id|ethtool_self_test
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_test
id|test
suffix:semicolon
r_struct
id|ethtool_ops
op_star
id|ops
op_assign
id|dev-&gt;ethtool_ops
suffix:semicolon
id|u64
op_star
id|data
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops-&gt;self_test
op_logical_or
op_logical_neg
id|ops-&gt;self_test_count
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|test
comma
id|useraddr
comma
r_sizeof
(paren
id|test
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|test.len
op_assign
id|ops
op_member_access_from_pointer
id|self_test_count
c_func
(paren
id|dev
)paren
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
id|test.len
op_star
r_sizeof
(paren
id|u64
)paren
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ops
op_member_access_from_pointer
id|self_test
c_func
(paren
id|dev
comma
op_amp
id|test
comma
id|data
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|test
comma
r_sizeof
(paren
id|test
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|useraddr
op_add_assign
r_sizeof
(paren
id|test
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
id|data
comma
id|test.len
op_star
r_sizeof
(paren
id|u64
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ethtool_get_strings
r_static
r_int
id|ethtool_get_strings
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_gstrings
id|gstrings
suffix:semicolon
r_struct
id|ethtool_ops
op_star
id|ops
op_assign
id|dev-&gt;ethtool_ops
suffix:semicolon
id|u8
op_star
id|data
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops-&gt;get_strings
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|gstrings
comma
id|useraddr
comma
r_sizeof
(paren
id|gstrings
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|gstrings.string_set
)paren
(brace
r_case
id|ETH_SS_TEST
suffix:colon
r_if
c_cond
(paren
id|ops-&gt;self_test_count
)paren
id|gstrings.len
op_assign
id|ops
op_member_access_from_pointer
id|self_test_count
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|ETH_SS_STATS
suffix:colon
r_if
c_cond
(paren
id|ops-&gt;get_stats_count
)paren
id|gstrings.len
op_assign
id|ops
op_member_access_from_pointer
id|get_stats_count
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|data
op_assign
id|kmalloc
c_func
(paren
id|gstrings.len
op_star
id|ETH_GSTRING_LEN
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ops
op_member_access_from_pointer
id|get_strings
c_func
(paren
id|dev
comma
id|gstrings.string_set
comma
id|data
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|gstrings
comma
r_sizeof
(paren
id|gstrings
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|useraddr
op_add_assign
r_sizeof
(paren
id|gstrings
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
id|data
comma
id|gstrings.len
op_star
id|ETH_GSTRING_LEN
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ethtool_phys_id
r_static
r_int
id|ethtool_phys_id
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_value
id|id
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops-&gt;phys_id
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|id
comma
id|useraddr
comma
r_sizeof
(paren
id|id
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|dev-&gt;ethtool_ops
op_member_access_from_pointer
id|phys_id
c_func
(paren
id|dev
comma
id|id.data
)paren
suffix:semicolon
)brace
DECL|function|ethtool_get_stats
r_static
r_int
id|ethtool_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|useraddr
)paren
(brace
r_struct
id|ethtool_stats
id|stats
suffix:semicolon
r_struct
id|ethtool_ops
op_star
id|ops
op_assign
id|dev-&gt;ethtool_ops
suffix:semicolon
id|u64
op_star
id|data
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops-&gt;get_ethtool_stats
op_logical_or
op_logical_neg
id|ops-&gt;get_stats_count
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|stats
comma
id|useraddr
comma
r_sizeof
(paren
id|stats
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|stats.n_stats
op_assign
id|ops
op_member_access_from_pointer
id|get_stats_count
c_func
(paren
id|dev
)paren
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
id|stats.n_stats
op_star
r_sizeof
(paren
id|u64
)paren
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ops
op_member_access_from_pointer
id|get_ethtool_stats
c_func
(paren
id|dev
comma
op_amp
id|stats
comma
id|data
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
op_amp
id|stats
comma
r_sizeof
(paren
id|stats
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|useraddr
op_add_assign
r_sizeof
(paren
id|stats
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|useraddr
comma
id|data
comma
id|stats.n_stats
op_star
r_sizeof
(paren
id|u64
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* The main entry point in this file.  Called from net/core/dev.c */
DECL|function|dev_ethtool
r_int
id|dev_ethtool
c_func
(paren
r_struct
id|ifreq
op_star
id|ifr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|__dev_get_by_name
c_func
(paren
id|ifr-&gt;ifr_name
)paren
suffix:semicolon
r_void
op_star
id|useraddr
op_assign
(paren
r_void
op_star
)paren
id|ifr-&gt;ifr_data
suffix:semicolon
id|u32
id|ethcmd
suffix:semicolon
multiline_comment|/*&n;&t; * XXX: This can be pushed down into the ethtool_* handlers that&n;&t; * need it.  Keep existing behaviour for the moment.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|netif_device_present
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ethtool_ops
)paren
r_goto
id|ioctl
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ethcmd
comma
id|useraddr
comma
r_sizeof
(paren
id|ethcmd
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|ethcmd
)paren
(brace
r_case
id|ETHTOOL_GSET
suffix:colon
r_return
id|ethtool_get_settings
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SSET
suffix:colon
r_return
id|ethtool_set_settings
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GDRVINFO
suffix:colon
r_return
id|ethtool_get_drvinfo
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GREGS
suffix:colon
r_return
id|ethtool_get_regs
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GWOL
suffix:colon
r_return
id|ethtool_get_wol
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SWOL
suffix:colon
r_return
id|ethtool_set_wol
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GMSGLVL
suffix:colon
r_return
id|ethtool_get_msglevel
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SMSGLVL
suffix:colon
r_return
id|ethtool_set_msglevel
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_NWAY_RST
suffix:colon
r_return
id|ethtool_nway_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_case
id|ETHTOOL_GLINK
suffix:colon
r_return
id|ethtool_get_link
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GEEPROM
suffix:colon
r_return
id|ethtool_get_eeprom
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SEEPROM
suffix:colon
r_return
id|ethtool_set_eeprom
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GCOALESCE
suffix:colon
r_return
id|ethtool_get_coalesce
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SCOALESCE
suffix:colon
r_return
id|ethtool_set_coalesce
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GRINGPARAM
suffix:colon
r_return
id|ethtool_get_ringparam
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SRINGPARAM
suffix:colon
r_return
id|ethtool_set_ringparam
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GPAUSEPARAM
suffix:colon
r_return
id|ethtool_get_pauseparam
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SPAUSEPARAM
suffix:colon
r_return
id|ethtool_set_pauseparam
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GRXCSUM
suffix:colon
r_return
id|ethtool_get_rx_csum
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SRXCSUM
suffix:colon
r_return
id|ethtool_set_rx_csum
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GTXCSUM
suffix:colon
r_return
id|ethtool_get_tx_csum
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_STXCSUM
suffix:colon
r_return
id|ethtool_set_tx_csum
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GSG
suffix:colon
r_return
id|ethtool_get_sg
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_SSG
suffix:colon
r_return
id|ethtool_set_sg
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_TEST
suffix:colon
r_return
id|ethtool_self_test
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GSTRINGS
suffix:colon
r_return
id|ethtool_get_strings
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_PHYS_ID
suffix:colon
r_return
id|ethtool_phys_id
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_case
id|ETHTOOL_GSTATS
suffix:colon
r_return
id|ethtool_get_stats
c_func
(paren
id|dev
comma
id|useraddr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
id|ioctl
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;do_ioctl
)paren
r_return
id|dev
op_member_access_from_pointer
id|do_ioctl
c_func
(paren
id|dev
comma
id|ifr
comma
id|SIOCETHTOOL
)paren
suffix:semicolon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
eof
