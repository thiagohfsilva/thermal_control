# Tarefas para Implementar o Thermal Control Firmware

Este arquivo organiza a implementação do firmware em cards no estilo JIRA.
Cada card possui contexto, user story, critérios de aceitação, notas técnicas e
pontos em aberto. A ordem dos cards deve ser seguida para reduzir retrabalho e
manter a arquitetura modular descrita no `README.md`.

## TASK-001 - Criar estrutura de pastas dos módulos

**Contexto:** O projeto precisa sair de uma base vazia para a organização modular descrita no `README.md`.

**User Story:** Como desenvolvedor do firmware, quero criar as pastas dos módulos para que o código fique separado por responsabilidade.

**Critérios de Aceitação:**
- A pasta `main/modules/` existe.
- As subpastas `app`, `control`, `drivers`, `sensors`, `thermal`, `safety`, `logger`, `communication` e `common` existem.

**Notas Técnicas:**
- Siga exatamente a estrutura indicada na seção "Estrutura do Projeto" do `README.md`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-002 - Criar o arquivo principal `main.c`

**Contexto:** O ESP-IDF precisa de um ponto de entrada da aplicação dentro do componente `main`.

**User Story:** Como desenvolvedor do firmware, quero criar `main/main.c` para ter o ponto inicial de execução do sistema.

**Critérios de Aceitação:**
- O arquivo `main/main.c` existe.
- O arquivo declara a função `app_main()`.

**Notas Técnicas:**
- Em projetos ESP-IDF, a função de entrada é `void app_main(void)`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-003 - Chamar `app_init()` no `app_main()`

**Contexto:** O `main.c` deve permanecer simples e delegar a inicialização para o módulo de aplicação.

**User Story:** Como desenvolvedor do firmware, quero que `app_main()` chame apenas `app_init()` para evitar regra de negócio no ponto de entrada.

**Critérios de Aceitação:**
- `app_main()` chama `app_init()`.
- `main.c` inclui apenas os headers necessários para essa chamada.

**Notas Técnicas:**
- O header esperado é `modules/app/app.h`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-004 - Atualizar `main/CMakeLists.txt`

**Contexto:** O CMake precisa conhecer os arquivos C criados para compilar o firmware.

**User Story:** Como desenvolvedor do firmware, quero atualizar o CMake para que todos os módulos sejam compilados pelo ESP-IDF.

**Critérios de Aceitação:**
- `main/main.c` está listado nos fontes do componente.
- Os arquivos `.c` dos módulos estão listados ou coletados de forma clara.

**Notas Técnicas:**
- Prefira uma lista explícita de fontes no início do projeto para facilitar revisão por iniciantes.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-005 - Criar `.clang-format`

**Contexto:** O projeto exige código formatado de forma padronizada.

**User Story:** Como desenvolvedor do firmware, quero criar `.clang-format` para garantir estilo consistente em todos os arquivos C e headers.

**Critérios de Aceitação:**
- O arquivo `.clang-format` existe na raiz.
- O conteúdo segue a configuração indicada no `README.md`.

**Notas Técnicas:**
- Não invente outro estilo; copie a configuração documentada.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-006 - Garantir build inicial simples

**Contexto:** Antes de adicionar lógica complexa, a base do projeto deve compilar.

**User Story:** Como desenvolvedor do firmware, quero validar uma build inicial para detectar problemas estruturais cedo.

**Critérios de Aceitação:**
- O comando de build do ESP-IDF executa sem erro de CMake.
- A falha, se existir, está documentada com causa clara.

**Notas Técnicas:**
- Use `idf.py build` dentro do ambiente configurado do ESP-IDF.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-007 - Criar `types.h`

**Contexto:** Módulos diferentes precisarão compartilhar estados e tipos comuns.

**User Story:** Como desenvolvedor do firmware, quero criar `types.h` para centralizar tipos usados por mais de um módulo.

**Critérios de Aceitação:**
- O arquivo `main/modules/common/types.h` existe.
- O arquivo possui include guard ou `#pragma once`.

**Notas Técnicas:**
- Não coloque configuração de hardware neste arquivo; use `config.h` para isso.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-008 - Definir estados da aplicação

**Contexto:** A aplicação precisa representar fases como inicialização, execução e falha.

**User Story:** Como desenvolvedor do firmware, quero um enum de estados da aplicação para padronizar decisões entre módulos.

**Critérios de Aceitação:**
- Existe um enum com estados `init`, `running`, `fault` e `shutdown`.
- O enum fica em `types.h`.

**Notas Técnicas:**
- Use nomes claros, por exemplo `app_state_t`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-009 - Definir estados de segurança

**Contexto:** O sistema precisa diferenciar operação normal de falhas térmicas ou de sensor.

**User Story:** Como desenvolvedor do firmware, quero um enum de segurança para que falhas sejam comunicadas de forma padronizada.

**Critérios de Aceitação:**
- Existe um enum com estados `ok`, `sensor_error` e `overtemperature`.
- O enum fica disponível para `safety`, `thermal` e `app`.

**Notas Técnicas:**
- Use nomes consistentes, por exemplo `safety_state_t`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-010 - Criar struct de status do sistema

**Contexto:** Logger, comunicação e aplicação precisam consultar dados atuais do controle térmico.

**User Story:** Como desenvolvedor do firmware, quero uma struct de status para transportar dados importantes do sistema.

**Critérios de Aceitação:**
- A struct contém temperatura atual, setpoint, duty cycle e estado atual.
- A struct fica em `types.h`.

**Notas Técnicas:**
- Use `float` para temperatura, setpoint e duty cycle.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-011 - Criar `defines.h`

**Contexto:** Constantes gerais ajudam a evitar números mágicos espalhados pelo código.

**User Story:** Como desenvolvedor do firmware, quero criar `defines.h` para guardar limites e macros genéricas do firmware.

**Critérios de Aceitação:**
- O arquivo `main/modules/common/defines.h` existe.
- O arquivo possui include guard ou `#pragma once`.

**Notas Técnicas:**
- Use este arquivo apenas para constantes genéricas, não para pinos ou canais de hardware.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-012 - Criar `config.h`

**Contexto:** O firmware deve permitir trocar pinos e parâmetros sem alterar lógica dos módulos.

**User Story:** Como desenvolvedor do firmware, quero criar `config.h` para centralizar configurações do hardware e do controle.

**Critérios de Aceitação:**
- O arquivo `main/modules/common/config.h` existe.
- O arquivo possui include guard ou `#pragma once`.

**Notas Técnicas:**
- Este é o ponto principal para parametrizar ESP32 DevKit e possíveis placas futuras.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-013 - Definir canal ADC do NTC

**Contexto:** O sensor NTC será lido por uma entrada ADC configurável.

**User Story:** Como desenvolvedor do firmware, quero configurar o canal ADC em um único lugar para facilitar mudança de placa.

**Critérios de Aceitação:**
- `config.h` possui uma definição para o canal ADC do NTC.
- Nenhum módulo usa canal ADC fixo diretamente no código.

**Notas Técnicas:**
- Use nomes descritivos, como `THERMAL_NTC_ADC_CHANNEL`.

**Pontos em Aberto / Definição:** Definir o canal real antes do teste em bancada.

## TASK-014 - Definir pino PWM do atuador

**Contexto:** O controle térmico acionará um atuador usando PWM.

**User Story:** Como desenvolvedor do firmware, quero configurar o pino PWM em `config.h` para trocar o hardware sem mexer na lógica.

**Critérios de Aceitação:**
- `config.h` possui uma definição para o pino PWM.
- O driver PWM usa essa definição.

**Notas Técnicas:**
- Use um nome como `THERMAL_PWM_GPIO`.

**Pontos em Aberto / Definição:** Definir o pino real antes do teste em bancada.

## TASK-015 - Definir frequência e resolução do PWM

**Contexto:** A saída PWM precisa de frequência e resolução adequadas ao atuador térmico.

**User Story:** Como desenvolvedor do firmware, quero configurar frequência e resolução do PWM para controlar a potência aplicada.

**Critérios de Aceitação:**
- `config.h` define frequência do PWM.
- `config.h` define resolução do duty cycle.

**Notas Técnicas:**
- Use valores iniciais seguros e fáceis de alterar, sem espalhar números no driver.

**Pontos em Aberto / Definição:** Confirmar frequência ideal conforme o atuador usado.

## TASK-016 - Definir período da task térmica

**Contexto:** O controle em malha fechada precisa executar em intervalo fixo.

**User Story:** Como desenvolvedor do firmware, quero configurar o período da task térmica para manter execução determinística.

**Critérios de Aceitação:**
- `config.h` possui uma definição para o período de controle.
- A task térmica usa essa definição.

