#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <fstream>
using namespace std;

// Functions for Expense Tracker
void saveToFile(const string& expenseName, float amount, const string& date, const string& filename);
void displayExpenses(const string& filename);
void deleteExpense(const string& filename, const string& expenseName);

// Functions for Income Tracker
void luuvaofile(const map<string, double long>& dulieu, const string& tenfile);
void docfile(map<string, double long>& dulieu, const string& tenfile);

// Expense Tracker
void runExpenseTracker() {
    string filename = "personal_expenses.txt";
    int choice;

    do {
        cout << "\n1. Nhap chi tieu\n";
        cout << "2. Hien thi chi tieu\n";
        cout << "3. Xoa chi tieu\n";
        cout << "4. Thoat\n";
        cout << "Chon mot phuong phap: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string expenseName, date;
            float amount;
            cout << "Loai hinh chi tieu la: ";
            getline(cin, expenseName);
            cout << "Xin hay nhap so tien chi tieu: ";
            cin >> amount;
            cin.ignore();
            cout << "Nhap ngay chi tieu (dd/mm/yyyy): ";
            getline(cin, date);

            saveToFile(expenseName, amount, date, filename);
        }
        else if (choice == 2) {
            displayExpenses(filename);
        }
        else if (choice == 3) {
            string expenseName;
            cout << "Nhap ten chi tieu can xoa: ";
            getline(cin, expenseName);
            deleteExpense(filename, expenseName);
        }

    } while (choice != 4);
}

// Income Tracker
void runIncomeTracker() {
    char tieptuc;
    double long tongtien = 0.0;
    double long tienluong, tienphucap, tienthuong, thunhapphu, dautu, thunhaptamthoi, banbetrano;

    map<string, double long> savings;
    string date;
    const string filename = "dulieutien.txt";
    docfile(savings, filename);

    cout << "Hay nhap ngay thang nam ban muon luu lai (dd/mm/yyyy): ";
    cin >> date;
    cout << "1.Tien luong\n2.Tien phu cap\n3.Tien thuong\n4.Thu nhap phu\n5.Dau tu\n6.Thu nhap tam thoi\n7.Ban be tra no" << endl;

    do {
        cout << "Hay chon danh muc tien thu nhap: ";
        int luachon;
        cin >> luachon;
        switch (luachon) {
        case 1:
            cout << "Hay nhap so tien: ";
            cin >> tienluong;
            tongtien += tienluong;
            break;
        case 2:
            cout << "Hay nhap so tien: ";
            cin >> tienphucap;
            tongtien += tienphucap;
            break;
        case 3:
            cout << "Hay nhap so tien: ";
            cin >> tienthuong;
            tongtien += tienthuong;
            break;
        case 4:
            cout << "Hay nhap so tien: ";
            cin >> thunhapphu;
            tongtien += thunhapphu;
            break;
        case 5:
            cout << "Hay nhap so tien: ";
            cin >> dautu;
            tongtien += dautu;
            break;
        case 6:
            cout << "Hay nhap so tien: ";
            cin >> thunhaptamthoi;
            tongtien += thunhaptamthoi;
            break;
        case 7:
            cout << "Hay nhap so tien: ";
            cin >> banbetrano;
            tongtien += banbetrano;
            break;
        default:
            cout << "Lua chon khong hop le!";
            break;
        }
        cout << "Ban co muon tiep tuc chuong trinh ?(Y/N): ";
        cin >> tieptuc;
    } while (tieptuc == 'Y' || tieptuc == 'y');

    savings[date] = tongtien;

    cout << "Tong so tien ban da thu duoc hom nay la: " << fixed << setprecision(0) << tongtien << " VND" << endl;
    luuvaofile(savings, filename);

    char ykien;
    cout << "Ban co muon kiem tra tien cua nhung ngay khac ?(Y/N):";
    cin >> ykien;
    if (ykien == 'Y' || ykien == 'y') {
        do {
            string ngaykiemtra;
            cout << "Hay nhap ngay ban muon kiem tra (dd/mm/yyyy): ";
            cin >> ngaykiemtra;
            auto it = savings.find(ngaykiemtra);
            if (it != savings.end()) {
                cout << "So tien ban da thu duoc vao ngay " << ngaykiemtra << " la: " << it->second << " VND" << endl;
            }
            else {
                cout << "Khong co du lieu!";
            }
            cout << "Ban co muon tiep tuc kiem tra ?(Y/N): ";
            cin >> ykien;
        } while (ykien == 'y' || ykien == 'Y');
    }
}

