                            
![Logo](https://user-images.githubusercontent.com/40214038/63216360-4d2ae000-c10a-11e9-9053-66f0a1c93a1a.png)
# Sensor de Nível de Caixa D'água com Arduino

  O projeto tem como objetivo desenvolver um sistema que forneça informações referente ao nível de líquido contido num reservatório, utilazando comunicação de rádio frequência com acionamento automática de uma bomba responsável por manter o reservatório cheio.

Componentes:
- Placas Arduino Uno; 
- Sensor Ultrassônico HC-SR04;
- Emissore e Receptore de Radio Frequência 2,4ghz Nrf24l01;
- Protoboards;
- Led;
- Registor;
- Jump Macho/Fêmea;
- Display LCD Gráfico 128×64 Backlight Azul;
- Botão tipo push-button
- Potenciômetro Linear de 100K  

O sistema contém dois conjuntos de dispositivos.

O primeiro é composto por:
  - Placa Arduino Uno;
  - Sensor Ultrassônico;
  - Emissor e Receptore de Radio Frequência;
  - Led (simula o acionamento da bomba)
  
  <p>Fica preso junto ao reservatório, é responsável por medir o nível de líquido utilizando o sensor de distância ultrasônico, preso a tampa do reservatório apontando em direção ao fundo do mesmo, assim é possível medir a altura entre a parte superior do reservatório e o líquido.<br \> 
  As medidas coletadas são analizadas e se, o nível de líquido atingir o nível baixo ou alto, a bomba é ligada ou desligada respectivamente e as informações enviadas para o segundo conjunto (a bomba está sendo representada pelo LED).

O segundo é composto por:
  - Placa Arduino Uno;
  - Display LCD;
  - 3 Botões
  - Potenciômetro
  
 <p>Ao ligar o sistema precionando o botão, as informações enviadas pelo primeiro conjunto, são tratadas e exibidas no display, assim é possível acompanhar visualmente e em tempo real, o nível do reservatório, o status da bomba, o modo de operação do sistema e as configurações de nível alto/baixo do reservatório.<br \>
  A bomba é ligada e desligada de forma automática pelo dispositivo acoplado ao reservatório, respeitando os níveis baixo e alto mas também é possível ligar e desligar a bomba de fomarma arbritária, bastando precionar o botão do modo manual, com este modo acionado, basta precionar o botão de liga/desliga da bomba.
  Por questão de segurança, mesmo no modo manual, se a bomba for acionada e o nível do reservatório atingir o máximo, automaticamente a bomba é desligada, evitando desperdício caso o usuário tenha esquecido a bomba ligada no modo manual.


![MaqEstadoLogo](https://github.com/AndreSalgueiro/SE/blob/master/Projeto%20Final/Medidor%20de%20Nivel%20Caixa%20Dagua/Imagens/Maquina_Estado.png)

![Display](https://github.com/AndreSalgueiro/SE/blob/master/Projeto%20Final/Medidor%20de%20Nivel%20Caixa%20Dagua/Imagens/Representacao%20Grafica%20-%20Display_bb.png)

![SensorUltrasonico](https://github.com/AndreSalgueiro/SE/blob/master/Projeto%20Final/Medidor%20de%20Nivel%20Caixa%20Dagua/Imagens/Representacao%20Grafica%20-%20Sensor%20Ultrasonico_bb.png)