**Notas Técnicas:**
- Use milissegundos como unidade para facilitar leitura.

**Pontos em Aberto / Definição:** Confirmar o período ideal após testes com o sistema físico.

## TASK-017 - Definir limites seguros de temperatura

**Contexto:** O sistema deve desligar ou bloquear saída quando a temperatura sair da faixa segura.

**User Story:** Como desenvolvedor do firmware, quero configurar limites térmicos para proteger o hardware e o usuário.

**Critérios de Aceitação:**
- `config.h` define temperatura mínima segura.
- `config.h` define temperatura máxima segura.

**Notas Técnicas:**
- Esses valores serão usados pelo módulo `safety`.

**Pontos em Aberto / Definição:** Definir limites finais conforme aplicação e hardware.

## TASK-018 - Centralizar configurações de hardware

**Contexto:** Configuração espalhada dificulta manutenção e troca de microcontrolador.

**User Story:** Como desenvolvedor do firmware, quero manter configurações de hardware em `config.h` ou Kconfig para facilitar portabilidade.

**Critérios de Aceitação:**
- Pinos, canais e parâmetros de hardware não aparecem fixos nos módulos.
- O código referencia constantes de configuração.

**Notas Técnicas:**
- Revise principalmente drivers e sensor NTC.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-019 - Criar driver ADC

**Contexto:** O acesso ao ADC deve ficar isolado em um driver para não acoplar sensores ao ESP-IDF.

**User Story:** Como desenvolvedor do firmware, quero criar `adc_drv` para encapsular a leitura analógica.

**Critérios de Aceitação:**
- Existem `main/modules/drivers/adc_drv.c` e `adc_drv.h`.
- O header expõe as funções públicas do driver.

**Notas Técnicas:**
- O sensor NTC deve chamar o driver, não APIs do ESP-IDF diretamente.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-020 - Implementar inicialização do ADC

**Contexto:** Antes de ler o NTC, o ADC precisa ser configurado corretamente.

**User Story:** Como desenvolvedor do firmware, quero implementar `adc_drv_init()` para preparar o ADC do ESP-IDF.

**Critérios de Aceitação:**
- `adc_drv_init()` configura canal, atenuação e resolução.
- A função retorna sucesso ou erro.

**Notas Técnicas:**
- Use o driver ADC compatível com a versão do ESP-IDF do projeto.

**Pontos em Aberto / Definição:** Confirmar versão do ESP-IDF usada no devcontainer.

## TASK-021 - Implementar leitura bruta do ADC

**Contexto:** O sensor NTC precisa receber uma amostra ADC bruta antes de converter para temperatura.

**User Story:** Como desenvolvedor do firmware, quero implementar `adc_drv_read_raw()` para obter a leitura do canal configurado.

**Critérios de Aceitação:**
- A função retorna o valor bruto do ADC.
- A função informa erro quando a leitura falhar.

**Notas Técnicas:**
- Evite retornar apenas `int` sem indicar se houve erro.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-022 - Tratar erro de leitura ADC

**Contexto:** Falhas de ADC não podem ser confundidas com temperatura válida.

**User Story:** Como desenvolvedor do firmware, quero tratar erro de leitura ADC para que o sistema entre em segurança quando necessário.

**Critérios de Aceitação:**
- Erros do ESP-IDF são convertidos para um retorno claro do driver.
- O chamador consegue diferenciar leitura válida de falha.

**Notas Técnicas:**
- Use `esp_err_t` ou uma enum própria, mas mantenha o contrato simples.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-023 - Criar driver PWM

**Contexto:** O atuador térmico deve ser controlado por uma abstração de PWM.

**User Story:** Como desenvolvedor do firmware, quero criar `pwm_drv` para encapsular o periférico LEDC.

**Critérios de Aceitação:**
- Existem `main/modules/drivers/pwm_drv.c` e `pwm_drv.h`.
- O header expõe inicialização e ajuste de duty cycle.

**Notas Técnicas:**
- Módulos de controle não devem chamar LEDC diretamente.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-024 - Inicializar PWM com LEDC

**Contexto:** O ESP32 usa o periférico LEDC para gerar PWM.

**User Story:** Como desenvolvedor do firmware, quero implementar `pwm_drv_init()` para preparar a saída PWM.

**Critérios de Aceitação:**
- A função configura timer, canal, frequência, resolução e GPIO.
- A função inicia a saída em 0% de duty.

**Notas Técnicas:**
- Use os valores definidos em `config.h`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-025 - Implementar ajuste de duty cycle

**Contexto:** O controle térmico precisa aplicar uma potência calculada ao atuador.

**User Story:** Como desenvolvedor do firmware, quero implementar `pwm_drv_set_duty(float duty_percent)` para controlar a saída.

**Critérios de Aceitação:**
- A função aceita valores em porcentagem.
- A função atualiza o LEDC com o duty correspondente.

**Notas Técnicas:**
- Converta 0 a 100% para a escala da resolução configurada.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-026 - Limitar duty cycle no driver PWM

**Contexto:** Valores inválidos de duty não devem gerar comportamento inesperado no hardware.

**User Story:** Como desenvolvedor do firmware, quero limitar o duty cycle para proteger a saída PWM.

**Critérios de Aceitação:**
- Valores menores que 0% viram 0%.
- Valores maiores que 100% viram 100%.

**Notas Técnicas:**
- Mesmo que o controle já limite a saída, o driver deve ser defensivo.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-027 - Criar driver GPIO

**Contexto:** O projeto pode precisar de GPIOs auxiliares para enable, fault ou status.

**User Story:** Como desenvolvedor do firmware, quero criar `gpio_drv` para centralizar configuração de GPIOs digitais.

**Critérios de Aceitação:**
- Existem `main/modules/drivers/gpio_drv.c` e `gpio_drv.h`.
- O header define funções públicas simples para GPIOs auxiliares.

**Notas Técnicas:**
- Não misture funções de PWM ou ADC neste driver.

**Pontos em Aberto / Definição:** Definir quais GPIOs auxiliares serão usados no hardware final.

## TASK-028 - Implementar GPIOs auxiliares

**Contexto:** Sinais digitais ajudam a habilitar atuadores ou indicar falhas.

**User Story:** Como desenvolvedor do firmware, quero configurar GPIOs auxiliares para apoiar operação e diagnóstico.

**Critérios de Aceitação:**
- GPIOs configurados usam definições de `config.h`.
- Há funções para ligar, desligar ou alterar estado quando necessário.

**Notas Técnicas:**
- Comece com funções simples e evite acoplar o driver a regras de negócio.

**Pontos em Aberto / Definição:** Confirmar necessidade de pino enable, fault ou LED de status.

## TASK-029 - Revisar dependências dos drivers

**Contexto:** Drivers são a camada mais baixa do projeto e não devem depender de módulos superiores.

**User Story:** Como desenvolvedor do firmware, quero garantir que drivers não chamem aplicação, controle ou segurança.

**Critérios de Aceitação:**
- Drivers incluem apenas headers de configuração, tipos básicos e ESP-IDF.
- Não há include de `app`, `thermal`, `control` ou `safety` dentro de `drivers`.

**Notas Técnicas:**
- Essa revisão evita dependência circular.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-030 - Criar módulo NTC

**Contexto:** A conversão de ADC para temperatura deve ficar isolada no módulo de sensor.

**User Story:** Como desenvolvedor do firmware, quero criar `ntc_sensor` para transformar leitura analógica em temperatura.

**Critérios de Aceitação:**
- Existem `main/modules/sensors/ntc_sensor.c` e `ntc_sensor.h`.
- O header expõe inicialização e leitura de temperatura.

**Notas Técnicas:**
- Este módulo deve usar `adc_drv`, não APIs ADC diretamente.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-031 - Inicializar sensor NTC

**Contexto:** O sensor depende do ADC para funcionar.

**User Story:** Como desenvolvedor do firmware, quero implementar `ntc_sensor_init()` para preparar a cadeia de leitura de temperatura.

**Critérios de Aceitação:**
- `ntc_sensor_init()` chama a inicialização necessária do ADC.
- A função retorna erro se a inicialização falhar.

**Notas Técnicas:**
- Evite inicializar o mesmo recurso várias vezes sem controle.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-032 - Configurar parâmetros do NTC

**Contexto:** A conversão de resistência para temperatura depende das características do NTC.

**User Story:** Como desenvolvedor do firmware, quero definir parâmetros do NTC para calcular temperatura corretamente.

**Critérios de Aceitação:**
- `config.h` contém resistência nominal do NTC.
- `config.h` contém o valor beta do NTC.

**Notas Técnicas:**
- Use valores iniciais comuns, mas deixe claro que devem ser conferidos no datasheet.

