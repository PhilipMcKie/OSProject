#ifndef PCB_H
#define PCB_H
typedef struct ProcessControlBlock{
  char* pname;
  int class;
  int priority;
  int state;
  int suspended;
  struct ProcessControlBlock* next;
  struct ProcessControlBlock* previous;
}PCB;

PCB* AllocatePCB();
int FreePCB(PCB*);
PCB* SetupPCB(char*, int, int);
PCB* FindPCB(char*, int);
void InsertPCB(PCB*, int);
int RemovePCB(PCB*);
int CreatePCB(char*, int, int);
int DeletePCB(char*);
int BlockPCB(char*);
int UnBlockPCB(char*);
int SuspendPCB(char*);
int ResumePCB(char*);
int setPriorityPCB(char*, int);
void showPCB(char*);
void showReadyPCB();
void showBlockedPCB();
void showAllPCB();
void pctl(char** args, int argc);

#endif
