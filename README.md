<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
<meta name="generator" content="http://www.nongnu.org/elyxer/"/>
<meta name="create-date" content="2016-12-30"/>
<link rel="stylesheet" href="lyx.css" type="text/css" media="all"/>

</head>
<body>
<div id="globalWrapper">
<h1 class="title">
18 Triangulation Algorithms for 2D Positioning (also known as the Resection Problem): benchmarking, software, source code in C, and documentation
</h1>
<h2 class="author">
<a class="URL" href="http://www.telecom.ulg.ac.be/publi/Author/PIERLOT-V.html">Vincent Pierlot</a> and <a class="URL" href="http://www.telecom.ulg.ac.be/publi/Author/VAN-DROOGENBROECK-M.html">Marc Van Droogenbroeck</a>, <br/>
<a class="URL" href="http://www.montefiore.ulg.ac.be">Montefiore Research Institute</a>, University of Liège, Belgium
</h2>
<div class="Standard">
<div class="center">
Scientific paper available in PDF <a class="URL" href="http://ieeexplore.ieee.org/xpl/articleDetails.jsp?tp=&amp;arnumber=6693716">here [IEEE]</a> or <a class="URL" href="http://orbi.ulg.ac.be/bitstream/2268/157469/1/Pierlot2014ANewThree.pdf">here</a>; <a class="URL" href="http://www2.ulg.ac.be/telecom/publi/publications/pierlot/Pierlot2014ANewThree/">HTML version of the article here</a>
</div>

</div>
<div class="Standard">
<div class="center">
<b>Keywords:</b> 2D positioning, triangulation, mobile robot positioning, algorithms, benchmarking, software, C source code, <a class="URL" href="doc/index.html">documentation</a>, ToTal algorithm 
</div>

</div>
<div class="Standard">
<div class="float">
<div class="figure">
<div class="center">
<img class="embedded" src="triangulation-setup-color.png" alt="figure triangulation-setup-color.png" style="width: 261px; max-width: 1044px; height: 204px; max-height: 816px;"/>

</div>
<div class="PlainVisible">
<div class="center">
Triangulation setup in the 2D plane. <span class="formula"><i>R</i></span> denotes a device such as a robot. <span class="formula"><i>B</i><sub>1</sub></span>, <span class="formula"><i>B</i><sub>2</sub></span>, and <span class="formula"><i>B</i><sub>3</sub></span> are the beacons. <span class="formula"><i>α</i><sub>1</sub></span>, <span class="formula"><i>α</i><sub>2</sub></span>, and <span class="formula"><i>α</i><sub>3</sub></span> are the angles for <span class="formula"><i>B</i><sub>1</sub></span>, <span class="formula"><i>B</i><sub>2</sub></span>, and <span class="formula"><i>B</i><sub>3</sub></span> respectively, relative to the robot reference orientation <span class="formula"><i>θ</i></span>. Our triangulation algorithm computes the robot position and orientation based on these angles.
</div>

</div>

</div>

</div>

</div>
<div class="Standard">
This page complements the paper &ldquo;A New Three Object Triangulation Algorithm for Mobile Robot Positioning&rdquo;, published in IEEE Transactions on Robotics (see <span class="bibcites">[<a class="bibliocite" name="cite-15" href="#biblio-15"><span class="bib-index">15</span></a>]</span>); this algorithm was introduced in <span class="bibcites">[<a class="bibliocite" name="cite-14" href="#biblio-14"><span class="bib-index">14</span></a>]</span> and used for the Eurobot contest in an original setup (see <span class="bibcites">[<a class="bibliocite" name="cite-16" href="#biblio-16"><span class="bib-index">16</span></a>]</span>). It is important to note that the “three object triangulation problem” is also known as the “three point resection problem” in the surveying engineering research area. 
</div>
<div class="Standard">
We provide the C source code, programs, <a class="URL" href="doc/index.html">documentation</a>, as well as the instructions to reproduce all the results given in the paper. In Section <a class="Reference" href="#sec:Programs">2↓</a>, we explain how to download and use the program. See Section <a class="Reference" href="#sec:Simulations">4↓</a> for the command lines used to generate the graphics and Section <a class="Reference" href="#sec:Benchmarks">1↓</a> for the command lines used to run the benchmark, reproduced in Table <a class="Reference" href="#tab:Comparison-algorithms">1↓</a>. We also remind our algorithm ToTal in Section <a class="Reference" href="#sec:ToTal-Algorithm">3↓</a>.
</div>
<h1 class="Section">
<a class="toc" name="toc-Section-1">1</a> Benchmarks
</h1>
<div class="Standard">
<a class="Label" name="sec:Benchmarks"> </a>The last column of the following table provides the command and arguments to obtain the execution times of the different algorithms:
</div>
<div class="Standard">
<div class="float">
<a class="Label" name="tab:Comparison-algorithms"> </a><div class="table">
<div class="center">
<table>
<tr>
<td align="right" valign="top">

