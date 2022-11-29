
#ifndef DELIVERY_56_BCDUS_H
#define DELIVERY_56_BCDUS_H

#include "Microservice.h"
#include "DecimalToBcd.h"
#include "BcdAddSub.h"
#include "BcdAddSub.h"
#include "DataRegister.h"
#include "RotateRegister.h"


enum class stateType : int
{
    reset         =  0,
    off           =  1,
    on            =  2,
    noise         =  3
};

class BcdUs : public Microservice{
public:
    BcdUs(){

        gen = 0; BCD = 0; reg1 = 0; bcd_addsub = 0; reg2 = 0; decimal = 0;
        enableActive = 0;
        enable = 0;
        rot_register = NULL;
        decimal2bcd = NULL;
        dataRegister1 = NULL;
        Bcd_AddSub = NULL;
        dataRegister2 = NULL;
        bcd2decimal = NULL;
        activesDefault();

    }

    void setRotateRegister (RotateRegister *rr)
    {
        if (rr != NULL)
        {
            /*! Guarda a referência do objeto Comparador */
            rot_register = rr;

            /*! Ajusta asaída de sinalização */
            classActive[0] = 1;
            logicActive[0] = rot_register->getActive ();
        }
        else
        {
            /*! Ajusta a saída de sinalização */
            classActive[0] = 0;
        }
        setActive ();
    }

    void setDecimalToBcd(DecimalToBcd *d2b){
        if(d2b != NULL){
            decimal2bcd = d2b;
            classActive[1] = 1;
            logicActive[1] = d2b->getActive();
        }else{
            classActive[1] = 0;
        }
        setActive();
    }

    void setDataRegister1(DataRegister *data_reg1){
        if(data_reg1 != NULL){
            dataRegister1 = data_reg1;
            classActive[2] = 1;
            logicActive[2] = data_reg1->getActive();
        }else{
            classActive[2] = 0;
        }
        setActive();
    }

    void setBcdAddSub(BcdAddSub *bcdaddsub){
        if(bcdaddsub != NULL){
            Bcd_AddSub = bcdaddsub;
            classActive[3] = 1;
            logicActive[3] = 1;
        }else{
            classActive[3] = 0;
        }
        setActive();
    }

    void setDataRegister2(DataRegister *data_reg2){
        if(data_reg2 != NULL){
            dataRegister2 = data_reg2;
            classActive[4] = 1;
            logicActive[4] = data_reg2->getActive();
        }else{
            classActive[4] = 0;
        }
        setActive();
    }

    void setBcdToDecimal(BcdToDecimal *b2d){
        if(b2d != NULL){
            bcd2decimal = b2d;
            classActive[5] = 1;
            logicActive[5] = b2d->getActive();
        }else{
            classActive[5] = 0;
        }
        setActive();
    }


    void doResetMicroservice ()
    {
        if ((enable == 1) && (active == 1))
        {
            gen = 0; BCD = 0; reg1 = 0; bcd_addsub = 0; reg2 = 0; decimal = 0;
            rot_register->doResetQ();
            dataRegister1->doResetQ();
            dataRegister2->doResetQ();

            /*! Ajusta máquina de estados para o início */
            state = stateType::reset;
        }
    }


    void setStart( int start){
        // printf("start : %d\n", start);
        if ((start >= 0) && (start <= 1))
        {
            /*! Guarda a entrada de controle. */
            BcdUs::start = start;

            /*! Ajusta a saída de sinalização. */
            startActive = 1;
        }
        else
        {
            /*! Ajusta a saída de sinalização. */
            startActive = 0;
        }
        setActive ();
    }
    void activesDefault(){
        for(int i = 0; i < 6; i++){
            BcdUs::classActive[i] = 0;
            BcdUs::logicActive[i] = 0;
        }
    }
    void doSetMicroservice (int s)
    {
        switch (s)
        {
            case 1:
                state = stateType::reset;
                break;

            case 2:
                state = stateType::on;
                break;

            default:
                /*! Detecção de ruído. */
                state = stateType::noise;
                break;
        }
    }


