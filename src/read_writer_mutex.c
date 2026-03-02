#include "../include/read_writer_mutex.h"

#include <pico/mutex.h>

void read_writer_mutex_init(read_writer_mutex_t* mtx)
{
  mtx->reader_count = 0;
  mutex_init(&mtx->reader_mutex);
  mutex_init(&mtx->writer_mutex);
}

void rw_mutex_enter_read_blocking(read_writer_mutex_t* mtx)
{
  mutex_enter_blocking(&mtx->reader_mutex);
  mtx->reader_count++;
  if (mtx->reader_count == 1)
  {
    mutex_enter_blocking(&mtx->writer_mutex);
  }
  mutex_exit(&mtx->reader_mutex);
}

void rw_mutex_exit_read(read_writer_mutex_t* mtx)
{
  mutex_enter_blocking(&mtx->reader_mutex);
  mtx->reader_count--;
  if (mtx->reader_count == 0)
  {
    mutex_exit(&mtx->writer_mutex);
  }
  mutex_exit(&mtx->reader_mutex);
}

void rw_mutex_enter_write_blocking(read_writer_mutex_t* mtx)
{
  mutex_enter_blocking(&mtx->writer_mutex);
}

void rw_mutex_exit_write(read_writer_mutex_t* mtx)
{
  mutex_exit(&mtx->writer_mutex);
}
