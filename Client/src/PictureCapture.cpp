#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "base64.h" 

using namespace cv;
using namespace std;
using json = nlohmann::json;


size_t write_callback(char* ptr, size_t size, size_t nmemb, string* data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

int main() {
   
    setlocale(LC_ALL,"Ru");
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Не удалось открыть камеру!" << endl;
        return -1;
    }

    Mat frame;
    cap >> frame;

   
    if (frame.empty()) {
        cerr << "Пустой кадр!" << endl;
        return -1;
    }

    
    vector<uchar> buffer;
    imencode(".png", frame, buffer);

    
    string base64_image = base64_encode(buffer.data(), buffer.size());

  
    json json_data;
    json_data["image"] = base64_image;

    
    string json_string = json_data.dump();

    
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/receive_image");

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_string.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        string response_data;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "Ошибка при отправке запроса: " << curl_easy_strerror(res) << endl;
        }
        else {
            cout << "Отправлено изображение на сервер." << endl;
            cout << "Ответ сервера: " << response_data << endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}