</td>
<td align="right" valign="top">
Algorithm
</td>
<td align="center" valign="top">
<span class="formula"> + </span>
</td>
<td align="center" valign="top">
<span class="formula"> × </span>
</td>
<td align="center" valign="top">
<span class="formula"> ⁄ </span>
</td>
<td align="center" valign="top">
<span class="formula"><span class="sqrt"><span class="radical">√</span><span class="ignored">(</span><span class="root"><i>x</i></span><span class="ignored">)</span></span></span>
</td>
<td align="center" valign="top">
<i>trigo</i>
</td>
<td align="center" valign="top">
time <span class="formula">(<i>s</i>) <sup>†</sup></span>
</td>
<td align="left" valign="top">
Command line
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-14" href="#biblio-14"><span class="bib-index">14</span></a>, <a class="bibliocite" name="cite-15" href="#biblio-15"><span class="bib-index">15</span></a>]</span>
</td>
<td align="right" valign="top">
ToTal <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">30</span>
</td>
<td align="center" valign="top">
<span class="formula">17</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<b>0</b>
</td>
<td align="center" valign="top">
<b>2</b>
</td>
<td align="center" valign="top">
<b>0.163</b>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m1</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-11" href="#biblio-11"><span class="bib-index">11</span></a>]</span> 
</td>
<td align="right" valign="top">
Ligas <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">29</span>
</td>
<td align="center" valign="top">
<span class="formula">22</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<b>0</b>
</td>
<td align="center" valign="top">
<b>2</b>
</td>
<td align="center" valign="top">
<span class="formula">0.171</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m18</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-7" href="#biblio-7"><span class="bib-index">7</span></a>]</span>
</td>
<td align="right" valign="top">
Font-Llagunes <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">23</span>
</td>
<td align="center" valign="top">
<span class="formula">17</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<b>0</b>
</td>
<td align="center" valign="top">
<span class="formula">5</span>
</td>
<td align="center" valign="top">
<span class="formula">0.223</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m3</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-12" href="#biblio-12"><span class="bib-index">12</span></a>]</span> 
</td>
<td align="right" valign="top">
Cassini <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<b>19</b>
</td>
<td align="center" valign="top">
<b>8</b>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<b>0</b>
</td>
<td align="center" valign="top">
<span class="formula">4</span>
</td>
<td align="center" valign="top">
<span class="formula">0.249</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m22</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-2" href="#biblio-2"><span class="bib-index">2</span></a>]</span>
</td>
<td align="right" valign="top">
Cohen <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">37</span>
</td>
<td align="center" valign="top">
<span class="formula">15</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">4</span>
</td>
<td align="center" valign="top">
<span class="formula">0.272</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m10</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-1" href="#biblio-1"><span class="bib-index">1</span></a>]</span>
</td>
<td align="right" valign="top">
Easton <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">22</span>
</td>
<td align="center" valign="top">
<span class="formula">24</span>
</td>
<td align="center" valign="top">
<b>1</b>
</td>
<td align="center" valign="top">
<b>0</b>
</td>
<td align="center" valign="top">
<span class="formula">5</span>
</td>
<td align="center" valign="top">
<span class="formula">0.298</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m7</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-4" href="#biblio-4"><span class="bib-index">4</span></a>]</span>
</td>
<td align="right" valign="top">
McGillem <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">37</span>
</td>
<td align="center" valign="top">
<span class="formula">18</span>
</td>
<td align="center" valign="top">
<span class="formula">5</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">8</span>
</td>
<td align="center" valign="top">
<span class="formula">0.340</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m6</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-6" href="#biblio-6"><span class="bib-index">6</span></a>]</span>
</td>
<td align="right" valign="top">
Hmam <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">29</span>
</td>
<td align="center" valign="top">
<span class="formula">11</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">9</span>
</td>
<td align="center" valign="top">
<span class="formula">0.428</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m8</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-2" href="#biblio-2"><span class="bib-index">2</span></a>]</span>
</td>
<td align="right" valign="top">
Cohen <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">26</span>
</td>
<td align="center" valign="top">
<span class="formula">11</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">11</span>
</td>
<td align="center" valign="top">
<span class="formula">0.437</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m9</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-10" href="#biblio-10"><span class="bib-index">10</span></a>]</span>
</td>
<td align="right" valign="top">
Esteves <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">43</span>
</td>
<td align="center" valign="top">
<span class="formula">14</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">11</span>
</td>
<td align="center" valign="top">
<span class="formula">0.471</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m2</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-12" href="#biblio-12"><span class="bib-index">12</span></a>]</span> 
</td>
<td align="right" valign="top">
Collins <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">34</span>
</td>
<td align="center" valign="top">
<span class="formula">10</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">11</span>
</td>
<td align="center" valign="top">
<span class="formula">0.485</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m21</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-4" href="#biblio-4"><span class="bib-index">4</span></a>]</span>
</td>
<td align="right" valign="top">
McGillem <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">29</span>
</td>
<td align="center" valign="top">
<span class="formula">9</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">11</span>
</td>
<td align="center" valign="top">
<span class="formula">0.501</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m5</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-12" href="#biblio-12"><span class="bib-index">12</span></a>]</span> 
</td>
<td align="right" valign="top">
Kaestner <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">28</span>
</td>
<td align="center" valign="top">
<span class="formula">10</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">2</span>
</td>
<td align="center" valign="top">
<span class="formula">11</span>
</td>
<td align="center" valign="top">
<span class="formula">0.504</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m20</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-13" href="#biblio-13"><span class="bib-index">13</span></a>]</span>
</td>
<td align="right" valign="top">
Tsukiyama <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">52</span>
</td>
<td align="center" valign="top">
<span class="formula">22</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">5</span>
</td>
<td align="center" valign="top">
<span class="formula">14</span>
</td>
<td align="center" valign="top">
<span class="formula">0.596</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m12</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-5" href="#biblio-5"><span class="bib-index">5</span></a>]</span>
</td>
<td align="right" valign="top">
Casanova <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">52</span>
</td>
<td align="center" valign="top">
<span class="formula">21</span>
</td>
<td align="center" valign="top">
<span class="formula">4</span>
</td>
<td align="center" valign="top">
<span class="formula">5</span>
</td>
<td align="center" valign="top">
<span class="formula">14</span>
</td>
<td align="center" valign="top">
<span class="formula">0.609</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m4</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-9" href="#biblio-9"><span class="bib-index">9</span></a>]</span>
</td>
<td align="right" valign="top">
Tienstra <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">33</span>
</td>
<td align="center" valign="top">
<span class="formula">18</span>
</td>
<td align="center" valign="top">
<span class="formula">8</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">9</span>
</td>
<td align="center" valign="top">
<span class="formula">0.640</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m17</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-8" href="#biblio-8"><span class="bib-index">8</span></a>]</span>
</td>
<td align="right" valign="top">
Font-Llagunes <span class="formula"><sup>1</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">62</span>
</td>
<td align="center" valign="top">
<span class="formula">25</span>
</td>
<td align="center" valign="top">
<span class="formula">6</span>
</td>
<td align="center" valign="top">
<span class="formula">1</span>
</td>
<td align="center" valign="top">
<span class="formula">8</span>
</td>
<td align="center" valign="top">
<span class="formula">0.648</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m19</span></tt>
</td>

