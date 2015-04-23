
#ifndef HAL_EXPORT_H
#define HAL_EXPORT_H

#ifdef HAL_STATIC_DEFINE
#  define HAL_EXPORT
#  define HAL_NO_EXPORT
#else
#  ifndef HAL_EXPORT
#    ifdef HAL_EXPORTS
        /* We are building this library */
#      define HAL_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define HAL_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef HAL_NO_EXPORT
#    define HAL_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef HAL_DEPRECATED
#  define HAL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef HAL_DEPRECATED_EXPORT
#  define HAL_DEPRECATED_EXPORT HAL_EXPORT HAL_DEPRECATED
#endif

#ifndef HAL_DEPRECATED_NO_EXPORT
#  define HAL_DEPRECATED_NO_EXPORT HAL_NO_EXPORT HAL_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define HAL_NO_DEPRECATED
#endif

#endif
