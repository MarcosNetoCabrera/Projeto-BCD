/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe de dispositivo Led no GDB online.
 *
 * @file        led.h
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


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_LED_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_LED_H_


#include <string.h>
#include "debugprint.h"


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa o disposito de software Led no GDB online.
 *
 *  @use      Sequência de uso dos serviços da classe.
 *
 *            ++ Led           led (ledName);
 *
 *            ++ led.turnOn ();
 *            ++ led.turnOff ();
 *            ++ led.toggler ();
 *            ++ led.emitsLight ();
 * -----------------------------------------------------------------------------
 */
class Led
{

public:

  /*! --------------------------------------------------------------------------
   * @brief      Configura o led.
  * ---------------------------------------------------------------------------
   */
  Led ()
  {

    /*! Entrada de hardware */
    light.setEnable (1);

    /*! Execuções do dispositivo */
    name[0] = 0;
    state = 0;

  }


  /*! --------------------------------------------------------------------------
   * @brief      Ajusta o nome do led.
   * ---------------------------------------------------------------------------
   */
 void setName (const char * ledName)
  {

    /*! Ajusta o nome do led */
    strcpy (name, ledName);

  }


  /*! --------------------------------------------------------------------------
   * @brief      Liga o led para emitir brilho.
   * ---------------------------------------------------------------------------
   */
  void turnOn ()
  {

    /*! Liga o led */
    state = 1;

  }



  /*! --------------------------------------------------------------------------
   * @brief      Desliga o led para não emitir brilho.
   * ---------------------------------------------------------------------------
   */
  void turnOff ()
  {

    /*! Desliga o led */
    state = 0;

  }



  /*! --------------------------------------------------------------------------
   * @brief      Troca o estado do led.
   * ---------------------------------------------------------------------------
   */
  void toggler ()
  {

    /*! Troca o valor do led */
    state = state ^ 1;

  }


  /*! --------------------------------------------------------------------------
   * @brief      O led emite brilho ou não.
   * ---------------------------------------------------------------------------
   */
  void emitsLight ()
  {

    if (state == 1)
    {
      light.printString (name, ": ON");
    }
    else
    {
      light.printString (name, ": OFF");
    }

  }


private:

  /*! Definião de hardware */
  DebugPrint      light;
  
  /*! Entrada de dispositivo */
  char            name[10+1];
  
  /*! Execução de dispositivo */
  int             state;

};

#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_LED_H_
