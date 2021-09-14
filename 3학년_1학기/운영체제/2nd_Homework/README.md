## Implementing Priority-based Round-Robin Scheduler
* 개발 환경 : C / Ubuntu 18.04 (VMware)
* 전체적인 구조<br>
<kbd><img src = "https://user-images.githubusercontent.com/48857568/133263376-6a326ade-9d98-4e25-a4e9-e8ec4f477e19.JPG" width="550" height="350"></kbd><br>

* ### Problem Description
  * C언어를 이용하여 우선순위 라운드 로빈 스케줄러를 구현한다.
  * 과제1의 Hash table를 구성하는 queue들을 ready queue들로 정의한다.
  * 과제 1의 Free List를 Thread waiting queue로 정의한다.
  * 각 ready queue의 entry 번호는 thread priority 번호이다.
  * Entry의 번호가 작을수록 thread priority가 높다고 가정한다.
  * 각 Ready queue의 thread는 round robin으로 스케줄링 된다.
  * Priority가 높은, 즉 priority번호가 가장 낮은 ready queue의 thread들을 우선적으로 스케줄링 한다.
  * Thread 가 ready state 또는 ready queue로 들어가는 시점
    * Thread가 처음 생성되었을 때
    * CPU에서 실행되는 running state의 thread가 높은 priority의 thread에 의해 쫓겨났을 때
    * CPU에서 실행되는 running state의 thread가 time slice를 모두 소비했을 때
    * Waiting state의 thread가 깨어났을 때
  * `Ready Queue & Task Waiting Queue`
    * CPU에 실행할 Thread는 Ready queue의 head에서 뺀다.
    * Ready queue로 넣을 때는 tail로 넣는다.
    * 단, ready queue로 thread를 넣을 때는 자신의 priority에 대응하는 ready queue에 넣는다.
  * `Thread Control Block(TCB)`
    * Thread의 정보를 저장하는 구조체.
    * 스케줄링에 필요한 정보를 저장함.
    * Thread를 생성할 때 해당 thread를 위한 TCB를 메모리에서 할당하고 초기화함.
    * TCB는 thread의 상태에 따라 ready queue 또는 waiting queue에 포함됨.
    * TCB에 해당하는 Thread 구조체의 멤버 변수들은 아래와 같다.
      * `int stackSize` : thread의 크기를 저장하는 변수.
      * `void* stackAddr` : thread의 주소를 저장하는 변수.
      * `ThreadStatus status` : thread의 현재 상태를 저장하는 변수(run, ready, wait, zombie의 4가지 상태가 있다)
      * `int exitCode` : thread가 종료되었을 때의 종료 코드
      * `pid_t pid` : thread의 id를 나타내는 변수
      * `Thread* phNext` : 다음 thread의 위치를 저장하는 변수
      * `Thread* phPrev` : 이전 thread의 위치를 저장하는 변수
  * `Thread Table`
    * 구조
    
    <kbd><img src = "https://user-images.githubusercontent.com/48857568/133263216-57e3d593-2fdd-43c2-b178-2cda4daa1179.JPG" width="500" height="320"></kbd>
    * 모든 thread를 관리하는 테이블이다.
    * Table의 각 entry는 생성된 thread의 TCB를 가리키며, entry 번호가 thread id로 정의됨.
    * Table의 entry가 유효한 TCB를 가리키는지를 판단하기 위해 bUsed flag를 사용함.
    * 주의: thread를 생성할 때 entry 0부터 빈 entry를 찾아서 할당하고, thread를 제거할 때 해당 thread id가 지정하는 entry의 bUsed를 리셋함.
  * `Thread* pCurrentThread`
    * Running 중인 thread는 ready queue, waiting queue에 모두 포함되지 않는다.
    * 따라서 Running thread를 저장하기 위한 변수인 pCurrentThread가 필요하다.
<hr></hr>

