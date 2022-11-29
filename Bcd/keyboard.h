/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe de impressão na tela no GDB online.
 *
 * @file        keyboard.h
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


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_KEYBOARD_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_KEYBOARD_H_


#include <stdio.h>
#include "conio.h"


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa a geração de uma cadeia com números binários.
 *
 *  @use      Sequência de uso dos serviçoos da classe.
 *
 *            ++ Keyboard    kb;
 *
 *            ++ kb.setEnable (enable);
 *            ++ kb.clearKeyboard ();
 *
 *            ++ keyPressed = kb.isKeyPressed ();
 *            ++ key = kb.readKey ();
 * -----------------------------------------------------------------------------
 */
class Keyboard
{

public:

  /*! --------------------------------------------------------------------------
   * @brief      Configura o dispositivo.
   * ---------------------------------------------------------------------------
   */
  Keyboard ()
  {

    /*! Entrada do dispositivo */
    enable  = 0;
  
    /*! Saídas do dispositivo */
    isKey   = 0;
    key     = 0;

  }


  /*! --------------------------------------------------------------------------
   * @brief      Habilitaçãoo das operações da lógica.
   *
   * @param[in]  enable   -  1, habilita todas as operações do dispositivo e
   *                         0, desabilita em caso contrário.
   * ---------------------------------------------------------------------------
   */
  void setEnable (int enable)
  {

    /*! Elimina os bits a esquerda do bit0 */
    Keyboard::enable = enable & 1;

  }



  /*! --------------------------------------------------------------------------
   * @brief      Limpa o buffer do teclado.
   * ---------------------------------------------------------------------------
   */
  void clearKeyboard()
  {
  
    /*! Limpa a fila FIFO do teclado */
    fflush (stdin);
  
  }


  /*! --------------------------------------------------------------------------
   * @brief      Verifica se alguma tecla foi pressionada.
   *
   * @return     1, se alguma tecla foi pressionada.
   *             0, em cao contrário.
   * ---------------------------------------------------------------------------
   */
  int isKeyPressed ()
  {

    isKey = kbhit ();
  
    isKey = (isKey == 0) ? 1 : 0;
 
    return isKey;
  
  }



  /*! --------------------------------------------------------------------------
   * @brief      Retira uma tecla do teclado, sem a necessidade do enter.
  *
   * @return     O código ASCII da tecla pressionada.
   * ---------------------------------------------------------------------------
   */
  char readKey ()
  {

    key = getch ();
  
    return key;
  
  }


private:

  /*! Entrada do dispositivo */
  int    enable;

  /*! Saídas do dispositivo */
  int    isKey;
  char   key;
};

#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_KEYBOARD_H_
