from facenet_pytorch import MTCNN
import cv2
from PIL import Image
import numpy as np
from matplotlib import pyplot as plt


# Create face detector
mtcnn = MTCNN(margin=20, keep_all=True, post_process=False)

# Load a single image and display
path = "C:\\Users\\Harukatsu\\Workspace\\Learning\\pytorch\\FaceRcog\\photo\\pessoa2\\"
file = "4.jpg"
frame = cv2.imread(path+file) 
img=frame
frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
frame = Image.fromarray(frame)
#plt.imshow(frame)
#plt.axis('off')
#plt.show()

# Detect face
boxes,probs = mtcnn.detect(img)

for i in range(0,len(boxes)):
    img = cv2.rectangle(img,(int(boxes[i][0]),int(boxes[i][1])),(int(boxes[i][2]),int(boxes[i][3])),(255,0,0),2)
    cv2.imwrite("filename1.jpg", img)
