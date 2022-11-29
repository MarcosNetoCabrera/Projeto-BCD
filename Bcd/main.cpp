#include <stdio.h>

#include "RotateRegister.h"
#include "BcdToDecimal.h"
#include "DataRegister.h"
#include "DecimalToBcd.h"
#include "BcdAddSub.h"

#include "keyboard.h"
#include "debugprint.h"
#include "LogicBuilder.h"
#include "BcdUs.h"
#include "Monitor.h"

int main(){


  Monitor    *mon = NULL;
  mon = new Monitor();

  
  for (int i = 0; i < 14; i++){
    if(i == 0){
        mon->setupDevice();
        mon->selectMicroservice();
        mon->readOperation();
        mon->setup();
    }else if(i == 1){
        mon->doResetMicroservice();
        mon->setStart(1);
    }else{
       mon->doMicroservice();
       mon->writeOutputs();
    }
  }
    mon->readInputs();
    
    return 0;
}