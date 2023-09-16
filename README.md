<h1 align="center" id="title">Arduino Power meter system with Internal PLC</h1>

<p align="center"><img src="https://s6.uupload.ir/files/layer_510_o37r.png" alt="project-image"></p>

<h3><strong>Features</strong></h3>
<ul>
<li>Instant display (voltage, power factor, current, power, frequency)</li>
<li>Ability to set automation in 12 modes and 4 relays (Internal PLC)</li>
<li>Ability to connect to MATLAB software</li>
<li>Ability to connect to the battery</li>
<li>Maximum measurable voltage: 280 volts (two-phase, single-phase)</li>
<li>The maximum measurable current is 100 amperes (using CT 100:1)</li>
<li>The maximum measurable frequency is 60 Hz</li>
<li>Voltage measurement accuracy 0.1 v</li>
<li>Current measurement accuracy 0.2 A</li>
<li>The accuracy of power measurement is 0.4 W</li>
<li>Frequency measurement accuracy of 0.1 Hz</li>
<li>The accuracy of power factor measurement is 0.01%</li>
</ul>
<p><strong>point</strong>:By changing the resistances of <strong>R17</strong> and <strong>R16</strong> in <strong>PZEM</strong>, it is possible to measure the voltage of more than <strong>280 volts</strong> (This is a voltage divider circuit).</p>
<p>For example, if <strong>R17</strong> is equal to <strong>2 megaohms</strong> and <strong>R16</strong> is equal to <strong>750 ohms</strong>, the voltage can be measured up to <strong>500 volts</strong>.</p>
<p>It is also necessary to make changes in the Arduino codes, Additional information in the folder <span style="text-decoration: underline;"><strong>500 volts</strong></span></p>
*point 2:This system also supports Modbus protocol. You can add this potkal to it. And it was in contact with other industrial equipment such as HME and PLCs

____________________________________________________________________________________________
<h3><strong>required pieces ::</strong></h3>
<table border="1">
<tbody>
<tr>
<td>
<h4>Electronic Components</h4>
</td>
<td>
<blockquote>Number</blockquote>
</td>
</tr>
<tr>
<td>Arduino Nano</td>
<td>1</td>
</tr>
<tr>
<td>PZEM004t</td>
<td>1</td>
</tr>
<tr>
<td>Liquid Crystal Displays (Character LCD)</td>
<td>1</td>
</tr>
<tr>
<td>4-channel relay module</td>
<td>1</td>
</tr>
<tr>
<td>push button</td>
<td>5</td>
</tr>
<tr>
<td>switch</td>
<td>1</td>
</tr>
<tr>
<td>Potentiometer 10 kilo ohms</td>
<td>1</td>
</tr>
<tr>
<td>10 kilo ohm resistance</td>
<td>5</td>
</tr>
<tr>
<td>n-channel MOSFET</td>
<td>1</td>
</tr>
</tbody>
</table>

____________________________________________________________________________________________


<h3>Test video&nbsp;</h3>
<p>Connecting power meter to MATLAB and view the data on the chart <a href="https://youtu.be/Np4y_KRA4oQ">https://youtu.be/Np4y_KRA4oQ</a></p>
<p>voltage measurement test <a href="https://youtu.be/dCQaTeNKbkk">https://youtu.be/dCQaTeNKbkk</a></p>
<p>current measurement test <a href="https://youtu.be/r_vkd0LcIXw">https://youtu.be/r_vkd0LcIXw</a></p>
<p>Relay function test <a href="https://youtu.be/pQEmvJ6B6WI">https://youtu.be/pQEmvJ6B6WI</a></p>
<p>&nbsp;</p>
<p>&nbsp;</p>

____________________________________________________________________________________________

<h3>Internal PLC settings :</h3>
<p>To access the settings menu, we must first turn the <strong>MODE</strong> key on and set the required parameters with the <strong>arrow keys</strong>.</p>
<table border="1">
<tbody>
<tr>
<td><strong>parameter in the settings menu</strong></td>
<td><strong>use</strong></td>
</tr>
<tr>
<td>OVER Voltage</td>
<td>Maximum voltage limit</td>
</tr>
<tr>
<td>LOW Voltage</td>
<td>Minimum voltage&nbsp;</td>
</tr>
<tr>
<td>OVER Current</td>
<td>maximum current limit</td>
</tr>
<tr>
<td>LOW Frequency</td>
<td>minimum frequency</td>
</tr>
<tr>
<td>OVER Frequency</td>
<td>Maximum frequency limit</td>
</tr>
<tr>
<td>LOW POWER FACTOR 1</td>
<td>steps, one power factors</td>
</tr>
<tr>
<td>LOW POWER FACTOR 2</td>
<td>steps, two power factors</td>
</tr>
<tr>
<td>LOW POWER FACTOR 3</td>
<td>steps, three power factors</td>
</tr>
<tr>
<td>TMS 1 SET</td>
<td>timer relay one</td>
</tr>
<tr>
<td>TMS 2 SET</td>
<td>timer relay two</td>
</tr>
<tr>
<td>TMS 3 SET</td>
<td>timer relay three</td>
</tr>
<tr>
<td>TMS 4 SET</td>
<td>timer relay four</td>
</tr>
<tr>
<td>R1</td>
<td>set the operation mode of relay one</td>
</tr>
<tr>
<td>R2</td>
<td>set the operation mode of relay two</td>
</tr>
<tr>
<td>R3</td>
<td>set the operation mode of relay three</td>
</tr>
<tr>
<td>R4</td>
<td>set the operation mode of relay four</td>
</tr>
</tbody>
</table>
<p>After making the settings, turn the <strong>MODE</strong> key to the off position so that the data is stored in the <strong>permanent memory</strong> of the controller</p>
<p>* Each relay timer unit is 100 milliseconds</p>
____________________________________________________________________________________________

<h3>A variety of performance modes (R1,R2,R3,R4):</h3>
<p>1- reverse time overcurrent function</p>
2- Additional constant time flow function<br />
3-Overvoltage function<br />
4- voltage reduction function<br />
5- frequency reduction function<br />
6- frequency increase function<br />
7- Function of the function of going out of normal mode (frequency, voltage, current)<br />
8-Function of power factor steps of one<br />
9-Function of power factor steps of two<br />
10- Function of power factor steps of three<br />
11-The operation of voltage out of normal mode<br />
12-&nbsp;Function of frequency out of normal mode</p>
