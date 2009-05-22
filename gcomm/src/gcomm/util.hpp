#ifndef UTIL_HPP
#define UTIL_HPP

#include <gcomm/common.hpp>
#include <gcomm/string.hpp>
#include <gcomm/exception.hpp>

#include <sstream>
#include <cstring>

using std::ostringstream;

BEGIN_GCOMM_NAMESPACE


static inline size_t read_string(const void* from, const size_t fromlen,
                                 const size_t from_offset, char** to)
{
    if (to == 0)
    {
        throw FatalException("invalid argument");
    }
    /* Scan for termination character */
    size_t i;
    for (i = from_offset; i < fromlen && *((char*)from + i) != '\0'; 
         ++i) { } 
    /* Buffer didn't contain '\0' */
    if (i == fromlen)
        return 0;
    /* Safe to strdup now */
    *to = strdup((char*) from + from_offset);
    return i + 1;
}

static inline size_t read_bytes(const void* from, const size_t fromlen,
                                const size_t from_offset, 
                                void* to, const size_t tolen)
{
    if (fromlen < from_offset + tolen)
        return 0;
    memcpy(to, (const uint8_t *)from + from_offset, tolen);
    return from_offset + tolen;
}

static inline size_t write_string(const char* from, void* to, 
                                  const size_t tolen, const size_t to_offset)
{
    size_t strl = strlen(from);
    if (tolen < strl + 1 + to_offset)
        return 0;
    /* Copy string including '\0' */
    memcpy((uint8_t*)to + to_offset, from, strl + 1);
    return to_offset + strl + 1;
}

static inline size_t write_bytes(const void* from, 
                                 const size_t fromlen,
                                 void* to, 
                                 const size_t tolen, const size_t to_offset)
{
    if (tolen < fromlen + to_offset)
        return 0;
    memcpy((uint8_t*)to + to_offset, from, fromlen);
    return to_offset + fromlen;
}

/**
 * Read boolean value from string. String must contain one of
 * 0, false, 1, true
 *
 * \param s Input string
 * \return Boolean value
 */
bool read_bool(const string& s);

/**
 * Read integer value from string. 
 *
 * \param s Input string
 * \return Integer value
 */
int read_int(const string& s);

/**
 * Read long value from string.
 *
 * \param s Input string
 * \return Long value
 */
long read_long(const string& s);


END_GCOMM_NAMESPACE

#endif // UTIL_HPP