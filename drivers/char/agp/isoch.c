multiline_comment|/*&n; * Setup routines for AGP 3.5 compliant bridges.&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;agp.h&quot;
multiline_comment|/* Generic AGP 3.5 enabling routines */
DECL|struct|agp_3_5_dev
r_struct
id|agp_3_5_dev
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|capndx
id|u8
id|capndx
suffix:semicolon
DECL|member|maxbw
id|u32
id|maxbw
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|function|agp_3_5_dev_list_insert
r_static
r_void
id|agp_3_5_dev_list_insert
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|list_head
op_star
r_new
)paren
(brace
r_struct
id|agp_3_5_dev
op_star
id|cur
comma
op_star
id|n
op_assign
id|list_entry
c_func
(paren
r_new
comma
r_struct
id|agp_3_5_dev
comma
id|list
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
id|head
)paren
(brace
id|cur
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|agp_3_5_dev
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur-&gt;maxbw
OG
id|n-&gt;maxbw
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
r_new
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|agp_3_5_dev_list_sort
r_static
r_void
id|agp_3_5_dev_list_sort
c_func
(paren
r_struct
id|agp_3_5_dev
op_star
id|list
comma
r_int
r_int
id|ndevs
)paren
(brace
r_struct
id|agp_3_5_dev
op_star
id|cur
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
comma
op_star
id|head
op_assign
op_amp
id|list-&gt;list
comma
op_star
id|start
op_assign
id|head-&gt;next
suffix:semicolon
id|u32
id|nistat
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
id|start
suffix:semicolon
id|pos
op_ne
id|head
suffix:semicolon
)paren
(brace
id|cur
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|agp_3_5_dev
comma
id|list
)paren
suffix:semicolon
id|dev
op_assign
id|cur-&gt;dev
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|cur-&gt;capndx
op_plus
id|AGPNISTAT
comma
op_amp
id|nistat
)paren
suffix:semicolon
id|cur-&gt;maxbw
op_assign
(paren
id|nistat
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|tmp
op_assign
id|pos
suffix:semicolon
id|pos
op_assign
id|pos-&gt;next
suffix:semicolon
id|agp_3_5_dev_list_insert
c_func
(paren
id|head
comma
id|tmp
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * Initialize all isochronous transfer parameters for an AGP 3.0 &n; * node (i.e. a host bridge in combination with the adapters &n; * lying behind it...)&n; */
DECL|function|agp_3_5_isochronous_node_enable
r_static
r_int
id|agp_3_5_isochronous_node_enable
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
comma
r_struct
id|agp_3_5_dev
op_star
id|dev_list
comma
r_int
r_int
id|ndevs
)paren
(brace
multiline_comment|/*&n;&t; * Convenience structure to make the calculations clearer&n;&t; * here.  The field names come straight from the AGP 3.0 spec.&n;&t; */
r_struct
id|isoch_data
(brace
id|u32
id|maxbw
suffix:semicolon
id|u32
id|n
suffix:semicolon
id|u32
id|y
suffix:semicolon
id|u32
id|l
suffix:semicolon
id|u32
id|rq
suffix:semicolon
r_struct
id|agp_3_5_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|pci_dev
op_star
id|td
op_assign
id|bridge-&gt;dev
comma
op_star
id|dev
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
op_amp
id|dev_list-&gt;list
comma
op_star
id|pos
suffix:semicolon
r_struct
id|agp_3_5_dev
op_star
id|cur
suffix:semicolon
r_struct
id|isoch_data
op_star
id|master
comma
id|target
suffix:semicolon
r_int
r_int
id|cdev
op_assign
l_int|0
suffix:semicolon
id|u32
id|mnistat
comma
id|tnistat
comma
id|tstatus
comma
id|mcmd
suffix:semicolon
id|u16
id|tnicmd
comma
id|mnicmd
suffix:semicolon
id|u8
id|mcapndx
suffix:semicolon
id|u32
id|tot_bw
op_assign
l_int|0
comma
id|tot_n
op_assign
l_int|0
comma
id|tot_rq
op_assign
l_int|0
comma
id|y_max
comma
id|rq_isoch
comma
id|rq_async
suffix:semicolon
id|u32
id|step
comma
id|rem
comma
id|rem_isoch
comma
id|rem_async
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We&squot;ll work with an array of isoch_data&squot;s (one for each&n;&t; * device in dev_list) throughout this function.&n;&t; */
r_if
c_cond
(paren
(paren
id|master
op_assign
id|kmalloc
c_func
(paren
id|ndevs
op_star
r_sizeof
(paren
op_star
id|master
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|get_out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Sort the device list by maxbw.  We need to do this because the&n;&t; * spec suggests that the devices with the smallest requirements&n;&t; * have their resources allocated first, with all remaining resources&n;&t; * falling to the device with the largest requirement.&n;&t; *&n;&t; * We don&squot;t exactly do this, we divide target resources by ndevs&n;&t; * and split them amongst the AGP 3.0 devices.  The remainder of such&n;&t; * division operations are dropped on the last device, sort of like&n;&t; * the spec mentions it should be done.&n;&t; *&n;&t; * We can&squot;t do this sort when we initially construct the dev_list&n;&t; * because we don&squot;t know until this function whether isochronous&n;&t; * transfers are enabled and consequently whether maxbw will mean&n;&t; * anything.&n;&t; */
id|agp_3_5_dev_list_sort
c_func
(paren
id|dev_list
comma
id|ndevs
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|td
comma
id|bridge-&gt;capndx
op_plus
id|AGPNISTAT
comma
op_amp
id|tnistat
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|td
comma
id|bridge-&gt;capndx
op_plus
id|AGPSTAT
comma
op_amp
id|tstatus
)paren
suffix:semicolon
multiline_comment|/* Extract power-on defaults from the target */
id|target.maxbw
op_assign
(paren
id|tnistat
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|target.n
op_assign
(paren
id|tnistat
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|target.y
op_assign
(paren
id|tnistat
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
suffix:semicolon
id|target.l
op_assign
(paren
id|tnistat
op_rshift
l_int|3
)paren
op_amp
l_int|0x7
suffix:semicolon
id|target.rq
op_assign
(paren
id|tstatus
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|y_max
op_assign
id|target.y
suffix:semicolon
multiline_comment|/*&n;&t; * Extract power-on defaults for each device in dev_list.  Along&n;&t; * the way, calculate the total isochronous bandwidth required&n;&t; * by these devices and the largest requested payload size.&n;&t; */
id|list_for_each
c_func
(paren
id|pos
comma
id|head
)paren
(brace
id|cur
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|agp_3_5_dev
comma
id|list
)paren
suffix:semicolon
id|dev
op_assign
id|cur-&gt;dev
suffix:semicolon
id|mcapndx
op_assign
id|cur-&gt;capndx
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|cur-&gt;capndx
op_plus
id|AGPNISTAT
comma
op_amp
id|mnistat
)paren
suffix:semicolon
id|master
(braket
id|cdev
)braket
dot
id|maxbw
op_assign
(paren
id|mnistat
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|master
(braket
id|cdev
)braket
dot
id|n
op_assign
(paren
id|mnistat
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|master
(braket
id|cdev
)braket
dot
id|y
op_assign
(paren
id|mnistat
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
suffix:semicolon
id|master
(braket
id|cdev
)braket
dot
id|dev
op_assign
id|cur
suffix:semicolon
id|tot_bw
op_add_assign
id|master
(braket
id|cdev
)braket
dot
id|maxbw
suffix:semicolon
id|y_max
op_assign
id|max
c_func
(paren
id|y_max
comma
id|master
(braket
id|cdev
)braket
dot
id|y
)paren
suffix:semicolon
id|cdev
op_increment
suffix:semicolon
)brace
multiline_comment|/* Check if this configuration has any chance of working */
r_if
c_cond
(paren
id|tot_bw
OG
id|target.maxbw
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;isochronous bandwidth required &quot;
l_string|&quot;by AGP 3.0 devices exceeds that which is supported by &quot;
l_string|&quot;the AGP 3.0 bridge!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|free_and_exit
suffix:semicolon
)brace
id|target.y
op_assign
id|y_max
suffix:semicolon
multiline_comment|/*&n;&t; * Write the calculated payload size into the target&squot;s NICMD&n;&t; * register.  Doing this directly effects the ISOCH_N value&n;&t; * in the target&squot;s NISTAT register, so we need to do this now&n;&t; * to get an accurate value for ISOCH_N later.&n;&t; */
id|pci_read_config_word
c_func
(paren
id|td
comma
id|bridge-&gt;capndx
op_plus
id|AGPNICMD
comma
op_amp
id|tnicmd
)paren
suffix:semicolon
id|tnicmd
op_and_assign
op_complement
(paren
l_int|0x3
op_lshift
l_int|6
)paren
suffix:semicolon
id|tnicmd
op_or_assign
id|target.y
op_lshift
l_int|6
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|td
comma
id|bridge-&gt;capndx
op_plus
id|AGPNICMD
comma
id|tnicmd
)paren
suffix:semicolon
multiline_comment|/* Reread the target&squot;s ISOCH_N */
id|pci_read_config_dword
c_func
(paren
id|td
comma
id|bridge-&gt;capndx
op_plus
id|AGPNISTAT
comma
op_amp
id|tnistat
)paren
suffix:semicolon
id|target.n
op_assign
(paren
id|tnistat
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* Calculate the minimum ISOCH_N needed by each master */
r_for
c_loop
(paren
id|cdev
op_assign
l_int|0
suffix:semicolon
id|cdev
OL
id|ndevs
suffix:semicolon
id|cdev
op_increment
)paren
(brace
id|master
(braket
id|cdev
)braket
dot
id|y
op_assign
id|target.y
suffix:semicolon
id|master
(braket
id|cdev
)braket
dot
id|n
op_assign
id|master
(braket
id|cdev
)braket
dot
id|maxbw
op_div
(paren
id|master
(braket
id|cdev
)braket
dot
id|y
op_plus
l_int|1
)paren
suffix:semicolon
id|tot_n
op_add_assign
id|master
(braket
id|cdev
)braket
dot
id|n
suffix:semicolon
)brace
multiline_comment|/* Exit if the minimal ISOCH_N allocation among the masters is more&n;&t; * than the target can handle. */
r_if
c_cond
(paren
id|tot_n
OG
id|target.n
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;number of isochronous &quot;
l_string|&quot;transactions per period required by AGP 3.0 devices &quot;
l_string|&quot;exceeds that which is supported by the AGP 3.0 &quot;
l_string|&quot;bridge!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|free_and_exit
suffix:semicolon
)brace
multiline_comment|/* Calculate left over ISOCH_N capability in the target.  We&squot;ll give&n;&t; * this to the hungriest device (as per the spec) */
id|rem
op_assign
id|target.n
op_minus
id|tot_n
suffix:semicolon
multiline_comment|/* &n;&t; * Calculate the minimum isochronous RQ depth needed by each master.&n;&t; * Along the way, distribute the extra ISOCH_N capability calculated&n;&t; * above.&n;&t; */
r_for
c_loop
(paren
id|cdev
op_assign
l_int|0
suffix:semicolon
id|cdev
OL
id|ndevs
suffix:semicolon
id|cdev
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is a little subtle.  If ISOCH_Y &gt; 64B, then ISOCH_Y&n;&t;&t; * byte isochronous writes will be broken into 64B pieces.&n;&t;&t; * This means we need to budget more RQ depth to account for&n;&t;&t; * these kind of writes (each isochronous write is actually&n;&t;&t; * many writes on the AGP bus).&n;&t;&t; */
id|master
(braket
id|cdev
)braket
dot
id|rq
op_assign
id|master
(braket
id|cdev
)braket
dot
id|n
suffix:semicolon
r_if
c_cond
(paren
id|master
(braket
id|cdev
)braket
dot
id|y
OG
l_int|0x1
)paren
(brace
id|master
(braket
id|cdev
)braket
dot
id|rq
op_mul_assign
(paren
l_int|1
op_lshift
(paren
id|master
(braket
id|cdev
)braket
dot
id|y
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
id|tot_rq
op_add_assign
id|master
(braket
id|cdev
)braket
dot
id|rq
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_eq
id|ndevs
op_minus
l_int|1
)paren
id|master
(braket
id|cdev
)braket
dot
id|n
op_add_assign
id|rem
suffix:semicolon
)brace
multiline_comment|/* Figure the number of isochronous and asynchronous RQ slots the&n;&t; * target is providing. */
id|rq_isoch
op_assign
(paren
id|target.y
OG
l_int|0x1
)paren
ques
c_cond
id|target.n
op_star
(paren
l_int|1
op_lshift
(paren
id|target.y
op_minus
l_int|1
)paren
)paren
suffix:colon
id|target.n
suffix:semicolon
id|rq_async
op_assign
id|target.rq
op_minus
id|rq_isoch
suffix:semicolon
multiline_comment|/* Exit if the minimal RQ needs of the masters exceeds what the target&n;&t; * can provide. */
r_if
c_cond
(paren
id|tot_rq
OG
id|rq_isoch
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;number of request queue slots &quot;
l_string|&quot;required by the isochronous bandwidth requested by &quot;
l_string|&quot;AGP 3.0 devices exceeds the number provided by the &quot;
l_string|&quot;AGP 3.0 bridge!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|free_and_exit
suffix:semicolon
)brace
multiline_comment|/* Calculate asynchronous RQ capability in the target (per master) as&n;&t; * well as the total number of leftover isochronous RQ slots. */
id|step
op_assign
id|rq_async
op_div
id|ndevs
suffix:semicolon
id|rem_async
op_assign
id|step
op_plus
(paren
id|rq_async
op_mod
id|ndevs
)paren
suffix:semicolon
id|rem_isoch
op_assign
id|rq_isoch
op_minus
id|tot_rq
suffix:semicolon
multiline_comment|/* Distribute the extra RQ slots calculated above and write our&n;&t; * isochronous settings out to the actual devices. */
r_for
c_loop
(paren
id|cdev
op_assign
l_int|0
suffix:semicolon
id|cdev
OL
id|ndevs
suffix:semicolon
id|cdev
op_increment
)paren
(brace
id|cur
op_assign
id|master
(braket
id|cdev
)braket
dot
id|dev
suffix:semicolon
id|dev
op_assign
id|cur-&gt;dev
suffix:semicolon
id|mcapndx
op_assign
id|cur-&gt;capndx
suffix:semicolon
id|master
(braket
id|cdev
)braket
dot
id|rq
op_add_assign
(paren
id|cdev
op_eq
id|ndevs
op_minus
l_int|1
)paren
ques
c_cond
(paren
id|rem_async
op_plus
id|rem_isoch
)paren
suffix:colon
id|step
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|cur-&gt;capndx
op_plus
id|AGPNICMD
comma
op_amp
id|mnicmd
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|cur-&gt;capndx
op_plus
id|AGPCMD
comma
op_amp
id|mcmd
)paren
suffix:semicolon
id|mnicmd
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
l_int|8
)paren
suffix:semicolon
id|mnicmd
op_and_assign
op_complement
(paren
l_int|0x3
op_lshift
l_int|6
)paren
suffix:semicolon
id|mcmd
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
l_int|24
)paren
suffix:semicolon
id|mnicmd
op_or_assign
id|master
(braket
id|cdev
)braket
dot
id|n
op_lshift
l_int|8
suffix:semicolon
id|mnicmd
op_or_assign
id|master
(braket
id|cdev
)braket
dot
id|y
op_lshift
l_int|6
suffix:semicolon
id|mcmd
op_or_assign
id|master
(braket
id|cdev
)braket
dot
id|rq
op_lshift
l_int|24
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|cur-&gt;capndx
op_plus
id|AGPCMD
comma
id|mcmd
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|cur-&gt;capndx
op_plus
id|AGPNICMD
comma
id|mnicmd
)paren
suffix:semicolon
)brace
id|free_and_exit
suffix:colon
id|kfree
c_func
(paren
id|master
)paren
suffix:semicolon
id|get_out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * This function basically allocates request queue slots among the&n; * AGP 3.0 systems in nonisochronous nodes.  The algorithm is&n; * pretty stupid, divide the total number of RQ slots provided by the&n; * target by ndevs.  Distribute this many slots to each AGP 3.0 device,&n; * giving any left over slots to the last device in dev_list.&n; */
DECL|function|agp_3_5_nonisochronous_node_enable
r_static
r_void
id|agp_3_5_nonisochronous_node_enable
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
comma
r_struct
id|agp_3_5_dev
op_star
id|dev_list
comma
r_int
r_int
id|ndevs
)paren
(brace
r_struct
id|agp_3_5_dev
op_star
id|cur
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
op_amp
id|dev_list-&gt;list
comma
op_star
id|pos
suffix:semicolon
id|u32
id|tstatus
comma
id|mcmd
suffix:semicolon
id|u32
id|trq
comma
id|mrq
comma
id|rem
suffix:semicolon
r_int
r_int
id|cdev
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|bridge-&gt;dev
comma
id|bridge-&gt;capndx
op_plus
id|AGPSTAT
comma
op_amp
id|tstatus
)paren
suffix:semicolon
id|trq
op_assign
(paren
id|tstatus
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|mrq
op_assign
id|trq
op_div
id|ndevs
suffix:semicolon
id|rem
op_assign
id|mrq
op_plus
(paren
id|trq
op_mod
id|ndevs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
id|head-&gt;next
suffix:semicolon
id|cdev
OL
id|ndevs
suffix:semicolon
id|cdev
op_increment
comma
id|pos
op_assign
id|pos-&gt;next
)paren
(brace
id|cur
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|agp_3_5_dev
comma
id|list
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|cur-&gt;dev
comma
id|cur-&gt;capndx
op_plus
id|AGPCMD
comma
op_amp
id|mcmd
)paren
suffix:semicolon
id|mcmd
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
l_int|24
)paren
suffix:semicolon
id|mcmd
op_or_assign
(paren
(paren
id|cdev
op_eq
id|ndevs
op_minus
l_int|1
)paren
ques
c_cond
id|rem
suffix:colon
id|mrq
)paren
op_lshift
l_int|24
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|cur-&gt;dev
comma
id|cur-&gt;capndx
op_plus
id|AGPCMD
comma
id|mcmd
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Fully configure and enable an AGP 3.0 host bridge and all the devices&n; * lying behind it.&n; */
DECL|function|agp_3_5_enable
r_int
id|agp_3_5_enable
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
(brace
r_struct
id|pci_dev
op_star
id|td
op_assign
id|bridge-&gt;dev
comma
op_star
id|dev
suffix:semicolon
id|u8
id|mcapndx
suffix:semicolon
id|u32
id|isoch
comma
id|arqsz
suffix:semicolon
id|u32
id|tstatus
comma
id|mstatus
comma
id|ncapid
suffix:semicolon
id|u32
id|mmajor
suffix:semicolon
id|u16
id|mpstat
suffix:semicolon
r_struct
id|agp_3_5_dev
op_star
id|dev_list
comma
op_star
id|cur
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|pos
suffix:semicolon
r_int
r_int
id|ndevs
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Extract some power-on defaults from the target */
id|pci_read_config_dword
c_func
(paren
id|td
comma
id|bridge-&gt;capndx
op_plus
id|AGPSTAT
comma
op_amp
id|tstatus
)paren
suffix:semicolon
id|isoch
op_assign
(paren
id|tstatus
op_rshift
l_int|17
)paren
op_amp
l_int|0x1
suffix:semicolon
r_if
c_cond
(paren
id|isoch
op_eq
l_int|0
)paren
multiline_comment|/* isoch xfers not available, bail out. */
r_return
op_minus
id|ENODEV
suffix:semicolon
id|arqsz
op_assign
(paren
id|tstatus
op_rshift
l_int|13
)paren
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/* &n;&t; * Allocate a head for our AGP 3.5 device list&n;&t; * (multiple AGP v3 devices are allowed behind a single bridge). &n;&t; */
r_if
c_cond
(paren
(paren
id|dev_list
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev_list
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|get_out
suffix:semicolon
)brace
id|head
op_assign
op_amp
id|dev_list-&gt;list
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
multiline_comment|/* Find all AGP devices, and add them to dev_list. */
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|mcapndx
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcapndx
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_amp
l_int|0xff00
)paren
(brace
r_case
l_int|0x0600
suffix:colon
multiline_comment|/* Bridge */
multiline_comment|/* Skip bridges. We should call this function for each one. */
r_continue
suffix:semicolon
r_case
l_int|0x0001
suffix:colon
multiline_comment|/* Unclassified device */
multiline_comment|/* Don&squot;t know what this is, but log it for investigation. */
r_if
c_cond
(paren
id|mcapndx
op_ne
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Wacky, found unclassified AGP device. %x:%x&bslash;n&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_int|0x0300
suffix:colon
multiline_comment|/* Display controller */
r_case
l_int|0x0400
suffix:colon
multiline_comment|/* Multimedia controller */
r_if
c_cond
(paren
(paren
id|cur
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cur
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|free_and_exit
suffix:semicolon
)brace
id|cur-&gt;dev
op_assign
id|dev
suffix:semicolon
id|pos
op_assign
op_amp
id|cur-&gt;list
suffix:semicolon
id|list_add
c_func
(paren
id|pos
comma
id|head
)paren
suffix:semicolon
id|ndevs
op_increment
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Take an initial pass through the devices lying behind our host&n;&t; * bridge.  Make sure each one is actually an AGP 3.0 device, otherwise&n;&t; * exit with an error message.  Along the way store the AGP 3.0&n;&t; * cap_ptr for each device&n;&t; */
id|list_for_each
c_func
(paren
id|pos
comma
id|head
)paren
(brace
id|cur
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|agp_3_5_dev
comma
id|list
)paren
suffix:semicolon
id|dev
op_assign
id|cur-&gt;dev
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_STATUS
comma
op_amp
id|mpstat
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mpstat
op_amp
id|PCI_STATUS_CAP_LIST
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CAPABILITY_LIST
comma
op_amp
id|mcapndx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcapndx
op_ne
l_int|0
)paren
(brace
r_do
(brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|mcapndx
comma
op_amp
id|ncapid
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ncapid
op_amp
l_int|0xff
)paren
op_ne
l_int|2
)paren
id|mcapndx
op_assign
(paren
id|ncapid
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|ncapid
op_amp
l_int|0xff
)paren
op_ne
l_int|2
)paren
op_logical_and
(paren
id|mcapndx
op_ne
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mcapndx
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;woah!  Non-AGP device &quot;
l_string|&quot;found on the secondary bus of an AGP 3.5 bridge!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|free_and_exit
suffix:semicolon
)brace
id|mmajor
op_assign
(paren
id|ncapid
op_rshift
id|AGP_MAJOR_VERSION_SHIFT
)paren
op_amp
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|mmajor
OL
l_int|3
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;woah!  AGP 2.0 device &quot;
l_string|&quot;found on the secondary bus of an AGP 3.5 &quot;
l_string|&quot;bridge operating with AGP 3.0 electricals!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|free_and_exit
suffix:semicolon
)brace
id|cur-&gt;capndx
op_assign
id|mcapndx
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|cur-&gt;capndx
op_plus
id|AGPSTAT
comma
op_amp
id|mstatus
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|mstatus
op_rshift
l_int|3
)paren
op_amp
l_int|0x1
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;woah!  AGP 3.x device &quot;
l_string|&quot;not operating in AGP 3.x mode found on the &quot;
l_string|&quot;secondary bus of an AGP 3.5 bridge operating &quot;
l_string|&quot;with AGP 3.0 electricals!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|free_and_exit
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Call functions to divide target resources amongst the AGP 3.0&n;&t; * masters.  This process is dramatically different depending on&n;&t; * whether isochronous transfers are supported.&n;&t; */
r_if
c_cond
(paren
id|isoch
)paren
(brace
id|ret
op_assign
id|agp_3_5_isochronous_node_enable
c_func
(paren
id|bridge
comma
id|dev_list
comma
id|ndevs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Something bad happened setting &quot;
l_string|&quot;up isochronous xfers.  Falling back to &quot;
l_string|&quot;non-isochronous xfer mode.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|agp_3_5_nonisochronous_node_enable
c_func
(paren
id|bridge
comma
id|dev_list
comma
id|ndevs
)paren
suffix:semicolon
id|free_and_exit
suffix:colon
multiline_comment|/* Be sure to free the dev_list */
r_for
c_loop
(paren
id|pos
op_assign
id|head-&gt;next
suffix:semicolon
id|pos
op_ne
id|head
suffix:semicolon
)paren
(brace
id|cur
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|agp_3_5_dev
comma
id|list
)paren
suffix:semicolon
id|pos
op_assign
id|pos-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|cur
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|dev_list
)paren
suffix:semicolon
id|get_out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
eof
