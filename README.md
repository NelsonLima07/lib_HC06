# lib_HC06
Biblioteca de comandos e comunicacao para o modulo bluetooth HC-06


# Conceitos
Todas as funcoes dessa biblioteca iniciam com o prefixo J3_HC06


# Descricao das funcoes
 -> THC06* J3_HC06_new(UART_HandleTypeDef* _uart, char* _nome);
Retorna o ponteiro para o THC06



 -> bool J3_HC06_ini(THC06* _hc06);
Inicia o HC06, inclusive encontrando automaticamenteo boudRate


 -> bool J3_HC06_statusOK(THC06* _hc06);
Retorna se o status esta OK do HC06


 -> bool J3_HC06_setName(THC06* _hc06);
Altera o nome do dispositivo HC06

