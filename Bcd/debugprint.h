/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe de impressão na tela no GDB online.
 *
 * @file        debugprint.h
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
 *              versC#o 3 da licenC'a, ou qualquer outra versao posterior.
 *
 *              Este programa é distribução na esperança de que seja útil,
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


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_DEBUGPRINT_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_DEBUGPRINT_H_


#include <stdio.h>
#include <stdlib.h>
#include "conio.h"


/*! ----------------------------------------------------------------------------
 *  @brief    A classe implementa a geração de uma cadeia com números binários.
 *
 *  @use      Sequência de uso dos serviçoos da classe.
 *
 *            ++ DebugPrint    screen;
 *
 *            ++ screen.setEnable (enable);
 *            ++ screen.clearScreen ();
 *            ++ screen.newLine ();
 *
 *            ++ screen.printBinaty (prefixe, intNumber, bitsSize);
 *            ++ screen.printHexa (prefixe, intNumber, nibbleSize);
 *            ++ screen.printDecimal (prefixe, intNumber);
 *            ++ screen.printCharacter (prefixe, character);
 *            ++ screen.printString (prefixe, string);
 * -----------------------------------------------------------------------------
 */
class DebugPrint
{

public:
    // Mudanças posteriores
    enum class nCasas : int
    {
      n      = 0,
      uma    = 1,
      duas   = 2,
      tres   = 3,
      quatro = 4
    };
    // 


  /*! --------------------------------------------------------------------------
   * @brief      Inicializa o dispositivo e os atributos da classe.
   * ---------------------------------------------------------------------------
   */
  DebugPrint ()
  {

    enable = 0;

  }


  /*! --------------------------------------------------------------------------
   * @brief      Habilitação das operações da classe.
   *
   * @param[in]  enable   -  1, habilita todas as operações na classe e
   *                         0, desabilita em caso contrário e limpa as saídas.
   * ---------------------------------------------------------------------------
   */
  void setEnable (int enable)
  {

    DebugPrint::enable = enable & 1;

  }


  /*! --------------------------------------------------------------------------
   * @brief      Imprime números na base binária.
   *
   * @param[in]  prefixe      -  Cadeia a ser impressa antes do número binário.
   *
   *             intValue     -  Valor inteiro a ser convertido em binário.
   *
   *             binaryLenth  -  Número de bits a serem impressos.
   * ---------------------------------------------------------------------------
   */
  void printBinary (const char *prefixe, int intValue, int binarySize)
  {
    int    value;
    char   buffer [binarySize + 1];

    if (enable == 1)
    {
        
     for (int i = 0; i < binarySize; i++)
	  {
	    /*! Emina os bits a esquerda do bit 0 */
	    value = intValue & 0x01;
	   // printf("value : %d, intValue : %d\n", value, intValue);

	    /*! Converte do valor binário para o código ASCII */
	    buffer[binarySize - i - 1] = (value + '0');
        // printf("buffer : %s, value : %d\n", buffer,value);  
	    /*! Próximo bit do valor binário */
	    intValue = intValue >> 1;
	  }
      
      buffer[binarySize] = 0;

      printf ("%s%s ", prefixe, buffer);
    }
    fflush(stdout);

  }




  /*! --------------------------------------------------------------------------
   * @brief      Imprime nC:meros na base hexadecimal.
   *
   * @param[in]  prefixe     -  Cadeia a ser impressa antes do número hexadecimal.
   *
   *             intValue    -  Valor inteiro a ser convertido em hexadecimal.
   *
   *             binaryLenth -  Número de nibbles a serem impressos.
   * ---------------------------------------------------------------------------
   */
  void printHexa (const char *prefixe, int intValue, int nibbleSize)
  {

    int    value;
    char   buffer [nibbleSize + 1];

    if (enable == 1)
    {
      for (int i = 0; i < nibbleSize; i++)
	  {
	    /*! Elimina os bits a esquerda do nibble */
	    value = (intValue & 0x0F);

	    if (value <= 9)
	    {

	      /*! Converte do valor hexadecimal de 0 a 9 para o código ASCII */
	      buffer[nibbleSize - i - 1] = value + '0';
	    }
	    else
	    {
          /*! Converte do valor hexadecimal de 10 a 15 para o código ASCII */
	      buffer[nibbleSize - i - 1] = (value - 10) + 'A';

	    }  //!< if enable.

	    /*! Próximo nibble */
	    intValue = intValue >> 4;

	  }  //!< for nibbleLenth.

      buffer[nibbleSize] = 0;

      printf ("%s%s h", prefixe, buffer);
    }  //  //!< if enable.

  }


  /*! --------------------------------------------------------------------------
   * @brief      Imprime números na base decimal.
   *
   * @param[in]  prefixe   -  Cadeia a ser impressa antes do número decimal.
   *
   *             intValue  -  Valor inteiro a ser impresso.
   * ---------------------------------------------------------------------------
   */
  void printDecimal (const char *prefixe, int intValue, nCasas ncasas = nCasas::n)
  {
    if (enable == 1)
    {
      /* Imprime a string de prefixo e o valor decimal */
      
      if (ncasas == nCasas::n)           printf ("%s%d", prefixe, intValue);
      else if (ncasas == nCasas::uma)    printf ("%s%1d", prefixe, intValue);
      else if (ncasas == nCasas::duas)   printf ("%s%2d", prefixe, intValue);
      else if (ncasas == nCasas::tres)   printf ("%s%3d", prefixe, intValue);
      else if (ncasas == nCasas::quatro) printf ("%s%4d", prefixe, intValue);
    }

  }


  /*! --------------------------------------------------------------------------
   * @brief      Imprime um caractere.
   *
   * @param[in]    prefixe   -  Cadeia a ser impressa antes do número decimal.
   *
   *               character -  Caracter a ser impresso.
   * ---------------------------------------------------------------------------
   */
  void printCharacter (const char *prefixe, char character)
  {

    if (enable == 1)
    {
      /* Imprime a string de prefixo e o caractere */
      printf ("%s%c", prefixe, character);
    }

  }


  /*! --------------------------------------------------------------------------
   * @brief      Imprime um cadeia de caracteres.
   *
   * @param[in]    prefixe  -  Cadeia a ser impressa antes do número decimal.
   *
   *                string  -  Cadeia de caracteres a ser impressa.
   * ---------------------------------------------------------------------------
   */
  void printString (const char *prefixe, const char *string)
  {

    if (enable == 1)
    {
      /* Imprime as strings de prefixo e alvo */
      printf ("%s%s", prefixe, string);
    }

  }



  /*! --------------------------------------------------------------------------
   * @brief      Limpa a tela de impressão.
   * ---------------------------------------------------------------------------
   */
  void clearScreen ()
  {

    if (enable == 1)
    {
      /*! Limpa a tela */
      system ("clear||clr");
    }

  }




  /*! --------------------------------------------------------------------------
   * @brief      Pula para a próxima linha para a coluna de início.
   * ---------------------------------------------------------------------------
   */
  void newLine ()
  {

    if (enable == 1)
    {
      /*! Pula para a próxima linha e retorna o cursor para o início */
      printf ("\n\r");
    }

  }


private:


  /*! Entrada da lógica */
  int enable;

};


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_DEBUGPRINT_H_
