/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe concreta lógica do registrador de rotação.
 *
 * @file        RotateRegister.h
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
 * 	                          +teacher    Miguel Grimm <miguelgrimm@gmail.com>
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
 *                Arquitetura de Sistemas Digitais. Ufam, 2021
 *              + NASCIMENTO, Miguel G. do. Anotações de aula da disciplina de
 *                Eletrônica Digital II. Ufam, 2021
 * *****************************************************************************
 */

#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_ROTATEREGISTER_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_ROTATEREGISTER_H_


#include "Register.h"


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa o registrador de rotação.
 *
 *  @use      Sequência de uso dos serviços da classe.
 *
 *            ++ ShiftRegister  reg (4);
 *
 *            ++ OPERAÇÃO DE CONFIGURAÇÃO.
 *            ++ reg.setEnable (1);
 *            ++ reg.setLoadEnable (0)
 *
 *            ++ OPERAÇÃO DE RESET/SET.
 *            ++ reg.doResetQ ();
 *            ++ reg.doSetQ ();
 *
 *            ++ OPERAÇÃO DE CARGA DE DADOS:
 *            ++ reg.setLoadEnable (1);
 *            ++ reg.setData (0);
 *            ++ active = reg.getActive ();
 *            ++ reg.doRegister ();
 *            ++ reg.setLoadEnable (0);
 *            ++ q = reg.getQ ();
 *
 *            ++ OPERAÇÃO DE DESLOCAMENTO PARA A DIREITA.
 *            ++ reg.setMode (rotateType::right);
 *            ++ reg.setRotatetEnable (1);
 *            ++ active = getActive ();
 *            ++ reg.doRegister ()
 *            ++ q = reg.getQ ();
 *            ++ serial = reg.getSerialOut ();
 * -----------------------------------------------------------------------------
 */
 
enum class rotateType : int
{
  right = 0,
  left  = 1
};


class RotateRegister : public Register
{
  
  public:
  
  /*! --------------------------------------------------------------------------
   *  @brief      Inicializa o registrador com o valor zero.
   *
   *  @param[in]  bitsLenth -  Número de bits do registrador.
   *  --------------------------------------------------------------------------
   */
  RotateRegister (int dataBitSize = 4) : Register (dataBitSize)
  {

    /*! Configura as entradas da lógica */
    rotateEnable = 1;
    rotateMode   = rotateType::left;

    /*! Configura os controle da lógica */
    maximumBit   = dataBitSize - 1;

    /*! Configura a saída da lógica */
    modeActive   = 1;
    RotateRegister::setActive ();

}


  /*! --------------------------------------------------------------------------
   *  @brief      Ajusta a entrada de habilita a carga.
   *
   *  @param[in]  rotateEnable  -  1, habilita a rotação da memória e
   *                               0, desabilita em caso contrário.
   * ---------------------------------------------------------------------------
   */
  void setRotateEnable (int rotateEnable)
  {

    if ((rotateEnable >= 0) && (rotateEnable <= 1))
    {
      /*! Ajusta a entrada shiftEnable */
      RotateRegister::rotateEnable = rotateEnable;
      
      /*! Ajusta a saída de sinalização */
      enableActive = 1;
      setActive ();
    }
    else
    {
      /*! Ajusta a saída de sinalização */
      enableActive = 0;
      setActive ();
    }

  }



  /*! --------------------------------------------------------------------------
   *  @brief      Ajusta o modo de rotação para a direita/esquerda.
   *
   *  @param[in]  rotateMode  -  rightRotate_e, rotação para a direita e
   *                             leftRotate_e, rotação para a esquerda.
   * ---------------------------------------------------------------------------
   */
  void setRotateMode (rotateType rotateMode = rotateType::right)
  {

    if (enable == 1)
    {
      if ((rotateMode >= rotateType::right) && (rotateMode <= rotateType::left))
      {
        /*! Ajusta o módulo de rotação */
        RotateRegister::rotateMode = rotateMode;

        /*! Ajusta a saída de sinalização */
        modeActive = 1;
        RotateRegister::setActive ();
      }
      else
      {
        /*! Ajusta a saída de sinalização */
        modeActive = 0;
        RotateRegister::setActive ();
      }
    }

  }


  /*! --------------------------------------------------------------------------
   *  @brief      Desloca de um bit o dado do registrador.
   *  --------------------------------------------------------------------------
   */
  void doRegister ()
 {

    if ((enable == 1) && (active == 1))
    {
      /*! reset é a entrada mais prioritária */
      if (loadEnable == 1)
      {
        /*! Modo carga */
        q = data;     
      }
      else if (rotateEnable == 1)
      {
        /*! Modo rotação */
        if (rotateMode == rotateType::right)
        {
          /*! Rotação para a direita */
          rightRotate ();
        }
        else
        {
          /*! Rotação para a esquerda */
          leftRotate ();
        }
      }
    }

  }


  /*! --------------------------------------------------------------------------
   *  @brief      Adquire o valor armazenado no registrador.
   *
   *  @return           -  Valor corrente armazenado.
   *  --------------------------------------------------------------------------
   */
  unsigned int getQ ()
  {
    /*! Valor armazenado */
    return q;
  }


  /*! --------------------------------------------------------------------------
   *  @brief      Adquire o bit de saC-da serial do registrador.
   *
   *  @return            -  Valor bit de saC-da serial do registrador.
   *  --------------------------------------------------------------------------
   */
  int getSerialOut ()
  {

    if (rotateMode == rotateType::right)
    {
      /*!  Adquire o bit menos significativo */
      serialOut = q & 1;
    }
    else
    {
      /*!  Adquire o bit mais significativo */
      serialOut = (q >> maximumBit) & 1;
    }
    return serialOut;

  }


private:


  /*! --------------------------------------------------------------------------
   *  @brief      Rotaciona de um bit o dado do registrador para a direita.
   *  --------------------------------------------------------------------------
   */
  void rightRotate ()
  {

    /*! Bit menos significativo */
    int lsb;

    /*! Adquire o bit menos significativo */
    lsb = q & 1;

    /*! Rotaciona o registrador para a direita de 1 bit */
    q = q >> 1;
    q = q | (lsb << maximumBit);

  }


  /*! --------------------------------------------------------------------------
   *  @brief      Rotaciona de um bit o dado do registrador para a esquerda.
   *  --------------------------------------------------------------------------
   */
  void leftRotate ()
  {

    /*! Bit mais significativo */
    int msb;

    /*! Adquire o bit mais significativo */
    msb = (q >> maximumBit) & 1;

    /*! Rotaciona o registrador para a direita de 1 bit */
    q = q << 1;
    q = q & maximumData;
    q = q | msb;

  }


  /*! --------------------------------------------------------------------------
   *  @brief      Ajusta a saída de sinalização.
   * ---------------------------------------------------------------------------
   */
  void setActive ()
  {

    /*! Ajusta a saída de sinalização */
    Register::setActive ();
    active &= modeActive;

  }


private:


  /*! ----------------------------------------------------------------------------
   *  @brief      Funções-membro vazias.
   * -----------------------------------------------------------------------------
   */
  void doCount ()
  {
    /*! Corpo vazio. */
  }
  void doFlipFlop ()
  {
    /*! Corpo vazio. */
  }


  /*! Entradas da lógica */
  int             rotateEnable;
  rotateType      rotateMode;

  /*! Controle da lógica */
  unsigned int    maximumBit;    //<! Valor máximo do registrador.

  int             modeActive;

  /*! Saída da lógica */
  int             serialOut;

};


#endif  // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_ROTATEREGISTER_H_
