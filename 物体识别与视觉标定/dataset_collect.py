import sys
import cv2
import os
import datetime
from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, 
                             QGroupBox, QLabel, QPushButton, QMessageBox, QComboBox)
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QImage, QPixmap, QFont


class DatasetCollector(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.cap = None
        self.image_count = 0
        self.dataset_dir = os.path.join(os.path.dirname(__file__), "dataset")
        
        self.camera_timer = QTimer()
        self.camera_timer.timeout.connect(self.update_frame)
        
        self.init_ui()
        self.create_dataset_folder()
    
    def create_dataset_folder(self):
        if not os.path.exists(self.dataset_dir):
            os.makedirs(self.dataset_dir)
            print(f"创建数据集文件夹: {self.dataset_dir}")
    
    def init_ui(self):
        self.setWindowTitle("数据集采集工具")
        self.setGeometry(100, 100, 800, 600)
        
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)
        main_layout.setSpacing(10)
        main_layout.setContentsMargins(10, 10, 10, 10)
        
        title_label = QLabel("数据集采集工具")
        title_label.setAlignment(Qt.AlignCenter)
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title_label.setFont(title_font)
        main_layout.addWidget(title_label)
        
        camera_font = QFont()
        camera_font.setPointSize(10)
        camera_font.setBold(True)
        
        combo_font = QFont()
        combo_font.setPointSize(9)
        
        camera_group = QGroupBox("摄像头控制")
        camera_group.setFont(camera_font)
        camera_layout = QVBoxLayout(camera_group)
        
        control_layout = QHBoxLayout()
        control_layout.addWidget(QLabel("摄像头："))
        
        self.camera_combo = QComboBox()
        self.camera_combo.addItems(["摄像头0", "摄像头1", "摄像头2"])
        self.camera_combo.setFixedWidth(120)
        self.camera_combo.setFont(combo_font)
        control_layout.addWidget(self.camera_combo)
        
        self.start_camera_btn = QPushButton("开启摄像头")
        self.stop_camera_btn = QPushButton("关闭摄像头")
        self.capture_btn = QPushButton("采集图像")
        
        for btn in [self.start_camera_btn, self.stop_camera_btn, self.capture_btn]:
            btn.setFixedWidth(120)
            btn.setFont(combo_font)
            btn.setStyleSheet("""
                QPushButton {
                    background-color: #3498db;
                    color: white;
                    border: none;
                    padding: 8px 15px;
                    border-radius: 4px;
                    font-weight: bold;
                }
                QPushButton:hover {
                    background-color: #2980b9;
                }
                QPushButton:disabled {
                    background-color: #cccccc;
                }
            """)
        
        self.start_camera_btn.clicked.connect(self.start_camera)
        self.stop_camera_btn.clicked.connect(self.stop_camera)
        self.capture_btn.clicked.connect(self.capture_image)
        
        control_layout.addWidget(self.start_camera_btn)
        control_layout.addWidget(self.stop_camera_btn)
        control_layout.addWidget(self.capture_btn)
        control_layout.addStretch()
        camera_layout.addLayout(control_layout)
        
        main_layout.addWidget(camera_group)
        
        image_group = QGroupBox("图像显示")
        image_group.setFont(camera_font)
        image_layout = QVBoxLayout(image_group)
        
        self.image_label = QLabel()
        self.image_label.setFixedSize(640, 480)
        self.image_label.setStyleSheet("border: 2px solid #cccccc; background-color: #f0f0f0;")
        self.image_label.setAlignment(Qt.AlignCenter)
        self.image_label.setText("摄像头未开启")
        image_layout.addWidget(self.image_label)
        
        main_layout.addWidget(image_group)
        
        info_group = QGroupBox("采集信息")
        info_group.setFont(camera_font)
        info_layout = QVBoxLayout(info_group)
        
        self.count_label = QLabel(f"已采集图像数量: {self.image_count}")
        self.count_label.setStyleSheet("font-size: 14px; font-weight: bold;")
        info_layout.addWidget(self.count_label)
        
        self.path_label = QLabel(f"保存路径: {self.dataset_dir}")
        self.path_label.setStyleSheet("font-size: 12px; color: #666666;")
        info_layout.addWidget(self.path_label)
        
        main_layout.addWidget(info_group)
        
        self.stop_camera_btn.setEnabled(False)
        self.capture_btn.setEnabled(False)
        
        self.set_style()
    
    def set_style(self):
        style = """
        QMainWindow {
            background-color: #f5f5f5;
        }

        QGroupBox {
            font-weight: bold;
            border: 2px solid #2196F3;
            border-radius: 5px;
            margin-top: 10px;
            padding-top: 10px;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px 0 5px;
        }

        QPushButton {
            background-color: #2196F3;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #1976D2;
        }

        QPushButton:pressed {
            background-color: #0D47A1;
        }

        QPushButton:disabled {
            background-color: #cccccc;
            color: #666666;
        }

        QLabel {
            font-weight: 500;
        }

        QComboBox {
            border: 1px solid #cccccc;
            border-radius: 3px;
            padding: 4px;
        }
        """
        self.setStyleSheet(style)
    
    def start_camera(self):
        try:
            camera_text = self.camera_combo.currentText()
            if camera_text == "摄像头0":
                camera_index = 0
            elif camera_text == "摄像头1":
                camera_index = 1
            elif camera_text == "摄像头2":
                camera_index = 2
            else:
                camera_index = 0

            self.cap = cv2.VideoCapture(camera_index)

            if not self.cap.isOpened():
                self.cap = cv2.VideoCapture(camera_index, cv2.CAP_DSHOW)

            if not self.cap.isOpened():
                QMessageBox.critical(self, "错误", f"无法打开摄像头 {camera_index}")
                print(f"错误：无法打开摄像头 {camera_index}")
                return

            self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
            self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

            actual_width = self.cap.get(cv2.CAP_PROP_FRAME_WIDTH)
            actual_height = self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
            print(f"摄像头分辨率: {actual_width} x {actual_height}")

            self.camera_timer.start(30)

            self.start_camera_btn.setEnabled(False)
            self.stop_camera_btn.setEnabled(True)
            self.capture_btn.setEnabled(True)
            self.camera_combo.setEnabled(False)

            print(f"摄像头 {camera_index} 开启成功")

        except Exception as e:
            QMessageBox.critical(self, "错误", f"摄像头开启失败: {str(e)}")
            print(f"摄像头错误：{str(e)}")
    
    def stop_camera(self):
        if self.cap:
            self.camera_timer.stop()
            self.cap.release()
            self.cap = None
        
        self.start_camera_btn.setEnabled(True)
        self.stop_camera_btn.setEnabled(False)
        self.capture_btn.setEnabled(False)
        self.camera_combo.setEnabled(True)
        
        self.image_label.setText("摄像头已关闭")
        self.image_label.setPixmap(QPixmap())
        
        print("摄像头已关闭")
    
    def update_frame(self):
        if self.cap and self.cap.isOpened():
            ret, frame = self.cap.read()
            if ret:
                rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                h, w, ch = rgb_image.shape
                bytes_per_line = ch * w
                qt_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)
                
                pixmap = QPixmap.fromImage(qt_image).scaled(
                    640, 480, Qt.IgnoreAspectRatio, Qt.SmoothTransformation)
                self.image_label.setPixmap(pixmap)
    
    def capture_image(self):
        if self.cap and self.cap.isOpened():
            ret, frame = self.cap.read()
            if ret:
                self.image_count += 1
                timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S_%f")[:-3]
                filename = os.path.join(self.dataset_dir, f"image_{timestamp}.jpg")
                cv2.imwrite(filename, frame)
                
                self.count_label.setText(f"已采集图像数量: {self.image_count}")
                
                print(f"图像已保存: {filename}")
                
                QMessageBox.information(self, "成功", f"图像已保存为: {filename}")
    
    def closeEvent(self, event):
        self.stop_camera()
        event.accept()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DatasetCollector()
    window.show()
    sys.exit(app.exec_())