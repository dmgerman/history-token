multiline_comment|/* $Id: platform.h,v 1.37.4.6 2005/01/31 12:22:20 armin Exp $&n; *&n; * platform.h&n; * &n; *&n; * Copyright 2000-2003  by Armin Schindler (mac@melware.de)&n; * Copyright 2000  Eicon Networks &n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef&t;__PLATFORM_H__
DECL|macro|__PLATFORM_H__
mdefine_line|#define&t;__PLATFORM_H__
macro_line|#if !defined(DIVA_BUILD)
DECL|macro|DIVA_BUILD
mdefine_line|#define DIVA_BUILD &quot;local&quot;
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;cardtype.h&quot;
multiline_comment|/* activate debuglib for modules only */
macro_line|#ifndef MODULE
DECL|macro|DIVA_NO_DEBUGLIB
mdefine_line|#define DIVA_NO_DEBUGLIB
macro_line|#endif
DECL|macro|DIVA_INIT_FUNCTION
mdefine_line|#define DIVA_INIT_FUNCTION  __init
DECL|macro|DIVA_EXIT_FUNCTION
mdefine_line|#define DIVA_EXIT_FUNCTION  __exit
DECL|macro|DIVA_USER_MODE_CARD_CONFIG
mdefine_line|#define DIVA_USER_MODE_CARD_CONFIG 1
DECL|macro|USE_EXTENDED_DEBUGS
mdefine_line|#define&t;USE_EXTENDED_DEBUGS 1
DECL|macro|MAX_ADAPTER
mdefine_line|#define MAX_ADAPTER     32
DECL|macro|DIVA_ISTREAM
mdefine_line|#define DIVA_ISTREAM 1
DECL|macro|MEMORY_SPACE_TYPE
mdefine_line|#define MEMORY_SPACE_TYPE  0
DECL|macro|PORT_SPACE_TYPE
mdefine_line|#define PORT_SPACE_TYPE    1
macro_line|#include &lt;linux/string.h&gt;
macro_line|#ifndef&t;byte
DECL|macro|byte
mdefine_line|#define&t;byte   u8
macro_line|#endif
macro_line|#ifndef&t;word
DECL|macro|word
mdefine_line|#define&t;word   u16
macro_line|#endif
macro_line|#ifndef&t;dword
DECL|macro|dword
mdefine_line|#define&t;dword  u32
macro_line|#endif
macro_line|#ifndef&t;qword
DECL|macro|qword
mdefine_line|#define&t;qword  u64
macro_line|#endif
macro_line|#ifndef&t;TRUE
DECL|macro|TRUE
mdefine_line|#define&t;TRUE&t;1
macro_line|#endif
macro_line|#ifndef&t;FALSE
DECL|macro|FALSE
mdefine_line|#define&t;FALSE&t;0
macro_line|#endif
macro_line|#ifndef&t;NULL
DECL|macro|NULL
mdefine_line|#define&t;NULL&t;((void *) 0)
macro_line|#endif
macro_line|#ifndef&t;MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;((a)&gt;(b) ? (b) : (a))
macro_line|#endif
macro_line|#ifndef&t;MAX
DECL|macro|MAX
mdefine_line|#define MAX(a,b)&t;((a)&gt;(b) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef&t;far
DECL|macro|far
mdefine_line|#define far
macro_line|#endif
macro_line|#ifndef&t;_pascal
DECL|macro|_pascal
mdefine_line|#define _pascal
macro_line|#endif
macro_line|#ifndef&t;_loadds
DECL|macro|_loadds
mdefine_line|#define _loadds
macro_line|#endif
macro_line|#ifndef&t;_cdecl
DECL|macro|_cdecl
mdefine_line|#define _cdecl
macro_line|#endif
DECL|macro|MEM_TYPE_RAM
mdefine_line|#define MEM_TYPE_RAM&t;&t;0
DECL|macro|MEM_TYPE_PORT
mdefine_line|#define MEM_TYPE_PORT&t;&t;1
DECL|macro|MEM_TYPE_PROM
mdefine_line|#define MEM_TYPE_PROM&t;&t;2
DECL|macro|MEM_TYPE_CTLREG
mdefine_line|#define MEM_TYPE_CTLREG&t;&t;3
DECL|macro|MEM_TYPE_RESET
mdefine_line|#define MEM_TYPE_RESET&t;&t;4
DECL|macro|MEM_TYPE_CFG
mdefine_line|#define MEM_TYPE_CFG&t;&t;5
DECL|macro|MEM_TYPE_ADDRESS
mdefine_line|#define MEM_TYPE_ADDRESS&t;6
DECL|macro|MEM_TYPE_CONFIG
mdefine_line|#define MEM_TYPE_CONFIG&t;&t;7
DECL|macro|MEM_TYPE_CONTROL
mdefine_line|#define MEM_TYPE_CONTROL&t;8
DECL|macro|MAX_MEM_TYPE
mdefine_line|#define MAX_MEM_TYPE&t;&t;10
DECL|macro|DIVA_OS_MEM_ATTACH_RAM
mdefine_line|#define DIVA_OS_MEM_ATTACH_RAM(a)&t;((a)-&gt;ram)
DECL|macro|DIVA_OS_MEM_ATTACH_PORT
mdefine_line|#define DIVA_OS_MEM_ATTACH_PORT(a)&t;((a)-&gt;port)
DECL|macro|DIVA_OS_MEM_ATTACH_PROM
mdefine_line|#define DIVA_OS_MEM_ATTACH_PROM(a)&t;((a)-&gt;prom)
DECL|macro|DIVA_OS_MEM_ATTACH_CTLREG
mdefine_line|#define DIVA_OS_MEM_ATTACH_CTLREG(a)&t;((a)-&gt;ctlReg)
DECL|macro|DIVA_OS_MEM_ATTACH_RESET
mdefine_line|#define DIVA_OS_MEM_ATTACH_RESET(a)&t;((a)-&gt;reset)
DECL|macro|DIVA_OS_MEM_ATTACH_CFG
mdefine_line|#define DIVA_OS_MEM_ATTACH_CFG(a)&t;((a)-&gt;cfg)
DECL|macro|DIVA_OS_MEM_ATTACH_ADDRESS
mdefine_line|#define DIVA_OS_MEM_ATTACH_ADDRESS(a)&t;((a)-&gt;Address)
DECL|macro|DIVA_OS_MEM_ATTACH_CONFIG
mdefine_line|#define DIVA_OS_MEM_ATTACH_CONFIG(a)&t;((a)-&gt;Config)
DECL|macro|DIVA_OS_MEM_ATTACH_CONTROL
mdefine_line|#define DIVA_OS_MEM_ATTACH_CONTROL(a)&t;((a)-&gt;Control)
DECL|macro|DIVA_OS_MEM_DETACH_RAM
mdefine_line|#define DIVA_OS_MEM_DETACH_RAM(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_PORT
mdefine_line|#define DIVA_OS_MEM_DETACH_PORT(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_PROM
mdefine_line|#define DIVA_OS_MEM_DETACH_PROM(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_CTLREG
mdefine_line|#define DIVA_OS_MEM_DETACH_CTLREG(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_RESET
mdefine_line|#define DIVA_OS_MEM_DETACH_RESET(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_CFG
mdefine_line|#define DIVA_OS_MEM_DETACH_CFG(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_ADDRESS
mdefine_line|#define DIVA_OS_MEM_DETACH_ADDRESS(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_CONFIG
mdefine_line|#define DIVA_OS_MEM_DETACH_CONFIG(a, x)&t;do { } while(0)
DECL|macro|DIVA_OS_MEM_DETACH_CONTROL
mdefine_line|#define DIVA_OS_MEM_DETACH_CONTROL(a, x)&t;do { } while(0)
macro_line|#if !defined(DIM)
DECL|macro|DIM
mdefine_line|#define DIM(array)  (sizeof (array)/sizeof ((array)[0]))
macro_line|#endif
DECL|macro|DIVA_INVALID_FILE_HANDLE
mdefine_line|#define DIVA_INVALID_FILE_HANDLE  ((dword)(-1))
DECL|macro|DIVAS_CONTAINING_RECORD
mdefine_line|#define DIVAS_CONTAINING_RECORD(address, type, field) &bslash;&n;        ((type *)((char*)(address) - (char*)(&amp;((type *)0)-&gt;field)))
r_extern
r_int
id|sprintf
c_func
(paren
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|typedef|LIST_ENTRY
r_typedef
r_void
op_star
id|LIST_ENTRY
suffix:semicolon
DECL|typedef|DEVICE_NAME
r_typedef
r_char
id|DEVICE_NAME
(braket
l_int|64
)braket
suffix:semicolon
DECL|typedef|ISDN_ADAPTER
r_typedef
r_struct
id|_ISDN_ADAPTER
id|ISDN_ADAPTER
suffix:semicolon
DECL|typedef|PISDN_ADAPTER
r_typedef
r_struct
id|_ISDN_ADAPTER
op_star
id|PISDN_ADAPTER
suffix:semicolon
DECL|typedef|DIVA_DI_PRINTF
r_typedef
r_void
(paren
op_star
id|DIVA_DI_PRINTF
)paren
(paren
r_int
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#include &quot;debuglib.h&quot;
DECL|macro|dtrc
mdefine_line|#define dtrc(p) DBG_PRV0(p)
DECL|macro|dbug
mdefine_line|#define dbug(a,p) DBG_PRV1(p)
DECL|typedef|E_INFO
r_typedef
r_struct
id|e_info_s
id|E_INFO
suffix:semicolon
DECL|typedef|diva_os_dependent_devica_name_t
r_typedef
r_char
id|diva_os_dependent_devica_name_t
(braket
l_int|64
)braket
suffix:semicolon
DECL|typedef|PDEVICE_OBJECT
r_typedef
r_void
op_star
id|PDEVICE_OBJECT
suffix:semicolon
r_struct
id|_diva_os_soft_isr
suffix:semicolon
r_struct
id|_diva_os_timer
suffix:semicolon
r_struct
id|_ISDN_ADAPTER
suffix:semicolon
r_void
id|diva_log_info
c_func
(paren
r_int
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/*&n;**  XDI DIDD Interface&n;*/
r_void
id|diva_xdi_didd_register_adapter
(paren
r_int
id|card
)paren
suffix:semicolon
r_void
id|diva_xdi_didd_remove_adapter
(paren
r_int
id|card
)paren
suffix:semicolon
multiline_comment|/*&n;** memory allocation&n;*/
DECL|function|diva_os_malloc
r_static
id|__inline__
r_void
op_star
id|diva_os_malloc
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|ret
op_assign
(paren
r_void
op_star
)paren
id|vmalloc
c_func
(paren
(paren
r_int
r_int
)paren
id|size
)paren
suffix:semicolon
)brace
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|diva_os_free
r_static
id|__inline__
r_void
id|diva_os_free
(paren
r_int
r_int
id|flags
comma
r_void
op_star
id|ptr
)paren
(brace
id|vfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;** use skbuffs for message buffer&n;*/
DECL|typedef|diva_os_message_buffer_s
r_typedef
r_struct
id|sk_buff
id|diva_os_message_buffer_s
suffix:semicolon
id|diva_os_message_buffer_s
op_star
id|diva_os_alloc_message_buffer
c_func
(paren
r_int
r_int
id|size
comma
r_void
op_star
op_star
id|data_buf
)paren
suffix:semicolon
r_void
id|diva_os_free_message_buffer
c_func
(paren
id|diva_os_message_buffer_s
op_star
id|dmb
)paren
suffix:semicolon
DECL|macro|DIVA_MESSAGE_BUFFER_LEN
mdefine_line|#define DIVA_MESSAGE_BUFFER_LEN(x) x-&gt;len
DECL|macro|DIVA_MESSAGE_BUFFER_DATA
mdefine_line|#define DIVA_MESSAGE_BUFFER_DATA(x) x-&gt;data
multiline_comment|/*&n;** mSeconds waiting&n;*/
DECL|function|diva_os_sleep
r_static
id|__inline__
r_void
id|diva_os_sleep
c_func
(paren
id|dword
id|mSec
)paren
(brace
id|msleep
c_func
(paren
id|mSec
)paren
suffix:semicolon
)brace
DECL|function|diva_os_wait
r_static
id|__inline__
r_void
id|diva_os_wait
c_func
(paren
id|dword
id|mSec
)paren
(brace
id|mdelay
c_func
(paren
id|mSec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;**  PCI Configuration space access&n;*/
r_void
id|PCIwrite
(paren
id|byte
id|bus
comma
id|byte
id|func
comma
r_int
id|offset
comma
r_void
op_star
id|data
comma
r_int
id|length
comma
r_void
op_star
id|pci_dev_handle
)paren
suffix:semicolon
r_void
id|PCIread
(paren
id|byte
id|bus
comma
id|byte
id|func
comma
r_int
id|offset
comma
r_void
op_star
id|data
comma
r_int
id|length
comma
r_void
op_star
id|pci_dev_handle
)paren
suffix:semicolon
multiline_comment|/*&n;**  I/O Port utilities&n;*/
r_int
id|diva_os_register_io_port
(paren
r_void
op_star
id|adapter
comma
r_int
r_register
comma
r_int
r_int
id|port
comma
r_int
r_int
id|length
comma
r_const
r_char
op_star
id|name
comma
r_int
id|id
)paren
suffix:semicolon
multiline_comment|/*&n;**  I/O port access abstraction&n;*/
id|byte
id|inpp
(paren
r_void
id|__iomem
op_star
)paren
suffix:semicolon
id|word
id|inppw
(paren
r_void
id|__iomem
op_star
)paren
suffix:semicolon
r_void
id|inppw_buffer
(paren
r_void
id|__iomem
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|outppw
(paren
r_void
id|__iomem
op_star
comma
id|word
)paren
suffix:semicolon
r_void
id|outppw_buffer
(paren
r_void
id|__iomem
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|outpp
(paren
r_void
id|__iomem
op_star
comma
id|word
)paren
suffix:semicolon
multiline_comment|/*&n;**  IRQ &n;*/
DECL|struct|_diva_os_adapter_irq_info
r_typedef
r_struct
id|_diva_os_adapter_irq_info
(brace
DECL|member|irq_nr
id|byte
id|irq_nr
suffix:semicolon
DECL|member|registered
r_int
id|registered
suffix:semicolon
DECL|member|irq_name
r_char
id|irq_name
(braket
l_int|24
)braket
suffix:semicolon
DECL|typedef|diva_os_adapter_irq_info_t
)brace
id|diva_os_adapter_irq_info_t
suffix:semicolon
r_int
id|diva_os_register_irq
(paren
r_void
op_star
id|context
comma
id|byte
id|irq
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|diva_os_remove_irq
(paren
r_void
op_star
id|context
comma
id|byte
id|irq
)paren
suffix:semicolon
DECL|macro|diva_os_in_irq
mdefine_line|#define diva_os_in_irq() in_irq()
multiline_comment|/*&n;**  Spin Lock framework&n;*/
DECL|typedef|diva_os_spin_lock_magic_t
r_typedef
r_int
id|diva_os_spin_lock_magic_t
suffix:semicolon
DECL|typedef|diva_os_spin_lock_t
r_typedef
id|spinlock_t
id|diva_os_spin_lock_t
suffix:semicolon
DECL|function|diva_os_initialize_spin_lock
r_static
id|__inline__
r_int
id|diva_os_initialize_spin_lock
(paren
id|spinlock_t
op_star
id|lock
comma
r_void
op_star
id|unused
)paren
(brace
"&bslash;"
id|spin_lock_init
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diva_os_enter_spin_lock
r_static
id|__inline__
r_void
id|diva_os_enter_spin_lock
(paren
id|diva_os_spin_lock_t
op_star
id|a
comma
"&bslash;"
id|diva_os_spin_lock_magic_t
op_star
id|old_irql
comma
"&bslash;"
r_void
op_star
id|dbg
)paren
(brace
id|spin_lock_bh
c_func
(paren
id|a
)paren
suffix:semicolon
)brace
DECL|function|diva_os_leave_spin_lock
r_static
id|__inline__
r_void
id|diva_os_leave_spin_lock
(paren
id|diva_os_spin_lock_t
op_star
id|a
comma
"&bslash;"
id|diva_os_spin_lock_magic_t
op_star
id|old_irql
comma
"&bslash;"
r_void
op_star
id|dbg
)paren
(brace
id|spin_unlock_bh
c_func
(paren
id|a
)paren
suffix:semicolon
)brace
DECL|macro|diva_os_destroy_spin_lock
mdefine_line|#define diva_os_destroy_spin_lock(a,b) do { } while(0)
multiline_comment|/*&n;**  Deffered processing framework&n;*/
DECL|typedef|diva_os_isr_callback_t
r_typedef
r_int
(paren
op_star
id|diva_os_isr_callback_t
)paren
(paren
r_struct
id|_ISDN_ADAPTER
op_star
)paren
suffix:semicolon
DECL|typedef|diva_os_soft_isr_callback_t
r_typedef
r_void
(paren
op_star
id|diva_os_soft_isr_callback_t
)paren
(paren
r_struct
id|_diva_os_soft_isr
op_star
id|psoft_isr
comma
r_void
op_star
id|context
)paren
suffix:semicolon
DECL|struct|_diva_os_soft_isr
r_typedef
r_struct
id|_diva_os_soft_isr
(brace
DECL|member|object
r_void
op_star
id|object
suffix:semicolon
DECL|member|callback
id|diva_os_soft_isr_callback_t
id|callback
suffix:semicolon
DECL|member|callback_context
r_void
op_star
id|callback_context
suffix:semicolon
DECL|member|dpc_thread_name
r_char
id|dpc_thread_name
(braket
l_int|24
)braket
suffix:semicolon
DECL|typedef|diva_os_soft_isr_t
)brace
id|diva_os_soft_isr_t
suffix:semicolon
r_int
id|diva_os_initialize_soft_isr
(paren
id|diva_os_soft_isr_t
op_star
id|psoft_isr
comma
id|diva_os_soft_isr_callback_t
id|callback
comma
r_void
op_star
id|callback_context
)paren
suffix:semicolon
r_int
id|diva_os_schedule_soft_isr
(paren
id|diva_os_soft_isr_t
op_star
id|psoft_isr
)paren
suffix:semicolon
r_int
id|diva_os_cancel_soft_isr
(paren
id|diva_os_soft_isr_t
op_star
id|psoft_isr
)paren
suffix:semicolon
r_void
id|diva_os_remove_soft_isr
(paren
id|diva_os_soft_isr_t
op_star
id|psoft_isr
)paren
suffix:semicolon
multiline_comment|/*&n;  Get time service&n;  */
r_void
id|diva_os_get_time
(paren
id|dword
op_star
id|sec
comma
id|dword
op_star
id|usec
)paren
suffix:semicolon
multiline_comment|/*&n;**  atomic operation, fake because we use threads&n;*/
DECL|typedef|diva_os_atomic_t
r_typedef
r_int
id|diva_os_atomic_t
suffix:semicolon
r_static
id|diva_os_atomic_t
id|__inline__
DECL|function|diva_os_atomic_increment
id|diva_os_atomic_increment
c_func
(paren
id|diva_os_atomic_t
op_star
id|pv
)paren
(brace
op_star
id|pv
op_add_assign
l_int|1
suffix:semicolon
r_return
(paren
op_star
id|pv
)paren
suffix:semicolon
)brace
r_static
id|diva_os_atomic_t
id|__inline__
DECL|function|diva_os_atomic_decrement
id|diva_os_atomic_decrement
c_func
(paren
id|diva_os_atomic_t
op_star
id|pv
)paren
(brace
op_star
id|pv
op_sub_assign
l_int|1
suffix:semicolon
r_return
(paren
op_star
id|pv
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;**  CAPI SECTION&n;*/
DECL|macro|NO_CORNETN
mdefine_line|#define NO_CORNETN
DECL|macro|IMPLEMENT_DTMF
mdefine_line|#define IMPLEMENT_DTMF 1
DECL|macro|IMPLEMENT_ECHO_CANCELLER
mdefine_line|#define IMPLEMENT_ECHO_CANCELLER 1
DECL|macro|IMPLEMENT_RTP
mdefine_line|#define IMPLEMENT_RTP 1
DECL|macro|IMPLEMENT_T38
mdefine_line|#define IMPLEMENT_T38 1
DECL|macro|IMPLEMENT_FAX_SUB_SEP_PWD
mdefine_line|#define IMPLEMENT_FAX_SUB_SEP_PWD 1
DECL|macro|IMPLEMENT_V18
mdefine_line|#define IMPLEMENT_V18 1
DECL|macro|IMPLEMENT_DTMF_TONE
mdefine_line|#define IMPLEMENT_DTMF_TONE 1
DECL|macro|IMPLEMENT_PIAFS
mdefine_line|#define IMPLEMENT_PIAFS 1
DECL|macro|IMPLEMENT_FAX_PAPER_FORMATS
mdefine_line|#define IMPLEMENT_FAX_PAPER_FORMATS 1
DECL|macro|IMPLEMENT_VOWN
mdefine_line|#define IMPLEMENT_VOWN 1
DECL|macro|IMPLEMENT_CAPIDTMF
mdefine_line|#define IMPLEMENT_CAPIDTMF 1
DECL|macro|IMPLEMENT_FAX_NONSTANDARD
mdefine_line|#define IMPLEMENT_FAX_NONSTANDARD 1
DECL|macro|VSWITCH_SUPPORT
mdefine_line|#define VSWITCH_SUPPORT 1
DECL|macro|IMPLEMENT_MARKED_OK_AFTER_FC
mdefine_line|#define IMPLEMENT_MARKED_OK_AFTER_FC 1
DECL|macro|DIVA_IDI_RX_DMA
mdefine_line|#define DIVA_IDI_RX_DMA 1
multiline_comment|/*&n;** endian macros&n;**&n;** If only...  In some cases we did use them for endianness conversion;&n;** unfortunately, other uses were real iomem accesses.&n;*/
DECL|macro|READ_BYTE
mdefine_line|#define READ_BYTE(addr)   readb(addr)
DECL|macro|READ_WORD
mdefine_line|#define READ_WORD(addr)   readw(addr)
DECL|macro|READ_DWORD
mdefine_line|#define READ_DWORD(addr)  readl(addr)
DECL|macro|WRITE_BYTE
mdefine_line|#define WRITE_BYTE(addr,v)  writeb(v,addr)
DECL|macro|WRITE_WORD
mdefine_line|#define WRITE_WORD(addr,v)  writew(v,addr)
DECL|macro|WRITE_DWORD
mdefine_line|#define WRITE_DWORD(addr,v) writel(v,addr)
DECL|function|GET_WORD
r_static
r_inline
id|__u16
id|GET_WORD
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|le16_to_cpu
c_func
(paren
op_star
(paren
id|__le16
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|GET_DWORD
r_static
r_inline
id|__u32
id|GET_DWORD
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|le32_to_cpu
c_func
(paren
op_star
(paren
id|__le32
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|PUT_WORD
r_static
r_inline
r_void
id|PUT_WORD
c_func
(paren
r_void
op_star
id|addr
comma
id|__u16
id|v
)paren
(brace
op_star
(paren
id|__le16
op_star
)paren
id|addr
op_assign
id|cpu_to_le16
c_func
(paren
id|v
)paren
suffix:semicolon
)brace
DECL|function|PUT_DWORD
r_static
r_inline
r_void
id|PUT_DWORD
c_func
(paren
r_void
op_star
id|addr
comma
id|__u32
id|v
)paren
(brace
op_star
(paren
id|__le32
op_star
)paren
id|addr
op_assign
id|cpu_to_le32
c_func
(paren
id|v
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;** 32/64 bit macors&n;*/
macro_line|#ifdef BITS_PER_LONG
macro_line|#if BITS_PER_LONG &gt; 32 
DECL|macro|PLATFORM_GT_32BIT
mdefine_line|#define PLATFORM_GT_32BIT
DECL|macro|ULongToPtr
mdefine_line|#define ULongToPtr(x) (void *)(unsigned long)(x)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;** undef os definitions of macros we use&n;*/
DECL|macro|ID_MASK
macro_line|#undef ID_MASK
DECL|macro|N_DATA
macro_line|#undef N_DATA
DECL|macro|ADDR
macro_line|#undef ADDR
multiline_comment|/*&n;** dump file&n;*/
DECL|macro|diva_os_dump_file_t
mdefine_line|#define diva_os_dump_file_t char
DECL|macro|diva_os_board_trace_t
mdefine_line|#define diva_os_board_trace_t char
DECL|macro|diva_os_dump_file
mdefine_line|#define diva_os_dump_file(__x__) do { } while(0)
multiline_comment|/*&n;** size of internal arrays&n;*/
DECL|macro|MAX_DESCRIPTORS
mdefine_line|#define MAX_DESCRIPTORS 64
macro_line|#endif&t;/* __PLATFORM_H__ */
eof
