import cv2
import mediapipe as mp
import requests
 
cap = cv2.VideoCapture(0)
# cap = cv2.VideoCapture('http://192.168.65.74:4747/video')
 
mpHands = mp.solutions.hands
hands = mpHands.Hands(max_num_hands=1)
mpDraw = mp.solutions.drawing_utils

pos = [0, 0, 0, 0, 0, 0, 0, 0]
refs = [8, 5, 12, 9, 16, 13, 20, 17]
thumb = [4, 2]
thumb_pos = [0, 0]

p_state = 0

pTime = 0
cTime = 0
def update_pos(id, cx, cy):
    if id in refs:
        pos[refs.index(id)] = cy
    elif id in thumb:
        thumb_pos[thumb.index(id)] = cx
    return

def count_fingers(pos):
    count = 0
    for i in range(1, 8, 2):
        if pos[i] - pos[i-1] > 0:
            count += 1
    return count

def count_thumb(thumb_pos):
    if thumb_pos[1] - thumb_pos[0] < 0:
        return 1
    return 0

while True:
    success, img = cap.read()
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(imgRGB)
    # print(results.multi_hand_landmarks)
 
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            for id, lm in enumerate(handLms.landmark):
                # print(id, lm)
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                update_pos(id, cx, cy)
                # if id == 4:
                cv2.circle(img, (cx, cy), 5, (255, 0, 255), cv2.FILLED)
 
            mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS)
            count = count_fingers(pos)
            if count == 1:
                if p_state != count:
                    requests.get('http://192.168.234.53/forw')
                    p_state = count
            elif count == 0:
                if p_state != count:
                    requests.get('http://192.168.234.53/stop')
                    p_state = count
            elif count == 2:
                if p_state != count:
                    requests.get('http://192.168.234.53/right')
                    p_state = count
            elif count == 3:
                if p_state != count:
                    requests.get('http://192.168.234.53/left')
                    p_state = count
            elif count == 4:
                if p_state != count:
                    requests.get('http://192.168.234.53/back')
                    p_state = count
            cv2.putText(img, str(count),(10, 70), cv2.FONT_HERSHEY_SIMPLEX, 3, (0, 0, 255), 3)
            # print(count)
 
    # cTime = time.time()
    # fps = 1 / (cTime - pTime)
    # pTime = cTime
 
    # cv2.putText(img, str(int(fps)), (10, 70), cv2.FONT_HERSHEY_PLAIN, 3,
    #             (255, 0, 255), 3)
 
    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break