    void doMicroservice ()
    {
        if (active == 1)
        {
            switch (state)
            {
                case stateType::reset:
                    /*! Estado inicial. */
                    /*! Operação de reset do registradores. */
                    dataRegister1->doResetQ ();
                    dataRegister2->doResetQ ();

                    // reset do rotate register é setar q0
                    rot_register->setLoadEnable(1);
                    rot_register->setData(1);
                    rot_register->doRegister();
                    rot_register->setLoadEnable(0);

                    gen= rot_register->getQ();

                    decimal2bcd->setDecimal(gen);
                    decimal2bcd->doEncoder();
                    BCD = decimal2bcd->getBCD();

                    dataRegister1->setData(BCD);
                    dataRegister1->doRegister();
                    reg1 = dataRegister1->getQ();

                    Bcd_AddSub->setDataA(reg1); Bcd_AddSub->setDataB(1);
                    Bcd_AddSub->doArithmetic();
                    
                    bcd_addsub = Bcd_AddSub->getResult();
                    
                    dataRegister2->setData(bcd_addsub);
                    dataRegister2->doRegister();
                    reg2 = dataRegister2->getQ();

                    bcd2decimal->setBCD(reg2);
                    bcd2decimal->doDecoder();
                    decimal = bcd2decimal->getDecimal();

                    state = stateType::off;

                    break;

                case stateType::off:
                    setEnable(0);
                    state = stateType::on;
                    break;

                case stateType::on:
                    setEnable(1);

                    // Lógica
                    gen = ~ rot_register->getQ();
                    rot_register->doRegister();

                    decimal2bcd->setDecimal(gen);
                    decimal2bcd->doEncoder();
                    BCD = decimal2bcd->getBCD();

                    dataRegister1->setData(BCD);
                    dataRegister1->doRegister();
                    reg1 = dataRegister1->getQ();

                    Bcd_AddSub->setDataA(reg1);  Bcd_AddSub->setDataB(1);
                    Bcd_AddSub->doArithmetic();
                    
                    bcd_addsub = Bcd_AddSub->getResult();
                    
                    dataRegister2->setData(bcd_addsub);
                    dataRegister2->doRegister();
                    reg2 = dataRegister2->getQ();

                    bcd2decimal->setBCD(reg2);
                    bcd2decimal->doDecoder();
                    decimal= ~bcd2decimal->getDecimal();
                    break;
                
                
                case stateType::noise:
                    // printf("Estado noise\n");

                    state = stateType::reset;
                    break;

                default:

                    state = stateType::noise;
                    break;
            }

        }
    }


    int getClassActive(int pos){
        return classActive[pos];
    }

    int getLogicActive(int pos){
        return  logicActive[pos];
    }

    stateType getState(){
        return state;
    }

    int getGen(){
        return gen;
    }
    int getDecimal(){
        return decimal;
    }
    int* printOutput(){
        // out = {gen, BCD, reg1, bcd_addsub, reg2, decimal};
        // return out;
        
        /*printf("| gen : %d  | BCD : %d |  reg1 : %d |  bcd_addsub : %d  | reg2: %d |  Decimal : %d | state : %d |\n",
                 gen, BCD, reg1, bcd_addsub, reg2, decimal, state);*/
        
        printf(" | BCD : %d |  reg1 : %d |  bcd_addsub : %d  | reg2: %d  ",
                BCD, reg1, bcd_addsub, reg2);
    }

private:
    void setActive(){
        Microservice::setActive();
        active = 1;
        for(int i = 0; i < 6; i++){
            if(classActive[i] != 1 || logicActive[i] != 1 || startActive != 1){ //|| enableActive != 1 || enable != 1
                
                /*printf("classActive [%d] : %d || logicActive[%d] : %d || startActive : %d\n",
                    i, classActive[i], i, logicActive[i], enableActive, enable);*/
                active = 0;
                break;
            }
        }
    }

    /*! Entradas do microsserviço */
    RotateRegister *rot_register;
    DecimalToBcd *decimal2bcd;
    DataRegister *dataRegister1;
    BcdAddSub *Bcd_AddSub;
    DataRegister *dataRegister2;
    BcdToDecimal *bcd2decimal;

    /*! Controle do microsserviço */
    stateType       state;
    int start, startActive;
    int gen,  BCD, reg1, bcd_addsub,  reg2, decimal;
    int    classActive[6];
    int    logicActive[6];
    int    out[6];

};

#endif //DELIVERY_56_BCDUS_H
