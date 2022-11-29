/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe concreta da lógica do codificador do código
 *              decimal para o código BCD.
 *
 * @file        Decimal2Bcd.h
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



#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_DECIMALTOBCD_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_DECIMALTOBCD_H_


#include "Converter.h"



/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa a lógica do codificador decimal para BCD.
 *
 *  @use      Sequência de uso dos serviços da classe.
 *
 *            ++ Decimal2Bcd    d2b;
 *
 *            ++ d2b.setEnable (enable);
 *            ++ d2b.setDecimal (data);
 *            ++ d2b.doEncoder ();
 *            ++ bcd = d2b.getDec ();
 * -----------------------------------------------------------------------------
 */
class DecimalToBcd : public Converter   //!< Herança.
{


public:


  /*! --------------------------------------------------------------------------
   *  @brief      Configura a lógica.
   *  --------------------------------------------------------------------------
   */
  DecimalToBcd (int dataBitSize = 10) : Converter (dataBitSize)
  {
    /*! Corpo vazio. */
    setInLogic(logicType::negative);
  }


  /*! --------------------------------------------------------------------------
   *  @brief       Guarda o valor da entrada da lógica.
   *  
   *  @param[in]   data  -  Valor do código decimal a ser codificado.
   *  --------------------------------------------------------------------------
   */
  void setDecimal (unsigned int data)
  {
    int   numOnes;
  
    /*! Tratamento da entrada decimal negativa */
    if (logic == logicType::negative)
    {
      data = ~ data;
    }

    /*! Verifica a entrada data é válida */
    numOnes = countTheNumberOfOnes (data);
    
    if ((data <= 0x200) && (numOnes == 1))
    {
      /*! Guarda o valor de entrada */
      Converter::data = data;
      
      dataActive = 1;
      setActive ();
    //   printf("active %d\n", active);
    }
    else
    {
      /*! Apaga as saídas da lógica */
      result = 0;
       
      dataActive = 0;
      setActive ();
    }

  }


  /*! --------------------------------------------------------------------------
   *  @brief       Realiza a lógica de codificação de decimal para BCD.
   *  --------------------------------------------------------------------------
   */
  void doEncoder () {
    // printf("enable %d active %d\n", enable, active);
    if ((enable == 1) && (active == 1))
    {
      /*! Codifica de decimal para BCD */
      result = findThePositionOfTheFirstBitToTheLeft (data);
    }
    else
    {
      result = 0;
      active = 0;
    }

  }


  /*! --------------------------------------------------------------------------
   *  @brief       Adquire o resultado de saída da lógica.
   *  
   *  @return      bcd, O valor resultado da lógica ou
   *               0, caso a lógica esteja desabilitada.
   *  --------------------------------------------------------------------------
   */
  unsigned int getBCD ()
  {
    /*! Retorna o valor da saída de resultado da lógica */
    return result;
  }


//private:


  void doDecoder ()
  {
    /*! Corpo vazio. */
  }
  void doConverter ()
  {
    /*! Corpo vazio. */
  }

};

#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_DECIMALTOBCD_H_
