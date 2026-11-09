import sys
from pathlib import Path
from datetime import datetime
import cv2
import numpy as np
import math
import time
from ultralytics import YOLO
from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, 
                             QGroupBox, QLabel, QSpinBox, QPushButton, QMessageBox, 
                             QComboBox, QTextEdit, QTableWidget, QTableWidgetItem,
                             QHeaderView, QTabWidget, QFileDialog, QDoubleSpinBox, QScrollArea)
from PyQt5.QtCore import Qt, QTimer, pyqtSignal
from PyQt5.QtGui import QImage, QPixmap, QPainter, QPen, QColor, QFont
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo


class RoboticArm:
    def __init__(self):
        self.full_cmd = ""
        self.x = 0
        self.y = 0
        self.z = 0
        self.voice_data = ""
        self.send_length = 0
        self.data_send = bytearray(128)

    def uart_tran_axis_data(self):
        checksum = 0
        self.data_send[0] = 0x55

        self.data_send[1] = (self.x >> 8) & 0xFF
        self.data_send[2] = self.x & 0xFF
        self.data_send[3] = (self.y >> 8) & 0xFF
        self.data_send[4] = self.y & 0xFF
        if self.z >= 105:
            self.z = 105
        if self.z <= 40:
            self.z = 40
        self.data_send[5] = (self.z >> 8) & 0xFF
        self.data_send[6] = self.z & 0xFF

        for i in range(7):
            checksum += self.data_send[i]
        self.data_send[7] = checksum & 0xFF
        self.send_length = 8

    def uart_tran_voice_data(self):
        self.data_send[0] = 0x66

        try:
            if isinstance(self.voice_data, str):
                voice_bytes = self.voice_data.encode('gbk')
            else:
                voice_bytes = str(self.voice_data).encode('gbk')

            if len(voice_bytes) > 126:
                raise ValueError(f"语音数据过长")

            for i, byte in enumerate(voice_bytes, start=1):
                self.data_send[i] = byte

            data_length = len(voice_bytes) + 2
            self.data_send[data_length - 1] = 0x00
            self.send_length = data_length

        except UnicodeEncodeError as e:
            self.data_send = bytearray(128)
            self.data_send[0] = 0x66
            self.data_send[1] = 0x00
            self.send_length = 2

    def uart_tran_tool_data(self, tool_state):
        self.data_send[0] = 0x77
        self.data_send[1] = tool_state
        self.data_send[2] = (0x77 + tool_state) & 0xFF
        self.send_length = 3


