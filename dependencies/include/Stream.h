/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */

#ifndef STREAM_H
#define STREAM_H

#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace serial_wiring {

/*!
 * \brief Callback supplied to `Stream::registerSerialEventCallback`,
 *        and invoked when data is available.
 *
 * \param [in] context_ Context to use in the callback
 *
 * \note Use `Stream.read()` to capture this data.
 *
 * <a href="https://www.arduino.cc/en/Reference/SerialEvent">serialEvent (Arduino.cc)</a>
 */
typedef void(*serial_event_t)(void * context_);

/*!
 * \brief Stream is the base class for character and binary based streams
 *
 * Stream defines the reading functions in Arduino. It is not called
 * directly, but invoked whenever you use a function that relies on
 * it. When using any core functionality that uses a read() or similar
 * method, you can safely assume it calls on the Stream class.
 *
 * \sa <a href="https://www.arduino.cc/en/Reference/Stream">Stream (Arduino.cc)</a>
 */
class Stream {
  public:
    /*!
     * \brief Checks the number of bytes available in the buffer
     *
     * \return The number of bytes available
     *
     * \sa <a href="https://www.arduino.cc/en/Reference/StreamAvailable">Stream::available (Arduino.cc)</a>
     */
    inline
    size_t
    available (
        void
    ) {
        return _available();
    }

    /*!
     * \brief Initializes the underlying serial channel
     */
    inline
    void
    begin (
        void
    ) {
        int error;

        if ( 0 != (error = _begin()) ) {
            errno = error;
#ifdef LOG_ERRORS
            ::perror("ERROR: Stream::begin - Underlying implementation encountered error!");
#endif
        }
    }

    /*!
     * \brief Closes the underlying serial channel
     *
     * \sa <a href="https://www.arduino.cc/en/Reference/Serial/End">Serial::end (Arduino.cc)</a>
     */
    inline
    void
    end (
        void
    ) {
        int error;

        if ( 0 != (error = _end()) ) {
            errno = error;
#ifdef LOG_ERRORS
            ::perror("ERROR: Stream::end - Underlying implementation encountered error!");
#endif
        }
    }

    /*!
     * \brief Clears the transmit buffer once all outgoing characters
     *        have been sent
     *
     * \warning Documentation descrepincy: The documentation states a
     *          boolean value is returned, but the actual source shows
     *          the return value to be of type `void`.
     *
     * \sa <a href="https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Stream.h">GitHub: Arduino/.../Stream.h</a>
     * \sa <a href="https://www.arduino.cc/en/Reference/StreamFlush">Stream::flush (Arduino.cc)</a>
     */
    inline
    void
    flush (
        void
    ) {
        int error;

        if ( 0 != (error = _flush()) ) {
            errno = error;
#ifdef LOG_ERRORS
            ::perror("ERROR: Stream::flush - Underlying implementation encountered error!");
#endif
        }
    }

    /*!
     * \brief Fetches the next byte from the buffer
     *
     * \return The first byte of incoming data available
     *
     * \note Returns -1 if there is no byte, although this should
     *       be avoided by first checking `available()` to see if
     *       data is available.
     *
     * \sa Stream::available
     * \sa <a href="https://www.arduino.cc/en/Reference/StreamRead">Stream::read (Arduino.cc)</a>
     */
    inline
    int
    read (
        void
    ) {
        int result = _read();

        if ( result < -1 || result > 255 ) {
            errno = ERANGE;
#ifdef LOG_ERRORS
            ::perror("ERROR: Stream::read - Underlying implementation result out of range!");
#endif
        }

        return result;
    }

    /*!
     * \brief Register a serial data ready callback
     *
     * This callback shall be invoked when serial data has become available
     *
     * \param [in] uponBytesAvailable_ Callback invoked when byte(s) are
     *                                 available in the buffer
     *
     * \param [in] context_ Optional context provided to `uponBytesAvailable_`
     *                      via the `context_` parameter
     */
    inline
    void
    registerSerialEventCallback (
        serial_event_t uponBytesAvailable_,
        void * context_ = nullptr
    ) {
        int error;

        if ( !uponBytesAvailable_ ) { context_ = nullptr; }

        if ( 0 != (error = _registerSerialEventCallback(uponBytesAvailable_, context_)) ) {
            errno = error;
#ifdef LOG_ERRORS
            ::perror("ERROR: Stream::registerSerialEventCallback - Underlying implementation encountered error!");
#endif
        }
    }

    /*!
     * \brief Writes a byte to the stream
     *
     * \param [in] byte_ The byte of data to write into the stream
     *
     * \sa <a href="https://www.arduino.cc/en/Reference/Serial/Write">Serial::write (Arduino.cc)</a>
     */
    inline
    void
    write (
        uint8_t byte_
    ) {
        int error;

        if ( 0 != (error = _write(byte_)) ) {
            errno = error;
#ifdef LOG_ERRORS
            ::perror("ERROR: Stream::write - Underlying implementation encountered error!");
#endif
        }
    }

  protected:
    ~Stream (void) {}

  private:
    virtual
    size_t
    _available (
        void
    ) = 0;

    virtual
    int
    _begin (
        void
    ) = 0;

    virtual
    int
    _end (
        void
    ) = 0;

    virtual
    int
    _flush (
        void
    ) = 0;

    virtual
    int
    _read (
        void
    ) = 0;

    virtual
    int
    _registerSerialEventCallback (
        serial_event_t uponBytesAvailable_,
        void * context_
    ) = 0;

    virtual
    int
    _write (
        uint8_t byte_
    ) = 0;
};

}  // namespace serial_wiring

/*!
 * \brief Arduino compatible `Stream`
 *
 * Arduino expects the `Stream` class to be available in
 * the global namespace. This typedef promotes it from
 * serial_wiring into the global namespace.
 */
typedef serial_wiring::Stream Stream;

#endif // STREAM_H

/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */
