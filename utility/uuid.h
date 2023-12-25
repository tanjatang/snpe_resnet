

#ifndef _UL_LIBUUID_UUID_H
#define _UL_LIBUUID_UUID_H

#include <sys/types.h>
#ifndef _WIN32
#include <sys/time.h>
#endif
#include <time.h>

typedef unsigned char uuid_t[16];

/* UUID Variant definitions */
#define UUID_VARIANT_NCS	0
#define UUID_VARIANT_DCE	1
#define UUID_VARIANT_MICROSOFT	2
#define UUID_VARIANT_OTHER	3

#define UUID_VARIANT_SHIFT	5
#define UUID_VARIANT_MASK     0x7

/* UUID Type definitions */
#define UUID_TYPE_DCE_NIL    0
#define UUID_TYPE_DCE_TIME   1
#define UUID_TYPE_DCE_SECURITY 2
#define UUID_TYPE_DCE_MD5    3
#define UUID_TYPE_DCE_RANDOM 4
#define UUID_TYPE_DCE_SHA1   5

#define UUID_TYPE_SHIFT      4
#define UUID_TYPE_MASK     0xf

#define UUID_STR_LEN	37

/* Allow UUID constants to be defined */
#ifdef __GNUC__
#define UUID_DEFINE(name,u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15) \
	static const uuid_t name __attribute__ ((unused)) = {u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15}
#else
#define UUID_DEFINE(name,u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15) \
	static const uuid_t name = {u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* clear.c */
extern void uuid_clear(uuid_t uu);

/* compare.c */
extern int uuid_compare(const uuid_t uu1, const uuid_t uu2);

/* copy.c */
extern void uuid_copy(uuid_t dst, const uuid_t src);

/* gen_uuid.c */
extern void uuid_generate(uuid_t out);
extern void uuid_generate_random(uuid_t out);
extern void uuid_generate_time(uuid_t out);
extern int uuid_generate_time_safe(uuid_t out);

extern void uuid_generate_md5(uuid_t out, const uuid_t ns, const char *name, size_t len);
extern void uuid_generate_sha1(uuid_t out, const uuid_t ns, const char *name, size_t len);

/* isnull.c */
extern int uuid_is_null(const uuid_t uu);

/* parse.c */
extern int uuid_parse(const char *in, uuid_t uu);
extern int uuid_parse_range(const char *in_start, const char *in_end, uuid_t uu);

/* unparse.c */
extern void uuid_unparse(const uuid_t uu, char *out);
extern void uuid_unparse_lower(const uuid_t uu, char *out);
extern void uuid_unparse_upper(const uuid_t uu, char *out);

/* uuid_time.c */
extern time_t uuid_time(const uuid_t uu, struct timeval *ret_tv);
extern int uuid_type(const uuid_t uu);
extern int uuid_variant(const uuid_t uu);

/* predefined.c */
extern const uuid_t *uuid_get_template(const char *alias);

#ifdef __cplusplus
}
#endif

#endif /* _UL_LIBUUID_UUID_H */
