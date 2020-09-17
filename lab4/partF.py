#adapted from member amey_s from instructables.com

import cv2 as cv2
import numpy as np
import time
import imutils
from copy import deepcopy
from picamera.array import PiRGBArray
from picamera import PiCamera
from threading import Thread
import cv2
 
MIDDLE_OF_FRAME_X = 160
MIDDLE_OF_FRAME_Y = 120
CALIB_CIRCLE_RADIUS=50
CALIB_COUNT = 3
RELAX_BOUND = 1.2

def colorCalibrate(cap):
    cv2.namedWindow('calibrater')
    count = 0
    calibPoints = []
    while(count != CALIB_COUNT):
        _,frame = cap.read()
        cv2.circle(frame, (MIDDLE_OF_FRAME_X, MIDDLE_OF_FRAME_Y),CALIB_CIRCLE_RADIUS ,(127,0,124), 2)
        cv2.imshow('calibrater',frame) 
        k = cv2.waitKey(5) & 0xFF
        if k == 97:
            count += 1
            pc = 0.0
            avg = np.array((0,0,0))
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) 

            print(type(hsv))

            for y in range(MIDDLE_OF_FRAME_Y - CALIB_CIRCLE_RADIUS,MIDDLE_OF_FRAME_Y + CALIB_CIRCLE_RADIUS):
                for x in range(MIDDLE_OF_FRAME_X - CALIB_CIRCLE_RADIUS,MIDDLE_OF_FRAME_X + CALIB_CIRCLE_RADIUS):
                    
                    if (x-MIDDLE_OF_FRAME_X)**2 + (y-MIDDLE_OF_FRAME_Y)**2 <= CALIB_CIRCLE_RADIUS**2:
                        pc +=1.0
                  
                        avg +=  hsv[x,y]
            avg = avg/pc
            print(avg)
            calibPoints.append(avg) 
    tm = np.maximum(calibPoints[0],calibPoints[1])
    ub = np.maximum(tm, calibPoints[2])
    tmin = np.minimum(calibPoints[0], calibPoints[1])
    lb = np.minimum(tmin, calibPoints[2])
    cv2.destroyAllWindows()
    print("Calibration complete!")
    print(lb)
    print(ub)

   
    return (1 / RELAX_BOUND) * lb,ub * RELAX_BOUND

class PiVideoStream:
    def __init__(self, resolution=(320, 240), framerate=32):
        # initialize the camera and stream
        self.camera = PiCamera()
        self.camera.resolution = resolution
        self.camera.framerate = framerate
        self.rawCapture = PiRGBArray(self.camera, size=resolution)
        self.stream = self.camera.capture_continuous(self.rawCapture,
            format="bgr", use_video_port=True)
 
        # initialize the frame and the variable used to indicate
        # if the thread should be stopped
        self.frame = None
        self.stopped = False



    def start(self):
        # start the thread to read frames from the video stream
        Thread(target=self.update, args=()).start()
        return self
 
    def update(self):
        # keep looping infinitely until the thread is stopped
        for f in self.stream:
            # grab the frame from the stream and clear the stream in
            # preparation for the next frame
            self.frame = f.array
            self.rawCapture.truncate(0)
 
            # if the thread indicator variable is set, stop the thread
            # and resource camera resources
            if self.stopped:
                self.stream.close()
                self.rawCapture.close()
                self.camera.close()
                return
    def read(self):
        # return the frame most recently read
        return None, self.frame
 
    def stop(self):
        # indicate that the thread should be stopped
        self.stopped = True












# Take input from webcam
cap = PiVideoStream()
cap.start()


greenLower, greenUpper = colorCalibrate(cap)



#greenLower = (29, 86, 6)
#greenUpper = (64, 255, 255)


def nothing(x):
    pass
# Creating a windows for later use
cv2.namedWindow('oFrame')
cv2.namedWindow('inRange')
cv2.namedWindow('eroded')
cv2.namedWindow('dilated')
cv2.namedWindow('tracking')
#
## Creating track bar for min and max for hue, saturation and value
## You can adjust the defaults as you like
#cv2.createTrackbar('hmin', 'HueComp',48,179,nothing)
#cv2.createTrackbar('hmax', 'HueComp',138,179,nothing)
#
#cv2.createTrackbar('smin', 'SatComp',27,255,nothing)
#cv2.createTrackbar('smax', 'SatComp',56,255,nothing)
#
#cv2.createTrackbar('vmin', 'ValComp',119,255,nothing)
#cv2.createTrackbar('vmax', 'ValComp',141,255,nothing)

















while(1):
    try:  
        _, frame = cap.read() 
        #converting to HSV
        #hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
        #hue,sat,val = cv2.split(hsv)
        oFrame = deepcopy(frame)
        frame = imutils.resize(frame, width=600)
        blurred = cv2.GaussianBlur(frame, (11, 11), 0)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
                                                                 
        # construct a mask for the color "green", then perform
        # a series of dilations and erosions to remove any small
        # blobs left in the mask
        mask1 = cv2.inRange(hsv, greenLower, greenUpper)
        mask2 = cv2.erode(mask1, None, iterations=2)
        mask3 = cv2.dilate(mask2, None, iterations=2)
        
        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        cnts = cv2.findContours(mask3.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        center = None
        circles = cv2.HoughCircles(mask3.copy(),cv2.HOUGH_GRADIENT,2,120,param1=120,param2=50,minRadius=10,maxRadius=0)



        #if circles is not None:
        #                                                                                                   
        #        for i in circles[0,:]:
        #            # If the ball is far, draw it in green
        #            if int(round(i[2])) < 30:
        #                cv2.circle(frame,(int(round(i[0])),int(round(i[1]))),int(round(i[2])),(0,255,0),5)
        #                cv2.circle(frame,(int(round(i[0])),int(round(i[1]))),2,(0,255,0),10)            
        #                
        #            # else draw it in red
        #            elif int(round(i[2])) > 35:
        #                cv2.circle(frame,(int(round(i[0])),int(round(i[1]))),int(round(i[2])),(0,0,255),5)
        #                cv2.circle(frame,(int(round(i[0])),int(round(i[1]))),2,(0,0,255),10)
              









        if len(cnts) > 0:                                                    
            # find the largest contour in the mask, then use
            # it to compute the minimum enclosing circle and
            # centroid
            c = max(cnts, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                                                                          
            # only proceed if the radius meets a minimum size
            if radius > 10:
                # draw the circle and centroid on the frame,
                # then update the list of tracked points
                cv2.circle(frame, (int(x), int(y)), int(radius),
                    (0, 255, 255), 2)
                cv2.circle(frame, center, 5, (0, 0, 255), -1)


             









        #Show the result in frames
        cv2.imshow('oFrame',oFrame)
        cv2.imshow('inRange',mask1)
        cv2.imshow('eroded',mask2)
        cv2.imshow('dilated',mask3)
        cv2.imshow('tracking',frame)

        k = cv2.waitKey(5) & 0xFF
        if k == 27:
            break
    except KeyboardInterrupt:
        cap.stop()
        cv2.destroyAllWindows()
        exit()  

cap.stop()
cv2.destroyAllWindows()
