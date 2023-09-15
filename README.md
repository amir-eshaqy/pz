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
</tr>
</tbody>
</table>
<h3>Test video&nbsp;</h3>
<p>Connecting power meter to MATLAB and view the data on the chart <a href="https://youtu.be/Np4y_KRA4oQ">https://youtu.be/Np4y_KRA4oQ</a></p>
<p>voltage measurement test <a href="https://youtu.be/dCQaTeNKbkk">https://youtu.be/dCQaTeNKbkk</a></p>
<p>current measurement test <a href="https://youtu.be/r_vkd0LcIXw">https://youtu.be/r_vkd0LcIXw</a></p>
<p>Relay function test <a href="https://youtu.be/pQEmvJ6B6WI">https://youtu.be/pQEmvJ6B6WI</a></p>
<p>&nbsp;</p>
<p>&nbsp;</p>
