#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <codecvt>
using namespace std;
const int MAX = 1e6;
// 20 họ phổ biến ở Việt Nam
vector<string> firstNames = {"Nguyễn", "Trần", "Lê", "Phạm", "Hoàng", "Huỳnh", "Phan", "Vũ", "Đặng", "Bùi", "Đỗ", "Hồ", "Ngô", "Dương", "Lý", "Doãn", "Lương", "Mai", "Lưu", "Thái" };
// 100 tên đệm phổ biến ở Việt Nam
vector<string> midNames = {"Nguyễn", "Trần", "Lê", "Phạm", "Hoàng", "Huỳnh", "Phan", "Vũ", "Đặng", "Bùi", "Đỗ", "Hồ", "Ngô", "Dương", "Lý", "Doãn", "Lương", "Mai", "Lưu", "Vương", "Đinh", "Trịnh", "Đoàn", "Đào", "Đinh", "Ân", "Tạ", "Triệu", "Tống", "Quách", "Tôn", "Hà", "Chu", "Dương", "Thái", "Đoàn", "Lục", "Từ", "Cao", "Vĩnh", "Mạc", "Đặng", "Mỹ", "Tiêu", "Từ", "Ninh", "Khương", "Lư", "Nông", "Tôn", "Lỗ", "Bạch", "Nhan", "Sơn", "Khương", "Thủy", "Trịnh", "Lê", "Tăng", "Cao", "Sử", "Mục", "Mông", "Quan", "Văn", "Hồng", "Lê", "Lý", "Mạnh", "Tăng", "Quan", "Mạc", "Triệu", "Tạ", "Tô", "Lý", "Bùi", "Khương", "Lục", "Ninh", "Đồng", "Từ", "Đinh", "Mạnh", "Chu", "Tạ", "Mạnh", "Tưởng", "Cao", "Tiên", "Thạch", "Mạnh", "Tiên", "Lý", "Đỗ", "Đoàn", "Chu", "Ninh", "Tạ", "Bùi"};
// 100 tên phổ biến ở Việt Nam
vector<string> lastNames = {"Huy", "Khang", "Bảo", "Minh", "Phúc", "Anh", "Khoa", "Phát", "Đạt", "Khôi", "Long", "Nam", "Duy", "Quân", "Kiệt", "Thịnh", "Tuấn", "Hưng", "Hoàng", "Hiếu", "Nhân", "Trí", "Tài", "Phong", "Nguyên", "An", "Phú", "Thành", "Đức", "Dũng", "Lộc", "Khánh", "Vinh", "Tiến", "Nghĩa", "Thiện", "Hào", "Hải", "Đăng", "Quang", "Lâm", "Nhật", "Trung", "Thắng", "Tú", "Hùng", "Tâm", "Sang", "Sơn", "Thái", "Cường", "Vũ", "Toàn", "Ân", "Thuận", "Bình", "Trường", "Danh", "Kiên", "Phước", "Thiên", "Tân", "Việt", "Khải", "Tín", "Dương", "Tùng", "Quý", "Hậu", "Trọng", "Triết", "Luân", "Phương", "Quốc", "Thông", "Khiêm", "Hòa", "Thanh", "Tường", "Kha", "Vỹ", "Bách", "Khanh", "Mạnh", "Lợi", "Đại", "Hiệp", "Đông", "Nhựt", "Giang", "Kỳ", "Phi", "Tấn", "Văn", "Vương", "Công", "Hiển", "Linh", "Ngọc", "Vĩ"};
// danh sách các trường ở TPHCM
vector<string> schools = {"THPT Bùi Thị Xuân", "THPT Trưng Vương", "THPT Giồng Ông Tố", "THPT Nguyễn Thị Minh Khai", "THPT Lê Quý Đôn", "THPT Nguyễn Trãi", "Phổ thông Năng khiếu thể thao Olympic", "THPT Hùng Vương", "THPT Mạc Đĩnh Chi", "THPT Bình Phú", "THPT Lê Thánh Tôn", "THPT Lương Văn Can", "THPT Ngô Gia Tự", "THPT Tạ Quang Bửu", "THPT Nguyễn Huệ", "THPT Nguyễn Khuyến", "THPT Nguyễn Du", "THPT Nguyễn Hiền", "THPT Võ Trường Toản", "THPT Thanh Đa", "THPT Võ Thị Sáu", "THPT Gia Định", "THPT Phan Đăng Lưu", "THPT Gò Vấp", "THPT Nguyễn Công Trứ", "THPT Phú Nhuận", "THPT Tân Bình", "THPT Nguyễn Chí Thanh", "THPT Trần Phú", "THPT Nguyễn Thượng Hiền", "THPT Thủ Đức", "THPT Nguyễn Hữu Huân", "THPT Tam Phú", "THPT Củ Chi", "THPT Quang Trung", "THPT An Nhơn Tây", "THPT Trung Phú", "THPT Trung Lập", "THPT Nguyễn Hữu Cầu", "THPT Lý Thường Kiệt", "THPT Bình Chánh", "THPT Ten Lơ Man", "THPT Marie Curie", "THPT Trần Khai Nguyên", "THPT Nguyễn An Ninh", "THPT Nam Kỳ Khởi Nghĩa", "THPT Nguyễn Thái Bình", "THPT Nguyễn Trung Trực", "THPT Hàn Thuyên", "THPT Hoàng Hoa Thám", "THPT Thăng Long", "THPT Phước Long", "THPT Bà Điểm", "THPT Tân Phong", "THPT Trường Chinh", "THPT Phú Hòa", "THPT Tân Thông Hội", "THPT Tây Thạnh", "THPT Long Trường", "THPT Nguyễn Văn Cừ", "THPT Nguyễn Hữu Tiến", "THPT Bình Khánh", "THPT Cần Thạnh", "THPT Trần Hưng Đạo", "THPT Hiệp Bình", "Tiểu học THCS và THPT Quốc Văn Sài Gòn", "THPT Trần Quang Khải", "THPT Vĩnh Lộc", "THPT Việt Âu", "THPT Việt Nhật", "THPT Hưng Đạo", "TH - THCS - THPT Nguyễn Văn Trỗi", "THPT Lê Lợi", "THPT Đoàn Thị Điểm", "THPT Đinh Thiện Lý", "THPT Chu Văn An", "THPT Huỳnh Thúc Kháng", "THPT Kỳ Đồng", "THPT Lý Tự Trọng", "THPT Nguyễn Du", "THPT Nguyễn Tất Thành", "THPT Nguyễn Thị Diệu", "THPT Nguyễn Thượng Hiền", "THPT Phạm Văn Đồng", "THPT Phan Bội Châu", "THPT Phan Chu Trinh", "THPT Trần Quốc Tuấn", "THPT Trường Sa", "THPT Tuyên Sơn", "THPT Vân Đồn", "THPT Vĩnh Phú", "THPT Võ Văn Tần", "THPT Trần Quốc Toản", "THPT Thoại Ngọc Hầu", "THPT Tôn Thất Tùng", "THPT Trường Võ", "THPT Việt - Mỹ", "THPT Võ Thị Sáu", "THPT Công Lý", "THPT Chu Văn An", "THPT Chuyên Lê Hồng Phong", "THPT Chuyên Khoa Học Tự Nhiên", "THPT Chuyên Khoa Học Xã Hội", "THPT Chuyên Ngoại Ngữ", "THPT Chuyên Sư Phạm", "THPT Chuyên Thích Quảng Đức", "THPT Chuyên Tổng Hợp", "THPT Chuyên Trần Đại Nghĩa", "THPT Chuyên Trần Đại Nghĩa Kỹ Thuật", "THPT Chuyên Trần Hưng Đạo", "THPT Chuyên Văn Hóa Nghệ Thuật", "THPT Chuyên Vật Lý - Kỹ Thuật", "THPT Chuyên Y Hà Nội", "THPT Đại Học Sư Phạm Hà Nội", "THPT Đại Sơn", "THPT Hà Nội - Amsterdam", "THPT Khoa Học Tự Nhiên", "THPT Kỹ Thuật Yên Bái", "THPT Lương Thế Vinh", "THPT Ngô Gia Tự", "THPT Phan Bội Châu", "THPT Sơn Hà", "THPT Sơn Lộc", "THPT Sư Phạm", "THPT Sư Phạm - Kỹ Thuật", "THPT Tây Đô", "THPT Thái Phiên", "THPT Trần Cao Vân", "THPT Trần Đại Nghĩa", "THPT Trần Hưng Đạo", "THPT Trần Phú", "THPT Trần Quốc Toản", "THPT Trần Văn Ơn", "THPT Trần Xuân Soạn", "THPT Trịnh Hoài Đức", "THPT Trưng Vương", "THPT Vĩnh Trường", "THPT Yên Bái", "THPT Yên Nghĩa"};
// danh sách các quận ở TPHCM 
vector<string> districts = {"Quận 1", "Quận 2", "Quận 3", "Quận 4", "Quận 5", "Quận 6", "Quận 7", "Quận 8", "Quận 9", "Quận 10", "Quận 11", "Quận 12", "Thủ Đức", "Gò Vấp", "Bình Thạnh", "Tân Bình", "Tân Phú", "Phú Nhuận", "Bình Tân", "Củ Chi", "Hóc Môn", "Bình Chánh", "Nhà Bè", "Cần Giờ"};
// danh sách 20 tên đường
vector<string> streetNames = {"Nguyễn Huệ", "Điện Biên Phủ", "Lê Lai", "Trần Hưng Đạo", "Võ Văn Kiệt", "Cách Mạng Tháng Tám", "Nam Kỳ Khởi Nghĩa", "Phạm Văn Đồng", "Nguyễn Văn Cừ", "Lê Duẩn", "Nguyễn Thị Minh Khai", "Trần Quang Khải", "Hai Bà Trưng", "Tôn Đức Thắng", "Lý Tự Trọng", "Bà Huyện Thanh Quan", "Lê Thánh Tôn", "Võ Thị Sáu", "Nguyễn Bỉnh Khiêm", "Hàm Nghi"};

//tạo seed ngẫu nhiên cho generator, sau đó sử dụng một loại generator ngẫu nhiên mt19937 để random
random_device rd;
mt19937 rng(rd());
string getRandomName() 
{
	// sử dụng class uniform_int_distribution để random số ngẫu nhiên trong khoảng cho trước
	// random chỉ số trong các list
	uniform_int_distribution<int> firstNameDist(0, firstNames.size() - 1);
	uniform_int_distribution<int> midNameDist1(0, midNames.size() - 1);
	uniform_int_distribution<int> midNameDist2(0, midNames.size() - 1);
	uniform_int_distribution<int> lastNameDist(0, lastNames.size() - 1);
	// random số từ trong một cái tên, ở đây em random từ 2 tới 4
	uniform_int_distribution<int> wordsDist(2, 4);

	int numOfWords = wordsDist(rng);
	// lấy các thành phần trong danh sách từ chỉ số đã random được ở trên
	string firstName = firstNames[firstNameDist(rng)];
	string midName1 = midNames[midNameDist1(rng)];
	string midName2 = midNames[midNameDist2(rng)];
	string lastName = lastNames[lastNameDist(rng)];
	//ghép các thành phần để được một cái tên hoàn chỉnh
	if (numOfWords == 2) return firstName + ' ' + lastName;
	else if (numOfWords == 4) return firstName + ' ' + midName1 + ' ' + midName2 + ' ' + lastName;
	else return firstName + ' ' + midName1 + ' ' + lastName;
}
// hàm random trường học, cách thức random tương tự như hàm random tên ở trên.
string getRandomSchool()
{
	uniform_int_distribution<int> schoolDist(0, schools.size() - 1);
	return schools[schoolDist(rng)];
}
// hàm random địa chỉ
string getRandomAddress()
{
	uniform_int_distribution<int> districtDist(0,districts.size() - 1);
	uniform_int_distribution<int> streetNameDist(0, streetNames.size() - 1);
	uniform_int_distribution<int> numberDist(1,1000);

	return to_string(numberDist(rng)) + " " + streetNames[streetNameDist(rng)] + ", " + districts[districtDist(rng)] + ", TPHCM";
}
// hàm random số cccd
// ta random lần lượt 12 chữ số rồi ghép lại để được số cccd
string getRandomCCCD()
{
	string cccd = "";
	for (int i = 0; i < 12; ++i)
	{
		uniform_int_distribution<int> digit(0,9);
		cccd += to_string(digit(rng));
	}
	return cccd;
}
// class date
class date
{
public:
	int day, month, year;
	string full;
	// constructor khởi tạo ngày bằng cách random
	date()
	{
		uniform_int_distribution<int> dateDist(1,28);
		uniform_int_distribution<int> monthDist(1,12);
		uniform_int_distribution<int> yearDist(2005,2007);
		day = dateDist(rng);
		month = monthDist(rng);
		year = yearDist(rng);
		// ghép các thành phần để được chuỗi ngày/tháng/năm hoàn chỉnh
		full = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	}
};
// hàm random điểm số
float getRandomPoint()
{
	uniform_real_distribution<float> pointDist(0,10);
	return round(pointDist(rng) * 100) / 100.0;
}
// class trường học, gồm các thuộc tính giống như bảng TRUONG
class Truong
{
public:
	string MATR, TENTR, DCHITR;
	Truong(int i)
	{
		// tạo mã trường theo format TRxxx với xxx là 3 chữ số thể hiện số thứ tự của trường
		MATR = "TR" + string((3 - to_string(i).length()),'0') + to_string(i);
		TENTR = getRandomSchool();
		DCHITR = getRandomAddress();
	}
};
// class học sinh, gồm các thuộc tính giống như bảng HS
class Hocsinh
{
public:
	string MAHS,ho,ten,cccd,DCHI_HS;
	date ntns;
	Hocsinh(int i)
	{
		// tạo mã học sinh theo format HSxxxxxxx với xxxxxxx là 7 chữ số thể hiện số thứ tự học sinh.
		MAHS = "HS" + string(7 - to_string(i).length(),'0') + to_string(i);
		// random một cái tên, sau đó tách từ đầu tiên để làm họ, phần còn lại là tên
		string hoten = getRandomName();
		int split_pos = 0;
		while (hoten[split_pos] != ' ')
			split_pos++;
		ho = "",ten = "";
		for (int j = 0; j < hoten.length(); ++j)
		{
			if (j < split_pos) ho += hoten[j];
			else if (j > split_pos) ten += hoten[j];         
		}
		cccd = getRandomCCCD();
		DCHI_HS = getRandomAddress();
	}
};
// hàm xét xếp loại và kết quả học tập của học sinh dựa vào điểm trung bình
void xeploai_ketqua(string &xeploai, string &kqua, float diemtb)
{
	if (diemtb >= 5) kqua = "Hoàn thành";
	else kqua = "Chưa hoàn thành";
	if (diemtb >= 9)  xeploai = "Xuất sắc";
	else if (diemtb >= 8) xeploai = "Giỏi";
	else if (diemtb >= 6.5) xeploai = "Khá";
	else if (diemtb >= 5) xeploai = "Trung bình";
	else xeploai = "Yếu"; 
}
int main() 
{
	// Tạo thư mục mới
    system("mkdir insert_query");	
	// viết câu lệnh insert data vào bảng trường, viết vào file TRUONG.sql
	ofstream truong("insert_query/TRUONG.sql");
	ofstream dstruong("insert_query/DS_truong.txt");
	vector<Truong*> trg(101);
	for (int i = 1; i <= 100; ++i)
	{
		trg[i] = new Truong(i);
		dstruong<<trg[i]->TENTR<<'\n';
		truong<<"INSERT INTO TRUONG VALUE(N'"<<trg[i]->MATR<<"',N'"<<trg[i]->TENTR<<"',N'"<<trg[i]->DCHITR<<"');\n";
	}
	// viết câu lệnh insert data vào bảng hs, viết vào file HS.sql
	ofstream hs("insert_query/HS.sql");
	vector<Hocsinh*> HS(MAX + 1);
	for (int i = 1; i <= MAX; ++i)
	{
		HS[i] = new Hocsinh(i);
		hs<<"INSERT INTO HS VALUE(N'"<<HS[i]->MAHS<<"',N'"<<HS[i]->ho<<"',N'"<<HS[i]->ten<<"','"<<HS[i]->cccd<<"','"<<HS[i]->ntns.full<<"',N'"<<HS[i]->DCHI_HS<<"');\n";    
	}
	// viết câu lệnh insert data vào bảng hoc, viết vào file HOC.sql
	ofstream hoc("insert_query/HOC.sql");
	string namhoc[3] = {"2020-2021", "2021-2022", "2022-2023"};
	for (int i = 1; i <= MAX; ++i)
	{
		uniform_int_distribution<int> schoolDist(1,100);
		Truong* pTruong = trg[schoolDist(rng)];
		float diemtb;
		string xeploai, kqua;
		// học sinh sẽ học 1,2 hoặc 3 năm tùy thuộc vào độ tuổi, mỗi năm học tương ứng với 1 dòng dữ liệu
		// do đó mỗi học sinh sẽ có từ 1 tới 3 dòng trong bảng HOC
		for (int j = 0; j < 2008 - HS[i]->ntns.year; ++j)
		{
			diemtb = getRandomPoint();
			xeploai_ketqua(xeploai, kqua, diemtb);
			hoc<<"INSERT INTO HOC VALUE(N'"<<pTruong->MATR<<"',N'"<<HS[i]->MAHS<<"',N'"<<namhoc[j]<<"',"<<diemtb<<",N'"<<xeploai<<"',N'"<<kqua<<"');\n";
		}
	}
	// dọn rác cho bộ nhớ
	for (int i = 1; i <= MAX; ++i)
	{
		if (i <= 100) delete trg[i];
		delete HS[i];
	}
	return 0;
}