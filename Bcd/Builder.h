/*! ****************************************************************************
 * @copyright   Miguel Grimm <miguelgrimm@gmail>
 *
 * @brief       Classe abstrata da fábrica de objetos.
 *
 * @file        Builder.h
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
 *                            +teacher    Miguel Grimm <miguelgrimm@gmail.com>
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
 *              + NASCIMENTO, Miguel G. do. Anotações de aula da disciplina
 *                de Arquitetura de Sistemas Digitais. Ufam, 2021.
 *              + NASCIMENTO, Miguel G. do. Anotações de aula da disciplina
 *                de Eletrônica Digital II. Ufam, 2021.
 * *****************************************************************************
 */


#ifndef C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BUILDER_H_
#define C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BUILDER_H_


class Builder
{


public:


    /*! Configuração da fábrica */
    Builder ()
    {
        /*! Configura as entradas da fábrica */
        enable       = 0;
        enableActive = 0;

        /*! Configura o controle da fábrica */
        activesDefault();
        setActive ();
    }


    /*! Entrada da fábrica */
    void setEnable (int enable)
    {
        if ((enable >= 0) && (enable <= 1))
        {
            /*! Ajusta a entrada de habilita */
            Builder::enable = enable;

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

    /*! Saída da fábrica */
    int getActive ()
    {
        return active;
    }

    void activesDefault(){
        for(int i = 0; i < 6; i++){
            Builder::newActive[i] = 0;
            Builder::setupActive[i] = 0;
        }
    }
    int getNewActive(int pos){
        return newActive[pos];
    }

    int getSetupActive(int pos){
        return setupActive[pos];
    }
protected:


    /*! Saída da fábrica */
    virtual void setActive ()
    {
        active = 1;
        for(int i = 0; i < 6; i++){
            if(newActive[i] != 1 || setupActive[i] != 1 || enableActive != 1){
                active = 0;
                break;
            }
        }
    }

    /*! Entrada da fábrica */
    int    enable;

    /*! Controles da fábrica */
    int    enableActive;
    int    newActive[6];
    int    setupActive[6];

    /*! Saída da fábrica */
    int    active;

};


#endif // C__USERS_MIGUELGRIMM_DESKTOP_CPPLINT_MASTER_BUILDER_H_
