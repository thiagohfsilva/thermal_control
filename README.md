# Thermal Control Firmware

Firmware embarcado para controle térmico em malha fechada utilizando FreeRTOS e arquitetura modular.

O projeto é organizado em módulos independentes responsáveis por aquisição de temperatura, controle térmico, segurança, comunicação e serviços auxiliares. Cada módulo possui sua própria inicialização e, quando necessário, cria internamente sua própria task FreeRTOS.

## Objetivos

- Controle de temperatura em malha fechada
- Arquitetura modular e escalável
- Separação entre aplicação, controle, sensores e hardware
- Execução determinística usando FreeRTOS
- Segurança térmica e tratamento de falhas
- Código legível e padronizado com `clang-format`

---

## Arquitetura do Firmware

A arquitetura segue uma organização em camadas, onde módulos de alto nível utilizam serviços dos módulos inferiores.

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

A ideia é evitar acoplamento excessivo entre módulos e manter responsabilidades bem definidas.

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
- `drivers/` → abstração do SDK e hardware
- `sensors/` → conversão de sinais físicos
- `thermal/` → gerenciamento do controle térmico
- `safety/` → proteção térmica e falhas
- `logger/` → logs e telemetria
- `communication/` → interfaces externas

### Regra de dependência

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

Cada módulo é responsável por sua própria inicialização e criação de task, quando necessário.

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
int main(void)
{
    app_init();

    vTaskStartScheduler();

    while (1) {
    }
}
```

---

## FreeRTOS

Tasks devem ser criadas apenas quando fizer sentido funcionalmente.

Exemplos:

| Módulo | Possui Task |
|--------|-------------|
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

Exemplo:

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

Antes de realizar commits, todo código deve ser formatado.

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

## Como formatar o código

Formatar um arquivo:

```bash
clang-format -i main/modules/thermal/thermal.c
```

Formatar múltiplos arquivos:

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

- Persistência de parâmetros
- Auto tuning PID
- Interface serial de configuração
- Logging estruturado
- Testes unitários
- Watchdog e diagnóstico