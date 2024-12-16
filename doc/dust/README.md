# DUST protocol

## Description

## Packet structure

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-wa1i{font-weight:bold;text-align:center;vertical-align:middle}
.tg .tg-uzvj{border-color:inherit;font-weight:bold;text-align:center;vertical-align:middle}
.tg .tg-7btt{border-color:inherit;font-weight:bold;text-align:center;vertical-align:top}
</style>
<table class="tg"><thead>
  <tr>
    <td class="tg-wa1i" rowspan="11">DUST<br>PACKET</td>
    <td class="tg-uzvj" rowspan="4">HEADER<br>(1byte)</td>
    <td class="tg-7btt">OPCODE<br>(2bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">LENGTH<br>(2bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">PACKET NUMBER<br>(12bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">CHECKSUM<br>(16bits)</td>
  </tr>
  <tr>
    <td class="tg-wa1i" rowspan="6">PAYLOAD<br>(32-256bytes)</td>
    <td class="tg-wa1i">DATA[0]</td>
  </tr>
  <tr>
    <td class="tg-wa1i">DATA[1]</td>
  </tr>
  <tr>
    <td class="tg-wa1i">DATA[2]</td>
  </tr>
  <tr>
    <td class="tg-wa1i">...</td>
  </tr>
  <tr>
    <td class="tg-wa1i">DATA[n-1]</td>
  </tr>
  <tr>
    <td class="tg-wa1i">DATA[n]</td>
  </tr>
  <tr>
    <td class="tg-wa1i">CRC16<br>(2bytes)</td>
    <td class="tg-wa1i">CRC</td>
  </tr></thead>
</table>

### OPCODE (2 bits wide)

| OPCODE     | VALUE |
|------------|-------|
| CONNECT    | 0x00  |
| DISCONNECT | 0x01  |
| DATA       | 0x02  |
| ERROR      | 0x03  |

### LENGTH (2 bits wide)

| LENGTH     | VALUE |
|------------|-------|
| BYTE32     | 0x00  |
| BYTE64     | 0x01  |
| BYTE128    | 0x02  |
| BYTE256    | 0x03  |

### PACKET NUMBER (12 bits wide)

### CHECKSUM (16 bits wide)

## Connection establishment (handshake)

```mermaid
sequenceDiagram
    UPDATER->>DEVICE: CONNECT PACKET
    DEVICE-->>UPDATER: CONNECT ACK PACKET
```

### CONNECT PACKET

<table class="tg"><thead>
  <tr>
    <td class="tg-wa1i" rowspan="11">DUST<br>PACKET</td>
    <td class="tg-uzvj" rowspan="4">HEADER<br>(4bytes)</td>
    <td class="tg-7btt">0x00<br>(2bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">0x00<br>(2bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">0x00<br>(12bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">0xffff<br>(16bits)</td>
  </tr>
  <tr>
    <td class="tg-wa1i" rowspan="6">PAYLOAD<br>(32-256bytes)</td>
    <td class="tg-wa1i">0xcc</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xcc</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xcc</td>
  </tr>
  <tr>
    <td class="tg-wa1i">...</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xcc</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xcc</td>
  </tr>
  <tr>
    <td class="tg-wa1i">CRC16<br>(2bytes)</td>
    <td class="tg-wa1i">0x56dd<br></td>
  </tr></thead>
</table>

### CONNECT ACK PACKET

<table class="tg"><thead>
  <tr>
    <td class="tg-wa1i" rowspan="11">DUST<br>PACKET</td>
    <td class="tg-uzvj" rowspan="4">HEADER<br>(4bytes)</td>
    <td class="tg-7btt">0x00<br>(2bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">0x00<br>(2bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">0x00<br>(12bits)</td>
  </tr>
  <tr>
    <td class="tg-7btt">0xffff<br>(16bits)</td>
  </tr>
  <tr>
    <td class="tg-wa1i" rowspan="6">PAYLOAD<br>(32-256bytes)</td>
    <td class="tg-wa1i">0xaa</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xaa</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xaa</td>
  </tr>
  <tr>
    <td class="tg-wa1i">...</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xaa</td>
  </tr>
  <tr>
    <td class="tg-wa1i">0xaa</td>
  </tr>
  <tr>
    <td class="tg-wa1i">CRC16<br>(2bytes)</td>
    <td class="tg-wa1i">0xa17f<br></td>
  </tr></thead>
</table>