**Pontos em Aberto / Definição:** Confirmar modelo e datasheet do NTC real.

## TASK-033 - Configurar resistor de referência

**Contexto:** O divisor de tensão do NTC precisa do valor do resistor fixo para calcular resistência.

**User Story:** Como desenvolvedor do firmware, quero configurar o resistor de referência para converter tensão em resistência.

**Critérios de Aceitação:**
- `config.h` contém o valor do resistor de referência.
- A conversão do NTC usa essa constante.

**Notas Técnicas:**
- Use ohms como unidade para evitar conversões escondidas.

**Pontos em Aberto / Definição:** Medir ou confirmar o resistor usado no circuito.

## TASK-034 - Converter ADC bruto em tensão

**Contexto:** A primeira etapa física da leitura é transformar contagem ADC em tensão.

**User Story:** Como desenvolvedor do firmware, quero converter leitura ADC bruta em tensão para calcular a resistência do NTC.

**Critérios de Aceitação:**
- Existe uma função ou bloco claro para converter raw ADC em volts.
- A conversão usa resolução e referência configuradas.

**Notas Técnicas:**
- Documente a unidade retornada pela função.

**Pontos em Aberto / Definição:** Confirmar referência/calibração ADC usada no ESP-IDF.

## TASK-035 - Converter tensão em resistência

**Contexto:** O cálculo de temperatura usa a resistência estimada do NTC.

**User Story:** Como desenvolvedor do firmware, quero converter tensão em resistência para alimentar a equação do NTC.

**Critérios de Aceitação:**
- A resistência calculada está em ohms.
- Casos de divisão por zero são evitados.

**Notas Técnicas:**
- Deixe claro no código se o NTC fica ligado ao VCC ou ao GND no divisor.

**Pontos em Aberto / Definição:** Confirmar topologia real do divisor de tensão.

## TASK-036 - Converter resistência em temperatura Celsius

**Contexto:** O controle térmico trabalha com temperatura em graus Celsius.

**User Story:** Como desenvolvedor do firmware, quero converter resistência do NTC em Celsius para usar no controle e nos logs.

**Critérios de Aceitação:**
- A função retorna temperatura em graus Celsius.
- A fórmula usa os parâmetros configurados do NTC.

**Notas Técnicas:**
- A equação beta é suficiente para a primeira versão.

**Pontos em Aberto / Definição:** Confirmar se a aplicação exige tabela Steinhart-Hart no futuro.

## TASK-037 - Validar leituras ADC impossíveis

**Contexto:** Valores extremos do ADC podem indicar sensor desconectado, curto ou erro elétrico.

**User Story:** Como desenvolvedor do firmware, quero rejeitar leituras impossíveis para não controlar com temperatura falsa.

**Critérios de Aceitação:**
- Leitura ADC zerada é tratada como inválida quando aplicável.
- Leitura ADC saturada é tratada como inválida quando aplicável.

**Notas Técnicas:**
- A decisão final depende da topologia do divisor do NTC.

**Pontos em Aberto / Definição:** Confirmar quais extremos indicam aberto ou curto no circuito real.

## TASK-038 - Retornar erro para sensor desconectado ou em curto

**Contexto:** O módulo de segurança precisa saber quando a leitura do sensor não é confiável.

**User Story:** Como desenvolvedor do firmware, quero retornar erro de sensor para acionar proteção térmica.

**Critérios de Aceitação:**
- A API do NTC diferencia temperatura válida de falha.
- Curto e desconexão geram retorno de erro.

**Notas Técnicas:**
- Não use temperatura mágica, como `-999`, para indicar erro.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-039 - Criar módulo de filtro

**Contexto:** Leituras ADC podem ter ruído e causar variação indesejada no controle.

**User Story:** Como desenvolvedor do firmware, quero criar `filter` para suavizar a temperatura antes do PID.

**Critérios de Aceitação:**
- Existem `main/modules/control/filter.c` e `filter.h`.
- O header expõe inicialização, atualização e reset do filtro.

**Notas Técnicas:**
- O filtro deve ser passivo e não criar task.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-040 - Implementar filtro exponencial

**Contexto:** Um filtro exponencial é simples, barato e suficiente para reduzir ruído inicial.

**User Story:** Como desenvolvedor do firmware, quero implementar filtro exponencial para suavizar a temperatura medida.

**Critérios de Aceitação:**
- A função recebe uma nova amostra e retorna valor filtrado.
- O fator de suavização é configurável.

**Notas Técnicas:**
- Use a forma `filtered = alpha * sample + (1 - alpha) * previous`.

**Pontos em Aberto / Definição:** Ajustar `alpha` após observar ruído em bancada.

## TASK-041 - Implementar reset do filtro

**Contexto:** O filtro precisa iniciar de um estado conhecido para evitar valores antigos ou lixo de memória.

**User Story:** Como desenvolvedor do firmware, quero resetar o filtro para uma temperatura inicial conhecida.

**Critérios de Aceitação:**
- Existe uma função de reset.
- Após reset, a próxima saída do filtro é previsível.

**Notas Técnicas:**
- Use reset ao inicializar e quando sair de uma falha, se fizer sentido.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-042 - Criar módulo PID

**Contexto:** O PID será o algoritmo principal de controle em malha fechada.

**User Story:** Como desenvolvedor do firmware, quero criar `pid` para calcular a saída de controle a partir do erro de temperatura.

**Critérios de Aceitação:**
- Existem `main/modules/control/pid.c` e `pid.h`.
- O header expõe funções para inicializar, resetar e atualizar o PID.

**Notas Técnicas:**
- O módulo PID não deve conhecer PWM, ADC ou FreeRTOS.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-043 - Criar struct de configuração do PID

**Contexto:** Ganhos e limites precisam ser agrupados para facilitar configuração e testes.

**User Story:** Como desenvolvedor do firmware, quero uma struct do PID para organizar parâmetros e estado interno.

**Critérios de Aceitação:**
- A struct contém `kp`, `ki`, `kd`.
- A struct contém limites mínimo e máximo de saída.

**Notas Técnicas:**
- Separe configuração fixa de estado interno se isso deixar o código mais claro.

**Pontos em Aberto / Definição:** Definir ganhos iniciais em bancada.

## TASK-044 - Implementar inicialização do PID

**Contexto:** O PID precisa começar com ganhos definidos e estado interno zerado.

**User Story:** Como desenvolvedor do firmware, quero implementar `pid_init()` para preparar o controlador.

**Critérios de Aceitação:**
- `pid_init()` valida parâmetros básicos.
- Integral, derivada e erro anterior começam em estado conhecido.

**Notas Técnicas:**
- Evite aceitar limite máximo menor que limite mínimo.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-045 - Implementar reset do PID

**Contexto:** Ao entrar em falha ou reiniciar controle, o PID não deve manter integral antiga.

**User Story:** Como desenvolvedor do firmware, quero implementar `pid_reset()` para limpar memória interna do controlador.

**Critérios de Aceitação:**
- A integral é zerada.
- O erro anterior e a derivada são reiniciados.

**Notas Técnicas:**
- Chame reset quando o controle for desabilitado por segurança.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-046 - Implementar atualização do PID

**Contexto:** A cada ciclo térmico, o controlador precisa calcular uma nova saída.

**User Story:** Como desenvolvedor do firmware, quero implementar `pid_update()` para calcular duty cycle a partir de setpoint e temperatura.

**Critérios de Aceitação:**
- A função recebe setpoint, temperatura atual e período.
- A função retorna uma saída numérica limitada.

**Notas Técnicas:**
- Use o período em segundos ou milissegundos, mas documente a unidade.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-047 - Aplicar anti-windup no PID

**Contexto:** A integral pode crescer demais quando a saída fica saturada.

**User Story:** Como desenvolvedor do firmware, quero implementar anti-windup para evitar recuperação lenta ou instável do controle.

**Critérios de Aceitação:**
- A integral não cresce indefinidamente.
- A saída saturada não causa acúmulo excessivo de erro integral.

**Notas Técnicas:**
- Uma abordagem simples é limitar a integral ou condicionar sua atualização.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-048 - Limitar saída do PID

**Contexto:** A saída do PID será usada como duty cycle e precisa respeitar limites físicos.

**User Story:** Como desenvolvedor do firmware, quero limitar a saída do PID para manter o atuador em faixa segura.

**Critérios de Aceitação:**
- Saída abaixo do mínimo é limitada ao mínimo.
- Saída acima do máximo é limitada ao máximo.

**Notas Técnicas:**
- Para PWM, os limites iniciais esperados são 0% e 100%.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-049 - Criar módulo `thermal_control`

**Contexto:** O controle térmico de alto nível deve coordenar o PID sem expor detalhes internos.

**User Story:** Como desenvolvedor do firmware, quero criar `thermal_control` para transformar setpoint e temperatura em duty cycle.

**Critérios de Aceitação:**
- Existem `main/modules/control/thermal_control.c` e `thermal_control.h`.
- O header expõe API de inicialização e atualização do controle.

**Notas Técnicas:**
- Este módulo usa `pid`, mas não deve acessar PWM diretamente.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-050 - Implementar API de atualização do controle térmico

**Contexto:** A task térmica precisa de uma função simples para obter a saída de controle.

**User Story:** Como desenvolvedor do firmware, quero uma API que receba setpoint e temperatura filtrada para calcular o duty cycle.

**Critérios de Aceitação:**
- A função recebe setpoint e temperatura atual.
- A função retorna duty cycle calculado.

**Notas Técnicas:**
- Nome sugerido: `thermal_control_update()`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-051 - Integrar `thermal_control` com PID

**Contexto:** O módulo `thermal_control` deve usar o PID como algoritmo interno.

**User Story:** Como desenvolvedor do firmware, quero que `thermal_control` chame o PID para manter a separação entre regra de controle e algoritmo.

**Critérios de Aceitação:**
- `thermal_control` chama `pid_update()`.
- O PID não é chamado diretamente pela task térmica.

**Notas Técnicas:**
- Essa camada facilita trocar PID por outro controlador no futuro.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-052 - Saturar duty cycle final

**Contexto:** O duty final deve ser seguro mesmo se o PID ou a configuração retornarem valor inesperado.

**User Story:** Como desenvolvedor do firmware, quero garantir duty entre 0% e 100% antes de aplicar ao PWM.

**Critérios de Aceitação:**
- `thermal_control` limita duty mínimo em 0%.
- `thermal_control` limita duty máximo em 100%.

**Notas Técnicas:**
- Mantenha também a proteção no driver PWM.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-053 - Criar módulo de segurança

**Contexto:** O firmware precisa de uma camada dedicada para proteger o sistema contra falhas térmicas.

**User Story:** Como desenvolvedor do firmware, quero criar `safety` para centralizar validações de temperatura e sensor.

**Critérios de Aceitação:**
- Existem `main/modules/safety/safety.c` e `safety.h`.
- O header expõe inicialização e checagens de segurança.

**Notas Técnicas:**
- Segurança não deve ficar espalhada na task térmica.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-054 - Avaliar necessidade de `safety_task`

**Contexto:** O README indica que a task de segurança é opcional.

**User Story:** Como desenvolvedor do firmware, quero decidir se a segurança precisa de task própria ou se será chamada pela task térmica.

**Critérios de Aceitação:**
- A decisão está registrada no código ou documentação técnica.
- Se criada, `safety_task.c` tem responsabilidade clara.

**Notas Técnicas:**
- Para a primeira versão, preferir checagem chamada pela task térmica, salvo necessidade real.

**Pontos em Aberto / Definição:** Confirmar se haverá monitoramento independente do controle térmico.

## TASK-055 - Implementar `safety_init()`

**Contexto:** O módulo de segurança deve começar em estado conhecido antes do controle iniciar.

**User Story:** Como desenvolvedor do firmware, quero inicializar a segurança para evitar estados indefinidos.

**Critérios de Aceitação:**
- `safety_init()` coloca o estado inicial como seguro.
- A função limpa falhas anteriores quando apropriado.

**Notas Técnicas:**
- Não habilite PWM dentro do módulo de segurança.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-056 - Validar faixa de temperatura segura

**Contexto:** Temperaturas fora dos limites configurados podem danificar o sistema.

**User Story:** Como desenvolvedor do firmware, quero validar temperatura mínima e máxima para detectar operação insegura.

**Critérios de Aceitação:**
- Temperatura abaixo do mínimo configurado gera estado apropriado.
- Temperatura acima do máximo configurado gera falha.

**Notas Técnicas:**
- Use limites definidos em `config.h`.

**Pontos em Aberto / Definição:** Confirmar se baixa temperatura deve ser falha ou apenas aviso.

## TASK-057 - Validar falha de sensor

**Contexto:** O controle não pode operar se a temperatura não for confiável.

**User Story:** Como desenvolvedor do firmware, quero validar erro de sensor para impedir controle com dado inválido.

**Critérios de Aceitação:**
- Erro retornado pelo NTC vira estado de segurança.
- O estado diferencia falha de sensor de superaquecimento.

**Notas Técnicas:**
- Use o enum de segurança criado em `types.h`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-058 - Detectar temperatura acima do limite

**Contexto:** Superaquecimento é a falha mais crítica do projeto.

**User Story:** Como desenvolvedor do firmware, quero retornar falha quando a temperatura passar do limite máximo.

**Critérios de Aceitação:**
- Temperatura acima do limite gera `overtemperature`.
- A falha fica disponível para `thermal` e `app`.

**Notas Técnicas:**
- Não aplique histerese nesta tarefa, a menos que seja definida depois.

**Pontos em Aberto / Definição:** Avaliar necessidade de histerese após testes.

## TASK-059 - Detectar erro de sensor

**Contexto:** Sensor desconectado ou em curto deve interromper o controle.

**User Story:** Como desenvolvedor do firmware, quero retornar falha quando o sensor informar erro.

**Critérios de Aceitação:**
- Erro de leitura do NTC gera `sensor_error`.
- O estado é propagado sem virar temperatura falsa.

**Notas Técnicas:**
- Nunca substitua erro de sensor por temperatura arbitrária.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-060 - Desligar PWM em falha de segurança

**Contexto:** Em falha, o atuador térmico deve ir para estado seguro.

**User Story:** Como desenvolvedor do firmware, quero garantir que falhas de segurança desliguem o PWM imediatamente.

**Critérios de Aceitação:**
- A task térmica aplica duty 0% quando segurança falha.
- O controle não calcula nem aplica potência durante falha crítica.

**Notas Técnicas:**
- A ação física de desligar fica no módulo `thermal`, usando `pwm_drv`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-061 - Expor falhas para o módulo `app`

**Contexto:** A aplicação precisa mudar estado quando há falha de segurança.

**User Story:** Como desenvolvedor do firmware, quero disponibilizar falhas para `app` para que a máquina de estados reaja corretamente.

**Critérios de Aceitação:**
- `app` consegue consultar o estado de segurança.
- Falhas causam transição para estado `fault`.

**Notas Técnicas:**
- Evite dependência direta de `safety` para `app` se `thermal` já expuser status consolidado.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-062 - Criar módulo `thermal`

**Contexto:** O módulo `thermal` é o coordenador do ciclo de controle térmico.

**User Story:** Como desenvolvedor do firmware, quero criar `thermal` para integrar sensor, filtro, segurança, controle e PWM.

**Critérios de Aceitação:**
- Existem `main/modules/thermal/thermal.c` e `thermal.h`.
- O header expõe inicialização, status e setpoint.

**Notas Técnicas:**
- Este módulo pode depender de sensores, controle, segurança e drivers.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-063 - Criar `thermal_task.c`

**Contexto:** A execução periódica do controle deve ficar em uma task FreeRTOS própria.

**User Story:** Como desenvolvedor do firmware, quero criar `thermal_task.c` para separar loop periódico da API pública do módulo.

**Critérios de Aceitação:**
- O arquivo `main/modules/thermal/thermal_task.c` existe.
- A task térmica fica implementada nesse arquivo.

**Notas Técnicas:**
- A task pode ter função interna chamada por `thermal_init()`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-064 - Implementar `thermal_init()`

**Contexto:** O módulo térmico precisa preparar todas as dependências antes de controlar temperatura.

**User Story:** Como desenvolvedor do firmware, quero implementar `thermal_init()` para inicializar sensor, filtro, controle, segurança e PWM.

**Critérios de Aceitação:**
- Todas as dependências necessárias são inicializadas.
- A função retorna erro se alguma inicialização falhar.

**Notas Técnicas:**
- Inicialize PWM em 0% antes de iniciar a task.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-065 - Criar task térmica em `thermal_init()`

**Contexto:** Cada módulo deve criar sua própria task quando necessário.

**User Story:** Como desenvolvedor do firmware, quero criar a task térmica dentro de `thermal_init()` para seguir a arquitetura do README.

**Critérios de Aceitação:**
- `thermal_init()` chama `xTaskCreate()` ou equivalente.
- A task não é criada em `main.c`.

**Notas Técnicas:**
- Defina nome, stack e prioridade em `config.h` ou constantes claras.

**Pontos em Aberto / Definição:** Ajustar stack e prioridade após testes.

