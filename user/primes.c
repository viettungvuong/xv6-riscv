#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes_find(int start_pipe)
{
  int right_pipe[2], primes[35], count = 0, prime, i = 0;
  char num, buf[1];

  for (; read(start_pipe, buf, sizeof(buf)) != 0; ++count)
  {
    primes[count] = buf[0];
  }
  close(start_pipe);
  if (count == 0)
  {
    return;
  }

  // output
  prime = primes[0];
  printf("prime %d\n", prime);

  // lọc số nguyên tố
  pipe(right_pipe);
  for (; i < count; ++i)
  {
    if (primes[i] % prime != 0) // giống ý tưởng của sàng evatosthenes
    {
      num = primes[i]; // gửi số nguyên tố qua pipe
      write(right_pipe[1], &num, 1);
    }
  }
  close(right_pipe[1]);

  int pid = fork();
  if (pid == 0)
  {
    primes_find(right_pipe[0]);
  }
}

int main(int argc, char *argv[])
{
  int first_pipe[2];
  char num;

  pipe(first_pipe); // tạo pipe để truyền các số nguyên tố

  for (int i = 2; i <= 35; i++)
  {
    num = i;
    write(first_pipe[1], &num, 1); // viết các số từ 2 đến 35 vào pipe
  }
  close(first_pipe[1]);

  primes_find(first_pipe[0]); // tìm số nguyên tố
  wait(0);
  return 0;
}