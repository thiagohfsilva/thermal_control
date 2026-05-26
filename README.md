# Thermal Control Firmware

Firmware embarcado para controle térmico em malha fechada utilizando FreeRTOS e arquitetura modular.

O projeto é organizado em módulos independentes responsáveis pela aquisição de temperatura, controle térmico, segurança, comunicação e serviços auxiliares. Cada módulo possui sua própria inicialização e, quando necessário, cria internamente sua própria task do FreeRTOS.

## Objetivos

- Controle de temperatura em malha fechada
- Arquitetura modular e escalável
- Separação entre aplicação, controle, sensores e hardware
- Execução determinística utilizando FreeRTOS
- Segurança térmica e tratamento de falhas
- Código legível e padronizado com `clang-format`

---

## Arquitetura do Firmware

A arquitetura segue uma organização em camadas, na qual módulos de alto nível utilizam serviços dos módulos inferiores.

```text
Application
    ↓
Modules
    ↓
Control / Sensors / Services
    ↓
Drivers
    ↓
SDK / Hardware
```

O objetivo é evitar acoplamento excessivo entre módulos e manter responsabilidades bem definidas.

---

## Estrutura do Projeto

```text
main/
│
├── main.c
│
├── modules/
│   │
│   ├── app/
│   │   ├── app.c
│   │   ├── app.h
│   │   ├── app_state_machine.c
│   │   └── app_state_machine.h
│   │
│   ├── control/
│   │   ├── pid.c
│   │   ├── pid.h
│   │   ├── thermal_control.c
│   │   ├── thermal_control.h
│   │   ├── filter.c
│   │   └── filter.h
│   │
│   ├── drivers/
│   │   ├── adc_drv.c
│   │   ├── adc_drv.h
│   │   ├── pwm_drv.c
│   │   ├── pwm_drv.h
│   │   ├── gpio_drv.c
│   │   └── gpio_drv.h
│   │
│   ├── sensors/
│   │   ├── ntc_sensor.c
│   │   └── ntc_sensor.h
│   │
│   ├── thermal/
│   │   ├── thermal.c
│   │   ├── thermal.h
│   │   └── thermal_task.c
│   │
│   ├── safety/
│   │   ├── safety.c
│   │   ├── safety.h
│   │   └── safety_task.c
│   │
│   ├── logger/
│   │   ├── logger.c
│   │   ├── logger.h
│   │   └── logger_task.c
│   │
│   ├── communication/
│   │   ├── communication.c
│   │   ├── communication.h
│   │   └── communication_task.c
│   │
│   └── common/
│       ├── types.h
│       ├── defines.h
│       └── config.h
│
└── CMakeLists.txt
```

---

## Filosofia de Modularização

Cada módulo deve possuir uma responsabilidade clara.

Exemplo:

- `app/` → regras de negócio e máquina de estados
- `control/` → algoritmo PID, filtros e controle térmico
- `drivers/` → abstração do SDK e do hardware
- `sensors/` → conversão de sinais físicos
- `thermal/` → gerenciamento do controle térmico
- `safety/` → proteção térmica e tratamento de falhas
- `logger/` → logs e telemetria
- `communication/` → interfaces externas

### Regra de Dependência

As dependências devem seguir apenas o fluxo descendente:

```text
app
 ↓
thermal
 ↓
control / sensors / services
 ↓
drivers
 ↓
SDK
```

Exemplo correto:

```c
float temp = ntc_sensor_get_temperature();

float duty =
    thermal_control_update(setpoint, temp);

pwm_drv_set_duty(duty);
```

Exemplo incorreto:

```text
driver chamando app
```

Módulos de baixo nível nunca devem depender de módulos de alto nível.

---

## Inicialização dos Módulos

Não existe um gerenciador central de tasks.

Cada módulo é responsável por sua própria inicialização e pela criação de sua task, quando necessário.

Exemplo:

```c
void thermal_init(void)
{
    pid_init();

    ntc_sensor_init();

    pwm_drv_init();

    xTaskCreate(
        thermal_task,
        "thermal",
        4096,
        NULL,
        5,
        NULL);
}
```

O `main()` deve permanecer simples:

```c
void app_main(void)
{
    app_init();
}
```

---

## Como Compilar o Projeto (ESP-IDF + VSCode)

Este projeto utiliza o framework ESP-IDF.

### Pré-requisitos

Instale:

- Visual Studio Code
- Extensão ESP-IDF para VSCode
- Toolchain do ESP-IDF
- Python configurado pelo instalador do ESP-IDF

Após instalar a extensão, configure o ambiente utilizando:

`Ctrl + Shift + P`

e execute:

```text
ESP-IDF: Configure ESP-IDF extension
```

Siga o assistente para instalar e configurar automaticamente o ambiente.

### Abrindo o Projeto

1. Abra o VSCode.
2. Selecione **File → Open Folder**.
3. Abra a pasta raiz do projeto.

A extensão do ESP-IDF detectará automaticamente a estrutura do projeto.

### Selecionando o Target

No VSCode:

```text
Ctrl + Shift + P
```

Execute:

```text
ESP-IDF: Set Espressif Device Target
```

Escolha o microcontrolador correto, por exemplo:

```text
ESP32
ESP32-S3
ESP32-C3
```

### Configuração do Projeto

Caso necessário, abra o menu de configuração:

```text
ESP-IDF: SDK Configuration editor (menuconfig)
```

ou via terminal:

```bash
idf.py menuconfig
```

### Compilação

Para compilar o projeto:

No terminal:

```bash
idf.py build
```

