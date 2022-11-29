/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe concreta de aritmética do somador/subtrator BCD.
 *
 * @file        bcdAddSub.h
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
 *              + NASCIMENTO, Miguel G. do. AnotaC'C5es de aula da disciplina de
 *                Eletrônica Digital II. Ufam, 2021.
 * *****************************************************************************
 */


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BINARY_ADDSUB_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BINARY_ADDSUB_H_


#include "Flow.h"


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa o somador/subtrator BCD.
 *
 *  @use      Sequência de uso dos serviços da classe.
 *
 *            ++ bcdAddSub       bcd;
 *
 *            ++ bcd.setEnable (enable);
 *            ++ bcd.setOperationMode (add);
 *
 *            ++ bcd.setDataA (dataA);
 *            ++ bcd.setDataB (dataB);
 *            ++ active = bcd.getActive ();
 *
 *            ++ bcd.setMode (add);
 *            ++ bcd.doArithmetic ();
 *
 *            ++ active = bcd.getActive ();
 *            ++ result = bcd.getResult ();
 *            ++ cout   = bcd.getCarryOut ();
 * -----------------------------------------------------------------------------
 */
class BcdAddSub : public Flow
{

public:

   BcdAddSub () : Flow (4)
  {

    /*! Zera as saídas */
    result   = 0;
    carryOut = 0;

  }


  /*! --------------------------------------------------------------------------
   *  @brief       Realiza a operação de adição/subtração.
   *  --------------------------------------------------------------------------
   */
  void doArithmetic () {
    // printf("enable %d active %d\n", enable, active);
    if ((enable == 1) && (active == 1))
    {
      /*! Comparação habilitada. */
      if (operationMode == operationType::add)
	  {
	    /*! Operação de adição selecionada. */
	    add ();
	  }
	  else
	  {
	    /*! Operação de subtração selecionada. */
		subtract ();
      }
    }
    else
    {
      /*! Somador/Subtrator desabilitado ou dado de entrada inválido */
      result   = 0;
      carryOut = 0;
      active   = 0;
    }

  }


  /*! --------------------------------------------------------------------------
   *  @brief       Realiza a soma de números BCDs não sinalizados.
   * ---------------------------------------------------------------------------
   */
  void add ()
  {
    /*! Resultado completo da adição. */
    unsigned int   buffer;

    /*! Adição com vem-um de entrada. */
    buffer = (dataA + dataB);

    /*! Ajusta as saídas da operação de adição. */
    result   = extractResult (buffer);
    // printf("result2 : %d\n", result);
    carryOut = extractCarryOut (buffer);
  }


  /*! --------------------------------------------------------------------------
   * @brief       Realiza a subtração de números BCDs não sinalizados.
   * ---------------------------------------------------------------------------
   */
  void subtract ()
  {
    /*! Resultado completo da subtração. */
    unsigned int   buffer;

    /*! Verifica se o resultado da subtração é negativo. */
	if (dataA < dataB)
	{
      /*! Subtração com resultado negativo. */
      buffer = -(dataA - dataB);
	}
	else
	{
      /*! Subtração com resultado positivo ou zero. */
      buffer = (dataA - dataB);
	}

    /*! Ajusta as saídas de dados e transporte */
    result   = extractResult (buffer);
    carryOut = extractBorrowOut (dataA, dataB);
  }


private:


  void doFlow ()
  {
    /*! Corpo vazio */
  }

  /*! --------------------------------------------------------------------------
   *  @brief      Verifica se dado fornecido é válido.
   *  --------------------------------------------------------------------------
   */
  bool isTheDataValid (int data)
  {
    bool   flag = false;

    if (isRange (data, 0, 9))
    {
      /*! O dado em Ascii é um número hexa */
      flag = true;
    
    }
    else 
    {
      /*! O dado em Ascii NÃO é um número hexa */
      flag = false;
    }

    return flag;
  }


  /*! --------------------------------------------------------------------------
   *  @brief      Extrai um grupo de últimos bits  do dado de entrada.
   *
   *              data   - Dado a ser extraído o grupo de bit.
   *
   *              number - Valor do número de bits do grupo.
   *
   *  @return     0..MAX,    valor do grupo de bits extraído do dado.
   *  --------------------------------------------------------------------------
   */
  int extractResult (int result)
  {
    /*! Resultado final. */
    int   res;
    // printf("result %d\n", result);
    if (result >= 10)
    {
      /*! Resultado de 10 a 15 */
      res = result - 10;
    }
    else
    {
      /*! Resultado de 0 a 9 */
      res = result;
    }
    
    return res;
  }


  /*! --------------------------------------------------------------------------
   *  @brief      Extrai o n-ésimo bit do dado de entrada.
   *
   *              data   - Dado a ser extraído o bit.
   *
   *              number - Valor do n-ésimo bit.
   *
   *  @return     0..1,    valor do bit extraído do dado.
   *  --------------------------------------------------------------------------
   */
  int extractCarryOut (int data)
  {
    /*! O bit de vai-um. */
    int   cout;

    if (data >= 10)
    {
      cout = 1;
    }
    else
    {
      cout = 0;
    }
   
    return cout;
  }
  
 
  /*! --------------------------------------------------------------------------
   *  @brief      Extrai o n-ésimo bit do dado de entrada.
   *  --------------------------------------------------------------------------
   */
  int extractBorrowOut (int a, int b)
  {
    /*! O bit de empresta-um */
    int   bout;

    if (b > a)
    {
      bout = 1;
    }
    else
    {
      bout = 0;
    }
   
    return bout;
  }
  
};


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BINARY_ADDSUB_H_
