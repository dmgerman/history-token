multiline_comment|/*&n; * ioport.h&t;Definitions of routines for detecting, reserving and&n; *&t;&t;allocating system resources.&n; *&n; * Authors:&t;Linus Torvalds&n; */
macro_line|#ifndef _LINUX_IOPORT_H
DECL|macro|_LINUX_IOPORT_H
mdefine_line|#define _LINUX_IOPORT_H
multiline_comment|/*&n; * Resources are tree-like, allowing&n; * nesting etc..&n; */
DECL|struct|resource
r_struct
id|resource
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|start
DECL|member|end
r_int
r_int
id|start
comma
id|end
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|parent
DECL|member|sibling
DECL|member|child
r_struct
id|resource
op_star
id|parent
comma
op_star
id|sibling
comma
op_star
id|child
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|resource_list
r_struct
id|resource_list
(brace
DECL|member|next
r_struct
id|resource_list
op_star
id|next
suffix:semicolon
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IO resources have these defined flags.&n; */
DECL|macro|IORESOURCE_BITS
mdefine_line|#define IORESOURCE_BITS&t;&t;0x000000ff&t;/* Bus-specific bits */
DECL|macro|IORESOURCE_IO
mdefine_line|#define IORESOURCE_IO&t;&t;0x00000100&t;/* Resource type */
DECL|macro|IORESOURCE_MEM
mdefine_line|#define IORESOURCE_MEM&t;&t;0x00000200
DECL|macro|IORESOURCE_IRQ
mdefine_line|#define IORESOURCE_IRQ&t;&t;0x00000400
DECL|macro|IORESOURCE_DMA
mdefine_line|#define IORESOURCE_DMA&t;&t;0x00000800
DECL|macro|IORESOURCE_PREFETCH
mdefine_line|#define IORESOURCE_PREFETCH&t;0x00001000&t;/* No side effects */
DECL|macro|IORESOURCE_READONLY
mdefine_line|#define IORESOURCE_READONLY&t;0x00002000
DECL|macro|IORESOURCE_CACHEABLE
mdefine_line|#define IORESOURCE_CACHEABLE&t;0x00004000
DECL|macro|IORESOURCE_RANGELENGTH
mdefine_line|#define IORESOURCE_RANGELENGTH&t;0x00008000
DECL|macro|IORESOURCE_SHADOWABLE
mdefine_line|#define IORESOURCE_SHADOWABLE&t;0x00010000
DECL|macro|IORESOURCE_BUS_HAS_VGA
mdefine_line|#define IORESOURCE_BUS_HAS_VGA&t;0x00080000
DECL|macro|IORESOURCE_UNSET
mdefine_line|#define IORESOURCE_UNSET&t;0x20000000
DECL|macro|IORESOURCE_AUTO
mdefine_line|#define IORESOURCE_AUTO&t;&t;0x40000000
DECL|macro|IORESOURCE_BUSY
mdefine_line|#define IORESOURCE_BUSY&t;&t;0x80000000&t;/* Driver has marked this resource busy */
multiline_comment|/* ISA PnP IRQ specific bits (IORESOURCE_BITS) */
DECL|macro|IORESOURCE_IRQ_HIGHEDGE
mdefine_line|#define IORESOURCE_IRQ_HIGHEDGE&t;&t;(1&lt;&lt;0)
DECL|macro|IORESOURCE_IRQ_LOWEDGE
mdefine_line|#define IORESOURCE_IRQ_LOWEDGE&t;&t;(1&lt;&lt;1)
DECL|macro|IORESOURCE_IRQ_HIGHLEVEL
mdefine_line|#define IORESOURCE_IRQ_HIGHLEVEL&t;(1&lt;&lt;2)
DECL|macro|IORESOURCE_IRQ_LOWLEVEL
mdefine_line|#define IORESOURCE_IRQ_LOWLEVEL&t;&t;(1&lt;&lt;3)
multiline_comment|/* ISA PnP DMA specific bits (IORESOURCE_BITS) */
DECL|macro|IORESOURCE_DMA_TYPE_MASK
mdefine_line|#define IORESOURCE_DMA_TYPE_MASK&t;(3&lt;&lt;0)
DECL|macro|IORESOURCE_DMA_8BIT
mdefine_line|#define IORESOURCE_DMA_8BIT&t;&t;(0&lt;&lt;0)
DECL|macro|IORESOURCE_DMA_8AND16BIT
mdefine_line|#define IORESOURCE_DMA_8AND16BIT&t;(1&lt;&lt;0)
DECL|macro|IORESOURCE_DMA_16BIT
mdefine_line|#define IORESOURCE_DMA_16BIT&t;&t;(2&lt;&lt;0)
DECL|macro|IORESOURCE_DMA_MASTER
mdefine_line|#define IORESOURCE_DMA_MASTER&t;&t;(1&lt;&lt;2)
DECL|macro|IORESOURCE_DMA_BYTE
mdefine_line|#define IORESOURCE_DMA_BYTE&t;&t;(1&lt;&lt;3)
DECL|macro|IORESOURCE_DMA_WORD
mdefine_line|#define IORESOURCE_DMA_WORD&t;&t;(1&lt;&lt;4)
DECL|macro|IORESOURCE_DMA_SPEED_MASK
mdefine_line|#define IORESOURCE_DMA_SPEED_MASK&t;(3&lt;&lt;6)
DECL|macro|IORESOURCE_DMA_COMPATIBLE
mdefine_line|#define IORESOURCE_DMA_COMPATIBLE&t;(0&lt;&lt;6)
DECL|macro|IORESOURCE_DMA_TYPEA
mdefine_line|#define IORESOURCE_DMA_TYPEA&t;&t;(1&lt;&lt;6)
DECL|macro|IORESOURCE_DMA_TYPEB
mdefine_line|#define IORESOURCE_DMA_TYPEB&t;&t;(2&lt;&lt;6)
DECL|macro|IORESOURCE_DMA_TYPEF
mdefine_line|#define IORESOURCE_DMA_TYPEF&t;&t;(3&lt;&lt;6)
multiline_comment|/* ISA PnP memory I/O specific bits (IORESOURCE_BITS) */
DECL|macro|IORESOURCE_MEM_WRITEABLE
mdefine_line|#define IORESOURCE_MEM_WRITEABLE&t;(1&lt;&lt;0)&t;/* dup: IORESOURCE_READONLY */
DECL|macro|IORESOURCE_MEM_CACHEABLE
mdefine_line|#define IORESOURCE_MEM_CACHEABLE&t;(1&lt;&lt;1)&t;/* dup: IORESOURCE_CACHEABLE */
DECL|macro|IORESOURCE_MEM_RANGELENGTH
mdefine_line|#define IORESOURCE_MEM_RANGELENGTH&t;(1&lt;&lt;2)&t;/* dup: IORESOURCE_RANGELENGTH */
DECL|macro|IORESOURCE_MEM_TYPE_MASK
mdefine_line|#define IORESOURCE_MEM_TYPE_MASK&t;(3&lt;&lt;3)
DECL|macro|IORESOURCE_MEM_8BIT
mdefine_line|#define IORESOURCE_MEM_8BIT&t;&t;(0&lt;&lt;3)
DECL|macro|IORESOURCE_MEM_16BIT
mdefine_line|#define IORESOURCE_MEM_16BIT&t;&t;(1&lt;&lt;3)
DECL|macro|IORESOURCE_MEM_8AND16BIT
mdefine_line|#define IORESOURCE_MEM_8AND16BIT&t;(2&lt;&lt;3)
DECL|macro|IORESOURCE_MEM_SHADOWABLE
mdefine_line|#define IORESOURCE_MEM_SHADOWABLE&t;(1&lt;&lt;5)&t;/* dup: IORESOURCE_SHADOWABLE */
DECL|macro|IORESOURCE_MEM_EXPANSIONROM
mdefine_line|#define IORESOURCE_MEM_EXPANSIONROM&t;(1&lt;&lt;6)
multiline_comment|/* PC/ISA/whatever - the normal PC address spaces: IO and memory */
r_extern
r_struct
id|resource
id|ioport_resource
suffix:semicolon
r_extern
r_struct
id|resource
id|iomem_resource
suffix:semicolon
r_extern
r_int
id|get_resource_list
c_func
(paren
r_struct
id|resource
op_star
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|check_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|request_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
)paren
suffix:semicolon
r_extern
r_int
id|release_resource
c_func
(paren
r_struct
id|resource
op_star
r_new
)paren
suffix:semicolon
r_extern
r_int
id|allocate_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
comma
r_int
r_int
id|size
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
comma
r_int
r_int
id|align
comma
r_void
(paren
op_star
id|alignf
)paren
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
suffix:semicolon
multiline_comment|/* Convenience shorthand with allocation */
DECL|macro|request_region
mdefine_line|#define request_region(start,n,name)&t;__request_region(&amp;ioport_resource, (start), (n), (name))
DECL|macro|request_mem_region
mdefine_line|#define request_mem_region(start,n,name) __request_region(&amp;iomem_resource, (start), (n), (name))
r_extern
r_struct
id|resource
op_star
id|__request_region
c_func
(paren
r_struct
id|resource
op_star
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Compatibility cruft */
DECL|macro|check_region
mdefine_line|#define check_region(start,n)&t;__check_region(&amp;ioport_resource, (start), (n))
DECL|macro|release_region
mdefine_line|#define release_region(start,n)&t;__release_region(&amp;ioport_resource, (start), (n))
DECL|macro|check_mem_region
mdefine_line|#define check_mem_region(start,n)&t;__check_region(&amp;iomem_resource, (start), (n))
DECL|macro|release_mem_region
mdefine_line|#define release_mem_region(start,n)&t;__release_region(&amp;iomem_resource, (start), (n))
r_extern
r_int
id|__check_region
c_func
(paren
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__release_region
c_func
(paren
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|get_ioport_list
mdefine_line|#define get_ioport_list(buf)&t;get_resource_list(&amp;ioport_resource, buf, PAGE_SIZE)
DECL|macro|get_mem_list
mdefine_line|#define get_mem_list(buf)&t;get_resource_list(&amp;iomem_resource, buf, PAGE_SIZE)
macro_line|#endif&t;/* _LINUX_IOPORT_H */
eof
