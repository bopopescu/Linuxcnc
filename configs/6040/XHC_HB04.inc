#*********************************************************************************************************************
# 
#  Utilisation d'une Handwheel xhc-hb04 avec LinuxCNC 2.7 (Debian)
#
#  Dans le répertoire   home/<utilisateur>/linuxcnc/configs/<ma-machine>
#
#  1- Placez une copie du fichier XHC_HB04.inc
#
#  2- Modifiez le fichier <ma-machine>.ini en insérant la ligne ci-dessous (caractère # compris) après la dernière ligne 
#     de la section [HAL] (probablement en dessous de la ligne "POSTGUI_HALFILE = custom_postgui.hal"). 
#
#     #INCLUDE XHC_HB04.inc
#
#  Attention, il faut effectuer cette modification à chaque fois que Stepconf est utilisé car le fichier <ma-machine>.ini 
#  est réinitialisé par Stepconf.
#
#  3- Dans le fichier XHC_HB04.inc, adaptez à vos préférences les dispositions et commandes et réalisez une nouvelle 
#     sérigraphie des boutons. La configuration proposée ici me convient pour des découpes de plaques (ctp, balsa, expoxy,
#     carbone, etc.) avec une machine 3 axes dont le Gcode provient essentiellment de CamBam (= pas d'axe A). 
#     J'ai pris l'option de n'utiliser que des valeurs X et Y positives, et en découpe la surface de la plaque étant 
#     à Z=0 la valeur négative de Z mini est de -30.
#  
#  Pour plus de détails, consultez :
#  - le fichier readme du répertoire usr/share/doc/linuxcnc/examples/sample-configs/sim/axis/xhc-hb04
#    on y trouve des informations concernant l'installation sur une distribution autre que Debian
#  - http://linuxcnc.org/docs/html/hal/halui_fr.html
#  - http://linuxcnc.org/docs/html/man/man1/xhc-hb04.1.html
#  - http://wiki.linuxcnc.org/cgi-bin/wiki.pl?Using_A_XHC-HB04_Wireless_MPG_Pendant
#    ...Attention toutefois aux infos antérieures à LinuxCNC 2.6 qui peuvent être obsolètes
#
#*********************************************************************************************************************

HALUI   = halui
HALFILE = LIB:xhc-hb04.tcl

[XHC_HB04_CONFIG]
layout = 2       
coords = x y z  
coefs  = 1 1 1  
scales = 10 10 10 
threadname = servo-thread 
sequence = 3     
jogmode = vnormal 
require_pendant = yes 
inch_or_mm = mm

[XHC_HB04_BUTTONS]

# BOUTONS MACH3
#  -------------- --------------  
# | reset        | stop         |
#  -------------- -------------- -------------- --------------  
# | goto-zero(-i)| start-pause  | rewind       | probe-z      |
#  -------------- -------------- -------------- -------------- 
# | spindle      | half(-i)     | zero(-i)     | safe-z       |
#  -------------- -------------- -------------- -------------- 
# | home         | macro-1      | macro-2      | macro-3      |
#  -------------- -------------- -------------- -------------- 
# | step         | mode         | macro-6      | macro-7      |
#  -------------- -------------- -------------- -------------- 
# BOUTONS LINUXCNC
#  -------------- --------------  
# | A/URGENT     | Mode Manuel  |
#  -------------- -------------- -------------- --------------  
# | POM (x/y/z)  | START/PAUSE  | PASaPAS      | STOP         |
#  -------------- -------------- -------------- -------------- 
# | BROCHE Start | X maxi       | Y maxi       | Z maxi       |
#  -------------- -------------- -------------- -------------- 
# | BROCHE Stop  | X mini       | Y mini       | Z mini       |
#  -------------- -------------- -------------- -------------- 
# | STEP +       | STEP -       | HOME1        | HOME2        |
#  -------------- -------------- -------------- -------------- 

#-----1ere ligne-----------------------------------------------
reset	    = halui.estop.activate
stop	    = halui.mode.manual 

#-----2eme ligne-----------------------------------------------
goto-zero   = ""
goto-zero-x = halui.joint.0.home
goto-zero-y = halui.joint.1.home
goto-zero-z = halui.joint.2.home
start-pause = std_start_pause
rewind	    = halui.program.step
probe-z     = halui.program.stop

#-----3eme ligne-----------------------------------------------
spindle     = halui.spindle.start
half        = halui.mdi-command-03
zero        = halui.mdi-command-04
safe-z	    = halui.mdi-command-05

#-----4eme ligne-----------------------------------------------
home        = halui.spindle.stop
macro-1	    = halui.mdi-command-00
macro-2	    = halui.mdi-command-01
macro-3	    = halui.mdi-command-02

#-----5eme ligne-----------------------------------------------
step        = xhc-hb04.stepsize-up
mode	    = xhc-hb04.stepsize-down
macro-6	    = halui.mdi-command-06
macro-7	    = halui.mdi-command-07

[HALUI]
MDI_COMMAND=G0 X0               (00)
MDI_COMMAND=G0 Y0               (01)
MDI_COMMAND=G0 Z20              (02)
MDI_COMMAND=G0 X500             (03)
MDI_COMMAND=G0 Y300             (04)
MDI_COMMAND=G0 Z100             (05)
MDI_COMMAND=G0 X0 Y0   Z50      (06)
MDI_COMMAND=G0 X0 Y300 Z50      (07)

#*********************************************************************************************************************
