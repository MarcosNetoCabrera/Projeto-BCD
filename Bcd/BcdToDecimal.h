/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe concreta da lógica do decodificador do código
 *              BCD (Binário codificado em Decimal) para o código decimal
 *
 * @file        Bcd2Decimal.h
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
 *                Arquitetura de Sistemas Digitais. Ufam, 2021
 *              + NASCIMENTO, Miguel G. do. Anotações de aula da disciplina de
 *                Eletrônica Digital II. Ufam, 2021
 * *****************************************************************************
 */


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BINARTOONEHOTE_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BINARTOONEHOTE_H_


#include "Converter.h"


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa a lógica do decodificador BCD para decimal.
 *
 *  @use      Sequência de uso dos serviços da classe.
 *
 *            ++ Bcd2Decimal  b2d (4);
 *
 *            ++ h2d.setEnable (1);
 *            ++ h2d.setOutLogic (logicType::positive)
 *            ++ h2d.setBCD (0);
 *            ++ active = h2d.getActive ();
 *
 *            ++ h2d.doDecoder ();
 *
 *            ++ decimal = h2d.getDecimal ();
 * -----------------------------------------------------------------------------
 */
class BcdToDecimal : public Converter
{

  public:

  /*! --------------------------------------------------------------------------
   *  @brief      Inicializa a lógica.
   *  --------------------------------------------------------------------------
   */
  BcdToDecimal (int dataBitSize = 10) : Converter (dataBitSize)
  {
    /*! Corpo vazio */
  }


  /*! --------------------------------------------------------------------------
   *  @brief       Guarda o valor da entrada da lógica.
   *  
   *  @param[in]   data  -  Valor do código BCD a ser decodificado.
   *  --------------------------------------------------------------------------
   */
  void setBCD (unsigned int data)
  {

    if (data <= 9)
    {
      /*! Guarda o valor de entrada */
      BcdToDecimal::data = data;
      
      dataActive = 1;
      setActive ();
    }
    else
    {
      /*! Limpa as saídas */
      result = 0;
      
      dataActive  = 0;
      setActive ();
    }

  }


  /*! --------------------------------------------------------------------------
   *  @brief       Realiza a lógica de decodificação de BCD para decimal.
   *  --------------------------------------------------------------------------
   */
  void doDecoder ()
  {

    if ((enable == 1) && (active == 1))
    {
      /*! Decodifica de BCD para decimal */
      result = pow (2, data);
    }
    else
    {
      result = 0;
      active = 0;
    }
  
  }



  /*! --------------------------------------------------------------------------
   *  @brief       Adquire o valor do resultado de saída da lógica.
   *  
   *  @return      decimal, O valor resultado da lógica ou
   *               0, caso a lógica esteja desabilitada.
   *  --------------------------------------------------------------------------
  */
  unsigned int getDecimal ()
  {
    unsigned int    dec;
  
    if (logic == logicType::positive)
    {
      /*! Somente um bit está em 1 */
      dec = result;
    }
    else
    {
      /*! Somente um bit está em 0 */
      dec = ~ result;
    }
  
    /*! Retorna o resultado da lógica */
    return dec;
  }


//private:

/*! Implementação dos métodos virtuais */
  void doEncoder ()
  {
    /*! Corpo vazio */
  }
  void doConverter ()
  {
    /*! Corpo vazio. */
  }


};


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BINARTOONEHOTE_H_