## TASK-066 - Executar task térmica em período fixo

**Contexto:** O controle precisa ser determinístico para o PID funcionar corretamente.

**User Story:** Como desenvolvedor do firmware, quero que a task térmica rode em período fixo configurável.

**Critérios de Aceitação:**
- A task usa o período definido em `config.h`.
- A execução usa atraso periódico adequado, como `vTaskDelayUntil`.

**Notas Técnicas:**
- Evite `vTaskDelay` simples se isso acumular atraso ao longo do tempo.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-067 - Ler temperatura pelo módulo NTC

**Contexto:** A task térmica precisa obter a medição atual antes de filtrar e controlar.

**User Story:** Como desenvolvedor do firmware, quero ler a temperatura usando `ntc_sensor` para manter a separação de camadas.

**Critérios de Aceitação:**
- A task chama API pública do sensor.
- A task não chama `adc_drv` diretamente.

**Notas Técnicas:**
- O sensor deve retornar temperatura ou erro.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-068 - Converter leitura para Celsius no fluxo térmico

**Contexto:** O controle e os logs devem trabalhar com unidade humana e consistente.

**User Story:** Como desenvolvedor do firmware, quero garantir que a task receba temperatura em Celsius para evitar confusão de unidades.

**Critérios de Aceitação:**
- O valor usado pela task está em graus Celsius.
- A unidade está documentada na API do sensor.

**Notas Técnicas:**
- A conversão deve acontecer no módulo `ntc_sensor`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-069 - Filtrar temperatura antes do controle

**Contexto:** O PID não deve reagir diretamente a ruído de medição.

**User Story:** Como desenvolvedor do firmware, quero filtrar a temperatura antes de calcular o duty cycle.

**Critérios de Aceitação:**
- A task passa a temperatura medida pelo filtro.
- O valor filtrado é o usado pelo controle térmico.

**Notas Técnicas:**
- Registre valor bruto e filtrado apenas se isso ajudar diagnóstico.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-070 - Checar segurança antes do PWM

**Contexto:** Nenhum duty cycle deve ser aplicado sem validação de segurança.

**User Story:** Como desenvolvedor do firmware, quero checar segurança antes de aplicar PWM para proteger o sistema.

**Critérios de Aceitação:**
- A task chama o módulo `safety` antes do controle final.
- Em falha, o fluxo pula aplicação normal de duty.

**Notas Técnicas:**
- A ordem esperada é leitura, filtro, segurança, controle e PWM.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-071 - Calcular duty cycle na task térmica

**Contexto:** Depois da validação de segurança, a task precisa calcular a potência de saída.

**User Story:** Como desenvolvedor do firmware, quero calcular duty cycle usando `thermal_control` para acionar o atuador.

**Critérios de Aceitação:**
- A task chama `thermal_control_update()`.
- O cálculo usa setpoint atual e temperatura filtrada.

**Notas Técnicas:**
- Não implemente PID diretamente na task.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-072 - Aplicar duty cycle no PWM

**Contexto:** A saída calculada precisa chegar ao hardware por meio do driver.

**User Story:** Como desenvolvedor do firmware, quero aplicar o duty cycle usando `pwm_drv_set_duty()` para controlar o atuador.

**Critérios de Aceitação:**
- A task chama `pwm_drv_set_duty()` com valor calculado.
- Erros do driver são tratados ou registrados.

**Notas Técnicas:**
- Nunca escreva diretamente no LEDC fora do driver PWM.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-073 - Desligar PWM na task em caso de falha

**Contexto:** A resposta a falha precisa ser imediata e previsível.

**User Story:** Como desenvolvedor do firmware, quero que a task térmica aplique duty 0% quando houver falha.

**Critérios de Aceitação:**
- Falha de segurança força `pwm_drv_set_duty(0)`.
- O status térmico registra a falha atual.

**Notas Técnicas:**
- Considere resetar o PID ao entrar em falha.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-074 - Expor status térmico atual

**Contexto:** Logger, comunicação e aplicação precisam consultar dados do controle.

**User Story:** Como desenvolvedor do firmware, quero expor uma função de status para observar o estado térmico atual.

**Critérios de Aceitação:**
- Existe uma função pública para obter status.
- O status inclui temperatura, setpoint, duty e falha.

**Notas Técnicas:**
- Proteja dados compartilhados se forem acessados por múltiplas tasks.

**Pontos em Aberto / Definição:** Definir se será usado mutex, critical section ou cópia atômica simples.

## TASK-075 - Expor alteração validada de setpoint

**Contexto:** O sistema precisa permitir ajuste de temperatura desejada sem aceitar valores perigosos.

**User Story:** Como desenvolvedor do firmware, quero alterar o setpoint por API validada para manter o controle seguro.

**Critérios de Aceitação:**
- Existe uma função pública para definir setpoint.
- Setpoints fora dos limites são rejeitados.

**Notas Técnicas:**
- Use limites configurados em `config.h`.

**Pontos em Aberto / Definição:** Definir faixa operacional permitida para o usuário.

## TASK-076 - Criar módulo `app`

**Contexto:** O módulo `app` representa a camada mais alta da aplicação.

**User Story:** Como desenvolvedor do firmware, quero criar `app` para concentrar inicialização e regras de aplicação.

**Critérios de Aceitação:**
- Existem `main/modules/app/app.c` e `app.h`.
- O header expõe `app_init()`.

**Notas Técnicas:**
- `app` pode chamar módulos de alto nível, mas drivers não devem chamar `app`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-077 - Criar máquina de estados da aplicação

**Contexto:** Estados explícitos facilitam tratamento de inicialização, execução e falhas.

**User Story:** Como desenvolvedor do firmware, quero criar `app_state_machine` para controlar transições da aplicação.

**Critérios de Aceitação:**
- Existem `app_state_machine.c` e `app_state_machine.h`.
- Há funções para inicializar, consultar e alterar estado.

**Notas Técnicas:**
- Use o enum de estados definido em `types.h`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-078 - Implementar `app_init()`

**Contexto:** `app_init()` será chamado pelo `app_main()` e deve iniciar o sistema.

**User Story:** Como desenvolvedor do firmware, quero implementar `app_init()` para organizar a inicialização da aplicação.

**Critérios de Aceitação:**
- `app_init()` existe e retorna sucesso ou erro.
- A função inicializa os módulos necessários em ordem clara.

**Notas Técnicas:**
- Se o retorno não puder ser usado por `app_main()`, registre erro via log.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-079 - Inicializar logger, comunicação e térmico

**Contexto:** A aplicação deve coordenar os módulos principais do firmware.

**User Story:** Como desenvolvedor do firmware, quero que `app_init()` inicialize logger, comunicação e controle térmico.

**Critérios de Aceitação:**
- `logger_init()` é chamado.
- `communication_init()` e `thermal_init()` são chamados.

**Notas Técnicas:**
- Defina uma ordem que permita registrar falhas de inicialização.

**Pontos em Aberto / Definição:** Confirmar se logger deve iniciar antes de todos os outros módulos.

## TASK-080 - Implementar lógica da máquina de estados

**Contexto:** A aplicação deve reagir a inicialização bem-sucedida, falhas e desligamento.

**User Story:** Como desenvolvedor do firmware, quero implementar a máquina de estados para controlar o fluxo principal do sistema.

**Critérios de Aceitação:**
- Transições válidas estão implementadas.
- Transições inválidas são rejeitadas ou ignoradas de forma previsível.

**Notas Técnicas:**
- Mantenha a máquina simples na primeira versão.

**Pontos em Aberto / Definição:** Definir se haverá eventos explícitos ou chamadas diretas de transição.

## TASK-081 - Iniciar aplicação em `init`

**Contexto:** O sistema deve começar em estado conhecido antes de habilitar controle.

**User Story:** Como desenvolvedor do firmware, quero iniciar a aplicação em `init` para representar fase de preparação.

**Critérios de Aceitação:**
- A máquina de estados começa em `init`.
- Nenhum estado indefinido é usado após boot.

**Notas Técnicas:**
- Defina o estado inicial durante `app_init()` ou inicialização da state machine.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-082 - Transicionar para `running`

**Contexto:** Após inicialização correta, o sistema deve indicar operação normal.

**User Story:** Como desenvolvedor do firmware, quero mudar para `running` quando todos os módulos iniciarem corretamente.

**Critérios de Aceitação:**
- O estado vira `running` após inicialização bem-sucedida.
- Falha de inicialização não permite `running`.

**Notas Técnicas:**
- Essa transição deve ocorrer apenas depois de `thermal_init()` concluir.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-083 - Transicionar para `fault`

**Contexto:** Falhas de segurança devem ficar visíveis no estado global da aplicação.

