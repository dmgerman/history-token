macro_line|#include &quot;ixj-ver.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;&t;/* printk() */
macro_line|#include &lt;linux/fs.h&gt;&t;&t;/* everything... */
macro_line|#include &lt;linux/errno.h&gt;&t;/* error codes */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &quot;ixj.h&quot;
multiline_comment|/*&n; *&t;PCMCIA service support for Quicknet cards&n; */
macro_line|#ifdef PCMCIA_DEBUG
DECL|variable|pc_debug
r_static
r_int
id|pc_debug
op_assign
id|PCMCIA_DEBUG
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|pc_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) if (pc_debug&gt;(n)) printk(KERN_DEBUG args)
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
DECL|struct|ixj_info_t
r_typedef
r_struct
id|ixj_info_t
(brace
DECL|member|ndev
r_int
id|ndev
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|member|port
r_struct
id|ixj
op_star
id|port
suffix:semicolon
DECL|typedef|ixj_info_t
)brace
id|ixj_info_t
suffix:semicolon
r_static
id|dev_link_t
op_star
id|ixj_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|ixj_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|ixj_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|ixj_cs_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|ixj_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
suffix:semicolon
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;ixj_cs&quot;
suffix:semicolon
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
op_assign
l_int|NULL
suffix:semicolon
DECL|function|ixj_attach
r_static
id|dev_link_t
op_star
id|ixj_attach
c_func
(paren
r_void
)paren
(brace
id|client_reg_t
id|client_reg
suffix:semicolon
id|dev_link_t
op_star
id|link
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ixj_attach()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Create new ixj device */
id|link
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dev_link_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|link
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dev_link_t
)paren
)paren
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.Attributes2
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
l_int|3
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
l_int|50
suffix:semicolon
id|link-&gt;conf.IntType
op_assign
id|INT_MEMORY_AND_IO
suffix:semicolon
id|link-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ixj_info_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link-&gt;priv
)paren
(brace
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|link-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ixj_info_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Register with Card Services */
id|link-&gt;next
op_assign
id|dev_list
suffix:semicolon
id|dev_list
op_assign
id|link
suffix:semicolon
id|client_reg.dev_info
op_assign
op_amp
id|dev_info
suffix:semicolon
id|client_reg.Attributes
op_assign
id|INFO_IO_CLIENT
op_or
id|INFO_CARD_SHARE
suffix:semicolon
id|client_reg.EventMask
op_assign
id|CS_EVENT_CARD_INSERTION
op_or
id|CS_EVENT_CARD_REMOVAL
op_or
id|CS_EVENT_RESET_PHYSICAL
op_or
id|CS_EVENT_CARD_RESET
op_or
id|CS_EVENT_PM_SUSPEND
op_or
id|CS_EVENT_PM_RESUME
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|ixj_event
suffix:semicolon
id|client_reg.Version
op_assign
l_int|0x0210
suffix:semicolon
id|client_reg.event_callback_args.client_data
op_assign
id|link
suffix:semicolon
id|ret
op_assign
id|CardServices
c_func
(paren
id|RegisterClient
comma
op_amp
id|link-&gt;handle
comma
op_amp
id|client_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RegisterClient
comma
id|ret
)paren
suffix:semicolon
id|ixj_detach
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|link
suffix:semicolon
)brace
DECL|function|ixj_detach
r_static
r_void
id|ixj_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ixj_detach(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
r_for
c_loop
(paren
id|linkp
op_assign
op_amp
id|dev_list
suffix:semicolon
op_star
id|linkp
suffix:semicolon
id|linkp
op_assign
op_amp
(paren
op_star
id|linkp
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
op_star
id|linkp
op_eq
id|link
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|linkp
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_RELEASE_PENDING
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|ixj_cs_release
c_func
(paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;handle
)paren
(brace
id|ret
op_assign
id|CardServices
c_func
(paren
id|DeregisterClient
comma
id|link-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CS_SUCCESS
)paren
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|DeregisterClient
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* Unlink device structure, free bits */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|link-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, args...) &bslash;&n;while ((last_ret=CardServices(last_fn=(fn), args))!=0) goto cs_failed
DECL|macro|CFG_CHECK
mdefine_line|#define CFG_CHECK(fn, args...) &bslash;&n;if (CardServices(fn, args) != 0) goto next_entry
DECL|function|ixj_get_serial
r_static
r_void
id|ixj_get_serial
c_func
(paren
id|dev_link_t
op_star
id|link
comma
id|IXJ
op_star
id|j
)paren
(brace
id|client_handle_t
id|handle
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|u_short
id|buf
(braket
l_int|128
)braket
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
r_int
id|last_ret
comma
id|last_fn
comma
id|i
comma
id|place
suffix:semicolon
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ixj_get_serial(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
id|buf
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|80
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_VERS_1
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|str
op_assign
(paren
r_char
op_star
)paren
id|buf
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCMCIA Version %d.%d&bslash;n&quot;
comma
id|str
(braket
l_int|0
)braket
comma
id|str
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|str
op_add_assign
l_int|2
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|str
)paren
suffix:semicolon
id|str
op_assign
id|str
op_plus
id|strlen
c_func
(paren
id|str
)paren
op_plus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %s&quot;
comma
id|str
)paren
suffix:semicolon
id|str
op_assign
id|str
op_plus
id|strlen
c_func
(paren
id|str
)paren
op_plus
l_int|1
suffix:semicolon
id|place
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|strlen
c_func
(paren
id|str
)paren
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_switch
c_cond
(paren
id|str
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;0&squot;
suffix:colon
r_case
l_char|&squot;1&squot;
suffix:colon
r_case
l_char|&squot;2&squot;
suffix:colon
r_case
l_char|&squot;3&squot;
suffix:colon
r_case
l_char|&squot;4&squot;
suffix:colon
r_case
l_char|&squot;5&squot;
suffix:colon
r_case
l_char|&squot;6&squot;
suffix:colon
r_case
l_char|&squot;7&squot;
suffix:colon
r_case
l_char|&squot;8&squot;
suffix:colon
r_case
l_char|&squot;9&squot;
suffix:colon
id|j-&gt;serial
op_add_assign
(paren
id|str
(braket
id|i
)braket
op_minus
l_int|48
)paren
op_star
id|place
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;A&squot;
suffix:colon
r_case
l_char|&squot;B&squot;
suffix:colon
r_case
l_char|&squot;C&squot;
suffix:colon
r_case
l_char|&squot;D&squot;
suffix:colon
r_case
l_char|&squot;E&squot;
suffix:colon
r_case
l_char|&squot;F&squot;
suffix:colon
id|j-&gt;serial
op_add_assign
(paren
id|str
(braket
id|i
)braket
op_minus
l_int|55
)paren
op_star
id|place
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
suffix:colon
r_case
l_char|&squot;b&squot;
suffix:colon
r_case
l_char|&squot;c&squot;
suffix:colon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;e&squot;
suffix:colon
r_case
l_char|&squot;f&squot;
suffix:colon
id|j-&gt;serial
op_add_assign
(paren
id|str
(braket
id|i
)braket
op_minus
l_int|87
)paren
op_star
id|place
suffix:semicolon
r_break
suffix:semicolon
)brace
id|place
op_assign
id|place
op_star
l_int|0x10
suffix:semicolon
)brace
id|str
op_assign
id|str
op_plus
id|strlen
c_func
(paren
id|str
)paren
op_plus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; version %s&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
id|cs_failed
suffix:colon
r_return
suffix:semicolon
)brace
DECL|function|ixj_config
r_static
r_void
id|ixj_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|IXJ
op_star
id|j
suffix:semicolon
id|client_handle_t
id|handle
suffix:semicolon
id|ixj_info_t
op_star
id|info
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|u_short
id|buf
(braket
l_int|128
)braket
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|config_info_t
id|conf
suffix:semicolon
id|cistpl_cftable_entry_t
op_star
id|cfg
op_assign
op_amp
id|parse.cftable_entry
suffix:semicolon
id|cistpl_cftable_entry_t
id|dflt
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
id|last_ret
comma
id|last_fn
suffix:semicolon
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ixj_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
id|buf
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|255
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|ParseTuple
comma
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
id|link-&gt;conf.ConfigBase
op_assign
id|parse.config.base
suffix:semicolon
id|link-&gt;conf.Present
op_assign
id|parse.config.rmask
(braket
l_int|0
)braket
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetConfigurationInfo
comma
id|handle
comma
op_amp
id|conf
)paren
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CFTABLE_ENTRY
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|CFG_CHECK
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CFG_CHECK
c_func
(paren
id|ParseTuple
comma
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cfg-&gt;io.nwin
OG
l_int|0
)paren
op_logical_or
(paren
id|dflt.io.nwin
OG
l_int|0
)paren
)paren
(brace
id|cistpl_io_t
op_star
id|io
op_assign
(paren
id|cfg-&gt;io.nwin
)paren
ques
c_cond
op_amp
id|cfg-&gt;io
suffix:colon
op_amp
id|dflt.io
suffix:semicolon
id|link-&gt;conf.ConfigIndex
op_assign
id|cfg-&gt;index
suffix:semicolon
id|link-&gt;io.BasePort1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;nwin
op_eq
l_int|2
)paren
(brace
id|link-&gt;io.BasePort2
op_assign
id|io-&gt;win
(braket
l_int|1
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.NumPorts2
op_assign
id|io-&gt;win
(braket
l_int|1
)braket
dot
id|len
suffix:semicolon
)brace
id|CFG_CHECK
c_func
(paren
id|RequestIO
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
multiline_comment|/* If we&squot;ve got this far, we&squot;re done */
r_break
suffix:semicolon
)brace
id|next_entry
suffix:colon
r_if
c_cond
(paren
id|cfg-&gt;flags
op_amp
id|CISTPL_CFTABLE_DEFAULT
)paren
id|dflt
op_assign
op_star
id|cfg
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetNextTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
)brace
id|CS_CHECK
c_func
(paren
id|RequestConfiguration
comma
id|handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
multiline_comment|/*&n; &t; *&t;Register the card with the core.&n; &t; */
id|j
op_assign
id|ixj_pcmcia_probe
c_func
(paren
id|link-&gt;io.BasePort1
comma
id|link-&gt;io.BasePort1
op_plus
l_int|0x10
)paren
suffix:semicolon
id|info-&gt;ndev
op_assign
l_int|1
suffix:semicolon
id|info-&gt;node.major
op_assign
id|PHONE_MAJOR
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|info-&gt;node
suffix:semicolon
id|ixj_get_serial
c_func
(paren
id|link
comma
id|j
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
r_return
suffix:semicolon
id|cs_failed
suffix:colon
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|last_fn
comma
id|last_ret
)paren
suffix:semicolon
id|ixj_cs_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
DECL|function|ixj_cs_release
r_static
r_void
id|ixj_cs_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|ixj_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ixj_cs_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|info-&gt;ndev
op_assign
l_int|0
suffix:semicolon
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
id|link-&gt;handle
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseIO
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
)brace
DECL|function|ixj_event
r_static
r_int
id|ixj_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
(brace
id|dev_link_t
op_star
id|link
op_assign
id|args-&gt;client_data
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;ixj_event(0x%06x)&bslash;n&quot;
comma
id|event
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CS_EVENT_CARD_REMOVAL
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_PRESENT
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|link-&gt;state
op_or_assign
id|DEV_RELEASE_PENDING
suffix:semicolon
id|ixj_cs_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CS_EVENT_CARD_INSERTION
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_PRESENT
op_or
id|DEV_CONFIG_PENDING
suffix:semicolon
id|ixj_config
c_func
(paren
id|link
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_SUSPEND
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_RESET_PHYSICAL
suffix:colon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
id|link-&gt;handle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_RESUME
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_CARD_RESET
suffix:colon
r_if
c_cond
(paren
id|DEV_OK
c_func
(paren
id|link
)paren
)paren
id|CardServices
c_func
(paren
id|RequestConfiguration
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ixj_driver
r_static
r_struct
id|pcmcia_driver
id|ixj_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ixj_cs&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|ixj_attach
comma
dot
id|detach
op_assign
id|ixj_detach
comma
)brace
suffix:semicolon
DECL|function|ixj_pcmcia_init
r_static
r_int
id|__init
id|ixj_pcmcia_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pcmcia_register_driver
c_func
(paren
op_amp
id|ixj_driver
)paren
suffix:semicolon
)brace
DECL|function|ixj_pcmcia_exit
r_static
r_void
id|ixj_pcmcia_exit
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|ixj_driver
)paren
suffix:semicolon
multiline_comment|/* XXX: this really needs to move into generic code.. */
r_while
c_loop
(paren
id|dev_list
op_ne
l_int|NULL
)paren
id|ixj_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
DECL|variable|ixj_pcmcia_init
id|module_init
c_func
(paren
id|ixj_pcmcia_init
)paren
suffix:semicolon
DECL|variable|ixj_pcmcia_exit
id|module_exit
c_func
(paren
id|ixj_pcmcia_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
