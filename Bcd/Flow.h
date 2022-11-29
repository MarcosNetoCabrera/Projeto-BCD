/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe abstrata da lógica genérica de fluxo de dados.
 *
 *              Este arquivo pertence ao Ecossistema de Aprendizagem Acelerada 
 *              de sistemas embarcados com o uso da linguagem C++.
 *
 * @file        Flow.h
 * @version     1.0
 * @date        27 Julho 2021
 *
 * @section     HARDWARES & SOFTWARES.
 *              +compiler     GDB online - C++ 17
 *              +revisions    Versão (data): Descrição breve.
 *                            ++ 1.0 (27 Julho 2021): VersC#o inicial.
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


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_FLOW_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_FLOW_H_


#include <math.h>

enum class operationType : int
{
  add  =  0,
  sub  =  1
};



/*! ----------------------------------------------------------------------------
 *  @brief    A classe define a lógica genérico de operações aritméticas.
 * -----------------------------------------------------------------------------
 */
class Flow
{

public:

  Flow (int dataBitSize = 4)
  {
    /*! Configurações de lógica default */
    enable        = 1;
    dataA         = 0;
    dataB         = 0;
    carryIn       = 0;
    carryOut      = 0;
    operationMode = operationType::add;

    /*! Configurações de controle default */
    Flow::dataBitSize = dataBitSize;
    maximumData = pow (2, dataBitSize) - 1;
  
    /*! Ajusta saída de sinalização */
    sizeActive      = (dataBitSize <= sizeof(unsigned int)*8) ? 1 : 0;
    enableActive    = 1;
    dataAActive     = 1;
    dataBActive     = 1;
    operationActive = 1;
    carryInActive   = 1;
    setActive ();

    /*! Ajusta saída de dados */
    result   = 0;
    carryOut = 0;
  }


  /*! ----------------------------------------------------------------------------
   * @brief      Ajusta a entrada de habilitação das operações.
   *
   * @param[in]  enable   -  1, habilita todas as operações na classe e
   *                         0, desabilita em caso contrário.
   * -----------------------------------------------------------------------------
   */
  void setEnable (int enable)
  {

    /*! Ajusta a entrada enable */
    if ((enable >= 0) && (enable <= 1))
    {
      Flow::enable = enable;

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
   *  @brief       Guarda o dado A válido.
   *  
   *  @param[in]   dataA  -  Valor do dado A.
   *  --------------------------------------------------------------------------
   */
  void setDataA (int dataA)
  {
    if (isTheDataValid (dataA))
    {
      /*! Guarda o dado de entrada */
      Flow::dataA = dataA;
    
      /*! Ajusta a saída de sinalização */
      dataAActive = 1;
      setActive ();
    }
    else 
    {
      /* Lógica desabilitada ou valor inválido da entrada */
      dataAActive = 0;
      setActive ();
    }

  }


  /*! --------------------------------------------------------------------------
   *  @brief       Guarda o dado B válido.
   *  
   *  @param[in]   dataB  -  Valor do dado B.
   *  --------------------------------------------------------------------------
   */
  void setDataB (int dataB)
  {

    if (isTheDataValid (dataB))
    {
      /*! Guarda o dado de entrada */
      Flow::dataB = dataB;
    
      /*! Ajusta a saída de sinalização */
      dataBActive = 1;
      setActive ();
    }
    else 
    {
      /* Lógica desabilitada ou valor inválido da entrada */
      dataBActive = 0;
      setActive ();
    }
  }
  

  /*! --------------------------------------------------------------------------
   *  @brief      Ajusta o modo da operação aritmética.
   *
   *  @param[in]  countMode   -  Valor do mode de operação aritmética.
   * ---------------------------------------------------------------------------
   */
  void setOperationMode (operationType operation)
  {
    if ((operation >= operationType::add) && (operation <= operationType::sub))
    {
      /*! Ajusta o modo da operação aritmética. */
      operationMode = operation;
    
      /*! Ajusta a saída de sinalização. */
      operationActive = 1;
      Flow::setActive ();
    }
    else
    {
      /*! Ajusta a saída de sinalização. */
      operationActive = 0;
      Flow::setActive ();
    }
  } 


  /*! --------------------------------------------------------------------------
   *  @brief       Guarda o valor da entrada de vem-um de entrada.
   *  
   *  @param[in]   carryIn  -  0..1, valor do bit de vem-um.
   *  --------------------------------------------------------------------------
   */
  void setCarryIn (int carryIn)
  {

    if ((enable == 1) && (carryIn >= 0) && (carryIn <= 1))
    {
      /*! Guarda a entrada serial a */
      Flow::carryIn = carryIn;
    
      /*! Ajusta a saída de sinalização */
      carryInActive = 1;
      setActive ();
    }
  
    else
    {
      /* Lógica desabilitada ou valor inválido da entrada */
      carryInActive = 0;
      setActive ();
    }

  }


  /*! Execução da lógica */
  virtual void doFlow ()       = 0;
  virtual void doArithmetic () = 0;


  /*! --------------------------------------------------------------------------
   *  @brief      Adquire a saída de sinalização.
   *  --------------------------------------------------------------------------
   */
  int getActive ()
  {
    return active;
  }


  /*! --------------------------------------------------------------------------
   *  @brief      Adquire o valor do resultado da operação aritmética.
   *
   *  @return     0..dataBitSize-1, valor do resultado da operação aritmética.
   *  --------------------------------------------------------------------------
   */
  int getResult ()
  {
    return result;
  }


  /*! --------------------------------------------------------------------------
   *  @brief      Adquire o valor do bit de vai-um de saída.
   *
   *  @return     0..1, valor do bits de vai-um.
   *  --------------------------------------------------------------------------
   */
  int getCarryOut ()
  {

    /*! Acessa ao atributo protegido */
    return carryOut;

  }


protected:


  /*! --------------------------------------------------------------------------
   *  @brief       Verificação de dádo válido.
   *  --------------------------------------------------------------------------
   */
  virtual bool isTheDataValid (int data) = 0;


  /*! --------------------------------------------------------------------------
   * @brief      Verifica se um valor está na faixa.
   *  --------------------------------------------------------------------------
   */
  bool isRange (int data, int min, int max)
  {
    /*! Sinalização do código BCD simples. */
    bool  flag;

    if ((data >= min) && (data <= max))
    {
      /*! O valor fornecido está na faixa. */
	  flag = true;
    }
    else 
    {
	  /*! O valor fornecido NÃO está na faixa. */
      flag = false;
    }
 
    return flag;

  }


  /*! --------------------------------------------------------------------------
   *  @brief      Ajusta a saída de sinalizaçãoo.
   *  --------------------------------------------------------------------------
   */
  void setActive ()
  {
    //   printf("sizeActive %d enableActive %d dataAActive %d dataBActive %d operationActive %d carryInActive %d", 
    //   sizeActive, enableActive, dataAActive, dataBActive, operationActive, carryInActive);
      
    active = sizeActive & enableActive & dataAActive & dataBActive &
             operationActive & carryInActive;
  }

  /*! Entradas de lógica */
  int            enable;
  unsigned int   dataA, dataB;
  operationType  operationMode;
  int            carryIn, carryOut;

  /*! Controle da lógica */
  int            dataBitSize;
  int            maximumData;
    
  int            sizeActive;
  int            enableActive;
  int            dataAActive, dataBActive;
  int            operationActive;
  int            carryInActive;

  /*! Saídas da lógica */
  unsigned int   result;
  int            active;

};


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_FLOW_H_