class ClickableImageLabel(QLabel):
    clicked = pyqtSignal(int, int, int)
    coordinate_selected = pyqtSignal(int, int)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.calibration_points = []
        self.selected_point_index = -1
        self.is_dragging = False
        self.target_point = None
        self.is_selecting_target = False

    def set_selecting_target(self, selecting):
        self.is_selecting_target = selecting
        if selecting:
            self.target_point = None

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            x = event.x()
            y = event.y()

            if self.is_selecting_target:
                x = max(0, min(x, self.width() - 1))
                y = max(0, min(y, self.height() - 1))
                self.target_point = (x, y)
                self.coordinate_selected.emit(x, y)
                self.update()
                return

            for i, (px, py) in enumerate(self.calibration_points):
                if abs(x - px) < 10 and abs(y - py) < 10:
                    self.selected_point_index = i
                    self.is_dragging = True
                    self.clicked.emit(x, y, i)
                    return

            if len(self.calibration_points) < 4:
                self.calibration_points.append((x, y))
                self.selected_point_index = len(self.calibration_points) - 1
                self.clicked.emit(x, y, self.selected_point_index)
            else:
                min_distance = float('inf')
                nearest_index = -1
                for i, (px, py) in enumerate(self.calibration_points):
                    distance = math.sqrt((x - px) ** 2 + (y - py) ** 2)
                    if distance < min_distance and distance < 20:
                        min_distance = distance
                        nearest_index = i

                if nearest_index >= 0:
                    self.selected_point_index = nearest_index
                    self.is_dragging = True
                    self.clicked.emit(x, y, nearest_index)

            self.update()

    def mouseMoveEvent(self, event):
        if self.is_dragging and 0 <= self.selected_point_index < len(self.calibration_points):
            x = event.x()
            y = event.y()
            self.calibration_points[self.selected_point_index] = (x, y)
            self.clicked.emit(x, y, self.selected_point_index)
            self.update()

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.is_dragging = False

    def paintEvent(self, event):
        super().paintEvent(event)
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        if self.target_point:
            x, y = self.target_point
            x = max(0, min(x, self.width() - 1))
            y = max(0, min(y, self.height() - 1))
            painter.setPen(QPen(QColor(255, 0, 255), 3))
            painter.drawEllipse(x - 8, y - 8, 16, 16)
            painter.drawLine(x - 12, y, x + 12, y)
            painter.drawLine(x, y - 15, x, y + 15)
            painter.setPen(QPen(Qt.black, 1))
            text_x = x + 15
            text_y = y - 10
            if text_x > self.width() - 50:
                text_x = x - 65
            if text_y < 15:
                text_y = y + 25
            painter.drawText(text_x, text_y, "目标")

        for i, (x, y) in enumerate(self.calibration_points):
            if i == 0:
                color = QColor(255, 0, 0)
            elif i == 1:
                color = QColor(0, 255, 0)
            elif i == 2:
                color = QColor(0, 0, 255)
            else:
                color = QColor(255, 255, 0)

            painter.setPen(QPen(color, 3))
            painter.drawEllipse(x - 5, y - 5, 10, 10)

            painter.setPen(QPen(Qt.black, 1))
            painter.drawText(x + 8, y - 8, str(i + 1))

            painter.setPen(QPen(color, 1, Qt.DashLine))
            painter.drawLine(x - 15, y, x + 15, y)
            painter.drawLine(x, y - 15, x, y + 15)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.serial = QSerialPort()
        self.cap = None
        self.calibration_points = []
        self.is_calibrated = False
        self.image_width = 640
        self.image_height = 480

        self.detection_results = None
        self.project_dir = Path(__file__).resolve().parent
        self.dataset_dir = self.project_dir / "dataset"
        self.image_count = 0
        self.latest_frame = None
        self.yolo_model = None
        self.collection_timer = QTimer(self)
        self.collection_timer.timeout.connect(self.capture_image)
        self.image_size = 640

        self.color_ranges = {
            "红色": {
                "lower1": np.array([0, 90, 60]),
                "upper1": np.array([10, 220, 250]),
                "lower2": np.array([155, 45, 35]),
                "upper2": np.array([179, 210, 230])
            },
            "绿色": {
                "lower": np.array([40, 20, 100]),
                "upper": np.array([80, 100, 200])
            },
            "蓝色": {
                "lower": np.array([90, 100, 50]),
                "upper": np.array([130, 255, 200])
            },
            "黄色": {
                "lower": np.array([20, 65, 72]),
                "upper": np.array([28, 178, 168])
            }
        }

        self.threshold_offset = 30
        self.current_target_coord = None

        self.camera_timer = QTimer()
        self.camera_timer.timeout.connect(self.update_frame)

        self.init_ui()
        self.load_calibration_points()

    def init_ui(self):
        self.setWindowTitle("视觉工作台 · 标定与数据采集")
        self.resize(1180, 820)
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setFrameShape(QScrollArea.NoFrame)
        self.setCentralWidget(scroll)
        central = QWidget()
        scroll.setWidget(central)
        root = QVBoxLayout(central)
        root.setContentsMargins(20, 12, 20, 12)
        root.setSpacing(10)

        heading = QHBoxLayout()
        title = QLabel("视觉工作台")
        title.setObjectName("pageTitle")
        heading.addWidget(title)
        heading.addStretch()
        self.camera_status = QLabel("●  摄像头未连接")
        self.camera_status.setObjectName("statusBadge")
        heading.addWidget(self.camera_status)
        root.addLayout(heading)
        subtitle = QLabel("连接摄像头，完成平面标定、目标检测与训练图像采集。")
        subtitle.setObjectName("muted")
        root.addWidget(subtitle)

        camera_card = QGroupBox("设备连接")
        toolbar = QHBoxLayout(camera_card)
        self.camera_combo = QComboBox()
        self.camera_combo.addItems(["摄像头0", "摄像头1", "摄像头2"])
        self.start_camera_btn = QPushButton("开启摄像头")
        self.stop_camera_btn = QPushButton("关闭摄像头")
        self.stop_camera_btn.setObjectName("secondary")
        toolbar.addWidget(self.camera_combo)
        toolbar.addWidget(self.start_camera_btn)
        toolbar.addWidget(self.stop_camera_btn)
        toolbar.addStretch()
        toolbar.addWidget(QLabel("预览区域 640 × 480"))
        self.start_camera_btn.clicked.connect(self.start_camera)
        self.stop_camera_btn.clicked.connect(self.stop_camera)
        root.addWidget(camera_card)

        body = QHBoxLayout()
        body.setSpacing(18)
        left = QVBoxLayout()
        preview_tabs = QTabWidget()
        for text, attr, clickable in [("原始画面 / 标定点", "original_label", True),
                                       ("目标识别结果", "processed_label", False)]:
            page = QWidget()
            layout = QVBoxLayout(page)
            layout.setContentsMargins(12, 12, 12, 12)
            label = ClickableImageLabel() if clickable else QLabel()
            label.setFixedSize(640, 480)
            label.setObjectName("videoPreview")
            label.setAlignment(Qt.AlignTop | Qt.AlignLeft)
            label.setText("等待摄像头画面…\n\n请先点击上方「开启摄像头」")
            setattr(self, attr, label)
            layout.addWidget(label, 0, Qt.AlignCenter)
            preview_tabs.addTab(page, text)
        self.original_label.clicked.connect(self.on_image_clicked)
        self.original_label.coordinate_selected.connect(self.on_target_coordinate_selected)
        left.addWidget(preview_tabs)
        hint = QLabel("标定提示：依次点击 4 个参考点；按住已有点可以拖动微调。")
        hint.setObjectName("muted")
        hint.setWordWrap(True)
        left.addWidget(hint)
        left.addStretch()
        body.addLayout(left, 3)

        right = QVBoxLayout()
        controls = QTabWidget()
        controls.setMinimumWidth(390)
        calibration = QWidget()
        cal = QVBoxLayout(calibration)
        cal.setContentsMargins(16, 16, 16, 16)
        cal.setSpacing(12)
        note = QLabel("01  坐标标定\n将画面中的四个参考点与工作台实际坐标一一对应。")
        note.setWordWrap(True)
        cal.addWidget(note)
        self.calibration_table = QTableWidget(4, 5)
        self.calibration_table.setHorizontalHeaderLabels(["点位", "像素X", "像素Y", "实际X", "实际Y"])
        self.calibration_table.verticalHeader().hide()
        self.calibration_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.calibration_table.setAlternatingRowColors(True)
        self.calibration_table.setFixedHeight(190)
        for i, (x, y) in enumerate([(70, -130), (70, -50), (130, -130), (130, -50)]):
            self.calibration_table.setRowHeight(i, 36)
            for j, value in enumerate([str(i+1), "0", "0", str(x), str(y)]):
                item = QTableWidgetItem(value)
                item.setTextAlignment(Qt.AlignCenter)
                if j == 0:
                    item.setFlags(item.flags() & ~Qt.ItemIsEditable)
                self.calibration_table.setItem(i, j, item)
        cal.addWidget(self.calibration_table)
        row = QHBoxLayout()
        self.calculate_btn = QPushButton("验证并保存标定")
        self.clear_cal_btn = QPushButton("清空标定")
        self.clear_cal_btn.setObjectName("secondary")
        row.addWidget(self.calculate_btn)
        row.addWidget(self.clear_cal_btn)
        self.calculate_btn.clicked.connect(self.calculate_transformation)
        self.clear_cal_btn.clicked.connect(self.clear_calibration)
        cal.addLayout(row)
        cal.addSpacing(12)
        cal.addWidget(QLabel("02  目标检测"))
        self.camera_coord_label = QLabel("(0, 0)")
        coord = QHBoxLayout()
        coord.addWidget(QLabel("选中像素坐标"))
        coord.addWidget(self.camera_coord_label)
        coord.addStretch()
        cal.addLayout(coord)
        self.confirm_count_btn = QPushButton("检测彩色方块")
        self.confirm_count_btn.clicked.connect(self.detect_color_targets)
        cal.addWidget(self.confirm_count_btn)
        cal.addStretch()
        controls.addTab(calibration, "标定与检测")

        collection = QWidget()
        collect = QVBoxLayout(collection)
        collect.setContentsMargins(16, 16, 16, 16)
        collect.setSpacing(12)
        note = QLabel("采集训练图像\n保存摄像头原始画面，不包含标定点和检测标记。")
        note.setWordWrap(True)
        collect.addWidget(note)
        self.count_label = QLabel("0")
        self.count_label.setObjectName("captureCount")
        collect.addWidget(self.count_label)
        collect.addWidget(QLabel("本次会话已采集 / 张"))
        self.path_label = QLabel(str(self.dataset_dir))
        self.path_label.setWordWrap(True)
        self.path_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.path_label.setObjectName("pathLabel")
        collect.addWidget(QLabel("保存目录"))
        collect.addWidget(self.path_label)
        self.choose_dir_btn = QPushButton("选择保存目录…")
        self.choose_dir_btn.setObjectName("secondary")
        self.choose_dir_btn.clicked.connect(self.choose_dataset_directory)
        collect.addWidget(self.choose_dir_btn)
        self.capture_btn = QPushButton("采集一张图像")
        self.capture_btn.clicked.connect(self.capture_image)
        collect.addWidget(self.capture_btn)
        interval_row = QHBoxLayout()
        interval_row.addWidget(QLabel("连续采集间隔"))
        self.interval_spin = QDoubleSpinBox()
        self.interval_spin.setRange(0.5, 60)
        self.interval_spin.setValue(2)
        self.interval_spin.setSingleStep(0.5)
        self.interval_spin.setSuffix(" 秒")
        interval_row.addWidget(self.interval_spin)
        collect.addLayout(interval_row)
        self.auto_capture_btn = QPushButton("开始连续采集")
        self.auto_capture_btn.setObjectName("secondary")
        self.auto_capture_btn.clicked.connect(self.toggle_collection)
        collect.addWidget(self.auto_capture_btn)
        self.last_capture_label = QLabel("尚未采集图像")
        self.last_capture_label.setWordWrap(True)
        self.last_capture_label.setObjectName("muted")
        collect.addWidget(self.last_capture_label)
        tip = QLabel("建议变换物体位置、角度和光照。采集得到 JPG 图片，训练前还需标注。")
        tip.setWordWrap(True)
        tip.setObjectName("muted")
        collect.addWidget(tip)
        collect.addStretch()
        controls.addTab(collection, "数据采集")
        right.addWidget(controls)
        logs = QGroupBox("运行记录")
        log_layout = QVBoxLayout(logs)
        self.info_text = QTextEdit()
        self.info_text.setReadOnly(True)
        self.info_text.document().setMaximumBlockCount(300)
        self.info_text.setMinimumHeight(100)
        self.info_text.setMaximumHeight(140)
        log_layout.addWidget(self.info_text)
        controls.addTab(logs, "运行记录")
        body.addLayout(right, 2)
        root.addLayout(body)
        self.set_camera_controls(False)
        self.set_style()

    def set_style(self):
        self.setStyleSheet("""
            QMainWindow, QScrollArea, QScrollArea > QWidget > QWidget { background: #f2f5fa; }
            QWidget { color: #24324a; font-size: 13px; }
            QLabel#pageTitle { font-size: 28px; font-weight: bold; color: #14243e; }
            QLabel#muted { color: #718096; font-size: 12px; }
            QLabel#statusBadge { color: #52647a; background: #e5ebf3;
                border-radius: 14px; padding: 8px 14px; }
            QGroupBox { background: white; border: 1px solid #dfe6ef;
                border-radius: 12px; margin-top: 10px; padding: 14px 10px 8px; font-weight: bold; }
            QGroupBox::title { subcontrol-origin: margin; left: 16px; padding: 0 6px; }
            QTabWidget::pane { border: 1px solid #dfe6ef; background: white;
                border-radius: 10px; }
            QTabBar::tab { background: #e8edf5; color: #61718a; padding: 11px 18px;
                margin-right: 4px; border-top-left-radius: 8px; border-top-right-radius: 8px; }
            QTabBar::tab:selected { background: white; color: #2563eb; font-weight: bold; }
            QPushButton { background: #2563eb; color: white; border: 1px solid #2563eb;
                border-radius: 8px; padding: 10px 14px; font-weight: bold; }
            QPushButton:hover { background: #1d4ed8; }
            QPushButton:pressed { background: #1e40af; }
            QPushButton#secondary { background: #eef3fc; color: #315582; border-color: #dbe5f5; }
            QPushButton#secondary:hover { background: #dfe9fa; }
            QPushButton:disabled, QPushButton#secondary:disabled {
                background: #edf0f4; border-color: #e4e8ee; color: #9ba6b5; }
            QComboBox, QDoubleSpinBox { background: white; border: 1px solid #d6deeb;
                border-radius: 7px; padding: 8px; min-width: 95px; }
            QTableWidget { background: white; alternate-background-color: #f5f8fd;
                border: 1px solid #e1e7f0; border-radius: 6px; gridline-color: #e8edf5;
                selection-background-color: #dbeafe; selection-color: #1e40af; }
            QHeaderView::section { background: #edf3fc; color: #526580;
                border: none; padding: 8px 2px; font-weight: bold; }
            QTextEdit { background: #f8fafc; border: 1px solid #e4eaf3;
                border-radius: 7px; padding: 8px; font-size: 12px; }
            QLabel#videoPreview { background: #111d30; color: #9caec6; border-radius: 6px;
                border: none; }
            QLabel#captureCount { font-size: 46px; font-weight: bold; color: #2563eb; }
            QLabel#pathLabel { background: #f1f5fb; padding: 10px; border-radius: 7px; color: #526580; }
        """)

    def set_camera_controls(self, active):
        self.start_camera_btn.setEnabled(not active)
        self.stop_camera_btn.setEnabled(active)
        self.camera_combo.setEnabled(not active)
        self.capture_btn.setEnabled(active)
        self.auto_capture_btn.setEnabled(active)
        self.confirm_count_btn.setEnabled(active)
        self.camera_status.setText("●  摄像头已连接" if active else "●  摄像头未连接")

    def choose_dataset_directory(self):
        directory = QFileDialog.getExistingDirectory(self, "选择数据集保存目录", str(self.dataset_dir))
        if directory:
            self.dataset_dir = Path(directory)
            self.path_label.setText(str(self.dataset_dir))

    def stop_collection(self):
        self.collection_timer.stop()
        self.auto_capture_btn.setText("开始连续采集")
        self.interval_spin.setEnabled(True)
        self.choose_dir_btn.setEnabled(True)

    def toggle_collection(self):
        if self.collection_timer.isActive():
            self.stop_collection()
            self.info_text.append("连续采集已停止")
        elif self.cap and self.cap.isOpened():
            self.collection_timer.start(round(self.interval_spin.value() * 1000))
            self.auto_capture_btn.setText("停止连续采集")
            self.interval_spin.setEnabled(False)
            self.choose_dir_btn.setEnabled(False)
            self.info_text.append("连续采集已开始")

    def create_serial_config(self):
        group = QGroupBox("串口通信")
        group_font = QFont()
        group_font.setPointSize(12)
        group_font.setBold(True)
        group.setFont(group_font)
        layout = QHBoxLayout(group)

        layout.addWidget(QLabel("端口："))
        self.port_combo = QComboBox()
        self.port_combo.setFixedWidth(120)
        combo_font = QFont()
        combo_font.setPointSize(10)
        self.port_combo.setFont(combo_font)
        layout.addWidget(self.port_combo)

        self.refresh_btn = QPushButton("刷新")
        self.open_btn = QPushButton("打开")
        self.close_btn = QPushButton("关闭")
        self.send_btn = QPushButton("发送")

        for btn in [self.refresh_btn, self.open_btn, self.close_btn, self.send_btn]:
            btn.setFixedWidth(70)
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
            """)

        self.refresh_btn.clicked.connect(self.update_serial_ports)
        self.open_btn.clicked.connect(self.open_serial)
        self.close_btn.clicked.connect(self.close_serial)
        self.send_btn.clicked.connect(self.send_serial_data)

        layout.addWidget(self.refresh_btn)
        layout.addWidget(self.open_btn)
        layout.addWidget(self.close_btn)
        layout.addWidget(self.send_btn)

        self.status_label = QLabel("未连接")
        self.status_label.setStyleSheet("color: red; font-weight: bold;")
        layout.addWidget(self.status_label)

        layout.addStretch()
        return group

    def update_serial_ports(self):
        self.port_combo.clear()
        try:
            ports = QSerialPortInfo.availablePorts()
            for port in ports:
                self.port_combo.addItem(port.portName())
        except Exception as e:
            self.info_text.append(f"获取串口失败：{str(e)}")

    def open_serial(self):
        try:
            self.port_name = self.port_combo.currentText()
            if not self.port_name:
                self.info_text.append("错误：请选择串口")
                return

            self.serial.setPortName(self.port_name)
            self.serial.setBaudRate(QSerialPort.Baud115200)
            self.serial.setDataBits(QSerialPort.Data8)
            self.serial.setParity(QSerialPort.NoParity)
            self.serial.setStopBits(QSerialPort.OneStop)
            self.serial.setFlowControl(QSerialPort.NoFlowControl)

            if self.serial.open(QSerialPort.ReadWrite):
                self.status_label.setText("已连接")
                self.status_label.setStyleSheet("color: green;")
                self.info_text.append(f"串口 {self.port_name} 打开成功")
            else:
                error_msg = self.serial.errorString()
                self.info_text.append(f"串口打开失败：{error_msg}")

        except Exception as e:
            self.info_text.append(f"串口打开失败：{str(e)}")

    def close_serial(self):
        if self.serial and self.serial.isOpen():
            self.serial.close()
        self.status_label.setText("未连接")
        self.status_label.setStyleSheet("color: red;")
        self.info_text.append("串口已关闭")

    def send_uint8_data(self, data, length):
        if not self.serial or not self.serial.isOpen():
            self.info_text.append("错误：串口未连接")
            return -1

        if not data or length <= 0:
            self.info_text.append("错误：数据无效")
            return -1

        try:
            bytes_written = self.serial.write(bytes(data[:length]))
            if bytes_written > 0:
                self.serial.waitForBytesWritten(100)
                return bytes_written
            else:
                self.info_text.append("错误：数据写入失败")
                return -1
        except Exception as e:
            self.info_text.append(f"数据发送失败：{str(e)}")
            return -1

    def send_serial_data(self, data=None):
        if not self.serial or not self.serial.isOpen():
            self.info_text.append("错误：串口未连接")
            return

        try:
            if data is None:
                self.robotic_arm.uart_tran_axis_data()
                data = self.robotic_arm.data_send[:self.robotic_arm.send_length]

            result = self.send_uint8_data(data, len(data))
            if result != -1:
                self.info_text.append("指令发送成功")

        except Exception as e:
            self.info_text.append(f"发送失败：{str(e)}")

    def send_tool_command(self, tool_state):
        if not self.serial or not self.serial.isOpen():
            self.info_text.append("错误：串口未连接")
            return False

        try:
            self.robotic_arm.uart_tran_tool_data(tool_state)
            data = self.robotic_arm.data_send[:self.robotic_arm.send_length]

            result = self.send_uint8_data(data, len(data))
            if result != -1:
                self.info_text.append(f"工具控制指令发送成功: 状态={tool_state}")
                return True
            else:
                return False

        except Exception as e:
            self.info_text.append(f"工具控制发送失败：{str(e)}")
            return False

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
                self.info_text.append(f"错误：无法打开摄像头 {camera_index}")
                return

            self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, self.image_width)
            self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, self.image_height)

            actual_width = self.cap.get(cv2.CAP_PROP_FRAME_WIDTH)
            actual_height = self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
            self.info_text.append(f"摄像头分辨率: {actual_width} x {actual_height}")

            self.camera_timer.start(30)

            self.latest_frame = None
            self.set_camera_controls(True)

            self.info_text.append(f"摄像头 {camera_index} 开启成功")

        except Exception as e:
            QMessageBox.critical(self, "错误", f"摄像头开启失败: {str(e)}")
            self.info_text.append(f"摄像头错误：{str(e)}")

    def stop_camera(self):
        self.stop_collection()
        self.latest_frame = None
        if self.cap:
            self.camera_timer.stop()
            self.cap.release()
            self.cap = None

        self.set_camera_controls(False)
        self.original_label.clear()
        self.processed_label.clear()

        self.original_label.setText("摄像头已关闭")
        self.processed_label.setText("摄像头已关闭")

        self.info_text.append("摄像头已关闭")

    def update_frame(self):
        if self.cap and self.cap.isOpened():
            ret, frame = self.cap.read()
            if ret:
                self.latest_frame = frame.copy()
                try:
                    rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                    h, w, ch = rgb_image.shape
                    bytes_per_line = ch * w
                    qt_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)

                    pixmap = QPixmap.fromImage(qt_image).scaled(
                        640, 480, Qt.IgnoreAspectRatio, Qt.SmoothTransformation)
                    self.original_label.setPixmap(pixmap)

                    processed_frame = self.process_frame(frame)
                    if processed_frame is not None:
                        rgb_processed = cv2.cvtColor(processed_frame, cv2.COLOR_BGR2RGB)
                        qt_processed = QImage(rgb_processed.data, w, h, bytes_per_line, QImage.Format_RGB888)
                        pixmap_processed = QPixmap.fromImage(qt_processed).scaled(
                            640, 480, Qt.IgnoreAspectRatio, Qt.SmoothTransformation)
                        self.processed_label.setPixmap(pixmap_processed)

                except Exception as e:
                    self.info_text.append(f"图像显示错误: {str(e)}")
            else:
                self.latest_frame = None
                if self.collection_timer.isActive():
                    self.stop_collection()
                    self.info_text.append("连续采集已停止：无法读取摄像头画面")

    def process_frame(self, frame):
        try:
            result = frame.copy()
            
            if self.detection_results is not None:
                color_configs = [("蓝色", (255, 0, 0), "0"), ("绿色", (0, 255, 0), "1"), ("红色", (0, 0, 255), "2"), ("黄色", (0, 255, 255), "3")]
                
                for color_name, bgr_color, color_code in color_configs:
                    if color_name in self.detection_results:
                        for (cx, cy) in self.detection_results[color_name]:
                            cv2.circle(result, (cx, cy), 8, bgr_color, -1)
                            cv2.circle(result, (cx, cy), 12, (255, 255, 255), 2)

            return result

        except Exception as e:
            print(f"图像处理错误: {e}")
            return frame

    def capture_image(self):
        if not self.cap or not self.cap.isOpened():
            self.stop_collection()
            self.info_text.append("采集失败：请先开启摄像头")
            return
        if self.latest_frame is None:
            self.info_text.append("采集失败：等待有效摄像头画面")
            return
        try:
            self.dataset_dir.mkdir(parents=True, exist_ok=True)
            filename = self.dataset_dir / ("image_" + datetime.now().strftime("%Y%m%d_%H%M%S_%f") + ".jpg")
            # imencode + tofile supports Chinese paths on Windows as well as Linux.
            success, encoded = cv2.imencode(".jpg", self.latest_frame.copy())
            if not success:
                raise OSError("图像编码失败")
            encoded.tofile(str(filename))
        except Exception as e:
            self.stop_collection()
            self.info_text.append(f"采集失败：{e}")
            return
        self.image_count += 1
        self.count_label.setText(str(self.image_count))
        self.last_capture_label.setText("最近保存：" + filename.name)
        self.info_text.append(f"已采集：{filename.name}")

    def on_image_clicked(self, x, y, point_index):
        try:
            scale_x = self.image_width / 640
            scale_y = self.image_height / 480
            actual_x = int(x * scale_x)
            actual_y = int(y * scale_y)

            if 0 <= point_index < 4:
                self.calibration_table.item(point_index, 1).setText(str(actual_x))
                self.calibration_table.item(point_index, 2).setText(str(actual_y))

                current_points = len(self.original_label.calibration_points)
                self.info_text.append(
                    f"标定点{point_index + 1}坐标: ({actual_x}, {actual_y}) - 已设置{current_points}/4个点")

        except Exception as e:
            self.info_text.append(f"设置标定点失败：{str(e)}")

    def on_target_coordinate_selected(self, x, y):
        try:
            scale_x = self.image_width / 640
            scale_y = self.image_height / 480
            actual_x = int(x * scale_x)
            actual_y = int(y * scale_y)

            self.current_target_coord = (actual_x, actual_y)
            self.camera_coord_label.setText(f"({actual_x}, {actual_y})")
            self.info_text.append(f"手动选择目标坐标: ({actual_x}, {actual_y})")

        except Exception as e:
            self.info_text.append(f"设置目标坐标失败：{str(e)}")

    def detect_color_targets(self):
        if not self.cap or not self.cap.isOpened():
            self.info_text.append("错误：请先开启摄像头")
            return

        try:
            self.calculate_transformation()
            
            ret, frame = self.cap.read()
            if not ret:
                self.info_text.append("错误：无法获取图像")
                return

            self.info_text.append("开始使用YOLO检测物体...")

            if self.yolo_model is None:
                self.yolo_model = YOLO(str(self.project_dir / "best.pt"))
            results = self.yolo_model(frame, imgsz=self.image_size)
            
            self.detection_results = {}
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
            
            if blue_targets:
                self.detection_results["蓝色"] = blue_targets
            if green_targets:
                self.detection_results["绿色"] = green_targets
            if red_targets:
                self.detection_results["红色"] = red_targets
            if yellow_targets:
                self.detection_results["黄色"] = yellow_targets
            
            self.info_text.append(f"检测完成: 蓝色{len(blue_targets)}个, 绿色{len(green_targets)}个, 红色{len(red_targets)}个, 黄色{len(yellow_targets)}个")

            camera_points = []
            actual_points = []
            
            for i in range(4):
                cam_x_item = self.calibration_table.item(i, 1)
                cam_y_item = self.calibration_table.item(i, 2)
                actual_x_item = self.calibration_table.item(i, 3)
                actual_y_item = self.calibration_table.item(i, 4)
                
                if cam_x_item and cam_y_item and actual_x_item and actual_y_item:
                    try:
                        cam_x = float(cam_x_item.text())
                        cam_y = float(cam_y_item.text())
                        actual_x = float(actual_x_item.text())
                        actual_y = float(actual_y_item.text())
                        
                        if cam_x != 0 and cam_y != 0:
                            camera_points.append([cam_x, cam_y])
                            actual_points.append([actual_x, actual_y])
                    except ValueError:
                        pass
            
            output_lines = []
            
            if len(camera_points) >= 4:
                src_pts = np.float32(camera_points)
                dst_pts = np.float32(actual_points)
                M = cv2.getPerspectiveTransform(src_pts, dst_pts)
                
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
            else:
                self.info_text.append("警告：标定点不足，使用原始像素坐标")
                
                for i, (x, y) in enumerate(blue_targets):
                    coord_x = round(x / 1000, 3)
                    coord_y = round(y / 1000, 3)
                    output_lines.append(f"blue cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")
                
                for i, (x, y) in enumerate(red_targets):
                    coord_x = round(x / 1000, 3)
                    coord_y = round(y / 1000, 3)
                    output_lines.append(f"red cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")
                
                for i, (x, y) in enumerate(green_targets):
                    coord_x = round(x / 1000, 3)
                    coord_y = round(y / 1000, 3)
                    output_lines.append(f"green cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")
                
                for i, (x, y) in enumerate(yellow_targets):
                    coord_x = round(x / 1000, 3)
                    coord_y = round(y / 1000, 3)
                    output_lines.append(f"yellow cube {i+1}: [{coord_x:.3f}, {coord_y:.3f}, 0.010]")

            if output_lines:
                output_str = "\n".join(output_lines)
                print(output_str)
                self.info_text.append("输出结果:")
                for line in output_lines:
                    self.info_text.append(line)
            else:
                self.info_text.append("未检测到任何目标")

        except Exception as e:
            self.info_text.append(f"检测目标失败：{str(e)}")

    def detect_color_all(self, frame, color_name):
        """自动检测所有指定颜色的色块"""
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        color_range = self.color_ranges[color_name]

        height, width = frame.shape[:2]

        if color_name == "红色":
            mask1 = cv2.inRange(hsv, color_range["lower1"], color_range["upper1"])
            mask2 = cv2.inRange(hsv, color_range["lower2"], color_range["upper2"])
            mask = mask1 + mask2
        elif color_name == "绿色":
            mask = self.detect_green_color(hsv, frame)
        else:
            mask = cv2.inRange(hsv, color_range["lower"], color_range["upper"])

        if color_name == "绿色":
            kernel = np.ones((7, 7), np.uint8)
            mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=3)
            mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)
        else:
            kernel = np.ones((5, 5), np.uint8)
            mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=2)
            mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)

        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        selected_points = []
        excluded_regions = []
        
        for contour in contours:
            area = cv2.contourArea(contour)
            
            if color_name == "绿色":
                min_area = 60
            elif color_name == "红色":
                min_area = 100
            else:
                min_area = 80
            
            if area > min_area:
                x, y, w, h = cv2.boundingRect(contour)
                aspect_ratio = w / float(h)
                
                if color_name == "红色":
                    min_aspect, max_aspect = 0.7, 1.3
                else:
                    min_aspect, max_aspect = 0.6, 1.4
                
                if min_aspect < aspect_ratio < max_aspect:
                    if color_name == "红色":
                        edge_margin = 20
                        if x < edge_margin or y < edge_margin or \
                           (x + w) > (width - edge_margin) or \
                           (y + h) > (height - edge_margin):
                            continue
                    
                    if color_name == "绿色":
                        cx = int(x + w / 2)
                        cy = int(y + h / 2)
                    else:
                        cx = int(x + w / 2)
                        cy = int(y + h / 2)
                        
                        M = cv2.moments(contour)
                        if M["m00"] != 0:
                            mcx = int(M["m10"] / M["m00"])
                            mcy = int(M["m01"] / M["m00"])
                            cx = (cx + mcx) // 2
                            cy = (cy + mcy) // 2
                
                    is_excluded = False
                    for ex_x, ex_y in excluded_regions:
                        distance = math.sqrt((cx - ex_x) ** 2 + (cy - ex_y) ** 2)
                        if distance < 50:
                            is_excluded = True
                            break
                    
                    if not is_excluded:
                        selected_points.append((cx, cy))
                        excluded_regions.append((cx, cy))

        return selected_points

    def detect_color_points(self, frame, color_name, count):
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        color_range = self.color_ranges[color_name]

        if color_name == "红色":
            mask1 = cv2.inRange(hsv, color_range["lower1"], color_range["upper1"])
            mask2 = cv2.inRange(hsv, color_range["lower2"], color_range["upper2"])
            mask = mask1 + mask2
        elif color_name == "绿色":
            mask = self.detect_green_color(hsv, frame)
        else:
            mask = cv2.inRange(hsv, color_range["lower"], color_range["upper"])

        if color_name == "绿色":
            kernel = np.ones((7, 7), np.uint8)
            mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=3)
            mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)
        else:
            kernel = np.ones((5, 5), np.uint8)
            mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=2)
            mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)

        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        contour_centers = []
        for contour in contours:
            area = cv2.contourArea(contour)
            min_area = 60 if color_name == "绿色" else 80
            if area > min_area:
                x, y, w, h = cv2.boundingRect(contour)
                aspect_ratio = w / float(h)
                
                if 0.6 < aspect_ratio < 1.4:
                    if color_name == "绿色":
                        cx = int(x + w / 2)
                        cy = int(y + h / 2)
                    else:
                        cx = int(x + w / 2)
                        cy = int(y + h / 2)
                        
                        M = cv2.moments(contour)
                        if M["m00"] != 0:
                            mcx = int(M["m10"] / M["m00"])
                            mcy = int(M["m01"] / M["m00"])
                            cx = (cx + mcx) // 2
                            cy = (cy + mcy) // 2
                    
                    contour_centers.append((-area, cx, cy))

        contour_centers.sort()

        selected_points = []
        excluded_regions = []

        for neg_area, cx, cy in contour_centers:
            is_excluded = False
            for ex_x, ex_y in excluded_regions:
                distance = math.sqrt((cx - ex_x) ** 2 + (cy - ex_y) ** 2)
                if distance < 50:
                    is_excluded = True
                    break

            if not is_excluded:
                selected_points.append((cx, cy))
                excluded_regions.append((cx, cy))
                
                if len(selected_points) >= count:
                    break

        if len(selected_points) < count:
            self.info_text.append(f"轮廓检测不足，使用像素级检测补充...")
            
            height, width = mask.shape
            pixel_probs = []

            for y in range(5, height - 5):
                for x in range(5, width - 5):
                    is_excluded = False
                    for ex_x, ex_y in excluded_regions:
                        distance = math.sqrt((x - ex_x) ** 2 + (y - ex_y) ** 2)
                        if distance < 50:
                            is_excluded = True
                            break
                    
                    if not is_excluded:
                        roi = mask[y-3:y+4, x-3:x+4]
                        roi_pixels = roi.size
                        roi_color_pixels = cv2.countNonZero(roi)
                        roi_prob = roi_color_pixels / roi_pixels if roi_pixels > 0 else 0
                        if roi_prob > 0.8:
                            pixel_probs.append((roi_prob, x, y))

            pixel_probs.sort(reverse=True, key=lambda x: x[0])

            for prob, x, y in pixel_probs:
                if len(selected_points) >= count:
                    break
                    
                is_excluded = False
                for ex_x, ex_y in excluded_regions:
                    distance = math.sqrt((x - ex_x) ** 2 + (y - ex_y) ** 2)
                    if distance < 50:
                        is_excluded = True
                        break

                if not is_excluded:
                    selected_points.append((x, y))
                    excluded_regions.append((x, y))

        self.info_text.append(f"检测{color_name}: 找到{len(selected_points)}个点")
        for i, (x, y) in enumerate(selected_points):
            self.info_text.append(f"  {color_name}点{i+1}: ({x}, {y})")

        return selected_points

    def detect_green_color(self, hsv, frame):
        """专门针对浅绿色方块的检测算法，增加与蓝色的区分"""
        h, s, v = cv2.split(hsv)
        
        hsv_mask = cv2.inRange(hsv, np.array([45, 40, 100]), np.array([70, 150, 200]))
        
        rgb = frame
        r, g, b = cv2.split(rgb)
        
        green_ratio = cv2.divide(g, r + 1, dtype=cv2.CV_32F)
        green_ratio = (green_ratio > 1.5).astype(np.uint8) * 255
        
        green_vs_blue = cv2.subtract(g, b)
        green_vs_blue = (green_vs_blue > 25).astype(np.uint8) * 255
        
        green_excess = cv2.subtract(g, r)
        green_excess = cv2.subtract(green_excess, b)
        green_excess = (green_excess > 12).astype(np.uint8) * 255
        
        blue_mask = cv2.inRange(hsv, np.array([90, 80, 50]), np.array([130, 255, 200]))
        blue_mask_inv = cv2.bitwise_not(blue_mask)
        
        mask2 = cv2.bitwise_and(green_ratio, green_vs_blue)
        mask2 = cv2.bitwise_and(mask2, green_excess)
        mask2 = cv2.bitwise_and(mask2, blue_mask_inv)
        
        final_mask = cv2.bitwise_or(hsv_mask, mask2)
        
        kernel = np.ones((3, 3), np.uint8)
        final_mask = cv2.morphologyEx(final_mask, cv2.MORPH_DILATE, kernel, iterations=2)
        final_mask = cv2.morphologyEx(final_mask, cv2.MORPH_ERODE, kernel, iterations=1)
        
        return final_mask

    def calculate_transformation(self):
        try:
            camera_points = []

            for i in range(4):
                cam_x_item = self.calibration_table.item(i, 1)
                cam_y_item = self.calibration_table.item(i, 2)

                if cam_x_item and cam_y_item and cam_x_item.text().strip() and cam_y_item.text().strip():
                    try:
                        cam_x = float(cam_x_item.text())
                        cam_y = float(cam_y_item.text())

                        if cam_x != 0 and cam_y != 0:
                            camera_points.append([cam_x, cam_y])
                            self.info_text.append(f"标定点{i + 1}: 摄像头({cam_x}, {cam_y})")
                        else:
                            self.info_text.append(f"警告：标定点{i + 1}坐标包含零值，跳过")
                    except ValueError:
                        self.info_text.append(f"错误：标定点{i + 1}坐标格式错误")
                else:
                    self.info_text.append(f"错误：标定点{i + 1}数据不完整")

            if len(camera_points) < 4:
                self.info_text.append(f"错误：需要4个有效的标定点，当前只有{len(camera_points)}个")
                return

            self.is_calibrated = True
            self.info_text.append("标定点验证成功")
            self.save_calibration_points()

        except Exception as e:
            self.info_text.append(f"标定验证失败：{str(e)}")

    def clear_calibration(self):
        self.transformation_matrix = None
        self.is_calibrated = False
        self.current_target_coord = None

        for i in range(4):
            for j in range(1, 5):
                self.calibration_table.item(i, j).setText("0")

        self.original_label.calibration_points.clear()
        self.original_label.target_point = None
        self.original_label.update()
        self.camera_coord_label.setText("(0, 0)")
        self.info_text.append("标定数据已清空")

    def save_calibration_points(self):
        try:
            lines = []
            for i in range(4):
                cam_x_item = self.calibration_table.item(i, 1)
                cam_y_item = self.calibration_table.item(i, 2)
                actual_x_item = self.calibration_table.item(i, 3)
                actual_y_item = self.calibration_table.item(i, 4)
                
                cam_x = cam_x_item.text() if cam_x_item else "0"
                cam_y = cam_y_item.text() if cam_y_item else "0"
                actual_x = actual_x_item.text() if actual_x_item else "0"
                actual_y = actual_y_item.text() if actual_y_item else "0"
                
                lines.append(f"{cam_x},{cam_y},{actual_x},{actual_y}")
            
            with open(self.project_dir / "camera_parama.txt", "w") as f:
                f.write("\n".join(lines))
            self.info_text.append("标定坐标已保存到camera_parama.txt")
        except Exception as e:
            self.info_text.append(f"保存标定坐标失败：{str(e)}")

    def load_calibration_points(self):
        default_actual_coords = [
            (70, -130),
            (70, -50),
            (130, -130),
            (130, -50)
        ]
        
        try:
            with open(self.project_dir / "camera_parama.txt", "r") as f:
                lines = f.readlines()
            
            if len(lines) < 4:
                self.info_text.append("标定文件数据不足，使用默认值")
                return
            
            valid_count = 0
            for i in range(4):
                if i < len(lines):
                    line = lines[i].strip()
                    parts = line.split(",")
                    if len(parts) >= 4:
                        try:
                            float(parts[0])
                            float(parts[1])
                            actual_x = float(parts[2])
                            actual_y = float(parts[3])
                            
                            self.calibration_table.item(i, 1).setText(parts[0])
                            self.calibration_table.item(i, 2).setText(parts[1])
                            
                            if actual_x == 0 and actual_y == 0:
                                self.calibration_table.item(i, 3).setText(str(default_actual_coords[i][0]))
                                self.calibration_table.item(i, 4).setText(str(default_actual_coords[i][1]))
                            else:
                                self.calibration_table.item(i, 3).setText(parts[2])
                                self.calibration_table.item(i, 4).setText(parts[3])
                            
                            valid_count += 1
                        except ValueError:
                            pass
            
            if valid_count > 0:
                self.info_text.append(f"已加载上次的标定坐标，有效数据{valid_count}个")
            else:
                self.info_text.append("标定文件数据无效，使用默认值")
        except FileNotFoundError:
            self.info_text.append("未找到标定文件camera_parama.txt，使用默认值")
        except Exception as e:
            self.info_text.append(f"加载标定坐标失败：{str(e)}")

    def closeEvent(self, event):
        self.save_calibration_points()
        self.stop_collection()
        self.camera_timer.stop()
        if self.cap:
            self.cap.release()
        if self.serial.isOpen():
            self.serial.close()
        event.accept()


def main():
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()