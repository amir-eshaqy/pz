<h1 align="center" id="title">Arduino Power analyzer system with Internal PLC</h1>

<p align="center"><img src="https://s6.uupload.ir/files/layer_510_o37r.png" alt="project-image"></p>

<h3><strong><span style="color: #800000;">Features</span></strong></h3>
<ul style="list-style-type: circle;">
<li><span style="color: #000000;">Instant display (voltage, power factor, current, power, frequency)</span></li>
<li><span style="color: #000000;">Ability to set automation in 12 modes and 4 relays (Internal PLC)</span></li>
<li><span style="color: #000000;">Ability to connect to MATLAB software</span></li>
<li><span style="color: #000000;">Ability to connect to the battery</span></li>
<li><span style="color: #000000;">Maximum measurable voltage: 280 volts (two-phase, single-phase)</span></li>
<li><span style="color: #000000;">The maximum measurable current is 100 amperes (using CT 100:1)</span></li>
<li><span style="color: #000000;">The maximum measurable frequency is 60 Hz</span></li>
<li><span style="color: #000000;">Voltage measurement accuracy 0.1 v</span></li>
<li>Current measurement accuracy 0.2 A</li>
<li>The accuracy of power measurement is 0.4 W</li>
<li>Frequency measurement accuracy of 0.1 Hz</li>
<li>The accuracy of power factor measurement is 0.01%</li>
</ul>
<p><strong><span style="color: #ff9900;">point</span></strong>:By changing the resistances of <span style="text-decoration: underline;"><strong>R17</strong> </span>and <span style="text-decoration: underline;"><strong>R16</strong> </span>in <span style="text-decoration: underline;"><strong>PZEM</strong></span>, it is possible to measure the voltage of more than <strong>280 volts</strong> (This is a voltage divider circuit).</p>
<p>For example, if <span style="text-decoration: underline;"><strong>R17</strong> </span>is equal to <span style="text-decoration: underline;"><strong>2 megaohms</strong></span> and <span style="text-decoration: underline;"><strong>R16</strong> </span>is equal to <span style="text-decoration: underline;"><strong>750 ohms</strong></span>, the voltage can be measured up to <strong>500 volts</strong>.</p>
<p>It is also necessary to make changes in the Arduino codes, which can be seen in the <span style="text-decoration: underline;"><strong>power_V8</strong></span> file</p>


required pieces ::: 
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
</tr>
</tbody>
</table>

