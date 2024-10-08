# Name: Jack Landers 
# Date: 9/25/25
# Title: Lab1 - Using a shell program
# Description: This program demonstrates basic linux and shell commands to calculate the areas of a circle and rectangle

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers logged on"
if [ $user = "jlanders" ]
then
	echo "Now you can proceed"
else
	echo "Denied, you are logged in as $user"
	exit 1
fi

response="Yes"
while [ $response != "No" ]
do
	echo "Enter height of rectangle: "
	read height
	echo "Enter width of rectangle: "
	read width
	echo "Enter radius of circle: "
	read radius
	area=`expr $height \* $width`
	circle=$(echo "$radius * $radius * 3.14159" | bc)
	echo "The area of the rectangle is $area, and the area of the circle is $circle"
	echo "Would you like to repeat to do it again? [Yes/No]"
	read response

done


