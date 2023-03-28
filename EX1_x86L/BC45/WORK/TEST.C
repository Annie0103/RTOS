// RM
//– { (1,3), (3,6) }
//– { (1,3), (3,6), (4,9) }

//OSTimeTick =  Add a piece of code in OSTimeTick to decrement 
//the compTime counter in the running task’s os_tcb

//OSIntExit() = This function will manage the scheduling after the 
//system has come back from the calling of ISR (preemp)

//OS_Sched() = is called when a task is voluntarily 
//giving up its possession of the CPU (complete)
//-----------------------------------------------
//OSStart() = This is function will try to find the task with the 
//highest priority and schedule it to run. 
//Called only once when the system executing tasks 
//for the very first time

#include "includes.h"

#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define  N_TASKS                        3       /* Number of identical tasks        */


OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];
char          TaskData[N_TASKS];                      /* Parameters to pass to each task               */
OS_EVENT     *RandomSem;

typedef struct{
    INT16U   c;  
    INT16U   p;             
} RM;

RM TaskUserData[N_TASKS];
INT8U err;

//typedef struct{
//    BOOLEAN   c;  
//    INT16U   from;
//    INT16U   to;  
//    INT16U   tt; //tick           
//} printout;
//static printout buffer[100];
//static INT32U  ccccc;

/*typedef struct{
    printout  buffer[100];
    INT32U  ccccc;
    RM TaskUserData[N_TASKS];   
} doTask;
doTask DO;*/

void Task(void *pdata)
{
    int start ; //the start time
    int end ; //the end time
    int toDelay;
    //INT32U C;
    OSTCBCur->compTime = ((RM *)pdata)->c;
    //printf("\n&which: %d cc %d", OSPrioCur,((RM *)pdata)->c);
    OSTCBCur->period = ((RM *)pdata)->p;
    //printf("\n&which: %d pp %d", OSPrioCur,((RM *)pdata)->p);
    
    start=OSTimeGet();
    while(1)
    {
        //OS_ENTER_CRITICAL();
        while(OSTCBCur->compTime>0) //C ticks
        {
            // do nothing
        }
        //OS_ENTER_CRITICAL();  
        //OSSemPend(RandomSem, 0, &err);
        end = OSTimeGet() ; // end time
        toDelay = (OSTCBCur->period)-(end-start) ;//period == (end-start)
        start = start+(OSTCBCur->period) ; // next start time
        OSTCBCur->compTime = ((RM *)pdata)->c;//C ;// reset the counter (c ticks for computation)
        //OSSemPost(RandomSem);
        //OS_EXIT_CRITICAL();
        //OS_EXIT_CRITICAL();
        OSTimeDly (toDelay); // delay and wait (P-C) times
        //print_buffer();
    }
}
static void TaskStartCreateTasks(void)
{
    TaskUserData[0].c = 1;
    TaskUserData[0].p = 3;
    TaskUserData[1].c = 3;
    TaskUserData[1].p = 6;
    TaskUserData[2].c = 4;
    TaskUserData[2].p = 24;
    
    OSTaskCreate(Task, (void *)&TaskUserData[0], &TaskStk[0][TASK_STK_SIZE - 1], 1);
    OSTaskCreate(Task, (void *)&TaskUserData[1], &TaskStk[1][TASK_STK_SIZE - 1], 2);
    OSTaskCreate(Task, (void *)&TaskUserData[2], &TaskStk[2][TASK_STK_SIZE - 1], 3);
}


static  void  TaskStartDispInit (void)
{
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
    PC_DispStr( 0,  0, "                                    Lab #1                                      ", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
    PC_DispStr( 0,  1, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  2, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  3, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  9, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 10, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 12, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 13, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 14, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 15, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 16, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 17, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 18, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 21, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 22, "#Tasks          :        CPU Usage:                                             ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 23, "#Task switch/sec:                                                               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 24, "                            <-PRESS 'ESC' TO QUIT->                             ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
}
static  void  TaskStartDisp (void)
{
    //char   s[80];
    //char   behavior[40];


    //sprintf(s, "%5d", OSTaskCtr);                                  /* Display #tasks running               */
    //PC_DispStr(18, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

#if OS_TASK_STAT_EN > 0
    //sprintf(s, "%3d", OSCPUUsage);                                 /* Display CPU usage in %               */
    //PC_DispStr(36, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
#endif

    //sprintf(s, "%5d", OSCtxSwCtr);                                 /* Display #context switches per second */
    //PC_DispStr(18, 23, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

    //sprintf(s, "V%1d.%02d", OSVersion() / 100, OSVersion() % 100); /* Display uC/OS-II's version number    */
    //PC_DispStr(75, 24, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

    print_buffer();

}
void  TaskStart (void *pdata)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif
    //char       s[100];
    INT16S     key;

    pdata = pdata;                                         /* Prevent compiler warning                 */

    //TaskStartDispInit();                                   /* Initialize the display                   */

    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);                           /* Install uC/OS-II's clock tick ISR        */
    PC_SetTickRate(OS_TICKS_PER_SEC);                      /* Reprogram tick rate                      */
    OS_EXIT_CRITICAL();

    OSStatInit();                                          /* Initialize uC/OS-II's statistics         */


    TaskStartCreateTasks();                                /* Create all the application tasks         */

    for (;;) {
        print_buffer();//TaskStartDisp();                                  /* Update the display                       */


        if (PC_GetKey(&key) == TRUE) {                     /* See if key has been pressed              */
            if (key == 0x1B) {                             /* Yes, see if it's the ESCAPE key          */
                PC_DOSReturn();                            /* Return to DOS                            */
            }
        }

        OSCtxSwCtr = 0;                                    /* Clear context switch counter             */
        OSTimeDly(200);//HMSM(0, 0, 1, 0);                         /* Wait one second                          */
    }
}
void  main (void)
{
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

    OSInit();                                              /* Initialize uC/OS-II                      */

    PC_DOSSaveReturn();                                    /* Save environment to return to DOS        */
    PC_VectSet(uCOS, OSCtxSw);                             /* Install uC/OS-II's context switch vector */

    RandomSem   = OSSemCreate(1);                          /* Random number semaphore                  */
    OSTimeSet(0);


    //OS_ENTER_CRITICAL();
    //PC_VectSet(0x08, OSTickISR);                           /* Install uC/OS-II's clock tick ISR        */
    //PC_SetTickRate(OS_TICKS_PER_SEC);                      /* Reprogram tick rate                      */
    //OS_EXIT_CRITICAL();

    //OSStatInit();                                          /* Initialize uC/OS-II's statistics         */

    //TaskStartCreateTasks();      


    OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);

    OSStart();                                             /* Start multitasking                       */
}


// 計算utilization if  sigma(c/p) <= U(n) = n(2^(1/n)-1), scheduable; otherwise not sure

// 算response time ? 

// ostickisr = 系統的
 