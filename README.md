CONTROLE DE SERVOMOTOR E LED RGB COM RASPBERRY PI PICO W

Este programa foi desenvolvido para controlar um servomotor e um LED RGB utilizando o Raspberry Pi Pico W, explorando o módulo PWM (Modulação por Largura de Pulso) do microcontrolador RP2040. O objetivo é simular o movimento angular do servo entre 0° e 180°, sincronizado com variações de brilho do LED, de forma didática e prática.

O código inicia configurando dois canais PWM independentes: um para o servomotor (conectado ao GPIO 22) e outro para o LED RGB (GPIO 12). Cada canal opera em um slice PWM diferente do RP2040, o que permite controle independente sem interferência. Para o servomotor, a frequência é definida em 50 Hz (período de 20 ms), padrão para servos, enquanto o LED utiliza 1 kHz (período de 1 ms) para evitar cintilação visível.

A configuração do PWM começa com o ajuste do clock divisor para 125, reduzindo a frequência do clock interno de 125 MHz para 1 MHz (1 µs por ciclo). Isso permite precisão no controle dos pulsos. Para o servo, o período de 20 ms é alcançado definindo o valor de wrap como 19999 (20.000 ciclos de 1 µs), enquanto o LED usa wrap 999 (1.000 ciclos de 1 µs) para seu período mais curto.

Na fase inicial, o programa executa uma sequência de movimentos pré-definidos:

Posição 180° (LED brilhante): O servo recebe um pulso de 2.400 µs (12% do período de 20 ms), e o LED é configurado para brilho máximo (999/999).

Posição 90° (LED médio): O pulso é ajustado para 1.470 µs (~7,35% do período), e o LED opera a ~50% de brilho.

Posição 0° (LED apagado): O pulso cai para 500 µs (2,5% do período), e o LED é desligado.
Cada posição é mantida por 5 segundos (sleep_ms(5000)), criando uma pausa observável.

Após essa sequência, o programa entra em um loop infinito de movimento suave. O servo oscila entre 0° e 180° com incrementos de 5 µs por passo, enquanto o LED varia seu brilho proporcionalmente. A relação entre a posição do servo e o brilho é calculada por um mapeamento linear: quando o pulso do servo varia de 500 µs (0°) a 2.400 µs (180°), o brilho do LED é ajustado de 0 a 999 usando a fórmula (pulse - 500) * 999 / 1900. Esse incremento gradual, combinado com um delay de 10 ms entre cada ajuste, cria uma transição suave tanto no movimento do servo quanto na iluminação do LED.

Um detalhe crítico é a independência dos slices PWM. O servo utiliza o Slice 3 (GPIO 22), e o LED o Slice 6 (GPIO 12), permitindo que operem em frequências diferentes sem conflitos. Essa arquitetura do RP2040 é essencial para projetos que exigem múltiplos dispositivos PWM.

No experimento com o BitDogLab, observa-se que o LED RGB responde instantaneamente às mudanças de posição do servo. Quando o servo está em 0°, o LED permanece apagado; conforme o servo avança para 180°, o brilho aumenta linearmente, atingindo o máximo na posição final. A ausência de cintilação no LED é garantida pela alta frequência de 1 kHz, imperceptível ao olho humano.

Para implementações físicas, é importante notar que servomotores consomem corrente significativa (até 300 mA em carga), exigindo circuitos de driver externos para proteger o GPIO do Pico. Já o LED RGB, se conectado diretamente, deve usar resistores limitadores de corrente (ex: 220 Ω) para evitar danos.

Em resumo, o programa demonstra conceitos fundamentais de PWM, temporização e controle de hardware, servindo como base para projetos mais complexos em automação e robótica. A integração entre servo e LED ilustra de forma prática como sistemas embarcados podem coordenar múltiplos componentes de maneira eficiente.




