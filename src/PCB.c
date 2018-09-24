#include "stringlib.h"
#include "PCB.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define NAME_NOT_FOUND -0x0001
#define NAME_INVALID -0x0002
#define CLASS_INVALID -0x0003
#define PRIORITY_INVALID -0x0004
#define STATE_INVALID -0x0005
#define UNSPECIFIED_ERROR -0x0006
#define NAME_NOT_UNIQUE -0x0007





typedef struct ProcessQueues{
  PCB* readyHead;
  PCB* blockedHead;
  int sizerdy;
  int sizeblk;
}Queue;

Queue active = {(PCB*)-1, (PCB*)-1, 0, 0};
//Queue suspended = {-1, -1, 0};


PCB* AllocatePCB(){
  void* ptr = malloc(sizeof(PCB));
  if(ptr == NULL){
    return NULL;
  }
  else{
    return (PCB*) ptr;
  }
}

int FreePCB(PCB* pcb){
  if(pcb == NULL){
    return -1;
  }
  free(pcb);
}

PCB* SetupPCB(char* name, int class, int priority){
  if(strlen(name) < 8){
    return (PCB*)NAME_INVALID;
  }
  if(priority < 0){
    return (PCB*)PRIORITY_INVALID;
  }
  if(class < 0 || class > 1){
    return (PCB*) CLASS_INVALID;
  }

  PCB* ptr = AllocatePCB();

  if(ptr == (PCB*)-1){
    return (PCB*)UNSPECIFIED_ERROR;
  }

  char* A = malloc(strlen(name)*sizeof(char));
  if(A == NULL){
    return (PCB*)NAME_INVALID;
  }
  strcpy(A, name);
  ptr->pname = A;
  ptr->class = class;
  ptr->priority = priority;
  ptr->state = 0;
  ptr->suspended = 0;
  ptr->next = (PCB*)-1;
  ptr->previous = (PCB*)-1;
  //InsertPCB(ptr, 0);

  return ptr;
}

PCB* FindPCB(char* name, int remove){
  int i = 0;
  PCB* Node;
  Node = active.readyHead;
  for(i = 0; i < active.sizerdy; i++){
    if(strcmp(Node->pname, name) == 0){
      if(remove == 1){
        active.sizerdy--;
      }
      return Node;
    }
    Node = Node->next;
  }

  Node = active.blockedHead;
  for(i = 0; i < active.sizeblk; i++){
    if(strcmp(Node->pname, name) == 0){
      if(remove == 1){
        active.sizeblk--;
      }
      return Node;
    }
    Node = Node->next;
  }
  return (PCB*)NAME_NOT_FOUND;

  // PCB* Head = suspended.readyHead;
  // for(i = 0; i < suspended.sizerdy; i++){
  //   if(strcmp(Head.name, name) == 0){
  //     return Head;
  //   }
  //   Head = Head->next;
  // }
  // PCB* Head = suspended.readyHead;
  // for(i = 0; i < suspended.sizeblk; i++){
  //   if(strcmp(Head.name, name) == 0){
  //     return Head;
  //   }
  //   Head = Head->next;
  // }
}

void InsertPCB(PCB* pcb, int state){
  PCB* Node;
  switch(state){
    case 0:
    if(active.readyHead == (PCB*)-1){
      active.readyHead = pcb;
      active.sizerdy++;
      return;
    }
    else{
      int i = 0;
      Node = active.readyHead;
      if(pcb->priority > Node->priority){
        active.readyHead = pcb;
        pcb->next = Node;
        Node->previous = pcb;
        active.sizerdy++;
        return;
      }
      for(i = 1; i < active.sizerdy; i++){
        Node = Node->next;

      }
      Node->next = pcb;
      pcb->previous = Node;
      active.sizerdy++;
      return;
    }
      break;
    case 1:
      Node = active.blockedHead;
      if(active.blockedHead == (PCB*)-1){
        active.blockedHead = pcb;
        active.sizeblk++;
        return;
      }
      int j = 0;
      for(j = 1; j < active.sizeblk; j++){
        Node = Node->next;
      }
      Node->next = pcb;
      pcb->previous = Node;
      active.sizeblk++;
      return;
  }
}

int RemovePCB(PCB* ptr){

  PCB* Nodep = ptr->previous;
  PCB* Noden = ptr->next;
  if( Nodep != (PCB*)-1){
    Nodep->next = Noden;
  }
  if(Noden != (PCB*)-1){
    Noden->previous = Nodep;
  }
  if(ptr == active.readyHead){
    active.readyHead = ptr->next;
  }
  if(ptr == active.blockedHead){
    active.blockedHead = ptr->next;
  }
  ptr->previous = (PCB*)-1;
  ptr->next = (PCB*)-1;


  return 1;
}


int CreatePCB(char* pname, int class, int priority){
  int j = (int)FindPCB(pname, 0);
  if(j >= 0){
    return NAME_NOT_UNIQUE;
  }
  PCB* ptr = SetupPCB(pname, class, priority);
    if(ptr < (PCB*)0){
      return ptr;
    }
    InsertPCB(ptr, 0);
}

int DeletePCB(char* pname){
  PCB* ptr = FindPCB(pname, 1);
  if(ptr <  0){
    return NAME_NOT_FOUND;
  }
  RemovePCB(ptr);
  free(ptr);
  return 1;
}

