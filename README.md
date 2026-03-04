# Pico Read Writer Mutex

This C library is used on the Raspberry Pi Pico to have a read-writer lock, which allows access multiple readers, but only one writer at a time, to a shared resource. Requires the [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk).

# Example Usage

```c
#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>

#include <read_writer_mutex.h>

read_writer_mutex_t mtx;
uint8_t my_shared_var = 10;

void core1();

int main()
{
  read_writer_mutex_init(&mtx);

  multicore_reset_core1();
  multicore_launch_core1(core1);

  // Enter the read lock for 100ms
  rw_mutex_enter_read_blocking(&mtx);
  printf("%u", my_shared_var); // 10
  sleep_ms(100);
  rw_mutex_exit_read(&mtx);

  // Wait for 50ms
  sleep_ms(50);

  // Waits an additional 50ms (for core1 to release write lock)
  rw_mutex_enter_read_blocking(&mtx);
  printf("%u", my_shared_var); // 30
  rw_mutex_exit_read(&mtx);
  return 0;
} 

void core1()
{
  // Enter the read lock for 50ms
  rw_mutex_enter_read_blocking(&mtx);
  printf("%u", my_shared_var); // 10
  sleep_ms(50);
  rw_mutex_exit_read(&mtx);

  // Waits for an additional 50ms (for core0 to release read), then lock
  // exclusively for 100ms
  rw_mutex_enter_write_blocking(&mtx);
  my_shared_var = 30;
  sleep_ms(100);
  rw_mutex_exit_write(&mtx);
}
```

# Licensing & Credit

Licensed under MIT. See LICENSE file for more information. Code developed for NASA 2024-2025 University Student Launch Initiative at Cedarville University. Originally developed by Arkin Solomon. Archived at [ArkinSolomon/project-elijah](https://github.com/ArkinSolomon/project-elijah). Contributions encouraged.

&copy; 2026 Arkin Solomon<br/>
[arkinsolomon.net](https://arkinsolomon.net)
