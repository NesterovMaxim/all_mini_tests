#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <random>

typedef uint16_t data_t;

std::atomic<data_t> data;
//data_t data;
std::mutex m;
unsigned cnt = 1100;

typedef std::mt19937 MyRNG;  // the Mersenne Twister with a popular choice of parameters
uint32_t seed_val;           // populate somehow

MyRNG rng;                   // e.g. keep one global instance (per thread)

std::uniform_int_distribution<uint32_t> uint_dist10(0,30);

void do_work()
{
  //m.lock(); m.unlock();

  std::this_thread::sleep_for(std::chrono::milliseconds(uint_dist10(rng)));

  //data.fetch_add(1, std::memory_order_relaxed);

  data++;
}
 
void check()
{
  std::vector<std::thread> pool;

  //m.lock();

  for (unsigned i = 0; i < cnt; ++i)
  {
    pool.push_back(std::thread(do_work));
  }


    //m.unlock();
 
    for (unsigned i = 0; i < cnt; ++i)
    {
      pool[i].join(); 
    }
}

int main()
{
  rng.seed(seed_val);

  unsigned total = 0;
  unsigned failed = 0;
  while (true)
  {
    ++total;
    check();
    if (data != cnt)
    {
      ++failed;
      std::cout << "Result:" << data << '\n';
    }

    if (total % 100 == 0)
    {
      std::cout << "\tTotal:\t" << total<< '\n';
      std::cout << "\tFailed:\t" << failed<< '\n';
      std::cout << "\tErrRate:\t" << double(failed)/(double(total)/100.0) << '\n';
    }

    data = 0;
  }
 
}