int BlockPCB(char* pname){
  if(strlen(pname) <= 0){
    return NAME_INVALID;
  }
  PCB* ptr = FindPCB(pname, 1);
  if(ptr == NAME_NOT_FOUND){
    return NAME_NOT_FOUND;
  }
  ptr->state = 1;
  RemovePCB(ptr);
  InsertPCB(ptr, 1);
}

int UnBlockPCB(char* pname){
  if(strlen(pname) <= 0){
    return NAME_INVALID;
  }
  PCB* ptr = FindPCB(pname, 1);
  if(ptr < (PCB*)0){
    return NAME_NOT_FOUND;
  }
  RemovePCB(ptr);
  InsertPCB(ptr, 0);
  ptr->state = 0;

}

int SuspendPCB(char* pname){
  if(strlen(pname) <= 0){
    return NAME_INVALID;
  }
  PCB* ptr = FindPCB(pname, 0);
  if(ptr == NAME_NOT_FOUND){
    return NAME_NOT_FOUND;
  }
  ptr->suspended = 1;
}

int ResumePCB(char* pname){
  if(strlen(pname) <= 0){
    return NAME_INVALID;
  }
  PCB* ptr = FindPCB(pname, 0);
  if(ptr < (PCB*)0){
    return NAME_NOT_FOUND;
  }
  ptr->suspended = 0;
}

int setPriorityPCB(char* pname, int priority){
  if(strlen(pname) <= 0){
    return NAME_INVALID;
  }
  PCB* ptr = FindPCB(pname, 0);
  if(ptr < (PCB*)0){
    return NAME_NOT_FOUND;
  }
  ptr->priority = priority;
  RemovePCB(ptr);
  InsertPCB(ptr, 0);
}

void showPCB(char* pname){
  PCB* ptr = FindPCB(pname, 0);
  if(ptr < (PCB*)0){
    printf("PCB Not Found\n");
    return;
  }
  printf("PCB Name: %s\nClass: %d\nState: %d\nSuspended: %d\nPriority: %d\n\n", ptr->pname, ptr->class, ptr->state, ptr->suspended, ptr->priority);
}

void showReadyPCB(){
  int i = 0;
  PCB* ptr = active.readyHead;
  for(i = 0; i < active.sizerdy; i++){
    printf("PCB Name: %s\nClass: %d\nState: %d\nSuspended: %d\nPriority: %d\n\n", ptr->pname, ptr->class, ptr->state, ptr->suspended, ptr->priority);
    ptr = ptr->next;
  }
}

void showBlockedPCB(){
  int i = 0;
  PCB* ptr = active.blockedHead;
  for(i = 0; i < active.sizeblk; i++){
    printf("PCB Name: %s\nClass: %d\nState: %d\nSuspended: %d\nPriority: %d\n\n", ptr->pname, ptr->class, ptr->state, ptr->suspended, ptr->priority);
    ptr = ptr->next;
  }
}

void showAllPCB(){
  showReadyPCB();
  showBlockedPCB();
}

void pctl(char** args, int argsc){
  int code = 0;
  if(argsc < 2){
    printf("Not enough arguments, %d\n", argsc);
    return;
  }
  if(strcmp(args[1], "suspend") == 0 && argsc == 3){

    code = SuspendPCB(args[2]);

  }else if(strcmp(args[1], "resume") == 0 && argsc == 3){

    code = ResumePCB(args[2]);

  }else if(strcmp(args[1], "setpriority") == 0 && argsc == 4){

    code = setPriorityPCB(args[2], atoi(args[3]));

  }else if(strcmp(args[1], "showpcb") == 0 && argsc == 3){

    showPCB(args[2]);

  }else if(strcmp(args[1], "showall") == 0){

    showAllPCB();

  }else if(strcmp(args[1], "showready") == 0){

    showReadyPCB();

  }else if(strcmp(args[1], "showblocked") == 0){

    showBlockedPCB();

  }else if(strcmp(args[1], "createpcb") == 0  && argsc == 5){

    code = CreatePCB(args[2], atoi(args[3]), atoi(args[4]));

  }else if(strcmp(args[1], "deletepcb") == 0 && argsc ==3){

    code = DeletePCB(args[2]);

  }else if(strcmp(args[1], "block") == 0 && argsc == 3){

    code = BlockPCB(args[2]);

  }else if(strcmp(args[1], "unblock") == 0 && argsc ==3){

    code = UnBlockPCB(args[2]);

  }
  else{
    printf("Syntax Error, Please check Documentation\n");
  }
  if(code >= 0){
    //printf("Success\n");
    return;
  }
  switch(code){
    case NAME_INVALID:
    printf("Name invalid!\n");
    break;

    case NAME_NOT_FOUND:
    printf("Name Not found!\n");
    break;

    case NAME_NOT_UNIQUE:
    printf("Name is not Unique!\n");
    break;

    case CLASS_INVALID:
    printf("Invalid Process Class!\n");
    break;

    case PRIORITY_INVALID:
    printf("Invalid Priority\n");
    break;

    case STATE_INVALID:
    printf("Invalid State!\n");
    break;

    case UNSPECIFIED_ERROR:
    printf("Memory Allocation or other error!\n");
    break;

    default:
    printf("Unknown error %d\n", code);
    break;
  }
}