**User Story:** Como desenvolvedor do firmware, quero mudar para `fault` quando houver erro crítico.

**Critérios de Aceitação:**
- Falha de segurança gera estado `fault`.
- O estado `fault` impede operação normal do controle.

**Notas Técnicas:**
- A origem da falha pode vir do status térmico.

**Pontos em Aberto / Definição:** Definir política de recuperação após falha.

## TASK-084 - Transicionar para `shutdown`

**Contexto:** O sistema precisa representar desligamento planejado ou bloqueio final.

**User Story:** Como desenvolvedor do firmware, quero ter estado `shutdown` para indicar sistema desligado com segurança.

**Critérios de Aceitação:**
- A máquina aceita transição para `shutdown`.
- O PWM permanece desligado nesse estado.

**Notas Técnicas:**
- Para a primeira versão, o shutdown pode ser simples e sem reinício automático.

**Pontos em Aberto / Definição:** Definir quem solicita shutdown no produto final.

## TASK-085 - Manter `main.c` sem regra de negócio

**Contexto:** O README pede que `main()` permaneça simples.

**User Story:** Como desenvolvedor do firmware, quero manter `main.c` mínimo para preservar modularidade.

**Critérios de Aceitação:**
- `main.c` chama apenas `app_init()` e não acessa drivers.
- Não há lógica de controle, segurança ou sensor em `main.c`.

**Notas Técnicas:**
- Qualquer regra deve ir para `app`, `thermal` ou módulos especializados.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-086 - Criar módulo logger

**Contexto:** Logs ajudam a entender comportamento do controle e falhas.

**User Story:** Como desenvolvedor do firmware, quero criar `logger` para registrar dados relevantes do sistema.

**Critérios de Aceitação:**
- Existem `main/modules/logger/logger.c` e `logger.h`.
- O header expõe `logger_init()`.

**Notas Técnicas:**
- Comece usando logs do ESP-IDF.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-087 - Criar `logger_task.c`

**Contexto:** Logs periódicos não devem bloquear diretamente o ciclo de controle.

**User Story:** Como desenvolvedor do firmware, quero criar uma task de logger para telemetria periódica.

**Critérios de Aceitação:**
- O arquivo `main/modules/logger/logger_task.c` existe.
- A task é criada pelo módulo logger.

**Notas Técnicas:**
- A task deve ter prioridade menor que a task térmica.

**Pontos em Aberto / Definição:** Ajustar período de log após testes.

## TASK-088 - Implementar `logger_init()`

**Contexto:** O logger precisa criar sua task e preparar recursos antes de registrar dados.

**User Story:** Como desenvolvedor do firmware, quero implementar `logger_init()` para iniciar o registro periódico.

**Critérios de Aceitação:**
- `logger_init()` cria a task de log.
- Erros de criação da task são tratados ou registrados.

**Notas Técnicas:**
- Evite iniciar múltiplas tasks se `logger_init()` for chamado duas vezes.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-089 - Registrar temperatura atual

**Contexto:** Temperatura é a principal variável observada no controle térmico.

**User Story:** Como desenvolvedor do firmware, quero registrar temperatura atual para acompanhar o comportamento do sistema.

**Critérios de Aceitação:**
- O log mostra temperatura em Celsius.
- O log ocorre em intervalo configurável.

**Notas Técnicas:**
- Obtenha o dado pelo status público do módulo `thermal`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-090 - Registrar setpoint atual

**Contexto:** Sem o setpoint, a temperatura medida não tem referência de comparação.

**User Story:** Como desenvolvedor do firmware, quero registrar o setpoint para diagnosticar o erro de controle.

**Critérios de Aceitação:**
- O log mostra o setpoint em Celsius.
- O valor registrado corresponde ao setpoint usado pelo controle.

**Notas Técnicas:**
- Registre na mesma linha da temperatura quando possível.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-091 - Registrar duty cycle atual

**Contexto:** O duty cycle mostra a potência que o controlador está pedindo ao atuador.

**User Story:** Como desenvolvedor do firmware, quero registrar duty cycle para entender a resposta do PID.

**Critérios de Aceitação:**
- O log mostra duty cycle em porcentagem.
- Em falha, o log mostra duty 0% ou estado equivalente.

**Notas Técnicas:**
- Use o status térmico consolidado.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-092 - Registrar estado e falhas

**Contexto:** Logs de estado ajudam a diagnosticar transições e proteções.

**User Story:** Como desenvolvedor do firmware, quero registrar estado da aplicação e falhas de segurança para facilitar depuração.

**Critérios de Aceitação:**
- O log mostra estado atual da aplicação.
- O log mostra falha de segurança quando existir.

**Notas Técnicas:**
- Use nomes de estados legíveis, não apenas números.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-093 - Evitar bloqueio do controle pelo logger

**Contexto:** A task de controle térmico deve ter prioridade sobre logs.

**User Story:** Como desenvolvedor do firmware, quero garantir que logger não atrase a task térmica.

**Critérios de Aceitação:**
- Logger não executa operações longas dentro da task térmica.
- Logger tem prioridade menor ou mecanismo não bloqueante.

**Notas Técnicas:**
- Se houver compartilhamento de dados, proteja sem bloquear por tempo longo.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-094 - Criar módulo comunicação

**Contexto:** O firmware precisa de uma forma inicial de consultar e ajustar parâmetros.

**User Story:** Como desenvolvedor do firmware, quero criar `communication` para preparar interfaces externas.

**Critérios de Aceitação:**
- Existem `main/modules/communication/communication.c` e `communication.h`.
- O header expõe `communication_init()`.

**Notas Técnicas:**
- A primeira versão pode ser simples, via console serial ou logs.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-095 - Criar `communication_task.c`

**Contexto:** Comunicação pode precisar processar comandos sem bloquear controle térmico.

**User Story:** Como desenvolvedor do firmware, quero criar uma task de comunicação para tratar comandos externos.

**Critérios de Aceitação:**
- O arquivo `main/modules/communication/communication_task.c` existe.
- A task é criada pelo módulo de comunicação.

**Notas Técnicas:**
- A task deve ter prioridade adequada para não competir com o controle térmico.

**Pontos em Aberto / Definição:** Definir protocolo final de comunicação.

## TASK-096 - Implementar comunicação inicial simples

**Contexto:** Antes de um protocolo completo, o projeto precisa de uma forma básica de interação.

**User Story:** Como desenvolvedor do firmware, quero implementar comunicação simples para consultar dados e testar setpoint.

**Critérios de Aceitação:**
- Existe uma forma de consultar dados atuais.
- Existe uma forma simples de solicitar alteração de setpoint.

**Notas Técnicas:**
- Pode ser console serial, comandos simples ou API interna exposta para testes.

**Pontos em Aberto / Definição:** Escolher entre console serial e API interna para a primeira entrega.

## TASK-097 - Permitir consulta da temperatura

**Contexto:** Usuário ou teste precisa saber a temperatura medida pelo sistema.

**User Story:** Como usuário do firmware, quero consultar a temperatura atual para verificar se a medição está funcionando.

**Critérios de Aceitação:**
- A comunicação retorna temperatura atual em Celsius.
- Falha de sensor é indicada quando não houver temperatura válida.

**Notas Técnicas:**
- Use o status público do módulo `thermal`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-098 - Permitir consulta do setpoint

**Contexto:** O setpoint define a temperatura alvo do controle.

**User Story:** Como usuário do firmware, quero consultar o setpoint atual para saber qual alvo está configurado.

**Critérios de Aceitação:**
- A comunicação retorna o setpoint atual em Celsius.
- O valor corresponde ao usado pelo controle térmico.

**Notas Técnicas:**
- Evite duplicar estado de setpoint em vários módulos.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-099 - Permitir consulta do duty cycle

**Contexto:** O duty cycle mostra a saída aplicada ao atuador.

**User Story:** Como usuário do firmware, quero consultar o duty cycle para entender a ação do controle.

**Critérios de Aceitação:**
- A comunicação retorna duty cycle em porcentagem.
- Em falha, a consulta deixa claro que a saída está desligada.

**Notas Técnicas:**
- Use o status térmico consolidado.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-100 - Permitir consulta do estado da aplicação

**Contexto:** Saber se o sistema está em init, running, fault ou shutdown facilita diagnóstico.

**User Story:** Como usuário do firmware, quero consultar o estado da aplicação para entender a condição atual do sistema.

**Critérios de Aceitação:**
- A comunicação retorna o estado atual.
- O estado é legível, não apenas numérico.

**Notas Técnicas:**
- Crie função auxiliar para converter enum em texto se necessário.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-101 - Permitir alteração de setpoint