Ou no VSCode:

```text
ESP-IDF: Build your project
```

O firmware compilado será gerado no diretório:

```text
build/
```

### Gravação na Placa

Conecte a placa via USB e execute:

```bash
idf.py flash
```

Ou pelo VSCode:

```text
ESP-IDF: Flash your project
```

### Monitor Serial

Para visualizar logs da aplicação:

```bash
idf.py monitor
```

Ou:

```bash
idf.py flash monitor
```

No VSCode:

```text
ESP-IDF: Monitor your device
```

Para sair do monitor serial:

```text
Ctrl + ]
```

### Limpeza do Build

Limpeza incremental:

```bash
idf.py clean
```

Limpeza completa:

```bash
idf.py fullclean
```

---

## FreeRTOS

Tasks devem ser criadas apenas quando fizer sentido funcionalmente.

| Módulo | Possui Task |
|--------|--------------|
| thermal | Sim |
| logger | Sim |
| communication | Sim |
| safety | Opcional |
| drivers | Não |
| sensors | Não |
| control | Não |

Módulos passivos devem expor apenas APIs.

---

## Controle Térmico

A task térmica deve possuir execução periódica e determinística.

Fluxo esperado:

```text
Acquire
    ↓
Filter
    ↓
Safety Check
    ↓
PID / Control
    ↓
Output Saturation
    ↓
PWM Update
```

Exemplo simplificado:

```text
ADC
→ temperatura
→ filtro
→ controlador
→ PWM
```

---

## Formatação de Código

Este projeto utiliza obrigatoriamente `clang-format`.

Antes de realizar commits, todo o código deve ser formatado.

### Instalação

Linux:

```bash
sudo apt install clang-format
```

Verificar versão:

```bash
clang-format --version
```

---

## Arquivo `.clang-format`

Criar um arquivo `.clang-format` na raiz do projeto:

```yaml
---
Language: Cpp
BasedOnStyle: LLVM

IndentWidth: 4
TabWidth: 4
UseTab: Never

ColumnLimit: 80
ContinuationIndentWidth: 4

InsertNewlineAtEOF: true

MaxEmptyLinesToKeep: 2

BreakBeforeBraces: Custom
BraceWrapping:
  AfterCaseLabel: false
  AfterFunction: true
  AfterControlStatement: Never

IndentCaseLabels: true
IndentCaseBlocks: false

PointerAlignment: Right
DerivePointerAlignment: false

SpaceBeforeParens: ControlStatements
SpaceBeforeAssignmentOperators: true

SpaceAfterCStyleCast: false
SpacesInParens: Never
SpacesInSquareBrackets: false
SpaceBeforeCaseColon: false

AlignAfterOpenBracket: Align

AllowShortEnumsOnASingleLine: false
AllowShortBlocksOnASingleLine: Never
AllowShortCaseLabelsOnASingleLine: false
AllowShortFunctionsOnASingleLine: None
AllowShortIfStatementsOnASingleLine: Never
AllowShortLoopsOnASingleLine: false

BreakStringLiterals: false
ReflowComments: false

SortIncludes: Never
```

---

## Como Formatar o Código

Formatar um arquivo:

```bash
clang-format -i main/modules/thermal/thermal.c
```

Formatar todos os arquivos `.c` e `.h`, incluindo subpastas:

```bash
find . \( -name "*.c" -o -name "*.h" \) \
-exec clang-format -i {} \;
```

---

## Diretrizes de Código

- Indentação de 4 espaços
- Sem tabs
- Máximo de 80 colunas
- Chaves de função na linha seguinte
- Includes não devem ser reordenados automaticamente
- Evitar lógica complexa no `main.c`
- Evitar dependências circulares
- Cada módulo deve possuir responsabilidade única
- Tasks devem ser criadas no `init()` do próprio módulo

Exemplo esperado:

```c
void thermal_init(void)
{
    if (initialized) {
        return;
    }

    initialized = true;

    pwm_drv_init();

    xTaskCreate(
        thermal_task,
        "thermal",
        4096,
        NULL,
        5,
        NULL);
}
```

---

## Futuras Melhorias

- Separar a task de aquisição/filtragem da task de controle. Idealmente, a aquisição deve ser pelo menos 100 vezes mais rápida que a execução do controle.
- Estimar corretamente a frequência de corte do filtro IIR e utilizar parâmetros coerentes no firmware.
- Verificar se os limites mínimo e máximo de temperatura para entrada no modo seguro fazem sentido.
- Validar o comportamento térmico do sistema, analisar oscilações e estimar a variância do sinal para verificar a efetividade do filtro.
- Confirmar se o ADC foi configurado corretamente em 12 bits.
- Melhorar o acumulador integral do PID. Como o processo é lento (~48 s), existe possibilidade de acúmulo excessivo (*integral windup*).
- Realizar calibração do sensor utilizando gelo (~0 °C) e água em ebulição (~100 °C) com termômetro certificado.
- Implementar medição de corrente na carga, permitindo entrada no modo seguro quando:

```text
duty_cycle > 0 && current == 0
```

- Revisar cada módulo com calma e validar se a arquitetura e implementação fazem sentido.
- Ainda existe muito trabalho antes de o sistema se tornar um produto real.

## Outras Ideias

- Persistência de parâmetros
- Auto-tuning do PID
- Interface serial de configuração
- Logging dividido e melhor estruturado
- Testes unitários
- Watchdog e diagnóstico
- Registro de falhas com causa raiz
- Sinalização via USB da deterioração do sistema e solicitação de manutenção preventiva