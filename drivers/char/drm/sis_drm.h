macro_line|#ifndef __SIS_DRM_H__
DECL|macro|__SIS_DRM_H__
mdefine_line|#define __SIS_DRM_H__
multiline_comment|/* SiS specific ioctls */
DECL|macro|DRM_IOCTL_SIS_FB_ALLOC
mdefine_line|#define DRM_IOCTL_SIS_FB_ALLOC&t;&t;DRM_IOWR(0x44, drm_sis_mem_t)
DECL|macro|DRM_IOCTL_SIS_FB_FREE
mdefine_line|#define DRM_IOCTL_SIS_FB_FREE&t;&t;DRM_IOW( 0x45, drm_sis_mem_t)
DECL|macro|DRM_IOCTL_SIS_AGP_INIT
mdefine_line|#define DRM_IOCTL_SIS_AGP_INIT&t;&t;DRM_IOWR(0x53, drm_sis_agp_t)
DECL|macro|DRM_IOCTL_SIS_AGP_ALLOC
mdefine_line|#define DRM_IOCTL_SIS_AGP_ALLOC&t;&t;DRM_IOWR(0x54, drm_sis_mem_t)
DECL|macro|DRM_IOCTL_SIS_AGP_FREE
mdefine_line|#define DRM_IOCTL_SIS_AGP_FREE&t;&t;DRM_IOW( 0x55, drm_sis_mem_t)
DECL|macro|DRM_IOCTL_SIS_FB_INIT
mdefine_line|#define DRM_IOCTL_SIS_FB_INIT&t;&t;DRM_IOW( 0x56, drm_sis_fb_t)
multiline_comment|/*&n;#define DRM_IOCTL_SIS_FLIP&t;&t;DRM_IOW( 0x48, drm_sis_flip_t)&n;#define DRM_IOCTL_SIS_FLIP_INIT&t;&t;DRM_IO(  0x49)&n;#define DRM_IOCTL_SIS_FLIP_FINAL&t;DRM_IO(  0x50)&n;*/
r_typedef
r_struct
(brace
DECL|member|context
r_int
id|context
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|free
r_int
r_int
id|free
suffix:semicolon
DECL|typedef|drm_sis_mem_t
)brace
id|drm_sis_mem_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|offset
DECL|member|size
r_int
r_int
id|offset
comma
id|size
suffix:semicolon
DECL|typedef|drm_sis_agp_t
)brace
id|drm_sis_agp_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|offset
DECL|member|size
r_int
r_int
id|offset
comma
id|size
suffix:semicolon
DECL|typedef|drm_sis_fb_t
)brace
id|drm_sis_fb_t
suffix:semicolon
macro_line|#endif /* __SIS_DRM_H__ */
eof
