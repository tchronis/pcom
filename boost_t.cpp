/*
 * boost_t.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: tchr
 */


//It needs external libs , so boost must be compiled
//http://en.highscore.de/cpp/boost/index.html

#include <boost/thread/thread.hpp>
#include <iostream>
#include <ctime>

void wait(int seconds)
{
  boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

boost::mutex mutex;

void thread()
{

  double a=0;

  for (unsigned long i = 0; i < 1000000000; ++i)
  {
    //wait(1);
   //boost::lock_guard<boost::mutex> lock(mutex);
   a=a+i;
  }
  std::cout << "Thread " << boost::this_thread::get_id() << ":" << a << "  ";

}



int myt(int n)
{
  int m=boost::thread::hardware_concurrency();
  std::cout<<"This Computer has capabilities for running "<<m<<" threads concurrently.\n";
  clock_t time1,time2;
  time1=clock();
  m=(int)(3*m/4);
  std::cout<<"Running only for 3/4 the available power...\n";
  boost::thread_group tgroup;
  for(int i=0;i<m;i++)
  {tgroup.create_thread(boost::bind(thread));}

  tgroup.join_all();
  /*
  boost::thread t1(thread);
  boost::thread t2(thread);
  boost::thread t3(thread);
  boost::thread t4(thread);
  boost::thread t5(thread);
  boost::thread t6(thread);
  boost::thread t7(thread);
  boost::thread t8(thread);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  */


  time2=clock();
  std::cout<<"\nAdded "<<m<<" billion numbers in "<<(float)(1.0*(time2-time1)/(1.0*CLOCKS_PER_SEC))<<" seconds.\n";
  return 0;
}


