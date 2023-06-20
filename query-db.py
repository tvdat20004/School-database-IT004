import time  
import xml.etree.ElementTree as ET 
import mysql.connector
import re
from datetime import datetime
import xml.dom.minidom
import getpass
import tabulate
import os

# Hàm nhập các giá trị cho truy vấn từ bàn phím (nhập theo yêu cầu, nếu nhập sai thì buộc phải nhập lại cho đến khi đúng)
def get_input():
	# Lấy thông tin về database name
	while True:
		print("""
Nhập tên database (1 hoặc 2)
1. truonghoc1
2. truonghoc2""")
		choose = input(">")
		# kiểm tra sự hợp lệ của input
		if choose == "1":
			database_name = "TRUONGHOC1"
			break
		elif choose == "2":
			database_name = "TRUONGHOC2"
			break
		else: 
			print("Input không hợp lệ, hãy nhập lại input.")
	# Nhập tên trường, nếu tên trường nhập vào không có trong database thì yêu cầu nhập lại.	
	with open("insert_query/DS_truong.txt",mode = 'r', encoding = 'utf-8') as ds:
		ds = ds.read().splitlines()
		ten_truong = None
		while ten_truong not in ds:
			print("Nhập tên trường:")
			ten_truong = input(">")
	#  Lấy thông tin về năm học
	while True: 
		print("""
Nhập năm học (1-3):
1. 2020-2021
2. 2021-2022
3. 2022-2023""")
		choose = input(">")
		if choose == "1":
			nam_hoc = "2020-2021"
			break
		elif choose == "2":
			nam_hoc = "2021-2022"
			break
		elif choose == "3":
			nam_hoc = "2022-2023"
			break
		else:
			print("Input không hợp lệ.")
	#  Lấy thông tin xếp loại học tập
	while True:
		print("""
Nhập xếp loại học tập (1-5):
1. Xuất sắc
2. Giỏi
3. Khá
4. Trung bình
5. Yếu""")
		choose = input(">")
		if choose == "1":
			xep_loai = "Xuất sắc"
			break
		elif choose == "2":
			xep_loai = "Giỏi"
			break
		elif choose == "3":
			xep_loai = "Khá"
			break
		elif choose == "4":
			xep_loai = "Trung bình"
			break
		elif choose == "5":
			xep_loai = "Yếu"
			break
		else:
			print("Input không hợp lệ.")
	return database_name, ten_truong, nam_hoc, xep_loai
# Hàm thực hiện truy vấn, sau đó in kết quả ra màn hình và tạo file XML theo yêu cầu
def query_and_print(database_name, truong, namhoc, xeploai):
	# Nhập mật khẩu và kết nối đến mySQL, nếu nhập sai mật khẩu thì thoát chương trình.
	password = getpass.getpass("Nhập password: ")
	try:
		connection = mysql.connector.connect(
			host = "localhost",
			user = "root",
			password = password,
			database = database_name
		)
	except:
		print("Mật khẩu sai!!")
		exit(0)
	# Đặt mốc thời gian bắt đầu 
	start_time = time.time()
	# Tạo đối tượng cursor để thực hiện truy vấn
	cursor = connection.cursor()
	# Thực hiện truy vấn dữ liệu
	query = """
	SELECT concat_ws(' ',HS.HO, HS.TEN) as HO_TEN, HS.NTNS, HOC.DIEMTB, HOC.XEPLOAI, HOC.KQUA
	FROM HS
	JOIN HOC ON HS.MAHS = HOC.MAHS
	JOIN TRUONG ON TRUONG.MATR = HOC.MATR
	WHERE TRUONG.TENTR = %s AND HOC.NAMHOC = %s AND HOC.XEPLOAI = %s
	"""
	values = (truong, namhoc, xeploai)
	cursor.execute(query, values)
	# Lấy kết quả truy vấn
	table = []
	for row in cursor.fetchall():
		table.append(row)
	# Đóng kết nối và cursor
	cursor.close()
	connection.close()
	# Đặt mốc kết thúc đo thời gian thực thi
	end_time = time.time()
	# In danh sách học sinh ra màn hình
	print(tabulate.tabulate(table, headers=['Họ tên','NTNS','Điểm trung bình', 'Xếp loại','Kết quả'], tablefmt='grid'))
	execution_time = end_time - start_time
	print("Thời gian truy vấn dữ liệu:", execution_time, "giây")

	# Tạo và xuất dữ liệu ra file XML
	root = ET.Element("students")
	for student in table:
		student_elem = ET.SubElement(root, "student")
		ET.SubElement(student_elem, "ho_ten").text = student[0]
		ET.SubElement(student_elem, "ntns").text = str(student[1])
		ET.SubElement(student_elem, "diemtb").text = str(student[2])
		ET.SubElement(student_elem, "xeploai").text = student[3]
		ET.SubElement(student_elem, "kqua").text = student[4]
	xml_filepath = f"XML/{database_name}-{truong}-{namhoc}-{xeploai}.xml"
	tree = ET.ElementTree(root)
	# Tạo thư mục mới
	if not os.path.exists("./XML"):
		os.mkdir("./XML")
	with open(xml_filepath, "wb") as xml_file:
		tree.write(xml_file)

	with open(xml_filepath, "r") as xml_file:
		xml_data = xml_file.read()

	# Parse tệp XML
	dom = xml.dom.minidom.parseString(xml_data)

	# Config tệp XML theo định dạng chuẩn
	xml_str = dom.toprettyxml(indent="  ")

	# Ghi nội dung tệp XML đã config vào file
	with open(xml_filepath, "w", encoding="utf-8") as file:
		file.write(xml_str)
database_name, truong, namhoc, xeploai = get_input()
query_and_print(database_name, truong, namhoc, xeploai)