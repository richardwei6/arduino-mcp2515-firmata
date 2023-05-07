/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */

#ifndef BYTE_CACHE_H
#define BYTE_CACHE_H

#include <cerrno>
#include <cstddef>
#include <cstdint>

#include "Stream.h"

namespace serial_wiring {

/*!
 * \brief Interface for accessing character and binary based caches
 */
class ByteCache {
  public:
    /*!
     * \brief Writes a byte to the cache
     *
     * \param [in] byte_ The byte of data to write into the cache
     */
    inline
    void
    cacheByte (
        uint8_t byte_
    ) {
        int error;

        if ( 0 != (error = _cacheByte(byte_)) ) {
            errno = error;
#ifdef LOG_ERRORS
            ::perror("ERROR: ByteCache::cacheByte - Underlying implementation encountered error!");
#endif
        }
    }

    /*!
     * \brief Fetches the next byte from the cache
     *
     * \return The first byte of cached data available
     *
     * \note Returns -1 if there is no byte, although this should
     *       be avoided by first checking `available()` to see if
     *       data is available.
     */
    inline
    int
    readCachedByte (
        void
    ) {
        int result = _readCachedByte();

        if ( result < -1 || result > 255 ) {
            errno = ERANGE;
#ifdef LOG_ERRORS
            ::perror("ERROR: ByteCache::readCachedByte - Underlying implementation result out of range!");
#endif
        }

        return result;
    }

    /*!
     * \brief Register a cached bytes ready callback
     *
     * The supplied callback shall be invoked when bytes are
     * available in the cache
     *
     * \param [in] uponCachedBytes_ Callback invoked when byte(s) are
     *                              available in the cache
     *
     * \param [in] context_ Optional context provided to uponCachedBytes_
     *                      via the `context_` parameter
     */
    inline
    void
    registerCachedBytesCallback (
        serial_event_t uponCachedBytes_,
        void * context_ = nullptr
    ) {
        int error;

        if ( !uponCachedBytes_ ) { context_ = nullptr; }

        if ( 0 != (error = _registerCachedBytesCallback(uponCachedBytes_, context_)) ) {
            errno = error;
#ifdef LOG_ERRORS
            ::perror("ERROR: ByteCache::registerCachedBytesCallback - Underlying implementation encountered error!");
#endif
        }
    }

    /*!
     * \brief Checks the number of bytes available in the cache
     *
     * \return The number of bytes available
     */
    inline
    size_t
    size (
        void
    ) {
        return _size();
    }

  protected:
    ~ByteCache (void) {}

  private:
    virtual
    int
    _cacheByte (
        uint8_t byte_
    ) = 0;

    virtual
    int
    _readCachedByte (
        void
    ) = 0;

    virtual
    int
    _registerCachedBytesCallback (
        serial_event_t uponCachedBytes_,
        void * context_ = nullptr
    ) = 0;

    virtual
    size_t
    _size (
        void
    ) = 0;
};

}  // namespace serial_wiring

#endif // BYTE_CACHE_H

/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */
