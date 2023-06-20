import glob
from lxml import etree
from tabulate import tabulate
# Lấy danh sách tệp có đuôi .xml trong thư mục XML
xml_files = glob.glob(f"XML/*.xml")

# Nhập ngưỡng điểm
nguong_tren = float(input("Nhập ngưỡng điểm cao:"))
nguong_duoi = float(input("Nhập ngưỡng điểm thấp:"))

# Đọc và xử lý từng tệp XML
for xml_file in xml_files:
	# Đọc file XML vào một đối tượng ElementTree
	tree = etree.parse(xml_file)
	# Chọn tất cả các phần tử student có thẻ diemtb có giá trị nằm trong ngưỡng [thấp, cao]
	students = tree.xpath(f"//student[diemtb >= {nguong_duoi} and diemtb <= {nguong_tren}]")
	# Lưu thông tin của từng học sinh vào list
	table = []
	for student in students:
		ho_ten = student.findtext('ho_ten')
		ntns = student.findtext('ntns')
		diemtb = student.findtext('diemtb')
		xeploai = student.findtext('xeploai')
		ketqua = student.findtext('kqua')
		table.append([ho_ten, ntns, diemtb, xeploai, ketqua])
	# In ra bảng dữ liệu
	print(tabulate(table, headers=['Họ tên','NTNS','Điểm trung bình', 'Xếp loại','Kết quả'], tablefmt='grid'))
