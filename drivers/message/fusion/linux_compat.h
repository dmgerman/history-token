multiline_comment|/* drivers/message/fusion/linux_compat.h */
macro_line|#ifndef FUSION_LINUX_COMPAT_H
DECL|macro|FUSION_LINUX_COMPAT_H
mdefine_line|#define FUSION_LINUX_COMPAT_H
multiline_comment|/*{-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
macro_line|#&t;if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,2,18)
DECL|typedef|dma_addr_t
r_typedef
r_int
r_int
id|dma_addr_t
suffix:semicolon
macro_line|#&t;endif
macro_line|#else
macro_line|#&t;if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,42)
DECL|typedef|dma_addr_t
r_typedef
r_int
r_int
id|dma_addr_t
suffix:semicolon
macro_line|#&t;endif
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,2,18)
multiline_comment|/*{-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/* This block snipped from lk-2.2.18/include/linux/init.h { */
multiline_comment|/*&n; * Used for initialization calls..&n; */
DECL|typedef|initcall_t
r_typedef
r_int
(paren
op_star
id|initcall_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|exitcall_t
r_typedef
r_void
(paren
op_star
id|exitcall_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__init_call
mdefine_line|#define __init_call&t;__attribute__ ((unused,__section__ (&quot;.initcall.init&quot;)))
DECL|macro|__exit_call
mdefine_line|#define __exit_call&t;__attribute__ ((unused,__section__ (&quot;.exitcall.exit&quot;)))
r_extern
id|initcall_t
id|__initcall_start
comma
id|__initcall_end
suffix:semicolon
DECL|macro|__initcall
mdefine_line|#define __initcall(fn)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static initcall_t __initcall_##fn __init_call = fn
DECL|macro|__exitcall
mdefine_line|#define __exitcall(fn)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static exitcall_t __exitcall_##fn __exit_call = fn
macro_line|#ifdef MODULE
multiline_comment|/* These macros create a dummy inline: gcc 2.9x does not count alias&n; as usage, hence the `unused function&squot; warning when __init functions&n; are declared static. We use the dummy __*_module_inline functions&n; both to kill the warning and check the type of the init/cleanup&n; function. */
DECL|typedef|__init_module_func_t
r_typedef
r_int
(paren
op_star
id|__init_module_func_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|__cleanup_module_func_t
r_typedef
r_void
(paren
op_star
id|__cleanup_module_func_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|macro|module_init
mdefine_line|#define module_init(x) &bslash;&n;&t;int init_module(void) __attribute__((alias(#x))); &bslash;&n;&t;extern inline __init_module_func_t __init_module_inline(void) &bslash;&n;&t;{ return x; }
DECL|macro|module_exit
mdefine_line|#define module_exit(x) &bslash;&n;&t;void cleanup_module(void) __attribute__((alias(#x))); &bslash;&n;&t;extern inline __cleanup_module_func_t __cleanup_module_inline(void) &bslash;&n;&t;{ return x; }
macro_line|#else 
DECL|macro|module_init
mdefine_line|#define module_init(x)&t;__initcall(x);
DECL|macro|module_exit
mdefine_line|#define module_exit(x)&t;__exitcall(x);
macro_line|#endif
multiline_comment|/* } block snipped from lk-2.2.18/include/linux/init.h */
multiline_comment|/* Wait queues. */
DECL|macro|DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define DECLARE_WAIT_QUEUE_HEAD(name)&t;&bslash;&n;&t;struct wait_queue * (name) = NULL
DECL|macro|DECLARE_WAITQUEUE
mdefine_line|#define DECLARE_WAITQUEUE(name, task)&t;&bslash;&n;&t;struct wait_queue (name) = { (task), NULL }
macro_line|#if defined(__sparc__) &amp;&amp; defined(__sparc_v9__)
multiline_comment|/* The sparc64 ioremap implementation is wrong in 2.2.x,&n; * but fixing it would break all of the drivers which&n; * workaround it.  Fixed in 2.3.x onward. -DaveM&n; */
DECL|macro|ARCH_IOREMAP
mdefine_line|#define ARCH_IOREMAP(base)&t;((unsigned long) (base))
macro_line|#else
DECL|macro|ARCH_IOREMAP
mdefine_line|#define ARCH_IOREMAP(base)&t;ioremap(base)
macro_line|#endif
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#else&t;&t;/* LINUX_VERSION_CODE must be &gt;= KERNEL_VERSION(2,2,18) */
multiline_comment|/* No ioremap bugs in &gt;2.3.x kernels. */
DECL|macro|ARCH_IOREMAP
mdefine_line|#define ARCH_IOREMAP(base)&t;ioremap(base)
multiline_comment|/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif&t;&t;/* LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,2,18) */
multiline_comment|/* PCI/driver subsystem { */
macro_line|#ifndef pci_for_each_dev
DECL|macro|pci_for_each_dev
mdefine_line|#define pci_for_each_dev(dev)&t;&t;for((dev)=pci_devices; (dev)!=NULL; (dev)=(dev)-&gt;next)
DECL|macro|pci_peek_next_dev
mdefine_line|#define pci_peek_next_dev(dev)&t;&t;((dev)-&gt;next ? (dev)-&gt;next : NULL)
DECL|macro|DEVICE_COUNT_RESOURCE
mdefine_line|#define DEVICE_COUNT_RESOURCE           6
DECL|macro|PCI_BASEADDR_FLAGS
mdefine_line|#define PCI_BASEADDR_FLAGS(idx)         base_address[idx]
DECL|macro|PCI_BASEADDR_START
mdefine_line|#define PCI_BASEADDR_START(idx)         base_address[idx] &amp; ~0xFUL
multiline_comment|/*&n; * We have to keep track of the original value using&n; * a temporary, and not by just sticking pdev-&gt;base_address[x]&n; * back.  pdev-&gt;base_address[x] is an opaque cookie that can&n; * be used by the PCI implementation on a given Linux port&n; * for any purpose. -DaveM&n; */
DECL|macro|PCI_BASEADDR_SIZE
mdefine_line|#define PCI_BASEADDR_SIZE(__pdev, __idx) &bslash;&n;({&t;unsigned int size, tmp; &bslash;&n;&t;pci_read_config_dword(__pdev, PCI_BASE_ADDRESS_0 + (4*(__idx)), &amp;tmp); &bslash;&n;&t;pci_write_config_dword(__pdev, PCI_BASE_ADDRESS_0 + (4*(__idx)), 0xffffffff); &bslash;&n;&t;pci_read_config_dword(__pdev, PCI_BASE_ADDRESS_0 + (4*(__idx)), &amp;size); &bslash;&n;&t;pci_write_config_dword(__pdev, PCI_BASE_ADDRESS_0 + (4*(__idx)), tmp); &bslash;&n;&t;(4 - size); &bslash;&n;})
macro_line|#else
DECL|macro|pci_peek_next_dev
mdefine_line|#define pci_peek_next_dev(dev)&t;&t;((dev) != pci_dev_g(&amp;pci_devices) ? pci_dev_g((dev)-&gt;global_list.next) : NULL)
DECL|macro|PCI_BASEADDR_FLAGS
mdefine_line|#define PCI_BASEADDR_FLAGS(idx)         resource[idx].flags
DECL|macro|PCI_BASEADDR_START
mdefine_line|#define PCI_BASEADDR_START(idx)         resource[idx].start
DECL|macro|PCI_BASEADDR_SIZE
mdefine_line|#define PCI_BASEADDR_SIZE(dev,idx)      (dev)-&gt;resource[idx].end - (dev)-&gt;resource[idx].start + 1
macro_line|#endif&t;&t;/* } ifndef pci_for_each_dev */
multiline_comment|/* procfs compat stuff... */
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,28)
DECL|macro|CREATE_PROCDIR_ENTRY
mdefine_line|#define CREATE_PROCDIR_ENTRY(x,y)  create_proc_entry(x, S_IFDIR, y)
multiline_comment|/* This is a macro so we don&squot;t need to pull all the procfs&n; * headers into this file. -DaveM&n; */
DECL|macro|create_proc_read_entry
mdefine_line|#define create_proc_read_entry(name, mode, base, __read_proc, __data) &bslash;&n;({      struct proc_dir_entry *__res=create_proc_entry(name,mode,base); &bslash;&n;        if (__res) { &bslash;&n;                __res-&gt;read_proc=(__read_proc); &bslash;&n;                __res-&gt;data=(__data); &bslash;&n;        } &bslash;&n;        __res; &bslash;&n;})
macro_line|#else
DECL|macro|CREATE_PROCDIR_ENTRY
mdefine_line|#define CREATE_PROCDIR_ENTRY(x,y)  proc_mkdir(x, y)
macro_line|#endif
macro_line|#endif
multiline_comment|/* Compatability for the 2.3.x PCI DMA API. */
macro_line|#ifndef PCI_DMA_BIDIRECTIONAL
multiline_comment|/*{-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
DECL|macro|PCI_DMA_BIDIRECTIONAL
mdefine_line|#define PCI_DMA_BIDIRECTIONAL&t;0
DECL|macro|PCI_DMA_TODEVICE
mdefine_line|#define PCI_DMA_TODEVICE&t;1
DECL|macro|PCI_DMA_FROMDEVICE
mdefine_line|#define PCI_DMA_FROMDEVICE&t;2
DECL|macro|PCI_DMA_NONE
mdefine_line|#define PCI_DMA_NONE&t;&t;3
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|__get_order
r_static
id|__inline__
r_int
id|__get_order
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
id|order
suffix:semicolon
id|size
op_assign
(paren
id|size
op_minus
l_int|1
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|1
)paren
suffix:semicolon
id|order
op_assign
op_minus
l_int|1
suffix:semicolon
r_do
(brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|order
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
r_return
id|order
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|pci_alloc_consistent
mdefine_line|#define pci_alloc_consistent(hwdev, size, dma_handle) &bslash;&n;({&t;void *__ret = (void *)__get_free_pages(GFP_ATOMIC, __get_order(size)); &bslash;&n;&t;if (__ret != NULL) { &bslash;&n;&t;&t;memset(__ret, 0, size); &bslash;&n;&t;&t;*(dma_handle) = virt_to_bus(__ret); &bslash;&n;&t;} &bslash;&n;&t;__ret; &bslash;&n;})
DECL|macro|pci_free_consistent
mdefine_line|#define pci_free_consistent(hwdev, size, vaddr, dma_handle) &bslash;&n;&t;free_pages((unsigned long)vaddr, __get_order(size))
DECL|macro|pci_map_single
mdefine_line|#define pci_map_single(hwdev, ptr, size, direction) &bslash;&n;&t;virt_to_bus(ptr);
DECL|macro|pci_unmap_single
mdefine_line|#define pci_unmap_single(hwdev, dma_addr, size, direction) &bslash;&n;&t;do { /* Nothing to do */ } while (0)
DECL|macro|pci_map_sg
mdefine_line|#define pci_map_sg(hwdev, sg, nents, direction)&t;(nents)
DECL|macro|pci_unmap_sg
mdefine_line|#define pci_unmap_sg(hwdev, sg, nents, direction) &bslash;&n;&t;do { /* Nothing to do */ } while(0)
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)&t;(virt_to_bus((sg)-&gt;address))
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)&t;&t;((sg)-&gt;length)
multiline_comment|/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif /* PCI_DMA_BIDIRECTIONAL */
multiline_comment|/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif /* _LINUX_COMPAT_H */
eof