* ### 구현 함수
  * `int thread_create(thread_t* thread, const pthread_attr_t* attr, int priority, void *(*start_routine)(void *), void* arg);`
    * 함수 매개변수 설명
      * `thread_t* thread `: 생성된 thread id를 반환한다. Thread table에서 할당된 ThreadTblEnt의 index 번호를 가지도록 구현한다.
      * `const pthread_attr_t* attr`: NULL로 가정함.
      * `int priority`: pthread API에 없으며, Priority 설정을 위해 추가됨.
      * `void *(*start_routine)(void *)`: thread가 실행할 함수 포인터
      * `void* arg`: thread가 실행할 함수로 전달될 argument
    * Thread를 생성하기 위한 함수이다.
    * pthread API의 pthread_create()와 동일한 interface를 가진다.
    * 생성된 thread는 priority가 지정하는 ready queue에 넣는다.
    * thread의 생성은 clone 함수를 통해서 수행된다.
    * clone() 으로 생성된 child thread 를 강제 정지시킨 후에 ready queue (child priority <= running thread)에 넣든지 아니면 context switching(child priority > running thread)을 준비해야 한다 .
    * 그렇지 않으면 , parent thread 와 번갈아 가면서 실행된다.이런 동작은 우리가 원하는 스케줄링으로 구동이 안된다는 것이다. 또한 Child thread 의 TCB 를 접근할 때 동기화 문제가 야기될 수 있음
    * pHashTableEnt의 `ObjNum % 8` 인덱스에 해당 ObjNum을 갖는 pObj를 Tail 부분에 삽입한다.
  * `thread_t thread_self(void);`
    * 자신의 Thread id 를 반환한다
    * 주의 : 이 함수를 호출한 thread 의 TCB 를 가리키는 ThreadTblEnt 를 찾고, 그 entry 의 index 값을 반환하도록 구현해야 함. 내부적으로 clone() 으로 생성된 thread id 를 받아서 Thread table에 등록된 TCB의 pid와 비교하자. thread id는 getpid()로 얻으면 된다. Clone() 으로 생성된 thread, process id 모두 pid 이다. Process control을 위해 사용한 모든 system call 을 thread 를 제어하기 위해 사용 가능함.
  * `int thread_suspend(thread_t tid);`
    * 인자로 받은 thread id에 해당하는 thread를 일시 정지시킨다. thread id는 Thread table의 index 값이다.
    * 만약 함수가 성공적으로 수행되면 0을 리턴하고, 아니라면 -1을 리턴한다.
    * 이 함수로 일시 정지될 thread는 ready queue 또는 waiting queue에 있을 수 있다.
    * 일시 정지되는 thread의 TCB는 반드시 waiting queue로 들어간다. 단, waiting queue의 tail로 들어간다.
  * `int thread_resume(thread_t tid);`
    * 인자로 받은 thread id를 가진 일시 정지된 thread를 회복시킨다.
    * 만약 함수가 성공적으로 수행되면 0을 리턴하고, 아니라면 -1을 리턴한다.
    * Resume 대상 thread의 priority에 따라 동작이 크게 달라진다.
    * 대상 thread가 running thread보다 우선 순위가 높으면 running thread를 preemption 시킨다. 즉, Resume 대상 thread로 context switching이 발생한다.
    * 우선 순위가 낮다면 단순히 대상 thread를 ready queue로 이동만 하면 된다.
  * `void __ContextSwitch(int curpid, int newpid);`
    * CPU에서 실행중인 thread를 정지시킨다: kill(curpid, SIGSTOP)
    * 새롭게 실행할 thread를 실행시킨다: kill(newpid, SIGCONT)
  * `void RunScheduler(void);`
    * CPU에서 running 중인 thread가 TIMESLICE를 다 사용해서 ready queue로 쫓아내질 때 스케줄러가 사용된다.
    * ready queue의 제일 앞에 있는 thread가 CPU에서 돌아가게 된다.
    * real-time timer로 구현된다.
    * 주의: alarm() 대신 sleep(), pause() 사용을 금지한다.
  * `int thread_join(thread_t tid, void** retval);`
    * parent thread가 자신이 생성한 child thread인 tid가 종료될 때까지 기다린다.
    * retval: thread_exit()의 인자로 전달된 값을 저장한다.
    * 함수의 실행 순서는 아래의 그림과 같다.
    
    <kbd><img src = "https://user-images.githubusercontent.com/48857568/133267779-a302d443-53c4-48f7-ada9-d9d251ec5083.JPG" width="300" height="500"></kbd>
    * Parent는 child thread가 종료되었음을 아래와 같이 확인할 수 있다.
      * Child thread가 종료되면 parent thread로 SIGCHLD 시그널이 전송된다.
      * Parent thread는 SIGCHLD 시그널에 대한 handler를 구현한다.
      * 이 handle에서 (1)의 코드가 시작되도록 구현해야 한다.
    * Zombie reaping
      * Child thread의 청소는 parent thread가 담당한다
      * (2)에서 Child thread의 TCB를 제거하고, stack도 제거한다.
  * `int thread_exit(void* retval);`
    * running 중인 thread 자신을 종료하는 함수이다.
    * retval: thread_join으로 기다리는 parent에게 전달할 값을 저장하는 변수 또는 exitCode이다.
    * 종료된 thread는 ready queue에 있으면 안된다. 왜냐하면 scheduler가 실행할 수 있기 때문이다.
    * 이 함수가 호출되면 zombie thread가 된다. 이를 위해서 zombie queue가 필요하지만 간단한 구현을 위해 waiting queue로 보내도록 한다.
    * thread의 실행을 마무리하고 return하기 전에 무조건 호출한다.
    * 만약 함수가 성공적으로 수행되면 0을 리턴하고, 아니라면 -1을 리턴한다.
