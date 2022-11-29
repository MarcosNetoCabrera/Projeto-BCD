/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe concreta da fábrica de objetos lógicos.
 *
 * @file        LogicBuilder.h
 * @version     1.0
 * @date        27 Julho 2021
 *
 * @section     HARDWARES & SOFTWARES.
 *              +compiler     GDB online - C++ 17
 *              +revisions    Versão (data): Descrição breve.
 *                            ++ 1.0 (27 Julho 2021): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS.
 *              +institution  UFAM - Universidade Federal do Amazonas.
 *              +courses      Engenharia da Computação / Engenharia Elétrica.
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *
 *                            Compilação e Depuração:
 *                            +teacher    Miguel Grimm <miguelgrimm@gmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer outra versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZAÇÃO OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 *
 * @section     REFERENCES.
 *              + NASCIMENTO, Miguel G. do. Anotações de aula da disciplina de
 *                Arquitetura de Sistemas Digitais. Ufam, 2021.
 *              + NASCIMENTO, Miguel G. do. Anotações de aula da disciplina de
 *                Eletrônica Digital II. Ufam, 2021.
 * *****************************************************************************
 */


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_LOGICBUILDER_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_LOGICBUILDER_H_



#include "RotateRegister.h"
#include "DataRegister.h"
#include "BcdToDecimal.h"
#include "BcdAddSub.h"
#include "DecimalToBcd.h"
#include "Builder.h"


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa a fábrica de objetos lógicos.
 *
 *  @use      Sequência de uso dos serviços da classe.
 *
 *            ++ LogicBuilder    fac;
 *
 *            ++ fac.setEnable (enable);
 *
 *            ++ fac.buildFibonacci (dataBitSize);
 *            ++ fac.buildCompare (dataBitSize);
 *
 *            ++ fac.setupCounter (moduleSize);
 *            ++ fac.setupCompare (data);
 *
 *            ++ cnt = fac.getCounter ();
 *            ++ cmp = fac.getCompare ();
 * -----------------------------------------------------------------------------
 */
class LogicBuilder : public Builder
{

public:

    /*! --------------------------------------------------------------------------
     *  @brief      Configuração inicial do serviço da fábrica.
     *  --------------------------------------------------------------------------
     */
    LogicBuilder ()
    {
        activesDefault();
        /*! Configura as refrências dos objetos da fábrica */
        rotate_reg = NULL;
        Decimal2Bcd =NULL;
        dataRegister1 =NULL;
        bcdAddSub =NULL;
        dataRegister2 = NULL;
        Bcd2Decimal = NULL;

    }


    /*! --------------------------------------------------------------------------
     *  @brief      Liberação dos objetos lógicos criados na fábrica.
     *  --------------------------------------------------------------------------
     */
    ~LogicBuilder ()

    {

        /*! Libera todos os objetos lógicos da fábrica */

    }

    void buildRotateRegister(int dataBitSize = 10)
    {

        if(enable == 1){
            rotate_reg = new RotateRegister(dataBitSize);
            newActive[0] = 1;
        }else{
            newActive[0] = 0;
        }
        setActive();

    }

    void buildDecimalToBcd(){
        if(enable == 1){
            Decimal2Bcd = new DecimalToBcd;
            newActive[1] = 1;
        }else{
            newActive[1] = 0;
        }
        setActive();
    }

    void buildDataRegister1(int dataBitSize = 10){
        if(enable == 1){
            dataRegister1 = new DataRegister(dataBitSize);
            newActive[2] = 1;
        }else{
            newActive[2] = 0;
        }
        setActive();
    }

    void buildBcdAddSub(){
        if(enable == 1){
            bcdAddSub = new BcdAddSub;
            newActive[3] = 1;
        }else{
            newActive[3] = 0;
        }
        setActive();
    }

    void buildDataRegister2(int dataBitSize = 4){
        if(enable == 1){
            dataRegister2 = new DataRegister(dataBitSize);
            newActive[4] = 1;
        }else{
            newActive[4] = 0;
        }
        setActive();
    }

    void buildBcdToDecimal(){
        if(enable == 1){
            Bcd2Decimal = new BcdToDecimal;
            newActive[5] = 1;
        }else{
            newActive[5] = 0;
        }
        setActive();
    }

    void setupRotateRegister (int dataSize = 10)
    {

        if (enable == 1 && rotate_reg != NULL)
        {
            rotate_reg = new RotateRegister(dataSize);
            rotate_reg->setEnable (1);
            rotate_reg->setRotateEnable(1);
            rotate_reg->setRotateMode (rotateType::left);
            rotate_reg->setLoadEnable(1);
            rotate_reg->setData(0b1111111110);
            rotate_reg->doRegister();
            rotate_reg->setLoadEnable(0);
            setupActive[0] = 1;
        }else{
            setupActive[0] = 0;
        }
        setActive();
    }
    void setupDecimalToBcd(){
        if(enable == 1 && Decimal2Bcd != NULL){
            Decimal2Bcd->setEnable(1);
            setupActive[1] = 1;
        }else{
            setupActive[1] = 0;
        }
        setActive();
    }

    void setupDataRegister1(){
        if(enable == 1 && dataRegister1 != NULL){
            dataRegister1->setEnable(1);
            dataRegister1->setLoadEnable(1);
            dataRegister1->doResetQ();

            setupActive[2] = 1;
        }else{
            setupActive[2] = 0;
        }
        setActive();
    }

    void setupBcdAddSub( operationType operation){
        if(enable == 1 && bcdAddSub != NULL){

            bcdAddSub->setEnable(1);
            bcdAddSub->setDataA(1);
            bcdAddSub->setOperationMode(operation);
            bcdAddSub->setCarryIn(0);

            setupActive[3] = 1;
        }else{
            setupActive[3] = 0;
        }
        setActive();
    }

    void setupDataRegister2(){
        if(enable == 1 && dataRegister2 != NULL){
            dataRegister2->setEnable(1);
            dataRegister2->setLoadEnable(1);
            dataRegister2->doResetQ();

            setupActive[4] = 1;
        }else{
            setupActive[4] = 0;
        }
        setActive();
    }

    void setupBcdToDecimal(){
        if(enable == 1 && Bcd2Decimal != NULL){
            Bcd2Decimal->setEnable(1);
            setupActive[5] = 1;
        }else{
            setupActive[5] = 0;
        }
        setActive();
    }
    RotateRegister * getRotateRegister ()
    {
        if (enable == 1)
        {
            return this->rotate_reg;
        }
    }

    DecimalToBcd *getDecimalToBcd(){
        if(enable == 1){
            return Decimal2Bcd;
        }
    }
    DataRegister *getDataRegister1(){
        if(enable == 1){
            return dataRegister1;
        }
    }

    BcdAddSub *getBcdAddSub(){
        if(enable == 1){
            return bcdAddSub;
        }
    }
    DataRegister *getDataRegister2(){
        if(enable == 1){
            return dataRegister2;
        }
    }
    BcdToDecimal *getBcdToDecimal(){
        if(enable == 1){
            return Bcd2Decimal;
        }
    }
private:

    /*! Objetos lógicos da fábrica */
    RotateRegister *rotate_reg;
    DecimalToBcd *Decimal2Bcd;
    DataRegister *dataRegister1;
    BcdAddSub *bcdAddSub;
    DataRegister *dataRegister2;
    BcdToDecimal *Bcd2Decimal;

};


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_LOGICBUILDER_H_
