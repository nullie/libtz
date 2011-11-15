#if BUILDING_LIBTZ && HAVE_VISIBILITY
#define LIBTZ_DLL_EXPORTED __attribute__((__visibility__("default")))
#else
#define LIBTZ_DLL_EXPORTED
#endif

struct state;

LIBTZ_DLL_EXPORTED const struct state *tz_alloc(register const char * name);
LIBTZ_DLL_EXPORTED void tz_free(const struct state * const sp);

