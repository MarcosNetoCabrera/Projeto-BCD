/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe abstrata do controlador de microsserviços.
 *
 * @file        Controller.h
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
 *              GNU General Public License (GNU GPLhttps://www.onlinegdb.com/edit/oYhejjmFd#_editor_4599625941).
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


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_CONTROLLER_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_CONTROLLER_H_


class Controller
{

  public:

    /*! Configuração do controlador */
    virtual void setup () = 0;

    /*! Entradas do controlador */
    virtual void readInputs () = 0;
  
    /*! Execução do controlador */
    virtual void selectMicroservice () = 0;
    virtual void doMicroservice () = 0;

    /*! Saídas do controlador */
    virtual void writeOutputs () = 0;

    /*! Acesso de interrupções */
    virtual void updateFromIntr () = 0;
//    virtual void readInputsfromInterrupt () = 0;

};  // class Controller.


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_CONTROLLER_H_