</tr>
<tr>
<td align="right" valign="top">
<span class="bibcites">[<a class="bibliocite" name="cite-3" href="#biblio-3"><span class="bib-index">3</span></a>]</span>
</td>
<td align="right" valign="top">
Madsen <span class="formula"><sup>2</sup></span>
</td>
<td align="center" valign="top">
<span class="formula">38</span>
</td>
<td align="center" valign="top">
<span class="formula">24</span>
</td>
<td align="center" valign="top">
<span class="formula">5</span>
</td>
<td align="center" valign="top">
<span class="formula">3</span>
</td>
<td align="center" valign="top">
<span class="formula">15</span>
</td>
<td align="center" valign="top">
<span class="formula">0.707</span>
</td>
<td align="left" valign="top">
<tt><span class="red">./triangulation -t3 -n1000000 -m14</span></tt>
</td>

</tr>

</table>
<div class="smallskip"> </div>
</div>
<div class="PlainVisible">
<span class="formula"> <sup>†</sup></span> For <span class="formula">10<sup>6</sup></span> executions on an Intel(R) Core(TM) i7 920 @ 2.67GHz.<div class="smallskip"> </div>
</div>
<div class="PlainVisible">
<span class="formula"><sup>1</sup></span> Geometric circle intersection<span class="hfill"> </span><span class="formula"><sup>2</sup></span> Trigonometric solution<div class="smallskip"> </div>
</div>
<div class="caption">
Table 1 Comparison of various triangulation algorithms to our ToTal algorithm (see <span class="bibcites">[<a class="bibliocite" name="cite-15" href="#biblio-15"><span class="bib-index">15</span></a>]</span>). 
</div>

</div>

</div>

</div>
<h1 class="Section">
<a class="toc" name="toc-Section-2">2</a> Programs<a class="Label" name="sec:Programs"> </a>
</h1>
<h2 class="Subsection">
<a class="toc" name="toc-Subsection-2.1">2.1</a> Download the C source code (zip package)
</h2>
<div class="Standard">
<a class="Label" name="sec:C-source-code"> </a>Follow <a class="URL" href="triangulation.zip">this link</a> to get the programs and C source code [<a class="URL" href="triangulation.zip">triangulation.zip</a>]. The package contains programs that you can directly use: 
</div>
<div class="Description">
<span class="Description-entry">bin_win32/triangulation.exe</span> for Windows users.
</div>
<div class="Description">
<span class="Description-entry">bin_i686/triangulation</span> for Linux 32 bits users.
</div>
<div class="Description">
<span class="Description-entry">bin_x86_64/triangulation</span> for Linux 64 bits users.
</div>
<h2 class="Subsection">
<a class="toc" name="toc-Subsection-2.2">2.2</a> Run the program by yourself
</h2>
<div class="Standard">
To run the program, copy the appropriate program (depending on your platform) into your current directory and type: 
</div>
<div class="Standard">
<div class="listing">
<pre class="listing">./triangulation
</pre>
</div>
 
