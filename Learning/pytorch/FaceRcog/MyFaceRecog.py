from facenet_pytorch import MTCNN, InceptionResnetV1
import torch
from torchvision import datasets
from torch.utils.data import DataLoader
import cv2 #opencv

accept_prob = 0.9

mtcnn = MTCNN(image_size=240, margin=0, keep_all=True,min_face_size=40)
mtcnn1 =MTCNN(image_size=240, margin=0, keep_all=False,min_face_size=40)
#keep_all = True identifies multiple faces, while false is just one
resnet = InceptionResnetV1(pretrained='vggface2').eval()
#modelo já treinado no pretrained

path = 'photo'
dataset = datasets.ImageFolder(path)

index_to_class = {i:c for c,i in dataset.class_to_idx.items()}

# dataset.class_to_idx.items() returns dict {folder_name:index}
# so {folder_name index} become {index :folder_name}

def collate_fn(x):
    return x[0]

loader = DataLoader(dataset, collate_fn=collate_fn)

names = []
emb_list =[]

for img,index in loader:
    face,prob = mtcnn1(img,return_prob=True) #search face and crop it
    if face is not None and prob>accept_prob:
        face2d = face.unsqueeze(0)
        emb = resnet(face2d)
        emb_list.append(emb.detach())
        names.append(index_to_class[index])

data = [emb_list,names]
torch.save(data,'data.pt')



load_data = torch.load('data.pt')
emb_list = load_data[0]
name_list = load_data[1]



path = "C:\\Users\\Harukatsu\\Workspace\\Learning\\pytorch\\FaceRcog\\photo\\pessoa2\\"
file = "1.jpg"


# reads image 'opencv-logo.png' as grayscale
img = cv2.imread(path+file) 
img_crop_list, prob_list = mtcnn(img, return_prob=True)
if img_crop_list is not None:
    boxes, _ =mtcnn.detect(img)

    print(boxes)

    for i,prob in enumerate(prob_list):
        if prob>accept_prob:
            emb = resnet(img_crop_list[i].unsqueeze(0)).detach()
            dist_list = []
            for idxm,emb_db in enumerate(emb_list):
                dist = torch.dist(emb,emb_db).item()
                dist_list.append(dist)
            min_dist=min(dist_list)
            min_dist_idx = dist_list.index(min_dist)
            name = name_list[min_dist_idx]
            box = boxes[i]
            
            color = (255, 0, 0)
            if min_dist<accept_prob:
                frame = cv2.rectangle(img,(int(box[0]),int(box[1])),(int(box[2]),int(box[3])),(255,0,0),2)
                cv2.imwrite("filename.jpg", frame)


