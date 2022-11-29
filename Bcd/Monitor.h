/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe concreta de controle dos microsserviços.
 *
 * @file        Monitor.h
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
 *                            +teacher	  Miguel Grimm <miguelgrimm@gmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer outra versao posterior.
 *
 *              Este programa C) distribução na esperança de que seja útil,
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


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_MONITOR_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_MONITOR_H_


#include <stdio.h>
#include "Controller.h"
#include "keyboard.h"
#include "Led.h"
#include "debugprint.h"
#include "BcdUs.h"


enum class usType : int
{
  powerUs = 1, 
  
  noUs = 0
};


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa o disposito de software Led no GDB online.
 *
 *  @use      Sequência de uso dos serviços da classe.
 *
 *            ++ Monitor           mon;
 *
 *            ++ led.turnOn ();
 *            ++ led.turnOff ();
 *            ++ led.toggler ();
 *            ++ led.emitsLight ();
 * -----------------------------------------------------------------------------
 */
class Monitor : public Controller
{


public:


  /*! --------------------------------------------------------------------------
   * @brief      Configura o monitor.
   * ---------------------------------------------------------------------------
   */
  Monitor ()
  {

    /*! Execução monitor */
    usNumber = usType::noUs;

  }


  /*! --------------------------------------------------------------------------
   * @brief      Ajusta o nome do led.
   * ---------------------------------------------------------------------------
   */
   void setup(){
       
       
    operationType op = getOperation(key);
    

    bcd_us = NULL;
    fac = NULL;
    fac = new LogicBuilder();
    
    fac->setEnable(1);

    fac->buildRotateRegister();
    fac->buildDecimalToBcd();
    fac->buildDataRegister1();
    fac->buildDataRegister2();
    fac->buildBcdToDecimal();
    fac->buildBcdAddSub();

    fac->setupRotateRegister();
    fac->setupDecimalToBcd();
    fac->setupDataRegister1();
    fac->setupDataRegister2();
    fac->setupBcdToDecimal();
    fac->setupBcdAddSub(op);

    
    bcd_us = new BcdUs();
    bcd_us->setRotateRegister(fac->getRotateRegister());
    bcd_us->setDecimalToBcd(fac->getDecimalToBcd());
    bcd_us->setDataRegister1(fac->getDataRegister1());
    bcd_us->setDataRegister2(fac->getDataRegister2());
    bcd_us->setBcdToDecimal(fac->getBcdToDecimal());
    bcd_us->setBcdAddSub(fac->getBcdAddSub());


    bcd_us->setStart(1);
  
  }
  
  void setupDevice (){
       /*! Entradas do dispositivo de software: botão */
    botton.setEnable (1);
    botton.clearKeyboard ();

    /*! Entradas do dispositivo de software: Screen */
    screen.setEnable(1);
    screen.clearScreen();
  }


  /*! --------------------------------------------------------------------------
   * @brief      Varrea as entradas de dispositivos lógicos.
   * ---------------------------------------------------------------------------
   */
  void readInputs (){
      
    /*! Execução do dipositivo de software */
    /*screen.printString(" -> ", "Opere o Microservico ['l'/'d']");
    screen.newLine();*/
    if(botton.isKeyPressed())
    {
        key = botton.readKey();
    }
 
        screen.newLine();
  }
 
 void readOperation(){
    if (key == 's')
    {
        
        botton.clearKeyboard();
        screen.printString("", "Selecione uma operação: 'a' para add || 's' para sub");
        screen.newLine();
        screen.printString("", "");
        screen.newLine();
        
        if(botton.isKeyPressed())
        {
            key = botton.readKey();
        }
    }
      
  }

  /*! --------------------------------------------------------------------------
   * @brief      Seleciona o microsserviço de maior prioridade a partir 
   *             das entradas ativadas,
   * ---------------------------------------------------------------------------
   */
  void selectMicroservice (){
    
   fflush(stdout);  
   screen.printString("", "Pressione 's' para iniciar o microsserviço");
   screen.newLine();  
   readInputs();
   switch (key)
    {
      case 's':  usNumber = usType::powerUs;
                 break;
      default:   usNumber = usType::noUs;
                 break;
    }
  }



  /*! --------------------------------------------------------------------------
   * @brief      Executa o microsserviço selecionado.
   * ---------------------------------------------------------------------------
   */

  void doMicroservice ()
  {
    switch (usNumber)
    {
      case usType::powerUs: bcd_us->doMicroservice();
                            break;

      default:              printf ("  + Nenhum microsserviço\n");
                            break;
    }
  }
  

  /*! --------------------------------------------------------------------------
   * @brief      Atualiza as saídas de dispositivo lógico.
   * ---------------------------------------------------------------------------
   */
   
   // printf("| gen : %d  | BCD : %d |  reg1 : %d |  bcd_addsub : %d  | reg2: %d |  Decimal : %d | state : %d |\n",
        //         gen, BCD, reg1, bcd_addsub, reg2, decimal, state);
   
  void writeOutputs ()
  {
    switch (usNumber)
    {
      case usType::powerUs: {
        
        screen.printBinary("| gen Decimal : ", bcd_us->getGen(), 10);
        bcd_us->printOutput();
        screen.printBinary("|  Decimal : ", bcd_us->getDecimal(),11);
        screen.newLine();
        
        break;
      }
                             
      default:            
        break;
    }
  }
  usType getUsNumber(){
      return usNumber;
  }
 
 /* void setMicroservice(BcdUs *ms){
      microservico = ms;
  }*/
  void doResetMicroservice(){
      bcd_us->doResetMicroservice();
  }
 
  void setStart(int start){
      bcd_us->setStart(start);
  }

  /*! --------------------------------------------------------------------------
   * @brief      Atualização da rotina de interrupção
   * ---------------------------------------------------------------------------
   */
  void updateFromIntr ()
  {
    /*! Corpo vazio */
  }


private:
 
 operationType getOperation(char key){
      if(key == 'a'){
          return operationType::add;
      }else if (key == 's'){
          return operationType::sub;
      }
  }


  LogicBuilder *fac;
  
  /*! Criação do microsserviço */
  BcdUs *bcd_us;
  
  /*! Criação estática dos dispositivos de software */
  Keyboard     botton;
  Led          led;
  DebugPrint   screen;
  
  /*! Saídas do dispositivo de software */
  char         key;
  
  /*! Execução de dispositivo */
  usType       usNumber;

};


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_MONITOR_H_
