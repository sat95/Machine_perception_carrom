import sys
sys.path.append('/usr/local/lib/python2.7/site-packages')
import numpy as np
import cv2

#striker Diameter = 3.5/74*Height = 3.5/74*783 = 37 approx 36 r=18
#hole size = 4*Height/74 = 42 r=21
#coin size = 3*Height/74 = 31 Approx 30 r=15




img = cv2.imread('Carrom.jpg')

img_name =sys.argv[1]


print img.size	
height, width, channels = img.shape
print height, width, channels	

#620> coin_y > 500

coin_x = 235
coin_y = 470


img=img

Shift_count=0

striker_Shift = int(3.5*height/(74))/2
striker_Radious = int(3.5*height/(74))/2
Striker_position_y = width/2+width/3
coin_radious = int(3*height/(74))/2

Coin_Position		= ((0,0),(148,148),(70,250),(100,30),(392,392),(235,470))
Striker_coin_position	= ((0,0),(171,171),(77,280),(132,32),(415,415),(252,498))


Striker_line_position  = (0,height/5+3+ 0*striker_Radious, height/5+3+ 2*striker_Radious, height/5+2+ 5*striker_Radious, height/5+1+ 8*striker_Radious, height/5+0+11*striker_Radious, height/5+0+13*striker_Radious, height/5+0+15*striker_Radious, height/5-1+18*striker_Radious, height/5-2+21*striker_Radious, height/5-3+24*striker_Radious, height/5-3+26*striker_Radious)

Ip_coin=  int(img_name[11])

cv2.circle(img,Coin_Position[int(img_name[11])], coin_radious, (0,0,0), -1)
cv2.circle(img,Striker_coin_position[int(img_name[11])], striker_Radious, (0,255,0), -1)
cv2.circle(img,(Striker_line_position[int(img_name[13])], Striker_position_y), striker_Radious, (0,255,0), -1)


cv2.line(img, Striker_coin_position[int(img_name[11])], (Striker_line_position[int(img_name[13])],Striker_position_y),(0,255,0), thickness=5, lineType= 8, shift=0)

cv2.line(img, Coin_Position[int(img_name[11])], (30,30),(0,0,0), thickness=5, lineType= 8, shift=0)








cv2.imshow("Temp.jpg",img)


cv2.waitKey(0)
cv2.destroyAllWindows()

