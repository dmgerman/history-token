multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/dma.h&n; *&n; * by Alexander Schulz &lt;aschulz@netwinder.org&gt;&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/* Use only the lowest 4MB, nothing else works.&n; * The rest is not DMAable. See dev /  .properties&n; * in OpenFirmware.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xC0400000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;8
DECL|macro|DMA_ISA_CASCADE
mdefine_line|#define DMA_ISA_CASCADE         4
DECL|function|__arch_adjust_zones
r_static
r_inline
r_void
id|__arch_adjust_zones
c_func
(paren
r_int
id|node
comma
r_int
r_int
op_star
id|zone_size
comma
r_int
r_int
op_star
id|zhole_size
)paren
(brace
r_if
c_cond
(paren
id|node
op_ne
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* Only the first 4 MB (=1024 Pages) are usable for DMA */
id|zone_size
(braket
l_int|1
)braket
op_assign
id|zone_size
(braket
l_int|0
)braket
op_minus
l_int|1024
suffix:semicolon
id|zone_size
(braket
l_int|0
)braket
op_assign
l_int|1024
suffix:semicolon
id|zhole_size
(braket
l_int|1
)braket
op_assign
id|zhole_size
(braket
l_int|0
)braket
suffix:semicolon
id|zhole_size
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|arch_adjust_zones
mdefine_line|#define arch_adjust_zones(node,size,holes) __arch_adjust_zones(node,size,holes)
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
