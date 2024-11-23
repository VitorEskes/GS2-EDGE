# 🌞💡 **Synthica - Lâmpada Inteligente** 💡🌞

Bem-vindo ao projeto **Synthica**, uma solução inovadora de iluminação inteligente desenvolvida para **economizar energia elétrica** e **aproveitar a energia solar natural**. Este projeto utiliza tecnologias IoT com o ESP32, sensores de luz e presença, e uma arquitetura robusta para garantir eficiência energética em diferentes ambientes.

---

## 🌟 **Funcionalidades**
- **🌞 Economia de Energia:** A lâmpada adapta-se automaticamente à luz ambiente, utilizando o sensor **LDR**. Se a luz ambiente for suficiente, a lâmpada permanece apagada, economizando energia.
- **👣 Sensor de Presença:** O sensor **PIR** detecta movimento e acende a lâmpada apenas quando necessário, evitando o desperdício de energia em ambientes vazios.
- **☁️ Integração em Nuvem:** A comunicação é feita por meio do protocolo **MQTT**, que permite a troca de dados em tempo real entre os dispositivos e o servidor.
- **📊 Monitoramento em Tempo Real:** Dashboard criado para acompanhar os dados coletados pelos sensores de presença e luminosidade. Ele apresenta gráficos dinâmicos para facilitar a análise das variáveis.
- **🔒 Controle Remoto:** Integração com a nuvem via **Postman** para enviar e receber dados do sistema em tempo real.
- **⚡ Eficiência Energética:** A lâmpada é capaz de operar de forma autônoma, aproveitando o máximo da energia solar disponível.

---

## ⚙️ **Componentes Utilizados**
- **ESP32**: Microcontrolador principal para processar os dados dos sensores e comunicar com a nuvem.
- **Sensor LDR**: Sensor de luz para medir a luminosidade ambiental.
- **Sensor PIR**: Sensor de movimento para detectar presença e acionar a lâmpada.
- **MQTT Broker**: Protocolo para comunicação entre dispositivos IoT e servidor.
- **Postman**: Ferramenta para testar as requisições MQTT e simular o comportamento do sistema.
- **Azure VM**: Plataforma em nuvem usada para armazenar e processar os dados.
- **Wokwi**: Simulador para testar e validar o projeto de forma interativa.
- **MongoDB**: Banco de dados para armazenar os dados históricos de sensores.

---

## 🔍 **Visualização do Wokwi**

A seguir, apresentamos uma visualização interativa do Wokwi. Esse dashboard foi criado para monitorar dados em tempo real, permitindo uma análise precisa e intuitiva de variáveis críticas para o projeto. Ele combina gráficos dinâmicos com uma interface amigável para facilitar a tomada de decisões.

![Dashboard Interativo](https://i.imgur.com/gHrBlWc.png)

---

## 🖼️ **Arquitetura do Sistema**

Abaixo está a arquitetura completa do sistema, mostrando a integração entre sensores, ESP32, MQTT, e a nuvem.  

![Arquitetura do Sistema](https://i.imgur.com/YDT2x59.png)

### **Descrição da Arquitetura**
1. **IoT (Sensores)**: Os sensores de luz e movimento capturam os dados ambientais. O sensor **LDR** mede a luminosidade e o sensor **PIR** detecta a presença no ambiente.
2. **ESP32**: O microcontrolador processa as informações dos sensores e envia para o broker MQTT, que gerencia as mensagens entre os dispositivos.
3. **Backend (MQTT Broker)**: O broker recebe as mensagens de sensores e controla a comunicação entre dispositivos, enviando as informações para a nuvem ou outras aplicações.
4. **Cloud (Azure)**: Plataforma em nuvem usada para análise, persistência e visualização dos dados recebidos, além de fornecer monitoramento remoto.
5. **Aplicações**: O dashboard interativo exibe os dados em tempo real, permitindo controle e análise detalhada do consumo energético e do ambiente monitorado.

---

## 🚀 **Como Executar o Projeto**

### **1. Configuração do Hardware no Wokwi**
- Crie um novo projeto no **Wokwi** e adicione o **ESP32**, **Sensor LDR** e **Sensor PIR** conforme o diagrama de conexão.  
- Ajuste os pinos no código conforme os dispositivos conectados.

### **2. Configuração do Broker MQTT**
- Utilize o seguinte broker para a comunicação:
  - **Endereço do Broker:** `broker.hivemq.com`  
  - **Porta:** `1883`  
  - **Tópicos:**
    - **Publicação (Sensor de Luz):** `/TEF/devin/attrs/l`
    - **Publicação (Sensor de Presença):** `/TEF/devin/attrs/s`
    - **Inscrição (Comando de Controle):** `/TEF/devin/cmd`

### **3. Executar o Código**
- Faça o upload do código para o **ESP32** no **Wokwi** e inicie a simulação.
- Use o **Postman** para enviar e testar as mensagens MQTT (pub/sub).

### **4. Monitoramento no Dashboard**
- Acesse o **Dashboard** no **Azure** para acompanhar os dados dos sensores em tempo real.
- Utilize a interface para ajustar configurações ou visualizar os dados históricos.

---

## 👥 **Equipe**

- **Gabriel Matias**: [LinkedIn](https://www.linkedin.com/in/vitor-eskes-2727bb2b6/)  
- **Nathan Craveiro**: [LinkedIn](https://www.linkedin.com/in/nathan-amin-6900462b6/)  
- **Vitor Eskes**: [LinkedIn](https://www.linkedin.com/in/gabriel-matias-simoes-5a55562b7/)  

---

**✨ Feito com paixão pelo time Synthica!**


> **Nota:** Os alunos do professor Fabio Cabrini agradecem por sua dedicação e por tornar as aulas tão inspiradoras e enriquecedoras. Obrigado, professor!

