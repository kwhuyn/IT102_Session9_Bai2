#include <stdio.h>
#include <string.h>

// Định nghĩa cấu trúc FlightTicket theo yêu cầu bài toán
struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;       // 1: Eco, 2: Deluxe, 3: Business
    float baggageWeight;   // Tổng trọng lượng hành lý ký gửi (kg)
    float baggageFee;      // Tiền phạt quá cước (VNĐ)
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int choice;

    do {
        printf("\n=== HỆ THỐNG BÁN VÉ VÀ CHECK-IN MÁY BAY ===\n");
        printf("1. Thêm vé máy bay mới\n");
        printf("2. Hiển thị danh sách vé\n");
        printf("3. Cập nhật hành lý theo PNR\n");
        printf("4. Xóa vé theo PNR\n");
        printf("5. Thoát\n");
        printf("Lựa chọn của bạn: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Lựa chọn không hợp lệ! Vui lòng nhập lại.\n");
            while (getchar() != '\n'); // Xóa bộ đệm
            continue;
        }
        while (getchar() != '\n'); // Xóa ký tự xuống dòng thừa sau khi đọc số

        switch (choice) {
            case 1: {
                // Kiểm tra điều kiện biên danh sách đầy
                if (soLuong >= 100) {
                    printf("Danh sách vé đã đầy, không thể thêm mới!\n");
                    break;
                }

                printf("Nhập mã PNR: ");
                scanf("%s", danhSachVe[soLuong].pnrCode);
                while (getchar() != '\n');

                printf("Nhập họ tên hành khách: ");
                fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
                danhSachVe[soLuong].passengerName[strcspn(danhSachVe[soLuong].passengerName, "\n")] = '\0';

                printf("Nhập hạng vé (1-Eco, 2-Deluxe, 3-Business): ");
                scanf("%d", &danhSachVe[soLuong].ticketClass);
                while (getchar() != '\n');

                printf("Nhập khối lượng hành lý (kg): ");
                scanf("%f", &danhSachVe[soLuong].baggageWeight);
                while (getchar() != '\n');

                // Tính toán phí phạt quá cước hành lý
                if (danhSachVe[soLuong].ticketClass == 3) {
                    danhSachVe[soLuong].baggageFee = 0.0f; // Business miễn phí toàn bộ
                } else {
                    if (danhSachVe[soLuong].baggageWeight <= 7.0f) {
                        danhSachVe[soLuong].baggageFee = 0.0f;
                    } else {
                        danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
                    }
                }

                soLuong++;
                printf("=> Thêm vé thành công! Cước phạt hành lý quá cân: %.0f VNĐ.\n", danhSachVe[soLuong - 1].baggageFee);
                break;
            }
            case 2: {
                // Kiểm tra danh sách rỗng
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                    break;
                }

                printf("\n=========================================================================================\n");
                printf("%-5s | %-10s | %-25s | %-12s | %-15s | %-20s\n", "STT", "Mã PNR", "Họ tên hành khách", "Hạng vé", "Hành lý (kg)", "Cước quá cước");
                printf("-----------------------------------------------------------------------------------------\n");
                for (int i = 0; i < soLuong; i++) {
                    char className[15];
                    if (danhSachVe[i].ticketClass == 1) strcpy(className, "Eco");
                    else if (danhSachVe[i].ticketClass == 2) strcpy(className, "Deluxe");
                    else strcpy(className, "Business");

                    printf("%-5d | %-10s | %-25s | %-12s | %-15.1f | %.0f VNĐ\n", 
                        i + 1, 
                        danhSachVe[i].pnrCode, 
                        danhSachVe[i].passengerName, 
                        className, 
                        danhSachVe[i].baggageWeight, 
                        danhSachVe[i].baggageFee);
                }
                printf("=========================================================================================\n");
                break;
            }
            case 3: {
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                    break;
                }

                char pnrInput[15];
                printf("Nhập mã PNR cần cập nhật hành lý: ");
                scanf("%s", pnrInput);
                while (getchar() != '\n');

                int foundIndex = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                        foundIndex