</div>
<div class="Standard">
It generates a <span class="formula">201 × 201</span> grayscale PGM image named &ldquo;<span class="sans">map.pgm</span>&rdquo;, and a <span class="formula">201 × 201</span> color PPM image named &ldquo;<span class="sans">map.ppm</span>&rdquo;. These images are the ones shown in Fig. <a class="Reference" href="#fig:Image-generated-default">2↓</a>. It also generates the corresponding scale images named &ldquo;scale.pgm&rdquo;, and &ldquo;scale.ppm&rdquo;.<div class="float">
<a class="Label" name="fig:Image-generated-default"> </a><div class="figure">
<div class="center">
<img class="embedded" src="map.png" alt="figure map.png" style="max-width: 201px; max-height: 201px;"/>
<img class="embedded" src="map-color.png" alt="figure map-color.png" style="max-width: 201px; max-height: 201px;"/>

</div>
<div class="caption">
Figure 2 Images generated with default arguments (<tt><span class="red"> ./triangulation -t5 -m1 -s"0.01" -n"100" -S"-2.0" -E"+2.0" -p"201" -M2 -T1</span></tt> ).
</div>

</div>

</div>

</div>
<h2 class="Subsection">
<a class="toc" name="toc-Subsection-2.3">2.3</a> Compile the code by yourself. 
</h2>
<div class="Standard">
Take a look at the <tt>Makefile</tt>. There is no external library needed to compile the code, so the compilation should be rather straightforward. 
</div>
<h2 class="Subsection">
<a class="toc" name="toc-Subsection-2.4">2.4</a> Options when you run the program
</h2>
<div class="Standard">
<a class="URL" href="options.html">Click on this link to get the extensive list of options.</a>
</div>
<h1 class="Section">
<a class="toc" name="toc-Section-3">3</a> ToTal Algorithm
</h1>
<div class="Standard">
<a class="Label" name="sec:ToTal-Algorithm"> </a>
</div>
<h2 class="Subsection">
<a class="toc" name="toc-Subsection-3.1">3.1</a> Description
</h2>
<div class="Standard">
<div class="float">
<a class="Label" name="alg:final-version"> </a><div class="algorithm">
Given the three beacon coordinates <span class="formula"><span class="symbol">{</span><i>x</i><sub>1</sub>,  <i>y</i><sub>1</sub><span class="symbol">}</span></span>, <span class="formula"><span class="symbol">{</span><i>x</i><sub>2</sub>,  <i>y</i><sub>2</sub><span class="symbol">}</span></span>, <span class="formula"><span class="symbol">{</span><i>x</i><sub>3</sub>,  <i>y</i><sub>3</sub><span class="symbol">}</span></span>, and the three angles <span class="formula"><i>α</i><sub>1</sub></span>, <span class="formula"><i>α</i><sub>2</sub></span>, <span class="formula"><i>α</i><sub>3</sub></span>:<ol>
<li>
compute the modified beacon coordinates:<br/>
<span class="formula"><i>x</i>’<sub>1</sub> = <i>x</i><sub>1</sub> − <i>x</i><sub>2</sub>,     <i>y</i>’<sub>1</sub> = <i>y</i><sub>1</sub> − <i>y</i><sub>2</sub>,     <i>x</i>’<sub>3</sub> = <i>x</i><sub>3</sub> − <i>x</i><sub>2</sub>,     <i>y</i>’<sub>3</sub> = <i>y</i><sub>3</sub> − <i>y</i><sub>2</sub>, </span>
</li>
<li>
compute the three <span class="formula">cot(.)</span>:<br/>
<span class="formula"><i>T</i><sub>12</sub> = cot(<i>α</i><sub>2</sub> − <i>α</i><sub>1</sub>),     <i>T</i><sub>23</sub> = cot(<i>α</i><sub>3</sub> − <i>α</i><sub>2</sub>),     <i>T</i><sub>31</sub> = <span class="fraction"><span class="ignored">(</span><span class="numerator">1 − <i>T</i><sub>12</sub><i>T</i><sub>23</sub></span><span class="ignored">)/(</span><span class="denominator"><i>T</i><sub>12</sub> + <i>T</i><sub>23</sub></span><span class="ignored">)</span></span></span>
</li>
<li>
compute the modified circle center coordinates:<br/>
<span class="formula"><i>x</i>’<sub>12</sub> = <i>x</i>’<sub>1</sub> + <i>T</i><sub>12</sub> <i>y</i>’<sub>1</sub>,   <i>y</i>’<sub>12</sub> = <i>y</i>’<sub>1</sub> − <i>T</i><sub>12</sub> <i>x</i>’<sub>1</sub>, </span><br/>
<span class="formula"><i>x</i>’<sub>23</sub> = <i>x</i>’<sub>3</sub> − <i>T</i><sub>23</sub> <i>y</i>’<sub>3</sub>,   <i>y</i>’<sub>23</sub> = <i>y</i>’<sub>3</sub> + <i>T</i><sub>23</sub> <i>x</i>’<sub>3</sub>, </span><br/>
<span class="formula"><i>x</i>’<sub>31</sub> = (<i>x</i>’<sub>3</sub> + <i>x</i>’<sub>1</sub>) + <i>T</i><sub>31</sub> (<i>y</i>’<sub>3</sub> − <i>y</i>’<sub>1</sub>), </span><br/>
<span class="formula"><i>y</i>’<sub>31</sub> = (<i>y</i>’<sub>3</sub> + <i>y</i>’<sub>1</sub>) − <i>T</i><sub>31</sub> (<i>x</i>’<sub>3</sub> − <i>x</i>’<sub>1</sub>), </span>
</li>
<li>
compute <span class="formula"><i>k</i>’<sub>31</sub></span>:<br/>
<span class="formula"><i>k</i>’<sub>31</sub> = <i>x</i>’<sub>1</sub><i>x</i>’<sub>3</sub> + <i>y</i>’<sub>1</sub><i>y</i>’<sub>3</sub> + <i>T</i><sub>31</sub>(<i>x</i>’<sub>1</sub><i>y</i>’<sub>3</sub> − <i>x</i>’<sub>3</sub><i>y</i>’<sub>1</sub>), </span>
</li>
<li>
compute <span class="formula"><i>D</i></span> (if <span class="formula"><i>D</i> = 0</span>, return with an error):<br/>
<span class="formula"><i>D</i> = (<i>x</i>’<sub>12</sub> − <i>x</i>’<sub>23</sub>)(<i>y</i>’<sub>23</sub> − <i>y</i>’<sub>31</sub>) − (<i>y</i>’<sub>12</sub> − <i>y</i>’<sub>23</sub>)(<i>x</i>’<sub>23</sub> − <i>x</i>’<sub>31</sub>), </span>
</li>
<li>
compute the robot position <span class="formula"><span class="symbol">{</span><i>x</i><sub><i>R</i></sub>,  <i>y</i><sub><i>R</i></sub><span class="symbol">}</span></span> and return:<br/>
<span class="formula"><i>x</i><sub><i>R</i></sub> = <i>x</i><sub>2</sub> + <span class="fraction"><span class="ignored">(</span><span class="numerator"><i>k</i>’<sub>31</sub>(<i>y</i>’<sub>12</sub> − <i>y</i>’<sub>23</sub>)</span><span class="ignored">)/(</span><span class="denominator"><i>D</i></span><span class="ignored">)</span></span>,  <i>y</i><sub><i>R</i></sub> = <i>y</i><sub>2</sub> + <span class="fraction"><span class="ignored">(</span><span class="numerator"><i>k</i>’<sub>31</sub>(<i>x</i>’<sub>23</sub> − <i>x</i>’<sub>12</sub>)</span><span class="ignored">)/(</span><span class="denominator"><i>D</i></span><span class="ignored">)</span></span>.</span>
</li>