void viewhistory() {
    string filename = "personal_expenses.txt";//đọc dữ liệu trog file 
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file hoac file khong ton tai " << endl;
    }
    string line;
    cout << "\n--- LICH SU TIEU DUNG ---\n";
    while (getline(file, line)) {
        int pos1 = line.find(';');
        int pos2 = line.rfind(';');
        string expenseName = line.substr(0, pos1);
        string amountStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
        float amount = 0;
        try {
            amount = stof(amountStr);
        }
        catch (const std::invalid_argument& e) {
            cout << "Loi: Dinh dang so tien khong hop le: " << amountStr << endl;
            continue; // Bỏ qua dòng này và tiếp tục với dòng tiếp theo
        }
        string date = line.substr(pos2 + 1);
        cout << "So tien ban dung de lam:" << expenseName << "vao ngay:" << date << "la:" << amount << "VND" << endl;
    }
    file.close();
}

// Main Menu
int main() {
    int programChoice;
    cout << "Chon chuong trinh:\n";
    cout << "1. Quan ly chi tieu\n";
    cout << "2. Quan ly thu nhap\n";
    cout << "3. Lich su tieu dung\n";
    cout << "Lua chon cua ban: ";
    cin >> programChoice;

    if (programChoice == 1) {
        runExpenseTracker();
    }
    else if (programChoice == 2) {
        runIncomeTracker();
    }
    else if (programChoice == 3) {
        viewhistory();
    }
    else {
        cout << "Lua chon khong hop le!";
    }

    return 0;
}

// Expense Tracker Functions
void saveToFile(const string& expenseName, float amount, const string& date, const string& filename) {
    ofstream file(filename, ios::app);  // Mở file ở chế độ append (ios::app) để thêm vào cuối file
    if (!file) {
        cout << "Loi khi mo file de ghi!" << endl;
        return;
    }

    file << expenseName << ";" << amount << ";" << date << endl;
    file.close();
    cout << "Du lieu da duoc luu thanh cong!" << endl;
}

void displayExpenses(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Loi khi mo file de doc hoac file chua ton tai!" << endl;
        return;
    }

    string name, date, line;
    float amount, total = 0;
    bool hasData = false;

    while (getline(file, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.rfind(';');

        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            name = line.substr(0, pos1);
            string amountStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
            float amount = 0;
            try {
                amount = stof(amountStr);
            }
            catch (const std::invalid_argument& e) {
                cout << "Loi: Dinh dang so tien khong hop le: " << amountStr << endl;
                continue; // Bỏ qua dòng này và tiếp tục với dòng tiếp theo
            }
            date = line.substr(pos2 + 1);
            cout << "[" << date << "] " << name << ": " << amount << " VND" << endl;
            total += amount;
            hasData = true;
        }
    }

    if (!hasData) {
        cout << "Chua co chi tieu nao duoc luu!" << endl;
    }
    else {
        cout << "Tong chi tieu: " << total << " VND" << endl;
    }

    file.close();
}

void deleteExpense(const string& filename, const string& expenseName) {
    ifstream file(filename);
    if (!file) {
        cout << "Loi khi mo file de doc!" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cout << "Loi khi tao file tam!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            if (name != expenseName) {
                tempFile << line << endl;
            }
            else {
                found = true;
            }
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        if (remove(filename.c_str()) != 0) {
            cout << "Loi: Khong the xoa file goc!" << endl;
            return;
        }
        if (rename("temp.txt", filename.c_str()) != 0) {
            cout << "Loi: Khong the doi ten file!" << endl;
            return;
        }
        cout << "Da xoa chi tieu: " << expenseName << endl;
    }
    else {
        remove("temp.txt");
        cout << "Khong tim thay chi tieu can xoa!" << endl;
    }
}

// Income Tracker Functions
void luuvaofile(const map<string, double long>& dulieu, const string& tenfile) {
    ofstream file(tenfile, ios::app);  // Mở file ở chế độ append để thêm dữ liệu
    if (file.is_open()) {
        for (const auto& entry : dulieu) {
            file << entry.first << " " << entry.second << endl;
        }
        file.close();
        cout << "Du lieu da duoc luu lai!" << endl;
    }
    else {
        cout << "Khong the luu du lieu" << endl;
    }
}

void docfile(map<string, double long>& dulieu, const string& tenfile) {
    ifstream file(tenfile);
    if (file.is_open()) {
        string date;
        double long amount;
        while (file >> date >> amount) {
            dulieu[date] = amount;
        }
        file.close();
    }
    else {
        cout << "Khong co du lieu tu truoc do!" << endl;
    }
}