**Contexto:** O controle térmico precisa aceitar novo alvo de temperatura durante operação.

**User Story:** Como usuário do firmware, quero alterar o setpoint para controlar a temperatura desejada.

**Critérios de Aceitação:**
- Existe comando ou API para solicitar novo setpoint.
- O novo valor chega ao módulo `thermal`.

**Notas Técnicas:**
- A alteração deve passar pela API validada de setpoint.

**Pontos em Aberto / Definição:** Definir formato final do comando.

## TASK-102 - Validar novo setpoint

**Contexto:** Um setpoint inválido pode causar operação insegura ou sem sentido.

**User Story:** Como desenvolvedor do firmware, quero validar o setpoint antes de aceitar a alteração.

**Critérios de Aceitação:**
- Setpoints fora da faixa configurada são recusados.
- A comunicação informa sucesso ou erro da alteração.

**Notas Técnicas:**
- Use os mesmos limites do módulo térmico para evitar regras duplicadas.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-103 - Rejeitar setpoints fora dos limites

**Contexto:** A proteção deve impedir entrada de valores perigosos pelo usuário.

**User Story:** Como usuário do firmware, quero que o sistema recuse setpoints inválidos para evitar operação insegura.

**Critérios de Aceitação:**
- Setpoint abaixo do mínimo não altera o valor atual.
- Setpoint acima do máximo não altera o valor atual.

**Notas Técnicas:**
- Registre a tentativa rejeitada em log quando possível.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-104 - Criar testes unitários do PID

**Contexto:** O PID é crítico para o comportamento do controle térmico.

**User Story:** Como desenvolvedor do firmware, quero testar o PID para evitar regressões no algoritmo de controle.

**Critérios de Aceitação:**
- Existem testes para inicialização e atualização do PID.
- Os testes rodam no ambiente definido para o projeto.

**Notas Técnicas:**
- Priorize testes sem dependência de hardware.

**Pontos em Aberto / Definição:** Definir framework de testes do projeto.

## TASK-105 - Testar saturação do PID

**Contexto:** A saída do PID não pode passar dos limites configurados.

**User Story:** Como desenvolvedor do firmware, quero testar saturação mínima e máxima para garantir saída segura.

**Critérios de Aceitação:**
- Há teste para saída abaixo do limite mínimo.
- Há teste para saída acima do limite máximo.

**Notas Técnicas:**
- Use entradas artificiais que forcem erro grande.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-106 - Testar anti-windup

**Contexto:** Anti-windup evita comportamento ruim após saturação prolongada.

**User Story:** Como desenvolvedor do firmware, quero testar anti-windup para garantir que a integral fique controlada.

**Critérios de Aceitação:**
- O teste força saturação por vários ciclos.
- A integral não cresce sem limite.

**Notas Técnicas:**
- Verifique comportamento após sair da saturação.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-107 - Criar testes do filtro

**Contexto:** O filtro influencia diretamente a temperatura usada pelo PID.

**User Story:** Como desenvolvedor do firmware, quero testar o filtro para garantir suavização previsível.

**Critérios de Aceitação:**
- Existem testes para atualização do filtro.
- O resultado esperado é calculado e comparado.

**Notas Técnicas:**
- Use valores simples para facilitar conferência manual.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-108 - Testar reset do filtro

**Contexto:** Reset incorreto pode deixar o controle usando histórico antigo.

**User Story:** Como desenvolvedor do firmware, quero testar reset do filtro para garantir estado inicial conhecido.

**Critérios de Aceitação:**
- Após reset, a saída corresponde ao valor inicial esperado.
- O histórico anterior não afeta a saída após reset.

**Notas Técnicas:**
- Faça pelo menos um teste com valor anterior diferente do valor de reset.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-109 - Testar conversão do NTC

**Contexto:** Erro na conversão do NTC compromete todo o controle térmico.

**User Story:** Como desenvolvedor do firmware, quero testar a conversão ADC para temperatura para validar a matemática do sensor.

**Critérios de Aceitação:**
- Há teste com valor conhecido de ADC ou resistência.
- A temperatura calculada fica dentro de tolerância definida.

**Notas Técnicas:**
- Use casos baseados no datasheet do NTC quando disponível.

**Pontos em Aberto / Definição:** Definir tolerância aceitável da conversão.

## TASK-110 - Testar leituras inválidas do NTC

**Contexto:** Sensor desconectado ou saturado deve gerar erro, não temperatura válida.

**User Story:** Como desenvolvedor do firmware, quero testar leituras inválidas para garantir detecção de falhas.

**Critérios de Aceitação:**
- ADC zero gera erro quando aplicável.
- ADC saturado gera erro quando aplicável.

**Notas Técnicas:**
- Ajuste os casos conforme a topologia do divisor.

**Pontos em Aberto / Definição:** Confirmar topologia final do NTC.

## TASK-111 - Testar limites de segurança

**Contexto:** O módulo de segurança precisa reagir corretamente aos limites configurados.

**User Story:** Como desenvolvedor do firmware, quero testar limites térmicos para garantir proteção do sistema.

**Critérios de Aceitação:**
- Temperatura dentro da faixa retorna estado seguro.
- Temperatura fora da faixa retorna falha esperada.

**Notas Técnicas:**
- Teste valores no limite e logo acima do limite.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-112 - Testar falha por superaquecimento

**Contexto:** Superaquecimento deve ser detectado de forma confiável.

**User Story:** Como desenvolvedor do firmware, quero testar temperatura acima do limite para garantir estado de falha.

**Critérios de Aceitação:**
- Temperatura acima do máximo gera `overtemperature`.
- O resultado é propagado para o fluxo térmico.

**Notas Técnicas:**
- Use limite configurado em `config.h` no teste.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-113 - Testar falha por sensor inválido

**Contexto:** O sistema deve entrar em falha quando o sensor não fornece dado confiável.

**User Story:** Como desenvolvedor do firmware, quero testar erro de sensor para garantir proteção contra medição inválida.

**Critérios de Aceitação:**
- Erro do sensor gera `sensor_error`.
- O controle não continua como se a temperatura fosse válida.

**Notas Técnicas:**
- Simule retorno de erro do módulo NTC.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-114 - Testar desligamento do PWM em falha

**Contexto:** A ação segura mais importante é desligar o atuador em falha.

**User Story:** Como desenvolvedor do firmware, quero testar que falhas forçam PWM em 0%.

**Critérios de Aceitação:**
- Falha de sensor aplica duty 0%.
- Superaquecimento aplica duty 0%.

**Notas Técnicas:**
- Se o teste for unitário, use mock ou stub do driver PWM.

**Pontos em Aberto / Definição:** Definir estratégia de mock para drivers.

## TASK-115 - Testar validação de setpoint

**Contexto:** A entrada do usuário não deve aceitar valores fora da faixa permitida.

**User Story:** Como desenvolvedor do firmware, quero testar setpoint mínimo e máximo para evitar configuração insegura.

**Critérios de Aceitação:**
- Setpoint válido é aceito.
- Setpoints abaixo e acima da faixa são rejeitados.

**Notas Técnicas:**
- Verifique também se o setpoint antigo permanece após rejeição.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-116 - Compilar para ESP32 DevKit

**Contexto:** A primeira validação prática é garantir que o projeto compila para o alvo inicial.

**User Story:** Como desenvolvedor do firmware, quero compilar para ESP32 DevKit para confirmar compatibilidade com o ambiente.

**Critérios de Aceitação:**
- O alvo ESP32 DevKit está configurado.
- A build termina sem erro.

**Notas Técnicas:**
- Use `idf.py set-target` se necessário antes do build.

**Pontos em Aberto / Definição:** Definir o modelo exato do ESP32 DevKit usado na bancada.

## TASK-117 - Gravar firmware no ESP32 DevKit

**Contexto:** Depois de compilar, o firmware precisa ser testado no hardware real.

**User Story:** Como desenvolvedor do firmware, quero gravar o firmware no ESP32 DevKit para validar execução embarcada.

**Critérios de Aceitação:**
- O firmware é gravado sem erro.
- O monitor serial inicia após a gravação.

**Notas Técnicas:**
- Use `idf.py flash monitor` com a porta serial correta.

**Pontos em Aberto / Definição:** Definir porta serial usada no computador de teste.

## TASK-118 - Confirmar boot estável

**Contexto:** O firmware deve iniciar sem resetar continuamente ou travar.

**User Story:** Como desenvolvedor do firmware, quero confirmar boot estável para validar a base do sistema.

**Critérios de Aceitação:**
- O dispositivo não entra em reset contínuo.
- Não aparecem panic ou watchdog no monitor serial.

