Calculadora Modular em C

Este projeto implementa uma calculadora científica e estatística modular em linguagem C, com suporte a operações básicas, avançadas, estatísticas, e manipulação de matrizes, além de armazenamento de histórico em arquivo CSV.

Funcionalidades

A calculadora possui uma ampla gama de operações divididas em categorias:

--Operações Básicas--

Soma

Subtração

Multiplicação

Divisão (com tratamento de erro para divisão por zero)

--Operações Avançadas--

Potência

Raiz quadrada

Fatorial (até 20!)

Logaritmo (base 10)

Seno, Cosseno e Tangente

--Operações Estatísticas--

Média

Mediana

Desvio padrão

Máximo e mínimo

Operações Inteiras MDC (Máximo Divisor Comum)

MMC (Mínimo Múltiplo Comum)

Matrizes (2x2 e 3x3) Leitura de matrizes

Impressão formatada

Soma de matrizes

Multiplicação de matrizes

--Histórico de Operações--

Registro automático de todas as operações realizadas

Visualização no terminal

Exportação em formato CSV (historico.csv)

Estrutura do Código

O projeto é dividido em seções bem organizadas e comentadas:

// ===== FUNÇÕES BÁSICAS ===== // ===== FUNÇÕES AVANÇADAS ===== // ===== FUNÇÕES ESTATÍSTICAS ===== // ===== FUNÇÕES DE MATRIZES ===== // ===== HISTÓRICO ===== // ===== ENTRADA ===== // ===== MENU ===== Cada grupo contém funções específicas para modularizar o código e facilitar futuras expansões.

--Histórico e Exportação--

Todas as operações são armazenadas no vetor global historico[], limitado a 50 entradas (MAX_HIST = 50).

Exemplo de exportação:

ID,Tipo,A,B,Resultado 1,Soma,5.00,2.00,7.00 2,Divisão,10.00,2.00,5.00 3,Potência,2.00,3.00,8.00 Para salvar o histórico:

Escolha a opção 21 - Salvar Histórico

O arquivo historico.csv será criado no diretório atual do programa.

--Exemplo de Execução--

==== CALCULADORA MODULAR ====

Soma
Subtração
Multiplicação
Divisão ...
Salvar Histórico
Sair Escolha: 1 Digite um número: 10 Digite um número: 5 Resultado = 15.00 Visualização do histórico:
=== HISTÓRICO DE OPERAÇÕES ===

[1] Soma (10.00, 5.00) = 15.00 --Tecnologias Utilizadas-- Linguagem C (padrão ANSI)

Bibliotecas:

stdio.h – Entrada/Saída

stdlib.h – Funções utilitárias

string.h – Manipulação de strings

math.h – Funções matemáticas
