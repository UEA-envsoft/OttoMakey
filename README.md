# OttoMakey
Code for the Otto Makey robot to be controlled by the Otto Humanoid setting of the Otto bluetooth phone app  

Be aware that, although functional, this remains a work in progress!  

![image](https://github.com/UEA-envsoft/OttoMakey/assets/64538329/34ca207f-491b-4e2d-9c59-1651081e79a3)

Note this code uses default Rx and Tx for bluetooth communication so bluetooth module must be discinnected when code is uploaded over serial.  

3d print files for Otto Makey can be found here  https://www.printables.com/model/32017-makey-dancing-robot-of-the-maker-faire/comments/1105816  

The android version of the Otto DIY bluetooth controller can be found here https://play.google.com/store/apps/details?id=com.ottodiy  

Makey was wired as follows:

![image](https://github.com/UEA-envsoft/OttoMakey/assets/64538329/5d756b10-fc5b-44d5-af75-68486af9888e)

If I understand what I have read correctly, both the HC-05 and HC-06 bluetooth modules are powered at 5v but use 3.3v logic, whereas the Nano produces a 5v Tx signal so I included a potential divider in my Tx(Nano) to Rx(bluetooth module) connection.  

![366928412_677927230896373_1195863756038563531_n](https://github.com/UEA-envsoft/OttoMakey/assets/64538329/07f3d5a7-3b26-4f1b-84a6-afea39c52499)

Rather than perform a calibration I determined my trim values by manually adjusting the servos to find the adjustment values.

These are entered in OttoMakey.cpp on lines  36 to 42 as follows default is 0 for all
<pre>
  //manual trim  
  servo[0].SetTrim(0);
  servo[1].SetTrim(0);
  servo[2].SetTrim(0);
  servo[3].SetTrim(0);
  servo[4].SetTrim(0);
  servo[5].SetTrim(0);
  servo[6].SetTrim(0);
</pre>
  
