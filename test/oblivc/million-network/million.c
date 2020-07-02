#include<stdio.h>
#include<obliv.h>
#include<memory.h>

#include"million.h"
#include"../common/util.h"


int currentParty;
const char* mySide()
{
  if(currentParty==1) return "Generator";
  else return "Evaluator";
}

double lap;

int main(int argc,char *argv[])
{
  ProtocolDesc pd;
  protocolIO io;
  if(argc<4)
  { if(argc<2) fprintf(stderr,"Port number missing\n");
    else if(argc<3) fprintf(stderr,"Server location missing\n");
    else fprintf(stderr,"wealth missing\n");
    fprintf(stderr,"Usage: %s <port> <--|remote_host> <string>\n",argv[0]);
    return 1;
  }

  sscanf(argv[3], "%d", &io.mywealth);

  //protocolUseStdio(&pd);
  const char* remote_host = (strcmp(argv[2],"--")?argv[2]:NULL);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);

  currentParty = (remote_host?2:1);
  setCurrentParty(&pd,currentParty);
  lap = wallClock();
  setupYaoProtocol(&pd, true);
  //cleanupProtocol(&pd);
  for(int i=0; i<1; i++){
      //ocTestUtilTcpOrDie(&pd, remote_host, argv[1]);
      mainYaoProtocol(&pd, true, millionaire, &io);
      //cleanupProtocol(&pd);
  }
  // mainYaoProtocol(&pd, true, editDistance, &io);
  cleanupYaoProtocol(&pd);
  // execYaoProtocol(&pd,editDistance,&io);
  fprintf(stderr,"%s total time: %lf s\n",mySide(),wallClock()-lap);
  cleanupProtocol(&pd);
  fprintf(stderr,"Result: %d\n",io.cmp);
  return 0;
}
