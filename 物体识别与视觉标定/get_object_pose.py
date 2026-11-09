import cv2
import numpy as np
import json
import math
from ultralytics import YOLO


def load_calibration_points():
    try:
        with open("camera_parama.txt", "r") as f:
            lines = f.readlines()
        
        if len(lines) < 4:
            print("标定文件数据不足")
            return None, None
        
        camera_points = []
        actual_points = []
        
        for i in range(4):
            if i < len(lines):
                line = lines[i].strip()
                parts = line.split(",")
                if len(parts) >= 4:
                    try:
                        cam_x = float(parts[0])
                        cam_y = float(parts[1])
                        actual_x = float(parts[2])
                        actual_y = float(parts[3])
                        
                        if cam_x != 0 and cam_y != 0:
                            camera_points.append([cam_x, cam_y])
                            actual_points.append([actual_x, actual_y])
                    except ValueError:
                        print(f"标定点{i+1}数据无效")
        
        if len(camera_points) < 4:
            print(f"有效标定数据不足4个，当前{len(camera_points)}个")
            return None, None
        
        print(f"加载到 {len(camera_points)} 个标定坐标")
        return camera_points, actual_points
    
    except FileNotFoundError:
        print("未找到标定文件camera_parama.txt")
        return None, None
    except Exception as e:
        print(f"加载标定坐标失败：{str(e)}")
        return None, None


def main():
    print("=== 自动检测脚本 ===")
    
    camera_points, actual_points = load_calibration_points()
    if camera_points is None or len(camera_points) < 4:
        print("错误：无法加载标定坐标")
        return
    
    src_pts = np.float32(camera_points)
    dst_pts = np.float32(actual_points)
    M = cv2.getPerspectiveTransform(src_pts, dst_pts)
    
    print("透视变换矩阵计算成功")
    
    print("打开摄像头0...")
    cap = cv2.VideoCapture(0)
    
    if not cap.isOpened():
        cap = cv2.VideoCapture(2, cv2.CAP_DSHOW)
    
    if not cap.isOpened():
        print("错误：无法打开摄像头")
        return
    
    print("摄像头打开成功")
    
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    
    print("等待摄像头稳定...")
    for _ in range(5):
        ret, frame = cap.read()
        if not ret:
            print("错误：无法获取图像")
            cap.release()
            return
    
    print("开始使用YOLO检测...")
    ret, frame = cap.read()
    if not ret:
        print("错误：无法获取图像")
        cap.release()
        return
    
    yolo_model = YOLO('best.pt')
    image_size = 640
    
    results = yolo_model(frame, imgsz=image_size)
    
    blue_targets = []
    green_targets = []
    red_targets = []
    yellow_targets = []
    
    for result in results:
        boxes = result.boxes
        for box in boxes:
            x1, y1, x2, y2 = box.xyxy[0].cpu().numpy()
            cls_id = int(box.cls[0].cpu().numpy())
            
            cx = int((x1 + x2) / 2)
            cy = int((y1 + y2) / 2)
            
            if cls_id == 0:
                red_targets.append((cx, cy))
            elif cls_id == 1:
                green_targets.append((cx, cy))
            elif cls_id == 2:
                blue_targets.append((cx, cy))
            elif cls_id == 13:  # data.yaml: yellow cube
                yellow_targets.append((cx, cy))
    
    print(f"检测完成: 蓝色{len(blue_targets)}个, 绿色{len(green_targets)}个, 红色{len(red_targets)}个, 黄色{len(yellow_targets)}个")
    
    output_lines = []
    
    for i, (x, y) in enumerate(blue_targets):
        pt = np.array([[x, y]], dtype=np.float32)
        transformed = cv2.perspectiveTransform(pt.reshape(1, 1, 2), M)
        coord_x = round(transformed[0][0][0] / 1000, 3)
        coord_y = round(transformed[0][0][1] / 1000, 3)
        output_lines.append(f"blue cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")
    
    for i, (x, y) in enumerate(red_targets):
        pt = np.array([[x, y]], dtype=np.float32)
        transformed = cv2.perspectiveTransform(pt.reshape(1, 1, 2), M)
        coord_x = round(transformed[0][0][0] / 1000, 3)
        coord_y = round(transformed[0][0][1] / 1000, 3)
        output_lines.append(f"red cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")
    
    for i, (x, y) in enumerate(green_targets):
        pt = np.array([[x, y]], dtype=np.float32)
        transformed = cv2.perspectiveTransform(pt.reshape(1, 1, 2), M)
        coord_x = round(transformed[0][0][0] / 1000, 3)
        coord_y = round(transformed[0][0][1] / 1000, 3)
        output_lines.append(f"green cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")
    
    for i, (x, y) in enumerate(yellow_targets):
        pt = np.array([[x, y]], dtype=np.float32)
        transformed = cv2.perspectiveTransform(pt.reshape(1, 1, 2), M)
        coord_x = round(transformed[0][0][0] / 1000, 3)
        coord_y = round(transformed[0][0][1] / 1000, 3)
        output_lines.append(f"yellow cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")
    
    cap.release()
    
    if output_lines:
        output_str = "\n".join(output_lines)
        print("\n检测结果:")
        print(output_str)
    else:
        print("未检测到任何目标")


if __name__ == "__main__":
    main()
