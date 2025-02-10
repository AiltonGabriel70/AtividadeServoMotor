#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição dos pinos
#define SERVO_PIN 22    // PWM Slice 3 (GPIO 22)
#define LED_PIN 12      // PWM Slice 6 (GPIO 12)

int main() {
    // Configuração do PWM para o Servo (50Hz)
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint servo_slice = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_config servo_config = pwm_get_default_config();
    pwm_config_set_clkdiv(&servo_config, 125.0f);  // 1µs por ciclo (125MHz / 125 = 1MHz)
    pwm_config_set_wrap(&servo_config, 19999);     // Período de 20ms (50Hz)
    pwm_init(servo_slice, &servo_config, true);

    // Configuração do PWM para o LED (1KHz)
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint led_slice = pwm_gpio_to_slice_num(LED_PIN);
    pwm_config led_config = pwm_get_default_config();
    pwm_config_set_clkdiv(&led_config, 125.0f);    // 1µs por ciclo
    pwm_config_set_wrap(&led_config, 999);          // Período de 1ms (1KHz)
    pwm_init(led_slice, &led_config, true);

    // Sequência de posições do servo e brilho do LED
    while (true) {
        // Posição 180° (LED brilhante)
        pwm_set_gpio_level(SERVO_PIN, 2400);       // 2400µs
        pwm_set_gpio_level(LED_PIN, 999);           // 100% de brilho
        sleep_ms(5000);

        // Posição 90° (LED médio)
        pwm_set_gpio_level(SERVO_PIN, 1470);        // 1470µs
        pwm_set_gpio_level(LED_PIN, 500);           // ~50% de brilho
        sleep_ms(5000);

        // Posição 0° (LED apagado)
        pwm_set_gpio_level(SERVO_PIN, 500);         // 500µs
        pwm_set_gpio_level(LED_PIN, 0);              // 0% de brilho
        sleep_ms(5000);

        // Movimento suave com LED (0° → 180° → 0°)
        for (int pulse = 500; pulse <= 2400; pulse += 5) {
            pwm_set_gpio_level(SERVO_PIN, pulse);
            pwm_set_gpio_level(LED_PIN, (pulse - 500) * 999 / 1900); // Mapeamento linear
            sleep_ms(10);
        }
        for (int pulse = 2400; pulse >= 500; pulse -= 5) {
            pwm_set_gpio_level(SERVO_PIN, pulse);
            pwm_set_gpio_level(LED_PIN, (pulse - 500) * 999 / 1900);
            sleep_ms(10);
        }
    }

    return 0;
}