**Notas Técnicas:**
- Observe o monitor por tempo suficiente para ver várias execuções da task térmica.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-119 - Medir entrada ADC com valores conhecidos

**Contexto:** A leitura ADC precisa ser validada antes de confiar na temperatura calculada.

**User Story:** Como desenvolvedor do firmware, quero medir valores conhecidos no ADC para validar o driver.

**Critérios de Aceitação:**
- Uma tensão baixa gera leitura coerente.
- Uma tensão alta gera leitura coerente.

**Notas Técnicas:**
- Use fonte ou divisor conhecido e registre os valores medidos.

**Pontos em Aberto / Definição:** Definir equipamento disponível para teste.

## TASK-120 - Comparar temperatura com referência externa

**Contexto:** A temperatura calculada deve ser comparada com uma medição confiável.

**User Story:** Como desenvolvedor do firmware, quero comparar o NTC com uma referência para validar conversão e calibração.

**Critérios de Aceitação:**
- A temperatura do firmware é comparada com termômetro externo.
- O erro observado é registrado.

**Notas Técnicas:**
- Faça teste em pelo menos temperatura ambiente e uma condição aquecida.

**Pontos em Aberto / Definição:** Definir tolerância aceitável em graus Celsius.

## TASK-121 - Validar aumento de PWM abaixo do setpoint

**Contexto:** Se a temperatura está abaixo do alvo, o controlador deve pedir mais potência.

**User Story:** Como desenvolvedor do firmware, quero confirmar que o PWM aumenta quando a temperatura está abaixo do setpoint.

**Critérios de Aceitação:**
- Com temperatura abaixo do setpoint, duty cycle aumenta.
- O aumento aparece no log ou na medição do PWM.

**Notas Técnicas:**
- Use um setpoint seguro para teste de bancada.

**Pontos em Aberto / Definição:** Definir método de medição do PWM.

## TASK-122 - Validar redução de PWM perto do setpoint

**Contexto:** Ao se aproximar da temperatura alvo, o controlador deve reduzir potência.

**User Story:** Como desenvolvedor do firmware, quero confirmar que o PWM reduz perto do setpoint para evitar overshoot.

**Critérios de Aceitação:**
- Duty cycle reduz quando a temperatura se aproxima do setpoint.
- O comportamento é visível em logs ou medição.

**Notas Técnicas:**
- Ganhos PID iniciais podem precisar de ajuste para esse teste.

**Pontos em Aberto / Definição:** Definir ganhos PID iniciais de bancada.

## TASK-123 - Validar desligamento por falha

**Contexto:** A proteção precisa funcionar no hardware real.

**User Story:** Como desenvolvedor do firmware, quero confirmar que o PWM desliga quando ocorre falha de segurança.

**Critérios de Aceitação:**
- Falha simulada de sensor desliga PWM.
- Falha de limite térmico desliga PWM quando testável com segurança.

**Notas Técnicas:**
- Prefira simular falha antes de forçar condição térmica real.

**Pontos em Aberto / Definição:** Definir procedimento seguro para simular falhas.

## TASK-124 - Validar setpoint dentro dos limites

**Contexto:** A interface de configuração deve aceitar valores permitidos.

**User Story:** Como usuário do firmware, quero alterar setpoint válido para controlar o sistema.

**Critérios de Aceitação:**
- Um setpoint dentro da faixa é aceito.
- O novo valor passa a aparecer em logs ou consulta.

**Notas Técnicas:**
- Teste pelo caminho real de comunicação escolhido.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-125 - Validar rejeição de setpoint inválido

**Contexto:** A interface deve proteger o sistema contra entrada perigosa.

**User Story:** Como usuário do firmware, quero que setpoints inválidos sejam recusados para preservar segurança.

**Critérios de Aceitação:**
- Setpoint abaixo do mínimo é rejeitado.
- Setpoint acima do máximo é rejeitado.

**Notas Técnicas:**
- Verifique que o setpoint anterior continua ativo.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-126 - Rodar `clang-format`

**Contexto:** O projeto exige padronização de estilo antes da entrega.

**User Story:** Como desenvolvedor do firmware, quero formatar todos os arquivos C e H para manter consistência.

**Critérios de Aceitação:**
- `clang-format` foi executado nos arquivos `.c` e `.h`.
- Não há arquivos de código fora do padrão configurado.

**Notas Técnicas:**
- Use o comando indicado no `README.md`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-127 - Revisar direção dos includes

**Contexto:** A arquitetura depende de fluxo de dependência descendente.

**User Story:** Como desenvolvedor do firmware, quero revisar includes para evitar acoplamento indevido entre módulos.

**Critérios de Aceitação:**
- Módulos de baixo nível não incluem módulos de alto nível.
- A regra de dependência do `README.md` é respeitada.

**Notas Técnicas:**
- Revise especialmente `drivers`, `sensors` e `control`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-128 - Garantir que drivers não dependem de alto nível

**Contexto:** Drivers devem ser reutilizáveis e não conhecer regras de aplicação.

**User Story:** Como desenvolvedor do firmware, quero garantir que drivers não dependam de aplicação, thermal ou safety.

**Critérios de Aceitação:**
- Nenhum arquivo em `drivers` inclui headers de alto nível.
- Drivers expõem APIs simples chamadas pelos módulos superiores.

**Notas Técnicas:**
- Se precisar de configuração, use `config.h`.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-129 - Verificar criação de tasks por módulo

**Contexto:** O README define que cada módulo cria sua própria task quando necessário.

**User Story:** Como desenvolvedor do firmware, quero verificar que tasks são criadas no módulo responsável para manter organização.

**Critérios de Aceitação:**
- Task térmica é criada em `thermal`.
- Tasks de logger e comunicação são criadas nos próprios módulos.

**Notas Técnicas:**
- `main.c` e `app` não devem centralizar criação de todas as tasks.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-130 - Remover código morto e stubs

**Contexto:** Código temporário dificulta manutenção e confunde novos desenvolvedores.

**User Story:** Como desenvolvedor do firmware, quero remover código morto antes da entrega para manter o projeto limpo.

**Critérios de Aceitação:**
- Não há funções vazias sem justificativa.
- Não há comentários temporários como TODO sem tarefa associada.

**Notas Técnicas:**
- Stubs necessários devem ter motivo claro e estar documentados.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-131 - Fazer build limpa final

**Contexto:** A entrega precisa ser validada a partir de um estado limpo.

**User Story:** Como desenvolvedor do firmware, quero fazer build limpa para garantir que o projeto não depende de artefatos antigos.

**Critérios de Aceitação:**
- A pasta de build anterior não é necessária para compilar.
- A build limpa termina sem erro.

**Notas Técnicas:**
- Use o fluxo recomendado do ESP-IDF para limpar e compilar.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-132 - Registrar resultado da build final

**Contexto:** O resultado final precisa ficar rastreável para revisão.

**User Story:** Como desenvolvedor do firmware, quero registrar o resultado da build final para facilitar validação da entrega.

**Critérios de Aceitação:**
- O comando executado é registrado.
- O resultado da build é registrado como sucesso ou falha com causa.

**Notas Técnicas:**
- Pode ser registrado em comentário de PR, issue ou documento técnico definido pela equipe.

**Pontos em Aberto / Definição:** Definir onde registrar evidências de build.

## TASK-133 - Atualizar documentação técnica se necessário

**Contexto:** Documentação divergente do código prejudica manutenção.

**User Story:** Como desenvolvedor do firmware, quero atualizar documentação apenas se a implementação final divergir do README.

**Critérios de Aceitação:**
- Divergências reais são documentadas.
- O README não é alterado sem necessidade.

**Notas Técnicas:**
- Priorize manter implementação alinhada ao README.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-134 - Conferir que README não foi alterado sem necessidade

**Contexto:** O README é a referência arquitetural atual do projeto.

**User Story:** Como mantenedor do projeto, quero garantir que o README permaneça estável durante a implementação.

**Critérios de Aceitação:**
- Alterações no README são revisadas.
- Se não houver motivo técnico, o README permanece sem mudanças.

**Notas Técnicas:**
- Use diff do controle de versão quando disponível.

**Pontos em Aberto / Definição:** Nenhum.

## TASK-135 - Conferir devcontainer

**Contexto:** O devcontainer facilita ambiente reproduzível para desenvolvimento.

**User Story:** Como desenvolvedor do firmware, quero garantir que o devcontainer continue presente para facilitar onboarding.

**Critérios de Aceitação:**
- A pasta `.devcontainer/` continua no projeto.
- `Dockerfile` e `devcontainer.json` continuam presentes.

**Notas Técnicas:**
- Não remova o devcontainer durante limpezas do projeto.

**Pontos em Aberto / Definição:** Nenhum.
