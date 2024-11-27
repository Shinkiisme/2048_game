#include "2048Lib.hpp"

//Hàm khởi tạo trò chơi mới
void newGame(sf::RenderWindow& window, const sf::Font& font, int**& bang, int& size, Node*& currentNode, std::string& username, bool& isNewGame) {
    // Hiển thị màn hình chào mừng
    printWelcomeScreen(window, font);

    // Lấy tên người chơi từ người dùng
    username = playerName(window, font);
    
    // Nếu người chơi không nhập tên/ấn thoát, giải phóng bộ nhớ và thoát chương trình
    if (username == "") {
        freeMemory(bang, size, currentNode); // Giải phóng bộ nhớ
        exit(0); // Thoát chương trình
    }

    // Tải trò chơi đã lưu nếu có, hoặc trả về nullptr nếu không có
    bang = loadSave(size, username);

    // Nếu không có trò chơi đã lưu
    if (bang == nullptr) {

        // Yêu cầu người chơi nhập kích thước bảng
        size = sizeInput(window, font);

        // Nếu người chơi ấn thoát khi nhập kích thước, giải phóng bộ nhớ và thoát
        if (size == -1) {
            freeMemory(bang, size, currentNode);
            exit(0);
        }

        // Tạo bảng mới với kích thước được chọn
        bang = makeGrid(size);

        // Sinh số ngẫu nhiên đầu tiên trên bảng
        randNumber(bang, size);
    }

    // Khởi tạo trạng thái trò chơi hiện tại cho 'currentNode'
    currentNode->gameState = new int[size * size];

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            currentNode->gameState[i * size + j] = bang[i][j]; // Sao chép giá trị từ bảng hiện tại

    // Đặt cờ 'isNewGame' thành false, vì trò chơi đã được khởi tạo
    isNewGame = false;
}