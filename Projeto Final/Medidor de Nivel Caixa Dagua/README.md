                            ![Logo](https://user-images.githubusercontent.com/40214038/63216360-4d2ae000-c10a-11e9-9053-66f0a1c93a1a.png)

# Sensor de Nível de Caixa D'água com Arduino

  O projeto tem como objetivo desenvolver um sistema que forneça informações referente ao nível de líquido contido num reservatório, utilazando comunicação de rádio frequência e o acionamento automática de uma bomba responsável por manter o reservatório cheio.

Componentes:
- Placas Arduino Uno; 
- Sensor Ultrassônico HC-SR04;
- Emissore e Receptore de Radio Frequência 2,4ghz Nrf24l01;
- Protoboards;
- Led;
- Registor;
- Jump Macho/Fêmea;
-  Display LCD Gráfico 128×64 Backlight Azul;
-  Botão tipo push-button

O sistema contém dois conjuntos de dispositivos.

O primeiro é composto por:
  - Placa Arduino Uno;
  - Sensor Ultrassônico;
  - Emissore e Receptore de Radio Frequência;
  - Led (simula o acionamento da bomba)
  
  <p>Fica preso junto ao reservatório, é responsável por medir o nível de líquido utilizando o sensor de distância ultrasônico preso a tampa do reservatório, com os dois sensores trig e echo apontando para o fundo, assim é possível medir a altura entre a parte superior do reservatório e o líquido.<br \> 
  As medidas coletadas são analizadas e se o nível de líquido atingir o nível baixo, a bomba é acionada (a bomba está sendo representada pelo LED) e as informações enviadas para o segundo conjunto.

O segundo é composto por:
  - Placa Arduino Uno;
  - Display LCD;
  - 2 Botões
  
 <p>Ao ligar o sistema precionando o botão, a informação do nível da água e estado da bomba (ligada/desligada) enviadas pelo primeiro conjunto, são tratados e exibidos no display, assim é possível acompanhar visualmente em tempo real, o nível do reservatório e o acionamento da bomba.<br \>
  A bomba é acionada de forma automática pelo dispositivo acoplado ao reservatório, mas por segurança, é possível ligar e desligar a mesma, utilizando um segundo botão próximo ao display.


![MaqEstadoLogo](https://github.com/AndreSalgueiro/SE/blob/master/Projeto%20Final/Medidor%20de%20Nivel%20Caixa%20Dagua/Maq_etado_inicial.jpg)
