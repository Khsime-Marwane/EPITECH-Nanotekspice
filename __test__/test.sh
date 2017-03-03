#!/bin/sh

# nand passe pas
# clocks

#
#      TESTING COMPONENT 4013
#

# tests check rising clock when clock initialized at 0
echo "" | ../nanotekspice resources/4013.nts clock=0 data=0 set=0 reset=1 > .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=0 data=0 set=1 reset=0 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=0 data=1 set=0 reset=0 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=0 data=1 set=1 reset=0 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=0 data=1 set=0 reset=1 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=0 data=1 set=1 reset=1 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=0 data=1 set=1 reset=1 >> .tmp4013;
# tests check rising clock when clock initialized at 1
echo "" | ../nanotekspice resources/4013.nts clock=1 data=0 set=0 reset=0 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=1 data=0 set=0 reset=1 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=1 data=0 set=1 reset=0 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=1 data=1 set=0 reset=0 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=1 data=1 set=1 reset=0 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=1 data=1 set=0 reset=1 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=1 data=1 set=1 reset=1 >> .tmp4013;
echo "" | ../nanotekspice resources/4013.nts clock=1 data=1 set=1 reset=1 >> .tmp4013;
# tests when clock rising
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=0 set=0 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=0 set=0 reset=1 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=0 set=1 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=1 set=0 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=1 set=1 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=1 set=0 reset=1 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=1 set=1 reset=1 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=1 set=1 reset=1 >> .tmp4013;
# tests when clock !rising
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=0 set=0 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=0 set=0 reset=1 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=0 set=1 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=1 set=0 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=1 set=1 reset=0 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=1 set=0 reset=1 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=1 set=1 reset=1 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=1 data=1 set=1 reset=1 >> .tmp4013;
echo "simulate\ndisplay"| ../nanotekspice resources/4013.nts clock=0 data=0 set=0 reset=0 >> .tmp4013;

diff .tmp4013 answers/4013 > /dev/null
if [ $? -eq 0 ]
then
    echo "Tests 4013 DUAL FLIP FLOP \t\t\tPASSED"
else
    echo "Tests 4013 DUAL FLIP FLOP \t\t\tFAILED"
fi
