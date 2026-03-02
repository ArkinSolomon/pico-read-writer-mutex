#ifndef READ_WRITER_MUTEX_H
#define READ_WRITER_MUTEX_H

#include <pico/mutex.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup read_writer_mutex Read-Writer Mutex
 * @{
 */

/**
 * @brief A single pico read-writer mutex. 
 * 
 * Operates by keeping track of the number of readers and only allows writing
 * when the number of readers is zero.
 */
typedef struct
{
  /** @private */
  unsigned int reader_count;
  /** @private */
  mutex_t reader_mutex;
  /** @private */
  mutex_t writer_mutex;
  /** @private */
} read_writer_mutex_t;

/**
 * @brief Initialize a read-writer mutex.
 * 
 * Must be called before using the mutex.
 * 
 * @param mtx Pointer to mutex structure.
 */
void read_writer_mutex_init(read_writer_mutex_t* mtx);

/**
 * @brief Acquire the mutex's read lock.
 * 
 * This function blocks until the read lock is acquired. Release with
 * rw_mutex_exit_read(read_writer_mutex_t*). The mutex must be initialized 
 * before calling this function with read_writer_mutex_init(read_writer_mutex_t*).
 * 
 * @param mtx Pointer to mutex structure.
 */
void rw_mutex_enter_read_blocking(read_writer_mutex_t* mtx);

/**
 * @brief Release the mutex's read lock.
 * 
 * This function decrements the number of readers on the provided mutex. Note 
 * that continuing to decrement the reader count below zero is possible, and 
 * will require calling rw_mutex_enter_read_blocking(read_writer_mutex_t*) to
 * restore it back to zero, or read_writer_mutex_init(read_writer_mutex_t*) to
 * reset the count. The mutex must be initialized before calling this function 
 * with read_writer_mutex_init(read_writer_mutex_t*).
 * 
 * @param mtx Pointer to mutex structure.
 */
void rw_mutex_exit_read(read_writer_mutex_t* mtx);

/**
 * @brief Gain exclusive write access to the shared resource.
 * 
 * This function will block until there are no readers on this mutex, and then
 * will acquire the write lock. The mutex must be initialized before calling
 * this function with read_writer_mutex_init(read_writer_mutex_t*).
 * 
 * @param mtx Pointer to mutex structure.
 */
void rw_mutex_enter_write_blocking(read_writer_mutex_t* mtx);

/**
 * @brief Release exclusive write access to the shared resource.
 * 
 * This function will release exclusive write access to the shared resource.
 * Attempting to release write access without first acquiring it is undefined
 * behavior. The mutex must be initialized before calling this function with
 * read_writer_mutex_init(read_writer_mutex_t*).
 * 
 * @param mtx Pointer to mutex structure.
 */
void rw_mutex_exit_write(read_writer_mutex_t* mtx);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