</ol>
<div class="caption">
Algorithm 1 Final version of the ToTal algorithm.
</div>

</div>

</div>

</div>
<h2 class="Subsection">
<a class="toc" name="toc-Subsection-3.2">3.2</a> The ToTal algorithm in C code
</h2>
<div class="Standard">
A version of ToTal in C is available: <a class="URL" href="doc/total_8c_source.html">total.c</a>. 
</div>
<h2 class="Subsection">
<a class="toc" name="toc-Subsection-3.3">3.3</a> The ToTal algorithm in Matlab/Octave code
</h2>
<div class="Standard">
A Matlab/Octave version is also available: <a class="URL" href="triangulationToTal.m">triangulationToTal.m</a>.
</div>
<h1 class="Section">
<a class="toc" name="toc-Section-4">4</a> Simulations
</h1>
<div class="Standard">
<a class="Label" name="sec:Simulations"> </a>To reproduce the figures given in the paper, run the command with the arguments as mentioned under each corresponding figure:<div class="float">
<a class="Label" name="fig:Position-and-orientation-error"> </a><div class="figure">
<div class="center">
<table>
<tr>
<td align="center" valign="top">
<img class="embedded" src="map-perr-10mdeg-M4.png" alt="figure map-perr-10mdeg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-perr-100mdeg-M4.png" alt="figure map-perr-100mdeg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-perr-1deg-M4.png" alt="figure map-perr-1deg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-perr-100mdeg-M2.png" alt="figure map-perr-100mdeg-M2.png" style="max-width: 201px; max-height: 201px;"/>

