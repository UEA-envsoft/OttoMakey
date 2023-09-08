# OttoMakey
Code for the Otto Makey robot to be controlled by the Otto Humanoid setting of the Otto bluetooth phone app  

Be aware althoug functional this remains a work in progress!  

Note this code uses default Rx and Tx for bluetooth communication so bluetooth module must be discinnected when code is uploaded over serial.  

3d print files for Otto Makey can be found here  https://www.printables.com/model/32017-makey-dancing-robot-of-the-maker-faire/comments/1105816  

The android version of the Otto DIY bluetooth controller can be found here https://play.google.com/store/apps/details?id=com.ottodiy  

Makey was wired as follows:

![image](https://github.com/UEA-envsoft/OttoMakey/assets/64538329/935b69fc-6451-484d-84cd-972c943e1e44)

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
  
