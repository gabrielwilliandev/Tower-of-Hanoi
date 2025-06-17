# 🧠 Projeto Final — Estrutura de Dados

## 🏗️ Simulador da Torre de Hanói (Terminal)

### 🌟 Objetivo

Este projeto tem como objetivo desenvolver um simulador da **Torre de Hanói**, utilizando **estruturas de dados (pilhas e listas encadeadas)**. A simulação é realizada via terminal e permite ao usuário interagir com o jogo, movendo os discos entre as torres, escolhendo o número de discos e visualizando um histórico de partidas.

---

### 👥 Integrantes do Grupo

* Ana Vitória Resende
* Bianca Maria
* Gabriel Willian

---

### 🧩 Funcionalidades

* [x] Seleção do número de discos antes de iniciar o jogo
* [x] Movimento dos discos entre as torres com validações
* [x] Reinício da partida a qualquer momento
* [x] Registro de histórico com:

  * Nome do jogador
  * Número de movimentos
  * Quantidade de discos
  * Data e hora de encerramento da partida
* [x] Armazenamento do histórico:

  * Em uma **lista encadeada** na memória
  * Em um **arquivo de texto** permanente
* [x] Busca por histórico:

  * Por nome de jogador
  * Por data da partida

---

### 💻 Tecnologias utilizadas

* Linguagem C
* Terminal (interface textual)
* Estruturas de Dados:

  * Pilhas (para as torres)
  * Lista Duplamente Encadeada (para o histórico)

---

### 🗂️ Organização do Projeto

* `main.c`: Função principal e menu
* `discos.c/h`: Lógica das pilhas e movimentação dos discos
* `historico.c/h`: Estrutura e manipulação do histórico
* `historico.txt`: Arquivo com registros das partidas (criado ao salvar um nome)

---

### 📋 Como Compilar e Executar

```bash
gcc main.c discos.c historico.c -o hanoi
./hanoi
```

---

### 🗓️ Apresentação

* 🗕️ **Data da apresentação:** 17/06
* ⏱️ **Duração:** até 10 minutos
* 🎥 Será demonstrada a execução completa do jogo com suas funcionalidades

---

### 🦚 Critérios atendidos

* [x] Uso adequado de estruturas de dados (pilhas e listas)
* [x] Interação com o usuário via terminal
* [x] Organização e clareza do código
* [x] Organização do repositório (Git e GitHub)
* [x] Participação individual (commits por integrante)

---

### 📁 Histórico salvo no arquivo `historico.txt` no formato:

```
Nome: Gabriel
Data: 2025/06/17
Modo: 3 discos
Movimentos: 7
```

---

### 📌 Referências

* [OBMEP: Torre de Hanói](http://clubes.obmep.org.br/blog/torre-de-hanoi/)
* [UNESP - Torre de Hanói](https://www.ibilce.unesp.br/Home/Departamentos/Matematica/labmat/torre_de_hanoi.pdf)

---