</td>

</tr>
<tr>
<td align="center" valign="top">
<img class="embedded" src="map-perr-10mdeg-M4-color.png" alt="figure map-perr-10mdeg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-perr-100mdeg-M4-color.png" alt="figure map-perr-100mdeg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-perr-1deg-M4-color.png" alt="figure map-perr-1deg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-perr-100mdeg-M2-color.png" alt="figure map-perr-100mdeg-M2-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>

</tr>
<tr>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"0.01" -T1 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"0.1" -T1 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"1.0" -T1 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M2 -s"0.1" -T1 -n1000</span></tt>
</td>

</tr>
<tr>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-10mdeg-M4.png" alt="figure map-oerr-10mdeg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-100mdeg-M4.png" alt="figure map-oerr-100mdeg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-1deg-M4.png" alt="figure map-oerr-1deg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-100mdeg-M2.png" alt="figure map-oerr-100mdeg-M2.png" style="max-width: 201px; max-height: 201px;"/>

</td>

</tr>
<tr>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-10mdeg-M4-color.png" alt="figure map-oerr-10mdeg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-100mdeg-M4-color.png" alt="figure map-oerr-100mdeg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-1deg-M4-color.png" alt="figure map-oerr-1deg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-oerr-100mdeg-M2-color.png" alt="figure map-oerr-100mdeg-M2-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>

</tr>
<tr>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"0.01" -T2 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"0.1" -T2 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"1.0" -T2 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M2 -s"0.1" -T2 -n1000</span></tt>
</td>

</tr>
<tr>
<td align="center" valign="top">
<img class="embedded" src="map-1D-10mdeg-M4.png" alt="figure map-1D-10mdeg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-1D-100mdeg-M4.png" alt="figure map-1D-100mdeg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-1D-1deg-M4.png" alt="figure map-1D-1deg-M4.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-1D-100mdeg-M2.png" alt="figure map-1D-100mdeg-M2.png" style="max-width: 201px; max-height: 201px;"/>

</td>

</tr>
<tr>
<td align="center" valign="top">
<img class="embedded" src="map-1D-10mdeg-M4-color.png" alt="figure map-1D-10mdeg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-1D-100mdeg-M4-color.png" alt="figure map-1D-100mdeg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-1D-1deg-M4-color.png" alt="figure map-1D-1deg-M4-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>
<td align="center" valign="top">
<img class="embedded" src="map-1D-100mdeg-M2-color.png" alt="figure map-1D-100mdeg-M2-color.png" style="max-width: 201px; max-height: 201px;"/>

</td>

</tr>
<tr>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"0.01" -T3 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"0.1" -T3 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M4 -s"1.0" -T3 -n1000</span></tt>
</td>
<td align="center" valign="top">
<tt><span class="red">./triangulation -t5 -M2 -s"0.1" -T3 -n1000</span></tt>
</td>

</tr>

</table>

</div>
<div class="caption">
Figure 3 Simulation results giving the position and orientation errors for noisy angle measurements. The beacon positions are represented by black and white dot patterns. The first, second, and third columns provide the results for <span class="formula"><i>σ</i> = 0.01 <i>deg</i></span>, <span class="formula"><i>σ</i> = 0.1 <i>deg</i></span>, and <span class="formula"><i>σ</i> = 1 <i>deg</i></span> respectively. Position errors are expressed in meters, the orientation error is expressed in degrees, and the error measure <span class="formula"><span class="fraction"><sup class="numerator">1</sup>⁄<sub class="denominator">|<i>D</i>|</sub></span></span> is in <span class="formula">1 ⁄ <i>m</i><sup>2</sup></span>. The last column shows the results for <span class="formula"><i>σ</i> = 0.1 <i>deg</i></span>; they are identical to that of the second column but after an histogram equalization to enhance its visual representation and interpretation.
</div>

</div>

</div>

