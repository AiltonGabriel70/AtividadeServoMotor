CONTROLE DE SERVOMOTOR E LED RGB COM RASPBERRY PI PICO W

Este projeto demonstra o controle de um servomotor e LED RGB via PWM utilizando o Raspberry Pi Pico W no simulador Wokwi.

PRÉ-REQUISITOS

VS Code instalado (https://code.visualstudio.com/) com as extensões:

C/C++

CMake Tools

Wokwi for VS Code

Pico SDK configurado (siga o guia: https://github.com/raspberrypi/pico-sdk)



COMPORTAMENTO DO SISTEMA

Fase Inicial (15 segundos):

Servo move-se para 180° (LED brilhante) → 90° (LED médio) → 0° (LED apagado).

Cada posição é mantida por 5 segundos.

Movimento Contínuo:

Servo oscila suavemente entre 0° e 180°.

LED varia o brilho proporcionalmente à posição do servo (0° = apagado, 180° = brilhante).

CONFIGURAÇÕES TÉCNICAS

Servomotor (GPIO 22):

Frequência: 50 Hz (período de 20 ms).

Ciclo ativo: 500 µs (0°) a 2400 µs (180°).

LED RGB (GPIO 12):

Frequência: 1 kHz (período de 1 ms).

Brilho: 0% (0°) a 100% (180°).

ESTRUTURA DO PROJETO


OBSERVAÇÕES (BITDOGLAB)

O LED RGB altera seu brilho de acordo com a posição do servo.

Transições suaves são alcançadas com incrementos de 5 µs no sinal PWM.

Servo (Slice 3) e LED (Slice 6) operam em slices PWM independentes.



NOTAS IMPORTANTES

Projeto desenvolvido para o simulador Wokwi.

Em implementações físicas:

Verifique a corrente suportada pelo GPIO para o LED.

Utilize fonte externa para servomotores de alto torque.

Para contribuições ou dúvidas, acesse o repositório do projeto.