</div>
<h1 class="Section">
<a class="toc" name="toc-Section-5">5</a> Copyrights and license
</h1>
<div class="Standard">
All rights reserved by Vincent <span class="versalitas">Pierlot</span> and Marc <span class="versalitas">Van Droogenbroeck</span>. 
</div>
<div class="Standard">
You are allowed to use the programs and the source code for educational purposes and for your own usage only. 
</div>
<div class="Standard">
Distribution or any form of commercial usage is strictly prohibited. Please contact the authors if you want to use the program or source code outside the scope of the authorized usage. 
</div>
<div class="Standard">
<div class="left">
<h1 class="biblio">
References
</h1>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-1"><span class="bib-index">1</span></a>] </span> <span class="bib-authors">A. Easton, S. Cameron</span>. <span class="bib-title">A Gaussian Error Model for Triangulation-Based Pose Estimation Using Noisy Landmarks</span>.  <i><span class="bib-booktitle">IEEE Conference on Robotics, Automation and Mechatronics</span></i>:<span class="bib-pages">1-6</span>, <span class="bib-year">2006</span>. URL <a href="http://dx.doi.org/10.1109/RAMECH.2006.252663"><span class="bib-url">http://dx.doi.org/10.1109/RAMECH.2006.252663</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-2"><span class="bib-index">2</span></a>] </span> <span class="bib-authors">C. Cohen, F. Koss</span>. <span class="bib-title">A Comprehensive Study of Three Object Triangulation</span>.  <i><span class="bib-booktitle">Mobile Robots VII</span></i>, <span class="bib-volume">1831</span>:<span class="bib-pages">95-106</span>, <span class="bib-year">1992</span>. URL <a href="http://dx.doi.org/10.1117/12.143782"><span class="bib-url">http://dx.doi.org/10.1117/12.143782</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-3"><span class="bib-index">3</span></a>] </span> <span class="bib-authors">C.B. Madsen, C.S. Andersen</span>. <span class="bib-title">Optimal landmark selection for triangulation of robot position</span>. <i><span class="bib-journal">Robotics and Autonomous Systems</span></i>, <span class="bib-volume">23</span>(<span class="bib-number">4</span>):<span class="bib-pages">277-292</span>, <span class="bib-year">1998</span>. URL <a href="http://dx.doi.org/10.1016/S0921-8890(98)00014-1"><span class="bib-url">http://dx.doi.org/10.1016/S0921-8890(98)00014-1</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-4"><span class="bib-index">4</span></a>] </span> <span class="bib-authors">C.D. McGillem, T.S. Rappaport</span>. <span class="bib-title">A Beacon Navigation Method for Autonomous Vehicles</span>. <i><span class="bib-journal">IEEE Transactions on Vehicular Technology</span></i>, <span class="bib-volume">38</span>(<span class="bib-number">3</span>):<span class="bib-pages">132-139</span>, <span class="bib-year">1989</span>. URL <a href="http://dx.doi.org/10.1109/25.45466"><span class="bib-url">http://dx.doi.org/10.1109/25.45466</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-5"><span class="bib-index">5</span></a>] </span> <span class="bib-authors">E.Z. Casanova, S.D. Quijada, J.G. García-Bermejo, J.R.P. González</span>. <span class="bib-title">A New Beacon-based System for the Localization of Moving Objects</span>.  <i><span class="bib-booktitle">IEEE International Conference on Mechatronics and Machine Vision in Practice</span></i>, <span class="bib-year">2002</span>. URL <a href="http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.7.1615"><span class="bib-url">http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.7.1615</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-6"><span class="bib-index">6</span></a>] </span> <span class="bib-authors">H. Hmam</span>. <span class="bib-title">Mobile Platform Self-Localization</span>.  <i><span class="bib-booktitle">Information, Decision and Control</span></i>:<span class="bib-pages">242-247</span>, <span class="bib-year">2007</span>. URL <a href="http://dx.doi.org/10.1109/IDC.2007.374557"><span class="bib-url">http://dx.doi.org/10.1109/IDC.2007.374557</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-7"><span class="bib-index">7</span></a>] </span> <span class="bib-authors">J.M. Font-Llagunes, J.A. Batlle</span>. <span class="bib-title">Consistent triangulation for mobile robot localization using discontinuous angular measurements</span>. <i><span class="bib-journal">Robotics and Autonomous Systems</span></i>, <span class="bib-volume">57</span>(<span class="bib-number">9</span>):<span class="bib-pages">931-942</span>, <span class="bib-year">2009</span>. URL <a href="http://dx.doi.org/10.1016/j.robot.2009.06.001"><span class="bib-url">http://dx.doi.org/10.1016/j.robot.2009.06.001</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-8"><span class="bib-index">8</span></a>] </span> <span class="bib-authors">J.M. Font-Llagunes, J.A. Batlle</span>. <span class="bib-title">New method that solves the three-point resection problem using straight lines intersection</span>. <i><span class="bib-journal">Journal of Surveying Engineering</span></i>, <span class="bib-volume">135</span>(<span class="bib-number">2</span>):<span class="bib-pages">39-45</span>, <span class="bib-year">2009</span>. URL <a href="http://dx.doi.org/10.1061/(ASCE)0733-9453(2009)135:2(39)"><span class="bib-url">http://dx.doi.org/10.1061/(ASCE)0733-9453(2009)135:2(39)</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-9"><span class="bib-index">9</span></a>] </span> <span class="bib-authors">J.M. Porta, F. Thomas</span>. <span class="bib-title">Simple Solution to the Three Point Resection Problem</span>. <i><span class="bib-journal">Journal of Surveying Engineering</span></i>, <span class="bib-volume">135</span>(<span class="bib-number">4</span>):<span class="bib-pages">170-172</span>, <span class="bib-year">2009</span>. URL <a href="http://dx.doi.org/10.1061/(ASCE)0733-9453(2009)135:4(170)"><span class="bib-url">http://dx.doi.org/10.1061/(ASCE)0733-9453(2009)135:4(170)</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-10"><span class="bib-index">10</span></a>] </span> <span class="bib-authors">J.S. Esteves, A. Carvalho, C. Couto</span>. <span class="bib-title">Position and Orientation Errors in Mobile Robot Absolute Self-Localization Using an Improved Version of the Generalized Geometric Triangulation Algorithm</span>.  <i><span class="bib-booktitle">IEEE International Conference on Industrial Technology (ICIT)</span></i>:<span class="bib-pages">830-835</span>, <span class="bib-year">2006</span>. URL <a href="http://dx.doi.org/10.1109/ICIT.2006.372345"><span class="bib-url">http://dx.doi.org/10.1109/ICIT.2006.372345</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-11"><span class="bib-index">11</span></a>] </span> <span class="bib-authors">M. Ligas</span>. <span class="bib-title">Simple Solution to the Three Point Resection Problem</span>. <i><span class="bib-journal">Journal of Surveying Engineering</span></i>, <span class="bib-volume">139</span>(<span class="bib-number">3</span>):<span class="bib-pages">120-125</span>, <span class="bib-year">2013</span>. URL <a href="http://dx.doi.org/10.1061/(ASCE)SU.1943-5428.0000104"><span class="bib-url">http://dx.doi.org/10.1061/(ASCE)SU.1943-5428.0000104</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-12"><span class="bib-index">12</span></a>] </span> <span class="bib-authors">R. Burtch</span>. <span class="bib-title">Three point resection problem</span>. <span class="bib-publisher">Surveying Engineering Department, Ferris State University</span>, <span class="bib-year">2005</span>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-13"><span class="bib-index">13</span></a>] </span> <span class="bib-authors">T. Tsukiyama</span>. <span class="bib-title">Mobile Robot Localization from Landmark Bearings</span>.  <i><span class="bib-booktitle">World Congress on Fundamental and Applied Metrology</span></i>:<span class="bib-pages">2109-2112</span>, <span class="bib-year">2009</span>. URL <a href="http://www.imeko.org/publications/wc-2009/IMEKO-WC-2009-TC17-084.pdf"><span class="bib-url">http://www.imeko.org/publications/wc-2009/IMEKO-WC-2009-TC17-084.pdf</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-14"><span class="bib-index">14</span></a>] </span> <span class="bib-authors">V. Pierlot, M. Van Droogenbroeck, M. Urbin-Choffray</span>. <span class="bib-title">A new three object triangulation algorithm based on the power center of three circles</span>.  <i><span class="bib-booktitle">Research and Education in Robotics (EUROBOT)</span></i>, <span class="bib-volume">161</span>:<span class="bib-pages">248-262</span>, <span class="bib-year">2011</span>. URL <a href="http://hdl.handle.net/2268/89435"><span class="bib-url">http://hdl.handle.net/2268/89435</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-15"><span class="bib-index">15</span></a>] </span> <span class="bib-authors">V. Pierlot, M. Van Droogenbroeck</span>. <span class="bib-title">A New Three Object Triangulation Algorithm for Mobile Robot Positioning</span>. <i><span class="bib-journal">IEEE Transactions on Robotics</span></i>, <span class="bib-volume">30</span>(<span class="bib-number">3</span>):<span class="bib-pages">566-577</span>, <span class="bib-year">2014</span>. URL <a href="http://dx.doi.org/10.1109/TRO.2013.2294061"><span class="bib-url">http://dx.doi.org/10.1109/TRO.2013.2294061</span></a>.
</p>
<p class="biblio">
<span class="entry">[<a class="biblioentry" name="biblio-16"><span class="bib-index">16</span></a>] </span> <span class="bib-authors">V. Pierlot, M. Van Droogenbroeck</span>. <span class="bib-title">BeAMS: a Beacon based Angle Measurement Sensor for mobile robot positioning</span>. <i><span class="bib-journal">IEEE Transactions on Robotics</span></i>, <span class="bib-volume">30</span>(<span class="bib-number">3</span>):<span class="bib-pages">533-549</span>, <span class="bib-year">2014</span>. URL <a href="http://dx.doi.org/10.1109/TRO.2013.2293834"><span class="bib-url">http://dx.doi.org/10.1109/TRO.2013.2293834</span></a>.
</p>

</div>

</div>

<hr class="footer"/>
<div class="footer" id="generated-by">
Document generated by <a href="http://elyxer.nongnu.org/">eLyXer 1.2.5 (2013-03-10)</a> on <span class="create-date">2016-12-30T11:40:10.585149</span>
</div>
</div>
</body>
</html>
